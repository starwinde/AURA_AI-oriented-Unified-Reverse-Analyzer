# ADR-0032 — External Tool Acquisition Pattern

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0031 (reference engine), CLAUDE.md §"핵심 원칙 1·4", D-27

---

## Context

ADR-0031 로 Rizin 이 매 PR 게이트의 mandatory 의존성으로 확정되면서, AURA
의 빌드/CI/로컬 dev 셋이 동일한 외부 도구 바이너리를 결정론적으로
획득하는 메커니즘이 필요해졌다. AURA 가 자체 빌드하는 라이브러리
의존성 (cJSON, SQLite, doctest) 은 정적 링크 + 소스 vendor 패턴이
확립돼 있으나, **외부 런타임 도구** (subprocess 호출 대상) 는 본질이
달라 동일 패턴 적용이 부적합하다.

CMake `FetchContent` 는 빌드 시점 다운로드의 표준 메커니즘이지만,
subprocess-only 도구 (D-27) 는 빌드 산출물이 아니라 런타임 외부 자원이며
CMake 의존 그래프 밖에 두는 것이 의미상 정합하다. 또한 `FetchContent` 는
SHA 검증, 플랫폼별 asset 분기, 오프라인 캐시를 직접 다루기 어렵다.

## Decision

외부 런타임 도구 수급은 다음 패턴으로 통일한다.

1. **Manifest**: `third_party/<tool>/manifest.json` — version + 플랫폼별
   asset (`url`, `sha256`, `extract_to`) 의 single source of truth. 커밋된다.
2. **Fetch script**: `scripts/fetch_external_tools.{sh,ps1}` — manifest 를
   읽어 prebuilt 를 다운로드 → SHA256 검증 → `third_party/<tool>/<version>/`
   로 추출. CMake 호출 전에 실행. 추출 디렉토리는 gitignore.
3. **Override**: `AURA_<TOOL>_BIN` 환경변수 (예: `AURA_RIZIN_BIN`) 가
   있으면 manifest 무시, 그 경로 사용 (버전 검증 경고만 — 강제 X).
4. **CI**: workflow 의 cmake configure 전 단계에서 fetch script 1회 실행.
   다운로드는 GitHub Actions cache 로 캐싱 (key = manifest 의 SHA256).
5. **로컬 dev**: 최초 1회 fetch script 실행, 이후 캐시 재사용. PATH 의
   설치본을 쓰고 싶으면 `AURA_<TOOL>_BIN` 으로 override.

본 패턴은 reference engine (Rizin) + future optional engine (Ghidra 등)
모두에 동일 적용한다.

## Rationale

- **D-27 / CLAUDE.md §"핵심 원칙 4" 와 정합** — 외부 도구는 별도 프로세스이며
  빌드 산출물이 아니다. CMake 의존 그래프 밖에 두는 것이 의미상 옳다.
- **결정론**: SHA256 lockfile 이 prebuilt cache poisoning + asset 변경에
  대한 무결성 보장. URL 도 manifest 에 명시해 GitHub release 명명 규칙
  변경에 대한 회귀를 방지.
- **플랫폼 분기 단순**: Tier 1 OS (Linux/Windows MSVC) 의 asset 이 다르므로
  manifest 가 host platform 별 lookup 테이블을 제공.
- **로컬 dev 마찰 최소**: `AURA_<TOOL>_BIN` override 로 본인이 apt/scoop/brew
  로 설치한 도구를 그대로 사용 가능 — 강제 다운로드 강요하지 않음.
- **CMake `FetchContent` 거부 이유**: (1) 빌드 의존 그래프 오염, (2) SHA
  검증 / 캐시 / 플랫폼 분기를 직접 구현해야 하는 비용이 별도 스크립트와
  동일, (3) 오프라인 빌드 부서짐.

## Consequences

### Positive

- 신규 외부 도구 추가 비용 = manifest 1개 + fetch script 의 lookup 1줄.
- CI / 로컬 / 모든 dev 가 같은 도구 버전 사용 보장.
- 오프라인 빌드 가능 (캐시 후).
- CMake 빌드 자체는 외부 네트워크 도달성 불필요.

### Negative

- Manifest 의 SHA256 갱신 절차가 수동 (도구 버전 업그레이드 시). 다만
  연 1~2회 빈도라 자동화 ROI 낮음.
- `FetchContent` 라는 표준을 거부하므로 신규 contributor 에게 학습 비용.
  본 ADR 로 답변 고정.

### Neutral

- 본 패턴은 빌드 링크 의존성 (cJSON, SQLite, doctest 등 헤더/소스 vendor)
  에는 적용되지 않는다. 그쪽은 기존대로 `third_party/<lib>/` 소스 커밋.

## Alternatives Considered

### A. CMake `FetchContent` 로 Rizin 다운로드

거부. 빌드 의존 그래프 오염 + SHA/캐시/플랫폼 분기 직접 구현 비용이 별도
스크립트와 동등. subprocess-only 도구의 본질과 부정합.

### B. 패키지 매니저 위임 (apt / vcpkg / brew)

거부. 환경마다 버전 다양성 → invariant 게이트가 환경마다 다르게 깨짐.
Tier 1 결정론 위반.

### C. Docker 이미지 안에서만 게이트 실행

거부. ADR-0030 Tier 1 (Linux WSL + Windows MSVC native) 환경 정책과
충돌. 로컬 dev 마찰 (특히 Windows native) 큼.

### D. Submodule + 소스 빌드

거부. MSVC 호환성을 자가 부담하는 비용 (Phase 9 에서 막 폴리시 한 패턴의
재현). subprocess-only 정책상 소스가 필요 없음.

## Implementation

본 ADR 의 첫 적용은 `tests/integration/orchestrator_smoke/` 구현 PR.
- `third_party/rizin/manifest.json` 신규
- `scripts/fetch_external_tools.{sh,ps1}` 신규
- `.gitignore` 에 `third_party/rizin/<version>/` 패턴 추가
- CI workflow 에 fetch script 호출 + cache step 추가

future Ghidra optional 도입 시 `third_party/ghidra/manifest.json` 추가.

## References

- ADR-0031 — Reference engine policy (본 ADR 의 첫 사용처)
- D-27 — Rizin subprocess-only
- CLAUDE.md §"핵심 원칙 1·4"
- CONTEXT.md §"External tool acquisition"
