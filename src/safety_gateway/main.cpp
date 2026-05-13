#include "control_api.h"
#include "gateway_cache.h"
#include "gateway_config.h"
#include "gateway_policy.h"
#include "gateway_request.h"
#include "mcp_http.h"
#include "remote_access.h"
#include "request_log.h"
#include "session_reveal_store.h"
#include "ui_assets.h"
#include "upstream_forwarder.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace {

constexpr size_t kMaxHttpBodyBytes = 1024 * 1024;

std::string readAll(std::istream& in) {
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void usage() {
    std::cerr
        << "usage:\n"
        << "  aura-safety-gateway --serve [--ui] [--listen-host 127.0.0.1] [--listen-port 8765] [--upstream-url http://127.0.0.1:8780/mcp] [--cache path.sqlite]\n"
        << "  aura-safety-gateway --once <request.json> [--cache path.sqlite] [--compact]\n"
        << "  aura-safety-gateway --inspect-policy [--compact]\n"
        << "  aura-safety-gateway --version\n";
}

int emitError(const std::string& code, const std::string& message) {
    std::cout << "{\"decision\":\"block\",\"error\":{\"code\":\""
              << code << "\",\"message\":\"" << message << "\"}}\n";
    return 2;
}

bool parsePort(const char* value, int* out) {
    if (!value || !out) return false;
    try {
        const int parsed = std::stoi(value);
        if (parsed < 1 || parsed > 65535) return false;
        *out = parsed;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool isLoopbackHost(const std::string& host) {
    return host == "127.0.0.1" || host == "localhost" || host == "::1";
}

std::string normalizedBindHost(const std::string& host) {
    if (host == "localhost") return "127.0.0.1";
    return host;
}

std::string lowerAscii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

std::string httpResponse(const std::string& status,
                         const std::string& body,
                         const std::string& content_type = "application/json") {
    std::ostringstream out;
    out << "HTTP/1.1 " << status << "\r\n"
        << "Content-Type: " << content_type << "\r\n"
        << "Content-Length: " << body.size() << "\r\n"
        << "Connection: close\r\n\r\n"
        << body;
    return out.str();
}

#ifdef _WIN32
using SocketHandle = SOCKET;
constexpr SocketHandle kInvalidSocket = INVALID_SOCKET;
void closeSocket(SocketHandle socket) { closesocket(socket); }
int socketError() { return WSAGetLastError(); }
#else
using SocketHandle = int;
constexpr SocketHandle kInvalidSocket = -1;
void closeSocket(SocketHandle socket) { close(socket); }
int socketError() { return errno; }
#endif

void setSocketTimeout(SocketHandle socket, int timeout_ms) {
#ifdef _WIN32
    DWORD timeout = static_cast<DWORD>(timeout_ms);
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
#else
    timeval timeout{};
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
#endif
}

std::string isoNow() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buffer;
}

bool sendAll(SocketHandle socket, const std::string& data) {
    size_t sent = 0;
    while (sent < data.size()) {
        const int n = send(socket, data.data() + sent, static_cast<int>(data.size() - sent), 0);
        if (n <= 0) return false;
        sent += static_cast<size_t>(n);
    }
    return true;
}

size_t contentLengthFromHeaders(const std::string& headers) {
    const std::string lower = lowerAscii(headers);
    const std::string key = "content-length:";
    const size_t pos = lower.find(key);
    if (pos == std::string::npos) return 0;
    size_t start = pos + key.size();
    while (start < headers.size() && std::isspace(static_cast<unsigned char>(headers[start]))) {
        ++start;
    }
    size_t end = start;
    size_t value = 0;
    while (end < headers.size() && std::isdigit(static_cast<unsigned char>(headers[end]))) {
        const unsigned digit = static_cast<unsigned>(headers[end] - '0');
        if (value > (kMaxHttpBodyBytes - digit) / 10) {
            return kMaxHttpBodyBytes + 1;
        }
        value = value * 10 + digit;
        ++end;
    }
    if (end == start) return 0;
    return value;
}

bool readHttpRequest(SocketHandle client, std::string* request, bool* oversized) {
    request->clear();
    if (oversized) *oversized = false;
    char buffer[4096];
    size_t header_end = std::string::npos;
    size_t content_length = 0;
    while (true) {
        const int n = recv(client, buffer, sizeof(buffer), 0);
        if (n <= 0) return false;
        request->append(buffer, static_cast<size_t>(n));
        header_end = request->find("\r\n\r\n");
        if (header_end != std::string::npos) {
            content_length = contentLengthFromHeaders(request->substr(0, header_end));
            if (content_length > kMaxHttpBodyBytes) {
                if (oversized) *oversized = true;
                return false;
            }
            break;
        }
        if (request->size() > kMaxHttpBodyBytes) {
            if (oversized) *oversized = true;
            return false;
        }
    }
    const size_t body_start = header_end + 4;
    while (request->size() < body_start + content_length) {
        const int n = recv(client, buffer, sizeof(buffer), 0);
        if (n <= 0) return false;
        request->append(buffer, static_cast<size_t>(n));
        if (request->size() > body_start + kMaxHttpBodyBytes) {
            if (oversized) *oversized = true;
            return false;
        }
    }
    return true;
}

std::string requestBody(const std::string& request) {
    const size_t header_end = request.find("\r\n\r\n");
    if (header_end == std::string::npos) return {};
    const size_t body_start = header_end + 4;
    const size_t content_length = contentLengthFromHeaders(request.substr(0, header_end));
    if (body_start >= request.size()) return {};
    return request.substr(body_start, std::min(content_length, request.size() - body_start));
}

std::string requestLineToken(const std::string& request, int index) {
    const size_t line_end = request.find("\r\n");
    const std::string line = line_end == std::string::npos ? request : request.substr(0, line_end);
    std::istringstream in(line);
    std::string token;
    for (int i = 0; i <= index; ++i) {
        if (!(in >> token)) return {};
    }
    return token;
}

std::string requestMethod(const std::string& request) {
    return requestLineToken(request, 0);
}

std::string requestTarget(const std::string& request) {
    return requestLineToken(request, 1);
}

std::string requestPathOnly(const std::string& target) {
    const size_t q = target.find('?');
    return q == std::string::npos ? target : target.substr(0, q);
}

std::unordered_map<std::string, std::string> requestHeaders(const std::string& request) {
    std::unordered_map<std::string, std::string> headers;
    const size_t header_end = request.find("\r\n\r\n");
    if (header_end == std::string::npos) return headers;
    size_t line_start = request.find("\r\n");
    if (line_start == std::string::npos || line_start + 2 >= header_end) return headers;
    line_start += 2;
    while (line_start < header_end) {
        const size_t line_end = request.find("\r\n", line_start);
        if (line_end == std::string::npos || line_end > header_end) break;
        const std::string line = request.substr(line_start, line_end - line_start);
        const size_t colon = line.find(':');
        if (colon != std::string::npos) {
            size_t value_start = colon + 1;
            while (value_start < line.size() &&
                   std::isspace(static_cast<unsigned char>(line[value_start]))) {
                ++value_start;
            }
            headers.emplace(line.substr(0, colon), line.substr(value_start));
        }
        line_start = line_end + 2;
    }
    return headers;
}

bool isMcpPost(const std::string& method, const std::string& target) {
    return method == "POST" && requestPathOnly(target) == "/mcp";
}

std::string clientIpFromSockaddr(const sockaddr_in& addr) {
    char buffer[INET_ADDRSTRLEN] = {};
    if (inet_ntop(AF_INET, &addr.sin_addr, buffer, sizeof(buffer))) {
        return buffer;
    }
    return "unknown";
}

void appendBlockedRemoteLog(aura::safety_gateway::RequestLog* log,
                            const std::string& client_ip,
                            const std::string& method,
                            const std::string& target,
                            const aura::safety_gateway::RemoteAccessDecision& decision) {
    if (!log) return;
    aura::safety_gateway::RequestLogEntry entry;
    entry.request_id = "blocked-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    entry.timestamp_iso8601 = isoNow();
    entry.client_name = "remote-client";
    entry.client_ip = client_ip;
    entry.method = method;
    entry.tool_name = target;
    entry.decision = "blocked";
    entry.route = "blocked";
    entry.remote_auth_result = decision.result_code;
    entry.upstream_status = "not_forwarded";
    entry.protected_payload_json = "{}";
    aura::safety_gateway::GatewayAuditEvent event;
    event.event_id = "evt_remote_block";
    event.timestamp_iso8601 = entry.timestamp_iso8601;
    event.event_type = decision.audit_event_type.empty() ? "remote_blocked" : decision.audit_event_type;
    event.detail = decision.audit_detail.empty() ? decision.detail : decision.audit_detail;
    entry.audit_events.push_back(std::move(event));
    log->append(std::move(entry));
}

int runHttpServer(aura::safety_gateway::GatewayConfig config,
                  bool allow_remote_bind,
                  const std::string& config_path) {
    if (!isLoopbackHost(config.remote.listen_host) && !allow_remote_bind) {
        return emitError("remote_bind_requires_opt_in",
                         "non-loopback listen host requires --allow-remote-bind");
    }

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return emitError("winsock_startup_failed", "WSAStartup failed");
    }
#endif

    SocketHandle server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == kInvalidSocket) {
#ifdef _WIN32
        WSACleanup();
#endif
        return emitError("socket_failed", "could not create listening socket");
    }

    int reuse = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuse), sizeof(reuse));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<unsigned short>(config.remote.port));
    const std::string bind_host = normalizedBindHost(config.remote.listen_host);
    if (inet_pton(AF_INET, bind_host.c_str(), &addr.sin_addr) != 1) {
        closeSocket(server);
#ifdef _WIN32
        WSACleanup();
#endif
        return emitError("invalid_listen_host", "listen host must be an IPv4 address or localhost");
    }

    if (bind(server, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        const int err = socketError();
        closeSocket(server);
#ifdef _WIN32
        WSACleanup();
#endif
        return emitError("bind_failed", "could not bind listen socket: " + std::to_string(err));
    }

    if (listen(server, 16) != 0) {
        const int err = socketError();
        closeSocket(server);
#ifdef _WIN32
        WSACleanup();
#endif
        return emitError("listen_failed", "could not listen on socket: " + std::to_string(err));
    }

    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = config.cache_db_path;
    aura::safety_gateway::RequestLog request_log;
    aura::safety_gateway::SessionRevealStore reveal_store;
    aura::safety_gateway::GatewayControlState control_state;
    control_state.config = &config;
    control_state.mcp_options = &options;
    control_state.request_log = &request_log;
    control_state.reveal_store = &reveal_store;
    control_state.config_path = config_path;
    control_state.listen_address = "http://" + config.remote.listen_host + ":" +
                                   std::to_string(config.remote.port);
    control_state.allow_remote_bind = allow_remote_bind;

    std::cerr << "aura-safety-gateway listening on " << control_state.listen_address
              << "/mcp and " << control_state.listen_address << "/ui\n";

    while (true) {
        sockaddr_in client_addr{};
#ifdef _WIN32
        int client_addr_len = sizeof(client_addr);
#else
        socklen_t client_addr_len = sizeof(client_addr);
#endif
        SocketHandle client = accept(server,
                                     reinterpret_cast<sockaddr*>(&client_addr),
                                     &client_addr_len);
        if (client == kInvalidSocket) {
            continue;
        }
        setSocketTimeout(client, 5000);
        const std::string client_ip = clientIpFromSockaddr(client_addr);

        std::string request;
        bool oversized = false;
        if (!readHttpRequest(client, &request, &oversized)) {
            const std::string body = oversized
                ? R"({"decision":"blocked","error":{"code":"oversized_request","message":"HTTP request body is too large"}})"
                : R"({"error":{"code":"bad_request","message":"could not read HTTP request"}})";
            sendAll(client, httpResponse(oversized ? "413 Payload Too Large" : "400 Bad Request", body));
            closeSocket(client);
            continue;
        }

        const std::string method = requestMethod(request);
        const std::string target = requestTarget(request);
        const std::string path = requestPathOnly(target);

        if (method == "GET" && path == "/ui") {
            const std::string body = aura::safety_gateway::safetyGatewayUiHtml();
            sendAll(client, httpResponse("200 OK", body, "text/html; charset=utf-8"));
            closeSocket(client);
            continue;
        }

        aura::safety_gateway::GatewayHttpRequestView api_request;
        api_request.method = method;
        api_request.target = target;
        api_request.body = requestBody(request);
        api_request.client_ip = client_ip;
        api_request.headers = requestHeaders(request);
        aura::safety_gateway::GatewayHttpResponse api_response;
        if (path.rfind("/api/", 0) == 0) {
            aura::safety_gateway::RemoteAccessRequest api_remote_request;
            api_remote_request.client_ip = client_ip;
            api_remote_request.target = target;
            api_remote_request.headers = api_request.headers;
            const auto api_remote_decision =
                aura::safety_gateway::evaluateRemoteAccess(config.remote, api_remote_request);
            if (!api_remote_decision.allowed) {
                appendBlockedRemoteLog(&request_log, client_ip, method, target, api_remote_decision);
                const std::string body = std::string(R"({"decision":"blocked","error":{"code":")") +
                                         api_remote_decision.result_code + R"(","message":")" +
                                         api_remote_decision.detail + R"("}})";
                sendAll(client, httpResponse("403 Forbidden", body));
                closeSocket(client);
                continue;
            }
            if (aura::safety_gateway::handleControlApiRequest(api_request,
                                                          &control_state,
                                                          &api_response)) {
                sendAll(client, httpResponse(api_response.status,
                                             api_response.body,
                                             api_response.content_type));
                closeSocket(client);
                continue;
            }
        }

        if (!isMcpPost(method, target)) {
            const std::string body = R"({"error":{"code":"not_found","message":"use POST /mcp or GET /ui"}})";
            sendAll(client, httpResponse("404 Not Found", body));
            closeSocket(client);
            continue;
        }

        aura::safety_gateway::RemoteAccessRequest remote_request;
        remote_request.client_ip = client_ip;
        remote_request.target = target;
        remote_request.headers = api_request.headers;
        const auto remote_decision =
            aura::safety_gateway::evaluateRemoteAccess(config.remote, remote_request);
        if (!remote_decision.allowed) {
            appendBlockedRemoteLog(&request_log, client_ip, method, target, remote_decision);
            const std::string body = std::string(R"({"decision":"blocked","error":{"code":")") +
                                     remote_decision.result_code + R"(","message":")" +
                                     remote_decision.detail + R"("}})";
            sendAll(client, httpResponse("403 Forbidden", body));
            closeSocket(client);
            continue;
        }

        auto detailed =
            aura::safety_gateway::handleMcpJsonRpcDetailed(requestBody(request), options);
        aura::safety_gateway::UpstreamForwardResult upstream_result;
        aura::safety_gateway::UpstreamForwardResult* upstream_ptr = nullptr;
        if (config.forward.enabled && !detailed.blocked &&
            !detailed.protected_forward_body.empty()) {
            aura::safety_gateway::UpstreamForwardRequest forward_request;
            forward_request.upstream_url = config.forward.upstream_url;
            forward_request.json_body = detailed.protected_forward_body;
            forward_request.timeout_ms = config.forward.timeout_ms;
            upstream_result = aura::safety_gateway::forwardJsonToUpstream(forward_request);
            upstream_ptr = &upstream_result;
        }
        aura::safety_gateway::recordMcpGatewayResult(&control_state,
                                                     &detailed,
                                                     client_ip,
                                                     remote_decision,
                                                     upstream_ptr);

        std::string body = detailed.response_json;
        if (upstream_ptr && upstream_ptr->ok && !upstream_ptr->body.empty()) {
            body = upstream_ptr->body;
        }
        sendAll(client, httpResponse("200 OK", body));
        closeSocket(client);
    }
}

}  // namespace

