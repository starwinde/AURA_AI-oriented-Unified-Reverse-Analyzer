/* src/engine/probe/engine_probe.c — Phase 2.5 GREEN.
 *
 * Minimal implementation that satisfies the first two tracer bullets:
 *   1. `rizin -v` exit 0 with stdout "rizin X.Y.Z ..." → AVAILABLE +
 *      detected_version = "X.Y.Z"
 *   2. spawn failure (rizin not on PATH) → ENGINE_MISSING
 *
 * Anything else maps to UNKNOWN_ERROR for now; later slices add
 * VERSION_MISMATCH (parsed but too old), TIMEOUT, PERMISSION_DENIED.
 */

#include "engine_probe.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/* Wall-clock millisecond stamp. time(NULL) is second-resolution but
 * sufficient for "probed_at_ms is set" semantics; later slices can swap
 * in a monotonic / sub-second source without changing the contract. */
static int64_t aura_probe_now_ms(void)
{
    return (int64_t)time(NULL) * 1000;
}

static int probe_file_exists(const char *path)
{
    if (!path || !*path) return 0;
    struct stat st;
    return stat(path, &st) == 0;
}

int aura_probe_resolve_binary(const char *env_var,
                              const char *vendored_rel,
                              const char *default_name,
                              char       *out_buf,
                              size_t      out_cap)
{
    if (!out_buf || out_cap == 0 || !default_name) return 3;
    out_buf[0] = '\0';

    /* 1. env override — highest priority. We do not stat() to validate;
     * if the user set it explicitly, trust them and let the runner
     * surface ENGINE_MISSING on spawn failure. Their explicit choice
     * deserves a clear error rather than a silent fallback. */
    if (env_var) {
        const char *v = getenv(env_var);
        if (v && *v) {
            strncpy(out_buf, v, out_cap - 1);
            out_buf[out_cap - 1] = '\0';
            return 1;
        }
    }

    /* 2. vendored repo path — installed under third_party/<engine>/.
     * AURA_REPO_ROOT must point at the repo root (CLI / test harness
     * sets this). Skip silently when the env is unset OR the file is
     * absent so PATH fallback can run. */
    if (vendored_rel && *vendored_rel) {
        const char *root = getenv("AURA_REPO_ROOT");
        if (root && *root) {
            int n = snprintf(out_buf, out_cap, "%s/%s", root, vendored_rel);
            if (n > 0 && (size_t)n < out_cap && probe_file_exists(out_buf)) {
                return 2;
            }
            out_buf[0] = '\0';
        }
    }

    /* 3. PATH default — single name, OS PATH resolution. */
    strncpy(out_buf, default_name, out_cap - 1);
    out_buf[out_cap - 1] = '\0';
    return 3;
}

const char *aura_probe_status_str(AuraProbeStatus s)
{
    switch (s) {
    case AURA_PROBE_AVAILABLE:         return "AVAILABLE";
    case AURA_PROBE_RUNTIME_MISSING:   return "RUNTIME_MISSING";
    case AURA_PROBE_ENGINE_MISSING:    return "ENGINE_MISSING";
    case AURA_PROBE_VERSION_MISMATCH:  return "VERSION_MISMATCH";
    case AURA_PROBE_PERMISSION_DENIED: return "PERMISSION_DENIED";
    case AURA_PROBE_TIMEOUT:           return "TIMEOUT";
    case AURA_PROBE_UNKNOWN_ERROR:     return "UNKNOWN_ERROR";
    }
    return "UNKNOWN_ERROR";
}

/* Copy at most cap-1 bytes from [start, end) into dst, NUL-terminate. */
static void copy_bounded(char *dst, size_t cap, const char *start, const char *end)
{
    if (cap == 0) return;
    size_t n = (size_t)(end - start);
    if (n >= cap) n = cap - 1;
    memcpy(dst, start, n);
    dst[n] = '\0';
}

