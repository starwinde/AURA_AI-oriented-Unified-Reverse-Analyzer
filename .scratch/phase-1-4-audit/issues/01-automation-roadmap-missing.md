# 01 — AUTOMATION_ROADMAP.md missing from repo root

**Status**: needs-triage
**Severity**: HIGH (process integrity)
**Phase impact**: cross-cutting (모든 Phase의 진행 상태 추적 도구 부재)

## 증상

`CLAUDE.md` (`.claude/CLAUDE.md` 동일)는 다음과 같이 명시:

> | 3 | `AUTOMATION_ROADMAP.md` | **Live canonical** — 현재 Phase/Step 상태, 핸드오프 로그 (rules.md §11.1) |

그리고 §자동화 세션 프로토콜 §1: "AUTOMATION_ROADMAP.md 읽기 → 현재 Phase/Step + 핸드오프 로그 확인"

그러나 실제 repo 루트에는 `AUTOMATION_ROADMAP.md` **부재**.

## 검증

```
$ ls AUTOMATION_ROADMAP.md
ls: cannot access 'AUTOMATION_ROADMAP.md': No such file or directory

$ git ls-files | grep -i automation_roadmap
legacy/AUTOMATION_ROADMAP.md     # legacy 폴더에만 존재
```

## 영향

- 자동화 세션 프로토콜이 첫 단계부터 실패
- Phase 진행 추적 canonical 문서가 없음 → `Tasks.md` 만으로는 sub-step 단위 핸드오프 추적 불가
- 본 점검도 "Phase 경계 식별"을 `Tasks.md`로만 수행 (canonical 손실)

## 제안 처리

| 옵션 | 내용 |
|---|---|
| A | `legacy/AUTOMATION_ROADMAP.md`를 루트로 promote + 갱신 |
| B | CLAUDE.md를 수정하여 `Tasks.md`만 canonical로 통합 |
| C | `AUTOMATION_ROADMAP.md`를 새로 만들고 Phase 1~4 핸드오프 로그를 `git log` 에서 재구성 |

D-결정 또는 사용자 결정 사안. **ready-for-human**.

## 참조

- `CLAUDE.md` L21
- `rules.md §11.1` (확인 필요 — 본 점검 read-only)
- `legacy/AUTOMATION_ROADMAP.md`
