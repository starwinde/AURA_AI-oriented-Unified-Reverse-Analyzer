# AURA — Context

AURA 는 외부 RE 도구 (Ghidra / Rizin 등) 를 오케스트레이션하고 그 결과를
unified model 로 환원해 LLM 에 컨텍스트로 제공하는 도구다. 자체 RE 엔진을
처음부터 구현하지 않는다 (2026-05-03 pivot). 본 문서는 도메인 expert 와
개발자가 같은 단어로 같은 것을 가리키도록 하는 용어 사전이다.

---

## Language

### Engines & adapters

**Adapter**:
외부 RE 도구 1개를 호출해 그 출력을 **Unified Model** 로 환원하는 모듈.
_Avoid_: wrapper, plugin, backend.

**Reference engine**:
Adapter 중 매 PR 게이트가 의존하는 mandatory 1개. 현재 = **Rizin**.
없으면 Tier 1 CI 게이트가 RED.
_Avoid_: primary engine, default backend.

**Rizin execution baseline**:
현재 필수 reference engine 은 fetch script 가 내려받아 검증한 **Rizin
0.8.0 shared64** 이다. 기본 vendored 경로는
`third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe`
(Windows) 이지만, 추출된 바이너리는 Git 에 커밋하지 않는다. rz-ghidra
0.8.0 은 존재할 때 preferred pseudo-C provider 이며, 같은 prefix 의
`lib/rizin/plugins/rz_ghidra_sleigh` 를 `SLEIGHHOME` 으로 사용할 수 있다.
fetch/install script 가 실제 설치하기 전까지 rz-ghidra 자동 설치를 주장하지
않는다. 부재 시 deterministic install guidance 를 표시하고 pseudo-C 를
조작해 만들지 않는다. 0.8.2 계열은 신규 적용 기준이 아니다. 상세 = ADR-0052.

**Optional engine**:
있으면 추가 시나리오를 기여하고, 없으면 해당 시나리오만 SKIP 되는 adapter.
현재 = Ghidra 등. 매 PR 게이트의 RED/GREEN 에 영향 주지 않는다.
_Avoid_: secondary engine, fallback engine.

**Unified Model**:
서로 다른 adapter 가 같은 바이너리에 대해 산출하는 표준 in-memory 표현.
Phase 3 (Ingestion) 의 결과물이며 override / LLM context 의 입력이다.
_Avoid_: IR, AST, analysis result.

### Test & gate vocabulary

**Invariant gate**:
외부 도구 출력의 **계약** (필드 존재, 타입, round-trip 동작) 만 단언하는
화이트박스 통합 테스트. 외부 도구의 byte-level 출력 변동을 흡수한다.
_Avoid_: smoke test, golden test, e2e test.

**Golden test**:
외부 산출물을 사전 저장된 byte-equal reference 와 비교하는 테스트.
**AURA 는 매 PR 게이트로 채택하지 않는다** — Rizin/Ghidra 버전 변동에
취약하기 때문. 향후 stabilization 후 추가 가능.
_Avoid_: snapshot test (다른 의미로 쓰일 수 있음).

**Tier 1 gate**:
ADR-0030 정의 — Linux WSL + Windows MSVC 양 환경에서 빌드 + ctest GREEN
이 매 PR 머지의 강제 조건.

### Frontends

**Frontend**:
`aura_core` 라이브러리를 호출해 사용자에게 노출하는 진입점. AURA 는 두
co-equal frontend 를 갖는다 — **CLI** (mainline, headless) 와 **GUI**
(Qt6, 시각화). 둘 다 같은 `aura_core` orchestrator API 만 사용한다.
_Avoid_: client (daemon 패턴 잔향), shell, UI (모호).

**CLI**:
첫 frontend. one-shot 실행 (REPL/daemon 아님), git-style subcommand
(`aura analyze foo.elf`), JSON-default 출력. binary 이름 = `aura`.
_Avoid_: CUI (한국어 컨벤션이지만 파일/타깃 이름은 영어 표준 사용).

**GUI IPC client**:
`aura gui ...` 서브커맨드. headless 분석을 새로 수행하는 명령이 아니라,
이미 실행 중인 `aura-gui` 의 localhost RPC 서버에 붙어 live GUI 상태를
조작/조회하는 automation surface 다. 포트 기본값은
`$AURA_GUI_RPC_PORT` 또는 `27654`, 토큰 기본값은 `$AURA_GUI_RPC_TOKEN`.
MCP gateway 가 GUI 상태를 재사용할 때의 하위 제어 경로로 사용할 수 있다.
_Avoid_: daemon CLI, remote GUI control.

**GUI**:
두 번째 frontend. Qt6 기반, long-lived process, interactive 시각화.
CLI v1 + LLM 통합 사용사례 1개 검증 후 부트스트랩. v1 표면 =
**project-first 흐름** (`.aura.db` New/Open → Project view 의 binary
list → Add Binary → Analysis Options dialog `Quick`/`Full` → Function
list view). Single `QMainWindow` + `QStackedWidget` (page 0 = Project,
page 1 = Functions). 상세 = ADR-0035 (ADR-0034 supersedes).

