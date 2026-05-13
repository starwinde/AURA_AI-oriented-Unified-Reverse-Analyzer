# Effective Safety On/Off Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make safety toggles operationally real: first-analysis string protection must pass the user's checkbox into analysis, and Safety Assets rule-pack checkboxes must determine the actual rule packs used during string protection.

**Architecture:** Keep the existing registration-only `MainWindow::addBinary()` path for non-interactive callers. Add a production `addBinaryAndAnalyze(...)` helper for the UI and tests. Add explicit `RulePackSelectionMode` to `SafetyProfile` so legacy empty `rule_pack_ids` remains "all rule packs," while the GUI can save "selected subset" or "none" unambiguously.

**Tech Stack:** C++17, Qt Widgets, AURA safety core, cJSON profile persistence, GUI smoke tests, safety unit tests, CMake/CTest.

---

## Autoplan Review

### Product

- Verdict: proceed with one integrated slice.
- Reason: users currently see toggles that imply control, but core behavior can still apply all rule packs. That is worse than no toggle because it teaches a false mental model.
- Product decision: "off" must mean no rule-pack findings, including no built-in fallback findings.

### Design

- Verdict: keep the current surfaces.
- Reason: the user already knows "Analysis Options" for per-analysis controls and "Safety Assets" for profile controls. Adding another screen would increase confusion.
- Design decision: default/all mode should render as all valid rule packs checked, not as an empty list.

### Engineering

- Verdict: add an explicit mode field; do not reinterpret empty `rule_pack_ids`.
- Reason: existing profiles depend on empty ids meaning "load all packs." Changing that globally would silently weaken existing safety behavior.
- Engineering decision: use `RulePackSelectionMode::{All, Selected, None}` and persist it as `rule_pack_selection_mode`.

### DX

- Verdict: test the behavior at both core and GUI levels.
- Reason: UI-only tests previously passed while runtime behavior was still wrong. Core tests must prove `None` suppresses runtime and built-in rules.
- DX decision: use focused `safety_unit` tests for semantics and `gui_smoke` for end-to-end UI flow.

### Final Autoplan Decision

- Approved plan shape: integrated safety On/Off plan.
- No open taste decisions.
- Do not implement until the user explicitly authorizes execution.

---

## Current Facts

- `AnalysisOptionsDialog` already has `stringProtectionEnabled()`.
- `onAnalyzeClicked()` and table double-click already pass `dlg.stringProtectionEnabled()` into `runAnalyze(...)`.
- `onAddBinary()` currently registers only; it does not show analysis options or run first analysis.
- `scanStringWithRulePacks(...)` ultimately uses `effectiveRules(profile)`.
- Current core behavior treats empty `rule_pack_ids` as all rule packs.
- Current default behavior should remain secure: legacy/default profiles without a mode field must keep using all rule packs.

---

## Implementation Invariants

These are non-negotiable. If an implementation cannot preserve one, stop and ask before continuing.

- `MainWindow::addBinary(...)` remains registration-only. It must not show a modal dialog and must not implicitly analyze.
- `onAnalyzeClicked()` and `onTableDoubleClicked()` keep their existing behavior except for sharing the same protection semantics through `runAnalyze(...)`.
- Empty `rule_pack_ids` without a persisted `rule_pack_selection_mode` still means `All`.
- Explicit `RulePackSelectionMode::None` means no runtime rule packs and no built-in fallback rules.
- Merely opening Safety Assets and pressing OK must not convert an unedited `All` profile into `Selected`.
- Rule Pack UI is multi-select; token classification model UI remains single-select.
- Eval datasets stay read-only.
- Token Classification Model behavior is not changed in this slice.

---

## Execution Order

Use this exact order because later GUI tests depend on the core mode existing first.

1. Add failing safety core tests.
2. Implement `RulePackSelectionMode` and persistence.
3. Verify `safety_unit`.
4. Update Safety Assets UI semantics.
5. Wire first Add Binary analysis flow.
6. Add GUI smoke coverage.
7. Verify `safety_unit` and `gui_smoke`.
8. Run subagent spec review, then code-quality review.

