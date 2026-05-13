# Demo Snapshot Minimal MCP Output Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a read-only `demo-snapshot` surface that shows only third-party-safe AURA GUI/MCP data: which functions, protected strings, reference edges, and variable-like reference hints are being sent, with explicit masking status.

**Architecture:** Keep existing detailed GUI RPC, CLI, and MCP tools unchanged for development automation. Add a new GUI RPC method (`demo_snapshot`) that builds a bounded summary from the current foreground GUI state, expose it through `aura gui demo-snapshot` and MCP `aura_gui_demo_snapshot`, then update the foreground demo console to display this compact snapshot instead of dumping every detailed JSON response.

**Tech Stack:** C++17, Qt GUI RPC server, CLI11, cJSON, AURA MCP bridge, doctest smoke tests, PowerShell demo script.

---

## Autoplan Review

**CEO check:** The feature should solve the actual demo problem, not make all MCP output smaller. Decision: add a new purpose-built read-only snapshot and leave detailed tools intact.

**Design check:** The third-party viewer needs a clear story: "these are the functions sent, these are the strings sent, strings are protected/masked, these are references." Decision: use compact top-level sections and counters instead of raw nested engine data.

**Engineering check:** The lowest-risk source of truth is the running GUI state because this project treats GUI as the primary frontend. Decision: implement `demo_snapshot` in `src/gui/rpc_server.cpp`, then route CLI/MCP through it.

**DX check:** The demo script should stop printing noisy raw JSON by default. Decision: add a "DEMO SNAPSHOT" section and keep detailed captures either omitted or clearly secondary.

**Rejected alternatives:**
- Shrinking `aura_gui_functions`, `aura_gui_xrefs`, or `aura_gui_disasm_function`: rejected because existing automation/debug consumers need detail.
- PowerShell-only summarization: rejected because it does not create a product feature and can drift from MCP behavior.

## Output Contract

`aura gui demo-snapshot` returns the normal CLI GUI RPC envelope:

```json
{
  "aura_schema": 1,
  "command": "gui demo-snapshot",
  "rpc": {
    "ok": true,
    "result": {
      "snapshot_schema": 1,
      "disclosure": "demo_minimal",
      "protected_only": true,
      "counts": {
        "functions_total": 72,
        "functions_included": 3,
        "strings_total": 48,
        "strings_included": 5,
        "references_total": 12,
        "references_included": 5
      },
      "functions_sent": [
        { "row": 0, "addr": 4198400, "name": "main" }
      ],
      "strings_sent": [
        {
          "string_id": 7,
          "addr": 4210688,
          "length": 16,
          "encoding": "ascii",
          "protected_value": "<MASK:SECRET>",
          "masked": true,
          "has_protection": true,
          "findings_count": 1
        }
      ],
      "references_sent": [
        { "from": 4198450, "to": 4210688, "kind": "data", "target_kind": "string" }
      ],
      "variable_references_sent": [
        { "var_id": 1, "function_id": 4, "name": "local_10h", "kind": "stack", "stack_offset": -16, "op_str_omitted": true }
      ],
      "omissions": {
        "raw_string_content_omitted": true,
        "disassembly_text_omitted": true,
        "op_str_omitted": true
      }
    }
  }
}
```

MCP `aura_gui_demo_snapshot` wraps the same CLI JSON in the existing protected MCP envelope. It must not require mutation confirmation because it is read-only.

## File Structure

- Modify `src/gui/rpc_server.cpp`: add `demo_snapshot` helper builders and method branch.
- Modify `src/gui/main_window.h`: expose read-only GUI variable records for bounded demo summaries.
- Modify `src/cli/main.cpp`: add `aura gui demo-snapshot`; add `mcp-json call aura_gui_demo_snapshot` support without binary/function args.
- Modify `src/mcp/mcp_tools.cpp`: register `aura_gui_demo_snapshot` with GUI auth fields.
- Modify `src/mcp/mcp_cli_bridge.cpp`: route `aura_gui_demo_snapshot` to `aura gui demo-snapshot`; optionally normalize/verify protected-only fields.
- Modify `tests/integration/cli_smoke/cli_smoke.cpp`: assert CLI help advertises `demo-snapshot`; assert `mcp-json` can emit a call for the new tool.
- Modify `tests/integration/mcp_smoke/mcp_smoke.cpp`: assert tool list includes `aura_gui_demo_snapshot`; assert env auth/unreachable path routes through the bridge.
- Modify `.scratch/aura_gui_mcp_demo_console.ps1`: display a compact `DEMO SNAPSHOT` section and use MCP `aura_gui_demo_snapshot` in the JSON-RPC capture.

