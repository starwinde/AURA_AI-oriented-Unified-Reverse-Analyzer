// src/engine/consent/consent_lock.h — Phase 2.5 §1.5
//
// Automation escape hatch. Plan §1.5: a CI / unattended user runs
// `aura --bootstrap-engines all` once, which writes
// ~/.aura/engine_consent.lock. The presence of that file is a blanket
// "yes, you may bootstrap any engine without prompting" signal that
// short-circuits the gate's ASK_USER branch.
//
// Kept narrow on purpose — just file presence + path resolution. The
// decision wrapper (`aura_consent_check_with_lock`) lands in a later
// slice once the test for the wrapper exists.

#ifndef AURA_ENGINE_CONSENT_LOCK_H
#define AURA_ENGINE_CONSENT_LOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/* 1 if the lock file at `path` is present and readable, 0 if absent,
 * -1 on a path-level error (e.g. NULL path). Stat-only — does not
 * open or modify the file, does not parse contents. */
int aura_consent_lock_exists(const char *path);

/* Decision wrapper. If `lock_path` is present, return GRANTED for
 * every engine without consulting the store — that is the automation
 * blanket-consent contract from plan §1.5. Otherwise delegate to the
 * regular store-backed `aura_consent_check`. NULL `lock_path` is
 * equivalent to "no lock" (delegate). */
#include "consent_gate.h"

AuraConsentDecision aura_consent_check_with_lock(
    AuraConsentStore *store,
    const char       *engine_id,
    int64_t           now_ms,
    const char       *lock_path);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_CONSENT_LOCK_H */
