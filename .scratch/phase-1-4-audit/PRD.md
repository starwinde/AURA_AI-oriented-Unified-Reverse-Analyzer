# Phase 1~4 재점검 — PRD

**작성일**: 2026-05-03
**규율**: B + X (read-only audit + fix-only TDD; halt on `third_party/` modification)

---

## 배경

`Tasks.md` 기준 Phase 1~4 모두 sub-phase 단위로 `[x]` 또는 `[-]` 마킹됨. 그러나:
1. 직전 커밋 `1b52c2ff` 메시지는 "Phase 4 GREEN baseline"이지만 미커밋 DIFF + Windows MSVC 빌드 실패가 발견됨.
2. `AUTOMATION_ROADMAP.md`가 루트에 부재 (CLAUDE.md는 "Live canonical"로 지정).
3. Phase 1~4의 DoD (Definition of Done) 충족 여부가 환경 (Linux WSL vs MSVC) 별로 다름.

**점검 목적**: 각 Phase의 claimed-complete 항목이 *실제로 검증 가능한 baseline에서 작동*하는지 확인하고, 미해결 결함을 모두 등재.

---

## 범위 (in-scope)

| Phase | 점검 대상 |
|---|---|
| 1 | Engine Adapter Contract / Orchestrator Layer (1.1~1.8) |
| 2 | Rizin Adapter (2A.1~2A.11), Decompile (2B.1~2B.7), Ghidra Co-primary (2C.1~2C.6) |
| 3 | Unified Ingestion (3A~3F) |
| 4 | Override Layer (4A~4E) |

**범위 외**: Phase 5+ (GUI 등), 미완성 4D deferred 항목, 3C2 backlog.

---

## 점검 방법 (B 모드)

1. **Read-only**: 점검 단계에서 코드 수정 금지. 모든 발견은 `.scratch/phase-1-4-audit/issues/NN-*.md` 로 기록.
2. **검증 도구**:
   - 정적: `grep` / `Read` / `git log`로 claimed implementation 존재 검증
   - 동적: 가능한 경우 ctest 결과 확인 (Windows MSVC 환경 한정 — Linux/WSL은 실행 불가)
3. **DoD 매칭**: 각 sub-phase의 인용된 파일·라인·테스트가 실제로 존재하고 통과 가능한지 확인.

---

## 중단 트리거 (X 모드)

다음 시 즉각 중단 + 사용자 결정 요청:

- `third_party/` 디렉토리 수정 필요 (Capstone, SQLite, cJSON, tinyxml2, Rizin vendored 등)
- 3rd-party 라이선스 영향이 있는 결정
- D-결정 변경이 필요한 발견 (PRD §9 신규 D 도입 사안)

**중단하지 않는 경우**:
- AURA 자체 코드(`src/`, `include/`, `tests/`)의 cross-Phase 영향
- 빌드 설정 (`CMakeLists.txt`)
- 문서 (`docs/`, `*.md`)

---

## DoD (Definition of Done — 본 점검의)

1. ✅ `issues/` 에 발견 항목 N개 등재 (각 항목: `Status:` 라벨, 영향 Phase, 심각도, 재현 방법)
2. ✅ 최종 종합 리포트 `summary.md` 작성 — Phase별 GREEN / GREEN-on-Linux-only / RED 분류
3. ✅ `Tasks.md` `[x]` 표기와 실제 상태의 괴리 항목 모두 식별
4. ✅ `.claude/settings.local.json` / `docs/agents/`와 같은 안전 노이즈 제외, 본질적 결함만 추출

---

## 트리아지 라벨

`docs/agents/triage-labels.md` 따름:
- `needs-triage` — 발견 직후 (분류 미정)
- `needs-info` — 추가 검증 필요
- `ready-for-agent` — 본 세션 또는 후속 자동화 세션이 처리 가능
- `ready-for-human` — 인간 결정 필요 (D-결정, 라이선스, 정책)
- `wontfix` — 의도된 결함 / 범위 외

---

## Baseline

- **Git baseline**: `b0c625c1` (현재 HEAD)
- **미커밋 DIFF**: 그대로 보존 (수정 없음)
- **빌드 baseline**: Linux WSL = GREEN 가정 (Tasks.md 기록 신뢰), Windows MSVC = RED 확인됨

---

## 산출물 구조

```
.scratch/phase-1-4-audit/
├── PRD.md                          ← 본 문서
├── summary.md                      ← 최종 종합 (마지막에 작성)
└── issues/
    ├── 01-automation-roadmap-missing.md
    ├── 02-msvc-open-memstream-incomplete.md
    ├── ...
    └── NN-*.md
```
