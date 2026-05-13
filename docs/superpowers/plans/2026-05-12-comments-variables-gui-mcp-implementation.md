# Comments and Variables GUI/MCP Completion Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make comments and variable edits real GUI features: persistent, visible after reopen, and exposed through protected CLI/MCP output.

**Architecture:** Reuse AURA's existing `override_store` pattern instead of inventing a GUI-only store. GUI actions create typed override records, analyze/decompile display joins engine records with overrides, GUI RPC exposes protected summaries, and MCP wraps GUI RPC as the demo/agent surface. Comments ship first because they validate the storage/display/RPC/MCP loop before variable-key complexity.

**Tech Stack:** C++17, Qt Widgets, cJSON, SQLite-backed `override_store`, CMake/MSBuild, existing `gui_smoke`, `cli_smoke`, and `mcp_smoke`.

---

## Scope Boundary

This plan implements:

- Function-level comments that persist through project reopen.
- Decompile display rendering for saved comments.
- Protected comment summaries in GUI RPC and MCP.
- Variable alias/type overrides that persist through project reopen.
- GUI display/API access for applied variable overrides.
- Protected variable override summaries in GUI RPC and MCP.

This plan does not implement:

- Raw decompile/comment dumping through MCP.
- Instruction-level comments beyond a stable address target if the current store cannot safely key them.
- New malware analysis, dynamic execution, or live malware sample handling.
- Semantic type inference. Variable type edits are user-applied overrides only.

---

## File Structure

### Existing Files To Modify

- `include/override_store.h`
  - Keep as-is unless a payload limit issue forces a small helper comment update.

- `include/override_identity.h`
  - Keep existing `aura_override_key_from_variable_record()`; do not add a second identity system.

- `src/gui/main_window.h`
  - Add GUI-facing comment and variable override structs.
  - Add testable public APIs for comment/variable mutation and readback.
  - Add private key-builder declarations.

- `src/gui/main_window.cpp`
  - Implement comment apply/readback/rendering.
  - Implement variable override key building, apply, readback, and display join.
  - Extend decompile display rendering to prepend/inline saved comments.
  - Replace variable candidate dialog dry-run behavior with actual apply calls.

- `src/gui/rpc_server.cpp`
  - Add protected comment and variable override JSON in `demo_snapshot`.
  - Optionally add dedicated `list_comments` / `list_variable_overrides` RPC methods only if the snapshot becomes too crowded.

- `src/cli/main.cpp`
  - Add/extend `aura gui demo-snapshot` expectations only if new fields require CLI wrapper support. Prefer no new raw commands unless tests need them.

- `src/mcp/mcp_tools.cpp`
  - Expose any new GUI protected tools if added.
  - Otherwise ensure `aura_gui_demo_snapshot` schema documents comments/variables.

- `src/mcp/mcp_cli_bridge.cpp`
  - Pass through protected comment/variable fields from GUI RPC.

- `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add GUI round-trip tests for comments and variables.

- `tests/integration/cli_smoke/cli_smoke.cpp`
  - Add CLI GUI help/schema assertions if new commands are added.

- `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Add MCP protected snapshot assertions for comments and variable overrides.

### New Files

No new source files are required. If `main_window.cpp` grows too difficult to review, split pure helper functions into:

- `src/gui/override_projection.cpp`
- `src/gui/override_projection.h`

Only do this split if implementation exceeds a narrow helper block; avoid speculative refactoring.

---

## Task 1: Comment Mutation API and GUI Round-Trip

**Files:**

- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a failing GUI smoke test for function comment round-trip**

Add this subcase near the existing rename/reset override test in `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("function comments persist and reappear after reopen") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(window.functionCount() >= 1);

    const QString note = QStringLiteral("review note: check arithmetic");
    REQUIRE(window.setFunctionCommentAt(0, note));
    CHECK(window.functionCommentAt(0) == note);

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(reopened.functionCount() >= 1);
    CHECK(reopened.functionCommentAt(0) == note);
}
```

- [ ] **Step 2: Run the test and verify it fails to compile**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected:

```text
error C2039: 'setFunctionCommentAt': is not a member of 'aura::gui::MainWindow'
```

- [ ] **Step 3: Declare the testable API**

