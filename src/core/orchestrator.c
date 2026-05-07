/*
 * orchestrator.c — engine-agnostic dispatch / registry (Phase 1).
 *
 * Holds a small fixed-capacity registry of (manifest, adapter, adapter_ctx)
 * entries and routes one request at a time.
 *
 * Isolation strategy (Tasks.md 1.7):
 *
 *   - Subprocess-level isolation lives in the engine_subprocess primitive
 *     and the per-engine adapter (rules.md R-3): the adapter is the
 *     contractual boundary that translates child crashes / timeouts into
 *     AuraEngineStatus values. The orchestrator never sees an unmapped
 *     POSIX signal or unbounded blocking I/O.
 *
 *   - Cross-engine isolation lives here: each registry slot owns its own
 *     `adapter_ctx`, and the orchestrator never shares mutable state
 *     between slots. A CRASH or TIMEOUT on engine A leaves engine B's
 *     slot untouched and dispatchable. Per-slot diagnostic counters
 *     (`dispatch_count`, `failure_count`, `last_status`) make it cheap
 *     for callers to detect a flaky engine without taking a lock or
 *     restarting the orchestrator.
 *
 *   - Request validation (R-7): the orchestrator rejects any request
 *     whose `type` is outside the standard four. An adapter cannot smuggle
 *     a non-standard request type past this guard because the manifest
 *     validator already rejects non-standard `supported_types` bits.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "orchestrator.h"

#include <stdlib.h>
#include <string.h>

#include "logger.h"

/* Capacity is small on purpose: AURA's design only contemplates a
 * handful of engines (Ghidra primary + a few secondaries). A fixed
 * array keeps the implementation trivial and avoids reallocation
 * lifetime questions for the manifest / adapter pointers. */
#define AURA_ORCH_MAX_ENGINES 8

typedef struct AuraOrchestratorEntry {
    const AuraEngineManifest *manifest;
    const AuraEngineAdapter  *adapter;
    void                     *adapter_ctx;
    /* Per-engine diagnostic counters. Phase 1.7 cross-engine isolation:
     * a failure here MUST NOT spread to other slots. */
    unsigned long             dispatch_count;
    unsigned long             failure_count;
    AuraEngineStatus          last_status;
} AuraOrchestratorEntry;

struct AuraOrchestrator {
    AuraOrchestratorEntry entries[AURA_ORCH_MAX_ENGINES];
    size_t                count;
};

void aura_engine_response_dispose(AuraEngineResponse *response)
{
    if (!response) {
        return;
    }
    free(response->body);
    free(response->raw);
    free(response->diagnostics);
    response->body = NULL;
    response->raw = NULL;
    response->diagnostics = NULL;
    response->body_size = 0;
    response->raw_size = 0;
    response->diagnostics_size = 0;
}

/* ── R-8: type-별 primary engine set (Phase 2A pivot) ───────────────── */

size_t aura_orchestrator_select_primary(AuraEngineRequestType type,
                                         const char          **out_engine_ids,
                                         size_t                cap)
{
    if (!out_engine_ids || cap == 0) return 0;

    static const char *const ANALYZE_PRIMARY[]   = { "rizin" };
    static const char *const DECOMPILE_PRIMARY[] = { "rizin", "ghidra" };
    static const char *const DISASM_PRIMARY[]    = { "rizin" };
    static const char *const TRACE_PRIMARY[]     = { "rizin" };

    const char *const *src = NULL;
    size_t             n   = 0;

    switch (type) {
    case AURA_ENGINE_REQ_ANALYZE:
        src = ANALYZE_PRIMARY;
        n   = sizeof(ANALYZE_PRIMARY) / sizeof(ANALYZE_PRIMARY[0]);
        break;
    case AURA_ENGINE_REQ_DECOMPILE:
        src = DECOMPILE_PRIMARY;
        n   = sizeof(DECOMPILE_PRIMARY) / sizeof(DECOMPILE_PRIMARY[0]);
        break;
    case AURA_ENGINE_REQ_DISASM:
        src = DISASM_PRIMARY;
        n   = sizeof(DISASM_PRIMARY) / sizeof(DISASM_PRIMARY[0]);
        break;
    case AURA_ENGINE_REQ_TRACE:
        src = TRACE_PRIMARY;
        n   = sizeof(TRACE_PRIMARY) / sizeof(TRACE_PRIMARY[0]);
        break;
    default:
        return 0;
    }

    size_t copy = (n < cap) ? n : cap;
    for (size_t i = 0; i < copy; ++i) out_engine_ids[i] = src[i];
    return copy;
}

AuraOrchestrator *aura_orchestrator_create(void)
{
    AuraOrchestrator *orch = (AuraOrchestrator *)calloc(1, sizeof(*orch));
    if (!orch) {
        AURA_LOG_E("orchestrator: allocation failed");
        return NULL;
    }
    return orch;
}

