<!-- /autoplan restore point: C:\Users\21m15\.gstack\projects\AURA\codex-safety-rule-pack-selection-autoplan-restore-20260512-234744.md -->
# AURA Demo Gateway UI Fixes Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the GUI demo clearly show that AURA collects RE outputs, detects sensitive values, masks them, verifies the protected prompt, and never exposes raw sensitive values in protected UI modes.

**Architecture:** Keep the GUI as the source of truth. `StringTableModel` owns visible string rows, `MainWindow` owns analysis/protection state transitions, and `GatewayPane` owns LLM export readiness. CLI/MCP must mirror the same protected data model, but this plan prioritizes GUI-visible correctness first.

**Tech Stack:** C++17, Qt Widgets, existing AURA safety core, existing `gui_smoke`, `cli_smoke`, and `mcp_smoke` tests.

---

## File Structure

- Modify: `src/gui/string_table_model.cpp`
  - Owns string row filtering and display text.
  - Must guarantee `Alias` mode only shows rows with explicit aliases.
  - Must prevent raw fallback for protected rows.
- Modify: `src/gui/main_window.cpp`
  - Owns global display-mode combo behavior, protection recompute, Gateway refresh, and demo pane refresh.
  - Must make display-mode changes update row filtering/counts consistently.
- Modify: `src/gui/gateway_pane.cpp`
  - Owns LLM Gateway presentation.
  - Must replace internal English check ids with Korean presentation labels while retaining raw ids in tooltips/details.
- Modify: `src/gui/demo_mode_pane.cpp`
  - Owns the graduation demo flow panel.
  - Must make the local-original-vs-LLM-export boundary visible in Korean.
- Inspect: `src/gateway/llm_gateway.cpp`
  - Gateway readiness semantics should not change in this plan; inspect only if a test fails.
- Inspect: `src/cli/main.cpp`
  - CLI JSON must keep machine-readable check ids; inspect only if `cli_smoke` fails.
- Inspect: `src/mcp/mcp_tools.cpp`
  - MCP snapshot must keep protected output semantics; inspect only if `mcp_smoke` fails.
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add/adjust GUI tests for alias filtering, raw exposure prevention, Gateway Korean labels, and demo flow state.
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`
  - Verify CLI still exposes machine-readable ids/statuses.
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Verify MCP still excludes raw sensitive values.

---

## Task 1: Fix Alias Display Mode Semantics

**Files:**
- Modify: `src/gui/string_table_model.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write the failing GUI model test**

Add this case near the existing string display tests in `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("alias display mode shows only explicitly aliased strings") {
    aura::gui::StringTableModel model;
    QVector<aura::gui::GuiStringRecord> rows;

    aura::gui::GuiStringRecord aliased;
    aliased.addr = 0x1000;
    aliased.content = QStringLiteral("alice.smith@example.com");
    aliased.alias = QStringLiteral("customer_email");
    aliased.maskedContent = QStringLiteral("alic***************e.com");
    aliased.protectedValue = aliased.maskedContent;
    aliased.exportValue = aliased.maskedContent;
    aliased.hasProtection = true;
    aliased.displayMode = 1;
    rows.push_back(aliased);

    aura::gui::GuiStringRecord protectedWithoutAlias;
    protectedWithoutAlias.addr = 0x1008;
    protectedWithoutAlias.content = QStringLiteral("010-1234-5678");
    protectedWithoutAlias.maskedContent = QStringLiteral("010-********78");
    protectedWithoutAlias.protectedValue = protectedWithoutAlias.maskedContent;
    protectedWithoutAlias.exportValue = protectedWithoutAlias.maskedContent;
    protectedWithoutAlias.hasProtection = true;
    protectedWithoutAlias.displayMode = 1;
    rows.push_back(protectedWithoutAlias);

    aura::gui::GuiStringRecord plain;
    plain.addr = 0x1010;
    plain.content = QStringLiteral("__stdcall");
    plain.displayMode = 1;
    rows.push_back(plain);

    model.setStrings(rows);
    model.setFilter(aura::gui::StringTableModel::Filter::Alias);

    REQUIRE(model.rowCount() == 1);
    CHECK(model.data(model.index(0, 0)).toString()
          == QStringLiteral("customer_email"));
}
```

