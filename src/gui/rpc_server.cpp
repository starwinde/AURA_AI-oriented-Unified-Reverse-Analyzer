// src/gui/rpc_server.cpp — implementation. ADR-0038.

#include "rpc_server.h"

#include "main_window.h"

#include <QHostAddress>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QSet>
#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QtCore/QCoreApplication>

#include "cJSON.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace aura::gui {

namespace {

constexpr int kDemoMaxFunctions = 3;
constexpr int kDemoMaxStrings = 5;
constexpr int kDemoMaxReferences = 5;
constexpr int kDemoMaxVariableReferences = 5;

QString genRandomTokenHex() {
    QByteArray raw(32, 0);
    auto* rng = QRandomGenerator::system();
    for (int i = 0; i < raw.size(); ++i) {
        raw[i] = static_cast<char>(rng->bounded(256));
    }
    return QString::fromLatin1(raw.toHex());
}

QString resultJson(bool ok, cJSON* result_or_null, const char* err_or_null) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "ok", ok);
    if (ok) {
        if (result_or_null)
            cJSON_AddItemToObject(root, "result", result_or_null);
        else
            cJSON_AddItemToObject(root, "result", cJSON_CreateObject());
    } else {
        cJSON_AddStringToObject(root, "error", err_or_null ? err_or_null : "");
    }
    char* s = cJSON_PrintUnformatted(root);
    QString out = QString::fromUtf8(s);
    free(s);
    cJSON_Delete(root);
    return out;
}

const char* cstr(cJSON* o, const char* key) {
    cJSON* v = cJSON_GetObjectItemCaseSensitive(o, key);
    return (v && cJSON_IsString(v)) ? v->valuestring : nullptr;
}

int intval(cJSON* o, const char* key, int defv) {
    cJSON* v = cJSON_GetObjectItemCaseSensitive(o, key);
    return (v && cJSON_IsNumber(v)) ? v->valueint : defv;
}

QString summarizeCount(cJSON* object, const char* key) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(object, key);
    if (!cJSON_IsNumber(value)) return {};
    return QStringLiteral("%1=%2").arg(QString::fromLatin1(key)).arg(value->valueint);
}

QString summarizeArray(cJSON* object, const char* key) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(object, key);
    if (!cJSON_IsArray(value)) return {};
    return QStringLiteral("%1=%2").arg(QString::fromLatin1(key)).arg(cJSON_GetArraySize(value));
}

QString summarizeRpcActivityResult(const QString& response) {
    cJSON* root = cJSON_Parse(response.toUtf8().constData());
    if (!root) return QStringLiteral("invalid response");

    QStringList parts;
    cJSON* ok = cJSON_GetObjectItemCaseSensitive(root, "ok");
    cJSON* result = cJSON_GetObjectItemCaseSensitive(root, "result");
    if (cJSON_IsObject(result)) {
        for (const char* key : {"binary_count", "function_count",
                                "string_row", "function_addr"}) {
            const QString part = summarizeCount(result, key);
            if (!part.isEmpty()) parts.push_back(part);
        }
        for (const char* key : {"functions", "strings", "symbols", "xrefs",
                                "instructions", "blocks", "edges"}) {
            const QString part = summarizeArray(result, key);
            if (!part.isEmpty()) parts.push_back(part);
        }
        cJSON* snapshot = cJSON_GetObjectItemCaseSensitive(result,
                                                           "snapshot_schema");
        if (cJSON_IsNumber(snapshot)) {
            cJSON* protectedOnly =
                cJSON_GetObjectItemCaseSensitive(result, "protected_only");
            parts.push_back(QStringLiteral("snapshot=demo_minimal"));
            if (cJSON_IsBool(protectedOnly)) {
                parts.push_back(QStringLiteral("protected_only=%1")
                                    .arg(cJSON_IsTrue(protectedOnly)
                                             ? QStringLiteral("true")
                                             : QStringLiteral("false")));
            }
        }
    }

    if (parts.isEmpty() && cJSON_IsFalse(ok)) {
        cJSON* error = cJSON_GetObjectItemCaseSensitive(root, "error");
        if (cJSON_IsString(error) && error->valuestring) {
            parts.push_back(QStringLiteral("error=%1")
                                .arg(QString::fromUtf8(error->valuestring)));
        }
    }
    if (parts.isEmpty()) parts.push_back(QStringLiteral("no returned records"));

    cJSON_Delete(root);
    return parts.join(QStringLiteral("; "));
}

