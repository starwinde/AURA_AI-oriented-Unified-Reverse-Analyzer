# AURA — Engine-Integrated Reverse Engineering Platform

> PRD v1.0 (pivot baseline). 본 문서는 [Tasks.md](./Tasks.md) · [rules.md](./rules.md) 와 함께 관리된다.

---

## 1. 정체성

> AURA는 다음과 같은 소프트웨어다:
>
> "C/C++ 네이티브 기반 리버스 엔진 통합 플랫폼으로, 기존 디컴파일러의 결과를 그대로 활용하면서, 그 위에서 수정·전파·추적·비교가 가능한 분석 환경을 제공한다."

**핵심 명제**

- AURA 는 **엔진이 아니다**. 엔진 오케스트레이터 + 분석 UI 다.
- 분석·디컴파일 결과의 **단일 진실 원천 (source of truth) = 외부 엔진**. **request type 별로 primary 집합이 정의된다** — `disasm`/`analyze`/`trace` primary = `{rizin}`, `decompile` primary = `{rizin, ghidra}` (사용자 선택).
- **모든 분석 결과의 source-of-truth 는 외부 엔진이며, AURA 는 해당 결과를 생성·수정·보정하지 않는다.**
- AURA 의 역할 = 결과를 **재가공·통합·편집·추적**.
- 사용자 수정은 **override layer** 로 누적되며 엔진 원본 출력은 불변 (immutable).
- 엔진 출력은 raw + normalized **2-layer snapshot** 으로 보존되며, 모든 normalized record 는 `{source, confidence, completeness}` provenance 메타를 갖는다. 함수·블록·변수·타입 사실·호출 엣지 등은 독립 record (`FunctionRecord` / `BlockRecord` / `EdgeRecord` / `VariableRecord` / `TypeFactRecord` / `CallEdgeRecord` / `SymbolRecord` / `XrefRecord`) 로 1 급 분해된다.

**슬로건**

Existing engines, integrated. Native performance, modern UX.

---

## 2. 사용자 대상

| 페르소나 | 핵심 가치 |
|---------|----------|
| 보안 연구원 | Ghidra 정확도 + 빠른 응답 + 무료 |
| 악성코드 분석가 | 다중 엔진 비교 + LLM 보조 행위 요약 |
| CTF 참가자 | 가벼운 진입 장벽, 즉시 사용 가능 |
| 보안 학생/연구자 | 직관적 UI, 학습 곡선 낮음 |

---

## 3. 핵심 기능

| # | 기능 | 설명 |
|---|------|------|
| F-1 | **디컴파일 결과 표시 (fidelity)** | 외부 엔진 (Rizin / Ghidra co-primary) Pseudo-C 를 변형 없이 그대로 표시. 두 엔진 결과는 사용자 선택 (D-28). |
| F-2 | **변수 Rename + 전파** | 사용자가 변수명 변경 시 같은 SSA 정의를 참조하는 모든 use-site 자동 갱신 |
| F-3 | **타입 변경 + Cascade 전파** | 타입 retype 시 caller / callee 인자 / 구조체 필드 자동 cascade |
| F-4 | **CFG / HIR 동기화** | 디컴파일 뷰와 CFG 뷰가 동일 IR 을 share, 클릭 동기 highlight |
| F-5 | **Trace (역추적)** | Trace 는 엔진이 제공한 정의·참조 관계를 시각화하는 기능이며, AURA 가 새로운 데이터 흐름 분석을 수행하지 않는다. |
| F-6 | **다중 엔진 결과 비교** | Decompiler 비교: Rizin/Ghidra co-primary + RetDec secondary 후보. Disasm cross-check: Rizin primary + Capstone secondary 후보. Analysis primary 는 Rizin 단독이며 Ghidra analysis primary 승격은 별도 D 결정 필요. |
| F-7 | **대용량 바이너리 mmap 처리** | UI 스레드 동결 없이 lazy 로드 |
| F-8 | **LLM 보조 분석** | 자동 네이밍·요약 (옵션, 결과는 사용자 승인 후 override 로 저장) |
| F-9 | **Token Classification Model + Rule Pack 기반 Privacy Filter & Policy Gateway** | 실행 중인 GUI 를 `aura gui ...` CLI 로 제어하고, 향후 `aura-mcp` 가 Token Classification Model(`openai/privacy-filter` 기본 후보), 한국형/Secret Rule Pack, Eval Dataset 기반 평가를 결합한 민감정보 마스킹 시스템, 정책 allowlist, 길이 제한, 감사 로그를 거친 MCP tool 로 LLM/agent 에 제한된 분석 결과만 제공. 현재 구현 기준은 문자열 기반 마스킹 MVP 이며, 모델/룰셋/데이터셋 결합 탐지는 후속 확장 목표다. 기본 생성형 LLM 배치는 1개이며 gateway 는 두 번째 생성형 LLM 이 아니다. 새 분석 기능은 Strict MCP Coverage 에 따라 MCP surface 까지 함께 갱신되어야 완료로 본다. |
| F-10 | **Cutter-style 트리 브라우저** | 함수·참조·심볼·임포트·문자열을 좌측 `QTreeView` 로 표시한다. parent row 는 대표 엔티티, child row 는 엔진 metadata 이며, 미제공 값은 추론하지 않고 `-` 로 표시한다. 문자열 보호 v1 UI 는 별도 Safety 탭이 아니라 Strings 탭에 귀속한다. 보호 child row 는 최하단에 `기존`/`별칭`/`마스킹` 순서로 배치하고, 원문 `기존` row 는 민감정보 상세 표시 설정이 켜진 경우에만 노출한다. `Ctrl+F` 는 마지막으로 클릭/포커스한 패널을 기준으로 해당 tree/code pane 안에서 검색한다. |
| F-11 | **Cutter-style 전체 디스어셈블리 listing** | 함수 단위 디스어셈블리와 별도로 연속 VA listing 을 제공한다. 사용자는 주소 입력 page 가 아니라 함수 목록 선택으로 해당 위치에 스크롤한다. 내부 구현은 `pdj <count>` structured stream 과 bounded `pD 4096` arrow text 를 함께 사용하며, `pD` mixed listing 으로 invalid/data/comment/label 줄도 보존한다. Decompile / Disassembly / Full Disassembly pane 은 기본 syntax highlighting 을 제공해 주소, mnemonic, register, 숫자, 문자열, 주석, invalid line 을 구분한다. |

