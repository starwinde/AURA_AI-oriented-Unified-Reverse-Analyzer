# QA Gate Stale Build Guard Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make AURA's local release gate rebuild affected test binaries before running `ctest`, so stale executables cannot create false validation failures.

**Architecture:** Add one explicit local verification entrypoint per platform that builds the known gate targets first, then runs the full CTest suite. Keep the scripts thin wrappers around CMake/CTest, with no hidden test filtering, so they match the existing developer workflow while making the required build step impossible to forget.

**Tech Stack:** PowerShell 5+/7, POSIX shell, CMake/MSBuild or Ninja, CTest, existing AURA `build-trim-gui` build tree.

---

## Scope

This plan fixes the validation workflow, not MCP runtime behavior and not probe engine logic. The immediate failure observed on 2026-05-09 was resolved by rebuilding `probe_unit` before rerunning `ctest`; therefore the implementation focuses on making that rebuild a first-class release-gate step.

## Failure Analysis

The finishing workflow initially ran the full CTest suite against `build-trim-gui` and `probe_unit` failed in seven rizin-related cases. Rebuilding only `probe_unit` made those failures disappear, and the subsequent full CTest suite passed `12/12`.

Root cause: raw `ctest` can execute a stale test executable when a previous development step rebuilt only a subset of targets. The failure looked like a rizin resolver bug because fake-runner scripts were not matching the stale binary's behavior, but the current source and rebuilt test target were correct.

Required prevention: every release gate must build stale-prone unit targets before running full CTest. For this branch, the minimum target set is `probe_unit` and `mcp_unit`, followed by the full build tree and then full CTest.

## File Structure

- Create: `scripts/verify_release_gate.ps1`
  - Windows release-gate entrypoint.
  - Builds `probe_unit`, `mcp_unit`, and the full selected build tree before running CTest.
  - Exits non-zero on the first failing command.
- Create: `scripts/verify_release_gate.sh`
  - Linux/macOS-style release-gate entrypoint.
  - Mirrors the PowerShell behavior.
- Modify: `docs/test_plan.md`
  - Documents that release verification must use the new scripts, not raw `ctest` first.
- Modify: `README.md`
  - Adds the short local verification command for contributors.
- Modify: `Tasks.md`
  - Records the QA-gate hardening item as completed after implementation.

## Task 1: Add Windows Release-Gate Script

**Files:**
- Create: `scripts/verify_release_gate.ps1`

- [ ] **Step 1: Create the PowerShell script with strict command failure handling**

Create `scripts/verify_release_gate.ps1` with this full content:

```powershell
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
```

- [ ] **Step 2: Run the script from the repo root**

Run:

```powershell
.\scripts\verify_release_gate.ps1
```

Expected:

```text
==> Build probe_unit
==> Build mcp_unit
==> Build full tree
==> Run full CTest suite
100% tests passed, 0 tests failed out of 12
```

- [ ] **Step 3: Commit the Windows script**

Run:

```powershell
git add scripts/verify_release_gate.ps1
git commit -m "chore: add Windows release gate verifier"
```

Expected:

```text
[codex/... chore: add Windows release gate verifier]
```

## Task 2: Add POSIX Release-Gate Script

**Files:**
- Create: `scripts/verify_release_gate.sh`

- [ ] **Step 1: Create the shell script that mirrors the Windows verifier**

Create `scripts/verify_release_gate.sh` with this full content:

```sh
#!/usr/bin/env sh
set -eu

BUILD_DIR="${1:-build-trim-gui}"
CONFIG="${2:-Release}"

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)

cd "$REPO_ROOT"

run_step() {
    name="$1"
    shift
    printf '==> %s\n' "$name"
    "$@"
}

run_step "Build probe_unit" cmake --build "$BUILD_DIR" --config "$CONFIG" --target probe_unit
run_step "Build mcp_unit" cmake --build "$BUILD_DIR" --config "$CONFIG" --target mcp_unit
run_step "Build full tree" cmake --build "$BUILD_DIR" --config "$CONFIG"
run_step "Run full CTest suite" ctest --test-dir "$BUILD_DIR" -C "$CONFIG" --output-on-failure
```

- [ ] **Step 2: Verify shell syntax**

Run:

```powershell
bash -n scripts/verify_release_gate.sh
```

Expected:

```text
```

The command exits `0` and prints no syntax errors.

- [ ] **Step 3: Run the shell verifier where bash is available**

Run:

```powershell
bash scripts/verify_release_gate.sh build-trim-gui Release
```

Expected:

```text
==> Build probe_unit
==> Build mcp_unit
==> Build full tree
==> Run full CTest suite
100% tests passed, 0 tests failed out of 12
```

- [ ] **Step 4: Commit the POSIX script**

Run:

```powershell
git add scripts/verify_release_gate.sh
git commit -m "chore: add POSIX release gate verifier"
```

Expected:

```text
[codex/... chore: add POSIX release gate verifier]
```

