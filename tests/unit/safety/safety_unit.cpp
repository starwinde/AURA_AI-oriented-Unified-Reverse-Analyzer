#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "aura/safety/string_safety.h"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <fstream>
#include <string>
#include <vector>

namespace {

void setEnvVar(const char* key, const std::string& value) {
#ifdef _WIN32
    _putenv_s(key, value.c_str());
#else
    setenv(key, value.c_str(), 1);
#endif
}

void clearEnvVar(const char* key) {
#ifdef _WIN32
    _putenv_s(key, "");
#else
    unsetenv(key);
#endif
}

std::filesystem::path tempRoot(const char* name) {
    const auto buildId =
        std::hash<std::string>{}(std::filesystem::current_path().string());
    return std::filesystem::temp_directory_path() /
           (std::string(name) + "_" + std::to_string(buildId));
}

}  // namespace

TEST_CASE("rule pack scan detects common sensitive strings") {
    const aura::safety::SafetyProfile profile =
        aura::safety::loadDefaultSafetyProfile();

    const auto email =
        aura::safety::scanStringWithRulePacks("alice.smith@example.com",
                                              profile);
    REQUIRE(email.size() == 1);
    CHECK(email[0].kind == "email");

    const auto token = aura::safety::scanStringWithRulePacks(
        "api_key = \"abc1234567890XYZSECRET\"", profile);
    REQUIRE(token.size() == 1);
    CHECK(token[0].kind == "api_key");

    const auto url = aura::safety::scanStringWithRulePacks(
        "https://internal.example.local/api", profile);
    REQUIRE(url.size() == 1);
    CHECK(url[0].kind == "url");

    const auto phone = aura::safety::scanStringWithRulePacks(
        "call me at 010-1234-5678", profile);
    REQUIRE(phone.size() == 1);
    CHECK(phone[0].kind == "phone_number");
}

TEST_CASE("runtime rule pack from AURA_HOME overrides built-in fallback") {
    namespace fs = std::filesystem;
    const fs::path root = tempRoot("aura_safety_unit_home");
    const fs::path packs = root / "rule-packs";
    fs::remove_all(root);
    fs::create_directories(packs);
    fs::create_directories(root / "safety-profiles");
    {
        std::ofstream out(packs / "default.json", std::ios::binary);
        out << R"({
          "schema": 1,
          "id": "default",
          "rules": [
            {
              "id": "test/customer-id",
              "kind": "customer_id",
              "pattern": "CUST-[0-9]{4}",
              "confidence": 0.88
            }
          ]
        })";
    }
    {
        std::ofstream out(root / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "default",
          "rule_pack_ids": ["default"]
        })";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto profile = aura::safety::loadDefaultSafetyProfile();
    const auto findings =
        aura::safety::scanStringWithRulePacks("ticket CUST-1234", profile);
    clearEnvVar("AURA_HOME");

    REQUIRE(findings.size() == 1);
    CHECK(findings[0].detector_id == "test/customer-id");
    CHECK(findings[0].kind == "customer_id");
}

TEST_CASE("safety profile selects directory rule packs and model policy") {
    namespace fs = std::filesystem;
    const fs::path root =
        tempRoot("aura_safety_unit_registry_home");
    fs::remove_all(root);
    const fs::path packDir = root / "rule-packs" / "korean-sensitive";
    fs::create_directories(packDir);
    fs::create_directories(root / "safety-profiles");

    {
        std::ofstream out(packDir / "manifest.json", std::ios::binary);
        out << R"({
          "schema_version": 1,
          "pack_id": "korean-sensitive",
          "version": "0.1.0",
          "locale": ["ko-KR"],
          "rules_file": "rules.json"
        })";
    }
    {
        std::ofstream out(packDir / "rules.json", std::ios::binary);
        out << R"({
          "schema_version": 1,
          "rules": [
            {
              "id": "kr/customer-id",
              "kind": "customer_id",
              "pattern": "CUST-[0-9]{4}",
              "confidence": 0.91
            }
          ]
        })";
    }
    {
        std::ofstream out(root / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "default",
          "rule_pack_ids": ["korean-sensitive"],
          "eval_dataset_ids": ["korean-sensitive"],
          "model_policy": {
            "enabled": true,
            "mode": "conditional",
            "model_id": "openai-privacy-filter",
            "max_input_chars": 4096,
            "timeout_ms": 1500,
            "run_when": ["external_export", "rule_findings_empty"],
            "on_missing": "degrade",
            "on_timeout": "degrade",
            "on_error": "degrade"
          }
        })";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto profile = aura::safety::loadDefaultSafetyProfile();
    const auto findings =
        aura::safety::scanStringWithRulePacks("ticket CUST-1234", profile);
    clearEnvVar("AURA_HOME");

    REQUIRE(profile.rule_pack_ids.size() == 1);
    CHECK(profile.rule_pack_ids[0] == "korean-sensitive");
    REQUIRE(profile.eval_dataset_ids.size() == 1);
    CHECK(profile.eval_dataset_ids[0] == "korean-sensitive");
    CHECK(profile.model_policy.enabled);
    CHECK(profile.model_policy.mode ==
          aura::safety::ModelPolicyMode::Conditional);
    CHECK(profile.model_policy.model_id == "openai-privacy-filter");
    CHECK(profile.model_policy.max_input_chars == 4096);
    CHECK(profile.model_policy.timeout_ms == 1500);
    CHECK(profile.model_policy.on_missing ==
          aura::safety::ModelFailureAction::Degrade);

    REQUIRE(findings.size() == 1);
    CHECK(findings[0].detector_id == "kr/customer-id");
    CHECK(findings[0].kind == "customer_id");
}

