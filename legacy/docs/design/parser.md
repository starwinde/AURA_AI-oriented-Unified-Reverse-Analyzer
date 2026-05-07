# AURA Phase 3 — 파서 모듈 설계 (통합 기준 문서)

> 작성일: 2026-03-26
> 상태: ✅ 확정 (2026-03-26)
> 목적: Phase 3 전체 파서 모듈의 구조체, 소유권, 생성/해제 함수, 포맷별 매핑의 단일 기준
>
> ⚠️ 하위 문서들은 구버전입니다. 이 문서가 유일한 기준입니다.
> 구버전 문서는 `docs/design/archive/` 로 이동됨 (2026-03-26):
> - `archive/phase3_fileinfo_design.md`
> - `archive/phase3_section_symbol_design.md`
> - `archive/phase3_section_symbol_fields.md`
> - `archive/phase3_section_symbol_final.md`

---

## 1. 확정 결정 목록

| 결정 | 내용 | 일자 |
|------|------|------|
| D-6 파일 I/O 방식 | mmap 확정 | 2026-03-26 |
| D-10 FileInfo 구조체 | B안 2레이어 (`MappedFile` + `FileInfo`) | 2026-03-26 |
| FileInfo.map 중복 보유 | hot path 복사 제거, 인라인 접근 함수로 통일 | 2026-03-26 |
| MappedFile.path | `char *` + `strdup()` (고정 버퍼 제거) | 2026-03-26 |
| FileInfo 힙 정렬 | `aligned_alloc(64, ...)` 생성 함수 강제 | 2026-03-26 |
| 이중 해제 방지 | `file_info_create(MappedFile **)` + NULL 무효화 | 2026-03-26 |
| Section.name | `char *` + `strdup()` | 2026-03-26 |
| Section.file_size | 포함 (PE SizeOfRawData 보존) | 2026-03-26 |
| Section.data | mmap 내부 포인터 (`file->map + offset`), 읽기 전용 | 2026-03-26 |
| Symbol.name | `char *` + `strdup()` | 2026-03-26 |
| Symbol.demangled | `__cxa_demangle` 반환값 직접 소유, NULL 허용 | 2026-03-26 |
| Symbol.size | 포함 (PE/Mach-O는 0) | 2026-03-26 |
| demangled 실패 처리 | NULL 저장, 사용 측에서 `symbol_display_name()` 폴백 | 2026-03-26 |
| C++ demangle 방식 | `__cxa_demangle` (cxxabi.h), PRD §4.2 등재 | 2026-03-26 |
| Mach-O 섹션 이름 형식 | `segname + "." + sectname` (예: `__TEXT.__text`) | 2026-03-26 |

---

## 2. 전체 구조체 정의

### 2.1 MappedFile — 레이어 1 (파일 I/O 전담)

```c
typedef struct {
    int            fd;      /* open() 반환 파일 디스크립터                  */
    const uint8_t *map;     /* mmap() 반환 주소 (읽기 전용)                 */
    size_t         size;    /* 파일 전체 크기                               */
    char          *path;    /* strdup() 복사본, MappedFile 소유             */
                            /* mapped_file_destroy() 에서 free()           */
} MappedFile;
```

### 2.2 FileInfo — 레이어 2 (포맷 파싱 결과)

```c
typedef struct {
    MappedFile    *file;            /* 소유권 보유, destroy 시 함께 해제    */
    AuraFormat     format;          /* AURA_FORMAT_ELF / PE / MACHO / RAW  */
    AuraArch       arch;            /* AURA_ARCH_X86_64 / ARM64 등          */
    uint64_t       entry_point;     /* 진입점 가상 주소                     */
    Section       *sections;        /* heap 배열, FileInfo 소유             */
    uint32_t       section_count;
    Symbol        *symbols;         /* heap 배열, FileInfo 소유             */
    uint32_t       symbol_count;
} __attribute__((aligned(64))) FileInfo;
/* 힙 할당 시 반드시: aligned_alloc(64, sizeof(FileInfo))                 */
```

**map 접근 — 인라인 함수 (단일 경로 강제, stale 포인터 방지):**
```c
static inline const uint8_t *fileinfo_map(const FileInfo *fi) {
    return fi->file->map;
}
static inline size_t fileinfo_map_size(const FileInfo *fi) {
    return fi->file->size;
}
```

### 2.3 Section