- [ ] **Step 2: Run test to verify RED**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` fails because Alias mode/filter still includes non-aliased rows or raw fallback rows.

- [ ] **Step 3: Implement the minimal filter fix**

In `src/gui/string_table_model.cpp`, make sure `Filter::Alias` accepts only explicit aliases:

```cpp
case Filter::Alias:
    return !row.alias.trimmed().isEmpty();
```

Also ensure `displayValueForString()` never returns raw original for a protected row when `displayMode == 1` and alias is missing:

```cpp
if (r.displayMode == 1) {
    if (!r.alias.trimmed().isEmpty()) return r.alias;
    if (r.hasProtection) return protectedDisplayValue(r, original);
    return original;
}
```

- [ ] **Step 4: Run test to verify GREEN**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes.

---

## Task 2: Make Display Combo and Category Filter Work Together

**Files:**
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI test**

Add a test that simulates the screenshot state through the real dock controls: category `All`, display mode `Alias`, and mixed aliased/non-aliased rows. Expected visible rows must be aliased-only when alias mode is selected.

```cpp
SUBCASE("strings dock alias mode hides non-aliased rows") {
    const SettingsKeyGuard activeProfileGuard(
        QStringLiteral("safety/activeProfileId"));
    QTemporaryDir home;
    REQUIRE(home.isValid());
    writeFixtureRulePack(home.path());
    AuraHomeGuard auraHome(home.path());

    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::Selected;
    profile.rule_pack_ids = {"fixture-rule"};
    std::string diagnostic;
    REQUIRE(aura::safety::saveSafetyProfile("default", profile, &diagnostic));

    aura::gui::MainWindow window;
    const QString db =
        QDir(tmp.path()).filePath(QStringLiteral("alias-mode.aura.db"));
    REQUIRE(window.openProject(db));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));
    REQUIRE_FALSE(window.stringList().isEmpty());

    int protectedRow = -1;
    for (int i = 0; i < window.stringList().size(); ++i) {
        if (window.stringList()[i].hasProtection) {
            protectedRow = i;
            break;
        }
    }
    REQUIRE(protectedRow >= 0);
    REQUIRE(window.setStringAliasAt(protectedRow,
                                    QStringLiteral("customer_email")));

    auto* modeCombo = window.findChild<QComboBox*>(
        QStringLiteral("stringsDisplayModeCombo"));
    REQUIRE(modeCombo != nullptr);
    const int aliasMode = modeCombo->findData(1);
    REQUIRE(aliasMode >= 0);
    modeCombo->setCurrentIndex(aliasMode);
    QApplication::processEvents();

    auto* categoryCombo = window.findChild<QComboBox*>(
        QStringLiteral("stringsCategoryFilterCombo"));
    REQUIRE(categoryCombo != nullptr);
    CHECK(categoryCombo->currentData().toInt()
          == static_cast<int>(aura::gui::StringTableModel::Filter::Alias));

    auto* label = window.findChild<QLabel*>(
        QStringLiteral("stringsCategoryCountLabel"));
    REQUIRE(label != nullptr);
    CHECK(label->text() == QStringLiteral("1"));
}
```

- [ ] **Step 2: Run RED**

Run the same `gui_smoke` build/test command.

Expected: fails if the dock/global display mode does not drive filtering.

- [ ] **Step 3: Implement combo behavior**

In `MainWindow` display-mode combo handler:

```cpp
const int mode = m_stringsDisplayModeCombo->currentData().toInt();
for (auto& s : m_strings) {
    s.displayMode = mode;
    refreshProtectedValue(s);
}
if (mode == 1 && m_stringsCategoryFilterCombo) {
    const int aliasIndex = m_stringsCategoryFilterCombo->findData(
        static_cast<int>(StringTableModel::Filter::Alias));
    if (aliasIndex >= 0) m_stringsCategoryFilterCombo->setCurrentIndex(aliasIndex);
}
if (m_stringsModel) {
    m_stringsModel->setStrings(m_strings);
}
```

If changing the category combo is too disruptive, add a model-level display mode filter instead. Do not leave `All + Alias` showing all raw strings, because that is the exact user-visible bug.

- [ ] **Step 4: Verify GREEN**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: Alias mode shows only explicitly aliased strings.

---

## Task 3: Harden Raw Original Exposure in Protected UI Modes

**Files:**
- Modify: `src/gui/string_table_model.cpp`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing test**

Add a test that protected strings never expose original values in parent rows for protected-focused modes:

```cpp
SUBCASE("protected display modes never expose raw protected parent text") {
    aura::gui::StringTableModel model;
    aura::gui::GuiStringRecord s;
    s.content = QStringLiteral("900101-1234567");
    s.hasProtection = true;
    s.maskedContent.clear();
    s.protectedValue.clear();
    s.displayMode = 2;

    model.setStrings(QVector<aura::gui::GuiStringRecord>{s});

    const QString shown = model.data(model.index(0, 0)).toString();
    CHECK(shown.contains(QLatin1Char('*')));
    CHECK_FALSE(shown.contains(QStringLiteral("900101-1234567")));
}
```

- [ ] **Step 2: Run RED**

Run `gui_smoke`.

Expected: fails if protected rows can still fall back to raw original.

- [ ] **Step 3: Implement display-layer fallback masking**

In `string_table_model.cpp`, keep a display-only fallback mask:

```cpp
QString starMaskForDisplay(const QString& value) {
    if (value.isEmpty()) return QStringLiteral("*");
    const int len = value.size();
    int maskCount = (len * 65 + 50) / 100;
    maskCount = qBound(1, maskCount, len);
    const int visible = len - maskCount;
    const int prefix = visible / 2 + visible % 2;
    const int suffix = visible / 2;
    return value.left(prefix)
        + QString(maskCount, QLatin1Char('*'))
        + (suffix > 0 ? value.right(suffix) : QString());
}
```

Use it only for display fallback. Do not mutate raw cache or `exportValue` here.

- [ ] **Step 4: Verify GREEN**

Run `gui_smoke`.

Expected: protected parent rows do not show raw sensitive values.

---

## Task 4: Make LLM Gateway Presentation Demo-Ready

**Files:**
- Modify: `src/gui/gateway_pane.cpp`
- Modify: `src/gui/gateway_pane.h`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI test for readable labels**

Add:

```cpp
SUBCASE("gateway pane uses presentation labels for checks") {
    aura::gui::MainWindow window;
    window.show();
    QApplication::processEvents();

    auto* table = window.findChild<QTreeWidget*>(
        QStringLiteral("gatewayVerificationTable"));
    REQUIRE(table != nullptr);

    bool sawKoreanOrReadableLabel = false;
    for (int i = 0; i < table->topLevelItemCount(); ++i) {
        const QString check = table->topLevelItem(i)->text(0);
        sawKoreanOrReadableLabel =
            sawKoreanOrReadableLabel ||
            check.contains(QStringLiteral("보호")) ||
            check.contains(QStringLiteral("Rule Pack")) ||
            check.contains(QStringLiteral("원본"));
    }
    CHECK(sawKoreanOrReadableLabel);
}
```

- [ ] **Step 2: Run RED**

Run `gui_smoke`.

Expected: fails if the table only shows internal ids such as `protection_enabled`.

- [ ] **Step 3: Add label mapping**

In `gateway_pane.cpp`, add a local helper:

```cpp
QString checkLabel(const QString& id) {
    if (id == QStringLiteral("protection_enabled"))
        return QStringLiteral("보호 기능 활성화");
    if (id == QStringLiteral("safety_scan_executed"))
        return QStringLiteral("안전 스캔 실행");
    if (id == QStringLiteral("safety_profile_applied"))
        return QStringLiteral("안전 프로필 적용");
    if (id == QStringLiteral("rule_packs_loaded"))
        return QStringLiteral("Rule Pack 로드");
    if (id == QStringLiteral("active_rule_count"))
        return QStringLiteral("활성 규칙 존재");
    if (id == QStringLiteral("masking_cache_current"))
        return QStringLiteral("마스킹 결과 최신");
    if (id == QStringLiteral("protected_prompt_generated"))
        return QStringLiteral("보호 프롬프트 생성");
    if (id == QStringLiteral("original_values_not_included"))
        return QStringLiteral("원본값 미포함");
    if (id == QStringLiteral("protected_items_available"))
        return QStringLiteral("보호 항목 존재");
    return id;
}
```

When inserting rows, set column 0 to `checkLabel(id)` and put the raw id in tooltip:

```cpp
item->setText(0, checkLabel(rawId));
item->setToolTip(0, rawId);
```

- [ ] **Step 4: Verify GREEN**

Run `gui_smoke`.

Expected: Gateway table is readable in GUI while retaining raw ids in tooltip/details.

---

## Task 5: Make Demo Pane Presentation-Ready Without Raw Export Confusion

**Files:**
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/demo_mode_pane.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI test**

The demo pane already has four stage cards. Add a test that verifies it is presentation-ready in Korean and does not imply raw values are sent to the LLM:

```cpp
SUBCASE("demo pane presents protected gateway flow without raw export confusion") {
    const SettingsKeyGuard activeProfileGuard(
        QStringLiteral("safety/activeProfileId"));
    QTemporaryDir home;
    REQUIRE(home.isValid());
    writeFixtureRulePack(home.path());
    AuraHomeGuard auraHome(home.path());

    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::Selected;
    profile.rule_pack_ids = {"fixture-rule"};
    std::string diagnostic;
    REQUIRE(aura::safety::saveSafetyProfile("default", profile, &diagnostic));

    aura::gui::MainWindow window;
    const QString db = QDir(tmp.path()).filePath(QStringLiteral("demo-flow.aura.db"));
    REQUIRE(window.openProject(db));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));

    auto* label = window.findChild<QLabel*>(QStringLiteral("demoFlowSummaryLabel"));
    REQUIRE(label != nullptr);
    CHECK(label->text().contains(QStringLiteral("수집")));
    CHECK(label->text().contains(QStringLiteral("탐지")));
    CHECK(label->text().contains(QStringLiteral("마스킹")));
    CHECK(label->text().contains(QStringLiteral("검증")));

    auto* table = window.findChild<QTableWidget*>(
        QStringLiteral("demoSensitiveItemsTable"));
    REQUIRE(table != nullptr);
    CHECK(table->horizontalHeaderItem(0)->text().contains(QStringLiteral("종류")));
    CHECK(table->horizontalHeaderItem(1)->text().contains(QStringLiteral("UI 확인용 원본")));
    CHECK(table->horizontalHeaderItem(2)->text().contains(QStringLiteral("마스킹")));
    CHECK(table->horizontalHeaderItem(3)->text().contains(QStringLiteral("LLM 전송")));

    auto* preview = window.findChild<QLabel*>(
        QStringLiteral("demoExportPreview"));
    REQUIRE(preview != nullptr);
    CHECK(preview->text().contains(QStringLiteral("original_included")));
    CHECK(preview->text().contains(QStringLiteral("false")));
}
```

- [ ] **Step 2: Run RED**

Run `gui_smoke`.

Expected: fails if no single readable Korean demo summary exists, or if table headers do not make the raw/LLM boundary clear.

- [ ] **Step 3: Implement summary**

In `src/gui/demo_mode_pane.cpp`, add one label with object name `demoFlowSummaryLabel` near the top:

```cpp
auto* summary = new QLabel(
    QStringLiteral("1. RE 결과 수집 → 2. 민감정보 탐지 → 3. 마스킹 → 4. LLM 전송 검증"),
    this);
