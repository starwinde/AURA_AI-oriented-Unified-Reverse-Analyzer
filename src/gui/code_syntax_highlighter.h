// src/gui/code_syntax_highlighter.h

#pragma once

#include <QColor>
#include <QSet>
#include <QString>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

namespace aura::gui {

class CodeSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    enum class Mode {
        CLike,
        Disasm,
    };

    explicit CodeSyntaxHighlighter(QTextDocument* doc, Mode mode);

    static bool isCKeyword(const QString& word);
    static bool isDisasmMnemonic(const QString& word);
    static bool looksLikeAddress(const QString& word);
    static QColor colorForRole(const QString& role);

protected:
    void highlightBlock(const QString& text) override;

private:
    void highlightCBlock(const QString& text);
    void highlightDisasmBlock(const QString& text);
    void applyRegex(const QString& text,
                    const class QRegularExpression& re,
                    const QTextCharFormat& fmt);
    QTextCharFormat format(const QString& role) const;

    Mode m_mode;
};

}  // namespace aura::gui
