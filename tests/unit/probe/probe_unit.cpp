// tests/unit/probe/probe_unit.cpp — Phase 2.5 first tracer bullet.
//
// Exercises the engine-agnostic probe core via a FakeCommandRunner so
// the tests do not need any real RE engine binary on disk. The two
// tracer cases are:
//
//   1. `rizin -v` → "rizin 0.8.2 ..." → status=AVAILABLE,
//      detected_version="0.8.2"
//   2. `rizin` not found (spawn failed) → status=ENGINE_MISSING

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstring>
#include <map>
#include <string>
#include <vector>

extern "C" {
#include "engine_probe.h"
#include "probe_registry.h"
#include "probe_cache.h"
}

#include <cstdio>
#include <cstdlib>
#include <filesystem>

namespace {

// ── FakeCommandRunner ──────────────────────────────────────────────────
//
// A scripted runner: callers register the expected (program, argv) and
// the response (exit_code, stdout, stderr, spawn_ok). The `.run` shim
// looks up the call and copies the response into AuraCommandResult.

struct FakeResponse {
    bool        spawn_ok;       // false → run() returns -1, exit_code=-1
    int         exit_code;
    std::string stdout_;
    std::string stderr_;
    bool        timed_out = false;  // when true, child considered killed by timeout
};

struct FakeRunnerState {
    // Keyed by "program\0arg1\0arg2..." so the same program with
    // different argv lists can be scripted independently.
    std::map<std::string, FakeResponse> scripts;
    std::vector<std::string>            calls; // for assertions
};

static std::string make_key(const char *program, const char *const *args) {
    std::string k = program;
    if (args) {
        for (size_t i = 0; args[i] != nullptr; ++i) {
            k.push_back('\0');
            k.append(args[i]);
        }
    }
    return k;
}

static int fake_run(AuraCommandRunner *self,
                    const char        *program,
                    const char *const *args,
                    AuraCommandResult *out) {
    auto *st = static_cast<FakeRunnerState *>(self->state);
    std::string key = make_key(program, args);
    st->calls.push_back(key);

    auto it = st->scripts.find(key);
    if (it == st->scripts.end()) {
        // Unscripted call → treat as ENOENT so probe maps to ENGINE_MISSING.
        out->exit_code = -1;
        std::strncpy(out->stderr_buf, "fake: unscripted",
                     sizeof(out->stderr_buf) - 1);
        out->stderr_buf[sizeof(out->stderr_buf) - 1] = '\0';
        out->stdout_buf[0] = '\0';
        return -1;
    }

    const FakeResponse &r = it->second;
    if (!r.spawn_ok) {
        out->exit_code = -1;
        std::strncpy(out->stderr_buf, r.stderr_.c_str(),
                     sizeof(out->stderr_buf) - 1);
        out->stderr_buf[sizeof(out->stderr_buf) - 1] = '\0';
        out->stdout_buf[0] = '\0';
        return -1;
    }

    out->exit_code = r.exit_code;
    out->timed_out = r.timed_out ? 1 : 0;
    std::strncpy(out->stdout_buf, r.stdout_.c_str(),
                 sizeof(out->stdout_buf) - 1);
    out->stdout_buf[sizeof(out->stdout_buf) - 1] = '\0';
    std::strncpy(out->stderr_buf, r.stderr_.c_str(),
                 sizeof(out->stderr_buf) - 1);
    out->stderr_buf[sizeof(out->stderr_buf) - 1] = '\0';
    return 0;
}

class FakeRunner {
public:
    FakeRunner() {
        runner_.run   = fake_run;
        runner_.state = &state_;
    }

    void script(const char *program,
                std::vector<const char *> args,
                FakeResponse              resp) {
        // args must be NULL-terminated for the C ABI.
        args.push_back(nullptr);
        state_.scripts[make_key(program, args.data())] = std::move(resp);
    }

    AuraCommandRunner *runner() { return &runner_; }

private:
    FakeRunnerState   state_;
    AuraCommandRunner runner_;
};

}  // namespace

// ── Tests ──────────────────────────────────────────────────────────────

TEST_CASE("rizin probe: AVAILABLE when `rizin -v` returns version") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "rizin 0.8.2 @ linux-x86-64 git.0.8.2\n"
                                 "build: 2024-09-01__12:00:00\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.engine_id) == "rizin");
    CHECK(std::string(result.detected_version) == "0.8.2");
}

TEST_CASE("rizin probe: ENGINE_MISSING when binary not found") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{
                    /*spawn_ok=*/false,
                    /*exit_code=*/-1,
                    /*stdout=*/  "",
                    /*stderr=*/  "execvp: No such file or directory"});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.engine_id) == "rizin");
    CHECK(std::string(result.detected_version).empty());
}

TEST_CASE("aura_probe_status_str: covers enum") {
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_AVAILABLE)) ==
          "AVAILABLE");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_ENGINE_MISSING)) ==
          "ENGINE_MISSING");
}

// ── Slice 2: ghidra-decomp probe ───────────────────────────────────────

TEST_CASE("ghidra-decomp probe: AVAILABLE when version cmd succeeds") {
    FakeRunner fake;
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "ghidra-decomp 11.0.3\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.engine_id) == "ghidra-decomp");
    CHECK(std::string(result.detected_version).length() > 0);
    CHECK(result.probed_at_ms != 0);
}

// ── Slice 3: ghidra-full probe ─────────────────────────────────────────

