# Safety Assets Rule Pack Selection Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Localize the Safety Assets dialog for Korean UI mode and let users add/remove rule packs from the active safety profile.

**Architecture:** Keep `SafetySettingsDialog` as the single profile-editing surface. Model selection remains single-choice, rule pack selection becomes multi-choice, and eval datasets stay read-only because they are evaluation assets, not live masking rules.

**Tech Stack:** C++17, Qt Widgets, AURA safety profiles, GUI smoke tests, CMake/CTest.

---

## File Structure

- Modify: `src/gui/safety_settings_dialog.h`
  - Add rule-pack selection helpers.
- Modify: `src/gui/safety_settings_dialog.cpp`
  - Add Korean/English text helpers.
  - Make rule pack rows user-checkable.
  - Add rule-pack apply/remove buttons.
  - Apply selected rule pack ids into `editedProfile()`.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Extend existing Safety Settings dialog smoke coverage.
  - Verify Korean text, rule-pack editability, multi-selection, and profile-switch reset behavior.

---

## Current Behavior Notes

- `SafetySettingsDialog` currently hard-codes many English labels such as `Safety Assets`, `Profile`, `Active profile`, `Selection`, `Detection`, `Rule packs`, `Evaluation`, and `Profile is ready.`
- `m_modelList` rows are checkable and store the asset id in `Qt::UserRole`.
- `m_rulePackList` rows show checked/unchecked state but are not user-checkable.
- `editedProfile()` currently calls only `applyModelSelectionToProfile(profile)`, so rule-pack changes cannot be saved.
- `m_evalDatasetList` is display-only and should remain display-only in this slice.

---

### Task 1: Add Rule Pack Tests First

**Files:**
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Extend the existing SafetySettingsDialog test setup**

Find the subcase that constructs:

```cpp
aura::gui::SafetySettingsDialog dlg(QStringLiteral("default"));
```

In that same subcase, after `modelList` lookup, add:

```cpp
        auto* rulePackList =
            dlg.findChild<QListWidget*>(QStringLiteral("safetyRulePackList"));
        auto* ruleAddBtn = dlg.findChild<QPushButton*>(
            QStringLiteral("safetyRulePackAddButton"));
        auto* ruleRemoveBtn = dlg.findChild<QPushButton*>(
            QStringLiteral("safetyRulePackRemoveButton"));
```

After the existing `REQUIRE(rmBtn != nullptr);`, add:

```cpp
        REQUIRE(rulePackList != nullptr);
        REQUIRE(ruleAddBtn != nullptr);
        REQUIRE(ruleRemoveBtn != nullptr);
```

- [ ] **Step 2: Make the test profiles include distinct rule packs**

In the same test, replace:

```cpp
        defaultProfile.rule_pack_ids = {};
```

with:

```cpp
        defaultProfile.rule_pack_ids = {"rule-alpha"};
```

Replace:

```cpp
        highSecurityProfile.rule_pack_ids = {};
```

with:

```cpp
        highSecurityProfile.rule_pack_ids = {"rule-beta"};
```

This makes profile-switch reset behavior observable.

- [ ] **Step 3: Add helper functions inside the subcase**

Below the existing `requireCheckedModel` helper, add:

```cpp
        auto checkedRulePackIds = [](const QListWidget* list) {
            QStringList ids;
            if (!list) return ids;
            for (int i = 0; i < list->count(); ++i) {
                const auto* item = list->item(i);
                if (!item || item->checkState() != Qt::Checked) continue;
                ids.push_back(item->data(Qt::UserRole).toString());
            }
            ids.sort();
            return ids;
        };

        auto setCheckedRulePackId = [](QListWidget* list,
                                       const QString& id,
                                       Qt::CheckState state) {
            REQUIRE(list != nullptr);
            for (int i = 0; i < list->count(); ++i) {
                auto* item = list->item(i);
                REQUIRE(item != nullptr);
                if (item->data(Qt::UserRole).toString() == id) {
                    item->setCheckState(state);
                    QApplication::processEvents();
                    return;
                }
            }
            FAIL(QStringLiteral("rule pack id not found: %1").arg(id).toStdString());
        };

        auto requireCheckedRulePacks = [&](const QStringList& expected) {
            QStringList sortedExpected = expected;
            sortedExpected.sort();
            CHECK(checkedRulePackIds(rulePackList) == sortedExpected);
        };
```

- [ ] **Step 4: Add assertions for rule-pack editability and persistence in editedProfile**

After the existing model reset assertions, add:

