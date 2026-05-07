# AURA Analysis Capabilities Inventory

**Generated**: 2026-04-04  
**Phase**: 8 (GUI MVP) — All core analysis modules complete (Phase 5.9 + 6.5)  
**Purpose**: Comprehensive comparison against Ghidra 12 analyzer list

---

## Executive Summary

AURA has implemented **core reverse engineering analysis capabilities** across 7 major modules. As of Phase 8, the GUI serves as the primary interface. This document inventories all analysis features currently available and identifies gaps relative to Ghidra 12.

**Status**: MVP-complete. Most fundamental binary analysis features are implemented; advanced/enterprise features (plugin system, scripting, collaborative analysis) are Phase 11+ scope.

---

## 1. DISASSEMBLY ANALYSIS

### 1.1 Linear Disassembly (`disasm.h`)

**Capabilities**:
- **Disassembler Engine**: Capstone ≥5.0 (x86/x86_64, ARM, ARM64)
- **Instruction Decoding**: Full binary→mnemonic+operand conversion
- **Architecture Support**:
  - x86_64 (primary)
  - x86 (32-bit)
  - ARM (32-bit)
  - ARM64 (AArch64)
  - x86 VAEX (vector extensions)
- **Instruction Output Format**:
  - Mnemonic (e.g., "mov", "add", "jmp")
  - Operands (e.g., "rax, rbx")
  - Raw bytes (byte_count, max 16 bytes/instr)
- **Scope**: Arbitrary memory regions (`.text`, `.code`, data sections)

**Implementation**: `src/disasm/capstone_wrapper.c`

---

### 1.2 Recursive Disassembly (Function-Level)

**NOT IMPLEMENTED** — AURA uses **linear/section-level** disassembly only. Functions are identified post-hoc via `func_detect.h` (see §2.4).

---

## 2. CONTROL FLOW ANALYSIS

### 2.1 Control Flow Graph (CFG) Recovery (`cfg.h`)

**Capabilities**:
- **BasicBlock Identification**: 
  - Automatic leader address collection (branch targets + fallthrough)
  - Single-entry, single-exit block decomposition
- **Edge Types**:
  - `CFG_EDGE_FALLTHROUGH` — sequential/unconditional jmp
  - `CFG_EDGE_BRANCH_TRUE` — jcc taken (conditional jump target)
  - `CFG_EDGE_BRANCH_FALSE` — jcc not-taken (next instruction)
  - `CFG_EDGE_CALL` — call instruction (interprocedural edge)
  - `CFG_EDGE_RET` — ret instruction (function exit)
- **Output Formats**:
  - Text (human-readable)
  - Graphviz DOT (visualization)
- **Scope**: Single-function CFG only (intra-procedural)

**Implementation**: `src/symbolic/cfg.c`

---

### 2.2 Block Analysis

**Capabilities**:
- Block-level metadata: `start_addr`, `end_addr`, instruction array
- Predecessor/successor tracking (for DFG)
- Dead-code detection (via DFG kill-set analysis)

**NOT IMPLEMENTED**: Loop analysis, natural loop hierarchy, loop-invariant code motion

---

### 2.3 Path Feasibility Analysis

**NOT IMPLEMENTED** — AURA has symbolic execution skeleton (`symbolic.h`) but no SMT solver integration. Only concrete value tracking is present.

---

## 3. DATA FLOW ANALYSIS

### 3.1 Reaching Definition Analysis (`dfg.h`)

**Capabilities**:
- **Algorithm**: Reaching definition (Def/Use dataflow)
- **Register Tracking**: 
  - x86_64 general-purpose registers (RAX, RCX, RDX, RBX, RSP, RBP, RSI, RDI, R8–R15)
  - Bitmask-based representation (uint32_t, 16 registers)
- **Per-Instruction Tracking**:
  - `DfgInsnInfo.def_mask` — which registers defined
  - `DfgInsnInfo.use_mask` — which registers used
- **Per-Block Tracking**:
  - `gen_mask` — definitions generated (reaching block boundary)
  - `kill_mask` — definitions killed/overwritten
  - `in_mask` — reaching definitions at block entry
  - `out_mask` — reaching definitions at block exit
- **Algorithm**: Worklist fixed-point iteration

