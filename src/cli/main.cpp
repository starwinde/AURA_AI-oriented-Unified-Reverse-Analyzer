// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0
//
// src/cli/main.cpp — `aura` CLI entry point (Phase 11.1).
//
// Frontend topology: see ADR-0033. CLI is one of two co-equal frontends
// over `aura_core`. v1 surface (Q5):
//
//   aura analyze <binary>     — ANALYZE dispatch → unified model JSON
//   aura info    <binary>     — binary fingerprint JSON
//   aura llm-context <binary> — LLM payload JSON (Slice D)
//
// All output is JSON on stdout with a stable schema header
//   { "aura_schema": 1, ... }
// Diagnostics / progress / warnings → stderr.
//
// Engine resolution (Q10): --engine <id> if specified, otherwise the
// orchestrator's primary set policy chooses (currently Rizin for ANALYZE).
//
// Configuration (Q9): no config file in v1. Inputs are CLI flags +
// environment variable fallback (AURA_RIZIN_BIN).

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "aura/safety/string_safety.h"
#include "CLI11.hpp"
#include "cJSON.h"

extern "C" {
#include "engine_request.h"
#include "orchestrator.h"
#include "override_identity.h"
#include "override_store.h"
#include "aura/type_propagation.h"
#include "rizin_adapter.h"
#include "sha256.h"
#include "command_runner_subprocess.h"
#include "engine_probe.h"
#include "probe_registry.h"
}

#include <fstream>
#include <filesystem>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace {

constexpr int kAuraSchemaVersion = 1;
constexpr const char *kVendoredRizinRelWin =
    "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe";
constexpr const char *kVendoredRizinRelPosix =
    "third_party/rizin/0.8.0-static/bin/rizin";
constexpr const char *kVendoredSleighRel =
    "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh";

struct GlobalOpts {
    bool        compact      = false;
    std::string engine_id;       // empty → primary set policy
    std::string rizin_bin_path;  // empty → env, vendored repo path, or PATH
};

// ── helpers ────────────────────────────────────────────────────────────────

static std::string repo_root_for_cli();
static std::string resolve_project_path(const std::string &flag_value,
                                        std::string &err);
static int compute_fingerprint(const std::string &binary,
                               AuraOverrideBinaryFingerprint &out);

cJSON *make_root() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "aura_schema", kAuraSchemaVersion);
    return root;
}

void emit_json(const cJSON *root, bool compact) {
    char *s = compact ? cJSON_PrintUnformatted(const_cast<cJSON *>(root))
                      : cJSON_Print(const_cast<cJSON *>(root));
    if (s) {
        std::fputs(s, stdout);
        std::fputc('\n', stdout);
        std::free(s);
    }
}

void emit_error_json(const char *code, const std::string &msg, bool compact) {
    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "error", code);
    cJSON_AddStringToObject(root, "message", msg.c_str());
    emit_json(root, compact);
    cJSON_Delete(root);
}

struct GuiRpcOpts {
    int         port = 0;
    std::string token;
};

static int gui_rpc_default_port() {
    if (const char *env = std::getenv("AURA_GUI_RPC_PORT")) {
        if (*env) return std::atoi(env);
    }
    return 27654;
}

static std::string gui_rpc_default_token() {
    if (const char *env = std::getenv("AURA_GUI_RPC_TOKEN")) {
        if (*env) return std::string(env);
    }
    return {};
}

#ifdef _WIN32
using AuraSocket = SOCKET;
constexpr AuraSocket kInvalidSocket = INVALID_SOCKET;
static void close_socket(AuraSocket s) { closesocket(s); }
#else
using AuraSocket = int;
constexpr AuraSocket kInvalidSocket = -1;
static void close_socket(AuraSocket s) { close(s); }
#endif

static bool send_all(AuraSocket sock, const std::string &data,
                     std::string &err) {
    size_t sent = 0;
    while (sent < data.size()) {
        const char *p = data.data() + sent;
#ifdef _WIN32
        const int n = ::send(sock, p, static_cast<int>(data.size() - sent), 0);
#else
        const ssize_t n = ::send(sock, p, data.size() - sent, 0);
#endif
        if (n <= 0) {
            err = "send failed";
            return false;
        }
        sent += static_cast<size_t>(n);
    }
    return true;
}

static bool recv_line(AuraSocket sock, std::string &line, std::string &err) {
    line.clear();
    char ch = 0;
    while (true) {
#ifdef _WIN32
        const int n = ::recv(sock, &ch, 1, 0);
#else
        const ssize_t n = ::recv(sock, &ch, 1, 0);
#endif
        if (n <= 0) {
            err = "connection closed before response";
            return false;
        }
        if (ch == '\n') return true;
        line.push_back(ch);
        if (line.size() > 16 * 1024 * 1024) {
            err = "response too large";
            return false;
        }
    }
}

static std::string gui_rpc_request_json(const std::string &method,
                                        cJSON *params,
                                        const std::string &token) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "method", method.c_str());
    cJSON_AddStringToObject(root, "token", token.c_str());
    if (params) {
        cJSON_AddItemToObject(root, "params", params);
    } else {
        cJSON_AddItemToObject(root, "params", cJSON_CreateObject());
    }
    char *raw = cJSON_PrintUnformatted(root);
    std::string out = raw ? raw : "";
    if (raw) std::free(raw);
    cJSON_Delete(root);
    out.push_back('\n');
    return out;
}

static int run_gui_rpc(const std::string &method, cJSON *params,
                       const GuiRpcOpts &opts, const GlobalOpts &g,
                       const std::string &command_label) {
    if (opts.port <= 0 || opts.port > 65535) {
        emit_error_json("invalid_gui_rpc_port",
                        "GUI RPC port must be in 1..65535", g.compact);
        if (params) cJSON_Delete(params);
        return 2;
    }
    if (opts.token.empty()) {
        emit_error_json("missing_gui_rpc_token",
                        "set --token or AURA_GUI_RPC_TOKEN", g.compact);
        if (params) cJSON_Delete(params);
        return 2;
    }

#ifdef _WIN32
    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        emit_error_json("winsock_init_failed", "WSAStartup failed", g.compact);
        if (params) cJSON_Delete(params);
        return 1;
    }
#endif

    AuraSocket sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == kInvalidSocket) {
        emit_error_json("gui_rpc_socket_failed", "could not create socket",
                        g.compact);
        if (params) cJSON_Delete(params);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(opts.port));
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    if (::connect(sock, reinterpret_cast<sockaddr *>(&addr),
                  sizeof(addr)) != 0) {
        close_socket(sock);
        emit_error_json("gui_rpc_connect_failed",
                        "could not connect to 127.0.0.1:" +
                            std::to_string(opts.port) +
                            " (start aura-gui with --rpc-port first)",
                        g.compact);
        if (params) cJSON_Delete(params);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    const std::string req = gui_rpc_request_json(method, params, opts.token);
    std::string err;
    std::string resp;
    const bool ok = send_all(sock, req, err) && recv_line(sock, resp, err);
    close_socket(sock);
#ifdef _WIN32
    WSACleanup();
#endif
    if (!ok) {
        emit_error_json("gui_rpc_io_failed", err, g.compact);
        return 1;
    }

    cJSON *rpc = cJSON_ParseWithLength(resp.data(), resp.size());
    if (!rpc) {
        emit_error_json("gui_rpc_bad_json", "GUI RPC returned invalid JSON",
                        g.compact);
        return 1;
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", command_label.c_str());
    cJSON_AddNumberToObject(root, "port", opts.port);
    cJSON_AddItemToObject(root, "rpc", rpc);
    emit_json(root, g.compact);

    cJSON *rpc_ok = cJSON_GetObjectItemCaseSensitive(rpc, "ok");
    const bool success = rpc_ok && cJSON_IsBool(rpc_ok) && cJSON_IsTrue(rpc_ok);
    cJSON_Delete(root);
    return success ? 0 : 1;
}

static void seed_repo_root_env_for_cli() {
    const char *cur = std::getenv("AURA_REPO_ROOT");
    if (cur && *cur) return;

    static std::string root = repo_root_for_cli();
#ifdef _WIN32
    _putenv_s("AURA_REPO_ROOT", root.c_str());
#else
    setenv("AURA_REPO_ROOT", root.c_str(), 1);
#endif
}

static void seed_sleighhome_env_for_cli() {
    const char *cur = std::getenv("SLEIGHHOME");
    if (cur && *cur) return;

    seed_repo_root_env_for_cli();
    namespace fs = std::filesystem;
    const fs::path sleigh_home = fs::path(repo_root_for_cli()) / kVendoredSleighRel;
    if (!fs::exists(sleigh_home)) return;

    static std::string resolved_sleigh_home;
    resolved_sleigh_home = sleigh_home.string();
#ifdef _WIN32
    _putenv_s("SLEIGHHOME", resolved_sleigh_home.c_str());
#else
    setenv("SLEIGHHOME", resolved_sleigh_home.c_str(), 1);
#endif
}

static std::string resolve_rizin_exec_for_cli(const GlobalOpts &g) {
    seed_repo_root_env_for_cli();
    seed_sleighhome_env_for_cli();

    if (!g.rizin_bin_path.empty()) return g.rizin_bin_path;

    char resolved[1024];
#ifdef _WIN32
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              kVendoredRizinRelWin,
                              "rizin", resolved, sizeof(resolved));
#else
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              kVendoredRizinRelPosix,
                              "rizin", resolved, sizeof(resolved));
#endif
    return resolved;
}

// Build an orchestrator with the Rizin adapter registered. NULL on failure.
AuraOrchestrator *build_orchestrator(const GlobalOpts &g, std::string &err) {
    AuraOrchestrator *orch = aura_orchestrator_create();
    if (!orch) {
        err = "orchestrator allocation failed";
        return nullptr;
    }

    AuraRizinAdapterConfig cfg{};
    cfg.timeout_s = 60;
    static std::string resolved_rizin;
    resolved_rizin = resolve_rizin_exec_for_cli(g);
    cfg.exec_path = resolved_rizin.c_str();

    if (aura_orchestrator_register_rizin(orch, &cfg) != 0) {
        aura_orchestrator_destroy(orch);
        err = "rizin adapter registration failed (check --rizin or "
              "AURA_RIZIN_BIN / vendored third_party/rizin)";
        return nullptr;
    }
    return orch;
}

// ── analyze ────────────────────────────────────────────────────────────────

cJSON *finding_to_json(const aura::safety::Finding &finding) {
    cJSON *out = cJSON_CreateObject();
    cJSON_AddStringToObject(out, "detector_id", finding.detector_id.c_str());
    cJSON_AddStringToObject(out, "kind", finding.kind.c_str());
    cJSON_AddNumberToObject(out, "start",
                            static_cast<double>(finding.start));
    cJSON_AddNumberToObject(out, "end", static_cast<double>(finding.end));
    cJSON_AddNumberToObject(out, "confidence", finding.confidence);
    cJSON_AddStringToObject(out, "mask_token", finding.mask_token.c_str());
    return out;
}

