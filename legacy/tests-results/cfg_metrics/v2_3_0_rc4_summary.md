# v2.3.0-rc4 Baseline Summary (Phase 2-D D-T post-prep measurement)

**HEAD**: a880497 (branch `phase-2d-rc4-measure` from main at merged Session #13
Part 2 prep commits 364ee16 / 69faa2e / 78451aa)
**Date**: 2026-04-22
**Corpus**: 88 funcs (frozen `aura_self_v2_1_0` + `/bin/cat` + `/bin/ls`)
**Host**: aarch64 Linux (dgx-spark)
**Collector**: `tests/tooling/collect_cfg_metrics.sh`
**Purpose**: re-measure the rc3 flag matrix after Session #13 Part 2 prep
landed three fixes aimed at unblocking D-2/D-3 measurability
— (prep.1) hir_builder ET_REL CALL name preservation, (prep.2) register-indirect
counter wiring in `parse_call_target` / `parse_jmp_target`, and (prep.3) the
new `linked_noreturn.x86_64.elf` PT_EXEC fixture.

## rc3 → rc4 counter diff (aarch64 88-func corpus, all 6 variants)

| counter                  | rc3 base | rc4 base | Δ  | indirect_on Δ | dwarf_nr_on Δ | sym_nr_on Δ | cap_4096 Δ | eh_flow_on Δ |
|--------------------------|---------:|---------:|---:|--------------:|--------------:|------------:|-----------:|-------------:|
| per_func_count           |       88 |       88 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.cap_hits_512         |       82 |       82 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.indirect_call_skipped|        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.indirect_jmp_skipped |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.funcs_built          |       88 |       88 |  0 |             0 |             0 |           0 |          0 |            0 |
| sa.funcs                 |       88 |       88 |  0 |             0 |             0 |           0 |          0 |            0 |
| sa.aborts                |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.gotos_emitted        |       20 |       20 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.funcs_with_goto      |       20 |       20 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.noreturn_truncations |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |

**Aggregate verdict**: rc3 vs rc4 aggregates are **bit-identical** across base
and all 5 flag-on variants (each variant's JSON aggregate block matches rc3's
bit-for-bit, confirmed via `diff`).  Session #13 prep.1/prep.2/prep.3 did not
shift any counter on the aarch64 88-func corpus — as expected, since these
preps target x86 ET_REL paths and a new x86 PT_EXEC fixture that the aarch64
corpus does not exercise.

## rc3 → rc4 counter diff (x86 8-fixture ET_REL corpus, all 6 variants)

| counter                  | rc3 base | rc4 base | Δ  | indirect_on Δ | dwarf_nr_on Δ | sym_nr_on Δ | cap_4096 Δ | eh_flow_on Δ |
|--------------------------|---------:|---------:|---:|--------------:|--------------:|------------:|-----------:|-------------:|
| per_func_count           |        8 |        8 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.cap_hits_512         |        1 |        1 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.indirect_call_skipped|        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.indirect_jmp_skipped |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| cfg.funcs_built          |        8 |        8 |  0 |             0 |             0 |           0 |          0 |            0 |
| sa.funcs                 |        8 |        8 |  0 |             0 |             0 |           0 |          0 |            0 |
| sa.aborts                |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.gotos_emitted        |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.funcs_with_goto      |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |
| hir.noreturn_truncations |        0 |        0 |  0 |             0 |             0 |           0 |          0 |            0 |

**Aggregate verdict**: rc3 vs rc4 x86 ET_REL aggregates are **also bit-identical**
across all 6 variants.  Session #13 prep.1 (ET_REL CALL name preservation) and
prep.2 (register-indirect counter) did not shift the 8-fixture aggregate.  See
"Targeted D-2/D-3 re-measurement" below for per-fixture deep-dive results that
explain why prep effects are not visible in the aggregate.

## Targeted D-2/D-3 re-measurement (single-fixture probes)

The 8-fixture x86 ET_REL corpus and the new PT_EXEC fixture were probed
directly with `--decompile-metrics` per fixture to isolate the prep effects.
Results are captured in `v2_3_0_rc4_linked_noreturn.jsonl` (7 variants × 2
funcs = 14 rows); supplementary single-shot probes of `dwarf_noreturn.x86_64.o`
and `indirect_call.x86_64.o` are shown below.

### D-2 probe — `dwarf_noreturn.x86_64.o` ET_REL (prep.1 target)

