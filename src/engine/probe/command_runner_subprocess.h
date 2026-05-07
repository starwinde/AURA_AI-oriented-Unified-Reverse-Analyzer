// src/engine/probe/command_runner_subprocess.h — Phase 2.5.1
//
// Real-process implementation of the AuraCommandRunner contract
// (command_runner.h). Spawns the requested program with the supplied
// argv, captures stdout/stderr into bounded buffers, and reports the
// child's exit code. Cross-platform: POSIX uses pipe+fork+execvp;
// Windows uses CreatePipe+CreateProcess.
//
// Intended for the production `aura --probe-engines` path. Tests
// continue to use the FakeCommandRunner pattern from probe_unit.cpp
// so they stay hermetic — this implementation is exercised by a
// dedicated subprocess_runner_unit suite that drives portable shell
// builtins (`cmd /c echo` on Windows, `/bin/echo` on POSIX).

#ifndef AURA_ENGINE_PROBE_COMMAND_RUNNER_SUBPROCESS_H
#define AURA_ENGINE_PROBE_COMMAND_RUNNER_SUBPROCESS_H

#include "command_runner.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Create a subprocess-backed command runner.
 *
 * timeout_ms: per-call wall-clock budget. The runner kills the child
 *             and reports timed_out=1 + exit_code=-1 when the budget
 *             is exhausted. Pass 0 for "no timeout" (not recommended
 *             for production probes — use 5000 ms by default).
 *
 * Returns NULL on allocation failure. The caller owns the returned
 * pointer and must release it with aura_command_runner_subprocess_destroy.
 */
AuraCommandRunner *aura_command_runner_subprocess_create(int timeout_ms);

/* Release a runner created by aura_command_runner_subprocess_create.
 * Safe on NULL. */
void aura_command_runner_subprocess_destroy(AuraCommandRunner *runner);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_COMMAND_RUNNER_SUBPROCESS_H */
