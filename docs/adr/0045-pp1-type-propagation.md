# ADR-0045 — Phase 11.4.3 (P4.PP1) Type Propagation: candidate cascade

- **Status**: Accepted (planning) — DB apply 개선 승인됨 (2026-05-06)
- **Date**: 2026-05-04
- **Related**: ADR-0037 (Override Editor — TYPE payload kind 이미
  정의), ADR-0040 (InstructionRecord — call site addr 출처),
  ADR-0042 (DecompilePane context menu — popover host), ADR-0043
  (Hex pane display-only path — D5 패턴), ADR-0044 (PP4 — display-only
  candidate 패턴 직선 답습).

## Context

P4.PP4 (cycle 23~25) closed v1. PP1 = plan v2 의 RE 도구 차별화 4종
중 사용자가 가장 강조한 영역 — directive: **수천 변수 수동 타입 수정
노가다 제거 — 타입 전파 후보를 트리로 보여주고 부분 선택**. mmap
인프라 (`include/mapped_file.h`) 존재.

선결 자산:
- `AuraTypeFactRecord` (R-12, Phase 2A) — engine-reported `var → type_str`.
- `AuraVariableRecord` — function 의 stack/reg/arg variable.
  `kind="arg"` 가 매개변수.
- `AuraCallEdgeRecord` — `caller_id → callee_id`, `site_addr`.
- `AuraInstructionRecord.type=="call"` + `jump==callee.entry` — call
  site → callee 매핑.
- `AURA_OVERRIDE_PAYLOAD_TYPE = 1` **이미 정의됨** (`override_store.h:50`).
  사용 사례 0 — 재활용 가능.

## Decisions

### D1 — TypePropagationCandidate = **display-only** (ADR-0044 D5 답습)

`AuraRecordCollection` 추가 0, body schema bump 0. *Derived view* —
기존 record (Variable / TypeFact / CallEdge / Instruction) 위
*call-site parameter matching* lookup.

**Reason (R-9 핵심)**: alias 분석 / pointer-to 추적 / data-flow
가시화 모두 *분석 추론* — R-9 위반. AURA 가 하는 일은 **"caller var
v1 이 call site C 의 N번째 인자이고, callee f 의 N번째 arg-kind
variable 이 v2 면, v1 → v2 후보"** 라는 *index lookup* 뿐. derived
view 화하면 R-12 도 자연 면역.

**핵심 패턴 인사이트**: ADR-0043 (hex pane) → ADR-0044 (PP4) →
ADR-0045 (PP1) — **3번째 display-only path 채택**. R-9 boundary 가
"engine record + lookup OK / 추론 X" 로 안정 정착.

**Alternative B** (1급 `AuraTypePropagationEdge` record): provenance
부착 의무 → "AURA 가 source 인 record" 발생 → R-9 위반. 거부.

### D2 — Propagation v1 scope: **caller var → callee parameter (1-step)**

오직 *직접 호출의 매개변수 매칭* 한 단계. return-type 양방향 (B),
alias chain (C) 모두 deferred / 거부.

**핵심 R-9 회피**: caller 측 "v1 이 N번째 인자로 전달됨" 은
calling-convention 해석 = AURA 가 못함. 따라서 v1 = **사용자가
선택한 callee 매개변수 슬롯에 한해** target_type 을 후보로 표시.
caller variable → call site 매핑은 engine (rizin `afvR` /
Ghidra HighFunction) 이 emit 해야 가능 — v1 미지원, GUI 가 "직접
callee arg 슬롯 선택" UX.

매칭 알고리즘 (C2 reference):
```
for ce in call_edges where ce.caller_id == F:
    for instr i where i.function_id==F and i.type=="call"
                       and i.jump==ce.callee.entry:
        // call site i.addr 확정
        callee_args = [v for v in variables
                       where v.function_id==ce.callee_id and v.kind=="arg"]
        for callee_arg in callee_args:
            old = typeFact(callee_arg)?.type_str ?? ""
            candidates.append({
                source: "callee_param",
                from_var: target_var, to_var: callee_arg.var_id,
                distance: 1, call_site: i.addr,
                old_type: old, new_type: target_type
            })
```

**Reason 옵션 B (return) 거부**: engine 이 return-value variable 일관
emit X — false positive 양산. **C (alias) 거부**: R-9 직격탄
(영구 거부 — engine 이 emit 해야 가능).

### D3 — Override store: **`AURA_OVERRIDE_PAYLOAD_TYPE` 재활용 (schema bump 0)**

`override_store.h:50` 의 enum 슬롯이 이미 정의되어 있고 사용처 0.
payload `text` 에 type literal ("UserStruct*", 256 byte cap) 그대로
저장. target identity 는 기존 `AuraOverrideKey` 의
`target_kind=VARIABLE` + `target_stable_id=var_id`.

**Reason**: 신규 enum 추가 = schema migration + R-5 정합 검증 재수행.
기존 슬롯 재활용 = 0 cost. cycle-9/16 RENAME path 와 동일 path → R-5
자동 보장.

**Alternative**: ANNOTATION + "TYPE:" prefix → enum 의미 희석. 거부.

### D4 — CLI: **`aura propagate-type --var <id> --target-type "<T>" [--dry-run|--apply]`, dry-run default**

JSON `{candidates: [{var_id, function_id, function_name, old_type,
new_type, distance, source, call_site_addr}, ...]}`. `--apply` flag
명시 시만 store 쓰기 (default dry-run JSON only). `--apply` 는
candidate id list (또는 `--all`) 동반 의무 — 부분 선택 CLI 에서도 지원.

**Reason**: PP4 `label-candidates` 와 동일 SRP. 즉시 apply 위험
(잘못 전파 시 분석 붕괴) → 사용자 확인 게이트 강제. dry-run default =
R-5 의 "override 누적은 명시적 사용자 의도" 정합.

