/*
 * rizin_adapter.c — AuraEngineAdapter vtable for Rizin (Phase 2A).
 *
 * Pipeline:
 *   request(ANALYZE)
 *     → rizin_subprocess (resolve exec, run bulk command)
 *     → rizin_snapshot   (framing + cJSON + canonical)
 *     → rizin_to_aura    (canonical → AuraRecordCollection)
 *     → flatten records into a single contiguous body blob
 *   raw = stdout buffer (R-4)
 *
 * Per R-10, this file is the only place the canonical / snapshot / hub
 * are bound together; the public header (include/rizin_adapter.h) only
 * exposes engine-neutral types + the body schema.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_adapter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "logger.h"
#include "rizin_command_set.h"
#include "rizin_decompile_caps.h"
#include "rizin_decompile_normalize.h"
#include "rizin_disasm_normalize.h"
#include "rizin_framing.h"
#include "rizin_snapshot.h"
#include "rizin_subprocess.h"
#include "rizin_to_aura.h"

/* ── manifest ────────────────────────────────────────────────────────── */

/* The manifest advertises the adapter's *compile-time* capability set.
 * DECOMPILE is enumerated here because the adapter ships the wiring; at
 * dispatch time we additionally consult per-instance caps detected via
 * `aura_rizin_detect_decompile_caps` to surface ERR_UNSUPPORTED when no
 * rz-ghidra/jsdec plugin is installed in the runtime rizin. This split
 * matches the orchestrator pattern (manifest = potential, runtime = actual). */
static const AuraEngineManifest g_rizin_manifest = {
    .engine_id        = "rizin",
    .version          = "0.7+",
    .exec_path        = NULL, /* resolved per-call by rizin_subprocess */
    .supported_types  = (1u << AURA_ENGINE_REQ_DISASM)
                      | (1u << AURA_ENGINE_REQ_ANALYZE)
                      | (1u << AURA_ENGINE_REQ_DECOMPILE),
    .capability_flags = AURA_ENGINE_CAP_NONE,
};

const AuraEngineManifest *aura_rizin_adapter_manifest(void)
{
    return &g_rizin_manifest;
}

/* ── pending cfg (set by register_rizin, consumed by init) ───────────── */

static AuraRizinAdapterConfig g_pending_cfg;
static int                    g_pending_cfg_set = 0;

typedef struct RizinAdapterCtx {
    AuraRizinAdapterConfig cfg;
    int                    has_cfg;
    /* Phase 2B.4: lazy decompile capability cache. We avoid running
     * detect_caps in init() so analyze-only consumers don't pay a
     * subprocess on adapter load. Filled on first DECOMPILE request. */
    AuraRizinDecompileCaps caps;
    int                    caps_detected;
} RizinAdapterCtx;

/* ── body accessors ──────────────────────────────────────────────────── */

/* Compute byte offset of each array within the body blob. */
#define BODY_OFF_FUNCTIONS  (sizeof(AuraRizinAnalyzeBody))
#define BODY_OFF_SYMBOLS(b) (BODY_OFF_FUNCTIONS + (b)->functions_count * sizeof(AuraFunctionRecord))
#define BODY_OFF_BLOCKS(b)  (BODY_OFF_SYMBOLS(b) + (b)->symbols_count * sizeof(AuraSymbolRecord))
#define BODY_OFF_EDGES(b)   (BODY_OFF_BLOCKS(b) + (b)->blocks_count * sizeof(AuraBlockRecord))
#define BODY_OFF_VARS(b)    (BODY_OFF_EDGES(b) + (b)->edges_count * sizeof(AuraEdgeRecord))
#define BODY_OFF_TFACTS(b)  (BODY_OFF_VARS(b) + (b)->variables_count * sizeof(AuraVariableRecord))
#define BODY_OFF_CALLEDGES(b) (BODY_OFF_TFACTS(b) + (b)->type_facts_count * sizeof(AuraTypeFactRecord))
#define BODY_OFF_XREFS(b)   (BODY_OFF_CALLEDGES(b) + (b)->call_edges_count * sizeof(AuraCallEdgeRecord))
#define BODY_OFF_STRINGS(b) (BODY_OFF_XREFS(b) + (b)->xrefs_count * sizeof(AuraXrefRecord))

static const char *body_base(const AuraRizinAnalyzeBody *b)
{
    return (const char *)b;
}

const AuraFunctionRecord *
aura_rizin_analyze_body_functions(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->functions_count == 0) return NULL;
    return (const AuraFunctionRecord *)(body_base(b) + BODY_OFF_FUNCTIONS);
}

const AuraSymbolRecord *
aura_rizin_analyze_body_symbols(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->symbols_count == 0) return NULL;
    return (const AuraSymbolRecord *)(body_base(b) + BODY_OFF_SYMBOLS(b));
}

const AuraBlockRecord *
aura_rizin_analyze_body_blocks(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->blocks_count == 0) return NULL;
    return (const AuraBlockRecord *)(body_base(b) + BODY_OFF_BLOCKS(b));
}

const AuraEdgeRecord *
aura_rizin_analyze_body_edges(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->edges_count == 0) return NULL;
    return (const AuraEdgeRecord *)(body_base(b) + BODY_OFF_EDGES(b));
}

const AuraVariableRecord *
aura_rizin_analyze_body_variables(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->variables_count == 0) return NULL;
    return (const AuraVariableRecord *)(body_base(b) + BODY_OFF_VARS(b));
}

