# ADR-0044 — Phase 11.4.2 (P4.PP4) Auto-labelling: candidate suggestion

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Related**: ADR-0033 (LLM additive 원칙 — AURA core 무 LLM),
  ADR-0037 (Override Editor / RENAME path), ADR-0039 (StringRecord —
  PP4 primary signal source), ADR-0040 (InstructionRecord — PP4
  consumer), ADR-0042 (DecompilePane context menu — popover host),
  ADR-0043 (Hex pane display-only path — 본 ADR 의 D5 패턴).

## Context

P3 (packaging, cycle-22) closed. PP4 = plan v2 의 RE 도구 차별화
페인 포인트 4종 중 첫 entry — 사용자 directive: **자동 적용 X — 후보군
제시 + 사용자 선택**으로 LAB_xxxxx → 의미명 좁히기.

선결 자산 모두 갖춤:
- `AuraXrefRecord` (R-12, Phase 2A) — function 으로 흐르는 xref 들
  (call/data/code).
- `AuraSymbolRecord` (Phase 11.3.5) — system call / library function
  이름 (kind=IMPORT 의 name).
- `AuraStringRecord` (Phase 11.3.6) — string literal (function 에서
  참조되는 message).
- `aura_llm` 모듈 (libcurl + LM Studio API) — Phase 6 자산.
- `override_store_put RENAME` — cycle-9 / cycle-16 검증.

## Decisions

### D1 — Candidate sources: **(a) string + (b) call-pattern v1; (d) LLM v2 deferred**

v1 후보 = 두 휴리스틱 source:

  (a) **String reference**: function 내부에서 참조되는 StringRecord 의
      content. xref `from_addr` 가 function `[entry, entry+size)` 안에
      있고 `to_addr` 가 string 의 addr 와 매칭되는 것을 모음.
  (b) **Call pattern**: function 이 호출하는 IMPORT SymbolRecord 이름.
      xref `from_addr ∈ function` 이고 `to_addr` 가 import symbol 의
      addr 와 매칭.

  (c) API similarity / 시그니처 매칭 — 거부 (fixture 수집 비용 + 정의
      모호).
  (d) LLM — **v2 (별도 cycle 4)**.

**Reason**: (a)+(b) 만으로 PP4 의 80% user-value 달성 (가장 흔한 RE
패턴: "이 함수는 `printf("login failed")` 호출 → `do_login` 후보").
LLM 을 v1 에 묶으면 (a)+(b) 의 결정성 회귀를 LLM 비결정성
(network/timeout) 이 가린다.

**Alternative** (모두 v1): 매트릭스 폭발. 거부.

### D2 — CLI surface: **별도 `aura label-candidates --func <hex>`**

JSON `{candidates: [{name, source: "string"|"import"|"llm",
confidence, evidence: {addr, snippet}}, ...]}`.

기존 `llm-context` 와 책임 분리:
- `llm-context` = *payload 생성기* (사용자가 LLM 호출).
- `label-candidates` = *ranked answer* (사용자가 선택).

**Reason**: SRP. `llm-context --suggest-rename` flag 추가는 거부 —
heuristic (a)+(b) 는 LLM 무관, AURA core 가 emit 하는 게 자연.

### D3 — GUI: **함수 우클릭 → "Suggest labels..." popover (옵션 A only)**

DecompilePane (ADR-0042 cycle-16 의 context menu) + FunctionTable 양쪽
우클릭 메뉴에 "Suggest labels..." 항목 추가 → modal QDialog (≤5 후보
list + Apply 버튼 + Cancel). Apply → 기존 `renameFunctionAt(row, name)`
재사용 = override_store RENAME path 그대로.

**Alternative B** (별도 dock 일괄): noisy + Cutter/IDA 패턴 X. v2
deferred.

### D4 — LLM 통합: **v2 deferred (별 cycle-26)**

v1 cycle 1~3 = heuristic 만. v2 cycle-26 = LLM source — `aura_llm`
직접 호출 X (ADR-0033 의 *additive* 원칙 보존). GUI 만 `LlmClient` 사용
가능. timeout 5s, fallback = source list 에서 "llm" 항목 생략.
heuristic 후보는 그대로 표시.

LM Studio default `http://122.43.160.242:1234`, `qwen3-coder-next`
(cookbook).

**Reason**: ADR-0033 "AURA core 가 LLM 안 호출" 보존 —
`label-candidates` CLI 는 heuristic only, GUI 만 LLM client 와 결합.

### D5 — Record status: **LabelCandidate = display-only (NOT 1급 record)** ← 핵심

