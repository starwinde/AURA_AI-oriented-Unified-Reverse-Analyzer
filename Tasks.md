# AURA Tasks — Multi-Engine Orchestrator Roadmap

> 본 문서는 [PRD.md](./PRD.md) 의 §1 정체성 + §4 시스템 구조 + §7 디자인 원칙에 기반한 페이즈 로드맵이다.
> AURA = **격리형 멀티 엔진 오케스트레이터** (disasm / analyze / decompile 전부 외부 엔진).
> AURA 본체는 엔진 결과를 **ingest / transform / display** 만 한다. 자체 분석을 수행하지 않는다 (rules R-1).
> v2.x (custom build) 이력은 `legacy/` 에 격리됨.

---

## 엔진 분류

본 로드맵의 모든 엔진은 아래 3 종 중 하나로 분류된다. 각 엔진은 **외부 subprocess** 로 실행되며, AURA 는 결과를 통합·중계·표시할 뿐 자체 구현하지 않는다 (rules R-1).

| 종류 | 역할 | 후보 |
|------|------|------|
| Disassembler Engine | 명령어 디스어셈블 | **Rizin (primary)**, Capstone (secondary / fallback) |
| Analysis Engine | 함수·심볼·CFG·타입 추출 | **Rizin (primary)** |
| Decompiler Engine | Pseudo-C 생성 | **Rizin (co-primary)**, **Ghidra (co-primary)**, RetDec (secondary) |
| Trace Engine | 정의 ↔ 사용 관계 | **Rizin (primary)** |

- **Rizin** = `disasm` / `analyze` / `decompile` / `trace` **primary** (Phase 2 active). subprocess + bulk JSON, librz 링크 금지 (D-27).
- **Ghidra** = `decompile` **co-primary** (Rizin 과 동률, 사용자 선택). disasm/analyze/trace primary 권한 없음.
- **RetDec** = secondary decompiler — primary 결과 비교/보조 (Phase 6).
- **Capstone** = `disasm` secondary / fallback. Decompile 비교 대상 아님.

---

## 진행 상태

### Active phases (현재 활성 / 완료된 phase 만)

| Phase | 제목 | 상태 |
|-------|------|------|
| 1 | Engine Adapter Contract / Orchestrator Layer | `[x]` 완료 |
| 2 | **Primary Engine (Rizin) Adapter — Analyze + Decompile** | `[x]` 완료 |
| 2A | Rizin Analyze Primary | `[x]` 완료 |
| 2B | Rizin Decompile Primary | `[x]` 완료 |
| 2C | Ghidra Decompile Co-primary (이관) | `[x]` 완료 |
| **2.5** | **Probe / Bootstrap / Consent + production wiring** | `[x]` 완료 (2026-05-05). 코어 (Slices 1-60) + closeout 2.5.1 (X.1-X.7, subprocess runner + `aura --probe-engines` CLI + deadlock 가드) + lookup contract 2.5.2 (X.8-X.8.2, env→vendored→PATH 5 env vars) + build infra (MSVC `/FI` 한글 경로 fix). Codex 5-round adversarial review APPROVE. **99 cases / 5 ctest suites GREEN, 양 OS (Windows MSVC + Linux WSL)**. 머지 commit `65440808`. §1.6 동시성 primitives → Phase 11.5 SessionManager. |
| 3 | Unified Model Ingestion | `[x]` 완료 (3A·3B·3C·3D·3E·3F 완료 — 2026-05-01. 3C = IR Artifact Ingestion 재정의 후 완료; pseudo-C view = 3C2 backlog Phase 4+ 로 분리.) |
| 4 | Override Layer | `[x]` 완료 (4A·4B·4C·4D / 4E.1 모두 `[x]`. 4E.2 → Phase 11.x 흡수). |
| **9** | **Platform Coverage (Windows MSVC + Linux Tier 1)** | `[-]` 진행 중 (2026-05-03 시작 — 10 issue 중 7 closed, 09/10 사용자 결정 대기) |
| **10** | **Legacy strip + orchestrator_smoke gate** | `[x]` 완료 (commits `0483147f`..`0070b985`) |
| **11.1** | **CLI v1 — `analyze` / `info` / `llm-context`** | `[x]` 완료 (commits `c6596be1`..`e61fa879`) |
| 11.2 | LLM 통합 e2e cookbook | `[-]` 진행 중. 기존 LM Studio/qwen transcript 는 과거 단일 LLM 호출 검증으로 보존하되, 현재 Phase 13 기준 Privacy Filter/MCP/Token Classification/Rule Pack end-to-end cookbook 은 미완. GUI IPC 자동화 경로는 검증 완료이며, 마스킹/LLM payload e2e 는 Phase 13 에서 진행. |
| **11.3** | **GUI v1 — Cutter-style workspace + 8 docks** | `[x]` 완료 (11.3.1~11.3.10 모두). 2026-05-06 local polish: 기본 배치를 좌측 Functions/Xrefs + Strings/Symbols/Imports, 우측 Decompile/Disassembly/Full Disassembly/CFG/Hex 로 정리하고, 5개 브라우저를 Cutter-style tree 표현으로 통일. `Ctrl+F` 는 마지막 활성 패널 기준 검색으로 확장. Full Disassembly 는 연속 listing + 함수 선택 스크롤 방식. 2026-05-07: Decompile / Disassembly / Full Disassembly 코드 pane 에 기본 syntax highlighting 추가(address, mnemonic, register, number, string, comment, invalid). |
| **11.4** | **Override CLI + PP1~PP4 (display-only)** | `[x]` 완료 (11.4.1~11.4.5) |
| **11.4.3-v2** | **PP1 store wire — Type propagation DB apply** | `[x]` 완료 (2026-05-06, D-35 승인). 기존 ROADMAP 의 “PP1 v2 store wire” 후속 phase 를 닫음. Scope: `propagate-type --apply --all/--candidate-ids --project` 가 선택된 candidate 를 기존 SQLite `override_store` 의 TYPE payload row 로 저장. 분석 결과 전체 DB 캐시 / candidate cache 테이블 신설은 범위 밖. |
| **11.5** | **P5 polish suite — keyboard / navigation / shortcuts** | `[x]` 완료 (8 features) |
| **11.6** | **Disasm flow arrow gutter (Cutter-style)** | `[x]` 완료 (ADR-0048) |
| **2D** | **Ghidra full opt-in vendoring** (third_party/ghidra-full + AuraDaemon.java + bootstrap script) | `[ ]` planned (Plan §2.1, ADR-0049/0050 후속) |
| **7.1** | **angr `symbolic` request type 신설** | `[ ]` planned (Plan §2.2, D-34 승인 완료). Scope: angr 외부 runner/subprocess 결과 수집 전용. AURA 내부 symbolic execution 구현 금지. 첫 구현에서 `include/engine_request.h` enum/mask + manifest validation + orchestrator primary `{angr}` 갱신 필요. **주의**: 옛 Phase 7.1 (Decompile compare) ≠ 신 Phase 7.1 (angr symbolic). 매핑은 [Tasks_deferred.md](./Tasks_deferred.md) 참조. |
| **12** | **External Engine Session & Cache Layer** (묶음, 6 sub) | `[ ]` planned (Plan §3-§5, ADR-0051 phase 번호 재배정) |
| 12.1 | SessionManager (RAII + refcount + pending_jobs + idle timer + LRU + semi-persistent 한계) | `[ ]` planned (옛 Plan 11.5) |
| 12.2 | Rizin r2pipe persistent session adapter | `[ ]` planned (옛 Plan 11.6) |
| 12.3 | Ghidra full + AuraDaemon.java + progressive readiness | `[ ]` planned (옛 Plan 11.7, Phase 2D 의존) |
| 12.4 | DB 캐시 (analysis_hash + 2-source merge + field-level type) + invalidation | `[ ]` planned (옛 Plan 11.8) |
| 12.5 | dependents() with confidence pruning + expansion cap | `[ ]` planned (옛 Plan 11.9) |
| 12.6 | integrity check + crash recovery | `[ ]` planned (옛 Plan 11.10) |
| **13** | **LLM Context Provider** (single generative LLM + Token Classification/Rule Privacy Filter & Policy Gateway + external MCP/IPC) | `[-]` 진행 중. 2026-05-06: GUI IPC attach path 착수 — `aura-gui --rpc-port` + `aura gui ...` client mode 로 live GUI 제어 가능. MCP 는 별도 `aura-mcp` gateway 로 계획 유지. 기본 구조는 2개 생성형 LLM 상시 배치가 아니라 1개 생성형 LLM + Token Classification Model(`openai/privacy-filter` 기본 후보) + 한국형/Secret Rule Pack + Eval Dataset 기반 평가 + policy gateway. 현재 구현 기준은 문자열 기반 마스킹 MVP. 2026-05-07: 문자열 보호 DB 1차 기준 승인 — String Alias 와 Mask Token 을 분리하고 `analysis_strings`, `string_overrides`, `string_protection_findings` 세 테이블로 시작한다(ADR-0053). 2026-05-07: runtime asset registry 승인 — 큰 모델/데이터셋은 `third_party/` 가 아니라 `~/.aura/token-classification-models/`, `~/.aura/eval-datasets/` 에 두고 Rule Pack/Safety Profile 을 분리한다(ADR-0054). 2026-05-07: Strings protection UI 승인 — 별도 Safety 탭 대신 Strings 탭 최하단 child row 에 `기존`/`별칭`/`마스킹` 을 두고 원문은 기본 숨김(ADR-0055). 2026-05-07: Safety core module layout 승인 — `include/aura/safety/` + `src/core/safety/`, GUI 는 표시만 담당(ADR-0056). 2026-05-07: Strict MCP Coverage 승인 — 새 분석 도구/데이터/자동화/export 기능은 `aura-mcp` surface 까지 함께 갱신되어야 완료이며, MCP 는 GUI 화면이 아니라 Unified Model + Safety Core export-safe view 기준으로 정의한다(ADR-0057). 2026-05-07: MCP raw access policy 승인 — MCP 기본 tool 은 Protected MCP Tool 이며, 원문 접근은 raw-access session toggle + 요청별 확인 + bounded scope + Raw Disclosure Event audit 가 필요한 Privileged MCP Tool 로만 허용한다(D-47). 2026-05-07: MCP schema stability 승인 — 공통 MCP Schema Envelope 과 Engine-Agnostic Record Contract 를 사용해 engine/model 변경 시 base struct/schema 변경을 피하고 engine 별 차이는 extension/raw artifact boundary 로 격리한다(D-48). 2026-05-07: MCP Security Regression Gate 승인 — MCP 기능은 smoke test 만으로 완료하지 않고 schema/error envelope, protected default, raw non-disclosure, privileged denial, approval, bounded scope, audit, engine-agnostic schema, compatibility 를 검증한다(D-49). 최종 pipeline 은 Rule Pack Engine + Token Classification Model Adapter 가 원본 문자열을 각각 검사한 뒤 병합하며, 구현 순서는 Rule Pack 우선이지만 모델 어댑터도 Phase 13 목표 구현 대상이다(D-45). string_references, render cache, export audit 은 후속 확장. 옛 Plan 12 = 신 Phase 13. |

