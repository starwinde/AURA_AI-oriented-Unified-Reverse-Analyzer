# Analysis Options Safety Assets Entry and Folders Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the analysis selection step route users into Safety Assets for detailed safety configuration, and add explicit folder-open controls for token classification models and rule packs inside the Safety Assets dialog.

**Architecture:** Keep `AnalysisOptionsDialog` as the analysis-level chooser plus a simple string protection enable toggle. Remove the per-analysis "string protection mode" combo from that dialog and replace it with a "Safety Assets settings" action that opens the real `SafetySettingsDialog` through `MainWindow`, so profile edits are saved through the same path used by `Settings -> Safety Assets`. Add folder buttons directly in `SafetySettingsDialog`, backed by deterministic runtime asset paths.

**Tech Stack:** C++17, Qt Widgets, QDesktopServices/QUrl, QSettings, AURA safety asset registry, doctest GUI smoke tests, CMake/CTest.

---

## Current Facts

- `src/gui/analysis_options_dialog.cpp` currently has:
  - `analysisStringProtectionCheckBox`
  - `analysisStringProtectionModeCombo`
  - `stringProtectionMode()`
- `src/gui/main_window.cpp` currently consumes `dlg.stringProtectionMode()` from:
  - `onAddBinary()`
  - `onAnalyzeClicked()`
  - `onTableDoubleClicked()`
- `src/gui/main_window.cpp::onSafetySettings()` already contains the authoritative save path:
  - open `SafetySettingsDialog`
  - read `editedProfile()`
  - call `aura::safety::saveSafetyProfile(...)`
  - update active profile id
- `src/gui/safety_settings_dialog.cpp` already lists models and rule packs but does not expose "open this asset directory" controls inside the dialog.
- There are existing MainWindow menu actions for model asset folders, but the requested UX is inside the Safety Assets settings screen.

---

## Autoplan Review

### Product Review

- Verdict: hold scope, but correct the interaction model.
- Product decision: Analysis Options should not be the place where users decide detailed protection mechanics. It should answer "protect strings in this analysis?" and provide a direct route to the real Safety Assets profile editor.
- Product decision: the Safety Assets button must be available even when the master checkbox is off. Users often need to configure assets before deciding whether to enable protection for the current analysis.
- Product decision: folder buttons belong inside Safety Assets because that is where users discover missing token models or rule packs.

### Design Review

- Verdict: one compact Analysis Options dialog plus one real Safety Assets dialog is the right UX.
- Design decision: remove the local mode combo entirely. Do not leave a disabled or hidden mode selector behind.
- Design decision: label the new button as an action, not a setting value: `안전 자산 세부 설정...` / `Safety Assets settings...`.
- Design decision: in Safety Assets, put each folder button adjacent to the section it affects: model folder near the model list, rule-pack folder near the rule-pack list.

### Engineering Review

- Verdict: use the existing `SafetySettingsDialog` save path, but factor it into a reusable helper.
- Engineering decision: `MainWindow::openSafetySettingsDialog(...)` must be the only GUI save path for profile edits. `onSafetySettings()` and the Analysis Options button both call it.
- Engineering decision: do not make `AnalysisOptionsDialog` know about profile persistence, `saveSafetyProfile(...)`, or active profile ids. It only emits `safetyAssetsRequested()`.
- Engineering decision: keep `StringProtectionMode::ScanOnly` in core/CLI/test helpers, but remove it from Analysis Options. The GUI checkbox maps to `Off` or `Mask` for this slice.
- Engineering decision: use `QDesktopServices::openUrl(QUrl::fromLocalFile(...))` for folders, not Windows-only `explorer` commands.

### DX Review

- Verdict: add tests at the stable boundaries instead of relying on brittle nested modal automation.
- DX decision: GUI smoke should verify that `analysisSafetyAssetsButton` exists and emits `safetyAssetsRequested()`.
- DX decision: GUI smoke should verify that `MainWindow::openSafetySettingsDialog` remains covered through the existing `Settings -> Safety Assets` path and direct SafetySettingsDialog persistence tests. Avoid a fragile test that tries to click through two modal dialogs unless needed.
- DX decision: folder buttons must expose `assetPath` so tests can verify the resolved path without launching the OS file manager.

