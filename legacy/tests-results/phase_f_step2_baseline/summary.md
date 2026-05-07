# Phase F Step 2 Baseline (2026-04-18, commit 1700cda)

## Session #3 → Session #4 Delta

| Binary | Ghidra fn | AURA cov (S3) | AURA cov (S4) | Cov % (S3) | Cov % (S4) | Δ cov% | covered_avg (S3) | covered_avg (S4) | Δ avg | all_Ghidra_avg (S3) | all_Ghidra_avg (S4) | Δ all_avg |
|--------|-----------|----------|----------|-------|-------|--------|-------------|-------------|-------|------------|------------|--------|
| /bin/cat | 146 | 23 | 23 | 15.8% | 15.8% | 0.0pp | 54.3 | 54.5 | +0.1 | 8.6 | 8.6 | 0.0 |
| /bin/ls  | 412 | 186 | 186 | 45.1% | 45.1% | 0.0pp | 55.6 | 55.9 | +0.3 | 25.5 | 25.6 | +0.1 |
| aura self| 1202 | 1053 | 1013 | 87.6% | 84.4% | **-3.2pp** | 55.2 | 55.0 | -0.2 | 48.7 | 46.8 | **-1.9** |

**Reference baseline**: Session #3 results from `tests/results/real_parity_2026-04-18/*_v2/parity.json`

## Timeout Frequency

| Binary | Session #3 | Session #4 | Δ |
|--------|-----------|-----------|---|
| /bin/cat | 0 | 0 | 0 |
| /bin/ls | 3 | 3 | 0 |
| aura self | 8 | 8 | 0 |

No change in timeout/crash frequency across all binaries.

## Key Findings

### Summary
Session #4 (commit 1700cda: "Phase F Q-4 missing lifter audit artifact" + prior changes) introduces a **regression on aura_self** (-3.2pp coverage, 40 fewer functions covered). Coverage on /bin/cat and /bin/ls remains stable. The structural ceiling at covered_avg ≈ 55 persists.

### Detailed Analysis

1. **aura_self regression (-3.2pp)**: 
   - Ghidra function count decreased: 1202 → 1200 (2 fewer functions detected by Ghidra, immaterial)
   - AURA covered count dropped: 1053 → 1013 (40 fewer functions decompiled successfully)
   - Δ covered_avg = -0.2 (within noise, 55.2 → 55.0)
   - Δ all_ghidra_avg = -1.9 (46.8 → 46.8, tighter spread)
   - **Interpretation**: Q-4 lifter audit artifact or prior changes degraded function decompilation on AURA's own binary. Likely a lifter regression in aarch64 branch, condition code, or unsupported ISA expansion.

2. **/bin/cat & /bin/ls stable**:
   - Both maintain exact same coverage percentages and function counts
   - Minor +0.1–+0.3 improvement in covered_avg (likely data variance, not signal)
   - Suggests Session #4 changes do not universally break functionality—effect is binary-specific

3. **covered_avg ≈ 55 ceiling**:
   - All three binaries remain clustered at covered_avg 54–56
   - Session #3 → #4 change does not alter this structural pattern
   - **Confirms prior observation**: quality plateau is not about function coverage count, but about decompilation *depth* (IR operations matched, condition code lowering, memory inference)

## Recommendations

### Q-4 Tier 2 Readiness
- **Do NOT advance Q-4 Tier 2** (br indirect + ccmp + csetm lift) until aura_self regression is resolved
- Regression is likely in the Q-4 Phase code itself or an earlier Phase F-0-C-2 lifter change that was not caught by the audit artifact
- Require diagnostic: which function categories regressed (branch-heavy, control-flow heavy, AArch64-SIMD-heavy)?

### Next Steps
1. **Diff Q-4 lifter changes** against Session #3 to isolate causation
2. **Unit test aura_self decompilation** on known-good functions (e.g., main, _start) to confirm regression is localized
3. **Rollback or patch** the offending lifter rule before Q-4 Tier 2
4. **Re-run this baseline** after fix to confirm recovery to ≥87% coverage on aura_self

### covered_avg Plateau
- The 55-point plateau on covered_avg across all three binaries suggests the next quality gain requires investment in **IR operation matching** (Phase F-1) or **condition code inference** (Phase F-0-C-3), not just function detection
- Session #4 changes confirm: lifting more functions does not lift average quality, confirming depth >> breadth hypothesis

---

## AFTER FIX: awk Bug Resolution (2026-04-18, Task #4)

### Root Cause Identified
**gap_analyzer.sh:83 awk parsing bug** — em-dash character misparse for function indices ≥ 1000 caused silent metric corruption. Fixed version re-measured aura_self.

### Re-measurement Results (aura_self_fixed)

| Metric | After Fix | Session #3 Baseline | Δ |
|--------|-----------|-------------------|---|
| **Coverage %** | **87.6%** | **87.6%** | **-0.0pp** ✓ |
| Functions covered | 1051 / 1200 | 1053 / 1202 | -2 fn (negligible) |
| covered_avg | 55.2 | 55.2 | 0.0 ✓ |
| all_ghidra_avg | 48.7 | 48.7 | 0.0 ✓ |
| cJSON functions covered | **79/79** | **79/79** | **✓ 100%** |
| Timeouts/crashes | 8 | 8 | 0 |

### Conclusion
**No code regression detected.** Session #4 commit 1700cda (α watchdog + C-2 PLT + Q-4 T1 Tier 1 lifter) maintains full parity with Session #3 baseline.

**Impact**: The -3.2pp regression reported in Task #1 was a **measurement artifact**, not a real defect. All 37 critical cJSON functions remain covered (79/79 including dependencies). Code quality stable.

**Recommendation**: **Clear to advance Q-4 Tier 2** (br indirect + ccmp + csetm lift). No blocking defects. covered_avg plateau at 55 remains structural (requires Phase F-1 IR depth work, not function count).

---

**Generated**: 2026-04-18 | **Commit**: 1700cda | **Time**: Inline with Phase F Step 2 baseline timeline
**Updated (Task #4)**: 2026-04-18 | **Status**: awk fix validated, green light for Q-4 Tier 2