---

## 4. 시스템 구조

```
┌──────────────────────────────────────────────┐
│           AURA UI  (Qt6, C++)                │
└────────────────────┬─────────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────────┐
│        Analysis Orchestrator  (C/C++)        │
└────────────────────┬─────────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────────┐
│        Engine Request Layer                  │
│  request types: disasm / analyze /           │
│                 decompile / trace (optional) │
└────────────────────┬─────────────────────────┘
                     │
        ┌────────────┴─────────────┐
        ▼                          ▼
┌────────────────┐         ┌──────────────────┐
│ Engine Adapter │         │  Override Layer  │
│   - Ghidra     │         │  (사용자 수정)    │
│   - RetDec     │         └──────────────────┘
│   - Rizin      │                  │
│   - Capstone   │                  │
└────────┬───────┘                  │
         │                          │
         ▼                          │
┌──────────────────────────────────────────────┐
│       Unified IR  (HIR / CFG / Func / Sym /  │
│                   Type)                      │
└────────────────────┬─────────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────────┐
│        mmap-based binary data                │
└──────────────────────────────────────────────┘
```

**원칙**

- 모든 엔진 = stateless subprocess + adapter layer.
- 통신 = stdout/stderr 텍스트 프로토콜 (Ghidra = XML).
- 엔진 출력 = Unified IR 로 변환 후 영속 (discard 금지).
- 사용자 수정 = override layer 에 누적, 엔진 출력 변형 금지.
- 실행 표면은 3개로 분리한다: `aura-gui` 는 사람이 쓰는 Qt GUI,
  `aura gui ...` 는 실행 중인 GUI 에 붙는 localhost IPC client,
  `aura-mcp` 는 LLM/agent 용 **Privacy Filter & Policy Gateway**(계획)다.
  MCP 는 엔진 또는 GUI RPC 를 직접 노출하지 않고 allowlist / length
  limit / masking / audit / user approval 을 적용한다. Privacy Filter 는
  문자열 기반 MVP 에서 시작하고, 목표 구조는 **Token Classification Model,
  Rule Pack, Eval Dataset 을 결합한 민감정보 마스킹 시스템**이다. 기본 runtime
  asset 위치는 `~/.aura/token-classification-models/`, `~/.aura/rule-packs/`,
  `~/.aura/eval-datasets/`, `~/.aura/safety-profiles/` 로 둔다. 이 gateway 는
  두 번째 생성형 LLM 모델이 아니라 정책 계층이며, 기본 제품 설명은
  **1개 생성형 LLM + Token Classification/Rule 기반 프라이버시 필터 + 정책 게이트웨이**로 고정한다.
- MCP 는 GUI tab/screen scraping 이 아니라 Unified Model record 와 Safety Core
  export-safe view 를 기준으로 노출한다. 새 분석 도구, 분석 데이터, 자동화 명령,
  export 기능은 Strict MCP Coverage 대상이며 MCP 반영 없이는 완료로 보지 않는다.
- MCP 응답은 공통 MCP Schema Envelope 을 사용하고, RE engine/model 이 바뀌어도
  base record 구조체와 schema 를 바꾸지 않는 Engine-Agnostic Record Contract 를
  따른다. engine 별 추가 정보는 `extensions.<engine_id>` 또는 raw artifact
  reference 로 격리한다.