**Scope**: Single-function, register-level only

**Implementation**: `src/symbolic/dfg.c`

---

### 3.2 Liveness Analysis

**NOT IMPLEMENTED** — Only reaching definitions. Liveness (variables live at block exit) not computed.

---

### 3.3 SSA Form Conversion

**PARTIALLY IMPLEMENTED** (in decompiler.h, not standalone DFG):
- IR-level SSA via `ir_build_ssa()` (Phase 5)
- Dominance frontier computation (Cooper et al. 2001)
- φ-function insertion
- Renaming pass (DFS)
- **Not in raw binary form** — only in intermediate representation

---

## 4. SYMBOLIC EXECUTION

### 4.1 Concrete Value Tracking (`symbolic.h`)

**Capabilities**:
- Abstract value types: `SYM_VAL_CONCRETE` (constants), `SYM_VAL_SYMBOLIC` (symbolic)
- Register state: 32-register array (x86_64: 16 GPRs + 16 reserved)
- Per-instruction semantics: `sym_step()` updates state
- Path condition tracking: Linked-list accumulation of branch conditions
- State cloning: Independent path exploration support

**Scope**: Single-threaded, worklist-based dispatcher; inline method only

**Implementation**: `src/symbolic/symbolic_engine.c`

---

### 4.2 SMT Solving / Constraint Solving

**NOT IMPLEMENTED** — Symbolic expressions have expr_id stubs but no constraint solver backend (Z3, CVC5, etc.). Path feasibility not solved.

---

### 4.3 Function Summary Inference

**NOT IMPLEMENTED** — No automatic summary generation (pre/post conditions, side effects).

---

## 5. FUNCTION ANALYSIS

### 5.1 Function Boundary Detection (`func_detect.h`)

**Detection Strategy** (priority order):
1. Prologue pattern: `push rbp; mov rbp, rsp` (standard x86_64)
2. Prologue pattern: `push rbp` (short form)
3. Stack frame allocation: `sub rsp, N` (leaf functions)
4. Symbol table entries: `AURA_SYM_FUNCTION` type (if FileInfo present)

**Output**:
- `FuncEntry`: (start, end, size, name)
- Automatic naming: "sub_\<hex\>" if no symbol

**Limitations**:
- Pattern-based heuristic (not dataflow)
- ARM/ARM64 prologue patterns NOT implemented
- Leaf function detection via sub-rsp only (limited)

**Implementation**: `src/symbolic/func_detect.c`

---

### 5.2 Call Graph Generation (`func_detect.h` → `CallGraph`)

**Capabilities**:
- Direct call detection: `call \<addr\>` instruction scanning
- Edge types:
  - Intra-binary calls: callee_idx populated
  - Indirect/external calls: callee_idx = `FUNC_CALLEE_UNKNOWN`
- Call site tracking: `call_site` address recorded

**Scope**: Direct calls only; indirect call targets not resolved

**Implementation**: `src/symbolic/func_detect.c`

---

### 5.3 Caller-Callee Analysis

**PARTIALLY IMPLEMENTED**:
- Forward edges: available via CallGraph
- Backward edges (reverse callgraph): NOT pre-computed

---

### 5.4 Function Signature Inference

**NOT IMPLEMENTED** — No parameter/return type inference. GUI accepts manual overrides.

---

### 5.5 Import/Export Resolution (`file_format.h`)

**Capabilities**:
- Import symbol extraction: PE IAT, ELF `.dynsym`
- Export symbol extraction: PE EAT, ELF `.symtab`
- Symbol metadata: name, address, binding (LOCAL, GLOBAL, WEAK), type (FUNCTION, OBJECT, IMPORT, EXPORT)
- Name demangling: C++ via `__cxa_demangle()` (GCC Runtime Exception)

**Implementation**: `src/parser/elf_parser.c`, `src/parser/pe_parser.c`, `src/parser/macho_parser.c`

---

## 6. TYPE INFERENCE & ANALYSIS

### 6.1 Type Inference (`decompiler.h` → `ir_infer_types()`)

**Capabilities**:
- Register-size-based types:
  - INT8 (al, bl, ...)
  - INT16 (ax, bx, ...)
  - INT32 (eax, ebx, ...)
  - INT64 (rax, rbx, ...)
