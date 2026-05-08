# fetch_external_tools.ps1 — Windows PowerShell counterpart to
# scripts/fetch_external_tools.sh. See ADR-0032 for the pattern.
#
# Override: $env:AURA_<TOOL>_BIN = "C:\path\to\rizin.exe" skips the manifest.

$ErrorActionPreference = "Stop"

$Root = Resolve-Path (Join-Path $PSScriptRoot "..")
$Tools = @("rizin")
$Platform = "windows-x86_64"

function Fetch-Tool {
    param([string]$Tool)

    $manifestPath = Join-Path $Root "third_party/$Tool/manifest.json"
    if (-not (Test-Path $manifestPath)) {
        throw "fetch_external_tools: ${Tool}: missing manifest at $manifestPath"
    }

    $overrideName = "AURA_$($Tool.ToUpper())_BIN"
    $overrideVal = [Environment]::GetEnvironmentVariable($overrideName)
    if ($overrideVal) {
        Write-Host "fetch_external_tools: $Tool`: using override $overrideName=$overrideVal"
        return
    }

    $manifest = Get-Content $manifestPath -Raw | ConvertFrom-Json
    $version = $manifest.version
    $plat = $manifest.platforms.$Platform
    if (-not $plat) {
        throw "fetch_external_tools: $Tool`: no entry for platform $Platform"
    }
    $installDir = $plat.install_dir
    if (-not $installDir) {
        throw "fetch_external_tools: $Tool`: platform $Platform missing install_dir"
    }

    $destDir = Join-Path $Root "third_party/$Tool/$installDir"
    $binPath = Join-Path $destDir $plat.binary_relpath

    $requiredRelpaths = @($plat.binary_relpath)
    if ($plat.PSObject.Properties.Name -contains "required_relpaths") {
        $requiredRelpaths = @($plat.required_relpaths)
    }

    $missingRequired = @()
    foreach ($relpath in $requiredRelpaths) {
        $requiredPath = Join-Path $destDir $relpath
        if (-not (Test-Path $requiredPath)) {
            $missingRequired += $relpath
        }
    }

    if ($missingRequired.Count -eq 0) {
        Write-Host "fetch_external_tools: $Tool@$version`: cache hit ($binPath)"
        return
    }

    if ((Test-Path $destDir) -and (Test-Path $binPath)) {
        Write-Host "fetch_external_tools: $Tool@$version`: cache incomplete, missing $($missingRequired -join ', '); refreshing"
        Remove-Item -LiteralPath $destDir -Recurse -Force
    }

    Write-Host "fetch_external_tools: $Tool@$version`: downloading from $($plat.url)"
    $tmpArchive = [System.IO.Path]::GetTempFileName() + "." + $plat.archive
    try {
        Invoke-WebRequest -Uri $plat.url -OutFile $tmpArchive -UseBasicParsing

        $hash = (Get-FileHash -Path $tmpArchive -Algorithm SHA256).Hash.ToLower()
        if ($hash -ne $plat.sha256.ToLower()) {
            throw @"
fetch_external_tools: $Tool@$version`: sha256 mismatch
  expected: $($plat.sha256)
  actual:   $hash
"@
        }

        New-Item -ItemType Directory -Force -Path $destDir | Out-Null

        switch ($plat.archive) {
            "zip" {
                if ($plat.strip_components -eq 0) {
                    Expand-Archive -Path $tmpArchive -DestinationPath $destDir -Force
                } else {
                    $tmpExtract = New-Item -ItemType Directory -Path ([System.IO.Path]::Combine([System.IO.Path]::GetTempPath(), [System.IO.Path]::GetRandomFileName()))
                    Expand-Archive -Path $tmpArchive -DestinationPath $tmpExtract -Force
                    $src = $tmpExtract
                    for ($i = 0; $i -lt $plat.strip_components; $i++) {
                        $src = (Get-ChildItem $src | Select-Object -First 1).FullName
                    }
                    Copy-Item -Path "$src/*" -Destination $destDir -Recurse -Force
                    Remove-Item -Path $tmpExtract -Recurse -Force
                }
            }
            default {
                throw "fetch_external_tools: $Tool`: unsupported archive type '$($plat.archive)' on Windows"
            }
        }

        foreach ($relpath in $requiredRelpaths) {
            $requiredPath = Join-Path $destDir $relpath
            if (-not (Test-Path $requiredPath)) {
                throw "fetch_external_tools: $Tool`: required path not found at $requiredPath after extract"
            }
        }
        Write-Host "fetch_external_tools: $Tool@$version`: ready at $binPath"
    }
    finally {
        Remove-Item -Path $tmpArchive -ErrorAction SilentlyContinue
    }
}

foreach ($tool in $Tools) {
    Fetch-Tool $tool
}