const AuraTypeFactRecord *
aura_rizin_analyze_body_type_facts(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->type_facts_count == 0) return NULL;
    return (const AuraTypeFactRecord *)(body_base(b) + BODY_OFF_TFACTS(b));
}

const AuraCallEdgeRecord *
aura_rizin_analyze_body_call_edges(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->call_edges_count == 0) return NULL;
    return (const AuraCallEdgeRecord *)(body_base(b) + BODY_OFF_CALLEDGES(b));
}

const AuraXrefRecord *
aura_rizin_analyze_body_xrefs(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->xrefs_count == 0) return NULL;
    return (const AuraXrefRecord *)(body_base(b) + BODY_OFF_XREFS(b));
}

const AuraStringRecord *
aura_rizin_analyze_body_strings(const AuraRizinAnalyzeBody *b)
{
    if (!b || b->magic != AURA_RIZIN_ANALYZE_BODY_MAGIC) return NULL;
    if (b->version < 3u) return NULL;
    if (b->strings_count == 0) return NULL;
    return (const AuraStringRecord *)(body_base(b) + BODY_OFF_STRINGS(b));
}

/* ── Phase 2B decompile body accessors ───────────────────────────────── */

#define DEC_ALIGN8(n) (((n) + 7u) & ~(size_t)7u)

const char *aura_rizin_decompile_body_text(const AuraRizinDecompileBody *b)
{
    if (!b || b->magic != AURA_RIZIN_DECOMPILE_BODY_MAGIC) return "";
    return (const char *)(b + 1);
}

const AuraRizinDecompileLineMap *
aura_rizin_decompile_body_line_map(const AuraRizinDecompileBody *b)
{
    if (!b || b->magic != AURA_RIZIN_DECOMPILE_BODY_MAGIC) return NULL;
    if (b->line_map_count == 0) return NULL;
    size_t off = sizeof(*b) + b->body_text_len + 1u; /* include NUL */
    off = DEC_ALIGN8(off);
    return (const AuraRizinDecompileLineMap *)((const char *)b + off);
}

const char *aura_rizin_decompile_backend_source(uint32_t backend)
{
    switch (backend) {
    case AURA_RIZIN_DEC_BACKEND_PDGJ: return "rizin/pdgj";
    case AURA_RIZIN_DEC_BACKEND_PDDJ: return "rizin/pddj";
    case AURA_RIZIN_DEC_BACKEND_PDD:  return "rizin/pdd";
    case AURA_RIZIN_DEC_BACKEND_PDF:  return "rizin/pdf";
    default:                          return "";
    }
}

/* ── Phase 11.3.7 (P2.F2) disassembly body accessor ──────────────────── */

const AuraInstructionRecord *
aura_rizin_disasm_body_instructions(const AuraRizinDisasmBody *b)
{
    if (!b || b->magic != AURA_RIZIN_DISASM_BODY_MAGIC) return NULL;
    if (b->instructions_count == 0) return NULL;
    return (const AuraInstructionRecord *)((const char *)b + sizeof(*b));
}

const char *
aura_rizin_disasm_body_text(const AuraRizinDisasmBody *b)
{
    if (!b || b->magic != AURA_RIZIN_DISASM_BODY_MAGIC) return NULL;
    if (b->version < 2u || b->text_size == 0) return NULL;
    /* Layout: header → instructions[] → text[]. */
    const char *base = (const char *)b + sizeof(*b)
                     + b->instructions_count * sizeof(AuraInstructionRecord);
    return base;
}

