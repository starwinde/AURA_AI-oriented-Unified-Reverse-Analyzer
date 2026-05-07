/*
 * rizin_subprocess.c — Rizin argv composition + exec resolution.
 *
 * Stateless: one-shot rizin invocation per call. No persistent
 * subprocess; no librz; no Rizin headers. Bulk commands are passed
 * via `-c`, output collected from stdout. See rizin_subprocess.h.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_subprocess.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine_subprocess.h"
#include "logger.h"

#if defined(_WIN32)
#  define AURA_RIZIN_EXE "rizin.exe"
#  define AURA_PATH_SEP  ';'
#  define AURA_DIR_SEP   '\\'
/* MSVC deprecates POSIX strdup in favour of _strdup. */
#  ifndef strdup
#    define strdup _strdup
#  endif
#else
#  define AURA_RIZIN_EXE "rizin"
#  define AURA_PATH_SEP  ':'
#  define AURA_DIR_SEP   '/'
#endif

/* ── result lifecycle ────────────────────────────────────────────── */

void aura_rizin_sub_result_free(AuraRizinSubResult *r)
{
    if (!r) return;
    free(r->stdout_buf);
    free(r->stderr_buf);
    free(r->resolved_exec);
    r->stdout_buf = NULL;
    r->stderr_buf = NULL;
    r->resolved_exec = NULL;
    r->stdout_len = 0;
    r->stderr_len = 0;
}

/* ── exec path resolution ────────────────────────────────────────── */

static int file_is_executable(const char *path)
{
    if (!path || !*path) return 0;
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    fclose(f);
    return 1;
}

static char *path_join(const char *dir, size_t dir_len, const char *name)
{
    size_t name_len = strlen(name);
    char *out = (char *)malloc(dir_len + 1 + name_len + 1);
    if (!out) return NULL;
    memcpy(out, dir, dir_len);
    out[dir_len] = AURA_DIR_SEP;
    memcpy(out + dir_len + 1, name, name_len);
    out[dir_len + 1 + name_len] = '\0';
    return out;
}

static char *search_path_env(void)
{
    const char *path_env = getenv("PATH");
    if (!path_env || !*path_env) return NULL;

    const char *p = path_env;
    while (*p) {
        const char *q = p;
        while (*q && *q != AURA_PATH_SEP) ++q;
        if (q != p) {
            char *cand = path_join(p, (size_t)(q - p), AURA_RIZIN_EXE);
            if (cand && file_is_executable(cand)) {
                return cand;
            }
            free(cand);
        }
        p = (*q == AURA_PATH_SEP) ? q + 1 : q;
    }
    return NULL;
}

char *aura_rizin_sub_resolve_exec(const char *override)
{
    /* 1. caller override (manifest) */
    if (override && *override && file_is_executable(override)) {
        return strdup(override);
    }
    /* 2. AURA_RIZIN_PATH */
    const char *env = getenv("AURA_RIZIN_PATH");
    if (env && *env && file_is_executable(env)) {
        return strdup(env);
    }
    /* 3. PATH search */
    return search_path_env();
}

/* ── status mapping ──────────────────────────────────────────────── */

static AuraRizinSubStatus map_subproc_status(AuraEngineSubprocStatus s)
{
    switch (s) {
    case AURA_ENGINE_SUBPROC_OK:          return AURA_RIZIN_SUB_OK;
    case AURA_ENGINE_SUBPROC_ERR_TIMEOUT: return AURA_RIZIN_SUB_ERR_TIMEOUT;
    case AURA_ENGINE_SUBPROC_ERR_KILLED:  return AURA_RIZIN_SUB_ERR_CRASH;
    case AURA_ENGINE_SUBPROC_ERR_SPAWN:   return AURA_RIZIN_SUB_ERR_SPAWN;
    case AURA_ENGINE_SUBPROC_ERR_INTERNAL:
    default:                              return AURA_RIZIN_SUB_ERR_INTERNAL;
    }
}

/* ── main entry ──────────────────────────────────────────────────── */

AuraRizinSubStatus aura_rizin_sub_run(const AuraRizinSubRequest *req,
                                      AuraRizinSubResult        *result)
{
    if (!result) return AURA_RIZIN_SUB_ERR_INVALID;
    memset(result, 0, sizeof(*result));

    if (!req || !req->binary_path || !req->commands) {
        result->status = AURA_RIZIN_SUB_ERR_INVALID;
        return result->status;
    }

    char *exec = aura_rizin_sub_resolve_exec(req->exec_path_override);
    if (!exec) {
        AURA_LOG_E("rizin_subprocess: rizin executable not found "
                   "(checked override / AURA_RIZIN_PATH / PATH)");
        result->status = AURA_RIZIN_SUB_ERR_NOT_FOUND;
        return result->status;
    }
    result->resolved_exec = exec;

    /* argv: rizin -q0 -e scr.color=0 -e scr.utf8=0 -c "<commands>" -- <binary>
     *
     * -q : quiet (no banner)
     * -0 : null-terminate output (we ignore but harmless)
     * -e scr.color=0 : strip ANSI color escapes — required so PDF disasm
     *                  output (Phase 11.3.1.1 fallback) renders cleanly
     *                  in plain-text consumers (GUI QPlainTextEdit, JSON
     *                  payloads). All structured outputs (aflj, isj, ...)
     *                  are unaffected since they emit JSON regardless.
     * -e scr.utf8=0  : ASCII-only frame chars (`|` / `+` / `-` instead of
     *                  unicode box drawing) — same rationale.
     * -c : run commands; subsequent positional arg is the binary
     * --  separator avoids a binary path that starts with '-' being
     *     parsed as a flag.
     */
    const char *argv[] = {
        exec,
        "-q",
        "-0",
        "-e", "scr.color=0",
        "-e", "scr.utf8=0",
        "-c", req->commands,
        "--",
        req->binary_path,
        NULL,
    };

    AuraEngineSubprocConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.argv = argv;
    cfg.envp_extra = NULL;
    cfg.timeout_s = req->timeout_s;
    cfg.default_timeout_s = 30;

    AuraEngineSubprocResult sub;
    memset(&sub, 0, sizeof(sub));
    AuraEngineSubprocStatus ss = aura_engine_subproc_run(&cfg, &sub);

    /* Detach the buffers so caller can free via our result_free(). */
    result->stdout_buf = sub.stdout_buf;
    result->stdout_len = sub.stdout_len;
    result->stderr_buf = sub.stderr_buf;
    result->stderr_len = sub.stderr_len;
    result->exit_code  = sub.exit_code;
    result->term_signal = sub.term_signal;
    /* Prevent double-free in aura_engine_subproc_result_free. */
    sub.stdout_buf = NULL;
    sub.stderr_buf = NULL;
    aura_engine_subproc_result_free(&sub);

    result->status = map_subproc_status(ss);

    /* rizin returns non-zero exit codes for parse errors etc. — surface
     * as INTERNAL so the adapter can translate to ERR_INVALID/INTERNAL,
     * but keep stdout/stderr for diagnostics. */
    if (result->status == AURA_RIZIN_SUB_OK && result->exit_code != 0) {
        AURA_LOG_E("rizin_subprocess: exit_code=%d", result->exit_code);
        result->status = AURA_RIZIN_SUB_ERR_INTERNAL;
    }
    return result->status;
}
