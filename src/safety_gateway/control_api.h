#pragma once

#include "gateway_config.h"
#include "mcp_http.h"
#include "remote_access.h"
#include "request_log.h"
#include "session_reveal_store.h"
#include "upstream_forwarder.h"

#include <string>
#include <unordered_map>

namespace aura::safety_gateway {

struct GatewayHttpRequestView {
    std::string method;
    std::string target;
    std::string body;
    std::string client_ip;
    std::unordered_map<std::string, std::string> headers;
};

struct GatewayHttpResponse {
    std::string status = "200 OK";
    std::string content_type = "application/json";
    std::string body = "{}";
};

struct GatewayControlState {
    GatewayConfig* config = nullptr;
    McpHttpOptions* mcp_options = nullptr;
    RequestLog* request_log = nullptr;
    SessionRevealStore* reveal_store = nullptr;
    std::string config_path;
    std::string listen_address;
    bool allow_remote_bind = false;
};

void recordMcpGatewayResult(GatewayControlState* state,
                            McpHttpResult* result,
                            const std::string& client_ip,
                            const RemoteAccessDecision& remote_decision,
                            const UpstreamForwardResult* upstream_result);

bool handleControlApiRequest(const GatewayHttpRequestView& request,
                             GatewayControlState* state,
                             GatewayHttpResponse* response);

}  // namespace aura::safety_gateway
