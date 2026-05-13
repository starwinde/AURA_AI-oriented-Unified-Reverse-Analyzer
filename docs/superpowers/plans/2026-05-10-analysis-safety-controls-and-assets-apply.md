# Analysis Safety Controls and Assets Apply Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the GUI-first safety workflow explicit and real: analysis options must let the user choose how string protection is applied, and Safety Assets "선택 적용" must persist and affect runtime analysis.

**Architecture:** Introduce a typed per-analysis safety mode instead of passing a raw boolean through GUI and CLI paths. Keep GUI as the reference surface, then mirror the same mode in CLI `aura analyze`. Repair Safety Assets by proving the path from button click -> edited profile -> saved JSON -> active profile -> `runAnalyze(...)` rule loading.

**Tech Stack:** C++17, Qt Widgets, cJSON profile persistence, AURA safety core, CLI11, doctest GUI/CLI smoke tests, CMake/CTest.

---

## Current Facts

- `AnalysisOptionsDialog` currently exposes only `bool stringProtectionEnabled()`.
- `MainWindow::runAnalyze(...)` currently accepts `bool enableStringProtection`.
- GUI analysis paths are `onAddBinary()`, `onAnalyzeClicked()`, and `onTableDoubleClicked()`.
- CLI now has `aura analyze --string-protection`, but it is still boolean and uses the default safety profile.
- Safety Assets has separate model and rule-pack "선택 적용/선택 해제" buttons.
- `SafetySettingsDialog::editedProfile()` returns an in-memory profile; `MainWindow::onSafetySettings()` saves it with `saveSafetyProfile(...)` and sets the active profile id.
- A known risk exists in Safety Assets: a row can look selected/current in the list without being checked, and "선택 적용" must be tested as the actual state-changing command, not just a visual selection.

---

## Autoplan Review

### Product Review

- Verdict: proceed with a GUI-first integrated slice.
- Reason: the current "string protection" checkbox hides several different user intents. Users need to choose whether they want no safety work, detection-only visibility, or automatic masking.
- Product decision: `Scan only` means "show findings without changing exported/protected values." It does not persist mask overrides and does not silently change output values.
- Product decision: Safety Assets "선택 적용" must be treated as a real profile-edit command, not a visual convenience. A successful OK must affect the next analysis.

### Design Review

- Verdict: keep one Analysis Options dialog; do not add a new screen.
- Reason: users already encounter this dialog immediately before analysis. A compact enable checkbox plus mode selector keeps the workflow local.
- Design decision: the detailed mode selector is disabled while the master checkbox is off. When enabled, the selector offers exactly two active choices: `Scan only` and `Mask findings`; Off remains represented by the unchecked master checkbox.
- Design decision: Safety Assets should make current row selection and checked state visually distinct enough through existing checkbox rows and button behavior; no new asset-management layout is required in this slice.

### Engineering Review

- Verdict: add a typed `StringProtectionMode` and pass it through core-facing GUI/CLI paths.
- Reason: continuing to pass a raw bool will recreate the same class of bug where UI state exists but runtime cannot distinguish intended behavior.
- Engineering decision: CLI must not overload the same option name as both flag and value option. Use `--string-protection-mode off|scan-only|mask` for the new explicit contract and preserve existing `--string-protection` as a compatibility alias for `mask`.
- Engineering decision: extracted helper logic should avoid duplicating GUI and CLI string-protection transformation semantics. If implementation duplication starts growing, add a small shared helper in safety core rather than letting GUI and CLI drift.

### DX Review

- Verdict: verification must include GUI and CLI actual targets plus smoke tests.
- Reason: the previous miss happened because `gui_smoke` was rebuilt but `aura-gui.exe` was stale.
- DX decision: acceptance requires `aura`, `aura-gui`, `cli_smoke`, `gui_smoke`, and the focused CTest runs.
- DX decision: CLI help must advertise the explicit protection mode so developers can discover the same behavior exposed in GUI.

### Final Autoplan Decision

- Approved after edits below.
- Scope is not expanded to live token-classification inference. Model selection persistence is validated, but live findings remain rule-pack based until a separate model-runtime plan.
- No open user decision is required before implementation.

