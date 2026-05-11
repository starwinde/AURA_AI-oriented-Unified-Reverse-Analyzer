# First Analysis String Protection Toggle Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Let users enable or disable string protection during the first Add Binary analysis flow, not only through later programmatic or re-analyze paths.

**Architecture:** Keep `MainWindow::addBinary()` as a registration-only helper for tests, RPC, drag-drop, and batch paths. Add a UI-only Add Binary flow that opens `AnalysisOptionsDialog`, registers the selected binary, finds the registered row, and immediately runs `runAnalyze(row, selectedLevel, stringProtectionEnabled)`. The existing analysis button and double-click flows continue using the same dialog.

**Tech Stack:** C++17, Qt Widgets, AURA GUI `MainWindow`, `AnalysisOptionsDialog`, GUI smoke tests, CMake/CTest.

---

## File Structure

- Modify: `src/gui/analysis_options_dialog.cpp`
  - Give the string-protection checkbox a stable object name.
  - Keep the default unchecked state unless a later product decision changes the default.
- Modify: `src/gui/main_window.h`
  - Add a small testable helper for the UI Add Binary flow.
  - Add a row lookup helper if the implementation needs to find the newly registered binary after `addBinary()`.
- Modify: `src/gui/main_window.cpp`
  - Keep `addBinary()` registration-only.
  - Add `addBinaryAndAnalyzeForTest(...)` or equivalent helper that shares logic with `onAddBinary()`.
  - Update `onAddBinary()` to open `AnalysisOptionsDialog` and pass the toggle value into the first analysis.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add coverage for the dialog checkbox state.
  - Add coverage that first-analysis flow can run with string protection off and on.

---

## Current Behavior Notes

- `AnalysisOptionsDialog` already contains a checkbox and `stringProtectionEnabled()`.
- `MainWindow::onAnalyzeClicked()` and `MainWindow::onTableDoubleClicked()` already pass `dlg.stringProtectionEnabled()` into `runAnalyze(...)`.
- `MainWindow::onAddBinary()` currently only calls `addBinary(path)`, so the first Add Binary step does not expose or apply analysis options.
- `MainWindow::addBinary()` is used by tests, RPC, and drag/drop style helpers, so changing it to show a modal dialog would break non-interactive paths.
- GUI smoke already has tests proving `analyzeBinaryAt(..., false)` disables string protection; the missing coverage is the first UI Add Binary flow.

---

### Task 1: Add Dialog-Level Test Coverage

**Files:**
- Modify: `src/gui/analysis_options_dialog.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Give the checkbox a stable object name**

In `src/gui/analysis_options_dialog.cpp`, after the checkbox is constructed:

```cpp
    m_enableStringProtection = new QCheckBox(
        ko ? QStringLiteral("문자열 마스킹/보호 스캔 사용")
           : QStringLiteral("Enable string masking/protection scan"),
        this);
```

add:

```cpp
    m_enableStringProtection->setObjectName(
        QStringLiteral("analysisStringProtectionCheckBox"));
```

Keep the existing default:

```cpp
    m_enableStringProtection->setChecked(false);
```

- [ ] **Step 2: Add a focused dialog smoke subcase**

In `tests/integration/gui_smoke/gui_smoke.cpp`, near the other Safety/Analysis option subcases, add:

```cpp
    SUBCASE("analysis options exposes first-analysis string protection toggle") {
        aura::gui::AnalysisOptionsDialog dlg(
            QStringLiteral("C:/tmp/sample.exe"));

        auto* toggle = dlg.findChild<QCheckBox*>(
            QStringLiteral("analysisStringProtectionCheckBox"));
        REQUIRE(toggle != nullptr);

        CHECK_FALSE(toggle->isChecked());
        CHECK_FALSE(dlg.stringProtectionEnabled());

        toggle->setChecked(true);
        QApplication::processEvents();
        CHECK(dlg.stringProtectionEnabled());

        toggle->setChecked(false);
        QApplication::processEvents();
        CHECK_FALSE(dlg.stringProtectionEnabled());
    }