Stop immediately if `safety_unit` fails after Task 2 or if `gui_smoke` fails twice with the same error.

---

### Task 1: Core Rule-Pack Mode Tests

**Files:**
- Modify: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Add explicit-none scan test**

Add near the existing rule-pack scan tests:

```cpp
TEST_CASE("rule pack selection mode disables all rule findings") {
    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::None;
    profile.rule_pack_ids = {};

    CHECK(aura::safety::scanStringWithRulePacks(
              "alice.smith@example.com api_key=abc1234567890XYZSECRET",
              profile)
              .empty());
}
```

Expected before implementation: compile fails because `RulePackSelectionMode` does not exist.

- [ ] **Step 2: Add legacy parse compatibility test**

Add:

```cpp
TEST_CASE("safety profile rule pack mode keeps legacy compatibility") {
    namespace fs = std::filesystem;
    const fs::path root =
        tempRoot("aura_safety_unit_rule_pack_mode_home");
    fs::remove_all(root);
    fs::create_directories(root / "safety-profiles");

    {
        std::ofstream out(root / "safety-profiles" / "legacy-all.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"legacy-all","rule_pack_ids":[]})";
    }
    {
        std::ofstream out(root / "safety-profiles" / "legacy-selected.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"legacy-selected","rule_pack_ids":["korean-sensitive"]})";
    }
    {
        std::ofstream out(root / "safety-profiles" / "explicit-none.json",
                          std::ios::binary);
        out << R"({"schema_version":1,"profile_id":"explicit-none","rule_pack_selection_mode":"none","rule_pack_ids":[]})";
    }

    setEnvVar("AURA_HOME", root.string());
    const auto legacyAll =
        aura::safety::loadSafetyProfileById("legacy-all");
    const auto legacySelected =
        aura::safety::loadSafetyProfileById("legacy-selected");
    const auto explicitNone =
        aura::safety::loadSafetyProfileById("explicit-none");
    clearEnvVar("AURA_HOME");

    REQUIRE(legacyAll.found);
    CHECK(legacyAll.profile.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::All);
    REQUIRE(legacySelected.found);
    CHECK(legacySelected.profile.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::Selected);
    REQUIRE(explicitNone.found);
    CHECK(explicitNone.profile.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::None);
}
```

- [ ] **Step 3: Extend save/reload test**

In `TEST_CASE("safety profile edits can be persisted and reloaded")`, before changing the model id, set:

```cpp
    edited.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::None;
    edited.rule_pack_ids = {};
```

After reload, assert:

```cpp
    CHECK(reloaded.profile.rule_pack_selection_mode ==
          aura::safety::RulePackSelectionMode::None);
    CHECK(reloaded.profile.rule_pack_ids.empty());
```

- [ ] **Step 4: Run the focused unit build and confirm RED**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
```

Expected before Task 2: compile fails because `RulePackSelectionMode` is not declared. If it does not fail, inspect whether the new tests were inserted into the compiled `safety_unit.cpp`.

---

### Task 2: Core Rule-Pack Mode Implementation

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`

- [ ] **Step 1: Add public enum and profile field**

In `include/aura/safety/string_safety.h`, before `struct ModelPolicy` or before `struct SafetyProfile`, add:

```cpp
enum class RulePackSelectionMode {
    All,
    Selected,
    None,
};
```

Inside `SafetyProfile`, before `rule_pack_ids`, add:

```cpp
    RulePackSelectionMode rule_pack_selection_mode =
        RulePackSelectionMode::All;
```

- [ ] **Step 2: Add parse/save helpers**

In `src/core/safety/string_safety.cpp` anonymous namespace, near the model-policy text helpers, add:

```cpp
RulePackSelectionMode parseRulePackSelectionMode(
    const std::string& value,
    const std::vector<std::string>& rulePackIds) {
    if (value == "none") return RulePackSelectionMode::None;
    if (value == "selected") return RulePackSelectionMode::Selected;
    if (value == "all") return RulePackSelectionMode::All;
    return rulePackIds.empty() ? RulePackSelectionMode::All
                               : RulePackSelectionMode::Selected;
}

const char* rulePackSelectionModeToText(RulePackSelectionMode mode) {
    switch (mode) {
        case RulePackSelectionMode::None:
            return "none";
        case RulePackSelectionMode::Selected:
            return "selected";
        case RulePackSelectionMode::All:
            return "all";
    }
    return "all";
}
```

