// tests/unit/bootstrap/bootstrap_unit.cpp — Phase 2.5 §1.6/§1.7
//
// Drives the bootstrap error classifier and (in later slices) the
// BootstrapManager dispatch.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "bootstrap_classify.h"
#include "bootstrap_manager.h"
#include "consent_gate.h"
}

namespace {

struct ScriptedFetch {
    std::vector<AuraBootstrapFailure> sequence;
    int                               calls = 0;
};

extern "C" AuraBootstrapFailure scripted_fetch(
    void *ctx, const char *engine_id, int attempt) {
    (void)engine_id; (void)attempt;
    auto *s = static_cast<ScriptedFetch *>(ctx);
    if (s->calls >= (int)s->sequence.size()) {
        return AURA_BOOTSTRAP_FAILED_RESOURCE;  // out-of-script -> hard stop
    }
    return s->sequence[s->calls++];
}

} // namespace

// ── Slice 40: classify maps "network" to TRANSIENT ─────────────────

TEST_CASE("bootstrap_classify: network errors are TRANSIENT") {
    AuraBootstrapErrorInput in{};
    in.kind     = "network";
    in.os_errno = 0;

    AuraBootstrapFailure f = aura_bootstrap_classify(&in);
    CHECK(f == AURA_BOOTSTRAP_FAILED_TRANSIENT);
    CHECK(std::string(aura_bootstrap_failure_str(f)) == "failed_transient");
}

TEST_CASE("bootstrap_classify: NULL input is OK (defensive)") {
    AuraBootstrapFailure f = aura_bootstrap_classify(nullptr);
    CHECK(f == AURA_BOOTSTRAP_OK);
    CHECK(std::string(aura_bootstrap_failure_str(f)) == "ok");
}

// ── Slice 44: TRANSIENT first attempt → RETRY_NOW ──────────────────
//
// Plan §1.7: a single auto-retry is permitted before the cooldown
// kicks in. attempts_used = 0 means we have not yet tried once → the
// failed call IS the first attempt and the policy says retry once
// immediately.

TEST_CASE("bootstrap_decide_action: TRANSIENT first failure → RETRY_NOW") {
    AuraBootstrapAction a =
        aura_bootstrap_decide_action(AURA_BOOTSTRAP_FAILED_TRANSIENT,
                                     /*attempts_used=*/1);
    CHECK(a == AURA_BOOTSTRAP_ACTION_RETRY_NOW);
}

// ── Slice 45: TRANSIENT after the auto-retry → COOLDOWN ────────────

TEST_CASE("bootstrap_decide_action: TRANSIENT 2nd failure → COOLDOWN") {
    AuraBootstrapAction a =
        aura_bootstrap_decide_action(AURA_BOOTSTRAP_FAILED_TRANSIENT,
                                     /*attempts_used=*/2);
    CHECK(a == AURA_BOOTSTRAP_ACTION_COOLDOWN);
}

// ── Slice 46: INTEGRITY/RESOURCE/DEPENDENCY → ABORT (no retry) ─────

TEST_CASE("bootstrap_decide_action: INTEGRITY → ABORT") {
    CHECK(aura_bootstrap_decide_action(AURA_BOOTSTRAP_FAILED_INTEGRITY, 1)
          == AURA_BOOTSTRAP_ACTION_ABORT);
}

TEST_CASE("bootstrap_decide_action: RESOURCE → ABORT") {
    CHECK(aura_bootstrap_decide_action(AURA_BOOTSTRAP_FAILED_RESOURCE, 1)
          == AURA_BOOTSTRAP_ACTION_ABORT);
}

TEST_CASE("bootstrap_decide_action: DEPENDENCY → ABORT") {
    CHECK(aura_bootstrap_decide_action(AURA_BOOTSTRAP_FAILED_DEPENDENCY, 1)
          == AURA_BOOTSTRAP_ACTION_ABORT);
}

TEST_CASE("bootstrap_decide_action: OK → NONE") {
    CHECK(aura_bootstrap_decide_action(AURA_BOOTSTRAP_OK, 0)
          == AURA_BOOTSTRAP_ACTION_NONE);
}

// ── Slice 50: TRANSIENT then OK → fetch invoked exactly twice ──────
//
// Plan §1.7 single auto-retry. The retry loop must:
//   - call fetch once, see TRANSIENT
//   - call fetch a second time per the RETRY_NOW verdict
//   - stop on OK and surface attempts_made = 2

TEST_CASE("bootstrap_run: TRANSIENT then OK calls fetch exactly twice and reports OK") {
    ScriptedFetch s{};
    s.sequence = { AURA_BOOTSTRAP_FAILED_TRANSIENT, AURA_BOOTSTRAP_OK };

    AuraBootstrapOutcome out{};
    int rc = aura_bootstrap_run("ghidra-full", &scripted_fetch, &s, &out);

    REQUIRE(rc == 0);
    CHECK(s.calls == 2);
    CHECK(out.attempts_made == 2);
    CHECK(out.final_failure == AURA_BOOTSTRAP_OK);
    CHECK(out.final_action  == AURA_BOOTSTRAP_ACTION_NONE);
}

// ── Slice 51: INTEGRITY first call → fetch invoked exactly once ────

TEST_CASE("bootstrap_run: INTEGRITY aborts immediately, fetch invoked once") {
    ScriptedFetch s{};
    s.sequence = { AURA_BOOTSTRAP_FAILED_INTEGRITY };

    AuraBootstrapOutcome out{};
    int rc = aura_bootstrap_run("ghidra-full", &scripted_fetch, &s, &out);

    REQUIRE(rc == 0);
    CHECK(s.calls == 1);
    CHECK(out.attempts_made == 1);
    CHECK(out.final_failure == AURA_BOOTSTRAP_FAILED_INTEGRITY);
    CHECK(out.final_action  == AURA_BOOTSTRAP_ACTION_ABORT);
}

