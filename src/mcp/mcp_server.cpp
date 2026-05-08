#include "mcp_tools.h"

extern "C" {
#include "cJSON.h"
}

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

constexpr const char* kProtocolVersion = "2025-06-18";
constexpr const char* kServerVersion = "0.1.0";

std::string printJson(cJSON* obj) {
    char* raw = cJSON_PrintUnformatted(obj);
    std::string out = raw != nullptr ? raw : "";
    std::free(raw);
    return out;
}

bool addOwnedItem(cJSON* object, const char* name, cJSON*& item) {
    if (object == nullptr || item == nullptr) {
        return false;
    }
    if (!cJSON_AddItemToObject(object, name, item)) {
        return false;
    }
    item = nullptr;
    return true;
}

bool addOwnedArrayItem(cJSON* array, cJSON*& item) {
    if (array == nullptr || item == nullptr) {
        return false;
    }
    if (!cJSON_AddItemToArray(array, item)) {
        return false;
    }
    item = nullptr;
    return true;
}

cJSON* duplicateIdOrNull(const cJSON* id) {
    if (id == nullptr) {
        return cJSON_CreateNull();
    }
    return cJSON_Duplicate(id, 1);
}

cJSON* jsonRpcResult(const cJSON* id, cJSON* result) {
    cJSON* root = cJSON_CreateObject();
    cJSON* id_copy = duplicateIdOrNull(id);
    if (root == nullptr || id_copy == nullptr || result == nullptr) {
        cJSON_Delete(root);
        cJSON_Delete(id_copy);
        cJSON_Delete(result);
        return nullptr;
    }

    if (cJSON_AddStringToObject(root, "jsonrpc", "2.0") == nullptr ||
        !addOwnedItem(root, "id", id_copy) ||
        !addOwnedItem(root, "result", result)) {
        cJSON_Delete(root);
        cJSON_Delete(id_copy);
        cJSON_Delete(result);
        return nullptr;
    }
    return root;
}

cJSON* jsonRpcError(const cJSON* id, int code, const char* message) {
    cJSON* root = cJSON_CreateObject();
    cJSON* id_copy = duplicateIdOrNull(id);
    cJSON* error = cJSON_CreateObject();
    if (root == nullptr || id_copy == nullptr || error == nullptr) {
        cJSON_Delete(root);
        cJSON_Delete(id_copy);
        cJSON_Delete(error);
        return nullptr;
    }

    if (cJSON_AddStringToObject(root, "jsonrpc", "2.0") == nullptr ||
        !addOwnedItem(root, "id", id_copy) ||
        cJSON_AddNumberToObject(error, "code", code) == nullptr ||
        cJSON_AddStringToObject(error, "message", message) == nullptr ||
        !addOwnedItem(root, "error", error)) {
        cJSON_Delete(root);
        cJSON_Delete(id_copy);
        cJSON_Delete(error);
        return nullptr;
    }
    return root;
}

bool envelopeHasErrorStatus(const cJSON* envelope) {
    const cJSON* status =
        cJSON_GetObjectItemCaseSensitive(envelope, "status");
    return cJSON_IsString(status) && status->valuestring != nullptr &&
           std::string(status->valuestring) == "error";
}

cJSON* textToolResult(cJSON* envelope) {
    if (envelope == nullptr) {
        return nullptr;
    }

    cJSON* result = cJSON_CreateObject();
    cJSON* content = cJSON_CreateArray();
    cJSON* item = cJSON_CreateObject();
    const bool is_error = envelopeHasErrorStatus(envelope);
    const std::string text = printJson(envelope);
    cJSON_Delete(envelope);

    if (result == nullptr || content == nullptr || item == nullptr ||
        text.empty()) {
        cJSON_Delete(result);
        cJSON_Delete(content);
        cJSON_Delete(item);
        return nullptr;
    }

    if (cJSON_AddStringToObject(item, "type", "text") == nullptr ||
        cJSON_AddStringToObject(item, "text", text.c_str()) == nullptr ||
        !addOwnedArrayItem(content, item) ||
        !addOwnedItem(result, "content", content) ||
        cJSON_AddBoolToObject(result, "isError", is_error) == nullptr) {
        cJSON_Delete(result);
        cJSON_Delete(content);
        cJSON_Delete(item);
        return nullptr;
    }
    return result;
}