v1.1+ (Phase 11.3.1 이후) 표면 확장 =
**Cutter-style dockable workspace** — page 1 을 nested `QMainWindow` 로
교체. 기본 배치는 왼쪽 상단 `Functions / Xrefs`, 왼쪽 하단
`Strings / Symbols / Imports`, 오른쪽 코드 탭
`Decompile / Disassembly / Full Disassembly / CFG / Hex`. 코드 pane 은 기본 syntax highlighting
으로 Decompile 의 C-like token 과 Disassembly 의 address/mnemonic/register/
comment/invalid line 을 구분한다. 함수/참조/심볼/임포트/문자열
브라우저는 Cutter 형식의 `QTreeView`: parent row 는 엔티티 이름 또는
대표값, child row 는 엔진이 제공한 metadata 필드다. GUI 는 없는 값을
추론하거나 0 으로 꾸미지 않고 `-` 로 표시한다. Decompile pane 은
rz-ghidra `pdgj` default → jsdec `pddj` → 텍스트 `pdd` → base Rizin
`pdf` (disasm fallback, Phase 11.3.1.1) 자동 chain, 함수 single-click
갱신, 세션 메모리 캐시. Disassembly 는 두 층: 선택 함수 단위 `pdfj/pdf`
뷰와, Cutter처럼 함수 목록 옆에서 연속 VA listing 을 보여주는
`Full Disassembly` 탭. 내부 구현은 Rizin `pdj <count>` structured stream 과
bounded `pD 4096` arrow text 를 함께 가져오며, `Structured` 는 `pD` 를
mixed listing 으로 분류해 invalid/data/comment/label 줄도 보존한다.
UI 는 `Structured` / `With arrows` 탭과 함수 선택 → 해당 위치 스크롤 방식이다.
Chunk cache / lazy paging 은 아직 후속이다. Dark `QPalette` default. `QSettings` 로 dock / window
상태와 언어 설정을 영속. 상세 = ADR-0036.

**Strings protection UI**:
문자열 기반 MVP 의 보호 UI 는 별도 Safety 탭이 아니라 기존 `Strings` 탭에 귀속한다.
parent row 는 기존 문자열 엔티티 요약과 보호 상태/Mask Token 요약을 보여주고,
child row 는 엔진 metadata 를 기존처럼 유지한다. 보호 관련 child row 는 최하단에
`기존`, `별칭`, `마스킹` 순서로 배치한다. 원문을 담는 `기존` row 는 민감정보 상세
표시 설정이 켜진 경우에만 노출하고 기본값은 숨김이다. 상세 = ADR-0055.

**GUI RPC server**:
`aura-gui --rpc-port <port>` 또는 `$AURA_GUI_RPC_PORT` 로 opt-in 되는
로컬 JSON-line TCP 서버. `127.0.0.1` 에만 bind 하고 모든 request 는 token
을 요구한다. 목적은 테스트/자동화/CLI attach 이며, LLM/agent 에 직접
노출하는 공용 API 가 아니다.

**LLM Privacy Filter & Policy Gateway**:
현재 MCP V1 은 별도 실행 파일 `aura-mcp` 로 제공되는 local stdio JSON-RPC
server 다. `AURA_REPO_ROOT` 로 repo root 를 찾아 local `aura` CLI 를 호출하고,
binary-file tool 은 `AURA_MCP_ALLOWED_ROOTS` allowlist 가 없거나 비어 있으면
fail-closed 된다. 현재 노출 surface 는 probe/info/analyze/function detail
중 구현된 bridge tool 이며, raw disassembly/decompile tool 은 등록되어도
의도적으로 deny 된다. LLM/agent 는 Rizin/rz-ghidra 또는 GUI RPC 에 직접
접근하지 않고 MCP tool 을 호출한다. 현재 gateway 가 적용하는 정책은 path
allowlist, 민감 문자열 masking, function detail 의 raw text/op_str 생략,
raw tool denial 이다. 사용자 승인, audit logging, raw 반환 승인 경로는
아직 구현된 기능이 아니라 후속 정책 확장 대상이다. Privacy Filter 는 현재
문자열 기반 MVP 에서 시작하고, 목표 구조는 **Token
Classification Model, Rule Pack, Eval Dataset 을 결합한 민감정보 마스킹
시스템**이다. 기본 생성형 LLM 배치는 **1개**이며, gateway 는 두 번째 생성형
LLM 모델이 아니라 policy layer 다.
_Avoid_: "중간에 LLM 모델을 배치", "2개 LLM 상시 운영" (보안 주체는 생성형 LLM 이 아니라 PII/privacy filter + policy gateway).