TEST_CASE("ghidra-full probe: AVAILABLE when JRE >=17 and analyzeHeadless OK") {
    FakeRunner fake;
    // `java -version` writes its banner to stderr; major version 17.
    fake.script("java", {"-version"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "",
                    /*stderr=*/  "openjdk version \"17.0.10\" 2024-01-16\n"});
    fake.script("analyzeHeadless", {"-help"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "Headless Analyzer Usage: analyzeHeadless ...\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.engine_id) == "ghidra-full");
    CHECK(result.probed_at_ms != 0);
}

TEST_CASE("ghidra-full probe: RUNTIME_MISSING when java not on PATH") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/false, -1, "", "execvp ENOENT"});
    // analyzeHeadless never queried in this branch — leave unscripted.

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.engine_id) == "ghidra-full");
    CHECK(std::string(result.required_runtime).find("17") !=
          std::string::npos);
    CHECK(std::string(result.install_hint).length() > 0);
}

TEST_CASE("ghidra-full probe: RUNTIME_MISSING when JRE major < 17") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/true, 0, "",
                             "openjdk version \"11.0.21\" 2023-10-17\n"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.detected_version) == "11.0.21");
}

TEST_CASE("ghidra-full probe: ENGINE_MISSING when JRE OK but no analyzeHeadless") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/true, 0, "",
                             "openjdk version \"21.0.1\" 2023-10-17\n"});
    fake.script("analyzeHeadless", {"-help"},
                FakeResponse{/*spawn_ok=*/false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint).length() > 0);
}

// ── Slice 4: angr probe ────────────────────────────────────────────────

TEST_CASE("angr probe: AVAILABLE when python imports angr and prints version") {
    FakeRunner fake;
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "9.2.112\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.engine_id) == "angr");
    CHECK(std::string(result.detected_version) == "9.2.112");
    CHECK(result.probed_at_ms != 0);
}

TEST_CASE("angr probe: RUNTIME_MISSING when python3 not on PATH") {
    FakeRunner fake;
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{/*spawn_ok=*/false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.required_runtime).find("Python") !=
          std::string::npos);
    CHECK(std::string(result.install_hint).length() > 0);
}

TEST_CASE("angr probe: ENGINE_MISSING when python OK but angr not installed") {
    FakeRunner fake;
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/1,
                    /*stdout=*/  "",
                    /*stderr=*/  "ModuleNotFoundError: No module named 'angr'"});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint).find("venv") !=
          std::string::npos);
    CHECK(std::string(result.raw_diagnostic).find("ModuleNotFoundError") !=
          std::string::npos);
}

// ── Slice X.1: angr probe Windows fallback chain ──────────────────────
//
// Plan §1 cross-platform guard (rules.md 2026-05-05): on Windows the
// CPython installer registers `python.exe`, not `python3.exe`. A
// hardcoded `python3` spawn would falsely report RUNTIME_MISSING even
// though the user followed our own install_hint
// (`winget install Python.Python.3.12`). The probe must fall back to
// `python` when `python3` is absent. This test scripts ONLY `python`
// and expects AVAILABLE on either OS.

TEST_CASE("angr probe: falls back to `python` when `python3` not on PATH") {
    FakeRunner fake;
    // python3 is intentionally NOT scripted → unscripted call returns -1
    // (ENOENT). The probe must try the next candidate.
    fake.script("python",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "9.2.55\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "9.2.55");
}

// ── Slice 5: retdec probe ──────────────────────────────────────────────

TEST_CASE("retdec probe: AVAILABLE when retdec-decompiler reports version") {
    FakeRunner fake;
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{
                    /*spawn_ok=*/true,
                    /*exit_code=*/0,
                    /*stdout=*/  "RetDec version: v5.0\n",
                    /*stderr=*/  ""});

    AuraProbeResult result{};
    int rc = aura_probe_retdec(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.engine_id) == "retdec");
    CHECK(std::string(result.detected_version).length() > 0);
    CHECK(result.probed_at_ms != 0);
}

TEST_CASE("retdec probe: ENGINE_MISSING when binary not found") {
    FakeRunner fake;
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{/*spawn_ok=*/false, -1, "",
                             "retdec-decompiler: not found"});

    AuraProbeResult result{};
    int rc = aura_probe_retdec(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint).length() > 0);
    CHECK(std::string(result.raw_diagnostic).find("not found") !=
          std::string::npos);
}

// ── Slice 9: rizin probe also surfaces stderr via raw_diagnostic ───────

TEST_CASE("rizin probe: raw_diagnostic carries stderr when binary missing") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{
                    /*spawn_ok=*/false,
                    /*exit_code=*/-1,
                    /*stdout=*/  "",
                    /*stderr=*/  "rizin: command not found"});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.raw_diagnostic).find("command not found") !=
          std::string::npos);
}

// ── Slice 8: raw_diagnostic captures stderr on spawn failure ───────────

TEST_CASE("ghidra-decomp probe: raw_diagnostic carries stderr on spawn failure") {
    FakeRunner fake;
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{
                    /*spawn_ok=*/false,
                    /*exit_code=*/-1,
                    /*stdout=*/  "",
                    /*stderr=*/  "execvp: No such file or directory"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.raw_diagnostic).find("No such file") !=
          std::string::npos);
}

// ── Slice 17-20: TIMEOUT propagates for the other four engines ────────

namespace {
struct TimeoutRunnerState { const char *stderr_msg; };
static int timeout_run(AuraCommandRunner *self, const char *,
                       const char *const *, AuraCommandResult *out) {
    auto *s = static_cast<TimeoutRunnerState *>(self->state);
    out->exit_code = -1;
    out->timed_out = 1;
    out->stdout_buf[0] = '\0';
    std::strncpy(out->stderr_buf, s->stderr_msg,
                 sizeof(out->stderr_buf) - 1);
    out->stderr_buf[sizeof(out->stderr_buf) - 1] = '\0';
    return 0;
}
static AuraCommandRunner make_timeout_runner(TimeoutRunnerState *st) {
    AuraCommandRunner r{};
    r.run = timeout_run;
    r.state = st;
    return r;
}
}  // namespace

