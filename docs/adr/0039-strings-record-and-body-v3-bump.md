# ADR-0039 — Phase 11.3.6 Strings: AuraStringRecord + analyze body v3

- **Status**: Accepted
- **Date**: 2026-05-04
- **Supersedes**: —
- **Related**: ADR-0035 (project-first GUI), Phase 11.3.5 cycles 1-7 (Xrefs/Symbols/Imports panels)

## Context

Phase 11.3.5 closed with three docks (Xrefs, Symbols, Imports) backed by
the existing 8-record schema (FunctionRecord, BlockRecord, EdgeRecord,
VariableRecord, TypeFactRecord, CallEdgeRecord, SymbolRecord, XrefRecord)
exposed by `AuraRizinAnalyzeBody` v2. The cycle-7 commit body explicitly
deferred Strings to a separate ADR because it requires bumping the body
schema:

> *"Strings remain deferred to Phase 11.3.6 (separate ADR — body schema bump)."*

Strings (rizin `izj` JSON output) are needed for:

1. **GUI Strings dock** — Cutter / IDA / Ghidra-equivalent literal browsing.
2. **PP4 (auto labelling)** — string references are a primary candidate
   source for naming `LAB_xxx` addresses.
3. **LLM context payloads** — `aura llm-context` should surface notable
   literals to ground the model's function naming.

All three need a single, normalized `AuraStringRecord` rather than
adapter-private blobs.

## Decision

### 9th 1급 record: `AuraStringRecord`

Add a 9th first-class record (R-12 still satisfied — strings are NOT
nested inside FunctionRecord). Definition (in `include/aura/normalized_records.h`):

```c
typedef enum AuraStringEncoding {
    AURA_STRING_ENC_UNKNOWN = 0,
    AURA_STRING_ENC_ASCII   = 1,
    AURA_STRING_ENC_UTF8    = 2,
    AURA_STRING_ENC_UTF16LE = 3,
    AURA_STRING_ENC_UTF16BE = 4,
    AURA_STRING_ENC_WIDE    = 5,
} AuraStringEncoding;

typedef struct AuraStringRecord {
    AuraProvenance     provenance;  /* R-11/R-12 first field */
    AuraStringId       string_id;
    uint64_t           addr;
    uint64_t           length;
    AuraStringEncoding encoding;
    char               section[16];
    char               content[128]; /* NUL-terminated, truncated */
} AuraStringRecord;
```

Provenance is mandatory (R-11). `content[]` is engine-reported text
truncated to 127 bytes; the engine raw layer retains full bytes.

### Body schema bump v2 → v3

`AURA_RIZIN_ANALYZE_BODY_VERSION` becomes `3u`. Layout appends a strings
slot:

```
[AuraRizinAnalyzeBody header]
[functions / symbols / blocks / edges / variables / type_facts /
 call_edges / xrefs ...]
[AuraStringRecord    strings   [strings_count   ]]   ← new in v3
```

Compatibility:
- v2 prefix bytes are identical, so existing accessors keep working
  byte-for-byte against a v3 body.
- New consumers MUST guard `strings_count` access on `version >= 3`
  before calling `aura_rizin_analyze_body_strings()`. The accessor
  itself returns NULL for `version < 3` to enforce this defensively.

### R-1 / R-9 guard

AURA does NOT scan the binary for strings on its own — every record
originates from rizin's `izj` bulk JSON (already in the command catalog).
PP4 candidate generation downstream is allowed to *select* / *rank*
strings, but never to *invent* new ones.

## Consequences

- Cycle-1 (this commit): record type + body schema + adapter wiring
  stub (strings_count=0). Build + ctest GREEN with no behavioural
  change — version bump alone is observable in `cli_smoke` body output.
- Cycle-2: rizin `izj` parsing → AuraStringRecord population in
  `rizin_to_aura.c`.
- Cycle-3: CLI `analyze` body emits `strings[]` array (mirroring the
  Phase 11.3.5 cycle-1 xrefs pattern).
- Cycle-4: RPC `list_strings` + GUI Strings dock + `gui_smoke` TC.

## Alternatives considered

- **Embed strings as a function attribute** — violates R-12 (independent
  records). Rejected.
- **Keep schema at v2 and bolt strings into a sidecar** — splits the
  source of truth and complicates the orchestrator's "single body" disposer
  contract. Rejected.
