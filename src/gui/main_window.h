// src/gui/main_window.h — AURA GUI MainWindow (Phase 11.3 / 11.3.1,
// ADR-0035 + ADR-0036).

#pragma once

#include <QMainWindow>
#include <QStack>
#include <QString>
#include <QVector>

extern "C" {
#include "engine_request.h"
#include "project_binaries.h"
#include "override_identity.h"
#include "override_store.h"
}

class QStackedWidget;
class QTableView;
class QTreeView;
class QAction;
class QPushButton;
class QDockWidget;
class QEvent;
class QPlainTextEdit;
class QWidget;

namespace aura::gui {

class ProjectBinaryModel;
class FunctionTableModel;
class XrefTableModel;
class SymbolTableModel;
class StringTableModel;
class DecompilePane;
class DisasmPane;
class FullDisasmPane;
class CfgPane;
class HexPane;

struct GuiFunctionRecord {
    QString  name;          // display name (override-applied if any)
    QString  originalName;  // engine-reported name (immutable)
    quint64  entry        = 0;
    quint64  size         = 0;
    QString  source;        // "rizin", or "user/rename" if overridden
    quint64  functionId   = 0;  // engine stable id (Phase 4A.X2 EXACT path)
    bool     overridden   = false;
};

// Phase 11.3.5: cross-reference record exposed to RPC + Xrefs dock.
// Stable, engine-agnostic shape — derived from AuraXrefRecord.
struct GuiXrefRecord {
    quint64 from   = 0;     // source address
    quint64 to     = 0;     // target address (often a function entry)
    QString kind;           // "data" | "code" | "call" | "unknown"
    QString source;         // provenance.source ("rizin", ...)
};

// Phase 11.3.5: symbol record exposed to RPC + Symbols dock.
// Imports are kind=="import" and reused by an Imports filter view.
struct GuiSymbolRecord {
    quint64 addr   = 0;
    QString kind;           // "function"|"object"|"section"|"import"|"unknown"
    QString name;
    QString source;         // provenance.source
};

// Phase 11.4.3 (P4.PP1) GUI mirrors of records the propagation
// algorithm reads. Same pattern as m_xrefs/m_symbols/m_strings —
// the analyze post-step copies the engine arrays into Qt-native
// vectors so the GUI doesn't need to keep AuraEngineResponse alive.
struct GuiCallEdgeRecord {
    quint32 callerId = 0;
    quint32 calleeId = 0;
    quint64 siteAddr = 0;
};

struct GuiVariableRecord {
    quint32 varId      = 0;
    quint32 functionId = 0;
    QString name;
    QString kind;        // "stack"|"reg"|"arg"|"sp"|"bp"
    qint32  stackOffset = 0;
};

struct GuiTypeFactRecord {
    quint32 varId      = 0;
    quint32 functionId = 0;
    QString typeStr;
};

// Phase 11.4.4 (P4.PP2) per ADR-0046 D5: display-only path 4번째
// 적용. GuiFieldCandidate is NOT a 1급 record. Transient view of
// stack-offset clusters within a function. (a) op_str source is v2.
struct GuiFieldCandidate {
    quint32 varId        = 0;
    qint32  stackOffset  = 0;
    QString name;
    QString kind;        // "stack"
};

// Phase 11.4.5 (P4.PP3) per ADR-0047 D5: display-only path 5번째
// 적용. GuiArrayCandidate is NOT a 1급 record. Transient view from
// generateArrayCandidates over m_variables (var_cluster), m_typeFacts
// (type_hint w/ '['), and disasmList(funcAddr) (op_str cluster — GUI-
// only activation per ADR-0047 D4 since the in-process disasm cache
// resolves PP2's deferred (a) source naturally).
//
// Per D2 naming hygiene: this struct intentionally exposes raw
// arithmetic stats (offsets/diffs/gcd) — NO synthesized "stride"/
// "array"/"element_type" fields. The string label rendered into the
// QListWidget likewise uses arithmetic-only vocabulary. Engine-
// reported `typeStr` (which may contain "[" / "*") passes through
// verbatim.
struct GuiArrayCandidate {
    QString source;          // "var_cluster" | "op_str" | "type_hint"
    QString baseReg;         // "" except source=="op_str"
    QVector<qint64> offsets;
    QVector<qint64> diffs;
    qint64  gcd       = 0;
    quint64 sampleAddr = 0;  // op_str: first instruction addr
    quint32 varId      = 0;  // type_hint: subject var; var_cluster: 0
    QString typeStr;         // type_hint only — engine literal verbatim
};

// Phase 11.4.3 (P4.PP1) per ADR-0045 D5: display-only path —
// GuiTypePropagationCandidate is NOT a 1급 record. Transient view
// from generateTypePropagationCandidates over the m_callEdges /
// m_variables / m_typeFacts mirrors above.
struct GuiTypePropagationCandidate {
    quint32 varId        = 0;       // sink (callee parameter var)
    quint32 functionId   = 0;       // sink's owning function (callee)
    quint64 callSiteAddr = 0;
    QString oldType;
    QString newType;
    int     distance     = 1;
    QString source;                 // "callee_param"
    bool    selected     = true;    // checkbox default: on
};

// Phase 11.4.2 (P4.PP4) per ADR-0044 D5: display-only path —
// GuiLabelCandidate is NOT a 1급 record, NOT in AuraRecordCollection.
// Transient view computed by generateLabelCandidates from existing
// xrefs/symbols/strings.
struct GuiLabelCandidate {
    QString name;
    QString source;       // "string" | "import"
    double  confidence;
    quint64 fromAddr;     // xref's from_addr (which call/data ref)
    QString evidence;     // short snippet for the picker UI
};

// Phase 11.6 T2 (Cutter-style flow-arrow gutter): one rendered arrow.
// Computed by MainWindow::computeFlowArrows from a function's
// disassembly. Each arrow connects an instruction performing a jump
// to the line index of its target (when the target is inside the
// same function — otherwise dstLine == -1 and the arrow paints an
// off-function stub at the appropriate edge).
//
// `kind` is the rendering hint:
//   "uncond"     — unconditional jmp / direct branch (blue)
//   "cond_true"  — conditional taken edge        (green)
//   "cond_false" — conditional fall-through edge (red)
//   "call"       — call (drawn dotted / muted)
//
// `lane` is assigned by assignFlowArrowLanes — 0 is the leftmost,
// nearest-to-text column; bigger lane = further left. -1 means the
// arrow overflows the configured max lanes (drawn off-edge).
struct GuiFlowArrow {
    quint64  srcAddr     = 0;
    quint64  dstAddr     = 0;
    int      srcLine     = -1;     // 0-based instruction index
    int      dstLine     = -1;     // -1 if outside the function
    QString  kind;                 // "uncond"|"cond_true"|"cond_false"|"call"
    int      lane        = -1;     // assigned column; -1 = overflow
    int      direction   = 0;      // -1 = up, +1 = down, 0 = same-line
};

// Phase 11.3.7 (P2.F2): per-instruction record exposed to RPC + Disasm dock.
// Stable engine-agnostic shape — derived from AuraInstructionRecord.
struct GuiInstructionRecord {
    quint64 addr   = 0;
    quint32 size   = 0;
    QString bytes;     // hex string e.g. "4889e5"
    QString mnemonic;  // "mov"
    QString opStr;     // "rbp, rsp"
    QString type;      // pdj.type
    quint64 jump   = 0;
    quint64 fail   = 0;
    QString source;    // provenance.source ("rizin")
};

// Phase 11.3.8 (P2.F3): basic-block + edge records for CFG view.
// Stable engine-agnostic shapes — derived from AuraBlockRecord +
// AuraEdgeRecord (Phase 2A). CFG data ownership stays in the
// analyze body per ADR-0041 D1; these are GUI-side mirrors so that
// runAnalyze can serve them to the CFG dock and RPC without keeping
// the AuraEngineResponse alive.
struct GuiBlockRecord {
    quint32 blockId    = 0;
    quint32 functionId = 0;
    quint64 startAddr  = 0;
    quint64 endAddr    = 0;
    QString source;
};

struct GuiEdgeRecord {
    quint32 srcBlock = 0;
    quint32 dstBlock = 0;
    QString kind;        // "fallthrough"|"jump"|"branch_true"|"branch_false"|"call"|"return"|"unknown"
    QString source;
};

// Phase 11.3.6: literal string record exposed to RPC + Strings dock.
// Stable engine-agnostic shape — derived from AuraStringRecord.
struct GuiStringRecord {
    quint64 stringId = 0;
    quint64 addr     = 0;
    quint64 length   = 0;
    QString encoding;        // "ascii"|"utf8"|"utf16le"|"utf16be"|"wide"|"unknown"
    QString section;         // ".rodata" etc; "" if absent
    QString content;         // engine-reported text snippet (≤127 bytes)
    QString source;          // provenance.source
    QString alias;           // user-visible display alias, empty in v1.
    QString maskedContent;   // protected value with mask tokens.
    QString protectedValue;  // alias if set, otherwise maskedContent/content.
    QString exportValue;     // external LLM/MCP-safe value; never alias-first.
    QString protectionSummary;
    int     displayMode = 0; // 0=original, 1=alias, 2=masked.
    bool    hasProtection = false;

