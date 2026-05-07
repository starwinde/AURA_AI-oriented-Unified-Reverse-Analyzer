# ADR-0040 — Phase 11.3.7 (P2.F2) Disassembly view + AuraInstructionRecord

- **Status**: Accepted
- **Date**: 2026-05-04
- **Supersedes**: —
- **Related**: ADR-0036 (Cutter-style workspace), ADR-0039 (StringRecord + body v3),
  Phase 11.3.1.1 (PDF disasm fallback — superseded by this for instruction-level
  view; PDF text fallback remains for `aura-gui` decompile pane when a decompile
  plugin is missing).

## Context

Phase 11.3.6 closed with 9-record analyze body (functions / symbols / blocks /
edges / variables / type_facts / call_edges / xrefs / strings). Decompile pane
exists as `pdf` text fallback (Phase 11.3.1.1) — there is no instruction-level
view (address / hex bytes / mnemonic / operands columns). Per the user
directive on the 8-hour autonomous loop:

> "기드라 / 커터 / IDA Pro 레벨의 RE 도구가 될 때까지 — 어셈블러, CFG,
> 디컴파일이 제대로 구현되어야 페인 포인트 작업 가치가 있다."

F2 (Disassembly view) is the first item in P2 (기초 RE 기능). The user also
directed `/grill-me` design grilling before P2 entry. This ADR records the
result of that grilling (delegated to a Plan sub-agent for token-saving;
multi-agent strategy).

## Decisions

### D1 — `AuraInstructionRecord` is a 10th 1급 record

Add a new normalized record type to `include/aura/normalized_records.h`:

```c
typedef struct AuraInstructionRecord {
    AuraProvenance provenance;     // R-11/R-12 first field
    AuraFunctionId function_id;    // owning function (0 if unattributed)
    uint64_t       addr;
    uint32_t       size;           // instruction byte length
    char           bytes[24];      // engine hex string e.g. "4889e5"
    char           mnemonic[16];   // "mov", "call", ...
    char           op_str[96];     // "rbp, rsp"
    char           type[16];       // pdj.type: "mov"|"jmp"|"call"|...
    uint64_t       jump;           // taken target (0 if N/A)
    uint64_t       fail;           // not-taken (0 if N/A)
} AuraInstructionRecord;
```

Reasoning: rizin `pdj`/`pdfj` already exposes `mnemonic` / `op_str` / `bytes`
separately. Collapsing into a single text dump would require AURA to re-parse
mnemonic vs operands downstream — that is an R-9 violation (derived analysis).
Structured fields keep R-12 honest and let consumers (label suggestion PP4,
search by mnemonic, future syntax highlighter) read what they need without
re-parsing.

The `bytes` field carries the engine's contiguous hex string ("4889e5"); the
display layer is responsible for any spacing pretty-print ("48 89 e5").

### D2 — CLI scope: `--func <addr>` only

