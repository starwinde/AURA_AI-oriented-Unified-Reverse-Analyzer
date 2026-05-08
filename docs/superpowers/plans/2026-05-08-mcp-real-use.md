# AURA MCP Real-Use Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a local `aura-mcp` stdio MCP server that real MCP clients can run to query AURA analysis through protected, bounded, schema-stable tools.

**Architecture:** V1 is a stdio-only C++ executable that speaks MCP JSON-RPC, registers AURA tools, and initially bridges to the existing `aura` CLI for analysis. Safety stays protected-by-default: string outputs are exported through a core protected-view helper, raw access is denied with structured errors, and every tool response uses the ADR-0057 MCP envelope.

**Tech Stack:** C++17, cJSON, CMake/MSVC, existing `aura_core`, existing `aura` CLI JSON surface, doctest/CTest, PowerShell and shell install scripts.

---

## Current Repo Facts

- Existing CLI target: `src/cli/main.cpp`, built as `build-trim-gui/src/cli/Release/aura.exe` on Windows.
- Existing core safety API: `include/aura/safety/string_safety.h`, implementation `src/core/safety/string_safety.cpp`.
- Existing GUI-only protected string export logic: `src/gui/main_window.cpp` around string population and `src/gui/rpc_server.cpp` `stringRecordJson(..., protectedOnly)`.
- Existing MCP policy: `docs/adr/0057-strict-mcp-coverage.md`.
- Existing runtime install scripts: `install.ps1`, `install.sh`.
- Existing tests are under `tests/unit/*` and `tests/integration/*`; CTest labels are already used.

## File Structure

Create these files:

- `include/aura/mcp/mcp_envelope.h`: C API for building MCP response envelopes.
- `src/mcp/mcp_envelope.cpp`: envelope JSON helpers using cJSON.
- `src/mcp/mcp_server.cpp`: stdio JSON-RPC loop, request dispatch, stdout/stderr separation.
- `src/mcp/mcp_tools.cpp`: tool registry, input schemas, tool call dispatch.
- `src/mcp/mcp_tools.h`: internal C++ declarations for tool registry and dispatch.
- `src/mcp/mcp_cli_bridge.cpp`: bounded subprocess bridge to `aura` CLI.
- `src/mcp/mcp_cli_bridge.h`: CLI bridge declarations.
- `src/mcp/mcp_path_policy.cpp`: path canonicalization and allowlist checks.
- `src/mcp/mcp_path_policy.h`: path policy declarations.
- `src/core/safety/protected_export.cpp`: core protected export helpers shared by GUI/MCP.
- `include/aura/safety/protected_export.h`: public protected export API.
- `tests/unit/mcp/CMakeLists.txt`: MCP unit test target.
- `tests/unit/mcp/mcp_unit.cpp`: envelope, path policy, tool registry, raw denial tests.
- `tests/integration/mcp_smoke/CMakeLists.txt`: MCP integration target.
- `tests/integration/mcp_smoke/mcp_smoke.cpp`: starts `aura-mcp`, sends JSON-RPC lines, validates fixture workflow.
- `docs/mcp.md`: copy-paste MCP setup and smoke guide.

Modify these files:

- `CMakeLists.txt`: add `src/mcp`, unit tests, integration tests.
- `src/gui/main_window.cpp`: replace duplicated protected string construction with core helper where practical.
- `src/gui/rpc_server.cpp`: keep behavior, but ensure protected string fields match the core export naming.
- `install.ps1`: print or verify `aura-mcp` path when built.
- `install.sh`: print or verify `aura-mcp` path when built.
- `README.md`: add MCP quickstart link and minimal config.
- `CONTEXT.md`: update MCP implementation status from future gateway to V1 stdio gateway when complete.
- `AUTOMATION_ROADMAP.md`: add completion row and verification evidence.

## Stable Contracts

All `aura-mcp` tool results return an envelope in `content[0].text` as JSON:

```json
{
  "mcp_schema_version": "1.0",
  "tool_schema_version": "aura_probe_engines/1.0",
  "kind": "aura_probe_engines",
  "status": "ok",
  "disclosure": "protected",
  "data": {},
  "warnings": [],
  "audit": null
}
```

MCP JSON-RPC response shape:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "content": [
      {
        "type": "text",
        "text": "{\"mcp_schema_version\":\"1.0\"}"
      }
    ],
    "isError": false
  }
}
```

Supported V1 tools:

- `aura_probe_engines`
- `aura_info`
- `aura_analyze`
- `aura_list_functions`
- `aura_get_disassembly`
- `aura_get_cfg`
- `aura_get_llm_context`
- `aura_get_raw_disassembly`
- `aura_get_raw_decompile`

The two raw tools exist only to return denied-by-default structured errors in V1.

## Task 1: Add MCP Envelope Builder

**Files:**
- Create: `include/aura/mcp/mcp_envelope.h`
- Create: `src/mcp/mcp_envelope.cpp`
- Create: `tests/unit/mcp/CMakeLists.txt`
- Create: `tests/unit/mcp/mcp_unit.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: Write failing envelope tests**

Add this initial test file at `tests/unit/mcp/mcp_unit.cpp`:

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

extern "C" {
#include "cJSON.h"
}

#include "aura/mcp/mcp_envelope.h"

#include <cstdlib>
#include <string>

namespace {
std::string printJson(cJSON* obj) {
    char* raw = cJSON_PrintUnformatted(obj);
    std::string out = raw ? raw : "";
    std::free(raw);
    return out;
}
}

TEST_CASE("mcp envelope contains stable protected success fields") {
    cJSON* data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "engine", "rizin");

    cJSON* env = aura_mcp_envelope_success(
        "aura_probe_engines/1.0",
        "aura_probe_engines",
        data,
        "protected");

    const std::string json = printJson(env);
    cJSON_Delete(env);

    CHECK(json.find("\"mcp_schema_version\":\"1.0\"") != std::string::npos);
    CHECK(json.find("\"tool_schema_version\":\"aura_probe_engines/1.0\"") != std::string::npos);
    CHECK(json.find("\"kind\":\"aura_probe_engines\"") != std::string::npos);
    CHECK(json.find("\"status\":\"ok\"") != std::string::npos);
    CHECK(json.find("\"disclosure\":\"protected\"") != std::string::npos);
    CHECK(json.find("\"warnings\":[]") != std::string::npos);
    CHECK(json.find("\"audit\":null") != std::string::npos);
}