### Final Autoplan Decision

- Approved after edits below.
- No open user decision is required.
- Scope remains GUI-first; CLI behavior is unchanged except existing smoke tests must continue passing.

---

## Required Behavior

### Analysis Options

The analysis selection dialog must not present "문자열 보호 적용 / String protection mode" as a local detailed option.

It must instead show:

- analysis level radio buttons
- master checkbox: `문자열 마스킹/보호 스캔 사용`
- button: `안전 자산 세부 설정...`

Button behavior:

- Clicking the button opens `SafetySettingsDialog`.
- The button is always enabled, even when `문자열 마스킹/보호 스캔 사용` is unchecked.
- Saving in that dialog must use the same persistence path as `Settings -> Safety Assets`.
- Returning from Safety Assets must keep the Analysis Options dialog open.
- Pressing OK in Analysis Options still starts analysis.
- Pressing Cancel in Analysis Options still cancels registration/analysis.

Runtime behavior after this change:

- Checkbox off: pass `StringProtectionMode::Off`.
- Checkbox on: pass `StringProtectionMode::Mask` for now.
- Rule pack/model detail is controlled by the active Safety Assets profile.
- `ScanOnly` remains in core/CLI/programmatic test helpers, but it is no longer exposed as a local GUI choice in Analysis Options.

### Safety Assets Folder Controls

The Safety Assets dialog must expose folder-open controls for:

- token classification models directory
- rule packs directory

Directory rules:

- Runtime user asset root is `$AURA_HOME` if set.
- Otherwise runtime user asset root is `~/.aura`.
- Model directory is `<asset_root>/token-classification-models`.
- Rule pack directory is `<asset_root>/rule-packs`.
- Clicking each button creates the directory if missing, then opens it with the OS file manager.
- The UI must expose stable object names:
  - `safetyModelDirectoryButton`
  - `safetyRulePackDirectoryButton`
- Each button must store its resolved path in a Qt dynamic property named `assetPath` so GUI smoke can validate the target without launching Explorer.

---

## File Structure

### Analysis Options Dialog

- Modify `src/gui/analysis_options_dialog.h`
  - Remove `QComboBox* m_stringProtectionMode`.
  - Remove or deprecate `stringProtectionMode()` as a UI-mode reader.
  - Add signal `void safetyAssetsRequested();`.
  - Keep `stringProtectionEnabled()` for the master checkbox.

- Modify `src/gui/analysis_options_dialog.cpp`
  - Remove `analysisStringProtectionModeCombo`.
  - Add `QPushButton` with object name `analysisSafetyAssetsButton`.
  - Connect button click to `safetyAssetsRequested`.
  - Update hint text to say detailed rules/models are configured in Safety Assets.

### Main Window

- Modify `src/gui/main_window.h`
  - Add private helper:
    ```cpp
    bool openSafetySettingsDialog(QWidget* parentForDialog = nullptr);
    ```
  - Keep `onSafetySettings()` as the menu action wrapper.

- Modify `src/gui/main_window.cpp`
  - Move the body of `onSafetySettings()` into `openSafetySettingsDialog(...)`.
  - Connect `AnalysisOptionsDialog::safetyAssetsRequested` to that helper in every analysis-options path.
  - Replace `dlg.stringProtectionMode()` in GUI analysis paths with:
    ```cpp
    dlg.stringProtectionEnabled()
        ? aura::safety::StringProtectionMode::Mask
        : aura::safety::StringProtectionMode::Off
    ```

### Safety Assets Dialog

- Modify `src/gui/safety_settings_dialog.h`
  - Add private helper declarations:
    ```cpp
    QString runtimeSafetyAssetRoot() const;
    QString tokenClassificationModelsDir() const;
    QString rulePacksDir() const;
    bool openDirectory(const QString& path);
    ```

- Modify `src/gui/safety_settings_dialog.cpp`
  - Include:
    ```cpp
    #include <QDesktopServices>
    #include <QUrl>
    ```
  - Add directory buttons near the model and rule-pack sections.
  - Use `QDir().mkpath(path)` before opening.
  - Use `QDesktopServices::openUrl(QUrl::fromLocalFile(path))`.

