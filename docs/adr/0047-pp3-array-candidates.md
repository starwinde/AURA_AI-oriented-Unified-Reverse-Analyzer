# ADR-0047 — Phase 11.4.5 (P4.PP3) Array/Pointer Expression: candidate stat

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Related**: ADR-0033 (LLM additive 원칙), ADR-0040 (InstructionRecord
  + DisasmBody 분리), ADR-0042 (DecompilePane context menu — popover
  host), ADR-0043 / ADR-0044 / ADR-0045 / ADR-0046 (display-only path —
  본 ADR 의 **5번째 적용**), Phase 11.4.4 PP2 (stride 의 PP2 의 자연
  확장).

## Context

PP4 + PP1 + PP2 모두 v1 closed (cycle 23~33). PP3 = plan v2 의 RE
도구 차별화 4종 중 **마지막**.

사용자 directive: **`array[5]` 가 `*(base+20)` 같은 pointer arithmetic
으로만 보임 → 마우스 hover/좌클릭 시 배열 후보 표시**.

선결 자산:
- `AuraInstructionRecord.op_str` (Phase 11.3.7) — `[base+offset]` 패턴.
  PP2 와 동일 source.
- `AuraXrefRecord` — data access 패턴.
- `AuraTypeFactRecord.type_str` — `"int[10]"` literal (engine emit
  성공 시).
- **MainWindow::runDisasm + disasmList** (cycle-19, Phase 11.3.10) —
  GUI 가 함수별 disasm 결과 in-process cache. **PP2 cycle-32 의
  deferred (a) op_str source 가 PP3 GUI-only path 에서 자연 해결**.

## Decisions

### D1 — Candidate sources: **(a) op_str + (c) variable cluster v1; (b) opportunistic; (d) LLM v2**

  (a) **op_str pattern**: `[base+offset]` 또는 `[base+offset+index*scale]`
      — 같은 base 에 multiple offset → stride 후보 raw stat.
  (c) **Variable / xref cluster**: base var 에 multiple offset access
      집계.
  (b) **TypeFactRecord type_str literal** — `"int[10]"` 형태 strncmp
      매칭, opportunistic (engine emit 시만).
  (d) **LLM stride → array 추론** — v2 별 cycle, GUI-only.

**핵심 차이 (vs PP2)**: PP2 cycle-32 가 (a) op_str 을 v2 deferred 한
이유는 analyze body 에 `instructions[]` 미보유 (ADR-0040 D4 분리). PP3
GUI 에서는 `MainWindow::runDisasm(funcAddr)` 가 이미 in-process disasm
cache 를 채우므로 (a) source GUI-only 활성 가능. CLI 는 PP2 와 같은
이유로 deferred.

### D2 — R-9 boundary: **arithmetic (count/diff/gcd) OK / 분석 어휘 emit 영구 거부** ← **5번째 적용 시 추가된 새 차원**

**OK**: "이 base 에 등장한 offset list + sorted diffs (offsets[i+1] -
offsets[i]) + GCD + max" — 모두 *count / diff / GCD* = **arithmetic,
추론 X**. PP2 의 "cluster offsets 모음" 의 자연 확장 (한 통계 더 — 차분).

**거부**: "stride=4 이므로 element 가 int" / "이 base 가 array of struct
foo" — **자료형 정의 합성** = R-9 직격탄 (PP2 D2 의 영구 거부와 동형).
사용자/LLM 위임.

**중간 회색지대 — Step 3 naming hygiene 가드**: "stride 4 일 가능성"
같은 자연어 hint label 도 **금지**. JSON / GUI 는 raw stat (`offsets:
[0, 4, 8, 12], diffs: [4, 4, 4], gcd: 4`) **만** 표시 — 사용자가
stride 라고 *읽음*. **AURA 가 "array" / "stride" / "element_type" 단어
emit 영구 거부**. PP2 의 "var_id list + stack_offset" 이 사용자가
struct 라고 *읽는* 패턴과 정확히 동형.

이 hygiene 가드는 PP1~PP2 에서 묵시적이었으나 PP3 에서 명시 필수 —
사용자 directive ("array 후보") 가 자연 욕구 ("stride=N → array[N/elem]"
단어 emit) 로 흐를 수 있음. 본 ADR 에 박아둠.

### D3 — CLI: **`aura array-candidates --func <hex>` (PP2 와 동형 SRP)**

JSON `{candidates: [{base_reg, offsets:[...], diffs:[...], gcd,
sample_addrs}, ...], type_hints: [{var_id, type_str_with_brackets}]}`.
v1 = (b) opportunistic + (c) variable cluster — (a) op_str = PP2 와
같은 이유로 v2 deferred. CLI GUI-only 거부 (cli_smoke 회귀 안전망 손실).

### D4 — GUI: **우클릭 popover (옵션 B), hover tooltip = v2**

PP4 / PP1 / PP2 dialog 패턴 5번째 답습 — Variable/Function 우클릭 →
"Suggest array shape..." → QListWidget (per-row checkbox) + diff/gcd
컬럼.

