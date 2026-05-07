// src/gui/string_table_model.cpp — implementation.

#include "string_table_model.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QSettings>
#include <QStringList>

namespace aura::gui {

namespace {

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

bool showOriginalStringDetails() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("privacy/showOriginalStringDetails"),
                   false).toBool();
}

int visibleMetaCount() {
    return showOriginalStringDetails()
        ? StringTableModel::MetaCount
        : StringTableModel::MetaCount - 1;
}

int metaForVisibleRow(int row) {
    if (showOriginalStringDetails() || row < StringTableModel::MetaOriginal)
        return row;
    return row + 1;
}

}  // namespace

StringTableModel::StringTableModel(QObject* parent)
    : QAbstractItemModel(parent) {}

void StringTableModel::setStrings(const QVector<GuiStringRecord>& strs) {
    beginResetModel();
    m_rows = strs;
    endResetModel();
}

int StringTableModel::stringRowForIndex(const QModelIndex& index) const {
    if (!index.isValid()) return -1;
    const int row = index.internalId() == 0
        ? index.row()
        : static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return -1;
    return row;
}

int StringTableModel::rowCount(const QModelIndex& parent) const {
    if (!parent.isValid()) return m_rows.size();
    if (parent.internalId() == 0 && parent.column() == 0)
        return visibleMetaCount();
    return 0;
}

int StringTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

QModelIndex StringTableModel::index(int row, int column,
                                    const QModelIndex& parent) const {
    if (column != 0 || row < 0) return {};
    if (!parent.isValid()) {
        if (row >= m_rows.size()) return {};
        return createIndex(row, column, quintptr(0));
    }
    if (parent.internalId() == 0 && row < visibleMetaCount())
        return createIndex(row, column,
                           static_cast<quintptr>(parent.row() + 1));
    return {};
}

QModelIndex StringTableModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || index.internalId() == 0) return {};
    const int row = static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    return createIndex(row, 0, quintptr(0));
}

QVariant StringTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    const int row = index.internalId() == 0
        ? index.row()
        : static_cast<int>(index.internalId()) - 1;
    if (row < 0 || row >= m_rows.size()) return {};
    const GuiStringRecord& r = m_rows[row];
    if (role == Qt::FontRole && index.internalId() == 0) {
        QFont f;
        f.setBold(true);
        return f;
    }
    if (role == Qt::ForegroundRole && index.internalId() != 0)
        return QBrush(QColor(220, 220, 220));
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole) return {};

    if (index.internalId() == 0) {
        const QString base = r.content.isEmpty()
            ? QStringLiteral("0x%1").arg(r.addr, 0, 16)
            : r.content;
        if (role == Qt::DisplayRole) {
            const QString alias =
                r.alias.isEmpty() ? QStringLiteral("-") : r.alias;
            const bool hasEffectiveMask =
                !r.maskedContent.isEmpty() && r.maskedContent != r.content;
            const QString masked =
                hasEffectiveMask ? r.maskedContent : QStringLiteral("-");
            return QStringLiteral("%1 : %2 : %3").arg(base, alias, masked);
        }
        if (r.hasProtection && role == Qt::ToolTipRole)
            return useKoreanUi()
                ? QStringLiteral("원문 기본 표시. 외부 LLM/MCP 전달에는 보호값 사용: %1")
                      .arg(r.protectedValue)
                : QStringLiteral("Original shown by default. External LLM/MCP export uses protected value: %1")
                      .arg(r.protectedValue);
        return base;
    }

    switch (metaForVisibleRow(index.row())) {
        case MetaAddr:
            return useKoreanUi()
                ? QStringLiteral("주소: 0x%1").arg(r.addr, 0, 16)
                : QStringLiteral("Addr: 0x%1").arg(r.addr, 0, 16);
        case MetaLength:
            return useKoreanUi()
                ? QStringLiteral("길이: %1").arg(r.length)
                : QStringLiteral("Length: %1").arg(r.length);
        case MetaEncoding:
            return useKoreanUi()
                ? QStringLiteral("인코딩: %1").arg(r.encoding)
                : QStringLiteral("Encoding: %1").arg(r.encoding);
        case MetaSection:
            return useKoreanUi()
                ? QStringLiteral("섹션: %1").arg(r.section)
                : QStringLiteral("Section: %1").arg(r.section);
        case MetaSource:
            return useKoreanUi()
                ? QStringLiteral("출처: %1").arg(r.source)
                : QStringLiteral("Source: %1").arg(r.source);
        case MetaOriginal:
            return useKoreanUi()
                ? QStringLiteral("기존: %1").arg(r.content)
                : QStringLiteral("Original: %1").arg(r.content);
        case MetaAlias:
            return useKoreanUi()
                ? QStringLiteral("별칭: %1").arg(
                      r.alias.isEmpty() ? QStringLiteral("-") : r.alias)
                : QStringLiteral("Alias: %1").arg(
                      r.alias.isEmpty() ? QStringLiteral("-") : r.alias);
        case MetaMasked:
        {
            const bool hasEffectiveMask =
                !r.maskedContent.isEmpty() && r.maskedContent != r.content;
            return useKoreanUi()
                ? QStringLiteral("마스킹: %1").arg(
                      hasEffectiveMask ? r.maskedContent : QStringLiteral("-"))
                : QStringLiteral("Masked: %1").arg(
                      hasEffectiveMask ? r.maskedContent : QStringLiteral("-"));
        }
        case MetaFindings: {
            if (r.findings.isEmpty()) {
                return useKoreanUi()
                    ? QStringLiteral("탐지 결과: -")
                    : QStringLiteral("Findings: -");
            }
            QStringList parts;
            for (const auto& f : r.findings) {
                parts << QStringLiteral("%1 %2 %3 %4-%5 %6")
                             .arg(f.maskToken, f.detectorId, f.kind)
                             .arg(f.startOffset)
                             .arg(f.endOffset)
                             .arg(f.confidence, 0, 'f', 2);
            }
            return useKoreanUi()
                ? QStringLiteral("탐지 결과: %1  보호 표시값: %2")
                      .arg(parts.join(QStringLiteral("; ")), r.protectedValue)
                : QStringLiteral("Findings: %1  Protected value: %2")
                      .arg(parts.join(QStringLiteral("; ")), r.protectedValue);
        }
    }
    return {};
}

QVariant StringTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return section + 1;
    if (section == 0)
        return useKoreanUi() ? QStringLiteral("내용") : QStringLiteral("Content");
    return {};
}

}  // namespace aura::gui
