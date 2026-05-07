# Phase F-1-C-3 + F-1-M Impact Diagnosis (Task #7, 2026-04-18)

**작성**: team-lead (docs-agent 무응답 2.5h 경과로 직접 진단)

## 결론: **H1 (Activation gap) 우세 + 부분 H3 (Offsetting)**

F-1-C-3 + F-1-M 은 소스 레벨에서 완전 구현됐으나 실 바이너리 디컴파일 출력
변화는 **제한적 범위** 에서만 발생. parity_score 가 감지할 만한 구조적
개선이 대다수 함수에 미적용.

## 증거 — baseline vs mid aura output diff

### cat (82 SAME / 3 DIFF, 3.5% 영향)
- 3 DIFF 함수의 변화 내용:
  - struct 번호 shift (struct_709 → struct_714) — 노이즈
  - 변수 naming var_XXX → local_XXX — F-1-M 리네이밍
  - 타입 narrowing int64_t → int32_t — F-1-M 타입 추론
- **구조적 제어 흐름 개선 (F-1-C-3 기대) 는 관찰되지 않음**

### ls (245 SAME / 56 DIFF, 18.6% 영향)
- sample diff: `arg1->field_152 == 3` (baseline) vs `arg1->field_152 == 9` (mid)
- `->field_N` 표기는 **양쪽 모두** 존재 → F-1-M field access 는 이미 베이스라인에서도 나옴 (이전 commit 에서 상당 부분 존재)
- 상수값 변화 (3 → 9) = 분석 변화 (일부는 regression 우려)

### aura_self (비교 불가)
- 바이너리 자체가 S#3 → S#4 사이에 바뀌어 함수 주소 매핑 완전 다름 (200 sample 중 0 매칭)

## 해석

### F-1-C-3 (condition code lowering) 의 실 바이너리 impact
**매우 제한적**. cat 에서 구조적 `if (a OP b)` 인라인 변화가 관찰되지 않음. 가능성:
1. 합성 corpus 의 패턴 (bool_var + if) 이 실 바이너리의 일반적 CFG 와 다름
2. ARM64 lifter 가 이미 cmp+b.cond → direct if 형태로 lower 하고 있어서 F-1-C-3 의 중간 bool_var 제거가 드물게 trigger
3. 대부분 함수가 이미 단순한 branch 구조라 인라인 여지 없음

### F-1-M (memory inference) 의 실 바이너리 impact
**부분 적용**. 변수 naming + 타입 narrowing 은 적용. 하지만:
- `->field_N` 표기는 **베이스라인에서도 이미 존재** — F-1-M 의 주요 contribution 이 새로 발생한 게 아니라 이전부터 되던 것
- F-1-M 의 offset tracking / alias consistency 가 measurable output 에 반영되는 빈도 낮음

## parity_score 미반영 원인 (H3 검증)

변수 이름 `var_756 → local_756` 전환은 네이밍 컴포넌트에 긍정적일 수 있으나:
- `parity_score.py` 의 naming scorer 가 이 prefix 차이를 감지하는지 미확인
- Ghidra 는 `local_X` / `local_XXX` 형식 사용 (cat/ls) — AURA 의 `var_` 가 `local_` 로 변환됐으면 매칭 개선 기대
- 그러나 숫자 suffix 는 여전히 다름 → partial match 만 가능

타입 narrowing `int64_t → int32_t`:
- Ghidra 가 정확한 타입을 갖고 있으면 매칭 개선
- 잘못 narrowing 이면 signature 하락

## 권고

### F-1-O / F-1-T / F-1-N 전망
**비슷한 패턴 예상**. F-1-O (const prop) 도 실 바이너리 함수 대다수에 적용 안 되면
covered_avg 이동 미미할 것. 현재 F-1-C-3/M 과 유사한 결과 가능성 높음.

### Recommended next actions