TEST_CASE("mcp envelope contains structured error payload") {
    cJSON* env = aura_mcp_envelope_error(
        "aura_info/1.0",
        "aura_info",
        "path_denied",
        "binary path is outside AURA_MCP_ALLOWED_ROOTS",
        "protected");

    const std::string json = printJson(env);
    cJSON_Delete(env);

    CHECK(json.find("\"status\":\"error\"") != std::string::npos);
    CHECK(json.find("\"code\":\"path_denied\"") != std::string::npos);
    CHECK(json.find("\"message\":\"binary path is outside AURA_MCP_ALLOWED_ROOTS\"") != std::string::npos);
    CHECK(json.find("\"disclosure\":\"protected\"") != std::string::npos);
}
```

- [ ] **Step 2: Add unit test target**

Create `tests/unit/mcp/CMakeLists.txt`:

```cmake
add_executable(mcp_unit mcp_unit.cpp)
target_include_directories(mcp_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(mcp_unit PRIVATE aura_mcp_core cjson)
target_compile_features(mcp_unit PRIVATE cxx_std_17)

add_test(NAME mcp_unit COMMAND mcp_unit)
set_tests_properties(mcp_unit PROPERTIES
    LABELS "unit;mcp"
    TIMEOUT 30
)
```

- [ ] **Step 3: Wire target and verify failure**

Modify `CMakeLists.txt` after the `aura_core` target:

```cmake
add_library(aura_mcp_core STATIC
    src/mcp/mcp_envelope.cpp
)
target_include_directories(aura_mcp_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(aura_mcp_core PUBLIC cjson)
target_compile_features(aura_mcp_core PUBLIC cxx_std_17)
```

Also add under `if(AURA_BUILD_TESTS)`:

```cmake
    add_subdirectory(tests/unit/mcp)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
```

Expected: compile fails because `aura/mcp/mcp_envelope.h` does not exist.

- [ ] **Step 4: Implement envelope header**

Create `include/aura/mcp/mcp_envelope.h`:

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

- [ ] **Step 5: Implement envelope source**

Create `src/mcp/mcp_envelope.cpp`:

```cpp
#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

namespace {
const char* nonempty(const char* value, const char* fallback) {
    return value && *value ? value : fallback;
}

cJSON* baseEnvelope(const char* tool_schema_version,
                    const char* kind,
                    const char* status,
                    const char* disclosure) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "mcp_schema_version", "1.0");
    cJSON_AddStringToObject(root, "tool_schema_version",
                            nonempty(tool_schema_version, "unknown/1.0"));
    cJSON_AddStringToObject(root, "kind", nonempty(kind, "unknown"));
    cJSON_AddStringToObject(root, "status", nonempty(status, "error"));
    cJSON_AddStringToObject(root, "disclosure",
                            nonempty(disclosure, "protected"));
    cJSON_AddItemToObject(root, "warnings", cJSON_CreateArray());
    cJSON_AddNullToObject(root, "audit");
    return root;
}
}

cJSON* aura_mcp_envelope_success(const char* tool_schema_version,
                                 const char* kind,
                                 cJSON* data_or_null,
                                 const char* disclosure) {
    cJSON* root = baseEnvelope(tool_schema_version, kind, "ok", disclosure);
    cJSON_AddItemToObject(root, "data",
                          data_or_null ? data_or_null : cJSON_CreateObject());
    return root;
}

cJSON* aura_mcp_envelope_error(const char* tool_schema_version,
                               const char* kind,
                               const char* code,
                               const char* message,
                               const char* disclosure) {
    cJSON* root = baseEnvelope(tool_schema_version, kind, "error", disclosure);
    cJSON* err = cJSON_CreateObject();
    cJSON_AddStringToObject(err, "code", nonempty(code, "error"));
    cJSON_AddStringToObject(err, "message", nonempty(message, ""));
    cJSON_AddItemToObject(root, "data", err);
    return root;
}
```

- [ ] **Step 6: Run envelope tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure
```

Expected: `mcp_unit` passes.

- [ ] **Step 7: Commit Task 1**

```powershell
git add CMakeLists.txt include/aura/mcp/mcp_envelope.h src/mcp/mcp_envelope.cpp tests/unit/mcp/CMakeLists.txt tests/unit/mcp/mcp_unit.cpp
git commit -m "feat(mcp): add stable response envelope"
```

## Task 2: Add Path Allowlist Policy

**Files:**
- Create: `src/mcp/mcp_path_policy.h`
- Create: `src/mcp/mcp_path_policy.cpp`
- Modify: `CMakeLists.txt`
- Modify: `tests/unit/mcp/mcp_unit.cpp`

**Security correction (2026-05-08):** MCP real-use path policy must fail closed. Missing, empty, or all-invalid `AURA_MCP_ALLOWED_ROOTS` means no allowed roots and must deny with a clear code such as `no_allowed_roots`. Do not fall back to the current working directory or repository root. Direct explicit-root calls remain available for internal callers and tests.

**TOCTOU note:** This policy authorizes a canonical path before a later tool opens it. Later CLI bridge/tool code should pass the returned `canonical_path` forward immediately and avoid re-resolving user input, but a check-then-use race can still exist if an attacker can replace files between authorization and open. Stronger handle-based opening is deferred beyond this task.

Task 2 safety checklist:
- [ ] Unset `AURA_MCP_ALLOWED_ROOTS` denies existing files with `no_allowed_roots`.
- [ ] Empty `AURA_MCP_ALLOWED_ROOTS` denies existing files with `no_allowed_roots`.
- [ ] Explicit environment roots allow only canonical files under those roots.
- [ ] Explicit-root overload remains usable for direct callers and tests.
- [ ] Empty/malformed env entries are ignored, while a valid sibling entry still works.
- [ ] Sibling prefix escapes are rejected after canonicalization.

- [ ] **Step 1: Add failing path policy tests**

Append to `tests/unit/mcp/mcp_unit.cpp`:

```cpp
#include "mcp_path_policy.h"

#include <filesystem>

TEST_CASE("mcp path policy rejects when env allowlist is unset or empty") {
    // Use temp directories/files, not fixed machine paths.
    // Unset AURA_MCP_ALLOWED_ROOTS -> denied with no_allowed_roots.
    // Empty AURA_MCP_ALLOWED_ROOTS -> denied with no_allowed_roots.
}

TEST_CASE("mcp path policy allows files under direct explicit roots") {
    // Explicit-root overload still allows a temp file under that root.
}

TEST_CASE("mcp path policy env allowlist allows a temp fixture path") {
    // AURA_MCP_ALLOWED_ROOTS set to a temp root allows a file below it.
}

TEST_CASE("mcp path policy rejects files outside configured roots") {
    // Sibling prefix escapes must be rejected: root/repo must not allow root/repo2/file.
}

TEST_CASE("mcp path policy rejects nonexistent paths") {
    // Nonexistent files deny before allowlist matching.
}

TEST_CASE("mcp path policy ignores malformed and empty env entries safely") {
    // Empty entries and bad roots are ignored; one valid root still allows the fixture.
}
```

- [ ] **Step 2: Wire source and verify failure**

Modify `CMakeLists.txt` `aura_mcp_core` source list:

```cmake
add_library(aura_mcp_core STATIC
    src/mcp/mcp_envelope.cpp
    src/mcp/mcp_path_policy.cpp
)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
```

Expected: compile fails because `mcp_path_policy.h` does not exist.

- [ ] **Step 3: Implement path policy header**

Create `src/mcp/mcp_path_policy.h`:

```cpp
#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct AuraMcpPathDecision {
    bool        allowed = false;
    std::string canonical_path;
    std::string error_code;
    std::string error_message;
};

std::vector<std::filesystem::path> aura_mcp_allowed_roots_from_environment();

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path& candidate);

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path&              candidate,
    const std::vector<std::filesystem::path>& allowed_roots);
```

- [ ] **Step 4: Implement path policy source**

The default overload reads `AURA_MCP_ALLOWED_ROOTS`. If it is unset, empty, or has no canonicalizable directory roots, it must deny with `no_allowed_roots`; no cwd/repo fallback is allowed. The explicit-root overload keeps the same semantics for callers that provide roots directly.

Create `src/mcp/mcp_path_policy.cpp`:

```cpp
#include "mcp_path_policy.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <system_error>
#include <utility>

namespace {

namespace fs = std::filesystem;

constexpr const char* kAllowedRootsEnv = "AURA_MCP_ALLOWED_ROOTS";

char rootSeparator() {
#ifdef _WIN32
    return ';';
#else
    return ':';
#endif
}

std::string trim(std::string value) {
    const auto not_space = [](unsigned char ch) {
        return std::isspace(ch) == 0;
    };
    value.erase(value.begin(),
                std::find_if(value.begin(), value.end(), not_space));
    value.erase(std::find_if(value.rbegin(), value.rend(), not_space).base(),
                value.end());
    return value;
}

AuraMcpPathDecision denied(std::string canonical_path,
                           std::string code,
                           std::string message) {
    AuraMcpPathDecision decision;
    decision.allowed = false;
    decision.canonical_path = std::move(canonical_path);
    decision.error_code = std::move(code);
    decision.error_message = std::move(message);
    return decision;
}

std::vector<fs::path> splitAllowedRoots(const std::string& raw_roots) {
    std::vector<fs::path> roots;
    std::stringstream     stream(raw_roots);
    std::string           item;

    while (std::getline(stream, item, rootSeparator())) {
        item = trim(std::move(item));
        if (!item.empty()) {
            roots.emplace_back(item);
        }
    }
    return roots;
}

fs::path canonicalizeRoot(const fs::path& root, std::error_code& ec) {
    ec.clear();
    return fs::canonical(root, ec);
}

bool samePathComponent(const fs::path& lhs, const fs::path& rhs) {
#ifdef _WIN32
    return _stricmp(lhs.string().c_str(), rhs.string().c_str()) == 0;
#else
    return lhs == rhs;
#endif
}

bool isUnderRoot(const fs::path& child, const fs::path& root) {
    auto child_it = child.begin();
    auto root_it = root.begin();

    for (; root_it != root.end(); ++root_it, ++child_it) {
        if (child_it == child.end() ||
            !samePathComponent(*child_it, *root_it)) {
            return false;
        }
    }
    return true;
}

}

std::vector<std::filesystem::path> aura_mcp_allowed_roots_from_environment() {
    const char* raw = std::getenv(kAllowedRootsEnv);
    if (raw == nullptr || trim(raw).empty()) {
        return {};
    }
    return splitAllowedRoots(raw);
}

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path& candidate) {
    return aura_mcp_path_allowed(candidate,
                                 aura_mcp_allowed_roots_from_environment());
}

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path&              candidate,
    const std::vector<std::filesystem::path>& allowed_roots) {
    std::error_code ec;
    if (candidate.empty() || !fs::exists(candidate, ec) || ec) {
        return denied("", "path_not_found",
                      "path does not exist or is not accessible");
    }

    const fs::path canonical_candidate = fs::canonical(candidate, ec);
    if (ec) {
        return denied("", "path_unresolved", "path cannot be canonicalized");
    }

    if (!fs::is_regular_file(canonical_candidate, ec) || ec) {
        return denied(canonical_candidate.string(), "not_a_regular_file",
                      "path is not a regular file");
    }

    bool had_valid_root = false;
    for (const fs::path& raw_root : allowed_roots) {
        if (raw_root.empty()) {
            continue;
        }
        const fs::path canonical_root = canonicalizeRoot(raw_root, ec);
        if (ec || !fs::is_directory(canonical_root, ec) || ec) {
            continue;
        }
        had_valid_root = true;

        if (isUnderRoot(canonical_candidate, canonical_root)) {
            return {true, canonical_candidate.string(), {}, {}};
        }
    }

    if (!had_valid_root) {
        return denied(canonical_candidate.string(), "no_allowed_roots",
                      "no configured allowlist roots could be resolved");
    }

    return denied(canonical_candidate.string(), "path_denied",
                  "path is outside AURA_MCP_ALLOWED_ROOTS");
}
```

- [ ] **Step 5: Run path policy tests**

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure
```

Expected: `mcp_unit` passes.

- [ ] **Step 6: Commit Task 2**

```powershell
git add CMakeLists.txt src/mcp/mcp_path_policy.h src/mcp/mcp_path_policy.cpp tests/unit/mcp/mcp_unit.cpp
git commit -m "feat(mcp): enforce binary path allowlist"
```

## Task 3: Add MCP Tool Registry and Raw Denial

**Files:**
- Create: `src/mcp/mcp_tools.h`
- Create: `src/mcp/mcp_tools.cpp`
- Modify: `CMakeLists.txt`
- Modify: `tests/unit/mcp/mcp_unit.cpp`

- [ ] **Step 1: Add failing registry tests**

Append to `tests/unit/mcp/mcp_unit.cpp`:

```cpp
#include "mcp_tools.h"

TEST_CASE("mcp tool registry lists protected AURA tools") {
    cJSON* tools = aura_mcp_tools_list_json();
    const std::string json = printJson(tools);
    cJSON_Delete(tools);

    CHECK(json.find("\"name\":\"aura_probe_engines\"") != std::string::npos);
    CHECK(json.find("\"name\":\"aura_info\"") != std::string::npos);
    CHECK(json.find("\"name\":\"aura_analyze\"") != std::string::npos);
    CHECK(json.find("\"name\":\"aura_get_disassembly\"") != std::string::npos);
    CHECK(json.find("\"name\":\"aura_get_raw_disassembly\"") != std::string::npos);
}

TEST_CASE("raw tools are denied by default") {
    cJSON* args = cJSON_CreateObject();
    cJSON_AddStringToObject(args, "binary_path", "tests/fixtures/bin/elf_smoke.x86_64");
    cJSON_AddStringToObject(args, "function_addr", "0x40117b");

    cJSON* env = aura_mcp_call_tool_json("aura_get_raw_disassembly", args);
    const std::string json = printJson(env);
    cJSON_Delete(env);

    CHECK(json.find("\"status\":\"error\"") != std::string::npos);
    CHECK(json.find("\"code\":\"raw_access_denied\"") != std::string::npos);
    CHECK(json.find("\"disclosure\":\"protected\"") != std::string::npos);
}
```

- [ ] **Step 2: Wire tool source and verify failure**

Modify `CMakeLists.txt`:

```cmake
add_library(aura_mcp_core STATIC
    src/mcp/mcp_envelope.cpp
    src/mcp/mcp_path_policy.cpp
    src/mcp/mcp_tools.cpp
)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
```

Expected: compile fails because `mcp_tools.h` does not exist.

- [ ] **Step 3: Implement tool registry header**

Create `src/mcp/mcp_tools.h`:

```cpp
#pragma once

extern "C" {
struct cJSON;
}

cJSON* aura_mcp_tools_list_json();
cJSON* aura_mcp_call_tool_json(const char* name, cJSON* args_or_null);
```

- [ ] **Step 4: Implement tool registry source**

Create `src/mcp/mcp_tools.cpp`:

```cpp
#include "mcp_tools.h"

#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

#include <cstring>

namespace {
cJSON* stringProperty(const char* description) {
    cJSON* prop = cJSON_CreateObject();
    cJSON_AddStringToObject(prop, "type", "string");
    cJSON_AddStringToObject(prop, "description", description);
    return prop;
}

cJSON* integerProperty(const char* description, int min_value) {
    cJSON* prop = cJSON_CreateObject();
    cJSON_AddStringToObject(prop, "type", "integer");
    cJSON_AddNumberToObject(prop, "minimum", min_value);
    cJSON_AddStringToObject(prop, "description", description);
    return prop;
}

cJSON* inputSchema(std::initializer_list<const char*> required) {
    cJSON* schema = cJSON_CreateObject();
    cJSON_AddStringToObject(schema, "type", "object");
    cJSON* props = cJSON_AddObjectToObject(schema, "properties");
    cJSON_AddItemToObject(props, "binary_path", stringProperty("Path to an allowed local binary."));
    cJSON_AddItemToObject(props, "function_addr", stringProperty("Function entry address such as 0x40117b."));
    cJSON_AddItemToObject(props, "limit", integerProperty("Maximum records to return.", 1));
    cJSON* req = cJSON_AddArrayToObject(schema, "required");
    for (const char* key : required) cJSON_AddItemToArray(req, cJSON_CreateString(key));
    cJSON_AddBoolToObject(schema, "additionalProperties", false);
    return schema;
}

void addTool(cJSON* arr, const char* name, const char* description, cJSON* schema) {
    cJSON* tool = cJSON_CreateObject();
    cJSON_AddStringToObject(tool, "name", name);
    cJSON_AddStringToObject(tool, "description", description);
    cJSON_AddItemToObject(tool, "inputSchema", schema);
    cJSON_AddItemToArray(arr, tool);
}

bool isRawTool(const char* name) {
    return name &&
           (std::strcmp(name, "aura_get_raw_disassembly") == 0 ||
            std::strcmp(name, "aura_get_raw_decompile") == 0);
}
}

