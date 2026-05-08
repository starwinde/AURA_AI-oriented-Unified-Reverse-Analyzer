// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace aura::safety {

struct ProtectedExportFinding {
    std::string detector_id;
    std::string kind;
    std::size_t start = 0;
    std::size_t end = 0;
    double confidence = 0.0;
    std::string mask_token;
};

struct ProtectedExportRecord {
    int string_id = 0;
    std::string protected_value;
    std::string masked_content;
    std::string source;
    std::string raw_content;
    std::size_t findings_count = 0;
    std::vector<ProtectedExportFinding> findings;
};

ProtectedExportRecord buildProtectedExportRecord(int string_id,
                                                 const std::string& content,
                                                 const std::string& source);

}  // namespace aura::safety