---

## Required Behavior

### Analysis Options

The GUI analysis dialog must offer detailed string protection application choices:

- `Off`: do not scan strings, do not mask, do not apply stored overrides.
- `Scan only`: run rule/model detection and display findings for this analysis, but keep the visible/export value as original unless the user later chooses a mask. Do not persist mask overrides or silently change protected/export values.
- `Mask findings`: run detection and generate masked protected/export values automatically.
- `Use Safety Assets profile`: all non-Off modes must use the currently active Safety Assets profile.

The first screen must still be simple:

- The old checkbox may remain as a master enable toggle, but enabling it must reveal or enable the detailed mode control.
- The default must remain `Off` unless product policy is explicitly changed later.
- Cancel still means no registration and no analysis in `File -> Add Binary`.

### Safety Assets

When the user clicks "선택 적용" on a model or rule pack:

- The current list item must become checked.
- The internal edited state must mark that asset category as dirty.
- Pressing OK must persist the changed profile JSON.
- The active profile id must remain or become the edited profile id.
- The next analysis with protection enabled must use the saved profile.

For rule packs:

- All mode opens as all valid packs checked.
- If the user clicks "선택 적용" on a subset, mode becomes `Selected`.
- If the user clicks "선택 해제" until none are checked, mode becomes `None`.

For token classification models:

- Single-select behavior remains: one checked model at most.
- "선택 적용" must persist `model_policy.model_id`, `token_classification_model_id`, and enabled flags consistently.
- If model runtime inference is still not wired, the GUI must not imply that model findings are live. The model selection can be persisted and validated, but live analysis still depends on rule packs unless a separate model-runtime task wires it.

### CLI/GUI Coupling

GUI is the reference surface. CLI must mirror the final analysis protection mode:

- `aura analyze --string-protection-mode off|scan-only|mask`.
- Existing `--string-protection` boolean remains accepted as a compatibility alias for `--string-protection-mode mask`.
- CLI output must include `body.string_protection_mode`.

---

## File Structure

### Core Type Boundary

- Modify `include/aura/safety/string_safety.h`
  - Add `enum class StringProtectionMode { Off, ScanOnly, Mask };`
  - Add a result helper type if needed for applying findings consistently.

- Modify `src/core/safety/string_safety.cpp`
  - Keep rule-pack scan behavior unchanged.
  - Add helper functions for protection mode text conversion if shared by CLI/GUI.

### GUI

- Modify `src/gui/analysis_options_dialog.h`
  - Replace/extend `stringProtectionEnabled()` with `stringProtectionMode()`.
  - Keep `stringProtectionEnabled()` as a compatibility wrapper if existing tests/helpers still use it.

- Modify `src/gui/analysis_options_dialog.cpp`
  - Add a mode control with stable object names:
    - `analysisStringProtectionCheckBox`
    - `analysisStringProtectionModeCombo`
  - Populate Off / Scan only / Mask findings.

- Modify `src/gui/main_window.h`
  - Change `addBinaryAndAnalyze(...)`, `analyzeBinaryAt(...)`, and `runAnalyze(...)` to accept `aura::safety::StringProtectionMode`.
  - Keep bool overloads only as test compatibility wrappers if needed.

- Modify `src/gui/main_window.cpp`
  - Apply mode semantics in string processing:
    - Off: current disabled branch.
    - ScanOnly: fill findings and summary, but `maskedContent` empty, `protectedValue/exportValue == content`.
    - Mask: current masking branch.
  - Ensure stored overrides are only reapplied when mode is `Mask`, not `ScanOnly`.

- Modify `src/gui/safety_settings_dialog.h/.cpp`
  - Split dirty flags:
    - `m_modelSelectionEdited`
    - `m_rulePackSelectionEdited`
  - Make button handlers explicitly update dirty flags.
  - Add test-only/readback helpers only if existing public methods cannot prove state.

### CLI

- Modify `src/cli/main.cpp`
  - Parse `--string-protection-mode off|scan-only|mask`.
  - Keep existing `--string-protection` boolean as a compatibility alias for `mask`.
  - Emit `body.string_protection_mode`.
  - Apply `scan-only` and `mask` exactly like GUI.