TEST_CASE("ghidra-decomp probe: TIMEOUT when runner times out") {
    TimeoutRunnerState st{"killed after 5s"};
    AuraCommandRunner runner = make_timeout_runner(&st);
    AuraProbeResult result{};
    REQUIRE(aura_probe_ghidra_decomp(&runner, &result) == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.raw_diagnostic).find("killed") !=
          std::string::npos);
}

TEST_CASE("ghidra-full probe: TIMEOUT when java spawn times out") {
    TimeoutRunnerState st{"java timeout"};
    AuraCommandRunner runner = make_timeout_runner(&st);
    AuraProbeResult result{};
    REQUIRE(aura_probe_ghidra_full(&runner, &result) == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.raw_diagnostic).find("timeout") !=
          std::string::npos);
}

TEST_CASE("angr probe: TIMEOUT when python3 times out") {
    TimeoutRunnerState st{"python timeout"};
    AuraCommandRunner runner = make_timeout_runner(&st);
    AuraProbeResult result{};
    REQUIRE(aura_probe_angr(&runner, &result) == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.raw_diagnostic).find("timeout") !=
          std::string::npos);
}

TEST_CASE("retdec probe: TIMEOUT when binary times out") {
    TimeoutRunnerState st{"retdec hung"};
    AuraCommandRunner runner = make_timeout_runner(&st);
    AuraProbeResult result{};
    REQUIRE(aura_probe_retdec(&runner, &result) == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.raw_diagnostic).find("hung") !=
          std::string::npos);
}

// ── Slice 21: ghidra-full TIMEOUT also from analyzeHeadless step ──────

TEST_CASE("ghidra-full probe: TIMEOUT when analyzeHeadless step times out") {
    FakeRunner fake;
    // java -version succeeds with major 21 — passes RUNTIME_MISSING gate.
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/true, 0, "",
                             "openjdk version \"21.0.1\" 2023-10-17\n"});
    // analyzeHeadless will be scripted via a custom raw runner override
    // is not possible with FakeRunner today — script as success then
    // simulate timeout by setting timed_out via the response. Extend
    // FakeResponse with a timed_out flag and have fake_run honor it.
    fake.script("analyzeHeadless", {"-help"},
                FakeResponse{/*spawn_ok=*/true, /*exit_code=*/-1, "",
                             "analyzeHeadless killed after 30s",
                             /*timed_out=*/true});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.raw_diagnostic).find("killed") !=
          std::string::npos);
}

// ── Slice 16: TIMEOUT propagates from runner to probe status ──────────

TEST_CASE("rizin probe: TIMEOUT when runner flags timed_out") {
    // Stand-in scripted runner that returns 0 (spawned) but sets timed_out.
    struct LocalState { bool timed_out_flag; };
    LocalState st{true};
    AuraCommandRunner runner{};
    runner.state = &st;
    runner.run = [](AuraCommandRunner *self, const char *,
                    const char *const *, AuraCommandResult *out) -> int {
        auto *s = static_cast<LocalState *>(self->state);
        out->exit_code  = -1;
        out->timed_out  = s->timed_out_flag ? 1 : 0;
        out->stdout_buf[0] = '\0';
        std::strncpy(out->stderr_buf, "probe timeout after 5s",
                     sizeof(out->stderr_buf) - 1);
        out->stderr_buf[sizeof(out->stderr_buf) - 1] = '\0';
        return 0;  // spawn ok
    };

    AuraProbeResult result{};
    int rc = aura_probe_rizin(&runner, &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_TIMEOUT);
    CHECK(std::string(result.engine_id) == "rizin");
    CHECK(std::string(result.raw_diagnostic).find("timeout") !=
          std::string::npos);
}

// ── Slice 15: registry JSON envelope exposes raw_diagnostic field ─────

TEST_CASE("probe_registry: collect_all envelope exposes raw_diagnostic per engine") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{false, -1, "", "rizin-stderr-marker"});
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});

    char *json = nullptr;
    REQUIRE(aura_probe_collect_all(fake.runner(), &json) == 0);
    REQUIRE(json != nullptr);
    std::string j(json);
    free(json);

    CHECK(j.find("\"raw_diagnostic\"")    != std::string::npos);
    CHECK(j.find("rizin-stderr-marker")   != std::string::npos);
}

// ── Slice 14: angr RUNTIME_MISSING also surfaces stderr ───────────────

TEST_CASE("angr probe: raw_diagnostic carries stderr when python spawn fails") {
    /* Slice X.1 (rules.md §1, 2026-05-05): the fallback chain tries
     * both `python3` and `python`. Spawn-fail must surface stderr from
     * the LAST attempted candidate (i.e. the one whose ENOENT actually
     * sticks as the result). Script both to fail and assert the final
     * diagnostic carries a recognisable "python" token. */
    FakeRunner fake;
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{/*spawn_ok=*/false, -1, "",
                             "execvp ENOENT: python3"});
    fake.script("python",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{/*spawn_ok=*/false, -1, "",
                             "execvp ENOENT: python"});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.raw_diagnostic).find("python") !=
          std::string::npos);
}

// ── Slice 13: ghidra-full ENGINE_MISSING also surfaces stderr ──────────

TEST_CASE("ghidra-full probe: raw_diagnostic carries stderr when analyzeHeadless missing") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/true, 0, "",
                             "openjdk version \"21.0.1\" 2023-10-17\n"});
    fake.script("analyzeHeadless", {"-help"},
                FakeResponse{/*spawn_ok=*/false, -1, "",
                             "execvp ENOENT: analyzeHeadless"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.raw_diagnostic).find("analyzeHeadless") !=
          std::string::npos);
}

// ── Slice 12: ghidra-full RUNTIME_MISSING also surfaces stderr ─────────

