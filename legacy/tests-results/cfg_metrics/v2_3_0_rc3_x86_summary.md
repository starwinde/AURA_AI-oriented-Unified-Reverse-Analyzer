# v2.3.0-rc3 x86 Corpus Summary (Phase 2-C C-7)

**HEAD**: 1315d6b (+ C-7 uncommitted)
**Date**: 2026-04-20
**Host**: aarch64 Linux (dgx-spark)
**Toolchain**: `x86_64-linux-gnu-gcc` 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1)
**Corpus**: 8 fixtures, cross-compiled to `.x86_64.o` under
`build-rel/tests/decompiler/corpus/cfg_metrics/`
**Collector**: `tests/tooling/collect_cfg_metrics.sh --corpus x86`

C-7 lands the measurement infrastructure that rc3 identified as missing:
a cross-compiled x86 fixture corpus exercised on the aarch64 dev host so
D-2 (DWARF noreturn) and D-3 (indirect resolver) default-on decisions
have real data instead of "aarch64 parser can't match" pseudo-results.

## Fixture manifest

| fixture              | flag target(s)                  | expected effect                       |
|----------------------|---------------------------------|---------------------------------------|
| `minimal_func`       | smoke                           | cfg.funcs_built += 1                  |
| `large_cfg`          | D-1 cap                         | cfg.cap_hits_512 ≥ 1 at cap=512       |
| `unreachable_exit`   | B-1 / sa.aborts                 | sa-postdom path annotation            |
| `noreturn_trunc`     | B-3                             | hir.noreturn_truncations via extern   |
| `call_then_return`   | funclet boundary                | clean fall-through                    |
| `indirect_call`      | D-3 register-indirect           | `call *%rdx` path                     |
| `dwarf_noreturn` 🆕  | D-2 DWARF + sym noreturn        | hir.noreturn_truncations via `abort`/`exit` |
| `plain_baseline` 🆕  | regression gate                 | cfg.funcs_built += 1; rest += 0       |

## Aggregate counter table (8 fixtures × 6 variants)

| counter                  | rc3 base | indirect_on | dwarf_nr_on | sym_nr_on | cap_4096 | eh_flow_on |
|--------------------------|---------:|------------:|------------:|----------:|---------:|-----------:|
| per_func_count           |        8 |           8 |           8 |         8 |        8 |          8 |
| cfg.cap_hits_512         |        1 |           1 |           1 |         1 |    **0** |          1 |
| cfg.indirect_call_skipped |       0 |           0 |           0 |         0 |        0 |          0 |
| cfg.indirect_jmp_skipped |        0 |           0 |           0 |         0 |        0 |          0 |
| cfg.funcs_built          |        8 |           8 |           8 |         8 |        8 |          8 |
| sa.funcs                 |        8 |           8 |           8 |         8 |        8 |          8 |
| sa.aborts                |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.gotos_emitted        |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.funcs_with_goto      |        0 |           0 |           0 |         0 |        0 |          0 |
| hir.noreturn_truncations |        0 |           0 |           0 |         0 |        0 |          0 |

## aarch64 vs x86 baseline delta (rc3 base)

| counter                  | aarch64 (rc3) | x86 (C-7) | note                                  |
|--------------------------|--------------:|----------:|---------------------------------------|
| per_func_count           |            88 |         8 | 88-func real corpus vs 8-func fixture |
| cfg.cap_hits_512         |            82 |         1 | large_cfg still trips cap              |
| cfg.funcs_built          |            88 |         8 | 1 func per .o on x86                   |
| hir.gotos_emitted        |            20 |         0 | small fixtures don't generate gotos   |
| sa.funcs                 |            88 |         8 | same ratio as funcs_built              |

The x86 corpus is intentionally small and counter-targeted — cap_4096 is
the one flag where the corpus can show a difference, giving a clean D-1
signal without the 88-func aarch64 smoke ballast.

## D-* re-adjudication (updated with x86 evidence)

### D-1 (CFG cap 512 → 4096) — **HOLD confirmed**

**x86 signal**: cap_hits_512 drops 1 → 0 on `large_cfg.x86_64.o` (−100 %).
On aarch64 corpus rc3 showed 82 → 67 (−18.3 %).  Both corpora agree that
raising the cap eliminates truncation on functions that genuinely exceed
512 BBs.

**Caveat unchanged**: rc3's aarch64 cap_4096 variant still reports
`funcs_built 88 → 87` and one `/bin/cat` function ERROR — evidence that
the cap raise unmasks a real-but-previously-hidden bug path.  The x86
corpus does not exhibit this (8/8 funcs_built across all variants) only
because none of the 8 fixtures hit the latent bug surface.

**Verdict**: keep HOLD.  Phase 2-D triage of the `/bin/cat`
`FUN_00102cf4` ERROR (already planned) is the gating item; the x86
evidence corroborates rather than changes that plan.

### D-2 (DWARF noreturn default-on) — **HOLD; C-7 exposes a pipeline gap**

