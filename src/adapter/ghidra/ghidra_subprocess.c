/*
 * ghidra_subprocess.c — D-29A turn #5 wrapper for vendored aura-decompile.
 *
 * Composes the argv one-shot invocation of aura-decompile, delegates the
 * spawn / drain / timeout / wait lifecycle to the engine-agnostic
 * primitive in src/core/engine_subprocess.c (Phase 1.1), then maps the
 * frozen exit-code contract (0..6) and lifecycle outcomes onto the
 * Ghidra-specific AuraGhidraStatus enum.
 *
 * Strict scope (frozen by plan §"Schema Reality + Verification Scope
 * Amendment"):
 *   - byte capture only; XML normalize / element translation live in
 *     ghidra_xml_normalize.c (turn #6) and ghidra_xml_to_hir.cpp (turn #7).
 *   - timeout enforcement: SIGTERM → 1s grace → SIGKILL (handled by the
 *     shared subprocess primitive).
 *   - exit code mapping: 0..6 from aura-decompile + 100..103 for AURA-side
 *     spawn / timeout / signal / internal errors.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#define _POSIX_C_SOURCE 200809L

#include "ghidra_subprocess.h"

#include "engine_subprocess.h"
#include "ghidra_xml_normalize.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GHIDRA_DEFAULT_TIMEOUT_S 30

/* ── exit-code mapping ─────────────────────────────────────────────────── */

static AuraGhidraStatus map_exit_code(int code)
{
    switch (code) {
    case 0: return AURA_GHIDRA_OK;
    case 1: return AURA_GHIDRA_ERR_ARGV;
    case 2: return AURA_GHIDRA_ERR_LOAD;
    case 3: return AURA_GHIDRA_ERR_ADDR;
    case 4: return AURA_GHIDRA_ERR_ARCH;
    case 5: return AURA_GHIDRA_ERR_DECOMPILE;
    case 6: return AURA_GHIDRA_ERR_IO;
    default: return AURA_GHIDRA_ERR_INTERNAL;
    }
}

/* ── public API ────────────────────────────────────────────────────────── */

void aura_ghidra_decompile_result_free(AuraGhidraDecompileResult *result)
{
    if (!result) return;
    free(result->xml);
    free(result->stderr_log);
    result->xml = NULL;
    result->stderr_log = NULL;
    result->xml_len = 0;
    result->stderr_len = 0;
}

AuraGhidraStatus aura_ghidra_decompile_at(
    const AuraGhidraSubprocessConfig *cfg,
    const char *binary_path,
    uint64_t addr,
    const char *arch_override_or_null,
    AuraGhidraDecompileResult *result)
{
    if (!result) return AURA_GHIDRA_ERR_INTERNAL;
    memset(result, 0, sizeof *result);

    if (!cfg || !cfg->decompile_bin || !binary_path) {
        result->status = AURA_GHIDRA_ERR_SPAWN;
        return AURA_GHIDRA_ERR_SPAWN;
    }

    /* argv composition: minimum 5 mandatory + optional --arch pair. */
    char addr_buf[32];
    snprintf(addr_buf, sizeof addr_buf, "0x%" PRIx64, addr);

    const char *argv[8] = {0};
    int argc = 0;
    argv[argc++] = cfg->decompile_bin;
    argv[argc++] = "--decompile";
    argv[argc++] = binary_path;
    argv[argc++] = "--addr";
    argv[argc++] = addr_buf;
    if (arch_override_or_null) {
        argv[argc++] = "--arch";
        argv[argc++] = arch_override_or_null;
    }
    argv[argc] = NULL;

    /* envp_extra: only the AURA_GHIDRA_* knobs. environ is appended by the
     * primitive itself, so the array stays small and read-only here. */
    char processors_env[1024];
    char sla_env[1024];
    const char *envp_extra[3] = {0};
    int extra_n = 0;
    if (cfg->processors_dir) {
        snprintf(processors_env, sizeof processors_env,
                 "AURA_GHIDRA_PROCESSORS_DIR=%s", cfg->processors_dir);
        envp_extra[extra_n++] = processors_env;
    }
    if (cfg->sla_dir) {
        snprintf(sla_env, sizeof sla_env,
                 "AURA_GHIDRA_SLA_DIR=%s", cfg->sla_dir);
        envp_extra[extra_n++] = sla_env;
    }
    envp_extra[extra_n] = NULL;

    AuraEngineSubprocConfig sp_cfg = {
        .argv              = argv,
        .envp_extra        = (extra_n > 0) ? envp_extra : NULL,
        .timeout_s         = cfg->timeout_s,
        .default_timeout_s = GHIDRA_DEFAULT_TIMEOUT_S,
    };

    AuraEngineSubprocResult sp;
    memset(&sp, 0, sizeof sp);
    AuraEngineSubprocStatus sp_st = aura_engine_subproc_run(&sp_cfg, &sp);
    result->wait_status = sp.wait_status;
    result->term_signal = sp.term_signal;

    /* Always carry stderr through to the caller — the 5-stage log is
     * diagnostic for both success and failure. */
    if (sp.stderr_buf && sp.stderr_len > 0) {
        result->stderr_log = sp.stderr_buf;
        result->stderr_len = sp.stderr_len;
        sp.stderr_buf = NULL; /* ownership transferred */
        sp.stderr_len = 0;
    }

    AuraGhidraStatus mapped = AURA_GHIDRA_ERR_INTERNAL;
    switch (sp_st) {
    case AURA_ENGINE_SUBPROC_ERR_SPAWN:
        mapped = AURA_GHIDRA_ERR_SPAWN;
        break;
    case AURA_ENGINE_SUBPROC_ERR_TIMEOUT:
        mapped = AURA_GHIDRA_ERR_TIMEOUT;
        break;
    case AURA_ENGINE_SUBPROC_ERR_KILLED:
        mapped = AURA_GHIDRA_ERR_KILLED;
        break;
    case AURA_ENGINE_SUBPROC_ERR_INTERNAL:
        mapped = AURA_GHIDRA_ERR_INTERNAL;
        break;
    case AURA_ENGINE_SUBPROC_OK:
        mapped = map_exit_code(sp.exit_code);
        break;
    }

    if (mapped == AURA_GHIDRA_OK) {
        /* Pipe stdout through the byte-level normalize layer (turn #6). */
        AuraXmlNormalizeResult nr;
        AuraXmlNormalizeStatus ns =
            aura_ghidra_xml_normalize(sp.stdout_buf ? sp.stdout_buf : "",
                                      sp.stdout_len, &nr);
        aura_engine_subproc_result_free(&sp);
        if (ns != AURA_XMLN_OK) {
            aura_ghidra_xml_normalize_result_free(&nr);
            result->xml = NULL;
            result->xml_len = 0;
            result->status = AURA_GHIDRA_ERR_IO;
            return AURA_GHIDRA_ERR_IO;
        }
        result->xml = nr.xml;     /* ownership transferred */
        result->xml_len = nr.xml_len;
    } else {
        /* Frozen contract: stdout must not be trusted on non-zero exit /
         * non-OK lifecycle. Discard captured stdout. stderr was already
         * detached above. */
        aura_engine_subproc_result_free(&sp);
        result->xml = NULL;
        result->xml_len = 0;
    }
    result->status = mapped;
    return mapped;
}
