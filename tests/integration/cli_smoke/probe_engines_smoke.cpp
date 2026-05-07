// probe_engines_smoke.cpp — Phase 2.5 first tracer bullet.
//
// Public behavior gate for `aura --probe-engines`: the command must emit
// a JSON envelope (aura_schema=1, command="probe-engines") whose body
// contains a stable `engines` array with one record per known engine_id
// (rizin, ghidra-decomp, ghidra-full, angr, retdec). Each record must
// carry at least an engine_id and a status string drawn from the
// ProbeStatus enum defined in plans/c-q12-refactored-key.md §1.1.
//
// This test is intentionally minimal. It does NOT assert that any
// particular engine is AVAILABLE — host environments differ. It only
// asserts the contract: command exists, JSON shape stable, all five
// engines surfaced.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <string>

#include "cJSON.h"

#ifdef _WIN32
#define POPEN  _popen
#define PCLOSE _pclose
#else
#define POPEN  popen
#define PCLOSE pclose
#endif

static std::string aura_binary() {
    if (const char *env = std::getenv("AURA_BIN")) return env;
    return "aura";
}

struct CmdResult {
    int         exit_code = -1;
    std::string stdout_;
};

static CmdResult run(const std::string &cmd) {
    CmdResult r;
#ifdef _WIN32
    std::string wrapped = "\"" + cmd + "\"";
    FILE *fp = POPEN(wrapped.c_str(), "r");
#else
    FILE *fp = POPEN(cmd.c_str(), "r");
#endif
    if (!fp) return r;
    std::array<char, 4096> buf{};
    while (std::fgets(buf.data(), buf.size(), fp)) {
        r.stdout_.append(buf.data());
    }
    int rc = PCLOSE(fp);
#ifdef _WIN32
    r.exit_code = rc;
#else
    if (WIFEXITED(rc)) r.exit_code = WEXITSTATUS(rc);
    else               r.exit_code = -1;
#endif
    return r;
}

static const std::set<std::string> kValidStatuses = {
    "AVAILABLE",
    "RUNTIME_MISSING",
    "ENGINE_MISSING",
    "VERSION_MISMATCH",
    "PERMISSION_DENIED",
    "TIMEOUT",
    "UNKNOWN_ERROR",
};

TEST_CASE("probe_engines: emits stable envelope with five engines") {
    CmdResult r = run("\"" + aura_binary() + "\" --probe-engines");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_.substr(0, 400));

    cJSON *root = cJSON_Parse(r.stdout_.c_str());
    REQUIRE_MESSAGE(root != nullptr,
                    "stdout is not valid JSON: ", r.stdout_.substr(0, 400));

    // Envelope contract — same shape as analyze/decompile commands.
    cJSON *schema = cJSON_GetObjectItem(root, "aura_schema");
    REQUIRE(cJSON_IsNumber(schema));
    CHECK(cJSON_GetNumberValue(schema) == 1.0);

    cJSON *command = cJSON_GetObjectItem(root, "command");
    REQUIRE(cJSON_IsString(command));
    CHECK(std::string(cJSON_GetStringValue(command)) == "probe-engines");

    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(cJSON_IsObject(body));

    cJSON *engines = cJSON_GetObjectItem(body, "engines");
    REQUIRE_MESSAGE(cJSON_IsArray(engines),
                    "body.engines must be an array");

    // Collect engine_ids and check minimal record shape.
    std::set<std::string> seen;
    cJSON *entry = nullptr;
    cJSON_ArrayForEach(entry, engines) {
        REQUIRE(cJSON_IsObject(entry));
        cJSON *eid = cJSON_GetObjectItem(entry, "engine_id");
        REQUIRE(cJSON_IsString(eid));
        cJSON *status = cJSON_GetObjectItem(entry, "status");
        REQUIRE(cJSON_IsString(status));

        std::string status_s = cJSON_GetStringValue(status);
        CHECK_MESSAGE(kValidStatuses.count(status_s) == 1,
                      "unknown status: ", status_s);

        seen.insert(cJSON_GetStringValue(eid));
    }

    // Required engines per Phase 2.5 §1.1.
    CHECK(seen.count("rizin") == 1);
    CHECK(seen.count("ghidra-decomp") == 1);
    CHECK(seen.count("ghidra-full") == 1);
    CHECK(seen.count("angr") == 1);
    CHECK(seen.count("retdec") == 1);

    cJSON_Delete(root);
}
