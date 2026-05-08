// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "safety_settings_dialog.h"

#include <algorithm>
#include <string>
#include <vector>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>

namespace aura::gui {

namespace {

bool containsId(const std::vector<std::string>& ids, const std::string& id) {
    return std::find(ids.begin(), ids.end(), id) != ids.end();
}

QString countLabel(std::size_t count) {
    return QString::number(static_cast<qsizetype>(count));
}

QString displayName(const aura::safety::SafetyAssetRef& ref) {
    return QString::fromStdString(ref.display_name.empty() ? ref.id
                                                           : ref.display_name);
}

QString assetLabel(const aura::safety::SafetyAssetRef& ref) {
    QString label = QStringLiteral("%1 (%2, %3)")
                        .arg(displayName(ref),
                             QString::fromStdString(ref.id),
                             QString::fromStdString(ref.source));
    if (!ref.valid && !ref.diagnostic.empty()) {
        label += QStringLiteral(" - %1")
                     .arg(QString::fromStdString(ref.diagnostic));
    }
    return label;
}

QString selectedIdText(const std::vector<std::string>& ids) {
    if (ids.empty()) return QStringLiteral("none");

    QStringList parts;
    for (const auto& id : ids) {
        parts.push_back(QString::fromStdString(id));
    }
    return parts.join(QStringLiteral(", "));
}

QString currentComboProfileId(const QComboBox* combo) {
    return combo ? combo->currentData().toString() : QStringLiteral("default");
}

}  // namespace

SafetySettingsDialog::SafetySettingsDialog(const QString& selectedProfileId,
                                           QWidget* parent)
    : QDialog(parent),
      m_registry(aura::safety::listSafetyAssets()),
      m_initialProfileId(selectedProfileId) {
    setWindowTitle(QStringLiteral("Safety Assets"));
    setObjectName(QStringLiteral("safetySettingsDialog"));
    setModal(true);
    resize(560, 620);

    auto* root = new QVBoxLayout(this);

    auto* profileGroup = new QGroupBox(QStringLiteral("Profile"), this);
    auto* profileLayout = new QFormLayout(profileGroup);
    m_profileCombo = new QComboBox(profileGroup);
    m_profileCombo->setObjectName(QStringLiteral("safetyProfileCombo"));
    profileLayout->addRow(QStringLiteral("Active profile"), m_profileCombo);

    m_summaryLabel = new QLabel(profileGroup);
    m_summaryLabel->setObjectName(QStringLiteral("safetySummaryLabel"));
    m_summaryLabel->setWordWrap(true);
    profileLayout->addRow(QStringLiteral("Selection"), m_summaryLabel);
    root->addWidget(profileGroup);

    auto* detectionGroup = new QGroupBox(QStringLiteral("Detection"), this);
    auto* detectionLayout = new QVBoxLayout(detectionGroup);

    detectionLayout->addWidget(
        new QLabel(QStringLiteral("Token classification model"),
                   detectionGroup));
    m_modelList = new QListWidget(detectionGroup);
    m_modelList->setObjectName(QStringLiteral("safetyModelList"));
    detectionLayout->addWidget(m_modelList);

    detectionLayout->addWidget(new QLabel(QStringLiteral("Rule packs"),
                                          detectionGroup));
    m_rulePackList = new QListWidget(detectionGroup);
    m_rulePackList->setObjectName(QStringLiteral("safetyRulePackList"));
    detectionLayout->addWidget(m_rulePackList);
    root->addWidget(detectionGroup);

    auto* evalGroup = new QGroupBox(QStringLiteral("Evaluation"), this);
    auto* evalLayout = new QVBoxLayout(evalGroup);
    m_evalDatasetList = new QListWidget(evalGroup);
    m_evalDatasetList->setObjectName(QStringLiteral("safetyEvalDatasetList"));
    evalLayout->addWidget(m_evalDatasetList);
    root->addWidget(evalGroup);

    m_statusLabel = new QLabel(this);
    m_statusLabel->setObjectName(QStringLiteral("safetyStatusLabel"));
    m_statusLabel->setWordWrap(true);
    root->addWidget(m_statusLabel);

    auto* buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    root->addWidget(buttons);

    populate();
    connect(m_profileCombo, &QComboBox::currentIndexChanged, this,
            &SafetySettingsDialog::updateSummary);
    updateSummary();
}

QString SafetySettingsDialog::selectedProfileId() const {
    return m_resolvedProfileId;
}

QString SafetySettingsDialog::statusText() const {
    return m_statusLabel ? m_statusLabel->text() : QString();
}

void SafetySettingsDialog::populate() {
    if (!m_profileCombo) return;

    m_profileCombo->clear();
    int selectedIndex = -1;
    for (const auto& profile : m_registry.profiles) {
        const QString id = QString::fromStdString(profile.id);
        m_profileCombo->addItem(assetLabel(profile), id);
        if (id == m_initialProfileId) {
            selectedIndex = m_profileCombo->count() - 1;
        }
    }

    if (selectedIndex < 0) {
        selectedIndex = m_profileCombo->findData(QStringLiteral("default"));
    }
    if (selectedIndex >= 0) {
        m_profileCombo->setCurrentIndex(selectedIndex);
    }
}

void SafetySettingsDialog::addAssetRows(
    QListWidget* list,
    const std::vector<aura::safety::SafetyAssetRef>& refs,
    const std::vector<std::string>& selectedIds,
    bool showEmptyMessage) {
    if (!list) return;

    list->clear();
    if (refs.empty() && showEmptyMessage) {
        auto* item = new QListWidgetItem(QStringLiteral("No assets found"),
                                         list);
        item->setFlags(Qt::ItemIsEnabled);
        return;
    }

    for (const auto& ref : refs) {
        auto* item = new QListWidgetItem(assetLabel(ref), list);
        item->setCheckState(containsId(selectedIds, ref.id) ? Qt::Checked
                                                            : Qt::Unchecked);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        if (!ref.valid) {
            item->setToolTip(QString::fromStdString(ref.diagnostic));
        }
    }
}

void SafetySettingsDialog::updateSummary() {
    if (!m_summaryLabel || !m_statusLabel) return;

    const std::string id = currentComboProfileId(m_profileCombo).toStdString();
    const auto loaded = aura::safety::resolveSelectedSafetyProfile(id);
    const auto validation =
        aura::safety::validateSafetyProfile(loaded.profile);
    m_resolvedProfileId = QString::fromStdString(loaded.profile_id);

    std::vector<std::string> selectedModels;
    if (loaded.profile.model_policy.enabled &&
        !loaded.profile.model_policy.model_id.empty()) {
        selectedModels.push_back(loaded.profile.model_policy.model_id);
    } else if (!loaded.profile.token_classification_model_id.empty()) {
        selectedModels.push_back(loaded.profile.token_classification_model_id);
    }

    addAssetRows(m_modelList, m_registry.models, selectedModels, true);
    addAssetRows(m_rulePackList, m_registry.rule_packs,
                 loaded.profile.rule_pack_ids, true);
    addAssetRows(m_evalDatasetList, m_registry.eval_datasets,
                 loaded.profile.eval_dataset_ids, true);

    m_summaryLabel->setText(
        QStringLiteral("Profile: %1\nModel: %2\nRule packs: %3\nEval datasets: %4")
            .arg(QString::fromStdString(loaded.profile_id),
                 selectedIdText(selectedModels),
                 countLabel(loaded.profile.rule_pack_ids.size()),
                 countLabel(loaded.profile.eval_dataset_ids.size())));

    if (loaded.used_fallback) {
        m_statusLabel->setText(
            QStringLiteral("Selected profile was not available. Default "
                           "profile will be used."));
        return;
    }
    if (!loaded.found) {
        m_statusLabel->setText(
            QStringLiteral("Selected profile was not found. Default profile "
                           "will be used."));
        return;
    }
    if (!validation.valid) {
        m_statusLabel->setText(
            QStringLiteral("Profile has missing assets: %1")
                .arg(QString::fromStdString(validation.messages.front())));
        return;
    }

    m_statusLabel->setText(QStringLiteral("Profile is ready."));
}

}  // namespace aura::gui
