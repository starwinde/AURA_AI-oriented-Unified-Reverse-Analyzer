# AURA Demo Productization Missing Work Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Turn the currently implemented AURA analysis and masking pieces into a GUI-first graduation demo where a viewer immediately understands: binary analysis extracts sensitive strings, AURA masks them, and only protected data is sent to LLM/MCP/CLI surfaces.

**Architecture:** Keep the existing analyzer, safety, CLI, and MCP paths as the source of truth. Add a thin GUI demo layer that reads the same analysis/safety/export data and presents it as a staged flow: input binary -> extracted data -> detected sensitive values -> masked export payload. CLI and MCP are verification surfaces, not the primary demo surface.

**Tech Stack:** C++17, Qt Widgets, CMake, existing AURA safety core, existing GUI smoke tests, existing CLI/MCP smoke tests.

---

## Current Problem

The repo has meaningful functionality, but the demo does not yet communicate it clearly. The current UI looks like a developer analysis tool. For the graduation review, the product must look like a focused demo:

1. A binary is analyzed.
2. Sensitive data is detected.
3. Masking is visibly applied with star-style values.
4. The LLM/MCP export preview proves original values are not sent.

The implementation must prioritize visual clarity over adding more analysis features.

---

## File Structure

### New GUI Files

- Create: `src/gui/demo_mode_pane.h`
  - Owns the demo flow widget API.
  - Exposes setters for binary name, analysis engine label, detected items, masking status, and export preview.

- Create: `src/gui/demo_mode_pane.cpp`
  - Builds the Qt UI for the demo mode.
  - Contains no analysis logic.
  - Displays the staged flow and summary cards.

- Create: `src/gui/safe_export_preview.h`
  - Defines a small GUI-facing model for LLM/MCP export preview rows.

- Create: `src/gui/safe_export_preview.cpp`
  - Converts existing string table/protection data into a compact export preview.
  - Guarantees preview rows have no original sensitive value unless the user explicitly selects a local-only original display mode.

### Modified GUI Files

- Modify: `src/gui/main_window.h`
  - Add `DemoModePane* m_demoModePane`.
  - Add helpers to refresh demo mode after analysis and safety profile changes.

- Modify: `src/gui/main_window.cpp`
  - Add a main tab or dock named `Demo`.
  - Refresh demo mode after `runAnalyze(...)` completes.
  - Refresh demo mode after Safety Assets apply/recompute/delete actions.
  - Add a menu action `View -> Demo Mode`.

- Modify: `src/gui/string_table_model.h`
  - Ensure display mode can default to masked values.
  - Expose row metadata needed by demo mode: category, original-present flag, display value, transmission value.

- Modify: `src/gui/string_table_model.cpp`
  - Make protected rows visually obvious in the standard strings view.
  - Keep masked display as the default for protected strings.

- Modify: `src/gui/CMakeLists.txt`
  - Add the new GUI source/header files to `aura-gui` and `gui_smoke`.

### Modified CLI/MCP Files

- Modify: `src/cli/main.cpp`
  - Add or refine a demo-friendly compact JSON mode for `llm-context` or existing `mcp-json`.
  - Keep original values excluded by default.

- Modify: `src/mcp/mcp_tools.cpp`
  - Ensure MCP tool results expose the same protected export fields used by GUI preview.

### Tests

- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add widget-level tests for Demo Mode construction and refresh behavior.
  - Add checks that masked values are default in protected string rows.
  - Add checks that export preview does not contain original protected values.

- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
  - Add compact demo JSON check.

- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Add MCP protected payload consistency check.

- Modify: `tests/unit/safety/safety_unit.cpp`
  - Add exact partial-star masking examples used in the demo.

### Docs

- Create: `docs/demo/DEMO_SCENARIO.md`
  - 5-minute explanation and 2-minute demo script.

- Create: `docs/demo/PROJECT_POSITIONING.md`
  - New title options, one-line explanation, and avoided claims.

---

## Slice 1: Demo Mode GUI Shell

**Purpose:** Add a dedicated demo screen before adding advanced behavior. The first pass may use existing data or placeholder empty states, but it must compile and have testable object names.

