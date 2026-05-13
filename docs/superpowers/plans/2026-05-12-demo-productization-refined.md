# AURA Demo Productization Refined Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a GUI-first graduation demo mode that visibly proves AURA masks sensitive reverse-engineering output before LLM/MCP export.

**Architecture:** Add one shared safe-export presentation model in `aura_core`, then let GUI, CLI, and MCP render that same protected shape. The GUI gets a dedicated four-stage Demo Mode: Analyze -> Detect -> Mask -> Export. The standard strings table defaults protected rows to masked display.

**Tech Stack:** C++17, Qt Widgets, CMake, `aura_core`, existing safety core, existing GUI/CLI/MCP smoke tests.

---

## Scope Boundary

This plan implements only the professor-facing demo productization work:

- four-stage Demo Mode GUI,
- before/after sensitive item table,
- masked-first strings presentation,
- shared safe export view builder,
- CLI/MCP payload consistency,
- fixed benign demo fixture,
- foreground GUI verification.

This plan does **not** implement new malware scanners, YARA alternatives, model marketplace UX, local LLM replacement, or Ghidra expansion. Those are deferred because they do not solve the immediate demo clarity problem.

---

## Existing Structure Verified

The repo currently uses:

- safety public headers under `include/aura/safety/`
- safety implementation under `src/core/safety/`
- `aura_core` source list in root `CMakeLists.txt`
- GUI files under `src/gui/`
- GUI smoke in `tests/integration/gui_smoke/gui_smoke.cpp`
- CLI smoke in `tests/integration/cli_smoke/cli_smoke.cpp`
- MCP smoke in `tests/integration/mcp_smoke/mcp_smoke.cpp`
- safety unit in `tests/unit/safety/safety_unit.cpp`

Do not create `src/safety/`; that path does not exist in this repo.

---

## File Structure

### Core Safe Export Model

- Create: `include/aura/safety/safe_export_view.h`
  - Public C++ model for protected export rows.
  - Keeps GUI/CLI/MCP consistent.

- Create: `src/core/safety/safe_export_view.cpp`
  - Implements JSON-independent helpers for protected export item construction.
  - Does not depend on Qt or cJSON.

- Modify: `CMakeLists.txt`
  - Add `src/core/safety/safe_export_view.cpp` to `AURA_CORE_SOURCES`.

### GUI Demo Mode

- Create: `src/gui/demo_mode_pane.h`
  - Qt widget API for the demo flow.
  - Exposes setters for summary, sensitive item rows, and export preview text.

- Create: `src/gui/demo_mode_pane.cpp`
  - Builds a visible four-stage layout with stable object names.

- Modify: `src/gui/main_window.h`
  - Add `DemoModePane *m_demoModePane`.
  - Add a refresh helper for demo data.

- Modify: `src/gui/main_window.cpp`
  - Add Demo tab/dock.
  - Refresh Demo Mode after analysis and safety changes.

- Modify: `src/gui/string_table_model.h`
  - Expose or preserve display mode necessary for masked-first default.

- Modify: `src/gui/string_table_model.cpp`
  - Protected rows display masked value by default.

- Modify: `src/gui/CMakeLists.txt`
  - Add demo mode source/header.

### CLI/MCP

- Modify: `src/cli/main.cpp`
  - Use the shared safe-export shape for protected LLM JSON fields.

- Modify: `src/mcp/mcp_tools.cpp`
  - Ensure MCP returns matching `transmission_policy`, `original_included`, and `transmission_value`.

### Fixtures and Docs

- Create: `tests/fixtures/sources/aura_demo_sensitive.c`
  - Benign demo source with hardcoded strings only.
  - Never run as malware; it is a static analysis fixture.

- Create: `docs/demo/PROJECT_POSITIONING.md`
  - New title, one-line pitch, what we built, what we do not claim.

- Create: `docs/demo/DEMO_SCENARIO.md`
  - 5-minute explanation and 2-minute demo script.

### Tests

- Modify: `tests/unit/safety/safety_unit.cpp`
  - Safe export view and masking examples.

- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Demo Mode object names, viewer-facing labels, masked-first display, export preview safety.

- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
  - Protected JSON does not include full original sensitive values.

- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - MCP output matches safe export policy.

---

## Task 1: Shared Safe Export View

**Goal:** Create a core-level protected export row model so GUI, CLI, and MCP do not drift.

**Files:**
- Create: `include/aura/safety/safe_export_view.h`
- Create: `src/core/safety/safe_export_view.cpp`
- Modify: `CMakeLists.txt`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Inspect existing protected export code**

Run:

```powershell
Get-Content include\aura\safety\protected_export.h
Get-Content src\core\safety\protected_export.cpp
Get-Content include\aura\safety\string_safety.h
Select-String -Path src\cli\main.cpp -Pattern "display_value|transmission_value|original_included|mask_token"
```

Expected: identify current protected view/finding field names before adding the shared model.

- [ ] **Step 2: Write failing safety unit test**

Add to `tests/unit/safety/safety_unit.cpp`:

```cpp
#include "aura/safety/safe_export_view.h"

SUBCASE("safe export item excludes original value by construction") {
    aura::safety::SafeExportInput input;
    input.kind = "string";
    input.location = "0x401000";
    input.category = "kr_rrn";
    input.original_value = "900101-1234567";
    input.display_value = "900101-1******";
    input.transmission_value = "900101-1******";
    input.mask_token = "kr_rrn_1";

    const auto item = aura::safety::makeSafeExportItem(input);
    CHECK(item.kind == "string");
    CHECK(item.location == "0x401000");
    CHECK(item.category == "kr_rrn");
    CHECK(item.display_value == "900101-1******");
    CHECK(item.transmission_value == "900101-1******");
    CHECK(item.mask_token == "kr_rrn_1");
    CHECK(item.original_included == false);
    CHECK(item.transmission_value.find("900101-1234567") == std::string::npos);
}
```

- [ ] **Step 3: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: FAIL because `aura/safety/safe_export_view.h` does not exist.

- [ ] **Step 4: Create public header**

Create `include/aura/safety/safe_export_view.h`:

```cpp
#pragma once

#include <string>
#include <vector>

namespace aura::safety {

struct SafeExportInput {
    std::string kind;
    std::string location;
    std::string category;
    std::string original_value;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
};

struct SafeExportItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
    bool original_included = false;
};

SafeExportItem makeSafeExportItem(const SafeExportInput& input);
std::vector<SafeExportItem> makeSafeExportItems(const std::vector<SafeExportInput>& inputs);

} // namespace aura::safety
```

- [ ] **Step 5: Implement source**

Create `src/core/safety/safe_export_view.cpp`:

```cpp
#include "aura/safety/safe_export_view.h"

namespace aura::safety {

SafeExportItem makeSafeExportItem(const SafeExportInput& input) {
    SafeExportItem item;
    item.kind = input.kind;
    item.location = input.location;
    item.category = input.category;
    item.display_value = input.display_value;
    item.transmission_value = input.transmission_value;
    item.mask_token = input.mask_token;
    item.original_included = false;
    return item;
}

std::vector<SafeExportItem> makeSafeExportItems(const std::vector<SafeExportInput>& inputs) {
    std::vector<SafeExportItem> out;
    out.reserve(inputs.size());
    for (const auto& input : inputs) {
        out.push_back(makeSafeExportItem(input));
    }
    return out;
}

} // namespace aura::safety
```

- [ ] **Step 6: Add to core CMake**

In root `CMakeLists.txt`, add this line near the existing safety sources:

```cmake
src/core/safety/safe_export_view.cpp
```

Expected area currently contains:

```cmake
src/core/safety/protected_export.cpp
src/core/safety/string_encoding.cpp
src/core/safety/string_safety.cpp
```

- [ ] **Step 7: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS.

---

## Task 2: Four-Stage Demo Mode Pane

**Goal:** Add a visible demo screen that communicates the product without verbal explanation.

