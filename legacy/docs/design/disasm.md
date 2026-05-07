# 디스어셈블러 모듈 설계

> 작성일: 2026-03-25
> 버전: 0.1.0
> 상태: 초기 설계 완료

---

## 1. 개요

디스어셈블러 모듈은 기계어 바이트 코드를 어셈블리 언어로 변환하는 핵심 기능을 제공한다.

### 1.1 설계 목표

| 항목 | 목표 |
|------|------|
| **정확도** | Capstone의 검증된 디스어셈블 정확도(≥99%) 상속 |
| **성능** | 네이티브 C 구현으로 빠른 처리 속도 |
| **간결성** | 최소한의 API로 모듈 사용 간편화 |

---

## 2. 아키텍처

```
┌─────────────────────────────────────────────────────────────┐
│                      User Application                        │
└──────────────────────┬──────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────┐
│              include/disasm.h (Public API)                   │
│  - DisasmContext struct                                      │
│  - disasm_init(), disasm_destroy(), disasm_run()             │
└──────────────────────┬──────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────┐
│              src/disasm/capstone_wrapper.c                   │
│         (Capstone 5.x Library Wrapper)                       │
│  - cs_open(), cs_disasm_iter(), cs_close()                   │
└──────────────────────┬──────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────┐
│              third_party/capstone/build/libcapstone.a        │
│                    (Static Library)                          │
└─────────────────────────────────────────────────────────────┘
```

---

## 3. 핵심 API

### 3.1 DisasmContext 구조체

```c
typedef struct DisasmContext DisasmContext;
```

- **Opaque pointer**: 외부에서는 구현 세부사항을 알 수 없음
- 내부적으로 Capstone의 `cs_handle`과 아키텍처 정보 보유

### 3.2 함수 시그니처

| 함수 | 설명 |
|------|------|
| `disasm_init(AuraArch)` | 컨텍스트 생성,Capstone 초기화 |
| `disasm_destroy(ctx)` | 리소스 해제 |
| `disasm_run(ctx, data, size, base_addr, results, max)` | 바이트 → 어셈블리 변환 |
| `disasm_set_option(ctx, opt, val)` | 디스어셈블 옵션 조정 |

### 3.3 DisasmResult 구조체

```c
typedef struct DisasmResult {
    AuraAddr address;       // 명령어 시작 주소
    uint8_t  bytes[16];     // 바이트 코드
    size_t   byte_count;    // 유효 바이트 수
    char     mnemonic[64];  // 니모닉 (mov, add 등)
    char     operand[128];  // 오퍼랜드 (eax, ebx 등)
} DisasmResult;
```

---

## 4. Capstone 5.x 채택 근거

### 4.1 선택 기준

PRD §4.2에서 명시한 대로 **Capstone ≥ 5.0**을 디스어셈블러 엔진으로 채택했다.

| 평가 항목 | Capstone 5.x | 비고 |
|----------|--------------|------|
| **정확도** | ≥99% (검증됨) | x86/x86_64, ARM 모두 지원 |
| **라이선스** | BSD-3-Clause | AURA와 호환 |
| **경량성** | ~1MB 정적 라이브러리 | 다른 프레임워크 대비 작음 |
| **C API** | 순수 C 구현 | AURA C/C++ 전략과 일치 |

### 4.2 연동 방식: third_party/ 서브모듈

**결정:** 시스템 패키지가 아닌 `third_party/capstone`을 정적 라이브러리로 사용

| 장점 | 설명 |
|------|------|
| **배포 단순성** | 외부 의존 없음, 정적 링크 |
| **버전 확정** | 프로젝트 고정 버전, 일관된 동작 |
| **빌드 제어** | CMakeLists.txt에서 직접 관리 |

### 4.3 빌드 통합

```cmake
# third_party/capstone/build/libcapstone.a 사용
add_library(capstone_static STATIC IMPORTED)
set_target_properties(capstone_static PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/capstone/build/libcapstone.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/third_party/capstone/include
)
```

---

## 5. 모듈 책임 분리

| 모듈 | 책임 | 의존 |
|------|------|------|
| `disasm.h` | 공개 인터페이스 정의 | `aura.h` (타입, 에러 코드) |
| `capstone_wrapper.c` | Capstone 래핑 구현 | `libcapstone.a`, `<capstone/capstone.h>` |
| `tests/test_disasm.c` | 단위 테스트 | `disasm.h`, `aura.h` |

---

## 6. 향후 확장 가능성

### 6.1 추가 옵션

```c
// 예: 디스어셈블 옵션 확장
#define DISASM_OPT_SYNTAX       0x01  // Intel vs AT&T syntax
#define DISASM_OPT_MNEMONIC     0x02  // 니모닉 포맷
#define DISASM_OPT_COMMENT      0x03  // 주석 추가 여부
```

### 6.2 멀티아키텍처 지원

| 아키텍처 | AuraArch 코드 | Capstone mode |
|----------|---------------|---------------|
| x86 | `AURA_ARCH_X86` | CS_ARCH_X86, CS_MODE_32 |
| x86_64 | `AURA_ARCH_X86_64` | CS_ARCH_X86, CS_MODE_64 |
| ARM | `AURA_ARCH_ARM` | CS_ARCH_ARM, CS_MODE_ARM |
| AArch64 | `AURA_ARCH_ARM64` | CS_ARCH_ARM64, CS_MODE_ARM |

---

## 7. 구현 일정

| 태스크 | 단계 |
|--------|------|
| **2.1** (이 태스크) | 설계 문서 작성 + 공개 API 정의 |
| 2.2 | Capstone 래퍼 구현 + 테스트 |
| 2.3 | ELF 로더 연동 |
| 2.4 | 메모리 매핑 및 섹션 분석 |

---

## 8. 관련 문서

- [PRD §4.2](../PRD.md) — 기술 사양: 외부 라이브러리 의존성
- [Capstone GitHub](https://github.com/capstone-engine/capstone) — 공식 저장소
- [Capstone 5.0 Release Notes](https://github.com/capstone-engine/capstone/releases/tag/5.0) — 주요 변경사항
