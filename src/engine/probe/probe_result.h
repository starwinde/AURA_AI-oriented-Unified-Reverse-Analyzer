// src/engine/probe/probe_result.h — Phase 2.5
//
// Engine-agnostic probe result types. No dependency on any RE engine
// adapter; safe to build without AURA_ENABLE_RIZIN. See plan §1.1 for
// the full ProbeStatus enum and the ProbeResult contract this module
// exposes incrementally as the TDD slices land.

#ifndef AURA_ENGINE_PROBE_RESULT_H
#define AURA_ENGINE_PROBE_RESULT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AURA_PROBE_AVAILABLE          = 0,
    AURA_PROBE_RUNTIME_MISSING    = 1,
    AURA_PROBE_ENGINE_MISSING     = 2,
    AURA_PROBE_VERSION_MISMATCH   = 3,
    AURA_PROBE_PERMISSION_DENIED  = 4,
    AURA_PROBE_TIMEOUT            = 5,
    AURA_PROBE_UNKNOWN_ERROR      = 6
} AuraProbeStatus;

/* String form of the enum for JSON envelopes / logs.
 * Stable wire identifier: caller must not free the returned pointer. */
const char *aura_probe_status_str(AuraProbeStatus s);

/* Minimal result record carried by Phase 2.5 tracer bullets. Additional
 * fields (install_hint, detected_alternatives, raw_diagnostic) are added
 * by later slices once their behavior tests are written. */
typedef struct {
    AuraProbeStatus status;
    char            engine_id[32];        /* "rizin" / "ghidra-full" / ... */
    char            detected_version[64]; /* parsed version, "" when n/a */
    char            required_runtime[128];/* "Java JRE >= 17" etc., "" for none */
    char            install_hint[256];    /* OS/vendor install hint, "" when n/a */
    /* Plan §1.1 OS-keyed install hint split. Filled per-OS so GUI/CLI
     * can render the command for the user's actual platform without
     * parsing a concatenated string. Empty string when n/a. */
    char            install_hint_linux[256];
    char            install_hint_macos[256];
    char            install_hint_windows[256];
    char            raw_diagnostic[512];  /* truncated stderr / parser fragment, "" when n/a */
    int64_t         probed_at_ms;         /* wall clock at probe time, 0 if unset */
} AuraProbeResult;

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_RESULT_H */
