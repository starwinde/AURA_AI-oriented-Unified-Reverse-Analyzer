# ADR-0030 — Tier-based Platform Support Policy

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: PRD.md §9 D-30 (인덱스)

---

## Context

AURA 는 Phase 1~4 의 75 sub-step claim 을 모두 달성했으나 (`Tasks.md`), 검증 환경은 Linux WSL (Ubuntu 24.04) 단일 환경으로만 보장돼 왔다. Phase 1~4 재점검 (`.scratch/phase-1-4-audit/summary.md`) 에서 다음이 드러남:

1. **Windows MSVC 빌드는 RED** — `open_memstream` 30+ callsite 미마이그레이션, `__attribute__((weak))` MSVC 미지원, `MappedFile.fd` 처리 모순.
2. **알려진 부채가 추적 시스템에 등재되지 않음** — Tasks.md 에 "별도 작업으로 분리" 라 두 번 기록됐으나 backlog 시스템 부재로 누적.
3. **macOS 환경 검증 불가** — Mac 하드웨어/CI 부재.

기존에는 "지원 OS" 정책이 묵시적이었다. 어느 환경에서 GREEN 이어야 PR 머지 가능한지 명문화 안 됨 → "Phase X GREEN baseline" 같은 주장이 환경 컨텍스트 없이 사용됨 → 신규 Phase 진입 시마다 부채 누적.

## Decision

3-Tier 플랫폼 지원 정책 채택.

| Tier | OS | 정의 | PR 머지 게이트 |
|------|-----|------|-----------------|
| **1** | Linux WSL (Ubuntu 24.04) | Verified — 매 PR ctest GREEN 의무 | 빌드 + ctest GREEN |
| **1** | Windows MSVC (latest stable) | Verified — 매 PR ctest GREEN 의무 | 빌드 + ctest GREEN |
| **3** | macOS | Best-effort, unverified — portability 코드 기준만 유지, 검증은 Mac 확보 후 | 게이트 없음 |

> Tier 2 (CI-verified, e2e exempt) 는 도입 시점에 재정의 가능하도록 예약. 현재는 1·3 만 활성.

## Rationale

- **Tier 1 양립**: Windows + Linux 모두 사용자 baseline 으로 정식 지원하는 것이 PRD의 사용자 의도와 일치 (Windows 11 호스트, WSL Ubuntu 환경 동시 운용).
- **macOS Tier 3**: Mac 하드웨어/CI 부재 상태에서 "지원 주장" 은 issue 05 의 함정 재발 위험. portability 만 유지하고 정식 지원 주장 하지 않음으로써 정직성 확보.
- **CI 강제**: 정책을 게이트로 자동화하지 않으면 다시 누적될 위험 (Phase 2A.11 의 학습).

## Consequences

### Positive

- 신규 PR 작업 시 양 Tier 1 환경 모두 검증 → 환경 의존 회귀 방지
- "Phase X GREEN" 주장의 환경 컨텍스트 명확
- macOS 검증 미보장 정직 명시 → 사용자 기대 관리

### Negative

- Windows MSVC CI runner 인프라 도입 비용 (issue 09)
- 기존 누적 부채 (issue 02·03·06·08) 일괄 정리 비용 (Phase 9 작업)
- macOS 사용자 보고 시 "Tier 3" 응답으로 만족도 저하 가능 (수용)

### Neutral

- Tier 2 정의 보류 — 구체적 분리가 필요해질 때 재정의

## Implementation

본 ADR 의 실행 작업은 **Phase 9 — Platform Coverage** 로 정식 등재. 작업 분해는 `.scratch/platform-coverage/` 하위 PRD + 10개 vertical-slice issue.

### 후속 변경 사항

- `CLAUDE.md` § 지원 플랫폼 추가
- `PRD.md` D-30 entry (본 ADR 포인터)
- `rules.md §1` Tier 1 enforcement 명문화
- `Tasks.md` Phase 9 thin entry 추가
- `AUTOMATION_ROADMAP.md` 부활 — Phase 9 active 상태 노출

## Alternatives Considered

### A. Linux WSL only (status quo 명문화)

거부. 사용자가 Windows 호스트 baseline 이며 GUI(Phase 5)는 Windows 검증 필요.

### B. 모든 OS (Windows + Linux + macOS) 동등 Tier 1

거부. Mac 검증 메커니즘 없이 주장만 추가하는 것은 issue 05 함정 재발.

### C. Best-effort 모든 OS (게이트 없음)

거부. 게이트 없이는 부채가 다시 누적 (Phase 2A.11 의 정확한 패턴).

## References

- `.scratch/phase-1-4-audit/summary.md` — Phase 1~4 재점검 결과
- `.scratch/platform-coverage/PRD.md` — 본 결정의 실행 PRD
- `.scratch/platform-coverage/issues/01..10` — vertical-slice 분해
- Tasks.md L84~92 (Phase 2A.11 status note), L207 (Phase 2 재점검 로그)
