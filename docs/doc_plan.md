# AURA Documentation Plan

> Task R.1 -- Documentation structure and assignment (formerly Phase 10.1)
> Author: qa-engineer (AI)
> Date: 2026-04-04

---

## 1. Current `docs/` Structure

```
docs/
├── design/                      # Architecture/design documents (existing)
│   ├── decompiler.md
│   ├── disasm.md
│   ├── gui.md
│   ├── llm_integration.md
│   ├── parser.md
│   ├── symbolic_exec.md
│   └── archive/                 # Superseded design iterations
│       ├── phase3_fileinfo_design.md
│       ├── phase3_section_symbol_design.md
│       ├── phase3_section_symbol_fields.md
│       └── phase3_section_symbol_final.md
├── benchmark.md                 # Performance benchmark results (8.T)
├── env_check.md                 # Environment setup verification
├── test_plan.md                 # Integration test plan (2.T)
├── test_report.md               # GUI E2E test report (8.T)
└── .gitkeep
```

## 2. Target `docs/` Structure (Release R Complete)

```
docs/
├── design/                      # [EXISTING] Architecture/design docs
│   └── (unchanged)
├── api/                         # [NEW] Doxygen-generated HTML (R.3)
│   └── html/                    # Auto-generated, in .gitignore
├── user_guide.md                # [NEW] User manual (R.2)
├── benchmark.md                 # [EXISTING] Benchmark results
├── test_plan.md                 # [EXISTING] Integration test plan
├── test_report.md               # [EXISTING] GUI E2E report
├── env_check.md                 # [EXISTING] Environment setup
├── doc_plan.md                  # [THIS FILE] Documentation plan
└── .gitkeep
```

Root-level additions:
```
CHANGELOG.md                     # [NEW] Keep a Changelog format (R.6)
Doxyfile                         # [NEW] Doxygen configuration (R.3)
Dockerfile                       # [NEW] Build environment image (R.4)
packaging/                       # [NEW] .deb + tarball scripts (R.5)
```

## 3. Document List and Assignment

| # | Document | Task | Method | Notes |
|---|----------|------|--------|-------|
| D1 | `docs/user_guide.md` | R.2 | AI-generated | Installation, CLI usage, GUI walkthrough, LLM integration. ASCII diagrams for layout. |
| D2 | `Doxyfile` | R.3 | AI-generated | Configure for `include/*.h` (17 headers). Output to `docs/api/`. |
| D3 | Doxygen comments in `include/*.h` | R.3 | AI-generated | Add `@brief`, `@param`, `@return` to all public APIs. Headers already have partial docs. |
| D4 | `docs/api/` HTML | R.3 | Auto-generated | `doxygen Doxyfile` output. Added to `.gitignore`. |
| D5 | `Dockerfile` | R.4 | AI-generated | Multi-stage: build stage (gcc, cmake, qt6, capstone, zydis) + runtime stage. |
| D6 | `packaging/` scripts | R.5 | AI-generated | `build_deb.sh` for .deb, `build_tarball.sh` for source tarball. CMake CPack integration. |
| D7 | `CHANGELOG.md` | R.6 | AI-generated | Keep a Changelog format. Covers v0.1.0 features from Phase 1-8. |
| D8 | GitHub Release v0.1.0 | R.6 | AI + manual | `gh release create` with build artifacts. Requires user approval for push. |

### Existing Documents (no changes needed)

| Document | Status |
|----------|--------|
| `docs/design/*.md` (6 files) | Complete -- architecture docs from Phase 2-8 |
| `docs/benchmark.md` | Complete -- Task 8.T benchmark results |
| `docs/test_plan.md` | Complete -- Task 2.T integration test plan |
| `docs/test_report.md` | Complete -- Task 8.T GUI E2E report |
| `docs/env_check.md` | Complete -- environment setup |
| `PRD.md` | Complete -- product requirements |
| `Tasks.md` | Active -- task tracking |
| `rules.md` | Complete -- development rules |

## 4. Public Headers for Doxygen (R.3 Scope)

17 headers in `include/`:

| Header | Module | Key APIs |
|--------|--------|----------|
| `aura_version.h` | Core | Version macros |
| `cfg.h` | Symbolic | `cfg_build()`, `Cfg`, `CfgBlock` |
| `decompiler.h` | Decompiler | `ir_lift()`, `ir_build_ssa()`, `ir_emit_pseudoc()`, `IrFunc` |
| `demangle.h` | Core | `aura_demangle()` |
| `dfg.h` | Symbolic | `dfg_analyze()`, `DfgResult` |
| `disasm.h` | Disasm | `disasm_init()`, `disasm_run()`, `DisasmResult` |
| `elf_parser.h` | Parser | `elf_parser_load()` |
| `file_format.h` | Parser | `FileInfo`, `Section`, `Symbol`, `MappedFile` |
| `func_detect.h` | Symbolic | `func_detect()`, `FuncEntry`, `FuncList` |
| `llm.h` | LLM | `LlmClient`, `llm_client_chat()`, `llm_prompt_build()` |
| `logger.h` | Core | `aura_log()`, `AURA_LOG_D/I/W/E` |
| `macho_parser.h` | Parser | `macho_parser_load()` |
| `mapped_file.h` | Parser | `mapped_file_open()`, `MappedFile` |
| `patch.h` | Disasm | `patch_encode()`, `PatchResult` |
| `pe_parser.h` | Parser | `pe_parser_load()` |
| `pipeline.h` | Core | `aura_disasm_file()`, `aura_info_file()`, `aura_cfg_func()` |
| `symbolic.h` | Symbolic | `symbolic_exec()` |

## 5. Task Execution Order

```
R.1 (this plan) -----> DONE
  |
  +-- R.2 (user_guide.md) -----> can start immediately
  |
  +-- R.3 (Doxygen) -----------> can start immediately (parallel with R.2)
  |
  +-- R.4 (Dockerfile) --------> can start immediately (parallel, depends on 1.T)
        |
        +-- R.5 (packaging) ---> after R.2, R.3, R.4
              |
              +-- R.6 (release) -> after R.5
                    |
                    +-- R.T (final gate) -> after R.6
```

## 6. Conventions

- All new documentation in English (code comments already English).
- Markdown format for all text docs.
- Doxygen comments use `/** ... */` style with `@brief`, `@param`, `@return`.
- `docs/api/` directory added to `.gitignore` (generated output).
- CHANGELOG follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) format.
- Dockerfile uses multi-stage build for minimal runtime image.
