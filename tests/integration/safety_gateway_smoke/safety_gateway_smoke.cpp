#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

namespace fs = std::filesystem;

#ifdef _WIN32
#define AURA_POPEN _popen
#define AURA_PCLOSE _pclose
#else
#define AURA_POPEN popen
#define AURA_PCLOSE pclose
#endif

std::string shellQuote(const std::string& value) {
#ifdef _WIN32
    return "\"" + value + "\"";
#else
    std::string out = "'";
    for (char ch : value) {
        if (ch == '\'') {
            out += "'\\''";
        } else {
            out += ch;
        }
    }
    out += "'";
    return out;
#endif
}

std::string popenCommand(const std::string& executable,
                         const std::vector<std::string>& args) {
#ifdef _WIN32
    std::string command = "\"\"" + executable + "\"";
    for (const auto& arg : args) {
        command += " " + shellQuote(arg);
    }
    command += "\"";
    return command;
#else
    std::string command = shellQuote(executable);
    for (const auto& arg : args) {
        command += " " + shellQuote(arg);
    }
    return command;
#endif
}

#ifdef _WIN32
std::string sendHttp(int port,
                     const std::string& method,
                     const std::string& target,
                     const std::string& body = {}) {
    WSADATA wsa;
    REQUIRE(WSAStartup(MAKEWORD(2, 2), &wsa) == 0);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    REQUIRE(sock != INVALID_SOCKET);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<unsigned short>(port));
    REQUIRE(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == 1);
    REQUIRE(connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0);

    std::ostringstream request;
    request << method << " " << target << " HTTP/1.1\r\n"
            << "Host: 127.0.0.1:" << port << "\r\n"
            << "Connection: close\r\n";
    if (!body.empty()) {
        request << "Content-Type: application/json\r\n"
                << "Content-Length: " << body.size() << "\r\n";
    }
    request << "\r\n" << body;
    const std::string wire = request.str();
    REQUIRE(send(sock, wire.data(), static_cast<int>(wire.size()), 0) > 0);

    std::string response;
    char buffer[4096];
    while (true) {
        const int n = recv(sock, buffer, sizeof(buffer), 0);
        if (n <= 0) break;
        response.append(buffer, static_cast<size_t>(n));
    }
    closesocket(sock);
    WSACleanup();
    return response;
}

std::string postMcp(int port, const std::string& body) {
    return sendHttp(port, "POST", "/mcp", body);
}

bool waitForPort(int port) {
    for (int i = 0; i < 40; ++i) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock != INVALID_SOCKET) {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(static_cast<unsigned short>(port));
            inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
            if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0) {
                closesocket(sock);
                WSACleanup();
                return true;
            }
            closesocket(sock);
        }
        WSACleanup();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return false;
}

int findAvailablePort() {
    WSADATA wsa;
    REQUIRE(WSAStartup(MAKEWORD(2, 2), &wsa) == 0);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    REQUIRE(sock != INVALID_SOCKET);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    REQUIRE(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == 1);
    REQUIRE(bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0);

    sockaddr_in bound{};
    int bound_len = sizeof(bound);
    REQUIRE(getsockname(sock, reinterpret_cast<sockaddr*>(&bound), &bound_len) == 0);
    const int port = ntohs(bound.sin_port);
    closesocket(sock);
    WSACleanup();
    return port;
}
#endif

TEST_CASE("aura-safety-gateway once mode masks protected value") {
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const fs::path request = fs::temp_directory_path() / "aura-safety-gateway-request.json";
    {
        std::ofstream out(request);
        out << R"({"request_id":"smoke-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}})";
    }

    const std::string command =
        popenCommand(bin, {"--once", request.string(), "--compact"});
    FILE* pipe = AURA_POPEN(command.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::ostringstream ss;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        ss << buffer;
    }
    const int rc = AURA_PCLOSE(pipe);
    CHECK(rc == 0);

    const std::string output = ss.str();
    CHECK(output.find("\"decision\":\"pass\"") != std::string::npos);
    CHECK(output.find("\"masked_count\":1") != std::string::npos);
    CHECK(output.find("alice.smith@example.com") == std::string::npos);
    CHECK(output.find("*") != std::string::npos);
}

