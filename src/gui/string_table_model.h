// src/gui/string_table_model.h — Phase 11.3.6.
//
// QAbstractItemModel for the Strings dock (Page 1).
// Cutter-style tree: top-level rows are strings; child rows show fields.

#pragma once

#include <QAbstractItemModel>
#include <QVector>

#include "main_window.h"  // GuiStringRecord

namespace aura::gui {

class StringTableModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum class Filter {
        All = 0,
        Protected,
        Unprotected,
        Alias,
        Masked,
        Email,
        KoreanRrn,
        Phone,
        Url,
        SecretToken,
        OtherFinding,
    };

    enum MetaRow {
        MetaAddr = 0,
        MetaLength,
        MetaEncoding,
        MetaSection,
        MetaSource,
        MetaOriginal,
        MetaAlias,
        MetaMasked,
        MetaFindings,
        MetaCount,
    };

    explicit StringTableModel(QObject* parent = nullptr);

    void setStrings(const QVector<GuiStringRecord>& strs);
    void setFilter(Filter filter);
    Filter filter() const { return m_filter; }
    int stringRowForIndex(const QModelIndex& index) const;

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
    void rebuildVisibleRows();
    bool acceptsRow(const GuiStringRecord& row) const;

    QVector<GuiStringRecord> m_rows;
    QVector<int> m_visibleRows;
    Filter m_filter = Filter::All;
};

}  // namespace aura::gui
