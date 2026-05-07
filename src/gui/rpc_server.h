// src/gui/rpc_server.h — GUI RPC server (Phase 11.3.3, ADR-0038).
//
// TCP localhost JSON-line server. Drives MainWindow via its public API.
// Default OFF (opt-in via --rpc-port or AURA_GUI_RPC_PORT env).
//
// Protocol:
//   request  : {"method":"<name>","params":{...},"token":"<hex>"}\n
//   response : {"ok":bool,"result":...,"error":"..."}\n
//
// Security:
//   - 127.0.0.1 binding only (never 0.0.0.0).
//   - Optional token via AURA_GUI_RPC_TOKEN env. If unset, a random
//     32-byte hex is generated at start and printed to stdout.
//   - Single client at a time (additional connections rejected).

#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>

class QTcpServer;
class QTcpSocket;

namespace aura::gui {

class MainWindow;

class RpcServer : public QObject {
    Q_OBJECT
public:
    explicit RpcServer(MainWindow* mw, QObject* parent = nullptr);
    ~RpcServer() override;

    // Start listening on 127.0.0.1:<port>. Returns true on success.
    bool start(quint16 port);

    quint16 port()  const { return m_port; }
    QString token() const { return m_token; }

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QString dispatch(const QByteArray& jsonLine);

    MainWindow*  m_mw     = nullptr;
    QTcpServer*  m_server = nullptr;
    QTcpSocket*  m_client = nullptr;
    QByteArray   m_buffer;
    quint16      m_port   = 0;
    QString      m_token;
};

}  // namespace aura::gui
