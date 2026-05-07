/*
 * ghidra_adapter.h — Ghidra Engine Adapter (Phase 2 / Tasks.md 2.x).
 *
 * Concrete adapter that fits Ghidra onto the engine-agnostic contract
 * defined in include/engine_request.h. The adapter:
 *
 *   - publishes a manifest with engine_id="ghidra", version "12.0.4",
 *     supported_types = {analyze, decompile} (Tasks.md 2.3),
 *   - implements the AuraEngineAdapter vtable, routing decompile
 *     requests to the existing aura_ghidra_decompile_at() wrapper
 *     (include/ghidra_subprocess.h),
 *   - returns AURA_ENGINE_ERR_UNSUPPORTED for analyze until the
 *     analyze-side adapter lands (still a valid manifest entry — the
 *     orchestrator is allowed to advertise types whose handlers are
 *     placeholders, as long as the placeholder path is observable).
 *
 * Per rules.md R-3, this is the only place Ghidra-specific code lives;
 * orchestrator and request schema remain engine-neutral.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_GHIDRA_ADAPTER_H
#define AURA_GHIDRA_ADAPTER_H

#include "engine_manifest.h"
#include "engine_request.h"
#include "ghidra_subprocess.h"
#include "orchestrator.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Manifest pointer (static storage, lifetime = process). */
const AuraEngineManifest *aura_ghidra_adapter_manifest(void);

/* Adapter vtable pointer (static storage, lifetime = process). */
const AuraEngineAdapter *aura_ghidra_adapter_vtable(void);

/* Convenience registration helper.
 *
 * Stashes `cfg` (shallow-copied) into a static slot consulted by the
 * adapter's init(). Pass NULL to use the zero-config default (paths
 * fall back to environment variables / build-time defaults inside the
 * subprocess wrapper). Then forwards to aura_orchestrator_register().
 *
 * Returns the same value as aura_orchestrator_register() (0 OK,
 * negative on failure). */
int aura_orchestrator_register_ghidra(
    AuraOrchestrator                  *orch,
    const AuraGhidraSubprocessConfig  *cfg_or_null);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_GHIDRA_ADAPTER_H */
