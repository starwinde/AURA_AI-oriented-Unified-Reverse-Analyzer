#include "mcp_http.h"

extern "C" {
#include "cJSON.h"
}

#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};
using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

struct JsonStringCandidate {
    std::string path;
    std::string text;
};

std::string printJson(cJSON* root) {
    char* raw = cJSON_PrintUnformatted(root);
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

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

std::string shortPreview(const std::string& value) {
    return "len=" + std::to_string(value.size());
}

bool hasPrefix(const std::string& value, const std::string& prefix) {
    return value.size() >= prefix.size() &&
           value.compare(0, prefix.size(), prefix) == 0;
}

bool hasSuffix(const std::string& value, const std::string& suffix) {
    return value.size() >= suffix.size() &&
           value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool isPayloadItemPathWithSuffix(const std::string& path, const char* suffix) {
    return hasPrefix(path, "params.arguments.payload.items[") &&
           hasSuffix(path, suffix);
}

bool isPayloadItemTextPath(const std::string& path) {
    return isPayloadItemPathWithSuffix(path, ".text");
}

bool isGatewayControlPath(const std::string& path) {
    if (path == "params.arguments.request_id" ||
        path == "params.arguments.source" ||
        path == "params.arguments.operation") {
        return true;
    }
    return isPayloadItemPathWithSuffix(path, ".kind") ||
           isPayloadItemPathWithSuffix(path, ".location") ||
           isPayloadItemPathWithSuffix(path, ".category");
}

bool isToolCallParamControlPath(const std::string& path) {
    return path == "params.name";
}

std::string jsonIdToRequestId(cJSON* request) {
    cJSON* id = cJSON_GetObjectItemCaseSensitive(request, "id");
    if (cJSON_IsString(id) && id->valuestring && id->valuestring[0]) {
        return id->valuestring;
    }
    if (cJSON_IsNumber(id)) {
        return "jsonrpc-" + std::to_string(id->valueint);
    }
    return "jsonrpc-notification";
}

void collectRewritableToolCallParamStrings(cJSON* node,
                                           const std::string& path,
                                           std::vector<JsonStringCandidate>* candidates) {
    if (!node || !candidates) return;
    if (path == "params.arguments") {
        return;
    }
    if (cJSON_IsString(node) && node->valuestring && node->valuestring[0]) {
        if (!isToolCallParamControlPath(path)) {
            JsonStringCandidate candidate;
            candidate.path = path;
            candidate.text = node->valuestring;
            candidates->push_back(std::move(candidate));
        }
        return;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            collectRewritableToolCallParamStrings(child,
                                                  path.empty() ? key : path + "." + key,
                                                  candidates);
        }
        return;
    }
    if (cJSON_IsArray(node)) {
        int index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++index) {
            collectRewritableToolCallParamStrings(child,
                                                  path + "[" + std::to_string(index) + "]",
                                                  candidates);
        }
    }
}

void collectRewritableArgumentStrings(cJSON* node,
                                      const std::string& path,
                                      std::vector<JsonStringCandidate>* candidates) {
    if (!node || !candidates) return;
    if (cJSON_IsString(node) && node->valuestring && node->valuestring[0]) {
        if (!isGatewayControlPath(path)) {
            JsonStringCandidate candidate;
            candidate.path = path;
            candidate.text = node->valuestring;
            candidates->push_back(std::move(candidate));
        }
        return;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            collectRewritableArgumentStrings(child,
                                             path.empty() ? key : path + "." + key,
                                             candidates);
        }
        return;
    }
    if (cJSON_IsArray(node)) {
        int index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++index) {
            collectRewritableArgumentStrings(child,
                                             path + "[" + std::to_string(index) + "]",
                                             candidates);
        }
    }
}

void collectJsonStrings(cJSON* node,
                        const std::string& path,
                        std::vector<GatewayPayloadItem>* items) {
    if (!node || !items) return;
    if (cJSON_IsString(node) && node->valuestring && node->valuestring[0]) {
        GatewayPayloadItem item;
        item.kind = "json_string";
        item.location = path.empty() ? "$" : path;
        item.category = "unknown";
        item.text = node->valuestring;
        items->push_back(std::move(item));
        return;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            if (path == "params" && key == "name") {
                continue;
            }
            collectJsonStrings(child,
                               path.empty() ? key : path + "." + key,
                               items);
        }
        return;
    }
    if (cJSON_IsArray(node)) {
        int index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++index) {
            collectJsonStrings(child,
                               path + "[" + std::to_string(index) + "]",
                               items);
        }
    }
}

