/*
 * engine_manifest.c — manifest validation helpers (Phase 1 / Tasks.md 1.4).
 *
 * Pure helpers, no I/O. Keeps the orchestrator free of policy code so
 * the same checks can be applied at adapter-registration time and from
 * unit tests without going through the full registry.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "engine_manifest.h"

int aura_engine_manifest_supports(const AuraEngineManifest *m,
                                  AuraEngineRequestType     t)
{
    if (!m) {
        return 0;
    }
    return (m->supported_types & (1u << (unsigned)t)) != 0u;
}

int aura_engine_manifest_validate(const AuraEngineManifest *m)
{
    if (!m) {
        return -1;
    }
    if (!m->engine_id || !m->version) {
        return -2;
    }
    if (m->supported_types == 0u) {
        return -3;
    }
    /* Reject non-standard request type bits (rules.md R-7). */
    if ((m->supported_types & ~AURA_ENGINE_REQ_TYPE_MASK_ALL) != 0u) {
        return -4;
    }
    return 0;
}
