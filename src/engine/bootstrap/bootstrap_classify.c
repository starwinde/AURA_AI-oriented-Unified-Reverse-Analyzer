// src/engine/bootstrap/bootstrap_classify.c — Phase 2.5 §1.7 GREEN minimal.

#include "bootstrap_classify.h"

#include <stddef.h>
#include <string.h>

const char *aura_bootstrap_failure_str(AuraBootstrapFailure f)
{
    switch (f) {
    case AURA_BOOTSTRAP_OK:                return "ok";
    case AURA_BOOTSTRAP_FAILED_TRANSIENT:  return "failed_transient";
    case AURA_BOOTSTRAP_FAILED_INTEGRITY:  return "failed_integrity";
    case AURA_BOOTSTRAP_FAILED_RESOURCE:   return "failed_resource";
    case AURA_BOOTSTRAP_FAILED_DEPENDENCY: return "failed_dependency";
    }
    return "ok";
}

AuraBootstrapAction aura_bootstrap_decide_action(
    AuraBootstrapFailure failure,
    int                  attempts_used)
{
    if (failure == AURA_BOOTSTRAP_OK) return AURA_BOOTSTRAP_ACTION_NONE;
    if (failure == AURA_BOOTSTRAP_FAILED_TRANSIENT) {
        /* Plan §1.7: one auto-retry, then 24h cooldown. attempts_used
         * counts the call that just failed, so 1 == still allowed to
         * retry once, ≥2 == burn cooldown. */
        if (attempts_used <= 1) return AURA_BOOTSTRAP_ACTION_RETRY_NOW;
        return AURA_BOOTSTRAP_ACTION_COOLDOWN;
    }
    /* INTEGRITY / RESOURCE / DEPENDENCY: never retry automatically. */
    return AURA_BOOTSTRAP_ACTION_ABORT;
}

AuraBootstrapFailure aura_bootstrap_classify(
    const AuraBootstrapErrorInput *in)
{
    if (!in || !in->kind) return AURA_BOOTSTRAP_OK;
    /* Tracer: only the network → TRANSIENT branch. Subsequent RED
     * tests force the other classes into existence one at a time. */
    if (strcmp(in->kind, "network") == 0) {
        return AURA_BOOTSTRAP_FAILED_TRANSIENT;
    }
    if (strcmp(in->kind, "sha256") == 0) {
        return AURA_BOOTSTRAP_FAILED_INTEGRITY;
    }
    if (strcmp(in->kind, "disk") == 0) {
        return AURA_BOOTSTRAP_FAILED_RESOURCE;
    }
    if (strcmp(in->kind, "pip") == 0) {
        return AURA_BOOTSTRAP_FAILED_DEPENDENCY;
    }
    return AURA_BOOTSTRAP_OK;
}