| variant               | hir.noreturn_truncations |
|-----------------------|-------------------------:|
| baseline              |                        0 |
| AURA_DWARF_NORETURN=1 |                        0 |
| AURA_NORETURN_FROM_SYM=1 |                     0 |

However, `aura --decompile` on this fixture emits `abort(); /* NORETURN */`
in **both** baseline and D-2 variants — the NORETURN annotation is being
rendered, but the counter is not being bumped.  This means:

- prep.1 is **effective at the HIR layer** — `abort` is resolved from the
  ELF `.rela.text` table so the callee name survives into `HIR_CALL_STMT.func_name`
  (rc3 pre-prep showed `sub_1a()`; rc4 post-prep shows `abort()`).
- Noreturn semantic recognition is **already wired at baseline** via a built-in
  symbol-name table — the `/* NORETURN */` annotation fires without any flag.
- The `hir.noreturn_truncations` counter is **not incrementing** on this
  pathway.  Either the counter is bumped in a code path the fixture doesn't
  reach (e.g. physical truncation of dead bytes after the call), or there is
  an instrumentation gap where the built-in noreturn feed bypasses the counter
  site that DWARF/sym feeds hit.

### D-2 probe — `linked_noreturn.x86_64.elf` PT_EXEC (prep.3 fixture)

14-row probe: 7 variants × {`main`@0x1257, `maybe_stack_canary`@0x11e9}.

| variant                               | hir.noreturn_truncations (main + canary) |
|---------------------------------------|-----------------------------------------:|
| baseline                              |                                     0, 0 |
| AURA_INDIRECT_RESOLVE=1               |                                     0, 0 |
| AURA_DWARF_NORETURN=1                 |                                     0, 0 |
| AURA_NORETURN_FROM_SYM=1              |                                     0, 0 |
| AURA_CFG_DISASM_MAX=4096              |                                     0, 0 |
| AURA_EH_FLOW=1                        |                                     0, 0 |
| AURA_DWARF_NORETURN=1 + AURA_NORETURN_FROM_SYM=1 | 0, 0                         |

**D-2 measurement: FAILED.**  The prep.3 PT_EXEC fixture was designed so that
`main`'s calls to `abort()` / `exit()` followed by dead `return -1` / `return -2`
statements would trigger noreturn truncation with the counter incrementing.
Instead the counter stays 0 across every flag combination.  Same root cause
as the ET_REL probe above: the counter appears to be wired on a narrower
codepath than the actual noreturn truncation logic exercises.

Raw per-fixture data: `v2_3_0_rc4_linked_noreturn.jsonl`.

### D-3 probe — `indirect_call.x86_64.o` ET_REL (prep.2 target)

| variant                      | cfg.indirect_call_skipped | cfg.indirect_jmp_skipped |
|------------------------------|--------------------------:|-------------------------:|
| baseline                     |                         0 |                        0 |
| AURA_INDIRECT_RESOLVE=1      |                         0 |                        0 |

**D-3 measurement: FAILED.**  Session #13 prep.2 claimed to extend the
indirect-call counter bump to register-indirect (`call *%reg`) patterns in
`parse_call_target` / `parse_jmp_target`, yet neither the baseline nor the
flag-on variant reports a skip on `indirect_call.x86_64.o` (-O0 `fp(x)`
lowers to `call *%rdx` on x86-64).  Possible causes (not diagnosed here,
this is a measurement task):

1. prep.2 site is a different call-target parser than the one walked for
   ET_REL disassembly — the register-indirect bump may be on a codepath
   bypassed by the ET_REL decode driver.
2. The disassembler is recognizing `*%rdx` as a resolvable target and
   emitting a CALL with an address operand rather than classifying it as
   skipped.
3. The schema's `indirect_call_skipped` is scoped to memory-indirect only
   and a separate counter (`indirect_call_register`?) was added by prep.2
   but is not surfaced in the `--decompile-metrics` JSON.

### D-1 probe — `/bin/cat` `FUN_00102cf4` under `AURA_CFG_DISASM_MAX=4096`

| variant                      | /bin/cat 0x2cf4 outcome | per_func_count total |
|------------------------------|------------------------|---------------------:|
| rc4 baseline                 | collected, cap_hits=1, gotos=1 | 88               |
| rc4 AURA_CFG_DISASM_MAX=4096 | **timed out (30s)**, silently skipped by collector | 87 |

