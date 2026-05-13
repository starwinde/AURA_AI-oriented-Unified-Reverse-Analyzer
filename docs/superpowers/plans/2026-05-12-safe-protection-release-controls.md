# Safe Protection Release Controls Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add safe, explicit UI/UX for changing string-protection display, transmission, recomputation, and deletion without accidentally exposing sensitive reverse-engineering output.

**Architecture:** Rule Pack selection remains an analysis policy, while display mode, LLM/MCP/CLI transmission policy, and persisted protection-result deletion become separate controls. GUI is canonical; CLI/MCP JSON mirrors the GUI protection policy and exposes enough audit state for demonstrations.

**Tech Stack:** C++17, Qt Widgets, cJSON, SQLite-backed protection store, doctest, CMake/MSVC Release build.

---

## Scope Boundaries

- Rule Pack checkboxes only control future detection/reanalysis.
- Existing protected strings stay protected until the user explicitly changes display mode or deletes protection results.
- GUI display mode does not automatically relax LLM/MCP/CLI transmission.
- Local LLM can be explicitly allowed to receive original values; external/MCP/CLI defaults stay protected.
- Deletion of protection results requires a confirmation dialog and an audit event.

## File Structure

- Modify `src/gui/safety_settings_dialog.h/.cpp`: add "Protection Results" section, recompute/delete buttons, and policy labels.
- Modify `src/gui/main_window.h/.cpp`: implement protection-result deletion/recompute helpers, transmission policy state, audit logging hooks, and dialog wiring.
- Modify `src/gui/string_table_model.h/.cpp`: keep parent row display stable while supporting selected display policy.
- Modify `src/core/string_protection_store.c`: add delete helpers for selected rows / rule-pack ids / all rows for a binary fingerprint.
- Modify safety headers that declare the protection store API, if present in `include/` or `src/core/`.
- Modify `src/mcp/mcp_tools.cpp` and `src/mcp/mcp_cli_bridge.cpp`: include `transmission_policy`, `value_sent`, `value_displayed`, and `protection_deleted` status where relevant.
- Modify CLI JSON code path, likely in `src/cli/` or current bridge code, to mirror protected transmission defaults.
- Test `tests/unit/safety/safety_unit.cpp`: protection-store deletion API.
- Test `tests/integration/gui_smoke/gui_smoke.cpp`: Safety Assets UI, confirmation behavior, display mode separation, deletion/recompute.
- Test `tests/integration/cli_smoke/cli_smoke.cpp`: JSON still sends protected values by default.
- Test `tests/integration/mcp_smoke/mcp_smoke.cpp`: MCP snapshot uses protected values unless local policy explicitly allows original.

---

### Task 1: Protection Policy Vocabulary

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI policy test**

Add a `gui_smoke` subcase near existing string protection tests:

```cpp
SUBCASE("string display policy is separate from transmission policy") {
    aura::gui::MainWindow window;
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));
    REQUIRE_FALSE(window.stringList().isEmpty());

    REQUIRE(window.setStringDisplayModeAt(0, 0));
    CHECK(window.stringList()[0].protectedValue == window.stringList()[0].content);
    CHECK(window.stringTransmissionValueAt(0, aura::gui::TransmissionTarget::ExternalLlm)
          != window.stringList()[0].content);
    CHECK(window.stringTransmissionValueAt(0, aura::gui::TransmissionTarget::Mcp)
          != window.stringList()[0].content);
}
```

- [ ] **Step 2: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: build fails because `TransmissionTarget` or `stringTransmissionValueAt` is not defined.

- [ ] **Step 3: Add policy enum and accessor**

In `src/gui/main_window.h`, add:

```cpp
enum class TransmissionTarget {
    GuiDisplay = 0,
    LocalLlm,
    ExternalLlm,
    Mcp,
    Cli,
};
```

Add public method:

```cpp
QString stringTransmissionValueAt(
    int stringRow,
    TransmissionTarget target) const;
```

In `src/gui/main_window.cpp`, implement:

```cpp
QString MainWindow::stringTransmissionValueAt(
    int stringRow,
    TransmissionTarget target) const {
    if (stringRow < 0 || stringRow >= m_strings.size()) return QString();
    const auto& s = m_strings[stringRow];
    if (target == TransmissionTarget::LocalLlm) {
        const QSettings settings(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
        if (settings.value(QStringLiteral("privacy/localLlmAllowOriginal"), false).toBool()) {
            return s.content;
        }
    }
    if (!s.exportValue.isEmpty() && s.exportValue != s.content) return s.exportValue;
    if (!s.maskedContent.isEmpty() && s.maskedContent != s.content) return s.maskedContent;
    if (!s.alias.isEmpty()) return s.alias;
    return s.content;
}
```

- [ ] **Step 4: Run test to verify pass**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): separate display and transmission protection policy"
```

---

### Task 2: Safety Assets Protection Results Section

**Files:**
- Modify: `src/gui/safety_settings_dialog.h`
- Modify: `src/gui/safety_settings_dialog.cpp`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing UI smoke test**

Add:

```cpp
SUBCASE("Safety Assets exposes explicit protection result controls") {
    aura::gui::SafetySettingsDialog dlg(
        aura::safety::defaultSafetyProfile(), QStringLiteral("default"));

    auto* recompute = dlg.findChild<QPushButton*>(
        QStringLiteral("safetyRecomputeProtectionButton"));
    auto* remove = dlg.findChild<QPushButton*>(
        QStringLiteral("safetyDeleteProtectionButton"));
    auto* help = dlg.findChild<QLabel*>(
        QStringLiteral("safetyProtectionPolicyHelpLabel"));

    REQUIRE(recompute != nullptr);
    REQUIRE(remove != nullptr);
    REQUIRE(help != nullptr);
    CHECK(help->text().contains(QStringLiteral("기존 보호 결과")));
}
```

- [ ] **Step 2: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: child widgets are not found.

- [ ] **Step 3: Add UI controls**

In `SafetySettingsDialog`, add a section below Rule Pack controls:

```cpp
auto* protectionGroup = new QGroupBox(QStringLiteral("보호 결과 관리"), this);
auto* protectionLayout = new QVBoxLayout(protectionGroup);
m_protectionPolicyHelpLabel = new QLabel(
    QStringLiteral("Rule Pack 해제는 다음 분석 정책만 바꿉니다. 기존 보호 결과는 명시적으로 재계산하거나 삭제할 때만 바뀝니다."),
    protectionGroup);
m_protectionPolicyHelpLabel->setObjectName(QStringLiteral("safetyProtectionPolicyHelpLabel"));
m_recomputeProtectionButton = new QPushButton(QStringLiteral("보호 결과 재계산"), protectionGroup);
m_recomputeProtectionButton->setObjectName(QStringLiteral("safetyRecomputeProtectionButton"));
m_deleteProtectionButton = new QPushButton(QStringLiteral("보호 결과 삭제..."), protectionGroup);
m_deleteProtectionButton->setObjectName(QStringLiteral("safetyDeleteProtectionButton"));
protectionLayout->addWidget(m_protectionPolicyHelpLabel);
protectionLayout->addWidget(m_recomputeProtectionButton);
protectionLayout->addWidget(m_deleteProtectionButton);
```

Expose signals:

```cpp
signals:
    void recomputeProtectionRequested();
    void deleteProtectionRequested();
```

Wire buttons:

```cpp
connect(m_recomputeProtectionButton, &QPushButton::clicked,
        this, &SafetySettingsDialog::recomputeProtectionRequested);
connect(m_deleteProtectionButton, &QPushButton::clicked,
        this, &SafetySettingsDialog::deleteProtectionRequested);
```

- [ ] **Step 4: Run test to verify pass**

Run the same `gui_smoke` command. Expected: pass.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/safety_settings_dialog.h src/gui/safety_settings_dialog.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): add protection result controls to safety assets"
```

---

### Task 3: Protection Result Deletion API

