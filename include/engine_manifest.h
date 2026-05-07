/*
 * engine_manifest.h — AURA Engine Manifest (Phase 1 / Tasks.md 1.4).
 *
 * Static descriptor each engine adapter advertises to the orchestrator.
 * It declares which standard request types the engine answers, where
 * its executable lives (when applicable), and an opaque capability
 * bitmask for finer-grained feature gating.
 *
 * The manifest is the only place the orchestrator learns what an engine
 * can do; per rules.md R-7 / R-8 it cannot be bypassed or extended at
 * the call site. supported_types is restricted to the four standard
 * AURA_ENGINE_REQ_* bits — non-standard bits cause validation failure.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_ENGINE_MANIFEST_H
#define AURA_ENGINE_MANIFEST_H

#include <stdint.h>

#include "engine_request.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Capability flag bitmask. Phase 1 only defines the absence sentinel.
 * Concrete capabilities (HighFunction, CFG, types, etc.) are added in
 * Phase 2 when the Ghidra adapter lands and the values can be defined
 * with real semantics rather than guessed up front. */
#define AURA_ENGINE_CAP_NONE 0u

typedef struct AuraEngineManifest {
    const char *engine_id;        /* e.g. "ghidra", "rizin" — required */
    const char *version;          /* e.g. "12.0.4" — required          */
    const char *exec_path;        /* subprocess binary, or NULL for    *
                                   * in-process adapters               */
    uint32_t    supported_types;  /* bitmask: 1u << AuraEngineRequestType*/
    uint32_t    capability_flags; /* AURA_ENGINE_CAP_* OR'd together   */
} AuraEngineManifest;

/* Returns non-zero if `m` advertises support for `t`. NULL-safe. */
int aura_engine_manifest_supports(const AuraEngineManifest *m,
                                  AuraEngineRequestType     t);

/* Returns 0 on success, negative on failure. Validates:
 *   - manifest is non-NULL,
 *   - engine_id and version are non-NULL,
 *   - supported_types is non-zero,
 *   - supported_types contains only standard AURA_ENGINE_REQ_* bits
 *     (R-7 forbids inventing new request types).
 */
int aura_engine_manifest_validate(const AuraEngineManifest *m);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_ENGINE_MANIFEST_H */
