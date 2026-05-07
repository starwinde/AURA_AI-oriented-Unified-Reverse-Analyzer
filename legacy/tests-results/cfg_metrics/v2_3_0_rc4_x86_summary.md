# v2.3.0-rc4 x86 Corpus Summary (Phase 2-D D-T post-prep measurement)

**HEAD**: a880497 (branch `phase-2d-rc4-measure` from main at merged Session #13
Part 2 prep commits 364ee16 / 69faa2e / 78451aa)
**Date**: 2026-04-22
**Host**: aarch64 Linux (dgx-spark)
**Toolchain**: `x86_64-linux-gnu-gcc` (same as rc3, cross via `build-rel`)
**Corpus**: 8 fixtures, cross-compiled to `.x86_64.o` under
`build-rel/tests/decompiler/corpus/cfg_metrics/`, **plus** the new
`linked_noreturn.x86_64.elf` PT_EXEC fixture (Session #13 prep.3).
**Collector**: `tests/tooling/collect_cfg_metrics.sh --corpus x86`
(linked_noreturn probed out-of-band — see below).

## Aggregate counter table (8 fixtures × 6 variants)

| counter                  | rc4 base | indirect_on | dwarf_nr_on | sym_nr_on | cap_4096 | eh_flow_on |
|--------------------------|---------:|------------:|------------:|----------:|---------:|-----------:|
| per_func_count           |        8 |           8 |           8 |         8 |        8 |          8 |
| cfg.cap_hits_512         |        1 |           1 |           1 |         1 |    **0** |          1 |
| cfg.indirect_call_skipped|        0 |           0 |           0 |         0 |        0 |          0 |
| cfg.indirect_jmp_skipped |        0 |           0 |           0 |         0 |        0 |          0 |
| cfg.funcs_built          |        8 |           8 |           8 |         8 |        8 |          8 |
| sa.funcs                 |        8 |           8 |           8 |         8 |        8 |          8 |
| sa.aborts                |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.gotos_emitted        |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.funcs_with_goto      |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.noreturn_truncations |        0 |           0 |           0 |         0 |        0 |          0 |

**rc3 → rc4 delta on this aggregate**: bit-identical.  Every counter in every
variant is unchanged from rc3.  Confirmed via `diff` of
`"cfg"` / `"sa"` / `"hir"` blocks between `v2_3_0_rc3_x86*.json` and
`v2_3_0_rc4_x86*.json` — zero differences.

## Why aggregates did not move despite three prep changes landing

Session #13 Part 2 shipped:

- **prep.1** `hir_builder` ET_REL CALL relocation name preservation (expected
  to flip `dwarf_noreturn.x86_64.o` under D-2/D-3 from 0 → 1 truncation).
- **prep.2** `recursive_disasm.c` register-indirect counter bump (expected to
  flip `indirect_call.x86_64.o` from 0 → 1 `indirect_call_skipped`).
- **prep.3** new `linked_noreturn.x86_64.elf` PT_EXEC fixture (expected to
  enable D-2 measurement on a linked executable where callee names and
  DWARF noreturn both resolve).

Direct per-fixture probes (below) show the **runtime behaviour** confirms
prep.1 landed (callee name `abort()` now appears in decompile output
instead of `sub_1a()`), but the **metrics counters** are not moving on any
fixture.  Two separate instrumentation gaps appear to be present:

1. `hir.noreturn_truncations` is not incrementing even when the decompiler
   visibly annotates a call as `/* NORETURN */` and presumably truncates
   the dead body below it (observed on both ET_REL and PT_EXEC fixtures,
   both baseline and flag-on).
2. `cfg.indirect_call_skipped` is not moving on `indirect_call.x86_64.o`
   (register-indirect) even with `AURA_INDIRECT_RESOLVE=1`, implying
   prep.2's bump site is on a path the ET_REL decode driver does not
   visit, or a new counter was added that the schema does not surface.

## Per-fixture probe — `dwarf_noreturn.x86_64.o` (D-2 target)

Direct invocation:

```
./build-rel/aura --decompile-metrics \
    build-rel/tests/decompiler/corpus/cfg_metrics/dwarf_noreturn.x86_64.o --func 0x0
```

| variant                  | noreturn_truncations | funcs_built |
|--------------------------|---------------------:|------------:|
| baseline                 |                    0 |           1 |
| AURA_DWARF_NORETURN=1    |                    0 |           1 |
| AURA_NORETURN_FROM_SYM=1 |                    0 |           1 |

`aura --decompile` on the same fixture emits:

```c
abort(); /* NORETURN */
```

in both baseline and flag-on runs.  So the callee name is resolved (prep.1
effective), noreturn semantic is recognised (built-in `abort` sym table
fires without a flag), but the **counter does not tick**.

**D-2 measurement status on ET_REL**: **partial** — semantic wiring works,
counter wiring does not.

## Per-fixture probe — `linked_noreturn.x86_64.elf` (D-2 target, prep.3 fixture)

Out-of-band collection (linked_noreturn is not in the `--corpus x86` iter
list, which iterates only the 8 `.o` fixtures). Data recorded in
`v2_3_0_rc4_linked_noreturn.jsonl` — 7 variants × 2 funcs = 14 rows.

Probed functions: `main`@0x1257 (calls `abort()`, `exit(42)`, both followed
by dead `return` statements) and `maybe_stack_canary`@0x11e9.

| variant                         | noreturn_truncations on main / canary |
|---------------------------------|--------------------------------------:|
| baseline                        |                                  0, 0 |
| AURA_INDIRECT_RESOLVE=1         |                                  0, 0 |
| AURA_DWARF_NORETURN=1           |                                  0, 0 |
| AURA_NORETURN_FROM_SYM=1        |                                  0, 0 |
| AURA_CFG_DISASM_MAX=4096        |                                  0, 0 |
| AURA_EH_FLOW=1                  |                                  0, 0 |
| D-2 + D-3 combined              |                                  0, 0 |

**D-2 measurement status on PT_EXEC**: **FAILED**.  prep.3 fixture is linked,
has a real symbol table and PLT stubs for `abort` / `exit`, has two dead
returns that should be truncated under D-2, and has `-O0 -g` DWARF — every
prerequisite from the rc3 x86 summary follow-up #3 is met, yet the
truncation counter stays 0.

The raw per-function JSON lines are preserved in
`v2_3_0_rc4_linked_noreturn.jsonl` for downstream triage.

## Per-fixture probe — `indirect_call.x86_64.o` (D-3 target, prep.2 code)

Direct invocation:

```
./build-rel/aura --decompile-metrics \
    build-rel/tests/decompiler/corpus/cfg_metrics/indirect_call.x86_64.o --func 0x0
```

| variant                   | indirect_call_skipped | indirect_jmp_skipped |
|---------------------------|----------------------:|---------------------:|
| baseline                  |                     0 |                    0 |
| AURA_INDIRECT_RESOLVE=1   |                     0 |                    0 |

**D-3 measurement status**: **FAILED**.  Session #13 prep.2 (commit 69faa2e
"feat(recursive_disasm): count register-indirect call/jmp") is present in
the branch, but the `--decompile-metrics` output on the register-indirect
fixture still reports 0 skips.  Either the bump site is not walked for the
ET_REL decode path, or the new counter is scoped to a different metrics
emission channel than the JSON line.