TEST_CASE("ghidra-full probe: raw_diagnostic carries stderr when java spawn fails") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/false, -1, "",
                             "execvp ENOENT: java"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.raw_diagnostic).find("ENOENT") !=
          std::string::npos);
}

// ── Slice 7': probe_cache — TTL cache with injectable clock ────────────

namespace { int64_t fake_now_ms = 0; }
static int64_t fake_clock_fn(void *ctx) {
    (void)ctx;
    return fake_now_ms;
}

TEST_CASE("probe_cache: serves cached envelope within TTL, refreshes after expiry") {
    FakeRunner fake;
    // Initial scripts: rizin AVAILABLE, others unscripted (= ENGINE_MISSING).
    fake.script("rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 build\n", ""});

    fake_now_ms = 1000;
    AuraProbeCache *cache =
        aura_probe_cache_create(/*ttl_ms=*/5000, fake_clock_fn, nullptr);
    REQUIRE(cache != nullptr);

    char *j1 = nullptr;
    REQUIRE(aura_probe_cache_get(cache, fake.runner(), &j1) == 0);
    REQUIRE(j1 != nullptr);
    CHECK(std::string(j1).find("0.8.2") != std::string::npos);
    free(j1);

    // Re-script rizin as missing. Within TTL → cache hit, old result.
    fake.script("rizin", {"-v"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake_now_ms = 4000;  // 3 s elapsed, still under 5 s TTL
    char *j2 = nullptr;
    REQUIRE(aura_probe_cache_get(cache, fake.runner(), &j2) == 0);
    CHECK(std::string(j2).find("0.8.2") != std::string::npos);
    free(j2);

    // Advance past TTL → cache miss → fresh probe sees the new script.
    fake_now_ms = 7000;
    char *j3 = nullptr;
    REQUIRE(aura_probe_cache_get(cache, fake.runner(), &j3) == 0);
    CHECK(std::string(j3).find("0.8.2") == std::string::npos);
    CHECK(std::string(j3).find("ENGINE_MISSING") != std::string::npos);
    free(j3);

    aura_probe_cache_destroy(cache);
}

// ── Slice 6: probe_registry — collect_all + JSON envelope ──────────────

TEST_CASE("probe_registry: collect_all emits JSON object with 5 engine keys") {
    FakeRunner fake;
    // Script all five engines as ENGINE_MISSING (simplest uniform case).
    fake.script("rizin", {"-v"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});

    char *json = nullptr;
    int rc = aura_probe_collect_all(fake.runner(), &json);

    REQUIRE(rc == 0);
    REQUIRE(json != nullptr);
    std::string j(json);
    free(json);

    // JSON must mention every engine_id as a key. Look for "<id>": pattern.
    CHECK(j.find("\"rizin\"")        != std::string::npos);
    CHECK(j.find("\"ghidra-decomp\"") != std::string::npos);
    CHECK(j.find("\"ghidra-full\"")   != std::string::npos);
    CHECK(j.find("\"angr\"")          != std::string::npos);
    CHECK(j.find("\"retdec\"")        != std::string::npos);
    // And each result must serialize its status string.
    CHECK(j.find("\"status\"")        != std::string::npos);
    CHECK(j.find("ENGINE_MISSING")    != std::string::npos);
}

TEST_CASE("ghidra-decomp probe: ENGINE_MISSING when binary not found") {
    FakeRunner fake;
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{
                    /*spawn_ok=*/false,
                    /*exit_code=*/-1,
                    /*stdout=*/  "",
                    /*stderr=*/  "execvp: No such file or directory"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.engine_id) == "ghidra-decomp");
    CHECK(std::string(result.install_hint).length() > 0);
    CHECK(result.probed_at_ms != 0);
}

// ── Slice 22: probe_registry envelope serializes status="TIMEOUT" ─────
//
// When a per-engine probe times out, the JSON envelope must surface the
// stable wire identifier "TIMEOUT" so downstream CLI/GUI/LLM consumers
// can distinguish it from generic ENGINE_MISSING / UNKNOWN_ERROR. This
// is a serialization contract test — the underlying TIMEOUT branch is
// already GREEN per slices 16-21.

TEST_CASE("probe_registry: collect_all envelope surfaces TIMEOUT status") {
    FakeRunner fake;
    // rizin spawns OK but is killed by the timeout watchdog.
    fake.script("rizin", {"-v"},
                FakeResponse{/*spawn_ok=*/true, /*exit_code=*/-1,
                             /*stdout=*/"", /*stderr=*/"killed by timer",
                             /*timed_out=*/true});
    // Other four engines: simple ENGINE_MISSING — irrelevant to this test
    // but required so the envelope has a deterministic shape.
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});

    char *json = nullptr;
    int rc = aura_probe_collect_all(fake.runner(), &json);

    REQUIRE(rc == 0);
    REQUIRE(json != nullptr);
    std::string j(json);
    free(json);

    // The rizin slot must serialize the TIMEOUT wire identifier.
    CHECK(j.find("TIMEOUT")              != std::string::npos);
    // And the stderr captured by the timeout branch must propagate.
    CHECK(j.find("killed by timer")      != std::string::npos);
}

// ── Slice 23: status_str wire-ID stability contract ──────────────────
//
// CLI / GUI / LLM consumers switch on these strings to render install
// hints, raise diagnostics, route escalation. They are part of the
// public wire format. Any rename is a breaking change and must be
// caught by this test before it ships.

TEST_CASE("aura_probe_status_str: stable wire identifiers for all 7 statuses") {
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_AVAILABLE))
              == "AVAILABLE");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_RUNTIME_MISSING))
              == "RUNTIME_MISSING");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_ENGINE_MISSING))
              == "ENGINE_MISSING");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_VERSION_MISMATCH))
              == "VERSION_MISMATCH");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_PERMISSION_DENIED))
              == "PERMISSION_DENIED");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_TIMEOUT))
              == "TIMEOUT");
    CHECK(std::string(aura_probe_status_str(AURA_PROBE_UNKNOWN_ERROR))
              == "UNKNOWN_ERROR");
}

