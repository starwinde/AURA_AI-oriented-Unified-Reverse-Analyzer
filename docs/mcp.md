# AURA MCP local stdio server

`aura-mcp` is the current MCP V1 entrypoint. It is a local stdio JSON-RPC
server that bridges allowlisted MCP tool calls to the local `aura` CLI and
returns protected AURA envelopes.

This is not a network service and it does not expose pseudo-C decompile output.
Raw disassembly and raw decompile tools are registered only to return a denial.

## Build and run

Build with the normal installer path:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -Build
```

```bash
./install.sh --build
```

The installers print the discovered `aura-mcp` path after a build. Environment
changes made by an installer do not persist into the parent shell, so set the
runtime variables in the shell that launches `aura-mcp`.

Windows:

```powershell
$env:AURA_REPO_ROOT = "C:\path\to\AURA"
$env:AURA_MCP_ALLOWED_ROOTS = "C:\path\to\binaries;D:\other\root"
.\build-local\src\mcp\Release\aura-mcp.exe
```

POSIX:

```bash
export AURA_REPO_ROOT="/path/to/AURA"
export AURA_MCP_ALLOWED_ROOTS="/path/to/binaries:/other/root"
./build-local/src/mcp/aura-mcp
```

## Environment variables

| Variable | Required | Meaning |
|----------|----------|---------|
| `AURA_REPO_ROOT` | Yes | Repository root used by `aura-mcp` to locate the local `aura` CLI. |
| `AURA_MCP_ALLOWED_ROOTS` | Yes for binary-file tools | Allowlist roots for binary paths. Windows uses semicolons; POSIX uses colons. Unset, empty, missing, or invalid roots fail closed. |
| `AURA_HOME` | No | Runtime home. Defaults to `~/.aura`. |
| `AURA_SAFETY_ASSETS_DIR` | No | Overrides safety assets. Default assets live under `~/.aura` / `AURA_HOME`. |

`aura_probe_engines` does not need a binary path. Tools that inspect a binary
require `binary_path` to resolve to a regular file under `AURA_MCP_ALLOWED_ROOTS`.

## JSON-RPC examples

`aura-mcp` reads one JSON-RPC request per line from stdin and writes one JSON
response per line to stdout.

Initialize:

```json
{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-06-18","capabilities":{},"clientInfo":{"name":"manual","version":"0.0.1"}}}
```

List tools:

```json
{"jsonrpc":"2.0","id":2,"method":"tools/list","params":{}}
```

Probe engines:

```json
{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"aura_probe_engines","arguments":{}}}
```

Analyze an allowlisted binary:

```json
{"jsonrpc":"2.0","id":4,"method":"tools/call","params":{"name":"aura_analyze","arguments":{"binary_path":"C:\\path\\to\\binaries\\sample.exe"}}}
```

Get one function's protected disassembly:

```json
{"jsonrpc":"2.0","id":5,"method":"tools/call","params":{"name":"aura_get_disassembly","arguments":{"binary_path":"C:\\path\\to\\binaries\\sample.exe","function_addr":"0x401000"}}}
```

Tool calls return MCP `content` with a text item. The text is a JSON string
containing AURA's protected envelope, including `mcp_schema_version`,
`tool_schema_version`, `kind`, `status`, `data`, `warnings`, and `disclosure`.

## Tool inventory

| Tool | Status |
|------|--------|
| `aura_probe_engines` | Implemented through the CLI bridge. |
| `aura_info` | Implemented for allowlisted binaries. |
| `aura_analyze` | Implemented for allowlisted binaries with protected/masked strings. |
| `aura_get_disassembly` | Implemented for one function with protected output. |
| `aura_get_cfg` | Implemented for one function with protected output. |
| `aura_get_llm_context` | Implemented for one function with protected output. |
| `aura_get_raw_disassembly` | Intentionally denied with `raw_access_denied`. |
| `aura_get_raw_decompile` | Intentionally denied with `raw_access_denied`. |

## Protected output contract

MCP default tools are protected. Current rules:

- `aura_analyze` masks string content and removes raw string fields such as
  `content`, `raw_content`, `original`, and `export_value`.
- `aura_get_disassembly` omits `body.text` and instruction `op_str`; it marks
  `protected_only`, `text_omitted`, and `op_str_omitted`.
- `aura_get_cfg` marks the body as `protected_only`.
- `aura_get_llm_context` recursively removes `text` and `op_str`.
- Raw access tools are denied. There is no approved raw-return path in MCP V1.
- Pseudo-C decompile is not implemented as an MCP tool in this slice.

## Troubleshooting

`cli_not_found`: set `AURA_REPO_ROOT` to the repository root and confirm the
matching `aura` CLI has been built.

`no_allowed_roots`: set `AURA_MCP_ALLOWED_ROOTS` to at least one existing
directory. Empty or invalid roots fail closed.

`path_denied`: move the binary under an allowlisted root or add its parent root
to `AURA_MCP_ALLOWED_ROOTS`.

`path_not_found` or `not_a_regular_file`: pass an existing regular binary file,
not a directory.

`tool_not_found` for `aura_list_functions`: this function-list helper is not
part of MCP V1 yet. Use `aura_analyze` or a known function address for the
current function-detail tools.

`raw_access_denied`: expected for raw tools. Use protected tools instead.
