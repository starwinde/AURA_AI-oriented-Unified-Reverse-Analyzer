// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#ifndef AURA_ARTIFACT_CACHE_H
#define AURA_ARTIFACT_CACHE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_ARTIFACT_CACHE_FINGERPRINT_CAP    65
#define AURA_ARTIFACT_CACHE_ENGINE_ID_CAP      32
#define AURA_ARTIFACT_CACHE_ENGINE_VERSION_CAP 64
#define AURA_ARTIFACT_CACHE_KIND_CAP           64
#define AURA_ARTIFACT_CACHE_BACKEND_CAP        64
#define AURA_ARTIFACT_CACHE_OPTIONS_HASH_CAP   65

typedef struct AuraArtifactCache AuraArtifactCache;

typedef struct AuraArtifactCacheKey {
    char     binary_fingerprint[AURA_ARTIFACT_CACHE_FINGERPRINT_CAP];
    char     engine_id[AURA_ARTIFACT_CACHE_ENGINE_ID_CAP];
    char     engine_version[AURA_ARTIFACT_CACHE_ENGINE_VERSION_CAP];
    int      request_type;
    char     artifact_kind[AURA_ARTIFACT_CACHE_KIND_CAP];
    char     backend[AURA_ARTIFACT_CACHE_BACKEND_CAP];
    int      schema_version;
    uint64_t function_addr;
    uint64_t window_addr;
    int      window_count;
    char     options_hash[AURA_ARTIFACT_CACHE_OPTIONS_HASH_CAP];
} AuraArtifactCacheKey;

AuraArtifactCache *aura_artifact_cache_open(const char *db_path);
void aura_artifact_cache_close(AuraArtifactCache *cache);

int aura_artifact_cache_put(AuraArtifactCache          *cache,
                            const AuraArtifactCacheKey *key,
                            const char                 *payload_json);

/*
 * Returns 1 for hit, 0 for miss, -1 for error.
 * On hit, *out_payload_json is malloc-owned and must be released with
 * aura_artifact_cache_free_payload().
 */
int aura_artifact_cache_get(AuraArtifactCache          *cache,
                            const AuraArtifactCacheKey *key,
                            char                      **out_payload_json);

void aura_artifact_cache_free_payload(char *payload_json);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_ARTIFACT_CACHE_H */