**Files:**
- Create: `src/gui/demo_mode_pane.h`
- Create: `src/gui/demo_mode_pane.cpp`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/CMakeLists.txt`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI smoke test**

Add a test case to `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("demo mode pane is available from main window") {
    MainWindow window;
    window.show();

    auto *demoPane = window.findChild<QWidget *>("demoModePane");
    REQUIRE(demoPane != nullptr);

    auto *flowLabel = demoPane->findChild<QLabel *>("demoModeFlowLabel");
    REQUIRE(flowLabel != nullptr);
    CHECK(flowLabel->text().contains("Binary"));
    CHECK(flowLabel->text().contains("Mask"));
    CHECK(flowLabel->text().contains("LLM"));
}
```

- [ ] **Step 2: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: FAIL because `demoModePane` does not exist.

- [ ] **Step 3: Create `DemoModePane` with stable object names**

Implement:

```cpp
// src/gui/demo_mode_pane.h
#pragma once

#include <QWidget>

class QLabel;
class QTableWidget;

class DemoModePane final : public QWidget {
    Q_OBJECT
public:
    explicit DemoModePane(QWidget *parent = nullptr);

    void setBinaryName(const QString &name);
    void setEngineName(const QString &name);
    void setSummary(int extractedStrings, int protectedStrings, int exportRows);
    void setExportPreviewText(const QString &text);

private:
    QLabel *m_flowLabel = nullptr;
    QLabel *m_binaryLabel = nullptr;
    QLabel *m_engineLabel = nullptr;
    QLabel *m_summaryLabel = nullptr;
    QLabel *m_exportPreview = nullptr;
};
```

```cpp
// src/gui/demo_mode_pane.cpp
#include "demo_mode_pane.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

DemoModePane::DemoModePane(QWidget *parent) : QWidget(parent) {
    setObjectName("demoModePane");

    auto *layout = new QVBoxLayout(this);

    m_flowLabel = new QLabel(tr("Binary -> Analyze -> Detect Sensitive Data -> Mask -> LLM/MCP Export"), this);
    m_flowLabel->setObjectName("demoModeFlowLabel");
    m_flowLabel->setWordWrap(true);
    layout->addWidget(m_flowLabel);

    auto *grid = new QGridLayout;
    m_binaryLabel = new QLabel(tr("Binary: not loaded"), this);
    m_binaryLabel->setObjectName("demoBinaryLabel");
    m_engineLabel = new QLabel(tr("Engine: not analyzed"), this);
    m_engineLabel->setObjectName("demoEngineLabel");
    m_summaryLabel = new QLabel(tr("Strings: 0 / Protected: 0 / Export rows: 0"), this);
    m_summaryLabel->setObjectName("demoSummaryLabel");
    grid->addWidget(m_binaryLabel, 0, 0);
    grid->addWidget(m_engineLabel, 0, 1);
    grid->addWidget(m_summaryLabel, 1, 0, 1, 2);
    layout->addLayout(grid);

    auto *exportBox = new QGroupBox(tr("LLM/MCP protected export preview"), this);
    auto *exportLayout = new QVBoxLayout(exportBox);
    m_exportPreview = new QLabel(tr("{ \"original_included\": false, \"items\": [] }"), exportBox);
    m_exportPreview->setObjectName("demoExportPreview");
    m_exportPreview->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_exportPreview->setWordWrap(true);
    exportLayout->addWidget(m_exportPreview);
    layout->addWidget(exportBox);
}

void DemoModePane::setBinaryName(const QString &name) {
    m_binaryLabel->setText(tr("Binary: %1").arg(name.isEmpty() ? tr("not loaded") : name));
}

void DemoModePane::setEngineName(const QString &name) {
    m_engineLabel->setText(tr("Engine: %1").arg(name.isEmpty() ? tr("not analyzed") : name));
}

void DemoModePane::setSummary(int extractedStrings, int protectedStrings, int exportRows) {
    m_summaryLabel->setText(tr("Strings: %1 / Protected: %2 / Export rows: %3")
                                .arg(extractedStrings)
                                .arg(protectedStrings)
                                .arg(exportRows));
}

