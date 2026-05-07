# Phase 3 — FileInfo 구조체 설계 비교

> ⚠️ **구버전 문서** — 최신 확정 내용은 [`parser.md`](./parser.md) 를 참조하세요.

> 작성일: 2026-03-26
> 최종 갱신: 2026-03-26
> 목적: mmap 기반 FileInfo 구조체 설계 방향 결정을 위한 참고 문서
> **결정: D-10 — B안 (2레이어 분리) 확정 (2026-03-26)**

---

## 1. 배경

- D-6 결정: 파일 I/O 방식 **mmap 확정** (2026-03-26)
- Ghidra, IDA Pro, Binary Ninja 세 도구 모두 mmap 방식 채택
- Phase 3.1 설계 시 `FileInfo` 구조체를 확정해야 3.2~3.6 전체 구현이 가능

---

## 2. 세 도구의 구조체 설계 방식

### 2.1 Ghidra (Java, 오픈소스)

**3단계 레이어 구조**

```
ByteProvider (인터페이스)          ← mmap 추상화 레이어
    └─ MappedByteProvider         ← 실제 mmap 구현체
         ├─ path
         ├─ FileChannel
         └─ MappedByteBuffer      ← Java의 mmap

FileBytes                         ← mmap 바이트 참조
    ├─ provider (ByteProvider)
    ├─ offset
    └─ size

Program (최상위 컨테이너)
    ├─ FileBytes
    ├─ Memory (섹션 매핑)
    └─ SymbolTable
```

- mmap과 파싱 결과를 레이어로 완전 분리
- Java GC가 메모리 관리 담당 (수동 해제 없음)
- 인터페이스 기반 다형성으로 포맷 확장

---

### 2.2 IDA Pro (C++, 클로즈드소스 — SDK 헤더 기반 추정)

**2단계 불투명 핸들 구조**

```
linput_t (불투명 핸들)             ← 파일 접근 추상화
    ├─ qlseek()                   ← 함수 포인터로만 접근
    ├─ qlread()                   ← 내부 구조 비공개
    └─ qlsize()

loader_input_t                    ← 로더 레이어
    ├─ linput_t *li
    ├─ format_name
    └─ file_type
```

- 내부 구현을 함수 포인터로 완전히 은닉
- 사용자(플러그인)는 구조체 직접 접근 불가
- 불투명 핸들 패턴으로 하위 호환성 보장

---

### 2.3 Binary Ninja (C++, 공개 API)

**3단계 분리 구조**

```
FileMetadata                      ← 파일 메타 (경로, 저장 상태)
    ├─ filename
    └─ modified

FileAccessor                      ← mmap 핸들
    ├─ fd
    ├─ mmap_ptr
    └─ size

BinaryView                        ← 포맷별 뷰 (ELF/PE/Mach-O)
    ├─ FileMetadata*
    ├─ FileAccessor*
    ├─ sections[]
    ├─ segments[]
    └─ symbols[]
```

- mmap 관리, 파일 메타, 포맷 파싱을 각각 독립 클래스로 분리
- RAII로 메모리 소유권 명확히 관리
- BinaryView 파생 클래스로 포맷별 확장

---

## 3. 세 도구 비교표

| 항목 | Ghidra | IDA Pro | Binary Ninja |
|------|--------|---------|--------------|
| **레이어 수** | 3단계 | 2단계 | 3단계 |
| **mmap 위치** | 최하위 레이어 독립 | 불투명 핸들 내부 | 최하위 레이어 독립 |
| **포맷 파싱 위치** | Program 레이어 | loader_input_t 레이어 | BinaryView 레이어 |
| **접근 방식** | 인터페이스 (다형성) | 함수 포인터 (불투명) | 클래스 상속 |
| **소유권 관리** | GC (Java) | 수동 (C++) | RAII (C++) |
| **언어** | Java | C++ | C++ |

---

## 4. AURA(C언어) 적용 가능 선택지

### A안 — 단일 구조체 (단순)

```c
typedef struct {
    int            fd;
    const uint8_t *map;       /* mmap 반환 주소 */
    size_t         map_size;
    char           path[512];
    AuraFormat     format;    /* ELF/PE/Mach-O/Unknown */
    AuraArch       arch;
    /* 파싱 결과 */
    Section        sections[MAX_SECTIONS];
    uint32_t       section_count;
} FileInfo;
```

