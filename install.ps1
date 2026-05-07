# AURA root installer/bootstrap script.
#
# Default:
#   - fetches the approved external runtime tools
#   - verifies the Rizin 0.8.0 shared64 + rz-ghidra baseline
#   - prints the environment variables needed for the current shell
#
# Optional:
#   ./install.ps1 -Build
#   ./install.ps1 -Build -BuildDir build-local -Config Release

[CmdletBinding()]
param(
    [switch]$Build,
    [string]$BuildDir = "build-local",
    [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
    [string]$Config = "Release",
    [switch]$NoGui,
    [switch]$SkipSafetyAssets,
    [string]$AuraHome = ""
)

$ErrorActionPreference = "Stop"

function Resolve-RepoRoot {
    $scriptPath = $MyInvocation.MyCommand.Path
    if (-not $scriptPath) {
        return (Resolve-Path ".").Path
    }
    return (Resolve-Path (Split-Path -Parent $scriptPath)).Path
}

function Require-File {
    param(
        [string]$Path,
        [string]$Description
    )
    if (-not (Test-Path -LiteralPath $Path)) {
        throw "Missing $Description at: $Path"
    }
    return (Resolve-Path -LiteralPath $Path).Path
}

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

function Resolve-Python {
    foreach ($candidate in @("py", "python", "python3")) {
        $cmd = Get-Command $candidate -ErrorAction SilentlyContinue
        if ($cmd) {
            return $cmd.Source
        }
    }
    Fail-Install `
        -Problem "Python 3 was not found." `
        -Cause "The PII runner uses an AURA-managed Python venv, but no py/python/python3 command is available." `
        -Fix "Install Python 3.10+ and rerun: powershell -NoProfile -ExecutionPolicy Bypass -File .\install.ps1"
}

function New-OrUpdate-PiiVenv {
    param(
        [string]$PythonExe,
        [string]$VenvDir
    )
    if (-not (Test-Path -LiteralPath (Join-Path $VenvDir "Scripts\python.exe"))) {
        Write-Host "AURA install: creating PII runner venv at $VenvDir"
        & $PythonExe -m venv $VenvDir
    }
    $venvPython = Require-File (Join-Path $VenvDir "Scripts\python.exe") "PII runner venv Python"
    & $venvPython -m pip install --upgrade pip | Out-Host
    & $venvPython -m pip install --upgrade "huggingface_hub==1.14.0" | Out-Host
    Write-Output $venvPython
}

$Root = Resolve-RepoRoot
Assert-WindowsHost
Set-Location $Root

if (-not $AuraHome) {
    if ($env:AURA_HOME) {
        $AuraHome = $env:AURA_HOME
    } else {
        $AuraHome = Join-Path $HOME ".aura"
    }
}
$AuraHome = (New-Item -ItemType Directory -Force -Path $AuraHome).FullName
if ($SkipSafetyAssets) {
    Assert-FreeSpace -Path $AuraHome -RequiredBytes 1GB -Description "Rizin and lightweight AURA runtime assets"
} else {
    Assert-FreeSpace -Path $AuraHome -RequiredBytes 6GB -Description "AURA safety model and eval datasets"
}

$RizinRoot = Join-Path $Root "third_party\rizin\0.8.0-shared\rizin-win-installer-clang_cl-64"
$RizinBin = Join-Path $RizinRoot "bin\rizin.exe"
$SleighHome = Join-Path $RizinRoot "lib\rizin\plugins\rz_ghidra_sleigh"
$GhidraPlugin = Join-Path $RizinRoot "lib\rizin\plugins\core_ghidra.dll"

Write-Host "AURA install: root=$Root"
Write-Host "AURA install: fetching external tools from manifest"

$oldRizinBin = $env:AURA_RIZIN_BIN
$oldRizinPath = $env:AURA_RIZIN_PATH
try {
    Remove-Item Env:AURA_RIZIN_BIN -ErrorAction SilentlyContinue
    Remove-Item Env:AURA_RIZIN_PATH -ErrorAction SilentlyContinue
    & (Join-Path $Root "scripts\fetch_external_tools.ps1")
}
finally {
    if ($oldRizinBin) { $env:AURA_RIZIN_BIN = $oldRizinBin }
    if ($oldRizinPath) { $env:AURA_RIZIN_PATH = $oldRizinPath }
}

$RizinBin = Require-File $RizinBin "Rizin 0.8.0 executable"
$GhidraPlugin = Require-File $GhidraPlugin "rz-ghidra plugin"
$SleighHome = Require-File $SleighHome "rz-ghidra SLEIGH directory"
Require-File (Join-Path $SleighHome "x86-64.sla") "x86-64 SLEIGH spec" | Out-Null

Write-Host "AURA install: verifying Rizin version"
$versionOutput = (& $RizinBin -v) -join "`n"
Write-Host $versionOutput
if ($versionOutput -notmatch "rizin 0\.8\.0") {
    throw "Unexpected Rizin version. Expected 0.8.0, got: $versionOutput"
}

$env:AURA_REPO_ROOT = $Root
$env:AURA_RIZIN_BIN = $RizinBin
$env:AURA_RIZIN_PATH = $RizinBin
$env:SLEIGHHOME = $SleighHome
$env:AURA_HOME = $AuraHome
$env:AURA_SAFETY_ASSETS_DIR = Join-Path $AuraHome "assets\safety"

Write-Host "AURA install: verified Rizin 0.8.0 shared64 + rz-ghidra baseline"
Write-Host "AURA_REPO_ROOT=$env:AURA_REPO_ROOT"
Write-Host "AURA_RIZIN_BIN=$env:AURA_RIZIN_BIN"
Write-Host "AURA_RIZIN_PATH=$env:AURA_RIZIN_PATH"
Write-Host "SLEIGHHOME=$env:SLEIGHHOME"

if (-not $SkipSafetyAssets) {
    Write-Host "AURA install: preparing safety runtime registry under $AuraHome"

    $python = Resolve-Python
    $venvDir = Join-Path $AuraHome "runners\pii-python-venv"
    $venvPython = New-OrUpdate-PiiVenv -PythonExe $python -VenvDir $venvDir

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

    $modelManifest = Require-File `
        (Join-Path $AuraHome "token-classification-models\openai-privacy-filter\manifest.json") `
        "openai-privacy-filter model manifest"
    Require-File `
        (Join-Path $AuraHome "token-classification-models\openai-privacy-filter\model.safetensors") `
        "openai/privacy-filter model weights" | Out-Null
    Require-File `
        (Join-Path $AuraHome "token-classification-models\openai-privacy-filter\tokenizer.json") `
        "openai/privacy-filter tokenizer" | Out-Null
    Require-File `
        (Join-Path $AuraHome "eval-datasets\safety-default\manifest.json") `
        "default safety eval dataset manifest" | Out-Null
    Require-File `
        (Join-Path $AuraHome "safety-profiles\default.json") `
        "default safety profile" | Out-Null
    Write-Host "AURA_PII_RUNNER_VENV=$venvDir"
    Write-Host "AURA_PII_MODEL_MANIFEST=$modelManifest"
}

Write-Host "AURA_HOME=$env:AURA_HOME"
Write-Host "AURA_SAFETY_ASSETS_DIR=$env:AURA_SAFETY_ASSETS_DIR"

if ($Build) {
    $guiFlag = if ($NoGui) { "OFF" } else { "ON" }
    Write-Host "AURA install: configuring CMake in $BuildDir (GUI=$guiFlag)"
    cmake -S $Root -B $BuildDir -G "Visual Studio 17 2022" -A x64 `
        -DAURA_ENABLE_RIZIN=ON `
        -DAURA_BUILD_GUI=$guiFlag `
        -DAURA_BUILD_TESTS=ON

    Write-Host "AURA install: building core targets ($Config)"
    cmake --build $BuildDir --target aura probe_unit cli_smoke probe_engines_smoke --config $Config

    if (-not $NoGui) {
        cmake --build $BuildDir --target aura-gui gui_smoke --config $Config
    }
}

Write-Host "AURA install: done"