cJSON *analyze_body_to_json(
    const AuraRizinAnalyzeBody *body,
    aura::safety::StringProtectionMode string_protection_mode) {
    const bool enable_string_protection =
        string_protection_mode != aura::safety::StringProtectionMode::Off;
    const bool mask_string_protection =
        string_protection_mode == aura::safety::StringProtectionMode::Mask;
    cJSON *out = cJSON_CreateObject();
    cJSON_AddNumberToObject(out, "magic", static_cast<double>(body->magic));
    cJSON_AddNumberToObject(out, "version",
                            static_cast<double>(body->version));
    cJSON_AddNumberToObject(out, "functions_count",
                            static_cast<double>(body->functions_count));
    cJSON_AddNumberToObject(out, "symbols_count",
                            static_cast<double>(body->symbols_count));
    cJSON_AddNumberToObject(out, "blocks_count",
                            static_cast<double>(body->blocks_count));
    cJSON_AddNumberToObject(out, "edges_count",
                            static_cast<double>(body->edges_count));
    cJSON_AddNumberToObject(out, "variables_count",
                            static_cast<double>(body->variables_count));
    cJSON_AddNumberToObject(out, "type_facts_count",
                            static_cast<double>(body->type_facts_count));
    cJSON_AddNumberToObject(out, "call_edges_count",
                            static_cast<double>(body->call_edges_count));
    cJSON_AddNumberToObject(out, "xrefs_count",
                            static_cast<double>(body->xrefs_count));
    /* Phase 11.3.6: strings_count is v3+; older bodies report 0. */
    cJSON_AddNumberToObject(out, "strings_count",
                            static_cast<double>(body->strings_count));
    cJSON_AddBoolToObject(out, "string_protection_enabled",
                          enable_string_protection);
    cJSON_AddStringToObject(
        out, "string_protection_mode",
        aura::safety::stringProtectionModeToText(
            string_protection_mode).c_str());

    cJSON *fns = cJSON_AddArrayToObject(out, "functions");
    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);
    for (size_t i = 0; i < body->functions_count; ++i) {
        cJSON *fn = cJSON_CreateObject();
        cJSON_AddNumberToObject(fn, "function_id",
                                static_cast<double>(funcs[i].function_id));
        cJSON_AddNumberToObject(fn, "entry",
                                static_cast<double>(funcs[i].entry));
        cJSON_AddNumberToObject(fn, "size",
                                static_cast<double>(funcs[i].size));
        cJSON_AddStringToObject(fn, "name",
                                funcs[i].name[0] ? funcs[i].name : "");
        cJSON *prov = cJSON_AddObjectToObject(fn, "provenance");
        cJSON_AddStringToObject(prov, "source", funcs[i].provenance.source);
        cJSON_AddNumberToObject(prov, "confidence",
                                funcs[i].provenance.confidence);
        cJSON_AddNumberToObject(prov, "completeness",
                                funcs[i].provenance.completeness);
        cJSON_AddItemToArray(fns, fn);
    }

    // Phase 11.3.5: surface symbols[] (incl. imports). Imports panel
    // filters by kind=="import"; Symbols panel takes the full list.
    cJSON *syms_arr = cJSON_AddArrayToObject(out, "symbols");
    const AuraSymbolRecord *syms = aura_rizin_analyze_body_symbols(body);
    for (size_t i = 0; syms && i < body->symbols_count; ++i) {
        cJSON *s = cJSON_CreateObject();
        cJSON_AddNumberToObject(s, "addr",
                                static_cast<double>(syms[i].addr));
        const char *kind = "unknown";
        switch (syms[i].kind) {
        case AURA_SYMBOL_FUNCTION: kind = "function"; break;
        case AURA_SYMBOL_OBJECT:   kind = "object";   break;
        case AURA_SYMBOL_SECTION:  kind = "section";  break;
        case AURA_SYMBOL_IMPORT:   kind = "import";   break;
        default: break;
        }
        cJSON_AddStringToObject(s, "kind", kind);
        cJSON_AddStringToObject(s, "name",
                                syms[i].name[0] ? syms[i].name : "");
        cJSON *prov = cJSON_AddObjectToObject(s, "provenance");
        cJSON_AddStringToObject(prov, "source", syms[i].provenance.source);
        cJSON_AddNumberToObject(prov, "confidence",
                                syms[i].provenance.confidence);
        cJSON_AddNumberToObject(prov, "completeness",
                                syms[i].provenance.completeness);
        cJSON_AddItemToArray(syms_arr, s);
    }

    // Phase 11.3.5: surface xrefs[] so downstream consumers (RPC, GUI dock,
    // headless callers) get the full normalized record, not just the count.
    cJSON *xrefs_arr = cJSON_AddArrayToObject(out, "xrefs");
    const AuraXrefRecord *xrefs = aura_rizin_analyze_body_xrefs(body);
    for (size_t i = 0; xrefs && i < body->xrefs_count; ++i) {
        cJSON *x = cJSON_CreateObject();
        cJSON_AddNumberToObject(x, "from",
                                static_cast<double>(xrefs[i].from_addr));
        cJSON_AddNumberToObject(x, "to",
                                static_cast<double>(xrefs[i].to_addr));
        const char *kind = "unknown";
        switch (xrefs[i].kind) {
        case AURA_XREF_DATA: kind = "data"; break;
        case AURA_XREF_CODE: kind = "code"; break;
        case AURA_XREF_CALL: kind = "call"; break;
        default: break;
        }
        cJSON_AddStringToObject(x, "kind", kind);
        cJSON *prov = cJSON_AddObjectToObject(x, "provenance");
        cJSON_AddStringToObject(prov, "source", xrefs[i].provenance.source);
        cJSON_AddNumberToObject(prov, "confidence",
                                xrefs[i].provenance.confidence);
        cJSON_AddNumberToObject(prov, "completeness",
                                xrefs[i].provenance.completeness);
        cJSON_AddItemToArray(xrefs_arr, x);
    }

    // Phase 11.3.6: surface strings[] (rizin izj). Same shape pattern as
    // xrefs[]/symbols[] — Strings dock + label-suggestion (PP4) consume
    // this array directly. Body schema v3+; v2 bodies report 0 entries.
    cJSON *strings_arr = cJSON_AddArrayToObject(out, "strings");
    const AuraStringRecord *strings = aura_rizin_analyze_body_strings(body);
    const auto safety_profile = enable_string_protection
                                    ? aura::safety::loadDefaultSafetyProfile()
                                    : aura::safety::SafetyProfile{};
    for (size_t i = 0; strings && i < body->strings_count; ++i) {
        cJSON *s = cJSON_CreateObject();
        cJSON_AddNumberToObject(s, "string_id",
                                static_cast<double>(strings[i].string_id));
        cJSON_AddNumberToObject(s, "addr",
                                static_cast<double>(strings[i].addr));
        cJSON_AddNumberToObject(s, "length",
                                static_cast<double>(strings[i].length));
        const char *enc = "unknown";
        switch (strings[i].encoding) {
        case AURA_STRING_ENC_ASCII:   enc = "ascii";   break;
        case AURA_STRING_ENC_UTF8:    enc = "utf8";    break;
        case AURA_STRING_ENC_UTF16LE: enc = "utf16le"; break;
        case AURA_STRING_ENC_UTF16BE: enc = "utf16be"; break;
        case AURA_STRING_ENC_WIDE:    enc = "wide";    break;
        default: break;
        }
        cJSON_AddStringToObject(s, "encoding", enc);
        cJSON_AddStringToObject(s, "section",
                                strings[i].section[0] ? strings[i].section : "");
        cJSON_AddStringToObject(s, "content",
                                strings[i].content[0] ? strings[i].content : "");
        if (enable_string_protection) {
            const std::string content =
                strings[i].content[0] ? strings[i].content : "";
            auto findings = aura::safety::scanStringWithRulePacks(
                content, safety_profile);
            auto protected_view = aura::safety::buildProtectedStringView(
                content, std::string(), std::move(findings));
            cJSON_AddStringToObject(
                s, "protected_value",
                mask_string_protection
                    ? protected_view.protected_value.c_str()
                    : content.c_str());
            cJSON_AddStringToObject(
                s, "masked_content",
                mask_string_protection ? protected_view.masked.c_str() : "");
            cJSON_AddNumberToObject(
                s, "findings_count",
                static_cast<double>(protected_view.findings.size()));
            cJSON *findings_arr = cJSON_AddArrayToObject(s, "findings");
            for (const auto &finding : protected_view.findings) {
                cJSON_AddItemToArray(findings_arr,
                                     finding_to_json(finding));
            }
        }
        cJSON *prov = cJSON_AddObjectToObject(s, "provenance");
        cJSON_AddStringToObject(prov, "source", strings[i].provenance.source);
        cJSON_AddNumberToObject(prov, "confidence",
                                strings[i].provenance.confidence);
        cJSON_AddNumberToObject(prov, "completeness",
                                strings[i].provenance.completeness);
        cJSON_AddItemToArray(strings_arr, s);
    }
    return out;
}

int run_analyze(const std::string &binary,
                aura::safety::StringProtectionMode string_protection_mode,
                const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }

    AuraEngineRequest req{};
    req.type         = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path  = binary.c_str();
    req.addr         = 0;
    req.arch_or_null = nullptr;

    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(), &req, &resp);

    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        std::string msg = "dispatch failed (status=";
        msg += std::to_string(static_cast<int>(st));
        msg += ")";
        emit_error_json("dispatch_failed", msg, g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }

    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);
    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "analyze");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddItemToObject(root, "body",
                          analyze_body_to_json(
                              body, string_protection_mode));

    emit_json(root, g.compact);

    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── disasm (Phase 11.3.7 / P2.F2) ──────────────────────────────────────────

cJSON *disasm_body_to_json(const AuraRizinDisasmBody *body) {
    cJSON *out = cJSON_CreateObject();
    cJSON_AddNumberToObject(out, "magic", static_cast<double>(body->magic));
    cJSON_AddNumberToObject(out, "version",
                            static_cast<double>(body->version));
    cJSON_AddNumberToObject(out, "function_addr",
                            static_cast<double>(body->function_addr));
    cJSON_AddNumberToObject(out, "instructions_count",
                            static_cast<double>(body->instructions_count));

    /* Phase 11.6 T1: text blob (rizin pdf with asm.lines flow arrows). */
    const char *txt = aura_rizin_disasm_body_text(body);
    cJSON_AddStringToObject(out, "text", txt ? txt : "");

    cJSON *arr = cJSON_AddArrayToObject(out, "instructions");
    const AuraInstructionRecord *ins =
        aura_rizin_disasm_body_instructions(body);
    for (size_t i = 0; ins && i < body->instructions_count; ++i) {
        cJSON *e = cJSON_CreateObject();
        cJSON_AddNumberToObject(e, "addr",
                                static_cast<double>(ins[i].addr));
        cJSON_AddNumberToObject(e, "size",
                                static_cast<double>(ins[i].size));
        cJSON_AddStringToObject(e, "bytes",
                                ins[i].bytes[0] ? ins[i].bytes : "");
        cJSON_AddStringToObject(e, "mnemonic",
                                ins[i].mnemonic[0] ? ins[i].mnemonic : "");
        cJSON_AddStringToObject(e, "op_str",
                                ins[i].op_str[0] ? ins[i].op_str : "");
        cJSON_AddStringToObject(e, "type",
                                ins[i].type[0] ? ins[i].type : "");
        cJSON_AddNumberToObject(e, "jump",
                                static_cast<double>(ins[i].jump));
        cJSON_AddNumberToObject(e, "fail",
                                static_cast<double>(ins[i].fail));
        cJSON *prov = cJSON_AddObjectToObject(e, "provenance");
        cJSON_AddStringToObject(prov, "source", ins[i].provenance.source);
        cJSON_AddNumberToObject(prov, "confidence",
                                ins[i].provenance.confidence);
        cJSON_AddNumberToObject(prov, "completeness",
                                ins[i].provenance.completeness);
        cJSON_AddItemToArray(arr, e);
    }
    return out;
}

int run_disasm(const std::string &binary, uint64_t func_addr,
               const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }

    AuraEngineRequest req{};
    req.type         = AURA_ENGINE_REQ_DISASM;
    req.binary_path  = binary.c_str();
    req.addr         = func_addr;
    req.arch_or_null = nullptr;

    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(), &req, &resp);

    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        std::string msg = "dispatch failed (status=";
        msg += std::to_string(static_cast<int>(st));
        msg += ")";
        emit_error_json("dispatch_failed", msg, g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }

    auto *body = static_cast<AuraRizinDisasmBody *>(resp.body);
    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "disasm");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddItemToObject(root, "body", disasm_body_to_json(body));

    emit_json(root, g.compact);

    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── field-candidates (Phase 11.4.4 / P4.PP2, ADR-0046) ────────────────────
//
// Display-only path 4번째 적용. Two heuristic sources:
//   (a) op_str regex: parse "[<reg>+0xNN]" patterns out of instruction
//       op_str fields. AURA does NOT interpret semantics — we just
//       count which (base_reg, offset) pairs appear in the function.
//   (c) stack_offset cluster: report variables whose kind=="stack",
//       sorted by stack_offset, as a hint that the function uses a
//       multi-field stack layout.
// R-9 boundary: substring extraction from a single record field is
// lookup. Synthesising a struct definition from these clusters is
// permanently rejected — that's the user's call (or LLM in v2 GUI).

namespace {

struct OffsetHit {
    int64_t  offset;        // signed (sign extracted from + / -)
    int      hits;
    uint64_t sample_addr;
    std::string mnemonic;
};

struct BaseRegGroup {
    std::string base_reg;
    std::map<int64_t, OffsetHit> by_offset;
};

// Extract one [reg+0xN] or [reg-0xN] occurrence from `op` starting at
// `pos`. Returns true and fills out_reg / out_off / new pos when matched.
// Pattern: `\[\s*([a-z][a-z0-9]+)\s*([+-])\s*0x([0-9a-fA-F]+)\s*\]`
bool match_bracket_offset(const std::string &op, size_t &pos,
                          std::string &out_reg, int64_t &out_off) {
    auto skip_ws = [&]() { while (pos < op.size() && (op[pos]==' '||op[pos]=='\t')) ++pos; };
    while (pos < op.size() && op[pos] != '[') ++pos;
    if (pos >= op.size()) return false;
    ++pos;  // consume '['
    skip_ws();
    // reg = [a-z][a-z0-9]+
    if (pos >= op.size() || !(op[pos] >= 'a' && op[pos] <= 'z')) return false;
    size_t r0 = pos;
    while (pos < op.size() &&
           ((op[pos] >= 'a' && op[pos] <= 'z') ||
            (op[pos] >= '0' && op[pos] <= '9'))) ++pos;
    std::string reg = op.substr(r0, pos - r0);
    skip_ws();
    if (pos >= op.size() || (op[pos] != '+' && op[pos] != '-')) return false;
    char sign = op[pos++];
    skip_ws();
    if (pos + 1 >= op.size() || op[pos] != '0' ||
        (op[pos+1] != 'x' && op[pos+1] != 'X')) return false;
    pos += 2;
    size_t h0 = pos;
    while (pos < op.size() &&
           ((op[pos] >= '0' && op[pos] <= '9') ||
            (op[pos] >= 'a' && op[pos] <= 'f') ||
            (op[pos] >= 'A' && op[pos] <= 'F'))) ++pos;
    if (pos == h0) return false;
    std::string hex = op.substr(h0, pos - h0);
    int64_t val = 0;
    try { val = static_cast<int64_t>(std::stoull(hex, nullptr, 16)); }
    catch (...) { return false; }
    if (sign == '-') val = -val;
    out_reg = reg;
    out_off = val;
    return true;
}

}  // namespace