void replaceJsonStringsInTraversal(cJSON* node,
                                   const std::string& path,
                                   const std::vector<GatewayOutputItem>& outputs,
                                   size_t* index) {
    if (!node || !index) return;
    if (cJSON_IsString(node) && node->valuestring && node->valuestring[0]) {
        if (*index < outputs.size()) {
            cJSON_SetValuestring(node, outputs[*index].protected_text.c_str());
        }
        ++(*index);
        return;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            if (path == "params" && key == "name") {
                continue;
            }
            replaceJsonStringsInTraversal(child,
                                          path.empty() ? key : path + "." + key,
                                          outputs,
                                          index);
        }
        return;
    }
    if (cJSON_IsArray(node)) {
        int array_index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++array_index) {
            replaceJsonStringsInTraversal(child,
                                          path + "[" + std::to_string(array_index) + "]",
                                          outputs,
                                          index);
        }
    }
}

bool replaceStringAtPath(cJSON* node,
                         const std::string& path,
                         const std::string& target_path,
                         const std::string& value) {
    if (!node) return false;
    if (cJSON_IsString(node)) {
        if (path != target_path) return false;
        cJSON_SetValuestring(node, value.c_str());
        return true;
    }
    if (cJSON_IsObject(node)) {
        for (cJSON* child = node->child; child; child = child->next) {
            const std::string key = child->string ? child->string : "";
            if (replaceStringAtPath(child,
                                    path.empty() ? key : path + "." + key,
                                    target_path,
                                    value)) {
                return true;
            }
        }
        return false;
    }
    if (cJSON_IsArray(node)) {
        int array_index = 0;
        for (cJSON* child = node->child; child; child = child->next, ++array_index) {
            if (replaceStringAtPath(child,
                                    path + "[" + std::to_string(array_index) + "]",
                                    target_path,
                                    value)) {
                return true;
            }
        }
    }
    return false;
}

void copyJsonId(cJSON* response, cJSON* request) {
    cJSON* id = cJSON_GetObjectItemCaseSensitive(request, "id");
    if (id) {
        cJSON_AddItemToObject(response, "id", cJSON_Duplicate(id, 1));
    } else {
        cJSON_AddNullToObject(response, "id");
    }
}

cJSON* baseResponse(cJSON* request) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "jsonrpc", "2.0");
    copyJsonId(root, request);
    return root;
}

std::string errorResponse(cJSON* request, int code, const char* message) {
    JsonPtr root(baseResponse(request));
    cJSON* err = cJSON_AddObjectToObject(root.get(), "error");
    cJSON_AddNumberToObject(err, "code", code);
    cJSON_AddStringToObject(err, "message", message);
    return printJson(root.get());
}

std::string parseErrorResponse() {
    JsonPtr root(cJSON_CreateObject());
    cJSON_AddStringToObject(root.get(), "jsonrpc", "2.0");
    cJSON_AddNullToObject(root.get(), "id");
    cJSON* err = cJSON_AddObjectToObject(root.get(), "error");
    cJSON_AddNumberToObject(err, "code", -32700);
    cJSON_AddStringToObject(err, "message", "parse error");
    return printJson(root.get());
}

std::string protocolVersionFromRequest(cJSON* request, const McpHttpOptions& options) {
    cJSON* params = cJSON_GetObjectItemCaseSensitive(request, "params");
    cJSON* version = params ? cJSON_GetObjectItemCaseSensitive(params, "protocolVersion") : nullptr;
    if (cJSON_IsString(version) && version->valuestring && version->valuestring[0]) {
        return version->valuestring;
    }
    return options.protocol_version;
}

void replaceJsonString(cJSON* object, const char* name, const std::string& value) {
    cJSON_ReplaceItemInObjectCaseSensitive(object, name, cJSON_CreateString(value.c_str()));
}

