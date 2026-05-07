// src/gui/disasm_pane.cpp — implementation.

#include "disasm_pane.h"

#include <QColor>
#include <QFont>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "code_syntax_highlighter.h"
#include "disasm_flow_gutter.h"

namespace aura::gui {

DisasmPane::DisasmPane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);

    m_headerLabel = new QLabel(QStringLiteral("Disassembly: (no function)"),
                               this);
    m_headerLabel->setStyleSheet(QStringLiteral(
        "QLabel { color: #aaaaaa; padding: 2px; font-weight: bold; }"));
    layout->addWidget(m_headerLabel);

    // Phase 11.6 T1 C2: tabbed view — structured table + arrow text.
    m_tabs = new QTabWidget(this);

    m_textView = new QPlainTextEdit(m_tabs);
    m_textView->setReadOnly(true);
    m_textView->setFont(
        QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_textView->setLineWrapMode(QPlainTextEdit::NoWrap);
    new CodeSyntaxHighlighter(m_textView->document(),
                              CodeSyntaxHighlighter::Mode::Disasm);

    // Phase 11.6 T2 C3: wrap text view with the flow gutter on its
    // left so arrows are painted in column with the disasm lines.
    auto* structContainer = new QWidget(m_tabs);
    auto* structLayout    = new QHBoxLayout(structContainer);
    structLayout->setContentsMargins(0, 0, 0, 0);
    structLayout->setSpacing(0);
    m_flowGutter = new DisasmFlowGutter(m_textView, structContainer);
    structLayout->addWidget(m_flowGutter);
    structLayout->addWidget(m_textView, 1);
    structContainer->setLayout(structLayout);
    m_tabs->addTab(structContainer, QStringLiteral("Structured"));

    m_arrowView = new QPlainTextEdit(m_tabs);
    m_arrowView->setReadOnly(true);
    m_arrowView->setFont(
        QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_arrowView->setLineWrapMode(QPlainTextEdit::NoWrap);
    new CodeSyntaxHighlighter(m_arrowView->document(),
                              CodeSyntaxHighlighter::Mode::Disasm);
    m_arrowView->setPlainText(
        QStringLiteral("// rizin pdf (asm.lines flow arrows) appears here "
                       "when a function is selected."));
    m_tabs->addTab(m_arrowView, QStringLiteral("With arrows"));

    layout->addWidget(m_tabs, 1);

    setLayout(layout);
    showPlaceholder(QStringLiteral("선택된 함수 없음"));

    // Phase 11.3.9 (P2.F4 C1): cursor → addr → instructionSelected.
    connect(m_textView, &QPlainTextEdit::cursorPositionChanged,
            this, &DisasmPane::onCursorPositionChanged);

    // Phase 11.6 T3: click on a flow arrow in the gutter → jump the
    // text-view cursor to the destination instruction. selectInstruction
    // also emits instructionSelected, which keeps cross-pane sync
    // (DecompilePane / CFG / Hex) coherent for free.
    connect(m_flowGutter, &DisasmFlowGutter::arrowClicked,
            this, &DisasmPane::selectInstruction);
}

void DisasmPane::onCursorPositionChanged() {
    if (!m_textView) return;
    const int line = m_textView->textCursor().blockNumber();
    if (line < 0 || line >= m_lineToAddr.size()) return;
    emit instructionSelected(m_lineToAddr[line]);
}

void DisasmPane::showDisasm(quint64 funcAddr,
                            const QVector<GuiInstructionRecord>& ins) {
    cache(funcAddr, ins);
    m_headerLabel->setText(
        QStringLiteral("Disassembly: 0x%1  (%2 instructions)")
            .arg(funcAddr, 0, 16)
            .arg(ins.size()));

    m_addrToLine.clear();
    m_lineToAddr.clear();
    m_lineToAddr.reserve(ins.size());
    QString out;
    out.reserve(ins.size() * 64);
    for (int i = 0; i < ins.size(); ++i) {
        const auto& r = ins[i];
        // Format: addr  bytes  mnemonic op_str
        // bytes column padded to a stable width so columns align.
        QString line = QStringLiteral("0x%1  %2  %3 %4\n")
                           .arg(r.addr, 0, 16)
                           .arg(r.bytes, -16, QLatin1Char(' '))
                           .arg(r.mnemonic, -8, QLatin1Char(' '))
                           .arg(r.opStr);
        out.append(line);
        m_addrToLine.insert(r.addr, i);
        m_lineToAddr.push_back(r.addr);
    }
    m_textView->setPlainText(out);

    // Phase 11.6 T2 C3: re-compute flow arrows + lane assignment for
    // the new function and push them to the gutter so it can paint
    // in lock-step with the freshly-rendered text.
    if (m_flowGutter) {
        QVector<GuiFlowArrow> arrows = MainWindow::computeFlowArrows(ins);
        MainWindow::assignFlowArrowLanes(arrows, m_flowGutter->maxLanes());
        m_flowGutter->setArrows(arrows);
    }
}

void DisasmPane::selectInstruction(quint64 addr) {
    if (!m_textView) return;
    auto it = m_addrToLine.constFind(addr);
    if (it == m_addrToLine.constEnd()) return;
    const int line = it.value();
    // Phase 11.3.9 (P2.F4 C1): block self-emit so a slot-driven cursor
    // move (e.g. from DecompilePane.lineSelected) doesn't echo back as
    // an instructionSelected.
    QSignalBlocker block(m_textView);
    QTextCursor cur(m_textView->document()->findBlockByNumber(line));
    m_textView->setTextCursor(cur);
    m_textView->ensureCursorVisible();

    // Highlight the line via ExtraSelection (yellow background).
    QList<QTextEdit::ExtraSelection> sels;
    QTextEdit::ExtraSelection sel;
    sel.format.setBackground(QColor(80, 80, 0));  // muted gold
    sel.format.setProperty(QTextFormat::FullWidthSelection, true);
    sel.cursor = cur;
    sel.cursor.clearSelection();
    sels.append(sel);
    m_textView->setExtraSelections(sels);
}

int DisasmPane::currentCursorLine() const {
    if (!m_textView) return -1;
    return m_textView->textCursor().blockNumber();
}

bool DisasmPane::hasCached(quint64 funcAddr) const {
    return m_cache.contains(funcAddr);
}

QVector<GuiInstructionRecord> DisasmPane::cached(quint64 funcAddr) const {
    return m_cache.value(funcAddr);
}

QString DisasmPane::cachedArrowText(quint64 funcAddr) const {
    return m_arrowCache.value(funcAddr);
}

void DisasmPane::cache(quint64 funcAddr,
                       const QVector<GuiInstructionRecord>& ins) {
    m_cache.insert(funcAddr, ins);
}

void DisasmPane::setArrowText(quint64 funcAddr, const QString& text) {
    m_arrowCache.insert(funcAddr, text);
    if (!m_arrowView) return;
    if (text.isEmpty()) {
        m_arrowView->setPlainText(
            QStringLiteral("// (no annotated text — older Rizin or "
                           "pdf frame missing)"));
    } else {
        m_arrowView->setPlainText(text);
        // Move cursor to top so user sees the function header first.
        QTextCursor c = m_arrowView->textCursor();
        c.movePosition(QTextCursor::Start);
        m_arrowView->setTextCursor(c);
    }
}

void DisasmPane::clearCache() {
    m_cache.clear();
    m_arrowCache.clear();
}

void DisasmPane::showPlaceholder(const QString& message) {
    m_headerLabel->setText(QStringLiteral("Disassembly"));
    m_textView->setPlainText(message);
    if (m_flowGutter) m_flowGutter->clearArrows();
}

QString DisasmPane::currentText() const {
    return m_textView ? m_textView->toPlainText() : QString();
}

int DisasmPane::currentLineCount() const {
    return m_textView ? m_textView->blockCount() : 0;
}

void DisasmPane::setMonospaceFontPointSize(int pt) {
    if (!m_textView) return;
    if (pt < 6)  pt = 6;
    if (pt > 32) pt = 32;
    QFont f = m_textView->font();
    f.setPointSize(pt);
    m_textView->setFont(f);
    // Phase 11.6 T1 C2: keep arrow view font in lockstep so the user
    // sees one zoom level across both tabs.
    if (m_arrowView) {
        QFont fa = m_arrowView->font();
        fa.setPointSize(pt);
        m_arrowView->setFont(fa);
    }
}

int DisasmPane::monospaceFontPointSize() const {
    return m_textView ? m_textView->font().pointSize() : 0;
}

}  // namespace aura::gui
