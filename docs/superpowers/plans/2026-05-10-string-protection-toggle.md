# String Protection Toggle Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add an explicit per-analysis GUI checkbox so string masking/protection is no longer implicitly enabled from the analysis options dialog.

**Architecture:** The analysis dialog owns the user's intent. `MainWindow` threads that intent into analysis and gates only the string protection pipeline, leaving binary analysis, functions, xrefs, symbols, CFG, decompile, and disassembly behavior unchanged.

**Tech Stack:** C++17, Qt Widgets, existing AURA GUI smoke tests, CMake/CTest.

---

## File Structure

- Modify: `src/gui/analysis_options_dialog.h`
  - Add the checkbox field and public getter.
- Modify: `src/gui/analysis_options_dialog.cpp`
  - Render the checkbox between the binary path and analysis level group.
  - Default it to unchecked.
- Modify: `src/gui/main_window.h`
  - Add an explicit `analyzeBinaryAt(row, level, enableStringProtection)` overload.
  - Change private `runAnalyze` to receive the flag.
- Modify: `src/gui/main_window.cpp`
  - Pass the dialog checkbox value from GUI entry points.
  - Gate scan/mask/override/persist behavior on the flag.
  - Preserve the old two-argument `analyzeBinaryAt` behavior for existing tests.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add a smoke test for the dialog default.
  - Add a smoke test for explicit disabled analysis.

---

### Task 1: Add Dialog Checkbox API

**Files:**
- Modify: `src/gui/analysis_options_dialog.h`
- Modify: `src/gui/analysis_options_dialog.cpp`
- Test later in Task 4.

- [ ] **Step 1: Update the header**

In `src/gui/analysis_options_dialog.h`, add a forward declaration and getter:

```cpp
class QCheckBox;
class QRadioButton;
```

Change the public section to:

```cpp
    AuraAnalysisLevel selectedLevel() const;
    bool stringProtectionEnabled() const;
```

Change the private section to:

```cpp
    QCheckBox*    m_enableStringProtection = nullptr;
    QRadioButton* m_radioFull  = nullptr;
    QRadioButton* m_radioQuick = nullptr;
    QRadioButton* m_radioAdvanced = nullptr;
```

- [ ] **Step 2: Update the dialog implementation includes**

In `src/gui/analysis_options_dialog.cpp`, add:

```cpp
#include <QCheckBox>
```

- [ ] **Step 3: Render the checkbox after the binary path**

In the constructor, immediately after:

```cpp
    outer->addLayout(form);
```

insert:

```cpp
    m_enableStringProtection = new QCheckBox(
        ko ? QStringLiteral("문자열 마스킹/보호 스캔 사용")
           : QStringLiteral("Enable string masking/protection scan"),
        this);
    m_enableStringProtection->setChecked(false);
    outer->addWidget(m_enableStringProtection);

    auto* protectionHint = new QLabel(
        ko ? QStringLiteral("켜면 이번 분석에서 문자열 안전 스캔과 마스킹 후보를 생성합니다.")
           : QStringLiteral("When enabled, this analysis generates string safety findings and masked values."),
        this);
    protectionHint->setStyleSheet(QStringLiteral("color: gray;"));
    protectionHint->setWordWrap(true);
    outer->addWidget(protectionHint);
```

- [ ] **Step 4: Add the getter**

After `selectedLevel()` in `src/gui/analysis_options_dialog.cpp`, add:

```cpp
bool AnalysisOptionsDialog::stringProtectionEnabled() const {
    return m_enableStringProtection && m_enableStringProtection->isChecked();
}
```

- [ ] **Step 5: Build just enough to catch header/include errors**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds, or fails only on later tasks not yet implemented if this task is being run out of order.

---

### Task 2: Thread the Flag Through MainWindow

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`

- [ ] **Step 1: Add the public overload**

In `src/gui/main_window.h`, near the existing public test helper:

```cpp
    bool analyzeBinaryAt(int row, AuraAnalysisLevel level);
```

change to:

```cpp
    bool analyzeBinaryAt(int row, AuraAnalysisLevel level);
    bool analyzeBinaryAt(int row,
                         AuraAnalysisLevel level,
                         bool enableStringProtection);
```

- [ ] **Step 2: Change the private runAnalyze signature**

In `src/gui/main_window.h`, replace:

```cpp
    bool runAnalyze(int row, AuraAnalysisLevel level);
```

with:

```cpp
    bool runAnalyze(int row,
                    AuraAnalysisLevel level,
                    bool enableStringProtection);
