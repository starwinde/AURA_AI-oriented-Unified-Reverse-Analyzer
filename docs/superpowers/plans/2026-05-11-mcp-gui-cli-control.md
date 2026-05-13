# MCP GUI+CLI Control Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** MCP가 CLI 분석만 호출하는 수준을 넘어, 실행 중인 AURA GUI를 기준으로 상태 조회, 바이너리 등록, 분석 실행, 안전한 결과 조회를 실제로 수행할 수 있게 한다.

**Architecture:** 기존 `aura-mcp` stdio 서버는 계속 MCP entrypoint로 유지한다. 새 MCP GUI tool들은 `aura` CLI의 기존 `gui ...` RPC client 경로를 호출하고, CLI는 실행 중인 `aura-gui`의 localhost JSON-line RPC 서버와 통신한다. GUI는 사용자가 보는 foreground 창으로 유지되고, MCP/CLI는 GUI 상태를 조회하거나 조작하되 외부로 나가는 응답은 protected envelope로 감싼다.

**Tech Stack:** C++17, CLI11, cJSON, Qt GUI RPC (`src/gui/rpc_server.cpp`), existing `aura-mcp` stdio transport, doctest/CMake smoke tests, Windows/MSVC Release build.

---

## Problem

현재 구현은 MCP 기능이 CLI 분석 경로에만 반영되어 있다.

```text
Codex/LLM -> aura-mcp -> aura CLI analyze/info/disasm/cfg -> JSON
```

GUI에는 별도 RPC 서버가 이미 있지만, MCP tool 목록에는 GUI 조작/조회 tool이 없다. 따라서 사용자가 원하는 “모든 것은 GUI 기준, foreground GUI가 실제로 열려 있고 MCP가 그 GUI 상태를 조작/조회한다”는 시연 목표를 충족하지 못한다.

목표 구조:

```text
Codex/LLM
  -> aura-mcp
  -> aura CLI gui ...
  -> running foreground aura-gui RPC server
  -> GUI state/action/result
  -> protected MCP envelope
```

## Current Source Anchors

- `src/gui/rpc_server.cpp`
  - Existing methods:
    - `status`
    - `open_project`
    - `add_binary`
    - `analyze`
    - `decompile`
    - `jump_string_reference`
    - `rename`
    - `reset_name`
    - `function_list`
    - `list_symbols`
    - `disasm_function`
    - `cfg_function`
    - `list_strings`
    - `list_protected_strings`
    - `list_xrefs`
    - `quit`
  - Security: localhost only, token required, single client.
- `src/cli/main.cpp`
  - Existing GUI RPC client entrypoint: `aura gui --port ... --token ... <subcommand>`
  - Existing exposed CLI subcommands:
    - `status`
    - `open-project`
    - `add-binary`
    - `analyze`
    - `functions`
    - `decompile`
    - `jump-string`
    - `strings`
    - `protected-strings`
    - `symbols`
    - `xrefs`
    - `quit`
  - Missing CLI wrappers for existing GUI RPC methods:
    - `disasm_function`
    - `cfg_function`
    - `rename`
    - `reset_name`
- `src/mcp/mcp_tools.cpp`
  - Existing MCP tools are CLI-analysis oriented only.
  - No `aura_gui_*` tools exist.
- `src/mcp/mcp_cli_bridge.cpp`
  - Existing protected subprocess bridge for `aura` CLI calls.
  - This is the right place to add GUI CLI calls if we keep one bridge.
- `tests/integration/gui_smoke/gui_smoke.cpp`
  - Has GUI public API coverage and string protection checks.
