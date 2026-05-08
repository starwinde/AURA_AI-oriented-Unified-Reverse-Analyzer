# PII Model and Dataset UI Autoplan Review

Date: 2026-05-08
Branch: main
Mode: autoplan, selective expansion

## Plan Summary

This development should add a user-facing Safety Assets surface that lets users
select the active PII safety profile and inspect the selected profile's token
classification model, rule packs, and eval datasets. It verifies that the
selected profile is reflected in the GUI string-protection flow.

The current repo already has the runtime asset layout under `~/.aura`, pinned
runtime asset manifests, safety profiles, rule packs, and default GUI string
protection. What is missing is a UI/UX layer for choosing the active profile
that contains those assets and a runtime contract that proves the GUI is using
the selected configuration instead of always calling `loadDefaultSafetyProfile()`.

## What Already Exists

- `assets/safety/runtime-assets.json` lists the installed model and eval dataset
  runtime assets.
- `assets/safety/safety-profiles/default.json` and `high-security.json` define
  profile-level policy.
- `install.ps1` and `install.sh` populate `~/.aura`.
- `src/core/safety/string_safety.cpp` loads the default safety profile from
  `~/.aura/safety-profiles/default.json` with repo fallback.
- `src/gui/main_window.cpp` applies the loaded default profile to extracted
  strings and displays masked/protected values.

## NOT In Scope

- Training or fine-tuning a new PII model.
- Uploading model weights or datasets to Git.
- Changing the Rizin 0.8.0 baseline.
- Making eval datasets affect live masking directly.
- Adding a broad new Safety workspace tab for every future MCP/LLM policy
  feature.

## CEO Review

Score: 8/10.

The feature is worth doing because the project already claims runtime assets are
replaceable, but users currently cannot operate that from the GUI. The product
risk is conceptual: if the UI says "change dataset" next to live masking output,
users may think the dataset changes current detection. Per ADR-0054, eval
datasets are for measuring model/rule quality, not for live detection.

Recommendation: ship this as **Safety Assets Settings** rather than "dataset
switcher". The top-level user task is "choose the active privacy protection
configuration"; dataset selection is a secondary evaluation setting.

## Design Review

Score: 7/10.

Recommended UX:

```text
Settings / Safety
  Profile
    Active profile: [Default v] [High Security v] [Import Profile]
    Summary: model, rule packs, eval datasets, policy mode

  Detection
    Token classification model: [openai-privacy-filter v]
    Rule packs: [x] Korean sensitive  [x] Secret/API key

  Evaluation
    Eval datasets: [x] safety-default
                   [ ] korean-address-en-ko
                   [ ] korean-proper-noun-koen
    [Run eval] [View last report]

  Runtime
    AURA_HOME: ...
    Safety assets: ...
    [Open folder] [Refresh assets]
```

Do not put this into the first-viewport analysis experience. Put it behind a
settings/action surface so the normal reverse-engineering workflow stays quiet.
In the Strings tree, show only a compact "Safety: Default" status and a refresh
or settings action.

## Engineering Review

Score: 6.5/10 before implementation.

Current blocker: `MainWindow` calls `loadDefaultSafetyProfile()` directly during
string import. That makes GUI selection impossible without either global mutable
state or a new profile-loading API.

Recommended architecture:

```text
~/.aura/
  safety-profiles/*.json
  token-classification-models/*/manifest.json
  rule-packs/*/manifest.json
  eval-datasets/*/manifest.aura.json
        |
        v
core safety asset registry
  list profiles/models/rule packs/eval datasets
  load profile by id/path
  validate referenced assets
        |
        v
GUI Safety Settings Dialog
  choose profile
  inspect selected model/rule/eval selections
  save selected profile id to QSettings
        |
        v
MainWindow string import
  load selected profile
  scan strings with rule packs
  show active safety status in Strings UI
```

Required core API additions:

