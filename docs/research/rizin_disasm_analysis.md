# Rizin 디스어셈블러 + 파일 로더 재분석

**Session #9, 2026-04-20** — Phase 2-E 병렬 연구 (rizin-disasm-analyst, Task #31)

> Scope: Rizin 의 **asm 엔진** (`librz/arch/p/asm/*`, `librz/arch/p/analysis/*`) + **바이너리 로더** (`librz/bin/format/*`) 에 집중.
> 자매 task: #30 함수 탐지 & 분석 passes, #32 RzIL 및 decompile bridge. Ghidra #27 과 triangulation.
> 라이선스: **LGPL-3** (Rizin). 본 문서는 공개 소스/문서 분석만으로 작성했으며 코드 복사 없음 — 설계 참고만 가능.

---

## 1. Executive Summary

Rizin 은 radare2 fork (2020~) 로 **"UX + 코드 청결도"** 를 목표로 재구성된 RE 프레임워크다. AURA 와 비교하면 디스어셈블러/로더 영역에서 **가장 근접한 사례** — 양쪽 모두 (1) Capstone 기반 wrapper + (2) libelf 미사용 커스텀 ELF 파서 + (3) recursive descent 분석 경로를 채택한다. 따라서 "Ghidra 로드맵" 에서 기술 격차가 너무 커 보이는 기능들의 **현실적 중간 단계** 가 Rizin 에 이미 구현되어 있다.

**본 분석에서 도출한 격차 top 3** (AURA 기준):

