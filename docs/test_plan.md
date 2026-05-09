# AURA Integration Test Plan

> Task 2.T -- Integration test design (formerly Phase 9.1)
> Author: qa-engineer (AI)
> Date: 2026-04-04
> Status: Active

---

## 1. Overview

This document defines the integration test strategy for AURA v0.1.0 MVP.
Integration tests verify that independently developed modules work correctly
when composed into end-to-end pipelines. They complement the existing 20 unit
tests (Phase 2--8) which validate individual module behavior.

**Scope:** Modules under test

| Module | Phase | Key API |
|--------|-------|---------|
| File parser (ELF/PE/Mach-O) | 3 | `elf_parser_load()`, `pe_parser_load()`, `macho_parser_load()` |
| Disassembler (Capstone) | 2 | `disasm_init()`, `disasm_run()` |
| Symbolic analysis (CFG/DFG/FuncDetect) | 4 | `cfg_build()`, `dfg_analyze()`, `func_detect()` |
| Decompiler (SSA IR, Pseudo-C) | 5 | `ir_lift()`, `ir_build_ssa()`, `ir_emit_pseudoc()` |
| Binary patch (Zydis) | 5.7 | `patch_apply()` |
| LLM integration (local + cloud) | 6--7 | `llm_client_chat()`, `llm_prompt_build()`, `llm_cache_*()` |
| Pipeline (high-level) | 2.4 | `aura_disasm_file()`, `aura_info_file()`, `aura_cfg_func()` |
| GUI (Qt6) | 8 | Manual verification (E2E scenarios in 8.T) |

**Test environment:**
- Platform: Linux aarch64 (NVIDIA DGX)
- Compiler: GCC/Clang with C11/C++17
- Build types: Release + ASAN Debug
- LM Studio: `http://localhost:1234/v1` (model: `openai/gpt-oss-20b`)
- Historical MVP ctest baseline: 20/20 PASS
- Current local release gate: `build-trim-gui` Release, 12/12 PASS as of 2026-05-09

---

## Local Release Gate

Use the release-gate wrapper before merging or shipping a branch:

```powershell
.\scripts\verify_release_gate.ps1
```

The wrapper intentionally rebuilds `probe_unit` and `mcp_unit` before the full CTest pass. Running raw `ctest` first can execute stale test binaries when only a subset of targets was rebuilt.

Expected current `build-trim-gui` Release result:

```text
100% tests passed, 0 tests failed out of 12
```

---

## 2. Test Binaries

| ID | File | Format | Arch | Size | Purpose |
|----|------|--------|------|------|---------|
| B1 | `tests/disasm/data/test_x86_64.elf` | ELF64 | x86_64 | small | CFG/DFG/decompile pipeline |
| B2 | `tests/disasm/data/test_multi_func` | ELF64 | AArch64 | ~65K insn | Multi-function, stripped symbols |
| B3 | `tests/disasm/data/x86_64_basic.bin` | Raw x86 | x86 | tiny | Raw disassembly |
| B4 | `/bin/ls` | ELF64 | AArch64 | ~140K | Real-world stripped PIE binary |
| B5 | `build/aura` | ELF64 | AArch64 | ~4.9M | Large, not stripped, self-analysis |
| B6 | `build/aura-gui` | ELF64 | AArch64 | ~6.4M | Largest available binary |
| B7 | (generated) | PE | x86 | synthetic | PE parser integration |
| B8 | (generated) | Mach-O | x86_64 | synthetic | Mach-O parser integration |

---

## 3. Integration Test Scenarios

### S01: ELF x86_64 -- Full analysis pipeline

**Modules:** File parser + Disassembler + CFG + DFG + Decompiler

| Item | Detail |
|------|--------|
| **Input** | B1 (`test_x86_64.elf`), function at known entry point (0x400040) |
| **Steps** | 1. `elf_parser_load()` -> FileInfo. 2. Find `.text` section. 3. `disasm_init(AURA_ARCH_X86_64)` -> DisasmContext. 4. `disasm_run()` on `.text`. 5. `cfg_build()` -> Cfg. 6. `dfg_analyze()` -> DfgResult. 7. `ir_lift()` + `ir_build_ssa()` + `ir_optimize()` + `ir_emit_pseudoc()` -> Pseudo-C |
| **Expected** | All API calls return `AURA_OK`. Pseudo-C output contains function signature, variable declarations, and at least one control structure. |
| **Success criteria** | Pipeline completes without crash. Pseudo-C output length > 0. No ASAN errors. |

