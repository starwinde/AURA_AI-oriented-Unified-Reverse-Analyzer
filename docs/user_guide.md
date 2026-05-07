# AURA User Guide

> Version 0.1.0
> AI-powered Unified Reverse Analyzer

---

## Table of Contents

1. [Overview](#1-overview)
2. [System Requirements](#2-system-requirements)
3. [Installation](#3-installation)
4. [GUI Quick Start](#4-gui-quick-start)
5. [CLI Reference](#5-cli-reference)
6. [LLM Integration](#6-llm-integration)
7. [Keyboard Shortcuts](#7-keyboard-shortcuts)
8. [Project Management](#8-project-management)
9. [Export Formats](#9-export-formats)
10. [Troubleshooting](#10-troubleshooting)

---

## 1. Overview

AURA is a native C/C++ reverse engineering tool that combines binary analysis,
disassembly, decompilation, and AI-powered code understanding. It supports
ELF, PE, and Mach-O binary formats across x86, x86_64, ARM, and AArch64
architectures.

Key capabilities:

- **Disassembly** -- Full instruction-level disassembly via Capstone engine
- **Decompilation** -- SSA-based IR with Pseudo-C output
- **Binary patching** -- x86/x86_64 instruction encoding via Zydis
- **LLM analysis** -- Function naming and code summarization via local/cloud LLMs
- **GUI** -- Qt6-based analysis workbench with synchronized views
- **CLI** -- Command-line tools for scripting and batch analysis

---

## 2. System Requirements

| Component | Requirement |
|-----------|-------------|
| OS | Linux (tested on Ubuntu 22.04+, aarch64 and x86_64) |
| Compiler | GCC 11+ or Clang 14+ with C11/C++17 support |
| CMake | 3.16 or later |
| Qt6 | 6.2+ (for GUI; `qt6-base-dev` package) |
| libcurl | 7.0+ (for LLM features; `libcurl4-openssl-dev`) |
| Disk | ~500 MB for build artifacts |
| RAM | 4 GB minimum, 8 GB recommended for large binaries |

### Optional

| Component | Purpose |
|-----------|---------|
| LM Studio | Local LLM server for AI analysis features |
| Graphviz | Rendering DOT output from CFG/callgraph commands |

---

## 3. Installation

### 3.1 Build from Source

```bash
# Clone the repository
git clone https://github.com/starwinde/AURA.git
cd AURA

# Build third-party dependencies (one-time)
cmake -B third_party/capstone/build third_party/capstone
make -C third_party/capstone/build -j$(nproc)

cmake -B third_party/zydis/build third_party/zydis
make -C third_party/zydis/build -j$(nproc)

# Build AURA
cmake -B build
cmake --build build -j$(nproc)

# Verify
./build/aura --version
# Output: AURA v0.1.0
```

### 3.2 Build Options

| CMake Option | Default | Description |
|--------------|---------|-------------|
| `AURA_BUILD_GUI` | ON | Build Qt6 GUI application |
| `AURA_BUILD_LLM` | ON | Build LLM integration module |
| `CMAKE_BUILD_TYPE` | Debug | Set to `Release` for optimized build |

Example: Release build without GUI:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DAURA_BUILD_GUI=OFF
cmake --build build -j$(nproc)
```

### 3.3 Run Tests

```bash
cd build && ctest --output-on-failure
```

---

## 4. GUI Quick Start

### 4.1 Launch

```bash
./build/aura-gui
```

The Project Manager window appears first. Create a new project or open an
existing one, then load a binary for analysis.

### 4.2 Main Window Layout

```
+------+----------------------------+-------------------+
|      |                            |  Decompile View   |
|  S   |    Disassembly View        |  (Pseudo-C)       |
|  i   |    (instructions)          |                   |
|  d   |                            +-------------------+
|  e   |                            |  LLM Panel        |
|  b   +----------------------------+  [Summarize]      |
|  a   |    Hex View (tab)          |  [Suggest Name]   |
|  r   |                            |                   |
+------+----------------------------+-------------------+
|  Console (toggle)                                     |
+-------------------------------------------------------+
|  Status Bar: address | offset | symbol | format | status
+-------------------------------------------------------+
```

**Sidebar panels** (left icon bar):

| Icon | Panel | Content |
|------|-------|---------|
| Fn | Symbols | Function and symbol list. Double-click to navigate. |
| Aa | Strings | Extracted string references |
| Ty | Data Types | Type information |
| Se | Sections | Binary section table (.text, .data, etc.) |
| Bk | Bookmarks | User-defined bookmarks |

### 4.3 Loading a Binary

1. **File > Open** (Ctrl+O) -- Opens a binary file directly (mmap, fast)
2. **File > Import** -- Copies binary into the project directory, then opens
3. **Drag & drop** -- Drop a file onto the window

After loading, the Disassembly view populates automatically. If the binary
has symbols, the Fn panel lists detected functions.

### 4.4 Navigation

- **Click a function** in the Fn panel to jump to its address
- **Go to Address** (Ctrl+G) -- Type an address or symbol name
- **Back / Forward** (Alt+Left / Alt+Right) -- Navigation history
- **Command Palette** (Ctrl+P) -- Search and execute any menu action

### 4.5 View Synchronization

When enabled (Edit > View Sync, on by default), clicking a function in the
Fn panel or navigating to an address will:

1. Scroll the Disassembly view to the target address
2. Update the Decompile view with the containing function's Pseudo-C output
3. Update the status bar with address, file offset, and symbol name

---

## 5. CLI Reference

The `aura` command-line tool provides batch analysis capabilities.

### Global Options

| Option | Description |
|--------|-------------|
| `--verbose` | Enable DEBUG-level log output (can appear anywhere in arguments) |
| `--version` | Print version string and exit |

### Commands

#### `--disasm <file>`

Disassemble the `.text` section of a binary file.

```bash
aura --disasm /bin/ls
aura --verbose --disasm /bin/ls    # with debug output
```

#### `--info <file> [--json]`

Display binary metadata (format, architecture, sections, symbols).

```bash
aura --info /bin/ls           # human-readable output
aura --info --json /bin/ls    # JSON output
```

#### `--functions <file>`

List detected functions in a binary.

```bash
aura --functions tests/disasm/data/test_multi_func
```

#### `--cfg <file> --func <addr> [--dot]`

Generate the Control Flow Graph for a function.

```bash
aura --cfg /bin/ls --func 0x4060    # text output
aura --cfg /bin/ls --func 0x4060 --dot | dot -Tpng -o cfg.png  # graphical
```

#### `--dfg <file> --func <addr> [--json]`

Generate the Data Flow Graph for a function.

```bash
aura --dfg /bin/ls --func 0x4060          # text output
aura --dfg /bin/ls --func 0x4060 --json   # JSON output
```

#### `--callgraph <file> [--dot]`

Generate the inter-procedural call graph.

```bash
aura --callgraph tests/disasm/data/test_multi_func
aura --callgraph tests/disasm/data/test_multi_func --dot | dot -Tpng -o cg.png
```

#### `--patch <file> --addr <hex_addr> --asm "<instruction>"`

Encode an x86/x86_64 instruction at a virtual address (verification mode).

```bash
aura --patch dummy.elf --addr 0x400040 --asm "nop"
# Output: patch: nop @ 0x400040 => 90

aura --patch dummy.elf --addr 0x400040 --asm "jmp 0x400050"
# Output: patch: jmp 0x400050 @ 0x400040 => eb 0e
```

---

## 6. LLM Integration

AURA integrates with LLM backends for AI-powered binary analysis.

### 6.1 Local LLM (LM Studio)

1. Install [LM Studio](https://lmstudio.ai/) and load a model
2. Start the local server (default: `http://localhost:1234/v1`)
3. AURA automatically connects to the local server

### 6.2 Cloud LLM (OpenAI / Groq)

Set API keys via environment variables:

```bash
export OPENAI_API_KEY="sk-..."
export GROQ_API_KEY="gsk_..."
```

### 6.3 Analysis Features

| Feature | Description |
|---------|-------------|
| **Function Name Suggestion** | Analyzes disassembly and suggests a descriptive function name |
| **Code Summarization** | Summarizes decompiled Pseudo-C code in natural language |

In the GUI, select a function and click "Summarize" or "Suggest Name" in the
LLM panel. Results are cached (file-based JSON with SHA256 keys) to avoid
redundant API calls.

### 6.4 Cache

LLM responses are cached in a file-based JSON store. The cache key is the
SHA256 hash of the prompt content. Repeated queries for the same function
are served from cache without network calls.

---

## 7. Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| Ctrl+O | Open binary file |
| Ctrl+S | Save project |
| Ctrl+Q | Quit |
| Ctrl+Z | Undo |
| Ctrl+Shift+Z | Redo |
| Ctrl+G | Go to address |
| Ctrl+P | Command palette |
| Alt+Left | Navigate back |
| Alt+Right | Navigate forward |

---

## 8. Project Management

AURA uses a project-based workflow similar to Ghidra.

### 8.1 Project Structure

```
MyProject.aura/
  ├── project.json              # Project metadata
  ├── binaries/
  │   ├── target.elf            # Imported binary (if imported)
  │   └── target.elf.aura.db   # SQLite analysis database
  └── exports/                  # Exported analysis results
```

### 8.2 Analysis Database

Each binary gets a SQLite database storing:

| Table | Content |
|-------|---------|
| `session` | Window geometry, cursor position, active binary path |
| `bookmarks` | User-defined address bookmarks with comments |
| `renames` | Function/variable rename history |
| `comments` | End-of-line and block comments |

### 8.3 Recent Projects

AURA remembers the 10 most recent projects. They appear in the Project
Manager window on launch.

---

## 9. Export Formats

File > Export provides four output formats:

| Format | Extension | Content |
|--------|-----------|---------|
| ASM | `.asm` | Full disassembly listing with addresses |
| JSON | `.json` | Structured JSON with file metadata and instruction array |
| C Bytes | `.c` | C `unsigned char` array of instruction bytes |
| Hex Dump | `.txt` | Raw hex byte dump per instruction address |

Example ASM export:

```asm
; AURA ASM Export
; File: /bin/ls
; Format: ELF AARCH64

0x0000000064a0:  mov      x29, sp
0x0000000064a4:  stp      x19, x20, [sp, #-0x20]!
```

---

## 10. Troubleshooting

### Binary fails to load

- Verify the file exists and is readable: `file <path>`
- Check format support: ELF, PE, Mach-O are supported. Raw binaries are not
  yet supported in the GUI.
- Check error output: use `aura --verbose --info <path>` for diagnostic info.

### GUI does not start

- Ensure Qt6 is installed: `dpkg -l | grep qt6-base-dev`
- On headless systems, use `QT_QPA_PLATFORM=offscreen` for testing.
- For VNC sessions, AURA uses non-native file dialogs to avoid X11 issues.

### LLM features show "not connected"

- Verify LM Studio is running: `curl http://localhost:1234/v1/models`
- For cloud APIs, check environment variables: `echo $OPENAI_API_KEY`
- LLM features gracefully degrade -- all other analysis works without LLM.

### Performance

- For large binaries (>100MB), expect longer initial analysis times.
- The disassembly view caps at 100,000 instructions for UI responsiveness.
- Use `--verbose` to see timing information in CLI mode.

### ASAN Builds

For memory safety testing:

```bash
cmake -B build-asan \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer" \
  -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
cmake --build build-asan -j$(nproc)
cd build-asan && ctest --output-on-failure
```

---

## Appendix: Supported Formats

| Format | Parse | Disasm | Decompile | Patch |
|--------|-------|--------|-----------|-------|
| ELF x86_64 | Yes | Yes | Yes | Yes (Zydis) |
| ELF x86 | Yes | Yes | Yes | Yes (Zydis) |
| ELF AArch64 | Yes | Yes | Yes | No |
| ELF ARM | Yes | Yes | Partial | No |
| PE x86/x86_64 | Yes | Yes | Yes | Yes (x86 only) |
| Mach-O x86_64 | Yes | Yes | Yes | No |
| Raw binary | No | CLI only | No | No |
