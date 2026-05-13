// src/gui/analysis_options_dialog.cpp — implementation.

#include "analysis_options_dialog.h"

#include "aura/safety/string_safety.h"

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QVBoxLayout>

namespace aura::gui {

namespace {

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

bool activeSafetyProfileEnablesProtection() {
    QSettings settings(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    const QString id = settings.value(QStringLiteral("safety/activeProfileId"),
                                      QStringLiteral("default")).toString();
    const auto selected =
        aura::safety::resolveSelectedSafetyProfile(id.toStdString());
    const auto& profile = selected.profile;
    return aura::safety::effectiveRuleCount(profile) > 0u;
}

}  // namespace

AnalysisOptionsDialog::AnalysisOptionsDialog(const QString& binaryPath,
                                             QWidget*       parent)
    : QDialog(parent) {
    const bool ko = useKoreanUi();
    setWindowTitle(ko ? QStringLiteral("분석 옵션")
                      : QStringLiteral("Analysis Options"));
    setModal(true);
    resize(520, 240);

    auto* outer = new QVBoxLayout(this);

    // Path display (read-only).
    auto* form = new QFormLayout();
    auto* pathEdit = new QLineEdit(binaryPath, this);
    pathEdit->setReadOnly(true);
    form->addRow(ko ? QStringLiteral("바이너리:")
                    : QStringLiteral("Binary:"), pathEdit);
    outer->addLayout(form);

    m_enableStringProtection = new QCheckBox(
        ko ? QStringLiteral("문자열 마스킹/보호 스캔 사용")
           : QStringLiteral("Enable string masking/protection scan"),
        this);
    m_enableStringProtection->setObjectName(
        QStringLiteral("analysisStringProtectionCheckBox"));
    m_enableStringProtection->setChecked(activeSafetyProfileEnablesProtection());
    outer->addWidget(m_enableStringProtection);

    auto* safetyAssetsButton = new QPushButton(
        ko ? QStringLiteral("안전 자산 세부 설정...")
           : QStringLiteral("Safety Assets settings..."),
        this);
    safetyAssetsButton->setObjectName(
        QStringLiteral("analysisSafetyAssetsButton"));
    form->addRow(ko ? QStringLiteral("보호 세부 설정:")
                    : QStringLiteral("Protection settings:"),
                 safetyAssetsButton);
    connect(safetyAssetsButton, &QPushButton::clicked,
            this, &AnalysisOptionsDialog::safetyAssetsRequested);

    auto* protectionHint = new QLabel(
        ko ? QStringLiteral("켜면 현재 안전 자산 프로필의 모델/규칙 팩으로 문자열을 보호합니다.")
           : QStringLiteral("When enabled, this analysis uses the active Safety Assets profile."),
        this);
    protectionHint->setStyleSheet(QStringLiteral("color: gray;"));
    protectionHint->setWordWrap(true);
    outer->addWidget(protectionHint);

    // Level radio group.
    auto* levelBox    = new QGroupBox(
        ko ? QStringLiteral("분석 단계") : QStringLiteral("Analysis level"),
        this);
    auto* levelLayout = new QVBoxLayout(levelBox);
    m_radioQuick = new QRadioButton(
        ko ? QStringLiteral("빠름 — Rizin `aa` (빠르지만 얕은 분석)")
           : QStringLiteral("Quick —  Rizin `aa`  (faster, shallower)"),
        levelBox);
    m_radioFull  = new QRadioButton(
        ko ? QStringLiteral("기본 — Rizin `aaa` (권장 기본값)")
           : QStringLiteral("Full  —  Rizin `aaa` (default)"),
        levelBox);
    m_radioAdvanced = new QRadioButton(
        ko ? QStringLiteral("고급 — Rizin `aaaa` (공격적 분석, 느릴 수 있음)")
           : QStringLiteral("Advanced — Rizin `aaaa` (aggressive, slower)"),
        levelBox);
    m_radioFull->setChecked(true);
    levelLayout->addWidget(m_radioQuick);
    levelLayout->addWidget(m_radioFull);
    levelLayout->addWidget(m_radioAdvanced);
    outer->addWidget(levelBox);

    auto* hint = new QLabel(
        ko ? QStringLiteral("추가 옵션(write mode / VA / demangle 등)은 이후 확장 예정")
           : QStringLiteral("More options (write mode / VA / demangle) are planned"),
        this);
    hint->setStyleSheet(QStringLiteral("color: gray;"));
    outer->addWidget(hint);

    outer->addStretch();

    // OK / Cancel.
    auto* buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    outer->addWidget(buttons);
}

AuraAnalysisLevel AnalysisOptionsDialog::selectedLevel() const {
    if (m_radioQuick && m_radioQuick->isChecked())
        return AURA_ANALYSIS_LEVEL_QUICK;
    if (m_radioAdvanced && m_radioAdvanced->isChecked())
        return AURA_ANALYSIS_LEVEL_ADVANCED;
    return AURA_ANALYSIS_LEVEL_FULL;
}

bool AnalysisOptionsDialog::stringProtectionEnabled() const {
    return m_enableStringProtection && m_enableStringProtection->isChecked();
}

void AnalysisOptionsDialog::setStringProtectionEnabled(bool enabled) {
    if (m_enableStringProtection) m_enableStringProtection->setChecked(enabled);
}

}  // namespace aura::gui
