# Safety Gateway Part 1 Follow-up Fixes Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use `superpowers:subagent-driven-development` or `superpowers:executing-plans` to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Close the three Part 1 review findings that currently prevent Safety Gateway Web Console from being considered complete.

**Architecture:** Keep the fixes inside the existing Part 1 gateway code. The gateway must scan every string that can be forwarded, report block decisions consistently, and only override persisted listen settings when the CLI user explicitly supplied listen flags.

**Tech Stack:** C++17, cJSON, existing `aura_safety_gateway_core`, doctest unit tests, existing Windows smoke test.

---

## Review Status

CEO review result: approved with `HOLD SCOPE`.

- Keep this as a Part 1 completion fix.
- Do not expand into Part 2 Policy Studio.
- Do not expand into Part 3 Operations/Audit.
- Product reason: a gateway cannot be trusted until forwarded payloads are fully protected, block decisions are accurate, and saved port settings actually work.

CSO review result: approved after security requirements were added.

- Do not scan/rewrite gateway control fields.
- Do not rely on fragile global string traversal order for supplemental fields.
- Use payload array order for `payload.items[].text`.
- Use exact JSON path mapping for supplemental user/tool-data fields.
- Verify raw values are absent from `protected_forward_body` and request log output.

Execution decision: proceed with this plan before any Part 2 or Part 3 work.

---

## Scope

This plan fixes only Part 1 correctness bugs.

In scope:

- Scan every user/tool-data string under `params.arguments` for `aura_gateway_protect_context`, even when `payload.items` parses successfully.
- Exclude gateway control/schema fields from scan and rewrite: `request_id`, `source`, `operation`, `payload.items[].kind`, `payload.items[].location`, `payload.items[].category`.
- Ensure the protected forward body cannot contain unscanned extra strings, while preserving all control/schema fields.
- Set top-level `GatewayResponse.decision` to `block` when any item is blocked as a hard secret.
- Preserve saved listen host/port on restart unless CLI flags are explicitly provided.
- Add tests for all three review findings.

Out of scope:

- Part 2 Policy Studio.
- Part 3 Operations/Audit.
- New persistent vault behavior.
- Qt port.

---

## File Structure

- Modify `src/safety_gateway/mcp_http.cpp`
  - Add explicit candidate collection for rewritable gateway-tool argument strings.
  - Preserve gateway control/schema fields during scanning and forward-body replacement.
  - Ensure forward-body replacement uses candidate path mapping, not fragile scan-order assumptions.

- Modify `src/safety_gateway/gateway_policy.cpp`
  - Set top-level `response.decision = "block"` when a hard-secret finding is blocked.

- Modify `src/safety_gateway/main.cpp`
  - Track whether `--listen-host` and `--listen-port` were supplied.
  - Override loaded config only when those flags are present.

- Modify `tests/unit/safety_gateway/safety_gateway_unit.cpp`
  - Add/adjust unit tests for extra gateway-tool strings, hard-secret decision, and loaded listen config override behavior where possible.

- Modify `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`
  - Add a smoke case if unit tests cannot cover the restart/listen behavior.

---

## Task 1: Scan Supplemental Strings In Gateway Tool Requests

**Files:**

- Modify: `src/safety_gateway/mcp_http.cpp`
- Test: `tests/unit/safety_gateway/safety_gateway_unit.cpp`

- [ ] **Step 1: Write the failing unit test**

Add this test to `tests/unit/safety_gateway/safety_gateway_unit.cpp`:

```cpp
TEST_CASE("mcp gateway tool also protects supplemental argument strings") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-gateway-extra.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();

    const auto detailed = aura::safety_gateway::handleMcpJsonRpcDetailed(
        R"({"jsonrpc":"2.0","id":"gateway-extra","method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"gateway-extra","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"payload","category":"unknown","text":"safe payload text"}]},"metadata":{"owner_email":"alice.smith@example.com"},"note":"call me at 010-1234-5678"}}}})",
        options);

    CHECK(detailed.has_request_log);
    CHECK(detailed.request_log.decision == "masked");
    CHECK(detailed.protected_forward_body.find("alice.smith@example.com") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("010-1234-5678") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("*") != std::string::npos);
    CHECK(detailed.request_log.items.size() >= 3);
    CHECK(detailed.protected_forward_body.find("\"request_id\":\"gateway-extra\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"source\":\"mcp\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"operation\":\"protect_context\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"kind\":\"string\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"location\":\"payload\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"category\":\"unknown\"") != std::string::npos);
}
```