## rc4 D-* re-adjudication vs rc3

| flag                   | rc3 verdict | rc4 verdict | change                                    |
|------------------------|-------------|-------------|-------------------------------------------|
| D-1 (cap 512 → 4096)   | HOLD        | HOLD        | same — /bin/cat 0x2cf4 hang still live    |
| D-2 (DWARF noreturn)   | HOLD        | HOLD        | new: counter wiring gap identified        |
| D-3 (indirect default) | HOLD        | HOLD        | new: prep.2 counter not observed on path  |

All three flags remain **HOLD for rc5/flip** — rc4 data does **not** promote
any flag to PROCEED.  The value of rc4 is diagnostic: it confirms prep.1
delivered the ET_REL naming at the HIR layer, but surfaces two new
instrumentation gaps that Phase 2-D downstream work must close before
counter-based flip gating is meaningful.

## Regression protection

- `ctest --test-dir build-rel -j$(nproc)` → **181/181 PASS** (collected
  immediately after the rc4 build; identical to main).
- 8-fixture x86 ET_REL collection unchanged from rc3 (no skips, no ERROR).
- linked_noreturn probes all completed in <5 s per variant (no timeouts).
- No source tree modifications — measurement-only task.

## Follow-ups (for Phase 2-D downstream)

1. **[D-2 gate / counter audit]** Trace `hir.noreturn_truncations` bump site.
   Verify it triggers on the built-in-sym-noreturn path (which already
   annotates `/* NORETURN */` at baseline) and on the DWARF-fed and
   external-sym-fed paths.  Add a unit test that increments the counter
   deterministically so future baselines don't mistake "no hits" for
   "instrumentation broken".
2. **[D-3 gate / prep.2 audit]** Verify commit 69faa2e's bump site is on
   the ET_REL `--decompile-metrics` driver path.  If not, either relocate
   the bump or surface a dedicated `indirect_call_register_skipped`
   counter on the schema.
3. **[D-1 gate]** Triage `/bin/cat` `FUN_00102cf4` hang at cap=4096 — the
   same blocker the rc3 summary flagged, untouched by Session #13 preps.
4. **[collector UX]** Either (a) raise the per-func timeout in the
   collector from 30 s to 120 s so cap_4096 ERRORs are captured rather
   than silently dropped, or (b) emit a `"skipped"` sentinel line so the
   aggregate counts reflect ERROR vs COLLECTED explicitly.
