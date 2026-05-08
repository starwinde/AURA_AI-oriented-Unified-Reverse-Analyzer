#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

extern "C" {
#include "cJSON.h"
}

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace {

namespace fs = std::filesystem;

std::string quotePath(const std::string& path) {
#ifdef _WIN32
    std::string escaped;
    escaped.reserve(path.size());
    for (const char ch : path) {
        if (ch == '"') {
            escaped += "\\\"";
        } else {
            escaped += ch;
        }
    }
    return "\"" + escaped + "\"";
#else
    std::string escaped = "'";
    for (const char ch : path) {
        if (ch == '\'') {
            escaped += "'\\''";
        } else {
            escaped += ch;
        }
    }
    escaped += "'";
    return escaped;
#endif
}

std::string tempInputPath(const char* suffix) {
    const char* tmp = std::getenv("TEMP");
    if (tmp == nullptr) {
        tmp = std::getenv("TMPDIR");
    }
    const std::string dir = tmp != nullptr ? tmp : ".";
    const auto ticks = std::chrono::high_resolution_clock::now()
                           .time_since_epoch()
                           .count();
#ifdef _WIN32
    return dir + "\\aura_mcp_smoke_" + suffix + "_" +
           std::to_string(ticks) + ".jsonl";
#else
    return dir + "/aura_mcp_smoke_" + suffix + "_" + std::to_string(ticks) +
           ".jsonl";
#endif
}

std::string runCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    REQUIRE(pipe != nullptr);

    std::string out;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        out += buffer;
    }
    const int rc = pclose(pipe);
    CHECK(rc == 0);
    return out;
}

void setEnvVar(const char* name, const std::string& value) {
#ifdef _WIN32
    _putenv_s(name, value.c_str());
#else
    setenv(name, value.c_str(), 1);
#endif
}

void unsetEnvVar(const char* name) {
#ifdef _WIN32
    _putenv_s(name, "");
#else
    unsetenv(name);
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

fs::path findRepoRoot() {
    fs::path cur = fs::current_path();
    for (;;) {
        if (fs::exists(cur / "tests" / "fixtures" / "bin" /
                       "elf_smoke.x86_64")) {
            return cur;
        }
        if (!cur.has_parent_path() || cur == cur.parent_path()) {
            break;
        }
        cur = cur.parent_path();
    }
    return {};
}

bool cliLooksAvailable(const fs::path& repo_root) {
#ifdef _WIN32
    return fs::exists(repo_root / "build-trim-gui" / "src" / "cli" /
                      "Release" / "aura.exe");
#else
    return fs::exists(repo_root / "build-trim-gui" / "src" / "cli" /
                      "aura");
#endif
}

cJSON* parseLine(const std::string& text, int line_index) {
    size_t pos = 0;
    for (int i = 0; i < line_index; ++i) {
        pos = text.find('\n', pos);
        REQUIRE(pos != std::string::npos);
        ++pos;
    }
    const size_t end = text.find('\n', pos);
    const std::string line =
        text.substr(pos, end == std::string::npos ? std::string::npos
                                                  : end - pos);
    cJSON* parsed = cJSON_ParseWithLength(line.data(), line.size());
    REQUIRE(parsed != nullptr);
    return parsed;
}

int responseLineCount(const std::string& text) {
    if (text.empty()) {
        return 0;
    }

    int count = 0;
    size_t pos = 0;
    while (pos < text.size()) {
        const size_t end = text.find('\n', pos);
        const std::string line =
            text.substr(pos, end == std::string::npos ? std::string::npos
                                                      : end - pos);
        if (!line.empty()) {
            ++count;
        }
        if (end == std::string::npos) {
            break;
        }
        pos = end + 1;
    }
    return count;
}

const cJSON* resultOf(const cJSON* response) {
    const cJSON* result = cJSON_GetObjectItemCaseSensitive(response, "result");
    REQUIRE(cJSON_IsObject(result));
    return result;
}

const cJSON* contentTextOf(const cJSON* result) {
    const cJSON* content =
        cJSON_GetObjectItemCaseSensitive(result, "content");
    REQUIRE(cJSON_IsArray(content));
    const cJSON* item = cJSON_GetArrayItem(content, 0);
    REQUIRE(cJSON_IsObject(item));
    const cJSON* text = cJSON_GetObjectItemCaseSensitive(item, "text");
    REQUIRE(cJSON_IsString(text));
    return text;
}

std::string optionalStringField(const cJSON* object, const char* name) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, name);
    return cJSON_IsString(item) && item->valuestring != nullptr
               ? item->valuestring
               : "";
}

