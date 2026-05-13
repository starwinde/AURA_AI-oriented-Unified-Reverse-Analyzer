# Variable, Comment, MCP GUI Completion Autoplan Review

## Plan Summary

Goal: finish the parts that are still only partially implemented after the safety/masking/MCP work: variable application, comment round-trip, and GUI-backed MCP exposure. GUI remains the product baseline. CLI and MCP must mirror GUI state and prove what the GUI actually did, not provide a separate CLI-only implementation.

## What Already Exists

- GUI can open a project, add a binary, analyze it, list functions/strings/symbols/xrefs, decompile functions, and expose protected strings.
- MCP tools are registered for GUI status/add/analyze/functions/demo snapshot/protected strings/symbols/xrefs/disasm/cfg/rename/reset.
- `aura_gui_demo_snapshot` works against the foreground GUI and returns protected-only minimal data.
- GUI safety, masking, encoding, string filters, decompile string-address substitution, and malware risk dock are implemented and covered by `gui_smoke`, `cli_smoke`, and `mcp_smoke`.
- Function rename/reset is implemented through `override_store` and covered by GUI and MCP smoke tests.
- Variable records are mirrored into GUI memory and used by candidate-generation features.
- Add-comment UI exists in the decompile context menu and writes an annotation payload to `override_store`.

## NOT In Scope

- Live malware download or execution.
- Dynamic debugging, sandbox execution, detonation, or behavioral malware analysis.
- Replacing the current Rizin/Ghidra orchestration model.
- Turning every variable inference candidate into a confirmed semantic type.
- Raw decompile/disassembly exposure through MCP without an explicit future approval flow.

## Autoplan Findings

### CEO Review

The highest product risk is claiming “variable and comment features work” when the current implementation is only partial. For a GUI-first reverse-engineering product, users expect comments and variable edits to survive reopen and appear in the analysis/decompile surface. Anything less should be labeled as dry-run or candidate-only.

Auto-decision: make comment and variable round-trip a first-class GUI slice before shipping this branch as “complete.”

### Design Review

The GUI needs a visible distinction between suggestions and applied edits:

- Suggestions: type propagation, field suggestions, array shape suggestions.
- Applied edits: renamed functions, saved comments, saved variable aliases/types.

Auto-decision: applied comments/variables must have a visible GUI affordance in the decompile pane or a dedicated annotations/variables dock. Status-bar-only feedback is insufficient because it disappears and is not inspectable.

### Engineering Review

Architecture should follow the existing override pattern:

```text
GUI action
  -> build stable override key
  -> override_store_put()
  -> project DB persists mutation
  -> analyze/decompile display joins engine records + overrides
  -> GUI RPC exposes protected/minimal state
  -> MCP wraps GUI RPC result
```

Critical gap: `buildKeyForVariable()` or equivalent does not exist yet. Current code explicitly defers variable-target override persistence. Comment storage exists but there is no confirmed display/reopen/MCP round-trip.

Auto-decision: implement variable/comment persistence through typed override keys and display joins, not through ad hoc GUI-only maps.

### DX Review

CLI/MCP should provide small debug surfaces that prove GUI state without dumping raw analysis:

- `aura gui comments` or inclusion in `demo-snapshot`.
- `aura gui variables` or protected variable references in `demo-snapshot`.
- MCP tools should expose the same protected state through `aura_gui_demo_snapshot` and, if needed, dedicated protected comment/variable list tools.

Auto-decision: do not add raw comment/decompile export as the default. Keep protected/minimal output as the default MCP policy.

## Architecture Diagram

```text
Qt GUI action/menu
   |
   v
MainWindow mutation API
   |
   v
override_store key builder
   |
   v
SQLite project DB
   |
   +--> GUI display join after analyze/decompile
   |
   +--> GUI RPC protected JSON
          |
          v
       aura CLI gui subcommands
          |
          v
       aura-mcp GUI tools
```