void DemoModePane::setExportPreviewText(const QString &text) {
    m_exportPreview->setText(text);
}
```

- [ ] **Step 4: Add Demo Mode to MainWindow**

In `src/gui/main_window.h`, add:

```cpp
class DemoModePane;
```

and private member:

```cpp
DemoModePane *m_demoModePane = nullptr;
```

In `src/gui/main_window.cpp`, include:

```cpp
#include "demo_mode_pane.h"
```

When building the central UI/tabs, add:

```cpp
m_demoModePane = new DemoModePane(this);
m_tabs->addTab(m_demoModePane, tr("Demo"));
```

Use the existing tab widget member name in the actual file. If the current central widget is not named `m_tabs`, add the demo pane to the existing central tab/dock layout following the local pattern.

- [ ] **Step 5: Update CMake**

In `src/gui/CMakeLists.txt`, add:

```cmake
demo_mode_pane.cpp
demo_mode_pane.h
```

to the same GUI source list that already contains `main_window.cpp`.

- [ ] **Step 6: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Slice 2: Masked-First String Presentation

**Purpose:** Make protected strings look protected without explanation. Protected values should default to masked display, not alias-token display.

**Files:**
- Modify: `src/gui/string_table_model.h`
- Modify: `src/gui/string_table_model.cpp`
- Modify: `tests/unit/safety/safety_unit.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add exact safety unit examples for demo masking**

Add examples:

```cpp
SUBCASE("demo masking keeps visible prefix and masks the rest") {
    auto masked = aura::safety::maskSensitiveValueForDisplay("900101-1234567");
    CHECK(masked == "900101-1******");

    auto phone = aura::safety::maskSensitiveValueForDisplay("010-1234-5678");
    CHECK(phone == "010-1234-****");
}
```

If the actual helper is named differently, keep the expected behavior and bind the test to the existing masking helper.

- [ ] **Step 2: Run safety unit to verify behavior**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS if previous partial masking already matches; otherwise FAIL and fix in the existing safety masking implementation.

- [ ] **Step 3: Add GUI smoke assertion for default masked value**

In `gui_smoke.cpp`, add a test that constructs a protected string row and checks that the displayed value contains `*` and does not contain the full original sensitive value.

```cpp
SUBCASE("protected string rows default to masked display") {
    StringTableModel model;
    // Use the existing helper or fixture pattern in gui_smoke.cpp to add one protected row.
    // Expected protected row display:
    const QString displayed = model.index(0, StringTableModel::ValueColumn).data(Qt::DisplayRole).toString();
    CHECK(displayed.contains("*"));
    CHECK_FALSE(displayed.contains("900101-1234567"));
}
```

Replace `ValueColumn` with the actual enum/column used by `StringTableModel`.

- [ ] **Step 4: Implement masked-first display**

In `src/gui/string_table_model.cpp`, update `data(..., Qt::DisplayRole)` for the string value column:

```cpp
if (row.is_protected && !row.masked_value.empty()) {
    return QString::fromStdString(row.masked_value);
}
return QString::fromStdString(row.content);
```

Use the actual row field names currently present in `StringTableModel`.

- [ ] **Step 5: Add visual marker**

For protected rows, return a clear badge/category string such as `Protected` or Korean `보호됨` in the category/status column:

```cpp
if (role == Qt::DisplayRole && column == StatusColumn) {
    return row.is_protected ? tr("보호됨") : tr("일반");
}
```

- [ ] **Step 6: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit gui_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_unit|gui_smoke" --output-on-failure
```

Expected: PASS.

---

## Slice 3: Safe Export Preview Model

**Purpose:** Show exactly what LLM/MCP receives, with original sensitive values excluded by default.

**Files:**
- Create: `src/gui/safe_export_preview.h`
- Create: `src/gui/safe_export_preview.cpp`
- Modify: `src/gui/demo_mode_pane.h`
- Modify: `src/gui/demo_mode_pane.cpp`
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/CMakeLists.txt`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Define GUI export preview model**

Create:

```cpp
// src/gui/safe_export_preview.h
#pragma once

#include <QString>
#include <QVector>

struct SafeExportPreviewRow {
    QString kind;
    QString location;
    QString displayValue;
    QString transmissionValue;
    QString maskToken;
    bool originalIncluded = false;
};

QString safeExportPreviewToJson(const QVector<SafeExportPreviewRow> &rows);
```

- [ ] **Step 2: Write failing GUI smoke test**

Add:

```cpp
SUBCASE("safe export preview excludes original protected values") {
    QVector<SafeExportPreviewRow> rows;
    rows.push_back({"string", "0x401000", "900101-1******", "900101-1******", "kr_rrn_1", false});

    const QString json = safeExportPreviewToJson(rows);
    CHECK(json.contains("\"original_included\":false"));
    CHECK(json.contains("900101-1******"));
    CHECK_FALSE(json.contains("900101-1234567"));
}
```

- [ ] **Step 3: Implement JSON preview**

```cpp
// src/gui/safe_export_preview.cpp
#include "safe_export_preview.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString safeExportPreviewToJson(const QVector<SafeExportPreviewRow> &rows) {
    QJsonObject root;
    root["transmission_policy"] = "protected";
    root["original_included"] = false;

    QJsonArray items;
    for (const auto &row : rows) {
        QJsonObject item;
        item["kind"] = row.kind;
        item["location"] = row.location;
        item["display_value"] = row.displayValue;
        item["transmission_value"] = row.transmissionValue;
        item["mask_token"] = row.maskToken;
        item["original_included"] = row.originalIncluded;
        items.append(item);
    }
    root["items"] = items;

    return QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Indented));
}
```

- [ ] **Step 4: Wire preview into Demo Mode**

In `MainWindow`, after analysis completes and strings are loaded:

```cpp
QVector<SafeExportPreviewRow> rows;
// Build rows from the same protected string data used by StringTableModel.
// For each protected string:
rows.push_back({
    "string",
    QString("0x%1").arg(address, 0, 16),
    maskedValue,
    maskedValue,
    maskToken,
    false
});
m_demoModePane->setExportPreviewText(safeExportPreviewToJson(rows));
```

Use the actual string record fields from the current model/analysis result.

- [ ] **Step 5: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

---

## Slice 4: CLI/MCP Demo Consistency

**Purpose:** The GUI is primary, but CLI and MCP must prove the same protected data is being sent.

**Files:**
- Modify: `src/cli/main.cpp`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add CLI smoke expectation**

Add a smoke assertion that `llm-context` or the existing compact JSON command includes:

```json
{
  "transmission_policy": "protected",
  "original_included": false,
  "transmission_value": "900101-1******"
}
```

and does not include:

```text
900101-1234567
```

- [ ] **Step 2: Add MCP smoke expectation**

In `mcp_smoke.cpp`, assert that the MCP output contains:

```cpp
CHECK(output.find("\"transmission_policy\":\"protected\"") != std::string::npos);
CHECK(output.find("\"original_included\":false") != std::string::npos);
CHECK(output.find("900101-1234567") == std::string::npos);
```

Adjust whitespace expectations if the output is pretty-printed.

- [ ] **Step 3: Implement or refine compact demo output**

In `src/cli/main.cpp`, ensure each protected string object has:

```cpp
cJSON_AddStringToObject(s, "display_value", protected_view.masked.c_str());
cJSON_AddStringToObject(s, "transmission_value", protected_view.masked.c_str());
cJSON_AddStringToObject(s, "transmission_policy", "protected");
cJSON_AddBoolToObject(s, "original_included", false);
cJSON_AddStringToObject(s, "mask_token", finding.mask_token.c_str());
```

Do not add the original content to demo/LLM/MCP export payloads unless a local-only debug flag is explicitly used.

- [ ] **Step 4: Make MCP use the same policy**

In `src/mcp/mcp_tools.cpp`, reuse the existing CLI bridge/export builder if available. If MCP builds JSON independently, add the same fields:

```cpp
"transmission_policy": "protected"
"original_included": false
"transmission_value": "<masked value>"
```

- [ ] **Step 5: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: PASS.

---

## Slice 5: Graduation Demo Script and Positioning