bool jsonTreeHasKey(const cJSON* item, const char* key) {
    if (item == nullptr || key == nullptr) {
        return false;
    }
    if (cJSON_IsObject(item)) {
        const cJSON* child = item->child;
        while (child != nullptr) {
            if (child->string != nullptr && std::string(child->string) == key) {
                return true;
            }
            if (jsonTreeHasKey(child, key)) {
                return true;
            }
            child = child->next;
        }
        return false;
    }
    if (cJSON_IsArray(item)) {
        const cJSON* child = item->child;
        while (child != nullptr) {
            if (jsonTreeHasKey(child, key)) {
                return true;
            }
            child = child->next;
        }
    }
    return false;
}

cJSON* envelopeFromCallResponse(const cJSON* response) {
    const cJSON* text = contentTextOf(resultOf(response));
    REQUIRE(text->valuestring != nullptr);
    cJSON* envelope = cJSON_Parse(text->valuestring);
    REQUIRE(envelope != nullptr);
    return envelope;
}

void checkProtectedOkEnvelope(const cJSON* envelope, const char* kind) {
    CHECK(optionalStringField(envelope, "status") == "ok");
    CHECK(optionalStringField(envelope, "kind") == kind);
    CHECK(optionalStringField(envelope, "disclosure") == "protected");

    const cJSON* data =
        cJSON_GetObjectItemCaseSensitive(envelope, "data");
    REQUIRE(cJSON_IsObject(data));
    const cJSON* aura_cli =
        cJSON_GetObjectItemCaseSensitive(data, "aura_cli");
    REQUIRE(cJSON_IsObject(aura_cli));
}

const cJSON* auraCliOf(const cJSON* envelope) {
    const cJSON* data =
        cJSON_GetObjectItemCaseSensitive(envelope, "data");
    REQUIRE(cJSON_IsObject(data));
    const cJSON* aura_cli =
        cJSON_GetObjectItemCaseSensitive(data, "aura_cli");
    REQUIRE(cJSON_IsObject(aura_cli));
    return aura_cli;
}

void checkJsonRpcError(const cJSON* response,
                       int          expected_code,
                       bool         expect_null_id) {
    REQUIRE(cJSON_IsObject(response));
    const cJSON* error = cJSON_GetObjectItemCaseSensitive(response, "error");
    REQUIRE(cJSON_IsObject(error));

    const cJSON* code = cJSON_GetObjectItemCaseSensitive(error, "code");
    REQUIRE(cJSON_IsNumber(code));
    CHECK(code->valueint == expected_code);

    const cJSON* id = cJSON_GetObjectItemCaseSensitive(response, "id");
    if (expect_null_id) {
        CHECK(cJSON_IsNull(id));
    } else {
        CHECK(!cJSON_IsNull(id));
    }
}

std::string runMcpWithInput(const std::string& exe,
                            const std::string& input_path) {
#ifdef _WIN32
    const std::string cmd =
        "type " + quotePath(input_path) + " | " + quotePath(exe);
#else
    const std::string cmd = quotePath(exe) + " < " + quotePath(input_path);
#endif
    return runCommand(cmd);
}

}  // namespace

TEST_CASE("aura-mcp initializes, lists tools, and denies raw calls") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath("basic");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"initialize\","
                 "\"params\":{\"protocolVersion\":\"2025-06-18\","
                 "\"capabilities\":{},\"clientInfo\":{\"name\":\"aura-test\","
                 "\"version\":\"1\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"notifications/"
                 "initialized\",\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"tools/list\","
                 "\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":3,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_raw_disassembly\","
                 "\"arguments\":{\"binary_path\":\"tests/fixtures/bin/"
                 "elf_smoke.x86_64\",\"function_addr\":\"0x40117b\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("\"id\":1") != std::string::npos);
    CHECK(out.find("\"id\":2") != std::string::npos);
    CHECK(out.find("\"id\":3") != std::string::npos);
    CHECK(out.find("notifications") == std::string::npos);

    cJSON* initialize = parseLine(out, 0);
    cJSON* tools_list = parseLine(out, 1);
    cJSON* raw_call = parseLine(out, 2);

    const cJSON* init_result = resultOf(initialize);
    CHECK(cJSON_IsString(cJSON_GetObjectItemCaseSensitive(
        init_result, "protocolVersion")));
    CHECK(cJSON_IsObject(cJSON_GetObjectItemCaseSensitive(
        init_result, "capabilities")));
    CHECK(cJSON_IsObject(cJSON_GetObjectItemCaseSensitive(
        init_result, "serverInfo")));

    const cJSON* tools_result = resultOf(tools_list);
    const cJSON* tools =
        cJSON_GetObjectItemCaseSensitive(tools_result, "tools");
    REQUIRE(cJSON_IsArray(tools));
    CHECK(out.find("aura_probe_engines") != std::string::npos);
    CHECK(out.find("aura_get_raw_disassembly") != std::string::npos);

    const cJSON* call_result = resultOf(raw_call);
    const cJSON* is_error =
        cJSON_GetObjectItemCaseSensitive(call_result, "isError");
    CHECK(cJSON_IsTrue(is_error));
    const cJSON* text = contentTextOf(call_result);
    REQUIRE(text->valuestring != nullptr);
    const std::string envelope_text = text->valuestring;
    CHECK(envelope_text.find("raw_access_denied") != std::string::npos);
    CHECK(envelope_text.find("\"status\":\"error\"") != std::string::npos);

    cJSON_Delete(initialize);
    cJSON_Delete(tools_list);
    cJSON_Delete(raw_call);
    std::remove(input_path.c_str());
}

