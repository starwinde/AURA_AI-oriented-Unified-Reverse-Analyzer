# Harden Root Installer Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make a fresh AURA checkout install correctly for other users with one root command, while keeping large runtime assets in `~/.aura` instead of Git.

**Architecture:** Keep the root install entrypoints thin and explicit: `install.ps1` for Windows, `install.sh` for POSIX. Both read committed manifests, perform preflight checks, install Rizin 0.8.0 runtime tools, populate `~/.aura` safety registries, download pinned Hugging Face assets, and verify required files. The installer prints actionable recovery commands instead of leaking raw exceptions.

**Tech Stack:** PowerShell 5+/7, POSIX shell, Python venv, `huggingface_hub==1.14.0`, CMake/CTest, AURA `assets/safety` runtime registry.

---

## File Structure

- Modify: `install.ps1`
  - Windows root installer. Owns Windows preflight, Rizin bootstrap, `~/.aura` creation, Python venv creation, safety asset download, verification, optional CMake build.
- Create: `install.sh`
  - POSIX root installer. Mirrors the Windows workflow with POSIX paths and `python3 -m venv`.
- Create: `assets/safety/runtime-assets.json`
  - Committed manifest for external safety runtime assets: model repo id, dataset repo ids, pinned revisions, expected files, approximate size notes.
- Create: `scripts/download_safety_assets.py`
  - Shared Python downloader used by both installers. Reads `assets/safety/runtime-assets.json`, calls `snapshot_download`, writes `manifest.aura.json` for dataset assets, validates expected files.
- Create: `tests/install/test_runtime_assets_manifest.py`
  - Fast Python tests for the manifest and downloader dry-run validation helpers.
- Modify: `README.md`
  - Add quickstart: full install, lightweight install, custom `AURA_HOME`, expected disk/network behavior.
- Modify: `.gitignore`
  - Ignore local `.env.local` only if the installer writes it in a later task. Do not ignore `~/.aura`; it is outside the repo.

---

### Task 1: Add Runtime Asset Manifest

**Files:**
- Create: `assets/safety/runtime-assets.json`
- Test: `tests/install/test_runtime_assets_manifest.py`

- [ ] **Step 1: Create the manifest file**

Create `assets/safety/runtime-assets.json` with this exact content:

```json
{
  "schema_version": 1,
  "python_packages": {
    "huggingface_hub": "1.14.0"
  },
  "token_classification_models": [
    {
      "asset_id": "openai-privacy-filter",
      "repo_id": "openai/privacy-filter",
      "repo_type": "model",
      "revision": "main",
      "target_subdir": "token-classification-models/openai-privacy-filter",
      "expected_files": [
        "config.json",
        "model.safetensors",
        "tokenizer.json",
        "manifest.json"
      ],
      "allow_patterns": [
        "config.json",
        "model.safetensors",
        "tokenizer.json",
        "tokenizer_config.json",
        "special_tokens_map.json",
        "vocab.*",
        "merges.txt",
        "*.txt",
        "*.md"
      ],
      "size_note": "about 2.8GB for model.safetensors"
    }
  ],
  "eval_datasets": [
    {
      "asset_id": "korean-address-en-ko",
      "repo_id": "ziozzang/korean_address_en-ko",
      "repo_type": "dataset",
      "revision": "main",
      "target_subdir": "eval-datasets/korean-address-en-ko",
      "expected_files": ["manifest.aura.json"],
      "purpose": "external_reference_eval_material"
    },
    {
      "asset_id": "korean-proper-noun-koen",
      "repo_id": "ziozzang/korean_proper_noun_koen",
      "repo_type": "dataset",
      "revision": "main",
      "target_subdir": "eval-datasets/korean-proper-noun-koen",
      "expected_files": ["manifest.aura.json"],
      "purpose": "external_reference_eval_material"
    }
  ]
}
```

- [ ] **Step 2: Write the manifest validation test**

Create `tests/install/test_runtime_assets_manifest.py`:

```python
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "assets" / "safety" / "runtime-assets.json"


def test_runtime_assets_manifest_shape():
    data = json.loads(MANIFEST.read_text(encoding="utf-8"))
    assert data["schema_version"] == 1
    assert data["python_packages"]["huggingface_hub"] == "1.14.0"

    models = data["token_classification_models"]
    assert len(models) == 1
    model = models[0]
    assert model["asset_id"] == "openai-privacy-filter"
    assert model["repo_id"] == "openai/privacy-filter"
    assert model["repo_type"] == "model"
    assert model["target_subdir"] == "token-classification-models/openai-privacy-filter"
    assert "model.safetensors" in model["expected_files"]
    assert "tokenizer.json" in model["expected_files"]
    assert "manifest.json" in model["expected_files"]

    dataset_ids = {d["asset_id"] for d in data["eval_datasets"]}
    assert dataset_ids == {"korean-address-en-ko", "korean-proper-noun-koen"}


def test_runtime_assets_manifest_has_no_repo_local_targets():
    data = json.loads(MANIFEST.read_text(encoding="utf-8"))
    all_assets = data["token_classification_models"] + data["eval_datasets"]
    for asset in all_assets:
        target = asset["target_subdir"]
        assert not target.startswith("third_party/")
        assert not target.startswith("assets/")
        assert ".." not in Path(target).parts
```

- [ ] **Step 3: Run the test and verify it passes**

Run:

```powershell
python -m pytest tests/install/test_runtime_assets_manifest.py -q
```

Expected:

```text
2 passed
```

- [ ] **Step 4: Commit**

```powershell
git add assets/safety/runtime-assets.json tests/install/test_runtime_assets_manifest.py
git commit -m "chore: add safety runtime asset manifest"
```

---

### Task 2: Extract Shared Safety Asset Downloader

**Files:**
- Create: `scripts/download_safety_assets.py`
- Modify: `install.ps1`
- Test: `tests/install/test_runtime_assets_manifest.py`

- [ ] **Step 1: Create the shared downloader**

Create `scripts/download_safety_assets.py`:

```python
#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import os
import shutil
import sys
from pathlib import Path
from typing import Any

from huggingface_hub import snapshot_download


def load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8"))


def copy_tree_contents(src: Path, dst: Path) -> None:
    if not src.exists():
        return
    dst.mkdir(parents=True, exist_ok=True)
    for child in src.iterdir():
        target = dst / child.name
        if child.is_dir():
            if target.exists():
                shutil.rmtree(target)
            shutil.copytree(child, target)
        else:
            shutil.copy2(child, target)


def ensure_expected_files(base: Path, expected: list[str], asset_id: str) -> None:
    missing = [name for name in expected if not (base / name).exists()]
    if missing:
        raise RuntimeError(
            f"asset '{asset_id}' is incomplete under {base}; missing: {', '.join(missing)}"
        )


def install_repo_assets(repo_root: Path, aura_home: Path) -> None:
    safety_root = repo_root / "assets" / "safety"
    copy_tree_contents(safety_root, aura_home / "assets" / "safety")
    copy_tree_contents(safety_root / "rule-packs", aura_home / "rule-packs")
    copy_tree_contents(safety_root / "eval-datasets", aura_home / "eval-datasets")
    copy_tree_contents(safety_root / "safety-profiles", aura_home / "safety-profiles")
    copy_tree_contents(
        safety_root / "token-classification-models",
        aura_home / "token-classification-models",
    )


def download_model(asset: dict[str, Any], aura_home: Path) -> Path:
    target = aura_home / asset["target_subdir"]
    target.mkdir(parents=True, exist_ok=True)
    snapshot_download(
        repo_id=asset["repo_id"],
        repo_type=asset.get("repo_type", "model"),
        revision=asset.get("revision", "main"),
        local_dir=str(target),
        allow_patterns=asset.get("allow_patterns"),
    )

    manifest_template = target / "manifest.template.json"
    manifest_path = target / "manifest.json"
    if manifest_template.exists() and not manifest_path.exists():
        manifest_path.write_text(
            manifest_template.read_text(encoding="utf-8"),
            encoding="utf-8",
        )

    ensure_expected_files(target, asset["expected_files"], asset["asset_id"])
    return target


def download_dataset(asset: dict[str, Any], aura_home: Path) -> Path:
    target = aura_home / asset["target_subdir"]
    target.mkdir(parents=True, exist_ok=True)
    snapshot_download(
        repo_id=asset["repo_id"],
        repo_type=asset.get("repo_type", "dataset"),
        revision=asset.get("revision", "main"),
        local_dir=str(target),
    )
    manifest = {
        "schema_version": 1,
        "dataset_id": asset["asset_id"],
        "source": "huggingface",
        "repo_id": asset["repo_id"],
        "revision": asset.get("revision", "main"),
        "purpose": asset.get("purpose", "external_reference_eval_material"),
    }
    (target / "manifest.aura.json").write_text(
        json.dumps(manifest, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    ensure_expected_files(target, asset["expected_files"], asset["asset_id"])
    return target


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", required=True)
    parser.add_argument("--aura-home", required=True)
    parser.add_argument("--manifest", required=True)
    parser.add_argument("--repo-assets-only", action="store_true")
    args = parser.parse_args(argv)

    repo_root = Path(args.repo_root).resolve()
    aura_home = Path(args.aura_home).expanduser().resolve()
    manifest = load_json(Path(args.manifest).resolve())
    aura_home.mkdir(parents=True, exist_ok=True)

    install_repo_assets(repo_root, aura_home)
    if args.repo_assets_only:
        print(json.dumps({"aura_home": str(aura_home), "mode": "repo-assets-only"}))
        return 0

    for model in manifest["token_classification_models"]:
        download_model(model, aura_home)
    for dataset in manifest["eval_datasets"]:
        download_dataset(dataset, aura_home)

    print(
        json.dumps(
            {
                "aura_home": str(aura_home),
                "model_count": len(manifest["token_classification_models"]),
                "dataset_count": len(manifest["eval_datasets"]),
            },
            ensure_ascii=False,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
```

