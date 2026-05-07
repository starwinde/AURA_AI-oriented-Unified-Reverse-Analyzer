# Phase 3 — Section / Symbol 구조체 확정 설계

> ⚠️ **구버전 문서** — 최신 확정 내용은 [`parser.md`](./parser.md) 를 참조하세요.

> 작성일: 2026-03-26
> 목적: Section / Symbol 구조체 필드 확정 결과 및 장단점 기록
> 상태: ✅ 확정 (2026-03-26)
> 선행 문서: `docs/design/phase3_section_symbol_fields.md` (상세 비교)

---

## 1. 확정 결정 사항

| # | 항목 | 결정 |
|---|------|------|
| 1 | `Section.name` 저장 방식 | `char *` + `strdup()` |
| 2 | `Symbol.name` 저장 방식 | `char *` + `strdup()` |
| 3 | `Symbol.demangled` 저장 방식 | `__cxa_demangle` 반환값 직접 소유 |
| 4 | `Section.file_size` 포함 여부 | 포함 |
| 5 | `Symbol.size` 포함 여부 | 포함 (PE/Mach-O는 0) |
| 6 | `demangled == NULL` 처리 | NULL 허용, 사용 측에서 `name` 폴백 |

---

## 2. 확정 구조체

### 2.1 Section

```c
/* 권한 플래그 */
#define AURA_SEC_READ   0x01u
#define AURA_SEC_WRITE  0x02u
#define AURA_SEC_EXEC   0x04u

typedef struct {
    char           *name;       /* strdup() 복사본, Section 소유           */
                                /* section_destroy() 에서 free()           */
    uint64_t        vaddr;      /* 가상 주소 (절대 주소, PE RVA 변환 후)   */
    uint64_t        offset;     /* 파일 오프셋 (mmap 직접 접근용)          */
    uint64_t        size;       /* 메모리 기준 크기 (VirtualSize)          */
    uint64_t        file_size;  /* 파일 기준 크기 (PE SizeOfRawData)       */
                                /* ELF/Mach-O 는 size 와 동일값           */
    const uint8_t  *data;       /* mmap 포인터 (읽기 전용)                 */
                                /* fi->file->map + offset                 */
    uint32_t        flags;      /* AURA_SEC_READ | WRITE | EXEC           */
} Section;
```

### 2.2 Symbol

```c
typedef enum {
    AURA_SYM_UNKNOWN  = 0,
    AURA_SYM_FUNCTION = 1,   /* STT_FUNC / IMAGE_SYM_TYPE_FUNCTION        */
    AURA_SYM_OBJECT   = 2,   /* STT_OBJECT / 데이터 변수                  */
    AURA_SYM_IMPORT   = 3,   /* 외부 임포트 심볼                           */
    AURA_SYM_EXPORT   = 4,   /* 익스포트 심볼                              */
} AuraSymType;

typedef enum {
    AURA_BIND_LOCAL  = 0,    /* STB_LOCAL                                  */
    AURA_BIND_GLOBAL = 1,    /* STB_GLOBAL                                 */
    AURA_BIND_WEAK   = 2,    /* STB_WEAK                                   */
} AuraSymBinding;

typedef struct {
    char           *name;       /* strdup() 복사본, Symbol 소유            */
                                /* symbol_destroy() 에서 free()            */
    char           *demangled;  /* __cxa_demangle 반환값, Symbol 소유      */
                                /* NULL 가능 — C 함수 또는 demangle 실패   */
                                /* 사용 측: sym->demangled ? : sym->name   */
    uint64_t        address;    /* 절대 주소 (PE: RVA + ImageBase)         */
    uint64_t        size;       /* 심볼 크기 (ELF st_size, PE/Mach-O는 0) */
    AuraSymType     type;
    AuraSymBinding  binding;
} Symbol;
```

---

## 3. 소유권 및 생명주기

```
파서 (elf_parser / pe_parser / macho_parser)
    │
    ├─ strdup(section_name)   → Section.name    (Section 소유)
    ├─ strdup(symbol_name)    → Symbol.name     (Symbol 소유)
    └─ __cxa_demangle(...)    → Symbol.demangled (Symbol 소유, NULL 가능)

file_info_destroy(FileInfo *info)
    ├─ for each Section  → section_destroy()
    │       └─ free(section->name)
    ├─ free(info->sections)
    ├─ for each Symbol   → symbol_destroy()
    │       ├─ free(symbol->name)
    │       └─ if (symbol->demangled) free(symbol->demangled)
    ├─ free(info->symbols)
    └─ mapped_file_destroy(info->file)  ← munmap + close
```

---

## 4. 포맷별 필드 매핑

### Section

