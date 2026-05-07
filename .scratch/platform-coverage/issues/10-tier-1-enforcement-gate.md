# 10 — Tier 1 enforcement gate

**Status**: needs-info
**Depends on**: 09

## 목표

PR 머지 전 양 Tier 1 환경 (Linux WSL + Windows MSVC) ctest GREEN을 의무화. 문서적 정책을 자동화된 게이트로 변환.

## DoD

- [ ] GitHub branch protection 규칙 추가 (또는 동등)
- [ ] `rules.md §1` 의 enforcement 정책이 실제 게이트와 일치
- [ ] 우회 권한 (admin override) 명문화
- [ ] dry-run 기간 (예: 1주) 후 정식 enforcement

## 결정 사안

- Tier 1 일시적 RED 발생 시 (예: 외부 의존성 회귀) 처리 정책: 파이프라인 정지 vs 우회 허용 + 후속 수정
- macOS Tier 3 → Tier 1 승급 절차

## 비고

본 issue는 Phase 9 의 close-out signal. 9.x 모두 통과 + 10 통과 = Phase 9 완료.
