// src/gui/full_disasm_pane.cpp

#include "full_disasm_pane.h"

#include <QColor>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QStringList>
#include <QTabWidget>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextEdit>
#include <QVBoxLayout>

#include "code_syntax_highlighter.h"
#include "disasm_flow_gutter.h"

#include <limits>

namespace aura::gui {

namespace {
bool parseLineAddress(const QString& line, quint64* out) {
    if (!out) return false;
    const int pos = line.indexOf(QStringLiteral("0x"));
    if (pos < 0) return false;
    int end = pos + 2;
    while (end < line.size()) {
        const QChar ch = line.at(end);
        if (!ch.isDigit() &&
            !(ch >= QLatin1Char('a') && ch <= QLatin1Char('f')) &&
            !(ch >= QLatin1Char('A') && ch <= QLatin1Char('F'))) {
            break;
        }
        ++end;
    }
    if (end <= pos + 2) return false;
    bool ok = false;
    const quint64 addr = line.mid(pos + 2, end - pos - 2).toULongLong(&ok, 16);
    if (!ok) return false;
    *out = addr;
    return true;
}

QString classifyLine(const QString& line) {
    const QString t = line.trimmed();
    quint64 ignored = 0;
    if (t.isEmpty()) return QStringLiteral("blank");
    if (t.startsWith(QStringLiteral(";--"))) return QStringLiteral("label");
    if (t.startsWith(QLatin1Char(';'))) return QStringLiteral("comment");
    if (t.contains(QStringLiteral("invalid"), Qt::CaseInsensitive)) {
        return QStringLiteral("invalid");
    }
    if (parseLineAddress(line, &ignored)) return QStringLiteral("code/data");
    return QStringLiteral("meta");
}
}  // namespace

FullDisasmPane::FullDisasmPane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);

    m_headerLabel = new QLabel(QStringLiteral("Full Disassembly"), this);
    m_headerLabel->setStyleSheet(QStringLiteral(
        "QLabel { color: #aaaaaa; padding: 2px; font-weight: bold; }"));
    layout->addWidget(m_headerLabel);

    m_tabs = new QTabWidget(this);

    m_textView = new QPlainTextEdit(m_tabs);
    m_textView->setObjectName(QStringLiteral("fullDisasmStructuredText"));
    m_textView->setReadOnly(true);
    m_textView->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_textView->setLineWrapMode(QPlainTextEdit::NoWrap);
    new CodeSyntaxHighlighter(m_textView->document(),
                              CodeSyntaxHighlighter::Mode::Disasm);
    connect(m_textView->verticalScrollBar(), &QScrollBar::valueChanged,
            this, &FullDisasmPane::onStructuredScrollChanged);

    auto* structContainer = new QWidget(m_tabs);
    auto* structLayout = new QHBoxLayout(structContainer);
    structLayout->setContentsMargins(0, 0, 0, 0);
    structLayout->setSpacing(0);
    m_flowGutter = new DisasmFlowGutter(m_textView, structContainer);
    structLayout->addWidget(m_flowGutter);
    structLayout->addWidget(m_textView, 1);
    structContainer->setLayout(structLayout);
    m_tabs->addTab(structContainer, QStringLiteral("Structured"));

    m_arrowView = new QPlainTextEdit(m_tabs);
    m_arrowView->setObjectName(QStringLiteral("fullDisasmArrowText"));
    m_arrowView->setReadOnly(true);
    m_arrowView->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_arrowView->setLineWrapMode(QPlainTextEdit::NoWrap);
    new CodeSyntaxHighlighter(m_arrowView->document(),
                              CodeSyntaxHighlighter::Mode::Disasm);
    m_tabs->addTab(m_arrowView, QStringLiteral("With arrows"));

    layout->addWidget(m_tabs, 1);

    showPlaceholder(QStringLiteral("// 분석 후 전체 디스어셈블리가 여기에 표시됩니다."));
}

void FullDisasmPane::setFunctionLabels(
    const QHash<quint64, QString>& labels) {
    m_functionLabels = labels;
}

QString FullDisasmPane::currentText() const {
    return m_textView ? m_textView->toPlainText() : QString();
}

quint64 FullDisasmPane::nextAddressAfterLoaded() const {
    quint64 next = 0;
    for (auto it = m_addrToEnd.constBegin(); it != m_addrToEnd.constEnd();
         ++it) {
        if (it.value() > next) next = it.value();
    }
    if (next != 0) return next;
    return m_loadedMaxAddr == std::numeric_limits<quint64>::max()
        ? m_loadedMaxAddr
        : m_loadedMaxAddr + 1;
}

