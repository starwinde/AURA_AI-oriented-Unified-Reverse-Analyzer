// src/gui/disasm_flow_gutter.cpp — implementation.

#include "disasm_flow_gutter.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QPen>
#include <QPlainTextEdit>
#include <QPolygon>
#include <QRect>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>

#include <algorithm>

namespace aura::gui {

DisasmFlowGutter::DisasmFlowGutter(QPlainTextEdit* textView, QWidget* parent)
    : QWidget(parent), m_textView(textView) {
    setFixedWidth(gutterWidthForLanes(m_maxLanes, m_laneWidth, m_margin));
    setAutoFillBackground(true);
    setMouseTracking(true);  // Phase 11.6 T3: receive moves w/o button.
    setCursor(Qt::ArrowCursor);
    if (m_textView) {
        connect(m_textView->verticalScrollBar(), &QScrollBar::valueChanged,
                this, &DisasmFlowGutter::onScrolled);
        connect(m_textView, &QPlainTextEdit::textChanged,
                this, [this]{ update(); });
    }
}

void DisasmFlowGutter::setArrows(const QVector<GuiFlowArrow>& arrows) {
    m_arrows = arrows;
    update();
}

void DisasmFlowGutter::clearArrows() {
    m_arrows.clear();
    update();
}

QSize DisasmFlowGutter::sizeHint() const {
    return QSize(gutterWidthForLanes(m_maxLanes, m_laneWidth, m_margin), 100);
}

int DisasmFlowGutter::gutterWidthForLanes(int maxLanes, int laneWidth,
                                          int margin) {
    if (maxLanes  < 0) maxLanes  = 0;
    if (laneWidth < 1) laneWidth = 1;
    if (margin    < 0) margin    = 0;
    return maxLanes * laneWidth + margin;
}

int DisasmFlowGutter::laneToX(int lane, int gutterWidth, int laneWidth) {
    if (lane < 0)      return -1;
    if (laneWidth < 1) laneWidth = 1;
    // Lane 0 sits one full lane-width in from the right edge so the
    // arrowhead's horizontal stub has room.
    return gutterWidth - (lane + 1) * laneWidth;
}

QColor DisasmFlowGutter::colorForKind(const QString& kind) {
    if (kind == QLatin1String("uncond"))     return QColor(0x3b, 0x78, 0xb3);
    if (kind == QLatin1String("cond_true"))  return QColor(0x3a, 0x8b, 0x3a);
    if (kind == QLatin1String("cond_false")) return QColor(0xb3, 0x50, 0x50);
    if (kind == QLatin1String("call"))       return QColor(0x88, 0x88, 0x88);
    return QColor(0xa0, 0xa0, 0xa0);
}

bool DisasmFlowGutter::isDottedKind(const QString& kind) {
    return kind == QLatin1String("call");
}

int DisasmFlowGutter::arrowIndexAtPos(QPoint p, int tolerancePx) const {
    if (!m_textView || m_arrows.isEmpty()) return -1;
    const int W = width();
    // Walk in reverse so the topmost-painted arrow wins on overlap.
    for (int i = m_arrows.size() - 1; i >= 0; --i) {
        const GuiFlowArrow& a = m_arrows[i];
        if (a.lane < 0)    continue;
        if (a.srcLine < 0) continue;
        if (a.dstLine < 0) continue;

        const int srcY = yForLine(a.srcLine);
        const int dstY = yForLine(a.dstLine);
        if (srcY < 0 || dstY < 0) continue;

        const int laneX = laneToX(a.lane, W, m_laneWidth);
        if (laneX < 0) continue;

        const int yLo = std::min(srcY, dstY);
        const int yHi = std::max(srcY, dstY);

        // Hit on the vertical lane line (most prominent feature).
        if (std::abs(p.x() - laneX) <= tolerancePx &&
            p.y() >= yLo - tolerancePx && p.y() <= yHi + tolerancePx) {
            return i;
        }
        // Hit on the source-side or dst-side horizontal stub.
        if (std::abs(p.y() - srcY) <= tolerancePx &&
            p.x() >= laneX - tolerancePx && p.x() <= W) {
            return i;
        }
        if (std::abs(p.y() - dstY) <= tolerancePx &&
            p.x() >= laneX - tolerancePx && p.x() <= W) {
            return i;
        }
    }
    return -1;
}

void DisasmFlowGutter::mouseMoveEvent(QMouseEvent* e) {
    const int idx = arrowIndexAtPos(e->pos());
    if (idx != m_hoverIndex) {
        m_hoverIndex = idx;
        setCursor(idx >= 0 ? Qt::PointingHandCursor : Qt::ArrowCursor);
        update();
    }
    QWidget::mouseMoveEvent(e);
}

void DisasmFlowGutter::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        const int idx = arrowIndexAtPos(e->pos());
        if (idx >= 0) {
            const quint64 dst = m_arrows[idx].dstAddr;
            emit arrowClicked(dst);
            e->accept();
            return;
        }
    }
    QWidget::mousePressEvent(e);
}

