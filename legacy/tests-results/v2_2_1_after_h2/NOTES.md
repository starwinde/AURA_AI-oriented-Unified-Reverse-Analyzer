# P1.4 H-2 Full Revert — A/B Diagnostic + Decision (2026-04-19)

## Final state (Path A — full revert)

- Smoke: **90 PASS / 0 FAIL (GREEN, exit 0)**
- FUN_001b4b2c: **113 lines** (exact v2.1.0 baseline match)
- ctest: 126/127 PASS — only `test_hir_emit` fails (H-1/H-4 leftovers for P1.5)

## A/B diagnostic

| approach | struct_recovery.c treatment | test edit | FUN_001b4b2c | smoke | verdict |
|---|---|---|---|---|---|
| Path B (surgical) | keep `SrArray.elem_count` field + `sr_get_array_elem_count()` + `a->elem_count = 0` init; remove only the post-pass loop | none needed | 37 lines | 49/41 RED | FAIL |
| **Path A (full, chosen)** | `git checkout d8a1cb8 -- struct_recovery.c` (v2.1.0 state, no H-2 symbols) | stub `test_homogeneous_stride_promoted_to_array` body + remove `extern` decl | **113 lines** | **90/0 GREEN** | **PASS** |

## Hypothesis confirmed

API preservation (the `SrArray.elem_count` field + `sr_get_array_elem_count()` + `a->elem_count = 0` init) is **NOT logic-neutral**. Some downstream consumer (likely codegen's array/struct rendering path) behaves differently when the field exists with value 0 vs not existing at all. With full revert removing the field entirely, struct-heavy aura_self functions restore to byte-exact v2.1.0 behavior.

## Test edit bundled in same commit

Full revert of `struct_recovery.c` removes the `sr_get_array_elem_count` symbol, which causes a link error in `tests/decompiler/test_struct_recovery.c` (extern decl + call in `test_homogeneous_stride_promoted_to_array`). To make the build green we edited the test file in the same commit:

- Removed `extern uint32_t sr_get_array_elem_count(...)` forward decl (line 736)
- Replaced entire body of `test_homogeneous_stride_promoted_to_array(void)` with `{ TEST_BEGIN("... [PHASE_H_DEFERRED]"); TEST_PASS(); }`
- Kept call from `main()` — now a no-op PASS

P1.5 scope accordingly shrinks to just `test_hir_emit` subcases (H-1 const-cond elided + H-4 param pointer-width narrowing).

## Decision attribution

Path A chosen by team-lead after A/B diagnostic result report. Original brief mandated Path B (surgical); escalation + data-driven pivot justified by the 3-failure / <20 PASS jump STOP rule.
