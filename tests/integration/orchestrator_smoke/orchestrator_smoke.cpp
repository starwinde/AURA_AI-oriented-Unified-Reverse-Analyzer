// orchestrator_smoke.cpp — Phase 10 reference engine integration gate.
//
// Pipeline:
//   fixture binary → orchestrator → Rizin adapter → AuraRizinAnalyzeBody
//                  → override store (in-memory SQLite) round-trip
//                  → cJSON serialization with handwritten schema validation
//
// Asserts the four invariants defined in CONTEXT.md "Invariant gate":
//   I1 — functions_count >= 1
//   I2 — at least one function with non-zero entry address (entrypoint)
//   I3 — override rename round-trip via in-memory SQLite store
//   I4 — unified-model JSON serialization passes handwritten schema check
//
// Reference engine = Rizin (ADR-0031). Test SKIPs gracefully when neither
// AURA_RIZIN_BIN env var nor the manifest-resolved binary at
// third_party/rizin/<version>/bin/rizin{,.exe} is executable — CI is
// expected to provide one of those (CONTEXT.md "Tier 1 gate").

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "cJSON.h"
#include "engine_request.h"
#include "orchestrator.h"
#include "override_identity.h"
#include "override_store.h"
#include "rizin_adapter.h"
#include "string_protection_store.h"

namespace fs = std::filesystem;

// ── fixture / rizin discovery ──────────────────────────────────────────────

static std::string repo_root() {
    // Test binary lives under <root>/build*/...; walk up until we find
    // CONTEXT.md. Fallback to AURA_REPO_ROOT env.
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

static std::string discover_rizin_bin() {
    if (const char *env = std::getenv("AURA_RIZIN_BIN")) {
        if (fs::exists(env)) return env;
    }
    fs::path root = repo_root();
#ifdef _WIN32
    fs::path candidate = root / "third_party/rizin/0.8.2/bin/rizin.exe";
#else
    fs::path candidate = root / "third_party/rizin/0.8.2/bin/rizin";
#endif
    if (fs::exists(candidate)) return candidate.string();
    return {};
}

// ── invariant helpers ──────────────────────────────────────────────────────

static cJSON *body_to_json(const AuraRizinAnalyzeBody *body) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "magic", static_cast<double>(body->magic));
    cJSON_AddNumberToObject(root, "version", static_cast<double>(body->version));
    cJSON_AddNumberToObject(root, "functions_count",
                            static_cast<double>(body->functions_count));
    cJSON_AddNumberToObject(root, "symbols_count",
                            static_cast<double>(body->symbols_count));
    cJSON *fns = cJSON_AddArrayToObject(root, "functions");
    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);
    for (size_t i = 0; i < body->functions_count && i < 8; ++i) {
        cJSON *fn = cJSON_CreateObject();
        cJSON_AddNumberToObject(fn, "entry",
                                static_cast<double>(funcs[i].entry));
        cJSON_AddNumberToObject(fn, "size",
                                static_cast<double>(funcs[i].size));
        cJSON_AddStringToObject(fn, "name", funcs[i].name[0] ? funcs[i].name : "");
        cJSON_AddItemToArray(fns, fn);
    }
    return root;
}

// Handwritten schema validator (no JSON Schema lib; Q8 decision).
// Returns "" on success, error message on failure.
static std::string validate_unified_json(const cJSON *root) {
    if (!cJSON_IsObject(root)) return "root not object";
    auto require_num = [&](const char *k) -> std::string {
        cJSON *v = cJSON_GetObjectItem(const_cast<cJSON *>(root), k);
        if (!v || !cJSON_IsNumber(v)) return std::string("missing/non-number: ") + k;
        return {};
    };
    for (const char *k : {"magic", "version", "functions_count", "symbols_count"}) {
        auto e = require_num(k);
        if (!e.empty()) return e;
    }
    cJSON *fns = cJSON_GetObjectItem(const_cast<cJSON *>(root), "functions");
    if (!fns || !cJSON_IsArray(fns)) return "missing/non-array: functions";
    cJSON *fn = nullptr;
    cJSON_ArrayForEach(fn, fns) {
        if (!cJSON_IsObject(fn)) return "function entry not object";
        cJSON *entry = cJSON_GetObjectItem(fn, "entry");
        cJSON *size  = cJSON_GetObjectItem(fn, "size");
        cJSON *name  = cJSON_GetObjectItem(fn, "name");
        if (!entry || !cJSON_IsNumber(entry)) return "function.entry bad";
        if (!size  || !cJSON_IsNumber(size))  return "function.size bad";
        if (!name  || !cJSON_IsString(name))  return "function.name bad";
    }
    return {};
}

