#!/usr/bin/env bash
# fetch_external_tools.sh — read third_party/<tool>/manifest.json and ensure
# the prebuilt is present at third_party/<tool>/<version>/. Idempotent.
#
# See ADR-0032 for the acquisition pattern. CI calls this once before cmake
# configure; local dev runs it once after clone (subsequent runs are no-ops
# when the cache is warm).
#
# Override: set AURA_<TOOL>_BIN=/path/to/binary to skip the manifest entirely
# (the path is used as-is; version is not verified).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
# On MSYS / Git-Bash, Windows-native python doesn't understand /c/... paths;
# convert to Windows-style for any path passed to python.
to_native_path() {
    if command -v cygpath >/dev/null 2>&1; then
        cygpath -w "$1"
    else
        echo "$1"
    fi
}
TOOLS=("rizin")

# ── platform detection ─────────────────────────────────────────────────────
case "$(uname -s)" in
    Linux*)   PLATFORM="linux-x86_64" ;;
    Darwin*)  PLATFORM="darwin-x86_64" ;;
    MINGW*|MSYS*|CYGWIN*) PLATFORM="windows-x86_64" ;;
    *) echo "fetch_external_tools: unknown platform $(uname -s)" >&2; exit 1 ;;
esac

require() {
    command -v "$1" >/dev/null 2>&1 || {
        echo "fetch_external_tools: missing dependency: $1" >&2
        exit 1
    }
}
require curl
require sha256sum

# ── pick a working python (Linux: python3, Windows: python or py) ──────────
PYTHON=""
for cand in python3 python py; do
    if command -v "$cand" >/dev/null 2>&1; then
        if "$cand" --version >/dev/null 2>&1; then
            PYTHON="$cand"
            break
        fi
    fi
done
if [[ -z "$PYTHON" ]]; then
    echo "fetch_external_tools: no working python interpreter (tried python3, python, py)" >&2
    echo "  install Python 3.x or set up jq parsing" >&2
    exit 1
fi

read_manifest() {
    # $1 = tool, $2 = dot-separated json path
    local manifest_path
    manifest_path="$(to_native_path "$ROOT/third_party/$1/manifest.json")"
    AURA_MANIFEST="$manifest_path" AURA_KEYPATH="$2" "$PYTHON" -c '
import json, os, sys
with open(os.environ["AURA_MANIFEST"]) as f:
    m = json.load(f)
cur = m
for k in os.environ["AURA_KEYPATH"].split("."):
    if k == "": continue
    cur = cur[k]
print(cur)
'
}

fetch_tool() {
    local tool="$1"
    local manifest="$ROOT/third_party/$tool/manifest.json"
    if [[ ! -f "$manifest" ]]; then
        echo "fetch_external_tools: $tool: missing manifest at $manifest" >&2
        exit 1
    fi

    local upper_tool
    upper_tool="$(echo "$tool" | tr '[:lower:]' '[:upper:]')"
    local override_var="AURA_${upper_tool}_BIN"
    if [[ -n "${!override_var:-}" ]]; then
        echo "fetch_external_tools: $tool: using override ${override_var}=${!override_var}"
        return 0
    fi

    local version url sha256 archive install_dir strip binrel
    version="$(read_manifest "$tool" "version")"
    url="$(read_manifest "$tool" "platforms.$PLATFORM.url")"
    sha256="$(read_manifest "$tool" "platforms.$PLATFORM.sha256")"
    archive="$(read_manifest "$tool" "platforms.$PLATFORM.archive")"
    install_dir="$(read_manifest "$tool" "platforms.$PLATFORM.install_dir")"
    strip="$(read_manifest "$tool" "platforms.$PLATFORM.strip_components")"
    binrel="$(read_manifest "$tool" "platforms.$PLATFORM.binary_relpath")"

    local dest_dir="$ROOT/third_party/$tool/$install_dir"
    local bin_path="$dest_dir/$binrel"

    if [[ -x "$bin_path" ]]; then
        echo "fetch_external_tools: $tool@$version: cache hit ($bin_path)"
        return 0
    fi

    echo "fetch_external_tools: $tool@$version: downloading from $url"
    local tmp_archive
    tmp_archive="$(mktemp --suffix=".${archive}")"
    trap 'rm -f "$tmp_archive"' RETURN
    curl -fsSL -o "$tmp_archive" "$url"

    local got
    got="$(sha256sum "$tmp_archive" | awk '{print $1}')"
    if [[ "$got" != "$sha256" ]]; then
        echo "fetch_external_tools: $tool@$version: sha256 mismatch" >&2
        echo "  expected: $sha256" >&2
        echo "  actual:   $got" >&2
        exit 1
    fi

    mkdir -p "$dest_dir"
    case "$archive" in
        tar.xz|tar.gz|tar.bz2)
            tar -xf "$tmp_archive" -C "$dest_dir" --strip-components="$strip"
            ;;
        zip)
            if [[ "$strip" -eq 0 ]]; then
                unzip -q "$tmp_archive" -d "$dest_dir"
            else
                local tmp_extract
                tmp_extract="$(mktemp -d)"
                unzip -q "$tmp_archive" -d "$tmp_extract"
                # strip N path components
                local src="$tmp_extract"
                for ((i=0; i<strip; i++)); do
                    src="$src/$(ls "$src" | head -n1)"
                done
                cp -a "$src/." "$dest_dir/"
                rm -rf "$tmp_extract"
            fi
            ;;
        *)
            echo "fetch_external_tools: $tool: unsupported archive type '$archive'" >&2
            exit 1
            ;;
    esac

    if [[ ! -x "$bin_path" ]]; then
        # Some archives extract without +x; ensure it.
        chmod +x "$bin_path" 2>/dev/null || true
    fi
    if [[ ! -e "$bin_path" ]]; then
        echo "fetch_external_tools: $tool: binary not found at $bin_path after extract" >&2
        exit 1
    fi
    echo "fetch_external_tools: $tool@$version: ready at $bin_path"
}

for tool in "${TOOLS[@]}"; do
    fetch_tool "$tool"
done
