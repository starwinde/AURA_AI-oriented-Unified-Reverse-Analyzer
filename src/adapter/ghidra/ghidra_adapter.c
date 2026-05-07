/*
 * ghidra_adapter.c — Ghidra primary engine adapter (Phase 2).
 *
 * Wires the existing aura-decompile subprocess wrapper
 * (src/decompiler/ghidra_subprocess.c) onto the engine-agnostic
 * AuraEngineAdapter contract. No engine-specific knowledge leaks back
 * into orchestrator.c or engine_request.h — that boundary is the whole
 * point of rules.md R-3.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ghidra_adapter.h"

#include <stdlib.h>
#include <string.h>

#include "aura/diagnostics.h"
#include "logger.h"

/* ── Manifest ─────────────────────────────────────────────────────────── */

/* Phase 2C scope narrowing: Ghidra is the DECOMPILE co-primary only.
 * analyze/disasm/trace primary 권한 was reassigned to rizin in Phase 2A.
 * The ANALYZE bit is intentionally removed — advertising a request type
 * we then reject with ERR_UNSUPPORTED would mislead consumers (R-4 / R-7
 * spirit). DECOMPILE is real-e2e-validated against the vendored
 * aura-decompile binary (test_orchestrator_ghidra_e2e: orchestrator →
 * adapter → subprocess → XML round-trip on trivial.elf @ 0x1129).
 *
 * Body normalization (XML → AuraEngineResponse.body) remains a Phase 3
 * concern; the adapter currently surfaces only raw_xml on out->raw, per
 * R-4 source-of-truth preservation. */
static const AuraEngineManifest g_ghidra_manifest = {
    .engine_id = "ghidra",
    .version   = "12.0.4",
    .exec_path = NULL, /* resolved per-call via the subprocess config; not a
                        * single fixed binary at this layer */
    .supported_types = (1u << AURA_ENGINE_REQ_DECOMPILE),
    .capability_flags = AURA_ENGINE_CAP_NONE,
};

const AuraEngineManifest *aura_ghidra_adapter_manifest(void)
{
    return &g_ghidra_manifest;
}

/* ── Configuration plumbing ───────────────────────────────────────────── */

/* The orchestrator's register flow calls adapter->init() with no
 * arguments, so the adapter pulls its subprocess config from this
 * static slot. aura_orchestrator_register_ghidra() sets it before
 * dispatching to aura_orchestrator_register(). NULL = use defaults. */
static AuraGhidraSubprocessConfig g_ghidra_pending_cfg;
static int                        g_ghidra_pending_cfg_set = 0;

/* Per-instance adapter context: a snapshot of the cfg taken at init
 * time. Owned by the orchestrator slot; freed in shutdown(). */
typedef struct GhidraAdapterCtx {
    AuraGhidraSubprocessConfig cfg;
    int                        has_cfg;
} GhidraAdapterCtx;

/* ── Status mapping (R-7 / Phase 1.7) ─────────────────────────────────── */

static AuraEngineStatus
ghidra_status_to_engine(AuraGhidraStatus s)
{
    switch (s) {
    case AURA_GHIDRA_OK:            return AURA_ENGINE_OK;
    case AURA_GHIDRA_ERR_TIMEOUT:   return AURA_ENGINE_ERR_TIMEOUT;
    case AURA_GHIDRA_ERR_KILLED:    return AURA_ENGINE_ERR_CRASH;
    case AURA_GHIDRA_ERR_ARGV:      /* malformed input */
    case AURA_GHIDRA_ERR_LOAD:
    case AURA_GHIDRA_ERR_ADDR:
    case AURA_GHIDRA_ERR_ARCH:      return AURA_ENGINE_ERR_INVALID;
    case AURA_GHIDRA_ERR_DECOMPILE: /* engine-internal failures */
    case AURA_GHIDRA_ERR_IO:
    case AURA_GHIDRA_ERR_SPAWN:
    case AURA_GHIDRA_ERR_INTERNAL:
    default:                        return AURA_ENGINE_ERR_INTERNAL;
    }
}

/* ── vtable: init / request / shutdown ────────────────────────────────── */

static int ghidra_adapter_init(void **adapter_ctx_out)
{
    if (!adapter_ctx_out) {
        return -1;
    }
    GhidraAdapterCtx *ctx = (GhidraAdapterCtx *)calloc(1, sizeof(*ctx));
    if (!ctx) {
        return -2;
    }
    if (g_ghidra_pending_cfg_set) {
        ctx->cfg = g_ghidra_pending_cfg;
        ctx->has_cfg = 1;
    }
    /* Consume the pending slot so a stale cfg cannot leak into a later
     * register() of a different engine instance. */
    memset(&g_ghidra_pending_cfg, 0, sizeof(g_ghidra_pending_cfg));
    g_ghidra_pending_cfg_set = 0;
    *adapter_ctx_out = ctx;
    return 0;
}

static void ghidra_adapter_shutdown(void *adapter_ctx)
{
    free(adapter_ctx);
}

