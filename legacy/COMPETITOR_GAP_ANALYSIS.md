# AURA — 상용 RE 도구 대비 기능 격차 분석

**작성일**: 2026-04-26 · **AURA 비교 시점**: branch `phase-2.4tp/t5b-rename-propagation` HEAD `a2328ec`
**작성자**: Session #22 (T-5b 작업 일시 보류 후 분석)
**관련 문서**: `AURA_CAPABILITY_ANALYSIS.md` (자체 능력 평가) · `MASTER_ROADMAP.md` (장기 궤적)

본 문서는 **상용/오픈소스 리버스 엔지니어링 도구 6종** (IDA Pro, Ghidra, Binary Ninja, Hopper, radare2+Cutter, JEB) 과 비교한 **AURA 의 기능 격차**를 코드 레벨 증거와 함께 정리한다. `AURA_CAPABILITY_ANALYSIS.md` 가 "AURA 가 할 수 있는 것" 관점이라면, 이 문서는 **"상용 기준으로 AURA 가 못 하는 것"** 관점이다.

---

## 1. 범례

| 기호 | 의미 |
|:---:|---|
| ✅ | 상용 도구와 실용적으로 동급 |
| 🟡 | 동작하지만 품질·범위 격차 큼 |
| ⚠️ | 부분 구현 / 스텁 / 결함 미해결 |
| ❌ | 완전 부재 |
| 📛 | 정책상 영구 불가 (PRD/CLAUDE.md 명시) |
| ❓ | 코드는 있으나 실제 작동 여부 미확인 |

각 ⚠️ / 🟡 셀은 검증 footnote `[^Nx]` 로 증거 (파일 경로·LOC·호출처) 를 첨부한다. 검증 protocol 은 §16 부록 참조.

---

## 2. 비교 대상 도구

| 도구 | 라이선스 | 강점 (이 문서가 가정하는 baseline) |
|---|---|---|
| **IDA Pro** + Hex-Rays | 상용 ($$$) | 산업 표준, FLIRT, 디컴파일 품질 1위, F.L.I.R.T. 시그DB |
| **Ghidra** | Apache 2.0 (NSA) | 무료, P-Code IR, 다중 아키텍처, Function ID DB |
| **Binary Ninja** | 상용 (Vector35) | LLIL/MLIL/HLIL 다층 IR, Sidekick AI, Python API |
| **Hopper** | 상용 | macOS/iOS 강세, Objective-C/Swift |
| **radare2 + Cutter** | LGPL/GPL | CLI 강력, ESIL emul, 무료 |
| **JEB** | 상용 | DEX/.NET/WASM, 모바일 RE 1위 |

---

## 3. 결론 — P0 ~ P2 결함 9 항목

> 이 9개를 해소하지 않으면 AURA 는 위 6종 어느 것의 사용자도 이주시키지 못한다.

### P0 (도구 정체성을 위협하는 결함)

1. **실 바이너리 디컴파일 품질 천장** — `cat 15.8% / ls 45.1% / aura-self 87.6%` covered, covered_avg ~55. Ghidra/Hex-Rays = 99 수준. (출처: `~/.claude/projects/.../memory/project_real_binary_parity_2026_04_18.md`, `feedback_aura_benchmark_bias.md`)
2. **AArch64 lifter UAF 미해결** — `src/decompiler/arm64_lifter.c:1072` `arm_irblock_alloc_instr` realloc-after-borrow. ASan 활성 시 즉사. test 가 `LABELS "no-asan"` 으로 skip 중. 모바일 RE 진입 차단. (`tests/CMakeLists.txt:3632–3644`)
3. **구조체/클래스/vtable 복원** — `struct_recovery.c` 625 LOC 존재하나 covered_avg 가 그 효과를 반영 못 함. C++/Rust/Go 바이너리에서 멤버 접근이 raw offset 으로 노출.

### P1 (시장 세그먼트 진입 차단)

4. **시그니처 DB (FLIRT/Function ID) 부재** — `flirt.c` + `flirt_ida.c` 코드는 있으나 **shipped 시그DB 0 개**. 라이브러리 함수 (printf 등) 모두 unknown 으로 노출 → 모든 분석에 노이즈.
5. **디버거 백엔드 부재** — `debugger_panel.cpp` 6.4 K, ptrace/gdb 호출 0 건. 100% UI 스텁.
6. **DWARF/PDB 통합 약함** — 파서는 1538/755 LOC 로 두텁지만, 디컴파일 codegen 으로의 실제 type apply 경로가 1 곳뿐 (`dwarf_types.c`). 디버그 심볼 보유 바이너리에서도 익명 변수·익명 타입.

### P2 (생태계 / UX)

7. **스크립팅 영구 금지** — CLAUDE.md 핵심 원칙. Python/Lua 불가. 상용 도구 핵심 가치제안 (자동화·플러그인) 정면 충돌. **이건 결함이 아니라 의도된 trade-off** 이므로 "구현 항목" 이 아닌 "이주 장벽" 으로만 이해해야 한다.
8. **Patch 디스크 write 경로 부재** — `patch_editor.cpp::onApply()` 가 `accept()` 만 호출, 실제 파일 쓰기 없음. UI 만 있고 행위 없음.
9. **LLM 할루시네이션 가드 부재** — 4 LLM backend (LM Studio, OpenAI, Llama.cpp, Groq) 구현되었으나 `src/llm/` 에 hallucinat/verify 0 건. AURA 의 차별 기능이 오히려 신뢰성 위험.

---

## 4. 디스어셈블 / 아키텍처 커버리지

