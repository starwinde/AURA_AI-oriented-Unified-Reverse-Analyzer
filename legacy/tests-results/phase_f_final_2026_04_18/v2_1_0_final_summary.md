# v2.1.0 Final 3-Binary Measurement (Phase F cumulative, HEAD=f54d54d)

## Session #3 (v2.0.0) → v2.1.0 Final Delta

| Binary | S3 Ghidra | S3 cov% | S3 covered_avg | v2.1.0 cov% | v2.1.0 covered_avg | Δ cov% | Δ avg |
|--------|-----------|---------|----------------|-------------|-------------------|--------|-------|
| /bin/cat | 146 | 15.8% | 54.3 | 15.8% | 54.5 | +0.0pp | +0.1 |
| /bin/ls | 412 | 45.1% | 55.6 | 45.1% | 56.2 | +0.0pp | +0.7 |
| aura_self | 1202 | 87.6% | 55.2 | 87.6% | 55.3 | -0.0pp | +0.1 |

## DoD Assessment (v2.1.0 Release Criteria)

### Primary DoD: covered_avg 55 → 70+

| Binary | v2.1.0 avg | Target | Gap | Status |
|--------|-----------|--------|-----|--------|
| /bin/cat | 54.5 | 70+ | -15.5 | ✗ MISSED |
| /bin/ls | 56.2 | 70+ | -13.8 | ✗ MISSED |
| aura_self | 55.3 | 70+ | -14.7 | ✗ MISSED |

**Verdict**: **INCOMPLETE** — All three binaries remain below 70-point threshold. Phase F work achieved stability but not depth breakthrough.

### Secondary DoD: cat/ls coverage improvement

- **/bin/cat**: 15.8% → 15.8% (Δ +0.0pp) ✗ No improvement
- **/bin/ls**: 45.1% → 45.1% (Δ +0.0pp) ✗ No improvement

Coverage percentages stable (no regression), but function detection plateau remains.

### Tertiary DoD: IR_OP_UNSUPPORTED frequency reduction

Not quantified in gap_analyzer output. Requires audit artifact analysis (see Phase F-0-Q-4 audit for baseline).

## Root Cause Analysis

### Why covered_avg Plateau Persists

1. **Phase F focus**: Q-4 T1/T2 (branch lifting) + α watchdog + C-2 PLT wiring + Q-1/Q-2/Q-3 (ISA expansion)
   - Improved function *detection breadth* (87.6% aura_self coverage, 45.1% ls coverage)
   - Did NOT improve *decompilation depth* (IR operation matching, condition code inference)

2. **Structural constraint**: All three binaries clustered at 54–56 avg, indicating:
   - Quality ceiling is **per-function IR complexity**, not function count
   - Each binary has ~55-point average baseline (IR ops matched, basic control flow)
   - Remaining 14-15 points require: conditional branches, memory operations, AArch64-specific ops

3. **Evidence**:
   - Timeouts unchanged (cat: 0, ls: 3, self: 8)
   - all_ghidra_avg also plateaued (cat: 8.6, ls: 25.8, self: 48.8)
   - Zero improvement in covered_avg despite 10 cumulative Phase F commits

## Path Forward

### To achieve covered_avg 70+ (v2.2.0)

**Option A: IR operation matching (Phase F-1)**
- Requires ~5-8 new IR operation types for conditional lowering, memory inference
- Estimated effort: 4-6 weeks
- Expected gain: +8-12 points per binary

**Option B: Condition code lowering (Phase F-0-C-3)**
- Prerequisite: Phase F-0-C-2 PLT wiring (✓ complete)
- Requires: ARM/AArch64 CCR flag semantics, Zydis intrinsic analysis
- Estimated effort: 2-3 weeks
- Expected gain: +5-8 points per binary

**Option C: Accept 55-point plateau (v2.1.0 final)**
- Scope reduction: Redefine v2.1.0 DoD to covered_avg ≥ 55 (✓ achieved)
- Release v2.1.0 as "function detection + basic IR matching baseline"
- Defer depth to Phase F-2/F-3

## Recommendation

**Current assessment**: v2.1.0 DoD (covered_avg > 70) **NOT MET**. 

**Action pending**: Team-lead decision on Phase F continuation scope:
1. Continue Phase F-1 (IR ops) for v2.2.0 target 70+
2. Continue Phase F-0-C-3 (ccond lowering) as faster path to 70+
3. Declare Phase F complete at 55-point plateau, tag v2.1.0 as interim release

---

**Generated**: 2026-04-18 | **Commit**: f54d54d | **Measurer**: Task #9 complete
**Test binaries**: /bin/cat (146 fn), /bin/ls (412 fn), aura_self (1201 fn)
**Measurement results**: `tests/results/phase_f_final_2026_04_18/{cat,ls,aura_self}/parity.json`
