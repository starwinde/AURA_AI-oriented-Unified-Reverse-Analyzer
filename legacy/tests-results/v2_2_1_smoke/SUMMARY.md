# v2.2.1 Canonical Smoke Baseline

**Date**: 2026-04-19
**HEAD**: `7fcea56` (post-P1.5 PHASE_H_DEFERRED stubs)
**Status**: CANONICAL baseline the v2.2.1 release tag will reference

---

## Smoke Result

**90 / 90 GREEN** (threshold: 85 of 90 must pass, ±20%)

Per-binary breakdown:
- cat      : 20 / 20
- ls       : 20 / 20
- aura_self: 50 / 50

Command: `bash tests/decompiler/test_real_binary_smoke.sh`
Output : `tests/results/v2_2_1_smoke/smoke_output.txt`

## ctest

- build-rel : 127 / 127 PASS
- build-asan: 127 / 127 PASS

## FUN_001b4b2c Sentinel (aura_self worst-case regression target)

- Address       : `0xb4b2c`
- Current lines : 113
- v2.1.0 fixture: 113 (`tests/results/phase_f_complete_2026_04_18/aura_self/aura/FUN_001b4b2c_0x1b4b2c.c`)
- md5 (both)    : `6ec5c8f78cdcc9d27e8cc0c630483653`
- Verdict       : **byte-exact match** — H lever regression fully reverted

## Phase 1 Commit Chain (RED → GREEN)

| Commit   | Step | Smoke  | Note                                         |
|----------|------|--------|----------------------------------------------|
| a865340  | P1.1 | 49/41  | WIP RED capture baseline                     |
| 00b74e8  | P1.2 | 46/44  | H-4 param pointer-width narrowing reverted   |
| 28dc520  | P1.3 | 50/40  | H-1 constant-condition if elision reverted   |
| 98d8e1e  | P1.4 | 90/0 G | H-2 struct→array promotion full revert       |
| 7fcea56  | P1.5 | 90/0 G | H-1/H-4 unit tests SKIP-stubbed (PHASE_H_DEFERRED) |

## References

- P1.1 RED baseline: `tests/results/v2_2_1_baseline_red/SUMMARY.md`
- Intermediate (post-H-2): `tests/results/v2_2_1_after_h2/{smoke_output.txt, NOTES.md}`
- v2.1.0 fixtures: `tests/results/phase_f_complete_2026_04_18/`

## Notes

- Binary `--version` still reports `AURA v2.2.0` at this point. Version bump is deferred to P1.7 (CHANGELOG + bump).
- This directory is the canonical baseline; do not delete intermediate `v2_2_1_after_*` — they are the audit trail.