- Pointer inference: LEA patterns, memory dereference heuristics
- Boolean inference: CMP/TEST results
- Floating-point: Partial (FLOAT, DOUBLE, LONG_DOUBLE for XMM/x87)
- Propagation rules: COPY, arithmetic, PHI (φ-function)

**Scope**: IR-level only (post-SSA); no binary-level type propagation

**Implementation**: `src/decompiler/ir_type_inference.c`

---

### 6.2 Struct/Union Layout Recovery

**NOT IMPLEMENTED** — No field offset analysis, aggregate type synthesis.

---

### 6.3 Pointer Analysis

**VERY LIMITED**:
- LEA-based pointer detection in type inference
- No points-to analysis (may-alias, must-alias)
- No memory access pattern clustering

---

## 7. DECOMPILATION & HIGH-LEVEL SYNTHESIS

### 7.1 IR Generation (`decompiler.h` → `ir_lift()`)

**Capabilities**:
- Machine code → SSA intermediate representation
- Operation types (IrOpcode):
  - Value movement: COPY, CONST
  - Arithmetic: ADD, SUB, MUL, DIV
  - Bitwise: AND, OR, XOR, SHL, SHR
  - Comparison: CMP_EQ, CMP_NE, CMP_LT, CMP_LE
  - Memory: LOAD, STORE
  - Control: BRANCH, JUMP, CALL, RET
  - SSA: PHI
- Type system (IrType): INT8/16/32/64, PTR, BOOL, FLOAT, DOUBLE, LONG_DOUBLE
- SSA value IDs: per-function global unique IDs

**Implementation**: `src/decompiler/ir_lifter.c`

---

### 7.2 SSA Form Construction (`ir_build_ssa()`)

**Capabilities**:
- Dominance analysis (Cooper et al. 2001)
- Dominance frontier computation (Cytron et al. 1991)
- φ-function insertion at frontier nodes
- Variable renaming (DFS-based)

**Scope**: IR-level; x86/ARM mappings to SSA values

**Implementation**: `src/decompiler/ir_ssa_builder.c`

---

### 7.3 Optimization Passes (`ir_optimize()`)

**Implemented**:
- `IR_OPT_CONST_FOLD`: Constant folding (CONST op CONST → CONST)
- `IR_OPT_COPY_PROP`: Copy propagation (COPY dst=src → use src)
- `IR_OPT_DCE`: Dead code elimination (side-effect-free unreachable ops)

**NOT IMPLEMENTED**:
- Loop-invariant code motion (LICM)
- Common subexpression elimination (CSE)
- Strength reduction
- Redundancy elimination

---

### 7.4 Pseudo-C Code Emission (`ir_emit_pseudoc()`)

**Capabilities**:
- Control structure recovery: if/while/do-while from CFG + PHI analysis
- Variable naming: a0–aN (args), v0–vN (locals) by SSA ID
- Type-aware rendering: INT64, BOOL, PTR, FLOAT, DOUBLE display
- Source-level variable tracking: SSA → pseudo-C variable mapping

**Limitations**:
- No high-level loop recovery (only low-level control flow)
- No aggregate type reconstruction
- No macro/function abstraction

**Implementation**: `src/decompiler/ir_codegen.c`

---

## 8. FILE FORMAT ANALYSIS

### 8.1 ELF Format Support (`elf_parser.h`)

**Capabilities**:
- ELF32 / ELF64 (both little-endian and big-endian, detected automatically)
- Sections: name, virtual address, file offset, size, permission flags (R/W/X)
- Symbol table (`.symtab` and `.dynsym`):
  - Symbol name, address, size
  - Type: FUNCTION, OBJECT, UNKNOWN
  - Binding: LOCAL, GLOBAL, WEAK
  - C++ demangling via `__cxa_demangle()`
- Entry point: e_entry field
- Architecture detection: e_machine mapping → AuraArch

**NOT IMPLEMENTED**:
- DWARF debugging symbols (only symbol table)
- Relocation processing
- Dynamic linking resolution
- PLT/GOT analysis

**Implementation**: `src/parser/elf_parser.c` (custom, no libelf)

---

### 8.2 PE Format Support (`pe_parser.h`)

