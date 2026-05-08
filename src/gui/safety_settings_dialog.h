// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <QDialog>
#include <QString>

#include <string>
#include <vector>

#include "aura/safety/string_safety.h"

class QComboBox;
class QLabel;
class QListWidget;

namespace aura::gui {

class SafetySettingsDialog final : public QDialog {
    Q_OBJECT

public:
    explicit SafetySettingsDialog(const QString& selectedProfileId,
                                  QWidget* parent = nullptr);

    QString selectedProfileId() const;
    aura::safety::SafetyProfile editedProfile() const;
    QString statusText() const;

private:
    void populate();
    void updateSummary();
    void updateStatusFromEditedProfile(const aura::safety::SafetyProfile& profile,
                                      bool usedFallback,
                                      bool found);
    void addAssetRows(QListWidget* list,
                      const std::vector<aura::safety::SafetyAssetRef>& refs,
                      const std::vector<std::string>& selectedIds,
                      bool showEmptyMessage);
    void applyModelSelectionToProfile(
        aura::safety::SafetyProfile& profile) const;
    std::vector<std::string> selectedModelIds() const;
    void updateModelSelectionFromChecked();

    aura::safety::SafetyAssetRegistry m_registry;
    QString m_initialProfileId;
    QString m_resolvedProfileId = QStringLiteral("default");
    QComboBox* m_profileCombo = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QLabel* m_statusLabel = nullptr;
    QListWidget* m_modelList = nullptr;
    QListWidget* m_rulePackList = nullptr;
    QListWidget* m_evalDatasetList = nullptr;
};

}  // namespace aura::gui
