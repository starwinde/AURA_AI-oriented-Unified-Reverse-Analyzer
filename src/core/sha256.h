/*
 * sha256.h — minimal SHA-256 (FIPS 180-4) for AURA.
 *
 * Implementation is pure C, no external dependencies. Used by:
 *   - CLI `aura info` for binary fingerprint output (Phase 11.1).
 *   - Future override fingerprint (Phase 4A binary anchor) when the
 *     fingerprint computation is moved out of adapter into core.
 *
 * Based on Brad Conte's public-domain SHA-256 (crypto-algorithms repo).
 * Adapted to AURA naming. Public domain.
 *
 * Copyright 2026 AURA Project Contributors (adaptations only).
 * SPDX-License-Identifier: Apache-2.0 OR Unlicense
 */
#ifndef AURA_SHA256_H
#define AURA_SHA256_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_SHA256_DIGEST_LEN 32

typedef struct AuraSha256Ctx {
    uint8_t  data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} AuraSha256Ctx;

void aura_sha256_init(AuraSha256Ctx *ctx);
void aura_sha256_update(AuraSha256Ctx *ctx, const void *data, size_t len);
void aura_sha256_final(AuraSha256Ctx *ctx, uint8_t out[AURA_SHA256_DIGEST_LEN]);

/* One-shot helper: hash entire file at `path`. Returns 0 on success,
 * negative on open / read failure. `out` is filled with 32 raw bytes. */
int aura_sha256_file(const char *path, uint8_t out[AURA_SHA256_DIGEST_LEN]);

/* Hex-encode 32-byte digest into 64+1 char buffer. */
void aura_sha256_hex(const uint8_t digest[AURA_SHA256_DIGEST_LEN],
                     char         out[AURA_SHA256_DIGEST_LEN * 2 + 1]);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_SHA256_H */
