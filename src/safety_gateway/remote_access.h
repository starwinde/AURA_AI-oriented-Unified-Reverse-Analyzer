#pragma once

#include "gateway_config.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace aura::safety_gateway {

struct RemoteAccessRequest {
    std::string client_ip;
    std::string target;
    std::unordered_map<std::string, std::string> headers;
};

struct RemoteAccessDecision {
    bool allowed = false;
    std::string result_code;
    std::string detail;
    std::string audit_event_type;
    std::string audit_detail;
    std::vector<std::string> audit_flags;
};

RemoteAccessDecision evaluateRemoteAccess(
    const GatewayRemoteConfig& config,
    const RemoteAccessRequest& request);

}  // namespace aura::safety_gateway