1. **A: parity_score.py metric 재검토** (H2 보강)
   - naming / memory scorer 가 F-1-M 출력을 제대로 점수화하는지 unit-test
   - Ghidra `local_X` vs AURA `local_X` 매칭 로직 확인
   - metric 버그 수정하면 기존 F-1-C-3+M 이 점수화될 수도

2. **B: Coverage-focused 레버 우선** (activation gap 우회)
   - F-1-P (pipeline .text ∪ .plt) 가 breadth 대폭 상승 (cat 27% → 98%)
   - covered_avg denominator 가 증가해도 numerator 가 더 크게 늘 가능성
   - metric 관점에서 더 visible

3. **C: 세션 자연 마감 + 다음 세션 재설계**
   - F-1 의 원래 premise (quality depth 레버로 covered_avg 70+) 가 실측상 불확실
   - parity_score 재설계 또는 Ghidra-기반 semantic diff metric 도입 검토

### F-1-O 단독 진행 vs 진단 후 진행

**F-1-O 단독 진행은 비권장** — H1 확인 후에는 비슷한 flat 결과 예상.
최소한 A (metric 재검토) 를 먼저 수행 후 F-1-O 착수가 자원 효율적.

## 데이터 아티팩트
- `tests/results/phase_f_step2_baseline/` — pre F-1-C-3+M
- `tests/results/phase_f_mid_measure_2026_04_18/` — post F-1-C-3+M
- `/tmp/aura_diff_sample.txt` 은 생성 안 됨 (team-lead 가 직접 진단)

---

## Appendix — Per-Function Component Delta Analysis (docs-agent follow-up)