    struct ProtectionFinding {
        QString detectorId;
        QString kind;
        int     startOffset = 0;
        int     endOffset = 0;
        double  confidence = 0.0;
        QString maskToken;
    };
    QVector<ProtectionFinding> findings;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    enum Page {
        PageProject  = 0,
        PageFunction = 1,
    };

    void switchToPage(Page page);

    // Programmatic helpers (also exercised by gui_smoke ctest).
    bool openProject(const QString& path);
    bool addBinary(const QString& binaryPath);

    // Phase 11.5 (P5 polish) — recent projects MRU list.
    // Persisted via QSettings under "recentProjects" key. Newest first,
    // deduped, capped at kRecentMax (5). Pushed on successful openProject.
    // Returned in MRU order for gui_smoke.
    QStringList recentProjects() const;

    // Phase 11.5 (P5 polish) — drag-drop binary onto the project view.
    // Public so gui_smoke can exercise the path without synthesizing
    // QDropEvent + QMimeData. The real dropEvent override forwards
    // here. Returns the count of paths actually routed to addBinary
    // (filters out non-existent or directories).
    int handleDroppedPaths(const QStringList& paths);

    // Phase 11.5 (P5 polish) — jump to a function by entry address.
    // Looks up m_functions for an entry == addr; on hit, selects the
    // matching row in the function table (driving the usual
    // onFunctionRowSelected → decompile/disasm/cfg cascade) and
    // returns true. Returns false (and surfaces a status bar nudge)
    // when no function with that entry exists. The existing menu
    // wraps this with a QInputDialog for hex entry; gui_smoke calls
    // it directly.
    bool jumpToFunction(quint64 addr);

