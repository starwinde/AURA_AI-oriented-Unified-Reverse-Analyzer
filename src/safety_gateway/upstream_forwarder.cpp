#include "upstream_forwarder.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstring>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace aura::safety_gateway {
namespace {

constexpr size_t kMaxUpstreamHeaderBytes = 64 * 1024;
constexpr size_t kMaxUpstreamBodyBytes = 2 * 1024 * 1024;

#ifdef _WIN32
using SocketHandle = SOCKET;
constexpr SocketHandle kInvalidSocket = INVALID_SOCKET;
void closeSocket(SocketHandle socket) { closesocket(socket); }
int lastSocketError() { return WSAGetLastError(); }
bool wouldBlock(int error) {
    return error == WSAEWOULDBLOCK || error == WSAEINPROGRESS ||
           error == WSAEINVAL;
}
#else
using SocketHandle = int;
constexpr SocketHandle kInvalidSocket = -1;
void closeSocket(SocketHandle socket) { close(socket); }
int lastSocketError() { return errno; }
bool wouldBlock(int error) {
    return error == EINPROGRESS || error == EWOULDBLOCK || error == EAGAIN;
}
#endif

struct ParsedUrl {
    std::string host;
    uint16_t port = 80;
    std::string path = "/";
};

std::string lowerAscii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

UpstreamForwardResult errorResult(std::string code, std::string detail) {
    UpstreamForwardResult result;
    result.error_code = std::move(code);
    result.error_detail = std::move(detail);
    return result;
}

bool parseHttpUrl(const std::string& url,
                  ParsedUrl* out,
                  UpstreamForwardResult* error) {
    const std::string lower = lowerAscii(url);
    if (lower.rfind("https://", 0) == 0) {
        *error = errorResult("https_not_supported",
                             "Part 1 upstream forwarding supports http only");
        return false;
    }
    constexpr const char* kScheme = "http://";
    if (lower.rfind(kScheme, 0) != 0) {
        *error = errorResult("invalid_upstream_url",
                             "upstream_url must start with http://");
        return false;
    }
    std::string rest = url.substr(std::strlen(kScheme));
    const size_t slash = rest.find('/');
    std::string authority = slash == std::string::npos ? rest : rest.substr(0, slash);
    out->path = slash == std::string::npos ? "/" : rest.substr(slash);
    if (authority.empty()) {
        *error = errorResult("invalid_upstream_url", "upstream host is empty");
        return false;
    }

    const size_t colon = authority.rfind(':');
    if (colon != std::string::npos) {
        out->host = authority.substr(0, colon);
        const std::string port_text = authority.substr(colon + 1);
        if (out->host.empty() || port_text.empty()) {
            *error = errorResult("invalid_upstream_url",
                                 "upstream host or port is empty");
            return false;
        }
        try {
            const int parsed = std::stoi(port_text);
            if (parsed < 1 || parsed > 65535) {
                *error = errorResult("invalid_upstream_url",
                                     "upstream port must be 1..65535");
                return false;
            }
            out->port = static_cast<uint16_t>(parsed);
        } catch (const std::exception&) {
            *error = errorResult("invalid_upstream_url",
                                 "upstream port must be numeric");
            return false;
        }
    } else {
        out->host = authority;
    }
    return true;
}

bool setNonBlocking(SocketHandle socket, bool enabled) {
#ifdef _WIN32
    u_long mode = enabled ? 1 : 0;
    return ioctlsocket(socket, FIONBIO, &mode) == 0;
#else
    const int flags = fcntl(socket, F_GETFL, 0);
    if (flags < 0) return false;
    if (enabled) return fcntl(socket, F_SETFL, flags | O_NONBLOCK) == 0;
    return fcntl(socket, F_SETFL, flags & ~O_NONBLOCK) == 0;
#endif
}

timeval timeoutToTimeval(uint32_t timeout_ms) {
    timeval tv{};
    tv.tv_sec = static_cast<long>(timeout_ms / 1000);
    tv.tv_usec = static_cast<long>((timeout_ms % 1000) * 1000);
    return tv;
}

bool waitForWritable(SocketHandle socket, uint32_t timeout_ms) {
    fd_set write_set;
    FD_ZERO(&write_set);
    FD_SET(socket, &write_set);
    timeval tv = timeoutToTimeval(timeout_ms);
    const int rc = select(static_cast<int>(socket + 1), nullptr, &write_set,
                          nullptr, &tv);
    return rc > 0 && FD_ISSET(socket, &write_set);
}

bool waitForReadable(SocketHandle socket, uint32_t timeout_ms) {
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(socket, &read_set);
    timeval tv = timeoutToTimeval(timeout_ms);
    const int rc = select(static_cast<int>(socket + 1), &read_set, nullptr,
                          nullptr, &tv);
    return rc > 0 && FD_ISSET(socket, &read_set);
}

bool connectWithTimeout(SocketHandle socket,
                        const sockaddr* addr,
                        socklen_t addr_len,
                        uint32_t timeout_ms,
                        std::string* error_detail) {
    if (!setNonBlocking(socket, true)) {
        *error_detail = "could not enable non-blocking socket";
        return false;
    }
    if (connect(socket, addr, addr_len) == 0) {
        setNonBlocking(socket, false);
        return true;
    }
    const int err = lastSocketError();
    if (!wouldBlock(err)) {
        *error_detail = "connect failed: " + std::to_string(err);
        return false;
    }
    if (!waitForWritable(socket, timeout_ms)) {
        *error_detail = "upstream connect timed out";
        return false;
    }

    int socket_error = 0;
#ifdef _WIN32
    int len = sizeof(socket_error);
#else
    socklen_t len = sizeof(socket_error);
#endif
    if (getsockopt(socket, SOL_SOCKET, SO_ERROR,
                   reinterpret_cast<char*>(&socket_error), &len) != 0 ||
        socket_error != 0) {
        *error_detail = "connect failed: " + std::to_string(socket_error);
        return false;
    }
    setNonBlocking(socket, false);
    return true;
}

bool sendAll(SocketHandle socket, const std::string& data, uint32_t timeout_ms) {
    size_t sent = 0;
    while (sent < data.size()) {
        if (!waitForWritable(socket, timeout_ms)) return false;
        const int n = send(socket, data.data() + sent,
                           static_cast<int>(data.size() - sent), 0);
        if (n <= 0) return false;
        sent += static_cast<size_t>(n);
    }
    return true;
}

std::string headerValue(const std::string& headers, const std::string& name) {
    const std::string lower_headers = lowerAscii(headers);
    const std::string key = lowerAscii(name) + ":";
    const size_t pos = lower_headers.find(key);
    if (pos == std::string::npos) return {};
    size_t start = pos + key.size();
    while (start < headers.size() &&
           std::isspace(static_cast<unsigned char>(headers[start]))) {
        ++start;
    }
    size_t end = headers.find("\r\n", start);
    if (end == std::string::npos) end = headers.size();
    return headers.substr(start, end - start);
}

size_t parseContentLength(const std::string& headers) {
    const std::string value = headerValue(headers, "Content-Length");
    if (value.empty()) return 0;
    try {
        return static_cast<size_t>(std::stoull(value));
    } catch (const std::exception&) {
        return 0;
    }
}

bool parseStatusCode(const std::string& headers, int* status_code) {
    if (headers.rfind("HTTP/", 0) != 0) return false;
    const size_t first_space = headers.find(' ');
    if (first_space == std::string::npos) return false;
    try {
        *status_code = std::stoi(headers.substr(first_space + 1, 3));
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

UpstreamForwardResult readHttpResponse(SocketHandle socket,
                                       uint32_t timeout_ms) {
    std::string response;
    char buffer[4096];
    size_t header_end = std::string::npos;
    while (header_end == std::string::npos) {
        if (!waitForReadable(socket, timeout_ms)) {
            return errorResult("upstream_timeout", "timed out reading headers");
        }
        const int n = recv(socket, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            return errorResult("upstream_error", "connection closed before headers");
        }
        response.append(buffer, static_cast<size_t>(n));
        if (response.size() > kMaxUpstreamHeaderBytes) {
            return errorResult("upstream_response_too_large",
                               "upstream response headers exceeded limit");
        }
        header_end = response.find("\r\n\r\n");
    }

    const std::string headers = response.substr(0, header_end);
    const size_t body_start = header_end + 4;
    const size_t content_length = parseContentLength(headers);
    if (content_length > kMaxUpstreamBodyBytes) {
        return errorResult("upstream_response_too_large",
                           "upstream response body exceeded limit");
    }
    while (content_length > 0 && response.size() < body_start + content_length) {
        if (!waitForReadable(socket, timeout_ms)) {
            return errorResult("upstream_timeout", "timed out reading body");
        }
        const int n = recv(socket, buffer, sizeof(buffer), 0);
        if (n <= 0) break;
        response.append(buffer, static_cast<size_t>(n));
        if (response.size() > body_start + kMaxUpstreamBodyBytes) {
            return errorResult("upstream_response_too_large",
                               "upstream response body exceeded limit");
        }
    }

    UpstreamForwardResult result;
    if (!parseStatusCode(headers, &result.status_code)) {
        return errorResult("upstream_error", "invalid HTTP response status");
    }
    result.body = body_start <= response.size()
                      ? response.substr(body_start, content_length == 0
                                                        ? std::string::npos
                                                        : content_length)
                      : "";
    result.ok = result.status_code >= 200 && result.status_code < 300;
    if (!result.ok) {
        result.error_code = "upstream_http_error";
        result.error_detail = "upstream returned HTTP " +
                              std::to_string(result.status_code);
    }
    return result;
}

}  // namespace

UpstreamForwardResult forwardJsonToUpstream(
    const UpstreamForwardRequest& request) {
    ParsedUrl url;
    UpstreamForwardResult parse_error;
    if (!parseHttpUrl(request.upstream_url, &url, &parse_error)) {
        return parse_error;
    }
    if (request.timeout_ms == 0) {
        return errorResult("invalid_timeout", "timeout_ms must be positive");
    }

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return errorResult("winsock_startup_failed", "WSAStartup failed");
    }
#endif

    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* addresses = nullptr;
    const std::string port_text = std::to_string(url.port);
    if (getaddrinfo(url.host.c_str(), port_text.c_str(), &hints, &addresses) != 0) {
#ifdef _WIN32
        WSACleanup();
#endif
        return errorResult("upstream_error", "could not resolve upstream host");
    }

    SocketHandle connected = kInvalidSocket;
    std::string connect_error = "no address connected";
    for (addrinfo* ai = addresses; ai; ai = ai->ai_next) {
        SocketHandle candidate =
            socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (candidate == kInvalidSocket) continue;
        if (connectWithTimeout(candidate, ai->ai_addr,
                               static_cast<socklen_t>(ai->ai_addrlen),
                               request.timeout_ms, &connect_error)) {
            connected = candidate;
            break;
        }
        closeSocket(candidate);
    }
    freeaddrinfo(addresses);
    if (connected == kInvalidSocket) {
#ifdef _WIN32
        WSACleanup();
#endif
        if (connect_error.find("timed out") != std::string::npos) {
            return errorResult("upstream_timeout", connect_error);
        }
        return errorResult("upstream_error", connect_error);
    }

    std::ostringstream http;
    http << "POST " << url.path << " HTTP/1.1\r\n"
         << "Host: " << url.host << ":" << url.port << "\r\n"
         << "Content-Type: application/json\r\n"
         << "Accept: application/json\r\n"
         << "Content-Length: " << request.json_body.size() << "\r\n"
         << "Connection: close\r\n\r\n"
         << request.json_body;

    if (!sendAll(connected, http.str(), request.timeout_ms)) {
        closeSocket(connected);
#ifdef _WIN32
        WSACleanup();
#endif
        return errorResult("upstream_timeout", "timed out sending request");
    }

    UpstreamForwardResult result =
        readHttpResponse(connected, request.timeout_ms);
    closeSocket(connected);
#ifdef _WIN32
    WSACleanup();
#endif
    return result;
}

}  // namespace aura::safety_gateway
