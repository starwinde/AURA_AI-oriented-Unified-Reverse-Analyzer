# Effective Rule Pack Selection Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make Safety Assets rule-pack checkboxes actually control which rule packs are used by string protection, including the ability to disable all rule packs.

**Architecture:** Add an explicit rule-pack selection mode to `SafetyProfile` so legacy/default empty `rule_pack_ids` can still mean “all packs,” while the GUI can save “selected subset” or “none selected” unambiguously. The safety engine must use this mode when loading effective rules, and the GUI must render default/all profiles as checked rows instead of visually empty rows.

**Tech Stack:** C++17, AURA safety core, cJSON profile persistence, Qt Widgets, GUI smoke tests, focused safety unit tests if available.

---

## File Structure

- Modify: `include/aura/safety/string_safety.h`
  - Add `RulePackSelectionMode`.
  - Add `rule_pack_selection_mode` to `SafetyProfile`.
- Modify: `src/core/safety/string_safety.cpp`
  - Parse/save the new profile field.
  - Preserve backward compatibility for existing profiles.
  - Apply mode in `effectiveRules(...)` / runtime rule loading.
- Modify: `src/gui/safety_settings_dialog.h`
  - Track whether the user edited rule-pack checks in this dialog.
- Modify: `src/gui/safety_settings_dialog.cpp`
  - Render “all mode” as all valid rule packs checked.
  - Save checked subset as selected mode.
  - Save zero checked rows as none mode.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add GUI coverage proving checked rows match default/all mode and editedProfile carries mode + ids.
  - Add end-to-end analysis coverage proving disabled rule packs produce no rule-pack findings.
- Optional modify: focused safety unit tests under `tests/` if an existing safety unit target already covers profile parsing/rule scanning.

---

## Root Cause

Current UI work only changes `SafetyProfile.rule_pack_ids`, but core rule loading treats an empty vector as “accept every rule pack”:

```cpp
std::vector<std::string> wanted = profile.rule_pack_ids;
const bool acceptAll = wanted.empty();
```

`loadDefaultSafetyProfile()` also documents this legacy contract:

```cpp
// Empty rule_pack_ids means "load every runtime rule pack"; if none
// exist, the engine falls back to the built-in MVP rules.
```

Therefore, a GUI state of “all rows unchecked” cannot currently mean “all rule packs off.” It is serialized as empty `rule_pack_ids`, then interpreted by the engine as “all rule packs on.”

---

## Compatibility Decision

Do not change legacy `rule_pack_ids.empty()` globally to mean “none.” That would silently weaken existing/default profiles.

Use an explicit mode:

```cpp
enum class RulePackSelectionMode {
    All,
    Selected,
    None,
};
```

Persistence field:

```json
"rule_pack_selection_mode": "all" | "selected" | "none"
```

Backward compatibility:

- Missing field + empty `rule_pack_ids` -> `All`
- Missing field + non-empty `rule_pack_ids` -> `Selected`
- `"all"` ignores `rule_pack_ids` during runtime loading
- `"selected"` uses only listed `rule_pack_ids`
- `"none"` loads no runtime rule packs and must not fall back to built-in MVP rules

---

### Task 1: Add Core Profile Mode Tests

**Files:**
- Modify an existing safety unit test file if one already exists.
- If no focused safety unit file exists, modify `tests/integration/gui_smoke/gui_smoke.cpp` only in later tasks and skip this task.

- [ ] **Step 1: Locate focused safety tests**

Run:

```powershell
Get-ChildItem -Path .\tests -Recurse -Filter *.cpp |
  Select-String -Pattern 'SafetyProfile|scanStringWithRulePacks|rule_pack_ids'
```

Expected: identify the smallest safety-core test target, if present.

- [ ] **Step 2: Add profile parse compatibility assertions**

Add tests equivalent to:

```cpp
CHECK(loadProfileFromJson(R"({"rule_pack_ids":[]})").rule_pack_selection_mode
      == RulePackSelectionMode::All);
CHECK(loadProfileFromJson(R"({"rule_pack_ids":["korean-sensitive"]})").rule_pack_selection_mode
      == RulePackSelectionMode::Selected);
CHECK(loadProfileFromJson(R"({"rule_pack_selection_mode":"none","rule_pack_ids":[]})").rule_pack_selection_mode
      == RulePackSelectionMode::None);
```

Use the actual existing test helpers instead of inventing a public parser if tests already have one.

- [ ] **Step 3: Add scanning behavior assertions**

Create a test profile with:

```cpp
SafetyProfile profile;
profile.rule_pack_selection_mode = RulePackSelectionMode::None;
profile.rule_pack_ids = {};
```