    // Phase 11.5 (P5 polish) — case-insensitive substring search over
    // m_functions[].name. Returns the row of the first function whose
    // name contains `needle`, or -1 if none. The View menu wraps this
    // with a QInputDialog (Ctrl+F); gui_smoke calls it directly.
    int findFunctionRowByName(const QString& needle) const;

    // Phase 11.5 (P5 polish) — formatted clipboard text for a function
    // row. `kind` ∈ {"address", "name"}. Returns "" if row is OOB or
    // kind is unknown. The right-click menu's Copy Address / Copy Name
    // actions write this string to QApplication::clipboard()->setText;
    // gui_smoke validates the formatting without depending on a live
    // clipboard (offscreen QPA may not expose one).
    QString clipboardTextForFunction(int row, const QString& kind) const;

    // Phase 11.5 (P5 polish) — Decompile/Disasm/Hex pane font-size
    // zoom (Ctrl+= / Ctrl+- / Ctrl+0). Persisted via QSettings under
    // "paneFontPt". The three pane setters are independent but the
    // mainwindow keeps them in sync via setPaneFontPointSize.
    void setPaneFontPointSize(int pt);
    int  paneFontPointSize() const;

    // Phase 11.5 (P5 polish) — keyboard shortcuts cheat sheet HTML.
    // Static so gui_smoke can invoke without a MainWindow instance.
    // The Help menu's "Keyboard shortcuts..." dialog renders this
    // string into a QMessageBox (rich text). Each shortcut row is a
    // <tr><td>key</td><td>action</td></tr> in a <table> so the
    // contract test can grep for both the key and the action label.
    static QString keyboardShortcutsHtml();

    // Phase 11.5 (P5 polish) — focus / raise one of the four tabified
    // workspace docks. n: 1=Decompile, 2=Disasm, 3=CFG, 4=Hex.
    // Returns true on success; false for OOR n or null dock pointer.
    bool focusDock(int n);
    bool jumpToStringReference(int stringRow);
    bool setStringAliasAt(int stringRow, const QString& alias);
    bool setStringMaskTokenAt(int stringRow, const QString& maskToken);
    bool setStringDisplayModeAt(int stringRow, int displayMode);
    QString stringProtectedValueAt(int stringRow) const;
    bool analyzeBinaryAt(int row, AuraAnalysisLevel level);
    bool decompileFunctionAt(int functionRow);  // for test
    bool disassembleFunctionAt(int functionRow);  // for test (Phase 11.3.7)
    bool renameFunctionAt(int functionRow, const QString& newName);
    bool resetFunctionNameAt(int functionRow);

