# 04 — 미커밋 DIFF가 WIP 상태로 방치됨

**Status**: needs-triage
**Severity**: HIGH (baseline 무결성 손상)
**Phase impact**: Phase 4 GREEN baseline 주장 무효화

## 증상

`git status` 시점 (점검 시작):

```
 M .claude/CLAUDE.md
 M .claude/settings.local.json
 M CLAUDE.md
 M PRD.md
 M include/aura_compat.h
 M include/mapped_file.h
 M rules.md
 M src/decompiler/hir_emit.c
 M src/parser/file_format.c
 M src/parser/mapped_file.c
 M tests/core/test_data_refs.c
 M tests/parser/test_format_support.c
?? .claude/scheduled_tasks.lock
?? docs/agents/
?? include/unistd.h
?? src/core/aura_compat.c
```

**294 insertions across 12 files + 4 untracked**.

직전 커밋 메시지: `feat(phase-4d/4e.1): rendering-time overrides + conservative resolve pass`. 그 이전: `1b52c2ff chore(infra): MSVC/Windows build compat — Phase 4 GREEN baseline`.

## DIFF 작업 단위 분류

| 그룹 | 변경 항목 | 작업 단위 | 상태 |
|---|---|---|---|
| G1 | CLAUDE.md, .claude/CLAUDE.md, PRD.md, rules.md | 언어 정책 갱신 (2026-05-02) | ✅ 완성 |
| G2 | docs/agents/{issue-tracker,triage-labels,domain}.md, CLAUDE.md §Agent skills | agent skills 인프라 도입 | ✅ 완성 |
| G3 | include/aura_compat.h (대규모 확장), include/unistd.h (NEW), src/core/aura_compat.c (NEW) | MSVC POSIX 호환 shim 확장 | ⚠️ 부분 (G4 미완성에 종속) |
| G4 | src/decompiler/hir_emit.c (open_memstream → 래퍼) | open_memstream 마이그레이션 | 🔴 미완성 (issue 02) |
| G5 | src/parser/file_format.c (aligned_alloc → calloc) | MSVC aligned_alloc 회피 | ✅ 완성 |
| G6 | include/mapped_file.h (Windows에 int fd 추가) | Windows MappedFile fd 필드 | ⚠️ G7과 모순 (issue 06) |
| G7 | tests/core/test_data_refs.c, tests/parser/test_format_support.c (#ifndef _WIN32 가드) | 테스트의 fd 분기 가드 | ⚠️ G6과 모순 (issue 06) |
| G8 | src/parser/mapped_file.c (mf->fd = -1 한 줄) | Windows MappedFile fd 초기화 | ✅ G6의 일부 |
| N1 | .claude/settings.local.json | WSL rizin 명령 권한 추가 | ✅ 환경 |
| N2 | .claude/scheduled_tasks.lock | 런타임 락 파일 | 🗑️ gitignore 대상 |

## 핵심 통찰

**DIFF는 "Phase 4 GREEN baseline" 직후의 MSVC 호환 마이그레이션 도중 중단된 WIP**:
1. shim 인프라를 깔고 (G3)
2. 첫 모듈(hir_emit.c)에 적용했고 (G4 부분)
3. fd 처리 두 접근을 시도하다 (G6 vs G7)
4. **나머지 28+2 callsite에 도달하기 전에 종료**

`src/core/aura_compat.c` 는 빈 파일 + 주석 "Intentionally empty for now" — **사고가 중단된 흔적**.

## 영향

- "Phase 4 GREEN baseline" 커밋 메시지 (`1b52c2ff`) 가 **거짓**: 그 시점에도 MSVC는 RED.
- 본 점검의 baseline이 모호함 — `b0c625c1` HEAD인지, `1b52c2ff`인지, working tree(미커밋 포함)인지.
- 자동화 세션 protocol §1.4가 본 baseline에서 작동 불가 (빌드 fail).

## 제안 처리

| 옵션 | 내용 |
|---|---|
| P1 | G4 완성 (20 callsite 마이그레이션 + 헬퍼 추출) | 대규모. **issue 02로 분리** |
| P2 | DIFF 전체 stash + baseline = 1b52c2ff | 보수적. 1b52c2ff도 RED일 수 있음 |
| P3 | G1+G2+G5+G8 선별 커밋, 나머지 stash | 안전한 부분 보존 |
| P4 | DIFF 그대로 두고 점검만 진행 | 현재 진로 |

본 점검 진행 중에는 **P4** 가정. 점검 완료 후 처리 결정.

## ready-for-human

DIFF 처리 결정은 사용자 사안.