**Purpose:** Stop describing internals first. Create a short, repeatable script that every team member can say consistently.

**Files:**
- Create: `docs/demo/DEMO_SCENARIO.md`
- Create: `docs/demo/PROJECT_POSITIONING.md`

- [ ] **Step 1: Create positioning document**

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

- [ ] **Step 2: Create demo script**

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

- [ ] **Step 3: No-build documentation check**

Run:

```powershell
Get-Content docs/demo/PROJECT_POSITIONING.md
Get-Content docs/demo/DEMO_SCENARIO.md
```

Expected: both files are readable and Korean text renders correctly.

---

## Final Verification

Run all required checks:

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

Then run the foreground GUI:

```powershell
$env:AURA_HOME="$PWD\\.scratch\\demo-home"
build-trim-gui\\src\\gui\\Release\\aura-gui.exe --rpc-port 27654
```

Manual GUI acceptance:

- Demo tab is visible.
- Add Binary -> Analyze works.
- Protected string rows show star-style masked values by default.
- Demo tab summary updates after analysis.
- LLM/MCP export preview says `original_included: false`.
- Export preview does not display the full original sensitive value.

---

## Implementation Order

1. Slice 1: Demo Mode GUI shell.
2. Slice 2: Masked-first string presentation.
3. Slice 3: Safe export preview in GUI.
4. Slice 4: CLI/MCP consistency.
5. Slice 5: Demo script and positioning.
6. Full build/test.
7. Foreground GUI demonstration.

Do not start with Ghidra expansion, malware-risk expansion, YARA/third-party scanner work, or model/dataset switching. Those are useful secondary features, but they do not solve the professor's core criticism: the demo must be understandable on sight.

---

## Self-Review

- **Spec coverage:** Covers every current incomplete item: demo UI, masked visual clarity, LLM export preview, CLI/MCP consistency, and project positioning.
- **Placeholder scan:** No `TBD`/`TODO` placeholders. Where exact existing member names may differ, the plan explicitly says to use the current local pattern and field names.
- **Type consistency:** New GUI model uses `SafeExportPreviewRow` and `safeExportPreviewToJson(...)` consistently across Slice 3.
- **Risk:** The biggest risk is wiring `MainWindow` refresh because current analysis result ownership may be centralized there. Keep demo mode read-only and avoid changing analysis semantics.

---

## GSTACK Autoplan Review

**Review date:** 2026-05-12

**Verdict:** Approve with required revisions before implementation.

This plan targets the right problem: AURA does not primarily need more backend feature breadth right now; it needs a GUI-first demo flow that makes the safety value obvious without verbal explanation. The current plan is directionally correct, but execution must be tightened around demo clarity, testability, and realistic scope.

### CEO / Scope Review

**Decision:** Keep the plan focused on demo productization.

The plan correctly defers Ghidra expansion, YARA/third-party malware tooling, model switching, and dataset switching. Those are not the professor's core criticism. The highest-value outcome is a repeatable 2-minute demo where a non-specialist sees:

1. analysis result,
2. detected sensitive value,
3. masked display,
4. protected LLM/MCP payload.

**Required revision:** Slice 1 must not stop at a generic `Demo` tab. It must present the exact four-stage story above using visible section labels. A tab that only contains labels and JSON will not solve the review problem.

**Accepted scope:** Demo Mode, masked-first strings, safe export preview, CLI/MCP parity, presentation docs.

**Explicitly not in scope for this plan:** new malware-risk heuristics, YARA alternatives, multi-engine benchmark claims, local LLM replacement, dataset/model marketplace UX.

### Design Review

**Decision:** Demo Mode must be a guided visual flow, not another developer table.

The current plan has a functional pane, but the first version is too plain. The demo screen needs visible hierarchy:

- top: one-sentence product claim,
- middle: four stage cards,
- bottom-left: detected sensitive items,
- bottom-right: LLM/MCP protected export preview.

**Required revision:** `DemoModePane` should expose object names for these visible areas:

```text
demoClaimLabel
demoStageAnalyze
demoStageDetect
demoStageMask
demoStageExport
demoSensitiveItemsTable
demoExportPreview
```

