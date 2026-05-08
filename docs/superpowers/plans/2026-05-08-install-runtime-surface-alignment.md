# Install Runtime Surface Alignment Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the root installers, fetch scripts, CI, and docs agree on the actual runtime surface: Rizin 0.8.0, rz-ghidra/SLEIGHHOME, Qt GUI prerequisites, and safety model/dataset assets.

**Architecture:** Keep large runtime assets out of Git. Use manifest-driven acquisition for external RE tools under `third_party/<tool>/<install_dir>`, user-home runtime assets under `~/.aura`, and explicit preflight checks for system dependencies such as Qt. The first pass must not invent bundled binaries; it should either fetch from pinned, hash-verified sources or fail with a concrete install instruction.

**Tech Stack:** PowerShell, POSIX shell, JSON manifests, CMake, GitHub Actions, Hugging Face Hub snapshot downloads, Qt6, Rizin 0.8.0, rz-ghidra 0.8.0.

---

## File Structure

- Modify `third_party/rizin/manifest.json`: keep only Rizin 0.8.0 package metadata and required Rizin binary paths.
- Create `third_party/rz-ghidra/manifest.json`: pinned rz-ghidra acquisition metadata when a hash-verified binary/archive source is available; otherwise a source-build or package-manager strategy marker with explicit unsupported platforms.
- Modify `scripts/fetch_external_tools.ps1`: support multiple tools, required path validation, non-binary required assets, and a clear unsupported-tool error.
- Modify `scripts/fetch_external_tools.sh`: mirror PowerShell behavior for multiple tools, required path validation, and unsupported platform handling.
- Modify `install.ps1`: use fetch results for Rizin and rz-ghidra, validate `SLEIGHHOME`, add Qt preflight only when `-Build` and GUI are requested, and keep safety asset installation unchanged.
- Modify `install.sh`: mirror Windows installer behavior for Rizin/rz-ghidra where supported, add Qt preflight for GUI builds, and keep safety asset installation unchanged.
- Modify `.github/workflows/orchestrator-smoke.yml`: make Windows/Linux smoke jobs run the same external tool fetch contract and verify whether pseudo-C is expected or fallback is expected.
- Modify `tests/integration/gui_smoke/CMakeLists.txt`: set `SLEIGHHOME` only when installed, but expose a deterministic variable to the test.
- Modify `tests/integration/gui_smoke/gui_smoke.cpp`: keep both pseudo-C and install-guidance branches valid, and add an assertion that explains which branch ran.
- Modify docs: `README.md`, `CLAUDE.md`, `CONTEXT.md`, `PRD.md`, `rules.md`, `docs/adr/0052-rizin-0.8.0-security-baseline.md`, `AUTOMATION_ROADMAP.md`.

---

### Task 1: Lock the Actual Runtime Contract

**Files:**
- Modify: `docs/adr/0052-rizin-0.8.0-security-baseline.md`
- Modify: `AUTOMATION_ROADMAP.md`
- Modify: `README.md`

- [ ] **Step 1: Record the current factual contract**

Update ADR-0052 to distinguish three states:

```markdown
### D0 — Runtime acquisition contract

The repository does not commit extracted Rizin or rz-ghidra binaries.
Installers may place runtime tools under `third_party/rizin/[version]/` and
`third_party/rz-ghidra/[version]/`, both ignored by Git. A clean checkout must
be reproducible by running the root installer or `scripts/fetch_external_tools.*`.
```

- [ ] **Step 2: Make rz-ghidra status explicit**

Replace any unconditional wording that says “baseline is Rizin + rz-ghidra installed” with:

```markdown
Rizin 0.8.0 is the mandatory reference engine. rz-ghidra 0.8.0 is the preferred
pseudo-C provider when available. If rz-ghidra is not installed, AURA must
surface deterministic install guidance and avoid fabricating pseudo-C output.
```

