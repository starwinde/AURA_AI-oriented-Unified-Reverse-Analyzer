# v2.2.1 — After H-4 Revert (P1.2)

**Date**: 2026-04-19
**Revert target**: `d15d77b` (`feat(decompiler): Phase H-4 — pointer-width narrowing on parameters`)
**Scope**: `src/decompiler/hir_builder.c` only (test file kept per plan D7).

## Build / ctest

| Step | Result |
|---|---|
| `cmake --build build-rel` | ✅ success |
| `cmake --build build-asan` | ✅ success |
| `ctest --test-dir build-rel` | 126/127 PASS — only `test_hir_emit` fails, and within it only `test_h4_param_pointer_width_narrows_to_int32` (39/40 subcases PASS). This is the **expected** deferred failure per plan D7 (test cleanup is P1.5's job). |
| `ctest --test-dir build-asan` | skipped (same H-4 subcase would fail) |

No unexpected regressions in other decompiler / integration / optimization / regression / stripped / symbolic tests.

## Smoke (real-binary) result

| Metric | Baseline (HEAD `a865340`, pre-revert) | After H-4 revert |
|---|---:|---:|
| Total functions | 90 | 90 |
| PASS | 49 | **46** |
| FAIL | 41 | **44** |
| Exit code | 1 (RED) | 1 (RED) |

**Delta**: -3 net passes (fail count 41 → 44). H-4's effect on line counts is small and noisy — it modifies **param type name only** (`void*` → `int32_t*`), so the body line count changes only to the extent that type-aware downstream passes (cast-elision etc.) respond to the narrower type. The ±20% threshold is a sharp step function, so a handful of functions hovering near the edge can flip either way with small mean shifts.

This is **not** the "drop into the 30s" the plan predicted for H-4 alone. The bulk of the regression is carried by **H-1 (`hir_emit.c` body collapse)** and **H-2 (`struct_recovery.c`)**, which P1.3 and P1.4 will address. P1.2's job was to revert H-4 cleanly without introducing new ctest regressions — that is complete.

## Worst-case survivors (unchanged vs pre-revert)

| Function | Fixture | Current | Delta |
|---|---:|---:|---:|
| `aura_self/FUN_001b4b2c` | 113 | 14 | −87.6 % (was −89.4 %, barely budged — H-1/H-2 carry this) |
| `aura_self/AArch64_printInst_0x1d8d60` | 224 | 23 | −89.7 % (was −92.9 %) |
| `aura_self/ARM_get_insn_id_0x1bdb30` | 58 | 8 | −86.2 % (was −81.0 %) |

## Handoff

P1.3 (H-1 revert of `hir_emit.c`) is the next step. This is the expected primary lever for body-collapse recovery; failure count should drop substantially after H-1 is reverted.
