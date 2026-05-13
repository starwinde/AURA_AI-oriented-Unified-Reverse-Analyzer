# Gateway Readiness Status Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Prevent the LLM Gateway from showing `PASS` when safety scanning or masking did not actually run, and make GUI/CLI/MCP report `PASS`, `WARNING`, `NOT_READY`, `DISABLED`, and `FAIL` consistently.

**Architecture:** Extend the shared gateway snapshot contract instead of adding GUI-only special cases. The builder receives explicit safety pipeline state, computes a final readiness status, and emits per-check results that GUI/CLI/MCP render from the same data.

**Tech Stack:** C++17, Qt6, cJSON, CMake, doctest, existing AURA safety/gateway code.

---

## Problem Statement

The current Gateway UI can show:

```text
LLM 전송 상태: PASS
protected_prompt_generated PASS
original_values_not_included PASS
```

even when no masking was executed or no sensitive items were available. That is technically true only for the narrow prompt check, but it is misleading for product/demo use. `PASS` must mean the data passed through the protection pipeline and is safe to send.

The fix is to split:

- **Final readiness status:** Can this snapshot be sent to an LLM under the protection policy?
- **Per-check results:** Which specific checks passed, warned, failed, or were not ready?
- **Finding count:** Were there protected items to process?
- **Safety pipeline state:** Was safety scan enabled, executed, profile applied, and rule packs/model available?

## Status Semantics

Use these final statuses:

| Status | Meaning | LLM send |
|---|---|---|
| `PASS` | Safety pipeline ran, policy was applied, and protected output contains no original sensitive values | Allowed |
| `WARNING` | Safety pipeline ran, but no findings or no active rules make the result weak for demo/security confidence | Allowed only with warning |
| `NOT_READY` | Safety pipeline did not run, cached protection state is missing/stale, or prompt cannot be trusted yet | Block by default |
| `DISABLED` | User intentionally turned safety protection off | Block by default for protected-send mode |
| `FAIL` | Raw original sensitive value appeared in protected output or a protection step failed | Block |

## Non-Negotiable Invariants

The implementation must preserve these invariants across GUI, CLI, and MCP:

| Invariant | Required behavior |
|---|---|
| No false PASS | `PASS` is impossible unless `safety_scan_executed=true`, `safety_profile_applied=true`, `masking_cache_current=true`, `active_rule_count>0`, and `protected_finding_count>0` |
| No item inflation | `GatewayBuildInput::items` contains only actual protected findings, never every scanned string |
| Zero findings is visible | A completed scan with `scanned_string_count>0` and `protected_finding_count=0` is `WARNING`, not `PASS` |
| Missing scan is separate | If no scan ran, status is `NOT_READY`, not `WARNING` |
| Disabled is explicit | If protection is off by user choice, status is `DISABLED`, not `PASS` or `NOT_READY` |
| Rule availability is real | `rule_packs_loaded` and `active_rule_count` come from the same effective rule path used by scanning |
| GUI is demo-readable | Final status uses uppercase user-facing labels, per-check result values use the serialized lowercase status text |

Use these per-check results:

| Result | Meaning |
|---|---|
| `PASS` | This check is satisfied |
| `WARNING` | This check succeeded with a caveat |
| `NOT_READY` | This check lacks required input/state |
| `DISABLED` | This check was intentionally bypassed by settings |
| `FAIL` | This check found a safety violation |

## Files And Responsibilities

**Gateway core**
- Modify: `include/aura/gateway/gateway_snapshot.h`
  - Add final readiness status enum and per-check result struct.
  - Add safety pipeline state and explicit scan/finding counts to `GatewayBuildInput`.
- Modify: `src/core/gateway/gateway_snapshot.cpp`
  - Compute final status from safety state, protected finding count, active rule count, and leakage checks.
  - Emit structured verification rows instead of plain strings.
- Modify: `tests/unit/safety/safety_unit.cpp`
  - Add unit tests for every readiness status.
  - Add a unit test proving “scan executed on benign strings, zero protected findings” is `WARNING`, not `PASS`.

**Safety rule visibility**
- Modify: `include/aura/safety/string_safety.h`
  - Add a public `std::size_t effectiveRuleCount(const SafetyProfile& profile);` helper.
- Modify: `src/core/safety/string_safety.cpp`
  - Implement `effectiveRuleCount()` using the same internal `effectiveRules(profile)` path used by scanning.

**GUI**
- Modify: `src/gui/main_window.cpp`
  - Populate gateway build input with real safety state from current analysis/profile path.
  - Track the last safety scan state separately from protected item count. A scan with zero findings is `WARNING`, not `NOT_READY`.
- Modify: `src/gui/main_window.h`
  - Add runtime fields for the current analysis safety state.
