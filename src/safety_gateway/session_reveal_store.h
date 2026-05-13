#pragma once

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

namespace aura::safety_gateway {

struct SessionRevealRecord {
    std::string request_id;
    std::string item_id;
    std::string category;
    std::string original;
};

struct SessionRevealResult {
    bool found = false;
    std::string request_id;
    std::string item_id;
    std::string category;
    std::string original;
    long long expires_in_seconds = 0;
    std::string audit_event_id;
    std::string denial_reason = "reveal_denied";
};

class SessionRevealStore {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    static constexpr std::size_t kDefaultMaxItems = 500;
    static constexpr std::chrono::seconds kDefaultTtl{600};

    explicit SessionRevealStore(std::size_t max_items = kDefaultMaxItems,
                                std::chrono::seconds ttl = kDefaultTtl);

    void put(SessionRevealRecord record);
    SessionRevealResult reveal(const std::string& request_id, const std::string& item_id);
    SessionRevealResult reveal(const std::string& request_id,
                               const std::string& item_id,
                               TimePoint now);
    std::size_t expire();
    std::size_t expire(TimePoint now);
    std::size_t eraseByRequestId(const std::string& request_id);
    void clear();
    std::size_t size() const;
    std::size_t maxItems() const;
    std::chrono::seconds ttl() const;

private:
    struct StoredRevealRecord {
        SessionRevealRecord record;
        TimePoint expires_at;
        std::size_t sequence = 0;
    };

    void put(SessionRevealRecord record, TimePoint now);
    void enforceLimit();

    std::size_t max_items_;
    std::chrono::seconds ttl_;
    std::size_t next_sequence_ = 1;
    std::vector<StoredRevealRecord> records_;
};

std::string sessionRevealResultToJson(const SessionRevealResult& result);

}  // namespace aura::safety_gateway