### Tests

- Modify `tests/unit/safety/safety_unit.cpp`
  - Add mode conversion tests if mode text helpers live in core.

- Modify `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add Analysis Options mode-control tests.
  - Add Safety Assets "선택 적용 -> OK/save -> reopen -> analyze" tests.
  - Add ScanOnly vs Mask runtime tests.

- Modify `tests/integration/cli_smoke/cli_smoke.cpp`
  - Add `--string-protection-mode off|scan-only|mask` contract tests.

---

## Detailed Execution Breakdown

This plan must be executed in the order below. Each slice ends with a concrete build or test gate before the next slice starts.

| Slice | Scope | Primary Files | Gate |
| --- | --- | --- | --- |
| 1 | Core mode type only | `include/aura/safety/string_safety.h`, `src/core/safety/string_safety.cpp`, `tests/unit/safety/safety_unit.cpp` | `safety_unit` builds and focused safety tests pass |
| 2 | Analysis Options UI state only | `src/gui/analysis_options_dialog.h`, `src/gui/analysis_options_dialog.cpp`, `tests/integration/gui_smoke/gui_smoke.cpp` | GUI smoke can find checkbox and mode combo |
| 3 | GUI runtime semantics | `src/gui/main_window.h`, `src/gui/main_window.cpp`, `tests/integration/gui_smoke/gui_smoke.cpp` | GUI smoke proves Off, ScanOnly, Mask differ |
| 4 | Safety Assets rule-pack apply | `src/gui/safety_settings_dialog.h`, `src/gui/safety_settings_dialog.cpp`, `tests/integration/gui_smoke/gui_smoke.cpp` | apply -> OK -> reopen preserves checked rule pack |
| 5 | Safety Assets model apply | `src/gui/safety_settings_dialog.h`, `src/gui/safety_settings_dialog.cpp`, `tests/integration/gui_smoke/gui_smoke.cpp` | apply -> OK -> reopen preserves selected model policy |
| 6 | CLI mode parity | `src/cli/main.cpp`, `tests/integration/cli_smoke/cli_smoke.cpp` | CLI smoke proves `off`, `scan-only`, `mask` output |
| 7 | Combined verification | no new source files | `aura`, `aura-gui`, `cli_smoke`, `gui_smoke`, and focused CTest pass |
| 8 | Foreground GUI verification | no new source files | launched `aura-gui.exe` visibly shows new controls and behavior |

### Dependency Rules

- Slice 1 must land first because GUI and CLI both depend on `StringProtectionMode`.
- Slice 2 must not change analysis runtime behavior; it only exposes the user's intended mode.
- Slice 3 must not change Safety Assets persistence; it only consumes the active profile according to the selected mode.
- Slice 4 and Slice 5 must not change the analysis dialog; they only make Safety Assets edits real and persistent.
- Slice 6 must mirror the behavior already proven through GUI. GUI remains authoritative when CLI behavior is ambiguous.
- Slice 7 must rebuild the actual app targets, not only smoke-test binaries.
- Slice 8 is mandatory because this bug class is user-visible and can survive automated smoke tests if the wrong executable is launched.

### Commit Checkpoints

Use these checkpoints if the implementation is committed incrementally:

1. `feat: add string protection mode type`
   - Include Slice 1 only.
2. `feat: expose analysis string protection modes`
   - Include Slice 2 only.
3. `feat: apply string protection modes in gui analysis`
   - Include Slice 3 only.
4. `fix: persist safety asset apply selections`
   - Include Slice 4 and Slice 5.
5. `feat: mirror string protection modes in cli`
   - Include Slice 6.
6. `test: verify safety mode gui and cli parity`
   - Include only test or documentation adjustments discovered during Slice 7 and Slice 8.

### Implementation Guardrails

- Do not replace the existing Safety Assets dialog with a new screen.
- Do not wire live token-classification inference in this plan.
- Do not treat checked rows and current selected rows as the same state.
- Do not persist mask overrides in `ScanOnly`.
- Do not let CLI invent behavior that GUI does not expose.
- Do not call the work complete unless `aura-gui.exe` itself was rebuilt and launched.

---

## Task 1: Add Protection Mode Type

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Add failing unit test for mode text round-trip**

Add near existing safety profile tests:

```cpp
TEST_CASE("string protection mode text round-trips") {
    CHECK(aura::safety::stringProtectionModeToText(
              aura::safety::StringProtectionMode::Off) == std::string("off"));
    CHECK(aura::safety::stringProtectionModeToText(
              aura::safety::StringProtectionMode::ScanOnly) ==
          std::string("scan-only"));
    CHECK(aura::safety::stringProtectionModeToText(
              aura::safety::StringProtectionMode::Mask) ==
          std::string("mask"));

    CHECK(aura::safety::parseStringProtectionMode("off") ==
          aura::safety::StringProtectionMode::Off);
    CHECK(aura::safety::parseStringProtectionMode("scan-only") ==
          aura::safety::StringProtectionMode::ScanOnly);
    CHECK(aura::safety::parseStringProtectionMode("mask") ==
          aura::safety::StringProtectionMode::Mask);
    CHECK(aura::safety::parseStringProtectionMode("unexpected") ==
          aura::safety::StringProtectionMode::Off);
}
```

- [ ] **Step 2: Run unit build and confirm RED**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
```