```cpp
        CHECK(ruleAddBtn->text().contains(QStringLiteral("선택")));
        CHECK(ruleRemoveBtn->text().contains(QStringLiteral("해제")));

        switchProfile(QStringLiteral("default"));
        requireCheckedRulePacks({QStringLiteral("rule-alpha")});

        setCheckedRulePackId(rulePackList, QStringLiteral("rule-beta"),
                             Qt::Checked);
        auto edited = dlg.editedProfile();
        QStringList editedRules;
        for (const auto& id : edited.rule_pack_ids) {
            editedRules.push_back(QString::fromStdString(id));
        }
        editedRules.sort();
        CHECK(editedRules == QStringList({QStringLiteral("rule-alpha"),
                                          QStringLiteral("rule-beta")}));

        setCheckedRulePackId(rulePackList, QStringLiteral("rule-alpha"),
                             Qt::Unchecked);
        edited = dlg.editedProfile();
        editedRules.clear();
        for (const auto& id : edited.rule_pack_ids) {
            editedRules.push_back(QString::fromStdString(id));
        }
        editedRules.sort();
        CHECK(editedRules == QStringList({QStringLiteral("rule-beta")}));

        switchProfile(QStringLiteral("high-security"));
        requireCheckedRulePacks({QStringLiteral("rule-beta")});

        setCheckedRulePackId(rulePackList, QStringLiteral("rule-alpha"),
                             Qt::Checked);
        switchProfile(QStringLiteral("default"));
        requireCheckedRulePacks({QStringLiteral("rule-alpha")});
```

- [ ] **Step 5: Run the focused build and expect failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build fails because `safetyRulePackAddButton` and `safetyRulePackRemoveButton` do not exist yet, or because rule pack rows do not expose ids/checkability yet. If it passes before implementation, inspect whether the assertions are actually compiled into the existing subcase.

---

### Task 2: Add Rule Pack Selection API

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`

- [ ] **Step 1: Update the header**

In `src/gui/safety_settings_dialog.h`, after:

```cpp
    void applyModelSelectionToProfile(
        aura::safety::SafetyProfile& profile) const;
    std::vector<std::string> selectedModelIds() const;
    void updateModelSelectionFromChecked();
```

change it to:

```cpp
    void applyModelSelectionToProfile(
        aura::safety::SafetyProfile& profile) const;
    void applyRulePackSelectionToProfile(
        aura::safety::SafetyProfile& profile) const;
    std::vector<std::string> selectedModelIds() const;
    std::vector<std::string> selectedRulePackIds() const;
    void updateModelSelectionFromChecked();
```

- [ ] **Step 2: Add a generic checked-id helper in the cpp anonymous namespace**

In `src/gui/safety_settings_dialog.cpp`, after `currentComboProfileId`, add:

```cpp
std::vector<std::string> checkedIdsFromList(const QListWidget* list) {
    std::vector<std::string> ids;
    if (!list) return ids;
    for (int i = 0; i < list->count(); ++i) {
        const auto* item = list->item(i);
        if (!item || item->checkState() != Qt::Checked) continue;
        const QString id = item->data(Qt::UserRole).toString();
        if (!id.isEmpty()) ids.push_back(id.toStdString());
    }
    return ids;
}
```

- [ ] **Step 3: Simplify selectedModelIds and add selectedRulePackIds**

Replace `SafetySettingsDialog::selectedModelIds()` with:

```cpp
std::vector<std::string> SafetySettingsDialog::selectedModelIds() const {
    return checkedIdsFromList(m_modelList);
}
```

Add below it:

```cpp
std::vector<std::string> SafetySettingsDialog::selectedRulePackIds() const {
    return checkedIdsFromList(m_rulePackList);
}
```

- [ ] **Step 4: Add rule-pack application method**

After `applyModelSelectionToProfile`, add:

```cpp
void SafetySettingsDialog::applyRulePackSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    profile.rule_pack_ids = selectedRulePackIds();
}
```

- [ ] **Step 5: Update editedProfile**

Replace:

```cpp
    applyModelSelectionToProfile(profile);
    return profile;
```

with:

```cpp
    applyModelSelectionToProfile(profile);
    applyRulePackSelectionToProfile(profile);
    return profile;
```

- [ ] **Step 6: Build and expect remaining failures**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build may still fail because rule-pack buttons are not implemented yet. Header/source declarations should compile cleanly.

---

### Task 3: Add Rule Pack UI Controls

**Files:**
- Modify: `src/gui/safety_settings_dialog.cpp`

- [ ] **Step 1: Add rule-pack buttons after the rule-pack list**

In the constructor, after:

```cpp
    detectionLayout->addWidget(m_rulePackList);
```

insert:

```cpp
    auto* ruleButtons = new QHBoxLayout();
    auto* addRuleBtn =
        new QPushButton(QStringLiteral("선택 적용"), detectionGroup);
    addRuleBtn->setObjectName(QStringLiteral("safetyRulePackAddButton"));
    auto* removeRuleBtn =
        new QPushButton(QStringLiteral("선택 해제"), detectionGroup);
    removeRuleBtn->setObjectName(QStringLiteral("safetyRulePackRemoveButton"));
    ruleButtons->addWidget(addRuleBtn);
    ruleButtons->addWidget(removeRuleBtn);
    ruleButtons->addStretch();
    detectionLayout->addLayout(ruleButtons);