```

- [ ] **Step 3: Update the implementation signature**

In `src/gui/main_window.cpp`, replace:

```cpp
bool MainWindow::runAnalyze(int row, AuraAnalysisLevel level) {
```

with:

```cpp
bool MainWindow::runAnalyze(int row,
                            AuraAnalysisLevel level,
                            bool enableStringProtection) {
```

- [ ] **Step 4: Preserve existing two-argument behavior**

Replace the current `analyzeBinaryAt` implementation:

```cpp
bool MainWindow::analyzeBinaryAt(int row, AuraAnalysisLevel level) {
    return runAnalyze(row, level);
}
```

with:

```cpp
bool MainWindow::analyzeBinaryAt(int row, AuraAnalysisLevel level) {
    return analyzeBinaryAt(row, level, true);
}

bool MainWindow::analyzeBinaryAt(int row,
                                 AuraAnalysisLevel level,
                                 bool enableStringProtection) {
    return runAnalyze(row, level, enableStringProtection);
}
```

This keeps existing GUI smoke tests and RPC-style internal tests compatible while adding an explicit disabled path.

- [ ] **Step 5: Pass the dialog value from GUI analyze button**

In `onAnalyzeClicked()`, replace:

```cpp
    runAnalyze(row, dlg.selectedLevel());
```

with:

```cpp
    runAnalyze(row, dlg.selectedLevel(), dlg.stringProtectionEnabled());
```

- [ ] **Step 6: Pass the dialog value from double-click analyze**

In `onTableDoubleClicked()`, replace:

```cpp
    runAnalyze(idx.row(), dlg.selectedLevel());
```

with:

```cpp
    runAnalyze(idx.row(), dlg.selectedLevel(), dlg.stringProtectionEnabled());
```

- [ ] **Step 7: Build to catch signature mismatches**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: compile reaches `gui_smoke` without unresolved `runAnalyze` overload errors.

---

### Task 3: Gate the String Protection Pipeline

**Files:**
- Modify: `src/gui/main_window.cpp`

- [ ] **Step 1: Replace unconditional safety profile setup**

In `MainWindow::runAnalyze`, replace:

```cpp
        const auto safetyProfile = activeSafetyProfile();
        updateSafetyStatusText();
```

with:

```cpp
        aura::safety::SafetyProfile safetyProfile;
        if (enableStringProtection) {
            safetyProfile = activeSafetyProfile();
            updateSafetyStatusText();
        } else if (m_safetyStatus) {
            m_safetyStatus->setText(
                useKoreanUi()
                    ? QStringLiteral("Safety: 이번 분석에서 비활성화")
                    : QStringLiteral("Safety: disabled for this analysis"));
        }
```

- [ ] **Step 2: Wrap scan and masking logic**

Inside the string loop, replace the current block starting at:

```cpp
            auto findings = aura::safety::scanStringWithRulePacks(
                s.content.toStdString(), safetyProfile);
```

and ending at:

```cpp
            refreshProtectedValue(s);
```

with:

```cpp
            if (enableStringProtection) {
                auto findings = aura::safety::scanStringWithRulePacks(
                    s.content.toStdString(), safetyProfile);
                const auto protectedView =
                    aura::safety::buildProtectedStringView(s.content.toStdString(),
                                                           std::string(),
                                                           std::move(findings));
                s.maskedContent = QString::fromStdString(protectedView.masked);
                s.protectedValue =
                    QString::fromStdString(protectedView.protected_value);
                s.hasProtection = !protectedView.findings.empty();
                for (const auto& f : protectedView.findings) {
                    GuiStringRecord::ProtectionFinding gf;
                    gf.detectorId = QString::fromStdString(f.detector_id);
                    gf.kind = QString::fromStdString(f.kind);
                    gf.startOffset = static_cast<int>(f.start);
                    gf.endOffset = static_cast<int>(f.end);
                    gf.confidence = f.confidence;
                    gf.maskToken = QString::fromStdString(f.mask_token);
                    s.findings.push_back(std::move(gf));
                }
                if (s.hasProtection) {
                    QStringList tokens;
                    for (const auto& f : s.findings) tokens << f.maskToken;
                    tokens.removeDuplicates();
                    s.protectionSummary =
                        useKoreanUi()
                            ? QStringLiteral("마스킹 가능: %1")
                                  .arg(tokens.join(QStringLiteral(", ")))
                            : QStringLiteral("Maskable: %1")
                                  .arg(tokens.join(QStringLiteral(", ")));
                }
                refreshProtectedValue(s);
            } else {
                s.maskedContent.clear();
                s.protectedValue = s.content;
                s.exportValue = s.content;
                s.hasProtection = false;
                s.findings.clear();
                s.protectionSummary.clear();
            }
```

- [ ] **Step 3: Gate stored override application and persistence**

Replace:

```cpp
        applyStoredStringOverrides(m_projectPath,
                                   currentFingerprintHex(m_currentSha256),
                                   &m_strings);
        if (m_stringsModel) m_stringsModel->setStrings(m_strings);
        persistStringProtectionRows(m_projectPath,
                                    currentFingerprintHex(m_currentSha256),
                                    m_strings);
```

with:

```cpp
        if (enableStringProtection) {
            applyStoredStringOverrides(m_projectPath,
                                       currentFingerprintHex(m_currentSha256),
                                       &m_strings);
        }
        if (m_stringsModel) m_stringsModel->setStrings(m_strings);
        if (enableStringProtection) {
            persistStringProtectionRows(m_projectPath,
                                        currentFingerprintHex(m_currentSha256),
                                        m_strings);
        }
```

- [ ] **Step 4: Build the target**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 4: Add GUI Smoke Coverage

**Files:**
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a dialog default test**

Add this subcase near the other GUI utility/dialog tests, or near the top of the main GUI smoke test body where `QApplication` is already active:

```cpp
    SUBCASE("analysis options dialog defaults string protection off") {
        aura::gui::AnalysisOptionsDialog dlg(
            QStringLiteral("C:/tmp/aura-test-binary.exe"));

        CHECK_FALSE(dlg.stringProtectionEnabled());
        CHECK(dlg.selectedLevel() == AURA_ANALYSIS_LEVEL_FULL);
    }
```

If the file does not already include the dialog header, add:

```cpp
#include "analysis_options_dialog.h"
```

- [ ] **Step 2: Add disabled analysis behavior coverage**

Add this subcase near the existing string protection subcases:

```cpp
    SUBCASE("string protection can be disabled for analyze") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinary(fixture));
        REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL, false));

        const auto strs = window.stringList();
        if (strs.isEmpty()) {
            MESSAGE("SKIP: fixture has no strings");
            return;
        }

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