- [ ] **Step 2: Run the unit test and verify it fails**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit" --output-on-failure
```

Expected before implementation:

- The new test fails because `owner_email` and/or `note` remains raw in `protected_forward_body`, because request log item count does not include supplemental strings, or because control/schema fields are accidentally changed.

- [ ] **Step 3: Add explicit candidate classification**

In `src/safety_gateway/mcp_http.cpp`, add a local candidate type near the existing JSON traversal helpers:

```cpp
struct JsonStringCandidate {
    std::string location;
    std::string text;
    bool rewritable = false;
};
```

Add path helpers:

```cpp
bool isPayloadItemTextPath(const std::string& path) {
    constexpr const char* kSuffix = ".text";
    return path.find("params.arguments.payload.items[") == 0 &&
           path.size() >= std::strlen(kSuffix) &&
           path.rfind(kSuffix) == path.size() - std::strlen(kSuffix);
}

bool isGatewayControlPath(const std::string& path) {
    if (path == "params.arguments.request_id" ||
        path == "params.arguments.source" ||
        path == "params.arguments.operation") {
        return true;
    }
    if (path.find("params.arguments.payload.items[") == 0) {
        constexpr const char* kKind = ".kind";
        constexpr const char* kLocation = ".location";
        constexpr const char* kCategory = ".category";
        return (path.size() >= std::strlen(kKind) &&
                path.rfind(kKind) == path.size() - std::strlen(kKind)) ||
               (path.size() >= std::strlen(kLocation) &&
                path.rfind(kLocation) == path.size() - std::strlen(kLocation)) ||
               (path.size() >= std::strlen(kCategory) &&
                path.rfind(kCategory) == path.size() - std::strlen(kCategory));
    }
    return false;
}
```

Add a candidate collector that skips control fields and records only rewritable strings:

```cpp
void collectRewritableArgumentStrings(cJSON* node,
                                      const std::string& path,
                                      std::vector<JsonStringCandidate>* candidates) {
    if (!node || !candidates) return;
    if (cJSON_IsString(node) && node->valuestring && node->valuestring[0]) {
        if (!isGatewayControlPath(path)) {
            JsonStringCandidate candidate;
            candidate.location = path;
            candidate.text = node->valuestring;
            candidate.rewritable = true;
            candidates->push_back(std::move(candidate));
        }
        return;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            collectRewritableArgumentStrings(child,
                                             path.empty() ? key : path + "." + key,
                                             candidates);
        }
        return;
    }
    if (cJSON_IsArray(node)) {
        int index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++index) {
            collectRewritableArgumentStrings(child,
                                             path + "[" + std::to_string(index) + "]",
                                             candidates);
        }
    }
}
```

- [ ] **Step 4: Refactor gateway-tool parsing to include supplemental strings**

In `src/safety_gateway/mcp_http.cpp`, change `parseGatewayToolOrGenericRequest(...)` so successful `parseGatewayRequest(...)` does not return immediately. Instead:

```cpp
if (tool_name == "aura_gateway_protect_context" && cJSON_IsObject(arguments)) {
    char* raw_arguments = cJSON_PrintUnformatted(arguments);
    std::string argument_json = raw_arguments ? raw_arguments : "{}";
    cJSON_free(raw_arguments);
    if (parseGatewayRequest(argument_json, gateway_request, parse_error)) {
        std::vector<JsonStringCandidate> candidates;
        collectRewritableArgumentStrings(arguments, "params.arguments", &candidates);
        for (auto& candidate : candidates) {
            if (!isPayloadItemTextPath(candidate.location)) {
                GatewayPayloadItem item;
                item.kind = "json_string";
                item.location = candidate.location;
                item.category = "unknown";
                item.text = std::move(candidate.text);
                gateway_request->items.push_back(std::move(item));
            }
        }
        return true;
    }
}
```

This keeps the existing gateway schema behavior while adding extra argument strings to the same scan/evaluation pipeline.

- [ ] **Step 5: Refactor forward replacement to use candidate path mapping**

In `src/safety_gateway/mcp_http.cpp`, add a helper that rewrites only exact candidate paths:

```cpp
bool replaceStringAtPath(cJSON* node,
                         const std::string& current_path,
                         const std::string& wanted_path,
                         const std::string& protected_value) {
    if (!node) return false;
    if (current_path == wanted_path && cJSON_IsString(node)) {
        cJSON_SetValuestring(node, protected_value.c_str());
        return true;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            if (replaceStringAtPath(child,
                                    current_path.empty() ? key : current_path + "." + key,
                                    wanted_path,
                                    protected_value)) {
                return true;
            }
        }
    }
    if (cJSON_IsArray(node)) {
        int index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++index) {
            if (replaceStringAtPath(child,
                                    current_path + "[" + std::to_string(index) + "]",
                                    wanted_path,
                                    protected_value)) {
                return true;
            }
        }
    }
    return false;
}
```

Then update `protectedForwardBody(...)` in two phases:

1. Replace `payload.items[].text` by payload array order for the original gateway payload items.
2. Replace supplemental items by exact JSON path for entries whose location starts with `params.arguments.`.

```cpp
size_t response_index = 0;
if (cJSON_IsArray(items)) {
    const int count = cJSON_GetArraySize(items);
    for (int i = 0; i < count && response_index < gateway_response.items.size(); ++i) {
        cJSON* row = cJSON_GetArrayItem(items, i);
        if (cJSON_IsObject(row)) {
            replaceJsonString(row, "text", gateway_response.items[response_index].protected_text);
            ++response_index;
        }
    }
}