int run_field_candidates(const std::string &binary, uint64_t func_addr,
                         const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(),
        &req, &resp);
    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        emit_error_json("dispatch_failed", "analyze failed", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);

    // Resolve target function for [entry, entry+size) bound + function_id.
    const AuraFunctionRecord *fns = aura_rizin_analyze_body_functions(body);
    const AuraFunctionRecord *func = nullptr;
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (fns[i].entry == func_addr) { func = &fns[i]; break; }
    }
    if (!func) {
        emit_error_json("function_not_found",
                        "no function with that entry addr", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }

    // (a) op_str regex source — DEFERRED to PP2 v2.
    //     Per ADR-0040 D4 the analyze body intentionally has no
    //     instructions[]; that data lives in AuraRizinDisasmBody and
    //     is fetched per-function via the DISASM dispatch. To turn
    //     (a) on, run_field_candidates would need to call DISASM for
    //     this function (or accept a pre-fetched disasm body) — that
    //     wiring is its own cycle. v1 emits the candidates array
    //     with op_str_regex source absent; the contract test
    //     accepts an empty array.
    std::map<std::string, BaseRegGroup> byReg;

    // (c) stack_offset cluster.
    std::vector<const AuraVariableRecord *> stackVars;
    const AuraVariableRecord *vrs = aura_rizin_analyze_body_variables(body);
    for (size_t i = 0; vrs && i < body->variables_count; ++i) {
        if (vrs[i].function_id != func->function_id) continue;
        if (std::strncmp(vrs[i].kind, "stack", 6) == 0) {
            stackVars.push_back(&vrs[i]);
        }
    }
    std::sort(stackVars.begin(), stackVars.end(),
              [](const AuraVariableRecord *a, const AuraVariableRecord *b) {
                  return a->stack_offset < b->stack_offset;
              });

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "field-candidates");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddNumberToObject(root, "function_addr",
                            static_cast<double>(func_addr));

    cJSON *cands = cJSON_AddArrayToObject(root, "candidates");
    for (auto &kv : byReg) {
        cJSON *e = cJSON_CreateObject();
        cJSON_AddStringToObject(e, "base_reg", kv.second.base_reg.c_str());
        cJSON *offs = cJSON_AddArrayToObject(e, "offsets");
        for (auto &op : kv.second.by_offset) {
            cJSON *o = cJSON_CreateObject();
            cJSON_AddNumberToObject(o, "value",
                                    static_cast<double>(op.second.offset));
            cJSON_AddNumberToObject(o, "hits",
                                    static_cast<double>(op.second.hits));
            cJSON_AddNumberToObject(o, "sample_addr",
                                    static_cast<double>(op.second.sample_addr));
            cJSON_AddStringToObject(o, "mnemonic",
                                    op.second.mnemonic.c_str());
            cJSON_AddItemToArray(offs, o);
        }
        cJSON_AddStringToObject(e, "source", "op_str_regex");
        cJSON_AddItemToArray(cands, e);
    }

    cJSON *clusters = cJSON_AddArrayToObject(root, "stack_clusters");
    for (const auto *v : stackVars) {
        cJSON *o = cJSON_CreateObject();
        cJSON_AddNumberToObject(o, "var_id",
                                static_cast<double>(v->var_id));
        cJSON_AddNumberToObject(o, "stack_offset",
                                static_cast<double>(v->stack_offset));
        cJSON_AddStringToObject(o, "name",
                                v->name[0] ? v->name : "");
        cJSON_AddStringToObject(o, "kind",
                                v->kind[0] ? v->kind : "");
        cJSON_AddItemToArray(clusters, o);
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── array-candidates (Phase 11.4.5 / P4.PP3, ADR-0047) ────────────────────
//
// Display-only path 5번째 적용. v1 sources:
//   (b) opportunistic: scan AuraTypeFactRecord where function_id matches
//       the target and type_str literal contains '[' (engine-emit
//       array). Verbatim engine literal pass-through.
//   (c) variable cluster: stack variables of the function sorted by
//       stack_offset → emit raw arithmetic (offsets/diffs/gcd) so the
//       user can read stride patterns. Per ADR-0047 D2 naming hygiene:
//       JSON keys / values use arithmetic vocabulary only — analysis
//       words ("stride"/"array"/"element_type") are emitted neither
//       by AURA nor present in synthesized strings.
//   (a) op_str source — DEFERRED to PP3 v2 (analyze body separation
//       per ADR-0040 D4; instructions[] live in DisasmBody and are
//       fetched per-function via DISASM dispatch). The PP3 GUI cycle
//       (C3) will wire (a) GUI-only via the existing in-process
//       MainWindow::disasmList(funcAddr) cache.

namespace {

// Euclidean GCD over signed 32-bit; returns absolute value.
int32_t gcd_i32(int32_t a, int32_t b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int32_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

}  // namespace

int run_array_candidates(const std::string &binary, uint64_t func_addr,
                         const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(),
        &req, &resp);
    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        emit_error_json("dispatch_failed", "analyze failed", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);

    // Resolve target function.
    const AuraFunctionRecord *fns = aura_rizin_analyze_body_functions(body);
    const AuraFunctionRecord *func = nullptr;
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (fns[i].entry == func_addr) { func = &fns[i]; break; }
    }
    if (!func) {
        emit_error_json("function_not_found",
                        "no function with that entry addr", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }

    // (c) variable cluster — stack vars sorted by stack_offset.
    std::vector<const AuraVariableRecord *> stackVars;
    const AuraVariableRecord *vrs = aura_rizin_analyze_body_variables(body);
    for (size_t i = 0; vrs && i < body->variables_count; ++i) {
        if (vrs[i].function_id != func->function_id) continue;
        if (std::strncmp(vrs[i].kind, "stack", 6) == 0) {
            stackVars.push_back(&vrs[i]);
        }
    }
    std::sort(stackVars.begin(), stackVars.end(),
              [](const AuraVariableRecord *a, const AuraVariableRecord *b) {
                  return a->stack_offset < b->stack_offset;
              });

    // (b) opportunistic type literal — type_facts for this function
    // whose type_str contains '[' (engine-emit bracket form).
    std::vector<const AuraTypeFactRecord *> typeHints;
    const AuraTypeFactRecord *tfs = aura_rizin_analyze_body_type_facts(body);
    for (size_t i = 0; tfs && i < body->type_facts_count; ++i) {
        if (tfs[i].function_id != func->function_id) continue;
        if (std::strchr(tfs[i].type_str, '[') == nullptr) continue;
        typeHints.push_back(&tfs[i]);
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "array-candidates");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddNumberToObject(root, "function_addr",
                            static_cast<double>(func_addr));

    // candidates[] = (a) op_str grouped by base_reg — empty in v1.
    cJSON_AddArrayToObject(root, "candidates");

    // variable_clusters[] — one per function (single base = stack frame).
    // We emit the raw arithmetic stat: offsets sorted, consecutive diffs,
    // and the GCD over diffs. No synthesized analysis vocabulary.
    cJSON *clusters = cJSON_AddArrayToObject(root, "variable_clusters");
    if (stackVars.size() >= 2) {
        cJSON *cl = cJSON_CreateObject();
        cJSON *offs = cJSON_AddArrayToObject(cl, "offsets");
        cJSON *vids = cJSON_AddArrayToObject(cl, "var_ids");
        for (const auto *v : stackVars) {
            cJSON_AddItemToArray(
                offs,
                cJSON_CreateNumber(static_cast<double>(v->stack_offset)));
            cJSON_AddItemToArray(
                vids,
                cJSON_CreateNumber(static_cast<double>(v->var_id)));
        }
        cJSON *diffs = cJSON_AddArrayToObject(cl, "diffs");
        int32_t g_acc = 0;
        for (size_t i = 1; i < stackVars.size(); ++i) {
            int32_t d = stackVars[i]->stack_offset
                      - stackVars[i - 1]->stack_offset;
            cJSON_AddItemToArray(
                diffs, cJSON_CreateNumber(static_cast<double>(d)));
            g_acc = gcd_i32(g_acc, d);
        }
        cJSON_AddNumberToObject(cl, "gcd", static_cast<double>(g_acc));
        cJSON_AddItemToArray(clusters, cl);
    }

    cJSON *hints = cJSON_AddArrayToObject(root, "type_hints");
    for (const auto *t : typeHints) {
        cJSON *o = cJSON_CreateObject();
        cJSON_AddNumberToObject(o, "var_id",
                                static_cast<double>(t->var_id));
        cJSON_AddStringToObject(o, "type_str", t->type_str);
        cJSON_AddItemToArray(hints, o);
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── propagate-type (Phase 11.4.3 / P4.PP1, ADR-0045) ──────────────────────
//
static bool parse_candidate_ids(const std::string &raw,
                                std::set<size_t> &out) {
    if (raw.empty()) return true;
    size_t pos = 0;
    while (pos < raw.size()) {
        size_t comma = raw.find(',', pos);
        std::string tok = raw.substr(pos, comma == std::string::npos
                                           ? std::string::npos
                                           : comma - pos);
        tok.erase(std::remove_if(tok.begin(), tok.end(),
                                 [](unsigned char ch) {
                                     return std::isspace(ch) != 0;
                                 }),
                  tok.end());
        if (tok.empty()) return false;
        try {
            size_t consumed = 0;
            unsigned long long id = std::stoull(tok, &consumed, 10);
            if (consumed != tok.size()) return false;
            out.insert(static_cast<size_t>(id));
        } catch (...) {
            return false;
        }
        if (comma == std::string::npos) break;
        pos = comma + 1;
    }
    return true;
}

static const AuraVariableRecord *find_variable_by_id(
    const AuraRizinAnalyzeBody *body, AuraVariableId var_id) {
    if (!body) return nullptr;
    const AuraVariableRecord *vars = aura_rizin_analyze_body_variables(body);
    for (size_t i = 0; vars && i < body->variables_count; ++i) {
        if (vars[i].var_id == var_id) return &vars[i];
    }
    return nullptr;
}

int run_propagate_type(const std::string &binary, uint64_t func_addr,
                       const std::string &target_type, bool apply,
                       const std::string &project,
                       const std::string &candidate_ids, bool apply_all,
                       const GlobalOpts &g) {
    if (target_type.size() >= AURA_OVERRIDE_PAYLOAD_TEXT_CAP) {
        emit_error_json("type_too_long",
                        "target type exceeds override payload text cap",
                        g.compact);
        return 2;
    }
    std::set<size_t> selected_ids;
    if (!parse_candidate_ids(candidate_ids, selected_ids)) {
        emit_error_json("invalid_candidate_ids",
                        "--candidate-ids must be a comma-separated list of "
                        "zero-based numeric candidate ids",
                        g.compact);
        return 2;
    }
    if (apply && !apply_all && selected_ids.empty()) {
        emit_error_json("missing_candidate_selection",
                        "--apply requires --all or --candidate-ids",
                        g.compact);
        return 2;
    }
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(),
        &req, &resp);
    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        emit_error_json("dispatch_failed", "analyze failed", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);

    AuraOverrideBinaryFingerprint fp{};
    if (apply && compute_fingerprint(binary, fp) != 0) {
        emit_error_json("file_read_failed", binary, g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }

    AuraTypePropagationResult tres{};
    int rc = aura_type_propagation_generate(
        body, func_addr, target_type.c_str(), &tres);
    if (rc != 0) {
        emit_error_json("propagation_failed",
                        "type_propagation_generate returned non-zero",
                        g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    if (apply && !apply_all) {
        for (size_t id : selected_ids) {
            if (id >= tres.count) {
                emit_error_json("candidate_id_out_of_range",
                                "one or more --candidate-ids values do not "
                                "exist in the generated candidate set",
                                g.compact);
                aura_type_propagation_result_free(&tres);
                aura_engine_response_dispose(&resp);
                aura_orchestrator_destroy(orch);
                return 2;
            }
        }
    }

    std::string db_path;
    size_t applied_count = 0;
    size_t skipped_count = 0;
    if (apply) {
        db_path = resolve_project_path(project, err);
        if (db_path.empty()) {
            emit_error_json("missing_project", err, g.compact);
            aura_type_propagation_result_free(&tres);
            aura_engine_response_dispose(&resp);
            aura_orchestrator_destroy(orch);
            return 2;
        }
        AuraOverrideStore *store = aura_override_store_open(db_path.c_str());
        if (!store) {
            emit_error_json("store_open_failed", db_path, g.compact);
            aura_type_propagation_result_free(&tres);
            aura_engine_response_dispose(&resp);
            aura_orchestrator_destroy(orch);
            return 1;
        }

        const AuraEngineManifest *manifest = aura_rizin_adapter_manifest();
        for (size_t i = 0; i < tres.count; ++i) {
            if (!apply_all && selected_ids.find(i) == selected_ids.end()) {
                continue;
            }
            const AuraTypePropagationCandidate &cand = tres.items[i];
            const AuraVariableRecord *var =
                find_variable_by_id(body, cand.var_id);
            if (!var) {
                ++skipped_count;
                continue;
            }
            AuraOverrideRecord rec{};
            rec.key = aura_override_key_from_variable_record(var, manifest, &fp);
            rec.key.request_type = AURA_ENGINE_REQ_ANALYZE;
            rec.key.engine_record_source_id = cand.var_id;
            rec.payload.kind = AURA_OVERRIDE_PAYLOAD_TYPE;
            std::strncpy(rec.payload.text, cand.new_type,
                         AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
            rec.status = AURA_OVERRIDE_STATUS_ACTIVE;
            if (aura_override_store_put(store, &rec) == 0) {
                ++applied_count;
            } else {
                ++skipped_count;
            }
        }
        aura_override_store_close(store);
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "propagate-type");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddNumberToObject(root, "function_addr",
                            static_cast<double>(func_addr));
    cJSON_AddStringToObject(root, "target_type", target_type.c_str());
    cJSON_AddBoolToObject  (root, "dry_run", !apply);
    if (apply) {
        cJSON_AddStringToObject(root, "project", db_path.c_str());
        cJSON_AddNumberToObject(root, "applied_count",
                                static_cast<double>(applied_count));
        cJSON_AddNumberToObject(root, "skipped_count",
                                static_cast<double>(skipped_count));
    }
    cJSON *arr = cJSON_AddArrayToObject(root, "candidates");
    for (size_t i = 0; i < tres.count; ++i) {
        const auto &c = tres.items[i];
        cJSON *e = cJSON_CreateObject();
        cJSON_AddNumberToObject(e, "candidate_id",
                                static_cast<double>(i));
        cJSON_AddNumberToObject(e, "var_id",
                                static_cast<double>(c.var_id));
        cJSON_AddNumberToObject(e, "function_id",
                                static_cast<double>(c.function_id));
        cJSON_AddNumberToObject(e, "call_site_addr",
                                static_cast<double>(c.call_site_addr));
        cJSON_AddStringToObject(e, "old_type",
                                c.old_type[0] ? c.old_type : "");
        cJSON_AddStringToObject(e, "new_type",
                                c.new_type[0] ? c.new_type : "");
        cJSON_AddNumberToObject(e, "distance",
                                static_cast<double>(c.distance));
        cJSON_AddStringToObject(e, "source",
                                c.source[0] ? c.source : "callee_param");
        cJSON_AddItemToArray(arr, e);
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_type_propagation_result_free(&tres);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── label-candidates (Phase 11.4.2 / P4.PP4, ADR-0044) ─────────────────────
//
// Display-only path per ADR-0044 D5. Reads existing records (xrefs[],
// symbols[], strings[]) from analyze body and emits ranked rename
// candidates. Never mutates the body, never adds to AuraRecordCollection.
//
// Heuristic per ADR-0044:
//   for each xref where xref.from_addr is in [func.entry, func.entry+size):
//     if xref.to_addr matches an IMPORT symbol → candidate(source=import)
//     if xref.to_addr matches a string addr   → candidate(source=string)
//   sort by confidence desc, break ties string > import; cap at 5.

namespace {

// Strip "imp." / "sym." / "fcn." prefixes; truncate to 24 ASCII chars.
std::string derive_name_from_symbol(const char *raw) {
    if (!raw) return {};
    std::string s = raw;
    static const char *prefixes[] = {"imp.", "sym.imp.", "sym.", "fcn."};
    for (const char *p : prefixes) {
        const size_t pl = std::strlen(p);
        if (s.size() > pl && s.compare(0, pl, p) == 0) {
            s.erase(0, pl);
            break;
        }
    }
    if (s.size() > 24) s.resize(24);
    return s;
}

// snake_case approximation: lowercase, non-alnum → '_', collapse '__',
// truncate to 24 chars, trim leading/trailing '_'.
std::string snake_case_from_string(const char *raw) {
    if (!raw) return {};
    std::string out;
    out.reserve(24);
    for (size_t i = 0; raw[i] && out.size() < 24; ++i) {
        const unsigned char c = static_cast<unsigned char>(raw[i]);
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            out += static_cast<char>(c);
        } else if (c >= 'A' && c <= 'Z') {
            out += static_cast<char>(c - 'A' + 'a');
        } else {
            if (!out.empty() && out.back() != '_') out += '_';
        }
    }
    while (!out.empty() && out.back() == '_') out.pop_back();
    while (!out.empty() && out.front() == '_') out.erase(0, 1);
    return out;
}

struct LabelCandidate {
    std::string name;
    std::string source;       // "string" | "import"
    double      confidence;
    uint64_t    fromAddr;
    std::string evidence;
};

}  // namespace

int run_label_candidates(const std::string &binary, uint64_t func_addr,
                         const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(),
        &req, &resp);
    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        emit_error_json("dispatch_failed", "analyze failed", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);

    // Locate the requested function by entry addr.
    const AuraFunctionRecord *fns = aura_rizin_analyze_body_functions(body);
    const AuraFunctionRecord *func = nullptr;
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (fns[i].entry == func_addr) { func = &fns[i]; break; }
    }
    if (!func) {
        emit_error_json("function_not_found",
                        "no function with that entry addr", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    const uint64_t fnLo = func->entry;
    const uint64_t fnHi = func->entry + (func->size ? func->size : 1);

    const AuraXrefRecord    *xrs = aura_rizin_analyze_body_xrefs(body);
    const AuraSymbolRecord  *sms = aura_rizin_analyze_body_symbols(body);
    const AuraStringRecord  *strs = aura_rizin_analyze_body_strings(body);

    // Build addr → IMPORT symbol map and addr → string map for O(1) lookup.
    std::map<uint64_t, const AuraSymbolRecord *> importByAddr;
    for (size_t i = 0; sms && i < body->symbols_count; ++i) {
        if (sms[i].kind == AURA_SYMBOL_IMPORT) {
            importByAddr[sms[i].addr] = &sms[i];
        }
    }
    std::map<uint64_t, const AuraStringRecord *> stringByAddr;
    for (size_t i = 0; strs && i < body->strings_count; ++i) {
        stringByAddr[strs[i].addr] = &strs[i];
    }

    std::vector<LabelCandidate> cands;
    for (size_t i = 0; xrs && i < body->xrefs_count; ++i) {
        const auto &x = xrs[i];
        if (x.from_addr < fnLo || x.from_addr >= fnHi) continue;
        // (b) call → import symbol
        auto itImp = importByAddr.find(x.to_addr);
        if (itImp != importByAddr.end()) {
            LabelCandidate c{};
            c.name       = derive_name_from_symbol(itImp->second->name);
            c.source     = "import";
            c.confidence = 0.7;
            c.fromAddr   = x.from_addr;
            c.evidence   = std::string("call:") + itImp->second->name;
            if (!c.name.empty()) cands.push_back(std::move(c));
        }
        // (a) data → string
        auto itStr = stringByAddr.find(x.to_addr);
        if (itStr != stringByAddr.end()) {
            LabelCandidate c{};
            c.name       = snake_case_from_string(itStr->second->content);
            c.source     = "string";
            c.confidence = 0.6;
            c.fromAddr   = x.from_addr;
            c.evidence   = std::string("str:") + itStr->second->content;
            if (!c.name.empty()) cands.push_back(std::move(c));
        }
    }

    // Sort: confidence desc, ties broken by source ("string" > "import").
    std::sort(cands.begin(), cands.end(),
              [](const LabelCandidate &a, const LabelCandidate &b) {
                  if (a.confidence != b.confidence)
                      return a.confidence > b.confidence;
                  return a.source < b.source;  // "import" < "string"
              });
    // Dedupe by name (keep first).
    std::set<std::string> seen;
    std::vector<LabelCandidate> unique;
    for (auto &c : cands) {
        if (seen.insert(c.name).second) unique.push_back(std::move(c));
    }
    if (unique.size() > 5) unique.resize(5);

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "label-candidates");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddNumberToObject(root, "function_addr",
                            static_cast<double>(func_addr));
    cJSON *arr = cJSON_AddArrayToObject(root, "candidates");
    for (const auto &c : unique) {
        cJSON *e = cJSON_CreateObject();
        cJSON_AddStringToObject(e, "name",       c.name.c_str());
        cJSON_AddStringToObject(e, "source",     c.source.c_str());
        cJSON_AddNumberToObject(e, "confidence", c.confidence);
        cJSON *ev = cJSON_AddObjectToObject(e, "evidence");
        cJSON_AddNumberToObject(ev, "from_addr",
                                static_cast<double>(c.fromAddr));
        cJSON_AddStringToObject(ev, "snippet", c.evidence.c_str());
        cJSON_AddItemToArray(arr, e);
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── cfg (Phase 11.3.8 / P2.F3) ─────────────────────────────────────────────

int run_cfg(const std::string &binary, uint64_t func_addr,
            const GlobalOpts &g) {
    // ADR-0041 D1: data ownership stays in the analyze body. CLI runs
    // ANALYZE once, then filters body.blocks[]/edges[] by function_id.
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(),
        &req, &resp);
    if (st != AURA_ENGINE_OK || resp.body == nullptr) {
        emit_error_json("dispatch_failed", "analyze failed", g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);

    // Resolve function_id by entry address.
    uint32_t fid = 0;
    const AuraFunctionRecord *fns = aura_rizin_analyze_body_functions(body);
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (fns[i].entry == func_addr) { fid = fns[i].function_id; break; }
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "cfg");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON *out = cJSON_AddObjectToObject(root, "body");
    cJSON_AddNumberToObject(out, "function_addr",
                            static_cast<double>(func_addr));
    cJSON_AddNumberToObject(out, "function_id", static_cast<double>(fid));

    cJSON *barr = cJSON_AddArrayToObject(out, "blocks");
    std::vector<uint32_t> blockIds;
    if (fid != 0) {
        const AuraBlockRecord *bb = aura_rizin_analyze_body_blocks(body);
        for (size_t i = 0; bb && i < body->blocks_count; ++i) {
            if (bb[i].function_id != fid) continue;
            blockIds.push_back(bb[i].block_id);
            cJSON *row = cJSON_CreateObject();
            cJSON_AddNumberToObject(row, "block_id",
                                    static_cast<double>(bb[i].block_id));
            cJSON_AddNumberToObject(row, "start",
                                    static_cast<double>(bb[i].start_addr));
            cJSON_AddNumberToObject(row, "end",
                                    static_cast<double>(bb[i].end_addr));
            cJSON *prov = cJSON_AddObjectToObject(row, "provenance");
            cJSON_AddStringToObject(prov, "source", bb[i].provenance.source);
            cJSON_AddItemToArray(barr, row);
        }
    }

    cJSON *earr = cJSON_AddArrayToObject(out, "edges");
    if (!blockIds.empty()) {
        const AuraEdgeRecord *eg = aura_rizin_analyze_body_edges(body);
        auto in_set = [&](uint32_t id) {
            for (auto x : blockIds) if (x == id) return true;
            return false;
        };
        for (size_t i = 0; eg && i < body->edges_count; ++i) {
            if (!in_set(eg[i].src_block) || !in_set(eg[i].dst_block)) continue;
            cJSON *row = cJSON_CreateObject();
            cJSON_AddNumberToObject(row, "src",
                                    static_cast<double>(eg[i].src_block));
            cJSON_AddNumberToObject(row, "dst",
                                    static_cast<double>(eg[i].dst_block));
            const char *kind = "unknown";
            switch (eg[i].kind) {
            case AURA_EDGE_FALLTHROUGH:  kind = "fallthrough";  break;
            case AURA_EDGE_JUMP:         kind = "jump";         break;
            case AURA_EDGE_BRANCH_TRUE:  kind = "branch_true";  break;
            case AURA_EDGE_BRANCH_FALSE: kind = "branch_false"; break;
            case AURA_EDGE_CALL:         kind = "call";         break;
            case AURA_EDGE_RETURN:       kind = "return";       break;
            default: break;
            }
            cJSON_AddStringToObject(row, "kind", kind);
            cJSON_AddItemToArray(earr, row);
        }
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return 0;
}

// ── info ───────────────────────────────────────────────────────────────────

struct BinaryInfo {
    uint64_t    file_size   = 0;
    std::string sha256_hex;
    std::string format_kind = "unknown";
    uint64_t    image_base  = 0;
    uint64_t    entry       = 0;
};

static uint16_t rd_u16le(const uint8_t *p) {
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}
static uint32_t rd_u32le(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}
static uint64_t rd_u64le(const uint8_t *p) {
    return (uint64_t)rd_u32le(p) | ((uint64_t)rd_u32le(p + 4) << 32);
}

// Parse minimal ELF / PE / Mach-O header info. Best-effort — leaves 0 fields
// where the format isn't supported or header is malformed.
void parse_header(const std::string &path, BinaryInfo &out) {
    std::ifstream fp(path, std::ios::binary);
    if (!fp) return;
    fp.seekg(0, std::ios::end);
    auto sz = fp.tellg();
    if (sz <= 0) return;
    out.file_size = static_cast<uint64_t>(sz);
    fp.seekg(0, std::ios::beg);

    // Read up to 4 KB of header (enough for ELF/PE optional headers).
    std::vector<uint8_t> hdr(4096, 0);
    fp.read(reinterpret_cast<char *>(hdr.data()),
            std::min<std::streamsize>(static_cast<std::streamsize>(hdr.size()),
                                      sz));
    auto got = static_cast<size_t>(fp.gcount());
    if (got < 16) return;

    // ELF: 7F 45 4C 46
    if (hdr[0] == 0x7f && hdr[1] == 'E' && hdr[2] == 'L' && hdr[3] == 'F') {
        out.format_kind = "elf";
        if (got < 64 || hdr[4] != 2 /* ELFCLASS64 */) return;
        // Elf64_Ehdr: e_entry at offset 24 (8B LE), e_phoff @ 32 (8B),
        //             e_phentsize @ 54 (2B), e_phnum @ 56 (2B).
        out.entry = rd_u64le(&hdr[24]);
        uint64_t phoff = rd_u64le(&hdr[32]);
        uint16_t phentsize = rd_u16le(&hdr[54]);
        uint16_t phnum = rd_u16le(&hdr[56]);
        // Lowest PT_LOAD p_vaddr = image_base (best effort).
        if (phentsize >= 56 && phnum > 0 &&
            phoff + (uint64_t)phentsize * phnum <= got) {
            uint64_t lowest = UINT64_MAX;
            for (uint16_t i = 0; i < phnum; ++i) {
                const uint8_t *ph = &hdr[phoff + (uint64_t)phentsize * i];
                uint32_t p_type = rd_u32le(ph);
                if (p_type == 1 /* PT_LOAD */) {
                    uint64_t p_vaddr = rd_u64le(ph + 16);
                    if (p_vaddr < lowest) lowest = p_vaddr;
                }
            }
            if (lowest != UINT64_MAX) out.image_base = lowest;
        }
        return;
    }

    // PE: MZ ... offset 0x3c → "PE\0\0" + COFF header + Optional header.
    if (hdr[0] == 'M' && hdr[1] == 'Z' && got >= 0x40) {
        uint32_t e_lfanew = rd_u32le(&hdr[0x3c]);
        if (e_lfanew + 24 + 2 > got) return;
        const uint8_t *pe = &hdr[e_lfanew];
        if (pe[0] != 'P' || pe[1] != 'E' || pe[2] != 0 || pe[3] != 0) return;
        out.format_kind = "pe";
        // Optional header magic at pe+24: 0x10b PE32, 0x20b PE32+.
        uint16_t opt_magic = rd_u16le(pe + 24);
        // AddressOfEntryPoint at OptionalHeader + 16 (both PE32 and PE32+).
        if (e_lfanew + 24 + 20 > got) return;
        uint32_t aoe = rd_u32le(pe + 24 + 16);
        if (opt_magic == 0x20b) {
            // PE32+: ImageBase at OptionalHeader + 24 (8 bytes).
            if (e_lfanew + 24 + 32 > got) return;
            out.image_base = rd_u64le(pe + 24 + 24);
        } else if (opt_magic == 0x10b) {
            // PE32: ImageBase at OptionalHeader + 28 (4 bytes).
            if (e_lfanew + 24 + 32 > got) return;
            out.image_base = rd_u32le(pe + 24 + 28);
        }
        out.entry = out.image_base + aoe;
        return;
    }

    // Mach-O: 0xfeedface (32-bit) / 0xfeedfacf (64-bit) / 0xcafebabe (fat).
    uint32_t magic = rd_u32le(&hdr[0]);
    if (magic == 0xfeedface || magic == 0xfeedfacf ||
        magic == 0xcafebabe || magic == 0xcefaedfe || magic == 0xcffaedfe) {
        out.format_kind = "mach-o";
        // Entry / image_base parsing left for v2 (LC_SEGMENT walk).
    }
}

// ── override (Phase 11.4) ──────────────────────────────────────────────────
//
// `aura override {list,get,put,delete}` — CRUD over the Phase 4B SQLite
// override store. Key construction follows the Phase 4A stable identity
// contract; binary fingerprint is auto-computed from `info`-style header
// parsing. `put` is gated on Q10 (ANALYZE dispatch policy) — pending.

// Resolve the SQLite DB path. Q1 (a): --project flag has highest priority,
// then $AURA_PROJECT env, else usage error. If the resolved path is a
// directory, use `<dir>/aura.db`; if a file (or non-existent path), use as is.
// Returns empty string + sets `err` on missing/invalid input.
static std::string resolve_project_path(const std::string &flag_value,
                                        std::string &err) {
    namespace fs = std::filesystem;
    std::string raw = flag_value;
    if (raw.empty()) {
        if (const char *env = std::getenv("AURA_PROJECT")) raw = env;
    }
    if (raw.empty()) {
        err = "missing --project (or $AURA_PROJECT). e.g. "
              "--project ./work/  or  --project ./my.db";
        return "";
    }
    fs::path p = raw;
    if (fs::exists(p) && fs::is_directory(p)) {
        return (p / "aura.db").string();
    }
    // File path (existing or to-be-created). Ensure parent dir exists.
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        std::error_code ec;
        fs::create_directories(p.parent_path(), ec);
        if (ec) {
            err = "could not create project parent dir: " + p.parent_path().string();
            return "";
        }
    }
    return p.string();
}

// Compute binary fingerprint (sha256 + size + format + image_base + entry)
// using the same code path as `info`. Returns 0 on success.
static int compute_fingerprint(const std::string &binary,
                               AuraOverrideBinaryFingerprint &out) {
    namespace fs = std::filesystem;
    std::memset(&out, 0, sizeof(out));
    if (!fs::exists(binary)) return -1;
    out.file_size = fs::file_size(binary);
    if (aura_sha256_file(binary.c_str(), out.sha256) != 0) return -1;

    BinaryInfo info{};
    parse_header(binary, info);
    std::strncpy(out.format_kind, info.format_kind.c_str(),
                 sizeof(out.format_kind) - 1);
    out.image_base = info.image_base;
    return 0;
}

// Append a fingerprint subobject to a cJSON parent.
static void emit_fingerprint(cJSON *parent,
                             const AuraOverrideBinaryFingerprint &fp) {
    cJSON *o = cJSON_AddObjectToObject(parent, "fingerprint");
    cJSON_AddNumberToObject(o, "file_size", static_cast<double>(fp.file_size));
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1];
    aura_sha256_hex(fp.sha256, hex);
    cJSON_AddStringToObject(o, "sha256", hex);
    cJSON_AddStringToObject(o, "format_kind", fp.format_kind);
    cJSON_AddNumberToObject(o, "image_base",
                            static_cast<double>(fp.image_base));
}

static const char *target_kind_str(AuraOverrideTargetKind k) {
    switch (k) {
        case AURA_OVERRIDE_TARGET_FUNCTION:   return "function";
        case AURA_OVERRIDE_TARGET_VARIABLE:   return "variable";
        case AURA_OVERRIDE_TARGET_TYPE:       return "type";
        case AURA_OVERRIDE_TARGET_ANNOTATION: return "annotation";
        case AURA_OVERRIDE_TARGET_ADDRESS:    return "address";
        case AURA_OVERRIDE_TARGET_SYMBOL:     return "symbol";
    }
    return "unknown";
}

static const char *payload_kind_str(AuraOverridePayloadKind k) {
    switch (k) {
        case AURA_OVERRIDE_PAYLOAD_RENAME:     return "rename";
        case AURA_OVERRIDE_PAYLOAD_TYPE:       return "type";
        case AURA_OVERRIDE_PAYLOAD_ANNOTATION: return "annotation";
    }
    return "unknown";
}

static const char *status_str(AuraOverrideStatus s) {
    switch (s) {
        case AURA_OVERRIDE_STATUS_PENDING:  return "pending";
        case AURA_OVERRIDE_STATUS_ACTIVE:   return "active";
        case AURA_OVERRIDE_STATUS_CONFLICT: return "conflict";
        case AURA_OVERRIDE_STATUS_ORPHAN:   return "orphan";
    }
    return "unknown";
}

static const char *confidence_str(AuraOverrideConfidence c) {
    switch (c) {
        case AURA_OVERRIDE_CONFIDENCE_EXACT:   return "exact";
        case AURA_OVERRIDE_CONFIDENCE_STRONG:  return "strong";
        case AURA_OVERRIDE_CONFIDENCE_WEAK:    return "weak";
        case AURA_OVERRIDE_CONFIDENCE_MISSING: return "missing";
    }
    return "unknown";
}

// Build the (incomplete) key portion that uses only the user-provided
// inputs: binary fingerprint + target_addr. Engine identity / stable_id /
// confidence are filled in by Q10-dependent caller for `put`, or are not
// needed for read-path commands which use `get`/iteration helpers.
static AuraOverrideKey skeleton_key_from_addr(
    const AuraOverrideBinaryFingerprint &fp, uint64_t func_addr) {
    AuraOverrideKey k{};
    k.binary_fingerprint = fp;
    k.request_type = AURA_ENGINE_REQ_ANALYZE;
    k.target_kind = AURA_OVERRIDE_TARGET_FUNCTION;
    k.target_addr = func_addr;
    // function_stable_id derivation when no engine record is available:
    // use the entry address itself as a stable proxy. WEAK confidence.
    k.function_stable_id = func_addr;
    k.target_stable_id   = func_addr;
    k.confidence = AURA_OVERRIDE_CONFIDENCE_WEAK;
    std::strncpy(k.engine_id, "rizin", sizeof(k.engine_id) - 1);
    return k;
}

// Build a Phase-4A-compliant key by dispatching ANALYZE first and looking
// up the function record at `func_addr`. Returns 0 on success, -1 on
// dispatch / record-not-found failure (with `err` filled).
//
// This is the "rich" path: confidence is derived per Phase 4A.X2 priority
// using the engine record fields. Used when --no-analyze is NOT set.
static int build_rich_key(AuraOrchestrator *orch, const std::string &binary,
                          uint64_t func_addr,
                          const AuraOverrideBinaryFingerprint &fp,
                          AuraOverrideKey &out_key, std::string &err) {
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(orch, "rizin", &req, &resp);
    if (st != AURA_ENGINE_OK || !resp.body) {
        err = "ANALYZE dispatch failed (status=" +
              std::to_string(static_cast<int>(st)) + ")";
        aura_engine_response_dispose(&resp);
        return -1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);
    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);
    size_t idx = SIZE_MAX;
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (funcs[i].entry == func_addr) { idx = i; break; }
    }
    if (idx == SIZE_MAX) {
        err = "no function at entry address in fresh ANALYZE result";
        aura_engine_response_dispose(&resp);
        return -1;
    }

    const AuraEngineManifest *manifest = aura_rizin_adapter_manifest();
    out_key = aura_override_key_from_function_record(&funcs[idx], manifest, &fp);
    // Phase 4A.X2 already set confidence (EXACT/STRONG/WEAK) and stable_id
    // based on what the engine record carried; we trust it.
    aura_engine_response_dispose(&resp);
    return 0;
}

// ── override put ───────────────────────────────────────────────────────────

static int run_override_put(const std::string &binary, uint64_t func_addr,
                             const std::string &new_name,
                             const std::string &project, bool no_analyze,
                             const GlobalOpts &g) {
    std::string err;
    std::string db_path = resolve_project_path(project, err);
    if (db_path.empty()) {
        emit_error_json("missing_project", err, g.compact);
        return 2;
    }
    AuraOverrideBinaryFingerprint fp{};
    if (compute_fingerprint(binary, fp) != 0) {
        emit_error_json("file_read_failed", binary, g.compact);
        return 1;
    }

    AuraOverrideKey key{};
    if (no_analyze) {
        // Path B (Q10) — fast, shallow. WEAK confidence, addr-as-stable-id.
        key = skeleton_key_from_addr(fp, func_addr);
    } else {
        // Path A (Q10 default) — dispatch ANALYZE, derive STRONG/EXACT key.
        AuraOrchestrator *orch = build_orchestrator(g, err);
        if (!orch) {
            emit_error_json("orchestrator_init_failed", err, g.compact);
            return 3;
        }
        int rc = build_rich_key(orch, binary, func_addr, fp, key, err);
        aura_orchestrator_destroy(orch);
        if (rc != 0) {
            emit_error_json("analyze_for_put_failed", err, g.compact);
            return 1;
        }
    }

    AuraOverrideStore *store = aura_override_store_open(db_path.c_str());
    if (!store) {
        emit_error_json("store_open_failed", db_path, g.compact);
        return 1;
    }
    AuraOverrideRecord rec{};
    rec.key = key;
    rec.payload.kind = AURA_OVERRIDE_PAYLOAD_RENAME;
    std::strncpy(rec.payload.text, new_name.c_str(),
                 AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
    rec.status = AURA_OVERRIDE_STATUS_PENDING;
    int rc = aura_override_store_put(store, &rec);
    aura_override_store_close(store);

    if (rc != 0) {
        emit_error_json("store_put_failed", "INSERT OR REPLACE failed",
                        g.compact);
        return 1;
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "override put");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddStringToObject(root, "project", db_path.c_str());
    cJSON_AddNumberToObject(root, "function_anchor_addr",
                            static_cast<double>(func_addr));
    cJSON_AddStringToObject(root, "rename", new_name.c_str());
    cJSON_AddStringToObject(root, "confidence", confidence_str(key.confidence));
    cJSON_AddStringToObject(root, "engine_id", key.engine_id);
    cJSON_AddBoolToObject  (root, "analyzed", !no_analyze);
    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}

// ── override list ──────────────────────────────────────────────────────────

static int run_override_list(const std::string &binary,
                              const std::string &project,
                              const GlobalOpts &g) {
    std::string err;
    std::string db_path = resolve_project_path(project, err);
    if (db_path.empty()) {
        emit_error_json("missing_project", err, g.compact);
        return 2;
    }
    AuraOverrideBinaryFingerprint fp{};
    if (compute_fingerprint(binary, fp) != 0) {
        emit_error_json("file_read_failed",
                        "could not fingerprint " + binary, g.compact);
        return 1;
    }
    AuraOverrideStore *store = aura_override_store_open(db_path.c_str());
    if (!store) {
        emit_error_json("store_open_failed",
                        "could not open SQLite store at " + db_path, g.compact);
        return 1;
    }
    int total = aura_override_store_count(store);
    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "override list");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddStringToObject(root, "project", db_path.c_str());
    emit_fingerprint(root, fp);
    cJSON *arr = cJSON_AddArrayToObject(root, "overrides");
    cJSON_AddNumberToObject(root, "total_rows_in_store",
                            static_cast<double>(total < 0 ? 0 : total));
    // NOTE: Phase 4B store currently exposes count + per-key lookup only.
    // No iterate-all API. This `list` shows store-wide totals; per-binary
    // enumeration awaits Phase 4 enumeration helper (separate task).
    // For now: a known-key probe via skeleton_key is not feasible without
    // an addr list — left empty intentionally with a note.
    cJSON_AddStringToObject(root, "note",
        "per-binary enumeration requires Phase 4 store iterate API "
        "(not yet exposed); current output reports total_rows_in_store. "
        "use `aura override get --func <addr>` for individual lookup.");
    (void)arr;

    emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_override_store_close(store);
    return 0;
}

// ── override get ───────────────────────────────────────────────────────────

static int run_override_get(const std::string &binary,
                             uint64_t func_addr,
                             const std::string &project,
                             bool no_analyze,
                             const GlobalOpts &g) {
    std::string err;
    std::string db_path = resolve_project_path(project, err);
    if (db_path.empty()) {
        emit_error_json("missing_project", err, g.compact);
        return 2;
    }
    AuraOverrideBinaryFingerprint fp{};
    if (compute_fingerprint(binary, fp) != 0) {
        emit_error_json("file_read_failed", binary, g.compact);
        return 1;
    }

    // Build the same key shape the corresponding `put` would have built —
    // matches default ANALYZE-derived rich key, or skeleton WEAK key with
    // --no-analyze. (Phase 4B store has strict primary-key match.)
    AuraOverrideKey key{};
    if (no_analyze) {
        key = skeleton_key_from_addr(fp, func_addr);
    } else {
        AuraOrchestrator *orch = build_orchestrator(g, err);
        if (!orch) {
            emit_error_json("orchestrator_init_failed", err, g.compact);
            return 3;
        }
        int rc = build_rich_key(orch, binary, func_addr, fp, key, err);
        aura_orchestrator_destroy(orch);
        if (rc != 0) {
            emit_error_json("analyze_for_get_failed", err, g.compact);
            return 1;
        }
    }

    AuraOverrideStore *store = aura_override_store_open(db_path.c_str());
    if (!store) {
        emit_error_json("store_open_failed", db_path, g.compact);
        return 1;
    }
    AuraOverrideRecord rec{};
    int rc = aura_override_store_get(store, &key, &rec);
    aura_override_store_close(store);

    if (rc < 0) {
        emit_error_json("store_get_failed", "internal error", g.compact);
        return 1;
    }
    if (rc == 1) {
        emit_error_json("not_found",
                        "no override at this key (binary fingerprint + addr)",
                        g.compact);
        return 1;
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "override get");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddStringToObject(root, "project", db_path.c_str());
    cJSON *o = cJSON_AddObjectToObject(root, "override");
    cJSON_AddNumberToObject(o, "function_anchor_addr",
                            static_cast<double>(rec.key.target_addr));
    cJSON_AddNumberToObject(o, "function_stable_id",
                            static_cast<double>(rec.key.function_stable_id));
    cJSON_AddStringToObject(o, "target_kind",
                            target_kind_str(rec.key.target_kind));
    cJSON_AddStringToObject(o, "engine_id", rec.key.engine_id);
    cJSON_AddStringToObject(o, "confidence",
                            confidence_str(rec.key.confidence));
    cJSON_AddStringToObject(o, "status", status_str(rec.status));
    cJSON *p = cJSON_AddObjectToObject(o, "payload");
    cJSON_AddStringToObject(p, "kind", payload_kind_str(rec.payload.kind));
    cJSON_AddStringToObject(p, "text", rec.payload.text);

    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}

// ── override delete ────────────────────────────────────────────────────────

static int run_override_delete(const std::string &binary,
                                uint64_t func_addr,
                                const std::string &project,
                                bool no_analyze,
                                const GlobalOpts &g) {
    std::string err;
    std::string db_path = resolve_project_path(project, err);
    if (db_path.empty()) {
        emit_error_json("missing_project", err, g.compact);
        return 2;
    }
    AuraOverrideBinaryFingerprint fp{};
    if (compute_fingerprint(binary, fp) != 0) {
        emit_error_json("file_read_failed", binary, g.compact);
        return 1;
    }

    AuraOverrideKey key{};
    if (no_analyze) {
        key = skeleton_key_from_addr(fp, func_addr);
    } else {
        AuraOrchestrator *orch = build_orchestrator(g, err);
        if (!orch) {
            emit_error_json("orchestrator_init_failed", err, g.compact);
            return 3;
        }
        int rc = build_rich_key(orch, binary, func_addr, fp, key, err);
        aura_orchestrator_destroy(orch);
        if (rc != 0) {
            emit_error_json("analyze_for_delete_failed", err, g.compact);
            return 1;
        }
    }

    AuraOverrideStore *store = aura_override_store_open(db_path.c_str());
    if (!store) {
        emit_error_json("store_open_failed", db_path, g.compact);
        return 1;
    }
    int rc = aura_override_store_delete(store, &key);
    aura_override_store_close(store);

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "override delete");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON_AddStringToObject(root, "project", db_path.c_str());
    cJSON_AddNumberToObject(root, "function_anchor_addr",
                            static_cast<double>(func_addr));
    cJSON_AddStringToObject(root, "result",
        rc == 0 ? "deleted" : (rc == 1 ? "not_found" : "error"));
    emit_json(root, g.compact);
    cJSON_Delete(root);
    return rc < 0 ? 1 : 0;
}

// ── engines ────────────────────────────────────────────────────────────────

struct EngineProbe {
    std::string id;             // "rizin", "ghidra", ...
    std::string role;           // "reference" or "optional"
    std::string env_var;        // override env var (e.g. AURA_RIZIN_BIN)
    std::string manifest_path;  // third_party/<id>/<ver>/bin/<binary>
    std::string discovered;     // resolved path (empty if not found)
    bool        available = false;
};

static std::string repo_root_for_cli() {
    if (const char *env = std::getenv("AURA_REPO_ROOT")) return env;
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    for (int i = 0; i < 10; ++i) {
        if (fs::exists(p / "CONTEXT.md")) return p.string();
        if (!p.has_parent_path()) break;
        p = p.parent_path();
    }
    return fs::current_path().string();
}

static EngineProbe probe_rizin() {
    EngineProbe e;
    e.id = "rizin";
    e.role = "reference";  // ADR-0031
    e.env_var = "AURA_RIZIN_BIN";
    namespace fs = std::filesystem;
    fs::path root = repo_root_for_cli();
#ifdef _WIN32
    e.manifest_path = (root / kVendoredRizinRelWin).string();
#else
    e.manifest_path = (root / kVendoredRizinRelPosix).string();
#endif
    if (const char *env = std::getenv("AURA_RIZIN_BIN")) {
        if (fs::exists(env)) {
            e.discovered = env;
            e.available = true;
            return e;
        }
    }
    if (fs::exists(e.manifest_path)) {
        e.discovered = e.manifest_path;
        e.available = true;
    }
    return e;
}

int run_engines(const GlobalOpts &g) {
    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "engines");
    cJSON *list = cJSON_AddArrayToObject(root, "engines");

    EngineProbe probes[] = {probe_rizin()};
    for (const auto &e : probes) {
        cJSON *o = cJSON_CreateObject();
        cJSON_AddStringToObject(o, "id", e.id.c_str());
        cJSON_AddStringToObject(o, "role", e.role.c_str());
        cJSON_AddStringToObject(o, "env_var", e.env_var.c_str());
        cJSON_AddStringToObject(o, "manifest_path", e.manifest_path.c_str());
        cJSON_AddStringToObject(o, "discovered", e.discovered.c_str());
        cJSON_AddBoolToObject  (o, "available",  e.available);
        cJSON_AddItemToArray(list, o);
    }

    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}

// ── llm-context ────────────────────────────────────────────────────────────

// Find function index by id (linear scan — function counts are small).
size_t find_func_by_id(const AuraFunctionRecord *funcs, size_t n,
                       AuraFunctionId id) {
    for (size_t i = 0; i < n; ++i) {
        if (funcs[i].function_id == id) return i;
    }
    return SIZE_MAX;
}

// Find function by entry address.
size_t find_func_by_entry(const AuraFunctionRecord *funcs, size_t n,
                          uint64_t addr) {
    for (size_t i = 0; i < n; ++i) {
        if (funcs[i].entry == addr) return i;
    }
    return SIZE_MAX;
}

// Best-effort decompile of a single function via the orchestrator. Returns
// nullptr on any failure (caller treats as "decompile not available"). The
// returned string is malloc'd; caller must free.
char *decompile_function_text(AuraOrchestrator *orch, const std::string &binary,
                              uint64_t addr, const GlobalOpts &g) {
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_DECOMPILE;
    req.binary_path = binary.c_str();
    req.addr        = addr;
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(), &req, &resp);
    char *out = nullptr;
    if (st == AURA_ENGINE_OK && resp.body && resp.body_size >= 16) {
        // First 16 bytes of any decompile body == AuraDecompileBodyHeader
        // prefix; we only need body_text via the Rizin accessor (Rizin is the
        // reference engine for now).
        auto *body = static_cast<const AuraRizinDecompileBody *>(resp.body);
        if (body->magic == AURA_RIZIN_DECOMPILE_BODY_MAGIC) {
            const char *txt = aura_rizin_decompile_body_text(body);
            if (txt && *txt) out = strdup(txt);
        }
    }
    aura_engine_response_dispose(&resp);
    return out;
}

// Build the JSON object for one function with optional callers/callees and
// optional decompile text.
cJSON *make_function_card(const AuraRizinAnalyzeBody *body,
                          size_t fn_idx, const char *decompile_text) {
    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);
    const AuraCallEdgeRecord *edges = aura_rizin_analyze_body_call_edges(body);
    const AuraFunctionRecord &f = funcs[fn_idx];

    cJSON *card = cJSON_CreateObject();
    cJSON_AddNumberToObject(card, "function_id",
                            static_cast<double>(f.function_id));
    cJSON_AddStringToObject(card, "name", f.name[0] ? f.name : "");
    cJSON_AddNumberToObject(card, "entry", static_cast<double>(f.entry));
    cJSON_AddNumberToObject(card, "size", static_cast<double>(f.size));
    cJSON *prov = cJSON_AddObjectToObject(card, "provenance");
    cJSON_AddStringToObject(prov, "source", f.provenance.source);
    cJSON_AddNumberToObject(prov, "confidence", f.provenance.confidence);
    cJSON_AddNumberToObject(prov, "completeness", f.provenance.completeness);

    cJSON *callers = cJSON_AddArrayToObject(card, "callers");
    cJSON *callees = cJSON_AddArrayToObject(card, "callees");
    for (size_t i = 0; i < body->call_edges_count; ++i) {
        if (edges[i].callee_id == f.function_id &&
            edges[i].caller_id != AURA_NULL_ID) {
            size_t k = find_func_by_id(funcs, body->functions_count,
                                       edges[i].caller_id);
            if (k != SIZE_MAX) {
                cJSON_AddItemToArray(callers, cJSON_CreateString(
                    funcs[k].name[0] ? funcs[k].name : ""));
            }
        }
        if (edges[i].caller_id == f.function_id &&
            edges[i].callee_id != AURA_NULL_ID) {
            size_t k = find_func_by_id(funcs, body->functions_count,
                                       edges[i].callee_id);
            if (k != SIZE_MAX) {
                cJSON_AddItemToArray(callees, cJSON_CreateString(
                    funcs[k].name[0] ? funcs[k].name : ""));
            }
        }
    }

    if (decompile_text) {
        cJSON_AddStringToObject(card, "decompile", decompile_text);
    }
    return card;
}

