// src/engine/bootstrap/bootstrap_manager.c — Phase 2.5 §1.6/§1.7

#include "bootstrap_manager.h"

#include <stddef.h>
#include <string.h>

void aura_bootstrap_apply_outcome(
    const AuraBootstrapOutcome *outcome,
    int64_t                     now_ms,
    AuraConsentRecord          *inout)
{
    if (!outcome || !inout) return;
    inout->last_attempt_at_ms = now_ms;
    if (outcome->final_failure == AURA_BOOTSTRAP_OK) {
        memset(inout->bootstrap_state, 0, sizeof(inout->bootstrap_state));
        strncpy(inout->bootstrap_state, "completed",
                sizeof(inout->bootstrap_state) - 1);
        inout->failure_count  = 0;
        inout->retry_after_ms = 0;
        return;
    }

    /* Failure path. Bump the counter and stamp the failure class
     * onto bootstrap_state via the wire-stable id. */
    inout->failure_count++;
    memset(inout->bootstrap_state, 0, sizeof(inout->bootstrap_state));
    strncpy(inout->bootstrap_state,
            aura_bootstrap_failure_str(outcome->final_failure),
            sizeof(inout->bootstrap_state) - 1);

    /* Cooldown only applies to the COOLDOWN verdict (TRANSIENT after
     * the auto-retry). Other failure classes (INTEGRITY/RESOURCE/
     * DEPENDENCY) leave retry_after_ms at 0 — the consent gate's
     * non-transient branch already refuses to grant on those. */
    if (outcome->final_action == AURA_BOOTSTRAP_ACTION_COOLDOWN) {
        const int64_t day_ms = 24LL * 60 * 60 * 1000;
        inout->retry_after_ms = now_ms + day_ms;
    } else {
        inout->retry_after_ms = 0;
    }
}

int aura_bootstrap_run(
    const char           *engine_id,
    AuraBootstrapFetchFn  fetch,
    void                 *fetch_ctx,
    AuraBootstrapOutcome *out)
{
    if (!out) return 0;
    memset(out, 0, sizeof(*out));
    if (!engine_id || !fetch) {
        out->final_action  = AURA_BOOTSTRAP_ACTION_ABORT;
        out->final_failure = AURA_BOOTSTRAP_FAILED_RESOURCE;
        return 0;
    }

    int attempt = 0;
    AuraBootstrapFailure last = AURA_BOOTSTRAP_OK;
    AuraBootstrapAction  decision = AURA_BOOTSTRAP_ACTION_NONE;

    for (;;) {
        attempt++;
        last = fetch(fetch_ctx, engine_id, attempt);
        if (last == AURA_BOOTSTRAP_OK) {
            decision = AURA_BOOTSTRAP_ACTION_NONE;
            break;
        }
        decision = aura_bootstrap_decide_action(last, attempt);
        if (decision != AURA_BOOTSTRAP_ACTION_RETRY_NOW) break;
        /* loop and retry */
    }

    out->attempts_made = attempt;
    out->final_failure = last;
    out->final_action  = decision;
    return 0;
}
