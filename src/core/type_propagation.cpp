/*
 * type_propagation.cpp — derived view algorithm per ADR-0045 D2.
 *
 * Pure lookup over engine records (no analysis, no inference). Builds
 * indices for O(1) callee→arg-variables and var→type_fact lookup, then
 * walks the caller's call_edges to emit one candidate per (call site,
 * callee arg) pair.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "aura/type_propagation.h"

#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>

#include "rizin_adapter.h"
#include "aura/normalized_records.h"

namespace {

void copy_str(char *dst, size_t cap, const char *src) {
    if (cap == 0) return;
    if (!src) { dst[0] = '\0'; return; }
    size_t n = std::strlen(src);
    if (n >= cap) n = cap - 1;
    std::memcpy(dst, src, n);
    dst[n] = '\0';
}

}  // namespace

extern "C" int aura_type_propagation_generate(
    const AuraRizinAnalyzeBody *body,
    uint64_t                    caller_entry,
    const char                 *target_type,
    AuraTypePropagationResult  *out)
{
    if (!body || !target_type || !out) return -1;
    out->items = nullptr;
    out->count = 0;

    /* 1. Resolve caller function_id by entry. */
    const AuraFunctionRecord *fns = aura_rizin_analyze_body_functions(body);
    AuraFunctionId callerId = AURA_NULL_ID;
    for (size_t i = 0; i < body->functions_count; ++i) {
        if (fns[i].entry == caller_entry) { callerId = fns[i].function_id; break; }
    }
    if (callerId == AURA_NULL_ID) {
        /* Caller not found — empty result is success (matches PP4 path). */
        return 0;
    }

    /* 2. Index variables by function_id (only "arg" kind) and type_facts
     *    by var_id. Both for O(1) lookup in the callee walk. */
    std::map<AuraFunctionId, std::vector<const AuraVariableRecord *>> argsByFn;
    const AuraVariableRecord *vrs = aura_rizin_analyze_body_variables(body);
    for (size_t i = 0; vrs && i < body->variables_count; ++i) {
        if (std::strncmp(vrs[i].kind, "arg", 4) == 0) {
            argsByFn[vrs[i].function_id].push_back(&vrs[i]);
        }
    }
    std::map<AuraVariableId, const AuraTypeFactRecord *> typeByVar;
    const AuraTypeFactRecord *tfs = aura_rizin_analyze_body_type_facts(body);
    for (size_t i = 0; tfs && i < body->type_facts_count; ++i) {
        if (tfs[i].var_id != AURA_NULL_ID) typeByVar[tfs[i].var_id] = &tfs[i];
    }

    /* 3. Walk call_edges; for each whose caller_id matches the requested
     *    function, enumerate callee args and emit one candidate per arg. */
    std::vector<AuraTypePropagationCandidate> raw;
    const AuraCallEdgeRecord *ces = aura_rizin_analyze_body_call_edges(body);
    for (size_t i = 0; ces && i < body->call_edges_count; ++i) {
        const auto &ce = ces[i];
        if (ce.caller_id != callerId) continue;
        if (ce.callee_id == AURA_NULL_ID) continue;  // unresolved (indirect)

        auto it = argsByFn.find(ce.callee_id);
        if (it == argsByFn.end()) continue;
        for (const auto *arg : it->second) {
            AuraTypePropagationCandidate c;
            std::memset(&c, 0, sizeof(c));
            c.var_id          = arg->var_id;
            c.function_id     = ce.callee_id;
            c.call_site_addr  = ce.site_addr;
            c.distance        = 1;
            copy_str(c.source,   sizeof(c.source),   "callee_param");
            copy_str(c.new_type, sizeof(c.new_type), target_type);
            auto tfIt = typeByVar.find(arg->var_id);
            const char *old = (tfIt != typeByVar.end())
                                  ? tfIt->second->type_str
                                  : "";
            copy_str(c.old_type, sizeof(c.old_type), old);
            raw.push_back(c);
        }
    }

    /* 4. Hand back as malloc'd block (callers may be C). */
    if (raw.empty()) return 0;
    auto *items = static_cast<AuraTypePropagationCandidate *>(
        std::malloc(sizeof(AuraTypePropagationCandidate) * raw.size()));
    if (!items) return -1;
    for (size_t i = 0; i < raw.size(); ++i) items[i] = raw[i];
    out->items = items;
    out->count = raw.size();
    return 0;
}

extern "C" void aura_type_propagation_result_free(
    AuraTypePropagationResult *r)
{
    if (!r) return;
    std::free(r->items);
    r->items = nullptr;
    r->count = 0;
}
