# Safety Gateway EXE Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build `aura-safety-gateway.exe`, an independent MCP-facing safety gateway endpoint that users can select as their MCP server URL so AURA Safety Assets are applied before data reaches an LLM client.

**Architecture:** The gateway is not a reverse-engineering mode. It is a policy layer exposed as an MCP-compatible endpoint, reusing `aura_core` safety/gateway functions and producing protected JSON with audit evidence. The first inbound data is filtered before forwarding; the gateway then checks whether the protected value is safe to pass, stores the protected decision/cache record, and only then returns or forwards the protected payload. Slice 1 implements deterministic `--once` JSON protection plus cache persistence; Slice 2 exposes a Streamable HTTP `/mcp` endpoint that official MCP clients can use directly; stdio is kept only as a local compatibility mode.

**Tech Stack:** C++17, CMake, cJSON, existing `aura_core`, existing MCP JSON-RPC conventions, doctest smoke/unit tests, Windows `.exe` target.

---

## Requirements

- Create a standalone executable named `aura-safety-gateway.exe`.
- Do not implement a new RE engine in this branch.
- The gateway sits in the MCP communication path and protects Safety Assets output.
- Users should be able to configure the official MCP client endpoint URL to the safety gateway, for example `http://127.0.0.1:8765/mcp`.
- The gateway must look like an MCP server to the client. The client should not need to know that AURA exists behind it.
- Streamable HTTP is the primary remote endpoint mode. Stdio remains optional for local clients.
- Streamable HTTP compatibility must cover the official MCP handshake path:
  - `initialize`;
  - `tools/list`;
  - `tools/call`;
  - request `id` preservation;
  - `MCP-Protocol-Version` handling;
  - optional `MCP-Session-Id` issuance and reuse.
- Input and output endpoints must be separately configurable:
  - input endpoint: where official MCP clients connect to the safety gateway;
  - output/upstream endpoint: where the gateway forwards approved requests, if forwarding is enabled.
- The first inbound data must be filtered before it is forwarded anywhere.
- The gateway must decide whether each value is safe to pass:
  - `allow`: value is not sensitive;
  - `mask`: value is sensitive but safe after masking;
  - `block`: value cannot be made safe or policy rejects it.
- The gateway must persist cache records for decisions and protected values so repeated requests do not re-scan identical content unnecessarily.
- Cache DBs must be user-selectable and independently manageable. A user analyzing software A can use `A-cache.sqlite`, then analyzing software B can choose either the same `A-cache.sqlite` or a separate `B-cache.sqlite`.
- Cache must store raw values only when explicitly allowed by a local debug policy. Default cache records store hashes, protected values, categories, actions, and audit metadata.
- Use official MCP docs/SDKs or high-star MCP projects as references when needed.
- Store downloaded references under `.scratch/mcp-reference/`; do not vendor reference code into product code.
- Reuse current AURA safety and gateway code:
  - `include/aura/gateway/gateway_snapshot.h`
  - `src/core/gateway/gateway_snapshot.cpp`
  - `include/aura/safety/safe_export_view.h`
  - `src/core/safety/safe_export_view.cpp`
  - `include/aura/safety/string_safety.h`
  - `src/core/safety/string_safety.cpp`
  - `src/mcp/mcp_tools.cpp`
  - `src/mcp/mcp_cli_bridge.cpp`
- The first testable result must work without Rizin/Ghidra:
  - read a JSON request;
  - protect strings/text fields;
  - emit a protected JSON response;
  - include pass/warning/block decision;
  - include audit records.

---

## File Structure

- Create `src/safety_gateway/CMakeLists.txt`
  - Builds `aura_safety_gateway_core` first, then adds `aura-safety-gateway` after the CLI task.
- Create `src/safety_gateway/main.cpp`
  - CLI entrypoint for `--serve --listen-host 127.0.0.1 --listen-port 8765`, optional `--upstream-url`, `--once`, `--stdio`, `--inspect-policy`, and `--version`.
- Create `src/safety_gateway/gateway_request.h`
  - Plain structs for gateway request, payload item, response, audit event, and decision.
- Create `src/safety_gateway/gateway_request.cpp`
  - Parse request JSON and serialize response JSON.
- Create `src/safety_gateway/gateway_policy.h`
  - Public function `evaluateGatewayRequest`.
- Create `src/safety_gateway/gateway_policy.cpp`
  - Apply safety scanning/masking to input payload, build audit entries, and compute decision.
- Create `src/safety_gateway/mcp_http.h`
  - HTTP/MCP request handling interfaces and JSON-RPC response helpers.
- Create `src/safety_gateway/mcp_http.cpp`
  - Minimal Streamable HTTP-compatible `/mcp` handler for `initialize`, `tools/list`, and `tools/call`.
- Create `src/safety_gateway/gateway_cache.h`
  - Cache interface for content hash lookup and decision persistence.
- Create `src/safety_gateway/gateway_cache.cpp`
  - SQLite-backed cache implementation using hashes and protected values.
- Create `tests/unit/safety_gateway/CMakeLists.txt`
  - Adds `safety_gateway_unit`.
- Create `tests/unit/safety_gateway/safety_gateway_unit.cpp`
  - Tests parser, masking decision, cache hit/miss, no-raw-original invariant, and malformed JSON errors.
- Create `tests/integration/safety_gateway_smoke/CMakeLists.txt`
  - Adds `safety_gateway_smoke`.
- Create `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`
  - Runs `aura-safety-gateway --once fixture.json` as a subprocess.
  - Starts `aura-safety-gateway --serve` and verifies `POST /mcp` JSON-RPC responses.
- Modify `CMakeLists.txt`
  - Add `add_subdirectory(src/safety_gateway)` unconditionally after `src/mcp` during Task 2 so parser tests can link.
  - Add unit/integration test subdirectories when `AURA_BUILD_TESTS` is enabled.
- Optional later modify `src/mcp/mcp_cli_bridge.cpp`
  - Add env-gated gateway relay path only after standalone EXE tests pass.

---

## JSON Contract

### Input

```json
{
  "request_id": "demo-001",
  "source": "mcp",
  "operation": "protect_context",
  "payload": {
    "items": [
      {
        "kind": "string",
        "location": "0x401000",
        "category": "unknown",
        "text": "alice.smith@example.com"
      }
    ]
  }
}
```

### Output

```json
{
  "request_id": "demo-001",
  "decision": "pass",
  "schema_version": "aura-safety-gateway/1.0",
  "summary": {
    "items_total": 1,
    "masked_count": 1,
    "blocked_count": 0,
    "raw_original_included": false
  },
  "items": [
    {
      "kind": "string",
      "location": "0x401000",
      "category": "email",
      "protected_text": "alic***************e.com",
      "action": "mask",
      "original_included": false
    }
  ],
  "audit": [
    {
      "action": "mask",
      "kind": "string",
      "location": "0x401000",
      "category": "email",
      "safe_preview": "alic***************e.com",
      "reason": "safety rule matched"
    }
  ]
}
```

### Decision Rules

- `pass`: all items are safe after masking or no protected values were found.
- `warning`: malformed optional fields were ignored or no active safety rules were available.
- `block`: a raw protected value would be included in output, payload is malformed, or policy says unmasked export is disallowed.

---

## Gateway Data Flow