**Files:**
- Create: `src/gui/demo_mode_pane.h`
- Create: `src/gui/demo_mode_pane.cpp`
- Modify: `src/gui/CMakeLists.txt`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI smoke test for visible demo hierarchy**

Add to `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
#include "demo_mode_pane.h"

SUBCASE("demo mode pane exposes the graduation demo flow") {
    DemoModePane pane;
    pane.show();

    auto *claim = pane.findChild<QLabel *>("demoClaimLabel");
    REQUIRE(claim != nullptr);
    CHECK(claim->text().contains("LLM"));
    CHECK(claim->text().contains("mask", Qt::CaseInsensitive));

    CHECK(pane.findChild<QWidget *>("demoStageAnalyze") != nullptr);
    CHECK(pane.findChild<QWidget *>("demoStageDetect") != nullptr);
    CHECK(pane.findChild<QWidget *>("demoStageMask") != nullptr);
    CHECK(pane.findChild<QWidget *>("demoStageExport") != nullptr);
    CHECK(pane.findChild<QTableWidget *>("demoSensitiveItemsTable") != nullptr);
    CHECK(pane.findChild<QLabel *>("demoExportPreview") != nullptr);
}
```

- [ ] **Step 2: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: FAIL because `demo_mode_pane.h` does not exist.

- [ ] **Step 3: Create `DemoModePane` header**

Create `src/gui/demo_mode_pane.h`:

```cpp
#pragma once

#include <QWidget>

class QLabel;
class QTableWidget;

struct DemoSensitiveItemRow {
    QString category;
    QString originalValue;
    QString maskedValue;
    QString destination;
};

class DemoModePane final : public QWidget {
    Q_OBJECT
public:
    explicit DemoModePane(QWidget *parent = nullptr);

    void setBinaryName(const QString& name);
    void setEngineName(const QString& name);
    void setSummary(int extractedStrings, int protectedStrings, int exportRows);
    void setSensitiveItems(const QVector<DemoSensitiveItemRow>& rows);
    void setExportPreviewText(const QString& text);

private:
    QWidget* makeStageCard(const QString& objectName, const QString& title, const QString& body);

    QLabel *m_claimLabel = nullptr;
    QLabel *m_binaryLabel = nullptr;
    QLabel *m_engineLabel = nullptr;
    QLabel *m_summaryLabel = nullptr;
    QTableWidget *m_sensitiveItemsTable = nullptr;
    QLabel *m_exportPreview = nullptr;
};
```

- [ ] **Step 4: Create `DemoModePane` implementation**

Create `src/gui/demo_mode_pane.cpp`:

```cpp
#include "demo_mode_pane.h"

#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

DemoModePane::DemoModePane(QWidget *parent) : QWidget(parent) {
    setObjectName("demoModePane");

    auto *root = new QVBoxLayout(this);

    m_claimLabel = new QLabel(tr("AURA masks sensitive reverse-engineering data before LLM/MCP export."), this);
    m_claimLabel->setObjectName("demoClaimLabel");
    m_claimLabel->setWordWrap(true);
    root->addWidget(m_claimLabel);

    auto *stageGrid = new QGridLayout;
    stageGrid->addWidget(makeStageCard("demoStageAnalyze", tr("1. Analyze"), tr("Load a binary and extract strings/functions.")), 0, 0);
    stageGrid->addWidget(makeStageCard("demoStageDetect", tr("2. Detect"), tr("Find RRN, phone, email, and token-like strings.")), 0, 1);
    stageGrid->addWidget(makeStageCard("demoStageMask", tr("3. Mask"), tr("Show protected values like 900101-1******.")), 0, 2);
    stageGrid->addWidget(makeStageCard("demoStageExport", tr("4. Export"), tr("Send only protected values to LLM/MCP.")), 0, 3);
    root->addLayout(stageGrid);

    auto *metaGrid = new QGridLayout;
    m_binaryLabel = new QLabel(tr("Binary: not loaded"), this);
    m_binaryLabel->setObjectName("demoBinaryLabel");
    m_engineLabel = new QLabel(tr("Engine: not analyzed"), this);
    m_engineLabel->setObjectName("demoEngineLabel");
    m_summaryLabel = new QLabel(tr("Strings: 0 / Protected: 0 / Export rows: 0"), this);
    m_summaryLabel->setObjectName("demoSummaryLabel");
    metaGrid->addWidget(m_binaryLabel, 0, 0);
    metaGrid->addWidget(m_engineLabel, 0, 1);
    metaGrid->addWidget(m_summaryLabel, 1, 0, 1, 2);
    root->addLayout(metaGrid);

    m_sensitiveItemsTable = new QTableWidget(this);
    m_sensitiveItemsTable->setObjectName("demoSensitiveItemsTable");
    m_sensitiveItemsTable->setColumnCount(4);
    m_sensitiveItemsTable->setHorizontalHeaderLabels({tr("Type"), tr("Original"), tr("Masked"), tr("Sent to")});
    m_sensitiveItemsTable->horizontalHeader()->setStretchLastSection(true);
    root->addWidget(m_sensitiveItemsTable, 2);

    m_exportPreview = new QLabel(tr("{\"transmission_policy\":\"protected\",\"original_included\":false,\"items\":[]}"), this);
    m_exportPreview->setObjectName("demoExportPreview");
    m_exportPreview->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_exportPreview->setWordWrap(true);
    root->addWidget(m_exportPreview);
}

QWidget* DemoModePane::makeStageCard(const QString& objectName, const QString& title, const QString& body) {
    auto *frame = new QFrame(this);
    frame->setObjectName(objectName);
    frame->setFrameShape(QFrame::StyledPanel);
    auto *layout = new QVBoxLayout(frame);
    auto *titleLabel = new QLabel(title, frame);
    auto *bodyLabel = new QLabel(body, frame);
    bodyLabel->setWordWrap(true);
    layout->addWidget(titleLabel);
    layout->addWidget(bodyLabel);
    return frame;
}

void DemoModePane::setBinaryName(const QString& name) {
    m_binaryLabel->setText(tr("Binary: %1").arg(name.isEmpty() ? tr("not loaded") : name));
}

void DemoModePane::setEngineName(const QString& name) {
    m_engineLabel->setText(tr("Engine: %1").arg(name.isEmpty() ? tr("not analyzed") : name));
}

void DemoModePane::setSummary(int extractedStrings, int protectedStrings, int exportRows) {
    m_summaryLabel->setText(tr("Strings: %1 / Protected: %2 / Export rows: %3")
                                .arg(extractedStrings)
                                .arg(protectedStrings)
                                .arg(exportRows));
}

void DemoModePane::setSensitiveItems(const QVector<DemoSensitiveItemRow>& rows) {
    m_sensitiveItemsTable->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
        m_sensitiveItemsTable->setItem(i, 0, new QTableWidgetItem(rows[i].category));
        m_sensitiveItemsTable->setItem(i, 1, new QTableWidgetItem(rows[i].originalValue));
        m_sensitiveItemsTable->setItem(i, 2, new QTableWidgetItem(rows[i].maskedValue));
        m_sensitiveItemsTable->setItem(i, 3, new QTableWidgetItem(rows[i].destination));
    }
}

void DemoModePane::setExportPreviewText(const QString& text) {
    m_exportPreview->setText(text);
}
```

- [ ] **Step 5: Add GUI CMake entries**

In `src/gui/CMakeLists.txt`, add to `AURA_GUI_SOURCES`:

```cmake
demo_mode_pane.cpp
```

Add to `AURA_GUI_HEADERS`:

```cmake
demo_mode_pane.h
```

- [ ] **Step 6: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS for the standalone pane test.

---

## Task 3: Add Demo Mode to Main Window

**Goal:** Make Demo Mode visible in the real GUI, not only as a test widget.

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Inspect current central widget structure**

Run:

```powershell
Get-Content src\gui\main_window.h
Select-String -Path src\gui\main_window.cpp -Pattern "QTabWidget|addTab|QDockWidget|setCentralWidget|runAnalyze|StringTableModel"
```

Expected: identify the existing tab/dock owner before editing.

- [ ] **Step 2: Write failing integration test**

Add to `gui_smoke.cpp`:

```cpp
SUBCASE("main window contains demo mode pane") {
    MainWindow window;
    window.show();

    auto *demoPane = window.findChild<DemoModePane *>("demoModePane");
    REQUIRE(demoPane != nullptr);

    auto *exportPreview = demoPane->findChild<QLabel *>("demoExportPreview");
    REQUIRE(exportPreview != nullptr);
    CHECK(exportPreview->text().contains("original_included"));
    CHECK(exportPreview->text().contains("false"));
}
```

- [ ] **Step 3: Implement MainWindow member**

In `src/gui/main_window.h`, add:

```cpp
class DemoModePane;
```

and a private member:

```cpp
DemoModePane *m_demoModePane = nullptr;
```

- [ ] **Step 4: Add Demo tab/dock**

In `src/gui/main_window.cpp`, include:

```cpp
#include "demo_mode_pane.h"
```

Add `m_demoModePane = new DemoModePane(this);` to the same UI construction area that creates the existing strings/disasm/decompile panes.

If the existing UI uses `QTabWidget`, add:

```cpp
m_tabs->addTab(m_demoModePane, tr("Demo"));
```

If the actual tab pointer has a different name, use the existing central tab member discovered in Step 1.

- [ ] **Step 5: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Task 4: Masked-First String Display

**Goal:** Standard string browsing should show protected values as masked by default.

**Files:**
- Modify: `tests/unit/safety/safety_unit.cpp`
- Modify: `src/gui/string_table_model.h`
- Modify: `src/gui/string_table_model.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add exact masking examples**

Add to `tests/unit/safety/safety_unit.cpp`:

```cpp
SUBCASE("demo masking examples use visible star masking") {
    CHECK(aura::safety::maskSensitiveValueForDisplay("900101-1234567") == "900101-1******");
    CHECK(aura::safety::maskSensitiveValueForDisplay("010-1234-5678") == "010-1234-****");
}
```

If the helper has a different current name, inspect `include/aura/safety/string_safety.h` and bind this test to the current rendering-mask helper.

- [ ] **Step 2: Run safety unit**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS if masking already matches, FAIL if display masking still needs adjustment.

- [ ] **Step 3: Inspect string table fields**

Run:

```powershell
Get-Content src\gui\string_table_model.h
Get-Content src\gui\string_table_model.cpp
Select-String -Path src\gui\string_table_model.cpp -Pattern "DisplayRole|masked|alias|original|protected|content"
```

Expected: identify the exact row fields before editing.

- [ ] **Step 4: Add GUI smoke test**

Add a focused test using the existing `StringTableModel` fixture pattern. The assertion must be:

```cpp
CHECK(displayed.contains("*"));
CHECK_FALSE(displayed.contains("900101-1234567"));
```

If no direct model fixture helper exists, create a `DemoModePane` test that inserts:

```cpp
QVector<DemoSensitiveItemRow> rows;
rows.push_back({"Korean RRN", "900101-1234567", "900101-1******", "LLM/MCP"});
pane.setSensitiveItems(rows);
```

and checks the masked cell.

- [ ] **Step 5: Implement masked-first display**

Update `src/gui/string_table_model.cpp` so protected rows return masked display for the value column:

```cpp
if (role == Qt::DisplayRole && isValueColumn(index.column())) {
    if (row.isProtected && !row.maskedValue.isEmpty()) {
        return row.maskedValue;
    }
    return row.originalValue;
}
```

Replace `isValueColumn`, `isProtected`, `maskedValue`, and `originalValue` with the exact names discovered in Step 3.

- [ ] **Step 6: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit gui_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_unit|gui_smoke" --output-on-failure
```

Expected: PASS.

---

