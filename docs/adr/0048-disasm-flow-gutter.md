# ADR-0048 — Phase 11.6 Disasm flow arrow gutter (Cutter-style)

- **Status**: Accepted (closeout)
- **Date**: 2026-05-04
- **Related**: ADR-0040 (P2.F2 Disassembly view + AuraInstructionRecord),
  ADR-0036 (Cutter-style workspace), ADR-0041 (P2.F3 CFG view).
  Code: [src/gui/disasm_pane.{h,cpp}](src/gui/disasm_pane.cpp),
  [src/gui/disasm_flow_gutter.{h,cpp}](src/gui/disasm_flow_gutter.cpp),
  `MainWindow::computeFlowArrows` / `MainWindow::assignFlowArrowLanes`.

## Context

Phase 11.3.7 (ADR-0040) closed instruction-level disassembly view —
address / hex bytes / mnemonic / op_str columns rendered in a
`QPlainTextEdit`. Cutter / IDA / Ghidra all visualise control flow as
curved or right-angle arrows in a left gutter so the reader can see at a
glance which JMP/JCC/CALL targets stay inside the function and how branches
nest. Phase 11.6 adds that gutter — without growing the engine record set
and without a new RPC channel.

The phase split into three commit groups, each closed in this ADR:

- **T1** (commits `610ed33b`, `22ad2961`, `4abf9164`) — backend body
  carries flow arrows + RPC `disasm_function` returns the rizin
  `pdf` text (with `asm.lines` ASCII arrows) so the **With arrows**
  tab can show rizin's own rendering side-by-side with the structured
  view.
- **T2** (commits `53fa00f7`, `b66ce04a`, `8d71eb12`, `45146cc9`) —
  the structured `DisasmFlowGutter` widget: arrow descriptor, lane
  assignment, paint, scroll sync, per-kind colours, real-binary smoke,
  spans-viewport fix.
- **T3** (commit `8eb6eacd`) — interactivity: hover highlight +
  click-to-navigate.

This ADR is written after the code landed (closeout) so it records what
**is**, not what was being proposed.

### 2026-05-06 amend — Full Disassembly tab

The function-scoped Disassembly pane remains `pdfj/pdf @ function_entry`.
AURA also exposes a separate **Full Disassembly** tab for Cutter-style
continuous VA browsing. The UI does not ask the user for an address window;
the function list drives scroll/highlight into the listing. Internally the
backend returns both `pdj <count>` structured records and a bounded `pD 4096`
text companion so the GUI can expose the same **Structured** / **With arrows**
split as the function-scoped pane. The Full Disassembly **Structured** tab is a
mixed listing derived from `pD`, so `invalid`, data labels, comments, and
label-only lines are preserved instead of being dropped by instruction-only
records. On Rizin 0.8.0, `pD` can timeout even on
small PE samples when the byte range is too large, so the arrow text companion
is hard-capped at 4KB. This is an intentionally temporary browsing model:
chunk cache and lazy paging are not part of this local patch and remain future
work before claiming Cutter-class scroll efficiency.

## Decisions

### D1 — Data path: existing `pdfj` fields, no new record

`MainWindow::computeFlowArrows(const QVector<GuiInstructionRecord>&)`
derives `GuiFlowArrow` purely from fields that `GuiInstructionRecord`
already carries (set in Phase 11.3.7): `type` (rizin `pdj.type` —
`"jmp"` / `"cjmp"` / `"call"` / …), `jump`, `fail`. Resolution of
`dstLine` is an in-vector lookup against the same instruction list.

**No new 1급 record / no new RPC method.** `AuraInstructionRecord` already
exposes `jump` and `fail`; everything else is GUI-side derivation
restricted to lookup + arithmetic. R-9 ("derived analysis emit X") is not
crossed because no new analytic concept (CFG edge, type fact, call edge)
is invented — the gutter only re-projects what the engine already said.

The "With arrows" tab is fed by an unrelated path: RPC
`disasm_function` returns the rizin `pdf` text directly so the user can
toggle to rizin's native rendering. No structured parsing on AURA's side.

### D2 — Lane assignment: shortest arrows get the smallest lane

`MainWindow::assignFlowArrowLanes(arrows, maxLanes=8)` sorts arrows by
`|dstLine - srcLine|` ascending and assigns the smallest free lane that
does not overlap an already-placed arrow's `[srcLine, dstLine]` range.
Arrows that exceed `maxLanes` get `lane = -1` and are not painted in the
gutter. Calls (out-of-function destination) get `lane = -1` as well —
their stub is implicit at the right edge.

**Lane 0 = rightmost column in the gutter (closest to text); bigger
lane = further left.** `DisasmFlowGutter::laneToX` returns
`gutterWidth - (lane+1) * laneWidth`. (`main_window.h:163` comment says
"leftmost" — that is a stale wording; the code and the gutter
implementation are the source of truth.)

