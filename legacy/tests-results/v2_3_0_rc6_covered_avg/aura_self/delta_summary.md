# Parity Delta vs Baseline

**Baseline**: `tests/results/phase_f_step3_f1g/aura_self/parity.json`
**Current**:  `tests/results/v2_3_0_rc6_covered_avg/aura_self/parity.json`
**Binary**:   `aura_self_v2_1_0`

- Common functions (both runs):     **1**
- Scored in both (non-empty):       **1**
- New in current (added):           1133
- Removed since baseline:           1127

## Per-component delta summary (scored_common)

| Component        | mean Δ | pos | neg | zero |
|------------------|-------:|----:|----:|-----:|
| signature        | -12.000 | 0 | 1 | 0 |
| control_flow     | -5.000 | 0 | 1 | 0 |
| memory           | +11.000 | 1 | 0 | 0 |
| ops_consts       | -1.000 | 0 | 1 | 0 |
| naming           | -1.000 | 0 | 1 | 0 |
| **total**        | -8.000 | 0 | 1 | 0 |

## Top 10 movers (by |total Δ|)

| Function | base | curr | total Δ | sig Δ | ctrl Δ | mem Δ | ops Δ | name Δ |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| `FUN_001b29cc_0x1b29cc` | 41 | 33 | -8 | -12 | -5 | +11 | -1 | -1 |
