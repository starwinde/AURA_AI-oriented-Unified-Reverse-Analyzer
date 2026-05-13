# MCP Real-Use Test and JSON Debug CLI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 실제 MCP stdio 호출을 재현하는 테스트, MCP 서버에 전송할 JSON-RPC 라인을 CLI에서 확인하는 `aura mcp-json` 명령, 그리고 Codex MCP 설정 등록 후 서브에이전트가 실제 도구 호출을 확인하는 검증 경로를 추가한다.

**Architecture:** `aura-mcp`는 그대로 MCP stdio 서버 역할을 유지한다. 새 `aura mcp-json` subcommand는 MCP 클라이언트가 보낼 newline-delimited JSON-RPC 요청을 생성하고, `mcp_smoke`는 그 JSON을 실제 `aura-mcp` 프로세스에 파이프로 넣어 응답 구조와 보호 정책을 검증한다. 마지막 검증은 `codex mcp add aura ...`로 Codex 설정에 서버를 등록한 뒤, 새 서브에이전트가 MCP 도구 discovery와 최소 tool call을 확인하는 방식으로 한다.

**Tech Stack:** C++17, CLI11, cJSON, CMake, doctest, Windows/MSVC Release build, existing `aura-mcp` stdio transport.

---

## Scope

이번 작업은 MCP를 “문서상 존재”가 아니라 “실제 stdio 프로세스에 JSON-RPC를 넣고 응답을 받는” 수준으로 검증한다.

포함:

- `aura mcp-json initialize`
- `aura mcp-json tools-list`
- `aura mcp-json call <tool-name> [--binary <path>] [--func <addr>]`
- `mcp_smoke`에서 `aura mcp-json` 출력물을 실제 `aura-mcp` 입력으로 사용
- `cli_smoke`에서 JSON 형식 확인
- `codex mcp add aura -- <aura-mcp.exe>`로 Codex MCP 설정 등록
- Codex 설정 등록 후 서브에이전트가 `aura_probe_engines` 또는 `aura_info` 도구를 실제 호출해 확인
- MCP/CLI/GUI 기준 문서에 “MCP 실사용 테스트는 stdio JSON-RPC 라인을 기준으로 한다”는 규칙 반영

제외:

- MCP over HTTP/SSE
- raw disassembly/decompile 허용 정책 변경
- GUI에 MCP 테스트 버튼 추가
- Codex 전역 MCP 등록을 repo 커밋에 포함하는 것
- Codex MCP 등록 실패를 AURA 서버 실패로 단정하는 것

## File Structure

- Modify: `src/cli/main.cpp`
  - `mcp-json` subcommand를 추가한다.
  - MCP JSON-RPC 요청 생성 helper를 추가한다.
  - 기존 `--compact` 출력 정책을 따른다.
  - 기존 CLI11 dispatch 구조를 유지한다. `CLI11_PARSE(app, argc, argv);` 직후 `cmd_mcp_json->parsed()`를 먼저 처리해 분석 엔진 초기화 없이 JSON request만 출력하게 한다.

- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
  - `aura mcp-json initialize/tools-list/call` 출력 구조를 검증한다.
  - 출력 JSON이 실제 JSON-RPC envelope인지 확인한다.
  - 기존 helper `aura_binary()`, `run()`, `parse_or_fail()`, `get_string()`, `fixture_path()`를 재사용한다.

- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - `aura mcp-json`으로 만든 JSON line을 `aura-mcp`에 입력한다.
  - initialize -> initialized notification -> tools/list -> tools/call 순서를 실제 프로세스 파이프에서 검증한다.
  - 기존 helper `quotePath()`, `runCommand()`, `runMcpWithInput()`, `parseLine()`, `responseLineCount()`, `envelopeFromCallResponse()`, `checkProtectedOkEnvelope()`, `jsonTreeHasKey()`를 재사용한다.

- Modify: `tests/integration/mcp_smoke/CMakeLists.txt`
  - `mcp_smoke`에 `AURA_BIN=$<TARGET_FILE:aura>` 환경이 반드시 들어가게 유지한다.
  - `aura` target이 없으면 JSON debug roundtrip case만 skip한다.

- Modify: `CLAUDE.md`
  - MCP 테스트 기준을 “실제 `aura-mcp` stdio roundtrip + CLI JSON fixture”로 명시한다.

- Modify: `.claude/CLAUDE.md`
  - 루트 `CLAUDE.md`와 동일한 MCP 테스트 기준을 반영한다.