- `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Has stdio MCP tests and CLI bridge tests.

## Scope

Included:

- CLI parity for missing GUI RPC actions:
  - `aura gui disasm-function --addr <hex>`
  - `aura gui cfg-function --addr <hex>`
  - `aura gui rename --row <n> --name <new_name>`
  - `aura gui reset-name --row <n>`
- MCP GUI tools:
  - `aura_gui_status`
  - `aura_gui_add_binary`
  - `aura_gui_analyze`
  - `aura_gui_functions`
  - `aura_gui_protected_strings`
  - `aura_gui_symbols`
  - `aura_gui_xrefs`
  - `aura_gui_disasm_function`
  - `aura_gui_cfg_function`
  - second-slice mutation tools gated by explicit flag:
    - `aura_gui_rename`
    - `aura_gui_reset_name`
- Foreground GUI demo workflow:
  - Start `aura-gui` visibly with `AURA_GUI_RPC_PORT` and `AURA_GUI_RPC_TOKEN`.
  - Use MCP tools to add binary, analyze, and query GUI state.
  - Keep GUI window open after every operation.
- Protected output:
  - MCP must expose `protected_strings`, not raw `strings`, by default.
  - Disassembly/CFG GUI MCP output must be bounded and protected.
  - Raw text-heavy decompile should not be exposed in MCP by default.

Excluded:

- Remote GUI control over non-localhost.
- Mouse/keyboard click automation through MCP.
- Exposing raw decompile/disassembly text to LLM by default.
- Starting hidden GUI instances for MCP.
- Making MCP mutate GUI state unless the tool name is explicit and the request includes a confirmation flag.

## Design Decisions

- **GUI is the source of truth for GUI MCP tools.** `aura_gui_*` tools must talk to a running GUI RPC server, not silently fall back to fresh CLI analysis.
- **CLI and MCP are developed together.** Every MCP GUI tool must have a CLI command or reuse an existing `aura gui ...` command.
- **MCP does not own GUI lifecycle initially.** The demo starts GUI explicitly in foreground. MCP connects to the user-visible GUI.
- **Token is explicit.** GUI MCP tools require `gui_port` and `gui_token` arguments or environment variables `AURA_GUI_RPC_PORT`, `AURA_GUI_RPC_TOKEN`.
- **Read-only first.** Status/query tools are implemented before mutation tools.

## Autoplan Review Revisions

This section records the automatic review decisions that must shape implementation.

- **Product/UX:** The demo must prove a user-visible GUI workflow, not merely “MCP can call a CLI.” The first visible artifact in the demo is the foreground `aura-gui` window; CLI/MCP logs are supporting evidence.
- **Architecture:** Do not let `aura-mcp` start hidden GUI instances. GUI lifecycle remains explicit: a visible GUI process starts with a known RPC port/token, then MCP attaches to it.
- **Safety:** Mutation tools are not part of the first implementation slice unless read-only/status/analyze flows are already passing. If implemented, mutation tools require both an explicit mutation tool name and `confirm_mutation:true`.
- **Security:** `gui_token` must never be echoed into MCP response envelopes or capture logs. It can be passed to the CLI subprocess, but it must be redacted from logged commands.
- **DX:** All manual commands must be copy-pasteable for PowerShell on this Windows repo path with spaces and Korean characters. Prefer quoted absolute executable paths and repo-relative binary fixture paths.
- **Testing:** Tests must distinguish three layers:
  - CLI can form/send GUI RPC commands.
  - MCP lists and validates GUI tools.
  - A foreground/manual demo proves end-to-end GUI attachment.
- **Scope Control:** The first executable slice should be read-only + analyze:
  - `aura_gui_status`
  - `aura_gui_add_binary`
  - `aura_gui_analyze`
  - `aura_gui_functions`
  - `aura_gui_protected_strings`
  Mutation tools can be a second slice after this passes.

## NOT in Scope

- MCP mouse/keyboard automation.
- MCP-owned hidden GUI launch.
- Remote GUI control beyond `127.0.0.1`.
- Raw decompile export through MCP.
- Raw string content export through MCP.
- Making GUI RPC token optional for MCP tools.
- Replacing existing CLI analysis MCP tools.

## What Already Exists

- `src/gui/rpc_server.cpp` already exposes localhost JSON-line GUI RPC with token authentication.
- `src/cli/main.cpp` already has `aura gui --port --token ...` for several GUI actions.
- `src/mcp/mcp_tools.cpp` already lists static-analysis MCP tools and dispatches to CLI bridge.
- `src/mcp/mcp_cli_bridge.cpp` already has subprocess execution and protected envelope handling.
- `tests/integration/gui_smoke/gui_smoke.cpp` already validates many GUI public APIs.
- `tests/integration/mcp_smoke/mcp_smoke.cpp` already validates MCP stdio, protected envelopes, and raw-denied behavior.

## Reviewed Architecture Diagram

```text
visible user desktop
    |
    v
foreground aura-gui.exe
    |
    | localhost JSON-line RPC, token required
    v
src/gui/rpc_server.cpp
    ^
    |
aura.exe gui --port P --token T ...
    ^
    |
aura-mcp.exe stdio server
    ^
    |