- Modify: `src/gui/gateway_pane.cpp`
  - Render final statuses as Korean labels.
  - Render per-check result values exactly from the snapshot.
  - Show warning/not-ready text when protected items are zero.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Assert no-analysis/no-masking state is not shown as `PASS`.
  - Assert protected-string flow still shows `PASS`.

**CLI/MCP**
- Modify: `src/cli/main.cpp`
  - Serialize new final readiness status and structured checks.
- Modify: `src/mcp/mcp_cli_bridge.cpp`
  - No separate policy logic; continue returning CLI gateway JSON.
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
  - Assert demo protected snapshot is `pass`.
  - Assert real snapshot without protection metadata is `warning` or `not_ready`, not `pass`.
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Assert MCP exposes the same status/check result fields.

## Task 1: Extend Gateway Status Contract

**Files:**
- Modify: `include/aura/gateway/gateway_snapshot.h`
- Modify: `src/core/gateway/gateway_snapshot.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Write failing enum/status tests**

Add this test to `tests/unit/safety/safety_unit.cpp`:

```cpp
TEST_CASE("GatewaySnapshot: readiness and check status text is stable") {
    using namespace aura::gateway;

    CHECK(std::string(gatewayReadinessStatusToText(
              GatewayReadinessStatus::Pass)) == "pass");
    CHECK(std::string(gatewayReadinessStatusToText(
              GatewayReadinessStatus::Warning)) == "warning");
    CHECK(std::string(gatewayReadinessStatusToText(
              GatewayReadinessStatus::NotReady)) == "not_ready");
    CHECK(std::string(gatewayReadinessStatusToText(
              GatewayReadinessStatus::Disabled)) == "disabled");
    CHECK(std::string(gatewayReadinessStatusToText(
              GatewayReadinessStatus::Fail)) == "fail");

    CHECK(std::string(gatewayCheckStatusToText(
              GatewayCheckStatus::Pass)) == "pass");
    CHECK(std::string(gatewayCheckStatusToText(
              GatewayCheckStatus::Warning)) == "warning");
    CHECK(std::string(gatewayCheckStatusToText(
              GatewayCheckStatus::NotReady)) == "not_ready");
    CHECK(std::string(gatewayCheckStatusToText(
              GatewayCheckStatus::Disabled)) == "disabled");
    CHECK(std::string(gatewayCheckStatusToText(
              GatewayCheckStatus::Fail)) == "fail");
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: compile failure because `GatewayReadinessStatus`, `GatewayCheckStatus`, and helper functions do not exist.

- [ ] **Step 3: Add the shared contract**

In `include/aura/gateway/gateway_snapshot.h`, replace the current verification status-only model with:

```cpp
enum class GatewayReadinessStatus {
    Pass,
    Warning,
    NotReady,
    Disabled,
    Fail,
};

enum class GatewayCheckStatus {
    Pass,
    Warning,
    NotReady,
    Disabled,
    Fail,
};

struct GatewayVerificationCheck {
    std::string name;
    GatewayCheckStatus status = GatewayCheckStatus::Pass;
    std::string detail;
};

struct GatewaySafetyState {
    bool protection_enabled = true;
    bool safety_scan_executed = false;
    bool safety_profile_applied = false;
    bool rule_packs_loaded = false;
    bool masking_cache_current = false;
    int scanned_string_count = 0;
    int protected_finding_count = 0;
    int active_rule_count = 0;
};
```

Change `GatewayVerificationReport` to:

```cpp
struct GatewayVerificationReport {
    GatewayReadinessStatus status = GatewayReadinessStatus::NotReady;
    std::vector<GatewayVerificationCheck> checks;
};
```

Add to `GatewayBuildInput`:

```cpp
GatewaySafetyState safety_state;
```

Add function declarations:

```cpp
const char* gatewayReadinessStatusToText(GatewayReadinessStatus status);
const char* gatewayCheckStatusToText(GatewayCheckStatus status);
```

Keep `gatewayVerificationStatusToText()` temporarily only if existing CLI/GUI code still references it during the transition. Remove it after callers are migrated.

- [ ] **Step 4: Implement text helpers**

In `src/core/gateway/gateway_snapshot.cpp`, add switch helpers:

```cpp
const char* gatewayReadinessStatusToText(GatewayReadinessStatus status) {
    switch (status) {
        case GatewayReadinessStatus::Pass:
            return "pass";
        case GatewayReadinessStatus::Warning:
            return "warning";
        case GatewayReadinessStatus::NotReady:
            return "not_ready";
        case GatewayReadinessStatus::Disabled:
            return "disabled";
        case GatewayReadinessStatus::Fail:
            return "fail";
    }
    return "";
}

const char* gatewayCheckStatusToText(GatewayCheckStatus status) {
    switch (status) {
        case GatewayCheckStatus::Pass:
            return "pass";
        case GatewayCheckStatus::Warning:
            return "warning";
        case GatewayCheckStatus::NotReady:
            return "not_ready";
        case GatewayCheckStatus::Disabled:
            return "disabled";
        case GatewayCheckStatus::Fail:
            return "fail";
    }
    return "";
}
```

- [ ] **Step 5: Run tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: enum text test passes; other compile errors may remain in callers and will be handled in Task 2-4.

- [ ] **Step 6: Commit Task 1**

Only commit if the user has allowed commits in this execution session. Otherwise leave changes unstaged.

```powershell
git add include/aura/gateway/gateway_snapshot.h src/core/gateway/gateway_snapshot.cpp tests/unit/safety/safety_unit.cpp
git commit -m "feat: add gateway readiness status contract"
```

## Task 2: Expose Active Rule Count And Compute Readiness Correctly

**Files:**
- Modify: `include/aura/safety/string_safety.h`
- Modify: `src/core/safety/string_safety.cpp`
- Modify: `src/core/gateway/gateway_snapshot.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Add failing active-rule-count and builder tests**

Add these tests to `tests/unit/safety/safety_unit.cpp`:

```cpp
TEST_CASE("SafetyProfile: selected missing rule pack has zero effective rules") {
    aura::safety::SafetyProfile profile;
    profile.rule_pack_selection_mode =
        aura::safety::RulePackSelectionMode::Selected;
    profile.rule_pack_ids = {"missing-rule-pack-for-test"};

    CHECK(aura::safety::effectiveRuleCount(profile) == 0);
}

TEST_CASE("GatewaySnapshot: disabled protection is not pass") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = false;

    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::Disabled);
    REQUIRE(snapshot.verification.checks.size() >= 1);
    CHECK(snapshot.verification.checks[0].status ==
          GatewayCheckStatus::Disabled);
}