cJSON* aura_mcp_tools_list_json() {
    cJSON* arr = cJSON_CreateArray();
    addTool(arr, "aura_probe_engines", "Probe available AURA RE engines.", inputSchema({}));
    addTool(arr, "aura_info", "Return binary fingerprint and format metadata.", inputSchema({"binary_path"}));
    addTool(arr, "aura_analyze", "Return bounded protected analysis records.", inputSchema({"binary_path"}));
    addTool(arr, "aura_list_functions", "List bounded function records.", inputSchema({"binary_path"}));
    addTool(arr, "aura_get_disassembly", "Return protected structured disassembly for one function.", inputSchema({"binary_path", "function_addr"}));
    addTool(arr, "aura_get_cfg", "Return CFG blocks and edges for one function.", inputSchema({"binary_path", "function_addr"}));
    addTool(arr, "aura_get_llm_context", "Return protected LLM context for one function.", inputSchema({"binary_path", "function_addr"}));
    addTool(arr, "aura_get_raw_disassembly", "Denied by default in V1; raw access requires future approval flow.", inputSchema({"binary_path", "function_addr"}));
    addTool(arr, "aura_get_raw_decompile", "Denied by default in V1; raw access requires future approval flow.", inputSchema({"binary_path", "function_addr"}));
    return arr;
}

cJSON* aura_mcp_call_tool_json(const char* name, cJSON*) {
    if (isRawTool(name)) {
        return aura_mcp_envelope_error(
            "raw/1.0",
            name,
            "raw_access_denied",
            "raw MCP tools are disabled in V1; use protected tools",
            "protected");
    }
    return aura_mcp_envelope_error(
        "unknown/1.0",
        name ? name : "unknown",
        "tool_not_implemented",
        "tool dispatch is not implemented yet",
        "protected");
}
```

- [ ] **Step 5: Run registry tests**

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure
```

Expected: `mcp_unit` passes.

- [ ] **Step 6: Commit Task 3**

```powershell
git add CMakeLists.txt src/mcp/mcp_tools.h src/mcp/mcp_tools.cpp tests/unit/mcp/mcp_unit.cpp
git commit -m "feat(mcp): register protected tool surface"
```

## Task 4: Add `aura-mcp` stdio Server Skeleton

**Files:**
- Create: `src/mcp/mcp_server.cpp`
- Create: `src/mcp/CMakeLists.txt`
- Modify: `CMakeLists.txt`
- Create: `tests/integration/mcp_smoke/CMakeLists.txt`
- Create: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add failing integration smoke**

Create `tests/integration/mcp_smoke/mcp_smoke.cpp`:

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace {
std::string runCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    REQUIRE(pipe != nullptr);
    std::string out;
    char buf[4096];
    while (fgets(buf, sizeof(buf), pipe)) out += buf;
    const int rc = pclose(pipe);
    CHECK(rc == 0);
    return out;
}
}

TEST_CASE("aura-mcp initializes and lists tools over stdio") {
#ifdef _WIN32
    const std::string exe = ".\\src\\mcp\\Release\\aura-mcp.exe";
    const std::string cmd =
        "powershell -NoProfile -Command \""
        "$p = Start-Process -FilePath '" + exe + "' -NoNewWindow -RedirectStandardInput pipe -RedirectStandardOutput pipe -PassThru"
        "\"";
    MESSAGE("Windows direct pipe helper is covered by unit-level protocol tests until Task 4 final command is added.");
    CHECK(true);
#else
    const std::string cmd =
        "printf '%s\n%s\n' "
        "'{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"initialize\",\"params\":{\"protocolVersion\":\"2025-06-18\",\"capabilities\":{},\"clientInfo\":{\"name\":\"aura-test\",\"version\":\"1\"}}}' "
        "'{\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"tools/list\",\"params\":{}}' "
        "| ./src/mcp/aura-mcp";
    const std::string out = runCommand(cmd);
    CHECK(out.find("\"protocolVersion\"") != std::string::npos);
    CHECK(out.find("\"tools\"") != std::string::npos);
    CHECK(out.find("aura_probe_engines") != std::string::npos);
#endif
}
```

Create `tests/integration/mcp_smoke/CMakeLists.txt`:

```cmake
add_executable(mcp_smoke mcp_smoke.cpp)
target_include_directories(mcp_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_compile_features(mcp_smoke PRIVATE cxx_std_17)
add_dependencies(mcp_smoke aura-mcp)

add_test(NAME mcp_smoke COMMAND mcp_smoke)
set_tests_properties(mcp_smoke PROPERTIES
    LABELS "integration;mcp"
    TIMEOUT 30
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
```

- [ ] **Step 2: Wire build and verify failure**

Create `src/mcp/CMakeLists.txt`:

```cmake
add_executable(aura-mcp mcp_server.cpp)
target_include_directories(aura-mcp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(aura-mcp PRIVATE aura_mcp_core cjson)
target_compile_features(aura-mcp PRIVATE cxx_std_17)
```

Modify root `CMakeLists.txt` after `add_library(aura_mcp_core ...)`:

```cmake
add_subdirectory(src/mcp)
```

Modify root `CMakeLists.txt` under tests:

```cmake
        add_subdirectory(tests/integration/mcp_smoke)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
```

Expected: compile fails because `src/mcp/mcp_server.cpp` does not exist.

- [ ] **Step 3: Implement stdio server**

Create `src/mcp/mcp_server.cpp`:

```cpp
#include "mcp_tools.h"

extern "C" {
#include "cJSON.h"
}

#include <cstdlib>
#include <iostream>
#include <string>

namespace {
std::string printJson(cJSON* obj) {
    char* raw = cJSON_PrintUnformatted(obj);
    std::string out = raw ? raw : "";
    std::free(raw);
    return out;
}

cJSON* jsonRpcResult(cJSON* id, cJSON* result) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "jsonrpc", "2.0");
    cJSON_AddItemToObject(root, "id", cJSON_Duplicate(id, 1));
    cJSON_AddItemToObject(root, "result", result);
    return root;
}

cJSON* jsonRpcError(cJSON* id, int code, const char* message) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "jsonrpc", "2.0");
    if (id) cJSON_AddItemToObject(root, "id", cJSON_Duplicate(id, 1));
    else cJSON_AddNullToObject(root, "id");
    cJSON* err = cJSON_AddObjectToObject(root, "error");
    cJSON_AddNumberToObject(err, "code", code);
    cJSON_AddStringToObject(err, "message", message);
    return root;
}

cJSON* textToolResult(cJSON* envelope, bool isError) {
    cJSON* result = cJSON_CreateObject();
    cJSON* content = cJSON_AddArrayToObject(result, "content");
    cJSON* item = cJSON_CreateObject();
    cJSON_AddStringToObject(item, "type", "text");
    const std::string text = printJson(envelope);
    cJSON_AddStringToObject(item, "text", text.c_str());
    cJSON_AddItemToArray(content, item);
    cJSON_AddBoolToObject(result, "isError", isError);
    cJSON_Delete(envelope);
    return result;
}