- External config: `C:\Users\21m15\.codex\config.toml`
  - `codex mcp add` 명령으로 `aura` MCP 서버를 등록한다.
  - 직접 편집이 필요하면 먼저 `.bak` 백업을 만든다.
  - 이 파일은 repo commit 대상이 아니다.

## Current Source Anchors

구현자는 아래 현재 구조를 기준으로 작업한다.

- `src/cli/main.cpp`
  - JSON 출력 helper: `make_root()`, `emit_json()`, `emit_error_json()`
  - subcommand 선언 위치: `main()` 내부 `cmd_engines` 선언 직후가 `mcp-json` 추가 위치
  - dispatch 위치: `CLI11_PARSE(app, argc, argv);` 직후, `if (cmd_engines->parsed())`보다 앞
  - 이유: `mcp-json`은 분석 엔진/파일 검증/GUI RPC에 의존하지 않는 request generator다.
- `tests/integration/cli_smoke/cli_smoke.cpp`
  - subprocess helper: `run()`
  - binary path helper: `aura_binary()`
  - fixture helper: `fixture_path()`
  - JSON helper: `parse_or_fail()`, `get_string()`
- `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - subprocess helper: `runCommand()`
  - path quote helper: `quotePath()`
  - MCP pipe helper: `runMcpWithInput()`
  - MCP response helper: `parseLine()`, `resultOf()`, `contentTextOf()`
  - protected envelope helper: `envelopeFromCallResponse()`, `checkProtectedOkEnvelope()`, `jsonTreeHasKey()`
- `tests/integration/mcp_smoke/CMakeLists.txt`
  - already injects `AURA_MCP_BIN=$<TARGET_FILE:aura-mcp>`
  - already injects `AURA_BIN=$<TARGET_FILE:aura>` when target `aura` exists

## GUI/CLI Boundary Rule

이번 기능은 MCP 개발자 검증용이므로 GUI 버튼이나 GUI 화면은 추가하지 않는다. 다만 AURA의 개발 기준은 GUI를 기준으로 검증하므로, CLI가 생성하는 MCP request가 실제 GUI/LLM-safe protected envelope 정책을 우회하지 않는지 `mcp_smoke`에서 확인한다. 즉, GUI에 새 컨트롤을 만들지는 않지만 CLI/MCP 출력 정책은 GUI의 안전 출력 기준과 일치해야 한다.

## Autoplan Review Revisions

이 섹션은 `autoplan` 검토 결과를 반영한 실행 제약이다.

- **CEO/Product:** `aura mcp-json`은 최종 사용자 기능이 아니라 MCP 연동 확인용 개발자 도구다. CLI 도움말과 테스트명은 "debug/request generator"로 표현하고, 정규 분석 UX처럼 홍보하지 않는다.
- **Engineering:** MCP JSON-RPC request generator는 실제 `aura-mcp` 서버의 protocol version과 method 이름을 그대로 써야 한다. 상수가 흩어지는 것을 줄이기 위해 `mcp-json` helper 근처에 protocol version/comment를 명시한다.
- **DX:** Codex MCP 등록은 전역 설정 변경이므로 반드시 `codex mcp get aura`, `codex mcp list`, 실패 시 rollback 명령을 최종 출력에 포함한다.
- **Security:** `AURA_MCP_ALLOWED_ROOTS`는 repo root로 제한한다. 테스트 fixture 외 경로를 허용하지 않는다.
- **Verification:** 서브에이전트가 MCP 도구를 보지 못하면 즉시 실패 처리하지 않고, "현재 세션에 새 MCP server가 hot-load되지 않음"과 "fresh `codex exec`에서도 보이지 않음"을 구분한다.

## NOT in Scope

- raw MCP 도구 enablement
- 외부 LLM이 대용량 raw disassembly/decompile payload를 직접 받는 흐름
- MCP server transport를 HTTP/SSE로 확장
- GUI에 MCP 등록/테스트 버튼 추가
- Codex 전역 설정을 repo commit으로 추적

## What Already Exists

- `src/mcp/mcp_server.cpp`: newline-delimited JSON-RPC stdio loop, `initialize`, `tools/list`, `tools/call`, `ping` 처리.
- `src/mcp/mcp_tools.cpp`: `aura_probe_engines`, `aura_info`, `aura_analyze`, function detail tools, raw-denied tools 목록.
- `src/mcp/mcp_cli_bridge.cpp`: MCP tool call을 `aura` CLI 실행으로 브리지하고 protected envelope로 감싼다.
- `tests/integration/mcp_smoke/mcp_smoke.cpp`: 현재도 직접 JSONL을 만들어 `aura-mcp`에 파이프하는 integration test가 있다.
- `codex mcp add`: 로컬 Codex CLI에 외부 stdio MCP server를 등록하는 명령이 이미 제공된다.

## Architecture Diagram

```text
developer / subagent
    |
    | Codex MCP tool discovery/call
    v
