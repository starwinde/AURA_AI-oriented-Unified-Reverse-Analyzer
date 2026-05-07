/*
 * rizin_to_aura.h — third-party hub: AuraRizinCanonical → 1st-class
 * AURA normalized records (R-11/R-12).
 *
 * The Rizin adapter populates AuraRizinCanonical (a mirror of rizin's
 * JSON output schema). This module is the single permitted consumer of
 * that mirror outside src/adapter/rizin/. It produces records in the
 * engine-agnostic AuraRecordCollection, attaching provenance
 * `{source="rizin", confidence, completeness}` to every record.
 *
 * Phase 2A scope:
 *   - functions[] → AuraFunctionRecord
 *   - symbols[]   → AuraSymbolRecord
 *   - blocks/edges/xrefs/variables/type-facts: skeleton; populated as
 *     Phase 2B widens canonical.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_THIRD_PARTY_HUB_RIZIN_TO_AURA_H
#define AURA_THIRD_PARTY_HUB_RIZIN_TO_AURA_H

#include "aura/normalized_records.h"
#include "third_party_hub/rizin_canonical.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraRizinHubStatus {
    AURA_RIZIN_HUB_OK         = 0,
    AURA_RIZIN_HUB_ERR_INVALID = 1, /* NULL inputs                       */
    AURA_RIZIN_HUB_ERR_INSERT  = 2, /* a record was rejected (R-11/R-12) */
} AuraRizinHubStatus;

/* Default provenance values for Phase 2A.
 *
 * confidence    — `aflj` is rizin's authoritative function list, so 0.9.
 *                 Symbols come straight from the binary's symbol table
 *                 (`isj`), so 0.95.
 * completeness  — 1.0 once aflj/isj have run; lower if the canonical
 *                 array length is 0 while the binary clearly had data
 *                 (caller can override). */
#define AURA_RIZIN_HUB_FN_CONFIDENCE     0.90f
#define AURA_RIZIN_HUB_FN_COMPLETENESS   1.00f
#define AURA_RIZIN_HUB_SYM_CONFIDENCE    0.95f
#define AURA_RIZIN_HUB_SYM_COMPLETENESS  1.00f
#define AURA_RIZIN_HUB_BLOCK_CONFIDENCE     0.90f
#define AURA_RIZIN_HUB_BLOCK_COMPLETENESS   1.00f
#define AURA_RIZIN_HUB_EDGE_CONFIDENCE      0.90f
#define AURA_RIZIN_HUB_EDGE_COMPLETENESS    1.00f
#define AURA_RIZIN_HUB_VAR_CONFIDENCE       0.85f
#define AURA_RIZIN_HUB_VAR_COMPLETENESS     1.00f
#define AURA_RIZIN_HUB_TFACT_CONFIDENCE     0.80f
#define AURA_RIZIN_HUB_TFACT_COMPLETENESS   1.00f
#define AURA_RIZIN_HUB_CALL_CONFIDENCE      0.90f
#define AURA_RIZIN_HUB_CALL_COMPLETENESS    1.00f
#define AURA_RIZIN_HUB_XREF_CONFIDENCE      0.90f
#define AURA_RIZIN_HUB_XREF_COMPLETENESS    1.00f
#define AURA_RIZIN_HUB_STRING_CONFIDENCE    0.95f
#define AURA_RIZIN_HUB_STRING_COMPLETENESS  1.00f

/* Map an AuraRizinCanonical bundle into normalized records and append
 * to the (caller-owned) collection.
 *
 * On per-record provenance/insert failure: returns ERR_INSERT, but
 * already-inserted records remain (caller decides whether to discard
 * the collection). NULL collection or NULL canonical → ERR_INVALID. */
AuraRizinHubStatus aura_rizin_to_aura_normalize(
    const AuraRizinCanonical *canonical,
    AuraRecordCollection     *out);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_THIRD_PARTY_HUB_RIZIN_TO_AURA_H */
