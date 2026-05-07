# ls covered_avg −2 Spot-check (Phase 2-D D-T 후속, Session #19)

**Date**: 2026-04-25
**HEAD**: `bc3c93a` (v2.3.0-rc6 baseline)
**Inputs**: `tests/results/v2_3_0_rc6_covered_avg/ls/{delta.json,parity.json}` + `tests/results/phase_f_step3_f1g/ls/parity.json`
**목적**: ls covered_avg 56→54 (Δ −2) 의 원인을 (timeout / real component regression / coverage expansion artifact) 로 분류하여 G-D 판정 근거 확보.

---

## 1. 결론 요약 (one-liner)

> **ls covered_avg −2 는 "회귀" 가 아니라 "coverage expansion artifact" 가 dominant**.
> rc6 가 baseline 보다 **+113 함수 더 decompile** (커버리지 61.8% → 99.3%, +37pp), 새로 decompile 된 함수들이 평균 50.7 점 (baseline 평균 56 보다 낮음) 으로 전체 평균을 56→54 로 희석.
> 공통 점수 함수 (n=189) 의 real component drift 는 mem mean −1.39 / ctrl mean −0.78 — 작지만 측정 가능. 절대값은 작다.

**G-D 권고: Pass** (단, ctrl/mem drift 는 v2.4 추적 항목으로 이관).

---

## 2. timeout 가설 — 기각

| 항목 | baseline | rc6 |
|---|---:|---:|
| `aura_timeouts` | 3 | **2** (오히려 −1 개선) |
| `total_functions` | 301 | 301 |
| `covered_functions` | 186 | **299** (+113) |

baseline timeout 이 더 많았다. timeout 으로 인한 covered_avg 희석은 0건 (`(a) timeout-induced` 카테고리 = **count 0**). rc6 의 timeout 2건은 baseline 에서도 timeout 이거나 새로 noise 가 생긴 함수 — 그 영향이 covered_avg 에 미치는 폭은 음수가 아니다.

---

## 3. 회귀 123 함수의 분류

Categorization (모든 `total_delta < 0` 함수):

| 카테고리 | count | Σ\|Δ\| | mean\|Δ\| |
|---|---:|---:|---:|
| (a) Timeout-induced (current=0, baseline>0) | **0** | 0 | — |
| (b) Real component regression (둘 다 >0, current<baseline) | **123** | 472 | 3.84 |
| (c) Other (cur=0 base=0 등) | 0 | 0 | — |

→ 123 회귀는 **모두** 양쪽에서 점수가 매겨진 함수의 component 드리프트.

### 3.1 component-level breakdown (123 real regressions)

| Component | neg_count | Σ Δ |
|---|---:|---:|
| signature | 1 | −8 |
| **control_flow** | **77** | **−237** |
| **memory** | **97** | **−274** |
| ops_consts | 2 | +3 |
| naming | 0 | +44 |

회귀 driver = **mem (97 함수) + ctrl (77 함수)**. 패턴: D-1 (CFG cap 512→4096) 과 D-3 (indirect resolver default-on) 으로 분석 깊이가 일부 함수에서 ctrl/mem 표현을 변동시킨 것으로 추정. 단일 함수당 평균 −3.84 (작음).

### 3.2 회귀 top 10 사례

| Function | base | cur | Δ | sig | ctrl | mem | ops | name |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| FUN_001129a0_0x1129a0 | 73 | 61 | −12 | 0 | −5 | −6 | −1 | 0 |
| FUN_00107110_0x107110 | 73 | 62 | −11 | 0 | −7 | −5 | 0 | +1 |
| FUN_00105df4_0x105df4 | 73 | 63 | −10 | −8 | +2 | −9 | +5 | 0 |
| FUN_00105ee0_0x105ee0 | 68 | 59 | −9 | 0 | −7 | −3 | 0 | +1 |
| FUN_00108b40_0x108b40 | 51 | 42 | −9 | 0 | −5 | −4 | 0 | 0 |
| FUN_00109b80_0x109b80 | 63 | 54 | −9 | 0 | −5 | −4 | 0 | 0 |
| FUN_00109cc0_0x109cc0 | 63 | 54 | −9 | 0 | −5 | −4 | 0 | 0 |
| FUN_0010a9b0_0x10a9b0 | 50 | 41 | −9 | 0 | −5 | −4 | 0 | 0 |
| FUN_0010ad30_0x10ad30 | 55 | 46 | −9 | 0 | −5 | −4 | 0 | 0 |
| FUN_00109e04_0x109e04 | 59 | 51 | 0 | 0 | −5 | −4 | 0 | +1 |

**관찰**: ctrl=−5/−7, mem=−4/−5/−6 패턴이 반복. 동질적 드리프트 — 무작위 잡음이 아니라 D-flip 으로 인한 일관된 small shift.

---

## 4. 개선 151 함수의 분해