**Files:**
- Modify: `src/core/string_protection_store.c`
- Modify: store API header used by `main_window.cpp`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing core deletion test**

Add to `safety_unit.cpp`:

```cpp
TEST_CASE("string protection store deletes protection rows for fingerprint") {
    AuraStringProtectionStore* store = aura_string_protection_store_open(tempDbPath());
    REQUIRE(store != nullptr);

    AuraStringProtectionFinding rec{};
    std::strncpy(rec.fingerprint, "abc", sizeof(rec.fingerprint) - 1);
    rec.string_addr = 0x1000;
    std::strncpy(rec.mask_token, "01********78", sizeof(rec.mask_token) - 1);
    rec.display_mode = 2;
    REQUIRE(aura_string_protection_store_save(store, &rec) == 0);

    REQUIRE(aura_string_protection_store_delete_for_fingerprint(store, "abc") == 1);
    AuraStringProtectionFinding got{};
    CHECK(aura_string_protection_store_get(store, "abc", 0x1000, &got) != 0);
    aura_string_protection_store_close(store);
}
```

- [ ] **Step 2: Run test to verify failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: missing delete API.

- [ ] **Step 3: Implement delete API**

Add C API:

```c
int aura_string_protection_store_delete_for_fingerprint(
    AuraStringProtectionStore* store,
    const char* fingerprint);
```

Implementation:

```c
int aura_string_protection_store_delete_for_fingerprint(
    AuraStringProtectionStore* store,
    const char* fingerprint) {
    if (!store || !fingerprint || !fingerprint[0]) return -1;
    sqlite3_stmt* st = NULL;
    const char* sql =
        "DELETE FROM string_protection WHERE fingerprint = ?1;";
    if (sqlite3_prepare_v2(store->db, sql, -1, &st, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(st, 1, fingerprint, -1, SQLITE_TRANSIENT);
    const int rc = sqlite3_step(st);
    const int changed = sqlite3_changes(store->db);
    sqlite3_finalize(st);
    return rc == SQLITE_DONE ? changed : -1;
}
```

- [ ] **Step 4: Add GUI helper**

In `MainWindow`, add:

```cpp
bool clearStringProtectionForCurrentBinary();
```

Implementation:

```cpp
bool MainWindow::clearStringProtectionForCurrentBinary() {
    const QString fingerprint = currentFingerprintHex(m_currentSha256);
    if (fingerprint.isEmpty()) return false;
    AuraStringProtectionStore* store =
        aura_string_protection_store_open(m_projectPath.toUtf8().constData());
    if (!store) return false;
    const int deleted = aura_string_protection_store_delete_for_fingerprint(
        store, fingerprint.toUtf8().constData());
    aura_string_protection_store_close(store);
    if (deleted < 0) return false;
    for (auto& s : m_strings) {
        s.maskedContent.clear();
        s.exportValue = s.content;
        s.protectedValue = s.content;
        s.displayMode = 0;
        s.hasProtection = false;
        s.findings.clear();
        s.protectionSummary.clear();
    }
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
    return true;
}
```

- [ ] **Step 5: Run tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit gui_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_unit|gui_smoke" --output-on-failure
```

Expected: both pass.

- [ ] **Step 6: Commit**

```powershell
git add src/core/string_protection_store.c src/gui/main_window.h src/gui/main_window.cpp tests/unit/safety/safety_unit.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(safety): support explicit protection result deletion"
```

---

### Task 4: Safe Confirmation Dialog UX

**Files:**
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/main_window.h`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing testable helper test**

Add helper-level test:

```cpp
SUBCASE("protection deletion confirmation text is explicit") {
    const QString text = aura::gui::MainWindow::protectionDeletionWarningText();
    CHECK(text.contains(QStringLiteral("원본 문자열")));
    CHECK(text.contains(QStringLiteral("삭제")));
    CHECK(text.contains(QStringLiteral("되돌릴 수")));
}
```

- [ ] **Step 2: Run failure**

Run `gui_smoke`. Expected: helper missing.

- [ ] **Step 3: Implement confirmation text and action**

