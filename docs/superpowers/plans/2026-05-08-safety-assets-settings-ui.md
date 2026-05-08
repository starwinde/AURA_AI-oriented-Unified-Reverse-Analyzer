# Safety Assets Settings UI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a GUI-accessible Safety Assets Settings flow so users can choose the active PII safety profile, inspect/change model, rule pack, and eval dataset selections, and have string protection use the selected profile.

**Architecture:** Put asset discovery and profile resolution in the core safety module, not in GUI code. The GUI adds a focused settings dialog that persists the selected profile id in `QSettings`, while `MainWindow` resolves the active profile through the shared core API before scanning strings. Eval datasets are shown under an Evaluation grouping and persisted as profile configuration, but they do not directly affect live masking.

**Tech Stack:** C++17, Qt6 Widgets, `QSettings`, CMake/CTest, doctest, existing `aura::safety` module, existing `gui_smoke` offscreen Qt test.

---

## File Structure

- Modify: `include/aura/safety/string_safety.h`
  - Add registry-facing structs and profile loading/validation APIs.
- Modify: `src/core/safety/string_safety.cpp`
  - Implement safety asset listing, profile-by-id loading, and selected-profile fallback logic.
- Modify: `tests/unit/safety/safety_unit.cpp`
  - Add fast unit tests for registry listing, profile-by-id loading, validation, and fallback behavior.
- Create: `src/gui/safety_settings_dialog.h`
  - Qt dialog declaration for profile/model/rule/eval selection.
- Create: `src/gui/safety_settings_dialog.cpp`
  - Qt dialog implementation, asset list rendering, validation/status messaging.
- Modify: `src/gui/CMakeLists.txt`
  - Build the new dialog into `aura-gui`.
- Modify: `tests/integration/gui_smoke/CMakeLists.txt`
  - Build the new dialog into `gui_smoke`.
- Modify: `src/gui/main_window.h`
  - Add selected safety profile helpers and a test-visible status accessor.
- Modify: `src/gui/main_window.cpp`
  - Add Settings menu action, persist selected profile id, resolve active profile before string scanning, and expose compact status text.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add offscreen smoke tests for settings action, profile persistence, and active profile status.
- Modify: `README.md`
  - Document Safety Assets Settings, profile/model/rule/eval distinction, and `~/.aura` override path.

---

### Task 1: Add Core Safety Asset Registry API

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Add failing unit tests for asset listing**

Append this test to `tests/unit/safety/safety_unit.cpp`:

```cpp
TEST_CASE("safety registry lists profiles, models, rule packs, and eval datasets") {
    namespace fs = std::filesystem;
    const fs::path home =
        fs::temp_directory_path() / "aura_safety_unit_asset_registry_home";
    const fs::path assets =
        fs::temp_directory_path() / "aura_safety_unit_asset_registry_assets";
    fs::remove_all(home);
    fs::remove_all(assets);

    fs::create_directories(home / "safety-profiles");
    fs::create_directories(home / "token-classification-models" / "local-model");
    fs::create_directories(home / "rule-packs" / "local-rules");
    fs::create_directories(home / "eval-datasets" / "local-eval");
    fs::create_directories(assets / "safety-profiles");
    fs::create_directories(assets / "rule-packs" / "repo-rules");

    {
        std::ofstream out(home / "safety-profiles" / "custom.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"custom","rule_pack_ids":["local-rules"],"eval_dataset_ids":["local-eval"],"model_policy":{"enabled":true,"mode":"conditional","model_id":"local-model"}})";
    }
    {
        std::ofstream out(home / "token-classification-models" / "local-model" /
                              "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"model_id":"local-model","display_name":"Local Model"})";
    }
    {
        std::ofstream out(home / "rule-packs" / "local-rules" / "manifest.json",
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
        std::ofstream out(assets / "rule-packs" / "repo-rules" / "manifest.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"pack_id":"repo-rules","display_name":"Repo Rules","rules_file":"rules.json"})";
    }

    setEnvVar("AURA_HOME", home.string());
    setEnvVar("AURA_SAFETY_ASSETS_DIR", assets.string());
    const auto registry = aura::safety::listSafetyAssets();
    clearEnvVar("AURA_SAFETY_ASSETS_DIR");
    clearEnvVar("AURA_HOME");

    REQUIRE(registry.profiles.size() == 1);
    CHECK(registry.profiles[0].id == "custom");
    CHECK(registry.profiles[0].source == "home");
    REQUIRE(registry.models.size() == 1);
    CHECK(registry.models[0].id == "local-model");
    REQUIRE(registry.rule_packs.size() == 2);
    CHECK(registry.eval_datasets.size() == 1);
    CHECK(registry.eval_datasets[0].id == "local-eval");
}
```

