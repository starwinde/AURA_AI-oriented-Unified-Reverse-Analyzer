# AURA Cache Speedup Autoplan

Status: proposed
Scope: structure improvement for decompile/disassembly reuse cache and duplicate Rizin-call removal

## Goal

Reduce repeated Rizin subprocess calls in the GUI by adding a project-local
read-through artifact cache for expensive view artifacts:

- function decompile text + line map
- function disassembly instruction list + arrow text
- full-disassembly viewport/window text + instruction list

This is not a new analysis engine and must not synthesize analysis. Cached
values are reusable engine output snapshots only.

## What Already Exists

- `DecompilePane` already has an in-process `QHash<funcAddr, Entry>` cache.
- `DisasmPane` already has in-process `QHash<funcAddr, instructions>` and
  `QHash<funcAddr, arrowText>` caches.
- `runAnalyze()` eagerly batch-decompiles all analyzed functions and fills the
  decompile pane cache.
- `runDisasm()` avoids duplicate per-function Rizin calls while the GUI process
  stays alive.
- `runFullDisasmWindow()` limits work to a bounded window instead of dumping the
  whole binary.
- The project DB currently stores project binaries, overrides, and string
  protection data, but not decompile/disassembly artifacts.

## Current Problems

1. GUI caches are process-local only.
   Closing/reopening a project loses decompile/disassembly results.

2. `runAnalyze()` clears decompile cache and eagerly re-runs batch decompile.
   If a project was already analyzed earlier, there is no persisted artifact to
   reuse.

3. Full disassembly window results are replaced, not cached by window key.
   Returning to the same address/count pays the same Rizin cost again.

4. Project binary loading has a 4096-row soft ceiling.
   This is separate from disasm/decompile speed, but it is the same class of
   "load a bounded prefix and silently ignore the rest" risk.

## Not In Scope

- Persistent Rizin/r2pipe sessions.
- Whole-binary analysis-result database cache.
- Merging cached artifacts from different engine versions.
- Raw artifact exposure through MCP privileged paths.
- New LLM summarization cache.
- RetDec/Ghidra full cache unification beyond storing backend-tagged artifacts.

## Proposed Architecture

```
MainWindow
  |
  | cache lookup before engine call
  v
AuraArtifactCache  ---- sqlite table: analysis_artifacts
  | miss
  v
Rizin adapter subprocess
  |
  | normalized body/text + provenance
  v
AuraArtifactCache put
  |
  v
DecompilePane / DisasmPane / FullDisasmPane memory cache + render
```

## SQLite Schema

Add `include/artifact_cache.h` and `src/core/artifact_cache.c`.

Table:

```sql
CREATE TABLE IF NOT EXISTS analysis_artifacts (
  binary_fingerprint TEXT NOT NULL,
  engine_id TEXT NOT NULL,
  engine_version TEXT NOT NULL DEFAULT '',
  request_type INTEGER NOT NULL,
  artifact_kind TEXT NOT NULL,
  backend TEXT NOT NULL DEFAULT '',
  schema_version INTEGER NOT NULL,
  function_addr INTEGER NOT NULL DEFAULT 0,
  window_addr INTEGER NOT NULL DEFAULT 0,
  window_count INTEGER NOT NULL DEFAULT 0,
  options_hash TEXT NOT NULL DEFAULT '',
  payload_json TEXT NOT NULL,
  created_at TEXT NOT NULL DEFAULT (datetime('now')),
  updated_at TEXT NOT NULL DEFAULT (datetime('now')),
  PRIMARY KEY (
    binary_fingerprint, engine_id, engine_version, request_type,
    artifact_kind, backend, schema_version, function_addr,
    window_addr, window_count, options_hash
  )
);
```

Artifact kinds:

- `decompile.function`
- `disasm.function`
- `disasm.window`

Payloads are JSON to keep the first slice small and inspectable:

- decompile: `{ "text": "...", "line_map": [{"line":1,"addr":4096}] }`
- disasm function/window:
  `{ "instructions": [...], "text": "arrow or mixed listing" }`

