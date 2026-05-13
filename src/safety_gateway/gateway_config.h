#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace aura::safety_gateway {

struct GatewayRemoteConfig {
    bool enabled = false;
    std::string listen_host = "127.0.0.1";
    uint16_t port = 8765;
    std::vector<std::string> ip_allowlist = {"127.0.0.1", "::1"};
    bool require_access_token = true;
    std::string access_token_hash;
    bool allow_query_token = true;
};

struct GatewayForwardConfig {
    bool enabled = false;
    std::string upstream_url;
    uint32_t timeout_ms = 5000;
};

struct GatewayConfig {
    std::string mode = "local_protect_only";
    std::string preset = "balanced";
    std::string cache_db_path;
    GatewayRemoteConfig remote;
    GatewayForwardConfig forward;
};

struct GatewayConfigValidationOptions {
    bool allow_remote_bind = false;
};

struct GatewayConfigOverride {
    bool has_listen_host = false;
    std::string listen_host;
    bool has_port = false;
    uint16_t port = 0;
    bool has_cache_db_path = false;
    std::string cache_db_path;
    bool has_upstream_url = false;
    std::string upstream_url;
    bool has_mode = false;
    std::string mode;
};

struct GatewayConfigResult {
    bool ok = false;
    std::string error_code;
    std::string error_detail;
};

GatewayConfig defaultGatewayConfig();
std::string defaultGatewayConfigPath();

// Part 1 stores access tokens with a deterministic FNV-1a based hash.
// This prevents plaintext config persistence, but it is not a password KDF.
std::string hashGatewayAccessToken(const std::string& token);
bool gatewayAccessTokenMatches(const std::string& token,
                               const std::string& token_hash);
void setGatewayAccessToken(GatewayConfig* config, const std::string& token);

void applyGatewayConfigOverride(GatewayConfig* config,
                                const GatewayConfigOverride& override_values);

GatewayConfigResult validateGatewayConfig(
    const GatewayConfig& config,
    const GatewayConfigValidationOptions& options = {});

GatewayConfigResult loadGatewayConfig(const std::string& path,
                                      GatewayConfig* out);
GatewayConfigResult saveGatewayConfig(const std::string& path,
                                      const GatewayConfig& config);

}  // namespace aura::safety_gateway
