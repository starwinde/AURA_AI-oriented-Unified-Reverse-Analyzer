#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

#include <cstring>

namespace {

constexpr const char* kMcpSchemaVersion = "1.0";

bool nonempty(const char* value) {
    return value != nullptr && value[0] != '\0';
}

bool stringFieldEquals(const cJSON* object, const char* name, const char* expected) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(item) && item->valuestring != nullptr &&
           std::strcmp(item->valuestring, expected) == 0;
}

bool hasStringField(const cJSON* object, const char* name) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(item) && nonempty(item->valuestring);
}

bool addString(cJSON* object, const char* name, const char* value) {
    return cJSON_AddStringToObject(object, name, value) != nullptr;
}

bool addOwnedItem(cJSON* object, const char* name, cJSON* item) {
    return item != nullptr && cJSON_AddItemToObject(object, name, item);
}

bool addOwnedArrayItem(cJSON* array, cJSON* item) {
    return item != nullptr && cJSON_AddItemToArray(array, item);
}

cJSON* base(const char* tool_schema_version,
            const char* kind,
            const char* status,
            const char* disclosure) {
    if (!nonempty(tool_schema_version) || !nonempty(kind) || !nonempty(status) ||
        !nonempty(disclosure)) {
        return nullptr;
    }

    cJSON* root = cJSON_CreateObject();
    if (root == nullptr) {
        return nullptr;
    }

    cJSON* warnings = cJSON_CreateArray();
    if (!addString(root, "mcp_schema_version", kMcpSchemaVersion) ||
        !addString(root, "tool_schema_version", tool_schema_version) ||
        !addString(root, "kind", kind) ||
        !addString(root, "status", status) ||
        !addString(root, "disclosure", disclosure) ||
        !cJSON_AddNullToObject(root, "audit") ||
        !addOwnedItem(root, "warnings", warnings)) {
        cJSON_Delete(warnings);
        cJSON_Delete(root);
        return nullptr;
    }

    return root;
}

}  // namespace

extern "C" cJSON* aura_mcp_envelope_success(const char* tool_schema_version,
                                            const char* kind,
                                            cJSON*      data_or_null,
                                            const char* disclosure) {
    if (data_or_null != nullptr && !cJSON_IsObject(data_or_null)) {
        return nullptr;
    }

    cJSON* root = base(tool_schema_version, kind, "ok", disclosure);
    if (root == nullptr) {
        return nullptr;
    }

    if (!cJSON_AddNullToObject(root, "error")) {
        cJSON_Delete(root);
        return nullptr;
    }

    cJSON* data = data_or_null != nullptr ? data_or_null : cJSON_CreateObject();
    if (data == nullptr) {
        cJSON_Delete(root);
        return nullptr;
    }

    if (!addOwnedItem(root, "data", data)) {
        if (data_or_null == nullptr) {
            cJSON_Delete(data);
        }
        cJSON_Delete(root);
        return nullptr;
    }

    return root;
}

extern "C" cJSON* aura_mcp_envelope_error(const char* tool_schema_version,
                                          const char* kind,
                                          const char* code,
                                          const char* message,
                                          const char* disclosure) {
    if (!nonempty(code) || !nonempty(message)) {
        return nullptr;
    }

    cJSON* root = base(tool_schema_version, kind, "error", disclosure);
    if (root == nullptr) {
        return nullptr;
    }

    cJSON* error = cJSON_CreateObject();
    if (error == nullptr) {
        cJSON_Delete(root);
        return nullptr;
    }

    if (!cJSON_AddNullToObject(root, "data")) {
        cJSON_Delete(error);
        cJSON_Delete(root);
        return nullptr;
    }

    if (!addString(error, "code", code) ||
        !addString(error, "message", message) ||
        !addOwnedItem(root, "error", error)) {
        cJSON_Delete(error);
        cJSON_Delete(root);
        return nullptr;
    }

    return root;
}

extern "C" cJSON* aura_mcp_envelope_add_warning(cJSON* envelope,
                                                const char* warning) {
    if (!cJSON_IsObject(envelope) || !nonempty(warning)) {
        return nullptr;
    }

    cJSON* warnings = cJSON_GetObjectItemCaseSensitive(envelope, "warnings");
    if (!cJSON_IsArray(warnings)) {
        return nullptr;
    }

    cJSON* warning_item = cJSON_CreateString(warning);
    if (!addOwnedArrayItem(warnings, warning_item)) {
        cJSON_Delete(warning_item);
        return nullptr;
    }
    return envelope;
}

extern "C" int aura_mcp_envelope_is_valid(const cJSON* envelope) {
    if (!cJSON_IsObject(envelope)) {
        return 0;
    }

    if (!stringFieldEquals(envelope, "mcp_schema_version", kMcpSchemaVersion) ||
        !hasStringField(envelope, "tool_schema_version") ||
        !hasStringField(envelope, "kind") ||
        !hasStringField(envelope, "disclosure")) {
        return 0;
    }

    const cJSON* warnings =
        cJSON_GetObjectItemCaseSensitive(envelope, "warnings");
    const cJSON* audit = cJSON_GetObjectItemCaseSensitive(envelope, "audit");
    if (!cJSON_IsArray(warnings) || !cJSON_IsNull(audit)) {
        return 0;
    }

    const cJSON* warning = nullptr;
    cJSON_ArrayForEach(warning, warnings) {
        if (!cJSON_IsString(warning) || !nonempty(warning->valuestring)) {
            return 0;
        }
    }

    const cJSON* status = cJSON_GetObjectItemCaseSensitive(envelope, "status");
    if (!cJSON_IsString(status) || status->valuestring == nullptr) {
        return 0;
    }

    const bool is_ok = std::strcmp(status->valuestring, "ok") == 0;
    const bool is_error = std::strcmp(status->valuestring, "error") == 0;
    if (!is_ok && !is_error) {
        return 0;
    }

    const cJSON* data = cJSON_GetObjectItemCaseSensitive(envelope, "data");
    const cJSON* error = cJSON_GetObjectItemCaseSensitive(envelope, "error");
    if (is_ok) {
        return cJSON_IsObject(data) && cJSON_IsNull(error) ? 1 : 0;
    }

    if (!cJSON_IsNull(data) || !cJSON_IsObject(error)) {
        return 0;
    }
    return hasStringField(error, "code") && hasStringField(error, "message") ? 1 : 0;
}
