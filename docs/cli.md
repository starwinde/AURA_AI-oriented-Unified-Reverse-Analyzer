# `aura` CLI — reference

> **Status**: active. Subcommands: `analyze`, `info`, `llm-context`,
> `disasm`, `cfg`, `engines`, `override`, `label-candidates`,
> `propagate-type`, `field-candidates`, `array-candidates`, `gui`, plus
> the top-level `--probe-engines` flag (Phase 2.5.1).
>
> See [ADR-0033](adr/0033-frontend-topology.md) for the frontend topology.
> The CLI is one of two co-equal frontends over `aura_core`; the other
> (Qt6 GUI) is bootstrapped after Phase 11.2 LLM e2e validation.

## Conventions

- **One-shot**: every invocation spawns, runs one orchestrator dispatch
  cycle, prints JSON, and exits. No REPL, no daemon.
- **JSON-default stdout**: every successful command emits JSON whose root
  carries `"aura_schema": 1`. Diagnostics, errors, and progress go to
  stderr.
- **Subcommand syntax**: global options come *before* the subcommand:
  `aura --compact analyze foo.elf`. Subcommand options come *after*:
  `aura llm-context foo.elf --func 0x401000 --with-decompile`.
- **GUI IPC mode**: `aura gui ...` is not a headless engine dispatch. It
  connects to an already-running `aura-gui` local RPC server and controls
  the live Qt process.
- **Engine resolution**: `--engine <id>` forces a specific adapter. When
  omitted, the orchestrator's primary-set policy chooses (currently
  Rizin for ANALYZE / DECOMPILE).
- **Engine binary lookup** (Phase 2.5.2, ADR-0050): probe + dispatch
  paths share the 3-tier resolver: **env override → vendored repo path
  (under `AURA_REPO_ROOT`) → PATH default**. Per-engine env vars listed
  in §"Engine binary environment variables" below.

## `aura --probe-engines` — engine availability probe (Phase 2.5.1)

Top-level flag (not a subcommand) — emits a stable JSON envelope describing
the host's RE engine availability without spawning the orchestrator.

```
$ aura --probe-engines --compact
{"aura_schema":1,"command":"probe-engines","body":{"engines":[
  {"engine_id":"rizin","status":"ENGINE_MISSING",
   "detected_version":"","required_runtime":"rizin >= 0.7",
   "install_hint_linux":"...","install_hint_macos":"...",
   "install_hint_windows":"...","raw_diagnostic":"...",
   "probed_at_ms":...},
  ...
]}}
```

Surfaced engines: `rizin`, `ghidra-decomp`, `ghidra-full`, `angr`, `retdec`.

`status` ∈ {`AVAILABLE`, `RUNTIME_MISSING`, `ENGINE_MISSING`,
`VERSION_MISMATCH`, `PERMISSION_DENIED`, `TIMEOUT`, `UNKNOWN_ERROR`}
(7-value enum, wire-stable).