TEST_CASE("GatewaySnapshot: missing safety scan is not ready") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = true;
    input.safety_state.safety_scan_executed = false;

    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::NotReady);
}

TEST_CASE("GatewaySnapshot: scan with no findings is warning not pass") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = true;
    input.safety_state.safety_scan_executed = true;
    input.safety_state.safety_profile_applied = true;
    input.safety_state.rule_packs_loaded = true;
    input.safety_state.masking_cache_current = true;
    input.safety_state.scanned_string_count = 1;
    input.safety_state.protected_finding_count = 0;
    input.safety_state.active_rule_count = 1;

    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::Warning);
    CHECK(snapshot.prompt.included_items == 0);
    CHECK(snapshot.protected_items.empty());
}

TEST_CASE("GatewaySnapshot: scanned benign item is not treated as protected") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = true;
    input.safety_state.safety_scan_executed = true;
    input.safety_state.safety_profile_applied = true;
    input.safety_state.rule_packs_loaded = true;
    input.safety_state.masking_cache_current = true;
    input.safety_state.scanned_string_count = 1;
    input.safety_state.protected_finding_count = 0;
    input.safety_state.active_rule_count = 1;

    // Intentionally do not push input.items. Gateway items represent actual
    // protected findings, not every scanned benign string.
    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::Warning);
    CHECK(snapshot.protected_items.empty());
    CHECK(snapshot.prompt.included_items == 0);
}

TEST_CASE("GatewaySnapshot: protected finding produces pass") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = true;
    input.safety_state.safety_scan_executed = true;
    input.safety_state.safety_profile_applied = true;
    input.safety_state.rule_packs_loaded = true;
    input.safety_state.masking_cache_current = true;
    input.safety_state.scanned_string_count = 1;
    input.safety_state.protected_finding_count = 1;
    input.safety_state.active_rule_count = 1;
    input.items.push_back({"string",
                           "0x401000",
                           "korean_rrn",
                           "900101-1234567",
                           "900101-1******",
                           "900101-1******",
                           "KR_RRN_1"});

    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::Pass);
    CHECK(snapshot.prompt.included_items == 1);
}

