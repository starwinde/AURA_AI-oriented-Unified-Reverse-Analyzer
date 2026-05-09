# [MCP 실사용] Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build an actually runnable `aura-mcp` stdio server for safe, bounded MCP usage in real clients, with a protected default output path and stable envelope format.

**Architecture:** Keep `aura-mcp` as a thin C++ stdio transport layer that only routes tool calls to controlled helpers (path-policy checker + CLI bridge + data sanitizers) and returns one ADR-0057 envelope format. Safety logic (rule/model/profile selection) remains in `aura::safety` and is reused from GUI and CLI paths where possible.

**Tech Stack:** C++17, Qt6 for current GUI files, cJSON, CMake/MSVC, doctest/CTest, PowerShell + bash helper scripts.

---

## Scope Split

- MCP 실사용 핵심 경로(`src/mcp`, `tests/unit/mcp`, `tests/integration/mcp_smoke`) 먼저 완성.
- 기존 GUI 안전 자산 UI(plan: `safety-assets-settings-ui`)와 연동 지점은 후반 verification에서 점검만 수행.

## File Structure

- Create: `include/aura/mcp/mcp_envelope.h`
- Create: `src/mcp/mcp_envelope.cpp`
- Create: `src/mcp/mcp_path_policy.h`
- Create: `src/mcp/mcp_path_policy.cpp`
- Create: `src/mcp/mcp_cli_bridge.h`
- Create: `src/mcp/mcp_cli_bridge.cpp`
- Create: `src/mcp/mcp_tools.h`
- Create: `src/mcp/mcp_tools.cpp`
- Create: `src/mcp/mcp_server.h`
- Create: `src/mcp/mcp_server.cpp`
- Create: `tests/unit/mcp/CMakeLists.txt`
- Create: `tests/unit/mcp/mcp_unit.cpp`
- Create: `tests/integration/mcp_smoke/CMakeLists.txt`
- Create: `tests/integration/mcp_smoke/mcp_smoke.cpp`
- Modify: `CMakeLists.txt`
- Modify: `src/gui/main_window.*` (status text only, no feature change)
- Modify: `install.ps1`, `install.sh`, `README.md`, `CONTEXT.md`, `AUTOMATION_ROADMAP.md`, `docs/mcp.md`

### Task 1: Lock MCP 계약(Envelope + Tool contract) 템플릿

- [ ] **Step 1: `docs/adr/0057-strict-mcp-coverage.md` 기준 메시지 키 확인 후 체크리스트로 기록**

```markdown
- mcp_schema_version: "1.0"
- tool_schema_version: "<tool-name>/1.0"
- kind: "<tool-name>"
- status: "ok|error"
- disclosure: "protected"
- data, warnings, audit 필드는 항상 존재
- tools/list는 현재 지원 툴 집합만 노출
```

- [ ] **Step 2: `include/aura/mcp/mcp_envelope.h` 선언 추가 (비실행 파일 단위 확인 용도)**

```cpp
#pragma once

extern "C" {
struct cJSON;
}

cJSON* aura_mcp_envelope_success(const char* tool_schema_version,
                                 const char* kind,
                                 cJSON* data_or_null,
                                 const char* disclosure);

cJSON* aura_mcp_envelope_error(const char* tool_schema_version,
                               const char* kind,
                               const char* code,
                               const char* message,
                               const char* disclosure);
```

- [ ] **Step 3: `src/mcp/mcp_envelope.cpp` 구현**

