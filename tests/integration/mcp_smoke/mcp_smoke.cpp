#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

extern "C" {
#include "cJSON.h"
}

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace {

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
        input << "{\"id\":10,\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"ping\"}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"tools/list\","
                 "\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"method\":\"notifications/"
                 "cancelled\",\"params\":{}}\n";
        input << "{\"jsonrpc\":\"2.0\",\"id\":{\"bad\":true},"
                 "\"method\":\"ping\"}\n";
    }

    const std::string out = runMcpWithInput(exe_env, input_path);
    CHECK(out.find("\"id\":10") != std::string::npos);
    CHECK(out.find("\"code\":-32600") != std::string::npos);
    CHECK(out.find("\"id\":null") != std::string::npos);
    CHECK(out.find("\"result\"") == std::string::npos);
    CHECK(out.find("tools") == std::string::npos);
    CHECK(out.find("cancelled") == std::string::npos);

    cJSON* missing_jsonrpc = parseLine(out, 0);
    cJSON* invalid_id = parseLine(out, 1);
    const cJSON* first_error =
        cJSON_GetObjectItemCaseSensitive(missing_jsonrpc, "error");
    REQUIRE(cJSON_IsObject(first_error));
    const cJSON* first_code =
        cJSON_GetObjectItemCaseSensitive(first_error, "code");
    CHECK(cJSON_IsNumber(first_code));
    CHECK(first_code->valueint == -32600);

    const cJSON* invalid_id_value =
        cJSON_GetObjectItemCaseSensitive(invalid_id, "id");
    CHECK(cJSON_IsNull(invalid_id_value));
    const cJSON* second_error =
        cJSON_GetObjectItemCaseSensitive(invalid_id, "error");
    REQUIRE(cJSON_IsObject(second_error));
    const cJSON* second_code =
        cJSON_GetObjectItemCaseSensitive(second_error, "code");
    CHECK(cJSON_IsNumber(second_code));
    CHECK(second_code->valueint == -32600);

    cJSON_Delete(missing_jsonrpc);
    cJSON_Delete(invalid_id);
    std::remove(input_path.c_str());
}