Reproduced directly: `AURA_CFG_DISASM_MAX=4096 ./build-rel/aura --decompile-metrics /bin/cat --func 0x2cf4`
runs past 120 s and is killed by `timeout` (SIGTERM). Baseline (cap=512)
completes in ≈1 s.  **D-1 regression unchanged from rc3**: cap raise unmasks
a latent pathological-path bug on this specific /bin/cat function.  Session
#13 preps did not target this symptom and it is still live.

## D-* flip recommendations (rc4-updated)

### D-1 (CFG cap 512 → 4096) — **HOLD** (unchanged from rc3)

rc4 re-confirms the same signal as rc3:
- `cap_hits_512` drops 82 → 67 on the aarch64 corpus when the cap is raised,
  and 1 → 0 on `large_cfg.x86_64.o` — the flag is effective at eliminating
  truncation on functions that exceed 512 BBs.
- `/bin/cat` `FUN_00102cf4` still hangs past 120 s at cap=4096 — latent bug
  unmasked by the cap raise persists post-prep.  This specific function also
  causes a line-count blowup (baseline 10 lines → cap_4096 ERROR) that is
  visible in the rc3 smoke cross-check.

**Verdict**: keep HOLD pending targeted triage of the `/bin/cat` 0x2cf4 hang.
Session #13 Part 2 addressed neither this triage nor the 30-s collector
timeout suggested in the rc3 follow-ups.

### D-2 (DWARF noreturn default-on) — **HOLD, instrumentation gap exposed**

rc3 conclusion was "HOLD, need linked-executable corpus + HIR_CALL_STMT
naming fix".  rc4 confirms prep.1 (ET_REL naming) and prep.3 (PT_EXEC
fixture) were delivered and that `abort()` now renders correctly in the
decompile output with a `/* NORETURN */` annotation.  **However**, the
`hir.noreturn_truncations` counter does not increment on either probe, so
the rc4 measurement cannot quantify the flag's effect.

**Verdict**: HOLD — promote the D-2 flip decision to require a preliminary
counter-instrumentation audit.  Before rc5/flip, diagnose why `*_truncations`
stays 0 when the decompiler is visibly truncating (or annotating) noreturn
call sites.  This is a new finding unique to rc4.

### D-3 (indirect default-on) — **HOLD, prep.2 counter wiring gap**

prep.2 was supposed to extend the `indirect_call_skipped` /
`indirect_jmp_skipped` counters to register-indirect targets.  rc4 shows
neither counter moves on `indirect_call.x86_64.o` (both baseline and
flag-on), despite the fixture emitting `call *%rdx`.  The prep may have
landed on a parse path not hit by the ET_REL metrics driver, or added a
new counter that isn't surfaced in the JSON schema.

**Verdict**: HOLD — add a counter-wiring audit to the D-3 flip gate.  Either
confirm the prep.2 site is on the decode path exercised by
`--decompile-metrics`, or surface the new counter in the JSON schema.

## Regression protection

- `ctest --test-dir build-rel -j$(nproc)` → **181/181 PASS** (same as main).
- Collector invocation and fixture availability unchanged vs rc3.
- Aggregates bit-identical to rc3, so rc4 is a measurement-only update.

## Follow-ups (for Phase 2-D downstream)

1. **[D-2 gate]** Audit `hir.noreturn_truncations` counter wiring —
   decompile output clearly shows `/* NORETURN */` annotations and
   presumably truncation, but the counter stays 0.  Track which code
   site bumps it and whether DWARF/sym feeds actually reach it.
2. **[D-3 gate]** Audit prep.2 register-indirect counter site —
   `parse_call_target` / `parse_jmp_target` edit in commit 69faa2e vs
   the ET_REL decode driver's call-emission path.  Either route the
   bump to the right place or expose a new counter in the metrics JSON.
3. **[D-1 gate]** Triage `/bin/cat` 0x2cf4 cap_4096 hang (still > 120 s
   per rc4 probe).  Bisect which code stage hangs when the BB cap is
   raised; likely a loop in CFG reconstruction or type inference.
4. **[collector]** Raise the 30-s per-func timeout in
   `tests/tooling/collect_cfg_metrics.sh` to 120 s so cap_4096 ERRORs
   are distinguishable from slow-but-correct runs.  Still defers D-1
   triage but stops silently losing data.