- [ ] **Step 3: Parse mode with legacy fallback**

In `parseSafetyProfileText(...)`, immediately after:

```cpp
    out.rule_pack_ids = jsonStringArray(root, "rule_pack_ids");
```

add:

```cpp
    out.rule_pack_selection_mode = parseRulePackSelectionMode(
        jsonString(root, "rule_pack_selection_mode"),
        out.rule_pack_ids);
```

- [ ] **Step 4: Save mode**

In `saveSafetyProfile(...)`, before `writeStringArray(root, "rule_pack_ids", ...)`, add:

```cpp
    cJSON_AddStringToObject(
        root, "rule_pack_selection_mode",
        rulePackSelectionModeToText(profile.rule_pack_selection_mode));
```

- [ ] **Step 5: Apply mode while loading rules**

In `loadRulesFromRoot(...)`, after `std::vector<Rule> out;`, add:

```cpp
    if (profile.rule_pack_selection_mode == RulePackSelectionMode::None) {
        return out;
    }
```

Replace:

```cpp
    const bool acceptAll = wanted.empty();
```

with:

```cpp
    const bool acceptAll =
        profile.rule_pack_selection_mode == RulePackSelectionMode::All;
```

- [ ] **Step 6: Suppress built-in fallback for explicit none**

In `effectiveRules(...)`, add first:

```cpp
    if (profile.rule_pack_selection_mode == RulePackSelectionMode::None) {
        return {};
    }
```

- [ ] **Step 7: Update default-profile comment**

Replace the old comment near `loadDefaultSafetyProfile()` that says empty `rule_pack_ids` means load every runtime pack with:

```cpp
    // Legacy profiles without rule_pack_selection_mode keep treating empty
    // rule_pack_ids as "all"; explicit None disables runtime and built-in rules.
```

- [ ] **Step 8: Verify core**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: `safety_unit` passes.

---

### Task 3: Safety Assets UI Semantics

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`

- [ ] **Step 1: Track rule-pack user edits**

In `SafetySettingsDialog` private fields, add:

```cpp
    bool m_rulePackSelectionEdited = false;
```

- [ ] **Step 2: Add valid-id helper**

In `safety_settings_dialog.cpp` anonymous namespace, after `checkedIdsFromList(...)`, add:

```cpp
std::vector<std::string> validIdsFromRefs(
    const std::vector<aura::safety::SafetyAssetRef>& refs) {
    std::vector<std::string> ids;
    for (const auto& ref : refs) {
        if (ref.valid) ids.push_back(ref.id);
    }
    return ids;
}
```

- [ ] **Step 3: Mark rule-pack changes as edited**

In the `m_rulePackList` `itemChanged` connection and both rule-pack button handlers, set:

```cpp
        m_rulePackSelectionEdited = true;
```

before `updateSummary()`.

- [ ] **Step 4: Preserve mode unless the user edited**

At the start of `updateSummary(bool resetSelection)`, add:

```cpp
    if (resetSelection) {
        m_rulePackSelectionEdited = false;
    }
```

Compute checked rule packs as:

```cpp
    std::vector<std::string> checkedRulePacks;
    if (!resetSelection && m_rulePackSelectionEdited) {
        checkedRulePacks = checkedIdsFromList(m_rulePackList);
    } else if (workingProfile.rule_pack_selection_mode ==
               aura::safety::RulePackSelectionMode::All) {
        checkedRulePacks = validIdsFromRefs(m_registry.rule_packs);
    } else if (workingProfile.rule_pack_selection_mode ==
               aura::safety::RulePackSelectionMode::None) {
        checkedRulePacks = {};
    } else {
        checkedRulePacks = workingProfile.rule_pack_ids;
    }