- [ ] **Step 2: Run the test and verify it fails**

Run:

```powershell
cmake --build build-trim-gui --target safety_unit --config Release
ctest --test-dir build-trim-gui -C Release -R "safety_unit" --output-on-failure
```

Expected: build fails because `aura::safety::listSafetyAssets()` and registry structs are not declared.

- [ ] **Step 3: Add registry declarations**

Add these declarations to `include/aura/safety/string_safety.h` after `struct SafetyProfile`:

```cpp
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

SafetyAssetRegistry listSafetyAssets();
```

- [ ] **Step 4: Implement manifest-id helpers and registry listing**

In `src/core/safety/string_safety.cpp`, add these helper functions inside the anonymous namespace after `readFile`:

```cpp
std::string firstNonEmpty(std::initializer_list<std::string> values) {
    for (const auto& value : values) {
        if (!value.empty()) return value;
    }
    return {};
}

SafetyAssetRef refFromJsonFile(const std::filesystem::path& path,
                               const std::string& source,
                               std::initializer_list<const char*> idKeys) {
    SafetyAssetRef ref;
    ref.path = path.string();
    ref.source = source;
    const std::string text = readFile(path);
    if (text.empty()) {
        ref.valid = false;
        ref.diagnostic = "manifest is empty or unreadable";
        ref.id = path.parent_path().filename().string();
        return ref;
    }
    cJSON* root = cJSON_ParseWithLength(text.data(), text.size());
    if (!root) {
        ref.valid = false;
        ref.diagnostic = "manifest is not valid JSON";
        ref.id = path.parent_path().filename().string();
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
        ref.id = path.parent_path().filename().string();
    }
    return ref;
}

void appendUniqueAsset(std::vector<SafetyAssetRef>& out, SafetyAssetRef ref) {
    const auto sameId = [&](const SafetyAssetRef& existing) {
        return existing.id == ref.id;
    };
    if (std::find_if(out.begin(), out.end(), sameId) == out.end())
        out.push_back(std::move(ref));
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
        if (!ent.is_directory()) continue;
        const auto manifestPath = ent.path() / manifestName;
        if (!std::filesystem::exists(manifestPath, ec)) continue;
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
        if (!ent.is_regular_file() || ent.path().extension() != ".json")
            continue;
        appendUniqueAsset(*out,
                          refFromJsonFile(ent.path(), source, {"profile_id"}));
    }
}
```

Add this public function before `loadDefaultSafetyProfile()`:

```cpp
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
```

- [ ] **Step 5: Build and run safety tests**

Run:

```powershell
cmake --build build-trim-gui --target safety_unit --config Release
ctest --test-dir build-trim-gui -C Release -R "safety_unit" --output-on-failure
```

Expected: `safety_unit` passes.

- [ ] **Step 6: Commit**

```powershell
git add include/aura/safety/string_safety.h src/core/safety/string_safety.cpp tests/unit/safety/safety_unit.cpp
git commit -m "feat: add safety asset registry"
```

---

### Task 2: Add Profile Loading and Validation APIs

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Add failing tests for profile-by-id and validation**

Append these tests to `tests/unit/safety/safety_unit.cpp`:

```cpp
TEST_CASE("safety profile can be loaded by id from AURA_HOME") {
    namespace fs = std::filesystem;
    const fs::path root =
        fs::temp_directory_path() / "aura_safety_unit_profile_by_id_home";
    fs::remove_all(root);
    fs::create_directories(root / "safety-profiles");

    {
        std::ofstream out(root / "safety-profiles" / "high-security.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "high-security",
          "rule_pack_ids": ["secret-api-key"],
          "eval_dataset_ids": ["safety-default"],
          "model_policy": {
            "enabled": true,
            "mode": "required",
            "model_id": "openai-privacy-filter",
            "on_missing": "block_export"
          }
        })";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto loaded = aura::safety::loadSafetyProfileById("high-security");
    clearEnvVar("AURA_HOME");

    REQUIRE(loaded.found);
    CHECK(loaded.profile_id == "high-security");
    CHECK(loaded.profile.rule_pack_ids.size() == 1);
    CHECK(loaded.profile.model_policy.mode ==
          aura::safety::ModelPolicyMode::Required);
}

TEST_CASE("selected safety profile falls back to default when missing") {
    namespace fs = std::filesystem;
    const fs::path root =
        fs::temp_directory_path() / "aura_safety_unit_selected_missing_home";
    fs::remove_all(root);
    fs::create_directories(root / "safety-profiles");

    {
        std::ofstream out(root / "safety-profiles" / "default.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"default","rule_pack_ids":["korean-sensitive"]})";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto selected =
        aura::safety::resolveSelectedSafetyProfile("deleted-profile");
    clearEnvVar("AURA_HOME");

    CHECK(selected.profile_id == "default");
    CHECK(selected.used_fallback);
    CHECK(selected.found);
}

TEST_CASE("profile validation reports missing referenced assets") {
    namespace fs = std::filesystem;
    const fs::path root =
        fs::temp_directory_path() / "aura_safety_unit_validation_home";
    fs::remove_all(root);
    fs::create_directories(root / "safety-profiles");

    {
        std::ofstream out(root / "safety-profiles" / "broken.json",
                          std::ios::binary);
        out << R"({
          "schema_version": 1,
          "profile_id": "broken",
          "rule_pack_ids": ["missing-rules"],
          "eval_dataset_ids": ["missing-eval"],
          "model_policy": {"enabled": true, "model_id": "missing-model"}
        })";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto loaded = aura::safety::loadSafetyProfileById("broken");
    const auto validation = aura::safety::validateSafetyProfile(loaded.profile);
    clearEnvVar("AURA_HOME");

    CHECK_FALSE(validation.valid);
    REQUIRE(validation.messages.size() == 3);
    CHECK(validation.messages[0].find("missing-rules") != std::string::npos);
    CHECK(validation.messages[1].find("missing-eval") != std::string::npos);
    CHECK(validation.messages[2].find("missing-model") != std::string::npos);
}
```

- [ ] **Step 2: Run tests and verify they fail**

Run:

```powershell
cmake --build build-trim-gui --target safety_unit --config Release
```

Expected: build fails because `loadSafetyProfileById`, `resolveSelectedSafetyProfile`, and `validateSafetyProfile` do not exist.

- [ ] **Step 3: Add profile result declarations**

Add these declarations to `include/aura/safety/string_safety.h` after `SafetyAssetRegistry`:

```cpp
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

SafetyProfileLoadResult loadSafetyProfileById(const std::string& profile_id);
SafetyProfileLoadResult resolveSelectedSafetyProfile(
    const std::string& selected_profile_id);
SafetyProfileValidation validateSafetyProfile(const SafetyProfile& profile);
```

- [ ] **Step 4: Extract profile parsing helper**

In `src/core/safety/string_safety.cpp`, replace the body of `loadDefaultSafetyProfile()` with a call to a new helper. Add this helper in the anonymous namespace before `}  // namespace`:

```cpp
SafetyProfile parseSafetyProfileText(const std::string& text) {
    SafetyProfile out;
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
```

Then make `loadDefaultSafetyProfile()`:

```cpp
SafetyProfile loadDefaultSafetyProfile() {
    auto loaded = loadSafetyProfileById("default");
    return loaded.profile;
}
```

- [ ] **Step 5: Implement profile loading by id and fallback**

Add these functions before `loadDefaultSafetyProfile()`:

```cpp
SafetyProfileLoadResult loadSafetyProfileById(const std::string& profile_id) {
    SafetyProfileLoadResult result;
    result.profile_id = profile_id;
    if (profile_id.empty()) {
        result.diagnostic = "profile id is empty";
        return result;
    }

    const std::vector<std::filesystem::path> candidates = {
        auraHome() / "safety-profiles" / (profile_id + ".json"),
        safetyAssetsRoot() / "safety-profiles" / (profile_id + ".json"),
    };
    for (const auto& path : candidates) {
        const std::string text = readFile(path);
        if (text.empty()) continue;
        result.found = true;
        result.path = path.string();
        result.profile = parseSafetyProfileText(text);
        return result;
    }

    result.diagnostic = "safety profile not found";
    return result;
}

SafetyProfileLoadResult resolveSelectedSafetyProfile(
    const std::string& selected_profile_id) {
    if (!selected_profile_id.empty()) {
        auto selected = loadSafetyProfileById(selected_profile_id);
        if (selected.found) return selected;
    }

    auto fallback = loadSafetyProfileById("default");
    fallback.used_fallback = selected_profile_id != "default";
    return fallback;
}
```

- [ ] **Step 6: Implement validation**

Add this function after `resolveSelectedSafetyProfile()`:

```cpp
SafetyProfileValidation validateSafetyProfile(const SafetyProfile& profile) {
    SafetyProfileValidation out;
    const auto registry = listSafetyAssets();

    auto has = [](const std::vector<SafetyAssetRef>& refs,
                  const std::string& id) {
        return std::find_if(refs.begin(), refs.end(), [&](const auto& ref) {
            return ref.id == id && ref.valid;
        }) != refs.end();
    };
    auto missing = [&](const std::string& kind, const std::string& id) {
        out.valid = false;
        out.messages.push_back(kind + " not found: " + id);
    };

    for (const auto& id : profile.rule_pack_ids) {
        if (!has(registry.rule_packs, id)) missing("rule pack", id);
    }
    for (const auto& id : profile.eval_dataset_ids) {
        if (!has(registry.eval_datasets, id)) missing("eval dataset", id);
    }
    if (profile.model_policy.enabled && !profile.model_policy.model_id.empty() &&
        !has(registry.models, profile.model_policy.model_id)) {
        missing("token classification model", profile.model_policy.model_id);
    }
    return out;
}
```

- [ ] **Step 7: Run safety tests**

Run:

```powershell
cmake --build build-trim-gui --target safety_unit --config Release
ctest --test-dir build-trim-gui -C Release -R "safety_unit" --output-on-failure
```

Expected: `safety_unit` passes.

- [ ] **Step 8: Commit**

```powershell
git add include/aura/safety/string_safety.h src/core/safety/string_safety.cpp tests/unit/safety/safety_unit.cpp
git commit -m "feat: resolve selected safety profiles"
```

---

### Task 3: Add Safety Settings Dialog

**Files:**
- Create: `src/gui/safety_settings_dialog.h`
- Create: `src/gui/safety_settings_dialog.cpp`
- Modify: `src/gui/CMakeLists.txt`
- Modify: `tests/integration/gui_smoke/CMakeLists.txt`

- [ ] **Step 1: Create dialog header**

Create `src/gui/safety_settings_dialog.h`:

```cpp
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <QDialog>
#include <QString>

#include "aura/safety/string_safety.h"

class QComboBox;
class QLabel;
class QListWidget;

namespace aura::gui {

class SafetySettingsDialog final : public QDialog {
    Q_OBJECT

public:
    explicit SafetySettingsDialog(const QString& selectedProfileId,
                                  QWidget* parent = nullptr);

    QString selectedProfileId() const;
    QString statusText() const;

private:
    void populate();
    void updateSummary();
    void addAssetRows(QListWidget* list,
                      const std::vector<aura::safety::SafetyAssetRef>& refs,
                      const std::vector<std::string>& selectedIds,
                      bool enabled);

    aura::safety::SafetyAssetRegistry m_registry;
    QString m_initialProfileId;
    QComboBox* m_profileCombo = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QLabel* m_statusLabel = nullptr;
    QListWidget* m_modelList = nullptr;
    QListWidget* m_rulePackList = nullptr;
    QListWidget* m_evalDatasetList = nullptr;
};

}  // namespace aura::gui
```

- [ ] **Step 2: Create dialog implementation**

Create `src/gui/safety_settings_dialog.cpp`:

