// src/gui/symbol_table_model.cpp — implementation.

#include "symbol_table_model.h"

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

SymbolTableModel::SymbolTableModel(QObject* parent)
    : QAbstractItemModel(parent) {}

void SymbolTableModel::setImportOnly(bool importOnly) {
    if (m_importOnly == importOnly) return;
    beginResetModel();
    m_importOnly = importOnly;
    m_rows.clear();
    endResetModel();
}

void SymbolTableModel::setSymbols(const QVector<GuiSymbolRecord>& syms) {
    beginResetModel();
    m_rows.clear();
    m_rows.reserve(syms.size());
    for (const auto& s : syms) {
        if (!m_importOnly || s.kind == QStringLiteral("import"))
            m_rows.push_back(s);
    }
    endResetModel();
}

int SymbolTableModel::rowCount(const QModelIndex& parent) const {
    if (!parent.isValid()) return m_rows.size();
    if (parent.internalId() == 0 && parent.column() == 0) return MetaCount;
    return 0;
}

int SymbolTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

QModelIndex SymbolTableModel::index(int row, int column,
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

QModelIndex SymbolTableModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || index.internalId() == 0) return {};
    const int row = static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    return createIndex(row, 0, quintptr(0));
}

QVariant SymbolTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    const int row = index.internalId() == 0
        ? index.row()
        : static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    const GuiSymbolRecord& r = m_rows[row];

    if (role == Qt::FontRole && index.internalId() == 0) {
        QFont f;
        f.setBold(true);
        return f;
    }
    if (role == Qt::ForegroundRole && index.internalId() != 0)
        return QBrush(QColor(220, 220, 220));
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole) return {};

    if (index.internalId() == 0) {
        const QString name = r.name.isEmpty()
            ? QStringLiteral("(unnamed)")
            : r.name;
        return name;
    }

    switch (index.row()) {
        case MetaAddr:
            return useKoreanUi()
                ? QStringLiteral("주소: 0x%1").arg(r.addr, 0, 16)
                : QStringLiteral("Addr: 0x%1").arg(r.addr, 0, 16);
        case MetaKind:
            return useKoreanUi()
                ? QStringLiteral("종류: %1").arg(r.kind)
                : QStringLiteral("Kind: %1").arg(r.kind);
        case MetaSource:
            return useKoreanUi()
                ? QStringLiteral("출처: %1").arg(r.source)
                : QStringLiteral("Source: %1").arg(r.source);
        default:
            return {};
    }
}

QVariant SymbolTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return section + 1;
    if (section == 0)
        return useKoreanUi() ? QStringLiteral("이름") : QStringLiteral("Name");
    return {};
}

}  // namespace aura::gui
