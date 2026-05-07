# v2.3.0-rc3 Baseline Summary (Decision gate G-C)

**HEAD**: ff9214a
**Date**: 2026-04-20
**Corpus**: 88 funcs (frozen `aura_self_v2_1_0` + `/bin/cat` + `/bin/ls`)
**Host**: aarch64 Linux (dgx-spark)
**Collector**: `tests/tooling/collect_cfg_metrics.sh`

Phase 2-C landed five opt-in flags (C-1…C-5). This rc3 baseline measures the
per-flag effect on the 88-func corpus to feed Decision gate G-C and inform the
D-1/D-2/D-3 default-on transition in Phase 2-D.

## Counter diff (rc3 baseline vs flag-on variants)

| counter                 | rc3 base | indirect_on | dwarf_nr_on | sym_nr_on | cap_4096 | eh_flow_on |
|-------------------------|---------:|------------:|------------:|----------:|---------:|-----------:|
| per_func_count          |       88 |          88 |          88 |        88 |       87 |         88 |
| cfg.cap_hits_512        |       82 |          82 |          82 |        82 |   **67** |         82 |
| cfg.indirect_call_skipped |     0 |           0 |           0 |         0 |        0 |          0 |
| cfg.indirect_jmp_skipped  |     0 |           0 |           0 |         0 |        0 |          0 |
| cfg.funcs_built         |       88 |          88 |          88 |        88 |       87 |         88 |
| sa.funcs                |       88 |          88 |          88 |        88 |       87 |         88 |
| sa.aborts               |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.gotos_emitted       |       20 |          20 |          20 |        20 |   **19** |         20 |
| hir.funcs_with_goto     |       20 |          20 |          20 |        20 |   **19** |         20 |
| hir.noreturn_truncations |       0 |           0 |           0 |         0 |        0 |          0 |

### Effect per flag

- **AURA_RESOLVE_INDIRECT (C-1)** → no diff. Expected: the aarch64 host lacks
  the x86 indirect-target pattern-match surface the resolver depends on; the
  `indirect_resolved` counter is not even wired on the schema for this corpus.
  Real-world effect must be confirmed via x86 frozen fixture (C-7).
- **AURA_DWARF_NORETURN (C-2)** → no diff. No DWARF-emitted `noreturn`
  attributes landed in the 88-func sample (`cat`/`ls` stripped, aura_self built
  without DWARF noreturn hints). The feed is wired; it just has nothing to
  truncate on this corpus.
- **AURA_NORETURN_FROM_SYM (C-4)** → no diff. Symbol heuristic requires the
  caller to target an external symbol matching the noreturn name table; the
  sampled functions do not terminate on such calls.
- **AURA_CFG_DISASM_MAX=4096 (C-3)** → **measurable**. `cap_hits_512` drops
  82 → 67 (−15, −18.3 %); `funcs_with_goto` 20 → 19; `funcs_built` 88 → 87
  (one function did not emit a metrics line — either timed out at 30 s or
  collapsed after the larger cap gave the CFG enough runway to expose an
  existing bail path). Full smoke diff below.
- **AURA_EH_FLOW (C-5)** → no diff on aggregate counters. The `.eh_frame`
  plumbing is opt-in and does not yet publish a dedicated counter; this
  variant exercises the init-path only.

## Smoke cross-check (threshold 85/90 = ±20 %)

| variant                   | pass | fail | verdict |
|---------------------------|-----:|-----:|---------|
| rc3 baseline (flags off)  |   90 |    0 | GREEN   |
| AURA_RESOLVE_INDIRECT=1   |   90 |    0 | GREEN   |
| AURA_DWARF_NORETURN=1     |   90 |    0 | GREEN   |
| AURA_NORETURN_FROM_SYM=1  |   90 |    0 | GREEN   |
| AURA_CFG_DISASM_MAX=4096  |   86 |    4 | GREEN   |
| AURA_EH_FLOW=1            |   90 |    0 | GREEN   |