```c
#define AURA_SEC_READ   0x01u
#define AURA_SEC_WRITE  0x02u
#define AURA_SEC_EXEC   0x04u

typedef struct {
    char           *name;       /* strdup() 복사본, Section 소유            */
                                /* section_destroy() 에서 free()            */
    uint64_t        vaddr;      /* 가상 주소 (절대 주소, PE RVA 변환 후)    */
    uint64_t        offset;     /* 파일 오프셋                              */
    uint64_t        size;       /* 메모리 기준 크기 (VirtualSize)           */
    uint64_t        file_size;  /* 파일 기준 크기 (PE: SizeOfRawData)       */
                                /* ELF/Mach-O: size 와 동일값              */
    const uint8_t  *data;       /* mmap 내부 포인터 (file->map + offset)   */
                                /* 읽기 전용, MappedFile 수명 동안 유효    */
    uint32_t        flags;      /* AURA_SEC_READ | WRITE | EXEC            */
} Section;
/* sizeof(Section) ≈ 56바이트 (포인터 2 + uint64 4 + uint32 1 + 패딩)    */
```

### 2.4 Symbol

```c
typedef enum {
    AURA_SYM_UNKNOWN  = 0,
    AURA_SYM_FUNCTION = 1,   /* ELF STT_FUNC, PE FUNCTION                 */
    AURA_SYM_OBJECT   = 2,   /* ELF STT_OBJECT, 데이터 변수               */
    AURA_SYM_IMPORT   = 3,   /* 외부 임포트 심볼                           */
    AURA_SYM_EXPORT   = 4,   /* 익스포트 심볼                              */
} AuraSymType;

typedef enum {
    AURA_BIND_LOCAL  = 0,    /* ELF STB_LOCAL                              */
    AURA_BIND_GLOBAL = 1,    /* ELF STB_GLOBAL                             */
    AURA_BIND_WEAK   = 2,    /* ELF STB_WEAK                               */
} AuraSymBinding;

typedef struct {
    char           *name;       /* strdup() 복사본, Symbol 소유            */
                                /* symbol_destroy() 에서 free()            */
    char           *demangled;  /* __cxa_demangle 반환값, Symbol 소유      */
                                /* NULL 허용 — C 함수 또는 demangle 실패  */
    uint64_t        address;    /* 절대 주소 (PE: RVA + ImageBase)         */
    uint64_t        size;       /* 심볼 크기 (ELF st_size, PE/Mach-O: 0)  */
    AuraSymType     type;
    AuraSymBinding  binding;
} Symbol;
/* sizeof(Symbol) = 8+8+8+8+4+4 = 40바이트                               */
```

---

## 3. 생성 / 해제 함수

```c
/* ── MappedFile ── */

MappedFile *mapped_file_open(const char *path);
/* - open() + mmap() 수행
   - path: strdup() 복사 소유
   - 실패 시 NULL 반환, 부분 할당 자동 정리 */

void mapped_file_destroy(MappedFile *mf);
/* - munmap() + close() + free(path) + free(mf)
   - mf == NULL 이면 즉시 반환 (안전) */


/* ── FileInfo ── */

FileInfo *file_info_create(MappedFile **mf_ptr);
/* - aligned_alloc(64, sizeof(FileInfo)) 로 64바이트 정렬 보장
   - *mf_ptr 를 fi->file 에 이전 후 *mf_ptr = NULL (이중 해제 방지)
   - 실패 시 NULL 반환, *mf_ptr 변경 없음 */

void file_info_destroy(FileInfo *fi);
/* 해제 순서:
   1. symbol_destroy() × symbol_count
   2. free(symbols)
   3. section_destroy() × section_count
   4. free(sections)
   5. mapped_file_destroy(file)
   6. free(fi)                          ← aligned_alloc은 free()로 해제 가능 */


/* ── Section / Symbol ── */

void section_destroy(Section *sec);
/* - free(sec->name)
   - sec->data 는 mmap 포인터이므로 free() 하지 않음 */

void symbol_destroy(Symbol *sym);
/* - free(sym->name)
   - if (sym->demangled) free(sym->demangled) */


/* ── 편의 함수 ── */

static inline const char *symbol_display_name(const Symbol *s) {
    return s->demangled ? s->demangled : s->name;
}
/* demangled NULL 폴백 — 출력, LLM 전달 시 사용 */
```

---

## 4. 소유권 전체 흐름

