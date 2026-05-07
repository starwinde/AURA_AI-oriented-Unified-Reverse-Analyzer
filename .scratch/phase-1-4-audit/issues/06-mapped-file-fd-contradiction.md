# 06 — `MappedFile.fd` 처리에 두 경쟁 접근이 working tree에 동시 존재

**Status**: needs-triage
**Severity**: MEDIUM (architectural ambiguity)
**Phase impact**: Phase 1 (parser/mapped_file)

## 증상

미커밋 DIFF에 같은 문제(Windows에서 `MappedFile.fd` 미존재)에 대한 **두 모순된 해결**이 공존:

### 접근 A — 헤더에 fd 추가 (G6)

`include/mapped_file.h` 변경:

```c
typedef struct {
#ifdef _WIN32
    void          *hFile;
    void          *hMapping;
    int            fd;        /**< POSIX-compat sentinel for legacy tests  */  // ← 추가
#else
    int            fd;
#endif
    ...
} MappedFile;
```

→ Windows에도 `fd` 필드 존재. 테스트는 `mf->fd = -1` 그대로 작동.

### 접근 B — 테스트에 #ifdef 가드 (G7)

`tests/core/test_data_refs.c`, `tests/parser/test_format_support.c` 변경:

```c
MappedFile *mf = (MappedFile *)calloc(1, sizeof(MappedFile));
if (!mf) return NULL;
#ifndef _WIN32
    mf->fd = -1;     // Windows에서는 fd 필드 없으므로 skip
#endif
```

→ 테스트가 Windows에서는 fd를 건드리지 않음.

## 문제

**A를 채택하면 B가 불필요**, **B를 채택하면 A가 불필요**. 둘 다 적용된 현 상태:
- 일관성 없음 (header는 Windows에 fd 두는데 일부 테스트는 #ifndef로 가드)
- 새 테스트 작성 시 어느 패턴을 따라야 할지 모호
- 작성자가 두 접근을 시도하다 한 쪽을 정리 못 한 흔적

## 제안 처리

**A 권장 (단일 헤더 truth)**:
- B의 #ifndef 가드 제거 → 테스트 코드 간결
- 헤더가 truth → 모든 플랫폼 동일 코드 경로
- `fd = -1` sentinel은 Windows에서도 의미가 명확 ("POSIX-compat sentinel")

또는 **B 권장 (구조 단순)**:
- header의 Windows 분기에 fd 제거 → 진정한 platform-specific struct
- 모든 fd 사용처에 #ifndef 강제

**둘 중 하나 선택, 나머지 폐기**. **ready-for-agent** (단순 정리 작업).

## 추가 검증 필요

`mapped_file.c` 의 `mapped_file_open` (L68)이 Windows 분기에서 `mf->fd = -1` 초기화 추가됨 (G8). 이는 **A와 일관**. 즉 작성자는 A에 더 가까운 의도였던 것으로 추정.

## 영향

작은 결함이지만 **DIFF 무결성** 의 신호:
- Phase 4 GREEN baseline 직후의 작업이 깔끔하게 마무리되지 않았다는 증거
- issue 02, 04와 함께 WIP 누적 패턴

## 관련 issue

- 04 (DIFF WIP)
