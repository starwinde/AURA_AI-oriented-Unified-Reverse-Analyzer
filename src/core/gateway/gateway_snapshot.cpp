#include "aura/gateway/gateway_snapshot.h"

namespace aura::gateway {

namespace {

bool isSensitiveCategory(const std::string& category) {
    return category == "korean_rrn" || category == "kr_rrn" ||
           category == "email" || category == "phone" ||
           category == "phone_number" || category == "secret" ||
           category == "token" || category == "api_key" ||
           category == "url";
}

std::string makeItemId(std::size_t index) {
    return "item_" + std::to_string(index + 1u);
}

std::string makeAuditId(std::size_t index) {
    return "gateway_audit_" + std::to_string(index + 1u);
}

bool containsOriginal(const std::string& value, const std::string& original) {
    return !original.empty() && value.find(original) != std::string::npos;
}

void appendPromptItemLine(std::string& body, const GatewayProtectedItem& item) {
    body += "- ";
    body += item.kind;
    body += " ";
    body += item.location;
    body += " ";
    body += item.category;
    body += ": ";
    body += item.transmission_value;
    body += "\n";
}

void addCheck(GatewaySnapshot& snapshot,
              std::string name,
              GatewayCheckStatus status,
              std::string detail) {
    snapshot.verification.checks.push_back(
        GatewayVerificationCheck{std::move(name), status, std::move(detail)});
}

}  // namespace

const char* gatewaySourceKindToText(GatewaySourceKind kind) {
    switch (kind) {
        case GatewaySourceKind::Rizin:
            return "rizin";
        case GatewaySourceKind::Ghidra:
            return "ghidra";
    }
    return "";
}

const char* gatewaySourceStatusToText(GatewaySourceStatus status) {
    switch (status) {
        case GatewaySourceStatus::Ready:
            return "ready";
        case GatewaySourceStatus::Missing:
            return "missing";
        case GatewaySourceStatus::Failed:
            return "failed";
        case GatewaySourceStatus::NotConfigured:
            return "not_configured";
    }
    return "";
}

const char* gatewayPolicyActionToText(GatewayPolicyAction action) {
    switch (action) {
        case GatewayPolicyAction::Allow:
            return "allow";
        case GatewayPolicyAction::Mask:
            return "mask";
        case GatewayPolicyAction::Omit:
            return "omit";
        case GatewayPolicyAction::Block:
            return "block";
    }
    return "";
}

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

GatewaySnapshot buildGatewaySnapshot(const GatewayBuildInput& input) {
    GatewaySnapshot snapshot;
    snapshot.sources = input.sources;
    snapshot.risk_summary.severity =
        input.malware_risk_severity.empty() ? "info"
                                            : input.malware_risk_severity;
    snapshot.risk_summary.finding_count =
        static_cast<int>(input.malware_risk_categories.size());
    snapshot.risk_summary.categories = input.malware_risk_categories;

    snapshot.prompt.title = "Protected reverse-engineering context";
    snapshot.prompt.body =
        "AURA protected reverse-engineering context\n"
        "Only protected values are included.\n\n";

    const auto& state = input.safety_state;

    if (!state.protection_enabled) {
        snapshot.verification.status = GatewayReadinessStatus::Disabled;
        addCheck(snapshot, "protection_enabled",
                 GatewayCheckStatus::Disabled,
                 "string protection is disabled by user settings");
        return snapshot;
    }

    addCheck(snapshot, "protection_enabled", GatewayCheckStatus::Pass,
             "string protection is enabled");

    if (!state.safety_scan_executed) {
        snapshot.verification.status = GatewayReadinessStatus::NotReady;
        addCheck(snapshot, "safety_scan_executed",
                 GatewayCheckStatus::NotReady,
                 "safety scan has not run for the current analysis");
        return snapshot;
    }

    addCheck(snapshot, "safety_scan_executed", GatewayCheckStatus::Pass,
             "safety scan ran for the current analysis");

    if (!state.safety_profile_applied) {
        snapshot.verification.status = GatewayReadinessStatus::NotReady;
        addCheck(snapshot, "safety_profile_applied",
                 GatewayCheckStatus::NotReady,
                 "safety profile was not applied");
        return snapshot;
    }

    addCheck(snapshot, "safety_profile_applied", GatewayCheckStatus::Pass,
             "safety profile was applied");

    bool hasWarning = false;
    if (!state.rule_packs_loaded) {
        hasWarning = true;
        snapshot.verification.status = GatewayReadinessStatus::Warning;
        addCheck(snapshot, "rule_packs_loaded", GatewayCheckStatus::Warning,
                 "no active rule pack was loaded");
    } else {
        addCheck(snapshot, "rule_packs_loaded", GatewayCheckStatus::Pass,
                 "active rule packs were loaded");
    }

    if (state.active_rule_count <= 0) {
        hasWarning = true;
        snapshot.verification.status = GatewayReadinessStatus::Warning;
        addCheck(snapshot, "active_rule_count", GatewayCheckStatus::Warning,
                 "no effective safety rules are active");
    } else {
        addCheck(snapshot, "active_rule_count", GatewayCheckStatus::Pass,
                 "effective safety rules are active");
    }

    if (hasWarning) {
        return snapshot;
    }

    if (!state.masking_cache_current) {
        snapshot.verification.status = GatewayReadinessStatus::NotReady;
        addCheck(snapshot, "masking_cache_current",
                 GatewayCheckStatus::NotReady,
                 "masked string cache is missing or stale");
        return snapshot;
    }

    addCheck(snapshot, "masking_cache_current", GatewayCheckStatus::Pass,
             "masked string cache is current");

    if (state.protected_finding_count <= 0) {
        snapshot.verification.status = GatewayReadinessStatus::Warning;
        addCheck(snapshot, "protected_items_present",
                 GatewayCheckStatus::Warning,
                 "safety scan ran but no protected findings were found");
        return snapshot;
    }

    bool original_values_not_included = true;
    std::string original_values_detail;
    for (std::size_t i = 0; i < input.items.size(); ++i) {
        const auto& item = input.items[i];

        GatewayProtectedItem out;
        out.id = makeItemId(i);
        out.kind = item.kind;
        out.location = item.location;
        out.category = item.category;
        out.display_value = item.display_value;
        out.transmission_value = item.transmission_value;
        out.mask_token = item.mask_token;
        out.original_included = false;

        const bool unsafe_display =
            containsOriginal(out.display_value, item.original_value);
        const bool unsafe_transmission =
            containsOriginal(out.transmission_value, item.original_value);

        if (unsafe_display || unsafe_transmission) {
            out.action = GatewayPolicyAction::Block;
            out.reason = "raw original value rejected before protected output";
            out.display_value = "[blocked]";
            out.transmission_value = "[blocked]";
            out.original_included = true;
            snapshot.prompt.blocked_items += 1;
            original_values_not_included = false;
            if (original_values_detail.empty()) {
                original_values_detail =
                    "raw original value appeared in protected output at " +
                    item.location;
            }
        } else if (item.transmission_value.empty()) {
            out.action = GatewayPolicyAction::Omit;
            out.reason = "empty protected transmission value";
            snapshot.prompt.omitted_items += 1;
        } else if (isSensitiveCategory(item.category)) {
            out.action = GatewayPolicyAction::Mask;
            out.reason =
                "sensitive value replaced with protected representation";
            snapshot.prompt.included_items += 1;
            appendPromptItemLine(snapshot.prompt.body, out);
        } else {
            out.action = GatewayPolicyAction::Allow;
            out.reason = "no sensitive category matched";
            snapshot.prompt.included_items += 1;
            appendPromptItemLine(snapshot.prompt.body, out);
        }

        GatewayAuditEvent audit;
        audit.id = makeAuditId(i);
        audit.action = gatewayPolicyActionToText(out.action);
        audit.item_id = out.id;
        audit.category = out.category;
        audit.safe_preview = out.transmission_value;
        audit.reason = out.reason;

        snapshot.protected_items.push_back(out);
        snapshot.audit_events.push_back(audit);
    }

    addCheck(snapshot, "protected_prompt_generated",
             snapshot.prompt.included_items > 0 ? GatewayCheckStatus::Pass
                                                : GatewayCheckStatus::Warning,
             snapshot.prompt.included_items > 0
                 ? "protected prompt was generated with included items"
                 : "no protected prompt items were included");

    if (!original_values_not_included || snapshot.prompt.blocked_items > 0) {
        snapshot.verification.status = GatewayReadinessStatus::Fail;
        addCheck(snapshot, "original_values_not_included",
                 GatewayCheckStatus::Fail, original_values_detail);
        return snapshot;
    }

    addCheck(snapshot, "original_values_not_included",
             GatewayCheckStatus::Pass,
             "raw original values are not included in protected output");

    if (snapshot.prompt.included_items <= 0) {
        snapshot.verification.status = GatewayReadinessStatus::Warning;
        addCheck(snapshot, "protected_items_present",
                 GatewayCheckStatus::Warning,
                 "protected findings exist but no protected prompt items were included");
        return snapshot;
    }

    addCheck(snapshot, "protected_items_present", GatewayCheckStatus::Pass,
             "protected items are available for the prompt");
    snapshot.verification.status =
        hasWarning ? GatewayReadinessStatus::Warning
                   : GatewayReadinessStatus::Pass;

    return snapshot;
}

}  // namespace aura::gateway
