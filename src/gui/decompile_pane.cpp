// src/gui/decompile_pane.cpp — implementation.

#include "decompile_pane.h"

#include <QAction>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QMenu>
#include <QSettings>
#include <QPlainTextEdit>
#include <QSettings>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QVBoxLayout>

#include "code_syntax_highlighter.h"

namespace aura::gui {

namespace {

bool useKoreanUi() {
    QSettings s(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    return s.value(QStringLiteral("ui/language"), QStringLiteral("ko"))
        .toString() != QStringLiteral("en");
}

}  // namespace

DecompilePane::DecompilePane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);

    m_headerLabel = new QLabel(
        QStringLiteral("Decompile — (no function selected)"), this);
    m_headerLabel->setStyleSheet(
        QStringLiteral("font-weight: bold; padding: 2px;"));
    layout->addWidget(m_headerLabel);

    m_textView = new QPlainTextEdit(this);
    m_textView->setReadOnly(true);
    m_textView->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_textView->setFont(
        QFontDatabase::systemFont(QFontDatabase::FixedFont));
    new CodeSyntaxHighlighter(m_textView->document(),
                              CodeSyntaxHighlighter::Mode::CLike);
    m_textView->setPlainText(
        QStringLiteral("// 함수를 선택하면 디컴파일 결과가 여기에 표시됩니다."));
    layout->addWidget(m_textView, /*stretch=*/1);

    // Phase 11.3.7 (P2.F2 C4): cursor → addr → lineSelected emit.
    connect(m_textView, &QPlainTextEdit::cursorPositionChanged,
            this, &DecompilePane::onCursorPositionChanged);

    // Phase 11.3.9 (P2.F4 C2): right-click context menu (5 actions).
    m_textView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_textView, &QWidget::customContextMenuRequested,
            this, &DecompilePane::onContextMenuRequested);
}

void DecompilePane::showDecompile(quint64 funcAddr,
                                  const QString& backendLabel,
                                  const QString& text) {
    m_headerLabel->setText(
        QStringLiteral("Decompile — 0x%1   [%2]")
            .arg(funcAddr, 0, 16)
            .arg(backendLabel));
    m_textView->setPlainText(text);
    // Snapshot the cached line map for the function being shown so the
    // cursor handler can map clicks → addresses without a re-lookup.
    m_currentLineMap = m_cache.value(funcAddr).lineMap;
    // Phase 11.3.9: build the reverse index (addr → first matching
    // line) for selectLine() lookup. If multiple lines share an addr
    // (rare), the smaller line wins.
    m_currentAddrToLine.clear();
    for (auto it = m_currentLineMap.constBegin();
         it != m_currentLineMap.constEnd(); ++it) {
        const int line = it.key();
        const quint64 addr = it.value();
        auto existing = m_currentAddrToLine.constFind(addr);
        if (existing == m_currentAddrToLine.constEnd()
            || line < existing.value()) {
            m_currentAddrToLine.insert(addr, line);
        }
    }
}