/* Extract the version token from a "rizin X.Y.Z ..." line. Returns 1 on
 * success, 0 when no plausible version could be parsed. */
static int parse_rizin_version(const char *stdout_buf, char *out_ver, size_t cap)
{
    if (!stdout_buf || !out_ver || cap == 0) return 0;

    /* Look for the literal "rizin " prefix at the start of any line.
     * The output of `rizin -v` typically begins:
     *     "rizin 0.8.2 @ linux-x86-64 git.0.8.2"
     * but build banners or warnings may precede it on some hosts. */
    const char *needle = "rizin ";
    const size_t needle_len = 6;
    const char *p = stdout_buf;
    const char *hit = NULL;
    while ((p = strstr(p, needle)) != NULL) {
        if (p == stdout_buf || *(p - 1) == '\n' || *(p - 1) == '\r') {
            hit = p;
            break;
        }
        p += needle_len;
    }
    if (!hit) return 0;

    const char *ver_start = hit + needle_len;
    const char *ver_end   = ver_start;
    /* version token = up to first whitespace / NUL */
    while (*ver_end && *ver_end != ' ' && *ver_end != '\t' &&
           *ver_end != '\n' && *ver_end != '\r') {
        ver_end++;
    }
    if (ver_end == ver_start) return 0;

    /* Reject obviously bogus "versions" (no digit at all). */
    int has_digit = 0;
    for (const char *q = ver_start; q < ver_end; ++q) {
        if (*q >= '0' && *q <= '9') { has_digit = 1; break; }
    }
    if (!has_digit) return 0;

    copy_bounded(out_ver, cap, ver_start, ver_end);
    return 1;
}

/* Compare a parsed "X.Y[.Z]" version against the (major, minor) floor.
 * Returns 1 when the parsed version is >= the floor, 0 otherwise.
 * Best-effort: unparseable input yields 0 so callers fall through to
 * the mismatch branch with the diagnostic visible. */
static int version_at_least(const char *ver, int floor_major, int floor_minor)
{
    if (!ver || !*ver) return 0;
    int major = 0;
    const char *p = ver;
    while (*p >= '0' && *p <= '9') { major = major * 10 + (*p - '0'); p++; }
    if (p == ver) return 0;
    int minor = 0;
    if (*p == '.') {
        p++;
        const char *m = p;
        while (*p >= '0' && *p <= '9') { minor = minor * 10 + (*p - '0'); p++; }
        if (p == m) minor = 0;
    }
    if (major != floor_major) return major > floor_major;
    return minor >= floor_minor;
}

int aura_probe_rizin(AuraCommandRunner *runner, AuraProbeResult *out)
{
    if (!runner || !runner->run || !out) return -1;

    memset(out, 0, sizeof(*out));
    strncpy(out->engine_id, "rizin", sizeof(out->engine_id) - 1);
    out->probed_at_ms = aura_probe_now_ms();
    strncpy(out->required_runtime, "rizin >= 0.7",
            sizeof(out->required_runtime) - 1);

    AuraCommandResult cmd;
    memset(&cmd, 0, sizeof(cmd));
    const char *argv[] = { "-v", NULL };
    char rizin_bin[512];
#ifdef _WIN32
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              "third_party/rizin/0.8.2/bin/rizin.exe",
                              "rizin", rizin_bin, sizeof(rizin_bin));
#else
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              "third_party/rizin/0.8.2/bin/rizin",
                              "rizin", rizin_bin, sizeof(rizin_bin));