    int  projectBinaryCount() const;
    int  functionCount() const { return m_functions.size(); }
    QString currentDecompileText() const;
    QString functionDisplayNameAt(int row) const;

    // Phase 11.3.5: read-only access to the most recent analyze's xrefs.
    // Empty before the first successful analyze.
    QVector<GuiXrefRecord> xrefList() const { return m_xrefs; }
    QVector<GuiSymbolRecord> symbolList() const { return m_symbols; }
    QVector<GuiStringRecord> stringList() const { return m_strings; }

    // Phase 11.3.7 (P2.F2 C3): on-demand disasm cache + invocation. RPC
    // server uses runDisasm() to fill the cache, then disasmList() to
    // read it back without a second dispatch.
    bool runDisasm(quint64 funcAddr);
    bool runFullDisasmWindow(quint64 addr, int count);
    bool runFullDisasmOverview();
    QVector<GuiInstructionRecord> disasmList(quint64 funcAddr) const;
    // Phase 11.6 T1 C3: read back the cached rizin pdf annotated text
    // (asm.lines flow arrows). Empty when no disasm has been performed
    // for that function yet, or when the backend didn't emit text.
    QString disasmArrowText(quint64 funcAddr) const;

    // Phase 11.6 T2 C1: build flow-arrow descriptors from a function's
    // raw instruction list. Pure function (no engine touch) — reads
    // ix.type / ix.jump / ix.fail to classify jumps and resolves
    // dstLine by addr lookup within the same instruction list.
    static QVector<GuiFlowArrow>
    computeFlowArrows(const QVector<GuiInstructionRecord>& ins);

    // Phase 11.6 T2 C1: assign each in-function arrow to a "lane" so
    // arrows don't overlap when painted in the gutter. Algorithm:
    //   - sort by length (shortest first), then by srcLine
    //   - greedy assign smallest unused lane such that no other arrow
    //     on that lane overlaps the [min,max] line range
    //   - cap at maxLanes; arrows that don't fit get lane = -1 and
    //     are rendered as overflow stubs
    // Modifies the input vector in place.
    static void
    assignFlowArrowLanes(QVector<GuiFlowArrow>& arrows, int maxLanes = 8);

    // Phase 11.3.8 (P2.F3 C2): CFG accessors. Filter the analyze-time
    // mirror by function_id. RPC + CFG dock both use these.
    QVector<GuiBlockRecord> blocksForFunction(quint64 funcAddr) const;
    QVector<GuiEdgeRecord>  edgesForBlocks(const QVector<GuiBlockRecord>& blocks) const;

    // Phase 11.4.2 (P4.PP4 C3) per ADR-0044: display-only label
    // candidate generation. Reads m_xrefs / m_symbols / m_strings
    // and returns ≤5 ranked candidates (string > import on ties).
    // Empty when the function has no xrefs hitting an import or
    // string. R-9 honoured — no record creation, no engine call.
    QVector<GuiLabelCandidate> generateLabelCandidates(quint64 funcAddr) const;

    // Phase 11.4.3 (P4.PP1 C4) per ADR-0045: display-only type
    // propagation candidates. Caller-rooted: walks m_callEdges where
    // caller_id matches the function with given entry, enumerates
    // each callee's "arg"-kind variables, looks up old type from
    // m_typeFacts. R-9 honoured — no inference, lookup-only.
    QVector<GuiTypePropagationCandidate>
    generateTypePropagationCandidates(quint64 funcAddr,
                                       const QString& targetType) const;

    // Phase 11.4.4 (P4.PP2 C3) per ADR-0046: display-only field
    // candidates. Filters m_variables by function_id and kind=="stack",
    // sorted by stackOffset. (a) op_str regex source is v2 — needs
    // disasm body integration. R-9 honoured.
    QVector<GuiFieldCandidate>
    generateFieldCandidates(quint64 funcAddr) const;

