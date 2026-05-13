#include "gateway_request.h"

extern "C" {
#include "cJSON.h"
}

#include <memory>
#include <utility>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};

using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

const char* stringValue(cJSON* object, const char* name) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(value) ? value->valuestring : nullptr;
}

bool requireString(cJSON* object,
                   const char* name,
                   std::string* out,
                   std::string* error) {
    const char* value = stringValue(object, name);
    if (!value || value[0] == '\0') {
        if (error) *error = std::string("missing or empty field: ") + name;
        return false;
    }
    *out = value;
    return true;
}

void addString(cJSON* object, const char* name, const std::string& value) {
    cJSON_AddStringToObject(object, name, value.c_str());
}

}  // namespace

bool parseGatewayRequest(const std::string& json, GatewayRequest* out, std::string* error) {
    if (!out) {
        if (error) *error = "output pointer is null";
        return false;
    }

    JsonPtr root(cJSON_Parse(json.c_str()));
    if (!root || !cJSON_IsObject(root.get())) {
        if (error) *error = "request must be a JSON object";
        return false;
    }

    GatewayRequest parsed;
    if (!requireString(root.get(), "request_id", &parsed.request_id, error) ||
        !requireString(root.get(), "source", &parsed.source, error) ||
        !requireString(root.get(), "operation", &parsed.operation, error)) {
        return false;
    }

    cJSON* payload = cJSON_GetObjectItemCaseSensitive(root.get(), "payload");
    cJSON* items = payload ? cJSON_GetObjectItemCaseSensitive(payload, "items") : nullptr;
    if (!cJSON_IsArray(items)) {
        if (error) *error = "payload.items must be an array";
        return false;
    }

    cJSON* item = nullptr;
    cJSON_ArrayForEach(item, items) {
        if (!cJSON_IsObject(item)) {
            if (error) *error = "payload item must be an object";
            return false;
        }

        GatewayPayloadItem row;
        if (!requireString(item, "kind", &row.kind, error) ||
            !requireString(item, "location", &row.location, error) ||
            !requireString(item, "text", &row.text, error)) {
            return false;
        }
        cJSON* category_item = cJSON_GetObjectItemCaseSensitive(item, "category");
        if (category_item && !cJSON_IsString(category_item)) {
            if (error) *error = "payload item category must be a string";
            return false;
        }
        row.category = category_item && category_item->valuestring ? category_item->valuestring : "unknown";
        parsed.items.push_back(std::move(row));
    }

    *out = std::move(parsed);
    return true;
}

std::string gatewayResponseToJson(const GatewayResponse& response, bool compact) {
    JsonPtr root(cJSON_CreateObject());
    addString(root.get(), "request_id", response.request_id);
    addString(root.get(), "decision", response.decision);
    addString(root.get(), "schema_version", "aura-safety-gateway/1.0");
    addString(root.get(), "cache_path", response.cache_path);
    addString(root.get(), "route", response.route);

    cJSON* summary = cJSON_AddObjectToObject(root.get(), "summary");
    cJSON_AddNumberToObject(summary, "items_total", response.items_total);
    cJSON_AddNumberToObject(summary, "masked_count", response.masked_count);
    cJSON_AddNumberToObject(summary, "blocked_count", response.blocked_count);
    cJSON_AddBoolToObject(summary, "raw_original_included", response.raw_original_included);

    cJSON* items = cJSON_AddArrayToObject(root.get(), "items");
    for (const auto& row : response.items) {
        cJSON* item = cJSON_CreateObject();
        addString(item, "kind", row.kind);
        addString(item, "location", row.location);
        addString(item, "category", row.category);
        addString(item, "protected_text", row.protected_text);
        addString(item, "action", row.action);
        cJSON_AddBoolToObject(item, "original_included", row.original_included);
        cJSON_AddItemToArray(items, item);
    }

    cJSON* audit = cJSON_AddArrayToObject(root.get(), "audit");
    for (const auto& row : response.audit) {
        cJSON* item = cJSON_CreateObject();
        addString(item, "action", row.action);
        addString(item, "kind", row.kind);
        addString(item, "location", row.location);
        addString(item, "category", row.category);
        addString(item, "safe_preview", row.safe_preview);
        addString(item, "reason", row.reason);
        cJSON_AddItemToArray(audit, item);
    }

    char* raw = compact ? cJSON_PrintUnformatted(root.get()) : cJSON_Print(root.get());
    std::string result = raw ? raw : "{}";
    cJSON_free(raw);
    return result;
}

}  // namespace aura::safety_gateway