void DisasmFlowGutter::leaveEvent(QEvent* e) {
    if (m_hoverIndex != -1) {
        m_hoverIndex = -1;
        setCursor(Qt::ArrowCursor);
        update();
    }
    QWidget::leaveEvent(e);
}

void DisasmFlowGutter::onScrolled() {
    update();
}

int DisasmFlowGutter::yForLine(int line) const {
    if (!m_textView || line < 0) return -1;
    QTextDocument* doc = m_textView->document();
    if (!doc) return -1;
    QTextBlock block = doc->findBlockByNumber(line);
    if (!block.isValid()) return -1;
    // cursorRect() is the documented public API for line geometry — it
    // returns the rect in *viewport* coordinates (already accounts for
    // scroll position). T2 C3 / DisasmPane will lay the gutter and the
    // text view side-by-side so y-coordinates align directly.
    QTextCursor cur(block);
    QRect r = m_textView->cursorRect(cur);
    return r.top() + r.height() / 2;
}

void DisasmFlowGutter::paintEvent(QPaintEvent* /*e*/) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, false);
    p.fillRect(rect(), palette().color(QPalette::Base));

    if (m_arrows.isEmpty() || !m_textView) return;

    const int W = width();
    const int H = height();

    for (int idx = 0; idx < m_arrows.size(); ++idx) {
        const GuiFlowArrow& a = m_arrows[idx];
        if (a.lane < 0)      continue;  // overflow / call (out-of-func).
        if (a.srcLine < 0)   continue;
        if (a.dstLine < 0)   continue;

        const int srcY = yForLine(a.srcLine);
        const int dstY = yForLine(a.dstLine);
        if (srcY < 0 || dstY < 0) continue;
        // Phase 11.6 T2 C4: skip arrows entirely off-screen on the
        // SAME side of the viewport. Arrows that straddle the visible
        // region (one endpoint above the top, the other below the
        // bottom) must still draw — QPainter clips them naturally and
        // the user sees the vertical lane segment crossing their view.
        if (srcY < 0 && dstY < 0) continue;  // both above viewport.
        if (srcY > H && dstY > H) continue;  // both below viewport.

        const int laneX = laneToX(a.lane, W, m_laneWidth);
        if (laneX < 0) continue;

        // Phase 11.6 T2 C3: per-kind colour + dotted style for "call".
        // Phase 11.6 T3: hovered arrow paints with width=2 to feel
        // clickable; unhovered arrows stay width=1.
        const bool   hovered = (idx == m_hoverIndex);
        const QColor col     = colorForKind(a.kind);
        QPen pen(col);
        pen.setWidth(hovered ? 2 : 1);
        if (isDottedKind(a.kind)) pen.setStyle(Qt::DotLine);
        p.setPen(pen);
        p.setBrush(col);

        // Source-side horizontal stub: from right edge inward to the lane.
        p.drawLine(W - 1, srcY, laneX, srcY);
        // Vertical line down (or up) the lane.
        p.drawLine(laneX, srcY, laneX, dstY);
        // Destination-side horizontal stub.
        p.drawLine(laneX, dstY, W - 3, dstY);

        // Solid arrowhead at the destination — use a solid pen so the
        // triangle outline is filled even when the line itself is
        // dotted (call edges).
        QPen aHeadPen(col);
        aHeadPen.setStyle(Qt::SolidLine);
        p.setPen(aHeadPen);
        QPolygon ah;
        ah << QPoint(W - 1, dstY)
           << QPoint(W - 5, dstY - 3)
           << QPoint(W - 5, dstY + 3);
        p.drawPolygon(ah);
    }
}

}  // namespace aura::gui