// ── Slice 24: probed_at_ms is JSON number, not string, and > 0 ──────
//
// Downstream consumers (cache TTL math, telemetry) need to do numeric
// comparison on probed_at_ms. Accidentally serializing it as a string
// (e.g. via cJSON_AddString) would silently break the cache freshness
// check. Pin the wire type with an unquoted-digit lookahead.

TEST_CASE("probe_registry: probed_at_ms serializes as numeric JSON value") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 build\n", ""});
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "ENOENT"});

    char *json = nullptr;
    REQUIRE(aura_probe_collect_all(fake.runner(), &json) == 0);
    REQUIRE(json != nullptr);
    std::string j(json);
    free(json);

    // Locate "probed_at_ms": and verify the next non-space char is a
    // digit (numeric), NOT a quote (string). At least one engine slot
    // must have a positive value (rizin AVAILABLE just stamped it).
    bool found_numeric_positive = false;
    size_t pos = 0;
    const std::string key = "\"probed_at_ms\":";
    while ((pos = j.find(key, pos)) != std::string::npos) {
        size_t v = pos + key.size();
        while (v < j.size() && j[v] == ' ') ++v;
        REQUIRE(v < j.size());
        // Wire type guard: must not be a quoted string.
        CHECK(j[v] != '"');
        // Parse the numeric token.
        if (j[v] >= '0' && j[v] <= '9') {
            long long val = std::atoll(j.c_str() + v);
            if (val > 0) found_numeric_positive = true;
        }
        pos = v;
    }
    CHECK(found_numeric_positive);
}

// ── Slice 25: registry parent key ↔ child engine_id consistency ─────
//
// Each child object under the envelope must carry the same engine_id
// as its parent JSON key. A mismatch would cause a routing bug where
// a consumer reads the "rizin" slot but the inner record claims
// engine_id="ghidra-decomp". Pin the invariant for all 5 engines.

TEST_CASE("probe_registry: parent key matches child engine_id for all 5 engines") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 build\n", ""});
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{true, 0, "ghidra-decomp 11.0\n", ""});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("python3",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{true, 0, "retdec-decompiler 5.0\n", ""});

    char *json = nullptr;
    REQUIRE(aura_probe_collect_all(fake.runner(), &json) == 0);
    REQUIRE(json != nullptr);
    std::string j(json);
    free(json);

    // For each engine_id we expect, locate the parent key and verify
    // the next "engine_id":"..." token within the same child object
    // matches the parent. Use a forward search: the first engine_id
    // value after each parent key must equal the parent.
    auto check_pair = [&](const std::string &parent_key) {
        size_t p = j.find("\"" + parent_key + "\":{");
        REQUIRE(p != std::string::npos);
        size_t e = j.find("\"engine_id\":\"", p);
        REQUIRE(e != std::string::npos);
        size_t v = e + std::string("\"engine_id\":\"").size();
        size_t end = j.find('"', v);
        REQUIRE(end != std::string::npos);
        std::string child_engine_id = j.substr(v, end - v);
        CHECK(child_engine_id == parent_key);
    };

    check_pair("rizin");
    check_pair("ghidra-decomp");
    check_pair("ghidra-full");
    check_pair("angr");
    check_pair("retdec");
}

// ── Slice 26: install_hint OS-별 분리 (plan §1.1 schema split) ─────
//
// Plan §1.1 calls for OS-keyed install hints so GUI/CLI can present the
// command for the user's actual OS without parsing a concatenated
// string. Tracer bullet: ghidra-full RUNTIME_MISSING populates per-OS
// hint fields with the correct package-manager tokens.

TEST_CASE("ghidra-full probe: RUNTIME_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{/*spawn_ok=*/false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    // Per-OS fields exist and carry the right package-manager token.
    CHECK(std::string(result.install_hint_linux).find("apt")    != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find("brew")   != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find("winget") != std::string::npos);
}

// ── Slice 27: ghidra-full ENGINE_MISSING per-OS install_hint ─────────
//
// When Java is fine but analyzeHeadless is missing, GUI/CLI should
// surface the OS-appropriate bootstrap script path. Linux/macOS use
// the .sh script, Windows uses the .ps1 variant.

TEST_CASE("ghidra-full probe: ENGINE_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{true, 0, "",
                             "openjdk version \"17.0.10\" 2024-01-16\n"});
    fake.script("analyzeHeadless", {"-help"},
                FakeResponse{false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint_linux).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find(".ps1") != std::string::npos);
}

// ── Slice 28: ghidra-decomp ENGINE_MISSING per-OS install_hint ──────

TEST_CASE("ghidra-decomp probe: ENGINE_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint_linux).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find(".ps1") != std::string::npos);
}

// ── Slice 34: angr VERSION_MISMATCH for parsed version < 9.2 ────────
//
// Plan §1.1 requires angr >= 9.2. A successful import that prints an
// older version must surface VERSION_MISMATCH (not AVAILABLE) and
// keep the parsed version visible for diagnostics.

