// tests/unit/consent/consent_unit.cpp — Phase 2.5 §1.5
//
// Drives the consent decision API through an injectable in-memory
// store. Plan §1.5 contract: first encounter of an engine returns
// ASK_USER, subsequent slices add granted/denied/cooldown branches.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstring>
#include <map>
#include <string>

extern "C" {
#include "consent_gate.h"
#include "consent_store_sqlite.h"
#include "consent_lock.h"
}

#include <cstdio>
#include <filesystem>

namespace {

struct FakeStoreState {
    // engine_id -> record (absent => "not yet decided")
    std::map<std::string, AuraConsentRecord> rows;
};

static int fake_load(AuraConsentStore   *self,
                     const char         *engine_id,
                     AuraConsentRecord  *out) {
    auto *st = static_cast<FakeStoreState *>(self->state);
    auto it = st->rows.find(engine_id);
    if (it == st->rows.end()) return 0;
    *out = it->second;
    return 1;
}

struct FakeStore {
    FakeStoreState     state;
    AuraConsentStore   store;
    FakeStore() {
        store.load  = &fake_load;
        store.state = &state;
    }
    AuraConsentStore *as_store() { return &store; }
};

} // namespace

// ── Slice 35: first encounter returns ASK_USER ──────────────────────

TEST_CASE("consent_gate: first encounter of an engine returns ASK_USER") {
    FakeStore fake;
    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "ghidra-full", /*now_ms=*/1000);
    CHECK(d == AURA_CONSENT_ASK_USER);
}

TEST_CASE("consent_gate: NULL store yields ASK_USER (defensive default)") {
    AuraConsentDecision d =
        aura_consent_check(nullptr, "ghidra-full", /*now_ms=*/1000);
    CHECK(d == AURA_CONSENT_ASK_USER);
}

// ── Slice 36: a "granted" record returns GRANTED ────────────────────

TEST_CASE("consent_gate: granted record returns GRANTED") {
    FakeStore fake;
    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "granted", sizeof(rec.decision) - 1);
    std::strncpy(rec.bootstrap_state, "completed",
                 sizeof(rec.bootstrap_state) - 1);
    rec.decided_at_ms = 500;
    fake.state.rows["ghidra-full"] = rec;

    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "ghidra-full", /*now_ms=*/1000);
    CHECK(d == AURA_CONSENT_GRANTED);
}

// ── Slice 37: a "denied" record returns DENIED ──────────────────────

TEST_CASE("consent_gate: denied record returns DENIED") {
    FakeStore fake;
    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "denied", sizeof(rec.decision) - 1);
    rec.decided_at_ms = 500;
    fake.state.rows["angr"] = rec;

    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "angr", /*now_ms=*/1000);
    CHECK(d == AURA_CONSENT_DENIED);
}

// ── Slice 38: granted but failed_transient + active cooldown ────────
//
// Plan §1.7: TRANSIENT failure → 24h cooldown. While retry_after_ms
// is still in the future the decision must be BLOCKED_FAILED, not
// GRANTED — re-running bootstrap inside the cooldown is the bug we
// want to prevent.

TEST_CASE("consent_gate: granted + failed_transient inside cooldown returns BLOCKED_FAILED") {
    FakeStore fake;
    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "granted", sizeof(rec.decision) - 1);
    std::strncpy(rec.bootstrap_state, "failed_transient",
                 sizeof(rec.bootstrap_state) - 1);
    rec.decided_at_ms      = 100;
    rec.last_attempt_at_ms = 500;
    rec.retry_after_ms     = 5000;     // cooldown ends at t=5000
    rec.failure_count      = 1;
    fake.state.rows["ghidra-full"] = rec;

    // Inside the cooldown window.
    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "ghidra-full", /*now_ms=*/2000);
    CHECK(d == AURA_CONSENT_BLOCKED_FAILED);
}

// ── Slice 39: granted + failed_integrity always BLOCKED_FAILED ──────
//
// Plan §1.7: INTEGRITY (SHA256) failures abort with no cooldown — the
// bootstrap layer leaves retry_after_ms=0 so a naive cooldown check
// would let the engine through. The consent gate must still refuse:
// integrity failures are not retryable without operator intervention.

TEST_CASE("consent_gate: granted + failed_integrity returns BLOCKED_FAILED even with no cooldown") {
    FakeStore fake;
    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "granted", sizeof(rec.decision) - 1);
    std::strncpy(rec.bootstrap_state, "failed_integrity",
                 sizeof(rec.bootstrap_state) - 1);
    rec.retry_after_ms = 0;        // no cooldown for integrity
    fake.state.rows["ghidra-full"] = rec;

    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "ghidra-full", /*now_ms=*/9999);
    CHECK(d == AURA_CONSENT_BLOCKED_FAILED);
}

TEST_CASE("consent_gate: granted + failed_transient after cooldown returns GRANTED") {
    FakeStore fake;
    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "granted", sizeof(rec.decision) - 1);
    std::strncpy(rec.bootstrap_state, "failed_transient",
                 sizeof(rec.bootstrap_state) - 1);
    rec.retry_after_ms = 5000;
    fake.state.rows["ghidra-full"] = rec;

    // Past the cooldown window — retry permitted.
    AuraConsentDecision d =
        aura_consent_check(fake.as_store(), "ghidra-full", /*now_ms=*/6000);
    CHECK(d == AURA_CONSENT_GRANTED);
}

