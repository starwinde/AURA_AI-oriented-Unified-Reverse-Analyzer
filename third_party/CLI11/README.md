# CLI11 (vendored)

Single-header C++ command-line parser. BSD-3 license.

- Source: https://github.com/CLIUtils/CLI11
- Vendored version: **2.6.2**
- Vendored on: 2026-05-03
- File: [`CLI11.hpp`](./CLI11.hpp)

## Why vendored

ADR-0032 covers external **runtime** tools (Rizin, Ghidra) via manifest +
fetch script. Build-time header-only deps follow the existing AURA pattern
of source vendoring (cf. `third_party/cjson/`, `third_party/sqlite/`,
`third_party/doctest/`).

## Upgrade procedure

```sh
curl -sL -o third_party/CLI11/CLI11.hpp \
  https://github.com/CLIUtils/CLI11/releases/download/v<NEW_VERSION>/CLI11.hpp
# Update the version line above and the comment at the top of CLI11.hpp.
```