- [ ] **Step 3: Run doc grep**

Run:

```powershell
Select-String -Path README.md,CLAUDE.md,CONTEXT.md,PRD.md,rules.md,AUTOMATION_ROADMAP.md,docs\adr\0052-rizin-0.8.0-security-baseline.md -Pattern 'Rizin 0.8.0 shared64 \+ rz-ghidra 0.8.0|SLEIGHHOME|rz_ghidra_sleigh' -CaseSensitive:$false
```

Expected: every remaining unconditional `rz-ghidra` statement says either “preferred when available” or points to an installer step that actually validates it.

- [ ] **Step 4: Commit contract docs**

```powershell
git add README.md CLAUDE.md CONTEXT.md PRD.md rules.md AUTOMATION_ROADMAP.md docs/adr/0052-rizin-0.8.0-security-baseline.md
git commit -m "docs: clarify runtime tool acquisition contract"
```

---

### Task 2: Add Multi-Tool Manifest Support to Fetch Scripts

**Files:**
- Modify: `scripts/fetch_external_tools.ps1`
- Modify: `scripts/fetch_external_tools.sh`
- Create: `third_party/rz-ghidra/manifest.json`

- [ ] **Step 1: Create a minimal rz-ghidra manifest**

Create `third_party/rz-ghidra/manifest.json` with explicit unsupported entries until a pinned archive is selected:

```json
{
  "tool": "rz-ghidra",
  "version": "0.8.0",
  "platforms": {
    "windows-x86_64": {
      "supported": false,
      "reason": "No pinned hash-verified Windows binary source has been selected yet."
    },
    "linux-x86_64": {
      "supported": false,
      "reason": "Use distro package manager or add a pinned binary/source-build strategy."
    }
  }
}
```

- [ ] **Step 2: Add tool list to PowerShell fetcher**

Change:

```powershell
$Tools = @("rizin")
```

to:

```powershell
$Tools = @("rizin", "rz-ghidra")
```

- [ ] **Step 3: Add unsupported-platform handling to PowerShell fetcher**

After `$plat` lookup, add:

```powershell
if ($plat.PSObject.Properties.Name -contains "supported" -and -not $plat.supported) {
    throw "fetch_external_tools: $Tool@$version: unsupported on $Platform: $($plat.reason)"
}
```

- [ ] **Step 4: Add required path helper to shell fetcher**

Add this helper after `read_manifest()`:

```bash
read_manifest_optional() {
    local manifest_path
    manifest_path="$(to_native_path "$ROOT/third_party/$1/manifest.json")"
    AURA_MANIFEST="$manifest_path" AURA_KEYPATH="$2" "$PYTHON" -c '
import json, os
with open(os.environ["AURA_MANIFEST"]) as f:
    m = json.load(f)
cur = m
try:
    for k in os.environ["AURA_KEYPATH"].split("."):
        if k == "": continue
        cur = cur[k]
except Exception:
    raise SystemExit(3)
print(cur)
'
}
```

- [ ] **Step 5: Add unsupported-platform handling to shell fetcher**

After platform field resolution begins, add:

```bash
if supported="$(read_manifest_optional "$tool" "platforms.$PLATFORM.supported" 2>/dev/null)"; then
    if [[ "$supported" == "False" || "$supported" == "false" ]]; then
        reason="$(read_manifest_optional "$tool" "platforms.$PLATFORM.reason" 2>/dev/null || echo "no reason provided")"
        echo "fetch_external_tools: $tool@$version: unsupported on $PLATFORM: $reason" >&2
        exit 1
    fi
fi
```

