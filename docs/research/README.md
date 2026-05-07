# AURA Research: Ghidra / Rizin / x64dbg Parity Analysis (v3)

> Session #9 (2026-04-21) 확장 — **12 research doc + 이 index = 13 개** 통합.
> AURA 의 Ghidra 급 도달 로드맵 근거. 3 도구 × 3 도메인 × 4 tool 관점 = **6-way triangulation**.
> 재활용 가능한 self-contained markdown. 미래 세션이 단일 entry point 로 삼음.
> v1 (Ghidra 3, Task #29) → v2 (+Rizin 3 + x64dbg 1, Task #34) → **v3 (+x64dbg 5 심층, Task #40)**.

---

## 1. 빠른 참조 (TL;DR v3)

### 1.1 현재 AURA parity 상태
- AURA Ghidra parity: **~55~60 점** (v2.3.0-rc3 기준, real-binary covered_avg 55 plateau)
- 연구 문서 **12 doc + 1 index = 13 (총 ~6000 LOC)**
- 현재 세션 (Session #9) 누적 unpushed: Pre-1 / Pre-2 / E-1 / E-2 + 12 research doc
- 정책: **Ghidra 급 도달 전까지 tag/release 금지** (`feedback_aura_versioning_policy.md`)

### 1.2 AURA 컴포넌트 × 연구 문서 매트릭스

각 AURA 컴포넌트에 대해 어느 연구 문서가 어느 주제를 다루는지 일람:

| AURA 컴포넌트 | Ghidra doc | Rizin doc | x64dbg doc | 우선순위 레버 |
|---------------|-----------|-----------|------------|----------------|
| **func_detect** (`src/symbolic/func_detect.c`) | #26 | #30 | #33 pattern | Pre-pattern gate / Nucleus / FLIRT / zignatures |
| **disasm** (`src/disasm/` + `recursive_disasm.c`) | #27 | #31 | (none direct) | ARM/Thumb / AArch64 adrp+ldr+br / switch |
| **IR + lifting** (`codegen.c`, `arm64_lifter.c`, `IrOpcode`) | #28 | #32 | (none direct) | **RzIL 28→82 점진 전환** (최대 ROI) |
| **Symbol + PDB** (`src/parser/pdb_parser.c`) | (partial in #26) | (partial in #30) | #33 + #39 | DIA SDK / partial load / symbol server |
| **GUI** (`src/gui/`) | (none) | (none) | #37 | Qt panel 전체 + theming + shortcut |
| **CLI** (`src/cli/`) | (none) | (none) | #33 + #38 | ExpressionParser DSL |
| **Plugin system** (PRD §4.1 유보) | (partial) | (partial) | #38 | v3.0.0 후 재검토 reference |
| **Bridge / API boundary** | (none) | (none) | #36 | GUI↔core 경계 재평가 |
| **Core engine** (runtime) | (none) | (none) | #35 | AURA scope 외 (정적 RE) |
| **Exception / unwind** (`.eh_frame`) | (partial in #28) | (partial in #32) | #39 | Phase 3.14 `.eh_frame` 강화 |

### 1.3 6-way triangulated 최상위 레버 v3 (AURA 구현 순서)

| 순위 | 레버 | 출처 | 예상 +Δ | 난이도 | 세션 | AURA 컴포넌트 |
|------|------|------|--------|--------|------|---------------|
| 1 | **IrOpcode 28→48 확장** (prereq) | #28 R-S1 + #32 Phase A | +4~6 | Med | 1-2 | IR |
| 2 | **ARM/Thumb + AArch64 adrp+ldr+br** | #27 S-1/S-3 + #31 S-A/S-B | +5~20 | Med | 2 | disasm |
| 3 | **per-block cmp stack + JumpBasic-lite** | #28 R-S2 + #27 S-2 | +6~10 | Med | 1-2 | IR + disasm |
| 4 | **Pre-pattern gate + prologue pair + NoReturn DB** | #26 S-1+S-2+S-4 | +3~5 | Low | 1 | func_detect |
| 5 | **FLIRT sigdb loader** | #30 F-1 | +2~5 | Med | 2-3 | func_detect |
| 6 | **Nucleus CFG-first** | #30 N-1 | +3~7 | High | 2-3 | func_detect |
| 7 | **IrVal Varnode refactor + Flag SSA** | #32 Phase B + #28 R-S2 | (#1 prereq) | Med | 2-3 | IR |
| 8 | **Lifter 재작성** (codegen.c + arm64_lifter.c) | #32 Phase C | (#7 prereq) | High | 3-5 | IR |
| 9 | **PDB symbol server + partial load** | #33 + #39 | +1~3 | Med | 1-2 | Symbol |
| 10 | **GUI Qt panel 전체 reference** | #37 | N/A (UX) | Med | 3-5 | GUI |
| 11 | **CLI ExpressionParser DSL** | #33 + #38 | N/A | Low | 1 | CLI |
| 12 | **Bridge ListInfo + C-ABI layer** | #36 | architectural | Low | 0-1 | Architecture |

**장기 합계**: **15-22 세션** (v2 예상과 일치 — x64dbg 5 doc 은 **주로 GUI/arch reference**라 parity +Δ 추가 없음).

---

## 2. 문서 목차 (13 = 12 + index)

### 2.1 Ghidra 시리즈 (3 doc, Apache 2.0 — 가장 자유로운 참조)

1. **[ghidra_func_detect_analysis.md](./ghidra_func_detect_analysis.md)** — ~330 LOC, Task #26
   - 함수 탐지 (entry / boundary / FID / FLIRT / pattern)
   - **Top**: S-1 Pre-pattern gate / S-2 prologue pair / S-4 NoReturn DB
   - **Recall 80.5% / Precision 93.6% / F1 0.866** (AArch64 stripped) → 목표 0.92

2. **[ghidra_disasm_analysis.md](./ghidra_disasm_analysis.md)** — ~402 LOC, Task #27
   - 디스어셈블러 (SLEIGH / recursive-linear / switch / mixed-mode)
   - **Top**: S-1 ARM/Thumb dual-context / S-2 JumpBasic-lite / S-3 AArch64 4-byte jump table

3. **[ghidra_disasm_decompile_bridge_analysis.md](./ghidra_disasm_decompile_bridge_analysis.md)** — ~546 LOC, Task #28
   - PCode / lifting / pass chain / type inference
   - **Top**: R-S1 IrOpcode 확장 / R-S2 per-block cmp stack / R-S3 PTRADD/PTRSUB
   - **합산 예상**: covered_avg 55 plateau 돌파 **+13~21%**

### 2.2 Rizin 시리즈 (3 doc, LGPL-3 — scratch 재구현 필수)

4. **[rizin_func_detect_analysis.md](./rizin_func_detect_analysis.md)** — ~1400 LOC, Task #30
   - `aa` 시리즈 + zignatures + Nucleus + FLIRT
   - **Top**: N-1 Nucleus CFG-first / F-1 FLIRT sigdb / Z-1 zignatures / S-4 noreturn DB

5. **[rizin_disasm_analysis.md](./rizin_disasm_analysis.md)** — ~350 LOC, Task #31
   - Capstone integration + 자체 arch plugin + 파일 loader
   - **Top**: S-A ARM mapping symbol / S-B AArch64 adrp+ldr+br (**Ghidra #27 양쪽 확증**)

6. **[rizin_il_analysis.md](./rizin_il_analysis.md)** — ~515 LOC, Task #32
   - RzIL 심층 + ESIL migration + decompiler plugins
   - **Top**: Phase A/B/C **8-12 세션 blueprint** (IrOpcode 28→82 점진 전환)

### 2.3 x64dbg 시리즈 (6 doc, GPL-3 — clean-room 이식)

7. **[x64dbg_analysis.md](./x64dbg_analysis.md)** — ~432 LOC, Task #33
   - 제한 4 scope: Pattern scan / PDB symbol server / CLI / Disasm UX (runtime debugger 는 AURA scope 외)
   - **Top**: S-x-1 Pattern scan DSL / S-x-2 PDB symbol server auto-download

8. **[x64dbg_core_engine.md](./x64dbg_core_engine.md)** — ~300-450 LOC, Task #35
   - Debugger core (BP manager / memory / thread / exception / stepping)
   - **AURA scope 외** (정적 RE). 단 exception taxonomy 는 HIR_COMMENT 비교 참조

9. **[x64dbg_bridge_api.md](./x64dbg_bridge_api.md)** — 262 LOC, Task #36
   - GUI↔DBG bridge 구조 (C ABI + `GUIMSG` dispatch + append-only enum)
   - **핵심 AURA 적용**: (i) bridge 자기규율 → `src/gui/` ↔ `src/core/` 경계, (ii) `PLUG_SDKVERSION` + `CB_*` → 장기 plugin 재도입 시 reference

10. **[x64dbg_gui_panels.md](./x64dbg_gui_panels.md)** — ~500-700 LOC, Task #37
    - 전체 Qt 패널 (15 view / 40+ dialog / 100+ shortcut) — **최고 AURA GUI reference**
    - **Top 14 패턴**: P1 AbstractTableView / P4 Bridge singleton / P7 RichTextPainter / P9 Configuration registry

11. **[x64dbg_plugin_scripting.md](./x64dbg_plugin_scripting.md)** — ~400-500 LOC, Task #38
    - Plugin SDK (`PLUG_SDKVERSION=1`, 35 CBTYPE) + SimpleScript + ExpressionParser (14-레벨 C precedence, shunting-yard)
    - **AURA**: plugin 은 PRD §4.1 유보. ExpressionParser 는 CLI `--filter "addr >= 0x1000"` 장기 참조

12. **[x64dbg_symbol_trace.md](./x64dbg_symbol_trace.md)** — ~400-500 LOC, Task #39
    - Symbol 4-layer (`SymbolSourceBase` / DIA / EAT-IAT-forwarder / merge-fallback) + Trace recording (TRAC / hit counter)
    - **Top**: `isOpen/isLoading/cancelLoading/waitUntilLoaded` lazy-load 플래그 + `decoratedName/undecoratedName` dual-field → PDB 파서 이식 가치

### 2.4 Index (이 문서)

13. **[README.md](./README.md)** — v3 (Task #40)

---

## 3. 6-way Triangulation 발견

### 3.1 공통 주제 1: **ARM / AArch64 디스어셈블러 정확도** (양쪽 양쪽 확증, v2 동일)
- Ghidra #27 S-1 (ARM/Thumb dual-context) + S-3 (AArch64 jump table)
- Rizin #31 S-A (`$a`/`$t`/`$d` mapping symbol) + S-B (adrp+ldr+br 3-instr)
- **레버 #2 채택** — 두 tool 이 같은 lever 를 각자 top 으로 지목

### 3.2 공통 주제 2: **PCode-style Low-IR 도입** (점진 blueprint, v2 동일)
- Ghidra #28 R-S1/R-S2/R-S3 + Rizin #32 Phase A/B/C
- x64dbg 는 runtime debugger 라 대응 없음 (정적 lifting 없음)
- **레버 #1 / #7 / #8 채택** — Rizin LGPL-3 실증 blueprint

### 3.3 공통 주제 3: **Signature / Pattern DB (runtime loadable)** (3-way, #33 x64dbg 합류)
- Ghidra #26 M-1 (XML pattern loader) + Rizin #30 F-1/Z-1 (FLIRT/zignatures) + x64dbg #33 S-x-1 (pattern scan DSL)
- **레버 #4 / #5 채택**

### 3.4 공통 주제 4: **PDB Symbol server + 심볼 엔진** (2-doc deep, v3 확장)
- x64dbg #33 (표면 4-tier fallback) + **#39 심층** (`SymbolSourceBase` lazy-load / DIA vs DbgHelp / MSF 직접 파싱)
- AURA Phase 3.12 PDB 존재 but auto-DL 부재 + lazy-load 미적용
- **레버 #9 채택**

### 3.5 공통 주제 5: **Nucleus / FLIRT** (Rizin 고유, v2 동일)
- AURA 완전 부재, stripped recall (Nucleus) + naming precision (FLIRT) 양쪽 대규모 개선
- **레버 #5 / #6 채택**

### 3.6 공통 주제 6 (v3 신규): **Plugin architecture**
- x64dbg #38 심층: 35 CBTYPE 이벤트 + `PLUG_SDKVERSION=1` + `PLUG_IMPEXP` export 매크로
- Rizin `RCorePlugin` + Ghidra `AnalyzerScheduler` 은 #30/#26 에 부분적 기술
- **AURA 영향**: PRD §4.1 "MVP 이후 유보" 정책을 **유지**. 단 v3.0.0+ 재도입 시 x64dbg 35 CBTYPE 이 가장 현실적 reference

### 3.7 공통 주제 7 (v3 신규): **GUI Qt 패널 MVC**
- x64dbg #37 **단독** (Ghidra=Swing/Java, Rizin=TUI) → **유일한 Qt native reference**
- AURA Qt6 적용 시 14 패턴 직접 매핑 가능 (`AbstractTableView` / Bridge singleton / `Configuration` registry / `VaHistory`)
- **레버 #10 채택**

### 3.8 공통 주제 8 (v3 신규): **GUI↔Core bridge 자기규율**
- x64dbg #36 의 "C ABI + `GUIMSG` 정수 + void\*" 비대칭 패턴
- AURA 는 단일 프로세스지만 **개념적 경계**는 동일하게 유익
- **레버 #12 채택**

---

## 4. 우선순위 재조정 (v3 = v2 Phase 2-X-1~9 + x64dbg 5 doc reference)

| Phase | 작업 | 근거 | 세션 |
|-------|------|------|------|
| **2-X-1** | IrOpcode 28→48 확장 (UDIV/SDIV/ZEXT/SEXT/SAR) | #28 R-S1 + #32 Phase A | 1-2 |
| **2-X-2** | ARM mapping symbol + AArch64 adrp+ldr+br | #27 + #31 | 2 |
| **2-X-3** | per-block cmp stack + JumpBasic-lite | #28 R-S2 + #27 S-2 | 1-2 |
| **2-X-4** | Pre-pattern gate + prologue pair + NoReturn DB | #26 S-1/S-2/S-4 | 1 |
| **2-X-5** | FLIRT sigdb loader + zignatures 경량 | #30 F-1 + Z-1 | 2-3 |
| **2-X-6** | Nucleus CFG-first 탐지 | #30 N-1 | 2-3 |
| **2-X-7** | IrVal Varnode refactor + Flag SSA (2-X-1 prereq) | #32 Phase B + #28 R-S2 | 2-3 |
| **장기 2-X-8** | Lifter 재작성 | #32 Phase C | 3-5 |
| **장기 2-X-9** | PDB symbol server auto-DL + `SymbolSourceBase` lazy-load | #33 + #39 | 1-2 |
| **v3 신규 2-X-10** | GUI 14 패턴 적용 (AbstractTableView / Configuration registry) | #37 | 3-5 |
| **v3 신규 2-X-11** | CLI ExpressionParser DSL (`--filter`) | #33 + #38 | 1 |
| **v3 신규 2-X-12** | Bridge ListInfo + C-ABI GUI↔core 경계 규정 | #36 | 0-1 |

**합계**: 15-22 세션 (2-X-10/11/12 는 UX/arch reference — parity +Δ 에 직접 기여 X).

---

## 5. 다음 단계 — Comparison Agent 체인 예정

v3 완료 후 **4 comparison agent** 가 각 AURA 컴포넌트 별로 연구 → 구현 변환:

| Agent | 입력 문서 | 출력 | AURA 컴포넌트 |
|-------|-----------|------|---------------|
| `compare-func-detect` | #26 + #30 + x64dbg #33 pattern | `docs/research/aura_vs_func_detect.md` | func_detect |
| `compare-disasm-ir` | #27 + #28 + #31 + #32 + #33 disasm | `docs/research/aura_vs_disasm_ir.md` | disasm + IR |
| `compare-symbol` | #33 + #39 | `docs/research/aura_vs_symbol.md` | PDB + symbol |
| `compare-gui-ext` | #33 CLI + #36 + #37 + #38 | `docs/research/aura_vs_gui_ext.md` | GUI + CLI + plugin |

각 agent 는 implementation-ready backlog (file path / API / test strategy) 생성.

---

## 6. 라이선스 매트릭스 (v3 업데이트)

| 도구 | 라이선스 | AURA 활용 방식 |
|------|---------|----------------|
| Ghidra | Apache 2.0 | 자유 참조 + 알고리즘 차용 OK (가장 자유) |
| Rizin | LGPL-3 | 알고리즘 참조 + **scratch 재구현 필수** (직접 copy 금지) |
| x64dbg | GPL-3 | **Clean-room 이식 원칙** (#33 §10.4, #35~#39 공통) — 설명 보고 재구현 |

IDA Pro / Binary Ninja core binary 분석은 EULA 상 금지 (본 세션에서 결정).

---

## 7. 재활용 가이드 (v2 동일, 대상 확장)

### 7.1 미래 세션에서 본 연구 consume 하는 방법
1. 본 README.md 먼저 읽기 → §1.2 매트릭스 + §1.3 12 레버 + §3 공통 주제 8 파악
2. 관심 영역 문서 clone (12 개 중 해당 컴포넌트)
3. 각 문서 §7 (로드맵) + §8 (상세 스펙) 에 수정 파일 / API / 테스트 전략 명시됨
4. 구현 시 commit msg 에 `analysis doc ref: docs/research/{file}.md §X` 인용

### 7.2 기준 문서 (인용 관계)
- Phase 2-E 완주 이후 본 연구가 **Phase 2-X** (단기 ROI, 2-X-1~7) / **Phase 2-Y** (Low-IR 장기, 2-X-8/9) / **Phase 2-Z** (v3 신규, 2-X-10/11/12 UX+arch) 의 근거
- Ghidra 급 도달 로드맵의 일부 (`feedback_aura_versioning_policy.md` — rc3 이후 tag 금지, PR-based workflow)

---

## 8. 메타데이터

- **작성 시점**: 2026-04-21 Session #9 (v2.3.0 Phase 2-E 병렬 연구 + x64dbg 5 doc 심층)
- **Git HEAD at analysis**: `2ebe264` (E-2 완료 후) — comparison agent 실행 시 추가 commit 예상
- **Teammates**:
  - Ghidra: ghidra-analyst / disasm-analyst / bridge-analyst (#26 / #27 / #28)
  - Rizin: rizin-func-analyst / rizin-disasm-analyst / rizin-il-analyst (#30 / #31 / #32)
  - x64dbg: x64dbg-analyst (#33) / x64dbg-core (#35) / x64dbg-bridge (#36) / x64dbg-gui (#37) / x64dbg-plugin (#38) / x64dbg-symbol (#39)
- **Curator chain**: v1 research-curator (#29) → v2 curator-v2 (#34) → **v3 curator-v3 (#40)**
- **Next**: comparison 4 agent + final synthesis
- **재검토 주기**: 각 도구 major update 시 (1-2년 단위), 또는 AURA IR 구조 변경 시

---

## 9. 추가 연구 후보 (backlog, v2 동일)

사용자 판단 시 dispatch 가능한 잠재 연구:

- **RetDec** (MIT, LLVM 기반 decompiler) — middle-IR reference
- **angr** (BSD-2, symbolic execution) — CFG 복원 / taint / indirect target resolution
- **BAP** (MIT, binary analysis framework) — IL / lifter design
- **Hex-Rays 공식 블로그 / 논문** (공개 정보만) — 상용 RE 트렌드 (lifting / type recovery)

IDA Pro / Binary Ninja core binary 분석은 EULA 상 금지.
