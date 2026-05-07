// src/gui/symbol_table_model.h — Phase 11.3.5.
//
// QAbstractItemModel for the Symbols/Imports dock (Page 1).
// Cutter-style tree: top-level rows are symbols; child rows show fields.

#pragma once

#include <QAbstractItemModel>
#include <QVector>

#include "main_window.h"  // GuiSymbolRecord

namespace aura::gui {

class SymbolTableModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum MetaRow {
        MetaAddr = 0,
        MetaKind,
        MetaSource,
        MetaCount,
    };

    explicit SymbolTableModel(QObject* parent = nullptr);

    void setImportOnly(bool importOnly);
    void setSymbols(const QVector<GuiSymbolRecord>& syms);

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
    QVector<GuiSymbolRecord> m_rows;
    bool m_importOnly = false;
};

}  // namespace aura::gui
