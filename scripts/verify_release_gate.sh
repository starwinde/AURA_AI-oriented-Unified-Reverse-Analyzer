#!/usr/bin/env sh
set -eu

if [ "$#" -gt 2 ]; then
    printf 'usage: %s [build-dir] [config]\n' "$0" >&2
    exit 2
fi

BUILD_DIR="${1:-build-trim-gui}"
CONFIG="${2:-Release}"

SCRIPT_DIR=$(CDPATH= cd "$(dirname "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd "$SCRIPT_DIR/.." && pwd)

cd "$REPO_ROOT"

run_step() {
    name="$1"
    shift
    printf '==> %s\n' "$name"
    "$@"
}

run_step "Build probe_unit" cmake --build "$BUILD_DIR" --config "$CONFIG" --target probe_unit
run_step "Build mcp_unit" cmake --build "$BUILD_DIR" --config "$CONFIG" --target mcp_unit
run_step "Build full tree" cmake --build "$BUILD_DIR" --config "$CONFIG"
run_step "Run full CTest suite" ctest --test-dir "$BUILD_DIR" -C "$CONFIG" --output-on-failure
