# Phase 3 — Section / Symbol 구조체 필드 상세 설계

> ⚠️ **구버전 문서** — 최신 확정 내용은 [`parser.md`](./parser.md) 를 참조하세요.

> 작성일: 2026-03-26
> 목적: `Section` / `Symbol` 각 필드의 필요성, 크기 결정 근거, 포맷 간 매핑, 메모리 레이아웃을 상세히 기술
> 상태: ✅ 확정됨 (구버전 — parser.md 참조)
> 선행 문서: `docs/design/phase3_section_symbol_design.md` (비교 개요)

---

## 1. Section 구조체 상세

### 1.1 필드별 분석

#### `name` — 섹션 이름

| 항목 | 내용 |
|------|------|
| 용도 | 섹션 식별, `aura --info` 출력, 코드/데이터 분류 |
| 사용 Phase | 3 (파서), 5 (디컴파일러), 8 (GUI 섹션 뷰) |

**포맷별 이름 길이 실측:**

| 포맷 | 최대 길이 | 예시 |
|------|-----------|------|
| ELF | 제한 없음 (string table) | `.text`, `.rodata`, `.eh_frame_hdr` (최대 ~30자) |
| PE | 8바이트 고정 | `.text`, `.rdata`, `.reloc` |
| Mach-O | sectname 16 + segname 16 = 32 | `__text` / `__TEXT` |

실제 바이너리에서 관찰되는 최장 ELF 섹션명: `.gnu.version_r` (14자), `.debug_info` (11자).
비표준 디버그 심볼이나 링커 스크립트 생성 섹션은 30자 이상 가능.

**크기 선택지:**

| 크기 | 장점 | 단점 |
|------|------|------|
| 16바이트 | Mach-O sectname 꼭 맞음, 메모리 절약 | ELF 긴 이름 잘림 가능 |
| 32바이트 | 실측 기준 충분 | 미래 확장 여유 부족 |
| **64바이트** | 모든 포맷 여유 있게 수용 | Section 1개당 56바이트 낭비 |
| 포인터 (`char *`) | 크기 제한 없음 | malloc 필요, 소유권 복잡 |

**권고**: `char name[64]` — 실측 최대 대비 2배 여유, 정적 할당으로 소유권 단순

---

#### `vaddr` — 가상 주소 (Virtual Address)

| 항목 | 내용 |
|------|------|
| 용도 | 디스어셈블 시 주소 기준점, CFG 노드 주소 계산, `aura --info` 주소 출력 |
| 포맷별 필드 | ELF: `sh_addr` / PE: `VirtualAddress`(RVA, ImageBase 더해야 절대 주소) / Mach-O: `addr` |
| 타입 | `uint64_t` — ELF64/PE32+/Mach-O 64 모두 64비트 주소 지원 필요 |
| 특이사항 | PE의 경우 RVA(상대 가상 주소)를 저장할지, ImageBase 합산 절대 주소를 저장할지 결정 필요 |

**PE RVA 처리 선택지:**

| 방식 | 장점 | 단점 |
|------|------|------|
| RVA 그대로 저장 | 파일 원본 값 보존 | 주소 사용 시마다 ImageBase 더해야 함 |
| **절대 주소로 변환 후 저장** | 사용 측 코드 단순 (ELF/PE/Mach-O 동일 인터페이스) | 파서에서 변환 처리 필요 |

**권고**: 절대 주소 변환 후 저장 — 파서 1곳에서 처리, 이후 모든 코드 단순화

---

#### `offset` — 파일 오프셋

| 항목 | 내용 |
|------|------|
| 용도 | mmap 기반 직접 접근: `file->map + section->offset` 으로 섹션 데이터 접근 |
| 포맷별 필드 | ELF: `sh_offset` / PE: `PointerToRawData` / Mach-O: `offset` |
| 타입 | `uint64_t` |
| 특이사항 | BSS 섹션(ELF NOBITS)은 파일에 데이터 없음 → offset=0, size>0 케이스 처리 필요 |

---

#### `size` — 섹션 크기