TEST_CASE("aura-mcp validates request envelopes and suppresses notifications") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath("validation");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "not-json\n";
        input << "{\"id\":10,\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"tools/list\","
                 "\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"notifications/"
                 "cancelled\",\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"unknown/method\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":{\"bad\":true},"
                 "\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":[1],\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":true,\"method\":\"ping\"}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(responseLineCount(out) == 5);
    CHECK(out.find("\"id\":10") != std::string::npos);
    CHECK(out.find("\"code\":-32600") != std::string::npos);
    CHECK(out.find("\"code\":-32700") != std::string::npos);
    CHECK(out.find("\"id\":null") != std::string::npos);
    CHECK(out.find("\"result\"") == std::string::npos);
    CHECK(out.find("tools") == std::string::npos);
    CHECK(out.find("cancelled") == std::string::npos);
    CHECK(out.find("unknown/method") == std::string::npos);

    cJSON* parse_error = parseLine(out, 0);
    cJSON* missing_jsonrpc = parseLine(out, 1);
    cJSON* invalid_id_object = parseLine(out, 2);
    cJSON* invalid_id_array = parseLine(out, 3);
    cJSON* invalid_id_bool = parseLine(out, 4);

    checkJsonRpcError(parse_error, -32700, true);
    checkJsonRpcError(missing_jsonrpc, -32600, false);
    checkJsonRpcError(invalid_id_object, -32600, true);
    checkJsonRpcError(invalid_id_array, -32600, true);
    checkJsonRpcError(invalid_id_bool, -32600, true);

    const cJSON* missing_id =
        cJSON_GetObjectItemCaseSensitive(missing_jsonrpc, "id");
    REQUIRE(cJSON_IsNumber(missing_id));
    CHECK(missing_id->valueint == 10);

    cJSON_Delete(parse_error);
    cJSON_Delete(missing_jsonrpc);
    cJSON_Delete(invalid_id_object);
    cJSON_Delete(invalid_id_array);
    cJSON_Delete(invalid_id_bool);
    std::remove(input_path.c_str());
}

TEST_CASE("aura_info fails closed when allowed roots are missing") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);
    ScopedEnvVar repo_root_env("AURA_REPO_ROOT");
    ScopedEnvVar allowed_roots_env("AURA_MCP_ALLOWED_ROOTS");

    const fs::path repo_root = findRepoRoot();
    REQUIRE(!repo_root.empty());
    const fs::path fixture =
        repo_root / "tests" / "fixtures" / "bin" / "elf_smoke.x86_64";
    REQUIRE(fs::exists(fixture));

    unsetEnvVar("AURA_MCP_ALLOWED_ROOTS");
    setEnvVar("AURA_REPO_ROOT", repo_root.string());

    const std::string input_path = tempInputPath("no_allowed_roots");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":20,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_info\",\"arguments\":"
              << "{\"binary_path\":\"" << fixture.generic_string()
              << "\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("\"id\":20") != std::string::npos);
    CHECK(out.find("no_allowed_roots") != std::string::npos);
    CHECK(out.find("\\\"status\\\":\\\"error\\\"") != std::string::npos);

    std::remove(input_path.c_str());
}