Expected: compile failure because `StringProtectionMode` helpers do not exist.

- [ ] **Step 3: Add enum and helpers**

In `include/aura/safety/string_safety.h`, add:

```cpp
enum class StringProtectionMode {
    Off,
    ScanOnly,
    Mask,
};

std::string stringProtectionModeToText(StringProtectionMode mode);
StringProtectionMode parseStringProtectionMode(const std::string& text);
```

In `src/core/safety/string_safety.cpp`, add:

```cpp
std::string stringProtectionModeToText(StringProtectionMode mode) {
    switch (mode) {
        case StringProtectionMode::ScanOnly:
            return "scan-only";
        case StringProtectionMode::Mask:
            return "mask";
        case StringProtectionMode::Off:
            return "off";
    }
    return "off";
}

StringProtectionMode parseStringProtectionMode(const std::string& text) {
    if (text == "scan-only") return StringProtectionMode::ScanOnly;
    if (text == "mask" || text == "on" || text == "true")
        return StringProtectionMode::Mask;
    return StringProtectionMode::Off;
}
```

- [ ] **Step 4: Verify unit test passes**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS.

---

## Task 2: Analysis Options Detailed Mode UI

**Files:**
- Modify: `src/gui/analysis_options_dialog.h`
- Modify: `src/gui/analysis_options_dialog.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke test for mode combo**

Extend `SUBCASE("analysis options dialog defaults string protection off")`:

```cpp
auto* modeCombo = dlg.findChild<QComboBox*>(
    QStringLiteral("analysisStringProtectionModeCombo"));
REQUIRE(modeCombo != nullptr);
CHECK(modeCombo->isEnabled() == false);
CHECK(dlg.stringProtectionMode() ==
      aura::safety::StringProtectionMode::Off);

checkbox->setChecked(true);
CHECK(modeCombo->isEnabled() == true);
modeCombo->setCurrentIndex(modeCombo->findData(QStringLiteral("scan-only")));
CHECK(dlg.stringProtectionMode() ==
      aura::safety::StringProtectionMode::ScanOnly);
modeCombo->setCurrentIndex(modeCombo->findData(QStringLiteral("mask")));
CHECK(dlg.stringProtectionMode() ==
      aura::safety::StringProtectionMode::Mask);
```

- [ ] **Step 2: Run GUI smoke build and confirm RED**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: compile failure because `stringProtectionMode()` or combo object does not exist.

- [ ] **Step 3: Add dialog API**

In `src/gui/analysis_options_dialog.h`, add forward declaration and fields:

```cpp
class QComboBox;
```

Add public method:

```cpp
aura::safety::StringProtectionMode stringProtectionMode() const;
```

Add private field:

```cpp
QComboBox* m_stringProtectionMode = nullptr;
```

Keep:

```cpp
bool stringProtectionEnabled() const;
```

as:

```cpp
return stringProtectionMode() != aura::safety::StringProtectionMode::Off;
```

- [ ] **Step 4: Add mode combo UI**

In `src/gui/analysis_options_dialog.cpp`, after the checkbox:

```cpp
m_stringProtectionMode = new QComboBox(this);
m_stringProtectionMode->setObjectName(
    QStringLiteral("analysisStringProtectionModeCombo"));