---

### S02: ELF AArch64 -- Real binary disassembly

**Modules:** File parser + Disassembler + Function detection

| Item | Detail |
|------|--------|
| **Input** | B4 (`/bin/ls`), entire `.text` section |
| **Steps** | 1. `elf_parser_load("/bin/ls")` -> FileInfo (format=ELF, arch=AARCH64). 2. Find `.text` section. 3. `disasm_init(AURA_ARCH_AARCH64)` -> DisasmContext. 4. `disasm_run()` -> instruction count > 0. 5. `func_detect()` -> detected function list. |
| **Expected** | FileInfo.format == `AURA_FORMAT_ELF`, arch == `AURA_ARCH_AARCH64`. Section `.text` found with nonzero size. Disassembly produces > 100 instructions. func_detect finds >= 1 function. |
| **Success criteria** | No segfault, no ASAN errors. All assertions hold. |

---

### S03: ELF AArch64 -- Multi-function decompilation

**Modules:** File parser + Disassembler + CFG + DFG + Decompiler + Function detection

| Item | Detail |
|------|--------|
| **Input** | B2 (`test_multi_func`), all detected functions |
| **Steps** | 1. Load and parse. 2. Detect functions via `func_detect()`. 3. For each detected function: build CFG, DFG, lift to IR, SSA, emit Pseudo-C. |
| **Expected** | At least 2 functions detected. Each produces valid Pseudo-C output (non-empty). No crashes on any function. |
| **Success criteria** | 100% of detected functions produce Pseudo-C without crash. ASAN clean. |

---

### S04: PE file -- Parse and disassemble

**Modules:** Format detector + PE parser + Disassembler

| Item | Detail |
|------|--------|
| **Input** | Synthetic PE binary (generated by test, using test_pe_parser patterns) |
| **Steps** | 1. `aura_detect_format()` -> `AURA_FORMAT_PE`. 2. `pe_parser_load()` -> FileInfo. 3. Verify sections (.text, .data present). 4. `disasm_init(fi->arch)` + `disasm_run()` on .text data. |
| **Expected** | Format correctly detected as PE. At least 2 sections parsed. Disassembly of .text produces instructions (or gracefully handles non-native arch). |
| **Success criteria** | No crash. Format detection correct. Section count >= 2. |

---

### S05: Mach-O file -- Parse and metadata

**Modules:** Format detector + Mach-O parser

| Item | Detail |
|------|--------|
| **Input** | Synthetic Mach-O binary (from test_macho_parser patterns) |
| **Steps** | 1. `aura_detect_format()` -> `AURA_FORMAT_MACHO`. 2. `macho_parser_load()` -> FileInfo. 3. Verify section and symbol extraction. |
| **Expected** | Format correctly detected as Mach-O. FileInfo populated with sections and (if present) symbols. |
| **Success criteria** | No crash. Correct format detection. |

---

### S06: Pipeline high-level API -- aura_info_file (JSON mode)

**Modules:** Pipeline + Format detector + All parsers

| Item | Detail |
|------|--------|
| **Input** | B1 (ELF x86_64), B4 (/bin/ls AArch64) |
| **Steps** | 1. `aura_info_file(path, 1)` (JSON mode) for each binary. 2. Capture stdout. 3. Validate JSON structure. |
| **Expected** | Valid JSON output containing: format, architecture, entry_point, sections array, symbols array. |
| **Success criteria** | JSON parseable. Key fields present and non-null. No crash. |

---

### S07: Call graph generation -- end-to-end

**Modules:** Pipeline + Disassembler + Function detection + Callgraph

| Item | Detail |
|------|--------|
| **Input** | B2 (`test_multi_func`) |
| **Steps** | 1. `aura_callgraph_file(path, 1)` (DOT mode). 2. Capture stdout. 3. Validate DOT format. |
| **Expected** | Output starts with `digraph`. Contains node declarations and edge declarations. At least 2 nodes. |
| **Success criteria** | Valid DOT syntax. Node count >= 2. No crash. |