std::string protectedForwardBody(cJSON* request,
                                 const GatewayResponse& gateway_response) {
    JsonPtr copy(cJSON_Duplicate(request, 1));
    cJSON* params = cJSON_GetObjectItemCaseSensitive(copy.get(), "params");
    cJSON* arguments = params ? cJSON_GetObjectItemCaseSensitive(params, "arguments") : nullptr;
    cJSON* payload = arguments ? cJSON_GetObjectItemCaseSensitive(arguments, "payload") : nullptr;
    cJSON* items = payload ? cJSON_GetObjectItemCaseSensitive(payload, "items") : nullptr;
    if (!cJSON_IsArray(items)) {
        if (params) {
            for (const auto& item : gateway_response.items) {
                if (hasPrefix(item.location, "params.") &&
                    !isToolCallParamControlPath(item.location)) {
                    replaceStringAtPath(params,
                                        "params",
                                        item.location,
                                        item.protected_text);
                }
            }
        }
        return printJson(copy.get());
    }
    if (!gateway_response.items.empty() &&
        hasPrefix(gateway_response.items.front().location, "params.")) {
        for (const auto& item : gateway_response.items) {
            if (hasPrefix(item.location, "params.") &&
                !isToolCallParamControlPath(item.location)) {
                replaceStringAtPath(params,
                                    "params",
                                    item.location,
                                    item.protected_text);
            }
        }
        return printJson(copy.get());
    }
    const int count = cJSON_GetArraySize(items);
    int response_index = 0;
    for (int i = 0; i < count && response_index < static_cast<int>(gateway_response.items.size()); ++i) {
        cJSON* item = cJSON_GetArrayItem(items, i);
        if (cJSON_IsObject(item)) {
            replaceJsonString(item,
                              "text",
                              gateway_response.items[static_cast<size_t>(response_index)].protected_text);
            ++response_index;
        }
    }
    for (size_t i = static_cast<size_t>(response_index); i < gateway_response.items.size(); ++i) {
        const auto& item = gateway_response.items[i];
        if (hasPrefix(item.location, "params.") &&
            !isToolCallParamControlPath(item.location) &&
            !isGatewayControlPath(item.location)) {
            replaceStringAtPath(params,
                                "params",
                                item.location,
                                item.protected_text);
        }
    }
    return printJson(copy.get());
}

bool parseGatewayToolOrGenericRequest(cJSON* request,
                                      const std::string& method_name,
                                      const std::string& tool_name,
                                      GatewayRequest* gateway_request,
                                      std::string* parse_error) {
    cJSON* params = cJSON_GetObjectItemCaseSensitive(request, "params");
    cJSON* arguments = params ? cJSON_GetObjectItemCaseSensitive(params, "arguments") : nullptr;
    if (tool_name == "aura_gateway_protect_context" && cJSON_IsObject(arguments)) {
        char* raw_arguments = cJSON_PrintUnformatted(arguments);
        std::string argument_json = raw_arguments ? raw_arguments : "{}";
        cJSON_free(raw_arguments);
        if (parseGatewayRequest(argument_json, gateway_request, parse_error)) {
            std::vector<JsonStringCandidate> candidates;
            collectRewritableArgumentStrings(arguments, "params.arguments", &candidates);
            for (const auto& candidate : candidates) {
                if (isPayloadItemTextPath(candidate.path)) {
                    continue;
                }
                GatewayPayloadItem item;
                item.kind = "json_string";
                item.location = candidate.path;
                item.category = "unknown";
                item.text = candidate.text;
                gateway_request->items.push_back(std::move(item));
            }
            std::vector<JsonStringCandidate> param_candidates;
            collectRewritableToolCallParamStrings(params, "params", &param_candidates);
            for (const auto& candidate : param_candidates) {
                GatewayPayloadItem item;
                item.kind = "json_string";
                item.location = candidate.path;
                item.category = "unknown";
                item.text = candidate.text;
                gateway_request->items.push_back(std::move(item));
            }
            return true;
        }
    }

    GatewayRequest parsed;
    parsed.request_id = jsonIdToRequestId(request);
    parsed.source = "mcp";
    parsed.operation = tool_name.empty() ? method_name : tool_name;
    if (cJSON_IsObject(arguments)) {
        collectJsonStrings(arguments, "params.arguments", &parsed.items);
        std::vector<JsonStringCandidate> param_candidates;
        collectRewritableToolCallParamStrings(params, "params", &param_candidates);
        for (const auto& candidate : param_candidates) {
            GatewayPayloadItem item;
            item.kind = "json_string";
            item.location = candidate.path;
            item.category = "unknown";
            item.text = candidate.text;
            parsed.items.push_back(std::move(item));
        }
    } else if (params) {
        collectJsonStrings(params, "params", &parsed.items);
    }
    *gateway_request = std::move(parsed);
    if (parse_error) parse_error->clear();
    return true;
}