In `src/gui/main_window.h`, add public methods next to `renameFunctionAt()` / `resetFunctionNameAt()`:

```cpp
bool setFunctionCommentAt(int functionRow, const QString& comment);
QString functionCommentAt(int functionRow) const;
```

Add a private helper declaration near `applyOverridesToFunctions()`:

```cpp
void applyCommentOverridesToFunctions();
```

If there is no comment storage field on `GuiFunctionRecord`, add one:

```cpp
QString comment;
bool hasComment = false;
```

- [ ] **Step 4: Implement minimal comment persistence**

In `src/gui/main_window.cpp`, implement:

```cpp
bool MainWindow::setFunctionCommentAt(int row, const QString& comment) {
    if (!m_overrideStore) return false;
    if (row < 0 || row >= m_functions.size()) return false;
    const QString trimmed = comment.trimmed();
    if (trimmed.isEmpty()) return false;

    AuraOverrideKey key = buildKeyForFunction(row);
    key.target_kind = AURA_OVERRIDE_TARGET_ANNOTATION;

    AuraOverrideRecord rec{};
    rec.key = key;
    rec.payload.kind = AURA_OVERRIDE_PAYLOAD_ANNOTATION;
    const QByteArray utf8 = trimmed.toUtf8();
    std::strncpy(rec.payload.text, utf8.constData(),
                 AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
    rec.status = AURA_OVERRIDE_STATUS_ACTIVE;

    if (aura_override_store_put(m_overrideStore, &rec) != 0)
        return false;

    applyCommentOverridesToFunctions();
    return true;
}

QString MainWindow::functionCommentAt(int row) const {
    if (row < 0 || row >= m_functions.size()) return {};
    return m_functions[row].comment;
}
```

Implement the join:

```cpp
void MainWindow::applyCommentOverridesToFunctions() {
    if (!m_overrideStore) return;
    for (int i = 0; i < m_functions.size(); ++i) {
        AuraOverrideKey key = buildKeyForFunction(i);
        key.target_kind = AURA_OVERRIDE_TARGET_ANNOTATION;

        AuraOverrideRecord rec{};
        const int rc = aura_override_store_get(m_overrideStore, &key, &rec);
        if (rc == 0 && rec.payload.kind == AURA_OVERRIDE_PAYLOAD_ANNOTATION) {
            m_functions[i].comment = QString::fromUtf8(rec.payload.text);
            m_functions[i].hasComment = !m_functions[i].comment.isEmpty();
        } else {
            m_functions[i].comment.clear();
            m_functions[i].hasComment = false;
        }
    }
}
```

- [ ] **Step 5: Call the comment join after analysis and mutation**

In `MainWindow::runAnalyze()`, after `applyOverridesToFunctions();`, call:

```cpp
applyCommentOverridesToFunctions();
```

In `setFunctionCommentAt()`, keep the immediate `applyCommentOverridesToFunctions()` call.

- [ ] **Step 6: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 2: Render Saved Comments in Decompile Display

**Files:**

- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a failing test for decompile comment rendering**

Add a subcase after the comment round-trip test:

```cpp
SUBCASE("function comments render in decompile display") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(window.functionCount() >= 1);

    const QString note = QStringLiteral("manual comment visible in decompile");
    REQUIRE(window.setFunctionCommentAt(0, note));

    const QString raw = QStringLiteral("int f(void) { return 0; }");
    const QString shown = window.renderDecompileTextForFunctionRow(0, raw);
    CHECK(shown.contains(note));
    CHECK(shown.contains(raw));
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
CHECK(shown.contains(note)) is NOT correct
```

- [ ] **Step 3: Implement comment prefix rendering**

In `MainWindow::renderDecompileTextForDisplay()`, before returning `out`, add:

```cpp
if (m_activeFunctionAddr != 0) {
    const int row = findFunctionRowByEntry(m_functions, m_activeFunctionAddr);
    if (row >= 0 && row < m_functions.size() && m_functions[row].hasComment) {
        out.prepend(QStringLiteral("// AURA comment: %1\n")
                        .arg(m_functions[row].comment));
    }
}
```

Add a public test helper instead of weakening the product behavior:

```cpp
QString renderDecompileTextForFunctionRow(int functionRow,
                                          const QString& rawText) const;
```

Its implementation should apply the same string-address substitution and comment prefix for the supplied row. Use this helper in the test if `m_activeFunctionAddr` cannot be set cleanly.

- [ ] **Step 4: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 3: Replace Modal Comment Path With Shared API

**Files:**

- Modify: `src/gui/main_window.cpp`
- Test: covered by Task 1 and Task 2.

- [ ] **Step 1: Refactor `onDecompContextAddComment()`**

Change `onDecompContextAddComment()` so it uses `setFunctionCommentAt()` after obtaining text:

```cpp
const int row = findFunctionRowByEntry(m_functions, m_activeFunctionAddr);
if (row < 0) {
    statusBar()->showMessage(QStringLiteral("Comment: 활성 함수 없음."));
    return;
}

if (setFunctionCommentAt(row, text.trimmed())) {
    statusBar()->showMessage(
        QStringLiteral("Comment 추가 (function 0x%1, near addr 0x%2): \"%3\"")
            .arg(m_activeFunctionAddr, 0, 16)
            .arg(addr, 0, 16)
            .arg(text.trimmed()));
} else {
    statusBar()->showMessage(QStringLiteral("Comment 저장 실패."));
}
```

- [ ] **Step 2: Remove duplicate store-write code**

Delete the old local `AuraOverrideRecord rec{}` write block from `onDecompContextAddComment()`. The only write path should be `setFunctionCommentAt()`.

- [ ] **Step 3: Verify no duplicate comment persistence paths remain**

Run:

```powershell
Select-String -Path 'src\gui\main_window.cpp' -Pattern 'AURA_OVERRIDE_PAYLOAD_ANNOTATION|setFunctionCommentAt'
```

Expected:

- One annotation payload write in `setFunctionCommentAt()`.
- `onDecompContextAddComment()` calls `setFunctionCommentAt()`.

- [ ] **Step 4: Verify tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 4: Protected Comment Output in GUI RPC and MCP

**Files:**

- Modify: `src/gui/rpc_server.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
- Modify if needed: `src/mcp/mcp_cli_bridge.cpp`

- [ ] **Step 1: Add failing MCP smoke expectations**

In `tests/integration/mcp_smoke/mcp_smoke.cpp`, extend the existing `aura_gui_demo_snapshot` test to assert the response can carry comment summaries:

```cpp
CHECK(out.find("comments_sent") != std::string::npos);
CHECK(out.find("comments_total") != std::string::npos);
CHECK(out.find("raw_comment_text_omitted") != std::string::npos);
```

Do not require a non-empty comment in this smoke test unless the test starts a GUI and creates one. Schema presence is enough for MCP registration.

- [ ] **Step 2: Add comment counts to RPC snapshot**

In `src/gui/rpc_server.cpp`, inside `demo_snapshot`, add:

```cpp
int commentsTotal = 0;
for (const auto& fn : functions) {
    if (fn.hasComment) ++commentsTotal;
}
const int commentsIncluded = std::min(commentsTotal, 5);
cJSON_AddNumberToObject(counts, "comments_total", commentsTotal);
cJSON_AddNumberToObject(counts, "comments_included", commentsIncluded);
```

Add the output array:

```cpp
cJSON* comments = cJSON_AddArrayToObject(r, "comments_sent");
int emittedComments = 0;
for (int i = 0; i < functions.size() && emittedComments < commentsIncluded; ++i) {
    const auto& fn = functions[i];
    if (!fn.hasComment) continue;
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "function_row", i);
    cJSON_AddStringToObject(item, "function_name",
                            fn.name.toUtf8().constData());
    cJSON_AddStringToObject(item, "comment",
                            QStringLiteral("<COMMENT_OMITTED>")
                                .toUtf8().constData());
    cJSON_AddBoolToObject(item, "raw_comment_text_omitted", true);
    cJSON_AddItemToArray(comments, item);
    ++emittedComments;
}
```

Update omissions:

```cpp
cJSON_AddBoolToObject(omissions, "raw_comment_text_omitted", true);
```

- [ ] **Step 3: Keep MCP pass-through protected**

If `aura_gui_demo_snapshot` already passes `aura gui demo-snapshot` text through, no bridge change is needed. If bridge filtering drops unknown fields, update `src/mcp/mcp_cli_bridge.cpp` so `comments_sent` and `comments_total` are preserved.

- [ ] **Step 4: Verify MCP and GUI**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke gui_smoke
ctest --test-dir build-trim-gui -C Release -R "mcp_smoke|gui_smoke" --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 5: Variable Override Key Builder and Persistence API

**Files:**

- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI test for variable override persistence**

Add a subcase near existing variable candidate tests:

```cpp
SUBCASE("variable alias/type overrides persist after reopen when variables exist") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));

    if (window.variableList().isEmpty()) {
        MESSAGE("SKIP: fixture produced no variables");
        return;
    }

    const quint32 varId = window.variableList()[0].varId;
    REQUIRE(window.setVariableOverrideById(
        varId, QStringLiteral("user_counter"), QStringLiteral("int32_t")));

    const auto applied = window.variableOverrideById(varId);
    CHECK(applied.alias == QStringLiteral("user_counter"));
    CHECK(applied.typeName == QStringLiteral("int32_t"));

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    if (!reopened.variableList().isEmpty()) {
        const auto reopenedApplied = reopened.variableOverrideById(varId);
        CHECK(reopenedApplied.alias == QStringLiteral("user_counter"));
        CHECK(reopenedApplied.typeName == QStringLiteral("int32_t"));
    }
}
```

- [ ] **Step 2: Declare variable override data**

In `src/gui/main_window.h`, add:

```cpp
struct GuiVariableOverride {
    quint32 varId = 0;
    quint32 functionId = 0;
    QString alias;
    QString typeName;
    bool hasAlias = false;
    bool hasType = false;
};
```

Add methods:

```cpp
bool setVariableOverrideById(quint32 varId,
                             const QString& alias,
                             const QString& typeName);
