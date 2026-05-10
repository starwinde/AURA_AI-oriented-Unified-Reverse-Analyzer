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
#include <QPushButton>
#include <QSettings>
#include <QSignalBlocker>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace aura::gui {

namespace {

bool containsId(const std::vector<std::string>& ids, const std::string& id) {
    return std::find(ids.begin(), ids.end(), id) != ids.end();
}

QString countLabel(std::size_t count) {
    return QString::number(static_cast<qsizetype>(count));
}

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

QString textKoEn(const char* ko, const char* en) {
    return useKoreanUi() ? QString::fromUtf8(ko) : QString::fromUtf8(en);
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
    if (ids.empty()) return textKoEn("없음", "none");

    QStringList parts;
    for (const auto& id : ids) {
        parts.push_back(QString::fromStdString(id));
    }
    return parts.join(QStringLiteral(", "));
}

QString currentComboProfileId(const QComboBox* combo) {
    return combo ? combo->currentData().toString() : QStringLiteral("default");
}

std::vector<std::string> checkedIdsFromList(const QListWidget* list) {
    std::vector<std::string> ids;
    if (!list) return ids;
    for (int i = 0; i < list->count(); ++i) {
        const auto* item = list->item(i);
        if (!item || item->checkState() != Qt::Checked) continue;
        const QString id = item->data(Qt::UserRole).toString();
        if (!id.isEmpty()) ids.push_back(id.toStdString());
    }
    return ids;
}

std::vector<std::string> validIdsFromList(const QListWidget* list) {
    std::vector<std::string> ids;
    if (!list) return ids;
    for (int i = 0; i < list->count(); ++i) {
        const auto* item = list->item(i);
        if (!item || !item->data(Qt::UserRole + 1).toBool()) continue;
        const QString id = item->data(Qt::UserRole).toString();
        if (!id.isEmpty()) ids.push_back(id.toStdString());
    }
    return ids;
}

std::vector<std::string> validIdsFromRefs(
    const std::vector<aura::safety::SafetyAssetRef>& refs) {
    std::vector<std::string> ids;
    for (const auto& ref : refs) {
        if (ref.valid) ids.push_back(ref.id);
    }
    return ids;
}

std::vector<std::string> activeModelIdsFromProfile(
    const aura::safety::SafetyProfile& profile) {
    if (!profile.model_policy.model_id.empty()) {
        return {profile.model_policy.model_id};
    }
    if (!profile.token_classification_model_id.empty()) {
        return {profile.token_classification_model_id};
    }
    return {};
}

void applyModelIdsToProfile(aura::safety::SafetyProfile& profile,
                           const std::vector<std::string>& modelIds) {
    if (modelIds.empty()) {
        profile.model_policy.enabled = false;
        profile.model_policy.model_id.clear();
        profile.token_classification_enabled = false;
        profile.token_classification_model_id.clear();
        return;
    }
    profile.model_policy.enabled = true;
    profile.model_policy.model_id = modelIds.front();
    profile.token_classification_model_id = modelIds.front();
    profile.token_classification_enabled = true;
    if (profile.model_policy.mode ==
        aura::safety::ModelPolicyMode::Disabled) {
        profile.model_policy.mode = aura::safety::ModelPolicyMode::Conditional;
    }
}

}  // namespace

