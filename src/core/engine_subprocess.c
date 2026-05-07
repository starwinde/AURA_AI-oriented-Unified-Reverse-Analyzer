/*
 * engine_subprocess.c — Engine-agnostic subprocess primitive (Phase 1.1).
 *
 * Dual-platform: POSIX (posix_spawn + poll loop) and Windows (CreateProcessW
 * + anonymous pipes + drain worker threads).  Both paths expose the same
 * public API declared in engine_subprocess.h.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif

#include "engine_subprocess.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AURA_ENGINE_SUBPROC_DEFAULT_TIMEOUT_S 30
#define AURA_ENGINE_SUBPROC_DRAIN_BUF         4096

/* ── shared helpers (both platforms) ──────────────────────────────────── */

static int append_buf(char **dst, size_t *cap, size_t *len,
                      const char *src, size_t n)
{
    size_t need = *len + n + 1;
    if (need > *cap) {
        size_t new_cap = (*cap == 0 ? 4096 : *cap * 2);
        while (new_cap < need) new_cap *= 2;
        char *nb = (char *)realloc(*dst, new_cap);
        if (!nb) return -1;
        *dst = nb;
        *cap = new_cap;
    }
    memcpy(*dst + *len, src, n);
    *len += n;
    (*dst)[*len] = '\0';
    return 0;
}

static int count_strv(const char *const *v)
{
    int n = 0;
    if (!v) return 0;
    while (v[n]) ++n;
    return n;
}

/* ── public: result_free ─────────────────────────────────────────────── */

void aura_engine_subproc_result_free(AuraEngineSubprocResult *result)
{
    if (!result) return;
    free(result->stdout_buf);
    free(result->stderr_buf);
    result->stdout_buf = NULL;
    result->stderr_buf = NULL;
    result->stdout_len = 0;
    result->stderr_len = 0;
}

/* ══════════════════════════════════════════════════════════════════════
 * Windows implementation (CreateProcessW)
 * ══════════════════════════════════════════════════════════════════════ */
#ifdef _WIN32

#include <windows.h>

/* Convert UTF-8 string to heap-allocated UTF-16. Caller frees. */
static wchar_t *utf8_to_wide(const char *s)
{
    if (!s) return NULL;
    int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if (n <= 0) return NULL;
    wchar_t *w = (wchar_t *)malloc((size_t)n * sizeof(wchar_t));
    if (!w) return NULL;
    MultiByteToWideChar(CP_UTF8, 0, s, -1, w, n);
    return w;
}

/* Quote one argv token per the Windows command-line escaping rules.
 * Only wraps in double quotes when the token contains spaces, tabs,
 * double quotes, or is empty — otherwise returns a plain copy.
 * Caller frees the returned string. */
static char *win_quote_arg(const char *arg)
{
    /* Check whether quoting is necessary */
    int needs_q = (*arg == '\0');
    for (const char *p = arg; *p && !needs_q; ++p) {
        if (*p == ' ' || *p == '\t' || *p == '"' || *p == '\n') needs_q = 1;
    }
    if (!needs_q) {
        size_t n = strlen(arg);
        char *out = (char *)malloc(n + 1);
        if (!out) return NULL;
        memcpy(out, arg, n + 1);
        return out;
    }

    size_t slen = strlen(arg);
    /* Worst case: every char is a backslash preceding a closing " → 2×. */
    char *out = (char *)malloc(slen * 2 + 4);
    if (!out) return NULL;
    char *q = out;
    *q++ = '"';
    int bslash = 0;
    for (const char *p = arg; *p; ++p) {
        if (*p == '\\') {
            *q++ = '\\';
            bslash++;
        } else if (*p == '"') {
            for (int i = 0; i < bslash; ++i) *q++ = '\\'; /* double preceding \ */
            *q++ = '\\';
            *q++ = '"';
            bslash = 0;
        } else {
            bslash = 0;
            *q++ = *p;
        }
    }
    for (int i = 0; i < bslash; ++i) *q++ = '\\'; /* double trailing \ */
    *q++ = '"';
    *q   = '\0';
    return out;
}

/* Build a single Windows command-line string from a NULL-terminated argv.
 * Caller frees the returned string. */
