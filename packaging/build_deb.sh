#!/bin/bash
# build_deb.sh — Build .deb package for AURA
# Usage: ./packaging/build_deb.sh [build-dir]
#
# Generates a .deb package in the specified build directory (default: build/).
# Requires: cmake, make, dpkg-deb

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="${1:-${PROJECT_DIR}/build}"

echo "=== AURA .deb package builder ==="
echo "Project dir : $PROJECT_DIR"
echo "Build dir   : $BUILD_DIR"

# Configure if needed
if [ ! -f "$BUILD_DIR/Makefile" ]; then
    echo "--- Configuring CMake (Release) ---"
    cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release "$PROJECT_DIR"
fi

# Build
echo "--- Building ---"
make -C "$BUILD_DIR" -j"$(nproc)"

# Generate .deb via CPack
echo "--- Generating .deb package ---"
cd "$BUILD_DIR"
cpack -G DEB

echo ""
echo "=== Done ==="
DEB_FILE=$(ls -1 "$BUILD_DIR"/aura_*.deb 2>/dev/null || ls -1 "$BUILD_DIR"/aura-*.deb 2>/dev/null || true)
if [ -n "$DEB_FILE" ]; then
    echo "Package: $DEB_FILE"
    dpkg-deb --info "$DEB_FILE" 2>/dev/null || true
else
    echo "Warning: .deb file not found in $BUILD_DIR"
fi
