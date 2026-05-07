# Benchmark Regression Harness — Design Spec

**Date:** 2026-04-14
**Status:** Draft
**Scope:** v1.1 prerequisite (P0) — automated precision/recall regression detection

---

## 1. Problem

v1.0.1 shipped with G2/G3/G4/G5 function detection phases disabled due to false-positive explosion (71,687 FP on libjvm, precision 39%). Before re-enabling these phases in v1.1, we need an automated harness that detects precision/recall regressions on every code change. Currently, `tests/benchmark/bench_func_detect.sh` computes metrics manually but has no CI integration, no baseline comparison, and no pass/fail gating.

## 2. Goals

- Automatically run function detection benchmarks on 3 fixture binaries
- Compare results against stored baselines with dual-threshold pass/fail logic
- Integrate into CI so regressions block merges
- Reuse existing `bench_func_detect.sh` metric computation

## 3. Non-Goals

- Per-function diff (which functions were gained/lost) — future enhancement
- Cross-architecture matrix (only AArch64 fixtures for now)
- Ghidra comparison in CI (requires Ghidra headless, too heavy)

## 4. Architecture

```
tests/benchmark/
├── bench_func_detect.sh          # Existing — single-binary benchmark
├── regression_harness.sh         # NEW — orchestrator (calls bench_func_detect.sh per fixture)
├── baselines/
│   ├── aura_stripped.json        # { precision, recall, f1, count, time_ms }
│   ├── libjvm_25mb.json          # { precision, recall, f1, count, time_ms }
│   └── libLLVM_15.json           # { count, time_ms } (no GT)
└── fixtures/                     # Git LFS tracked
    ├── aura_stripped              # 4.7 MB AArch64
    ├── aura_unstripped           # GT source (nm + readelf)
    ├── libjvm_stripped.so        # 25 MB
    ├── libjvm_unstripped.so      # GT source
    └── libLLVM-15.so             # 109 MB (no GT)
```

## 5. Regression Judgment Logic

Each binary must pass BOTH checks:

### 5.1 Absolute Floor (hard minimum)

| Binary | F1 | Precision | Recall |
|--------|-----|-----------|--------|
| aura_stripped | ≥ 0.90 | ≥ 0.90 | ≥ 0.90 |
| libjvm_25mb | — | ≥ 0.45 | ≥ 0.99 |
| libLLVM_15 | (no GT) | — | — |

### 5.2 Relative Drop (vs. baseline)

| Metric | Max Allowed Drop |
|--------|-----------------|
| F1, Precision, Recall | -2% of baseline value |
| Detection count (no-GT) | ±10% of baseline |
| Time | ≤ 2× baseline |

### 5.3 Decision Matrix

```
IF absolute_floor_met AND relative_drop_within_limit:
    PASS
ELSE:
    FAIL (print which threshold violated)
```

## 6. Baseline JSON Format

```json
{
  "binary": "aura_stripped",
  "arch": "aarch64",
  "size_mb": 4.7,
  "ground_truth_count": 628,
  "detected_count": 627,
  "precision": 0.9234,
  "recall": 0.9220,
  "f1": 0.9227,
  "time_ms": 115,
  "tolerance_bytes": 16,
  "date": "2026-04-14",
  "aura_commit": "132d8ce"
}
```

For no-GT binaries (libLLVM), `precision`, `recall`, `f1`, `ground_truth_count` are omitted.

## 7. Output Format

