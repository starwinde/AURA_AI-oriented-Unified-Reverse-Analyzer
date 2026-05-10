// src/gui/analysis_options_dialog.cpp — implementation.

#include "analysis_options_dialog.h"

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
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
    m_enableStringProtection->setChecked(false);
    outer->addWidget(m_enableStringProtection);

    auto* protectionHint = new QLabel(
        ko ? QStringLiteral("켜면 이번 분석에서 문자열 안전 스캔과 마스킹 후보를 생성합니다.")
           : QStringLiteral("When enabled, this analysis generates string safety findings and masked values."),
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

}  // namespace aura::gui
