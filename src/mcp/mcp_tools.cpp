#include "mcp_tools.h"

#include "aura/mcp/mcp_envelope.h"

extern "C" {
#include "cJSON.h"
}

#include <cstring>

namespace {

struct ToolSpec {
    const char* name;
    const char* description;
    const char* const* required_fields;
    int required_count;
};

constexpr const char* kBinaryPathFields[] = {"binary_path"};
constexpr const char* kFunctionFields[] = {"binary_path", "function_addr"};

constexpr ToolSpec kTools[] = {
    {"aura_probe_engines", "Probe available AURA reverse-engineering engines.",
     nullptr, 0},
    {"aura_info", "Return protected binary fingerprint and format metadata.",
     kBinaryPathFields, 1},
    {"aura_analyze", "Return bounded protected analysis records.",
     kBinaryPathFields, 1},
    {"aura_list_functions", "List bounded protected function records.",
     kBinaryPathFields, 1},
    {"aura_get_disassembly",
     "Return protected structured disassembly for one function.",
     kFunctionFields, 2},
    {"aura_get_cfg", "Return protected CFG blocks and edges for one function.",
     kFunctionFields, 2},
    {"aura_get_llm_context",
     "Return protected LLM context for one function.", kFunctionFields, 2},
    {"aura_get_raw_disassembly",
     "Denied by default; raw disassembly requires a future approval flow.",
     kFunctionFields, 2},
    {"aura_get_raw_decompile",
     "Denied by default; raw decompile requires a future approval flow.",
     kFunctionFields, 2},
};

bool streq(const char* lhs, const char* rhs) {
    return lhs != nullptr && rhs != nullptr && std::strcmp(lhs, rhs) == 0;
}

const ToolSpec* findTool(const char* name) {
    if (name == nullptr || name[0] == '\0') {
        return nullptr;
    }

    for (const ToolSpec& tool : kTools) {
        if (streq(name, tool.name)) {
            return &tool;
        }
    }
    return nullptr;
}

bool isRawTool(const char* name) {
    return streq(name, "aura_get_raw_disassembly") ||
           streq(name, "aura_get_raw_decompile");
}

cJSON* createStringProperty(const char* description) {
    cJSON* property = cJSON_CreateObject();
    if (property == nullptr) {
        return nullptr;
    }

    if (cJSON_AddStringToObject(property, "type", "string") == nullptr ||
        cJSON_AddStringToObject(property, "description", description) ==
            nullptr) {
        cJSON_Delete(property);
        return nullptr;
    }
    return property;
}

cJSON* createInputSchema(const char* const* required_fields,
                         int required_count) {
    cJSON* schema = cJSON_CreateObject();
    cJSON* properties = cJSON_CreateObject();
    cJSON* required = cJSON_CreateArray();
    if (schema == nullptr || properties == nullptr || required == nullptr) {
        cJSON_Delete(schema);
        cJSON_Delete(properties);
        cJSON_Delete(required);
        return nullptr;
    }

    if (required_fields != nullptr) {
        for (int i = 0; i < required_count; ++i) {
            const char* field = required_fields[i];
            cJSON* property =
                createStringProperty(streq(field, "binary_path")
                                         ? "Path to an allowlisted binary."
                                         : "Function address.");
            cJSON* required_item = cJSON_CreateString(field);
            if (property == nullptr || required_item == nullptr) {
                cJSON_Delete(property);
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
            if (!cJSON_AddItemToObject(properties, field, property)) {
                cJSON_Delete(property);
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
            property = nullptr;
            if (!cJSON_AddItemToArray(required, required_item)) {
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
        }
    }

    if (cJSON_AddStringToObject(schema, "type", "object") == nullptr) {
        cJSON_Delete(schema);
        cJSON_Delete(properties);
        cJSON_Delete(required);
        return nullptr;
    }
    if (!cJSON_AddItemToObject(schema, "properties", properties)) {
        cJSON_Delete(schema);
        cJSON_Delete(properties);
        cJSON_Delete(required);
        return nullptr;
    }
    properties = nullptr;
    if (!cJSON_AddItemToObject(schema, "required", required)) {
        cJSON_Delete(schema);
        cJSON_Delete(properties);
        cJSON_Delete(required);
        return nullptr;
    }
    required = nullptr;
    if (cJSON_AddBoolToObject(schema, "additionalProperties", false) ==
        nullptr) {
        cJSON_Delete(schema);
        return nullptr;
    }
    return schema;
}

bool addTool(cJSON* tools, const ToolSpec& spec) {
    cJSON* tool = cJSON_CreateObject();
    cJSON* schema =
        createInputSchema(spec.required_fields, spec.required_count);
    if (tool == nullptr || schema == nullptr) {
        cJSON_Delete(tool);
        cJSON_Delete(schema);
        return false;
    }

    if (cJSON_AddStringToObject(tool, "name", spec.name) == nullptr ||
        cJSON_AddStringToObject(tool, "description", spec.description) ==
            nullptr) {
        cJSON_Delete(tool);
        cJSON_Delete(schema);
        return false;
    }
    if (!cJSON_AddItemToObject(tool, "inputSchema", schema)) {
        cJSON_Delete(tool);
        cJSON_Delete(schema);
        return false;
    }
    schema = nullptr;
    if (!cJSON_AddItemToArray(tools, tool)) {
        cJSON_Delete(tool);
        return false;
    }
    return true;
}

const char* kindForTool(const char* name) {
    return (name != nullptr && name[0] != '\0') ? name : "unknown";
}

}  // namespace

extern "C" cJSON* aura_mcp_tools_list_json() {
    cJSON* tools = cJSON_CreateArray();
    if (tools == nullptr) {
        return nullptr;
    }

    for (const ToolSpec& tool : kTools) {
        if (!addTool(tools, tool)) {
            cJSON_Delete(tools);
            return nullptr;
        }
    }
    return tools;
}

extern "C" cJSON* aura_mcp_call_tool_json(const char* name,
                                           cJSON*      args_or_null) {
    (void)args_or_null;

    const ToolSpec* tool = findTool(name);
    if (tool == nullptr) {
        return aura_mcp_envelope_error("unknown/1.0",
                                       kindForTool(name),
                                       "tool_not_found",
                                       "MCP tool was not found",
                                       "protected");
    }

    if (isRawTool(name)) {
        return aura_mcp_envelope_error("raw/1.0",
                                       tool->name,
                                       "raw_access_denied",
                                       "Raw MCP tools are disabled by default",
                                       "protected");
    }

    return aura_mcp_envelope_error("protected/1.0",
                                   tool->name,
                                   "tool_not_implemented",
                                   "MCP tool dispatch is not implemented yet",
                                   "protected");
}
