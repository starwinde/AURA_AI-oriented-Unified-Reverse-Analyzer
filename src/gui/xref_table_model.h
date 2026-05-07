// src/gui/xref_table_model.h — Phase 11.3.5.
//
// QAbstractItemModel for the Xrefs dock (Page 1).
// Cutter-style tree: top-level rows are xrefs; child rows show fields.
// Backed by QVector<GuiXrefRecord> populated by MainWindow::runAnalyze.

#pragma once

#include <QAbstractItemModel>
#include <QVector>

#include "main_window.h"  // GuiXrefRecord

namespace aura::gui {

class XrefTableModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum MetaRow {
        MetaFrom = 0,
        MetaTo,
        MetaKind,
        MetaSource,
        MetaCount,
    };

    explicit XrefTableModel(QObject* parent = nullptr);

    void setXrefs(const QVector<GuiXrefRecord>& xrefs);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    QVector<GuiXrefRecord> m_rows;
};

}  // namespace aura::gui
