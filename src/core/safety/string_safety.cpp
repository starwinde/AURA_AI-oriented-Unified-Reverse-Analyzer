// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/safety/string_safety.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <initializer_list>
#include <map>
#include <cstdio>
#include <regex>
#include <set>

#include "cJSON.h"

namespace aura::safety {

namespace {

struct Rule {
    std::string id;
    std::string kind;
    std::string pattern;
    double confidence = 0.80;
};

std::string readFile(const std::filesystem::path& path) {
    FILE* f = std::fopen(path.string().c_str(), "rb");
    if (!f) return {};
    std::string out;
    char buf[4096];
    while (true) {
        const size_t n = std::fread(buf, 1, sizeof(buf), f);
        if (n > 0) out.append(buf, n);
        if (n < sizeof(buf)) break;
    }
    std::fclose(f);
    return out;
}

std::string firstNonEmpty(std::initializer_list<std::string> values) {
    for (const auto& value : values) {
        if (!value.empty()) return value;
    }
    return {};
}

std::string firstNonEmpty(const std::vector<std::string>& values) {
    for (const auto& value : values) {
        if (!value.empty()) return value;
    }
    return {};
}

std::filesystem::path auraHome() {
    if (const char* env = std::getenv("AURA_HOME")) {
        if (*env) return std::filesystem::path(env);
    }
#ifdef _WIN32
    if (const char* env = std::getenv("USERPROFILE")) {
        if (*env) return std::filesystem::path(env) / ".aura";
    }
#else
    if (const char* env = std::getenv("HOME")) {
        if (*env) return std::filesystem::path(env) / ".aura";
    }
#endif
    return std::filesystem::path(".aura");
}

std::string jsonString(cJSON* obj, const char* key) {
    cJSON* v = cJSON_GetObjectItemCaseSensitive(obj, key);
    return cJSON_IsString(v) && v->valuestring ? v->valuestring : "";
}

std::vector<std::string> jsonStringArray(cJSON* obj, const char* key) {
    std::vector<std::string> out;
    cJSON* values = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!cJSON_IsArray(values)) return out;
    cJSON* item = nullptr;
    cJSON_ArrayForEach(item, values) {
        if (cJSON_IsString(item) && item->valuestring)
            out.emplace_back(item->valuestring);
    }
    return out;
}

double jsonNumber(cJSON* obj, const char* key, double fallback) {
    cJSON* v = cJSON_GetObjectItemCaseSensitive(obj, key);
    return cJSON_IsNumber(v) ? v->valuedouble : fallback;
}

SafetyAssetRef refFromJsonFile(const std::filesystem::path& path,
                               const std::string& source,
                               std::initializer_list<const char*> idKeys,
                               std::string fallbackId = {}) {
    SafetyAssetRef ref;
    ref.path = path.string();
    ref.source = source;
    if (fallbackId.empty()) fallbackId = path.parent_path().filename().string();

    const std::string text = readFile(path);
    if (text.empty()) {
        ref.valid = false;
        ref.diagnostic = "manifest is empty or unreadable";
        ref.id = fallbackId;
        return ref;
    }

    cJSON* root = cJSON_ParseWithLength(text.data(), text.size());
    if (!root) {
        ref.valid = false;
        ref.diagnostic = "manifest is not valid JSON";
        ref.id = fallbackId;
        return ref;
    }

    std::vector<std::string> ids;
    for (const char* key : idKeys) ids.push_back(jsonString(root, key));
    ref.id = firstNonEmpty(ids);
    ref.display_name = firstNonEmpty({
        jsonString(root, "display_name"),
        jsonString(root, "name"),
        ref.id,
    });
    cJSON_Delete(root);

    if (ref.id.empty()) {
        ref.valid = false;
        ref.diagnostic = "manifest does not contain an asset id";
        ref.id = fallbackId;
    }
    return ref;
}

void appendUniqueAsset(std::vector<SafetyAssetRef>& out, SafetyAssetRef ref) {
    const auto sameId = [&](const SafetyAssetRef& existing) {
        return existing.id == ref.id;
    };
    if (std::find_if(out.begin(), out.end(), sameId) == out.end()) {
        out.push_back(std::move(ref));
    }
}

void listAssetDirs(const std::filesystem::path& root,
                   const std::string& source,
                   const char* manifestName,
                   std::initializer_list<const char*> idKeys,
                   std::vector<SafetyAssetRef>* out) {
    if (!out) return;
    std::error_code ec;
    if (!std::filesystem::is_directory(root, ec)) return;
    for (const auto& ent : std::filesystem::directory_iterator(root, ec)) {
        if (ec) break;
        std::error_code entEc;
        if (!ent.is_directory(entEc)) continue;
        const auto manifestPath = ent.path() / manifestName;
        if (!std::filesystem::exists(manifestPath, entEc)) continue;
        appendUniqueAsset(*out,
                          refFromJsonFile(manifestPath, source, idKeys));
    }
}

void listProfileFiles(const std::filesystem::path& root,
                      const std::string& source,
                      std::vector<SafetyAssetRef>* out) {
    if (!out) return;
    std::error_code ec;
    if (!std::filesystem::is_directory(root, ec)) return;
    for (const auto& ent : std::filesystem::directory_iterator(root, ec)) {
        if (ec) break;
        std::error_code entEc;
        if (!ent.is_regular_file(entEc) || ent.path().extension() != ".json")
            continue;
        appendUniqueAsset(*out, refFromJsonFile(ent.path(), source,
                                                {"profile_id"},
                                                ent.path().stem().string()));
    }
}

std::filesystem::path safetyAssetsRoot() {
    if (const char* env = std::getenv("AURA_SAFETY_ASSETS_DIR")) {
        if (*env) return std::filesystem::path(env);
    }
    return std::filesystem::path("assets") / "safety";
}

ModelPolicyMode parseModelPolicyMode(const std::string& text) {
    if (text == "conditional") return ModelPolicyMode::Conditional;
    if (text == "required") return ModelPolicyMode::Required;
    return ModelPolicyMode::Disabled;
}

ModelFailureAction parseModelFailureAction(const std::string& text) {
    if (text == "block_export") return ModelFailureAction::BlockExport;
    return ModelFailureAction::Degrade;
}

std::vector<Rule> builtinRules() {
    return {
        {
            "builtin/email",
            "email",
            R"([A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,})",
            0.98,
        },
        {
            "builtin/kr-phone",
            "phone_number",
            R"(\b(?:\+82[- .]?)?(?:(?:0?1[016789])[- .]?\d{3,4}[- .]?\d{4}|(?:0?(?:2|[3-6][1-5]|70))[- .]?\d{3,4}[- .]?\d{4})\b)",
            0.86,
        },
        {
            "builtin/api-key",
            "api_key",
            R"((api[_\- ]?key|secret|token|password|passwd)[A-Za-z0-9_ .:=\-]{0,24}['"]?[A-Za-z0-9_\-]{16,})",
            0.90,
        },
        {
            "builtin/bearer-token",
            "token",
            R"(Bearer[ \t]+[A-Za-z0-9_\-\.]{16,})",
            0.92,
        },
        {
            "builtin/url",
            "url",
            R"(https?://[A-Za-z0-9.\-_/:%?&=#]+)",
            0.82,
        },
        {
            "builtin/ipv4",
            "ip_address",
            R"(\b(?:\d{1,3}\.){3}\d{1,3}\b)",
            0.76,
        },
        {
            "builtin/windows-path",
            "internal_path",
            R"([A-Za-z]:\\(?:[^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]*)",
            0.78,
        },
        {
            "builtin/posix-path",
            "internal_path",
            R"(/(?:home|Users|var|etc|opt|srv|mnt)/[A-Za-z0-9._/\-]+)",
            0.78,
        },
    };
}