```

Set summary count from `checkedRulePacks.size()`.

- [ ] **Step 5: Save selected/none only after edit**

Change `applyRulePackSelectionToProfile(...)` to:

```cpp
void SafetySettingsDialog::applyRulePackSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    if (!m_rulePackSelectionEdited) return;
    const auto ids = selectedRulePackIds();
    profile.rule_pack_ids = ids;
    profile.rule_pack_selection_mode =
        ids.empty() ? aura::safety::RulePackSelectionMode::None
                    : aura::safety::RulePackSelectionMode::Selected;
}
```

This prevents merely opening and pressing OK from converting an unedited `All` profile into an explicit `Selected` profile.

- [ ] **Step 6: Remove the old UI-only fallback**

If the working tree contains helper code that turns an empty checked list into every valid rule pack, remove it. In particular, do not keep logic equivalent to:

```cpp
if (ids.empty()) return validIdsFromList(m_rulePackList);
```

or:

```cpp
workingProfile.rule_pack_ids = checkedRulePacks.empty()
    ? validIdsFromRefs(m_registry.rule_packs)
    : checkedRulePacks;
```

The UI can display `All` as all checked rows, but saving all-unchecked after user edit must produce explicit `None`.

---

### Task 4: First Add Binary Analysis Flow

**Files:**
- Modify: `src/gui/analysis_options_dialog.cpp`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`

- [ ] **Step 1: Name the checkbox**

After constructing `m_enableStringProtection`, add:

```cpp
    m_enableStringProtection->setObjectName(
        QStringLiteral("analysisStringProtectionCheckBox"));
```

- [ ] **Step 2: Add production helper**

In `MainWindow` public helpers, add:

```cpp
    bool addBinaryAndAnalyze(const QString& binaryPath,
                             AuraAnalysisLevel level,
                             bool enableStringProtection);
```

In private helpers, add:

```cpp
    int  projectRowForBinaryPath(const QString& binaryPath) const;
```

In `main_window.cpp`, implement:

```cpp
bool MainWindow::addBinaryAndAnalyze(const QString& binaryPath,
                                     AuraAnalysisLevel level,
                                     bool enableStringProtection) {
    if (!addBinary(binaryPath)) return false;
    const int row = projectRowForBinaryPath(binaryPath);
    if (row < 0) return false;
    return runAnalyze(row, level, enableStringProtection);
}
```

and:

```cpp
int MainWindow::projectRowForBinaryPath(const QString& binaryPath) const {
    if (!m_projectModel) return -1;
    const QByteArray target = binaryPath.toUtf8();
    for (int row = 0; row < m_projectModel->rowCount(); ++row) {
        const auto* rec = m_projectModel->recordAt(row);
        if (!rec) continue;
        if (QByteArray(rec->path) == target) return row;
    }
    return -1;
}
```

- [ ] **Step 3: Wire `onAddBinary()`**

Replace:

```cpp
    if (path.isEmpty()) return;
    addBinary(path);
```

with:

```cpp
    if (path.isEmpty()) return;

    AnalysisOptionsDialog dlg(path, this);
    if (dlg.exec() != QDialog::Accepted) return;
    addBinaryAndAnalyze(path, dlg.selectedLevel(),
                        dlg.stringProtectionEnabled());
```

Do not change RPC, drag-drop, or direct `addBinary(...)` tests.

- [ ] **Step 4: Confirm Cancel semantics**

Do not call `addBinaryAndAnalyze(...)` before `dlg.exec()` returns accepted. The accepted-only flow must remain:

```cpp
    AnalysisOptionsDialog dlg(path, this);
    if (dlg.exec() != QDialog::Accepted) return;
    addBinaryAndAnalyze(path, dlg.selectedLevel(),
                        dlg.stringProtectionEnabled());
```

This guarantees cancelling the analysis options dialog does not register the binary.

---

### Task 5: GUI Smoke Coverage

**Files:**
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add analysis-options checkbox assertions**

In the analysis options subcase, find the checkbox by `analysisStringProtectionCheckBox`, assert it starts unchecked, toggle it on/off, and assert `dlg.stringProtectionEnabled()` follows.