TEST_CASE("aura-mcp bridges probe, info, and analyze through aura CLI") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);
    ScopedEnvVar repo_root_env("AURA_REPO_ROOT");
    ScopedEnvVar allowed_roots_env("AURA_MCP_ALLOWED_ROOTS");

    const fs::path repo_root = findRepoRoot();
    REQUIRE(!repo_root.empty());
    REQUIRE(cliLooksAvailable(repo_root));

    const fs::path fixture =
        repo_root / "tests" / "fixtures" / "bin" / "elf_smoke.x86_64";
    REQUIRE(fs::exists(fixture));

    setEnvVar("AURA_REPO_ROOT", repo_root.string());
    setEnvVar("AURA_MCP_ALLOWED_ROOTS", repo_root.string());

    const std::string input_path = tempInputPath("bridge");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":30,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_probe_engines\","
                 "\"arguments\":{}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":31,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_info\",\"arguments\":"
              << "{\"binary_path\":\"" << fixture.generic_string()
              << "\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":32,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_analyze\",\"arguments\":"
              << "{\"binary_path\":\"" << fixture.generic_string()
              << "\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("\"id\":30") != std::string::npos);
    CHECK(out.find("\"id\":31") != std::string::npos);
    CHECK(out.find("\"id\":32") != std::string::npos);
    CHECK(out.find("mcp_schema_version") != std::string::npos);
    CHECK(out.find("aura_probe_engines") != std::string::npos);
    CHECK(out.find("sha256") != std::string::npos);
    CHECK(out.find("functions") != std::string::npos);
    CHECK(out.find("aura_cli") != std::string::npos);

    cJSON* analyze_response = parseLine(out, 2);
    const cJSON* analyze_text = contentTextOf(resultOf(analyze_response));
    REQUIRE(analyze_text->valuestring != nullptr);
    cJSON* analyze_envelope = cJSON_Parse(analyze_text->valuestring);
    REQUIRE(analyze_envelope != nullptr);
    CHECK(optionalStringField(analyze_envelope, "status") == "ok");
    CHECK(optionalStringField(analyze_envelope, "disclosure") == "protected");

    const cJSON* data =
        cJSON_GetObjectItemCaseSensitive(analyze_envelope, "data");
    REQUIRE(cJSON_IsObject(data));
    const cJSON* aura_cli =
        cJSON_GetObjectItemCaseSensitive(data, "aura_cli");
    REQUIRE(cJSON_IsObject(aura_cli));
    const cJSON* body = cJSON_GetObjectItemCaseSensitive(aura_cli, "body");
    if (cJSON_IsObject(body)) {
        const cJSON* strings =
            cJSON_GetObjectItemCaseSensitive(body, "strings");
        if (cJSON_IsArray(strings)) {
            const cJSON* row = nullptr;
            cJSON_ArrayForEach(row, strings) {
                if (!cJSON_IsObject(row)) {
                    continue;
                }
                CHECK(cJSON_GetObjectItemCaseSensitive(row, "content") ==
                      nullptr);
                CHECK(cJSON_GetObjectItemCaseSensitive(row, "raw_content") ==
                      nullptr);
                CHECK(cJSON_IsString(cJSON_GetObjectItemCaseSensitive(
                    row, "protected_value")));
                CHECK(cJSON_IsString(cJSON_GetObjectItemCaseSensitive(
                    row, "masked_content")));
                CHECK(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(
                    row, "protected_only")));
                CHECK(cJSON_IsArray(cJSON_GetObjectItemCaseSensitive(
                    row, "findings")));
            }
        }
    }

    cJSON_Delete(analyze_envelope);
    cJSON_Delete(analyze_response);
    std::remove(input_path.c_str());
}

