#include "control_api.h"

extern "C" {
#include "cJSON.h"
}

#include <algorithm>
#include <chrono>
#include <ctime>
#include <memory>
#include <random>
#include <set>
#include <sstream>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};
using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

std::string isoNow() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buffer;
}

std::string printJson(cJSON* root) {
    char* raw = cJSON_PrintUnformatted(root);
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

void addString(cJSON* object, const char* name, const std::string& value) {
    cJSON_AddStringToObject(object, name, value.c_str());
}

std::string jsonError(const std::string& code, const std::string& message) {
    JsonPtr root(cJSON_CreateObject());
    cJSON_AddBoolToObject(root.get(), "ok", 0);
    cJSON* error = cJSON_AddObjectToObject(root.get(), "error");
    addString(error, "code", code);
    addString(error, "message", message);
    return printJson(root.get());
}

GatewayHttpResponse errorResponse(const std::string& status,
                                  const std::string& code,
                                  const std::string& message) {
    GatewayHttpResponse response;
    response.status = status;
    response.body = jsonError(code, message);
    return response;
}

std::string configToJson(const GatewayConfig& config, const std::string& listen_address) {
    JsonPtr root(cJSON_CreateObject());
    addString(root.get(), "mode", config.mode);
    addString(root.get(), "preset", config.preset);
    addString(root.get(), "cache_db", config.cache_db_path);
    addString(root.get(), "listen", listen_address);
    addString(root.get(), "listen_host", config.remote.listen_host);
    cJSON_AddNumberToObject(root.get(), "listen_port", config.remote.port);
    cJSON_AddBoolToObject(root.get(), "remote_enabled", config.remote.enabled);
    cJSON_AddBoolToObject(root.get(), "require_access_token", config.remote.require_access_token);
    cJSON_AddBoolToObject(root.get(), "allow_query_token", config.remote.allow_query_token);
    cJSON_AddBoolToObject(root.get(), "access_token_configured",
                          !config.remote.access_token_hash.empty());
    cJSON* allowlist = cJSON_AddArrayToObject(root.get(), "ip_allowlist");
    for (const auto& ip : config.remote.ip_allowlist) {
        cJSON_AddItemToArray(allowlist, cJSON_CreateString(ip.c_str()));
    }
    addString(root.get(), "upstream_url", config.forward.upstream_url);
    cJSON_AddBoolToObject(root.get(), "forward_enabled", config.forward.enabled);
    cJSON_AddNumberToObject(root.get(), "forward_timeout_ms", config.forward.timeout_ms);
    return printJson(root.get());
}

bool readString(cJSON* root, const char* name, std::string* out) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(root, name);
    if (!value) return false;
    if (!cJSON_IsString(value) || !value->valuestring) return false;
    *out = value->valuestring;
    return true;
}

bool readBool(cJSON* root, const char* name, bool* out) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(root, name);
    if (!value || !cJSON_IsBool(value)) return false;
    *out = cJSON_IsTrue(value);
    return true;
}

bool readInt(cJSON* root, const char* name, int* out) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(root, name);
    if (!value || !cJSON_IsNumber(value)) return false;
    *out = value->valueint;
    return true;
}

std::string randomToken() {
    static constexpr char kAlphabet[] =
        "ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz23456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, sizeof(kAlphabet) - 2);
    std::string token = "sgw_";
    for (int i = 0; i < 32; ++i) {
        token.push_back(kAlphabet[dist(gen)]);
    }
    return token;
}

std::string demoMcpBody(const std::string& fixture) {
    std::string text = "normal reverse engineering context";
    std::string category = "unknown";
    if (fixture == "pii") {
        text = "alice.smith@example.com and 010-1234-5678";
    } else if (fixture == "secret") {
        text = "api_key = \"sk-DEMOSECRET1234567890\"";
    } else if (fixture == "remote_fail") {
        text = "remote request without token should be blocked before scan";
        category = "remote";
    } else if (fixture == "upstream_timeout") {
        text = "forward timeout demo with alice.smith@example.com";
    }

    std::ostringstream body;
    body << R"({"jsonrpc":"2.0","id":77,"method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{)"
         << R"("request_id":"demo-)" << fixture << "-" << std::chrono::steady_clock::now().time_since_epoch().count() << R"(",)"
         << R"("source":"demo-console","operation":"protect_context","payload":{"items":[{)"
         << R"("kind":"string","location":"demo",)"
         << R"("category":")" << category << R"(",)"
         << R"("text":")";
    for (char ch : text) {
        if (ch == '"' || ch == '\\') body << '\\';
        body << ch;
    }
    body << R"("}]}}}}})";
    return body.str();
}

std::string statsJson(const std::vector<RequestLogEntry>& entries) {
    int masked = 0;
    int blocked = 0;
    int allowed = 0;
    int protected_items = 0;
    for (const auto& entry : entries) {
        if (entry.decision == "blocked") {
            ++blocked;
        } else if (entry.decision == "masked") {
            ++masked;
        } else {
            ++allowed;
        }
        protected_items += static_cast<int>(entry.items.size());
    }
    JsonPtr root(cJSON_CreateObject());
    cJSON_AddNumberToObject(root.get(), "requests_today", static_cast<double>(entries.size()));
    cJSON_AddNumberToObject(root.get(), "masked", masked);
    cJSON_AddNumberToObject(root.get(), "blocked", blocked);
    cJSON_AddNumberToObject(root.get(), "allowed", allowed);
    cJSON_AddNumberToObject(root.get(), "protected_items", protected_items);
    return printJson(root.get());
}

