// src/gui/analysis_options_dialog.h — Phase 11.3 Slice E (ADR-0035).
//
// Cutter-inspired Analysis Options dialog. v1 exposes aa / aaa / aaaa.
// v2 will add per-option checkboxes (write mode / VA / demangle / ...).

#pragma once

#include <QDialog>
#include <QString>

extern "C" {
#include "engine_request.h"
}

class QRadioButton;
class QCheckBox;

namespace aura::gui {

class AnalysisOptionsDialog : public QDialog {
    Q_OBJECT
public:
    explicit AnalysisOptionsDialog(const QString& binaryPath,
                                   QWidget*       parent = nullptr);

    AuraAnalysisLevel selectedLevel() const;
    bool stringProtectionEnabled() const;

private:
    QCheckBox*    m_enableStringProtection = nullptr;
    QRadioButton* m_radioFull  = nullptr;
    QRadioButton* m_radioQuick = nullptr;
    QRadioButton* m_radioAdvanced = nullptr;
};

}  // namespace aura::gui