```text
Official MCP client
  ↓ POST /mcp
Safety Gateway receives JSON-RPC
  ↓
MCP protocol handler
  - initialize
  - tools/list
  - tools/call
  - preserve JSON-RPC id
  - validate protocol/session headers when present
  ↓
Extract tool call arguments / payload items
  ↓
Input filter
  - reject malformed payload
  - normalize text fields
  - compute content hash
  ↓
Cache lookup
  - if same content + same policy hash exists, reuse protected decision
  - if missing/stale, run safety scan
  ↓
Safety decision
  - allow / mask / block
  ↓
Cache write
  - store hash, protected_text, category, action, detector summary, policy hash
  - do not store raw original by default
  ↓
Forward or respond
  - pass/mask: return protected MCP result
  - block: return MCP error or protected block result
```

## Cache Policy

Cache is a user-managed artifact, not a hidden global singleton.

Recommended per-target cache files:

```text
.aura/cache/<project-or-binary-name>.safety-gateway.sqlite
```

Default cache file when the user does not specify one:

```text
.aura/safety-gateway-cache.sqlite
```

Explicit user-selected cache:

```powershell
aura-safety-gateway --cache .scratch/safety-gateway-cache.sqlite
aura-safety-gateway --cache D:\aura-cache\software-a.sqlite
aura-safety-gateway --cache D:\aura-cache\software-b.sqlite
```

Endpoint mode must also accept cache selection:

```powershell
aura-safety-gateway --serve --listen-host 127.0.0.1 --listen-port 8765 --cache D:\aura-cache\software-a.sqlite
```

MCP client configuration then points only to the gateway endpoint:

```json
{
  "mcpServers": {
    "aura-safety-gateway-software-a": {
      "url": "http://127.0.0.1:8765/mcp"
    }
  }
}
```

If the user wants to switch from software A to software B, they restart the gateway with a different `--cache` path or run a second gateway on another port:

```powershell
aura-safety-gateway --serve --listen-port 8765 --cache D:\aura-cache\software-a.sqlite
aura-safety-gateway --serve --listen-port 8766 --cache D:\aura-cache\software-b.sqlite
```

If the gateway should forward approved MCP calls to an upstream MCP server, configure output separately:

```powershell
aura-safety-gateway `
  --serve `
  --listen-host 127.0.0.1 `
  --listen-port 8765 `
  --upstream-url http://127.0.0.1:8780/mcp `
  --cache D:\aura-cache\software-a.sqlite
```

Port model:

```text
MCP Client
  -> input/listen: http://127.0.0.1:8765/mcp
  -> aura-safety-gateway.exe
  -> output/upstream: http://127.0.0.1:8780/mcp or GUI RPC port
```

Forwarding is optional. In demo/local protection mode, the gateway may answer directly without upstream forwarding.

## Endpoint Security Policy

- Default input binding is `127.0.0.1`, not `0.0.0.0`.
- Binding to a non-loopback host requires explicit `--allow-remote-bind`.
- `--upstream-url` is optional. When absent, the gateway answers only with protected gateway tools and does not forward.
- When `--upstream-url` is present, only approved requests are forwarded.
- Blocked requests must not be forwarded.
- The gateway response must include whether the result was:
  - `local`: answered by the gateway itself;
  - `forwarded`: sent to upstream after filtering;
  - `blocked`: not sent upstream.
- The upstream URL itself should be shown in diagnostics, but not repeated in every protected payload unless `--verbose` is set.

## MCP HTTP Compatibility Rules

- Endpoint path is `/mcp` by default.
- The server accepts JSON-RPC requests over HTTP POST.
- `initialize` returns a valid server identity and capabilities.
- If the server issues `MCP-Session-Id`, later requests with that session ID are accepted.
- Stateless mode is allowed for MVP; if no session ID is issued, the client should still be able to call `tools/list` and `tools/call`.
- Request `id` must be copied into the response. Do not hardcode `id: 1`.
- Unsupported methods return JSON-RPC error `-32601`.
- Malformed JSON returns JSON-RPC error `-32700`.
- Invalid params return JSON-RPC error `-32602`.
- HTTP response should use `Content-Type: application/json` for direct JSON responses.
- SSE/resumability is deferred, but the implementation must not prevent adding it later.

Table shape:

```sql
CREATE TABLE gateway_cache (
  content_hash TEXT NOT NULL,
  policy_hash TEXT NOT NULL,
  kind TEXT NOT NULL,
  category TEXT NOT NULL,
  action TEXT NOT NULL,
  protected_text TEXT NOT NULL,
  detector_summary TEXT NOT NULL,
  created_at TEXT NOT NULL,
  last_seen_at TEXT NOT NULL,
  hit_count INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (content_hash, policy_hash, kind)
);
```

Security rules:

- `content_hash` is SHA-256 of the original text plus kind.
- `policy_hash` changes when rule-pack/profile settings change.
- `protected_text` may be stored because it is safe-to-export output.
- Raw original text is not stored by default.
- Debug raw cache mode is out of scope for this plan.
- Cache hit still returns an audit event with `reason: "cache hit"`.
- The response summary includes the active cache path or a redacted cache identifier so the user can verify which DB is being used.

---

## Task 1: MCP Reference Intake

**Files:**
- Create: `.scratch/mcp-reference/README.md`
- No product code changes.

- [ ] **Step 1: Download or record official/high-star references**

Use official MCP docs first. If examples are needed, clone only into `.scratch/mcp-reference/`.

```powershell
New-Item -ItemType Directory -Force .scratch/mcp-reference | Out-Null
git clone --depth 1 https://github.com/modelcontextprotocol/typescript-sdk .scratch/mcp-reference/official-typescript-sdk
git clone --depth 1 https://github.com/modelcontextprotocol/python-sdk .scratch/mcp-reference/official-python-sdk
git clone --depth 1 https://github.com/jlowin/fastmcp .scratch/mcp-reference/fastmcp
```

- [ ] **Step 2: Write reference notes**

Create `.scratch/mcp-reference/README.md`:

```markdown
# MCP Reference Notes

References are for protocol/transport study only. Product code must not copy reference implementation code.

## Sources

- Official TypeScript SDK: https://github.com/modelcontextprotocol/typescript-sdk
- Official Python SDK: https://github.com/modelcontextprotocol/python-sdk
- FastMCP: https://github.com/jlowin/fastmcp

## AURA Use

- Confirm JSON-RPC request/response shape.
- Confirm `initialize`, `tools/list`, and `tools/call` behavior.
- Confirm stdio newline-delimited message handling.
- Implement AURA gateway in C++17 using existing cJSON and aura_core.
```

- [ ] **Step 3: Commit nothing from `.scratch`**

Run:

```powershell
git status --short
```

Expected: `.scratch/mcp-reference/` appears as untracked and remains uncommitted.

---

## Task 2: Gateway Request Model and JSON Parser

**Files:**
- Create: `src/safety_gateway/CMakeLists.txt`
- Create: `src/safety_gateway/gateway_request.h`
- Create: `src/safety_gateway/gateway_request.cpp`
- Test: `tests/unit/safety_gateway/safety_gateway_unit.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: Write failing parser tests**

Add a doctest case:

```cpp
TEST_CASE("safety gateway parses protect_context request") {
    const char* json = R"({
      "request_id":"demo-001",
      "source":"mcp",
      "operation":"protect_context",
      "payload":{"items":[
        {"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}
      ]}
    })";

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    CHECK(aura::safety_gateway::parseGatewayRequest(json, &request, &error));
    CHECK(request.request_id == "demo-001");
    CHECK(request.source == "mcp");
    CHECK(request.operation == "protect_context");
    REQUIRE(request.items.size() == 1);
    CHECK(request.items[0].kind == "string");
    CHECK(request.items[0].text == "alice.smith@example.com");
}
```