GuiVariableOverride variableOverrideById(quint32 varId) const;
QVector<GuiVariableOverride> variableOverrideList() const;
```

Add private state:

```cpp
QHash<quint32, GuiVariableOverride> m_variableOverrides;
```

Add private helpers:

```cpp
AuraOverrideKey buildKeyForVariable(int variableRow) const;
void applyOverridesToVariables();
int variableRowById(quint32 varId) const;
```

- [ ] **Step 3: Implement `buildKeyForVariable()` using the existing core helper**

In `src/gui/main_window.cpp`, implement:

```cpp
int MainWindow::variableRowById(quint32 varId) const {
    for (int i = 0; i < m_variables.size(); ++i) {
        if (m_variables[i].varId == varId) return i;
    }
    return -1;
}

AuraOverrideKey MainWindow::buildKeyForVariable(int row) const {
    AuraVariableRecord rec{};
    if (row < 0 || row >= m_variables.size()) return rec.key; // do not use this line literally if it fails compile
}
```

Use this compile-safe implementation instead:

```cpp
AuraOverrideKey MainWindow::buildKeyForVariable(int row) const {
    AuraOverrideKey missing{};
    missing.confidence = AURA_OVERRIDE_CONFIDENCE_MISSING;
    if (row < 0 || row >= m_variables.size()) return missing;

    const auto& v = m_variables[row];
    AuraVariableRecord rec{};
    rec.var_id = static_cast<AuraVariableId>(v.varId);
    rec.function_id = static_cast<AuraFunctionId>(v.functionId);
    rec.stack_offset = v.stackOffset;
    const QByteArray name = v.name.toUtf8();
    std::strncpy(rec.name, name.constData(), sizeof(rec.name) - 1);
    const QByteArray kind = v.kind.toUtf8();
    std::strncpy(rec.kind, kind.constData(), sizeof(rec.kind) - 1);
    std::strncpy(rec.provenance.source, "rizin",
                 sizeof(rec.provenance.source) - 1);
    rec.provenance.confidence = 1.0f;
    rec.provenance.completeness = 1.0f;

    const AuraEngineManifest* manifest = aura_rizin_adapter_manifest();
    return aura_override_key_from_variable_record(&rec, manifest,
                                                  &m_currentFingerprint);
}
```

- [ ] **Step 4: Encode alias/type into payload text**

Use a simple line format that stays inside `AURA_OVERRIDE_PAYLOAD_TEXT_CAP`:

```text
alias=user_counter
type=int32_t
```

Implement local helpers in `main_window.cpp`:

```cpp
QString encodeVariableOverridePayload(const QString& alias,
                                      const QString& typeName) {
    return QStringLiteral("alias=%1\ntype=%2")
        .arg(alias.left(80), typeName.left(80));
}