for (; response_index < gateway_response.items.size(); ++response_index) {
    const auto& item = gateway_response.items[response_index];
    if (item.location.find("params.arguments.") == 0) {
        replaceStringAtPath(arguments,
                            "params.arguments",
                            item.location,
                            item.protected_text);
    }
}
return printJson(copy.get());
```

This keeps payload item order stable even when multiple payload rows share the same display `location`, while supplemental fields use exact JSON-path mapping. Control/schema fields remain excluded from both scan and rewrite.

- [ ] **Step 6: Add a control-field preservation assertion for generic tool calls**

Extend the existing generic tool-call test in `tests/unit/safety_gateway/safety_gateway_unit.cpp`:

```cpp
CHECK(detailed.protected_forward_body.find("\"name\":\"demo_external_tool\"") != std::string::npos);
CHECK(detailed.protected_forward_body.find("\"query\"") != std::string::npos);
CHECK(detailed.protected_forward_body.find("\"nested\"") != std::string::npos);
```

- [ ] **Step 7: Run the test and verify it passes**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit" --output-on-failure
```

Expected:

- `mcp gateway tool also protects supplemental argument strings` passes.
- Existing generic MCP argument protection test still passes.

---

## Task 2: Mark Hard Secret Responses As Blocked

**Files:**

- Modify: `src/safety_gateway/gateway_policy.cpp`
- Test: `tests/unit/safety_gateway/safety_gateway_unit.cpp`

- [ ] **Step 1: Strengthen the existing hard-secret unit test**

In `TEST_CASE("safety gateway uses core safety rules for API keys")`, add:

```cpp
CHECK(response.decision == "block");
```

Keep the existing assertions:

```cpp
CHECK(response.blocked_count == 1);
CHECK(response.items[0].action == "block");
```