## Task 5: Demo Export Preview Uses Shared Safe Export Items

**Goal:** The GUI export preview says exactly what leaves for LLM/MCP and excludes original sensitive values.

**Files:**
- Modify: `src/gui/demo_mode_pane.h`
- Modify: `src/gui/demo_mode_pane.cpp`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add GUI smoke test for safe preview**

Add:

```cpp
SUBCASE("demo export preview does not include original protected value") {
    DemoModePane pane;
    pane.setExportPreviewText("{\"transmission_policy\":\"protected\",\"original_included\":false,\"items\":[{\"transmission_value\":\"900101-1******\"}]}");

    auto *preview = pane.findChild<QLabel *>("demoExportPreview");
    REQUIRE(preview != nullptr);
    CHECK(preview->text().contains("transmission_policy"));
    CHECK(preview->text().contains("protected"));
    CHECK(preview->text().contains("original_included"));
    CHECK(preview->text().contains("false"));
    CHECK_FALSE(preview->text().contains("900101-1234567"));
}
```

- [ ] **Step 2: Add MainWindow refresh helper**

After analysis/safety refresh, build safe export items from existing string protection data:

```cpp
std::vector<aura::safety::SafeExportInput> inputs;
// For each protected string row:
inputs.push_back({
    "string",
    location,
    category,
    originalValue,
    maskedValue,
    maskedValue,
    maskToken
});
const auto items = aura::safety::makeSafeExportItems(inputs);
```

Then serialize for GUI preview using Qt JSON locally in `main_window.cpp` or a small helper. Do not expose `originalValue` in the preview object.

- [ ] **Step 3: Update Demo Mode table at the same time**

For each protected string, add:

```cpp
DemoSensitiveItemRow{
    QString::fromStdString(item.category),
    QString::fromStdString(originalValue),
    QString::fromStdString(item.transmission_value),
    QStringLiteral("LLM/MCP")
}
```

The table may show the original in GUI because it is a local operator view. The export preview must not show it.

- [ ] **Step 4: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Task 6: CLI and MCP Consistency

**Goal:** CLI/MCP prove the same safe-export policy as GUI.

**Files:**
- Modify: `src/cli/main.cpp`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Inspect current JSON builders**

Run:

```powershell
Select-String -Path src\cli\main.cpp -Pattern "display_value|transmission_value|original_included|llm-context|strings"
Select-String -Path src\mcp\mcp_tools.cpp -Pattern "display_value|transmission_value|original_included|llm|context|strings"
```

- [ ] **Step 2: Add CLI smoke assertion**

In `cli_smoke.cpp`, assert the demo/LLM JSON contains:

```cpp
CHECK(output.find("\"transmission_policy\"") != std::string::npos);
CHECK(output.find("\"protected\"") != std::string::npos);
CHECK(output.find("\"original_included\"") != std::string::npos);
CHECK(output.find("900101-1234567") == std::string::npos);
```

Use the current test fixture invocation style.

- [ ] **Step 3: Add MCP smoke assertion**

In `mcp_smoke.cpp`, assert:

```cpp
CHECK(output.find("\"transmission_policy\"") != std::string::npos);
CHECK(output.find("\"original_included\"") != std::string::npos);
CHECK(output.find("900101-1234567") == std::string::npos);
```

- [ ] **Step 4: Wire shared safe export item fields**

In CLI and MCP JSON builders, protected items must include:

```cpp
cJSON_AddStringToObject(s, "display_value", item.display_value.c_str());
cJSON_AddStringToObject(s, "transmission_value", item.transmission_value.c_str());
cJSON_AddStringToObject(s, "transmission_policy", "protected");
cJSON_AddBoolToObject(s, "original_included", item.original_included);
cJSON_AddStringToObject(s, "mask_token", item.mask_token.c_str());
```

Do not add the original sensitive value to LLM/MCP export payloads.

- [ ] **Step 5: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: PASS.

---

## Task 7: Fixed Benign Demo Fixture

**Goal:** Make the live demo reproducible.

