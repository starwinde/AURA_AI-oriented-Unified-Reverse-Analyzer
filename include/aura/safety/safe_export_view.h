// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <vector>

namespace aura::safety {

struct SafeExportInput {
    std::string kind;
    std::string location;
    std::string category;
    std::string original_value;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
};

struct SafeExportItem {
    std::string kind;
    std::string location;
    std::string category;
    std::string display_value;
    std::string transmission_value;
    std::string mask_token;
    bool original_included = false;
};

SafeExportItem makeSafeExportItem(const SafeExportInput& input);
std::vector<SafeExportItem> makeSafeExportItems(
    const std::vector<SafeExportInput>& inputs);

}  // namespace aura::safety
