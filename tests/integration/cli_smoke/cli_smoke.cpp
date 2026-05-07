// cli_smoke.cpp — Phase 11.1 CLI v1 invariant gate.
//
// Spawns the `aura` binary as a subprocess, captures stdout, parses the
// JSON, and asserts the public contract of each subcommand. Same pattern
// as orchestrator_smoke (doctest + cJSON), one layer up: instead of
// linking aura_core, we exercise the real installed-style binary.
//
// Reference engine = Rizin. Test SKIPs gracefully when AURA_RIZIN_BIN /
// fetched binary is missing — CI (orchestrator-smoke.yml) provides it.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "cJSON.h"

namespace fs = std::filesystem;

// ── repo discovery ─────────────────────────────────────────────────────────

static std::string repo_root() {
    if (const char *env = std::getenv("AURA_REPO_ROOT")) return env;
    fs::path p = fs::current_path();
    for (int i = 0; i < 10; ++i) {
        if (fs::exists(p / "CONTEXT.md")) return p.string();
        if (!p.has_parent_path()) break;
        p = p.parent_path();
    }
    return fs::current_path().string();
}

static std::string fixture_path() {
    fs::path root = repo_root();
#ifdef _WIN32
    return (root / "tests/fixtures/bin/pe_smoke.x86_64.exe").string();
#else
    return (root / "tests/fixtures/bin/elf_smoke.x86_64").string();
#endif
}

// Path to the `aura` binary, injected via env by CMake (AURA_BIN).
static std::string aura_binary() {
    if (const char *env = std::getenv("AURA_BIN")) return env;
    return "aura";  // PATH fallback
}

// Path to a working rizin, either from AURA_RIZIN_BIN or
// third_party/rizin/0.8.0-*/.../bin/rizin{,.exe}. Empty string = not found.
static std::string discover_rizin_bin() {
    if (const char *env = std::getenv("AURA_RIZIN_BIN")) {
        if (fs::exists(env)) return env;
    }
    fs::path root = repo_root();
#ifdef _WIN32
    fs::path candidate =
        root / "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe";
#else
    fs::path candidate = root / "third_party/rizin/0.8.0-static/bin/rizin";
#endif
    if (fs::exists(candidate)) return candidate.string();
    return {};
}

// Fixed vendored path only. Used by the auto-discovery regression so the
// test does not accidentally pass because CTest injected AURA_RIZIN_BIN.
static std::string vendored_rizin_bin() {
    fs::path root = repo_root();
#ifdef _WIN32
    fs::path candidate =
        root / "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe";
#else
    fs::path candidate = root / "third_party/rizin/0.8.0-static/bin/rizin";
#endif
    if (fs::exists(candidate)) return candidate.string();
    return {};
}

// ── subprocess capture ─────────────────────────────────────────────────────

struct CmdResult {
    int         exit_code = -1;
    std::string stdout_;
};

#ifdef _WIN32
#define POPEN  _popen
#define PCLOSE _pclose
#else
#define POPEN  popen
#define PCLOSE pclose
#endif

// Run a shell command and capture stdout. Quotes the binary path to handle
// spaces (e.g. the Korean "바탕 화면" in this repo's path).
//
// Windows quirk: _popen invokes `cmd /c "<command>"` which STRIPS the outer
// quotes. If the command string itself contains a quoted path with spaces,
// cmd then splits on the inner spaces. The standard fix is to wrap the
// entire command in an extra layer of quotes so cmd's strip leaves valid
// quoted tokens. See cmd.exe quoting rules (`cmd /?`, the section on /c).
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
    r.exit_code = rc;  // _pclose returns the exit code directly
#else
    if (WIFEXITED(rc)) r.exit_code = WEXITSTATUS(rc);
    else               r.exit_code = -1;
#endif
    return r;
}

// Build the leading "AURA_RIZIN_BIN=... aura --compact" prefix.
static std::string aura_invocation(const std::string &rizin) {
    std::string s;
#ifdef _WIN32
    (void)rizin;
    // cmd.exe doesn't accept inline VAR=val prefix; rely on env already set
    // by the parent ctest process via set_tests_properties(ENVIRONMENT ...).
    s = "\"" + aura_binary() + "\" --compact";
#else
    s = "AURA_RIZIN_BIN=\"" + rizin + "\" \"" + aura_binary() + "\" --compact";
#endif
    return s;
}