GuiVariableOverride decodeVariableOverridePayload(const QString& text) {
    GuiVariableOverride out;
    const auto lines = text.split(QLatin1Char('\n'));
    for (const auto& line : lines) {
        if (line.startsWith(QStringLiteral("alias="))) {
            out.alias = line.mid(6);
            out.hasAlias = !out.alias.isEmpty();
        } else if (line.startsWith(QStringLiteral("type="))) {
            out.typeName = line.mid(5);
            out.hasType = !out.typeName.isEmpty();
        }
    }
    return out;
}
```

- [ ] **Step 5: Implement variable set/read/join**

Implement:

```cpp
bool MainWindow::setVariableOverrideById(quint32 varId,
                                         const QString& alias,
                                         const QString& typeName) {
    if (!m_overrideStore) return false;
    const int row = variableRowById(varId);
    if (row < 0) return false;
    if (alias.trimmed().isEmpty() && typeName.trimmed().isEmpty())
        return false;

    AuraOverrideRecord rec{};
    rec.key = buildKeyForVariable(row);
    rec.payload.kind = AURA_OVERRIDE_PAYLOAD_TYPE;
    const QString payload = encodeVariableOverridePayload(alias.trimmed(),
                                                          typeName.trimmed());
    const QByteArray utf8 = payload.toUtf8();
    std::strncpy(rec.payload.text, utf8.constData(),
                 AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
    rec.status = AURA_OVERRIDE_STATUS_ACTIVE;

    if (aura_override_store_put(m_overrideStore, &rec) != 0)
        return false;
    applyOverridesToVariables();
    return true;
}

GuiVariableOverride MainWindow::variableOverrideById(quint32 varId) const {
    return m_variableOverrides.value(varId);
}

QVector<GuiVariableOverride> MainWindow::variableOverrideList() const {
    QVector<GuiVariableOverride> out;
    out.reserve(m_variableOverrides.size());
    for (auto it = m_variableOverrides.constBegin();
         it != m_variableOverrides.constEnd(); ++it) {
        out.push_back(it.value());
    }
    return out;
}
```

Implement:

```cpp
void MainWindow::applyOverridesToVariables() {
    m_variableOverrides.clear();
    if (!m_overrideStore) return;

    for (int i = 0; i < m_variables.size(); ++i) {
        AuraOverrideKey key = buildKeyForVariable(i);
        AuraOverrideRecord rec{};
        const int rc = aura_override_store_get(m_overrideStore, &key, &rec);
        if (rc != 0 || rec.payload.kind != AURA_OVERRIDE_PAYLOAD_TYPE)
            continue;

        GuiVariableOverride ov =
            decodeVariableOverridePayload(QString::fromUtf8(rec.payload.text));
        ov.varId = m_variables[i].varId;
        ov.functionId = m_variables[i].functionId;
        if (ov.hasAlias || ov.hasType)
            m_variableOverrides.insert(ov.varId, ov);
    }
}
```

- [ ] **Step 6: Call variable join after analysis**

In `MainWindow::runAnalyze()`, after `m_variables` is populated, call:

```cpp
applyOverridesToVariables();
```

- [ ] **Step 7: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 6: Make Variable Candidate Apply Actually Store Overrides

**Files:**

- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Update type propagation dialog apply path**

Find the block that currently says selected candidates only count and report via status bar. Replace the accepted-dialog branch with:

```cpp
int applied = 0;
for (int i = 0; i < list->count(); ++i) {
    auto* it = list->item(i);
    if (!(it->flags() & Qt::ItemIsUserCheckable) ||
        it->checkState() != Qt::Checked) {
        continue;
    }
    const quint32 varId = it->data(Qt::UserRole + 0).toUInt();
    const QString newType = it->data(Qt::UserRole + 2).toString();
    if (setVariableOverrideById(varId, QString(), newType))
        ++applied;
}
statusBar()->showMessage(
    QStringLiteral("Type propagation applied: %1 variable override(s).")
        .arg(applied));
```

- [ ] **Step 2: Update field suggestion apply path**

For selected field candidates, store aliases using the current candidate name:

```cpp
int applied = 0;
for (int i = 0; i < list->count(); ++i) {
    auto* it = list->item(i);
    if (!(it->flags() & Qt::ItemIsUserCheckable) ||
        it->checkState() != Qt::Checked) {
        continue;
    }
    const quint32 varId = it->data(Qt::UserRole).toUInt();
    const QString alias = QStringLiteral("field_%1").arg(varId);
    if (setVariableOverrideById(varId, alias, QString()))
        ++applied;
}
statusBar()->showMessage(
    QStringLiteral("Field suggestions applied: %1 variable override(s).")
        .arg(applied));
```

If a better field name already exists on the item text, parse only the explicit `name=` token; do not infer names from translated UI prose.

- [ ] **Step 3: Add a direct API test instead of modal automation**

Because nested modal automation is brittle, keep GUI smoke focused on the public API:

```cpp
SUBCASE("variable override API stores type-only and alias-only edits") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    if (window.variableList().isEmpty()) {
        MESSAGE("SKIP: fixture produced no variables");
        return;
    }
    const quint32 varId = window.variableList()[0].varId;
    CHECK(window.setVariableOverrideById(
        varId, QString(), QStringLiteral("UserStruct*")));
    CHECK(window.variableOverrideById(varId).typeName
          == QStringLiteral("UserStruct*"));
    CHECK(window.setVariableOverrideById(
        varId, QStringLiteral("renamed_var"), QString()));
    CHECK(window.variableOverrideById(varId).alias
          == QStringLiteral("renamed_var"));
}
```

- [ ] **Step 4: Verify**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 7: Protected Variable Output in GUI RPC and MCP

**Files:**

- Modify: `src/gui/rpc_server.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
- Modify if needed: `src/mcp/mcp_cli_bridge.cpp`

