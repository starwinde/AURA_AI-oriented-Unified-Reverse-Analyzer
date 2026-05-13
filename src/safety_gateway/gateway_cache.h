#pragma once

#include "gateway_request.h"

#include <string>

namespace aura::safety_gateway {

struct GatewayCacheKey {
    std::string content_hash;
    std::string policy_hash;
    std::string kind;
};

struct GatewayCacheEntry {
    GatewayCacheKey key;
    std::string category;
    std::string action;
    std::string protected_text;
    std::string detector_summary;
};

std::string defaultGatewayCachePath();
std::string gatewayContentHash(const GatewayPayloadItem& item);
bool lookupGatewayCache(const std::string& cache_path,
                        const GatewayCacheKey& key,
                        GatewayCacheEntry* out);
bool storeGatewayCache(const std::string& cache_path,
                       const GatewayCacheEntry& entry);

}  // namespace aura::safety_gateway