static AuraRizinAnalyzeBody *
flatten_collection(const AuraRecordCollection *col, size_t *out_size)
{
    size_t fcount  = aura_records_function_count(col);
    size_t scount  = aura_records_symbol_count(col);
    size_t blcount = aura_records_block_count(col);
    size_t ecount  = aura_records_edge_count(col);
    size_t vcount  = aura_records_variable_count(col);
    size_t tfcount = aura_records_type_fact_count(col);
    size_t cecount = aura_records_call_edge_count(col);
    size_t xrcount = aura_records_xref_count(col);
    size_t stcount = aura_records_string_count(col);

    AuraRizinAnalyzeBody hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.magic            = AURA_RIZIN_ANALYZE_BODY_MAGIC;
    hdr.version          = AURA_RIZIN_ANALYZE_BODY_VERSION;
    hdr.functions_count  = fcount;
    hdr.symbols_count    = scount;
    hdr.blocks_count     = blcount;
    hdr.edges_count      = ecount;
    hdr.variables_count  = vcount;
    hdr.type_facts_count = tfcount;
    hdr.call_edges_count = cecount;
    hdr.xrefs_count      = xrcount;
    hdr.strings_count    = stcount;

    size_t total = BODY_OFF_STRINGS(&hdr) + stcount * sizeof(AuraStringRecord);
    AuraRizinAnalyzeBody *body = (AuraRizinAnalyzeBody *)malloc(total);
    if (!body) return NULL;
    *body = hdr;

    { AuraFunctionRecord  *d = (AuraFunctionRecord *) ((char *)body + BODY_OFF_FUNCTIONS);
      for (size_t i = 0; i < fcount;  ++i) { const AuraFunctionRecord  *s = aura_records_function_at (col,i); if(s) d[i]=*s; } }
    { AuraSymbolRecord    *d = (AuraSymbolRecord *)   ((char *)body + BODY_OFF_SYMBOLS(body));
      for (size_t i = 0; i < scount;  ++i) { const AuraSymbolRecord    *s = aura_records_symbol_at   (col,i); if(s) d[i]=*s; } }
    { AuraBlockRecord     *d = (AuraBlockRecord *)    ((char *)body + BODY_OFF_BLOCKS(body));
      for (size_t i = 0; i < blcount; ++i) { const AuraBlockRecord     *s = aura_records_block_at    (col,i); if(s) d[i]=*s; } }
    { AuraEdgeRecord      *d = (AuraEdgeRecord *)     ((char *)body + BODY_OFF_EDGES(body));
      for (size_t i = 0; i < ecount;  ++i) { const AuraEdgeRecord      *s = aura_records_edge_at     (col,i); if(s) d[i]=*s; } }
    { AuraVariableRecord  *d = (AuraVariableRecord *) ((char *)body + BODY_OFF_VARS(body));
      for (size_t i = 0; i < vcount;  ++i) { const AuraVariableRecord  *s = aura_records_variable_at (col,i); if(s) d[i]=*s; } }
    { AuraTypeFactRecord  *d = (AuraTypeFactRecord *) ((char *)body + BODY_OFF_TFACTS(body));
      for (size_t i = 0; i < tfcount; ++i) { const AuraTypeFactRecord  *s = aura_records_type_fact_at(col,i); if(s) d[i]=*s; } }
    { AuraCallEdgeRecord  *d = (AuraCallEdgeRecord *) ((char *)body + BODY_OFF_CALLEDGES(body));
      for (size_t i = 0; i < cecount; ++i) { const AuraCallEdgeRecord  *s = aura_records_call_edge_at(col,i); if(s) d[i]=*s; } }
    { AuraXrefRecord      *d = (AuraXrefRecord *)     ((char *)body + BODY_OFF_XREFS(body));
      for (size_t i = 0; i < xrcount; ++i) { const AuraXrefRecord      *s = aura_records_xref_at     (col,i); if(s) d[i]=*s; } }
    { AuraStringRecord    *d = (AuraStringRecord *)   ((char *)body + BODY_OFF_STRINGS(body));
      for (size_t i = 0; i < stcount; ++i) { const AuraStringRecord    *s = aura_records_string_at   (col,i); if(s) d[i]=*s; } }

    *out_size = total;
    return body;
}

/* ── status mapping ──────────────────────────────────────────────────── */

static AuraEngineStatus map_sub_status(AuraRizinSubStatus s)
{
    switch (s) {
    case AURA_RIZIN_SUB_OK:           return AURA_ENGINE_OK;
    case AURA_RIZIN_SUB_ERR_NOT_FOUND:return AURA_ENGINE_ERR_NOT_FOUND;
    case AURA_RIZIN_SUB_ERR_TIMEOUT:  return AURA_ENGINE_ERR_TIMEOUT;
    case AURA_RIZIN_SUB_ERR_CRASH:    return AURA_ENGINE_ERR_CRASH;
    case AURA_RIZIN_SUB_ERR_INVALID:  return AURA_ENGINE_ERR_INVALID;
    case AURA_RIZIN_SUB_ERR_SPAWN:
    case AURA_RIZIN_SUB_ERR_INTERNAL:
    default:                          return AURA_ENGINE_ERR_INTERNAL;
    }
}

/* ── vtable: init / request / shutdown ───────────────────────────────── */

static int rizin_adapter_init(void **ctx_out)
{
    if (!ctx_out) return -1;
    RizinAdapterCtx *c = (RizinAdapterCtx *)calloc(1, sizeof(*c));
    if (!c) return -1;
    if (g_pending_cfg_set) {
        c->cfg     = g_pending_cfg;
        c->has_cfg = 1;
        g_pending_cfg_set = 0;
        memset(&g_pending_cfg, 0, sizeof(g_pending_cfg));
    }
    *ctx_out = c;
    return 0;
}

static void rizin_adapter_shutdown(void *ctx)
{
    free(ctx);
}

/* ── length-aware growable byte buffer ───────────────────────────────── */

typedef struct {
    char  *data;
    size_t len;
    size_t cap;
} ByteBuf;

static int bytebuf_append(ByteBuf *b, const char *src, size_t n)
{
    if (n == 0) return 0;
    if (b->len + n + 1u > b->cap) {
        size_t nc = b->cap ? b->cap * 2u : 4096u;
        while (nc < b->len + n + 1u) nc *= 2u;
        char *p = (char *)realloc(b->data, nc);
        if (!p) return -1;
        b->data = p;
        b->cap  = nc;
    }
    memcpy(b->data + b->len, src, n);
    b->len += n;
    b->data[b->len] = '\0'; /* convenience NUL, not source of truth */
    return 0;
}

static void bytebuf_free(ByteBuf *b)
{
    free(b->data);
    memset(b, 0, sizeof(*b));
}

/* ── subprocess helper ───────────────────────────────────────────────── */

