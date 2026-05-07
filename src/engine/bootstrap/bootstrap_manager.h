// src/engine/bootstrap/bootstrap_manager.h — Phase 2.5 §1.6/§1.7
//
// Synchronous bootstrap dispatch with the plan-§1.7 retry policy.
// The actual fetch (network download + verify + install) is provided
// as a callback, so tests inject a FakeFetcher and the production
// caller wires in the real curl/sha256/venv pipeline.
//
// This slice is single-threaded by design: per-engine mutex and the
// global concurrency semaphore land in subsequent slices once the
// retry loop contract is locked down.

#ifndef AURA_ENGINE_BOOTSTRAP_MANAGER_H
#define AURA_ENGINE_BOOTSTRAP_MANAGER_H

#include "bootstrap_classify.h"
#include "consent_gate.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The fetch callback returns the failure classification it produced
 * (AURA_BOOTSTRAP_OK on success). It MUST be idempotent and safe to
 * call multiple times — the manager invokes it exactly once per
 * attempt as dictated by `aura_bootstrap_decide_action`. */
typedef AuraBootstrapFailure (*AuraBootstrapFetchFn)(
    void       *ctx,
    const char *engine_id,
    int         attempt /* 1-based */);

typedef struct {
    AuraBootstrapFailure final_failure;  /* OK on success                  */
    int                  attempts_made;  /* 1, 2, ... — never 0            */
    AuraBootstrapAction  final_action;   /* policy verdict for the last err */
} AuraBootstrapOutcome;

/* Run the retry policy against `fetch`. Returns 0 always — diagnostic
 * lives in the outcome struct so callers do not need to demux libc-
 * style return codes. NULL fetch / engine_id is a programmer error
 * and yields ABORT with attempts_made = 0. */
int aura_bootstrap_run(
    const char           *engine_id,
    AuraBootstrapFetchFn  fetch,
    void                 *fetch_ctx,
    AuraBootstrapOutcome *out);

/* Project a bootstrap outcome onto the persistence schema used by
 * the consent store. The decision text ("granted"/"denied"/...) is
 * NOT touched here — that is the user's prerogative and is set by
 * the consent prompt path. We only update the bootstrap_state /
 * retry_after_ms / failure_count fields based on §1.7 policy.
 *
 * `now_ms` is injected so cooldown deadlines are deterministic in
 * tests. Cooldown window is 24h (24*60*60*1000) per plan §1.7.
 */
void aura_bootstrap_apply_outcome(
    const AuraBootstrapOutcome *outcome,
    int64_t                     now_ms,
    AuraConsentRecord          *inout_rec);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_BOOTSTRAP_MANAGER_H */
