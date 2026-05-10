# String Protection Toggle Plan

## Goal

Move string masking/protection from implicit GUI activation to an explicit per-analysis choice.

The toggle should live in the analysis options dialog, between the selected binary path and analysis level selection.

## Current behavior

- `AnalysisOptionsDialog` currently only lets the user choose the Rizin analysis level.
- GUI analysis entry points show that dialog after binary selection and before `runAnalyze`.
- `MainWindow::runAnalyze` currently always scans strings with the active safety profile, builds masked/protected values, refreshes protected export values, and persists protection rows.
- Because that happens unconditionally, GUI analysis can look like masking is enabled by default.

## Proposed UX

Add a checkbox to `AnalysisOptionsDialog`:

- Label: `문자열 마스킹/보호 스캔 사용`
- Position: directly below the binary path field, above the `분석 단계` group.
- Default: unchecked.
- Hint: enabling it runs string safety scanning and creates masked/protected values for this analysis run.

This keeps the decision at the exact point where the user already confirms:

1. target binary
2. masking/protection enabled or disabled
3. analysis depth

## Implementation plan

1. Extend `src/gui/analysis_options_dialog.h/.cpp`.
   - Add `QCheckBox* m_enableStringProtection`.
   - Add `bool stringProtectionEnabled() const`.
   - Default the checkbox to `false`.

2. Thread the option through GUI analyze entry points in `src/gui/main_window.cpp`.
   - `onAnalyzeClicked()` passes `dlg.stringProtectionEnabled()`.
   - `onTableDoubleClicked()` passes `dlg.stringProtectionEnabled()`.
   - Add a private `runAnalyze(row, level, enableStringProtection)` path.

3. Preserve compatibility for non-dialog callers.
   - Keep existing `analyzeBinaryAt(row, level)` available.
   - Add an explicit overload or helper for `analyzeBinaryAt(row, level, enableStringProtection)`.
   - Existing tests/RPC-style callers can keep their current behavior until they opt into the new flag.

4. Gate the string protection pipeline.
   - When enabled: keep the current scan/mask/persist behavior.
   - When disabled:
     - do not call `scanStringWithRulePacks`;
     - do not build masked/protected values;
     - do not apply stored protection overrides;
     - do not persist protection rows for the run;
     - set display/export/protected values to the original string content.

5. Make disabled state visible.
   - Status text should distinguish `Safety: disabled for this analysis` from configured-but-enabled profiles.

## Test plan

1. Build GUI smoke target.
   - `cmake --build build-trim-gui --config Release --target gui_smoke`

2. Run GUI smoke tests.
   - `ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure`

3. Add/adjust tests where practical.
   - Dialog default is unchecked.
   - Analysis with protection disabled leaves string rows unmasked.
   - Analysis with protection enabled preserves the current masking behavior.

## Autoplan review notes

- CEO/Product: good fit. It puts a sensitive behavior at the point of user intent instead of hiding it behind default analysis.
- Design: low UI risk. The dialog already has a binary-to-analysis flow, so one checkbox there is natural.
- Engineering: low-to-medium risk. The main risk is accidentally applying stored protection overrides even when the new flag is off.
- DX/Test: keep old helper APIs stable and add an explicit option for new tests.

## Open decision

Default should be OFF for the GUI. Remembering the last checked state is intentionally excluded for now because that can recreate the same "auto-enabled" surprise after one enabled run.
