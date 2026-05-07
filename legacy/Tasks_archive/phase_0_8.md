# Tasks Archive — Phase 0~8 (v1.0 baseline)

> **Status**: frozen. 본 파일은 `Tasks.md` 에서 분리된 종결 릴리스 스냅샷이다. rules.md §11.5 (archival 규정) 에 따라 상태 전환 금지.
> **Archived**: 2026-04-20 Session #9.
> **Parent canonical**: [Tasks.md](../Tasks.md)

---

## Phase 0: 프로젝트 설정

### 0.1 프로젝트 디렉토리 구조 생성 `[x]`

**완료 기준:**
- `src/core/`, `src/disasm/`, `src/decompiler/`, `src/parser/`, `src/llm/`, `src/gui/` 디렉토리
- `include/`, `tests/`, `third_party/`, `docs/` 디렉토리
- 각 디렉토리에 `.gitkeep` 또는 기본 헤더

**산출물:** 디렉토리 트리

---

### 0.2 개발 도구 및 라이브러리 설치 확인 `[x]`

**완료 기준:**
- `gcc --version` / `clang --version` (C11/C++17 지원)
- `cmake --version` (≥ 3.16)
- Capstone 라이브러리 확인
- 확인 결과를 `docs/env_check.md`에 기록

**산출물:** `docs/env_check.md`

---

### 0.3 Git 저장소 초기화 및 기본 커밋 `[x]`

**완료 기준:**
- `git init`, `.gitignore` (C/C++ 빌드 산출물, IDE 파일)
- `README.md` 기본 작성
- 초기 커밋: `chore: initialize AURA project structure`

**산출물:** `.gitignore`, `README.md`

---

### 0.T Phase 0 종합 테스트 `[x]`

**완료 기준:**
- 표준 디렉토리 구조 존재
- `.gitignore` 정상 동작
- GitHub 원격 저장소 push 완료

---

## Phase 1: 기본 인프라 + 플러그인 시스템

### 1.1 C 언어 프로젝트 설계 `[x]`

**완료 기준:**
- `src/core/aura.h` — 공통 타입, 에러 코드
- `src/core/aura.c` — 진입점, 초기화 골격
- 컴파일 가능

**산출물:** `src/core/aura.{c,h}`

---

### 1.2 CMake 빌드 시스템 구성 `[x]`

**완료 기준:**
- `cmake -B build && make -C build` 전체 빌드 성공
- `ctest --test-dir build` 실행 가능
- `make clean`, `make install`, `make package` 지원

**산출물:** `CMakeLists.txt`

---

### 1.3 버전 관리 체계 `[x]`

**완료 기준:**
- `include/aura_version.h` — `AURA_VERSION_MAJOR/MINOR/PATCH`
- `aura --version` → `AURA v1.0.0`
- git tag 생성

**산출물:** `include/aura_version.h`

---

### 1.4 CI/CD 파이프라인 `[x]`

**완료 기준:**
- `.github/workflows/build.yml` — Linux 자동 빌드
- 빌드 실패 시 GitHub Actions에서 실패 표시
- README 빌드 상태 배지

**산출물:** `.github/workflows/build.yml`

---

### 1.5 플러그인 시스템 설계 `[x]`

**완료 기준:**
- `include/aura_plugin.h` — C API 플러그인 인터페이스
- 플러그인 생명주기 (`dlopen` → `init` → `destroy` → `dlclose`)
- `docs/plugin_api.md` 작성

**산출물:** `include/aura_plugin.h`, `docs/plugin_api.md`

---

### 1.6 플러그인 시스템 구현 `[x]`

**의존성:** 1.5
**완료 기준:**
- `src/core/plugin_loader.c` — `dlopen`/`dlsym` 기반 로더
- PluginManager API
- 예제 플러그인 (`plugins/example/`)

**산출물:** `src/core/plugin_loader.c`, `plugins/example/`

---

### 1.7 Python 스크립트 인터페이스 `[REMOVED 2026-04-17]`