```

- [ ] **Step 2: Connect direct rule-pack check changes**

After the existing `connect(m_modelList, &QListWidget::itemChanged, ...)`, add:

```cpp
    connect(m_rulePackList, &QListWidget::itemChanged, this, [this]() {
        updateSummary();
    });
```

- [ ] **Step 3: Connect rule-pack apply/remove buttons**

After the model button connections, add:

```cpp
    connect(addRuleBtn, &QPushButton::clicked, this, [this]() {
        if (!m_rulePackList) return;
        auto* item = m_rulePackList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_rulePackList);
        item->setCheckState(Qt::Checked);
        updateSummary();
    });
    connect(removeRuleBtn, &QPushButton::clicked, this, [this]() {
        if (!m_rulePackList) return;
        auto* item = m_rulePackList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_rulePackList);
        item->setCheckState(Qt::Unchecked);
        updateSummary();
    });
```

- [ ] **Step 4: Make rule-pack rows user-checkable**

In `addAssetRows`, replace:

```cpp
        if (list == m_modelList) {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setData(Qt::UserRole, QString::fromStdString(ref.id));
        }
```

with:

```cpp
        if (list == m_modelList || list == m_rulePackList) {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setData(Qt::UserRole, QString::fromStdString(ref.id));
        }
```

- [ ] **Step 5: Preserve checked rule packs across updateSummary**

In `updateSummary`, after the `selectedModels` block, add:

```cpp
    std::vector<std::string> selectedRulePacks = workingProfile.rule_pack_ids;
    if (!resetSelection) {
        selectedRulePacks = selectedRulePackIds();
    }
```

Replace:

```cpp
    addAssetRows(m_rulePackList, m_registry.rule_packs,
                 workingProfile.rule_pack_ids, true);
```

with:

```cpp
    workingProfile.rule_pack_ids = selectedRulePacks;
    addAssetRows(m_rulePackList, m_registry.rule_packs,
                 selectedRulePacks, true);
```

- [ ] **Step 6: Build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 4: Localize Safety Assets Dialog

**Files:**
- Modify: `src/gui/safety_settings_dialog.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add QSettings include and helper**

In `src/gui/safety_settings_dialog.cpp`, add:

```cpp
#include <QSettings>
```

Inside the anonymous namespace, add:

```cpp
bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

QString textKoEn(const char* ko, const char* en) {
    return useKoreanUi() ? QString::fromUtf8(ko) : QString::fromUtf8(en);
}
```

- [ ] **Step 2: Localize constructor text**

Replace these constructor strings:

```cpp
    setWindowTitle(QStringLiteral("Safety Assets"));
    auto* profileGroup = new QGroupBox(QStringLiteral("Profile"), this);
    profileLayout->addRow(QStringLiteral("Active profile"), m_profileCombo);
    profileLayout->addRow(QStringLiteral("Selection"), m_summaryLabel);
    auto* detectionGroup = new QGroupBox(QStringLiteral("Detection"), this);
    new QLabel(QStringLiteral("Token classification model"), detectionGroup)
    new QLabel(QStringLiteral("Rule packs"), detectionGroup)
    auto* evalGroup = new QGroupBox(QStringLiteral("Evaluation"), this);
```

with:

```cpp
    setWindowTitle(textKoEn("안전 자산", "Safety Assets"));
    auto* profileGroup = new QGroupBox(textKoEn("프로필", "Profile"), this);
    profileLayout->addRow(textKoEn("활성 프로필", "Active profile"), m_profileCombo);
    profileLayout->addRow(textKoEn("선택", "Selection"), m_summaryLabel);
    auto* detectionGroup = new QGroupBox(textKoEn("탐지", "Detection"), this);
    new QLabel(textKoEn("토큰 분류 모델", "Token classification model"),
               detectionGroup)
    new QLabel(textKoEn("규칙 팩", "Rule packs"), detectionGroup)
    auto* evalGroup = new QGroupBox(textKoEn("평가", "Evaluation"), this);
```

Keep the exact existing object names.

- [ ] **Step 3: Localize hints and buttons**

Use:

```cpp
const QString applyText = textKoEn("선택 적용", "Apply selected");
const QString removeText = textKoEn("선택 해제", "Clear selected");
```

Then construct both model and rule buttons with those variables.

Replace the hard-coded Korean model hint with:

```cpp
        new QLabel(
            textKoEn("체크된 모델만 이번 프로파일에 사용됩니다. 자산 추가/삭제는 별도 관리자 메뉴를 사용합니다.",
                     "Only checked models are used by this profile. Use the asset manager to add or remove assets."),
            detectionGroup));
```

