# ADR-0033 — Frontend Topology: Co-equal CLI + GUI on shared `aura_core`

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0030 (Tier 정책), ADR-0031 (reference engine), CLAUDE.md
§"제약 사항 요약"

---

## Context

Phase 10 strip (commit `0483147f`) 이후 AURA 코드베이스에 frontend 가 0
개. 새 frontend 의 위상을 정해야 다음 마일스톤 (`src/cli/` 신규,
`src/gui/` 재도입 시점) 의 모듈 경계 / 빌드 / install 구조가 결정된다.

이전 Phase 5 (구) 는 GUI 를 mainline 정체성으로 두고 진행됐고, 결과는
scrap (`legacy strip`). GUI 디자인 라운드가 LLM 통합 / adapter 보강 /
CI 진척을 차단하는 패턴이 strip 의 직접 원인이었다.

CLAUDE.md §"제약 사항 요약" 의 "완전한 독립 CLI (`--headless`) — Phase
11.4 이후" 도 stale — strip 으로 모든 frontend 가 사라져 재정의 필요.

## Decision

AURA 는 **2 개의 co-equal frontend** 를 가진다.

| Frontend | 역할 | 진입점 | Lifecycle |
|----------|------|--------|-----------|
| **CLI** | mainline, headless, automation/CI/LLM pipeline | `aura` binary | one-shot (Q3) |
| **GUI** | 시각화, interactive RE 워크플로우 | `aura-gui` binary (가칭) | long-lived Qt event loop |

둘 다 `aura_core` 라이브러리의 orchestrator API 만 호출한다 — 직접 의존
없음, 둘 사이 통신 없음.

**Bootstrapping 순서**: CLI first. GUI bootstrap 은 CLI v1 ctest GREEN +
LLM 통합 사용사례 1 개 e2e 검증 후.

## Rationale

### Co-equal vs primary 한쪽

- **GUI primary 의 함정**: Phase 5 (구) scrap 의 정확한 패턴. Qt 위젯/
  layout 작업이 LLM 통합 / CI 진척을 차단.
- **CLI primary 의 함정**: GUI 가 "CLI 의 그림자" 가 되면 GUI-native
  인터랙션 (interactive disasm browse, hex editor, cross-ref jump) 이
  어색해진다. RE 도구 가치의 큰 부분 봉쇄.
- **Co-equal 의 enable**: 같은 `aura_core` orchestrator API 를 두 client
  가 다른 방식으로 호출. service contract 가 single source of truth.
  인터페이스 변경이 core 를 흔들지 않는다.

### CLI first 의 근거

1. **Service contract 검증 비용 최소** — CLI 는 dispatch path 를 stdout
   으로 print 하는 얇은 layer. orchestrator_smoke (commit `3879a03f`) 가
   이미 80% 한 일. GUI 는 layout/event/rendering 추가 비용으로 contract
   검증 신호가 노이즈에 묻힘.
2. **CONTEXT.md 정체성의 LLM 절반 unblock** — "external tool
   orchestrator + LLM context provider" 중 LLM 절반의 진척이 현재 0.
   CLI 한 개가 `aura analyze | aura llm-context | curl ...` 류
   파이프라인을 즉시 enable. GUI 는 같은 가치를 못 enable.
3. **CI 회귀 안전망 구축** — CLI 는 stdout/exit-code 로 ctest 에 자연
   등록. 매 PR 게이트에 frontend 1 개 이상이 들어가면 service contract
   drift 를 잡힘.
4. **Phase 5 (구) scrap 의 패턴 회피** — GUI 가 mainline 정체성이 되면
   Qt 디자인 라운드가 모든 다른 진척 차단. Strip 의 직접 원인 재현.

### GUI gate (CLI v1 + LLM 사용사례 후) 의 근거

co-equal 의 service contract 는 CLI 단독으로 부분 검증. LLM pipeline
하나가 e2e 동작하면 contract 의 LLM 절반도 안정. 그때가 GUI bootstrap 의
자연 타이밍. 너무 이른 GUI 진입은 두 trees 의 병행 작업이라 이전 Phase
5 함정 재현.