cJSON* handleInitialize() {
    cJSON* result = cJSON_CreateObject();
    cJSON* capabilities = cJSON_CreateObject();
    cJSON* tools = cJSON_CreateObject();
    cJSON* server_info = cJSON_CreateObject();
    if (result == nullptr || capabilities == nullptr || tools == nullptr ||
        server_info == nullptr) {
        cJSON_Delete(result);
        cJSON_Delete(capabilities);
        cJSON_Delete(tools);
        cJSON_Delete(server_info);
        return nullptr;
    }

    if (cJSON_AddStringToObject(result,
                                "protocolVersion",
                                kProtocolVersion) == nullptr ||
        !addOwnedItem(capabilities, "tools", tools) ||
        !addOwnedItem(result, "capabilities", capabilities) ||
        cJSON_AddStringToObject(server_info, "name", "aura-mcp") == nullptr ||
        cJSON_AddStringToObject(server_info, "version", kServerVersion) ==
            nullptr ||
        !addOwnedItem(result, "serverInfo", server_info)) {
        cJSON_Delete(result);
        cJSON_Delete(capabilities);
        cJSON_Delete(tools);
        cJSON_Delete(server_info);
        return nullptr;
    }
    return result;
}

cJSON* handleToolsList() {
    cJSON* result = cJSON_CreateObject();
    cJSON* tools = aura_mcp_tools_list_json();
    if (result == nullptr || tools == nullptr) {
        cJSON_Delete(result);
        cJSON_Delete(tools);
        return nullptr;
    }

    if (!addOwnedItem(result, "tools", tools)) {
        cJSON_Delete(result);
        cJSON_Delete(tools);
        return nullptr;
    }
    return result;
}

cJSON* handleToolsCall(const cJSON* id, const cJSON* request) {
    const cJSON* params =
        cJSON_GetObjectItemCaseSensitive(request, "params");
    const cJSON* name = cJSON_IsObject(params)
                            ? cJSON_GetObjectItemCaseSensitive(params, "name")
                            : nullptr;
    if (!cJSON_IsString(name) || name->valuestring == nullptr ||
        name->valuestring[0] == '\0') {
        return jsonRpcError(id, -32602, "tools/call requires params.name");
    }

    cJSON* args =
        cJSON_GetObjectItemCaseSensitive(params, "arguments");
    cJSON* envelope = aura_mcp_call_tool_json(name->valuestring, args);
    cJSON* result = textToolResult(envelope);
    if (result == nullptr) {
        return jsonRpcError(id, -32603, "Internal error");
    }
    return jsonRpcResult(id, result);
}

cJSON* dispatchRequest(cJSON* request) {
    if (!cJSON_IsObject(request)) {
        return jsonRpcError(nullptr, -32600, "Invalid Request");
    }

    cJSON* id = cJSON_GetObjectItemCaseSensitive(request, "id");
    cJSON* method = cJSON_GetObjectItemCaseSensitive(request, "method");
    if (!cJSON_IsString(method) || method->valuestring == nullptr ||
        method->valuestring[0] == '\0') {
        return jsonRpcError(id, -32600, "Invalid Request");
    }

    const std::string method_name = method->valuestring;
    if (method_name == "notifications/initialized") {
        return nullptr;
    }
    if (method_name == "initialize") {
        return jsonRpcResult(id, handleInitialize());
    }
    if (method_name == "tools/list") {
        return jsonRpcResult(id, handleToolsList());
    }
    if (method_name == "tools/call") {
        return handleToolsCall(id, request);
    }
    if (method_name == "ping") {
        return jsonRpcResult(id, cJSON_CreateObject());
    }
    return jsonRpcError(id, -32601, "Method not found");
}

void writeResponse(cJSON* response) {
    if (response == nullptr) {
        cJSON* fallback = jsonRpcError(nullptr, -32603, "Internal error");
        if (fallback == nullptr) {
            return;
        }
        std::cout << printJson(fallback) << '\n';
        cJSON_Delete(fallback);
        return;
    }

    std::cout << printJson(response) << '\n';
    cJSON_Delete(response);
}

}  // namespace

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        cJSON* request = cJSON_ParseWithLength(line.data(), line.size());
        if (request == nullptr) {
            writeResponse(jsonRpcError(nullptr, -32700, "Parse error"));
            continue;
        }

        cJSON* response = dispatchRequest(request);
        if (response != nullptr) {
            writeResponse(response);
        }
        cJSON_Delete(request);
    }
    return 0;
}
