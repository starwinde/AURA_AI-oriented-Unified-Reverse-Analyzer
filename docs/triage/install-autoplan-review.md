# Install Autoplan Review

Date: 2026-05-08
Scope: make root install scripts work for other users, not just the current Windows account.

## Plan Summary

The installer should create the user runtime registry under `~/.aura`, fetch
Rizin 0.8.0, rule packs, safety profiles, eval datasets, and the default token
classification model, then verify the result with actionable failure messages.

## Decisions

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|-------|----------|----------------|-----------|-----------|----------|
| 1 | CEO | Keep `~/.aura` as the default runtime registry | Auto | Product clarity | It keeps large models and datasets out of Git while giving every user a predictable local install location. | Storing model assets under the repo |
| 2 | CEO | Split install into tiers: tools, safety assets, build | Auto | User outcome | New users can recover from network/model failures without blocking Rizin-only GUI usage. | One all-or-nothing install path |
| 3 | Eng | Add explicit platform handling instead of Windows-only assumptions | Auto | Correctness | `Scripts/python.exe` and Visual Studio generator are Windows-specific and will fail on POSIX users. | Treating `install.ps1` as universal |
| 4 | Eng | Pin external model/dataset revisions in a manifest | Auto | Reproducibility | Hugging Face assets can change; installs must be repeatable for CI and demos. | Floating `main` snapshots |
| 5 | Eng | Add preflight checks and structured rescue text | Auto | Operability | Python, disk space, network, HF auth, and long paths fail differently and need different fixes. | Generic PowerShell exceptions |
| 6 | DX | Document one-command install and lightweight install | Auto | Time to first working run | Some users need GUI/Rizin only; others need the 2.8GB model path. | Making the huge model download mandatory without explanation |

## What Already Exists

- `install.ps1` bootstraps Rizin 0.8.0 and creates `~/.aura`.
- `scripts/fetch_external_tools.ps1` and `.sh` fetch Rizin from `third_party/rizin/manifest.json`.
- `assets/safety/` contains rule packs, safety profiles, eval dataset seed files, and a model manifest template.
- ADR-0054 and ADR-0058 define `~/.aura` runtime registries and `pii-python-venv`.

## Not In Scope

- Implementing the real `transformers` model runner.
- Uploading model weights or datasets to Git.
- Replacing the JSON runner protocol.
- Changing Rizin 0.8.0 as the execution baseline.

## Architecture

```text
repo root
  install.ps1 / install.sh
      |
      +-- preflight: shell, Python, disk, network, long path
      +-- tools: scripts/fetch_external_tools.* -> third_party/rizin/0.8.0-*
      +-- safety registry -> ~/.aura/
      |     +-- runners/pii-python-venv/
      |     +-- token-classification-models/openai-privacy-filter/
      |     +-- eval-datasets/
      |     +-- rule-packs/
      |     +-- safety-profiles/
      +-- verify: versions, required files, manifests, optional pdgj smoke
      +-- print: env vars and next commands
```

## Failure Modes

| Failure | Severity | Fix |
|---|---:|---|
| Python missing or wrong Python selected | High | Fail before downloads with install command examples. |
| Linux/mac user runs only Windows script | High | Add `install.sh` or a clear Windows-only banner. |
| Model download silently changes over time | High | Pin Hugging Face revisions in an installer manifest. |
| 2.8GB model download surprises users | Medium | Add `-SkipSafetyAssets` as documented lightweight path and print size warning. |
| HF unauthenticated rate limit | Medium | Support `HF_TOKEN` and explain retry/auth. |
| No disk-space check | Medium | Preflight free space before model download. |
| Env vars only affect installer process | Medium | Print exact per-shell export commands and optionally write `.env.local`. |

## Test Plan

| Test | Expected |
|---|---|
| `install.ps1 -SkipSafetyAssets` on clean Windows | Rizin 0.8.0 verified, no model download. |
| `install.ps1` on clean Windows | `~/.aura` registry populated and required model files verified. |
| Re-run `install.ps1` | Cache hit, no destructive overwrite, exits 0. |
| `install.ps1 -AuraHome <custom>` | All registry files created under the custom path. |
| Missing Python | Fails before partial install with problem/cause/fix text. |
| Blocked network | Keeps copied local rule packs and reports model download recovery command. |
| POSIX `install.sh` | Fetches Linux Rizin static runtime and creates POSIX venv layout. |

## DX Scorecard

| Dimension | Score | Notes |
|---|---:|---|
| Time to first working GUI | 7/10 | Good with Rizin cache; model path slows default install. |
| Guessable command | 8/10 | `install.ps1` is obvious on Windows. Needs `install.sh`. |
| Error recovery | 5/10 | Raw exceptions still leak through in some cases. |
| Cross-platform readiness | 4/10 | Current root installer is Windows-centric. |
| Reproducibility | 5/10 | Rizin is hashed; HF snapshots are not revision-pinned. |
| Disk/network transparency | 5/10 | Large model download should be announced before starting. |

## Recommendation

Approve implementation of a hardened installer pass before shipping this branch:

1. Add `install.sh` for Linux/mac parity.
2. Add `assets/safety/runtime-assets.json` or similar manifest with model/dataset repo ids, revisions, expected files, and size notes.
3. Refactor `install.ps1` into named phases with preflight and clearer rescue text.
4. Add README quickstart for full install vs lightweight install.
5. Verify Windows full/lightweight install and at least parse-check POSIX script locally.