## Task 1: GUI RPC Demo Snapshot

**Files:**
- Modify: `src/gui/rpc_server.cpp`
- Modify: `src/gui/main_window.h`

- [ ] **Step 1: Add bounded helper constants near existing anonymous namespace helpers**

Add constants near `stringRecordJson`:

```cpp
constexpr int kDemoMaxFunctions = 3;
constexpr int kDemoMaxStrings = 5;
constexpr int kDemoMaxReferences = 5;
```

- [ ] **Step 2: Add helper builders in `src/gui/rpc_server.cpp`**

Add helpers in the anonymous namespace after `stringRecordJson`:

```cpp
QString hexAddr(quint64 value) {
    return QStringLiteral("0x%1").arg(value, 0, 16);
}

cJSON* demoFunctionJson(int row, const QString& name) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "row", row);
    cJSON_AddStringToObject(item, "name", name.toUtf8().constData());
    return item;
}

cJSON* demoStringJson(const GuiStringRecord& s) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "string_id", static_cast<double>(s.stringId));
    cJSON_AddNumberToObject(item, "addr", static_cast<double>(s.addr));
    cJSON_AddStringToObject(item, "addr_hex", hexAddr(s.addr).toUtf8().constData());
    cJSON_AddNumberToObject(item, "length", static_cast<double>(s.length));
    cJSON_AddStringToObject(item, "encoding", s.encoding.toUtf8().constData());
    cJSON_AddStringToObject(item, "protected_value", s.exportValue.toUtf8().constData());
    const bool masked = !s.maskedContent.isEmpty() && s.maskedContent != s.content;
    cJSON_AddBoolToObject(item, "masked", masked);
    cJSON_AddBoolToObject(item, "has_protection", s.hasProtection);
    cJSON_AddNumberToObject(item, "findings_count", s.findings.size());
    cJSON_AddBoolToObject(item, "raw_content_omitted", true);
    return item;
}

cJSON* demoXrefJson(const GuiXrefRecord& x, const QSet<quint64>& stringAddrs) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "from", static_cast<double>(x.from));
    cJSON_AddStringToObject(item, "from_hex", hexAddr(x.from).toUtf8().constData());
    cJSON_AddNumberToObject(item, "to", static_cast<double>(x.to));
    cJSON_AddStringToObject(item, "to_hex", hexAddr(x.to).toUtf8().constData());
    cJSON_AddStringToObject(item, "kind", x.kind.toUtf8().constData());
    cJSON_AddStringToObject(item, "target_kind",
                            stringAddrs.contains(x.to) ? "string" : "address");
    return item;
}
```

If `QSet` is not already included by this file, include `<QSet>`.

- [ ] **Step 3: Add `demo_snapshot` RPC branch**

Add an `else if` branch before `quit`:

```cpp
} else if (std::strcmp(method, "demo_snapshot") == 0) {
    const auto strings = m_mw->stringList();
    const auto xrefs = m_mw->xrefList();

    cJSON* r = cJSON_CreateObject();
    cJSON_AddNumberToObject(r, "snapshot_schema", 1);
    cJSON_AddStringToObject(r, "disclosure", "demo_minimal");
    cJSON_AddBoolToObject(r, "protected_only", true);

    cJSON* counts = cJSON_AddObjectToObject(r, "counts");
    cJSON_AddNumberToObject(counts, "functions_total", m_mw->functionCount());
    cJSON_AddNumberToObject(counts, "functions_included",
                            std::min(m_mw->functionCount(), kDemoMaxFunctions));
    cJSON_AddNumberToObject(counts, "strings_total", strings.size());
    cJSON_AddNumberToObject(counts, "strings_included",
                            std::min(strings.size(), kDemoMaxStrings));
    cJSON_AddNumberToObject(counts, "references_total", xrefs.size());
    cJSON_AddNumberToObject(counts, "references_included",
                            std::min(xrefs.size(), kDemoMaxReferences));

    cJSON* functions = cJSON_AddArrayToObject(r, "functions_sent");
    for (int i = 0; i < std::min(m_mw->functionCount(), kDemoMaxFunctions); ++i) {
        cJSON_AddItemToArray(functions,
                             demoFunctionJson(i, m_mw->functionDisplayNameAt(i)));
    }

    QSet<quint64> stringAddrs;
    cJSON* stringItems = cJSON_AddArrayToObject(r, "strings_sent");
    for (int i = 0; i < strings.size(); ++i) {
        stringAddrs.insert(strings[i].addr);
        if (i < kDemoMaxStrings) {
            cJSON_AddItemToArray(stringItems, demoStringJson(strings[i]));
        }
    }

    cJSON* refs = cJSON_AddArrayToObject(r, "references_sent");
    for (int i = 0; i < std::min(xrefs.size(), kDemoMaxReferences); ++i) {
        cJSON_AddItemToArray(refs, demoXrefJson(xrefs[i], stringAddrs));
    }

    cJSON* varRefs = cJSON_AddArrayToObject(r, "variable_references_sent");
    const auto variables = m_mw->variableList();
    for (int i = 0; i < std::min(variables.size(), 5); ++i) {
        cJSON* item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "var_id", variables[i].varId);
        cJSON_AddNumberToObject(item, "function_id", variables[i].functionId);
        cJSON_AddStringToObject(item, "name",
                                variables[i].name.isEmpty()
                                    ? "<unnamed>"
                                    : variables[i].name.toUtf8().constData());
        cJSON_AddStringToObject(item, "kind",
                                variables[i].kind.toUtf8().constData());
        cJSON_AddNumberToObject(item, "stack_offset",
                                variables[i].stackOffset);
        cJSON_AddBoolToObject(item, "op_str_omitted", true);
        cJSON_AddItemToArray(varRefs, item);
    }

    cJSON* omissions = cJSON_AddObjectToObject(r, "omissions");
    cJSON_AddBoolToObject(omissions, "raw_string_content_omitted", true);
    cJSON_AddBoolToObject(omissions, "disassembly_text_omitted", true);
    cJSON_AddBoolToObject(omissions, "op_str_omitted", true);

    out = resultJson(true, r, nullptr);
```

This implementation intentionally does not expose raw instruction text, raw string content, or op_str.

- [ ] **Step 4: Add read-only variable accessor**

In `src/gui/main_window.h`, add this accessor next to `stringList()`:

```cpp
QVector<GuiVariableRecord> variableList() const { return m_variables; }
```

## Task 2: CLI and MCP Tool Routing

**Files:**
- Modify: `src/cli/main.cpp`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `src/mcp/mcp_cli_bridge.cpp`

- [ ] **Step 1: Add CLI subcommand**

In the `gui` command setup in `src/cli/main.cpp`, add:

```cpp
auto *cmd_gui_demo_snapshot = cmd_gui->add_subcommand(
    "demo-snapshot",
    "show third-party-safe minimal GUI/MCP demo snapshot");
```

In the `if (cmd_gui->parsed())` dispatch block before `quit`, add:

```cpp
if (cmd_gui_demo_snapshot->parsed()) {
    return run_gui_rpc("demo_snapshot", params_object(), gui_rpc, g,
                       "gui demo-snapshot");
}
```

- [ ] **Step 2: Register MCP tool**

In `src/mcp/mcp_tools.cpp`, add a `ToolSpec` entry:

```cpp
{"aura_gui_demo_snapshot",
 "Return a third-party-safe minimal snapshot of the foreground AURA GUI.",
 kGuiAuthFields, 2},
```

Because it starts with `aura_gui_`, existing GUI auth validation applies. Do not add it to mutation checks.

- [ ] **Step 3: Route MCP tool to CLI**

In `src/mcp/mcp_cli_bridge.cpp`, update GUI tool CLI argument routing:

```cpp
} else if (streq(name, "aura_gui_demo_snapshot")) {
    args.push_back(literalArg("demo-snapshot"));
```

No extra arguments are required beyond the existing `--port` and environment-scoped token handling.

## Task 3: CLI and MCP Smoke Tests

**Files:**
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: CLI help test**

Update the GUI help test to require the new command:

```cpp
CHECK(r.stdout_.find("demo-snapshot") != std::string::npos);
```

- [ ] **Step 2: MCP JSON request generator test**

Add a test near the existing `mcp-json call` tests:

```cpp
TEST_CASE("cli_smoke: mcp-json call emits GUI demo snapshot request") {
    CmdResult r = run("\"" + aura_binary() +
                      "\" --compact mcp-json call aura_gui_demo_snapshot");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_);

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "method") == "tools/call");
    cJSON *params = cJSON_GetObjectItem(root, "params");
    REQUIRE(params != nullptr);
    CHECK(get_string(params, "name") == "aura_gui_demo_snapshot");
    cJSON_Delete(root);
}
```

This test verifies request generation only. Auth validation belongs to MCP smoke because the CLI generator does not know the GUI token.

- [ ] **Step 3: MCP tool-list test**

In `mcp_smoke.cpp`, extend the GUI tool-list assertions:

```cpp
CHECK(toolsArrayHasName(tools, "aura_gui_demo_snapshot"));
```

- [ ] **Step 4: MCP env auth/unreachable test**

Add or extend an unreachable-GUI test for `aura_gui_demo_snapshot`:

```cpp
input << "{\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"tools/call\","
         "\"params\":{\"name\":\"aura_gui_demo_snapshot\","
         "\"arguments\":{\"gui_port\":\"65534\","
         "\"gui_token\":\"demo-token\"}}}\n";
```

Assert:

```cpp
CHECK(out.find("aura_gui_demo_snapshot") != std::string::npos);
CHECK(out.find("gui_rpc_connect_failed") != std::string::npos);
```

## Task 4: Foreground Demo Console Uses Snapshot

**Files:**
- Modify: `.scratch/aura_gui_mcp_demo_console.ps1`

- [ ] **Step 1: Add a human-readable snapshot printer**

Add a PowerShell helper that parses the CLI JSON and prints only the snapshot summary:

```powershell
function Write-DemoSnapshotSummary {
    param(
        [System.Collections.Generic.List[string]]$Out,
        [AllowNull()][string]$SnapshotJson
    )

    if ([string]::IsNullOrWhiteSpace($SnapshotJson)) {
        Add-LogLine -Out $Out -Text "No demo snapshot JSON captured."
        return
    }

    try {
        $parsed = $SnapshotJson | ConvertFrom-Json
        $snap = $parsed.rpc.result
        Add-LogLine -Out $Out -Text "disclosure=$($snap.disclosure) protected_only=$($snap.protected_only)"
        Add-LogLine -Out $Out -Text "counts functions=$($snap.counts.functions_included)/$($snap.counts.functions_total) strings=$($snap.counts.strings_included)/$($snap.counts.strings_total) refs=$($snap.counts.references_included)/$($snap.counts.references_total)"
        foreach ($fn in @($snap.functions_sent)) {
            Add-LogLine -Out $Out -Text "function row=$($fn.row) name=$($fn.name)"
        }
        foreach ($s in @($snap.strings_sent)) {
            Add-LogLine -Out $Out -Text "string addr=$($s.addr_hex) masked=$($s.masked) protected=$($s.has_protection) value=$($s.protected_value)"
        }
        foreach ($r in @($snap.references_sent)) {
            Add-LogLine -Out $Out -Text "reference from=$($r.from_hex) to=$($r.to_hex) kind=$($r.kind) target=$($r.target_kind)"
        }
        foreach ($v in @($snap.variable_references_sent)) {
            Add-LogLine -Out $Out -Text "variable-reference var_id=$($v.var_id) function_id=$($v.function_id) name=$($v.name) kind=$($v.kind) stack_offset=$($v.stack_offset) op_str_omitted=$($v.op_str_omitted)"
        }
    } catch {
        Add-LogLine -Out $Out -Text "Could not parse demo snapshot: $($_.Exception.Message)"
    }
}
```

