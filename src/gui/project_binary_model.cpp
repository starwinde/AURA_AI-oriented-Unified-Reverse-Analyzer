// src/gui/project_binary_model.cpp — implementation.

#include "project_binary_model.h"

#include <QDateTime>
#include <QSettings>

namespace aura::gui {

namespace {

constexpr int kListCapacity = 4096;  // v1 soft ceiling

QString formatSize(qint64 bytes) {
    if (bytes < 1024)
        return QStringLiteral("%1 B").arg(bytes);
    if (bytes < 1024LL * 1024)
        return QStringLiteral("%1 KB").arg(bytes / 1024);
    if (bytes < 1024LL * 1024 * 1024)
        return QStringLiteral("%1 MB").arg(bytes / (1024LL * 1024));
    return QStringLiteral("%1 GB").arg(bytes / (1024LL * 1024 * 1024));
}

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

QString formatLastAnalyzed(qint64 unix_seconds) {
    if (unix_seconds <= 0)
        return useKoreanUi() ? QStringLiteral("(없음)") : QStringLiteral("(never)");
    return QDateTime::fromSecsSinceEpoch(unix_seconds)
        .toString(QStringLiteral("yyyy-MM-dd HH:mm"));
}

}  // namespace

ProjectBinaryModel::ProjectBinaryModel(QObject* parent)
    : QAbstractTableModel(parent) {}

void ProjectBinaryModel::setRegistry(AuraProjectBinaries* pb) {
    beginResetModel();
    m_pb = pb;
    m_rows.clear();
    endResetModel();
    if (m_pb) reload();
}

void ProjectBinaryModel::reload() {
    beginResetModel();
    m_rows.clear();
    if (m_pb) {
        QVector<AuraProjectBinaryRecord> buf(kListCapacity);
        int n = aura_project_binaries_list(m_pb, buf.data(), kListCapacity);
        if (n > 0) {
            buf.resize(n);
            m_rows = std::move(buf);
        }
    }
    endResetModel();
}

const AuraProjectBinaryRecord* ProjectBinaryModel::recordAt(int row) const {
    if (row < 0 || row >= m_rows.size()) return nullptr;
    return &m_rows[row];
}

int ProjectBinaryModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return m_rows.size();
}

int ProjectBinaryModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant ProjectBinaryModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole) return {};

    const int row = index.row();
    if (row < 0 || row >= m_rows.size()) return {};
    const AuraProjectBinaryRecord& r = m_rows[row];

    switch (index.column()) {
        case ColPath:
            return QString::fromUtf8(r.path);
        case ColFingerprint: {
            const QString hex = QString::fromUtf8(r.fingerprint);
            if (role == Qt::ToolTipRole) return hex;  // full
            return hex.left(8);                       // display short
        }
        case ColSize:
            return formatSize(static_cast<qint64>(r.size));
        case ColLastAnalyzed:
            return formatLastAnalyzed(static_cast<qint64>(r.last_analyzed_at));
        default:
            return {};
    }
}

QVariant ProjectBinaryModel::headerData(int section, Qt::Orientation orientation,
                                        int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return section + 1;

    switch (section) {
        case ColPath:         return useKoreanUi() ? QStringLiteral("경로") : QStringLiteral("Path");
        case ColFingerprint:  return QStringLiteral("SHA-256");
        case ColSize:         return useKoreanUi() ? QStringLiteral("크기") : QStringLiteral("Size");
        case ColLastAnalyzed: return useKoreanUi() ? QStringLiteral("마지막 분석") : QStringLiteral("Last Analyzed");
        default:              return {};
    }
}

}  // namespace aura::gui
