# rc4 Remeasure Summary (Phase 2-D D-audit.4)

**Branch**: `phase-2d-remeasure` (from `phase-2d-audit-indirect` @ `a6ff6dc`)
**Date**: 2026-04-24
**Host arch**: aarch64 (dgx-spark)
**Collector**: `tests/tooling/collect_cfg_metrics.sh`
**Purpose**: re-measure the rc4 flag matrix after `D-audit.2` fix (`a6ff6dc`
routes x86 register-indirect `call *%reg` / `jmp *%reg` counters through
`decompile-metrics` JSON output).

## Context

- **D-audit.1 (#1)**: hir.noreturn_truncations counter wire audit — found 4
  truncation sites in `hir_builder.c` bump the counter, but PLT-call path
  skips HIR emit (`term=NULL` bail) so the counter never fires on real
  noreturn callees. Split into RED-marker task `#5` (D-audit.1b) for a
  separate session. **Not fixed in this worktree** → `noreturn_truncations=0`
  expected to persist.
- **D-audit.2 (#2) FIX APPLIED**: `src/decompiler/cfg.c` now routes the
  register-indirect counter bump into the `decompile-metrics` JSON. 9 LoC
  added. Commits `069ec06` (RED test) + `de051fd` (second RED) + `a6ff6dc`
  (GREEN fix).
- **D-audit.3 (#3)**: `/bin/cat` `FUN_00102cf4` cap=4096 hang triage —
  Option (d) pipeline-bail + collector timeout bump filed as task `#6`
  (D-audit.5). **Not fixed** → `cap_4096` variant still silently skips
  this function, per-func count drops 88 → 87.

## rc3 vs rc4 vs rc4_remeasure counter delta (aarch64 88-func corpus)

| counter                     | rc3 base | rc4 base | rc4_remeasure base | Δ (rc4→rc4_rm) | origin                |
|-----------------------------|---------:|---------:|-------------------:|---------------:|-----------------------|
| per_func_count              |       88 |       88 |                 88 |            0   | —                     |
| cfg.cap_hits_512            |       82 |       82 |                 82 |            0   | unchanged             |
| **cfg.indirect_call_skipped** | **0**  |    **0** |              **7** |         **+7** | **#2 fix effect**     |
| **cfg.indirect_jmp_skipped**  | **0**  |    **0** |            **188** |       **+188** | **#2 fix effect**     |
| cfg.funcs_built             |       88 |       88 |                 88 |            0   | unchanged             |
| sa.funcs                    |       88 |       88 |                 88 |            0   | unchanged             |
| sa.aborts                   |        0 |        0 |                  0 |            0   | unchanged             |
| hir.gotos_emitted           |       20 |       20 |                 20 |            0   | unchanged             |
| hir.funcs_with_goto         |       20 |       20 |                 20 |            0   | unchanged             |
| hir.noreturn_truncations    |        0 |        0 |                  0 |            0   | #5 PLT gap unresolved |

### rc4_remeasure flag-variant matrix (smoke corpus)

| variant              | per_func | cap_512 | indirect_call | indirect_jmp | gotos | nrt |
|----------------------|---------:|--------:|--------------:|-------------:|------:|----:|
| baseline             |       88 |      82 |             7 |          188 |    20 |   0 |
| indirect_on          |       88 |      82 |             7 |          188 |    20 |   0 |
| dwarf_noreturn_on    |       88 |      82 |             7 |          188 |    20 |   0 |
| sym_noreturn_on      |       88 |      82 |             7 |          188 |    20 |   0 |
| cap_4096             |       87 |      67 |            40 |          195 |    19 |   0 |
| eh_flow_on           |       88 |      82 |             7 |          188 |    20 |   0 |

### rc4_remeasure flag-variant matrix (x86 8-fixture ET_REL corpus)

| variant              | per_func | cap_512 | indirect_call | indirect_jmp | gotos | nrt |
|----------------------|---------:|--------:|--------------:|-------------:|------:|----:|
| baseline             |        8 |       1 |             1 |            0 |     0 |   0 |
| indirect_on          |        8 |       1 |             1 |            0 |     0 |   0 |
| dwarf_noreturn_on    |        8 |       1 |             1 |            0 |     0 |   0 |
| sym_noreturn_on      |        8 |       1 |             1 |            0 |     0 |   0 |
| cap_4096             |        8 |       0 |             1 |            0 |     0 |   0 |
| eh_flow_on           |        8 |       1 |             1 |            0 |     0 |   0 |

rc4 x86 baseline reported `indirect_call_skipped=0`; rc4_remeasure reports
**1** on the same corpus (source: `indirect_call.x86_64.o` register-indirect
`call *%rdx` now counted). Same direction of effect as aarch64.

## linked_noreturn.x86_64.elf PT_EXEC probe result

14 rows (7 variants × 2 funcs). Identical to rc4: **noreturn_truncations=0**
across every flag combination for both `main@0x1257` and
`maybe_stack_canary@0x11e9`.

| variant                               | 0x1257 nrt | 0x11e9 nrt |
|---------------------------------------|-----------:|-----------:|
| baseline                              |          0 |          0 |
| AURA_INDIRECT_RESOLVE=1               |          0 |          0 |
| AURA_DWARF_NORETURN=1                 |          0 |          0 |
| AURA_NORETURN_FROM_SYM=1              |          0 |          0 |
| AURA_CFG_DISASM_MAX=4096              |          0 |          0 |
| AURA_EH_FLOW=1                        |          0 |          0 |
| AURA_DWARF_NORETURN=1 + AURA_NORETURN_FROM_SYM=1 | 0 | 0      |

Raw: `rc4_remeasure_linked_noreturn.jsonl`.

Root cause remains the **#5 PLT-call HIR emit gap** (D-audit.1b): HIR layer
emits `term=NULL` for PLT calls, so the truncation counter site is never
reached. Fix lives outside this measurement task.

## /bin/cat FUN_00102cf4 cap=4096 note

- `cap_4096` variant collector silently skipped FUN_00102cf4 after the per-func
  30 s timeout elapsed — expected per #3 triage (pathological path hits
  exponential worklist blowup under cap=4096).
- Other 87 functions under `/bin/cat + /bin/ls + aura_self` collected normally.
- `cap_hits_512` drops 82 → 67 (∆−15) as cap raise eliminates truncation on
  large functions.
- **Caveat** (new signal): `indirect_call_skipped` jumps 7 → 40 and
  `indirect_jmp_skipped` jumps 188 → 195 under cap_4096. The additional 33
  call-skipped + 7 jmp-skipped come from the 15 formerly-cap-hit functions
  now disassembling their full bodies, exposing more indirect sites.

## D-1/D-2/D-3 flip decision data (rc4_remeasure)

### D-3 (indirect default-on) — **FLIP-READY, pending cost-benefit**

- rc4_remeasure baseline `indirect_*_skipped = 7 + 188 = 195` sites per 88 funcs
  — roughly **~2.2 skipped sites per function** on average across the 88-func
  smoke corpus. That is well above any reasonable "≥10% of functions touch
  an indirect site" threshold for flipping the resolver to default-on.
- flag-on (`AURA_INDIRECT_RESOLVE=1`) produces identical aggregate — resolver
  is already cold-activating on skipped sites (no further aggregate movement
  expected from the flag flip per se).
- **Recommendation**: proceed to D-3 flip decision. The #2 fix removes the
  "counter is 0 so we have no data" blocker identified in rc4 summary. Next
  step is per-function parity comparison between indirect_on vs. off to
  quantify parity uplift (separate task, not in scope here).

### D-1 (CFG cap 512 → 4096) — **HOLD** (unchanged)

- `cap_hits_512` drops 82 → 67 (∆−15 funcs no longer truncated), confirming
  the cap lift is effective on functions that need it.
- However, `/bin/cat` `FUN_00102cf4` still hangs past 30 s at cap=4096 — the
  pathological-path bug (#3 triage, #6 follow-up) is unresolved.
- **Recommendation**: HOLD pending #6 D-audit.5 (Option d pipeline-bail +
  timeout bump). Flip unsafe until the latent pathology is contained.

### D-2 (DWARF noreturn default-on) — **HOLD** (unchanged)

- `noreturn_truncations=0` across every probe variant (aarch64 smoke +
  x86 ET_REL + linked_noreturn PT_EXEC). The counter does not fire because
  HIR layer silently drops terminators for PLT calls (see #5 D-audit.1b).
- **Recommendation**: HOLD pending #5 fix. D-2 flip decision is gated on
  the counter being able to report effect of the flag — currently the flag
  is wired but invisible to instrumentation.

## Files produced

- `rc4_remeasure.{json,jsonl}` — smoke baseline (88 funcs)
- `rc4_remeasure_indirect_on.{json,jsonl}` — AURA_INDIRECT_RESOLVE=1
- `rc4_remeasure_dwarf_noreturn_on.{json,jsonl}` — AURA_DWARF_NORETURN=1
- `rc4_remeasure_sym_noreturn_on.{json,jsonl}` — AURA_NORETURN_FROM_SYM=1
- `rc4_remeasure_cap_4096.{json,jsonl}` — AURA_CFG_DISASM_MAX=4096 (87 funcs; cat 0x2cf4 skipped)
- `rc4_remeasure_eh_flow_on.{json,jsonl}` — AURA_EH_FLOW=1
- `rc4_remeasure_x86.{json,jsonl}` — x86 ET_REL baseline (8 fixtures)
- `rc4_remeasure_x86_{indirect_on,dwarf_noreturn_on,sym_noreturn_on,cap_4096,eh_flow_on}.{json,jsonl}`
- `rc4_remeasure_linked_noreturn.jsonl` — 7 variants × 2 funcs, linked_noreturn PT_EXEC probe
- `rc4_remeasure_summary.md` — this file

## Regression gates

- `ctest --test-dir build-rel` → **183/183 PASS**
- `tests/decompiler/test_real_binary_smoke.sh` → **90/90 GREEN**

Build: fresh worktree at `a6ff6dc`, cmake Release, aarch64 gcc 13, submodules
initialized (capstone + zydis + zycore).