Codex/LLM MCP tool call
```

The key invariant is that `aura-mcp` never fabricates GUI state. GUI MCP tools succeed only when the visible GUI RPC server is reachable and authenticated.

## Failure Modes Registry

| Failure | User-visible symptom | Detection | Required response |
|---|---|---|---|
| GUI not running | `aura_gui_status` fails | CLI bridge returns GUI RPC connect failure | Return protected MCP error `gui_unreachable`; do not fallback to static CLI analyze |
| Wrong token | MCP GUI tool fails | GUI RPC returns `invalid token` | Return protected MCP error; redact token in logs |
| Wrong port | MCP GUI tool fails | connection refused/time out | Return problem/cause/fix message with expected port env |
| Hidden GUI accidentally started | Demo seems to work but no user-visible GUI | process/window inspection | Treat as failed demo; foreground GUI is required |
| Raw string leak | `aura_gui_protected_strings` includes `content` | MCP smoke key scan | Fail test and block shipping |
| Raw disasm leak | GUI MCP disasm includes `text`/`op_str` unbounded | MCP smoke key scan | Strip or mark omitted before MCP envelope |
| Mutation without confirmation | Rename/reset occurs unexpectedly | Missing `confirm_mutation:true` validation | Fail closed before CLI call |
| Token appears in logs | Capture log contains token | grep capture/log output | Redact command logging before final demo |

## Test Diagram

| Flow | Code path | Test |
|---|---|---|
| CLI disasm-function wrapper | `src/cli/main.cpp` -> `run_gui_rpc("disasm_function")` | `cli_smoke` argument/shape test |
| CLI cfg-function wrapper | `src/cli/main.cpp` -> `run_gui_rpc("cfg_function")` | `cli_smoke` argument/shape test |
| MCP lists GUI tools | `mcp_tools.cpp` `tools/list` | `mcp_smoke` direct tools array assertion |
| MCP validates GUI args | `mcp_tools.cpp` / bridge validation | `mcp_smoke` missing token/port/function tests |
| MCP status reaches GUI | `aura-mcp` -> `aura gui status` -> GUI RPC | manual foreground verification plus `mcp_smoke` unreachable-GUI test |
| MCP add/analyze reaches GUI | `aura_gui_add_binary`, `aura_gui_analyze` | manual foreground verification + GUI state count check |
| Protected strings remain protected | `aura_gui_protected_strings` | `mcp_smoke` no `content` key check |
| GUI remains foreground | demo harness | manual verification, process/window title check |

## Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|---|---|---|---|---|---|
| 1 | Product | Foreground GUI is mandatory for demo | Auto-decided | User requirement | User explicitly said all demonstrations are GUI-first and foreground-visible | Hidden/background-only MCP demo |
| 2 | Architecture | MCP attaches to existing visible GUI instead of launching hidden GUI | Auto-decided | Simpler trust boundary | Existing GUI RPC already provides localhost/token boundary | MCP-owned GUI lifecycle |
| 3 | Safety | Read-only/analyze GUI MCP slice ships before mutation tools | Auto-decided | Reduce blast radius | Status/add/analyze/query proves the missing bridge without rename risk | Implement all mutation tools in first slice |
| 4 | Security | GUI token must be redacted from logs/envelopes | Auto-decided | Secret hygiene | MCP/demo logs are visible and may be shared | Echoing full CLI command with token |

## Task 1: CLI GUI-RPC Parity

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] Add `aura gui disasm-function --addr <hex>`.
  - CLI method: `run_gui_rpc("disasm_function", {"addr": number})`
  - Validate `--addr` with `std::stoull(..., 0)`.
  - Output shape remains:
    ```json
    {"aura_schema":1,"command":"gui disasm-function","rpc":{"ok":true,"result":{"function_addr":4198779,"instructions":[...]}}}
    ```

- [ ] Add `aura gui cfg-function --addr <hex>`.
  - CLI method: `run_gui_rpc("cfg_function", {"addr": number})`
  - Output includes `blocks` and `edges`.

- [ ] Add `aura gui rename --row <n> --name <new_name>`.
  - CLI method: `run_gui_rpc("rename", {"function_row":n,"new_name":name})`
  - This is mutation, so CLI name must be explicit.

- [ ] Add `aura gui reset-name --row <n>`.
  - CLI method: `run_gui_rpc("reset_name", {"function_row":n})`

- [ ] Keep existing CLI commands unchanged:
  - `status`, `open-project`, `add-binary`, `analyze`, `functions`, `decompile`, `jump-string`, `strings`, `protected-strings`, `symbols`, `xrefs`, `quit`.

### Task 1A: CLI command declarations

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] **Step 1: Add failing help smoke test**

Add this test near the GUI CLI tests in `tests/integration/cli_smoke/cli_smoke.cpp`:

```cpp
TEST_CASE("cli_smoke: gui help advertises function detail and rename RPC commands") {
    CmdResult r = run("\"" + aura_binary() + "\" gui --help");
    REQUIRE(r.exit_code == 0);
    CHECK(r.stdout_.find("disasm-function") != std::string::npos);
    CHECK(r.stdout_.find("cfg-function") != std::string::npos);
    CHECK(r.stdout_.find("rename") != std::string::npos);
    CHECK(r.stdout_.find("reset-name") != std::string::npos);
}
```

- [ ] **Step 2: Run failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected before implementation: help output does not contain at least one of the new commands.

- [ ] **Step 3: Declare missing GUI subcommands**

In `src/cli/main.cpp`, after the existing `cmd_gui_decompile` / `cmd_gui_jump_string` / list commands are declared, add:

```cpp
auto *cmd_gui_disasm_function = cmd_gui->add_subcommand(
    "disasm-function", "fetch GUI disassembly for a function address");
std::string gui_disasm_addr;
cmd_gui_disasm_function->add_option("--addr", gui_disasm_addr,
                                    "function address, e.g. 0x40117b")
    ->required();

auto *cmd_gui_cfg_function = cmd_gui->add_subcommand(
    "cfg-function", "fetch GUI CFG for a function address");
std::string gui_cfg_addr;
cmd_gui_cfg_function->add_option("--addr", gui_cfg_addr,
                                 "function address, e.g. 0x40117b")
    ->required();

auto *cmd_gui_rename = cmd_gui->add_subcommand(
    "rename", "rename a GUI function row");
int gui_rename_row = 0;
std::string gui_rename_name;
cmd_gui_rename->add_option("--row", gui_rename_row,
                           "function row to rename")
    ->required();
cmd_gui_rename->add_option("--name", gui_rename_name,
                           "new function display name")
    ->required();