| 항목 | 내용 |
|------|------|
| 용도 | 경계 검사, 디스어셈블 범위 결정, mmap 접근 범위 |
| 포맷별 필드 | ELF: `sh_size` / PE: `VirtualSize`와 `SizeOfRawData` 두 가지 존재 / Mach-O: `size` |
| 타입 | `uint64_t` |

**PE 크기 두 가지 처리:**

| 필드 | 의미 | AURA 사용 |
|------|------|-----------|
| `VirtualSize` | 메모리에 로드된 실제 크기 | 분석 기준 크기로 사용 |
| `SizeOfRawData` | 파일에서의 크기 (정렬 패딩 포함) | mmap 접근 시 사용 |

**권고**: `size`는 `VirtualSize` 기준 저장, `file_size` 추가 필드로 `SizeOfRawData` 보존

---

#### `flags` — 권한 플래그

| 항목 | 내용 |
|------|------|
| 용도 | 코드/데이터 구분, 디스어셈블 대상 판별, 분석 정책 결정 |
| 포맷별 필드 | ELF: `sh_flags` / PE: `Characteristics` / Mach-O: `flags` |

**포맷별 플래그 매핑:**

| AURA 플래그 | ELF | PE | Mach-O |
|-------------|-----|----|--------|
| `AURA_SEC_READ` | `SHF_ALLOC` (암묵적) | `IMAGE_SCN_MEM_READ` | 기본 포함 |
| `AURA_SEC_WRITE` | `SHF_WRITE` | `IMAGE_SCN_MEM_WRITE` | `S_ATTR_NO_TOC` 반전 |
| `AURA_SEC_EXEC` | `SHF_EXECINSTR` | `IMAGE_SCN_MEM_EXECUTE` | `S_ATTR_PURE_INSTRUCTIONS` |

---

#### `file_size` — 파일상 크기 (PE 전용)

PE의 `SizeOfRawData`를 별도 보존. ELF/Mach-O에서는 `size`와 동일값.

---

### 1.2 Section 최종 후보 구조체

```c
/* 권한 플래그 */
#define AURA_SEC_READ   0x01u
#define AURA_SEC_WRITE  0x02u
#define AURA_SEC_EXEC   0x04u

typedef struct {
    char        name[64];       /* 섹션 이름 (.text, __TEXT.__text 등)     */
    uint64_t    vaddr;          /* 가상 주소 (절대 주소, PE RVA 변환 후)    */
    uint64_t    offset;         /* 파일 오프셋 (mmap 접근용)                */
    uint64_t    size;           /* 메모리 기준 크기 (VirtualSize)           */
    uint64_t    file_size;      /* 파일 기준 크기 (SizeOfRawData, PE 전용)  */
    uint32_t    flags;          /* AURA_SEC_READ | WRITE | EXEC             */
} Section;
/* sizeof(Section) = 64 + 8*4 + 4 = 100바이트 → 패딩 후 104바이트 */
```

---

## 2. Symbol 구조체 상세

### 2.1 필드별 분석

#### `name` — 원본 심볼 이름 (mangled 포함)

| 항목 | 내용 |
|------|------|
| 용도 | 원본 보존, demangle 실패 시 폴백, 디버그 |
| 저장 방식 선택지 | 고정 버퍼 vs 포인터 |

**버퍼 크기 실측 분석:**

| 심볼 유형 | 최대 길이 예시 |
|-----------|--------------|
| C 함수 | `pthread_create` (15자) |
| C++ 일반 메서드 | `_ZN4AURA6Parser9parse_elfEPK8MappedFile` (42자) → 디맹글: `AURA::Parser::parse_elf(MappedFile const*)` (46자) |
| C++ 템플릿 (단순) | `_ZNSt6vectorIiSaIiEE9push_backERKi` (36자) → 디맹글: `std::vector<int, std::allocator<int>>::push_back(int const&)` (62자) |
| C++ 템플릿 (복잡) | `_ZNSt8__detail15_List_node_baseINSt13__atomic_baseImEEE` → 디맹글: 200자+ |
| 극단적 템플릿 | Boost.MPL, TMP 코드 → **1000자 이상** |