std::string requestsJson(const std::vector<RequestLogEntry>& entries) {
    JsonPtr root(cJSON_CreateObject());
    JsonPtr list(cJSON_Parse(requestLogEntriesToJson(entries).c_str()));
    cJSON_AddItemToObject(root.get(), "requests", list.release());
    return printJson(root.get());
}

}  // namespace

void recordMcpGatewayResult(GatewayControlState* state,
                            McpHttpResult* result,
                            const std::string& client_ip,
                            const RemoteAccessDecision& remote_decision,
                            const UpstreamForwardResult* upstream_result) {
    if (!state || !state->request_log || !state->reveal_store || !result ||
        !result->has_request_log) {
        return;
    }

    result->request_log.client_ip = client_ip.empty() ? "unknown" : client_ip;
    result->request_log.remote_auth_result = remote_decision.result_code;
    if (!remote_decision.audit_event_type.empty()) {
        GatewayAuditEvent event;
        event.event_id = "evt_remote";
        event.timestamp_iso8601 = isoNow();
        event.event_type = remote_decision.audit_event_type;
        event.detail = remote_decision.audit_detail;
        result->request_log.audit_events.push_back(std::move(event));
    }

    if (upstream_result) {
        if (upstream_result->ok) {
            result->request_log.route = "forwarded";
            result->request_log.upstream_status =
                "http_" + std::to_string(upstream_result->status_code);
        } else {
            result->request_log.route = "forward_failed";
            result->request_log.upstream_status = upstream_result->error_code;
            GatewayAuditEvent event;
            event.event_id = "evt_upstream";
            event.timestamp_iso8601 = isoNow();
            event.event_type = upstream_result->error_code;
            event.detail = upstream_result->error_detail;
            result->request_log.audit_events.push_back(std::move(event));
        }
    } else if (result->blocked) {
        result->request_log.route = "blocked";
    }

    for (const auto& record : result->reveal_records) {
        state->reveal_store->put(record);
    }

    const auto evicted = state->request_log->append(result->request_log);
    for (const auto& request_id : evicted) {
        state->reveal_store->eraseByRequestId(request_id);
    }
}