### Phase 13 remaining slices

- [x] 13.0a GUI IPC attach path — `aura-gui --rpc-port` + `aura gui ...` live GUI control.
- [-] 13.1 String Safety Core MVP — Rule Pack 우선 탐지, Mask Token allocation, Protected String View, 문자열 보호 DB/GUI/CLI 선행 구현. Strict MCP Coverage 기준으로는 `aura-mcp` surface 전까지 MCP Pending.
- [ ] 13.2 MCP schema contract — MCP Schema Envelope, Protected MCP Tool error/success envelope, `strings.list` / `strings.get` protected payload schema 확정 및 test fixture 작성.
- [ ] 13.3 `aura-mcp` skeleton — 별도 gateway executable, project DB 또는 Headless Engine API 기반 protected strings read path, GUI IPC 는 live GUI state 가 필요한 경우에만 사용.
- [ ] 13.4 MCP Security Regression Gate — schema/error envelope, protected default, raw non-disclosure, privileged denial, per-request approval denial, bounded scope denial, audit metadata no-raw, engine-agnostic schema, compatibility tests.
- [ ] 13.5 Raw access control — Raw-Access Session Toggle, Per-Request Approval, Approval ID, Bounded Scope enforcement, Raw Disclosure Event persistence. 저장 위치(project DB vs `~/.aura/audit/`)는 구현 전 별도 ADR 로 확정한다. 첫 구현은 denial/error path 우선, raw success path 는 별도 승인 후.
- [-] 13.6 Token Classification Model Adapter — Python venv 기반 외부 CLI runner 를 초기 표준으로 채택(ADR-0058). `~/.aura/token-classification-models/` runtime asset resolve, model finding interface, Rule Finding + Model Finding merger integration 진행 중. 현재 완료: legacy dummy runner smoke, Safety Profile `model_policy` schema, runtime asset registry skeleton, 세부 설계 확정(offset_unit=`utf8_byte`, batch scan API, AURA-managed `pii-python-venv`, explicit bootstrap, Model Finding Normalizer, Standard Finding Kind Vocabulary). 남은 구현: 13.6a runner protocol v1 gate(dummy runner 도 `offset_unit=utf8_byte` request/response + 한국어 UTF-8 byte offset test + error output `request_id` 유지 + `mode`→`backend` migration), 13.6b manifest v1 validator, 13.6c runner env bootstrap/check + problem/cause/fix CLI error UX, 13.6d C++ batch adapter + subprocess timeout/error mapping + runner 내부 error 를 canonical `error_code` 로 매핑 + `max_input_chars` 초과 시 silent truncate 금지/`input_too_large` 정책 테스트(default degrade warning, high-security block_export) + Safety warning/policy result 를 `AuraDiagnostics` 와 분리, 13.6e `transformers_token_classification` backend + normalizer, 13.6f Rule+Model merger integration tests.
- [ ] 13.7 Eval Dataset harness — `~/.aura/eval-datasets/` 기반 탐지율/오탐률/마스킹 일관성 평가.
- [ ] 13.8 Protected decompile/disassembly export — 문자열 보호값을 decompile/disassembly MCP payload 에 반영하는 render/cache 정책. `string_references` / render cache 필요 여부를 별도 ADR 로 확정.
- [ ] 13.9 LLM/MCP e2e cookbook — protected strings payload, 원문 미노출 증거, privileged denial 증거, audit metadata 증거를 포함한 중간/최종 시연 자료.

상태 기호: `[ ]` 미시작 / `[-]` 구현 중 / `[x]` 완료

> **라이브 상세 진행**: [`AUTOMATION_ROADMAP.md`](./AUTOMATION_ROADMAP.md) 우선 (rules.md §11.1).
> **다음 세션 진입점**: [`AUTOMATION_ROADMAP.md`](./AUTOMATION_ROADMAP.md) §"다음 세션 백로그".

### Deferred / Scrapped (옛 Phase 5/6/7/8)

2026-05-03 외부 도구 오케스트레이션 pivot 으로 무효화되거나 보류된 phase 항목은 별도 문서에서 관리:

> **[Tasks_deferred.md](./Tasks_deferred.md)** — Phase 5 (🔄 reborn → 11.3~11.6) / Phase 6 (⏸️ deferred) / Phase 7 (⏸️ deferred, 7.1 만 살아남음) / Phase 8 (⏸️ deferred, mmap = D-6 완료)

---

## Phase 1 — Engine Adapter Contract / Orchestrator Layer  `[x]`

**목표**: 모든 외부 엔진 (disasm / analyze / decompile) 을 동일한 추상 위에 띄울 수 있는 **어댑터 계약** 과 **오케스트레이터 골격** 을 정의한다. 본 페이즈 산출물은 엔진 무관 (engine-agnostic). 특정 엔진의 구체 구현은 Phase 2 에서 시작.

- [x] 1.1 Subprocess 실행 추상 — `spawn` / `stdin·stdout·stderr` / `wait` / `kill`. 엔진 공용 primitive. *(`include/engine_subprocess.h` + `src/core/engine_subprocess.c` extracted; `ghidra_subprocess.c` migrated to delegate spawn/drain/timeout/wait through the shared primitive — only argv composition + Ghidra exit-code mapping remain engine-specific)*
- [x] 1.2 **Request Types 정의** — 모든 adapter 는 동일한 request 타입을 기준으로 동작한다. *(`include/engine_request.h:44-49` `AuraEngineRequestType` + R-7 마스크 line 53-57)*
    - `disasm` — 명령어 단위 디스어셈블 결과 요청.
    - `analyze` — 함수·심볼·CFG·타입 등 정적 분석 결과 요청.
    - `decompile` — Pseudo-C 결과 요청.
    - `trace` *(optional)* — 엔진이 제공하는 정의 ↔ 사용 관계 요청.
- [x] 1.3 IPC schema 정의 — request 본체는 **반드시 request type 필드를 포함** + 엔진별 payload 슬롯. response 는 type 별 normalize 된 본체 + 엔진 원시 응답 보존. *(`engine_request.h:80-113` — `AuraEngineRequest.type` 필수, `AuraEngineResponse` = body + raw)*
- [x] 1.4 Engine Manifest — 엔진 식별자 + 지원 request type 집합 + 실행 경로 + 버전 + capability flags. *(`include/engine_manifest.h:34-41` + `src/core/engine_manifest.c:23-39` validate)*
- [x] 1.5 Adapter 인터페이스 — `adapter_init` / `adapter_request` / `adapter_shutdown`. Orchestrator 가 호출하는 단일 진입점. request type 기반 dispatch. *(`engine_request.h:138-144` `AuraEngineAdapter` vtable)*
- [x] 1.6 Orchestrator Layer — UI ↔ Adapter 중계, 엔진 선택 / 라우팅, 결과 fan-in. *(`include/orchestrator.h` + `src/core/orchestrator.c` create/destroy/register/dispatch, type 기반 라우팅 line 119-139)*
- [x] 1.7 Error / Timeout / Crash isolation — 한 엔진 실패가 AURA 본체 또는 다른 엔진에 전파되지 않음. *(subprocess-level 격리는 `engine_subprocess` (SIGTERM→1s grace→SIGKILL); adapter status mapping `ghidra_status_to_engine`; orchestrator R-7 type guard + per-slot diagnostic counters; `tests/orchestrator/test_orchestrator_dispatch.c::case_isolation` proves cross-engine non-propagation + invalid-type reject)*
- [x] 1.8 Source-of-truth 규칙 — **엔진 결과 우선**, AURA 측 임의 변형·정정·필터링 금지 (rules R-4). *(`engine_request.h:97-103` 명문화 + `src/adapter/ghidra/ghidra_adapter.c:128-138` raw XML 무가공 detach)*

참조: PRD §4, §7, rules R-1~R-6

---

## Phase 2 — Primary Engine (Rizin) Adapter — Analyze + Decompile  `[x]`

