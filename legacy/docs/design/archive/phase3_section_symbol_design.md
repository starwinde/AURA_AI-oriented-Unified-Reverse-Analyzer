# Phase 3 — Section / Symbol 구조체 필드 설계

> ⚠️ **구버전 문서** — 최신 확정 내용은 [`parser.md`](./parser.md) 를 참조하세요.

> 작성일: 2026-03-26
> 목적: AURA `Section` / `Symbol` 구조체 세부 필드 확정을 위한 참고 문서
> 상태: ✅ 확정 (2026-03-26) — 상세 내용: `phase3_section_symbol_final.md`

---

## 1. 배경

- D-10 결정: FileInfo B안(2레이어) 확정 (2026-03-26)
- `FileInfo` 구조체 내 `Section *sections`, `Symbol *symbols` 포인터가 존재하나
  각 구조체의 세부 필드가 미확정 상태
- 3.2 ELF 파서, 3.3 PE 파서, 3.4 Mach-O 파서 구현 전에 필드 확정 필요

---

## 2. 포맷 스펙 원본 필드

### 2.1 Section 헤더 비교

| 필드 의미 | ELF (`Elf64_Shdr`) | PE (`IMAGE_SECTION_HEADER`) | Mach-O (`section_64`) |
|-----------|-------------------|-----------------------------|-----------------------|
| 이름 | `sh_name` (string table index) | `Name[8]` (직접 문자열) | `sectname[16]` + `segname[16]` |
| 가상 주소 | `sh_addr` | `VirtualAddress` (RVA) | `addr` |
| 파일 오프셋 | `sh_offset` | `PointerToRawData` | `offset` |
| 디스크 크기 | `sh_size` | `SizeOfRawData` | `size` |
| 가상 크기 | `sh_size` (동일) | `VirtualSize` | `size` (동일) |
| 플래그 | `sh_flags` (SHF_ALLOC, SHF_EXECINSTR, SHF_WRITE) | `Characteristics` | `flags` |
| 정렬 | `sh_addralign` | — | `align` |
| 섹션 타입 | `sh_type` (PROGBITS, NOBITS, SYMTAB 등) | — | — |
| 엔트리 크기 | `sh_entsize` | — | `reserved2` |

### 2.2 Symbol 테이블 비교

| 필드 의미 | ELF (`Elf64_Sym`) | PE (COFF `IMAGE_SYMBOL`) | Mach-O (`nlist_64`) |
|-----------|------------------|--------------------------|---------------------|
| 이름 | `st_name` (string table index) | `N` (이름 직접 또는 offset) | `n_strx` (string table index) |
| 주소 / 값 | `st_value` | `Value` | `n_value` |
| 크기 | `st_size` | — | — |
| 타입 | `st_info` 하위 4비트 (STT_FUNC, STT_OBJECT, STT_NOTYPE 등) | `Type` | `n_type` (N_SECT, N_FUN 등) |
| 바인딩 | `st_info` 상위 4비트 (STB_GLOBAL, STB_LOCAL, STB_WEAK) | `StorageClass` | `n_type` (N_EXT 등) |
| 가시성 | `st_other` (STV_DEFAULT, STV_HIDDEN, STV_PROTECTED) | — | — |
| 소속 섹션 | `st_shndx` | `SectionNumber` | `n_sect` |

---

## 3. 주요 도구별 구조체 설계

### 3.1 Section

| 필드 | Ghidra (`MemoryBlock`) | IDA Pro (`segment_t`) | Binary Ninja (`Section`) |
|------|----------------------|----------------------|--------------------------|
| 이름 | `name` (String) | `name` (char*) | `name` (string) |
| 시작 주소 | `start` (Address) | `startEA` (ea_t) | `start` (uint64_t) |
| 끝 주소 | `end` (Address) | `startEA + size` | `start + length` |
| 크기 | `size` (long) | `size` (asize_t) | `length` (uint64_t) |
| 실행 권한 | `execute` (bool) | `SEGPERM_EXEC` | `ReadOnlyCode` (semantics) |
| 쓰기 권한 | `write` (bool) | `SEGPERM_WRITE` | `ReadWriteData` (semantics) |
| 읽기 권한 | `read` (bool) | `SEGPERM_READ` | 기본 포함 |
| 타입 | `type` (DEFAULT, BIT_MAPPED) | `SEG_CODE`, `SEG_DATA` | `type` |
| 파일 오프셋 | 별도 FileBytes 참조 | — | — |