```
=== AURA Benchmark Regression Harness ===
Commit: 132d8ce | Date: 2026-04-14

[1/3] aura_stripped (4.7MB AArch64)
  Precision: 0.9234 (baseline 0.9234, Δ+0.00%)  ✓ PASS
  Recall:    0.9220 (baseline 0.9220, Δ+0.00%)  ✓ PASS
  F1:        0.9227 (baseline 0.9227, Δ+0.00%)  ✓ PASS
  Time:      115ms  (baseline 115ms,  ×1.00)     ✓ PASS

[2/3] libjvm_25mb (25MB)
  Precision: 0.5001 (baseline 0.5001, Δ+0.00%)  ✓ PASS
  Recall:    0.9988 (baseline 0.9988, Δ+0.00%)  ✓ PASS
  Time:      2812ms (baseline 2812ms, ×1.00)     ✓ PASS

[3/3] libLLVM-15.so (109MB, no GT)
  Detected:  137636 (baseline 137636, Δ+0.00%)  ✓ PASS
  Time:      8700ms (baseline 8700ms, ×1.00)     ✓ PASS

Result: 3/3 PASS
```

Exit code: 0 on all PASS, 1 on any FAIL.

## 8. CI Integration

### .github/workflows/ci.yml addition

```yaml
  benchmark:
    needs: build-and-test
    runs-on: ubuntu-24.04
    steps:
      - uses: actions/checkout@v4
        with:
          lfs: true
      - name: Build Capstone
        run: # ... (same as build job)
      - name: Build Zydis
        run: # ... (same as build job)
      - name: Build AURA (Release)
        run: |
          cmake -B build -DCMAKE_BUILD_TYPE=Release
          cmake --build build -j$(nproc)
      - name: Run Benchmark Regression
        run: bash tests/benchmark/regression_harness.sh --aura build/aura
```

### Failure behavior
- benchmark job failure does NOT block the existing build/build-and-test jobs
- It DOES appear as a failed check on PRs for visibility
- Can be promoted to required check later when baselines stabilize

## 9. Updating Baselines

When a legitimate improvement is made:

```bash
bash tests/benchmark/regression_harness.sh --aura build/aura --update-baselines
```

This overwrites `baselines/*.json` with current results. The updated baselines should be committed with the improvement.

## 10. Dependencies

- `bench_func_detect.sh` (existing, reused as-is)
- Python 3 (metric computation, already used by bench_func_detect.sh)
- `nm`, `readelf` (GT extraction, standard binutils)
- Git LFS (fixture storage)
- `jq` (JSON baseline comparison — add to CI if not present)

## 11. Codex Review — Incorporated Fixes

The following issues were identified by Codex adversarial review and incorporated:

### 11.1 Comparison Semantics
- All float metrics rounded to 4 decimal places before comparison
- "-2%" means relative percent (e.g., baseline 0.92 → floor 0.9016), not percentage points
- Time check is **WARN only**, not FAIL (CI runner noise)

### 11.2 Fixture Integrity
- `fixtures/PROVENANCE.md` records source URL, license, SHA256 for each binary
- `regression_harness.sh` verifies SHA256 before running; mismatched hash → infra failure (exit 2), not benchmark FAIL (exit 1)

### 11.3 Baseline Update Safety
- `--update-baselines` prints diff of old vs new baselines before overwriting
- Refuses to update if any metric worsened unless `--force` is also passed
- `time_ms` field is excluded from baseline updates (runner noise)

### 11.4 Error Handling
- Missing tool (jq, nm, readelf, python3) → exit 2 (infra failure)
- Single binary crash/timeout → that binary FAIL, others continue
- LFS pointer file detected instead of real binary → exit 2

### 11.5 CI Blocking Policy
- **Phase 1 (now):** Non-blocking (visibility only)
- **Phase 2 (G2-G5 re-enable):** Promote to required check before merging any PR that re-enables a disabled detection phase

### 11.6 Security
- Fixtures are analysis-only; CI scripts must never execute them
- `regression_harness.sh` sets `chmod -x` on all fixtures before running

---

## 12. Implementation Order

1. Git LFS setup + fixture addition + PROVENANCE.md
2. Baseline JSON generation (run bench_func_detect.sh, capture results)
3. regression_harness.sh implementation (with integrity check, dual-threshold, WARN-only time)
4. CI workflow integration (non-blocking phase 1)
5. Codex adversarial review of implementation