**Strict MCP Coverage**:
새 분석 도구, 분석 데이터, 자동화 명령, export 기능이 추가되면 `aura-mcp`
surface 도 반드시 함께 추가/수정한다. MCP 반영이 없으면 해당 작업은
"완료"가 아니라 "GUI/CLI 선행 구현" 또는 "MCP Pending" 상태다. 단, 창 배치,
색상, 탭 순서 같은 순수 GUI-only polish 는 분석 데이터나 자동화 계약을 바꾸지
않는 한 MCP 변경 대상이 아니다. 상세 = ADR-0057.

**MCP Surface**:
LLM/agent 가 호출할 수 있는 MCP tool/resource/prompt 와 schema. GUI tab 이
아니라 **Unified Model** record 와 **Safety Core** export-safe view 를 기준으로
정의한다. 예: functions, strings, decompile, disassembly, xrefs 같은 분석
record 단위. _Avoid_: screen scraping API, GUI widget API.

**MCP Schema Envelope**:
모든 MCP 응답이 공유하는 최상위 JSON 구조. 최소 필드는
`mcp_schema_version`, `tool_schema_version`, `kind`, `status`, `data`,
`warnings`, `disclosure` 다. tool 별 payload 는 `data` 아래에 두며, engine 별
차이는 기본 field 를 바꾸지 않고 `extensions` 또는 raw artifact reference 로
격리한다.

**MCP Schema Version**:
MCP 전체 공통 envelope 의 버전. 예: `mcp_schema_version = "1.0"`. 모든 MCP tool
응답에 공통 적용되며, envelope 자체의 breaking change 가 있으면 major version 을
올린다.

**Tool Schema Version**:
개별 MCP tool payload 의 버전. 예: `tool_schema_version = "strings.list/1.0"`.
`list_strings` 와 `get_decompile` 처럼 tool 별 payload 변경 속도가 다르기 때문에
MCP 전체 버전과 분리한다.

**MCP Kind**:
응답이 어떤 tool/result 계열인지 나타내는 안정 문자열. 예:
`strings.list`, `decompile.get`, `disassembly.get`. UI tab 이름이 아니라 MCP
contract 이름이다.

**MCP Status**:
MCP tool 실행 결과 상태. 기본값은 `ok`, 실패는 `error`, 일부 결과만 반환된 경우는
`partial` 을 사용한다. 상세 실패 원인은 error payload 또는 warning 으로 분리한다.

**MCP Data**:
tool 별 실제 payload 를 담는 envelope field. 공통 metadata(`schema_version`,
`status`, `disclosure`, `warnings`, `audit`) 와 분리해 client 가 payload 범위를
명확히 알 수 있게 한다.

**MCP Warning**:
요청은 성공했지만 사용자가 알아야 할 제한, 누락, truncation, unavailable 상태를
나타내는 구조화 메시지. 없는 값을 AURA 가 추론해 채우지 않고 warning 으로 노출한다.

**MCP Disclosure**:
응답 데이터의 노출 등급. 기본값은 `protected`. 원문 접근 승인을 거친 응답은
`raw_approved` 를 사용한다. raw-access toggle 이 꺼져 있거나 승인이 없으면 raw
disclosure 응답을 만들 수 없다.

**MCP Extensions**:
base record 를 바꾸지 않고 engine/tool 별 추가 정보를 담는 namespace. 예:
`extensions.rizin`, `extensions.ghidra`. MCP client 는 모르는 extension 을 무시해야
한다.

**Raw Artifact Reference**:
raw stdout, raw XML, engine native IR 처럼 크거나 engine-specific 한 원본 산출물을
직접 payload 에 넣지 않고 참조하는 식별자. base record 는 이 참조만 들고, 실제 raw
artifact 접근은 별도 정책과 권한을 따른다.

**Base Record**:
engine 과 무관하게 유지되는 AURA 표준 record. Function/String/Symbol/Xref/
Decompile/Disassembly 같은 공통 field 만 포함한다. engine native field 는 base
record 에 넣지 않는다.

**Engine Native Field**:
Rizin/Ghidra/x64dbg/angr/RetDec 중 특정 engine 에만 존재하거나 의미가 다른 field.
base record 에 직접 추가하지 않고 `extensions.<engine_id>` 또는 raw artifact 로
격리한다.

**Engine-Agnostic Record Contract**:
Rizin/Ghidra/x64dbg/angr/RetDec 등 다른 RE engine/model 로 바뀌어도 MCP 와 core
service 의 기본 record 구조가 바뀌지 않도록 하는 계약. engine native field 는
base record 에 넣지 않고 `extensions.<engine_id>` 또는 raw artifact reference 로
둔다. _Avoid_: engine-specific base struct, screen-derived schema.

**MCP Additive Change**:
기존 field 의미와 타입을 유지하면서 optional field, extension, warning, enum 값을
추가하는 schema 변경. client 는 unknown field 를 무시하고 unknown enum 은
`unknown` 으로 처리해야 한다.

**MCP Breaking Change**:
기존 field 삭제, 이름 변경, 타입 변경, 의미 변경, 필수 field 추가처럼 기존 client 를
깨는 schema 변경. major schema version bump 없이는 금지한다.