TEST_CASE("GatewaySnapshot: raw original leak produces fail") {
    using namespace aura::gateway;
    GatewayBuildInput input;
    input.safety_state.protection_enabled = true;
    input.safety_state.safety_scan_executed = true;
    input.safety_state.safety_profile_applied = true;
    input.safety_state.rule_packs_loaded = true;
    input.safety_state.masking_cache_current = true;
    input.safety_state.scanned_string_count = 1;
    input.safety_state.protected_finding_count = 1;
    input.safety_state.active_rule_count = 1;
    input.items.push_back({"string",
                           "0x401000",
                           "korean_rrn",
                           "900101-1234567",
                           "900101-1234567",
                           "900101-1234567",
                           "KR_RRN_1"});

    const GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    CHECK(snapshot.verification.status == GatewayReadinessStatus::Fail);
    CHECK(snapshot.prompt.blocked_items == 1);
}
```

- [ ] **Step 2: Run failing tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: failures because builder still only emits pass/fail and plain checks.

- [ ] **Step 3: Add active rule count helper**

In `include/aura/safety/string_safety.h`, add:

```cpp
std::size_t effectiveRuleCount(const SafetyProfile& profile);
```

In `src/core/safety/string_safety.cpp`, implement:

```cpp
std::size_t effectiveRuleCount(const SafetyProfile& profile) {
    return effectiveRules(profile).size();
}
```

This must use the same effective rule path as `scanStringWithRulePacks()`. Do not infer rule availability from `rule_pack_selection_mode`.

- [ ] **Step 4: Add a check helper**

In `src/core/gateway/gateway_snapshot.cpp`, add:

```cpp
void addCheck(GatewaySnapshot& snapshot,
              std::string name,
              GatewayCheckStatus status,
              std::string detail) {
    snapshot.verification.checks.push_back(
        GatewayVerificationCheck{std::move(name),
                                 status,
                                 std::move(detail)});
}
```

- [ ] **Step 5: Replace final readiness calculation**

At the end of `buildGatewaySnapshot()`, compute checks in this order:

```cpp
const auto& state = input.safety_state;

if (!state.protection_enabled) {
    snapshot.verification.status = GatewayReadinessStatus::Disabled;
    addCheck(snapshot,
             "protection_enabled",
             GatewayCheckStatus::Disabled,
             "string protection is disabled by user settings");
    return snapshot;
}

addCheck(snapshot,
         "protection_enabled",
         GatewayCheckStatus::Pass,
         "string protection is enabled");

if (!state.safety_scan_executed) {
    snapshot.verification.status = GatewayReadinessStatus::NotReady;
    addCheck(snapshot,
             "safety_scan_executed",
             GatewayCheckStatus::NotReady,
             "safety scan has not run for the current analysis");
    return snapshot;
}

addCheck(snapshot,
         "safety_scan_executed",
         GatewayCheckStatus::Pass,
         "safety scan ran for the current analysis");

if (!state.safety_profile_applied) {
    snapshot.verification.status = GatewayReadinessStatus::NotReady;
    addCheck(snapshot,
             "safety_profile_applied",
             GatewayCheckStatus::NotReady,
             "safety profile was not applied");
    return snapshot;
}

addCheck(snapshot,
         "safety_profile_applied",
         GatewayCheckStatus::Pass,
         "safety profile was applied");

if (!state.rule_packs_loaded) {
    snapshot.verification.status = GatewayReadinessStatus::Warning;
    addCheck(snapshot,
             "rule_packs_loaded",
             GatewayCheckStatus::Warning,
             "no active rule pack was loaded");
} else {
    addCheck(snapshot,
             "rule_packs_loaded",
             GatewayCheckStatus::Pass,
             "active rule packs were loaded");
}

if (state.active_rule_count <= 0) {
    snapshot.verification.status = GatewayReadinessStatus::Warning;
    addCheck(snapshot,
             "active_rule_count",
             GatewayCheckStatus::Warning,
             "effective safety rule count is zero");
} else {
    addCheck(snapshot,
             "active_rule_count",
             GatewayCheckStatus::Pass,
             "effective safety rule count is non-zero");
}

if (!state.masking_cache_current) {
    snapshot.verification.status = GatewayReadinessStatus::NotReady;
    addCheck(snapshot,
             "masking_cache_current",
             GatewayCheckStatus::NotReady,
             "masking cache is missing or stale");
    return snapshot;
}

addCheck(snapshot,
         "masking_cache_current",
         GatewayCheckStatus::Pass,
         "masking cache is current for this analysis");

if (snapshot.prompt.blocked_items > 0) {
    snapshot.verification.status = GatewayReadinessStatus::Fail;
    addCheck(snapshot,
             "original_values_not_included",
             GatewayCheckStatus::Fail,
             "raw original values were rejected before protected output");
    return snapshot;
}

addCheck(snapshot,
         "protected_prompt_generated",
         GatewayCheckStatus::Pass,
         "protected prompt was generated");
addCheck(snapshot,
         "original_values_not_included",
         GatewayCheckStatus::Pass,
         "no known original sensitive value is present in the prompt");