static char *build_cmdline(const char *const *argv)
{
    int argc = count_strv(argv);
    if (argc < 1) return NULL;

    char **quoted = (char **)calloc((size_t)argc, sizeof(char *));
    if (!quoted) return NULL;

    size_t total = 1; /* NUL */
    for (int i = 0; i < argc; ++i) {
        quoted[i] = win_quote_arg(argv[i]);
        if (!quoted[i]) {
            for (int j = 0; j < i; ++j) free(quoted[j]);
            free(quoted);
            return NULL;
        }
        total += strlen(quoted[i]) + (i + 1 < argc ? 1 : 0); /* +1 for space */
    }

    char *cmdline = (char *)malloc(total);
    if (!cmdline) {
        for (int i = 0; i < argc; ++i) free(quoted[i]);
        free(quoted);
        return NULL;
    }
    char *p = cmdline;
    for (int i = 0; i < argc; ++i) {
        size_t qlen = strlen(quoted[i]);
        memcpy(p, quoted[i], qlen);
        p += qlen;
        if (i + 1 < argc) *p++ = ' ';
        free(quoted[i]);
    }
    *p = '\0';
    free(quoted);
    return cmdline;
}

/* Build a UTF-16 environment block that merges the parent's environment
 * with envp_extra ("KEY=VALUE" overrides; case-insensitive KEY match).
 * Block format: KEY=VALUE\0 ... \0\0.  Caller frees. */
static wchar_t *build_env_block_w(const char *const *envp_extra)
{
    wchar_t *parent = GetEnvironmentStringsW();
    if (!parent) return NULL;

    /* Count parent entries */
    size_t pcnt = 0;
    { const wchar_t *p = parent; while (*p) { pcnt++; p += wcslen(p) + 1; } }

    int ecnt = count_strv(envp_extra);

    /* Arrays of pointers into (or replacing) parent entries */
    wchar_t **ent   = (wchar_t **)calloc(pcnt + (size_t)ecnt + 1, sizeof(wchar_t *));
    int      *owned = (int       *)calloc(pcnt + (size_t)ecnt + 1, sizeof(int));
    if (!ent || !owned) {
        free(ent); free(owned);
        FreeEnvironmentStringsW(parent);
        return NULL;
    }

    /* Fill with parent entries (pointers into the block — not owned) */
    size_t nent = 0;
    { const wchar_t *p = parent; while (*p) { ent[nent++] = (wchar_t *)p; p += wcslen(p) + 1; } }

    /* Apply envp_extra: override existing key or append */
    for (int i = 0; i < ecnt; ++i) {
        wchar_t *we = utf8_to_wide(envp_extra[i]);
        if (!we) {
            for (size_t j = 0; j < nent; ++j) if (owned[j]) free(ent[j]);
            free(ent); free(owned); FreeEnvironmentStringsW(parent);
            return NULL;
        }
        const wchar_t *eq  = wcschr(we, L'=');
        size_t         klen = eq ? (size_t)(eq - we) : wcslen(we);

        int found = 0;
        for (size_t j = 0; j < nent; ++j) {
            const wchar_t *jeq  = wcschr(ent[j], L'=');
            size_t         jklen = jeq ? (size_t)(jeq - ent[j]) : wcslen(ent[j]);
            if (jklen == klen && _wcsnicmp(ent[j], we, klen) == 0) {
                if (owned[j]) free(ent[j]);
                ent[j] = we; owned[j] = 1; found = 1; break;
            }
        }
        if (!found) { ent[nent] = we; owned[nent] = 1; nent++; }
    }

    /* Serialize to double-NUL block */
    size_t total = 1; /* final NUL */
    for (size_t i = 0; i < nent; ++i) total += wcslen(ent[i]) + 1;

    wchar_t *block = (wchar_t *)malloc(total * sizeof(wchar_t));
    if (block) {
        wchar_t *q = block;
        for (size_t i = 0; i < nent; ++i) {
            size_t el = wcslen(ent[i]);
            memcpy(q, ent[i], (el + 1) * sizeof(wchar_t));
            q += el + 1;
        }
        *q = L'\0';
    }

    for (size_t i = 0; i < nent; ++i) if (owned[i]) free(ent[i]);
    free(ent); free(owned);
    FreeEnvironmentStringsW(parent);
    return block; /* NULL iff malloc failed */
}

/* ── drain worker thread ──────────────────────────────────────────────── */

typedef struct {
    HANDLE  pipe_r;
    char   *buf;
    size_t  cap;
    size_t  len;
    int     oom;
} DrainCtx;

