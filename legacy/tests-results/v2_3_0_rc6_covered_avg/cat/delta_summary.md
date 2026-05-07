# Parity Delta vs Baseline

**Baseline**: `tests/results/phase_f_step3_f1g/cat/parity.json`
**Current**:  `tests/results/v2_3_0_rc6_covered_avg/cat/parity.json`
**Binary**:   `cat`

- Common functions (both runs):     **85**
- Scored in both (non-empty):       **85**
- New in current (added):           0
- Removed since baseline:           0

## Per-component delta summary (scored_common)

| Component        | mean Δ | pos | neg | zero |
|------------------|-------:|----:|----:|-----:|
| signature        | +10.024 | 35 | 0 | 50 |
| control_flow     | +17.482 | 64 | 17 | 4 |
| memory           | +8.976 | 66 | 13 | 6 |
| ops_consts       | -0.012 | 0 | 1 | 84 |
| naming           | +5.094 | 69 | 0 | 16 |
| **total**        | +41.565 | 64 | 21 | 0 |

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