```cpp
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "safety_settings_dialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

namespace aura::gui {

namespace {

bool containsId(const std::vector<std::string>& ids, const std::string& id) {
    return std::find(ids.begin(), ids.end(), id) != ids.end();
}

QString assetLabel(const aura::safety::SafetyAssetRef& ref) {
    const QString name = QString::fromStdString(
        ref.display_name.empty() ? ref.id : ref.display_name);
    const QString id = QString::fromStdString(ref.id);
    const QString source = QString::fromStdString(ref.source);
    return QStringLiteral("%1 (%2, %3)").arg(name, id, source);
}

}  // namespace

SafetySettingsDialog::SafetySettingsDialog(const QString& selectedProfileId,
                                           QWidget* parent)
    : QDialog(parent),
      m_registry(aura::safety::listSafetyAssets()),
      m_initialProfileId(selectedProfileId) {
    setWindowTitle(QStringLiteral("Safety Assets"));
    setObjectName(QStringLiteral("safetySettingsDialog"));
    resize(560, 620);

    auto* root = new QVBoxLayout(this);

    auto* profileGroup = new QGroupBox(QStringLiteral("Profile"), this);
    auto* profileLayout = new QFormLayout(profileGroup);
    m_profileCombo = new QComboBox(profileGroup);
    m_profileCombo->setObjectName(QStringLiteral("safetyProfileCombo"));
    profileLayout->addRow(QStringLiteral("Active profile"), m_profileCombo);
    m_summaryLabel = new QLabel(profileGroup);
    m_summaryLabel->setObjectName(QStringLiteral("safetySummaryLabel"));
    m_summaryLabel->setWordWrap(true);
    profileLayout->addRow(QStringLiteral("Summary"), m_summaryLabel);
    root->addWidget(profileGroup);

    auto* detectionGroup = new QGroupBox(QStringLiteral("Detection"), this);
    auto* detectionLayout = new QVBoxLayout(detectionGroup);
    m_modelList = new QListWidget(detectionGroup);
    m_modelList->setObjectName(QStringLiteral("safetyModelList"));
    m_rulePackList = new QListWidget(detectionGroup);
    m_rulePackList->setObjectName(QStringLiteral("safetyRulePackList"));
    detectionLayout->addWidget(new QLabel(QStringLiteral("Token classification model"), detectionGroup));
    detectionLayout->addWidget(m_modelList);
    detectionLayout->addWidget(new QLabel(QStringLiteral("Rule packs"), detectionGroup));
    detectionLayout->addWidget(m_rulePackList);
    root->addWidget(detectionGroup);

    auto* evalGroup = new QGroupBox(QStringLiteral("Evaluation"), this);
    auto* evalLayout = new QVBoxLayout(evalGroup);
    m_evalDatasetList = new QListWidget(evalGroup);
    m_evalDatasetList->setObjectName(QStringLiteral("safetyEvalDatasetList"));
    evalLayout->addWidget(m_evalDatasetList);
    root->addWidget(evalGroup);

    m_statusLabel = new QLabel(this);
    m_statusLabel->setObjectName(QStringLiteral("safetyStatusLabel"));
    m_statusLabel->setWordWrap(true);
    root->addWidget(m_statusLabel);

    auto* buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    root->addWidget(buttons);

    populate();
    connect(m_profileCombo, &QComboBox::currentTextChanged,
            this, &SafetySettingsDialog::updateSummary);
    updateSummary();
}

QString SafetySettingsDialog::selectedProfileId() const {
    return m_profileCombo
        ? m_profileCombo->currentData().toString()
        : QStringLiteral("default");
}

QString SafetySettingsDialog::statusText() const {
    return m_statusLabel ? m_statusLabel->text() : QString();
}

void SafetySettingsDialog::populate() {
    m_profileCombo->clear();
    int selectedIndex = -1;
    for (const auto& profile : m_registry.profiles) {
        const QString id = QString::fromStdString(profile.id);
        m_profileCombo->addItem(assetLabel(profile), id);
        if (id == m_initialProfileId) selectedIndex = m_profileCombo->count() - 1;
    }
    if (selectedIndex < 0) {
        selectedIndex = m_profileCombo->findData(QStringLiteral("default"));
    }
    if (selectedIndex >= 0) m_profileCombo->setCurrentIndex(selectedIndex);
}

void SafetySettingsDialog::addAssetRows(
    QListWidget* list,
    const std::vector<aura::safety::SafetyAssetRef>& refs,
    const std::vector<std::string>& selectedIds,
    bool enabled) {
    list->clear();
    for (const auto& ref : refs) {
        auto* item = new QListWidgetItem(assetLabel(ref), list);
        item->setFlags(Qt::ItemIsEnabled);
        item->setCheckState(containsId(selectedIds, ref.id)
                                ? Qt::Checked
                                : Qt::Unchecked);
        if (!enabled) item->setFlags(Qt::NoItemFlags);
    }
}

void SafetySettingsDialog::updateSummary() {
    const std::string id = selectedProfileId().toStdString();
    const auto loaded = aura::safety::resolveSelectedSafetyProfile(id);
    const auto validation =
        aura::safety::validateSafetyProfile(loaded.profile);

    addAssetRows(m_modelList, m_registry.models,
                 {loaded.profile.model_policy.model_id}, false);
    addAssetRows(m_rulePackList, m_registry.rule_packs,
                 loaded.profile.rule_pack_ids, false);
    addAssetRows(m_evalDatasetList, m_registry.eval_datasets,
                 loaded.profile.eval_dataset_ids, false);

    m_summaryLabel->setText(QStringLiteral("Model: %1\nRule packs: %2\nEval datasets: %3")
        .arg(QString::fromStdString(loaded.profile.model_policy.model_id))
        .arg(loaded.profile.rule_pack_ids.size())
        .arg(loaded.profile.eval_dataset_ids.size()));

    if (!loaded.found) {
        m_statusLabel->setText(QStringLiteral("Selected profile was not found. Default profile will be used."));
        return;
    }
    if (!validation.valid) {
        m_statusLabel->setText(QStringLiteral("Profile has missing assets: %1")
            .arg(QString::fromStdString(validation.messages.front())));
        return;
    }
    m_statusLabel->setText(QStringLiteral("Profile is ready."));
}

}  // namespace aura::gui
```