### D3 — Widget layered, not embedded

`DisasmFlowGutter` is a sibling `QWidget` placed to the **left** of the
`QPlainTextEdit` inside a horizontal layout (`disasm_pane.cpp:43`).
It is **not** painted into the text view's viewport — no
`QAbstractTextDocumentLayout` hook, no margin manipulation, no extra
text-block formats. The gutter listens to the text view's
`verticalScrollBar()::valueChanged` and to `textChanged`, then calls
`update()` so its own `paintEvent` reads the freshest line geometry via
`QPlainTextEdit::cursorRect()`.

**Why layered, not embedded**: the doc-layout cost of painting per-block
formats (Qt's `QTextBlockFormat`) at every scroll is non-trivial. A
sibling widget reading `cursorRect()` (already cached by Qt's layout)
adds zero work to the text view itself.

### D4 — Hit-test: lane line + both stubs, reverse order

`DisasmFlowGutter::arrowIndexAtPos(QPoint, tolerancePx = 3)`:

- Iterates `m_arrows` in **reverse** so the topmost-painted arrow wins
  on overlap.
- Skips arrows with `lane < 0`, `srcLine < 0`, or `dstLine < 0`.
- Hits if the cursor is within `tolerancePx` of either: the vertical
  lane line between `[yLo, yHi]`, the source-side horizontal stub at
  `srcY`, or the destination-side horizontal stub at `dstY`.
- Left-click → `arrowClicked(quint64 dstAddr)` → wired in
  `disasm_pane.cpp:78` to `DisasmPane::selectInstruction(addr)`,
  which also emits `instructionSelected` so DecompilePane / CFG /
  Hex stay in sync **without any extra wiring** (Phase 11.3.9 's
  cross-pane mediator is reused).

Cursor changes to `PointingHandCursor` when over an arrow,
`ArrowCursor` otherwise. Hovered arrow paints with `width=2` (rest
stay `width=1`) — only visual; no doc relayout.

### D5 — Per-kind colours hardcoded in widget

`DisasmFlowGutter::colorForKind` and `isDottedKind` are static functions
returning fixed colours: `uncond → #3b78b3` (blue solid),
`cond_true → #3a8b3a` (green solid), `cond_false → #b35050` (red solid),
`call → #888888` (gray dotted), fallback `#a0a0a0` (gray solid). No
theme system. **Reason**: theming the GUI is a separate cross-cutting
concern; the gutter's palette stays the single source of truth so a
future legend UI / theme system has one place to read from.

### D6 — Test seam: `yForLineTest`

T3 added `int yForLineTest(int line) const` (delegates to the private
`yForLine`) so `gui_smoke` can compute click points in the gutter's own
coordinate system. The motivating bug: `pane.findChild<QPlainTextEdit*>()`
could return either the **Structured** tab's text view or the
**With arrows** tab's, depending on Qt's child-traversal order — the
first iteration of the click test landed on the wrong arrow because the
test was reading line-Y from the wrong sibling. Exposing `yForLineTest`
makes the test independent of `findChild`'s ordering.

## Consequences

- `AuraInstructionRecord` schema unchanged. `GuiInstructionRecord`
  unchanged. `DisasmBody` is the only carrier — and only the GUI-side
  derived `GuiFlowArrow` vector is added there (additive). RPC
  consumers see the same disasm payload as Phase 11.3.7.
- **R-9 violation: 0** — no new analysis concept emitted. Lane
  assignment, hit-test, kind-string mapping are all rendering helpers
  that map existing `pdj` fields to pixels.
- **R-12 (single-source-of-truth) impact: 0** — flow arrows are
  derived on demand inside the GUI process, never stored in any
  `AuraEngineResponse` or override layer.
- Cross-pane sync uses the existing `instructionSelected` signal — no
  new mediator hop, no new contract.
- Test surface: `gui_smoke` gains the SUBCASE
  `"hit-test + click jumps cursor"` (T3). At land-time:
  ctest -L integration **3/3 GREEN** (orchestrator_smoke + cli_smoke
  + gui_smoke). Local re-verify with `AURA_BUILD_GUI=OFF`:
  orchestrator_smoke + cli_smoke **2/2 GREEN**; gui_smoke unbuilt
  locally (Qt6 opt-in flag still off — same posture as the rest of
  Phase 11.3.x).

## Out-of-scope (deferred)

- **Theming / per-kind colour configurability** — see D5 reason.
- **`main_window.h:163` comment fix** ("leftmost" → "rightmost,
  nearest-text"). Cosmetic; tracked here so the next pass at that
  file picks it up.
- **Curved arrows** — current rendering is right-angle only; curved
  Bézier paths for long jumps land in a future polish phase if the
  user signals demand.
- **Gutter legend UI** — colour / kind mapping is documented here and
  in `disasm_flow_gutter.cpp:67`; a visible legend (popover / status
  bar) is deferred.
