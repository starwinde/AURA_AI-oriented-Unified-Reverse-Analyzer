#!/bin/bash
# build_tarball.sh — Build source tarball for AURA
# Usage: ./packaging/build_tarball.sh [build-dir]
#
# Generates a source .tar.gz archive in the specified build directory (default: build/).

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="${1:-${PROJECT_DIR}/build}"

echo "=== AURA source tarball builder ==="
echo "Project dir : $PROJECT_DIR"
echo "Build dir   : $BUILD_DIR"

# Configure if needed
if [ ! -f "$BUILD_DIR/Makefile" ]; then
    echo "--- Configuring CMake (Release) ---"
    cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release "$PROJECT_DIR"
fi

# Generate source tarball via CPack
echo "--- Generating source tarball ---"
cd "$BUILD_DIR"
cpack --config CPackSourceConfig.cmake

echo ""
echo "=== Done ==="
TARBALL=$(ls -1 "$BUILD_DIR"/aura-*.tar.gz 2>/dev/null || true)
if [ -n "$TARBALL" ]; then
    echo "Tarball: $TARBALL"
    echo "Size: $(du -h "$TARBALL" | cut -f1)"
else
    echo "Warning: tarball not found in $BUILD_DIR"
fi
