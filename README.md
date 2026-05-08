# AURA: AI-powered Unified Reverse Analyzer

![Build](https://github.com/starwinde/AURA-AI-powered-Unified-Reverse-Analyzer/actions/workflows/build.yml/badge.svg)
![Version](https://img.shields.io/badge/version-2.0.0-blue)
![License](https://img.shields.io/badge/license-Apache%202.0-green)
![Tests](https://img.shields.io/badge/tests-122%2F122%20PASS-green)

**High-performance reverse engineering tool built with C/C++ native implementation and LLM integration.**

우리는 바이브 리버싱을 고려한 리버스 엔지니어링 환경을 제공하고자 합니다.

AURA provides binary analysis, disassembly, and decompilation at native performance. It implements all 15 Phase-12 analyzer feature categories (a project-internal milestone); overall Ghidra parity as assessed by adversarial review on 2026-04-16 is approximately **45%** (see `AUTOMATION_ROADMAP.md` and the δ bundle roadmap). On the most recent apples-to-apples function-detection comparison (2026-04-07, stripped 4.7 MB self-binary), AURA scored **F1 = 0.9227** in 115 ms vs Ghidra 11.3.1's F1 = 0.8445 in 11,360 ms (**99× faster**, `docs/benchmark.md:160`). The current internal baseline (2026-04-14, 5.1 MB build) reports AURA **F1 = 0.9728** (`tests/benchmark/baselines/aura_stripped.json`); no paired Ghidra re-measurement exists at the newer binary size. On 689 MB `libjvm.so` function detection, AURA completes in **3.47 s vs Ghidra's 605 s (174× faster)** — note Ghidra still wins on F1 for this binary (0.9931 vs 0.6665); AURA's advantage there is throughput, not accuracy. On stripped C++ binaries of this class, function-boundary precision drops to ~0.50 due to vtable over-detection (tracked as RC-4 in the δ bundle). AURA's full-analysis time on libjvm is **4.74 s** (`docs/benchmark.md:98`), but we do not currently publish a paired Ghidra full-analysis number.

> **Status**: **v2.0.0 released (2026-04-17, major bump)**. Breaking change: the `aura_python` CPython embedding and GUI "Script Manager" action have been removed to restore PRD §4.1 (C/C++ only) and §8 (Python/scripting plugin interface is Out of Scope) alignment (V1.1.x-R R-6). This release also closes the full V1.1.x-R defect sweep — R-1/R-4 (ir_build_ssa unreachable-block SIGSEGV), R-1-asan (arm64_lifter realloc-after-borrow UAF), R-2a/R-2b (HIR bare-integer deref + self-referential CALL arg-count), R-3 (stripped relocatable FDE adjacent-function merge), and R-5 (ehframe AddrSet/CandidateSet type mismatch) are all fixed. Current `ctest` on both `build-rel` and `build-asan` is **122/122 PASS** on both configs. V1.1.x-R 전체 해소 (R-1/R-4/R-1-asan/R-2a/R-2b/R-3/R-5/R-6).

---

## Highlights

Benchmarks on ARM64 (DGX Spark). Canonical baseline is `tests/benchmark/baselines/aura_stripped.json` (2026-04-14, commit 132d8ce). Per-row provenance in footnotes.

| Metric | AURA | Ghidra | Source |
|--------|------|--------|--------|
| Function detection F1 (2026-04-07 apples-to-apples, 4.7 MB stripped self) | **0.9227**² | 0.8445² (Ghidra 11.3.1, 99× slower) | ² docs/benchmark.md:160 |
| Function detection F1 (2026-04-14 baseline, 5.1 MB stripped self) | **0.9728**¹ | — (no paired Ghidra re-measure at this size) | ¹ tests/benchmark/baselines/aura_stripped.json |
| Function detection Precision / Recall (baseline) | 0.9796 / 0.9661¹ | — | ¹ |
| Detection time (5.1 MB stripped) | **190 ms**¹ | — | ¹ |
| Function detection on 689 MB libjvm (stripped) | **3.47 s** (F1 0.6665)³ | 605 s (F1 0.9931) — 174× faster but lower F1³ | ³ docs/benchmark.md:162 (2026-04-07) |
| Function detection on 109 MB libLLVM-15 | **8.70 s**⁴ | 612.9 s (70×)⁴ | ⁴ docs/benchmark.md:165 |
| Full analysis (disasm + CFG + symbols) on 689 MB libjvm | **4.74 s**⁸ | — (no paired Ghidra full-analysis number) | ⁸ docs/benchmark.md:98 |
| Full analysis on 109 MB libLLVM-15 | **10.31 s**⁸ | — | ⁸ docs/benchmark.md:102 |
| Phase-12 analyzer-feature milestone (internal scope, not overall Ghidra parity) | **15/15 (100%)**⁵ | — | ⁵ tests/results/12.T_ghidra_parity.txt:73 |
| Overall Ghidra parity (external adversarial estimate, 2026-04-16) | **~45%** | 100% (reference) | External assessment, not reproduced in-repo. See `AUTOMATION_ROADMAP.md` Phase C/D targets for verifiable baselines. |
| Decompiler variable reduction | **72.7%**⁶ | N/A | ⁶ tests/results/5.T_decompiler_v2.txt:118 |
| Decompiler goto rate | **0%**⁶ | N/A | ⁶ tests/results/5.T_decompiler_v2.txt:119 |
| Optimization passes | **16**⁷ | ~25 | ⁷ src/decompiler/codegen.c:2009-2049 |

A separate 2026-04-16 re-measurement against Ghidra 12.0.4 on the *current* build reported AURA F1=0.9964 vs Ghidra F1=0.8866 and a 190× speedup, but used AURA's own unstripped output as ground truth. That measurement is a **provisional internal sanity check** and is **not** the headline figure — see `tests/results/ghidra_parity/2026-04-16_func_detection.json` for the circularity disclosure.

---

## Features

### Core Analysis
- **Disassembly** — x86, x86_64, ARM, AArch64 are end-to-end validated via Capstone 5.x (`src/disasm/capstone_wrapper.c`). MIPS, PowerPC, RISC-V, Dalvik, and MSIL are declared in `AuraArch` but the Capstone backend wiring is not yet in place (tracked as RC-3 in the δ bundle / Phase C follow-up).
- **File formats** — ELF, PE, Mach-O, DEX (Android), .NET, Firmware/ROM (custom parsers, no libelf)
- **Debug info** — DWARF, PDB, `.eh_frame`/`.gcc_except_table`, SEH
- **Analysis** — Xref backend, full recursive disassembly, indirect call resolution, non-returning detection, inline function detection, calling convention auto-detection, FLIRT signatures, binary diff, alias analysis, taint analysis, stack frame analysis
- **Relocation** — Full ELF `.rela.*` + PE `.reloc` processing

### Decompiler (SSA + HIR)
- **2-level IR** — Machine-close SSA IR → High-level IR (HIR) → Pseudo-C
- **16 optimization passes** (`src/decompiler/codegen.c:2009-2049`) — SCCP, const prop, copy prop, expression simplification, CSE, condition simplification, dead code, dead store, phi elimination, register coalescing, expression reassociation, LICM, strength reduction, tail call, const fold, DCE
- **ARM64-specific lowering** — AAPCS parameter seeding (x0-x7, `src/decompiler/param_id.c`, roadmap C-1), ADRP+ADD/LDR relocation lowering (roadmap B-2), tail-call detection (B-6), zeroing-idiom recognition (B-8)
- **Type system** — Constraint-based TIE inference, struct/array/union recovery, pointer chain tracking, variable name propagation, DWARF/PDB integration
- **Control flow** — Interval-based structural analysis, natural loop detection (while/do-while/for), goto elimination, switch/case recovery
- **Multi-architecture decompilation** — **AArch64 is the primary validated target**. x86, x86_64, ARM, MIPS, PowerPC, RISC-V, and Dalvik lifters exist under `src/decompiler/*_lifter.c`, but the main pipeline dispatch in `src/core/pipeline.c:841-845` is only end-to-end validated for AArch64 at this time.

### LLM Integration
- **4 backends** — LM Studio, llama.cpp, OpenAI API, Groq API
- **Features** — Function naming, code summarization, vulnerability analysis, interactive queries, analysis history
- **Caching** — SHA256-keyed response cache
- **Privacy roadmap** — LLM/agent access is planned to flow through `aura-mcp`,
  a Privacy Filter & Policy Gateway. The target masking system combines a
  PII-specialized detection model with dataset-based detection; the current
  implementation starts from a string-based masking MVP.
- **MCP safety contract** — new analysis/export/automation surfaces must update
  the MCP surface as well. MCP responses use an engine-agnostic schema envelope,
  protected values by default, privileged raw access only with explicit approval
  and audit metadata, and security regression tests for non-disclosure and schema
  stability.

### GUI (Qt6)
- **Views** — Disassembly, Hex, Pseudo-C, CFG graph, Call graph, Stack layout, Debugger
- **Panels** — Functions, Symbols, Strings, Sections, Data Types, Bookmarks, Console, LLM, Collaboration
- **Search** — Active-pane `Ctrl+F` for functions, xrefs, strings, symbols,
  imports, decompile/disassembly panes; byte pattern, wildcard, regex,
  constant, YARA rules, text
- **Tools** — Patch editor, type editor, struct/enum definition, snapshot manager, command palette (Ctrl+P)
- **Theme** — Catppuccin (Dark/Light)

### Infrastructure
- **Plugin system** — C API (`.so` dlopen/dlsym)
- **Python scripting** — CPython embedding with `aura` module
- **CLI headless mode** — `aura --headless <binary>` with JSON/Markdown output
- **Collaboration server** — WebSocket-based real-time sync with LWW conflict resolution
- **Packaging** — Docker, DEB, source TGZ
- **Ghidra parity benchmark** — `tests/benchmark/gap_analyzer.sh` + `parity_score.py` drive Ghidra 12.0.4 headless and score AURA's decompiler output (5 components, 100-point scale). See `AUTOMATION_ROADMAP.md §E-1/E-2`.
- **CI** — GitHub Actions `ci.yml`: `build-and-test` job runs build + ctest; separate `asan` job runs an ASAN build of ctest (excludes `test_python` pending a CPython leak suppression). `build.yml` runs a Release build on every branch push.

---

## Quick Install

Windows:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1
```

Linux/macOS:

```bash
./install.sh
```

The full install creates a user runtime registry under `~/.aura`:

```text
~/.aura/
  runners/pii-python-venv/
  token-classification-models/openai-privacy-filter/
  eval-datasets/
  rule-packs/
  safety-profiles/
  assets/safety/
```

The default token classification model is large. First install may download
about 3GB. The files are runtime assets and are not committed to Git.

Rizin `0.8.0` is the mandatory reference engine. Extracted Rizin/rz-ghidra
binaries are runtime artifacts and are not committed to Git; fetch scripts must
download and verify the Rizin bundle before AURA can use the vendored path.
rz-ghidra `0.8.0` is the preferred pseudo-C provider when present, but the
installer must not be described as installing it automatically until the
fetch/install scripts actually do that. If pseudo-C support is absent, AURA must
show deterministic install guidance and must not fabricate pseudo-C from
disassembly output.

For a lightweight Rizin/GUI setup without model or dataset downloads:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
```

```bash
./install.sh --skip-safety-assets
```

To use a custom runtime location:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -AuraHome "D:\AURA_RUNTIME"
```

```bash
./install.sh --aura-home "$HOME/.cache/aura-runtime"
```

The installer prints the environment variables used by AURA, including
`AURA_HOME`, `AURA_RIZIN_BIN`, `AURA_RIZIN_PATH`, and
`AURA_SAFETY_ASSETS_DIR`.

### MCP local stdio server

`aura-mcp` is the current MCP V1 local stdio JSON-RPC server. Installer builds
with `-Build` / `--build` include the `aura-mcp` target and print its discovered
path. Runtime clients must set `AURA_REPO_ROOT` to the repo root and set
`AURA_MCP_ALLOWED_ROOTS` to the binary-file allowlist (`;` on Windows, `:` on
POSIX). Binary tools fail closed when allowed roots are unset or empty.

See [MCP local stdio server](docs/mcp.md) for setup, JSON-RPC examples, tool
inventory, protected-output rules, and troubleshooting.

---

## Safety Assets Settings

AURA stores privacy-filter runtime assets under `~/.aura` by default. The GUI
uses **Settings -> Safety Assets** to choose the active safety profile.

Safety profiles are JSON files under `safety-profiles/`. A profile selects the
token classification model, rule packs, eval datasets, and model failure policy.
The active profile is persisted in the GUI setting `safety/activeProfileId`.

Runtime masking currently uses the selected profile's rule packs when the
Strings workflow builds protected values. The selected model and model failure
policy are surfaced and validated in the settings dialog, but model inference is
not yet wired into live string masking. Eval datasets are listed for
evaluation/reporting context only; changing an eval dataset does not directly
change live string masking.

Users can add or override local assets under:

```text
~/.aura/
  safety-profiles/*.json
  token-classification-models/*/manifest.json
  rule-packs/*/manifest.json
  eval-datasets/*/manifest.aura.json
```

Committed repo assets remain the fallback. Local `~/.aura` assets with the same
id take precedence, including invalid manifests so the GUI can surface a clear
diagnostic instead of silently hiding a broken local override.

---

## CLI Usage

```bash
# 버전 확인
./build/aura --version

# 파일 메타데이터 (포맷/아키텍처/섹션/심볼)
./build/aura --info /path/to/binary
./build/aura --info --json /path/to/binary

# 디스어셈블 (.text 섹션)
./build/aura --disasm /path/to/binary
./build/aura --disasm /path/to/binary --verbose  # 디버그 로그

# 함수 탐지
./build/aura --functions /path/to/binary

# CFG (텍스트 / Graphviz DOT)
./build/aura --cfg /path/to/binary --func 0x401000
./build/aura --cfg /path/to/binary --func 0x401000 --dot

# DFG (데이터 흐름)
./build/aura --dfg /path/to/binary --func 0x401000

# 호출 그래프
./build/aura --callgraph /path/to/binary

# Xref (특정 주소 참조)
./build/aura --xref /path/to/binary --addr 0x401000

# 문자열 + 코드 참조
./build/aura --strings /path/to/binary

# Full recursive disassembly
./build/aura --recursive /path/to/binary

# 헤드리스 자동 분석 (JSON 출력)
./build/aura --headless /path/to/binary --json

# 바이너리 패치
./build/aura --patch /path/to/binary --addr 0x401000 --asm "nop; nop"

# GUI 실행
./build/aura-gui
```

---

## Requirements

- **Compiler**: GCC 13+ or Clang 16+ (C11/C++17)
- **CMake**: ≥ 3.16
- **Qt6**: ≥ 6.2 (for GUI only, optional)
- **libcurl**: ≥ 7.0 (for LLM integration)
- **doxygen + graphviz**: (for API docs, optional)

---

## Build

```bash
# 1. 저장소 clone (submodule 포함)
git clone --recurse-submodules https://github.com/starwinde/AURA-AI-powered-Unified-Reverse-Analyzer.git
cd AURA-AI-powered-Unified-Reverse-Analyzer

# 2. 전체 빌드 (Capstone은 submodule로 자동 빌드)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# 3. 테스트 (110/114 PASS — 4 current regressions from in-progress B-1 ABI seeding)
ctest --test-dir build --output-on-failure
# Known failures: test_real_binary_O1, test_real_binary_O2,
#                 test_real_binary_advanced_O1, test_real_binary_advanced_O2
# — tracked in AUTOMATION_ROADMAP.md §B-1

# 4. 실행
./build/aura --version       # CLI
./build/aura-gui             # GUI

# 5. (선택) ASAN 빌드
cmake -B build-asan -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-fsanitize=address -fno-omit-frame-pointer' \
  -DCMAKE_CXX_FLAGS='-fsanitize=address -fno-omit-frame-pointer'
cmake --build build-asan -j$(nproc)
ctest --test-dir build-asan --output-on-failure

# 6. (선택) Docker 이미지
docker build -t aura:2.0 .
docker run --rm aura:2.0 --version

# 7. (선택) 배포 패키지 생성
cd build && make package  # aura_2.0.0_arm64.deb + aura-2.0.0-Linux.tar.gz

# 8. (선택) API 문서 생성
cmake --build build --target docs  # docs/api/html/
```

---

## Project Structure

```
AURA/
├── src/
│   ├── core/         # 공통 타입, 파이프라인, 플러그인 로더, Python 임베딩, 헤드리스
│   ├── disasm/       # Capstone 래퍼, 간접 호출 해석
│   ├── parser/       # ELF/PE/Mach-O/DEX/.NET/Firmware 파서, DWARF/PDB, eh_frame/SEH
│   ├── symbolic/     # 심볼릭 실행, CFG, DFG, 함수 탐지
│   ├── decompiler/   # SSA IR + HIR, 16개 최적화 패스, 다중 아키 lifter
│   ├── llm/          # LM Studio / llama.cpp / OpenAI / Groq 클라이언트
│   ├── gui/          # Qt6 GUI (뷰, 패널, 다이얼로그)
│   └── collab/       # 협업 서버 + 클라이언트
├── include/          # 공개 헤더 (50+)
├── tests/
│   ├── core/         # 코어 모듈 단위 테스트
│   ├── disasm/       # 디스어셈블러 테스트
│   ├── parser/       # 파서 테스트
│   ├── decompiler/   # 디컴파일러 테스트 (각 최적화 패스별)
│   ├── llm/          # LLM 클라이언트 테스트
│   ├── integration/  # E2E 통합 테스트 + GUI E2E
│   ├── benchmark/    # 성능 벤치마크 (bench_pipeline, bench_decompiler, bench_func_detect)
│   ├── plugin/       # 플러그인 로드 테스트
│   ├── python/       # Python 바인딩 테스트
│   ├── headless/     # 헤드리스 모드 테스트
│   └── results/      # DoD 검증 기록
├── docs/
│   ├── design/       # 설계 문서 (parser, symbolic, decompiler_v2, HIR, LLM, GUI, 협업)
│   ├── api/          # Doxygen HTML (생성됨)
│   ├── user_guide.md # 사용자 매뉴얼
│   ├── benchmark.md  # 벤치마크 결과
│   └── test_plan.md  # 통합 테스트 계획
├── third_party/
│   ├── capstone/     # Capstone 5.x (submodule)
│   ├── zydis/        # Zydis 4.x (submodule, 바이너리 패치)
│   ├── cjson/        # cJSON (단일 파일)
│   ├── sqlite/       # SQLite amalgamation
│   └── yara/         # YARA (BSD 3-Clause)
├── plugins/
│   └── example/      # 예제 플러그인
├── packaging/
│   ├── build_deb.sh  # .deb 빌드 스크립트
│   └── build_tarball.sh
├── Dockerfile
├── Doxyfile
└── CMakeLists.txt
```

---

## Performance

Benchmarks on ARM64 (DGX Spark). Current `ctest`: 110/114 PASS (see Status note above).

| Task | Binary | AURA | Ghidra | Target | Source |
|------|--------|------|--------|--------|--------|
| Full analysis | 109 MB libLLVM-15 | **10.31 s** | — | ≤ 30 min | docs/benchmark.md:102 |
| Full analysis | 133 MB libLLVM-20 | **12.21 s** | — | ≤ 30 min | docs/benchmark.md:103 |
| Function detection (baseline, 5.1 MB stripped) | aura self | **190 ms, F1 0.9728** | — (no paired Ghidra re-measure at 5.1 MB size) | F1 ≥ 0.90 | baselines/aura_stripped.json (2026-04-14) |
| Function detection (apples-to-apples, 4.7 MB stripped) | aura self | **115 ms, F1 0.9227** | 11,360 ms, F1 0.8445 (Ghidra 11.3.1, 99×) | F1 ≥ 0.90 | docs/benchmark.md:160 (2026-04-07) |
| Function detection (libjvm) | 689 MB libjvm stripped | **3,473 ms, F1 0.6665** | 605,618 ms, F1 0.9931 (174× faster, lower F1) | — | docs/benchmark.md:162 |
| UI thread model | — | QThread-separated analysis worker (designed to avoid blocking UI); no quantitative latency benchmark yet | — | — | src/gui/analysis_worker.h:20-36 |
| x86_64 disassembly | — | Capstone 5.x (instruction decode; decompiler pipeline not yet E2E validated for x86_64) | — | ≥ 99% | — |

---

## Documentation

- **[User Guide](docs/user_guide.md)** — 10개 섹션, CLI 전체 참조, GUI 튜토리얼
- **[Benchmark Results](docs/benchmark.md)** — 성능 측정 결과
- **[Test Report](docs/test_report.md)** — 통합 테스트 결과
- **[Automation Roadmap](AUTOMATION_ROADMAP.md)** — 24/7 자동화 세션용 Phase A~E 진행 계획 및 핸드오프 로그
- **[Tasks.md](Tasks.md)** — 세부 태스크·DoD·현재 진행 상태
- **[PRD.md](PRD.md)** — 제품 목표·범위·Open Decisions
- **[rules.md](rules.md)** — AI 행동 규칙·코드 스타일·커밋 규칙
- **[API Documentation](docs/api/html/index.html)** — Doxygen 생성 (make docs)
- **Design Documents**:
  - [Parser](docs/design/parser.md)
  - [Decompiler v2 / HIR](docs/design/decompiler_v2.md) + [HIR detail](docs/design/high_level_ir.md)
  - [LLM Integration](docs/design/llm_integration.md)
  - [GUI](docs/design/gui.md)
  - [Collaboration Server](docs/design/collab_server.md)

---

## License

Apache License 2.0. See [LICENSE](./LICENSE).

### Third-party Licenses

| Library | License | Usage |
|---------|---------|-------|
| [Capstone](https://github.com/capstone-engine/capstone) | BSD 3-Clause | Disassembly engine |
| [Zydis](https://github.com/zyantific/zydis) | MIT | Binary patching encoder (x86/x86_64) |
| [cJSON](https://github.com/DaveGamble/cJSON) | MIT | JSON parsing |
| [libcurl](https://curl.se) | MIT/X | HTTP client for LLM API |
| [SQLite](https://www.sqlite.org) | Public Domain | GUI project database |
| [YARA](https://github.com/VirusTotal/yara) | BSD 3-Clause | Rule-based pattern scanning |
| [Qt6](https://www.qt.io) | LGPL v3 | GUI framework (dynamically linked) |
| [libdwarf / LLVM DebugInfoDWARF](https://github.com/davea42/libdwarf-code) | LGPL/Apache 2.0 | DWARF debug info parsing |
| cxxabi.h (GCC/Clang runtime) | GCC Runtime Exception | C++ symbol demangling |

---

## Contributing

Contributions welcome via pull requests. Please ensure:
- All non-regressing tests pass (`ctest --test-dir build`). If you touch the decompiler, do not introduce new failures beyond the 4 current B-1 regressions listed in `AUTOMATION_ROADMAP.md §B-1`.
- ASAN build is clean for AURA-owned code (`ctest --test-dir build-asan --exclude-regex '^test_python$'`) — `test_python` is excluded pending a CPython leak suppression.
- Code follows style in [rules.md](rules.md)
- New features include unit tests

---

## Acknowledgments

Built with assistance from [Claude Code](https://claude.com/claude-code) (Anthropic).