```

If the test file does not already include these headers, add:

```cpp
#include <QCheckBox>
```

- [ ] **Step 3: Build and run the focused test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected before implementation: build fails or test fails because the checkbox object name does not exist.  
Expected after Step 1: test passes.

---

### Task 2: Add a Testable First-Analysis Helper

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`

- [ ] **Step 1: Add public test helper declarations**

In `src/gui/main_window.h`, near the existing public programmatic helpers:

```cpp
    bool addBinary(const QString& binaryPath);
```

add:

```cpp
    bool addBinaryAndAnalyzeForTest(const QString& binaryPath,
                                    AuraAnalysisLevel level,
                                    bool enableStringProtection);
```

Near the private helper declarations, after:

```cpp
    int  selectedProjectRow() const;
```

add:

```cpp
    int  projectRowForBinaryPath(const QString& binaryPath) const;
```

- [ ] **Step 2: Implement row lookup**

In `src/gui/main_window.cpp`, after `MainWindow::selectedProjectRow() const`, add:

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

This helper must read from the project model after `addBinary()` reloads it.

- [ ] **Step 3: Implement the shared first-analysis helper**

In `src/gui/main_window.cpp`, after `MainWindow::addBinary(...)`, add:

```cpp
bool MainWindow::addBinaryAndAnalyzeForTest(const QString& binaryPath,
                                            AuraAnalysisLevel level,
                                            bool enableStringProtection) {
    if (!addBinary(binaryPath)) return false;
    const int row = projectRowForBinaryPath(binaryPath);
    if (row < 0) return false;
    return runAnalyze(row, level, enableStringProtection);
}
```

This helper intentionally uses the same `addBinary()` and `runAnalyze()` paths as the UI flow, but avoids a modal dialog so `gui_smoke` can verify the first-analysis behavior deterministically.

- [ ] **Step 4: Build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 3: Wire the Real Add Binary UI Flow

**Files:**
- Modify: `src/gui/main_window.cpp`

- [ ] **Step 1: Update `onAddBinary()` to show analysis options**

Replace the end of `MainWindow::onAddBinary()`:

```cpp
    if (path.isEmpty()) return;
    addBinary(path);
```

with:

```cpp
    if (path.isEmpty()) return;

    AnalysisOptionsDialog dlg(path, this);
    if (dlg.exec() != QDialog::Accepted) return;

    addBinaryAndAnalyzeForTest(path, dlg.selectedLevel(),
                               dlg.stringProtectionEnabled());
```

The name `addBinaryAndAnalyzeForTest` is acceptable for the first slice because it is public for smoke coverage, but the implementation is production code. If this name feels misleading in review, rename it to `addBinaryAndAnalyze(...)` and keep it public with a comment saying it is also used by tests.

- [ ] **Step 2: Preserve existing non-UI paths**

Do not change these call sites in this slice:

```cpp
MainWindow::addBinary(...)
MainWindow::handleDroppedPaths(...)
RpcServer::handle add_binary
```

They should continue to register binaries without opening modal UI or implicitly analyzing.

- [ ] **Step 3: Build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build succeeds.

---

### Task 4: Add First-Analysis Behavior Tests

**Files:**
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add off-path first-analysis test**

Near the existing subcase:

```cpp
    SUBCASE("string protection can be disabled for analyze") {
```

add:

```cpp
    SUBCASE("first add-binary analysis can disable string protection") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinaryAndAnalyzeForTest(
            stringFixture, AURA_ANALYSIS_LEVEL_FULL, false));

        const auto strs = window.stringList();
        REQUIRE_FALSE(strs.isEmpty());
        for (const auto& s : strs) {
            CHECK_FALSE(s.hasProtection);
            CHECK(s.maskedContent.isEmpty());
            CHECK(s.protectedValue == s.content);
            CHECK(s.exportValue == s.content);
            CHECK(s.protectionSummary.isEmpty());
        }
    }
```