cJSON* stringRecordJson(const GuiStringRecord& s, bool protectedOnly) {
    cJSON* row = cJSON_CreateObject();
    cJSON_AddNumberToObject(row, "string_id",
                            static_cast<double>(s.stringId));
    cJSON_AddNumberToObject(row, "addr",
                            static_cast<double>(s.addr));
    cJSON_AddNumberToObject(row, "length",
                            static_cast<double>(s.length));
    cJSON_AddStringToObject(row, "encoding",
                            s.encoding.toUtf8().constData());
    cJSON_AddStringToObject(row, "detected_encoding",
                            s.encoding.toUtf8().constData());
    cJSON_AddNumberToObject(row, "encoding_confidence",
                            s.encodingConfidence);
    cJSON_AddBoolToObject(row, "encoding_lossy", s.encodingLossy);
    cJSON_AddStringToObject(row, "display_literal",
                            s.displayLiteral.toUtf8().constData());
    cJSON_AddStringToObject(row, "section",
                            s.section.toUtf8().constData());
    if (!protectedOnly) {
        cJSON_AddStringToObject(row, "content",
                                s.content.toUtf8().constData());
    }
    cJSON_AddBoolToObject(row, "has_protection", s.hasProtection);
    const bool hasEffectiveMask =
        !s.maskedContent.isEmpty() && s.maskedContent != s.content;
    const QString maskedContent =
        hasEffectiveMask ? s.maskedContent : QString();
    cJSON_AddStringToObject(row, "masked_content",
                            maskedContent.toUtf8().constData());
    cJSON_AddStringToObject(row, "protected_value",
                            (protectedOnly ? s.exportValue : s.protectedValue)
                                .toUtf8().constData());
    cJSON_AddStringToObject(row, "display_value",
                            s.protectedValue.toUtf8().constData());
    cJSON_AddStringToObject(row, "transmission_value",
                            s.exportValue.toUtf8().constData());
    cJSON_AddStringToObject(row, "transmission_policy", "protected");
    cJSON_AddBoolToObject(row, "original_included", false);
    cJSON_AddStringToObject(row, "export_value",
                            s.exportValue.toUtf8().constData());
    cJSON_AddStringToObject(row, "protection_summary",
                            s.protectionSummary.toUtf8().constData());
    cJSON* findings = cJSON_AddArrayToObject(row, "findings");
    for (const auto& f : s.findings) {
        cJSON* fr = cJSON_CreateObject();
        cJSON_AddStringToObject(fr, "detector_id",
                                f.detectorId.toUtf8().constData());
        cJSON_AddStringToObject(fr, "kind",
                                f.kind.toUtf8().constData());
        cJSON_AddNumberToObject(fr, "start_offset", f.startOffset);
        cJSON_AddNumberToObject(fr, "end_offset", f.endOffset);
        cJSON_AddNumberToObject(fr, "confidence", f.confidence);
        cJSON_AddStringToObject(fr, "mask_token",
                                f.maskToken.toUtf8().constData());
        cJSON_AddItemToArray(findings, fr);
    }
    cJSON_AddStringToObject(row, "source",
                            s.source.toUtf8().constData());
    cJSON_AddBoolToObject(row, "protected_only", protectedOnly);
    return row;
}

QString hexAddr(quint64 value) {
    return QStringLiteral("0x%1").arg(value, 0, 16);
}

cJSON* demoFunctionJson(int row, const QString& name) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "row", row);
    cJSON_AddStringToObject(item, "name", name.toUtf8().constData());
    return item;
}

cJSON* demoCommentJson(int row, const QString& functionName) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "function_row", row);
    cJSON_AddStringToObject(item, "function_name",
                            functionName.toUtf8().constData());
    cJSON_AddStringToObject(item, "comment", "<COMMENT_OMITTED>");
    cJSON_AddBoolToObject(item, "raw_comment_text_omitted", true);
    return item;
}