Codex MCP config ("aura")
    |
    | stdio command: build-trim-gui/src/mcp/Release/aura-mcp.exe
    v
aura-mcp
    |
    | tools/call
    v
src/mcp/mcp_tools.cpp
    |
    | protected bridge
    v
src/mcp/mcp_cli_bridge.cpp
    |
    | subprocess
    v
build-trim-gui/src/cli/Release/aura.exe
    |
    | analyze/info/probe JSON
    v
protected MCP envelope
```

## Failure Modes Registry

| Failure | User-visible Symptom | Detection | Response |
|---|---|---|---|
| `aura-mcp.exe` not built | `codex mcp add` points to missing command or subagent cannot start server | `Test-Path $mcp` before registration | Build `aura-mcp`, then re-run registration |
| Stale Codex MCP registration | Subagent calls old binary or wrong repo | `codex mcp get aura` path mismatch | `codex mcp remove aura`, then add fresh path |
| Allowed roots missing | MCP tool returns `no_allowed_roots` | `aura_info`/`aura_analyze` envelope error | Register with `--env AURA_MCP_ALLOWED_ROOTS="$repo"` |
| Current app session does not hot-load MCP | Parent session cannot see tools after `codex mcp add` | Subagent reports no AURA tools | Verify with fresh `codex exec`; mark restart required if fresh process works |
| Fresh Codex also cannot see MCP | No AURA tools in new process | `codex exec` verification fails | Record exact Codex MCP registration failure; do not blame AURA server without stdio test failure |
| Raw payload leaks | MCP response contains `content`, `raw_content`, disassembly `text`, or `op_str` | `mcp_smoke` key scan | Fail test; fix protected normalization before registration |

## Test Diagram

| Flow | Codepath | Test |
|---|---|---|
| CLI emits initialize request | `src/cli/main.cpp` `mcp-json initialize` | `cli_smoke: mcp-json initialize emits JSON-RPC request` |
| CLI emits tools/list request | `src/cli/main.cpp` `mcp-json tools-list` | `cli_smoke: mcp-json tools-list emits JSON-RPC request` |
| CLI emits tools/call request | `src/cli/main.cpp` `mcp-json call` | `cli_smoke: mcp-json call emits tool call request` |
| CLI-generated JSON drives server | `aura mcp-json` -> `aura-mcp` stdio | `mcp_smoke: aura-mcp accepts JSON generated by aura mcp-json` |
| Protected analyze envelope | `mcp_tools` -> `mcp_cli_bridge` -> `aura analyze` | existing and new `mcp_smoke` checks |
| Codex external registration | `codex mcp add/get/list` | manual verification plus subagent/fresh `codex exec` |

---

### Task 1: CLI JSON-RPC Request Generator

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] **Step 1: Write failing CLI smoke tests for `mcp-json initialize`**

Add this test near the other CLI JSON command tests in `tests/integration/cli_smoke/cli_smoke.cpp`:

```cpp
TEST_CASE("cli_smoke: mcp-json initialize emits JSON-RPC request") {
    CmdResult r =
        run("\"" + aura_binary() + "\" --compact mcp-json initialize");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_.substr(0, 200));

    cJSON* root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "jsonrpc") == "2.0");
    CHECK(get_string(root, "method") == "initialize");

    cJSON* id = cJSON_GetObjectItem(root, "id");
    REQUIRE(cJSON_IsNumber(id));
    CHECK(id->valueint == 1);

    cJSON* params = cJSON_GetObjectItem(root, "params");
    REQUIRE(cJSON_IsObject(params));
    CHECK(get_string(params, "protocolVersion") == "2025-06-18");

    cJSON* clientInfo = cJSON_GetObjectItem(params, "clientInfo");
    REQUIRE(cJSON_IsObject(clientInfo));
    CHECK(get_string(clientInfo, "name") == "aura-cli");

    cJSON_Delete(root);
}
```

Add this negative-path test in the same file:

```cpp
TEST_CASE("cli_smoke: mcp-json unknown subcommand fails closed") {
    CmdResult r =
        run("\"" + aura_binary() + "\" --compact mcp-json nope");
    CHECK(r.exit_code != 0);
}
```

- [ ] **Step 2: Run test and confirm it fails**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: `mcp-json` is not a recognized command or test fails because the command does not exist.

- [ ] **Step 3: Add MCP JSON helper functions**

In `src/cli/main.cpp`, add helpers near `make_root()` / `emit_json()`:

```cpp
cJSON* make_jsonrpc_request(int id, const char* method) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "jsonrpc", "2.0");
    cJSON_AddNumberToObject(root, "id", id);
    cJSON_AddStringToObject(root, "method", method);
    return root;
}