summary->setObjectName(QStringLiteral("demoFlowSummaryLabel"));
summary->setWordWrap(true);
```

Also change the demo table headers from generic English labels to presentation-safe Korean labels:

```cpp
m_sensitiveItemsTable->setHorizontalHeaderLabels(
    {QStringLiteral("종류"),
     QStringLiteral("UI 확인용 원본"),
     QStringLiteral("마스킹"),
     QStringLiteral("LLM 전송")});
```

The `UI 확인용 원본` column may show local user-visible originals for demonstration, but the `LLM 전송` column and `demoExportPreview` must never include raw sensitive values.

- [ ] **Step 4: Verify GREEN**

Run `gui_smoke`.

Expected: demo pane gives a professor-readable flow without code-level explanation, and the raw/local-vs-export boundary is visible.

---

## Task 6: Keep CLI/MCP Aligned With Protected Gateway Semantics

**Files:**
- Inspect: `src/cli/main.cpp`
- Inspect: `src/mcp/mcp_tools.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Confirm CLI test coverage**

Open `tests/integration/cli_smoke/cli_smoke.cpp` and confirm or add assertions in the Gateway JSON test that CLI output still contains machine-readable fields:

```cpp
CHECK(jsonText.find("\"verification\"") != std::string::npos);
CHECK(jsonText.find("\"status\"") != std::string::npos);
CHECK(jsonText.find("\"checks\"") != std::string::npos);
CHECK(jsonText.find("\"original_values_not_included\"") != std::string::npos);
```

