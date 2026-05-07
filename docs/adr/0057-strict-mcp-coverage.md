# ADR-0057: Strict MCP Coverage Policy

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0038, ADR-0053, ADR-0054, ADR-0056, PRD D-37, PRD D-39

## Context

AURA 의 차별점은 RE GUI 하나가 아니라, 검증된 RE engine 결과를 Unified
Model 로 모으고 GUI / IPC / MCP / LLM 안전 계층에서 일관되게 사용하는 데
있다. 새 분석 기능이 GUI 나 CLI 에만 추가되고 MCP 에 반영되지 않으면
LLM/agent 경로는 계속 뒤처지고, AURA 의 "안전한 자동화 gateway" 정체성이
약해진다.

반대로 모든 시각적 UI 변경까지 MCP 변경을 요구하면 창 배치, 색상, 탭 순서
같은 순수 presentation 작업에도 불필요한 schema churn 이 생긴다. 따라서
MCP coverage 의 강한 기준과 예외 범위를 명확히 정의한다.

## Decision

AURA 는 **Strict MCP Coverage** 를 채택한다.

새 **Analysis Capability** 가 추가되면 MCP surface 도 반드시 함께 추가하거나
수정한다. MCP 반영이 없으면 해당 작업은 "완료"가 아니라 **GUI/CLI 선행
구현** 상태로 본다.

Analysis Capability 는 다음 중 하나를 뜻한다.

- 새 RE engine adapter 또는 기존 adapter 의 새 request/response type
- 새 분석 데이터 record, field, normalized model, cache, DB table
- CLI/GUI IPC 에서 호출 가능한 새 자동화 명령
- 외부 LLM/agent/export 경로에서 소비할 수 있는 새 데이터
- Privacy Filter, Policy Gateway, audit, masking 결과에 영향을 주는 변경

Strict MCP Coverage 의 예외는 좁게 둔다.

- 창 배치, 색상, splitter 위치, 탭 순서, 단순 label 변경
- 분석 데이터 구조나 자동화 계약을 바꾸지 않는 GUI-only polish
- MCP/LLM/export 로 전달되지 않는 임시 debug UI

예외에 해당하더라도 분석 데이터, 자동화 명령, export payload, privacy policy
중 하나라도 바뀌면 MCP coverage 대상이다.

## Layer Definitions

### Adapter Layer

Rizin, rz-ghidra, Ghidra, x64dbg, angr 같은 외부 도구를 호출하고 raw output 을
AURA 가 다룰 수 있는 형태로 수집한다. Adapter 는 MCP tool 이 아니다.

### Unified Model Layer

서로 다른 adapter 의 결과를 AURA 의 표준 record 로 환원한 계층이다. MCP 는
GUI widget 이 아니라 이 계층의 안정된 record 를 기준으로 노출한다.

### Core Service Layer

Unified Model 위에서 override, cache, lookup, safety 같은 공용 처리를 수행하는
계층이다. Safety Core 도 이 계층에 속한다.

### Safety Core Layer

Rule Pack Engine, Token Classification Model Adapter, Finding Merger, Mask Token
Allocator, Protected String View Builder 를 포함한다. MCP 와 LLM/export 경로는
원문 record 를 직접 내보내지 않고 이 계층의 export-safe view 를 기본 사용한다.

### GUI Layer

사람이 쓰는 Qt 표시 계층이다. GUI 는 원문 표시 옵션이나 Cutter-style 배치 같은
presentation 을 담당할 수 있지만, MCP contract 의 source of truth 가 아니다.

### GUI IPC Layer

`aura gui ...` 로 실행 중인 `aura-gui` 에 붙는 localhost automation/control
surface 다. GUI 상태 재사용, selection 이동, live view 조작에 사용한다. MCP 가
필요하면 하위 transport 로 사용할 수 있지만 MCP 자체와 동일하지 않다.

### MCP Gateway Layer

`aura-mcp` 로 제공할 외부 LLM/agent 용 gateway 다. MCP 는 Rizin/rz-ghidra,
GUI RPC, raw DB 를 직접 노출하지 않는다. allowlist, length limit, masking,
audit, user approval, protected export view 를 적용한 뒤 제한된 tool/resource
contract 만 제공한다.

### MCP Surface

LLM/agent 가 호출할 수 있는 MCP tool/resource/prompt 와 그 schema 를 뜻한다.
예: `list_functions`, `get_function`, `list_strings`, `get_decompile`,
`get_disassembly`. 이름은 구현 phase 에서 확정하되, 기준 단위는 GUI tab 이
아니라 Unified Model record 다.

### MCP Schema Envelope