| 항목 | 내용 |
|------|------|
| 장점 | 구현 단순, 포인터 추적 불필요, 함수 인자 1개 |
| 단점 | 구조체 비대화, mmap 관리와 파싱 결과 혼재 |
| 참고 도구 | 없음 (세 도구 모두 이 방식 미사용) |

---

### B안 — 2레이어 분리 (권고)

**Binary Ninja 방식을 C로 적용**

```c
/* 레이어 1: mmap 핸들 (파일 I/O 전담) */
typedef struct {
    int            fd;
    const uint8_t *map;
    size_t         size;
    char           path[512];
} MappedFile;

/* 레이어 2: 포맷 파싱 결과 */
typedef struct {
    MappedFile    *file;      /* mmap 핸들 참조 */
    AuraFormat     format;    /* ELF / PE / Mach-O / Raw */
    AuraArch       arch;
    uint64_t       entry_point;
    Section       *sections;
    uint32_t       section_count;
    Symbol        *symbols;
    uint32_t       symbol_count;
} FileInfo;
```

| 항목 | 내용 |
|------|------|
| 장점 | mmap 생명주기와 파싱 결과 분리, 단위 테스트 용이, 확장 쉬움 |
| 단점 | 포인터 2개 관리, 소유권 규칙 명시 필요 |
| 참고 도구 | Binary Ninja (FileAccessor + BinaryView 구조) |

---

### C안 — 함수 테이블 (IDA 방식을 C로 적용)

```c
/* 포맷별 구현체가 함수 테이블을 채움 */
typedef struct FileFormatOps {
    const char *name;
    int  (*detect) (const uint8_t *buf, size_t size);
    int  (*parse)  (MappedFile *f, FileInfo *out);
    void (*destroy)(FileInfo *info);
} FileFormatOps;

/* 전역 등록 테이블 */
extern const FileFormatOps *g_formats[];
```

| 항목 | 내용 |
|------|------|
| 장점 | 포맷별 구현 완전 분리, 런타임 포맷 추가 가능, 플러그인 확장 용이 |
| 단점 | 함수 포인터로 디버깅 난이도 상승, 구현 복잡도 높음 |
| 참고 도구 | IDA Pro (loader 플러그인 구조) |

---

## 5. 권고 — B안 채택

세 선택지 중 **B안(2레이어 분리)**이 AURA C 구현에 가장 적합하다.

**이유:**

1. **세 도구 중 가장 현대적인 Binary Ninja 방식**을 C로 직역한 형태
2. mmap 생명주기(`MappedFile`)와 파싱 결과(`FileInfo`) 명확히 분리
   - `MappedFile`: `open() → mmap() → munmap() → close()` 담당
   - `FileInfo`: 파싱된 섹션, 심볼, 진입점 등 담당
3. 함수 포인터 없이 단순 구조체로 구현 가능 (C 친화적)
4. Phase 4 이후 분석 결과(`CFG`, `DFG`)를 `FileInfo`에 추가할 때 확장 용이
5. 단위 테스트 시 `MappedFile` mock 가능

**소유권 규칙 (명시 필요):**
```
MappedFile 생성 → FileInfo 생성 시 소유권 이전
FileInfo 해제   → 내부에서 MappedFile도 함께 해제
```

---

## 6. 결정 사항

| 항목 | 시점 | 상태 |
|------|------|------|
| A/B/C안 최종 선택 | 2026-03-26 | ✅ **B안 확정** |
| `Section`, `Symbol` 구조체 세부 필드 | Phase 3.1 설계 중 | 🔴 미결 |
| D-7 캐시 구조 | Phase 3.2 완료 후 | 🔴 미결 |

---

## 7. 확정된 구조체 설계 (B안 — 2026-03-26 문제 분석 반영)

### 7.1 문제 분석 및 해결 이력 (2026-03-26)

| 우선순위 | 문제 | 해결 방안 | 핵심 원칙 |
|---------|------|-----------|----------|
| 🔴 | `FileInfo.map` 중복 보유 → stale 포인터 | hot path 복사 제거, 인라인 접근 함수로 통일 | 단일 소유 |
| 🔴 | `aligned(64)` 힙 할당 시 정렬 미보장 | `aligned_alloc(64, ...)` 생성 함수에서 강제 | C11 표준 |
| 🟠 | `MappedFile.path[512]` 고정 버퍼 | `char *path` + `strdup()` 소유 | 가변 길이 |
| 🟠 | `MappedFile` 이중 해제 위험 | `file_info_create(MappedFile **)` + NULL 무효화 | 소유권 이전 강제 |

