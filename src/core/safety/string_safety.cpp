// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/safety/string_safety.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <regex>
#include <set>
#include <cstdio>

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

}  // namespace

SafetyProfile loadDefaultSafetyProfile() {
    SafetyProfile out;
    // Empty rule_pack_ids means "load every runtime rule pack"; if none
    // exist, the engine falls back to the built-in MVP rules.

    const std::filesystem::path homeProfilePath =
        auraHome() / "safety-profiles" / "default.json";
    std::string text = readFile(homeProfilePath);
    if (text.empty()) {
        text = readFile(safetyAssetsRoot() / "safety-profiles" /
                        "default.json");
    }
    if (text.empty()) return out;

    cJSON* root = cJSON_ParseWithLength(text.data(), text.size());
    if (!root) return out;

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
    return out;
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