## Consequences

### Positive

- 두 frontend 가 직접 의존 없어 병행 개발 가능 (예: GUI worktree).
- `aura_core` 가 라이브러리로 깨끗하게 유지 — 인터페이스/터미널/Qt 의존성
  0 (이미 그렇다).
- Frontend 변경이 core 를 흔들지 않음 — service contract 안정성.

### Negative

- 두 frontend 의 기능 parity 유지 비용 (예: `--engine` 선택을 CLI 에서
  새로 추가하면 GUI 도 동등 노출 필요).
- mainline binary 이름이 `aura` (CLI) 라 GUI 진입 시 `aura-gui` 같은
  suffix 가 필요. GUI primary 시나리오 대비 약간 어색.

### Neutral

- 향후 daemon 패턴 도입 시 (현재 Q3 결정으로 거부) 본 ADR 이 superseded.

## Alternatives Considered

### A. GUI primary, CLI 는 자동화 hatch

거부. Phase 5 (구) scrap 의 정확한 패턴. LLM/automation/CI 진척 차단 위험.

### B. CLI primary, GUI 는 시각화 lens

거부. GUI-native 인터랙션 (interactive disasm, xref jump) 가 "CLI 명령의
그림자" 가 되면 RE 도구 가치 봉쇄.

### D. GUI 만, CLI 는 dev-only verification

거부. CONTEXT.md "external tool orchestrator + LLM context provider"
정체성의 automation/LLM pipeline 절반 봉쇄.

### Co-equal 안에서 GUI first

거부. 첫 demonstrable outcome 까지 CLI 대비 4~5배 비용 (Qt 위젯 학습 +
layout + main_window + binary picker dialog + analyze 호출 + table view +
데이터 모델). 그 동안 LLM/CI 진척 0.

### Co-equal + 동시 진행 (CLI/GUI 병행)

거부. Single-developer 컨텍스트 스위칭 비용 큼. aura_core API 가 동시에
두 방향에서 압력 받아 churn. GUI worktree 옵션은 사용자 자율로 가능
(본 ADR 은 그것을 막지 않음).

## Implementation

본 ADR 의 첫 실집행 = **Phase 11.1 — CLI v1**.

CLI v1 표면 (Q5 합의):
- `aura analyze <bin>` — ANALYZE dispatch, unified model JSON
- `aura info <bin>` — binary fingerprint
- `aura llm-context <bin> [--func <addr>]` — LLM payload JSON

CLI v1 구현 합의 (Q6~Q14):
- argparse: CLI11 vendored single-header
- 출력: JSON default + `--compact`, root 에 `"aura_schema": 1`
- Source layout: `src/cli/`, target = `aura`
- Config: 없음 (flag + env var fallback)
- Engine: 미지정 시 `aura_orchestrator_select_primary` 정책
- State: stateless (project DB 미통합)
- Test: `tests/integration/cli_smoke/` doctest popen + JSON parse
- Docs: `--help` + `docs/cli.md`

### 후속 변경 사항

- `CONTEXT.md` — Frontend / CLI / GUI / Primary set 용어 추가 (본 커밋).
- `AUTOMATION_ROADMAP.md` — Phase 11.1 entry 추가.
- `CLAUDE.md` §"제약 사항 요약" — "완전한 독립 CLI (`--headless`) Phase
  11.4 이후" 항목은 strip 으로 stale, 본 ADR 로 갱신 (Phase 11.1).

## References

- ADR-0030 — Tier 정책 (CLI ctest 가 Tier 1 양 환경에서 GREEN 의무)
- ADR-0031 — Reference engine policy
- ADR-0032 — External tool acquisition pattern
- CONTEXT.md §"Frontends" + §"Engine routing"
- Phase 10 strip commit `0483147f` — frontend 0 화의 직접 원인