**Files:**
- Create: `tests/fixtures/sources/aura_demo_sensitive.c`
- Optional modify: relevant fixture CMake if this repo already compiles fixtures.
- Test: `tests/integration/gui_smoke/gui_smoke.cpp` or CLI smoke fixture setup.

- [ ] **Step 1: Create benign fixture source**

Create `tests/fixtures/sources/aura_demo_sensitive.c`:

```c
#include <stdio.h>

static const char *demo_rrn = "900101-1234567";
static const char *demo_phone = "010-1234-5678";
static const char *demo_email = "student.demo@example.com";
static const char *demo_token = "sk-demo-1234567890abcdef";

int main(void) {
    puts(demo_rrn);
    puts(demo_phone);
    puts(demo_email);
    puts(demo_token);
    return 0;
}
```

- [ ] **Step 2: Build fixture using existing fixture pattern**

Inspect:

```powershell
Get-Content tests\fixtures\sources\aura_smoke.c
Select-String -Path CMakeLists.txt,tests\integration\*\CMakeLists.txt -Pattern "aura_smoke|fixtures|sources"
```

If fixtures are compiled by CMake, add `aura_demo_sensitive.c` to the same fixture build path. If not, document the manual build command in `docs/demo/DEMO_SCENARIO.md`:

```powershell
cl /nologo /O2 tests\fixtures\sources\aura_demo_sensitive.c /Fe:.scratch\aura_demo_sensitive.exe
```

- [ ] **Step 3: Add test fixture usage**

Use the fixture in CLI or GUI smoke where possible. The test should prove at least one protected output appears and full original sensitive value is absent from export payload.

- [ ] **Step 4: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke gui_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|gui_smoke" --output-on-failure
```

Expected: PASS.

---

## Task 8: Demo Docs

**Goal:** Give the team the exact wording and demo flow.

**Files:**
- Create: `docs/demo/PROJECT_POSITIONING.md`
- Create: `docs/demo/DEMO_SCENARIO.md`

- [ ] **Step 1: Create positioning doc**

Create `docs/demo/PROJECT_POSITIONING.md`:

```markdown
# AURA Project Positioning

## Recommended Title

민감정보 보호 기반 LLM 연동 리버스 엔지니어링 보조 도구

## One-Line Explanation

AURA는 Rizin/Ghidra 같은 기존 리버스 엔지니어링 엔진의 분석 결과를 통합하고, LLM으로 전달되기 전 문자열과 함수 정보 속 민감정보를 자동 마스킹하는 보호형 분석 환경입니다.

## What We Built

- 외부 분석 엔진 결과를 AURA GUI로 통합해 보여주는 분석 환경
- 바이너리 문자열에서 주민등록번호, 전화번호, 이메일, 토큰형 문자열을 탐지하는 보호 계층
- 탐지된 민감정보를 `900101-1******` 같은 형태로 표시하는 마스킹 UI
- LLM/MCP/CLI로 전송되는 데이터에서 원본 민감정보를 제외하는 안전 전송 경로

## What We Do Not Claim

- 자체 디컴파일러를 완성했다고 주장하지 않는다.
- Ghidra보다 항상 빠르다고 주장하지 않는다.
- 악성코드를 확정 탐지한다고 주장하지 않는다.
- LLM이 절대 학습하지 않는다고 단정하지 않는다.
```

- [ ] **Step 2: Create demo scenario doc**

Create `docs/demo/DEMO_SCENARIO.md`:

```markdown
# AURA Demo Scenario

## 5-Minute Explanation

저희 프로젝트는 리버스 엔지니어링 결과를 LLM과 안전하게 연동하기 위한 보조 도구입니다. 기존의 Rizin/Ghidra 같은 분석 엔진은 그대로 활용하되, 그 결과를 AURA에서 통합해서 보여주고, LLM으로 넘어가기 전에 주민등록번호, 전화번호, 이메일 같은 민감정보를 자동으로 마스킹합니다.

