# AURA 프로젝트 — AI 실행 컨텍스트

> 이 파일은 Claude Code(LLM)가 세션 시작 시 가장 먼저 읽는 최상위 지시 문서다.
> 작성일: 2026-03-25

---

## 프로젝트 개요

AURA는 C/C++로 구현하는 외부 엔진 통합형 리버스 엔지니어링 플랫폼이다. AURA 본체는
디컴파일러/디스어셈블러/타입 추론 엔진을 자체 구현하지 않고, Rizin/Ghidra 등 외부 엔진
결과를 수집·정규화·표시·override 하는 오케스트레이터 역할을 한다.

---

## 세션 시작 시 필독 문서

세션을 시작할 때마다 아래 순서대로 문서를 읽고 현재 상태를 파악한 뒤 작업을 수행한다.

| 순서 | 파일 | 목적 |
|------|------|------|
| 0 | `~/.claude/memory/MEMORY.md` | 전역 사용자 메모리 (모든 프로젝트 공통 — 사용자 선호, 행동 피드백) |
| 1 | `PRD.md` | 프로젝트 목표, 기능 요구사항, Open Decisions 확인 |
| 2 | `rules.md` | AI 행동 규칙, 중단 조건, 코드 스타일, 커밋 규칙, 문서 계층 (§11) |
| 3 | `AUTOMATION_ROADMAP.md` | **Live canonical** — 현재 Phase/Step 상태, 핸드오프 로그 (rules.md §11.1) |
| 4 | `Tasks.md` | **Release snapshot** — 릴리스 경계의 상태 (실시간 진행은 ROADMAP 우선, rules.md §11.2) |
| 5 | `AURA_MCP_플러그인_가이드.md` | MCP 환경 미구성 시 참조 |

> **문서 충돌 시 우선순위**: 제품/범위/결정은 `PRD.md`, 행동 규칙/멈춤 조건은 `rules.md`,
> 라이브 진행 상태는 `AUTOMATION_ROADMAP.md`, 릴리스 스냅샷은 `Tasks.md` 를 따른다.
> 상세는 `rules.md §11` 참조.

---

## 핵심 원칙

1. **언어 정책 (2026-05-02 갱신)**: AURA 는 **외부 도구 오케스트레이션** 방향으로 전환. AURA core (orchestrator / IPC / UI / project DB) 는 계속 C/C++. 외부 도구 호출 경로는 해당 도구가 요구하는 런타임을 그대로 받아들인다 (예: Ghidra subprocess → JVM, Rizin → 네이티브 바이너리). **사용 불가 환경 표기 의무**: 특정 도구의 런타임이 호스트에 없으면 (Ghidra 의 Java JRE 부재 등) 해당 기능을 "사용 불가"로 명시하고 **이유 + 요구 런타임 + 설치 안내**를 함께 노출해야 한다 (silent disable 금지).
2. **성능 우선**: AURA core 는 네이티브 코드 최적화. 외부 도구 비용은 IPC 경계 / 캐싱으로 흡수.
3. **MVP 집중**: 플러그인 시스템, 스크립트 인터페이스는 MVP 이후로 유보.
4. **정적 링크 우선**: AURA 가 직접 빌드하는 의존성은 가능하면 정적 링크. 외부 도구는 별도 프로세스 (D-27 Rizin subprocess-only 정책).
5. **외부 의존성 채택 기준** (D-26, 2026-04-26 reformulation): 라이선스 호환 (Apache 2.0 / MIT / BSD / Public Domain) + foundational commodity (산업 표준 존재 영역) + AURA 차별점 아님 = extract 우선 검토. **Differentiation 영역** (LLM 통합, UX, 협업, project DB, AI rename) = 커스텀 유지. 신규 의존성 도입은 `rules.md §10` 사용자 확인 gate 적용.
6. **Rizin 실행 기준 (ADR-0052, 2026-05-06)**: 현재 적용 기준은 **Rizin 0.8.0 shared64 + rz-ghidra 0.8.0** 이다. 기본 Windows 경로는 `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe`, `SLEIGHHOME` 은 같은 prefix 의 `lib/rizin/plugins/rz_ghidra_sleigh` 를 사용한다. 0.8.2 계열은 신규 시연/테스트 기준으로 사용하지 않는다.
7. **보안 제품 경고 처리 (ADR-0052)**: Defender/SmartScreen/EDR 이 AURA/Rizin/rz-ghidra 를 cyber security risk 로 표시할 수 있다. 이는 RE 도구의 외부 analyzer/plugin DLL/임의 바이너리 분석 특성상 예상 가능한 경고이며, 코드로 우회하지 않는다. 출처/버전/경로/해시와 로컬 분석/LLM 자동 전송 없음 원칙을 문서로 설명한다.

---

## 기술 스택