    // Phase 11.4.5 (P4.PP3 C3) per ADR-0047: display-only array
    // candidates. Reads three sources: (a) op_str clusters from the
    // in-process disasmList(funcAddr) cache (callers should runDisasm
    // first), (b) type_facts whose engine literal contains '[' (e.g.
    // "int[10]"), (c) variable cluster of stack vars sorted by offset.
    // Returns ALL three source types in one vector, discriminated by
    // `source`. Per D2 naming hygiene the synthesized output uses
    // arithmetic vocabulary only.
    QVector<GuiArrayCandidate>
    generateArrayCandidates(quint64 funcAddr) const;

    // Phase 11.4.5 (P4.PP3 C4) per ADR-0047 D2: row-text formatter for
    // the Suggest-array-shape dialog, exposed for gui_smoke's naming-
    // hygiene regression guard. The synthesized output uses arithmetic
    // / engine-verbatim vocabulary ONLY — gui_smoke asserts no
    // "stride" / "array" / "element_type" tokens are emitted by AURA
    // (engine-reported `typeStr` literals are explicitly excluded
    // from that scan since they may legitimately contain '[' / '*').
    static QString formatArrayCandidateRow(const GuiArrayCandidate& c);

private slots:
    void onGoToAddress();  // Phase 11.5 — Ctrl+G dialog → jumpToFunction
    void onFindInActiveScope(); // Ctrl+F → last-focused pane/table search
    void onZoomInPanes();  // Phase 11.5 — Ctrl+= → setPaneFontPointSize(+1)
    void onZoomOutPanes(); // Phase 11.5 — Ctrl+- → setPaneFontPointSize(-1)
    void onResetPaneZoom();// Phase 11.5 — Ctrl+0 → setPaneFontPointSize(default)
    void onShowKeyboardShortcuts();  // Phase 11.5 — Ctrl+/ → cheat-sheet QMessageBox
    void onNewProject();
    void onOpenProject();
    void onAddBinary();
    void onAnalyzeClicked();
    void onTableDoubleClicked(const class QModelIndex& idx);
    void onFunctionRowSelected(const class QModelIndex& current,
                               const class QModelIndex& previous);
    void onStringRowActivated(const class QModelIndex& current);
    void onStringCurrentRowChanged(const class QModelIndex& current,
                                   const class QModelIndex& previous);
    void onStringContextMenu(const class QPoint& pos);
    void onFunctionContextMenu(const class QPoint& pos);
    void onAbout();

    // Phase 11.3.9 (P2.F4 C2): DecompilePane context-menu actions.
    void onDecompContextJump(quint64 addr);
    void onDecompContextRename();
    void onDecompContextReset();
    void onDecompContextFindXrefs(quint64 addr);
    void onDecompContextAddComment(quint64 addr);

    // Phase 11.3.9 (P2.F4 C3): function navigation history.
public slots:
    void goBack();
    void goForward();
public:
    bool canGoBack() const    { return !m_navBack.isEmpty(); }
    bool canGoForward() const { return !m_navForward.isEmpty(); }

private:
    void buildMenus();
    void pushRecentProject(const QString& path);
    void rebuildRecentMenu();
    void buildCentralStack();
    void buildStatusBar();
    void applyDarkPalette();
    bool eventFilter(QObject* obj, QEvent* event) override;
    enum class SearchScope {
        Functions,
        Xrefs,
        Strings,
        Symbols,
        Imports,
        Decompile,
        Disassembly,
        FullDisassembly,
        CFG,
        Hex,
    };
    void installSearchScope(QWidget* root, SearchScope scope);
    QString searchScopeLabel(SearchScope scope) const;
    bool searchTreeView(QTreeView* view, const QString& needle);
    bool searchPlainText(QPlainTextEdit* view, const QString& needle);
    QPlainTextEdit* activeTextEditIn(QWidget* pane) const;
    bool searchInScope(SearchScope scope, const QString& needle);
    int  functionRowContainingAddress(quint64 addr) const;
    bool persistStringOverride(int stringRow) const;
    void closeProject();
    void updateWindowTitle();
    void restoreUiState();
    void saveUiState();

    int  selectedProjectRow() const;
    bool runAnalyze(int row, AuraAnalysisLevel level);
    bool runDecompile(quint64 funcAddr);
    /* runDisasm now in public section (Phase 11.3.7 RPC needs access). */

    // Override pipeline.
    AuraOverrideKey buildKeyForFunction(int functionRow) const;
    void            applyOverridesToFunctions();   // post-analyze + post-rename

    void closeEvent(class QCloseEvent* event) override;