#endif
    int rc = runner->run(runner, rizin_bin, argv, &cmd);

    if (rc == 0 && cmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (rc != 0 || cmd.exit_code == -1) {
        /* Spawn itself failed → engine binary not on PATH / not on disk. */
        out->status = AURA_PROBE_ENGINE_MISSING;
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (cmd.exit_code != 0) {
        /* Spawned but the command failed; treat as indeterminate for now. */
        out->status = AURA_PROBE_UNKNOWN_ERROR;
        return 0;
    }

    if (parse_rizin_version(cmd.stdout_buf,
                            out->detected_version,
                            sizeof(out->detected_version))) {
        if (version_at_least(out->detected_version, 0, 7)) {
            out->status = AURA_PROBE_AVAILABLE;
        } else {
            out->status = AURA_PROBE_VERSION_MISMATCH;
        }
    } else {
        out->status = AURA_PROBE_UNKNOWN_ERROR;
    }
    return 0;
}

/* Extract a version-like token (first whitespace-delimited run that
 * contains at least one digit) from arbitrary stdout. Returns 1 when
 * a token was copied, 0 otherwise. Generic enough for vendored tools
 * whose `--version` banner format we do not control. */
static int parse_generic_version(const char *stdout_buf,
                                 char *out_ver, size_t cap)
{
    if (!stdout_buf || !out_ver || cap == 0) return 0;

    const char *p = stdout_buf;
    while (*p) {
        /* skip whitespace */
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
        if (!*p) break;

        const char *tok_start = p;
        int has_digit = 0;
        while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            if (*p >= '0' && *p <= '9') has_digit = 1;
            p++;
        }
        if (has_digit) {
            copy_bounded(out_ver, cap, tok_start, p);
            return 1;
        }
    }
    return 0;
}

/* Parse the Java major version from a `java -version` banner.
 * Banner shape: openjdk version "17.0.10" 2024-01-16 ... or
 *               java version "1.8.0_392" ... (legacy 1.x = major 8)
 * Returns the integer major version (>0) on success, 0 on failure.
 * When out_full_version is non-NULL, the full quoted version (e.g.
 * "17.0.10") is copied there. */
static int parse_java_major(const char *banner,
                            char *out_full_version, size_t cap)
{
    if (!banner) return 0;

    /* Find the first quoted version literal: "X.Y.Z..." */
    const char *q1 = strchr(banner, '"');
    if (!q1) return 0;
    const char *q2 = strchr(q1 + 1, '"');
    if (!q2) return 0;

    if (out_full_version && cap > 0) {
        copy_bounded(out_full_version, cap, q1 + 1, q2);
    }

    /* Scan first integer in the quoted token. */
    const char *p = q1 + 1;
    int first = 0;
    while (p < q2 && *p >= '0' && *p <= '9') {
        first = first * 10 + (*p - '0');
        p++;
    }
    if (first == 0) return 0;

    /* Legacy "1.x" → major = x */
    if (first == 1 && p < q2 && *p == '.') {
        p++;
        int second = 0;
        while (p < q2 && *p >= '0' && *p <= '9') {
            second = second * 10 + (*p - '0');
            p++;
        }
        return second > 0 ? second : 1;
    }
    return first;
}