void aura_orchestrator_destroy(AuraOrchestrator *orch)
{
    if (!orch) {
        return;
    }
    for (size_t i = 0; i < orch->count; ++i) {
        AuraOrchestratorEntry *e = &orch->entries[i];
        if (e->adapter && e->adapter->shutdown) {
            e->adapter->shutdown(e->adapter_ctx);
        }
        e->manifest = NULL;
        e->adapter = NULL;
        e->adapter_ctx = NULL;
    }
    orch->count = 0;
    free(orch);
}

int aura_orchestrator_register(AuraOrchestrator         *orch,
                               const AuraEngineManifest *manifest,
                               const AuraEngineAdapter  *adapter)
{
    if (!orch || !manifest || !adapter) {
        return -1;
    }
    if (!adapter->request) {
        AURA_LOG_E("orchestrator: adapter missing required `request` fn");
        return -2;
    }
    int rc = aura_engine_manifest_validate(manifest);
    if (rc != 0) {
        AURA_LOG_E("orchestrator: manifest invalid (rc=%d) for engine '%s'",
                   rc, manifest->engine_id ? manifest->engine_id : "(null)");
        return -3;
    }
    if (orch->count >= AURA_ORCH_MAX_ENGINES) {
        AURA_LOG_E("orchestrator: registry full (max=%d)", AURA_ORCH_MAX_ENGINES);
        return -4;
    }

    void *ctx = NULL;
    if (adapter->init) {
        int init_rc = adapter->init(&ctx);
        if (init_rc != 0) {
            AURA_LOG_E("orchestrator: adapter '%s' init failed (rc=%d)",
                       manifest->engine_id, init_rc);
            return -5;
        }
    }

    AuraOrchestratorEntry *slot = &orch->entries[orch->count];
    slot->manifest = manifest;
    slot->adapter = adapter;
    slot->adapter_ctx = ctx;
    slot->dispatch_count = 0;
    slot->failure_count = 0;
    slot->last_status = AURA_ENGINE_OK;
    orch->count += 1;
    return 0;
}

/* R-7 guard: only the four standard request types ever reach an adapter. */
static int request_type_is_standard(AuraEngineRequestType t)
{
    switch (t) {
    case AURA_ENGINE_REQ_DISASM:
    case AURA_ENGINE_REQ_ANALYZE:
    case AURA_ENGINE_REQ_DECOMPILE:
    case AURA_ENGINE_REQ_TRACE:
        return 1;
    default:
        return 0;
    }
}

static AuraOrchestratorEntry *
orch_find_entry(AuraOrchestrator *orch,
                const char       *engine_id_or_null,
                AuraEngineRequestType type)
{
    for (size_t i = 0; i < orch->count; ++i) {
        AuraOrchestratorEntry *e = &orch->entries[i];
        if (!aura_engine_manifest_supports(e->manifest, type)) {
            continue;
        }
        if (engine_id_or_null) {
            if (e->manifest && e->manifest->engine_id &&
                strcmp(e->manifest->engine_id, engine_id_or_null) == 0) {
                return e;
            }
        } else {
            return e;
        }
    }
    return NULL;
}

AuraEngineStatus
aura_orchestrator_dispatch(AuraOrchestrator        *orch,
                           const char              *engine_id_or_null,
                           const AuraEngineRequest *req,
                           AuraEngineResponse      *out)
{
    if (!out) {
        return AURA_ENGINE_ERR_INVALID;
    }
    /* Always leave `out` in a disposable state, even on early return. */
    memset(out, 0, sizeof(*out));

    if (!orch || !req) {
        out->status = AURA_ENGINE_ERR_INVALID;
        return out->status;
    }
    if (!request_type_is_standard(req->type)) {
        /* R-7: refuse anything outside disasm / analyze / decompile / trace.
         * Routing such a request would risk an out-of-bounds shift in the
         * manifest's supported_types check. */
        out->type = req->type;
        out->status = AURA_ENGINE_ERR_INVALID;
        return out->status;
    }
    out->type = req->type;

    AuraOrchestratorEntry *entry = orch_find_entry(orch, engine_id_or_null, req->type);
    if (!entry) {
        out->status = AURA_ENGINE_ERR_NOT_FOUND;
        return out->status;
    }

    entry->dispatch_count += 1;

    AuraEngineStatus st = entry->adapter->request(entry->adapter_ctx, req, out);
    /* Mirror the request type even if the adapter forgot to. */
    out->type = req->type;
    out->status = st;

    /* Phase 1.7: account the outcome on this slot only. Cross-engine
     * isolation is achieved structurally (no shared state across slots);
     * the counters here are diagnostic, not enforcing. */
    entry->last_status = st;
    if (st != AURA_ENGINE_OK) {
        entry->failure_count += 1;
    }
    return st;
}