cJSON* demoStringJson(const GuiStringRecord& s) {
    const bool masked =
        !s.maskedContent.isEmpty() && s.maskedContent != s.content;
    const QString protectedValue =
        masked ? s.exportValue : QStringLiteral("<RAW_CONTENT_OMITTED>");

    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "string_id",
                            static_cast<double>(s.stringId));
    cJSON_AddNumberToObject(item, "addr", static_cast<double>(s.addr));
    cJSON_AddStringToObject(item, "addr_hex",
                            hexAddr(s.addr).toUtf8().constData());
    cJSON_AddNumberToObject(item, "length",
                            static_cast<double>(s.length));
    cJSON_AddStringToObject(item, "encoding",
                            s.encoding.toUtf8().constData());
    cJSON_AddStringToObject(item, "detected_encoding",
                            s.encoding.toUtf8().constData());
    cJSON_AddBoolToObject(item, "encoding_lossy", s.encodingLossy);
    cJSON_AddStringToObject(item, "protected_value",
                            protectedValue.toUtf8().constData());
    cJSON_AddBoolToObject(item, "masked", masked);
    cJSON_AddBoolToObject(item, "has_protection", s.hasProtection);
    cJSON_AddNumberToObject(item, "findings_count", s.findings.size());
    cJSON_AddBoolToObject(item, "raw_content_omitted", true);
    return item;
}

cJSON* demoXrefJson(const GuiXrefRecord& x,
                    const QSet<quint64>& stringAddrs) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "from", static_cast<double>(x.from));
    cJSON_AddStringToObject(item, "from_hex",
                            hexAddr(x.from).toUtf8().constData());
    cJSON_AddNumberToObject(item, "to", static_cast<double>(x.to));
    cJSON_AddStringToObject(item, "to_hex",
                            hexAddr(x.to).toUtf8().constData());
    cJSON_AddStringToObject(item, "kind", x.kind.toUtf8().constData());
    cJSON_AddStringToObject(item, "target_kind",
                            stringAddrs.contains(x.to) ? "string" : "address");
    return item;
}

cJSON* demoVariableJson(const GuiVariableRecord& v) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "var_id", v.varId);
    cJSON_AddNumberToObject(item, "function_id", v.functionId);
    cJSON_AddStringToObject(item, "name",
                            v.name.isEmpty()
                                ? "<unnamed>"
                                : v.name.toUtf8().constData());
    cJSON_AddStringToObject(item, "kind", v.kind.toUtf8().constData());
    cJSON_AddNumberToObject(item, "stack_offset", v.stackOffset);
    cJSON_AddBoolToObject(item, "op_str_omitted", true);
    return item;
}

cJSON* variableOverrideJson(const GuiVariableOverride& ov) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "var_id", ov.varId);
    cJSON_AddNumberToObject(item, "function_id", ov.functionId);
    cJSON_AddBoolToObject(item, "has_alias", ov.hasAlias);
    cJSON_AddBoolToObject(item, "has_type", ov.hasType);
    cJSON_AddStringToObject(
        item, "alias",
        ov.hasAlias ? "<ALIAS_OMITTED>" : "");
    cJSON_AddStringToObject(
        item, "type",
        ov.hasType ? "<TYPE_OMITTED>" : "");
    cJSON_AddBoolToObject(item, "raw_alias_omitted", ov.hasAlias);
    cJSON_AddBoolToObject(item, "raw_type_omitted", ov.hasType);
    cJSON_AddBoolToObject(item, "protected_only", true);
    return item;
}

cJSON* demoRiskJson(const GuiMalwareRiskFinding& risk) {
    cJSON* item = cJSON_CreateObject();
    cJSON_AddStringToObject(item, "severity", risk.severity.toUtf8().constData());
    cJSON_AddStringToObject(item, "category", risk.category.toUtf8().constData());
    cJSON_AddStringToObject(item, "title", risk.title.toUtf8().constData());
    cJSON_AddStringToObject(item, "source", risk.source.toUtf8().constData());
    cJSON_AddStringToObject(item, "evidence", "<EVIDENCE_OMITTED>");
    cJSON_AddBoolToObject(item, "raw_evidence_omitted", true);
    return item;
}

QString protectedDecompileText(QString text) {
    static const QRegularExpression commentLine(
        QStringLiteral("(?m)^// AURA comment:.*(?:\\r?\\n)?"));
    text.remove(commentLine);
    return text;
}

int boundedQtCount(qsizetype value, int maxValue) {
    if (value <= 0) return 0;
    const qsizetype cap = static_cast<qsizetype>(maxValue);
    return static_cast<int>(value < cap ? value : cap);
}

}  // namespace