int run_llm_context(const std::string &binary, bool has_func, uint64_t func_addr,
                    bool with_decompile, const GlobalOpts &g) {
    std::string err;
    AuraOrchestrator *orch = build_orchestrator(g, err);
    if (!orch) {
        emit_error_json("orchestrator_init_failed", err, g.compact);
        return 3;
    }

    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path = binary.c_str();
    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(
        orch, g.engine_id.empty() ? nullptr : g.engine_id.c_str(), &req, &resp);
    if (st != AURA_ENGINE_OK || !resp.body) {
        std::string m = "dispatch failed (status=" +
                        std::to_string((int)st) + ")";
        emit_error_json("dispatch_failed", m, g.compact);
        aura_engine_response_dispose(&resp);
        aura_orchestrator_destroy(orch);
        return 1;
    }
    auto *body = static_cast<AuraRizinAnalyzeBody *>(resp.body);
    const AuraFunctionRecord *funcs = aura_rizin_analyze_body_functions(body);

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "llm-context");
    cJSON_AddStringToObject(root, "binary", binary.c_str());

    int rc = 0;
    if (has_func) {
        // Per-function mode.
        size_t idx = find_func_by_entry(funcs, body->functions_count, func_addr);
        if (idx == SIZE_MAX) {
            std::string m = "no function at entry 0x";
            char buf[20]; std::snprintf(buf, sizeof(buf), "%llx",
                                        (unsigned long long)func_addr);
            m += buf;
            emit_error_json("function_not_found", m, g.compact);
            rc = 1;
        } else {
            cJSON_AddStringToObject(root, "mode", "function");
            char *dec = nullptr;
            if (with_decompile) {
                dec = decompile_function_text(orch, binary, func_addr, g);
            }
            cJSON_AddItemToObject(root, "function",
                                  make_function_card(body, idx, dec));
            std::free(dec);
        }
    } else {
        // Whole-binary mode.
        cJSON_AddStringToObject(root, "mode", "binary");
        cJSON_AddNumberToObject(root, "functions_count",
                                static_cast<double>(body->functions_count));
        cJSON *arr = cJSON_AddArrayToObject(root, "functions");
        for (size_t i = 0; i < body->functions_count; ++i) {
            char *dec = nullptr;
            if (with_decompile) {
                dec = decompile_function_text(orch, binary,
                                              funcs[i].entry, g);
            }
            cJSON_AddItemToArray(arr, make_function_card(body, i, dec));
            std::free(dec);
        }
    }

    if (rc == 0) emit_json(root, g.compact);
    cJSON_Delete(root);
    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);
    return rc;
}

