# Rizin 함수 탐지 + 분석 passes 재분석

> **Session #9 (2026-04-20), v2.3.0 Phase 2-B 병렬 연구 (Task #30)**
> 작성자: research teammate `rizin-func-analyst` (Team `v2-3-0-phase-2b`)
> 범위: Rizin `dev` 브랜치 (2026-04 기준) 소스 + 공식 handbook + sigdb-source/sigdb 두 저장소
> 대상 AURA: v2.3.0-rc1.1 + Phase 2-E 진행 중
> Triangulation: Ghidra analyst (#26) `ghidra_func_detect_analysis.md`, Rizin sibling (#31 disasm, #32 IL)

---

## 1. Executive Summary

Rizin 의 함수 탐지는 **4 층 엔진 + 2 종 시그니처 DB** 로 구성된다.
(1) 엔트리·심볼 기반 재귀 분석 (`rz_core_analysis_all` / `aa`),
(2) **Nucleus** 컴파일러-불가지 CFG-우선 탐지 (`aab`, Andriesse-Slowinska 논문 이식),
(3) 사용자 설정형 prelude 매칭 (`analysis.prelude` + 아키텍처 내장 pattern + `aap`),
(4) ESIL 에뮬레이션 기반 indirect call resolution + noreturn propagation (`aaaa`).
시그니처 DB 는 **IDA 호환 FLIRT** (`.pat`/`.sig`, v0.4.0 이후 default) + **zignatures** (SDB key-value, bytes + graph + refs + prototype) 을 동시 운영.

**AURA 와의 핵심 격차 top 3 (ROI 순)**:

1. **Nucleus 알고리즘 부재** — Rizin 은 Andriesse-Slowinska 의 compiler-agnostic CFG 재구성 알고리즘을 이식(`aab`). inter-/intra-procedural edge 를 구조적으로 구분 → non-contiguous / multi-entry / stripped 바이너리에서 AURA 의 prologue-only 탐지가 놓치는 함수를 복구. AURA `func_detect.c` 는 prologue pattern + CFG 후처리 의존 → stripped 바이너리 recall 천장 (cat 15.8% / ls 45.1%) 의 구조적 원인. **Recall +8~15%p 기대**.
2. **IDA 호환 FLIRT 파이프라인 부재** — Rizin sigdb 는 glibc/libstdc++/libgcc 등을 ELF/PE × 아키텍처 × bit-width 매트릭스로 공개 공급하며 `.pat` 포맷은 **byte + mask + CRC16 + 함수 길이 + 참조 심볼 tail** 구조. AURA `flirt.c` 는 자체 포맷이라 **공개 signature DB 를 전혀 재사용하지 못한다** (Ghidra FID 는 라이선스 이슈로 사실상 미공개). **명명 precision 큰 개선 + 즉시 사용 가능한 수백 MB 라이브러리 DB**.
3. **`analysis.prelude` 사용자 설정 + prelude 자동 수확 부재** — Rizin 은 (a) `e analysis.prelude=0x554889e5` 로 사용자 패턴 주입, (b) 탐지된 함수의 앞 바이트에서 pattern 을 역-추출해 재사용 (GSoC 2026 제안 단계). AURA 는 C 코드 하드-코딩만 → obfuscator / non-standard ABI 대응력 부족. **LOW 난이도, +1~2%p**.

**Ghidra analyst #26 추천과의 cross-validation**:

| #26 제안 | Rizin 이 이미 구현? | AURA 우선순위 |
|---|---|---|
| S-1 Pre-pattern 검증 gate | **❌ 없음** (Rizin 도 AURA 와 동일하게 후보만 본다) | Ghidra 고유 → 이식 유지 |
| S-4 NoReturn DB 확장 | **✅ Rizin 도 심볼명 DB + ESIL 전파** | 이식 유지, Rizin 에서 심볼 리스트 참조 |
| S-5 x86-64 PLT / PE IAT | **✅ Rizin PLT recovery 성숙** | Rizin 구현 참조 가능 (LGPL-3 알고리즘 차용) |
| M-1 XML Pattern DSL | ❌ Rizin 은 C 하드-코딩만 | Ghidra 고유 강점, M-1 유지 |
| M-3 Medium-hash FID | ❌ Rizin FLIRT 은 다른 축 | **Ghidra FID + Rizin FLIRT 이중 이식** 재고 |
| **새로 추가 권장 (Rizin 만의)** | — | **Nucleus (N-1), IDA-compat FLIRT loader (F-1), zignatures graph hash (Z-1)** |

---

## 2. Rizin 의 `aa` 시리즈 분석 pass chain 심층

### 2.1 명령어 깊이 매트릭스

[출처: Rizin Handbook §48 Code Analysis, `librz/core/canalysis.c`, `librz/core/cmd/cmd_analysis.c`]

| 명령어 | 역할 | 대표 C 함수 (Rizin) | AURA 대응 |
|---|---|---|---|
| `aa` | **Analyze all** — entry + symbol 기반 재귀 descent | `rz_core_analysis_all()` | `pipeline.c` + `func_detect.c` Phase B (call target) |
| `aab` | **Basic-block analysis (Nucleus)** — CFG-기반 함수 경계 추론 | `rz_core_analysis_basic_blocks_ex()` (+ Nucleus CFG merge) | **❌ 미구현** — AURA 의 최대 격차 |
| `aac` | Analyze function calls (from current or selected) | `rz_core_analysis_calls()` | `func_detect.c` Phase B |
| `aap` | **Prelude scan** — arch prelude bytes 전체 메모리 스캔 | `rz_core_search_preludes()` / `analysis.prelude` consumer | `func_detect.c` Phase A (하드-코딩) |
| `aar` | Analyze data references (xrefs) | `rz_core_analysis_refs()` | `xref.c`, `elf_scalar_refs.c` |
| `aad` | Pointer-to-pointer refs | `rz_core_analysis_aad_refs()` | 미구현 |
| `aaf` | Analyze all function calls (program-wide) | `rz_core_analysis_fcn_all_refs()` | `func_detect.c` Phase C + `xref.c` |
| `aae` | ESIL emulation for constant/indirect resolution | `rz_core_analysis_esil_default()` | `const_prop.c` (부분) |
| `aaef` | ESIL for all functions | `rz_core_analysis_esil_for_all_fcn()` | 미구현 |
| `aan` | Autoname functions by flags/heuristics | `rz_core_analysis_autoname_all_fcns()` | 부분 (`func_id.c` FNV-1a) |
| `aav` | Analyze values (data scan for pointers → code) | `rz_core_analysis_value_pointers()` | `address_tables.c` (부분) |
| `aas` | Analyze symbols (weak/strong binding) | `rz_core_analysis_all_symbols()` | Phase D |
| `aaz` | Analyze strings references | `rz_core_analysis_strings()` | `string_refs.c` |
| `aaaa` | = `aaa` + ESIL + noreturn propagate + FLIRT apply | *command chain* | 미구현 (chain) |

### 2.2 `rz_core_analysis_all` 소스 (핵심 발췌)

[출처: `librz/core/canalysis.c::rz_core_analysis_all`]

```c
RZ_API int rz_core_analysis_all(RzCore *core) {
    ...
    int depth = aopt->depth;  // analysis.depth 기본 64
    bool analysis_vars = rz_config_get_i(core->config, "analysis.vars");

    /* 1. Entry0 */
    item = rz_flag_get(core->flags, "entry0");
    if (item) {
        rz_core_analysis_fcn(core, item->offset, -1,
                             RZ_ANALYSIS_XREF_TYPE_NULL, depth - 1);
        rz_core_analysis_function_rename(core, item->offset, "entry0");
    }

    /* 2. 심볼 테이블 순회 (FUNC, IFUNC, loc 등) */
    rz_pvector_foreach (o->symbols, it) {
        symbol = *it;
        if (isValidSymbol(symbol)) {
            rz_core_analysis_fcn(core, addr, -1,
                                 RZ_ANALYSIS_XREF_TYPE_NULL, depth - 1);
        }
    }

    /* 3. main 심볼 (special) */
    if ((binmain = rz_bin_object_get_special_symbol(o, RZ_BIN_SPECIAL_SYMBOL_MAIN))) {
        rz_core_analysis_fcn(core, addr, -1, ...);
    }

    /* 4. 모든 entry (init, fini, preinit, tls, dynamic) */
    vector = rz_bin_object_get_entries(bin);
    rz_pvector_foreach (vector, it) { ... }

    /* 5. 변수 복구 (stack-based + reg-based) */
    if (analysis_vars) {
        rz_list_foreach_prev(fcns, iter, fcni) {
            rz_core_recover_vars(core, fcni, true);
        }
    }

    /* 6. 플랫폼 별 IO port / MMIO flag 주입 */
    rz_platform_profile_add_flag_every_io(arch_target->profile, core->flags);
    ...
}
```

**관찰**:
- **`depth - 1`**: 재귀 descent 시 depth counter 감소. `analysis.depth=64` 기본 → 64-level 재귀 호출 trace.
- **`rz_core_analysis_fcn()`** 내부는 linear sweep + recursive descent 하이브리드. 디스어셈블러가 `jmp`/`call` target 을 발견하면 대기열에 추가 (AURA Phase B/C 와 동형).
- **`rz_core_recover_vars`**: 스택 프레임 slot 분석. AURA 는 `type_inference.c` 가 유사 역할을 HIR 수준에서 수행.
- ARM Thumb-1 helper (`__gnu_thumb1_case_uqi`) 특수 처리 — 컴파일러 생성 helper 를 별도 등록해 switch table 오검출 방지.

### 2.3 `aaa` 확장 (advanced) 호출 체인

[출처: `librz/core/cmd/cmd_analysis.c` command chain + Rizin Handbook §48]

`aaa` 는 `aa` 후 다음 단계를 추가 (cmd 문자열 chain 또는 C 함수 직접 호출):

1. `rz_core_analysis_all()`  — 위 §2.2
2. **prelude scan** (`aap`) — `rz_core_search_preludes()` 가 각 arch 별 기본 prelude bytes 를 text section 전체에서 AhoCorasick 비슷한 검색으로 매칭. `analysis.prelude` config 가 세팅되어 있으면 그 값 우선.
3. **xref 재계산** (`aar`) — 데이터 섹션 포인터 스캔 → code 영역 target 발견 시 함수 후보 등록.
4. **function call 분석** (`aac`) — `call` 명령어 target 이 아직 함수로 등록되지 않았으면 신규 함수 생성.
5. **autoname** (`aan`) — FLIRT/zignature 매칭 + heuristic 이름 부여 (`fcn.xxxxxx` → `sym.imp.printf` 등).
6. **calling convention 추론** — `rz_analysis_cc_guess()` 로 ABI 판정 (cdecl, fastcall, sysvcc, ms64 등). 함수 prototype 조립.

### 2.4 `aaaa` 확장 (more aggressive)

`aaa` + 다음:

7. **ESIL emulation** (`aae`) — `rz_core_analysis_esil_default()` 가 ESIL VM 을 돌려 (a) register constant propagation → indirect call target, (b) stack slot 치환, (c) string reference 추출. AURA 는 HIR 수준 `const_prop.c` 로 부분 커버.
8. **noreturn propagation** — `rz_core_analysis_propagate_noreturn()` 가 `abort`/`exit`/`__stack_chk_fail` 등의 알려진 심볼 + ESIL-flagged 함수를 기반으로 caller 의 fall-through edge 제거. AURA analyst #26 의 S-4 제안과 정확히 부합.
9. **FLIRT 적용** (Fa / `flirt.sigdb.path`) — sigdb 의 모든 매칭 가능한 `.sig` 를 적용.
10. **type propagation** — 매칭된 함수의 prototype 에서 caller 의 인자 타입 역-전파. `aafta` 의 Dwarf 경로와 통합.

### 2.5 AURA pipeline 과의 구조적 차이

| 축 | Rizin | AURA |
|---|---|---|
| Scheduler | 단일 함수 내 순차 (`rz_core_analysis_all`) + cmd 문자열 chain | `pipeline.c` 단일 순차 |
| 재귀 깊이 | `analysis.depth=64` 제어 가능 | 하드-코딩 (재귀 없이 worklist) |
| ESIL VM | 내장 emulator, script-able | 미구현 (Capstone-only disasm) |
| 4 라운드 재-매칭 | ❌ (Ghidra 고유) | ❌ |
| Indirect call resolution | ESIL constant prop | HIR `const_prop.c` (사후) |
| Nucleus (CFG-first) | ✅ (`aab`) | **❌** |

---

## 3. Rizin function detection 메커니즘

### 3.1 Prelude pattern matching

**구현 위치**: `librz/core/csearch.c::rz_core_search_preludes()` (추정, handbook 기준)

**세 가지 경로**:

1. **사용자 설정**: `e analysis.prelude=<hex>` — 예: x86-64 System V `push rbp; mov rbp, rsp` = `0x554889e5`.
2. **아키텍처 내장**: `RzAnalysisPlugin` 각 arch 구현체 (`librz/analysis/p/analysis_x86_gas.c`, `analysis_arm_cs.c` 등) 가 prelude byte 배열을 제공.
3. **자동 수확 (연구 단계)**: GSoC 2026 제안 — 이미 탐지된 함수들의 시작 바이트를 모아 n-gram 통계로 pattern 을 역-추출 (현재 미구현).

**매칭 알고리즘**: 단순 linear scan (NAND-mask 비트레벨 와일드카드는 **미지원** — Rizin 은 고정 바이트 열만 매칭). Ghidra 의 XML DSL 비트-와일드카드 수준은 지원하지 않는다. **AURA 도 이 수준 — Rizin 모방만으로는 Ghidra 수준 도달 불가**.

**recent 개선**: "checks for jumps to function preludes by default" — `jmp <prelude-matching-address>` 탐지 시 target 을 함수 후보로 승격. AURA `func_detect.c` Phase C 의 xref 경로에 이미 유사 로직 존재.

### 3.2 Nucleus algorithm (aab) — **AURA 미구현 최대 격차**

**논문**: Andriesse, D., Slowinska, A., Bos, H. *"Compiler-Agnostic Function Detection in Binaries"*. EuroS&P 2017 (IEEE). [Semantic Scholar: 104b030480e0d5687964301a9474365220fa0c11]

**핵심 아이디어**:
1. **Linear disassembly** 로 미지 영역의 모든 byte 를 일단 명령어로 해석 (오검출 포함).
2. **Basic block 경계** 추출 — `jmp`/`call`/`ret`/conditional branch 지점.
3. **Intraprocedural edge**: 조건 분기, fall-through, 가까운 `jmp` (같은 function body 내).
4. **Interprocedural edge**: `call`, 원거리 `jmp` (tail call), `ret`.
5. **BB 를 intra edge 로만 clustering** → 각 cluster = 후보 함수.
6. **Entry point 결정**: cluster 내부에서 incoming intra-edge 가 없는 (= 다른 cluster 에서만 호출되는) BB 가 함수 시작.

**왜 강력한가**:
- **시그니처 불필요** — stripped / obfuscated / packed (post-unpack) 바이너리에서도 작동.
- **non-contiguous function** 처리 — GCC `-ffunction-sections` 나 PGO 바이너리의 분산된 code chunks 를 올바르게 하나로 묶음.
- **multi-entry function** 처리 — C++ exception unwind target, ARM Thumb/ARM 모드 전환 지점을 별도 entry 로 인식.
- **컴파일러 불가지** — MSVC/GCC/Clang/ICC/Rust/Go 모두 동일 알고리즘으로 커버.

**단점**:
- **False positive 위험**: linear disassembly 초기 단계에서 data 를 code 로 해석 → 검증 단계 필요 (Nucleus 는 cluster size + valid-opcode ratio 로 필터).
- **비용**: 전체 text section linear sweep + BB merge → O(N log N). AURA scale 에서는 허용 가능.

**AURA 이식 전략** (§5 개선 로드맵 N-1):
- `src/symbolic/nucleus.c` 신규 모듈.
- 이미 있는 `cfg.c` + `func_detect.c` 의 BB 추출 재사용.
- **Rizin `librz/analysis/fcn.c` 의 Nucleus 경로 직접 참조** (LGPL-3 — 알고리즘 차용 OK, 직접 copy-paste 만 주의).
- 기존 AURA Phase A-D 와 **OR merge**: Nucleus 가 놓친 stripped-FDE 기반 함수는 G1 이 보강, Nucleus 가 찾은 multi-entry 는 AURA candidate set 에 추가.

### 3.3 Call target iteration (recursive descent)

**`rz_core_analysis_fcn()`** 내부:
```
1. 현재 주소에서 명령어 하나 디스어셈블
2. 명령어 종류 분기:
   - call/jmp (direct): target 주소를 function queue 에 push (depth > 0 일 때)
   - jmp (indirect): ESIL 로 target 추정 (가능하면 queue 에 push)
   - ret/jmp (tail): 현재 함수 body 종료
3. BB boundary 기록
4. fall-through 와 conditional branch target 으로 continue
5. 깊이 한계 도달 또는 이미 방문 시 종료
```

**AURA 대응**: `func_detect.c` Phase B 가 동일 로직 (worklist-based). 큰 차이는 **depth 제한 부재** — AURA 는 전체 프로그램을 한 번에 처리하고 이후 `build_funclist` 로 분리. Rizin 은 per-function depth 로 폭주 방지.

### 3.4 Symbol table use

Rizin 은 `RzBinSymbol` 구조체의 `type` 필드를 기반으로:
- `RZ_BIN_TYPE_FUNC_STR` ("FUNC") → 직접 함수 생성
- `RZ_BIN_TYPE_IFUNC_STR` ("IFUNC") → GNU indirect function (`__cpu_indicator_init` 등) — 결정자 함수 + 실제 구현 양쪽 등록
- `RZ_BIN_TYPE_SECTION_STR` → skip
- PLT section → `rz_core_analysis_plt()` 별도 경로

**PLT 처리** (Rizin):
- `librz/core/cplt.c` (추정) — arch 별 PLT stub 모양 하드-코딩.
- x86/x86_64/ARM32/ARM64 모두 커버.
- GOT/PLT/IAT 연동 → thunk 이름을 `sym.imp.<name>` 으로 assign.

**AURA 현황**: `func_detect_plt.c` 가 **AArch64 만** 커버. Rizin 의 x86_64 PLT stub 패턴 (`ff 25 ?? ?? ?? ??` = `jmp qword [rip+disp32]` + `68 ?? ?? ?? ??` = `push imm32` + `e9 ?? ?? ?? ??` = `jmp rel32`) 을 **직접 이식 가능** (LGPL-3 알고리즘 차용).

### 3.5 Post-pass: aliasing, rename, xref propagation

Rizin 의 `aan` (autoname) + `aaa` 후반부:
1. **Alias detection**: 동일 byte-body 함수가 여러 주소에 노출 (weak symbol, COMDAT fold) → canonical 하나만 유지, 나머지는 alias.
2. **Heuristic rename**: `fcn.001234` → `str.chr` (string ref), `sub.dlopen` (import alias), `loc.switch_table_handler` 등.
3. **XREF propagate**: 함수 A 가 함수 B 를 호출하면 B 의 incoming xref 리스트에 A 등록. 분석 UI 가 "used by" 표시에 활용.

**AURA 대응**: `xref.c` 가 수준 1-2 만 수행. `func_id.c` 의 naming 은 FNV-1a 단일 tier — Rizin 의 FLIRT + autoname chain 에 비해 훨씬 약하다.

---

## 4. Zignatures — Rizin 의 signature DB (2 종 병행)

Rizin 은 **2 개의 독립된 signature 시스템**을 운영한다. 이 구분은 handbook 에 명확하지 않아 혼동하기 쉽다.

### 4.1 FLIRT (IDA Pro 호환, v0.4.0 이후 default)

[출처: Rizin Handbook §56 Signatures, rizinorg/sigdb, rizinorg/sigdb-source]

**포맷**:
- **`.pat`** — 사람이 읽는 text. Hex-Rays IDA 의 FLAIR toolkit 과 **호환**.
- **`.sig`** — compressed binary. name/version/architecture 메타데이터 포함.

**`.pat` 파일 구조** (IDA FLAIR spec + Rizin 파서 기준):
```
<pattern-bytes-32-hex>..<CRC16>..<length-4-hex> <tail-bytes> <func-name> <public-names-offsets>
```
- **pattern-bytes (32 bytes)**: 함수 시작 32 바이트. byte-level + 위치별 mask (`..` = 와일드카드, 주로 relocation 위치).
- **CRC16**: 첫 32 바이트 이후 N 바이트 범위의 CRC (컴파일러 생성 immediate 회피용 skip 포함).
- **length**: 함수 총 길이 (검증 필드).
- **tail bytes**: 선택 — CRC 이후 남은 고유 바이트.
- **func-name + public-names**: 이 signature 가 매칭하면 부여할 이름 + 함수 body 내에서 참조해야 하는 외부 심볼 (cross-reference 검증).

**명령어** (Rizin):
- `Fc <filename>` — 현재 분석된 바이너리에서 `.pat` 생성.
- `Fs <path>` — `.sig` 또는 `.pat` 를 현재 바이너리에 적용.
- `Fa` — sigdb 자동 적용 (모든 매칭 가능한 signature 시도).
- `Fl` — 사용 가능한 signature 목록.

**config**:
- `flirt.sigdb.path=/path/to/sigdb` — 외부 DB 경로.
- `-Dinstall_sigdb=true` meson 빌드 옵션으로 내장 설치.

**sigdb (rizinorg/sigdb) 구조**:
```
elf/<arch>/<bits>/<library>/<library>.sig
pe/<arch>/<bits>/<library>/<library>.sig
```
예: `elf/x86/64/glibc-2.39/glibc-2.39.sig`, `pe/i386/msvcrt-14.0/msvcrt-14.0.sig`.

**sigdb-source 구조**: 동일 계층 + `.pat`, `.description` (≤ 1024 chars), `.src.sha1` (원본 .a/.lib 해시 — 재생성 가능성 보장).

**매칭 알고리즘** (IDA FLIRT 논리 이식):
1. 모든 `.sig` 를 decision-tree 로 merge (byte-level trie).
2. 각 함수 시작 주소에서 trie walk → 첫 32 bytes mask-match.
3. Match 시 CRC16 범위 검증.
4. length 검증.
5. Public names (cross-references) 검증 — 이 signature 가 기대하는 외부 심볼이 실제 바이너리에 존재하는가?
6. 모든 검증 통과 → 이름 assign.

**AURA 와의 정량 차이**:
- AURA `flirt.c` (492 LOC) — 자체 포맷, **IDA `.sig`/`.pat` 읽지 못한다**.
- Rizin sigdb: 수백 MB 라이브러리 커버 (glibc, musl, libstdc++, libgcc, Windows CRT, MFC, etc.).
- **AURA 가 IDA-compat FLIRT 파서를 이식하면 즉시 수백 MB 의 공개 signature 활용 가능** (F-1 제안, §5).

### 4.2 zignatures (SDB key-value, radare2 heritage)

[출처: book.rada.re/signatures/zignatures.html + Rizin handbook §28 SDB]

**FLIRT 과 별도**의 signature 시스템. FLIRT 가 byte-level 매칭 중심이면, zignatures 는 **structural**.

**구성 요소** (각 함수 1 개의 zignature 는 여러 component 를 포함):
| Component | 내용 | Ghidra 대응 |
|---|---|---|
| `bytes` | 와일드카드 포함 byte 패턴 (`31ed4989d1..48..ff..f4`) | FID short/medium hash 의 저레벨 대응 |
| `graph` | `cc`=cyclomatic complexity, `bbs`=BB 수, `edges`=edge 수, `ebbs`=exit BB 수 | FID 에는 없는 축 |
| `refs` | 이 함수가 호출하는 외부 심볼명 리스트 | FID parent-name 검증 부분 대응 |
| `xrefs` | 이 함수를 호출하는 외부 심볼명 리스트 | BSim structural feature 와 유사 |
| `hash` | 함수 전체 CRC/SHA | FID full hash |
| `name` | 이름 | FID domain name |
| `prototype` | 함수 signature (C proto) | FID 도 포함 |
| `offset` | 원본 주소 (tracking 용) | — |

**저장 포맷**: SDB (Rizin 의 자체 key-value DB — 파일당 단일 plain-text, line-based).
```
zign|x86|64|glibc_234|printf=bytes:...|graph:cc=3,bbs=5,edges=6|refs:_dcgettext,vfprintf|prototype:int printf(const char *, ...)
```

**명령어**:
- `zaf <funcname> <signame>` — 기존 함수에서 zignature 생성.
- `zg` (= `zaF`) — 모든 함수 일괄 생성.
- `zos <file>` — SDB 파일로 저장.
- `zoz <file>` — 압축 SDB 저장.
- `zo <file>` — SDB 로드.
- `z/` — 전체 바이너리 스캔해 signature 매칭.
- `zb` — **5 closest matches + 유사도 (0.0-1.0)**. threshold-based scoring.
- `z.` — 현재 주소만.
- `zign.autoload=true` — `~/.local/share/rizin/zigns` 자동 로드.

**매칭 점수**: byte similarity (B) + graph similarity (G) 가중합. 구체 가중치는 `zign.*` config 로 튜닝 가능.

**Ghidra FID vs Rizin zignatures**:
| 축 | Ghidra FID | Rizin zignatures |
|---|---|---|
| tier 수 | 3 (short 4-unit, medium 24-unit, full body) | 1 (전체 bytes + 와일드카드) |
| 정규화 | `InstructionSkipper` per-processor (immediate mask) | 와일드카드 수동 기재 |
| graph feature | ❌ | ✅ (cc, bbs, edges, ebbs) |
| xref feature | 부분 (parent name) | ✅ (incoming + outgoing 둘 다) |
| threshold | `SCORE_THRESHOLD=14.6` (bit entropy 기준) | 사용자 조정 weighted sum |
| DB 공개 여부 | ❌ (라이선스, 사용자 빌드) | ✅ (sigdb 공개) |
| 매칭 속도 | 매우 빠름 (short-hash shortlist) | 중간 (SDB linear + graph 비교) |

**AURA 활용 가능성**:
- **zignatures graph feature** 이식 (Z-1) — HIR 이 이미 있으므로 (`cfg.c`, `hir_builder.c`) CC/BBS/edges 계산 즉시 가능. **BSim-유사 구조적 similarity 의 경량 버전** — Ghidra analyst #26 의 L-2 BSim 제안보다 10x 낮은 구현 비용.

### 4.3 Ghidra FID vs Rizin FLIRT + zignatures (3-way 비교)

| 평가 축 | Ghidra FID | Rizin FLIRT | Rizin zignatures |
|---|---|---|---|
| 주 매칭 축 | 3-tier hash | byte + CRC + length | bytes + graph + refs |
| DB 가용성 | ❌ 비공개 (사용자 빌드) | ✅ 공개 sigdb | ✅ 공개 (작음) |
| 호환성 | Ghidra 전용 | **IDA FLIRT 호환** | radare2/Rizin 전용 |
| 정규화 정밀도 | 매우 높음 (processor-specific skipper) | 중간 (relocation mask 자동) | 낮음 (수동) |
| structural | ❌ | ❌ | ✅ |
| 활용 단계 | Post-FID propagation | `aaa`/`aaaa` 후반 | 선택 (zo/z/) |

**결론**: Rizin FLIRT 은 AURA 가 **IDA 생태계의 수백 MB 공개 signature 에 즉시 접근** 할 수 있는 유일한 경로. Ghidra FID 만 이식하면 사용자가 직접 DB 빌드해야 → barrier 높음. **F-1 (FLIRT loader) 이 AURA 명명 품질 향상의 최고 ROI**.

---

## 5. Rizin vs AURA 비교표

| # | Rizin 기법 | AURA 구현 상태 | 관련 파일 | Gap |
|---|---|---|---|---|
| 1 | `rz_core_analysis_all` 엔트리·심볼 기반 재귀 | ✅ 동등 | `func_detect.c` Phase B/C | 0 |
| 2 | `analysis.depth` 제한 (기본 64) | ❌ 미구현 | — | 재귀 폭주 방지 경로 추가 고려 |
| 3 | **Nucleus (aab)** CFG-기반 | **❌ 미구현** | — | **최대 격차** (§3.2) |
| 4 | Prelude scan (`aap`) 내장 패턴 | ✅ 부분 (하드-코딩) | `func_detect.c:131-204` | 사용자 config 주입 부재 |
| 5 | `analysis.prelude` 사용자 설정 | ❌ 미구현 | — | **LOW 난이도 개선** |
| 6 | Prelude 자동 수확 (n-gram) | ❌ 미구현 (Rizin 도 연구 단계) | — | 장기 |
| 7 | 엔트리 소스: ELF e_entry | ✅ 동등 | `elf_parser.c` | 0 |
| 8 | 엔트리: .init_array/.fini_array/.preinit_array | ✅ G2 (2026-04) | `func_detect_datascan.c` | 0 |
| 9 | 엔트리: ELF IFUNC 별도 처리 | ⚠️ 부분 | Phase D | IFUNC decision stub 미인식 |
| 10 | 엔트리: ARM Thumb-1 helper 특수 처리 | ❌ 미구현 | — | Thumb 지원 미완 |
| 11 | 엔트리: main special symbol | ✅ 동등 | `entry_points.c` | 0 |
| 12 | PLT stub: AArch64 | ✅ 동등 | `func_detect_plt.c` | 0 |
| 13 | PLT stub: x86-64 (`ff 25` jmp-thru-GOT) | ❌ 미구현 | — | **LOW 난이도 이식 가능** |
| 14 | PLT stub: ARM32 | ❌ 미구현 | — | Rizin 참조 가능 |
| 15 | PE IAT stub | ❌ 미구현 | — | Rizin 참조 가능 |
| 16 | xref 분석 (`aar`) | ✅ 동등 | `xref.c`, `elf_scalar_refs.c` | 0 |
| 17 | Pointer-to-pointer refs (`aad`) | ❌ 미구현 | — | 낮은 우선순위 |
| 18 | ESIL emulation | ❌ 미구현 | — | **const_prop.c 가 HIR 단계 부분 대응** |
| 19 | ESIL 기반 indirect call 해결 | ⚠️ 부분 | `indirect_resolver.c`, `const_prop.c` | 환류 부재 |
| 20 | noreturn propagation (symbol DB + ESIL) | ⚠️ 부분 | `noreturn_detect.c` (400 LOC) | 심볼 DB 소규모 |
| 21 | Calling convention 자동 판정 | ❌ 미구현 | — | ABI 감지 |
| 22 | Variable recovery (stack slots) | ⚠️ 부분 | `type_inference.c` | HIR 수준만 |
| 23 | FLIRT (IDA 호환) | **❌ 호환 없음** | `flirt.c` (자체 포맷, 492 LOC) | **최대 명명 격차** |
| 24 | FLIRT sigdb 공개 DB 소비 | ❌ | — | F-1 이식으로 해결 |
| 25 | zignatures (SDB + graph feature) | ❌ 미구현 | — | Z-1 이식 낮은 비용 |
| 26 | zb 5-closest fuzzy match | ❌ 미구현 | — | 장기 |
| 27 | Platform profile (MMIO flag) | ❌ 미구현 | — | 임베디드 바이너리 대응 |
| 28 | 4 라운드 반복 매칭 | ❌ 미구현 | — | Ghidra 고유, Rizin 도 없음 |

**정량 요약**:
- ✅ 동등: **8 항목**
- ⚠️ 부분: **5 항목**
- ❌ 미구현: **15 항목** — 중 5 개가 high-ROI (Nucleus, `analysis.prelude`, x86-64 PLT, FLIRT IDA-compat, zignatures graph feature)

---

## 6. Rizin vs Ghidra — 같은 영역 다른 구현 비교

| 영역 | Ghidra | Rizin | 승자 / 이식 우선 |
|---|---|---|---|
| Pattern DB 확장성 | XML DSL + 비트-와일드카드 | C 하드-코딩 + `analysis.prelude` config | **Ghidra** (M-1 유지) |
| Pattern 공개 제공 | ✅ (Apache 2.0, 모든 아키텍처) | 내장 prelude 고정 | **Ghidra** |
| CFG-first 탐지 | ❌ (pattern-driven) | ✅ Nucleus (aab) | **Rizin** (N-1 이식) |
| Signature 공개 DB | ❌ FID 비공개 | ✅ FLIRT sigdb (수백 MB) | **Rizin** (F-1 이식) |
| Signature 호환성 | Ghidra 전용 | IDA 호환 | **Rizin** |
| Signature 정규화 | `InstructionSkipper` per-processor (정교) | FLIRT CRC-based | **Ghidra** (M-4 유지) |
| Structural similarity | BSim (LSH) | zignatures graph (경량) | Ghidra 정확 / Rizin 저비용 (Z-1) |
| Decompiler 통합 | P-Code + DecompilerParameterId | rz-ghidra plugin (Ghidra 재사용) | Ghidra 본격 |
| ESIL / VM | ❌ | ✅ | Rizin (L 장기) |
| 4 라운드 반복 | ✅ | ❌ | Ghidra 고유 |
| noreturn 심볼 DB | 크다 | 중간 | Ghidra (S-4 재활용, Rizin 보강) |
| 사용자 config 주입 | 제한적 (XML edit) | `analysis.*` env vars 풍부 | Rizin (UX) |

**요지**: Ghidra 는 **pattern 외연**이 강하고, Rizin 은 **CFG 알고리즘 + 공개 signature** 가 강하다. AURA 는 둘을 **조합** 해야 한다.

---

## 7. 개선 로드맵 (Ghidra analyst #26 와 cross-validate)

### 7.1 Rizin 으로부터 차용 (신규 제안)

| # | 제안 | 예상 Δ | 난이도 | 의존성 | Rizin 참조 |
|---|------|-------|--------|--------|-----------|
| **N-1** | **Nucleus CFG-first 함수 탐지** — linear sweep → BB 추출 → intra/inter edge 분류 → cluster = function. `src/symbolic/nucleus.c` 신규. 기존 `cfg.c` + `func_detect.c` 와 OR-merge. | **Recall +8~15%p** (stripped 바이너리 cat 15.8% → 30%+ 추정) | **MED** | `cfg.c` BB 추출 API 노출 필요 | `librz/analysis/fcn.c` + Andriesse 논문 |
| **F-1** | **IDA-compat FLIRT loader** — `.pat`/`.sig` 포맷 파서 + sigdb 디렉토리 스캔. 기존 `flirt.c` 를 `flirt_legacy.c` 로 rename, 신규 `flirt_ida.c` 를 primary. Build-time 옵션으로 sigdb 번들 (meson equivalent). | **명명 precision 체감 +30~50%p** (libc/libstdc++/CRT 즉시 식별) | MED-HIGH | `.pat` 파서 (~500 LOC), CRC16 검증, decision tree | Rizin `librz/signature/` + IDA FLAIR spec |
| **Z-1** | **zignatures graph feature 경량 이식** — 각 함수의 `cc`/`bbs`/`edges`/`ebbs` 계산 + SDB-like plain-text persistence. fuzzy match (weighted similarity). | 유사 함수 인식 +uncertain (bench 필요) | LOW-MED | `cfg.c` 재사용, SDB-유사 포맷 직접 C 작성 | Rizin `librz/signature/zign.c` |
| **P-1** | **x86-64 / ARM32 / PE IAT PLT stub 추가** — `func_detect_plt.c` 다중 arch 분기. | Recall on x86_64/PE +5%p | LOW | 기존 PLT 구조 확장 | Rizin `librz/core/cplt.c` |
| **C-1** | **`analysis.prelude` 사용자 config 주입** — `aura --prelude <hex>` 옵션 + 런타임 설정. obfuscator 바이너리 수동 지원. | 특수 케이스 대응 | LOW | CLI 파서 변경 | `librz/config/` analysis.prelude |
| **E-1** | **Calling convention guess** — 진입점 5 명령어에서 사용된 register 를 ABI 프로파일 (SysV x86_64 RDI/RSI/..., MS x64 RCX/RDX/...) 에 매칭. | param_id 정확도 +10%p | MED | `param_id.c` 확장 | Rizin `rz_analysis_cc_guess` |
| **D-1** | **`analysis.depth` 재귀 제한** — `func_detect.c` worklist 에 depth counter 추가. 폭주하는 함수 (call chain 1000+) 차단. | 안정성 | LOW | — | Rizin `analysis.depth=64` 기본 |

### 7.2 Ghidra analyst #26 추천 cross-validation

| #26 제안 | Rizin 현황 | 개정 의견 |
|---|---|---|
| S-1 Pre-pattern gate | **Rizin 에 없음** | Ghidra 고유 → **#26 유지 권장** |
| S-2 Prologue pair boost | Rizin 도 하드-코딩만 | #26 유지 |
| S-3 Ghidra x86-64gcc 패턴 정적 이식 | — | #26 유지 |
| S-4 NoReturn DB 확장 | **Rizin 도 심볼 DB 운영** | #26 유지 + **Rizin noreturn list 머지** 재료 추가 |
| S-5 x86-64 PLT / PE IAT | **Rizin 구현 성숙** | 🔄 **Rizin 참조로 재계획** (위 P-1) |
| S-6 Switch-table 경계 보정 | Rizin 도 부분 | #26 유지 |
| M-1 XML Pattern DSL | Rizin 없음 | Ghidra 고유 → #26 유지 |
| M-3 Medium-hash FID | Rizin FLIRT 은 다른 축 | 🔄 **F-1 (FLIRT loader) 와 병행 — 두 signature 시스템 동시 운영** |
| M-4 Per-processor InstructionSkipper | Rizin FLIRT 의 CRC 도 유사 | #26 유지 |
| M-5 PseudoDisassembler 검증 | Rizin 에 없음 | #26 유지 |
| M-6 DWARF subprogram 직접 소비 | Rizin `aafta` 가 DWARF consumer | #26 유지 |
| M-7 4 라운드 scheduler | Ghidra 고유 | #26 유지 |
| L-2 BSim HIR similarity | Rizin zignatures graph 가 경량 대응 | 🔄 **Z-1 이 경량 선행 단계**, L-2 는 후순위 |

### 7.3 Rizin + Ghidra 공통 제안 (양쪽에서 확증)

**S-4 noreturn DB 확장**은 Rizin 과 Ghidra 양쪽이 동일 방향으로 검증. **최우선 LOW-risk 작업**.

**Calling convention guess (E-1)** 는 Rizin 에만 있으나 Ghidra 도 DecompilerParameterId 로 유사 목적 달성. AURA `param_id.c` 와 중복 설계 주의.

### 7.4 AURA 고유 유지 영역

Rizin/Ghidra 둘 다 없는 영역:
- **`.eh_frame` FDE 기반 G1 탐지** — AURA 의 핵심 차별점. `func_detect_ehframe.c` 는 이 영역의 state-of-art. 유지 + 강화.
- **HIR** — 독자 IR. P-Code (Ghidra) / RzIL (Rizin) 과 trade-off. 유지.

---

## 8. 핵심 제안 top 5 상세 스펙 (구현 draft)

### 8.1 N-1: Nucleus CFG-first 함수 탐지

**대상 파일**: `src/symbolic/nucleus.c` (신규), `src/symbolic/func_detect.c` (통합 지점)

**알고리즘**:
```c
/* nucleus.c 골격 */
typedef struct {
    uint64_t start;
    uint64_t end;
    uint8_t  kind;   /* 0=fall-through, 1=cond, 2=uncond jmp, 3=call, 4=ret */
    uint64_t target; /* kind 1/2/3 일 때 */
} NucleusBB;

typedef struct {
    uint8_t  type;   /* 0=intra, 1=inter */
    size_t   from_bb;
    size_t   to_bb;
} NucleusEdge;

/* 1. Linear sweep disassembly */
int nucleus_linear_sweep(const uint8_t *text, size_t size, uint64_t base,
                         NucleusBB **out_bbs, size_t *out_count);

/* 2. Edge 분류 — call/ret/원거리 jmp 는 inter, 근거리 조건 분기 + fall-through 는 intra */
int nucleus_classify_edges(const NucleusBB *bbs, size_t n,
                           NucleusEdge **out_edges, size_t *out_count);

/* 3. Union-find on intra edges → cluster */
int nucleus_cluster(const NucleusBB *bbs, size_t n,
                    const NucleusEdge *edges, size_t m,
                    size_t **out_cluster_of_bb);

/* 4. Cluster 당 entry 결정 — incoming intra edge 0 인 BB */
int nucleus_find_entries(const NucleusBB *bbs, size_t n,
                         const size_t *cluster_of_bb,
                         uint64_t **out_entries, size_t *out_count);

/* 5. AURA CandidateSet 과 merge */
int nucleus_emit_candidates(const uint64_t *entries, size_t n,
                            CandidateSet *cs);
```

**통합**: `func_detect.c::collect_candidates()` 에 Phase E `CAND_SRC_NUCLEUS` 추가. confidence 85 (prologue pair 150 보다 낮음, symbol 100 동일 tier).

**테스트**: `tests/symbolic/test_nucleus.c` — 논문 benchmark 바이너리 샘플 (SPEC CPU2006) 에서 Andriesse 보고치 (F1 ~0.95 on stripped GCC) 재현.

**예상 LOC**: ~800 라인 (핵심 400 + 통합 200 + 테스트 200).

### 8.2 F-1: IDA-compat FLIRT loader

**대상 파일**: `src/core/flirt_ida.c` (신규), `src/core/flirt.c` → `flirt_legacy.c` rename.

**포맷 파서** (`.pat` 우선 — text, debug 용이):
```c
typedef struct {
    uint8_t  pattern[32];
    uint8_t  mask[32];       /* bit 1 = 고정, 0 = 와일드카드 */
    uint16_t crc16;
    uint16_t crc16_len;      /* CRC 대상 범위 */
    uint16_t func_len;
    char    *func_name;
    struct {
        uint16_t offset;      /* 함수 시작으로부터 */
        char    *name;        /* 예상되는 cross-ref 심볼 */
    } *public_names;
    size_t   public_count;
} FlirtPattern;

int flirt_ida_load_pat(const char *path, FlirtPattern **out, size_t *n);
int flirt_ida_load_sig(const char *path, FlirtPattern **out, size_t *n);
int flirt_ida_match(const FlirtPattern *patterns, size_t n,
                    const FuncEntry *fe, const uint8_t *body, size_t len,
                    const char **out_name);
```

**CRC16**: IDA FLAIR 는 CCITT-16 사용. 구현 단순 (≤ 50 LOC).

**Decision tree**: 32-byte prefix 의 첫 4 바이트로 O(1) bucket → bucket 내 linear scan. 대규모 sigdb 에서도 ms 단위 매칭.

**번들링 결정 필요**:
- Option A: `third_party/sigdb/` 내장 (repo 크기 급증).
- Option B: build-time 다운로드 + checksum 검증.
- **권장**: Option B — CMake `FetchContent_Declare(sigdb ...)` 유사 패턴. AURA 의 `third_party/sqlite/` 가 전례.

**라이선스**: Rizin LGPL-3, sigdb 원본 라이브러리들은 각각의 라이선스 (glibc LGPL, musl MIT, ...). FLIRT 포맷 자체는 IDA spec — 독자 파서 구현은 OK.

### 8.3 Z-1: zignatures graph feature

**대상 파일**: `src/symbolic/func_graph_sig.c` (신규), `src/symbolic/func_id.h` 확장.

```c
typedef struct {
    uint32_t cc;        /* cyclomatic complexity */
    uint32_t bbs;       /* BB count */
    uint32_t edges;     /* total edges */
    uint32_t ebbs;      /* exit BB count (ret/noreturn call terminus) */
    uint16_t call_fanout;
    uint16_t loop_depth;
} GraphSig;

int graph_sig_compute(const CfgFunction *f, GraphSig *out);
float graph_sig_similarity(const GraphSig *a, const GraphSig *b);  /* 0.0-1.0 */
```

**유사도 함수**: normalized Manhattan distance 또는 cosine. 6-dim vector.

**저장 포맷**: AURA 독자 plain-text (SDB 의존성 회피).
```
aura_zsig|x86_64|glibc-2.39|printf|cc=3|bbs=5|edges=6|ebbs=1|cfan=2|ldepth=1|crc=0xABCD
```

**활용**: `func_id.c` 의 FNV-1a 단일 tier 에 graph-tier 보조. FLIRT 매칭과 두 tier 교차 검증.

### 8.4 P-1: 다중 arch PLT stub

**대상 파일**: `src/symbolic/func_detect_plt.c` 확장.

**x86-64 ELF PLT** (System V):
```asm
; PLT[n] (16 bytes)
jmp    qword ptr [rip + GOT_offset]    ; ff 25 XX XX XX XX
push   imm32                            ; 68 XX XX XX XX
jmp    PLT[0]                           ; e9 XX XX XX XX
```
바이트 패턴: `ff 25 ?? ?? ?? ?? 68 ?? ?? ?? ?? e9 ?? ?? ?? ??` (16 bytes).

**x86-64 PE IAT stub**:
```asm
jmp    qword ptr [__imp_funcname]       ; ff 25 XX XX XX XX (RIP-relative)
```
단일 6-byte thunk. PE `.idata` section + `IMAGE_IMPORT_DESCRIPTOR` 에서 이름 매핑.

**ARM32 PLT** (Thumb or ARM):
```asm
add   ip, pc, #...                     ; e28fc600 류
add   ip, ip, #...                     ; e28cca.. 류
ldr   pc, [ip, #...]!                  ; e5bcf...
```

**구현**: 각 arch 별 `detect_plt_x86_64()`, `detect_plt_arm32()`, `detect_plt_pe_iat()` 함수. `func_detect_plt.c` 의 `emit_plt_candidates()` 가 dispatch.

**이름 매핑**: ELF `.rela.plt` + `.dynsym` (기존 AURA parser 가 파싱 중) → PLT[n] → symbol name. PE `IMAGE_IMPORT_DESCRIPTOR` → `IMAGE_THUNK_DATA` → name.

### 8.5 C-1: `analysis.prelude` 사용자 config

**대상 파일**: `src/cli/main.c` 또는 `aura.c` (CLI 파서), `src/symbolic/func_detect.c`.

**CLI**:
```
aura --prelude 55:48:89:e5 binary.elf
aura --prelude 'ff:.:.:.:48:89:e5' binary.elf  # mask 지원
aura --prelude-file patterns.txt binary.elf
```

**환경변수 fallback**: `AURA_PRELUDE=55:48:89:e5`.

**패턴 포맷** (단순):
- 콜론 구분 hex.
- `.` = 와일드카드 니블 (4 비트).
- 파일 모드: 한 줄당 하나, `#` 코멘트.

**매칭**: `func_detect.c` Phase A 에 `CAND_SRC_USER_PRELUDE=85` confidence 추가. 기존 하드-코딩 패턴과 병렬 실행.

---

## 9. Cross-reference

### 9.1 Ghidra analyst #26 와의 overlap + 상이점

**Overlap (양쪽 확증 — 최우선)**:
- S-4 noreturn DB 확장 — Ghidra + Rizin 양쪽에서 검증. **S-4 = 양쪽 문서의 공통 top-3**.
- M-3 Medium-hash FID ↔ F-1 FLIRT loader — 서로 다른 축의 signature 이나 **모두 명명 품질 격차 해소**. 병행 권장.
- M-1 XML Pattern DSL — Ghidra 고유. Rizin 에는 없음. **Ghidra 만의 강점**.

**Rizin 고유 추가**:
- N-1 Nucleus — Ghidra 에도 없는 독립 방향. 최대 recall 개선.
- F-1 FLIRT — IDA 생태계 접근.
- Z-1 zignatures graph — BSim (L-2) 의 10x 저비용 버전.

**Ghidra 고유 유지**:
- M-1 XML DSL, M-7 4-round scheduler, S-1 pre-pattern gate.

### 9.2 Rizin sibling tasks (#31, #32)

- **#31 rizin-disasm-analyst** (자매) — Rizin RzAnalysisPlugin 구조 + Capstone 래퍼 비교. 본 #30 의 §3.1 "prelude 아키텍처 내장 패턴" 은 #31 이 심화할 영역.
- **#32 rizin-il-analyst** (자매) — RzIL (Rizin Intermediate Language) vs Ghidra P-Code vs AURA HIR. 본 #30 의 Z-1 (graph feature) 은 HIR 수준이지만 L-2 BSim 레벨 유사도는 #32 가 다룰 영역.

### 9.3 AURA 내부 연계

- `src/symbolic/func_detect.c` (835 LOC) — N-1 통합 지점.
- `src/symbolic/func_id.c` (529 LOC) — F-1 (FLIRT-IDA) + Z-1 (graph sig) 이식 대상.
- `src/core/flirt.c` (492 LOC) — F-1 추진 시 `flirt_legacy.c` 로 rename.
- `src/core/noreturn_detect.c` (400 LOC) — S-4 확장 대상 (Ghidra + Rizin 리스트 머지).
- `src/symbolic/func_detect_plt.c` — P-1 다중 arch 확장.
- `src/disasm/aarch64_plt_thunks.c` — P-1 와 합병 재고 (통합 `src/symbolic/plt_detect/` 디렉토리 가능).

---

## 10. 인용 / 출처

### 10.1 Rizin 공식

- Rizin Handbook §48 Code Analysis — https://book.rizin.re/src/analysis/code_analysis.html
- Rizin Handbook §47 Data and Code Analysis — https://book.rizin.re/src/analysis/intro.html
- Rizin Handbook §56 Signatures (FLIRT) — https://book.rizin.re/src/analysis/signatures.html
- Rizin Handbook §28 SDB — https://book.rizin.re/src/basic_commands/sdb.html
- Rizin Handbook §135 Reference Card — https://book.rizin.re/src/refcard/intro.html
- rz-sign man page — https://www.mankier.com/1/rz-sign
- Rizin GSoC 2026 proposals (prelude auto-harvest) — https://rizin.re/gsoc/2026/
- Rizin v0.4.0 release notes — https://github.com/rizinorg/rizin/releases/tag/v0.4.0

### 10.2 Rizin 소스 코드

- `librz/core/canalysis.c::rz_core_analysis_all` — 본 §2.2 발췌 (검증 완료)
- `librz/core/cmd/cmd_analysis.c` — command dispatch
- `librz/analysis/fcn.c` (추정) — Nucleus 알고리즘 + recursive descent
- `librz/analysis/` — arch plugin 들 (`analysis_x86_gas.c`, `analysis_arm_cs.c` 등)
- `librz/signature/zign.c` (추정) — zignatures 저장/매칭
- `librz/signature/flirt*` (추정) — FLIRT 파서 + 매칭

### 10.3 Rizin signature DB

- rizinorg/sigdb — https://github.com/rizinorg/sigdb (compiled `.sig` 배포)
- rizinorg/sigdb-source — https://github.com/rizinorg/sigdb-source (pat 원본 + generate scripts)

### 10.4 Rizin 블로그 + 커뮤니티

- RSoC 2021 Summary (FLIRT 이식 기여) — https://rizin.re/posts/rsoc-2021-summary/
- RSoC 2025 Mark API — https://rizin.re/posts/rsoc-2025-mark-api/

### 10.5 학술 참조 (Nucleus)

- Andriesse, D., Slowinska, A., Bos, H. *"Compiler-Agnostic Function Detection in Binaries"*. IEEE EuroS&P 2017. — Semantic Scholar: 104b030480e0d5687964301a9474365220fa0c11
- PDF 사본: https://rbonichon.github.io/asi36/papers/functionboundary.pdf
- Dataset: https://github.com/CenterForSecureAndDependableSystems/FunctionBoundary

### 10.6 radare2 레거시 (Rizin 의 zignatures 기원)

- radare2 book §zignatures — https://book.rada.re/signatures/zignatures.html (포맷 + 명령어 상속)

### 10.7 AURA 내부

- `docs/research/ghidra_func_detect_analysis.md` — triangulation 대상, §7.2 cross-validation 원본
- `src/symbolic/func_detect.c` + `func_id.c` — 이식 통합 지점
- `src/core/flirt.c` — F-1 대상
- `Tasks_archive/v1_1.md` V1.1-3 — G1~G5 재활성화 실험

---

## 11. TODO / Open questions

1. **Nucleus 라이선스 준수** — LGPL-3 알고리즘은 차용 OK. 구체 구현을 Rizin 소스에서 copy-paste 하면 LGPL-3 전파 → AURA Apache 2.0 와 충돌. **scratch 재구현 필수**. 논문만 참조해 독자 작성.
2. **FLIRT sigdb 번들링 결정** — third_party 내장 vs build-time 다운로드 vs runtime 수동 지정. 번들 크기 (수백 MB) 가 AURA git repo 에 부담.
3. **IDA FLIRT `.sig` 포맷 정확성** — IDA FLAIR 공식 spec 은 SDK 에 포함, Rizin 구현이 100% 호환은 아닐 수 있음. Rizin 소스 확인 필요.
4. **Nucleus precision trade-off** — Andriesse 논문은 F1 ~0.95 on SPEC CPU2006 stripped GCC. AURA 의 AArch64 stripped 바이너리에서 동일 재현 여부는 실험 필요. cat/ls/aura-self 벤치 재측정 필수.
5. **zignatures graph feature 벤치 baseline** — cc/bbs/edges 유사도 threshold 0.8 이 실제 libc 함수 매칭에 충분한지 미확정. 실험 필요.
6. **ESIL VM 이식 가치** — Rizin ESIL 은 대공사 (수천 LOC). AURA 가 이미 HIR const_prop 으로 부분 대응 중. **단기 이식 비권장** — L 장기 후보.
7. **Calling convention guess precision** — x86_64 에서 SysV vs MS ABI 는 register 사용 패턴만으로 구분 가능하나, fastcall 변종 / Rust `extern "C"` / Swift calling convention 등 엣지 케이스 많음.
8. **Rizin `aab` Nucleus 의 Rizin 내부 개선 사항** — 원 논문 대비 Rizin 의 production 구현이 추가 휴리스틱을 얼마나 가졌는지 소스 정독 필요 (본 문서는 논문 수준만 분석).
9. **rz-ghidra plugin** — Rizin 이 Ghidra decompiler 를 plugin 으로 통합. AURA 는 자체 HIR — rz-ghidra 수준의 "외부 의존" 경로는 현재 AURA 원칙 (PRD §3 커스텀 구현 우선) 에 위배. **reference only**.

---

**문서 종료**. 다음 세션 착수 추천 순서:

**단기**: **S-4 (noreturn DB, Ghidra+Rizin 공통 확증)** → **P-1 (x86-64 PLT 확장)** → **C-1 (analysis.prelude CLI)**.
**중기**: **F-1 (IDA-compat FLIRT loader, +명명 30~50%p)** → **N-1 (Nucleus, +recall 8~15%p)** → **Z-1 (zignatures graph)**.
**장기**: L-2 BSim, ESIL VM 이식 재검토.

Ghidra analyst #26 의 S-1/M-1/M-5 와 본 문서의 N-1/F-1 을 **병행 추진 가능** (의존성 없음). 두 문서 통합 시 AURA recall ~80% → ~95%, precision ~94% → ~97%, 명명 품질 대폭 개선 예상.