**작성**: docs-agent (2026-04-18 late, Task #7 재개 후)
**목적**: team-lead 의 sample-based diff 에 paired per-function component-delta
증거를 보강하여 H1/H2/H3 가설을 정량적으로 확정.

### 방법
Session #4 phase_f_step2_baseline 과 현 mid 의 `parity.json` 을 function-name 키로
조인, 각 함수의 5-component score delta (mid − base) 계산. ls 가 샘플 크기(n=189
common covered) 때문에 가장 신뢰도 높음. cat 은 n=23 으로 보조. aura_self 는
address 재배치로 join 불가 (team-lead 관찰과 동일).

### ls 결과 (n=189 common covered)

| 지표 | 값 |
|---|---|
| Total score Δ == 0 | **180 / 189 (95.2%)** |
| Total score Δ > +5 | 6 / 189 |
| Total score Δ > 0, ≤ +5 | 1 / 189 |
| Total score Δ < 0 | 2 / 189 (1 in −5..−1, 1 below −5) |

**Per-component Δ 분포 (189 함수 중):**

| Component | mean Δ | pos | neg | zero |
|---|---:|---:|---:|---:|
| signature     | +0.37  | 7 | 2 | 180 |
| **control_flow** | **0.00** | **0** | **0** | **189** |
| **memory**       | **0.00** | **0** | **0** | **189** |
| ops_consts    |  0.00  | 0 | 0 | 189 |
| naming        | −0.005 | 1 | 2 | 186 |

### 핵심 발견 — Smoking Gun

- **control_flow 컴포넌트 delta = 0 이 189/189 전체** — F-1-C-3 이 직접
  targeting 한 컴포넌트에 **단 한 함수도** 점수 변화 없음.
- **memory 컴포넌트 delta = 0 이 189/189 전체** — F-1-M 이 직접 targeting 한
  컴포넌트에 **단 한 함수도** 점수 변화 없음.
- 그러나 team-lead 의 sample diff 에서 **54 / 189 ls 파일은 text 수준에서 확실히
  변경됨** (cosmetic 2 제외).
- → 코드는 바뀌었지만 score 가 0 delta. → **scorer 가 그 변경을 측정 못 함.**

### H3 기각 근거

H3 (offsetting regression) 가 맞다면 함수별로 한 컴포넌트 +α, 다른 컴포넌트 −α
의 교차 분포가 보여야 함. 실제는 **정확히 0** 이 대부분. 위의 ±7 signature
변화도 특정 함수에서만 발생하고 다른 컴포넌트의 상쇄 움직임이 동반되지 않음.
→ H3 는 현 데이터로 기각.

### H2 확정 근거 — parity_score.py 코드 검토

`tests/benchmark/parity_score.py` 의 `score_control_flow` (line 149-161):
```python
weights = {"if":4, "while":3, "for":3, "switch":3, "return":4, ...}
for kw, w in weights.items():
    total += w * (1 - abs(g_count - a_count) / max(g_count, a_count, 1))
```
→ **키워드 빈도 proximity** 만 측정. F-1-C-3 이 만든 `if (x == 0) { ... }`
인라인은 이미 pre-C-3 output 이 `if` 를 emit 하고 있었다면 키워드 카운트
불변 → score 불변.

`score_memory` (line 162-172):
```python
weights = {"deref":8, "addr_of":6, "index":6}
# count *expr, &expr, [idx] occurrences
```
→ **deref/addr/index 토큰 카운트** 만 측정. F-1-M 의 `int64_t → void*`
변환은 **타입 선언 변경** 일 뿐, 새로운 `*expr`/`&`/`[...]` 를 생산하지 않음.
→ score 불변.

이로써 H2 는 코드 레벨에서도 확정. control_flow 와 memory 의 scoring 함수가
각각 F-1-C-3 / F-1-M 이 개선하는 **의미론적 변화를 측정할 수 있는 메트릭이
아님** (둘 다 토큰 카운트 기반).

### 재수정된 결론

| Hypothesis | 상태 (docs-agent 근거) |
|---|---|
| H1 — Activation gap | **일부 사실**: cat 87% / ls 70% 가 byte-identical → F-1-C-3+M 이 다수 함수에 미적용. 그러나 ls 의 30% 에서는 변경 발생. |
| H2 — Scoring miss | **주원인 확정**: 189 ls 함수 전원에 대해 control_flow+memory delta 0. text 는 변했지만 scorer 가 못 봄. parity_score.py 의 토큰 카운트 scoring 이 F-1-C-3/M 의 의미론적 개선을 표현하지 못함. |
| H3 — Offsetting regression | **기각**: 정확히 0 인 분포는 ±α 상쇄로 설명 불가. |

### team-lead 권고와의 일치점

Team-lead option A ("parity_score.py metric 재검토") 가 정답. 단, "H2 보강"
으로 표현된 것보다 **H2 가 주원인** 임을 데이터가 명시적으로 지지. 구체
fix:

1. **score_memory**: type-precision sub-score 추가 (8 deref + 6 type-precision + 6 index 로 재분배). 파라미터/로컬 타입 비교를 점수화.
2. **score_control_flow**: 키워드 카운트 외에 **branch density** (branch statements / total statements) 또는 **nesting depth** 를 sub-metric 으로 추가. F-1-C-3 의 cset-cmp-b.cond → 단일 if 붕괴는 branch density 감소로 관찰 가능.
3. **diff mode**: `gap_analyzer.sh --baseline <prev_parity.json>` 추가 → 레버 측정이 absolute plateau 와 무관하게 self-interpreting.

### F-1-O 권고 (team-lead option B 와 비교)

Team-lead option B (F-1-P breadth 우선) 와 docs-agent 권고 (P0 scorer 수정 먼저)
는 모두 타당. 결정 기준:

- **P0 scorer 먼저**: F-1-O 를 올바르게 측정하기 위해. 4-6 시간.
- **F-1-P 먼저**: breadth 확장은 `covered_functions` 숫자 자체를 키우므로
  scorer 한계와 무관하게 DoD 일부 (coverage%) 개선. 4-8 시간.

개인 권고: **P0 scorer → F-1-O** 순서. 이유는 F-1-O/T/N 이 다 같은
scoring blind spot 에 부딪힐 것이므로, 이 레버 세 개를 각각 세션 낭비하기
전에 scorer 를 한 번 고치는 게 ROI 최고.
