# Phase 4A — Stable Identity Contract

**Status**: Implemented (2026-05-01)
**Files**: `include/override_identity.h`, `src/core/override_identity.c`
**Tests**: `tests/core/test_override_identity.c` (TC-1..TC-15)

---

## Problem

When AURA re-analyzes a binary, engine-assigned IDs (function addresses, variable names) may shift. Without a stable key, user overrides (renames, type annotations) can silently land on the wrong target or be dropped entirely. Silent misapply is a correctness violation.

---

## Design Rules

**R-5**: Engine output (`AuraEngineResponse.raw`, `.body`) is immutable from AURA's perspective. Override application produces a separate display-layer view (Phase 4C). No mutation here.

**R-9**: The override layer performs no new analysis — no CFG, no type inference, no function matching. Stable IDs are assembled from existing engine record fields only.

---

## 4A.X1 — Binary Fingerprint (Outermost Guard)

```c
typedef struct AuraOverrideBinaryFingerprint {
    uint64_t file_size;
    uint8_t  sha256[32];
    char     format_kind[8];        /* "elf" / "pe" / "mach-o" / "unknown" */
    uint64_t image_base;            /* 0 = unknown / not applicable */
    uint8_t  text_section_hash[32]; /* all-zero = not computed */
} AuraOverrideBinaryFingerprint;
```

If `binary_fingerprint` differs from the stored key's fingerprint, auto-apply is **forbidden** regardless of any other field match. `fingerprint` is an identifier, not an analysis result.

Comparison rules (`aura_override_fingerprint_match`):
- `file_size`, `sha256[32]`, `format_kind` always compared.
- `image_base`: compared only if both sides are non-zero.
- `text_section_hash`: compared only if both sides are non-zero.

---

## 4A.X2 — function_stable_id Priority

Derived from `AuraFunctionRecord` fields in priority order:

| Priority | Condition | `function_stable_id` | Confidence |
|---|---|---|---|
| 1 | `record->function_id != AURA_NULL_ID` | `record->function_id` | EXACT |
| 2 | `entry != 0 && size != 0 && provenance.source[0] != '\0'` | `record->entry` | STRONG |
| 3 | `entry != 0 && size != 0 && name[0] != '\0'` | `record->entry` | WEAK |
| 4 | None of the above | `0` | MISSING |

---

## 4A.X3 — Engine Metadata

`AuraOverrideKey` carries engine identity to prevent cross-engine misapply:

- `engine_id[32]` ← `manifest->engine_id`
- `engine_version[32]` ← `manifest->version`
- `body_schema_version` and `normalized_record_schema_version` are reserved for future schema evolution.

`aura_override_key_same_target` compares `engine_id` as a first-class discriminator.

---

## 4A.X4 — Overlay Boundary

`AuraEngineResponse.raw` and `.body` are immutable from AURA's perspective. Override application in Phase 4C produces a separate `AuraOverrideView`. No mutation of engine output occurs in this layer.

---

## Confidence Policy

| Level | Auto-apply | Description |
|---|---|---|
| EXACT | YES | Engine-provided stable id + binary fingerprint match |
| STRONG | YES | Binary fingerprint + engine_id + function address/range + target address/storage + provenance source |
| WEAK | NO | Name / index / estimated position only. Must be promoted to conflict for UI review |
| MISSING | NO | Target not found after re-analysis. Preserved as orphan |

**Silent misapply is forbidden**: if confidence < STRONG, the override MUST NOT be applied automatically and MUST be preserved in a conflict/orphan state for explicit user resolution.

---

## Helper API

| Function | Purpose |
|---|---|
| `aura_override_key_from_function_record` | Build key + derive confidence (4A.X2) from `AuraFunctionRecord` |
| `aura_override_key_from_variable_record` | Build key for `AuraVariableRecord`; target_kind = VARIABLE |
| `aura_override_fingerprint_match` | Exact binary comparison per 4A.X1 rules |
| `aura_override_confidence_allows_auto_apply` | Returns true only for EXACT and STRONG |
| `aura_override_key_same_target` | Same target if engine_id + fingerprint + request_type + function/target stable ids all match; confidence intentionally excluded |

---

## Phase 4 Gate

Phase 4A is the gate condition for 4B–4E. SQLite store (4B), overlay apply (4C), and conflict persistence must not be implemented until this sub-phase is complete and GREEN.

---

## Phase 4D / 4E Scope Decisions (2026-05-02)

### 4D — propagation policy

- Override application is **rendering-time lookup only**. Setting a rename or type override creates exactly one row; no cascade rows are written.
- `AuraOverrideView::lookup(function_id, target_kind, target_stable_id)` is the single source of truth at render time.
- def-use / caller-callee / struct-field cascades are **not implemented**. Reason: the current `AuraRecordCollection` does not expose these relationships explicitly enough to honor R-9 (no new analysis); a future Phase 4D follow-up will revisit when adapter coverage clarifies what is engine-derived.

### 4E.1 — re-analysis matching policy (conservative)

- FUNCTION targets match by **exact entry address** (`target_addr`). Stored keys always carry `target_addr = record->entry` after Phase 4E (key derivation extended 2026-05-02).
- Function name fallback is **forbidden**.
- VARIABLE / TYPE / ANNOTATION / ADDRESS / SYMBOL targets currently classify as ORPHAN. Cross-run variable matching requires a parent-function anchor not yet stored in the key contract; deferred to a Phase 4D follow-up.
- Ambiguous match (multiple fresh records at the same entry) → ORPHAN.
- Fingerprint mismatch → CONFLICT (not ORPHAN). Rationale: the user's override may still be semantically meaningful in the new binary, but silent-misapply is forbidden — promote to user review.

### 4E.2 — UI flow

- conflict / orphan UI flow is deferred to **Phase 5 GUI**. Phase 4 ships the status persistence + classification API (`set_status`, `count_by_status`, `resolve_pass` stats) and stops there.