m_stringProtectionMode->addItem(
    ko ? QStringLiteral("탐지만 수행") : QStringLiteral("Scan only"),
    QStringLiteral("scan-only"));
m_stringProtectionMode->addItem(
    ko ? QStringLiteral("탐지 후 자동 마스킹") : QStringLiteral("Mask findings"),
    QStringLiteral("mask"));
m_stringProtectionMode->setEnabled(false);
outer->addWidget(m_stringProtectionMode);

connect(m_enableStringProtection, &QCheckBox::toggled,
        m_stringProtectionMode, &QComboBox::setEnabled);
```

Implement:

```cpp
aura::safety::StringProtectionMode
AnalysisOptionsDialog::stringProtectionMode() const {
    if (!m_enableStringProtection || !m_enableStringProtection->isChecked()) {
        return aura::safety::StringProtectionMode::Off;
    }
    const QString mode =
        m_stringProtectionMode
            ? m_stringProtectionMode->currentData().toString()
            : QStringLiteral("mask");
    return aura::safety::parseStringProtectionMode(mode.toStdString());
}
```

- [ ] **Step 5: Verify GUI smoke targeted build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS after later runtime tasks; if runtime compile still uses bool signatures, proceed to Task 3 first.

---

## Task 3: Apply Mode Semantics in GUI Runtime

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke tests for ScanOnly vs Mask**

Add two subcases near existing string protection tests:

```cpp
SUBCASE("string protection scan-only records findings without masking values") {
    QTemporaryDir home;
    REQUIRE(home.isValid());
    writeFixtureRulePack(home.path());
    AuraHomeGuard auraHome(home.path());

    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::Selected;
    profile.rule_pack_ids = {"fixture-rule"};
    std::string diagnostic;
    REQUIRE(aura::safety::saveSafetyProfile(
        "default", profile, &diagnostic));

    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::ScanOnly));

    bool sawFinding = false;
    for (const auto& s : window.stringList()) {
        sawFinding = sawFinding || !s.findings.isEmpty();
        CHECK(s.maskedContent.isEmpty());
        CHECK(s.protectedValue == s.content);
        CHECK(s.exportValue == s.content);
    }
    CHECK(sawFinding);
}

SUBCASE("string protection mask mode records findings and masked values") {
    QTemporaryDir home;
    REQUIRE(home.isValid());
    writeFixtureRulePack(home.path());
    AuraHomeGuard auraHome(home.path());

    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::Selected;
    profile.rule_pack_ids = {"fixture-rule"};
    std::string diagnostic;
    REQUIRE(aura::safety::saveSafetyProfile(
        "default", profile, &diagnostic));

    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));

    bool sawMask = false;
    for (const auto& s : window.stringList()) {
        sawMask = sawMask ||
                  (!s.findings.isEmpty() && !s.maskedContent.isEmpty() &&
                   s.maskedContent != s.content);
    }
    CHECK(sawMask);
}
```

- [ ] **Step 2: Change MainWindow signatures**

In `src/gui/main_window.h`, change:

```cpp
bool addBinaryAndAnalyze(const QString& binaryPath,
                         AuraAnalysisLevel level,
                         aura::safety::StringProtectionMode protectionMode);
bool analyzeBinaryAt(int row,
                     AuraAnalysisLevel level,
                     aura::safety::StringProtectionMode protectionMode);
bool runAnalyze(int row,
                AuraAnalysisLevel level,
                aura::safety::StringProtectionMode protectionMode);
```

Keep bool overloads:

```cpp
bool addBinaryAndAnalyze(const QString& binaryPath,
                         AuraAnalysisLevel level,
                         bool enableStringProtection);