- [ ] **Step 3: Add stored override does not reapply while disabled**

Add this subcase after `"string overrides reapply after reopening project"`:

```cpp
    SUBCASE("stored string overrides do not reapply when protection is disabled") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinary(fixture));
        REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL, true));
        if (window.stringList().isEmpty()) {
            MESSAGE("SKIP: fixture has no strings");
            return;
        }

        REQUIRE(window.setStringAliasAt(0, QStringLiteral("disabled_alias")));
        REQUIRE(window.setStringMaskTokenAt(0, QStringLiteral("DISABLED_MASK")));
        REQUIRE(window.setStringDisplayModeAt(0, 2));
        CHECK(window.stringProtectedValueAt(0) == QStringLiteral("[DISABLED_MASK]"));

        aura::gui::MainWindow reopened;
        REQUIRE(reopened.openProject(dbPath));
        REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL, false));
        REQUIRE_FALSE(reopened.stringList().isEmpty());
        CHECK(reopened.stringList()[0].alias.isEmpty());
        CHECK(reopened.stringList()[0].maskedContent.isEmpty());
        CHECK(reopened.stringProtectedValueAt(0) == reopened.stringList()[0].content);
    }
```

- [ ] **Step 4: Build after test edits**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 5: Verify and Commit

**Files:**
- Verify all modified files.

- [ ] **Step 1: Run GUI smoke tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: all selected tests pass.

- [ ] **Step 2: Inspect diff**

Run:

```powershell
git diff -- src/gui/analysis_options_dialog.h src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
```

Expected:
- checkbox is in the analysis options dialog;
- GUI analyze paths pass `dlg.stringProtectionEnabled()`;
- disabled path does not scan, mask, apply stored overrides, or persist protection rows;
- old `analyzeBinaryAt(row, level)` still exists.

- [ ] **Step 3: Commit**

Run:

```powershell
git add src/gui/analysis_options_dialog.h src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-string-protection-toggle.md .scratch/masking-toggle/PLAN.md
git commit -m "feat: add explicit string protection toggle"
```

Expected: commit succeeds.

---

## Self-Review

Spec coverage:
- User asked for non-automatic activation: covered by unchecked dialog default and GUI path passing the checkbox value.
- User asked for the choice between binary and analysis phase: covered by checkbox placement immediately after binary path and before analysis level.
- User wanted activation check in that state: covered by visible per-analysis checkbox and `stringProtectionEnabled()`.

Placeholder scan:
- No task uses TBD/TODO/fill-later language.
- Code steps include exact snippets and file paths.

Type consistency:
- Getter name is `stringProtectionEnabled()` everywhere.
- Flag name is `enableStringProtection()` in function signatures.
- Existing `analyzeBinaryAt(row, level)` remains compatible and delegates to the new overload.
