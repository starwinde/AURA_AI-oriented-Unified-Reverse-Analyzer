// src/gui/main_window.cpp — AURA GUI MainWindow implementation
// (Phase 11.3 v1 + 11.3.1 v1.1 Cutter workspace + Decompile pane).

#include "main_window.h"

#include "analysis_options_dialog.h"
#include "decompile_pane.h"
#include "disasm_pane.h"
#include "full_disasm_pane.h"
#include "cfg_pane.h"
#include "hex_pane.h"
#include "function_table_model.h"
#include "xref_table_model.h"
#include "symbol_table_model.h"
#include "string_table_model.h"
#include "project_binary_model.h"
#include "aura/safety/string_safety.h"

#include <QAction>
#include <QActionGroup>
#include <QAbstractItemModel>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QDateTime>
#include <QDockWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSet>
#include <QStack>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPalette>
#include <QPlainTextEdit>
#include <QPoint>
#include <QPushButton>
#include <QSettings>
#include <QStackedWidget>
#include <QStatusBar>
#include <QStyleFactory>
#include <QTableView>
#include <QTextCursor>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

#include <cstdio>
#include <cstring>
#include <functional>

extern "C" {
#include "orchestrator.h"
#include "engine_probe.h"
#include "rizin_adapter.h"
#include "sha256.h"
#include "aura/normalized_records.h"
#include "string_protection_store.h"
}

namespace aura::gui {

namespace {

constexpr const char* kSettingsOrg     = "AURA";
constexpr const char* kSettingsApp     = "aura-gui";
constexpr const char* kKeyOuterGeom    = "outer/geometry";
constexpr const char* kKeyOuterState   = "outer/windowState";
constexpr const char* kKeyWorkspace    = "workspace/state";
constexpr const char* kKeyWorkspaceLayoutVersion = "workspace/layoutVersion";
constexpr int         kWorkspaceLayoutVersion = 5;
constexpr const char* kKeyLastProject  = "lastProjectPath";
// Phase 11.5: recent-projects MRU list (QStringList persisted as
// QSettings group). Capped at kRecentMax — newest first, deduped.
constexpr const char* kKeyRecentProjects = "recentProjects";
constexpr int         kRecentMax         = 5;
// Phase 11.5: monospace pane font-size (Decompile/Disasm/Hex synced).
constexpr const char* kKeyPaneFontPt     = "paneFontPt";
constexpr const char* kKeyUiLanguage     = "ui/language";
constexpr int         kPaneFontDefaultPt = 10;
constexpr int         kPaneFontMinPt     = 6;
constexpr int         kPaneFontMaxPt     = 32;
constexpr const char* kVendoredRizinRelWin =
    "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin.exe";
constexpr const char* kVendoredRizinRelPosix =
    "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin";
constexpr const char* kVendoredSleighRel =
    "third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh";

bool useKoreanUi() {
    QSettings s(QString::fromUtf8(kSettingsOrg), QString::fromUtf8(kSettingsApp));
    return s.value(QString::fromUtf8(kKeyUiLanguage),
                   QStringLiteral("ko")).toString() != QStringLiteral("en");
}

QString rizinStringFlagNeedle(QString content) {
    content = content.trimmed();
    QString out = QStringLiteral("str.");
    out.reserve(content.size() + 4);
    for (const QChar ch : content) {
        if (ch.isLetterOrNumber() || ch == QLatin1Char('.')
            || ch == QLatin1Char(':')) {
            out += ch;
        } else if (ch.isSpace() || ch.unicode() >= 0x20) {
            out += QLatin1Char('_');
        }
    }
    while (out.endsWith(QLatin1Char('_'))) out.chop(1);
    return out;
}

bool parseFirstHexAddress(const QString& line, quint64* out) {
    if (!out) return false;
    const int pos = line.indexOf(QStringLiteral("0x"));
    if (pos < 0) return false;
    int end = pos + 2;
    while (end < line.size()) {
        const QChar ch = line.at(end);
        if (!ch.isDigit()
            && !(ch >= QLatin1Char('a') && ch <= QLatin1Char('f'))
            && !(ch >= QLatin1Char('A') && ch <= QLatin1Char('F'))) {
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

bool resolveRipRelativeTarget(const GuiInstructionRecord& ix, quint64* out) {
    if (!out) return false;
    const QString op = ix.opStr;
    const int rip = op.indexOf(QStringLiteral("rip"), 0,
                               Qt::CaseInsensitive);
    if (rip < 0) return false;
    const int hex = op.indexOf(QStringLiteral("0x"), rip,
                               Qt::CaseInsensitive);
    if (hex < 0) return false;
    int sign = +1;
    for (int i = hex - 1; i >= rip; --i) {
        const QChar ch = op.at(i);
        if (ch == QLatin1Char('+')) { sign = +1; break; }
        if (ch == QLatin1Char('-')) { sign = -1; break; }
    }
    int end = hex + 2;
    while (end < op.size()) {
        const QChar ch = op.at(end);
        if (!ch.isDigit()
            && !(ch >= QLatin1Char('a') && ch <= QLatin1Char('f'))
            && !(ch >= QLatin1Char('A') && ch <= QLatin1Char('F'))) {
            break;
        }
        ++end;
    }
    bool ok = false;
    const quint64 off = op.mid(hex + 2, end - hex - 2).toULongLong(&ok, 16);
    if (!ok) return false;
    *out = sign > 0 ? ix.addr + ix.size + off : ix.addr + ix.size - off;
    return true;
}

QString findRepoRootForGui() {
    if (const char* env = std::getenv("AURA_REPO_ROOT")) {
        if (*env) return QString::fromUtf8(env);
    }

    const QStringList starts = {
        QDir::currentPath(),
        QCoreApplication::applicationDirPath(),
    };

    for (const QString& start : starts) {
        QDir dir(start);
        for (int i = 0; i < 10; ++i) {
#ifdef Q_OS_WIN
            const QString vendored = dir.filePath(QString::fromUtf8(kVendoredRizinRelWin));
#else
            const QString vendored = dir.filePath(QString::fromUtf8(kVendoredRizinRelPosix));
#endif
            if (QFileInfo::exists(vendored)) {
                return dir.absolutePath();
            }
            if (!dir.cdUp()) break;
        }
    }

    return QDir::currentPath();
}

void seedSleighHomeForGui(const QString& repoRoot) {
    if (const char* env = std::getenv("SLEIGHHOME")) {
        if (*env) return;
    }

    const QString sleighHome = QDir(repoRoot).filePath(QString::fromUtf8(kVendoredSleighRel));
    if (QFileInfo::exists(sleighHome)) {
        qputenv("SLEIGHHOME", sleighHome.toUtf8());
    }
}

QString resolveRizinExecForGui() {
    const QString root = findRepoRootForGui();
    qputenv("AURA_REPO_ROOT", root.toUtf8());
    seedSleighHomeForGui(root);

    if (const char* env = std::getenv("AURA_RIZIN_BIN")) {
        if (*env) {
            qputenv("AURA_RIZIN_PATH", QByteArray(env));
            return QString::fromUtf8(env);
        }
    }

    char resolved[1024] = {0};
#ifdef Q_OS_WIN
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              kVendoredRizinRelWin,
                              "rizin",
                              resolved,
                              sizeof(resolved));
#else
    aura_probe_resolve_binary("AURA_RIZIN_BIN",
                              kVendoredRizinRelPosix,
                              "rizin",
                              resolved,
                              sizeof(resolved));
#endif
    const QString exec = QString::fromUtf8(resolved);
    if (QFileInfo::exists(exec)) {
        qputenv("AURA_RIZIN_PATH", exec.toUtf8());
    }
    return exec;
}

QString backendLabel(uint32_t backend) {
    switch (backend) {
        case AURA_RIZIN_DEC_BACKEND_PDGJ: return QStringLiteral("rizin/pdgj (rz-ghidra)");
        case AURA_RIZIN_DEC_BACKEND_PDDJ: return QStringLiteral("rizin/pddj (jsdec JSON)");
        case AURA_RIZIN_DEC_BACKEND_PDD:  return QStringLiteral("rizin/pdd (jsdec text)");
        case AURA_RIZIN_DEC_BACKEND_PDF:  return QStringLiteral("rizin/pdf (disassembly fallback — install rz-ghidra for pseudo-C)");
        default:                          return QStringLiteral("unknown");
    }
}

QString currentFingerprintHex(const QByteArray& digest) {
    if (digest.size() != AURA_SHA256_DIGEST_LEN) return QStringLiteral("unknown");
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1] = {0};
    aura_sha256_hex(reinterpret_cast<const uint8_t*>(digest.constData()), hex);
    return QString::fromLatin1(hex);
}

void copyUtf8(char* dst, size_t cap, const QString& src) {
    if (!dst || cap == 0) return;
    const QByteArray bytes = src.toUtf8();
    std::strncpy(dst, bytes.constData(), cap - 1);
    dst[cap - 1] = '\0';
}

QString sha256HexForText(const QString& text) {
    const QByteArray bytes = text.toUtf8();
    AuraSha256Ctx ctx;
    uint8_t digest[AURA_SHA256_DIGEST_LEN];
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1] = {0};
    aura_sha256_init(&ctx);
    aura_sha256_update(&ctx, bytes.constData(),
                       static_cast<size_t>(bytes.size()));
    aura_sha256_final(&ctx, digest);
    aura_sha256_hex(digest, hex);
    return QString::fromLatin1(hex);
}

void refreshProtectedValue(GuiStringRecord& s) {
    const bool hasMask =
        !s.maskedContent.isEmpty() && s.maskedContent != s.content;
    s.exportValue = hasMask ? s.maskedContent : s.content;

    if (s.displayMode == 1 && !s.alias.isEmpty()) {
        s.protectedValue = s.alias;
    } else if (s.displayMode == 2 && hasMask) {
        s.protectedValue = s.maskedContent;
    } else if (!s.alias.isEmpty()) {
        s.protectedValue = s.alias;
    } else if (hasMask) {
        s.protectedValue = s.maskedContent;
    } else {
        s.protectedValue = s.content;
    }

    if (hasMask) {
        s.hasProtection = true;
        s.protectionSummary =
            useKoreanUi()
                ? QStringLiteral("마스킹 가능: %1").arg(s.maskedContent)
                : QStringLiteral("Maskable: %1").arg(s.maskedContent);
    }
}

void persistStringProtectionRows(const QString& projectPath,
                                 const QString& binaryFingerprint,
                                 const QVector<GuiStringRecord>& strings) {
    if (projectPath.isEmpty() || binaryFingerprint.isEmpty()) return;
    AuraStringProtectionStore* store =
        aura_string_protection_store_open(projectPath.toUtf8().constData());
    if (!store) return;

    for (const GuiStringRecord& s : strings) {
        AuraStoredStringRecord rec{};
        copyUtf8(rec.binary_fingerprint, sizeof(rec.binary_fingerprint),
                 binaryFingerprint);
        copyUtf8(rec.engine_id, sizeof(rec.engine_id),
                 s.source.isEmpty() ? QStringLiteral("unknown") : s.source);
        rec.analysis_run_id = 0;
        rec.string_id = static_cast<uint64_t>(s.stringId);
        rec.addr = static_cast<uint64_t>(s.addr);
        rec.length = static_cast<uint64_t>(s.length);
        copyUtf8(rec.encoding, sizeof(rec.encoding), s.encoding);
        copyUtf8(rec.section, sizeof(rec.section), s.section);
        copyUtf8(rec.original_text, sizeof(rec.original_text), s.content);
        copyUtf8(rec.source, sizeof(rec.source), s.source);
        aura_string_protection_store_put_string(store, &rec);

        for (const auto& f : s.findings) {
            AuraStringProtectionFinding row{};
            copyUtf8(row.binary_fingerprint, sizeof(row.binary_fingerprint),
                     binaryFingerprint);
            row.string_addr = static_cast<uint64_t>(s.addr);
            copyUtf8(row.detector_id, sizeof(row.detector_id), f.detectorId);
            copyUtf8(row.finding_kind, sizeof(row.finding_kind), f.kind);
            row.start_offset = f.startOffset;
            row.end_offset = f.endOffset;
            row.confidence = f.confidence;
            copyUtf8(row.mask_token, sizeof(row.mask_token), f.maskToken);
            aura_string_protection_store_put_finding(store, &row);
        }
    }

    aura_string_protection_store_close(store);
}

void applyStoredStringOverrides(const QString& projectPath,
                                const QString& binaryFingerprint,
                                QVector<GuiStringRecord>* strings) {
    if (!strings || projectPath.isEmpty() || binaryFingerprint.isEmpty())
        return;
    AuraStringProtectionStore* store =
        aura_string_protection_store_open(projectPath.toUtf8().constData());
    if (!store) return;

    for (GuiStringRecord& s : *strings) {
        AuraStringOverrideRecord got{};
        const QString originalHash = sha256HexForText(s.content);
        if (aura_string_protection_store_get_override(
                store,
                binaryFingerprint.toUtf8().constData(),
                static_cast<uint64_t>(s.addr),
                originalHash.toUtf8().constData(),
                &got) != 0) {
            continue;
        }
        s.alias = QString::fromUtf8(got.alias);
        if (got.mask_token[0])
            s.maskedContent = QString::fromUtf8(got.mask_token);
        s.displayMode = got.display_mode;
        refreshProtectedValue(s);
    }

    aura_string_protection_store_close(store);
}

}  // namespace

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(QStringLiteral("AURA"));
    resize(1280, 800);

    applyDarkPalette();

    buildCentralStack();
    buildMenus();
    buildStatusBar();
    updateWindowTitle();

    // Phase 11.5: accept dragged binary files dropped onto the window.
    setAcceptDrops(true);

    restoreUiState();
}

MainWindow::~MainWindow() {
    closeProject();
}

void MainWindow::switchToPage(Page page) {
    if (m_stack) m_stack->setCurrentIndex(static_cast<int>(page));
}

int MainWindow::projectBinaryCount() const {
    if (!m_projectDb) return 0;
    return aura_project_binaries_count(m_projectDb);
}

QString MainWindow::currentDecompileText() const {
    return m_decompilePane ? m_decompilePane->currentText() : QString();
}

void MainWindow::applyDarkPalette() {
    // Cutter-inspired dark palette via QPalette (ADR-0036 §Rationale).
    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QPalette p;
    const QColor bg(45, 45, 48);
    const QColor base(30, 30, 30);
    const QColor altBase(40, 40, 42);
    const QColor text(220, 220, 220);
    const QColor disabled(127, 127, 127);
    const QColor highlight(38, 79, 120);
    const QColor highlightText(255, 255, 255);

    p.setColor(QPalette::Window,          bg);
    p.setColor(QPalette::WindowText,      text);
    p.setColor(QPalette::Base,            base);
    p.setColor(QPalette::AlternateBase,   altBase);
    p.setColor(QPalette::ToolTipBase,     base);
    p.setColor(QPalette::ToolTipText,     text);
    p.setColor(QPalette::Text,            text);
    p.setColor(QPalette::Button,          bg);
    p.setColor(QPalette::ButtonText,      text);
    p.setColor(QPalette::BrightText,      Qt::red);
    p.setColor(QPalette::Highlight,       highlight);
    p.setColor(QPalette::HighlightedText, highlightText);
    p.setColor(QPalette::Link,            QColor(100, 160, 220));

    p.setColor(QPalette::Disabled, QPalette::Text,            disabled);
    p.setColor(QPalette::Disabled, QPalette::ButtonText,      disabled);
    p.setColor(QPalette::Disabled, QPalette::WindowText,      disabled);
    p.setColor(QPalette::Disabled, QPalette::HighlightedText, disabled);

    QApplication::setPalette(p);
}

