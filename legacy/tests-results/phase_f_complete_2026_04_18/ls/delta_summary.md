# Parity Delta vs Baseline

**Baseline**: `/home/str_dgx_spark/Desktop/AURA/tests/results/real_parity_2026-04-18/ls_v2/parity.json`
**Current**:  `/home/str_dgx_spark/Desktop/AURA/tests/results/phase_f_complete_2026_04_18/ls/parity.json`
**Binary**:   `ls`

- Common functions (both runs):     **301**
- Scored in both (non-empty):       **301**
- New in current (added):           0
- Removed since baseline:           111

## Per-component delta summary (scored_common)

| Component        | mean Δ | pos | neg | zero |
|------------------|-------:|----:|----:|-----:|
| signature        | +4.173 | 58 | 2 | 241 |
| control_flow     | +8.877 | 175 | 83 | 43 |
| memory           | +3.492 | 158 | 128 | 15 |
| ops_consts       | +0.076 | 7 | 2 | 292 |
| naming           | +2.960 | 193 | 2 | 106 |
| **total**        | +19.578 | 165 | 110 | 26 |

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
