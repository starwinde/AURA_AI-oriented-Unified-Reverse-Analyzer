#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

extern "C" {
#include "cJSON.h"
}

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

std::string tempInputPath() {
    const char* tmp = std::getenv("TEMP");
    if (tmp == nullptr) {
        tmp = std::getenv("TMPDIR");
    }
    const std::string dir = tmp != nullptr ? tmp : ".";
#ifdef _WIN32
    return dir + "\\aura_mcp_smoke_input.jsonl";
#else
    return dir + "/aura_mcp_smoke_input.jsonl";
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

}  // namespace

TEST_CASE("aura-mcp initializes, lists tools, and denies raw calls") {
    const char* exe_env = std::getenv("AURA_MCP_BIN");
    REQUIRE(exe_env != nullptr);

    const std::string input_path = tempInputPath();
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

#ifdef _WIN32
    const std::string cmd =
        "type " + quotePath(input_path) + " | " + quotePath(exe_env);
#else
    const std::string cmd = quotePath(exe_env) + " < " + quotePath(input_path);
#endif
    const std::string out = runCommand(cmd);
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
