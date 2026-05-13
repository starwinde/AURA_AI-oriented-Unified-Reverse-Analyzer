#include "session_reveal_store.h"

extern "C" {
#include "cJSON.h"
}

#include <algorithm>
#include <memory>
#include <sstream>
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

std::string makeAuditEventId(std::size_t sequence) {
    std::ostringstream out;
    out << "evt_reveal_" << sequence;
    return out.str();
}

}  // namespace

SessionRevealStore::SessionRevealStore(std::size_t max_items, std::chrono::seconds ttl)
    : max_items_(max_items == 0 ? kDefaultMaxItems : max_items),
      ttl_(ttl.count() <= 0 ? kDefaultTtl : ttl) {}

void SessionRevealStore::put(SessionRevealRecord record) {
    put(std::move(record), Clock::now());
}

void SessionRevealStore::put(SessionRevealRecord record, TimePoint now) {
    auto it = std::find_if(records_.begin(), records_.end(), [&](const StoredRevealRecord& row) {
        return row.record.request_id == record.request_id && row.record.item_id == record.item_id;
    });

    StoredRevealRecord stored;
    stored.record = std::move(record);
    stored.expires_at = now + ttl_;
    stored.sequence = next_sequence_++;

    if (it != records_.end()) {
        *it = std::move(stored);
    } else {
        records_.push_back(std::move(stored));
    }
    enforceLimit();
}

SessionRevealResult SessionRevealStore::reveal(const std::string& request_id,
                                               const std::string& item_id) {
    return reveal(request_id, item_id, Clock::now());
}

SessionRevealResult SessionRevealStore::reveal(const std::string& request_id,
                                               const std::string& item_id,
                                               TimePoint now) {
    expire(now);

    SessionRevealResult result;
    result.request_id = request_id;
    result.item_id = item_id;

    auto it = std::find_if(records_.begin(), records_.end(), [&](const StoredRevealRecord& row) {
        return row.record.request_id == request_id && row.record.item_id == item_id;
    });
    if (it == records_.end()) {
        return result;
    }

    result.found = true;
    result.category = it->record.category;
    result.original = it->record.original;
    result.expires_in_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(it->expires_at - now).count();
    if (result.expires_in_seconds < 0) {
        result.expires_in_seconds = 0;
    }
    result.audit_event_id = makeAuditEventId(it->sequence);
    result.denial_reason.clear();
    return result;
}

std::size_t SessionRevealStore::expire() {
    return expire(Clock::now());
}

std::size_t SessionRevealStore::expire(TimePoint now) {
    const auto before = records_.size();
    records_.erase(std::remove_if(records_.begin(),
                                  records_.end(),
                                  [&](const StoredRevealRecord& row) {
                                      return row.expires_at <= now;
                                  }),
                   records_.end());
    return before - records_.size();
}

std::size_t SessionRevealStore::eraseByRequestId(const std::string& request_id) {
    const auto before = records_.size();
    records_.erase(std::remove_if(records_.begin(),
                                  records_.end(),
                                  [&](const StoredRevealRecord& row) {
                                      return row.record.request_id == request_id;
                                  }),
                   records_.end());
    return before - records_.size();
}

void SessionRevealStore::clear() {
    records_.clear();
}

std::size_t SessionRevealStore::size() const {
    return records_.size();
}

std::size_t SessionRevealStore::maxItems() const {
    return max_items_;
}

std::chrono::seconds SessionRevealStore::ttl() const {
    return ttl_;
}

void SessionRevealStore::enforceLimit() {
    while (records_.size() > max_items_) {
        auto oldest = std::min_element(records_.begin(),
                                       records_.end(),
                                       [](const StoredRevealRecord& left,
                                          const StoredRevealRecord& right) {
                                           return left.sequence < right.sequence;
                                       });
        if (oldest == records_.end()) {
            return;
        }
        records_.erase(oldest);
    }
}

std::string sessionRevealResultToJson(const SessionRevealResult& result) {
    JsonPtr root(cJSON_CreateObject());
    addString(root.get(), "request_id", result.request_id);
    addString(root.get(), "item_id", result.item_id);
    if (result.found) {
        addString(root.get(), "category", result.category);
        addString(root.get(), "original", result.original);
        cJSON_AddNumberToObject(root.get(), "expires_in_seconds",
                                static_cast<double>(result.expires_in_seconds));
        addString(root.get(), "audit_event_id", result.audit_event_id);
    } else {
        addString(root.get(), "error", result.denial_reason);
    }

    char* raw = cJSON_PrintUnformatted(root.get());
    std::string out = raw ? raw : "{}";
    cJSON_free(raw);
    return out;
}

}  // namespace aura::safety_gateway