- [ ] **Step 3: Add files to GUI CMake**

In `src/gui/CMakeLists.txt`, add:

```cmake
    safety_settings_dialog.cpp
```

to `AURA_GUI_SOURCES`, and add:

```cmake
    safety_settings_dialog.h
```

to `AURA_GUI_HEADERS`.

In `tests/integration/gui_smoke/CMakeLists.txt`, add these to `target_sources(gui_smoke PRIVATE ...)`:

```cmake
    ${CMAKE_SOURCE_DIR}/src/gui/safety_settings_dialog.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/safety_settings_dialog.h
```

- [ ] **Step 4: Build GUI targets**

Run:

```powershell
cmake --build build-trim-gui --target aura-gui gui_smoke --config Release
```

Expected: both targets build.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp src/gui/CMakeLists.txt tests/integration/gui_smoke/CMakeLists.txt
git commit -m "feat: add safety assets settings dialog"
```

---

### Task 4: Wire MainWindow to Selected Safety Profile

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke test for selected profile status**

Append this subcase inside `TEST_CASE("gui_smoke: project-first flow → function list (FULL)")` in `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
    SUBCASE("safety settings profile selection persists through QSettings") {
        QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
        s.remove(QStringLiteral("safety/activeProfileId"));

        aura::gui::MainWindow first;
        CHECK(first.activeSafetyProfileIdForTest() == QStringLiteral("default"));
        CHECK(first.openSafetySettingsForTest(QStringLiteral("high-security")));
        CHECK(first.activeSafetyProfileIdForTest() == QStringLiteral("high-security"));
        CHECK(first.safetyStatusTextForTest().contains(QStringLiteral("high-security")));

        aura::gui::MainWindow second;
        CHECK(second.activeSafetyProfileIdForTest() == QStringLiteral("high-security"));

        s.remove(QStringLiteral("safety/activeProfileId"));
    }