---

### S08: Binary patch -- round-trip verification

**Modules:** File parser + Disassembler + Patch (Zydis) + Disassembler (re-verify)

| Item | Detail |
|------|--------|
| **Input** | B1 (`test_x86_64.elf`), patch address 0x400040 |
| **Steps** | 1. Load ELF, read original bytes at 0x400040. 2. `patch_apply(0x400040, "nop")` -> patched bytes. 3. Disassemble patched bytes. 4. Verify disassembly shows `nop`. 5. `patch_apply(0x400040, "jmp 0x400050")` -> patched bytes. 6. Disassemble and verify `jmp` target. |
| **Expected** | Patched bytes match expected encoding. Re-disassembly produces the expected mnemonic. |
| **Success criteria** | Round-trip: assemble -> disassemble matches original intent. No ASAN errors. |

---

### S09: LLM integration -- function name suggestion

**Modules:** LLM client + Prompt templates + Cache

| Item | Detail |
|------|--------|
| **Input** | Disassembly text of a simple function (from B1 or B2) |
| **Steps** | 1. `llm_global_init()`. 2. `llm_client_create_lmstudio(NULL, NULL)`. 3. `llm_prompt_build(LLM_PROMPT_FUNC_NAME, disasm_text, &req)`. 4. `llm_client_chat(client, &req, &resp)`. 5. `llm_prompt_parse_func_name(resp.content, name, sizeof(name))`. 6. Verify name is non-empty. 7. Repeat same request -- verify cache hit. |
| **Expected** | LLM returns a valid response. Parser extracts a non-empty function name. Second request served from cache. |
| **Success criteria** | `resp.error == AURA_OK`. Parsed name length > 0. Cache hit confirmed on retry. No memory leaks. |
| **Note** | Requires LM Studio running at localhost:1234. Skip if unavailable. |

---

### S10: LLM integration -- code summary

**Modules:** LLM client + Prompt templates + Decompiler output

| Item | Detail |
|------|--------|
| **Input** | Pseudo-C output from S01 decompilation |
| **Steps** | 1. Generate Pseudo-C from S01 pipeline. 2. `llm_prompt_build(LLM_PROMPT_CODE_SUMMARY, pseudoc, &req)`. 3. `llm_client_chat(client, &req, &resp)`. 4. `llm_prompt_parse_summary(resp.content, summary, sizeof(summary))`. |
| **Expected** | Summary is a non-empty human-readable text describing the function. |
| **Success criteria** | `resp.error == AURA_OK`. Summary length > 10 characters. No crash. |
| **Note** | Requires LM Studio running at localhost:1234. Skip if unavailable. |

---

### S11: LLM error handling -- server unavailable

**Modules:** LLM client

| Item | Detail |
|------|--------|
| **Input** | Intentionally invalid URL (`http://localhost:59999/v1`) |
| **Steps** | 1. `llm_client_create_lmstudio("http://localhost:59999/v1", NULL)`. 2. `llm_query(client, "test", "test", &resp)`. 3. Check error code. |
| **Expected** | `resp.error != AURA_OK`. `resp.error_msg` contains meaningful text. No crash or hang (timeout within LLM_DEFAULT_CONNECT_SEC). |
| **Success criteria** | Graceful error return within 10 seconds. No segfault. |

---

### S12: Large binary -- self-analysis performance

**Modules:** File parser + Disassembler + Function detection

| Item | Detail |
|------|--------|
| **Input** | B5 (`build/aura`, ~4.9MB ELF AArch64) |
| **Steps** | 1. Time: `elf_parser_load()`. 2. Time: `disasm_run()` on .text. 3. Time: `func_detect()`. 4. Record total wall time. |
| **Expected** | Total analysis completes within 60 seconds (PRD 8.T DoD: 1MB < 60s, this is ~5MB so proportional). |
| **Success criteria** | Completes without crash. Wall time recorded for benchmark. |

---

### S13: Cross-format -- format auto-detection accuracy

**Modules:** Format detector