cJSON* make_mcp_initialize_request() {
    cJSON* root = make_jsonrpc_request(1, "initialize");
    cJSON* params = cJSON_CreateObject();
    cJSON* capabilities = cJSON_CreateObject();
    cJSON* client_info = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "protocolVersion", "2025-06-18");
    cJSON_AddItemToObject(params, "capabilities", capabilities);
    cJSON_AddStringToObject(client_info, "name", "aura-cli");
    cJSON_AddStringToObject(client_info, "version", "1");
    cJSON_AddItemToObject(params, "clientInfo", client_info);
    cJSON_AddItemToObject(root, "params", params);
    return root;
}

cJSON* make_mcp_tools_list_request() {
    cJSON* root = make_jsonrpc_request(2, "tools/list");
    cJSON_AddItemToObject(root, "params", cJSON_CreateObject());
    return root;
}
```

- [ ] **Step 4: Add `mcp-json initialize` and `mcp-json tools-list` subcommands**

In `main()` after the existing `engines` command declaration, add:

```cpp
auto* cmd_mcp_json = app.add_subcommand(
    "mcp-json", "emit MCP JSON-RPC request lines for debugging");
cmd_mcp_json->require_subcommand(1);

auto* cmd_mcp_init = cmd_mcp_json->add_subcommand(
    "initialize", "emit an MCP initialize request");
auto* cmd_mcp_tools = cmd_mcp_json->add_subcommand(
    "tools-list", "emit an MCP tools/list request");
```

Immediately after `CLI11_PARSE(app, argc, argv);` and before `if (cmd_engines->parsed())`, add:

```cpp
if (cmd_mcp_json->parsed()) {
    cJSON* root = nullptr;
    if (cmd_mcp_init->parsed()) {
        root = make_mcp_initialize_request();
    } else if (cmd_mcp_tools->parsed()) {
        root = make_mcp_tools_list_request();
    }
    if (root == nullptr) {
        emit_error_json("invalid_mcp_json_command",
                        "unknown mcp-json command", g.compact);
        return 2;
    }
    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}
```

- [ ] **Step 5: Run test and confirm initialize passes**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: the new initialize test passes.

- [ ] **Step 6: Commit Task 1**

```powershell
git add src/cli/main.cpp tests/integration/cli_smoke/cli_smoke.cpp
git commit -m "feat: add MCP JSON request CLI"
```

---

### Task 2: Tool Call JSON Generation

**Files:**
- Modify: `src/cli/main.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`

- [ ] **Step 1: Write failing tests for `mcp-json tools-list` and `mcp-json call`**

Add:

```cpp
TEST_CASE("cli_smoke: mcp-json tools-list emits JSON-RPC request") {
    CmdResult r =
        run("\"" + aura_binary() + "\" --compact mcp-json tools-list");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_.substr(0, 200));

    cJSON* root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "jsonrpc") == "2.0");
    CHECK(get_string(root, "method") == "tools/list");
    cJSON* params = cJSON_GetObjectItem(root, "params");
    REQUIRE(cJSON_IsObject(params));
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: mcp-json call emits tool call request") {
    const std::string fixture = fixture_path();
    CmdResult r = run("\"" + aura_binary() +
                      " --compact mcp-json call aura_analyze --binary \"" +
                      fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_.substr(0, 300));

    cJSON* root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "jsonrpc") == "2.0");
    CHECK(get_string(root, "method") == "tools/call");

    cJSON* params = cJSON_GetObjectItem(root, "params");
    REQUIRE(cJSON_IsObject(params));
    CHECK(get_string(params, "name") == "aura_analyze");

    cJSON* args = cJSON_GetObjectItem(params, "arguments");
    REQUIRE(cJSON_IsObject(args));
    CHECK(get_string(args, "binary_path") == fixture);

    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: mcp-json call validates required binary argument") {
    CmdResult r =
        run("\"" + aura_binary() +
            "\" --compact mcp-json call aura_analyze");
    CHECK(r.exit_code == 2);

    cJSON* root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "missing_mcp_binary");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: mcp-json call validates function arguments") {
    const std::string fixture = fixture_path();
    CmdResult r =
        run("\"" + aura_binary() +
            "\" --compact mcp-json call aura_get_disassembly --binary \"" +
            fixture + "\"");
    CHECK(r.exit_code == 2);

    cJSON* root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "missing_mcp_function_args");
    cJSON_Delete(root);
}
```

- [ ] **Step 2: Run test and confirm tool call test fails**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: `mcp-json call` is not implemented yet.

- [ ] **Step 3: Add `make_mcp_tool_call_request`**

In `src/cli/main.cpp`, add:

```cpp
cJSON* make_mcp_tool_call_request(int id,
                                  const std::string& tool_name,
                                  const std::string& binary_path,
                                  const std::string& function_addr) {
    cJSON* root = make_jsonrpc_request(id, "tools/call");
    cJSON* params = cJSON_CreateObject();
    cJSON* arguments = cJSON_CreateObject();

    cJSON_AddStringToObject(params, "name", tool_name.c_str());
    if (!binary_path.empty()) {
        cJSON_AddStringToObject(arguments, "binary_path", binary_path.c_str());
    }
    if (!function_addr.empty()) {
        cJSON_AddStringToObject(arguments, "function_addr",
                                function_addr.c_str());
    }
    cJSON_AddItemToObject(params, "arguments", arguments);
    cJSON_AddItemToObject(root, "params", params);
    return root;
}
```

- [ ] **Step 4: Add `mcp-json call` parser**

In `main()`, add:

```cpp
auto* cmd_mcp_call = cmd_mcp_json->add_subcommand(
    "call", "emit an MCP tools/call request");