if (state.protected_finding_count <= 0 &&
    snapshot.verification.status != GatewayReadinessStatus::NotReady) {
    snapshot.verification.status = GatewayReadinessStatus::Warning;
    addCheck(snapshot,
             "protected_items_present",
             GatewayCheckStatus::Warning,
             "safety scan ran but no protected findings were found");
} else if (snapshot.verification.status != GatewayReadinessStatus::Warning) {
    snapshot.verification.status = GatewayReadinessStatus::Pass;
    addCheck(snapshot,
             "protected_items_present",
             GatewayCheckStatus::Pass,
             "protected items are available for the prompt");
}
```

During this step, remove the old `checks.push_back("protected_prompt_generated")` and `failures.push_back(...)` logic. Raw original failures should be represented by a `GatewayVerificationCheck` with `Fail`.

- [ ] **Step 6: Run safety tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: all gateway readiness unit tests pass.

- [ ] **Step 7: Commit Task 2**

Only commit if commits are allowed in the session.

```powershell
git add include/aura/safety/string_safety.h src/core/safety/string_safety.cpp src/core/gateway/gateway_snapshot.cpp tests/unit/safety/safety_unit.cpp
git commit -m "fix: prevent false pass gateway readiness"
```

## Task 3: Serialize New Status In CLI/MCP JSON

**Files:**
- Modify: `src/cli/main.cpp`
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add failing CLI JSON assertions**

In `tests/integration/cli_smoke/cli_smoke.cpp`, update the gateway demo test to assert:

```cpp
const cJSON *verification = cJSON_GetObjectItem(gateway, "verification");
REQUIRE(cJSON_IsObject(verification));
CHECK(get_string(verification, "status") == "pass");
const cJSON *checks = cJSON_GetObjectItem(verification, "checks");
REQUIRE(cJSON_IsArray(checks));
const cJSON *first_check = cJSON_GetArrayItem(checks, 0);
REQUIRE(cJSON_IsObject(first_check));
CHECK(cJSON_IsString(cJSON_GetObjectItem(first_check, "name")));
CHECK(cJSON_IsString(cJSON_GetObjectItem(first_check, "status")));
CHECK(cJSON_IsString(cJSON_GetObjectItem(first_check, "detail")));
```

In the real binary gateway test, assert the status is `warning` when the scan ran but found no protected items, and `pass` only when protected items exist:

```cpp
const cJSON *verification = cJSON_GetObjectItem(gateway, "verification");
REQUIRE(cJSON_IsObject(verification));
const std::string status = get_string(verification, "status");
const cJSON *items = cJSON_GetObjectItem(gateway, "protected_items");
REQUIRE(cJSON_IsArray(items));
if (cJSON_GetArraySize(items) == 0) {
    CHECK(status == "warning");
} else {
    CHECK(status == "pass");
}
```

- [ ] **Step 1b: Add a CLI regression test for benign strings**

Add a focused assertion around the real binary path or a small fixture where no rule matches:

```cpp
// The Gateway must not count every scanned string as a protected item.
// Only strings with actual findings enter protected_items.
if (status == "warning") {
    CHECK(cJSON_GetArraySize(items) == 0);
}
```

This catches the current bug where `build_gateway_input_from_analyze_body()` pushes a gateway item for every string even when `protectedView.findings` is empty.

Also add this assertion to the demo gateway test so demo data proves the positive path:

```cpp
const std::string status = get_string(verification, "status");
CHECK(status == "pass");
const cJSON *items = cJSON_GetObjectItem(gateway, "protected_items");
REQUIRE(cJSON_IsArray(items));
CHECK(cJSON_GetArraySize(items) > 0);
```

- [ ] **Step 2: Add failing MCP assertions**

In `tests/integration/mcp_smoke/mcp_smoke.cpp`, after reading `gateway.verification`, assert:

```cpp
const cJSON* verification =
    cJSON_GetObjectItemCaseSensitive(gateway, "verification");
REQUIRE(cJSON_IsObject(verification));
const cJSON* status =
    cJSON_GetObjectItemCaseSensitive(verification, "status");
REQUIRE(cJSON_IsString(status));
const cJSON* checks =
    cJSON_GetObjectItemCaseSensitive(verification, "checks");
REQUIRE(cJSON_IsArray(checks));
```

- [ ] **Step 3: Run failing CLI/MCP tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: failure because CLI still serializes the old verification shape.

- [ ] **Step 4: Update JSON serialization**

In `src/cli/main.cpp`, update the `GatewayVerificationReport` serializer to emit:

```json
{
  "status": "pass|warning|not_ready|disabled|fail",
  "checks": [
    {
      "name": "safety_scan_executed",
      "status": "pass",
      "detail": "safety scan ran for the current analysis"
    }
  ]
}
```

Use:

```cpp
cJSON_AddStringToObject(verification,
                        "status",
                        aura::gateway::gatewayReadinessStatusToText(
                            snapshot.verification.status));