| 구성 요소 | 선택 | 비고 |
|-----------|------|------|
| 주 언어 | C11 / C++17 | 혼용 허용, 신규 모듈은 C++17 권장 |
| 디스어셈블/분석 primary | Rizin | subprocess + bulk JSON. `disasm` / `analyze` / `trace` primary, `decompile` co-primary |
| 디컴파일 co-primary | Ghidra `decompile/cpp/` + Rizin | `decompile` 은 사용자 선택. Ghidra 는 disasm/analyze/trace primary 권한 없음 |
| 보조 엔진 | Capstone / RetDec | Capstone = disasm secondary, RetDec = decompile secondary. primary 누락분 대체 금지 |
| JSON 파싱 | cJSON ✅ 확정 | 단일 파일, 정적 링크, LLM 응답 처리 |
| 파일 파싱 | 외부 엔진 출력 기반 ingestion | 자체 분석/함수 경계 생성 금지. 새 파서/라이브러리는 PRD §9 + rules.md §10 승인 필요 |
| 파일 I/O 방식 | mmap ✅ 확정 (D-6) | 500MB 대형 파일 lazy load, open() + mmap() |
| GUI 프레임워크 | Qt6 ✅ 확정 | 크로스플랫폼 지원 (2026-03-25 결정, D-1 완료) |
| HTTP 클라이언트 | libcurl ≥ 7.0 | LLM API 연동, OpenAI 호환 API 요청 |
| LLM 연동 | API/MCP/IPC 기반 | Phase 13 에서 privacy pre-filter + external MCP/IPC 방향으로 재정의 예정 |
| DB 엔진 | SQLite (amalgamation) | GUI 프로젝트 DB, Public Domain, `third_party/sqlite/` 소스 내장 (D-13, 2026-04-03 확정) |

---

## 프로젝트 구조

경로는 실제 환경에 맞게 적용한다. 아래는 표준 디렉토리 구조다.

```
<AURA_ROOT>/
├── src/
│   ├── core/           # Orchestrator, request/response, override, diagnostics
│   ├── adapter/        # rizin / ghidra 등 외부 엔진 subprocess adapter
│   ├── engine/         # probe / bootstrap / consent / command runner
│   ├── third_party_hub/# engine canonical mirror 격리 + normalized record 변환
│   ├── cli/            # CLI entrypoints
│   ├── llm/            # LLM 클라이언트/컨텍스트 provider 예정
│   └── gui/            # Qt6 UI. Orchestrator API 만 호출
├── include/            # 공개 헤더 파일
├── build-rel/          # 현재 릴리스 빌드 출력물 (git 제외)
├── tests/              # 단위 테스트 및 통합 테스트
├── third_party/        # 외부 라이브러리 (Capstone 등)
└── docs/               # 문서
```

---

## 개발 워크플로우

1. **태스크 순서 실행**: Tasks.md의 순서대로 하나씩 완료한다 (0.1 → 0.2 → ...).
2. **상태 표시**: 구현 완료 시 `[ ]` → `[-]`, DoD 검증 완료 시 `[-]` → `[x]`로 변경한다. (`[-]` = 구현 완료·검증 진행 중)
3. **설계 우선**: 구현 전에 설계 단계가 누락된 경우 설계를 먼저 추가한다.
4. **상세 규칙 준수**: 중단 조건, 코드 스타일, 커밋 규칙은 `rules.md`를 따른다.

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

## 중요: 소리 알림

내 요청에 응답하거나 명령을 실행한 후, 소리로 알려주려면 이 명령을 실행해 (Windows):

```powershell
powershell -NoProfile -Command "(New-Object Media.SoundPlayer 'C:\Windows\Media\notify.wav').PlaySync()"
```

대체 (간단한 비프음):

```powershell
powershell -NoProfile -Command "[console]::beep(800,300)"
```

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
5. **WSL 종료** — `wsl --shutdown` 실행. WSL 을 사용한 작업 (build-wsl 빌드/테스트 등) 끝나면 즉시 종료. WSL VM (`vmmem` 프로세스) 은 idle 상태에서도 GB 단위 메모리 점유함. 다음 사용 시 cold start ~5초 비용 < 메모리 절약 가치.

### WSL 사용 규칙 (2026-05-05 사용자 결정)
- **빌드/테스트 1회 끝날 때마다 `wsl --shutdown`** — 작업 묶음 끝나는 시점 (예: ctest GREEN 확인 후, commit 후)
- WSL 작업이 연속이면 (다음 명령에 또 WSL 사용) 종료 생략 가능
- 의심스러우면 종료 — cold start 비용 (~5초) 이 idle vmmem (1-4GB) 보다 저렴

---

## Agent skills

### Issue tracker

Local markdown — issues live as files under `.scratch/<feature-slug>/` in this repo. See `docs/agents/issue-tracker.md`.

### Triage labels

Default 5-role vocabulary (`needs-triage` / `needs-info` / `ready-for-agent` / `ready-for-human` / `wontfix`). See `docs/agents/triage-labels.md`.

### Domain docs

Single-context — `CONTEXT.md` + `docs/adr/` at the repo root. See `docs/agents/domain.md`.