**Protected MCP Tool**:
기본 MCP tool. 분석 데이터를 반환할 때 원문 문자열/code text 를 직접 노출하지
않고 **Protected String View** 또는 Safety Core 의 export-safe view 를 사용한다.

**Privileged MCP Tool**:
원문 문자열, 원문 decompile, 원문 disassembly text 처럼 민감할 수 있는 raw data
를 반환할 수 있는 별도 MCP tool. 기본 비활성화이며 raw-access session toggle,
요청별 사용자 확인, bounded scope, audit logging 이 모두 필요하다.

**Raw-Access Session Toggle**:
사용자가 현재 session 에서 privileged raw 접근 가능성을 켜는 전역 스위치. 기본값은
OFF. 이 toggle 이 ON 이어도 요청별 사용자 확인 없이는 raw data 를 반환할 수 없다.

**Per-Request Approval**:
Privileged MCP Tool 이 실제 raw data 를 반환하기 직전에 받는 사용자 확인. 호출자,
tool, project, target stable id, 반환 범위, byte/line/count limit, 요청 목적을
보여준 뒤 승인받아야 한다.

**Bounded Scope**:
raw 반환의 최대 범위 제한. 예: 문자열 N개, decompile N라인, disassembly N바이트.
전체 DB dump, 전체 decompile dump, 전체 disassembly dump 는 bounded scope 가
아니므로 금지한다.

**Approval ID**:
Per-Request Approval 1건을 식별하는 audit id. Raw Disclosure Event 에 기록되며,
어떤 raw 반환이 어떤 사용자 승인에 의해 발생했는지 추적한다.

**Raw Disclosure Event**:
Privileged MCP Tool 이 원문 데이터를 반환한 사실을 남기는 audit event. 원문 값은
저장하지 않고 project id, caller/tool, target stable id, 범위, 길이/count/hash,
timestamp, approval id 같은 메타데이터만 저장한다.

**MCP Caller**:
MCP tool 을 호출한 외부 LLM/agent/client 식별자. audit 과 approval UI 에 표시한다.
신뢰 결정을 caller 이름만으로 하지 않고 policy/approval 과 함께 판단한다.

**Target Stable ID**:
raw 또는 protected data 요청 대상이 되는 AURA record 의 stable id. 주소나 화면
row 번호보다 우선 사용하며, audit log 에 원문 값 대신 기록한다.

**MCP Security Regression Gate**:
MCP 관련 Analysis Capability 가 feature complete 로 인정받기 위해 통과해야 하는
보안 회귀 테스트 묶음. smoke test 만으로는 충분하지 않으며, schema, protected
default, raw 차단/승인, bounded scope, audit, engine-agnostic stability 를 함께
검증한다.

**MCP Schema Envelope Test**:
모든 MCP 성공 응답이 `mcp_schema_version`, `tool_schema_version`, `kind`, `status`,
`data`, `warnings`, `disclosure` 를 포함하는지 검증하는 테스트.

**MCP Error Envelope Test**:
권한 없음, raw-access toggle OFF, approval 없음, 범위 초과, project 없음 같은 실패
응답도 stable schema 를 갖는지 검증하는 테스트. 실패 원인을 문자열만으로 뭉개지 않고
구조화된 error payload 로 반환해야 한다.

**Protected Default Test**:
기본 MCP tool 의 `disclosure` 가 `protected` 이며, raw data 를 반환하는 privileged
path 로 자동 승격되지 않는지 검증하는 테스트.

**Raw Non-Disclosure Test**:
Protected MCP Tool 응답에 원문 문자열/code text 가 포함되지 않는지 검증하는 테스트.
이메일, API key, 내부 경로, URL/IP 같은 민감 샘플을 사용한다.

**Privileged Raw Denial Test**:
Raw-Access Session Toggle 이 OFF 인 상태에서 Privileged MCP Tool 이 raw data 를
반환하지 않고 구조화된 error 를 반환하는지 검증하는 테스트.

**Per-Request Approval Test**:
Raw-Access Session Toggle 이 ON 이어도 Per-Request Approval 이 없으면 raw data 를
반환하지 않는지 검증하는 테스트.

**Bounded Scope Test**:
Privileged MCP Tool 이 전체 DB/decompile/disassembly dump 를 거부하고, 문자열 N개,
decompile N라인, disassembly N바이트 같은 제한을 강제하는지 검증하는 테스트.

**Raw Disclosure Audit Test**:
승인된 raw 반환이 발생했을 때 Raw Disclosure Event 가 생성되고, audit log 에 원문 값
자체가 저장되지 않는지 검증하는 테스트.

**Engine-Agnostic Schema Test**:
Rizin/Ghidra/x64dbg/angr/RetDec 등 engine/model 이 바뀌어도 Base Record 와 MCP
Schema Envelope 의 필드 의미와 타입이 유지되고, engine-specific 정보가
`extensions.<engine_id>` 또는 Raw Artifact Reference 로만 들어가는지 검증하는 테스트.