### Tests

- Modify `tests/integration/gui_smoke/gui_smoke.cpp`
  - Update Analysis Options tests to expect no mode combo.
  - Add test that Safety Assets button exists and emits `safetyAssetsRequested()`.
  - Keep Safety Assets save behavior covered through direct dialog profile tests and the MainWindow settings helper path.
  - Add test that Safety Assets folder buttons expose correct object names and `assetPath` properties.
  - Keep existing ScanOnly runtime tests only for programmatic `MainWindow::analyzeBinaryAt(..., StringProtectionMode::ScanOnly)`.

---

## Detailed Execution Breakdown

| Slice | Scope | Gate |
| --- | --- | --- |
| 1 | Remove local Analysis Options mode combo and add Safety Assets button | `gui_smoke` builds |
| 2 | Route Analysis Options button through MainWindow save path | GUI smoke proves signal wiring; Safety Settings save tests still pass |
| 3 | Add Safety Assets folder buttons and path helpers | GUI smoke proves paths/object names |
| 4 | Rebuild actual GUI and smoke tests | `aura-gui`, `gui_smoke`, `cli_smoke` pass |

---

## Concrete Edit Map

Apply edits in this order so each failure points to one unfinished boundary:

1. `tests/integration/gui_smoke/gui_smoke.cpp`
   - Update existing subcase: `"analysis options dialog defaults string protection off"`.
   - Update existing subcase: `"safety model selection resets when switching profiles"`.
   - Do not add a new nested-modal click-through test.
2. `src/gui/analysis_options_dialog.h`
   - Remove mode-combo API.
   - Add `safetyAssetsRequested()` signal.
3. `src/gui/analysis_options_dialog.cpp`
   - Replace combo UI with action button.
4. `src/gui/main_window.h`
   - Add reusable helper declaration.
5. `src/gui/main_window.cpp`
   - Extract Safety Assets save path helper.
   - Connect the Analysis Options button in all three analysis-dialog call sites.
   - Replace deleted `dlg.stringProtectionMode()` calls.
6. `src/gui/safety_settings_dialog.h`
   - Add folder path/open helper declarations.
7. `src/gui/safety_settings_dialog.cpp`
   - Add folder buttons and helper implementations.
8. Build/test in the order listed in Task 4.

### Existing GUI Smoke Anchors

Use these existing anchors instead of creating duplicate broad tests:

- Analysis Options UI: subcase `"analysis options dialog defaults string protection off"` near the top of `tests/integration/gui_smoke/gui_smoke.cpp`.
- Safety Assets UI/profile behavior: subcase `"safety model selection resets when switching profiles"`.
- Programmatic `ScanOnly` coverage: subcase `"string protection scan-only records findings without masking"` must remain because `ScanOnly` still exists outside the Analysis Options UI.

### Exact GUI Runtime Mapping

Add this local helper inside `src/gui/main_window.cpp`, near the analysis-dialog call sites or as an unnamed-namespace helper if preferred:

```cpp
aura::safety::StringProtectionMode protectionModeFromDialog(
    const AnalysisOptionsDialog& dlg) {
    return dlg.stringProtectionEnabled()
               ? aura::safety::StringProtectionMode::Mask
               : aura::safety::StringProtectionMode::Off;
}
```

Then use:

```cpp
runAnalyze(row, dlg.selectedLevel(), protectionModeFromDialog(dlg));
```

or:

```cpp
addBinaryAndAnalyze(path, dlg.selectedLevel(), protectionModeFromDialog(dlg));
```

Do not inline three slightly different ternaries unless the surrounding file style strongly prefers it.

---

## Task 1: Replace Analysis Options Mode Combo with Safety Assets Button

**Files:**
- Modify: `src/gui/analysis_options_dialog.h`
- Modify: `src/gui/analysis_options_dialog.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Update failing GUI smoke expectation**

In the `"analysis options dialog defaults string protection off"` subcase, replace the mode-combo checks with:

```cpp
auto* modeCombo = dlg.findChild<QComboBox*>(
    QStringLiteral("analysisStringProtectionModeCombo"));
auto* safetyAssetsButton = dlg.findChild<QPushButton*>(
    QStringLiteral("analysisSafetyAssetsButton"));