auto *cmd_gui_reset_name = cmd_gui->add_subcommand(
    "reset-name", "reset a GUI function row name");
int gui_reset_name_row = 0;
cmd_gui_reset_name->add_option("--row", gui_reset_name_row,
                               "function row to reset")
    ->required();
```

- [ ] **Step 4: Re-run CLI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: help test passes.

### Task 1B: CLI GUI-RPC dispatch

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] **Step 1: Add invalid address tests**

Add:

```cpp
TEST_CASE("cli_smoke: gui disasm-function rejects invalid address") {
    CmdResult r = run("\"" + aura_binary() +
                      "\" --compact gui disasm-function --addr nope");
    CHECK(r.exit_code == 2);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "invalid_func_addr");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: gui cfg-function rejects invalid address") {
    CmdResult r = run("\"" + aura_binary() +
                      "\" --compact gui cfg-function --addr nope");
    CHECK(r.exit_code == 2);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "invalid_func_addr");
    cJSON_Delete(root);
}
```

- [ ] **Step 2: Add dispatch code**

In the `if (cmd_gui->parsed())` block in `src/cli/main.cpp`, add branches before `quit`:

```cpp
auto parse_gui_addr = [&](const std::string &s, uint64_t &out) -> bool {
    try {
        out = std::stoull(s, nullptr, 0);
        return true;
    } catch (...) {
        return false;
    }
};

if (cmd_gui_disasm_function->parsed()) {
    uint64_t addr = 0;
    if (!parse_gui_addr(gui_disasm_addr, addr)) {
        emit_error_json("invalid_func_addr",
                        "could not parse --addr: " + gui_disasm_addr,
                        g.compact);
        return 2;
    }
    cJSON *p = params_object();
    cJSON_AddNumberToObject(p, "addr", static_cast<double>(addr));
    return run_gui_rpc("disasm_function", p, gui_rpc, g,
                       "gui disasm-function");
}
if (cmd_gui_cfg_function->parsed()) {
    uint64_t addr = 0;
    if (!parse_gui_addr(gui_cfg_addr, addr)) {
        emit_error_json("invalid_func_addr",
                        "could not parse --addr: " + gui_cfg_addr,
                        g.compact);
        return 2;
    }
    cJSON *p = params_object();
    cJSON_AddNumberToObject(p, "addr", static_cast<double>(addr));
    return run_gui_rpc("cfg_function", p, gui_rpc, g,
                       "gui cfg-function");
}
if (cmd_gui_rename->parsed()) {
    cJSON *p = params_object();
    cJSON_AddNumberToObject(p, "function_row", gui_rename_row);
    cJSON_AddStringToObject(p, "new_name", gui_rename_name.c_str());
    return run_gui_rpc("rename", p, gui_rpc, g, "gui rename");
}
if (cmd_gui_reset_name->parsed()) {
    cJSON *p = params_object();
    cJSON_AddNumberToObject(p, "function_row", gui_reset_name_row);
    return run_gui_rpc("reset_name", p, gui_rpc, g, "gui reset-name");
}
```

- [ ] **Step 3: Run CLI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: invalid address tests pass and existing GUI CLI tests remain green.

## Task 2: MCP Tool Registry for GUI

**Files:**
- Modify: `src/mcp/mcp_tools.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] Add read-only GUI MCP tool specs:
  - `aura_gui_status`
    - required: `gui_port`, `gui_token`
  - `aura_gui_functions`
    - required: `gui_port`, `gui_token`
  - `aura_gui_protected_strings`
    - required: `gui_port`, `gui_token`
  - `aura_gui_symbols`
    - required: `gui_port`, `gui_token`
  - `aura_gui_xrefs`
    - required: `gui_port`, `gui_token`
  - `aura_gui_disasm_function`
    - required: `gui_port`, `gui_token`, `function_addr`
  - `aura_gui_cfg_function`
    - required: `gui_port`, `gui_token`, `function_addr`

- [ ] Add action GUI MCP tool specs:
  - `aura_gui_add_binary`
    - required: `gui_port`, `gui_token`, `binary_path`
  - `aura_gui_analyze`
    - required: `gui_port`, `gui_token`
    - defaulted: `row` defaults to `0`, `level` defaults to `full`

- [ ] Add mutation GUI MCP tool specs only with explicit confirmation:
  - `aura_gui_rename`
    - required: `gui_port`, `gui_token`, `function_row`, `new_name`, `confirm_mutation`
  - `aura_gui_reset_name`
    - required: `gui_port`, `gui_token`, `function_row`, `confirm_mutation`

- [ ] `tools/list` must show GUI tools distinctly from static-analysis tools.

### Task 2A: GUI MCP tool list contracts

