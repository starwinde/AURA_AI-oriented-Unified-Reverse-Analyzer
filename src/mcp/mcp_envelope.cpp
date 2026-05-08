#include "aura/mcp/mcp_envelope.h"

#include <cstring>

namespace {

constexpr const char* kMcpSchemaVersion = "1.0";

bool nonempty(const char* value) {
    return value != nullptr && value[0] != '\0';
}

bool stringFieldEquals(const cJSON* object,
                       const char*  name,
                       const char*  expected) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(item) && item->valuestring != nullptr &&
           std::strcmp(item->valuestring, expected) == 0;
}

bool hasStringField(const cJSON* object, const char* name) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(item) && nonempty(item->valuestring);
}

cJSON* createBaseEnvelope(const char* kind,
                          const char* tool_schema_version,
                          const char* status,
                          const char* disclosure) {
    if (!nonempty(kind) || !nonempty(tool_schema_version)) {
        return nullptr;
    }

    cJSON* root = cJSON_CreateObject();
    if (root == nullptr) {
        return nullptr;
    }

    cJSON_AddStringToObject(root, "mcp_schema_version", kMcpSchemaVersion);
    cJSON_AddStringToObject(root, "tool_schema_version", tool_schema_version);
    cJSON_AddStringToObject(root, "kind", kind);
    cJSON_AddStringToObject(root, "status", status);
    cJSON_AddStringToObject(root, "disclosure", disclosure);
    cJSON_AddItemToObject(root, "warnings", cJSON_CreateArray());
    cJSON_AddNullToObject(root, "audit");

    const cJSON* warnings = cJSON_GetObjectItemCaseSensitive(root, "warnings");
    const cJSON* audit = cJSON_GetObjectItemCaseSensitive(root, "audit");
    if (!cJSON_IsArray(warnings) || !cJSON_IsNull(audit)) {
        cJSON_Delete(root);
        return nullptr;
    }

    return root;
}

}  // namespace

extern "C" cJSON* aura_mcp_envelope_success(const char* kind,
                                             const char* tool_schema_version,
                                             const char* disclosure,
                                             cJSON*      data_or_null) {
    if (!nonempty(disclosure)) {
        return nullptr;
    }

    cJSON* root =
        createBaseEnvelope(kind, tool_schema_version, "ok", disclosure);
    if (root == nullptr) {
        return nullptr;
    }

    cJSON* data = data_or_null != nullptr ? data_or_null : cJSON_CreateObject();
    if (data == nullptr) {
        cJSON_Delete(root);
        return nullptr;
    }

    cJSON_AddItemToObject(root, "data", data);
    cJSON_AddNullToObject(root, "error");

    if (!aura_mcp_envelope_is_valid(root)) {
        cJSON_Delete(root);
        return nullptr;
    }
    return root;
}

extern "C" cJSON* aura_mcp_envelope_error(const char* kind,
                                           const char* tool_schema_version,
                                           const char* code,
                                           const char* message) {
    if (!nonempty(code) || !nonempty(message)) {
        return nullptr;
    }

    cJSON* root = createBaseEnvelope(kind, tool_schema_version, "error", "none");
    if (root == nullptr) {
        return nullptr;
    }

    cJSON* error = cJSON_CreateObject();
    if (error == nullptr) {
        cJSON_Delete(root);
        return nullptr;
    }
    cJSON_AddStringToObject(error, "code", code);
    cJSON_AddStringToObject(error, "message", message);

    cJSON_AddNullToObject(root, "data");
    cJSON_AddItemToObject(root, "error", error);

    if (!aura_mcp_envelope_is_valid(root)) {
        cJSON_Delete(root);
        return nullptr;
    }
    return root;
}

extern "C" cJSON* aura_mcp_envelope_add_warning(cJSON*      envelope,
                                                 const char* warning) {
    if (!cJSON_IsObject(envelope) || !nonempty(warning)) {
        return nullptr;
    }

    cJSON* warnings = cJSON_GetObjectItemCaseSensitive(envelope, "warnings");
    if (!cJSON_IsArray(warnings)) {
        return nullptr;
    }

    cJSON* warning_item = cJSON_CreateString(warning);
    if (warning_item == nullptr) {
        return nullptr;
    }
    cJSON_AddItemToArray(warnings, warning_item);
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
    return hasStringField(error, "code") &&
                   hasStringField(error, "message")
               ? 1
               : 0;
}
