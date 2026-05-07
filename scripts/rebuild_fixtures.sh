#!/usr/bin/env bash
# rebuild_fixtures.sh — regenerate orchestrator_smoke fixture binaries from
# tests/fixtures/sources/. Run on Linux to refresh elf_smoke.x86_64.
#
# This is NOT part of the normal CI / PR build path. Only run when the
# fixture source changes intentionally; CONTEXT.md "Invariant gate" absorbs
# byte-level variation from routine compiler updates.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="$ROOT/tests/fixtures/sources/aura_smoke.c"
OUT_DIR="$ROOT/tests/fixtures/bin"
mkdir -p "$OUT_DIR"

if ! command -v gcc >/dev/null 2>&1; then
    echo "rebuild_fixtures: gcc not found — install build-essential (Ubuntu)" >&2
    exit 1
fi

ELF_OUT="$OUT_DIR/elf_smoke.x86_64"
echo "rebuild_fixtures: building ELF → $ELF_OUT"
gcc -O0 -g -fno-pie -no-pie -o "$ELF_OUT" "$SRC"
file "$ELF_OUT"

cat <<NOTE

PE fixture (pe_smoke.x86_64.exe) must be rebuilt on Windows via:
    powershell -ExecutionPolicy Bypass -File scripts/rebuild_fixtures.ps1
NOTE
