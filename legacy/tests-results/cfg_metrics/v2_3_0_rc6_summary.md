# v2.3.0-rc6 Baseline Summary (Phase 2-D D-flips post-merge measurement)

**HEAD**: `bc3c93a` (main, post `45aaf32` D-1 + `9aa0c13` D-2 + `9e0e811` D-3 + audit chain)
**Date**: 2026-04-25
**Corpus**: 89 funcs (smoke: cat + ls + aura_self + Session #13 linked_noreturn fixture)
**Host**: aarch64 Linux (dgx-spark)
**Collector**: `tests/tooling/collect_cfg_metrics.sh --corpus smoke`

## Purpose

Re-measure the 90-function smoke corpus on main HEAD after all three Phase 2-D
default-on flips landed (D-1 cap 4096, D-2 DWARF noreturn, D-3 indirect resolver)
plus the four-commit audit chain (`ffd23bf` PLT-call HIR emit fix, `7c7405b` ASan
cat_hang skip, `7761cc0` collect timeout bump, `7135eac` ir_build_ssa cap-aware
guard, `01bbf9f`/`07c5541` `sa.aborts_oversize` counter, `4cf77ed` linked_noreturn
RED). rc4 was measured on `d5b361a` before the flips; rc6 is the new baseline
that callers should diff against to see the *net* effect of Phase 2-D.

## rc4 → rc6 counter diff (smoke corpus)

| counter                       | rc4 base | rc6 base | Δ      | reading |
|-------------------------------|---------:|---------:|-------:|---------|
| per_func_count                |       88 |       89 |     +1 | corpus +1 (linked_noreturn fixture) |
| cfg.cap_hits_512              |       82 |       68 |    **-14** | **D-1** cap 4096 default-on reduces hits (-17%) |
| cfg.indirect_call_skipped     |        0 |       56 |    **+56** | **D-3 + audit** wire fix routes register-indirect count |
| cfg.indirect_jmp_skipped      |        0 |      204 |   **+204** | **D-3 + audit** wire fix routes register-indirect count |
| cfg.funcs_built               |       88 |       89 |     +1 | corpus +1 |
| sa.funcs                      |       88 |       89 |     +1 | corpus +1 |
| sa.aborts                     |        0 |        0 |      0 | Cooper watchdog still cold post-flip |
| hir.gotos_emitted             |       20 |       21 |     +1 | corpus +1 (one extra goto emission) |
| hir.funcs_with_goto           |       20 |       21 |     +1 | corpus +1 |
| hir.noreturn_truncations      |        0 |        0 |      0 | architectural limit (memory `project_noreturn_truncation_counter.md`) |

## Reading

### D-1 (CFG cap 512 → 4096 default-on, main `45aaf32`)

`cap_hits_512` falls from 82 to 68 on the same baseline corpus (per_func_count
+1 from the linked_noreturn fixture is the only corpus change; the pre-existing
88 funcs alone account for the 14-hit drop). With cap 4096, large functions that
previously bailed at 512 BBs now build full CFGs. The cliff in /bin/cat
`FUN_00102cf4` is no longer a 120s hang — the SSA-dom convergence regression
gate (Session #14, backfilled by PR #34) measures it at 0.04s post-fix. The
D-1 promotion delivers what the rc1 data (cap_hits 93%) predicted.

### D-2 (DWARF noreturn default-on, main `9aa0c13`)

D-2's observable signal is per-function `/* NORETURN */` annotation frequency,
which lives in the `.jsonl` per-function records (see `v2_3_0_rc6.jsonl`).
The aggregate JSON does not aggregate annotation counts — `noreturn_truncations`
in `hir` stays 0 because `noreturn_detect_emit_boundaries` splits the CFG at
every noreturn call site, so the trailing-stmt condition at `hir_emit.c:619`
is unreachable on linker-produced binaries (memory
`project_noreturn_truncation_counter.md`). The unchanged `0` is therefore the
expected post-flip signal at the aggregate level — bit-identical to the
pre-flip 0 by architectural construction, not by behavioral coincidence.

### D-3 (indirect resolver default-on, main `9e0e811`)

`cfg.indirect_call_skipped` jumps 0 → 56, and `cfg.indirect_jmp_skipped` jumps
0 → 204. rc4's zeros were the smoking gun in `rc4_remeasure_summary.md` ("the
counter wire site is outside the measurement path"). The audit chain on main
(`a6ff6dc fix(cfg_metrics): route register-indirect counter into
decompile-metrics`, `069ec06`/`de051fd` RED tests) routed the counters into
the `--decompile-metrics` driver path before D-3 flipped on-by-default. The
22% function rate quoted in D-3's commit message is now visible at the smoke
level.

### Stable counters

`sa.aborts == 0` confirms the Cooper watchdog still doesn't fire on the smoke
corpus post-flip — D-1's cap raise did not introduce structural-analysis
abort regressions. `funcs_built / sa.funcs / per_func_count` all bump by +1
together (linked_noreturn fixture entry, planned in Session #13 prep.3).

## What rc6 is good for

- A clean post-flip baseline for any future measurement to diff against.
- A demonstrable record that D-1/D-2/D-3 delivered measurable counter shifts
  on a frozen 89-func corpus, not just on artificial benchmarks.
- A check that no schema version bumped (still `schema_version: 1`, same
  shape as rc1–rc5), so rc1–rc5 baselines remain comparable.

## What rc6 is NOT

- It is not a "regression detector" — the smoke corpus is small. Use it as a
  baseline anchor; long-tail corpus regressions need the full
  cfg_metrics_corpus harness (Phase 2-T).
- It does not measure the `aborts_oversize` counter that the audit chain
  added (`01bbf9f`); that counter belongs to the cap-guard pathway, not the
  smoke-corpus aggregation.
