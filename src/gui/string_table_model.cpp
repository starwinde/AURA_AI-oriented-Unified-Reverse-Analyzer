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

bool hasEffectiveMask(const GuiStringRecord& r) {
    return !r.maskedContent.isEmpty() && r.maskedContent != r.content;
}

bool findingKindMatches(const GuiStringRecord& r,
                        std::initializer_list<const char*> kinds) {
    for (const auto& finding : r.findings) {
        const QString kind = finding.kind.toLower();
        for (const char* wanted : kinds) {
            if (kind == QString::fromLatin1(wanted)) return true;
        }
    }
    return false;
}

QVector<int> visibleMetaRows(const GuiStringRecord& r) {
    QVector<int> rows;
    rows.reserve(StringTableModel::MetaCount);
    for (int meta = 0; meta < StringTableModel::MetaCount; ++meta) {
        if (meta == StringTableModel::MetaOriginal &&
            !showOriginalStringDetails()) {
            continue;
        }
        if (meta == StringTableModel::MetaAlias && r.alias.isEmpty()) {
            continue;
        }
        rows.push_back(meta);
    }
    return rows;
}

int visibleMetaCount(const GuiStringRecord& r) {
    return visibleMetaRows(r).size();
}

int metaForVisibleRow(const GuiStringRecord& r, int row) {
    const QVector<int> rows = visibleMetaRows(r);
    if (row < 0 || row >= rows.size()) return -1;
    return rows[row];
}

QString starMaskForDisplay(const QString& value) {
    if (value.isEmpty()) return QStringLiteral("*");
    const int len = value.size();
    int maskCount = (len * 65 + 50) / 100;
    maskCount = qBound(1, maskCount, len);
    const int visible = len - maskCount;
    const int prefix = visible / 2 + visible % 2;
    const int suffix = visible / 2;
    return value.left(prefix)
        + QString(maskCount, QLatin1Char('*'))
        + (suffix > 0 ? value.right(suffix) : QString());
}

QString protectedDisplayValue(const GuiStringRecord& r,
                              const QString& original) {
    return hasEffectiveMask(r) ? r.maskedContent : starMaskForDisplay(original);
}

QString displayValueForString(const GuiStringRecord& r) {
    const QString original = r.content.isEmpty()
        ? QStringLiteral("0x%1").arg(r.addr, 0, 16)
        : r.content;
    if (r.displayMode == 1) {
        if (!r.alias.trimmed().isEmpty()) return r.alias;
        if (r.hasProtection) return protectedDisplayValue(r, original);
        return original;
    }
    if (r.displayMode == 2 && r.hasProtection)
        return protectedDisplayValue(r, original);
    if (hasEffectiveMask(r))
        return r.maskedContent;
    if (r.hasProtection)
        return protectedDisplayValue(r, original);
    return original;
}

}  // namespace

StringTableModel::StringTableModel(QObject* parent)
    : QAbstractItemModel(parent) {}

void StringTableModel::setStrings(const QVector<GuiStringRecord>& strs) {
    beginResetModel();
    m_rows = strs;
    rebuildVisibleRows();
    endResetModel();
}

void StringTableModel::setFilter(Filter filter) {
    if (m_filter == filter) return;
    beginResetModel();
    m_filter = filter;
    rebuildVisibleRows();
    endResetModel();
}

int StringTableModel::stringRowForIndex(const QModelIndex& index) const {
    if (!index.isValid()) return -1;
    if (index.internalId() != 0) {
        const int sourceRow = static_cast<int>(index.internalId()) - 1;
        return sourceRow >= 0 && sourceRow < m_rows.size() ? sourceRow : -1;
    }
    if (index.row() < 0 || index.row() >= m_visibleRows.size()) return -1;
    return m_visibleRows[index.row()];
}

