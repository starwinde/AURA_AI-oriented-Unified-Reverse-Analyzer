#include "request_log.h"

extern "C" {
#include "cJSON.h"
}

#include <algorithm>
#include <set>
#include <memory>
#include <utility>

namespace aura::safety_gateway {
namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};

using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

void addString(cJSON* object, const char* name, const std::string& value) {
    cJSON_AddStringToObject(object, name, value.c_str());
}

cJSON* itemDecisionToJson(const GatewayItemDecision& decision) {
    cJSON* item = cJSON_CreateObject();
    addString(item, "item_id", decision.item_id);
    addString(item, "category", decision.category);
    addString(item, "action", decision.action);
    addString(item, "original_preview", decision.original_preview);
    addString(item, "protected_value", decision.protected_value);
    addString(item, "reason", decision.reason);
    cJSON_AddNumberToObject(item, "confidence", decision.confidence);
    return item;
}

cJSON* auditEventToJson(const GatewayAuditEvent& event) {
    cJSON* item = cJSON_CreateObject();
    if (!event.event_id.empty()) {
        addString(item, "event_id", event.event_id);
    }
    addString(item, "timestamp_iso8601", event.timestamp_iso8601);
    addString(item, "event_type", event.event_type);
    addString(item, "detail", event.detail);
    return item;
}

cJSON* requestLogEntryToJsonObject(const RequestLogEntry& entry) {
    cJSON* root = cJSON_CreateObject();
    addString(root, "request_id", entry.request_id);
    addString(root, "timestamp_iso8601", entry.timestamp_iso8601);
    addString(root, "client_name", entry.client_name);
    addString(root, "client_ip", entry.client_ip);
    addString(root, "method", entry.method);
    addString(root, "tool_name", entry.tool_name);
    addString(root, "decision", entry.decision);
    addString(root, "route", entry.route);
    addString(root, "remote_auth_result", entry.remote_auth_result);
    addString(root, "upstream_status", entry.upstream_status);
    addString(root, "protected_payload_json", entry.protected_payload_json);

    std::set<std::string> categories_seen;
    cJSON* categories = cJSON_AddArrayToObject(root, "categories");
    for (const auto& decision : entry.items) {
        if (!decision.category.empty() && categories_seen.insert(decision.category).second) {
            cJSON_AddItemToArray(categories, cJSON_CreateString(decision.category.c_str()));
        }
    }

    cJSON* items = cJSON_AddArrayToObject(root, "items");
    for (const auto& decision : entry.items) {
        cJSON_AddItemToArray(items, itemDecisionToJson(decision));
    }

    cJSON* audit_events = cJSON_AddArrayToObject(root, "audit_events");
    for (const auto& event : entry.audit_events) {
        cJSON_AddItemToArray(audit_events, auditEventToJson(event));
    }

    return root;
}

std::string printCompact(cJSON* root) {
    char* raw = cJSON_PrintUnformatted(root);
    std::string result = raw ? raw : "{}";
    cJSON_free(raw);
    return result;
}

}  // namespace

RequestLog::RequestLog(std::size_t max_entries)
    : max_entries_(max_entries == 0 ? kDefaultMaxEntries : max_entries) {}

std::vector<std::string> RequestLog::append(RequestLogEntry entry) {
    entries_.push_back(std::move(entry));

    std::vector<std::string> evicted_request_ids;
    while (entries_.size() > max_entries_) {
        if (!entries_.front().request_id.empty()) {
            evicted_request_ids.push_back(entries_.front().request_id);
        }
        entries_.erase(entries_.begin());
    }
    return evicted_request_ids;
}

std::vector<RequestLogEntry> RequestLog::latest(std::size_t limit) const {
    if (limit == 0 || limit >= entries_.size()) {
        return entries_;
    }

    return std::vector<RequestLogEntry>(entries_.end() - static_cast<std::ptrdiff_t>(limit),
                                        entries_.end());
}

bool RequestLog::findByRequestId(const std::string& request_id, RequestLogEntry* out) const {
    auto it = std::find_if(entries_.begin(), entries_.end(), [&](const RequestLogEntry& entry) {
        return entry.request_id == request_id;
    });
    if (it == entries_.end()) {
        return false;
    }
    if (out) {
        *out = *it;
    }
    return true;
}

bool RequestLog::addAuditEvent(const std::string& request_id, GatewayAuditEvent event) {
    auto it = std::find_if(entries_.begin(), entries_.end(), [&](const RequestLogEntry& entry) {
        return entry.request_id == request_id;
    });
    if (it == entries_.end()) {
        return false;
    }
    it->audit_events.push_back(std::move(event));
    return true;
}

void RequestLog::clear() {
    entries_.clear();
}

std::size_t RequestLog::size() const {
    return entries_.size();
}

std::size_t RequestLog::maxEntries() const {
    return max_entries_;
}

std::string requestLogEntryToJson(const RequestLogEntry& entry) {
    JsonPtr root(requestLogEntryToJsonObject(entry));
    return printCompact(root.get());
}

std::string requestLogEntriesToJson(const std::vector<RequestLogEntry>& entries) {
    JsonPtr root(cJSON_CreateArray());
    for (const auto& entry : entries) {
        cJSON_AddItemToArray(root.get(), requestLogEntryToJsonObject(entry));
    }
    return printCompact(root.get());
}

}  // namespace aura::safety_gateway