- [ ] **Step 2: Run test and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R safety_gateway_unit --output-on-failure
```

Expected: build fails because `safety_gateway_unit` or parser symbols do not exist.

- [ ] **Step 3: Implement request structs**

Create `src/safety_gateway/gateway_request.h`:

```cpp
#pragma once

#include <string>
#include <vector>

namespace aura::safety_gateway {

struct GatewayPayloadItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string text;
};

struct GatewayRequest {
    std::string request_id;
    std::string source;
    std::string operation;
    std::vector<GatewayPayloadItem> items;
};

struct GatewayAuditRecord {
    std::string action;
    std::string kind;
    std::string location;
    std::string category;
    std::string safe_preview;
    std::string reason;
};

struct GatewayOutputItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string protected_text;
    std::string action;
    bool original_included = false;
};

struct GatewayResponse {
    std::string request_id;
    std::string decision;
    std::string cache_path;
    std::string route = "local";
    int items_total = 0;
    int masked_count = 0;
    int blocked_count = 0;
    bool raw_original_included = false;
    std::vector<GatewayOutputItem> items;
    std::vector<GatewayAuditRecord> audit;
};

bool parseGatewayRequest(const std::string& json,
                         GatewayRequest* out,
                         std::string* error);
std::string gatewayResponseToJson(const GatewayResponse& response,
                                  bool compact);

}  // namespace aura::safety_gateway
```

- [ ] **Step 4: Implement JSON parse/serialize**

Create `src/safety_gateway/gateway_request.cpp` using `cJSON_Parse`, strict object checks, and clear errors:

```cpp
#include "gateway_request.h"

extern "C" {
#include "cJSON.h"
}

#include <memory>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};

using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

const char* stringValue(cJSON* object, const char* name) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(value) && value->valuestring ? value->valuestring : nullptr;
}

bool requireString(cJSON* object, const char* name, std::string* out, std::string* error) {
    const char* value = stringValue(object, name);
    if (!value || value[0] == '\0') {
        if (error) *error = std::string("missing or empty field: ") + name;
        return false;
    }
    *out = value;
    return true;
}

void addString(cJSON* object, const char* name, const std::string& value) {
    cJSON_AddStringToObject(object, name, value.c_str());
}

}  // namespace

bool parseGatewayRequest(const std::string& json, GatewayRequest* out, std::string* error) {
    if (!out) {
        if (error) *error = "output pointer is null";
        return false;
    }
    JsonPtr root(cJSON_Parse(json.c_str()));
    if (!root || !cJSON_IsObject(root.get())) {
        if (error) *error = "request must be a JSON object";
        return false;
    }

    GatewayRequest parsed;
    if (!requireString(root.get(), "request_id", &parsed.request_id, error) ||
        !requireString(root.get(), "source", &parsed.source, error) ||
        !requireString(root.get(), "operation", &parsed.operation, error)) {
        return false;
    }

    cJSON* payload = cJSON_GetObjectItemCaseSensitive(root.get(), "payload");
    cJSON* items = payload ? cJSON_GetObjectItemCaseSensitive(payload, "items") : nullptr;
    if (!cJSON_IsArray(items)) {
        if (error) *error = "payload.items must be an array";
        return false;
    }

    cJSON* item = nullptr;
    cJSON_ArrayForEach(item, items) {
        if (!cJSON_IsObject(item)) {
            if (error) *error = "payload item must be an object";
            return false;
        }
        GatewayPayloadItem row;
        if (!requireString(item, "kind", &row.kind, error) ||
            !requireString(item, "location", &row.location, error) ||
            !requireString(item, "text", &row.text, error)) {
            return false;
        }
        const char* category = stringValue(item, "category");
        row.category = category ? category : "unknown";
        parsed.items.push_back(std::move(row));
    }

    *out = std::move(parsed);
    return true;
}