std::vector<Rule> parseRulesJson(const std::string& text) {
    std::vector<Rule> out;
    cJSON* root = cJSON_ParseWithLength(text.data(), text.size());
    if (!root) return out;
    cJSON* rules = cJSON_GetObjectItemCaseSensitive(root, "rules");
    if (!cJSON_IsArray(rules)) {
        cJSON_Delete(root);
        return out;
    }
    cJSON* item = nullptr;
    cJSON_ArrayForEach(item, rules) {
        if (!cJSON_IsObject(item)) continue;
        Rule r;
        r.id = jsonString(item, "id");
        r.kind = jsonString(item, "kind");
        r.pattern = jsonString(item, "pattern");
        r.confidence = jsonNumber(item, "confidence", 0.80);
        if (!r.id.empty() && !r.kind.empty() && !r.pattern.empty())
            out.push_back(std::move(r));
    }
    cJSON_Delete(root);
    return out;
}

std::vector<Rule> loadRulesFile(const std::filesystem::path& path) {
    return parseRulesJson(readFile(path));
}

std::vector<Rule> loadRulePackDirectory(const std::filesystem::path& dir) {
    if (!std::filesystem::is_directory(dir)) return {};
    const std::filesystem::path manifestPath = dir / "manifest.json";
    std::filesystem::path rulesPath = dir / "rules.json";
    const std::string manifestText = readFile(manifestPath);
    if (!manifestText.empty()) {
        cJSON* root =
            cJSON_ParseWithLength(manifestText.data(), manifestText.size());
        if (root) {
            const std::string rulesFile = jsonString(root, "rules_file");
            if (!rulesFile.empty()) rulesPath = dir / rulesFile;
            cJSON_Delete(root);
        }
    }
    return loadRulesFile(rulesPath);
}

