# Parity Delta vs Baseline

**Baseline**: `/home/str_dgx_spark/Desktop/AURA/tests/results/phase_f_mid_measure_2026_04_18/ls/parity.json`
**Current**:  `/home/str_dgx_spark/Desktop/AURA/tests/results/phase_f_post_p_2026_04_18/ls/parity.json`
**Binary**:   `ls`

- Common functions (both runs):     **301**
- Scored in both (non-empty):       **301**
- New in current (added):           0
- Removed since baseline:           0

## Per-component delta summary (scored_common)

| Component        | mean Δ | pos | neg | zero |
|------------------|-------:|----:|----:|-----:|
| signature        | +3.900 | 50 | 0 | 251 |
| control_flow     | +8.767 | 169 | 89 | 43 |
| memory           | +3.478 | 154 | 127 | 20 |
| ops_consts       | +0.000 | 0 | 0 | 301 |
| naming           | +2.691 | 112 | 0 | 189 |
| **total**        | +18.837 | 147 | 128 | 26 |

## Top 10 movers (by |total Δ|)

| Function | base | curr | total Δ | sig Δ | ctrl Δ | mem Δ | ops Δ | name Δ |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| `__cxa_atexit_0x103900` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__cxa_finalize_0x1038d0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__fpending_0x103950` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__fprintf_chk_0x103c00` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__freading_0x103d90` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__gmon_start___0x103b50` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__isoc23_strtoumax_0x103b90` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__libc_start_main_0x103860` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__mbstowcs_chk_0x103da0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
| `__memcpy_chk_0x1039a0` | 0 | 78 | +78 | +30 | +25 | +18 | +0 | +5 |