void DecompilePane::onContextMenuRequested(const QPoint& pos) {
    if (!m_textView) return;
    // Resolve cursor-line addr from the cached line_map.
    QTextCursor cur = m_textView->cursorForPosition(pos);
    const int line1 = cur.blockNumber() + 1;  // 1-based per line_map
    const quint64 addr = m_currentLineMap.value(line1, 0);
    const bool ko = useKoreanUi();

    QMenu menu(this);
    QAction* jumpAct    = menu.addAction(
        ko ? QStringLiteral("디스어셈블리로 이동(&J)")
           : QStringLiteral("&Jump to disasm"));
    jumpAct->setEnabled(addr != 0);
    menu.addSeparator();
    QAction* renameAct  = menu.addAction(
        ko ? QStringLiteral("함수 이름 변경(&R)...")
           : QStringLiteral("&Rename function..."));
    QAction* resetAct   = menu.addAction(
        ko ? QStringLiteral("이름 초기화(&S)")
           : QStringLiteral("Re&set name"));
    QAction* xrefsAct   = menu.addAction(
        ko ? QStringLiteral("참조 찾기(&X)")
           : QStringLiteral("Find &xrefs"));
    xrefsAct->setEnabled(addr != 0);
    QAction* commentAct = menu.addAction(
        ko ? QStringLiteral("주석 추가(&C)...")
           : QStringLiteral("Add &comment..."));
    commentAct->setEnabled(addr != 0);
    menu.addSeparator();
    QAction* substituteStringsAct = menu.addAction(
        ko ? QStringLiteral("문자열 주소 자동 치환")
           : QStringLiteral("Auto-substitute string addresses"));
    substituteStringsAct->setCheckable(true);
    QSettings settings(QStringLiteral("AURA"), QStringLiteral("aura-gui"));
    substituteStringsAct->setChecked(
        settings.value(QStringLiteral("decompile/autoSubstituteStringAddresses"),
                       true).toBool());

    QAction* chosen = menu.exec(m_textView->mapToGlobal(pos));
    if (!chosen) return;

    if      (chosen == jumpAct)    emit contextJumpToDisasm(addr);
    else if (chosen == renameAct)  emit contextRename();
    else if (chosen == resetAct)   emit contextResetName();
    else if (chosen == xrefsAct)   emit contextFindXrefs(addr);
    else if (chosen == commentAct) emit contextAddComment(addr);
    else if (chosen == substituteStringsAct)
        emit contextToggleStringSubstitution();
}

void DecompilePane::selectLine(quint64 addr) {
    if (!m_textView) return;
    auto it = m_currentAddrToLine.constFind(addr);
    if (it == m_currentAddrToLine.constEnd()) return;
    const int line1 = it.value();  // 1-based per AuraRizinDecompileLineMap
    const int blockIdx = line1 - 1;
    if (blockIdx < 0) return;
    // Block our own cursorPositionChanged → lineSelected echo so the
    // bidirectional sync doesn't loop.
    QSignalBlocker block(m_textView);
    QTextCursor cur(m_textView->document()->findBlockByNumber(blockIdx));
    m_textView->setTextCursor(cur);
    m_textView->ensureCursorVisible();
}

void DecompilePane::onCursorPositionChanged() {
    if (!m_textView || m_currentLineMap.isEmpty()) return;
    // QTextCursor.blockNumber() is 0-based; line_map keys are 1-based
    // (mirrors AuraRizinDecompileLineMap.line).
    const int line1 = m_textView->textCursor().blockNumber() + 1;
    auto it = m_currentLineMap.constFind(line1);
    if (it == m_currentLineMap.constEnd()) return;
    emit lineSelected(it.value());
}

DecompileLineAddrMap DecompilePane::cachedLineMap(quint64 funcAddr) const {
    return m_cache.value(funcAddr).lineMap;
}

void DecompilePane::showPlaceholder(const QString& message) {
    m_headerLabel->setText(QStringLiteral("Decompile"));
    m_textView->setPlainText(message);
}

bool DecompilePane::hasCached(quint64 funcAddr) const {
    return m_cache.contains(funcAddr);
}

QString DecompilePane::cachedText(quint64 funcAddr) const {
    return m_cache.value(funcAddr).text;
}

QString DecompilePane::cachedBackend(quint64 funcAddr) const {
    return m_cache.value(funcAddr).backendLabel;
}

void DecompilePane::cache(quint64 funcAddr, const QString& backendLabel,
                          const QString& text) {
    m_cache.insert(funcAddr, Entry{backendLabel, text, {}});
}

void DecompilePane::cache(quint64 funcAddr, const QString& backendLabel,
                          const QString& text,
                          const DecompileLineAddrMap& lineMap) {
    m_cache.insert(funcAddr, Entry{backendLabel, text, lineMap});
}

void DecompilePane::clearCache() {
    m_cache.clear();
}

QString DecompilePane::currentText() const {
    return m_textView->toPlainText();
}

void DecompilePane::setMonospaceFontPointSize(int pt) {
    if (pt < 6)  pt = 6;
    if (pt > 32) pt = 32;
    QFont f = m_textView->font();
    f.setPointSize(pt);
    m_textView->setFont(f);
}

int DecompilePane::monospaceFontPointSize() const {
    return m_textView->font().pointSize();
}

}  // namespace aura::gui