TEST_CASE("angr probe: parsed version below 9.2 yields VERSION_MISMATCH") {
    FakeRunner fake;
    fake.script("python3", {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{true, 0, "9.0.10000\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_VERSION_MISMATCH);
    CHECK(std::string(result.engine_id) == "angr");
    CHECK(std::string(result.detected_version) == "9.0.10000");
    CHECK(std::string(result.required_runtime).find("9.2") != std::string::npos);
}

// Sanity: a 9.2.x banner stays AVAILABLE.

TEST_CASE("angr probe: parsed version 9.2.x stays AVAILABLE") {
    FakeRunner fake;
    fake.script("python3", {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{true, 0, "9.2.55\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "9.2.55");
}

// ── Slice 33: rizin VERSION_MISMATCH for parsed version < 0.7 ───────
//
// Plan §1.1 requires rizin >= 0.7. A successful spawn whose banner
// reports an older version must surface VERSION_MISMATCH (not
// AVAILABLE), keep the parsed version visible for diagnostics, and
// state the required version so the user knows what to upgrade to.

TEST_CASE("rizin probe: parsed version below 0.7 yields VERSION_MISMATCH") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.6.3 @ linux-x86-64\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_VERSION_MISMATCH);
    CHECK(std::string(result.engine_id) == "rizin");
    CHECK(std::string(result.detected_version) == "0.6.3");
    CHECK(std::string(result.required_runtime).find("0.7") != std::string::npos);
}

// Sanity: an explicitly recent version still resolves to AVAILABLE
// (guards against the new gate accidentally rejecting good versions).

TEST_CASE("rizin probe: parsed version 0.8.x stays AVAILABLE") {
    FakeRunner fake;
    fake.script("rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 @ linux-x86-64\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "0.8.2");
}

// ── Slice 32: registry JSON envelope exposes per-OS install_hint ────
//
// Plan §1.1 splits install_hint by OS; the registry serializer must
// surface all three so a remote consumer can render the right command
// for its host without re-probing locally.

TEST_CASE("probe_registry: per-OS install_hint fields appear in JSON envelope") {
    FakeRunner fake;
    // Drive ghidra-decomp into ENGINE_MISSING — that branch we know
    // populates all three per-OS slots.
    fake.script("ghidra-decomp", {"--version"},
                FakeResponse{false, -1, "", "execvp ENOENT"});
    // Other engines: any spawn-fail is fine; we are only asserting on
    // ghidra-decomp's slot in the envelope.
    fake.script("rizin", {"-v"},
                FakeResponse{false, -1, "", "execvp ENOENT"});
    fake.script("java", {"-version"},
                FakeResponse{false, -1, "", "execvp ENOENT"});
    fake.script("python3", {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "execvp ENOENT"});
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "execvp ENOENT"});

    char *json = nullptr;
    int rc = aura_probe_collect_all(fake.runner(), &json);
    REQUIRE(rc == 0);
    REQUIRE(json != nullptr);

    std::string s(json);
    free(json);

    CHECK(s.find("\"install_hint_linux\"")   != std::string::npos);
    CHECK(s.find("\"install_hint_macos\"")   != std::string::npos);
    CHECK(s.find("\"install_hint_windows\"") != std::string::npos);
    // ghidra-decomp's actual values land in the envelope.
    CHECK(s.find("bootstrap_ghidra_decomp.sh")  != std::string::npos);
    CHECK(s.find("bootstrap_ghidra_decomp.ps1") != std::string::npos);
}

// ── Slice 31: angr ENGINE_MISSING per-OS install_hint ───────────────
//
// When python3 spawns OK but `import angr` fails, the per-OS hints
// should point at the bootstrap script (.sh on POSIX, .ps1 on
// Windows) that creates the venv and installs angr.

TEST_CASE("angr probe: ENGINE_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("python3", {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{true, 1, "",
                             "ModuleNotFoundError: No module named 'angr'\n"});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint_linux).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find(".sh")    != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find(".ps1") != std::string::npos);
}

// ── Slice 30: angr RUNTIME_MISSING per-OS install_hint ──────────────
//
// When python3 itself is unavailable, the per-OS hints should carry
// the right package-manager token (apt/brew/winget) so GUI/CLI can
// render the exact install command for the host platform.

TEST_CASE("angr probe: RUNTIME_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("python3", {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_RUNTIME_MISSING);
    CHECK(std::string(result.install_hint_linux).find("apt")    != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find("brew")   != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find("winget") != std::string::npos);
}

// ── Slice 29: retdec ENGINE_MISSING per-OS install_hint ─────────────
//
// retdec is optional and no longer vendored as a source tree. The
// per-OS hints should point users at the supported external-runtime
// contract instead of non-existent bootstrap scripts.

TEST_CASE("retdec probe: ENGINE_MISSING populates per-OS install_hint fields") {
    FakeRunner fake;
    fake.script("retdec-decompiler", {"--version"},
                FakeResponse{false, -1, "", "execvp ENOENT"});

    AuraProbeResult result{};
    int rc = aura_probe_retdec(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_ENGINE_MISSING);
    CHECK(std::string(result.install_hint_linux).find("AURA_RETDEC_DECOMPILER_BIN") != std::string::npos);
    CHECK(std::string(result.install_hint_macos).find("AURA_RETDEC_DECOMPILER_BIN") != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find("AURA_RETDEC_DECOMPILER_BIN") != std::string::npos);
    CHECK(std::string(result.install_hint_windows).find("PATH") != std::string::npos);
}

// ── Phase 2.5.2 Slice X.8: probe binary lookup contract ──────────────
//
// rules.md §1 self-consistency: probe must honor the same engine binary
// override that CLI build_orchestrator does. Lookup priority:
//   1. env var (e.g. AURA_RIZIN_BIN) — explicit user choice wins
//   2. vendored repo path under AURA_REPO_ROOT/third_party/<engine>/...
//   3. PATH default (single name)

namespace {

struct ScopedEnv {
    std::string name;
    std::string prev_value;
    bool        had_prev;
    ScopedEnv(const char *n, const char *v) : name(n), had_prev(false) {
        if (const char *p = std::getenv(n)) {
            prev_value = p;
            had_prev = true;
        }
#ifdef _WIN32
        if (v) _putenv_s(n, v);
        else   _putenv_s(n, "");
#else
        if (v) setenv(n, v, 1);
        else   unsetenv(n);
#endif
    }
    ~ScopedEnv() {
#ifdef _WIN32
        _putenv_s(name.c_str(), had_prev ? prev_value.c_str() : "");
#else
        if (had_prev) setenv(name.c_str(), prev_value.c_str(), 1);
        else          unsetenv(name.c_str());
#endif
    }
};

}  // namespace

