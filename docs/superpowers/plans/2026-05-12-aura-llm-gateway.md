# AURA LLM Gateway MVP Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a GUI-first LLM safety gateway that turns Rizin/Ghidra analysis outputs into a protected prompt, verifies that raw sensitive values are not sent, and exposes the same snapshot through CLI/MCP.

**Architecture:** Reuse the existing safety, safe-export, malware-risk, GUI demo, CLI `llm-context`, and MCP surfaces. Add one deterministic gateway model as the shared contract, then render it in GUI, CLI, and MCP instead of duplicating masking logic in each surface.

**Tech Stack:** C++17, C11 where existing modules require it, Qt6 GUI, cJSON, CMake, existing AURA safety rule packs, existing Rizin/Ghidra adapter diagnostics.

---

## Product Boundary

This plan intentionally reframes AURA as an LLM gateway for reverse-engineering outputs, not as a standalone decompiler.

**In scope for this MVP:**
- Rizin/Ghidra source status collection.
- Common gateway snapshot model.
- Sensitive string and secret finding reuse from existing safety code.
- Static malware-risk summary reuse from existing `aura::security::analyzeMalwareRisk`.
- Policy decisions: `allow`, `mask`, `omit`, `block`.
- Protected prompt preview.
- Pre-send verification.
- GUI Gateway dock.
- CLI/MCP gateway JSON.
- GUI smoke tests proving the demo flow is visible.

**Not in scope for this MVP:**
- Claiming Ghidra pseudo-C exists when the current adapter only has raw XML/diagnostics.
- Live malware execution or dynamic sandboxing.
- Full Cutter-equivalent disassembly navigation.
- Real external LLM send by default.
- User-editable policy language.
- New third-party malware scanner.

## Existing Files And Responsibilities

**Core safety and export**
- Modify: `include/aura/safety/safe_export_view.h`
  - Existing minimal safe export item contract.
  - Keep this as a low-level export primitive.
- Modify: `src/core/safety/safe_export_view.cpp`
  - Existing logic that guarantees original values are not included.
  - Use from gateway builder.
- Create: `include/aura/gateway/gateway_snapshot.h`
  - Shared Gateway Snapshot structs and enum text helpers.
- Create: `src/core/gateway/gateway_snapshot.cpp`
  - Builds gateway snapshot, protected prompt, policy decisions, and verification report.
- Modify: `CMakeLists.txt`
  - Add new gateway core source and include path if needed.

**GUI**
- Create: `src/gui/gateway_pane.h`
  - Qt widget interface for Gateway Overview, Protected Prompt, Verification, and Audit Preview.
- Create: `src/gui/gateway_pane.cpp`
  - UI implementation only; no detector logic.
- Modify: `src/gui/main_window.h`
  - Add gateway dock members and a `refreshGatewayPane()` method.
- Modify: `src/gui/main_window.cpp`
  - Build gateway snapshot from current analysis state and feed `GatewayPane`.
- Modify: `src/gui/CMakeLists.txt`
  - Add gateway pane files.

**CLI/MCP**
- Modify: `src/cli/main.cpp`
  - Add `gateway-snapshot` subcommand.
  - Reuse the same gateway builder used by GUI.
- Modify: `src/mcp/mcp_tools.cpp`
  - Add or update an MCP tool that returns the gateway snapshot.
- Modify: `src/mcp/mcp_cli_bridge.cpp`
  - Ensure the CLI bridge can emit the same gateway snapshot JSON for demos.

**Tests**
- Modify: `tests/unit/safety/safety_unit.cpp`
  - Add gateway builder and verifier unit tests unless a new target is cleaner.
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`
  - Assert Gateway dock exists and shows protected prompt/verification status.
- Modify: `tests/integration/cli_smoke/cli_smoke.cpp`
  - Assert `gateway-snapshot` output shape.
- Modify: `tests/integration/mcp_smoke/mcp_smoke.cpp`
  - Assert MCP gateway tool output shape.

## Shared Data Contract

Implement these names exactly so GUI, CLI, and MCP stay aligned.

```cpp
namespace aura::gateway {

enum class GatewaySourceKind {
    Rizin,
    Ghidra,
};

enum class GatewaySourceStatus {
    Ready,
    Missing,
    Failed,
    NotConfigured,
};

enum class GatewayPolicyAction {
    Allow,
    Mask,
    Omit,
    Block,
};

enum class GatewayVerificationStatus {
    Pass,
    Fail,
};

struct GatewaySourceStatusRecord {
    GatewaySourceKind kind;
    GatewaySourceStatus status;
    std::string detail;
};

struct GatewayProtectedItem {
    std::string id;
    std::string kind;
    std::string location;
    std::string category;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
    GatewayPolicyAction action = GatewayPolicyAction::Allow;
    std::string reason;
    bool original_included = false;
};

struct GatewayRiskSummary {
    std::string severity;
    int finding_count = 0;
    std::vector<std::string> categories;
};

struct GatewayProtectedPrompt {
    std::string title;
    std::string body;
    int included_items = 0;
    int omitted_items = 0;
    int blocked_items = 0;
};

struct GatewayVerificationReport {
    GatewayVerificationStatus status = GatewayVerificationStatus::Pass;
    std::vector<std::string> checks;
    std::vector<std::string> failures;
};

struct GatewayAuditEvent {
    std::string id;
    std::string action;
    std::string item_id;
    std::string category;
    std::string safe_preview;
    std::string reason;
};

struct GatewaySnapshot {
    std::vector<GatewaySourceStatusRecord> sources;
    std::vector<GatewayProtectedItem> protected_items;
    GatewayRiskSummary risk_summary;
    GatewayProtectedPrompt prompt;
    GatewayVerificationReport verification;
    std::vector<GatewayAuditEvent> audit_events;
};

}  // namespace aura::gateway
```

## Task 1: Gateway Core Contract

**Files:**
- Create: `include/aura/gateway/gateway_snapshot.h`
- Create: `src/core/gateway/gateway_snapshot.cpp`
- Modify: `CMakeLists.txt`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Write failing enum text helper tests**

Add this test block to `tests/unit/safety/safety_unit.cpp`:

```cpp
#include "aura/gateway/gateway_snapshot.h"

