#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gateway_policy.h"
#include "gateway_request.h"
#include "gateway_config.h"
#include "mcp_http.h"
#include "remote_access.h"
#include "request_log.h"
#include "session_reveal_store.h"

extern "C" {
#include "cJSON.h"
}

#include <cstdio>
#include <chrono>
#include <filesystem>
#include <memory>
#include <string>

namespace {

struct JsonDeleter {
    void operator()(cJSON* value) const { cJSON_Delete(value); }
};

using JsonPtr = std::unique_ptr<cJSON, JsonDeleter>;

const cJSON* field(const cJSON* root, const char* name) {
    return cJSON_GetObjectItemCaseSensitive(const_cast<cJSON*>(root), name);
}

std::string stringField(const cJSON* root, const char* name) {
    const cJSON* value = field(root, name);
    REQUIRE(cJSON_IsString(value));
    REQUIRE(value->valuestring != nullptr);
    return value->valuestring;
}

std::filesystem::path uniqueCachePath(const char* name) {
    auto path = std::filesystem::temp_directory_path() / name;
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
    return path;
}

}  // namespace

TEST_CASE("safety gateway parses protect_context request") {
    const char* json = R"({
      "request_id":"demo-001",
      "source":"mcp",
      "operation":"protect_context",
      "payload":{"items":[
        {"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}
      ]}
    })";

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    CHECK(aura::safety_gateway::parseGatewayRequest(json, &request, &error));
    CHECK(request.request_id == "demo-001");
    CHECK(request.source == "mcp");
    CHECK(request.operation == "protect_context");
    REQUIRE(request.items.size() == 1);
    CHECK(request.items[0].kind == "string");
    CHECK(request.items[0].location == "0x401000");
    CHECK(request.items[0].category == "unknown");
    CHECK(request.items[0].text == "alice.smith@example.com");
}

TEST_CASE("safety gateway defaults missing category to unknown") {
    const char* json = R"({
      "request_id":"demo-002",
      "source":"mcp",
      "operation":"protect_context",
      "payload":{"items":[
        {"kind":"string","location":"0x401010","text":"normal note"}
      ]}
    })";

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(json, &request, &error));
    REQUIRE(request.items.size() == 1);
    CHECK(request.items[0].category == "unknown");
}

TEST_CASE("safety gateway rejects malformed request") {
    aura::safety_gateway::GatewayRequest request;
    std::string error;
    CHECK_FALSE(aura::safety_gateway::parseGatewayRequest(
        R"({"request_id":"bad","source":"mcp","operation":"protect_context","payload":{}})",
        &request,
        &error));
    CHECK(error.find("payload.items") != std::string::npos);
}

TEST_CASE("safety gateway rejects malformed category field") {
    aura::safety_gateway::GatewayRequest request;
    std::string error;
    CHECK_FALSE(aura::safety_gateway::parseGatewayRequest(
        R"({"request_id":"bad-category","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":7,"text":"normal"}]}})",
        &request,
        &error));
    CHECK(error.find("category") != std::string::npos);
}

TEST_CASE("safety gateway masks sensitive strings without raw original") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-mask.sqlite");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(
        R"({"request_id":"mask-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"},{"kind":"comment","location":"0x401020","category":"unknown","text":"normal reverse engineering note"}]}})",
        &request,
        &error));

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path.string();
    const auto response =
        aura::safety_gateway::evaluateGatewayRequest(request, options);
    const std::string json =
        aura::safety_gateway::gatewayResponseToJson(response, true);

    CHECK(response.decision == "pass");
    CHECK(response.masked_count == 1);
    CHECK(response.raw_original_included == false);
    CHECK(json.find("alice.smith@example.com") == std::string::npos);
    CHECK(json.find("\"original_included\":false") != std::string::npos);
    CHECK(json.find("\"cache_path\"") != std::string::npos);
    CHECK(json.find("\"route\":\"local\"") != std::string::npos);

    JsonPtr root(cJSON_Parse(json.c_str()));
    REQUIRE(root != nullptr);
    REQUIRE(cJSON_IsObject(root.get()));
    CHECK(stringField(root.get(), "request_id") == "mask-001");
    CHECK(stringField(root.get(), "schema_version") ==
          "aura-safety-gateway/1.0");
    const cJSON* items = field(root.get(), "items");
    REQUIRE(cJSON_IsArray(items));
    const cJSON* first = cJSON_GetArrayItem(items, 0);
    REQUIRE(cJSON_IsObject(first));
    CHECK(stringField(first, "action") == "mask");
    CHECK(stringField(first, "category") == "email");
    CHECK(stringField(first, "protected_text").find('*') != std::string::npos);
}