LabelCandidate 는 `AuraRecordCollection` 추가 X, body schema bump X.
*Derived view* — 기존 record (Function/Xref/String/Symbol) 위 *selection
+ ranking* 결과. ADR-0043 hex pane 의 "display-only path" 패턴 답습.

**Reason (R-9 핵심)**: candidate 는 *분석 산출* 이 아니라 *질문에 대한
답변 후보*. LLM 응답을 record 화하면 R-9 의 "AURA 가 분석 추론" 이 됨
— 거부. heuristic 도 마찬가지 (record 의 *index lookup*, 아닌 *해석*).
Candidate 는 CLI JSON / GUI dialog 의 *transient* 데이터.

**핵심 통찰**: AURA 가 LLM 응답을 "분석"으로 취급할 수 없음 → engine
처럼 1급 record 화 거부 → display-only path → R-9/R-12 모두 자연 우회.
사용자가 Apply 클릭하면 `override_store_put RENAME` 으로 비로소 영속화
— 이미 R-5 정합 path.

## Cycle plan (4 cycles)

| Cycle | Focus | Files |
|------|------|-------|
| C1 (cycle-23, this) | ADR + LabelCandidate display-only 명세 + heuristic ranking 알고리즘 | `docs/adr/0044-pp4-auto-labelling.md`, `AUTOMATION_ROADMAP.md` |
| C2 (cycle-24) | CLI `label-candidates --func` + heuristic (a)+(b) + cli_smoke TC | `src/cli/main.cpp` (subcommand + run_label_candidates), `tests/integration/cli_smoke/cli_smoke.cpp` |
| C3 (cycle-25) | GUI popover (옵션 A) + Apply → renameFunctionAt 재사용 + gui_smoke | `src/gui/main_window.{h,cpp}` (context menu + QDialog), `src/gui/decompile_pane.cpp` (menu entry), `tests/integration/gui_smoke/gui_smoke.cpp` |
| C4 (cycle-26) | LLM source 추가 (D4) — GUI-only (`LlmClient` 호출) + timeout/fallback | `src/gui/main_window.cpp`, `src/llm/llm_client.h` 재사용 |

## Heuristic ranking algorithm (C2 reference)

```
candidates = []
for xref in xrefs where xref.from_addr ∈ [func.entry, func.entry+func.size):
    for sym in symbols where sym.kind==IMPORT and sym.addr == xref.to_addr:
        candidates.append({
            source: "import",
            name:    derived_name(sym.name),  // strip "imp." / "sym." prefix
            confidence: 0.7,
            evidence: { addr: xref.from_addr, target: sym.name }
        })
    for str in strings where str.addr == xref.to_addr:
        candidates.append({
            source: "string",
            name:    snake_case_from_string(str.content),  // first 24 chars
            confidence: 0.6,
            evidence: { addr: xref.from_addr, snippet: str.content }
        })

candidates.sort(by confidence desc, then by source preference: string > import)
return candidates[:5]
```

`snake_case_from_string`: lowercase + non-alnum→`_` + collapse `__`,
truncate 24 chars. `derived_name`: trim known prefixes / `__`-separators.

## R-1 / R-5 / R-9 / R-10 / R-12 guards (명시)

- **R-1**: AURA 가 자체 binary 분석 X. 후보 source 모두 record
  (`xrefs[]/strings[]/symbols[]`) 의 *index lookup*. heuristic 결합 =
  ADR-0039 의 "select / rank" 정합.
- **R-5 (핵심)**: Apply path = 기존 `override_store_put RENAME`
  (cycle-9/16 검증). `AuraEngineResponse.body` mutate 0. label
  candidate 생성/조회는 store touch 0 (v1 transient).
- **R-9 (핵심)**: LabelCandidate = derived view (display-only path,
  ADR-0043 hex pane 패턴). `AuraRecordCollection` 추가 X, body schema
  bump X. LLM 응답 record 화 거부.
- **R-10**: `RzCore *` / librz 미사용. heuristic 은
  `aura_records_xref_at` / `aura_records_string_at` /
  `aura_records_symbol_at` accessor 만 호출.
- **R-12**: 1급 record schema 변경 0. body version v3 그대로.

## Alternatives considered (요약)

- D1 v1 = (a)+(b)+(c)+(d): 매트릭스 폭발, 비결정성 가림. 거부.
- D2 wrapper script: heuristic 이 LLM 무관 → 거부, core CLI 가 자연.
- D3 옵션 B/C: surface 폭발 / noisy. v2.
- D4 v1 LLM 포함: ADR-0033 "AURA core 무 LLM" 위반 + 비결정성. v2.
- D5 LabelCandidate = 1급 record: R-9 위반 (AURA 분석). 거부.
