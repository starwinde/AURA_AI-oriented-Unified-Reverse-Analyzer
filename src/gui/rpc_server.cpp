// src/gui/rpc_server.cpp — implementation. ADR-0038.

#include "rpc_server.h"

#include "main_window.h"

#include <QHostAddress>
#include <QRandomGenerator>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QtCore/QCoreApplication>

#include "cJSON.h"

#include <cstdio>
#include <cstdlib>

namespace aura::gui {

namespace {

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
            m_mw->currentDecompileText().toUtf8().constData());
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
            m_mw->currentDecompileText().toUtf8().constData());
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
    } else if (std::strcmp(method, "quit") == 0) {
        out = resultJson(true, nullptr, nullptr);
        QCoreApplication::quit();
    } else {
        out = resultJson(false, nullptr, "unknown method");
    }

    cJSON_Delete(root);
    return out;
}

}  // namespace aura::gui