// ── test ───────────────────────────────────────────────────────────────────

TEST_CASE("string_protection_store: strings aliases and findings stay separate") {
    AuraStringProtectionStore *store =
        aura_string_protection_store_open(":memory:");
    REQUIRE(store != nullptr);

    AuraStoredStringRecord s{};
    std::strncpy(s.binary_fingerprint,
                 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                 sizeof(s.binary_fingerprint) - 1);
    std::strncpy(s.engine_id, "rizin", sizeof(s.engine_id) - 1);
    s.string_id = 1;
    s.addr = 0x140021010;
    s.length = 23;
    std::strncpy(s.encoding, "ascii", sizeof(s.encoding) - 1);
    std::strncpy(s.section, ".data", sizeof(s.section) - 1);
    std::strncpy(s.original_text, "alice.smith@example.com",
                 sizeof(s.original_text) - 1);
    std::strncpy(s.source, "rizin", sizeof(s.source) - 1);
    REQUIRE(aura_string_protection_store_put_string(store, &s) == 0);

    AuraStringOverrideRecord ov{};
    std::strncpy(ov.binary_fingerprint, s.binary_fingerprint,
                 sizeof(ov.binary_fingerprint) - 1);
    ov.string_addr = s.addr;
    std::strncpy(ov.original_hash,
                 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
                 sizeof(ov.original_hash) - 1);
    std::strncpy(ov.alias, "customer_email", sizeof(ov.alias) - 1);
    std::strncpy(ov.mask_token, "[EMAIL_1]", sizeof(ov.mask_token) - 1);
    ov.display_mode = 1;
    REQUIRE(aura_string_protection_store_put_override(store, &ov) == 0);

    AuraStringOverrideRecord got_override{};
    REQUIRE(aura_string_protection_store_get_override(
                store, ov.binary_fingerprint, ov.string_addr,
                ov.original_hash, &got_override) == 0);
    CHECK(std::string(got_override.alias) == "customer_email");
    CHECK(std::string(got_override.mask_token) == "[EMAIL_1]");
    CHECK(got_override.display_mode == 1);

    AuraStringProtectionFinding f{};
    std::strncpy(f.binary_fingerprint, s.binary_fingerprint,
                 sizeof(f.binary_fingerprint) - 1);
    f.string_addr = s.addr;
    std::strncpy(f.detector_id, "pii-rule/email", sizeof(f.detector_id) - 1);
    std::strncpy(f.finding_kind, "email", sizeof(f.finding_kind) - 1);
    f.start_offset = 0;
    f.end_offset = 23;
    f.confidence = 0.99;
    std::strncpy(f.mask_token, "[EMAIL_1]", sizeof(f.mask_token) - 1);
    REQUIRE(aura_string_protection_store_put_finding(store, &f) == 0);

    CHECK(aura_string_protection_store_count_strings(store) == 1);
    CHECK(aura_string_protection_store_count_overrides(store) == 1);
    CHECK(aura_string_protection_store_count_findings(store) == 1);

    aura_string_protection_store_close(store);
}

