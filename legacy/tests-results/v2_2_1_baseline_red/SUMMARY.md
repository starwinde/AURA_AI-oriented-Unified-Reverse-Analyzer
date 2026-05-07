# v2.2.1 Baseline — RED Capture (P1.1)

**Date**: 2026-04-19
**Binary under test**: `build-rel/aura` @ `60a399b` (reports `AURA v2.2.0`)
**Test**: `tests/decompiler/test_real_binary_smoke.sh` (90 functions, ±20% line-count tolerance, ≥85 PASS threshold)
**Purpose**: Capture the pre-revert regression baseline so Phase 1 reverts (H-4 → H-1 → H-2) have a measurable GREEN target.

## Result: **RED** (exit code 1)

| Metric | Value |
|---|---|
| Total functions tested | 90 |
| PASS | **49** (cat 18/20, ls 18/20, aura_self 13/50) |
| FAIL | **41** (cat 2/20, ls 2/20, aura_self 37/50) |
| Threshold | 85 of 90 must be within ±20% of v2.1.0 fixture line count |
| Margin | **FAIL by 36 functions** (49 ≪ 85) |

`cat` / `ls` ls-pass counts include 2 pre-existing v2.1.0 timeouts (`FUN_00105df4`, `FUN_00105fe0`) that the script recognizes via fixture header (`// TIMEOUT ...`) and classifies as PASS — neither is a v2.2.0 regression.

## Top 3 Worst Regressions (by |delta %|)