    // Phase 11.5 (P5 polish): drag-drop binary onto the window.
    // dropEvent extracts local-file URLs and forwards to
    // handleDroppedPaths.
    void dragEnterEvent(class QDragEnterEvent* event) override;
    void dropEvent     (class QDropEvent*      event) override;

    // Outer (project / function workspace) stacked switch.
    QStackedWidget*      m_stack          = nullptr;

    // Page 0: project view.
    QTableView*          m_projectTable   = nullptr;
    ProjectBinaryModel*  m_projectModel   = nullptr;
    QPushButton*         m_analyzeButton  = nullptr;

    // Page 1: nested QMainWindow workspace (Cutter-style, ADR-0036).
    QMainWindow*         m_workspace      = nullptr;
    QDockWidget*         m_functionDock   = nullptr;
    QTreeView*           m_functionTable  = nullptr;
    FunctionTableModel*  m_functionModel  = nullptr;
    QDockWidget*         m_decompileDock  = nullptr;
    DecompilePane*       m_decompilePane  = nullptr;
    QDockWidget*         m_disasmDock     = nullptr;
    DisasmPane*          m_disasmPane     = nullptr;
    QDockWidget*         m_fullDisasmDock = nullptr;
    FullDisasmPane*      m_fullDisasmPane = nullptr;
    QDockWidget*         m_xrefsDock      = nullptr;
    QTreeView*           m_xrefsTable     = nullptr;
    XrefTableModel*      m_xrefsModel     = nullptr;
    QDockWidget*         m_symbolsDock    = nullptr;
    QTreeView*           m_symbolsTable   = nullptr;
    SymbolTableModel*    m_symbolsModel   = nullptr;
    QDockWidget*         m_importsDock    = nullptr;
    QTreeView*           m_importsTable   = nullptr;
    SymbolTableModel*    m_importsModel   = nullptr;
    QDockWidget*         m_stringsDock    = nullptr;
    QTreeView*           m_stringsTable   = nullptr;
    StringTableModel*    m_stringsModel   = nullptr;
    QDockWidget*         m_cfgDock        = nullptr;
    CfgPane*             m_cfgPane        = nullptr;
    QDockWidget*         m_hexDock        = nullptr;
    HexPane*             m_hexPane        = nullptr;

    // Project state.
    AuraProjectBinaries* m_projectDb      = nullptr;
    AuraOverrideStore*   m_overrideStore  = nullptr;
    QString              m_projectPath;
    QString              m_currentBinaryPath;
    QByteArray           m_currentSha256;  // 32-byte raw digest
    /* Phase 11.3.9: addr of the function currently displayed in the
     * Decomp/Disasm/CFG panes — set by onFunctionRowSelected. Used by
     * context-menu actions that target the active function (Rename,
     * Reset name). 0 when no function is active. */
    quint64              m_activeFunctionAddr = 0;

    // Phase 11.3.9 (P2.F4 C3): nav history stacks (browser-style).
    // m_navInProgress prevents goBack/goForward from re-pushing into
    // the back stack when they synthesise a row selection.
    QStack<quint64>      m_navBack;
    QStack<quint64>      m_navForward;
    bool                 m_navInProgress = false;
    class QAction*       m_actNavBack    = nullptr;
    class QAction*       m_actNavForward = nullptr;
    QVector<GuiFunctionRecord> m_functions;
    QVector<GuiXrefRecord>     m_xrefs;
    QVector<GuiSymbolRecord>   m_symbols;
    QVector<GuiStringRecord>   m_strings;
    QVector<GuiBlockRecord>    m_blocks;       // Phase 11.3.8
    QVector<GuiEdgeRecord>     m_edges;        // Phase 11.3.8
    QVector<GuiCallEdgeRecord> m_callEdges;    // Phase 11.4.3
    QVector<GuiVariableRecord> m_variables;    // Phase 11.4.3
    QVector<GuiTypeFactRecord> m_typeFacts;    // Phase 11.4.3
    AuraOverrideBinaryFingerprint m_currentFingerprint{};
    SearchScope m_activeSearchScope = SearchScope::Functions;

    // Menu actions.
    QAction* m_actNewProject     = nullptr;
    QAction* m_actOpenProject    = nullptr;
    QAction* m_actAddBinary      = nullptr;
    QAction* m_actQuit           = nullptr;
    QAction* m_actBackToProject  = nullptr;
    QAction* m_actAbout          = nullptr;

    // Phase 11.5: recent-projects submenu (rebuilt on each push).
    class QMenu* m_recentMenu    = nullptr;
};

}  // namespace aura::gui