**MCP Compatibility Test**:
MCP Additive Change 가 기존 필드를 깨지 않고, unknown field/unknown enum 을 client 가
무시하거나 `unknown` 으로 처리할 수 있는지 검증하는 테스트.

**Analysis Capability**:
Strict MCP Coverage 대상이 되는 기능 단위. 새 engine adapter, request/response
type, 분석 record/field/cache/DB table, CLI/GUI IPC 자동화 명령, LLM/export 로
전달 가능한 데이터, Privacy Filter/Policy Gateway/audit/masking 에 영향을 주는
변경을 포함한다. 순수 visual polish 는 제외한다.

**MCP Pending**:
Analysis Capability 의 GUI/CLI/Core 구현은 되었지만 MCP surface 와 MCP test 가
아직 따라오지 않은 상태. merge 가능 여부는 별도 판단할 수 있으나 feature
complete 또는 졸업작품 시연 완료 상태로 표기하지 않는다.

**Token Classification Model**:
외부 LLM 으로 전달하기 전 문자열 안의 PII span 을 탐지하는 NER/token
classification 계열 모델. 예: `openai/privacy-filter`. 생성형 LLM 이 아니며,
AURA 기본 설치 기준에서는 모델 파일을 repository 나 `third_party/` 에 넣지
않고 사용자 홈의 `~/.aura/token-classification-models/` 아래 런타임 자산으로
둔다. 기본 프로필은 `openai-privacy-filter` 를 가리키되 교체 가능해야 한다.
초기 탑재는 Python venv 기반 외부 CLI runner 로 수행하며, Python/모델 런타임은
`aura_core` 에 embed/link 하지 않는다. 상세 = ADR-0054, ADR-0058.

**AURA-managed Python Venv**:
AURA 가 runtime asset 으로 관리하는 전용 Python virtual environment. PII 모델
실행은 system Python 이 아니라 이 venv 의 Python 으로만 수행한다. system Python 은
venv bootstrap 후보로만 사용하며 모델 실행 fallback 이 아니다. v1 PII runner env 는
`pii-python-venv`, 기본 위치는 `~/.aura/runners/pii-python-venv/` 다.

**Runner Environment Bootstrap**:
`aura safety bootstrap-runner --runner pii-python-venv` 처럼 명시 명령으로 runner
venv 를 생성/검증하는 절차. 일반 분석/export 중 자동 venv 생성이나 package install 은
금지한다. 기본은 `tools/pii-runner/requirements.lock.txt` 기준 검증이며, 네트워크
사용은 명시 옵션이 있을 때만 허용한다.

**Rule Pack**:
민감정보 탐지를 위한 정규식, 후처리 조건, confidence 기준,
allowlist/denylist, 테스트 샘플을 묶은 규칙 패키지. 예:
`korean-sensitive`, `secret-api-key`. Rule Pack 은 **규칙 데이터**이며,
이를 실행하는 코드는 Rule Pack Engine, 실행 결과는 Rule Finding 이다.
모델이 아니고 탐지 결과도 아니다. repository 는 작은 기본 rule pack 과
manifest 를 제공할 수 있고, 사용자 추가 rule pack 은
`~/.aura/rule-packs/` 에 둔다. 모델이 놓치기 쉬운 한국형 개인정보,
API key, token, DB URI 같은 형식 기반 민감정보를 보완한다.

**Rule Finding**:
Rule Pack Engine 이 문자열에 Rule Pack 을 적용해 만든 민감정보 후보. 예:
`finding_kind=email`, `kr_rrn`, `api_key`, `jwt`. 최소 필드는 detector_id
(`rule/korean-sensitive/kr_rrn` 등), source=`rule`, finding_kind, start_offset,
end_offset, confidence, mask_token 후보. Rule Finding 은 원본 문자열을 직접
바꾸지 않고, `string_protection_findings` 에 저장될 수 있다. 최종 치환은
Finding Merger 와 Mask Token Allocator 이후 적용한다.

**Model Finding**:
Token Classification Model 이 문자열에서 탐지한 민감정보 후보. Rule Finding
과 같은 후보 계층이지만 source=`model` 이며 detector_id 는 model profile/model id
를 가리킨다. `start`/`end` offset 은 v1 에서 `utf8_byte` 기준이다. 최종
저장/마스킹 단계에서는 Rule Finding 과 함께 병합된다.

**Model Finding Normalizer**:
Python runner 내부에서 raw transformers token/entity output 을 AURA 표준
Model Finding 으로 바꾸는 정규화 계층. BIO prefix 제거, label→finding kind 매핑,
kind 별 threshold 적용, unknown label drop, UTF-8 byte offset 변환, 잘못된 span 제거를
수행한다. stdout 으로는 normalizer 를 통과한 Model Finding JSON 만 나가며,
C++ core 는 이를 다시 schema/span/kind/confidence 기준으로 검증한다.