void appendRules(std::vector<Rule>& dst, std::vector<Rule> src) {
    dst.insert(dst.end(),
               std::make_move_iterator(src.begin()),
               std::make_move_iterator(src.end()));
}

std::vector<Rule> loadRulesFromRoot(const std::filesystem::path& root,
                                    const SafetyProfile& profile,
                                    bool includeLegacyFiles,
                                    std::set<std::string>* loadedIds,
                                    const std::set<std::string>& skipIds) {
    std::vector<Rule> out;
    std::error_code ec;
    if (!std::filesystem::exists(root, ec)) return out;

    std::vector<std::string> wanted = profile.rule_pack_ids;
    const bool acceptAll = wanted.empty();
    auto wants = [&](const std::filesystem::path& p) {
        if (acceptAll) return true;
        const std::string stem = p.stem().string();
        const std::string filename = p.filename().string();
        if (std::find(wanted.begin(), wanted.end(), filename) != wanted.end())
            return true;
        return std::find(wanted.begin(), wanted.end(), stem) != wanted.end();
    };

    for (const auto& ent : std::filesystem::directory_iterator(root, ec)) {
        if (ec) break;
        if (!wants(ent.path())) continue;
        const std::string assetId = ent.is_directory()
                                        ? ent.path().filename().string()
                                        : ent.path().stem().string();
        if (skipIds.find(assetId) != skipIds.end()) continue;
        std::vector<Rule> rules;
        if (ent.is_directory()) {
            rules = loadRulePackDirectory(ent.path());
        } else if (includeLegacyFiles && ent.is_regular_file() &&
                   ent.path().extension() == ".json") {
            rules = loadRulesFile(ent.path());
        }
        if (!rules.empty()) {
            appendRules(out, std::move(rules));
            if (loadedIds) loadedIds->insert(assetId);
        }
    }
    return out;
}

std::vector<Rule> loadRuntimeRules(const SafetyProfile& profile) {
    std::set<std::string> loadedIds;
    std::vector<Rule> out =
        loadRulesFromRoot(auraHome() / "rule-packs", profile,
                          true /* legacy ~/.aura/rule-packs/<id>.json */,
                          &loadedIds, {});
    appendRules(out, loadRulesFromRoot(safetyAssetsRoot() / "rule-packs",
                                       profile, false, &loadedIds, loadedIds));
    return out;
}

std::vector<Rule> effectiveRules(const SafetyProfile& profile) {
    auto rules = loadRuntimeRules(profile);
    if (!rules.empty()) return rules;
    return builtinRules();
}

std::string upperKind(std::string kind) {
    for (char& ch : kind) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        } else {
            ch = '_';
        }
    }
    while (!kind.empty() && kind.back() == '_') kind.pop_back();
    return kind.empty() ? "SENSITIVE" : kind;
}

bool plausibleIpv4(const std::string& text) {
    int parts = 0;
    std::size_t start = 0;
    while (start < text.size()) {
        const std::size_t dot = text.find('.', start);
        const std::string token = text.substr(start, dot == std::string::npos
                                                       ? std::string::npos
                                                       : dot - start);
        if (token.empty() || token.size() > 3) return false;
        const int n = std::atoi(token.c_str());
        if (n < 0 || n > 255) return false;
        ++parts;
        if (dot == std::string::npos) break;
        start = dot + 1;
    }
    return parts == 4;
}