TEST_CASE("safety gateway records cache hit without storing raw original") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-cache.sqlite");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(
        R"({"request_id":"cache-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"010-1234-5678"}]}})",
        &request,
        &error));

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path.string();
    auto first = aura::safety_gateway::evaluateGatewayRequest(request, options);
    auto second = aura::safety_gateway::evaluateGatewayRequest(request, options);

    REQUIRE(first.items.size() == 1);
    REQUIRE(second.items.size() == 1);
    CHECK(first.items[0].action == "mask");
    CHECK(second.items[0].action == "mask");
    CHECK(first.items[0].protected_text == second.items[0].protected_text);

    bool saw_cache_hit = false;
    for (const auto& audit : second.audit) {
        if (audit.reason == "cache hit") {
            saw_cache_hit = true;
            CHECK(audit.action == "mask");
        }
    }
    CHECK(saw_cache_hit);

    const std::string json =
        aura::safety_gateway::gatewayResponseToJson(second, true);
    CHECK(json.find("010-1234-5678") == std::string::npos);

    std::FILE* db = std::fopen(cache_path.string().c_str(), "rb");
    REQUIRE(db != nullptr);
    std::string db_bytes;
    char buffer[1024];
    while (const auto n = std::fread(buffer, 1, sizeof(buffer), db)) {
        db_bytes.append(buffer, n);
    }
    std::fclose(db);
    CHECK(db_bytes.find("010-1234-5678") == std::string::npos);
}

TEST_CASE("safety gateway masks common 010 phone formats") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-phone.sqlite");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(
        R"({"request_id":"phone-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"01012345678"},{"kind":"string","location":"0x401010","category":"unknown","text":"010 1234 5678"}]}})",
        &request,
        &error));

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path.string();
    const auto response =
        aura::safety_gateway::evaluateGatewayRequest(request, options);
    const std::string json =
        aura::safety_gateway::gatewayResponseToJson(response, true);

    CHECK(response.masked_count == 2);
    CHECK(json.find("01012345678") == std::string::npos);
    CHECK(json.find("010 1234 5678") == std::string::npos);
    REQUIRE(response.items.size() == 2);
    CHECK((response.items[0].category == "phone" ||
           response.items[0].category == "phone_number"));
    CHECK((response.items[1].category == "phone" ||
           response.items[1].category == "phone_number"));
}

TEST_CASE("safety gateway uses core safety rules for API keys") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-api-key.sqlite");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(
        "{\"request_id\":\"secret-001\",\"source\":\"mcp\",\"operation\":\"protect_context\","
        "\"payload\":{\"items\":[{\"kind\":\"string\",\"location\":\"0x401000\","
        "\"category\":\"unknown\",\"text\":\"api_key = \\\"abc1234567890XYZSECRET\\\"\"}]}}",
        &request,
        &error));

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path.string();
    const auto response =
        aura::safety_gateway::evaluateGatewayRequest(request, options);
    const std::string json =
        aura::safety_gateway::gatewayResponseToJson(response, true);

    CHECK(response.blocked_count == 1);
    CHECK(response.decision == "block");
    CHECK(json.find("abc1234567890XYZSECRET") == std::string::npos);
    REQUIRE(response.items.size() == 1);
    CHECK(response.items[0].category == "api_key");
    CHECK(response.items[0].protected_text.find('*') != std::string::npos);
    CHECK(response.items[0].action == "block");
}

TEST_CASE("safety gateway preserves block decision for cached API keys") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-api-key-cache.sqlite");

    aura::safety_gateway::GatewayRequest request;
    std::string error;
    REQUIRE(aura::safety_gateway::parseGatewayRequest(
        "{\"request_id\":\"secret-cache-001\",\"source\":\"mcp\",\"operation\":\"protect_context\","
        "\"payload\":{\"items\":[{\"kind\":\"string\",\"location\":\"0x401000\","
        "\"category\":\"unknown\",\"text\":\"api_key = \\\"abc1234567890XYZSECRET\\\"\"}]}}",
        &request,
        &error));

    aura::safety_gateway::GatewayPolicyOptions options;
    options.cache_path = cache_path.string();
    const auto first = aura::safety_gateway::evaluateGatewayRequest(request, options);
    const auto second = aura::safety_gateway::evaluateGatewayRequest(request, options);

    CHECK(first.decision == "block");
    CHECK(second.decision == "block");
    CHECK(second.blocked_count == 1);
    REQUIRE(second.items.size() == 1);
    CHECK(second.items[0].action == "block");

    bool saw_cache_hit = false;
    for (const auto& audit : second.audit) {
        if (audit.reason == "cache hit") {
            saw_cache_hit = true;
            CHECK(audit.action == "block");
        }
    }
    CHECK(saw_cache_hit);
}