Add static method:

```cpp
static QString protectionDeletionWarningText();
```

Implementation:

```cpp
QString MainWindow::protectionDeletionWarningText() {
    return QStringLiteral(
        "저장된 보호 결과를 삭제하면 이 바이너리의 문자열이 원본 문자열 기준으로 다시 표시될 수 있습니다.\n\n"
        "Rule Pack 설정은 유지되지만, 기존 마스킹/finding/전송 보호 캐시는 제거됩니다.\n"
        "이 작업은 되돌릴 수 없습니다.");
}
```

Dialog handler:

```cpp
void MainWindow::confirmAndClearStringProtection() {
    const auto answer = QMessageBox::warning(
        this,
        QStringLiteral("보호 결과 삭제"),
        protectionDeletionWarningText(),
        QMessageBox::Cancel | QMessageBox::Yes,
        QMessageBox::Cancel);
    if (answer != QMessageBox::Yes) return;
    if (clearStringProtectionForCurrentBinary()) {
        statusBar()->showMessage(QStringLiteral("보호 결과를 삭제했습니다."), 5000);
    }
}
```

- [ ] **Step 4: Wire Safety dialog button**

When opening `SafetySettingsDialog`, connect:

```cpp
connect(&dlg, &SafetySettingsDialog::deleteProtectionRequested,
        this, &MainWindow::confirmAndClearStringProtection);
```

- [ ] **Step 5: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: pass.

- [ ] **Step 6: Commit**

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): require confirmation before deleting protection results"
```

---

### Task 5: Recompute Protection Results From Current Safety Profile

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing recompute test**

Add:

```cpp
SUBCASE("protection recompute applies current safety profile without deleting binary") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));
    REQUIRE_FALSE(window.stringList().isEmpty());

    REQUIRE(window.clearStringProtectionForCurrentBinary());
    CHECK_FALSE(window.stringList()[0].hasProtection);

    REQUIRE(window.recomputeStringProtectionForCurrentBinary());
    bool protectedAgain = false;
    for (const auto& s : window.stringList()) {
        protectedAgain = protectedAgain || s.hasProtection;
    }
    CHECK(protectedAgain);
}
```

- [ ] **Step 2: Run failure**

Run `gui_smoke`. Expected: `recomputeStringProtectionForCurrentBinary` missing.

- [ ] **Step 3: Implement recompute helper**

Add:

```cpp
bool recomputeStringProtectionForCurrentBinary();
```

Implementation should:

```cpp
bool MainWindow::recomputeStringProtectionForCurrentBinary() {
    if (m_strings.isEmpty()) return false;
    const auto profile = activeSafetyProfile();
    for (auto& s : m_strings) {
        auto findings = aura::safety::scanStringWithRulePacks(
            s.content.toStdString(), profile);
        auto protectedView = aura::safety::buildProtectedStringView(
            s.content.toStdString(), findings);
        s.findings.clear();
        for (const auto& f : protectedView.findings) {
            GuiStringRecord::ProtectionFinding gf;
            gf.detectorId = QString::fromStdString(f.detector_id);
            gf.kind = QString::fromStdString(f.kind);
            gf.maskToken = QString::fromStdString(f.mask_token);
            gf.start = static_cast<int>(f.start);
            gf.length = static_cast<int>(f.length);
            s.findings.push_back(gf);
        }
        s.hasProtection = !protectedView.findings.empty();
        s.maskedContent = s.hasProtection
            ? QString::fromStdString(protectedView.masked_content)
            : QString();
        s.displayMode = s.hasProtection ? 2 : 0;
        refreshProtectedValue(s);
    }
    persistStringProtectionRows(m_projectPath, currentFingerprintHex(m_currentSha256), m_strings);
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
    return true;
}
```

- [ ] **Step 4: Wire Safety dialog recompute button**

Connect:

```cpp
connect(&dlg, &SafetySettingsDialog::recomputeProtectionRequested,
        this, [this]() {
    if (recomputeStringProtectionForCurrentBinary()) {
        statusBar()->showMessage(QStringLiteral("현재 안전 자산 기준으로 보호 결과를 재계산했습니다."), 5000);
    }
});
```

- [ ] **Step 5: Run tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: pass.

- [ ] **Step 6: Commit**

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): recompute protection results from safety assets"
```