- [ ] **Step 1: Add RPC JSON helper**

In `src/gui/rpc_server.cpp`, add:

```cpp
cJSON* variableOverrideJson(const GuiVariableOverride& ov) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "var_id", ov.varId);
    cJSON_AddNumberToObject(item, "function_id", ov.functionId);
    cJSON_AddBoolToObject(item, "has_alias", ov.hasAlias);
    cJSON_AddBoolToObject(item, "has_type", ov.hasType);
    cJSON_AddStringToObject(
        item, "alias",
        ov.hasAlias ? ov.alias.toUtf8().constData() : "");
    cJSON_AddStringToObject(
        item, "type",
        ov.hasType ? ov.typeName.toUtf8().constData() : "");
    cJSON_AddBoolToObject(item, "protected_only", true);
    return item;
}
```

- [ ] **Step 2: Extend `demo_snapshot`**

Inside `demo_snapshot`, collect:

```cpp
const auto variableOverrides = m_mw->variableOverrideList();
const int variableOverridesIncluded =
    boundedQtCount(variableOverrides.size(), kDemoMaxVariableReferences);
cJSON_AddNumberToObject(counts, "variable_overrides_total",
                        variableOverrides.size());
cJSON_AddNumberToObject(counts, "variable_overrides_included",
                        variableOverridesIncluded);

cJSON* variableOverrideItems =
    cJSON_AddArrayToObject(r, "variable_overrides_sent");
for (int i = 0; i < variableOverridesIncluded; ++i)
    cJSON_AddItemToArray(variableOverrideItems,
                         variableOverrideJson(variableOverrides[i]));
```

- [ ] **Step 3: Add MCP smoke schema assertions**

In `tests/integration/mcp_smoke/mcp_smoke.cpp`, extend demo snapshot assertions:

```cpp
CHECK(out.find("variable_overrides_total") != std::string::npos);
CHECK(out.find("variable_overrides_sent") != std::string::npos);
CHECK(out.find("protected_only") != std::string::npos);
```