TEST_CASE("mcp handler preserves id for initialize") {
    aura::safety_gateway::McpHttpOptions options;
    const auto response = aura::safety_gateway::handleMcpJsonRpc(
        R"({"jsonrpc":"2.0","id":17,"method":"initialize","params":{"protocolVersion":"2025-11-25","capabilities":{},"clientInfo":{"name":"aura-smoke","version":"0.1"}}})",
        options);

    CHECK(response.find("\"id\":17") != std::string::npos);
    CHECK(response.find("\"protocolVersion\":\"2025-11-25\"") != std::string::npos);
    CHECK(response.find("\"name\":\"aura-safety-gateway\"") != std::string::npos);
}

TEST_CASE("mcp handler lists protect context tool") {
    aura::safety_gateway::McpHttpOptions options;
    const auto response = aura::safety_gateway::handleMcpJsonRpc(
        R"({"jsonrpc":"2.0","id":18,"method":"tools/list","params":{}})",
        options);

    CHECK(response.find("\"id\":18") != std::string::npos);
    CHECK(response.find("\"name\":\"aura_gateway_protect_context\"") != std::string::npos);
}

TEST_CASE("mcp handler protects tools call arguments") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-mcp.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();
    const auto response = aura::safety_gateway::handleMcpJsonRpc(
        R"({"jsonrpc":"2.0","id":19,"method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"mcp-001","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}}}})",
        options);

    CHECK(response.find("\"id\":19") != std::string::npos);
    CHECK(response.find("\"content\"") != std::string::npos);
    CHECK(response.find("\\\"decision\\\":\\\"pass\\\"") != std::string::npos);
    CHECK(response.find("\\\"masked_count\\\":1") != std::string::npos);
    CHECK(response.find("alice.smith@example.com") == std::string::npos);
}

TEST_CASE("request log serializes categories and evicts oldest ids") {
    aura::safety_gateway::RequestLog log(1);
    aura::safety_gateway::RequestLogEntry first;
    first.request_id = "old";
    first.timestamp_iso8601 = "2026-05-13T00:00:00Z";
    first.decision = "masked";
    first.route = "local_protect_only";
    first.items.push_back({"item_1", "email", "mask", "al****om", "al***************om", "rule", 0.7});

    aura::safety_gateway::RequestLogEntry second = first;
    second.request_id = "new";
    const auto none = log.append(first);
    const auto evicted = log.append(second);

    CHECK(none.empty());
    REQUIRE(evicted.size() == 1);
    CHECK(evicted[0] == "old");
    CHECK(log.size() == 1);

    const auto json = aura::safety_gateway::requestLogEntriesToJson(log.latest());
    CHECK(json.find("\"request_id\":\"new\"") != std::string::npos);
    CHECK(json.find("\"categories\":[\"email\"]") != std::string::npos);
}

TEST_CASE("session reveal store expires and erases by request id") {
    using Store = aura::safety_gateway::SessionRevealStore;
    Store store(10, std::chrono::seconds(1));
    const auto now = Store::Clock::now();
    store.put({"req-1", "item-1", "email", "alice.smith@example.com"});

    auto found = store.reveal("req-1", "item-1");
    CHECK(found.found);
    CHECK(found.original == "alice.smith@example.com");

    CHECK(store.expire(now + std::chrono::seconds(5)) >= 0);
    auto missing = store.reveal("req-1", "item-1", now + std::chrono::seconds(5));
    CHECK_FALSE(missing.found);

    store.put({"req-2", "item-1", "phone", "010-1234-5678"});
    CHECK(store.eraseByRequestId("req-2") == 1);
    CHECK_FALSE(store.reveal("req-2", "item-1").found);
}

TEST_CASE("remote access gate requires allowed ip and token when enabled") {
    aura::safety_gateway::GatewayConfig config =
        aura::safety_gateway::defaultGatewayConfig();
    config.remote.enabled = true;
    aura::safety_gateway::setGatewayAccessToken(&config, "demo-token");

    aura::safety_gateway::RemoteAccessRequest request;
    request.client_ip = "127.0.0.1";
    request.target = "/mcp";
    request.headers["Authorization"] = "Bearer demo-token";

    auto allowed = aura::safety_gateway::evaluateRemoteAccess(config.remote, request);
    CHECK(allowed.allowed);
    CHECK(allowed.result_code == "remote_allowed");

    request.headers.clear();
    auto missing = aura::safety_gateway::evaluateRemoteAccess(config.remote, request);
    CHECK_FALSE(missing.allowed);
    CHECK(missing.result_code == "remote_blocked_missing_token");

    request.client_ip = "192.0.2.10";
    request.headers["Authorization"] = "Bearer demo-token";
    auto blocked_ip = aura::safety_gateway::evaluateRemoteAccess(config.remote, request);
    CHECK_FALSE(blocked_ip.allowed);
    CHECK(blocked_ip.result_code == "remote_blocked_ip");
}