**저장 방식 비교:**

| 방식 | 장점 | 단점 |
|------|------|------|
| `char name[256]` | 정적 할당, 소유권 단순, 캐시 친화적 | 256자 초과 심볼 잘림 (실제 발생) |
| `char name[512]` | 대부분 케이스 수용 | Symbol 1개당 512바이트 → 10만 심볼 시 50MB |
| `const char *name` (mmap 포인터) | 할당 없음, 크기 제한 없음 | 문자열 테이블 오프셋 계산 필요, mmap 해제 전에만 유효 |
| `char *name` (heap) | 크기 제한 없음 | malloc/free 필요, 소유권 복잡 |

**권고**: `const char *name` — mmap 내 string table을 직접 가리킴, 할당 없음, 크기 제한 없음
- 단, mmap 생명주기 동안만 유효 → FileInfo 소유권 규칙으로 보장됨

---

#### `demangled` — 디맹글 이름

| 항목 | 내용 |
|------|------|
| 용도 | `aura --info` 가독성 있는 출력, Phase 6 LLM에 전달할 함수명 |
| 채우는 시점 | 3.6 태스크에서 `aura_demangle()` 호출 |
| 실패 시 | `name`과 동일값 복사 |

`name`을 포인터로 쓰면 `demangled`는 heap 또는 별도 버퍼 필요:
- `__cxa_demangle`이 `malloc`으로 반환 → `free()` 필요
- Symbol 구조체에 고정 버퍼 두거나, 포인터 + 별도 해제

**권고**: `char *demangled` (heap, `__cxa_demangle` 반환값 직접 소유)
- `symbol_destroy()`에서 `free(sym->demangled)` 처리

---

#### `address` — 심볼 주소

| 항목 | 내용 |
|------|------|
| 용도 | CFG 진입점, 디스어셈블 기준, cross-reference |
| 포맷별 필드 | ELF: `st_value` / PE: `Value` + ImageBase / Mach-O: `n_value` |
| 타입 | `uint64_t` |
| 특이사항 | ELF 재배치 오브젝트(`.o`)는 `st_value`가 섹션 내 오프셋 — 실행 바이너리에서만 절대 주소 |

---

#### `size` — 심볼 크기

| 항목 | 내용 |
|------|------|
| 용도 | 함수 범위 결정, 디스어셈블 종료 지점 |
| 포맷별 지원 | ELF: `st_size` ✅ / PE: ❌ 없음 / Mach-O: ❌ 없음 |
| 없는 경우 | 0으로 저장, 다음 심볼 주소로 추정 (Phase 4에서 처리) |

**권고**: 포함. PE/Mach-O에서는 0, Phase 4 CFG 분석으로 보완.

---

#### `type` — 심볼 종류

| AURA 열거값 | ELF | PE StorageClass | Mach-O |
|-------------|-----|-----------------|--------|
| `AURA_SYM_FUNCTION` | `STT_FUNC` | `IMAGE_SYM_CLASS_FUNCTION` | `N_FUN` |
| `AURA_SYM_OBJECT` | `STT_OBJECT` | `IMAGE_SYM_CLASS_STATIC` | `N_GSYM` |
| `AURA_SYM_IMPORT` | `STT_NOTYPE` + `.plt` 섹션 | Import Table 항목 | `INDIRECT_SYMBOL` |
| `AURA_SYM_EXPORT` | `STB_GLOBAL` + `STT_FUNC` | Export Table 항목 | `N_EXT` |
| `AURA_SYM_UNKNOWN` | `STT_NOTYPE`, 기타 | 기타 | 기타 |

---

#### `binding` — 바인딩 범위

| AURA 열거값 | ELF | PE | Mach-O |
|-------------|-----|----|--------|
| `AURA_BIND_LOCAL` | `STB_LOCAL` | STATIC StorageClass | N_EXT 없음 |
| `AURA_BIND_GLOBAL` | `STB_GLOBAL` | EXTERNAL StorageClass | `N_EXT` |
| `AURA_BIND_WEAK` | `STB_WEAK` | WEAK_EXTERNAL | `N_WEAK_DEF` |