Then assert:

```cpp
CHECK(scanStringWithRulePacks("alice@example.com", profile).empty());
```

This test must fail before the implementation because current `effectiveRules(profile)` falls back to built-in rules.

---

### Task 2: Implement Rule Pack Selection Mode in Core

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`

- [ ] **Step 1: Add the enum and field**

In `include/aura/safety/string_safety.h`, before `struct SafetyProfile`, add:

```cpp
enum class RulePackSelectionMode {
    All,
    Selected,
    None,
};
```

Inside `SafetyProfile`, add:

```cpp
    RulePackSelectionMode rule_pack_selection_mode =
        RulePackSelectionMode::All;
```

- [ ] **Step 2: Add string conversion helpers**

In `src/core/safety/string_safety.cpp` anonymous namespace, add:

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

const char* rulePackSelectionModeString(RulePackSelectionMode mode) {
    switch (mode) {
    case RulePackSelectionMode::None: return "none";
    case RulePackSelectionMode::Selected: return "selected";
    case RulePackSelectionMode::All: return "all";
    }
    return "all";
}
```

- [ ] **Step 3: Parse the new field with legacy fallback**

In the profile JSON parser, after:

```cpp
    out.rule_pack_ids = jsonStringArray(root, "rule_pack_ids");
```

add:

```cpp
    out.rule_pack_selection_mode = parseRulePackSelectionMode(
        jsonString(root, "rule_pack_selection_mode"),
        out.rule_pack_ids);
```

- [ ] **Step 4: Save the new field**

In `saveSafetyProfile(...)`, before writing `rule_pack_ids`, add:

```cpp
    cJSON_AddStringToObject(
        root, "rule_pack_selection_mode",
        rulePackSelectionModeString(profile.rule_pack_selection_mode));
```

- [ ] **Step 5: Apply mode in runtime rule loading**

Change `loadRulesFromRoot(...)` logic from:

```cpp
    std::vector<std::string> wanted = profile.rule_pack_ids;
    const bool acceptAll = wanted.empty();
```

to:

```cpp
    if (profile.rule_pack_selection_mode == RulePackSelectionMode::None) {
        return out;
    }
    std::vector<std::string> wanted = profile.rule_pack_ids;
    const bool acceptAll =
        profile.rule_pack_selection_mode == RulePackSelectionMode::All;
```

- [ ] **Step 6: Prevent built-in fallback for explicit none**

Change `effectiveRules(...)` from:

```cpp
std::vector<Rule> effectiveRules(const SafetyProfile& profile) {
    auto rules = loadRuntimeRules(profile);
    if (!rules.empty()) return rules;
    return builtinRules();
}
```

to:

```cpp
std::vector<Rule> effectiveRules(const SafetyProfile& profile) {
    if (profile.rule_pack_selection_mode == RulePackSelectionMode::None) {
        return {};
    }
    auto rules = loadRuntimeRules(profile);
    if (!rules.empty()) return rules;
    return builtinRules();
}
```

- [ ] **Step 7: Build focused targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 3: Fix Safety Assets Dialog Semantics

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`

- [ ] **Step 1: Track user edits**

In `SafetySettingsDialog` private fields, add:

```cpp
    bool m_rulePackSelectionEdited = false;
```

- [ ] **Step 2: Mark rule-pack changes as user edits**

In the `m_rulePackList` `itemChanged` connection, change:

```cpp
    connect(m_rulePackList, &QListWidget::itemChanged, this, [this]() {
        updateSummary();
    });
```

to:

```cpp
    connect(m_rulePackList, &QListWidget::itemChanged, this, [this]() {
        m_rulePackSelectionEdited = true;
        updateSummary();
    });
```

In add/remove rule button handlers, set the flag before `updateSummary()`:

```cpp
        m_rulePackSelectionEdited = true;
```

- [ ] **Step 3: Render all-mode profiles as checked rows**

Add helper:

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

In `updateSummary(...)`, compute display ids:

```cpp
    std::vector<std::string> checkedRulePacks;
    if (!resetSelection && m_rulePackSelectionEdited) {
        checkedRulePacks = checkedIdsFromList(m_rulePackList);
    } else if (workingProfile.rule_pack_selection_mode
               == aura::safety::RulePackSelectionMode::All) {
        checkedRulePacks = validIdsFromRefs(m_registry.rule_packs);
    } else if (workingProfile.rule_pack_selection_mode
               == aura::safety::RulePackSelectionMode::None) {
        checkedRulePacks = {};
    } else {
        checkedRulePacks = workingProfile.rule_pack_ids;
    }
```

On profile switch (`resetSelection == true`), also reset:

```cpp
    if (resetSelection) {
        m_rulePackSelectionEdited = false;
    }