void MainWindow::buildCentralStack() {
    m_stack = new QStackedWidget(this);

    // ── Page 0 — Project view (ADR-0035 그대로) ─────────────────────────
    auto* projectPage = new QWidget(m_stack);
    auto* pLayout = new QVBoxLayout(projectPage);
    pLayout->setContentsMargins(0, 0, 0, 0);

    m_projectTable = new QTableView(projectPage);
    m_projectModel = new ProjectBinaryModel(this);
    m_projectTable->setModel(m_projectModel);
    m_projectTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_projectTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_projectTable->setAlternatingRowColors(true);
    m_projectTable->verticalHeader()->setVisible(false);
    m_projectTable->horizontalHeader()->setStretchLastSection(false);
    m_projectTable->horizontalHeader()->setSectionResizeMode(
        ProjectBinaryModel::ColPath, QHeaderView::Stretch);
    m_projectTable->horizontalHeader()->setSectionResizeMode(
        ProjectBinaryModel::ColFingerprint, QHeaderView::ResizeToContents);
    m_projectTable->horizontalHeader()->setSectionResizeMode(
        ProjectBinaryModel::ColSize, QHeaderView::ResizeToContents);
    m_projectTable->horizontalHeader()->setSectionResizeMode(
        ProjectBinaryModel::ColLastAnalyzed, QHeaderView::ResizeToContents);
    connect(m_projectTable, &QTableView::doubleClicked, this,
            &MainWindow::onTableDoubleClicked);

    pLayout->addWidget(m_projectTable);

    auto* btnRow = new QHBoxLayout();
    btnRow->addStretch();
    m_analyzeButton = new QPushButton(
        useKoreanUi() ? QStringLiteral("분석...")
                      : QStringLiteral("Analyze..."),
        projectPage);
    m_analyzeButton->setEnabled(false);
    connect(m_analyzeButton, &QPushButton::clicked, this,
            &MainWindow::onAnalyzeClicked);
    btnRow->addWidget(m_analyzeButton);
    pLayout->addLayout(btnRow);

    m_stack->addWidget(projectPage);

    // ── Page 1 — Nested Cutter-style workspace (ADR-0036) ─────────────
    m_workspace = new QMainWindow(m_stack);
    m_workspace->setObjectName(QStringLiteral("workspace"));
    m_workspace->setWindowFlags(Qt::Widget);  // embed inside QStackedWidget
    m_workspace->setDockNestingEnabled(true);

    // Central — intentionally collapsed. The function browser and primary
    // analysis panes are dock widgets, so keeping an instructional central
    // page only wastes the main workspace.
    auto* workspaceCenter = new QWidget(m_workspace);
    workspaceCenter->setObjectName(QStringLiteral("workspaceCenter"));
    workspaceCenter->setFixedSize(0, 0);
    m_workspace->setCentralWidget(workspaceCenter);

    // Left dock — Cutter-style function browser.
    m_functionDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("함수") : QStringLiteral("Functions"),
        m_workspace);
    m_functionDock->setObjectName(QStringLiteral("functionDock"));
    m_functionDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_functionTable = new QTreeView(m_functionDock);
    m_functionTable->setObjectName(QStringLiteral("functionTable"));
    m_functionModel = new FunctionTableModel(this);
    m_functionTable->setModel(m_functionModel);
    m_functionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_functionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_functionTable->setAlternatingRowColors(true);
    m_functionTable->setRootIsDecorated(true);
    m_functionTable->setItemsExpandable(true);
    m_functionTable->setExpandsOnDoubleClick(true);
    m_functionTable->setUniformRowHeights(true);
    m_functionTable->header()->setStretchLastSection(true);
    m_functionTable->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_functionTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_functionTable, &QWidget::customContextMenuRequested, this,
            &MainWindow::onFunctionContextMenu);
    m_functionDock->setWidget(m_functionTable);
    m_workspace->addDockWidget(Qt::LeftDockWidgetArea, m_functionDock);

    // Right dock — Decompile pane.
    m_decompileDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("디컴파일") : QStringLiteral("Decompile"),
        m_workspace);
    m_decompileDock->setObjectName(QStringLiteral("decompileDock"));
    m_decompileDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_decompilePane = new DecompilePane(m_decompileDock);
    m_decompileDock->setWidget(m_decompilePane);
    m_workspace->addDockWidget(Qt::RightDockWidgetArea, m_decompileDock);
    m_workspace->resizeDocks({m_functionDock, m_decompileDock},
                             {280, 900}, Qt::Horizontal);

    // Phase 11.3.7 (P2.F2 C3): Disassembly dock — tabified onto Decompile
    // dock per ADR-0040 D5 (Cutter pattern; user toggles between
    // pseudo-C and raw asm in same screen real estate).
    m_disasmDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("디스어셈블리")
                      : QStringLiteral("Disassembly"),
        m_workspace);
    m_disasmDock->setObjectName(QStringLiteral("disasmDock"));
    m_disasmDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_disasmPane = new DisasmPane(m_disasmDock);
    m_disasmDock->setWidget(m_disasmPane);
    m_workspace->tabifyDockWidget(m_decompileDock, m_disasmDock);

    // Full-disassembly dock — Cutter-style continuous VA listing. It reuses
    // DISASM with a bounded pD text stream and function selection scrolls here.
    m_fullDisasmDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("전체 디스어셈블리")
                      : QStringLiteral("Full Disassembly"),
        m_workspace);
    m_fullDisasmDock->setObjectName(QStringLiteral("fullDisasmDock"));
    m_fullDisasmDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_fullDisasmPane = new FullDisasmPane(m_fullDisasmDock);
    m_fullDisasmDock->setWidget(m_fullDisasmPane);
    m_workspace->tabifyDockWidget(m_decompileDock, m_fullDisasmDock);

    // Phase 11.3.8 (P2.F3 C2): CFG dock — tabified onto Decompile/Disasm
    // group so the user toggles between three views in one screen real
    // estate (per ADR-0041 D5).
    m_cfgDock = new QDockWidget(QStringLiteral("CFG"), m_workspace);
    m_cfgDock->setObjectName(QStringLiteral("cfgDock"));
    m_cfgDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_cfgPane = new CfgPane(m_cfgDock);
    m_cfgDock->setWidget(m_cfgPane);
    m_workspace->tabifyDockWidget(m_decompileDock, m_cfgDock);

    // Phase 11.3.10 (P2.F5 C2): Hex dock — tabified onto the same group
    // (per ADR-0043 D3 — DisasmPane pattern; user toggles between
    // Decompile / Disasm / CFG / Hex in one screen real estate).
    m_hexDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("헥스") : QStringLiteral("Hex"),
        m_workspace);
    m_hexDock->setObjectName(QStringLiteral("hexDock"));
    m_hexDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_hexPane = new HexPane(m_hexDock);
    m_hexDock->setWidget(m_hexPane);
    m_workspace->tabifyDockWidget(m_decompileDock, m_hexDock);

    // Phase 11.3.7 (P2.F2 C4): one-way line_map sync — cursor click in
    // DecompilePane resolves to an address (via cached lineMap) and
    // jumps DisasmPane to the matching instruction. Reverse direction
    // (disasm → decomp) is F4 territory per ADR-0040 D5.
    connect(m_decompilePane, &DecompilePane::lineSelected,
            m_disasmPane,    &DisasmPane::selectInstruction);

    // Phase 11.3.8 (P2.F3 C4): cross-pane sync — double-click on a
    // basic block in CfgPane jumps DisasmPane to the block's first
    // instruction (per ADR-0041 D5).
    connect(m_cfgPane,    &CfgPane::blockActivated,
            m_disasmPane, &DisasmPane::selectInstruction);

    // Phase 11.3.9 (P2.F4 C1): bidirectional line_map sync — closes the
    // F2 deferred reverse direction (ADR-0042 D1). Each pane uses
    // QSignalBlocker internally to prevent echo loops.
    connect(m_disasmPane,    &DisasmPane::instructionSelected,
            m_decompilePane, &DecompilePane::selectLine);

    // Phase 11.3.10 (P2.F5 C4): one-way cross-pane sync into hex view
    // (ADR-0043 D5). Disasm cursor and CFG block double-click both
    // page the hex pane to the matching offset. Reverse (hex click →
    // disasm) is F5 v2 territory (nearest-instruction snap).
    connect(m_disasmPane, &DisasmPane::instructionSelected,
            m_hexPane,    &HexPane::scrollToAddr);
    connect(m_cfgPane,    &CfgPane::blockActivated,
            m_hexPane,    &HexPane::scrollToAddr);
    connect(m_disasmPane, &DisasmPane::instructionSelected,
            m_fullDisasmPane, &FullDisasmPane::setStartAddress);
    connect(m_cfgPane,    &CfgPane::blockActivated,
            m_fullDisasmPane, &FullDisasmPane::setStartAddress);

    // Phase 11.3.9 (P2.F4 C2): DecompilePane context-menu actions.
    connect(m_decompilePane, &DecompilePane::contextJumpToDisasm,
            this, &MainWindow::onDecompContextJump);
    connect(m_decompilePane, &DecompilePane::contextRename,
            this, &MainWindow::onDecompContextRename);
    connect(m_decompilePane, &DecompilePane::contextResetName,
            this, &MainWindow::onDecompContextReset);
    connect(m_decompilePane, &DecompilePane::contextFindXrefs,
            this, &MainWindow::onDecompContextFindXrefs);
    connect(m_decompilePane, &DecompilePane::contextAddComment,
            this, &MainWindow::onDecompContextAddComment);

    // Phase 11.3.5: Xrefs dock — tabbed with the upper-left function group.
    m_xrefsDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("참조") : QStringLiteral("Xrefs"),
        m_workspace);
    m_xrefsDock->setObjectName(QStringLiteral("xrefsDock"));
    m_xrefsDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_xrefsTable = new QTreeView(m_xrefsDock);
    m_xrefsModel = new XrefTableModel(m_xrefsTable);
    m_xrefsTable->setModel(m_xrefsModel);
    m_xrefsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_xrefsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_xrefsTable->setRootIsDecorated(true);
    m_xrefsTable->setUniformRowHeights(true);
    m_xrefsTable->header()->setStretchLastSection(true);
    m_xrefsDock->setWidget(m_xrefsTable);
    m_workspace->addDockWidget(Qt::LeftDockWidgetArea, m_xrefsDock);

    // Phase 11.3.5: Symbols dock — lower-left metadata tab.
    m_symbolsDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("심볼") : QStringLiteral("Symbols"),
        m_workspace);
    m_symbolsDock->setObjectName(QStringLiteral("symbolsDock"));
    m_symbolsDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_symbolsTable = new QTreeView(m_symbolsDock);
    m_symbolsModel = new SymbolTableModel(m_symbolsTable);
    m_symbolsTable->setModel(m_symbolsModel);
    m_symbolsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_symbolsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_symbolsTable->setRootIsDecorated(true);
    m_symbolsTable->setUniformRowHeights(true);
    m_symbolsTable->header()->setStretchLastSection(true);
    m_symbolsDock->setWidget(m_symbolsTable);
    m_workspace->addDockWidget(Qt::LeftDockWidgetArea, m_symbolsDock);

    // Phase 11.3.5: Imports dock — separate import-only tree model fed
    // from the same m_symbols mirror.
    m_importsDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("임포트") : QStringLiteral("Imports"),
        m_workspace);
    m_importsDock->setObjectName(QStringLiteral("importsDock"));
    m_importsDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_importsTable = new QTreeView(m_importsDock);
    m_importsModel = new SymbolTableModel(m_importsTable);
    m_importsModel->setImportOnly(true);
    m_importsTable->setModel(m_importsModel);
    m_importsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_importsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_importsTable->setRootIsDecorated(true);
    m_importsTable->setUniformRowHeights(true);
    m_importsTable->header()->setStretchLastSection(true);
    m_importsDock->setWidget(m_importsTable);
    m_workspace->tabifyDockWidget(m_symbolsDock, m_importsDock);

    // Phase 11.3.6: Strings dock — dedicated model (different schema from
    // Symbols, so QSortFilterProxyModel reuse is not applicable). Tabified
    // alongside Symbols/Imports so the user toggles between three related
    // literal-style browsers in the same screen real-estate.
    m_stringsDock = new QDockWidget(
        useKoreanUi() ? QStringLiteral("문자열") : QStringLiteral("Strings"),
        m_workspace);
    m_stringsDock->setObjectName(QStringLiteral("stringsDock"));
    m_stringsDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_stringsTable = new QTreeView(m_stringsDock);
    m_stringsModel = new StringTableModel(m_stringsTable);
    m_stringsTable->setModel(m_stringsModel);
    m_stringsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_stringsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_stringsTable->setRootIsDecorated(true);
    m_stringsTable->setUniformRowHeights(true);
    m_stringsTable->header()->setStretchLastSection(true);
    m_stringsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_stringsTable, &QTreeView::activated,
            this, &MainWindow::onStringRowActivated);
    connect(m_stringsTable, &QTreeView::doubleClicked,
            this, &MainWindow::onStringRowActivated);
    connect(m_stringsTable, &QWidget::customContextMenuRequested, this,
            &MainWindow::onStringContextMenu);
    m_stringsDock->setWidget(m_stringsTable);
    m_workspace->tabifyDockWidget(m_symbolsDock, m_stringsDock);

    // Cutter-like default: upper-left function/reference browser, lower-left
    // string/symbol/import metadata, and a large right code-view tab group.
    m_workspace->tabifyDockWidget(m_functionDock, m_xrefsDock);
    m_workspace->splitDockWidget(m_functionDock, m_symbolsDock, Qt::Vertical);
    m_functionDock->raise();
    m_stringsDock->raise();
    m_decompileDock->raise();
    m_workspace->resizeDocks({m_functionDock, m_decompileDock},
                             {320, 1280}, Qt::Horizontal);
    m_workspace->resizeDocks({m_functionDock, m_symbolsDock},
                             {540, 360}, Qt::Vertical);

    installSearchScope(m_functionTable, SearchScope::Functions);
    installSearchScope(m_xrefsTable, SearchScope::Xrefs);
    installSearchScope(m_stringsTable, SearchScope::Strings);
    installSearchScope(m_symbolsTable, SearchScope::Symbols);
    installSearchScope(m_importsTable, SearchScope::Imports);
    installSearchScope(m_decompilePane, SearchScope::Decompile);
    installSearchScope(m_disasmPane, SearchScope::Disassembly);
    installSearchScope(m_fullDisasmPane, SearchScope::FullDisassembly);
    installSearchScope(m_cfgPane, SearchScope::CFG);
    installSearchScope(m_hexPane, SearchScope::Hex);

    m_stack->addWidget(m_workspace);

    setCentralWidget(m_stack);
    m_stack->setCurrentIndex(PageProject);
}

void MainWindow::buildMenus() {
    auto* mb = menuBar();
    const bool ko = useKoreanUi();

    auto* fileMenu = mb->addMenu(ko ? QStringLiteral("&파일")
                                    : QStringLiteral("&File"));

    m_actNewProject = new QAction(
        ko ? QStringLiteral("새 프로젝트(&N)...")
           : QStringLiteral("&New Project..."),
        this);
    m_actNewProject->setShortcut(QKeySequence::New);
    connect(m_actNewProject, &QAction::triggered, this, &MainWindow::onNewProject);
    fileMenu->addAction(m_actNewProject);

    m_actOpenProject = new QAction(
        ko ? QStringLiteral("프로젝트 열기(&O)...")
           : QStringLiteral("&Open Project..."),
        this);
    m_actOpenProject->setShortcut(QKeySequence::Open);
    connect(m_actOpenProject, &QAction::triggered, this, &MainWindow::onOpenProject);
    fileMenu->addAction(m_actOpenProject);

    // Phase 11.5: recent projects MRU (populated lazily — see
    // rebuildRecentMenu, called on startup and after each successful
    // openProject).
    m_recentMenu = fileMenu->addMenu(
        ko ? QStringLiteral("최근 프로젝트 열기(&R)")
           : QStringLiteral("Open &Recent"));
    rebuildRecentMenu();

    fileMenu->addSeparator();

    m_actAddBinary = new QAction(
        ko ? QStringLiteral("바이너리 추가(&A)...")
           : QStringLiteral("&Add Binary..."),
        this);
    m_actAddBinary->setEnabled(false);
    connect(m_actAddBinary, &QAction::triggered, this, &MainWindow::onAddBinary);
    fileMenu->addAction(m_actAddBinary);

    fileMenu->addSeparator();

    m_actQuit = new QAction(
        ko ? QStringLiteral("종료(&Q)") : QStringLiteral("&Quit"),
        this);
    m_actQuit->setShortcut(QKeySequence::Quit);
    connect(m_actQuit, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(m_actQuit);

    auto* viewMenu = mb->addMenu(ko ? QStringLiteral("&보기")
                                    : QStringLiteral("&View"));
    m_actBackToProject = new QAction(
        ko ? QStringLiteral("프로젝트 화면으로 돌아가기(&B)")
           : QStringLiteral("&Back to Project"),
        this);
    m_actBackToProject->setShortcut(Qt::Key_Escape);
    m_actBackToProject->setEnabled(false);
    connect(m_actBackToProject, &QAction::triggered, this,
            [this] { switchToPage(PageProject); });
    viewMenu->addAction(m_actBackToProject);

    // Phase 11.3.9 (P2.F4 C3): function navigation history actions
    // (browser-style Alt+Left / Alt+Right). View menu hosts the
    // discoverable copies; ADR-0042 D4 explicitly rejects a new toolbar.
    viewMenu->addSeparator();
    m_actNavBack = new QAction(
        ko ? QStringLiteral("이전 함수(&B)") : QStringLiteral("&Back (function)"),
        this);
    m_actNavBack->setShortcut(QKeySequence(Qt::ALT | Qt::Key_Left));
    m_actNavBack->setEnabled(false);
    connect(m_actNavBack, &QAction::triggered, this, &MainWindow::goBack);
    viewMenu->addAction(m_actNavBack);

    m_actNavForward = new QAction(
        ko ? QStringLiteral("다음 함수(&F)")
           : QStringLiteral("&Forward (function)"),
        this);
    m_actNavForward->setShortcut(QKeySequence(Qt::ALT | Qt::Key_Right));
    m_actNavForward->setEnabled(false);
    connect(m_actNavForward, &QAction::triggered, this, &MainWindow::goForward);
    viewMenu->addAction(m_actNavForward);

    // Phase 11.5 (P5 polish) — go-to-function-by-address (Ctrl+G).
    viewMenu->addSeparator();
    QAction* actGoTo = new QAction(
        ko ? QStringLiteral("주소로 이동(&G)...")
           : QStringLiteral("&Go to address..."),
        this);
    actGoTo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    connect(actGoTo, &QAction::triggered, this, &MainWindow::onGoToAddress);
    viewMenu->addAction(actGoTo);

    // Phase 11.5+ — find in the last-focused pane/table (Ctrl+F).
    QAction* actFind = new QAction(
        ko ? QStringLiteral("현재 패널에서 찾기(&F)...")
           : QStringLiteral("&Find in active pane..."),
        this);
    actFind->setShortcut(QKeySequence::Find);  // Ctrl+F
    connect(actFind, &QAction::triggered,
            this, &MainWindow::onFindInActiveScope);
    viewMenu->addAction(actFind);

    // Phase 11.5 (P5 polish) — Decompile/Disasm/Hex pane font zoom
    // (Ctrl+= / Ctrl+- / Ctrl+0). Persisted via QSettings.
    viewMenu->addSeparator();
    QAction* actZoomIn = new QAction(
        ko ? QStringLiteral("패널 확대(&I)") : QStringLiteral("Zoom &In (panes)"),
        this);
    actZoomIn->setShortcut(QKeySequence::ZoomIn);  // Ctrl+=
    connect(actZoomIn, &QAction::triggered, this, &MainWindow::onZoomInPanes);
    viewMenu->addAction(actZoomIn);
    QAction* actZoomOut = new QAction(
        ko ? QStringLiteral("패널 축소(&O)") : QStringLiteral("Zoom &Out (panes)"),
        this);
    actZoomOut->setShortcut(QKeySequence::ZoomOut);  // Ctrl+-
    connect(actZoomOut, &QAction::triggered, this, &MainWindow::onZoomOutPanes);
    viewMenu->addAction(actZoomOut);
    QAction* actZoomReset = new QAction(
        ko ? QStringLiteral("패널 배율 초기화(&R)")
           : QStringLiteral("&Reset pane zoom"),
        this);
    actZoomReset->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(actZoomReset, &QAction::triggered, this,
            &MainWindow::onResetPaneZoom);
    viewMenu->addAction(actZoomReset);

    // Phase 11.5 (P5 polish) — Ctrl+1/2/3/4 dock focus.
    viewMenu->addSeparator();
    struct { const char* label; int n; Qt::Key key; } docks[] = {
        {ko ? "디컴파일 패널로 이동(&D)" : "Focus &Decompile", 1, Qt::Key_1},
        {ko ? "디스어셈블리 패널로 이동(&S)" : "Focus Di&sasm", 2, Qt::Key_2},
        {ko ? "전체 디스어셈블리 패널로 이동(&F)" : "Focus &Full Disasm", 3, Qt::Key_3},
        {ko ? "CFG 패널로 이동(&C)" : "Focus &CFG", 4, Qt::Key_4},
        {ko ? "헥스 패널로 이동(&H)" : "Focus &Hex", 5, Qt::Key_5},
    };
    for (auto& d : docks) {
        QAction* a = new QAction(QString::fromUtf8(d.label), this);
        a->setShortcut(QKeySequence(Qt::CTRL | d.key));
        const int n = d.n;
        connect(a, &QAction::triggered, this,
                [this, n] { focusDock(n); });
        viewMenu->addAction(a);
    }

    auto* settingsMenu = mb->addMenu(ko ? QStringLiteral("&설정")
                                        : QStringLiteral("&Settings"));
    auto* languageMenu = settingsMenu->addMenu(
        ko ? QStringLiteral("언어(&L)") : QStringLiteral("&Language"));
    auto* languageGroup = new QActionGroup(this);
    QAction* koreanAct = languageMenu->addAction(QStringLiteral("한국어"));
    QAction* englishAct = languageMenu->addAction(QStringLiteral("English"));
    koreanAct->setCheckable(true);
    englishAct->setCheckable(true);
    koreanAct->setActionGroup(languageGroup);
    englishAct->setActionGroup(languageGroup);
    koreanAct->setChecked(ko);
    englishAct->setChecked(!ko);
    auto setLanguage = [this](const QString& lang) {
        QSettings s(QString::fromUtf8(kSettingsOrg),
                    QString::fromUtf8(kSettingsApp));
        s.setValue(QString::fromUtf8(kKeyUiLanguage), lang);
        QMessageBox::information(
            this,
            lang == QStringLiteral("ko") ? QStringLiteral("언어 설정")
                                         : QStringLiteral("Language"),
            lang == QStringLiteral("ko")
                ? QStringLiteral("한국어 UI 설정을 저장했습니다. 다음 실행부터 적용됩니다.")
                : QStringLiteral("English UI setting saved. It will apply on next launch."));
    };
    connect(koreanAct, &QAction::triggered, this,
            [setLanguage] { setLanguage(QStringLiteral("ko")); });
    connect(englishAct, &QAction::triggered, this,
            [setLanguage] { setLanguage(QStringLiteral("en")); });

    auto* helpMenu = mb->addMenu(ko ? QStringLiteral("&도움말")
                                    : QStringLiteral("&Help"));
    // Phase 11.5 (P5 polish) — keyboard shortcuts cheat sheet (Ctrl+/).
    QAction* actShortcuts = new QAction(
        ko ? QStringLiteral("키보드 단축키(&K)...")
           : QStringLiteral("&Keyboard shortcuts..."),
        this);
    actShortcuts->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Slash));
    connect(actShortcuts, &QAction::triggered, this,
            &MainWindow::onShowKeyboardShortcuts);
    helpMenu->addAction(actShortcuts);
    helpMenu->addSeparator();
    m_actAbout = new QAction(
        ko ? QStringLiteral("AURA 정보(&A)") : QStringLiteral("&About AURA"),
        this);
    connect(m_actAbout, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(m_actAbout);
}

