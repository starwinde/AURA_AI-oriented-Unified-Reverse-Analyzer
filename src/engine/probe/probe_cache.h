// src/engine/probe/probe_cache.h — Phase 2.5 slice 7'
//
// In-memory TTL cache wrapping aura_probe_collect_all. Plan §1.1
// specifies a 5-minute TTL plus a persistent DB layer; this slice
// delivers only the in-memory half. The persistent layer is a later
// slice that depends on a DB schema decision.
//
// The clock is injected so tests can drive expiry deterministically.
// Production wiring uses a monotonic-clock adapter.

#ifndef AURA_ENGINE_PROBE_CACHE_H
#define AURA_ENGINE_PROBE_CACHE_H

#include <stdint.h>

#include "command_runner.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Returns "now" in milliseconds. Implementation may use any reference
 * point; the cache only cares about deltas, so a monotonic source is
 * appropriate in production. */
typedef int64_t (*AuraClockFn)(void *ctx);

typedef struct AuraProbeCache AuraProbeCache;

/* Create a cache with the given TTL. clock+clock_ctx must remain valid
 * for the cache lifetime. Returns NULL on allocation failure or invalid
 * arguments. */
AuraProbeCache *aura_probe_cache_create(int64_t      ttl_ms,
                                        AuraClockFn  clock,
                                        void        *clock_ctx);

void aura_probe_cache_destroy(AuraProbeCache *cache);

/* Returns a freshly-strdup'd JSON envelope via *out_json. On a cache
 * hit (within TTL of the previous build) the cached envelope is
 * returned without re-running probes; on miss, runner is invoked.
 *
 * Caller frees *out_json. Returns 0 on success, negative on failure. */
int aura_probe_cache_get(AuraProbeCache    *cache,
                         AuraCommandRunner *runner,
                         char             **out_json);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_CACHE_H */
