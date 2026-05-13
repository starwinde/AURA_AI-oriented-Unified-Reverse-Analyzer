// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * string_protection_store.h — SQLite tables for protected string views.
 *
 * Scope v1:
 *   - Persist engine-reported strings without mutating engine output.
 *   - Keep user aliases separate from mask tokens.
 *   - Persist detector findings that justify a protected display value.
 */

#ifndef AURA_STRING_PROTECTION_STORE_H
#define AURA_STRING_PROTECTION_STORE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_STRING_PROTECTION_FP_HEX_CAP      64
#define AURA_STRING_PROTECTION_TEXT_CAP        512
#define AURA_STRING_PROTECTION_SMALL_TEXT_CAP  128

typedef struct AuraStoredStringRecord {
    char     binary_fingerprint[AURA_STRING_PROTECTION_FP_HEX_CAP + 1];
    char     engine_id[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    int64_t  analysis_run_id;
    uint64_t string_id;
    uint64_t addr;
    uint64_t length;
    char     encoding[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    char     section[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    char     original_text[AURA_STRING_PROTECTION_TEXT_CAP];
    char     source[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
} AuraStoredStringRecord;

typedef struct AuraStringOverrideRecord {
    char     binary_fingerprint[AURA_STRING_PROTECTION_FP_HEX_CAP + 1];
    uint64_t string_addr;
    char     original_hash[AURA_STRING_PROTECTION_FP_HEX_CAP + 1];
    char     alias[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    char     mask_token[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    int      display_mode;
} AuraStringOverrideRecord;

typedef struct AuraStringProtectionFinding {
    char     binary_fingerprint[AURA_STRING_PROTECTION_FP_HEX_CAP + 1];
    uint64_t string_addr;
    char     detector_id[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    char     finding_kind[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
    int      start_offset;
    int      end_offset;
    double   confidence;
    char     mask_token[AURA_STRING_PROTECTION_SMALL_TEXT_CAP];
} AuraStringProtectionFinding;

typedef struct AuraStringProtectionStore AuraStringProtectionStore;

AuraStringProtectionStore *aura_string_protection_store_open(const char *path);
void aura_string_protection_store_close(AuraStringProtectionStore *store);

int aura_string_protection_store_put_string(
    AuraStringProtectionStore    *store,
    const AuraStoredStringRecord *rec);

int aura_string_protection_store_put_override(
    AuraStringProtectionStore       *store,
    const AuraStringOverrideRecord  *rec);

int aura_string_protection_store_get_override(
    AuraStringProtectionStore *store,
    const char                *binary_fingerprint,
    uint64_t                   string_addr,
    const char                *original_hash,
    AuraStringOverrideRecord  *out);

int aura_string_protection_store_put_finding(
    AuraStringProtectionStore        *store,
    const AuraStringProtectionFinding *rec);

int aura_string_protection_store_delete_for_fingerprint(
    AuraStringProtectionStore *store,
    const char                *binary_fingerprint);

int aura_string_protection_store_count_strings(AuraStringProtectionStore *store);
int aura_string_protection_store_count_overrides(AuraStringProtectionStore *store);
int aura_string_protection_store_count_findings(AuraStringProtectionStore *store);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_STRING_PROTECTION_STORE_H */
