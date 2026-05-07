// src/engine/bootstrap/bootstrap_classify.h — Phase 2.5 §1.7
//
// Pure error classification for engine bootstrap. Plan §1.7 maps four
// failure classes to four policies (TRANSIENT auto-retry + 24h cooldown,
// INTEGRITY immediate abort no cooldown, RESOURCE immediate abort + UI,
// DEPENDENCY_CONFLICT immediate abort + AURA dev lock refresh).
//
// Splitting classification out as a pure function lets the
// BootstrapManager and the Consent gate share one canonical error
// taxonomy without dragging in the actual fetch / venv machinery.

#ifndef AURA_ENGINE_BOOTSTRAP_CLASSIFY_H
#define AURA_ENGINE_BOOTSTRAP_CLASSIFY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AURA_BOOTSTRAP_OK                  = 0,
    AURA_BOOTSTRAP_FAILED_TRANSIENT    = 1, /* network, partial download */
    AURA_BOOTSTRAP_FAILED_INTEGRITY    = 2, /* SHA256 mismatch           */
    AURA_BOOTSTRAP_FAILED_RESOURCE     = 3, /* disk full, permission     */
    AURA_BOOTSTRAP_FAILED_DEPENDENCY   = 4  /* pip resolver conflict     */
} AuraBootstrapFailure;

/* Inputs the caller provides, kept narrow so this module never
 * touches the network or filesystem itself. `kind` is a short symbol
 * the fetch / verify / install layers emit; `os_errno` carries the
 * libc errno (or 0 when not applicable). */
typedef struct {
    const char *kind;       /* "network", "sha256", "disk", "pip", ... */
    int         os_errno;   /* errno snapshot, 0 when n/a              */
} AuraBootstrapErrorInput;

/* Map an error input to a plan-§1.7 failure class. */
AuraBootstrapFailure aura_bootstrap_classify(
    const AuraBootstrapErrorInput *in);

/* Wire-stable string id for the failure (matches the bootstrap_state
 * column persisted in the consent DB). Non-OK values map to
 * "failed_transient" / "failed_integrity" / etc. */
const char *aura_bootstrap_failure_str(AuraBootstrapFailure f);

/* Plan §1.7 retry policy applied to a single failure event:
 *   AURA_BOOTSTRAP_ACTION_RETRY_NOW: TRANSIENT, first attempt → 1 auto-retry.
 *   AURA_BOOTSTRAP_ACTION_COOLDOWN:  TRANSIENT, retry already used → 24h
 *                                    cooldown, persist retry_after_ms.
 *   AURA_BOOTSTRAP_ACTION_ABORT:     INTEGRITY/RESOURCE/DEPENDENCY, no
 *                                    cooldown — operator must intervene.
 *   AURA_BOOTSTRAP_ACTION_NONE:      OK input, nothing to do. */
typedef enum {
    AURA_BOOTSTRAP_ACTION_NONE       = 0,
    AURA_BOOTSTRAP_ACTION_RETRY_NOW  = 1,
    AURA_BOOTSTRAP_ACTION_COOLDOWN   = 2,
    AURA_BOOTSTRAP_ACTION_ABORT      = 3
} AuraBootstrapAction;

AuraBootstrapAction aura_bootstrap_decide_action(
    AuraBootstrapFailure failure,
    int                  attempts_used);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_BOOTSTRAP_CLASSIFY_H */