static std::string aura_invocation_without_rizin_env() {
#ifdef _WIN32
    return "set AURA_RIZIN_BIN=& set AURA_REPO_ROOT=& \"" + aura_binary() +
           "\" --compact";
#else
    return "env -u AURA_RIZIN_BIN -u AURA_REPO_ROOT \"" + aura_binary() +
           "\" --compact";
#endif
}

// ── invariant helpers ──────────────────────────────────────────────────────

static cJSON *parse_or_fail(const std::string &payload) {
    cJSON *root = cJSON_Parse(payload.c_str());
    REQUIRE_MESSAGE(root != nullptr,
                    "stdout is not valid JSON: ", payload.substr(0, 200));
    return root;
}

static double get_number(const cJSON *obj, const char *key) {
    cJSON *v = cJSON_GetObjectItem(const_cast<cJSON *>(obj), key);
    REQUIRE(v != nullptr);
    REQUIRE(cJSON_IsNumber(v));
    return cJSON_GetNumberValue(v);
}

static std::string get_string(const cJSON *obj, const char *key) {
    cJSON *v = cJSON_GetObjectItem(const_cast<cJSON *>(obj), key);
    REQUIRE(v != nullptr);
    REQUIRE(cJSON_IsString(v));
    return cJSON_GetStringValue(v);
}

// ── tests ──────────────────────────────────────────────────────────────────

TEST_CASE("cli_smoke: aura --version") {
    CmdResult r = run("\"" + aura_binary() + "\" --version");
    CHECK(r.exit_code == 0);
    CHECK(r.stdout_.find("aura ") == 0);
}

TEST_CASE("cli_smoke: gui help advertises protected string export") {
    CmdResult r = run("\"" + aura_binary() + "\" gui --help");
    CHECK(r.exit_code == 0);
    CHECK(r.stdout_.find("protected-strings") != std::string::npos);
}

