#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "aura/mcp/mcp_envelope.h"

#include "cJSON.h"

#include <string>

namespace {

const cJSON* field(const cJSON* root, const char* name) {
    return cJSON_GetObjectItemCaseSensitive(root, name);
}

std::string stringField(const cJSON* root, const char* name) {
    const cJSON* item = field(root, name);
    REQUIRE(item != nullptr);
    REQUIRE(cJSON_IsString(item));
    REQUIRE(item->valuestring != nullptr);
    return item->valuestring;
}

}  // namespace

TEST_CASE("success envelope has ADR-0057 shape and validates") {
    cJSON* data = cJSON_CreateObject();
    REQUIRE(data != nullptr);
    cJSON_AddStringToObject(data, "engine", "probe");

    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0",
                                           "probe_result",
                                           data,
                                           "protected");
    REQUIRE(env != nullptr);

    CHECK(stringField(env, "mcp_schema_version") == "1.0");
    CHECK(stringField(env, "tool_schema_version") ==
          "aura_probe_engines/1.0");
    CHECK(stringField(env, "kind") == "probe_result");
    CHECK(stringField(env, "status") == "ok");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(cJSON_IsObject(field(env, "data")));
    CHECK(cJSON_IsNull(field(env, "error")));
    CHECK(cJSON_IsArray(field(env, "warnings")));
    CHECK(cJSON_GetArraySize(field(env, "warnings")) == 0);
    CHECK(cJSON_IsNull(field(env, "audit")));
    CHECK(aura_mcp_envelope_is_valid(env) == 1);

    cJSON_Delete(env);
}

TEST_CASE("success envelope creates an empty data object when data is null") {
    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0",
                                           "probe_result",
                                           nullptr,
                                           "protected");
    REQUIRE(env != nullptr);

    CHECK(cJSON_IsObject(field(env, "data")));
    CHECK(cJSON_GetArraySize(field(env, "data")) == 0);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);

    cJSON_Delete(env);
}

TEST_CASE("error envelope has ADR-0057 shape and validates") {
    cJSON* env = aura_mcp_envelope_error("aura_probe_engines/1.0",
                                         "probe_result",
                                         "engine_missing",
                                         "rizin was not found",
                                         "protected");
    REQUIRE(env != nullptr);

    CHECK(stringField(env, "mcp_schema_version") == "1.0");
    CHECK(stringField(env, "tool_schema_version") ==
          "aura_probe_engines/1.0");
    CHECK(stringField(env, "kind") == "probe_result");
    CHECK(stringField(env, "status") == "error");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(cJSON_IsNull(field(env, "data")));
    REQUIRE(cJSON_IsObject(field(env, "error")));
    CHECK(stringField(field(env, "error"), "code") == "engine_missing");
    CHECK(stringField(field(env, "error"), "message") ==
          "rizin was not found");
    CHECK(cJSON_IsArray(field(env, "warnings")));
    CHECK(cJSON_IsNull(field(env, "audit")));
    CHECK(aura_mcp_envelope_is_valid(env) == 1);

    cJSON_Delete(env);
}

TEST_CASE("warning append adds warning strings and preserves validity") {
    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0",
                                           "probe_result",
                                           nullptr,
                                           "protected");
    REQUIRE(env != nullptr);

    CHECK(aura_mcp_envelope_add_warning(env, "using cached probe result") ==
          env);

    const cJSON* warnings = field(env, "warnings");
    REQUIRE(cJSON_IsArray(warnings));
    REQUIRE(cJSON_GetArraySize(warnings) == 1);
    const cJSON* warning = cJSON_GetArrayItem(warnings, 0);
    REQUIRE(cJSON_IsString(warning));
    CHECK(std::string(warning->valuestring) == "using cached probe result");
    CHECK(aura_mcp_envelope_is_valid(env) == 1);

    cJSON_Delete(env);
}

TEST_CASE("invalid and null envelopes are rejected") {
    CHECK(aura_mcp_envelope_is_valid(nullptr) == 0);
    CHECK(aura_mcp_envelope_add_warning(nullptr, "warning") == nullptr);

    cJSON* missing_data = cJSON_CreateObject();
    REQUIRE(missing_data != nullptr);
    cJSON_AddStringToObject(missing_data, "mcp_schema_version", "1.0");
    cJSON_AddStringToObject(missing_data, "tool_schema_version",
                            "aura_probe_engines/1.0");
    cJSON_AddStringToObject(missing_data, "kind", "probe_result");
    cJSON_AddStringToObject(missing_data, "status", "ok");
    cJSON_AddStringToObject(missing_data, "disclosure", "protected");
    cJSON_AddItemToObject(missing_data, "warnings", cJSON_CreateArray());
    cJSON_AddNullToObject(missing_data, "audit");

    CHECK(aura_mcp_envelope_is_valid(missing_data) == 0);

    cJSON_Delete(missing_data);
}

TEST_CASE("validator rejects malformed warning arrays") {
    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0",
                                           "probe_result",
                                           nullptr,
                                           "protected");
    REQUIRE(env != nullptr);

    cJSON* warnings = cJSON_GetObjectItemCaseSensitive(env, "warnings");
    REQUIRE(cJSON_IsArray(warnings));
    cJSON_AddItemToArray(warnings, cJSON_CreateString(""));
    CHECK(aura_mcp_envelope_is_valid(env) == 0);

    cJSON_DeleteItemFromArray(warnings, 0);
    cJSON_AddItemToArray(warnings, cJSON_CreateNumber(7));
    CHECK(aura_mcp_envelope_is_valid(env) == 0);

    cJSON_Delete(env);
}

TEST_CASE("validator rejects invalid error object fields") {
    cJSON* env = aura_mcp_envelope_error("aura_probe_engines/1.0",
                                         "probe_result",
                                         "engine_missing",
                                         "rizin was not found",
                                         "protected");
    REQUIRE(env != nullptr);

    cJSON* error = cJSON_GetObjectItemCaseSensitive(env, "error");
    REQUIRE(cJSON_IsObject(error));

    cJSON_ReplaceItemInObjectCaseSensitive(error, "code",
                                           cJSON_CreateString(""));
    CHECK(aura_mcp_envelope_is_valid(env) == 0);

    cJSON_ReplaceItemInObjectCaseSensitive(error, "code",
                                           cJSON_CreateString("engine_missing"));
    cJSON_ReplaceItemInObjectCaseSensitive(error, "message",
                                           cJSON_CreateNumber(3));
    CHECK(aura_mcp_envelope_is_valid(env) == 0);

    cJSON_Delete(env);
}

TEST_CASE("success builder rejects non-object caller data") {
    cJSON* data = cJSON_CreateArray();
    REQUIRE(data != nullptr);

    cJSON* env = aura_mcp_envelope_success("aura_probe_engines/1.0",
                                           "probe_result",
                                           data,
                                           "protected");
    CHECK(env == nullptr);

    // The rejected node remains caller-owned. Do not delete it here because
    // the pre-fix implementation incorrectly consumed it on failure.
}