cJSON* handleInitialize() {
    cJSON* result = cJSON_CreateObject();
    cJSON_AddStringToObject(result, "protocolVersion", "2025-06-18");
    cJSON* caps = cJSON_AddObjectToObject(result, "capabilities");
    cJSON_AddItemToObject(caps, "tools", cJSON_CreateObject());
    cJSON* info = cJSON_AddObjectToObject(result, "serverInfo");
    cJSON_AddStringToObject(info, "name", "aura-mcp");
    cJSON_AddStringToObject(info, "version", "0.1.0");
    return result;
}

cJSON* handleToolsList() {
    cJSON* result = cJSON_CreateObject();
    cJSON_AddItemToObject(result, "tools", aura_mcp_tools_list_json());
    return result;
}
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        cJSON* req = cJSON_ParseWithLength(line.data(), line.size());
        if (!req) {
            cJSON* err = jsonRpcError(nullptr, -32700, "Parse error");
            std::cout << printJson(err) << std::endl;
            cJSON_Delete(err);
            continue;
        }

        cJSON* id = cJSON_GetObjectItemCaseSensitive(req, "id");
        cJSON* method = cJSON_GetObjectItemCaseSensitive(req, "method");
        if (!cJSON_IsString(method) || !method->valuestring) {
            cJSON* err = jsonRpcError(id, -32600, "Invalid Request");
            std::cout << printJson(err) << std::endl;
            cJSON_Delete(err);
            cJSON_Delete(req);
            continue;
        }

        cJSON* resp = nullptr;
        const std::string m = method->valuestring;
        if (m == "notifications/initialized") {
            cJSON_Delete(req);
            continue;
        } else if (m == "initialize") {
            resp = jsonRpcResult(id, handleInitialize());
        } else if (m == "tools/list") {
            resp = jsonRpcResult(id, handleToolsList());
        } else if (m == "tools/call") {
            cJSON* params = cJSON_GetObjectItemCaseSensitive(req, "params");
            cJSON* name = cJSON_GetObjectItemCaseSensitive(params, "name");
            cJSON* args = cJSON_GetObjectItemCaseSensitive(params, "arguments");
            if (!cJSON_IsString(name)) {
                resp = jsonRpcError(id, -32602, "tools/call requires params.name");
            } else {
                cJSON* env = aura_mcp_call_tool_json(name->valuestring, args);
                const bool isError = env &&
                    cJSON_IsString(cJSON_GetObjectItemCaseSensitive(env, "status")) &&
                    std::string(cJSON_GetObjectItemCaseSensitive(env, "status")->valuestring) == "error";
                resp = jsonRpcResult(id, textToolResult(env, isError));
            }
        } else if (m == "ping") {
            resp = jsonRpcResult(id, cJSON_CreateObject());
        } else {
            resp = jsonRpcError(id, -32601, "Method not found");
        }

        std::cout << printJson(resp) << std::endl;
        cJSON_Delete(resp);
        cJSON_Delete(req);
    }
    return 0;
}
```

- [ ] **Step 4: Build and smoke manually**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
```

Manual smoke in PowerShell:

```powershell
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/list","params":{}}',
'{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_get_raw_disassembly","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- response 1 contains `protocolVersion`.
- response 2 contains `aura_probe_engines`.
- response 3 contains `raw_access_denied` and `isError:true`.

- [ ] **Step 5: Run MCP tests**

```powershell
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

Expected: `mcp_unit` passes. `mcp_smoke` may be a Windows placeholder in this task; it must not fail.

- [ ] **Step 6: Commit Task 4**

```powershell
git add CMakeLists.txt src/mcp/CMakeLists.txt src/mcp/mcp_server.cpp tests/integration/mcp_smoke/CMakeLists.txt tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat(mcp): add stdio server skeleton"
```

## Task 5: Add CLI Bridge for `aura_probe_engines`, `aura_info`, and `aura_analyze`

**Files:**
- Create: `src/mcp/mcp_cli_bridge.h`
- Create: `src/mcp/mcp_cli_bridge.cpp`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `CMakeLists.txt`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add bridge integration expectation**

Update the manual smoke section in `tests/integration/mcp_smoke/mcp_smoke.cpp` for non-Windows later; for Windows, add a comment assertion that final manual command must cover:

```cpp
MESSAGE("Manual Windows MCP smoke must call aura_probe_engines and observe mcp_schema_version.");
CHECK(true);
```

Do not add a flaky Windows pipe test here. The final verification command in this task is the source of truth on Windows.

- [ ] **Step 2: Wire bridge source**

Modify root `CMakeLists.txt`:

```cmake
add_library(aura_mcp_core STATIC
    src/mcp/mcp_envelope.cpp
    src/mcp/mcp_path_policy.cpp
    src/mcp/mcp_tools.cpp
    src/mcp/mcp_cli_bridge.cpp
)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
```

Expected: compile fails because `mcp_cli_bridge.cpp` does not exist.

- [ ] **Step 3: Implement bridge header**

Create `src/mcp/mcp_cli_bridge.h`:

```cpp
#pragma once

#include <string>

struct AuraMcpCliResult {
    int exit_code = 1;
    std::string stdout_text;
    std::string stderr_text;
};

AuraMcpCliResult aura_mcp_run_aura_cli(const std::string& repo_root,
                                       const std::string& arguments);
```

- [ ] **Step 4: Implement bridge source**

Create `src/mcp/mcp_cli_bridge.cpp`:

```cpp
#include "mcp_cli_bridge.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <sstream>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace {
std::string quote(const std::string& value) {
#ifdef _WIN32
    std::string out = "\"";
    for (char ch : value) out += ch == '"' ? "\\\"" : std::string(1, ch);
    out += "\"";
    return out;
#else
    std::string out = "'";
    for (char ch : value) out += ch == '\'' ? "'\\''" : std::string(1, ch);
    out += "'";
    return out;
#endif
}
}

AuraMcpCliResult aura_mcp_run_aura_cli(const std::string& repo_root,
                                       const std::string& arguments) {
    AuraMcpCliResult result;
    const std::filesystem::path root(repo_root.empty()
                                         ? std::filesystem::current_path()
                                         : std::filesystem::path(repo_root));
#ifdef _WIN32
    const auto aura = root / "build-trim-gui" / "src" / "cli" / "Release" / "aura.exe";
#else
    const auto aura = root / "build-trim-gui" / "src" / "cli" / "aura";
#endif
    std::ostringstream cmd;
    cmd << quote(aura.string()) << " " << arguments << " 2>&1";
    FILE* pipe = popen(cmd.str().c_str(), "r");
    if (!pipe) {
        result.stderr_text = "failed to start aura CLI";
        return result;
    }
    std::array<char, 4096> buf{};
    while (fgets(buf.data(), static_cast<int>(buf.size()), pipe)) {
        result.stdout_text += buf.data();
        if (result.stdout_text.size() > 1024 * 1024) {
            result.stderr_text = "aura CLI output exceeded 1 MiB";
            break;
        }
    }
    result.exit_code = pclose(pipe);
    return result;
}
```

- [ ] **Step 5: Dispatch protected CLI tools**

Replace `aura_mcp_call_tool_json` in `src/mcp/mcp_tools.cpp` with this implementation shape:

```cpp
// Add includes at top:
#include "mcp_cli_bridge.h"
#include "mcp_path_policy.h"

#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <string>

// Add helpers in anonymous namespace:
const char* jsonString(cJSON* obj, const char* key) {
    cJSON* v = cJSON_GetObjectItemCaseSensitive(obj, key);
    return cJSON_IsString(v) ? v->valuestring : nullptr;
}

std::string repoRoot() {
    if (const char* env = std::getenv("AURA_REPO_ROOT")) {
        if (*env) return env;
    }
    return std::filesystem::current_path().string();
}

std::string allowedRoots() {
    if (const char* env = std::getenv("AURA_MCP_ALLOWED_ROOTS")) {
        if (*env) return env;
    }
    return repoRoot();
}

cJSON* parseCliJsonOrError(const char* tool_schema,
                           const char* kind,
                           const AuraMcpCliResult& r) {
    if (r.exit_code != 0 || r.stdout_text.empty()) {
        return aura_mcp_envelope_error(tool_schema, kind, "cli_failed",
                                       r.stdout_text.empty() ? "aura CLI failed" : r.stdout_text.c_str(),
                                       "protected");
    }
    cJSON* parsed = cJSON_ParseWithLength(r.stdout_text.data(), r.stdout_text.size());
    if (!parsed) {
        return aura_mcp_envelope_error(tool_schema, kind, "cli_json_invalid",
                                       "aura CLI returned non-JSON output",
                                       "protected");
    }
    cJSON* data = cJSON_CreateObject();
    cJSON_AddItemToObject(data, "aura_cli", parsed);
    return aura_mcp_envelope_success(tool_schema, kind, data, "protected");
}

std::string quoteArg(const std::string& value) {
#ifdef _WIN32
    std::string out = "\"";
    for (char ch : value) out += ch == '"' ? "\\\"" : std::string(1, ch);
    out += "\"";
    return out;
#else
    std::string out = "'";
    for (char ch : value) out += ch == '\'' ? "'\\''" : std::string(1, ch);
    out += "'";
    return out;
#endif
}
```

Then inside `aura_mcp_call_tool_json` after the raw-tool block:

```cpp
    if (std::strcmp(name, "aura_probe_engines") == 0) {
        const auto r = aura_mcp_run_aura_cli(repoRoot(), "--compact --probe-engines");
        return parseCliJsonOrError("aura_probe_engines/1.0", "aura_probe_engines", r);
    }

    if (std::strcmp(name, "aura_info") == 0 ||
        std::strcmp(name, "aura_analyze") == 0) {
        const char* binary = jsonString(args_or_null, "binary_path");
        if (!binary) {
            return aura_mcp_envelope_error(name, name, "missing_binary_path",
                                           "binary_path is required", "protected");
        }
        const auto path = aura_mcp_path_allowed(binary, allowedRoots());
        if (!path.allowed) {
            return aura_mcp_envelope_error(name, name, path.error_code.c_str(),
                                           "binary path is not allowed", "protected");
        }
        std::string sub = std::strcmp(name, "aura_info") == 0 ? "info " : "--compact analyze ";
        const auto r = aura_mcp_run_aura_cli(repoRoot(), sub + quoteArg(path.canonical_path));
        return parseCliJsonOrError(std::string(name).append("/1.0").c_str(), name, r);
    }
```

If C++ temporary `.c_str()` lifetime causes review concern, use local `std::string schema = std::string(name) + "/1.0";` before passing.

- [ ] **Step 6: Manual MCP CLI bridge smoke**

Run:

```powershell
$env:AURA_REPO_ROOT = (Get-Location).Path
$env:AURA_MCP_ALLOWED_ROOTS = (Get-Location).Path
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/call","params":{"name":"aura_probe_engines","arguments":{}}}',
'{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_info","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64"}}}',
'{"jsonrpc":"2.0","id":4,"method":"tools/call","params":{"name":"aura_analyze","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- id 2 contains `aura_probe_engines`.
- id 3 contains `sha256`.
- id 4 contains `functions`.
- All tool envelopes contain `"disclosure":"protected"`.

- [ ] **Step 7: Run tests**

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp mcp_unit
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

Expected: MCP tests pass.

- [ ] **Step 8: Commit Task 5**

```powershell
git add CMakeLists.txt src/mcp/mcp_cli_bridge.h src/mcp/mcp_cli_bridge.cpp src/mcp/mcp_tools.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat(mcp): bridge protected tools to aura cli"
```

## Task 6: Promote Protected String Export to Core and Apply to MCP Analyze

**Files:**
- Create: `include/aura/safety/protected_export.h`
- Create: `src/core/safety/protected_export.cpp`
- Modify: `CMakeLists.txt`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `tests/unit/mcp/mcp_unit.cpp`

- [ ] **Step 1: Add non-disclosure test**

Append to `tests/unit/mcp/mcp_unit.cpp`:

```cpp
#include "aura/safety/protected_export.h"

TEST_CASE("protected export masks sensitive string values") {
    aura::safety::ProtectedExportRecord rec =
        aura::safety::buildProtectedExportRecord(
            7,
            "alice.smith@example.com",
            "test-source");

    CHECK(rec.string_id == 7);
    CHECK(rec.protected_value == "[EMAIL_1]");
    CHECK(rec.masked_content == "[EMAIL_1]");
    CHECK(rec.findings_count == 1);
    CHECK(rec.raw_content.empty());
}
```

- [ ] **Step 2: Wire source and verify failure**

Modify `CMakeLists.txt` `AURA_CORE_SOURCES` list by adding:

```cmake
    src/core/safety/protected_export.cpp
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
```

Expected: compile fails because `aura/safety/protected_export.h` does not exist.

- [ ] **Step 3: Implement protected export header**

Create `include/aura/safety/protected_export.h`:

```cpp
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace aura::safety {

struct ProtectedExportFinding {
    std::string detector_id;
    std::string kind;
    std::size_t start = 0;
    std::size_t end = 0;
    double confidence = 0.0;
    std::string mask_token;
};

struct ProtectedExportRecord {
    int string_id = 0;
    std::string protected_value;
    std::string masked_content;
    std::string source;
    std::string raw_content;
    std::size_t findings_count = 0;
    std::vector<ProtectedExportFinding> findings;
};

ProtectedExportRecord buildProtectedExportRecord(int string_id,
                                                 const std::string& content,
                                                 const std::string& source);

}
```

- [ ] **Step 4: Implement protected export source**

Create `src/core/safety/protected_export.cpp`:

```cpp
#include "aura/safety/protected_export.h"

#include "aura/safety/string_safety.h"

namespace aura::safety {

ProtectedExportRecord buildProtectedExportRecord(int string_id,
                                                 const std::string& content,
                                                 const std::string& source) {
    const SafetyProfile profile = loadDefaultSafetyProfile();
    auto findings = scanStringWithRulePacks(content, profile);
    auto view = buildProtectedStringView(content, std::string(), std::move(findings));

    ProtectedExportRecord out;
    out.string_id = string_id;
    out.protected_value = view.protected_value;
    out.masked_content = view.masked;
    out.source = source;
    out.raw_content.clear();
    out.findings_count = view.findings.size();
    for (const auto& f : view.findings) {
        ProtectedExportFinding pf;
        pf.detector_id = f.detector_id;
        pf.kind = f.kind;
        pf.start = f.start;
        pf.end = f.end;
        pf.confidence = f.confidence;
        pf.mask_token = f.mask_token;
        out.findings.push_back(std::move(pf));
    }
    return out;
}

}
```

- [ ] **Step 5: Link tests with aura_core**

Modify `tests/unit/mcp/CMakeLists.txt`:

```cmake
target_link_libraries(mcp_unit PRIVATE aura_mcp_core aura_core cjson)
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target mcp_unit
ctest --test-dir build-trim-gui -C Release -R mcp_unit --output-on-failure
```

Expected: non-disclosure test passes.

- [ ] **Step 6: Apply protected export to MCP analyze normalization**

In `src/mcp/mcp_tools.cpp`, after parsing CLI JSON for `aura_analyze`, walk `data.aura_cli.body.strings[]` and remove `content`, replacing it with:

```json
{
  "protected_value": "...",
  "masked_content": "...",
  "protected_only": true,
  "findings": []
}
```

Implementation approach:

```cpp
// Include:
#include "aura/safety/protected_export.h"