TEST_CASE("cli_smoke: analyze emits valid unified-model JSON") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_number(root, "aura_schema") == 1.0);
    CHECK(get_string(root, "command") == "analyze");
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    CHECK(get_number(body, "functions_count") >= 1.0);
    cJSON *fns = cJSON_GetObjectItem(body, "functions");
    REQUIRE(cJSON_IsArray(fns));
    CHECK(cJSON_GetArraySize(fns) >= 1);
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: analyze auto-discovers vendored rizin without env override") {
    if (vendored_rizin_bin().empty()) {
        MESSAGE("SKIP: no vendored rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation_without_rizin_env() + " analyze \"" +
                      fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_number(root, "aura_schema") == 1.0);
    CHECK(get_string(root, "command") == "analyze");
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    CHECK(get_number(body, "functions_count") >= 1.0);
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: analyze body exposes symbols[] array") {
    // Phase 11.3.5 cycle-4: symbols (incl. imports) are first-class
    // normalized records and the analyze body must surface them as an
    // array of {addr, kind, name, provenance}. Imports panel = kind=="import"
    // filter view; Symbols panel = full list.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE(r.exit_code == 0);

    cJSON *root = parse_or_fail(r.stdout_);
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    cJSON *syms = cJSON_GetObjectItem(body, "symbols");
    REQUIRE_MESSAGE(cJSON_IsArray(syms),
                    "body.symbols must be an array");
    double count = get_number(body, "symbols_count");
    CHECK(static_cast<int>(count) == cJSON_GetArraySize(syms));
    if (cJSON_GetArraySize(syms) > 0) {
        cJSON *first = cJSON_GetArrayItem(syms, 0);
        REQUIRE(first != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "addr")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "kind")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "name")));
        REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(first, "provenance")));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: analyze body exposes xrefs[] array") {
    // Phase 11.3.5 cycle-1: xrefs are first-class normalized records and
    // the unified analyze body must surface them as an array (not just
    // a count) so downstream tooling (RPC, GUI dock) can consume them.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    cJSON *xrefs = cJSON_GetObjectItem(body, "xrefs");
    REQUIRE_MESSAGE(cJSON_IsArray(xrefs),
                    "body.xrefs must be an array; got: ",
                    (xrefs ? cJSON_PrintUnformatted(xrefs) : "null"));
    // Count and array length must agree.
    double count = get_number(body, "xrefs_count");
    CHECK(static_cast<int>(count) == cJSON_GetArraySize(xrefs));
    // If any present, each entry must have the canonical shape.
    if (cJSON_GetArraySize(xrefs) > 0) {
        cJSON *first = cJSON_GetArrayItem(xrefs, 0);
        REQUIRE(first != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "from")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "to")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "kind")));
        REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(first, "provenance")));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: analyze body exposes strings[] array") {
    // Phase 11.3.6 cycle-3: strings are first-class normalized records
    // (9th 1급 record, body schema v3) and the unified analyze body must
    // surface them as an array (not just strings_count) so downstream
    // tooling (RPC list_strings, GUI Strings dock, PP4 label suggestion)
    // can consume them. The fixture is a real ELF (libc-linked) so a few
    // literals are essentially guaranteed.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    // Body schema must be v3+ for strings to be populated.
    CHECK(get_number(body, "version") >= 3.0);
    cJSON *strings = cJSON_GetObjectItem(body, "strings");
    REQUIRE_MESSAGE(cJSON_IsArray(strings),
                    "body.strings must be an array; got: ",
                    (strings ? cJSON_PrintUnformatted(strings) : "null"));
    // Count and array length must agree.
    double count = get_number(body, "strings_count");
    CHECK(static_cast<int>(count) == cJSON_GetArraySize(strings));
    // If any present, each entry must have the canonical shape.
    if (cJSON_GetArraySize(strings) > 0) {
        cJSON *first = cJSON_GetArrayItem(strings, 0);
        REQUIRE(first != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "string_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "addr")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "length")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "encoding")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "section")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "content")));
        REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(first, "provenance")));
        cJSON *prov = cJSON_GetObjectItem(first, "provenance");
        CHECK(get_string(prov, "source") == std::string("rizin"));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: field-candidates --func emits offset clusters (Phase 11.4.4)") {
    // PP2 / ADR-0046 — display-only path 4번째 적용.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " field-candidates --func "
                      + addr_arg + " \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "field-candidates exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "field-candidates");
    CHECK(get_number(root, "function_addr") == entry);
    cJSON *cands = cJSON_GetObjectItem(root, "candidates");
    REQUIRE_MESSAGE(cJSON_IsArray(cands),
                    "candidates must be an array");
    cJSON *clusters = cJSON_GetObjectItem(root, "stack_clusters");
    REQUIRE_MESSAGE(cJSON_IsArray(clusters),
                    "stack_clusters must be an array");
    // For minimal fixtures op_str source may yield 0 (analyze body
    // doesn't pre-fill instructions[] — disasm body separation per
    // ADR-0040 D4); stack_clusters may also be 0 for trivial functions.
    // Contract test verifies shape; both arrays may be empty.
    if (cJSON_GetArraySize(cands) > 0) {
        cJSON *c0 = cJSON_GetArrayItem(cands, 0);
        REQUIRE(c0 != nullptr);
        CHECK(cJSON_IsString(cJSON_GetObjectItem(c0, "base_reg")));
        REQUIRE(cJSON_IsArray(cJSON_GetObjectItem(c0, "offsets")));
        CHECK(get_string(c0, "source") == std::string("op_str_regex"));
    }
    if (cJSON_GetArraySize(clusters) > 0) {
        cJSON *s0 = cJSON_GetArrayItem(clusters, 0);
        REQUIRE(s0 != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(s0, "var_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(s0, "stack_offset")));
        CHECK(get_string(s0, "kind") == std::string("stack"));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: array-candidates --func emits raw stat + type_hints (Phase 11.4.5)") {
    // PP3 / ADR-0047 — display-only path 5번째 적용.
    // v1 = (b) opportunistic type_str literal (filter type_facts where
    //      type_str contains '[') + (c) variable cluster (stack vars
    //      sorted by stack_offset → diffs/gcd raw arithmetic).
    // (a) op_str source DEFERRED v2 (analyze body has no instructions[]).
    //
    // R-9 / Step 3 naming hygiene: contract test ALSO asserts that
    //   stdout MUST NOT contain "stride" / "array" / "element_type"
    //   tokens — AURA emits arithmetic ("offsets"/"diffs"/"gcd") and
    //   raw engine literals only; analysis vocabulary belongs to the
    //   user / LLM.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " array-candidates --func "
                      + addr_arg + " \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "array-candidates exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == std::string("array-candidates"));
    CHECK(get_number(root, "function_addr") == entry);

    cJSON *cands = cJSON_GetObjectItem(root, "candidates");
    REQUIRE_MESSAGE(cJSON_IsArray(cands),
                    "candidates must be an array");
    cJSON *clusters = cJSON_GetObjectItem(root, "variable_clusters");
    REQUIRE_MESSAGE(cJSON_IsArray(clusters),
                    "variable_clusters must be an array");
    cJSON *hints = cJSON_GetObjectItem(root, "type_hints");
    REQUIRE_MESSAGE(cJSON_IsArray(hints),
                    "type_hints must be an array");

    // (a) op_str source deferred — candidates may be empty.
    // For minimal fixtures variable_clusters/type_hints may also be 0.
    if (cJSON_GetArraySize(clusters) > 0) {
        cJSON *c0 = cJSON_GetArrayItem(clusters, 0);
        REQUIRE(c0 != nullptr);
        REQUIRE(cJSON_IsArray(cJSON_GetObjectItem(c0, "offsets")));
        REQUIRE(cJSON_IsArray(cJSON_GetObjectItem(c0, "diffs")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "gcd")));
    }
    if (cJSON_GetArraySize(hints) > 0) {
        cJSON *h0 = cJSON_GetArrayItem(hints, 0);
        REQUIRE(h0 != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(h0, "var_id")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(h0, "type_str")));
    }

    // R-9 / D2 naming-hygiene regression guard: forbidden analysis tokens
    // must NOT appear anywhere in the JSON. Engine literal "type_str"
    // values may legitimately contain "[" / "]" / "*" — we forbid the
    // English vocabulary tokens AURA itself would have to synthesize.
    CHECK(r.stdout_.find("stride") == std::string::npos);
    CHECK(r.stdout_.find("element_type") == std::string::npos);
    // "array" allowed only if it appears inside an engine type literal
    // (e.g. some compilers might emit "array of ..."), which we accept
    // as engine-verbatim. To stay strict in v1 we still forbid the
    // literal token — the heuristic emits structural keys only.
    CHECK(r.stdout_.find("\"array\"") == std::string::npos);
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: propagate-type --func dry-run emits candidates body (Phase 11.4.3)") {
    // PP1 / ADR-0045 — display-only path. Caller-function rooted.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // 1) analyze → first function entry.
    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    // 2) propagate-type at that entry (dry-run default).
    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " propagate-type --func "
                      + addr_arg
                      + " --target-type \"UserStruct*\" \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "propagate-type exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "propagate-type");
    CHECK(get_number(root, "function_addr") == entry);
    CHECK(get_string(root, "target_type") == std::string("UserStruct*"));
    cJSON *dryRun = cJSON_GetObjectItem(root, "dry_run");
    CHECK(cJSON_IsBool(dryRun));
    CHECK(cJSON_IsTrue(dryRun));
    cJSON *arr = cJSON_GetObjectItem(root, "candidates");
    REQUIRE_MESSAGE(cJSON_IsArray(arr),
                    "candidates must be an array");
    // For minimal fixtures the first function may have 0 candidates
    // (no resolved call_edges out of it). Contract test verifies shape.
    if (cJSON_GetArraySize(arr) > 0) {
        cJSON *c0 = cJSON_GetArrayItem(arr, 0);
        REQUIRE(c0 != nullptr);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "candidate_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "var_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "function_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "call_site_addr")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(c0, "old_type")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(c0, "new_type")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "distance")));
        CHECK(get_string(c0, "source") == std::string("callee_param"));
        CHECK(get_string(c0, "new_type") == std::string("UserStruct*"));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: propagate-type --apply --all opens project store") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);

    fs::path tmp = fs::temp_directory_path() /
                   fs::path("aura_cli_smoke_prop_apply");
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " propagate-type --func "
                      + addr_arg
                      + " --target-type \"UserStruct*\" --apply --all "
                      + "--project \"" + tmp.string() + "\" \"" +
                      fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "propagate-type apply exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "propagate-type");
    cJSON *dryRun = cJSON_GetObjectItem(root, "dry_run");
    CHECK(cJSON_IsFalse(dryRun));
    CHECK(cJSON_IsNumber(cJSON_GetObjectItem(root, "applied_count")));
    CHECK(cJSON_IsNumber(cJSON_GetObjectItem(root, "skipped_count")));
    CHECK(fs::exists(tmp / "aura.db"));
    cJSON_Delete(root);
    fs::remove_all(tmp);
}

