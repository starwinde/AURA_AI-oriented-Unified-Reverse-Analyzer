// src/gui/disasm_pane.h — Phase 11.3.7 (P2.F2 C3, ADR-0040).
//
// Disassembly pane (instruction-level). Mirrors DecompilePane shape:
// monospace QPlainTextEdit + per-function cache. Tabified onto the
// existing Decompile dock so the user toggles between pseudo-C and
// raw asm in one screen real estate.

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

class DisasmFlowGutter;  // Phase 11.6 T2 C3.

class DisasmPane : public QWidget {
    Q_OBJECT
public:
    explicit DisasmPane(QWidget* parent = nullptr);

    // Replace the displayed text. Each instruction is formatted as a
    // single line: <addr>  <bytes>  <mnemonic> <op_str>
    void showDisasm(quint64 funcAddr,
                    const QVector<GuiInstructionRecord>& ins);

    // Phase 11.6 T1 C2: replace the rizin pdf annotated-text view
    // (with asm.lines flow arrows) for `funcAddr`. Called after
    // showDisasm by MainWindow::runDisasm once the body's text blob
    // is available. Empty string clears the arrow tab.
    void setArrowText(quint64 funcAddr, const QString& text);

    // Cache control.
    bool                                   hasCached(quint64 funcAddr) const;
    QVector<GuiInstructionRecord>          cached(quint64 funcAddr) const;
    QString                                cachedArrowText(quint64 funcAddr) const;
    void                                   cache(quint64 funcAddr,
                                                 const QVector<GuiInstructionRecord>& ins);
    void                                   clearCache();

    // Show a placeholder ("선택된 함수 없음" / "분석 중...").
    void showPlaceholder(const QString& message);

    // Test hooks.
    QString currentText() const;
    int     currentLineCount() const;
    int     currentCursorLine() const;  // 0-based

    // Phase 11.6 T2 C3: read-only access to the embedded flow gutter
    // so gui_smoke can verify arrows were pushed in after showDisasm.
    DisasmFlowGutter* flowGutter() const { return m_flowGutter; }

    // Phase 11.5 (P5 polish): adjust monospace text-view font size
    // (Ctrl+= / Ctrl+- / Ctrl+0). pt clamped to [6, 32].
    void setMonospaceFontPointSize(int pt);
    int  monospaceFontPointSize() const;

public slots:
    /* Phase 11.3.7 (P2.F2 C4): jump cursor to the instruction whose
     * `addr` matches; highlight the line. No-op if addr unknown in
     * the currently-displayed function. Wired in main_window from
     * DecompilePane::lineSelected. */
    void selectInstruction(quint64 addr);

signals:
    /* Phase 11.3.9 (P2.F4 C1): emitted when the user moves the cursor
     * onto a line that maps to a known instruction address. Wired in
     * main_window to DecompilePane::selectLine for bidirectional
     * line_map sync (the F4 closure of F2's deferred reverse path). */
    void instructionSelected(quint64 addr);

private slots:
    void onCursorPositionChanged();

private:
    QLabel*           m_headerLabel = nullptr;
    QTabWidget*       m_tabs        = nullptr;   // Phase 11.6 T1 C2
    QPlainTextEdit*   m_textView    = nullptr;   // Tab 1: structured
    QPlainTextEdit*   m_arrowView   = nullptr;   // Tab 2: pdf w/ arrows
    DisasmFlowGutter* m_flowGutter  = nullptr;   // Phase 11.6 T2 C3

    QHash<quint64, QVector<GuiInstructionRecord>> m_cache;
    QHash<quint64, QString>                       m_arrowCache;  // 11.6 T1
    /* addr → 0-based line index in the currently-displayed pane. */
    QHash<quint64, int>                            m_addrToLine;
    /* 0-based line index → addr (Phase 11.3.9 reverse mapping for
     * cursorPositionChanged → emit instructionSelected). */
    QVector<quint64>                               m_lineToAddr;
};

}  // namespace aura::gui