static DWORD WINAPI drain_thread(LPVOID param)
{
    DrainCtx *ctx = (DrainCtx *)param;
    char tmp[AURA_ENGINE_SUBPROC_DRAIN_BUF];
    DWORD nread;
    while (ReadFile(ctx->pipe_r, tmp, (DWORD)sizeof tmp, &nread, NULL) && nread > 0) {
        if (append_buf(&ctx->buf, &ctx->cap, &ctx->len, tmp, (size_t)nread) != 0) {
            ctx->oom = 1;
            break;
        }
    }
    return 0;
}

/* ── Windows aura_engine_subproc_run ─────────────────────────────────── */

AuraEngineSubprocStatus aura_engine_subproc_run(
    const AuraEngineSubprocConfig *cfg,
    AuraEngineSubprocResult       *result)
{
    if (!result) return AURA_ENGINE_SUBPROC_ERR_INTERNAL;
    memset(result, 0, sizeof *result);

    if (!cfg || !cfg->argv || !cfg->argv[0]) {
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }

    /* Build UTF-16 command line */
    char *cmdline8 = build_cmdline(cfg->argv);
    if (!cmdline8) {
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }
    wchar_t *wcmdline = utf8_to_wide(cmdline8);
    free(cmdline8);
    if (!wcmdline) {
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }

    /* Build environment block (A-4) */
    wchar_t *env_block = NULL;
    DWORD    creation_flags = CREATE_NO_WINDOW;
    if (cfg->envp_extra) {
        env_block = build_env_block_w(cfg->envp_extra);
        if (!env_block) {
            free(wcmdline);
            result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
            return result->status;
        }
        creation_flags |= CREATE_UNICODE_ENVIRONMENT;
    }

    /* Create anonymous pipes for stdout and stderr.
     * bInheritHandle = TRUE so write ends are inherited by child. */
    SECURITY_ATTRIBUTES sa;
    sa.nLength              = sizeof sa;
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle       = TRUE;

    HANDLE hOutR = NULL, hOutW = NULL;
    HANDLE hErrR = NULL, hErrW = NULL;
    if (!CreatePipe(&hOutR, &hOutW, &sa, 0) ||
        !CreatePipe(&hErrR, &hErrW, &sa, 0)) {
        if (hOutR) CloseHandle(hOutR); if (hOutW) CloseHandle(hOutW);
        if (hErrR) CloseHandle(hErrR); if (hErrW) CloseHandle(hErrW);
        free(wcmdline); free(env_block);
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }
    /* Read ends must NOT be inherited by child */
    SetHandleInformation(hOutR, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(hErrR, HANDLE_FLAG_INHERIT, 0);

    /* Open NUL device for child stdin (equivalent to /dev/null) */
    HANDLE hNul = CreateFileW(L"NUL", GENERIC_READ,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              &sa, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);

    STARTUPINFOW si;
    memset(&si, 0, sizeof si);
    si.cb          = sizeof si;
    si.dwFlags     = STARTF_USESTDHANDLES;
    si.hStdInput   = (hNul != INVALID_HANDLE_VALUE) ? hNul : NULL;
    si.hStdOutput  = hOutW;
    si.hStdError   = hErrW;

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof pi);

    BOOL ok = CreateProcessW(NULL, wcmdline, NULL, NULL,
                             TRUE,           /* bInheritHandles */
                             creation_flags, /* CREATE_NO_WINDOW [+ UNICODE_ENV] */
                             env_block, NULL, &si, &pi);
    free(wcmdline);
    free(env_block);

    /* Parent closes the write ends immediately (signals EOF to drain threads
     * once the child has also closed its copies). */
    if (hNul  != INVALID_HANDLE_VALUE) CloseHandle(hNul);
    CloseHandle(hOutW);
    CloseHandle(hErrW);

    if (!ok) {
        CloseHandle(hOutR); CloseHandle(hErrR);
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }
    CloseHandle(pi.hThread); /* we only need pi.hProcess */

    /* Start drain threads */
    DrainCtx out_ctx = { hOutR, NULL, 0, 0, 0 };
    DrainCtx err_ctx = { hErrR, NULL, 0, 0, 0 };
    HANDLE tOut = CreateThread(NULL, 0, drain_thread, &out_ctx, 0, NULL);
    HANDLE tErr = CreateThread(NULL, 0, drain_thread, &err_ctx, 0, NULL);

    /* Wait for child */
    int default_to = (cfg->default_timeout_s > 0)
        ? cfg->default_timeout_s : AURA_ENGINE_SUBPROC_DEFAULT_TIMEOUT_S;
    int timeout_s = (cfg->timeout_s == 0) ? default_to : cfg->timeout_s;
    DWORD timeout_ms = (timeout_s < 0) ? INFINITE : (DWORD)((unsigned)timeout_s * 1000u);

    int timed_out = 0;
    if (WaitForSingleObject(pi.hProcess, timeout_ms) == WAIT_TIMEOUT) {
        timed_out = 1;
        TerminateProcess(pi.hProcess, 1u);
        WaitForSingleObject(pi.hProcess, 1000); /* 1 s grace */
    }

    /* Join drain threads (they see EOF once child is gone) */
    if (tOut) { WaitForSingleObject(tOut, INFINITE); CloseHandle(tOut); }
    if (tErr) { WaitForSingleObject(tErr, INFINITE); CloseHandle(tErr); }
    CloseHandle(hOutR);
    CloseHandle(hErrR);

    DWORD exit_code = 0;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    CloseHandle(pi.hProcess);

    /* Preserve stderr on all paths so adapters can surface diagnostics */
    if (err_ctx.len > 0) {
        result->stderr_buf = err_ctx.buf;
        result->stderr_len = err_ctx.len;
    } else {
        free(err_ctx.buf);
    }

    if (out_ctx.oom || err_ctx.oom) {
        free(out_ctx.buf);
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }
    if (timed_out) {
        free(out_ctx.buf);
        result->status = AURA_ENGINE_SUBPROC_ERR_TIMEOUT;
        return result->status;
    }

    if (out_ctx.len > 0) {
        result->stdout_buf = out_ctx.buf;
        result->stdout_len = out_ctx.len;
    } else {
        free(out_ctx.buf);
    }
    result->exit_code = (int)exit_code;
    result->status    = AURA_ENGINE_SUBPROC_OK;
    return result->status;
}