TEST_CASE("cli_smoke: propagate-type --apply requires explicit selection") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) +
                      " propagate-type --func 0x401000 "
                      "--target-type \"UserStruct*\" --apply \"" +
                      fixture + "\"");
    CHECK(r.exit_code == 2);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "missing_candidate_selection");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: propagate-type --candidate-ids validates range") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    fs::path tmp = fs::temp_directory_path() /
                   fs::path("aura_cli_smoke_prop_bad_id");
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    CmdResult r = run(aura_invocation(rizin) +
                      " propagate-type --func 0x401000 "
                      "--target-type \"UserStruct*\" --apply "
                      "--candidate-ids 999999 --project \"" +
                      tmp.string() + "\" \"" + fixture + "\"");
    CHECK(r.exit_code == 2);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "candidate_id_out_of_range");
    cJSON_Delete(root);
    fs::remove_all(tmp);
}

TEST_CASE("cli_smoke: label-candidates --func emits ranked candidates (Phase 11.4.2)") {
    // PP4 / ADR-0044: display-only path. heuristic (a) string + (b) import.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // 1) analyze → first function entry.
    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    // 2) label-candidates at that entry.
    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " label-candidates --func "
                      + addr_arg + " \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "label-candidates exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "label-candidates");
    CHECK(get_number(root, "function_addr") == entry);
    cJSON *arr = cJSON_GetObjectItem(root, "candidates");
    REQUIRE_MESSAGE(cJSON_IsArray(arr),
                    "candidates must be an array");
    // For the test fixtures, the first function may have 0 candidates
    // (no string/import xrefs from there). The contract test verifies
    // shape and bounds: array length ≤ 5, each entry has the canonical
    // shape if present.
    CHECK(cJSON_GetArraySize(arr) <= 5);
    if (cJSON_GetArraySize(arr) > 0) {
        cJSON *c0 = cJSON_GetArrayItem(arr, 0);
        REQUIRE(c0 != nullptr);
        CHECK(cJSON_IsString(cJSON_GetObjectItem(c0, "name")));
        CHECK(cJSON_IsString(cJSON_GetObjectItem(c0, "source")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(c0, "confidence")));
        REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(c0, "evidence")));
        const std::string src = get_string(c0, "source");
        CHECK((src == "string" || src == "import"));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: cfg --func emits blocks+edges body (Phase 11.3.8)") {
    // P2.F3 C2 per ADR-0041: data ownership in analyze body, CLI filters
    // by function_id and emits {blocks[], edges[]}.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) { MESSAGE("SKIP: no rizin binary"); return; }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // 1) analyze to find a function entry that has at least one block.
    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    // 2) cfg at that entry.
    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " cfg --func "
                      + addr_arg + " \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "cfg exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "cfg");
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    CHECK(get_number(body, "function_addr") == entry);
    cJSON *blocks = cJSON_GetObjectItem(body, "blocks");
    cJSON *edges  = cJSON_GetObjectItem(body, "edges");
    REQUIRE(cJSON_IsArray(blocks));
    REQUIRE(cJSON_IsArray(edges));
    // Note: the PE fixture (Windows path) currently surfaces 0 blocks /
    // 0 edges from rizin — Phase 2A backend limitation tracked in the
    // ROADMAP. ELF path yields ≥1 block. The contract test verifies the
    // shape: array exists, and IF non-empty each entry has the canonical
    // record shape.
    if (cJSON_GetArraySize(blocks) > 0) {
        cJSON *b0 = cJSON_GetArrayItem(blocks, 0);
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(b0, "block_id")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(b0, "start")));
        CHECK(cJSON_IsNumber(cJSON_GetObjectItem(b0, "end")));
        REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(b0, "provenance")));
    }
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: disasm --func emits per-instruction body (Phase 11.3.7)") {
    // Phase 11.3.7 (P2.F2 C2): `aura disasm --func <addr>` runs rizin pdfj
    // through the DISASM dispatch and returns the AuraRizinDisasmBody as
    // JSON. Picks the first function from analyze() to find a real entry.
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // 1) analyze to find a function entry to disassemble.
    CmdResult ar = run(aura_invocation(rizin) + " analyze \"" + fixture + "\"");
    REQUIRE_MESSAGE(ar.exit_code == 0, "analyze exit=", ar.exit_code);
    cJSON *aroot = parse_or_fail(ar.stdout_);
    cJSON *abody = cJSON_GetObjectItem(aroot, "body");
    REQUIRE(abody != nullptr);
    cJSON *fns = cJSON_GetObjectItem(abody, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *fn0 = cJSON_GetArrayItem(fns, 0);
    double entry = get_number(fn0, "entry");
    cJSON_Delete(aroot);
    REQUIRE(entry > 0.0);

    // 2) disasm at that entry.
    char addr_arg[32];
    snprintf(addr_arg, sizeof(addr_arg), "0x%llx",
             (unsigned long long)(uint64_t)entry);
    CmdResult r = run(aura_invocation(rizin) + " disasm --func "
                      + addr_arg + " \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "disasm exit=", r.exit_code,
                    " out=", r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "disasm");
    cJSON *body = cJSON_GetObjectItem(root, "body");
    REQUIRE(body != nullptr);
    // Phase 11.6 T1: body schema v2 — adds `text` field carrying rizin
    // `pdf` (annotated disassembly with asm.lines flow arrows). Existing
    // `instructions[]` view remains backward-compatible.
    CHECK(get_number(body, "version") == 2.0);
    CHECK(get_number(body, "function_addr") == entry);
    cJSON *txt = cJSON_GetObjectItem(body, "text");
    REQUIRE_MESSAGE(cJSON_IsString(txt),
                    "body.text must be a string (Phase 11.6 T1)");
    const std::string textBlob(txt->valuestring ? txt->valuestring : "");
    // The text MUST contain the function entry's address as a hex prefix
    // somewhere — guards against blank/garbage emission.
    char hex_needle[24];
    snprintf(hex_needle, sizeof(hex_needle), "0x%08llx",
             (unsigned long long)(uint64_t)entry);
    CHECK_MESSAGE(textBlob.find(hex_needle) != std::string::npos,
                  "body.text expected to contain ", hex_needle,
                  " — got: ", textBlob.substr(0, 200));
    cJSON *ins = cJSON_GetObjectItem(body, "instructions");
    REQUIRE_MESSAGE(cJSON_IsArray(ins),
                    "body.instructions must be an array");
    double ic = get_number(body, "instructions_count");
    CHECK(static_cast<int>(ic) == cJSON_GetArraySize(ins));
    REQUIRE(cJSON_GetArraySize(ins) >= 1);

    cJSON *first = cJSON_GetArrayItem(ins, 0);
    REQUIRE(first != nullptr);
    CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "addr")));
    CHECK(cJSON_IsNumber(cJSON_GetObjectItem(first, "size")));
    CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "bytes")));
    CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "mnemonic")));
    CHECK(cJSON_IsString(cJSON_GetObjectItem(first, "op_str")));
    REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(first, "provenance")));
    cJSON *prov = cJSON_GetObjectItem(first, "provenance");
    CHECK(get_string(prov, "source") == std::string("rizin"));
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: info emits a valid binary fingerprint") {
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation("/dev/null") + " info \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_number(root, "aura_schema") == 1.0);
    CHECK(get_string(root, "command") == "info");
    cJSON *fp = cJSON_GetObjectItem(root, "fingerprint");
    REQUIRE(fp != nullptr);
    CHECK(get_number(fp, "file_size") > 0.0);
    std::string sha = get_string(fp, "sha256");
    CHECK(sha.size() == 64);  // hex digest
    std::string fmt = get_string(fp, "format_kind");
    CHECK((fmt == "elf" || fmt == "pe" || fmt == "mach-o"));
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: engines command lists rizin reference engine") {
    CmdResult r = run("\"" + aura_binary() + "\" --compact engines");
    REQUIRE(r.exit_code == 0);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "engines");
    cJSON *list = cJSON_GetObjectItem(root, "engines");
    REQUIRE(cJSON_IsArray(list));
    REQUIRE(cJSON_GetArraySize(list) >= 1);
    cJSON *first = cJSON_GetArrayItem(list, 0);
    CHECK(get_string(first, "id") == "rizin");
    CHECK(get_string(first, "role") == "reference");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: failure — unknown subcommand exits non-zero") {
    CmdResult r = run("\"" + aura_binary() + "\" not-a-real-command 2>&1");
    CHECK(r.exit_code != 0);  // CLI11 returns 105 for missing required subcmd
}