CHECK(modeCombo == nullptr);
REQUIRE(safetyAssetsButton != nullptr);
CHECK_FALSE(dlg.stringProtectionEnabled());
CHECK(dlg.selectedLevel() == AURA_ANALYSIS_LEVEL_FULL);
checkbox->setChecked(true);
CHECK(dlg.stringProtectionEnabled());
CHECK(safetyAssetsButton->isEnabled());
checkbox->setChecked(false);
CHECK_FALSE(dlg.stringProtectionEnabled());
CHECK(safetyAssetsButton->isEnabled());
```

- [ ] **Step 2: Run GUI smoke build and confirm RED**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: compile or test failure because `analysisSafetyAssetsButton` does not exist yet.

- [ ] **Step 3: Change dialog header**

In `src/gui/analysis_options_dialog.h`:

```cpp
class QPushButton;
```

Remove:

```cpp
class QComboBox;
aura::safety::StringProtectionMode stringProtectionMode() const;
QComboBox*    m_stringProtectionMode = nullptr;
```

Add signal:

```cpp
signals:
    void safetyAssetsRequested();
```

Keep these public methods:

```cpp
AuraAnalysisLevel selectedLevel() const;
bool stringProtectionEnabled() const;
```

The header must no longer include `aura/safety/string_safety.h` after `stringProtectionMode()` is removed, unless another declaration still needs it.

- [ ] **Step 4: Change dialog implementation**

In `src/gui/analysis_options_dialog.cpp`:

Remove:

```cpp
#include <QComboBox>
```

Add:

```cpp
#include <QPushButton>
```

Replace the combo construction block with:

```cpp
auto* safetyAssetsButton = new QPushButton(
    ko ? QStringLiteral("안전 자산 세부 설정...")
       : QStringLiteral("Safety Assets settings..."),
    this);
safetyAssetsButton->setObjectName(
    QStringLiteral("analysisSafetyAssetsButton"));
form->addRow(ko ? QStringLiteral("보호 세부 설정:")
                : QStringLiteral("Protection settings:"),
             safetyAssetsButton);
connect(safetyAssetsButton, &QPushButton::clicked,
        this, &AnalysisOptionsDialog::safetyAssetsRequested);
```

Change hint text to:

```cpp
auto* protectionHint = new QLabel(
    ko ? QStringLiteral("켜면 현재 안전 자산 프로필의 모델/규칙 팩으로 문자열을 보호합니다.")
       : QStringLiteral("When enabled, this analysis uses the active Safety Assets profile."),
    this);
```

Delete the `AnalysisOptionsDialog::stringProtectionMode()` function.

After this task, `AnalysisOptionsDialog` should not mention:

```cpp
QComboBox
analysisStringProtectionModeCombo
StringProtectionMode
stringProtectionMode
```

- [ ] **Step 5: Verify GUI smoke builds**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build fails only if MainWindow still calls deleted `dlg.stringProtectionMode()`. That is fixed in Task 2.

---

## Task 2: Route Analysis Options Button Through MainWindow Safety Settings

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add helper declaration**

In `src/gui/main_window.h`, near `onSafetySettings()`:

```cpp
bool openSafetySettingsDialog(QWidget* parentForDialog = nullptr);
```

Keep it private. Tests should validate this path through stable public behavior and existing dialog tests, not by calling this helper directly.

- [ ] **Step 2: Extract save path helper**

Replace `MainWindow::onSafetySettings()` body with:

```cpp
void MainWindow::onSafetySettings() {
    openSafetySettingsDialog(this);
}
```

Add helper:

```cpp
bool MainWindow::openSafetySettingsDialog(QWidget* parentForDialog) {
    SafetySettingsDialog dlg(activeSafetyProfileId(),
                             parentForDialog ? parentForDialog : this);
    if (dlg.exec() != QDialog::Accepted) return false;
    const auto editedProfile = dlg.editedProfile();
    std::string diagnostic;
    if (!aura::safety::saveSafetyProfile(
            dlg.selectedProfileId().toStdString(), editedProfile, &diagnostic)) {
        QMessageBox::warning(
            this, tr("Safety profile save failed"),
            tr("Could not save safety profile: %1").arg(
                QString::fromStdString(diagnostic)));
        return false;
    }
    setActiveSafetyProfileId(dlg.selectedProfileId());
    return true;
}
```

This helper must be the only GUI code path that calls:

```cpp
aura::safety::saveSafetyProfile(...)
setActiveSafetyProfileId(...)
```

for Safety Assets profile edits.

- [ ] **Step 3: Connect Analysis Options dialog button in all GUI paths**

In `onAnalyzeClicked()`, after dialog construction:

```cpp
connect(&dlg, &AnalysisOptionsDialog::safetyAssetsRequested, this,
        [this, &dlg]() { openSafetySettingsDialog(&dlg); });