- [ ] **Step 2: Confirm MCP test coverage**

Open `tests/integration/mcp_smoke/mcp_smoke.cpp` and confirm or add assertions in the protected snapshot test that MCP output does not expose raw sensitive values:

```cpp
CHECK(snapshot.find("900101-1234567") == std::string::npos);
CHECK(snapshot.find("alice.smith@example.com") == std::string::npos);
CHECK(snapshot.find("masked_content") != std::string::npos);
```

- [ ] **Step 3: Run verification**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: CLI/MCP still expose stable machine-readable status while GUI uses readable labels.

- [ ] **Step 4: Production change rule**

Do not edit `src/cli/main.cpp` or `src/mcp/mcp_tools.cpp` if the tests pass. If either test fails because GUI label changes leaked into machine-readable JSON, restore the JSON check `name` fields to the existing raw ids and keep the Korean labels only in `src/gui/gateway_pane.cpp`.

---

## Task 7: Foreground GUI Verification

**Files:**
- No source file changes unless a visible defect is found.

- [ ] **Step 1: Build final GUI**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-gui
```

Expected: `aura-gui.exe` builds. If linking fails with `LNK1104`, stop the running `aura-gui.exe` process and rebuild.

- [ ] **Step 2: Launch foreground GUI**

Run:

```powershell
Start-Process -FilePath "C:\Users\21m15\OneDrive\바탕 화면\AURA\build-trim-gui\src\gui\Release\aura-gui.exe" -WorkingDirectory "C:\Users\21m15\OneDrive\바탕 화면\AURA"
```

- [ ] **Step 3: Manual GUI checklist**

Verify these visible states:

- `문자열` 탭에서 display mode `별칭` shows only rows with explicit aliases.
- `문자열` 탭에서 protected rows do not show raw email/phone/RRN in alias or masked modes.
- `LLM Gateway` check table uses readable Korean labels.
- `LLM Gateway` final status reaches `PASS` after protected analysis with active Rule Pack.
- Gateway prompt preview does not include raw sensitive values.
- Demo pane shows the flow: RE result collection, sensitive detection, masking, LLM transfer verification.

---

## Final Verification Commands

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected:

- All listed build targets succeed.
- All listed tests pass.
- Foreground GUI reflects the new display semantics.

---

## Self-Review

- Spec coverage:
  - Alias-only display is covered by Tasks 1 and 2.
  - Raw original exposure is covered by Task 3.
  - Gateway explanation/readability is covered by Task 4.
  - Demo scenario clarity is covered by Task 5.
  - CLI/MCP consistency is covered by Task 6.
  - Foreground GUI validation is covered by Task 7.
- Placeholder scan:
  - No TBD/TODO placeholders are left.
- Type consistency:
  - Uses existing `StringTableModel::Filter::Alias`, `GuiStringRecord`, `MainWindow`, `GatewayPane`, and existing smoke-test patterns.

---

## GSTACK REVIEW REPORT

**Autoplan run date:** 2026-05-12  
**Plan reviewed:** `docs/superpowers/plans/2026-05-12-demo-gateway-ui-fixes.md`  
**Base branch detected:** `origin/main`  
**Current branch:** `codex/safety-rule-pack-selection`  
**Restore point:** `C:\Users\21m15\.gstack\projects\AURA\codex-safety-rule-pack-selection-autoplan-restore-20260512-234744.md`

### Scope Detection

| Scope | Result | Evidence |
|---|---|---|
| UI scope | YES | Plan modifies `StringTableModel`, `MainWindow`, `GatewayPane`, `DemoModePane`; addresses visible combo/table/dock behavior. |
| DX scope | YES | Plan keeps CLI/MCP JSON aligned with GUI Gateway semantics. |
| Security/privacy scope | YES | Plan prevents raw sensitive value exposure in protected UI modes and LLM/MCP export preview. |

### CEO Review

| Question | Verdict | Decision |
|---|---|---|
| Is this the right problem? | YES | This directly addresses the professor feedback: the demo must show the protection Gateway clearly, not just internal masking logic. |
| Is scope calibrated? | MOSTLY YES | Alias filtering, raw exposure, Gateway explanation, and demo flow are the right next slice. |
| What is not in scope? | ACCEPTED | Full disassembler/Cutter parity, real LLM execution, and new malware engines are intentionally deferred. |
| Biggest 6-month regret | FLAGGED | If Gateway remains only a table of checks, the product still feels like “regex masking UI” rather than a protection Gateway. Task 5 now focuses the demo narrative. |

**CEO decision:** Proceed with selective expansion already captured in the plan. Do not add new engines before fixing the visible Gateway demo path.

### Design Review

| Area | Score | Finding | Plan Change |
|---|---:|---|---|
| Alias mode UX | 6/10 | Original plan tested model filtering but did not force real dock combo behavior. | Task 2 was updated to drive `stringsDisplayModeCombo` and assert the category switches to Alias. |
| Gateway readability | 7/10 | Internal check ids are accurate but poor for demos. | Task 4 keeps raw ids as tooltips but shows readable Korean labels. |
| Demo flow clarity | 6/10 | Existing stage cards already show four steps, so adding only another summary is insufficient. | Task 5 was changed to Korean presentation labels and raw/local-vs-export boundary clarity. |
| Raw data communication | 5/10 | Demo table has an `Original` column, which can confuse observers into thinking raw data is exported. | Task 5 now renames it to `UI 확인용 원본` and requires `LLM 전송`/preview to stay protected. |

**Design decision:** Keep the existing dense Qt tool UI, but add clearer labels and safer defaults. Avoid a separate landing/marketing screen.

### Engineering Review

| Area | Finding | Severity | Decision |
|---|---|---:|---|
| Task 1 | `Filter::Alias` should use `trimmed()` so whitespace-only aliases do not count. | Medium | Keep in plan. |
| Task 2 | Initial test draft bypassed real GUI controls by setting the model directly. | High | Updated plan to use actual combo widgets after analysis. |
| Task 3 | Display-layer fallback masking is correct, but must not mutate `exportValue` or persisted cache. | High | Plan explicitly keeps fallback display-only. |
| Task 4 | GUI label mapping should not change CLI/MCP machine-readable ids. | Medium | Plan requires tooltip/raw id preservation and CLI/MCP verification. |
| Task 5 | Existing `DemoModePane` already has stage cards; duplicate UI should be avoided. | Medium | Plan changed from “add flow” to “make flow presentation-ready.” |
| Verification | `gui_smoke` alone is not enough for user-facing GUI changes. | Medium | Plan keeps final `aura-gui` build and foreground manual checklist. |

**Engineering decision:** Implement Tasks 1-5 sequentially, then run CLI/MCP consistency checks. Do not bundle unrelated disassembler work into this slice.

### DevEx Review

| Surface | Finding | Decision |
|---|---|---|
| CLI JSON | Must remain stable for scripted demos. | Keep internal ids/statuses unchanged even if GUI labels become Korean. |
| MCP snapshot | Must not reintroduce raw sensitive values through display fields. | Keep `original_values_not_included` and raw-value exclusion tests. |
| Test commands | Commands are concrete and match existing build directory. | Keep. |
| Failure handling | Existing plan mentions `LNK1104` and foreground GUI lock. | Keep. |

### Autoplan Adjustments Applied

1. Task 2 was revised to test the actual GUI combo path, not only the model API.
2. Task 5 was revised because `DemoModePane` already has stage cards; the real issue is presentation clarity and raw/export boundary wording.
3. The plan now explicitly requires Korean/demo-safe table headers: `종류`, `UI 확인용 원본`, `마스킹`, `LLM 전송`.
4. The plan preserves machine-readable CLI/MCP Gateway ids while improving GUI labels.

### Review Status

| Phase | Status | Notes |
|---|---|---|
| CEO | PASS WITH NOTES | Correct next product slice; defer bigger RE-engine work. |
| Design | PASS WITH CHANGES | Adjusted Task 2 and Task 5. |
| Engineering | PASS WITH CHANGES | Added stricter GUI-control test and display-only masking constraint. |
| DevEx | PASS | CLI/MCP compatibility covered. |
| External voices | DEGRADED | Local `gstack-review-read` timed out; no external Codex/Claude review was run in this pass. |

**Final autoplan verdict:** APPROVED TO IMPLEMENT after the applied plan edits. Start with Task 1, then Task 2, because the user-visible alias bug is the immediate blocker.