TEST(GatewaySnapshotTest, EnumTextHelpersAreStable) {
    using namespace aura::gateway;
    EXPECT_STREQ("rizin", gatewaySourceKindToText(GatewaySourceKind::Rizin));
    EXPECT_STREQ("ghidra", gatewaySourceKindToText(GatewaySourceKind::Ghidra));
    EXPECT_STREQ("ready", gatewaySourceStatusToText(GatewaySourceStatus::Ready));
    EXPECT_STREQ("not_configured",
                 gatewaySourceStatusToText(GatewaySourceStatus::NotConfigured));
    EXPECT_STREQ("mask", gatewayPolicyActionToText(GatewayPolicyAction::Mask));
    EXPECT_STREQ("block", gatewayPolicyActionToText(GatewayPolicyAction::Block));
    EXPECT_STREQ("pass",
                 gatewayVerificationStatusToText(GatewayVerificationStatus::Pass));
    EXPECT_STREQ("fail",
                 gatewayVerificationStatusToText(GatewayVerificationStatus::Fail));
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: compile failure because `aura/gateway/gateway_snapshot.h` does not exist.

- [ ] **Step 3: Add the gateway header**

Create `include/aura/gateway/gateway_snapshot.h` with the shared data contract above and these declarations:

```cpp
const char* gatewaySourceKindToText(GatewaySourceKind kind);
const char* gatewaySourceStatusToText(GatewaySourceStatus status);
const char* gatewayPolicyActionToText(GatewayPolicyAction action);
const char* gatewayVerificationStatusToText(GatewayVerificationStatus status);
```

- [ ] **Step 4: Add the gateway implementation**

Create `src/core/gateway/gateway_snapshot.cpp`:

```cpp
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/gateway/gateway_snapshot.h"

namespace aura::gateway {

const char* gatewaySourceKindToText(GatewaySourceKind kind) {
    switch (kind) {
        case GatewaySourceKind::Rizin: return "rizin";
        case GatewaySourceKind::Ghidra: return "ghidra";
    }
    return "unknown";
}

const char* gatewaySourceStatusToText(GatewaySourceStatus status) {
    switch (status) {
        case GatewaySourceStatus::Ready: return "ready";
        case GatewaySourceStatus::Missing: return "missing";
        case GatewaySourceStatus::Failed: return "failed";
        case GatewaySourceStatus::NotConfigured: return "not_configured";
    }
    return "unknown";
}

const char* gatewayPolicyActionToText(GatewayPolicyAction action) {
    switch (action) {
        case GatewayPolicyAction::Allow: return "allow";
        case GatewayPolicyAction::Mask: return "mask";
        case GatewayPolicyAction::Omit: return "omit";
        case GatewayPolicyAction::Block: return "block";
    }
    return "unknown";
}

const char* gatewayVerificationStatusToText(GatewayVerificationStatus status) {
    switch (status) {
        case GatewayVerificationStatus::Pass: return "pass";
        case GatewayVerificationStatus::Fail: return "fail";
    }
    return "unknown";
}

}  // namespace aura::gateway
```

- [ ] **Step 5: Wire the file into CMake**

Add `src/core/gateway/gateway_snapshot.cpp` to the same core/static library target that already compiles `src/core/safety/safe_export_view.cpp`.

- [ ] **Step 6: Run the test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS.

- [ ] **Step 7: Commit**

```powershell
git add include/aura/gateway/gateway_snapshot.h src/core/gateway/gateway_snapshot.cpp CMakeLists.txt tests/unit/safety/safety_unit.cpp
git commit -m "feat: add gateway snapshot contract"
```

## Task 2: Gateway Builder And Verification

**Files:**
- Modify: `include/aura/gateway/gateway_snapshot.h`
- Modify: `src/core/gateway/gateway_snapshot.cpp`
- Test: `tests/unit/safety/safety_unit.cpp`

- [ ] **Step 1: Write failing builder test**

Add this test:

```cpp
TEST(GatewaySnapshotTest, BuildsProtectedPromptAndVerificationFromSafeItems) {
    using namespace aura::gateway;

    GatewayBuildInput input;
    input.sources.push_back(
        {GatewaySourceKind::Rizin, GatewaySourceStatus::Ready, "analysis loaded"});
    input.sources.push_back(
        {GatewaySourceKind::Ghidra, GatewaySourceStatus::NotConfigured,
         "Ghidra runtime is not configured"});
    input.items.push_back({"string", "0x401000", "korean_rrn",
                           "900101-1234567", "900101-1******",
                           "900101-1******", "KR_RRN_1"});

    GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    ASSERT_EQ(snapshot.protected_items.size(), 1u);
    EXPECT_EQ(snapshot.protected_items[0].action, GatewayPolicyAction::Mask);
    EXPECT_FALSE(snapshot.protected_items[0].original_included);
    EXPECT_EQ(snapshot.verification.status, GatewayVerificationStatus::Pass);
    EXPECT_NE(snapshot.prompt.body.find("900101-1******"), std::string::npos);
    EXPECT_EQ(snapshot.prompt.body.find("900101-1234567"), std::string::npos);
    ASSERT_FALSE(snapshot.audit_events.empty());
}
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
```

Expected: compile failure because `GatewayBuildInput` and `buildGatewaySnapshot` do not exist.

- [ ] **Step 3: Add builder input types**

Append to `include/aura/gateway/gateway_snapshot.h`:

```cpp
struct GatewayBuildItemInput {
    std::string kind;
    std::string location;
    std::string category;
    std::string original_value;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
};

struct GatewayBuildInput {
    std::vector<GatewaySourceStatusRecord> sources;
    std::vector<GatewayBuildItemInput> items;
    std::string malware_risk_severity = "info";
    std::vector<std::string> malware_risk_categories;
};

GatewaySnapshot buildGatewaySnapshot(const GatewayBuildInput& input);
```

- [ ] **Step 4: Implement builder**

Add to `src/core/gateway/gateway_snapshot.cpp`:

```cpp
namespace {

bool isSensitiveCategory(const std::string& category) {
    return category == "korean_rrn" ||
           category == "email" ||
           category == "phone" ||
           category == "secret" ||
           category == "token" ||
           category == "url";
}

std::string makeAuditId(size_t index) {
    return "gateway_audit_" + std::to_string(index + 1u);
}

}  // namespace

GatewaySnapshot buildGatewaySnapshot(const GatewayBuildInput& input) {
    GatewaySnapshot snapshot;
    snapshot.sources = input.sources;
    snapshot.risk_summary.severity = input.malware_risk_severity.empty()
        ? "info"
        : input.malware_risk_severity;
    snapshot.risk_summary.finding_count =
        static_cast<int>(input.malware_risk_categories.size());
    snapshot.risk_summary.categories = input.malware_risk_categories;
    snapshot.prompt.title = "Protected reverse-engineering context";

    std::string body;
    body += "AURA protected reverse-engineering context\n";
    body += "Only protected values are included.\n\n";

    size_t audit_index = 0u;
    for (const auto& item : input.items) {
        GatewayProtectedItem out;
        out.id = "item_" + std::to_string(snapshot.protected_items.size() + 1u);
        out.kind = item.kind;
        out.location = item.location;
        out.category = item.category;
        out.display_value = item.display_value;
        out.transmission_value = item.transmission_value;
        out.mask_token = item.mask_token;
        out.original_included = false;

        if (item.transmission_value.empty()) {
            out.action = GatewayPolicyAction::Omit;
            out.reason = "empty protected transmission value";
            snapshot.prompt.omitted_items += 1;
        } else if (isSensitiveCategory(item.category)) {
            out.action = GatewayPolicyAction::Mask;
            out.reason = "sensitive value replaced with protected representation";
            snapshot.prompt.included_items += 1;
            body += "- ";
            body += item.kind + " " + item.location + " ";
            body += item.category + ": " + item.transmission_value + "\n";
        } else {
            out.action = GatewayPolicyAction::Allow;
            out.reason = "no sensitive category matched";
            snapshot.prompt.included_items += 1;
            body += "- ";
            body += item.kind + " " + item.location + " ";
            body += item.category + ": " + item.transmission_value + "\n";
        }

        GatewayAuditEvent audit;
        audit.id = makeAuditId(audit_index++);
        audit.action = gatewayPolicyActionToText(out.action);
        audit.item_id = out.id;
        audit.category = out.category;
        audit.safe_preview = out.transmission_value;
        audit.reason = out.reason;
        snapshot.audit_events.push_back(audit);
        snapshot.protected_items.push_back(out);
    }

    snapshot.prompt.body = body;
    snapshot.verification.status = GatewayVerificationStatus::Pass;
    snapshot.verification.checks.push_back("protected_prompt_generated");
    snapshot.verification.checks.push_back("original_values_not_included");

    for (const auto& item : input.items) {
        if (!item.original_value.empty() &&
            snapshot.prompt.body.find(item.original_value) != std::string::npos) {
            snapshot.verification.status = GatewayVerificationStatus::Fail;
            snapshot.verification.failures.push_back(
                "raw original value appeared in protected prompt at " + item.location);
        }
    }

    return snapshot;
}
```

- [ ] **Step 5: Run unit test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS.

- [ ] **Step 6: Add fail-path test**

Add:

```cpp
TEST(GatewaySnapshotTest, VerificationFailsWhenRawOriginalLeaksIntoPrompt) {
    using namespace aura::gateway;

    GatewayBuildInput input;
    input.items.push_back({"string", "0x401000", "korean_rrn",
                           "900101-1234567", "900101-1******",
                           "900101-1234567", "KR_RRN_1"});

    GatewaySnapshot snapshot = buildGatewaySnapshot(input);

    EXPECT_EQ(snapshot.verification.status, GatewayVerificationStatus::Fail);
    ASSERT_FALSE(snapshot.verification.failures.empty());
}
```

- [ ] **Step 7: Run unit test again**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit
ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure
```

Expected: PASS.

- [ ] **Step 8: Commit**

```powershell
git add include/aura/gateway/gateway_snapshot.h src/core/gateway/gateway_snapshot.cpp tests/unit/safety/safety_unit.cpp
git commit -m "feat: build protected gateway snapshots"
```

## Task 3: Gateway JSON Serialization For CLI/MCP

**Files:**
- Modify: `src/cli/main.cpp`
- Modify: `src/mcp/mcp_tools.cpp`
- Modify: `src/mcp/mcp_cli_bridge.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Write failing CLI smoke assertion**

Add a CLI smoke test that runs:

```powershell
.\build-trim-gui\Release\aura.exe gateway-snapshot --demo --compact
```

Expected JSON keys:

```json
{
  "command": "gateway-snapshot",
  "gateway": {
    "sources": [],
    "protected_items": [],
    "risk_summary": {},
    "protected_prompt": {},
    "verification": {},
    "audit_events": []
  }
}
```

The test must assert:

```cpp
EXPECT_NE(output.find("\"command\":\"gateway-snapshot\""), std::string::npos);
EXPECT_NE(output.find("\"protected_prompt\""), std::string::npos);
EXPECT_NE(output.find("\"verification\""), std::string::npos);
EXPECT_NE(output.find("\"audit_events\""), std::string::npos);
EXPECT_EQ(output.find("900101-1234567"), std::string::npos);
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: FAIL because `gateway-snapshot` command does not exist.

- [ ] **Step 3: Add JSON serializer helpers in CLI**

In `src/cli/main.cpp`, add helper functions near existing safety JSON helpers:

```cpp
static cJSON* gateway_snapshot_to_json(const aura::gateway::GatewaySnapshot& snapshot) {
    cJSON* root = cJSON_CreateObject();
    cJSON* sources = cJSON_AddArrayToObject(root, "sources");
    for (const auto& source : snapshot.sources) {
        cJSON* item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "kind",
            aura::gateway::gatewaySourceKindToText(source.kind));
        cJSON_AddStringToObject(item, "status",
            aura::gateway::gatewaySourceStatusToText(source.status));
        cJSON_AddStringToObject(item, "detail", source.detail.c_str());
        cJSON_AddItemToArray(sources, item);
    }

    cJSON* protected_items = cJSON_AddArrayToObject(root, "protected_items");
    for (const auto& protected_item : snapshot.protected_items) {
        cJSON* item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "id", protected_item.id.c_str());
        cJSON_AddStringToObject(item, "kind", protected_item.kind.c_str());
        cJSON_AddStringToObject(item, "location", protected_item.location.c_str());
        cJSON_AddStringToObject(item, "category", protected_item.category.c_str());
        cJSON_AddStringToObject(item, "display_value",
                                protected_item.display_value.c_str());
        cJSON_AddStringToObject(item, "transmission_value",
                                protected_item.transmission_value.c_str());
        cJSON_AddStringToObject(item, "mask_token", protected_item.mask_token.c_str());
        cJSON_AddStringToObject(item, "action",
            aura::gateway::gatewayPolicyActionToText(protected_item.action));
        cJSON_AddStringToObject(item, "reason", protected_item.reason.c_str());
        cJSON_AddBoolToObject(item, "original_included",
                              protected_item.original_included);
        cJSON_AddItemToArray(protected_items, item);
    }

    cJSON* risk = cJSON_AddObjectToObject(root, "risk_summary");
    cJSON_AddStringToObject(risk, "severity", snapshot.risk_summary.severity.c_str());
    cJSON_AddNumberToObject(risk, "finding_count",
                            snapshot.risk_summary.finding_count);
    cJSON* risk_categories = cJSON_AddArrayToObject(risk, "categories");
    for (const auto& category : snapshot.risk_summary.categories) {
        cJSON_AddItemToArray(risk_categories, cJSON_CreateString(category.c_str()));
    }

    cJSON* prompt = cJSON_AddObjectToObject(root, "protected_prompt");
    cJSON_AddStringToObject(prompt, "title", snapshot.prompt.title.c_str());
    cJSON_AddStringToObject(prompt, "body", snapshot.prompt.body.c_str());
    cJSON_AddNumberToObject(prompt, "included_items", snapshot.prompt.included_items);
    cJSON_AddNumberToObject(prompt, "omitted_items", snapshot.prompt.omitted_items);
    cJSON_AddNumberToObject(prompt, "blocked_items", snapshot.prompt.blocked_items);

    cJSON* verification = cJSON_AddObjectToObject(root, "verification");
    cJSON_AddStringToObject(verification, "status",
        aura::gateway::gatewayVerificationStatusToText(snapshot.verification.status));
    cJSON* checks = cJSON_AddArrayToObject(verification, "checks");
    for (const auto& check : snapshot.verification.checks) {
        cJSON_AddItemToArray(checks, cJSON_CreateString(check.c_str()));
    }
    cJSON* failures = cJSON_AddArrayToObject(verification, "failures");
    for (const auto& failure : snapshot.verification.failures) {
        cJSON_AddItemToArray(failures, cJSON_CreateString(failure.c_str()));
    }

    cJSON* audit = cJSON_AddArrayToObject(root, "audit_events");
    for (const auto& event : snapshot.audit_events) {
        cJSON* item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "id", event.id.c_str());
        cJSON_AddStringToObject(item, "action", event.action.c_str());
        cJSON_AddStringToObject(item, "item_id", event.item_id.c_str());
        cJSON_AddStringToObject(item, "category", event.category.c_str());
        cJSON_AddStringToObject(item, "safe_preview", event.safe_preview.c_str());
        cJSON_AddStringToObject(item, "reason", event.reason.c_str());
        cJSON_AddItemToArray(audit, item);
    }

    return root;
}
```

- [ ] **Step 4: Add demo builder path**

In `src/cli/main.cpp`, add a small demo builder used only by `--demo`:

```cpp
static aura::gateway::GatewaySnapshot build_demo_gateway_snapshot() {
    aura::gateway::GatewayBuildInput input;
    input.sources.push_back({aura::gateway::GatewaySourceKind::Rizin,
                             aura::gateway::GatewaySourceStatus::Ready,
                             "demo analysis loaded"});
    input.sources.push_back({aura::gateway::GatewaySourceKind::Ghidra,
                             aura::gateway::GatewaySourceStatus::NotConfigured,
                             "Ghidra runtime is not configured"});
    input.items.push_back({"string", "0x401000", "korean_rrn",
                           "900101-1234567", "900101-1******",
                           "900101-1******", "KR_RRN_1"});
    input.items.push_back({"string", "0x401020", "email",
                           "student@example.com", "stu********@example.com",
                           "stu********@example.com", "EMAIL_1"});
    input.malware_risk_severity = "low";
    input.malware_risk_categories.push_back("network");
    return aura::gateway::buildGatewaySnapshot(input);
}
```

- [ ] **Step 5: Add CLI command**

Add subcommand:

```cpp
bool gateway_demo = false;
auto* cmd_gateway = app.add_subcommand(
    "gateway-snapshot",
    "emit protected LLM gateway snapshot JSON");