TEST_CASE("cli_smoke: failure — analyze on nonexistent file errors out") {
    CmdResult r = run("\"" + aura_binary() +
                      "\" analyze /no/such/path/0xdeadbeef.bin 2>&1");
    CHECK(r.exit_code != 0);
    // CLI11's CLI::ExistingFile validator rejects with exit code 105.
}

TEST_CASE("cli_smoke: failure — llm-context with bad --func errors gracefully") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));
    CmdResult r = run(aura_invocation(rizin) +
                      " llm-context \"" + fixture + "\" --func 0xffffffff");
    CHECK(r.exit_code == 1);  // function_not_found
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "function_not_found");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: override list creates empty store + reports fingerprint") {
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // Use a unique tmp project dir under build dir.
    fs::path tmp = fs::temp_directory_path() / fs::path("aura_cli_smoke_proj");
    fs::remove_all(tmp);  // clean state
    fs::create_directories(tmp);

    CmdResult r = run("\"" + aura_binary() + "\" --compact override list \"" +
                      fixture + "\" --project \"" + tmp.string() + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=", r.stdout_.substr(0, 200));
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "command") == "override list");
    CHECK(get_number(root, "total_rows_in_store") == 0.0);
    cJSON *fp = cJSON_GetObjectItem(root, "fingerprint");
    REQUIRE(fp != nullptr);
    CHECK(std::string(get_string(fp, "sha256")).size() == 64);
    cJSON_Delete(root);

    // aura.db created inside the directory
    CHECK(fs::exists(tmp / "aura.db"));
    fs::remove_all(tmp);
}