TEST_CASE("aura-safety-gateway once mode exits nonzero for blocked hard secret") {
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const fs::path request = fs::temp_directory_path() / "aura-safety-gateway-secret-request.json";
    const fs::path cache = fs::temp_directory_path() / "aura-safety-gateway-secret-cache.sqlite";
    std::error_code ignored;
    fs::remove(cache, ignored);
    {
        std::ofstream out(request);
        out << R"({"request_id":"smoke-secret-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"api_key = \"abc1234567890XYZSECRET\""}]}})";
    }

    const std::string command =
        popenCommand(bin, {"--once", request.string(), "--cache", cache.string(), "--compact"});
    FILE* pipe = AURA_POPEN(command.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::ostringstream ss;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        ss << buffer;
    }
    const int rc = AURA_PCLOSE(pipe);
    CHECK(rc != 0);

    const std::string output = ss.str();
    CHECK(output.find("\"decision\":\"block\"") != std::string::npos);
    CHECK(output.find("\"blocked_count\":1") != std::string::npos);
    CHECK(output.find("abc1234567890XYZSECRET") == std::string::npos);
}

TEST_CASE("aura-safety-gateway rejects remote bind without explicit opt-in") {
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const std::string command =
        popenCommand(bin, {"--serve", "--listen-host", "0.0.0.0", "--listen-port", "18766", "--compact"});
    FILE* pipe = AURA_POPEN(command.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::ostringstream ss;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        ss << buffer;
    }
    const int rc = AURA_PCLOSE(pipe);
    CHECK(rc != 0);

    const std::string output = ss.str();
    CHECK(output.find("\"decision\":\"block\"") != std::string::npos);
    CHECK(output.find("\"code\":\"remote_bind_requires_opt_in\"") != std::string::npos);
}

TEST_CASE("aura-safety-gateway serves from persisted listen port when flag is absent") {
#ifndef _WIN32
    MESSAGE("HTTP process smoke currently runs on Windows CI only");
#else
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const int port = findAvailablePort();
    const fs::path root =
        fs::temp_directory_path() /
        ("aura-safety-gateway-config-port-" + std::to_string(GetCurrentProcessId()));
    const fs::path config_dir = root / ".aura";
    std::error_code ignored;
    fs::remove_all(root, ignored);
    REQUIRE(fs::create_directories(config_dir));
    {
        std::ofstream out(config_dir / "safety-gateway-config.json");
        out << R"({"remote":{"listen_host":"127.0.0.1","port":)"
            << port << R"(}})";
    }

    std::string command = std::string("\"") + bin + "\" --serve";
    std::vector<char> mutable_command(command.begin(), command.end());
    mutable_command.push_back('\0');
    const std::string cwd = root.string();

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    REQUIRE(CreateProcessA(nullptr,
                           mutable_command.data(),
                           nullptr,
                           nullptr,
                           FALSE,
                           CREATE_NO_WINDOW,
                           nullptr,
                           cwd.c_str(),
                           &si,
                           &pi));
    try {
        REQUIRE(waitForPort(port));
        const std::string ui = sendHttp(port, "GET", "/ui");
        CHECK(ui.find("HTTP/1.1 200 OK") != std::string::npos);
        CHECK(ui.find("Safety Gateway") != std::string::npos);
    } catch (...) {
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        fs::remove_all(root, ignored);
        throw;
    }
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    fs::remove_all(root, ignored);
#endif
}