static AuraRizinSubStatus run_subprocess(RizinAdapterCtx *ctx,
                                          const char *binary_path,
                                          const char *commands,
                                          ByteBuf    *stdout_out)
{
    AuraRizinSubRequest sreq;
    memset(&sreq, 0, sizeof(sreq));
    sreq.exec_path_override = (ctx && ctx->has_cfg) ? ctx->cfg.exec_path : NULL;
    sreq.binary_path        = binary_path;
    sreq.commands           = commands;
    sreq.timeout_s          = (ctx && ctx->has_cfg) ? ctx->cfg.timeout_s : 0;

    AuraRizinSubResult sres;
    AuraRizinSubStatus ss = aura_rizin_sub_run(&sreq, &sres);

    if (sres.stdout_buf && sres.stdout_len > 0) {
        /* Append to length-aware buffer (A-3: no strlen/strcat). */
        if (bytebuf_append(stdout_out, sres.stdout_buf, sres.stdout_len) != 0)
            ss = AURA_RIZIN_SUB_ERR_INTERNAL;
    }
    aura_rizin_sub_result_free(&sres);
    return ss;
}

/* ── 2-pass analyze ──────────────────────────────────────────────────── */

static AuraEngineStatus
handle_analyze(RizinAdapterCtx          *ctx,
               const AuraEngineRequest  *req,
               AuraEngineResponse       *out)
{
    if (!req->binary_path || !*req->binary_path)
        return AURA_ENGINE_ERR_INVALID;

    ByteBuf combined;
    memset(&combined, 0, sizeof(combined));

    /* ── Pass 1: global analyze (Phase 11.3 ADR-0035 — aa/aaa/aaaa) ─── */
    char *global_cmds =
        aura_rizin_cmd_build_analyze_global_with_level(req->analysis_level);
    if (!global_cmds) {
        AURA_LOG_E("rizin_adapter: global command build failed");
        return AURA_ENGINE_ERR_INTERNAL;
    }
    AuraRizinSubStatus ss = run_subprocess(ctx, req->binary_path,
                                            global_cmds, &combined);
    free(global_cmds);

    if (ss != AURA_RIZIN_SUB_OK) {
        bytebuf_free(&combined);
        return map_sub_status(ss);
    }

    /* Parse global stdout to extract function entry addresses. */
    AuraRizinFullSnapshot snap1;
    AuraRizinSnapshotStatus snst = aura_rizin_snapshot_parse(
        combined.data, combined.len, &snap1);
    if (snst != AURA_RIZIN_SNAPSHOT_OK) {
        aura_rizin_full_snapshot_free(&snap1);
        bytebuf_free(&combined);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* Collect function entry addresses as hex strings. */
    size_t fn_count = snap1.canonical.functions_count;
    const char **addr_list = NULL;
    char (*addr_bufs)[22] = NULL; /* "0x" + 16 hex digits + NUL */
    if (fn_count > 0) {
        addr_list = (const char **)calloc(fn_count, sizeof(const char *));
        addr_bufs = (char (*)[22])calloc(fn_count, 22u);
        if (!addr_list || !addr_bufs) {
            free(addr_list); free(addr_bufs);
            aura_rizin_full_snapshot_free(&snap1);
            bytebuf_free(&combined);
            return AURA_ENGINE_ERR_INTERNAL;
        }
        size_t valid = 0;
        for (size_t i = 0; i < fn_count; ++i) {
            uint64_t entry = snap1.canonical.functions[i].offset;
            int n = snprintf(addr_bufs[valid], 22u, "0x%llx",
                             (unsigned long long)entry);
            if (n > 0 && n < 22 &&
                aura_rizin_cmd_addr_hex_valid(addr_bufs[valid])) {
                addr_list[valid] = addr_bufs[valid];
                ++valid;
            }
        }
        fn_count = valid;
    }
    aura_rizin_full_snapshot_free(&snap1);

    /* ── Pass 2: per-function batch (only when functions found) ─────── */
    if (fn_count > 0) {
        /* Separate the two stdouts with a newline so framing lines align. */
        if (bytebuf_append(&combined, "\n", 1) != 0) {
            free(addr_list); free(addr_bufs);
            bytebuf_free(&combined);
            return AURA_ENGINE_ERR_INTERNAL;
        }
        char *pfn_cmds = aura_rizin_cmd_build_per_function_batch_with_analysis(
            addr_list, fn_count);
        free(addr_list);
        free(addr_bufs);

        if (!pfn_cmds) {
            bytebuf_free(&combined);
            return AURA_ENGINE_ERR_INTERNAL;
        }
        ss = run_subprocess(ctx, req->binary_path, pfn_cmds, &combined);
        free(pfn_cmds);

        if (ss != AURA_RIZIN_SUB_OK) {
            /* Non-fatal: per-function data unavailable; proceed with global. */
            AURA_LOG_E("rizin_adapter: per-function subprocess failed, continuing");
        }
    } else {
        free(addr_list);
        free(addr_bufs);
    }

    /* R-4: preserve raw combined stdout. */
    out->raw      = combined.data;
    out->raw_size = combined.len;
    combined.data = NULL; /* ownership transferred */

    /* ── Parse merged buffer ─────────────────────────────────────────── */
    AuraRizinFullSnapshot snap;
    snst = aura_rizin_snapshot_parse(
        (const char *)out->raw, out->raw_size, &snap);
    if (snst != AURA_RIZIN_SNAPSHOT_OK) {
        aura_rizin_full_snapshot_free(&snap);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* Hub: canonical → normalized records. */
    AuraRecordCollection *col = aura_records_create();
    if (!col) {
        aura_rizin_full_snapshot_free(&snap);
        return AURA_ENGINE_ERR_INTERNAL;
    }
    AuraRizinHubStatus hst = aura_rizin_to_aura_normalize(&snap.canonical, col);
    if (hst != AURA_RIZIN_HUB_OK) {
        aura_records_destroy(col);
        aura_rizin_full_snapshot_free(&snap);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* Flatten into body blob. */
    size_t body_size = 0;
    AuraRizinAnalyzeBody *body = flatten_collection(col, &body_size);
    aura_records_destroy(col);
    aura_rizin_full_snapshot_free(&snap);

    if (!body) return AURA_ENGINE_ERR_INTERNAL;
    out->body      = body;
    out->body_size = body_size;
    return AURA_ENGINE_OK;
}

/* ── Phase 2B.4: lazy decompile-capability detection ─────────────────── */

/* Run detect_caps once per adapter context, cache result. The subprocess
 * call goes through `rizin_subprocess` which honours the same exec_path
 * resolution as the analyze path. Returns 0 on OK (caps populated, may
 * be all-zero if no plugins installed); non-zero on hard subprocess
 * failure (rizin missing, spawn error).
 *
 * `probe_binary_path` is reused as the rizin argv binary — caps depend
 * only on the rizin install (`Lc` enumerates loaded plugins), not on
 * the loaded binary, so we can piggy-back on whatever the caller is
 * already going to decompile. This avoids the chicken-and-egg of needing
 * a portable empty fixture present at the runtime CWD. */
static int ensure_caps(RizinAdapterCtx *ctx, const char *probe_binary_path)
{
    if (!ctx) return -1;
    if (ctx->caps_detected) return 0;
    if (!probe_binary_path || !*probe_binary_path) return -1;

    const char *exec_path = (ctx->has_cfg) ? ctx->cfg.exec_path : NULL;
    int rc = aura_rizin_detect_decompile_caps(
        exec_path, probe_binary_path, &ctx->caps);
    ctx->caps_detected = 1;
    if (rc != 0) {
        /* Non-zero return is a subprocess-layer issue (NOT_FOUND etc.).
         * Treat as "no decompile backend" — caps already zeroed. */
        memset(&ctx->caps, 0, sizeof(ctx->caps));
    }
    return 0;
}

/* ── Phase 2B.4: DECOMPILE request handler ───────────────────────────── */

/* Convert hex addr to "0x%llx" string suitable for the cmd builder. */
static int format_addr_hex(uint64_t addr, char *out, size_t cap)
{
    int n = snprintf(out, cap, "0x%llx", (unsigned long long)addr);
    return (n > 0 && (size_t)n < cap) ? 0 : -1;
}

/* Find the first frame whose base id matches `base`. Returns NULL if
 * no such frame exists. */
static const AuraRizinFrame *
find_frame_by_base(const AuraRizinSnapshot *snap, const char *base)
{
    if (!snap || !base) return NULL;
    for (size_t i = 0; i < snap->frame_count; ++i) {
        AuraRizinCmdIdParts parts;
        if (!aura_rizin_command_id_parse(snap->frames[i].command_id, &parts))
            continue;
        if (strcmp(parts.base, base) == 0) return &snap->frames[i];
    }
    return NULL;
}

static AuraEngineStatus
handle_decompile(RizinAdapterCtx          *ctx,
                 const AuraEngineRequest  *req,
                 AuraEngineResponse       *out)
{
    if (!req->binary_path || !*req->binary_path)
        return AURA_ENGINE_ERR_INVALID;
    /* addr == 0 is a valid request (entry of a freshly-loaded binary
     * may genuinely be at offset 0 in some embeddings); we don't treat
     * 0 as "missing". The CLI is responsible for surfacing required-arg
     * UX. */

    /* 1) Capability gate: detect once (using the request's own binary as
     *    the rizin probe), fail fast when nothing installed. */
    if (ensure_caps(ctx, req->binary_path) != 0)
        return AURA_ENGINE_ERR_INTERNAL;
    AuraRizinDecompileBackend backend =
        aura_rizin_decompile_select_backend(&ctx->caps);
    /* Phase 11.3.1.1: select_backend now returns PDF as ultimate fallback
     * (base Rizin always available), so NONE is never expected. Defensive
     * check kept for future enum extensions. */
    if (backend == AURA_RIZIN_DEC_NONE) {
        AURA_LOG_E("rizin_adapter: no decompile backend selected "
                   "(unexpected — PDF fallback should be unconditional)");
        return AURA_ENGINE_ERR_UNSUPPORTED;
    }

    /* 2) Build the bulk command (aaa + framed pdgj/pddj/pdd @ addr). */
    char addr_hex[22];
    if (format_addr_hex(req->addr, addr_hex, sizeof(addr_hex)) != 0)
        return AURA_ENGINE_ERR_INVALID;
    char *bulk = aura_rizin_cmd_build_decompile(backend, addr_hex);
    if (!bulk) return AURA_ENGINE_ERR_INVALID;

    /* 3) Run subprocess. */
    ByteBuf combined;
    memset(&combined, 0, sizeof(combined));
    AuraRizinSubStatus ss = run_subprocess(ctx, req->binary_path, bulk,
                                            &combined);
    free(bulk);
    if (ss != AURA_RIZIN_SUB_OK) {
        bytebuf_free(&combined);
        return map_sub_status(ss);
    }

    /* R-4: preserve raw combined stdout regardless of parse outcome. */
    out->raw      = combined.data;
    out->raw_size = combined.len;
    /* combined.data ownership transferred to response; clear pointer so
     * bytebuf_free is a no-op. */
    char  *raw_ptr = combined.data;
    size_t raw_len = combined.len;
    combined.data  = NULL; combined.len = 0; combined.cap = 0;

    /* 4) Frame-parse the stdout (aaa + decompile frames). */
    AuraRizinSnapshot snap;
    AuraRizinFrameStatus fs = aura_rizin_frame_parse(raw_ptr, raw_len, &snap);
    if (fs != AURA_RIZIN_FRAME_OK) {
        aura_rizin_snapshot_free(&snap);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* 5) Locate the decompile frame for the chosen backend. */
    const char *base = AURA_RIZIN_DECOMPILE_CMDS[backend];
    const AuraRizinFrame *dec_frame = find_frame_by_base(&snap, base);
    if (!dec_frame) {
        aura_rizin_snapshot_free(&snap);
        AURA_LOG_E("rizin_adapter: decompile frame %s missing in stdout", base);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* 6) Backend-specific normalize. */
    AuraRizinDecompileBody *body = NULL;
    AuraRizinDecompileNormStatus ns;

    if (backend == AURA_RIZIN_DEC_PDGJ || backend == AURA_RIZIN_DEC_PDDJ) {
        /* JSON parse the frame body (raw_json view; not NUL-terminated —
         * cJSON_ParseWithLength handles len). */
        cJSON *root = cJSON_ParseWithLength(dec_frame->raw_json,
                                              dec_frame->raw_json_len);
        if (!root) {
            aura_rizin_snapshot_free(&snap);
            AURA_LOG_E("rizin_adapter: %s JSON parse failed", base);
            return AURA_ENGINE_ERR_INTERNAL;
        }
        ns = aura_rizin_decompile_normalize(
            backend, req->addr, root, NULL, 0, &body);
        cJSON_Delete(root);
    } else {
        /* PDD (jsdec text fallback) and PDF (base disasm fallback) both
         * take the raw frame body as text passthrough. */
        ns = aura_rizin_decompile_normalize(
            backend, req->addr, NULL,
            dec_frame->raw_json, dec_frame->raw_json_len, &body);
    }

    aura_rizin_snapshot_free(&snap);

    if (ns != AURA_RIZIN_DEC_NORM_OK || !body) {
        return AURA_ENGINE_ERR_INTERNAL;
    }

    out->body      = body;
    out->body_size = sizeof(*body) + body->body_text_len + 1u
                     + body->line_map_count
                       * sizeof(AuraRizinDecompileLineMap);
    return AURA_ENGINE_OK;
}

/* ── Phase 11.3.4 batch decompile (single subprocess, N bodies) ──────── */

int aura_rizin_decompile_batch_run(
    const char            *exec_path,
    const char            *binary_path,
    const uint64_t        *addr_list,
    size_t                 n,
    int                    timeout_s,
    AuraRizinDecompileBody **out_bodies,
    uint32_t              *out_backend)
{
    if (!binary_path || !addr_list || n == 0 || !out_bodies) return -1;
    for (size_t i = 0; i < n; ++i) out_bodies[i] = NULL;

    /* Caps detection: best-effort. select_backend always returns at
     * least PDF (Phase 11.3.1.1 fallback). */
    AuraRizinDecompileCaps caps;
    memset(&caps, 0, sizeof(caps));
    aura_rizin_detect_decompile_caps(exec_path, binary_path, &caps);
    AuraRizinDecompileBackend backend =
        aura_rizin_decompile_select_backend(&caps);
    if (out_backend) *out_backend = (uint32_t)backend;

    /* Build address-hex list. */
    char **hex_list = (char **)calloc(n, sizeof(char *));
    if (!hex_list) return -1;
    for (size_t i = 0; i < n; ++i) {
        char buf[22];
        if (format_addr_hex(addr_list[i], buf, sizeof(buf)) != 0) goto fail_hex;
        hex_list[i] = strdup(buf);
        if (!hex_list[i]) goto fail_hex;
    }
    char *bulk = aura_rizin_cmd_build_decompile_batch(
        backend, (const char *const *)hex_list, n);
    /* hex_list strings are no longer needed once bulk is built. */
    for (size_t i = 0; i < n; ++i) free(hex_list[i]);
    free(hex_list);
    hex_list = NULL;
    if (!bulk) return -1;

    /* Run subprocess. */
    AuraRizinSubRequest req = {0};
    req.exec_path_override = exec_path;
    req.binary_path        = binary_path;
    req.commands           = bulk;
    req.timeout_s          = (timeout_s > 0) ? timeout_s : 60;
    AuraRizinSubResult res = {0};
    AuraRizinSubStatus ss = aura_rizin_sub_run(&req, &res);
    free(bulk);
    if (ss != AURA_RIZIN_SUB_OK) {
        aura_rizin_sub_result_free(&res);
        return -1;
    }

    /* Frame-parse. */
    AuraRizinSnapshot snap;
    AuraRizinFrameStatus fs = aura_rizin_frame_parse(
        res.stdout_buf, res.stdout_len, &snap);
    aura_rizin_sub_result_free(&res);
    if (fs != AURA_RIZIN_FRAME_OK) {
        aura_rizin_snapshot_free(&snap);
        return -1;
    }

    /* For each frame whose base == backend cmd, normalize into the
     * matching addr slot. */
    const char *base = AURA_RIZIN_DECOMPILE_CMDS[backend];
    for (size_t fi = 0; fi < snap.frame_count; ++fi) {
        AuraRizinCmdIdParts parts;
        if (!aura_rizin_command_id_parse(snap.frames[fi].command_id, &parts))
            continue;
        if (strcmp(parts.base, base) != 0) continue;
        if (!parts.has_addr) continue;
        /* Locate the matching slot. */
        size_t slot = (size_t)-1;
        for (size_t i = 0; i < n; ++i) {
            if (addr_list[i] == parts.addr) { slot = i; break; }
        }
        if (slot == (size_t)-1) continue;
        if (out_bodies[slot]) continue;  /* already filled (dup) */

        AuraRizinDecompileBody *body = NULL;
        AuraRizinDecompileNormStatus ns;
        if (backend == AURA_RIZIN_DEC_PDGJ || backend == AURA_RIZIN_DEC_PDDJ) {
            cJSON *root = cJSON_ParseWithLength(
                snap.frames[fi].raw_json, snap.frames[fi].raw_json_len);
            if (!root) continue;
            ns = aura_rizin_decompile_normalize(
                backend, parts.addr, root, NULL, 0, &body);
            cJSON_Delete(root);
        } else {
            ns = aura_rizin_decompile_normalize(
                backend, parts.addr, NULL,
                snap.frames[fi].raw_json,
                snap.frames[fi].raw_json_len, &body);
        }
        if (ns == AURA_RIZIN_DEC_NORM_OK && body) {
            out_bodies[slot] = body;
        }
    }

    aura_rizin_snapshot_free(&snap);
    return 0;

fail_hex:
    if (hex_list) {
        for (size_t i = 0; i < n; ++i) free(hex_list[i]);
        free(hex_list);
    }
    return -1;
}

/* ── Phase 11.3.7 (P2.F2 C2): per-function disassembly ─────────────────── */

static AuraRizinDisasmBody *
make_disasm_text_body(uint64_t addr, const char *text, size_t text_len)
{
    const size_t text_size = text_len + 1u;
    const size_t total = sizeof(AuraRizinDisasmBody) + text_size;
    AuraRizinDisasmBody *body = (AuraRizinDisasmBody *)calloc(1, total);
    if (!body) return NULL;

    body->magic = AURA_RIZIN_DISASM_BODY_MAGIC;
    body->version = AURA_RIZIN_DISASM_BODY_VERSION;
    body->function_addr = addr;
    body->instructions_count = 0u;
    body->text_size = text_size;

    char *dst = (char *)body + sizeof(*body);
    if (text && text_len > 0u) memcpy(dst, text, text_len);
    dst[text_len] = '\0';
    return body;
}

static AuraEngineStatus
handle_disasm(RizinAdapterCtx          *ctx,
              const AuraEngineRequest  *req,
              AuraEngineResponse       *out)
{
    if (!req->binary_path || !*req->binary_path)
        return AURA_ENGINE_ERR_INVALID;

    const AuraRizinDisasmOptions *opts = NULL;
    if (req->payload && req->payload_size >= sizeof(AuraRizinDisasmOptions)) {
        opts = (const AuraRizinDisasmOptions *)req->payload;
    }
    const int window_mode =
        opts && opts->mode == AURA_RIZIN_DISASM_MODE_WINDOW;
    const int text_range_mode =
        opts && opts->mode == AURA_RIZIN_DISASM_MODE_TEXT_RANGE;
    unsigned window_count = opts ? opts->instruction_count : 0u;
    if (window_mode) {
        if (window_count == 0u) window_count = 96u;
        if (window_count > 512u) window_count = 512u;
    }
    unsigned byte_count = opts ? opts->byte_count : 0u;
    if (text_range_mode) {
        if (byte_count == 0u) byte_count = 4096u;
        if (byte_count > 4096u) byte_count = 4096u;
    }

    /* 1) Build the bulk command. Function mode uses pdfj/pdf; structured
     * full-window mode uses pdj; Cutter-style overview mode uses pD text. */
    char addr_hex[22];
    if (format_addr_hex(req->addr, addr_hex, sizeof(addr_hex)) != 0)
        return AURA_ENGINE_ERR_INVALID;
    char *bulk = NULL;
    if (text_range_mode) {
        bulk = aura_rizin_cmd_build_disasm_text_range(addr_hex, byte_count);
    } else if (window_mode) {
        bulk = aura_rizin_cmd_build_disasm_window(addr_hex, window_count);
    } else {
        bulk = aura_rizin_cmd_build_disasm(addr_hex);
    }
    if (!bulk) return AURA_ENGINE_ERR_INVALID;

    /* 2) Run subprocess. */
    ByteBuf combined;
    memset(&combined, 0, sizeof(combined));
    AuraRizinSubStatus ss = run_subprocess(ctx, req->binary_path, bulk,
                                            &combined);
    free(bulk);
    if (ss != AURA_RIZIN_SUB_OK) {
        bytebuf_free(&combined);
        return map_sub_status(ss);
    }

    /* R-4: preserve raw combined stdout regardless of parse outcome. */
    out->raw      = combined.data;
    out->raw_size = combined.len;
    char  *raw_ptr = combined.data;
    size_t raw_len = combined.len;
    combined.data  = NULL; combined.len = 0; combined.cap = 0;

    /* 3) Frame-parse the stdout (aaa + disasm frames). */
    AuraRizinSnapshot snap;
    AuraRizinFrameStatus fs = aura_rizin_frame_parse(raw_ptr, raw_len, &snap);
    if (fs != AURA_RIZIN_FRAME_OK) {
        aura_rizin_snapshot_free(&snap);
        return AURA_ENGINE_ERR_INTERNAL;
    }

    if (text_range_mode) {
        const AuraRizinFrame *tf = find_frame_by_base(&snap, "pDtext");
        if (!tf) {
            aura_rizin_snapshot_free(&snap);
            AURA_LOG_E("rizin_adapter: pD text frame missing in stdout");
            return AURA_ENGINE_ERR_INTERNAL;
        }
        AuraRizinDisasmBody *body =
            make_disasm_text_body(req->addr, tf->raw_json, tf->raw_json_len);
        aura_rizin_snapshot_free(&snap);
        if (!body) return AURA_ENGINE_ERR_INTERNAL;
        out->body = body;
        out->body_size = sizeof(*body) + body->text_size;
        return AURA_ENGINE_OK;
    }

    /* 4) Locate the JSON disassembly frame. */
    const AuraRizinFrame *df =
        find_frame_by_base(&snap, window_mode ? "pdj" : "pdfj");
    if (!df) {
        aura_rizin_snapshot_free(&snap);
        AURA_LOG_E("rizin_adapter: disasm JSON frame missing in stdout");
        return AURA_ENGINE_ERR_INTERNAL;
    }

    /* Phase 11.6 T1 + Full Disassembly: locate annotated disasm text.
     * Function mode uses `pdf`; full-window mode uses bounded `pD`.
     * Optional — older Rizin or future schema-shape variations may omit it.
     */
    const AuraRizinFrame *df_text =
        find_frame_by_base(&snap, window_mode ? "pDtext" : "pdftext");

    /* 5) cJSON parse + normalize → AuraRizinDisasmBody. */
    cJSON *root = cJSON_ParseWithLength(df->raw_json, df->raw_json_len);
    if (!root) {
        aura_rizin_snapshot_free(&snap);
        AURA_LOG_E("rizin_adapter: pdfj JSON parse failed");
        return AURA_ENGINE_ERR_INTERNAL;
    }
    const char *text_ptr = NULL;
    size_t      text_len = 0;
    if (df_text && df_text->raw_json && df_text->raw_json_len > 0) {
        text_ptr = df_text->raw_json;
        text_len = df_text->raw_json_len;
    }
    AuraRizinDisasmBody *body = NULL;
    AuraRizinDisasmNormStatus ns =
        aura_rizin_disasm_normalize(req->addr, root,
                                    text_ptr, text_len, &body);
    cJSON_Delete(root);
    aura_rizin_snapshot_free(&snap);

    if (ns != AURA_RIZIN_DISASM_NORM_OK || !body) {
        return AURA_ENGINE_ERR_INTERNAL;
    }

    out->body      = body;
    out->body_size = sizeof(*body)
                   + body->instructions_count * sizeof(AuraInstructionRecord)
                   + body->text_size;
    return AURA_ENGINE_OK;
}

static AuraEngineStatus
rizin_adapter_request(void                    *adapter_ctx,
                      const AuraEngineRequest *req,
                      AuraEngineResponse      *out)
{
    if (!out) return AURA_ENGINE_ERR_INVALID;
    memset(out, 0, sizeof(*out));
    if (!req) return AURA_ENGINE_ERR_INVALID;
    out->type = req->type;

    AuraEngineStatus st;
    switch (req->type) {
    case AURA_ENGINE_REQ_ANALYZE:
        st = handle_analyze((RizinAdapterCtx *)adapter_ctx, req, out);
        break;
    case AURA_ENGINE_REQ_DECOMPILE:
        st = handle_decompile((RizinAdapterCtx *)adapter_ctx, req, out);
        break;
    case AURA_ENGINE_REQ_DISASM:
        st = handle_disasm((RizinAdapterCtx *)adapter_ctx, req, out);
        break;
    default:
        st = AURA_ENGINE_ERR_UNSUPPORTED;
        break;
    }
    out->status = st;
    return st;
}

static const AuraEngineAdapter g_rizin_vtable = {
    .init     = rizin_adapter_init,
    .request  = rizin_adapter_request,
    .shutdown = rizin_adapter_shutdown,
};

const AuraEngineAdapter *aura_rizin_adapter_vtable(void)
{
    return &g_rizin_vtable;
}

/* ── registration ────────────────────────────────────────────────────── */

int aura_orchestrator_register_rizin(
    AuraOrchestrator             *orch,
    const AuraRizinAdapterConfig *cfg_or_null)
{
    if (cfg_or_null) {
        g_pending_cfg     = *cfg_or_null;
        g_pending_cfg_set = 1;
    } else {
        memset(&g_pending_cfg, 0, sizeof(g_pending_cfg));
        g_pending_cfg_set = 0;
    }
    return aura_orchestrator_register(orch,
                                       aura_rizin_adapter_manifest(),
                                       aura_rizin_adapter_vtable());
}
