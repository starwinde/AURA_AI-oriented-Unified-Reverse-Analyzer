# AURA func_detect vs Ghidra / Rizin / x64dbg — 비교 분석 + 개선 로드맵

> **Task #41, Session #9, v2.3.0 Phase 2-B compare-1.**
> 입력 연구 doc: `ghidra_func_detect_analysis.md` (#26), `rizin_func_detect_analysis.md` (#30), `x64dbg_analysis.md` (#33) — §3 pattern scan 부분만.
> 대상 AURA: v2.3.0-rc1.1 (Phase 2-E 진행 중).
> 작성 원칙: implementation-ready (파일/line/API 명시, vague 제안 금지). 코드 read-only. commit 금지.

---

## 1. AURA 현재 구현

### 1.1 `src/symbolic/func_detect.c` 구조 (835 LOC)

- **`collect_candidates()`** (`func_detect.c:231-465`): 단일 패스로 6 phase 실행.
  - **Phase A** (`func_detect.c:248-305`) — prologue pattern scan (x86/AArch64/ARM32 하드-코딩 C 함수).
    - x86: `is_push_rbp()` / `is_mov_rbp_rsp()` / `is_sub_rsp()` (`func_detect.c:131-154`).
    - AArch64: `is_aarch64_stp_fp_lr()` / `is_aarch64_sub_sp()` / `is_aarch64_str_lr()` (`func_detect.c:161-182`).
    - ARM32: `is_arm32_push_lr()` / `is_arm32_stmdb_lr()` (`func_detect.c:188-204`).
  - **Phase B** (`func_detect.c:307-330`) — 직접 call/bl/jal 타겟을 후보로 승격. self-ref (`target == insn.address`) 차단으로 ET_REL `.o` 의 unresolved `bl` (R_AARCH64_CALL26 addend=0) 회귀 방지.
  - **Phase C** (`func_detect.c:332-346`) — Xref CALL 타겟 (`xref_build()` 결과).
  - **Phase D** (`func_detect.c:348-364`) — 심볼 테이블 `AURA_SYM_FUNCTION`.
  - **Phase E (=G1)** (`func_detect.c:393-395`) — `fd_ehframe_add_candidates()` .eh_frame FDE. F-1-F FDE pc_end heuristic 는 AArch64-only gate (`func_detect.c:400-408`).
  - **Phase F-0-C-2** (`func_detect.c:416`) — `fd_plt_add_candidates()` — **AArch64 ELF 전용** PLT stub (adrp+ldr+br x17 고정 패턴).
  - **Phase F (=G2)** (`func_detect.c:425-427`) — `fd_datascan_add_candidates()` .init_array/.fini_array/.preinit_array (text_data=NULL 로 G3 비활성).
- **G3 (.rodata/.data fptr), G4 (gap fill), G5 (post-ret)** — 모두 **#if 0 비활성** (`func_detect.c:431-461`). Round 3 벤치에서 Precision 0.39 까지 떨어져 retire 됨.
- **Confidence tier** (`func_detect_internal.h:43-53`):
  `FDE 240 > FDE_END 230 > SYMBOL_SIZED 200 > CALL 180 > PLT 175 > XREF 170 > SYMBOL_UNSIZED 160 > PROLOGUE_PUSH_MOV 80 > PROLOGUE_PUSH 60 > DATA 40 > GAP 30`.
- **`func_detect()`** smart default (`func_detect.c:723-732`): 심볼 있으면 `min_confidence=100` (prologue-only 제거), 없으면 `0`.

### 1.2 `src/symbolic/func_id.c` (529 LOC)

- FNV-1a **single-tier** prologue hash (`func_id.c:160-171`). MAX 64 bytes.
- Per-arch immediate mask:
  - x86: B8-BF/68/E8/E9/0F8x/81 imm32 → 0x00 (`func_id.c:65-92`).
  - AArch64: ADRP imm21, B/BL imm26, ADD/SUB imm12, LDR/STR imm12, MOVZ/MOVK/MOVN imm16 (`func_id.c:94-135`).
- Built-in DB: **12 엔트리** (memcpy/memset/strlen/strcmp/_start/strcpy/memmove/memcmp/strncpy/atoi/puts, x86_64 only) (`func_id.c:219-305`).

### 1.3 `src/core/flirt.c` (492 LOC)

- **자체 format** — IDA `.pat`/`.sig` 비호환. Rizin sigdb 수백 MB 재사용 불가.

### 1.4 `src/core/noreturn_detect.c` (400 LOC)

- Builtin name DB ~50 이름 (exit/abort/__assert_fail/longjmp/pthread_exit 등) (`noreturn_detect.c:83-`).
- 심볼 테이블 매칭 후 call site 기록. **CFG edge 제거 / 뒤 함수 경계 승격 미구현**.

### 1.5 현재 성능

- AArch64 stripped: **Recall 80.5% / Precision 93.6% / F1 0.866**.
- 실 바이너리 3-binary (cat 15.8% / ls 45.1% / aura-self 87.6%) — `covered_avg 55` structural ceiling (MEMORY `project_real_binary_parity_2026_04_18.md`).

### 1.6 한계 지점 (explicit)

1. **단일 패스** — Ghidra 의 4-round 재-매칭 없음. data/xref 확정 후 재검증 루프 부재.
2. **pattern 외부화 제로** — 새 ABI/compiler 지원 시 C 재컴파일 필요.
3. **pre-context 검증 없음** — prologue 후보의 바로 앞 바이트가 ret/nop/defined 인지 확인 안 함.
4. **FID 단일 tier** — Ghidra 의 3-tier (short/medium/full) + InstructionSkipper 대비 정밀도 부족.
5. **FLIRT incompat** — 공개 signature 재사용 불가.
6. **CFG-first 탐지 없음** — Nucleus / Andriesse algorithm 부재 → stripped 바이너리 recall 천장.
7. **PLT 다중 arch 미지원** — AArch64 ELF 만. x86-64 PLT / ARM32 PLT / PE IAT 미구현.
8. **사용자 pattern 주입 없음** — `analysis.prelude` 등가 CLI 옵션 부재.
9. **noreturn 결과 소비 약함** — call site 기록만, 뒤 경계 승격 안 됨.
10. **test 구조 분산** — `tests/symbolic/test_func_detect.c` 통합 파일 없음. datascan/ehframe/gap/plt 개별 테스트만 (`tests/symbolic/test_func_detect_*.c` 5 개).

---

## 2. 외부 tool 격차 매트릭스

| # | 기법 | Ghidra | Rizin | x64dbg | AURA | Gap | 예상 Δ (F1) |
|---|------|:------:|:-----:|:------:|:----:|-----|-------------|
| 1 | Entry: ELF e_entry | ✅ | ✅ | n/a | ✅ | 0 | — |
| 2 | Entry: .init_array/.fini_array | ✅ | ✅ | n/a | ✅ (G2) | 0 | — |
| 3 | Entry: Mach-O LC_FUNCTION_STARTS | ✅ | ⚠️ | n/a | ⚠️ | MED | — |
| 4 | Entry: DWARF subprogram | ✅ | ✅ (aafta) | n/a | ⚠️ (타입만) | **MED** | +0.02~0.05 (unstripped) |
| 5 | Prologue: x86/AArch64/ARM32 | ✅ | ✅ | ✅ | ✅ | 0 | — |
| 6 | **Pre-pattern 검증 (after="defined")** | ✅ | ❌ | ❌ | ❌ | **HIGH** (FP 주범) | **+0.02~0.04 (P)** |
| 7 | Prologue pair boost (2-3 insn 연쇄) | ✅ | ⚠️ | ❌ | ⚠️ (부분, PUSH_MOV 만) | LOW | +0.01 |
| 8 | Pattern: XML/외부 DSL 로드 | ✅ | ❌ | ❌ | ❌ | HIGH | +0.02~0.03 (R) |
| 9 | Pattern: byte-mask primitive | ✅ (bit) | ✅ (bytes) | ✅ (nibble) | ❌ | **MED** (foundation) | +0 단독 / enabler |
| 10 | Pattern: 비트-레벨 와일드카드 | ✅ | ❌ | ❌ (nibble만) | ❌ | MED (long-term) | — |
| 11 | Pattern: 사용자 prelude 주입 | ⚠️ (XML edit) | ✅ (analysis.prelude) | ✅ (CLI) | ❌ | **LOW** | +0 편의 |
| 12 | PLT: AArch64 ELF | ✅ | ✅ | n/a | ✅ | 0 | — |
| 13 | **PLT: x86-64 ELF (ff 25 / 68 / e9)** | ✅ | ✅ | n/a | ❌ | **LOW** | +0.03~0.05 on x86_64 |
| 14 | **PLT: PE IAT (ff 25 RIP-rel)** | ✅ | ✅ | n/a | ❌ | **LOW** | +0.05 on Windows PE |
| 15 | PLT: ARM32 | ✅ | ✅ | n/a | ❌ | MED | +0.02 on ARM32 |
| 16 | Call target (direct + xref) | ✅ | ✅ | n/a | ✅ | 0 | — |
| 17 | Indirect call constant-prop 환류 | ✅ | ✅ (ESIL) | n/a | ⚠️ (HIR only) | MED | +0.01~0.02 |
| 18 | **.eh_frame FDE (Ghidra 에 없음)** | ❌ | ❌ | n/a | ✅ **AURA 차별점** | — | (유지) |
| 19 | FID: short hash (4 units) | ✅ | n/a | n/a | ⚠️ (단일 tier, 64 bytes) | MED | +naming |
| 20 | **FID: medium hash (24 units body)** | ✅ | n/a | n/a | ❌ | **MED-HIGH** | +0.01 (rename cascade) |
| 21 | InstructionSkipper per-processor | ✅ | ⚠️ | n/a | ⚠️ (arch mask) | MED | +FID stability |
| 22 | **FLIRT IDA `.pat`/`.sig` 호환** | ❌ | ✅ | n/a | ❌ (자체) | **HIGH** | +naming 30~50%p |
| 23 | FLIRT 공개 sigdb 소비 | ❌ | ✅ | n/a | ❌ | HIGH | (F-1 의존) |
| 24 | zignatures graph (cc/bbs/edges) | ❌ (BSim 별도) | ✅ | n/a | ❌ | LOW-MED | +uncertain |
| 25 | **Nucleus CFG-first (Andriesse)** | ❌ | ✅ | n/a | ❌ | **HIGH** | **+0.08~0.15 (R, stripped)** |
| 26 | NoReturn 심볼 DB | ✅ (크다) | ✅ (중간) | n/a | ⚠️ (~50) | LOW | +0.01~0.02 |
| 27 | NoReturn CFG edge 제거 + 뒤 경계 승격 | ✅ | ✅ | n/a | ❌ | MED | +0.01 |
| 28 | PseudoDisassembler trial-decode 검증 | ✅ | ❌ | ❌ | ❌ | MED | +0.02~0.03 (P) |
| 29 | Switch-table 경계 보정 환류 | ✅ (pattern DB) | ⚠️ | n/a | ⚠️ (switch_recovery 있음, 미환류) | MED | +0.01~0.02 (P) |
| 30 | ContextBuilder (Thumb/CPSR) | ✅ | ✅ | n/a | ❌ | MED | Thumb 바이너리 한정 |
| 31 | 4-round 반복 scheduler | ✅ | ❌ | n/a | ❌ | HIGH | +0.01~0.02 |
| 32 | Symbol server (PDB MS symbol store) | ⚠️ | ❌ | ✅ | ❌ | LOW | Windows 한정 |
| 33 | `analysis.depth` 재귀 제한 | ✅ | ✅ | n/a | ❌ | LOW | 안정성 |

**Cross-validation**: S-4 (noreturn DB) 는 **Ghidra + Rizin 양쪽 확증** (최우선 LOW risk). Byte-mask pattern primitive 는 **세 도구 공통 foundation** — AURA 도입 정당성 강화.

---

## 3. 개선 항목 (단기 / 중기 / 장기)

**ID 규약**: 접두가 출처를 나타낸다. G = Ghidra (#26), R = Rizin (#30), X = x64dbg (#33), H = hybrid (복수 확증).

### 3.1 단기 (1-3 세션, v2.3.0 Phase 2-F ~ v2.4.0, LOW-MED 난이도)

| ID | 제안 | 예상 Δ | 세션 | 확증 |
|----|------|-------|------|------|
| **H-S1** | NoReturn DB 확장 + CFG 환류 | F1 +0.01~0.02, P +0.005 | 1 | 2/3 (#26 S-4 + #30 E/noreturn) |
| **G-S1** | Pre-pattern 검증 gate | **P +0.03~0.05** | 1 | 1/3 (#26 S-1 고유) |
| **G-S2** | Prologue pair boost (3-insn 연쇄) | P +0.01~0.02 | 1 | 1/3 (#26 S-2) |
| **X-S1** | `PatternByte{data,mask}` primitive 이식 | +0 단독 (enabler) | 1 | 3/3 (foundation) |
| **R-P1** | x86-64 PLT stub 감지 (`ff 25 / 68 / e9` 16-byte) | R on x86_64 **+0.03~0.05** | 1 | 2/3 (#26 S-5 + #30 P-1) |
| **R-P2** | PE IAT stub 감지 (`ff 25` 6-byte thunk) | R on Windows **+0.05** | 1 | 2/3 (#26 S-5 + #30 P-1) |
| **R-C1** | `--prelude <hex>` CLI config 주입 | obfuscator 대응 편의 | 1 | 2/3 (#30 C-1 + #33 S-x-1) |
| **R-D1** | Worklist depth counter (폭주 방지) | 안정성 | 0.5 | 1/3 (#30 D-1) |

### 3.2 중기 (3-6 세션, v2.4.x ~ v2.5.0, MED-HIGH 난이도)

| ID | 제안 | 예상 Δ | 세션 | 확증 |
|----|------|-------|------|------|
| **R-N1** | **Nucleus CFG-first 함수 탐지** (clean-room, LGPL 회피) | **R +0.08~0.15 (stripped)** | 3-4 | 1/3 (#30 N-1) |
| **R-F1** | IDA-compat FLIRT loader (`.pat`/`.sig` 파서 + CRC16) | **naming +30~50%p** | 3-4 | 1/3 (#30 F-1) |
| **G-M1** | XML pattern DSL 로더 (X-S1 기반 + 비트 와일드카드) | R +0.02~0.03 | 2-3 | 1/3 (#26 M-1) |
| **G-M2** | Ghidra pattern DB 이식 (x86-64gcc/win + AARCH64_LE/win) | R +0.03~0.05 (G-M1 후) | 1 | 1/3 (#26 M-2) |
| **G-M3** | Medium-hash FID (24 code-unit body, flow 추적) | naming +10%p | 2-3 | 1/3 (#26 M-3) |
| **G-M4** | Per-processor InstructionSkipper | FID stability +20% | 2 | 1/3 (#26 M-4) |
| **G-M5** | PseudoDisassembler trial-decode validation | P +0.02~0.03 | 2 | 1/3 (#26 M-5) |
| **G-M6** | DWARF `DW_TAG_subprogram` 경계 소비 | R +0.05 (unstripped) | 2 | 1/3 (#26 M-6) |
| **G-S3** | Ghidra x86-64gcc 패턴 static 이식 (G-M1 없이 먼저 일부) | R +0.01~0.02 | 1 | 1/3 (#26 S-3) |
| **R-Z1** | zignatures graph feature (cc/bbs/edges/ebbs/cfan/loop) | uncertain (bench 필요) | 2 | 1/3 (#30 Z-1) |
| **R-E1** | Calling convention guess (`param_id.c` 확장) | param_id +10%p | 2-3 | 1/3 (#30 E-1) |
| **G-S6** | Switch-table 경계 환류 (`switch_recovery.c` → `func_detect`) | P +0.01~0.02 | 2 | 1/3 (#26 S-6) |

### 3.3 장기 (6+ 세션, v3.x, HIGH 난이도)

| ID | 제안 | 예상 Δ | 확증 |
|----|------|-------|------|
| G-M7 | 4-round 반복 scheduler | R +0.01~0.02 | 1/3 (#26 M-7) |
| G-L1 | `aura-fidb-build` CLI (`.a`/`.lib` → AURA FID DB) | naming 돌파 | 1/3 (#26 L-1) |
| G-L2 | BSim-유사 HIR structural similarity (R-Z1 확장판) | fuzzing/malware | 1/3 (#26 L-2) |
| R-L1 | ESIL-유사 VM 이식 (indirect call resolution) | R +uncertain | 1/3 (#30 ESIL) |
| G-L5 | Go pclntab / Rust `__rust_*` / Swift metadata | 언어 특화 +20%p | 1/3 (#26 L-5) |

---

## 4. 단기 top-5 상세 spec (implementation-ready)

아래 5 항목은 §3.1 단기 중 **H-S1 / G-S1 / G-S2 / R-P1 / R-C1** 을 우선 선택.
근거: 모두 1 세션 규모, 기존 파일 편집 위주, TDD RED 테스트 설계 가능, 누적 F1 +0.04~0.07 예상.

---

### 4.1 H-S1 — NoReturn DB 확장 + CFG 환류

- **Priority**: 단기 (최우선 — 양쪽 확증).
- **예상 Δ**: F1 +0.01~0.02, P +0.005, R +0.01 (noreturn 뒤 경계 승격).
- **수정 파일**:
  - `src/core/noreturn_detect.c:83-` — builtin names 배열을 ~50 → ~120 으로 확장.
  - `src/core/noreturn_detect.c` — 신규 함수 `noreturn_detect_emit_boundaries()` 추가 (post-pass).
  - `include/noreturn_detect.h` — 신규 함수 prototype 공개.
  - `src/core/pipeline.c` (추정, grep 확인 필요) — `func_detect` 이후 `noreturn_detect_emit_boundaries()` 호출 훅.
  - `src/symbolic/func_detect.c:393-427` Phase E 직후에 추가 훅 지점 가능 (alternative).
- **신규 자료구조**:
  ```c
  /* noreturn_detect.h */
  typedef struct {
      AuraAddr  post_ret_addr;   /* noreturn call 다음 aligned 주소 */
      AuraAddr  noreturn_func;   /* 호출된 noreturn 함수 */
      uint8_t   confidence;      /* CAND_CONF_NORETURN_BOUNDARY = 90 제안 */
  } NoreturnBoundary;

  uint32_t noreturn_detect_emit_boundaries(
      const NoreturnResult *nr,
      const DisasmResult *insns, size_t count,
      CandidateSet *out);
  ```
- **Builtin name 확장 리스트** (병합):
  - glibc/musl: `__assert_fail`, `__stack_chk_fail`, `longjmp`, `_longjmp`, `siglongjmp`, `pthread_exit`, `quick_exit`, `__libc_start_main_impl` (일부는 기존).
  - libstdc++: `__cxa_throw`, `__cxa_rethrow`, `_Unwind_Resume`, `__cxa_bad_typeid`, `__cxa_bad_cast`, `_ZSt17__throw_bad_allocv`, `_ZSt20__throw_length_errorPKc`, `_ZSt16__throw_bad_castv`, `_ZSt19__throw_logic_errorPKc`.
  - Rust: `rust_panic`, `__rust_start_panic`, (prefix match) `_ZN4core9panicking5panic`, `_ZN3std9panicking20rust_panic_with_hook`.
  - Go: `runtime.goexit`, `runtime.throw`, `runtime.gopanic`, `runtime.fatalthrow`.
  - Windows CRT / PE: `_invalid_parameter_noinfo_noreturn`, `_CxxThrowException`, `ExitProcess`, `TerminateProcess`, `RaiseException`, `FatalExit`, `__fastfail`.
- **TDD RED 구조**:
  - `tests/core/test_noreturn_detect.c` (신규 또는 기존 연장) — fixture ELF 에 `call __stack_chk_fail; <aligned addr>` 패턴, `noreturn_detect_emit_boundaries()` 가 aligned addr 을 후보로 방출하는지 assert.
  - RED: 호출 시점에 결과 `count==0` → 구현 후 `count==1` & `confidence==90` & `post_ret_addr` 정확.
- **예상 commit 수**: 3 (DB 확장 / emit API 구현 / pipeline 훅).
- **세션 estimate**: 1.
- **의존성**: 없음.
- **인용**: #26 §5.1 S-4 + §6.2 / #30 §7.3 (S-4 공통 확증).

---

### 4.2 G-S1 — Pre-pattern 검증 gate

- **Priority**: 단기 (Ghidra 고유, FP 주범 차단).
- **예상 Δ**: P +0.03~0.05 (post-ret noise + alignment pad 뒤 오검출 차단), R -0 (prolog 후보에만 영향, FDE/SYMBOL confidence 는 120+ 로 영향 없음).
- **수정 파일**:
  - `src/symbolic/func_detect.c` — 신규 static 함수 `pre_pattern_is_code_end(const DisasmResult *prev, AuraArch arch)` 약 L200 부근 (trim_op 뒤, collect_candidates 앞).
  - `src/symbolic/func_detect.c:254-305` Phase A — 각 prologue match 지점에서 `i > 0 ? &insns[i-1] : NULL` 을 넘겨 호출, false 시 confidence -30 (또는 candidateset_add 생략). `.eh_frame`/symbol 후보 (Phase D/E) 는 영향 없음.
- **구현 스케치**:
  ```c
  static int pre_pattern_is_code_end(const DisasmResult *prev, AuraArch arch)
  {
      if (!prev) return 1;  /* 섹션 시작 = 허용 */
      const char *mn = prev->mnemonic;
      if (strcmp(mn, "ret")  == 0) return 1;
      if (strcmp(mn, "retab") == 0) return 1;
      if (strcmp(mn, "ud2")  == 0) return 1;
      if (strcmp(mn, "int3") == 0) return 1;
      if (strcmp(mn, "brk")  == 0) return 1;
      if (strcmp(mn, "hlt")  == 0) return 1;
      if (strcmp(mn, "nop")  == 0) return 1;
      if (arch == AURA_ARCH_X86_64 &&
          strcmp(mn, "jmp") == 0) return 1;  /* tail jmp */
      if (arch == AURA_ARCH_ARM64 &&
          strcmp(mn, "b") == 0) return 1;    /* tail b */
      if (strcmp(mn, "bx") == 0 && strstr(prev->operand, "lr")) return 1;
      if (strcmp(mn, "pop") == 0 && strstr(prev->operand, "pc")) return 1;
      return 0;
  }
  ```
- **TDD RED 구조**:
  - `tests/symbolic/test_func_detect_pre_pattern.c` (신규) — in-memory `DisasmResult[]` fixture 두 개: (a) `ret` 뒤에 prologue → candidate 수락. (b) random instruction 뒤 prologue → candidate 거부 / confidence 감소.
  - 현재 `tests/symbolic/` 에 `test_func_detect.c` 통합 파일이 없어 (5 개 분산), 신규 파일이 자연스러움.
- **예상 commit 수**: 2 (helper + Phase A 적용).
- **세션 estimate**: 1.
- **의존성**: 없음.
- **인용**: #26 §5.1 S-1 + §6.1.

---

### 4.3 G-S2 — Prologue pair boost (3-insn 연쇄 강화)

- **Priority**: 단기.
- **예상 Δ**: P +0.01~0.02 (PROLOGUE_PUSH 60 이 min_confidence=100 에 걸리지 않던 FP 후보를 상향 → 통과, FP 대신 TP 가 오는 조건일 때).
  - 단독 이득은 제한적. G-S1 결합 시 상승.
- **수정 파일**:
  - `src/symbolic/func_detect.c:254-305` Phase A — 현재 2-insn 매치 (`push rbp + mov rbp, rsp`) 만 PUSH_MOV (80) tier. 3-insn 연쇄 (`push rbp + mov rbp, rsp + sub rsp, N`) 를 신규 `CAND_CONF_PROLOGUE_TRIPLE = 120` 으로 승격.
  - `src/symbolic/func_detect_internal.h:50-52` — 신규 상수 `CAND_CONF_PROLOGUE_TRIPLE 120` 추가. PUSH_MOV 와 CALL 사이.
- **구현 스케치**:
  ```c
  /* x86_64: push rbp + mov rbp,rsp + sub rsp,N */
  if (is_push_rbp(cur) &&
      i + 2 < count &&
      is_mov_rbp_rsp(&insns[i+1]) &&
      is_sub_rsp(&insns[i+2])) {
      candidateset_add(out, cur->address, CAND_SRC_PROLOGUE,
                       CAND_CONF_PROLOGUE_TRIPLE, 0);
      continue;
  }
  /* AArch64: stp x29,x30 + mov x29,sp */
  if (is_aarch64_stp_fp_lr(cur) &&
      i + 1 < count &&
      is_aarch64_mov_fp_sp(&insns[i+1])) {  /* 신규 helper */
      /* TRIPLE 등급 승격 */
  }
  ```
- **TDD RED**: `tests/symbolic/test_func_detect_prologue.c` (신규) — 3-insn fixture 가 confidence 120 으로 등록되는지 assert.
- **예상 commit 수**: 2 (상수 + 패턴).
- **세션 estimate**: 0.5-1.
- **의존성**: 없음 (G-S1 과 독립).
- **인용**: #26 §5.1 S-2.

---

### 4.4 R-P1 — x86-64 PLT stub 감지

- **Priority**: 단기.
- **예상 Δ**: R on x86_64 stripped binaries **+0.03~0.05** (cat/ls 등 외부 함수 비율 높은 소형 바이너리에서 체감 큼).
- **수정 파일**:
  - `src/symbolic/func_detect_plt.c` — 현재 88 LOC, AArch64 분기만 존재. `detect_plt_x86_64_elf()` 신규 함수 추가.
  - `src/symbolic/func_detect_plt.c` — 기존 `fd_plt_add_candidates()` dispatch 를 arch 로 분기 (`fi->arch == AURA_ARCH_X86_64` → x86-64 경로).
  - 재명명 권장: `func_detect_plt.c` 가 arch-agnostic dispatcher 가 되므로 내부 helper 를 `plt_aarch64.c` / `plt_x86_64.c` 로 분할 (LOW: 현 88 LOC 이면 단일 파일 유지도 OK).
- **패턴 스펙** (SysV x86-64 ELF PLT entry, 16 bytes aligned):
  ```
  FF 25 xx xx xx xx     ; jmp qword ptr [rip + GOT_offset]   (6 bytes)
  68 xx xx xx xx        ; push imm32                         (5 bytes)
  E9 xx xx xx xx        ; jmp rel32 (PLT[0])                 (5 bytes)
  ```
  - PLT[0] (resolver) 는 `ff 35 / ff 25 / 00 00 00 00` 첫 엔트리, 이후 16-byte stride.
  - `.plt.sec`/`.plt.got` 변종 존재 (lazy vs BIND_NOW) — 최소 `.plt` 부터 커버.
- **신규 자료구조**: 없음 (기존 `CandidateSet` 재사용, `CAND_SRC_PLT` + `CAND_CONF_PLT=175`).
- **심볼 이름 매핑**: ELF `.rela.plt` + `.dynsym` 파싱은 AURA 이미 구현 (`src/parser/elf_parser.c` 에 relocation table 있음). PLT[n] index → `.rela.plt[n].r_info` symbol index → `.dynsym[i].st_name`. 이름은 `FuncEntry.name` 에 `sym.imp.<name>` 프리픽스로 저장 (Rizin 규칙).
- **TDD RED**:
  - Fixture: `tests/fixtures/x86_64_plt.elf` 신규 (작은 C 프로그램 `int main() { puts("hi"); return 0; }` 을 `gcc -no-pie -fno-stack-protector` 로 빌드 + strip).
  - `tests/symbolic/test_func_detect_plt.c` 에 x86_64 case 추가 — PLT entry 갯수 = `.rela.plt` count 와 일치, 각 entry 의 name resolved.
- **예상 commit 수**: 3 (fixture + 감지기 + 테스트).
- **세션 estimate**: 1.
- **의존성**: ELF relocation parser (기존, 확인만 필요).
- **인용**: #26 §5.1 S-5 + #30 §8.4 P-1.

---

### 4.5 R-C1 — `--prelude <hex>` CLI config 주입

- **Priority**: 단기 (LOW 난이도, 편의).
- **예상 Δ**: F1 +0 (baseline). obfuscator / non-standard ABI 바이너리에서 사용자 수동 지원 가능.
- **수정 파일**:
  - `src/cli/` 또는 `src/core/cli_main.c` (grep 확인 필요) — argparse 에 `--prelude <hex>` / `--prelude-file <path>` 옵션 추가.
  - `src/symbolic/func_detect.c` — 신규 `FuncDetectOptions` 필드 `user_preludes` + `user_prelude_count`.
  - `include/func_detect.h` — `FuncDetectOptions` 구조체 확장.
  - `src/symbolic/func_detect.c:248-305` Phase A — hard-coded patterns 루프 후에 user prelude 매칭 루프 추가.
- **신규 자료구조**:
  ```c
  /* include/func_detect.h */
  typedef struct {
      uint8_t  bytes[32];
      uint8_t  mask[32];    /* 0xFF=고정, 0x00=와일드카드 (X-S1 PatternByte 와 동일) */
      uint8_t  len;
  } AuraUserPrelude;

  typedef struct {
      uint8_t              min_confidence;
      const AuraUserPrelude *user_preludes;
      size_t                user_prelude_count;
  } FuncDetectOptions;
  ```
- **텍스트 포맷** (X-S1 `patternfind.c` 포팅과 정합):
  - 콜론/공백 구분 hex: `55:48:89:e5` 또는 `55 48 89 e5`.
  - 바이트 와일드카드: `??`.
  - 니블 와일드카드: `4?` (상위 니블만 매칭).
- **환경변수 fallback**: `AURA_PRELUDE=55:48:89:e5`.
- **신규 API**:
  ```c
  int aura_user_prelude_parse(const char *text,
                              AuraUserPrelude *out);  /* 0 = OK */
  ```
- **TDD RED**:
  - `tests/cli/test_user_prelude.sh` (신규) — `aura --prelude 55:48:89:e5 fixture.elf` 실행 → exit 0 + 특정 주소가 candidate 로 등록.
  - `tests/symbolic/test_user_prelude_parse.c` (신규) — text → AuraUserPrelude 변환 unit test.
- **예상 commit 수**: 4 (parser + struct + CLI wire + test).
- **세션 estimate**: 1.
- **의존성**: X-S1 (PatternByte primitive) 를 먼저 도입하면 코드 공유 가능. 독립 도입도 OK.
- **인용**: #30 §8.5 C-1 + #33 §3.1 X-S1.

---

## 5. 실행 그래프 (의존 관계)

```
X-S1 (PatternByte primitive)
  ├── R-C1  (--prelude CLI)
  ├── G-M1  (XML pattern DSL)
  │     └── G-M2  (Ghidra pattern DB 이식)
  └── G-S3  (Ghidra x86-64gcc static 이식, stopgap)

H-S1 (NoReturn DB 확장)       ── 독립, 최우선
G-S1 (Pre-pattern gate)       ── 독립
G-S2 (Prologue TRIPLE)        ── 독립 (G-S1 과 결합 시 상승)
R-P1 (x86-64 PLT)             ── ELF reloc parser 의존 (기존)
R-P2 (PE IAT)                 ── PE import parser 의존 (확인 필요)
R-D1 (depth limit)            ── 독립

R-N1 (Nucleus)                ── cfg.c BB API 노출 필요
R-F1 (FLIRT IDA loader)       ── CRC16 util, sigdb 번들 정책 결정 선행
G-M3 (Medium-hash FID)        ── cfg.c flow walker 필요
  └── G-M4 (InstructionSkipper) ── G-M3 선행
G-M5 (PseudoDisasm)           ── disasm.c bounded-decode API 노출
G-M6 (DWARF subprogram)       ── dwarf_types.c 확장
G-S6 (switch-table 환류)      ── switch_recovery.c ↔ func_detect.c 순환 의존 해결

R-Z1 (zignatures graph)       ── cfg.c 재사용, 독립 도입 가능
R-E1 (calling convention)     ── param_id.c 확장
G-M7 (4-round scheduler)      ── pipeline.c 구조 변경 (대공사)
```

**권장 단기 순서** (1 세션씩, 누적 F1 +0.04~0.07 예상):
1. **H-S1** (최우선, 양쪽 확증, risk LOW)
2. **G-S1** (FP 주범 차단, Precision 돌파구)
3. **X-S1** (foundation for R-C1/G-M1)
4. **R-P1** (x86_64 recall 돌파)
5. **R-C1** (편의 + G-S1/G-S2 검증에 활용 가능)
6. **G-S2** (G-S1 이후 효과 증폭)
7. **R-P2** (PE 전용, 선택적)
8. **R-D1** (안정성 보강)

---

## 6. Phase 2-X 로드맵 매핑 (README v3 §4)

Session #9 README v3 의 Phase 2-B ~ 2-F 매핑:

| Phase | README v3 §4 주제 | 본 문서 항목 |
|-------|-------------------|--------------|
| **2-B (현재)** | Compare 분석 (research doc → 실행 가능 backlog) | **본 문서 §4 단기 top-5** 를 2-B 출력으로 채택 |
| **2-C** | (x86 benchmark fixture) | — (func_detect 외부 의존 없음) |
| **2-D** | Quality bugs (truncated body 등 3요인) | G-M5 (PseudoDisasm) 가 2-D 후 재평가 — trial decode 가 truncated body 진단에 도움 |
| **2-E** | EH flow + CHK postdom (진행 중) | H-S1 Rust/Go noreturn 확장은 EH flow 와 일부 겹침 (cross-check 필요) |
| **2-F (next)** | Phase 2-F 단기 개선 실행 | **§3.1 H-S1 → G-S1 → X-S1 → R-P1** 순차 수행 권장 |
| 2-G (제안) | Medium-hash FID + FLIRT loader | **R-F1 + G-M3** (세션 6-8) |
| 2-H (제안) | Nucleus CFG-first | **R-N1** (세션 3-4, 단독 큰 바디) |
| 2-I (제안) | XML pattern DSL + Ghidra pattern DB | **G-M1 + G-M2** (세션 3-4) |
| 2-J (제안) | DWARF subprogram + calling convention | **G-M6 + R-E1** |

---

## 7. 인용

### 7.1 연구 doc 참조

- **#26** `docs/research/ghidra_func_detect_analysis.md`
  - §3.2 BulkPatternSearcher + XML DSL — G-M1/G-M2 근거
  - §3.3 FID 3-tier (SHORT=4, MEDIUM=24, SCORE_THRESHOLD=14.6) — G-M3/G-M4 근거
  - §5.1 S-1/S-2/S-3/S-4/S-5/S-6 — 본 문서 G-S1/G-S2/G-S3, H-S1, R-P1 (S-5)
  - §5.2 M-1/M-3/M-4/M-5/M-6/M-7 — 본 문서 중기 block
  - §6 단기 top-5 구현 draft — 4.1/4.2 상세 스펙 원본
  - §7 Ghidra source paths (`FunctionStartAnalyzer.java`, `FidService.java`, `NoReturnFunctionAnalyzer.java`)
- **#30** `docs/research/rizin_func_detect_analysis.md`
  - §2 `rz_core_analysis_all` + `aa`/`aaa`/`aaaa` 체인
  - §3.2 Nucleus (Andriesse-Slowinska 2017) — R-N1 근거
  - §4.1 FLIRT `.pat`/`.sig` + IDA FLAIR 호환 — R-F1 근거
  - §4.2 zignatures SDB + graph feature — R-Z1 근거
  - §5 비교표 (28 항목)
  - §7.1 신규 제안 N-1/F-1/Z-1/P-1/C-1/E-1/D-1 — 본 문서 R-접두 항목
  - §7.3 Ghidra+Rizin 공통 확증 (S-4 noreturn)
  - §8.1-8.5 상세 spec
- **#33** `docs/research/x64dbg_analysis.md`
  - §3.1 `PatternByte{data,mask}` + `patternfind.cpp` 구조 — X-S1 근거
  - §3.3 triangulation 표 (Ghidra × Rizin × x64dbg × AURA wildcarded byte matching 공통 foundation)
  - §7.1 pattern 4-way 비교 — 본 문서 §2 격차 매트릭스 항목 8/9/10/11 근거
  - §8.1 S-x-1 (~200 LOC 이식) — 4.5 R-C1 의 텍스트 파서 공유 근거

### 7.2 AURA 내부 참조

- `src/symbolic/func_detect.c:131-204` — 아키 별 prologue helper (x86/AArch64/ARM32)
- `src/symbolic/func_detect.c:231-465` — `collect_candidates()` 6-phase
- `src/symbolic/func_detect.c:703-775` — `func_detect()` smart default + min_confidence
- `src/symbolic/func_detect_internal.h:28-53` — `CandidateSource` enum + confidence tier
- `src/symbolic/func_detect_plt.c` (88 LOC, AArch64-only) — R-P1/R-P2 확장 대상
- `src/symbolic/func_id.c:65-135` — x86/AArch64 immediate mask (G-M4 per-processor skipper 시작점)
- `src/symbolic/func_id.c:219-305` — 12-entry builtin DB (G-M3 에서 확장 대상)
- `src/core/flirt.c` (492 LOC) — R-F1 도입 시 `flirt_legacy.c` 로 rename, 신규 `flirt_ida.c` 가 primary
- `src/core/noreturn_detect.c:83-` — builtin names 확장 (H-S1)
- `tests/symbolic/test_func_detect_*.c` (5 files) — `test_func_detect.c` 통합 파일 없음. H-S1/G-S1/G-S2/R-P1 별 신규 파일로 신규 추가.
- `tests/benchmark/bench_func_detect.sh` — F1 측정 harness (각 항목 구현 후 재측정 필수)

### 7.3 외부

- Andriesse, D., Slowinska, A., Bos, H. *"Compiler-Agnostic Function Detection in Binaries"*. IEEE EuroS&P 2017. (R-N1)
- Ghidra `Ghidra/Processors/{AARCH64,x86}/data/patterns/*.xml` (Apache 2.0, G-M2 이식 대상)
- IDA FLAIR `.pat`/`.sig` 포맷 spec (Rizin 구현 참조, R-F1)

---

## 8. 경계 / Open decisions

1. **R-F1 sigdb 번들 정책**: `third_party/sigdb/` 내장 vs build-time 다운로드. 번들 크기 (수백 MB) 이 AURA repo 부담. CMake `FetchContent_Declare` 권장 (전례: `third_party/sqlite/`).
2. **R-N1 LGPL 전파 방지**: Rizin `librz/analysis/fcn.c` 직접 copy-paste 금지. Andriesse 논문만 참조 → clean-room 재구현.
3. **Ghidra pattern DB (G-M2) 라이선스**: Apache 2.0 → AURA Apache 2.0 와 호환. `LICENSES/GHIDRA-Apache2.0` + NOTICE 추가 필요.
4. **F1 Δ 수치 검증**: 본 문서의 예상 Δ 는 #26/#30 의 휴리스틱 + 기존 AURA 벤치 조합. 각 항목 구현 후 `tests/benchmark/bench_func_detect.sh` 실측 필수.
5. **G-S1 pre-pattern gate 범위**: 현재 `collect_candidates()` Phase A 에만 적용. Phase B/C 의 call-target 후보는 이미 CALL confidence 180 > min_confidence 100 이라 영향 없음 — 의도적.
6. **H-S1 와 Phase 2-E CHK postdom 상호작용**: Phase 2-E (commits `c2beabd`, `2ebe264`) 는 EH flow / postdom 관련. noreturn CFG 환류 도입 시 commit 후 재시험.

---

**문서 종료**. 본 문서는 Task #41 comparison 완료 산출물. 다음 단계는 2-F 세션에서 §3.1 단기 top-5 를 TDD 순차 실행. 개선 항목 총 **33 건** (단기 8 / 중기 12 / 장기 5 + arch 지원 등 보조 8).