```
mapped_file_open("/bin/ls")
    └─ MappedFile { fd, map, size, path=strdup("/bin/ls") }
           ↓
file_info_create(&mf)          ← mf = NULL 로 무효화
    └─ aligned_alloc(64, ...)
         └─ FileInfo { file=mf, ... }
                ↓
파서 (elf_parser / pe_parser / macho_parser)
    ├─ Section { name=strdup(...), data=fileinfo_map(fi)+offset, ... }
    └─ Symbol  { name=strdup(...), demangled=__cxa_demangle(...) or NULL }
                ↓
file_info_destroy(fi)
    ├─ symbol_destroy() × N     free(name), free(demangled)
    ├─ free(symbols)
    ├─ section_destroy() × N    free(name)  [data는 free 안 함]
    ├─ free(sections)
    └─ mapped_file_destroy()    munmap + close + free(path)
```

---

## 5. 포맷별 필드 매핑

### Section

| AURA 필드 | ELF | PE | Mach-O |
|-----------|-----|----|--------|
| `name` | string table strdup | `Name[8]` strdup | `segname + "." + sectname` strdup (예: `__TEXT.__text`) |
| `vaddr` | `sh_addr` | `VirtualAddress + ImageBase` | `addr` |
| `offset` | `sh_offset` | `PointerToRawData` | `offset` |
| `size` | `sh_size` | `VirtualSize` | `size` |
| `file_size` | `sh_size` (동일) | `SizeOfRawData` | `size` (동일) |
| `data` | `map + sh_offset` | `map + PointerToRawData` | `map + offset` |
| `flags` | `SHF_EXECINSTR`→EXEC, `SHF_WRITE`→WRITE, `SHF_ALLOC`→READ | `IMAGE_SCN_MEM_*` 변환 | `S_ATTR_PURE_INSTRUCTIONS`→EXEC 등 |

### Symbol

| AURA 필드 | ELF | PE | Mach-O |
|-----------|-----|----|--------|
| `name` | string table strdup | COFF string table strdup | string table strdup |
| `demangled` | `__cxa_demangle(name)`, NULL 가능 | `__cxa_demangle(name)`, MSVC `?` prefix 미지원 → NULL | `__cxa_demangle(name)`, NULL 가능 |
| `address` | `st_value` | `Value + ImageBase` | `n_value` |
| `size` | `st_size` | 0 | 0 |
| `type` | `STT_FUNC`→FUNCTION, `STT_OBJECT`→OBJECT | StorageClass 변환 | `N_FUN`→FUNCTION 등 |
| `binding` | `STB_GLOBAL`→GLOBAL, `STB_LOCAL`→LOCAL, `STB_WEAK`→WEAK | `IMAGE_SYM_CLASS_EXTERNAL`→GLOBAL 등 | `N_EXT` 여부 |

---

## 6. 리스크 및 대응

| 리스크 | 발생 시점 | 대응 |
|--------|----------|------|
| `free()` 누락 메모리 누수 | 3.2~3.4 파서 구현 | ASAN + valgrind 의무화 |
| `demangled NULL` 미처리 크래시 | 3.5 `--info` 출력 | `symbol_display_name()` 통일 사용 |
| `strdup()` 실패 (OOM) | 대형 바이너리 | NULL 체크 필수, `AURA_ERR_OOM` 전파 |
| PE MSVC `?` prefix demangle 실패 | 3.3 PE 파서 | `demangled = NULL` 처리, Phase 3 허용 |
| `Section.data` — mmap 해제 후 접근 | FileInfo destroy 순서 오류 | destroy 순서 엄수 (Section → MappedFile) |
| `aligned_alloc` 미사용 직접 malloc | 3.1 구현 시 실수 | `file_info_create()` 만 사용, 직접 할당 금지 |

---

## 7. 산출물 — 구현 대상 파일

| 파일 | 역할 |
|------|------|
| `include/mapped_file.h` | `MappedFile` 구조체 + API 선언 |
| `include/file_format.h` | `FileInfo`, `Section`, `Symbol`, 열거형, 인라인 함수 선언 |
| `src/parser/format_detector.c` | magic bytes 기반 포맷 자동 감지 |
| `src/parser/elf_parser.c` | ELF32/64 파서 |
| `src/parser/pe_parser.c` | PE32/PE32+ 파서 |
| `src/parser/macho_parser.c` | Mach-O 32/64 + Fat Binary 파서 |
| `src/core/demangle.c` | `__cxa_demangle` 래퍼 (3.6) |