void MainWindow::buildStatusBar() {
    statusBar()->showMessage(
        useKoreanUi()
            ? QStringLiteral("프로젝트를 열거나 새로 만드세요 — 파일 → 새 프로젝트 / 프로젝트 열기")
            : QStringLiteral("Open or create a project — File → New Project / Open Project"));
}

void MainWindow::closeProject() {
    if (m_projectModel) m_projectModel->setRegistry(nullptr);
    if (m_projectDb) {
        aura_project_binaries_close(m_projectDb);
        m_projectDb = nullptr;
    }
    if (m_overrideStore) {
        aura_override_store_close(m_overrideStore);
        m_overrideStore = nullptr;
    }
    m_projectPath.clear();
    m_currentBinaryPath.clear();
    m_currentSha256.clear();
    m_functions.clear();
    m_xrefs.clear();
    m_symbols.clear();
    std::memset(&m_currentFingerprint, 0, sizeof(m_currentFingerprint));
    if (m_decompilePane) m_decompilePane->clearCache();
    if (m_disasmPane)    m_disasmPane->clearCache();
    if (m_cfgPane)       m_cfgPane->clearCache();
    if (m_actAddBinary) m_actAddBinary->setEnabled(false);
    if (m_analyzeButton) m_analyzeButton->setEnabled(false);
}

void MainWindow::updateWindowTitle() {
    if (m_projectPath.isEmpty()) {
        setWindowTitle(QStringLiteral("AURA"));
    } else {
        const QFileInfo fi(m_projectPath);
        setWindowTitle(QStringLiteral("AURA — %1").arg(fi.fileName()));
    }
}

void MainWindow::restoreUiState() {
    QSettings s(QString::fromUtf8(kSettingsOrg), QString::fromUtf8(kSettingsApp));
    if (s.contains(QString::fromUtf8(kKeyOuterGeom)))
        restoreGeometry(s.value(QString::fromUtf8(kKeyOuterGeom)).toByteArray());
    if (s.contains(QString::fromUtf8(kKeyOuterState)))
        restoreState(s.value(QString::fromUtf8(kKeyOuterState)).toByteArray());
    if (m_workspace &&
        s.value(QString::fromUtf8(kKeyWorkspaceLayoutVersion), 0).toInt() ==
            kWorkspaceLayoutVersion &&
        s.contains(QString::fromUtf8(kKeyWorkspace))) {
        m_workspace->restoreState(
            s.value(QString::fromUtf8(kKeyWorkspace)).toByteArray());
    } else {
        s.remove(QString::fromUtf8(kKeyWorkspace));
        s.setValue(QString::fromUtf8(kKeyWorkspaceLayoutVersion),
                   kWorkspaceLayoutVersion);
    }
    // Phase 11.5: pane font-size restore (default if absent).
    const int pt = s.value(QString::fromUtf8(kKeyPaneFontPt),
                           kPaneFontDefaultPt).toInt();
    setPaneFontPointSize(pt);
}

void MainWindow::saveUiState() {
    QSettings s(QString::fromUtf8(kSettingsOrg), QString::fromUtf8(kSettingsApp));
    s.setValue(QString::fromUtf8(kKeyOuterGeom),  saveGeometry());
    s.setValue(QString::fromUtf8(kKeyOuterState), saveState());
    if (m_workspace)
        s.setValue(QString::fromUtf8(kKeyWorkspace), m_workspace->saveState());
    s.setValue(QString::fromUtf8(kKeyWorkspaceLayoutVersion),
               kWorkspaceLayoutVersion);
    if (!m_projectPath.isEmpty())
        s.setValue(QString::fromUtf8(kKeyLastProject), m_projectPath);
    // Phase 11.5: persist pane font-size.
    s.setValue(QString::fromUtf8(kKeyPaneFontPt), paneFontPointSize());
}

// ── Phase 11.5 (P5 polish): recent-projects MRU list ─────────────────────

QStringList MainWindow::recentProjects() const {
    QSettings s(QString::fromUtf8(kSettingsOrg),
                QString::fromUtf8(kSettingsApp));
    return s.value(QString::fromUtf8(kKeyRecentProjects))
        .toStringList();
}

void MainWindow::pushRecentProject(const QString& path) {
    if (path.isEmpty()) return;
    QSettings s(QString::fromUtf8(kSettingsOrg),
                QString::fromUtf8(kSettingsApp));
    QStringList list =
        s.value(QString::fromUtf8(kKeyRecentProjects)).toStringList();
    list.removeAll(path);          // dedupe
    list.prepend(path);             // newest first
    while (list.size() > kRecentMax) list.removeLast();
    s.setValue(QString::fromUtf8(kKeyRecentProjects), list);
    rebuildRecentMenu();
}

void MainWindow::rebuildRecentMenu() {
    if (!m_recentMenu) return;
    m_recentMenu->clear();
    const QStringList list = recentProjects();
    if (list.isEmpty()) {
        QAction* placeholder = m_recentMenu->addAction(
            QStringLiteral("(no recent projects)"));
        placeholder->setEnabled(false);
        return;
    }
    for (const QString& path : list) {
        // Numeric mnemonic (1..9) → no key collision with the rest of
        // the File menu's accelerators.
        const int idx = m_recentMenu->actions().size() + 1;
        const QString display = (idx <= 9)
            ? QStringLiteral("&%1  %2").arg(idx).arg(path)
            : path;
        QAction* a = m_recentMenu->addAction(display);
        connect(a, &QAction::triggered, this,
                [this, path]() { openProject(path); });
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    saveUiState();
    QMainWindow::closeEvent(event);
}

// ── Phase 11.5 (P5 polish): drag-drop binary onto window ─────────────────

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        // Accept *any* URL list; the dropEvent does the real validation.
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event) {
    if (!event->mimeData()->hasUrls()) return;
    QStringList paths;
    const QList<QUrl> urls = event->mimeData()->urls();
    for (const QUrl& u : urls) {
        if (!u.isLocalFile()) continue;
        paths << u.toLocalFile();
    }
    if (paths.isEmpty()) return;
    handleDroppedPaths(paths);
    event->acceptProposedAction();
}

bool MainWindow::jumpToFunction(quint64 addr) {
    if (!m_functionTable) return false;
    int row = -1;
    for (int i = 0; i < m_functions.size(); ++i) {
        if (m_functions[i].entry == addr) { row = i; break; }
    }
    if (row < 0) {
        statusBar()->showMessage(
            QStringLiteral("No function at 0x%1 — analyze the binary first")
                .arg(addr, 0, 16),
            5000);
        return false;
    }
    // Mirrors goBack/goForward: selecting the function index drives the
    // onFunctionRowSelected cascade (decompile + disasm + cfg).
    const QModelIndex idx = m_functionModel->functionIndex(row);
    m_functionTable->setCurrentIndex(idx);
    m_functionTable->scrollTo(idx);
    return true;
}

int MainWindow::functionRowContainingAddress(quint64 addr) const {
    for (int i = 0; i < m_functions.size(); ++i) {
        const auto& f = m_functions[i];
        const quint64 span = f.size == 0 ? 1 : f.size;
        if (addr >= f.entry && addr < f.entry + span) return i;
    }
    return -1;
}

bool MainWindow::jumpToStringReference(int stringRow) {
    if (stringRow < 0 || stringRow >= m_strings.size()) return false;

    const auto& s = m_strings[stringRow];
    quint64 refAddr = 0;
    int functionRow = -1;
    for (const auto& x : m_xrefs) {
        if (x.to != s.addr) continue;
        const int row = functionRowContainingAddress(x.from);
        if (row < 0) continue;
        refAddr = x.from;
        functionRow = row;
        break;
    }

    if (functionRow < 0) {
        const QString addrHex = QString::number(s.addr, 16);
        const QString addrNeedle = QStringLiteral("0x%1").arg(addrHex);
        const QString flagNeedle = rizinStringFlagNeedle(s.content);
        if (m_fullDisasmPane) {
            const QStringList lines =
                m_fullDisasmPane->currentText().split(QLatin1Char('\n'));
            for (const QString& line : lines) {
                if (!line.contains(addrNeedle, Qt::CaseInsensitive)
                    && !line.contains(addrHex, Qt::CaseInsensitive)
                    && (flagNeedle.isEmpty()
                        || !line.contains(flagNeedle, Qt::CaseInsensitive))) {
                    continue;
                }
                quint64 lineAddr = 0;
                if (!parseFirstHexAddress(line, &lineAddr)) continue;
                const int row = functionRowContainingAddress(lineAddr);
                if (row < 0) continue;
                refAddr = lineAddr;
                functionRow = row;
                break;
            }
        }
    }

    if (functionRow < 0) {
        const QString addrHex = QString::number(s.addr, 16);
        const QString addrNeedle = QStringLiteral("0x%1").arg(addrHex);
        const QString flagNeedle = rizinStringFlagNeedle(s.content);
        const int scanLimit = qMin(m_functions.size(), 32);
        for (int i = 0; i < scanLimit && functionRow < 0; ++i) {
            const quint64 funcAddr = m_functions[i].entry;
            if (!runDisasm(funcAddr)) continue;
            const auto ins = disasmList(funcAddr);
            for (const auto& ix : ins) {
                const QString hay = ix.opStr;
                quint64 ripTarget = 0;
                if (hay.contains(addrNeedle, Qt::CaseInsensitive)
                    || hay.contains(addrHex, Qt::CaseInsensitive)
                    || (!flagNeedle.isEmpty()
                        && hay.contains(flagNeedle, Qt::CaseInsensitive))
                    || (resolveRipRelativeTarget(ix, &ripTarget)
                        && ripTarget == s.addr)) {
                    refAddr = ix.addr;
                    functionRow = i;
                    break;
                }
            }
        }
    }

    if (functionRow < 0 || refAddr == 0) {
        statusBar()->showMessage(
            QStringLiteral("문자열 참조를 찾지 못했습니다: 0x%1")
                .arg(s.addr, 0, 16),
            5000);
        return false;
    }

    const quint64 funcAddr = m_functions[functionRow].entry;
    jumpToFunction(funcAddr);
    focusDock(1);
    if (m_decompileDock) m_decompileDock->raise();
    if (m_decompilePane) m_decompilePane->selectLine(refAddr);
    if (m_disasmPane) m_disasmPane->selectInstruction(refAddr);
    if (m_fullDisasmPane) m_fullDisasmPane->setStartAddress(refAddr);
    statusBar()->showMessage(
        QStringLiteral("문자열 참조로 이동: 0x%1 -> 0x%2")
            .arg(s.addr, 0, 16)
            .arg(refAddr, 0, 16),
        5000);
    return true;
}

QString MainWindow::stringProtectedValueAt(int stringRow) const {
    if (stringRow < 0 || stringRow >= m_strings.size()) return {};
    return m_strings[stringRow].protectedValue;
}

bool MainWindow::persistStringOverride(int stringRow) const {
    if (stringRow < 0 || stringRow >= m_strings.size()) return false;
    if (m_projectPath.isEmpty()) return false;
    const QString fp = currentFingerprintHex(m_currentSha256);
    if (fp.isEmpty() || fp == QStringLiteral("unknown")) return false;

    AuraStringProtectionStore* store =
        aura_string_protection_store_open(m_projectPath.toUtf8().constData());
    if (!store) return false;

    const GuiStringRecord& s = m_strings[stringRow];
    AuraStringOverrideRecord rec{};
    copyUtf8(rec.binary_fingerprint, sizeof(rec.binary_fingerprint), fp);
    rec.string_addr = static_cast<uint64_t>(s.addr);
    copyUtf8(rec.original_hash, sizeof(rec.original_hash),
             sha256HexForText(s.content));
    copyUtf8(rec.alias, sizeof(rec.alias), s.alias);
    copyUtf8(rec.mask_token, sizeof(rec.mask_token), s.maskedContent);
    rec.display_mode = s.displayMode;
    const bool ok = aura_string_protection_store_put_override(store, &rec) == 0;
    aura_string_protection_store_close(store);
    return ok;
}

bool MainWindow::setStringAliasAt(int stringRow, const QString& alias) {
    if (stringRow < 0 || stringRow >= m_strings.size()) return false;
    m_strings[stringRow].alias = alias.trimmed();
    if (!m_strings[stringRow].alias.isEmpty())
        m_strings[stringRow].displayMode = 1;
    refreshProtectedValue(m_strings[stringRow]);
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
    persistStringOverride(stringRow);
    return true;
}

bool MainWindow::setStringMaskTokenAt(int stringRow, const QString& maskToken) {
    if (stringRow < 0 || stringRow >= m_strings.size()) return false;
    QString token = maskToken.trimmed();
    if (!token.isEmpty()) {
        if (!token.startsWith(QLatin1Char('['))) token.prepend(QLatin1Char('['));
        if (!token.endsWith(QLatin1Char(']'))) token.append(QLatin1Char(']'));
    }
    m_strings[stringRow].maskedContent = token;
    if (!token.isEmpty()) {
        m_strings[stringRow].displayMode = 2;
        m_strings[stringRow].hasProtection = true;
    }
    refreshProtectedValue(m_strings[stringRow]);
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
    persistStringOverride(stringRow);
    return true;
}

bool MainWindow::setStringDisplayModeAt(int stringRow, int displayMode) {
    if (stringRow < 0 || stringRow >= m_strings.size()) return false;
    if (displayMode < 0 || displayMode > 2) return false;
    m_strings[stringRow].displayMode = displayMode;
    refreshProtectedValue(m_strings[stringRow]);
    if (m_stringsModel) m_stringsModel->setStrings(m_strings);
    persistStringOverride(stringRow);
    return true;
}

QString MainWindow::clipboardTextForFunction(int row,
                                             const QString& kind) const {
    if (row < 0 || row >= m_functions.size()) return QString();
    const auto& f = m_functions[row];
    if (kind == QStringLiteral("address")) {
        return QStringLiteral("0x%1").arg(f.entry, 0, 16);
    }
    if (kind == QStringLiteral("name")) {
        return f.name;
    }
    return QString();
}

void MainWindow::setPaneFontPointSize(int pt) {
    if (pt < kPaneFontMinPt) pt = kPaneFontMinPt;
    if (pt > kPaneFontMaxPt) pt = kPaneFontMaxPt;
    if (m_decompilePane) m_decompilePane->setMonospaceFontPointSize(pt);
    if (m_disasmPane)    m_disasmPane->setMonospaceFontPointSize(pt);
    if (m_hexPane)       m_hexPane->setMonospaceFontPointSize(pt);
}

int MainWindow::paneFontPointSize() const {
    // Decompile pane is the canonical source — three panes are kept
    // in sync via setPaneFontPointSize.
    if (m_decompilePane) return m_decompilePane->monospaceFontPointSize();
    return kPaneFontDefaultPt;
}

void MainWindow::onZoomInPanes() {
    setPaneFontPointSize(paneFontPointSize() + 1);
    statusBar()->showMessage(
        QStringLiteral("Pane font: %1pt").arg(paneFontPointSize()), 2000);
}

void MainWindow::onZoomOutPanes() {
    setPaneFontPointSize(paneFontPointSize() - 1);
    statusBar()->showMessage(
        QStringLiteral("Pane font: %1pt").arg(paneFontPointSize()), 2000);
}

void MainWindow::onResetPaneZoom() {
    setPaneFontPointSize(kPaneFontDefaultPt);
    statusBar()->showMessage(
        QStringLiteral("Pane font reset: %1pt").arg(paneFontPointSize()), 2000);
}

QString MainWindow::keyboardShortcutsHtml() {
    // Single source of truth — Help dialog and gui_smoke both read
    // this. Each <tr> = (key, action). When adding a new shortcut,
    // append a row here so it shows up in both places automatically.
    return QStringLiteral(
        "<h3>AURA — Keyboard shortcuts</h3>"
        "<table cellspacing='6'>"
        "<tr><th align='left'>Key</th><th align='left'>Action</th></tr>"
        "<tr><td><b>Ctrl+N</b></td><td>New project</td></tr>"
        "<tr><td><b>Ctrl+O</b></td><td>Open project</td></tr>"
        "<tr><td><b>Esc</b></td><td>Back to project view</td></tr>"
        "<tr><td><b>Alt+Left</b></td><td>Navigate back (function)</td></tr>"
        "<tr><td><b>Alt+Right</b></td><td>Navigate forward (function)</td></tr>"
        "<tr><td><b>Ctrl+G</b></td><td>Go to function address</td></tr>"
        "<tr><td><b>Ctrl+F</b></td><td>Find in active pane</td></tr>"
        "<tr><td><b>Ctrl+=</b></td><td>Zoom in (Decompile/Disasm/Hex)</td></tr>"
        "<tr><td><b>Ctrl+-</b></td><td>Zoom out (Decompile/Disasm/Hex)</td></tr>"
        "<tr><td><b>Ctrl+0</b></td><td>Reset pane zoom</td></tr>"
        "<tr><td><b>Ctrl+1</b></td><td>Focus Decompile dock</td></tr>"
        "<tr><td><b>Ctrl+2</b></td><td>Focus Disasm dock</td></tr>"
        "<tr><td><b>Ctrl+3</b></td><td>Focus Full Disasm dock</td></tr>"
        "<tr><td><b>Ctrl+4</b></td><td>Focus CFG dock</td></tr>"
        "<tr><td><b>Ctrl+5</b></td><td>Focus Hex dock</td></tr>"
        "<tr><td><b>Ctrl+/</b></td><td>This shortcuts dialog</td></tr>"
        "</table>"
        "<p><i>Drag-and-drop a binary onto the window to add it to the "
        "open project. Recent projects under File → Open Recent.</i></p>");
}

bool MainWindow::focusDock(int n) {
    QDockWidget* dock = nullptr;
    QWidget*     pane = nullptr;
    switch (n) {
        case 1:
            dock = m_decompileDock; pane = m_decompilePane;
            m_activeSearchScope = SearchScope::Decompile;
            break;
        case 2:
            dock = m_disasmDock; pane = m_disasmPane;
            m_activeSearchScope = SearchScope::Disassembly;
            break;
        case 3:
            dock = m_fullDisasmDock; pane = m_fullDisasmPane;
            m_activeSearchScope = SearchScope::FullDisassembly;
            break;
        case 4:
            dock = m_cfgDock; pane = m_cfgPane;
            m_activeSearchScope = SearchScope::CFG;
            break;
        case 5:
            dock = m_hexDock; pane = m_hexPane;
            m_activeSearchScope = SearchScope::Hex;
            break;
        default: return false;
    }
    if (!dock) return false;
    dock->raise();        // bring tab forward in tabified group
    dock->show();
    if (pane) pane->setFocus();
    return true;
}

void MainWindow::onShowKeyboardShortcuts() {
    QMessageBox box(this);
    box.setWindowTitle(QStringLiteral("Keyboard shortcuts"));
    box.setTextFormat(Qt::RichText);
    box.setText(keyboardShortcutsHtml());
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();
}

int MainWindow::findFunctionRowByName(const QString& needle) const {
    if (needle.isEmpty()) return -1;
    for (int i = 0; i < m_functions.size(); ++i) {
        if (m_functions[i].name.contains(needle, Qt::CaseInsensitive)) {
            return i;
        }
    }
    return -1;
}