bool rejectFalsePositive(const Rule& rule, const std::string& match) {
    if (rule.kind == "ip_address") return !plausibleIpv4(match);
    if (rule.kind != "api_key" && rule.kind != "token") return false;
    bool anyAlpha = false;
    bool anyDigit = false;
    for (const char ch : match) {
        anyAlpha = anyAlpha || std::isalpha(static_cast<unsigned char>(ch));
        anyDigit = anyDigit || std::isdigit(static_cast<unsigned char>(ch));
    }
    return !(anyAlpha && anyDigit);
}

bool parseSafetyProfileText(const std::string& text,
                            SafetyProfile* profile,
                            const std::string& expectedProfileId = {}) {
    if (!profile || text.empty()) return false;

    cJSON* root = cJSON_ParseWithLength(text.data(), text.size());
    if (!cJSON_IsObject(root)) {
        if (root) cJSON_Delete(root);
        return false;
    }
    if (!expectedProfileId.empty() &&
        jsonString(root, "profile_id") != expectedProfileId) {
        cJSON_Delete(root);
        return false;
    }

    SafetyProfile out;
    out.rule_pack_ids = jsonStringArray(root, "rule_pack_ids");
    out.eval_dataset_ids = jsonStringArray(root, "eval_dataset_ids");

    out.token_classification_model_id =
        jsonString(root, "token_classification_model_id");
    cJSON* enabled =
        cJSON_GetObjectItemCaseSensitive(root, "token_classification_enabled");
    out.token_classification_enabled = cJSON_IsTrue(enabled);

    cJSON* model = cJSON_GetObjectItemCaseSensitive(root, "model_policy");
    if (cJSON_IsObject(model)) {
        out.model_policy.enabled =
            cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(model, "enabled"));
        out.model_policy.mode =
            parseModelPolicyMode(jsonString(model, "mode"));
        out.model_policy.model_id = jsonString(model, "model_id");
        out.model_policy.max_input_chars = static_cast<std::size_t>(
            jsonNumber(model, "max_input_chars", 4096.0));
        out.model_policy.timeout_ms = static_cast<int>(
            jsonNumber(model, "timeout_ms", 1500.0));
        out.model_policy.run_when = jsonStringArray(model, "run_when");
        out.model_policy.on_missing =
            parseModelFailureAction(jsonString(model, "on_missing"));
        out.model_policy.on_timeout =
            parseModelFailureAction(jsonString(model, "on_timeout"));
        out.model_policy.on_error =
            parseModelFailureAction(jsonString(model, "on_error"));
        out.token_classification_enabled = out.model_policy.enabled;
        out.token_classification_model_id = out.model_policy.model_id;
    }

    cJSON_Delete(root);
    *profile = std::move(out);
    return true;
}

SafetyProfileLoadResult loadDefaultSafetyProfileResult() {
    SafetyProfileLoadResult result;
    result.profile_id = "default";

    const std::vector<std::filesystem::path> candidates = {
        auraHome() / "safety-profiles" / "default.json",
        safetyAssetsRoot() / "safety-profiles" / "default.json",
    };

    bool sawInvalid = false;
    for (const auto& path : candidates) {
        const std::string text = readFile(path);
        if (text.empty()) continue;
        SafetyProfile profile;
        if (!parseSafetyProfileText(text, &profile, "default")) {
            sawInvalid = true;
            continue;
        }
        result.found = true;
        result.path = path.string();
        result.profile = std::move(profile);
        if (sawInvalid) {
            result.used_fallback = true;
            result.diagnostic =
                "home default safety profile was invalid; used fallback";
        }
        return result;
    }

    result.diagnostic = sawInvalid ? "default safety profile is invalid"
                                   : "default safety profile not found";
    return result;
}

bool containsValidAssetId(const std::vector<SafetyAssetRef>& refs,
                          const std::string& id) {
    return std::find_if(refs.begin(), refs.end(),
                        [&](const SafetyAssetRef& ref) {
                            return ref.valid && ref.id == id;
                        }) != refs.end();
}

void addMissingAssetMessages(const std::vector<std::string>& ids,
                             const std::vector<SafetyAssetRef>& refs,
                             const char* kind,
                             std::vector<std::string>* messages) {
    if (!messages) return;
    for (const auto& id : ids) {
        if (containsValidAssetId(refs, id)) continue;
        messages->push_back(std::string("missing ") + kind + ": " + id);
    }
}

}  // namespace

