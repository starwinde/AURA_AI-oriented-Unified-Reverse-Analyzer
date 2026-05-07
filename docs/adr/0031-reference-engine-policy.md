# ADR-0031 — Reference Engine Policy

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0030 (Tier 정책), CLAUDE.md §"핵심 원칙 1·4", D-27 (subprocess-only)

---

## Context

Phase 10 strip 직후 외부 도구 오케스트레이션 경로의 첫 통합 게이트
(`tests/integration/orchestrator_smoke/`) 를 설계하면서, 어느 adapter 가
매 PR 게이트의 mandatory 의존성이 되어야 하는지 결정해야 했다. AURA 는
복수 adapter (Rizin, Ghidra, future) 를 동등하게 다루는 오케스트레이터지만,
ADR-0030 Tier 1 게이트의 결정론적 GREEN/RED 판정을 위해 **단 하나의
adapter** 가 환경에 항상 존재한다고 가정해야 한다.

Phase 2~3 의 이력은 Ghidra 의 디컴파일 우위를 강조해 왔으므로, 미래
reader 가 "왜 Ghidra 가 mandatory 가 아닌가?" 를 질문할 가능성이 높다.

## Decision

| 역할 | 정의 | 현재 |
|------|------|------|
| **Reference engine** | 매 PR Tier 1 게이트가 의존하는 mandatory adapter. 호스트 부재 시 게이트 RED. | **Rizin** |
| **Optional engine** | 있으면 추가 시나리오 기여, 없으면 SKIP. 게이트 RED/GREEN 에 영향 없음. | Ghidra (및 future) |

새 adapter 가 도입될 때 reference vs optional 위치는 본 ADR 의 후속
amendment 또는 신규 ADR 로 명시한다 (디폴트 = optional).

## Rationale

- **CI 게이트는 결정론이어야 한다.** "어느 환경은 Rizin, 어느 환경은
  Ghidra" 는 회귀 원인 분리 비용을 증대시킨다.
- **Rizin = 단일 정적 바이너리.** GitHub Actions runner (Linux + Windows
  MSVC) 양쪽에 prebuilt 다운로드 + 캐시가 수 초. Ghidra 는 JVM + 수백 MB
  배포로 매 PR 비용이 분 단위.
- **Phase 1~3 의 unified model 계약은 adapter 와 직교**하므로, 한
  reference engine 만으로도 "ingestion → override → JSON 직렬화" 경로의
  살아있음이 증명된다. 디컴파일 품질 검증은 별도 (수동/주간) 시나리오의 일.
- **D-27 subprocess-only 정책과 정합** — Rizin 은 별도 프로세스로 호출되며
  AURA 코어와 링크되지 않는다 (CLAUDE.md §"핵심 원칙 4").

## Consequences

### Positive

- Tier 1 게이트의 환경 요구사항이 단순 (Rizin prebuilt 1개).
- 새 adapter 도입 시 default-optional 이라 기존 게이트 안정성에 영향 없음.
- Ghidra 미설치 dev 환경 (예: Java JRE 부재 호스트) 에서도 통합 테스트
  GREEN 유지 가능 — 해당 시나리오만 SKIP.

### Negative

- Rizin 분석 품질 한계가 reference engine 표준이 됨. 디컴파일 우위 검증은
  optional 시나리오에 의존하므로 게이트 강도가 실제 사용 품질보다 낮을
  가능성.
- "왜 Ghidra 가 reference 가 아닌가?" 가 신규 contributor 에게 반복
  질문될 가능성 (본 ADR 로 답변 고정).

### Neutral

- 향후 Rizin → 다른 도구로 reference 위치를 옮길 수 있음 (manifest 와 fetch
  script 패턴 동일하므로 마이그레이션 비용 제한적). 그 시점에 본 ADR
  superseded 처리.

## Alternatives Considered

### A. Ghidra mandatory

거부. CI 비용 (JVM + 다운로드 크기 + warmup 시간) 이 매 PR 게이트에
부적합. 디컴파일 품질은 별도 시나리오에서 잡는 것이 분리 관심사.

### B. 둘 다 mandatory

거부. 외부 도구 2개의 가용성 곱이 곧 게이트 가용성. 한쪽 부재가 무관 PR
의 회귀가 됨 → "skip 관행" 이 생겨 게이트가 죽는 패턴 (ADR-0030 의 학습).

### C. 둘 다 optional, host 가 가진 도구로 실행

거부. 환경마다 다른 게이트는 결정론 위반. 회귀 원인 분리 비용 증대.

## References

- CLAUDE.md §"핵심 원칙 1·4"
- ADR-0030 — Tier 정책 (본 결정의 게이트 정의)
- D-27 — Rizin subprocess-only
- CONTEXT.md §"Engines & adapters"