RequestLogEntry makeRequestLogEntry(const GatewayRequest& gateway_request,
                                    const GatewayResponse& gateway_response,
                                    const std::string& method,
                                    const std::string& tool_name,
                                    const std::string& protected_payload_json) {
    RequestLogEntry entry;
    entry.request_id = gateway_request.request_id;
    entry.timestamp_iso8601 = isoNow();
    entry.client_name = gateway_request.source.empty() ? "mcp-client" : gateway_request.source;
    entry.client_ip = "unknown";
    entry.method = method;
    entry.tool_name = tool_name;
    entry.decision = gateway_response.blocked_count > 0 ? "blocked" :
                     (gateway_response.masked_count > 0 ? "masked" : "allowed");
    entry.route = gateway_response.blocked_count > 0 ? "blocked" : "local_protect_only";
    entry.remote_auth_result = "local_loopback_allowed";
    entry.upstream_status = "not_forwarded";
    entry.protected_payload_json = protected_payload_json;

    for (size_t i = 0; i < gateway_response.items.size(); ++i) {
        const auto& out = gateway_response.items[i];
        GatewayItemDecision decision;
        decision.item_id = "item_" + std::to_string(i + 1);
        decision.category = out.category;
        decision.action = out.action;
        decision.protected_value = out.protected_text;
        decision.confidence = out.action == "allow" ? 0.0 : 0.70;
        decision.reason = i < gateway_response.audit.size()
                              ? gateway_response.audit[i].reason
                              : "gateway evaluation";
        if (i < gateway_request.items.size()) {
            decision.original_preview = shortPreview(gateway_request.items[i].text);
        }
        entry.items.push_back(std::move(decision));
    }

    for (size_t i = 0; i < gateway_response.audit.size(); ++i) {
        const auto& audit = gateway_response.audit[i];
        GatewayAuditEvent event;
        event.event_id = "evt_" + std::to_string(i + 1);
        event.timestamp_iso8601 = entry.timestamp_iso8601;
        event.event_type = audit.action;
        event.detail = audit.kind + " " + audit.location + " " + audit.reason;
        entry.audit_events.push_back(std::move(event));
    }
    return entry;
}

std::vector<SessionRevealRecord> makeRevealRecords(const GatewayRequest& gateway_request,
                                                   const GatewayResponse& gateway_response,
                                                   const RequestLogEntry& entry) {
    std::vector<SessionRevealRecord> records;
    for (size_t i = 0; i < gateway_response.items.size() &&
                       i < gateway_request.items.size() &&
                       i < entry.items.size(); ++i) {
        if (gateway_response.items[i].action != "mask") {
            continue;
        }
        SessionRevealRecord record;
        record.request_id = entry.request_id;
        record.item_id = entry.items[i].item_id;
        record.category = gateway_response.items[i].category;
        record.original = gateway_request.items[i].text;
        records.push_back(std::move(record));
    }
    return records;
}

}  // namespace