TEST_CASE("cli_smoke: override get on empty store returns not_found exit 1") {
    // Intent: with an empty project store, `override get` MUST return
    // exit=1 + error="not_found". We use --no-analyze so the skeleton
    // key (fingerprint + addr) is built without dispatching ANALYZE,
    // sidestepping the cross-fixture problem where a hardcoded entry
    // address (e.g. 0x40117b) might not be a real function on every
    // platform's fixture (PE vs ELF have different layouts). The
    // skeleton-key path still hits `aura_override_store_get` against
    // the empty store and surfaces the same `not_found` we care about.
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));
    fs::path tmp = fs::temp_directory_path() / fs::path("aura_cli_smoke_proj2");
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    CmdResult r = run("\"" + aura_binary() +
                      "\" --compact override get \"" + fixture +
                      "\" --func 0x40117b --no-analyze --project \"" +
                      tmp.string() + "\"");
    CHECK(r.exit_code == 1);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "not_found");
    cJSON_Delete(root);
    fs::remove_all(tmp);
}

TEST_CASE("cli_smoke: override missing --project returns usage exit 2") {
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));
    CmdResult r = run("\"" + aura_binary() +
                      "\" --compact override list \"" + fixture + "\"");
    CHECK(r.exit_code == 2);
    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_string(root, "error") == "missing_project");
    cJSON_Delete(root);
}

