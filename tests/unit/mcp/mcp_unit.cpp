#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "aura/safety/protected_export.h"
#include "aura/mcp/mcp_envelope.h"
#include "mcp_cli_bridge_internal.h"
#include "mcp_path_policy.h"
#include "mcp_tools.h"

#include "cJSON.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

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

bool hasToolNamed(const cJSON* tools, const char* name) {
    const cJSON* tool = nullptr;
    cJSON_ArrayForEach(tool, tools) {
        const cJSON* tool_name = field(tool, "name");
        if (cJSON_IsString(tool_name) && tool_name->valuestring != nullptr &&
            std::string(tool_name->valuestring) == name) {
            return true;
        }
    }
    return false;
}

const cJSON* toolNamed(const cJSON* tools, const char* name) {
    const cJSON* tool = nullptr;
    cJSON_ArrayForEach(tool, tools) {
        const cJSON* tool_name = field(tool, "name");
        if (cJSON_IsString(tool_name) && tool_name->valuestring != nullptr &&
            std::string(tool_name->valuestring) == name) {
            return tool;
        }
    }
    return nullptr;
}

bool arrayHasString(const cJSON* array, const char* value) {
    const cJSON* item = nullptr;
    cJSON_ArrayForEach(item, array) {
        if (cJSON_IsString(item) && item->valuestring != nullptr &&
            std::string(item->valuestring) == value) {
            return true;
        }
    }
    return false;
}

std::string errorCode(const cJSON* envelope) {
    const cJSON* error = field(envelope, "error");
    REQUIRE(cJSON_IsObject(error));
    return stringField(error, "code");
}

void setEnvVar(const char* name, const std::string& value) {
#ifdef _WIN32
    REQUIRE(_putenv_s(name, value.c_str()) == 0);
#else
    REQUIRE(setenv(name, value.c_str(), 1) == 0);
#endif
}

void unsetEnvVar(const char* name) {
#ifdef _WIN32
    REQUIRE(_putenv_s(name, "") == 0);
#else
    REQUIRE(unsetenv(name) == 0);
#endif
}

std::string getEnvVar(const char* name) {
    const char* value = std::getenv(name);
    return value != nullptr ? value : "";
}

class ScopedEnvVar {
  public:
    explicit ScopedEnvVar(const char* name)
        : name_(name), had_value_(std::getenv(name) != nullptr),
          old_value_(getEnvVar(name)) {}

    ~ScopedEnvVar() {
        if (had_value_) {
            setEnvVar(name_, old_value_);
        } else {
            unsetEnvVar(name_);
        }
    }

    ScopedEnvVar(const ScopedEnvVar&) = delete;
    ScopedEnvVar& operator=(const ScopedEnvVar&) = delete;

  private:
    const char* name_;
    bool        had_value_;
    std::string old_value_;
};

class TempTree {
  public:
    TempTree()
        : root_(makeUniqueTempPath()) {
        std::filesystem::create_directories(root_);
    }

    ~TempTree() {
        std::error_code ec;
        std::filesystem::remove_all(root_, ec);
    }

    const std::filesystem::path& root() const {
        return root_;
    }

    std::filesystem::path writeFile(const std::filesystem::path& relative,
                                    const std::string& contents = "fixture") {
        const auto path = root_ / relative;
        std::filesystem::create_directories(path.parent_path());
        std::ofstream out(path, std::ios::binary);
        REQUIRE(out.good());
        out << contents;
        out.close();
        REQUIRE(out.good());
        return path;
    }

  private:
    static std::filesystem::path makeUniqueTempPath() {
        const auto base = std::filesystem::temp_directory_path();
        for (int i = 0; i < 100; ++i) {
            const auto ticks =
                std::chrono::steady_clock::now().time_since_epoch().count();
            auto path = base / ("aura-mcp-path-policy-" +
                                std::to_string(ticks) + "-" +
                                std::to_string(i));
            if (!std::filesystem::exists(path)) {
                return path;
            }
        }
        FAIL("could not allocate unique temp path");
        return base / "aura-mcp-path-policy-failed";
    }