모든 MCP 응답이 공유하는 최상위 JSON 구조다. 최소 필드는
`mcp_schema_version`, `tool_schema_version`, `kind`, `status`, `data`,
`warnings`, `disclosure` 로 둔다. tool 별 payload 는 `data` 아래에 들어가며,
engine 별 차이는 기본 필드를 바꾸지 않고 `extensions` 또는 raw artifact reference
로 격리한다.

### Engine-Agnostic Record Contract

MCP 와 core service 가 노출하는 기본 record 구조는 특정 RE engine 의 native
구조체를 따르지 않는다. Rizin, Ghidra, x64dbg, angr, RetDec 등 engine 이 바뀌어도
Function/String/Symbol/Xref/Decompile/Disassembly 같은 공통 record 의 필드 의미와
타입은 유지한다. engine 전용 값은 stable base record 를 변경하지 않고
`extensions.<engine_id>` 또는 별도 raw artifact reference 로 둔다.

### MCP Additive Change

기존 필드의 의미와 타입을 유지하면서 새 optional field, 새 warning, 새 extension,
새 enum 값을 추가하는 변경이다. 기존 client 는 모르는 field 와 enum 값을 무시하거나
`unknown` 으로 처리해야 한다.

### MCP Breaking Change

기존 field 삭제, 이름 변경, 타입 변경, 의미 변경, 필수 field 추가, 기존 enum 의미
변경처럼 기존 client 를 깨는 변경이다. Breaking change 는 major schema version
bump 없이는 금지한다.

### Protected MCP Tool

기본 MCP tool 이다. 문자열, decompile, disassembly, symbol 같은 분석 데이터를
반환할 때 원문을 직접 노출하지 않고 Safety Core 의 export-safe view 를 사용한다.

### Privileged MCP Tool

원문 문자열이나 원문 code text 처럼 민감할 수 있는 raw data 를 반환할 수 있는
별도 tool 이다. 기본 비활성화되며, session raw-access toggle 이 켜져 있고
요청별 사용자 확인이 완료된 경우에만 동작한다.

### Raw Disclosure Event

Privileged MCP Tool 이 원문 데이터를 반환한 사실을 나타내는 audit event 다.
project id, caller/tool, target stable id, 범위, byte/line/count limit, timestamp,
approval id 를 기록한다. 원문 값 자체는 audit log 에 저장하지 않는다.

### Headless Engine API

GUI 를 실행하지 않고 project DB / Unified Model / adapter pipeline 을 통해
분석 결과를 얻는 내부 API 다. MCP gateway 는 가능하면 이 경로를 우선 사용하고,
live GUI 상태가 필요한 경우에만 GUI IPC 를 사용한다.

## Schema Stability Policy

MCP schema 는 engine-agnostic contract 를 따른다. 다른 RE engine 또는 RE model 을
추가해도 기본 MCP 구조와 core stable record 구조체를 바꾸지 않는 것을 원칙으로
한다.

공통 응답 envelope 은 다음 형태를 기본으로 한다.

```json
{
  "mcp_schema_version": "1.0",
  "tool_schema_version": "strings.list/1.0",
  "kind": "strings.list",
  "status": "ok",
  "disclosure": "protected",
  "data": {},
  "warnings": [],
  "audit": null
}
```

정책:

1. Base record 는 engine-neutral field 만 가진다.
2. Engine native type, canonical enum, raw AST/IR/decompiler-specific field 는 base
   record 에 직접 추가하지 않는다.
3. Engine 별 추가 정보는 `extensions.<engine_id>` 또는 raw artifact reference 로
   둔다.
4. 기존 field 삭제/이름 변경/타입 변경/의미 변경은 MCP Breaking Change 다.
5. 새 optional field, 새 extension, 새 warning, 새 enum 값은 MCP Additive Change 다.
6. Client 는 unknown field 를 무시하고 unknown enum 을 `unknown` 으로 처리해야 한다.
7. 필드가 없다는 사실을 `0`, `false`, `"unknown"` 으로 추론하지 않고 `null`,
   field absence, 또는 explicit `unavailable` status/warning 으로 표현한다.
8. Breaking change 가 필요하면 `mcp_schema_version` major 를 올리고, 기존 schema 를
   가능한 기간 동안 병행 제공한다.

이 정책은 "다른 리버스 엔지니어링 모델로 변경해도 구조체에 변화가 없도록" 하기
위한 기준이다. 엔진 차이는 adapter 와 extension boundary 에서 흡수하고, MCP/LLM
소비자는 안정된 AURA record 를 본다.

## Completion Rule

Analysis Capability 의 완료 기준은 다음을 모두 만족해야 한다.

