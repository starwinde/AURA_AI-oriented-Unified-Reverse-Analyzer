# /bin/cat FUN_00102cf4 cap=4096 hang triage

**Task**: Phase 2-D D-audit.3 (diagnosis only — no code edits).
**Scope**: explain why `AURA_CFG_DISASM_MAX=4096 aura --decompile-metrics
/bin/cat --func 0x2cf4` hangs past 180 s while the default cap=512 run
completes in well under 1 s, and recommend an unblock path for D-1
(default-cap flip).
**Author**: `cat-hang-triage` teammate, 2026-04-24.

---

## 1. Symptom — reproduction

### Command

```
AURA_CFG_DISASM_MAX=4096 timeout 180 \
  build-rel/aura --decompile-metrics /bin/cat --func 0x2cf4
```

### Output (last lines, stderr+stdout interleaved)

```
[INFO ] stage=calling_conv conv=7 args=0 has_ret=1
[INFO ] stack: func 0x2cf4 frame=0 fp=0 vars=0
[INFO ] stage=param_id func=0x2cf4 params=0 has_ret=1
[INFO ] stage=calling_conv conv=7 args=0 has_ret=1
[INFO ] stack: func 0x2cf4 frame=0 fp=0 vars=0
[INFO ] stage=cfg func=0x2cf4 blocks=622 edges=1006
[INFO ] stage=dfg blocks=622
                 ↑ last line before 180-s kill; exit=124 (SIGTERM from timeout)
```

No subsequent `alias:`, `loop_detect`, `type_infer`, or final JSON line;
the metrics row for this function is therefore dropped from
`tests/results/cfg_metrics/v2_3_0_rc4_cap_4096.jsonl` (87 rows vs 88-row
baseline — exactly `0x2cf4` missing, `comm -23` confirmed).

### Default-cap (rc4 base) behaviour — same function, same binary

```
[INFO ] stage=cfg func=0x2cf4 blocks=136 edges=232
[INFO ] stage=dfg blocks=136
[INFO ] alias: func 0x2cf4 — 1144 values, 1144 partitions
[INFO ] stage=loop_detect func=0x2cf4 loops=0 back_edges=0
[INFO ] stage=type_infer func=func blocks=3 vals=1144
{"func":"0x2cf4", … "cap_hits_512":1, … }
```

Elapsed `/usr/bin/time -f %e`: **0.00 s** (sub-second). Same function,
same input — only `AURA_CFG_DISASM_MAX` differs.

### Cap-sweep (single-func, 60-s per-run cap)

| AURA_CFG_DISASM_MAX | blocks | edges | wall time | status  |
|--------------------:|-------:|------:|----------:|---------|
| 512 (default)       |    136 |   232 |     0.00 s | OK       |
| 1024                |    262 |   445 |    >60 s  | timeout |
| 2048                |    562 |   903 |    >60 s  | timeout |
| 4096                |    622 |  1006 |   >180 s  | timeout |

Transition threshold is between `cap=512` and `cap=1024` — i.e. between
**136 and 262 blocks**. RSS stays 9-11 MB across all caps, so this is
pure CPU, not an allocation storm (confirmed by `strace -c`: 0.94 ms in
syscalls over 60 s of wall time, 0.07 % syscall ratio).

---

## 2. Environment

| key                 | value                                                   |
|---------------------|---------------------------------------------------------|
| host arch           | aarch64 (ARM64)                                         |
| kernel              | `Linux 6.17.0-1008-nvidia`                              |
| cpu count           | 20 (1-min load avg 1.14 at time of run)                 |
| AURA HEAD           | `ff99d23` (branch `main`, "Phase 2-D D-T")              |
| worktree branch     | `phase-2d-audit-cat-hang` (based on `main`)             |
| `aura` build        | `build-rel/aura` 10.6 MB, `AURA v2.2.1` (self-report)   |
| `/bin/cat`          | 66.3 KB, aarch64 PIE, stripped, BuildID `2f91f735…`     |
| `/bin/cat` .text    | `[0x1b00, 0x51ac)` → 13 484 bytes → 3 371 insns         |