bool analyzeBinaryAt(int row,
                     AuraAnalysisLevel level,
                     bool enableStringProtection);
```

implemented as:

```cpp
return addBinaryAndAnalyze(
    binaryPath, level,
    enableStringProtection ? aura::safety::StringProtectionMode::Mask
                           : aura::safety::StringProtectionMode::Off);
```

- [ ] **Step 3: Pass mode from all dialog paths**

In `onAddBinary()`, `onAnalyzeClicked()`, and `onTableDoubleClicked()`, replace:

```cpp
dlg.stringProtectionEnabled()
```

with:

```cpp
dlg.stringProtectionMode()
```

- [ ] **Step 4: Implement mode branches in `runAnalyze(...)`**

At the start:

```cpp
const bool scanStrings =
    protectionMode != aura::safety::StringProtectionMode::Off;
const bool maskStrings =
    protectionMode == aura::safety::StringProtectionMode::Mask;
```

Replace `enableStringProtection` checks:

- Use `scanStrings` to call `scanStringWithRulePacks(...)`.
- Use `maskStrings` to set `maskedContent` and masked `protectedValue/exportValue`.
- In `ScanOnly`, copy findings but keep:

```cpp
s.maskedContent.clear();
s.protectedValue = s.content;
s.exportValue = s.content;
s.hasProtection = !s.findings.isEmpty();
```

Apply stored overrides and persist protection rows only in mask mode:

```cpp
if (maskStrings) applyStoredStringOverrides(...);
if (maskStrings) persistStringProtectionRows(...);
```

- [ ] **Step 5: Verify GUI runtime**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
cmake --build build-trim-gui --config Release --target aura-gui
```

Expected: PASS and real GUI target rebuilds.

---

## Task 4: Repair Safety Assets "선택 적용" Persistence

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing test for rule-pack apply button save/reopen/analyze**

Add to the Safety Assets subcase or a new subcase:

```cpp
SUBCASE("safety assets rule-pack apply persists and affects analysis") {
    QTemporaryDir home;
    REQUIRE(home.isValid());
    writeFixtureRulePack(home.path());
    AuraHomeGuard auraHome(home.path());
    const SettingsKeyGuard activeProfileGuard(
        QStringLiteral("safety/activeProfileId"));

    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::None;
    profile.rule_pack_ids = {};
    std::string diagnostic;
    REQUIRE(aura::safety::saveSafetyProfile(
        "default", profile, &diagnostic));

    aura::gui::SafetySettingsDialog dlg(QStringLiteral("default"));
    auto* rulePackList = dlg.findChild<QListWidget*>(
        QStringLiteral("safetyRulePackList"));
    auto* applyBtn = dlg.findChild<QPushButton*>(
        QStringLiteral("safetyRulePackAddButton"));
    REQUIRE(rulePackList != nullptr);
    REQUIRE(applyBtn != nullptr);

    for (int i = 0; i < rulePackList->count(); ++i) {
        auto* item = rulePackList->item(i);
        if (item->data(Qt::UserRole).toString() ==
            QStringLiteral("fixture-rule")) {
            rulePackList->setCurrentRow(i);
            break;
        }
    }
    REQUIRE(rulePackList->currentItem() != nullptr);
    applyBtn->click();
    QApplication::processEvents();

    auto edited = dlg.editedProfile();
    CHECK(edited.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::Selected);
    CHECK(edited.rule_pack_ids == std::vector<std::string>{"fixture-rule"});
    REQUIRE(aura::safety::saveSafetyProfile(
        "default", edited, &diagnostic));

    const auto reloaded =
        aura::safety::loadSafetyProfileById("default");
    REQUIRE(reloaded.found);
    CHECK(reloaded.profile.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::Selected);
    CHECK(reloaded.profile.rule_pack_ids ==
          std::vector<std::string>{"fixture-rule"});

    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));
    bool sawFinding = false;
    for (const auto& s : window.stringList()) {
        sawFinding = sawFinding || !s.findings.isEmpty();
    }
    CHECK(sawFinding);
}
```

- [ ] **Step 2: Add failing test for model apply persistence**

Extend the existing model selection test:

```cpp
setCheckedModelId(modelList, QStringLiteral("model-beta"));
addBtn->click();
QApplication::processEvents();
const auto edited = dlg.editedProfile();
CHECK(edited.model_policy.enabled);
CHECK(edited.model_policy.model_id == "model-beta");
CHECK(edited.token_classification_enabled);
CHECK(edited.token_classification_model_id == "model-beta");
```

- [ ] **Step 3: Split dirty flags**

In `src/gui/safety_settings_dialog.h`, replace:

```cpp
bool m_rulePackSelectionEdited = false;
```

with:

```cpp
bool m_modelSelectionEdited = false;
bool m_rulePackSelectionEdited = false;
```

- [ ] **Step 4: Mark model edits explicitly**

In model `itemChanged`, `addModelBtn`, and `removeModelBtn` handlers, set:

```cpp
m_modelSelectionEdited = true;
```

before `updateSummary()`.

In `updateSummary(resetSelection=true)`, reset both:

```cpp
m_modelSelectionEdited = false;
m_rulePackSelectionEdited = false;
```

- [ ] **Step 5: Preserve unedited model profile**

Change:

```cpp
void SafetySettingsDialog::applyModelSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    applyModelIdsToProfile(profile, selectedModelIds());
}
```

to:

```cpp
void SafetySettingsDialog::applyModelSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    if (!m_modelSelectionEdited) return;
    applyModelIdsToProfile(profile, selectedModelIds());
}
```

Add a second helper for transient summary if needed:

```cpp
void applyModelIdsToProfileForSummary(
    aura::safety::SafetyProfile& profile,
    const std::vector<std::string>& ids) {
    applyModelIdsToProfile(profile, ids);
}
```

Do not let `editedProfile()` rewrite model fields merely because the dialog opened.

- [ ] **Step 6: Ensure OK path saves exactly edited profile**

In `MainWindow::onSafetySettings()`, after save succeeds, reload and update status:

```cpp
setActiveSafetyProfileId(dlg.selectedProfileId());
updateSafetyStatusText();
```

If this is already true, keep it and add the test coverage only.

- [ ] **Step 7: Verify Safety Assets behavior**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
cmake --build build-trim-gui --config Release --target aura-gui
```

Expected: PASS.

---

## Task 5: Mirror Protection Mode in CLI

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] **Step 1: Add failing CLI smoke tests**

Add:

```cpp
TEST_CASE("cli_smoke: analyze string protection modes are explicit") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult off = run(aura_invocation(rizin) +
                        " analyze --string-protection-mode off \"" +
                        fixture + "\"");
    REQUIRE(off.exit_code == 0);
    cJSON *offRoot = parse_or_fail(off.stdout_);
    cJSON *offBody = cJSON_GetObjectItem(offRoot, "body");
    CHECK(get_string(offBody, "string_protection_mode") == "off");
    cJSON_Delete(offRoot);

    CmdResult scan = run(aura_invocation(rizin) +
                         " analyze --string-protection-mode scan-only \"" +
                         fixture + "\"");
    REQUIRE(scan.exit_code == 0);
    cJSON *scanRoot = parse_or_fail(scan.stdout_);
    cJSON *scanBody = cJSON_GetObjectItem(scanRoot, "body");
    CHECK(get_string(scanBody, "string_protection_mode") == "scan-only");
    cJSON_Delete(scanRoot);

    CmdResult mask = run(aura_invocation(rizin) +
                         " analyze --string-protection-mode mask \"" +
                         fixture + "\"");
    REQUIRE(mask.exit_code == 0);
    cJSON *maskRoot = parse_or_fail(mask.stdout_);
    cJSON *maskBody = cJSON_GetObjectItem(maskRoot, "body");
    CHECK(get_string(maskBody, "string_protection_mode") == "mask");
    cJSON_Delete(maskRoot);
}
```

- [ ] **Step 2: Change CLI option shape**

In `src/cli/main.cpp`, replace boolean:

```cpp
bool analyze_string_protection = false;
```

with:

```cpp
std::string analyze_string_protection_mode = "off";
bool analyze_string_protection_legacy = false;
```

Register:

```cpp
cmd_analyze->add_option(
    "--string-protection-mode", analyze_string_protection_mode,
    "string protection mode: off, scan-only, mask")
    ->check(CLI::IsMember({"off", "scan-only", "mask"}));