TEST_CASE("probe resolver: env override wins (rc=1)") {
    ScopedEnv env("AURA_TEST_BIN", "/custom/path/to/tool");
    char out[256];
    int hit = aura_probe_resolve_binary("AURA_TEST_BIN",
                                        "third_party/x/bin/tool",
                                        "tool", out, sizeof(out));
    CHECK(hit == 1);
    CHECK(std::string(out) == "/custom/path/to/tool");
}

TEST_CASE("probe resolver: empty env value falls through to PATH default") {
    ScopedEnv env("AURA_TEST_BIN", "");
    ScopedEnv root("AURA_REPO_ROOT", nullptr);
    char out[256];
    int hit = aura_probe_resolve_binary("AURA_TEST_BIN", NULL,
                                        "tool", out, sizeof(out));
    CHECK(hit == 3);
    CHECK(std::string(out) == "tool");
}

TEST_CASE("probe resolver: vendored path used when file exists (rc=2)") {
    namespace fs = std::filesystem;
    auto tmp_dir = fs::temp_directory_path() / "aura_probe_resolver_test";
    fs::create_directories(tmp_dir / "third_party" / "x" / "bin");
    auto vendored = tmp_dir / "third_party" / "x" / "bin" / "tool";
    {
        std::FILE *f = std::fopen(vendored.string().c_str(), "wb");
        REQUIRE(f != nullptr);
        std::fputs("dummy\n", f);
        std::fclose(f);
    }

    ScopedEnv env("AURA_TEST_BIN", nullptr);
    ScopedEnv root("AURA_REPO_ROOT", tmp_dir.string().c_str());

    char out[512];
    int hit = aura_probe_resolve_binary("AURA_TEST_BIN",
                                        "third_party/x/bin/tool",
                                        "tool", out, sizeof(out));
    CHECK(hit == 2);
    CHECK(std::string(out).find("third_party/x/bin/tool") != std::string::npos);

    fs::remove_all(tmp_dir);
}

TEST_CASE("probe resolver: vendored path absent → PATH default (rc=3)") {
    namespace fs = std::filesystem;
    auto tmp_dir = fs::temp_directory_path() / "aura_probe_resolver_no_vendored";
    fs::create_directories(tmp_dir);

    ScopedEnv env("AURA_TEST_BIN", nullptr);
    ScopedEnv root("AURA_REPO_ROOT", tmp_dir.string().c_str());

    char out[256];
    int hit = aura_probe_resolve_binary("AURA_TEST_BIN",
                                        "third_party/missing/bin/tool",
                                        "tool", out, sizeof(out));
    CHECK(hit == 3);
    CHECK(std::string(out) == "tool");

    fs::remove_all(tmp_dir);
}

TEST_CASE("rizin probe: AURA_RIZIN_BIN env override is honored at spawn") {
    ScopedEnv env("AURA_RIZIN_BIN", "/opt/custom/rizin");
    ScopedEnv root("AURA_REPO_ROOT", nullptr);

    FakeRunner fake;
    fake.script("/opt/custom/rizin", {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 @ test\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);

    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "0.8.2");
}