    std::filesystem::path root_;
};

class ScopedSafetyAssets {
  public:
    ScopedSafetyAssets()
        : aura_home_("AURA_HOME"),
          safety_assets_("AURA_SAFETY_ASSETS_DIR") {
        setEnvVar("AURA_HOME", home_.root().string());
        setEnvVar("AURA_SAFETY_ASSETS_DIR", assets_.root().string());
    }

    ScopedSafetyAssets(const ScopedSafetyAssets&) = delete;
    ScopedSafetyAssets& operator=(const ScopedSafetyAssets&) = delete;

  private:
    TempTree home_;
    TempTree assets_;
    ScopedEnvVar aura_home_;
    ScopedEnvVar safety_assets_;
};

char pathListSeparator() {
#ifdef _WIN32
    return ';';
#else
    return ':';
#endif
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

TEST_CASE("error envelope rejects empty or null code/message") {
    CHECK(aura_mcp_envelope_error("aura_probe_engines/1.0",
                                  "probe_result",
                                  nullptr,
                                  "missing code",
                                  "protected") == nullptr);
    CHECK(aura_mcp_envelope_error("aura_probe_engines/1.0",
                                  "probe_result",
                                  "",
                                  "missing code",
                                  "protected") == nullptr);
    CHECK(aura_mcp_envelope_error("aura_probe_engines/1.0",
                                  "probe_result",
                                  "missing message",
                                  nullptr,
                                  "protected") == nullptr);
    CHECK(aura_mcp_envelope_error("aura_probe_engines/1.0",
                                  "probe_result",
                                  "missing message",
                                  "",
                                  "protected") == nullptr);
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

    cJSON_Delete(data);
}

TEST_CASE("path policy rejects files when env allowlist is unset or empty") {
    ScopedEnvVar env("AURA_MCP_ALLOWED_ROOTS");
    TempTree temp;
    const auto file = temp.writeFile("bin/sample.bin");

    unsetEnvVar("AURA_MCP_ALLOWED_ROOTS");
    const AuraMcpPathDecision unset_decision = aura_mcp_path_allowed(file);

    CHECK_FALSE(unset_decision.allowed);
    CHECK(unset_decision.canonical_path ==
          std::filesystem::canonical(file).string());
    CHECK(unset_decision.error_code == "no_allowed_roots");
    CHECK_FALSE(unset_decision.error_message.empty());

    setEnvVar("AURA_MCP_ALLOWED_ROOTS", "");
    const AuraMcpPathDecision empty_decision = aura_mcp_path_allowed(file);

    CHECK_FALSE(empty_decision.allowed);
    CHECK(empty_decision.canonical_path ==
          std::filesystem::canonical(file).string());
    CHECK(empty_decision.error_code == "no_allowed_roots");
    CHECK_FALSE(empty_decision.error_message.empty());
}

TEST_CASE("path policy allows files under direct explicit roots") {
    TempTree temp;
    const auto file = temp.writeFile("bin/sample.bin");

    const AuraMcpPathDecision decision =
        aura_mcp_path_allowed(file, {temp.root()});

    CHECK(decision.allowed);
    CHECK(decision.canonical_path == std::filesystem::canonical(file).string());
    CHECK(decision.error_code.empty());
    CHECK(decision.error_message.empty());
}

TEST_CASE("path policy rejects sibling prefix escapes outside allowed roots") {
    TempTree temp;
    const auto allowed_root = temp.root() / "repo";
    const auto sibling_root = temp.root() / "repo2";
    std::filesystem::create_directories(allowed_root);
    std::filesystem::create_directories(sibling_root);
    const auto sibling_file = sibling_root / "escape.bin";
    {
        std::ofstream out(sibling_file, std::ios::binary);
        REQUIRE(out.good());
        out << "escape";
    }

    const AuraMcpPathDecision decision =
        aura_mcp_path_allowed(sibling_file, {allowed_root});

    CHECK_FALSE(decision.allowed);
    CHECK(decision.canonical_path ==
          std::filesystem::canonical(sibling_file).string());
    CHECK(decision.error_code == "path_denied");
    CHECK_FALSE(decision.error_message.empty());
}

TEST_CASE("path policy env allowlist allows a temp fixture path") {
    ScopedEnvVar env("AURA_MCP_ALLOWED_ROOTS");
    TempTree temp;
    const auto file = temp.writeFile("fixture.bin");
    setEnvVar("AURA_MCP_ALLOWED_ROOTS", temp.root().string());

    const AuraMcpPathDecision decision = aura_mcp_path_allowed(file);

    CHECK(decision.allowed);
    CHECK(decision.canonical_path == std::filesystem::canonical(file).string());
    CHECK(decision.error_code.empty());
}

TEST_CASE("path policy rejects nonexistent paths") {
    TempTree temp;
    const auto missing = temp.root() / "missing.bin";

    const AuraMcpPathDecision decision =
        aura_mcp_path_allowed(missing, {temp.root()});

    CHECK_FALSE(decision.allowed);
    CHECK(decision.canonical_path.empty());
    CHECK(decision.error_code == "path_not_found");
    CHECK_FALSE(decision.error_message.empty());
}

TEST_CASE("path policy ignores malformed and empty env entries safely") {
    ScopedEnvVar env("AURA_MCP_ALLOWED_ROOTS");
    TempTree temp;
    const auto file = temp.writeFile("nested/fixture.bin");
    const auto bad_root = temp.root() / "does-not-exist";
    const std::string roots = std::string(1, pathListSeparator()) +
                              bad_root.string() + pathListSeparator() +
                              std::string(1, pathListSeparator()) +
                              (temp.root() / "nested").string() +
                              pathListSeparator();
    setEnvVar("AURA_MCP_ALLOWED_ROOTS", roots);

    const AuraMcpPathDecision decision = aura_mcp_path_allowed(file);

    CHECK(decision.allowed);
    CHECK(decision.canonical_path == std::filesystem::canonical(file).string());
    CHECK(decision.error_code.empty());
}

TEST_CASE("mcp tool registry lists protected and raw tool names") {
    cJSON* tools = aura_mcp_tools_list_json();
    REQUIRE(cJSON_IsArray(tools));

    CHECK(hasToolNamed(tools, "aura_probe_engines"));
    CHECK(hasToolNamed(tools, "aura_info"));
    CHECK(hasToolNamed(tools, "aura_analyze"));
    CHECK(hasToolNamed(tools, "aura_get_disassembly"));
    CHECK(hasToolNamed(tools, "aura_get_cfg"));
    CHECK(hasToolNamed(tools, "aura_get_llm_context"));
    CHECK(hasToolNamed(tools, "aura_get_raw_disassembly"));
    CHECK(hasToolNamed(tools, "aura_get_raw_decompile"));

    cJSON_Delete(tools);
}

TEST_CASE("mcp tool registry objects include input schemas") {
    cJSON* tools = aura_mcp_tools_list_json();
    REQUIRE(cJSON_IsArray(tools));
    REQUIRE(cJSON_GetArraySize(tools) > 0);

    const cJSON* tool = nullptr;
    cJSON_ArrayForEach(tool, tools) {
        CHECK(cJSON_IsString(field(tool, "name")));
        CHECK(cJSON_IsString(field(tool, "description")));
        CHECK(cJSON_IsObject(field(tool, "inputSchema")));
    }

    cJSON_Delete(tools);
}

TEST_CASE("probe engine tool schema does not require binary arguments") {
    cJSON* tools = aura_mcp_tools_list_json();
    REQUIRE(cJSON_IsArray(tools));

    const cJSON* probe_tool = toolNamed(tools, "aura_probe_engines");
    REQUIRE(probe_tool != nullptr);

    const cJSON* schema = field(probe_tool, "inputSchema");
    REQUIRE(cJSON_IsObject(schema));
    CHECK(stringField(schema, "type") == "object");
    const cJSON* required = field(schema, "required");
    REQUIRE(cJSON_IsArray(required));
    CHECK(cJSON_GetArraySize(required) == 0);

    cJSON_Delete(tools);
}

TEST_CASE("mcp tool schemas declare expected required arguments") {
    cJSON* tools = aura_mcp_tools_list_json();
    REQUIRE(cJSON_IsArray(tools));

    const cJSON* info_schema = field(toolNamed(tools, "aura_info"),
                                     "inputSchema");
    REQUIRE(cJSON_IsObject(info_schema));
    const cJSON* info_required = field(info_schema, "required");
    REQUIRE(cJSON_IsArray(info_required));
    CHECK(arrayHasString(info_required, "binary_path"));
    CHECK(cJSON_IsFalse(field(info_schema, "additionalProperties")));

    const cJSON* disassembly_schema =
        field(toolNamed(tools, "aura_get_disassembly"), "inputSchema");
    REQUIRE(cJSON_IsObject(disassembly_schema));
    const cJSON* disassembly_required =
        field(disassembly_schema, "required");
    REQUIRE(cJSON_IsArray(disassembly_required));
    CHECK(arrayHasString(disassembly_required, "binary_path"));
    CHECK(arrayHasString(disassembly_required, "function_addr"));
    CHECK(cJSON_IsFalse(field(disassembly_schema, "additionalProperties")));

    cJSON_Delete(tools);
}

TEST_CASE("raw mcp tools are denied by default") {
    cJSON* env =
        aura_mcp_call_tool_json("aura_get_raw_disassembly", nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(errorCode(env) == "raw_access_denied");
    cJSON_Delete(env);

    env = aura_mcp_call_tool_json("aura_get_raw_decompile", nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(errorCode(env) == "raw_access_denied");
    cJSON_Delete(env);
}

TEST_CASE("mcp tool dispatch does not take ownership of caller args") {
    cJSON* args = cJSON_CreateObject();
    REQUIRE(args != nullptr);
    REQUIRE(cJSON_AddStringToObject(args, "unused", "sample.bin") !=
            nullptr);

    cJSON* env = aura_mcp_call_tool_json("aura_analyze", args);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(errorCode(env) == "invalid_arguments");
    cJSON_Delete(env);

    CHECK(cJSON_IsObject(args));
    CHECK(stringField(args, "unused") == "sample.bin");
    cJSON_Delete(args);
}

TEST_CASE("protected export record masks sensitive strings without raw content") {
    ScopedSafetyAssets safety_assets;

    const auto record = aura::safety::buildProtectedExportRecord(
        7, "support alice.smith@example.com", "cli.analyze.strings");

    CHECK(record.string_id == 7);
    CHECK(record.source == "cli.analyze.strings");
    CHECK(record.protected_value == "support [EMAIL_1]");
    CHECK(record.masked_content == "support [EMAIL_1]");
    CHECK(record.findings_count == 1);
    REQUIRE(record.findings.size() == 1);
    CHECK_FALSE(record.findings[0].detector_id.empty());
    CHECK(record.findings[0].kind == "email");
    CHECK(record.findings[0].start == 8);
    CHECK(record.findings[0].end == 31);
    CHECK(record.findings[0].confidence > 0.0);
    CHECK(record.findings[0].mask_token == "[EMAIL_1]");
}

TEST_CASE("analyze CLI JSON normalization protects body strings") {
    ScopedSafetyAssets safety_assets;

    cJSON* root = cJSON_Parse(R"({
      "ok": true,
      "body": {
        "strings": [
          {
            "id": 1,
            "source": "rizin",
            "content": "admin@example.com",
            "raw_content": "admin@example.com",
            "original": "admin@example.com",
            "export_value": "admin@example.com"
          },
          {
            "string_id": 2,
            "content": "plain menu label",
            "raw_content": "plain menu label",
            "original": "plain menu label",
            "export_value": "plain menu label"
          },
          {"id": 3, "content": 42}
        ]
      }
    })");
    REQUIRE(root != nullptr);

    aura_mcp_normalize_analyze_cli_json(root);

    const cJSON* body = field(root, "body");
    REQUIRE(cJSON_IsObject(body));
    const cJSON* strings = field(body, "strings");
    REQUIRE(cJSON_IsArray(strings));

    const cJSON* sensitive = cJSON_GetArrayItem(strings, 0);
    REQUIRE(cJSON_IsObject(sensitive));
    CHECK(field(sensitive, "content") == nullptr);
    CHECK(field(sensitive, "raw_content") == nullptr);
    CHECK(field(sensitive, "original") == nullptr);
    CHECK(field(sensitive, "export_value") == nullptr);
    CHECK(stringField(sensitive, "protected_value") == "[EMAIL_1]");
    CHECK(stringField(sensitive, "masked_content") == "[EMAIL_1]");
    CHECK(cJSON_IsTrue(field(sensitive, "protected_only")));
    const cJSON* sensitive_findings = field(sensitive, "findings");
    REQUIRE(cJSON_IsArray(sensitive_findings));
    REQUIRE(cJSON_GetArraySize(sensitive_findings) == 1);
    const cJSON* finding = cJSON_GetArrayItem(sensitive_findings, 0);
    REQUIRE(cJSON_IsObject(finding));
    CHECK_FALSE(stringField(finding, "detector_id").empty());
    CHECK(stringField(finding, "kind") == "email");
    CHECK(stringField(finding, "mask_token") == "[EMAIL_1]");

    const cJSON* plain = cJSON_GetArrayItem(strings, 1);
    REQUIRE(cJSON_IsObject(plain));
    CHECK(field(plain, "content") == nullptr);
    CHECK(field(plain, "raw_content") == nullptr);
    CHECK(field(plain, "original") == nullptr);
    CHECK(field(plain, "export_value") == nullptr);
    CHECK(stringField(plain, "protected_value") == "plain menu label");
    CHECK(stringField(plain, "masked_content") == "plain menu label");
    CHECK(cJSON_IsTrue(field(plain, "protected_only")));
    const cJSON* plain_findings = field(plain, "findings");
    REQUIRE(cJSON_IsArray(plain_findings));
    CHECK(cJSON_GetArraySize(plain_findings) == 0);

    const cJSON* non_string = cJSON_GetArrayItem(strings, 2);
    REQUIRE(cJSON_IsObject(non_string));
    CHECK(field(non_string, "content") != nullptr);
    CHECK(field(non_string, "protected_value") == nullptr);

    cJSON_Delete(root);
}

TEST_CASE("analyze CLI JSON normalization leaves payload without strings unchanged") {
    cJSON* root = cJSON_Parse(R"({"ok": true, "body": {"functions": []}})");
    REQUIRE(root != nullptr);

    aura_mcp_normalize_analyze_cli_json(root);

    const cJSON* body = field(root, "body");
    REQUIRE(cJSON_IsObject(body));
    CHECK(field(body, "functions") != nullptr);
    CHECK(field(body, "strings") == nullptr);

    cJSON_Delete(root);
}

TEST_CASE("bridged protected mcp tool validates missing arguments") {
    cJSON* env = aura_mcp_call_tool_json("aura_analyze", nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(errorCode(env) == "invalid_arguments");
    cJSON_Delete(env);
}

TEST_CASE("unimplemented function list tool is not advertised or callable") {
    cJSON* tools = aura_mcp_tools_list_json();
    REQUIRE(cJSON_IsArray(tools));
    CHECK_FALSE(hasToolNamed(tools, "aura_list_functions"));
    cJSON_Delete(tools);

    cJSON* env = aura_mcp_call_tool_json("aura_list_functions", nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(stringField(env, "disclosure") == "protected");
    CHECK(errorCode(env) == "tool_not_found");
    cJSON_Delete(env);
}

TEST_CASE("unknown and null mcp tool names are not found") {
    cJSON* env = aura_mcp_call_tool_json("aura_missing", nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(errorCode(env) == "tool_not_found");
    cJSON_Delete(env);

    env = aura_mcp_call_tool_json(nullptr, nullptr);
    REQUIRE(env != nullptr);
    CHECK(aura_mcp_envelope_is_valid(env) == 1);
    CHECK(stringField(env, "status") == "error");
    CHECK(errorCode(env) == "tool_not_found");
    cJSON_Delete(env);
}