int aura_probe_retdec(AuraCommandRunner *runner, AuraProbeResult *out)
{
    if (!runner || !runner->run || !out) return -1;

    memset(out, 0, sizeof(*out));
    strncpy(out->engine_id, "retdec", sizeof(out->engine_id) - 1);
    out->probed_at_ms = aura_probe_now_ms();

    AuraCommandResult cmd;
    memset(&cmd, 0, sizeof(cmd));
    const char *argv[] = { "--version", NULL };
    char retdec_bin[512];
#ifdef _WIN32
    aura_probe_resolve_binary("AURA_RETDEC_DECOMPILER_BIN",
                              "third_party/retdec/bin/retdec-decompiler.exe",
                              "retdec-decompiler",
                              retdec_bin, sizeof(retdec_bin));
#else
    aura_probe_resolve_binary("AURA_RETDEC_DECOMPILER_BIN",
                              "third_party/retdec/bin/retdec-decompiler",
                              "retdec-decompiler",
                              retdec_bin, sizeof(retdec_bin));
#endif
    int rc = runner->run(runner, retdec_bin, argv, &cmd);

    if (rc == 0 && cmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (rc != 0 || cmd.exit_code == -1) {
        out->status = AURA_PROBE_ENGINE_MISSING;
        strncpy(out->install_hint,
                "expected at third_party/retdec/bin/retdec-decompiler"
                " (build from source or install upstream package)",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "bash scripts/bootstrap_retdec.sh",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "bash scripts/bootstrap_retdec.sh",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "powershell -File scripts\\bootstrap_retdec.ps1",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (cmd.exit_code != 0) {
        out->status = AURA_PROBE_UNKNOWN_ERROR;
        return 0;
    }

    parse_generic_version(cmd.stdout_buf,
                          out->detected_version,
                          sizeof(out->detected_version));
    out->status = AURA_PROBE_AVAILABLE;
    return 0;
}

int aura_probe_angr(AuraCommandRunner *runner, AuraProbeResult *out)
{
    if (!runner || !runner->run || !out) return -1;

    memset(out, 0, sizeof(*out));
    strncpy(out->engine_id, "angr", sizeof(out->engine_id) - 1);
    out->probed_at_ms = aura_probe_now_ms();
    strncpy(out->required_runtime, "Python 3.x with angr >= 9.2",
            sizeof(out->required_runtime) - 1);

    AuraCommandResult cmd;
    memset(&cmd, 0, sizeof(cmd));
    const char *argv[] = {
        "-c", "import angr; print(angr.__version__)", NULL
    };
    /* Lookup priority (Phase 2.5.2):
     *   1. AURA_ANGR_PYTHON_BIN env override
     *   2. vendored third_party/angr/venv/{bin,Scripts}/python(.exe)
     *   3. cross-platform fallback chain (rules.md §1, 2026-05-05) —
     *      Windows tries `python` first, POSIX tries `python3` first.
     */
    char angr_python_bin[512];
#ifdef _WIN32
    int hit = aura_probe_resolve_binary(
        "AURA_ANGR_PYTHON_BIN",
        "third_party/angr/venv/Scripts/python.exe",
        /* default name placeholder; if PATH fallback wins (rc==3),
         * we override it with the OS-preferred fallback chain below. */
        "python",
        angr_python_bin, sizeof(angr_python_bin));
    static const char *const python_candidates[] = { "python", "python3", NULL };
#else
    int hit = aura_probe_resolve_binary(
        "AURA_ANGR_PYTHON_BIN",
        "third_party/angr/venv/bin/python",
        "python3",
        angr_python_bin, sizeof(angr_python_bin));
    static const char *const python_candidates[] = { "python3", "python", NULL };
#endif

    int rc = -1;
    if (hit == 1 || hit == 2) {
        /* Explicit env override or vendored hit — single attempt, no
         * fallback chain. The user / repo state was unambiguous. */
        memset(&cmd, 0, sizeof(cmd));
        rc = runner->run(runner, angr_python_bin, argv, &cmd);
    } else {
        /* PATH fallback — try OS-preferred name first, then alternate. */
        for (int i = 0; python_candidates[i] != NULL; ++i) {
            memset(&cmd, 0, sizeof(cmd));
            rc = runner->run(runner, python_candidates[i], argv, &cmd);
            if (rc == 0) break;
        }
    }

    if (rc == 0 && cmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (rc != 0 || cmd.exit_code == -1) {
        out->status = AURA_PROBE_RUNTIME_MISSING;
        strncpy(out->install_hint,
                "install Python 3.x (Linux: apt install python3;"
                " macOS: brew install python@3.12;"
                " Windows: winget install Python.Python.3.12)",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "sudo apt install python3",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "brew install python@3.12",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "winget install Python.Python.3.12",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (cmd.exit_code != 0) {
        out->status = AURA_PROBE_ENGINE_MISSING;
        strncpy(out->install_hint,
                "angr not importable in selected Python;"
                " run scripts/bootstrap_angr.{sh,ps1} to create"
                " third_party/angr/venv and pip install angr",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "bash scripts/bootstrap_angr.sh",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "bash scripts/bootstrap_angr.sh",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "powershell -File scripts\\bootstrap_angr.ps1",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (parse_generic_version(cmd.stdout_buf,
                              out->detected_version,
                              sizeof(out->detected_version))) {
        if (version_at_least(out->detected_version, 9, 2)) {
            out->status = AURA_PROBE_AVAILABLE;
        } else {
            out->status = AURA_PROBE_VERSION_MISMATCH;
        }
    } else {
        /* No version token visible — surface the binary as available
         * but flag the empty version downstream. */
        out->status = AURA_PROBE_AVAILABLE;
    }
    return 0;
}

int aura_probe_ghidra_full(AuraCommandRunner *runner, AuraProbeResult *out)
{
    if (!runner || !runner->run || !out) return -1;

    memset(out, 0, sizeof(*out));
    strncpy(out->engine_id, "ghidra-full", sizeof(out->engine_id) - 1);
    out->probed_at_ms = aura_probe_now_ms();
    strncpy(out->required_runtime, "Java JRE >= 17",
            sizeof(out->required_runtime) - 1);

    /* Step 1: java -version. AURA_JAVA_BIN env override (vendored
     * JREs are not bundled — Ghidra full requires the host's JRE). */
    AuraCommandResult jcmd;
    memset(&jcmd, 0, sizeof(jcmd));
    const char *jargv[] = { "-version", NULL };
    char java_bin[512];
    aura_probe_resolve_binary("AURA_JAVA_BIN", NULL, "java",
                              java_bin, sizeof(java_bin));
    int jrc = runner->run(runner, java_bin, jargv, &jcmd);

    if (jrc == 0 && jcmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, jcmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (jrc != 0 || jcmd.exit_code == -1) {
        out->status = AURA_PROBE_RUNTIME_MISSING;
        strncpy(out->install_hint,
                "install OpenJDK 17+ (Linux: apt install openjdk-17-jre;"
                " macOS: brew install openjdk@17;"
                " Windows: winget install Microsoft.OpenJDK.17)",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "sudo apt install openjdk-17-jre",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "brew install openjdk@17",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "winget install Microsoft.OpenJDK.17",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, jcmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    /* Java writes -version to stderr; some distros mirror to stdout. */
    const char *banner = jcmd.stderr_buf[0] ? jcmd.stderr_buf
                                            : jcmd.stdout_buf;
    int major = parse_java_major(banner,
                                 out->detected_version,
                                 sizeof(out->detected_version));
    if (major == 0 || major < 17) {
        out->status = AURA_PROBE_RUNTIME_MISSING;
        strncpy(out->install_hint,
                "found Java but major version < 17;"
                " upgrade to OpenJDK 17+ for Ghidra full",
                sizeof(out->install_hint) - 1);
        return 0;
    }

    /* Step 2: analyzeHeadless -help.
     * Lookup priority:
     *   1. AURA_GHIDRA_FULL_ANALYZE_HEADLESS env override
     *   2. vendored third_party/ghidra-full/support/analyzeHeadless(.bat)
     *   3. PATH fallback */
    AuraCommandResult acmd;
    memset(&acmd, 0, sizeof(acmd));
    const char *aargv[] = { "-help", NULL };
    char ah_bin[512];
#ifdef _WIN32
    aura_probe_resolve_binary(
        "AURA_GHIDRA_FULL_ANALYZE_HEADLESS",
        "third_party/ghidra-full/support/analyzeHeadless.bat",
        "analyzeHeadless", ah_bin, sizeof(ah_bin));
#else
    aura_probe_resolve_binary(
        "AURA_GHIDRA_FULL_ANALYZE_HEADLESS",
        "third_party/ghidra-full/support/analyzeHeadless",
        "analyzeHeadless", ah_bin, sizeof(ah_bin));
#endif
    int arc = runner->run(runner, ah_bin, aargv, &acmd);

    if (arc == 0 && acmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, acmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (arc != 0 || acmd.exit_code == -1) {
        out->status = AURA_PROBE_ENGINE_MISSING;
        strncpy(out->install_hint,
                "expected at third_party/ghidra-full/support/analyzeHeadless"
                " (run scripts/bootstrap_ghidra_full.{sh,ps1})",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "bash scripts/bootstrap_ghidra_full.sh",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "bash scripts/bootstrap_ghidra_full.sh",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "powershell -File scripts\\bootstrap_ghidra_full.ps1",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, acmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        /* Keep detected_version (Java) — useful diagnostic for the user. */
        return 0;
    }

    out->status = AURA_PROBE_AVAILABLE;
    /* detected_version stays as the Java version for now; a later slice
     * can extract a Ghidra build number from the analyzeHeadless banner. */
    return 0;
}

int aura_probe_ghidra_decomp(AuraCommandRunner *runner, AuraProbeResult *out)
{
    if (!runner || !runner->run || !out) return -1;

    memset(out, 0, sizeof(*out));
    strncpy(out->engine_id, "ghidra-decomp", sizeof(out->engine_id) - 1);
    out->probed_at_ms = aura_probe_now_ms();

    AuraCommandResult cmd;
    memset(&cmd, 0, sizeof(cmd));
    const char *argv[] = { "--version", NULL };
    char gd_bin[512];
#ifdef _WIN32
    aura_probe_resolve_binary("AURA_GHIDRA_DECOMP_BIN",
                              "third_party/ghidra-decomp/bin/ghidra-decomp.exe",
                              "ghidra-decomp", gd_bin, sizeof(gd_bin));
#else
    aura_probe_resolve_binary("AURA_GHIDRA_DECOMP_BIN",
                              "third_party/ghidra-decomp/bin/ghidra-decomp",
                              "ghidra-decomp", gd_bin, sizeof(gd_bin));
#endif
    int rc = runner->run(runner, gd_bin, argv, &cmd);

    if (rc == 0 && cmd.timed_out) {
        out->status = AURA_PROBE_TIMEOUT;
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (rc != 0 || cmd.exit_code == -1) {
        /* Vendored binary not on disk yet. The hint guides the user to
         * the third_party tree where the bootstrap script will land it. */
        out->status = AURA_PROBE_ENGINE_MISSING;
        strncpy(out->install_hint,
                "expected at third_party/ghidra-decomp/bin/ghidra-decomp"
                " (run scripts/bootstrap_ghidra_decomp.{sh,ps1})",
                sizeof(out->install_hint) - 1);
        strncpy(out->install_hint_linux,
                "bash scripts/bootstrap_ghidra_decomp.sh",
                sizeof(out->install_hint_linux) - 1);
        strncpy(out->install_hint_macos,
                "bash scripts/bootstrap_ghidra_decomp.sh",
                sizeof(out->install_hint_macos) - 1);
        strncpy(out->install_hint_windows,
                "powershell -File scripts\\bootstrap_ghidra_decomp.ps1",
                sizeof(out->install_hint_windows) - 1);
        strncpy(out->raw_diagnostic, cmd.stderr_buf,
                sizeof(out->raw_diagnostic) - 1);
        return 0;
    }

    if (cmd.exit_code != 0) {
        out->status = AURA_PROBE_UNKNOWN_ERROR;
        return 0;
    }

    if (parse_generic_version(cmd.stdout_buf,
                              out->detected_version,
                              sizeof(out->detected_version))) {
        out->status = AURA_PROBE_AVAILABLE;
    } else {
        /* Spawned cleanly but no version token visible — surface the
         * binary as available but flag the empty version downstream. */
        out->status = AURA_PROBE_AVAILABLE;
    }
    return 0;
}
