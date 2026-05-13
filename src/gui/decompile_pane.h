// src/gui/decompile_pane.h — Phase 11.3.1 Slice B/C (ADR-0036).
//
// Right-dock pane that displays the Rizin decompile result for the
// currently selected function. v1.1 = monospace QPlainTextEdit + cache
// + backend label header.

#pragma once

#include <QHash>
#include <QString>
#include <QWidget>

class QLabel;
class QPlainTextEdit;

namespace aura::gui {

/* Phase 11.3.7 (P2.F2 C4): line_map maps decompile body line numbers
 * (1-based) to engine-reported addresses. Used by the cursor-changed
 * → lineSelected(addr) signal to drive Disasm sync. Empty for backends
 * that don't emit a line map (PDD text / PDF fallback). */
using DecompileLineAddrMap = QHash<int /*line*/, quint64 /*addr*/>;

class DecompilePane : public QWidget {
    Q_OBJECT
public:
    explicit DecompilePane(QWidget* parent = nullptr);

    // Replace the displayed text + backend label.
    void showDecompile(quint64 funcAddr, const QString& backendLabel,
                       const QString& text);

    // Cache control.
    bool        hasCached(quint64 funcAddr) const;
    QString     cachedText(quint64 funcAddr) const;
    QString     cachedBackend(quint64 funcAddr) const;
    DecompileLineAddrMap cachedLineMap(quint64 funcAddr) const;
    void        cache(quint64 funcAddr, const QString& backendLabel,
                      const QString& text);
    void        cache(quint64 funcAddr, const QString& backendLabel,
                      const QString& text,
                      const DecompileLineAddrMap& lineMap);
    void        clearCache();

    // Show a placeholder ("선택된 함수 없음" / "분석 중...").
    void showPlaceholder(const QString& message);

    // Test hook.
    QString currentText() const;

    // Phase 11.5 (P5 polish): adjust the monospace text-view font size
    // (Ctrl+= / Ctrl+- / Ctrl+0 wired in main_window). pt is clamped
    // to [6, 32] inside the implementation.
    void setMonospaceFontPointSize(int pt);
    int  monospaceFontPointSize() const;

signals:
    /* Emitted when the user clicks/moves the cursor onto a line that
     * the line_map maps to a concrete address. Wired in main_window
     * to DisasmPane::selectInstruction(addr). */
    void lineSelected(quint64 addr);

    /* Phase 11.3.9 (P2.F4 C2): context-menu actions emitted to
     * main_window. addr is the cursor-line addr (0 if unmapped) for
     * actions that need it; rename/reset are function-scoped and use
     * main_window's active function entry. */
    void contextJumpToDisasm(quint64 addr);
    void contextRename();
    void contextResetName();
    void contextFindXrefs(quint64 addr);
    void contextAddComment(quint64 addr);
    void contextToggleStringSubstitution();

public slots:
    /* Phase 11.3.9 (P2.F4 C1): jump cursor to whichever line the
     * current function's reverse line_map maps `addr` to. No-op if
     * unmapped (PDD/PDF text fallbacks have no line_map). Wired from
     * DisasmPane::instructionSelected via main_window. */
    void selectLine(quint64 addr);

private slots:
    void onCursorPositionChanged();
    void onContextMenuRequested(const class QPoint& pos);

private:
    QLabel*         m_headerLabel = nullptr;
    QPlainTextEdit* m_textView    = nullptr;

    struct Entry {
        QString              backendLabel;
        QString              text;
        DecompileLineAddrMap lineMap;
    };
    QHash<quint64, Entry> m_cache;

    /* Snapshot of the currently-displayed function's line map so the
     * cursor handler can resolve clicks without a per-event hash lookup
     * back through the cache. */
    DecompileLineAddrMap m_currentLineMap;
    /* Phase 11.3.9: addr → 1-based line index for the reverse direction
     * (DisasmPane.instructionSelected → selectLine). Built alongside
     * m_currentLineMap from the same Entry. */
    QHash<quint64, int>  m_currentAddrToLine;
};

}  // namespace aura::gui