Add an evaluation hint before `m_evalDatasetList`:

```cpp
    evalLayout->addWidget(new QLabel(
        textKoEn("평가 데이터셋은 탐지 성능 검증용이며, 분석 중 실시간 마스킹 규칙은 아닙니다.",
                 "Eval datasets are for safety-filter evaluation, not live masking rules."),
        evalGroup));
```

- [ ] **Step 4: Localize empty-state and status messages**

In `addAssetRows`, replace:

```cpp
        auto* item = new QListWidgetItem(QStringLiteral("No assets found"),
                                         list);
```

with:

```cpp
        auto* item = new QListWidgetItem(
            textKoEn("자산을 찾을 수 없습니다", "No assets found"), list);
```

In `updateStatusFromEditedProfile`, replace status strings with Korean/English branches:

```cpp
        m_statusLabel->setText(
            textKoEn("선택한 프로필을 사용할 수 없어 기본 프로필을 사용합니다.",
                     "Selected profile was not available. Default profile will be used."));
```

```cpp
        m_statusLabel->setText(
            textKoEn("선택한 프로필을 찾을 수 없어 기본 프로필을 사용합니다.",
                     "Selected profile was not found. Default profile will be used."));
```

```cpp
        m_statusLabel->setText(
            textKoEn("프로필에 필요한 자산이 없습니다: ",
                     "Profile has missing assets: ") + detail);
```

```cpp
    m_statusLabel->setText(
        textKoEn("프로필을 사용할 수 있습니다.", "Profile is ready."));
```

- [ ] **Step 5: Localize summary labels**

Replace:

```cpp
        QStringLiteral("Profile: %1\nModel: %2\nRule packs: %3\nEval datasets: %4")
```

with:

```cpp
        textKoEn("프로필: %1\n모델: %2\n규칙 팩: %3\n평가 데이터셋: %4",
                 "Profile: %1\nModel: %2\nRule packs: %3\nEval datasets: %4")
```

- [ ] **Step 6: Add a Korean UI smoke assertion**

In `tests/integration/gui_smoke/gui_smoke.cpp`, add a small subcase near the Safety Settings tests:

```cpp
    SUBCASE("safety settings dialog localizes Korean UI labels") {
        QSettings settings(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
        const QVariant oldLanguage = settings.value(QStringLiteral("ui/language"));
        settings.setValue(QStringLiteral("ui/language"), QStringLiteral("ko"));

        aura::gui::SafetySettingsDialog dlg(QStringLiteral("default"));
        CHECK(dlg.windowTitle() == QStringLiteral("안전 자산"));
        CHECK(dlg.statusText().contains(QStringLiteral("프로필")));

        if (oldLanguage.isValid()) {
            settings.setValue(QStringLiteral("ui/language"), oldLanguage);
        } else {
            settings.remove(QStringLiteral("ui/language"));
        }
    }
```

If `QSettings` or `QVariant` is not included in the test file, add:

```cpp
#include <QSettings>
#include <QVariant>
```

- [ ] **Step 7: Build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 5: Verify and Commit

**Files:**
- Verify all modified files.

- [ ] **Step 1: Run GUI smoke**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `1/1` tests pass.

- [ ] **Step 2: Inspect diff**

Run:

```powershell
git diff -- src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/integration/gui_smoke/gui_smoke.cpp
```

Expected:

- Safety Settings uses Korean/English text helpers.
- Rule pack rows are user-checkable and multi-select.
- Rule pack selection flows into `editedProfile().rule_pack_ids`.
- Eval dataset rows remain read-only.
- Tests verify localization and rule-pack editability.

- [ ] **Step 3: Commit**

Run:

```powershell
git add src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-safety-assets-rule-pack-selection.md .scratch/safety-assets-rulepacks/PLAN.md
git commit -m "feat: make safety rule packs editable"
```

Expected: commit succeeds.

---

## Self-Review

Spec coverage:
- Korean Safety Assets UI: covered in Task 4.
- Rule pack remove/apply/change: covered in Tasks 1-3.
- Rule pack persistence through profile editing: covered by `editedProfile()` tests and implementation.
- Eval datasets role: kept read-only with explanatory copy.

Placeholder scan:
- No TBD/TODO/fill-later steps.
- Every code-changing step includes concrete code snippets.

Type consistency:
- `selectedRulePackIds()` is declared and implemented with the same name.
- `applyRulePackSelectionToProfile()` is declared and implemented with the same name.
- `safetyRulePackAddButton` and `safetyRulePackRemoveButton` object names match tests and implementation.

Precondition:
- `main` is currently ahead of `origin/main` from the previous local merge. Execution should either push `main` first or create the implementation branch from this local `main` deliberately.
