// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

namespace aura::safety {

struct DetectedStringEncoding {
    std::string label;
    double confidence = 0.0;
    std::string display;
    bool lossy = false;
};

DetectedStringEncoding detectStringEncoding(const std::string& bytes);
std::string displayLiteralForEncoding(const DetectedStringEncoding& encoding);

}  // namespace aura::safety