**x86 signal**: `dwarf_noreturn.x86_64.o` with AURA_DWARF_NORETURN=1
shows **no** hir.noreturn_truncations increment despite:
- `<stdlib.h>` emitting DW_AT_noreturn on `abort` / `exit` subprogram DIEs
  (verified via `x86_64-linux-gnu-objdump --dwarf=info`);
- aura's `call_fixup_feed_dwarf_noreturn()` ingesting the DIEs into
  `call_fixup_dynamic_noreturn` at analysis time;
- aura's HIR_SEQ walker (`hir_emit.c:584-591`) bumping the counter on any
  `HIR_CALL_STMT` whose `func_name` resolves via `call_fixup_lookup`.

Root cause is upstream of C-2: on ET_REL `.o` decompile, aura's HIR
builder does **not** propagate the relocation target name into
`HIR_CALL_STMT.func_name`.  Instead the callee surfaces as
`sub_<offset>` (confirmed by decompiling `dwarf_noreturn.x86_64.o` at
`--func 0x0` under AURA_DWARF_NORETURN=1 — output shows `sub_1a()`
instead of `abort()`).  The noreturn-name lookup therefore misses on
unlinked corpus objects even when DWARF carries the attribute.

**New insight from C-7**: the D-2 flag plumbing is correct end-to-end
for *linked* binaries (where relocations resolve to named symbols that
both DWARF and the HIR layer see), but the current measurement corpus
cannot exercise it because unlinked `.o` files rename calls to
`sub_<offset>`.  This is **not** a regression introduced by C-2 — the
gap predates rc3.

**Verdict**: keep HOLD.  Phase 2-D D-2 default-on decision still needs:
(a) either a linked-executable corpus that exercises the flag, or
(b) a small HIR-builder fix to preserve `CALL` relocation target names
into `HIR_CALL_STMT.func_name` on ET_REL paths.  Recommend (b) as a new
Phase 2-D task (small, surgical in `src/decompiler/hir_builder.c`;
unlocks measurement for both D-2 and D-3).

### D-3 (indirect default-on) — **HOLD; x86 corpus limitation identified**

**x86 signal**: `indirect_call.x86_64.o` at -O0 compiles `fp(x)` to
`call *%rdx` (register-indirect, objdump confirmed).  aura's existing
`parse_call_target()` in `src/core/recursive_disasm.c:177-195` only
bumps `indirect_call_skipped` when the operand string contains `[`
(i.e. memory-indirect like `call [rax+0x10]`).  Register-indirect is
not counted.  Baseline and AURA_RESOLVE_INDIRECT=1 both report 0 for
`indirect_call_skipped` / `indirect_jmp_skipped` on the x86 corpus.

**Practical consequence**: the current fixture cannot quantify D-3 flag
effect because the counter wiring doesn't cover the one indirect
pattern the fixture generates.  Two orthogonal improvements would
unblock D-3 measurement:
1. Extend `parse_call_target()` to bump the skip counter on
   register-indirect calls as well (mnemonic `call` with non-empty
   non-numeric operand).  Small, localized change.
2. Add a fixture variant that compiles to memory-indirect
   (`jmp [rax+.Ltable]` style — e.g., a `switch` on a small enum the
   compiler lowers to a jump table at `-O1 -fno-inline`).  Larger
   scope, likely a Phase 2-D sibling task to the D-2 pipeline fix.

**Verdict**: keep HOLD.  D-3 default-on is blocked by the same
`HIR_CALL_STMT` naming gap identified for D-2 (the resolver itself
needs the name to register with `call_fixup_dynamic`), plus the
indirect-counter wiring gap described above.  Phase 2-D should couple
both fixes.

## Decision gate G-C (unchanged by C-7)

C-7 does not relitigate G-C; it feeds D-1/D-2/D-3 planning.

## Regression protection

- `ctest -j$(nproc)` → **140/140 PASS**
- `tests/decompiler/test_real_binary_smoke.sh` → **90/90 GREEN**
- aarch64 smoke collection via pre-C-7 path:
  `collect_cfg_metrics.sh <prefix>` output matches
  `v2_3_0_rc3.json` bit-exact (aggregate block) except for the new
  `"corpus"` field (always `"smoke"` in default mode, `"x86"` in x86 mode).

## Follow-ups (Phase 2-D candidates)

1. **[critical for D-2/D-3]** `src/decompiler/hir_builder.c`: preserve
   CALL relocation target symbol names on ET_REL paths so
   `HIR_CALL_STMT.func_name` matches `call_fixup_dynamic` entries.
2. **[enables D-3]** `src/core/recursive_disasm.c:parse_call_target` +
   `parse_jmp_target`: bump skip counters on register-indirect
   (`call *%reg`, `call %reg`) in addition to memory-indirect.
3. **[enables better corpora]** Add a linked-executable fixture built
   from a `main()` wrapping `abort()` / `exit()` so the noreturn path
   runs through the full PT_EXEC pipeline.
4. **[D-1 remains]** rc3's `/bin/cat` `FUN_00102cf4` ERROR triage — not
   re-tested in C-7 since the x86 corpus does not cover it.
