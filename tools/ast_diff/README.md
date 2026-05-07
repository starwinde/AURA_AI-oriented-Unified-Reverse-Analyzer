# tools/ast_diff/

C++ binary used by `tests/benchmark/parity_score.py --semantic` (Phase G
Hybrid scorer overlay) to compare two C decompile outputs by AST
structure rather than token count.

**Not built by AURA's main CMake.** Standalone CMake project. Bench
tooling only — no impact on `aura` runtime, GUI, CLI, or release tarball.

## Build

```bash
sudo apt install libclang-18-dev    # one-time per dev machine
cmake -S tools/ast_diff -B tools/ast_diff/build
cmake --build tools/ast_diff/build -j
```

Output: `tools/ast_diff/build/ast_diff`

## CLI

```
ast_diff <ghidra_file> <aura_file>
```

Exit codes:
- `0` — both files parsed successfully
- `2` — at least one file failed to parse (JSON still emitted with
  `ast_parse_ok: false` and zeroed scores)
- `3` — usage error

## Output (stdout, JSON)

```json
{"ast_branch_semantic": 7,
 "ast_struct_semantic": 4,
 "ast_total": 11,
 "ast_parse_ok": true}
```

- `ast_branch_semantic` (0–10): Jaccard similarity over branch
  conditions (if/while/for/do/switch). Compound-condition flatten
  (F-1-C-3 visibility) applied during normalization.
- `ast_struct_semantic` (0–10): Jaccard similarity over member-access
  patterns. Cast-and-deref `*(T*)((U*)base + N)` normalized to
  synthetic `MemberAccess(base, N)` nodes (F-1-M visibility).
- `ast_total` = `ast_branch_semantic + ast_struct_semantic` (max 20).
- `ast_parse_ok` = `false` if libclang reported fatal diagnostics.

## How parity_score.py invokes it

`tests/benchmark/parity_score.py` resolves the binary path via the
`AURA_AST_DIFF` env var (default: `<repo>/tools/ast_diff/build/ast_diff`).
Per-function calls are subprocess invocations with a 10-second timeout.
On binary missing or call failure, `parity_score.py` warns once and
returns zeroed AST sub-scores; legacy 5 sub-scores are still computed.

## Tests

```bash
cmake --build tools/ast_diff/build
ctest --test-dir tools/ast_diff/build --output-on-failure
```

Or run the unit binary directly:

```bash
./tools/ast_diff/build/test_ast_diff ./tools/ast_diff/build/ast_diff
```

## Design

See `tests/benchmark/HYBRID_SCORER_DESIGN.md`.