```

For every check:

```cpp
cJSON* check_json = cJSON_CreateObject();
cJSON_AddStringToObject(check_json, "name", check.name.c_str());
cJSON_AddStringToObject(check_json,
                        "status",
                        aura::gateway::gatewayCheckStatusToText(check.status));
cJSON_AddStringToObject(check_json, "detail", check.detail.c_str());
cJSON_AddItemToArray(checks, check_json);
```

- [ ] **Step 5: Ensure demo input declares safety state**

In the CLI demo gateway builder input, set:

```cpp
input.safety_state.protection_enabled = true;
input.safety_state.safety_scan_executed = true;
input.safety_state.safety_profile_applied = true;
input.safety_state.rule_packs_loaded = true;
input.safety_state.masking_cache_current = true;
input.safety_state.scanned_string_count = 1;
input.safety_state.protected_finding_count = 1;
input.safety_state.active_rule_count = 1;
```

For real binary gateway input, the CLI scans strings immediately while building the snapshot, so set scan state from the attempted scan, not from whether findings were found:

```cpp
input.safety_state.protection_enabled = true;
input.safety_state.safety_scan_executed = true;
input.safety_state.safety_profile_applied = true;
input.safety_state.rule_packs_loaded =
    aura::safety::effectiveRuleCount(safety_profile) > 0;
input.safety_state.masking_cache_current = true;
input.safety_state.active_rule_count =
    static_cast<int>(aura::safety::effectiveRuleCount(safety_profile));
```

This intentionally prevents a real binary with zero protected items from being reported as full `pass`, while still distinguishing “scan ran and found nothing” (`warning`) from “scan never ran” (`not_ready`).

Also change `build_gateway_input_from_analyze_body()` so it only pushes Gateway items for strings with actual protection findings:

```cpp
input.safety_state.scanned_string_count =
    static_cast<int>(body->strings_count);

for (std::size_t i = 0; strings != nullptr && i < body->strings_count; ++i) {
    const std::string original = strings[i].content != nullptr
        ? strings[i].content
        : "";
    auto findings =
        aura::safety::scanStringWithRulePacks(original, safety_profile);
    const auto protected_view = aura::safety::buildProtectedStringView(
        original, std::string(), std::move(findings));

    if (protected_view.findings.empty()) {
        continue;
    }

    input.safety_state.protected_finding_count +=
        static_cast<int>(protected_view.findings.size());

    input.items.push_back({"string",
                           location,
                           protected_view.findings.front().kind,
                           original,
                           protected_view.masked,
                           protected_view.protected_value,
                           protected_view.findings.front().mask_token});
}
```

Do not push benign/unmatched strings into `GatewayBuildInput::items`. Otherwise a scan with zero findings can still become a false `pass`.

- [ ] **Step 6: Run CLI/MCP tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: CLI/MCP tests pass.

- [ ] **Step 7: Commit Task 3**

Only commit if commits are allowed in the session.

```powershell
git add src/cli/main.cpp src/mcp/mcp_cli_bridge.cpp tests/integration/cli_smoke/cli_smoke.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "fix: expose gateway readiness through cli and mcp"
```

## Task 4: Render Clear Readiness In GUI

**Files:**
- Modify: `src/gui/gateway_pane.cpp`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke assertions**

In `tests/integration/gui_smoke/gui_smoke.cpp`, add a subcase for empty/no-masking gateway:

```cpp
SUBCASE("gateway does not show PASS when no protection state exists") {
    window.show();
    QApplication::processEvents();

    auto* status = window.findChild<QLabel*>(
        QStringLiteral("gatewayStatusLabel"));
    REQUIRE(status != nullptr);
    CHECK_FALSE(status->text().contains(QStringLiteral("PASS")));
    CHECK(status->text().contains(QStringLiteral("NOT_READY")) ||
          status->text().contains(QStringLiteral("WARNING")) ||
          status->text().contains(QStringLiteral("대기")));
}
```

Add a separate subcase for clearing protection cache after a protected state:

```cpp
SUBCASE("gateway becomes not ready after protection results are cleared") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(stringFixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE_FALSE(window.stringList().isEmpty());

    int protectedRow = -1;
    for (int i = 0; i < window.stringList().size(); ++i) {
        if (window.stringList()[i].content.size() >= 8) {
            protectedRow = i;
            break;
        }
    }
    REQUIRE(protectedRow >= 0);
    REQUIRE(window.setStringMaskTokenAt(protectedRow,
                                        QStringLiteral("DEMO_MASK")));

    auto* status = window.findChild<QLabel*>(
        QStringLiteral("gatewayStatusLabel"));
    REQUIRE(status != nullptr);
    CHECK(status->text().contains(QStringLiteral("PASS")));

    REQUIRE(window.clearStringProtectionForCurrentBinary());
    CHECK_FALSE(status->text().contains(QStringLiteral("PASS")));
    CHECK(status->text().contains(QStringLiteral("NOT_READY")));
}
```

Update the protected-string subcase to assert:

```cpp
CHECK(status->text().contains(QStringLiteral("PASS")));