void MainWindow::onFindInActiveScope() {
    const QString scope = searchScopeLabel(m_activeSearchScope);
    bool ok = false;
    const QString needle = QInputDialog::getText(
        this,
        useKoreanUi()
            ? QStringLiteral("찾기")
            : QStringLiteral("Find"),
        useKoreanUi()
            ? QStringLiteral("%1에서 찾을 문자열:").arg(scope)
            : QStringLiteral("Search %1 for:").arg(scope),
        QLineEdit::Normal, QString(), &ok);
    if (!ok) return;
    const QString trimmed = needle.trimmed();
    if (trimmed.isEmpty()) return;
    if (searchInScope(m_activeSearchScope, trimmed)) {
        statusBar()->showMessage(
            useKoreanUi()
                ? QStringLiteral("%1에서 '%2' 검색 결과로 이동").arg(scope, trimmed)
                : QStringLiteral("Found '%1' in %2").arg(trimmed, scope),
            3000);
        return;
    }
    statusBar()->showMessage(
        useKoreanUi()
            ? QStringLiteral("%1에서 '%2'를 찾지 못했습니다").arg(scope, trimmed)
            : QStringLiteral("No match for '%1' in %2").arg(trimmed, scope),
        4000);
}

void MainWindow::installSearchScope(QWidget* root, SearchScope scope) {
    if (!root) return;
    const QVariant value = static_cast<int>(scope);
    root->setProperty("auraSearchScope", value);
    root->installEventFilter(this);
    const auto children = root->findChildren<QWidget*>();
    for (QWidget* w : children) {
        if (!w) continue;
        w->setProperty("auraSearchScope", value);
        w->installEventFilter(this);
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event &&
        (event->type() == QEvent::FocusIn ||
         event->type() == QEvent::MouseButtonPress)) {
        const QVariant v = obj ? obj->property("auraSearchScope") : QVariant();
        if (v.isValid()) {
            m_activeSearchScope = static_cast<SearchScope>(v.toInt());
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

QString MainWindow::searchScopeLabel(SearchScope scope) const {
    const bool ko = useKoreanUi();
    switch (scope) {
        case SearchScope::Functions:
            return ko ? QStringLiteral("함수") : QStringLiteral("Functions");
        case SearchScope::Xrefs:
            return ko ? QStringLiteral("참조") : QStringLiteral("Xrefs");
        case SearchScope::Strings:
            return ko ? QStringLiteral("문자열") : QStringLiteral("Strings");
        case SearchScope::Symbols:
            return ko ? QStringLiteral("심볼") : QStringLiteral("Symbols");
        case SearchScope::Imports:
            return ko ? QStringLiteral("임포트") : QStringLiteral("Imports");
        case SearchScope::Decompile:
            return ko ? QStringLiteral("디컴파일") : QStringLiteral("Decompile");
        case SearchScope::Disassembly:
            return ko ? QStringLiteral("디스어셈블리") : QStringLiteral("Disassembly");
        case SearchScope::FullDisassembly:
            return ko ? QStringLiteral("전체 디스어셈블리") : QStringLiteral("Full Disassembly");
        case SearchScope::CFG:
            return QStringLiteral("CFG");
        case SearchScope::Hex:
            return ko ? QStringLiteral("헥스") : QStringLiteral("Hex");
    }
    return QStringLiteral("Search");
}

bool MainWindow::searchTreeView(QTreeView* view, const QString& needle) {
    if (!view || needle.isEmpty()) return false;
    QAbstractItemModel* model = view->model();
    if (!model) return false;

    const QModelIndex start = view->currentIndex();
    bool skipUntilStart = start.isValid();
    bool foundStart = !start.isValid();
    QModelIndex firstMatch;

    std::function<bool(const QModelIndex&)> visit = [&](const QModelIndex& parent) {
        const int rows = model->rowCount(parent);
        const int cols = model->columnCount(parent);
        for (int r = 0; r < rows; ++r) {
            const QModelIndex rowIndex = model->index(r, 0, parent);
            if (skipUntilStart && rowIndex == start) {
                foundStart = true;
                continue;
            }
            QString rowText;
            for (int c = 0; c < cols; ++c) {
                rowText += model->data(model->index(r, c, parent)).toString();
                rowText += QLatin1Char(' ');
            }
            if (foundStart &&
                rowText.contains(needle, Qt::CaseInsensitive)) {
                view->setCurrentIndex(rowIndex);
                view->scrollTo(rowIndex);
                return true;
            }
            if (!firstMatch.isValid() &&
                rowText.contains(needle, Qt::CaseInsensitive)) {
                firstMatch = rowIndex;
            }
            if (visit(rowIndex)) return true;
        }
        return false;
    };

    if (visit(QModelIndex())) return true;
    if (firstMatch.isValid()) {
        view->setCurrentIndex(firstMatch);
        view->scrollTo(firstMatch);
        return true;
    }
    return false;
}

bool MainWindow::searchPlainText(QPlainTextEdit* view,
                                 const QString& needle) {
    if (!view || needle.isEmpty()) return false;
    if (view->find(needle)) return true;
    QTextCursor c = view->textCursor();
    c.movePosition(QTextCursor::Start);
    view->setTextCursor(c);
    return view->find(needle);
}

QPlainTextEdit* MainWindow::activeTextEditIn(QWidget* pane) const {
    if (!pane) return nullptr;
    const auto edits = pane->findChildren<QPlainTextEdit*>();
    QPlainTextEdit* firstVisible = nullptr;
    for (QPlainTextEdit* edit : edits) {
        if (!edit || !edit->isVisible()) continue;
        if (!firstVisible) firstVisible = edit;
        if (edit->hasFocus()) return edit;
    }
    return firstVisible;
}

bool MainWindow::searchInScope(SearchScope scope, const QString& needle) {
    switch (scope) {
        case SearchScope::Functions:
            return searchTreeView(m_functionTable, needle);
        case SearchScope::Xrefs:
            return searchTreeView(m_xrefsTable, needle);
        case SearchScope::Strings:
            return searchTreeView(m_stringsTable, needle);
        case SearchScope::Symbols:
            return searchTreeView(m_symbolsTable, needle);
        case SearchScope::Imports:
            return searchTreeView(m_importsTable, needle);
        case SearchScope::Decompile:
            return searchPlainText(activeTextEditIn(m_decompilePane), needle);
        case SearchScope::Disassembly:
            return searchPlainText(activeTextEditIn(m_disasmPane), needle);
        case SearchScope::FullDisassembly:
            return searchPlainText(activeTextEditIn(m_fullDisasmPane), needle);
        case SearchScope::CFG:
            return searchPlainText(activeTextEditIn(m_cfgPane), needle);
        case SearchScope::Hex:
            return searchPlainText(activeTextEditIn(m_hexPane), needle);
    }
    return false;
}

void MainWindow::onGoToAddress() {
    if (m_functions.isEmpty()) {
        statusBar()->showMessage(
            QStringLiteral("No analyzed functions yet — run Analyze first"),
            4000);
        return;
    }
    bool ok = false;
    const QString text = QInputDialog::getText(
        this, QStringLiteral("Go to address"),
        QStringLiteral("function entry (hex, e.g. 0x401234):"),
        QLineEdit::Normal, QStringLiteral("0x"), &ok);
    if (!ok) return;
    const QString trimmed = text.trimmed();
    if (trimmed.isEmpty()) return;
    QString hex = trimmed;
    if (hex.startsWith(QStringLiteral("0x")) ||
        hex.startsWith(QStringLiteral("0X"))) {
        hex = hex.mid(2);
    }
    bool parsed = false;
    const quint64 addr = hex.toULongLong(&parsed, 16);
    if (!parsed) {
        statusBar()->showMessage(
            QStringLiteral("Invalid hex: %1").arg(text), 4000);
        return;
    }
    jumpToFunction(addr);
}

int MainWindow::handleDroppedPaths(const QStringList& paths) {
    if (!m_projectDb) {
        statusBar()->showMessage(
            QStringLiteral(
                "Drop ignored — open or create a project first "
                "(File → New / Open Project)."),
            5000);
        return 0;
    }
    int added = 0;
    int rejected = 0;
    for (const QString& p : paths) {
        const QFileInfo fi(p);
        if (!fi.exists() || !fi.isFile()) { ++rejected; continue; }
        if (addBinary(p)) ++added;
        else              ++rejected;
    }
    if (added > 0 && rejected == 0) {
        statusBar()->showMessage(
            QStringLiteral("Added %1 binary%2 via drag-drop.")
                .arg(added).arg(added == 1 ? "" : "(s)"),
            4000);
    } else if (added > 0) {
        statusBar()->showMessage(
            QStringLiteral("Added %1; %2 rejected (not a file).")
                .arg(added).arg(rejected),
            5000);
    } else if (rejected > 0) {
        statusBar()->showMessage(
            QStringLiteral("Drop rejected — %1 path(s) not a file.")
                .arg(rejected),
            5000);
    }
    return added;
}

bool MainWindow::openProject(const QString& path) {
    if (path.isEmpty()) return false;
    closeProject();

    const QByteArray pathUtf8 = path.toUtf8();
    AuraProjectBinaries* pb = aura_project_binaries_open(pathUtf8.constData());
    if (!pb) {
        QMessageBox::critical(this, QStringLiteral("Open Project"),
                              QStringLiteral("프로젝트 파일을 열 수 없습니다:\n%1")
                                  .arg(path));
        return false;
    }
    AuraOverrideStore* os = aura_override_store_open(pathUtf8.constData());
    if (!os) {
        aura_project_binaries_close(pb);
        QMessageBox::critical(this, QStringLiteral("Open Project"),
                              QStringLiteral("Override store 열기 실패:\n%1")
                                  .arg(path));
        return false;
    }

    m_projectDb     = pb;
    m_overrideStore = os;
    m_projectPath   = path;
    if (m_projectModel) m_projectModel->setRegistry(pb);
    if (m_actAddBinary) m_actAddBinary->setEnabled(true);
    if (m_analyzeButton) m_analyzeButton->setEnabled(true);
    updateWindowTitle();
    statusBar()->showMessage(
        QStringLiteral("프로젝트 로드됨: %1 — File → Add Binary 로 분석 대상 추가")
            .arg(path));
    switchToPage(PageProject);
    pushRecentProject(path);
    return true;
}

bool MainWindow::addBinary(const QString& binaryPath) {
    if (!m_projectDb) {
        QMessageBox::warning(this, QStringLiteral("Add Binary"),
                             QStringLiteral("프로젝트를 먼저 여세요."));
        return false;
    }
    if (binaryPath.isEmpty()) return false;

    const QByteArray pathUtf8 = binaryPath.toUtf8();

    uint8_t digest[AURA_SHA256_DIGEST_LEN];
    if (aura_sha256_file(pathUtf8.constData(), digest) != 0) {
        QMessageBox::critical(this, QStringLiteral("Add Binary"),
                              QStringLiteral("파일 해시 실패:\n%1").arg(binaryPath));
        return false;
    }
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1];
    aura_sha256_hex(digest, hex);

    QFileInfo fi(binaryPath);

    AuraProjectBinaryRecord rec;
    std::memset(&rec, 0, sizeof(rec));
    std::strncpy(rec.path, pathUtf8.constData(),
                 AURA_PROJECT_BINARY_PATH_CAP - 1);
    std::strncpy(rec.fingerprint, hex, AURA_PROJECT_BINARY_FINGERPRINT_LEN);
    rec.size             = fi.size();
    rec.added_at         = QDateTime::currentSecsSinceEpoch();
    rec.last_analyzed_at = 0;

    if (aura_project_binaries_put(m_projectDb, &rec) != 0) {
        QMessageBox::critical(this, QStringLiteral("Add Binary"),
                              QStringLiteral("DB 기록 실패:\n%1").arg(binaryPath));
        return false;
    }

    if (m_projectModel) m_projectModel->reload();
    statusBar()->showMessage(
        QStringLiteral("추가됨: %1 (sha256=%2…)")
            .arg(fi.fileName(), QString::fromLatin1(hex, 8)));
    return true;
}

int MainWindow::selectedProjectRow() const {
    if (!m_projectTable) return -1;
    const auto idx = m_projectTable->currentIndex();
    return idx.isValid() ? idx.row() : -1;
}

bool MainWindow::runAnalyze(int row, AuraAnalysisLevel level) {
    const auto* rec = m_projectModel ? m_projectModel->recordAt(row) : nullptr;
    if (!rec) return false;

    const QByteArray binaryPath = QByteArray(rec->path);
    m_currentBinaryPath = QString::fromUtf8(binaryPath);

    // Build binary fingerprint for override key derivation (Phase 4A.X1).
    {
        uint8_t digest[AURA_SHA256_DIGEST_LEN];
        if (aura_sha256_file(binaryPath.constData(), digest) == 0) {
            m_currentSha256 = QByteArray(reinterpret_cast<const char*>(digest),
                                         AURA_SHA256_DIGEST_LEN);
            std::memset(&m_currentFingerprint, 0, sizeof(m_currentFingerprint));
            m_currentFingerprint.file_size = rec->size;
            std::memcpy(m_currentFingerprint.sha256, digest,
                        AURA_SHA256_DIGEST_LEN);
            // format_kind / image_base / text_section_hash left as defaults
            // — fingerprint_match in Phase 4A only requires sha256+file_size.
            const QString lower = m_currentBinaryPath.toLower();
            const char* fmt =
                lower.endsWith(QStringLiteral(".exe")) ||
                lower.endsWith(QStringLiteral(".dll")) ? "pe"
                : lower.endsWith(QStringLiteral(".dylib")) ? "mach-o"
                : "elf";
            std::strncpy(m_currentFingerprint.format_kind, fmt,
                         sizeof(m_currentFingerprint.format_kind) - 1);
        }
    }

    statusBar()->showMessage(
        QStringLiteral("분석 중: %1 (%2)")
            .arg(QFileInfo(QString::fromUtf8(binaryPath)).fileName(),
                 level == AURA_ANALYSIS_LEVEL_QUICK
                     ? QStringLiteral("Quick aa")
                     : level == AURA_ANALYSIS_LEVEL_ADVANCED
                           ? QStringLiteral("Advanced aaaa")
                           : QStringLiteral("Full aaa")));
    if (m_analyzeButton) m_analyzeButton->setEnabled(false);
    QApplication::processEvents();

    AuraOrchestrator* orch = aura_orchestrator_create();
    if (!orch) {
        QMessageBox::critical(this, QStringLiteral("Analyze"),
                              QStringLiteral("orchestrator 생성 실패"));
        if (m_analyzeButton) m_analyzeButton->setEnabled(true);
        return false;
    }

    AuraRizinAdapterConfig cfg{};
    cfg.timeout_s = 60;
    const QByteArray rizinExec = resolveRizinExecForGui().toUtf8();
    if (!rizinExec.isEmpty()) cfg.exec_path = rizinExec.constData();
    if (aura_orchestrator_register_rizin(orch, &cfg) != 0) {
        aura_orchestrator_destroy(orch);
        QMessageBox::critical(
            this, QStringLiteral("Analyze"),
            QStringLiteral("Rizin adapter 등록 실패. AURA_RIZIN_BIN 확인."));
        if (m_analyzeButton) m_analyzeButton->setEnabled(true);
        return false;
    }

    AuraEngineRequest req{};
    req.type           = AURA_ENGINE_REQ_ANALYZE;
    req.binary_path    = binaryPath.constData();
    req.analysis_level = level;

    AuraEngineResponse resp{};
    AuraEngineStatus st = aura_orchestrator_dispatch(orch, "rizin", &req, &resp);

    bool ok = (st == AURA_ENGINE_OK && resp.body != nullptr);
    if (ok) {
        const auto* body = static_cast<const AuraRizinAnalyzeBody*>(resp.body);
        const AuraFunctionRecord* funcs =
            aura_rizin_analyze_body_functions(body);

        m_functions.clear();
        m_functions.reserve(static_cast<int>(body->functions_count));
        for (size_t i = 0; i < body->functions_count; ++i) {
            GuiFunctionRecord r;
            const QString engineName =
                QString::fromUtf8(funcs[i].name[0] ? funcs[i].name : "");
            r.originalName = engineName;
            r.name         = engineName;
            r.entry        = funcs[i].entry;
            r.size         = funcs[i].size;
            r.source       = QString::fromUtf8(funcs[i].provenance.source);
            r.functionId   = static_cast<quint64>(funcs[i].function_id);
            r.overridden   = false;
            m_functions.push_back(std::move(r));
        }

        // Phase 11.3.5: capture xrefs into the GUI list for RPC + dock.
        m_xrefs.clear();
        const AuraXrefRecord* xrs = aura_rizin_analyze_body_xrefs(body);
        m_xrefs.reserve(static_cast<int>(body->xrefs_count));
        for (size_t i = 0; xrs && i < body->xrefs_count; ++i) {
            GuiXrefRecord x;
            x.from = xrs[i].from_addr;
            x.to   = xrs[i].to_addr;
            switch (xrs[i].kind) {
            case AURA_XREF_DATA: x.kind = QStringLiteral("data"); break;
            case AURA_XREF_CODE: x.kind = QStringLiteral("code"); break;
            case AURA_XREF_CALL: x.kind = QStringLiteral("call"); break;
            default:             x.kind = QStringLiteral("unknown"); break;
            }
            x.source = QString::fromUtf8(xrs[i].provenance.source);
            m_xrefs.push_back(std::move(x));
        }
        if (m_xrefsModel) m_xrefsModel->setXrefs(m_xrefs);

        // Phase 11.3.5: capture symbols (incl. imports) into the GUI list.
        m_symbols.clear();
        const AuraSymbolRecord* ssr =
            aura_rizin_analyze_body_symbols(body);
        m_symbols.reserve(static_cast<int>(body->symbols_count));
        for (size_t i = 0; ssr && i < body->symbols_count; ++i) {
            GuiSymbolRecord s;
            s.addr = ssr[i].addr;
            switch (ssr[i].kind) {
            case AURA_SYMBOL_FUNCTION: s.kind = QStringLiteral("function"); break;
            case AURA_SYMBOL_OBJECT:   s.kind = QStringLiteral("object");   break;
            case AURA_SYMBOL_SECTION:  s.kind = QStringLiteral("section");  break;
            case AURA_SYMBOL_IMPORT:   s.kind = QStringLiteral("import");   break;
            default:                   s.kind = QStringLiteral("unknown"); break;
            }
            s.name   = QString::fromUtf8(ssr[i].name[0] ? ssr[i].name : "");
            s.source = QString::fromUtf8(ssr[i].provenance.source);
            m_symbols.push_back(std::move(s));
        }
        if (m_symbolsModel) m_symbolsModel->setSymbols(m_symbols);
        if (m_importsModel) m_importsModel->setSymbols(m_symbols);

        // Phase 11.3.6: capture literal strings (rizin izj) into the GUI list.
        m_strings.clear();
        const AuraStringRecord* str =
            aura_rizin_analyze_body_strings(body);
        m_strings.reserve(static_cast<int>(body->strings_count));
        const auto safetyProfile = aura::safety::loadDefaultSafetyProfile();
        for (size_t i = 0; str && i < body->strings_count; ++i) {
            GuiStringRecord s;
            s.stringId = str[i].string_id;
            s.addr     = str[i].addr;
            s.length   = str[i].length;
            switch (str[i].encoding) {
            case AURA_STRING_ENC_ASCII:   s.encoding = QStringLiteral("ascii");   break;
            case AURA_STRING_ENC_UTF8:    s.encoding = QStringLiteral("utf8");    break;
            case AURA_STRING_ENC_UTF16LE: s.encoding = QStringLiteral("utf16le"); break;
            case AURA_STRING_ENC_UTF16BE: s.encoding = QStringLiteral("utf16be"); break;
            case AURA_STRING_ENC_WIDE:    s.encoding = QStringLiteral("wide");    break;
            default:                      s.encoding = QStringLiteral("unknown"); break;
            }
            s.section = QString::fromUtf8(str[i].section[0] ? str[i].section : "");
            s.content = QString::fromUtf8(str[i].content[0] ? str[i].content : "");
            s.source  = QString::fromUtf8(str[i].provenance.source);

            auto findings = aura::safety::scanStringWithRulePacks(
                s.content.toStdString(), safetyProfile);
            const auto protectedView =
                aura::safety::buildProtectedStringView(s.content.toStdString(),
                                                       std::string(),
                                                       std::move(findings));
            s.maskedContent = QString::fromStdString(protectedView.masked);
            s.protectedValue =
                QString::fromStdString(protectedView.protected_value);
            s.hasProtection = !protectedView.findings.empty();
            for (const auto& f : protectedView.findings) {
                GuiStringRecord::ProtectionFinding gf;
                gf.detectorId = QString::fromStdString(f.detector_id);
                gf.kind = QString::fromStdString(f.kind);
                gf.startOffset = static_cast<int>(f.start);
                gf.endOffset = static_cast<int>(f.end);
                gf.confidence = f.confidence;
                gf.maskToken = QString::fromStdString(f.mask_token);
                s.findings.push_back(std::move(gf));
            }
            if (s.hasProtection) {
                QStringList tokens;
                for (const auto& f : s.findings) tokens << f.maskToken;
                tokens.removeDuplicates();
                s.protectionSummary =
                    useKoreanUi()
                        ? QStringLiteral("마스킹 가능: %1")
                              .arg(tokens.join(QStringLiteral(", ")))
                        : QStringLiteral("Maskable: %1")
                              .arg(tokens.join(QStringLiteral(", ")));
            }
            refreshProtectedValue(s);
            m_strings.push_back(std::move(s));
        }
        applyStoredStringOverrides(m_projectPath,
                                   currentFingerprintHex(m_currentSha256),
                                   &m_strings);
        if (m_stringsModel) m_stringsModel->setStrings(m_strings);
        persistStringProtectionRows(m_projectPath,
                                    currentFingerprintHex(m_currentSha256),
                                    m_strings);

        // Phase 11.4.3 (P4.PP1 C4): mirror call_edges / variables /
        // type_facts so generateTypePropagationCandidates can walk
        // them without keeping AuraEngineResponse alive.
        m_callEdges.clear();
        const AuraCallEdgeRecord* ces =
            aura_rizin_analyze_body_call_edges(body);
        m_callEdges.reserve(static_cast<int>(body->call_edges_count));
        for (size_t i = 0; ces && i < body->call_edges_count; ++i) {
            GuiCallEdgeRecord c;
            c.callerId = ces[i].caller_id;
            c.calleeId = ces[i].callee_id;
            c.siteAddr = ces[i].site_addr;
            m_callEdges.push_back(std::move(c));
        }
        m_variables.clear();
        const AuraVariableRecord* vrs =
            aura_rizin_analyze_body_variables(body);
        m_variables.reserve(static_cast<int>(body->variables_count));
        for (size_t i = 0; vrs && i < body->variables_count; ++i) {
            GuiVariableRecord v;
            v.varId       = vrs[i].var_id;
            v.functionId  = vrs[i].function_id;
            v.name        = QString::fromUtf8(vrs[i].name);
            v.kind        = QString::fromUtf8(vrs[i].kind);
            v.stackOffset = vrs[i].stack_offset;
            m_variables.push_back(std::move(v));
        }
        m_typeFacts.clear();
        const AuraTypeFactRecord* tfs =
            aura_rizin_analyze_body_type_facts(body);
        m_typeFacts.reserve(static_cast<int>(body->type_facts_count));
        for (size_t i = 0; tfs && i < body->type_facts_count; ++i) {
            GuiTypeFactRecord t;
            t.varId      = tfs[i].var_id;
            t.functionId = tfs[i].function_id;
            t.typeStr    = QString::fromUtf8(tfs[i].type_str);
            m_typeFacts.push_back(std::move(t));
        }

        // Phase 11.3.10 (P2.F5 C2): bind the hex pane to the binary
        // file (mmap, display-only path per ADR-0043 D1). Always reopen
        // on each analyze in case the same binary was re-added.
        if (m_hexPane && !m_currentBinaryPath.isEmpty()) {
            m_hexPane->openBinary(m_currentBinaryPath);
        }

        // Phase 11.3.8 (P2.F3 C2): mirror blocks + edges into the GUI
        // for CFG dock + RPC consumers. Per ADR-0041 D1, agfj is NOT
        // re-invoked — the analyze body already carries them.
        m_blocks.clear();
        const AuraBlockRecord* blk = aura_rizin_analyze_body_blocks(body);
        m_blocks.reserve(static_cast<int>(body->blocks_count));
        for (size_t i = 0; blk && i < body->blocks_count; ++i) {
            GuiBlockRecord b;
            b.blockId    = blk[i].block_id;
            b.functionId = blk[i].function_id;
            b.startAddr  = blk[i].start_addr;
            b.endAddr    = blk[i].end_addr;
            b.source     = QString::fromUtf8(blk[i].provenance.source);
            m_blocks.push_back(std::move(b));
        }
        m_edges.clear();
        const AuraEdgeRecord* eg = aura_rizin_analyze_body_edges(body);
        m_edges.reserve(static_cast<int>(body->edges_count));
        for (size_t i = 0; eg && i < body->edges_count; ++i) {
            GuiEdgeRecord e;
            e.srcBlock = eg[i].src_block;
            e.dstBlock = eg[i].dst_block;
            switch (eg[i].kind) {
            case AURA_EDGE_FALLTHROUGH:   e.kind = QStringLiteral("fallthrough");   break;
            case AURA_EDGE_JUMP:          e.kind = QStringLiteral("jump");          break;
            case AURA_EDGE_BRANCH_TRUE:   e.kind = QStringLiteral("branch_true");   break;
            case AURA_EDGE_BRANCH_FALSE:  e.kind = QStringLiteral("branch_false");  break;
            case AURA_EDGE_CALL:          e.kind = QStringLiteral("call");          break;
            case AURA_EDGE_RETURN:        e.kind = QStringLiteral("return");        break;
            default:                       e.kind = QStringLiteral("unknown");       break;
            }
            e.source = QString::fromUtf8(eg[i].provenance.source);
            m_edges.push_back(std::move(e));
        }

        if (m_projectDb) {
            aura_project_binaries_mark_analyzed(
                m_projectDb, rec->fingerprint,
                QDateTime::currentSecsSinceEpoch());
            if (m_projectModel) m_projectModel->reload();
        }
    }

    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);

    if (m_analyzeButton) m_analyzeButton->setEnabled(true);

    if (!ok) {
        QMessageBox::critical(
            this, QStringLiteral("Analyze"),
            QStringLiteral("분석 실패 (status=%1).").arg(static_cast<int>(st)));
        statusBar()->showMessage(QStringLiteral("분석 실패."));
        return false;
    }

    statusBar()->showMessage(
        QStringLiteral("분석 완료: 함수 %1개").arg(m_functions.size()));

    if (m_decompilePane) {
        m_decompilePane->clearCache();
    }

    // Phase 11.3.4: eager batch decompile. Single Rizin invocation
    // populates DecompilePane cache for every analyzed function so
    // subsequent row clicks are instant cache hits.
    if (m_decompilePane && !m_functions.isEmpty()) {
        const int N = m_functions.size();
        statusBar()->showMessage(
            QStringLiteral("Decompile (batch): %1 함수 일괄 처리 중...").arg(N));
        QApplication::processEvents();

        QVector<quint64> addrs;
        addrs.reserve(N);
        for (const auto& fn : m_functions) addrs.push_back(fn.entry);

        QVector<AuraRizinDecompileBody*> bodies(N, nullptr);
        uint32_t backend_used = AURA_RIZIN_DEC_BACKEND_NONE;
        const QByteArray batchRizinExec = resolveRizinExecForGui().toUtf8();
        const char* exec = batchRizinExec.isEmpty()
            ? nullptr
            : batchRizinExec.constData();
        const QByteArray binPathUtf8 = m_currentBinaryPath.toUtf8();
        // Generous timeout — N functions × ~0.1s each + aaa pass.
        const int batchTimeout = std::max(60, 30 + N / 10);
        int rc = aura_rizin_decompile_batch_run(
            exec, binPathUtf8.constData(),
            reinterpret_cast<const uint64_t*>(addrs.constData()),
            static_cast<size_t>(N),
            batchTimeout,
            bodies.data(),
            &backend_used);

        int filled = 0;
        if (rc == 0) {
            const QString label = backendLabel(backend_used);
            for (int i = 0; i < N; ++i) {
                if (!bodies[i]) continue;
                const char* btext = aura_rizin_decompile_body_text(bodies[i]);
                // Phase 11.3.7 (P2.F2 C4): also stash the line map so
                // cursor-clicks in DecompilePane resolve to addresses.
                const auto* lm =
                    aura_rizin_decompile_body_line_map(bodies[i]);
                DecompileLineAddrMap lineMap;
                for (size_t k = 0; lm && k < bodies[i]->line_map_count; ++k) {
                    lineMap.insert(static_cast<int>(lm[k].line),
                                   lm[k].addr);
                }
                m_decompilePane->cache(addrs[i], label,
                                       QString::fromUtf8(btext ? btext : ""),
                                       lineMap);
                std::free(bodies[i]);
                bodies[i] = nullptr;
                ++filled;
            }
        }
        // Free any orphans on error.
        for (auto* b : bodies) if (b) std::free(b);

        statusBar()->showMessage(
            QStringLiteral("분석 완료: 함수 %1개 (decompile cache: %2/%1)")
                .arg(N).arg(filled));
        m_decompilePane->showPlaceholder(
            QStringLiteral("// 좌측 함수 목록에서 함수를 선택하세요."));
    }

    // Apply existing overrides (rename) before pushing to the model.
    applyOverridesToFunctions();

    if (m_functionModel) m_functionModel->setFunctions(m_functions);

    if (m_fullDisasmPane) {
        QHash<quint64, QString> labels;
        labels.reserve(m_functions.size());
        for (const auto& f : m_functions) {
            labels.insert(f.entry, f.name);
        }
        m_fullDisasmPane->setFunctionLabels(labels);
        runFullDisasmOverview();
    }

    // Wire selection → decompile (re-bind every analyze, since model reset
    // recreates the selection model).
    if (m_functionTable && m_functionTable->selectionModel()) {
        connect(m_functionTable->selectionModel(),
                &QItemSelectionModel::currentRowChanged,
                this, &MainWindow::onFunctionRowSelected,
                Qt::UniqueConnection);
    }
    if (m_stringsTable && m_stringsTable->selectionModel()) {
        connect(m_stringsTable->selectionModel(),
                &QItemSelectionModel::currentRowChanged,
                this, &MainWindow::onStringCurrentRowChanged,
                Qt::UniqueConnection);
    }

    if (m_actBackToProject) m_actBackToProject->setEnabled(true);
    switchToPage(PageFunction);
    return true;
}

bool MainWindow::analyzeBinaryAt(int row, AuraAnalysisLevel level) {
    return runAnalyze(row, level);
}

bool MainWindow::runDecompile(quint64 funcAddr) {
    if (m_currentBinaryPath.isEmpty() || !m_decompilePane) return false;

    if (m_decompilePane->hasCached(funcAddr)) {
        m_decompilePane->showDecompile(funcAddr,
                                       m_decompilePane->cachedBackend(funcAddr),
                                       m_decompilePane->cachedText(funcAddr));
        return true;
    }

    statusBar()->showMessage(
        QStringLiteral("Decompile 중: 0x%1").arg(funcAddr, 0, 16));
    m_decompilePane->showPlaceholder(QStringLiteral("// 디컴파일 중..."));
    QApplication::processEvents();

    AuraOrchestrator* orch = aura_orchestrator_create();
    if (!orch) return false;

    AuraRizinAdapterConfig cfg{};
    cfg.timeout_s = 60;
    const QByteArray rizinExec = resolveRizinExecForGui().toUtf8();
    if (!rizinExec.isEmpty()) cfg.exec_path = rizinExec.constData();
    if (aura_orchestrator_register_rizin(orch, &cfg) != 0) {
        aura_orchestrator_destroy(orch);
        m_decompilePane->showPlaceholder(
            QStringLiteral("// Rizin adapter 등록 실패."));
        return false;
    }

    const QByteArray binaryPath = m_currentBinaryPath.toUtf8();
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_DECOMPILE;
    req.binary_path = binaryPath.constData();
    req.addr        = funcAddr;

    AuraEngineResponse resp{};
    AuraEngineStatus st =
        aura_orchestrator_dispatch(orch, "rizin", &req, &resp);

    bool ok = (st == AURA_ENGINE_OK && resp.body != nullptr);
    QString text;
    QString backend;
    DecompileLineAddrMap lineMap;
    if (ok) {
        const auto* body =
            static_cast<const AuraRizinDecompileBody*>(resp.body);
        const char* btext = aura_rizin_decompile_body_text(body);
        text    = QString::fromUtf8(btext ? btext : "");
        backend = backendLabel(body->backend);
        // Phase 11.3.7 (P2.F2 C4): capture line map for cursor → addr.
        const auto* lm = aura_rizin_decompile_body_line_map(body);
        for (size_t k = 0; lm && k < body->line_map_count; ++k) {
            lineMap.insert(static_cast<int>(lm[k].line), lm[k].addr);
        }
    }

    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);

    if (!ok || text.isEmpty()) {
        const QString msg =
            QStringLiteral(
                "// 디컴파일을 사용할 수 없습니다 (status=%1).\n"
                "//\n"
                "// Rizin 에 디컴파일 플러그인이 설치되지 않았을 수 있습니다.\n"
                "// 설치 방법 (rz-pm 필요):\n"
                "//   rz-pm install rz-ghidra        # rz-ghidra (pdgj) — 추천\n"
                "//   rz-pm install jsdec            # jsdec (pddj) — 대체\n"
                "//\n"
                "// 또는 시스템 패키지로 설치 (배포판에 따라 다름):\n"
                "//   apt install rizin-plugins\n")
                .arg(static_cast<int>(st));
        m_decompilePane->showPlaceholder(msg);
        statusBar()->showMessage(
            QStringLiteral("Decompile 사용 불가: 0x%1 (플러그인 미설치)")
                .arg(funcAddr, 0, 16));
        // Cache the placeholder too — same function won't keep dispatching.
        m_decompilePane->cache(funcAddr, QStringLiteral("unavailable"), msg);
        return false;
    }

    m_decompilePane->cache(funcAddr, backend, text, lineMap);
    m_decompilePane->showDecompile(funcAddr, backend, text);
    statusBar()->showMessage(
        QStringLiteral("Decompile 완료: 0x%1 [%2]")
            .arg(funcAddr, 0, 16)
            .arg(backend));
    return true;
}