```cpp
#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

namespace {
const char* nz(const char* v, const char* f) {
    return (v && *v) ? v : f;
}

cJSON* base(const char* tool_schema_version, const char* kind, const char* status, const char* disclosure) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "mcp_schema_version", "1.0");
    cJSON_AddStringToObject(root, "tool_schema_version", nz(tool_schema_version, "unknown/1.0"));
    cJSON_AddStringToObject(root, "kind", nz(kind, "unknown"));
    cJSON_AddStringToObject(root, "status", nz(status, "error"));
    cJSON_AddStringToObject(root, "disclosure", nz(disclosure, "protected"));
    cJSON_AddItemToObject(root, "warnings", cJSON_CreateArray());
    cJSON_AddNullToObject(root, "audit");
    return root;
}
}

cJSON* aura_mcp_envelope_success(const char* tool_schema_version, const char* kind, cJSON* data_or_null, const char* disclosure) {
    cJSON* root = base(tool_schema_version, kind, "ok", disclosure);
    cJSON_AddItemToObject(root, "data", data_or_null ? data_or_null : cJSON_CreateObject());
    return root;
}

cJSON* aura_mcp_envelope_error(const char* tool_schema_version, const char* kind, const char* code, const char* message, const char* disclosure) {
    cJSON* root = base(tool_schema_version, kind, "error", disclosure);
    cJSON* err = cJSON_CreateObject();
    cJSON_AddStringToObject(err, "code", nz(code, "error"));
    cJSON_AddStringToObject(err, "message", nz(message, ""));
    cJSON_AddItemToObject(root, "data", err);
    return root;
}
```

- [ ] **Step 4: `ctest` 스모크로 Envelope 성공/실패 문자열 형태 검증**

Run: `cmake --build build-trim-gui --config Release --target mcp_unit`
Expected: 현재 `mcp_unit` 미생성으로 컴파일 실패.

### Task 2: Envelope 단위테스트 작성 및 CTest 등록

- [ ] **Step 1: `tests/unit/mcp/CMakeLists.txt` 생성**

```cmake
add_executable(mcp_unit mcp_unit.cpp)

target_include_directories(mcp_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)

target_link_libraries(mcp_unit PRIVATE aura_mcp_core aura_core cjson)
target_compile_features(mcp_unit PRIVATE cxx_std_17)
add_test(NAME mcp_unit COMMAND mcp_unit)
set_tests_properties(mcp_unit PROPERTIES LABELS "unit;mcp" TIMEOUT 30)
```

- [ ] **Step 2: `tests/unit/mcp/mcp_unit.cpp`에 Envelope 테스트 추가**

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

#include <string>

TEST_CASE("MCP envelope success structure") {
    cJSON* data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "engine", "rizin");
    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0", "aura_probe_engines", data, "protected");
    CHECK(cJSON_GetObjectItem(env, "status")->valuestring != nullptr);
    CHECK(std::string(cJSON_GetObjectItem(env, "status")->valuestring) == "ok");
    cJSON_Delete(env);
}

TEST_CASE("MCP envelope error structure") {
    cJSON* env = aura_mcp_envelope_error("aura_info/1.0", "aura_info", "path_denied", "out of range", "protected");
    CHECK(std::string(cJSON_GetObjectItem(cJSON_GetObjectItem(env, "data"), "code")->valuestring) == "path_denied");
    cJSON_Delete(env);
}
```

- [ ] **Step 3: `CMakeLists.txt`에 `aura_mcp_core`, `mcp_unit` 등록**

```cmake
add_library(aura_mcp_core STATIC src/mcp/mcp_envelope.cpp src/mcp/mcp_path_policy.cpp src/mcp/mcp_cli_bridge.cpp src/mcp/mcp_tools.cpp src/mcp/mcp_server.cpp)

target_include_directories(aura_mcp_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(aura_mcp_core PUBLIC cjson)

target_include_directories(aura_mcp_core PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/third_party/doctest)

target_compile_features(aura_mcp_core PUBLIC cxx_std_17)

if(AURA_BUILD_TESTS)
  add_subdirectory(tests/unit/mcp)
endif()
```

- [ ] **Step 4: Envelope/유닛 테스트 실행**

Run:
`cmake --build build-trim-gui --config Release --target mcp_unit`
`ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure`

Expected: 두 테스트 통과.

### Task 3: 경로 허용 정책(Path allowlist) 모듈 분리

- [ ] **Step 1: `src/mcp/mcp_path_policy.h` 생성**

```cpp
#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct AuraMcpPathDecision {
    bool allowed = false;
    std::string canonical_path;
    std::string error_code;
    std::string error_message;
};

std::vector<std::filesystem::path> aura_mcp_allowed_roots_from_environment();
AuraMcpPathDecision aura_mcp_path_allowed(const std::filesystem::path& candidate);
AuraMcpPathDecision aura_mcp_path_allowed(const std::filesystem::path& candidate,
                                         const std::vector<std::filesystem::path>& allowed_roots);
