# ADR-0046 — Phase 11.4.4 (P4.PP2) Field Misidentification: candidate cluster

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Related**: ADR-0033 (LLM additive 원칙), ADR-0040 (InstructionRecord
  — op_str source), ADR-0042 (DecompilePane context menu — popover host),
  ADR-0043 / ADR-0044 / ADR-0045 (display-only path — 본 ADR 의 4번째
  적용), Phase 4B `AURA_OVERRIDE_PAYLOAD_TYPE` (PP1 D3 와 동일 슬롯
  재활용).

## Context

PP4 + PP1 모두 v1 closed (cycle 23~30). PP2 = plan v2 의 RE 도구
차별화 4종 중 3번째: **`s->field_A` 가 잘못된 offset 으로 보여 다른
필드로 오인 → 자동 후보 + 사용자/LLM 선택**.

선결 자산:
- `AuraInstructionRecord.op_str` (Phase 11.3.7) — disasm 결과의 operand
  텍스트 (e.g. `[rdi+0x10]`).
- `AuraVariableRecord` — function 의 stack/reg/arg variable + stack_offset.
- `AuraTypeFactRecord` — engine-reported var → type_str (struct 멤버
  정보 거의 부재).
- `AURA_OVERRIDE_PAYLOAD_TYPE = 1` — PP1 D3 와 동일 슬롯, schema bump 0.
- `aura_llm` — Phase 6 자산 (v2 LLM source 용, GUI-only).

## Decisions

### D1 — Field candidate sources: **(a) op_str regex + (c) stack_offset cluster v1; (b) opportunistic; (d) LLM v2**

  (a) **Instruction op_str regex** `[<reg>+0xNN]` — primary signal.
      PP4 의 string ref 와 정확히 동형: engine 이 emit 한 record 의
      한 필드에서 substring 추출.
  (c) **Variable stack_offset cluster** — 같은 base 변수에 다중
      stack_offset access → struct 후보 evidence.
  (b) **TypeFactRecord struct member** — engine 이 type 추론 성공
      시만 emit, 거의 부재 (rizin afvf X) → opportunistic, 있으면
      표시 / 없으면 skip.
  (d) **LLM 추론** — v2 별 cycle, GUI-only, ADR-0033 보존.

**Reason**: v1 (a)+(c) 두 source 만으로 가장 흔한 케이스 ("같은
reg 에 +0x0 / +0x10 / +0x18 access 패턴" / "stack 변수 여러 offset")
80% 충족. PP4 의 (a)+(b) v1 / LLM v2 분리 패턴 답습.

### D2 — R-9 boundary: **op_str regex = lookup OK / offset cluster → struct 정의 합성 = 거부** ← 핵심

`op_str` 은 engine 이 emit 한 *record field* — 그 안의 substring
`[<reg>+offset]` 추출은 ADR-0044 의 `string.content → snake_case`
변환과 같은 *select / normalize* 동작. **그러나** "이 reg 에 등장한
모든 offset 모음 + count + max" 까지가 한계.

**거부**: "offset 0x0+8 = int64? float?" 같은 자료형 추론 = R-9 직격탄
(struct 정의 합성). v1 = "이 reg 에 등장한 (offset, instruction addr,
op mnemonic) tuple 의 ranked list" 만. **struct 정의 합성은 사용자
또는 LLM (v2) 의 일** — AURA 영구 거부.

### D3 — CLI: **`aura field-candidates --func <hex> [--var <var_id>]` (per-function 기본, var filter 옵션)**

PP4 `label-candidates` 와 동형 SRP. JSON `{candidates: [{base_reg,
offsets: [{value, hits, sample_addr, mnemonic}, ...], evidence_var_id?,
source}]}`. var filter 없으면 함수 전체 reg cluster 일괄. 별도
`struct-suggest` 명령 거부 — `field-candidates` 가 base_reg 별로
그룹핑하면 한 명령으로 충족.

### D4 — GUI: **Variable 우클릭 → "Suggest fields..." → tree dialog (PP1 답습)**

DecompilePane + Variables dock 양쪽 — root: 선택 변수 (또는 reg) /
child: 후보 offset (각 row evidence: hit count + sample call site).
PP1 의 QTreeView + checkbox 패턴 일관. 별도 dock 거부 (PP4/PP1 D3
같은 이유 — surface noisy).

### D5 — Apply path: **`AURA_OVERRIDE_PAYLOAD_TYPE` 재활용 + PP1 store wire deferral 그대로 상속**

