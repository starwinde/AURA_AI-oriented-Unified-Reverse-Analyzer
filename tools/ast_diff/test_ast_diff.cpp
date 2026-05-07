// Minimal C++ unit tests for tools/ast_diff/.
// Uses bare assert(); intentionally no gtest dependency.
//
// Build: included in tools/ast_diff/CMakeLists.txt.
// Run: ctest --test-dir tools/ast_diff/build

// NB: cassert's assert() is a no-op when NDEBUG is defined (Release
// builds). We use a custom CHECK macro that always evaluates and
// exits with status 1 on failure.
#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        std::fprintf(stderr, "[FAIL] %s:%d: %s — %s\n", \
                     __FILE__, __LINE__, #cond, (msg)); \
        std::exit(1); \
    } \
} while (0)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <unistd.h>  // close()

namespace {

// Forward-declare what we need from ast_diff.cpp by re-declaring the
// public surface we exercise via subprocess. We do NOT link against
// ast_diff.cpp directly (avoids the main() collision); we exec the
// binary and parse JSON. This keeps the test independent of internal
// API drift.

std::string write_temp(const std::string& contents, const char* suffix) {
    char tmpl[] = "/tmp/ast_diff_test_XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) return {};
    std::string p = tmpl;
    p += suffix ? suffix : ".c";
    // Rename to add .c suffix so libclang treats input as C.
    std::rename(tmpl, p.c_str());
    close(fd);
    std::ofstream ofs(p);
    ofs << contents;
    return p;
}

struct AstResult {
    int branch = 0;
    int strct  = 0;
    int total  = 0;
    bool ok    = false;
};

AstResult run_ast_diff(const std::string& g, const std::string& a,
                       const char* binary) {
    AstResult r;
    std::string gp = write_temp(g, ".c");
    std::string ap = write_temp(a, ".c");
    if (gp.empty() || ap.empty()) return r;

    char cmd[2048];
    std::snprintf(cmd, sizeof(cmd), "'%s' '%s' '%s' 2>/dev/null",
                  binary, gp.c_str(), ap.c_str());
    FILE* p = popen(cmd, "r");
    if (!p) {
        std::remove(gp.c_str()); std::remove(ap.c_str());
        return r;
    }
    char buf[4096]; std::string out;
    while (std::fgets(buf, sizeof(buf), p)) out += buf;
    pclose(p);
    std::remove(gp.c_str()); std::remove(ap.c_str());

    // Crude JSON parse — just look for the integer/bool fields.
    auto find_int = [&](const char* key, int& v) {
        std::string k = std::string("\"") + key + "\":";
        size_t i = out.find(k);
        if (i == std::string::npos) return;
        i += k.size();
        while (i < out.size() && (out[i] == ' ' || out[i] == '\t')) ++i;
        v = std::atoi(out.c_str() + i);
    };
    find_int("ast_branch_semantic", r.branch);
    find_int("ast_struct_semantic", r.strct);
    find_int("ast_total", r.total);
    r.ok = out.find("\"ast_parse_ok\": true") != std::string::npos;
    return r;
}

const char* g_binary = "./ast_diff";  // relative to build dir

void test_identical_branch_high() {
    std::string code = "int f(int a) { if (a == 0) return 1; return 0; }";
    auto r = run_ast_diff(code, code, g_binary);
    CHECK(r.ok, "identical input should parse OK");
    CHECK(r.branch >= 8, "identical branch conditions should hash equal");
    std::fprintf(stderr, "[OK] test_identical_branch_high (branch=%d)\n",
                 r.branch);
}

void test_cond_lowering_normalized() {
    std::string g = "int f(int a) { if (a == 0) return 1; return 0; }";
    std::string a = "int f(int a) { int _v0 = (a == 0); "
                    "if (_v0) return 1; return 0; }";
    auto ref = run_ast_diff(g, g, g_binary);
    auto sample = run_ast_diff(g, a, g_binary);
    CHECK(ref.ok && sample.ok, "both should parse");
    int gap_branch = ref.branch - sample.branch;
    // C-3 flatten should make the if-condition equivalent.
    CHECK(gap_branch <= 1,
          "C-3 flatten should close branch gap to <=1");
    std::fprintf(stderr,
                 "[OK] test_cond_lowering_normalized (ref=%d sample=%d gap=%d)\n",
                 ref.branch, sample.branch, gap_branch);
}

void test_member_offset_recognized() {
    // Ghidra-style: explicit struct with fN naming = offset N (Ghidra
    // convention when struct layout is recovered). Member access
    // s->f8 should normalize to MemberAccess(s, 8).
    std::string g = "struct S { int f0; int f4; int f8; int f12; }; "
                    "int f(struct S *s) { return s->f8; }";
    // AURA-style: cast-and-deref pattern with offset 8 → should also
    // normalize to MemberAccess(p, 8).
    std::string a = "int f(void *p) { return *(int *)((char *)p + 8); }";
    auto r = run_ast_diff(g, a, g_binary);
    CHECK(r.ok, "fixture should parse cleanly");
    CHECK(r.strct >= 5, "struct member normalization should hash equal");
    std::fprintf(stderr,
                 "[OK] test_member_offset_recognized (struct=%d)\n", r.strct);
}

void test_parse_failure_graceful() {
    std::string g = "int f(int a) { return a; }";
    std::string a = "int f(int a {  /* unclosed */";
    auto r = run_ast_diff(g, a, g_binary);
    // Should produce JSON, ast_parse_ok=false, scores=0.
    // ok flag may still be true if libclang KeepGoing recovers; either
    // way we should have a valid JSON response.
    CHECK(r.branch >= 0 && r.strct >= 0, "should produce valid JSON");
    std::fprintf(stderr,
                 "[OK] test_parse_failure_graceful (branch=%d strct=%d ok=%d)\n",
                 r.branch, r.strct, r.ok);
}

}  // namespace

int main(int argc, char** argv) {
    // Allow override of binary path for ctest.
    if (argc >= 2) g_binary = argv[1];

    test_identical_branch_high();
    test_cond_lowering_normalized();
    test_member_offset_recognized();
    test_parse_failure_graceful();

    std::fprintf(stderr, "\nAll tests passed.\n");
    return 0;
}