/* ══════════════════════════════════════════════════════════════════════
 * POSIX implementation (posix_spawn + poll loop)
 * ══════════════════════════════════════════════════════════════════════ */
#else /* !_WIN32 */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <spawn.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

extern char **environ;

/* Build envp = environ + envp_extra entries (strings not copied;
 * the helper does not own them). Returns NULL on allocation failure. */
static char **build_envp(const char *const *envp_extra)
{
    int n_env   = count_strv((const char *const *)environ);
    int n_extra = count_strv(envp_extra);

    char **envp = (char **)calloc((size_t)(n_env + n_extra + 1), sizeof(char *));
    if (!envp) return NULL;

    for (int i = 0; i < n_env;   ++i) envp[i] = environ[i];
    for (int i = 0; i < n_extra; ++i) envp[n_env + i] = (char *)envp_extra[i];
    envp[n_env + n_extra] = NULL;
    return envp;
}

AuraEngineSubprocStatus aura_engine_subproc_run(
    const AuraEngineSubprocConfig *cfg,
    AuraEngineSubprocResult       *result)
{
    if (!result) return AURA_ENGINE_SUBPROC_ERR_INTERNAL;
    memset(result, 0, sizeof *result);

    if (!cfg || !cfg->argv || !cfg->argv[0]) {
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }

    int argc = count_strv(cfg->argv);
    if (argc < 1) {
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }
    char **argv = (char **)calloc((size_t)(argc + 1), sizeof(char *));
    if (!argv) {
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }
    for (int i = 0; i < argc; ++i) argv[i] = (char *)cfg->argv[i];
    argv[argc] = NULL;

    char **envp = build_envp(cfg->envp_extra);
    if (!envp) {
        free(argv);
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }

    int outpipe[2] = {-1, -1};
    int errpipe[2] = {-1, -1};
    int devnull = -1;
    if (pipe(outpipe) != 0 || pipe(errpipe) != 0 ||
        (devnull = open("/dev/null", O_RDONLY)) < 0) {
        if (outpipe[0] >= 0) { close(outpipe[0]); close(outpipe[1]); }
        if (errpipe[0] >= 0) { close(errpipe[0]); close(errpipe[1]); }
        free(envp); free(argv);
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }

    posix_spawn_file_actions_t fa;
    posix_spawn_file_actions_init(&fa);
    posix_spawn_file_actions_adddup2(&fa, devnull,     STDIN_FILENO);
    posix_spawn_file_actions_addclose(&fa, devnull);
    posix_spawn_file_actions_adddup2(&fa, outpipe[1],  STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&fa, outpipe[0]);
    posix_spawn_file_actions_addclose(&fa, outpipe[1]);
    posix_spawn_file_actions_adddup2(&fa, errpipe[1],  STDERR_FILENO);
    posix_spawn_file_actions_addclose(&fa, errpipe[0]);
    posix_spawn_file_actions_addclose(&fa, errpipe[1]);

    pid_t pid = -1;
    int   rc  = posix_spawn(&pid, argv[0], &fa, NULL, argv, envp);
    posix_spawn_file_actions_destroy(&fa);

    close(devnull);
    close(outpipe[1]);
    close(errpipe[1]);

    if (rc != 0) {
        close(outpipe[0]); close(errpipe[0]);
        free(envp); free(argv);
        result->status = AURA_ENGINE_SUBPROC_ERR_SPAWN;
        return result->status;
    }

    fcntl(outpipe[0], F_SETFL, O_NONBLOCK);
    fcntl(errpipe[0], F_SETFL, O_NONBLOCK);

    int default_to = (cfg->default_timeout_s > 0)
        ? cfg->default_timeout_s : AURA_ENGINE_SUBPROC_DEFAULT_TIMEOUT_S;
    int    timeout_s = (cfg->timeout_s == 0) ? default_to : cfg->timeout_s;
    time_t deadline  = (timeout_s < 0) ? (time_t)0 : (time(NULL) + timeout_s);

    char  *outbuf = NULL, *errbuf = NULL;
    size_t outcap = 0, outlen = 0;
    size_t errcap = 0, errlen = 0;
    int oom = 0, out_open = 1, err_open = 1, timed_out = 0;
    char tmp[AURA_ENGINE_SUBPROC_DRAIN_BUF];

    while (out_open || err_open) {
        if (timeout_s >= 0 && time(NULL) >= deadline) {
            timed_out = 1;
            kill(pid, SIGTERM);
            struct timespec grace = { 1, 0 };
            nanosleep(&grace, NULL);
            kill(pid, SIGKILL);
            break;
        }
        if (out_open) {
            ssize_t n = read(outpipe[0], tmp, sizeof tmp);
            if (n > 0) { if (append_buf(&outbuf,&outcap,&outlen,tmp,(size_t)n)!=0){oom=1;break;} }
            else if (n == 0) out_open = 0;
        }
        if (err_open) {
            ssize_t n = read(errpipe[0], tmp, sizeof tmp);
            if (n > 0) { if (append_buf(&errbuf,&errcap,&errlen,tmp,(size_t)n)!=0){oom=1;break;} }
            else if (n == 0) err_open = 0;
        }
        struct timespec sleep_ts = { 0, 5L * 1000L * 1000L };
        nanosleep(&sleep_ts, NULL);
    }
    close(outpipe[0]);
    close(errpipe[0]);

    int wait_status = 0;
    if (waitpid(pid, &wait_status, 0) < 0) {
        free(envp); free(argv); free(outbuf); free(errbuf);
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }
    free(envp); free(argv);
    result->wait_status = wait_status;

    if (errlen > 0) { result->stderr_buf = errbuf; result->stderr_len = errlen; }
    else free(errbuf);

    if (oom)       { free(outbuf); result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL; return result->status; }
    if (timed_out) { free(outbuf); result->status = AURA_ENGINE_SUBPROC_ERR_TIMEOUT;  return result->status; }
    if (WIFSIGNALED(wait_status)) {
        free(outbuf);
        result->term_signal = WTERMSIG(wait_status);
        result->status = AURA_ENGINE_SUBPROC_ERR_KILLED;
        return result->status;
    }
    if (!WIFEXITED(wait_status)) {
        free(outbuf);
        result->status = AURA_ENGINE_SUBPROC_ERR_INTERNAL;
        return result->status;
    }

    if (outlen > 0) { result->stdout_buf = outbuf; result->stdout_len = outlen; }
    else free(outbuf);
    result->exit_code = WEXITSTATUS(wait_status);
    result->status    = AURA_ENGINE_SUBPROC_OK;
    return result->status;
}

#endif /* _WIN32 */
