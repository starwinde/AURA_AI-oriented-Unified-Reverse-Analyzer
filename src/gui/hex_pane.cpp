// src/gui/hex_pane.cpp — implementation (C2 skeleton).

#include "hex_pane.h"

#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QVBoxLayout>

namespace aura::gui {

namespace {
constexpr int     kBytesPerRow = 16;
/* Phase 11.3.10 (P2.F5 C3): window size for lazy rendering. ~32 KB =
 * 2048 rows of hex text — large enough that scrolling within a function
 * stays inside one window, small enough that 100MB+ binaries don't
 * blow up QPlainTextEdit. */
constexpr quint64 kWindowBytes = 32u * 1024u;

// Format a single 16-byte row as:
//   "<addr16hex>  XX XX ...  ASCII (non-printable→.)"
QString formatRow(quint64 baseAddr, const uint8_t* data, size_t len) {
    QString out;
    out.reserve(64);
    out += QStringLiteral("%1  ").arg(baseAddr, 16, 16, QLatin1Char('0'));
    // Hex column.
    for (int i = 0; i < kBytesPerRow; ++i) {
        if (i < (int)len) {
            out += QStringLiteral("%1 ")
                       .arg(data[i], 2, 16, QLatin1Char('0'));
        } else {
            out += QStringLiteral("   ");
        }
    }
    out += QStringLiteral(" ");
    // ASCII column.
    for (size_t i = 0; i < len; ++i) {
        const uint8_t b = data[i];
        out += (b >= 0x20 && b < 0x7f) ? QChar(b) : QChar('.');
    }
    return out;
}
}  // namespace

HexPane::HexPane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);

    m_headerLabel = new QLabel(QStringLiteral("Hex: (no binary loaded)"),
                                this);
    m_headerLabel->setStyleSheet(
        QStringLiteral("font-weight: bold; padding: 2px;"));
    layout->addWidget(m_headerLabel);

    m_textView = new QPlainTextEdit(this);
    m_textView->setReadOnly(true);
    m_textView->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_textView->setFont(
        QFontDatabase::systemFont(QFontDatabase::FixedFont));
    layout->addWidget(m_textView, 1);
}

HexPane::~HexPane() { closeBinary(); }

bool HexPane::openBinary(const QString& path) {
    closeBinary();
    if (path.isEmpty()) return false;
    const QByteArray u8 = path.toUtf8();
    m_mf = mapped_file_open(u8.constData());
    if (!m_mf) {
        m_headerLabel->setText(QStringLiteral("Hex: open failed"));
        m_textView->setPlainText(
            QStringLiteral("(failed to mmap %1)").arg(path));
        return false;
    }
    m_headerLabel->setText(
        QStringLiteral("Hex: %1 (%2 bytes)").arg(path).arg(m_mf->size));
    fillRange(0, kWindowBytes);
    return true;
}

void HexPane::closeBinary() {
    if (m_mf) {
        mapped_file_destroy(m_mf);
        m_mf = nullptr;
    }
    if (m_textView) m_textView->clear();
    if (m_headerLabel)
        m_headerLabel->setText(QStringLiteral("Hex: (no binary loaded)"));
}

void HexPane::fillRange(quint64 start, quint64 byteCount) {
    // Clamp window to actual file extents; align start down to a row
    // boundary so the leftmost addr column always reads cleanly.
    if (!m_mf || !m_mf->map || m_mf->size == 0) {
        if (m_textView) m_textView->setPlainText(QStringLiteral("(empty)"));
        m_windowStart = 0;
        m_windowBytes = 0;
        return;
    }
    if (start > m_mf->size) start = m_mf->size;
    start -= start % kBytesPerRow;
    quint64 end = start + byteCount;
    if (end > m_mf->size) end = m_mf->size;
    const quint64 bytes = (end > start) ? (end - start) : 0;
    const quint64 rows  = (bytes + kBytesPerRow - 1) / kBytesPerRow;

    QString out;
    out.reserve(static_cast<int>(rows) * 80);
    for (quint64 r = 0; r < rows; ++r) {
        const quint64 off = start + r * kBytesPerRow;
        const quint64 len = std::min<quint64>(kBytesPerRow, end - off);
        out += formatRow(off, m_mf->map + off, static_cast<size_t>(len));
        out += QLatin1Char('\n');
    }
    if (m_textView) m_textView->setPlainText(out);
    m_windowStart = start;
    m_windowBytes = bytes;
}

void HexPane::scrollToAddr(quint64 addr) {
    if (!m_textView || !m_mf || m_mf->size == 0) return;
    if (addr >= m_mf->size) return;

    // If addr is outside the current window, repaint a window centered
    // (roughly) on it. Otherwise just move the cursor inside the
    // existing window — keeps scrolling within a small range fast and
    // avoids flicker.
    const bool outside = (addr <  m_windowStart) ||
                         (addr >= m_windowStart + m_windowBytes);
    if (outside) {
        const quint64 half = kWindowBytes / 2;
        const quint64 newStart = (addr > half) ? (addr - half) : 0;
        fillRange(newStart, kWindowBytes);
    }
    // Resolve to a 0-based block index inside the rendered window.
    const quint64 relAddr = addr - m_windowStart;
    const int line = static_cast<int>(relAddr / kBytesPerRow);
    if (line < 0 || line >= m_textView->blockCount()) return;
    QTextCursor cur(m_textView->document()->findBlockByNumber(line));
    m_textView->setTextCursor(cur);
    m_textView->ensureCursorVisible();
}

quint64 HexPane::windowStartOffset() const { return m_windowStart; }
quint64 HexPane::windowByteCount()  const { return m_windowBytes; }

QString HexPane::currentText() const {
    return m_textView ? m_textView->toPlainText() : QString();
}

int HexPane::currentLineCount() const {
    return m_textView ? m_textView->blockCount() : 0;
}

quint64 HexPane::fileSize() const {
    return m_mf ? static_cast<quint64>(m_mf->size) : 0;
}

void HexPane::setMonospaceFontPointSize(int pt) {
    if (!m_textView) return;
    if (pt < 6)  pt = 6;
    if (pt > 32) pt = 32;
    QFont f = m_textView->font();
    f.setPointSize(pt);
    m_textView->setFont(f);
}

int HexPane::monospaceFontPointSize() const {
    return m_textView ? m_textView->font().pointSize() : 0;
}

}  // namespace aura::gui
