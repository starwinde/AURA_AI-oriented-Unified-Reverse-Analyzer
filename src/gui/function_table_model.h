// src/gui/function_table_model.h — Phase 11.3 Slice F (ADR-0035).
//
// QAbstractItemModel for the function browser (Page 1).
// Cutter-style tree: top-level rows are functions; child rows show metadata.
// Backed by QVector<GuiFunctionRecord> populated by MainWindow::runAnalyze.

#pragma once

#include <QAbstractItemModel>
#include <QVector>

#include "main_window.h"  // GuiFunctionRecord

namespace aura::gui {

class FunctionTableModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum MetaRow {
        MetaOffset = 0,
        MetaSize,
        MetaImport,
        MetaNargs,
        MetaNblocks,
        MetaNlocals,
        MetaCallType,
        MetaStackFrame,
        MetaComment,
        MetaCount,
    };

    explicit FunctionTableModel(QObject* parent = nullptr);

    void setFunctions(const QVector<GuiFunctionRecord>& funcs);
    bool isFunctionIndex(const QModelIndex& index) const;
    int functionRowForIndex(const QModelIndex& index) const;
    QModelIndex functionIndex(int functionRow) const;

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
    QVector<GuiFunctionRecord> m_rows;
};

}  // namespace aura::gui
