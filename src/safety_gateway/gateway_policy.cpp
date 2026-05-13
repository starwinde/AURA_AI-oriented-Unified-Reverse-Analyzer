#include "gateway_policy.h"

#include "gateway_cache.h"
#include "aura/safety/string_safety.h"

#include <algorithm>
#include <cctype>
#include <vector>

namespace aura::safety_gateway {
namespace {

std::string starMask(const std::string& value) {
    if (value.empty()) return "*";
    const int len = static_cast<int>(value.size());
    int mask_count = (len * 65 + 50) / 100;
    mask_count = std::max(1, std::min(mask_count, len));
    const int visible = len - mask_count;
    const int prefix = visible / 2 + visible % 2;
    const int suffix = visible / 2;
    return value.substr(0, static_cast<size_t>(prefix)) +
           std::string(static_cast<size_t>(mask_count), '*') +
           (suffix > 0 ? value.substr(value.size() - static_cast<size_t>(suffix)) : std::string());
}

bool looksSensitiveByFallback(const std::string& value, std::string* category) {
    std::string lowered = value;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    const auto contains = [&](const char* needle) {
        return lowered.find(needle) != std::string::npos;
    };
    if (value.find('@') != std::string::npos && value.find('.') != std::string::npos) {
        if (category) *category = "email";
        return true;
    }
    if (contains("api_key") || contains("apikey") || contains("access_key") ||
        contains("secret") || contains("password") || contains("passwd") ||
        contains("bearer ") || contains("token") || contains("sk-") ||
        contains("ghp_") || contains("xoxb-") || contains("akia")) {
        if (category) *category = "api_key";
        return true;
    }
    std::string digits;
    for (unsigned char ch : value) {
        if (std::isdigit(ch)) {
            digits.push_back(static_cast<char>(ch));
        }
    }
    if ((digits.size() == 10 || digits.size() == 11) && digits.rfind("010", 0) == 0) {
        if (category) *category = "phone";
        return true;
    }
    if (value.size() >= 13 && value.find('-') != std::string::npos) {
        if (category) *category = "identifier";
        return true;
    }
    return false;
}

bool isHardSecretCategory(const std::string& category) {
    return category == "api_key" || category == "secret" || category == "token" ||
           category == "password" || category == "credential";
}

aura::safety::Finding fallbackFinding(const std::string& value,
                                      const std::string& category) {
    aura::safety::Finding finding;
    finding.source = aura::safety::FindingSource::Rule;
    finding.detector_id = "gateway_fallback";
    finding.kind = category.empty() ? "sensitive" : category;
    finding.start = 0;
    finding.end = value.size();
    finding.confidence = 0.70;
    return finding;
}

std::string effectivePolicyHash(const GatewayPolicyOptions& options,
                                const aura::safety::SafetyProfile& profile) {
    if (!options.policy_hash.empty() && options.policy_hash != "default-policy") {
        return options.policy_hash;
    }
    return "default-rulepacks-v1:rules=" +
           std::to_string(aura::safety::effectiveRuleCount(profile)) +
           ":fallback=v2";
}

}  // namespace

GatewayResponse evaluateGatewayRequest(const GatewayRequest& request,
                                       const GatewayPolicyOptions& options) {
    GatewayResponse response;
    response.request_id = request.request_id;
    response.decision = "pass";
    response.route = "local";
    response.items_total = static_cast<int>(request.items.size());

    const std::string cache_path =
        options.cache_path.empty() ? defaultGatewayCachePath() : options.cache_path;
    const aura::safety::SafetyProfile safety_profile =
        aura::safety::loadDefaultSafetyProfile();
    const std::string policy_hash = effectivePolicyHash(options, safety_profile);
    if (options.include_cache_path_in_response) {
        response.cache_path = cache_path;
    }

    for (const auto& item : request.items) {
        GatewayCacheKey key{gatewayContentHash(item), policy_hash, item.kind};
        GatewayCacheEntry cached;
        if (options.use_cache && lookupGatewayCache(cache_path, key, &cached)) {
            GatewayOutputItem out;
            out.kind = item.kind;
            out.location = item.location;
            out.category = cached.category;
            out.protected_text = cached.protected_text;
            out.action = cached.action;
            out.original_included = false;
            if (out.action == "mask") response.masked_count += 1;
            if (out.action == "block") {
                response.blocked_count += 1;
                response.decision = "block";
            }

            GatewayAuditRecord audit;
            audit.action = out.action;
            audit.kind = item.kind;
            audit.location = item.location;
            audit.category = cached.category;
            audit.safe_preview = cached.protected_text;
            audit.reason = "cache hit";
            response.items.push_back(std::move(out));
            response.audit.push_back(std::move(audit));
            continue;
        }

        std::string fallback_category = item.category.empty() ? "unknown" : item.category;
        std::vector<aura::safety::Finding> findings =
            aura::safety::scanStringWithRulePacks(item.text, safety_profile);
        const bool fallback_matched =
            looksSensitiveByFallback(item.text, &fallback_category);
        if (findings.empty() && fallback_matched) {
            findings.push_back(fallbackFinding(item.text, fallback_category));
        }
        const bool matched = !findings.empty();
        const aura::safety::ProtectedStringView view =
            aura::safety::buildProtectedStringView(item.text, "", findings);
        const std::string category = matched ? view.findings.front().kind :
                                     (item.category.empty() ? "unknown" : item.category);

        GatewayOutputItem out;
        out.kind = item.kind;
        out.location = item.location;
        out.category = category;
        out.original_included = false;

        GatewayAuditRecord audit;
        audit.kind = item.kind;
        audit.location = item.location;
        audit.category = category;

        if (matched) {
            const bool hard_secret = isHardSecretCategory(category);
            out.action = hard_secret ? "block" : "mask";
            out.protected_text = view.protected_value;
            if (out.protected_text == item.text) {
                out.protected_text = starMask(item.text);
            }
            if (hard_secret) {
                response.blocked_count += 1;
                response.decision = "block";
            } else {
                response.masked_count += 1;
            }
            audit.action = out.action;
            audit.safe_preview = out.protected_text;
            audit.reason = view.findings.front().detector_id.empty()
                               ? "safety rule matched"
                               : view.findings.front().detector_id;
        } else {
            out.action = "allow";
            out.protected_text = item.text;
            audit.action = "allow";
            audit.safe_preview = out.protected_text;
            audit.reason = "no protected value detected";
        }

        if (matched && out.protected_text == item.text) {
            response.decision = "block";
            response.blocked_count += 1;
            response.raw_original_included = true;
            out.action = "block";
            audit.action = "block";
            audit.reason = "protected value would be exported raw";
        }

        response.items.push_back(std::move(out));
        response.audit.push_back(std::move(audit));

        if (options.use_cache) {
            const auto& saved = response.items.back();
            GatewayCacheEntry entry;
            entry.key = key;
            entry.category = saved.category;
            entry.action = saved.action;
            entry.protected_text = saved.protected_text;
            entry.detector_summary = matched ? audit.reason : "no-match";
            storeGatewayCache(cache_path, entry);
        }
    }

    return response;
}

}  // namespace aura::safety_gateway
