# Safety Gateway Web Console Part 1 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use `superpowers:subagent-driven-development` or `superpowers:executing-plans` to implement this plan task-by-task.
> Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build the first real product surface for `Safety Gateway`: a web console served by `aura-safety-gateway.exe` that shows live MCP traffic, applies protection policy, optionally forwards protected requests to an upstream MCP server, and gives a clear demo path for masking/blocking/reveal.

**Architecture:** Keep the gateway as a separate executable under `src/safety_gateway/`. Add a small HTTP control API and static web UI inside the same process. Make `RequestLogEntry` the central product object for UI, CLI, logs, and tests.

**Tech Stack:** C++17, existing safety core, existing lightweight HTTP server code, static HTML/CSS/JS embedded into the executable, SQLite cache only for protected/auditable data, memory-only reveal store for originals.

---

## Product Boundary

Part 1 must be a working gateway, not a mock dashboard.

- `/mcp` receives actual JSON-RPC style MCP HTTP requests.
- Gateway inspects text payloads and tool arguments.
- Gateway masks or blocks according to the active preset.
- Gateway records the decision and item-level details.
- Gateway either returns local protected output or forwards protected-only payloads to an upstream MCP endpoint.
- Web UI shows the same request as a six-step flow:
  1. Incoming request
  2. Safety scan
  3. Policy decision
  4. Protected payload
  5. Forward or block
  6. Audit result

Out of scope for Part 1:

- Full rule editing UI.
- PII model download/install UI.
- Persistent original-value vault.
- Qt port.

Those are covered by Part 2 and Part 3.

---

## Data Model

- [ ] Add `src/safety_gateway/request_log.h`.
- [ ] Add `src/safety_gateway/request_log.cpp`.
- [ ] Define `RequestLogEntry` as the canonical UI/API object:

```cpp
struct GatewayItemDecision {
    std::string item_id;
    std::string category;
    std::string action;          // allow | mask | block
    std::string original_preview; // never full original
    std::string protected_value;
    std::string reason;
    double confidence = 0.0;
};

struct GatewayAuditEvent {
    std::string timestamp_iso8601;
    std::string event_type;
    std::string detail;
};

struct RequestLogEntry {
    std::string request_id;
    std::string timestamp_iso8601;
    std::string client_name;
    std::string client_ip;
    std::string method;
    std::string tool_name;
    std::string decision;        // allowed | masked | blocked
    std::string route;           // local_protect_only | forwarded | blocked
    std::string remote_auth_result;
    std::string upstream_status;
    std::string protected_payload_json;
    std::vector<GatewayItemDecision> items;
    std::vector<GatewayAuditEvent> audit_events;
};
```

- [ ] Implement bounded in-memory request log retention.
- [ ] Default retention: latest 500 requests.
- [ ] When retention overflows, evict oldest entries and evict matching reveal originals.
- [ ] Add JSON serialization helpers for the control API.

### Tests

- [ ] Add unit test: request log stores and serializes request id, decision, route, items, and audit events.
- [ ] Add unit test: retention evicts old request entries.
- [ ] Add unit test: retention also evicts reveal originals for evicted entries.

---

## Session-Only Reveal Store

- [ ] Add `src/safety_gateway/session_reveal_store.h`.
- [ ] Add `src/safety_gateway/session_reveal_store.cpp`.
- [ ] Store originals only in process memory.
- [ ] Key originals by `request_id + item_id`.
- [ ] Never write original values to SQLite or plaintext log files.
- [ ] Add TTL and count limit.
- [ ] Default TTL: 10 minutes.
- [ ] Default max reveal originals: 500 items.
- [ ] Reveal requires explicit API call and creates an audit event.
- [ ] Revealed value response includes:

```json
{
  "request_id": "req_...",
  "item_id": "item_...",
  "category": "email",
  "original": "alice.smith@example.com",
  "expires_in_seconds": 600,
  "audit_event_id": "evt_..."
}
```

### Tests

- [ ] Add unit test: original is retrievable before TTL.
- [ ] Add unit test: original is unavailable after expiry.
- [ ] Add unit test: reveal miss returns `reveal_denied`.
- [ ] Add unit test: reveal response does not modify protected payload.

---

## Configuration Model

- [ ] Add `src/safety_gateway/gateway_config.h`.
- [ ] Add `src/safety_gateway/gateway_config.cpp`.
- [ ] Define runtime config:

```cpp
struct GatewayRemoteConfig {
    bool enabled = false;
    std::string listen_host = "127.0.0.1";
    uint16_t port = 8765;
    std::vector<std::string> ip_allowlist = {"127.0.0.1", "::1"};
    bool require_access_token = true;
    std::string access_token_hash;
    bool allow_query_token = true;
};

struct GatewayForwardConfig {
    bool enabled = false;
    std::string upstream_url;
    uint32_t timeout_ms = 5000;
};

struct GatewayConfig {
    std::string mode = "local_protect_only";
    std::string preset = "balanced";
    std::string cache_db_path;
    GatewayRemoteConfig remote;
    GatewayForwardConfig forward;
};
```

- [ ] Load config from `.aura/safety-gateway-config.json` by default.
- [ ] Allow command-line override for listen host, port, cache path, upstream URL, and mode.
- [ ] Save config after `PUT /api/config`.
- [ ] Store access token as a hash, not plaintext.
- [ ] Include config validation with explicit error strings.

### Tests

- [ ] Add unit test: default config is local-only and loopback-only.
- [ ] Add unit test: invalid remote bind without explicit opt-in returns `remote_bind_requires_opt_in`.
- [ ] Add unit test: token is saved hashed.
- [ ] Add unit test: config round-trip preserves cache path, mode, upstream URL, and allowlist.

---

## Remote Access Gate

- [ ] Add `src/safety_gateway/remote_access.h`.
- [ ] Add `src/safety_gateway/remote_access.cpp`.
- [ ] Validate incoming remote requests before policy scan:
  - Client IP must match allowlist.
  - Token must be present when required.
  - Token can be supplied by `Authorization: Bearer ...`.
  - Token can be supplied by `X-Safety-Gateway-Token`.
  - Token can be supplied by `?token=...`, but this must be marked `weak_query_token` in audit.
- [ ] If remote access fails, return a real blocked response and do not forward.
- [ ] Record remote audit events:
  - `remote_allowed`
  - `remote_blocked_ip`
  - `remote_blocked_missing_token`
  - `remote_blocked_invalid_token`
  - `remote_query_token_used`

### Tests

- [ ] Add unit test: allowed IP plus valid bearer token passes.
- [ ] Add unit test: allowed IP plus missing token blocks.
- [ ] Add unit test: disallowed IP blocks even with valid token.
- [ ] Add unit test: query token passes only when enabled and writes weak-token audit event.

---

## MCP Request Processing

- [ ] Update `src/safety_gateway/mcp_http.cpp`.
- [ ] Parse MCP JSON-RPC request id and method.
- [ ] Extract text candidates from:
  - top-level `params`
  - `params.arguments`
  - nested string fields in tool arguments
- [ ] Enforce max request body size before parsing.
- [ ] On oversize request, return `blocked` with `oversized_request`.
- [ ] Use existing safety scanner and active profile for detection.
- [ ] Produce item decisions:
  - no finding: `allow`
  - finding under mask policy: `mask`
  - finding under block policy: `block`
- [ ] Preserve JSON-RPC request id in responses.
- [ ] Generate protected payload JSON with masked values only.
- [ ] Store raw originals only in `SessionRevealStore`.

### Tests

- [ ] Add unit test: JSON-RPC id is preserved.
- [ ] Add unit test: raw email becomes masked in protected payload.
- [ ] Add unit test: raw secret becomes masked or blocked according to preset.
- [ ] Add unit test: protected payload never contains original email/secret.
- [ ] Add unit test: oversize request returns blocked and is not forwarded.

---

## Upstream Forwarding

- [ ] Add `src/safety_gateway/upstream_forwarder.h`.
- [ ] Add `src/safety_gateway/upstream_forwarder.cpp`.
- [ ] Implement HTTP POST forwarding for `http://host:port/path` upstream URLs.
- [ ] Preserve JSON-RPC id.
- [ ] Replace tool arguments with protected arguments before forwarding.
- [ ] Never forward blocked requests.
- [ ] On upstream timeout, return `upstream_timeout` and audit the failure.
- [ ] On upstream HTTP/network error, return `upstream_error` and audit the failure.
- [ ] Show upstream response in UI without reinserting raw originals.

### Tests

- [ ] Add integration smoke with a fake upstream server.
- [ ] Assert upstream receives masked payload, not raw payload.
- [ ] Assert blocked request is not sent to upstream.
- [ ] Assert upstream timeout produces an audited error.

---

## Control API

