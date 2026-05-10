# Safety Assets Localization and Rule Pack Selection Plan

## Goal

Improve the Safety Assets dialog so Korean UI mode is consistently localized and rule packs can be selected/removed from the active profile like token classification models.

## Current State

- `SafetySettingsDialog` uses mixed Korean and English labels.
- The window title, group titles, row labels, summary text, empty-state text, and status messages are mostly English.
- Model rows are user-checkable and there are buttons for `선택 적용` / `선택 해제`.
- Rule pack rows show checked state from the profile, but they are not user-checkable because `addAssetRows()` only makes `m_modelList` user-checkable.
- `editedProfile()` currently applies only model selection changes; it does not write rule pack selection changes back into the returned `SafetyProfile`.
- Eval datasets are display/validation assets, not runtime masking controls. Keep them read-only for this slice unless the user explicitly asks to edit evaluation config too.

## Scope

### In scope

1. Localize Safety Assets dialog text using the existing `ui/language` setting.
2. Make rule pack rows checkable in the dialog.
3. Add rule pack apply/remove buttons equivalent to the model buttons.
4. Persist edited rule pack selection through `editedProfile()` and `saveSafetyProfile()`.
5. Add GUI smoke coverage for:
   - Korean UI labels/status text.
   - Rule pack selection changes reflected in `editedProfile()`.
   - Profile switching resets rule pack checks to the selected profile defaults.

### Not in scope

1. Editing `Eval datasets` in this slice.
2. Downloading/removing runtime assets from disk.
3. Changing the safety scan engine.
4. Changing the new per-analysis masking toggle.
5. Adding a full Eval Runner UI.

## Proposed UX

In Korean UI mode:

- Window title: `안전 자산`
- `Profile` -> `프로필`
- `Active profile` -> `활성 프로필`
- `Selection` -> `선택`
- `Detection` -> `탐지`
- `Token classification model` -> `토큰 분류 모델`
- `Rule packs` -> `규칙 팩`
- `Evaluation` -> `평가`
- `Profile is ready.` -> `프로필을 사용할 수 있습니다.`
- `No assets found` -> `자산을 찾을 수 없습니다`

Rule packs should behave as follows:

- Checked rule pack = included in active profile.
- Unchecked rule pack = removed from active profile.
- `선택 적용` checks the currently selected row.
- `선택 해제` unchecks the currently selected row.
- Unlike models, rule packs are multi-select in meaning: more than one can remain checked.
- If every rule pack is unchecked, the profile is valid only if the existing core behavior treats empty `rule_pack_ids` as "load every runtime rule pack." If that semantic is still true, surface the behavior in a hint. If not, validation should warn that no rule packs are selected.

## Implementation Plan

### Task 1: Add localization helpers

Files:

- `src/gui/safety_settings_dialog.cpp`

Add a local `useKoreanUi()` helper matching the pattern already used in `analysis_options_dialog.cpp`.

Use it in the constructor and status/summary methods instead of hard-coded English strings.

### Task 2: Make rule packs editable

Files:

- `src/gui/safety_settings_dialog.h`
- `src/gui/safety_settings_dialog.cpp`

Add:

- `std::vector<std::string> selectedRulePackIds() const;`
- `void applyRulePackSelectionToProfile(aura::safety::SafetyProfile& profile) const;`

Update `editedProfile()` so it applies both model and rule pack selections.

Change `addAssetRows()` so both `m_modelList` and `m_rulePackList` rows are user-checkable and store `Qt::UserRole` ids.

Add rule pack apply/remove buttons with object names:

- `safetyRulePackAddButton`
- `safetyRulePackRemoveButton`

Do not enforce single-selection for rule packs. Keep `updateModelSelectionFromChecked()` model-only.

### Task 3: Keep eval datasets read-only but localized

Files:

- `src/gui/safety_settings_dialog.cpp`

Keep `m_evalDatasetList` non-user-checkable.

Localize the section label and add a short hint:

- Korean: `평가 데이터셋은 탐지 성능 검증용이며, 분석 중 실시간 마스킹 규칙은 아닙니다.`
- English: `Eval datasets are for safety-filter evaluation, not live masking rules.`

### Task 4: Add GUI smoke coverage

Files:

- `tests/integration/gui_smoke/gui_smoke.cpp`

Extend the existing `SafetySettingsDialog` test that already manipulates model selection.

Add assertions for:

- Korean labels/status where `ui/language` is set to Korean.
- `safetyRulePackList` exists.
- rule pack rows expose ids in `Qt::UserRole`.
- checking/unchecking rule packs changes `dlg.editedProfile().rule_pack_ids`.
- model selection remains single-select.
- rule pack selection remains multi-select.
- switching profile resets rule pack checks to profile defaults.

### Task 5: Verify

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

## Autoplan Review

### Product

This is the right next step after making masking explicitly opt-in. Users now need a clear place to configure what happens when they opt in. Rule packs are part of live detection, so leaving them read-only makes the dialog feel misleading.

### Design

Keep one dialog. Do not add a separate rule-pack manager yet. The least surprising model is: model selection is single-choice, rule pack selection is multi-choice, eval datasets remain informational.

### Engineering

The risky part is preserving the model-only single-selection behavior while allowing rule packs to be multi-checked. Avoid a generic "selected asset ids" abstraction that accidentally applies model semantics to rule packs.

### DX / Testing

The existing GUI smoke test already covers model switching and is the right anchor. Add rule-pack assertions there rather than creating a new heavyweight fixture.

## Decisions

| Decision | Choice | Reason |
|---|---|---|
| Eval datasets editable now? | No | They are evaluation assets, not live masking controls. Editing them is a separate Eval Runner/Profile UX task. |
| Rule pack selection cardinality | Multi-select | Live detection should allow combining `korean-sensitive` and `secret-api-key`. |
| Empty rule pack behavior | Verify before implementation | Current code comments suggest empty means all runtime rule packs, but UI copy must match actual behavior. |
| Language support | Korean/English via existing setting | Matches current GUI language pattern and avoids hard-coded Korean in English UI. |

## Precondition

`main` is currently ahead of `origin/main` by one commit from the previous string-protection toggle work. Before implementing this plan, either push `main` or create the next feature branch from the local `main` knowingly.