- MCP 기본 tool 은 원문을 반환하지 않는 Protected MCP Tool 로 설계한다. 원문
  접근은 별도 Privileged MCP Tool 에서만 허용하며, raw-access session toggle,
  요청별 사용자 확인, bounded scope, Raw Disclosure Event audit log 를 모두
  요구한다. audit log 는 원문 값을 저장하지 않는다.
- MCP 기능은 smoke test 만으로 완료하지 않는다. Schema/Error envelope,
  protected default, raw non-disclosure, privileged denial, per-request approval,
  bounded scope, raw disclosure audit, engine-agnostic schema, compatibility 를
  포함하는 MCP Security Regression Gate 를 통과해야 완료다.
- GUI 기본 workspace 는 Cutter식 좌측 브라우저 + 우측 코드 탭이다.
  좌측 상단은 Functions/Xrefs, 좌측 하단은 Strings/Symbols/Imports,
  우측은 Decompile/Disassembly/Full Disassembly/CFG/Hex 로 둔다.
  브라우저는 display-only tree 이며, 엔진이 주지 않은 값은 합성하지 않는다.
  문자열 보호 v1 UI 는 `Strings` 탭에 귀속하고, 보호 child row 는 최하단에
  `기존`/`별칭`/`마스킹` 순서로 둔다. `기존` 원문 row 는 기본 숨김이며
  민감정보 상세 표시 설정이 켜진 경우에만 노출한다.
  Full Disassembly 는 Rizin `pdj <count>` structured stream 과 bounded
  `pD 4096` arrow text 로 구현하되, `Structured` 탭은 `pD` mixed listing 을
  분류해 invalid/data/comment/label 줄도 보존한다. UI 는 Cutter처럼
  `Structured` / `With arrows` 탭 + 함수 선택 스크롤 방식으로 제공한다.
- 현재 reference execution baseline = **Rizin 0.8.0 shared64 + rz-ghidra
  0.8.0**. 기본 경로는
  `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/...`,
  pseudo-C decompile 은 같은 bundle 의 `rz_ghidra_sleigh` 를
`SLEIGHHOME` 으로 사용한다 (ADR-0052).
- 보안 제품이 이 toolchain 을 cyber security risk 로 표시할 수 있다.
  이는 리버스 엔지니어링 도구의 예상 가능한 평판/행위 기반 경고이며,
  AURA 는 이를 우회하지 않는다. 출처/버전/해시/로컬 분석/LLM 자동 전송
없음으로 관리한다 (ADR-0052).

**Engine Request Types**

| 타입 | 의미 |
|------|------|
| `disasm` | 명령어 단위 디스어셈블 결과 요청 |
| `analyze` | 함수·심볼·CFG·타입 등 정적 분석 결과 요청 |
| `decompile` | Pseudo-C 결과 요청 |
| `trace` *(optional)* | 엔진이 제공하는 정의 ↔ 사용 관계 요청 |

Orchestrator 는 request type 기반으로 엔진에 요청을 전달한다. 모든 adapter 는 Engine Manifest 의 지원 request type 집합 안에서만 dispatch 된다.

> **AURA Unified IR 은 engine output 의 canonical representation 이며, AURA 내부에서 새로운 분석 결과를 생성하지 않는다.**

---

## 5. 외부 의존성

| 의존성 | 역할 | 라이선스 | 도입 상태 |
|--------|------|----------|----------|
| Rizin | **Primary** disasm + analyze + decompile + trace 엔진 (subprocess, bulk JSON). librz 링크 금지 — 별도 프로세스 실행만 허용. | LGPL-3.0 | ✅ Phase 2 (vendored at `third_party/rizin/`) |
| Ghidra `decompile/cpp/` 12.0.4 | **Decompile co-primary** (Rizin 과 동률, 사용자 선택). disasm/analyze/trace primary 권한 없음. | Apache 2.0 | ✅ vendored (`third_party/ghidra-decompile/`) |
| RetDec | **Secondary decompiler** — Rizin/Ghidra 결과 비교용. primary 덮어쓰기 금지. | MIT | 🟡 Phase 6 |
| Capstone ≥ 5.0 | **Disasm secondary** — 보조 disasm 뷰 / fallback. decompile 비교 대상 아님. (disasm primary 는 Rizin) | BSD-3 | ✅ |
| Qt6 | GUI | LGPL/Commercial | ✅ |
| SQLite | 프로젝트 DB (override 영속, recent 목록) | Public Domain | ✅ |
| tinyxml2 11.0.0 | Ghidra XML 파싱 | zlib | ✅ |
| libcurl ≥ 7.0 | LLM HTTP 클라이언트 | MIT/X11 | ✅ |
| cJSON | JSON 파싱 (LLM, 설정) | MIT | ✅ |
| bison / flex | Ghidra sleigh-compile 빌드 시간 의존 | GPL (build-only) | ✅ (PRD §10 사용자 §10 승인) |

**원칙**: 새 외부 의존성은 `rules.md §5` 사용자 확인 절차를 거친다.

