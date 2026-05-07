# rebuild_fixtures.ps1 — Windows half of the fixture rebuild flow.
# Builds tests/fixtures/bin/pe_smoke.x86_64.exe via MSVC cl.exe.
#
# Requires Visual Studio 2022 Build Tools. The script auto-locates
# vcvars64.bat via vswhere.exe.
$ErrorActionPreference = "Stop"

$Root = Resolve-Path (Join-Path $PSScriptRoot "..")
$Src = Join-Path $Root "tests/fixtures/sources/aura_smoke.c"
$OutDir = Join-Path $Root "tests/fixtures/bin"
$Out = Join-Path $OutDir "pe_smoke.x86_64.exe"

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$VsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $VsWhere)) {
    throw "rebuild_fixtures: vswhere.exe not found at $VsWhere — install VS Build Tools."
}

$VsRoot = & $VsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $VsRoot) {
    throw "rebuild_fixtures: no MSVC toolchain found via vswhere"
}
$VcVars = Join-Path $VsRoot "VC\Auxiliary\Build\vcvars64.bat"
if (-not (Test-Path $VcVars)) {
    throw "rebuild_fixtures: vcvars64.bat missing at $VcVars"
}

Write-Host "rebuild_fixtures: building PE -> $Out"
# Import vcvars env into the current PowerShell process (so cl.exe runs with
# correct PATH/INCLUDE/LIB without spawning cmd /c "...path with korean..." bat
# files that corrupt under MBCS).
& cmd.exe /c "`"$VcVars`" >NUL 2>&1 && set" 2>$null | ForEach-Object {
    if ($_ -match '^([^=]+)=(.*)$') {
        Set-Item -Path "Env:$($matches[1])" -Value $matches[2]
    }
}

$ObjOut = Join-Path $OutDir "aura_smoke.obj"
& cl.exe /nologo /Od /Fo:"$ObjOut" /Fe:"$Out" "$Src" /link /SUBSYSTEM:CONSOLE /INCREMENTAL:NO 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) {
    throw "rebuild_fixtures: cl.exe exit $LASTEXITCODE"
}
Remove-Item $ObjOut -ErrorAction SilentlyContinue
if (-not (Test-Path $Out)) {
    throw "rebuild_fixtures: cl.exe completed but output missing"
}
Write-Host "rebuild_fixtures: PE build OK"

Write-Host ""
Write-Host "ELF fixture (elf_smoke.x86_64) must be rebuilt on Linux via:"
Write-Host "    bash scripts/rebuild_fixtures.sh"