std::string gatewayResponseToJson(const GatewayResponse& response, bool compact) {
    JsonPtr root(cJSON_CreateObject());
    addString(root.get(), "request_id", response.request_id);
    addString(root.get(), "decision", response.decision);
    addString(root.get(), "schema_version", "aura-safety-gateway/1.0");
    addString(root.get(), "cache_path", response.cache_path);
    addString(root.get(), "route", response.route);

    cJSON* summary = cJSON_AddObjectToObject(root.get(), "summary");
    cJSON_AddNumberToObject(summary, "items_total", response.items_total);
    cJSON_AddNumberToObject(summary, "masked_count", response.masked_count);
    cJSON_AddNumberToObject(summary, "blocked_count", response.blocked_count);
    cJSON_AddBoolToObject(summary, "raw_original_included", response.raw_original_included);

    cJSON* items = cJSON_AddArrayToObject(root.get(), "items");
    for (const auto& row : response.items) {
        cJSON* item = cJSON_CreateObject();
        addString(item, "kind", row.kind);
        addString(item, "location", row.location);
        addString(item, "category", row.category);
        addString(item, "protected_text", row.protected_text);
        addString(item, "action", row.action);
        cJSON_AddBoolToObject(item, "original_included", row.original_included);
        cJSON_AddItemToArray(items, item);
    }

    cJSON* audit = cJSON_AddArrayToObject(root.get(), "audit");
    for (const auto& row : response.audit) {
        cJSON* item = cJSON_CreateObject();
        addString(item, "action", row.action);
        addString(item, "kind", row.kind);
        addString(item, "location", row.location);
        addString(item, "category", row.category);
        addString(item, "safe_preview", row.safe_preview);
        addString(item, "reason", row.reason);
        cJSON_AddItemToArray(audit, item);
    }

    char* raw = compact ? cJSON_PrintUnformatted(root.get()) : cJSON_Print(root.get());
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

}  // namespace aura::safety_gateway
```

- [ ] **Step 5: Wire minimal core and unit targets**

Create `src/safety_gateway/CMakeLists.txt` with only the parser source at first:

```cmake
add_library(aura_safety_gateway_core STATIC
    gateway_request.cpp
)
target_include_directories(aura_safety_gateway_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(aura_safety_gateway_core PUBLIC aura_core cjson)
target_compile_features(aura_safety_gateway_core PUBLIC cxx_std_17)
```

Modify root `CMakeLists.txt` after `add_subdirectory(src/mcp)`:

```cmake
# ── Safety Gateway EXE ─────────────────────────────────────────────────────
add_subdirectory(src/safety_gateway)
```

Modify the `if(AURA_BUILD_TESTS)` block:

```cmake
add_subdirectory(tests/unit/safety_gateway)
```

Create `tests/unit/safety_gateway/CMakeLists.txt`:

```cmake
add_executable(safety_gateway_unit
    safety_gateway_unit.cpp
)
target_include_directories(safety_gateway_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/src/safety_gateway
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(safety_gateway_unit PRIVATE aura_safety_gateway_core aura_core cjson)
target_compile_features(safety_gateway_unit PRIVATE cxx_std_17)

add_test(NAME safety_gateway_unit COMMAND safety_gateway_unit)
set_tests_properties(safety_gateway_unit PROPERTIES
    LABELS "unit;safety_gateway"
    TIMEOUT 30
)
```

- [ ] **Step 6: Run unit test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R safety_gateway_unit --output-on-failure
```

Expected: parser test passes.

---

## Task 3: Safety Policy Evaluation

**Files:**
- Create: `src/safety_gateway/gateway_policy.h`
- Create: `src/safety_gateway/gateway_policy.cpp`
- Create: `src/safety_gateway/gateway_cache.h`
- Create: `src/safety_gateway/gateway_cache.cpp`
- Modify: `tests/unit/safety_gateway/safety_gateway_unit.cpp`
- Modify: `src/safety_gateway/CMakeLists.txt`

- [ ] **Step 1: Write failing policy tests**

Add:

```cpp
TEST_CASE("safety gateway masks protected text and omits original") {
    aura::safety_gateway::GatewayRequest request;
    request.request_id = "demo-002";
    request.source = "mcp";
    request.operation = "protect_context";
    request.items.push_back({"string", "0x401000", "unknown", "alice.smith@example.com"});

    aura::safety_gateway::GatewayPolicyOptions options;
    aura::safety_gateway::GatewayResponse response =
        aura::safety_gateway::evaluateGatewayRequest(request, options);

    CHECK(response.decision == "pass");
    CHECK(response.items_total == 1);
    CHECK(response.masked_count == 1);
    CHECK_FALSE(response.raw_original_included);
    REQUIRE(response.items.size() == 1);
    CHECK(response.items[0].action == "mask");
    CHECK(response.items[0].protected_text.find('*') != std::string::npos);
    CHECK(response.items[0].protected_text.find("alice.smith@example.com") == std::string::npos);

    const std::string json = aura::safety_gateway::gatewayResponseToJson(response, true);
    CHECK(json.find("alice.smith@example.com") == std::string::npos);
}
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
```

Expected: missing `evaluateGatewayRequest`.

- [ ] **Step 3: Implement policy header**

Create `src/safety_gateway/gateway_policy.h`:

```cpp
#pragma once

#include "gateway_request.h"

namespace aura::safety_gateway {

struct GatewayPolicyOptions {
    std::string policy_hash = "default-policy";
    bool use_cache = true;
    std::string cache_path;
    bool include_cache_path_in_response = true;
};

GatewayResponse evaluateGatewayRequest(const GatewayRequest& request,
                                       const GatewayPolicyOptions& options);

}  // namespace aura::safety_gateway
```

- [ ] **Step 4: Implement cache interface**

Create `src/safety_gateway/gateway_cache.h`:

```cpp
#pragma once

#include "gateway_request.h"

#include <string>

namespace aura::safety_gateway {

struct GatewayCacheKey {
    std::string content_hash;
    std::string policy_hash;
    std::string kind;
};

struct GatewayCacheEntry {
    GatewayCacheKey key;
    std::string category;
    std::string action;
    std::string protected_text;
    std::string detector_summary;
};

std::string defaultGatewayCachePath();
std::string gatewayContentHash(const GatewayPayloadItem& item);
bool lookupGatewayCache(const std::string& cache_path,
                        const GatewayCacheKey& key,
                        GatewayCacheEntry* out);
bool storeGatewayCache(const std::string& cache_path,
                       const GatewayCacheEntry& entry);

}  // namespace aura::safety_gateway
```

Create `src/safety_gateway/gateway_cache.cpp`:

```cpp
#include "gateway_cache.h"

extern "C" {
#include "sha256.h"
#include "sqlite3.h"
}

#include <cstdlib>
#include <filesystem>
#include <sstream>

namespace aura::safety_gateway {
namespace fs = std::filesystem;

std::string defaultGatewayCachePath() {
    const char* env = std::getenv("AURA_SAFETY_GATEWAY_CACHE");
    if (env && env[0]) return env;
    return (fs::current_path() / ".aura" / "safety-gateway-cache.sqlite").string();
}

std::string gatewayContentHash(const GatewayPayloadItem& item) {
    const std::string material = item.kind + "\n" + item.text;
    uint8_t digest[AURA_SHA256_DIGEST_LEN];
    AuraSha256Ctx ctx;
    aura_sha256_init(&ctx);
    aura_sha256_update(&ctx, material.data(), material.size());
    aura_sha256_final(&ctx, digest);
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1];
    aura_sha256_hex(digest, hex);
    return hex;
}

static void ensureParentDirectory(const std::string& cache_path) {
    const auto parent = fs::path(cache_path).parent_path();
    if (!parent.empty()) {
        fs::create_directories(parent);
    }
}

static bool ensureSchema(sqlite3* db) {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS gateway_cache ("
        "content_hash TEXT NOT NULL,"
        "policy_hash TEXT NOT NULL,"
        "kind TEXT NOT NULL,"
        "category TEXT NOT NULL,"
        "action TEXT NOT NULL,"
        "protected_text TEXT NOT NULL,"
        "detector_summary TEXT NOT NULL,"
        "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "last_seen_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "hit_count INTEGER NOT NULL DEFAULT 0,"
        "PRIMARY KEY (content_hash, policy_hash, kind));";
    return sqlite3_exec(db, sql, nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool lookupGatewayCache(const std::string& cache_path,
                        const GatewayCacheKey& key,
                        GatewayCacheEntry* out) {
    if (!out || cache_path.empty()) return false;
    ensureParentDirectory(cache_path);
    sqlite3* db = nullptr;
    if (sqlite3_open(cache_path.c_str(), &db) != SQLITE_OK) return false;
    const bool schema_ok = ensureSchema(db);
    if (!schema_ok) {
        sqlite3_close(db);
        return false;
    }
    const char* sql =
        "SELECT category, action, protected_text, detector_summary "
        "FROM gateway_cache WHERE content_hash=? AND policy_hash=? AND kind=?;";
    sqlite3_stmt* stmt = nullptr;
    bool found = false;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, key.kind.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            out->key = key;
            out->category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            out->action = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            out->protected_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            out->detector_summary = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            found = true;
        }
    }
    sqlite3_finalize(stmt);
    if (found) {
        sqlite3_stmt* update = nullptr;
        const char* update_sql =
            "UPDATE gateway_cache SET last_seen_at=CURRENT_TIMESTAMP, hit_count=hit_count+1 "
            "WHERE content_hash=? AND policy_hash=? AND kind=?;";
        if (sqlite3_prepare_v2(db, update_sql, -1, &update, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(update, 1, key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(update, 2, key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(update, 3, key.kind.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(update);
        }
        sqlite3_finalize(update);
    }
    sqlite3_close(db);
    return found;
}

bool storeGatewayCache(const std::string& cache_path,
                       const GatewayCacheEntry& entry) {
    if (cache_path.empty()) return false;
    ensureParentDirectory(cache_path);
    sqlite3* db = nullptr;
    if (sqlite3_open(cache_path.c_str(), &db) != SQLITE_OK) return false;
    if (!ensureSchema(db)) {
        sqlite3_close(db);
        return false;
    }
    const char* sql =
        "INSERT INTO gateway_cache(content_hash, policy_hash, kind, category, action, protected_text, detector_summary) "
        "VALUES(?,?,?,?,?,?,?) "
        "ON CONFLICT(content_hash, policy_hash, kind) DO UPDATE SET "
        "category=excluded.category, action=excluded.action, protected_text=excluded.protected_text, "
        "detector_summary=excluded.detector_summary, last_seen_at=CURRENT_TIMESTAMP;";
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, entry.key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, entry.key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, entry.key.kind.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, entry.category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, entry.action.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, entry.protected_text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, entry.detector_summary.c_str(), -1, SQLITE_TRANSIENT);
        ok = sqlite3_step(stmt) == SQLITE_DONE;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return ok;
}

}  // namespace aura::safety_gateway
```

- [ ] **Step 5: Implement policy**

Create `src/safety_gateway/gateway_policy.cpp`:

```cpp
#include "gateway_policy.h"

#include "gateway_cache.h"

#include <algorithm>

namespace aura::safety_gateway {
namespace {

std::string starMask(const std::string& value) {
    if (value.empty()) return "*";
    const int len = static_cast<int>(value.size());
    int mask_count = (len * 65 + 50) / 100;
    mask_count = std::max(1, std::min(mask_count, len));
    const int visible = len - mask_count;
    const int prefix = visible / 2 + visible % 2;
    const int suffix = visible / 2;
    return value.substr(0, static_cast<size_t>(prefix)) +
           std::string(static_cast<size_t>(mask_count), '*') +
           (suffix > 0 ? value.substr(value.size() - static_cast<size_t>(suffix)) : std::string());
}

bool looksSensitiveByFallback(const std::string& value, std::string* category) {
    if (value.find('@') != std::string::npos && value.find('.') != std::string::npos) {
        if (category) *category = "email";
        return true;
    }
    if (value.find("010-") != std::string::npos) {
        if (category) *category = "phone";
        return true;
    }
    if (value.size() >= 13 && value.find('-') != std::string::npos) {
        if (category) *category = "identifier";
        return true;
    }
    return false;
}

}  // namespace

GatewayResponse evaluateGatewayRequest(const GatewayRequest& request,
                                       const GatewayPolicyOptions& options) {
    GatewayResponse response;
    response.request_id = request.request_id;
    response.decision = "pass";
    response.items_total = static_cast<int>(request.items.size());
    const std::string cache_path =
        options.cache_path.empty() ? defaultGatewayCachePath() : options.cache_path;
    if (options.include_cache_path_in_response) {
        response.cache_path = cache_path;
    }

    for (const auto& item : request.items) {
        GatewayCacheKey key{gatewayContentHash(item), options.policy_hash, item.kind};
        GatewayCacheEntry cached;
        if (options.use_cache && lookupGatewayCache(cache_path, key, &cached)) {
            GatewayOutputItem out;
            out.kind = item.kind;
            out.location = item.location;
            out.category = cached.category;
            out.protected_text = cached.protected_text;
            out.action = cached.action;
            out.original_included = false;
            if (out.action == "mask") response.masked_count += 1;
            if (out.action == "block") response.blocked_count += 1;
            GatewayAuditRecord audit;
            audit.action = out.action;
            audit.kind = item.kind;
            audit.location = item.location;
            audit.category = cached.category;
            audit.safe_preview = cached.protected_text;
            audit.reason = "cache hit";
            response.items.push_back(std::move(out));
            response.audit.push_back(std::move(audit));
            continue;
        }

        std::string category = item.category.empty() ? "unknown" : item.category;
        bool matched = looksSensitiveByFallback(item.text, &category);

        GatewayOutputItem out;
        out.kind = item.kind;
        out.location = item.location;
        out.category = category;
        out.original_included = false;

        GatewayAuditRecord audit;
        audit.kind = item.kind;
        audit.location = item.location;
        audit.category = category;

        if (matched) {
            out.action = "mask";
            out.protected_text = starMask(item.text);
            response.masked_count += 1;
            audit.action = "mask";
            audit.safe_preview = out.protected_text;
            audit.reason = "safety rule matched";
        } else {
            out.action = "allow";
            out.protected_text = item.text;
            audit.action = "allow";
            audit.safe_preview = out.protected_text;
            audit.reason = "no protected value detected";
        }

        if (matched && out.protected_text == item.text) {
            response.decision = "block";
            response.blocked_count += 1;
            response.raw_original_included = true;
            out.action = "block";
            audit.action = "block";
            audit.reason = "protected value would be exported raw";
        }

        response.items.push_back(std::move(out));
        response.audit.push_back(std::move(audit));
        if (options.use_cache) {
            const auto& saved = response.items.back();
            GatewayCacheEntry entry;
            entry.key = key;
            entry.category = saved.category;
            entry.action = saved.action;
            entry.protected_text = saved.protected_text;
            entry.detector_summary = matched ? "fallback-sensitive-match" : "fallback-no-match";
            storeGatewayCache(cache_path, entry);
        }
    }

    return response;
}

}  // namespace aura::safety_gateway
```

Note: this starts with deterministic fallback rules so the EXE works without external models. A later task replaces the fallback with full active profile/rule-pack loading.

- [ ] **Step 5: Add policy and cache sources to core target**

Modify `src/safety_gateway/CMakeLists.txt`:

```cmake
add_library(aura_safety_gateway_core STATIC
    gateway_request.cpp
    gateway_policy.cpp
    gateway_cache.cpp
)
target_include_directories(aura_safety_gateway_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/sqlite
)
target_link_libraries(aura_safety_gateway_core PUBLIC aura_core cjson PRIVATE sqlite3)
target_compile_features(aura_safety_gateway_core PUBLIC cxx_std_17)
```

- [ ] **Step 6: Run unit tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R safety_gateway_unit --output-on-failure
```

Expected: parser and policy tests pass.

- [ ] **Step 7: Add cache hit test**

Add:

```cpp
TEST_CASE("safety gateway reuses cached protected value") {
    const auto cache = (std::filesystem::temp_directory_path() / "aura-gateway-cache-test.sqlite").string();
    std::filesystem::remove(cache);

    aura::safety_gateway::GatewayRequest request;
    request.request_id = "cache-001";
    request.source = "mcp";
    request.operation = "protect_context";
    request.items.push_back({"string", "0x401000", "unknown", "010-1234-5678"});

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache;
    auto first = aura::safety_gateway::evaluateGatewayRequest(request, options);
    auto second = aura::safety_gateway::evaluateGatewayRequest(request, options);

    REQUIRE(second.audit.size() == 1);
    CHECK(second.audit[0].reason == "cache hit");
    CHECK(second.items[0].protected_text == first.items[0].protected_text);
    CHECK(second.items[0].protected_text.find("010-1234-5678") == std::string::npos);
}
```

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R safety_gateway_unit --output-on-failure
```

Expected: cache test passes.

---

## Task 4: Build Standalone EXE

**Files:**
- Create: `src/safety_gateway/main.cpp`
- Modify: `src/safety_gateway/CMakeLists.txt`

- [ ] **Step 1: Add executable CMake target**

Append to `src/safety_gateway/CMakeLists.txt`:

```cmake
add_executable(aura-safety-gateway main.cpp)
target_include_directories(aura-safety-gateway PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/sqlite
)
target_link_libraries(aura-safety-gateway PRIVATE aura_safety_gateway_core aura_core cjson sqlite3)
target_compile_features(aura-safety-gateway PRIVATE cxx_std_17)
```

- [ ] **Step 2: Confirm root CMake wiring exists**

Task 2 already added this root CMake entry. Confirm it exists exactly once:

```cmake
# ── Safety Gateway EXE ─────────────────────────────────────────────────────
add_subdirectory(src/safety_gateway)
```

Task 2 already added the unit test directory. Do not add a duplicate:

```cmake
add_subdirectory(tests/unit/safety_gateway)
```

- [ ] **Step 3: Implement `--once` CLI**

Create `src/safety_gateway/main.cpp`:

```cpp
#include "gateway_policy.h"
#include "gateway_request.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string readAll(std::istream& in) {
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void usage() {
    std::cerr
        << "usage:\n"
        << "  aura-safety-gateway --serve [--listen-host 127.0.0.1] [--listen-port 8765] [--upstream-url http://127.0.0.1:8780/mcp] [--cache path.sqlite]\n"
        << "  aura-safety-gateway --once <request.json> [--cache path.sqlite] [--compact]\n"
        << "  aura-safety-gateway --inspect-policy [--compact]\n"
        << "  aura-safety-gateway --version\n";
}

int emitError(const std::string& code, const std::string& message) {
    std::cout << "{\"decision\":\"block\",\"error\":{\"code\":\""
              << code << "\",\"message\":\"" << message << "\"}}\n";
    return 2;
}

bool parsePort(const char* value, int* out) {
    if (!value || !out) return false;
    try {
        const int parsed = std::stoi(value);
        if (parsed < 1 || parsed > 65535) return false;
        *out = parsed;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

}  // namespace

int main(int argc, char** argv) {
    bool compact = false;
    std::string mode;
    std::string path;
    std::string cache_path;
    std::string listen_host = "127.0.0.1";
    int listen_port = 8765;
    std::string upstream_url;
    bool allow_remote_bind = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i] ? argv[i] : "";
        if (arg == "--compact") compact = true;
        else if (arg == "--cache" && i + 1 < argc) {
            cache_path = argv[++i];
        }
        else if (arg == "--listen-host" && i + 1 < argc) {
            listen_host = argv[++i];
        }
        else if (arg == "--listen-port" && i + 1 < argc) {
            if (!parsePort(argv[++i], &listen_port)) {
                return emitError("invalid_port", "listen port must be between 1 and 65535");
            }
        }
        else if (arg == "--upstream-url" && i + 1 < argc) {
            upstream_url = argv[++i];
        }
        else if (arg == "--allow-remote-bind") {
            allow_remote_bind = true;
        }
        else if (arg == "--version") {
            std::cout << "aura-safety-gateway 0.1.0\n";
            return 0;
        } else if (arg == "--inspect-policy") {
            mode = "inspect-policy";
        } else if (arg == "--serve") {
            mode = "serve";
        } else if (arg == "--once" && i + 1 < argc) {
            mode = "once";
            path = argv[++i];
        } else {
            usage();
            return 2;
        }
    }

    if (mode == "inspect-policy") {
        std::cout << "{\"schema_version\":\"aura-safety-gateway/1.0\","
                  << "\"mode\":\"deterministic-fallback\","
                  << "\"masking\":\"star-65-percent\","
                  << "\"raw_original_export\":\"blocked\"}\n";
        return 0;
    }

    if (mode == "serve") {
        (void)listen_host;
        (void)listen_port;
        (void)upstream_url;
        (void)allow_remote_bind;
        return emitError("serve_not_implemented", "HTTP MCP server is implemented in Task 6");
    }

    if (mode != "once" || path.empty()) {
        usage();
        return 2;
    }

    std::ifstream file(path, std::ios::binary);
    if (!file) return emitError("open_failed", "could not open request file");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    if (!aura::safety_gateway::parseGatewayRequest(readAll(file), &request, &error)) {
        return emitError("invalid_request", error);
    }

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path;
    const auto response = aura::safety_gateway::evaluateGatewayRequest(request, options);
    std::cout << aura::safety_gateway::gatewayResponseToJson(response, compact) << "\n";
    return response.decision == "block" ? 3 : 0;
}
```

- [ ] **Step 4: Build EXE**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-safety-gateway
```

Expected: `build-trim-gui/src/safety_gateway/Release/aura-safety-gateway.exe` exists.

---

## Task 5: Gateway Smoke Test

**Files:**
- Create: `tests/integration/safety_gateway_smoke/CMakeLists.txt`
- Create: `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: Write subprocess smoke test**

Create `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`:

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

TEST_CASE("aura-safety-gateway once mode masks protected value") {
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const fs::path request = fs::temp_directory_path() / "aura-safety-gateway-request.json";
    {
        std::ofstream out(request);
        out << R"({"request_id":"smoke-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}})";
    }

    const std::string command =
        std::string("\"") + bin + "\" --once \"" + request.string() + "\" --compact";
    FILE* pipe = _popen(command.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::ostringstream ss;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        ss << buffer;
    }
    const int rc = _pclose(pipe);
    CHECK(rc == 0);

    const std::string output = ss.str();
    CHECK(output.find("\"decision\":\"pass\"") != std::string::npos);
    CHECK(output.find("\"masked_count\":1") != std::string::npos);
    CHECK(output.find("alice.smith@example.com") == std::string::npos);
    CHECK(output.find("*") != std::string::npos);
}
```

- [ ] **Step 2: Write smoke CMake**

Create `tests/integration/safety_gateway_smoke/CMakeLists.txt`:

```cmake
add_executable(safety_gateway_smoke safety_gateway_smoke.cpp)
add_dependencies(safety_gateway_smoke aura-safety-gateway)
target_include_directories(safety_gateway_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_compile_features(safety_gateway_smoke PRIVATE cxx_std_17)

add_test(NAME safety_gateway_smoke COMMAND safety_gateway_smoke)
set_tests_properties(safety_gateway_smoke PROPERTIES
    LABELS "integration;safety_gateway"
    TIMEOUT 30
    ENVIRONMENT "AURA_SAFETY_GATEWAY_BIN=$<TARGET_FILE:aura-safety-gateway>"
)
```

- [ ] **Step 3: Add integration test directory to root CMake**

Modify the `if(AURA_BUILD_TESTS)` block in root `CMakeLists.txt`:

```cmake
add_subdirectory(tests/integration/safety_gateway_smoke)
```

Keep the existing Task 2 unit entry:

```cmake
add_subdirectory(tests/unit/safety_gateway)
```

- [ ] **Step 4: Run smoke test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_smoke
ctest --test-dir build-trim-gui -C Release -R safety_gateway_smoke --output-on-failure
```

Expected: smoke test passes and output does not contain raw email.

---

## Task 6: Streamable HTTP MCP Endpoint MVP

**Files:**
- Modify: `src/safety_gateway/main.cpp`
- Create: `src/safety_gateway/mcp_http.h`
- Create: `src/safety_gateway/mcp_http.cpp`
- Modify: `src/safety_gateway/CMakeLists.txt`
- Modify: `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`

- [ ] **Step 1: Write failing initialize HTTP endpoint test**

Add a test that starts:

```powershell
aura-safety-gateway --serve --listen-host 127.0.0.1 --listen-port <free-test-port>
```

Send a JSON-RPC POST to `http://127.0.0.1:<port>/mcp`:

```json
{"jsonrpc":"2.0","id":17,"method":"initialize","params":{"protocolVersion":"2025-11-25","capabilities":{},"clientInfo":{"name":"aura-smoke","version":"0.1"}}}
```

Expected:

```json
{"jsonrpc":"2.0","id":17,"result":{"protocolVersion":"2025-11-25","serverInfo":{"name":"aura-safety-gateway"}}}
```

The test must verify the response preserves `id: 17`.

- [ ] **Step 2: Write failing tools/list endpoint test**

Send:

```json
{"jsonrpc":"2.0","id":18,"method":"tools/list","params":{}}
```

Expected response contains:

```json
{"jsonrpc":"2.0","id":18,"result":{"tools":[{"name":"aura_gateway_protect_context"}]}}
```

- [ ] **Step 3: Implement JSON-RPC handler**

Create `src/safety_gateway/mcp_http.h`:

```cpp
#pragma once

#include "gateway_policy.h"

#include <string>

namespace aura::safety_gateway {

struct McpHttpOptions {
    GatewayPolicyOptions policy;
    std::string protocol_version = "2025-11-25";
};

std::string handleMcpJsonRpc(const std::string& request_body,
                             const McpHttpOptions& options);

}  // namespace aura::safety_gateway
```

Create `src/safety_gateway/mcp_http.cpp`:

```cpp
#include "mcp_http.h"

extern "C" {
#include "cJSON.h"
}

#include <memory>
#include <string>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};
using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

int requestId(cJSON* root) {
    cJSON* id = cJSON_GetObjectItemCaseSensitive(root, "id");
    return cJSON_IsNumber(id) ? id->valueint : 0;
}

std::string printJson(cJSON* root) {
    char* raw = cJSON_PrintUnformatted(root);
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

cJSON* baseResponse(int id) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "jsonrpc", "2.0");
    cJSON_AddNumberToObject(root, "id", id);
    return root;
}

std::string errorResponse(int id, int code, const char* message) {
    JsonPtr root(baseResponse(id));
    cJSON* err = cJSON_AddObjectToObject(root.get(), "error");
    cJSON_AddNumberToObject(err, "code", code);
    cJSON_AddStringToObject(err, "message", message);
    return printJson(root.get());
}

}  // namespace

std::string handleMcpJsonRpc(const std::string& request_body,
                             const McpHttpOptions& options) {
    JsonPtr request(cJSON_Parse(request_body.c_str()));
    if (!request || !cJSON_IsObject(request.get())) {
        return errorResponse(0, -32700, "parse error");
    }
    const int id = requestId(request.get());
    cJSON* method = cJSON_GetObjectItemCaseSensitive(request.get(), "method");
    if (!cJSON_IsString(method) || !method->valuestring) {
        return errorResponse(id, -32600, "invalid request");
    }
    const std::string name = method->valuestring;

    if (name == "initialize") {
        JsonPtr root(baseResponse(id));
        cJSON* result = cJSON_AddObjectToObject(root.get(), "result");
        cJSON_AddStringToObject(result, "protocolVersion",
                                options.protocol_version.c_str());
        cJSON_AddItemToObject(result, "capabilities", cJSON_CreateObject());
        cJSON* server = cJSON_AddObjectToObject(result, "serverInfo");
        cJSON_AddStringToObject(server, "name", "aura-safety-gateway");
        cJSON_AddStringToObject(server, "version", "0.1.0");
        return printJson(root.get());
    }

    if (name == "tools/list") {
        JsonPtr root(baseResponse(id));
        cJSON* result = cJSON_AddObjectToObject(root.get(), "result");
        cJSON* tools = cJSON_AddArrayToObject(result, "tools");
        cJSON* tool = cJSON_CreateObject();
        cJSON_AddStringToObject(tool, "name", "aura_gateway_protect_context");
        cJSON_AddStringToObject(tool, "description",
                                "Protect AURA context before LLM/MCP export");
        cJSON* schema = cJSON_AddObjectToObject(tool, "inputSchema");
        cJSON_AddStringToObject(schema, "type", "object");
        cJSON_AddItemToArray(tools, tool);
        return printJson(root.get());
    }

    if (name == "tools/call") {
        return errorResponse(id, -32602,
                             "tools/call requires params.arguments in gateway request format");
    }

    return errorResponse(id, -32601, "method not found");
}

}  // namespace aura::safety_gateway
```

- [ ] **Step 4: Implement minimal `--serve`**

First update `src/safety_gateway/CMakeLists.txt` so the protocol handler is compiled:

```cmake
add_library(aura_safety_gateway_core STATIC
    gateway_request.cpp
    gateway_policy.cpp
    gateway_cache.cpp
    mcp_http.cpp
)
```

Then replace the Task 4 `serve_not_implemented` branch in `main.cpp` with a minimal localhost HTTP server:

- Listen on configured `listen_host:listen_port`.
- Accept `POST /mcp`.
- Read request body.
- Return `Content-Type: application/json`.
- For v1, return direct JSON-RPC responses. Streaming/SSE can be deferred until a client needs server-initiated events.

Use `handleMcpJsonRpc` for every `POST /mcp` request. Do not inspect methods with substring matching.

The implementation must reject non-loopback host binding before creating the socket:

```cpp
auto isLoopbackHost = [](const std::string& host) {
    return host == "127.0.0.1" || host == "localhost" || host == "::1";
};

if (!isLoopbackHost(listen_host) && !allow_remote_bind) {
    return emitError("remote_bind_requires_opt_in",
                     "non-loopback listen host requires --allow-remote-bind");
}
```

On Windows, use Winsock initialization in the serve branch:

```cpp
#ifdef _WIN32
WSADATA wsa;
if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    return emitError("winsock_startup_failed", "WSAStartup failed");
}
#endif
```

The server loop may be single-threaded for v1. It must keep running until the process is terminated, because the user explicitly wants the gateway to remain available for repeated MCP calls.

- [ ] **Step 5: Add tools/call protection test**

Send:

```json
{"jsonrpc":"2.0","id":19,"method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"mcp-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}}}}
```

Expected:

- response preserves `id: 19`;
- response result contains MCP text content;
- text contains `"decision":"pass"`;
- text contains `"masked_count":1`;
- response does not contain `alice.smith@example.com`.

Then implement `tools/call` argument parsing in `mcp_http.cpp` by converting `params.arguments` into a `GatewayRequest`, calling `evaluateGatewayRequest`, and wrapping `gatewayResponseToJson` as:

```json
{"content":[{"type":"text","text":"<protected gateway json>"}]}
```

If `--listen-host 0.0.0.0` or another non-loopback address is used without `--allow-remote-bind`, startup must fail with:

```json
{"decision":"block","error":{"code":"remote_bind_requires_opt_in","message":"non-loopback listen host requires --allow-remote-bind"}}
```

- [ ] **Step 6: Add endpoint configuration example**

Add a short docs snippet to `docs/demo/DEMO_SCENARIO.md` or a new `docs/demo/SAFETY_GATEWAY_MCP_ENDPOINT.md`:

```json
{
  "mcpServers": {
    "aura-safety-gateway": {
      "url": "http://127.0.0.1:8765/mcp"
    }
  }
}
```

Explain that the user points the MCP endpoint to the gateway, not directly to `aura-mcp`.

Also document port separation:

```powershell
# Input endpoint for the MCP client
--listen-port 8765

# Optional output endpoint for approved upstream forwarding
--upstream-url http://127.0.0.1:8780/mcp
```

- [ ] **Step 7: Run smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_smoke
ctest --test-dir build-trim-gui -C Release -R safety_gateway_smoke --output-on-failure
```

Expected: HTTP endpoint and once tests pass.

- [ ] **Step 8: Add port/security tests**

Add tests for:

```text
--serve --listen-host 127.0.0.1 --listen-port <port>
  -> starts successfully

--serve --listen-host 0.0.0.0 --listen-port <port>
  -> exits with remote_bind_requires_opt_in unless --allow-remote-bind is present

--serve --listen-port <port> without --upstream-url
  -> tools/call route is "local"
```

---

## Task 7: Optional Local Stdio Compatibility

**Files:**
- Modify: `src/safety_gateway/main.cpp`
- Modify: `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`

- [ ] **Step 1: Keep stdio secondary**

Only implement stdio after `/mcp` works. This mode exists for local MCP clients that launch a process instead of connecting to a URL.

- [ ] **Step 2: Write failing stdio test**

Start `aura-safety-gateway --stdio`, send a `tools/list` JSON-RPC line, and expect the same tool schema as `/mcp`.

- [ ] **Step 3: Implement minimal stdio**

Use the same JSON-RPC handler as the HTTP endpoint. The only difference is transport framing: one JSON message per stdin line, one JSON response per stdout line.

- [ ] **Step 4: Run gateway smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-safety-gateway safety_gateway_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_smoke" --output-on-failure
```

Expected: `/mcp`, `--once`, and `--stdio` tests pass.

---

## Task 8: Final Verification and Commit

**Files:**
- All files touched above.

- [ ] **Step 1: Run focused tests**

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit safety_gateway_smoke aura-safety-gateway
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit|safety_gateway_smoke" --output-on-failure
```

- [ ] **Step 2: Run integration regression**

```powershell
cmake --build build-trim-gui --config Release --target safety_unit malware_risk_unit cli_smoke mcp_smoke gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R "safety_unit|malware_risk_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

- [ ] **Step 3: Manual demo command**

Create `.scratch/safety-gateway-demo-request.json`:

```json
{"request_id":"manual-demo","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"},{"kind":"comment","location":"0x401020","category":"unknown","text":"normal reverse engineering note"}]}}
```

Run:

```powershell
.\build-trim-gui\src\safety_gateway\Release\aura-safety-gateway.exe --once .scratch\safety-gateway-demo-request.json --compact
```

Expected:
- JSON contains `"decision":"pass"`.
- JSON contains `"masked_count":1`.
- JSON does not contain `alice.smith@example.com`.
- JSON contains at least one `*`.

- [ ] **Step 4: Commit**

```powershell
git add CMakeLists.txt src/safety_gateway tests/unit/safety_gateway tests/integration/safety_gateway_smoke src/mcp tests/integration/mcp_smoke
git commit -m "feat: add standalone safety gateway exe"
```

Do not add `.scratch/mcp-reference/`.

---

## Scope Explicitly Deferred

- Full stateful Streamable HTTP sessions with resumability.
- Legacy SSE endpoint compatibility.
- Replacing existing `aura-mcp` internals as default path.
- Live malware execution or live malware download.
- New RE analysis features.
- GUI redesign for the gateway; only status display is allowed later.
- Vendoring official MCP SDK code into product source.

---

## GSTACK REVIEW REPORT

| Phase | Verdict | Findings | Plan Action |
|---|---|---:|---|
| CEO/Product | PASS | 1 | Keep endpoint-first positioning; Safety Gateway is the product surface, not another RE mode. |
| Design | PASS_WITH_NOTES | 1 | No GUI work in this slice; add clear endpoint/cache/port docs for demo and setup. |
| Engineering | PASS_WITH_REQUIRED_CHANGES | 4 | Add MCP handshake, JSON-RPC id preservation, cache DB ownership, and non-loopback bind guard. |
| DX | PASS_WITH_REQUIRED_CHANGES | 3 | Add exact commands, failure messages, and smoke tests for `--serve`, `--once`, cache path, and route. |

### CEO/Product Review

What was examined:
- User requirement that official MCP clients point their endpoint URL at the gateway.
- Requirement that the first inbound data is filtered, checked, cached, then passed.
- AURA project identity as a protected LLM gateway rather than a new RE engine.

Finding:
- The plan is correctly focused on a distinct product surface: `aura-safety-gateway.exe`. This is stronger for the graduation demo than saying “AURA has another MCP command,” because the user-visible setup becomes one URL: `http://127.0.0.1:8765/mcp`.

Decision:
- Keep `aura-safety-gateway.exe` as a standalone endpoint and do not make `aura-mcp` internal relay the primary path.

### Design Review

What was examined:
- Whether this plan needs GUI work.
- Whether endpoint/cache choices are understandable to a demo user.

Finding:
- GUI is not the first slice. The demo explanation should show a simple gateway configuration card or command snippet rather than a new settings screen. A GUI screen can be added after the EXE is real.

Decision:
- Keep GUI deferred. Add `docs/demo/SAFETY_GATEWAY_MCP_ENDPOINT.md` in Task 6 so the command, cache DB, input port, and upstream URL are explainable.

### Engineering Review

What was examined:
- Existing `src/mcp` CMake and MCP tool structure.
- Existing `aura_core` gateway/safety code.
- Official MCP Streamable HTTP shape.
- Windows localhost executable constraints.

Findings:
1. The HTTP endpoint cannot be only a raw POST JSON wrapper. Official MCP clients expect `initialize`, `tools/list`, and `tools/call` to behave like JSON-RPC MCP methods.
2. The first draft hardcoded response `id: 1`; this breaks multi-request clients. The plan now requires preserving request IDs.
3. Non-loopback binding is risky for a tool that processes reverse-engineering context. The plan now defaults to `127.0.0.1` and requires `--allow-remote-bind` for external binds.
4. Cache path is user-managed, which is correct. The cache key must include `policy_hash` so changing detection/filtering rules does not silently reuse stale protected decisions.

Decisions:
- Add `mcp_http.h/.cpp` as a small protocol handler instead of mixing JSON-RPC logic into `main.cpp`.
- Keep session/resumability deferred but do not design against it.
- Keep raw original text out of cache by default.

### DX Review

What was examined:
- Commands a user must run.
- MCP client configuration.
- Test evidence required before implementation is called complete.

Findings:
1. The plan now has copy-pasteable commands for `--once`, `--serve`, `--cache`, `--listen-port`, and `--upstream-url`.
2. Smoke tests must verify no raw original value appears in process output, not just that the process exits `0`.
3. Failure mode for `0.0.0.0` without `--allow-remote-bind` must be a stable JSON error so the user can understand why the server did not start.

Decision:
- Add port/security tests in Task 6 and keep `safety_gateway_smoke` as the evidence gate.

### Autoplan Final Decision

Proceed with implementation after this plan. No user-challenge remains.

Implementation order should be:

1. Request parser and response serializer.
2. Cache and policy evaluator.
3. `--once` EXE.
4. MCP HTTP `initialize` and `tools/list`.
5. MCP HTTP `tools/call` protection.
6. Port/security tests.
7. Optional stdio compatibility.

Official references checked during review:
- MCP Streamable HTTP transport specification: https://modelcontextprotocol.io/specification/2025-11-25/basic/transports
- MCP TypeScript SDK server documentation: https://ts.sdk.modelcontextprotocol.io/documents/server.html
- MCP C# SDK transport documentation: https://csharp.sdk.modelcontextprotocol.io/concepts/transports/transports.html

---

## Self-Review

- Spec coverage:
  - Standalone EXE: Task 4.
  - MCP middle gateway role: Tasks 6 and 7.
  - Safety Assets protection layer: Tasks 3 and 7.
  - Official/high-star references: Task 1.
  - No RE mode expansion: Requirements and deferred scope.
  - Testable output: Tasks 5 and 8.
- Placeholder scan:
  - No `TBD` or “implement later” language remains in implementation tasks.
  - Deferred scope is explicit and not required for the first shippable slice.
- Type consistency:
  - `GatewayRequest`, `GatewayResponse`, `parseGatewayRequest`, `gatewayResponseToJson`, and `evaluateGatewayRequest` are defined before use.
  - CMake target names match the commands: `aura-safety-gateway`, `safety_gateway_unit`, `safety_gateway_smoke`.
  - `aura_safety_gateway_core` is created before unit tests link against it, and `mcp_http.cpp` is added to the target only in the MCP HTTP task.