RpcServer::RpcServer(MainWindow* mw, QObject* parent)
    : QObject(parent), m_mw(mw) {}

RpcServer::~RpcServer() {
    if (m_server) m_server->close();
}

bool RpcServer::start(quint16 port) {
    // Token: env override or random.
    if (const char* env = std::getenv("AURA_GUI_RPC_TOKEN")) {
        m_token = QString::fromUtf8(env);
    } else {
        m_token = genRandomTokenHex();
    }

    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this,
            &RpcServer::onNewConnection);

    if (!m_server->listen(QHostAddress(QHostAddress::LocalHost), port)) {
        std::fprintf(stderr, "[rpc] listen failed on 127.0.0.1:%u — %s\n",
                     static_cast<unsigned>(port),
                     m_server->errorString().toUtf8().constData());
        return false;
    }
    m_port = m_server->serverPort();
    std::fprintf(stdout, "[rpc] listening on 127.0.0.1:%u  token=%s\n",
                 static_cast<unsigned>(m_port),
                 m_token.toUtf8().constData());
    std::fflush(stdout);
    return true;
}

void RpcServer::onNewConnection() {
    QTcpSocket* sock = m_server->nextPendingConnection();
    if (!sock) return;
    if (m_client) {
        // v1: single client only.
        sock->write("{\"ok\":false,\"error\":\"another client already connected\"}\n");
        sock->flush();
        sock->disconnectFromHost();
        sock->deleteLater();
        return;
    }
    m_client = sock;
    m_buffer.clear();
    connect(m_client, &QTcpSocket::readyRead, this, &RpcServer::onReadyRead);
    connect(m_client, &QTcpSocket::disconnected, this,
            &RpcServer::onDisconnected);
}

void RpcServer::onDisconnected() {
    if (m_client) {
        m_client->deleteLater();
        m_client = nullptr;
    }
    m_buffer.clear();
}

void RpcServer::onReadyRead() {
    if (!m_client) return;
    m_buffer += m_client->readAll();

    while (true) {
        const int nl = m_buffer.indexOf('\n');
        if (nl < 0) break;
        const QByteArray line = m_buffer.left(nl);
        m_buffer.remove(0, nl + 1);

        const QString resp = dispatch(line);
        m_client->write(resp.toUtf8());
        m_client->write("\n");
        m_client->flush();
    }
}