- [ ] **Step 2: Call CLI demo snapshot in foreground capture**

In `Invoke-Capture`, after analyze and before detailed commands, add:

```powershell
Write-Section -Out $out -Text "DEMO SNAPSHOT"
$snapshotJson = Invoke-LoggedAuraGui -Out $out -GuiArgs @("demo-snapshot")
Write-DemoSnapshotSummary -Out $out -SnapshotJson $snapshotJson
```

Keep detailed calls only if they are needed to choose a function address, but the visible demo should emphasize the summary section.

- [ ] **Step 3: Add MCP demo snapshot JSON-RPC call**

In `Invoke-McpJsonRpcCapture`, add:

```powershell
$lines.Add((New-McpCallLine -Id 6 -Name "aura_gui_demo_snapshot" -Arguments $baseArgs))
```

Then renumber later IDs or allow unique IDs with no duplicates.

## Task 5: Build, Test, and Foreground Verification

**Files:**
- No source files expected beyond previous tasks.

- [ ] **Step 1: Build targeted smoke tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke gui_smoke
```

Expected: all three targets build successfully.

- [ ] **Step 2: Run smoke tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected: `100% tests passed`.

- [ ] **Step 3: Validate CLI help**

Run:

```powershell
build-trim-gui\src\cli\Release\aura.exe gui --help
```

Expected: output contains `demo-snapshot`.

- [ ] **Step 4: Validate foreground GUI snapshot manually**

With foreground `aura-gui` running and `AURA_GUI_RPC_PORT` / `AURA_GUI_RPC_TOKEN` set, run:

```powershell
build-trim-gui\src\cli\Release\aura.exe --compact gui demo-snapshot
```

Expected JSON contains:
- `snapshot_schema: 1`
- `disclosure: "demo_minimal"`
- `protected_only: true`
- `functions_sent`
- `strings_sent`
- `references_sent`
- `omissions.raw_string_content_omitted: true`

- [ ] **Step 5: Validate MCP snapshot manually**

Pipe JSON-RPC into MCP:

```powershell
@'
{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"aura-demo","version":"1"}}}
{"jsonrpc":"2.0","method":"notifications/initialized","params":{}}
{"jsonrpc":"2.0","id":2,"method":"tools/call","params":{"name":"aura_gui_demo_snapshot","arguments":{}}}
'@ | build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected: MCP response includes `aura_gui_demo_snapshot` and the protected CLI JSON; no raw token is printed.

## Task 6: Main Handoff Preparation

**Files:**
- No new files unless release notes are requested.

- [ ] **Step 1: Inspect final diff**

Run:

```powershell
git status --short
git diff -- src/cli/main.cpp src/gui/rpc_server.cpp src/mcp/mcp_cli_bridge.cpp src/mcp/mcp_tools.cpp tests/integration/cli_smoke/cli_smoke.cpp tests/integration/mcp_smoke/mcp_smoke.cpp .scratch/aura_gui_mcp_demo_console.ps1
```

Expected: only planned files changed for this feature, plus existing prior uncommitted work remains visible.

- [ ] **Step 2: Prepare staged set separately from unrelated scratch artifacts**

Stage only source, tests, and the plan/script files that belong to this work. Do not stage unrelated `.scratch` captures or copied DBs.

- [ ] **Step 3: Before merging to `main`, run finishing branch workflow**

Use `superpowers:finishing-a-development-branch` or the project ship workflow after tests pass. Do not merge directly into `main` until the final diff has been reviewed.

## Self-Review

**Spec coverage:** The plan covers the user-approved 1번 approach, CLI and GUI together, MCP exposure, third-party-safe output, foreground demo script, and verification.

**Placeholder scan:** No task depends on undefined future work. `variable_references_sent` is bounded to real GUI variable records and explicitly marks `op_str` as omitted.

**Type consistency:** CLI command is `demo-snapshot`; GUI RPC method is `demo_snapshot`; MCP tool is `aura_gui_demo_snapshot`. All three names are intentionally distinct by layer and consistently mapped.