---

### 2.2 Symbol 최종 후보 구조체

```c
typedef enum {
    AURA_SYM_UNKNOWN  = 0,
    AURA_SYM_FUNCTION = 1,
    AURA_SYM_OBJECT   = 2,
    AURA_SYM_IMPORT   = 3,
    AURA_SYM_EXPORT   = 4,
} AuraSymType;

typedef enum {
    AURA_BIND_LOCAL  = 0,
    AURA_BIND_GLOBAL = 1,
    AURA_BIND_WEAK   = 2,
} AuraSymBinding;

typedef struct {
    const char     *name;           /* mmap 내 string table 직접 포인터  */
                                    /* (FileInfo 해제 전까지 유효)        */
    char           *demangled;      /* __cxa_demangle 반환값 (heap)       */
                                    /* NULL이면 name과 동일로 간주        */
    uint64_t        address;        /* 절대 주소 (PE: RVA + ImageBase)    */
    uint64_t        size;           /* 심볼 크기 (ELF만 유효, 나머지 0)   */
    AuraSymType     type;
    AuraSymBinding  binding;
} Symbol;
/* sizeof(Symbol) = 8+8+8+8+4+4 = 40바이트 */
```

---

## 3. 메모리 레이아웃 영향

### 10만 심볼 기준 메모리 사용량

| 방식 | Symbol 1개 크기 | 10만 개 합계 |
|------|----------------|-------------|
| 고정 버퍼 `name[256] + demangled[256]` | 536바이트 | **~54MB** |
| 포인터 방식 (권고안) | 40바이트 | **~4MB** |

포인터 방식이 실제 바이너리 분석 시 메모리 사용량에서 압도적으로 유리.

---

## 4. 소유권 규칙

```
MappedFile (mmap)
    └─ FileInfo
          ├─ Section[]     → 정적 배열, FileInfo와 함께 해제
          └─ Symbol[]
                ├─ name    → MappedFile.map 내부 포인터 (별도 해제 불필요)
                └─ demangled → heap (symbol_destroy()에서 free())

file_info_destroy(FileInfo *info)
    → Symbol 배열 순회하며 demangled free()
    → sections free()
    → symbols free()
    → mapped_file_destroy(info->file)  ← munmap + close
```

---

## 5. 미결 항목 및 결정 필요 사항

| # | 항목 | 선택지 | 권고 |
|---|------|--------|------|
| 1 | `Section.name` 저장 방식 | 고정 `char[64]` vs mmap 포인터 | `char[64]` — 섹션 수 적음 (수십 개), 단순성 우선 |
| 2 | `Symbol.name` 저장 방식 | 고정 버퍼 vs mmap 포인터 | **mmap 포인터** — 심볼 수 많음 (수만 개), 메모리 절약 |
| 3 | `Symbol.demangled` 저장 방식 | 고정 버퍼 vs heap | **heap** (`__cxa_demangle` 반환값 직접 사용) |
| 4 | `Section.file_size` 포함 여부 | 포함 vs 제거 | **포함** — PE mmap 접근 시 필요 |
| 5 | `Symbol.size` 포함 여부 | 포함(0) vs 제거 | **포함(0)** — Phase 4 CFG에서 활용 |
| 6 | `demangled == NULL` 처리 | NULL 허용 vs 항상 채움 | NULL 허용, 출력 시 `name` 폴백 |

---

## 6. 관련 결정 사항

| 항목 | 결정 | 일자 |
|------|------|------|
| 파일 I/O 방식 | mmap 확정 (D-6) | 2026-03-26 |
| FileInfo 구조체 | B안 2레이어 확정 (D-10) | 2026-03-26 |
| C++ demangle 방식 | `__cxa_demangle` 채택, PRD §4.2 등재 | 2026-03-26 |
| **Section 필드** | **🔴 미확정 — 이 문서 기반 결정 필요** | — |
| **Symbol 필드** | **🔴 미확정 — 이 문서 기반 결정 필요** | — |