McpHttpResult handleMcpJsonRpcDetailed(const std::string& request_body,
                                       const McpHttpOptions& options) {
    McpHttpResult detailed;
    JsonPtr request(cJSON_Parse(request_body.c_str()));
    if (!request || !cJSON_IsObject(request.get())) {
        detailed.response_json = parseErrorResponse();
        return detailed;
    }

    cJSON* method = cJSON_GetObjectItemCaseSensitive(request.get(), "method");
    if (!cJSON_IsString(method) || !method->valuestring) {
        detailed.response_json = errorResponse(request.get(), -32600, "invalid request");
        return detailed;
    }
    const std::string name = method->valuestring;

    if (name == "initialize") {
        JsonPtr root(baseResponse(request.get()));
        cJSON* result = cJSON_AddObjectToObject(root.get(), "result");
        cJSON_AddStringToObject(result, "protocolVersion",
                                protocolVersionFromRequest(request.get(), options).c_str());
        cJSON_AddItemToObject(result, "capabilities", cJSON_CreateObject());
        cJSON* server = cJSON_AddObjectToObject(result, "serverInfo");
        cJSON_AddStringToObject(server, "name", "aura-safety-gateway");
        cJSON_AddStringToObject(server, "version", "0.1.0");
        detailed.response_json = printJson(root.get());
        return detailed;
    }

    if (name == "tools/list") {
        JsonPtr root(baseResponse(request.get()));
        cJSON* result = cJSON_AddObjectToObject(root.get(), "result");
        cJSON* tools = cJSON_AddArrayToObject(result, "tools");
        cJSON* tool = cJSON_CreateObject();
        cJSON_AddStringToObject(tool, "name", "aura_gateway_protect_context");
        cJSON_AddStringToObject(tool, "description",
                                "Protect AURA context before LLM/MCP export");
        cJSON* schema = cJSON_AddObjectToObject(tool, "inputSchema");
        cJSON_AddStringToObject(schema, "type", "object");
        cJSON_AddItemToArray(tools, tool);
        detailed.response_json = printJson(root.get());
        return detailed;
    }

    if (name == "tools/call") {
        cJSON* params = cJSON_GetObjectItemCaseSensitive(request.get(), "params");
        cJSON* tool_name = params ? cJSON_GetObjectItemCaseSensitive(params, "name") : nullptr;
        cJSON* arguments = params ? cJSON_GetObjectItemCaseSensitive(params, "arguments") : nullptr;
        if (!cJSON_IsString(tool_name) || !tool_name->valuestring || !tool_name->valuestring[0]) {
            detailed.response_json = errorResponse(request.get(), -32602, "tools/call requires params.name");
            return detailed;
        }
        if (arguments && !cJSON_IsObject(arguments)) {
            detailed.response_json = errorResponse(request.get(), -32602, "tools/call params.arguments must be an object");
            return detailed;
        }

        GatewayRequest gateway_request;
        std::string parse_error;
        if (!parseGatewayToolOrGenericRequest(request.get(),
                                              name,
                                              tool_name->valuestring,
                                              &gateway_request,
                                              &parse_error)) {
            detailed.response_json = errorResponse(request.get(), -32602, parse_error.c_str());
            return detailed;
        }

        const auto gateway_response = evaluateGatewayRequest(gateway_request, options.policy);
        const std::string gateway_json = gatewayResponseToJson(gateway_response, true);
        detailed.has_request_log = true;
        detailed.request_log =
            makeRequestLogEntry(gateway_request,
                                gateway_response,
                                name,
                                tool_name->valuestring ? tool_name->valuestring : "",
                                gateway_json);
        detailed.reveal_records =
            makeRevealRecords(gateway_request, gateway_response, detailed.request_log);
        detailed.blocked = gateway_response.blocked_count > 0;
        if (!detailed.blocked) {
            detailed.protected_forward_body = protectedForwardBody(request.get(), gateway_response);
        }

        JsonPtr root(baseResponse(request.get()));
        cJSON* result = cJSON_AddObjectToObject(root.get(), "result");
        cJSON* content = cJSON_AddArrayToObject(result, "content");
        cJSON* text = cJSON_CreateObject();
        cJSON_AddStringToObject(text, "type", "text");
        cJSON_AddStringToObject(text, "text", gateway_json.c_str());
        cJSON_AddItemToArray(content, text);
        detailed.response_json = printJson(root.get());
        return detailed;
    }

    cJSON* params = cJSON_GetObjectItemCaseSensitive(request.get(), "params");
    GatewayRequest gateway_request;
    gateway_request.request_id = jsonIdToRequestId(request.get());
    gateway_request.source = "mcp";
    gateway_request.operation = name;
    if (params) {
        collectJsonStrings(params, "params", &gateway_request.items);
    }
    if (!gateway_request.items.empty()) {
        const auto gateway_response = evaluateGatewayRequest(gateway_request, options.policy);
        const std::string gateway_json = gatewayResponseToJson(gateway_response, true);
        detailed.has_request_log = true;
        detailed.request_log =
            makeRequestLogEntry(gateway_request,
                                gateway_response,
                                name,
                                name,
                                gateway_json);
        detailed.reveal_records =
            makeRevealRecords(gateway_request, gateway_response, detailed.request_log);
        detailed.blocked = gateway_response.blocked_count > 0;
        if (!detailed.blocked) {
            detailed.protected_forward_body = protectedForwardBody(request.get(), gateway_response);
        }
        detailed.response_json = gateway_json;
        return detailed;
    }

    detailed.response_json = errorResponse(request.get(), -32601, "method not found");
    return detailed;
}

std::string handleMcpJsonRpc(const std::string& request_body,
                             const McpHttpOptions& options) {
    return handleMcpJsonRpcDetailed(request_body, options).response_json;
}

}  // namespace aura::safety_gateway
