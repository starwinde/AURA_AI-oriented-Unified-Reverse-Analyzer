# Phase 2-D D-T — 3-binary covered_avg measurement (rc6)

**Date**: 2026-04-25
**HEAD**: `d025348` (v2.3.0-rc6 corpus baseline)
**Harness**: `tests/benchmark/gap_analyzer.sh`
**Baseline**: `tests/results/phase_f_step3_f1g/{cat,ls,aura_self}/parity.json` (Phase F-1 step 3, Session #5 anchor)
**Ghidra**: `~/tools/ghidra_12.0.4_PUBLIC/`
**Aura binary**: `build-rel/aura` (10.6 MB)

## covered_avg results

| Binary | Baseline (phase_f_step3_f1g) | rc6 | Δ | userland coverage | timeouts/crashes | Stop-cond (≥−5 pt regression) |
|--------|------------------------------:|----:|---:|------------------:|------------------:|:------------------------------:|
| `/bin/cat` | 54 | **56** | **+2** ✅ | 85 / 85 | 0 | clear |
| `/bin/ls`  | 56 | **54** | **−2** ⚠️ | 299 / 301 | 2 | clear (within tolerance) |
| `aura_self_v2_1_0` (frozen) | 55 | **51** | **−4** ⚠️ | 1125 / 1134 | 9 | clear (within tolerance) |

## Per-binary mean total Δ (component sum, baseline-matched functions)

| Binary | n (matched) | mean total Δ | improved / regressed / unchanged |
|--------|------------:|-------------:|:---------------------------------|
| cat | 85 | **+41.57** | 64 / 21 / 0 |
| ls  | 301 | **+19.14** | 151 / 123 / 27 |
| aura_self | 1 | **−8.00** | 0 / 1 / 0 (sparse name match — see note) |

## Notes

- **cat**: 강한 양의 delta. signature +10 / control_flow +17.5 / memory +9 / naming +5 / ops_consts ~0. 64/85 함수 개선, 21 회귀, 0 unchanged. covered_avg integer +2.
- **ls**: 평균 component delta +19 이지만 score-binning 결과 covered_avg 1pt drop (56→54). 151/123/27 분포, AURA timeouts/crashes 2건 (이전 baseline 대비 신규 발생 가능성, parity.json 의 timeout 표식 참조).
- **aura_self**: covered_avg 55→51 = −4. delta_summary 의 n=1 은 baseline 의 함수 이름 매칭이 1건만 일치한 결과 (baseline 생성 시점의 aura 본체는 frozen v2_1_0 과 함수 명칭 분포가 다름). covered_avg 자체 비교는 유효 (전체 1125 함수의 평균 점수). 9 timeouts/crashes 는 frozen v2_1_0 의 size 영향.

## D-T DoD 충족 여부

- ✅ 3 binary 측정 완료 (cat / ls / aura_self)
- ✅ covered_avg delta 기록 (+2 / −2 / −4)
- ✅ 결과 산출물: `parity.json`, `delta.json`, `delta_summary.md` × 3 + 본 summary.md
- ✅ Stop 조건 미해당 (모든 binary 의 delta ≥ −5 pt)

## G-D 판정

**Pass** — 사용자 결정 (Session #19, 2026-04-25). 근거: ls spot-check (`ls_regression_spotcheck.md`) 가 −2 covered_avg 의 dominant 원인을 **coverage expansion artifact** 로 입증.

핵심 산술:
- baseline covered = 186/301 (61.8%) → rc6 covered = 299/301 (99.3%), **+113 함수 신규 decompile**
- 점수 합 ≈10,416 → ≈16,146, **+5,730 (+55%)**
- 신규 covered 함수 평균 ≈ 50.7 < baseline 평균 56 → avg 56→54 희석
- timeout 가설 기각: baseline `aura_timeouts=3` → rc6 `=2` (오히려 −1 개선)
- 공통 점수 함수 n=189 의 mem mean **−1.39** / ctrl mean **−0.78** small drift = 측정 가능하지만 작음

차기 이관 항목 (v2.4):
- **TRACK-1**: 공통 함수 component drift 진단 — D-1 cap raise / D-3 indirect resolver 가 ctrl/mem 표현에 미친 small shift 의 원인
- **TRACK-2**: 회귀 top 10 함수 샘플 디컴파일 비교 — ctrl=−5/−7, mem=−4/−5 동질적 패턴의 공통 코드 경로

aura-acceptance-rule Rule 9 조건 1-4 충족 → **Phase 2-D umbrella `[-]` → `[x]` 승격 완료**. v2.3.0 umbrella `[-]` 유지 = final tag 발행 결정 별개 user input 대기 (Phase 2.5).

## 재현 명령

```bash
cd /home/str_dgx_spark/Desktop/AURA
for tgt in \
  "cat /bin/cat" \
  "ls /bin/ls" \
  "aura_self tests/fixtures/frozen_binaries/aura_self_v2_1_0"; do
  read name path <<< "$tgt"
  bash tests/benchmark/gap_analyzer.sh \
    --aura build-rel/aura \
    --binary "$path" \
    --out "tests/results/v2_3_0_rc6_covered_avg/$name" \
    --baseline "tests/results/phase_f_step3_f1g/$name/parity.json"
done
```