std::string mcp_tool_name;
std::string mcp_binary_path;
std::string mcp_function_addr;
cmd_mcp_call->add_option("tool", mcp_tool_name,
                         "MCP tool name, e.g. aura_analyze")->required();
cmd_mcp_call->add_option("--binary", mcp_binary_path,
                         "binary_path argument for binary/function tools");
cmd_mcp_call->add_option("--func", mcp_function_addr,
                         "function_addr argument for function tools");
```

Extend the dispatch:

```cpp
} else if (cmd_mcp_call->parsed()) {
    root = make_mcp_tool_call_request(
        3, mcp_tool_name, mcp_binary_path, mcp_function_addr);
}
```

- [ ] **Step 5: Validate required argument combinations**

Before creating the request:

```cpp
if ((mcp_tool_name == "aura_info" || mcp_tool_name == "aura_analyze") &&
    mcp_binary_path.empty()) {
    emit_error_json("missing_mcp_binary",
                    "this MCP tool requires --binary", g.compact);
    return 2;
}
if ((mcp_tool_name == "aura_get_disassembly" ||
     mcp_tool_name == "aura_get_cfg" ||
     mcp_tool_name == "aura_get_llm_context") &&
    (mcp_binary_path.empty() || mcp_function_addr.empty())) {
    emit_error_json("missing_mcp_function_args",
                    "this MCP tool requires --binary and --func", g.compact);
    return 2;
}
```

`aura_probe_engines` intentionally allows empty `arguments`.

- [ ] **Step 6: Run CLI tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: `mcp-json` tests pass.

- [ ] **Step 7: Commit Task 2**

```powershell
git add src/cli/main.cpp tests/integration/cli_smoke/cli_smoke.cpp
git commit -m "feat: emit MCP tool call JSON from CLI"
```

---

### Task 3: Real MCP Stdio Roundtrip Using CLI-Generated JSON

**Files:**
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
- Modify: `tests/integration/mcp_smoke/CMakeLists.txt`

- [ ] **Step 1: Add helper to run `aura mcp-json` inside mcp smoke**

In `tests/integration/mcp_smoke/mcp_smoke.cpp`, add:

```cpp
std::string auraCliBinary() {
    const char* env = std::getenv("AURA_BIN");
    REQUIRE(env != nullptr);
    REQUIRE(env[0] != '\0');
    return env;
}