| AURA 필드 | ELF | PE | Mach-O |
|-----------|-----|----|--------|
| `name` | string table에서 복사 | `Name[8]` 복사 | `segname + "/" + sectname` 조합 |
| `vaddr` | `sh_addr` | `VirtualAddress + ImageBase` | `addr` |
| `offset` | `sh_offset` | `PointerToRawData` | `offset` |
| `size` | `sh_size` | `VirtualSize` | `size` |
| `file_size` | `sh_size` (동일) | `SizeOfRawData` | `size` (동일) |
| `flags` | `SHF_*` 변환 | `Characteristics` 변환 | `flags` 변환 |

### Symbol

| AURA 필드 | ELF | PE | Mach-O |
|-----------|-----|----|--------|
| `name` | string table에서 strdup | COFF string table에서 strdup | string table에서 strdup |
| `demangled` | `__cxa_demangle(name)` | `__cxa_demangle(name)` (MSVC `?` prefix 미지원) | `__cxa_demangle(name)` |
| `address` | `st_value` | `Value + ImageBase` | `n_value` |
| `size` | `st_size` | 0 | 0 |
| `type` | `STT_*` 변환 | StorageClass 변환 | `n_type` 변환 |
| `binding` | `STB_*` 변환 | StorageClass 변환 | `N_EXT` 여부 |

---

## 5. 장단점 분석

### Section

| 장점 | 단점 |
|------|------|
| 이름 길이 제한 없음 — 비표준 섹션명도 완전 보존 | `strdup()` 실패 시 NULL 처리 코드 필요 |
| mmap 수명과 독립 — 파일 닫은 후에도 섹션 이름 유효 | `section_destroy()` 에서 반드시 `free(name)` 호출 필요 |
| `file_size` 분리로 PE mmap 접근 정확 | ELF/Mach-O에서 `size == file_size` 중복 저장 |

### Symbol

| 장점 | 단점 |
|------|------|
| 이름 길이 제한 없음 — 1000자+ 템플릿 심볼도 완전 보존 | 심볼 10만 개 기준 `strdup()` 10만 회 호출 |
| `demangled` 직접 소유로 복사 비용 없음 | `demangled` NULL 체크를 사용 측 모든 곳에서 해야 함 |
| `size` 포함으로 Phase 4 CFG 분석 시 함수 범위 즉시 활용 | PE/Mach-O는 `size=0` → Phase 4에서 별도 추정 로직 필요 |
| LLM에 demangled 전달 시 전체 이름 손실 없음 | `symbol_destroy()` 에서 `name`, `demangled` 각각 `free()` 필요 |

### 전체 공통

| 장점 | 단점 |
|------|------|
| ELF/PE/Mach-O 동일 인터페이스 — 파서별 분기 최소화 | 동적 할당이 많아 ASAN/valgrind 검증 필수 |
| 소유권 명확 — 각 구조체가 자신의 문자열 소유 | `_destroy()` 함수 누락 시 메모리 누수 발생 |
| Phase 6 LLM 연동 시 demangled 그대로 활용 가능 | `demangled == NULL` 폴백 로직이 여러 곳에 분산될 수 있음 |

---

## 6. 리스크 및 대응

| 리스크 | 발생 시점 | 대응 |
|--------|----------|------|
| `free()` 누락으로 메모리 누수 | 3.2~3.4 파서 구현 시 | ASAN + valgrind 의무화 |
| `demangled NULL` 미처리로 크래시 | 3.5 `--info` 출력 구현 시 | 출력 함수에 `AURA_SYM_NAME(sym)` 매크로 정의 |
| `strdup()` 실패 (메모리 부족) | 대형 바이너리 분석 시 | 반환값 NULL 체크 필수, `AURA_ERR_OOM` 에러 코드로 전파 |
| PE MSVC 심볼 (`?` prefix) demangle 실패 | 3.3 PE 파서 구현 시 | `demangled = NULL` 처리, Phase 3 범위 내 허용 |

---

## 7. 편의 함수 (구현 권고)

```c
/* demangled NULL 폴백 — 인라인 함수로 타입 안전성 확보 */
static inline const char *symbol_display_name(const Symbol *s) {
    return s->demangled ? s->demangled : s->name;
}
```

---

## 8. 관련 결정 사항

| 항목 | 결정 | 일자 |
|------|------|------|
| 파일 I/O 방식 | mmap 확정 (D-6) | 2026-03-26 |
| FileInfo 구조체 | B안 2레이어 확정 (D-10) | 2026-03-26 |
| C++ demangle 방식 | `__cxa_demangle` 채택, PRD §4.2 등재 | 2026-03-26 |
| **Section 필드** | **✅ 확정 — 이 문서** | **2026-03-26** |
| **Symbol 필드** | **✅ 확정 — 이 문서** | **2026-03-26** |