- [ ] **Step 4: Verify**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke gui_smoke
ctest --test-dir build-trim-gui -C Release -R "mcp_smoke|gui_smoke" --output-on-failure
```

Expected:

```text
100% tests passed
```

---

## Task 8: Foreground GUI Verification

**Files:**

- No source edits.

- [ ] **Step 1: Build Release targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke cli_smoke mcp_smoke aura-gui
```

Expected:

```text
gui_smoke.exe
cli_smoke.exe
mcp_smoke.exe
aura-gui.exe
```

- [ ] **Step 2: Run tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "gui_smoke|cli_smoke|mcp_smoke" --output-on-failure
```

Expected:

```text
100% tests passed, 0 tests failed out of 3
```

- [ ] **Step 3: Start foreground GUI**

If `aura-gui.exe` is already running from this build tree and blocks linking, stop only that process. Then run:

```powershell
$env:AURA_GUI_RPC_PORT='27654'
$env:AURA_GUI_RPC_TOKEN='aura-demo-token'
Start-Process -FilePath (Resolve-Path 'build-trim-gui\src\gui\Release\aura-gui.exe') -WorkingDirectory (Resolve-Path '.')
Start-Sleep -Seconds 2
Get-Process aura-gui -ErrorAction SilentlyContinue |
  Select-Object Id,ProcessName,Path,MainWindowTitle
```

Expected:

```text
ProcessName: aura-gui
MainWindowTitle: AURA
```

- [ ] **Step 4: Exercise GUI through GUI RPC**

Run:

```powershell
$db=(Resolve-Path '.scratch').Path + '\comments-vars-live-check.aura.db'
$bin=(Resolve-Path 'tests\fixtures\bin\pe_smoke.x86_64.exe').Path
build-trim-gui\src\cli\Release\aura.exe gui --port 27654 --token aura-demo-token open-project $db
build-trim-gui\src\cli\Release\aura.exe gui --port 27654 --token aura-demo-token add-binary $bin
build-trim-gui\src\cli\Release\aura.exe gui --port 27654 --token aura-demo-token analyze --row 0 --level full
build-trim-gui\src\cli\Release\aura.exe gui --port 27654 --token aura-demo-token demo-snapshot
```

Expected:

- `open-project` ok.
- `add-binary` ok.
- `analyze` ok with `function_count > 0`.
- `demo-snapshot` includes `comments_total`, `variable_overrides_total`, and protected omission fields.

- [ ] **Step 5: MCP live check**

Run:

```powershell
$inputPath = Join-Path (Resolve-Path '.scratch') 'mcp-comments-vars-live.jsonl'
@'
{"jsonrpc":"2.0","id":1,"method":"tools/list","params":{}}
{"jsonrpc":"2.0","id":2,"method":"tools/call","params":{"name":"aura_gui_demo_snapshot","arguments":{"gui_port":27654,"gui_token":"aura-demo-token"}}}
'@ | Set-Content -Path $inputPath -Encoding ascii
Get-Content $inputPath | build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- `tools/list` includes `aura_gui_demo_snapshot`.
- `tools/call` returns `status:"ok"`.
- Returned JSON contains `comments_sent`, `variable_overrides_sent`, and protected omission flags.

---

## Self-Review

### Spec Coverage

- GUI comment persistence: Task 1.
- GUI comment rendering: Task 2.
- Modal comment path uses same implementation: Task 3.
- Comment CLI/MCP protected output: Task 4.
- Variable override persistence: Task 5.
- Variable candidate apply changes real state: Task 6.
- Variable CLI/MCP protected output: Task 7.
- Foreground GUI proof: Task 8.

### Placeholder Scan

No task uses `TBD`, `TODO`, or “write tests” without concrete test bodies. Fixture-dependent variable tests include explicit skip behavior because existing fixtures may produce zero variables depending on engine output.

### Type Consistency

The plan uses existing core `aura_override_key_from_variable_record()` and adds only a GUI wrapper `MainWindow::buildKeyForVariable()`. Function comments use the existing override store payload kind `AURA_OVERRIDE_PAYLOAD_ANNOTATION`; variable alias/type uses `AURA_OVERRIDE_PAYLOAD_TYPE` with a compact text payload.
