/*
 * diagnostics.c — Phase 3E sidecar diagnostic stream — alloc + view.
 *
 * Visibility-only stream isolated from AuraEngineResponse.body. See
 * include/aura/diagnostics.h for the wire layout and R-9 constraints.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "aura/diagnostics.h"

#include <stdlib.h>
#include <string.h>

int aura_diagnostics_view(const void                   *blob,
                          size_t                        blob_size,
                          const AuraDiagnosticsHeader **out_header,
                          const AuraDiagnosticEntry   **out_entries)
{
    if (out_header)  *out_header  = NULL;
    if (out_entries) *out_entries = NULL;
    if (!blob || blob_size < sizeof(AuraDiagnosticsHeader)) return -1;

    const AuraDiagnosticsHeader *h = (const AuraDiagnosticsHeader *)blob;
    if (h->magic   != AURA_DIAG_BLOB_MAGIC)   return -2;
    if (h->version != AURA_DIAG_BLOB_VERSION) return -3;

    size_t need = sizeof(AuraDiagnosticsHeader)
                + (size_t)h->count * sizeof(AuraDiagnosticEntry);
    if (blob_size < need) return -4;

    if (out_header)  *out_header  = h;
    if (out_entries) {
        *out_entries = (const AuraDiagnosticEntry *)
            ((const char *)blob + sizeof(AuraDiagnosticsHeader));
    }
    return 0;
}

int aura_diagnostics_alloc_critical(const char            *reason_key,
                                    AuraDiagnosticRefKind  ref_kind,
                                    uint64_t               ref_id,
                                    void                 **out_blob,
                                    size_t                *out_size)
{
    if (!reason_key || !out_blob || !out_size) return -1;
    *out_blob = NULL;
    *out_size = 0;

    size_t klen = strlen(reason_key);
    if (klen == 0 || klen >= AURA_DIAG_REASON_KEY_MAX) return -2;

    size_t total = sizeof(AuraDiagnosticsHeader)
                 + sizeof(AuraDiagnosticEntry);
    void *p = calloc(1, total);
    if (!p) return -3;

    AuraDiagnosticsHeader *h = (AuraDiagnosticsHeader *)p;
    h->magic    = AURA_DIAG_BLOB_MAGIC;
    h->version  = AURA_DIAG_BLOB_VERSION;
    h->count    = 1u;
    h->reserved = 0u;

    AuraDiagnosticEntry *e = (AuraDiagnosticEntry *)
        ((char *)p + sizeof(AuraDiagnosticsHeader));
    memcpy(e->reason_key, reason_key, klen);
    e->reason_key[klen] = '\0';
    e->severity = (uint32_t)AURA_DIAG_SEV_CRITICAL;
    e->ref_kind = (uint32_t)ref_kind;
    e->ref_id   = ref_id;

    *out_blob = p;
    *out_size = total;
    return 0;
}
