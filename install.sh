#!/usr/bin/env sh
set -eu

BUILD=0
NO_GUI=0
SKIP_SAFETY_ASSETS=0
REPO_SAFETY_ASSETS_ONLY=0
BUILD_DIR=build-local
CONFIG=Release
AURA_HOME_DIR="${AURA_HOME:-$HOME/.aura}"

usage() {
  cat <<'EOF'
Usage: ./install.sh [options]

Options:
  --build                 Configure and build AURA after installing runtime tools.
  --no-gui                Disable GUI targets during --build.
  --skip-safety-assets    Skip model and dataset downloads.
  --repo-safety-assets-only
                          Copy repo safety manifests/rules only; skip HF downloads.
  --build-dir PATH        CMake build directory. Default: build-local.
  --config CONFIG         CMake build type. Default: Release.
  --aura-home PATH        Runtime asset directory. Default: ${AURA_HOME:-$HOME/.aura}.
  -h, --help              Show this help.
EOF
}

fail_install() {
  echo "AURA install failed." >&2
  echo "Problem: $1" >&2
  echo "Cause: $2" >&2
  echo "Fix: $3" >&2
  exit 1
}

need_cmd() {
  command -v "$1" >/dev/null 2>&1 || fail_install \
    "Required command '$1' was not found." \
    "The installer needs '$1' for this phase." \
    "Install '$1' and rerun ./install.sh."
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --build)
      BUILD=1
      ;;
    --no-gui)
      NO_GUI=1
      ;;
    --skip-safety-assets)
      SKIP_SAFETY_ASSETS=1
      ;;
    --repo-safety-assets-only)
      REPO_SAFETY_ASSETS_ONLY=1
      ;;
    --build-dir)
      option="$1"
      shift
      [ "$#" -gt 0 ] || fail_install \
        "Missing value for $option." \
        "The option requires a following path." \
        "Rerun ./install.sh with '$option PATH'."
      BUILD_DIR="$1"
      ;;
    --config)
      option="$1"
      shift
      [ "$#" -gt 0 ] || fail_install \
        "Missing value for $option." \
        "The option requires a following CMake build type." \
        "Rerun ./install.sh with '$option Release'."
      CONFIG="$1"
      ;;
    --aura-home)
      option="$1"
      shift
      [ "$#" -gt 0 ] || fail_install \
        "Missing value for $option." \
        "The option requires a following path." \
        "Rerun ./install.sh with '$option PATH'."
      AURA_HOME_DIR="$1"
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail_install \
        "Unknown option '$1'." \
        "The installer does not recognize this command-line option." \
        "Run ./install.sh --help for supported options."
      ;;
  esac
  shift
done

need_cmd curl
need_cmd sha256sum
need_cmd bash

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
cd "$ROOT"

mkdir -p "$AURA_HOME_DIR"
FREE_KB="$(df -Pk "$AURA_HOME_DIR" | awk 'NR==2 {print $4}')"
if [ "$SKIP_SAFETY_ASSETS" -eq 1 ] || [ "$REPO_SAFETY_ASSETS_ONLY" -eq 1 ]; then
  NEED_KB=1048576
else
  NEED_KB=6291456
fi
if [ "${FREE_KB:-0}" -lt "$NEED_KB" ]; then
  fail_install \
    "Not enough disk space under $AURA_HOME_DIR." \
    "The selected install mode needs more free space." \
    "Free disk space or rerun with --aura-home on a larger drive."
fi

echo "AURA install: root=$ROOT"
echo "AURA install: fetching external tools from manifest"
bash "$ROOT/scripts/fetch_external_tools.sh"

RIZIN_BIN="$ROOT/third_party/rizin/0.8.0-static/bin/rizin"
[ -x "$RIZIN_BIN" ] || fail_install \
  "Rizin 0.8.0 binary was not found." \
  "Fetch completed but $RIZIN_BIN is missing or not executable." \
  "Remove third_party/rizin/0.8.0-static and rerun ./install.sh."

