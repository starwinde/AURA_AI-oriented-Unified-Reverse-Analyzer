// src/gui/disasm_flow_gutter.h — Phase 11.6 T2 C2 (Cutter-style flow
// arrow gutter).
//
// QWidget rendered to the LEFT of a QPlainTextEdit (the disasm
// "Structured" tab's text view). For each GuiFlowArrow with a valid
// in-function destination (dstLine >= 0) and assigned lane (lane >=
// 0), paints the classical 3-segment arrow:
//
//   right-edge  ----+              <- horizontal stub at src line
//                   |
//                   |              <- vertical lane line
//                   |
//   right-edge  <---+              <- horizontal stub + arrowhead at dst
//
// Lane convention: lane 0 = closest to the text (rightmost column in
// the gutter), bigger lane = further away from text. assignFlowArrowLanes
// (T2 C1) gives the shortest arrows the smallest lanes so most jumps
// occupy minimum horizontal real estate.
//
// T2 C2 scope: gutter widget + geometry + paintEvent. All arrows drawn
// in a uniform pen (gray) — per-kind color theming (true=green, false=
// red, uncond=blue, call=gray dotted) lands in T2 C3 along with the
// DisasmPane integration.

#pragma once

#include <QVector>
#include <QWidget>

#include "main_window.h"  // GuiFlowArrow

class QPlainTextEdit;

namespace aura::gui {

class DisasmFlowGutter : public QWidget {
    Q_OBJECT
public:
    explicit DisasmFlowGutter(QPlainTextEdit* textView,
                              QWidget* parent = nullptr);

    void setArrows(const QVector<GuiFlowArrow>& arrows);
    void clearArrows();

    QSize sizeHint() const override;

    // Layout helpers — pure functions, headless-testable.
    //
    // gutterWidthForLanes: pixel width needed for `maxLanes` lanes,
    // each `laneWidth` px wide, plus a `margin` for the arrowhead
    // stub on the right edge.
    static int gutterWidthForLanes(int maxLanes, int laneWidth, int margin);

    // laneToX: pixel x-coordinate of `lane`'s vertical line within a
    // gutter of total width `gutterWidth`. Lane 0 is rightmost (closest
    // to text). Higher lanes step left by `laneWidth` each.
    static int laneToX(int lane, int gutterWidth, int laneWidth);

    // Test seam — exposed so the gui_smoke test can verify the chosen
    // configuration without poking at the protected paintEvent.
    int laneWidthPx() const { return m_laneWidth; }
    int marginPx()    const { return m_margin; }
    int maxLanes()    const { return m_maxLanes; }
    int arrowCount()  const { return m_arrows.size(); }

    // Phase 11.6 T2 C4: read-only access to the live arrow vector so
    // gui_smoke can audit the kinds / lanes assigned for a real
    // fixture function (not just count them).
    const QVector<GuiFlowArrow>& arrows() const { return m_arrows; }

    // Phase 11.6 T3: hit-test — index into m_arrows of the (topmost)
    // arrow whose vertical lane line is within `tolerancePx` of `p`,
    // or -1 if no arrow matches. Public so the test can drive it
    // without synthesising QMouseEvents.
    int arrowIndexAtPos(QPoint p, int tolerancePx = 3) const;

    // Currently-hovered arrow index (or -1). Test seam.
    int hoveredArrowIndex() const { return m_hoverIndex; }

    // Phase 11.6 T3: y-pixel for a 0-based line in the *gutter's*
    // coordinate system — matches arrowIndexAtPos input. Test seam
    // so callers can pick a click point that lines up with the
    // gutter's view of where each instruction sits, rather than
    // recomputing from the text view (which may resolve to a
    // different sibling QPlainTextEdit via findChild traversal).
    int yForLineTest(int line) const { return yForLine(line); }

    // Phase 11.6 T2 C3: per-kind colour mapping. Pure function so the
    // colour palette is testable headless and stays the single source
    // of truth for both paintEvent and any future legend UI.
    //   "uncond"     -> blue   (#3b78b3) solid
    //   "cond_true"  -> green  (#3a8b3a) solid
    //   "cond_false" -> red    (#b35050) solid
    //   "call"       -> gray   (#888888) dotted
    //   anything else -> gray   (#a0a0a0) solid
    static QColor colorForKind(const QString& kind);
    static bool   isDottedKind(const QString& kind);

signals:
    // Phase 11.6 T3: emitted on a left-click that lands on an arrow.
    // DisasmPane wires this to selectInstruction(dstAddr) so clicking
    // a branch's lane line jumps the cursor to its target.
    void arrowClicked(quint64 dstAddr);

protected:
    void paintEvent(QPaintEvent* e)  override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void leaveEvent(QEvent* e) override;

private slots:
    void onScrolled();

private:
    int yForLine(int line) const;

    QPlainTextEdit*       m_textView   = nullptr;
    QVector<GuiFlowArrow> m_arrows;
    int                   m_laneWidth  = 8;
    int                   m_margin     = 6;
    int                   m_maxLanes   = 8;
    int                   m_hoverIndex = -1;  // T3: hovered arrow.
};

}  // namespace aura::gui
