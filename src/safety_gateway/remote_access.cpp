#include "remote_access.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace aura::safety_gateway {
namespace {

bool isLoopbackIp(const std::string& ip) {
    return ip == "127.0.0.1" || ip == "::1" || ip == "localhost";
}

std::string lowerAscii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

std::string headerValue(const RemoteAccessRequest& request,
                        const std::string& name) {
    const std::string wanted = lowerAscii(name);
    for (const auto& header : request.headers) {
        if (lowerAscii(header.first) == wanted) {
            return header.second;
        }
    }
    return {};
}

bool hasAllowedIp(const GatewayRemoteConfig& config, const std::string& ip) {
    return std::find(config.ip_allowlist.begin(), config.ip_allowlist.end(), ip) !=
           config.ip_allowlist.end();
}

std::string bearerToken(const std::string& authorization) {
    constexpr const char* kPrefix = "bearer ";
    if (authorization.size() <= 7) return {};
    if (lowerAscii(authorization.substr(0, 7)) != kPrefix) return {};
    return authorization.substr(7);
}

int hexValue(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    return -1;
}

std::string percentDecode(std::string value) {
    std::string out;
    for (size_t i = 0; i < value.size(); ++i) {
        if (value[i] == '+' ) {
            out.push_back(' ');
        } else if (value[i] == '%' && i + 2 < value.size()) {
            const int hi = hexValue(value[i + 1]);
            const int lo = hexValue(value[i + 2]);
            if (hi >= 0 && lo >= 0) {
                out.push_back(static_cast<char>((hi << 4) | lo));
                i += 2;
            } else {
                out.push_back(value[i]);
            }
        } else {
            out.push_back(value[i]);
        }
    }
    return out;
}

std::string queryValue(const std::string& target, const std::string& key) {
    const size_t q = target.find('?');
    if (q == std::string::npos) return {};
    std::string query = target.substr(q + 1);
    size_t start = 0;
    while (start <= query.size()) {
        size_t end = query.find('&', start);
        if (end == std::string::npos) end = query.size();
        const std::string part = query.substr(start, end - start);
        const size_t eq = part.find('=');
        const std::string name = percentDecode(part.substr(0, eq));
        if (name == key) {
            return percentDecode(eq == std::string::npos ? "" : part.substr(eq + 1));
        }
        if (end == query.size()) break;
        start = end + 1;
    }
    return {};
}

RemoteAccessDecision decision(bool allowed,
                              std::string code,
                              std::string detail,
                              std::string audit_type,
                              std::string audit_detail) {
    RemoteAccessDecision out;
    out.allowed = allowed;
    out.result_code = std::move(code);
    out.detail = std::move(detail);
    out.audit_event_type = std::move(audit_type);
    out.audit_detail = std::move(audit_detail);
    return out;
}

}  // namespace

RemoteAccessDecision evaluateRemoteAccess(
    const GatewayRemoteConfig& config,
    const RemoteAccessRequest& request) {
    const std::string client_ip =
        request.client_ip.empty() ? "unknown" : request.client_ip;

    if (!config.enabled) {
        if (isLoopbackIp(client_ip)) {
            return decision(true, "local_loopback_allowed",
                            "remote mode disabled; loopback client allowed",
                            "remote_allowed",
                            "loopback client allowed while remote mode is disabled");
        }
        return decision(false, "remote_disabled",
                        "remote mode is disabled for non-loopback clients",
                        "remote_blocked_ip",
                        "non-loopback client blocked while remote mode is disabled");
    }

    if (!hasAllowedIp(config, client_ip)) {
        return decision(false, "remote_blocked_ip",
                        "client IP is not in remote.ip_allowlist",
                        "remote_blocked_ip",
                        "blocked client_ip=" + client_ip);
    }

    if (!config.require_access_token) {
        return decision(true, "remote_allowed",
                        "client IP allowed and token not required",
                        "remote_allowed",
                        "allowed client_ip=" + client_ip);
    }

    std::string token = bearerToken(headerValue(request, "Authorization"));
    std::string transport = "bearer";
    if (token.empty()) {
        token = headerValue(request, "X-Safety-Gateway-Token");
        transport = "header";
    }
    bool weak_query_token = false;
    if (token.empty() && config.allow_query_token) {
        token = queryValue(request.target, "token");
        transport = "query";
        weak_query_token = !token.empty();
    }

    if (token.empty()) {
        return decision(false, "remote_blocked_missing_token",
                        "remote access requires an access token",
                        "remote_blocked_missing_token",
                        "missing token for client_ip=" + client_ip);
    }
    if (!gatewayAccessTokenMatches(token, config.access_token_hash)) {
        return decision(false, "remote_blocked_invalid_token",
                        "remote access token did not match",
                        "remote_blocked_invalid_token",
                        "invalid token for client_ip=" + client_ip);
    }

    auto out = decision(true,
                        weak_query_token ? "weak_query_token" : "remote_allowed",
                        "client IP and token accepted",
                        weak_query_token ? "remote_query_token_used"
                                         : "remote_allowed",
                        "allowed client_ip=" + client_ip +
                            " token_transport=" + transport);
    if (weak_query_token) {
        out.audit_flags.push_back("weak_query_token");
    }
    return out;
}

}  // namespace aura::safety_gateway
