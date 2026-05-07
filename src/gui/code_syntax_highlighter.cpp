// src/gui/code_syntax_highlighter.cpp

#include "code_syntax_highlighter.h"

#include <QRegularExpression>
#include <QTextDocument>

namespace aura::gui {

namespace {

QTextCharFormat makeFormat(const QColor& fg, bool bold = false) {
    QTextCharFormat f;
    f.setForeground(fg);
    if (bold) f.setFontWeight(QFont::Bold);
    return f;
}

const QSet<QString>& cKeywords() {
    static const QSet<QString> words = {
        QStringLiteral("auto"), QStringLiteral("break"), QStringLiteral("case"),
        QStringLiteral("char"), QStringLiteral("const"), QStringLiteral("continue"),
        QStringLiteral("default"), QStringLiteral("do"), QStringLiteral("double"),
        QStringLiteral("else"), QStringLiteral("enum"), QStringLiteral("extern"),
        QStringLiteral("float"), QStringLiteral("for"), QStringLiteral("goto"),
        QStringLiteral("if"), QStringLiteral("inline"), QStringLiteral("int"),
        QStringLiteral("long"), QStringLiteral("register"), QStringLiteral("restrict"),
        QStringLiteral("return"), QStringLiteral("short"), QStringLiteral("signed"),
        QStringLiteral("sizeof"), QStringLiteral("static"), QStringLiteral("struct"),
        QStringLiteral("switch"), QStringLiteral("typedef"), QStringLiteral("union"),
        QStringLiteral("unsigned"), QStringLiteral("void"), QStringLiteral("volatile"),
        QStringLiteral("while"), QStringLiteral("bool"), QStringLiteral("true"),
        QStringLiteral("false"), QStringLiteral("undefined"), QStringLiteral("undefined1"),
        QStringLiteral("undefined2"), QStringLiteral("undefined4"), QStringLiteral("undefined8"),
        QStringLiteral("int8_t"), QStringLiteral("int16_t"), QStringLiteral("int32_t"),
        QStringLiteral("int64_t"), QStringLiteral("uint8_t"), QStringLiteral("uint16_t"),
        QStringLiteral("uint32_t"), QStringLiteral("uint64_t"), QStringLiteral("size_t"),
        QStringLiteral("code"),
    };
    return words;
}

const QSet<QString>& disasmMnemonics() {
    static const QSet<QString> words = {
        QStringLiteral("adc"), QStringLiteral("add"), QStringLiteral("and"),
        QStringLiteral("call"), QStringLiteral("cbw"), QStringLiteral("clc"),
        QStringLiteral("cli"), QStringLiteral("cmp"), QStringLiteral("cmova"),
        QStringLiteral("cmovae"), QStringLiteral("cmovb"), QStringLiteral("cmovbe"),
        QStringLiteral("cmove"), QStringLiteral("cmovne"), QStringLiteral("dec"),
        QStringLiteral("div"), QStringLiteral("enter"), QStringLiteral("hlt"),
        QStringLiteral("idiv"), QStringLiteral("imul"), QStringLiteral("in"),
        QStringLiteral("inc"), QStringLiteral("int"), QStringLiteral("ja"),
        QStringLiteral("jae"), QStringLiteral("jb"), QStringLiteral("jbe"),
        QStringLiteral("je"), QStringLiteral("jg"), QStringLiteral("jge"),
        QStringLiteral("jl"), QStringLiteral("jle"), QStringLiteral("jmp"),
        QStringLiteral("jne"), QStringLiteral("jno"), QStringLiteral("jns"),
        QStringLiteral("jo"), QStringLiteral("js"), QStringLiteral("lea"),
        QStringLiteral("leave"), QStringLiteral("loop"), QStringLiteral("mov"),
        QStringLiteral("movsx"), QStringLiteral("movsxd"), QStringLiteral("movzx"),
        QStringLiteral("mul"), QStringLiteral("neg"), QStringLiteral("nop"),
        QStringLiteral("not"), QStringLiteral("or"), QStringLiteral("out"),
        QStringLiteral("pop"), QStringLiteral("push"), QStringLiteral("ret"),
        QStringLiteral("rol"), QStringLiteral("ror"), QStringLiteral("sal"),
        QStringLiteral("sar"), QStringLiteral("sbb"), QStringLiteral("seta"),
        QStringLiteral("sete"), QStringLiteral("setne"), QStringLiteral("shl"),
        QStringLiteral("shr"), QStringLiteral("stc"), QStringLiteral("sub"),
        QStringLiteral("test"), QStringLiteral("xchg"), QStringLiteral("xor"),
        QStringLiteral("invalid"),
    };
    return words;
}

}  // namespace

CodeSyntaxHighlighter::CodeSyntaxHighlighter(QTextDocument* doc, Mode mode)
    : QSyntaxHighlighter(doc), m_mode(mode) {}

bool CodeSyntaxHighlighter::isCKeyword(const QString& word) {
    return cKeywords().contains(word);
}

bool CodeSyntaxHighlighter::isDisasmMnemonic(const QString& word) {
    return disasmMnemonics().contains(word.toLower());
}

bool CodeSyntaxHighlighter::looksLikeAddress(const QString& word) {
    static const QRegularExpression re(
        QStringLiteral(R"(^0x[0-9a-fA-F]{4,16}$)"));
    return re.match(word).hasMatch();
}

QColor CodeSyntaxHighlighter::colorForRole(const QString& role) {
    if (role == QLatin1String("address")) return QColor(0xff, 0xa6, 0x57);
    if (role == QLatin1String("mnemonic")) return QColor(0x5e, 0xd1, 0xc4);
    if (role == QLatin1String("register")) return QColor(0x9c, 0xc9, 0xff);
    if (role == QLatin1String("keyword")) return QColor(0x83, 0xb8, 0xff);
    if (role == QLatin1String("type")) return QColor(0x7e, 0xd9, 0x8c);
    if (role == QLatin1String("number")) return QColor(0xff, 0xc7, 0x77);
    if (role == QLatin1String("string")) return QColor(0xce, 0xe8, 0x7a);
    if (role == QLatin1String("comment")) return QColor(0x7f, 0x8c, 0x8d);
    if (role == QLatin1String("label")) return QColor(0xd6, 0xa8, 0xff);
    if (role == QLatin1String("invalid")) return QColor(0xff, 0x6b, 0x6b);
    return QColor(0xd8, 0xdc, 0xe3);
}

void CodeSyntaxHighlighter::highlightBlock(const QString& text) {
    if (m_mode == Mode::CLike) {
        highlightCBlock(text);
    } else {
        highlightDisasmBlock(text);
    }
}

QTextCharFormat CodeSyntaxHighlighter::format(const QString& role) const {
    const bool bold = role == QLatin1String("address")
                   || role == QLatin1String("mnemonic")
                   || role == QLatin1String("keyword")
                   || role == QLatin1String("label");
    return makeFormat(colorForRole(role), bold);
}

void CodeSyntaxHighlighter::applyRegex(const QString& text,
                                       const QRegularExpression& re,
                                       const QTextCharFormat& fmt) {
    auto it = re.globalMatch(text);
    while (it.hasNext()) {
        const auto m = it.next();
        setFormat(m.capturedStart(), m.capturedLength(), fmt);
    }
}

void CodeSyntaxHighlighter::highlightCBlock(const QString& text) {
    static const QRegularExpression strings(
        QStringLiteral(R"("([^"\\]|\\.)*"|'([^'\\]|\\.)*')"));
    static const QRegularExpression numbers(
        QStringLiteral(R"(\b(0x[0-9a-fA-F]+|\d+)\b)"));
    static const QRegularExpression functions(
        QStringLiteral(R"(\b[A-Za-z_][A-Za-z0-9_]*(?=\s*\())"));
    static const QRegularExpression comments(QStringLiteral(R"(//.*$)"));
    static const QRegularExpression words(
        QStringLiteral(R"(\b[A-Za-z_][A-Za-z0-9_]*\b)"));

    applyRegex(text, numbers, format(QStringLiteral("number")));
    applyRegex(text, functions, format(QStringLiteral("label")));

    auto it = words.globalMatch(text);
    while (it.hasNext()) {
        const auto m = it.next();
        const QString w = m.captured();
        if (isCKeyword(w)) {
            const QString role =
                w.endsWith(QStringLiteral("_t")) || w.startsWith(QStringLiteral("uint"))
                    || w.startsWith(QStringLiteral("int"))
                    || w == QLatin1String("void")
                    || w == QLatin1String("char")
                    ? QStringLiteral("type")
                    : QStringLiteral("keyword");
            setFormat(m.capturedStart(), m.capturedLength(), format(role));
        }
    }

    applyRegex(text, strings, format(QStringLiteral("string")));

    const auto c = comments.match(text);
    if (c.hasMatch()) {
        setFormat(c.capturedStart(), c.capturedLength(),
                  format(QStringLiteral("comment")));
    }
}

void CodeSyntaxHighlighter::highlightDisasmBlock(const QString& text) {
    static const QRegularExpression comments(QStringLiteral(R"(;.*$)"));
    static const QRegularExpression addresses(
        QStringLiteral(R"(\b0x[0-9a-fA-F]{4,16}\b)"));
    static const QRegularExpression registers(
        QStringLiteral(R"(\b([er]?[abcd]x|[abcd][hl]|[er]?(si|di|bp|sp)|r([0-9]|1[0-5])[bwd]?|xmm\d+|ymm\d+|zmm\d+|rip|eip|cs|ds|es|fs|gs|ss)\b)"),
        QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression numbers(
        QStringLiteral(R"(\b(0x[0-9a-fA-F]+|\d+)\b)"));
    static const QRegularExpression mnemonic(
        QStringLiteral(R"(^\s*(?:[a-z/ -]+\s+)?(?:0x[0-9a-fA-F]+\s+)?(?:[0-9a-fA-F]{2}\s+)*([A-Za-z][A-Za-z0-9.]*))"));

    const QString trimmed = text.trimmed();
    if (trimmed.startsWith(QStringLiteral(";--"))) {
        setFormat(0, text.size(), format(QStringLiteral("label")));
        return;
    }
    if (trimmed.contains(QStringLiteral("invalid"), Qt::CaseInsensitive)) {
        setFormat(0, text.size(), format(QStringLiteral("invalid")));
        return;
    }

    applyRegex(text, numbers, format(QStringLiteral("number")));
    applyRegex(text, addresses, format(QStringLiteral("address")));
    applyRegex(text, registers, format(QStringLiteral("register")));

    const auto m = mnemonic.match(text);
    if (m.hasMatch()) {
        const QString op = m.captured(1).toLower();
        if (isDisasmMnemonic(op)) {
            setFormat(m.capturedStart(1), m.capturedLength(1),
                      format(QStringLiteral("mnemonic")));
        }
    }

    const auto c = comments.match(text);
    if (c.hasMatch()) {
        setFormat(c.capturedStart(), c.capturedLength(),
                  format(QStringLiteral("comment")));
    }
}

}  // namespace aura::gui
