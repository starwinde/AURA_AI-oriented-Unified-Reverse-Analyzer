/*
 * tp_hub.c — AURA Third-Party I/O Hub: dispatch entry points.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * Each public entry point follows the same contract:
 *   1. NULL-check inputs → E_INVAL
 *   2. Resolve adapter (preferred or AUTO via priority)
 *   3. Verify capability flag
 *   4. Open adapter ctx → invoke fn → close adapter ctx
 *   5. Return adapter's return value (or rc from open/close on failure)
 *
 * The skeleton opens/closes the adapter context per call. A future
 * revision may cache contexts keyed on (binary, source) for
 * pipeline-wide reuse.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "third_party_hub/tp_adapter.h"

#include <stddef.h>

/* AUTO dispatch priority (high → low). Fixed for skeleton; future
 * revisions may replace with a cost model. */
static const aura_tp_source_t k_auto_order[] = {
    AURA_TP_SOURCE_AURA_NATIVE,
    AURA_TP_SOURCE_RIZIN,
    AURA_TP_SOURCE_CAPSTONE,
    AURA_TP_SOURCE_ZYDIS,
    AURA_TP_SOURCE_GHIDRA,
    AURA_TP_SOURCE_YARA,
};
static const size_t k_auto_order_n =
    sizeof(k_auto_order) / sizeof(k_auto_order[0]);

static const aura_tp_adapter_t *resolve(aura_tp_source_t preferred,
                                        uint32_t         required_cap)
{
    if (preferred == AURA_TP_SOURCE_AUTO) {
        for (size_t i = 0; i < k_auto_order_n; ++i) {
            const aura_tp_adapter_t *a = aura_tp_lookup_adapter(k_auto_order[i]);
            if (a && (a->caps & required_cap)) return a;
        }
        return NULL;
    }

    const aura_tp_adapter_t *a = aura_tp_lookup_adapter(preferred);
    if (!a) return NULL;
    return (a->caps & required_cap) ? a : NULL;
}

/* Common wrapper: validate + resolve + open/dispatch/close. The
 * actual dispatch step is performed by the caller via the returned
 * adapter pointer (so we keep distinct fn-ptr type signatures intact). */
static int prologue(aura_tp_binary_t          *bin,
                    aura_tp_vec_t             *out,
                    aura_tp_source_t           preferred,
                    uint32_t                   required_cap,
                    const aura_tp_adapter_t  **out_adapter,
                    void                     **out_ctx)
{
    if (!bin || !out || !out_adapter || !out_ctx) return AURA_TP_E_INVAL;

    const aura_tp_adapter_t *a = resolve(preferred, required_cap);
    if (!a || !a->open_fn || !a->close_fn) return AURA_TP_E_NOTSUP;

    void *ctx = NULL;
    int rc = a->open_fn(bin, &ctx);
    if (rc != AURA_TP_OK) return rc;

    *out_adapter = a;
    *out_ctx     = ctx;
    return AURA_TP_OK;
}

int aura_tp_hub_disasm_range(aura_tp_binary_t *bin,
                             aura_tp_source_t  preferred,
                             aura_tp_addr_t    va,
                             size_t            len,
                             aura_tp_vec_t    *out_ops)
{
    const aura_tp_adapter_t *a   = NULL;
    void                    *ctx = NULL;
    int rc = prologue(bin, out_ops, preferred,
                      AURA_TP_CAP_DISASM_RANGE, &a, &ctx);
    if (rc != AURA_TP_OK) return rc;

    if (!a->disasm_range) { a->close_fn(ctx); return AURA_TP_E_NOTSUP; }

    int dispatch_rc = a->disasm_range(ctx, va, len, out_ops);
    int close_rc    = a->close_fn(ctx);
    return (dispatch_rc < 0) ? dispatch_rc : (close_rc < 0 ? close_rc : dispatch_rc);
}

int aura_tp_hub_list_functions(aura_tp_binary_t *bin,
                               aura_tp_source_t  preferred,
                               aura_tp_vec_t    *out_funcs)
{
    const aura_tp_adapter_t *a   = NULL;
    void                    *ctx = NULL;
    int rc = prologue(bin, out_funcs, preferred,
                      AURA_TP_CAP_LIST_FUNCS, &a, &ctx);
    if (rc != AURA_TP_OK) return rc;

    if (!a->list_functions) { a->close_fn(ctx); return AURA_TP_E_NOTSUP; }

    int dispatch_rc = a->list_functions(ctx, out_funcs);
    int close_rc    = a->close_fn(ctx);
    return (dispatch_rc < 0) ? dispatch_rc : (close_rc < 0 ? close_rc : dispatch_rc);
}

int aura_tp_hub_list_sections(aura_tp_binary_t *bin,
                              aura_tp_source_t  preferred,
                              aura_tp_vec_t    *out_sections)
{
    const aura_tp_adapter_t *a   = NULL;
    void                    *ctx = NULL;
    int rc = prologue(bin, out_sections, preferred,
                      AURA_TP_CAP_LIST_SECTIONS, &a, &ctx);
    if (rc != AURA_TP_OK) return rc;

    if (!a->list_sections) { a->close_fn(ctx); return AURA_TP_E_NOTSUP; }

    int dispatch_rc = a->list_sections(ctx, out_sections);
    int close_rc    = a->close_fn(ctx);
    return (dispatch_rc < 0) ? dispatch_rc : (close_rc < 0 ? close_rc : dispatch_rc);
}