- [ ] **Step 2: Extend the Python test with helper validation**

Append to `tests/install/test_runtime_assets_manifest.py`:

```python
def test_downloader_script_exists_and_mentions_snapshot_download():
    script = ROOT / "scripts" / "download_safety_assets.py"
    text = script.read_text(encoding="utf-8")
    assert "snapshot_download" in text
    assert "--repo-assets-only" in text
    assert "manifest.aura.json" in text
```

- [ ] **Step 3: Run the tests**

Run:

```powershell
python -m pytest tests/install/test_runtime_assets_manifest.py -q
```

Expected:

```text
3 passed
```

- [ ] **Step 4: Commit**

```powershell
git add scripts/download_safety_assets.py tests/install/test_runtime_assets_manifest.py
git commit -m "chore: add shared safety asset downloader"
```

---

### Task 3: Harden `install.ps1`

**Files:**
- Modify: `install.ps1`

- [ ] **Step 1: Add installer preflight functions**

In `install.ps1`, add these functions after `Require-File`:

```powershell
function Fail-Install {
    param(
        [string]$Problem,
        [string]$Cause,
        [string]$Fix
    )
    throw @"
AURA install failed.
Problem: $Problem
Cause: $Cause
Fix: $Fix
"@
}

function Get-FreeBytes {
    param([string]$Path)
    $target = New-Item -ItemType Directory -Force -Path $Path
    $drive = Get-PSDrive -Name $target.PSDrive.Name
    return [int64]$drive.Free
}

function Assert-FreeSpace {
    param(
        [string]$Path,
        [int64]$RequiredBytes,
        [string]$Description
    )
    $free = Get-FreeBytes -Path $Path
    if ($free -lt $RequiredBytes) {
        $requiredGb = [math]::Round($RequiredBytes / 1GB, 1)
        $freeGb = [math]::Round($free / 1GB, 1)
        Fail-Install `
            -Problem "Not enough disk space for $Description." `
            -Cause "Required ${requiredGb}GB, available ${freeGb}GB." `
            -Fix "Free disk space or rerun with -AuraHome on a larger drive."
    }
}