---

## 3. Function profile — what FUN_00102cf4 actually is

Corpus file naming tells us this function is **7 instructions / 28 bytes
wide** in the symbol-stripped /bin/cat layout:

```
test/corpus entry:     FUN_00102cf4_0x102cf4.c   (absolute 0x00102cf4)
next entry in list:    FUN_00102d10_0x102d10.c   (absolute 0x00102d10)
gap:                   0x00102d10 − 0x00102cf4 = 0x1c  → 7 aarch64 insns
```

AURA's FUN absolute addresses use a `+ 0x100000` rebase (see
`tests/tooling/collect_cfg_metrics.sh:163` `addr_abs_to_rel`) — the
`--func 0x2cf4` parameter reaches the same binary offset. Objdump at
that offset in /bin/cat:

```
2cf0:  97fffb04   bl   1900 <abort@plt>     ← previous func's terminator
2cf4:  b00000e0   adrp x0, 1f000            ← FUN_00102cf4 entry
2cf8:  f947ec00   ldr  x0, [x0, #4056]
2cfc:  b4000040   cbz  x0, 2d04             ← conditional into this func's tail
2d00:  …                                    ← (body ≤ 7 insns total)
2d10:                                        ← next function
```

Seven instructions is a short helper; its true CFG should be ≤ 3 blocks.
That cap=512 still builds **136 blocks / 232 edges** (while `cap_hits_512=1`
— the cap was reached) says the CFG builder does **not** stop at the
0x2d10 boundary; it keeps walking fall-through and branch targets past
the function's natural end into adjacent /bin/cat .text regions. With
the cap lifted to 4096, it absorbs ~622 basic blocks covering a large
fraction of the .text section (3 371 insns ÷ ~5.4 insns/block ≈ 624
blocks — matches the observed 622).

### Branch-instruction density of /bin/cat .text

```
conditional/direct branches (b, bl, cbz, cbnz, tbz, tbnz, b.*):  898
indirect branches  (br x_):                                       65
indirect calls     (blr x_):                                       0
```

65 `br x_` register-indirect branches in the section explain why the
CFG builder treats neighbouring functions as reachable from 0x2cf4:
aarch64 `br` used for switch-tables and tail-calls is not a
function-boundary signal.

---

## 4. Backtrace — where the wall time is spent

### Interrupted gdb session

```
AURA_CFG_DISASM_MAX=4096 timeout 70 gdb --batch --nx \
  --ex "set args --decompile-metrics /bin/cat --func 0x2cf4" \
  --ex "handle SIGINT stop print nopass" \
  --ex "run" --ex "bt 50" \
  build-rel/aura
```

After an external `SIGINT` at ~45 s into the hang:

```
Program received signal SIGINT, Interrupt.
0x0000aaaaaacb2890 in ir_build_ssa ()
#0  0x0000aaaaaacb2890 in ir_build_ssa ()
#1  0x0000aaaaaaca0f24 in aura_decompile_func ()
#2  0x0000aaaaaaca1c28 in cli_decompile_metrics ()
#3  0x0000fffff7b784c4 in __libc_start_call_main …
#4  0x0000fffff7b78598 in __libc_start_main_impl …
#5  0x0000aaaaaac9d6b0 in _start ()
```

Multiple re-attaches via external SIGINT all reported the same thread
in `ir_build_ssa`. (ptrace_scope=1 on this host blocks `gcore`/`gdb
attach` to an already-running foreign process, so repeated re-sampling
required re-running `gdb run`; each sample landed in
`ir_build_ssa`.)

### Mapping the hang PC to source

Symbol load base = `main` runtime − `main` file offset =
`0xaaaaaac9c940 − 0x1fc940 = 0xaaaaaaaa0000`.

Hang PC `0xaaaaaacb2890 − 0xaaaaaaaa0000 = 0x212890` → offset **`0x24c`**
into `ir_build_ssa` (symbol at file offset `0x212644`, confirmed via
`nm -n build-rel/aura`).

`objdump -d build-rel/aura` around `0x212890`:

```
  21285c:  nop
  212860:  ldr   w3, [x21, x7]          ; rpo[b1]
  212864:  mov   w1, w3                 ; new b1
  212868:  ubfiz x7, x3, #2, #32
  21286c:  ldr   w0, [x19, x1, lsl #2]  ; idom[b1]
  212870:  cmp   w0, w2
  212874:  b.gt  212860                 ← inner while (rpo[b1] > rpo[b2])
  212878:  cmp   w0, w2
  21287c:  b.ge  212898                 ← break when equalised
  212880:  ldr   w4, [x21, x6]          ; rpo[b2]
  212884:  mov   w5, w4
  212888:  ubfiz x6, x4, #2, #32
  21288c:  ldr   w2, [x19, x5, lsl #2]  ; idom[b2]
  212890:  cmp   w2, w0                 ← HANG PC
  212894:  b.gt  212880                 ← inner while (rpo[b2] > rpo[b1])
  212898:  cmp   w3, w4
  21289c:  b.ne  212848                 ← outer while (b1 != b2)
```

This is a textbook inlined copy of **`dom_intersect`**
(`src/decompiler/codegen.c:1918`):

```c
static uint32_t dom_intersect(const int *rpo, const uint32_t *idom,
                              uint32_t b1, uint32_t b2) {
    while (b1 != b2) {
        while (rpo[b1] > rpo[b2]) b1 = idom[b1];   // ← hang site
        while (rpo[b2] > rpo[b1]) b2 = idom[b2];
    }
    return b1;
}
```

Called from `compute_dominators`
(`src/decompiler/codegen.c:1928-1957`), the Cooper-Harvey-Kennedy
fixed-point of `ir_build_ssa` (`codegen.c:2193`).

---

## 5. Suspected cause — two interacting defects

### (a) CFG builder does not stop at function boundary

`FUN_00102cf4` is ~7 aarch64 insns, but the per-function disasm loop
bounded by `CFG_DISASM_MAX` (`src/core/pipeline.c:93,1095`) keeps
following successors past `0x2d10` because /bin/cat is stripped and
there is no `.rela`/symbol table to declare where the callee "owns"
bytes. At cap=512 it swallows 136 blocks (cap_hits_512=1); at cap=4096
it swallows ~622 (covering most of /bin/cat .text).

This overreach is the **prerequisite** for the SSA hang — the function
CFG handed to `ir_build_ssa` is orders of magnitude larger than the
true function.

### (b) `compute_rpo` produces BFS-forward numbering, not RPO

`src/decompiler/codegen.c:1882-1915`:

```c
/* BFS로 방문 순서 결정 → RPO = BFS 역순 (간단화) */
while (head < tail) {
    uint32_t cur = queue[head++];
    rpo_num[cur] = rpo_cnt++;         // ← assigns FORWARD BFS order
    …
}
```

The comment claims "reverse BFS", but the code assigns numbers in
**forward** BFS visitation order. Cooper-Harvey-Kennedy ("A Simple,
Fast Dominance Algorithm", 2001) is explicitly designed around true
reverse post-order (DFS post-order reversed), where `rpo[idom[b]] <
rpo[b]` holds after a single pass and the outer fixed-point terminates
within two iterations on reducible CFGs.

With BFS-forward numbering that property does **not** hold across
loop back-edges or irreducible regions: the `b.gt` inner whiles of
`dom_intersect` still terminate (idom chain is finite), but the outer
`while (changed)` in `compute_dominators` can take `O(V)` iterations
to stabilise instead of ~2. Combined with the 622-block inflated CFG
from (a), wall time scales closer to cubic than quadratic:

| blocks | est. inner work | observed |
|-------:|----------------:|---------:|
|    136 |   ~  2.5 M ops  | <1 s     |
|    262 |   ~ 18   M ops  | >60 s    |
|    562 |   ~178   M ops  | >60 s    |
|    622 |   ~241   M ops  | >180 s   |

Pure `O(V³)` from 136→622 is ≈96× — the observed jump is at least
200× (< 1 s → > 180 s), consistent with the outer fixed-point also
multiplying iteration count with V.

### What changed rc3 → rc4 at this site

rc3 summary notes the /bin/cat cap=4096 variant took an ERROR-bail
path that shows as a stage-abort counter; rc4 silently drops the row.
`git log --oneline -30` shows no change to `codegen.c` in the Session
#13 prep commits — the three `prep.*` commits (hir_builder ET_REL name
preservation, register-indirect counter wiring, new x86 fixture) touch
x86 lifter/indirect paths, none of which are on the aarch64 SSA path.
So the rc3 ERROR vs rc4 silent-timeout difference is **measurement
artefact, not regression**: rc3's counter row was a function that
aborted early in structural analysis and still emitted JSON; rc4 takes
longer to reach the abort and now crosses the 30-s collector timeout
in `tests/tooling/collect_cfg_metrics.sh:70`, so the row is dropped
outright. In both cases the underlying SSA pathology exists; rc3
happened to short-circuit earlier.

