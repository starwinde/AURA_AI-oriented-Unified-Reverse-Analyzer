// src/gui/xref_table_model.cpp — implementation.

#include "xref_table_model.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QSettings>

namespace aura::gui {

namespace {

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

}  // namespace

XrefTableModel::XrefTableModel(QObject* parent)
    : QAbstractItemModel(parent) {}

void XrefTableModel::setXrefs(const QVector<GuiXrefRecord>& xrefs) {
    beginResetModel();
    m_rows = xrefs;
    endResetModel();
}

int XrefTableModel::rowCount(const QModelIndex& parent) const {
    if (!parent.isValid()) return m_rows.size();
    if (parent.internalId() == 0 && parent.column() == 0) return MetaCount;
    return 0;
}

int XrefTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

QModelIndex XrefTableModel::index(int row, int column,
                                  const QModelIndex& parent) const {
    if (column != 0 || row < 0) return {};
    if (!parent.isValid()) {
        if (row >= m_rows.size()) return {};
        return createIndex(row, column, quintptr(0));
    }
    if (parent.internalId() == 0 && row < MetaCount)
        return createIndex(row, column,
                           static_cast<quintptr>(parent.row() + 1));
    return {};
}

QModelIndex XrefTableModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || index.internalId() == 0) return {};
    const int row = static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    return createIndex(row, 0, quintptr(0));
}

QVariant XrefTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    const int row = index.internalId() == 0
        ? index.row()
        : static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    const GuiXrefRecord& r = m_rows[row];
    if (role == Qt::FontRole && index.internalId() == 0) {
        QFont f;
        f.setBold(true);
        return f;
    }
    if (role == Qt::ForegroundRole && index.internalId() != 0)
        return QBrush(QColor(220, 220, 220));
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole) return {};

    if (index.internalId() == 0) {
        return QStringLiteral("0x%1 -> 0x%2")
            .arg(r.from, 0, 16)
            .arg(r.to, 0, 16);
    }
    switch (index.row()) {
        case MetaFrom:
            return useKoreanUi()
                ? QStringLiteral("참조 위치: 0x%1").arg(r.from, 0, 16)
                : QStringLiteral("From: 0x%1").arg(r.from, 0, 16);
        case MetaTo:
            return useKoreanUi()
                ? QStringLiteral("대상: 0x%1").arg(r.to, 0, 16)
                : QStringLiteral("To: 0x%1").arg(r.to, 0, 16);
        case MetaKind:
            return useKoreanUi()
                ? QStringLiteral("종류: %1").arg(r.kind)
                : QStringLiteral("Kind: %1").arg(r.kind);
        case MetaSource:
            return useKoreanUi()
                ? QStringLiteral("출처: %1").arg(r.source)
                : QStringLiteral("Source: %1").arg(r.source);
    }
    return {};
}

QVariant XrefTableModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return section + 1;
    if (section == 0)
        return useKoreanUi() ? QStringLiteral("참조") : QStringLiteral("Xref");
    return {};
}

}  // namespace aura::gui