**Rizin 라이선스 정책 (D-27)**: librz 정적/동적 링크 금지. Rizin 은 별도 프로세스로 실행한다. AURA 바이너리에 LGPL 링크 의무를 전파하지 않도록 한다. 단, Rizin 바이너리/소스를 배포하는 경우 Rizin 자체 LGPL 고지와 배포 의무는 준수한다.

### 5.1. Engine binary lookup 환경 변수 (Phase 2.5.2 — ADR-0050)

probe / orchestrator 가 외부 도구 binary 를 찾는 우선순위: **env override → vendored repo path → PATH default**. 사용자가 binary 위치를 명시 override 하려면 다음 환경 변수 사용:

| 환경 변수 | 도구 | 적용 경로 |
|----------|------|----------|
| `AURA_RIZIN_BIN` | Rizin | probe + CLI dispatch (ANALYZE/DISASM) |
| `AURA_GHIDRA_DECOMP_BIN` | ghidra-decomp | probe |
| `AURA_GHIDRA_FULL_ANALYZE_HEADLESS` | ghidra-full analyzeHeadless | probe |
| `AURA_JAVA_BIN` | Java JRE (ghidra-full 의존) | probe |
| `AURA_ANGR_PYTHON_BIN` | angr 가 import 될 Python interpreter | probe |
| `AURA_RETDEC_DECOMPILER_BIN` | RetDec retdec-decompiler | probe |
| `AURA_REPO_ROOT` | (메타) vendored tier 활성화에 필요 — repo root 가리킴 | probe (CLI 가 자동 seed) |

미설정 시 vendored (`third_party/<engine>/...`) 경로 자동 검사 → 부재 시 OS PATH fallback. 자세한 lookup 정책은 ADR-0050 참조.

---

## 6. 성공 기준

| 지표 | 목표 |
|------|------|
| Ghidra Pseudo-C fidelity | 100% (engine 출력 그대로 표시, 임의 가공 0 건) |
| Rename 전파 정확도 | 동일 SSA 정의의 모든 use-site 갱신, 타 변수 오염 0 |
| Type cascade 정확도 | caller / callee / 구조체 필드 자동 갱신, 사용자 confirm 없는 inferred 변경 0 |
| 대용량 바이너리 응답 | 500MB 파일 open → 첫 함수 디컴파일 ≤ 5s, UI 동결 0 |
| 빌드 | Linux clang/gcc 100% GREEN, ctest 0 fail |
| 다중 엔진 비교 | 같은 함수 ≥ 2 엔진 결과 동시 표시 가능 (확장 시) |

---

## 7. 디자인 원칙

1. **엔진 재구현 금지** — 디컴파일러 / 디스어셈블러 / 타입 추론 / 아키텍처별 명령어 해석은 자체 구현하지 않는다.
2. **Stateless subprocess** — 모든 엔진은 외부 프로세스, 상태는 AURA 가 보관.
3. **Output non-discard** — 엔진 출력은 모두 Unified IR 로 저장, 일부 폐기 금지.
4. **Override 불변성** — 사용자 수정은 override layer 에만 쌓이고, 엔진 출력 자체를 수정하지 않는다.
5. **Adapter 격리** — 엔진별 특성은 `src/adapter/<engine>/` 에만 존재, Orchestrator / Unified IR 은 엔진 무관.
6. **UI 분리** — UI 는 Orchestrator API 만 호출하고 엔진을 직접 spawn 하지 않는다.
7. **Engine Request 표준화** — 모든 엔진 호출은 정의된 request type (`disasm` / `analyze` / `decompile` / `trace`) 을 사용한다.
8. **Type-별 Primary 집합** — request type 마다 primary 집합을 정의: `disasm`={rizin}, `analyze`={rizin}, `decompile`={rizin, ghidra}, `trace`={rizin}. secondary engine 은 type 별 primary 집합을 덮어쓰지 못한다. decompile 의 두 primary 는 동률이며 사용자가 명시 선택한다.
9. **Engine canonical type 격리** — Rizin / Ghidra 등 엔진의 raw / canonical 자료형은 `src/adapter/<engine>/` 또는 `third_party_hub/` 내부에만 존재한다. AURA core / Unified IR / GUI 가 직접 보거나 import 하지 않는다. 정규화 허브 통과 후 AURA normalized record 만 core 로 전달.
10. **Snapshot Provenance + 1 급 record 분해** — normalized snapshot 의 모든 record 는 `{source, confidence, completeness}` provenance 를 갖는다. 함수에 타입·호출·변수 정보를 뭉개 넣지 말고 `FunctionRecord` / `BlockRecord` / `EdgeRecord` / `VariableRecord` / `TypeFactRecord` / `CallEdgeRecord` / `SymbolRecord` / `XrefRecord` 로 1 급 분해한다.

---

## 8. 범위 외 (금지)