TEST_CASE("repo safety profile is the default when AURA_HOME has none") {
    namespace fs = std::filesystem;
    const fs::path home =
        tempRoot("aura_safety_unit_empty_home");
    const fs::path assets =
        tempRoot("aura_safety_unit_repo_assets");
    fs::remove_all(home);
    fs::remove_all(assets);
    fs::create_directories(home);
    fs::create_directories(assets / "safety-profiles");

    {
        std::ofstream out(assets / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "default",
          "rule_pack_ids": ["secret-api-key"],
          "eval_dataset_ids": ["safety-default"],
          "model_policy": {
            "enabled": true,
            "mode": "required",
            "model_id": "repo-default-model",
            "max_input_chars": 1024,
            "timeout_ms": 2500,
            "run_when": ["external_export"],
            "on_missing": "block_export",
            "on_timeout": "block_export",
            "on_error": "degrade"
          }
        })";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto profile = aura::safety::loadDefaultSafetyProfile();
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(profile.rule_pack_ids.size() == 1);
    CHECK(profile.rule_pack_ids[0] == "secret-api-key");
    CHECK(profile.model_policy.enabled);
    CHECK(profile.model_policy.mode == aura::safety::ModelPolicyMode::Required);
    CHECK(profile.model_policy.model_id == "repo-default-model");
    CHECK(profile.model_policy.max_input_chars == 1024);
    CHECK(profile.model_policy.timeout_ms == 2500);
    CHECK(profile.model_policy.on_missing ==
          aura::safety::ModelFailureAction::BlockExport);
}