TEST_CASE("aura-mcp bridges function detail tools through aura CLI") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);
    ScopedEnvVar repo_root_env("AURA_REPO_ROOT");
    ScopedEnvVar allowed_roots_env("AURA_MCP_ALLOWED_ROOTS");

    const fs::path repo_root = findRepoRoot();
    REQUIRE(!repo_root.empty());
    REQUIRE(cliLooksAvailable(repo_root));

    const fs::path fixture =
        repo_root / "tests" / "fixtures" / "bin" / "elf_smoke.x86_64";
    REQUIRE(fs::exists(fixture));

    setEnvVar("AURA_REPO_ROOT", repo_root.string());
    setEnvVar("AURA_MCP_ALLOWED_ROOTS", repo_root.string());

    const std::string input_path = tempInputPath("function_details");
    {
        std::ofstream input(input_path, std::ios::binary);
        REQUIRE(input.good());
        input << "{\"jsonrpc\":\"2.0\",\"id\":40,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_disassembly\","
                 "\"arguments\":{\"binary_path\":\""
              << fixture.generic_string()
              << "\",\"function_addr\":\"0x40117b\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":41,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_cfg\","
                 "\"arguments\":{\"binary_path\":\""
              << fixture.generic_string()
              << "\",\"function_addr\":\"0x40117b\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":42,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_llm_context\","
                 "\"arguments\":{\"binary_path\":\""
              << fixture.generic_string()
              << "\",\"function_addr\":\"0x40117b\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":43,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_disassembly\","
                 "\"arguments\":{\"binary_path\":\""
              << fixture.generic_string() << "\"}}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":44,\"method\":\"tools/call\","
                 "\"params\":{\"name\":\"aura_get_disassembly\","
                 "\"arguments\":{\"binary_path\":\""
              << fixture.generic_string()
              << "\",\"function_addr\":\"not-an-address\"}}}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(responseLineCount(out) == 5);

    cJSON* disasm_response = parseLine(out, 0);
    cJSON* cfg_response = parseLine(out, 1);
    cJSON* llm_context_response = parseLine(out, 2);
    cJSON* missing_addr_response = parseLine(out, 3);
    cJSON* invalid_addr_response = parseLine(out, 4);

    cJSON* disasm_envelope = envelopeFromCallResponse(disasm_response);
    cJSON* cfg_envelope = envelopeFromCallResponse(cfg_response);
    cJSON* llm_context_envelope = envelopeFromCallResponse(llm_context_response);
    cJSON* missing_addr_envelope =
        envelopeFromCallResponse(missing_addr_response);
    cJSON* invalid_addr_envelope =
        envelopeFromCallResponse(invalid_addr_response);

    checkProtectedOkEnvelope(disasm_envelope, "aura_get_disassembly");
    checkProtectedOkEnvelope(cfg_envelope, "aura_get_cfg");
    checkProtectedOkEnvelope(llm_context_envelope, "aura_get_llm_context");
    CHECK(jsonTreeHasKey(disasm_envelope, "instructions"));
    CHECK(jsonTreeHasKey(cfg_envelope, "blocks"));
    CHECK(jsonTreeHasKey(llm_context_envelope, "callees"));

    const cJSON* disasm_body =
        cJSON_GetObjectItemCaseSensitive(auraCliOf(disasm_envelope), "body");
    REQUIRE(cJSON_IsObject(disasm_body));
    CHECK(cJSON_GetObjectItemCaseSensitive(disasm_body, "text") == nullptr);
    CHECK(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(
        disasm_body, "protected_only")));
    CHECK(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(
        disasm_body, "text_omitted")));
    CHECK(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(
        disasm_body, "op_str_omitted")));

    const cJSON* instructions =
        cJSON_GetObjectItemCaseSensitive(disasm_body, "instructions");
    REQUIRE(cJSON_IsArray(instructions));
    const cJSON* first_instruction = cJSON_GetArrayItem(instructions, 0);
    REQUIRE(cJSON_IsObject(first_instruction));
    CHECK(cJSON_GetObjectItemCaseSensitive(first_instruction, "op_str") ==
          nullptr);
    CHECK(cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(
        first_instruction, "addr")));
    CHECK(cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(
        first_instruction, "size")));
    CHECK(cJSON_IsString(cJSON_GetObjectItemCaseSensitive(
        first_instruction, "mnemonic")));
    CHECK(cJSON_IsObject(cJSON_GetObjectItemCaseSensitive(
        first_instruction, "provenance")));

    CHECK(optionalStringField(missing_addr_envelope, "status") == "error");
    CHECK(optionalStringField(missing_addr_envelope, "kind") ==
          "aura_get_disassembly");
    CHECK(optionalStringField(missing_addr_envelope, "disclosure") ==
          "protected");
    const cJSON* error =
        cJSON_GetObjectItemCaseSensitive(missing_addr_envelope, "error");
    REQUIRE(cJSON_IsObject(error));
    CHECK(optionalStringField(error, "code") == "invalid_arguments");

    CHECK(optionalStringField(invalid_addr_envelope, "status") == "error");
    CHECK(optionalStringField(invalid_addr_envelope, "kind") ==
          "aura_get_disassembly");
    CHECK(optionalStringField(invalid_addr_envelope, "disclosure") ==
          "protected");
    const cJSON* invalid_error =
        cJSON_GetObjectItemCaseSensitive(invalid_addr_envelope, "error");
    REQUIRE(cJSON_IsObject(invalid_error));
    CHECK(optionalStringField(invalid_error, "code") == "cli_failed");

    cJSON_Delete(disasm_envelope);
    cJSON_Delete(cfg_envelope);
    cJSON_Delete(llm_context_envelope);
    cJSON_Delete(missing_addr_envelope);
    cJSON_Delete(invalid_addr_envelope);
    cJSON_Delete(disasm_response);
    cJSON_Delete(cfg_response);
    cJSON_Delete(llm_context_response);
    cJSON_Delete(missing_addr_response);
    cJSON_Delete(invalid_addr_response);
    std::remove(input_path.c_str());
}