- [ ] **Step 6: Run fetchers to verify intentional failure**

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\fetch_external_tools.ps1
```

Expected: Rizin cache hit or ready, then rz-ghidra unsupported error with the manifest reason.

Run on Linux/WSL when available:

```bash
bash scripts/fetch_external_tools.sh
```

Expected: same unsupported error for rz-ghidra.

- [ ] **Step 7: Commit manifest/fetcher support**

```powershell
git add scripts/fetch_external_tools.ps1 scripts/fetch_external_tools.sh third_party/rz-ghidra/manifest.json
git commit -m "chore: add explicit rz-ghidra acquisition contract"
```

---

### Task 3: Choose and Implement rz-ghidra Acquisition Strategy

**Files:**
- Modify: `third_party/rz-ghidra/manifest.json`
- Modify: `scripts/fetch_external_tools.ps1`
- Modify: `scripts/fetch_external_tools.sh`
- Modify: `install.ps1`
- Modify: `install.sh`

- [ ] **Step 1: Select source per platform**

Use this decision table:

| Platform | Preferred source | Acceptance rule |
|---|---|---|
| Windows | Pinned project-controlled archive or pinned release artifact | Must include `core_ghidra.dll`, `rz_ghidra_sleigh/x86-64.sla`, SHA256 |
| Linux | Distro package if CI image provides version 0.8.0, otherwise pinned archive/source build | Must make `pdgj` available or mark pseudo-C unavailable |
| macOS | Unsupported for now | Installer prints explicit unsupported message |

- [ ] **Step 2: Verify candidate archive before manifest edit**

For Windows candidate archive:

```powershell
$url = '<selected-url>'
$tmp = [System.IO.Path]::GetTempFileName() + '.zip'
Invoke-WebRequest -Uri $url -OutFile $tmp -UseBasicParsing
Get-FileHash -Path $tmp -Algorithm SHA256
Expand-Archive -Path $tmp -DestinationPath "$env:TEMP\rz-ghidra-check" -Force
Test-Path "$env:TEMP\rz-ghidra-check\lib\rizin\plugins\core_ghidra.dll"
Test-Path "$env:TEMP\rz-ghidra-check\lib\rizin\plugins\rz_ghidra_sleigh\x86-64.sla"
```

Expected: both `Test-Path` calls return `True`.

- [ ] **Step 3: Fill manifest with exact required paths**

Replace the Windows unsupported entry with:

```json
"windows-x86_64": {
  "supported": true,
  "url": "<selected-url>",
  "sha256": "<computed-sha256>",
  "archive": "zip",
  "install_dir": "0.8.0",
  "strip_components": 0,
  "required_relpaths": [
    "lib/rizin/plugins/core_ghidra.dll",
    "lib/rizin/plugins/rz_ghidra_sleigh/x86-64.sla"
  ]
}
```

- [ ] **Step 4: Allow manifest entries without binary_relpath**

In PowerShell, compute `$binPath` only when the property exists:

```powershell
$binPath = $null
if ($plat.PSObject.Properties.Name -contains "binary_relpath") {
    $binPath = Join-Path $destDir $plat.binary_relpath
}
```

Use `$requiredRelpaths = @($plat.required_relpaths)` when present. If neither `binary_relpath` nor `required_relpaths` exists, throw:

```powershell
throw "fetch_external_tools: $Tool`: platform $Platform must define binary_relpath or required_relpaths"
```

- [ ] **Step 5: Mirror no-binary manifest support in shell**

Change shell logic so `binrel` is optional:

```bash
binrel="$(read_manifest_optional "$tool" "platforms.$PLATFORM.binary_relpath" 2>/dev/null || true)"
required_relpaths="$(read_manifest_optional "$tool" "platforms.$PLATFORM.required_relpaths" 2>/dev/null || true)"
```

For the first implementation, use a Python helper to print required paths one per line:

```bash
read_required_relpaths() {
    local manifest_path
    manifest_path="$(to_native_path "$ROOT/third_party/$1/manifest.json")"
    AURA_MANIFEST="$manifest_path" AURA_PLATFORM="$PLATFORM" "$PYTHON" -c '
import json, os
with open(os.environ["AURA_MANIFEST"]) as f:
    m = json.load(f)
p = m["platforms"][os.environ["AURA_PLATFORM"]]
paths = p.get("required_relpaths")
if paths is None:
    paths = [p["binary_relpath"]]
for path in paths:
    print(path)
'
}
```

- [ ] **Step 6: Validate fetch results**

Run:

```powershell
Remove-Item -LiteralPath .\third_party\rz-ghidra\0.8.0 -Recurse -Force -ErrorAction SilentlyContinue
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\fetch_external_tools.ps1
Test-Path .\third_party\rz-ghidra\0.8.0\lib\rizin\plugins\core_ghidra.dll
Test-Path .\third_party\rz-ghidra\0.8.0\lib\rizin\plugins\rz_ghidra_sleigh\x86-64.sla
```

Expected: both `Test-Path` calls return `True`.

- [ ] **Step 7: Commit acquisition implementation**

```powershell
git add scripts/fetch_external_tools.ps1 scripts/fetch_external_tools.sh third_party/rz-ghidra/manifest.json install.ps1 install.sh
git commit -m "feat: fetch rz-ghidra runtime assets"
```

---

### Task 4: Wire Installers to the Shared Tool Contract

**Files:**
- Modify: `install.ps1`
- Modify: `install.sh`

- [ ] **Step 1: Move Windows rz-ghidra paths under the new tool root**

Change:

```powershell
$SleighHome = Join-Path $RizinRoot "lib\rizin\plugins\rz_ghidra_sleigh"
$GhidraPlugin = Join-Path $RizinRoot "lib\rizin\plugins\core_ghidra.dll"
```

to:

```powershell
$RzGhidraRoot = Join-Path $Root "third_party\rz-ghidra\0.8.0"
$SleighHome = Join-Path $RzGhidraRoot "lib\rizin\plugins\rz_ghidra_sleigh"
$GhidraPlugin = Join-Path $RzGhidraRoot "lib\rizin\plugins\core_ghidra.dll"
```

- [ ] **Step 2: Add Linux rz-ghidra detection**

After Rizin verification in `install.sh`, add:

```bash
if command -v rz-pm >/dev/null 2>&1; then
  :