static AuraEngineStatus
ghidra_handle_decompile(GhidraAdapterCtx        *ctx,
                        const AuraEngineRequest *req,
                        AuraEngineResponse      *out)
{
    if (!req->binary_path) {
        out->status = AURA_ENGINE_ERR_INVALID;
        return out->status;
    }

    AuraGhidraSubprocessConfig cfg;
    if (ctx && ctx->has_cfg) {
        cfg = ctx->cfg;
    } else {
        memset(&cfg, 0, sizeof(cfg));
        cfg.timeout_s = 30;
    }

    AuraGhidraDecompileResult r;
    memset(&r, 0, sizeof(r));
    AuraGhidraStatus gs = aura_ghidra_decompile_at(&cfg,
                                                   req->binary_path,
                                                   req->addr,
                                                   req->arch_or_null,
                                                   &r);

    /* R-4: keep the engine's raw output even on success. The XML is the
     * source of truth; any normalized body we add later (Phase 3) sits
     * alongside it, never in place of it. */
    out->raw      = r.xml;       /* may be NULL on failure */
    out->raw_size = r.xml_len;
    /* Phase 3C re-definition (2026-05-01): vendored aura-decompile emits
     * Ghidra IR/SSA, not PrettyPrint pseudo-C. The decompile body view
     * has no source-of-truth in that XML, so the adapter MUST keep body
     * NULL — fabricating one would violate R-9. The PrettyPrint absence
     * is surfaced via the Phase 3E diagnostics sidecar below. */
    out->body     = NULL;
    out->body_size = 0;
    /* stderr_log is diagnostic — we let the wrapper own it (it's freed
     * via aura_ghidra_decompile_result_free) and detach raw/xml. */
    r.xml = NULL;
    r.xml_len = 0;
    aura_ghidra_decompile_result_free(&r);

    out->status = ghidra_status_to_engine(gs);

    /* Phase 3E.1/3C.4: emit a single critical diagnostic on the success
     * path advertising that pseudo-C is unavailable for this backend.
     * Visibility-only — no body fix-up, no merge with raw. Allocation
     * failure is non-fatal: the response stays valid, callers simply
     * see no diagnostic. */
    if (out->status == AURA_ENGINE_OK && out->diagnostics == NULL) {
        void  *blob = NULL;
        size_t blob_size = 0;
        if (aura_diagnostics_alloc_critical(
                AURA_DIAG_REASON_GHIDRA_PSEUDO_C_UNAVAILABLE,
                AURA_DIAG_REF_REQUEST,
                req->addr,
                &blob, &blob_size) == 0) {
            out->diagnostics      = blob;
            out->diagnostics_size = blob_size;
        }
    }
    return out->status;
}

static AuraEngineStatus
ghidra_adapter_request(void                    *adapter_ctx,
                       const AuraEngineRequest *req,
                       AuraEngineResponse      *out)
{
    if (!req || !out) {
        if (out) {
            out->status = AURA_ENGINE_ERR_INVALID;
        }
        return AURA_ENGINE_ERR_INVALID;
    }
    /* The orchestrator zeroes `out` before calling, but the adapter is
     * the contractual owner of body/raw — be explicit. */
    out->type             = req->type;
    out->status           = AURA_ENGINE_ERR_INTERNAL;
    out->body             = NULL;
    out->body_size        = 0;
    out->raw              = NULL;
    out->raw_size         = 0;
    out->diagnostics      = NULL;
    out->diagnostics_size = 0;

    GhidraAdapterCtx *ctx = (GhidraAdapterCtx *)adapter_ctx;

    switch (req->type) {
    case AURA_ENGINE_REQ_DECOMPILE:
        return ghidra_handle_decompile(ctx, req, out);
    case AURA_ENGINE_REQ_ANALYZE:
    case AURA_ENGINE_REQ_DISASM:
    case AURA_ENGINE_REQ_TRACE:
    default:
        /* Phase 2C: only DECOMPILE is in the manifest, so the
         * orchestrator filters non-DECOMPILE requests at routing time
         * (manifest_supports check) and never delivers them here. The
         * default arm exists as defensive coverage in case a stale
         * caller bypasses the orchestrator and invokes the vtable
         * directly. */
        out->status = AURA_ENGINE_ERR_UNSUPPORTED;
        return out->status;
    }
}

static const AuraEngineAdapter g_ghidra_adapter = {
    .init     = ghidra_adapter_init,
    .request  = ghidra_adapter_request,
    .shutdown = ghidra_adapter_shutdown,
};

const AuraEngineAdapter *aura_ghidra_adapter_vtable(void)
{
    return &g_ghidra_adapter;
}

/* ── Registration helper ──────────────────────────────────────────────── */

int aura_orchestrator_register_ghidra(
    AuraOrchestrator                 *orch,
    const AuraGhidraSubprocessConfig *cfg_or_null)
{
    if (!orch) {
        return -1;
    }
    if (cfg_or_null) {
        g_ghidra_pending_cfg = *cfg_or_null;
        g_ghidra_pending_cfg_set = 1;
    } else {
        memset(&g_ghidra_pending_cfg, 0, sizeof(g_ghidra_pending_cfg));
        g_ghidra_pending_cfg_set = 0;
    }
    int rc = aura_orchestrator_register(orch,
                                        aura_ghidra_adapter_manifest(),
                                        aura_ghidra_adapter_vtable());
    if (rc != 0) {
        /* On failure, init() never ran (or ran and reset the slot
         * itself). Either way clear so a retry is clean. */
        memset(&g_ghidra_pending_cfg, 0, sizeof(g_ghidra_pending_cfg));
        g_ghidra_pending_cfg_set = 0;
        AURA_LOG_E("ghidra_adapter: register failed (rc=%d)", rc);
    }
    return rc;
}