TEST_CASE("cli_smoke: override put + get round-trip with --no-analyze") {
    // The skeleton path (Q10 Path B) — fast and works without the engine,
    // so it's the test-friendly variant. The default (Path A) requires a
    // working Rizin and is exercised by the dedicated ANALYZE-path test.
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));
    fs::path tmp = fs::temp_directory_path() / fs::path("aura_cli_smoke_proj3");
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    CmdResult put = run("\"" + aura_binary() +
                        "\" --compact override put \"" + fixture +
                        "\" --func 0x40117b --rename test_main --project \"" +
                        tmp.string() + "\" --no-analyze");
    REQUIRE_MESSAGE(put.exit_code == 0,
                    "exit=", put.exit_code, " out=",
                    put.stdout_.substr(0, 200));
    cJSON *root = parse_or_fail(put.stdout_);
    CHECK(get_string(root, "command") == "override put");
    CHECK(get_string(root, "rename") == "test_main");
    CHECK(get_string(root, "confidence") == "weak");
    cJSON *analyzed = cJSON_GetObjectItem(root, "analyzed");
    CHECK(cJSON_IsFalse(analyzed));
    cJSON_Delete(root);

    CmdResult get = run("\"" + aura_binary() +
                        "\" --compact override get \"" + fixture +
                        "\" --func 0x40117b --project \"" +
                        tmp.string() + "\" --no-analyze");
    REQUIRE(get.exit_code == 0);
    cJSON *root2 = parse_or_fail(get.stdout_);
    cJSON *ov = cJSON_GetObjectItem(root2, "override");
    REQUIRE(ov != nullptr);
    cJSON *payload = cJSON_GetObjectItem(ov, "payload");
    REQUIRE(payload != nullptr);
    CHECK(get_string(payload, "kind") == "rename");
    CHECK(get_string(payload, "text") == "test_main");
    cJSON_Delete(root2);

    CmdResult del = run("\"" + aura_binary() +
                        "\" --compact override delete \"" + fixture +
                        "\" --func 0x40117b --project \"" +
                        tmp.string() + "\" --no-analyze");
    REQUIRE(del.exit_code == 0);
    cJSON *root3 = parse_or_fail(del.stdout_);
    CHECK(get_string(root3, "result") == "deleted");
    cJSON_Delete(root3);

    fs::remove_all(tmp);
}

