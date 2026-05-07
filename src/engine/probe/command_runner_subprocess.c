// src/engine/probe/command_runner_subprocess.c — Phase 2.5.1 Slice X.3
//
// Real subprocess implementation of AuraCommandRunner. Cross-platform
// per rules.md §1 (2026-05-05) — Windows + POSIX implementations live
// in the same file behind #ifdef _WIN32. Both branches honor the same
// contract documented in command_runner.h.

#include "command_runner_subprocess.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int timeout_ms;   /* 0 = no timeout */
} SubprocState;

/* Forward decl of the per-OS run shim. */
static int subproc_run(AuraCommandRunner *self,
                       const char        *program,
                       const char *const *args,
                       AuraCommandResult *out);

AuraCommandRunner *aura_command_runner_subprocess_create(int timeout_ms)
{
    AuraCommandRunner *r = (AuraCommandRunner *)calloc(1, sizeof(*r));
    if (!r) return NULL;
    SubprocState *s = (SubprocState *)calloc(1, sizeof(*s));
    if (!s) { free(r); return NULL; }
    s->timeout_ms = timeout_ms;
    r->run        = &subproc_run;
    r->state      = s;
    return r;
}

void aura_command_runner_subprocess_destroy(AuraCommandRunner *runner)
{
    if (!runner) return;
    free(runner->state);
    free(runner);
}

/* ── Shared helpers ───────────────────────────────────────────────── */

static void copy_truncated(char *dst, size_t cap, const char *src, size_t n)
{
    if (cap == 0) return;
    size_t copy = (n < cap - 1) ? n : (cap - 1);
    if (src && copy > 0) memcpy(dst, src, copy);
    dst[copy] = '\0';
}

/* ── Windows implementation ────────────────────────────────────────── */

#ifdef _WIN32

#include <windows.h>

/* Append a properly quoted argument to a growing command-line buffer.
 * Quoting follows the standard MSVC CommandLineToArgvW reverse rules:
 *   - if the arg contains whitespace or quotes, wrap in double quotes
 *   - escape internal `"` as `\"`, and double any backslashes that
 *     immediately precede a `"` (or the closing quote).
 * For our use case (probe argv passing fixed strings), the simple
 * subset is sufficient.
 */
static int needs_quoting(const char *s)
{
    if (!*s) return 1;
    for (const char *p = s; *p; ++p) {
        if (*p == ' ' || *p == '\t' || *p == '"') return 1;
    }
    return 0;
}

static int append_arg(char **buf, size_t *len, size_t *cap, const char *arg)
{
    int quote = needs_quoting(arg);
    size_t need = strlen(arg) + (quote ? 2 : 0) + 8;
    if (*len + need >= *cap) {
        size_t ncap = (*cap == 0) ? 256 : (*cap * 2);
        while (ncap < *len + need) ncap *= 2;
        char *nb = (char *)realloc(*buf, ncap);
        if (!nb) return -1;
        *buf = nb;
        *cap = ncap;
    }
    if (quote) (*buf)[(*len)++] = '"';
    for (const char *p = arg; *p; ++p) {
        if (*p == '"') {
            (*buf)[(*len)++] = '\\';
            (*buf)[(*len)++] = '"';
        } else {
            (*buf)[(*len)++] = *p;
        }
    }
    if (quote) (*buf)[(*len)++] = '"';
    (*buf)[*len] = '\0';
    return 0;
}

static char *build_cmdline(const char *program, const char *const *args)
{
    char *buf = NULL;
    size_t len = 0, cap = 0;
    if (append_arg(&buf, &len, &cap, program) != 0) return NULL;
    if (args) {
        for (size_t i = 0; args[i] != NULL; ++i) {
            if (cap > 0) {
                if (len + 2 >= cap) {
                    size_t ncap = cap * 2;
                    char *nb = (char *)realloc(buf, ncap);
                    if (!nb) { free(buf); return NULL; }
                    buf = nb;
                    cap = ncap;
                }
                buf[len++] = ' ';
                buf[len]   = '\0';
            }
            if (append_arg(&buf, &len, &cap, args[i]) != 0) {
                free(buf);
                return NULL;
            }
        }
    }
    return buf;
}

typedef struct {
    HANDLE h;
    char  *out;
    size_t cap;
} PipeReader;

static DWORD WINAPI pipe_reader_thread(LPVOID param)
{
    PipeReader *r = (PipeReader *)param;
    HANDLE h = r->h;
    char *out = r->out;
    size_t cap = r->cap;
    if (cap == 0) return 0;
    size_t total = 0;
    DWORD got = 0;
    char tmp[1024];
    for (;;) {
        BOOL ok = ReadFile(h, tmp, sizeof(tmp), &got, NULL);
        if (!ok || got == 0) break;
        if (total + 1 < cap) {
            size_t room = cap - 1 - total;
            size_t n = (got < room) ? got : room;
            memcpy(out + total, tmp, n);
            total += n;
        }
    }
    out[total] = '\0';
    return 0;
}

