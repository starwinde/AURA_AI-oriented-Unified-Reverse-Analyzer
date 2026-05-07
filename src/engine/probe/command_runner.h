// src/engine/probe/command_runner.h — Phase 2.5
//
// Abstract command runner so probe logic stays decoupled from the actual
// subprocess machinery (or filesystem). Production code wires this to a
// real spawn-and-capture implementation; tests inject a fake to drive
// every probe state without requiring real engine binaries on disk.
//
// Contract:
//   - run(...) returns 0 when the child process spawned successfully
//     (regardless of its exit code, which is in `out->exit_code`).
//   - run(...) returns -1 when the child could not be spawned at all
//     (e.g. ENOENT, permission denied) — `out->exit_code` is set to -1
//     and `out->stderr_buf` may carry a short diagnostic.
//   - args is a NULL-terminated array of C-strings, conventional argv
//     style without a leading program-name slot.

#ifndef AURA_ENGINE_PROBE_COMMAND_RUNNER_H
#define AURA_ENGINE_PROBE_COMMAND_RUNNER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int  exit_code;          /* child exit, or -1 when spawn failed */
    int  timed_out;          /* nonzero when child was killed by timeout */
    char stdout_buf[4096];   /* NUL-terminated, truncated to fit */
    char stderr_buf[4096];   /* NUL-terminated, truncated to fit */
} AuraCommandResult;

struct AuraCommandRunner;

typedef int (*AuraCommandRunFn)(
    struct AuraCommandRunner *self,
    const char               *program,
    const char *const        *args,
    AuraCommandResult        *out);

typedef struct AuraCommandRunner {
    AuraCommandRunFn run;
    void            *state;
} AuraCommandRunner;

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_COMMAND_RUNNER_H */