TEST_CASE("mcp detailed result includes request log and protected forward body") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-detailed.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();

    const auto detailed = aura::safety_gateway::handleMcpJsonRpcDetailed(
        R"({"jsonrpc":"2.0","id":21,"method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"mcp-detailed","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"0x401000","category":"unknown","text":"alice.smith@example.com"}]}}}})",
        options);

    CHECK(detailed.response_json.find("\"id\":21") != std::string::npos);
    CHECK(detailed.has_request_log);
    CHECK(detailed.request_log.request_id == "mcp-detailed");
    CHECK(detailed.request_log.decision == "masked");
    REQUIRE(detailed.request_log.items.size() == 1);
    CHECK(detailed.request_log.items[0].item_id == "item_1");
    REQUIRE(detailed.reveal_records.size() == 1);
    CHECK(detailed.reveal_records[0].original == "alice.smith@example.com");
    CHECK(detailed.protected_forward_body.find("alice.smith@example.com") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("*") != std::string::npos);
}

TEST_CASE("mcp gateway tool also protects supplemental argument strings") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-gateway-extra.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();

    const auto detailed = aura::safety_gateway::handleMcpJsonRpcDetailed(
        R"({"jsonrpc":"2.0","id":"gateway-extra","method":"tools/call","params":{"name":"aura_gateway_protect_context","arguments":{"request_id":"gateway-extra","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"payload","category":"unknown","text":"safe payload text"}]},"metadata":{"owner_email":"alice.smith@example.com"},"note":"call me at 010-1234-5678"}}}})",
        options);

    CHECK(detailed.has_request_log);
    CHECK(detailed.request_log.decision == "masked");
    CHECK(detailed.protected_forward_body.find("alice.smith@example.com") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("010-1234-5678") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("*") != std::string::npos);
    CHECK(detailed.request_log.items.size() >= 3);
    CHECK(detailed.protected_forward_body.find("\"request_id\":\"gateway-extra\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"source\":\"mcp\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"operation\":\"protect_context\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"kind\":\"string\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"location\":\"payload\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"category\":\"unknown\"") != std::string::npos);
}

TEST_CASE("mcp gateway tool protects params outside arguments before forwarding") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-gateway-param-meta.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();

    const auto detailed = aura::safety_gateway::handleMcpJsonRpcDetailed(
        R"({"jsonrpc":"2.0","id":"gateway-param-meta","method":"tools/call","params":{"name":"aura_gateway_protect_context","_meta":{"owner_email":"alice.smith@example.com"},"arguments":{"request_id":"gateway-param-meta","source":"mcp","operation":"protect_context","payload":{"items":[{"kind":"string","location":"payload","category":"unknown","text":"safe payload text"}]}}}})",
        options);

    CHECK(detailed.has_request_log);
    CHECK(detailed.request_log.decision == "masked");
    CHECK(detailed.protected_forward_body.find("alice.smith@example.com") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"_meta\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"name\":\"aura_gateway_protect_context\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("*") != std::string::npos);
}

TEST_CASE("mcp detailed result protects arbitrary tool call arguments") {
    const auto cache_path =
        uniqueCachePath("aura-safety-gateway-unit-generic-tool.sqlite");
    aura::safety_gateway::McpHttpOptions options;
    options.policy.cache_path = cache_path.string();

    const auto detailed = aura::safety_gateway::handleMcpJsonRpcDetailed(
        R"({"jsonrpc":"2.0","id":"generic-1","method":"tools/call","params":{"name":"demo_external_tool","arguments":{"query":"summarize alice.smith@example.com","nested":{"phone":"010-1234-5678"}}}})",
        options);

    CHECK(detailed.response_json.find("\"id\":\"generic-1\"") != std::string::npos);
    CHECK(detailed.has_request_log);
    CHECK(detailed.request_log.tool_name == "demo_external_tool");
    CHECK(detailed.request_log.items.size() == 2);
    CHECK(detailed.request_log.decision == "masked");
    CHECK(detailed.protected_forward_body.find("alice.smith@example.com") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("010-1234-5678") == std::string::npos);
    CHECK(detailed.protected_forward_body.find("demo_external_tool") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"query\"") != std::string::npos);
    CHECK(detailed.protected_forward_body.find("\"nested\"") != std::string::npos);
}