VERSION_OUTPUT="$("$RIZIN_BIN" -v)"
echo "$VERSION_OUTPUT"
echo "$VERSION_OUTPUT" | grep 'rizin 0\.8\.0' >/dev/null || fail_install \
  "Unexpected Rizin version." \
  "Expected Rizin 0.8.0." \
  "Delete third_party/rizin/0.8.0-static and rerun ./install.sh."

export AURA_REPO_ROOT="$ROOT"
export AURA_RIZIN_BIN="$RIZIN_BIN"
export AURA_RIZIN_PATH="$RIZIN_BIN"
export AURA_HOME="$AURA_HOME_DIR"
export AURA_SAFETY_ASSETS_DIR="$AURA_HOME_DIR/assets/safety"

RZ_GHIDRA_PROBE="$ROOT/tests/fixtures/bin/elf_smoke.x86_64"
if [ -f "$RZ_GHIDRA_PROBE" ] && "$RIZIN_BIN" -e scr.color=0 -q -c 'pdg?' "$RZ_GHIDRA_PROBE" 2>/dev/null | grep 'pdgj' >/dev/null; then
  echo "AURA install: rz-ghidra pdgj available"
else
  echo "AURA install: rz-ghidra pdgj not available; pseudo-C will show install guidance/fallback"
fi

if [ "$SKIP_SAFETY_ASSETS" -eq 0 ]; then
  need_cmd python3
  if [ "$REPO_SAFETY_ASSETS_ONLY" -eq 1 ]; then
    echo "AURA install: copying repo safety assets only"
    python3 "$ROOT/scripts/download_safety_assets.py" \
      --repo-root "$ROOT" \
      --aura-home "$AURA_HOME_DIR" \
      --manifest "$ROOT/assets/safety/runtime-assets.json" \
      --repo-assets-only
  else
    VENV_DIR="$AURA_HOME_DIR/runners/pii-python-venv"
    if [ ! -x "$VENV_DIR/bin/python" ]; then
      echo "AURA install: creating PII runner venv at $VENV_DIR"
      python3 -m venv "$VENV_DIR"
    fi
    VENV_PY="$VENV_DIR/bin/python"
    "$VENV_PY" -m pip install --upgrade pip
    "$VENV_PY" -m pip install --upgrade "huggingface_hub==1.14.0"
    echo "AURA install: downloading token classification model and eval datasets"
    echo "AURA install: this may download about 3GB on first run"
    "$VENV_PY" "$ROOT/scripts/download_safety_assets.py" \
      --repo-root "$ROOT" \
      --aura-home "$AURA_HOME_DIR" \
      --manifest "$ROOT/assets/safety/runtime-assets.json"
  fi
fi

echo "AURA_HOME=$AURA_HOME"
echo "AURA_RIZIN_BIN=$AURA_RIZIN_BIN"
echo "AURA_RIZIN_PATH=$AURA_RIZIN_PATH"
echo "AURA_SAFETY_ASSETS_DIR=$AURA_SAFETY_ASSETS_DIR"

if [ "$BUILD" -eq 1 ]; then
  need_cmd cmake
  GUI_FLAG=ON
  if [ "$NO_GUI" -eq 1 ]; then
    GUI_FLAG=OFF
  fi
  if [ "$NO_GUI" -eq 0 ]; then
    if ! pkg-config --exists Qt6Widgets 2>/dev/null && [ -z "${Qt6_DIR:-}" ] && [ -z "${CMAKE_PREFIX_PATH:-}" ]; then
      fail_install \
        "Qt6 was not found for GUI build." \
        "AURA_BUILD_GUI=ON requires Qt6 Widgets." \
        "Install qt6-base-dev or rerun ./install.sh --no-gui."
    fi
  fi
  cmake -S "$ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$CONFIG" \
    -DAURA_ENABLE_RIZIN=ON \
    -DAURA_BUILD_GUI="$GUI_FLAG" \
    -DAURA_BUILD_TESTS=ON
  cmake --build "$BUILD_DIR" --target aura probe_unit cli_smoke probe_engines_smoke
fi

echo "AURA install: done"