1. **ARM/Thumb 매핑 심볼 (`$t`, `$a`, `$d`) 처리 부재.** Rizin 도 완전하지는 않으나 (issue #4665 고빈도 bug 존재) ELF symbol table 의 ARM mapping symbols 를 `asm.bits` 전환 힌트로 소비한다. AURA `src/parser/elf_parser.c` 는 `$t` 심볼을 일반 FUNC/OBJECT 로만 분류하고, `capstone_wrapper.c` 는 **단일 ARM 모드** (`CS_MODE_ARM`) 로 컨텍스트 고정. 이는 Ghidra #27 S-1 제안과 정확히 겹치며, Rizin 이 선행 참조다.

2. **Jump-table heuristic arch coverage.** Rizin 의 `jmptbl.c` (radare2 legacy 계승) 는 `try_walkthrough_jmptbl` / `try_walkthrough_casetbl` / `walkthrough_arm_jmptbl_style` / `r_anal_jmptbl_arm64_from_br` 의 **4-분기 dispatcher** 로 x86 / ARM(Thumb TBH/TBB) / AArch64 / MIPS(GP relative) 를 커버한다. AURA `src/decompiler/switch_recovery.c` (294 LOC) 는 control-flow chain consolidation 만 — **raw byte-level jump table walker 없음**. rc3 real-binary corpus 에서 switch 손실 위주 miss 가 누적되는 원인.

3. **Loader 모듈 분화 깊이.** Rizin `librz/bin/format/elf/` 는 `elf_symbols.c` / `elf_relocs.c` / `elf_sections.c` / `elf_segments.c` / `elf_dynamic.c` / `elf_strtab.c` 등 **책임 단위로 파일 분리**. AURA `src/parser/elf_parser.c` 는 525 LOC 단일 파일에 전 책임 집약. 기능 parity 자체는 근접하나, relocation 처리 고도화 (특히 R_AARCH64_* LD/ST 쌍) 에서 AURA 가 아직 얕다.

**AURA 가 가장 실용적으로 차용할 레버** 는 Ghidra 의 SLEIGH 도입 같은 대형 재설계가 아니라, **Rizin 의 세 가지 기존 관용구를 직접 이식** 하는 것: (a) ARM mapping symbol → decode mode slicing, (b) per-arch jumptbl walker, (c) loader 파일 분할. §7 상세.

---

## 2. Rizin 전체 파이프라인

```
┌─────────────────────────┐
│ rz_bin (librz/bin/)     │  format detect → loader plugin → RzBinObject
│  format/elf,pe,mach0,…  │  sections / symbols / relocs / imports / strings
└──────────┬──────────────┘
           │ RzBinObject
           ▼
┌─────────────────────────┐
│ rz_io (librz/io/)       │  multi-mapped address space (virtual ↔ physical)
│  io map stacking        │  rva resolution, patching, cache layer
└──────────┬──────────────┘
           │ byte stream with mapping
           ▼
┌─────────────────────────┐
│ rz_asm (librz/arch/p/   │  plugin dispatcher (arch / cpu / bits)
│        asm/*)           │  asm_*.c — disassemble 1 instruction
│   → Capstone / Zydis /  │  (adapter pattern — plugin selects backend)
│     custom / GNU binutils
└──────────┬──────────────┘
           │ RzAsmOp (mnemonic + operand string)
           ▼
┌─────────────────────────┐
│ rz_analysis (librz/arch │  RzAnalysisOp (type, jump, fail, ptr, stackop…)
│  /p/analysis/*)         │  analysis_*.c — parallel to asm plugin, decides
│                         │  "what does this instruction semantically do"
└──────────┬──────────────┘
           │ RzAnalysisOp + optional RzILOp effect
           ▼
┌─────────────────────────┐
│ recursive analysis (aa, │  af → fcn discovery, aar → xref, aac → call
│  aaa, aaaa)             │  jmptbl walker, signature matcher, emulation
└─────────────────────────┘
```

Rizin 의 독특한 설계 결정:

- **`asm` plugin 과 `analysis` plugin 을 분리**. 한 아키텍처가 디코딩 (opcode → 문자열) 과 의미분석 (opcode → type/flow) 를 서로 다른 플러그인 파일로 구현한다. 같은 Capstone 엔진을 공유하더라도 두 plugin 은 각각 `handle` 을 만들고 별도로 옵션을 설정한다 (`librz/arch/p/asm/asm_arm_cs.c` vs `librz/arch/p/analysis/analysis_arm_cs.c`).
- **Multi-backend per-arch**: x86 혼자 `asm_x86_as.c` (GNU as), `asm_x86_nasm.c`, `asm_x86_nz.c` (native), `asm_x86_zydis.c` 의 **4 개 어셈블러 + Capstone analysis** 를 갖는다. AURA 는 현재 Capstone + Zydis 2-backend (disasm + reassemble).
- **IL (RzIL) 은 별도 계층**: decode 후 `il/` 폴더의 lifter 가 RzAnalysisOp → RzIL 로 변환. Ghidra PCode 와 유사한 역할 (Task #32 주 관심사).

---

## 3. librz/arch — 디스어셈블러 플러그인 생태계

### 3.1 디렉토리 구조

```
librz/arch/
├── arch.c, asm.c, analysis.c, aop.c, op.c   # core dispatcher
├── block.c, fcn.c, xrefs.c                  # analysis primitives
├── cpus/                                    # CPU variant definitions
├── esil/                                    # ESIL (Evaluable Strings IL) — legacy from r2
├── il/                                      # RzIL (Rizin IL) — new unified IL
├── isa/                                     # raw decoder tables (hand-written, ~50 arch)
├── isa_gnu/                                 # GNU binutils ported decoders (fallback)
├── opcodes/, platforms/, types/, cpus/
├── p/
│   ├── arch_*.c                             # top-level arch plugin (wraps asm+analysis)
│   ├── asm/asm_<arch>[_<backend>].c         # ~80 files — disassembler plugins
│   ├── analysis/analysis_<arch>[_<backend>].c  # parallel analysis plugins
│   └── parse/                               # syntax highlighting / pseudo
└── rtti.c, rtti_itanium.c, rtti_msvc.c      # RTTI walkers
```

### 3.2 Capstone 기반 플러그인 집합

- **15+ `_cs` suffix plugin**: ARM, Alpha, HPPA, LoongArch, M680x, M68k, MIPS, PPC, RISC-V, SPARC, SysZ(시스템 Z), TriCore, XCore, Xtensa, CBPF. AURA 가 현재 쓰는 Capstone 아키텍처 4종 (x86/x86_64/ARM/ARM64) 대비 **3~4 배 확장** 을 한 프레임 안에서 수용.
- **Capstone cs_helper.h** 가 `rz_asm_*_cs` / `rz_analysis_*_cs` 의 공통 라이프사이클 (init / fini / disasm / opex / detail) 을 제공. 이는 AURA `capstone_wrapper.c` 가 현재 담당하는 역할과 동일하나, Rizin 은 **per-arch context struct** 를 따로 둔다 (예: `AnalysisArmCSContext { RzArmITContext it; csh handle; int omode; int obits; }`). AURA 의 `struct DisasmContext { csh; AuraArch; cs_err; }` 대비 **IT-block 상태 / 동적 mode tracking** 이 추가된 점이 구조적 차이.

### 3.3 non-Capstone backends

같은 아키텍처에 backend 가 여러 개 존재하는 의미:

| arch | backend (복수) | 용도 |
|------|---------------|------|
| x86  | `_as` (GNU as), `_nasm`, `_nz` (native), `_zydis`, Capstone analysis | reassembly 품질별 선택 (예: `_nz` 는 standalone tiny coder, `_zydis` 는 최고 정확도) |
| arm  | `_as` (GNU as), `_cs` (Capstone) | assemble 과 disassemble 를 다른 엔진으로 |

AURA 시사점: **Zydis 는 이미 있음**. AURA 의 `src/disasm/zydis_wrapper.c` 는 패치/assemble 전용 (v2.0.0 Phase 5.7). Rizin 은 동일 backend 를 **disasm 용 fallback** 으로도 등록 — Capstone decode 실패/불일치 cross-check 용도. 이는 AURA real-binary corpus 에서 Capstone 디코딩 버그가 의심될 때 활용 가능한 **무료 2nd opinion** 이다.

### 3.4 새 아키텍처 추가 비용

Rizin 에서 새 ISA 추가는:
- Capstone 가 지원한다면: `asm/asm_<arch>_cs.c` + `analysis/analysis_<arch>_cs.c` 의 `arch_*` plugin 2 파일 (~300 LOC 각). 대부분은 mapping table (`cs_insn_id → RzAnalysisOpType`) 나열.
- Capstone 미지원이면: `isa/<arch>/*` 수준에서 hand-written decoder (대형 작업, 수천 LOC).

AURA 시사점: 현재 AURA 는 Capstone 에서 지원하는 아키텍처만 수용하며 (`aura.h:AuraArch` enum 4종), 4종→50+ 종으로의 스케일 아웃은 **enum 확장 + `capstone_arch_from_aura` switch** + arch-specific analysis 추가가 필요. Rizin 의 plugin registration 테이블 패턴 (정적 배열에 plugin struct 를 링크 시점에 등록) 은 AURA 에서도 동일하게 쓸 수 있다. 단, MVP 에서 arch 확장은 비목표 (PRD §2).

---

## 4. Linear vs Recursive Disassembly

### 4.1 명령어 체계

| 명령 | 동작 | AURA 대응 |
|------|------|----------|
| `pd N`   | 현재 PC 에서 N 개 instruction linear disasm | `--disasm` 출력의 일반 경로 |
| `pD N`   | N **바이트** linear disasm | (AURA 에 직접 대응 없음; offset 기반 호출만) |
| `pdf`    | 현재 함수 전체 disasm (decode + flow-sensitive) | CLI `--disasm-func` + `pipeline.c::aura_full_analyze()` |
| `pde N`  | execution flow 따라 N instruction — **conditional/unconditional** branch 의 taken 경로 추적 | 없음 (AURA 는 CFG 빌드 후 걸쳐가는 구조) |
| `pdr`    | 함수 그래프 전체 recursive — 모든 reachable block 을 DFS 순회 | `recursive_disasm.c::recursive_disasm_from_entries` 가 reachable 집계와 동일 역할 |
| `af`     | 현재 위치에서 함수 경계 해석 → RzAnalysisFunction | `func_detect.c` |
| `afr`    | recursive — call 대상까지 따라가며 함수 생성 | AURA 는 `xref.c` + `recursive_disasm.c` 의 queue 기반 work-list 로 동일 |

### 4.2 재귀 경로 핵심 결정

Rizin `fcn.c` 의 함수 분석은 **exploration BFS** + **signature halt** 가 기본. AURA recursive_disasm.c 와의 구조적 차이:

| 항목 | Rizin | AURA |
|------|-------|------|
| work-queue | `RzList<Addr>` 로 BFS | `WorkQueue` (sorted) — recursive_disasm.c |
| visited set | hash map | sorted array (250+ LOC에 걸친 linear scan) |
| terminator 규칙 | arch-specific `RzAnalysisOp.type == JMP/RET/UNK/ILL` + noreturn hint | x86 ret/hlt/ud2/int3 + unconditional jmp — arch 하드코딩 |
| call target 등록 | 즉시 큐잉, noreturn 검증 전 reconciliation | 큐잉만, noreturn 은 `noreturn_detect.c` 에서 별도 처리 |
| conditional branch | both taken / fallthrough 큐잉 | 동일 |
| indirect branch | `anal.jmptbl` 경로로 위임 → jumptbl walker | `indirect_resolver.c` (rip-rel, vtable 2패턴만) + `switch_recovery.c` (control-flow chain) |

차이 요지: **indirect branch 를 byte-level pattern 으로 풀어내는 계층이 AURA 에 없다**. Rizin 은 여기서 "walker" 라는 전용 컴포넌트를 `jmptbl.c` 하나에 집중시킨 반면, AURA 는 두 개의 얕은 모듈 (`indirect_resolver.c` 379 LOC, `switch_recovery.c` 294 LOC — 후자는 IR 레벨 chain merge 담당) 로 분산되어 있다.

---

## 5. 파일 포맷 로더 (`librz/bin/`)

### 5.1 지원 포맷

`librz/bin/format/` 하위 디렉토리 (≈ 30):
- 실행 파일: elf, pe, mach0, coff, ne, le, te, omf
- 모바일/게임: dex, apk, java, nes, nin, gns1, xbe, psxexe
- 아카이브/스크립트: bflt, pyc, luac, wasm, cart, nxo
- 메모리 덤프: mdmp, dmp, mdt, mbn
- 기타: ecoff, pef, p9, qnx, spc700, vsf, xnu, objc

AURA 현재 지원 (`src/parser/`): elf, pe, macho, dex, dotnet, pdb, dwarf, eh_frame, seh, firmware + format_detector / mapped_file / relocation. **10+ 포맷** — 카테고리 커버리지는 유사하나 Rizin 에 비해 "레거시 game console" 계열 전무.

### 5.2 ELF 파일 분리

Rizin `librz/bin/format/elf/`:
```
elf.c / elf.h / elf64.c / elf64.h         # core
elf_parser.c / elf64_parser.c             # header + layout
elf_symbols.c / elf64_symbols.c
elf_relocs.c / elf64_relocs.c
elf_sections.c / elf64_sections.c
elf_segments.c / elf64_segments.c
elf_dynamic.c / elf64_dynamic.c           # PT_DYNAMIC, .dynamic parsing
elf_strtab.c / elf64_strtab.c
```

**책임 분리 원칙**: 각 파일 = 단일 ELF sub-structure. 32/64 는 parallel 구현 (매크로 templating 없이 복제).

AURA `src/parser/elf_parser.c` 525 LOC 는 이 모든 책임을 한 파일에서 수행. 당장은 동작하지만 **relocation 확장**, **ARM-specific note section**, **.gnu.version / .gnu.version_r** 처리를 추가할 때 이 monolithic 설계가 코드 리뷰/테스트 단위를 흐리는 시점이 온다. 리팩터 제안은 §7.2.

### 5.3 PE 파일 분리 (mirror 구조)

Rizin PE: `pe.c / pe64.c / pe_hdr.c / pe_imports.c / pe_exports.c / pe_section.c / pe_relocs.c / pe_rsrc.c / pe_debug.c / pe_security.c / pe_tls.c / pe_clr.c / pe_overlay.c / pe_info.c / pemixed.c` + `pe_specs.h`.

특기할 점:
- **pemixed.c** — "native + managed (.NET IL) 혼합" 바이너리 처리. AURA 는 `dotnet_parser.c` 로 .NET 을 별도 파서로 두고 있으나 **두 포맷이 한 PE 안에 섞인 경우의 cross-ref** 는 현재 미구현.
- **pe_clr.c** — CLR header 전용. AURA `dotnet_parser.c` 와 정확히 대응.

### 5.4 libelf 사용 여부

Rizin 은 **libelf 사용 안 함** (AURA PRD §4.2 와 동일 결정). elf_parser.c 계열이 ELF spec 을 직접 해석하며 `<elf.h>` 의존조차 없음 (원시 오프셋/크기 상수를 자체 헤더로 정의). 이는 AURA 설계 결정 (PRD §4.2 "ELF/PE 파서 libelf 사용 금지") 과 **독립적으로 같은 결론** 에 도달한 동료 프로젝트라는 근거 — 향후 외부 리뷰어에게 "libelf 없이 가능" 을 입증할 때 Rizin 을 실증 사례로 인용 가능.

---

## 6. ARM / Thumb mapping symbols & Jump-table walker 심층

### 6.1 mapping symbol 소비 (Rizin issue #4665)

ARM ELF spec 에 따라 symbol table 에 다음 특수 심볼이 존재한다:
- `$a` — ARM code 시작
- `$t` — Thumb code 시작
- `$d` — data 영역 시작 (문자열/테이블/풀)

Rizin 의 현재 처리 (불완전, 활발히 수정 중):
- `librz/bin/format/elf/elf_symbols.c` 가 `$t` / `$a` / `$d` 를 파싱해 `RzBinAddrinfo` 또는 유사 메타로 기록.
- `librz/arch/p/analysis/analysis_arm_cs.c` 의 `AnalysisArmCSContext.obits` 에서 `asm.bits` 전환 시 Capstone handle 재설정.
- Issue #4665 는 **symbol 은 파싱되나 실제 disassembly 에서 힌트로 쓰이지 않아 Thumb 을 ARM 으로 잘못 해석** 하는 bug. AURA 와 **동일 종류의 bug 가 Rizin 에도 있다** 는 사실 자체가 — (a) 이 문제가 RE 프레임워크 공통 난제, (b) AURA 도 "완벽 해결" 보다 "heuristic 개선" 수준에 착륙해야 함을 보여준다.

**AURA 적용 제안**:
1. `elf_parser.c` 에서 `$t` / `$a` / `$d` 를 `FileInfo` 의 별도 **address-bits map** 배열로 수집 (기존 symbol 배열에 남기면 downstream 이 FUNC 로 오분류).
2. `capstone_wrapper.c::disasm_init` 가 특정 address 범위의 decode 요청 시 이 map 을 참조해 `cs_option(handle, CS_OPT_MODE, CS_MODE_THUMB)` 로 일시 전환.
3. 이는 Ghidra #27 문서의 **S-1 "ARM/Thumb dual-context"** 제안과 정확히 같은 작업 — Ghidra 로드맵 + Rizin 실증 둘 다의 근거로 justification 확보.

### 6.2 jmptbl.c 아키텍처별 walker

`libr/anal/jmptbl.c` (radare2, Rizin 포팅됨) 의 공개 dispatcher:
- `try_walkthrough_jmptbl` — 일반 케이스 (table base + scale + count)
- `try_walkthrough_casetbl` — case index 테이블이 별도로 존재하는 구조 (2-array indirection)
- `walkthrough_arm_jmptbl_style` — ARM Thumb `TBB` / `TBH` (byte/halfword branch tables, offset = PC + 2\*value)
- `r_anal_jmptbl_arm64_from_br` — AArch64 `br` 로부터 역추적하며 `adrp ...; add Rtbl, Rtbl, #lo12; ldr Rtarget, [Rtbl, Rindex, LSL #3]` 패턴 인식

입력 공통 시그니처:
- 함수 경계 내 **이전 기본 블록** 의 cmp/sub 로부터 table size 추정
- **Predecessor block** 에서 table base 주소 추출 (const propagation 필요 — ARM adrp 쌍, x86 `lea`/`mov` 상수)
- table 바이트를 `RzIO` 로 읽어 각 엔트리가 함수 내부 실행 주소를 가리키는지 검증 → 유효 엔트리만 xref

**AURA 현재**:
- `switch_recovery.c` 는 IR 레벨 chain merge 만 (이미 cmp/eq chain 이 IR 로 decode 완료된 상태에서 동작). raw table walking 없음.
- `indirect_resolver.c::resolve_rip_relative` + `detect_vtable_pattern` — x86 한정, 2 패턴. AArch64 adrp/ldr 페어 탐지 **없음**.
- 결과: AArch64 real binary (rc3 corpus 중 `/bin/ls` 등) 에서 switch-heavy 함수의 covered_avg 가 떨어지는 구조적 원인.

**AURA 적용 제안** (§7 S-B): `indirect_resolver.c` 를 확장해 Rizin 의 4-dispatcher 패턴 중 우선 AArch64 `adrp+ldr+br` 3-instruction 윈도우를 추가. Ghidra #27 S-3 ("AArch64 4-byte jump table + adrp/add base") 와 겹치며, Rizin 에 구현체가 존재하므로 알고리즘 참조 (복사가 아닌 spec 수준) 가능.

---

## 7. AURA 로드맵 (Rizin 관점)

### 7.1 직접 비교표

| 영역 | Rizin | AURA | Gap | 관련 파일 |
|------|-------|------|-----|----------|
| ELF loader | 자체 구현 (모듈 10+ 파일로 분리) | 자체 구현 (단일 파일 525 LOC) | 설계는 동일, 분할 필요 | `src/parser/elf_parser.c` |
| PE loader | 자체 구현 (모듈 15+ 파일) | 자체 구현 (단일 파일 498 LOC) | 동일 | `src/parser/pe_parser.c` |
| Capstone wrapper | per-arch context struct + IT state | 단일 context, 동적 mode 전환 없음 | IT-block state 부재 | `src/disasm/capstone_wrapper.c:29` |
| ARM mapping symbol 소비 | 부분 구현 (issue #4665) | 전무 | **치명적** ARM parity 결함 | `src/parser/elf_parser.c:325` |
| asm/analysis plugin 분리 | 완전 분리 (asm_*_cs + analysis_*_cs) | 미분리 (wrapper 하나) | 구조는 AURA 가 더 단순, 확장성은 낮음 | `src/disasm/capstone_wrapper.c` |
| Multi-backend per arch | x86=4 어셈블러 + Capstone | Capstone + Zydis (assemble 전용) | Zydis 를 disasm fallback 으로 추가 가능 | `src/disasm/zydis_wrapper.c` |
| Jump table (x86) | jmptbl.c + pattern match | switch_recovery.c (IR chain만) | raw walker 부재 | `src/decompiler/switch_recovery.c` |
| Jump table (ARM TBH/TBB) | walkthrough_arm_jmptbl_style | 없음 | AArch32 Thumb 테이블 코드 미커버 | `src/disasm/indirect_resolver.c` |
| Jump table (AArch64 adrp+ldr+br) | r_anal_jmptbl_arm64_from_br | 없음 | real-binary `/bin/ls` miss 원인 | `src/disasm/indirect_resolver.c` |
| IL lifting | RzIL (Task #32 scope) | HIR + IR (다계층) | 본 문서 범위 외 | — |
| Loader 포맷 수 | 30+ (게임/임베디드 포함) | 10+ (기본 + dex/.NET) | MVP scope 에선 OK | `src/parser/` |

### 7.2 단기 ROI (Rizin 참조로 정당화되는 제안)

| ID | 작업 | 예상 +Δ parity | 난이도 | 출처 |
|----|------|----------------|--------|------|
| **S-A** | ARM `$t/$a/$d` mapping symbol → per-address-range decode mode slicing | +2~4 (ARM/Thumb corpus) | Med | Rizin `elf_symbols.c` + Ghidra #27 S-1 |
| **S-B** | AArch64 `adrp+ldr+br` 3-instr 윈도우 인식 (indirect_resolver.c 확장) | +3~5 (AArch64 switch-heavy) | Med | Rizin `r_anal_jmptbl_arm64_from_br` + Ghidra #27 S-3 |
| **S-C** | ARM Thumb `TBB/TBH` walker 추가 | +1~2 (AArch32 Thumb) | Low | Rizin `walkthrough_arm_jmptbl_style` |
| **S-D** | Zydis 를 x86/x86_64 disasm 2nd opinion 으로 등록 (Capstone 결과와 대조, 불일치 시 report) | cross-check telemetry만 (직접 +Δ 없음) | Low | Rizin multi-backend 관습 |

**추천 실행 순서**: S-A → S-B (둘 다 Ghidra #27 과 중복 당첨 — 우선순위 최상) → S-C → S-D.

### 7.3 중기 리팩터

| ID | 작업 | 의도 |
|----|------|------|
| **M-A** | `src/parser/elf_parser.c` 를 `elf_header.c / elf_symbols.c / elf_relocs.c / elf_sections.c / elf_dynamic.c` 로 분할 | Rizin 의 책임 단위 분리 패턴 차용 — 향후 R_AARCH64 reloc 대거 추가 시 리뷰 단위 명료화 |
| **M-B** | `DisasmContext` 에 `mode_override_map` 필드 추가 (address → mode lookup) | S-A 의 기반. per-arch context 패턴 참조 (Rizin AnalysisArmCSContext) |
| **M-C** | `src/disasm/capstone_wrapper.c` 를 `cs_core.c` (init/destroy) + `cs_arm.c` / `cs_x86.c` 로 분할 | arch-specific quirk (IT state, x86 prefix/REX) 을 독립 파일로. Rizin 의 asm/analysis plugin 분리가 원형 |

### 7.4 중기에 하지 말아야 할 것 (scope 보호)

- **Rizin asm 플러그인 아키텍처 전체 이식 금지**. Rizin 의 "plugin registration 테이블 + dlopen" 방식은 PRD §4 "플러그인 시스템 MVP 이후 유보" 와 충돌. plugin struct 패턴의 **설계 교훈** 만 참고, runtime 동적 로딩은 도입 금지.
- **RzIL 교체 시도 금지** (본 분석 범위 외, Task #32 에서 별도 판단). AURA HIR/IR 생태계는 이미 Session #8 에 안정화 진행 중.
- **50+ 아키텍처 확장 금지** (PRD §2). 현재 4 arch → 필요 시 +2 (RISC-V / MIPS) 수준이 MVP 상한.

---

## 8. Rizin 과 Ghidra/IDA 의 포지셔닝 (curator 참고)

| 축 | Ghidra | Rizin | AURA |
|----|--------|-------|------|
| 디코딩 모델 | SLEIGH DSL (declarative) | Capstone wrapper + hand-written fallback | Capstone wrapper |
| IL | PCode (80+ opcode) | RzIL (수십 opcode, newer) / ESIL (legacy) | HIR + IR (25+ opcode) |
| 로더 | Java-based FormatLoader | C-based per-format module | C-based per-format file |
| 플러그인 확장 | Java + Python(Jython) 스크립트 | C plugin + Python/Rust binding | **비목표** (MVP) |
| 라이선스 | Apache-2 | LGPL-3 | Apache-2 (AURA) — Rizin code 직접 reuse 불가, 설계 참조만 |

**중요**: Rizin 은 **LGPL-3**. AURA (Apache-2) 에 Rizin 코드 직접 복사 시 라이선스 incompatibility. 본 문서는 **개념/알고리즘 명세 참조** 만 허용하며, 구현은 spec 을 읽고 **from scratch** 로 작성해야 한다. commit message 에 "Rizin algorithm reference" 수준의 인용은 가능, 코드 블록 복사는 금지.

---

## 9. 재활용 가이드

### 9.1 후속 세션에서 본 문서 쓰는 법

1. real-binary parity 개선 세션 착수 시 §7.2 의 **S-A / S-B / S-C** 우선 검토 — Ghidra #27 와 중복되어 triangulated 레버.
2. 새 binary format 지원 요청 들어올 때 §5 **Rizin format 디렉토리 리스트** 로 bundled scope 체크 (예: "dex 가능한가?" → AURA 이미 있음).
3. ELF 파서 리팩터 PR 에서 M-A 분할 패턴 인용.
4. 사용자로부터 "libelf 왜 안 써?" 질문 받았을 때 §5.4 인용 (Rizin 동일 결정).

### 9.2 Triangulation with Ghidra #27 / #30 / #32

| 제안 | 출처 (본 문서) | 겹치는 타 문서 | 우선순위 |
|------|--------------|---------------|---------|
| ARM mapping symbol 소비 | S-A | Ghidra #27 S-1 | **최상** — 두 프레임워크에서 동일 레버 확인 |
| AArch64 jump table | S-B | Ghidra #27 S-3 | **상** — 동일 |
| ELF 파서 분할 | M-A | — (본 문서 독자) | 중 — 리뷰 효율 개선, +Δ 직접 없음 |
| Thumb TBB/TBH walker | S-C | — | 중 — AArch32 corpus 미구현 시 defer |
| Zydis 2-opinion | S-D | — | 저 — telemetry 가치만 |

### 9.3 Rizin 관련 향후 분석 (backlog)

- **#30 (함수 탐지)**: `fcn.c`, `aaa` 파이프라인, `zignatures` FLIRT-like 매처
- **#32 (IL / decompile bridge)**: RzIL spec, ARM/x86 lifter 구현, `agraph` decompile 경로
- **본 문서 후속**: Rizin `elf_relocs.c` 의 AArch64 `R_AARCH64_ADR_PREL_PG_HI21` / `ADD_ABS_LO12_NC` 등 PLT/PIE relocation 처리 (AURA `relocation.c` 확장 시 참조)

---

## 10. 메타데이터

- **작성 시점**: 2026-04-20 Session #9, Phase 2-E 병렬 연구 (Task #31)
- **AURA Git HEAD at analysis time**: main branch, Pre-1 / Pre-2 / E-1 / E-2 커밋 이후
- **Rizin version referenced**: dev branch (2026-04 snapshot), `book.rizin.re` + GitHub 디렉토리 listings
- **License note**: Rizin LGPL-3 → AURA Apache-2 incompat. 본 문서의 제안은 **알고리즘 spec 참조만**; from-scratch 구현 필수.
- **재검토 주기**: Rizin major release 또는 AURA ARM corpus 확장 시점.
- **Sibling docs**:
  - `ghidra_disasm_analysis.md` (Task #27) — SLEIGH 중심 비교
  - `ghidra_func_detect_analysis.md` (Task #26) — 함수 탐지 parity
  - `ghidra_disasm_decompile_bridge_analysis.md` (Task #28) — IR lifting
  - `rizin_func_analysis.md` (Task #30, 작성 중) — `aaa` / zignatures
  - `rizin_il_bridge_analysis.md` (Task #32, 작성 중) — RzIL

---

## 11. 참조 (External, 인용 전용)

- Rizin GitHub: `rizinorg/rizin` — `librz/bin/format/{elf,pe,mach0,...}/`, `librz/arch/p/{asm,analysis}/`, `librz/arch/isa/`
- Rizin Handbook: `book.rizin.re` — Chapter 43 (Disassembling), Chapter 45 (RzIL), Chapter 48 (Code Analysis)
- radare2 legacy (Rizin 상위 호환): `radareorg/radare2` — `libr/anal/jmptbl.c`
- Issue references: rizinorg/rizin#4665 (ARM $t mapping symbol bug)
- ARM mapping symbol spec: ARM binutils `ARM-Mapping-Symbols` documentation
- AURA 로컬 대응 파일:
  - `src/parser/elf_parser.c:325` (EM_ARM/EM_AARCH64 분기, 매핑 심볼 처리 부재)
  - `src/disasm/capstone_wrapper.c:29` (DisasmContext 정의)
  - `src/core/recursive_disasm.c` (BFS work-queue)
  - `src/disasm/indirect_resolver.c` (rip-rel + vtable 2패턴)
  - `src/decompiler/switch_recovery.c` (IR chain merge)
