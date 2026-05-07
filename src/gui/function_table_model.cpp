// src/gui/function_table_model.cpp — implementation.

#include "function_table_model.h"

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

FunctionTableModel::FunctionTableModel(QObject* parent)
    : QAbstractItemModel(parent) {}

void FunctionTableModel::setFunctions(const QVector<GuiFunctionRecord>& funcs) {
    beginResetModel();
    m_rows = funcs;
    endResetModel();
}

int FunctionTableModel::rowCount(const QModelIndex& parent) const {
    if (!parent.isValid())
        return m_rows.size();
    if (parent.internalId() == 0 && parent.column() == 0)
        return MetaCount;
    return 0;
}

int FunctionTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

QModelIndex FunctionTableModel::index(int row, int column,
                                      const QModelIndex& parent) const {
    if (column != 0 || row < 0) return {};
    if (!parent.isValid()) {
        if (row >= m_rows.size()) return {};
        return createIndex(row, column, quintptr(0));
    }
    if (parent.internalId() == 0 && parent.column() == 0 &&
        row < MetaCount) {
        return createIndex(row, column,
                           static_cast<quintptr>(parent.row() + 1));
    }
    return {};
}

QModelIndex FunctionTableModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || index.internalId() == 0)
        return {};
    const int functionRow = static_cast<int>(index.internalId()) - 1;
    if (functionRow < 0 || functionRow >= m_rows.size())
        return {};
    return createIndex(functionRow, 0, quintptr(0));
}

bool FunctionTableModel::isFunctionIndex(const QModelIndex& index) const {
    return index.isValid() && index.internalId() == 0 &&
           index.row() >= 0 && index.row() < m_rows.size();
}

int FunctionTableModel::functionRowForIndex(const QModelIndex& index) const {
    if (!index.isValid()) return -1;
    if (index.internalId() == 0)
        return index.row();
    return static_cast<int>(index.internalId()) - 1;
}

QModelIndex FunctionTableModel::functionIndex(int functionRow) const {
    if (functionRow < 0 || functionRow >= m_rows.size()) return {};
    return index(functionRow, 0, {});
}

QVariant FunctionTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    const int functionRow = functionRowForIndex(index);
    if (functionRow < 0 || functionRow >= m_rows.size()) return {};
    const GuiFunctionRecord& r = m_rows[functionRow];

    if (role == Qt::FontRole && index.internalId() == 0) {
        QFont f;
        f.setBold(true);
        return f;
    }
    if (role == Qt::ForegroundRole && index.internalId() != 0) {
        return QBrush(QColor(220, 220, 220));
    }
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole) return {};

    if (index.internalId() == 0) {
        const QString name = r.name.isEmpty()
            ? QStringLiteral("(unnamed)")
            : r.name;
        if (role == Qt::ToolTipRole) {
            return QStringLiteral("%1\n0x%2")
                .arg(name)
                .arg(r.entry, 0, 16);
        }
        return name;
    }

    const int meta = index.row();
    const bool isImport = r.name.startsWith(QStringLiteral("sym.imp.")) ||
                          r.name.startsWith(QStringLiteral("imp."));
    switch (meta) {
        case MetaOffset:
            return useKoreanUi()
                ? QStringLiteral("오프셋: 0x%1").arg(r.entry, 0, 16)
                : QStringLiteral("Offset: 0x%1").arg(r.entry, 0, 16);
        case MetaSize:
            return useKoreanUi()
                ? QStringLiteral("크기: 0x%1").arg(r.size, 0, 16)
                : QStringLiteral("Size: 0x%1").arg(r.size, 0, 16);
        case MetaImport:
            return useKoreanUi()
                ? QStringLiteral("가져오기: %1").arg(isImport ? QStringLiteral("true") : QStringLiteral("false"))
                : QStringLiteral("Import: %1").arg(isImport ? QStringLiteral("true") : QStringLiteral("false"));
        case MetaNargs:
            return QStringLiteral("Nargs: -");
        case MetaNblocks:
            return QStringLiteral("Nbbs: -");
        case MetaNlocals:
            return QStringLiteral("Nlocals: -");
        case MetaCallType:
            return QStringLiteral("Call type: -");
        case MetaStackFrame:
            return QStringLiteral("StackFrame: -");
        case MetaComment:
            return useKoreanUi()
                ? QStringLiteral("주석:")
                : QStringLiteral("Comment:");
        default:
            return {};
    }
}

QVariant FunctionTableModel::headerData(int section, Qt::Orientation orientation,
                                        int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return section + 1;
    if (section == 0)
        return useKoreanUi() ? QStringLiteral("이름") : QStringLiteral("Name");
    return {};
}

}  // namespace aura::gui