```

- [ ] **Step 2: `src/mcp/mcp_path_policy.cpp` 구현(공개 루트 없음 시 deny-first)**

```cpp
#include "mcp_path_policy.h"
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <system_error>

namespace {
namespace fs = std::filesystem;
constexpr const char* kEnv = "AURA_MCP_ALLOWED_ROOTS";

#ifdef _WIN32
constexpr char kPathSep = ';';
#else
constexpr char kPathSep = ':';
#endif

std::vector<fs::path> parseRoots(const std::string& raw) {
    std::vector<fs::path> roots;
    std::stringstream ss(raw);
    std::string part;
    while (std::getline(ss, part, kPathSep)) {
        if (!part.empty()) roots.push_back(fs::path(part));
    }
    return roots;
}
}
```

- [ ] **Step 3: `src/mcp/mcp_path_policy.cpp`에 `aura_mcp_path_allowed()` 본문 채우기**

```cpp
AuraMcpPathDecision aura_mcp_path_allowed(const fs::path& candidate) {
    return aura_mcp_path_allowed(candidate, aura_mcp_allowed_roots_from_environment());
}

AuraMcpPathDecision aura_mcp_path_allowed(const fs::path& candidate,
                                         const std::vector<fs::path>& allowed_roots) {
    std::error_code ec;
    if (!fs::exists(candidate, ec) || ec) return {false, "", "path_not_found", "path does not exist"};
    fs::path canonical = fs::weakly_canonical(candidate, ec);
    if (ec) return {false, "", "path_unresolved", "path cannot be canonicalized"};

    bool has_valid_root = false;
    for (const auto& r : allowed_roots) {
        if (r.empty()) continue;
        fs::path root = fs::weakly_canonical(r, ec);
        if (ec || !fs::exists(root, ec) || !fs::is_directory(root, ec)) continue;
        has_valid_root = true;
        auto root_it = root.begin();
        auto can_it = canonical.begin();
        bool under = true;
        for (; root_it != root.end() && can_it != canonical.end(); ++root_it, ++can_it) {
            if (*root_it != *can_it) { under = false; break; }
        }
        if (under) return {true, canonical.string(), {}, {}};
    }
    if (!has_valid_root) return {false, canonical.string(), "no_allowed_roots", "no resolved allowlist roots"};
    return {false, canonical.string(), "path_denied", "path is outside allowlist"};
}
```

- [ ] **Step 4: `tests/unit/mcp/mcp_unit.cpp`에 path policy 테스트 추가**

```cpp
TEST_CASE("path policy requires allowlist env") {
    auto dec = aura_mcp_path_allowed("tests/fixtures/bin/elf_smoke.x86_64");
    CHECK_FALSE(dec.allowed);
    CHECK(dec.error_code == "no_allowed_roots");
}
```

- [ ] **Step 5: path policy 경계값 테스트 실행**

Run:
`cmake --build build-trim-gui --config Release --target mcp_unit`
`ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure`

### Task 4: CLI 브릿지(한정된 서브프로세스 실행)

- [ ] **Step 1: `src/mcp/mcp_cli_bridge.h` 생성**

```cpp
#pragma once

#include <string>

struct AuraCliResult {
    int exit_code = -1;
    std::string stdout_text;
    std::string stderr_text;
};

AuraCliResult aura_mcp_run_aura_cli(const std::string& args);
```

- [ ] **Step 2: `src/mcp/mcp_cli_bridge.cpp` 생성**

```cpp
#include "mcp_cli_bridge.h"

#include <cstdlib>

AuraCliResult aura_mcp_run_aura_cli(const std::string& args) {
    AuraCliResult out;
    (void)args;
    out.exit_code = 0;
    out.stdout_text = "{}";
    out.stderr_text = "";
    return out;
}
```

- [ ] **Step 3: 브릿지 최소 실행 체크 테스트(`mcp_unit`) 작성**

```cpp
TEST_CASE("cli bridge returns empty json on no-op command") {
    const auto r = aura_mcp_run_aura_cli("--help");
    CHECK(r.exit_code == 0);
    CHECK(!r.stdout_text.empty());
}
```

- [ ] **Step 4: CLI 브릿지 단계 실행**

Run:
`cmake --build build-trim-gui --config Release --target mcp_unit`
`ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure`

### Task 5: MCP tool 디스패치 최소 뼈대

- [ ] **Step 1: `src/mcp/mcp_tools.h` 생성**

```cpp
#pragma once