TEST_CASE("ghidra-decomp probe: AURA_GHIDRA_DECOMP_BIN env override is honored") {
    ScopedEnv env("AURA_GHIDRA_DECOMP_BIN", "/opt/g/ghidra-decomp");
    ScopedEnv root("AURA_REPO_ROOT", nullptr);

    FakeRunner fake;
    fake.script("/opt/g/ghidra-decomp", {"--version"},
                FakeResponse{true, 0, "ghidra-decomp 11.1\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}

TEST_CASE("retdec probe: AURA_RETDEC_DECOMPILER_BIN env override is honored") {
    ScopedEnv env("AURA_RETDEC_DECOMPILER_BIN", "/opt/r/retdec-decompiler");
    ScopedEnv root("AURA_REPO_ROOT", nullptr);

    FakeRunner fake;
    fake.script("/opt/r/retdec-decompiler", {"--version"},
                FakeResponse{true, 0, "RetDec 5.0\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_retdec(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}

TEST_CASE("angr probe: AURA_ANGR_PYTHON_BIN env override skips fallback chain") {
    ScopedEnv env("AURA_ANGR_PYTHON_BIN", "/opt/venv/bin/python");
    ScopedEnv root("AURA_REPO_ROOT", nullptr);

    FakeRunner fake;
    fake.script("/opt/venv/bin/python",
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{true, 0, "9.2.55\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "9.2.55");
}

TEST_CASE("ghidra-full probe: AURA_GHIDRA_FULL_ANALYZE_HEADLESS env override honored") {
    ScopedEnv env("AURA_GHIDRA_FULL_ANALYZE_HEADLESS",
                  "/opt/g/support/analyzeHeadless");
    ScopedEnv jenv("AURA_JAVA_BIN", nullptr);
    ScopedEnv root("AURA_REPO_ROOT", nullptr);

    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{true, 0, "",
                             "openjdk version \"17.0.10\" 2024-01-16\n"});
    fake.script("/opt/g/support/analyzeHeadless", {"-help"},
                FakeResponse{true, 0, "Usage: analyzeHeadless\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}

// ── Phase 2.5.2 Slice X.8.1: per-probe vendored path regression ───────
//
// Codex review #4 medium: the resolver-only tests above prove the
// helper's tiers work, but they do not catch a future regression where
// a probe forgets to call the resolver, passes the wrong vendored_rel,
// or skips vendored after AURA_REPO_ROOT is set. These per-probe tests
// build the exact expected vendored file under a temp AURA_REPO_ROOT
// and assert FakeRunner sees the absolute path the resolver should
// produce. Drop the env override entirely so the only path that yields
// AVAILABLE is the vendored tier.

namespace {

struct VendoredRoot {
    std::filesystem::path dir;
    std::filesystem::path file;
    ScopedEnv             env_override;
    ScopedEnv             repo_root;

    VendoredRoot(const char *override_name,
                 const std::string &test_dir_name,
                 const char *vendored_rel)
      : dir(std::filesystem::temp_directory_path() / test_dir_name),
        file(dir / vendored_rel),
        env_override(override_name, nullptr),
        repo_root("AURA_REPO_ROOT", nullptr)
    {
        std::filesystem::create_directories(file.parent_path());
        std::FILE *f = std::fopen(file.string().c_str(), "wb");
        if (f) { std::fputs("dummy\n", f); std::fclose(f); }
        /* Late-set AURA_REPO_ROOT so the resolver sees it. ScopedEnv ctor
         * already cleared any previous value. Use generic_string() so
         * the resolver's `%s/%s` snprintf produces a path that matches
         * what we script in FakeRunner (forward slashes throughout). */
        std::string root_s = dir.generic_string();
#ifdef _WIN32
        _putenv_s("AURA_REPO_ROOT", root_s.c_str());
#else
        setenv("AURA_REPO_ROOT", root_s.c_str(), 1);
#endif
    }
    ~VendoredRoot() {
        std::error_code ec;
        std::filesystem::remove_all(dir, ec);
    }
    /* Resolver concatenates with snprintf "%s/%s" → forward slashes.
     * std::filesystem::path::string() returns native form (backslashes
     * on Windows), which would mismatch FakeRunner keys. Use
     * generic_string() to normalize to forward-slash form. */
    std::string absolute() const { return file.generic_string(); }
};

}  // namespace

TEST_CASE("rizin probe: vendored third_party path is honored when present") {
#ifdef _WIN32
    VendoredRoot vr("AURA_RIZIN_BIN", "aura_rizin_vendored",
                    "third_party/rizin/0.8.2/bin/rizin.exe");
#else
    VendoredRoot vr("AURA_RIZIN_BIN", "aura_rizin_vendored",
                    "third_party/rizin/0.8.2/bin/rizin");
#endif
    FakeRunner fake;
    fake.script(vr.absolute().c_str(), {"-v"},
                FakeResponse{true, 0, "rizin 0.8.2 @ vendored\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_rizin(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "0.8.2");
}

TEST_CASE("ghidra-decomp probe: vendored third_party path is honored when present") {
#ifdef _WIN32
    VendoredRoot vr("AURA_GHIDRA_DECOMP_BIN", "aura_gd_vendored",
                    "third_party/ghidra-decomp/bin/ghidra-decomp.exe");
#else
    VendoredRoot vr("AURA_GHIDRA_DECOMP_BIN", "aura_gd_vendored",
                    "third_party/ghidra-decomp/bin/ghidra-decomp");
#endif
    FakeRunner fake;
    fake.script(vr.absolute().c_str(), {"--version"},
                FakeResponse{true, 0, "ghidra-decomp 11.1\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_decomp(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}

TEST_CASE("retdec probe: vendored third_party path is honored when present") {
#ifdef _WIN32
    VendoredRoot vr("AURA_RETDEC_DECOMPILER_BIN", "aura_retdec_vendored",
                    "third_party/retdec/bin/retdec-decompiler.exe");
#else
    VendoredRoot vr("AURA_RETDEC_DECOMPILER_BIN", "aura_retdec_vendored",
                    "third_party/retdec/bin/retdec-decompiler");
#endif
    FakeRunner fake;
    fake.script(vr.absolute().c_str(), {"--version"},
                FakeResponse{true, 0, "RetDec 5.0\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_retdec(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}

TEST_CASE("angr probe: vendored venv python is honored when present") {
#ifdef _WIN32
    VendoredRoot vr("AURA_ANGR_PYTHON_BIN", "aura_angr_vendored",
                    "third_party/angr/venv/Scripts/python.exe");
#else
    VendoredRoot vr("AURA_ANGR_PYTHON_BIN", "aura_angr_vendored",
                    "third_party/angr/venv/bin/python");
#endif
    FakeRunner fake;
    fake.script(vr.absolute().c_str(),
                {"-c", "import angr; print(angr.__version__)"},
                FakeResponse{true, 0, "9.2.55\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_angr(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
    CHECK(std::string(result.detected_version) == "9.2.55");
}

TEST_CASE("ghidra-full probe: vendored analyzeHeadless is honored when present") {
#ifdef _WIN32
    VendoredRoot vr("AURA_GHIDRA_FULL_ANALYZE_HEADLESS",
                    "aura_gf_vendored",
                    "third_party/ghidra-full/support/analyzeHeadless.bat");
#else
    VendoredRoot vr("AURA_GHIDRA_FULL_ANALYZE_HEADLESS",
                    "aura_gf_vendored",
                    "third_party/ghidra-full/support/analyzeHeadless");
#endif
    ScopedEnv jenv("AURA_JAVA_BIN", nullptr);

    FakeRunner fake;
    fake.script("java", {"-version"},
                FakeResponse{true, 0, "",
                             "openjdk version \"17.0.10\" 2024-01-16\n"});
    fake.script(vr.absolute().c_str(), {"-help"},
                FakeResponse{true, 0, "Usage: analyzeHeadless\n", ""});

    AuraProbeResult result{};
    int rc = aura_probe_ghidra_full(fake.runner(), &result);
    REQUIRE(rc == 0);
    CHECK(result.status == AURA_PROBE_AVAILABLE);
}