- 자체 디컴파일러 / 디스어셈블러 / 타입 추론 / 명령어 해석 구현 ← 절대 금지
- **AURA 내부에서 CFG / IR / 타입 정보를 새로 생성하는 로직 금지**
- **엔진 출력과 불일치하는 내부 상태 생성 금지**
- 엔진 출력 임의 변형 (정정·필터링 포함)
- 사용자 confirm 없는 LLM 결과 자동 적용
- AURA 코어 로직을 인터프리터 언어 (Python / JavaScript / Java) 로 작성 — LLM 클라이언트도 C/C++. **단 외부 도구 (Ghidra 등) 가 요구하는 자체 런타임은 허용** (2026-05-02 정책 갱신, `rules.md §1`). 런타임 부재 시 "사용 불가" + 이유 + 설치 안내 노출 의무.
- 실시간 다중 사용자 협업 (별도 product)
- 동적 디버거 통합 (Phase 외)

---

## 9. Open Decisions

| # | 결정 사항 | 상태 | 비고 |
|---|-----------|------|------|
| D-1 | Rizin adapter 도입 시점 | ✅ 결정 (2026-04-30) | **Phase 2 부터** Rizin = `disasm`/`analyze`/`decompile`/`trace` primary, Ghidra = `decompile` co-primary. Phase 2 를 2A (Rizin analyze) / 2B (Rizin decompile) / 2C (Ghidra decompile co-primary) 로 분리. |
| D-2 | Override layer 직렬화 포맷 (SQLite row vs JSON blob) | ✅ 결정 (2026-05-01) | **SQLite row-oriented** — override 를 독립 row 로 저장. JSON blob 방식 대비 개별 조회·수정·충돌 관리가 용이. Phase 4B 에서 schema 구현. |
| D-3 | 다중 엔진 결과 vote / 우선순위 규칙 | 🔴 미결 | Phase 7 시작 시 |
| D-4 | LLM 런타임 default | ✅ 결정 | LM Studio (`http://localhost:1234/v1`, `qwen/qwen3-coder-next`). OpenAI 호환 API 교체 가능 |
| D-5 | 캐시 위치 | ✅ 결정 | `~/.cache/aura/` (XDG) |
| D-6 | GUI 프레임워크 | ✅ 결정 | Qt6 |
| D-7 | DB 엔진 | ✅ 결정 | SQLite (project-local `.aura.db`) |
| D-27 | Rizin subprocess-only / no librz | ✅ 결정 (2026-04-30) | librz 정적/동적 링크 금지. Rizin 은 별도 프로세스로 실행. AURA 바이너리에 LGPL 링크 의무를 전파하지 않도록 한다. 단, Rizin 바이너리/소스를 배포하는 경우 Rizin 자체 LGPL 고지·배포 의무는 준수. IPC 는 stateless subprocess + bulk JSON extraction. stdout 에 command 별 **명시 BEGIN/END delimiter framing**: `===AURA-BEGIN:<id>===` … `===AURA-END:<id>===`. empty body 허용 (aaa 같이 출력 없는 command). delimiter pair 누락·id 불일치·중첩은 reject. |
| D-28 | Decompile co-primary 사용자 선택 정책 | 🟡 권고안 | `decompile` request 시 engine_id 미지정 → 사용자 default (settings 의 `decompile.preferred_engine`, 초기값 = `rizin`). 명시 지정 시 그대로 dispatch. Phase 5 GUI 에서 엔진 선택 드롭다운 노출. |
| D-29 | `AURA_ENABLE_RIZIN_HUB` default 정책 | ✅ 결정 (2026-05-01) | **조건부 default**: `AURA_ENABLE_RIZIN=OFF` 빌드 시 hub 도 OFF (분석 비활성화 빌드의 크기를 늘리지 않음). `AURA_ENABLE_RIZIN=ON` 빌드 시 hub 기본 ON (어댑터의 정규화 record 경로 자동 활성화). 사용자가 명시적으로 `-DAURA_ENABLE_RIZIN_HUB=OFF` 를 지정하면 그 값이 우선 (CMake `option()` 이 cache 값을 보존). 전역 default ON 으로 전환하지 않은 이유: hub 가 Rizin adapter 의존이라 Rizin 미활성 시 죽은 코드가 됨. Phase 2A/2B/2C e2e GREEN (2026-05-01 Session #27) 으로 trigger 충족, 전환 정책 결정 완료. |
| D-30 | Tier-based Platform Support Policy | ✅ 결정 (2026-05-03) | 3-Tier 정책: **Tier 1** = Linux WSL (Ubuntu 24.04) + Windows MSVC (latest stable). 매 PR ctest GREEN 의무. **Tier 3** = macOS, best-effort/unverified, Mac 하드웨어/CI 확보 후 승급 예정. Tier 2 (CI-verified e2e exempt) 는 보류. 상세 근거 + 대안 + 결과: `docs/adr/0030-tier-platform-policy.md`. 실행 작업: Phase 9 (`.scratch/platform-coverage/`). |
| D-31 | Real subprocess `AuraCommandRunner` (POSIX + Windows) | ✅ 결정 (2026-05-05) | abstract `command_runner.h` 위에 production backend 도입. POSIX = pipe + fork + execvp + poll-based deadline drain (100ms poll cap + 64-iter drain cap). Windows = CreatePipe + CreateProcess + per-pipe reader thread. Codex 5-round adversarial review APPROVE. 상세: `docs/adr/0049-subprocess-command-runner.md`. |
| D-32 | Probe binary lookup contract (env → vendored → PATH) | ✅ 결정 (2026-05-05) | 5 probe 모두 단일 헬퍼 `aura_probe_resolve_binary` 사용. 3-tier 우선순위 + 5 신규 env vars (§5.1 표). install_hint ↔ probe 자기-일관성 강제 (rules.md §1). 상세: `docs/adr/0050-probe-binary-lookup-contract.md`. |
| D-33 | Phase 번호 재배정 (plan 11.5-12 → 12.1-13) | ✅ 결정 (2026-05-05) | 옛 plan 11.5/11.6 = 코드베이스 11.5 (P5 polish ✅ landed) / 11.6 (Disasm flow gutter ✅ landed) 와 충돌 → 옛 11.5~11.10 → **Phase 12 묶음 (12.1~12.6)** "External Engine Session & Cache Layer" / 옛 12 → **Phase 13** "LLM Context Provider". 옛 phase 번호 재사용 영구 금지. 상세: `docs/adr/0051-phase-number-renumber.md`. |
| D-34 | Symbolic request type policy | ✅ 결정 (2026-05-06) | AURA 는 `symbolic` request type 을 허용한다. `symbolic` primary 는 `{angr}` 이며 AURA 는 symbolic execution 을 자체 구현하지 않는다. angr 는 외부 subprocess / runner 로만 실행되고, AURA 는 raw output 보존, normalized mapping, UI 표시만 수행한다. angr 부재 또는 실패 시 secondary/fallback 으로 대체하지 않는다. `aura_angr_runner.py` 는 외부 도구 runner 로 간주하며 AURA core 로직이 아니다. 실제 코드 계약(`include/engine_request.h` enum/mask, manifest validation, orchestrator primary set)은 Phase 7.1 구현에서 갱신한다. |
| D-35 | Type propagation DB apply path | ✅ 결정 (2026-05-06) | 타입 전파 수정/후속 기능을 위해 DB 개선을 허가한다. 범위는 분석 결과 전체 캐시 또는 후보 캐시 신설이 아니라, 사용자가 명시 Apply 한 후보만 기존 SQLite `override_store` 의 `AURA_OVERRIDE_PAYLOAD_TYPE` row 로 저장하는 것이다. CLI 계약: `propagate-type --apply` 는 `--all` 또는 `--candidate-ids` 와 `--project`/`$AURA_PROJECT` 가 있을 때만 store write. 상세: `docs/adr/0045-pp1-type-propagation.md` D6. |
| D-36 | Multi-decompiler serving final target | ✅ 방향 결정 (2026-05-06) | 최종 제품은 Rizin/rz-ghidra, Ghidra, RetDec 등 복수 decompiler 결과를 같은 함수 단위로 요청·보존·표시할 수 있어야 한다. 현재 0.8.0 Rizin/rz-ghidra 는 시연 가능한 단일 기준일 뿐 최종 범위 축소가 아니다. 결과 merge/vote/자동 정정은 금지하며, compare 는 display-only side-by-side/tabbed 계층에서 수행한다. 구체 CLI flag, GUI layout, cache schema, RetDec/Ghidra PrettyPrint 도입 방식은 구현 phase 진입 시 별도 ADR 로 확정한다. |
| D-37 | GUI IPC + MCP execution split | ✅ 결정 (2026-05-06) | `aura-gui` 는 opt-in localhost RPC server 를 제공하고, `aura gui ...` 는 나중에 실행되어 현재 GUI 에 접속하는 client mode 로 동작한다. MCP 는 GUI 에 내장하지 않고 별도 `aura-mcp` gateway 로 둔다. Gateway 는 LLM/agent 요청을 allowlist/policy/audit 후 GUI IPC 또는 headless engine API 로 전달한다. |
| D-38 | GUI browser presentation policy | ✅ 결정 (2026-05-06) | Functions/Xrefs/Symbols/Imports/Strings 는 Cutter-style `QTreeView` 로 표현한다. GUI 는 엔진 record 의 display layer 이므로 없는 metadata 를 0, false, unknown 등으로 추론하지 않고 `-` 로 둔다. |
| D-39 | Single LLM + Token Classification/Rule privacy filter gateway policy | ✅ 결정 (2026-05-06, 용어 갱신 2026-05-07) | 제품 기본 구조는 2개 생성형 LLM 상시 배치가 아니라 **1개 생성형 LLM + Token Classification Model/Rule Pack 기반 Privacy Filter & Policy Gateway**다. `aura-mcp` 는 생성형 모델이 아니라 policy gateway 이며, 문자열 기반 MVP 에서 시작해 token classification 탐지, 정규식 rule pack, eval dataset 기반 평가를 결합한 민감정보 마스킹 시스템으로 확장한다. 보조 verifier 모델은 기본 아키텍처에서 제외하고, 별도 연구/옵션 phase 승인 없이는 요구사항으로 두지 않는다. |
| D-40 | Full disassembly continuous listing policy | ✅ 결정 (2026-05-06) | 전체 디스어셈블리는 Cutter처럼 연속 VA listing 으로 표시하고 함수 목록 선택 시 해당 주소로 스크롤한다. 함수 단위 `pdfj/pdf` 뷰는 기존대로 유지한다. Full Disassembly 는 `pdj <count>` structured record 와 bounded `pD 4096` arrow text 를 함께 반환하고, `Structured` 탭은 `pD` mixed listing 을 분류해 invalid/data/comment/label 줄도 보존한다. Rizin 0.8.0 `pD` 는 작은 EXE 에서도 8KB+ 범위가 timeout 될 수 있으므로 arrow text 는 4KB hard cap 으로 둔다. Chunk cache / lazy paging 은 아직 미구현이며, Cutter급 스크롤 효율은 후속 phase 범위다. |
| D-41 | String alias vs mask token persistence | ✅ 결정 (2026-05-07) | 문자열 보호에서 **String Alias**(사용자 의미 별칭) 와 **Mask Token**(외부 전달 안전 토큰) 은 분리한다. GUI 는 둘을 함께 표시할 수 있지만 MCP/외부 LLM 전달은 mask token 우선이다. 1차 DB 기준은 `analysis_strings`, `string_overrides`, `string_protection_findings` 세 테이블이며, `string_references`, render cache, export audit 은 후속 확장이다. 상세: `docs/adr/0053-string-protection-db.md`. |
| D-42 | Safety filter runtime asset registry | ✅ 결정 (2026-05-07) | 민감 문자열 탐지 모델은 **Token Classification Model** 로 부르고, 기본 후보는 `openai/privacy-filter` 다. 큰 모델 가중치와 교체 가능한 평가 데이터셋은 `third_party/` 나 Git 저장소가 아니라 사용자 홈의 `~/.aura/token-classification-models/`, `~/.aura/eval-datasets/` 에 둔다. 정규식/후처리 묶음은 **Rule Pack** 이며, Rule Pack 은 모델/탐지결과가 아니라 정규식, 후처리 조건, confidence 기준, allowlist/denylist, 테스트 샘플을 담은 규칙 데이터다. **Rule Finding** 은 Rule Pack Engine 실행 결과이고 **Model Finding** 은 Token Classification Model 실행 결과이며, 둘 다 원본 문자열을 직접 바꾸지 않는다. **Finding Merger** 는 두 finding 계층을 병합해 최종 후보 목록을 만들고, **Mask Token Allocator** 는 label-numbered/same-value-same-mask 정책으로 mask token 을 부여한다. 실제 치환은 Protected String View 생성 시 수행한다. **Eval Dataset** 은 학습용 데이터가 아니라 모델만/rule pack만/model+rule 결합의 탐지율, 오탐률, 마스킹 일관성을 검증하는 테스트셋이다. 모델/룰/데이터셋/마스킹 정책 조합은 **Safety Profile** 로 관리한다. Safety Profile 은 탐지 로직이 아니라 configuration 이며, loader 는 schema 검증과 runtime asset 경로 resolve 까지만 책임진다. 상세: `docs/adr/0054-safety-filter-runtime-assets.md`. |
| D-43 | Strings protection UI placement | ✅ 결정 (2026-05-07) | 문자열 보호 v1 UI 는 별도 Safety 탭이 아니라 기존 `Strings` 탭에 귀속한다. parent row 는 문자열 엔티티와 보호 상태/Mask Token 요약을 보여주고, 보호 child row 는 최하단에 `기존`/`별칭`/`마스킹` 순서로 둔다. 원문을 담는 `기존` row 는 기본 숨김이며 민감정보 상세 표시 설정이 켜진 경우에만 노출한다. 상세: `docs/adr/0055-strings-protection-ui.md`. |
| D-44 | Safety core module layout | ✅ 결정 (2026-05-07) | Privacy Filter 공용 로직은 GUI 가 아니라 core module 로 둔다. Public API 는 `include/aura/safety/`, 구현은 `src/core/safety/` 아래에 두며, `safety_profile`, `rule_pack`, `finding`, `finding_merger`, `mask_token_allocator` 모듈로 시작한다. GUI 는 표시/사용자 입력만 담당하고, CLI/GUI/향후 `aura-mcp` 는 같은 core safety API 를 재사용한다. 상세: `docs/adr/0056-safety-core-module-layout.md`. |
| D-45 | Safety detection pipeline implementation order | ✅ 결정 (2026-05-07) | 최종 실행 구조는 원본 문자열을 Rule Pack Engine 과 Token Classification Model Adapter 가 각각 검사한 뒤 Rule Finding + Model Finding 을 Finding Merger 에서 병합하고 Mask Token Allocator 로 넘긴다. 모델은 마스킹된 문자열이 아니라 원본 문자열을 검사한다. 구현 순서는 Rule Pack 경로를 먼저 완성하지만, Token Classification Model Adapter 도 Phase 13 의 같은 목표 구현 대상이다. |
| D-46 | Strict MCP Coverage | ✅ 결정 (2026-05-07) | 새 분석 도구, 분석 데이터, 자동화 명령, export 기능이 추가되면 `aura-mcp` surface 도 반드시 함께 추가/수정한다. MCP 반영이 없으면 해당 작업은 완료가 아니라 GUI/CLI 선행 구현 또는 MCP Pending 으로 본다. MCP 는 GUI 화면 단위가 아니라 Unified Model record + Safety Core export-safe view 기준으로 노출한다. 순수 GUI polish 는 분석 데이터나 자동화 계약을 바꾸지 않는 한 제외한다. 상세: `docs/adr/0057-strict-mcp-coverage.md`. |
| D-47 | MCP raw access policy | ✅ 결정 (2026-05-07) | MCP 기본 tool 은 원문을 반환하지 않는 Protected MCP Tool 이다. 원문 문자열/code text 접근은 별도 Privileged MCP Tool 로 분리하고, raw-access session toggle, 요청별 사용자 확인, bounded scope, Raw Disclosure Event audit log 를 모두 요구한다. audit log 는 원문 값을 저장하지 않는다. 상세: `docs/adr/0057-strict-mcp-coverage.md`. |
| D-48 | MCP schema stability and engine-agnostic records | ✅ 결정 (2026-05-07) | MCP 응답은 `mcp_schema_version`, `tool_schema_version`, `kind`, `status`, `data`, `warnings`, `disclosure` 를 포함하는 공통 envelope 을 사용한다. 기본 record 는 engine-neutral field 만 가지며, Rizin/Ghidra/x64dbg/angr/RetDec 등 engine/model 별 추가 정보는 `extensions.<engine_id>` 또는 raw artifact reference 로 격리한다. 기존 field 삭제/이름 변경/타입 변경/의미 변경은 breaking change 로 보고 major schema version bump 없이는 금지한다. 상세: `docs/adr/0057-strict-mcp-coverage.md`. |
| D-49 | MCP Security Regression Gate | ✅ 결정 (2026-05-07) | MCP 관련 기능은 smoke test 만으로 완료할 수 없다. Schema/Error envelope, protected default, raw non-disclosure, privileged raw denial, per-request approval, bounded scope, raw disclosure audit, engine-agnostic schema, compatibility 테스트를 통과해야 feature complete 로 본다. 첫 slice 에서 raw 성공 경로를 만들지 않더라도 protected non-disclosure 와 privileged denial/error path 는 먼저 검증한다. 상세: `docs/adr/0057-strict-mcp-coverage.md`. |
| D-50 | Python venv PII runner + runtime safety asset registry | ✅ 결정 (2026-05-07) | Rule Pack, Eval Dataset, Token Classification Model 은 모두 `<asset-id>/manifest.json` 기반 runtime asset registry 로 관리한다. 사용자 자산은 `~/.aura/`, repo 기본 소형 자산은 `assets/safety/` 에 두며 `third_party/` 에 모델/데이터셋/Rule Pack 을 넣지 않는다. 초기 Token Classification Model Adapter 는 Python venv 기반 외부 CLI runner subprocess 로 구현하고, AURA core 는 Python/transformers/ONNX Runtime 을 embed/link 하지 않는다. runner 는 로컬 JSON protocol 로 Model Finding 을 반환한다. 상세: `docs/adr/0058-python-pii-runner-runtime-registry.md`. |

> 상태 범례: 🔴 미결 (사용자 결정 필요) | 🟡 권고안 있음 | ✅ 결정됨

---

## 10. 거버넌스

- 본 PRD 가 Tasks.md / rules.md / 코드 결정에 우선한다.
- 본 PRD 는 제품 정체성, 범위, 외부 의존성, Open Decision 에 대한 최상위 권위다.
- AI 행동 규칙과 멈춤 조건은 rules.md 를 따르며, 라이브 진행 상태는 AUTOMATION_ROADMAP.md 가 Tasks.md 보다 우선한다.
- 새 기능·새 의존성·새 엔진 어댑터·새 request type 도입은 PRD §9 에 신규 D 결정으로 등재 후 승인.
- v2.x (custom build) 이력은 `legacy/` 디렉토리에 격리됨. 본 PRD 는 v1.0 (orchestrator pivot) baseline.
