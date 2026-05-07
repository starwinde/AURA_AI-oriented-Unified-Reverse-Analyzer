// src/engine/consent/consent_gate.h — Phase 2.5 §1.5
//
// Engine-bootstrap consent decision API. Pure decision layer over an
// injectable storage backend so the same logic can be exercised against
// an in-memory map (tests) or the persistent SQLite store
// (~/.aura/global_consent.db) in production.
//
// Decision contract (plan §1.5):
//   - GRANTED:   consent recorded, bootstrap may proceed.
//   - DENIED:    consent recorded, bootstrap MUST NOT proceed.
//   - ASK_USER:  no record yet; the GUI/CLI must surface the prompt.
//   - BLOCKED_FAILED:
//                consent existed but a previous bootstrap failed and the
//                cooldown window has not elapsed; do not retry yet.

#ifndef AURA_ENGINE_CONSENT_GATE_H
#define AURA_ENGINE_CONSENT_GATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AURA_CONSENT_ASK_USER       = 0,
    AURA_CONSENT_GRANTED        = 1,
    AURA_CONSENT_DENIED         = 2,
    AURA_CONSENT_BLOCKED_FAILED = 3
} AuraConsentDecision;

/* Persisted record. Mirrors the engine_consent table columns from
 * plan §1.5 but without SQLite specifics so callers can swap the
 * backing store. Caller-owned strings (no allocation here). */
typedef struct {
    char    decision[16];        /* "granted"/"denied"/"ask_each_time" */
    char    bootstrap_state[24]; /* "completed"/"failed_*"/""           */
    int64_t decided_at_ms;
    int64_t last_attempt_at_ms;
    int64_t retry_after_ms;      /* 0 when no cooldown active           */
    int     failure_count;
} AuraConsentRecord;

struct AuraConsentStore;

/* Backend hook: copy the record for `engine_id` into `out`. Returns 1
 * when a row exists and was copied, 0 when absent. Negative on error. */
typedef int (*AuraConsentLoadFn)(
    struct AuraConsentStore *self,
    const char              *engine_id,
    AuraConsentRecord       *out);

typedef struct AuraConsentStore {
    AuraConsentLoadFn load;
    void             *state;
} AuraConsentStore;

/* Pure decision: consult the store for the engine, apply cooldown rule,
 * return one of the four decisions above. `now_ms` is injected so tests
 * can drive cooldown windows deterministically. */
AuraConsentDecision aura_consent_check(
    AuraConsentStore *store,
    const char       *engine_id,
    int64_t           now_ms);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_CONSENT_GATE_H */