- [ ] **Step 2: Run the unit test and verify it fails**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_unit
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit" --output-on-failure
```

Expected before implementation:

- The hard-secret test fails because `response.decision` is still `pass`.

- [ ] **Step 3: Set top-level decision when hard secret blocks**

In `src/safety_gateway/gateway_policy.cpp`, inside the `if (hard_secret)` branch:

```cpp
if (hard_secret) {
    response.decision = "block";
    response.blocked_count += 1;
} else {
    response.masked_count += 1;
}
```

- [ ] **Step 4: Verify CLI once mode returns blocked exit code**

Add or adjust a smoke assertion in `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`:

```cpp
TEST_CASE("aura-safety-gateway once mode exits nonzero for hard secret block") {
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const fs::path request = fs::temp_directory_path() / "aura-safety-gateway-secret-request.json";
    {
        std::ofstream out(request);
        out << "{\"request_id\":\"secret-smoke\",\"source\":\"mcp\",\"operation\":\"protect_context\","
            << "\"payload\":{\"items\":[{\"kind\":\"string\",\"location\":\"demo\","
            << "\"category\":\"unknown\",\"text\":\"api_key = \\\"sk-DEMOSECRET1234567890\\\"\"}]}}";
    }

    const std::string command =
        popenCommand(bin, {"--once", request.string(), "--compact"});
    FILE* pipe = AURA_POPEN(command.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::ostringstream ss;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        ss << buffer;
    }
    const int rc = AURA_PCLOSE(pipe);
    CHECK(rc != 0);

    const std::string output = ss.str();
    CHECK(output.find("\"decision\":\"block\"") != std::string::npos);
    CHECK(output.find("sk-DEMOSECRET1234567890") == std::string::npos);
}
```

- [ ] **Step 5: Run unit and smoke tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-safety-gateway safety_gateway_unit safety_gateway_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit|safety_gateway_smoke" --output-on-failure
```

Expected:

- Hard-secret unit test passes.
- Once-mode hard-secret smoke test passes.

---

## Task 3: Respect Persisted Listen Host And Port

**Files:**

- Modify: `src/safety_gateway/main.cpp`
- Test: `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp`

- [ ] **Step 1: Add CLI flag tracking variables**

In `src/safety_gateway/main.cpp`, near current CLI variables:

```cpp
bool has_listen_host = false;
bool has_listen_port = false;
```

- [ ] **Step 2: Set tracking variables during argument parse**

Change argument parsing:

```cpp
} else if (arg == "--listen-host" && i + 1 < argc) {
    listen_host = argv[++i];
    has_listen_host = true;
} else if (arg == "--listen-port" && i + 1 < argc) {
    if (!parsePort(argv[++i], &listen_port)) {
        return emitError("invalid_port", "listen port must be between 1 and 65535");
    }
    has_listen_port = true;
}
```

- [ ] **Step 3: Override loaded config only when flags are present**

Replace:

```cpp
config.remote.listen_host = listen_host;
config.remote.port = static_cast<uint16_t>(listen_port);
```

with:

```cpp
if (has_listen_host) {
    config.remote.listen_host = listen_host;
}
if (has_listen_port) {
    config.remote.port = static_cast<uint16_t>(listen_port);
}
```

- [ ] **Step 4: Add restart/listen behavior smoke coverage**

Add a smoke test that creates a temporary working directory, writes `.aura/safety-gateway-config.json` with a non-default port, starts the gateway without `--listen-port`, and verifies it listens on the saved port.

Use this body in `tests/integration/safety_gateway_smoke/safety_gateway_smoke.cpp` under the Windows HTTP smoke section:

```cpp
TEST_CASE("aura-safety-gateway serve mode respects saved listen port") {
#ifndef _WIN32
    MESSAGE("HTTP process smoke currently runs on Windows CI only");
#else
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const int port = 18768;
    const fs::path cwd = fs::temp_directory_path() / "aura-safety-gateway-config-smoke";
    std::error_code ignored;
    fs::remove_all(cwd, ignored);
    fs::create_directories(cwd / ".aura");

    {
        std::ofstream out(cwd / ".aura" / "safety-gateway-config.json");
        out << "{"
            << "\"mode\":\"local_protect_only\","
            << "\"preset\":\"balanced\","
            << "\"cache_db_path\":\"" << (cwd / "cache.sqlite").string() << "\","
            << "\"remote\":{\"enabled\":false,\"listen_host\":\"127.0.0.1\",\"port\":" << port
            << ",\"ip_allowlist\":[\"127.0.0.1\"],\"require_access_token\":true,"
            << "\"access_token_hash\":\"\",\"allow_query_token\":true},"
            << "\"forward\":{\"enabled\":false,\"upstream_url\":\"\",\"timeout_ms\":5000}"
            << "}";
    }

    std::string command =
        std::string("\"") + bin + "\" --serve";
    std::vector<char> mutable_command(command.begin(), command.end());
    mutable_command.push_back('\0');

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    REQUIRE(CreateProcessA(nullptr,
                           mutable_command.data(),
                           nullptr,
                           nullptr,
                           FALSE,
                           CREATE_NO_WINDOW,
                           nullptr,
                           cwd.string().c_str(),
                           &si,
                           &pi));
    try {
        REQUIRE(waitForPort(port));
        const std::string ui = sendHttp(port, "GET", "/ui");
        CHECK(ui.find("Safety Gateway") != std::string::npos);
    } catch (...) {
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        throw;
    }
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
#endif
}
```

