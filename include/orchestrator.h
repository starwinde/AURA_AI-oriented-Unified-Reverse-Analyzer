/*
 * orchestrator.h — AURA Engine Orchestrator (Phase 1 / Tasks.md 1.6).
 *
 * Single mediation point between AURA's UI / CLI and the set of
 * registered engine adapters. The orchestrator owns:
 *
 *   - the registry of (manifest, adapter, adapter_ctx) tuples,
 *   - the routing decision for a given request type,
 *   - the call into the adapter's vtable,
 *   - the (Phase 2+) crash / timeout isolation around that call.
 *
 * Per rules.md R-6, no other layer may spawn or dispatch to an engine
 * directly. UI / CLI / tests reach engines exclusively through this
 * API. The orchestrator is engine-agnostic; concrete adapters live in
 * src/adapter/<engine>/ in later phases.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_ORCHESTRATOR_H
#define AURA_ORCHESTRATOR_H

#include "engine_manifest.h"
#include "engine_request.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque handle. Definition lives in src/core/orchestrator.c. */
typedef struct AuraOrchestrator AuraOrchestrator;

/* Allocate a fresh orchestrator with an empty registry. Returns NULL
 * on allocation failure. */
AuraOrchestrator *aura_orchestrator_create(void);

/* Tear down the orchestrator: invokes adapter->shutdown() on every
 * registered adapter (in registration order) and frees the registry.
 * NULL-safe. */
void aura_orchestrator_destroy(AuraOrchestrator *orch);

/* Register an engine. The orchestrator validates the manifest, calls
 * adapter->init(), and stores the resulting context. Returns 0 on
 * success and a negative value on validation, capacity, or init
 * failure. The manifest and adapter pointers must remain valid for
 * the orchestrator's lifetime (typically static storage). */
int aura_orchestrator_register(AuraOrchestrator        *orch,
                               const AuraEngineManifest *manifest,
                               const AuraEngineAdapter  *adapter);

/* Route one request.
 *
 * `engine_id_or_null` chooses the target:
 *   - non-NULL: dispatch to the engine whose manifest.engine_id matches
 *     (case-sensitive strcmp). AURA_ENGINE_ERR_NOT_FOUND if absent or
 *     the engine does not advertise req->type.
 *   - NULL: dispatch to the first registered engine that advertises
 *     req->type (registration order). AURA_ENGINE_ERR_NOT_FOUND if no
 *     engine supports it.
 *
 * On any return value, `out` is populated and remains disposable via
 * aura_engine_response_dispose(). */
AuraEngineStatus aura_orchestrator_dispatch(AuraOrchestrator        *orch,
                                            const char              *engine_id_or_null,
                                            const AuraEngineRequest *req,
                                            AuraEngineResponse      *out);

/* Static policy lookup for "primary engines" of a request type
 * (rules.md R-8 — Type-별 Primary Set, redefined 2026-04-30 pivot).
 *
 * Fills `out_engine_ids[]` (capacity `cap`) with engine_id pointers
 * (static storage) in priority order and returns the number written.
 * Returns 0 if `type` has no primary set or `out_engine_ids == NULL` or
 * `cap == 0`.
 *
 * Phase 2A policy:
 *   ANALYZE   → {"rizin"}
 *   DECOMPILE → {"rizin", "ghidra"}
 *   DISASM    → {"rizin"}
 *   TRACE     → {"rizin"}
 *
 * The function does NOT consult the registry — it returns the policy
 * regardless of which engines are currently registered. Callers that
 * need "first registered primary" should walk the result and call
 * dispatch with each id in turn. */
size_t aura_orchestrator_select_primary(AuraEngineRequestType type,
                                         const char          **out_engine_ids,
                                         size_t                cap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_ORCHESTRATOR_H */