### 3.2 Symbol

| 필드 | Ghidra | IDA Pro | Binary Ninja |
|------|--------|---------|--------------|
| 원본 이름 (mangled) | `name` | `name` | `raw_name` |
| 디맹글 이름 | 별도 Demangler 처리 | `demangle_name()` | `name` (자동 적용) |
| 짧은 이름 | — | — | `short_name` |
| 전체 이름 | — | — | `full_name` |
| 주소 | `address` (Address) | `ea` (ea_t) | `address` (uint64_t) |
| 심볼 종류 | `symbolType` (FUNCTION, LABEL, NAMESPACE, CLASS, EXTERNAL) | `flags` | `type` (FunctionSymbol, DataSymbol, ImportedFunctionSymbol 등) |
| 바인딩 | `source` (ANALYSIS, USER_DEFINED, IMPORTED) | — | `binding` (GlobalBinding, LocalBinding, WeakBinding) |
| 크기 | — | — | — |
| 네임스페이스 | `namespace` | — | `namespace` |

---

## 4. 세 포맷 + 세 도구 교집합 (공통 최소 필드)

### Section 공통 필드

| 필드 | 포함 이유 |
|------|-----------|
| `name` | 모든 포맷·도구 공통 |
| `vaddr` (가상 주소) | 모든 포맷 공통, 디스어셈블·분석의 기준점 |
| `offset` (파일 오프셋) | mmap 기반 직접 접근에 필요 |
| `size` | 모든 포맷·도구 공통 |
| `flags` (실행/쓰기/읽기) | 분석 시 코드/데이터 구분 필수 |

### Symbol 공통 필드

| 필드 | 포함 이유 |
|------|-----------|
| `name` (raw mangled) | 모든 포맷·도구 공통, 원본 보존 필요 |
| `demangled_name` | 가독성, 3.6 태스크에서 `aura_demangle()` 적용 |
| `address` | 모든 포맷·도구 공통, 분석의 기준점 |
| `type` (함수/데이터/임포트/익스포트) | 디스어셈블·CFG 구성에 필요 |
| `binding` (전역/로컬/약) | 링킹·분석 시 필요 |

---

## 5. 확정 구조체 — `phase3_section_symbol_final.md` 참조

2026-03-26 확정. 주요 결정 사항:

| 필드 | 결정 |
|------|------|
| `Section.name` | `char *` + `strdup()` (크기 제한 없음) |
| `Section.file_size` | 포함 (PE `SizeOfRawData` 보존) |
| `Symbol.name` | `char *` + `strdup()` |
| `Symbol.demangled` | `__cxa_demangle` 반환값 직접 소유, NULL 허용 |
| `Symbol.size` | 포함 (PE/Mach-O는 0) |

상세 구조체 코드 및 소유권 규칙 → `docs/design/phase3_section_symbol_final.md`

---

## 6. 미결 항목

| 항목 | 상태 |
|------|------|
| `Section.name` 저장 방식 | ✅ 확정 — `char *` + strdup |
| `Symbol.name` / `demangled` 저장 방식 | ✅ 확정 — 동적 포인터 |
| `Symbol.size` 포함 여부 | ✅ 확정 — 포함 |
| `Section.file_size` 포함 여부 | ✅ 확정 — 포함 |

---

## 7. 관련 결정 사항

| 항목 | 결정 | 일자 |
|------|------|------|
| 파일 I/O 방식 | mmap 확정 (D-6) | 2026-03-26 |
| FileInfo 구조체 | B안 2레이어 확정 (D-10) | 2026-03-26 |
| C++ demangle 방식 | A안 `__cxa_demangle` 채택, PRD §4.2 등재 | 2026-03-26 |
| **Section/Symbol 필드** | **🔴 미확정 — 이 문서 검토 후 결정** | — |