// ── Slice 52: TRANSIENT twice → cooldown verdict, fetch twice ──────

TEST_CASE("bootstrap_run: TRANSIENT twice → COOLDOWN, fetch invoked exactly twice") {
    ScriptedFetch s{};
    s.sequence = { AURA_BOOTSTRAP_FAILED_TRANSIENT,
                   AURA_BOOTSTRAP_FAILED_TRANSIENT };

    AuraBootstrapOutcome out{};
    int rc = aura_bootstrap_run("angr", &scripted_fetch, &s, &out);

    REQUIRE(rc == 0);
    CHECK(s.calls == 2);
    CHECK(out.attempts_made == 2);
    CHECK(out.final_failure == AURA_BOOTSTRAP_FAILED_TRANSIENT);
    CHECK(out.final_action  == AURA_BOOTSTRAP_ACTION_COOLDOWN);
}

// ── Slice 41: sha256 mismatch is INTEGRITY (no cooldown) ───────────

TEST_CASE("bootstrap_classify: sha256 mismatch is INTEGRITY") {
    AuraBootstrapErrorInput in{"sha256", 0};
    AuraBootstrapFailure f = aura_bootstrap_classify(&in);
    CHECK(f == AURA_BOOTSTRAP_FAILED_INTEGRITY);
    CHECK(std::string(aura_bootstrap_failure_str(f)) == "failed_integrity");
}

// ── Slice 42: disk full / permission denied is RESOURCE ────────────

TEST_CASE("bootstrap_classify: disk error is RESOURCE") {
    AuraBootstrapErrorInput in{"disk", 28 /* ENOSPC */};
    AuraBootstrapFailure f = aura_bootstrap_classify(&in);
    CHECK(f == AURA_BOOTSTRAP_FAILED_RESOURCE);
    CHECK(std::string(aura_bootstrap_failure_str(f)) == "failed_resource");
}

// ── Slice 43: pip resolver conflict is DEPENDENCY ──────────────────

TEST_CASE("bootstrap_classify: pip resolver conflict is DEPENDENCY") {
    AuraBootstrapErrorInput in{"pip", 0};
    AuraBootstrapFailure f = aura_bootstrap_classify(&in);
    CHECK(f == AURA_BOOTSTRAP_FAILED_DEPENDENCY);
    CHECK(std::string(aura_bootstrap_failure_str(f)) == "failed_dependency");
}

// ── Slice 56: apply_outcome — OK case → "completed" + cleared cooldown ─

TEST_CASE("bootstrap_apply_outcome: OK clears bootstrap_state to 'completed'") {
    AuraBootstrapOutcome outcome{};
    outcome.final_failure = AURA_BOOTSTRAP_OK;
    outcome.final_action  = AURA_BOOTSTRAP_ACTION_NONE;
    outcome.attempts_made = 1;

    AuraConsentRecord rec{};
    // Pre-existing failure state from a prior run.
    std::strncpy(rec.bootstrap_state, "failed_transient",
                 sizeof(rec.bootstrap_state) - 1);
    rec.failure_count  = 3;
    rec.retry_after_ms = 9999;

    aura_bootstrap_apply_outcome(&outcome, /*now_ms=*/5000, &rec);

    CHECK(std::string(rec.bootstrap_state) == "completed");
    CHECK(rec.failure_count == 0);
    CHECK(rec.retry_after_ms == 0);
    CHECK(rec.last_attempt_at_ms == 5000);
}

// ── Slice 57: apply_outcome — TRANSIENT cooldown verdict ───────────
//
// Plan §1.7: TRANSIENT after the auto-retry → 24h cooldown. The
// outcome's COOLDOWN action drives the projection — we set
// bootstrap_state="failed_transient", retry_after_ms = now + 24h,
// and bump failure_count.

TEST_CASE("bootstrap_apply_outcome: COOLDOWN sets failed_transient + 24h cooldown") {
    AuraBootstrapOutcome outcome{};
    outcome.final_failure = AURA_BOOTSTRAP_FAILED_TRANSIENT;
    outcome.final_action  = AURA_BOOTSTRAP_ACTION_COOLDOWN;
    outcome.attempts_made = 2;

    AuraConsentRecord rec{};
    rec.failure_count = 1;

    constexpr int64_t now = 1'000'000;
    constexpr int64_t day_ms = 24LL * 60 * 60 * 1000;
    aura_bootstrap_apply_outcome(&outcome, now, &rec);

    CHECK(std::string(rec.bootstrap_state) == "failed_transient");
    CHECK(rec.retry_after_ms == now + day_ms);
    CHECK(rec.failure_count == 2);
    CHECK(rec.last_attempt_at_ms == now);
}

// ── Slice 58: apply_outcome — INTEGRITY ABORT, no cooldown stamp ────

TEST_CASE("bootstrap_apply_outcome: INTEGRITY ABORT records failed_integrity with no cooldown") {
    AuraBootstrapOutcome outcome{};
    outcome.final_failure = AURA_BOOTSTRAP_FAILED_INTEGRITY;
    outcome.final_action  = AURA_BOOTSTRAP_ACTION_ABORT;
    outcome.attempts_made = 1;

    AuraConsentRecord rec{};
    rec.failure_count  = 0;
    rec.retry_after_ms = 9999;   // stale value from a previous run

    aura_bootstrap_apply_outcome(&outcome, /*now_ms=*/3000, &rec);

    CHECK(std::string(rec.bootstrap_state) == "failed_integrity");
    CHECK(rec.retry_after_ms == 0);
    CHECK(rec.failure_count == 1);
}
