// src/engine/probe/probe_cache.c — Phase 2.5 slice 7'

#include "probe_cache.h"

#include <stdlib.h>
#include <string.h>

#include "probe_registry.h"

struct AuraProbeCache {
    int64_t      ttl_ms;
    AuraClockFn  clock;
    void        *clock_ctx;
    char        *cached_json;       /* NULL until first build */
    int64_t      cached_at_ms;
    int          have_cached;
};

AuraProbeCache *aura_probe_cache_create(int64_t      ttl_ms,
                                        AuraClockFn  clock,
                                        void        *clock_ctx) {
    if (!clock || ttl_ms < 0) return NULL;
    AuraProbeCache *c = (AuraProbeCache *)calloc(1, sizeof(*c));
    if (!c) return NULL;
    c->ttl_ms    = ttl_ms;
    c->clock     = clock;
    c->clock_ctx = clock_ctx;
    return c;
}

void aura_probe_cache_destroy(AuraProbeCache *cache) {
    if (!cache) return;
    free(cache->cached_json);
    free(cache);
}

static char *xstrdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *o = (char *)malloc(n);
    if (o) memcpy(o, s, n);
    return o;
}

int aura_probe_cache_get(AuraProbeCache    *cache,
                         AuraCommandRunner *runner,
                         char             **out_json) {
    if (!cache || !runner || !out_json) return -1;

    int64_t now = cache->clock(cache->clock_ctx);
    if (cache->have_cached &&
        (now - cache->cached_at_ms) < cache->ttl_ms) {
        char *dup = xstrdup(cache->cached_json);
        if (!dup) return -2;
        *out_json = dup;
        return 0;
    }

    char *fresh = NULL;
    int rc = aura_probe_collect_all(runner, &fresh);
    if (rc != 0) return rc;

    free(cache->cached_json);
    cache->cached_json  = fresh;
    cache->cached_at_ms = now;
    cache->have_cached  = 1;

    char *dup = xstrdup(fresh);
    if (!dup) return -3;
    *out_json = dup;
    return 0;
}
