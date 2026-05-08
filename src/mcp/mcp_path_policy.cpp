#include "mcp_path_policy.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <system_error>
#include <utility>

namespace {

namespace fs = std::filesystem;

constexpr const char* kAllowedRootsEnv = "AURA_MCP_ALLOWED_ROOTS";

char rootSeparator() {
#ifdef _WIN32
    return ';';
#else
    return ':';
#endif
}

std::string trim(std::string value) {
    const auto not_space = [](unsigned char ch) {
        return std::isspace(ch) == 0;
    };
    value.erase(value.begin(),
                std::find_if(value.begin(), value.end(), not_space));
    value.erase(std::find_if(value.rbegin(), value.rend(), not_space).base(),
                value.end());
    return value;
}

AuraMcpPathDecision denied(std::string canonical_path,
                           std::string code,
                           std::string message) {
    AuraMcpPathDecision decision;
    decision.allowed = false;
    decision.canonical_path = std::move(canonical_path);
    decision.error_code = std::move(code);
    decision.error_message = std::move(message);
    return decision;
}

fs::path canonicalizeRoot(const fs::path& root, std::error_code& ec) {
    ec.clear();
    return fs::canonical(root, ec);
}

bool samePathComponent(const fs::path& lhs, const fs::path& rhs) {
#ifdef _WIN32
    return _stricmp(lhs.string().c_str(), rhs.string().c_str()) == 0;
#else
    return lhs == rhs;
#endif
}

bool isUnderRoot(const fs::path& child, const fs::path& root) {
    auto child_it = child.begin();
    auto root_it = root.begin();

    for (; root_it != root.end(); ++root_it, ++child_it) {
        if (child_it == child.end() ||
            !samePathComponent(*child_it, *root_it)) {
            return false;
        }
    }
    return true;
}

std::vector<fs::path> splitAllowedRoots(const std::string& raw_roots) {
    std::vector<fs::path> roots;
    std::stringstream     stream(raw_roots);
    std::string           item;

    while (std::getline(stream, item, rootSeparator())) {
        item = trim(std::move(item));
        if (!item.empty()) {
            roots.emplace_back(item);
        }
    }
    return roots;
}

}  // namespace

std::vector<std::filesystem::path> aura_mcp_allowed_roots_from_environment() {
    const char* raw = std::getenv(kAllowedRootsEnv);
    if (raw == nullptr || trim(raw).empty()) {
        return {std::filesystem::current_path()};
    }
    return splitAllowedRoots(raw);
}

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path& candidate) {
    return aura_mcp_path_allowed(candidate,
                                 aura_mcp_allowed_roots_from_environment());
}

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path&              candidate,
    const std::vector<std::filesystem::path>& allowed_roots) {
    std::error_code ec;
    if (candidate.empty() || !fs::exists(candidate, ec)) {
        return denied("", "path_not_found",
                      "path does not exist or is not accessible");
    }
    if (ec) {
        return denied("", "path_not_found",
                      "path does not exist or is not accessible");
    }

    const fs::path canonical_candidate = fs::canonical(candidate, ec);
    if (ec) {
        return denied("", "path_unresolved", "path cannot be canonicalized");
    }

    if (!fs::is_regular_file(canonical_candidate, ec) || ec) {
        return denied(canonical_candidate.string(), "not_a_regular_file",
                      "path is not a regular file");
    }

    bool had_valid_root = false;
    for (const fs::path& raw_root : allowed_roots) {
        if (raw_root.empty()) {
            continue;
        }

        const fs::path canonical_root = canonicalizeRoot(raw_root, ec);
        if (ec) {
            continue;
        }
        if (!fs::is_directory(canonical_root, ec) || ec) {
            continue;
        }
        had_valid_root = true;

        if (isUnderRoot(canonical_candidate, canonical_root)) {
            AuraMcpPathDecision decision;
            decision.allowed = true;
            decision.canonical_path = canonical_candidate.string();
            return decision;
        }
    }

    if (!had_valid_root) {
        return denied(canonical_candidate.string(), "no_allowed_roots",
                      "no configured allowlist roots could be resolved");
    }

    return denied(canonical_candidate.string(), "path_denied",
                  "path is outside AURA_MCP_ALLOWED_ROOTS");
}