- [ ] Add `src/safety_gateway/control_api.h`.
- [ ] Add `src/safety_gateway/control_api.cpp`.
- [ ] Add routes:
  - `GET /ui`
  - `GET /api/status`
  - `GET /api/config`
  - `PUT /api/config`
  - `GET /api/stats`
  - `GET /api/requests`
  - `GET /api/requests/{id}`
  - `POST /api/requests/{id}/reveal`
  - `POST /api/demo/inject`
  - `POST /api/remote/token/generate`
  - `GET /api/remote/clients`
- [ ] Return JSON error shape:

```json
{
  "ok": false,
  "error": {
    "code": "missing_access_token",
    "message": "Remote access requires an access token."
  }
}
```

### Tests

- [ ] Add smoke test: `/api/status` returns running status.
- [ ] Add smoke test: `/api/config` round-trips editable fields.
- [ ] Add smoke test: `/api/demo/inject` creates request log entries.
- [ ] Add smoke test: reveal endpoint works for session-only originals.

---

## Web UI

- [ ] Add `src/safety_gateway/ui_assets.h`.
- [ ] Add `src/safety_gateway/ui_assets.cpp`.
- [ ] Serve static HTML/CSS/JS from `/ui`.
- [ ] Use `Safety Gateway` as the product name.
- [ ] Do not brand Part 1 as AURA-first.
- [ ] Visual style can reuse AURA dark theme colors and panel density.
- [ ] First screen layout:
  - Top status bar: mode, listen address, upstream status, cache DB.
  - Stat cards: requests today, masked, blocked, allowed, protected items.
  - Live Gateway Monitor table.
  - Request Inspector.
  - Right-side config panel.
- [ ] Monitor table columns:
  - time
  - client
  - method/tool
  - decision
  - categories
  - route
  - auth
- [ ] Request Inspector tabs:
  - Flow
  - Protected Payload
  - Items
  - Audit
  - Upstream
- [ ] Demo fixture buttons:
  - safe request
  - PII masking request
  - hard secret block request
  - remote token failure request
  - upstream timeout request
- [ ] Reveal UI:
  - reveal button appears per protected item.
  - reveal requires click.
  - reveal result is temporary and visually marked.
  - reveal action is written to audit events.
- [ ] Remote mode UI:
  - Local/Remote toggle.
  - Listen host input.
  - Port input.
  - IP allowlist editor.
  - Token generate button.
  - Token transport guidance: bearer/header recommended, query token weak/demo-compatible.
- [ ] Forwarding UI:
  - Local Protect Only / Forward to Upstream toggle.
  - Upstream URL input.
  - Test upstream button.

### Tests

- [ ] Add GUI/web smoke using HTTP checks for `/ui` content.
- [ ] Assert static UI includes six flow labels.
- [ ] Assert demo buttons are present.
- [ ] Assert `Safety Gateway` appears as the product name.

---

## Threat Model Checks

- [ ] Add explicit tests or smoke cases for:
  - remote attacker without token
  - allowed IP missing token
  - token in URL leaked into audit as weak query token usage
  - oversized request
  - upstream timeout
  - reveal abuse through expired or missing item id

---

## Verification Commands

- [ ] Build:

```powershell
cmake --build build-trim-gui --config Release --target aura-safety-gateway safety_gateway_unit safety_gateway_smoke
```

- [ ] Test:

```powershell
ctest --test-dir build-trim-gui -C Release -R "safety_gateway_unit|safety_gateway_smoke" --output-on-failure
```

- [ ] Manual run:

```powershell
.\build-trim-gui\src\safety_gateway\Release\aura-safety-gateway.exe --listen 127.0.0.1:8765 --ui
```

- [ ] Open:

```text
http://127.0.0.1:8765/ui
```

- [ ] Demo acceptance:
  - Inject PII fixture.
  - UI shows incoming request, detected item, masked protected payload, audit event.
  - Inject hard-secret fixture.
  - UI shows blocked decision.
  - Enable upstream fake server.
  - UI shows forwarded route and upstream received masked payload only.

---

## Completion Criteria

- [ ] A user can run one executable and open `/ui`.
- [ ] The UI shows real gateway traffic, not static samples.
- [ ] Masked and blocked counts come from actual request decisions.
- [ ] Reveal is session-only and audited.
- [ ] Remote mode blocks by IP/token policy.
- [ ] Forward mode sends protected-only payloads to upstream MCP.
- [ ] All Part 1 tests pass.
