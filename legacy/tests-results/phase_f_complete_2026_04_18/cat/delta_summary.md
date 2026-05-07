# Parity Delta vs Baseline

**Baseline**: `/home/str_dgx_spark/Desktop/AURA/tests/results/real_parity_2026-04-18/cat_v2/parity.json`
**Current**:  `/home/str_dgx_spark/Desktop/AURA/tests/results/phase_f_complete_2026_04_18/cat/parity.json`
**Binary**:   `cat`

- Common functions (both runs):     **85**
- Scored in both (non-empty):       **85**
- New in current (added):           0
- Removed since baseline:           61

## Per-component delta summary (scored_common)

| Component        | mean Δ | pos | neg | zero |
|------------------|-------:|----:|----:|-----:|
| signature        | +10.165 | 36 | 0 | 49 |
| control_flow     | +17.541 | 65 | 16 | 4 |
| memory           | +8.871 | 65 | 13 | 7 |
| ops_consts       | +0.047 | 1 | 1 | 83 |
| naming           | +5.106 | 70 | 0 | 15 |
| **total**        | +41.729 | 65 | 20 | 0 |

## Top 10 movers (by |total Δ|)

| Function | base | curr | total Δ | sig Δ | ctrl Δ | mem Δ | ops Δ | name Δ |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| `__cxa_atexit_0x101790` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__cxa_finalize_0x101780` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__fpending_0x1017b0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__fprintf_chk_0x101960` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__fpurge_0x101860` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__freading_0x101a40` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__gmon_start___0x1018d0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__libc_start_main_0x101760` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__memmove_chk_0x101a90` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__memset_chk_0x1018f0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