// ── probe-engines (Phase 2.5.1 Slice X.4) ──────────────────────────────────
//
// Runs the engine-agnostic probe registry against a real subprocess
// command runner and emits the standard envelope so consumers (CLI
// users, GUI bootstrap, automation tooling) see a stable JSON shape.
//
// Body schema:
//   { engines: [ { engine_id, status, detected_version, install_hint*,
//                  required_runtime, raw_diagnostic, probed_at_ms }, ... ] }
//
// engines[] is array form (not object-keyed) per the integration
// contract test (probe_engines_smoke.cpp). Five entries always:
// rizin, ghidra-decomp, ghidra-full, angr, retdec.

int run_probe_engines(const GlobalOpts &g) {
    /* Phase 2.5.2 X.8 fix (Codex review #4 high #1, #5 high): the probe
     * resolver consults AURA_REPO_ROOT to honor the vendored lookup
     * tier (third_party/<engine>/...). Set it before collecting probes
     * so a normal repo checkout with vendored binaries on disk is
     * detected, even when the user has not exported AURA_REPO_ROOT —
     * OR has exported it as an empty string (the resolver treats empty
     * as unset, so we must overwrite to reach vendored). */
    seed_repo_root_env_for_cli();

    AuraCommandRunner *runner = aura_command_runner_subprocess_create(5000);
    if (!runner) {
        emit_error_json("probe_init_failed",
                        "could not create subprocess command runner",
                        g.compact);
        return 1;
    }

    char *flat_json = nullptr;
    int rc = aura_probe_collect_all(runner, &flat_json);
    aura_command_runner_subprocess_destroy(runner);
    if (rc != 0 || !flat_json) {
        emit_error_json("probe_collect_failed",
                        "aura_probe_collect_all returned non-zero",
                        g.compact);
        std::free(flat_json);
        return 1;
    }

    cJSON *flat = cJSON_Parse(flat_json);
    std::free(flat_json);
    if (!flat) {
        emit_error_json("probe_parse_failed",
                        "registry emitted invalid JSON", g.compact);
        return 1;
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "probe-engines");
    cJSON *body = cJSON_AddObjectToObject(root, "body");
    cJSON *engines = cJSON_AddArrayToObject(body, "engines");

    /* Flatten the {engine_id: result_obj, ...} object into the array form
     * the integration contract expects. We detach from the head of
     * `flat` repeatedly until empty — same insertion order as the
     * registry table (rizin first, retdec last). The result objects
     * already carry their own engine_id field, so no key is lost. */
    cJSON *child = nullptr;
    while ((child = flat->child) != nullptr) {
        cJSON *detached = cJSON_DetachItemViaPointer(flat, child);
        if (!detached) break;
        cJSON_AddItemToArray(engines, detached);
    }
    cJSON_Delete(flat);

    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}

