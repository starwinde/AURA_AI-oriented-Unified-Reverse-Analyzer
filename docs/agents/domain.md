# Domain Docs

How the engineering skills should consume this repo's domain
documentation when exploring the codebase.

This repo is **single-context**: one `CONTEXT.md` + `docs/adr/` at the
root cover the whole project (no `CONTEXT-MAP.md`, not a monorepo).

## Before exploring, read these

- **`CONTEXT.md`** at the repo root (domain glossary).
- **`docs/adr/`** — read ADRs that touch the area you're about to
  work in.

If any of these files don't exist, **proceed silently**. Don't flag
their absence; don't suggest creating them upfront. The producer skill
(`/grill-with-docs`) creates them lazily when terms or decisions
actually get resolved.

## Existing design docs (already in the repo)

`docs/design/` already contains targeted design notes (e.g.
`d_phase4_stable_identity.md`, `d_rizin_skeleton.md`). Treat these as
authoritative for the sub-system they describe — they predate this
glossary convention and remain the source of truth for their topic.
ADRs under `docs/adr/` are for **decisions** (the why); design docs
under `docs/design/` are for **mechanism** (the how). Cite both when
they overlap.

## File structure

```
/
├── CONTEXT.md          ← domain glossary (created lazily)
├── docs/
│   ├── adr/            ← decision records (created lazily)
│   ├── agents/         ← this file + sibling agent-config docs
│   └── design/         ← existing per-subsystem design notes
└── src/
```

## Use the glossary's vocabulary

When your output names a domain concept (in an issue title, a refactor
proposal, a hypothesis, a test name), use the term as defined in
`CONTEXT.md`. Don't drift to synonyms the glossary explicitly avoids.

If the concept you need isn't in the glossary yet, that's a signal —
either you're inventing language the project doesn't use (reconsider)
or there's a real gap (note it for `/grill-with-docs`).

## Flag ADR conflicts

If your output contradicts an existing ADR, surface it explicitly
rather than silently overriding:

> _Contradicts ADR-0007 (event-sourced orders) — but worth reopening because…_
