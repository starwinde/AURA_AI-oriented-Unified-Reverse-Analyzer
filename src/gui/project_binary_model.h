// src/gui/project_binary_model.h — QAbstractTableModel for project binary
// list (Phase 11.3 Slice D, ADR-0035).
//
// 4 columns: Path / SHA-256 (앞 8자) / Size / Last Analyzed
//
// Backed by an AuraProjectBinaries handle (opaque, owned by MainWindow).
// reload() pulls a fresh snapshot via aura_project_binaries_list().

#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

extern "C" {
#include "project_binaries.h"
}

namespace aura::gui {

class ProjectBinaryModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Column {
        ColPath         = 0,
        ColFingerprint  = 1,
        ColSize         = 2,
        ColLastAnalyzed = 3,
        ColCount        = 4,
    };

    explicit ProjectBinaryModel(QObject* parent = nullptr);

    // Bind to a registry handle. Pass nullptr to clear.
    void setRegistry(AuraProjectBinaries* pb);

    // Re-read all rows from the registry.
    void reload();

    // Access the underlying record at `row` (read-only).
    const AuraProjectBinaryRecord* recordAt(int row) const;

    // QAbstractTableModel overrides.
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

private:
    AuraProjectBinaries*               m_pb = nullptr;
    QVector<AuraProjectBinaryRecord>   m_rows;
};

}  // namespace aura::gui
