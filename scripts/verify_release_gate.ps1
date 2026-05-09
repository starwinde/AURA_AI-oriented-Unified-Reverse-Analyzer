param(
    [string]$BuildDir = "build-trim-gui",
    [string]$Config = "Release"
)

$ErrorActionPreference = "Stop"

function Invoke-Step {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Name,
        [Parameter(Mandatory = $true)]
        [scriptblock]$Command
    )

    # Keep each step to one native command so $LASTEXITCODE maps to the step.
    Write-Host "==> $Name"
    & $Command
    if ($LASTEXITCODE -ne 0) {
        throw "$Name failed with exit code $LASTEXITCODE"
    }
}

$RepoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
Push-Location $RepoRoot
try {
    Invoke-Step "Build probe_unit" {
        cmake --build $BuildDir --config $Config --target probe_unit
    }
    Invoke-Step "Build mcp_unit" {
        cmake --build $BuildDir --config $Config --target mcp_unit
    }
    Invoke-Step "Build full tree" {
        cmake --build $BuildDir --config $Config
    }
    Invoke-Step "Run full CTest suite" {
        ctest --test-dir $BuildDir -C $Config --output-on-failure
    }
}
finally {
    Pop-Location
}