std::string runAuraMcpJson(const std::string& args) {
    return runCommand(quotePath(auraCliBinary()) + " --compact mcp-json " +
                      args);
}
```

Place these helpers inside the existing anonymous namespace, after `cliBridgeBuilt()` and before `parseLine()`.

- [ ] **Step 2: Write failing roundtrip test**

Add:

```cpp
TEST_CASE("aura-mcp accepts JSON generated by aura mcp-json") {
    if (!cliBridgeBuilt()) {
        return;
    }
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    ScopedEnvVar repo_root_env("AURA_REPO_ROOT");
    ScopedEnvVar allowed_roots_env("AURA_MCP_ALLOWED_ROOTS");
    const fs::path repo_root = findRepoRoot();
    REQUIRE(!repo_root.empty());
    REQUIRE(cliLooksAvailable(repo_root));
    const fs::path fixture =
        repo_root / "tests" / "fixtures" / "bin" / "elf_smoke.x86_64";
    REQUIRE(fs::exists(fixture));

    setEnvVar("AURA_REPO_ROOT", repo_root.string());
    setEnvVar("AURA_MCP_ALLOWED_ROOTS", repo_root.string());

    const std::string initialize = runAuraMcpJson("initialize");
    const std::string tools_list = runAuraMcpJson("tools-list");
    const std::string analyze =
        runAuraMcpJson("call aura_analyze --binary " +
                       quotePath(fixture.string()));

    const std::string input_path = tempInputPath("cli_generated_roundtrip");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << initialize;
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"notifications/"
                 "initialized\",\"params\":{}}\n";
        input << tools_list;
        input << analyze;
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(responseLineCount(out) == 3);
    CHECK(out.find("\"method\"") == std::string::npos);
    CHECK(out.find("\"id\":1") != std::string::npos);
    CHECK(out.find("\"id\":2") != std::string::npos);
    CHECK(out.find("\"id\":3") != std::string::npos);
    CHECK(out.find("aura_analyze") != std::string::npos);
    CHECK(out.find("aura_cli") != std::string::npos);
    CHECK(out.find("protected") != std::string::npos);

    cJSON* init_response = parseLine(out, 0);
    cJSON* tools_response = parseLine(out, 1);
    cJSON* analyze_response = parseLine(out, 2);
    const cJSON* init_result = resultOf(init_response);
    CHECK(optionalStringField(init_result, "protocolVersion") ==
          "2025-06-18");
    const cJSON* server_info =
        cJSON_GetObjectItemCaseSensitive(init_result, "serverInfo");
    REQUIRE(cJSON_IsObject(server_info));
    CHECK(optionalStringField(server_info, "name") == "aura-mcp");

    const cJSON* tools_result = resultOf(tools_response);
    const cJSON* tools =
        cJSON_GetObjectItemCaseSensitive(tools_result, "tools");
    REQUIRE(cJSON_IsArray(tools));
    CHECK(out.find("aura_probe_engines") != std::string::npos);
    CHECK(out.find("aura_analyze") != std::string::npos);

    cJSON* analyze_envelope = envelopeFromCallResponse(analyze_response);
    checkProtectedOkEnvelope(analyze_envelope, "aura_analyze");
    CHECK(!jsonTreeHasKey(analyze_envelope, "content"));
    CHECK(!jsonTreeHasKey(analyze_envelope, "raw_content"));

    cJSON_Delete(analyze_envelope);
    cJSON_Delete(analyze_response);
    cJSON_Delete(tools_response);
    cJSON_Delete(init_response);
    std::remove(input_path.c_str());
}
```

- [ ] **Step 3: Run mcp smoke and confirm failure if command is not wired**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected before Task 1/2 implementation: fails because `aura mcp-json` is missing. Expected after Task 1/2: passes.

- [ ] **Step 4: Keep CMake environment explicit**

Confirm `tests/integration/mcp_smoke/CMakeLists.txt` contains:

```cmake
if(TARGET aura)
    add_dependencies(mcp_smoke aura)
    target_compile_definitions(mcp_smoke PRIVATE AURA_MCP_SMOKE_HAS_CLI=1)
    list(APPEND _mcp_smoke_environment "AURA_BIN=$<TARGET_FILE:aura>")
else()
    target_compile_definitions(mcp_smoke PRIVATE AURA_MCP_SMOKE_HAS_CLI=0)
endif()
```

If missing or drifted, restore exactly that shape.

- [ ] **Step 5: Run MCP smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_smoke
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected: `mcp_smoke` passes and proves CLI-generated JSON can drive the real MCP server.

- [ ] **Step 6: Commit Task 3**

```powershell
git add tests/integration/mcp_smoke/mcp_smoke.cpp tests/integration/mcp_smoke/CMakeLists.txt
git commit -m "test: exercise MCP server with CLI-generated JSON"
```

---

### Task 4: Register Aura MCP in Codex and Verify with Subagent

**Files:**
- External config only: `C:\Users\21m15\.codex\config.toml`
- No repo files modified unless documenting the verification path.

- [ ] **Step 1: Snapshot current Codex MCP state**

Run:

```powershell
codex mcp list
codex mcp get aura
```

Expected: either `aura` is absent, or the output shows the current command/env that will be replaced. Copy the relevant lines into the working notes or final response before changing registration.

- [ ] **Step 2: Build `aura-mcp` and `aura` before registration**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura
cmake --build build-trim-gui --config Release --target aura-mcp
```