cmd_gateway->add_flag("--demo", gateway_demo,
    "emit deterministic demo snapshot without analyzing a binary");
```

Add command handling:

```cpp
if (cmd_gateway->parsed()) {
    if (!gateway_demo) {
        emit_error_json("gateway_requires_demo_or_binary",
                        "gateway-snapshot currently requires --demo in MVP",
                        g.compact);
        return 2;
    }
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "gateway-snapshot");
    cJSON_AddItemToObject(root, "gateway",
                          gateway_snapshot_to_json(build_demo_gateway_snapshot()));
    print_json_and_delete(root, g.compact);
    return 0;
}
```

- [ ] **Step 6: Wire MCP to the same JSON contract**

In `src/mcp/mcp_tools.cpp`, expose a tool named `aura_get_gateway_snapshot` that returns a `gateway` object with the same fields. If an existing MCP bridge already shells out to CLI, prefer calling the new `gateway-snapshot --demo --compact` path from `src/mcp/mcp_cli_bridge.cpp` to avoid duplicate JSON logic.

Tool description:

```text
Return the protected AURA Gateway snapshot used for LLM pre-send review. The output excludes raw protected values and includes policy decisions, verification status, and audit events.
```

- [ ] **Step 7: Run CLI and MCP smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: PASS.

- [ ] **Step 8: Commit**

```powershell
git add src/cli/main.cpp src/mcp/mcp_tools.cpp src/mcp/mcp_cli_bridge.cpp tests/integration/cli_smoke/cli_smoke.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat: expose gateway snapshot through cli and mcp"
```

## Task 4: Gateway GUI Pane

**Files:**
- Create: `src/gui/gateway_pane.h`
- Create: `src/gui/gateway_pane.cpp`
- Modify: `src/gui/CMakeLists.txt`
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI smoke assertions**

Add assertions that the GUI contains:

```cpp
QVERIFY(window.findChild<QDockWidget*>("gatewayDock") != nullptr);
QVERIFY(window.findChild<QLabel*>("gatewayStatusLabel") != nullptr);
QVERIFY(window.findChild<QPlainTextEdit*>("gatewayProtectedPrompt") != nullptr);
QVERIFY(window.findChild<QTreeWidget*>("gatewayAuditTable") != nullptr);
```

Expected visible text after demo data is loaded:

```cpp
QCOMPARE(window.findChild<QLabel*>("gatewayStatusLabel")->text(),
         QStringLiteral("LLM 전송 상태: PASS"));