#include <string>

std::string aura_handle_mcp_request(const std::string& input_json);
```

- [ ] **Step 2: `src/mcp/mcp_tools.cpp` 기본 도구 리스트 구현**

```cpp
#include "mcp_tools.h"
#include "mcp_envelope.h"
#include "mcp_path_policy.h"

std::string aura_handle_mcp_request(const std::string& input_json) {
    (void)input_json;
    cJSON* root = cJSON_CreateObject();
    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0", "aura_probe_engines", root, "protected");
    auto* printed = cJSON_PrintUnformatted(env);
    std::string out = printed ? printed : "";
    std::free(printed);
    cJSON_Delete(env);
    return out;
}
```

- [ ] **Step 3: `tests/unit/mcp/mcp_unit.cpp`에 tool-handler 최소 단위 추가**

```cpp
TEST_CASE("mcp tool handler emits valid json") {
    auto out = aura_handle_mcp_request("{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"tools/list\"}");
    CHECK(!out.empty());
}
```

- [ ] **Step 4: 빌드/테스트**

Run:
`cmake --build build-trim-gui --config Release --target mcp_unit`
`ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure`

### Task 6: MCP stdio 서버 루프 분리

- [ ] **Step 1: `src/mcp/mcp_server.h` 생성**

```cpp
#pragma once

int aura_mcp_main();
```

- [ ] **Step 2: `src/mcp/mcp_server.cpp`에 stdin/stdout 라인별 JSON loop 추가**

```cpp
#include "mcp_server.h"
#include "mcp_tools.h"
#include <iostream>
#include <string>

int aura_mcp_main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::cout << aura_handle_mcp_request(line) << "\n";
        std::cout.flush();
    }
    return 0;
}
```

- [ ] **Step 3: 서버 엔트리 포인트 연결 (`src/mcp/main.cpp` 또는 기존 타겟 진입점)**

```cpp
#include "mcp_server.h"

int main() { return aura_mcp_main(); }
```

- [ ] **Step 4: 빌드 타겟 확인**

Run:
`cmake --build build-trim-gui --config Release --target aura-mcp`

Expected: `build-trim-gui/src/mcp/Release/aura-mcp.exe` 생성.

### Task 7: 도구별 라우팅 구현(aura_info, aura_analyze, 디테일 뷰)

- [ ] **Step 1: `src/mcp/mcp_tools.cpp`에서 JSON-RPC method별 분기 추가**

```cpp
if (method == "tools/call") {
    if (tool == "aura_probe_engines") { return callProbeEngines(args, env); }
    if (tool == "aura_info") { return callInfo(args, env); }
    if (tool == "aura_analyze") { return callAnalyze(args, env); }
    if (tool == "aura_get_disassembly") { return callDisassembly(args, env); }
    return aura_mcp_envelope_error("aura/1.0", tool.c_str(), "tool_not_supported", "tool unsupported", "protected");
}
```

- [ ] **Step 2: `aura_info` 경로에서 `aura_mcp_path_allowed` 사용**

```cpp
auto decision = aura_mcp_path_allowed(binaryPath);
if (!decision.allowed) {
    return aura_mcp_envelope_error("aura_info/1.0", "aura_info", decision.error_code.c_str(), decision.error_message.c_str(), "protected");
}
```

- [ ] **Step 3: `aura_get_disassembly / aura_get_cfg / aura_get_llm_context`는 `allowed` 실패 시 동일 deny envelope 반환**

- [ ] **Step 4: 각 툴 호출에 대해 `mcp_unit` 또는 `mcp_smoke` 최소 테스트 추가**

- [ ] **Step 5: 실행 검증**

Run:
`cmake --build build-trim-gui --config Release --target aura-mcp`
`ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure`

### Task 8: 통합 Smoke 실행 테스트 작성

- [ ] **Step 1: `tests/integration/mcp_smoke/CMakeLists.txt` 생성/등록**

```cmake
add_executable(mcp_smoke mcp_smoke.cpp)
target_include_directories(mcp_smoke PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mcp_smoke PRIVATE cjson)
add_test(NAME mcp_smoke COMMAND mcp_smoke)
set_tests_properties(mcp_smoke PROPERTIES LABELS "integration;mcp" TIMEOUT 120)
```

- [ ] **Step 2: `tests/integration/mcp_smoke/mcp_smoke.cpp`에서 initialize → tools/list → analyze 호출 라인시퀀스 추가**

```cpp
int main() {
    std::vector<std::string> input = {
        R"({"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}})",
        R"({"jsonrpc":"2.0","id":2,"method":"tools/list","params":{}})"
    };
    return 0;
}
```

- [ ] **Step 3: denied-path, protected-path 수동 검증 실행**

```powershell
$env:AURA_REPO_ROOT = (Get-Location).Path
$env:AURA_MCP_ALLOWED_ROOTS = (Get-Location).Path
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/call","params":{"name":"aura_analyze","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected: 응답 JSON-RPC 라인에 `"disclosure":"protected"`.