SafetySettingsDialog::SafetySettingsDialog(const QString& selectedProfileId,
                                           QWidget* parent)
    : QDialog(parent),
      m_registry(aura::safety::listSafetyAssets()),
      m_initialProfileId(selectedProfileId) {
    setWindowTitle(textKoEn("안전 자산", "Safety Assets"));
    setObjectName(QStringLiteral("safetySettingsDialog"));
    setModal(true);
    resize(560, 620);

    auto* root = new QVBoxLayout(this);

    auto* profileGroup = new QGroupBox(textKoEn("프로필", "Profile"), this);
    auto* profileLayout = new QFormLayout(profileGroup);
    m_profileCombo = new QComboBox(profileGroup);
    m_profileCombo->setObjectName(QStringLiteral("safetyProfileCombo"));
    profileLayout->addRow(textKoEn("활성 프로필", "Active profile"),
                          m_profileCombo);

    m_summaryLabel = new QLabel(profileGroup);
    m_summaryLabel->setObjectName(QStringLiteral("safetySummaryLabel"));
    m_summaryLabel->setWordWrap(true);
    profileLayout->addRow(textKoEn("선택", "Selection"), m_summaryLabel);
    root->addWidget(profileGroup);

    auto* detectionGroup = new QGroupBox(textKoEn("탐지", "Detection"), this);
    auto* detectionLayout = new QVBoxLayout(detectionGroup);

    detectionLayout->addWidget(
        new QLabel(textKoEn("토큰 분류 모델", "Token classification model"),
                   detectionGroup));
    detectionLayout->addWidget(
        new QLabel(
            textKoEn("체크된 모델만 이번 프로파일에 사용됩니다. 자산 추가/삭제는 별도 관리자 메뉴를 사용합니다.",
                     "Only checked models are used by this profile. Use the asset manager to add or remove assets."),
            detectionGroup));
    m_modelList = new QListWidget(detectionGroup);
    m_modelList->setObjectName(QStringLiteral("safetyModelList"));
    detectionLayout->addWidget(m_modelList);

    const QString applyText = textKoEn("선택 적용", "Apply selected");
    const QString removeText = textKoEn("선택 해제", "Clear selected");

    auto* modelButtons = new QHBoxLayout();
    auto* addModelBtn = new QPushButton(applyText, detectionGroup);
    addModelBtn->setObjectName(QStringLiteral("safetyModelAddButton"));
    auto* removeModelBtn = new QPushButton(removeText, detectionGroup);
    removeModelBtn->setObjectName(QStringLiteral("safetyModelRemoveButton"));
    modelButtons->addWidget(addModelBtn);
    modelButtons->addWidget(removeModelBtn);
    modelButtons->addStretch();
    detectionLayout->addLayout(modelButtons);

    detectionLayout->addWidget(new QLabel(textKoEn("규칙 팩", "Rule packs"),
                                          detectionGroup));
    detectionLayout->addWidget(
        new QLabel(
            textKoEn("모두 해제하면 런타임의 모든 규칙 팩을 사용합니다.",
                     "Clearing all rule packs uses all runtime rule packs."),
            detectionGroup));
    m_rulePackList = new QListWidget(detectionGroup);
    m_rulePackList->setObjectName(QStringLiteral("safetyRulePackList"));
    detectionLayout->addWidget(m_rulePackList);

    auto* ruleButtons = new QHBoxLayout();
    auto* addRuleBtn = new QPushButton(applyText, detectionGroup);
    addRuleBtn->setObjectName(QStringLiteral("safetyRulePackAddButton"));
    auto* removeRuleBtn = new QPushButton(removeText, detectionGroup);
    removeRuleBtn->setObjectName(QStringLiteral("safetyRulePackRemoveButton"));
    ruleButtons->addWidget(addRuleBtn);
    ruleButtons->addWidget(removeRuleBtn);
    ruleButtons->addStretch();
    detectionLayout->addLayout(ruleButtons);
    root->addWidget(detectionGroup);

    auto* evalGroup = new QGroupBox(textKoEn("평가", "Evaluation"), this);
    auto* evalLayout = new QVBoxLayout(evalGroup);
    evalLayout->addWidget(
        new QLabel(
            textKoEn("평가 데이터셋은 탐지 성능 검증용이며, 분석 중 실시간 마스킹 규칙은 아닙니다.",
                     "Eval datasets are for safety-filter evaluation, not live masking rules."),
            evalGroup));
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
    connect(m_profileCombo, &QComboBox::currentIndexChanged, this, [this]() {
        updateSummary(/*resetSelection=*/true);
    });
    connect(m_modelList, &QListWidget::itemChanged, this,
            [this](QListWidgetItem* item) {
        if (item && item->checkState() == Qt::Checked) {
            m_modelList->setCurrentItem(item);
        }
        updateModelSelectionFromChecked();
        updateSummary();
    });
    connect(m_rulePackList, &QListWidget::itemChanged, this, [this]() {
        updateSummary();
    });
    connect(addModelBtn, &QPushButton::clicked, this, [this]() {
        if (!m_modelList) return;
        auto* item = m_modelList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_modelList);
        item->setCheckState(Qt::Checked);
        updateModelSelectionFromChecked();
        updateSummary();
    });
    connect(removeModelBtn, &QPushButton::clicked, this, [this]() {
        if (!m_modelList) return;
        auto* item = m_modelList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_modelList);
        item->setCheckState(Qt::Unchecked);
        updateModelSelectionFromChecked();
        updateSummary();
    });
    connect(addRuleBtn, &QPushButton::clicked, this, [this]() {
        if (!m_rulePackList) return;
        auto* item = m_rulePackList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_rulePackList);
        item->setCheckState(Qt::Checked);
        updateSummary();
    });
    connect(removeRuleBtn, &QPushButton::clicked, this, [this]() {
        if (!m_rulePackList) return;
        auto* item = m_rulePackList->currentItem();
        if (!item) return;
        QSignalBlocker blocker(m_rulePackList);
        item->setCheckState(Qt::Unchecked);
        updateSummary();
    });
    updateSummary(/*resetSelection=*/true);
}