| 항목 | IDA | Ghidra | BN | r2 | Hopper | JEB | **AURA** |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| x86 / x86-64 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ [^A1] |
| ARM (A32 / Thumb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ⚠️ [^A2] |
| AArch64 (ARM64) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ⚠️ [^A3] |
| MIPS | ✅ | ✅ | ✅ | ✅ | — | — | 🟡 [^A4] |
| PowerPC | ✅ | ✅ | ✅ | ✅ | — | — | 🟡 [^A5] |
| RISC-V | ✅ | ✅ | ✅ | ✅ | — | — | 🟡 [^A6] |
| Dalvik (Android DEX) | ⚠️ | ✅ | — | ⚠️ | — | ✅ | 🟡 [^A7] |
| SPARC / 68k / Z80 / 8051 | ✅ | ✅ | ⚠️ | ✅ | — | — | ❌ |
| AVR / PIC | ✅ | ✅ | ⚠️ | ✅ | — | — | ❌ |
| WASM | ⚠️ | ✅ | ⚠️ | ⚠️ | — | ✅ | ❌ |
| 마이크로코드 / 다층 IR | Hex-Rays | P-Code | LLIL/MLIL/HLIL | ESIL | — | IR | ⚠️ HIR 단일 [^A8] |

[^A1]: `src/disasm/capstone_wrapper.c` 289 LOC, `src/disasm/zydis_wrapper.c` 208 LOC. 디스어셈 자체는 Capstone 5 위임 — 동급. 단 **함수 탐지 정확도** 는 별도 (P0 결함과 결합).
[^A2]: ARM A32 / Thumb 일반 lifter 없음. `src/disasm/aarch64_plt_thunks.c` 213 LOC 는 PLT thunk 전용. 일반 ARM 명령어 → HIR 경로 부재.
[^A3]: `src/decompiler/arm64_lifter.c` 1468 LOC + 64.6K. 실 lifter 존재. 그러나 `tests/CMakeLists.txt:3634` 에 `# LABELS "no-asan": under ASan this test exposes a PRE-EXISTING UAF in arm64_lifter.c:1072 (arm_irblock_alloc_instr realloc-after-borrow, same pattern as the Session #1-extra fix at line 594 on 2026-04-17)`. 즉 정상 빌드는 작동 추정, ASan 빌드에서 즉사. 메모리: `~/.claude/projects/.../memory/project_arm64_lifter_uaf_1072.md` (2-X-8 재작성 대기).
[^A4]: `src/decompiler/mips_lifter.c` 373 LOC / 15.2K. test 존재 여부 미확인 — `tests/decompiler/` glob 에서 `mips` 매치 없음 (검증 grep). 통합 단위 테스트 부재 추정.
[^A5]: `src/decompiler/ppc_lifter.c` 325 LOC / 13.8K. 동일 — 단위 테스트 매치 없음.
[^A6]: `src/decompiler/riscv_lifter.c` 373 LOC / 16K. `tests/decompiler/test_ssa_dom_convergence.c` 가 일부 RISC-V 경로 cover 하나 ISA 전반 검증 없음.
[^A7]: `src/decompiler/dalvik_lifter.c` 413 LOC + `src/parser/dex_parser.c` 272 LOC. DEX 파일 → HIR 경로는 존재하나 Android 앱 (APK / OAT / VDEX) 로더 없음. JEB 비교에서 명백히 열세.
[^A8]: AURA HIR 은 단일 레벨. Binary Ninja 처럼 LLIL → MLIL → HLIL multi-stage lift / lower 모델 부재. 결과적으로 의사코드 정제도 한 단계 분석에 의존 → 품질 천장 P0.

---

## 5. 파일 포맷 / 로더

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| ELF (32/64) | ✅ | ✅ [^F1] |
| PE / PE+ | ✅ | ✅ [^F2] |
| Mach-O (단일 슬라이스) | ✅ | 🟡 [^F3] |
| Mach-O FAT / Universal | ✅ | ⚠️ [^F4] |
| dyld_shared_cache | ✅ (IDA/Hopper/BN) | ❌ |
| Android DEX | ✅ (JEB/Ghidra) | 🟡 [^F5] |
| Android OAT / VDEX / ART | ✅ (JEB) | ❌ |
| .NET / CLR | ✅ (dnSpy/JEB) | 🟡 [^F6] |
| Java class / JAR | ✅ (JEB) | ❌ |
| WebAssembly | ⚠️ | ❌ |
| Firmware (raw + base + banks) | ✅ | 🟡 [^F7] |
| iOS IPA / kernelcache | ✅ (IDA/Hopper) | ❌ |
| Intel HEX / S-rec | ✅ | ❌ |
| 코어 덤프 / minidump | ✅ | ❌ |
| COFF / OMF / a.out | ✅ | ❌ |
| Game ROM (NES/SNES/GBA 등) | ✅ (Ghidra) | ❌ |

[^F1]: `src/parser/elf_parser.c` 19.7K / 600+ LOC, `src/parser/relocation.c` 30.4K. 표준 ELF 64/32 + relocation. eh_frame 별도 파서 36.1K. 실용 수준.
[^F2]: `src/parser/pe_parser.c` 21.4K, `seh_parser.c` 11.8K, `pe_unwind.c` 3.9K. PE/SEH/unwind 통합. 단 PDB 통합은 §7 [^T2] 참조.
[^F3]: `src/parser/macho_parser.c` 22.3K / 609 LOC. 실 파서 존재. 그러나 dyld_shared_cache 코드 grep 0 건 — iOS 대형 시스템 라이브러리 분석 불가.
[^F4]: FAT/Universal 처리 함수명 (`parse_macho_fat` 등) grep 0 건. 단일 슬라이스만 파싱 추정. macho_parser.c 내부 구현 미확인.
[^F5]: `dex_parser.c` 272 LOC + `dalvik_lifter.c` 413 LOC. DEX → HIR 경로는 존재. 그러나 APK 컨테이너 / multidex / OAT 미지원. test_format_support.c 에서 dalvik 매치 2건만.
[^F6]: `dotnet_parser.c` 294 LOC. CLR 메타데이터 헤더 파싱 추정. IL bytecode → HIR lifter 부재 (전용 lifter 파일 없음).
[^F7]: `src/parser/firmware_loader.c` 95 LOC / 2.9K. `firmware_loader.h` 1.3K — 최소 인터페이스. base address / banks 옵션 노출 미확인. 실 펌웨어 분석 케이스 누락.

---

## 6. 디컴파일 품질 — 가장 치명적 영역

| 항목 | Ghidra / Hex-Rays | **AURA** |
|---|:---:|:---:|
| **실 바이너리 함수 커버리지** | ~99% | **15–87%** [^D1] |
| **covered_avg 점수** | ~99 | **~55** [^D2] |
| 함수 자동 탐지 정확도 | 95%+ | ⚠️ [^D3] |
| 변수 타입 복원 | ✅ | ⚠️ [^D4] |
| 구조체 / 유니온 복원 | ✅ | 🟡 [^D5] |
| 배열 인덱싱 복원 | ✅ | 🟡 [^D6] |
| switch / jump table | ✅ | 🟡 [^D7] |
| 가상 함수 / vtable | ✅ | ❌ [^D8] |
| C++ 클래스 / 상속 | ⚠️/✅ | ❌ |
| try / catch 복원 | ⚠️/✅ | 🟡 [^D9] |
| goto 제거 / 구조화 | ✅ | 🟡 [^D10] |
| 인라인 함수 탐지 | ✅ | 🟡 [^D11] |
| noreturn 전파 | ✅ | ⚠️ [^D12] |
| 컴파일러 시그니처 인식 | ✅ | ❌ |
| 표준 헤더 자동 적용 | ✅ | ❌ |

[^D1]: 메모리 `project_real_binary_parity_2026_04_18.md`: cat 15.8% / ls 45.1% / aura-self 87.6%. aura-self 는 자기 코드 overfitting (`feedback_aura_benchmark_bias.md`). 실 외부 바이너리 = 16~45% 가 진짜.
[^D2]: 동일 메모리 + `project_phase_f_plan.md`. covered_avg 55 가 구조적 천장 — 함수 탐지 / CFG 복원 / hir_builder term=NULL bail 3 요인 복합 (`project_quality_bugs_session8.md`).
[^D3]: `src/symbolic/func_detect.c` 959 LOC + 4 보조 모듈 (gap/datascan/ehframe/plt). 광범위하나 stale auto-count 결함 등 잔존 (`Tasks.md` 의 test_func_detect_gap stale auto-count 인용).
[^D4]: `type_inference.c` 513 LOC + `type_constraint.c` 884 LOC + `type_dispatch.c` 97 LOC + `var_propagation.c` 352 LOC. v2.4.0 TP-1 머지로 default path 통합. 그러나 T-5b (rename → vp_apply_to_hir) 미머지 상태 = 변수 rename 이 HIR 까지 전파되지 않음.
[^D5]: `struct_recovery.c` 625 LOC + `aggregate_types.c` 760 LOC. pipeline.c / hir.h / decompiler.h / codegen.c 통합. test `test_struct_recovery.c`, `test_aggregate_types.c`, `test_struct_array_emit.c`, `test_hir_struct_typedef.sh` 존재. 그러나 covered_avg 가 효과를 못 잡음 → emit 률 미상.
[^D6]: 위 [^D5] 와 동일 모듈. 배열 인덱싱은 `ptr_chain.c` 330 LOC 에서 일부.
[^D7]: `switch_recovery.c` 294 LOC. codegen.c / control_flow.c / indirect_resolver.c 통합. test `test_switch_recovery.c` 존재. 인식률 정량 측정 부재.
[^D8]: vtable 복원 키워드 grep 결과 없음. C++ ABI 인식은 `__cxa_demangle` 만 (이름 복원, 클래스 그래프 X).
[^D9]: `src/decompiler/exception_flow.c` 610 LOC + `src/symbolic/eh_cfg.c` 112 LOC + `src/parser/eh_frame_parser.c` 36.1K. 정보는 풍부하나 의사코드에 try/catch 키워드 emit 경로 미확인.
[^D10]: `src/decompiler/goto_elimination.c` 97 LOC — `ge_classify_edge()` 가 edge 를 BREAK/CONTINUE/GOTO 셋 중 분류. `control_flow.c` 가 사용 (4건). 단순 분류기 — 비환원 (irreducible) CFG 에서 goto 잔존.
[^D11]: `src/core/inline_detect.c` 407 LOC / 13K. test 존재 미확인. 효과 정량 측정 없음.
[^D12]: `src/core/noreturn_detect.c` 555 LOC. v2.3.0 D-2 에서 truncation counter architectural 한계 노출 (`project_noreturn_truncation_counter.md`) — `/* NORETURN */` annotation 우회로 D-2 gate 충족.

---

## 7. 타입 시스템 / 디버그 심볼

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| DWARF v2~v5 파싱 | ✅ | 🟡 [^T1] |
| DWARF → 디컴파일 적용 | ✅ | ⚠️ [^T2] |
| PDB (Microsoft) 파싱 | ✅ | 🟡 [^T3] |
| PDB → 디컴파일 적용 | ✅ | ⚠️ [^T4] |
| C++ Itanium demangle | ✅ | ✅ [^T5] |
| Rust 심볼 demangle | ✅ | ❌ |
| Go (gopclntab) | ✅ | ❌ |
| Swift demangle | ✅ | ❌ |
| Objective-C 메타데이터 | ✅ (Hopper) | ❌ |
| 사용자 타입 라이브러리 영속 | ✅ | ⚠️ [^T6] |
| 표준 헤더 (libc / win32 / POSIX) | ✅ | ❌ |
| 칼링 컨벤션 자동 추론 | ✅ | 🟡 [^T7] |

[^T1]: `src/parser/dwarf_parser.c` 1538 LOC / 55.2K. CU/DIE/abbrev/.debug_line 폭넓게 파싱 추정. `tests/parser/test_dwarf_parser.c` 12 건 매치.
[^T2]: 디컴파일러로의 type apply 함수 (`apply_dwarf|attach_dwarf|use_dwarf|dwarf_apply|debug_types_apply`) grep 결과 = `dwarf_types.c:1` (단 1건). 즉 파서 출력이 codegen 단계로 전파되는 경로가 매우 좁다. 디버그 심볼이 있어도 변수/타입 이름이 의사코드에 거의 반영되지 않을 가능성.
[^T3]: `src/parser/pdb_parser.c` 755 LOC / 25.3K. `tests/parser/test_pdb_parser.c`, `test_pdb_partial.c`, `test_pdb_dual_name.c` 3 종 — 실 검증 있음.
[^T4]: `src/decompiler/pdb_types.c` 356 LOC. `pdb_*` 심볼 grep 58건 — 통합 시도는 있으나 covered_avg 효과 미상.
[^T5]: `src/core/demangle.cpp` 1.1K — `__cxa_demangle` 단순 래퍼. C++ 이름 → 가독 형태. Itanium ABI 만.
[^T6]: `src/gui/type_editor.cpp` 9.5K + `type_editor.h` 2.3K. 사용자가 GUI 로 타입 정의 가능. 그러나 SQLite 영속 → 다음 세션에서 codegen 에 재적용 경로 미검증.
[^T7]: `src/decompiler/calling_conv.c` 508 LOC / 20.2K. cdecl / stdcall / fastcall 등 추론 추정. test 직접 매치 없음 (test_*calling* glob 미확인).

---

## 8. 인터랙티브 편집 (RE 의 핵심 UX)

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| **변수 rename → HIR 반영** | ✅ | 🟡 [^I1] |
| 함수 rename → 영속 | ✅ | ⚠️ [^I2] |
| 타입 cast (변수) | ✅ | ❌ [^I3] |
| 구조체 정의 → 의사코드 반영 | ✅ | ⚠️ [^I4] |
| 스택 프레임 편집 | ✅ | 🟡 [^I5] |
| 주석 추가 / 영속화 | ✅ | ❓ |
| 북마크 | ✅ | ✅ [^I6] |
| 네비게이션 히스토리 (back/forward) | ✅ | 🟡 [^I7] |
| 즉시 재분석 (rename → propagate) | ✅ | ❌ [^I8] |

[^I1]: v2.4.0 T-5b 진행 중 (현재 branch). `src/gui/rename_validate.cpp` 4.3K 검증 헬퍼 + main_window QInputDialog 와이어 + FileLoader rename map + `vp_apply_to_hir` bridge 6-commit 시퀀스. **미머지** — 격차 표 작성 시점에서 변수 rename 이 HIR 의 hir_var.name 까지 전파되지 않음.
[^I2]: `src/gui/edit_handlers.cpp` 2.6K + `undo_manager.cpp` 4.1K. 함수 rename 처리는 main_window.cpp 내부 추정. SQLite project DB 영속 경로 미검증.
[^I3]: T-5d 미착수. Tasks.md 에 placeholder 만.
[^I4]: type_editor 가 정의 가능 (UI 9.5K) 하나 codegen 으로 전파되는 cycle 미확인.
[^I5]: `stack_layout_view.cpp` 7.3K — 스택 프레임 표시 UI. 편집 → re-decompile 경로 미검증.
[^I6]: `src/core/auto_bookmark.c` 271 LOC + `auto_bookmark.h` 4K. crypto_detect 와 연동 (3 건 grep). 자동 북마크.
[^I7]: `src/gui/nav_history.cpp` 1.2K — 매우 작음. push/pop API 만 추정. Ghidra 식 풍부한 history (call site 추적 등) 부재.
[^I8]: 위 [^I1] 의 미머지 상태 + DWARF apply 단일 경로 [^T2] 결합 = "변수명 바꾸면 다른 함수에서도 즉시 새 이름으로 보인다" 시나리오 동작 안 함.

---

## 9. 디버거 통합

| 항목 | IDA / x64dbg / WinDbg | Ghidra | **AURA** |
|---|:---:|:---:|:---:|
| 통합 디버거 백엔드 | ✅ | ✅ | ❌ [^B1] |
| 브레이크포인트 설정 / 토글 | ✅ | ✅ | ⚠️ UI만 [^B2] |
| 단일 스텝 / 스텝 인투 / 아웃 | ✅ | ✅ | ❌ |
| 메모리 / 레지스터 뷰 | ✅ | ✅ | ⚠️ UI만 [^B2] |
| 원격 디버그 (gdbserver / WinDbg) | ✅ | ✅ | ❌ |
| 트레이스 / time-travel | ⚠️ | ⚠️ | ❌ |
| 동적 데이터 → 정적 분석 피드백 | ✅ | ✅ | ❌ |

[^B1]: `src/gui/debugger_panel.cpp` 6.4K. ptrace / gdb / process_attach 키워드 grep = src/ 하 0건 (`src/gui/main_window.cpp` 와 `debugger_panel.cpp` 자체 매치는 변수명일 뿐 시스템 호출 없음). 백엔드 0%.
[^B2]: `debugger_panel.cpp` 의 첫 60줄 검토: BP list QListWidget, register QTableWidget 에 `{"RAX", 0}, {"RBX", 0}` 등 디폴트 0 으로 초기화. 이벤트 연결 없음 → UI만 그려짐.

---

## 10. 패칭

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| 명령어 어셈블 (Keystone/Zydis) | ✅ | 🟡 [^P1] |
| 패치 미리보기 (인코딩 결과 표시) | ✅ | ✅ [^P2] |
| **디스크 write / 새 바이너리 저장** | ✅ | ❌ [^P3] |
| 패치 diff / 일괄 export | ✅ | ❌ |
| Hex 에디터 뷰 | ✅ | ❌ |
| 패치 undo / redo | ✅ | 🟡 [^P4] |

[^P1]: `src/disasm/zydis_wrapper.c` 208 LOC + `include/patch.h` 3.3K. Zydis 어셈블러 통합 (D-?? Phase 5.7). nop/ret/int3/jmp/call 만 지원 (`patch_editor.cpp:31` placeholder text).
[^P2]: `patch_editor.cpp::onAsmChanged()` 가 `patch_encode()` 호출 → 인코딩된 바이트 미리보기 + 길이 표시. 작동.
[^P3]: `patch_editor.cpp::onApply()` 본체 (line 117–121): `m_applied = true; accept();` — 단지 dialog accept, 실제 파일 write 없음. main_window.cpp 등 호출처에서 디스크 반영 코드 grep 결과 미확인. **사실상 미완** — UI 는 OK 라고 말하지만 바이너리는 변경되지 않음.
[^P4]: `undo_manager.cpp` 4.1K + edit_handlers 통합 (17건 grep). rename / annotation 만 cover 추정, patch 통합 미확인.

---

## 11. 자동화 / 확장 (📛 영구 정책 영역)

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| Python 스크립팅 | ✅ (전 도구) | 📛 [^X1] |
| Lua / JS 스크립팅 | ⚠️ | 📛 |
| 플러그인 SDK | ✅ | 📛 [^X2] |
| C/C++ 헤드리스 API | ⚠️ | 🟡 [^X3] |
| CLI 자동화 옵션 | ✅ (r2 강점) | 🟡 [^X4] |
| 배치 / 회귀 분석 자동화 | ✅ | 🟡 [^X5] |

[^X1]: `.claude/CLAUDE.md` `핵심 원칙` 1: "C/C++ 전용. Python, Java 등 인터프리터 언어 사용 금지". 상용 도구 핵심 가치제안 (자동화 생태계) 정면 충돌. **결함이 아니라 포지셔닝 결정** — 본 표는 객관적 격차만 표기.
[^X2]: `include/aura_plugin.h` 13.2K + `src/core/plugin_loader.c` 9.4K — 플러그인 인터페이스는 구조적으로 존재하나 PRD 가 "MVP 이후 유보". 실 출시 플러그인 0 개.
[^X3]: `include/headless.h` 871B + `src/core/headless.c` 14K. 헤드리스 진입점 일부 존재. 외부 C/C++ 프로젝트가 AURA 를 lib 으로 link 하는 use case 사례 미상.
[^X4]: `src/cli/decompile_all.c` 10.3K + `decompile_metrics.c` 5.2K — 두 명령만. r2 처럼 광범위한 CLI subcommand 부재.
[^X5]: 회귀 harness `tests/benchmark/regression_harness.sh` 존재 (CLAUDE.md 참조). 단 도구 사용자가 자기 워크플로우를 자동화하는 표면이 좁음.

---

## 12. 시각화 / 네비게이션

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| CFG 그래프 뷰 | ✅ | 🟡 [^V1] |
| 콜그래프 | ✅ | 🟡 [^V2] |
| CFG ↔ 의사코드 동기화 클릭 | ✅ | ❓ [^V3] |
| Strings / Imports / Exports 패널 | ✅ | 🟡 [^V4] |
| Xref 양방향 점프 | ✅ | 🟡 [^V5] |
| 미니맵 / heatmap | ✅(BN) | ❌ |
| 데이터 타입 트리 (struct browser) | ✅ | ⚠️ [^V6] |
| 명령 팔레트 | ✅(BN) | ✅ [^V7] |

[^V1]: `src/gui/cfg_view.cpp` 14.5K — 노드/엣지 렌더링 추정. 레이아웃 알고리즘 (sugiyama 등) 사용 여부 미확인.
[^V2]: `src/gui/callgraph_view.cpp` 13.1K + `src/decompiler/callgraph.c` 192 LOC.
[^V3]: 시그널 connect 검색 결과 (`addressSelected|gotoAddress|jumpTo`) = src/gui/ 0건. CFG 클릭 → 의사코드 jump 시그널 미검증. Ghidra 표준 UX 부재 가능.
[^V4]: `src/gui/panels.cpp` 10.4K. 다중 패널 통합. 각 패널의 검색·필터링 깊이 미확인.
[^V5]: `include/xref.h` 5K + `src/core/xref.c` 11.5K. xref 데이터는 풍부. UI 양방향 점프 신호 grep 미확인.
[^V6]: type_editor 트리뷰 추정 (9.5K). 그러나 [^T6] 영속·재적용 사이클 미검증.
[^V7]: `src/gui/command_palette.cpp` 71 LOC — 동적 QAction 필터링 (Type-to-search). 작동하는 BN-style palette.

---

## 13. 시그니처 / 라이브러리 식별

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| FLIRT / Function ID DB | ✅ (IDA / Ghidra) | ⚠️ [^S1] |
| **Shipped 시그니처 DB** | ✅ (수십만 시그) | ❌ [^S2] |
| Lumina / Sidekick (클라우드) | ✅ (IDA/BN) | ❌ |
| 패커 / 프로텍터 탐지 | ✅ (DiE/PEiD 통합) | ⚠️ [^S3] |
| 컴파일러 / 런타임 식별 | ✅ | ❌ |
| Yara 통합 | ✅ | 🟡 [^S4] |
| Algorithm fingerprint (crypto) | ⚠️ | 🟡 [^S5] |

[^S1]: `src/core/flirt.c` 492 LOC + `flirt_ida.c` 10.6K. `FlirtDb` / `FlirtSig` 구조 + `flirt_db_create/add/destroy` API. IDA `.sig`/`.pat` 형식 파싱 추정. test `tests/core/test_flirt.c` 존재 (9건 매치).
[^S2]: 그러나 `data/sigs/` 같은 시그DB 디렉토리 부재. 사용자가 IDA 라이선스에서 자기 .sig 를 가져와야 함. 즉시 사용성 = 0.
[^S3]: `crypto_detect.c` 582 LOC 가 일부 알고리즘 시그 검출. 일반 packer (UPX/ASPack 등) 탐지 별도 모듈 부재.
[^S4]: `src/core/yara_search.c` 207 LOC. Yara rule 파일 적용 가능 추정. test 검증 미확인.
[^S5]: `crypto_detect.c` 가 AES S-box, SHA constants 등 검출 (auto_bookmark 와 연동 3건 grep). 알고리즘 종류 정량 미상.

---

## 14. 협업 / 프로젝트

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| 프로젝트 저장 / 로드 | ✅ | 🟡 [^C1] |
| 프로젝트 매니저 UI | ✅ | ✅ [^C2] |
| **멀티유저 동시 편집** | ✅ (Ghidra Server / BN Sync) | 🟡 [^C3] |
| 변경 이력 (git-like) | ✅ (Ghidra) | ⚠️ [^C4] |
| 두 바이너리 diff (BinDiff/Diaphora) | ✅ | 🟡 [^C5] |
| 함수 단위 export / import | ✅ | ❌ |
| 익스포트 (header / IDL) | ✅ | ⚠️ [^C6] |

[^C1]: `src/gui/project.cpp` 13.7K + `project_manager_window.cpp` 3.7K + `session_manager.cpp` 6.3K. `third_party/sqlite/` (D-13, 2026-04-03) 영속 백엔드.
[^C2]: 프로젝트 매니저 윈도우 분리 GUI.
[^C3]: `src/collab/` 8 파일 (`collab_server.cpp` 27.5K + `collab_client.cpp` 19.7K + `collab_protocol.cpp` 16.6K + `collab_sync.cpp` 9.9K + `collab_auth.cpp` 10.9K + `main_server.cpp` 4.1K). QTcpSocket / connectToHost / listen 매치 — collab_server 와 collab_client 에 실 네트워크 코드 (3 파일). **백엔드 본체 존재**. GUI 측 `collab_panel.cpp` 12.7K 가 client 와 연결 (4 파일 grep). 다만 production 검증 / 다중 사용자 시나리오 테스트는 `tests/collab/test_sync_engine.cpp` + `test_collab.cpp` 2 건 — 깊이 미상.
[^C4]: undo_manager 17건 grep — UI 액션 단위 undo 만. git-like 영속 history (커밋/체크아웃) 부재.
[^C5]: `src/core/binary_diff.c` 415 LOC. `bdiff_print()` 만 외부 노출, CLI/GUI 호출처 미발견. 코드는 있으나 사용자 진입점 부재.
[^C6]: `src/gui/export_dialog.cpp` 3.2K — UI 다이얼로그 작음. C 헤더 / IDL / IDA Pro 형식 export 깊이 미상.

---

## 15. 분석 엔진 (고급)

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| 데이터 플로 / SSA | ✅ | 🟡 [^E1] |
| 심볼릭 실행 | ⚠️(angr 별도) | ⚠️ [^E2] |
| 테인트 분석 | ⚠️ | ⚠️ [^E3] |
| 별칭 분석 | ✅(Hex-Rays) | 🟡 [^E4] |
| 루프 분석 / induction var | ✅ | 🟡 [^E5] |
| noreturn 전파 | ✅ | ⚠️ [^E6] |
| 인덴티튜드 (induction var) | ✅ | ❓ |
| 상수 전파 / 사장 코드 제거 | ✅ | ✅ [^E7] |
| Lifted IR 검증 (validator) | ⚠️ | 🟡 [^E8] |

[^E1]: `src/symbolic/dfg.c` 510 LOC + `phi_elimination.c` 326 LOC + `flag_ssa.c` 121 LOC + `reg_coalesce.c` 517 LOC. SSA dom 결함이 v2.3.0 Session #14 R1 fix 로 해소됨 (`project_session14_results.md`).
[^E2]: `src/symbolic/symbolic_engine.c` 583 LOC — `sym_engine_destroy`, `sym_state_destroy` 외 외부 호출처 = `src/symbolic/dfg.c` 단 1개 파일. 즉 **모듈 존재하나 통합 거의 0**. 의미 있는 path exploration 미작동 추정.
[^E3]: `src/core/taint_analysis.c` 496 LOC. 외부 호출처 (`taint_(analyze|run|propagate|track)`) grep = 0 건 (자기 파일 1건 제외). **dead code 수준**.
[^E4]: `src/decompiler/alias_analysis.c` 498 LOC. `dead_store.c` 가 사용 (`alias_(analyze|query|may_alias|run)` grep 5건 중 외부 1건). 좁은 통합.
[^E5]: `src/decompiler/loop_detect.c` 681 LOC + `licm.c` 192 LOC + `strength_reduce.c` 178 LOC. Natural loop 분석 + 루프 불변 코드 이동. goto_elimination 이 LoopInfo 사용.
[^E6]: [^D12] 와 동일 — counter architectural 한계.
[^E7]: `src/decompiler/const_prop.c` 417 LOC + `dead_code.c` 321 LOC + `dead_store.c` 230 LOC + `cse.c` 143 LOC + `expr_simplify.c` 276 LOC + `expr_reassoc.c` 341 LOC. 표준 최적화 패스 다수.
[^E8]: `src/decompiler/ir_validator.c` 335 LOC + `include/ir_validator.h` 3.1K. IR 무결성 검증.

---

## 16. AI / LLM 통합 (AURA 의 의도된 차별점)

| 항목 | IDA Decompiler AI / BN Sidekick | **AURA** |
|---|:---:|:---:|
| 함수명 자동 제안 | ✅ | 🟡 [^L1] |
| 변수명 자동 제안 | ✅ | 🟡 [^L1] |
| 자연어 질의 (이 함수가 뭐 하나?) | ✅ | 🟡 [^L1] |
| 다중 backend (OpenAI / 로컬) | ✅ | ✅ [^L2] |
| **할루시네이션 검증 / 회복** | ⚠️ | ❌ [^L3] |
| 결과 캐싱 | ✅ | ✅ [^L4] |
| 컨텍스트 윈도우 관리 | ✅ | ❓ |
| 비용 / 토큰 모니터링 | ✅ | ❓ |

[^L1]: `src/gui/llm_panel.cpp` 9.9K + `prompt_templates.c` 6.6K. 프롬프트 템플릿 + GUI 입력. 품질 = LLM 의존.
[^L2]: `src/llm/` 하 4 backend: `openai_client.c` 11.3K, `lmstudio_client.c` 9.6K, `llamacpp_client.c` 8.7K, `groq_client.c` 2.8K. + `openai_compat.h`. 다양성 우수.
[^L3]: `hallucinat|trust|verify|llm_validate` grep = `src/llm/` 0 건. `rename_validate` 는 GUI 측 통사 검증만 (식별자 형식 등) — LLM 응답 진위 검증 아님. `feedback` 메모리 항목 0 건. **AURA 차별 기능이 안전장치 없음**. 사용자 수동 확인 강제.
[^L4]: `src/llm/llm_cache.c` 7.2K. 응답 캐싱 ✓.

---

## 17. UX / 운영

| 항목 | 상용 baseline | **AURA** |
|---|:---:|:---:|
| 다국어 UI (i18n) | ⚠️ | ⚠️ [^U1] |
| 키바인딩 커스터마이즈 | ✅ | 🟡 [^U2] |
| 테마 / 다크모드 | ✅ | 🟡 [^U3] |
| 명령 팔레트 | ✅(BN) | ✅ [^V7] |
| 실시간 검색 (전 항목) | ✅ | 🟡 [^U4] |
| **대형 바이너리 (>1GB) 처리** | ✅ | 🟡 [^U5] |
| 로깅 / 콘솔 패널 | ✅ | ⚠️ [^U6] |
| 안정성 (장시간 분석 무크래시) | ✅ | ⚠️ [^U7] |

[^U1]: 프로젝트 자체는 한국어 + 영어 혼용. UI 문자열 i18n 시스템 (Qt Linguist 등) 적용 여부 미확인.
[^U2]: `src/gui/shortcut_manager.cpp` 13.1K. 단축키 관리 본격 구현 추정. 사용자 정의 binding 영속 미확인.
[^U3]: `src/gui/theme_manager.cpp` 4.9K. 다크/라이트 토글 추정.
[^U4]: `src/core/search.c` 12.4K + `search_dialog.cpp` 4.5K. 다차원 검색 (string/xref/type) 깊이 미확인.
[^U5]: D-6 결정 (PRD): `mmap` 채택 — 24 occurrences across 15 files. 1 GB+ 바이너리 실측 벤치마크 부재.
[^U6]: `src/gui/console_panel.cpp` 33 LOC — info/warning/error 3종 logger. 매우 단순 (검색·필터·내보내기 부재).
[^U7]: AArch64 lifter UAF (line 1072) + 잠재 SSA dom 결함 등 ASan 노출 사례 다수 (`project_arm64_lifter_uaf_1072.md`, R1 fix 이력). 장시간 무크래시 회귀 검증 없음.

---

## 18. Effort × Impact 매트릭스 (개선 우선순위)

> **Effort**: 추정 PR 수 (S = 1–3, M = 4–10, L = 10+) · **Impact**: 사용자 이주 동인 정도

| 결함 | Effort | Impact | 권장 우선순위 |
|---|:---:|:---:|---|
| 디컴파일 covered_avg 55→80+ | L (다 페이즈) | ★★★★★ | **P0-1** v2.5 ~ v3.0 핵심 |
| AArch64 UAF 해소 + ASan 클린 | M | ★★★★ | **P0-2** 2-X-8 재작성 |
| 구조체/vtable/C++ 클래스 복원 emit | L | ★★★★ | **P0-3** type_inference 위 별도 layer |
| FLIRT 시그DB 번들 (libc 일부) | S | ★★★★ | **P1-1** 즉시 가능 — `data/sigs/` 만들고 IDA .sig 변환 |
| DWARF/PDB → codegen apply 경로 확장 | M | ★★★★ | **P1-2** dwarf_types.c 확장 |
| Patch 디스크 write 경로 | S | ★★★ | **P1-3** patch_editor 사용자 사기 방지 |
| LLM 할루시네이션 가드 | S | ★★★ | **P1-4** 신뢰성 확보 |
| 디버거 백엔드 (gdb 시작점) | L | ★★★ | **P2-1** 별도 페이즈 |
| dyld_shared_cache / iOS / WASM | L 각각 | ★★ | **P3** 시장 세그먼트별 |
| 스크립팅 / 플러그인 | (정책) | ★★★★ | 📛 PRD 결정 영역 — 본 문서 권고 X |
| ARM A32/Thumb 일반 lifter | M | ★★ | **P2-2** 모바일 RE 기반 |
| MIPS/PPC/RISC-V test 강화 | S | ★★ | **P2-3** lifter 신뢰성 |

**즉시 착수 가능 (S)**:
- P1-1 시그DB 번들 (수일)
- P1-3 Patch write (수일)
- P1-4 LLM 가드 (수일)

**현재 진행 중 / 직결**:
- v2.4.0 T-5b (Variable Rename propagation) → P0-3 sub-task
- v2.4.0 TP-3 / T-5c → 타입 cast UI

---

## 19. 검증 방법 부록 (재현 가능)

본 표의 footnote 는 2026-04-26 commit `a2328ec` 기준. 다음 명령으로 재현 가능.

### 19.1 헤더 vs 구현 LOC

```bash
wc -l src/parser/*.c src/disasm/*.c src/decompiler/*.c \
      src/symbolic/*.c src/core/*.c src/gui/*.{cpp,h}
```

### 19.2 호출처 카운트 (Grep)

```bash
# 예: DWARF apply 경로
rg -t c -t cpp 'apply_dwarf|attach_dwarf|use_dwarf|dwarf_apply|debug_types_apply' src/

# 예: 디버거 백엔드 호출
rg -t c -t cpp -i 'ptrace|gdb_|process_attach|breakpoint' src/

# 예: 할루시네이션 가드
rg -t c -t cpp -i 'hallucinat|llm_validate|verify' src/llm/

# 예: 네트워크 코드 (collab 백엔드 검증)
rg 'QTcpSocket|connectToHost|listen\(' src/collab/
```

### 19.3 테스트 등록 / no-asan skip

```bash
rg -B 2 -A 2 'LABELS "no-asan"' tests/CMakeLists.txt
```

### 19.4 파서 ↔ codegen 통합 검사 (예시)

```bash
# 어느 파일이 dwarf_types 를 호출하는가
rg 'dwarf_types|dt_apply|dt_resolve' src/decompiler/codegen.c src/core/pipeline.c
```

### 19.5 외부 진입점 (사용자가 실제로 만나는 표면)

```bash
ls -la src/cli/ src/gui/ | head -50
```

---

## 20. 한계 / 면책

- **본 문서는 정적 코드 분석 기반**. 실제 사용자 시나리오 (예: "실제로 macOS dylib 을 열어 vtable 까지 본다") end-to-end 시연은 별도 검증 필요.
- 일부 ❓ 항목 (CFG↔의사코드 동기화, 주석 영속, 패치 부분의 실 디스크 write 경로 등) 은 GUI 코드 깊이 추적 시 변경 가능.
- covered_avg / 실 바이너리 점수는 메모리 (`project_real_binary_parity_2026_04_18.md` 등) 인용 — 본 문서 작성 시점 (2026-04-26) 에서 신선도 ≈ 1주.
- v2.4.0 T-5b 완성 직후 §8 [^I1] / [^I8] / §15 [^E2/E3] 일부 등급 상향 가능.

---

## 21. 다음 액션 후보 (사용자 결정 필요)

1. **PRD §7 Open Decisions 등재**: 본 문서의 P0~P2 9 결함 중 어느 것을 PRD 정식 결정으로 추진할지 사용자 confirm.
2. **MASTER_ROADMAP.md 통합**: 18 매트릭스를 페이즈 / 트랙 단위 항목으로 분해.
3. **v2.4.0 scope 재조정**: 현재 v2.4 = TP-1..4 + T-5a..d. P0/P1 결함 일부 (예: P1-1 FLIRT 번들) 를 v2.4 scope 에 추가할지, v2.5 / v3.0 으로 분리할지.
4. **v2.4.0 T-5b 복귀 즉시 여부**: 본 문서 작성 직후 T-5b 코드 작업 재개 가능 — 별도 turn 으로 진행.

이 4 항목은 사용자 결정에 의존하므로 본 분석 문서는 **권고 없이 결함만 제시**한다.

---

## 변경 이력

| 일자 | 세션 | 변경 |
|---|---|---|
| 2026-04-26 | #22 | 초안 작성 (T-5b 일시 보류 후 분석) |
