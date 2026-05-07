# Phase F-1 Mid-Measurement — F-1-C-3 + F-1-M Cumulative Effect

**Date**: 2026-04-18
**HEAD**: `1b5c9fd` (F-1-M memory inference, built on `f1699a9` F-1-C-3 cond-code lowering)
**Baselines compared**: Session #3 (commit `b7c9bab`) and Session #4 Phase F final (`5d2cb2a`)
**Tooling**: `tests/benchmark/gap_analyzer.sh` Option A filter
**ctest**: 126/126 ✅ (pre-measurement gate)

---

## TL;DR

**F-1-C-3 + F-1-M landed without moving covered_avg.** All 3 binaries remain at the 54-56 plateau. v2.1.0 DoD (70+) **not reached**; no measurable progress from either lever.

## Summary Table

| Binary | Session #3 avg | Session #4 avg | **Mid (today) avg** | Δ vs S#4 | fair cov% (Option A) |
|--------|---------------:|---------------:|--------------------:|---------:|---------------------:|
| cat        | 54 | 54.5 | **54** | −0.5 | 27.1% (23/85)     |
| ls         | 55 | 56.2 | **56** | −0.2 | 61.8% (186/301)   |
| aura_self  | 55 | 55.3 | **55** | −0.3 | 93.0% (1052/1131) |

> Note: S#4 averages are fractional because they aggregate multiple sub-runs. gap_analyzer.sh returns integer-truncated averages; the apparent small regressions (−0.2 to −0.5) are within the ±1 rounding error band and should be read as **flat**, not a regression.

## 5-Component Breakdown (covered-functions average)

Components are absolute points contributed to the per-function total (sum of components = covered_avg).

| Component (weight) | cat | ls | aura_self | median |
|---|---:|---:|---:|---:|
| signature   (~30) | 22.35 | 23.89 | 22.39 | ~22.9 |
| control_flow (~30) | 15.70 | 16.50 | 15.99 | ~16.1 |
| memory       (~20) | 10.30 |  8.96 | 10.22 | ~10.2 |
| ops_consts   (~10) |  0.52 |  0.77 |  0.71 | ~0.7  |
| naming       (~10) |  5.61 |  6.13 |  5.91 | ~5.9  |
| **total**         | 54.48 | 56.25 | 55.22 | ~55.5 |

## F-1-C-3 expected vs actual (control_flow)

- **Expected**: +10~15 points on control_flow (RED: 6 → 16-21)
- **Observed**: control_flow sits at **15-17** across all 3 binaries
- Absolute position suggests *some* control-flow structure is working, but we have **no pre-F-1-C-3 control_flow baseline with the Option A filter** to attribute the 15-17 to C-3 specifically vs pre-existing scoring
- What we do know: covered_avg total is flat vs S#4 — if control_flow rose, another component must have fallen by the same amount, with no net effect. No such drop is visible in the numbers.

## F-1-M expected vs actual (memory)

- **Expected**: +8~12 points on memory (baseline ~2 → 10-14)
- **Observed**: memory at **9-10** across binaries
- Same caveat as above — 9-10 could represent a real improvement from M, or the pre-M baseline.
- The covered_avg didn't move, so even if M added points to memory, equivalent points must have been lost elsewhere.

## Candidate explanations (to be diagnosed before burning more levers)

1. **Parity score saturation/offset**: F-1-C-3 / F-1-M may have tightened AURA output but in ways the current `parity_score.py` heuristic doesn't reward (e.g., removing dead stores *reduces* surface area but doesn't improve matching score).
2. **Guard miss on real binaries**: C-3 / M may fire on synthetic test fixtures but fail a real-binary pattern guard. 126/126 ctest passes, but those are synthetic corpora.
3. **Offsetting regression**: One component up + another down = zero net. Need per-component diff vs Session #4 to rule out.
4. **Landing vs activation gap**: Code merged, feature-flag / build-order issue prevents it running on the decompile path used by gap_analyzer.sh.

## 70+ DoD Gate

**NOT MET.** All three binaries are ~15 points below the 70 floor. At current velocity (−0.3 per lever), continuing F-1-O / F-1-T / F-1-N without diagnosis risks the same outcome.

## Recommendation

**Pause F-1-O. Diagnose first.**

Concrete next step (20-40 min):
- Pick 3 functions where we have the Ghidra reference and AURA output (e.g., `cat/aura/FUN_00101b00_0x101b00.c` and its Ghidra counterpart).
- Run `parity_score.py` manually on them and inspect which components are losing points and why.
- Diff against a pre-C-3/pre-M artifact (`tests/results/phase_f_step2_baseline/cat/aura/…` vs `tests/results/phase_f_mid_measure_2026_04_18/cat/aura/…`) to observe the actual AURA output delta.
- If the AURA output *hasn't changed* between the two commits → C-3/M didn't run → landing/activation bug.
- If the AURA output *changed* but parity score didn't improve → scoring metric isn't measuring the improvement → need to revise `parity_score.py` or retarget the lever.

Only after this diagnosis does F-1-O become worth spending a session on.

## Artifacts

- `cat/parity.json` `ls/parity.json` `aura_self/parity.json`
- `cat/aura/*.c` `ls/aura/*.c` `aura_self/aura/*.c` (per-function AURA output, diffable against `tests/results/phase_f_step2_baseline/`)
- `cat/ghidra/*.c` etc. (Ghidra reference output)
- `*_run.log` (headless + decompile traces)