| # | Function | Fixture (v2.1.0) | Current (v2.2.0) | Delta | Kind |
|---|---|---:|---:|---:|---|
| 1 | `aura_self/ARM_reg_name_0x1bdae0` | 18 | 58 | **+222.2 %** | over-expansion |
| 2 | `aura_self/AArch64_printInst_0x1d8d60` | 224 | 16 | **−92.9 %** | body collapse |
| 3 | `aura_self/FUN_001b4b2c` (offset 0xb4b2c) | 113 | 12 | **−89.4 %** | body collapse (team-lead's known worst) |

## Full Failing Functions (41)

### cat (2)
| Function | Fixture | Current | Delta |
|---|---:|---:|---:|
| `FUN_00102d10_0x102d10` | 11 | 8 | −27.3 % |
| `FUN_00102d40_0x102d40` | 11 | 8 | −27.3 % |

### ls (2)
| Function | Fixture | Current | Delta |
|---|---:|---:|---:|
| `FUN_00105e10_0x105e10` | 11 | 8 | −27.3 % |
| `FUN_00105e40_0x105e40` | 11 | 8 | −27.3 % |

### aura_self (37)
| Function | Fixture | Current | Delta |
|---|---:|---:|---:|
| `FUN_001b4b2c_0x1b4b2c` | 113 | 12 | −89.4 % |
| `decodeToMCInst_2.isra.0_0x19c4c4` | 29 | 18 | −37.9 % |
| `decodeToMCInst_4.constprop.0.isra.0_0x1be490` | 24 | 18 | −25.0 % |
| `decodeToMCInst_4.isra.0_0x1a5484` | 24 | 11 | −54.2 % |
| `printInstruction_0x1d0080` | 31 | 11 | −64.5 % |
| `AArch64SysReg_genericRegisterString_0x1e7b04` | 45 | 23 | −48.9 % |
| `AArch64_reg_access_0x1dbd44` | 35 | 18 | −48.6 % |
| `AArch64_getFeatureBits_0x1cb714` | 8 | 17 | +112.5 % |
| `AArch64_getInstruction_0x1cb720` | 36 | 12 | −66.7 % |
| `AArch64_get_op_access_0x1dbcf0` | 22 | 17 | −22.7 % |
| `AArch64_init_0x1cbb90` | 28 | 58 | +107.1 % |
| `AArch64_map_vregister_0x1dbbb0` | 12 | 21 | +75.0 % |
| `AArch64_option_0x190bb4` | 14 | 21 | +50.0 % |
| `AArch64_post_printer_0x1db6b4` | 28 | 35 | +25.0 % |
| `AArch64_printInst_0x1d8d60` | 224 | 16 | −92.9 % |
| `ARM_addReg_0x1bda40` | 33 | 15 | −54.5 % |
| `ARM_addSysReg_0x1bdaa0` | 33 | 58 | +75.8 % |
| `ARM_addUserMode_0x1bda80` | 33 | 58 | +75.8 % |
| `ARM_addVectorDataSize_0x1bda20` | 33 | 19 | −42.4 % |
| `ARM_addVectorDataType_0x1bda00` | 33 | 26 | −21.2 % |
| `ARM_blx_to_arm_mode_0x1bddb0` | 11 | 17 | +54.5 % |
| `ARM_getFeatureBits_0x1b0080` | 13 | 31 | +138.5 % |
| `ARM_getRegName_0x1bba40` | 13 | 26 | +100.0 % |
| `ARM_get_detail_op_0x1e7244` | 23 | 17 | −26.1 % |
| `ARM_get_insn_id_0x1bdb30` | 58 | 11 | −81.0 % |
| `ARM_get_op_access_0x1bddc0` | 22 | 7 | −68.2 % |
| `ARM_global_init_0x1909e0` | 21 | 11 | −47.6 % |
| `ARM_init_0x1b0100` | 28 | 16 | −42.9 % |
| `ARM_option_0x190aa0` | 21 | 28 | +33.3 % |
| `ARM_post_printer_0x1bba80` | 27 | 12 | −55.6 % |
| `ARM_printInst_0x1bbd10` | 72 | 35 | −51.4 % |
| `ARM_reg_access_0x1bde04` | 35 | 18 | −48.6 % |
| `ARM_reg_name2_0x1bdb04` | 18 | 14 | −22.2 % |
| `ARM_reg_name_0x1bdae0` | 18 | 58 | +222.2 % |
| `AddThumb1SBit_0x1957c0` | 32 | 11 | −65.6 % |
| `AddThumbPredicate_0x1958a0` | 37 | 18 | −51.4 % |
| `DecodeAddrMode2IdxInstruction.isra.0_0x198900` | 38 | 7 | −81.6 % |

## Observations

- **cat/ls**: 2 regressions each (all `-27.3 %`, fixture 11 → current 8). Team-lead's earlier 15-func sample flagged cat/ls as "100 % safe"; this larger 20-per-binary sample exposes that PLT stubs and small wrapper functions do regress. Root cause to confirm during revert sequence.
- **aura_self**: 37/50 = **74 % regression rate**, matching the 60–70 % rate implied by the Session #6 multi-func sample. Two failure modes co-exist:
  - **Collapse** (body shrinks): dominant pattern — 25+ cases, matches team-lead's "90 % body collapse" description for `FUN_001b4b2c`. Likely H-4 (pointer-width narrowing) and/or H-2 interactions.
  - **Over-expansion** (body grows, often to ≈58 lines): 11 cases. Distinct failure signature, likely H-1 (loop classification re-emission) introducing spurious blocks.
- Failure count (41) is substantially higher than team-lead's ~6 estimate. The 50-func aura_self sample and explicit ±20 % tolerance surface regressions the 10-func sample missed.

## Commitment

This RED state is **intentional** and establishes the regression floor. Phase 1 revert sequence (P1.2 H-4 → P1.3 H-1 → P1.4 H-2) must raise pass count from 49/90 → ≥85/90. P1.6 re-runs this exact script and commits the GREEN baseline.

## Files

- `tests/decompiler/test_real_binary_smoke.sh` — smoke harness (90 funcs, ±20 %, 30 s per-func timeout).
- `tests/results/v2_2_1_baseline_red/smoke_output.txt` — full stdout of the failing run.
