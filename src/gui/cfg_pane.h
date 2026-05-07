// src/gui/cfg_pane.h — Phase 11.3.8 (P2.F3 C2, ADR-0041).
//
// Control Flow Graph view (skeleton in C2). C3 will add BasicBlockNode +
// EdgeArrow + BFS layout; C4 will add pan/zoom + double-click jump.

#pragma once

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsView>
#include <QHash>
#include <QVector>

#include "main_window.h"  // GuiBlockRecord / GuiEdgeRecord

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;

namespace aura::gui {

/* Phase 11.3.8 (P2.F3 C3): one node per basic block. Stores its
 * stable id + start address so double-click can resolve to a
 * DisasmPane jump (wired in C4). */
class BasicBlockNode : public QGraphicsRectItem {
public:
    BasicBlockNode(quint32 blockId, quint64 startAddr, quint64 endAddr,
                   QGraphicsItem* parent = nullptr);
    quint32 blockId()   const { return m_blockId; }
    quint64 startAddr() const { return m_startAddr; }
private:
    quint32 m_blockId;
    quint64 m_startAddr;
    quint64 m_endAddr;
};

/* Edge arrow with EdgeKind color (per ADR-0041 D5). */
class EdgeArrow : public QGraphicsPathItem {
public:
    EdgeArrow(const QPointF& srcCenter, const QPointF& dstCenter,
              const QString& kind, QGraphicsItem* parent = nullptr);
};

class CfgPane : public QGraphicsView {
    Q_OBJECT
public:
    explicit CfgPane(QWidget* parent = nullptr);

    // Replace the displayed CFG. C2 stub: clears the scene and stores
    // the records; visual nodes/edges land in C3.
    void showCfg(quint64 funcAddr,
                 const QVector<GuiBlockRecord>& blocks,
                 const QVector<GuiEdgeRecord>&  edges);

    // Cache control.
    bool hasCached(quint64 funcAddr) const;
    QVector<GuiBlockRecord> cachedBlocks(quint64 funcAddr) const;
    QVector<GuiEdgeRecord>  cachedEdges (quint64 funcAddr) const;
    void cache(quint64 funcAddr,
               const QVector<GuiBlockRecord>& blocks,
               const QVector<GuiEdgeRecord>&  edges);
    void clearCache();

    // Test hooks.
    int  sceneItemCount() const;
    int  currentBlockCount() const;
    int  currentEdgeCount() const;

    // Phase 11.3.7 (P2.F3 C4): test hook — invoke as if the user
    // double-clicked a basic block; emits blockActivated(addr).
    bool activateBlockAt(int index);

signals:
    /* Phase 11.3.8 (P2.F3 C4): emitted on double-click of a
     * BasicBlockNode. Wired in main_window to
     * DisasmPane::selectInstruction(addr). */
    void blockActivated(quint64 addr);

protected:
    void wheelEvent(class QWheelEvent* event) override;
    void mouseDoubleClickEvent(class QMouseEvent* event) override;

private:
    QGraphicsScene* m_scene = nullptr;

    struct Entry {
        QVector<GuiBlockRecord> blocks;
        QVector<GuiEdgeRecord>  edges;
    };
    QHash<quint64, Entry> m_cache;
    int m_currentBlockCount = 0;
    int m_currentEdgeCount  = 0;
};

}  // namespace aura::gui