function Assert-WindowsHost {
    if (-not $IsWindows -and $PSVersionTable.PSVersion.Major -ge 6) {
        Fail-Install `
            -Problem "install.ps1 is the Windows installer." `
            -Cause "This host is not Windows." `
            -Fix "Run ./install.sh from the repository root."
    }
}
```

- [ ] **Step 2: Replace raw Python failure with actionable failure**

Change `Resolve-Python` so the final throw becomes:

```powershell
    Fail-Install `
        -Problem "Python 3 was not found." `
        -Cause "The PII runner uses an AURA-managed Python venv, but no py/python/python3 command is available." `
        -Fix "Install Python 3.10+ and rerun: powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1"
```

- [ ] **Step 3: Replace inline downloader generation with shared script**

Remove the whole `Write-SafetyAssetDownloader` function from `install.ps1`.

Replace:

```powershell
$downloadScript = Join-Path $env:TEMP "aura_download_safety_assets.py"
Write-SafetyAssetDownloader -ScriptPath $downloadScript
Write-Host "AURA install: downloading token classification model and eval datasets"
& $venvPython $downloadScript
```

with:

```powershell
$runtimeManifest = Require-File `
    (Join-Path $Root "assets\safety\runtime-assets.json") `
    "safety runtime asset manifest"
$downloadScript = Require-File `
    (Join-Path $Root "scripts\download_safety_assets.py") `
    "safety asset downloader"
Write-Host "AURA install: downloading token classification model and eval datasets"
Write-Host "AURA install: this may download about 3GB on first run"
& $venvPython $downloadScript `
    --repo-root $Root `
    --aura-home $AuraHome `
    --manifest $runtimeManifest
```

- [ ] **Step 4: Add host and disk preflight calls**

After `$Root = Resolve-RepoRoot`, add:

```powershell
Assert-WindowsHost
```

After `$AuraHome` is resolved, add:

```powershell
if ($SkipSafetyAssets) {
    Assert-FreeSpace -Path $AuraHome -RequiredBytes 1GB -Description "Rizin and lightweight AURA runtime assets"
} else {
    Assert-FreeSpace -Path $AuraHome -RequiredBytes 6GB -Description "AURA safety model and eval datasets"
}
```

- [ ] **Step 5: Run lightweight install**

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
```

Expected:

```text
AURA install: verified Rizin 0.8.0 shared64 + rz-ghidra baseline
AURA install: done
```

- [ ] **Step 6: Run full install**

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1
```

Expected:

```text
AURA install: downloading token classification model and eval datasets
AURA_PII_MODEL_MANIFEST=...
AURA install: done
```

- [ ] **Step 7: Commit**

```powershell
git add install.ps1
git commit -m "chore: harden Windows root installer"
```

---

### Task 4: Add POSIX `install.sh`

**Files:**
- Create: `install.sh`

- [ ] **Step 1: Create POSIX installer**

Create `install.sh`:

```sh
#!/usr/bin/env sh
set -eu

BUILD=0
NO_GUI=0
SKIP_SAFETY_ASSETS=0
BUILD_DIR=build-local
CONFIG=Release
AURA_HOME_DIR="${AURA_HOME:-$HOME/.aura}"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --build) BUILD=1 ;;
    --no-gui) NO_GUI=1 ;;
    --skip-safety-assets) SKIP_SAFETY_ASSETS=1 ;;
    --build-dir) shift; BUILD_DIR="${1:?missing --build-dir value}" ;;
    --config) shift; CONFIG="${1:?missing --config value}" ;;
    --aura-home) shift; AURA_HOME_DIR="${1:?missing --aura-home value}" ;;
    -h|--help)
      cat <<'EOF'
Usage: ./install.sh [--skip-safety-assets] [--aura-home PATH] [--build] [--no-gui]

Creates ~/.aura by default, fetches Rizin 0.8.0 static runtime, installs safety
runtime assets, and optionally builds AURA.
EOF
      exit 0
      ;;
    *) echo "AURA install failed: unknown option $1" >&2; exit 2 ;;
  esac
  shift
done

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
cd "$ROOT"

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

need_cmd python3
need_cmd curl
need_cmd sha256sum

mkdir -p "$AURA_HOME_DIR"
FREE_KB="$(df -Pk "$AURA_HOME_DIR" | awk 'NR==2 {print $4}')"
if [ "$SKIP_SAFETY_ASSETS" -eq 1 ]; then
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
sh "$ROOT/scripts/fetch_external_tools.sh"

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

if [ "$SKIP_SAFETY_ASSETS" -eq 0 ]; then
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

echo "AURA_HOME=$AURA_HOME"
echo "AURA_RIZIN_BIN=$AURA_RIZIN_BIN"
echo "AURA_RIZIN_PATH=$AURA_RIZIN_PATH"
echo "AURA_SAFETY_ASSETS_DIR=$AURA_SAFETY_ASSETS_DIR"

if [ "$BUILD" -eq 1 ]; then
  GUI_FLAG=ON
  [ "$NO_GUI" -eq 1 ] && GUI_FLAG=OFF
  cmake -S "$ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$CONFIG" \
    -DAURA_ENABLE_RIZIN=ON \
    -DAURA_BUILD_GUI="$GUI_FLAG" \
    -DAURA_BUILD_TESTS=ON
  cmake --build "$BUILD_DIR" --target aura probe_unit cli_smoke probe_engines_smoke
fi

echo "AURA install: done"
```

- [ ] **Step 2: Make the script executable**

Run:

```powershell
git update-index --chmod=+x install.sh
```

Expected: no output.

- [ ] **Step 3: Syntax-check the shell script**

Run:

```powershell
bash -n install.sh
```

Expected: no output. If `bash` is not installed on Windows, run:

```powershell
git diff --check -- install.sh
```

Expected: no output.

- [ ] **Step 4: Commit**

```powershell
git add install.sh
git commit -m "chore: add POSIX root installer"
```

---

### Task 5: Add Installer Documentation

**Files:**
- Modify: `README.md`

- [ ] **Step 1: Insert quickstart section**

In `README.md`, before `## CLI Usage`, insert:

````markdown
## Quick Install

Windows:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1
```

Linux/macOS:

```bash
./install.sh
```

The full install creates a user runtime registry under `~/.aura`:

```text
~/.aura/
  runners/pii-python-venv/
  token-classification-models/openai-privacy-filter/
  eval-datasets/
  rule-packs/
  safety-profiles/
  assets/safety/
```

The default token classification model is large. First install may download
about 3GB. The files are runtime assets and are not committed to Git.

For a lightweight Rizin/GUI setup without model or dataset downloads:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
```

```bash
./install.sh --skip-safety-assets
```

To use a custom runtime location:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -AuraHome "D:\AURA_RUNTIME"
```

```bash
./install.sh --aura-home "$HOME/.cache/aura-runtime"
```

The installer prints the environment variables used by AURA, including
`AURA_HOME`, `AURA_RIZIN_BIN`, `AURA_RIZIN_PATH`, and
`AURA_SAFETY_ASSETS_DIR`.
````

- [ ] **Step 2: Run markdown sanity check**

Run:

```powershell
Select-String -Path README.md -Pattern "Quick Install","SkipSafetyAssets","--skip-safety-assets","AURA_HOME"
```

Expected: all four patterns appear.

- [ ] **Step 3: Commit**

```powershell
git add README.md
git commit -m "docs: document root installer"
```

---

### Task 6: Verify Installer Paths

**Files:**
- No new files
- Verify: `install.ps1`, `install.sh`, `scripts/download_safety_assets.py`

- [ ] **Step 1: Run Windows lightweight installer**

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
```

Expected:

```text
AURA install: verified Rizin 0.8.0 shared64 + rz-ghidra baseline
AURA install: done
```

- [ ] **Step 2: Run Windows custom AuraHome installer**

Run:

```powershell
$tmp = Join-Path $env:TEMP "aura-install-test"
Remove-Item -LiteralPath $tmp -Recurse -Force -ErrorAction SilentlyContinue
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -AuraHome $tmp
Test-Path (Join-Path $tmp "token-classification-models\openai-privacy-filter\model.safetensors")
Test-Path (Join-Path $tmp "safety-profiles\default.json")
```

Expected:

```text
True
True
```

- [ ] **Step 3: Run script checks**

Run:

```powershell
git diff --check
python -m pytest tests/install/test_runtime_assets_manifest.py -q
```

Expected:

```text
3 passed
```

- [ ] **Step 4: Run existing focused tests**

Run:

```powershell
$oldBin=$env:AURA_RIZIN_BIN; $oldPath=$env:AURA_RIZIN_PATH; $oldRoot=$env:AURA_REPO_ROOT
Remove-Item Env:AURA_RIZIN_BIN -ErrorAction SilentlyContinue
Remove-Item Env:AURA_RIZIN_PATH -ErrorAction SilentlyContinue
Remove-Item Env:AURA_REPO_ROOT -ErrorAction SilentlyContinue
ctest --test-dir build-trim-gui -C Release -R "probe_unit" --output-on-failure
if ($oldBin) { $env:AURA_RIZIN_BIN=$oldBin }
if ($oldPath) { $env:AURA_RIZIN_PATH=$oldPath }
if ($oldRoot) { $env:AURA_REPO_ROOT=$oldRoot }
```

Expected:

```text
100% tests passed
```

- [ ] **Step 5: Commit verification fixes if needed**

If any verification step required a fix:

```powershell
git add install.ps1 install.sh scripts/download_safety_assets.py README.md assets/safety/runtime-assets.json tests/install/test_runtime_assets_manifest.py
git commit -m "chore: finish installer verification"
```

If no fixes were needed, do not create an empty commit.

---

## Self-Review Checklist

- [ ] Spec coverage: root installer, `~/.aura`, model download, dataset download, directory setup, cross-user support, POSIX support, docs, verification.
- [ ] No placeholders: every task has exact files, commands, and expected results.
- [ ] Type/path consistency: `openai-privacy-filter`, `korean-address-en-ko`, `korean-proper-noun-koen`, `pii-python-venv`, and `~/.aura` are spelled consistently.
- [ ] Existing boundaries preserved: no model weights in Git, no `third_party` model storage, no real `transformers` runner implementation.