bool MainWindow::decompileFunctionAt(int functionRow) {
    if (functionRow < 0 || functionRow >= m_functions.size()) return false;
    return runDecompile(m_functions[functionRow].entry);
}

bool MainWindow::disassembleFunctionAt(int functionRow) {
    if (functionRow < 0 || functionRow >= m_functions.size()) return false;
    return runDisasm(m_functions[functionRow].entry);
}

void MainWindow::onFunctionRowSelected(const QModelIndex& current,
                                       const QModelIndex& /*previous*/) {
    if (!current.isValid()) return;
    const int row = m_functionModel
        ? m_functionModel->functionRowForIndex(current)
        : current.row();
    if (row < 0 || row >= m_functions.size()) return;
    const quint64 addr = m_functions[row].entry;
    // Phase 11.3.9 (P2.F4 C3): nav history. push prior addr to back,
    // clear forward (browser-standard non-linear nav invalidates
    // forward). Skip when a goBack/goForward action drove this select
    // (m_navInProgress=true) — that path manipulates the stacks
    // explicitly in goBack/goForward themselves.
    if (!m_navInProgress && m_activeFunctionAddr != 0
        && m_activeFunctionAddr != addr) {
        m_navBack.push(m_activeFunctionAddr);
        m_navForward.clear();
        if (m_actNavBack)    m_actNavBack->setEnabled(true);
        if (m_actNavForward) m_actNavForward->setEnabled(false);
    }
    m_activeFunctionAddr = addr;  // Phase 11.3.9: track for context menu
    if (m_fullDisasmPane) m_fullDisasmPane->setStartAddress(addr);
    runDecompile(addr);
    // Phase 11.3.7: also populate the Disassembly tab. Cache hits make
    // subsequent row clicks instant.
    runDisasm(addr);
    // Phase 11.3.8 (P2.F3 C2): populate the CFG dock. CFG data is
    // already in m_blocks/m_edges from analyze; just filter + show.
    if (m_cfgPane) {
        const auto bs = blocksForFunction(addr);
        const auto es = edgesForBlocks(bs);
        m_cfgPane->showCfg(addr, bs, es);
    }
}

void MainWindow::onStringRowActivated(const QModelIndex& current) {
    const int row = m_stringsModel
        ? m_stringsModel->stringRowForIndex(current)
        : current.row();
    jumpToStringReference(row);
}

void MainWindow::onStringCurrentRowChanged(const QModelIndex& current,
                                           const QModelIndex& /*previous*/) {
    onStringRowActivated(current);
}

void MainWindow::onStringContextMenu(const QPoint& pos) {
    if (!m_stringsTable || !m_stringsModel) return;
    const QModelIndex idx = m_stringsTable->indexAt(pos);
    const int row = m_stringsModel->stringRowForIndex(idx);
    if (row < 0 || row >= m_strings.size()) return;
    m_stringsTable->setCurrentIndex(idx);

    QMenu menu(this);
    QAction* setAlias = menu.addAction(
        useKoreanUi() ? QStringLiteral("별칭 설정...")
                      : QStringLiteral("Set alias..."));
    QAction* setMask = menu.addAction(
        useKoreanUi() ? QStringLiteral("마스킹 토큰 설정...")
                      : QStringLiteral("Set mask token..."));

    QMenu* displayMenu = menu.addMenu(
        useKoreanUi() ? QStringLiteral("보호 표시값")
                      : QStringLiteral("Protected display value"));
    QAction* useOriginal = displayMenu->addAction(
        useKoreanUi() ? QStringLiteral("기존") : QStringLiteral("Original"));
    QAction* useAlias = displayMenu->addAction(
        useKoreanUi() ? QStringLiteral("별칭") : QStringLiteral("Alias"));
    QAction* useMasked = displayMenu->addAction(
        useKoreanUi() ? QStringLiteral("마스킹") : QStringLiteral("Masked"));

    QAction* chosen = menu.exec(m_stringsTable->viewport()->mapToGlobal(pos));
    if (!chosen) return;

    if (chosen == setAlias) {
        bool ok = false;
        const QString value = QInputDialog::getText(
            this,
            useKoreanUi() ? QStringLiteral("별칭 설정")
                          : QStringLiteral("Set alias"),
            useKoreanUi() ? QStringLiteral("별칭:")
                          : QStringLiteral("Alias:"),
            QLineEdit::Normal,
            m_strings[row].alias,
            &ok);
        if (ok) setStringAliasAt(row, value);
        return;
    }
    if (chosen == setMask) {
        bool ok = false;
        const QString value = QInputDialog::getText(
            this,
            useKoreanUi() ? QStringLiteral("마스킹 토큰 설정")
                          : QStringLiteral("Set mask token"),
            useKoreanUi() ? QStringLiteral("마스킹 토큰:")
                          : QStringLiteral("Mask token:"),
            QLineEdit::Normal,
            m_strings[row].maskedContent,
            &ok);
        if (ok) setStringMaskTokenAt(row, value);
        return;
    }
    if (chosen == useOriginal) setStringDisplayModeAt(row, 0);
    if (chosen == useAlias) setStringDisplayModeAt(row, 1);
    if (chosen == useMasked) setStringDisplayModeAt(row, 2);
}

QVector<GuiInstructionRecord>
MainWindow::disasmList(quint64 funcAddr) const {
    if (!m_disasmPane) return {};
    return m_disasmPane->cached(funcAddr);
}