### D5 — GUI: **Variable 우클릭 → Propagation Tree dialog (옵션 A only)**

DecompilePane (ADR-0042) + Variables dock 양쪽 우클릭 메뉴 "Propagate
type..." → modal QDialog. content = QTreeView (root: 선택 변수 —
child: 후보 callee parameter, 각 row checkbox + old/new type column) +
target-type LineEdit + Apply / Cancel. Apply → 체크된 row 만
`override_store_put(TYPE)` 일괄. 미체크 row = 무시 — **부분 선택 =
사용자 directive 직격 충족**.

**Reason 옵션 B (별도 dock) 거부**: active-variable 추적 = surface
noisy. PP4 의 popover 패턴 일관 답습. mmap (D6) 은 candidate set >
100k 인 binary 에서만 의미 — v1 in-memory.

### D6 — DB apply path 승인: **candidate cache 없이 TYPE override 만 영속**

**승인 (2026-05-06, 사용자 지시)**: 타입 전파 수정과 후속 기능을 위해
DB 개선을 허가한다. 단, 개선 범위는 `variables[]` / `type_facts[]` /
`call_edges[]` 전체 분석 캐시나 `type_propagation_candidates` 테이블을
신설하는 것이 아니라, 사용자가 명시적으로 Apply 한 후보만 기존
`override_store` 의 `AURA_OVERRIDE_PAYLOAD_TYPE` row 로 저장하는 것이다.

구현 계약:
- `propagate-type --apply` 는 `--all` 또는 `--candidate-ids` 가 있을 때만
  store 를 쓴다. dry-run 은 기존처럼 store touch 0.
- 저장 key 는 `aura_override_key_from_variable_record()` 를 사용하고,
  `target_kind=VARIABLE`, `payload_kind=TYPE`, `payload_text=<target_type>`.
- 저장 row 는 사용자 명시 Apply 이므로 `ACTIVE` 로 기록한다.
- 후보 목록은 derived view 로 유지한다. 후보 캐시 / 분석 결과 전체
  캐시는 별도 D 결정 전까지 도입하지 않는다.

## Cycle plan (5 cycles, C6 옵션)

| Cycle | Focus | Files |
|------|------|-------|
| C1 (cycle-26, this) | ADR + display-only 명세 + heuristic 알고리즘 + payload kind 결정 | `docs/adr/0045-pp1-type-propagation.md`, `AUTOMATION_ROADMAP.md` |
| C2 (cycle-27) | propagation candidate 알고리즘 (D2 v1) — `src/core/type_propagation.{h,cpp}` (derived view, R-9 면역) + unit test | new src + tests/unit |
| C3 (cycle-28) | CLI `propagate-type` (--dry-run default + --apply --candidate-ids) + cli_smoke | `src/cli/main.cpp`, cli_smoke |
| C4 (cycle-29) | GUI tree dialog + checkbox 부분 선택 + menu entry + gui_smoke | `src/gui/main_window.{h,cpp}`, decompile_pane.cpp, gui_smoke |
| C5 (cycle-30) | Apply path 통합 — selected → `override_store_put(TYPE)` 일괄 + 결과 toast | main_window.cpp |
| C5a / 11.4.3-v2 (2026-05-06) | PP1 store wire 승인/구현 — `--apply --all/--candidate-ids --project` → `override_store_put(TYPE)` | `src/cli/main.cpp`, cli_smoke |
| C6 (cycle-31, opt) | mmap 직렬화 — candidate set > 100k binary 한정 | new `src/core/type_propagation_cache.{h,cpp}` |

## R-1 / R-5 / R-9 / R-10 / R-12 guards (명시)

- **R-1**: AURA 가 자체 binary 분석 X. 모든 source 가 record
  (`variables[]/type_facts[]/call_edges[]/instructions[]`) 의 *index
  lookup*. calling convention 해석 안 함 (D2 v1 한계).
- **R-5 (핵심)**: Apply path = 기존 `override_store_put(AURA_OVERRIDE_PAYLOAD_TYPE)`
  (이미 정의된 enum 슬롯). `AuraEngineResponse.body` mutate 0.
  candidate 생성/조회는 store touch 0.
- **R-9 (핵심)**: TypePropagationCandidate = derived view (display-only,
  ADR-0043/0044 패턴 3번째 채택). `AuraRecordCollection` 추가 X, body
  schema bump X. **alias 분석 / pointer-to 추적 / data-flow 추론 모두
  거부** — caller 측 인자 매핑조차 engine 이 emit 안 하면 후보 미생성
  (false positive 회피 > 완전성).
- **R-10**: `RzCore *` / librz 미사용. `aura_records_*_at` accessor만.
- **R-12**: 1급 record schema 변경 0. body version v3 그대로. payload
  enum 기존 슬롯 재활용.

## Alternatives considered (요약)

- D1 1급 record (`AuraTypePropagationEdge`): R-9 위반 (provenance =
  AURA 가 source). 거부.
- D2 옵션 B (return-type 양방향): engine return-variable 누락 → false
  positive. v2.
- D2 옵션 C (alias chain): R-9 직격탄. 영구 거부.
- D3 신규 `AURA_OVERRIDE_PAYLOAD_TYPE_PROPAGATE` kind: 기존 TYPE 슬롯
  미사용 → 중복. 거부.
- D3 ANNOTATION + "TYPE:" prefix: enum 의미 희석. 거부.
- D4 GUI-only (CLI 생략): cli_smoke 회귀 불가. 거부.
- D5 옵션 B (별도 dock): noisy + 패턴 X. v2.
- D5 옵션 C (둘 다 + popover): surface 폭발. 거부.
