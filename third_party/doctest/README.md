# doctest (vendored)

Single-header C++ testing framework. MIT licensed.

- Source: https://github.com/doctest/doctest
- Vendored version: **2.4.11**
- Vendored on: 2026-05-03
- File: [`doctest.h`](./doctest.h)

## Why vendored

ADR-0032 covers external **runtime** tools (Rizin, Ghidra) via manifest +
fetch script. Build-time header-only deps follow the existing AURA pattern
of source vendoring (cf. `third_party/cjson/`, `third_party/sqlite/`).

## Upgrade procedure

```sh
curl -sL -o third_party/doctest/doctest.h \
  https://raw.githubusercontent.com/doctest/doctest/v<NEW_VERSION>/doctest/doctest.h
# Update the version line above and the comment at the top of doctest.h.
```