**Standard Finding Kind Vocabulary**:
Rule Finding 과 Model Finding 이 공유하는 v1 finding kind 목록. 현재 값은
`email`, `phone_number`, `kr_rrn`, `api_key`, `token`, `url`, `ip_address`,
`internal_path`, `person_name`, `address`, `organization`, `account_id`,
`customer_id`, `unknown_sensitive` 다. repo 기본 rule pack 과 model normalizer 는 이
vocabulary 를 strict 하게 따라야 하며, 사용자 rule pack 의 unknown kind 는
`unknown_sensitive` 로 낮추고 warning 을 남긴다.

**Finding Merger**:
Rule Finding 과 Model Finding 을 하나의 최종 finding 후보 목록으로 병합하는 단계.
겹치는 span 병합, 더 긴 span 우선, confidence/source 우선순위 적용, 같은 원문/같은
위치 중복 제거, finding_kind 정규화를 수행한다. 원본 문자열을 바꾸지 않고, 최종
마스킹 문자열도 만들지 않는다. 결과는 Mask Token Allocator 로 전달할 후보 목록이다.

**Mask Token Allocator**:
Finding Merger 가 남긴 후보에 `[EMAIL_1]`, `[KR_RRN_1]`, `[SECRET_1]` 같은
Mask Token 을 부여하는 단계. 기본 정책은 label-numbered + same-value-same-mask 이다.
원본 문자열을 직접 변형하지 않고, Protected String View 생성 시 사용할 치환 mapping 을
만든다.

**Eval Dataset**:
민감정보 탐지/마스킹 성능을 검증하기 위한 입력 샘플과 기대 탐지 결과의
묶음. 모델을 학습시키기 위한 training dataset 이 아니라, AURA 필터가 잘
동작하는지 확인하는 테스트셋이다. 최소 구성은 input_text, expected_findings,
non_sensitive_cases, expected_masked_text 또는 expected_mask_tokens, tags,
locale, source. 모델만, rule pack 만, model+rule 결합의 탐지율/오탐률/마스킹
일관성을 비교한다. 기본/한국형/사용자 추가 dataset 을 분리하며 런타임 위치는
`~/.aura/eval-datasets/` 이다. 실행 코드는 Eval Runner, 결과물은 Eval Report 다.

**Safety Profile**:
사용할 Token Classification Model, Rule Pack 목록, Eval Dataset 목록, masking
정책(`label_numbered`, same-value-same-mask 등)을 묶은 설정 단위. 모델,
rule pack, dataset, detector 자체가 아니라 **무엇을 사용할지 선택하는
configuration** 이다. 기본 위치는 `~/.aura/safety-profiles/default.json`
이며, repository 에는 기본 profile template 을 둘 수 있다. `model_policy.mode` 는
`disabled`/`conditional`/`required` 를 사용한다. `conditional.run_when` 은 OR 이며,
`external_export`, `rule_findings_empty`, `contains_natural_language` 같은 condition 을
지원한다. `degrade` 는 Rule Pack-only 결과로 계속 진행하고 structured warning 을
남기는 정책이며, `block_export` 는 외부 LLM/MCP/export payload 생성을 차단한다.

**Safety Warning**:
Privacy Filter 정책 실행 중 사용자가 알아야 하는 제한, 모델 실패, degrade,
block_export 상태를 나타내는 구조화 메시지. Engine mapping-loss 전용
`AuraDiagnostics` 와 분리한다. 최소 의미 필드는 warning_code, severity, scope,
model_id, action, export_blocked, message, remediation 이며, MCP 에서는 envelope
`warnings[]`, CLI 에서는 stderr 또는 JSON `warnings[]`, GUI 에서는 Safety 상태 표시로
렌더링한다. 문구는 problem/cause/fix 를 포함해야 한다.

**Safety Profile Loader**:
Safety Profile JSON 을 읽어 AURA 내부 설정 구조로 바꾸는 loader. 탐지/마스킹을
직접 수행하지 않는다. loader 의 책임은 profile schema 검증, runtime asset 경로
해결, 선택된 Token Classification Model/Rule Pack/Eval Dataset/Masking Policy
목록 반환까지다.

**Safety core module layout**:
Privacy Filter 관련 공용 로직은 GUI 가 아니라 core 에 둔다. Public API 는
`include/aura/safety/`, 구현은 `src/core/safety/` 아래에 둔다. 예:
`safety_profile`, `rule_pack`, `finding`, `finding_merger`,
`mask_token_allocator`. GUI/CLI/MCP 는 이 API 를 호출하고, GUI 는 표시와 사용자
입력만 담당한다. 상세 = ADR-0056.

