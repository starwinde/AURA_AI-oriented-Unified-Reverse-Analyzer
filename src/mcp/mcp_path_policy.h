#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct AuraMcpPathDecision {
    bool        allowed = false;
    std::string canonical_path;
    std::string error_code;
    std::string error_message;
};

std::vector<std::filesystem::path> aura_mcp_allowed_roots_from_environment();

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path& candidate);

AuraMcpPathDecision aura_mcp_path_allowed(
    const std::filesystem::path&              candidate,
    const std::vector<std::filesystem::path>& allowed_roots);