SafetyAssetRegistry listSafetyAssets() {
    SafetyAssetRegistry out;

    const auto home = auraHome();
    const auto repo = safetyAssetsRoot();

    listProfileFiles(home / "safety-profiles", "home", &out.profiles);
    listProfileFiles(repo / "safety-profiles", "repo", &out.profiles);

    listAssetDirs(home / "token-classification-models", "home",
                  "manifest.json", {"model_id", "asset_id"}, &out.models);
    listAssetDirs(repo / "token-classification-models", "repo",
                  "manifest.template.json", {"model_id", "asset_id"},
                  &out.models);

    listAssetDirs(home / "rule-packs", "home", "manifest.json",
                  {"pack_id", "id"}, &out.rule_packs);
    listAssetDirs(repo / "rule-packs", "repo", "manifest.json",
                  {"pack_id", "id"}, &out.rule_packs);

    listAssetDirs(home / "eval-datasets", "home", "manifest.aura.json",
                  {"dataset_id", "asset_id"}, &out.eval_datasets);
    listAssetDirs(repo / "eval-datasets", "repo", "manifest.json",
                  {"dataset_id", "asset_id"}, &out.eval_datasets);

    return out;
}

SafetyProfileLoadResult loadSafetyProfileById(const std::string& profile_id) {
    SafetyProfileLoadResult result;
    result.profile_id = profile_id;
    if (profile_id.empty()) {
        result.diagnostic = "profile id is empty";
        return result;
    }

    std::string invalidDiagnostic;
    const auto registry = listSafetyAssets();
    for (const auto& ref : registry.profiles) {
        if (ref.id != profile_id) continue;
        if (!ref.valid) {
            invalidDiagnostic = ref.diagnostic;
            continue;
        }

        SafetyProfile profile;
        if (!parseSafetyProfileText(readFile(ref.path), &profile,
                                    profile_id)) {
            invalidDiagnostic = "safety profile is not valid JSON";
            continue;
        }

        result.found = true;
        result.path = ref.path;
        result.profile = std::move(profile);
        return result;
    }

    result.diagnostic = invalidDiagnostic.empty()
                            ? "safety profile not found: " + profile_id
                            : "safety profile is invalid: " + profile_id +
                                  " (" + invalidDiagnostic + ")";
    return result;
}

SafetyProfileLoadResult resolveSelectedSafetyProfile(
    const std::string& selected_profile_id) {
    if (selected_profile_id.empty() || selected_profile_id == "default") {
        return loadDefaultSafetyProfileResult();
    }

    auto selected = loadSafetyProfileById(selected_profile_id);
    if (selected.found) return selected;

    auto fallback = loadDefaultSafetyProfileResult();
    fallback.used_fallback = true;
    fallback.diagnostic = "selected safety profile '" + selected_profile_id +
                          "' could not be loaded; " + selected.diagnostic;
    return fallback;
}

SafetyProfileValidation validateSafetyProfile(const SafetyProfile& profile) {
    SafetyProfileValidation validation;
    const auto registry = listSafetyAssets();

    addMissingAssetMessages(profile.rule_pack_ids, registry.rule_packs,
                            "rule pack", &validation.messages);
    addMissingAssetMessages(profile.eval_dataset_ids, registry.eval_datasets,
                            "eval dataset", &validation.messages);
    if (profile.model_policy.enabled) {
        if (profile.model_policy.model_id.empty()) {
            validation.messages.push_back("missing model: <empty>");
        } else if (!containsValidAssetId(registry.models,
                                         profile.model_policy.model_id)) {
            validation.messages.push_back("missing model: " +
                                          profile.model_policy.model_id);
        }
    }
    if (profile.token_classification_enabled &&
        (!profile.model_policy.enabled ||
         profile.token_classification_model_id != profile.model_policy.model_id)) {
        if (profile.token_classification_model_id.empty()) {
            validation.messages.push_back(
                "missing token classification model: <empty>");
        } else if (!containsValidAssetId(
                       registry.models,
                       profile.token_classification_model_id)) {
            validation.messages.push_back(
                "missing token classification model: " +
                profile.token_classification_model_id);
        }
    }

    validation.valid = validation.messages.empty();
    return validation;
}

SafetyProfile loadDefaultSafetyProfile() {
    // Empty rule_pack_ids means "load every runtime rule pack"; if none
    // exist, the engine falls back to the built-in MVP rules.
    return loadDefaultSafetyProfileResult().profile;
}