핵심은 자체 디컴파일러를 새로 만드는 것이 아니라, 기존 분석 결과를 LLM에 넘길 때 발생할 수 있는 개인정보 노출 위험을 줄이는 보호 계층을 구현한 것입니다.

## 2-Minute Demo

1. 민감정보가 포함된 테스트 EXE를 AURA에 추가합니다.
2. Analyze를 눌러 외부 엔진 기반 분석을 실행합니다.
3. Demo 화면에서 추출된 문자열 개수와 보호된 문자열 개수를 확인합니다.
4. 주민등록번호/전화번호/이메일이 `900101-1******` 같은 형태로 마스킹된 것을 보여줍니다.
5. LLM/MCP Export Preview에서 `original_included: false`와 마스킹된 전송 값만 포함되는 것을 보여줍니다.
6. 결론: LLM을 이용한 리버스 엔지니어링 보조는 유지하면서 민감정보 노출 위험을 줄입니다.

## Demo Success Criteria

- 설명 없이도 화면에서 원본 값이 마스킹된 것을 알 수 있어야 한다.
- LLM/MCP로 나가는 JSON에 원본 민감정보가 없어야 한다.
- 발표자가 Rizin/Ghidra 내부 구현보다 AURA가 만든 보호 흐름을 먼저 설명해야 한다.
```

- [ ] **Step 3: Verify docs render**

Run:

```powershell
Get-Content docs\demo\PROJECT_POSITIONING.md
Get-Content docs\demo\DEMO_SCENARIO.md
```

Expected: Korean text displays correctly.

---

## Task 9: Foreground GUI Verification and Capture

**Goal:** Prove the demo works visually, not only through tests.

**Files:**
- No source file required unless bugs are found.
- Output capture under `.scratch/demo-captures/`.

- [ ] **Step 1: Full build and test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected: all selected tests PASS.

- [ ] **Step 2: Launch foreground GUI**

Run:

```powershell
$env:AURA_HOME="$PWD\.scratch\demo-home"
build-trim-gui\src\gui\Release\aura-gui.exe --rpc-port 27654
```

Expected: foreground GUI opens.

- [ ] **Step 3: Manual acceptance**

Confirm:

- Demo tab is visible.
- Four stage cards are visible.
- Add Binary -> Analyze works with the benign demo fixture.
- Sensitive item table shows original and masked values.
- Masked value uses star-style masking.
- Export preview says `original_included: false`.
- Export preview does not show full original sensitive values.

- [ ] **Step 4: Save capture**

Save a screenshot or manual capture under:

```text
.scratch/demo-captures/
```

Name format:

```text
demo-mode-YYYYMMDD-HHMMSS.png
```

If automated screenshot tooling is unavailable, record the foreground GUI PID and the exact manual observations in the final report.

---

## Final Verification Commands

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected:

- `safety_unit`: PASS
- `cli_smoke`: PASS
- `mcp_smoke`: PASS
- `gui_smoke`: PASS
- `aura-gui`: builds successfully

---

## Execution Order

1. Task 1: Shared safe export view.
2. Task 2: Demo Mode pane.
3. Task 3: MainWindow integration.
4. Task 4: Masked-first string display.
5. Task 5: GUI export preview wiring.
6. Task 6: CLI/MCP consistency.
7. Task 7: Fixed benign demo fixture.
8. Task 8: Demo docs.
9. Task 9: Full tests and foreground GUI verification.

---

## Self-Review

- **Spec coverage:** Covers all incomplete items from the status table and all required autoplan amendments.
- **Placeholder scan:** No `TBD` or intentionally vague deferred implementation steps. Discovery steps are explicit commands and must be completed before editing.
- **Type consistency:** `SafeExportInput`, `SafeExportItem`, `DemoSensitiveItemRow`, and `DemoModePane` names are consistent across tasks.
- **Scope control:** Excludes YARA, malware-risk expansion, local LLM replacement, and Ghidra expansion.
- **Risk:** Exact MainWindow/string model field names must be discovered before implementation. The plan includes mandatory inspection commands before those edits.