bool handleControlApiRequest(const GatewayHttpRequestView& request,
                             GatewayControlState* state,
                             GatewayHttpResponse* response) {
    if (!response || !state || !state->config || !state->request_log ||
        !state->reveal_store || !state->mcp_options) {
        return false;
    }

    const std::string& target = request.target;
    if (request.method == "GET" && target == "/api/status") {
        JsonPtr root(cJSON_CreateObject());
        addString(root.get(), "product", "Safety Gateway");
        addString(root.get(), "mode", state->config->mode);
        addString(root.get(), "listen", state->listen_address);
        addString(root.get(), "cache_db", state->config->cache_db_path);
        addString(root.get(), "upstream",
                  state->config->forward.enabled ? state->config->forward.upstream_url : "disabled");
        cJSON_AddNumberToObject(root.get(), "request_log_size",
                                static_cast<double>(state->request_log->size()));
        response->body = printJson(root.get());
        return true;
    }

    if (request.method == "GET" && target == "/api/config") {
        response->body = configToJson(*state->config, state->listen_address);
        return true;
    }

    if (request.method == "PUT" && target == "/api/config") {
        JsonPtr root(cJSON_Parse(request.body.c_str()));
        if (!root || !cJSON_IsObject(root.get())) {
            *response = errorResponse("400 Bad Request", "invalid_json", "config body must be a JSON object");
            return true;
        }

        GatewayConfig next = *state->config;
        std::string text;
        int number = 0;
        bool flag = false;
        if (readString(root.get(), "mode", &text)) {
            next.mode = text;
            next.forward.enabled = text == "forward";
        }
        if (readString(root.get(), "listen_host", &text)) next.remote.listen_host = text;
        if (readInt(root.get(), "listen_port", &number) && number > 0 && number <= 65535) {
            next.remote.port = static_cast<uint16_t>(number);
        }
        if (readBool(root.get(), "remote_enabled", &flag)) next.remote.enabled = flag;
        if (readString(root.get(), "upstream_url", &text)) {
            next.forward.upstream_url = text;
            if (!text.empty() && next.mode == "forward") next.forward.enabled = true;
        }
        if (readString(root.get(), "cache_db", &text)) next.cache_db_path = text;
        cJSON* allowlist = cJSON_GetObjectItemCaseSensitive(root.get(), "ip_allowlist");
        if (cJSON_IsArray(allowlist)) {
            next.remote.ip_allowlist.clear();
            cJSON* item = nullptr;
            cJSON_ArrayForEach(item, allowlist) {
                if (cJSON_IsString(item) && item->valuestring && item->valuestring[0]) {
                    next.remote.ip_allowlist.emplace_back(item->valuestring);
                }
            }
        }

        GatewayConfigValidationOptions options;
        options.allow_remote_bind = state->allow_remote_bind;
        const auto validation = validateGatewayConfig(next, options);
        if (!validation.ok) {
            *response = errorResponse("400 Bad Request", validation.error_code, validation.error_detail);
            return true;
        }
        const auto saved = saveGatewayConfig(state->config_path, next);
        if (!saved.ok) {
            *response = errorResponse("400 Bad Request", saved.error_code, saved.error_detail);
            return true;
        }
        *state->config = next;
        state->mcp_options->policy.cache_path = next.cache_db_path;
        response->body = configToJson(*state->config, state->listen_address);
        return true;
    }

    if (request.method == "GET" && target == "/api/stats") {
        response->body = statsJson(state->request_log->latest());
        return true;
    }

    if (request.method == "GET" && target == "/api/requests") {
        response->body = requestsJson(state->request_log->latest(200));
        return true;
    }

    const std::string request_prefix = "/api/requests/";
    if (target.rfind(request_prefix, 0) == 0) {
        std::string rest = target.substr(request_prefix.size());
        const bool reveal = rest.size() > 7 && rest.rfind("/reveal") == rest.size() - 7;
        if (reveal) {
            rest = rest.substr(0, rest.size() - 7);
        }

        if (!reveal && request.method == "GET") {
            RequestLogEntry entry;
            if (!state->request_log->findByRequestId(rest, &entry)) {
                *response = errorResponse("404 Not Found", "request_not_found", "request id not found");
                return true;
            }
            response->body = requestLogEntryToJson(entry);
            return true;
        }

        if (reveal && request.method == "POST") {
            JsonPtr root(cJSON_Parse(request.body.c_str()));
            std::string item_id;
            if (!root || !cJSON_IsObject(root.get()) || !readString(root.get(), "item_id", &item_id)) {
                *response = errorResponse("400 Bad Request", "invalid_reveal_request", "item_id is required");
                return true;
            }
            auto reveal_result = state->reveal_store->reveal(rest, item_id);
            if (reveal_result.found) {
                GatewayAuditEvent event;
                event.event_id = reveal_result.audit_event_id;
                event.timestamp_iso8601 = isoNow();
                event.event_type = "reveal";
                event.detail = "session-only reveal for item " + item_id;
                state->request_log->addAuditEvent(rest, std::move(event));
            }
            response->body = sessionRevealResultToJson(reveal_result);
            return true;
        }
    }

    if (request.method == "POST" && target == "/api/demo/inject") {
        JsonPtr root(cJSON_Parse(request.body.c_str()));
        std::string fixture = "pii";
        if (root && cJSON_IsObject(root.get())) {
            readString(root.get(), "fixture", &fixture);
        }

        auto detailed = handleMcpJsonRpcDetailed(demoMcpBody(fixture), *state->mcp_options);
        RemoteAccessDecision remote;
        remote.allowed = true;
        remote.result_code = fixture == "remote_fail" ? "remote_blocked_missing_token" : "demo_allowed";
        remote.audit_event_type = fixture == "remote_fail" ? "remote_blocked_missing_token" : "demo_injected";
        remote.audit_detail = "demo fixture=" + fixture;
        if (fixture == "remote_fail" && detailed.has_request_log) {
            detailed.blocked = true;
            detailed.request_log.decision = "blocked";
            detailed.request_log.route = "blocked";
        }
        recordMcpGatewayResult(state, &detailed, request.client_ip, remote, nullptr);

        JsonPtr out(cJSON_CreateObject());
        cJSON_AddBoolToObject(out.get(), "ok", detailed.has_request_log);
        addString(out.get(), "fixture", fixture);
        addString(out.get(), "request_id", detailed.has_request_log ? detailed.request_log.request_id : "");
        response->body = printJson(out.get());
        return true;
    }

    if (request.method == "POST" && target == "/api/remote/token/generate") {
        const std::string token = randomToken();
        setGatewayAccessToken(state->config, token);
        saveGatewayConfig(state->config_path, *state->config);
        JsonPtr root(cJSON_CreateObject());
        cJSON_AddBoolToObject(root.get(), "ok", 1);
        addString(root.get(), "token", token);
        addString(root.get(), "message", "Token is shown once. Store it before closing this response.");
        response->body = printJson(root.get());
        return true;
    }

    if (request.method == "GET" && target == "/api/remote/clients") {
        JsonPtr root(cJSON_CreateObject());
        cJSON* clients = cJSON_AddArrayToObject(root.get(), "clients");
        std::set<std::string> seen;
        for (const auto& entry : state->request_log->latest()) {
            if (!entry.client_ip.empty() && seen.insert(entry.client_ip).second) {
                cJSON_AddItemToArray(clients, cJSON_CreateString(entry.client_ip.c_str()));
            }
        }
        response->body = printJson(root.get());
        return true;
    }

    return false;
}

}  // namespace aura::safety_gateway