**Files:**
- Modify: `src/mcp/mcp_tools.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add failing tools/list test**

Add this helper near the other MCP JSON helper functions in `tests/integration/mcp_smoke/mcp_smoke.cpp`. If a helper with this exact name already exists in the file, replace its body with this implementation rather than adding a duplicate:

```cpp
bool toolsArrayHasName(const cJSON* tools, const char* name);
```

Then add:

```cpp
TEST_CASE("aura-mcp lists GUI MCP tools") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath("gui_tools_list");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"tools/list\","
                 "\"params\":{}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    cJSON* response = parseLine(out, 0);
    const cJSON* tools =
        cJSON_GetObjectItemCaseSensitive(resultOf(response), "tools");
    REQUIRE(cJSON_IsArray(tools));
    CHECK(toolsArrayHasName(tools, "aura_gui_status"));
    CHECK(toolsArrayHasName(tools, "aura_gui_add_binary"));
    CHECK(toolsArrayHasName(tools, "aura_gui_analyze"));
    CHECK(toolsArrayHasName(tools, "aura_gui_functions"));
    CHECK(toolsArrayHasName(tools, "aura_gui_protected_strings"));
    cJSON_Delete(response);
    std::remove(input_path.c_str());
}
```

- [ ] **Step 2: Add minimal read/analyze GUI tools to registry**

In `src/mcp/mcp_tools.cpp`, add required field arrays near existing arrays:

```cpp
constexpr const char* kGuiAuthFields[] = {"gui_port", "gui_token"};
constexpr const char* kGuiBinaryFields[] = {
    "gui_port", "gui_token", "binary_path"};
```

Add these `ToolSpec` entries to `kTools`:

```cpp
{"aura_gui_status",
 "Query a running foreground AURA GUI status via localhost RPC.",
 kGuiAuthFields, 2},
{"aura_gui_add_binary",
 "Add a binary to the running foreground AURA GUI project.",
 kGuiBinaryFields, 3},
{"aura_gui_analyze",
 "Run analysis in the running foreground AURA GUI.",
 kGuiAuthFields, 2},
{"aura_gui_functions",
 "List functions from the running foreground AURA GUI.",
 kGuiAuthFields, 2},
{"aura_gui_protected_strings",
 "List LLM/MCP-safe protected strings from the running foreground AURA GUI.",
 kGuiAuthFields, 2},
```

- [ ] **Step 3: Run MCP smoke and verify the new test fails only until dispatch is added**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected after tool list only: tools/list test passes; call tests for GUI tools are not added yet.

## Task 3: MCP GUI Bridge Through CLI

**Files:**
- Modify: `src/mcp/mcp_cli_bridge.cpp`
- Modify: `src/mcp/mcp_cli_bridge.h`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] Implement GUI tool dispatch by calling `aura gui ...` subprocess commands.

Mapping:

| MCP tool | CLI command |
|---|---|
| `aura_gui_status` | `aura gui --port P --token T status` |
| `aura_gui_add_binary` | `aura gui --port P --token T add-binary PATH` |
| `aura_gui_analyze` | `aura gui --port P --token T analyze --row N --level full` |
| `aura_gui_functions` | `aura gui --port P --token T functions` |
| `aura_gui_protected_strings` | `aura gui --port P --token T protected-strings` |
| `aura_gui_symbols` | `aura gui --port P --token T symbols` |
| `aura_gui_xrefs` | `aura gui --port P --token T xrefs` |
| `aura_gui_disasm_function` | `aura gui --port P --token T disasm-function --addr ADDR` |
| `aura_gui_cfg_function` | `aura gui --port P --token T cfg-function --addr ADDR` |
| `aura_gui_rename` | `aura gui --port P --token T rename --row N --name NAME` |
| `aura_gui_reset_name` | `aura gui --port P --token T reset-name --row N` |

- [ ] Wrap every response with MCP protected envelope:
  - `kind`: MCP tool name
  - `status`: `ok` or `error`
  - `disclosure`: `protected`
  - `data.aura_cli`: parsed CLI response

- [ ] For `aura_gui_protected_strings`, assert output contains no raw `content`.

- [ ] For `aura_gui_disasm_function`, omit raw `text` and `op_str` from MCP envelopes and mark them as omitted.

### Task 3A: GUI MCP argument validation

**Files:**
- Modify: `src/mcp/mcp_tools.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add missing token/port tests**

Add:

```cpp
TEST_CASE("aura GUI MCP tools fail closed without GUI auth arguments") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath("gui_missing_auth");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_gui_status\","
                 "\"arguments\":{}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_gui_add_binary\","
                 "\"arguments\":{\"gui_port\":\"27654\","
                 "\"binary_path\":\"tests/fixtures/bin/elf_smoke.x86_64\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("invalid_arguments") != std::string::npos);
    CHECK(out.find("gui_token") != std::string::npos);
    std::remove(input_path.c_str());
}
```

- [ ] **Step 2: Implement required-field validation before dispatch**

In `src/mcp/mcp_tools.cpp`, add helper:

```cpp
bool argsHaveRequiredFields(cJSON* args_or_null,
                            const ToolSpec& tool,
                            const char** missing_field) {
    if (missing_field) {
        *missing_field = nullptr;
    }
    if (tool.required_fields == nullptr || tool.required_count == 0) {
        return true;
    }
    if (!cJSON_IsObject(args_or_null)) {
        if (missing_field) {
            *missing_field = tool.required_fields[0];
        }
        return false;
    }
    for (int i = 0; i < tool.required_count; ++i) {
        const char* field = tool.required_fields[i];
        cJSON* value = cJSON_GetObjectItemCaseSensitive(args_or_null, field);
        if (value == nullptr ||
            (cJSON_IsString(value) && value->valuestring[0] == '\0')) {
            if (missing_field) {
                *missing_field = field;
            }
            return false;
        }
    }
    return true;
}
```