TEST_CASE("safety registry lists profiles, models, rule packs, and eval datasets") {
    namespace fs = std::filesystem;
    const fs::path home =
        tempRoot("aura_safety_unit_asset_registry_home");
    const fs::path assets =
        tempRoot("aura_safety_unit_asset_registry_assets");
    fs::remove_all(home);
    fs::remove_all(assets);

    fs::create_directories(home / "safety-profiles");
    fs::create_directories(home / "token-classification-models" / "local-model");
    fs::create_directories(home / "rule-packs" / "local-rules");
    fs::create_directories(home / "eval-datasets" / "local-eval");
    fs::create_directories(assets / "safety-profiles");
    fs::create_directories(assets / "token-classification-models" /
                           "repo-model");
    fs::create_directories(assets / "rule-packs" / "local-rules");
    fs::create_directories(assets / "rule-packs" / "repo-rules");
    fs::create_directories(assets / "eval-datasets" / "repo-eval");

    {
        std::ofstream out(home / "safety-profiles" / "custom.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"custom","rule_pack_ids":["local-rules"],"eval_dataset_ids":["local-eval"],"model_policy":{"enabled":true,"mode":"conditional","model_id":"local-model"}})";
    }
    {
        std::ofstream out(home / "token-classification-models" /
                              "local-model" / "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"model_id":"local-model","display_name":"Local Model"})";
    }
    {
        std::ofstream out(home / "rule-packs" / "local-rules" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"local-rules","display_name":"Local Rules","rules_file":"rules.json"})";
    }
    {
        std::ofstream out(home / "eval-datasets" / "local-eval" /
                              "manifest.aura.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"dataset_id":"local-eval","display_name":"Local Eval"})";
    }
    {
        std::ofstream out(assets / "rule-packs" / "repo-rules" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"repo-rules","display_name":"Repo Rules","rules_file":"rules.json"})";
    }
    {
        std::ofstream out(assets / "token-classification-models" /
                              "repo-model" / "manifest.template.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"model_id":"repo-model","display_name":"Repo Model"})";
    }
    {
        std::ofstream out(assets / "eval-datasets" / "repo-eval" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"dataset_id":"repo-eval","display_name":"Repo Eval"})";
    }
    {
        std::ofstream out(assets / "rule-packs" / "local-rules" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"local-rules","display_name":"Repo Duplicate Rules","rules_file":"rules.json"})";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto registry = aura::safety::listSafetyAssets();
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(registry.profiles.size() == 1);
    CHECK(registry.profiles[0].id == "custom");
    CHECK(registry.profiles[0].source == "home");
    REQUIRE(registry.models.size() == 2);
    CHECK(std::find_if(registry.models.begin(), registry.models.end(),
                       [](const aura::safety::SafetyAssetRef& ref) {
                           return ref.id == "local-model" &&
                                  ref.source == "home";
                       }) != registry.models.end());
    CHECK(std::find_if(registry.models.begin(), registry.models.end(),
                       [](const aura::safety::SafetyAssetRef& ref) {
                           return ref.id == "repo-model" &&
                                  ref.source == "repo";
                       }) != registry.models.end());
    REQUIRE(registry.rule_packs.size() == 2);
    const auto localRules = std::find_if(
        registry.rule_packs.begin(), registry.rule_packs.end(),
        [](const aura::safety::SafetyAssetRef& ref) {
            return ref.id == "local-rules";
        });
    REQUIRE(localRules != registry.rule_packs.end());
    CHECK(localRules->source == "home");
    const auto repoRules = std::find_if(
        registry.rule_packs.begin(), registry.rule_packs.end(),
        [](const aura::safety::SafetyAssetRef& ref) {
            return ref.id == "repo-rules";
        });
    REQUIRE(repoRules != registry.rule_packs.end());
    CHECK(repoRules->source == "repo");
    REQUIRE(registry.eval_datasets.size() == 2);
    CHECK(std::find_if(registry.eval_datasets.begin(),
                       registry.eval_datasets.end(),
                       [](const aura::safety::SafetyAssetRef& ref) {
                           return ref.id == "local-eval" &&
                                  ref.source == "home";
                       }) != registry.eval_datasets.end());
    CHECK(std::find_if(registry.eval_datasets.begin(),
                       registry.eval_datasets.end(),
                       [](const aura::safety::SafetyAssetRef& ref) {
                           return ref.id == "repo-eval" &&
                                  ref.source == "repo";
                       }) != registry.eval_datasets.end());
}

TEST_CASE("safety registry keeps invalid home asset over repo duplicate") {
    namespace fs = std::filesystem;
    const fs::path home =
        tempRoot("aura_safety_unit_invalid_home_asset");
    const fs::path assets =
        tempRoot("aura_safety_unit_invalid_repo_asset");
    fs::remove_all(home);
    fs::remove_all(assets);
    fs::create_directories(home / "rule-packs" / "duplicate-rules");
    fs::create_directories(assets / "rule-packs" / "duplicate-rules");

    {
        std::ofstream out(home / "rule-packs" / "duplicate-rules" /
                              "manifest.json",
                          std::ios::binary);
        out << "{";
    }
    {
        std::ofstream out(assets / "rule-packs" / "duplicate-rules" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"duplicate-rules","display_name":"Repo Duplicate","rules_file":"rules.json"})";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto registry = aura::safety::listSafetyAssets();
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(registry.rule_packs.size() == 1);
    CHECK(registry.rule_packs[0].id == "duplicate-rules");
    CHECK(registry.rule_packs[0].source == "home");
    CHECK(!registry.rule_packs[0].valid);
    CHECK(!registry.rule_packs[0].diagnostic.empty());
}

TEST_CASE("safety registry keeps invalid home profile over repo duplicate") {
    namespace fs = std::filesystem;
    const fs::path home =
        tempRoot("aura_safety_unit_invalid_home_profile");
    const fs::path assets =
        tempRoot("aura_safety_unit_invalid_repo_profile");
    fs::remove_all(home);
    fs::remove_all(assets);
    fs::create_directories(home / "safety-profiles");
    fs::create_directories(assets / "safety-profiles");

    {
        std::ofstream out(home / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << "{";
    }
    {
        std::ofstream out(assets / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"default","rule_pack_ids":[]})";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto registry = aura::safety::listSafetyAssets();
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(registry.profiles.size() == 1);
    CHECK(registry.profiles[0].id == "default");
    CHECK(registry.profiles[0].source == "home");
    CHECK(!registry.profiles[0].valid);
    CHECK(!registry.profiles[0].diagnostic.empty());
}

TEST_CASE("partial home rule pack override keeps repo default packs") {
    namespace fs = std::filesystem;
    const fs::path home =
        tempRoot("aura_safety_unit_partial_home");
    const fs::path assets =
        tempRoot("aura_safety_unit_partial_assets");
    fs::remove_all(home);
    fs::remove_all(assets);
    fs::create_directories(home / "rule-packs" / "korean-sensitive");
    fs::create_directories(home / "safety-profiles");
    fs::create_directories(assets / "rule-packs" / "secret-api-key");

    {
        std::ofstream out(home / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "default",
          "rule_pack_ids": ["korean-sensitive", "secret-api-key"]
        })";
    }
    {
        std::ofstream out(home / "rule-packs" / "korean-sensitive" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"korean-sensitive","rules_file":"rules.json"})";
    }
    {
        std::ofstream out(home / "rule-packs" / "korean-sensitive" /
                              "rules.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "rules": [
            {
              "id": "home/customer-id",
              "kind": "customer_id",
              "pattern": "CUST-[0-9]{4}",
              "confidence": 0.91
            }
          ]
        })";
    }
    {
        std::ofstream out(assets / "rule-packs" / "secret-api-key" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"secret-api-key","rules_file":"rules.json"})";
    }
    {
        std::ofstream out(assets / "rule-packs" / "secret-api-key" /
                              "rules.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "rules": [
            {
              "id": "repo/api-key",
              "kind": "api_key",
              "pattern": "api_key[=:][A-Za-z0-9]{8,}",
              "confidence": 0.90
            }
          ]
        })";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto profile = aura::safety::loadDefaultSafetyProfile();
    const auto customer =
        aura::safety::scanStringWithRulePacks("ticket CUST-1234", profile);
    const auto secret =
        aura::safety::scanStringWithRulePacks("api_key=abc12345", profile);
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(customer.size() == 1);
    CHECK(customer[0].detector_id == "home/customer-id");
    REQUIRE(secret.size() == 1);
    CHECK(secret[0].detector_id == "repo/api-key");
}