---

### Task 6: Strings Dock Display Mode UX

**Files:**
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/string_table_model.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing UI test**

Add:

```cpp
SUBCASE("Strings dock exposes display mode selector") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));

    auto* combo = window.findChild<QComboBox*>(
        QStringLiteral("stringsDisplayModeCombo"));
    REQUIRE(combo != nullptr);
    CHECK(combo->findText(QStringLiteral("마스킹")) >= 0);
    CHECK(combo->findText(QStringLiteral("별칭")) >= 0);
    CHECK(combo->findText(QStringLiteral("원본")) >= 0);
}
```

- [ ] **Step 2: Run failure**

Run `gui_smoke`. Expected: combo missing.

- [ ] **Step 3: Add selector**

In Strings dock toolbar row:

```cpp
m_stringsDisplayModeCombo = new QComboBox(stringsRoot);
m_stringsDisplayModeCombo->setObjectName(QStringLiteral("stringsDisplayModeCombo"));
m_stringsDisplayModeCombo->addItem(QStringLiteral("마스킹"), 2);
m_stringsDisplayModeCombo->addItem(QStringLiteral("별칭"), 1);
m_stringsDisplayModeCombo->addItem(QStringLiteral("원본"), 0);
stringsFilterRow->addWidget(m_stringsDisplayModeCombo);
connect(m_stringsDisplayModeCombo, &QComboBox::currentIndexChanged,
        this, [this]() {
    const int mode = m_stringsDisplayModeCombo->currentData().toInt();
    for (auto& s : m_strings) {
        s.displayMode = mode;
        refreshProtectedValue(s);
    }
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
});
```

- [ ] **Step 4: Run test**

Run `gui_smoke`. Expected: pass.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): add string display mode selector"
```

---

### Task 7: CLI/MCP Protected Transmission JSON

**Files:**
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `src/mcp/mcp_cli_bridge.cpp`
- Modify: CLI JSON source under `src/cli/`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Write failing JSON tests**

Expected fields in CLI/MCP string payload:

```json
{
  "display_value": "010********78",
  "transmission_value": "010********78",
  "transmission_policy": "protected",
  "original_included": false
}
```

In `cli_smoke`, assert:

```cpp
CHECK(output.find("\"transmission_policy\":\"protected\"") != std::string::npos);
CHECK(output.find("\"original_included\":false") != std::string::npos);
```

In `mcp_smoke`, assert equivalent JSON fields on the snapshot/demo response.

- [ ] **Step 2: Run failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: fields missing.

- [ ] **Step 3: Implement JSON fields**

For every string object sent through CLI/MCP, add:

```cpp
cJSON_AddStringToObject(obj, "display_value", displayValue.toUtf8().constData());
cJSON_AddStringToObject(obj, "transmission_value", transmissionValue.toUtf8().constData());
cJSON_AddStringToObject(obj, "transmission_policy", "protected");
cJSON_AddBoolToObject(obj, "original_included", false);
```

Local-only debug mode may use:

```cpp
cJSON_AddStringToObject(obj, "transmission_policy", "local_original_allowed");
cJSON_AddBoolToObject(obj, "original_included", true);
```

- [ ] **Step 4: Run tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: pass.

- [ ] **Step 5: Commit**

```powershell
git add src/mcp src/cli tests/integration/cli_smoke/cli_smoke.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat: expose protected transmission policy in cli and mcp"
```

---

### Task 8: Audit Log For Protection Policy Changes

**Files:**
- Modify: `src/gui/main_window.cpp`
- Modify: `src/gui/main_window.h`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing audit test**

Add:

```cpp
SUBCASE("protection deletion writes audit event") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(
        0, AURA_ANALYSIS_LEVEL_FULL,
        aura::safety::StringProtectionMode::Mask));
    REQUIRE(window.clearStringProtectionForCurrentBinary());
    const QString audit = window.latestSafetyAuditEventForTest();
    CHECK(audit.contains(QStringLiteral("protection_results_deleted")));
    CHECK(audit.contains(QStringLiteral("fingerprint")));
}
```

- [ ] **Step 2: Run failure**

Run `gui_smoke`. Expected: audit helper missing.

- [ ] **Step 3: Implement minimal audit event**

Add member:

```cpp
QString m_latestSafetyAuditEventForTest;
```

Add helper:

```cpp
void recordSafetyAuditEvent(const QString& event, const QString& detail);
QString latestSafetyAuditEventForTest() const;
```

Implementation:

```cpp
void MainWindow::recordSafetyAuditEvent(const QString& event, const QString& detail) {
    m_latestSafetyAuditEventForTest =
        QStringLiteral("%1 fingerprint=%2 detail=%3")
            .arg(event, currentFingerprintHex(m_currentSha256), detail);
}
```

Call it in deletion/recompute/display-policy changes.

- [ ] **Step 4: Run tests**

Run `gui_smoke`. Expected: pass.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat(gui): audit protection policy changes"
```