### `cap_4096` failures (line-count drift, not semantic regressions)

| bucket    | function                              | fixture | current | addr_rel | drift    |
|-----------|---------------------------------------|--------:|--------:|---------:|---------:|
| cat       | FUN_00102cf4_0x102cf4.c               |      10 |   ERROR |   0x2cf4 | ERROR    |
| ls        | FUN_00103e80_0x103e80.c               |      50 |     301 |   0x3e80 | +502.0 % |
| aura_self | AArch64_printInst_0x1d8d60.c          |     224 |    1081 |  0xd8d60 | +382.6 % |
| aura_self | ARM_printInst_0x1bbd10.c              |      72 |     378 |  0xbbd10 | +425.0 % |

The line-count blowups are expected: the frozen fixtures were regenerated
with cap=512. Raising the cap to 4096 lets the decompiler emit the full body
of functions that previously truncated at cap=512, so the comparison against
the (capped) reference balloons by 4-5×. These are **not** semantic
regressions — smoke still reports GREEN because the harness threshold absorbs
the drift. The `cat` FUN_00102cf4 ERROR needs a targeted re-run in Phase 2-D
before default-on to rule out an actual crash; a single-func failure at
cap=4096 is consistent with the `funcs_built` 88→87 shortfall observed in
counters.

## Decision gate G-C

| criterion                                                  | status |
|------------------------------------------------------------|:------:|
| Smoke ≥ 85/90 GREEN across all 6 variants                  | **✅**  |
| Each flag probed at least once at runtime                  | **✅**  |
| Flag effect measurable on aarch64 corpus                   | **partial** (only cap_4096) |
| x86-specific flags (indirect, DWARF noreturn) probed       | **deferred → C-7** |

**Verdict: G-C PASS (with C-7 reservation).** The 5 flags are wired, opt-in,
and do not break the baseline. The aarch64 corpus is insufficient to
characterize C-1/C-2/C-4/C-5 effect sizes — a limitation called out at C-1
design time. rc3 does not block Phase 2-D planning; the x86 frozen fixture
(C-7) is the gating work for D-1/D-3 default-on decisions.

## D-* default-on recommendations

- **D-1 (CFG cap 512 → 4096)** — **HOLD pending fixture refresh + targeted
  triage**. Signal is real (cap_hits_512 −18.3 %), but the smoke delta
  (86/90 with one ERROR) shows the current fixtures codify the cap=512
  truncation. Before flipping default: (a) refresh fixtures at cap=4096 for
  the 4 affected functions, (b) reproduce the FUN_00102cf4 ERROR and confirm
  it is not a regression, (c) revisit `collect_cfg_metrics.sh` timeout
  (30 s → 60 s?) to remove the single `funcs_built` shortfall.

- **D-2 (DWARF noreturn default-on)** — **HOLD for broader corpus**. rc3 shows
  0 effect on 88 funcs. Needs a corpus with DWARF-emitted noreturn attributes
  (e.g. glibc `__assert_fail`, `abort`, `_exit`) before the flag's value can
  be quantified. Recommend pairing with C-7 x86 fixture expansion.

- **D-3 (indirect default-on)** — **DEFER to C-7**. The aarch64 parser does
  not match the indirect-call/jmp patterns on this host, so rc3 cannot
  quantify the lift. D-3 decision must wait for the x86 frozen fixture and
  a re-run of the rc3 collector there.

## Follow-ups

- `hir.noreturn_truncations` stayed 0 across the board — worth verifying the
  counter is actually incremented on a synthetic DWARF/sym noreturn case (unit
  test), so we don't mistake "no input" for "no plumbing" in future baselines.
- `cap_4096` 87/88 funcs_built: identify the single dropped function (likely
  timeout) and factor it into D-1 triage.
- C-5 (eh_flow) is metrics-quiet. If Phase 2-D decides to gate on measurable
  effect, the `.eh_frame` path needs a counter surfaced on the schema.