std::vector<Finding> scanStringWithRulePacks(const std::string& text,
                                             const SafetyProfile& profile) {
    std::vector<Finding> out;
    for (const Rule& rule : effectiveRules(profile)) {
        try {
            const std::regex re(rule.pattern, std::regex::ECMAScript |
                                              std::regex::icase);
            for (std::sregex_iterator it(text.begin(), text.end(), re), end;
                 it != end; ++it) {
                const auto& m = *it;
                const std::string match = m.str();
                if (match.empty() || rejectFalsePositive(rule, match))
                    continue;
                Finding f;
                f.source = FindingSource::Rule;
                f.detector_id = rule.id;
                f.kind = rule.kind;
                f.start = static_cast<std::size_t>(m.position());
                f.end = f.start + static_cast<std::size_t>(m.length());
                f.confidence = rule.confidence;
                out.push_back(std::move(f));
            }
        } catch (const std::regex_error&) {
            continue;
        }
    }
    return mergeFindings(std::move(out));
}

std::vector<Finding> mergeFindings(std::vector<Finding> findings) {
    findings.erase(
        std::remove_if(findings.begin(), findings.end(),
                       [](const Finding& f) { return f.end <= f.start; }),
        findings.end());
    std::sort(findings.begin(), findings.end(), [](const Finding& a,
                                                   const Finding& b) {
        if (a.start != b.start) return a.start < b.start;
        const auto aw = a.end - a.start;
        const auto bw = b.end - b.start;
        if (aw != bw) return aw > bw;
        return a.confidence > b.confidence;
    });

    std::vector<Finding> out;
    for (Finding f : findings) {
        bool consumed = false;
        for (Finding& kept : out) {
            const bool overlap = f.start < kept.end && kept.start < f.end;
            if (!overlap) continue;
            const auto fw = f.end - f.start;
            const auto kw = kept.end - kept.start;
            if (fw > kw || (fw == kw && f.confidence > kept.confidence)) {
                kept = std::move(f);
            }
            consumed = true;
            break;
        }
        if (!consumed) out.push_back(std::move(f));
    }

    std::sort(out.begin(), out.end(), [](const Finding& a, const Finding& b) {
        return a.start < b.start;
    });
    return out;
}

void allocateMaskTokens(std::vector<Finding>& findings) {
    std::map<std::string, int> counts;
    for (Finding& f : findings) {
        if (!f.mask_token.empty()) continue;
        const std::string kind = upperKind(f.kind);
        const int n = ++counts[kind];
        f.mask_token = "[" + kind + "_" + std::to_string(n) + "]";
    }
}

void allocateMaskTokensForOriginal(const std::string& original,
                                   std::vector<Finding>& findings) {
    std::map<std::string, int> counts;
    std::map<std::string, std::string> tokenByValue;
    for (Finding& f : findings) {
        if (!f.mask_token.empty()) continue;
        const std::size_t end = std::min(f.end, original.size());
        const std::string value =
            f.start < end ? original.substr(f.start, end - f.start) : "";
        const std::string kind = upperKind(f.kind);
        const std::string key = kind + "\n" + value;
        auto it = tokenByValue.find(key);
        if (it != tokenByValue.end()) {
            f.mask_token = it->second;
            continue;
        }
        const int n = ++counts[kind];
        f.mask_token = "[" + kind + "_" + std::to_string(n) + "]";
        tokenByValue.emplace(key, f.mask_token);
    }
}

ProtectedStringView buildProtectedStringView(
    const std::string& original,
    const std::string& alias,
    std::vector<Finding> findings) {
    findings = mergeFindings(std::move(findings));
    allocateMaskTokensForOriginal(original, findings);

    std::string masked;
    std::size_t pos = 0;
    for (const Finding& f : findings) {
        if (f.start > original.size()) continue;
        const std::size_t end = std::min(f.end, original.size());
        if (end < pos) continue;
        masked.append(original.substr(pos, f.start - pos));
        masked.append(f.mask_token);
        pos = end;
    }
    masked.append(original.substr(pos));

    ProtectedStringView out;
    out.original = original;
    out.alias = alias;
    out.findings = std::move(findings);
    out.masked = out.findings.empty() ? original : masked;
    out.protected_value = !alias.empty() ? alias : out.masked;
    return out;
}

}  // namespace aura::safety