Exit code = 0 on a successful envelope emit (regardless of any individual
engine's status). Non-zero only when the runner itself fails to start
(rare: OOM, fork/CreateProcess failure unrelated to a specific probe).

The CLI seeds `AURA_REPO_ROOT` automatically if unset/empty so vendored
binaries under `third_party/<engine>/...` are detected without manual
configuration (ADR-0050 D4, Codex review #5).

## Engine binary environment variables (Phase 2.5.2 / ADR-0050)

3-tier lookup priority for every probe + the orchestrator dispatch path:

1. **env override** — explicit user choice; trusted as-is, no stat()
2. **vendored repo path** — `${AURA_REPO_ROOT}/third_party/<engine>/...`
   (file-existence checked via stat)
3. **PATH default** — single name resolved by the OS

| Engine | Env var | Vendored path (POSIX / Windows) |
|--------|---------|---------------------------------|
| Rizin | `AURA_RIZIN_BIN` | `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin{,.exe}` |
| ghidra-decomp | `AURA_GHIDRA_DECOMP_BIN` | `third_party/ghidra-decomp/bin/ghidra-decomp{,.exe}` |
| ghidra-full / java | `AURA_JAVA_BIN` | (none — host JRE) |
| ghidra-full / analyzeHeadless | `AURA_GHIDRA_FULL_ANALYZE_HEADLESS` | `third_party/ghidra-full/support/analyzeHeadless{,.bat}` |
| angr / python | `AURA_ANGR_PYTHON_BIN` | `third_party/angr/venv/{bin/python,Scripts/python.exe}` |
| retdec | `AURA_RETDEC_DECOMPILER_BIN` | `third_party/retdec/bin/retdec-decompiler{,.exe}` |
| (meta) | `AURA_REPO_ROOT` | (sets the base for vendored tier; CLI auto-seeds) |

angr keeps an OS-preferred fallback chain (`python3` → `python` on POSIX,
`python` → `python3` on Windows) **only** at the PATH tier; explicit env
or vendored hits bypass the chain so user choice surfaces clear errors
instead of silent fallback.

Legacy single-engine flag `--rizin <path>` is still honored for ANALYZE /
DISASM dispatch but new code should prefer `AURA_RIZIN_BIN`.

For the project baseline, CLI also auto-seeds `SLEIGHHOME` to
`third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh`
when the variable is unset and that directory exists. This is required for
the rz-ghidra `pdgj` pseudo-C path.

## Security product warning note

Windows Defender, SmartScreen, or endpoint protection may label the local
Rizin/rz-ghidra toolchain as a cyber security risk. That warning is expected
for reverse-engineering tools that execute external analyzers, load plugin
DLLs, and inspect arbitrary binaries. AURA does not suppress that warning.
Validate the tool source/version/hash, keep analysis local, and apply
allow-listing only through local security policy.

The approved execution baseline is documented in ADR-0052:
Rizin 0.8.0 shared64 + rz-ghidra 0.8.0.

## Global options

| Flag | Effect |
|------|--------|
| `--compact` | Emit JSON on a single line (no indent). Default is pretty-printed. |
| `--engine <id>` | Explicit engine id (e.g. `rizin`, `ghidra`). Default: primary set policy. |
| `--rizin <path>` | Path to the rizin binary. Default: `$AURA_RIZIN_BIN`, then vendored `third_party/rizin`, then PATH. |
| `--version` | Print `aura <version>` and exit. |
| `-h, --help` | Help text. Subcommand help: `aura <subcmd> --help`. |

## Exit codes

| Code | Meaning |
|------|---------|
| 0 | Success. |
| 1 | Dispatch failed (e.g. engine error, function not found). |
| 2 | Usage error (bad flag, malformed `--func`, etc.). |
| 3 | Orchestrator init failed (Rizin not registrable). |

## Output schema

All commands share the root structure:

```jsonc
{
  "aura_schema": 1,                  // schema version, stable surface
  "command":     "<analyze|info|llm-context>",
  "binary":      "<input path>",
  ...                                // command-specific fields
}
```

On error, the root carries `error` (machine-readable code) and `message`
(human description) instead of command-specific fields.

---

## `aura gui ...` — live GUI IPC client

Controls a running `aura-gui` process through the localhost JSON-line RPC
server. This is the automation-facing path for GUI state that already exists
on screen; it is also the intended substrate for the future `aura-mcp`
Privacy Filter & Policy Gateway.
The GUI may render records as Cutter-style trees, but IPC responses stay as
bounded JSON records/lists so automation does not depend on widget layout.

Start the GUI with RPC enabled:

```powershell
$env:AURA_GUI_RPC_TOKEN="dev-token"
aura-gui.exe --rpc-port 27654
```

Then attach later with the CLI:

```powershell
aura --compact gui --port 27654 --token dev-token status
aura --compact gui --port 27654 --token dev-token open-project .\aura_test.aura.db
aura --compact gui --port 27654 --token dev-token add-binary .\Easy_CrackMe.exe
aura --compact gui --port 27654 --token dev-token analyze --level advanced
aura --compact gui --port 27654 --token dev-token functions
aura --compact gui --port 27654 --token dev-token decompile --row 0
```

Connection defaults:

| Option | Default |
|--------|---------|
| `--port <n>` | `$AURA_GUI_RPC_PORT`, else `27654` |
| `--token <s>` | `$AURA_GUI_RPC_TOKEN` |

Available v1 subcommands:

| Command | RPC method | Purpose |
|---------|------------|---------|
| `status` | `status` | Check live GUI state (`binary_count`, `function_count`). |
| `open-project <path>` | `open_project` | Open a project DB in the GUI. |
| `add-binary <path>` | `add_binary` | Add a binary to the open GUI project. |
| `analyze [--row N] [--level quick|full|advanced]` | `analyze` | Run GUI analysis. |
| `functions` | `function_list` | List functions loaded in the GUI. |
| `decompile [--row N]` | `decompile` | Decompile a GUI function row. |
| `strings` | `list_strings` | Return strings from the last analysis. |
| `symbols` | `list_symbols` | Return symbols/imports from the last analysis. |
| `xrefs` | `list_xrefs` | Return xrefs from the last analysis. |
| `quit` | `quit` | Ask the GUI process to exit. |

Security boundary:

- `aura-gui` binds RPC to `127.0.0.1` only.
- Every request requires a token.
- The v1 server accepts one client connection at a time.
- This IPC path is for local automation and tests. LLM/agent access should
  go through the planned MCP Privacy Filter & Policy Gateway, which applies
  allowlists, masking, length limits, user approval, and audit logging before
  forwarding to GUI IPC or headless engine APIs.
- The Privacy Filter starts as a string-based MVP. The target masking system
  combines a Token Classification Model, Rule Packs, and Eval Datasets.
- Default runtime assets live under the user home, not `third_party/`:
  `~/.aura/token-classification-models/`, `~/.aura/rule-packs/`,
  `~/.aura/eval-datasets/`, and `~/.aura/safety-profiles/` (ADR-0054).
- The gateway is not a second generative LLM model. The default architecture
  is one user-selected generative LLM plus PII/privacy filtering and policy
  gating.
- String protection persistence separates original strings, user-facing
  aliases, and outbound mask tokens. The v1 DB baseline is
  `analysis_strings`, `string_overrides`, and `string_protection_findings`
  (ADR-0053). External LLM/MCP payloads should prefer mask tokens over aliases.

Output wraps the GUI RPC response:

```jsonc
{
  "aura_schema": 1,
  "command": "gui status",
  "port": 27654,
  "rpc": {
    "ok": true,
    "result": {
      "binary_count": 1,
      "function_count": 72
    }
  }
}
```

---

## `aura analyze <binary>`

ANALYZE dispatch via reference engine; emits the unified-model
representation as JSON.

```sh
$ aura --compact analyze tests/fixtures/bin/elf_smoke.x86_64 | jq .body.functions_count
13
```

Output shape (selected fields):

```jsonc
{
  "aura_schema": 1,
  "command":     "analyze",
  "binary":     "...",
  "body": {
    "magic":           2947164673,           // AuraRizinAnalyzeBody magic
    "version":         2,
    "functions_count": 13,
    "symbols_count":   36,
    "blocks_count":    24,
    // ... edges_count, variables_count, type_facts_count,
    //     call_edges_count, xrefs_count
    "functions": [
      {
        "function_id": 12,
        "entry":       4198779,              // engine-reported entry addr
        "size":        93,
        "name":        "dbg.main",
        "provenance":  { "source": "rizin", "confidence": 0.9, "completeness": 1 }
      },
      // ...
    ]
  }
}
```

---

## `aura info <binary>`

Computes a binary fingerprint without invoking an external RE engine —
pure file I/O + a minimal header parse.

```sh
$ aura --compact info tests/fixtures/bin/elf_smoke.x86_64 | jq .fingerprint
{
  "file_size":   17744,
  "sha256":      "8afdfde4bbc144b29436563b5d6e05bc2d9b07e53d7c93a14bfb6db4eae9a460",
  "format_kind": "elf",
  "image_base":  4194304,
  "entry":       4198480
}
```

| Field | Meaning |
|-------|---------|
| `file_size` | Bytes on disk. |
| `sha256` | Hex SHA-256 of the entire file (matches `sha256sum`). |
| `format_kind` | `elf` / `pe` / `mach-o` / `unknown`. Detected from magic bytes. |
| `image_base` | ELF: lowest `PT_LOAD` `p_vaddr`. PE: optional-header `ImageBase`. Mach-O: 0 (v1 limitation). |
| `entry` | ELF: `e_entry`. PE: `ImageBase + AddressOfEntryPoint`. Mach-O: 0 (v1 limitation). |

`info` does not need Rizin — useful as a fast, side-effect-free
identifier for caching, project DB keys, and override fingerprints.

---

## `aura propagate-type <binary> --func <addr> --target-type <T>`

Generates PP1 type propagation candidates from existing engine records.
Default mode is dry-run and does not touch SQLite:

```sh
$ aura --compact propagate-type foo.elf --func 0x40117b --target-type "UserStruct*"
```

To persist selected results, use explicit apply:

```sh
$ aura --compact propagate-type foo.elf --func 0x40117b \
    --target-type "UserStruct*" --apply --candidate-ids 0,2 \
    --project ./project.aura.db
```

`--apply` requires either `--candidate-ids <ids>` or `--all`. The write path
stores only user-approved TYPE overrides in the existing `override_store`;
it does not cache `variables[]`, `type_facts[]`, `call_edges[]`, or candidate
lists.

---

## `aura llm-context <binary> [--func <addr>] [--with-decompile]`

Builds a vendor-neutral JSON payload of function metadata for downstream
LLM consumption. **AURA does not call any LLM** — it only structures the
payload. The user is free to send (or not send) it to any model.

> Design principle: LLM is **additive**. Every AURA capability must
> remain useful without LLM. `llm-context` is the management-ergonomic
> bridge — it normalises engine output into a shape that's easy to feed
> to a model *or* to a human review pipeline.

### Modes

- **Whole-binary** (default): emits a function table.
  ```sh
  $ aura --compact llm-context foo.elf | jq '.functions | length'
  13
  ```
- **Per-function** (`--func <addr>`): emits one function with 1-hop
  caller/callee names.
  ```sh
  $ aura --compact llm-context foo.elf --func 0x40117b | \
      jq '.function.callees'
  ["sym.imp.printf", "dbg.aura_helper_add", "dbg.aura_helper_mul",
   "dbg.aura_helper_sub"]
  ```

### Function card fields

```jsonc
{
  "function_id": 12,
  "name":        "dbg.main",
  "entry":       4198779,
  "size":        93,
  "provenance":  { "source": "rizin", "confidence": 0.9, "completeness": 1 },
  "callers":     ["..."],            // 1-hop, by name
  "callees":     ["..."],
  "decompile":   "...",              // only when --with-decompile and
                                     // engine has a decompile backend
}
```

### `--with-decompile`

Triggers an additional `DECOMPILE` dispatch per function. Cost: one
external-tool call per function in whole-binary mode (slow on large
binaries). Graceful degrade: if the engine has no decompile backend
(e.g. Rizin without rz-ghidra/jsdec), the field is simply omitted and
analysis-level fields remain unchanged.

### Pipeline example (LM Studio at localhost:1234)

```sh
aura --compact llm-context foo.elf --func 0x40117b | \
  jq -n --slurpfile p /dev/stdin '{
    model: "qwen/qwen3-coder-next",
    messages: [
      { role: "system",
        content: "Suggest a concise rename for the following function." },
      { role: "user", content: ($p[0] | tojson) }
    ]
  }' | \
  curl -s http://localhost:1234/v1/chat/completions \
    -H "Content-Type: application/json" -d @-
```

The pipeline above is **a user composition**, not a built-in command.
That's the additive principle in practice — AURA hands you a payload;
your prompt and your endpoint are yours.

---

## Failure modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| `aura: orchestrator_init_failed` | Rizin binary unreachable. | Set `--rizin` or `$AURA_RIZIN_BIN`, or `bash scripts/fetch_external_tools.sh`. |
| `aura: dispatch_failed (status=N)` | Engine subprocess error. | Check stderr for the engine's own diagnostics. |
| `aura: function_not_found` | `--func` address has no matching function in the engine output. | Run `aura analyze` first and pick an `entry` from the result. |
| stderr `[ERROR] rizin_adapter: no decompile backend` | Rizin lacks rz-ghidra/jsdec at runtime. | `decompile` field is omitted; remaining payload is valid. Install rz-ghidra to get decompile output. |

## Reference

- ADR-0030 — Tier 1 platform policy
- ADR-0031 — Reference engine policy
- ADR-0032 — External tool acquisition pattern
- ADR-0033 — Frontend topology (this document's parent)
- ADR-0052 — Rizin 0.8.0 security/execution baseline
- CONTEXT.md §"Frontends" + §"Engine routing"
- `tests/integration/cli_smoke/` — per-PR invariant gate that locks the
  contract documented above.