int run_info(const std::string &binary, const GlobalOpts &g) {
    BinaryInfo info{};
    parse_header(binary, info);

    uint8_t digest[AURA_SHA256_DIGEST_LEN];
    if (aura_sha256_file(binary.c_str(), digest) == 0) {
        char hex[AURA_SHA256_DIGEST_LEN * 2 + 1];
        aura_sha256_hex(digest, hex);
        info.sha256_hex = hex;
    } else {
        emit_error_json("file_read_failed",
                        "could not read " + binary, g.compact);
        return 1;
    }

    cJSON *root = make_root();
    cJSON_AddStringToObject(root, "command", "info");
    cJSON_AddStringToObject(root, "binary", binary.c_str());
    cJSON *fp = cJSON_AddObjectToObject(root, "fingerprint");
    cJSON_AddNumberToObject(fp, "file_size",
                            static_cast<double>(info.file_size));
    cJSON_AddStringToObject(fp, "sha256", info.sha256_hex.c_str());
    cJSON_AddStringToObject(fp, "format_kind", info.format_kind.c_str());
    cJSON_AddNumberToObject(fp, "image_base",
                            static_cast<double>(info.image_base));
    cJSON_AddNumberToObject(fp, "entry", static_cast<double>(info.entry));

    emit_json(root, g.compact);
    cJSON_Delete(root);
    return 0;
}

}  // namespace