Then call it in `aura_mcp_call_tool_json` before raw-tool handling or dispatch:

```cpp
const char* missing_field = nullptr;
if (!argsHaveRequiredFields(args_or_null, *tool, &missing_field)) {
    std::string message = "missing required argument: ";
    message += missing_field != nullptr ? missing_field : "unknown";
    return aura_mcp_envelope_error("protected/1.0",
                                   tool->name,
                                   "invalid_arguments",
                                   message.c_str(),
                                   "protected");
}
```

- [ ] **Step 3: Run MCP smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected: missing auth tests pass.

### Task 3B: Bridge first-slice GUI tools

**Files:**
- Modify: `src/mcp/mcp_cli_bridge.cpp`
- Modify: `src/mcp/mcp_cli_bridge.h`
- Modify: `src/mcp/mcp_tools.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Export the GUI bridge entrypoint**

In `src/mcp/mcp_cli_bridge.h`, add the GUI bridge declaration directly after `aura_mcp_cli_bridge_call_json`:

```cpp
cJSON* aura_mcp_cli_bridge_gui_call_json(const char* tool_name,
                                         cJSON*      args_or_null);
```

- [ ] **Step 2: Add bridge helpers for GUI arguments**

In `src/mcp/mcp_cli_bridge.cpp`, add these helpers inside the existing anonymous namespace near `jsonStringField` / `jsonIntField`:

```cpp
const char* stringArg(cJSON* args_or_null, const char* key) {
    cJSON* item = cJSON_GetObjectItemCaseSensitive(args_or_null, key);
    return cJSON_IsString(item) ? item->valuestring : nullptr;
}

const char* stringArgOrDefault(cJSON* args_or_null,
                               const char* key,
                               const char* fallback) {
    const char* value = stringArg(args_or_null, key);
    return nonempty(value) ? value : fallback;
}

std::string numberArgOrDefault(cJSON* args_or_null,
                               const char* key,
                               int fallback) {
    cJSON* item = cJSON_GetObjectItemCaseSensitive(args_or_null, key);
    if (cJSON_IsNumber(item)) {
        return std::to_string(item->valueint);
    }
    if (cJSON_IsString(item) && nonempty(item->valuestring)) {
        return item->valuestring;
    }
    return std::to_string(fallback);
}
```

- [ ] **Step 3: Add GUI bridge command builder**

In `src/mcp/mcp_cli_bridge.cpp`, add a function close to existing CLI bridge entrypoint:

```cpp
extern "C" cJSON* aura_mcp_cli_bridge_gui_call_json(const char* name,
                                                     cJSON* args_or_null) {
    const char* port = stringArg(args_or_null, "gui_port");
    const char* token = stringArg(args_or_null, "gui_token");
    if (!nonempty(port) || !nonempty(token)) {
        return aura_mcp_envelope_error("protected/1.0",
                                       name,
                                       "invalid_arguments",
                                       "gui_port and gui_token are required",
                                       "protected");
    }

    std::vector<CliArg> args = {
        literalArg("--compact"),
        literalArg("gui"),
        literalArg("--port"),
        literalArg(port),
        literalArg("--token"),
        literalArg(token),
    };

    if (streq(name, "aura_gui_status")) {
        args.push_back(literalArg("status"));
    } else if (streq(name, "aura_gui_add_binary")) {
        const char* binary_path = stringArg(args_or_null, "binary_path");
        args.push_back(literalArg("add-binary"));
        args.push_back(literalArg(binary_path));
    } else if (streq(name, "aura_gui_analyze")) {
        const std::string row = numberArgOrDefault(args_or_null, "row", 0);
        const char* level = stringArgOrDefault(args_or_null, "level", "full");
        args.push_back(literalArg("analyze"));
        args.push_back(literalArg("--row"));
        args.push_back(literalArg(row.c_str()));
        args.push_back(literalArg("--level"));
        args.push_back(literalArg(level));
    } else if (streq(name, "aura_gui_functions")) {
        args.push_back(literalArg("functions"));
    } else if (streq(name, "aura_gui_protected_strings")) {
        args.push_back(literalArg("protected-strings"));
    } else {
        return aura_mcp_envelope_error("protected/1.0",
                                       name,
                                       "tool_not_implemented",
                                       "GUI MCP bridge does not implement this tool",
                                       "protected");
    }

    return runCliAndWrap(name, args);
}
```

- [ ] **Step 4: Dispatch first-slice GUI tools**

In `src/mcp/mcp_tools.cpp`, ensure the existing include section contains this include exactly once:

```cpp
#include "mcp_cli_bridge.h"
```

Then dispatch these tools before falling through to the existing static-analysis bridge:

```cpp
if (streq(name, "aura_gui_status") ||
    streq(name, "aura_gui_add_binary") ||
    streq(name, "aura_gui_analyze") ||
    streq(name, "aura_gui_functions") ||
    streq(name, "aura_gui_protected_strings")) {
    return aura_mcp_cli_bridge_gui_call_json(name, args_or_null);
}
```

- [ ] **Step 5: Add not-running GUI failure test**

Add in `mcp_smoke`:

```cpp
TEST_CASE("aura GUI MCP status reports unreachable GUI") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath("gui_unreachable");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_gui_status\","
                 "\"arguments\":{\"gui_port\":\"65534\","
                 "\"gui_token\":\"demo-token\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("aura_gui_status") != std::string::npos);
    CHECK(out.find("\"status\":\"error\"") != std::string::npos);
    CHECK(out.find("gui_rpc_connect_failed") != std::string::npos);
    std::remove(input_path.c_str());
}
```

- [ ] **Step 6: Run MCP smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected: GUI unreachable test returns protected error, not a crash.

## Task 4: GUI Foreground Demo Harness

**Files:**
- Create: `.scratch/aura_gui_mcp_demo_console.ps1`

- [ ] Add a visible PowerShell demo console that starts foreground GUI:
  ```powershell
  $env:AURA_GUI_RPC_PORT = "27654"
  $env:AURA_GUI_RPC_TOKEN = "aura-demo-token"
  Start-Process -FilePath .\build-trim-gui\src\gui\Release\aura-gui.exe -WindowStyle Normal
  ```

- [ ] The demo console must not exit after one run.

- [ ] The demo console waits for trigger files and performs:
  - check GUI RPC status
  - add fixture binary
  - analyze row 0
  - fetch functions
  - fetch protected strings
  - fetch symbols/xrefs
  - fetch CFG/disasm for the first function reported by `functions`

- [ ] Every capture is written to:
  - `.scratch/mcp-gui-demo-captures/capture-YYYYMMDD-HHMMSS.log`

### Task 4A: Persistent foreground demo console

**Files:**
- Create: `.scratch/aura_gui_mcp_demo_console.ps1`

- [ ] **Step 1: Create demo console script**

Create `.scratch/aura_gui_mcp_demo_console.ps1`:

```powershell
$ErrorActionPreference = "Stop"

$Repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$Aura = Join-Path $Repo "build-trim-gui\src\cli\Release\aura.exe"
$Gui = Join-Path $Repo "build-trim-gui\src\gui\Release\aura-gui.exe"
$Mcp = Join-Path $Repo "build-trim-gui\src\mcp\Release\aura-mcp.exe"
$Fixture = "tests/fixtures/bin/elf_smoke.x86_64"
$Port = "27654"
$Token = "aura-demo-token"
$RequestDir = Join-Path $Repo ".scratch\mcp-gui-demo-requests"
$CaptureDir = Join-Path $Repo ".scratch\mcp-gui-demo-captures"

New-Item -ItemType Directory -Force -Path $RequestDir | Out-Null
New-Item -ItemType Directory -Force -Path $CaptureDir | Out-Null

$env:AURA_GUI_RPC_PORT = $Port
$env:AURA_GUI_RPC_TOKEN = $Token
$env:AURA_REPO_ROOT = $Repo
$env:AURA_MCP_ALLOWED_ROOTS = $Repo
$Host.UI.RawUI.WindowTitle = "AURA MCP GUI Demo Console"
Set-Location $Repo

function Ensure-Gui {
    $existing = Get-Process | Where-Object { $_.ProcessName -eq "aura-gui" } | Select-Object -First 1
    if ($null -eq $existing) {
        Start-Process -FilePath $Gui -WorkingDirectory $Repo -WindowStyle Normal | Out-Null
        Start-Sleep -Seconds 2
    }
}

function Invoke-Capture {
    $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
    $capture = Join-Path $CaptureDir "capture-$stamp.log"
    Ensure-Gui

    $commands = @(
        @("status"),
        @("add-binary", $Fixture),
        @("analyze", "--row", "0", "--level", "full"),
        @("functions"),
        @("protected-strings")
    )

    $out = New-Object System.Collections.Generic.List[string]
    $out.Add("AURA MCP GUI capture $stamp")
    foreach ($cmd in $commands) {
        $line = "aura gui --port <redacted> --token <redacted> " + ($cmd -join " ")
        Write-Host $line -ForegroundColor Yellow
        $out.Add($line)
        $result = & $Aura --compact gui --port $Port --token $Token @cmd
        Write-Host $result
        $out.Add($result)
    }
    $utf8NoBom = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllLines($capture, $out, $utf8NoBom)
    Write-Host "Capture written: $capture" -ForegroundColor Green
}