**Capabilities**:
- PE32 and PE32+ (64-bit)
- Sections: name, virtual address (RVA), raw size, permission flags
- Import Directory Table (IAT):
  - Imported DLL list
  - Imported function names
- Export Directory Table (EAT):
  - Exported function names
  - Export ordinals
- Entry point: AddressOfEntryPoint
- Machine type → AuraArch

**NOT IMPLEMENTED**:
- Export forwarding
- Delay-load imports
- .NET metadata (if IL assembly)
- Resource section analysis
- Certificate/signature verification

**Implementation**: `src/parser/pe_parser.c`

---

### 8.3 Mach-O Format Support (`macho_parser.h`)

**Capabilities**:
- Mach-O 32/64 (LE and BE)
- Fat Binary (Universal Binary) — first architecture parsed
- Load Commands:
  - `LC_SEGMENT` / `LC_SEGMENT_64`: section enumeration
  - `LC_SYMTAB`: symbol table
  - `LC_MAIN`: entry point
- Sections: format = "segname.sectname"
- Symbols: import/export/function classification

**NOT IMPLEMENTED**:
- DWARF sections
- Code signature verification
- Entitlements parsing

**Implementation**: `src/parser/macho_parser.c`

---

### 8.4 Raw Binary Format

**Fallback Mode**: If no recognized magic (ELF/PE/Mach-O), treated as raw binary with base address assumed 0x0000.

---

## 9. BINARY PATCHING & MODIFICATION

### 9.1 Binary Patch Encoding (`patch.h`)

**Capabilities**:
- Assembly string → machine code conversion
- Zydis-based x86/x86_64 encoder
- Supported patterns:
  - `nop` → 0x90
  - `ret` / `retn` → 0xC3
  - `int3` → 0xCC
  - `jmp 0x<hex>` → JMP rel32
  - `call 0x<hex>` → CALL rel32
- Relative offset auto-calculation (rel32)
- In-memory patching: `patch_apply()`

**NOT IMPLEMENTED**:
- ARM/ARM64 encoding
- Complex instruction encoding (lea with complex addressing, etc.)
- Multi-instruction sequences
- Patch undo/rollback

**Implementation**: `src/disasm/zydis_wrapper.c`, `src/core/patch.c`

---

## 10. LLM INTEGRATION

### 10.1 Backend Support (`llm.h`)

**Supported Backends**:
- **LM Studio** (local): `http://localhost:1234/v1`
  - Model: `qwen/qwen3-coder-next` (default)
- **llama.cpp** (local): `http://localhost:8080/v1`
- **OpenAI API**: GPT-4o (with API key)
- **Groq API**: llama-3.3-70b-versatile (with API key)

**Capabilities**:
- Chat completion interface (abstract backend)
- Temperature control (0.0–2.0)
- Max token limit
- Timeout configuration

**Implementation**: `src/llm/llm_client.c`, `src/llm/lmstudio_client.c`, etc.

---

### 10.2 LLM-Assisted Analysis

**Prompt Templates** (`llm.h` → `llm_prompt_build()`):
- `LLM_PROMPT_FUNC_NAME`: Function naming suggestion (disasm input → function name JSON output)
- `LLM_PROMPT_CODE_SUMMARY`: Code summary (pseudo-C input → summary text)

**Scope**: Phase 6+ (local LLM), Phase 7+ (cloud APIs)

**NOT IMPLEMENTED**:
- Parameter/return type inference via LLM
- Vulnerability analysis via LLM
- Cryptographic pattern recognition
- Taint analysis

---

### 10.3 Response Caching

**Capabilities** (`llm_cache_*`):
- SHA256-based cache keys (model + prompt + temperature)
- On-disk cache (default: `~/.cache/aura/llm/`)
- Hit/miss tracking

---

## 11. PROGRAM ANALYSIS (NOT IMPLEMENTED)

| Feature | Status | Notes |
|---------|--------|-------|
| Taint Analysis | ❌ | No source/sink marking |
| Constant Propagation | ❌ | Only in IR optimization (const fold) |
| Value Set Analysis (VSA) | ❌ | No abstract domain implementation |
| Interval Analysis | ❌ | No bounds tracking |
| Memory Alias Analysis | ❌ | No may-alias/must-alias computation |
| Pointer Analysis | ⚠️ Partial | LEA heuristics only |
| Escape Analysis | ❌ | No stack vs. heap tracking |
| Loop Analysis | ❌ | No natural loop hierarchy |
| Dominance Analysis | ✅ IR-level | Not at binary level |
| Anti-dependence Analysis | ❌ | No dependence graph construction |