- [ ] **Step 2: Update rule-pack dialog test**

Use explicit all-mode default profile:

```cpp
        defaultProfile.rule_pack_selection_mode =
            aura::safety::RulePackSelectionMode::All;
        defaultProfile.rule_pack_ids = {};
```

Use selected high-security profile:

```cpp
        highSecurityProfile.rule_pack_selection_mode =
            aura::safety::RulePackSelectionMode::Selected;
        highSecurityProfile.rule_pack_ids = {"rule-beta"};
```

Assert:

```cpp
        requireCheckedRulePacks({"rule-alpha", "rule-beta"});
```

for default/all mode, then assert edited subset is `Selected`, and all-unchecked is `None`.

- [ ] **Step 3: Add first-analysis off test**

Add:

```cpp
    SUBCASE("first add-binary analysis can disable string protection") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinaryAndAnalyze(
            stringFixture, AURA_ANALYSIS_LEVEL_FULL, false));

        const auto strs = window.stringList();
        REQUIRE_FALSE(strs.isEmpty());
        for (const auto& s : strs) {
            CHECK_FALSE(s.hasProtection);
            CHECK(s.maskedContent.isEmpty());
            CHECK(s.protectedValue == s.content);
            CHECK(s.exportValue == s.content);
            CHECK(s.findings.isEmpty());
            CHECK(s.protectionSummary.isEmpty());
        }
    }
```

- [ ] **Step 4: Add first-analysis on test**

Add:

```cpp
    SUBCASE("first add-binary analysis can enable string protection") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinaryAndAnalyze(
            stringFixture, AURA_ANALYSIS_LEVEL_FULL, true));

        const auto strs = window.stringList();
        REQUIRE_FALSE(strs.isEmpty());

        bool sawProtected = false;
        for (const auto& s : strs) {
            sawProtected = sawProtected || s.hasProtection ||
                           !s.maskedContent.isEmpty() ||
                           s.protectedValue != s.content;
        }
        CHECK(sawProtected);
    }
```

- [ ] **Step 5: Add explicit-none runtime test**

Add:

```cpp
    SUBCASE("disabled rule packs produce no rule-pack findings") {
        QTemporaryDir home;
        REQUIRE(home.isValid());
        AuraHomeGuard auraHome(home.path());

        aura::safety::SafetyProfile profile;
        profile.rule_pack_selection_mode =
            aura::safety::RulePackSelectionMode::None;
        profile.rule_pack_ids = {};
        std::string diagnostic;
        REQUIRE(aura::safety::saveSafetyProfile("default", profile,
                                                &diagnostic));
        CHECK(diagnostic.empty());

        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinaryAndAnalyze(
            stringFixture, AURA_ANALYSIS_LEVEL_FULL, true));

        const auto strs = window.stringList();
        REQUIRE_FALSE(strs.isEmpty());
        for (const auto& s : strs) {
            CHECK_FALSE(s.hasProtection);
            CHECK(s.maskedContent.isEmpty());
            CHECK(s.protectedValue == s.content);
            CHECK(s.findings.isEmpty());
            CHECK(s.protectionSummary.isEmpty());
        }
    }
```

- [ ] **Step 6: Keep registration-only coverage**

Keep the existing `SUBCASE("add binary")` asserting:

```cpp
REQUIRE(window.addBinary(fixture));
CHECK(window.projectBinaryCount() == 1);
```

Do not add function-count or string-protection assertions to that subcase. It intentionally documents that `addBinary(...)` does not analyze.

---

### Task 6: Verification and Review

**Files:**
- Verify all modified files.

- [ ] **Step 1: Build and run safety unit**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: `safety_unit` passes.

- [ ] **Step 2: Build and run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes.

- [ ] **Step 3: Inspect diff**

Run:

```powershell
git diff -- include/aura/safety/string_safety.h src/core/safety/string_safety.cpp src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/unit/safety/safety_unit.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-effective-safety-onoff.md
```

Expected:

- Explicit `RulePackSelectionMode` exists.
- `None` suppresses built-in fallback.
- Safety Assets default/all displays checked packs.
- Edited all-unchecked profile saves `None`.
- First Add Binary UI opens `AnalysisOptionsDialog`.
- Direct `addBinary(...)` remains registration-only.