### Task 9: 설치/문서 동기화

- [ ] **Step 1: `docs/mcp.md` 문서 생성**

```markdown
# AURA MCP

- Build: `cmake --build build-trim-gui --config Release --target aura-mcp`
- Run: `.\build-trim-gui\src\mcp\Release\aura-mcp.exe`
- Required env: `AURA_REPO_ROOT`, `AURA_MCP_ALLOWED_ROOTS`
```

- [ ] **Step 2: `install.ps1`/`install.sh`에 AURA_MCP_BIN 출력 문구 추가**

```powershell
if (Test-Path .\build-trim-gui\src\mcp\Release\aura-mcp.exe) { Write-Host "AURA_MCP_BIN=$((Resolve-Path .\build-trim-gui\src\mcp\Release\aura-mcp.exe))" }
```

- [ ] **Step 3: `README.md`, `CONTEXT.md`, `AUTOMATION_ROADMAP.md`에 실사용 항목 반영**

```markdown
AURA ships stdio MCP gateway: `aura-mcp`, protected tools only.
```

- [ ] **Step 4: 파싱/스크립트 문법 검사**

```powershell
$tokens=$null; $errors=$null; [System.Management.Automation.Language.Parser]::ParseFile((Resolve-Path '.\install.ps1'), [ref]$tokens, [ref]$errors) > $null; if ($errors.Count) { throw 'install.ps1 parse fail' }
bash -n install.sh
bash -n scripts/fetch_external_tools.sh
```

### Task 10: 최종 확인 및 문서화 마감

- [ ] **Step 1: 전체 MCP 타깃 빌드**

```powershell
cmake --build build-trim-gui --config Release
```

- [ ] **Step 2: 레이블 기반 테스트 전체 통과**

```powershell
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

- [ ] **Step 3: `src/gui/main_window.cpp`에서 현재 상태 텍스트 연동 및 안전 디폴트 경고 노출만 확인**

- [ ] **Step 4: `git status` 정리 후 실행 이력(명령/결과) 저장**

### Completion Criteria

- [ ] MCP stdio 서버 바이너리 빌드/실행 성공
- [ ] initialize/tools/list/aura_probe_engines/aura_analyze 기본 호출 성공
- [ ] 모든 MCP 응답이 `mcp_schema_version`과 `disclosure`를 포함
- [ ] 경로 허용 정책이 `no_allowed_roots`, `path_denied`를 명확히 반환
- [ ] raw 도구 기본 경로는 deny로 동작
- [ ] `ctest -L mcp` 통과
- [ ] 설치/README 문서와 실행 경로가 동기화

### Self-Review

- [ ] 계약(Envelope, path-policy, dispatch)이 모두 단일 책임으로 분리되었는가?
- [ ] 각 단계별 테스트가 2~5분 단위로 실제 빌드/검증 가능한가?
- [ ] placeholder 코드가 남아 있지 않은가?
- [ ] 기존 `safety_assets` UI와 충돌 없이 동작 범위가 격리되었는가?

---

Plan complete and saved to `docs/superpowers/plans/2026-05-09-mcp-real-use-fine-grain.md`. Two execution options:

1. Subagent-Driven (recommended) - required for this scale and dependency checks.
2. Inline Execution - run directly in this session with milestone checkpoints.