field 선택 적용 = "이 변수를 struct foo* 로 본다" + "struct foo 의
멤버는 사용자 직접 정의" — PP1 의 var → type override 와 path 100%
동일. PP1 v2 `buildKeyForVariable()` 가 land 하면 PP2 도 *그 위에*
즉시 wire. **struct definition 자체 저장 슬롯은 v3** (별 ADR —
`AURA_OVERRIDE_PAYLOAD_STRUCT_DEF` 신규 enum 필요, 본 plan 스코프 외).

## Cycle plan (4 cycles)

| Cycle | Focus | Files |
|------|------|-------|
| C1 (cycle-31, this) | ADR + display-only 명세 + heuristic source 정의 + R-9 경계 | `docs/adr/0046-pp2-field-candidates.md`, `AUTOMATION_ROADMAP.md` |
| C2 (cycle-32) | `aura field-candidates --func` + heuristic (a) op_str regex + (c) stack_offset cluster + cli_smoke | `src/cli/main.cpp`, optional `src/core/field_candidates.{h,cpp}` (PP1 type_propagation 패턴 답습), cli_smoke |
| C3 (cycle-33) | GUI "Suggest fields..." popover + tree + checkbox + dry-run status | `src/gui/main_window.{h,cpp}`, gui_smoke |
| C4 (cycle-34) | contract TC + R-9 가드 검증 + PP2 close | gui_smoke 강화 + ROADMAP |

(LLM source 통합 = v2 별 cycle, PP4 cycle-26 패턴 답습, GUI-only.)

## R-1 / R-5 / R-9 / R-10 / R-12 가드 (명시)

- **R-1**: engine record (`instructions[]`, `variables[]`,
  `type_facts[]`) 의 *index lookup* + op_str 의 *substring 추출* 만.
  binary 분석 X.
- **R-5**: Apply path = `override_store_put(AURA_OVERRIDE_PAYLOAD_TYPE)`
  (PP1 D3 와 동일 슬롯). v1 dry-run = store touch 0.
- **R-9 (핵심)**: `FieldCandidate` = derived view (display-only path
  **4번째 채택** — hex (ADR-0043) → PP4 (0044) → PP1 (0045) → PP2
  (0046)). `AuraRecordCollection` 추가 X, body schema bump X.
  **op_str regex 매칭은 record field 의 substring 추출 (lookup)**
  로 해석 — 단, **"offset cluster 에서 자료형/struct 정의 합성"
  영구 거부** (R-9 직격탄, 사용자/LLM 영구 위임).
- **R-10**: `RzCore *` / librz 미사용. `aura_records_*_at` accessor만.
- **R-12**: 1급 record schema 변경 0. body version v3 그대로. payload
  enum 기존 슬롯 재활용.

## Display-only path decision tree (4번째 적용 검증)

PP2 가 4번째 적용 — 패턴 안정 평가 위한 decision tree:

1. **데이터 소스 = 기존 record 의 field?** → Yes (op_str / stack_offset
   / type_str)
2. **조작 = select + group + count?** → Yes (regex extract / cluster
   / rank)
3. **합성 산출물 = 새 분석 객체?** → No (offset list 만, struct 정의 X)
4. **Apply = 기존 override slot?** → Yes (TYPE 슬롯 PP1 과 동일)

→ display-only path 4 조건 충족. **boundary risk**: "offset cluster
→ struct definition 자동 합성" 유혹이 가장 큼 (사용자 directive 가
"field 구분" 이라 자연 욕구). **거부 가드 명시**: struct 정의 합성
영구 거부 — 사용자 또는 LLM (v2 GUI-only) 만 가능.

→ **PP3 (배열) 도 동일 decision tree 적용 가능** — pattern stable.

## Alternatives considered (요약)

- D1 v1 = (a)+(b)+(c)+(d): 매트릭스 폭발, 비결정성 가림. 거부.
- D1 v1 = (a) only: stack offset 단서 누락 → 후보 빈약. 거부.
- D2 op_str regex 거부 (engine 이 별도 record emit 해야): rizin
  현재 emit X — 후보 0. v1 거부, v2 시 engine 협상 별도.
- D2 자료형 추론 v1: R-9 직격탄. 영구 거부.
- D3 별도 `struct-suggest` 명령: SRP 위반, 한 명령 안에서 base_reg
  그룹핑 가능. 거부.
- D4 별도 dock: PP4/PP1 D3 동일 사유. v2.
- D5 신규 `AURA_OVERRIDE_PAYLOAD_FIELD` kind: PP1 의 TYPE 슬롯과
  의미 중복. 거부.
- D5 struct definition 자체 저장 (`AURA_OVERRIDE_PAYLOAD_STRUCT_DEF`):
  v3 별 ADR 필요. 본 plan 스코프 외.