> **REMOVED 2026-04-17 (V1.1.x-R R-6)** — PRD §4.1 ("C/C++ only, no interpreter
> languages") 과 §8 line 203 ("Python/스크립트 플러그인 인터페이스 = Out of
> Scope") 재확인에 따라 완전 삭제. `src/core/aura_python.c`,
> `include/aura_python.h`, `tests/python/test_python.c`, GUI Script Manager
> action, CMake `AURA_BUILD_PYTHON` 옵션 모두 제거. 상세는
> `tests/results/V1.1.x-R_R-6.md` 참조.

**의존성:** 1.6 (N/A — 제거됨)
**산출물:** 없음 (제거됨)

---

### 1.8 CLI 헤드리스 모드 `[x]`

**완료 기준:**
- `src/core/headless.c` — `aura --headless <file>` 전체 분석 파이프라인
- JSON 또는 Markdown 출력

**산출물:** `src/core/headless.c`

---

### 1.T Phase 1 종합 테스트 `[x]`

**완료 기준:**
- 빌드 + 버전 출력 + CI + 플러그인 로드 + 헤드리스 모드 전체 검증
- `docs/env_check.md` 최신화

---

## Phase 2: 디스어셈블러 + Xref + 재귀 디스어셈블

### 2.1 디스어셈블러 모듈 설계 `[x]`

**완료 기준:**
- `include/disasm.h` — 공개 API
- `DisasmContext`, `DisasmResult` 구조체 정의

**산출물:** `include/disasm.h`

---

### 2.2 Capstone 연동 및 기본 테스트 `[x]`

**의존성:** 2.1
**완료 기준:**
- `third_party/capstone/` 정적 링크
- `disasm_init()`, `disasm_run()`, `disasm_destroy()` 구현
- x86_64 기본 명령어 디스어셈블 확인

**산출물:** `src/disasm/capstone_wrapper.c`

---

### 2.3 바이너리 파일 로더 `[x]`

**의존성:** 2.2
**완료 기준:**
- `include/mapped_file.h` — mmap 기반 파일 로더
- 대형 파일 (≥ 500MB) lazy load 지원

**산출물:** `src/parser/mapped_file.c`

---

### 2.4 메모리 매핑 + 섹션 분석 `[x]`

**의존성:** 2.3
**완료 기준:**
- `FileInfo` 구조체 (MappedFile + 파싱 결과 2레이어 분리)
- 섹션 목록 추출

**산출물:** `src/parser/file_info.c`

---

### 2.5 디스어셈블러 UI 통합 `[x]`

**의존성:** 2.4, 8.10
**완료 기준:**
- GUI 디스어셈블리 뷰에서 .text 섹션 디스어셈블 결과 렌더링
- 주소/바이트/니모닉/오퍼랜드 컬럼

---

### 2.6 x86/x86_64 정확도 검증 `[x]`

**의존성:** 2.2
**완료 기준:**
- 기본 명령어 ≥ 99% 정확도 (Capstone 보증)
- 단위 테스트 `tests/disasm/test_disasm.c`

**산출물:** `tests/disasm/test_disasm.c`

---

### 2.7 ARM 아키텍처 지원 `[x]`

**의존성:** 2.2
**완료 기준:**
- x86, x86_64, ARM, ARM64 디스어셈블 지원
- 아키텍처별 테스트

**산출물:** `tests/disasm/test_arm.c`

---

### 2.8 Xref 백엔드 `[x]`

**의존성:** 2.7
**완료 기준:**
- `src/core/xref.c` — 코드/데이터 크로스레퍼런스 그래프
- `include/xref.h` 공개 API
- call/jmp/lea/mov 참조 자동 수집
- `--xref <address>` CLI

**산출물:** `src/core/xref.c`, `include/xref.h`

---

### 2.9 문자열 참조 분석 `[x]`

**의존성:** 2.8
**완료 기준:**
- .rodata/.data 문자열 자동 탐지
- 각 문자열의 코드 참조 목록
- `--strings` CLI

**산출물:** `src/core/string_refs.c`

---

### 2.10 데이터 참조 분석 `[x]`

**의존성:** 2.8
**완료 기준:**
- 전역/정적 변수 참조 추적
- 데이터 섹션 ↔ 코드 양방향 매핑

**산출물:** `src/core/data_refs.c`

---

### 2.11 기본 재귀 디스어셈블 `[x]`

**의존성:** 2.8
**완료 기준:**
- Call-driven 재귀 하강 디스어셈블
- Work queue + visited set

**산출물:** `src/core/recursive_disasm.c`

---

### 2.12 Full 재귀 디스어셈블 (점프 테이블 포함) `[x]`

**의존성:** 2.11
**완료 기준:**
- 조건 분기, 점프 테이블 탐색 포함
- `--recursive` CLI 플래그
- 함수 탐지율 향상

**산출물:** `src/core/recursive_disasm.c` 확장

---

### 2.13 간접 호출/점프 해석 `[x]`

**의존성:** 2.12
**완료 기준:**
- 함수 포인터, vtable, 점프 테이블 패턴 인식
- 간접 타겟을 Xref 그래프에 추가
- C++ vtable 기본 패턴

**산출물:** `src/disasm/indirect_resolver.c`

---

### 2.14 Non-returning 함수 탐지 `[x]`

**의존성:** 2.12
**완료 기준:**
- exit(), abort(), __cxa_throw, __stack_chk_fail 패턴
- 35개 빌트인 non-returning DB
- CFG에서 호출 후 블록 종료 처리

**산출물:** `src/core/noreturn_detect.c`

> **Ghidra parity note (2026-04-09)**: 본 태스크는 Ghidra `Non-Returning Functions – Known` analyzer 의미론(builtin DB + 심볼명 매칭)만 구현. `Non-Returning Functions – Discovered` (CFG 추론 기반 발견)는 미구현 — 현재 `noreturn_detect.c` (400 LOC) 에 Discovered 분기 없음. v1.0.1 P.17 Wiring Contracts 단계에서 Registry 등록 시 `noreturn_known` short_id 1개로 등록하고, `noreturn_discovered`는 v1.1+ 별도 태스크로 분리 예정. 본 격차로 인해 현재 parity는 `Known: ✅ / Discovered: ❌`.

---

### 2.15 인라인 함수 탐지 `[x]`

**의존성:** 4.8 (FLIRT)
**완료 기준:**
- Sliding window mnemonic hash 기반 패턴 매칭
- FLIRT 시그니처 DB 활용

**산출물:** `src/core/inline_detect.c`

---

### 2.16 호출 규약 자동 탐지 `[x]`

**의존성:** 2.12
**완료 기준:**
- cdecl/stdcall/fastcall/SysV/MS x64/ARM EABI/AArch64 자동 판별
- 레지스터 사용 + 스택 정리 패턴 분석

**산출물:** `src/decompiler/calling_conv.c`

---

### 2.T Phase 2 종합 테스트 `[x]`

**의존성:** 2.16
**완료 기준:**
- 전체 디스어셈블러 + Xref + 재귀 통합 테스트
- `make test` 전체 PASS
- 함수 탐지율 벤치마크 (stripped 바이너리)

**산출물:** `tests/results/2.T_disasm.txt`

---

## Phase 3: 파일 포맷 파서 + 디버그 정보

### 3.1 파일 포맷 분석기 설계 `[x]`

**완료 기준:**
- `include/file_format.h` — 공통 API
- Magic bytes 기반 포맷 자동 감지

**산출물:** `include/file_format.h`, `src/parser/format_detector.c`

---

### 3.2 ELF 파서 (커스텀 구현) `[x]`

**의존성:** 3.1
**완료 기준:**
- libelf 미사용, 직접 구현
- 헤더, 섹션, 심볼, relocation 파싱
- 32/64비트, little/big endian 지원

**산출물:** `src/parser/elf_parser.c`

---

### 3.3 PE 파서 (커스텀 구현) `[x]`

**의존성:** 3.1
**완료 기준:**
- DOS 헤더, PE 헤더, 섹션, Import Table 파싱
- PE32/PE32+ 지원

**산출물:** `src/parser/pe_parser.c`

---

### 3.4 Mach-O 파서 (커스텀 구현) `[x]`

**의존성:** 3.1
**완료 기준:**
- Mach-O 헤더, Load commands, 심볼 파싱
- Fat binary 지원

**산출물:** `src/parser/macho_parser.c`

---

### 3.5 메타데이터 추출 `[x]`

**완료 기준:**
- 아키텍처, 엔트리포인트, 심볼 카운트
- `aura --info <file>` CLI 지원

---

### 3.6 C++ 심볼 Demangle `[x]`

**완료 기준:**
- `cxxabi.h` `__cxa_demangle()` 래핑
- `include/demangle.h` 공개 API

**산출물:** `src/parser/demangle.c`

---

### 3.7 DEX (Android) 포맷 지원 `[x]`

**의존성:** 3.1
**완료 기준:**
- DEX 헤더, string_ids, type_ids, method_ids 파싱
- `AURA_FORMAT_DEX`, `AURA_ARCH_DALVIK` 추가
- Dalvik 바이트코드 lifter

**산출물:** `src/parser/dex_parser.c`, `src/decompiler/dalvik_lifter.c`

---

### 3.8 .NET / MSIL 포맷 지원 `[x]`

**의존성:** 3.3
**완료 기준:**
- .NET PE CLR 헤더 파싱
- 메타데이터 루트, #Strings 힙, MethodDef 테이블
- `AURA_FORMAT_DOTNET`, `AURA_ARCH_MSIL` 추가

**산출물:** `src/parser/dotnet_parser.c`

---

### 3.9 펌웨어/ROM 지원 `[x]`

**완료 기준:**
- Raw binary 로더 (base address + arch 지정)
- `.firmware`, `.vectors` 섹션 생성

**산출물:** `src/parser/firmware_loader.c`

---

### 3.10 DWARF 파서 `[x]`

**의존성:** 3.2
**완료 기준:**
- `.debug_info`, `.debug_abbrev`, `.debug_line`, `.debug_str` 파싱
- 타입/변수/라인 정보 추출
- 외부 라이브러리 허용 (2026-04-04 승인)

**산출물:** `src/parser/dwarf_parser.c`, `include/dwarf_info.h`

---

### 3.11 DWARF → 타입 시스템 연동 `[x]`

**의존성:** 3.10, 5.16
**완료 기준:**
- DWARF 타입을 디컴파일러 타입 시스템에 주입
- struct 필드명, 변수명, 함수 시그니처 자동 적용

**산출물:** `src/decompiler/dwarf_types.c`

---

### 3.12 PDB 파서 `[x]`

**의존성:** 3.3
**완료 기준:**
- MSF 컨테이너, TPI, DBI 스트림 파싱
- struct/union/enum/procedure 타입

**산출물:** `src/parser/pdb_parser.c`, `include/pdb_info.h`

---

### 3.13 PDB → 타입 시스템 연동 `[x]`

**의존성:** 3.12, 5.16
**완료 기준:**
- PDB 타입/변수 정보를 디컴파일러에 주입

**산출물:** `src/decompiler/pdb_types.c`

---

### 3.14 .eh_frame / .gcc_except_table 파서 `[x]`

**의존성:** 3.2
**완료 기준:**
- ELF .eh_frame CIE/FDE 파싱
- .gcc_except_table LSDA 파싱
- try/catch 영역 추출

**산출물:** `src/parser/eh_frame_parser.c`

---

### 3.15 SEH 분석 (PE) `[x]`

**의존성:** 3.3
**완료 기준:**
- .pdata RUNTIME_FUNCTION + .xdata UNWIND_INFO 파싱
- __try/__except/__finally 영역 식별

**산출물:** `src/parser/seh_parser.c`

---

### 3.16 Relocation 완전 처리 `[x]`

**의존성:** 3.2, 3.3
**완료 기준:**
- ELF .rela.dyn/.rela.plt/.rel.* 완전 파싱
- PE .reloc BaseRelocationTable 파싱
- x86_64, AArch64, ARM32, i386 relocation 타입

**산출물:** `src/parser/relocation.c`

---

### 3.T Phase 3 종합 테스트 `[x]`

**완료 기준:**
- 전체 파서 + 디버그 정보 + 예외 처리 통합 테스트
- ELF/PE/Mach-O/DEX/.NET/Firmware 전부 PASS

**산출물:** `tests/results/3.T_parser.txt`

---

## Phase 4: 심볼릭 실행 + 고급 분석

### 4.1 심볼릭 실행 엔진 설계 `[x]`

**완료 기준:**
- `include/symbolic.h` — SymEngine, SymState, SymValue

**산출물:** `include/symbolic.h`

---

### 4.2 추상적 실행 엔진 구현 `[x]`

**의존성:** 4.1
**완료 기준:**
- `sym_engine_create()`, `sym_step()` 구현
- 기본 산술, 메모리, 레지스터 연산

**산출물:** `src/symbolic/sym_engine.c`

---

### 4.3 CFG 생성 `[x]`

**의존성:** 4.2
**완료 기준:**
- `include/cfg.h` — Cfg, BasicBlock
- `cfg_build()` 3단계 알고리즘

**산출물:** `src/symbolic/cfg.c`

---

### 4.4 DFG (Reaching Definitions) `[x]`

**의존성:** 4.3
**완료 기준:**
- `include/dfg.h` — DfgResult
- 레지스터 수준 reaching definition 분석

**산출물:** `src/symbolic/dfg.c`

---

### 4.5 함수 경계 인식 `[x]`

**의존성:** 4.3
**완료 기준:**
- `include/func_detect.h` — FuncDetect
- Prologue 패턴 (x86/AArch64/ARM) + 심볼 테이블 + call-target + Xref 기반

**산출물:** `src/symbolic/func_detect.c`

---

### 4.6 암호화 탐지 `[x]`

**완료 기준:**
- AES S-box, RC4 KSA, XOR 루프 패턴 탐지
- LLM 분석 연동 프롬프트

**산출물:** `src/core/crypto_detect.c`

---

### 4.7 네트워크 프로토콜 분석기 `[x]`

**완료 기준:**
- 60+ 네트워크 API (BSD sockets, Winsock, libcurl, OpenSSL) 심볼 매칭
- HTTP 메서드/헤더 문자열 탐지
- 포트 번호 상수 탐지

**산출물:** `src/core/net_proto.c`

---

### 4.8 FLIRT 함수 시그니처 매칭 `[x]`

**완료 기준:**
- 9개 빌트인 x86_64/AArch64 시그니처
- 패턴 매칭 엔진 (mask/wildcard 지원)
- 시그니처 DB 로드

**산출물:** `src/core/flirt.c`, `include/flirt.h`

---

### 4.9 바이너리 Diff `[x]`

**완료 기준:**
- 바이트 수준, 섹션 수준, 심볼 수준 비교
- 두 바이너리 간 차이점 표시

**산출물:** `src/core/binary_diff.c`

---

### 4.10 자동 북마크 (분석 엔진) `[x]`

**완료 기준:**
- 5개 탐지 패스: crypto, network, xref hotspots, entry point, anti-debug

**산출물:** `src/core/auto_bookmark.c`

---

### 4.11 에일리어스 분석 `[x]`

**의존성:** 5.17
**완료 기준:**
- Steensgaard union-find 기반 포인터 에일리어싱 추적
- SSA IR 수준에서 동작

**산출물:** `src/decompiler/alias_analysis.c`

---

### 4.12 테인트 분석 `[x]`

**의존성:** 4.11
**완료 기준:**
- 28개 source 함수, 36개 sink 함수 DB
- Forward taint propagation

**산출물:** `src/core/taint_analysis.c`

---

### 4.13 스택 프레임 분석 백엔드 `[x]`

**의존성:** 2.16
**완료 기준:**
- 멀티아키텍처 프롤로그 탐지 (x86_64/x86/AArch64/ARM32)
- 스택 변수 크기/오프셋/타입 자동 추론
- DWARF 변수명 연동

**산출물:** `src/decompiler/stack_analysis.c`

---

### 4.T Phase 4 종합 테스트 `[x]`

**완료 기준:**
- 심볼릭 실행 + 모든 고급 분석 통합 테스트

**산출물:** `tests/results/4.T_symbolic.txt`

---

## Phase 5: 디컴파일러 + HIR + 최적화

### 5.1 디컴파일러 설계 (SSA 기반 IR) `[x]`

**완료 기준:**
- `include/decompiler.h` — IR 구조 (22 opcodes, 13 types)
- SSA IR 5단계 알고리즘 문서화

**산출물:** `include/decompiler.h`, `docs/design/decompiler_research.md`

---

### 5.2 Pseudo-C 코드 생성기 기본 구조 `[x]`

**의존성:** 5.1
**완료 기준:**
- `ir_lift()`, `ir_build_ssa()`, `ir_emit_pseudoc()` 파이프라인

**산출물:** `src/decompiler/codegen.c`

---

### 5.3 변수 타입 추론 (기본) `[x]`

**의존성:** 5.2
**완료 기준:**
- 레지스터 크기 기반 휴리스틱
- int8/16/32/64, ptr 타입

**산출물:** `src/decompiler/type_inference.c`

---

### 5.4 제어 구조 복원 (if/loop/switch) `[x]`

**의존성:** 5.2
**완료 기준:**
- CFG 패턴 매칭 기반 제어 구조 복원
- if/else, while, switch

**산출물:** `src/decompiler/control_flow.c`

---

### 5.5 함수 호출 그래프 생성 `[x]`

**의존성:** 5.2
**완료 기준:**
- `include/callgraph.h` — CallGraph
- 직접 호출 그래프 + DOT 출력

**산출물:** `src/symbolic/callgraph.c`

---

### 5.6 디컴파일 뷰 UI 통합 `[x]`

**의존성:** 5.4, 8.12
**완료 기준:**
- GUI 디컴파일 뷰에 Pseudo-C 렌더링
- 구문 강조 (PseudoCHighlighter)

**산출물:** `src/gui/pseudoc_highlighter.cpp`

---

### 5.7 바이너리 패치 (Zydis 인코더) `[x]`

**완료 기준:**
- `include/patch.h` — PatchContext, patch_apply()
- Zydis x86/x86_64 어셈블리 인코딩

**산출물:** `src/decompiler/patch.c`

---

### 5.8 xmm → float/double 타입 추론 `[x]`

**의존성:** 5.3
**완료 기준:**
- SSE movss/addss → float, movsd/addsd → double
- SysV ABI xmm0 return

**산출물:** `src/decompiler/codegen.c` (xmm 확장)

---

### 5.9 x87 FPU → long double 타입 추론 `[x]`

**의존성:** 5.3
**완료 기준:**
- fld/fst/fadd/fmul/fdiv 처리
- st(0)~st(7) 스택 추적

**산출물:** `src/decompiler/codegen.c` (x87 확장)

---

### 5.10 ymm/zmm 벡터 타입 추론 `[x]`

**의존성:** 5.3
**완료 기준:**
- AVX/AVX-512 명령어 lifting
- `__m128`, `__m256`, `__m512` 타입

**산출물:** `src/decompiler/codegen.c` (AVX 확장)

---

### 5.11 MMX 타입 추론 `[x]`

**의존성:** 5.3
**완료 기준:**
- mm0~mm7 레지스터
- movq/paddb/pmullw 등 MMX 명령어

**산출물:** `src/decompiler/codegen.c` (MMX 확장)

---

### 5.12 ARM/AArch64 디컴파일 `[x]`

**의존성:** 5.2
**완료 기준:**
- `ir_lift_arm64()` — AArch64 전용 리프터
- AAPCS 호출 규약

**산출물:** `src/decompiler/arm64_lifter.c`

---

### 5.13 MIPS 디컴파일 `[x]`

**완료 기준:**
- `ir_lift_mips()` — MIPS 리프터
- $a0-$a3 ABI, $v0 return

**산출물:** `src/decompiler/mips_lifter.c`

---

### 5.14 PowerPC 디컴파일 `[x]`

**완료 기준:**
- `ir_lift_ppc()` — PowerPC 리프터
- r3-r10 ABI

**산출물:** `src/decompiler/ppc_lifter.c`

---

### 5.15 RISC-V 디컴파일 `[x]`

**완료 기준:**
- `ir_lift_riscv()` — RISC-V 리프터
- a0-a7 ABI

**산출물:** `src/decompiler/riscv_lifter.c`

---

### 5.16 구조체/배열 자동 복원 `[x]`

**의존성:** 4.13
**완료 기준:**
- 메모리 접근 패턴 기반 struct field 추론
- 배열 접근 (base + index * scale) 인식

**산출물:** `src/decompiler/struct_recovery.c`

---

### 5.17 포인터 체인 추적 `[x]`

**의존성:** 5.16
**완료 기준:**
- 다중 역참조 (p->next->data) 패턴 인식

**산출물:** `src/decompiler/ptr_chain.c`

---

### 5.18 변수 이름 전파 `[x]`

**의존성:** 5.16
**완료 기준:**
- SSA 기반 변수명 전파 (디버그 심볼 → 전체 함수)

**산출물:** `src/decompiler/var_propagation.c`

---

### 5.19 상수 전파 (Dataflow) `[x]`

**의존성:** 5.2
**완료 기준:**
- SSA sparse worklist 기반 상수 폴딩 + 전파
- CONST/COPY/PHI/binary arithmetic/CMP 처리

**산출물:** `src/decompiler/const_prop.c`

---

### 5.20 데드코드 제거 `[x]`

**의존성:** 5.19
**완료 기준:**
- Unreachable block 제거
- 사용되지 않는 변수 제거 (mark-sweep DCE)

**산출물:** `src/decompiler/dead_code.c`

---

### 5.21 예외 흐름 CFG 통합 `[x]`

**의존성:** 3.14, 3.15
**완료 기준:**
- try/catch/throw → CFG 엣지 반영
- 디컴파일 출력: `try { ... } catch (...)` / `__try { ... } __finally`

**산출물:** `src/decompiler/exception_flow.c`

---

### 5.22 최적화 패스 매니저 `[x]`

**완료 기준:**
- `include/pass_manager.h` — IrPass 인터페이스
- Fixpoint 반복 (최대 5회)
- 기존 ir_optimize() 리팩토링

**산출물:** `src/decompiler/pass_manager.c`

---

### 5.23 Copy Propagation 강화 `[x]`

**의존성:** 5.22
**완료 기준:**
- 체인 전파 + PHI-through 전파
- PassManager 등록

**산출물:** `src/decompiler/copy_prop.c`

---

### 5.24 Expression Simplification `[x]`

**의존성:** 5.22
**완료 기준:**
- 항등 규칙 (x+0, x*1, x*0, x-x 등)
- 이중 부정, 상수 체인 폴딩

**산출물:** `src/decompiler/expr_simplify.c`

---

### 5.25 CSE (공통 부분식 제거) `[x]`

**의존성:** 5.22
**완료 기준:**
- 해시 기반 value numbering (GVN-lite)

**산출물:** `src/decompiler/cse.c`

---

### 5.26 Condition Simplification `[x]`

**의존성:** 5.22
**완료 기준:**
- `if(x!=0) → if(x)`, De Morgan, 불가능 조건 제거

**산출물:** `src/decompiler/cond_simplify.c`

---

### 5.27 Natural Loop Detection `[x]`

**의존성:** 5.4
**완료 기준:**
- Back-edge 기반 natural loop 탐지
- while / do-while / for 분류 (induction variable)

**산출물:** `src/decompiler/loop_detect.c`

---

### 5.28 Advanced Control Flow Structuring `[x]`

**의존성:** 5.27
**완료 기준:**
- Post-dominator tree (Cooper et al.)
- Interval 기반 구조적 분석

**산출물:** `src/decompiler/structural_analysis.c`

---

### 5.29 Goto Elimination `[x]`

**의존성:** 5.28
**완료 기준:**
- Break/continue 변환
- Goto 출현율 < 5%

**산출물:** `src/decompiler/goto_elimination.c`

---

### 5.30 Switch/Case Recovery `[x]`

**의존성:** 5.28
**완료 기준:**
- 비교 체인 (if-else-if) → switch 변환
- 점프 테이블 기반 switch (2.13 활용)

**산출물:** `src/decompiler/switch_recovery.c`

---

### 5.31 Phi Elimination / Out-of-SSA `[x]`

**의존성:** 5.22
**완료 기준:**
- φ-함수 제거 → 일반 변수 할당
- 최소 복사 삽입

**산출물:** `src/decompiler/phi_elimination.c`

---

### 5.32 Register Coalescing `[x]`

**의존성:** 5.31
**완료 기준:**
- Union-Find 기반 COPY 체인 병합
- 변수 수 50% 감소 (목표 달성: 72.7%)
- 변수명 추론 (argc, i, ptr 등)

**산출물:** `src/decompiler/reg_coalesce.c`

---

### 5.33 TIE 제약 기반 타입 추론 `[x]`

**의존성:** 5.22
**완료 기준:**
- LOAD/STORE/ADD/CALL 제약 수집
- Union-find 기반 해결
- 25개 libc 함수 시그니처 연동

**산출물:** `src/decompiler/type_constraint.c`

---

### 5.34 Expression Reassociation `[x]`

**의존성:** 5.32
**완료 기준:**
- 가환 연산 canonical ordering
- 중첩 괄호 최소화

**산출물:** `src/decompiler/expr_reassoc.c`

---

### 5.35 Dead Store Elimination `[x]`

**의존성:** 5.22, 4.11
**완료 기준:**
- 에일리어스 분석 기반 안전한 dead store 제거

**산출물:** `src/decompiler/dead_store.c`

---

### 5.36 Tail Call Detection `[x]`

**의존성:** 5.22
**완료 기준:**
- call + ret 패턴 → `return func()` 출력

**산출물:** `src/decompiler/tail_call.c`

---

### 5.37 LICM (Loop Invariant Code Motion) `[x]`

**의존성:** 5.27
**완료 기준:**
- 루프 불변 연산을 preheader로 이동
- 부작용 없는 연산만

**산출물:** `src/decompiler/licm.c`

---

### 5.38 Strength Reduction `[x]`

**의존성:** 5.27
**완료 기준:**
- `x*8 → x<<3` (2의 거듭제곱 MUL → SHL)

**산출물:** `src/decompiler/strength_reduce.c`

---

### 5.39 HIR (High-level IR) 설계 문서 `[x]`

**완료 기준:**
- `docs/design/high_level_ir.md`
- 22개 HIR 노드 정의
- SSA IR → HIR 변환 전략

**산출물:** `docs/design/high_level_ir.md`

---

### 5.40 HIR Builder 구현 `[x]`

**의존성:** 5.39, 5.28
**완료 기준:**
- `include/hir.h` — HirNode, HirFunc
- SSA IR + 구조적 분석 → HIR 트리

**산출물:** `include/hir.h`, `src/decompiler/hir_builder.c`

---

### 5.41 Aggregate Type System `[x]`

**의존성:** 5.40, 5.33
**완료 기준:**
- struct/array/union을 HIR 타입으로
- 5.16 struct_recovery 결과 연동

**산출물:** `src/decompiler/aggregate_types.c`

---

### 5.42 HIR → Pseudo-C Emission `[x]`

**의존성:** 5.40, 5.41
**완료 기준:**
- 고품질 Pseudo-C 생성
- `ptr->field`, `arr[i]` 표현
- 연산자 우선순위 기반 최소 괄호

**산출물:** `src/decompiler/hir_emit.c`

---

### 5.43 디컴파일러 품질 메트릭 `[x]`

**의존성:** 5.42
**완료 기준:**
- 변수 수, 표현식 깊이, goto 카운트 측정
- 달성: 변수 72.7% 감소, goto 0%, F1 0.866 (Ghidra 초과)

**산출물:** `tests/benchmark/bench_decompiler.c`

---

### 5.44 Round-trip Compilation Test `[x]`

**의존성:** 5.42
**완료 기준:**
- Pseudo-C 출력 → gcc 컴파일 성공
- 7/7 함수 통과

**산출물:** `tests/decompiler/test_roundtrip.c`

---

### 5.T Phase 5 종합 테스트 `[x]`

**완료 기준:**
- 전체 디컴파일러 + 16개 최적화 패스 + HIR 통합 테스트
- 품질 메트릭 달성

**산출물:** `tests/results/5.T_decompiler.txt`

---

## Phase 6: LLM 로컬 연동

### 6.1 LLM 연동 모듈 설계 `[x]`

**완료 기준:**
- `include/llm.h` — LlmClient vtable
- `docs/design/llm_integration.md`

**산출물:** `include/llm.h`

---

### 6.2 LM Studio API 클라이언트 `[x]`

**의존성:** 6.1
**완료 기준:**
- libcurl 기반 OpenAI-compatible API 클라이언트
- `http://localhost:1234/v1/chat/completions`

**산출물:** `src/llm/lmstudio_client.c`

---

### 6.3 llama.cpp 연동 `[x]`

**의존성:** 6.1
**완료 기준:**
- llama.cpp server API 클라이언트

**산출물:** `src/llm/llamacpp_client.c`

---

### 6.4 로컬 모델 캐시 시스템 `[x]`

**의존성:** 6.2, 6.3
**완료 기준:**
- 파일 기반 JSON 캐시
- SHA256 key (model + prompt + temperature)

**산출물:** `src/llm/llm_cache.c`

---

### 6.5 프롬프트 템플릿 및 파싱 `[x]`

**의존성:** 6.4
**완료 기준:**
- FUNC_NAME, CODE_SUMMARY 템플릿
- JSON 응답 파싱

**산출물:** `src/llm/prompt_templates.c`

---

### 6.T Phase 6 종합 테스트 `[x]`

**완료 기준:**
- LLM 로컬 연동 전체 테스트
- 20/20 PASS

**산출물:** `tests/results/6.T_local_llm.txt`

---

## Phase 7: LLM 클라우드 + 고급 기능

### 7.1 클라우드 API 통합 설계 `[x]`

**의존성:** 6.1
**완료 기준:**
- OpenAI 호환 API 설계
- `docs/design/llm_integration.md` 클라우드 섹션

---

### 7.2 OpenAI API 클라이언트 `[x]`

**의존성:** 7.1
**완료 기준:**
- libcurl 기반 OpenAI Chat Completions
- 환경변수 `OPENAI_API_KEY` 지원

**산출물:** `src/llm/openai_client.c`

---

### 7.3 Groq API 클라이언트 `[x]`

**의존성:** 7.1
**완료 기준:**
- Groq API 클라이언트
- OpenAI 호환 helpers 재활용

**산출물:** `src/llm/groq_client.c`

---

### 7.4 API 키 관리 + 설정 UI `[x]`

**의존성:** 7.2, 7.3
**완료 기준:**
- 설정 파일 기반 API 키 저장
- Qt6 설정 다이얼로그

**산출물:** `src/llm/llm_config.c`, `src/gui/settings_dialog.cpp`

---

### 7.5 요청/응답 캐싱 시스템 `[x]`

**의존성:** 7.4
**완료 기준:**
- 클라우드용 캐시 확장 (6.4 재활용)

**산출물:** `src/llm/llm_cache.c` (확장)

---

### 7.6 LLM 취약점 분석 `[x]`

**의존성:** 7.4
**완료 기준:**
- 선택 함수 → 보안 취약점 탐지/설명
- `LLM_PROMPT_VULN_ANALYSIS` 템플릿

---

### 7.7 LLM 대화형 질의 `[x]`

**의존성:** 7.4
**완료 기준:**
- GUI LLM 패널에서 자유 질문 입력
- 현재 함수 컨텍스트 자동 포함

**산출물:** `src/gui/llm_panel.cpp`

---

### 7.8 LLM 분석 히스토리 `[x]`

**의존성:** 7.7
**완료 기준:**
- LlmHistoryEntry 저장/재사용
- QListWidget 히스토리 UI

---

### 7.T Phase 7 종합 테스트 `[x]`

**완료 기준:**
- 클라우드 LLM + 고급 기능 통합 테스트

**산출물:** `tests/results/7.T_cloud_llm.txt`

---

## Phase 8: GUI (Qt6) + 협업 서버

### 8.1 Qt6 + CMake 빌드 환경 `[x]`

**완료 기준:**
- Qt6 발견 + `aura-gui` 타겟

---

### 8.2 SQLite amalgamation 통합 `[x]`

**완료 기준:**
- `third_party/sqlite/` amalgamation
- 정적 링크

---

### 8.3 프로젝트 시스템 `[x]`

**완료 기준:**
- `.aura/` 디렉토리 기반 프로젝트
- SQLite `.aura.db`

---

### 8.4 Project Manager 창 `[x]`

**완료 기준:**
- New/Open Project UI
- 최근 10개 프로젝트 관리

---

### 8.5 MainWindow 뼈대 `[x]`

**완료 기준:**
- 좌측 아이콘바 + 중앙 뷰 + 우측 패널 레이아웃

---

### 8.6 테마 + 폰트 설정 `[x]`

**완료 기준:**
- Catppuccin (다크/라이트) 테마
- 폰트 설정

---

### 8.7 File Open/Import `[x]`

**완료 기준:**
- Open (mmap 직접) + Import (프로젝트 복사)
- QFileDialog DontUseNativeDialog (VNC 호환)

---

### 8.8 자동 분석 통합 `[x]`

**완료 기준:**
- 바이너리 로드 시 자동 분석 파이프라인 (QThread 백그라운드)

---

### 8.9 Export 기능 `[x]`

**완료 기준:**
- ASM, JSON, C bytes, Hex dump 4종 export

---

### 8.10 디스어셈블리 뷰 `[x]`

**완료 기준:**
- 100K 줄 렌더링 + 주소/바이트/니모닉 컬럼
- 이진 탐색 기반 navigateToAddress

---

### 8.11 Hex 뷰 `[x]`

**완료 기준:**
- 16진수 + ASCII 디스플레이

---

### 8.12 디컴파일 뷰 `[x]`

**완료 기준:**
- 함수 범위 추출 + Pseudo-C 렌더링
- FuncEntry 기반 범위 확정

---

### 8.13 뷰 동기화 `[x]`

**완료 기준:**
- Fn 클릭 → 디스어셈블리 + 디컴파일 동기 이동

---

### 8.14 LLM 패널 `[x]`

**완료 기준:**
- 현재 함수 → LLM 질의 + 응답 표시

---

### 8.15 아이콘바 + 패널 전환 `[x]`

**완료 기준:**
- Fn/Aa/Se/Ty/Bk 패널 토글

---

### 8.16 심볼 목록 패널 `[x]`

**완료 기준:**
- 심볼 목록 + 클릭 이동

---

### 8.17 문자열 목록 패널 `[x]`

**완료 기준:**
- .rodata 문자열 목록

---

### 8.18 섹션/세그먼트 패널 `[x]`

**완료 기준:**
- ELF/PE/Mach-O 섹션 트리

---

### 8.19 데이터 타입 패널 (Level 1) `[x]`

**완료 기준:**
- 기본 타입 (int, ptr 등) 표시

---

### 8.20 북마크 패널 `[x]`

**완료 기준:**
- 수동 + 자동 북마크 목록

---

### 8.21 검색 (Go to Address + 심볼/문자열) `[x]`

**완료 기준:**
- 주소/심볼/문자열 검색 통합

---

### 8.22 Navigation 히스토리 `[x]`

**완료 기준:**
- Back/Forward 이동

---

### 8.23 상태바 완성 `[x]`

**완료 기준:**
- 주소/오프셋/심볼릭/분석상태 표시

---

### 8.24 Console/Messages 패널 `[x]`

**완료 기준:**
- 로그 메시지 + 토글

---

### 8.25 Undo/Redo 시스템 `[x]`

**완료 기준:**
- QUndoStack 통합

---

### 8.26 프로젝트 저장/복원 `[x]`

**완료 기준:**
- SessionManager + SQLite 저장

---

### 8.27 인라인 리네이밍 `[x]`

**완료 기준:**
- 함수/변수 이름 인라인 편집

---

### 8.28 주석/코멘트 `[x]`

**완료 기준:**
- 주소별 주석 저장

---

### 8.29 명령 팔레트 `[x]`

**완료 기준:**
- Ctrl+P → 명령 팔레트

---

### 8.30 CFG 그래프 뷰 `[x]`

**완료 기준:**
- BFS 레이아웃 + 색상 구분 엣지
- DOT export

**산출물:** `src/gui/cfg_view.cpp`

---

### 8.31 Call Graph 뷰 `[x]`

**완료 기준:**
- 함수 호출 관계 시각화

**산출물:** `src/gui/callgraph_view.cpp`

---

### 8.32 패치 편집기 `[x]`

**완료 기준:**
- 어셈블리 입력 → 라이브 미리보기 → 적용

**산출물:** `src/gui/patch_editor.cpp`

---

### 8.33 Stack Layout 뷰 `[x]`

**의존성:** 4.13
**완료 기준:**
- 스택 프레임 시각화 (지역 변수, 인자, 패딩)

**산출물:** `src/gui/stack_layout_view.cpp`

---

### 8.34 데이터 타입 편집 (Level 2) `[x]`

**완료 기준:**
- 변수 타입 변경 UI

**산출물:** `src/gui/type_editor.cpp`

---

### 8.35 구조체/enum 정의 (Level 3) `[x]`

**의존성:** 8.34
**완료 기준:**
- 사용자 정의 struct/enum UI

---

### 8.36 바이트 패턴 검색 `[x]`

**완료 기준:**
- Hex 시퀀스 검색

**산출물:** `src/core/search.c`

---

### 8.37 와일드카드 패턴 검색 `[x]`

**완료 기준:**
- `90 ?? CC` 형태 패턴

---

### 8.38 정규식 검색 `[x]`

**완료 기준:**
- POSIX 확장 정규식

---

### 8.39 상수값 검색 `[x]`

**완료 기준:**
- Immediate 값 검색

---

### 8.40 YARA 규칙 검색 `[x]`

**완료 기준:**
- libyara 정적 링크 (BSD 3-Clause)
- `third_party/yara/`

**산출물:** `src/core/yara_search.c`

---

### 8.41 텍스트 검색 `[x]`

**완료 기준:**
- 디스어셈블/디컴파일 뷰 텍스트 검색

---

### 8.42 Xref UI `[x]`

**의존성:** 2.8
**완료 기준:**
- Xref To/From 표시

---

### 8.43 단축키 체계 `[x]`

**완료 기준:**
- 40+ 기본 단축키 + 사용자 커스터마이징
- QSettings 영속성

**산출물:** `src/gui/shortcut_manager.cpp`

---

### 8.44 Select 메뉴 `[x]`

**완료 기준:**
- All/None/Instructions/Data/Undefined 등 8개 선택 액션

---

### 8.45 Tools 메뉴 `[x]`

**완료 기준:**
- Script Manager, REPL, Patch Editor 통합

---

### 8.46 파일 잠금 토글 `[x]`

**완료 기준:**
- 상태바 잠금 토글 + UndoStack 비활성화

---

### 8.47 분석 자동위치 표시 `[x]`

**완료 기준:**
- 상태바에 현재 분석 주소 표시

---

### 8.48 스냅샷 `[x]`

**완료 기준:**
- 분석 상태 스냅샷 저장/복원
- SQLite `snapshots` 테이블

---

### 8.49 디버거 제어 `[x]`

**완료 기준:**
- 중단점 + 레지스터 + 실행 제어 UI

**산출물:** `src/gui/debugger_panel.cpp`

---

### 8.50 프로세서 매뉴얼 접근 `[x]`

**완료 기준:**
- 우클릭 → 명령어 매뉴얼 (100+ x86 참조)

---

### 8.51 인쇄 기능 `[x]`

**완료 기준:**
- File > Print (Ctrl+P) QPrinter 통합

---

### 8.52 컬럼 커스터마이징 `[x]`

**완료 기준:**
- 디스어셈블 뷰 컬럼 가시성/폭 설정

**산출물:** `src/gui/disasm_column_config.cpp`

---

### 8.53 AURA Server 설계 `[x]`

**완료 기준:**
- `docs/design/collab_server.md` — 서버-클라이언트 아키텍처
- WebSocket 프로토콜 (JSON over TCP:17721)
- 토큰 기반 인증, role 기반 권한

---

### 8.54 실시간 동기화 엔진 `[x]`

**의존성:** 8.53
**완료 기준:**
- 변경 이벤트 전파, LWW 충돌 해결
- Global monotonic sequence ordering
- 오프라인 큐 + 재접속 시 동기화

**산출물:** `src/collab/collab_sync.cpp`, `src/collab/collab_server.cpp`

---

### 8.55 협업 모드 UI `[x]`

**의존성:** 8.54
**완료 기준:**
- 접속 사용자 목록, 실시간 변경 알림, 히스토리/undo
- MainWindow 도크 패널

**산출물:** `src/gui/collab_panel.cpp`

---

### 8.T Phase 8 종합 테스트 `[x]`

**완료 기준:**
- 전체 GUI + 협업 서버 통합 테스트
- 7/7 GUI E2E 시나리오 PASS
- 전체 ctest 82/82 PASS

**산출물:** `tests/results/8.T_gui.txt`, `tests/integration/test_gui_e2e.cpp`

---