- `listSafetyProfiles()`
- `listTokenClassificationModels()`
- `listRulePacks()`
- `listEvalDatasets()`
- `loadSafetyProfileById(id)`
- `validateSafetyProfile(profile)`
- `resolveSelectedSafetyProfile(settings_profile_id)`

## DX Review

Score: 7/10.

The installed asset layout is now good enough for developers, but discoverability
is weak. A new contributor needs a small CLI inspection command or at least a
documented JSON shape to add custom assets.

Recommended developer rule:

- GUI reads committed/runtime manifests.
- Install scripts download assets.
- Users add local assets under `~/.aura`.
- Developers test the registry with fast tests that do not download models.

## Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|-------|----------|----------------|-----------|-----------|----------|
| 1 | CEO | Build Safety Assets Settings, not a dataset-only switcher | Auto | Product clarity | The actual user value is active protection configuration; datasets alone do not change live masking. | Dataset-only selector |
| 2 | Design | Keep controls in settings, show compact status in Strings | Auto | Existing UX fit | ADR-0055 keeps Safety v1 under Strings and avoids a misleading full Safety tab. | New first-class Safety workspace tab |
| 3 | Eng | Add core registry/profile APIs before GUI wiring | Auto | Shared runtime contract | GUI, CLI, and future MCP need the same asset resolution rules. | GUI-only file scanning |
| 4 | Eng | Treat eval datasets as evaluation inputs, not live detection inputs | Auto | Correct domain model | ADR-0054 defines eval datasets as benchmark material. | Dataset affects string masking directly |
| 5 | DX | Add fast registry tests without downloading model weights | Auto | Practical verification | CI should validate asset discovery and profile validation cheaply. | Network-dependent GUI tests |

## Failure Modes Registry

| Failure mode | Severity | Mitigation |
|--------------|----------|------------|
| UI says dataset changed but masking output does not change | High | Label datasets under Evaluation only and explain via grouping, not prose-heavy warning. |
| Profile references missing model/rule/dataset | High | Validate profile and show disabled/error state with problem, cause, fix. |
| GUI saves profile id that no longer exists | Medium | Fall back to default profile and show a one-time status warning. |
| User imports a huge or malformed asset manifest | Medium | Validate JSON schema and never load model weights in the GUI selection dialog. |
| CLI and GUI resolve different profiles | High | Put registry and profile resolution in core safety module. |

## Test Diagram

```text
Core registry lists assets
  -> unit: repo assets only
  -> unit: ~/.aura override assets
  -> unit: malformed manifest rejected

Profile loading by id
  -> unit: default profile
  -> unit: high-security profile
  -> unit: missing selected profile fallback

GUI settings selection
  -> gui_smoke: dialog opens
  -> gui_smoke: selected profile saved to QSettings
  -> gui_smoke: reload uses saved profile

String protection flow
  -> integration: MainWindow uses selected profile, not hardcoded default
  -> unit: different rule pack selection changes protected findings

Eval dataset selection
  -> unit: selected eval dataset ids persisted
  -> no live masking expectation
```

## Implementation Checklist

1. Add core safety asset registry structs and listing functions.
2. Add profile-by-id loading and validation.
3. Add selected profile persistence through `QSettings`.
4. Add Safety Settings dialog or Settings section with profile/model/rule/eval
   asset lists.
5. Wire `MainWindow` string protection to selected profile resolution.
6. Show active safety profile/status in the Strings UI.
7. Add unit tests for registry/profile validation.
8. Add GUI smoke coverage for opening settings and persisting a profile choice.
9. Update README/docs to explain runtime asset replacement and UI selection.

## Final Recommendation

Approve the feature with one scope correction: call it **Safety Assets Settings**
and make profile selection the primary UX. In the current implementation, rule
pack choices affect live runtime string detection. Model choices and model
policy are surfaced and validated but are not yet wired into live masking. Eval
dataset choices affect evaluation/reporting only.
