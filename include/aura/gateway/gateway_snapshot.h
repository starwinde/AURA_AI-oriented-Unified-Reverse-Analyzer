#pragma once

#include <string>
#include <vector>

namespace aura::gateway {

enum class GatewaySourceKind { Rizin, Ghidra };
enum class GatewaySourceStatus { Ready, Missing, Failed, NotConfigured };
enum class GatewayPolicyAction { Allow, Mask, Omit, Block };
enum class GatewayReadinessStatus { Pass, Warning, NotReady, Disabled, Fail };
enum class GatewayCheckStatus { Pass, Warning, NotReady, Disabled, Fail };

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

struct GatewayVerificationCheck {
    std::string name;
    GatewayCheckStatus status = GatewayCheckStatus::Pass;
    std::string detail;
};

struct GatewayVerificationReport {
    GatewayReadinessStatus status = GatewayReadinessStatus::NotReady;
    std::vector<GatewayVerificationCheck> checks;
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
    GatewaySafetyState safety_state;
    std::string malware_risk_severity = "info";
    std::vector<std::string> malware_risk_categories;
};

const char* gatewaySourceKindToText(GatewaySourceKind kind);
const char* gatewaySourceStatusToText(GatewaySourceStatus status);
const char* gatewayPolicyActionToText(GatewayPolicyAction action);
const char* gatewayReadinessStatusToText(GatewayReadinessStatus status);
const char* gatewayCheckStatusToText(GatewayCheckStatus status);
GatewaySnapshot buildGatewaySnapshot(const GatewayBuildInput& input);

}  // namespace aura::gateway
