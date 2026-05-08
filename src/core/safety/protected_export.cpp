// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/safety/protected_export.h"

#include "aura/safety/string_safety.h"

#include <utility>

namespace aura::safety {

ProtectedExportRecord buildProtectedExportRecord(int string_id,
                                                 const std::string& content,
                                                 const std::string& source) {
    const SafetyProfile profile = loadDefaultSafetyProfile();
    auto findings = scanStringWithRulePacks(content, profile);
    const auto view = buildProtectedStringView(content, "", std::move(findings));

    ProtectedExportRecord record;
    record.string_id = string_id;
    record.protected_value = view.protected_value;
    record.masked_content = view.masked;
    record.source = source;
    record.findings_count = view.findings.size();
    record.findings.reserve(view.findings.size());
    for (const Finding& finding : view.findings) {
        ProtectedExportFinding exported;
        exported.detector_id = finding.detector_id;
        exported.kind = finding.kind;
        exported.start = finding.start;
        exported.end = finding.end;
        exported.confidence = finding.confidence;
        exported.mask_token = finding.mask_token;
        record.findings.push_back(std::move(exported));
    }
    return record;
}

}  // namespace aura::safety