- [ ] **Step 5: Run smoke test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_gateway_smoke
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_smoke" --output-on-failure
```

Expected:

- The new saved-port smoke test passes.
- Existing `--listen-port` smoke still passes.

---

## Task 4: Final Regression And Manual Check

**Files:**

- No new files.
- Verify changed files from Tasks 1-3.

- [ ] **Step 1: Run full Part 1 build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target aura-safety-gateway safety_gateway_unit safety_gateway_smoke
```

Expected:

- Build succeeds.

- [ ] **Step 2: Run full Part 1 tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit|safety_gateway_smoke" --output-on-failure
```

Expected:

- `safety_gateway_unit` passes.
- `safety_gateway_smoke` passes.

- [ ] **Step 3: Start foreground or visible demo server**

Run:

```powershell
.\build-trim-gui\src\safety_gateway\Release\aura-safety-gateway.exe --serve --ui --listen-host 127.0.0.1 --listen-port 8765
```

Expected stderr:

```text
aura-safety-gateway listening on http://127.0.0.1:8765/mcp and http://127.0.0.1:8765/ui
```

- [ ] **Step 4: Manual HTTP check for supplemental strings**

In another PowerShell:

```powershell
$body = '{"jsonrpc":"2.0","id":"gateway-extra-live","method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"gateway-extra-live","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"payload","category":"unknown","text":"safe payload text"}]},"metadata":{"owner_email":"alice.smith@example.com"},"note":"call me at 010-1234-5678"}}}}'
$r = Invoke-RestMethod -Uri "http://127.0.0.1:8765/mcp" -Method Post -ContentType "application/json" -Body $body
$log = Invoke-RestMethod -Uri "http://127.0.0.1:8765/api/requests/gateway-extra-live"
($log | ConvertTo-Json -Compress).Contains("alice.smith@example.com")
($log | ConvertTo-Json -Compress).Contains("010-1234-5678")
```

Expected:

```text
False
False
```

- [ ] **Step 5: Manual UI check**

Open:

```text
http://127.0.0.1:8765/ui
```

Expected:

- Request appears in Live Gateway Monitor.
- Request Inspector shows `masked`.
- Protected payload does not contain original email or phone.

---

## Completion Criteria

- [ ] `aura_gateway_protect_context` requests scan `payload.items` and supplemental strings.
- [ ] Upstream forward body contains no raw supplemental PII/secret strings.
- [ ] Hard-secret block sets item action and top-level response decision to `block`.
- [ ] `--once` returns nonzero for hard-secret block.
- [ ] Saved listen host/port are respected when CLI flags are absent.
- [ ] CLI flags still override saved listen host/port when explicitly supplied.
- [ ] `safety_gateway_unit` and `safety_gateway_smoke` pass.

---

## Execution Handoff

Plan complete and saved to `docs/superpowers/plans/2026-05-13-safety-gateway-part1-followup-fixes.md`.

Recommended execution:

1. Use `superpowers:subagent-driven-development`.
2. Assign Task 1 to a worker focused only on `mcp_http.cpp` and related unit tests.
3. Assign Task 2 to a worker focused only on `gateway_policy.cpp` and hard-secret tests.
4. Assign Task 3 to a worker focused only on `main.cpp` and listen-port smoke tests.
5. Run final regression from Task 4 in the parent session.

Do not start Part 2 or Part 3 until this follow-up plan passes.

---

## Self-Review

Spec coverage:

- Finding 1 is covered by Task 1.
- Finding 2 is covered by Task 2.
- Finding 3 is covered by Task 3.
- Final manual and regression verification is covered by Task 4.

Placeholder scan:

- This plan does not use `TBD`, `TODO`, `implement later`, or unspecified test instructions.

Type consistency:

- Function names match current code: `handleMcpJsonRpcDetailed`, `parseGatewayRequest`, `collectJsonStrings`, `protectedForwardBody`, `GatewayResponse`, `GatewayConfig`.
- Test paths match current tree.
