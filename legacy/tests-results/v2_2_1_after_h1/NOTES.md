# P1.3 — After H-1 revert

- Commit parent: `00b74e8` (post P1.2 H-4 revert)
- This revert touches: `src/decompiler/hir_emit.c` only
- Binary: `build-rel/aura` rebuilt, `--version` still `AURA v2.2.0`

## Smoke summary

| Stage                         | PASS / 90 | FAIL / 90 |
|-------------------------------|-----------|-----------|
| v2.2.0 baseline (P1.1 RED)    | 49        | 41        |
| After H-4 revert (P1.2)       | 46        | 44        |
| After H-1 revert (P1.3, here) | 50        | 40        |

Net improvement vs P1.2: +4 PASS. H-2 (P1.4) is expected to be the big jump.

## ctest delta

`test_hir_emit` now reports **38 PASS / 2 FAIL**. Failing subcases (expected):

- `test_const_cond_eliminated` — asserts `if (1)` elided; pre-H-1 production does not elide.
- `test_h4_param_pointer_width_narrows_to_int32` — still failing from P1.2.

Both are on P1.5's `PHASE_H_DEFERRED` SKIP list.

`test_if_else` PASS — the LOAD `<undef>` cond fixture still emits `if (…) { } else { }` as expected under pre-H-1 production.

No other ctest regressions.