QVERIFY(window.findChild<QPlainTextEdit*>("gatewayProtectedPrompt")
            ->toPlainText()
            .contains(QStringLiteral("Only protected values are included.")));
QVERIFY(!window.findChild<QPlainTextEdit*>("gatewayProtectedPrompt")
            ->toPlainText()
            .contains(QStringLiteral("900101-1234567")));
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: FAIL because Gateway dock does not exist.

- [ ] **Step 3: Add GatewayPane header**

Create `src/gui/gateway_pane.h`:

```cpp
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "aura/gateway/gateway_snapshot.h"

#include <QWidget>

class QLabel;
class QPlainTextEdit;
class QTreeWidget;

class GatewayPane final : public QWidget {
    Q_OBJECT

public:
    explicit GatewayPane(QWidget* parent = nullptr);
    void setSnapshot(const aura::gateway::GatewaySnapshot& snapshot);

private:
    QLabel* m_statusLabel = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QPlainTextEdit* m_prompt = nullptr;
    QTreeWidget* m_audit = nullptr;
};
```

- [ ] **Step 4: Add GatewayPane implementation**

Create `src/gui/gateway_pane.cpp`:

```cpp
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "gateway_pane.h"

#include <QHeaderView>
#include <QLabel>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>

GatewayPane::GatewayPane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    m_statusLabel = new QLabel(QStringLiteral("LLM 전송 상태: 대기"), this);
    m_statusLabel->setObjectName(QStringLiteral("gatewayStatusLabel"));
    layout->addWidget(m_statusLabel);

    m_summaryLabel = new QLabel(QStringLiteral("탐지 0개 / 마스킹 0개 / 차단 0개"), this);
    m_summaryLabel->setObjectName(QStringLiteral("gatewaySummaryLabel"));
    layout->addWidget(m_summaryLabel);

    m_prompt = new QPlainTextEdit(this);
    m_prompt->setObjectName(QStringLiteral("gatewayProtectedPrompt"));
    m_prompt->setReadOnly(true);
    m_prompt->setMinimumHeight(180);
    layout->addWidget(m_prompt, 1);

    m_audit = new QTreeWidget(this);
    m_audit->setObjectName(QStringLiteral("gatewayAuditTable"));
    m_audit->setColumnCount(4);
    m_audit->setHeaderLabels({QStringLiteral("Action"),
                              QStringLiteral("Category"),
                              QStringLiteral("Preview"),
                              QStringLiteral("Reason")});
    m_audit->setRootIsDecorated(false);
    m_audit->setUniformRowHeights(true);
    m_audit->header()->setStretchLastSection(true);
    layout->addWidget(m_audit, 1);
}

void GatewayPane::setSnapshot(const aura::gateway::GatewaySnapshot& snapshot) {
    const bool pass =
        snapshot.verification.status == aura::gateway::GatewayVerificationStatus::Pass;
    m_statusLabel->setText(pass ? QStringLiteral("LLM 전송 상태: PASS")
                               : QStringLiteral("LLM 전송 상태: FAIL"));

    int masked = 0;
    int blocked = 0;
    for (const auto& item : snapshot.protected_items) {
        if (item.action == aura::gateway::GatewayPolicyAction::Mask) ++masked;
        if (item.action == aura::gateway::GatewayPolicyAction::Block) ++blocked;
    }

    m_summaryLabel->setText(QStringLiteral("탐지 %1개 / 마스킹 %2개 / 차단 %3개")
                                .arg(snapshot.protected_items.size())
                                .arg(masked)
                                .arg(blocked));

    m_prompt->setPlainText(QString::fromStdString(snapshot.prompt.body));

    m_audit->clear();
    for (const auto& event : snapshot.audit_events) {
        auto* row = new QTreeWidgetItem();
        row->setText(0, QString::fromStdString(event.action));
        row->setText(1, QString::fromStdString(event.category));
        row->setText(2, QString::fromStdString(event.safe_preview));
        row->setText(3, QString::fromStdString(event.reason));
        m_audit->addTopLevelItem(row);
    }
}
```