```

- [ ] **Step 2: Run gui smoke build and verify it fails**

Run:

```powershell
cmake --build build-trim-gui --target gui_smoke --config Release
```

Expected: build fails because `activeSafetyProfileIdForTest`, `openSafetySettingsForTest`, and `safetyStatusTextForTest` do not exist.

- [ ] **Step 3: Add MainWindow declarations**

In `src/gui/main_window.h`, add these public methods near other test-visible helpers:

```cpp
QString activeSafetyProfileIdForTest() const;
QString safetyStatusTextForTest() const;
bool openSafetySettingsForTest(const QString& profileId);
```

Add these private declarations near other private helper methods:

```cpp
QString activeSafetyProfileId() const;
aura::safety::SafetyProfile activeSafetyProfile() const;
void setActiveSafetyProfileId(const QString& profileId);
void updateSafetyStatusText();
void onSafetySettings();
```

Add this private member near existing GUI state members:

```cpp
QString m_safetyStatusText;
```

- [ ] **Step 4: Include dialog and add settings key**

In `src/gui/main_window.cpp`, add:

```cpp
#include "safety_settings_dialog.h"
```

Near existing settings keys, add:

```cpp
constexpr const char* kKeySafetyActiveProfile = "safety/activeProfileId";
```

- [ ] **Step 5: Implement profile helpers**

Add these methods to `src/gui/main_window.cpp` near other `QSettings` helpers:

```cpp
QString MainWindow::activeSafetyProfileId() const {
    QSettings s(QString::fromUtf8(kSettingsOrg),
                QString::fromUtf8(kSettingsApp));
    return s.value(QString::fromUtf8(kKeySafetyActiveProfile),
                   QStringLiteral("default")).toString();
}

aura::safety::SafetyProfile MainWindow::activeSafetyProfile() const {
    const auto selected =
        aura::safety::resolveSelectedSafetyProfile(
            activeSafetyProfileId().toStdString());
    return selected.profile;
}

void MainWindow::setActiveSafetyProfileId(const QString& profileId) {
    QSettings s(QString::fromUtf8(kSettingsOrg),
                QString::fromUtf8(kSettingsApp));
    s.setValue(QString::fromUtf8(kKeySafetyActiveProfile),
               profileId.isEmpty() ? QStringLiteral("default") : profileId);
    updateSafetyStatusText();
}

void MainWindow::updateSafetyStatusText() {
    const QString id = activeSafetyProfileId();
    const auto selected =
        aura::safety::resolveSelectedSafetyProfile(id.toStdString());
    const auto validation =
        aura::safety::validateSafetyProfile(selected.profile);

    if (!selected.found) {
        m_safetyStatusText = QStringLiteral("Safety: default (selected profile missing)");
    } else if (!validation.valid) {
        m_safetyStatusText = QStringLiteral("Safety: %1 (missing assets)")
            .arg(QString::fromStdString(selected.profile_id));
    } else {
        m_safetyStatusText = QStringLiteral("Safety: %1")
            .arg(QString::fromStdString(selected.profile_id));
    }
    statusBar()->showMessage(m_safetyStatusText, 4000);
}

QString MainWindow::activeSafetyProfileIdForTest() const {
    return activeSafetyProfileId();
}

QString MainWindow::safetyStatusTextForTest() const {
    return m_safetyStatusText;
}

bool MainWindow::openSafetySettingsForTest(const QString& profileId) {
    setActiveSafetyProfileId(profileId);
    return activeSafetyProfileId() == profileId;
}
```

- [ ] **Step 6: Add Settings menu action**

In `MainWindow::buildMenus()`, after the language menu setup, add:

```cpp
    settingsMenu->addSeparator();
    QAction* safetyAct = settingsMenu->addAction(
        ko ? QStringLiteral("안전 자산(&S)...")
           : QStringLiteral("&Safety Assets..."));
    safetyAct->setObjectName(QStringLiteral("safetySettingsAction"));
    connect(safetyAct, &QAction::triggered,
            this, &MainWindow::onSafetySettings);
```

Add this method:

```cpp
void MainWindow::onSafetySettings() {
    SafetySettingsDialog dlg(activeSafetyProfileId(), this);
    if (dlg.exec() != QDialog::Accepted) return;
    setActiveSafetyProfileId(dlg.selectedProfileId());
}
```

- [ ] **Step 7: Use selected profile during string scanning**

In `MainWindow::runAnalyze`, replace:

```cpp
const auto safetyProfile = aura::safety::loadDefaultSafetyProfile();
```

with:

```cpp
const auto safetyProfile = activeSafetyProfile();
updateSafetyStatusText();
```

- [ ] **Step 8: Build and run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --target gui_smoke --config Release
ctest --test-dir build-trim-gui -C Release -R "gui_smoke" --output-on-failure
```

Expected: `gui_smoke` passes.