```

Apply the same connection in:

- `onTableDoubleClicked(...)`
- `onAddBinary()`

The connection must be made before `dlg.exec()`.

- [ ] **Step 4: Replace GUI dialog mode reads**

In those same three paths, replace:

```cpp
dlg.stringProtectionMode()
```

with the helper:

```cpp
protectionModeFromDialog(dlg)
```

- [ ] **Step 5: Add GUI smoke signal test**

In the Analysis Options subcase:

```cpp
int requested = 0;
QObject::connect(&dlg, &aura::gui::AnalysisOptionsDialog::safetyAssetsRequested,
                 [&requested]() { ++requested; });
safetyAssetsButton->click();
CHECK(requested == 1);
CHECK(safetyAssetsButton->isEnabled());
```

Do not call `openSafetySettingsDialog(...)` from this smoke test. The nested modal path is manually verified in Task 4 and the save semantics are already covered by `SafetySettingsDialog` profile tests.

- [ ] **Step 6: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Task 3: Add Folder Open Controls to Safety Assets Dialog

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke test for folder buttons**

In the `"safety model selection resets when switching profiles"` subcase, after `dlg` is constructed and after `modelList` / `rulePackList` are found, add:

```cpp
auto* modelDirButton = dlg.findChild<QPushButton*>(
    QStringLiteral("safetyModelDirectoryButton"));
auto* rulePackDirButton = dlg.findChild<QPushButton*>(
    QStringLiteral("safetyRulePackDirectoryButton"));

REQUIRE(modelDirButton != nullptr);
REQUIRE(rulePackDirButton != nullptr);
CHECK(modelDirButton->property("assetPath").toString().endsWith(
    QStringLiteral("/token-classification-models")) ||
      modelDirButton->property("assetPath").toString().endsWith(
    QStringLiteral("\\token-classification-models")));
CHECK(rulePackDirButton->property("assetPath").toString().endsWith(
    QStringLiteral("/rule-packs")) ||
      rulePackDirButton->property("assetPath").toString().endsWith(
    QStringLiteral("\\rule-packs")));
```

Also verify `$AURA_HOME` was honored:

```cpp
CHECK(modelDirButton->property("assetPath").toString().startsWith(
    QDir::cleanPath(homeSafetyRoot)));
CHECK(rulePackDirButton->property("assetPath").toString().startsWith(
    QDir::cleanPath(homeSafetyRoot)));
```

- [ ] **Step 2: Add helper declarations**

In `src/gui/safety_settings_dialog.h`:

```cpp
QString runtimeSafetyAssetRoot() const;
QString tokenClassificationModelsDir() const;
QString rulePacksDir() const;
bool openDirectory(const QString& path);
```

These helpers can stay private because tests validate the exposed button properties.

- [ ] **Step 3: Add includes**

In `src/gui/safety_settings_dialog.cpp`:

```cpp
#include <QDesktopServices>
#include <QUrl>
```

- [ ] **Step 4: Implement path helpers**

Add:

```cpp
QString SafetySettingsDialog::runtimeSafetyAssetRoot() const {
    const QByteArray env = qgetenv("AURA_HOME");
    if (!env.isEmpty()) return QDir::cleanPath(QString::fromLocal8Bit(env));
    return QDir::cleanPath(QDir::homePath() + QStringLiteral("/.aura"));
}

QString SafetySettingsDialog::tokenClassificationModelsDir() const {
    return QDir(runtimeSafetyAssetRoot()).filePath(
        QStringLiteral("token-classification-models"));
}

