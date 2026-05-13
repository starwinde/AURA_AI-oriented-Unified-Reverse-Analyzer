#include "gateway_config.h"

extern "C" {
#include "cJSON.h"
}

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};
using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

GatewayConfigResult okResult() {
    return {true, {}, {}};
}

GatewayConfigResult errorResult(std::string code, std::string detail) {
    return {false, std::move(code), std::move(detail)};
}

std::string lowerAscii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

bool isLoopbackHost(const std::string& host) {
    return host == "127.0.0.1" || host == "localhost" || host == "::1";
}

bool isHttpUrl(const std::string& url) {
    return lowerAscii(url).rfind("http://", 0) == 0;
}

bool isHttpsUrl(const std::string& url) {
    return lowerAscii(url).rfind("https://", 0) == 0;
}

const cJSON* objectField(const cJSON* root, const char* name) {
    return cJSON_GetObjectItemCaseSensitive(const_cast<cJSON*>(root), name);
}

bool readStringField(const cJSON* root,
                     const char* name,
                     std::string* out,
                     GatewayConfigResult* error) {
    const cJSON* value = objectField(root, name);
    if (!value) return true;
    if (!cJSON_IsString(value) || !value->valuestring) {
        *error = errorResult("invalid_config_field",
                             std::string(name) + " must be a string");
        return false;
    }
    *out = value->valuestring;
    return true;
}

bool readBoolField(const cJSON* root,
                   const char* name,
                   bool* out,
                   GatewayConfigResult* error) {
    const cJSON* value = objectField(root, name);
    if (!value) return true;
    if (!cJSON_IsBool(value)) {
        *error = errorResult("invalid_config_field",
                             std::string(name) + " must be a boolean");
        return false;
    }
    *out = cJSON_IsTrue(value);
    return true;
}

bool readUint16Field(const cJSON* root,
                     const char* name,
                     uint16_t* out,
                     GatewayConfigResult* error) {
    const cJSON* value = objectField(root, name);
    if (!value) return true;
    if (!cJSON_IsNumber(value) || value->valuedouble < 1.0 ||
        value->valuedouble > 65535.0) {
        *error = errorResult("invalid_config_field",
                             std::string(name) + " must be 1..65535");
        return false;
    }
    *out = static_cast<uint16_t>(value->valueint);
    return true;
}

bool readUint32Field(const cJSON* root,
                     const char* name,
                     uint32_t* out,
                     GatewayConfigResult* error) {
    const cJSON* value = objectField(root, name);
    if (!value) return true;
    if (!cJSON_IsNumber(value) || value->valuedouble < 1.0) {
        *error = errorResult("invalid_config_field",
                             std::string(name) + " must be a positive integer");
        return false;
    }
    *out = static_cast<uint32_t>(value->valuedouble);
    return true;
}

bool readStringArrayField(const cJSON* root,
                          const char* name,
                          std::vector<std::string>* out,
                          GatewayConfigResult* error) {
    const cJSON* value = objectField(root, name);
    if (!value) return true;
    if (!cJSON_IsArray(value)) {
        *error = errorResult("invalid_config_field",
                             std::string(name) + " must be an array");
        return false;
    }
    std::vector<std::string> parsed;
    const cJSON* item = nullptr;
    cJSON_ArrayForEach(item, value) {
        if (!cJSON_IsString(item) || !item->valuestring || !item->valuestring[0]) {
            *error = errorResult("invalid_config_field",
                                 std::string(name) +
                                     " must contain non-empty strings");
            return false;
        }
        parsed.emplace_back(item->valuestring);
    }
    *out = std::move(parsed);
    return true;
}

std::string printJson(cJSON* root) {
    char* raw = cJSON_Print(root);
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

void addStringArray(cJSON* root,
                    const char* name,
                    const std::vector<std::string>& values) {
    cJSON* array = cJSON_AddArrayToObject(root, name);
    for (const auto& value : values) {
        cJSON_AddItemToArray(array, cJSON_CreateString(value.c_str()));
    }
}

}  // namespace

GatewayConfig defaultGatewayConfig() {
    return GatewayConfig{};
}

std::string defaultGatewayConfigPath() {
    return (std::filesystem::path(".aura") / "safety-gateway-config.json")
        .string();
}