void FullDisasmPane::onStructuredScrollChanged(int value) {
    if (!m_textView || m_loadedMaxAddr == 0) return;
    auto* bar = m_textView->verticalScrollBar();
    if (!bar || bar->maximum() <= 0) return;
    if (value < bar->maximum() - 2) return;

    const quint64 request = nextAddressAfterLoaded();
    if (request == 0 || request == m_lastScrollLoadRequest) return;
    m_lastScrollLoadRequest = request;
    emit addressOutsideLoadedRange(request);
}

bool FullDisasmPane::containsAddress(quint64 addr) const {
    return addr != 0
        && m_loadedMinAddr != 0
        && addr >= m_loadedMinAddr
        && addr <= m_loadedMaxAddr;
}

void FullDisasmPane::setStartAddress(quint64 addr) {
    if (addr == 0 || !m_textView) return;
    m_currentAddr = addr;
    auto it = m_addrToLine.constFind(addr);
    if (it == m_addrToLine.constEnd()) {
        quint64 bestAddr = 0;
        int bestLine = -1;
        for (auto span = m_addrToEnd.constBegin();
             span != m_addrToEnd.constEnd(); ++span) {
            if (span.key() <= addr && addr < span.value() &&
                span.key() >= bestAddr) {
                bestAddr = span.key();
                bestLine = m_addrToLine.value(span.key(), -1);
            }
        }
        if (bestLine < 0) {
            emit addressOutsideLoadedRange(addr);
            return;
        }
        it = m_addrToLine.constFind(bestAddr);
    }

    QTextCursor cur(m_textView->document()->findBlockByNumber(it.value()));
    m_textView->setTextCursor(cur);
    m_textView->ensureCursorVisible();

    QList<QTextEdit::ExtraSelection> sels;
    QTextEdit::ExtraSelection sel;
    sel.format.setBackground(QColor(35, 80, 120));
    sel.format.setProperty(QTextFormat::FullWidthSelection, true);
    sel.cursor = cur;
    sel.cursor.clearSelection();
    sels.append(sel);
    m_textView->setExtraSelections(sels);
}

void FullDisasmPane::showText(quint64 baseAddr,
                              quint64 byteCount,
                              const QString& text) {
    m_currentAddr = baseAddr;
    m_headerLabel->setText(
        QStringLiteral("Full Disassembly: 0x%1  (%2 bytes)")
            .arg(baseAddr, 0, 16)
            .arg(byteCount));
    m_textView->setPlainText(text);
    m_lastScrollLoadRequest = 0;
    if (m_flowGutter) m_flowGutter->clearArrows();
    m_addrToEnd.clear();
    rebuildAddressIndex(text);
    updateLoadedRangeFromIndex();

    QTextCursor c = m_textView->textCursor();
    c.movePosition(QTextCursor::Start);
    m_textView->setTextCursor(c);
}

void FullDisasmPane::showInstructions(
    quint64 baseAddr,
    int requestedCount,
    const QVector<GuiInstructionRecord>& ins) {
    m_currentAddr = baseAddr;
    m_addrToLine.clear();
    m_addrToEnd.clear();
    m_headerLabel->setText(
        QStringLiteral("Full Disassembly: 0x%1  (%2/%3 instructions)")
            .arg(baseAddr, 0, 16)
            .arg(ins.size())
            .arg(requestedCount));

    QString out;
    out.reserve(ins.size() * 80);
    for (int i = 0; i < ins.size(); ++i) {
        const auto& r = ins[i];
        m_addrToLine.insert(r.addr, i);
        if (r.size > 0) {
            m_addrToEnd.insert(r.addr, r.addr + r.size);
        }
        out.append(QStringLiteral("0x%1  %2  %3 %4\n")
                       .arg(r.addr, 0, 16)
                       .arg(r.bytes, -16, QLatin1Char(' '))
                       .arg(r.mnemonic, -8, QLatin1Char(' '))
                       .arg(r.opStr));
    }
    m_textView->setPlainText(out);
    m_lastScrollLoadRequest = 0;
    updateLoadedRangeFromIndex();
    if (m_flowGutter) {
        QVector<GuiFlowArrow> arrows = MainWindow::computeFlowArrows(ins);
        MainWindow::assignFlowArrowLanes(arrows, m_flowGutter->maxLanes());
        m_flowGutter->setArrows(arrows);
    }
    QTextCursor c = m_textView->textCursor();
    c.movePosition(QTextCursor::Start);
    m_textView->setTextCursor(c);
}