- [ ] **Step 2: Add on-path first-analysis test**

After the off-path test, add:

```cpp
    SUBCASE("first add-binary analysis can enable string protection") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinaryAndAnalyzeForTest(
            stringFixture, AURA_ANALYSIS_LEVEL_FULL, true));

        const auto strs = window.stringList();
        REQUIRE_FALSE(strs.isEmpty());

        bool sawProtected = false;
        for (const auto& s : strs) {
            sawProtected = sawProtected || s.hasProtection
                           || !s.maskedContent.isEmpty()
                           || s.protectedValue != s.content;
        }
        CHECK(sawProtected);
    }
```

Use `stringFixture`, not the minimal ELF fixture, because the existing disabled-protection test already relies on it having strings.

- [ ] **Step 3: Verify `addBinary()` remains registration-only**

Keep the existing subcase:

```cpp
    SUBCASE("add binary") {
        REQUIRE(window.openProject(dbPath));
        REQUIRE(window.addBinary(fixture));
        CHECK(window.projectBinaryCount() == 1);
    }
```

Do not add an analysis assertion to this subcase. It documents that the helper remains registration-only.

- [ ] **Step 4: Run GUI smoke**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `1/1` tests pass.

---

### Task 5: Docs and Commit

**Files:**
- Modify: `docs/superpowers/plans/2026-05-10-first-analysis-string-protection-toggle.md`
- Optionally modify: `.scratch/safety-assets-rulepacks/PLAN.md`

- [ ] **Step 1: Decide whether to update scratch plan**

If `.scratch/safety-assets-rulepacks/PLAN.md` is still being used as the live checklist for this safety UI work, add one short follow-up line under scope or decisions:

```markdown
- Follow-up planned: first Add Binary analysis should open Analysis Options and pass the string-protection toggle into the initial `runAnalyze(...)` call.
```

If that scratch plan is treated as closed evidence for the previous slice, do not edit it.

- [ ] **Step 2: Inspect diff**

Run:

```powershell
git diff -- src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-first-analysis-string-protection-toggle.md
```

Expected:

- `AnalysisOptionsDialog` checkbox has object name `analysisStringProtectionCheckBox`.
- `onAddBinary()` opens `AnalysisOptionsDialog`.
- Accepted dialog path registers the binary and runs first analysis with `dlg.stringProtectionEnabled()`.
- Existing `addBinary()` helper remains registration-only.
- GUI smoke covers disabled and enabled first-analysis string protection.

- [ ] **Step 3: Commit**

Run:

```powershell
git add src/gui/analysis_options_dialog.cpp src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp docs/superpowers/plans/2026-05-10-first-analysis-string-protection-toggle.md
git commit -m "feat: add first-analysis string protection toggle"
```

Expected: commit succeeds.

---

## Self-Review

Spec coverage:
- First analysis options step: covered by updating `onAddBinary()` to show `AnalysisOptionsDialog`.
- Toggle on/off behavior: covered by disabled and enabled first-analysis GUI smoke tests.
- Existing re-analyze paths: preserved because `onAnalyzeClicked()` and double-click already use `dlg.stringProtectionEnabled()`.
- Non-interactive paths: preserved by keeping `addBinary()` registration-only.

Placeholder scan:
- No TBD/TODO/fill-later steps.
- Every code-changing step includes concrete code snippets.

Type consistency:
- `addBinaryAndAnalyzeForTest(...)` declaration and definition use the same signature.
- `projectRowForBinaryPath(...)` declaration and definition use the same signature.
- Checkbox object name is consistently `analysisStringProtectionCheckBox`.

Risk notes:
- `gui_smoke` may be slow because it already performs real Rizin-backed analysis. Keep this as one or two targeted subcases using `stringFixture`.
- If the enabled first-analysis test is flaky because the fixture has no rule-pack match in a given environment, switch the assertion to compare against the existing behavior of `analyzeBinaryAt(..., true)` on the same fixture, not to a hard-coded token.