// ── Slice 53: SQLite consent store — empty DB → ASK_USER ────────────
//
// Tracer for the production store. ":memory:" keeps the test hermetic
// (no ~/.aura touch). Schema CREATE TABLE happens inside open(); load
// for an absent engine_id must report "row not found", which the gate
// converts into ASK_USER.

TEST_CASE("consent_store_sqlite: empty :memory: DB → ASK_USER through gate") {
    AuraConsentStoreSqlite *s = aura_consent_store_sqlite_open(":memory:");
    REQUIRE(s != nullptr);
    AuraConsentStore *vt = aura_consent_store_sqlite_as_store(s);
    REQUIRE(vt != nullptr);

    AuraConsentDecision d = aura_consent_check(vt, "ghidra-full", 1000);
    CHECK(d == AURA_CONSENT_ASK_USER);

    aura_consent_store_sqlite_close(s);
}

// ── Slice 54: upsert + reload → decision survives the round-trip ────

TEST_CASE("consent_store_sqlite: upsert(granted) → gate returns GRANTED") {
    AuraConsentStoreSqlite *s = aura_consent_store_sqlite_open(":memory:");
    REQUIRE(s != nullptr);

    AuraConsentRecord rec{};
    std::strncpy(rec.decision, "granted", sizeof(rec.decision) - 1);
    std::strncpy(rec.bootstrap_state, "completed",
                 sizeof(rec.bootstrap_state) - 1);
    rec.decided_at_ms = 500;
    REQUIRE(aura_consent_store_sqlite_upsert(s, "ghidra-full", &rec) == 0);

    AuraConsentStore *vt = aura_consent_store_sqlite_as_store(s);
    AuraConsentDecision d = aura_consent_check(vt, "ghidra-full", 1000);
    CHECK(d == AURA_CONSENT_GRANTED);

    aura_consent_store_sqlite_close(s);
}

// ── Slice 55: upsert overrides previous record (same engine_id) ─────

TEST_CASE("consent_store_sqlite: upsert(denied) overrides previous granted") {
    AuraConsentStoreSqlite *s = aura_consent_store_sqlite_open(":memory:");
    REQUIRE(s != nullptr);

    AuraConsentRecord granted{};
    std::strncpy(granted.decision, "granted", sizeof(granted.decision) - 1);
    REQUIRE(aura_consent_store_sqlite_upsert(s, "angr", &granted) == 0);

    AuraConsentRecord denied{};
    std::strncpy(denied.decision, "denied", sizeof(denied.decision) - 1);
    REQUIRE(aura_consent_store_sqlite_upsert(s, "angr", &denied) == 0);

    AuraConsentDecision d =
        aura_consent_check(aura_consent_store_sqlite_as_store(s), "angr", 1000);
    CHECK(d == AURA_CONSENT_DENIED);

    aura_consent_store_sqlite_close(s);
}

// ── Slice 59: lock file presence helper ─────────────────────────────
//
// Plan §1.5 automation: a CI / unattended user runs the bootstrap
// command once which writes ~/.aura/engine_consent.lock. The decision
// wrapper consults that file to skip ASK_USER. This slice exercises
// only the presence check; the wrapper integration arrives in the
// next slice once we have something to wrap.

TEST_CASE("consent_lock: missing file returns 0") {
    auto path = std::filesystem::temp_directory_path() /
                "aura_consent_lock_missing.lock";
    std::filesystem::remove(path);   // make sure it's absent
    int rc = aura_consent_lock_exists(path.string().c_str());
    CHECK(rc == 0);
}

TEST_CASE("consent_lock: present file returns 1") {
    auto path = std::filesystem::temp_directory_path() /
                "aura_consent_lock_present.lock";
    {
        std::FILE *f = std::fopen(path.string().c_str(), "wb");
        REQUIRE(f != nullptr);
        std::fputs("granted\n", f);
        std::fclose(f);
    }
    int rc = aura_consent_lock_exists(path.string().c_str());
    CHECK(rc == 1);
    std::filesystem::remove(path);   // cleanup
}

TEST_CASE("consent_lock: NULL path returns -1") {
    CHECK(aura_consent_lock_exists(nullptr) == -1);
    CHECK(aura_consent_lock_exists("")      == -1);
}

// ── Slice 60: lock-aware decision wrapper ──────────────────────────
//
// Lock present → GRANTED for any engine, even when the persisted
// store has no row (would otherwise be ASK_USER) or has a denied
// record (the lock represents an explicit operator override).

TEST_CASE("consent_check_with_lock: lock present → GRANTED even when store says ASK_USER") {
    auto path = std::filesystem::temp_directory_path() /
                "aura_consent_lock_grant.lock";
    {
        std::FILE *f = std::fopen(path.string().c_str(), "wb");
        REQUIRE(f != nullptr);
        std::fclose(f);
    }

    FakeStore fake;  // empty rows → would return ASK_USER without lock
    AuraConsentDecision d = aura_consent_check_with_lock(
        fake.as_store(), "ghidra-full", 1000, path.string().c_str());
    CHECK(d == AURA_CONSENT_GRANTED);

    std::filesystem::remove(path);
}

TEST_CASE("consent_check_with_lock: no lock → delegates to store (ASK_USER for empty store)") {
    auto path = std::filesystem::temp_directory_path() /
                "aura_consent_lock_absent.lock";
    std::filesystem::remove(path);   // ensure absent

    FakeStore fake;
    AuraConsentDecision d = aura_consent_check_with_lock(
        fake.as_store(), "ghidra-full", 1000, path.string().c_str());
    CHECK(d == AURA_CONSENT_ASK_USER);
}
