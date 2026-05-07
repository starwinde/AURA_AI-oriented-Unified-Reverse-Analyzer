# 09 — Windows MSVC CI runner 도입

**Status**: ready-for-human
**Depends on**: 02·03·04·06·07 (모두 GREEN)

## 목표

GitHub Actions `windows-latest` runner 또는 self-hosted MSVC 환경에서 매 PR 빌드+ctest 실행. Tier 1 enforcement 준비.

## DoD

- [ ] `.github/workflows/ci-windows.yml` 신규 (또는 기존 CI에 matrix 추가)
- [ ] CMake configure + build (Release, vcpkg / 의존성 명시)
- [ ] ctest 실행, capability-gated SKIP은 허용
- [ ] PR 머지 게이트 등록 (GitHub branch protection)

## 결정 사안

- Windows runner: GitHub Actions windows-latest (무료) vs self-hosted
- 의존성 관리: vcpkg / chocolatey / 직접 빌드
- e2e 테스트 (rizin/ghidra subprocess): Windows에서 어디까지 검증?

## 비고

본 issue 진행 전에 02·03·04·06·07 모두 GREEN 이어야 의미 있음. CI가 RED를 잡아내는 것이 아니라 baseline 유지를 보장하는 도구.

ready-for-human — CI 인프라 결정은 사용자/유지보수자 사안.