**Required revision:** GUI smoke must assert the viewer-facing Korean/English text exists. A test that only checks `Binary`, `Mask`, and `LLM` is too weak.

**Required revision:** The export preview should not dominate the screen. It should be compact and secondary. The primary visual proof is the before/after masking table.

### Engineering Review

**Decision:** Introduce a small shared presentation model before wiring GUI, CLI, and MCP.

The plan currently risks duplicating payload shaping between `DemoModePane`, CLI, and MCP. That is exactly how GUI and CLI drift happened earlier.

**Required revision:** Add a shared source-facing builder before GUI rendering:

- Create: `src/safety/safe_export_view.h`
- Create: `src/safety/safe_export_view.cpp`

This module should produce a small neutral structure:

```cpp
struct AuraSafeExportItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
    bool original_included;
};
```

GUI can convert it to Qt rows, CLI can convert it to cJSON, and MCP can return the same shape. This avoids making `src/gui/safe_export_preview.cpp` the hidden source of truth.

**Required revision:** Replace plan phrases like "Use the actual string record fields" with concrete implementation discovery steps:

```powershell
Get-Content src/gui/string_table_model.h
Get-Content src/gui/main_window.h
Select-String -Path src/gui/main_window.cpp -Pattern "strings|StringTableModel|runAnalyze|protected"
```

Then update the implementation step with the exact field names before coding.

### DX / Verification Review

**Decision:** Keep CLI/MCP as demo verification surfaces, but GUI remains primary.

The test plan is mostly right, but it lacks a demo fixture requirement. Without a fixed fixture, the GUI can pass tests while the live demo fails or shows weak data.

**Required revision:** Add a fixed demo fixture task before final GUI run:

- use an existing benign fixture if present;
- otherwise create/build a benign EXE fixture with hardcoded test strings;
- include at least: Korean RRN, phone, email, API-token-like value;
- never execute downloaded or suspicious binaries.

**Required revision:** Final manual acceptance must include a screenshot or saved capture path for the foreground GUI state. The demo must be visually inspectable after the run.

### Failure Modes Registry

| Failure | Impact | Required Mitigation |
|---|---|---|
| Demo tab exists but looks like another debug panel | Professor still does not understand the product | Four-stage visual layout and before/after table |
| GUI preview and CLI/MCP payload drift | Safety claim becomes untrustworthy | Shared `safe_export_view` builder |
| Masking test passes on synthetic helper but live analysis shows no protected rows | Demo fails live | Fixed benign EXE fixture and foreground GUI test |
| Export preview accidentally includes original value | Core safety promise is broken | Negative tests for full original sensitive values |
| Plan expands into malware/YARA/model switching | Time is lost on non-core scope | Keep those items out of this plan |

### Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|---|---|---|---|---|---|
| 1 | CEO | Keep scope centered on demo productization | Auto-decided | Solve the visible review problem first | The professor criticized demo clarity, not scanner breadth | Adding YARA/model switching now |
| 2 | Design | Require a four-stage visual Demo Mode | Auto-decided | UI must explain without narration | A generic tab with JSON will not pass the demo critique | Developer-only table layout |
| 3 | Engineering | Add shared safe export view builder | Auto-decided | Prevent GUI/CLI/MCP drift | Safety payload semantics must have one source of truth | GUI-only export shaping |
| 4 | DX | Require fixed benign demo fixture | Auto-decided | Reproducibility beats ad hoc demos | The live demo must always show strong masking examples | Depending on arbitrary binaries |
| 5 | Verification | Require foreground GUI capture | Auto-decided | Visual proof matters for this project | Build tests alone do not prove the demo communicates | CLI-only verification |

### Autoplan Amendments Required Before Execution

- [ ] Add `src/safety/safe_export_view.h/.cpp` to the file structure and task list.
- [ ] Revise `DemoModePane` to include stage cards and a before/after sensitive item table.
- [ ] Add a fixed benign demo fixture task.
- [ ] Strengthen GUI smoke assertions to check viewer-facing labels and absence of full original sensitive values.
- [ ] Add final foreground GUI capture as a required verification artifact.

After these amendments, the plan is suitable for subagent-driven implementation.
