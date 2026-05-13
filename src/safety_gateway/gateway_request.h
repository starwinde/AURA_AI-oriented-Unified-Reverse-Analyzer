#pragma once

#include <string>
#include <vector>

namespace aura::safety_gateway {

struct GatewayPayloadItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string text;
};

struct GatewayRequest {
    std::string request_id;
    std::string source;
    std::string operation;
    std::vector<GatewayPayloadItem> items;
};

struct GatewayOutputItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string protected_text;
    std::string action;
    bool original_included = false;
};

struct GatewayAuditRecord {
    std::string action;
    std::string kind;
    std::string location;
    std::string category;
    std::string safe_preview;
    std::string reason;
};

struct GatewayResponse {
    std::string request_id;
    std::string decision = "pass";
    std::string cache_path;
    std::string route = "local";
    int items_total = 0;
    int masked_count = 0;
    int blocked_count = 0;
    bool raw_original_included = false;
    std::vector<GatewayOutputItem> items;
    std::vector<GatewayAuditRecord> audit;
};

bool parseGatewayRequest(const std::string& json, GatewayRequest* out, std::string* error);
std::string gatewayResponseToJson(const GatewayResponse& response, bool compact);

}  // namespace aura::safety_gateway