void FullDisasmPane::showMixedListing(
    quint64 baseAddr,
    int requestedCount,
    const QString& text,
    const QVector<GuiInstructionRecord>& ins) {
    m_currentAddr = baseAddr;
    m_addrToLine.clear();
    m_addrToEnd.clear();
    m_headerLabel->setText(
        QStringLiteral("Full Disassembly: 0x%1  (%2 instructions, mixed)")
            .arg(baseAddr, 0, 16)
            .arg(requestedCount));

    const QStringList lines = text.split(QLatin1Char('\n'));
    QString out;
    out.reserve(text.size() + lines.size() * 12 + ins.size() * 80);
    for (int i = 0; i < lines.size(); ++i) {
        quint64 addr = 0;
        if (parseLineAddress(lines.at(i), &addr) &&
            !m_addrToLine.contains(addr)) {
            m_addrToLine.insert(addr, i);
        }
        out.append(formatMixedListingLine(lines.at(i)));
        out.append(QLatin1Char('\n'));
    }
    int lineNo = lines.size();
    for (const auto& r : ins) {
        if (r.size > 0) {
            m_addrToEnd.insert(r.addr, r.addr + r.size);
        }
        if (m_addrToLine.contains(r.addr)) continue;
        m_addrToLine.insert(r.addr, lineNo++);
        const QString line = QStringLiteral("0x%1  %2  %3 %4")
                                 .arg(r.addr, 0, 16)
                                 .arg(r.bytes, -16, QLatin1Char(' '))
                                 .arg(r.mnemonic, -8, QLatin1Char(' '))
                                 .arg(r.opStr);
        out.append(formatMixedListingLine(line));
        out.append(QLatin1Char('\n'));
    }
    m_textView->setPlainText(out);
    m_lastScrollLoadRequest = 0;
    updateLoadedRangeFromIndex();

    if (m_flowGutter) {
        QVector<GuiFlowArrow> rawArrows = MainWindow::computeFlowArrows(ins);
        QVector<GuiFlowArrow> arrows;
        arrows.reserve(rawArrows.size());
        for (auto a : rawArrows) {
            const int src = m_addrToLine.value(a.srcAddr, -1);
            const int dst = m_addrToLine.value(a.dstAddr, -1);
            if (src < 0 || dst < 0) continue;
            a.srcLine = src;
            a.dstLine = dst;
            a.direction = (dst > src) ? +1 : (dst < src ? -1 : 0);
            arrows.push_back(a);
        }
        MainWindow::assignFlowArrowLanes(arrows, m_flowGutter->maxLanes());
        m_flowGutter->setArrows(arrows);
    }

    QTextCursor c = m_textView->textCursor();
    c.movePosition(QTextCursor::Start);
    m_textView->setTextCursor(c);
}

void FullDisasmPane::setArrowText(quint64 baseAddr, const QString& text) {
    if (!m_arrowView) return;
    if (text.isEmpty()) {
        m_arrowView->setPlainText(
            QStringLiteral("// (no annotated text — pD frame missing)"));
        return;
    }
    m_arrowView->setPlainText(text);
    QTextCursor c = m_arrowView->textCursor();
    c.movePosition(QTextCursor::Start);
    m_arrowView->setTextCursor(c);
    Q_UNUSED(baseAddr);
}

QString FullDisasmPane::formatMixedListingLine(const QString& line) const {
    const QString kind = classifyLine(line);
    return QStringLiteral("%1  %2").arg(kind, -9, QLatin1Char(' ')).arg(line);
}

void FullDisasmPane::rebuildAddressIndex(const QString& text) {
    m_addrToLine.clear();
    const QStringList lines = text.split(QLatin1Char('\n'));
    for (int i = 0; i < lines.size(); ++i) {
        quint64 addr = 0;
        if (parseLineAddress(lines.at(i), &addr) &&
            !m_addrToLine.contains(addr)) {
            m_addrToLine.insert(addr, i);
        }
    }
}

void FullDisasmPane::updateLoadedRangeFromIndex() {
    m_loadedMinAddr = 0;
    m_loadedMaxAddr = 0;
    for (auto it = m_addrToLine.constBegin(); it != m_addrToLine.constEnd();
         ++it) {
        if (it.key() == 0) continue;
        if (m_loadedMinAddr == 0 || it.key() < m_loadedMinAddr) {
            m_loadedMinAddr = it.key();
        }
        if (it.key() > m_loadedMaxAddr) {
            m_loadedMaxAddr = it.key();
        }
    }
}

void FullDisasmPane::showPlaceholder(const QString& message) {
    if (m_headerLabel) m_headerLabel->setText(QStringLiteral("Full Disassembly"));
    if (m_textView) m_textView->setPlainText(message);
    if (m_arrowView) m_arrowView->setPlainText(message);
    if (m_flowGutter) m_flowGutter->clearArrows();
    m_addrToLine.clear();
    m_addrToEnd.clear();
    m_loadedMinAddr = 0;
    m_loadedMaxAddr = 0;
    m_lastScrollLoadRequest = 0;
}

}  // namespace aura::gui
