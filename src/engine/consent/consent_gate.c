// src/engine/consent/consent_gate.c — Phase 2.5 §1.5 GREEN minimal.

#include "consent_gate.h"

#include <stddef.h>
#include <string.h>

/* True iff the bootstrap_state indicates a failure that participates
 * in the cooldown gate (plan §1.7). INTEGRITY/RESOURCE/DEPENDENCY
 * failures abort immediately without cooldown — but the consent layer
 * still treats any failed_* state with a non-zero retry_after_ms as
 * blocked until the deadline; the bootstrap layer is responsible for
 * never setting retry_after_ms on the no-cooldown classes. */
static int is_failed_state(const char *bootstrap_state)
{
    if (!bootstrap_state || !bootstrap_state[0]) return 0;
    return strncmp(bootstrap_state, "failed_", 7) == 0;
}

AuraConsentDecision aura_consent_check(
    AuraConsentStore *store,
    const char       *engine_id,
    int64_t           now_ms)
{
    if (!store || !store->load || !engine_id) {
        /* Defensive: a misconfigured caller should never silently
         * proceed; the safest default is to ask the user. */
        return AURA_CONSENT_ASK_USER;
    }

    AuraConsentRecord rec;
    memset(&rec, 0, sizeof(rec));
    int rc = store->load(store, engine_id, &rec);
    if (rc <= 0) {
        /* No record OR backend error → ask the user. Errors fall to
         * the same branch deliberately: silently granting on a load
         * failure would be a security regression. */
        return AURA_CONSENT_ASK_USER;
    }

    if (strcmp(rec.decision, "denied") == 0) {
        return AURA_CONSENT_DENIED;
    }
    if (strcmp(rec.decision, "granted") == 0) {
        if (is_failed_state(rec.bootstrap_state)) {
            /* Plan §1.7 no-retry classes: integrity / resource /
             * dependency_conflict abort without cooldown — operator
             * must act before any retry. Anything other than the
             * transient class is treated as permanently blocked
             * until the persisted state is cleared. */
            if (strcmp(rec.bootstrap_state, "failed_transient") != 0) {
                return AURA_CONSENT_BLOCKED_FAILED;
            }
            /* Transient: respect the cooldown window. */
            if (rec.retry_after_ms > 0 && now_ms < rec.retry_after_ms) {
                return AURA_CONSENT_BLOCKED_FAILED;
            }
        }
        return AURA_CONSENT_GRANTED;
    }

    /* Remaining branches (denied, ask_each_time, cooldown,
     * failed_bootstrap → BLOCKED_FAILED) get added by subsequent
     * RED tests. Anything else falls back to ASK_USER. */
    return AURA_CONSENT_ASK_USER;
}