## Read-Through Flow

### Decompile

1. Check `DecompilePane` memory cache.
2. Check `analysis_artifacts` for `decompile.function`.
3. On DB hit, populate `DecompilePane` memory cache and render.
4. On DB miss, call Rizin as today.
5. Store successful body in DB and memory cache.
6. Do not persist "plugin unavailable" placeholders in the first slice.

### Batch Decompile

1. Before `aura_rizin_decompile_batch_run`, split functions into:
   - cache hits
   - cache misses
2. Only pass misses to the batch call.
3. Fill memory cache from both DB hits and new results.
4. Keep current all-or-nothing behavior only for the miss subset.

### Function Disassembly

1. Check `DisasmPane` memory cache.
2. Check DB artifact `disasm.function`.
3. On DB hit, fill `DisasmPane` memory cache and render.
4. On miss, call Rizin and store result.

### Full Disassembly Window

1. Key by `(binary_fingerprint, engine_version, addr, count)`.
2. Reuse DB artifact for exact window hits.
3. Do not try to stitch adjacent windows in the first slice.

## Duplicate-Call Removal

- `runAnalyze()` should not blindly batch-decompile every function if DB hits
  exist.
- `runFullDisasmOverview()` should use `runFullDisasmWindow()` read-through
  behavior.
- PP3 array candidate flow should keep using `runDisasm(fa)`, but `runDisasm`
  should become cheap on DB hit.

## Test Plan

### Unit

- `artifact_cache_unit`
  - creates schema idempotently
  - put/get decompile payload
  - put/get disasm payload
  - engine_version mismatch misses
  - schema_version mismatch misses
  - binary_fingerprint mismatch misses
  - duplicate key replaces payload and preserves created_at where practical

### GUI Smoke

- Analyze fixture once, decompile first function, close project, reopen project,
  decompile same function, verify text is populated from DB.
- Same for `runDisasm()` and `disasmList()`.
- Same for `runFullDisasmWindow(entry, 128)`.

### Regression Guard

- Add a fake/spy path if practical to prove a cache hit does not dispatch Rizin.
  If difficult in GUI smoke, add this to unit/integration with a small
  `MainWindow` test hook or artifact-cache-level test.

## Failure Modes

| Risk | Mitigation |
|---|---|
| Stale cache after engine upgrade | include `engine_version` in key |
| Stale cache after schema change | include `schema_version` in key |
| Cache grows without bound | defer pruning; add count/size stats first |
| Placeholder cached as real output | do not persist unavailable placeholders |
| Large full-disassembly payloads | cache exact bounded windows only |
| Hidden R-9 violation | cache only engine output, never inferred text |

## Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|---|---|---|---|---|---|
| 1 | CEO | Cache artifacts, not whole analysis bodies | Auto | Keep scope tied to user pain | Speeds repeated views without designing the full Phase 12 database cache | Whole unified model cache |
| 2 | Eng | Use project SQLite table for first slice | Auto | Prefer existing local storage | Project DB already stores binaries, overrides, and string protection | Global cache under ~/.aura |
| 3 | Eng | Use read-through cache before engine calls | Auto | Remove duplicate work at call boundary | Keeps current pane caches and adapter behavior intact | Persistent engine session first |
| 4 | Eng | Store JSON payloads initially | Auto | Inspectable and low-risk | Avoids binary serialization churn while schemas are still moving | Custom binary blob format |
| 5 | Eng | Do not cache unavailable placeholders | Auto | Avoid sticky false negatives | A later plugin install should take effect without manual invalidation | Persist all failures |

## Execution Slices

1. Add `artifact_cache` core API and unit tests.
2. Wire project DB handle lifecycle in `MainWindow`.
3. Add decompile read-through cache and batch miss filtering.
4. Add function disassembly read-through cache.
5. Add full-disassembly window read-through cache.
6. Add GUI smoke reopen tests.
7. Address project binary list pagination separately.

## Approval Gate

Recommended next step: implement slices 1-4 first. This closes the most visible
duplicate Rizin calls without pulling in the full Phase 12 session/cache layer.