**Hover tooltip 거부 (v2)**:
1. surface noisy
2. QPlainTextEdit cursor hover → addr resolve → engine raw text 위에
   transform = R-5 위반 위험
3. PP4/PP1/PP2 의 dialog 패턴 4번 답습 = 학습/테스트 비용 0
4. hover 는 *부분 선택* (체크박스) UX 불가 — 사용자 directive "후보
   표시" 충족 X

**GUI-only path**: (a) op_str source 활성. `disasmList(funcAddr)` 위
in-process stride grouping. R-9 boundary 동일.

### D5 — Apply path: **v1 = no-apply (statusBar count toast)**

Engine decompile text 의 "transformed view" 저장 = R-5 직격탄 (engine
output mutate). Override layer 에 "addr X 의 base+offset = array idx"
hint 저장은 신규 `AURA_OVERRIDE_PAYLOAD_ARRAY_HINT` enum 필요 →
**schema bump + R-12 검증 재수행 → 본 plan 외**. PP1 v2 store wire +
PP2 struct definition slot 두 개 이미 deferred — **3번째 deferred slot
만들 합리 0**.

v1 = "선택된 N 후보 statusBar count" (PP1/PP2 와 동일 pattern). apply
path = PP3 v2 별 cycle.

## Cycle plan (4 cycles)

| Cycle | Focus | Files |
|------|------|-------|
| C1 (cycle-34, this) | ADR + display-only 5번째 명세 + Step 3 naming hygiene 가드 명문화 | `docs/adr/0047-pp3-array-candidates.md`, `AUTOMATION_ROADMAP.md` |
| C2 (cycle-35) | CLI `aura array-candidates --func <hex>` + heuristic (b) + (c) + cli_smoke | `src/cli/main.cpp`, cli_smoke |
| C3 (cycle-36) | GUI "Suggest array shape..." popover + (a) op_str source GUI-only 활성화 (`disasmList(funcAddr)` stride grouping) + gui_smoke | `src/gui/main_window.{h,cpp}`, gui_smoke |
| C4 (cycle-37) | contract TC 강화 + naming hygiene 회귀 가드 + PP3 close + **PP1~PP4 4종 차별화 ALL CLOSED** | gui_smoke + ROADMAP |

## Display-only path 5번째 채택 — decision tree

| Step | 질문 | PP3 답 |
|---|---|---|
| 1 | 데이터 source = 기존 record field? | **Yes** — op_str / stack_offset / from-to_addr / type_str |
| 2 | 조작 = select + group + count? | **Yes** — base 별 group + offset 정렬 + 차분 산출 (arithmetic, 추론 X) |
| 3 | 합성 산출물 = 새 분석 객체? | **No** — `(base, offsets[], diffs[], gcd)` raw stat 모음, **분석 어휘 emit X** |
| 4 | Apply = 기존 override slot? | **N/A v1** (no-apply), v2 시 신규 enum 별 ADR |

→ 5번째 채택 OK. **Pattern 정착 단계** — hex(F5) → PP4 → PP1 → PP2 →
PP3 로 R-9 boundary 가 **"engine record + lookup/arithmetic OK / 추론
OR 분석 어휘 emit X"** 로 확장 정의됨.

## R-1 / R-5 / R-9 / R-10 / R-12 가드 (명시)

- **R-1**: 자체 disassemble/analyze X. base/offset 모두 record substring
  / field lookup. 차분/GCD = arithmetic (분석 X).
- **R-5**: v1 store touch 0. apply path 자체가 v2 별 ADR.
- **R-9 (핵심)**: ArrayCandidate = derived view (5번째 적용). raw stat
  (offsets, diffs, gcd) 만 emit. **"stride/array/element_type" 분석
  어휘 emit 영구 거부** — PP2 의 "struct 정의 합성" 거부와 동형. v2
  stride→array 추론은 LLM 경유.
- **R-10**: librz 미사용. `aura_records_*_at` accessor + `disasmList()`
  GUI cache 만.
- **R-12**: 1급 record 추가 0. body schema bump 0. payload enum 추가
  0 (v1 no-apply).

## Alternatives considered (요약)

- D1 v1 = (a)+(b)+(c)+(d): 매트릭스 폭발. 거부.
- D1 v1 (a) only: variable / xref 단서 누락 → 후보 빈약. 거부.
- D2 stride → element type 추론 v1: R-9 직격탄. 영구 거부.
- D2 자연어 hint ("stride=4 후보") emit: Step 3 naming hygiene 위반.
  영구 거부.
- D3 GUI-only (CLI 생략): cli_smoke 회귀 손실. 거부.
- D4 옵션 A hover only: 부분 선택 X + R-5 위험. v2.
- D4 옵션 C 둘 다: surface 폭발. v2.
- D5 apply v1 (decompile text transform): R-5 위반. 거부.
- D5 신규 `AURA_OVERRIDE_PAYLOAD_ARRAY_HINT`: schema bump + R-12 재검증,
  별 ADR. v2.