Write-Host "AURA MCP GUI Demo Console stays open." -ForegroundColor Green
Write-Host "Create *.trigger in $RequestDir to capture again."
while ($true) {
    $trigger = Get-ChildItem -LiteralPath $RequestDir -Filter "*.trigger" -File |
        Sort-Object LastWriteTime |
        Select-Object -First 1
    if ($null -ne $trigger) {
        Remove-Item -LiteralPath $trigger.FullName -Force
        Invoke-Capture
    }
    Start-Sleep -Milliseconds 500
}
```

- [ ] **Step 2: Launch visible console**

Run:

```powershell
$repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$script = Join-Path $repo ".scratch\aura_gui_mcp_demo_console.ps1"
$cmd = "& '$script'"
$encoded = [Convert]::ToBase64String([System.Text.Encoding]::Unicode.GetBytes($cmd))
Start-Process -FilePath powershell.exe -ArgumentList @("-NoExit","-ExecutionPolicy","Bypass","-EncodedCommand",$encoded) -WindowStyle Normal
```

Expected: visible PowerShell window titled `AURA MCP GUI Demo Console` remains open.

- [ ] **Step 3: Trigger a capture**

Run:

```powershell
$repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$requestDir = Join-Path $repo ".scratch\mcp-gui-demo-requests"
New-Item -ItemType Directory -Force -Path $requestDir | Out-Null
Set-Content -LiteralPath (Join-Path $requestDir "capture.trigger") -Value "capture" -Encoding UTF8
```

Expected:

- foreground `aura-gui` is visible
- console remains open
- `.scratch\mcp-gui-demo-captures\capture-*.log` is created
- capture log does not contain `aura-demo-token`

## Task 5: Integration Tests

**Files:**
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] CLI smoke:
  - Validate new `aura gui disasm-function --addr ...` command shape.
  - Validate new `aura gui cfg-function --addr ...` command shape.
  - Validate `rename/reset-name` argument validation without needing running GUI.

- [ ] MCP smoke:
  - `tools/list` includes new `aura_gui_*` tools.
  - Missing `gui_token` fails closed.
  - Missing `gui_port` fails closed or uses env only when env is explicitly present.
  - Mutation tools require `confirm_mutation=true`.

- [ ] GUI smoke:
  - Use `MainWindow` public APIs as the GUI state oracle.
  - Add binary/analyze through GUI API.
  - Validate existing public APIs still match RPC output:
    - `functionList`
    - `protected_strings`
    - `symbols`
    - `xrefs`

## Task 6: Manual Foreground Verification

**Files:**
- No repo source changes unless demo script is kept under `.scratch`.

- [ ] Build:
  ```powershell
  cmake --build build-trim-gui --config Release --target aura
  cmake --build build-trim-gui --config Release --target aura-gui
  cmake --build build-trim-gui --config Release --target aura-mcp
  ```

- [ ] Start foreground GUI:
  ```powershell
  $env:AURA_GUI_RPC_PORT="27654"
  $env:AURA_GUI_RPC_TOKEN="aura-demo-token"
  .\build-trim-gui\src\gui\Release\aura-gui.exe
  ```

- [ ] In another visible PowerShell, run CLI GUI RPC:
  ```powershell
  .\build-trim-gui\src\cli\Release\aura.exe --compact gui --port 27654 --token aura-demo-token status
  .\build-trim-gui\src\cli\Release\aura.exe --compact gui --port 27654 --token aura-demo-token add-binary tests\fixtures\bin\elf_smoke.x86_64
  .\build-trim-gui\src\cli\Release\aura.exe --compact gui --port 27654 --token aura-demo-token analyze --row 0 --level full
  .\build-trim-gui\src\cli\Release\aura.exe --compact gui --port 27654 --token aura-demo-token functions
  ```

- [ ] Then run MCP GUI tool calls through `aura-mcp` JSON-RPC:
  - `aura_gui_status`
  - `aura_gui_analyze`
  - `aura_gui_functions`
  - `aura_gui_protected_strings`

- [ ] The GUI window must remain visible and open after all operations.

## Verification Matrix

| Area | Command | Required Result |
|---|---|---|
| CLI GUI parity | `ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure` | PASS |
| MCP GUI tools listed | `ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure` | PASS |
| GUI behavior | `ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure` | PASS |
| Foreground GUI demo | visible `aura-gui.exe` window | stays open |
| MCP->GUI status | MCP `aura_gui_status` | returns GUI binary/function counts |
| MCP->GUI analyze | MCP `aura_gui_analyze` | GUI state changes, function count > 0 |
| Safety boundary | MCP `aura_gui_protected_strings` | no raw `content` |

## Acceptance Criteria

- MCP tool list includes GUI tools with `aura_gui_*` names.
- MCP can query a running foreground GUI via localhost RPC.
- MCP can add a binary and trigger analysis in the running GUI.
- MCP can retrieve GUI state/results after analysis.
- CLI has equivalent `aura gui ...` commands for every GUI MCP behavior.
- GUI remains the user-visible source of truth during demo.
- Raw string content and raw disassembly/decompile text are not exposed through GUI MCP tools by default.
- Tests cover CLI, MCP, and GUI paths together.

## Self-Review

- Spec coverage: covers the missing MCP->GUI bridge and enforces CLI+GUI simultaneous development.
- Placeholder scan: no task relies on TBD behavior; every tool maps to an existing or planned CLI command.
- Safety check: GUI mutation tools are explicit and confirmation-gated; protected output remains the default.
- UX check: demo requirement is foreground GUI first, not hidden or background-only automation.
