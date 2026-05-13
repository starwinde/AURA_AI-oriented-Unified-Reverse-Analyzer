// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/safety/safe_export_view.h"

namespace aura::safety {

SafeExportItem makeSafeExportItem(const SafeExportInput& input) {
    SafeExportItem item;
    item.kind = input.kind;
    item.location = input.location;
    item.category = input.category;
    item.display_value = input.display_value;
    if (!input.original_value.empty() &&
        item.display_value == input.original_value) {
        item.display_value.clear();
    }
    item.transmission_value = input.transmission_value;
    if (!input.original_value.empty() &&
        item.transmission_value == input.original_value) {
        item.transmission_value = item.display_value;
    }
    item.mask_token = input.mask_token;
    item.original_included = false;
    return item;
}

std::vector<SafeExportItem> makeSafeExportItems(
    const std::vector<SafeExportInput>& inputs) {
    std::vector<SafeExportItem> items;
    items.reserve(inputs.size());
    for (const SafeExportInput& input : inputs) {
        items.push_back(makeSafeExportItem(input));
    }
    return items;
}

}  // namespace aura::safety