TEST_CASE("rule pack scan avoids obvious reverse-engineering noise") {
    const aura::safety::SafetyProfile profile =
        aura::safety::loadDefaultSafetyProfile();

    CHECK(aura::safety::scanStringWithRulePacks("fcn.140001070", profile)
              .empty());
    CHECK(aura::safety::scanStringWithRulePacks("0x140001070", profile)
              .empty());
    CHECK(aura::safety::scanStringWithRulePacks("mov eax, dword [rbp - 4]",
                                                profile)
              .empty());
    CHECK(aura::safety::scanStringWithRulePacks("push 140001070", profile)
              .empty());
}

TEST_CASE("finding merger keeps the strongest overlapping span") {
    std::vector<aura::safety::Finding> findings;
    aura::safety::Finding shortOne;
    shortOne.detector_id = "short";
    shortOne.kind = "token";
    shortOne.start = 4;
    shortOne.end = 10;
    shortOne.confidence = 0.99;
    findings.push_back(shortOne);

    aura::safety::Finding longOne;
    longOne.detector_id = "long";
    longOne.kind = "api_key";
    longOne.start = 0;
    longOne.end = 16;
    longOne.confidence = 0.80;
    findings.push_back(longOne);

    auto merged = aura::safety::mergeFindings(std::move(findings));
    REQUIRE(merged.size() == 1);
    CHECK(merged[0].detector_id == "long");
    CHECK(merged[0].start == 0);
    CHECK(merged[0].end == 16);
}

TEST_CASE("protected string view masks findings and preserves alias priority") {
    aura::safety::Finding f;
    f.detector_id = "builtin/email";
    f.kind = "email";
    f.start = 0;
    f.end = 23;
    f.confidence = 0.98;

    auto view = aura::safety::buildProtectedStringView(
        "alice.smith@example.com", "customer_email", {f});
    REQUIRE(view.findings.size() == 1);
    CHECK(view.findings[0].mask_token == "[EMAIL_1]");
    CHECK(view.masked == "[EMAIL_1]");
    CHECK(view.protected_value == "customer_email");
}

TEST_CASE("protected string view reuses mask token for the same source value") {
    const std::string original =
        "first alice.smith@example.com second alice.smith@example.com";
    aura::safety::Finding a;
    a.detector_id = "builtin/email";
    a.kind = "email";
    a.start = 6;
    a.end = 29;
    a.confidence = 0.98;

    aura::safety::Finding b = a;
    b.start = 37;
    b.end = 60;

    auto view = aura::safety::buildProtectedStringView(original, "", {a, b});
    REQUIRE(view.findings.size() == 2);
    CHECK(view.findings[0].mask_token == "[EMAIL_1]");
    CHECK(view.findings[1].mask_token == "[EMAIL_1]");
    CHECK(view.masked == "first [EMAIL_1] second [EMAIL_1]");
}
