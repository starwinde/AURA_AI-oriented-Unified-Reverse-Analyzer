#pragma once

#include "gateway_policy.h"
#include "request_log.h"
#include "session_reveal_store.h"

#include <string>
#include <vector>

namespace aura::safety_gateway {

struct McpHttpOptions {
    GatewayPolicyOptions policy;
    std::string protocol_version = "2025-11-25";
};

struct McpHttpResult {
    std::string response_json;
    bool has_request_log = false;
    RequestLogEntry request_log;
    std::vector<SessionRevealRecord> reveal_records;
    std::string protected_forward_body;
    bool blocked = false;
};

McpHttpResult handleMcpJsonRpcDetailed(const std::string& request_body,
                                       const McpHttpOptions& options);

std::string handleMcpJsonRpc(const std::string& request_body,
                             const McpHttpOptions& options);

}  // namespace aura::safety_gateway