**Safety detection pipeline**:
최종 실행 구조는 원본 문자열을 Rule Pack Engine 과 Token Classification Model
Adapter 가 각각 검사하고, Rule Finding + Model Finding 을 Finding Merger 에서
병합한 뒤 Mask Token Allocator 와 Protected String View 로 넘기는 방식이다.
모델은 마스킹된 문자열이 아니라 원본 문자열을 검사한다. 구현 순서는 risk control
때문에 Rule Pack 경로를 먼저 완성하지만, Token Classification Model Adapter 도
Phase 13 의 같은 목표 구현 대상이다. 초기 Model Adapter 는 Python venv runner
subprocess 를 batch scan 으로 호출하고 normalized Model Finding JSON 만 수신한다.

**Protected String View**:
원본 `AuraStringRecord` 를 직접 바꾸지 않고, GUI/IPC/MCP/LLM 경로에서 표시하거나
전달하기 위해 만든 안전한 문자열 표현. `analysis_strings` 의 원본값,
`string_overrides` 의 사용자 별칭/마스킹 토큰, `string_protection_findings` 의
탐지 근거를 조합해 만든다. 상세 = ADR-0053.

**Headless Engine API**:
GUI 를 실행하지 않고 project DB / Unified Model / adapter pipeline 을 통해 분석
결과를 얻는 내부 API. `aura-mcp` 는 가능하면 이 경로를 우선 사용하고, live GUI
상태나 selection 이 필요한 경우에만 **GUI IPC client** 를 하위 transport 로 쓴다.

**String Alias**:
사용자가 문자열 의미를 이해하기 쉽게 붙이는 별칭. 예: `customer_email`.
사람을 위한 표시값이므로 외부 전달 안전값으로 간주하지 않는다. 사용자가
민감정보를 다시 적을 수 있기 때문이다.
_Avoid_: mask, redaction token.

**Mask Token**:
민감 문자열을 외부 LLM/MCP 로 전달할 때 원본 대신 쓰는 안정 토큰. 예:
`[EMAIL_1]`, `[PHONE_1]`. detector finding 과 연결되며, 외부 전달 경로에서는
String Alias 보다 우선한다.
_Avoid_: alias, rename.

**String protection persistence**:
문자열 보호 1차 DB 기준은 `analysis_strings`, `string_overrides`,
`string_protection_findings` 세 테이블이다. `string_references`, render cache,
export audit 는 후속 확장이다. 상세 = ADR-0053.

v1.2 (Phase 11.3.2) 표면 확장 = **Override Editor** — 함수 list 우클릭
context menu 의 `Rename...` / `Reset name`. `QInputDialog` 입력 → 같은
`.aura.db` 의 override_store 에 즉시 commit (Phase 11.4 정책 일관) →
함수 list reload 시 user override 가 Name 컬럼에 표시 (원래 이름은
tooltip, Source 컬럼 = `"user/rename"`). Stable_id 계산은 CLI 의
`build_rich_key` 에서 추출한 `aura_override_identity_build_function_key()`
공유 — co-equal contract (CLI ↔ GUI 동일 키) 보장. Type / annotation /
LLM rename / 전체 list dock = v1.3+. 상세 = ADR-0037.

### Engine routing

**Primary set**:
`aura_orchestrator_select_primary()` 가 노출하는 request type 별 engine
우선순위 정책표 (Phase 2A R-8). 예: ANALYZE → {rizin}, DECOMPILE →
{rizin, ghidra}. **Reference engine 과 다른 개념** — Reference engine 은
"Tier 1 게이트가 의존하는 mandatory adapter" 를 가리키고, primary set 은
"request type 별 dispatch 우선순위" 를 가리킨다. 단어 "primary" 는 후자에서만
사용한다 (단수형 "primary engine" 은 reference engine 의 alias 로 사용 금지).

**Multi-decompiler serving**:
같은 함수에 대해 Rizin/rz-ghidra, Ghidra, RetDec 등 복수 decompiler 결과를
동시에 요청·보존·표시하는 최종 목표. 현재 필수 baseline 은 Rizin 0.8.0
shared64 이고, rz-ghidra 0.8.0 은 설치되어 있을 때 preferred pseudo-C
provider 이며 최종 범위 축소가 아니다.
비교는 display-only 이고, AURA 가 결과를 merge/vote 하거나 "정답"으로
자동 정정하지 않는다. 상세 phase 번호와 CLI/GUI surface 는 향후 ADR 에서
확정한다.

### External tool acquisition

**External tool manifest**:
`third_party/<tool>/manifest.json` — version + 플랫폼별 SHA256 + 다운로드 URL
을 담은 단일 파일. fetch script + CI workflow + 로컬 dev 셋이 모두
이 파일을 single source of truth 로 참조.

**Fetch script**:
`scripts/fetch_external_tools.{sh,ps1}` — manifest 를 읽어 prebuilt 를
`third_party/<tool>/<version>/` 로 다운로드·검증·추출. CMake 의존 그래프
밖에서 실행되며, CI 는 cmake configure 전에 1회 호출한다.
현재 계약상 Rizin 0.8.0 은 이 경로로 획득되어야 한다. rz-ghidra 0.8.0 은
preferred pseudo-C provider 이지만 fetch/install script 가 실제 설치하기
전까지 자동 설치 보장으로 설명하지 않는다.