---

## 12. GUI FEATURES (Phase 8)

### 12.1 Implemented Analysis UIs

- **Disassembly View** (read-only, 100K line capacity)
- **Hex Dump** (read-only, all bytes)
- **Decompilation View** (IR-generated pseudo-C)
- **Function Panel** (tree; click→disasm sync)
- **Symbol Panel** (searchable by name)
- **Search Bar** (address/symbol/string queries)
- **Navigation History** (Back/Forward)
- **Undo/Redo** (QUndoStack)
- **Console Panel** (debug/analysis output)
- **Command Palette** (Ctrl+P)
- **LLM Panel** (UI shell; backend not integrated into workflow)

### 12.2 NOT IMPLEMENTED (Ghidra-like)

- **Collaborative Analysis** (multi-user, comment threads)
- **Breakpoints** (static; live debugging not supported)
- **Dynamic Analysis** (no runtime instrumentation)
- **Bookmark/Annotation System** (full)
- **Version Control** (within tool, not external git)
- **Script Console** (no Python/Jython support)
- **Versioning/Snapshots** (basic SessionManager only)

---

## 13. COMPARISON AGAINST GHIDRA 12

| Category | AURA | Ghidra | Status |
|----------|------|--------|--------|
| **Disassembly** | Capstone-based linear | Recursive recursive disasm | ✅ Basic feature parity |
| **CFG Recovery** | Intra-procedural | Intra/inter-procedural | ⚠️ Limited (no inter-proc) |
| **Reaching Def Analysis** | ✅ Register-level | Variable-level | ✅ Register-scope only |
| **SSA Form** | ✅ IR-level | Binary-level | ⚠️ IR-only, not source-level |
| **Dataflow** | DFG reach-def | Comprehensive (liveness, may-alias) | ⚠️ Minimal |
| **Type Inference** | Register-size heuristic | Type propagation DB | ⚠️ Limited |
| **Decompilation** | Pseudo-C from IR | High-quality C code | ⚠️ Basic output |
| **SMT Solving** | Concrete values only | Z3 integration | ❌ Not implemented |
| **Plugin System** | None | Java plugin API | ❌ Phase 11+ |
| **Scripting** | None | Python/Jython | ❌ Phase 11+ |
| **Collaborative** | None | Shared databases | ❌ Not planned |
| **ELF Support** | ✅ Full | ✅ Full | ✅ Parity |
| **PE Support** | ✅ Basic | ✅ Advanced | ⚠️ No resource/cert |
| **Mach-O Support** | ✅ Basic | ✅ Full | ⚠️ No dwarf/codesig |
| **DWARF Symbols** | ❌ No | ✅ Yes | ❌ Not implemented |

---

## 14. WHAT AURA CAN DO

### Binary Analysis Workflows

1. **Fast Triage**:
   - Load binary (ELF/PE/Mach-O)
   - View metadata (architecture, entry, sections, imports/exports)
   - Linear disassembly of `.text` section
   - Function boundary heuristics + call graph

2. **Function-Level Analysis**:
   - CFG recovery for single function
   - Data flow (reaching definitions per register)
   - SSA IR lifting + optimization
   - Pseudo-C pseudo-code generation

3. **LLM-Assisted Naming** (Phase 6+):
   - Feed disasm → LLM → function name suggestion
   - Feed pseudo-C → LLM → code summary

4. **Patching & Modification**:
   - Encode x86/x86_64 assembly instructions
   - In-memory patch application

### Scope Limitations

- **No inter-procedural analysis** (function calls modeled as black-box)
- **No SMT constraint solving** (path feasibility not solved)
- **No advanced data-flow** (liveness, may-alias, taint)
- **No DWARF symbol support** (only symbol table)
- **GUI-only** (CLI for debug validation only; no headless batch mode)

---

## 15. WHAT AURA CANNOT DO (vs. Ghidra)