TEST_CASE("orchestrator_smoke: Rizin → unified model → override → JSON") {
    const std::string rizin = discover_rizin_bin();
    if (rizin.empty()) {
        MESSAGE("SKIP: no rizin binary (set AURA_RIZIN_BIN or run "
                "scripts/fetch_external_tools.{sh,ps1})");
        return;
    }
    const std::string fixture = fixture_path();
    REQUIRE(fs::exists(fixture));

    // ── orchestrator + Rizin adapter ───────────────────────────────────────
    AuraOrchestrator *orch = aura_orchestrator_create();
    REQUIRE(orch != nullptr);

    AuraRizinAdapterConfig cfg{};
    cfg.exec_path = rizin.c_str();
    cfg.timeout_s = 30;
    REQUIRE(aura_orchestrator_register_rizin(orch, &cfg) == 0);

    AuraEngineRequest req{};
    req.type = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = fixture.c_str();
    req.addr = 0;
    req.arch_or_null = "x86_64";

    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(orch, "rizin", &req, &resp);
    REQUIRE_MESSAGE(st == AURA_ENGINE_OK,
                    "dispatch failed status=", static_cast<int>(st));
    REQUIRE(resp.body != nullptr);
    REQUIRE(resp.body_size >= sizeof(AuraRizinAnalyzeBody));

    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);
    REQUIRE(body->magic == AURA_RIZIN_ANALYZE_BODY_MAGIC);

    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);

    // ── I1 — functions_count >= 1 ──────────────────────────────────────────
    SUBCASE("I1 — functions_count >= 1") {
        CHECK(body->functions_count >= 1);
    }

    // ── I2 — at least one entry-pointed function ───────────────────────────
    SUBCASE("I2 — entrypoint present") {
        bool any_entry = false;
        for (size_t i = 0; i < body->functions_count; ++i) {
            if (funcs[i].entry != 0) { any_entry = true; break; }
        }
        CHECK(any_entry);
    }

    // ── I3 — override rename round-trip ────────────────────────────────────
    SUBCASE("I3 — override store round-trip") {
        REQUIRE(body->functions_count >= 1);
        const AuraFunctionRecord &target = funcs[0];

        AuraOverrideBinaryFingerprint fp{};
        fp.file_size = fs::file_size(fixture);
        std::strncpy(fp.format_kind,
#ifdef _WIN32
                     "pe",
#else
                     "elf",
#endif
                     sizeof(fp.format_kind) - 1);

        const AuraEngineManifest *manifest = aura_rizin_adapter_manifest();
        REQUIRE(manifest != nullptr);

        AuraOverrideKey key = aura_override_key_from_function_record(
            &target, manifest, &fp);
        // Confidence may be WEAK without engine-provided stable id; that's
        // fine for a store round-trip — the put/get path doesn't gate on it.

        AuraOverrideStore *store = aura_override_store_open(":memory:");
        REQUIRE(store != nullptr);

        AuraOverrideRecord rec{};
        rec.key = key;
        rec.payload.kind = AURA_OVERRIDE_PAYLOAD_RENAME;
        std::strncpy(rec.payload.text, "aura_test_renamed",
                     AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
        rec.status = AURA_OVERRIDE_STATUS_PENDING;

        REQUIRE(aura_override_store_put(store, &rec) == 0);
        CHECK(aura_override_store_count(store) == 1);

        AuraOverrideRecord got{};
        REQUIRE(aura_override_store_get(store, &key, &got) == 0);
        CHECK(got.payload.kind == AURA_OVERRIDE_PAYLOAD_RENAME);
        CHECK(std::string(got.payload.text) == "aura_test_renamed");
        CHECK(aura_override_key_same_target(&got.key, &key));

        aura_override_store_close(store);
    }

    // ── I4 — JSON serialization + handwritten schema check ────────────────
    SUBCASE("I4 — unified model JSON schema") {
        cJSON *json = body_to_json(body);
        REQUIRE(json != nullptr);
        std::string err = validate_unified_json(json);
        CHECK_MESSAGE(err.empty(), "schema validation: ", err);
        cJSON_Delete(json);
    }

    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
}