## Task 3: Document the Correct Verification Order

**Files:**
- Modify: `docs/test_plan.md`
- Modify: `README.md`

- [ ] **Step 1: Add release-gate section to `docs/test_plan.md`**

Add this section near the existing build/test instructions:

````markdown
## Local Release Gate

Use the release-gate wrapper before merging or shipping a branch:

```powershell
.\scripts\verify_release_gate.ps1
```

The wrapper intentionally rebuilds `probe_unit` and `mcp_unit` before the full CTest pass. Running raw `ctest` first can execute stale test binaries when only a subset of targets was rebuilt.

Expected result:

```text
100% tests passed, 0 tests failed out of 12
```
````

- [ ] **Step 2: Add contributor command to `README.md`**

Add this short block under the local build/test section:

````markdown
### Release verification

Before merging or pushing a completed branch on Windows:

```powershell
.\scripts\verify_release_gate.ps1
```

On Linux or WSL:

```sh
sh scripts/verify_release_gate.sh build-trim-gui Release
```
````

- [ ] **Step 3: Verify Markdown snippets are present**

Run:

```powershell
Select-String -Path docs/test_plan.md -Pattern "Local Release Gate"
Select-String -Path README.md -Pattern "Release verification"
```

Expected:

```text
docs/test_plan.md:...:## Local Release Gate
README.md:...:### Release verification
```

- [ ] **Step 4: Commit documentation**

Run:

```powershell
git add docs/test_plan.md README.md
git commit -m "docs: document release gate verifier"
```

Expected:

```text
[codex/... docs: document release gate verifier]
```

## Task 4: Record the QA Hardening in `Tasks.md`

**Files:**
- Modify: `Tasks.md`

- [ ] **Step 1: Add a completed task entry**

Add this entry to the current MCP/QA task area:

```markdown
- [x] Harden local release verification against stale test binaries.
  - Added `scripts/verify_release_gate.ps1` and `scripts/verify_release_gate.sh`.
  - Gate order: build `probe_unit`, build `mcp_unit`, build full tree, run full CTest suite.
  - Regression reason: raw `ctest` can execute stale test executables after partial target builds.
```

- [ ] **Step 2: Verify task entry is discoverable**

Run:

```powershell
Select-String -Path Tasks.md -Pattern "stale test binaries"
```

Expected:

```text
Tasks.md:...:- [x] Harden local release verification against stale test binaries.
```

- [ ] **Step 3: Commit task index update**

Run:

```powershell
git add Tasks.md
git commit -m "docs: record release gate hardening"
```

Expected:

```text
[codex/... docs: record release gate hardening]
```

## Task 5: Final Verification and Branch Finish

**Files:**
- No new source files.
- Validate all files from Tasks 1-4.

- [ ] **Step 1: Run Windows verifier as the primary local gate**

Run:

```powershell
.\scripts\verify_release_gate.ps1
```

Expected:

```text
100% tests passed, 0 tests failed out of 12
```

- [ ] **Step 2: Verify MCP-specific tests still pass**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -L mcp --output-on-failure
```

Expected:

```text
100% tests passed, 0 tests failed out of 2
```

- [ ] **Step 3: Verify working tree only contains intended files**

Run:

```powershell
git status --short
```

Expected includes only the release-gate scripts, docs, and any already-approved MCP envelope changes:

```text
 M README.md
 M Tasks.md
 M docs/test_plan.md
 M include/aura/mcp/mcp_envelope.h
 M src/mcp/mcp_envelope.cpp
 M tests/unit/mcp/mcp_unit.cpp
?? docs/superpowers/plans/2026-05-09-mcp-real-use-fine-grain.md
?? docs/superpowers/plans/2026-05-09-qa-gate-stale-build-guard.md
?? scripts/verify_release_gate.ps1
?? scripts/verify_release_gate.sh
```

- [ ] **Step 4: Run finishing branch workflow**

Run the finishing skill after all commits are in place:

```text
[$superpowers:finishing-a-development-branch](C:\Users\21m15\.codex\plugins\cache\openai-curated\superpowers\f812c146\skills\finishing-a-development-branch\SKILL.md)
```

Expected:

```text
Implementation complete. What would you like to do?
```

## Self-Review

- Spec coverage: The plan addresses the observed failure mode by rebuilding stale-prone targets before full CTest. It also records the behavior in docs so the next finishing run does not repeat the raw-CTest-first sequence.
- Placeholder scan: No placeholder markers or unspecified implementation steps remain.
- Type and command consistency: Both scripts use the same default build directory (`build-trim-gui`) and configuration (`Release`), matching the failing and later passing verification run.

## Execution Handoff

Plan complete and saved to `docs/superpowers/plans/2026-05-09-qa-gate-stale-build-guard.md`. Two execution options:

1. Subagent-Driven (recommended) - dispatch a fresh subagent per task, with review between tasks.
2. Inline Execution - implement the scripts and docs directly in this session with milestone checks.