static int subproc_run(AuraCommandRunner *self,
                       const char        *program,
                       const char *const *args,
                       AuraCommandResult *out)
{
    SubprocState *st = (SubprocState *)self->state;
    memset(out, 0, sizeof(*out));
    out->exit_code = -1;

    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
    HANDLE out_r = NULL, out_w = NULL, err_r = NULL, err_w = NULL;

    if (!CreatePipe(&out_r, &out_w, &sa, 0)) {
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "CreatePipe(stdout) failed", 26);
        return -1;
    }
    SetHandleInformation(out_r, HANDLE_FLAG_INHERIT, 0);

    if (!CreatePipe(&err_r, &err_w, &sa, 0)) {
        CloseHandle(out_r); CloseHandle(out_w);
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "CreatePipe(stderr) failed", 26);
        return -1;
    }
    SetHandleInformation(err_r, HANDLE_FLAG_INHERIT, 0);

    char *cmdline = build_cmdline(program, args);
    if (!cmdline) {
        CloseHandle(out_r); CloseHandle(out_w);
        CloseHandle(err_r); CloseHandle(err_w);
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "build_cmdline OOM", 18);
        return -1;
    }

    STARTUPINFOA si;
    memset(&si, 0, sizeof(si));
    si.cb         = sizeof(si);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdOutput = out_w;
    si.hStdError  = err_w;
    si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));

    BOOL ok = CreateProcessA(
        NULL,        /* let CreateProcess parse cmdline */
        cmdline,
        NULL, NULL,
        TRUE,        /* inherit handles */
        CREATE_NO_WINDOW,
        NULL, NULL,
        &si, &pi);

    /* Parent must close its copies of the write ends so child EOF
     * propagates to ReadFile when the child exits. */
    CloseHandle(out_w);
    CloseHandle(err_w);

    if (!ok) {
        DWORD err = GetLastError();
        char msg[128];
        snprintf(msg, sizeof(msg),
                 "CreateProcess failed (GetLastError=%lu)", (unsigned long)err);
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       msg, strlen(msg));
        free(cmdline);
        CloseHandle(out_r);
        CloseHandle(err_r);
        return -1;
    }
    free(cmdline);

    PipeReader out_reader = { out_r, out->stdout_buf, sizeof(out->stdout_buf) };
    PipeReader err_reader = { err_r, out->stderr_buf, sizeof(out->stderr_buf) };
    HANDLE out_thread = CreateThread(NULL, 0, pipe_reader_thread, &out_reader, 0, NULL);
    HANDLE err_thread = CreateThread(NULL, 0, pipe_reader_thread, &err_reader, 0, NULL);
    if (!out_thread || !err_thread) {
        TerminateProcess(pi.hProcess, 1);
        WaitForSingleObject(pi.hProcess, 1000);
        if (out_thread) {
            WaitForSingleObject(out_thread, 1000);
            CloseHandle(out_thread);
        }
        if (err_thread) {
            WaitForSingleObject(err_thread, 1000);
            CloseHandle(err_thread);
        }
        CloseHandle(out_r);
        CloseHandle(err_r);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "CreateThread(pipe reader) failed", 32);
        return -1;
    }

    DWORD wait_ms = (st->timeout_ms > 0) ? (DWORD)st->timeout_ms : INFINITE;
    DWORD waited  = WaitForSingleObject(pi.hProcess, wait_ms);
    if (waited == WAIT_TIMEOUT) {
        TerminateProcess(pi.hProcess, 1);
        WaitForSingleObject(pi.hProcess, 1000);
        out->timed_out = 1;
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "killed by timer", 16);
    } else {
        DWORD code = 0;
        if (GetExitCodeProcess(pi.hProcess, &code)) {
            out->exit_code = (int)code;
        }
    }

    WaitForSingleObject(out_thread, INFINITE);
    WaitForSingleObject(err_thread, INFINITE);
    CloseHandle(out_thread);
    CloseHandle(err_thread);

    if (out->timed_out) {
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "killed by timer", 16);
    }

    CloseHandle(out_r);
    CloseHandle(err_r);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

#else /* POSIX */

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static long now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)(ts.tv_sec * 1000) + (long)(ts.tv_nsec / 1000000);
}

typedef struct {
    int    fd;
    char  *out;
    size_t cap;
    size_t total;
    int    open;
} FdCapture;

static int set_nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static void capture_init(FdCapture *c, int fd, char *out, size_t cap)
{
    c->fd = fd;
    c->out = out;
    c->cap = cap;
    c->total = 0;
    c->open = 1;
    if (cap > 0) out[0] = '\0';
}

static void drain_available(FdCapture *c)
{
    char tmp[1024];
    if (!c->open) return;

    /* Bound the drain at 64 reads per call (≤64 KiB) so a fast
     * producer (e.g. `yes`) cannot starve the surrounding wait
     * loop from re-checking waitpid / deadline. EAGAIN exits
     * earlier; the cap is a fairness floor. */
    for (int i = 0; i < 64; ++i) {
        ssize_t n = read(c->fd, tmp, sizeof(tmp));
        if (n > 0) {
            if (c->cap > 0 && c->total + 1 < c->cap) {
                size_t room = c->cap - 1 - c->total;
                size_t copy = ((size_t)n < room) ? (size_t)n : room;
                memcpy(c->out + c->total, tmp, copy);
                c->total += copy;
                c->out[c->total] = '\0';
            }
            continue;
        }
        if (n == 0) {
            c->open = 0;
            return;
        }
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
            return;
        }
        c->open = 0;
        return;
    }
}