1. Unified Model 또는 Core Service 계약이 명시된다.
2. GUI/CLI/IPC 중 해당 기능의 사용자-facing surface 가 구현된다.
3. MCP surface 가 추가/수정된다.
4. MCP 가 보호값을 써야 하는 데이터는 Safety Core 를 통과한다.
5. 원문 미노출, schema 안정성, 기본 동작을 검증하는 테스트가 추가된다.
6. PRD / Tasks / ADR 중 해당 범위 문서가 갱신된다.

MCP 구현을 같은 slice 에서 완료할 수 없으면 상태를 **MCP Pending** 으로
표시한다. 이 상태는 merge 가능할 수 있지만, feature complete 로 표기하지 않는다.

## MCP Security Regression Gate

MCP 관련 기능은 smoke test 만으로 완료할 수 없다. 최소 완료 기준은 다음 테스트
묶음을 통과하는 것이다.

1. **MCP Schema Envelope Test** — 성공 응답 envelope 필수 필드 검증.
2. **MCP Error Envelope Test** — 실패 응답도 구조화된 schema 로 반환되는지 검증.
3. **Protected Default Test** — 기본 MCP tool 이 `disclosure=protected` 로 동작하는지 검증.
4. **Raw Non-Disclosure Test** — protected 응답에 원문 문자열/code text 가 없는지 검증.
5. **Privileged Raw Denial Test** — raw-access toggle OFF 상태에서 raw 반환이 차단되는지 검증.
6. **Per-Request Approval Test** — toggle ON 이어도 요청별 승인 없이는 raw 반환이 차단되는지 검증.
7. **Bounded Scope Test** — 전체 dump 금지와 count/line/byte limit 강제를 검증.
8. **Raw Disclosure Audit Test** — raw 반환 성공 시 audit event 생성, audit log 원문 미저장을 검증.
9. **Engine-Agnostic Schema Test** — engine/model 변경에도 base record/envelope 안정성을 검증.
10. **MCP Compatibility Test** — additive change 와 unknown field/enum 내성을 검증.

첫 구현 slice 에서 모든 privileged raw 성공 경로를 만들지 않더라도, denial/error
path 와 protected non-disclosure 는 반드시 먼저 검증한다.

## Raw Access Policy

MCP 의 기본 경로는 원문 데이터를 반환하지 않는다. 기본 tool 은 모두 Protected
MCP Tool 로 설계한다.

원문 접근은 완전 금지하지 않고, 확장성을 위해 Privileged MCP Tool 로 분리한다.
다만 다음 조건을 모두 만족해야 한다.

1. raw access session toggle 이 사용자가 명시적으로 켠 상태여야 한다.
2. 각 raw 요청마다 사용자 확인을 받아야 한다.
3. 확인 UI/문구는 호출자, tool, project, 대상 stable id, 반환 범위, byte/line/count
   limit, 요청 목적을 보여줘야 한다.
4. 전체 DB dump, 전체 decompile dump, 전체 disassembly dump 는 금지한다.
5. raw 반환 범위는 문자열 N개, decompile N라인, disassembly N바이트처럼 bounded
   scope 로 제한한다.
6. 모든 raw 반환은 Raw Disclosure Event 로 audit log 에 기록한다.
7. audit log 는 원문 값을 저장하지 않고 stable id, hash, 길이, label, 범위,
   approval id 같은 메타데이터만 저장한다.

이 정책에 따라 외부 LLM/agent 의 기본 사용 경로는 보호값만 소비하고, 로컬 사용자
승인 하의 제한된 디버깅/검증 시나리오에서만 원문 접근을 허용한다.

## Consequences

- AURA 의 GUI, CLI, IPC, MCP 가 같은 분석 모델을 공유한다는 제품 방향성이
  강화된다.
- 기능 추가 비용은 증가한다. 대신 LLM/agent 경로가 뒤처지는 drift 를 줄인다.
- MCP schema versioning, backward-compatible field addition, protected export
  regression test 가 중요해진다.
- 순수 GUI polish 는 coverage 대상에서 제외해 불필요한 MCP churn 을 막는다.
- 원문 접근은 확장 가능하지만, 기본값 보호와 요청별 승인/audit 로 통제된다.
- 새 engine/model 추가 시 base struct/schema 를 바꾸지 않고 extension boundary 를
  사용하므로 자동화 client 안정성이 높아진다.

## Rejected Alternatives

### MCP 를 phase 단위로 몰아서 갱신

구현 속도는 빠르지만 GUI/CLI 와 MCP 가 장기간 불일치할 위험이 크다.

### GUI 화면 단위 MCP

`get_current_strings_tab` 같은 화면 중심 contract 는 UI 변경에 취약하고,
LLM/agent 에 필요한 구조화 데이터를 제공하기 어렵다. MCP 는 GUI widget 이
아니라 Unified Model + Safety Core 기준으로 노출한다.