- [ ] **Step 5: Add dock members**

In `src/gui/main_window.h`, add forward declaration and members:

```cpp
class GatewayPane;

QDockWidget* m_gatewayDock = nullptr;
GatewayPane* m_gatewayPane = nullptr;
void refreshGatewayPane();
```

- [ ] **Step 6: Create dock in MainWindow**

In `src/gui/main_window.cpp`, include:

```cpp
#include "gateway_pane.h"
#include "aura/gateway/gateway_snapshot.h"
```

Near the existing demo/malware dock creation, add:

```cpp
m_gatewayDock = new QDockWidget(QStringLiteral("LLM Gateway"), m_workspace);
m_gatewayDock->setObjectName(QStringLiteral("gatewayDock"));
m_gatewayDock->setAllowedAreas(Qt::AllDockWidgetAreas);
m_gatewayPane = new GatewayPane(m_gatewayDock);
m_gatewayDock->setWidget(m_gatewayPane);
m_workspace->tabifyDockWidget(m_decompileDock, m_gatewayDock);
refreshGatewayPane();
```

Add method:

```cpp
void MainWindow::refreshGatewayPane() {
    if (!m_gatewayPane) return;

    aura::gateway::GatewayBuildInput input;
    input.sources.push_back({aura::gateway::GatewaySourceKind::Rizin,
                             aura::gateway::GatewaySourceStatus::Ready,
                             "GUI analysis state loaded"});
    input.sources.push_back({aura::gateway::GatewaySourceKind::Ghidra,
                             aura::gateway::GatewaySourceStatus::NotConfigured,
                             "Ghidra status is shown only when configured"});

    for (const auto& s : m_strings) {
        if (s.exportValue.isEmpty() && s.protectedValue.isEmpty()) continue;
        input.items.push_back({"string",
                               QStringLiteral("0x%1")
                                   .arg(s.vaddr, 0, 16)
                                   .toStdString(),
                               s.protectionCategory.toStdString(),
                               s.content.toStdString(),
                               s.protectedValue.toStdString(),
                               s.exportValue.isEmpty()
                                   ? s.protectedValue.toStdString()
                                   : s.exportValue.toStdString(),
                               s.maskToken.toStdString()});
    }

    if (!m_malwareRisks.isEmpty()) {
        input.malware_risk_severity = "low";
        for (const auto& risk : m_malwareRisks) {
            input.malware_risk_categories.push_back(risk.category.toStdString());
        }
    }

    m_gatewayPane->setSnapshot(aura::gateway::buildGatewaySnapshot(input));
}
```

