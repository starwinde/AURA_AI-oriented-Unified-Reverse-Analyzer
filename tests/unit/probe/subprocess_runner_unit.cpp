// tests/unit/probe/subprocess_runner_unit.cpp — Phase 2.5.1 Slice X.3
//
// Exercises the real (non-fake) AuraCommandRunner backed by an OS
// subprocess. Uses portable shell builtins so the suite never depends
// on a real RE engine binary.
//
// Cross-platform commands:
//   POSIX  : /bin/sh -c "echo hello"
//   Windows: cmd.exe /c "echo hello"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <chrono>
#include <cstring>
#include <string>

extern "C" {
#include "command_runner_subprocess.h"
}

#ifdef _WIN32
static const char *kShell    = "cmd.exe";
static const char *kShellArg = "/c";
#else
static const char *kShell    = "/bin/sh";
static const char *kShellArg = "-c";
#endif

TEST_CASE("subprocess runner: echo prints to stdout, exit code 0") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    const char *argv[] = { kShellArg, "echo hello-from-subprocess", nullptr };
    int rc = r->run(r, kShell, argv, &res);

    CHECK(rc == 0);
    CHECK(res.exit_code == 0);
    CHECK(res.timed_out == 0);
    CHECK(std::string(res.stdout_buf).find("hello-from-subprocess")
          != std::string::npos);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: nonzero exit code is reported") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    const char *argv[] = { kShellArg, "exit 42", nullptr };
    int rc = r->run(r, kShell, argv, &res);

    CHECK(rc == 0);                  /* spawn succeeded */
    CHECK(res.exit_code == 42);
    CHECK(res.timed_out == 0);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: missing program returns spawn failure (-1)") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    const char *argv[] = { nullptr };
    int rc = r->run(r,
                    "this-binary-definitely-does-not-exist-aura-test",
                    argv, &res);

    CHECK(rc == -1);
    CHECK(res.exit_code == -1);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: stderr is captured separately from stdout") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
#ifdef _WIN32
    /* `echo X 1>&2` is the cmd.exe redirect form. */
    const char *argv[] = { kShellArg, "echo err-stream 1>&2", nullptr };
#else
    const char *argv[] = { kShellArg, "echo err-stream 1>&2", nullptr };
#endif
    int rc = r->run(r, kShell, argv, &res);

    CHECK(rc == 0);
    CHECK(res.exit_code == 0);
    CHECK(std::string(res.stderr_buf).find("err-stream")
          != std::string::npos);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: large output does not deadlock") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
#ifdef _WIN32
    const char *argv[] = {
        "/c",
        "for /L %i in (1,1,2000) do @echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        nullptr
    };
    int rc = r->run(r, "cmd", argv, &res);
#else
    const char *argv[] = { "-c", "yes | head -c 131072", nullptr };
    int rc = r->run(r, "/bin/sh", argv, &res);
#endif

    CHECK(rc == 0);
    CHECK(res.exit_code == 0);
    CHECK(res.timed_out == 0);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: simultaneous large stdout and stderr are captured") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
#ifdef _WIN32
    /* cmd.exe has no simple portable way to make two shell builtins write
     * concurrently, so this Windows regression uses sequential large
     * streams. Iteration count tuned so cmd.exe finishes well inside the
     * 5 s timeout while still pushing past our 4 KiB capture buffer
     * (200 × 64 chars = 12.8 KiB per stream, plus CRLF). */
    const char *argv[] = {
        "/c",
        "for /L %i in (1,1,200) do @echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa & for /L %i in (1,1,200) do @echo EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE 1>&2",
        nullptr
    };
    int rc = r->run(r, "cmd", argv, &res);
#else
    const char *argv[] = {
        "-c",
        "yes | head -c 70000; yes E | head -c 70000 1>&2",
        nullptr
    };
    int rc = r->run(r, "/bin/sh", argv, &res);
#endif

    CHECK(rc == 0);
    CHECK(res.exit_code == 0);
    CHECK(res.timed_out == 0);
    CHECK(std::strlen(res.stdout_buf) > 0);
    CHECK(std::strlen(res.stderr_buf) > 0);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: timeout while stdout is streaming returns promptly") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(500);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    auto before = std::chrono::steady_clock::now();
#ifdef _WIN32
    const char *argv[] = {
        "/c",
        "for /L %i in (1,1,1000000) do @echo x",
        nullptr
    };
    int rc = r->run(r, "cmd", argv, &res);
#else
    const char *argv[] = { "-c", "yes", nullptr };
    int rc = r->run(r, "/bin/sh", argv, &res);
#endif
    auto after = std::chrono::steady_clock::now();
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(after - before)
            .count();

    CHECK(rc == 0);
    CHECK(res.timed_out == 1);
    CHECK(res.exit_code == -1);
    CHECK(std::string(res.stderr_buf).find("killed by timer")
          != std::string::npos);
    CHECK(elapsed_ms < 1000);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: timeout diagnostic is preserved for stderr streaming") {
    AuraCommandRunner *r = aura_command_runner_subprocess_create(500);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    auto before = std::chrono::steady_clock::now();
#ifdef _WIN32
    const char *argv[] = {
        "/c",
        "for /L %i in (1,1,1000000) do @echo E 1>&2",
        nullptr
    };
    int rc = r->run(r, "cmd", argv, &res);
#else
    const char *argv[] = { "-c", "yes E 1>&2", nullptr };
    int rc = r->run(r, "/bin/sh", argv, &res);
#endif
    auto after = std::chrono::steady_clock::now();
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(after - before)
            .count();

    CHECK(rc == 0);
    CHECK(res.timed_out == 1);
    CHECK(res.exit_code == -1);
    CHECK(std::string(res.stderr_buf).find("killed by timer")
          != std::string::npos);
    CHECK(elapsed_ms < 1000);

    aura_command_runner_subprocess_destroy(r);
}

TEST_CASE("subprocess runner: background descendant pipe inheritance does not hang") {
#ifdef _WIN32
    /* Windows handle inheritance across a detached cmd.exe descendant is not
     * equivalent to the POSIX fork/shell case this regression targets.
     */
    CHECK(true);
#else
    AuraCommandRunner *r = aura_command_runner_subprocess_create(5000);
    REQUIRE(r != nullptr);

    AuraCommandResult res{};
    auto before = std::chrono::steady_clock::now();
    const char *argv[] = { "-c", "(sleep 5) & exit 0", nullptr };
    int rc = r->run(r, "/bin/sh", argv, &res);
    auto after = std::chrono::steady_clock::now();
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(after - before)
            .count();

    CHECK(rc == 0);
    CHECK(res.exit_code == 0);
    CHECK(res.timed_out == 0);
    CHECK(elapsed_ms < 2000);

    aura_command_runner_subprocess_destroy(r);
#endif
}
