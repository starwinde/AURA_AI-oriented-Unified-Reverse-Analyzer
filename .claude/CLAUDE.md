# AURA 프로젝트 — AI 실행 컨텍스트

> 이 파일은 Claude Code(LLM)가 세션 시작 시 가장 먼저 읽는 최상위 지시 문서다.
> 작성일: 2026-03-25

---

## 프로젝트 개요

AURA는 C/C++로 구현하는 고성능 리버스 엔지니어링 도구다. 바이너리 분석, 디스어셈블리, 디컴파일 기능을 네이티브 성능으로 제공하는 것이 목표다.

---

## 세션 시작 시 필독 문서

세션을 시작할 때마다 아래 순서대로 문서를 읽고 현재 상태를 파악한 뒤 작업을 수행한다.

| 순서 | 파일 | 목적 |
|------|------|------|
| 0 | `~/.claude/memory/MEMORY.md` | 전역 사용자 메모리 (모든 프로젝트 공통 — 사용자 선호, 행동 피드백) |
| 1 | `PRD.md` | 프로젝트 목표, 기능 요구사항, Open Decisions 확인 |
| 2 | `rules.md` | AI 행동 규칙, 중단 조건, 코드 스타일, 커밋 규칙 (§11 문서 계층 포함) |
| 3 | `AUTOMATION_ROADMAP.md` | **Live canonical** — 현재 Phase/Step 상태, 핸드오프 로그 (rules.md §11.1) |
| 4 | `Tasks.md` | **Release snapshot** — 릴리스 경계의 상태 (실시간 진행은 ROADMAP 우선, rules.md §11.2) |
| 5 | `AURA_MCP_플러그인_가이드.md` | MCP 환경 미구성 시 참조 |

> **문서 충돌 시 우선순위**: `AUTOMATION_ROADMAP.md` > `Tasks.md` > 메모리. 상세는 `rules.md §11.2` 참조.

---

## 핵심 원칙

1. **언어 정책 (2026-05-02 갱신)**: AURA 는 **외부 도구 오케스트레이션** 방향으로 전환. AURA core (orchestrator / IPC / UI / project DB) 는 계속 C/C++. 외부 도구 호출 경로는 해당 도구가 요구하는 런타임을 그대로 받아들인다 (예: Ghidra subprocess → JVM, Rizin → 네이티브 바이너리). **사용 불가 환경 표기 의무**: 특정 도구의 런타임이 호스트에 없으면 (Ghidra 의 Java JRE 부재 등) 해당 기능을 "사용 불가"로 명시하고 **이유 + 요구 런타임 + 설치 안내**를 함께 노출해야 한다 (silent disable 금지).
2. **성능 우선**: AURA core 는 네이티브 코드 최적화. 외부 도구 비용은 IPC 경계 / 캐싱으로 흡수.
3. **MVP 집중**: 플러그인 시스템, 스크립트 인터페이스는 MVP 이후로 유보.
4. **정적 링크 우선**: AURA 가 직접 빌드하는 의존성은 가능하면 정적 링크. 외부 도구는 별도 프로세스 (D-27 Rizin subprocess-only 정책).
5. **외부 의존성 채택 기준** (D-26, 2026-04-26 reformulation): 라이선스 호환 (Apache 2.0 / MIT / BSD / Public Domain) + foundational commodity (산업 표준 존재 영역) + AURA 차별점 아님 = extract 우선 검토. **Differentiation 영역** (LLM 통합, UX, 협업, project DB, AI rename) = 커스텀 유지. 신규 의존성 도입은 `rules.md §10` 사용자 확인 gate 적용.

---

## 기술 스택

