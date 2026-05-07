# Function Detection Benchmark Report

> Generated: 2026-04-06 01:17 UTC
> Binary: `aura_stripped` (4738 KB)
> Ground truth: 621 functions (nm + readelf from unstripped binary)
> Address tolerance: 16 bytes

## Results

| Tool | Detected | TP | FP | FN | Precision | Recall | F1 | Time |
|------|----------|----|----|----|-----------|---------|----|------|
| AURA | 534 | 500 | 34 | 121 | 0.9363 | 0.8052 | 0.8658 | 118ms |
| Ghidra | 749 | 577 | 172 | 44 | 0.7704 | 0.9291 | 0.8423 | 10849ms |

## Target

| Metric | Target | AURA Result | Status |
|--------|--------|-------------|--------|
| Recall | >= 80% | 80.5% | PASS |

## Configuration

- AURA: `/home/str_dgx_spark/Desktop/AURA/build/aura`
- Ghidra: `/opt/ghidra_11.3.1_PUBLIC`
- Stripped: `/tmp/aura_stripped`
- Unstripped: `/home/str_dgx_spark/Desktop/AURA/build/aura`