Call `refreshGatewayPane()` after `refreshDemoModePane()` and after string analysis updates.

- [ ] **Step 7: Wire GUI CMake**

Add `src/gui/gateway_pane.cpp` to the GUI target source list in `src/gui/CMakeLists.txt`.

- [ ] **Step 8: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

- [ ] **Step 9: Commit**

```powershell
git add src/gui/gateway_pane.h src/gui/gateway_pane.cpp src/gui/CMakeLists.txt src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: add llm gateway overview pane"
```

## Task 5: Real Analysis Snapshot Integration

**Files:**
- Modify: `src/gui/main_window.cpp`
- Modify: `src/cli/main.cpp`
- Modify: `src/mcp/mcp_cli_bridge.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`
- Test: `tests/integration/cli_smoke/cli_smoke.cpp`
- Test: `tests/integration/mcp_smoke/mcp_smoke.cpp`

- [ ] **Step 1: Add CLI test for fixture mode**

Use the existing sensitive demo fixture path already used by CLI smoke. Add an assertion for:

```powershell
.\build-trim-gui\Release\aura.exe gateway-snapshot path\to\fixture.exe --compact
```

Required assertions:

```cpp
EXPECT_NE(output.find("\"gateway\""), std::string::npos);
EXPECT_NE(output.find("\"verification\""), std::string::npos);
EXPECT_EQ(output.find("900101-1234567"), std::string::npos);
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke
ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure
```

