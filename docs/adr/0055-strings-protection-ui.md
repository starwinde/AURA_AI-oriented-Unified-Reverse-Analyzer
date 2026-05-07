# ADR-0055 — Strings protection UI belongs to the Strings tree

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0036, ADR-0053, ADR-0054, PRD D-38, PRD D-41, PRD D-42

## Context

Phase 13 의 Privacy Filter MVP 는 문자열 기반으로 시작한다. 별도 `Safety` 코드 탭을
추가하면 향후 MCP/LLM 기능까지 이미 완성된 것처럼 보일 수 있고, 현재 Cutter-style
workspace 의 우측 코드 탭을 불필요하게 복잡하게 만든다.

현재 사용자가 민감정보를 확인하고 수정할 자연스러운 위치는 `Strings` 트리다.
문자열 선택은 이미 디컴파일 이동과 연결되어 있으므로, 보호 상태도 같은 엔티티 위에
붙이는 편이 가장 작고 설명하기 쉽다.

## Decision

1. Safety/PII v1 UI 는 별도 `Safety` 탭을 만들지 않고 기존 `Strings` 탭에 귀속한다.
2. `Strings` parent row 는 문자열 엔티티 요약과 보호 상태/Mask Token 요약을 보여준다.
3. 기존 엔진 metadata child row 는 유지한다.
4. 보호 관련 child row 는 트리 최하단에 다음 순서로 추가한다.
   - `기존`: 원본 문자열
   - `별칭`: String Alias
   - `마스킹`: Mask Token 또는 Protected String View 요약
5. `기존` row 는 민감정보 원문을 노출할 수 있으므로 기본값은 숨김이다. 사용자가
   민감정보 상세 표시 설정을 켠 경우에만 노출한다.
6. 디컴파일/디스어셈블리/LLM payload 의 실제 치환은 Protected String View 경로에서
   수행하며, `Strings` UI 는 그 상태를 확인하고 편집하는 표면이다.

## Consequences

- 현재 문자열 기반 MVP 범위와 UI 범위가 일치한다.
- 기존 Cutter-style 좌측 브라우저와 우측 코드 탭 구조를 깨지 않는다.
- 원문 민감정보를 기본 화면에서 과하게 노출하지 않는 보안 UX 를 설명할 수 있다.
- 향후 함수명/심볼/디컴파일 결과까지 보호 범위가 확장되면 별도 Safety 탭 또는
  report view 를 재검토한다.
