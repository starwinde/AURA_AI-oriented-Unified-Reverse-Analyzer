// src/gui/full_disasm_pane.h — Cutter-style continuous disassembly view.

#pragma once

#include <QHash>
#include <QString>
#include <QVector>
#include <QWidget>

#include "main_window.h"  // GuiInstructionRecord

class QLabel;
class QPlainTextEdit;
class QTabWidget;

namespace aura::gui {

class DisasmFlowGutter;

class FullDisasmPane : public QWidget {
    Q_OBJECT
public:
    explicit FullDisasmPane(QWidget* parent = nullptr);

    void setFunctionLabels(const QHash<quint64, QString>& labels);
    void showText(quint64 baseAddr, quint64 byteCount, const QString& text);
    void showInstructions(quint64 baseAddr,
                          int requestedCount,
                          const QVector<GuiInstructionRecord>& ins);
    void showMixedListing(quint64 baseAddr,
                          int requestedCount,
                          const QString& text,
                          const QVector<GuiInstructionRecord>& ins);
    void setArrowText(quint64 baseAddr, const QString& text);
    void showPlaceholder(const QString& message);

    quint64 currentAddress() const { return m_currentAddr; }
    QString currentText() const;

public slots:
    void setStartAddress(quint64 addr);

private:
    QLabel*           m_headerLabel = nullptr;
    QTabWidget*       m_tabs        = nullptr;
    QPlainTextEdit*   m_textView    = nullptr;
    QPlainTextEdit*   m_arrowView   = nullptr;
    DisasmFlowGutter* m_flowGutter  = nullptr;
    quint64           m_currentAddr = 0;
    QHash<quint64, int>     m_addrToLine;
    QHash<quint64, QString> m_functionLabels;

    void rebuildAddressIndex(const QString& text);
    QString formatMixedListingLine(const QString& line) const;
};

}  // namespace aura::gui
