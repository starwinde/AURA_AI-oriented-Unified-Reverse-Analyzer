# Safety Gateway Web Console Design

**Date:** 2026-05-13
**Branch:** `codex/safety-gateway-exe-build`
**Product name:** Safety Gateway
**Status:** Design approved for staged planning; implementation not started for this UI slice.

---

## Summary

Safety Gateway is a general MCP/LLM protection gateway. It started from reverse
engineering safety, but the product surface should not be limited to reverse
engineering. The default product language is generic gateway protection; reverse
engineering is one profile/preset among others.

The first UI is a web console served by `aura-safety-gateway.exe`. Web UI stays
the primary implementation target for now because it is faster to debug, easier
to change, and aligns naturally with the existing HTTP gateway endpoint. Qt
porting is explicitly deferred until the web UX proves itself.

---

## Product Positioning

Safety Gateway is not another reverse engineering UI and not just a masking
table. It is a network-visible safety layer between MCP clients, upstream tools,
and LLMs.

Core story:

```text
Client request
  -> Safety Gateway
  -> detection by rules/models/custom filters
  -> policy decision
  -> protected payload
  -> optional upstream MCP forwarding
  -> audit log
```

Default profile set:

- General LLM Safety
- Reverse Engineering
- Source Code Review
- Customer Support Logs
- Demo

Reverse Engineering profile covers strings, decompile output, function names,
comments, hardcoded secrets, and memory-address-adjacent context. It is a first
class demo profile, not the whole product.

---

## Three-Part Delivery Plan

### Part 1: Safety Gateway Web Console

Goal: make the gateway visibly useful and demonstrable.

Included:

- Web UI served by the gateway.
- Live Gateway Monitor as the first screen.
- Request-based and item-based statistics.
- Recent request table.
- Request Inspector with the full 6-step flow.
- Demo fixture buttons.
- Session-only Reveal.
- Cache DB selection.
- Local/Remote mode with port setting.
- Remote access with actual blocking:
  - listen host;
  - port;
  - remote endpoint display;
  - IP allowlist;
  - access token;
  - remote request allow/block audit.
- Access token accepted through:
  - `Authorization: Bearer sg_xxx`;
  - `X-Safety-Gateway-Token: sg_xxx`;
  - URL query token is actually allowed because the user requested it, but it
    must be labeled insecure/demo-compatible and logged as a weaker auth path.
- Upstream MCP forwarding actually implemented:
  - Local Protect Only mode;
  - Forward to Upstream mode;
  - blocked requests never forwarded;
  - masked requests forward only protected payload.
- Basic preset selector only. Full policy editing waits for Part 2.

Excluded from Part 1:

- Full Rule Pack editor.
- Model download workflow.
- Encrypted Vault.
- Cache browser/export/delete.
- Full policy studio.
- Qt port.

### Part 2: Policy Studio

Goal: make the protection behavior user-editable rather than hardcoded.

Included:

- Rule Pack list, enable/disable, validate, apply.
- Rule Pack file edit/create UI.
- Keyword and regex custom filtering rules.
- Policy presets:
  - Strict;
  - Balanced;
  - Demo.
- Per-rule action:
  - allow;
  - mask;
  - block.
- PII model management:
  - model path select;
  - model on/off;
  - download/install workflow.
- Model/rule diagnostics:
  - active;
  - missing;
  - invalid;
  - failed validation.

### Part 3: Operations and Audit

Goal: make the gateway manageable beyond a demo session.

Included:

- Cache DB browser.
- Cache delete/export.
- Log search/export.
- Reveal audit history.
- Remote access history.
- IP allowlist history.
- Token rotation history.
- Encrypted Local Vault for persistent reveal, if still desired.
- Qt port review after the web UI stabilizes.

---

## Part 1 UI Structure

### First Screen: Live Gateway Monitor

Live Gateway Monitor is the landing screen. It answers: what is the gateway
receiving, what is it protecting, what is it blocking, and what is leaving?

Top section:

```text
Safety Gateway
Status: Running
Endpoint: http://127.0.0.1:8765/mcp
Mode: Local / Remote
Profile: General LLM Safety / Reverse Engineering / ...
Upstream: Off / Forwarding to http://127.0.0.1:8780/mcp
Cache DB: D:\aura-cache\demo.sqlite
```

Request decision statistics:

```text
Total Requests | Masked Requests | Blocked Requests | Allowed Requests | Warning Requests
```

Sensitive item statistics:

```text
Total Sensitive Items | Email | Phone | API Key | Secret | Token | URL | Identifier | Custom
```

Recent requests table:

```text
Time | Client | Client IP | Tool | Decision | Sensitive Items | Policy | Route | View
```

### Request Inspector

Clicking a request opens the Inspector.

The Inspector must show six steps:

1. Original Request
2. Detected Sensitive Items
3. Rule / Model Evidence
4. Policy Decision
5. Protected Payload
6. Audit Log

This is the main demo surface. A viewer should understand the gateway by reading
this screen even without hearing the internal implementation explanation.

### Session-Only Reveal

Reveal means temporarily showing an original value that is otherwise masked.
The first implementation is session-only.

Rules:

- Original values are hidden by default.
- Reveal works one item at a time.
- Reveal requires a reason.
- Reveal lasts for a short duration such as 10 seconds.
- Reveal events are audited.
- No bulk reveal.
- Raw original values are not persisted in the cache DB.
- When the gateway process exits, session-only originals disappear.

### Demo Fixture Buttons

Demo fixtures create real gateway requests through the same pipeline used by
MCP traffic. They must not fake rows in the UI.

Buttons:

- Inject Clean Request
- Inject PII Request
- Inject Secret Request
- Inject RE Context Request
- Inject Blocked Request

Flow:

```text
Demo button
  -> /api/demo/inject
  -> gateway protection pipeline
  -> request log record
  -> Live Monitor update
  -> Inspector data available
```

### Remote Access

Remote access is part of Part 1 because the product must behave like a real
gateway, not only a localhost filter.

Settings:

- Local only / Remote enabled toggle.
- Listen host:
  - `127.0.0.1`;
  - `0.0.0.0`;
  - selected LAN IP.
- Port.
- Remote endpoint display.
- Access token on/off.
- Token generate/copy.
- IP allowlist:
  - single IP, such as `192.168.0.44`;
  - CIDR, such as `192.168.0.0/24`.

Token input methods:

- Recommended: `Authorization: Bearer sg_xxx`.
- Compatibility: `X-Safety-Gateway-Token: sg_xxx`.
- Allowed but risky: `/mcp?token=sg_xxx`.

Remote request gate:

```text
request arrives
  -> determine client IP
  -> if remote mode disabled and not loopback: block
  -> if IP allowlist enabled and IP not allowed: block
  -> if token required and token invalid/missing: block
  -> run protection pipeline
  -> forward or respond
  -> audit allow/block reason
```

Remote log:

```text
Time | Client IP | Token State | Allowlist | Decision | Reason
```

### Upstream MCP Forwarding

Two modes are supported in Part 1.

Local Protect Only:

```text
MCP client -> Safety Gateway -> protected result returned
```

Forward to Upstream:

```text
MCP client
  -> Safety Gateway
  -> detection/policy/cache/audit
  -> upstream MCP endpoint receives protected request only
```

Rules:

- Blocked requests are never forwarded.
- Masked requests forward only protected payload.
- Raw original values are not forwarded.
- Upstream errors are visible in request status and audit.

---

## API Surface Needed for Web UI

Part 1 requires these internal routes in addition to `/mcp`:

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

These APIs are local gateway control APIs, not MCP tool APIs.

---

## Error and Visibility Requirements

Every user-visible failure needs a named state:

- `gateway_not_running`
- `port_in_use`
- `remote_bind_requires_opt_in`
- `remote_ip_not_allowed`
- `missing_access_token`
- `invalid_access_token`
- `upstream_unreachable`
- `upstream_error`
- `policy_validation_failed`
- `cache_unavailable`
- `reveal_denied`
- `reveal_expired`

No silent failures are allowed. The Live Monitor and Inspector must show the
reason for block/warning/error states.