```

- [ ] **Step 4: Save selected/none mode from the dialog**

Change `applyRulePackSelectionToProfile(...)` to:

```cpp
void SafetySettingsDialog::applyRulePackSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    const auto ids = selectedRulePackIds();
    profile.rule_pack_ids = ids;
    profile.rule_pack_selection_mode =
        ids.empty() ? aura::safety::RulePackSelectionMode::None
                    : aura::safety::RulePackSelectionMode::Selected;
}
```

This means once a user edits the dialog, the saved state is explicit. If the product later needs an “Auto/all packs” command, add a separate button or tri-state control in a later slice.

- [ ] **Step 5: Update summary count**

Keep the summary count based on visible checked ids:

```cpp
                 countLabel(checkedRulePacks.size()),
```

Expected: default/all profile no longer appears as “0 rule packs.”

---

### Task 4: Add GUI Smoke Coverage

**Files:**
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Update Safety Settings rule-pack test for all mode**

In the Safety Settings dialog test fixture, set default profile to explicit all:

```cpp
        defaultProfile.rule_pack_selection_mode =
            aura::safety::RulePackSelectionMode::All;
        defaultProfile.rule_pack_ids = {};
```

Then assert default profile renders both available rule packs as checked:

```cpp
        switchProfile(QStringLiteral("default"));
        requireCheckedRulePacks({"rule-alpha", "rule-beta"});
```

- [ ] **Step 2: Assert subset selection mode**

After unchecking `rule-alpha`, assert:

```cpp
        auto edited = dlg.editedProfile();
        CHECK(edited.rule_pack_selection_mode
              == aura::safety::RulePackSelectionMode::Selected);
        CHECK(sortedEditedRulePackIds()
              == std::vector<std::string>{"rule-beta"});
```

- [ ] **Step 3: Assert none selection mode**

After unchecking the final checked rule pack, assert:

```cpp
        edited = dlg.editedProfile();
        CHECK(edited.rule_pack_selection_mode
              == aura::safety::RulePackSelectionMode::None);
        CHECK(sortedEditedRulePackIds() == std::vector<std::string>{});
```

- [ ] **Step 4: Add runtime behavior test**

Add a subcase near existing string protection tests:

```cpp
    SUBCASE("disabled rule packs produce no rule-pack findings") {
        // Build or save a profile with rule_pack_selection_mode=None,
        // set it active, analyze stringFixture with protection enabled,
        // then assert no string has rule-pack protection fields.
    }
```

Use existing `saveSafetyProfile(...)` and QSettings helpers in the test. Concrete expected checks:

```cpp
        for (const auto& s : window.stringList()) {
            CHECK_FALSE(s.hasProtection);
            CHECK(s.maskedContent.isEmpty());
            CHECK(s.protectedValue == s.content);
            CHECK(s.protectionSummary.isEmpty());
        }
```

- [ ] **Step 5: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `1/1` tests pass.

---

### Task 5: Reconcile Existing Dirty UI Fix

**Files:**
- Modify: `src/gui/safety_settings_dialog.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Do not keep the current “empty ids means off” UI-only fix alone**

The current dirty working-tree fix makes `editedProfile().rule_pack_ids` empty, but without the core mode from this plan the engine still interprets that as all rule packs on.

When implementing this plan, either:

- replace the current dirty fix with the explicit `RulePackSelectionMode::None` behavior, or
- keep the empty-id UI behavior only after the mode field is added and saved.

- [ ] **Step 2: Re-run the subagent review**

After implementation and tests pass, run:

```text
superpowers:subagent-driven-development
```

Use one spec reviewer and one code-quality reviewer, same as the previous safety rule-pack slice.

---

## Self-Review

Spec coverage:
- Individual rule-pack on/off: represented by `Selected` mode + listed ids.
- All rule packs enabled: represented by `All` mode.
- All rule packs disabled: represented by `None` mode, with no built-in fallback.
- Existing/default profiles: preserved by missing-field fallback.
- GUI confusion: default/all no longer renders as zero checked rows.

Placeholder scan:
- No TBD/TODO/fill-later steps.
- Every code-changing step includes concrete code snippets.

Type consistency:
- `RulePackSelectionMode` is used consistently in core, GUI, and tests.
- Persistence string values are exactly `all`, `selected`, and `none`.

Risk notes:
- This changes profile schema. Backward compatibility is mandatory.
- `None` must suppress built-in fallback, otherwise “all off” still leaks built-in detections.
- If MCP/export paths call `loadDefaultSafetyProfile()` directly, they will still default to all packs by design; changing those defaults is outside this slice.
