// src/gui/cfg_pane.cpp — Phase 11.3.8 (P2.F3 C3): real graph rendering.
//
// BasicBlockNode + EdgeArrow + BFS topological layout (Sugiyama
// simplification per ADR-0041 D4). Color map per ADR-0041 D5.
//
// R-9 guard: layout is GUI presentation, not analysis. Graph topology
// originates from EdgeRecord (Phase 2A); this file only assigns
// (x, y) coordinates.

#include "cfg_pane.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QQueue>
#include <QWheelEvent>

namespace aura::gui {

// ── BasicBlockNode ────────────────────────────────────────────────────────

namespace {
constexpr qreal kBlockWidth   = 220.0;
constexpr qreal kBlockHeight  = 56.0;
constexpr qreal kHorizSpacing = 240.0;
constexpr qreal kVertSpacing  = 100.0;
}  // namespace

BasicBlockNode::BasicBlockNode(quint32 blockId, quint64 startAddr,
                               quint64 endAddr, QGraphicsItem* parent)
    : QGraphicsRectItem(0.0, 0.0, kBlockWidth, kBlockHeight, parent),
      m_blockId(blockId),
      m_startAddr(startAddr),
      m_endAddr(endAddr) {
    setBrush(QBrush(QColor(40, 44, 52)));
    setPen(QPen(QColor(170, 170, 170), 1.5));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setData(0, QVariant(static_cast<qulonglong>(startAddr)));

    auto* label = new QGraphicsTextItem(this);
    label->setDefaultTextColor(QColor(220, 220, 220));
    QFont f("Consolas");
    f.setPointSize(9);
    label->setFont(f);
    label->setPlainText(
        QStringLiteral("0x%1\nblock #%2\n[%3 bytes]")
            .arg(startAddr, 0, 16)
            .arg(blockId)
            .arg(endAddr > startAddr ? (endAddr - startAddr) : 0));
    label->setPos(8.0, 4.0);
}

// ── EdgeArrow ─────────────────────────────────────────────────────────────

static QColor edgeColor(const QString& kind) {
    if (kind == QStringLiteral("branch_true"))  return QColor( 76, 175,  80);
    if (kind == QStringLiteral("branch_false")) return QColor(244,  67,  54);
    if (kind == QStringLiteral("call"))         return QColor( 33, 150, 243);
    if (kind == QStringLiteral("fallthrough"))  return QColor(150, 150, 150);
    if (kind == QStringLiteral("jump"))         return QColor(120, 120, 120);
    if (kind == QStringLiteral("return"))       return QColor(156,  39, 176);
    return QColor(120, 120, 120);  // unknown
}

EdgeArrow::EdgeArrow(const QPointF& srcCenter, const QPointF& dstCenter,
                     const QString& kind, QGraphicsItem* parent)
    : QGraphicsPathItem(parent) {
    QPen pen(edgeColor(kind), 2.0);
    setPen(pen);
    setBrush(Qt::NoBrush);

    QPainterPath path;
    path.moveTo(srcCenter);
    path.lineTo(dstCenter);

    // Tiny arrowhead at the destination — two short segments.
    QPointF v = dstCenter - srcCenter;
    qreal len = std::hypot(v.x(), v.y());
    if (len > 1.0) {
        QPointF unit(v.x() / len, v.y() / len);
        QPointF tip = dstCenter;
        QPointF base = tip - unit * 10.0;
        QPointF perp(-unit.y(), unit.x());
        path.moveTo(tip);
        path.lineTo(base + perp * 5.0);
        path.moveTo(tip);
        path.lineTo(base - perp * 5.0);
    }
    setPath(path);
}

// ── CfgPane ───────────────────────────────────────────────────────────────

CfgPane::CfgPane(QWidget* parent) : QGraphicsView(parent) {
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setBackgroundBrush(QBrush(QColor(28, 30, 34)));

    // Phase 11.3.8 (P2.F3 C4): pan = drag-on-empty-space (ADR-0041 D5).
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    auto* placeholder = m_scene->addText(
        QStringLiteral("(no function selected — double-click a function to view CFG)"));
    placeholder->setDefaultTextColor(Qt::gray);
}

void CfgPane::wheelEvent(QWheelEvent* event) {
    // Phase 11.3.8 (P2.F3 C4): Ctrl + wheel zoom (ADR-0041 D5 — Ctrl
    // modifier guards against accidental scroll zoom).
    if (event->modifiers() & Qt::ControlModifier) {
        const qreal step = 1.15;
        if (event->angleDelta().y() > 0) {
            scale(step, step);
        } else {
            scale(1.0 / step, 1.0 / step);
        }
        event->accept();
        return;
    }
    QGraphicsView::wheelEvent(event);
}

void CfgPane::mouseDoubleClickEvent(QMouseEvent* event) {
    // Phase 11.3.8 (P2.F3 C4): double-click on a BasicBlockNode emits
    // blockActivated(startAddr). main_window wires this to
    // DisasmPane::selectInstruction for cross-pane sync.
    QGraphicsItem* it = itemAt(event->pos());
    while (it && !dynamic_cast<BasicBlockNode*>(it)) {
        it = it->parentItem();
    }
    if (auto* node = dynamic_cast<BasicBlockNode*>(it)) {
        emit blockActivated(node->startAddr());
        event->accept();
        return;
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

bool CfgPane::activateBlockAt(int index) {
    // Test hook: walk the scene's BasicBlockNode items in insertion
    // order and emit blockActivated(addr) for the index-th one.
    if (!m_scene) return false;
    int seen = 0;
    const auto items = m_scene->items(Qt::AscendingOrder);
    for (auto* it : items) {
        if (auto* node = dynamic_cast<BasicBlockNode*>(it)) {
            if (seen == index) {
                emit blockActivated(node->startAddr());
                return true;
            }
            ++seen;
        }
    }
    return false;
}

void CfgPane::showCfg(quint64 funcAddr,
                      const QVector<GuiBlockRecord>& blocks,
                      const QVector<GuiEdgeRecord>&  edges) {
    cache(funcAddr, blocks, edges);
    m_scene->clear();
    m_currentBlockCount = blocks.size();
    m_currentEdgeCount  = edges.size();

    if (blocks.isEmpty()) {
        auto* placeholder = m_scene->addText(
            QStringLiteral("CFG @ 0x%1 — no blocks (engine returned 0 — see PE backend backlog)")
                .arg(funcAddr, 0, 16));
        placeholder->setDefaultTextColor(Qt::gray);
        m_scene->setSceneRect(m_scene->itemsBoundingRect());
        return;
    }

    // ── BFS topological layout (ADR-0041 D4 — Sugiyama 단순화) ──
    // 1) Entry block = the one whose startAddr matches funcAddr (or the
    //    block with the smallest startAddr as fallback).
    quint32 entryId = 0;
    for (const auto& b : blocks) {
        if (b.startAddr == funcAddr) { entryId = b.blockId; break; }
    }
    if (entryId == 0) {
        // fallback: lowest startAddr
        const GuiBlockRecord* best = nullptr;
        for (const auto& b : blocks) {
            if (!best || b.startAddr < best->startAddr) best = &b;
        }
        if (best) entryId = best->blockId;
    }

    // 2) BFS depth assignment. Outgoing-edge adjacency map.
    QHash<quint32, QVector<quint32>> adj;
    for (const auto& e : edges) {
        adj[e.srcBlock].push_back(e.dstBlock);
    }
    QHash<quint32, int> depth;
    QQueue<quint32> q;
    if (entryId != 0) { depth[entryId] = 0; q.enqueue(entryId); }
    while (!q.isEmpty()) {
        quint32 cur = q.dequeue();
        const int d = depth.value(cur);
        for (quint32 next : adj.value(cur)) {
            if (!depth.contains(next)) {
                depth[next] = d + 1;
                q.enqueue(next);
            }
        }
    }
    // Unreachable blocks → put them at depth = max+1 (singleton row).
    int maxDepth = 0;
    for (auto it = depth.constBegin(); it != depth.constEnd(); ++it)
        maxDepth = std::max(maxDepth, it.value());
    for (const auto& b : blocks) {
        if (!depth.contains(b.blockId)) depth[b.blockId] = maxDepth + 1;
    }

    // 3) Group by depth; assign x by index within depth (sorted by addr
    //    for deterministic layout).
    QHash<int, QVector<const GuiBlockRecord*>> rows;
    for (const auto& b : blocks) {
        rows[depth.value(b.blockId)].push_back(&b);
    }
    for (auto it = rows.begin(); it != rows.end(); ++it) {
        std::sort(it.value().begin(), it.value().end(),
                  [](const GuiBlockRecord* a, const GuiBlockRecord* b) {
                      return a->startAddr < b->startAddr;
                  });
    }

    // 4) Create nodes at computed coordinates; remember center points
    //    keyed by blockId for the edge pass.
    QHash<quint32, QPointF> centers;
    for (auto it = rows.constBegin(); it != rows.constEnd(); ++it) {
        const int d = it.key();
        const auto& row = it.value();
        const qreal y = d * kVertSpacing;
        const qreal rowWidth = row.size() * kHorizSpacing;
        const qreal xStart = -rowWidth / 2.0;
        for (int i = 0; i < row.size(); ++i) {
            const qreal x = xStart + i * kHorizSpacing;
            const auto* b = row[i];
            auto* node = new BasicBlockNode(b->blockId, b->startAddr,
                                             b->endAddr);
            node->setPos(x, y);
            m_scene->addItem(node);
            centers.insert(b->blockId, QPointF(x + kBlockWidth / 2.0,
                                                y + kBlockHeight / 2.0));
        }
    }

    // 5) Create edges between known centers.
    for (const auto& e : edges) {
        if (!centers.contains(e.srcBlock) || !centers.contains(e.dstBlock))
            continue;
        // Source = bottom-center; destination = top-center for vertical
        // flow. center is rect-center; offset to edges of the rect.
        QPointF srcC = centers.value(e.srcBlock);
        QPointF dstC = centers.value(e.dstBlock);
        QPointF src(srcC.x(), srcC.y() + kBlockHeight / 2.0);
        QPointF dst(dstC.x(), dstC.y() - kBlockHeight / 2.0);
        auto* arrow = new EdgeArrow(src, dst, e.kind);
        m_scene->addItem(arrow);
    }

    m_scene->setSceneRect(m_scene->itemsBoundingRect().adjusted(-40, -40, 40, 40));
    fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

bool CfgPane::hasCached(quint64 funcAddr) const {
    return m_cache.contains(funcAddr);
}

QVector<GuiBlockRecord> CfgPane::cachedBlocks(quint64 funcAddr) const {
    return m_cache.value(funcAddr).blocks;
}

QVector<GuiEdgeRecord> CfgPane::cachedEdges(quint64 funcAddr) const {
    return m_cache.value(funcAddr).edges;
}

void CfgPane::cache(quint64 funcAddr,
                    const QVector<GuiBlockRecord>& blocks,
                    const QVector<GuiEdgeRecord>&  edges) {
    m_cache.insert(funcAddr, Entry{blocks, edges});
}

void CfgPane::clearCache() {
    m_cache.clear();
}

int CfgPane::sceneItemCount() const {
    return m_scene ? m_scene->items().size() : 0;
}

int CfgPane::currentBlockCount() const { return m_currentBlockCount; }
int CfgPane::currentEdgeCount()  const { return m_currentEdgeCount;  }

}  // namespace aura::gui
