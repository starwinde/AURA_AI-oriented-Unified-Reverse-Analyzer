#pragma once

#include <cstdint>
#include <string>

namespace aura::safety_gateway {

struct UpstreamForwardRequest {
    std::string upstream_url;
    std::string json_body;
    uint32_t timeout_ms = 5000;
};

struct UpstreamForwardResult {
    bool ok = false;
    int status_code = 0;
    std::string body;
    std::string error_code;
    std::string error_detail;
};

UpstreamForwardResult forwardJsonToUpstream(
    const UpstreamForwardRequest& request);

}  // namespace aura::safety_gateway
