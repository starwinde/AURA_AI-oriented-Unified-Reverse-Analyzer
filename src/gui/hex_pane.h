// src/gui/hex_pane.h — Phase 11.3.10 (P2.F5 C2, ADR-0043).
//
// Hex view dock — raw bytes, mmap-direct, display-only path.
// Per ADR-0043 D1: hex bytes do NOT route through normalized records
// or AuraEngineResponse — the pane reads the file directly via mmap.
// R-9/R-12 are unaffected (raw bytes are not analysis output).

#pragma once

#include <QHash>
#include <QString>
#include <QWidget>

extern "C" {
#include "mapped_file.h"
}

class QLabel;
class QPlainTextEdit;

namespace aura::gui {

class HexPane : public QWidget {
    Q_OBJECT
public:
    explicit HexPane(QWidget* parent = nullptr);
    ~HexPane() override;

    // Open / close a binary by path. openBinary swaps in a fresh
    // MappedFile and renders the first window of bytes (C2: ≤16KB
    // initial render; viewport-driven lazy generation lands in C3).
    bool openBinary(const QString& path);
    void closeBinary();

    // Test hooks.
    QString  currentText() const;
    int      currentLineCount() const;
    quint64  fileSize() const;
    /* Phase 11.3.10 (P2.F5 C3): byte offset of the first row currently
     * rendered. Used by tests to verify window paging. */
    quint64  windowStartOffset() const;
    /* Number of bytes in the window currently rendered. */
    quint64  windowByteCount() const;

    // Phase 11.5 (P5 polish): adjust monospace text-view font size
    // (Ctrl+= / Ctrl+- / Ctrl+0). pt clamped to [6, 32].
    void setMonospaceFontPointSize(int pt);
    int  monospaceFontPointSize() const;

public slots:
    /* Phase 11.3.10 (P2.F5 C4 — connect target): scroll the view to
     * the row containing `addr`. v1: simple line index = addr / 16;
     * file_offset == addr (no VA→file translation in v1 — D1 v2). */
    void scrollToAddr(quint64 addr);

private:
    /* Phase 11.3.10 (P2.F5 C3): render a window starting at file offset
     * `start` for `byteCount` bytes (clamped to file size). 100MB+
     * binaries stay responsive because the QPlainTextEdit only ever
     * holds a window-sized text. */
    void fillRange(quint64 start, quint64 byteCount);

    QLabel*         m_headerLabel = nullptr;
    QPlainTextEdit* m_textView    = nullptr;
    MappedFile*     m_mf          = nullptr;  // owned

    // Currently-rendered window (byte offsets into the mmap region).
    quint64 m_windowStart = 0;
    quint64 m_windowBytes = 0;
};

}  // namespace aura::gui