> **Status (2026-05-01 Session #27)**: 2A / 2B / 2C 모두 완료. ctest -L "rizin|orchestrator" 23/23 GREEN (rizin on PATH). Phase 3 진입 준비됨. 상세는 각 sub-phase status 노트 + `Phase 2 재점검 로그` 참조.

**목표**: Phase 1 어댑터 계약 위에 Rizin 을 primary engine 으로 결합한 첫 구체 구현. Ghidra 는 decompile co-primary 로 보존.
**참조**: `docs/design/d_rizin_skeleton.md` (신규), `docs/design/third_party_hub.md`

### Phase 2A — Rizin Analyze Primary  `[x]`

> **Status (2026-05-01 Session #27 close-out)**
> 2A.1–2A.11 verified. Linux WSL e2e GREEN: `aura --engine=rizin --analyze
> tests/fixtures/stripped_nucleus.elf` → 26 functions / 9 symbols / exit 0.
> Linux ctest 18/18 GREEN (rizin 9 + orchestrator 9, e2e skipped without rizin in PATH).
> macOS 검증 환경 미제공 (사용자 결정 2026-04-30 유지).
>
> **Windows MSVC 인프라 결함 (Phase 2A 범위 외, 별도 작업으로 분리)**:
>   - YARA `sys/mman.h` 기존에 알려짐. Windows MSVC 디폴트 OFF 로 우회 (`AURA_BUILD_YARA`).
>   - 추가 발견: GCC 전용 `__attribute__((aligned(64)))` (file_format.h),
>     `unistd.h` 직접 include (decompile_metrics, decompile_all, mapped_file,
>     engine_subprocess 외 5+ 파일), `__attribute__((unused/noreturn))` 다수.
>   - 부분 fix 보존 (향후 Windows 포팅 대비):
>     • `AURA_FILEINFO_ALIGN` shim — file_format.h
>     • `src/third_party_hub` include path — CMakeLists.txt (rizin_to_aura.h 누락)
>   - Windows MSVC 전체 포팅은 별도 인프라 작업 (수 시간~1일 추정).
>
> Phase 2A-followup: Pass 2 per-function widening 이 rizin 0.9 의 명령 rename
> (`agfj`→`agf json`, `axtj`→`axt j`, `afvj`→`afvl j`) 와 불일치 — e2e assertion
> 범위 외이지만 widened record 가 0 으로 채워짐. 별도 fix.

- [x] 2A.1 Rizin subprocess wire — Phase 1 [engine_subprocess](include/engine_subprocess.h) primitive 위에 배선. argv 조립 + exit-code 매핑. *(Verified: test_rizin_subprocess 8 cases — exec resolve priority, argv composition `rizin -q -0 -c CMDS -- BIN`, status mapping, NULL-input rejection.)*
- [x] 2A.2 Bulk JSON command catalog — `aaa` / `aflj` / `agfj` / `isj` / `iij` / `izj` / `axtj` / `afvj`. command 별 stdout framing: `===AURA-BEGIN:<id>===` / `===AURA-END:<id>===` delimiter pair 방식 (D-27 확정). *(Verified: test_rizin_command_set 8 cases incl. delimiter-injection rejection on cmd args + addr_hex grammar.)*
- [x] 2A.3 Raw snapshot — engine stdout 의 cJSON 트리를 immutable 보존 (R-4). *(Verified: test_rizin_snapshot 6 cases — raw_buffer byte-for-byte preservation, framing→cJSON pipeline, malformed-JSON graceful free.)*
- [x] 2A.4 Normalized snapshot — third_party_hub 정규화 허브 (`include/third_party_hub/rizin_canonical.h` mirror) 통과 후 1 급 record 컬렉션 생성: `FunctionRecord` / `BlockRecord` / `EdgeRecord` / `VariableRecord` / `TypeFactRecord` / `CallEdgeRecord` / `SymbolRecord` / `XrefRecord`. 각 record 에 `{source="rizin", confidence, completeness}` provenance 부착 (R-11/R-12). *(2026-04-30 완료: Block/Edge/Variable/TypeFact/CallEdge/Xref widening 구현 — rizin_to_aura.c stable ID lookups, 2-pass subprocess, body v2 schema (version=2, 8 counts+accessors). Verified: test_rizin_record_widen 8 cases (blocks+edges, variables+type_facts, xrefs+call_edges, orphan skip, empty canonical, NUL byte non-crash, command-id parser). Windows ctest 8/8 rizin GREEN.)*
- [x] 2A.5 Engine Manifest 등록 — `rizin` / 지원 request type = `analyze` (Phase 2A scope; `disasm` / `trace` 는 후속 Phase 2A-2 또는 2B 에서 추가, `decompile` 은 2B) / 버전 `0.7+` / capability_flags = NONE. *(Plan narrowed 2026-04-30: original disasm+analyze+trace bundle deferred — adapter currently returns ERR_UNSUPPORTED for non-ANALYZE per R-7. Verified: test_rizin_isolation manifest assertions + supports_only_analyze.)*
- [x] 2A.6 Adapter init/request/shutdown 구현 — Phase 1 [AuraEngineAdapter](include/engine_request.h) vtable. *(Verified: test_rizin_isolation 5 cases — init/shutdown lifecycle, NULL inputs, unsupported types, AuraRizinAnalyzeBody single-blob layout for free-by-disposer.)*
- [x] 2A.7 Orchestrator type-별 primary 집합 helper — `aura_orchestrator_select_primary(type)`. R-8 강제. *(Verified: test_orchestrator_primary_set 6 cases — ANALYZE={rizin}, DECOMPILE={rizin,ghidra}, DISASM/TRACE={rizin}, NULL/cap=0/unknown-type rejection, cap truncation.)*
- [x] 2A.8 함수 단위 e2e — `analyze` 1 함수 GREEN (함수 목록·CFG·심볼·xref ingestion). 모든 record provenance 채워짐. *(2026-05-01 완료: WSL Ubuntu 24.04 + rizin 0.9.0 (소스 빌드, ~/rizin-install/) 환경에서 e2e GREEN — 18 functions + 93 symbols 추출, raw stdout AURA-BEGIN 마커 보존. Bugfix: rizin 0.9 가 `?e` 를 `echo` 로 rename → `rizin_command_set.c` framing builder 수정 (`?e` → `echo`), test_rizin_command_set 동기화. Linux ctest 11/11 + Windows ctest 10/10+1 SKIP 무회귀. macOS 검증 환경 미제공 (사용자 결정 2026-04-30). 후속 quality issue: Pass 2 per-function widening (agfj/axtj/afvj) 가 rizin 0.9 의 새 `agf json`/`axt j`/`afvl j` 형식과 불일치하여 0 widened records — e2e assertion 범위 외, Phase 2A-followup 으로 분리.)*
- [x] 2A.9 R-10 격리 검증 — `RzCore` / `RzAnalysis*` 가 `src/adapter/rizin/` 와 `include/third_party_hub/rizin_canonical.h` 외부에 0 건. librz 링크 0 건. *(Verified 2026-04-30: `grep -rE "RzCore|RzAnalysis|rz_core\.h|rz_analysis\.h" src/core src/gui` → 0 hits; 3 hits under `include/third_party_hub/` are pre-existing skeleton doc-comments inside the R-10 exception zone.)*
- [x] 2A.10 Crash / timeout graceful degrade — Phase 1 isolation 정책 준수. *(2026-04-30 완료: test_engine_subprocess timeout case (ping -n 4 / timeout_s=1) → AURA_ENGINE_SUBPROC_ERR_TIMEOUT, Windows TerminateProcess 경로 확인. NOT_FOUND graceful path 는 test_rizin_isolation 에서 검증. 3.3s ctest GREEN.)*
- [x] 2A.11 CLI `aura --engine=rizin --analyze <binary>` 동작. *(2026-05-01 Session #27 완료: Linux WSL `build-linux/aura --engine=rizin --analyze tests/fixtures/stripped_nucleus.elf` → `functions: 26, symbols: 9` 출력 + exit 0 확인. src/core/aura.c:101-163 `#ifdef AURA_ENABLE_RIZIN` 가드 경로 정상 동작. Windows MSVC 런타임 검증은 인프라 결함으로 분리 — Phase 2A status note 참조.)*

### Phase 2B — Rizin Decompile Primary  `[x]`

> **Status (2026-05-01 Session #27 close-out)**
> 2B.1–2B.7 모두 verified. WSL Ubuntu + rizin 0.9.0 + rz-ghidra HEAD
> (소스 빌드, /home/str/rizin-install/) 환경. ctest -L "rizin|orchestrator"
> 22/22 GREEN (analyze_e2e + decompile_e2e + decompile_dispatch 포함).
> CLI 실제 동작 확인: `build-linux/aura --engine=rizin --decompile
> tests/fixtures/stripped_nucleus.elf --addr 0x5bc` → backend=rizin/pdgj,
> body 177 bytes Pseudo-C, line_map 4, conf 0.90, comp 0.44, exit 0.
> jsdec (PDDJ) 백엔드는 정책상 capability fallback 으로만 다루며 실제
> 환경에 설치되지 않음 → normalize 가 ERR_BAD_BACKEND 반환 (anti-fake
> policy: 검증되지 않은 jsdec schema 로 fabricated body 출력 금지).

- [x] 2B.1 rz-ghidra / jsdec plugin 의존성 검사 — runtime detection. *(2026-05-01 Session #27 완료: src/adapter/rizin/rizin_decompile_caps.{h,c} 신설. AuraRizinDecompileCaps {has_pdgj/has_pddj/has_pdd} + AuraRizinDecompileBackend enum (NONE/PDGJ/PDDJ/PDD) + 우선순위 체인 pdgj>pddj>pdd>NONE. Pure parser `aura_rizin_parse_decompile_caps()` 가 `rizin -q -c "Lc"` 출력에서 anchored name match (no substring false positive). Subprocess wrapper `aura_rizin_detect_decompile_caps()` 는 tests/fixtures/empty.bin (신규 portable 0-byte) 사용 — /dev/null 금지 (Windows 호환). Verified: test_rizin_decompile_caps 9 cases GREEN, 실제 WSL 환경에서 rz-ghidra 설치 후 smoke `rc=0 pdgj=1 backend=PDGJ`.)*
- [x] 2B.2 `pdgj` / `pddj` / `pdd` 명령 카탈로그 + decompile builder. *(2026-05-01 완료: AURA_RIZIN_DECOMPILE_CMDS[] 인덱스=backend enum 매핑 + aura_rizin_cmd_build_decompile(backend, addr_hex) 가 `aaa` 분석 prefix + 단일 framed `<cmd> @ <addr>` 출력. id 는 base 만 사용 (rizin 0.9 echo 가 `@` 를 seek 으로 파싱하는 quirk 회피). Verified: test_rizin_command_set 13 cases GREEN — pdgj/pddj/pdd id 검증, NONE/out-of-range/bad-addr 거부, framing 순서 + @-수식어 부재 단언.)*
- [x] 2B.3 Decompile snapshot record — single-blob body + normalize. *(2026-05-01 완료: include/rizin_adapter.h 에 AuraRizinDecompileBody (magic 0xAFAA2B01, version 1) + AuraRizinDecompileLineMap + 접근자. src/adapter/rizin/rizin_decompile_normalize.{h,c} 가 REAL pdgj 스키마 ({"code","annotations":[{"start","end","type","offset",...}]}) 를 파싱 — type=="offset" annotations 의 byte_offset → 1-based line 매핑, 연속 (line,addr) 중복 dedup. PDD text fallback 은 raw 복사 + line_map 0. PDDJ 는 ERR_BAD_BACKEND (jsdec schema 검증 안 됨 — anti-fake). Verified: test_rizin_decompile_normalize 9 cases GREEN incl. real captured pdgj snippet.)*
- [x] 2B.4 Manifest 갱신 — DECOMPILE 비트 + lazy caps + handle_decompile. *(2026-05-01 완료: g_rizin_manifest.supported_types |= DECOMPILE. RizinAdapterCtx 에 lazy caps 캐시. ensure_caps 는 request 의 binary_path 를 rizin 프로브 argv 로 재사용 (fixture 의존 제거). handle_decompile 가 cmd build → subprocess → frame parse → cJSON parse (PDGJ/PDDJ) 또는 raw view (PDD) → normalize → body. Verified: test_rizin_isolation 6 cases (manifest DECOMPILE 광고, no-backend → ERR_UNSUPPORTED), real smoke status=OK body magic 0xAFAA2B01.)*
- [x] 2B.5 Decompile e2e — 1 함수 Pseudo-C GREEN. *(2026-05-01 완료: tests/adapter/rizin/test_rizin_decompile_e2e.c 신설. 실제 명령 `PATH=/home/str/rizin-install/bin:... ctest --test-dir build-linux -R rizin_decompile_e2e` → 1/1 Passed (1.04s). 사용 바이너리 tests/fixtures/stripped_nucleus.elf, 사용 함수 주소 0x5bc. 검증: backend=PDGJ, body_len=177, line_map=4, conf=0.90, comp=0.44, raw_size=3149. body 가 실제 rz-ghidra 의 Pseudo-C ("void fcn.000005bc(void) { fcn.00000674(); return; }"). raw stdout 에 framing 마커 ===AURA-BEGIN:pdgj=== / ===AURA-END:pdgj=== 보존 (R-4). rizin 부재 시 SKIP (CTest 77).)*
- [x] 2B.6 Dual-primary dispatch — `decompile` request 시 engine_id 미지정 → 사용자 default (D-28). Rizin/Ghidra 동시 등록 가능 검증. *(2026-05-01 완료: tests/orchestrator/test_orchestrator_decompile_dispatch.c 신설, 6 cases GREEN. Fake adapter (no engine subprocess) 로 routing 만 검증 — both registered, explicit rizin / explicit ghidra / NULL→first-registered (D-28) / ghidra+ANALYZE→ERR_NOT_FOUND / NULL+ANALYZE→rizin. 회귀 ctest -L "rizin|orchestrator" 22/22 GREEN.)*
- [x] 2B.7 CLI `aura --engine=rizin --decompile <binary> --addr <hex>` 동작. *(2026-05-01 완료: src/core/aura.c 의 AURA_ENABLE_RIZIN 가드에 decompile 분기 추가. 실제 명령 `build-linux/aura --engine=rizin --decompile tests/fixtures/stripped_nucleus.elf --addr 0x5bc` → exit 0, backend=rizin/pdgj, addr=0x5bc, body_len=177, line_map=4, conf=0.90, comp=0.44 + Pseudo-C body 출력. 음성 경로: bad addr 0xZZ → exit 1, unknown engine → exit 1. analyze CLI 회귀 0 (functions: 26, symbols: 9).)*

### Phase 2C — Ghidra Decompile Co-primary (이관)  `[x]`

> **Status (2026-05-01 Session #27 close-out)**
> 2C.1–2C.6 모두 verified. 정책: Ghidra = DECOMPILE co-primary 전용
> (raw XML 까지만 real-e2e 검증). analyze/disasm/trace primary 권한은
> Rizin (Phase 2A) 으로 이관됨. Manifest 가 ANALYZE 비트를 더는
> 광고하지 않음 — orchestrator-level ERR_NOT_FOUND 로 routing 단계에서
> 차단. 기존 placeholder 코드 제거. Body 정규화 (XML→AuraEngineResponse.body)
> 는 Phase 3 영역으로 명시 — anti-fake 원칙: fabricated body 또는
> hardcoded pseudo-C 추가 금지.
>
> 검증: ctest -L "rizin|orchestrator" with rizin on PATH → **23/23 GREEN**
> (analyze_e2e + decompile_e2e + decompile_dispatch + ghidra_e2e + ghidra_register
> + ghidra_adapter_graceful). Real CLI: `AURA_DECOMPILE_BIN=...
> AURA_GHIDRA_PROCESSORS_DIR=... AURA_GHIDRA_SLA_DIR=... build-linux/aura
> --engine=ghidra --decompile tests/fixtures/ghidra_invocation/smoke/trivial.elf
> --addr 0x1129` → backend=ghidra/raw-xml, raw_size=902, real XML
> (`<?xml ...?><doc><function name="func_0x00001129" ...`), exit 0.
> rizin DECOMPILE/ANALYZE CLI 회귀 0.

- [x] 2C.1 Ghidra subprocess wire — Phase 1 primitive 위에 배선. *(기존 진행분 보존: src/decompiler/ghidra_subprocess.{h,c} + src/adapter/ghidra/ghidra_adapter.c. argv 조립 + envp_extra (AURA_GHIDRA_PROCESSORS_DIR / AURA_GHIDRA_SLA_DIR) + exit-code → AuraGhidraStatus 매핑. test_ghidra_subprocess_wrapper 가 timeout / killed / ARGV/LOAD/ADDR/ARCH 에러 경로 모두 검증.)*
- [x] 2C.2 Ghidra 응답 파싱 — XML (tinyxml2). *(기존 진행분 보존: tinyxml2 정적 라이브러리 third_party/tinyxml2/, src/decompiler/ghidra_xml_normalize.c + ghidra_xml_to_hir.cpp (D-29A turn #7 의 4-element mapper). test_ghidra_xml_normalize / test_ghidra_xml_to_hir 가 XML 정규화 + HIR 매핑 검증.)*
- [x] 2C.3 Engine Manifest **scope 축소** — DECOMPILE only. *(2026-05-01 Session #27 완료, commit `11a2b2e2`: g_ghidra_manifest.supported_types 가 (1u<<DECOMPILE) 로 narrowed. ANALYZE 비트 + adapter switch 의 ANALYZE placeholder case 제거 — orchestrator manifest_supports 필터가 routing 단계에서 ERR_NOT_FOUND 반환. test_orchestrator_ghidra_register: case_manifest 가 ANALYZE/DISASM/TRACE NOT supported 단언, case_dispatch_unsupported 가 세 type 모두 ERR_NOT_FOUND 단언.)*
- [x] 2C.4 함수 단위 e2e — `decompile` 1 함수 GREEN. *(기존 진행분 보존, Phase 2C.3 narrowing 후 회귀 0: tests/orchestrator/test_orchestrator_ghidra_e2e.c 가 vendored aura-decompile 바이너리 spawn → tests/fixtures/ghidra_invocation/smoke/trivial.elf @ 0x1129 → orchestrator dispatch DECOMPILE → resp.raw 에 `<doc>` + `<function` XML 태그 보존 단언. ctest 0.31s GREEN. R-4 raw_xml 보존 confirmed.)*
- [x] 2C.5 CLI `aura --engine=ghidra --decompile <binary> --addr <hex>` 동작 회귀 0. *(2026-05-01 Session #27 완료, commit `4b23e783`: src/core/aura.c 에 ghidra 분기 추가. env vars AURA_DECOMPILE_BIN / AURA_GHIDRA_PROCESSORS_DIR / AURA_GHIDRA_SLA_DIR 필수 (anti-fake — hardcoded fallback 금지). Output: backend=ghidra/raw-xml, addr, raw_size, raw XML head 800 chars. Real run on tests/fixtures/ghidra_invocation/smoke/trivial.elf @ 0x1129 → exit 0, raw_size=902, 실제 `<?xml ...?>` 출력. 음성 경로: missing env → exit 1 with specific message; ERR_TIMEOUT/ERR_CRASH/ERR_INVALID 모두 명시적 에러. rizin --decompile / --analyze CLI 회귀 0.)*
- [x] 2C.6 Crash / timeout graceful degrade — Phase 1 isolation 정책 준수. *(2026-05-01 Session #27 완료, commit `f73bf515`: tests/adapter/ghidra/test_ghidra_adapter_graceful.c 신설, 4 cases — NULL request → ERR_INVALID, NULL binary_path → ERR_INVALID, bogus decompile_bin → ERR_INTERNAL (SPAWN 매핑), 3회 반복 dispatch idempotent. wrapper-level timeout/killed 는 test_ghidra_subprocess_wrapper 가 별도 검증. adapter status mapping (AURA_GHIDRA_OK/TIMEOUT/KILLED/ARGV/LOAD/ADDR/ARCH/DECOMPILE/IO/SPAWN/INTERNAL → AURA_ENGINE_OK/TIMEOUT/CRASH/INVALID/INTERNAL R-7 합성) 동작 확인.)*

참조: `docs/design/d29b_semantic_mapping.md`, `docs/design/d28_ghidra_hir_mapping.md` (Ghidra decompile-only 범위로 재해석)

### Phase 2 재점검 로그 (Re-verification)

> **2026-05-01 Session #27 — Phase 2B/2C end-state re-verification (post-close-out).**
> No source changes since `9557d556` (Phase 2C close-out). Working tree
> clean modulo `.claude/settings.local.json` (harness-managed, not project
> code). Build incremental — `cmake --build build-linux` was a no-op
> rebuild that linked the existing aura + aura-decompile binaries. All
> verifications below were run on the **existing committed code**, not on
> a freshly-edited tree.
>
> **Executed validation commands and results:**
>
> | Command | Result |
> |---------|--------|
> | `ctest --test-dir build-linux -L "rizin"` (PATH=/home/str/rizin-install/bin:…) | **12/12 Passed** (rizin sub-suites + analyze_e2e 0.19s + decompile_e2e 1.05s) |
> | `ctest --test-dir build-linux -L "rizin\|orchestrator"` (PATH=…) | **23/23 Passed** (analyze_e2e + decompile_e2e + decompile_dispatch + ghidra_register×3 + ghidra_e2e + ghidra_adapter_graceful + 16 sibling rizin/orchestrator) |
> | `ctest --test-dir build-linux -L "rizin\|orchestrator"` (no PATH) | **23 reported pass, 2 SKIP** (test_rizin_analyze_e2e + test_rizin_decompile_e2e gracefully SKIP via CTest 77 when rizin not on PATH — intended) |
> | `ctest --test-dir build-linux -R orchestrator_ghidra` | **4/4 Passed** (manifest, register, unsupported, e2e — Ghidra DECOMPILE-only manifest enforced; ANALYZE/DISASM/TRACE all ERR_NOT_FOUND at orchestrator routing) |
> | `ctest --test-dir build-linux -R ghidra_adapter_graceful` | **1/1 Passed** (4 sub-cases: NULL request, NULL binary_path, bogus decompile_bin, disposer idempotent) |
> | rizin DECOMPILE CLI: `build-linux/aura --engine=rizin --decompile tests/fixtures/stripped_nucleus.elf --addr 0x5bc` | **exit 0**, backend=rizin/pdgj, body_len=177, line_map=4, conf=0.90, comp=0.44, real Pseudo-C body (`void fcn.000005bc(void) { fcn.00000674(); return; }`) |
> | rizin ANALYZE CLI (regression): `build-linux/aura --engine=rizin --analyze tests/fixtures/stripped_nucleus.elf` | **exit 0**, "functions: 26 / symbols: 9" |
> | Ghidra DECOMPILE CLI (env vars set; fixture path actually `tests/fixtures/ghidra_invocation/smoke/trivial.elf`): `build-linux/aura --engine=ghidra --decompile <fixture> --addr 0x1129` | **exit 0**, backend=ghidra/raw-xml, raw_size=902, real `<?xml … ?><doc><function name="func_0x00001129" …` |
> | Ghidra CLI negative — nonexistent fixture (`tests/fixtures/trivial.elf` does not exist in repo) | **exit 1**, "aura: ghidra rejected the request (bad addr/arch/load)" — graceful degrade confirmed |
> | Ghidra CLI negative — `unset AURA_DECOMPILE_BIN` | **exit 1**, "aura: --engine=ghidra --decompile requires AURA_DECOMPILE_BIN env var" |
>
> **Engine status (re-verified):**
>
> | Engine / Type | Manifest | Real e2e | Body normalized? | CLI |
> |---------------|----------|----------|------------------|-----|
> | rizin / ANALYZE | advertised | GREEN (analyze_e2e) | yes (AuraRizinAnalyzeBody) | `--engine=rizin --analyze <bin>` |
> | rizin / DECOMPILE (PDGJ) | advertised | GREEN (decompile_e2e) | yes (AuraRizinDecompileBody) | `--engine=rizin --decompile <bin> --addr <hex>` |
> | rizin / DECOMPILE (PDDJ) | runtime-cap fallback | not tested in env | normalize → ERR_BAD_BACKEND (anti-fake) | n/a |
> | rizin / DECOMPILE (PDD) | runtime-cap fallback | not tested in env | yes (text-only body) | n/a |
> | rizin / DISASM, TRACE | NOT advertised | n/a | n/a | n/a |
> | ghidra / DECOMPILE | advertised | GREEN (orchestrator_ghidra_e2e) | **NO — Phase 3** (raw XML only on resp.raw, body=NULL) | `--engine=ghidra --decompile <bin> --addr <hex>` |
> | ghidra / ANALYZE | **NOT advertised** (Phase 2C.3) | n/a | n/a | n/a |
> | ghidra / DISASM, TRACE | NOT advertised | n/a | n/a | n/a |
>
> **Policy holds (verified live):**
> - Ghidra ANALYZE 미광고 정책 유지 — `aura_engine_manifest_supports(m, AURA_ENGINE_REQ_ANALYZE) == 0` (case_manifest assertion).
> - Orchestrator routes ANALYZE/DISASM/TRACE → ERR_NOT_FOUND BEFORE adapter is consulted (case_dispatch_unsupported 3 sub-cases).
> - rizin DECOMPILE/ANALYZE 회귀 0 — 모든 Phase 2A/2B 테스트 + CLI 동일 결과.
>
> **Known gaps (re-acknowledged, no new work in this session):**
> - **Ghidra XML → normalized body / HIR**: Phase 3 보류. 현재 resp.body=NULL, raw XML 만 R-4 source-of-truth 로 보존. ghidra_xml_to_hir.cpp 의 4-element mapper 가 별도 layer 로 존재하지만 AuraEngineResponse.body 와는 미연결.
> - **jsdec / PDDJ schema 미검증**: 환경 미설치, normalize 가 ERR_BAD_BACKEND 반환. fabricated body 출력 거부 정책 유지.
> - **rizin 0.9 framing `@` quirk follow-up** (Phase 2A-followup): analyze Pass-2 widening (`agfj`/`axtj`/`afvj`/`aftj` per-function frames with `@<addr>` in id) 가 rizin 0.9 의 echo seek 파싱에 silently 삼켜져 widened record 0-fill. decompile builder (Phase 2B.2) 는 이미 id 에서 `@<addr>` 제거하여 우회. analyze pass-2 fix 별도 작업.
> - **Windows MSVC 포팅**: `__attribute__((aligned))`, `unistd.h` 직접 include, GCC 전용 attribute 다수 잔존 (9+ 파일). Phase 2A.11 부분 fix (file_format.h shim, third_party_hub include path, YARA opt-out) 보존; 전체 포팅은 별도 인프라 작업.
> - **Engine status set R-7 정밀도**: SPAWN/IO/INTERNAL 가 모두 ERR_INTERNAL 로 collapse — CLI 가 generic "(status=N)" 만 표시. R-7 정책 변경 필요시 별도.
>
> **회귀 발견: 없음 (none).** 모든 Phase 2A/2B/2C 테스트 + CLI smoke 가 본 재점검에서 GREEN. 새 코드 변경 없음.


---

## Phase 3 — Unified Model Ingestion  `[ ]`

**목표**: 엔진 응답을 AURA Unified Model 로 ingestion / normalization / mapping 한다. 본 페이즈는 표현 변환 단계이며 분석 단계가 아니다.

> **핵심 원칙 (절대 위반 금지)**
> 1. AURA는 새로운 분석 결과를 생성하지 않는다.
> 2. Ingestion 단계는 엔진 출력의 구조를 복사하고 필드를 매핑하는 작업만 수행한다.
> 3. 정규화 과정에서 CFG, IR, 타입, 데이터 흐름을 새로 계산하거나 추론하는 로직은 금지된다.

> **본 페이즈 비대칭 (재구조화 동기, 2026-05-01 Session #27 기준)**
>
> - **Rizin analyze** — 8 종 1 급 record (`FunctionRecord` / `BlockRecord` / `EdgeRecord` / `VariableRecord` / `TypeFactRecord` / `CallEdgeRecord` / `SymbolRecord` / `XrefRecord`) 가 이미 `AuraRizinAnalyzeBody` 로 `AuraEngineResponse.body` 에 연결됨 (Phase 2A.4 완료, R-11 provenance + R-12 1 급화 적용).
> - **Rizin decompile** — `AuraRizinDecompileBody` (Pseudo-C + line_map) body 연결 완료 (Phase 2B.3).
> - **Ghidra decompile** — raw XML 만 보존, `resp.body = NULL` (Phase 2C close-out 명시 보류).
>
> 즉 Phase 3 의 실 미완료 = **Ghidra decompile body 매핑 + adapter 간 body schema 통일**. 본 페이즈를 6 sub-phase (3A–3F) 로 분해한다. Rizin 경로는 이미 구현된 record set 을 body contract 에 정렬·검증하는 범위로 한정한다 (새 record / 새 매핑 패스 / 새 추론 도입 금지).

#### Phase 3A — Ingestion Contract & Unified Body Schema  `[x]`

**범위**: `AuraEngineResponse.body` 의 type-별 contract 확정. 현재 `include/engine_request.h` 의 `void *body` placeholder 를 type-별 typed pointer 로 격상.

- [x] 3A.1 Body schema 분기 명문화 — `AURA_ENGINE_REQ_ANALYZE` body = `AuraRizinAnalyzeBody`-shape (single-blob flattened record collection, 8 종 1 급 record). `AURA_ENGINE_REQ_DECOMPILE` body = `AuraDecompileBodyView` 16-byte prefix + backend-specific payload (Rizin: 기존 `AuraRizinDecompileBody` sub-shape 보존; Ghidra: Phase 3C). *(2026-05-01: `include/aura/decompile_body.h` 신설, `AuraDecompileBodyHeader` + `AuraDecompileBackend` enum + `aura_decompile_body_view_inspect()`. `src/core/decompile_body_view.c` 가 Rizin 매직 인식.)*
- [x] 3A.2 `engine_request.h` doc-comment 갱신 — `body` 가 Phase 3+ placeholder 라는 표현 제거, 실 contract 인용. R-4 raw 보존 정책 유지. *(2026-05-01: `AuraEngineResponse.body` doc-comment + `diagnostics` / `diagnostics_size` 사이드카 필드 추가, `aura_engine_response_dispose()` 에 free 분기 추가.)*
- [x] 3A.3 R-9 enforcement static check — body 내부에 엔진 응답에서 직접 유래하지 않는 필드 (AURA 측 추정 edge kind / 추론 타입 등) 도입 시 reject 규칙 명문화. *(2026-05-01: `decompile_body.h` 도큐먼트에 명시.) tests/integration/test_unified_ingestion.c (3F.1) 가 enforcement 시연 — 3F 에서 활성화.*
- [x] 3A.4 어휘 lint 강화 — 본 페이즈 후반의 *용어 제한* 블록 토큰을 신규 항목 본문이 도입하면 PR 차단 (CI grep guard 또는 PR review checklist). *(2026-05-01: 본 Tasks.md 의 §"용어 제한" + Phase 3 enforcement 블록을 PR review checklist 항목으로 운용 — CI grep guard 별도 등록 안 함, review-time 강제.)*

> **DoD 공통**: ingestion / normalization / mapping 범위만. R-1 / R-9 위반 시 reject. 본 항목 작업이 v2.x custom decompiler 경로 (legacy 토큰 — `HirFunc` / `IrFunc` / SSA→HIR / `hir_builder`) 를 재사용 전제로 도입하면 reject. 위 토큰은 *legacy 폐기 / 사용 금지* 문맥에서만 등장 허용.

#### Phase 3B — Rizin Analyze Body 정합화 + v0.8.0 execution baseline 정정  `[x]`

> **Status (2026-05-01 close-out)**
> stable Rizin v0.8.2 기준의 analyze schema 정합화 기록은 보존하되,
> 2026-05-06 ADR-0052 로 **실행/시연/decompile 기준은 Rizin 0.8.0
> shared64 + rz-ghidra 0.8.0** 으로 정정한다. Windows 검증 기준 경로:
> `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe`
> + `SLEIGHHOME=third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh`.
> 직접 `pdgj` 및 GUI IPC decompile 에서 `dbg.main` pseudo-C 출력 확인.
>
> 과거 Phase 3 analyze baseline 은 0.8.2 source 기록으로 남지만 신규 작업은
> 0.8.0 shared64 bundle 을 적용 기준으로 삼는다. librz 링크 0 건 유지 (R-10).

- [x] 3B.1 `AuraRizinAnalyzeBody` ↔ 3A.1 analyze body schema header 일치 검증 — 8 종 record layout (`include/aura/normalized_records.h`) 가 contract 의 expected layout 과 동일. *(layout 변경 0, 기존 Phase 2A.4 schema 보존.)*
- [x] 3B.2 R-11 provenance + R-12 1 급화 contract 경계 재검증 — body 받는 쪽이 record 의 `{source, confidence, completeness}` 누락 / `FunctionRecord` 부속 배열 존재 시 reject. *(기존 `test_rizin_record_widen` / `test_rizin_record_shape` / `test_rizin_provenance` 가 GREEN — Pass 2 widening 결과까지 동일 provenance 강제 확인.)*
- [x] 3B.3 **Rizin command schema baseline 정정** (재명명: 원래 명세는 "rizin 0.9 quirk fix" 였으나, 0.8 계열에서도 `agfj` / `afvj` / `aftj` 부재 확인 — 0.9-dev specific 이슈가 아니라 0.8 계열 schema baseline). 적용:
  - `src/adapter/rizin/rizin_command_set.{h,c}` — `AuraRizinPerFunctionCmd {id_base, cmd}` struct 도입. id_base (parser 안정 키) 와 cmd (0.8 계열 실제 명령) 분리. 매핑: `agfj`→`agf json`, `axtj`→`axtj` (불변), `afvj`→`afvlj`. `aftj` 제거 (0.8 계열 JSON 모드 부재 — 호출 시 `rizin -c` script halt + framing 깨짐). fake record 합성 0 (R-9).
  - `src/adapter/rizin/rizin_framing.{h,c}` — id 분리자 `@` → `_` (rizin echo seek quirk 회피, general safety). `aura_rizin_command_id_parse()` 가 `_` 기반 분리.
  - `src/adapter/rizin/rizin_snapshot.c` — ingestion adapter 가 0.8 계열 실제 JSON schema 직접 매핑:
    - `populate_cfg`: `{"nodes":[{id, offset, out_nodes:[], ...}]}` 인식. addr=offset, size=0 (미보고 — 추정 안 함), jump/fail=out_nodes[0/1] 위치적 매핑 (out_nodes 가 정확히 2 초과면 dropped — diagnostic visibility 는 Phase 3E). legacy array shape backward-compat 보존.
    - `populate_variables_from_array`: `{"name","type","arg","storage":{"type","stack","reg"}}` 인식. kind = element.kind > storage.type > category key 우선순위. legacy `{"isarg","kind","ref.offset"}` 보존.
  - 테스트 동기화: `test_rizin_command_set` (struct + aftj 부재 단언), `test_rizin_record_widen` / `test_rizin_snapshot` (`_` separator).
- [x] 3B.4 **third_party execution baseline 교체** — 신규 적용 기준은 `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/` 이다. 기존 0.8.2 source 기록은 과거 analyze 정합화 근거로만 취급한다. AURA build graph 의 librz 링크 0 건 / `RZ_API` core leak 0 건 재확인 대상.

> **DoD 공통**: ingestion / normalization / mapping 범위만. 새 record 정의 금지. R-1 / R-9 / R-10 / R-11 / R-12 위반 시 reject.

> **Compatibility backlog (Phase 3 외부)**
> - **rz-ghidra stable plugin build** — ✅ **해소 / 기준 갱신 (2026-05-06)**. Windows 기준 `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/` prefix 에 rz-ghidra 0.8.0 plugin `core_ghidra.dll` + `rz_ghidra_sleigh/` SLA 트리 적용. `pdgj @ 0x40117b` 직접 실행 및 GUI decompile 에서 `dbg.main` pseudo-C GREEN. 시스템 전역 설치 미수행 — project-local prefix 로 한정.
> - **0.9-dev / 0.8.2 보존** — reference/history env 로만 활용. 신규 시연·테스트 기준 아님.
> - **`aftj` (function-type extraction)** — 0.8 계열 / 0.9-dev 모두 JSON 모드 부재. 미지원으로 명문화 (R-9 합성 금지).
> - **보안 제품 경고** — Windows Defender / SmartScreen / EDR 이 AURA/Rizin/rz-ghidra 를 cyber security risk 로 표시할 수 있음. ADR-0052 에 따라 출처/버전/경로/해시와 로컬 분석 원칙을 문서화하며, 경고 우회 코드는 금지.

#### Phase 3C — Ghidra Decompile IR Artifact Ingestion  `[x]` (재정의 — 2026-05-01 완료)

> **Phase 3C 완료 의미 — 명확화**: Ghidra decompile path 는 raw IR/SSA XML 보존 + diagnostics sidecar 로 closed. **Ghidra pseudo-C 구현은 Phase 3 에서 수행되지 않았다** — pseudo-C view 채움은 **Phase 4+ backlog (3C2)** 로 이관되었으며 별도 D-결정 + 사용자 승인 필요. 본 sub-phase 의 완료는 "IR artifact ingestion + body=NULL 정상 명문화 + diagnostic visibility" 까지의 범위를 의미한다.

**관찰 사실 (2026-05-01 재검증)**: 현재 vendored `aura-decompile` 가 emit 하는 XML 은 Ghidra decompiler 의 **IR / SSA 표현** (`<varnodes>`, `<op code=N>`, `<seqnum>`, `<block>`, `<highlist>`, `<prototype>`) 이다. **PrettyPrint pseudo-C source-of-truth 가 부재**: `<line>` / `<emit>` / `<token>` 태그 0 건. fixture `tests/fixtures/ghidra_invocation/smoke/{trivial,branch,external_call}.xml` 에서 직접 확인. stderr 의 `[xml-emit] ok` 는 XML 직렬화 단계 표식이지 PrettyPrint emit element 가 아니다. `aura-decompile` argv 도 `--decompile / --addr / --arch` 만 — PrettyPrint 출력 모드 옵션 부재.

**범위 재정의**: 기존 "Ghidra XML → AuraDecompileBodyView pseudo-C + line_map" 계획은 **폐기**. 대체:
- raw XML 을 IR artifact 로 공식 보존 (R-4) 하고, `out->body` 는 **`AuraDecompileBodyView` 를 채우지 않는다**. body view 는 pseudo-C view contract 인데 IR XML 은 그 contract 의 source-of-truth 가 아니므로 view-level 매핑 자체가 불성립.
- IR XML → pseudo-C / line_map / 임의 line counter / address mapping 합성 **일체 금지** (R-9).
- fake non-NULL body, 빈 pseudo-C body 로 DoD 통과 **금지**.
- "PrettyPrint pseudo-C 부재" 사실은 diagnostics sidecar (3E) 로만 노출.

- [x] 3C.1 IR artifact 보존 — `out->raw` / `out->raw_size` 에 aura-decompile stdout XML 그대로 (byte 변형 0). `out->body = NULL; out->body_size = 0;` 명문화. 현 `ghidra_adapter.c:140-147` 동작 유지. *(2026-05-01: `tests/orchestrator/test_orchestrator_ghidra_e2e.c` 가 success path 에서 `out.body == NULL && out.body_size == 0 && out.raw != NULL` 단언; 25/25 GREEN.)*
- [x] 3C.2 IR artifact 인식 단언 — adapter 가 emit 한 XML 이 Ghidra IR 형태 (`<doc><function>...<ast><varnodes>` 또는 `<block>` / `<op code=>`) 임을 단순 sniff 단언 (parsing 없이 prefix / 핵심 토큰 substring 존재만). *(2026-05-01: `tests/adapter/ghidra/test_ghidra_ir_artifact.c` 신설 — fixture 3종 (trivial/branch/external_call) 에 `<doc>+<function>+(<ast>|<varnodes>|<block>|<op>|<seqnum>)` 단언 + PrettyPrint 태그 (`<line>/<emit>/<token>`) 부재 단언. e2e 테스트도 동일 sniff. label `phase3c`.)*
- [x] 3C.3 R-9 enforcement 명문화 — IR XML 을 pseudo-C 로 합성하지 않음. `ghidra_adapter.c` 에 IR→pseudo-C / IR→line_map / IR→address-line 매핑 코드 추가 금지. *(`test_ghidra_ir_artifact` 의 PrettyPrint 태그 부재 단언이 R-9 enforcement 시연.)*
- [x] 3C.4 PrettyPrint 부재 → diagnostic visibility — `reason_key = ghidra_pseudo_c_unavailable` (severity=critical, ref_kind=request, ref_id=req->addr) 를 3E sidecar 로 발행. *(2026-05-01: `src/adapter/ghidra/ghidra_adapter.c::ghidra_handle_decompile()` success path 에서 `aura_diagnostics_alloc_critical()` 호출. body 합성 없음 — visibility only. e2e 단언 GREEN.)*
- [x] 3C.5 legacy 4-element mapper 분리 유지 — `src/decompiler/ghidra_xml_to_hir.cpp` (D-29A turn #7) 는 v2.x HIR 경로 잔존물로 본 sub-phase 와 비연결. body / orchestrator 경로 재진입 금지. *(adapter 코드에서 미참조; CMakeLists 에 v2.x decompiler 빌드 가드 별개.)*

> **DoD 공통**: raw 보존 (R-4). pseudo-C / line_map / line counter 합성 금지 (R-9). body=NULL 유지. 차단된 pseudo-C view 는 3C2 backlog 로 분리.

> **Backlog — 3C2 / Phase 4+ "Ghidra PrettyPrint Output Source"** (Phase 3 close-out 시점에 Phase 4+ 로 정식 이관 — 2026-05-01)
>
> 사실 (Phase 3 종료 시점):
> - 현 vendored `aura-decompile` 는 Ghidra IR/SSA XML 만 emit 한다 (`<varnodes>` / `<op code=N>` / `<seqnum>` / `<block>` / `<highlist>` / `<prototype>`).
> - PrettyPrint pseudo-C source-of-truth (`<line>` / `<emit>` / `<token>`) 부재.
> - `aura-decompile` argv 에 PrettyPrint 출력 모드 옵션 부재.
> - Phase 3 에서는 Ghidra decompile path 를 raw IR artifact + diagnostic (`ghidra_pseudo_c_unavailable`) 으로 처리한다 (= 3C 완료 범위).
>
> Phase 4+ 에서 별도 D-결정 후 진행. Phase 3 에서 구현하지 않는다. 후보:
> - **(A)** vendored `aura-decompile` 에 PrettyPrint 출력 모드 추가 (Ghidra `decompile.cc` `PrintC` emitter 노출). third_party 변경 동반 → **D-결정 + 사용자 승인 필요**.
> - **(B)** rz-ghidra 경로의 PDGJ 출력만 pseudo-C source-of-truth 로 인정. Ghidra adapter 는 IR-only fix 유지.
> - **(C)** Ghidra Headless `DecompilerOptions` (line numbering 활성) 사용 별도 binary path. third_party 추가 동반 → 사용자 승인 필요.
>
> Phase 4+ 이관 시 본 항목 자체는 backlog 트래커로만 유지하고, 실제 sub-phase 분해는 D-결정 시점의 plan 으로 갈음한다.

#### Phase 3D — Ghidra Analyze Capability 보류  `[ ]` (별도 D-결정)

**범위**: Ghidra adapter manifest 가 Phase 2C.3 에서 DECOMPILE only 로 narrowed 됨. Phase 3 에서 ANALYZE 광고 추가 / Ghidra → record set 매핑 추가 **금지**.

- [x] 3D.1 manifest scope 변경 금지 — `g_ghidra_manifest.supported_types` 가 `(1u << DECOMPILE)` 유지. *(`tests/orchestrator/test_orchestrator_ghidra_register::case_manifest` 가 cases 5–8 에서 DECOMPILE only 단언; ANALYZE/DISASM/TRACE non-advertise 회귀 0 — 2026-05-01 25/25 GREEN.)*
- [x] 3D.2 Ghidra ANALYZE 도입 시 PRD §9 신규 D-결정 + rules R-8 (type-별 primary 집합) 변경 + 사용자 명시 승인 필요함을 본 항목에 기록. Phase 3 범위에서 **제외**. *(본 항목으로 명문화 완료.)*
- [x] 3D.3 orchestrator routing 회귀 0 — ghidra + ANALYZE → ERR_NOT_FOUND 단언. *(`case_dispatch_unsupported` 가 DISASM/ANALYZE/TRACE 모두 ERR_NOT_FOUND 단언 — 25/25 GREEN.)*

> **DoD 공통**: 본 sub-phase 는 *유지* 작업. 새 코드 추가 0. ingestion / normalization / mapping 경계 외 movement 금지.

#### Phase 3E — Tier C Diagnostic Stream (visibility only)  `[ ]`

**범위**: legacy 설계 d28 의 §6.0 Tier A / B / C 분류 + §13 의 `<aura_diagnostics>` schema **만** 부분 재사용. 나머지 d28 / d29b 본문은 폐기 (아래 *Legacy 문서 처리* 참조). diagnostic 의 목적은 **mapping loss visibility only** — fix / inference / 보정 목적 금지.

- [x] 3E.1 Diagnostic 출력 경로 — `AuraEngineResponse.diagnostics` / `diagnostics_size` 분리 필드. body schema 와 격리, orchestrator → CLI 1회성 출력 경로. *(2026-05-01: `include/aura/diagnostics.h` 신설 — `AuraDiagnosticsHeader` (magic 0xAFAA3E01 v1) + `AuraDiagnosticEntry`. `src/core/diagnostics.c` 가 alloc/view 제공. `aura_engine_response_dispose` 가 free. `src/core/aura.c` ghidra decompile 분기에서 `aura_diagnostics_view` 로 critical 항목 출력.)*
- [x] 3E.2 reason key 사전 — `ghidra_pseudo_c_unavailable` (Phase 3C 활성), `address_space_dropped` / `indirect_op` / `param_truncated` / `jumptable_dropped` / `seqnum_collision` 예약 (3C2 backlog 활성 시점에 발행). *(diagnostics.h 매크로로 정의.)*
- [x] 3E.3 visibility 범위 한정 — severity `critical` 만 강제. acknowledge / harness hard-fail / per-tier ≥95% gate 는 범위 밖. *(`AuraDiagnosticSeverity` enum + alloc helper 가 critical 만 노출.)*
- [x] 3E.4 legacy 폐기 — d28 §6.3 / §7 미사용. 재사용 = §6.0 Tier 분류 + §13 diagnostic schema 까지. *(diagnostics.h 헤더 코멘트로 명문화.)*

> **Ghidra adapter 발행** — `src/adapter/ghidra/ghidra_adapter.c::ghidra_handle_decompile()` success path 1 곳 (Phase 3C.4 의 의존 항목). `tests/orchestrator/test_orchestrator_ghidra_e2e.c` 가 view rc=0, count=1, reason=`ghidra_pseudo_c_unavailable`, severity=CRITICAL, ref_kind=REQUEST(1), ref_id=req->addr 단언 — 2026-05-01 GREEN.

> **DoD 공통**: ingestion / normalization / mapping 범위만. diagnostic 은 visibility only — 추론 / 보정 / 자동 fix 금지 (R-9).

#### Phase 3F — Mapping Conformance Tests  `[ ]`

**범위**: 모든 adapter 가 3A.1 body contract 를 일관 출력함을 검증하는 통합 테스트 신설. AURA 측 추론 / 보정 로직이 끼어들지 않음을 시연.

- [x] 3F.1 `tests/integration/test_unified_ingestion.c` 신설. *(2026-05-01: 3 sub-case capability-gated. 실측: rizin analyze GREEN (functions=26 symbols=9 blocks=48 edges=29), ghidra decompile GREEN (body=NULL raw_size=902 IR-only critical diagnostic), rizin decompile SKIP (rz-ghidra plugin 부재 — 기존 capability backlog 와 동일).)*
    - **Rizin analyze**: body magic 단언, functions/symbols 비공백 단언, body-vs-diagnostics 격리 단언.
    - **Rizin decompile**: body magic 단언, body_text 비공백, PDGJ backend 시 line_map 채움, framing marker (`===AURA-BEGIN/END===`) 보존.
    - **Ghidra decompile**: `body == NULL && body_size == 0` 단언 (fabricated body 부재), raw IR sniff (`<doc>+<function>+(<ast>|<varnodes>|<block>|<op>|<seqnum>)`), PrettyPrint 태그 부재 단언 (R-9 enforcement), `ghidra_pseudo_c_unavailable` critical diagnostic 단언.
- [x] 3F.2 R-9 enforcement 검증 — sub-case 단언이 직접 시연. Rizin pseudo-C body 와 Ghidra IR-only raw 가 같은 fixture 에 대해 서로 다른 source-of-truth 를 내도 AURA 가 합성/merge/보정 없이 그대로 표시. mapping loss 는 diagnostic visibility 만.
- [x] 3F.3 ctest label `unified-ingestion;orchestrator` 등록 + `SKIP_RETURN_CODE 77` (capability gate). *(2026-05-01: `tests/CMakeLists.txt` 5094-5125 라인.)*

> **DoD 공통**: 본 sub-phase 는 검증 layer. 새 ingestion 로직 추가 0. 검증 결과로 R-9 enforcement 시연.

#### Phase 3 / Phase 2 close-out 보류 항목 매핑

| Phase 2C close-out 보류 (Phase 2 재점검 로그) | Phase 3 처리 sub-phase |
|---|---|
| Ghidra XML → normalized body / HIR | **3C** |
| jsdec / PDDJ schema 미검증 | **N/A** — 환경 미설치 정책 유지, body schema 차원에서는 변동 없음 |
| rizin 0.9 framing `@` quirk follow-up — Pass 2 widening 0-fill | **3B.3** (blocking)

**명시적 금지 (Phase 3 내부 강제)**

- [ ] 새로운 CFG 생성 금지
- [ ] 새로운 IR 생성 금지
- [ ] 타입 추론 금지
- [ ] 데이터 흐름 분석 금지
- [ ] 엔진 결과 보정/정정 금지
- [ ] 엔진 간 결과 merge 금지

**용어 제한 (Phase 3 내부 강제)**

- "정규화 분석기" 표현 사용 금지
- "analysis" 단어 사용 금지
- 사용 가능 용어: ingestion / normalization / mapping

#### Legacy 설계 문서 처리 (Phase 3 내부 강제)

Phase 3 는 다음 legacy 문서를 **구현 근거로 사용하지 않는다**. 위 문서들은 v2.x custom decompiler (legacy SSA → legacy HIR builder, `HirFunc` / `IrFunc` / `hir_builder` 전제) 로 작성됐고, orchestrator pivot (D-1, 2026-04-30) 이후 그대로 따르면 R-1 / R-9 위반 위험이다.

| 문서 | Phase 3 처리 |
|---|---|
| `docs/design/high_level_ir.md` | **사용 금지** — legacy v2.x SSA → legacy HIR builder 전제 (R-9 위반 위험). |
| `docs/design/d28_ghidra_hir_mapping.md` | **부분 재사용** — §6.0 Tier A / B / C 분류 + §13 `<aura_diagnostics>` schema 까지. §6.3 (legacy ABI 확장 — `HirCallConv` / `HirStorage`) / §7 (5-tier per-tier ≥95% harness with PrettyPrint diff) / §8 (영속 키 with legacy `HirFunc`) 는 **사용 금지**. |
| `docs/design/d29b_semantic_mapping.md` | **사용 금지** — `AuraGhirFunc` → legacy `HirFunc` 통합 / legacy `hir_builder` structuring 재사용 전제 (R-9 위반 위험). |

참조: `docs/design/high_level_ir.md` (legacy 사용 금지), `docs/design/d28_ghidra_hir_mapping.md` (§6.0 + §13 만 재사용), `docs/design/d29b_semantic_mapping.md` (legacy 사용 금지), `docs/design/d_rizin_skeleton.md` (Rizin record set 정의 — Phase 2A.4 적용분), `docs/design/third_party_hub.md` (canonical mirror 격리 정책).

---

## Phase 4 — Override Layer

**D-2 확정 (2026-05-01)**: SQLite row-oriented. Sub-phase 분해: 4A→4B→4C→4D→4E.
**핵심 규칙**: R-5 (engine output immutable), R-9 (no new analysis in override layer).

---

### Phase 4A — Stable Identity Contract  `[x]` *(완료 2026-05-01)*

**목표**: override target 을 재분석 후에도 안정적으로 식별하는 key contract 정의.

- [x] 4A.1 `include/override_identity.h` — AuraOverrideKey, AuraOverrideBinaryFingerprint, AuraOverrideConfidence (EXACT/STRONG/WEAK/MISSING), helper API 선언.
- [x] 4A.2 `src/core/override_identity.c` — helper 구현 (key_from_function_record, key_from_variable_record, fingerprint_match, confidence_allows_auto_apply, key_same_target).
- [x] 4A.3 `tests/core/test_override_identity.c` — 15 TC 단위 테스트. WSL ctest GREEN.
- [x] 4A.4 `docs/design/d_phase4_stable_identity.md` — 명세 문서 (4A.X1–X4 + match policy).

---

### Phase 4B — SQLite Store  `[x]` *(완료 2026-05-02)*

- [x] 4B.1 SQLite schema — `overrides` 테이블 (AuraOverrideKey 모든 필드 + payload + created_at/updated_at). PK = (sha256, engine_id, request_type, function_stable_id, target_kind, target_stable_id).
- [x] 4B.2 CRUD API (`include/override_store.h`, `src/core/override_store.c`) — open/close/put/get/delete/count. INSERT OR REPLACE 시 created_at 보존.
- [x] 4B.3 round-trip 단위 테스트 (`tests/core/test_override_store.c`) — TC-1..TC-10, in-memory DB. ctest GREEN.

---

### Phase 4C — Overlay Apply  `[x]` *(완료 2026-05-02)*

- [x] 4C.1 `AuraOverrideView` (`include/override_view.h`, `src/core/override_view.c`) — (fingerprint, engine_id) 로 필터된 ACTIVE override 의 in-memory snapshot. engine 출력 미수정 (R-5). build/lookup/destroy.
- [x] 4C.2 auto-apply 로직 (`include/override_resolve.h`, `src/core/override_resolve.c`) — `aura_override_resolve(stored, fresh)` → APPLY/CONFLICT/ORPHAN. fingerprint mismatch=ORPHAN, target shift=CONFLICT, 양쪽 confidence ≥ STRONG=APPLY.
- [x] 4C.3 conflict/orphan 상태 영속 — `overrides.status` 컬럼 + `aura_override_store_set_status` / `count_by_status`. PENDING/ACTIVE/CONFLICT/ORPHAN 4-state.

---

### Phase 4D — Rename / Type Override Layering  `[x]` *(scope-confined 2026-05-02)*

**Decision (2026-05-02)**: write-time cascade 미구현. override 적용은 rendering-time lookup 으로 한정한다. R-9 (no new analysis) 보존을 위해 def-use / caller-callee / struct field cascade 는 도입하지 않는다.

> PRD F-2/F-3 의 최종 사용자 가치(SSA use-site rename 전파, type cascade)는 아직 완성되지 않았다.
> Phase 4D 완료 표시는 override 저장/lookup 기반의 scope-confined 완료를 뜻하며, cascade/전파 구현 완료를 뜻하지 않는다.

- [x] 4D.1 Variable Rename — `AuraOverrideView` 의 `aura_override_view_lookup(function_id, VARIABLE, var_id)` 가 rendering 시점 use-site 별 lookup 을 제공. write-time 전파 자료 생성 없음.
- [x] 4D.2 Type Cast — `AURA_OVERRIDE_PAYLOAD_TYPE` 로 단일 record 저장. cascade 미구현.
- [ ] (deferred) cross-run variable matching: `AuraOverrideKey` 에 parent function entry 앵커 추가 + variable 키 derivation 확장. 현재 4E.1 파이프라인에서 variable target 은 ORPHAN 처리.
- [ ] (deferred) caller/callee/struct field cascade: 엔진이 노출하는 관계 record (현재 collection 에 명시적이지 않음) 가 정해진 이후 별도 design pass.

---

### Phase 4E — Re-analysis Pipeline  `[-]` *(4E.1 완료 2026-05-02; 4E.2 Phase 5 이관)*

**Conservative matching policy (2026-05-02)**: function 은 stable_id 또는 entry address exact match 만 사용. name fallback 금지. variable 은 parent function exact match 후 var_id 매칭 (현재 미지원, 4D 후속). fingerprint mismatch → CONFLICT. ambiguous match → ORPHAN.

- [x] 4E.1 재분석 시 override 재적용 파이프라인 (`include/override_pipeline.h`, `src/core/override_pipeline.c`) — `aura_override_resolve_pass()` 가 (fingerprint, engine_id) 매칭 row 를 walk 하여 entry exact match 결과로 status 를 ACTIVE/CONFLICT/ORPHAN 으로 업데이트. stats 반환 (evaluated/applied/conflict/orphan/unchanged). Variable target 은 4D 후속 의존으로 ORPHAN.
- [ ] 4E.2 conflict/orphan 사용자 해결 UI flow → **Phase 5 GUI 작업**으로 이관 (2026-05-02 결정). Phase 4 에서는 status 저장/조회/분류 API 까지만 제공.

---

## Phase 5/6/7/8 — Deferred or scrapped

본 phase 들은 2026-05-03 외부 도구 오케스트레이션 pivot 으로 무효화되거나 보류됨.
원래 의도 / 부활 조건 / 후속 phase 매핑은 별도 문서:

> **[Tasks_deferred.md](./Tasks_deferred.md)**

요약:
- **Phase 5 (GUI Integration)** = 🔄 reborn — Phase 11.3~11.6 으로 분해 후 80% 완료. 잔여 = 5.5 GUI 엔진 dropdown / 5.6 Trace graph 뷰 (백로그 후보).
- **Phase 6 (Secondary Engine Adapters: RetDec / Capstone)** = ⏸️ deferred — 현재 primary 만으로 충분.
- **Phase 7 (Multi-engine Compare)** = ⏸️ deferred. 단 옛 7.1 (decompile compare) 는 폐기, **신 7.1 (angr `symbolic` request type)** 만 신규 phase 로 살아남음 (ROADMAP 백로그).
- **Phase 8 (Performance / mmap)** = ⏸️ deferred — mmap = D-6 완료, concurrency = Phase 11.5 SessionManager 흡수 예정.

---

## Phase 9 — Platform Coverage (Windows MSVC + Linux Tier 1)  `[-]` *(2026-05-03 시작)*

**목표**: ADR-0030 Tier-based Platform Support Policy 의 실행. Linux WSL + Windows MSVC 양립 지원 + 매 PR ctest GREEN 게이트.

**상세 운영**: 본 Phase 는 Matt Pocock 워크플로우로 운영. 본 Tasks.md 에는 thin entry 만 두고 sub-step 단위 진행 상황은 다음에서 관리한다:

- **PRD**: [`.scratch/platform-coverage/PRD.md`](.scratch/platform-coverage/PRD.md)
- **Issues**: [`.scratch/platform-coverage/issues/`](.scratch/platform-coverage/issues/) — 10개 vertical-slice issue (01~10)
- **ADR**: [`docs/adr/0030-tier-platform-policy.md`](docs/adr/0030-tier-platform-policy.md)
- **Live status**: [`AUTOMATION_ROADMAP.md`](AUTOMATION_ROADMAP.md) §활성 작업

> 본 Phase 는 issue-tracker 기반으로 운영되는 첫 사례. 산출이 효과적이면 Phase 5+ 도 동일 방식 적용.

**선행 점검**: [`.scratch/phase-1-4-audit/summary.md`](.scratch/phase-1-4-audit/summary.md) — Phase 1~4 재점검 결과 (75 sub-step Linux WSL GREEN 확인 + Windows MSVC 결함 7건 식별).

**참조**: rules.md §1 (Tier 1 enforcement), CLAUDE.md §지원 플랫폼.

---

## 핸드오프 / 자동화

본 Tasks.md 는 **release snapshot** (rules.md §11.2). 라이브 진행은 [`AUTOMATION_ROADMAP.md`](AUTOMATION_ROADMAP.md) 우선. 세션 단위 작업 이력은 git log + AUTOMATION_ROADMAP.md 핸드오프 로그로 추적.
