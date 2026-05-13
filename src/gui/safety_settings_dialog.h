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
class QPushButton;

namespace aura::gui {

class SafetySettingsDialog final : public QDialog {
    Q_OBJECT

public:
    explicit SafetySettingsDialog(const QString& selectedProfileId,
                                  QWidget* parent = nullptr);

    QString selectedProfileId() const;
    aura::safety::SafetyProfile editedProfile() const;
    QString statusText() const;

signals:
    void recomputeProtectionRequested();
    void deleteProtectionRequested();
    void applyProfileRequested();

private:
    void populate();
    void updateSummary(bool resetSelection = false);
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
    void applyRulePackSelectionToProfile(
        aura::safety::SafetyProfile& profile) const;
    std::vector<std::string> selectedRulePackIds() const;
    void updateModelSelectionFromChecked();
    QString runtimeSafetyAssetRoot() const;
    QString tokenClassificationModelsDir() const;
    QString rulePacksDir() const;
    bool openDirectory(const QString& path);

    aura::safety::SafetyAssetRegistry m_registry;
    QString m_initialProfileId;
    QString m_resolvedProfileId = QStringLiteral("default");
    QComboBox* m_profileCombo = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QLabel* m_statusLabel = nullptr;
    QListWidget* m_modelList = nullptr;
    QListWidget* m_rulePackList = nullptr;
    QListWidget* m_evalDatasetList = nullptr;
    QLabel* m_protectionPolicyHelpLabel = nullptr;
    QPushButton* m_recomputeProtectionButton = nullptr;
    QPushButton* m_deleteProtectionButton = nullptr;
    bool m_modelSelectionEdited = false;
    bool m_rulePackSelectionEdited = false;
};

}  // namespace aura::gui