| Ghidra Feature | AURA Capability | Roadmap |
|----------------|-----------------|---------|
| High-quality decompilation | Basic pseudo-C | Possible in Phase 11 w/ LLM refinement |
| Struct field recovery | None | Phase 11+ |
| Type libraries / FLIRT | None | Future research |
| Collaborative analysis | None | Not planned (client tool focus) |
| Script automation (Python) | None | Phase 11+, low priority |
| Debugger integration | None | Not planned (reverse engineering focus) |
| Patch diffing | Single-file patching only | Phase 11+ |
| Bulk binary analysis | None (GUI only) | Phase 11 (batch CLI mode) |
| Yara rule integration | None | Phase 11+ |
| Emulation-assisted analysis | None | Low priority |

---

## 16. ARCHITECTURE ROADMAP

```
Phase 8 (Current): GUI MVP
├─ 8.1-8.29: [x] All implemented
└─ 8.T: [x] Integration test

Phase 9: Integration Testing

Phase 10: Documentation & Release

Phase 11: Extended Capabilities (Optional)
├─ 11.1-11.3: Advanced analysis (loop analysis, CSE, etc.)
├─ 11.4: Batch CLI mode (headless)
├─ 11.5: Script engine (if demand exists)
└─ 11.6: Collaborative features (if demand exists)
```

---

## 17. Conclusions

**AURA MVP Strengths**:
1. ✅ Fast binary loading & metadata extraction (multi-format)
2. ✅ Accurate CFG recovery (single-function)
3. ✅ SSA-based IR generation & optimization
4. ✅ Type inference (register-size heuristic)
5. ✅ LLM integration for function naming / code summary
6. ✅ Lightweight, native performance
7. ✅ Qt6-based GUI with modern UX (dark/light theme, command palette, undo/redo)

**AURA MVP Gaps vs. Ghidra**:
1. ❌ No inter-procedural analysis (limits large-program reasoning)
2. ❌ No SMT solving (path feasibility not considered)
3. ❌ Limited data-flow (only reaching definitions)
4. ❌ Basic decompilation (pseudo-C, not high-level C)
5. ❌ No scripting/automation (GUI-only MVP)
6. ❌ No DWARF debug symbols
7. ❌ No plugin system

**Suitable Use Cases**:
- **Fast binary triage** (format detection, entry point, exports)
- **Function-level analysis** (CFG, data flow, basic decompilation)
- **Vulnerability research** (when targeting small functions)
- **Malware identification** (function signature generation + LLM naming)
- **RE education** (clean architecture, good for learning)

**NOT Suitable For**:
- Large-scale enterprise reverse engineering (Ghidra better)
- Interactive debugging (not a debugger)
- Fully automated analysis (no batch mode in MVP)
- Complex type recovery (limited struct inference)

---

## Appendix: Public API Surface by Module

| Module | Header | Key Functions | Lines |
|--------|--------|---|---|
| disasm | `disasm.h` | disasm_init, disasm_run, disasm_arch_from_string | ~140 |
| parser | `elf_parser.h`, `pe_parser.h`, `macho_parser.h`, `file_format.h` | elf/pe/macho_parser_load, file_info_create, symbol_display_name | ~270 |
| func_detect | `func_detect.h` | func_detect, func_detect_destroy, func_detect_print | ~150 |
| cfg | `cfg.h` | cfg_build, cfg_destroy, cfg_print_text, cfg_print_dot | ~145 |
| dfg | `dfg.h` | dfg_analyze, dfg_destroy, dfg_get_def, dfg_get_use | ~150 |
| decompiler | `decompiler.h` | ir_lift, ir_build_ssa, ir_optimize, ir_emit_pseudoc, ir_infer_types | ~360 |
| patch | `patch.h` | patch_encode, patch_context_new, patch_apply | ~90 |
| symbolic | `symbolic.h` | sym_engine_create, sym_step, sym_state_clone | ~210 |
| llm | `llm.h` | llm_client_create_*, llm_client_chat, llm_cache_*, llm_prompt_build | ~335 |
| pipeline | `pipeline.h` | aura_disasm_file, aura_info_file, aura_cfg_func, aura_functions_file, aura_callgraph_file | ~100 |
| **TOTAL** | **10 headers** | **60+ public functions** | **~1,950 LOC (headers)** |

---

**End of Analysis Report**