- [ ] **Step 4: Run subagent-driven review after implementation**

After implementation and tests pass, run:

```text
superpowers:subagent-driven-development
```

Use one spec-compliance reviewer and one code-quality reviewer over the implementation diff.

Spec reviewer prompt:

```text
Review the current diff against docs/superpowers/plans/2026-05-10-effective-safety-onoff.md.
Focus only on spec compliance. Confirm:
- first Add Binary accepted path passes AnalysisOptionsDialog stringProtectionEnabled into runAnalyze
- addBinary remains registration-only
- RulePackSelectionMode legacy fallback is correct
- explicit None suppresses runtime and built-in rules
- Safety Assets all/selected/none UI semantics match the plan
- tests cover the required acceptance cases
Return APPROVED or ISSUES with file/line references.
```

Code-quality reviewer prompt:

```text
Review the current diff for concrete bugs, not style nits. Focus on:
- profile parse/save compatibility
- Qt signal recursion or stale m_rulePackSelectionEdited state
- accidental conversion of All to Selected on unedited OK
- row lookup correctness after addBinary reload
- tests that can pass without proving runtime behavior
Return APPROVED or ISSUES with file/line references.
```

---

## Acceptance Matrix

| Scenario | Expected result | Verification |
|---|---|---|
| Existing profile has no mode and empty `rule_pack_ids` | Loads as `All` | `safety_unit` legacy compatibility test |
| Existing profile has no mode and non-empty `rule_pack_ids` | Loads as `Selected` | `safety_unit` legacy compatibility test |
| Profile saves mode `none` | Reloads as `None` with empty ids | `safety_unit` save/reload test |
| `None` profile scans email/API token text | No findings | `safety_unit` explicit-none scan test |
| Safety Assets opens default/all profile | All valid rule packs visibly checked | `gui_smoke` dialog test |
| User unchecks to one rule pack | `Selected` + that id | `gui_smoke` dialog test |
| User unchecks all rule packs | `None` + empty ids | `gui_smoke` dialog test |
| First Add Binary with protection off | Strings remain unprotected | `gui_smoke` first-analysis off test |
| First Add Binary with protection on | At least one protected string appears | `gui_smoke` first-analysis on test |
| Direct `addBinary(...)` call | Registers only, no implicit analyze | Existing `gui_smoke` add binary subcase |

---

## Rollback Plan

If implementation has to be abandoned before commit:

```powershell
git restore -- include/aura/safety/string_safety.h src/core/safety/string_safety.cpp src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/unit/safety/safety_unit.cpp tests/integration/gui_smoke/gui_smoke.cpp
```

Do not remove the plan file unless the user explicitly asks to discard the planning work.

---

## Commit Plan

Use one commit after tests and reviews pass:

```powershell
git add include/aura/safety/string_safety.h src/core/safety/string_safety.cpp src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/unit/safety/safety_unit.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-effective-safety-onoff.md
git commit -m "feat: make safety toggles effective"
```

Do not commit until the user explicitly authorizes implementation and the requested verification passes.

---

## Self-Review

Spec coverage:
- First-analysis string protection On/Off is covered by `addBinaryAndAnalyze(...)` and GUI smoke tests.
- Rule-pack All/Selected/None is covered by safety unit tests and Safety Assets GUI tests.
- Backward compatibility is covered by missing-field parse tests.
- Built-in fallback suppression for explicit `None` is covered by direct scan and GUI smoke tests.

Placeholder scan:
- No TBD/TODO/fill-later steps.
- Every code-changing step includes concrete code snippets.

Type consistency:
- The production helper is consistently named `addBinaryAndAnalyze(...)`.
- Persistence field is consistently `rule_pack_selection_mode`.
- Mode strings are exactly `all`, `selected`, and `none`.

Autoplan conclusion:
- Product, Design, Engineering, and DX reviews all support the integrated plan.
- No unresolved decisions remain.
- Implementation is blocked only on explicit user authorization.