| 구성 요소 | 선택 | 비고 |
|-----------|------|------|
| 주 언어 | C11 / C++17 | 혼용 허용, 신규 모듈은 C++17 권장 |
| 디스어셈블 엔진 | Capstone ≥ 5.0 | x86/x86_64, ARM 지원 |
| 어셈블 엔진 | Zydis ≥ 4.0 (MIT) | 바이너리 패치용 (x86/x86_64), Phase 5.7 연동. Keystone GPLv2 대체 |
| JSON 파싱 | cJSON ✅ 확정 | 단일 파일, 정적 링크, LLM 응답 처리 |
| 파일 파싱 | 현재 커스텀 (`src/parser/{elf,pe,macho}_parser.c`) | 향후 license-clean 외부 라이브러리 도입 가능 — PRD §7 신규 D 결정 + `rules.md §10` 사용자 확인. (libelf 절대 금지 정책은 D-26 으로 해제) |
| 파일 I/O 방식 | mmap ✅ 확정 (D-6) | 500MB 대형 파일 lazy load, open() + mmap() |
| GUI 프레임워크 | Qt6 ✅ 확정 | 크로스플랫폼 지원 (2026-03-25 결정, D-1 완료) |
| C++ demangle | cxxabi.h (`__cxa_demangle`) | C++ 심볼 demangle 래퍼, GCC Runtime Exception — 정적 링크 허용 (PRD §4.2, 2026-03-26 승인) |
| HTTP 클라이언트 | libcurl ≥ 7.0 | LLM API 연동 (Phase 6), OpenAI 호환 API 요청 |
| LLM 연동 | API 기반 (로컬 + 클라우드) | 로컬: LM Studio `http://localhost:1234/v1`, 모델: `qwen/qwen3-coder-next`; 클라우드: OpenAI 호환 API |
| DB 엔진 | SQLite (amalgamation) | GUI 프로젝트 DB, Public Domain, `third_party/sqlite/` 소스 내장 (D-13, 2026-04-03 확정) |

---

## 프로젝트 구조

경로는 실제 환경에 맞게 적용한다. 아래는 표준 디렉토리 구조다.

```
<AURA_ROOT>/
├── src/
│   ├── core/           # 공통 타입, 에러 코드, 런타임 초기화
│   ├── disasm/         # 디스어셈블러 모듈 (Capstone 래핑)
│   ├── parser/         # ELF/PE/Mach-O 파서 (현재 커스텀)
│   ├── symbolic/       # 심볼릭 실행 엔진
│   ├── decompiler/     # 제어 흐름 복원 및 의사코드 생성
│   ├── llm/            # 로컬 LLM 연동 (LM Studio API 클라이언트)
│   └── gui/            # GUI 레이어 (core와 완전 분리)
├── include/            # 공개 헤더 파일
├── build/              # 빌드 출력물 (git 제외)
├── tests/              # 단위 테스트 및 통합 테스트
├── third_party/        # 외부 라이브러리 (Capstone 등)
└── docs/               # 문서
```

---

## 개발 워크플로우

1. **태스크 순서 실행**: Tasks.md의 순서대로 하나씩 완료한다 (0.1 → 0.2 → ...).
2. **상태 표시**: 구현 완료 시 `[ ]` → `[-]`, DoD 검증 완료 시 `[-]` → `[x]`로 변경한다. (`[-]` = 구현 완료·검증 진행 중)
3. **설계 우선**: 구현 전에 설계 단계가 누락된 경우 설계를 먼저 추가한다.
4. **GUI 기준 개발 강제**: 사용자 기능은 GUI를 기준면으로 설계·구현·검증한다. CLI만 먼저 만들고 GUI를 나중으로 미루지 않는다.
5. **CLI/GUI 동시 반영**: GUI에서 노출되는 기능의 CLI 경로가 존재하거나 기존 CLI 계약과 연결되는 경우, 같은 변경에서 CLI 동작·도움말·테스트도 함께 갱신한다. 반대로 CLI 기능을 추가/변경할 때도 GUI 노출 또는 명시적 비노출 사유를 같은 계획에 포함한다.
6. **검증 타깃 구분**: GUI 동작을 바꾼 경우 `gui_smoke`만으로 완료 처리하지 않고 실제 앱 타깃 `aura-gui`도 빌드한다. CLI 표면이 영향을 받으면 `aura` 타깃과 관련 CLI smoke도 함께 확인한다.
7. **상세 규칙 준수**: 중단 조건, 코드 스타일, 커밋 규칙은 `rules.md`를 따른다.