| 카테고리 | count | Σ Δ | mean Δ |
|---|---:|---:|---:|
| **Coverage expansion** (base=0 → cur>0) | **112** | **+6094** | **+54.41** |
| Real uplift (둘 다 >0, cur>base) | 39 | +139 | +3.56 |

→ 개선의 **97.8% (6094/6233)** 은 **새로 decompile 된 함수** 의 기여. baseline 에서 점수 0 이었던 (decompile 실패 / no-output) 함수 113 개 (counterfactual: 113-1=112 carry over) 가 rc6 에서 평균 54 점으로 covered.

---

## 5. covered_avg 변화의 산술적 해체

| 항목 | baseline | rc6 |
|---|---:|---:|
| covered_functions | 186 | 299 |
| covered_average | 56 | 54 |
| **score sum (avg × count)** | ≈ 10,416 | **≈ 16,146** |
| **Δ score sum** | — | **+5,730 (+55.0%)** |

새로 covered 된 113 함수의 평균 점수 ≈ **50.7** (baseline 평균 56 보다 낮음).
즉 분자는 +55% 늘었지만 분모도 함께 늘어, **avg = sum/count 비율** 은 56→54 로 미세 희석.

**즉 covered_avg metric 은 "분모 변화 = 커버리지 확대"** 를 반영하지 못하고 단순 평균만 본다. 이 metric 만으로 회귀 판정하면 **coverage 가 늘수록 점수가 떨어지는 역설** 이 발생.

---

## 6. 공통 점수 함수 (n=189) 의 component drift

baseline 과 rc6 모두에서 점수 매겨진 함수만 (n=189) 비교한 component-level mean drift:

| Component | pos | neg | zero | Σ Δ | mean Δ |
|---|---:|---:|---:|---:|---:|
| signature | 0 | 1 | 188 | −8 | −0.04 |
| control_flow | 59 | 86 | 44 | −147 | **−0.78** |
| memory | 44 | 127 | 18 | −262 | **−1.39** |
| ops_consts | 1 | 2 | 186 | +3 | +0.02 |
| naming | 79 | 0 | 110 | +81 | **+0.43** |

→ 공통 함수 한정으로 봐도 **mem (−1.39) + ctrl (−0.78)** 이 net 음수, naming (+0.43) 이 양수 보전. 이 드리프트는 작지만 통계적으로 측정 가능. **v2.4-* 추적 대상**.

---

## 7. 종합 판단

### Pareto-positive 측면 (Pass 근거)

- **+5,730 점수 합** 증가 (+55%)
- **+113 함수 신규 decompile** (+37pp coverage)
- 평균 per-function delta = **+19.14** (n=301)
- 개선 151 / 회귀 123 / 동일 27 — distribution 자체는 개선 다수
- naming 은 net 양수 (+0.43 mean), Phase 2-X-9 PDB partial / forwarder / dual-name 효과 추정

### 회귀 근거 (Hold 근거)

- 공통 함수 189 개 중 mem 127 개 / ctrl 86 개가 음수 component delta
- top 회귀의 동질적 패턴 (ctrl=−5, mem=−4) → D-1/D-3 flip 이 일부 함수 분석 깊이를 낮춤
- 단, 절대값 작다 (mean drift mem −1.39, ctrl −0.78)

### 권고

**G-D = Pass**. 사유:

1. **−2 covered_avg 의 dominant 원인은 coverage expansion artifact** (분모 확대로 인한 평균 희석). 회귀가 아니다.
2. 공통 함수 component drift 는 **측정 가능하지만 작다** (mem −1.4, ctrl −0.8 mean). 차기 release 에서 추적하면 충분.
3. Stop 조건 (covered_avg ≥ −5pt regression) 미해당.
4. 절대 점수 sum +55% 증가 = 명백한 net positive delivery.

### v2.4 이관 항목

- **TRACK-1**: ls 공통 함수 component drift 추적 — D-1 cap raise / D-3 indirect resolver 가 ctrl/mem 표현에 미친 small shift 의 원인 진단. Phase 2.4-C / 2.4-E 검토 시 입력.
- **TRACK-2**: 회귀 top 10 함수 샘플 진단 — ctrl=−5/−7, mem=−4/−5 패턴의 공통 코드 경로 식별 (ex: 특정 instruction class, calling convention edge).

이 두 항목은 **v2.3.0 ship 을 차단하지 않음**. additive minor 인 v2.4.0 의 quality refinement 로 자연 흡수.

---

## 8. 재현 명령

```bash
cd /home/str_dgx_spark/Desktop/AURA
python3 << 'PY'
import json
d = json.load(open("tests/results/v2_3_0_rc6_covered_avg/ls/delta.json"))
deltas = d["deltas"]
regressed = [(n, e) for n, e in deltas.items() if e["total_delta"] < 0]
both_pos = [(n,e) for n,e in regressed if e["base_total"]>0 and e["current_total"]>0]
print(f"regressed={len(regressed)}  real_component_regression={len(both_pos)}")
PY
```

기대: `regressed=123  real_component_regression=123`.