QString SafetySettingsDialog::rulePacksDir() const {
    return QDir(runtimeSafetyAssetRoot()).filePath(QStringLiteral("rule-packs"));
}

bool SafetySettingsDialog::openDirectory(const QString& path) {
    if (path.isEmpty()) return false;
    QDir().mkpath(path);
    return QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
```

- [ ] **Step 5: Add model directory button**

After `m_modelList` setup:

```cpp
auto* modelDirBtn = new QPushButton(
    textKoEn("모델 폴더 열기", "Open model folder"), detectionGroup);
modelDirBtn->setObjectName(QStringLiteral("safetyModelDirectoryButton"));
modelDirBtn->setProperty("assetPath", tokenClassificationModelsDir());
detectionLayout->addWidget(modelDirBtn);
connect(modelDirBtn, &QPushButton::clicked, this, [this]() {
    openDirectory(tokenClassificationModelsDir());
});
```

Place this before the existing model apply/clear button row so users see the folder entrypoint close to the model list.

- [ ] **Step 6: Add rule pack directory button**

After `m_rulePackList` setup:

```cpp
auto* rulePackDirBtn = new QPushButton(
    textKoEn("규칙 팩 폴더 열기", "Open rule pack folder"), detectionGroup);
rulePackDirBtn->setObjectName(QStringLiteral("safetyRulePackDirectoryButton"));
rulePackDirBtn->setProperty("assetPath", rulePacksDir());
detectionLayout->addWidget(rulePackDirBtn);
connect(rulePackDirBtn, &QPushButton::clicked, this, [this]() {
    openDirectory(rulePacksDir());
});
```

Place this before the existing rule-pack apply/clear button row so users see the folder entrypoint close to the rule-pack list.

- [ ] **Step 7: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Task 4: Final GUI/CLI Verification

**Files:**
- No new source changes.

- [ ] **Step 1: Rebuild actual targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura
cmake --build build-trim-gui --config Release --target aura-gui
cmake --build build-trim-gui --config Release --target cli_smoke
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: all builds succeed.

- [ ] **Step 2: Run focused tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: both PASS.

- [ ] **Step 3: Launch foreground GUI**

Run:

```powershell
& 'C:\Users\21m15\OneDrive\바탕 화면\AURA\build-trim-gui\src\gui\Release\aura-gui.exe'
```

Manual checks:

1. Use `File -> Add Binary`.
2. Confirm Analysis Options has no `문자열 보호 적용` combo.
3. Confirm `안전 자산 세부 설정...` opens Safety Assets.
4. Confirm Safety Assets has model folder and rule-pack folder buttons.
5. Confirm OK in Safety Assets returns to Analysis Options.
6. Confirm OK in Analysis Options starts analysis.
7. Confirm checking `문자열 마스킹/보호 스캔 사용` still uses the active Safety Assets profile.

---

## Stop Conditions

- Stop if the Analysis Options dialog still exposes `analysisStringProtectionModeCombo`.
- Stop if Safety Assets opened from Analysis Options does not save through `saveSafetyProfile(...)`.
- Stop if folder buttons launch hard-coded Explorer commands instead of `QDesktopServices::openUrl(...)`.
- Stop if `aura-gui` cannot rebuild because an old `aura-gui.exe` process is still running; terminate the stale process and rebuild once.

---

## Acceptance Criteria

- Analysis Options no longer has a local string protection mode combo.
- Analysis Options has a Safety Assets settings button.
- The Safety Assets button opens the real Safety Assets dialog and saves profile edits.
- Safety Assets dialog has model-folder and rule-pack-folder open controls.
- Folder paths honor `$AURA_HOME` or fallback to `~/.aura`.
- GUI and CLI smoke tests still pass.
- Actual `aura-gui.exe` is rebuilt and manually launched.

---

## Self-Review

- Spec coverage: the request has two parts. Analysis Options routing is covered by Tasks 1-2. Directory-open controls are covered by Task 3. Verification is covered by Task 4.
- Placeholder scan: no placeholder markers are used.
- Type consistency: the plan keeps `StringProtectionMode` for runtime/API compatibility but removes the local GUI mode combo from Analysis Options.