---

## Test Requirements

Part 1 tests:

- Web UI static route returns the shell.
- Status/config APIs round-trip.
- Demo fixture inserts a real logged request.
- `/mcp` request creates a request log.
- Request statistics count both requests and sensitive items.
- Inspector payload never includes raw original by default.
- Reveal requires reason and expires.
- Remote request from non-allowlisted IP is blocked.
- Missing/invalid token is blocked.
- `Authorization: Bearer` token is accepted.
- `X-Safety-Gateway-Token` token is accepted.
- URL query token is accepted but marked weak in audit.
- Blocked requests do not forward upstream.
- Masked requests forward protected payload only.
- Upstream failure is visible and audited.

---

## Not in Scope

These are deliberately outside Part 1:

- Full policy editor internals.
- Model download and bootstrap.
- Encrypted persistent reveal vault.
- Multi-user role system.
- SaaS/cloud deployment.
- Qt rewrite.

---

## CEO Review

### Verdict

Proceed, but treat this as a product surface, not a settings panel. The plan is
ambitious enough for a graduation demo and a believable product direction only
if Part 1 ships the Live Monitor plus Inspector as the hero experience. If Part
1 becomes mostly forms and toggles, it will fail the demo even if technically
correct.

### What This Plan Gets Right

- The product name is now clear: Safety Gateway.
- The first screen shows live protection behavior instead of hiding value inside
  configuration.
- Request-level and item-level metrics make the gateway legible.
- Session-only Reveal creates a useful demo while avoiding permanent raw-value
  storage.
- Remote mode with IP allowlist and token turns this into a real gateway.
- Upstream MCP forwarding keeps the architecture honest.
- Web UI first is the right call for iteration speed; Qt can follow once the
  UX is proven.

### CEO-Level Risks

1. **Scope gravity is high.** Part 1 already contains monitor, inspector, demo
   injection, reveal, remote auth, IP allowlist, cache selection, and forwarding.
   This is large. The only way it stays tractable is to make the visual path
   shallow and real: one request pipeline, one log store, one inspector.

2. **Remote mode creates a trust burden.** If the UI says remote is supported
   but token/IP enforcement is partial, the feature is worse than absent. Remote
   controls must be enforced in backend tests, not only shown in UI.

3. **URL query token is strategically weak.** The user explicitly wants it
   actually allowed, so it remains in scope. The plan must label it weak, audit
   its use, and avoid making it the recommended path.

4. **Forwarding can leak if the contract is vague.** The forwarding layer must
   forward a transformed protected request, not replay the original request.
   Tests must include a raw non-disclosure assertion on upstream-received bytes.

5. **The product can become too RE-specific again.** The Reverse Engineering
   profile should be visible, but the page hierarchy should say Safety Gateway
   first and RE profile second.

### Required Adjustments Before Implementation Plan

- Make `RequestLogEntry` the central product object:
  - request id;
  - timestamp;
  - client name;
  - client IP;
  - tool/method;
  - decision;
  - categories;
  - protected payload;
  - route;
  - remote auth result;
  - audit events.
- Define where session-only originals live:
  - memory-only store keyed by request id + item id;
  - not serialized to SQLite;
  - evicted on process exit and after request retention limit.
- Define forwarding output explicitly:
  - original MCP JSON-RPC id preserved;
  - tool arguments replaced with protected arguments;
  - upstream response audited;
  - upstream response shown in Inspector without raw original injection.
- Add a threat model section to the implementation plan:
  - remote attacker without token;
  - allowed IP with missing token;
  - token in URL leaked through logs;
  - malicious oversized request;
  - upstream timeout;
  - reveal abuse.

### Scope Mode

HOLD SCOPE with rigor. The user has already chosen the broad version. Do not
silently reduce it. Do not expand further until Part 1 proves the core product
loop.

### Final Recommendation

Write the implementation plan for Part 1 only. Do not start Part 2 until the
Live Monitor can show a real request entering `/mcp`, being detected, being
masked/blocked/forwarded, and appearing in the Inspector with audit evidence.