cmd_analyze->add_flag(
    "--string-protection", analyze_string_protection_legacy,
    "compatibility alias for --string-protection-mode mask");
```

Before dispatch:

```cpp
const auto cliProtectionMode =
    analyze_string_protection_legacy
        ? aura::safety::StringProtectionMode::Mask
        : aura::safety::parseStringProtectionMode(
              analyze_string_protection_mode);
```

- [ ] **Step 3: Apply mode semantics in CLI JSON**

Change `analyze_body_to_json(...)` to accept `StringProtectionMode`.

Emit:

```cpp
cJSON_AddStringToObject(
    out, "string_protection_mode",
    aura::safety::stringProtectionModeToText(protectionMode).c_str());
cJSON_AddBoolToObject(
    out, "string_protection_enabled",
    protectionMode != aura::safety::StringProtectionMode::Off);
```

For `ScanOnly`, include findings but keep `protected_value == content` and `masked_content == ""`.

For `Mask`, include findings and masked values.

- [ ] **Step 4: Verify CLI and GUI together**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura
cmake --build build-trim-gui --config Release --target aura-gui
cmake --build build-trim-gui --config Release --target cli_smoke
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: all PASS.

---

## Task 6: Manual GUI Verification Checklist

**Files:**
- No code changes.

- [ ] **Step 1: Rebuild actual GUI app**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-gui
```

Expected: `build-trim-gui/src/gui/Release/aura-gui.exe` timestamp updates.

- [ ] **Step 2: Launch foreground GUI**

Run:

```powershell
& 'C:\Users\21m15\OneDrive\바탕 화면\AURA\build-trim-gui\src\gui\Release\aura-gui.exe'
```

Expected: AURA GUI opens.

- [ ] **Step 3: Verify Analysis Options**

Manual steps:

1. Open or create a project.
2. Use `File -> Add Binary`.
3. Pick a binary.
4. Confirm the Analysis Options dialog appears before registration.
5. Confirm "문자열 마스킹/보호 스캔 사용" reveals/enables detailed mode.
6. Choose Off, Scan only, Mask findings in separate runs.
7. Confirm Strings panel behavior:
   - Off: no findings, original values.
   - Scan only: findings visible, original export/protected values.
   - Mask: masked values generated.

- [ ] **Step 4: Verify Safety Assets Apply**

Manual steps:

1. Open `Settings -> Safety Assets`.
2. Select a Rule Pack row.
3. Click `선택 적용`.
4. Press OK.
5. Reopen `Settings -> Safety Assets`.
6. Confirm the same Rule Pack is checked.
7. Run Mask findings analysis.
8. Confirm strings are scanned by the selected Rule Pack.

---

## Stop Conditions

- Stop if `gui_smoke` fails twice with the same Safety Assets state mismatch.
- Stop if manual GUI still shows old Analysis Options after `aura-gui` target rebuild; that indicates the wrong executable or stale process is being launched.
- Stop if CLI and GUI mode semantics diverge. GUI is authoritative; change CLI to match GUI.

---

## Acceptance Criteria

- Analysis Options has a detailed string protection mode control.
- `Off`, `ScanOnly`, and `Mask` have distinct runtime effects.
- Safety Assets "선택 적용" persists to profile JSON and affects subsequent analysis.
- Rule Pack `Selected` and `None` behavior remains real in core.
- CLI mirrors GUI mode semantics.
- Verification includes actual app target `aura-gui`, CLI target `aura`, `gui_smoke`, and `cli_smoke`.

---

## Self-Review

- Spec coverage: both requested items are covered. Item 1 is Tasks 1-3 and 5. Item 2 is Task 4 and manual Task 6.
- Placeholder scan: no TBD/TODO placeholders are used.
- Type consistency: `StringProtectionMode::{Off, ScanOnly, Mask}` is used consistently across core, GUI, and CLI.