// Phase 11.3.8 (P2.F3 C2): filter the analyze-time block mirror by the
// function whose entry == funcAddr. function_id resolution: walk
// m_functions to find the matching id; then keep blocks whose
// function_id equals that. Empty input → empty output.
QVector<GuiBlockRecord>
MainWindow::blocksForFunction(quint64 funcAddr) const {
    quint32 fid = 0;
    for (const auto& f : m_functions) {
        if (f.entry == funcAddr) { fid = static_cast<quint32>(f.functionId); break; }
    }
    QVector<GuiBlockRecord> out;
    if (fid == 0) return out;
    for (const auto& b : m_blocks) {
        if (b.functionId == fid) out.push_back(b);
    }
    return out;
}

QVector<GuiEdgeRecord>
MainWindow::edgesForBlocks(const QVector<GuiBlockRecord>& blocks) const {
    if (blocks.isEmpty()) return {};
    QSet<quint32> ids;
    for (const auto& b : blocks) ids.insert(b.blockId);
    QVector<GuiEdgeRecord> out;
    for (const auto& e : m_edges) {
        // An edge belongs to this function's CFG iff both endpoints are
        // in the function's block set. (Inter-function edges live in
        // call_edges[], not edges[].)
        if (ids.contains(e.srcBlock) && ids.contains(e.dstBlock)) {
            out.push_back(e);
        }
    }
    return out;
}

QString MainWindow::disasmArrowText(quint64 funcAddr) const {
    if (!m_disasmPane) return QString();
    return m_disasmPane->cachedArrowText(funcAddr);
}

// ── Phase 11.6 T2 C1 — flow-arrow descriptors + lane assignment ─────────
//
// Pure data layer: reads InstructionRecord.type / jump / fail to
// classify jumps, resolves dst line via addr lookup, then runs a
// greedy lane-assignment pass so the gutter painter can render
// non-overlapping vertical lanes for each arrow.

QVector<GuiFlowArrow>
MainWindow::computeFlowArrows(const QVector<GuiInstructionRecord>& ins) {
    QVector<GuiFlowArrow> arrows;
    if (ins.isEmpty()) return arrows;

    // Build addr → line index map (single pass, O(N)).
    QHash<quint64, int> addrToLine;
    addrToLine.reserve(ins.size());
    for (int i = 0; i < ins.size(); ++i) {
        addrToLine.insert(ins[i].addr, i);
    }

    auto resolveDst = [&](quint64 dst) -> int {
        if (dst == 0) return -1;
        auto it = addrToLine.constFind(dst);
        return (it == addrToLine.constEnd()) ? -1 : it.value();
    };

    auto classifyKind = [](const QString& type) -> QString {
        // rizin "type" values: jmp, ujmp, cjmp, call, ucall, ret, mov, ...
        if (type == QLatin1String("jmp") ||
            type == QLatin1String("ujmp")) return QStringLiteral("uncond");
        if (type == QLatin1String("cjmp") ||
            type == QLatin1String("ucjmp")) return QStringLiteral("cond_true");
        if (type == QLatin1String("call") ||
            type == QLatin1String("ucall")) return QStringLiteral("call");
        return QString();  // not a flow-affecting op
    };

    for (int i = 0; i < ins.size(); ++i) {
        const auto& r = ins[i];
        const QString k = classifyKind(r.type);
        if (k.isEmpty()) continue;

        if (k == QStringLiteral("cond_true")) {
            // Conditional: TRUE edge to jump, FALSE edge to fail (or fall-through).
            if (r.jump != 0) {
                GuiFlowArrow a;
                a.srcAddr = r.addr;
                a.dstAddr = r.jump;
                a.srcLine = i;
                a.dstLine = resolveDst(r.jump);
                a.kind    = QStringLiteral("cond_true");
                a.direction = (a.dstLine < 0) ? 0
                              : (a.dstLine > a.srcLine ? +1 : -1);
                arrows.push_back(std::move(a));
            }
            // FALSE edge — only emit when fail is non-default (rizin
            // sometimes leaves fail=0 even though next-ix is implicit).
            if (r.fail != 0 && r.fail != r.jump) {
                GuiFlowArrow a;
                a.srcAddr = r.addr;
                a.dstAddr = r.fail;
                a.srcLine = i;
                a.dstLine = resolveDst(r.fail);
                a.kind    = QStringLiteral("cond_false");
                a.direction = (a.dstLine < 0) ? 0
                              : (a.dstLine > a.srcLine ? +1 : -1);
                arrows.push_back(std::move(a));
            }
        } else {
            if (r.jump == 0) continue;
            GuiFlowArrow a;
            a.srcAddr = r.addr;
            a.dstAddr = r.jump;
            a.srcLine = i;
            a.dstLine = resolveDst(r.jump);
            a.kind    = k;
            a.direction = (a.dstLine < 0) ? 0
                          : (a.dstLine > a.srcLine ? +1 : -1);
            arrows.push_back(std::move(a));
        }
    }
    return arrows;
}

void MainWindow::assignFlowArrowLanes(QVector<GuiFlowArrow>& arrows,
                                      int maxLanes) {
    if (arrows.isEmpty()) return;
    if (maxLanes <= 0) maxLanes = 8;

    // Filter to in-function arrows only (those with both src + dst
    // resolved). Out-of-function arrows skip the lane lottery — they
    // paint as edge stubs at lane 0.
    struct IndexedArrow {
        int idx;        // index into the input vector
        int lo, hi;     // inclusive line range
    };
    QVector<IndexedArrow> live;
    live.reserve(arrows.size());
    for (int i = 0; i < arrows.size(); ++i) {
        const auto& a = arrows[i];
        if (a.dstLine < 0) continue;  // overflow / off-func — handled later
        IndexedArrow ia;
        ia.idx = i;
        ia.lo  = qMin(a.srcLine, a.dstLine);
        ia.hi  = qMax(a.srcLine, a.dstLine);
        live.push_back(ia);
    }
    // Shorter arrows get smaller lanes — they fit easier.
    std::sort(live.begin(), live.end(),
              [](const IndexedArrow& x, const IndexedArrow& y) {
                  int dx = x.hi - x.lo;
                  int dy = y.hi - y.lo;
                  if (dx != dy) return dx < dy;
                  return x.lo < y.lo;
              });

    // Per-lane occupancy: list of (lo, hi) ranges already taken.
    QVector<QVector<QPair<int, int>>> occupancy(maxLanes);

    for (const auto& ia : live) {
        int chosen = -1;
        for (int lane = 0; lane < maxLanes; ++lane) {
            bool clash = false;
            for (const auto& range : occupancy[lane]) {
                // Overlap iff !(hi < r.lo || lo > r.hi).
                if (!(ia.hi < range.first || ia.lo > range.second)) {
                    clash = true; break;
                }
            }
            if (!clash) { chosen = lane; break; }
        }
        arrows[ia.idx].lane = chosen;  // -1 if no lane fit
        if (chosen >= 0) {
            occupancy[chosen].push_back({ia.lo, ia.hi});
        }
    }
}

bool MainWindow::runDisasm(quint64 funcAddr) {
    if (m_currentBinaryPath.isEmpty() || !m_disasmPane) return false;

    if (m_disasmPane->hasCached(funcAddr)) {
        m_disasmPane->showDisasm(funcAddr, m_disasmPane->cached(funcAddr));
        // Phase 11.6 T1 C2: re-publish cached arrow text on cache hit
        // so toggling between functions keeps the arrow tab in sync.
        m_disasmPane->setArrowText(funcAddr,
            m_disasmPane->cachedArrowText(funcAddr));
        return true;
    }

    AuraOrchestrator* orch = aura_orchestrator_create();
    if (!orch) return false;

    AuraRizinAdapterConfig cfg{};
    cfg.timeout_s = 60;
    const QByteArray rizinExec = resolveRizinExecForGui().toUtf8();
    if (!rizinExec.isEmpty()) cfg.exec_path = rizinExec.constData();
    if (aura_orchestrator_register_rizin(orch, &cfg) != 0) {
        aura_orchestrator_destroy(orch);
        return false;
    }

    const QByteArray binaryPath = m_currentBinaryPath.toUtf8();
    AuraEngineRequest req{};
    req.type        = AURA_ENGINE_REQ_DISASM;
    req.binary_path = binaryPath.constData();
    req.addr        = funcAddr;

    AuraEngineResponse resp{};
    AuraEngineStatus st =
        aura_orchestrator_dispatch(orch, "rizin", &req, &resp);

    QVector<GuiInstructionRecord> ins;
    QString arrowText;  // Phase 11.6 T1 C2: pdf annotated text
    bool ok = (st == AURA_ENGINE_OK && resp.body != nullptr);
    if (ok) {
        const auto* body =
            static_cast<const AuraRizinDisasmBody*>(resp.body);
        const AuraInstructionRecord* arr =
            aura_rizin_disasm_body_instructions(body);
        ins.reserve(static_cast<int>(body->instructions_count));
        for (size_t i = 0; arr && i < body->instructions_count; ++i) {
            GuiInstructionRecord r;
            r.addr     = arr[i].addr;
            r.size     = arr[i].size;
            r.bytes    = QString::fromUtf8(arr[i].bytes);
            r.mnemonic = QString::fromUtf8(arr[i].mnemonic);
            r.opStr    = QString::fromUtf8(arr[i].op_str);
            r.type     = QString::fromUtf8(arr[i].type);
            r.jump     = arr[i].jump;
            r.fail     = arr[i].fail;
            r.source   = QString::fromUtf8(arr[i].provenance.source);
            ins.push_back(std::move(r));
        }
        const char* txt = aura_rizin_disasm_body_text(body);
        if (txt) arrowText = QString::fromUtf8(txt);
    }

    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);

    if (!ok) {
        m_disasmPane->showPlaceholder(
            QStringLiteral("// Disassembly 사용 불가 (status=%1)").arg(
                static_cast<int>(st)));
        return false;
    }

    m_disasmPane->cache(funcAddr, ins);
    m_disasmPane->showDisasm(funcAddr, ins);
    m_disasmPane->setArrowText(funcAddr, arrowText);
    return true;
}

bool MainWindow::runFullDisasmWindow(quint64 addr, int count) {
    if (m_currentBinaryPath.isEmpty() || !m_fullDisasmPane) return false;
    if (count <= 0) count = 128;
    if (count > 256) count = 256;

    statusBar()->showMessage(
        QStringLiteral("전체 디스어셈블리 로드 중: 0x%1").arg(addr, 0, 16));
    m_fullDisasmPane->showPlaceholder(QStringLiteral("// 전체 디스어셈블리 로드 중..."));
    QApplication::processEvents();

    AuraOrchestrator* orch = aura_orchestrator_create();
    if (!orch) return false;

    AuraRizinAdapterConfig cfg{};
    cfg.timeout_s = 60;
    const QByteArray rizinExec = resolveRizinExecForGui().toUtf8();
    if (!rizinExec.isEmpty()) cfg.exec_path = rizinExec.constData();
    if (aura_orchestrator_register_rizin(orch, &cfg) != 0) {
        aura_orchestrator_destroy(orch);
        m_fullDisasmPane->showPlaceholder(
            QStringLiteral("// Rizin adapter 등록 실패."));
        return false;
    }

    AuraRizinDisasmOptions opts{};
    opts.mode = AURA_RIZIN_DISASM_MODE_WINDOW;
    opts.instruction_count = static_cast<uint32_t>(count);

    const QByteArray binaryPath = m_currentBinaryPath.toUtf8();
    AuraEngineRequest req{};
    req.type         = AURA_ENGINE_REQ_DISASM;
    req.binary_path  = binaryPath.constData();
    req.addr         = addr;
    req.payload      = &opts;
    req.payload_size = sizeof(opts);

    AuraEngineResponse resp{};
    AuraEngineStatus st =
        aura_orchestrator_dispatch(orch, "rizin", &req, &resp);

    QVector<GuiInstructionRecord> ins;
    QString arrowText;
    const bool ok = (st == AURA_ENGINE_OK && resp.body != nullptr);
    if (ok) {
        const auto* body =
            static_cast<const AuraRizinDisasmBody*>(resp.body);
        const AuraInstructionRecord* arr =
            aura_rizin_disasm_body_instructions(body);
        ins.reserve(static_cast<int>(body->instructions_count));
        for (size_t i = 0; arr && i < body->instructions_count; ++i) {
            GuiInstructionRecord r;
            r.addr     = arr[i].addr;
            r.size     = arr[i].size;
            r.bytes    = QString::fromUtf8(arr[i].bytes);
            r.mnemonic = QString::fromUtf8(arr[i].mnemonic);
            r.opStr    = QString::fromUtf8(arr[i].op_str);
            r.type     = QString::fromUtf8(arr[i].type);
            r.jump     = arr[i].jump;
            r.fail     = arr[i].fail;
            r.source   = QString::fromUtf8(arr[i].provenance.source);
            ins.push_back(std::move(r));
        }
        const char* bodyText = aura_rizin_disasm_body_text(body);
        if (bodyText) {
            arrowText = QString::fromUtf8(bodyText);
        }
    }

    aura_engine_response_dispose(&resp);
    aura_orchestrator_destroy(orch);

    if (!ok) {
        m_fullDisasmPane->showPlaceholder(
            QStringLiteral("// 전체 디스어셈블리 사용 불가 (status=%1)")
                .arg(static_cast<int>(st)));
        return false;
    }

    if (arrowText.isEmpty()) {
        m_fullDisasmPane->showInstructions(addr, count, ins);
    } else {
        m_fullDisasmPane->showMixedListing(addr, count, arrowText, ins);
    }
    m_fullDisasmPane->setArrowText(addr, arrowText);
    statusBar()->showMessage(
        QStringLiteral("전체 디스어셈블리 완료: 0x%1 (%2 instructions)")
            .arg(addr, 0, 16)
            .arg(ins.size()));
    return true;
}

bool MainWindow::runFullDisasmOverview() {
    if (m_functions.isEmpty()) {
        if (m_fullDisasmPane) {
            m_fullDisasmPane->showPlaceholder(
                QStringLiteral("// 분석된 함수가 없습니다."));
        }
        return false;
    }
    quint64 base = m_functions.first().entry;
    for (const auto& f : m_functions) {
        if (f.entry != 0 && f.entry < base) base = f.entry;
    }
    const quint64 align = (base >= 0x100000ull) ? 0x100000ull : 0x1000ull;
    base &= ~(align - 1ull);
    /* Cutter-style full disassembly is a browsable text window, not a
     * one-shot whole-binary dump. Rizin 0.8.0 `pD` gets expensive quickly on
     * some PE images because it preserves labels/comments/invalid lines, so
     * initial load stays close to the current viewport and later paging can
     * extend it in small chunks.
     */
    return runFullDisasmWindow(base, 128);
}

void MainWindow::onAnalyzeClicked() {
    const int row = selectedProjectRow();
    if (row < 0) {
        QMessageBox::information(this, QStringLiteral("Analyze"),
                                 QStringLiteral("분석할 binary 행을 먼저 선택하세요."));
        return;
    }
    const auto* rec = m_projectModel ? m_projectModel->recordAt(row) : nullptr;
    if (!rec) return;

    AnalysisOptionsDialog dlg(QString::fromUtf8(rec->path), this);
    if (dlg.exec() != QDialog::Accepted) return;
    runAnalyze(row, dlg.selectedLevel());
}

void MainWindow::onTableDoubleClicked(const QModelIndex& idx) {
    if (!idx.isValid()) return;
    const auto* rec = m_projectModel ? m_projectModel->recordAt(idx.row()) : nullptr;
    if (!rec) return;
    AnalysisOptionsDialog dlg(QString::fromUtf8(rec->path), this);
    if (dlg.exec() != QDialog::Accepted) return;
    runAnalyze(idx.row(), dlg.selectedLevel());
}

void MainWindow::onNewProject() {
    const QString path = QFileDialog::getSaveFileName(
        this, QStringLiteral("New Project"),
        QString(),
        QStringLiteral("AURA Project (*.aura.db)"));
    if (path.isEmpty()) return;

    QString finalPath = path;
    if (!finalPath.endsWith(QStringLiteral(".aura.db"),
                            Qt::CaseInsensitive)) {
        finalPath += QStringLiteral(".aura.db");
    }
    openProject(finalPath);
}

void MainWindow::onOpenProject() {
    const QString path = QFileDialog::getOpenFileName(
        this, QStringLiteral("Open Project"),
        QString(),
        QStringLiteral("AURA Project (*.aura.db);;All files (*)"));
    if (path.isEmpty()) return;
    openProject(path);
}

void MainWindow::onAddBinary() {
    const QString path = QFileDialog::getOpenFileName(
        this, QStringLiteral("Add Binary"),
        QString(),
        QStringLiteral("Binaries (*.elf *.exe *.dll *.so *.dylib);;"
                       "All files (*)"));
    if (path.isEmpty()) return;
    addBinary(path);
}

// ── Override editor (Phase 11.3.2 / ADR-0037) ─────────────────────────

AuraOverrideKey MainWindow::buildKeyForFunction(int row) const {
    AuraOverrideKey k{};
    if (row < 0 || row >= m_functions.size()) return k;
    const GuiFunctionRecord& f = m_functions[row];

    // Reconstruct an AuraFunctionRecord (just enough for key derivation).
    AuraFunctionRecord rec{};
    rec.function_id = static_cast<AuraFunctionId>(f.functionId);
    rec.entry       = f.entry;
    rec.size        = f.size;
    const QByteArray name = f.originalName.toUtf8();
    std::strncpy(rec.name, name.constData(), sizeof(rec.name) - 1);
    const QByteArray src = f.source.toUtf8();
    std::strncpy(rec.provenance.source, src.constData(),
                 sizeof(rec.provenance.source) - 1);
    rec.provenance.confidence   = 1.0f;
    rec.provenance.completeness = 1.0f;

    const AuraEngineManifest* manifest = aura_rizin_adapter_manifest();
    return aura_override_key_from_function_record(&rec, manifest,
                                                  &m_currentFingerprint);
}

void MainWindow::applyOverridesToFunctions() {
    if (!m_overrideStore) return;
    for (int i = 0; i < m_functions.size(); ++i) {
        AuraOverrideKey key = buildKeyForFunction(i);
        AuraOverrideRecord rec{};
        int rc = aura_override_store_get(m_overrideStore, &key, &rec);
        if (rc == 0 && rec.payload.kind == AURA_OVERRIDE_PAYLOAD_RENAME) {
            m_functions[i].name       = QString::fromUtf8(rec.payload.text);
            m_functions[i].source     = QStringLiteral("user/rename");
            m_functions[i].overridden = true;
        } else {
            m_functions[i].name       = m_functions[i].originalName;
            m_functions[i].overridden = false;
        }
    }
}