| Item | Detail |
|------|--------|
| **Input** | B1 (ELF), B7 (PE), B8 (Mach-O), random data file |
| **Steps** | 1. `mapped_file_open()` for each. 2. `aura_detect_format()` for each. 3. Verify correct format enum. 4. For random data, verify `AURA_FORMAT_RAW`. |
| **Expected** | ELF -> `AURA_FORMAT_ELF`, PE -> `AURA_FORMAT_PE`, Mach-O -> `AURA_FORMAT_MACHO`, random -> `AURA_FORMAT_RAW`. |
| **Success criteria** | 4/4 correct detections. |

---

## 4. Test Implementation Plan

| Scenario | Task | Test file |
|----------|------|-----------|
| S01--S03 | 2.T | `tests/integration/test_disasm_parser.c` |
| S04--S05 | 2.T | `tests/integration/test_disasm_parser.c` |
| S06--S07 | 2.T | `tests/integration/test_disasm_parser.c` |
| S08 | 2.T | `tests/integration/test_disasm_parser.c` |
| S09--S11 | 6.T | `tests/integration/test_llm_integration.c` |
| S12 | 8.T | `docs/benchmark.md` (timing script) |
| S13 | 2.T | `tests/integration/test_disasm_parser.c` |
| GUI E2E | 8.T | `docs/test_report.md` (manual scenarios) |

---

## 5. Non-Functional Requirements

### 5.1 Memory Safety

All integration tests must pass under AddressSanitizer (ASAN) with zero errors.
Build command: `cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fsanitize=address" -DCMAKE_CXX_FLAGS="-fsanitize=address"`

### 5.2 Performance Targets (PRD Section 5)

| Metric | Target | Measured in |
|--------|--------|-------------|
| ELF 100MB initial analysis | <= 30 min | 8.T |
| ELF 500MB initial analysis | <= 2 hr | 8.T |
| UI response during analysis | <= 100ms | 8.T (manual) |
| 1MB binary full analysis | <= 60 sec | 8.T |

### 5.3 Error Handling

- All crash paths must produce a meaningful error message (not segfault)
- LLM server unavailability must be handled gracefully (timeout + error return)
- Corrupt/truncated binary files must return error code, not crash

---

## 6. GUI E2E Scenarios (Task 8.T)

Manual test scenarios to be recorded in `docs/test_report.md`:

| # | Scenario | Steps | Expected |
|---|----------|-------|----------|
| G1 | File load and analysis | Open aura-gui -> New Project -> Load /bin/ls -> verify disasm view populated | Disassembly table shows instructions |
| G2 | Decompile view sync | Click function in Fn panel -> verify disasm jumps to address -> verify decompile view updates | Both views synchronized |
| G3 | LLM analysis | Select function -> click "Summarize" in LLM panel -> verify response | LLM response appears in panel |
| G4 | Export | File -> Export -> select ASM format -> verify file content | Valid ASM export file |
| G5 | Search | Ctrl+G -> search by address -> verify navigation | Navigates to correct address |
| G6 | Theme switch | Edit -> Toggle Theme -> verify UI updates | Theme changes without crash |
| G7 | Project save/restore | Ctrl+S -> close -> reopen project -> verify state | Bookmarks, renames, comments preserved |

---

## 7. Test Execution Order

```
2.T design (this document)
  |
  +-- 2.T (S01-S08, S13: disasm + parser integration tests)
  |
  +-- 6.T (S09-S11: LLM integration tests)
       |
       +-- 8.T (G1-G7: GUI E2E manual tests)
             |
             +-- 8.T (S12 + extended benchmarks)
             |
             +-- 1.T (logger module + ASAN/Valgrind sweep)
                   |
                   +-- Integration gate (final: all Phase .T pass)
```

---

## 8. Exit Criteria (Integration Gate)

Integration testing is complete when:
1. All automated integration tests (S01-S13) pass in both Release and ASAN builds
2. All GUI E2E scenarios (G1-G7) pass (manual verification recorded)
3. Performance benchmarks meet PRD targets (or deviations documented)
4. ASAN: 0 errors across all test paths
5. ctest: all tests pass (unit + integration)
6. Results recorded in `tests/results/8.T_system.txt`