static int subproc_run(AuraCommandRunner *self,
                       const char        *program,
                       const char *const *args,
                       AuraCommandResult *out)
{
    SubprocState *st = (SubprocState *)self->state;
    memset(out, 0, sizeof(*out));
    out->exit_code = -1;

    int out_fds[2], err_fds[2];
    if (pipe(out_fds) != 0) {
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "pipe(stdout) failed", 20);
        return -1;
    }
    if (pipe(err_fds) != 0) {
        close(out_fds[0]); close(out_fds[1]);
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "pipe(stderr) failed", 20);
        return -1;
    }

    /* Build argv with program prepended. */
    size_t nargs = 0;
    if (args) while (args[nargs]) ++nargs;
    char **argv = (char **)calloc(nargs + 2, sizeof(char *));
    if (!argv) {
        close(out_fds[0]); close(out_fds[1]);
        close(err_fds[0]); close(err_fds[1]);
        return -1;
    }
    argv[0] = (char *)program;
    for (size_t i = 0; i < nargs; ++i) argv[i + 1] = (char *)args[i];

    pid_t pid = fork();
    if (pid < 0) {
        free(argv);
        close(out_fds[0]); close(out_fds[1]);
        close(err_fds[0]); close(err_fds[1]);
        return -1;
    }

    if (pid == 0) {
        /* Child */
        dup2(out_fds[1], STDOUT_FILENO);
        dup2(err_fds[1], STDERR_FILENO);
        close(out_fds[0]); close(out_fds[1]);
        close(err_fds[0]); close(err_fds[1]);
        execvp(program, argv);
        /* If we got here, exec failed. */
        _exit(127);
    }

    /* Parent */
    free(argv);
    close(out_fds[1]);
    close(err_fds[1]);
    set_nonblock(out_fds[0]);
    set_nonblock(err_fds[0]);

    long deadline = (st->timeout_ms > 0) ? (now_ms() + st->timeout_ms) : -1;
    int status = 0;
    int reaped = 0;
    FdCapture out_cap;
    FdCapture err_cap;
    capture_init(&out_cap, out_fds[0], out->stdout_buf, sizeof(out->stdout_buf));
    capture_init(&err_cap, err_fds[0], out->stderr_buf, sizeof(out->stderr_buf));

    while (!reaped) {
        drain_available(&out_cap);
        drain_available(&err_cap);

        pid_t r = waitpid(pid, &status, WNOHANG);
        if (r == pid) { reaped = 1; break; }

        long wait_for = -1;
        if (deadline >= 0) {
            wait_for = deadline - now_ms();
            if (wait_for < 0) wait_for = 0;
        }
        /* Cap poll() at 100 ms regardless of deadline so the wait loop
         * can re-check waitpid promptly when the direct child exits but
         * a descendant inherits the pipe (no POLLHUP arrives in that
         * case). Without the cap, poll blocks for the full remaining
         * deadline and the runner falsely times out a child that
         * actually exited cleanly. */
        int poll_ms = 100;
        if (wait_for >= 0 && wait_for < poll_ms) poll_ms = (int)wait_for;
        struct pollfd pfds[2];
        nfds_t nfds = 0;
        if (out_cap.open) {
            pfds[nfds].fd = out_cap.fd;
            pfds[nfds].events = POLLIN | POLLHUP | POLLERR;
            ++nfds;
        }
        if (err_cap.open) {
            pfds[nfds].fd = err_cap.fd;
            pfds[nfds].events = POLLIN | POLLHUP | POLLERR;
            ++nfds;
        }
        if (nfds == 0 && (poll_ms < 0 || poll_ms > 100)) poll_ms = 100;
        int pr = poll((nfds > 0) ? pfds : NULL, nfds, poll_ms);
        if (pr < 0 && errno == EINTR) continue;
        if (pr > 0) {
            drain_available(&out_cap);
            drain_available(&err_cap);
        }

        if (deadline >= 0 && now_ms() >= deadline) {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            out->timed_out = 1;
            reaped = 1;
            break;
        }
    }

    drain_available(&out_cap);
    drain_available(&err_cap);
    if (out->timed_out) {
        copy_truncated(out->stderr_buf, sizeof(out->stderr_buf),
                       "killed by timer", 16);
    }
    close(out_fds[0]);
    close(err_fds[0]);

    if (!out->timed_out) {
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 127) {
                /* execvp failed in the child — treat as spawn failure
                 * so callers map it to ENGINE_MISSING. */
                out->exit_code = -1;
                return -1;
            }
            out->exit_code = code;
        } else {
            out->exit_code = -1;
        }
    }
    return 0;
}

#endif /* _WIN32 */