Expected: FAIL because non-demo binary path is not implemented yet.

- [ ] **Step 3: Extract current CLI protected string collection**

In `src/cli/main.cpp`, locate the logic that already builds `SafeExportItem` records for `llm-context` or protected string output. Extract it into a helper:

```cpp
static aura::gateway::GatewayBuildInput build_gateway_input_for_binary(
    const std::string& binary_path,
    aura::safety::StringProtectionMode string_protection_mode) {
    aura::gateway::GatewayBuildInput input;
    input.sources.push_back({aura::gateway::GatewaySourceKind::Rizin,
                             aura::gateway::GatewaySourceStatus::Ready,
                             "Rizin analysis requested"});
    input.sources.push_back({aura::gateway::GatewaySourceKind::Ghidra,
                             aura::gateway::GatewaySourceStatus::NotConfigured,
                             "Ghidra is not required for gateway MVP"});

    // Reuse the existing string extraction path used by llm-context.
    // For every extracted string, scan safety findings, build protected view,
    // then push GatewayBuildItemInput with original, display, transmission,
    // category, mask_token, and location.

    return input;
}
```

The implementation must call existing extraction/safety helpers; it must not invent strings.

- [ ] **Step 4: Replace `--demo`-only guard**

Allow:

```powershell
aura.exe gateway-snapshot <binary> --compact
```

Keep `--demo` for deterministic classroom/demo output.

- [ ] **Step 5: Route MCP through real snapshot when binary is provided**

In `src/mcp/mcp_cli_bridge.cpp`, make the gateway tool emit:

```powershell
aura.exe gateway-snapshot "<binary>" --compact
```

For no-binary demo calls, keep:

```powershell
aura.exe gateway-snapshot --demo --compact
```

- [ ] **Step 6: Run CLI/MCP tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target cli_smoke mcp_smoke
ctest --test-dir build-trim-gui -C Release -R "cli_smoke|mcp_smoke" --output-on-failure
```

Expected: PASS.

- [ ] **Step 7: Commit**

```powershell
git add src/cli/main.cpp src/mcp/mcp_cli_bridge.cpp tests/integration/cli_smoke/cli_smoke.cpp tests/integration/mcp_smoke/mcp_smoke.cpp
git commit -m "feat: build gateway snapshots from real analysis"
```

## Task 6: Demo-Ready Verification UX

**Files:**
- Modify: `src/gui/gateway_pane.h`
- Modify: `src/gui/gateway_pane.cpp`
- Modify: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add failing GUI smoke for verification detail**

Add assertions:

```cpp
auto* verification = window.findChild<QTreeWidget*>("gatewayVerificationTable");
QVERIFY(verification != nullptr);
QVERIFY(verification->topLevelItemCount() >= 2);
```

- [ ] **Step 2: Run and confirm failure**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: FAIL because `gatewayVerificationTable` does not exist.

- [ ] **Step 3: Add verification table**

In `GatewayPane`, add:

```cpp
QTreeWidget* m_verification = nullptr;
```

Create it in the constructor:

```cpp
m_verification = new QTreeWidget(this);
m_verification->setObjectName(QStringLiteral("gatewayVerificationTable"));
m_verification->setColumnCount(2);
m_verification->setHeaderLabels({QStringLiteral("Check"),
                                 QStringLiteral("Result")});