bool MainWindow::renameFunctionAt(int row, const QString& newName) {
    if (!m_overrideStore) return false;
    if (row < 0 || row >= m_functions.size()) return false;
    if (newName.isEmpty()) return false;

    AuraOverrideKey key = buildKeyForFunction(row);
    AuraOverrideRecord rec{};
    rec.key            = key;
    rec.payload.kind   = AURA_OVERRIDE_PAYLOAD_RENAME;
    const QByteArray nameUtf8 = newName.toUtf8();
    std::strncpy(rec.payload.text, nameUtf8.constData(),
                 AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
    rec.status = AURA_OVERRIDE_STATUS_ACTIVE;

    if (aura_override_store_put(m_overrideStore, &rec) != 0) {
        statusBar()->showMessage(QStringLiteral("Rename 실패 (override store put)."));
        return false;
    }

    applyOverridesToFunctions();
    if (m_functionModel) m_functionModel->setFunctions(m_functions);
    statusBar()->showMessage(
        QStringLiteral("Rename: 0x%1 → %2")
            .arg(m_functions[row].entry, 0, 16)
            .arg(newName));
    return true;
}

bool MainWindow::resetFunctionNameAt(int row) {
    if (!m_overrideStore) return false;
    if (row < 0 || row >= m_functions.size()) return false;

    AuraOverrideKey key = buildKeyForFunction(row);
    int rc = aura_override_store_delete(m_overrideStore, &key);
    if (rc < 0) {
        statusBar()->showMessage(QStringLiteral("Reset 실패 (rc=%1).").arg(rc));
        return false;
    }
    applyOverridesToFunctions();
    if (m_functionModel) m_functionModel->setFunctions(m_functions);
    statusBar()->showMessage(
        QStringLiteral("Reset: 0x%1 → %2 (engine 이름 복원)")
            .arg(m_functions[row].entry, 0, 16)
            .arg(m_functions[row].originalName));
    return true;
}

QString MainWindow::functionDisplayNameAt(int row) const {
    if (row < 0 || row >= m_functions.size()) return {};
    return m_functions[row].name;
}

// ── Phase 11.3.9 (P2.F4 C2): DecompilePane context-menu actions ────────
//
// R-5 guard: Rename / Add comment land in override_store via _put;
// AuraEngineResponse is never mutated. Display layer joins the engine
// record set with the override store at presentation time.

static int findFunctionRowByEntry(
    const QVector<aura::gui::GuiFunctionRecord>& fns, quint64 entry) {
    for (int i = 0; i < fns.size(); ++i) {
        if (fns[i].entry == entry) return i;
    }
    return -1;
}

// ── Phase 11.4.2 (P4.PP4 C3): GUI label candidates + popover ─────────────
//
// Display-only path per ADR-0044 D5. Mirrors the CLI heuristic
// (src/cli/main.cpp run_label_candidates) but operates on the GUI's
// already-mirrored vectors (m_xrefs / m_symbols / m_strings) so no
// re-dispatch is needed. R-5 / R-9 / R-12 unchanged.

namespace {
QString deriveNameFromSymbol(const QString& raw) {
    QString s = raw;
    static const QStringList prefixes = {
        QStringLiteral("sym.imp."), QStringLiteral("imp."),
        QStringLiteral("sym."), QStringLiteral("fcn.")
    };
    for (const auto& p : prefixes) {
        if (s.size() > p.size() && s.startsWith(p)) {
            s.remove(0, p.size());
            break;
        }
    }
    if (s.size() > 24) s.truncate(24);
    return s;
}

QString snakeCaseFromString(const QString& raw) {
    QString out;
    out.reserve(24);
    for (QChar c : raw) {
        if (out.size() >= 24) break;
        const ushort u = c.unicode();
        if ((u >= 'a' && u <= 'z') || (u >= '0' && u <= '9')) {
            out += c;
        } else if (u >= 'A' && u <= 'Z') {
            out += QChar(u - 'A' + 'a');
        } else {
            if (!out.isEmpty() && out.back() != QLatin1Char('_'))
                out += QLatin1Char('_');
        }
    }
    while (!out.isEmpty() && out.back()  == QLatin1Char('_')) out.chop(1);
    while (!out.isEmpty() && out.front() == QLatin1Char('_')) out.remove(0, 1);
    return out;
}
}  // namespace

QVector<GuiLabelCandidate>
MainWindow::generateLabelCandidates(quint64 funcAddr) const {
    QVector<GuiLabelCandidate> result;
    // Locate the function record for size; without size we can't bound
    // xref scanning by [entry, entry+size).
    quint64 fnLo = 0, fnHi = 0;
    for (const auto& f : m_functions) {
        if (f.entry == funcAddr) {
            fnLo = f.entry;
            fnHi = f.entry + (f.size ? f.size : 1);
            break;
        }
    }
    if (fnLo == 0) return result;

    // Index imports by addr; index strings by addr.
    QHash<quint64, const GuiSymbolRecord*> importByAddr;
    for (const auto& s : m_symbols) {
        if (s.kind == QStringLiteral("import"))
            importByAddr.insert(s.addr, &s);
    }
    QHash<quint64, const GuiStringRecord*> stringByAddr;
    for (const auto& s : m_strings) {
        stringByAddr.insert(s.addr, &s);
    }

    QVector<GuiLabelCandidate> raw;
    for (const auto& x : m_xrefs) {
        if (x.from < fnLo || x.from >= fnHi) continue;
        if (auto it = importByAddr.constFind(x.to);
            it != importByAddr.constEnd()) {
            GuiLabelCandidate c;
            c.name       = deriveNameFromSymbol(it.value()->name);
            c.source     = QStringLiteral("import");
            c.confidence = 0.7;
            c.fromAddr   = x.from;
            c.evidence   = QStringLiteral("call:") + it.value()->name;
            if (!c.name.isEmpty()) raw.push_back(std::move(c));
        }
        if (auto it = stringByAddr.constFind(x.to);
            it != stringByAddr.constEnd()) {
            GuiLabelCandidate c;
            c.name       = snakeCaseFromString(it.value()->content);
            c.source     = QStringLiteral("string");
            c.confidence = 0.6;
            c.fromAddr   = x.from;
            c.evidence   = QStringLiteral("str:") + it.value()->content;
            if (!c.name.isEmpty()) raw.push_back(std::move(c));
        }
    }

    std::sort(raw.begin(), raw.end(),
              [](const GuiLabelCandidate& a, const GuiLabelCandidate& b) {
                  if (a.confidence != b.confidence)
                      return a.confidence > b.confidence;
                  return a.source < b.source;  // "import" < "string" so flip
              });

    QSet<QString> seen;
    for (auto& c : raw) {
        if (seen.contains(c.name)) continue;
        seen.insert(c.name);
        result.push_back(std::move(c));
        if (result.size() >= 5) break;
    }
    return result;
}

// ── Phase 11.4.3 (P4.PP1 C4): GUI type propagation candidates ────────────
//
// Same algorithm as src/core/type_propagation.cpp / CLI run_propagate_type,
// but in-process over the GUI's already-mirrored vectors. R-5/R-9/R-12
// unchanged from ADR-0045 D5.

QVector<GuiTypePropagationCandidate>
MainWindow::generateTypePropagationCandidates(
    quint64 funcAddr, const QString& targetType) const {
    QVector<GuiTypePropagationCandidate> result;

    quint32 callerId = 0;
    for (const auto& f : m_functions) {
        if (f.entry == funcAddr) {
            callerId = static_cast<quint32>(f.functionId);
            break;
        }
    }
    if (callerId == 0) return result;

    // Index "arg" variables by function_id; type_facts by var_id.
    QHash<quint32, QVector<const GuiVariableRecord*>> argsByFn;
    for (const auto& v : m_variables) {
        if (v.kind == QStringLiteral("arg"))
            argsByFn[v.functionId].push_back(&v);
    }
    QHash<quint32, const GuiTypeFactRecord*> typeByVar;
    for (const auto& t : m_typeFacts) {
        if (t.varId != 0) typeByVar.insert(t.varId, &t);
    }

    for (const auto& ce : m_callEdges) {
        if (ce.callerId != callerId) continue;
        if (ce.calleeId == 0) continue;  // unresolved indirect
        auto itArgs = argsByFn.constFind(ce.calleeId);
        if (itArgs == argsByFn.constEnd()) continue;
        for (const auto* arg : itArgs.value()) {
            GuiTypePropagationCandidate c;
            c.varId        = arg->varId;
            c.functionId   = ce.calleeId;
            c.callSiteAddr = ce.siteAddr;
            c.distance     = 1;
            c.source       = QStringLiteral("callee_param");
            c.newType      = targetType;
            auto itT = typeByVar.constFind(arg->varId);
            c.oldType = (itT != typeByVar.constEnd())
                            ? itT.value()->typeStr
                            : QString();
            c.selected = true;
            result.push_back(std::move(c));
        }
    }
    return result;
}

// ── Phase 11.4.4 (P4.PP2 C3): GUI field candidates ───────────────────────
//
// Mirrors the CLI heuristic (src/cli/main.cpp run_field_candidates) but
// in-process over m_functions / m_variables. Stack cluster only in v1;
// the op_str regex source is v2 (needs disasm body access).

QVector<GuiFieldCandidate>
MainWindow::generateFieldCandidates(quint64 funcAddr) const {
    QVector<GuiFieldCandidate> result;
    quint32 fid = 0;
    for (const auto& f : m_functions) {
        if (f.entry == funcAddr) {
            fid = static_cast<quint32>(f.functionId);
            break;
        }
    }
    if (fid == 0) return result;

    for (const auto& v : m_variables) {
        if (v.functionId != fid) continue;
        if (v.kind != QStringLiteral("stack")) continue;
        GuiFieldCandidate c;
        c.varId       = v.varId;
        c.stackOffset = v.stackOffset;
        c.name        = v.name;
        c.kind        = v.kind;
        result.push_back(std::move(c));
    }
    std::sort(result.begin(), result.end(),
              [](const GuiFieldCandidate& a, const GuiFieldCandidate& b) {
                  return a.stackOffset < b.stackOffset;
              });
    return result;
}

// ── Phase 11.4.5 (P4.PP3 C3) — array candidate generator ──────────────────
//
// Per ADR-0047 D1+D4: GUI naturally activates (a) op_str source via the
// existing in-process disasmList cache (callers should runDisasm first).
// Sources are merged into one vector keyed on `source`.
//
// Per D2 naming hygiene: synthesized output uses ARITHMETIC vocabulary
// only (offsets / diffs / gcd). No "stride" / "array" / "element_type"
// tokens. Engine-reported `typeStr` literals pass through verbatim.

namespace {

qint64 gcd_i64_abs(qint64 a, qint64 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        qint64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Lightweight scan of `op` for `[<reg>+0xN]` / `[<reg>-0xN]` patterns.
// Mirrors src/cli/main.cpp match_bracket_offset semantics in QString form.
// Appends each (reg, off) hit; returns count appended.
int scanBracketOffsets(const QString& op,
                       QVector<QPair<QString, qint64>>* out) {
    int count = 0;
    int i = 0;
    const int n = op.size();
    while (i < n) {
        const int lb = op.indexOf(QLatin1Char('['), i);
        if (lb < 0) break;
        i = lb + 1;
        while (i < n && (op[i] == QLatin1Char(' ') ||
                         op[i] == QLatin1Char('\t'))) ++i;
        if (i >= n) break;
        if (!(op[i] >= QLatin1Char('a') && op[i] <= QLatin1Char('z'))) continue;
        const int r0 = i;
        while (i < n &&
               ((op[i] >= QLatin1Char('a') && op[i] <= QLatin1Char('z')) ||
                (op[i] >= QLatin1Char('0') && op[i] <= QLatin1Char('9')))) ++i;
        const QString reg = op.mid(r0, i - r0);
        while (i < n && (op[i] == QLatin1Char(' ') ||
                         op[i] == QLatin1Char('\t'))) ++i;
        if (i >= n || (op[i] != QLatin1Char('+') && op[i] != QLatin1Char('-'))) continue;
        const QChar sign = op[i++];
        while (i < n && (op[i] == QLatin1Char(' ') ||
                         op[i] == QLatin1Char('\t'))) ++i;
        if (i + 1 >= n || op[i] != QLatin1Char('0') ||
            (op[i + 1] != QLatin1Char('x') && op[i + 1] != QLatin1Char('X'))) continue;
        i += 2;
        const int h0 = i;
        while (i < n &&
               ((op[i] >= QLatin1Char('0') && op[i] <= QLatin1Char('9')) ||
                (op[i] >= QLatin1Char('a') && op[i] <= QLatin1Char('f')) ||
                (op[i] >= QLatin1Char('A') && op[i] <= QLatin1Char('F')))) ++i;
        if (i == h0) continue;
        const QString hex = op.mid(h0, i - h0);
        bool ok = false;
        qint64 val = static_cast<qint64>(hex.toULongLong(&ok, 16));
        if (!ok) continue;
        if (sign == QLatin1Char('-')) val = -val;
        if (out) out->append({reg, val});
        ++count;
    }
    return count;
}

}  // namespace

QString MainWindow::formatArrayCandidateRow(const GuiArrayCandidate& c) {
    // Per ADR-0047 D2 naming hygiene: every literal token here MUST be
    // arithmetic vocabulary or a structural label (no "stride" /
    // "array" / "element_type"). Engine-reported `typeStr` is the only
    // value that may contain '[' / '*' / English words — and it
    // passes through verbatim because it's not AURA-synthesized.
    if (c.source == QStringLiteral("op_str")) {
        QStringList offStrs;
        for (qint64 o : c.offsets)
            offStrs.append(QString::number(o));
        QStringList diffStrs;
        for (qint64 d : c.diffs)
            diffStrs.append(QString::number(d));
        return QStringLiteral(
                   "[op_str] base=%1  offsets=[%2]  "
                   "diffs=[%3]  gcd=%4  sample=0x%5")
                   .arg(c.baseReg)
                   .arg(offStrs.join(QLatin1Char(',')))
                   .arg(diffStrs.join(QLatin1Char(',')))
                   .arg(c.gcd)
                   .arg(c.sampleAddr, 0, 16);
    }
    if (c.source == QStringLiteral("type_hint")) {
        return QStringLiteral(
                   "[type_hint] var_id=%1  type_str=%2")
                   .arg(c.varId)
                   .arg(c.typeStr);
    }
    // var_cluster
    QStringList offStrs;
    for (qint64 o : c.offsets)
        offStrs.append(QString::number(o));
    QStringList diffStrs;
    for (qint64 d : c.diffs)
        diffStrs.append(QString::number(d));
    return QStringLiteral(
               "[var_cluster] offsets=[%1]  diffs=[%2]  gcd=%3")
               .arg(offStrs.join(QLatin1Char(',')))
               .arg(diffStrs.join(QLatin1Char(',')))
               .arg(c.gcd);
}

QVector<GuiArrayCandidate>
MainWindow::generateArrayCandidates(quint64 funcAddr) const {
    QVector<GuiArrayCandidate> result;

    quint32 fid = 0;
    for (const auto& f : m_functions) {
        if (f.entry == funcAddr) {
            fid = static_cast<quint32>(f.functionId);
            break;
        }
    }
    if (fid == 0) return result;

    // (a) op_str cluster — GUI-only path per ADR-0047 D4.
    // Group bracket hits by base register; emit one candidate per
    // base with ≥2 distinct offsets so the user can read the diffs.
    const QVector<GuiInstructionRecord> insns = disasmList(funcAddr);
    QMap<QString, QMap<qint64, quint64>> byReg;  // reg → offset → first addr
    for (const auto& ins : insns) {
        QVector<QPair<QString, qint64>> hits;
        scanBracketOffsets(ins.opStr, &hits);
        for (const auto& hp : hits) {
            auto& m = byReg[hp.first];
            if (!m.contains(hp.second)) m[hp.second] = ins.addr;
        }
    }
    for (auto it = byReg.constBegin(); it != byReg.constEnd(); ++it) {
        if (it.value().size() < 2) continue;
        GuiArrayCandidate c;
        c.source  = QStringLiteral("op_str");
        c.baseReg = it.key();
        QList<qint64> offs = it.value().keys();
        std::sort(offs.begin(), offs.end());
        for (qint64 o : offs) c.offsets.append(o);
        qint64 g = 0;
        for (int i = 1; i < c.offsets.size(); ++i) {
            qint64 d = c.offsets[i] - c.offsets[i - 1];
            c.diffs.append(d);
            g = gcd_i64_abs(g, d);
        }
        c.gcd = g;
        c.sampleAddr = it.value().value(offs.first(), 0);
        result.push_back(std::move(c));
    }

    // (b) type_hint — type_facts whose engine literal contains '['.
    for (const auto& tf : m_typeFacts) {
        if (tf.functionId != fid) continue;
        if (!tf.typeStr.contains(QLatin1Char('['))) continue;
        GuiArrayCandidate c;
        c.source  = QStringLiteral("type_hint");
        c.varId   = tf.varId;
        c.typeStr = tf.typeStr;
        result.push_back(std::move(c));
    }

    // (c) variable cluster — single combined cluster of the function's
    // stack vars sorted by offset (≥2 stack vars required).
    QVector<const GuiVariableRecord*> stackVars;
    for (const auto& v : m_variables) {
        if (v.functionId != fid) continue;
        if (v.kind != QStringLiteral("stack")) continue;
        stackVars.push_back(&v);
    }
    if (stackVars.size() >= 2) {
        std::sort(stackVars.begin(), stackVars.end(),
                  [](const GuiVariableRecord* a, const GuiVariableRecord* b) {
                      return a->stackOffset < b->stackOffset;
                  });
        GuiArrayCandidate c;
        c.source = QStringLiteral("var_cluster");
        for (const auto* v : stackVars) c.offsets.append(v->stackOffset);
        qint64 g = 0;
        for (int i = 1; i < c.offsets.size(); ++i) {
            qint64 d = c.offsets[i] - c.offsets[i - 1];
            c.diffs.append(d);
            g = gcd_i64_abs(g, d);
        }
        c.gcd = g;
        result.push_back(std::move(c));
    }

    return result;
}

// ── Phase 11.3.9 (P2.F4 C3): navigation history ──────────────────────────

namespace {
// Convert a function entry addr to its row in m_functions.
int rowOfFunctionByEntry(
    const QVector<aura::gui::GuiFunctionRecord>& fns, quint64 entry) {
    for (int i = 0; i < fns.size(); ++i)
        if (fns[i].entry == entry) return i;
    return -1;
}
}  // namespace

void MainWindow::goBack() {
    if (m_navBack.isEmpty()) return;
    const quint64 prev = m_navBack.pop();
    if (m_activeFunctionAddr != 0) {
        m_navForward.push(m_activeFunctionAddr);
    }
    const int row = rowOfFunctionByEntry(m_functions, prev);
    if (row >= 0 && m_functionTable) {
        m_navInProgress = true;
        const QModelIndex idx = m_functionModel->functionIndex(row);
        m_functionTable->setCurrentIndex(idx);
        m_functionTable->scrollTo(idx);
        // setCurrentIndex triggers onFunctionRowSelected which (because of
        // the flag) skips the stack push. m_activeFunctionAddr is
        // updated there.
        m_navInProgress = false;
    }
    if (m_actNavBack)    m_actNavBack->setEnabled(!m_navBack.isEmpty());
    if (m_actNavForward) m_actNavForward->setEnabled(true);
}

void MainWindow::goForward() {
    if (m_navForward.isEmpty()) return;
    const quint64 next = m_navForward.pop();
    if (m_activeFunctionAddr != 0) {
        m_navBack.push(m_activeFunctionAddr);
    }
    const int row = rowOfFunctionByEntry(m_functions, next);
    if (row >= 0 && m_functionTable) {
        m_navInProgress = true;
        const QModelIndex idx = m_functionModel->functionIndex(row);
        m_functionTable->setCurrentIndex(idx);
        m_functionTable->scrollTo(idx);
        m_navInProgress = false;
    }
    if (m_actNavBack)    m_actNavBack->setEnabled(true);
    if (m_actNavForward) m_actNavForward->setEnabled(!m_navForward.isEmpty());
}

void MainWindow::onDecompContextJump(quint64 addr) {
    if (addr == 0 || !m_disasmPane) return;
    m_disasmPane->selectInstruction(addr);
}

void MainWindow::onDecompContextRename() {
    const int row = findFunctionRowByEntry(m_functions, m_activeFunctionAddr);
    if (row < 0) {
        statusBar()->showMessage(QStringLiteral("Rename: 활성 함수 없음."));
        return;
    }
    bool ok = false;
    const QString cur = m_functions[row].name;
    const QString newName = QInputDialog::getText(
        this, QStringLiteral("Rename function"),
        QStringLiteral("새 이름:"), QLineEdit::Normal, cur, &ok);
    if (ok && !newName.trimmed().isEmpty()) {
        renameFunctionAt(row, newName.trimmed());
    }
}

void MainWindow::onDecompContextReset() {
    const int row = findFunctionRowByEntry(m_functions, m_activeFunctionAddr);
    if (row < 0) {
        statusBar()->showMessage(QStringLiteral("Reset: 활성 함수 없음."));
        return;
    }
    resetFunctionNameAt(row);
}

void MainWindow::onDecompContextFindXrefs(quint64 addr) {
    if (addr == 0) return;
    // v1: just raise the Xrefs dock; full filter-by-addr lands in F4 v2.
    if (m_xrefsDock) {
        m_xrefsDock->raise();
        m_xrefsDock->show();
        statusBar()->showMessage(
            QStringLiteral("Xrefs dock 활성 (필터 0x%1 — F4 v2 에서 적용)")
                .arg(addr, 0, 16));
    }
}

void MainWindow::onDecompContextAddComment(quint64 addr) {
    // F4 v1: comment is attached to the active function (whichever
    // function is currently displayed). Per-instruction annotations
    // — keyed by `addr` — land in F4 v2 once the override store
    // grows an instruction-level key variant. v1 reuses the existing
    // function-keyed override path (R-5 honoured: store-only).
    if (!m_overrideStore) return;
    const int row = findFunctionRowByEntry(m_functions, m_activeFunctionAddr);
    if (row < 0) {
        statusBar()->showMessage(QStringLiteral("Comment: 활성 함수 없음."));
        return;
    }
    bool ok = false;
    const QString text = QInputDialog::getText(
        this, QStringLiteral("Add comment"),
        QStringLiteral("comment (≤256 bytes):"),
        QLineEdit::Normal, QString(), &ok);
    if (!ok || text.trimmed().isEmpty()) return;

    AuraOverrideKey key = buildKeyForFunction(row);
    AuraOverrideRecord rec{};
    rec.key            = key;
    rec.payload.kind   = AURA_OVERRIDE_PAYLOAD_ANNOTATION;
    const QByteArray u8 = text.trimmed().toUtf8();
    std::strncpy(rec.payload.text, u8.constData(),
                 AURA_OVERRIDE_PAYLOAD_TEXT_CAP - 1);
    rec.status = AURA_OVERRIDE_STATUS_ACTIVE;

    if (aura_override_store_put(m_overrideStore, &rec) != 0) {
        statusBar()->showMessage(QStringLiteral("Comment 저장 실패."));
        return;
    }
    statusBar()->showMessage(
        QStringLiteral("Comment 추가 (function 0x%1, near addr 0x%2): \"%3\"")
            .arg(m_activeFunctionAddr, 0, 16).arg(addr, 0, 16)
            .arg(text.trimmed()));
}

void MainWindow::onFunctionContextMenu(const QPoint& pos) {
    if (!m_functionTable) return;
    const QModelIndex idx = m_functionTable->indexAt(pos);
    if (!idx.isValid()) return;
    const int row = m_functionModel
        ? m_functionModel->functionRowForIndex(idx)
        : idx.row();
    if (row < 0 || row >= m_functions.size()) return;

    const bool ko = useKoreanUi();
    QMenu menu(this);
    QAction* renameAct  = menu.addAction(
        ko ? QStringLiteral("이름 변경(&R)...")
           : QStringLiteral("&Rename..."));
    QAction* resetAct   = menu.addAction(
        ko ? QStringLiteral("이름 초기화(&S)")
           : QStringLiteral("Re&set name"));
    resetAct->setEnabled(m_functions[row].overridden);
    menu.addSeparator();
    // Phase 11.4.2 (P4.PP4 C3): suggest labels from xrefs/strings/imports.
    QAction* suggestAct = menu.addAction(
        ko ? QStringLiteral("레이블 추천(&L)...")
           : QStringLiteral("&Suggest labels..."));
    // Phase 11.4.3 (P4.PP1 C4): propagate variable type to callee args.
    QAction* propAct    = menu.addAction(
        ko ? QStringLiteral("타입 전파(&T)...")
           : QStringLiteral("&Propagate type..."));
    // Phase 11.4.4 (P4.PP2 C3): suggest stack-field structure (v1: clusters).
    QAction* fieldsAct  = menu.addAction(
        ko ? QStringLiteral("필드 추천(&F)...")
           : QStringLiteral("Suggest &fields..."));
    // Phase 11.4.5 (P4.PP3 C3): suggest array shape — raw arithmetic stat
    // (offsets/diffs/gcd) + engine type literals. Per ADR-0047 D2 the
    // dialog renders arithmetic vocabulary only — no "stride"/"array"/
    // "element_type" strings synthesized by AURA.
    QAction* arrayAct   = menu.addAction(
        ko ? QStringLiteral("배열 형태 추천(&A)...")
           : QStringLiteral("Suggest &array shape..."));

    // Phase 11.5 (P5 polish) — copy-to-clipboard helpers (RE-workflow:
    // paste address into external tool, paste name into a write-up).
    menu.addSeparator();
    QAction* copyAddrAct = menu.addAction(
        (ko ? QStringLiteral("주소 복사(&C) (0x%1)")
            : QStringLiteral("&Copy address (0x%1)"))
            .arg(m_functions[row].entry, 0, 16));
    QAction* copyNameAct = menu.addAction(
        (ko ? QStringLiteral("이름 복사(&Y) (%1)")
            : QStringLiteral("Cop&y name (%1)"))
            .arg(m_functions[row].name));

    QAction* chosen = menu.exec(m_functionTable->viewport()->mapToGlobal(pos));
    if (!chosen) return;

    if (chosen == copyAddrAct) {
        const QString text =
            clipboardTextForFunction(row, QStringLiteral("address"));
        QApplication::clipboard()->setText(text);
        statusBar()->showMessage(
            (ko ? QStringLiteral("클립보드에 복사됨: %1")
                : QStringLiteral("Copied to clipboard: %1"))
                .arg(text), 3000);
        return;
    }
    if (chosen == copyNameAct) {
        const QString text =
            clipboardTextForFunction(row, QStringLiteral("name"));
        QApplication::clipboard()->setText(text);
        statusBar()->showMessage(
            (ko ? QStringLiteral("클립보드에 복사됨: %1")
                : QStringLiteral("Copied to clipboard: %1"))
                .arg(text), 3000);
        return;
    }
    if (chosen == renameAct) {
        bool ok = false;
        const QString cur = m_functions[row].name;
        const QString newName = QInputDialog::getText(
            this, ko ? QStringLiteral("함수 이름 변경")
                     : QStringLiteral("Rename function"),
            QStringLiteral("새 이름:"), QLineEdit::Normal, cur, &ok);
        if (ok && !newName.trimmed().isEmpty()) {
            renameFunctionAt(row, newName.trimmed());
        }
    } else if (chosen == resetAct) {
        resetFunctionNameAt(row);
    } else if (chosen == suggestAct) {
        // PP4 popover: list ≤5 candidates + Apply.
        const auto cands =
            generateLabelCandidates(m_functions[row].entry);
        if (cands.isEmpty()) {
            QMessageBox::information(
                this, QStringLiteral("Suggest labels"),
                QStringLiteral(
                    "이 함수에서 추출 가능한 후보가 없습니다.\n"
                    "(함수 내부에서 import/string 를 참조하는 xref 가 없음)"));
            return;
        }
        QDialog dlg(this);
        dlg.setWindowTitle(
            QStringLiteral("Suggest labels — 0x%1")
                .arg(m_functions[row].entry, 0, 16));
        auto* layout = new QVBoxLayout(&dlg);
        auto* list   = new QListWidget(&dlg);
        for (const auto& c : cands) {
            auto* it = new QListWidgetItem(
                QStringLiteral("%1   [%2, conf=%3]   %4")
                    .arg(c.name)
                    .arg(c.source)
                    .arg(c.confidence, 0, 'f', 2)
                    .arg(c.evidence.left(60)),
                list);
            it->setData(Qt::UserRole, c.name);
        }
        if (list->count() > 0) list->setCurrentRow(0);
        layout->addWidget(list);
        auto* btnRow = new QHBoxLayout();
        auto* applyBtn  = new QPushButton(QStringLiteral("Apply"), &dlg);
        auto* cancelBtn = new QPushButton(QStringLiteral("Cancel"), &dlg);
        btnRow->addStretch();
        btnRow->addWidget(applyBtn);
        btnRow->addWidget(cancelBtn);
        layout->addLayout(btnRow);
        connect(applyBtn,  &QPushButton::clicked, &dlg, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dlg, &QDialog::reject);
        if (dlg.exec() == QDialog::Accepted) {
            auto* sel = list->currentItem();
            if (sel) {
                renameFunctionAt(row,
                                 sel->data(Qt::UserRole).toString());
            }
        }
    } else if (chosen == propAct) {
        // PP1 popover (ADR-0045 D5): target-type LineEdit + QListWidget
        // (per-row checkbox) + Apply / Cancel. Apply path is wired in
        // cycle-30 (C5); v1 surfaces the candidate set + selection only.
        QDialog dlg(this);
        dlg.setWindowTitle(
            QStringLiteral("Propagate type — function 0x%1")
                .arg(m_functions[row].entry, 0, 16));
        auto* layout = new QVBoxLayout(&dlg);
        auto* tgtRow = new QHBoxLayout();
        tgtRow->addWidget(new QLabel(QStringLiteral("Target type:"), &dlg));
        auto* tgtEdit = new QLineEdit(QStringLiteral("UserStruct*"), &dlg);
        tgtRow->addWidget(tgtEdit, 1);
        layout->addLayout(tgtRow);

        auto* list   = new QListWidget(&dlg);
        layout->addWidget(list, 1);

        auto refresh = [&]() {
            list->clear();
            const auto cands = generateTypePropagationCandidates(
                m_functions[row].entry, tgtEdit->text());
            for (int i = 0; i < cands.size(); ++i) {
                const auto& c = cands[i];
                auto* it = new QListWidgetItem(
                    QStringLiteral(
                        "fn_id=%1  var_id=%2  call@0x%3  %4 → %5  "
                        "[%6 d=%7]")
                        .arg(c.functionId)
                        .arg(c.varId)
                        .arg(c.callSiteAddr, 0, 16)
                        .arg(c.oldType.isEmpty()
                                 ? QStringLiteral("(unknown)")
                                 : c.oldType)
                        .arg(c.newType)
                        .arg(c.source)
                        .arg(c.distance),
                    list);
                it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
                it->setCheckState(c.selected ? Qt::Checked : Qt::Unchecked);
                it->setData(Qt::UserRole + 0, c.varId);
                it->setData(Qt::UserRole + 1, c.functionId);
                it->setData(Qt::UserRole + 2, c.newType);
            }
            if (cands.isEmpty()) {
                auto* empty = new QListWidgetItem(
                    QStringLiteral(
                        "(이 함수에서 호출하는 함수의 매개변수 후보 없음 — "
                        "indirect call 또는 callee args 미감지)"),
                    list);
                empty->setFlags(Qt::ItemIsEnabled);
            }
        };
        refresh();
        connect(tgtEdit, &QLineEdit::textChanged,
                [&](const QString&) { refresh(); });

        auto* btnRow = new QHBoxLayout();
        auto* applyBtn  = new QPushButton(QStringLiteral("Apply"), &dlg);
        applyBtn->setToolTip(QStringLiteral(
            "v1: counts selected candidates and reports via status bar. "
            "Variable-target override_store integration ships as a "
            "separate phase (PP1 v2 store wire) — needs "
            "buildKeyForVariable() which doesn't exist yet."));
        auto* cancelBtn = new QPushButton(QStringLiteral("Cancel"), &dlg);
        btnRow->addStretch();
        btnRow->addWidget(applyBtn);
        btnRow->addWidget(cancelBtn);
        layout->addLayout(btnRow);
        connect(applyBtn, &QPushButton::clicked, &dlg, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dlg, &QDialog::reject);
        if (dlg.exec() == QDialog::Accepted) {
            // PP1 C5 v1: count selected candidates, surface via status
            // bar. Variable-target override_store_put deferred to a
            // dedicated PP1 v2 phase that introduces
            // buildKeyForVariable(). R-5 still honoured — store touch 0.
            int selected = 0;
            for (int i = 0; i < list->count(); ++i) {
                auto* it = list->item(i);
                if (it->flags() & Qt::ItemIsUserCheckable
                    && it->checkState() == Qt::Checked) ++selected;
            }
            statusBar()->showMessage(
                QStringLiteral(
                    "Propagate type (dry-run): %1개 candidate 선택됨 "
                    "[target=%2] — store 통합은 PP1 v2 phase 에서.")
                    .arg(selected).arg(tgtEdit->text()));
        }
    } else if (chosen == fieldsAct) {
        // PP2 popover (ADR-0046 D4): stack cluster list. v1 dry-run
        // — selected items are counted but not persisted; struct
        // definition storage is v3 (new override payload kind).
        const auto cands = generateFieldCandidates(m_functions[row].entry);
        QDialog dlg(this);
        dlg.setWindowTitle(
            QStringLiteral("Suggest fields — function 0x%1")
                .arg(m_functions[row].entry, 0, 16));
        auto* layout = new QVBoxLayout(&dlg);
        auto* hint = new QLabel(
            QStringLiteral(
                "stack-offset cluster (v1). op_str regex 후보는 v2 — "
                "DISASM body 통합 후 활성. struct 정의 합성은 R-9 "
                "위반으로 사용자/LLM 영구 위임."), &dlg);
        hint->setWordWrap(true);
        hint->setStyleSheet(
            QStringLiteral("color: #888; padding: 4px;"));
        layout->addWidget(hint);

        auto* list = new QListWidget(&dlg);
        for (const auto& c : cands) {
            auto* it = new QListWidgetItem(
                QStringLiteral(
                    "var_id=%1  stack_offset=%2  name=%3  [%4]")
                    .arg(c.varId)
                    .arg(c.stackOffset)
                    .arg(c.name.isEmpty()
                             ? QStringLiteral("(unnamed)") : c.name)
                    .arg(c.kind),
                list);
            it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
            it->setCheckState(Qt::Unchecked);
            it->setData(Qt::UserRole, c.varId);
        }
        if (cands.isEmpty()) {
            auto* empty = new QListWidgetItem(
                QStringLiteral(
                    "(이 함수는 stack 변수 0개 — engine 이 stack "
                    "kind 변수 미감지)"),
                list);
            empty->setFlags(Qt::ItemIsEnabled);
        }
        layout->addWidget(list, 1);

        auto* btnRow = new QHBoxLayout();
        auto* applyBtn  = new QPushButton(QStringLiteral("Apply"), &dlg);
        applyBtn->setEnabled(!cands.isEmpty());
        applyBtn->setToolTip(QStringLiteral(
            "v1: counts checked clusters, surfaces via status bar. "
            "Struct definition persistence ships in v3 (new payload "
            "kind AURA_OVERRIDE_PAYLOAD_STRUCT_DEF)."));
        auto* cancelBtn = new QPushButton(QStringLiteral("Cancel"), &dlg);
        btnRow->addStretch();
        btnRow->addWidget(applyBtn);
        btnRow->addWidget(cancelBtn);
        layout->addLayout(btnRow);
        connect(applyBtn,  &QPushButton::clicked, &dlg, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dlg, &QDialog::reject);
        if (dlg.exec() == QDialog::Accepted) {
            int sel = 0;
            for (int i = 0; i < list->count(); ++i) {
                auto* it = list->item(i);
                if ((it->flags() & Qt::ItemIsUserCheckable) &&
                    it->checkState() == Qt::Checked) ++sel;
            }
            statusBar()->showMessage(
                QStringLiteral(
                    "Suggest fields (dry-run): %1개 cluster 선택됨 — "
                    "struct 정의 저장은 v3 phase 에서.")
                    .arg(sel));
        }
    } else if (chosen == arrayAct) {
        // PP3 popover (ADR-0047 D4): merged candidate list from
        //   (a) op_str clusters (GUI activates via in-process disasm
        //       cache — runDisasm fills it lazily here),
        //   (b) type_hint literals (engine type_str containing '['),
        //   (c) stack variable cluster (offsets/diffs/gcd).
        // v1 = no-apply (status bar count). Apply path requires a new
        // override payload kind (AURA_OVERRIDE_PAYLOAD_ARRAY_HINT) —
        // ADR-0047 D5 defers to a separate phase.
        const quint64 fa = m_functions[row].entry;
        runDisasm(fa);  // fill in-process cache for (a) source
        const auto cands = generateArrayCandidates(fa);
        QDialog dlg(this);
        dlg.setWindowTitle(
            QStringLiteral("Suggest array shape — function 0x%1")
                .arg(fa, 0, 16));
        auto* layout = new QVBoxLayout(&dlg);
        // Naming-hygiene compliant hint label (no synthesized analysis
        // vocabulary — only arithmetic / engine literal terms).
        auto* hint = new QLabel(
            QStringLiteral(
                "raw arithmetic only (offsets / diffs / gcd) + engine "
                "type literals. 자료형 정의 합성은 R-9 위반으로 "
                "사용자/LLM 영구 위임 — Apply 는 v2 phase 에서."), &dlg);
        hint->setWordWrap(true);
        hint->setStyleSheet(
            QStringLiteral("color: #888; padding: 4px;"));
        layout->addWidget(hint);

        auto* list = new QListWidget(&dlg);
        for (const auto& c : cands) {
            // Single source of truth for row text — gui_smoke
            // regression-guards this same formatter (cycle-37).
            auto* it = new QListWidgetItem(
                MainWindow::formatArrayCandidateRow(c), list);
            it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
            it->setCheckState(Qt::Unchecked);
        }
        if (cands.isEmpty()) {
            auto* empty = new QListWidgetItem(
                QStringLiteral(
                    "(이 함수는 후보 0개 — engine 이 [base+offset] "
                    "패턴 / stack 변수 / [-bracketed] type_str 미감지)"),
                list);
            empty->setFlags(Qt::ItemIsEnabled);
        }
        layout->addWidget(list, 1);

        auto* btnRow = new QHBoxLayout();
        auto* applyBtn  = new QPushButton(QStringLiteral("Apply"), &dlg);
        applyBtn->setEnabled(!cands.isEmpty());
        applyBtn->setToolTip(QStringLiteral(
            "v1: counts checked items, surfaces via status bar. "
            "Apply path requires AURA_OVERRIDE_PAYLOAD_ARRAY_HINT "
            "(new payload kind) — ADR-0047 D5 defers to v2 phase."));
        auto* cancelBtn = new QPushButton(QStringLiteral("Cancel"), &dlg);
        btnRow->addStretch();
        btnRow->addWidget(applyBtn);
        btnRow->addWidget(cancelBtn);
        layout->addLayout(btnRow);
        connect(applyBtn,  &QPushButton::clicked, &dlg, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dlg, &QDialog::reject);
        if (dlg.exec() == QDialog::Accepted) {
            int sel = 0;
            for (int i = 0; i < list->count(); ++i) {
                auto* it = list->item(i);
                if ((it->flags() & Qt::ItemIsUserCheckable) &&
                    it->checkState() == Qt::Checked) ++sel;
            }
            statusBar()->showMessage(
                QStringLiteral(
                    "Suggest array shape (dry-run): %1개 후보 선택됨 "
                    "— 자료형 정의 저장은 v2 phase 에서.")
                    .arg(sel));
        }
    }
}

void MainWindow::onAbout() {
    QMessageBox::about(
        this, QStringLiteral("About AURA"),
        QStringLiteral(
            "<h3>AURA</h3>"
            "<p>RE-tool orchestrator + LLM context provider.</p>"
            "<p>GUI v1.2 (Phase 11.3.2) — Project view + Cutter workspace + "
            "Override editor (ADR-0035 / 0036 / 0037).</p>"));
}

}  // namespace aura::gui