**Override**:
사용자가 unified model 의 한 요소 (예: 함수 이름) 를 영속적으로 재정의한
사실. Phase 4B SQLite store 에 저장되고 Phase 4D 가 렌더링 시점에 적용한다.
_Avoid_: rename, annotation, patch.

### Project & analysis vocabulary

**Project**:
사용자의 분석 작업 단위. 단일 `.aura.db` SQLite 파일로 표현되며
override + `project_binaries` 테이블 (Phase 11.3) 을 담는다. CLI 의
`--project foo.db` 와 GUI 의 New/Open Project 메뉴가 같은 단위를
가리킨다. **디렉토리 아님** (Ghidra `.gpr` + `.rep/` 와 다름).
_Avoid_: workspace, session, repository.

**Analysis level**:
ANALYZE request 의 `analysis_level` enum. v1 = `QUICK` (Rizin `aa`)
/ `FULL` (Rizin `aaa`, default). GUI 의 Analysis Options dialog 슬라이더
가 노출. v2 에서 4단계 + 옵션 체크박스로 확장 예정. Default = `FULL`
이라 Phase 10/11.1/11.4 ctest 영향 0.
_Avoid_: analysis depth, analysis mode (모호).

---

## Relationships

- 한 **Adapter** 는 한 외부 도구를 감싸 한 **Unified Model** 을 산출한다.
- **Reference engine** 은 **Adapter** 의 부분집합 (현재 Rizin 단일 원소).
- **Override** 는 **Unified Model** 위에 layered 되어, 같은 model 을 다른
  표현으로 보이게 한다 (model 자체는 불변).
- **Invariant gate** 는 (**Reference engine** → **Unified Model** → **Override**
  round-trip → JSON 직렬화) 파이프라인을 단언한다.
- **External tool manifest** 는 **Reference engine** 과 future **Optional
  engine** 모두에 동일 패턴으로 적용된다.
- **CLI** 와 **GUI** 는 같은 `aura_core` API 의 co-equal consumer. 둘 사이
  직접 의존 없음.
- **MCP Surface** 는 **GUI** 화면 구조가 아니라 **Unified Model** 과
  **Safety Core** export-safe view 를 기준으로 정의한다.
- **Engine-Agnostic Record Contract** 는 새 engine/model 추가 시 base
  struct/schema 변경을 막고, engine 차이를 extension boundary 로 격리한다.
- **Strict MCP Coverage** 는 새 **Analysis Capability** 가 GUI/CLI 에만 머물러
  LLM/agent 경로와 drift 되는 것을 막는 완료 기준이다.
- **Primary set** 은 **CLI** 의 `--engine` 미지정 dispatch 와 **GUI** 의
  엔진 드롭다운 default 양쪽이 참조한다.

---

## Example dialogue

> **Dev:** "Ghidra 가 호스트에 없으면 PR 머지가 막히나요?"
> **Owner:** "아니요. Ghidra 는 **optional engine** 이라 시나리오가 SKIP 될
> 뿐 **Tier 1 gate** 는 GREEN. **Reference engine** 인 Rizin 만 mandatory."
>
> **Dev:** "그럼 Rizin 버전이 올라가서 함수 이름 prefix 가 `fcn.` → `sym.` 로
> 바뀌면 게이트가 깨지나요?"
> **Owner:** "안 깨져야 합니다. 우리는 **golden test** 가 아니라 **invariant
> gate** 라서, '함수 ≥ 1, entrypoint 존재' 같은 계약만 단언해요. byte-level
> 변동은 의도적으로 흡수합니다."

---

## Flagged ambiguities

- 과거 문서에서 "Phase 2~3 baseline" 이 사실상 Ghidra 우대로 읽혔으나,
  ADR-0031 로 **Reference engine = Rizin** 확정. Ghidra 는 **optional**.
- "smoke test" 분류 어휘로는 사용 금지 — **invariant gate** 또는 **golden
  test** 중 어느 의미인지 모호함. 단 디렉토리 / CMake target / CI workflow
  이름 (예: `tests/integration/orchestrator_smoke/`, `cli_smoke`) 의
  관습적 표기로는 허용. 분류는 여전히 **invariant gate**.
- "primary engine" (단수) 은 사용 금지 — **reference engine** 또는
  **primary set** 중 정확한 쪽을 사용. 코드의 `aura_orchestrator_select_primary`
  함수는 **primary set** 의미.
- "CUI" 는 자연어 대화에서는 허용하나 코드 / 디렉토리 / target / 문서에서는
  **CLI** 사용.
- "external dependency" 가 빌드 링크 의존성 (cJSON, SQLite) 과 외부 런타임
  도구 (Rizin, Ghidra) 양쪽에 사용됨. 후자는 명시적으로 "**external tool**"
  로 지칭 (manifest 패턴 적용 대상).
