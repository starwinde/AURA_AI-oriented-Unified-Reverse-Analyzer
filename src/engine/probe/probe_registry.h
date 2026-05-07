// src/engine/probe/probe_registry.h — Phase 2.5 slice 6
//
// Collector that runs every per-engine probe and emits a single JSON
// envelope describing the host's RE-engine availability. The envelope
// shape is deliberately flat so downstream consumers (CLI / GUI / LLM
// context provider) can index by engine_id without parsing nested
// arrays.

#ifndef AURA_ENGINE_PROBE_REGISTRY_H
#define AURA_ENGINE_PROBE_REGISTRY_H

#include "command_runner.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Run every engine probe in turn, serialize results to a JSON object
 * keyed by engine_id, and return the heap-allocated string via *out_json.
 *
 * Caller takes ownership: free(*out_json).
 *
 * Returns 0 on success, negative on failure (NULL args, JSON OOM, etc.). */
int aura_probe_collect_all(AuraCommandRunner *runner, char **out_json);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_REGISTRY_H */