int main(int argc, char** argv) {
    bool compact = false;
    std::string mode;
    std::string path;
    std::string cache_path;
    std::string listen_host = "127.0.0.1";
    int listen_port = 8765;
    bool listen_host_supplied = false;
    bool listen_port_supplied = false;
    std::string upstream_url;
    bool allow_remote_bind = false;
    bool ui_enabled = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i] ? argv[i] : "";
        if (arg == "--compact") {
            compact = true;
        } else if (arg == "--cache" && i + 1 < argc) {
            cache_path = argv[++i];
        } else if (arg == "--listen-host" && i + 1 < argc) {
            listen_host = argv[++i];
            listen_host_supplied = true;
        } else if (arg == "--listen-port" && i + 1 < argc) {
            if (!parsePort(argv[++i], &listen_port)) {
                return emitError("invalid_port", "listen port must be between 1 and 65535");
            }
            listen_port_supplied = true;
        } else if (arg == "--upstream-url" && i + 1 < argc) {
            upstream_url = argv[++i];
        } else if (arg == "--allow-remote-bind") {
            allow_remote_bind = true;
        } else if (arg == "--ui") {
            ui_enabled = true;
        } else if (arg == "--version") {
            std::cout << "aura-safety-gateway 0.1.0\n";
            return 0;
        } else if (arg == "--inspect-policy") {
            mode = "inspect-policy";
        } else if (arg == "--serve") {
            mode = "serve";
        } else if (arg == "--stdio") {
            mode = "stdio";
        } else if (arg == "--once" && i + 1 < argc) {
            mode = "once";
            path = argv[++i];
        } else {
            usage();
            return 2;
        }
    }

    if (mode == "inspect-policy") {
        std::cout << "{\"schema_version\":\"aura-safety-gateway/1.0\","
                  << "\"mode\":\"deterministic-fallback\","
                  << "\"masking\":\"star-65-percent\","
                  << "\"raw_original_export\":\"blocked\"}\n";
        return 0;
    }

    if (mode == "serve") {
        (void)ui_enabled;
        aura::safety_gateway::GatewayConfig config =
            aura::safety_gateway::defaultGatewayConfig();
        const std::string config_path = aura::safety_gateway::defaultGatewayConfigPath();
        aura::safety_gateway::GatewayConfig loaded;
        const auto load_result =
            aura::safety_gateway::loadGatewayConfig(config_path, &loaded);
        if (load_result.ok) {
            config = loaded;
        } else if (std::filesystem::exists(config_path)) {
            return emitError(load_result.error_code, load_result.error_detail);
        }
        if (listen_host_supplied) {
            config.remote.listen_host = listen_host;
        }
        if (listen_port_supplied) {
            config.remote.port = static_cast<uint16_t>(listen_port);
        }
        if (!cache_path.empty()) {
            config.cache_db_path = cache_path;
        }
        if (config.cache_db_path.empty()) {
            config.cache_db_path = aura::safety_gateway::defaultGatewayCachePath();
        }
        if (!upstream_url.empty()) {
            config.mode = "forward";
            config.forward.enabled = true;
            config.forward.upstream_url = upstream_url;
        }
        aura::safety_gateway::GatewayConfigValidationOptions validation_options;
        validation_options.allow_remote_bind = allow_remote_bind;
        const auto validation =
            aura::safety_gateway::validateGatewayConfig(config, validation_options);
        if (!validation.ok) {
            return emitError(validation.error_code, validation.error_detail);
        }
        return runHttpServer(config, allow_remote_bind, config_path);
    }

    if (mode == "stdio") {
        aura::safety_gateway::McpHttpOptions options;
        options.policy.cache_path = cache_path;
        std::cout << aura::safety_gateway::handleMcpJsonRpc(readAll(std::cin), options) << "\n";
        return 0;
    }

    if (mode != "once" || path.empty()) {
        usage();
        return 2;
    }

    std::ifstream file(path, std::ios::binary);
    if (!file) return emitError("open_failed", "could not open request file");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    if (!aura::safety_gateway::parseGatewayRequest(readAll(file), &request, &error)) {
        return emitError("invalid_request", error);
    }

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path;
    const auto response = aura::safety_gateway::evaluateGatewayRequest(request, options);
    std::cout << aura::safety_gateway::gatewayResponseToJson(response, compact) << "\n";
    return response.decision == "block" ? 3 : 0;
}