---

## 6. Blast radius

### Current corpus (88 funcs × 6 variants × rc4)

Exactly **1 of 88** functions is affected:
`/bin/cat 0x2cf4` — confirmed by `comm -23` between `v2_3_0_rc4.jsonl`
(baseline, 88 rows) and `v2_3_0_rc4_cap_4096.jsonl` (87 rows) — the
missing row is `0x2cf4`. All 19 /bin/cat, 18 /bin/ls, 50 aura_self_v2_1_0
functions at cap=4096 either complete or emit a row.

### Theoretical risk at D-1 (default-on cap=4096)

Any function whose CFG at cap=4096 has **≥ ~250 blocks** risks the
same hang. Within the current corpus this is nearly zero (only `0x2cf4`
overflows, because only it combines stripped-boundary + dense
indirect-branch section). In a wider corpus (e.g., libjvm.so, stripped
kernel modules, obfuscated binaries), the incidence will be higher
proportional to:
- stripped symbol table (no function boundaries → CFG builder
  overreach),
- `br x_` / `blr x_` density in .text (indirect jumps that the CFG
  builder can't resolve cross jump into neighbour functions),
- call-tables / jump-tables that make many functions reachable
  syntactically from any entry.

Conservative estimate: **< 5 %** of functions in a production-reverse
corpus, but that is enough to wreck batch runs with a long tail of
>180-s hangs.

---

## 7. Options A-D comparison

| Option | Description | Implementation surface | Perf impact (good path) | Robustness | LOC est. |
|--------|-------------|------------------------|-------------------------|------------|---------:|
| **(a) Dynamic cap clamp** — per-func heuristic: when CFG builder sees it has already entered N blocks belonging to a different symbol/section or has crossed a `ret`+pad boundary, clamp that function's local cap to min(cap, 512). | `src/core/pipeline.c` CFG loop + `src/symbolic/cfg.c` edge-add path. Needs a cheap predicate for "this block left the function". | Zero when predicate is off; correct functions benefit from cap=4096. | High if predicate is sound. Two-stage: ship conservative predicate (e.g., "block starts after a pad of `nop` ≥ 4 or within another detected function's range"), measure precision, tighten. | ~60-120 |
| **(b) Timeout bump** — raise collector timeout from 30 s to 600 s. | `tests/tooling/collect_cfg_metrics.sh:70` only. | None — hang still occurs, we just wait for it. | Does not fix the pathology; D-1 (default-on flip) will still hang real users at the CLI, not just in the harness. Pure measurement workaround. | ~1 |
| **(c) FUN isolation** — introduce `AURA_CFG_SKIP_FUNC=0x102cf4,…` env var and have the collector pass it for known pathological addresses. | new env lookup in `pipeline.c`, collector passes list. | Zero (function is skipped). | Needs curating the skip list per corpus; no ungated protection at the CLI. Maintenance burden scales with corpus. | ~40 |
| **(d) Pipeline bail** — if `ir_build_ssa` input has `block_count > CFG_SSA_MAX` (or elapsed > `CFG_SSA_MS`), emit a counter bump (e.g. `sa.aborts_oversize`) and return `AURA_OK` with SSA skipped; downstream HIR/goto emit already tolerates "no SSA" paths. | `src/decompiler/codegen.c:2176` `ir_build_ssa` entry + a new counter in `cfg_metrics.h`. | None on sub-threshold functions. Over-threshold functions lose SSA-dependent analyses (type_infer, copy-prop) but keep basic HIR output + metrics row. | Defensive, unlocks D-1 without paying for (a)'s cleverness. Later, (a) can co-exist and tighten the threshold. | ~40-70 |

---

## 8. Recommendation

**Option (d) — Pipeline bail, immediate.** Ship a hard-capped SSA
input size check in `ir_build_ssa` entry that returns `AURA_OK` with a
`sa.aborts_oversize` counter bump when `func->block_count` exceeds a
threshold around **N=400** (below the 562-block cap=2048 hang but
above any legitimate function seen in the corpus at cap=512, max ~200).

Rationale:

1. **Unblocks D-1 without pretending to fix the root cause.** The
   real defects are (a) CFG overreach and (b) BFS-as-RPO. Both are
   worth fixing, but each is a 1-2-day surgery with its own test
   burden. D-1's goal is "default-on cap=4096 measurable" — option (d)
   delivers that now while preserving honest measurement via the new
   counter.
2. **Pure defensive; no behaviour change on healthy paths.** The
   current 88-func corpus does not hit N=400 except for the one
   offender. The counter makes the incidence visible.
3. **Cheap to implement (~40-70 LOC).** One `if (func->block_count >
   CFG_SSA_MAX) { bump; return AURA_OK; }` plus a counter field and
   JSON plumbing to match `sa.aborts` next to it.
4. **Composable.** When Option (a) or a proper RPO fix lands later, the
   bail threshold can be raised or removed; the counter becomes
   near-zero rather than constantly firing.

Option (b) is useful as a **safety net** alongside (d): bump the
collector timeout from 30 s → 120 s so rc5 measurements never silently
drop rows if a new corpus entry finds a different failure mode.
Option (c) is a distant fallback if (d) turns out to mis-categorise
large legitimate functions. Option (a) is the right long-term fix but
should not gate D-1.

### Optional follow-up (not in scope for D-audit.3)

- Replace the BFS-forward numbering in `compute_rpo` with an actual
  DFS post-order reversal (~20 LOC, measurable single-func
  speed-up).
- Add a CFG-overreach watchdog that counts blocks whose address falls
  outside `[func_start, func_start + FUNC_DISASM_MAX]` and bails the
  function with a counter.

Both are independent of D-1 and should be scheduled after rc4
remeasure.

---

## 9. Estimated effort (follow-up implementation session)

| Task                                                  | Effort (hrs) |
|-------------------------------------------------------|-------------:|
| Option (d) implementation (threshold + counter + JSON) | 1.5         |
| Option (d) RED test + GREEN (one synthetic 500-block fixture) | 1.5         |
| Option (b) collector timeout bump + rc4 remeasure     | 0.5          |
| CHANGELOG + Tasks.md note + commit                    | 0.5          |
| **Total**                                             | **4.0**      |

Does not include the optional RPO rework or overreach watchdog (those
are follow-up Phase 2-E / 2-F candidates, est. 4-6 hrs each).

---

## 10. Appendix — raw logs

- `/tmp/cat_hang_repro.log` — 180-s `timeout` run stdout+stderr.
- `/tmp/cat_default_cap.log` — cap=512 reference run (OK).
- `/tmp/strace_cat.log` — syscall summary during 60-s hang
  (total syscall time 0.94 ms).
- `/tmp/cat_gdb_samples.log` — gdb batch backtrace capture.
- `/tmp/cat_objdump.txt` — full `objdump -d /bin/cat` used for
  function-boundary analysis.

All four files are ephemeral (`/tmp`) and not committed. Reproduction
commands in §1 above are deterministic on the stated host; the
cap-sweep in §1 re-ran inside ~3 minutes.