## Test Diagram

| Flow | Required Test | Current State | Decision |
|---|---|---|---|
| Function rename/reset | GUI smoke + MCP smoke | Covered | Keep |
| Add function comment | GUI smoke reopen round-trip | Gap | Add |
| Comment rendered in decompile display | GUI smoke display assertion | Gap | Add |
| Comment included in protected GUI snapshot | RPC/MCP smoke | Gap | Add |
| Variable records mirrored from engine | GUI candidate tests | Partially covered | Keep and strengthen |
| Variable alias/type apply | GUI smoke reopen round-trip | Gap | Add |
| Variable apply in decompile/variable UI | GUI smoke display assertion | Gap | Add |
| Variable protected MCP output | MCP smoke | Partial via demo variable refs, fixture-dependent | Add deterministic fixture or synthetic GUI state |
| Raw data omission policy | MCP smoke | Covered for strings/disasm | Extend to comments/variables |

## Failure Modes Registry

| Failure | User Impact | Severity | Mitigation |
|---|---|---:|---|
| Comment saves but is never rendered | User thinks note disappeared | High | Reopen/display test |
| Variable apply only changes status bar | User thinks variable was renamed but it is lost | High | Persistent override key + test |
| MCP exposes raw comments or strings accidentally | Third-party demo leaks sensitive data | High | protected-only JSON schema tests |
| GUI and CLI disagree on variable/comment state | Demo credibility failure | Medium | GUI RPC as source of truth |
| Fixture has zero variables | Tests pass without proving variable path | Medium | deterministic fixture or injected test body |

## Execution Checklist

- [ ] Add comment mutation API usable by tests, avoiding modal-only coverage.
- [ ] Persist comments with stable function/instruction-level override keys.
- [ ] Render saved comments in the decompile pane display layer.
- [ ] Add GUI smoke: add comment, reopen project, decompile same function, assert comment visible.
- [ ] Add protected comment summary to GUI RPC `demo_snapshot`.
- [ ] Add MCP smoke assertion that comments appear only in protected/minimal form.
- [ ] Introduce variable override key support for variable alias/type edits.
- [ ] Add GUI action/API for applying variable alias/type from candidate dialogs.
- [ ] Render applied variable names/types in the GUI display layer where available.
- [ ] Add GUI smoke: apply variable edit, reopen, assert visible and persisted.
- [ ] Add CLI GUI command or snapshot field for protected variable edits.
- [ ] Add MCP smoke for protected variable output.
- [ ] Run `cmake --build build-trim-gui --config Release --target gui_smoke cli_smoke mcp_smoke aura-gui`.
- [ ] Run `ctest --test-dir build-trim-gui -C Release -R "gui_smoke|cli_smoke|mcp_smoke" --output-on-failure`.
- [ ] Launch foreground `aura-gui.exe`, load fixture, analyze, and verify GUI-visible result.

## Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|---|---|---|---|---|---|
| 1 | CEO | Treat variables/comments as incomplete until GUI round-trip exists | Auto-decided | GUI-first product truth | A visible reverse-engineering feature must persist and reappear after reopen | Calling dry-run/status-only features complete |
| 2 | Design | Add persistent visible surfaces for applied comments and variables | Auto-decided | Inspectability | Status bar messages cannot prove saved state to users | Hidden-only project DB mutations |
| 3 | Eng | Use typed override_store keys for variables/comments | Auto-decided | Existing architecture | Function rename already uses this pattern and survives reopen | Separate ad hoc GUI maps |
| 4 | DX | Expose protected comment/variable summaries through GUI RPC/MCP | Auto-decided | Demo safety | Third-party demo needs minimal proof without raw leakage | Raw decompile/comment dumping |

## Final Gate Recommendation

Approve the next implementation slice with one constraint: do comments first, then variables. Comment round-trip is smaller and validates the override/display/RPC/MCP pattern before introducing variable key complexity.
