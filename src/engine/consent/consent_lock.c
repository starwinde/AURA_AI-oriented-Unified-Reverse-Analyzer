// src/engine/consent/consent_lock.c — Phase 2.5 §1.5

#include "consent_lock.h"

#include <stddef.h>
#include <sys/stat.h>

int aura_consent_lock_exists(const char *path)
{
    if (!path || !*path) return -1;
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return 1;
}

AuraConsentDecision aura_consent_check_with_lock(
    AuraConsentStore *store,
    const char       *engine_id,
    int64_t           now_ms,
    const char       *lock_path)
{
    if (lock_path && aura_consent_lock_exists(lock_path) == 1) {
        return AURA_CONSENT_GRANTED;
    }
    return aura_consent_check(store, engine_id, now_ms);
}