QString SafetySettingsDialog::selectedProfileId() const {
    return m_resolvedProfileId;
}

QString SafetySettingsDialog::statusText() const {
    return m_statusLabel ? m_statusLabel->text() : QString();
}

std::vector<std::string> SafetySettingsDialog::selectedModelIds() const {
    return checkedIdsFromList(m_modelList);
}

void SafetySettingsDialog::applyModelSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    applyModelIdsToProfile(profile, selectedModelIds());
}

std::vector<std::string> SafetySettingsDialog::selectedRulePackIds() const {
    auto ids = checkedIdsFromList(m_rulePackList);
    if (!ids.empty()) return ids;
    return validIdsFromList(m_rulePackList);
}

void SafetySettingsDialog::applyRulePackSelectionToProfile(
    aura::safety::SafetyProfile& profile) const {
    profile.rule_pack_ids = selectedRulePackIds();
}

aura::safety::SafetyProfile SafetySettingsDialog::editedProfile() const {
    const std::string id = currentComboProfileId(m_profileCombo).toStdString();
    const auto loaded = aura::safety::resolveSelectedSafetyProfile(id);
    auto profile = loaded.profile;
    applyModelSelectionToProfile(profile);
    applyRulePackSelectionToProfile(profile);
    return profile;
}

void SafetySettingsDialog::updateStatusFromEditedProfile(
    const aura::safety::SafetyProfile& profile,
    bool usedFallback,
    bool found) {
    const auto validation = aura::safety::validateSafetyProfile(profile);
    if (usedFallback) {
        m_statusLabel->setText(
            textKoEn("선택한 프로필을 사용할 수 없습니다. 기본 프로필을 사용합니다.",
                     "Selected profile was not available. Default profile will be used."));
        return;
    }
    if (!found) {
        m_statusLabel->setText(
            textKoEn("선택한 프로필을 찾을 수 없습니다. 기본 프로필을 사용합니다.",
                     "Selected profile was not found. Default profile will be used."));
        return;
    }
    if (!validation.valid) {
        const QString detail = validation.messages.empty()
                                   ? QStringLiteral("missing required assets.")
                                   : QString::fromStdString(
                                         validation.messages.front());
        m_statusLabel->setText(
            textKoEn("프로필에 누락된 자산이 있습니다: %1",
                     "Profile has missing assets: %1")
                .arg(detail));
        return;
    }
    m_statusLabel->setText(
        textKoEn("프로필을 사용할 수 있습니다.", "Profile is ready."));
}

