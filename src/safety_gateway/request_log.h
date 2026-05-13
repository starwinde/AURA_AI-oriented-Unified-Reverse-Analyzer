#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace aura::safety_gateway {

struct GatewayItemDecision {
    std::string item_id;
    std::string category;
    std::string action;
    std::string original_preview;
    std::string protected_value;
    std::string reason;
    double confidence = 0.0;
};

struct GatewayAuditEvent {
    std::string event_id;
    std::string timestamp_iso8601;
    std::string event_type;
    std::string detail;
};

struct RequestLogEntry {
    std::string request_id;
    std::string timestamp_iso8601;
    std::string client_name;
    std::string client_ip;
    std::string method;
    std::string tool_name;
    std::string decision;
    std::string route;
    std::string remote_auth_result;
    std::string upstream_status;
    std::string protected_payload_json;
    std::vector<GatewayItemDecision> items;
    std::vector<GatewayAuditEvent> audit_events;
};

class RequestLog {
public:
    static constexpr std::size_t kDefaultMaxEntries = 500;

    explicit RequestLog(std::size_t max_entries = kDefaultMaxEntries);

    std::vector<std::string> append(RequestLogEntry entry);
    std::vector<RequestLogEntry> latest(std::size_t limit = 0) const;
    bool findByRequestId(const std::string& request_id, RequestLogEntry* out) const;
    bool addAuditEvent(const std::string& request_id, GatewayAuditEvent event);
    void clear();
    std::size_t size() const;
    std::size_t maxEntries() const;

private:
    std::size_t max_entries_;
    std::vector<RequestLogEntry> entries_;
};

std::string requestLogEntryToJson(const RequestLogEntry& entry);
std::string requestLogEntriesToJson(const std::vector<RequestLogEntry>& entries);

}  // namespace aura::safety_gateway