---

### Task 9: Foreground GUI Demonstration

**Files:**
- No source changes unless a GUI defect is found.

- [ ] **Step 1: Build final targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura-gui
```

Expected: all targets build.

- [ ] **Step 2: Run tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected: all tests pass.

- [ ] **Step 3: Launch foreground GUI**

Run:

```powershell
Get-Process | Where-Object { $_.ProcessName -eq 'aura-gui' } | Stop-Process -Force -ErrorAction SilentlyContinue
$env:AURA_GUI_RPC_PORT='27654'
$env:AURA_GUI_RPC_TOKEN='demo-token'
Start-Process -FilePath (Resolve-Path 'build-trim-gui\src\gui\Release\aura-gui.exe') -ArgumentList @('--rpc-port','27654') -WorkingDirectory (Get-Location) -PassThru
```

Expected: AURA GUI opens in foreground.

- [ ] **Step 4: Manual GUI script**

In GUI:

1. Open or add the sensitive string fixture.
2. Analyze with string protection enabled.
3. Verify Strings dock defaults to masked values.
4. Open `Settings -> Safety Assets`.
5. Uncheck a Rule Pack and click `선택 적용`.
6. Confirm existing protected strings remain masked.
7. Click `보호 결과 재계산`.
8. Confirm results follow the current Rule Pack selection.
9. Click `보호 결과 삭제...`.
10. Cancel once and confirm nothing changes.
11. Click again, confirm deletion, and verify protected results are removed.
12. Run CLI/MCP demo and confirm JSON still uses protected transmission policy by default.

- [ ] **Step 5: Commit final verification note if docs exist**

If the repo tracks QA notes, update the relevant QA document with:

```markdown
## Safe Protection Release Controls

- GUI verified: Safety Assets apply does not auto-delete existing protection.
- GUI verified: explicit recompute follows current Rule Pack selection.
- GUI verified: explicit delete requires confirmation.
- CLI/MCP verified: default transmission JSON remains protected.
```

Commit:

```powershell
git add docs tests src
git commit -m "test: verify safe protection release controls"
```

---

## Self-Review

- Spec coverage: Rule Pack off, display mode, transmission policy, delete/recompute, UI confirmation, CLI/MCP mirror, and GUI verification are all covered.
- Placeholder scan: no task relies on "TBD" or unspecified behavior.
- Type consistency: `TransmissionTarget`, `stringTransmissionValueAt`, `clearStringProtectionForCurrentBinary`, `recomputeStringProtectionForCurrentBinary`, and audit helper names are defined before later use.
- Risk: exact SQLite table/column names in `string_protection_store.c` must be verified during implementation before finalizing the delete SQL.
- Risk: `SafetySettingsDialog` constructor signature may need minor adjustment if the current class requires more context than profile/id.
