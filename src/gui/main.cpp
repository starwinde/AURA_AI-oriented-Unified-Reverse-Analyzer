// src/gui/main.cpp — AURA GUI entry point (Phase 11.3 ~ 11.3.3).
//
// Bootstraps QApplication, MainWindow, and (optionally) the RPC server
// when --rpc-port is specified or AURA_GUI_RPC_PORT env is set.

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include <cstdlib>

#include "main_window.h"
#include "rpc_server.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("AURA"));
    app.setOrganizationName(QStringLiteral("AURA"));

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QStringLiteral("AURA — RE-tool orchestrator + LLM context provider"));
    QCommandLineOption rpcOpt(
        QStringList() << QStringLiteral("rpc-port"),
        QStringLiteral("Enable RPC server on 127.0.0.1:<port>. "
                       "Token printed to stdout (or set via "
                       "AURA_GUI_RPC_TOKEN env)."),
        QStringLiteral("port"));
    parser.addOption(rpcOpt);
    parser.addHelpOption();
    parser.process(app);

    aura::gui::MainWindow window;
    window.show();

    quint16 rpcPort = 0;
    if (parser.isSet(rpcOpt)) {
        rpcPort = static_cast<quint16>(parser.value(rpcOpt).toUInt());
    } else if (const char* env = std::getenv("AURA_GUI_RPC_PORT")) {
        rpcPort = static_cast<quint16>(std::atoi(env));
    }

    aura::gui::RpcServer* rpc = nullptr;
    if (rpcPort > 0) {
        rpc = new aura::gui::RpcServer(&window, &app);
        if (!rpc->start(rpcPort)) {
            // listen failed already reported on stderr; exit non-zero.
            return 2;
        }
    }

    return app.exec();
}
