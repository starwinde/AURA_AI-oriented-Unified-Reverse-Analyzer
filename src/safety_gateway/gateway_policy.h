#pragma once

#include "gateway_request.h"

namespace aura::safety_gateway {

struct GatewayPolicyOptions {
    std::string policy_hash = "default-policy";
    bool use_cache = true;
    std::string cache_path;
    bool include_cache_path_in_response = true;
};

GatewayResponse evaluateGatewayRequest(const GatewayRequest& request,
                                       const GatewayPolicyOptions& options);

}  // namespace aura::safety_gateway