std::string hashGatewayAccessToken(const std::string& token) {
    constexpr uint64_t kOffset = 1469598103934665603ull;
    constexpr uint64_t kPrime = 1099511628211ull;
    uint64_t hash = kOffset;
    const std::string scoped = "aura-safety-gateway-token-v1:" + token;
    for (const unsigned char ch : scoped) {
        hash ^= ch;
        hash *= kPrime;
    }
    std::ostringstream out;
    out << "fnv1a64:v1:" << std::hex << std::setw(16) << std::setfill('0')
        << hash;
    return out.str();
}

bool gatewayAccessTokenMatches(const std::string& token,
                               const std::string& token_hash) {
    return !token.empty() && !token_hash.empty() &&
           hashGatewayAccessToken(token) == token_hash;
}

void setGatewayAccessToken(GatewayConfig* config, const std::string& token) {
    if (!config) return;
    config->remote.access_token_hash = hashGatewayAccessToken(token);
}

void applyGatewayConfigOverride(GatewayConfig* config,
                                const GatewayConfigOverride& override_values) {
    if (!config) return;
    if (override_values.has_listen_host) {
        config->remote.listen_host = override_values.listen_host;
    }
    if (override_values.has_port) {
        config->remote.port = override_values.port;
    }
    if (override_values.has_cache_db_path) {
        config->cache_db_path = override_values.cache_db_path;
    }
    if (override_values.has_upstream_url) {
        config->forward.upstream_url = override_values.upstream_url;
        config->forward.enabled = !override_values.upstream_url.empty();
    }
    if (override_values.has_mode) {
        config->mode = override_values.mode;
        config->forward.enabled = override_values.mode == "forward";
    }
}

GatewayConfigResult validateGatewayConfig(
    const GatewayConfig& config,
    const GatewayConfigValidationOptions& options) {
    if (config.mode != "local_protect_only" && config.mode != "forward") {
        return errorResult("invalid_mode",
                           "mode must be local_protect_only or forward");
    }
    if (config.preset.empty()) {
        return errorResult("invalid_preset", "preset must not be empty");
    }
    if (config.remote.listen_host.empty()) {
        return errorResult("invalid_listen_host", "listen_host must not be empty");
    }
    if (config.remote.listen_host == "::1") {
        return errorResult("ipv6_listen_not_supported",
                           "Part 1 HTTP server supports IPv4 listen hosts only");
    }
    if (!isLoopbackHost(config.remote.listen_host) && !options.allow_remote_bind) {
        return errorResult("remote_bind_requires_opt_in",
                           "non-loopback listen host requires explicit opt-in");
    }
    if (config.remote.ip_allowlist.empty()) {
        return errorResult("empty_ip_allowlist",
                           "remote.ip_allowlist must contain at least one IP");
    }
    for (const auto& ip : config.remote.ip_allowlist) {
        if (ip.empty()) {
            return errorResult("invalid_ip_allowlist",
                               "remote.ip_allowlist must not contain empty values");
        }
    }
    if (config.remote.enabled && config.remote.require_access_token &&
        config.remote.access_token_hash.empty()) {
        return errorResult("missing_access_token_hash",
                           "remote mode requires an access token hash");
    }
    if (config.forward.enabled || config.mode == "forward") {
        if (config.forward.upstream_url.empty()) {
            return errorResult("missing_upstream_url",
                               "forward mode requires forward.upstream_url");
        }
        if (isHttpsUrl(config.forward.upstream_url)) {
            return errorResult("https_not_supported",
                               "Part 1 upstream forwarding supports http only");
        }
        if (!isHttpUrl(config.forward.upstream_url)) {
            return errorResult("invalid_upstream_url",
                               "upstream_url must start with http://");
        }
    } else if (!config.forward.upstream_url.empty() &&
               !isHttpUrl(config.forward.upstream_url)) {
        return errorResult("invalid_upstream_url",
                           "upstream_url must start with http://");
    }
    if (config.forward.timeout_ms == 0) {
        return errorResult("invalid_timeout", "forward.timeout_ms must be positive");
    }
    return okResult();
}