m_verification->setRootIsDecorated(false);
m_verification->setUniformRowHeights(true);
layout->addWidget(m_verification);
```

Populate in `setSnapshot`:

```cpp
m_verification->clear();
for (const auto& check : snapshot.verification.checks) {
    auto* row = new QTreeWidgetItem();
    row->setText(0, QString::fromStdString(check));
    row->setText(1, QStringLiteral("PASS"));
    m_verification->addTopLevelItem(row);
}
for (const auto& failure : snapshot.verification.failures) {
    auto* row = new QTreeWidgetItem();
    row->setText(0, QString::fromStdString(failure));
    row->setText(1, QStringLiteral("FAIL"));
    m_verification->addTopLevelItem(row);
}
```

- [ ] **Step 4: Run GUI tests**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke aura-gui
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: PASS.

- [ ] **Step 5: Commit**

```powershell
git add src/gui/gateway_pane.h src/gui/gateway_pane.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: show gateway verification checks"
```

## Task 7: Final Foreground GUI Verification

**Files:**
- No source edits unless verification exposes a bug.

- [ ] **Step 1: Build all required targets**

Run:

```powershell
cmake --build build-trim-gui --config Release --target safety_unit cli_smoke mcp_smoke gui_smoke aura aura-gui
```

Expected: build succeeds.

- [ ] **Step 2: Run automated tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "safety_unit|cli_smoke|mcp_smoke|gui_smoke" --output-on-failure
```

Expected: all selected tests pass.

- [ ] **Step 3: Launch GUI in foreground**

Run:

```powershell
Start-Process -FilePath ".\build-trim-gui\Release\aura-gui.exe" -WorkingDirectory (Get-Location)
```

Expected: foreground GUI opens.

- [ ] **Step 4: Manual GUI acceptance check**

Verify:
- `LLM Gateway` dock exists.
- Status reads `LLM 전송 상태: PASS` after protected data is loaded.
- Protected prompt contains masked values such as `900101-1******`.
- Protected prompt does not contain raw values such as `900101-1234567`.
- Audit table has at least one `mask` event.
- Existing Strings, Demo Mode, Malware Risk, Decompile, Disasm docks still open.

- [ ] **Step 5: CLI demo check**

Run:

```powershell
.\build-trim-gui\Release\aura.exe gateway-snapshot --demo --compact
```

Expected:
- JSON includes `gateway.protected_prompt`.
- JSON includes `gateway.verification.status`.
- JSON includes `gateway.audit_events`.
- JSON does not include `900101-1234567`.

- [ ] **Step 6: MCP demo check**

Run the existing MCP smoke or the project’s documented MCP JSON request generator for `aura_get_gateway_snapshot`.

Expected:
- MCP output has the same high-level fields as CLI.
- MCP output does not include raw protected values.

- [ ] **Step 7: Commit verification fixes only if needed**

If any verification fix was required:

```powershell
git add <fixed-files>
git commit -m "fix: stabilize gateway demo verification"
```

## Test Matrix

| Area | Command | Required Result |
|---|---|---|
| Core | `ctest --test-dir build-trim-gui -C Release -R safety_unit --output-on-failure` | Gateway builder and verifier pass |
| CLI | `ctest --test-dir build-trim-gui -C Release -R cli_smoke --output-on-failure` | `gateway-snapshot` JSON excludes raw values |
| MCP | `ctest --test-dir build-trim-gui -C Release -R mcp_smoke --output-on-failure` | MCP gateway tool shape matches CLI |
| GUI | `ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure` | Gateway dock and protected prompt visible |
| App | `cmake --build build-trim-gui --config Release --target aura-gui` | Foreground GUI can be launched |

## Autoplan Review Decisions Applied

| Decision | Applied As |
|---|---|
| Reframe from masking utility to LLM Gateway | Gateway Overview + Protected Prompt + Verification + Audit |
| GUI is the product surface | Gateway dock is mandatory before claiming complete |
| CLI/MCP must match GUI | Shared `GatewaySnapshot` model and JSON contract |
| Avoid Ghidra overclaiming | Ghidra status is explicit and can be `not_configured` |
| Avoid live LLM risk in MVP | Protected prompt is generated and verified before any real send |

## Self-Review

**Spec coverage:**
- Rizin/Ghidra result collection: covered by source status records and integration tasks.
- Common structure: covered by `GatewaySnapshot`.
- Sensitive/secret detection: covered through existing safety export integration.
- Risk classification: covered through `GatewayRiskSummary` and current malware-risk reuse.
- LLM policy: covered by `GatewayPolicyAction`.
- Protected prompt: covered by `GatewayProtectedPrompt`.
- Pre-send verification: covered by `GatewayVerificationReport`.
- LLM result output: intentionally deferred from MVP; protected prompt is the safe boundary.
- Mask/block log: covered by `GatewayAuditEvent` and GUI table.

**Placeholder scan:**
- No task uses `TBD`, `TODO`, or undefined follow-up text as acceptance criteria.
- The only intentionally abstract part is reuse of existing CLI extraction logic in Task 5; the constraint is explicit: do not invent strings.

**Type consistency:**
- `GatewayBuildInput`, `GatewaySnapshot`, `GatewayProtectedItem`, `GatewayVerificationReport`, and enum helper names are consistent across tasks.