// ── main ───────────────────────────────────────────────────────────────────

int main(int argc, char **argv) {
    /* Phase 2.5.1 Slice X.4: handle `aura --probe-engines` before CLI11
     * subcommand parsing so it does not need to coexist with the
     * require_subcommand(1) constraint. This subcommand is intentionally
     * orthogonal — it doesn't take a binary path and doesn't dispatch
     * to any engine. */
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--probe-engines") == 0) {
            GlobalOpts gp;
            for (int j = 1; j < argc; ++j) {
                if (std::strcmp(argv[j], "--compact") == 0) gp.compact = true;
            }
            return run_probe_engines(gp);
        }
    }

    CLI::App app{"aura — RE-tool orchestrator + LLM context provider"};
    app.set_version_flag("--version", "aura 0.1.0");
    app.require_subcommand(1);

    GlobalOpts g;
    app.add_flag("--compact", g.compact, "compact JSON output (no indent)");
    app.add_option("--engine", g.engine_id,
                   "explicit engine id (default: primary set policy)");
    app.add_option("--rizin", g.rizin_bin_path,
                   "path to rizin binary (default: $AURA_RIZIN_BIN, "
                   "vendored third_party/rizin, or PATH)");

    // analyze
    auto *cmd_analyze = app.add_subcommand(
        "analyze", "ANALYZE dispatch → unified model JSON");
    std::string analyze_bin;
    std::string analyze_string_protection_mode = "off";
    bool analyze_string_protection_legacy = false;
    cmd_analyze->add_option("binary", analyze_bin, "path to binary")
        ->required()
        ->check(CLI::ExistingFile);
    cmd_analyze
        ->add_option("--string-protection-mode",
                     analyze_string_protection_mode,
                     "string protection mode: off, scan-only, mask")
        ->check(CLI::IsMember({"off", "scan-only", "mask"}));
    cmd_analyze->add_flag(
        "--string-protection", analyze_string_protection_legacy,
        "compatibility alias for --string-protection-mode mask");

    // field-candidates (Phase 11.4.4 / P4.PP2 — struct field misidentification)
    auto *cmd_fldc = app.add_subcommand(
        "field-candidates",
        "PP2 struct field offsets → grouped by base register + stack cluster");
    std::string fldc_bin;
    std::string fldc_func_str;
    cmd_fldc->add_option("binary", fldc_bin, "path to binary")
        ->required()->check(CLI::ExistingFile);
    cmd_fldc->add_option("--func", fldc_func_str,
                         "function entry address (hex)")->required();

    // array-candidates (Phase 11.4.5 / P4.PP3 — array/pointer expression)
    auto *cmd_arrc = app.add_subcommand(
        "array-candidates",
        "PP3 array shape raw stat → variable cluster diffs/gcd + type literals");
    std::string arrc_bin;
    std::string arrc_func_str;
    cmd_arrc->add_option("binary", arrc_bin, "path to binary")
        ->required()->check(CLI::ExistingFile);
    cmd_arrc->add_option("--func", arrc_func_str,
                         "function entry address (hex)")->required();

    // propagate-type (Phase 11.4.3 / P4.PP1 — type propagation v1)
    auto *cmd_prop = app.add_subcommand(
        "propagate-type",
        "PP1 propagate type → ranked candidates rooted at a caller function");
    std::string prop_bin;
    std::string prop_func_str;
    std::string prop_target_type;
    std::string prop_project;
    std::string prop_candidate_ids;
    bool        prop_apply = false;
    bool        prop_apply_all = false;
    cmd_prop->add_option("binary", prop_bin, "path to binary")
        ->required()->check(CLI::ExistingFile);
    cmd_prop->add_option("--func", prop_func_str,
                         "caller function entry (hex)")->required();
    cmd_prop->add_option("--target-type", prop_target_type,
                         "proposed type (e.g. \"UserStruct*\")")
        ->required();
    cmd_prop->add_flag("--apply", prop_apply,
                       "write selected candidates to override store");
    cmd_prop->add_option("--project", prop_project,
                         "SQLite project path for --apply. Falls back to "
                         "$AURA_PROJECT env.");
    cmd_prop->add_option("--candidate-ids", prop_candidate_ids,
                         "comma-separated zero-based candidate ids for --apply");
    cmd_prop->add_flag("--all", prop_apply_all,
                       "apply all candidates");

    // label-candidates (Phase 11.4.2 / P4.PP4 — auto labelling)
    auto *cmd_lblc = app.add_subcommand(
        "label-candidates",
        "PP4 auto labelling → ranked rename suggestions for a function");
    std::string lblc_bin;
    std::string lblc_func_str;
    cmd_lblc->add_option("binary", lblc_bin, "path to binary")
        ->required()->check(CLI::ExistingFile);
    cmd_lblc->add_option("--func", lblc_func_str,
                         "function entry address (hex, e.g. 0x401000)")
        ->required();

    // cfg (Phase 11.3.8 / P2.F3 — control flow graph)
    auto *cmd_cfg = app.add_subcommand(
        "cfg",
        "CFG view → per-function blocks[] + edges[] (analyze body filter)");
    std::string cfg_bin;
    std::string cfg_func_str;
    cmd_cfg->add_option("binary", cfg_bin, "path to binary")
        ->required()->check(CLI::ExistingFile);
    cmd_cfg->add_option("--func", cfg_func_str,
                        "function entry address (hex, e.g. 0x401000)")
        ->required();

    // disasm (Phase 11.3.7 / P2.F2 — instruction-level disassembly)
    auto *cmd_disasm = app.add_subcommand(
        "disasm", "DISASM dispatch → per-function instruction list (pdfj)");
    std::string disasm_bin;
    std::string disasm_func_str;
    cmd_disasm->add_option("binary", disasm_bin, "path to binary")
        ->required()
        ->check(CLI::ExistingFile);
    cmd_disasm->add_option("--func", disasm_func_str,
                           "function entry address (hex, e.g. 0x401000)")
        ->required();

    // info
    auto *cmd_info = app.add_subcommand(
        "info", "binary fingerprint (file_size, sha256, format, entry)");
    std::string info_bin;
    cmd_info->add_option("binary", info_bin, "path to binary")
        ->required()
        ->check(CLI::ExistingFile);

    // engines
    auto *cmd_engines = app.add_subcommand(
        "engines", "list registered engines + availability (debug)");

    // override (Phase 11.4 — list/get/delete only; put pending Q10)
    auto *cmd_override = app.add_subcommand(
        "override", "user override store CRUD (Phase 4B)");
    cmd_override->require_subcommand(1);
    std::string ov_project;
    auto add_project = [&](CLI::App *sub) {
        sub->add_option("--project", ov_project,
                        "SQLite project path (dir → aura.db, or .db file). "
                        "Falls back to $AURA_PROJECT env.");
    };
    std::string ov_bin;
    auto add_binary = [&](CLI::App *sub) {
        sub->add_option("binary", ov_bin, "path to binary")
            ->required()->check(CLI::ExistingFile);
    };

    auto *cmd_ov_list = cmd_override->add_subcommand(
        "list", "list overrides for a binary");
    add_binary(cmd_ov_list);
    add_project(cmd_ov_list);

    auto *cmd_ov_get = cmd_override->add_subcommand(
        "get", "fetch one override by function anchor address");
    add_binary(cmd_ov_get);
    add_project(cmd_ov_get);
    std::string ov_get_func;
    bool ov_get_no_analyze = false;
    cmd_ov_get->add_option("--func", ov_get_func, "function entry address (hex)")
        ->required();
    cmd_ov_get->add_flag("--no-analyze", ov_get_no_analyze,
                         "skip ANALYZE (must match how the row was put)");

    auto *cmd_ov_delete = cmd_override->add_subcommand(
        "delete", "remove one override by function anchor address");
    add_binary(cmd_ov_delete);
    add_project(cmd_ov_delete);
    std::string ov_del_func;
    bool ov_del_no_analyze = false;
    cmd_ov_delete->add_option("--func", ov_del_func,
                              "function entry address (hex)")->required();
    cmd_ov_delete->add_flag("--no-analyze", ov_del_no_analyze,
                            "skip ANALYZE (must match how the row was put)");

    auto *cmd_ov_put = cmd_override->add_subcommand(
        "put", "create/replace an override (PENDING Q10 — dispatch policy)");
    add_binary(cmd_ov_put);
    add_project(cmd_ov_put);
    std::string ov_put_func, ov_put_rename;
    cmd_ov_put->add_option("--func", ov_put_func,
                           "function entry address (hex)")->required();
    cmd_ov_put->add_option("--rename", ov_put_rename,
                           "new function name (RENAME payload)")->required();
    bool ov_put_no_analyze = false;
    cmd_ov_put->add_flag("--no-analyze", ov_put_no_analyze,
                         "skip ANALYZE dispatch — fast (<1s) but WEAK "
                         "confidence (Phase 4A). Default: dispatch ANALYZE "
                         "to derive STRONG/EXACT confidence.");

    // llm-context
    auto *cmd_llm = app.add_subcommand(
        "llm-context",
        "function metadata payload for LLM consumption (vendor-neutral)");
    std::string llm_bin;
    std::string llm_func_str;
    bool        llm_with_decompile = false;
    cmd_llm->add_option("binary", llm_bin, "path to binary")
        ->required()
        ->check(CLI::ExistingFile);
    cmd_llm->add_option("--func", llm_func_str,
                        "single function entry address (hex, e.g. 0x401000); "
                        "omit for whole-binary mode");
    cmd_llm->add_flag("--with-decompile", llm_with_decompile,
                      "include decompile text per function (extra dispatch)");

    // gui: connect to a running aura-gui RPC server.
    auto *cmd_gui = app.add_subcommand(
        "gui", "control a running aura-gui via localhost IPC/RPC");
    cmd_gui->require_subcommand(1);
    GuiRpcOpts gui_rpc;
    gui_rpc.port = gui_rpc_default_port();
    gui_rpc.token = gui_rpc_default_token();
    cmd_gui->add_option("--port", gui_rpc.port,
                        "aura-gui RPC port (default: $AURA_GUI_RPC_PORT or 27654)");
    cmd_gui->add_option("--token", gui_rpc.token,
                        "aura-gui RPC token (default: $AURA_GUI_RPC_TOKEN)");

    auto *cmd_gui_status = cmd_gui->add_subcommand(
        "status", "check connection and report GUI project/analyze state");

    auto *cmd_gui_open = cmd_gui->add_subcommand(
        "open-project", "open a project DB in the running GUI");
    std::string gui_project_path;
    cmd_gui_open->add_option("path", gui_project_path, "project DB path")
        ->required();

    auto *cmd_gui_add = cmd_gui->add_subcommand(
        "add-binary", "add a binary to the running GUI project");
    std::string gui_binary_path;
    cmd_gui_add->add_option("path", gui_binary_path, "binary path")
        ->required()->check(CLI::ExistingFile);

    auto *cmd_gui_analyze = cmd_gui->add_subcommand(
        "analyze", "run GUI analysis for a project binary row");
    int gui_analyze_row = 0;
    std::string gui_analyze_level = "full";
    cmd_gui_analyze->add_option("--row", gui_analyze_row,
                                "project binary row (default: 0)");
    cmd_gui_analyze->add_option("--level", gui_analyze_level,
                                "quick, full, or advanced");

    auto *cmd_gui_functions = cmd_gui->add_subcommand(
        "functions", "list functions currently loaded in the GUI");

    auto *cmd_gui_decompile = cmd_gui->add_subcommand(
        "decompile", "decompile a function row in the running GUI");
    int gui_function_row = 0;
    cmd_gui_decompile->add_option("--row", gui_function_row,
                                  "function row (default: 0)");

    auto *cmd_gui_jump_string = cmd_gui->add_subcommand(
        "jump-string", "jump GUI decompiler to the xref of a string row");
    int gui_string_row = 0;
    cmd_gui_jump_string->add_option("--row", gui_string_row,
                                    "string row (default: 0)");

    auto *cmd_gui_strings = cmd_gui->add_subcommand(
        "strings", "list strings from the last GUI analysis");
    auto *cmd_gui_protected_strings = cmd_gui->add_subcommand(
        "protected-strings",
        "list LLM/MCP-safe protected strings from the last GUI analysis");
    auto *cmd_gui_symbols = cmd_gui->add_subcommand(
        "symbols", "list symbols from the last GUI analysis");
    auto *cmd_gui_xrefs = cmd_gui->add_subcommand(
        "xrefs", "list xrefs from the last GUI analysis");
    auto *cmd_gui_quit = cmd_gui->add_subcommand(
        "quit", "ask the running GUI to quit");

    CLI11_PARSE(app, argc, argv);

    if (cmd_engines->parsed()) return run_engines(g);
    if (cmd_analyze->parsed()) {
        const auto protection_mode =
            analyze_string_protection_legacy
                ? aura::safety::StringProtectionMode::Mask
                : aura::safety::parseStringProtectionMode(
                      analyze_string_protection_mode);
        return run_analyze(analyze_bin, protection_mode, g);
    }
    if (cmd_disasm->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(disasm_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + disasm_func_str,
                            g.compact);
            return 2;
        }
        return run_disasm(disasm_bin, addr, g);
    }
    if (cmd_cfg->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(cfg_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + cfg_func_str,
                            g.compact);
            return 2;
        }
        return run_cfg(cfg_bin, addr, g);
    }
    if (cmd_lblc->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(lblc_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + lblc_func_str,
                            g.compact);
            return 2;
        }
        return run_label_candidates(lblc_bin, addr, g);
    }
    if (cmd_prop->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(prop_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + prop_func_str,
                            g.compact);
            return 2;
        }
        return run_propagate_type(prop_bin, addr, prop_target_type,
                                  prop_apply, prop_project,
                                  prop_candidate_ids, prop_apply_all, g);
    }
    if (cmd_fldc->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(fldc_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + fldc_func_str,
                            g.compact);
            return 2;
        }
        return run_field_candidates(fldc_bin, addr, g);
    }
    if (cmd_arrc->parsed()) {
        uint64_t addr = 0;
        try { addr = std::stoull(arrc_func_str, nullptr, 0); }
        catch (...) {
            emit_error_json("invalid_func_addr",
                            "could not parse --func as hex: " + arrc_func_str,
                            g.compact);
            return 2;
        }
        return run_array_candidates(arrc_bin, addr, g);
    }
    if (cmd_info->parsed())    return run_info(info_bin, g);
    if (cmd_override->parsed()) {
        auto parse_addr = [&](const std::string &s, uint64_t &out) -> bool {
            try { out = std::stoull(s, nullptr, 0); return true; }
            catch (...) { return false; }
        };
        if (cmd_ov_list->parsed()) {
            return run_override_list(ov_bin, ov_project, g);
        }
        if (cmd_ov_get->parsed()) {
            uint64_t addr = 0;
            if (!parse_addr(ov_get_func, addr)) {
                emit_error_json("invalid_func_addr", ov_get_func, g.compact);
                return 2;
            }
            return run_override_get(ov_bin, addr, ov_project,
                                    ov_get_no_analyze, g);
        }
        if (cmd_ov_delete->parsed()) {
            uint64_t addr = 0;
            if (!parse_addr(ov_del_func, addr)) {
                emit_error_json("invalid_func_addr", ov_del_func, g.compact);
                return 2;
            }
            return run_override_delete(ov_bin, addr, ov_project,
                                       ov_del_no_analyze, g);
        }
        if (cmd_ov_put->parsed()) {
            uint64_t addr = 0;
            if (!parse_addr(ov_put_func, addr)) {
                emit_error_json("invalid_func_addr", ov_put_func, g.compact);
                return 2;
            }
            return run_override_put(ov_bin, addr, ov_put_rename, ov_project,
                                    ov_put_no_analyze, g);
        }
    }
    if (cmd_gui->parsed()) {
        auto params_object = []() { return cJSON_CreateObject(); };
        if (cmd_gui_status->parsed()) {
            return run_gui_rpc("status", params_object(), gui_rpc, g,
                               "gui status");
        }
        if (cmd_gui_open->parsed()) {
            cJSON *p = params_object();
            cJSON_AddStringToObject(p, "path", gui_project_path.c_str());
            return run_gui_rpc("open_project", p, gui_rpc, g,
                               "gui open-project");
        }
        if (cmd_gui_add->parsed()) {
            cJSON *p = params_object();
            cJSON_AddStringToObject(p, "path", gui_binary_path.c_str());
            return run_gui_rpc("add_binary", p, gui_rpc, g,
                               "gui add-binary");
        }
        if (cmd_gui_analyze->parsed()) {
            if (gui_analyze_level != "quick" &&
                gui_analyze_level != "full" &&
                gui_analyze_level != "advanced") {
                emit_error_json("invalid_analysis_level",
                                "--level must be quick, full, or advanced",
                                g.compact);
                return 2;
            }
            cJSON *p = params_object();
            cJSON_AddNumberToObject(p, "row", gui_analyze_row);
            cJSON_AddStringToObject(p, "level", gui_analyze_level.c_str());
            return run_gui_rpc("analyze", p, gui_rpc, g, "gui analyze");
        }
        if (cmd_gui_functions->parsed()) {
            return run_gui_rpc("function_list", params_object(), gui_rpc, g,
                               "gui functions");
        }
        if (cmd_gui_decompile->parsed()) {
            cJSON *p = params_object();
            cJSON_AddNumberToObject(p, "function_row", gui_function_row);
            return run_gui_rpc("decompile", p, gui_rpc, g, "gui decompile");
        }
        if (cmd_gui_jump_string->parsed()) {
            cJSON *p = params_object();
            cJSON_AddNumberToObject(p, "string_row", gui_string_row);
            return run_gui_rpc("jump_string_reference", p, gui_rpc, g,
                               "gui jump-string");
        }
        if (cmd_gui_strings->parsed()) {
            return run_gui_rpc("list_strings", params_object(), gui_rpc, g,
                               "gui strings");
        }
        if (cmd_gui_protected_strings->parsed()) {
            return run_gui_rpc("list_protected_strings", params_object(),
                               gui_rpc, g, "gui protected-strings");
        }
        if (cmd_gui_symbols->parsed()) {
            return run_gui_rpc("list_symbols", params_object(), gui_rpc, g,
                               "gui symbols");
        }
        if (cmd_gui_xrefs->parsed()) {
            return run_gui_rpc("list_xrefs", params_object(), gui_rpc, g,
                               "gui xrefs");
        }
        if (cmd_gui_quit->parsed()) {
            return run_gui_rpc("quit", params_object(), gui_rpc, g,
                               "gui quit");
        }
    }
    if (cmd_llm->parsed()) {
        bool has_func = !llm_func_str.empty();
        uint64_t addr = 0;
        if (has_func) {
            try {
                addr = std::stoull(llm_func_str, nullptr, 0);
            } catch (...) {
                emit_error_json("invalid_func_addr",
                                "could not parse --func: " + llm_func_str,
                                g.compact);
                return 2;
            }
        }
        return run_llm_context(llm_bin, has_func, addr, llm_with_decompile, g);
    }
    return 0;
}