Expected: both targets build successfully.

- [ ] **Step 3: Verify executable paths exist**

Run:

```powershell
$repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$aura = "$repo\build-trim-gui\src\cli\Release\aura.exe"
$mcp = "$repo\build-trim-gui\src\mcp\Release\aura-mcp.exe"
Test-Path $aura
Test-Path $mcp
```

Expected: both print `True`.

- [ ] **Step 4: Remove stale Aura MCP registration if it exists**

Run:

```powershell
codex mcp list
codex mcp get aura
```

If `codex mcp get aura` returns an existing server with a stale path, remove it:

```powershell
codex mcp remove aura
```

Expected: either no existing `aura` server exists, or the stale one is removed cleanly.

- [ ] **Step 5: Register local `aura-mcp` in Codex**

Run:

```powershell
$repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$mcp = "$repo\build-trim-gui\src\mcp\Release\aura-mcp.exe"
codex mcp add aura `
  --env AURA_REPO_ROOT="$repo" `
  --env AURA_MCP_ALLOWED_ROOTS="$repo" `
  -- $mcp
```

Expected: Codex records an `aura` stdio MCP server.

- [ ] **Step 6: Inspect the registered server**

Run:

```powershell
codex mcp get aura
codex mcp list
```

Expected:

- server name is `aura`
- command points to `build-trim-gui\src\mcp\Release\aura-mcp.exe`
- environment includes `AURA_REPO_ROOT`
- environment includes `AURA_MCP_ALLOWED_ROOTS`

- [ ] **Step 7: Start a fresh subagent to verify MCP discovery**

Use `superpowers:subagent-driven-development` during execution. Spawn a fresh subagent with this exact task:

```text
You are verifying the newly registered AURA MCP server in Codex.

Do not edit files.
First, report whether an AURA MCP tool namespace is visible in your tool list.
Then try the lowest-risk available AURA MCP call:
- Prefer aura_probe_engines if available.
- If aura_probe_engines is not exposed by name, list the available AURA MCP tools and stop.

Return:
1. whether the aura MCP server was discoverable,
2. which tool names were visible,
3. whether the probe/info call succeeded,
4. the top-level response keys only, not large payloads.
```

Expected: the subagent can see the AURA MCP tool namespace or reports that the current Codex app needs a session restart to load newly registered MCP servers.

- [ ] **Step 8: If current session cannot see new MCP tools, verify through `codex exec`**

Run:

```powershell
codex exec -C "C:\Users\21m15\OneDrive\바탕 화면\AURA" `
  "Check whether the AURA MCP server is available. If available, call the safest AURA MCP probe tool and summarize the top-level response keys only. Do not edit files."
```

Expected: a fresh Codex process sees the registered MCP server. If it still does not, record the exact failure as a Codex MCP registration issue, not an AURA server failure.

- [ ] **Step 9: Commit nothing for external Codex config**

Run:

```powershell
git status --short --branch
```

Expected: `C:\Users\21m15\.codex\config.toml` changes are outside the repo and are not staged. Repo remains clean unless code/docs changed in earlier tasks.

---

### Task 5: Manual Real-Use Evidence Command

**Files:**
- Modify: `docs/superpowers/plans/2026-05-11-mcp-real-use-json-debug-cli.md`
- Optional Modify: `CLAUDE.md`
- Optional Modify: `.claude/CLAUDE.md`

- [ ] **Step 1: Run the real command sequence manually**

Run:

```powershell
$repo = "C:\Users\21m15\OneDrive\바탕 화면\AURA"
$aura = "$repo\build-trim-gui\src\cli\Release\aura.exe"
$mcp = "$repo\build-trim-gui\src\mcp\Release\aura-mcp.exe"
$fixture = "tests/fixtures/bin/elf_smoke.x86_64"
$env:AURA_REPO_ROOT = $repo
$env:AURA_MCP_ALLOWED_ROOTS = $repo
& $aura --compact mcp-json initialize
& $aura --compact mcp-json tools-list
& $aura --compact mcp-json call aura_analyze --binary $fixture
```

Expected: each command prints one JSON-RPC request with `jsonrpc:"2.0"`.

- [ ] **Step 2: Pipe the generated JSON into `aura-mcp`**

Run:

```powershell
$inputFile = Join-Path $env:TEMP "aura-mcp-real-use.jsonl"
$lines = @(
  (& $aura --compact mcp-json initialize),
  '{"jsonrpc":"2.0","method":"notifications/initialized","params":{}}',
  (& $aura --compact mcp-json tools-list),
  (& $aura --compact mcp-json call aura_analyze --binary $fixture)
)
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
[System.IO.File]::WriteAllLines($inputFile, $lines, $utf8NoBom)
Get-Content -Encoding UTF8 $inputFile | & $mcp
```

Expected:

- 3 response lines
- initialize response has `serverInfo.name:"aura-mcp"`
- tools/list response includes `aura_analyze`
- tools/call response contains a text envelope with `status:"ok"`, `kind:"aura_analyze"`, `disclosure:"protected"`

- [ ] **Step 3: Record verification output in final response**

Do not commit generated temp files. In the final answer, summarize:

```text
Manual MCP real-use:
- aura mcp-json initialize: PASS
- aura mcp-json tools-list: PASS
- aura mcp-json call aura_analyze: PASS
- piping JSONL into aura-mcp: PASS
- codex mcp add aura: PASS
- subagent MCP discovery/tool call: PASS or RESTART_REQUIRED with exact evidence
```

- [ ] **Step 4: Commit docs if policy notes changed**

If `CLAUDE.md` or `.claude/CLAUDE.md` was updated:

```powershell
git add CLAUDE.md .claude/CLAUDE.md
git commit -m "docs: document MCP real-use verification path"
```

---

### Task 6: Full Verification and Ship Readiness

**Files:**
- No new code files unless a verification failure requires a fix.

- [ ] **Step 1: Build affected targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura
cmake --build build-trim-gui --config Release --target aura-mcp
cmake --build build-trim-gui --config Release --target cli_smoke
cmake --build build-trim-gui --config Release --target mcp_smoke
```

Expected: all builds succeed.

- [ ] **Step 2: Run focused tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure
```

Expected: both tests pass.

- [ ] **Step 3: Run existing adjacent regression tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure
ctest --test-dir build-trim-gui -C Release -R probe_engines_smoke --output-on-failure
```

Expected: both pass or skip only for documented environment reasons.

- [ ] **Step 4: Confirm git state**

Run:

```powershell
git status --short --branch
git log --oneline -5
```

Expected: working tree clean except intentional untracked local artifacts if any. No generated temp JSONL files are staged.

- [ ] **Step 5: Final commit if verification-only docs were added**

If no docs changed after Task 4, do not create an empty commit. If docs changed:

```powershell
git add CLAUDE.md .claude/CLAUDE.md
git commit -m "docs: capture MCP JSON debug workflow"
```

---

## Verification Matrix

| Area | Command | Required Result |
|---|---|---|
| CLI JSON generator | `ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure` | PASS |
| MCP real stdio | `ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure` | PASS |
| MCP unit contract | `ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure` | PASS |
| Engine probe adjacency | `ctest --test-dir build-trim-gui -C Release -R probe_engines_smoke --output-on-failure` | PASS or documented SKIP |
| Manual real-use | `Get-Content $inputFile | & $mcp` | 3 JSON-RPC response lines |
| Codex MCP registration | `codex mcp get aura` | registered stdio server |
| Subagent verification | spawned subagent or `codex exec` fresh process | AURA MCP tools visible or restart requirement documented |

## Acceptance Criteria

- `aura --compact mcp-json initialize` prints one valid JSON-RPC initialize request.
- `aura --compact mcp-json tools-list` prints one valid JSON-RPC tools/list request.
- `aura --compact mcp-json call aura_analyze --binary <path>` prints one valid JSON-RPC tools/call request.
- The JSON emitted by `aura mcp-json` can be piped directly into `aura-mcp`.
- `mcp_smoke` uses CLI-generated JSON for at least one full initialize/tools/call roundtrip.
- `codex mcp add aura` registers the built `aura-mcp.exe` with `AURA_REPO_ROOT` and `AURA_MCP_ALLOWED_ROOTS`.
- A fresh subagent or `codex exec` process confirms whether the registered AURA MCP tools are visible and callable.
- MCP protected output still omits raw string content and raw disassembly fields.
- No raw MCP tools are enabled as part of this change.

## Self-Review

- Spec coverage: covers real MCP stdio test and a CLI for inspecting transmitted JSON shape.
- Placeholder scan: no implementation step relies on "TBD" or unspecified validation.
- Type consistency: command names are consistently `mcp-json`, `initialize`, `tools-list`, and `call`.
- Risk check: the plan does not change MCP raw access policy and does not introduce HTTP transport.
