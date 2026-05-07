# `third_party/` dependency policy

This directory contains only dependencies that AURA currently builds from
source or needs as lightweight local headers/manifests. Large optional engines
must be resolved through an environment variable, PATH, a fetch script, or a
release/runtime artifact instead of being committed as full upstream source
trees.

## In-repo dependencies

| Directory | Role | Integration |
| --- | --- | --- |
| `sqlite/` | Project DB, override store, string protection store, consent store | Built as the `sqlite3` static target from `CMakeLists.txt` |
| `cjson/` | JSON parsing/serialization for Rizin output, GUI RPC, LLM, safety data | Built as the `cjson` static target from `CMakeLists.txt` |
| `CLI11/` | CLI option parsing | Header-only include path for `src/cli` |
| `doctest/` | Unit and smoke tests | Header-only include path for test targets |
| `curl/` | libcurl header fallback for LLM HTTP | System `CURL::libcurl` is preferred; vendored headers are fallback only |
| `rizin/` | Rizin source/manifest plus local fetched runtime cache | Runtime bundles under versioned folders are ignored |
| `capstone/` | Legacy/CI reference build and future adapter candidate | Not linked by current `aura_core`; keep until CI is simplified |
| `zydis/` | Legacy/CI reference build and future adapter candidate | Not linked by current `aura_core`; keep until CI is simplified |
| `yara/` | Future scan/signature adapter candidate | Not linked by current `aura_core` |
| `ghidra-decompile/` | Future/legacy Ghidra decompile material | Current probe path expects an external `ghidra-decomp` runtime |
| `llvm-project/` | Developer tooling reference for `tools/ast_diff` | Not part of the core runtime build |

## Deliberately not vendored

| Path | Status | Reason |
| --- | --- | --- |
| `retdec/` | Optional external runtime only | AURA probes `retdec-decompiler`, but does not build or link RetDec source |
| `sigdb/` | Optional external data only | No current runtime/build reference; large signature sets should be fetched on demand |
| `tinyxml2/` | Removed | Current Ghidra XML handling is byte-level normalization, not tinyxml2 parsing |

## Runtime lookup rule

External engines follow this order:

1. Explicit environment variable, for example `AURA_RIZIN_BIN` or
   `AURA_RETDEC_DECOMPILER_BIN`.
2. Local runtime drop under `third_party/<engine>/...` when that path exists.
3. OS `PATH` fallback.

The local runtime-drop directories are intentionally ignored when they are not
part of the committed source contract.