TEST_CASE("aura-safety-gateway fails loudly on malformed persisted config") {
#ifndef _WIN32
    MESSAGE("HTTP process smoke currently runs on Windows CI only");
#else
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const fs::path root =
        fs::temp_directory_path() /
        ("aura-safety-gateway-bad-config-" + std::to_string(GetCurrentProcessId()));
    const fs::path config_dir = root / ".aura";
    std::error_code ignored;
    fs::remove_all(root, ignored);
    REQUIRE(fs::create_directories(config_dir));
    {
        std::ofstream out(config_dir / "safety-gateway-config.json");
        out << R"({"remote":{"listen_host":"127.0.0.1","port":"bad"}})";
    }

    std::string command = std::string("\"") + bin + "\" --serve";
    std::vector<char> mutable_command(command.begin(), command.end());
    mutable_command.push_back('\0');
    const std::string cwd = root.string();

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    REQUIRE(CreateProcessA(nullptr,
                           mutable_command.data(),
                           nullptr,
                           nullptr,
                           FALSE,
                           CREATE_NO_WINDOW,
                           nullptr,
                           cwd.c_str(),
                           &si,
                           &pi));

    REQUIRE(WaitForSingleObject(pi.hProcess, 5000) == WAIT_OBJECT_0);
    DWORD exit_code = 0;
    REQUIRE(GetExitCodeProcess(pi.hProcess, &exit_code));
    CHECK(exit_code != 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    fs::remove_all(root, ignored);
#endif
}

TEST_CASE("aura-safety-gateway serves MCP HTTP requests") {
#ifndef _WIN32
    MESSAGE("HTTP process smoke currently runs on Windows CI only");
#else
    const char* bin = std::getenv("AURA_SAFETY_GATEWAY_BIN");
    REQUIRE(bin != nullptr);

    const int port = findAvailablePort();
    std::string command =
        std::string("\"") + bin + "\" --serve --listen-host 127.0.0.1 --listen-port " +
        std::to_string(port);
    std::vector<char> mutable_command(command.begin(), command.end());
    mutable_command.push_back('\0');

    STARTUPINFOA si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    REQUIRE(CreateProcessA(nullptr,
                           mutable_command.data(),
                           nullptr,
                           nullptr,
                           FALSE,
                           CREATE_NO_WINDOW,
                           nullptr,
                           nullptr,
                           &si,
                           &pi));
    try {
        REQUIRE(waitForPort(port));

        const std::string init = postMcp(
            port,
            R"({"jsonrpc":"2.0","id":17,"method":"initialize","params":{"protocolVersion":"2025-11-25","capabilities":{},"clientInfo":{"name":"aura-smoke","version":"0.1"}}})");
        CHECK(init.find("\"id\":17") != std::string::npos);
        CHECK(init.find("\"name\":\"aura-safety-gateway\"") != std::string::npos);

        const std::string call = postMcp(
            port,
            R"({"jsonrpc":"2.0","id":19,"method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"mcp-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}}}})");
        CHECK(call.find("\"id\":19") != std::string::npos);
        CHECK(call.find("alice.smith@example.com") == std::string::npos);
        CHECK(call.find("\\\"masked_count\\\":1") != std::string::npos);

        const std::string ui = sendHttp(port, "GET", "/ui");
        CHECK(ui.find("HTTP/1.1 200 OK") != std::string::npos);
        CHECK(ui.find("Safety Gateway") != std::string::npos);
        CHECK(ui.find("Live Gateway Monitor") != std::string::npos);
        CHECK(ui.find("1. Incoming request") != std::string::npos);
        CHECK(ui.find("6. Audit result") != std::string::npos);

        const std::string demo = sendHttp(
            port,
            "POST",
            "/api/demo/inject",
            R"({"fixture":"pii"})");
        CHECK(demo.find("HTTP/1.1 200 OK") != std::string::npos);
        CHECK(demo.find("\"ok\":true") != std::string::npos);
        CHECK(demo.find("\"request_id\":\"demo-pii-") != std::string::npos);

        const std::string stats = sendHttp(port, "GET", "/api/stats");
        CHECK(stats.find("\"requests_today\":") != std::string::npos);
        CHECK(stats.find("\"masked\":") != std::string::npos);

        const std::string requests = sendHttp(port, "GET", "/api/requests");
        CHECK(requests.find("\"requests\"") != std::string::npos);
        CHECK(requests.find("alice.smith@example.com") == std::string::npos);
    } catch (...) {
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        throw;
    }
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
#endif
}
