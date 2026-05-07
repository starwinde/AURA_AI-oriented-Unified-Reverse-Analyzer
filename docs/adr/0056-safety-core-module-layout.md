# ADR-0056 — Safety core module layout

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0053, ADR-0054, ADR-0055, PRD D-42, PRD D-43

## Context

Phase 13 의 Safety/PII 기능은 GUI, CLI, 향후 `aura-mcp` 가 모두 재사용해야 한다.
탐지/병합/마스킹 로직을 GUI 안에 넣으면 UI 와 policy code 가 결합되고, 나중에 MCP
또는 평가 CLI 에서 같은 로직을 다시 구현하게 된다.

반대로 core module 로 분리하면 `Strings` UI 는 표시와 사용자 입력만 담당하고,
Safety Profile Loader, Rule Pack Engine, Finding Merger, Mask Token Allocator 는
CLI/GUI/MCP 가 같은 API 로 호출할 수 있다.

## Decision

1. Safety 공용 로직은 GUI 가 아니라 core module 로 둔다.
2. Public headers 는 `include/aura/safety/` 아래에 둔다.
3. 구현 파일은 `src/core/safety/` 아래에 둔다.
4. 초기 모듈 후보:

   ```text
   include/aura/safety/
     safety_profile.h
     rule_pack.h
     finding.h
     finding_merger.h
     mask_token_allocator.h

   src/core/safety/
     safety_profile.c/.cpp
     rule_pack.c/.cpp
     finding_merger.c/.cpp
     mask_token_allocator.c/.cpp
   ```

5. GUI 는 `StringTableModel`/`MainWindow` 에서 core safety API 결과를 표시하고,
   탐지/병합/마스킹 알고리즘을 직접 소유하지 않는다.
6. CLI 와 향후 `aura-mcp` 도 같은 core safety API 를 재사용한다.
7. 최종 Safety detection pipeline 은 원본 문자열을 Rule Pack Engine 과 Token
   Classification Model Adapter 가 각각 검사한 뒤, Rule Finding + Model Finding 을
   Finding Merger 에서 병합하고 Mask Token Allocator 로 넘긴다.
8. 구현 순서는 Rule Pack 경로를 먼저 완성한다. 이는 개발 위험을 낮추기 위한
   순서일 뿐이며, Token Classification Model Adapter 도 Phase 13 의 같은 목표
   구현 대상이다.

## Consequences

- GUI, CLI, MCP 간 Privacy Filter 동작이 갈라지는 위험을 줄인다.
- 평가 CLI 와 중간 점검용 GUI 표시를 같은 결과 구조로 검증할 수 있다.
- GUI 구현은 보호 상태/alias/mask token 표시와 편집에 집중한다.
- Token Classification Model adapter 가 Python/외부 프로세스로 시작하더라도,
  adapter 호출 계약은 core safety module 경계에서 관리한다.
- Rule Pack-only 결과로 먼저 시연 가능하지만, 최종 설명은 Rule Pack + Model 병렬
  탐지 후 병합 구조로 유지한다.