auto* verification = window.findChild<QTreeWidget*>(
    QStringLiteral("gatewayVerificationTable"));
REQUIRE(verification != nullptr);
bool sawSafetyScan = false;
for (int row = 0; row < verification->topLevelItemCount(); ++row) {
    const QTreeWidgetItem* item = verification->topLevelItem(row);
    if (item->text(0) == QStringLiteral("safety_scan_executed") &&
        item->text(1) == QStringLiteral("pass")) {
        sawSafetyScan = true;
    }
}
CHECK(sawSafetyScan);
```

- [ ] **Step 2: Run failing GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: failure because GUI currently treats only `Pass/Fail`.

- [ ] **Step 3: Render final status labels**

In `src/gui/gateway_pane.cpp`, replace boolean pass rendering with:

```cpp
QString statusText;
switch (snapshot.verification.status) {
    case aura::gateway::GatewayReadinessStatus::Pass:
        statusText = QStringLiteral("최종 전송 판정: PASS");
        break;
    case aura::gateway::GatewayReadinessStatus::Warning:
        statusText = QStringLiteral("최종 전송 판정: WARNING");
        break;
    case aura::gateway::GatewayReadinessStatus::NotReady:
        statusText = QStringLiteral("최종 전송 판정: NOT_READY");
        break;
    case aura::gateway::GatewayReadinessStatus::Disabled:
        statusText = QStringLiteral("최종 전송 판정: DISABLED");
        break;
    case aura::gateway::GatewayReadinessStatus::Fail:
        statusText = QStringLiteral("최종 전송 판정: FAIL");
        break;
}
m_statusLabel->setText(statusText);
```

Change verification row rendering to use actual per-check statuses:

```cpp
for (const auto& check : snapshot.verification.checks) {
    auto* row = new QTreeWidgetItem();
    row->setText(0, QString::fromStdString(check.name));
    row->setText(1, QString::fromUtf8(
        aura::gateway::gatewayCheckStatusToText(check.status)));
    row->setText(2, QString::fromStdString(check.detail));
    m_verification->addTopLevelItem(row);
}
```

Update the verification table to three columns:

```cpp
m_verification->setColumnCount(3);
m_verification->setHeaderLabels(
    QStringList{QStringLiteral("Check"),
                QStringLiteral("Result"),
                QStringLiteral("Detail")});
```

- [ ] **Step 4: Populate safety state in GUI**

In `src/gui/main_window.h`, add explicit runtime state fields near the other analysis state members:

```cpp
bool m_gatewayProtectionEnabled = true;
bool m_gatewaySafetyScanExecuted = false;
bool m_gatewaySafetyProfileApplied = false;
bool m_gatewayRulePacksLoaded = false;
bool m_gatewayMaskingCacheCurrent = false;
int m_gatewayScannedStringCount = 0;
int m_gatewayProtectedFindingCount = 0;
int m_gatewayActiveRuleCount = 0;
```

In `src/gui/main_window.cpp`, reset these fields in project close/open paths and before a fresh analysis:

```cpp
m_gatewayProtectionEnabled = true;
m_gatewaySafetyScanExecuted = false;
m_gatewaySafetyProfileApplied = false;
m_gatewayRulePacksLoaded = false;
m_gatewayMaskingCacheCurrent = false;
m_gatewayScannedStringCount = 0;
m_gatewayProtectedFindingCount = 0;
m_gatewayActiveRuleCount = 0;
```

In the analysis path that already has `enableStringProtection`, `maskStringProtection`, and `safetyProfile`, set:

```cpp
m_gatewayProtectionEnabled = enableStringProtection;
m_gatewaySafetyScanExecuted = enableStringProtection;
m_gatewaySafetyProfileApplied = enableStringProtection;
m_gatewayRulePacksLoaded =
    enableStringProtection &&
    aura::safety::effectiveRuleCount(safetyProfile) > 0;
m_gatewayMaskingCacheCurrent = enableStringProtection && maskStringProtection;
m_gatewayScannedStringCount = enableStringProtection
    ? static_cast<int>(m_strings.size())
    : 0;