- [ ] **Step 9: Commit**

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: wire GUI safety profile selection"
```

---

### Task 5: Show Active Safety Status in Strings Workflow

**Files:**
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing smoke assertion for Settings action**

Append this subcase inside the existing GUI smoke test:

```cpp
    SUBCASE("safety settings action is discoverable from Settings menu") {
        aura::gui::MainWindow window;
        QAction* action = window.findChild<QAction*>(
            QStringLiteral("safetySettingsAction"));
        REQUIRE(action != nullptr);
        CHECK(action->text().contains(QStringLiteral("Safety"),
                                      Qt::CaseInsensitive) ||
              action->text().contains(QStringLiteral("안전")));
        CHECK(window.safetyStatusTextForTest().contains(QStringLiteral("Safety")));
    }
```

- [ ] **Step 2: Initialize safety status in MainWindow constructor**

In `MainWindow::MainWindow`, after menus/status bar are built and before returning from the constructor, add:

```cpp
updateSafetyStatusText();
```

If the constructor currently has a clear end section near `restoreUiState()`, put the call immediately after `restoreUiState()`.

- [ ] **Step 3: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --target gui_smoke --config Release
ctest --test-dir build-trim-gui -C Release -R "gui_smoke" --output-on-failure
```

Expected: `gui_smoke` passes and the action is discoverable by object name.

- [ ] **Step 4: Commit**

```powershell
git add src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: show active safety profile status"
```

---

### Task 6: Documentation and Final Verification

**Files:**
- Modify: `README.md`
- Verify: `src/core/safety/string_safety.cpp`, `src/gui/main_window.cpp`, `src/gui/safety_settings_dialog.cpp`

- [ ] **Step 1: Add README documentation**

In `README.md`, after the existing `## Quick Install` section, add:

```markdown
## Safety Assets Settings

AURA stores privacy-filter runtime assets under `~/.aura` by default. The GUI
uses **Settings → Safety Assets** to choose the active safety profile.

The active safety profile controls:

- the token classification model used by the PII policy;
- the rule packs used for live string detection;
- the eval datasets used for evaluation and reports;
- the model policy, including whether missing model execution degrades or blocks.

Rule packs and the selected model affect live string protection. Eval datasets
are evaluation inputs; changing them does not directly change live masking.

Custom assets can be added under:

```text
~/.aura/
  safety-profiles/
  token-classification-models/
  rule-packs/
  eval-datasets/
```

Run the root installer again to refresh the default assets:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1
```

```bash
./install.sh
```
```

- [ ] **Step 2: Run focused verification**

Run:

```powershell
cmake --build build-trim-gui --target safety_unit gui_smoke aura-gui --config Release
ctest --test-dir build-trim-gui -C Release -R "safety_unit|gui_smoke" --output-on-failure
```

Expected: both tests pass.

- [ ] **Step 3: Run existing smoke tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|probe_engines_smoke" --output-on-failure
```

Expected: both tests pass.

- [ ] **Step 4: Run whitespace and shell checks**

Run:

```powershell
git diff --check
bash -n install.sh
bash -n scripts/fetch_external_tools.sh
```

Expected: no output except possible Git CRLF warnings from Windows checkout.

- [ ] **Step 5: Confirm no model downloads are required for tests**

Run:

```powershell
Select-String -Path tests\unit\safety\safety_unit.cpp,tests\integration\gui_smoke\gui_smoke.cpp -Pattern "snapshot_download","huggingface","model.safetensors"
```

Expected: no matches.

- [ ] **Step 6: Commit**

```powershell
git add README.md
git commit -m "docs: document safety assets settings"
```

---

## Self-Review Checklist

- [ ] Spec coverage: active profile selection, model/rule/eval display, selected profile persistence, runtime GUI use, settings UX, tests, docs.
- [ ] Domain correctness: eval datasets are evaluation inputs only and do not directly affect live string masking.
- [ ] Core boundary: asset discovery and profile validation live in `aura::safety`, not in GUI-only code.
- [ ] Test coverage: unit tests cover registry/profile validation; GUI smoke covers settings discovery and persistence.
- [ ] No model weights in Git and no test requires Hugging Face downloads.
- [ ] No placeholders: every task has exact files, code snippets, commands, and expected results.
