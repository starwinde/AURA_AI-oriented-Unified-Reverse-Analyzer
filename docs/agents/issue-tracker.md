# Issue tracker: Local Markdown

Issues and PRDs for this repo live as markdown files in `.scratch/`.

This repo has no git remote and is tracked locally; the existing
`Tasks.md` and `AUTOMATION_ROADMAP.md` continue to own *phase-level*
project state. The `.scratch/` tree is for *issue-level* artefacts
that the agent skills produce (PRDs, decomposed implementation tickets,
QA findings, triage notes).

## Conventions

- One feature per directory: `.scratch/<feature-slug>/`
- The PRD is `.scratch/<feature-slug>/PRD.md`
- Implementation issues are `.scratch/<feature-slug>/issues/<NN>-<slug>.md`, numbered from `01`
- Triage state is recorded as a `Status:` line near the top of each issue file (see `triage-labels.md` for the role strings)
- Comments and conversation history append to the bottom of the file under a `## Comments` heading

## Relationship to `Tasks.md` / `AUTOMATION_ROADMAP.md`

`Tasks.md` and `AUTOMATION_ROADMAP.md` remain canonical for Phase /
Step state per `CLAUDE.md` and `rules.md §11`. Issue files under
`.scratch/` are **finer-grained** work units that decompose a single
Tasks.md bullet — they do not replace it. When a `.scratch/` issue is
finished, update the corresponding `Tasks.md` checkbox in the same
commit so the two stay aligned.

## When a skill says "publish to the issue tracker"

Create a new file under `.scratch/<feature-slug>/` (creating the
directory if needed). Add a one-line back-reference to the originating
`Tasks.md` / `AUTOMATION_ROADMAP.md` bullet so the audit trail is
complete in both directions.

## When a skill says "fetch the relevant ticket"

Read the file at the referenced path. The user will normally pass the
path or the issue number directly.