---

## 제약 사항 요약

| 항목 | 상태 |
|------|------|
| 플러그인 시스템 | MVP 이후 유보 |
| AURA core 구현 언어 | C11 / C++17 (변경 없음) |
| 외부 도구 런타임 (JVM / Python 등) | **허용** (해당 도구가 요구할 때). 호스트에 없으면 기능 "사용 불가" 표기 + 이유 + 요구 런타임 + 설치 안내 노출 (2026-05-02 정책 갱신) |
| 개발 검증 CLI (`--disasm`, `--info` 등) | 각 Phase에서 허용 |
| 완전한 독립 CLI (`--headless`) | Phase 11.4 이후 |

> MCP 구성 상세: `AURA_MCP_플러그인_가이드.md` 참조

---

## 지원 플랫폼 (2026-05-03 결정 — ADR-0030)

| Tier | OS | 정의 | PR 머지 게이트 |
|------|-----|------|-----------------|
| 1 | Linux WSL (Ubuntu 24.04) | Verified — 매 PR ctest GREEN 의무 | 빌드 + ctest GREEN |
| 1 | Windows MSVC (latest stable) | Verified — 매 PR ctest GREEN 의무 | 빌드 + ctest GREEN |
| 3 | macOS | Best-effort, unverified — Mac 하드웨어/CI 확보 후 승급 예정 | 게이트 없음 (portability 코드 기준만) |

> 상세 근거: `docs/adr/0030-tier-platform-policy.md`. 실행 작업: Phase 9 (`AUTOMATION_ROADMAP.md` + `.scratch/platform-coverage/`).

---

## 자동화 세션 프로토콜 (24/7 모드)

> 이 섹션은 무인 자동화 세션에서 따라야 하는 프로토콜이다.

### 세션 시작 시 (필수)
1. `AUTOMATION_ROADMAP.md` 읽기 → 현재 Phase/Step + 핸드오프 로그 확인
2. `Tasks.md` 읽기 → 프로젝트 상태 확인
3. `git log --oneline -5` → 마지막 커밋 확인
4. `cmake --build build-rel && ctest --test-dir build-rel` → 빌드 건강성 확인
5. 빌드 실패 시 → INFRA FAILURE 기록, 수정 시도 (3회 규칙 적용)
6. **현재 Step 진단 (20-30분)**: 현재 Step의 실패 증상을 직접 재현하고, 진단 결과를 AUTOMATION_ROADMAP.md의 해당 Step에 기록한 후 구현 시작

### 세션 중 (행동 규칙)
- **한 Step씩 순차 실행** — 건너뛰기 금지
- **TDD**: 테스트 먼저 → 구현 → 검증 (`rules.md §8` 준수)
- **커밋**: 의미 있는 단위마다 (1시간에 2-4 커밋)
- **Codex review**: 주요 변경마다 adversarial review 실행
- **디컴파일러 변경**: `bash tests/decompiler/test_real_binary.sh` 실행
- **함수 탐지 변경**: `bash tests/benchmark/regression_harness.sh --aura build-rel/aura`
- **3회 실패 시**: 핸드오프 로그에 `BLOCKED: 이유` 기록, 다음 Step으로 이동

### 세션 종료 시 (필수)
1. AUTOMATION_ROADMAP.md의 현재 Step 상태 `[x]` 또는 `[B]` 갱신
2. 핸드오프 로그에 1줄 추가: `[날짜] 완료: X, 다음: Y, 차단: Z`
3. `git status` clean (미커밋 변경 없음)
4. `git push origin master`