---

### 7.2 확정 구조체

```c
/* ── 레이어 1: mmap 핸들 (파일 I/O 전담) ── */
typedef struct {
    int            fd;
    const uint8_t *map;    /* mmap() 반환 주소                           */
    size_t         size;   /* 파일 전체 크기                              */
    char          *path;   /* strdup() 복사본, MappedFile 소유            */
                           /* mapped_file_destroy() 에서 free()          */
} MappedFile;

/* ── 레이어 2: 포맷 파싱 결과 ── */
typedef struct {
    MappedFile    *file;            /* 소유권 보유, destroy 시 함께 해제   */
    AuraFormat     format;          /* ELF / PE / Mach-O / Raw            */
    AuraArch       arch;
    uint64_t       entry_point;
    Section       *sections;
    uint32_t       section_count;
    Symbol        *symbols;
    uint32_t       symbol_count;
} __attribute__((aligned(64))) FileInfo;
/* 힙 할당 시 반드시: aligned_alloc(64, sizeof(FileInfo))                */
```

---

### 7.3 map 접근 — 인라인 함수 (단일 경로 강제)

```c
/* map 복사본 제거 — file->map 을 단일 경로로만 접근                      */
static inline const uint8_t *fileinfo_map(const FileInfo *fi) {
    return fi->file->map;
}
static inline size_t fileinfo_map_size(const FileInfo *fi) {
    return fi->file->size;
}
```

`fi->file` 은 구조체 앞에 위치 → 역참조 1회로 캐시 라인 내 접근 가능.

---

### 7.4 생성 / 해제 함수

```c
/* file_info_create: 소유권 이전 + NULL 무효화로 이중 해제 방지            */
FileInfo *file_info_create(MappedFile **mf_ptr) {
    if (!mf_ptr || !*mf_ptr) return NULL;
    FileInfo *fi = aligned_alloc(64, sizeof(FileInfo));
    if (!fi) return NULL;
    memset(fi, 0, sizeof(FileInfo));
    fi->file = *mf_ptr;
    *mf_ptr  = NULL;    /* 호출자 포인터 무효화 → 이중 해제 불가           */
    return fi;
}

/* mapped_file_open: strdup으로 path 소유                                 */
MappedFile *mapped_file_open(const char *path) {
    MappedFile *mf = calloc(1, sizeof(MappedFile));
    if (!mf) return NULL;
    mf->path = strdup(path);
    if (!mf->path) { free(mf); return NULL; }
    /* fd, mmap 처리 ... */
    return mf;
}

/* mapped_file_destroy: munmap + close + free(path)                       */
void mapped_file_destroy(MappedFile *mf) {
    if (!mf) return;
    if (mf->map && mf->size) munmap((void *)mf->map, mf->size);
    if (mf->fd >= 0) close(mf->fd);
    free(mf->path);
    free(mf);
}

/* file_info_destroy: Section/Symbol → MappedFile 순서로 해제             */
void file_info_destroy(FileInfo *fi) {
    if (!fi) return;
    for (uint32_t i = 0; i < fi->symbol_count; i++)
        symbol_destroy(&fi->symbols[i]);
    free(fi->symbols);
    for (uint32_t i = 0; i < fi->section_count; i++)
        section_destroy(&fi->sections[i]);
    free(fi->sections);
    mapped_file_destroy(fi->file);
    free(fi);   /* aligned_alloc은 free()로 해제 가능 (C11 보장)          */
}
```

---

### 7.5 호출 흐름

```c
/* 정상 사용 패턴 */
MappedFile *mf = mapped_file_open("/bin/ls");
FileInfo   *fi = file_info_create(&mf);
/* 이후 mf == NULL → 실수로 mapped_file_destroy(mf) 호출해도 무해        */

const uint8_t *data = fileinfo_map(fi);   /* 단일 경로 접근               */
size_t         sz   = fileinfo_map_size(fi);

file_info_destroy(fi);  /* MappedFile 포함 전체 해제                      */
```

---

### 7.6 선택 근거 (원본 유지)

- 종합 안정도 점수: B안 82점 (A안 73점, SoA 50점, C안 65점)
- 캐시 라인 최적화: hot path 복사 제거 → `fi->file` 단일 역참조로 대체 (stale 포인터 위험 제거)
- 정렬 보장: `aligned_alloc(64, ...)` 생성 함수 강제로 `__attribute__((aligned(64)))` 실효성 확보
