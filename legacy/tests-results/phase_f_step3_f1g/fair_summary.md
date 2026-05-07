# Phase F-1-G Fair Baseline — Option A Re-measurement

**Date**: 2026-04-18
**Session**: Phase F-1 Step 3 (F-1-G denominator filter)
**Filter**: Option A (keep `.init` + `.plt` + `.text` + `.fini`, drop GOT synthetic thunks)
**Binary under test**: `build-rel/aura` (read-only; no rebuild this run)
**Tooling**: `tests/benchmark/gap_analyzer.sh` @ HEAD (commit 22a05d7, Option A)

---

## 3-Binary Fair Baseline

| Binary | raw cov% | fair cov% | Ghidra raw | userland (kept) | filtered (GOT thunks) | covered_avg |
|---|---|---|---|---|---|---|
| /bin/cat      | 15.8% (23/146)       | **27.1% (23/85)**    | 146  | 85   | 61  | 54 |
| /bin/ls       | 45.1% (186/412)      | **61.8% (186/301)**  | 412  | 301  | 111 | 56 |
| aura (self)   | 87.6% (1049/1198)    | **93.0% (1049/1128)** | 1198 | 1128 | 70  | 55 |

**Total filtered across 3 binaries: 242 GOT synthetic thunks (~12% of raw Ghidra output).**

## Delta vs pre-filter (raw) baseline

| Binary | Δ cov% | Interpretation |
|---|---|---|
| cat       | +11.3 pp | Small util: 41.8% of Ghidra entries were GOT thunks. Largest relative lift. |
| ls        | +16.7 pp | Mid-sized util: 26.9% GOT thunks. Largest absolute lift. |
| aura_self | +5.4 pp  | Large self-hosted binary: only 5.8% GOT thunks (smaller ratio). |

The delta *inversely correlates with binary size* — smaller binaries have proportionally more GOT thunks per real function, so they suffered the largest denominator inflation pre-filter.

## covered_avg invariance check (F-1-G touches denominator only)

| Binary | Pre-filter covered_avg (raw) | Post-filter covered_avg (fair) | Δ |
|---|---|---|---|
| cat       | 54 | 54 | 0 |
| ls        | 56 | 56 | 0 |
| aura_self | 55 | 55 | 0 |

✅ **Confirmed**: F-1-G modifies denominator/filtering semantics only; per-function parity scoring is untouched. The covered_avg plateau (~55/100) that F-1 depth levers (C-3 / M / O / T / N) target remains the same measurement target.

## Numerator-denominator gap (F-1-P scope)

Current AURA pipeline clamps decompile emission to `.text` addresses. With Option A the denominator now legitimately includes `.plt` + `.init` + `.fini` — so the uncovered userland is exactly the set of PLT stubs and runtime hooks not yet served by the pipeline:

| Binary | .text-only covered (today) | userland denominator | gap (.plt + .init + .fini) |
|---|---|---|---|
| cat       | 23   | 85   | 62 (60 .plt + 2 init/fini) |
| ls        | 186* | 301  | 115 (~113 .plt + 2 init/fini) |
| aura_self | 1049 | 1128 | 79 (bulk .plt + 2 init/fini) |

*ls shows 186 covered out of only 23 `.text`-like expected for cat-scale — the AURA count already exceeds `.text`-only because AURA discovers some PLT-adjacent symbols via its own function-index (see `ls/aura_functions.txt`). Exact composition needs per-entry audit in F-1-P.

## Prediction — F-1-P (pipeline expansion to .plt/.init/.fini)

If F-1-P successfully extends the AURA decompile pipeline to cover the PLT + init/fini ranges, expected Option A fair cov% would approach:

| Binary | current fair | F-1-P target | gap closed |
|---|---|---|---|
| cat       | 27.1% (23/85)     | ~98% (83/85)     | +62 funcs |
| ls        | 61.8% (186/301)   | ~99% (~298/301)  | +112 funcs |
| aura_self | 93.0% (1049/1128) | ~99% (~1125/1128) | +76 funcs |

**Note**: PLT stubs have near-trivial structure (single branch to GOT slot) — AURA decompile output should be small, near-identical boilerplate. Their per-function `parity_score` will likely be **low** (signature only), so while recall improves, covered_avg may drop 2–5 points after F-1-P unless the pipeline emits human-readable PLT thunks (e.g., `puts@plt → call puts via GOT`). This is a trade-off F-1-P must face explicitly.

## Artifacts

- `cat/parity.json` — 3.9 KB
- `ls/parity.json` — 32 KB
- `aura_self/parity.json` — 127 KB
- `*/ghidra.log` — headless decompile traces
- `*/aura/*.c` — per-function AURA output
- `*/ghidra/*.c` — per-function Ghidra reference output

## Reproduction

```bash
bash tests/benchmark/gap_analyzer.sh \
  --aura build-rel/aura --binary /bin/cat \
  --out tests/results/phase_f_step3_f1g/cat
# … repeat for /bin/ls and build-rel/aura
```

Set `GAP_FILTER_DENOMINATOR=0` to restore pre-F-1-G raw counts (useful for regression comparison).