fi
if "$RIZIN_BIN" -q -c 'Lc' 2>/dev/null | grep -E '(^|[[:space:]])pdgj([[:space:]]|$)' >/dev/null; then
  echo "AURA install: rz-ghidra pdgj available"
else
  echo "AURA install: rz-ghidra pdgj not available; pseudo-C will show install guidance"
fi
```

- [ ] **Step 3: Keep Windows strict when manifest supports rz-ghidra**

Keep these checks in `install.ps1` after the new root path:

```powershell
$GhidraPlugin = Require-File $GhidraPlugin "rz-ghidra plugin"
$SleighHome = Require-File $SleighHome "rz-ghidra SLEIGH directory"
Require-File (Join-Path $SleighHome "x86-64.sla") "x86-64 SLEIGH spec" | Out-Null
```

- [ ] **Step 4: Add Qt preflight for Windows GUI build**

Before `cmake -S` in the `if ($Build)` block:

```powershell
if (-not $NoGui) {
    $qtProbe = Get-Command qmake6 -ErrorAction SilentlyContinue
    if (-not $qtProbe -and -not $env:Qt6_DIR -and -not $env:CMAKE_PREFIX_PATH) {
        Fail-Install `
            -Problem "Qt6 was not found for GUI build." `
            -Cause "AURA_BUILD_GUI=ON requires Qt6::Widgets and Qt6::Network." `
            -Fix "Install Qt 6.7.x and set Qt6_DIR or CMAKE_PREFIX_PATH, or rerun with -NoGui."
    }
}
```

- [ ] **Step 5: Add Qt preflight for Linux GUI build**

Before `cmake -S` in `install.sh`:

```bash
if [ "$NO_GUI" -eq 0 ]; then
  if ! pkg-config --exists Qt6Widgets 2>/dev/null && [ -z "${Qt6_DIR:-}" ] && [ -z "${CMAKE_PREFIX_PATH:-}" ]; then
    fail_install \
      "Qt6 was not found for GUI build." \
      "AURA_BUILD_GUI=ON requires Qt6 Widgets." \
      "Install qt6-base-dev or rerun ./install.sh --no-gui."
  fi
fi
```

- [ ] **Step 6: Commit installer wiring**

```powershell
git add install.ps1 install.sh
git commit -m "fix: align installers with runtime tool contract"
```

---

### Task 5: Keep Safety Model and Dataset Installation Stable

**Files:**
- Modify: `scripts/download_safety_assets.py`
- Modify: `install.ps1`
- Modify: `install.sh`
- Test: local command verification

- [ ] **Step 1: Add repo-assets-only installer mode for fast validation**

Add `-RepoSafetyAssetsOnly` to `install.ps1`:

```powershell
[switch]$RepoSafetyAssetsOnly
```

Pass it to Python:

```powershell
$assetArgs = @(
    "--repo-root", $Root,
    "--aura-home", $AuraHome,
    "--manifest", $runtimeManifest
)
if ($RepoSafetyAssetsOnly) { $assetArgs += "--repo-assets-only" }
& $venvPython $downloadScript @assetArgs
```

- [ ] **Step 2: Add matching shell flag**

Add parser state:

```bash
REPO_SAFETY_ASSETS_ONLY=0
```

Add usage line:

```text
  --repo-safety-assets-only  Copy repo safety manifests/rules only; skip HF downloads.
```

Add case:

```bash
--repo-safety-assets-only)
  REPO_SAFETY_ASSETS_ONLY=1
  ;;
```

Build Python args:

```bash
ASSET_ARGS="--repo-root $ROOT --aura-home $AURA_HOME_DIR --manifest $ROOT/assets/safety/runtime-assets.json"
if [ "$REPO_SAFETY_ASSETS_ONLY" -eq 1 ]; then
  "$VENV_PY" "$ROOT/scripts/download_safety_assets.py" \
    --repo-root "$ROOT" \
    --aura-home "$AURA_HOME_DIR" \
    --manifest "$ROOT/assets/safety/runtime-assets.json" \
    --repo-assets-only
else
  "$VENV_PY" "$ROOT/scripts/download_safety_assets.py" \
    --repo-root "$ROOT" \
    --aura-home "$AURA_HOME_DIR" \
    --manifest "$ROOT/assets/safety/runtime-assets.json"
fi
```

- [ ] **Step 3: Validate repo-only safety install**

Run:

```powershell
$tmp = Join-Path $env:TEMP "aura-safety-repo-only"
Remove-Item -LiteralPath $tmp -Recurse -Force -ErrorAction SilentlyContinue
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
python .\scripts\download_safety_assets.py --repo-root . --aura-home $tmp --manifest .\assets\safety\runtime-assets.json --repo-assets-only
Test-Path "$tmp\rule-packs\default.json"
Test-Path "$tmp\safety-profiles\default.json"
```

Expected: both `Test-Path` calls return `True`.

- [ ] **Step 4: Commit safety installer ergonomics**

```powershell
git add install.ps1 install.sh scripts/download_safety_assets.py
git commit -m "chore: add lightweight safety asset install mode"
```

---

### Task 6: Update CI to Exercise the Same Install Contract

**Files:**
- Modify: `.github/workflows/orchestrator-smoke.yml`
- Modify: `.github/workflows/build.yml`

- [ ] **Step 1: Make orchestrator smoke fetch contract explicit**

In both Ubuntu and Windows jobs, keep the dedicated fetch step:

```yaml
- name: Fetch external tools
  run: bash scripts/fetch_external_tools.sh
```

For Windows:

```yaml
- name: Fetch external tools
  shell: pwsh
  run: ./scripts/fetch_external_tools.ps1
```

- [ ] **Step 2: Add a Windows rz-ghidra verification step when supported**

```yaml
- name: Verify rz-ghidra assets
  shell: pwsh
  run: |
    if (-not (Test-Path "third_party/rz-ghidra/0.8.0/lib/rizin/plugins/core_ghidra.dll")) {
      throw "core_ghidra.dll not found"
    }
    if (-not (Test-Path "third_party/rz-ghidra/0.8.0/lib/rizin/plugins/rz_ghidra_sleigh/x86-64.sla")) {
      throw "x86-64.sla not found"
    }
```

- [ ] **Step 3: Set SLEIGHHOME from rz-ghidra root**

```yaml
"SLEIGHHOME=$($env:GITHUB_WORKSPACE)\third_party\rz-ghidra\0.8.0\lib\rizin\plugins\rz_ghidra_sleigh" | Out-File -Append $env:GITHUB_ENV
```

- [ ] **Step 4: Keep generic build job non-GUI**

In `build.yml`, leave GUI off unless Qt is installed. The current `cmake -B build -DCMAKE_BUILD_TYPE=Release -DAURA_ENABLE_RIZIN=ON` remains acceptable because `AURA_BUILD_GUI` defaults OFF.

- [ ] **Step 5: Commit CI alignment**

```powershell
git add .github/workflows/orchestrator-smoke.yml .github/workflows/build.yml
git commit -m "ci: exercise shared runtime install contract"
```

---

### Task 7: Verify End-to-End Locally

**Files:**
- No source file changes expected

- [ ] **Step 1: Verify fetcher whitespace**

Run:

```powershell
git diff --check
```

Expected: no whitespace errors.

- [ ] **Step 2: Verify Windows installer lightweight mode**

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1 -SkipSafetyAssets
```

Expected: Rizin path printed. If rz-ghidra support is implemented, `SLEIGHHOME` is printed and points under `third_party\rz-ghidra\0.8.0`.

- [ ] **Step 3: Verify CMake smoke targets**

Run:

```powershell
cmake --build build-trim-gui --target orchestrator_smoke cli_smoke probe_engines_smoke gui_smoke --config Release -- /m
ctest --test-dir build-trim-gui -C Release -R "orchestrator_smoke|cli_smoke|probe_engines_smoke|gui_smoke" --output-on-failure
```

Expected: 4/4 tests passed.

- [ ] **Step 4: Verify safety assets remain intact**

Run:

```powershell
Test-Path "$HOME\.aura\token-classification-models\openai-privacy-filter\model.safetensors"
Test-Path "$HOME\.aura\token-classification-models\openai-privacy-filter\tokenizer.json"
Test-Path "$HOME\.aura\eval-datasets\korean-address-en-ko\manifest.aura.json"
Test-Path "$HOME\.aura\eval-datasets\korean-proper-noun-koen\manifest.aura.json"
```

Expected: all four lines print `True`.

- [ ] **Step 5: Push only after local verification**

```powershell
git status --short --branch
git push origin main
```

Expected: push succeeds and GitHub Actions starts new runs.

---

## Self-Review

**Spec coverage:** This plan covers the requested missing install surfaces: Rizin, rz-ghidra/Ghidra plugin, Qt, safety model, and safety datasets. It also covers CI and docs because the current bug is an installer/documentation/CI contract mismatch.

**Placeholder scan:** The only intentionally unresolved item is the rz-ghidra binary source selection in Task 3. It is represented as a decision step with acceptance rules because choosing an unverified archive in a plan would be unsafe.

**Type consistency:** Tool names are consistently `rizin` and `rz-ghidra`; the installed pseudo-C assets are consistently `core_ghidra.dll` and `rz_ghidra_sleigh/x86-64.sla`; runtime assets remain under `~/.aura`.