TEST_CASE("cli_smoke: llm-context emits a binary-mode payload") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    CmdResult r = run(aura_invocation(rizin) +
                      " llm-context \"" + fixture + "\"");
    REQUIRE_MESSAGE(r.exit_code == 0,
                    "exit=", r.exit_code, " out=",
                    r.stdout_.substr(0, 200));

    cJSON *root = parse_or_fail(r.stdout_);
    CHECK(get_number(root, "aura_schema") == 1.0);
    CHECK(get_string(root, "command") == "llm-context");
    CHECK(get_string(root, "mode") == "binary");
    CHECK(get_number(root, "functions_count") >= 1.0);
    cJSON *fns = cJSON_GetObjectItem(root, "functions");
    REQUIRE(cJSON_IsArray(fns));
    REQUIRE(cJSON_GetArraySize(fns) >= 1);
    cJSON *first = cJSON_GetArrayItem(fns, 0);
    REQUIRE(first != nullptr);
    // each card must have callers + callees arrays + provenance
    REQUIRE(cJSON_IsArray(cJSON_GetObjectItem(first, "callers")));
    REQUIRE(cJSON_IsArray(cJSON_GetObjectItem(first, "callees")));
    REQUIRE(cJSON_IsObject(cJSON_GetObjectItem(first, "provenance")));
    cJSON_Delete(root);
}
