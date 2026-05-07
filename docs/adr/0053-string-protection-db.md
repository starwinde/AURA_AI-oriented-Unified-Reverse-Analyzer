# ADR-0053 — String protection persistence baseline

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0039, ADR-0038, ADR-0044, CONTEXT.md "LLM Privacy Filter & Policy Gateway"

## Context

AURA 는 문자열 record 를 GUI/IPC/MCP/LLM 경로로 노출한다. 문자열에는 이메일,
전화번호, API key, token, 내부 경로, 서버 주소 같은 민감 정보가 포함될 수
있다. 사용자가 문자열 의미를 이해하기 위해 붙이는 별칭과, 외부 LLM/MCP 로
전달하기 위한 마스킹 토큰은 목적이 다르다.

따라서 원본 문자열을 직접 덮어쓰거나 기존 `overrides` 테이블에 억지로 넣는
방식은 부적절하다. 원본 분석 데이터, 사용자 표시 별칭, detector findings 를
분리해야 한다.

## Decisions

### D1 — Alias and mask token are separate concepts

`String Alias` 는 사람이 이해하기 위한 사용자 별칭이다. 예:
`customer_email`.

`Mask Token` 은 외부 전달을 위한 안전 토큰이다. 예: `[EMAIL_1]`.

GUI 는 둘을 함께 표시할 수 있지만, MCP/외부 LLM 경로는 기본적으로 mask token
을 우선 사용한다. 사용자가 alias 에 민감정보를 다시 적을 수 있으므로 alias 는
외부 전달 안전값으로 간주하지 않는다.

### D2 — v1 persistence uses three tables

1차 구현은 다음 세 테이블만 추가한다.

- `analysis_strings`: engine-reported original string record. 원본 분석값 보존.
- `string_overrides`: 사용자 alias, mask token, display mode.
- `string_protection_findings`: detector/model/rule 이 찾은 민감정보 근거.

`string_references`, render cache, export audit tables 는 후속이다. 현재 문자열
이동 기능은 xref, full disasm text, RIP-relative 계산 fallback 으로 세션 내에서
해결하며, 성능/감사 요구가 커질 때 별도 테이블로 승격한다.

### D3 — Engine output remains immutable

세 테이블은 AURA-side protected view layer 다. `AuraStringRecord` 와
`AuraEngineResponse` 를 수정하지 않는다. 렌더링/IPC/MCP 계층이
`analysis_strings + string_overrides + string_protection_findings` 를 조합해
Protected String View 를 만든다.

## Consequences

- DB 테이블 증가는 1차 기준 3개로 제한된다.
- 중간 점검 설명은 "원본/별칭/마스킹/탐지근거를 분리한 문자열 보호 계층"으로
  정리할 수 있다.
- LLM/MCP 전달 정책은 `Mask Token` 을 기준으로 하며, `String Alias` 는 GUI
  가독성 보조값이다.
- 향후 export audit, detector catalog, render cache 는 별도 ADR 없이도 이
  ADR 의 후속 확장으로 추가 가능하지만, 테이블 추가 시 DoD 와 마이그레이션
  테스트가 필요하다.