void SafetySettingsDialog::updateModelSelectionFromChecked() {
    if (!m_modelList) return;
    QListWidgetItem* selectedItem = nullptr;
    if (auto* currentItem = m_modelList->currentItem();
        currentItem && currentItem->checkState() == Qt::Checked) {
        selectedItem = currentItem;
    }
    if (!selectedItem) {
        for (int i = 0; i < m_modelList->count(); ++i) {
            auto* item = m_modelList->item(i);
            if (item && item->checkState() == Qt::Checked) {
                selectedItem = item;
                break;
            }
        }
    }

    QSignalBlocker blocker(m_modelList);
    for (int i = 0; i < m_modelList->count(); ++i) {
        auto* item = m_modelList->item(i);
        if (!item || item->checkState() != Qt::Checked) continue;
        item->setCheckState(item == selectedItem ? Qt::Checked
                                                 : Qt::Unchecked);
    }
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

    const QSignalBlocker blocker(list);
    list->clear();
    if (refs.empty() && showEmptyMessage) {
        auto* item = new QListWidgetItem(textKoEn("자산을 찾을 수 없습니다",
                                                 "No assets found"),
                                         list);
        item->setFlags(Qt::ItemIsEnabled);
        return;
    }

    for (const auto& ref : refs) {
        auto* item = new QListWidgetItem(assetLabel(ref), list);
        item->setCheckState(containsId(selectedIds, ref.id) ? Qt::Checked
                                                            : Qt::Unchecked);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        if (list == m_modelList || list == m_rulePackList) {
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setData(Qt::UserRole, QString::fromStdString(ref.id));
            item->setData(Qt::UserRole + 1, ref.valid);
        }
        if (!ref.valid) {
            item->setToolTip(QString::fromStdString(ref.diagnostic));
        }
    }
}

void SafetySettingsDialog::updateSummary(bool resetSelection) {
    if (!m_summaryLabel || !m_statusLabel) return;

    const std::string id = currentComboProfileId(m_profileCombo).toStdString();
    const auto loaded = aura::safety::resolveSelectedSafetyProfile(id);
    m_resolvedProfileId = QString::fromStdString(loaded.profile_id);
    auto workingProfile = loaded.profile;
    if (resetSelection) {
        const auto selectedFromProfile = activeModelIdsFromProfile(workingProfile);
        applyModelIdsToProfile(workingProfile, selectedFromProfile);
    } else {
        applyModelSelectionToProfile(workingProfile);
    }

    std::vector<std::string> selectedModels;
    if (!resetSelection) {
        selectedModels = selectedModelIds();
    }
    if (selectedModels.empty()) {
        selectedModels = activeModelIdsFromProfile(workingProfile);
    }

    std::vector<std::string> checkedRulePacks = workingProfile.rule_pack_ids;
    if (!resetSelection) {
        checkedRulePacks = checkedIdsFromList(m_rulePackList);
    }

    addAssetRows(m_modelList, m_registry.models, selectedModels, true);
    workingProfile.rule_pack_ids = checkedRulePacks.empty()
                                       ? validIdsFromRefs(m_registry.rule_packs)
                                       : checkedRulePacks;
    addAssetRows(m_rulePackList, m_registry.rule_packs,
                 checkedRulePacks, true);
    addAssetRows(m_evalDatasetList, m_registry.eval_datasets,
                 workingProfile.eval_dataset_ids, true);

    m_summaryLabel->setText(
        textKoEn("프로필: %1\n모델: %2\n규칙 팩: %3\n평가 데이터셋: %4",
                 "Profile: %1\nModel: %2\nRule packs: %3\nEval datasets: %4")
            .arg(QString::fromStdString(loaded.profile_id),
                 selectedIdText(selectedModels),
                 countLabel(workingProfile.rule_pack_ids.size()),
                 countLabel(workingProfile.eval_dataset_ids.size())));
    updateStatusFromEditedProfile(workingProfile, loaded.used_fallback,
                                 loaded.found);
}

}  // namespace aura::gui