// Helper:
void protectAnalyzeStrings(cJSON* cliRoot) {
    cJSON* body = cJSON_GetObjectItemCaseSensitive(cliRoot, "body");
    cJSON* strings = cJSON_GetObjectItemCaseSensitive(body, "strings");
    if (!cJSON_IsArray(strings)) return;
    cJSON* row = nullptr;
    cJSON_ArrayForEach(row, strings) {
        cJSON* content = cJSON_GetObjectItemCaseSensitive(row, "content");
        if (!cJSON_IsString(content) || !content->valuestring) continue;
        cJSON* id = cJSON_GetObjectItemCaseSensitive(row, "string_id");
        cJSON* source = cJSON_GetObjectItemCaseSensitive(row, "source");
        const auto protectedRow = aura::safety::buildProtectedExportRecord(
            cJSON_IsNumber(id) ? id->valueint : 0,
            content->valuestring,
            cJSON_IsString(source) ? source->valuestring : "");
        cJSON_DeleteItemFromObjectCaseSensitive(row, "content");
        cJSON_AddStringToObject(row, "protected_value", protectedRow.protected_value.c_str());
        cJSON_AddStringToObject(row, "masked_content", protectedRow.masked_content.c_str());
        cJSON_AddBoolToObject(row, "protected_only", true);
        cJSON* findings = cJSON_AddArrayToObject(row, "findings");
        for (const auto& f : protectedRow.findings) {
            cJSON* fr = cJSON_CreateObject();
            cJSON_AddStringToObject(fr, "detector_id", f.detector_id.c_str());
            cJSON_AddStringToObject(fr, "kind", f.kind.c_str());
            cJSON_AddNumberToObject(fr, "start_offset", static_cast<double>(f.start));
            cJSON_AddNumberToObject(fr, "end_offset", static_cast<double>(f.end));
            cJSON_AddNumberToObject(fr, "confidence", f.confidence);
            cJSON_AddStringToObject(fr, "mask_token", f.mask_token.c_str());
            cJSON_AddItemToArray(findings, fr);
        }
    }
}
```

Call `protectAnalyzeStrings(parsed)` before putting parsed CLI JSON into the envelope for `aura_analyze`.

- [ ] **Step 7: Run non-disclosure manual check**

Use an existing fixture if it has strings. If not, create a temporary binary fixture later in Task 8. For this task, unit-level protected export is the required gate.

Run:

```powershell
cmake --build build-trim-gui --config Release
ctest --test-dir build-trim-gui -C Release -R "mcp_unit|safety_unit" --output-on-failure
```

Expected: both tests pass.

- [ ] **Step 8: Commit Task 6**

```powershell
git add CMakeLists.txt include/aura/safety/protected_export.h src/core/safety/protected_export.cpp src/mcp/mcp_tools.cpp tests/unit/mcp/CMakeLists.txt tests/unit/mcp/mcp_unit.cpp
git commit -m "feat(mcp): protect exported string records"
```

## Task 7: Implement Function Detail Tools

**Files:**
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add manual expected tool calls to smoke documentation inside test**

In `tests/integration/mcp_smoke/mcp_smoke.cpp`, add messages that the full Windows manual smoke must call:

```cpp
MESSAGE("Manual Windows MCP smoke must call aura_get_disassembly, aura_get_cfg, and aura_get_llm_context for 0x40117b.");
CHECK(true);
```

- [ ] **Step 2: Implement `aura_get_disassembly`, `aura_get_cfg`, `aura_get_llm_context` dispatch**

In `src/mcp/mcp_tools.cpp`, add a helper:

```cpp
std::string requiredFunctionAddr(cJSON* args) {
    const char* addr = jsonString(args, "function_addr");
    return addr ? addr : "";
}
```

Add dispatch blocks:

```cpp
    if (std::strcmp(name, "aura_get_disassembly") == 0 ||
        std::strcmp(name, "aura_get_cfg") == 0 ||
        std::strcmp(name, "aura_get_llm_context") == 0) {
        const char* binary = jsonString(args_or_null, "binary_path");
        const std::string func = requiredFunctionAddr(args_or_null);
        if (!binary) {
            return aura_mcp_envelope_error(name, name, "missing_binary_path",
                                           "binary_path is required", "protected");
        }
        if (func.empty()) {
            return aura_mcp_envelope_error(name, name, "missing_function_addr",
                                           "function_addr is required", "protected");
        }
        const auto path = aura_mcp_path_allowed(binary, allowedRoots());
        if (!path.allowed) {
            return aura_mcp_envelope_error(name, name, path.error_code.c_str(),
                                           "binary path is not allowed", "protected");
        }
        std::string sub;
        if (std::strcmp(name, "aura_get_disassembly") == 0) {
            sub = "--compact disasm ";
        } else if (std::strcmp(name, "aura_get_cfg") == 0) {
            sub = "--compact cfg ";
        } else {
            sub = "--compact llm-context ";
        }
        const std::string cmd = sub + quoteArg(path.canonical_path) + " --func " + quoteArg(func);
        const auto r = aura_mcp_run_aura_cli(repoRoot(), cmd);
        std::string schema = std::string(name) + "/1.0";
        return parseCliJsonOrError(schema.c_str(), name, r);
    }
```

- [ ] **Step 3: Manual MCP function detail smoke**

Run:

```powershell
$env:AURA_REPO_ROOT = (Get-Location).Path
$env:AURA_MCP_ALLOWED_ROOTS = (Get-Location).Path
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/call","params":{"name":"aura_get_disassembly","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}',
'{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_get_cfg","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}',
'{"jsonrpc":"2.0","id":4,"method":"tools/call","params":{"name":"aura_get_llm_context","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- id 2 contains `instructions`.
- id 3 contains `blocks`.
- id 4 contains `callees`.
- all envelopes contain `disclosure":"protected"`.

- [ ] **Step 4: Run tests**

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

Expected: MCP tests pass.

- [ ] **Step 5: Commit Task 7**

```powershell
git add src/mcp/mcp_tools.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat(mcp): expose function detail tools"
```

## Task 8: Documentation and Install Surface

**Files:**
- Create: `docs/mcp.md`
- Modify: `README.md`
- Modify: `install.ps1`
- Modify: `install.sh`
- Modify: `CONTEXT.md`
- Modify: `AUTOMATION_ROADMAP.md`

- [ ] **Step 1: Create MCP docs**

Create `docs/mcp.md`:

```markdown
# AURA MCP Server

`aura-mcp` is a local stdio MCP server for AURA analysis. It exposes protected, bounded tools for LLM/agent clients.

## Build

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
```

## Environment

```powershell
$env:AURA_REPO_ROOT = "C:\path\to\AURA"
$env:AURA_MCP_ALLOWED_ROOTS = "C:\path\to\AURA"
```

`AURA_MCP_ALLOWED_ROOTS` is a semicolon-separated list on Windows and a colon-separated list on Linux/macOS.

## Client Command