QString RpcServer::dispatch(const QByteArray& jsonLine) {
    cJSON* root = cJSON_ParseWithLength(jsonLine.constData(),
                                        static_cast<size_t>(jsonLine.size()));
    if (!root) {
        return resultJson(false, nullptr, "invalid JSON");
    }

    const char* method = cstr(root, "method");
    const char* token  = cstr(root, "token");
    cJSON*      params = cJSON_GetObjectItemCaseSensitive(root, "params");

    auto fail = [&](const char* msg) {
        cJSON_Delete(root);
        return resultJson(false, nullptr, msg);
    };

    if (!method) return fail("missing method");
    if (!token || m_token != QString::fromUtf8(token))
        return fail("invalid token");
    if (!m_mw) return fail("MainWindow null");

    QString out;
    if (std::strcmp(method, "status") == 0) {
        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "binary_count", m_mw->projectBinaryCount());
        cJSON_AddNumberToObject(r, "function_count", m_mw->functionCount());
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "open_project") == 0) {
        const char* p = cstr(params, "path");
        if (!p) return fail("missing path");
        bool ok = m_mw->openProject(QString::fromUtf8(p));
        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "binary_count", m_mw->projectBinaryCount());
        out = resultJson(ok, ok ? r : nullptr,
                         ok ? nullptr : "open_project failed");
        if (!ok) cJSON_Delete(r);
    } else if (std::strcmp(method, "add_binary") == 0) {
        const char* p = cstr(params, "path");
        if (!p) return fail("missing path");
        bool ok = m_mw->addBinary(QString::fromUtf8(p));
        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "binary_count", m_mw->projectBinaryCount());
        out = resultJson(ok, ok ? r : nullptr,
                         ok ? nullptr : "add_binary failed");
        if (!ok) cJSON_Delete(r);
    } else if (std::strcmp(method, "analyze") == 0) {
        const int row = intval(params, "row", 0);
        const char* lvl = cstr(params, "level");
        AuraAnalysisLevel level = AURA_ANALYSIS_LEVEL_FULL;
        if (lvl && std::strcmp(lvl, "quick") == 0)
            level = AURA_ANALYSIS_LEVEL_QUICK;
        else if (lvl && (std::strcmp(lvl, "advanced") == 0 ||
                         std::strcmp(lvl, "aggressive") == 0))
            level = AURA_ANALYSIS_LEVEL_ADVANCED;
        bool ok = m_mw->analyzeBinaryAt(row, level);
        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "function_count", m_mw->functionCount());
        out = resultJson(ok, ok ? r : nullptr,
                         ok ? nullptr : "analyze failed");
        if (!ok) cJSON_Delete(r);
    } else if (std::strcmp(method, "decompile") == 0) {
        const int row = intval(params, "function_row", 0);
        bool ok = m_mw->decompileFunctionAt(row);
        if (!ok) {
            out = resultJson(false, nullptr, "decompile failed");
            cJSON_Delete(root);
            return out;
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddStringToObject(r, "text",
            m_mw->renderProtectedDecompileTextForFunctionRow(
                    row, m_mw->currentDecompileText())
                .toUtf8()
                .constData());
        cJSON_AddBoolToObject(r, "raw_comment_text_omitted", true);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "jump_string_reference") == 0) {
        const int row = intval(params, "string_row", 0);
        bool ok = m_mw->jumpToStringReference(row);
        if (!ok) {
            out = resultJson(false, nullptr, "jump_string_reference failed");
            cJSON_Delete(root);
            return out;
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "string_row", row);
        cJSON_AddStringToObject(r, "text",
            m_mw->renderProtectedDecompileTextForFunctionRow(
                    -1, m_mw->currentDecompileText())
                .toUtf8()
                .constData());
        cJSON_AddBoolToObject(r, "raw_comment_text_omitted", true);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "rename") == 0) {
        const int row = intval(params, "function_row", 0);
        const char* nn = cstr(params, "new_name");
        if (!nn) return fail("missing new_name");
        bool ok = m_mw->renameFunctionAt(row, QString::fromUtf8(nn));
        cJSON* r = cJSON_CreateObject();
        cJSON_AddStringToObject(r, "display_name",
            m_mw->functionDisplayNameAt(row).toUtf8().constData());
        out = resultJson(ok, ok ? r : nullptr,
                         ok ? nullptr : "rename failed");
        if (!ok) cJSON_Delete(r);
    } else if (std::strcmp(method, "reset_name") == 0) {
        const int row = intval(params, "function_row", 0);
        bool ok = m_mw->resetFunctionNameAt(row);
        cJSON* r = cJSON_CreateObject();
        cJSON_AddStringToObject(r, "display_name",
            m_mw->functionDisplayNameAt(row).toUtf8().constData());
        out = resultJson(ok, ok ? r : nullptr,
                         ok ? nullptr : "reset_name failed");
        if (!ok) cJSON_Delete(r);
    } else if (std::strcmp(method, "function_list") == 0) {
        const int n = m_mw->functionCount();
        cJSON* arr = cJSON_CreateArray();
        for (int i = 0; i < n; ++i) {
            cJSON* row = cJSON_CreateObject();
            cJSON_AddNumberToObject(row, "row", i);
            cJSON_AddStringToObject(row, "name",
                m_mw->functionDisplayNameAt(i).toUtf8().constData());
            cJSON_AddItemToArray(arr, row);
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddItemToObject(r, "functions", arr);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "list_symbols") == 0) {
        // Phase 11.3.5: surface normalized symbols (incl. imports).
        const auto syms = m_mw->symbolList();
        cJSON* arr = cJSON_CreateArray();
        for (const auto& s : syms) {
            cJSON* row = cJSON_CreateObject();
            cJSON_AddNumberToObject(row, "addr", static_cast<double>(s.addr));
            cJSON_AddStringToObject(row, "kind", s.kind.toUtf8().constData());
            cJSON_AddStringToObject(row, "name", s.name.toUtf8().constData());
            cJSON_AddStringToObject(row, "source",
                                    s.source.toUtf8().constData());
            cJSON_AddItemToArray(arr, row);
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddItemToObject(r, "symbols", arr);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "disasm_function") == 0) {
        // Phase 11.3.7 (P2.F2 C3): on-demand disasm for a function entry.
        // params: { "addr": <number> }
        if (!params || !cJSON_IsObject(params)) {
            out = resultJson(false, nullptr, "params object required");
        } else {
            cJSON* a = cJSON_GetObjectItem(params, "addr");
            if (!a || !cJSON_IsNumber(a)) {
                out = resultJson(false, nullptr, "params.addr (number) required");
            } else {
                quint64 funcAddr = static_cast<quint64>(a->valuedouble);
                bool ok = m_mw->runDisasm(funcAddr);
                if (!ok) {
                    out = resultJson(false, nullptr, "disasm dispatch failed");
                } else {
                    const auto ins = m_mw->disasmList(funcAddr);
                    cJSON* arr = cJSON_CreateArray();
                    for (const auto& r : ins) {
                        cJSON* row = cJSON_CreateObject();
                        cJSON_AddNumberToObject(row, "addr",
                                                static_cast<double>(r.addr));
                        cJSON_AddNumberToObject(row, "size",
                                                static_cast<double>(r.size));
                        cJSON_AddStringToObject(row, "bytes",
                                                r.bytes.toUtf8().constData());
                        cJSON_AddStringToObject(row, "mnemonic",
                                                r.mnemonic.toUtf8().constData());
                        cJSON_AddStringToObject(row, "op_str",
                                                r.opStr.toUtf8().constData());
                        cJSON_AddStringToObject(row, "type",
                                                r.type.toUtf8().constData());
                        cJSON_AddNumberToObject(row, "jump",
                                                static_cast<double>(r.jump));
                        cJSON_AddNumberToObject(row, "fail",
                                                static_cast<double>(r.fail));
                        cJSON_AddStringToObject(row, "source",
                                                r.source.toUtf8().constData());
                        cJSON_AddItemToArray(arr, row);
                    }
                    cJSON* result = cJSON_CreateObject();
                    cJSON_AddNumberToObject(result, "function_addr",
                                            static_cast<double>(funcAddr));
                    cJSON_AddItemToObject(result, "instructions", arr);
                    // Phase 11.6 T1 C3: surface the rizin pdf text (asm.lines
                    // flow arrows) cached by runDisasm. Empty string when the
                    // backend (older Rizin) didn't emit it.
                    const QString arrowText =
                        m_mw->disasmArrowText(funcAddr);
                    cJSON_AddStringToObject(result, "text",
                        arrowText.toUtf8().constData());
                    out = resultJson(true, result, nullptr);
                }
            }
        }
    } else if (std::strcmp(method, "cfg_function") == 0) {
        // Phase 11.3.8 (P2.F3 C2): per-function CFG. Data ownership stays
        // in the analyze body (ADR-0041 D1). params: { "addr": <number> }.
        if (!params || !cJSON_IsObject(params)) {
            out = resultJson(false, nullptr, "params object required");
        } else {
            cJSON* a = cJSON_GetObjectItem(params, "addr");
            if (!a || !cJSON_IsNumber(a)) {
                out = resultJson(false, nullptr,
                                  "params.addr (number) required");
            } else {
                quint64 funcAddr = static_cast<quint64>(a->valuedouble);
                const auto bs = m_mw->blocksForFunction(funcAddr);
                const auto es = m_mw->edgesForBlocks(bs);
                cJSON* barr = cJSON_CreateArray();
                for (const auto& b : bs) {
                    cJSON* row = cJSON_CreateObject();
                    cJSON_AddNumberToObject(row, "block_id",
                                             static_cast<double>(b.blockId));
                    cJSON_AddNumberToObject(row, "function_id",
                                             static_cast<double>(b.functionId));
                    cJSON_AddNumberToObject(row, "start",
                                             static_cast<double>(b.startAddr));
                    cJSON_AddNumberToObject(row, "end",
                                             static_cast<double>(b.endAddr));
                    cJSON_AddStringToObject(row, "source",
                                             b.source.toUtf8().constData());
                    cJSON_AddItemToArray(barr, row);
                }
                cJSON* earr = cJSON_CreateArray();
                for (const auto& e : es) {
                    cJSON* row = cJSON_CreateObject();
                    cJSON_AddNumberToObject(row, "src",
                                             static_cast<double>(e.srcBlock));
                    cJSON_AddNumberToObject(row, "dst",
                                             static_cast<double>(e.dstBlock));
                    cJSON_AddStringToObject(row, "kind",
                                             e.kind.toUtf8().constData());
                    cJSON_AddStringToObject(row, "source",
                                             e.source.toUtf8().constData());
                    cJSON_AddItemToArray(earr, row);
                }
                cJSON* result = cJSON_CreateObject();
                cJSON_AddNumberToObject(result, "function_addr",
                                         static_cast<double>(funcAddr));
                cJSON_AddItemToObject(result, "blocks", barr);
                cJSON_AddItemToObject(result, "edges",  earr);
                out = resultJson(true, result, nullptr);
            }
        }
    } else if (std::strcmp(method, "list_strings") == 0) {
        // Phase 11.3.6: surface normalized literal strings (rizin izj).
        const auto strs = m_mw->stringList();
        cJSON* arr = cJSON_CreateArray();
        for (const auto& s : strs) {
            cJSON_AddItemToArray(arr, stringRecordJson(s, false));
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddItemToObject(r, "strings", arr);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "list_protected_strings") == 0) {
        // External LLM/MCP-facing shape: no raw content field.
        const auto strs = m_mw->stringList();
        cJSON* arr = cJSON_CreateArray();
        for (const auto& s : strs) {
            cJSON_AddItemToArray(arr, stringRecordJson(s, true));
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddItemToObject(r, "strings", arr);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "list_xrefs") == 0) {
        // Phase 11.3.5: surface normalized xrefs to RPC clients.
        const auto xrefs = m_mw->xrefList();
        cJSON* arr = cJSON_CreateArray();
        for (const auto& x : xrefs) {
            cJSON* row = cJSON_CreateObject();
            cJSON_AddNumberToObject(row, "from", static_cast<double>(x.from));
            cJSON_AddNumberToObject(row, "to",   static_cast<double>(x.to));
            cJSON_AddStringToObject(row, "kind", x.kind.toUtf8().constData());
            cJSON_AddStringToObject(row, "source",
                                    x.source.toUtf8().constData());
            cJSON_AddItemToArray(arr, row);
        }
        cJSON* r = cJSON_CreateObject();
        cJSON_AddItemToObject(r, "xrefs", arr);
        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "demo_snapshot") == 0) {
        const auto strings = m_mw->stringList();
        const auto xrefs = m_mw->xrefList();
        const auto variables = m_mw->variableList();
        const auto variableOverrides = m_mw->variableOverrideList();
        const auto risks = m_mw->malwareRiskList();
        const int functionCount = m_mw->functionCount();
        const int functionsIncluded =
            functionCount < kDemoMaxFunctions ? functionCount : kDemoMaxFunctions;
        const int stringsIncluded =
            boundedQtCount(strings.size(), kDemoMaxStrings);
        const int refsIncluded =
            boundedQtCount(xrefs.size(), kDemoMaxReferences);
        const int variablesIncluded =
            boundedQtCount(variables.size(), kDemoMaxVariableReferences);
        const int variableOverridesIncluded =
            boundedQtCount(variableOverrides.size(),
                           kDemoMaxVariableReferences);
        int commentsTotal = 0;
        for (int i = 0; i < functionCount; ++i) {
            if (!m_mw->functionCommentAt(i).isEmpty()) {
                ++commentsTotal;
            }
        }
        const int commentsIncluded =
            commentsTotal < 5 ? commentsTotal : 5;

        cJSON* r = cJSON_CreateObject();
        cJSON_AddNumberToObject(r, "snapshot_schema", 1);
        cJSON_AddStringToObject(r, "disclosure", "demo_minimal");
        cJSON_AddBoolToObject(r, "protected_only", true);

        cJSON* counts = cJSON_AddObjectToObject(r, "counts");
        cJSON_AddNumberToObject(counts, "functions_total", functionCount);
        cJSON_AddNumberToObject(counts, "functions_included",
                                functionsIncluded);
        cJSON_AddNumberToObject(counts, "strings_total", strings.size());
        cJSON_AddNumberToObject(counts, "strings_included",
                                stringsIncluded);
        cJSON_AddNumberToObject(counts, "references_total", xrefs.size());
        cJSON_AddNumberToObject(counts, "references_included",
                                refsIncluded);
        cJSON_AddNumberToObject(counts, "variable_references_total",
                                variables.size());
        cJSON_AddNumberToObject(counts, "variable_references_included",
                                variablesIncluded);
        cJSON_AddNumberToObject(counts, "variable_overrides_total",
                                variableOverrides.size());
        cJSON_AddNumberToObject(counts, "variable_overrides_included",
                                variableOverridesIncluded);
        cJSON_AddNumberToObject(counts, "malware_risks_total",
                                risks.size());
        cJSON_AddNumberToObject(counts, "comments_total", commentsTotal);
        cJSON_AddNumberToObject(counts, "comments_included",
                                commentsIncluded);

        cJSON* functions = cJSON_AddArrayToObject(r, "functions_sent");
        for (int i = 0; i < functionsIncluded; ++i) {
            cJSON_AddItemToArray(
                functions,
                demoFunctionJson(i, m_mw->functionDisplayNameAt(i)));
        }

        cJSON* comments = cJSON_AddArrayToObject(r, "comments_sent");
        int emittedComments = 0;
        for (int i = 0; i < functionCount &&
                        emittedComments < commentsIncluded; ++i) {
            if (m_mw->functionCommentAt(i).isEmpty()) continue;
            cJSON_AddItemToArray(
                comments,
                demoCommentJson(i, m_mw->functionDisplayNameAt(i)));
            ++emittedComments;
        }

        QSet<quint64> stringAddrs;
        cJSON* stringItems = cJSON_AddArrayToObject(r, "strings_sent");
        for (int i = 0; i < strings.size(); ++i) {
            stringAddrs.insert(strings[i].addr);
            if (i < kDemoMaxStrings) {
                cJSON_AddItemToArray(stringItems, demoStringJson(strings[i]));
            }
        }

        cJSON* refs = cJSON_AddArrayToObject(r, "references_sent");
        for (int i = 0; i < refsIncluded; ++i) {
            cJSON_AddItemToArray(refs, demoXrefJson(xrefs[i], stringAddrs));
        }

        cJSON* varRefs =
            cJSON_AddArrayToObject(r, "variable_references_sent");
        for (int i = 0; i < variablesIncluded; ++i) {
            cJSON_AddItemToArray(varRefs, demoVariableJson(variables[i]));
        }

        cJSON* variableOverrideItems =
            cJSON_AddArrayToObject(r, "variable_overrides_sent");
        for (int i = 0; i < variableOverridesIncluded; ++i) {
            cJSON_AddItemToArray(variableOverrideItems,
                                 variableOverrideJson(variableOverrides[i]));
        }

        cJSON* riskItems = cJSON_AddArrayToObject(r, "malware_risks_sent");
        for (int i = 0; i < boundedQtCount(risks.size(), 5); ++i) {
            cJSON_AddItemToArray(riskItems, demoRiskJson(risks[i]));
        }

        cJSON* omissions = cJSON_AddObjectToObject(r, "omissions");
        cJSON_AddBoolToObject(omissions, "raw_string_content_omitted", true);
        cJSON_AddBoolToObject(omissions, "disassembly_text_omitted", true);
        cJSON_AddBoolToObject(omissions, "op_str_omitted", true);
        cJSON_AddBoolToObject(omissions, "raw_comment_text_omitted", true);
        cJSON_AddBoolToObject(omissions, "raw_variable_alias_omitted", true);
        cJSON_AddBoolToObject(omissions, "raw_variable_type_omitted", true);
        cJSON_AddBoolToObject(omissions, "raw_risk_evidence_omitted", true);

        out = resultJson(true, r, nullptr);
    } else if (std::strcmp(method, "quit") == 0) {
        out = resultJson(true, nullptr, nullptr);
        QCoreApplication::quit();
    } else {
        out = resultJson(false, nullptr, "unknown method");
    }

    if (m_mw) {
        cJSON* response = cJSON_Parse(out.toUtf8().constData());
        cJSON* ok = response
                        ? cJSON_GetObjectItemCaseSensitive(response, "ok")
                        : nullptr;
        m_mw->recordRpcActivity(
            QString::fromUtf8(method),
            cJSON_IsBool(ok) && cJSON_IsTrue(ok),
            summarizeRpcActivityResult(out));
        if (response) cJSON_Delete(response);
    }

    cJSON_Delete(root);
    return out;
}

}  // namespace aura::gui