m_gatewayProtectedFindingCount = 0;
for (const auto& s : m_strings) {
    m_gatewayProtectedFindingCount += s.findings.size();
}
m_gatewayActiveRuleCount = enableStringProtection
    ? static_cast<int>(aura::safety::effectiveRuleCount(safetyProfile))
    : 0;
```

If the profile uses `None` or selected packs fail to load, `effectiveRuleCount()` is zero and the final status should become `WARNING` because the scan ran with no active rules. If `enableStringProtection=false`, the final status should be `DISABLED`.

In the existing cache-clear path `clearStringProtectionForCurrentBinary()`, mark the cache stale:

```cpp
m_gatewayMaskingCacheCurrent = false;
```

In `recomputeStringProtectionForCurrentBinary()`, set the runtime state after recompute:

```cpp
m_gatewayProtectionEnabled = true;
m_gatewaySafetyScanExecuted = true;
m_gatewaySafetyProfileApplied = true;
m_gatewayRulePacksLoaded =
    aura::safety::effectiveRuleCount(activeSafetyProfile()) > 0;
m_gatewayMaskingCacheCurrent = true;
m_gatewayScannedStringCount = static_cast<int>(m_strings.size());
m_gatewayProtectedFindingCount = 0;
for (const auto& s : m_strings) {
    m_gatewayProtectedFindingCount += s.findings.size();
}
m_gatewayActiveRuleCount =
    static_cast<int>(aura::safety::effectiveRuleCount(activeSafetyProfile()));
```

In `refreshGatewayPane()`, copy those fields directly into `input.safety_state`:

```cpp
input.safety_state.protection_enabled = m_gatewayProtectionEnabled;
input.safety_state.safety_scan_executed = m_gatewaySafetyScanExecuted;
input.safety_state.safety_profile_applied = m_gatewaySafetyProfileApplied;
input.safety_state.rule_packs_loaded = m_gatewayRulePacksLoaded;
input.safety_state.masking_cache_current = m_gatewayMaskingCacheCurrent;
input.safety_state.scanned_string_count = m_gatewayScannedStringCount;
input.safety_state.protected_finding_count = m_gatewayProtectedFindingCount;
input.safety_state.active_rule_count = m_gatewayActiveRuleCount;
```

Do not infer `safety_scan_executed` from `input.items.empty()`. A scan with zero protected items is a valid `WARNING` state, not `NOT_READY`.

- [ ] **Step 5: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: GUI smoke passes and no-protection state is not displayed as full `PASS`.

- [ ] **Step 6: Commit Task 4**

Only commit if commits are allowed in the session.

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp src/gui/gateway_pane.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "fix: show truthful gateway readiness in gui"
```

## Task 5: Final Verification And Foreground Demo

**Files:**
- No planned source edits after Task 4.

- [ ] **Step 1: Build all relevant targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura aura-gui
```

Expected: build succeeds.

- [ ] **Step 2: Run full focused test set**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected: all tests pass.

- [ ] **Step 3: Launch foreground GUI**

Run:

```powershell
$gui = Join-Path (Get-Location) 'build-trim-gui\src\gui\Release\aura-gui.exe'
Start-Process -FilePath $gui -WorkingDirectory (Get-Location)
```

Expected: AURA GUI opens visibly.

- [ ] **Step 4: Manual GUI demo checks**

Check these states:

1. Open AURA with no analyzed protected strings.
   - Expected: `최종 전송 판정: NOT_READY`, `WARNING`, or `대기`, not `PASS`.
2. Analyze a demo binary with protected strings.
   - Expected: `최종 전송 판정: PASS`.
   - Expected: `safety_scan_executed`, `safety_profile_applied`, `masking_cache_current`, and `original_values_not_included` are `pass`.
3. Disable protection or clear masking cache if the UI path exists.
   - Expected: `DISABLED` or `NOT_READY`, not `PASS`.

## Self-Review

**Spec coverage:** The plan covers false `PASS`, no masking, stale cache, protection disabled, raw leakage failure, GUI labels, CLI JSON, MCP JSON, and tests.

**Placeholder scan:** No `TBD`, unspecified “add tests”, or undefined function names remain. The new names are introduced in Task 1 before later tasks use them.

**Type consistency:** `GatewayReadinessStatus`, `GatewayCheckStatus`, `GatewayVerificationCheck`, and `GatewaySafetyState` are consistently used across core, GUI, CLI, and tests.

## Execution Handoff

Plan complete and saved to `docs/superpowers/plans/2026-05-12-gateway-readiness-status.md`.

Two execution options:

1. **Subagent-Driven (recommended)** - Dispatch a fresh subagent per task, review between tasks, and run focused tests after every task.
2. **Inline Execution** - Execute tasks in this session with checkpoint reviews.