int StringTableModel::rowCount(const QModelIndex& parent) const {
    if (!parent.isValid()) return m_visibleRows.size();
    if (parent.internalId() == 0 && parent.column() == 0) {
        const int sourceRow = stringRowForIndex(parent);
        if (sourceRow < 0) return 0;
        return visibleMetaCount(m_rows[sourceRow]);
    }
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
        if (row >= m_visibleRows.size()) return {};
        return createIndex(row, column, quintptr(0));
    }
    if (parent.internalId() == 0) {
        const int sourceRow = stringRowForIndex(parent);
        if (sourceRow < 0) return {};
        if (row >= visibleMetaCount(m_rows[sourceRow])) return {};
        return createIndex(row, column,
                           static_cast<quintptr>(sourceRow + 1));
    }
    return {};
}

QModelIndex StringTableModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || index.internalId() == 0) return {};
    const int sourceRow = static_cast<int>(index.internalId()) - 1;
    if (sourceRow < 0 || sourceRow >= m_rows.size()) return {};
    const int visibleRow = m_visibleRows.indexOf(sourceRow);
    if (visibleRow < 0) return {};
    return createIndex(visibleRow, 0, quintptr(0));
}

QVariant StringTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    const int row = stringRowForIndex(index);
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
        if (role == Qt::DisplayRole) {
            return displayValueForString(r);
        }
        if (r.hasProtection && role == Qt::ToolTipRole)
            return useKoreanUi()
                ? QStringLiteral("기본 표시값은 보호값입니다. 외부 LLM/MCP 전달에도 보호값 사용: %1")
                      .arg(r.protectedValue)
                : QStringLiteral("Protected value shown by default. External LLM/MCP export uses protected value: %1")
                      .arg(r.protectedValue);
        return displayValueForString(r);
    }

    switch (metaForVisibleRow(r, index.row())) {
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
                ? QStringLiteral("인코딩: %1 (%2)").arg(
                      r.encoding).arg(r.encodingConfidence, 0, 'f', 2)
                : QStringLiteral("Encoding: %1 (%2)").arg(
                      r.encoding).arg(r.encodingConfidence, 0, 'f', 2);
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
                ? QStringLiteral("별칭: %1").arg(r.alias)
                : QStringLiteral("Alias: %1").arg(r.alias);
        case MetaMasked:
        {
            return useKoreanUi()
                ? QStringLiteral("마스킹: %1").arg(
                      hasEffectiveMask(r) ? r.maskedContent : QStringLiteral("-"))
                : QStringLiteral("Masked: %1").arg(
                      hasEffectiveMask(r) ? r.maskedContent : QStringLiteral("-"));
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

bool StringTableModel::acceptsRow(const GuiStringRecord& row) const {
    switch (m_filter) {
        case Filter::Protected:
            return row.hasProtection;
        case Filter::Unprotected:
            return !row.hasProtection;
        case Filter::Alias:
            return !row.alias.trimmed().isEmpty();
        case Filter::Masked:
            return hasEffectiveMask(row);
        case Filter::Email:
            return findingKindMatches(row, {"email"});
        case Filter::KoreanRrn:
            return findingKindMatches(row, {"kr_rrn", "rrn", "korean_rrn"});
        case Filter::Phone:
            return findingKindMatches(row, {"phone", "telephone", "phone_number"});
        case Filter::Url:
            return findingKindMatches(row, {"url", "uri"});
        case Filter::SecretToken:
            return findingKindMatches(row, {"secret", "token", "api_key", "password"});
        case Filter::OtherFinding:
            return row.hasProtection &&
                   !findingKindMatches(row, {"email", "kr_rrn", "rrn",
                                             "korean_rrn", "phone",
                                             "telephone", "phone_number", "url", "uri",
                                             "secret", "token", "api_key",
                                             "password"});
        case Filter::All:
        default:
            return true;
    }
}

void StringTableModel::rebuildVisibleRows() {
    m_visibleRows.clear();
    for (int i = 0; i < m_rows.size(); ++i) {
        if (acceptsRow(m_rows[i])) m_visibleRows.push_back(i);
    }
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
