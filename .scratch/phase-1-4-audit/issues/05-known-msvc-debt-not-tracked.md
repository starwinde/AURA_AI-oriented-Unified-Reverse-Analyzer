# 05 — 알려진 MSVC 부채가 추적 시스템에 등재되지 않음

**Status**: needs-triage
**Severity**: MEDIUM (process gap)
**Phase impact**: cross-cutting

## 증상

`Tasks.md` Phase 2A.11 status note (L84~92)에 다음과 같은 자기 인식 기록:

> Windows MSVC 인프라 결함 (Phase 2A 범위 외, 별도 작업으로 분리):
>   - YARA `sys/mman.h` 기존에 알려짐. Windows MSVC 디폴트 OFF 로 우회 (`AURA_BUILD_YARA`).
>   - 추가 발견: GCC 전용 `__attribute__((aligned(64)))` (file_format.h),
>     `unistd.h` 직접 include (decompile_metrics, decompile_all, mapped_file,
>     engine_subprocess 외 5+ 파일), `__attribute__((unused/noreturn))` 다수.
>   - 부분 fix 보존 (향후 Windows 포팅 대비):
>     • `AURA_FILEINFO_ALIGN` shim — file_format.h
>     • `src/third_party_hub` include path — CMakeLists.txt (rizin_to_aura.h 누락)
>   - Windows MSVC 전체 포팅은 별도 인프라 작업 (수 시간~1일 추정).

Phase 2 재점검 로그(L207)에서 동일 항목 재기록:

> **Windows MSVC 포팅**: `__attribute__((aligned))`, `unistd.h` 직접 include, GCC 전용 attribute 다수 잔존 (9+ 파일). Phase 2A.11 부분 fix (file_format.h shim, third_party_hub include path, YARA opt-out) 보존; 전체 포팅은 별도 인프라 작업.

## 문제

**"별도 작업으로 분리" 처리가 실제로 트래킹되지 않음**:

- `legacy/AUTOMATION_ROADMAP.md` 외 별도 backlog 파일 없음 (issue 01 참조)
- `Tasks.md`의 Phase 6/7/8에 등재되지 않음
- 별도 design doc 없음
- 그 이후 Phase 4 진입 시 baseline 검증에 포함되지 않음

→ "분리" = 사실상 **방치**. issue 02 (open_memstream), issue 03 (weak attribute) 모두 이 카테고리.

## 영향

- "Phase X GREEN" 주장이 실제로 Linux only를 의미하는데 그 가정이 명시되지 않음
- 신규 Phase 진입 시마다 MSVC 부채가 누적
- DoD 정의 모호 — 어느 환경에서 GREEN이어야 통과인가?

## 제안 처리

| 단계 | 내용 |
|---|---|
| 1 | `Tasks.md` 상태 표기 갱신 — 모든 `[x]` 에 환경 명시 (Linux/MSVC/macOS) |
| 2 | MSVC 포팅을 Phase 8 (Performance/mmap) 또는 신규 Phase 9 (Platform Coverage)로 정식 등재 |
| 3 | `Tasks.md` 상단에 환경 baseline 표 추가 |
| 4 | (alternative) MSVC를 정식 지원 환경에서 제외하고 "Linux WSL only"로 정책 명문화 |

**ready-for-human** (정책 결정 필요).

## 관련 issue

- 01 (AUTOMATION_ROADMAP.md missing)
- 02, 03 (구체적 MSVC 결함)