GatewayConfigResult loadGatewayConfig(const std::string& path,
                                      GatewayConfig* out) {
    if (!out) {
        return errorResult("invalid_argument", "out config pointer is null");
    }
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return errorResult("config_open_failed", "could not open " + path);
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    JsonPtr root(cJSON_Parse(buffer.str().c_str()));
    if (!root || !cJSON_IsObject(root.get())) {
        return errorResult("config_parse_failed",
                           "config JSON must be an object");
    }

    GatewayConfig config = defaultGatewayConfig();
    GatewayConfigResult error;
    if (!readStringField(root.get(), "mode", &config.mode, &error) ||
        !readStringField(root.get(), "preset", &config.preset, &error) ||
        !readStringField(root.get(), "cache_db_path", &config.cache_db_path,
                         &error)) {
        return error;
    }

    const cJSON* remote = objectField(root.get(), "remote");
    if (remote) {
        if (!cJSON_IsObject(remote)) {
            return errorResult("invalid_config_field", "remote must be an object");
        }
        if (!readBoolField(remote, "enabled", &config.remote.enabled, &error) ||
            !readStringField(remote, "listen_host", &config.remote.listen_host,
                             &error) ||
            !readUint16Field(remote, "port", &config.remote.port, &error) ||
            !readStringArrayField(remote, "ip_allowlist",
                                  &config.remote.ip_allowlist, &error) ||
            !readBoolField(remote, "require_access_token",
                           &config.remote.require_access_token, &error) ||
            !readStringField(remote, "access_token_hash",
                             &config.remote.access_token_hash, &error) ||
            !readBoolField(remote, "allow_query_token",
                           &config.remote.allow_query_token, &error)) {
            return error;
        }
    }

    const cJSON* forward = objectField(root.get(), "forward");
    if (forward) {
        if (!cJSON_IsObject(forward)) {
            return errorResult("invalid_config_field", "forward must be an object");
        }
        if (!readBoolField(forward, "enabled", &config.forward.enabled, &error) ||
            !readStringField(forward, "upstream_url",
                             &config.forward.upstream_url, &error) ||
            !readUint32Field(forward, "timeout_ms", &config.forward.timeout_ms,
                             &error)) {
            return error;
        }
    }

    *out = std::move(config);
    return okResult();
}

GatewayConfigResult saveGatewayConfig(const std::string& path,
                                      const GatewayConfig& config) {
    GatewayConfigValidationOptions save_options;
    save_options.allow_remote_bind = true;
    const auto validation = validateGatewayConfig(config, save_options);
    if (!validation.ok) return validation;

    JsonPtr root(cJSON_CreateObject());
    cJSON_AddStringToObject(root.get(), "mode", config.mode.c_str());
    cJSON_AddStringToObject(root.get(), "preset", config.preset.c_str());
    cJSON_AddStringToObject(root.get(), "cache_db_path",
                            config.cache_db_path.c_str());

    cJSON* remote = cJSON_AddObjectToObject(root.get(), "remote");
    cJSON_AddBoolToObject(remote, "enabled", config.remote.enabled);
    cJSON_AddStringToObject(remote, "listen_host",
                            config.remote.listen_host.c_str());
    cJSON_AddNumberToObject(remote, "port", config.remote.port);
    addStringArray(remote, "ip_allowlist", config.remote.ip_allowlist);
    cJSON_AddBoolToObject(remote, "require_access_token",
                          config.remote.require_access_token);
    cJSON_AddStringToObject(remote, "access_token_hash",
                            config.remote.access_token_hash.c_str());
    cJSON_AddBoolToObject(remote, "allow_query_token",
                          config.remote.allow_query_token);

    cJSON* forward = cJSON_AddObjectToObject(root.get(), "forward");
    cJSON_AddBoolToObject(forward, "enabled", config.forward.enabled);
    cJSON_AddStringToObject(forward, "upstream_url",
                            config.forward.upstream_url.c_str());
    cJSON_AddNumberToObject(forward, "timeout_ms", config.forward.timeout_ms);

    const std::filesystem::path output_path(path);
    const auto parent = output_path.parent_path();
    if (!parent.empty()) {
        std::error_code ec;
        std::filesystem::create_directories(parent, ec);
        if (ec) {
            return errorResult("config_directory_failed",
                               "could not create " + parent.string() + ": " +
                                   ec.message());
        }
    }

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        return errorResult("config_write_failed", "could not write " + path);
    }
    out << printJson(root.get()) << "\n";
    if (!out) {
        return errorResult("config_write_failed", "write failed for " + path);
    }
    return okResult();
}

}  // namespace aura::safety_gateway
