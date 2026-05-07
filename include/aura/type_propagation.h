/*
 * type_propagation.h — Phase 11.4.3 (P4.PP1) per ADR-0045.
 *
 * Display-only path (3rd adoption after ADR-0043 hex / ADR-0044 PP4):
 * `AuraTypePropagationCandidate` is NOT a 1급 record, NOT in
 * `AuraRecordCollection`. The body schema is unchanged. Candidates
 * are derived on demand via call_edge × callee-arg lookup over the
 * existing analyze body.
 *
 * R-9 boundary: AURA reads the engine's records (variables[], type_facts[],
 * call_edges[], instructions[]) and emits *call-site parameter slot*
 * candidates only. No alias chasing, no calling-convention interpretation
 * on the caller side, no return-value matching — those land in PP1 v2 or
 * stay rejected (alias permanently).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TYPE_PROPAGATION_H
#define AURA_TYPE_PROPAGATION_H

#include <stddef.h>
#include <stdint.h>

#include "aura/normalized_records.h"   /* AuraVariableId / AuraFunctionId */

#ifdef __cplusplus
extern "C" {
#endif

/* Forward decl — full definition lives in include/rizin_adapter.h, but
 * including the whole rizin adapter header here would pull in the
 * Rizin-shaped body layout. Keep this header free of adapter coupling. */
typedef struct AuraRizinAnalyzeBody AuraRizinAnalyzeBody;

typedef struct AuraTypePropagationCandidate {
    AuraVariableId var_id;             /* sink: callee-parameter var      */
    AuraFunctionId function_id;        /* sink's owning function (callee) */
    uint64_t       call_site_addr;     /* call_edge.site_addr             */
    char           old_type[64];       /* engine type_fact text or ""    */
    char           new_type[64];       /* user-proposed target type       */
    int            distance;           /* 1 = direct callee parameter     */
    char           source[16];         /* "callee_param"                  */
} AuraTypePropagationCandidate;

typedef struct AuraTypePropagationResult {
    AuraTypePropagationCandidate *items;
    size_t                        count;
} AuraTypePropagationResult;

/* Generate propagation candidates rooted at the given caller function
 * entry. Walks call_edges where caller_id == found(caller_entry), then
 * for each callee enumerates "arg"-kind variables and emits one
 * candidate per (call site, callee arg) pair. old_type comes from
 * type_facts (empty string if absent). target_type is copied verbatim
 * into each candidate's new_type.
 *
 * Returns 0 on success (out->items may be NULL when count == 0). On
 * allocation failure or invalid args, returns -1 and out is left zeroed.
 *
 * Caller frees the result with aura_type_propagation_result_free. */
int aura_type_propagation_generate(
    const AuraRizinAnalyzeBody *body,
    uint64_t                    caller_entry,
    const char                 *target_type,
    AuraTypePropagationResult  *out);

void aura_type_propagation_result_free(AuraTypePropagationResult *r);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* AURA_TYPE_PROPAGATION_H */