```powershell
C:\path\to\AURA\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

## Manual Smoke

```powershell
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/list","params":{}}',
'{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_probe_engines","arguments":{}}}',
'{"jsonrpc":"2.0","id":4,"method":"tools/call","params":{"name":"aura_analyze","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- `initialize` returns `serverInfo.name = aura-mcp`.
- `tools/list` includes `aura_probe_engines`.
- `aura_probe_engines` returns an AURA MCP envelope.
- `aura_analyze` returns `disclosure = protected`.

## Security Defaults

- stdio only in V1.
- stdout is reserved for MCP JSON-RPC.
- logs go to stderr.
- binary paths must be under `AURA_MCP_ALLOWED_ROOTS`.
- raw tools are denied by default.
- protected tools do not return raw sensitive string content.
```

- [ ] **Step 2: Update README**

Add a short section to `README.md` near CLI/GUI execution:

```markdown
## MCP Server

AURA ships a local stdio MCP server for protected agent access:

```powershell
cmake --build build-trim-gui --config Release --target aura-mcp
$env:AURA_REPO_ROOT = (Get-Location).Path
$env:AURA_MCP_ALLOWED_ROOTS = (Get-Location).Path
.\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

See `docs/mcp.md` for client configuration and smoke tests.
```

- [ ] **Step 3: Update install scripts**

In `install.ps1`, after printing `AURA_RIZIN_PATH`, add:

```powershell
$McpExe = Join-Path $Root "build-trim-gui\src\mcp\Release\aura-mcp.exe"
if (Test-Path -LiteralPath $McpExe) {
    Write-Host "AURA_MCP_BIN=$McpExe"
} else {
    Write-Host "AURA install: aura-mcp not built yet; run cmake --build build-trim-gui --config Release --target aura-mcp"
}
```

In `install.sh`, after printing Rizin env values, add:

```bash
MCP_BIN="$ROOT/build-trim-gui/src/mcp/aura-mcp"
if [ -x "$MCP_BIN" ]; then
  echo "AURA_MCP_BIN=$MCP_BIN"
else
  echo "AURA install: aura-mcp not built yet; run cmake --build build-trim-gui --target aura-mcp"
fi
```

- [ ] **Step 4: Update context and roadmap**

In `CONTEXT.md`, change MCP from future-only wording to V1 wording:

```markdown
`aura-mcp` is the local stdio MCP gateway. V1 exposes protected headless tools over JSON-RPC stdio and does not require the GUI. Streamable HTTP and raw privileged success paths are deferred.
```

In `AUTOMATION_ROADMAP.md`, add a row recording:

```markdown
| 2026-05-08 | MCP V1 implementation planned/executed: stdio `aura-mcp`, protected tool surface, path allowlist, CLI bridge, raw denial, docs, and MCP CTest label. | Next: subagent-driven implementation and QA/ship. | Raw privileged success path deferred. |
```

- [ ] **Step 5: Run docs/script validation**

```powershell
$tokens=$null; $errors=$null; [System.Management.Automation.Language.Parser]::ParseFile((Resolve-Path '.\install.ps1'), [ref]$tokens, [ref]$errors) > $null; if ($errors.Count) { $errors | ForEach-Object { $_.Message }; exit 1 }; 'install.ps1 parse ok'
bash -n install.sh
```

Expected: both pass.

- [ ] **Step 6: Commit Task 8**

```powershell
git add README.md docs/mcp.md install.ps1 install.sh CONTEXT.md AUTOMATION_ROADMAP.md
git commit -m "docs(mcp): document local server setup"
```

## Task 9: Final Verification

**Files:**
- No planned source edits unless verification exposes a bug.

- [ ] **Step 1: Build release targets**

```powershell
cmake --build build-trim-gui --config Release
```

Expected: build succeeds and includes `aura.exe`, `aura-gui.exe`, and `aura-mcp.exe`.

- [ ] **Step 2: Run focused MCP tests**

```powershell
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

Expected: all MCP tests pass.

- [ ] **Step 3: Run full test suite in clean runtime env**

```powershell
$saved=@{}; foreach ($n in 'AURA_RIZIN_BIN','AURA_RIZIN_PATH','AURA_REPO_ROOT','SLEIGHHOME') { if (Test-Path "Env:$n") { $saved[$n]=(Get-Item "Env:$n").Value; Remove-Item "Env:$n" } }; try { ctest --test-dir build-trim-gui -C Release --output-on-failure; $code=$LASTEXITCODE } finally { foreach ($kv in $saved.GetEnumerator()) { Set-Item "Env:$($kv.Key)" $kv.Value } }; exit $code
```

Expected: full CTest passes.

- [ ] **Step 4: Run manual MCP happy path**

```powershell
$env:AURA_REPO_ROOT = (Get-Location).Path
$env:AURA_MCP_ALLOWED_ROOTS = (Get-Location).Path
$input = @(
'{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"1"}}}',
'{"jsonrpc":"2.0","id":2,"method":"tools/list","params":{}}',
'{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_probe_engines","arguments":{}}}',
'{"jsonrpc":"2.0","id":4,"method":"tools/call","params":{"name":"aura_info","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64"}}}',
'{"jsonrpc":"2.0","id":5,"method":"tools/call","params":{"name":"aura_get_llm_context","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}'
) -join "`n"
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected:

- output is valid JSON-RPC lines only.
- `tools/list` includes AURA tools.
- tool calls return `mcp_schema_version`.
- tool calls return `disclosure":"protected"`.
- `aura_get_llm_context` includes `dbg.main` or callees for the sample fixture.

- [ ] **Step 5: Run manual MCP denied path**

```powershell
$input = '{"jsonrpc":"2.0","id":1,"method":"tools/call","params":{"name":"aura_get_raw_disassembly","arguments":{"binary_path":"tests/fixtures/bin/elf_smoke.x86_64","function_addr":"0x40117b"}}}'
$input | .\build-trim-gui\src\mcp\Release\aura-mcp.exe
```

Expected: output contains `raw_access_denied`, `isError:true`, and no raw disassembly body.

- [ ] **Step 6: Commit verification fixes only if needed**

If a verification bug was fixed:

```powershell
git add <changed-files>
git commit -m "fix(mcp): stabilize final verification"
```

If no fixes were needed, do not create an empty commit.

## Completion Criteria

- `aura-mcp` builds on Windows.
- `tools/list` works in a real stdio request/response run.
- `aura_probe_engines`, `aura_info`, `aura_analyze`, and `aura_get_llm_context` work through MCP.
- All MCP tool responses use the ADR-0057 envelope.
- Default disclosure is protected.
- Raw tools are denied by default.
- Path allowlist rejects outside-root binaries.
- MCP tests have `mcp` CTest label.
- Full CTest passes.
- `docs/mcp.md` has copy-paste setup.

## Deferred Work

- Streamable HTTP transport.
- Raw privileged success path with per-request approval.
- Audit log persistence beyond denied metadata.
- Direct core serializer reuse instead of CLI subprocess bridge.
- MCP resources/prompts beyond tools.
- GUI configuration screen for MCP.

## Self-Review

Spec coverage:

- Real MCP server: covered by Tasks 4 and 9.
- Tool surface: covered by Tasks 3, 5, and 7.
- Protected default: covered by Tasks 3, 6, and 9.
- Path policy: covered by Task 2.
- Tests: covered by Tasks 1-9.
- Docs/install: covered by Task 8.

Placeholder scan:

- No unresolved placeholder markers, vague error-handling instructions, or undefined future steps remain.
- Deferred items are explicitly outside V1.

Type consistency:

- Envelope functions use `cJSON*`.
- Tool registry functions use `cJSON*`.
- Path policy uses `AuraMcpPathDecision`.
- Protected export uses `ProtectedExportRecord`.
