/*
 * tp_registry.c — AURA Third-Party I/O Hub: adapter registry.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * Static-array registry. Adapters are immutable globals — the
 * registry stores pointers, never copies. Process-wide single
 * instance; thread-affinity is the caller's responsibility (for
 * the skeleton, registration is expected at startup before any
 * dispatch fan-out).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "third_party_hub/tp_adapter.h"

#include <stddef.h>

static const aura_tp_adapter_t *g_adapters[AURA_TP_REGISTRY_MAX];
static size_t                   g_count;

int aura_tp_register_adapter(const aura_tp_adapter_t *adp)
{
    if (!adp || !adp->name) return AURA_TP_E_INVAL;
    if (adp->source <= AURA_TP_SOURCE_UNKNOWN ||
        adp->source >= AURA_TP_SOURCE__COUNT) {
        return AURA_TP_E_INVAL;
    }

    for (size_t i = 0; i < g_count; ++i) {
        if (g_adapters[i]->source == adp->source) return AURA_TP_E_DUP;
    }

    if (g_count >= AURA_TP_REGISTRY_MAX) return AURA_TP_E_FULL;

    g_adapters[g_count++] = adp;
    return AURA_TP_OK;
}

const aura_tp_adapter_t *aura_tp_lookup_adapter(aura_tp_source_t source)
{
    for (size_t i = 0; i < g_count; ++i) {
        if (g_adapters[i]->source == source) return g_adapters[i];
    }
    return NULL;
}

void aura_tp_clear_registry(void)
{
    for (size_t i = 0; i < AURA_TP_REGISTRY_MAX; ++i) g_adapters[i] = NULL;
    g_count = 0;
}
