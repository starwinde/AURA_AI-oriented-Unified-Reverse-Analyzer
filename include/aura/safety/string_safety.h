// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace aura::safety {

enum class FindingSource {
    Rule,
    Model,
};

struct Finding {
    FindingSource source = FindingSource::Rule;
    std::string detector_id;
    std::string kind;
    std::size_t start = 0;
    std::size_t end = 0;
    double confidence = 0.0;
    std::string mask_token;
};

enum class ModelPolicyMode {
    Disabled,
    Conditional,
    Required,
};

enum class ModelFailureAction {
    Degrade,
    BlockExport,
};

enum class RulePackSelectionMode {
    All,
    Selected,
    None,
};

enum class StringProtectionMode {
    Off,
    ScanOnly,
    Mask,
};

struct ModelPolicy {
    bool enabled = false;
    ModelPolicyMode mode = ModelPolicyMode::Disabled;
    std::string model_id;
    std::size_t max_input_chars = 4096;
    int timeout_ms = 1500;
    std::vector<std::string> run_when;
    ModelFailureAction on_missing = ModelFailureAction::Degrade;
    ModelFailureAction on_timeout = ModelFailureAction::Degrade;
    ModelFailureAction on_error = ModelFailureAction::Degrade;
};

struct SafetyProfile {
    RulePackSelectionMode rule_pack_selection_mode =
        RulePackSelectionMode::All;
    std::vector<std::string> rule_pack_ids;
    std::vector<std::string> eval_dataset_ids;
    std::string token_classification_model_id;
    bool token_classification_enabled = false;
    ModelPolicy model_policy;
};

struct SafetyAssetRef {
    std::string id;
    std::string display_name;
    std::string path;
    std::string source;
    bool valid = true;
    std::string diagnostic;
};

struct SafetyAssetRegistry {
    std::vector<SafetyAssetRef> profiles;
    std::vector<SafetyAssetRef> models;
    std::vector<SafetyAssetRef> rule_packs;
    std::vector<SafetyAssetRef> eval_datasets;
};

struct SafetyProfileLoadResult {
    bool found = false;
    bool used_fallback = false;
    std::string profile_id;
    std::string path;
    std::string diagnostic;
    SafetyProfile profile;
};

struct SafetyProfileValidation {
    bool valid = true;
    std::vector<std::string> messages;
};

struct ProtectedStringView {
    std::string original;
    std::string alias;
    std::string masked;
    std::string protected_value;
    std::vector<Finding> findings;
};

class TokenClassificationModelAdapter {
public:
    virtual ~TokenClassificationModelAdapter() = default;
    virtual std::vector<Finding> scan(const std::string& text) = 0;
};

SafetyProfile loadDefaultSafetyProfile();
SafetyAssetRegistry listSafetyAssets();
SafetyProfileLoadResult loadSafetyProfileById(const std::string& profile_id);
SafetyProfileLoadResult resolveSelectedSafetyProfile(
    const std::string& selected_profile_id);
SafetyProfileValidation validateSafetyProfile(const SafetyProfile& profile);
bool saveSafetyProfile(const std::string& profile_id,
                      const SafetyProfile& profile,
                      std::string* diagnostic = nullptr);

std::string stringProtectionModeToText(StringProtectionMode mode);
StringProtectionMode parseStringProtectionMode(const std::string& text);

std::vector<Finding> scanStringWithRulePacks(const std::string& text,
                                             const SafetyProfile& profile);

std::vector<Finding> mergeFindings(std::vector<Finding> findings);
void allocateMaskTokens(std::vector<Finding>& findings);

ProtectedStringView buildProtectedStringView(
    const std::string& original,
    const std::string& alias,
    std::vector<Finding> findings);

}  // namespace aura::safety