Surface as `aura --engine=rizin --disasm <binary> --func <hex>`. One function
per invocation, mirrors the decompile CLI shape (Phase 2B). Range-based
`--range <start>-<end>` is **deferred** to F2-v2 / F5 (hex view) — there is no
F2 user-value for arbitrary ranges (the GUI consumer is "double-click function
→ see instructions").

YAGNI guard: shipping both flags now doubles the test matrix; range can be
added additively later without breaking the function flag.

### D3 — RPC method: `disasm_function(func_addr)`

GUI calls this once per function double-click; the response is cached
(re-using the decompile-cache pattern from Phase 11.3.4). One method, one
cache key, identical mental model to decompile RPC.

### D4 — Body schema: separate `AuraRizinDisasmBody` (NOT analyze body bump)

Add a new single-allocation body type (mirrors the decompile body shape):

```c
#define AURA_RIZIN_DISASM_BODY_MAGIC   0xAFAA2C01u
#define AURA_RIZIN_DISASM_BODY_VERSION 1u

typedef struct AuraRizinDisasmBody {
    uint32_t magic;
    uint32_t version;
    uint64_t function_addr;       // request key
    size_t   instructions_count;
} AuraRizinDisasmBody;

const AuraInstructionRecord *
aura_rizin_disasm_body_instructions(const AuraRizinDisasmBody *b);
```

**Rejected**: bumping `AuraRizinAnalyzeBody` to v4 with `instructions[]` array.
That would force every `analyze` invocation to fetch instructions for *all*
functions — analyze time multiplies 5–10×, defeating the Phase 11.3 Quick/Full
analysis-level split. On-demand per-function fetch is the right unit. R-12
permits multiple body types; the decompile body is precedent.

### D5 — GUI dock + line_map sync

- Dock placement: new `disasmDock` in the function workspace, **tabified onto
  the existing decompile dock** (Cutter pattern — user toggles between
  decomp / disasm in one screen real estate).
- F2 wires sync **one direction only**: `DecompilePane::lineSelected(quint64
  addr)` → `DisasmPane::selectInstruction(addr)` (scroll + highlight). This
  uses the existing `AuraRizinDecompileLineMap` (line ↔ addr).
- Reverse direction (disasm click → decomp line) is left as `// TODO F4`
  signal/slot stub; full bidirectional sync is the subject of F4 (Decomp pane
  강화). Putting both into F2 would make F2 a mini-F4 — scope creep.

## Consequences

**F2 cycle plan (4 cycles, TDD strict)**:

| Cycle | Focus | Files | Test |
|------|------|-------|------|
| C1 | ADR + data model | `normalized_records.{h,c}`, `rizin_adapter.h` (DisasmBody + accessor decl), `src/adapter/rizin/rizin_adapter.c` (accessor impl) | unit test for InstructionRecord provenance reject |
| C2 | CLI + rizin pdfj parsing | `rizin_command_set.{h,c}` (pdfj framed cmd), new `rizin_disasm_normalize.{h,c}` (pdfj → DisasmBody), `src/cli/main.cpp` (`--disasm --func` branch + DISASM type), `rizin_adapter.c` (DISASM dispatch + manifest) | cli_smoke TC: `aura disasm` JSON shape + count > 0 on real ELF |
| C3 | RPC + GUI Disasm dock | `rpc_server.cpp` (`disasm_function`), `src/gui/disasm_pane.{h,cpp}` (QPlainTextEdit, monospace), `main_window.{h,cpp}` (dock + tabify + double-click → disasm_function + cache) | gui_smoke TC: disasmDock objectName + instruction lines > 0 |
| C4 | line_map sync (one-way) | `decompile_pane.{h,cpp}` (`lineSelected` signal), `disasm_pane.{h,cpp}` (`selectInstruction` slot, addr↔line hash), `main_window.cpp` (connect) | gui_smoke TC: simulate line click → assert disasm cursor at expected addr |

**R-1/R-9/R-10 guards** (unchanged from prior phases):
- AURA never disassembles. All instructions originate from rizin `pdfj` JSON.
- `RzCore` / rizin canonical types stay inside `src/adapter/rizin/` and the
  `third_party_hub` mirror.
- No "smart" instruction post-processing — display layer can pretty-print
  `bytes` (spacing) and resolve `flags[]` later, but never re-parses
  mnemonic/operands.

## Alternatives considered

- **Single text dump per instruction** (D1): rejected — forces re-parsing
  downstream, R-9 risk.
- **CLI + RPC dual scope (`--func` AND `--range`)** (D2/D3): rejected for v1
  — no concrete user-value yet, doubles test matrix. Additive in F5.
- **Bump analyze body to v4** (D4): rejected — analyze latency explosion,
  defeats Quick/Full split.
- **Disasm dock in BottomDockArea or 2nd tab inside decompile pane** (D5):
  rejected — Cutter convention is separate dock; readability needs full pane
  width.
- **Bidirectional sync in F2** (D5): rejected — scope creep into F4.
