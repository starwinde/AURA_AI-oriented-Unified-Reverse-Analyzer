#include "mcp_tools.h"

#include "aura/mcp/mcp_envelope.h"
#include "mcp_cli_bridge.h"

extern "C" {
#include "cJSON.h"
}

#include <cstdlib>
#include <cstring>
#include <string>

namespace {

struct ToolSpec {
    const char* name;
    const char* description;
    const char* const* required_fields;
    int required_count;
    const char* const* optional_fields = nullptr;
    int optional_count = 0;
};

constexpr const char* kBinaryPathFields[] = {"binary_path"};
constexpr const char* kFunctionFields[] = {"binary_path", "function_addr"};
constexpr const char* kGuiAuthFields[] = {"gui_port", "gui_token"};
constexpr const char* kGuiBinaryFields[] = {
    "gui_port", "gui_token", "binary_path"};
constexpr const char* kGuiFunctionFields[] = {
    "gui_port", "gui_token", "function_addr"};
constexpr const char* kGuiRenameFields[] = {
    "gui_port", "gui_token", "function_row", "new_name",
    "confirm_mutation"};
constexpr const char* kGuiResetNameFields[] = {
    "gui_port", "gui_token", "function_row", "confirm_mutation"};
constexpr const char* kGuiAnalyzeOptionalFields[] = {"row", "level"};

constexpr ToolSpec kTools[] = {
    {"aura_probe_engines", "Probe available AURA reverse-engineering engines.",
     nullptr, 0},
    {"aura_info", "Return protected binary fingerprint and format metadata.",
     kBinaryPathFields, 1},
    {"aura_analyze", "Return bounded protected analysis records.",
     kBinaryPathFields, 1},
    {"aura_get_disassembly",
     "Return protected structured disassembly for one function.",
     kFunctionFields, 2},
    {"aura_get_cfg", "Return protected CFG blocks and edges for one function.",
     kFunctionFields, 2},
    {"aura_get_llm_context",
     "Return protected LLM context for one function.", kFunctionFields, 2},
    {"aura_get_gateway_snapshot",
     "Return the protected AURA Gateway snapshot used for LLM pre-send review. The output excludes raw protected values and includes policy decisions, verification status, and audit events.",
     nullptr, 0, kBinaryPathFields, 1},
    {"aura_get_raw_disassembly",
     "Denied by default; raw disassembly requires a future approval flow.",
     kFunctionFields, 2},
    {"aura_get_raw_decompile",
     "Denied by default; raw decompile requires a future approval flow.",
     kFunctionFields, 2},
    {"aura_gui_status",
     "Query a running foreground AURA GUI status via localhost RPC.",
     kGuiAuthFields, 2},
    {"aura_gui_add_binary",
     "Add a binary to the running foreground AURA GUI project.",
     kGuiBinaryFields, 3},
    {"aura_gui_analyze",
     "Run analysis in the running foreground AURA GUI.",
     kGuiAuthFields, 2, kGuiAnalyzeOptionalFields, 2},
    {"aura_gui_functions",
     "List functions from the running foreground AURA GUI.",
     kGuiAuthFields, 2},
    {"aura_gui_demo_snapshot",
     "Return a third-party-safe minimal snapshot from the foreground AURA GUI; output includes comments_total, comments_included, comments_sent, variable_overrides_total, variable_overrides_sent, protected_only, raw_comment_text_omitted, raw_alias_omitted, and raw_type_omitted with raw user text omitted.",
     kGuiAuthFields, 2},
    {"aura_gui_protected_strings",
     "List LLM/MCP-safe protected strings from the running foreground AURA GUI.",
     kGuiAuthFields, 2},
    {"aura_gui_symbols",
     "List symbols from the running foreground AURA GUI.",
     kGuiAuthFields, 2},
    {"aura_gui_xrefs",
     "List xrefs from the running foreground AURA GUI.",
     kGuiAuthFields, 2},
    {"aura_gui_disasm_function",
     "Return protected GUI disassembly for one function address.",
     kGuiFunctionFields, 3},
    {"aura_gui_cfg_function",
     "Return protected GUI CFG for one function address.",
     kGuiFunctionFields, 3},
    {"aura_gui_rename",
     "Rename a function row in the running foreground AURA GUI.",
     kGuiRenameFields, 5},
    {"aura_gui_reset_name",
     "Reset a function row name in the running foreground AURA GUI.",
     kGuiResetNameFields, 4},
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

bool isGuiTool(const char* name) {
    return name != nullptr && std::strncmp(name, "aura_gui_", 9) == 0;
}

bool isGuiMutationTool(const char* name) {
    return streq(name, "aura_gui_rename") ||
           streq(name, "aura_gui_reset_name");
}

bool envHasValue(const char* name) {
    const char* value = std::getenv(name);
    return value != nullptr && value[0] != '\0';
}

const char* fieldType(const char* field);

bool fieldValueMatchesType(cJSON* value, const char* field) {
    const char* type = fieldType(field);
    if (streq(type, "boolean")) {
        return cJSON_IsBool(value);
    }
    if (streq(type, "integer")) {
        return cJSON_IsNumber(value);
    }
    if (cJSON_IsString(value)) {
        return value->valuestring != nullptr && value->valuestring[0] != '\0';
    }
    return false;
}

bool fieldPresent(cJSON* args_or_null, const char* field) {
    cJSON* value = cJSON_GetObjectItemCaseSensitive(args_or_null, field);
    if (value == nullptr) {
        if (streq(field, "gui_port")) {
            return envHasValue("AURA_GUI_RPC_PORT");
        }
        if (streq(field, "gui_token")) {
            return envHasValue("AURA_GUI_RPC_TOKEN");
        }
        return false;
    }
    return fieldValueMatchesType(value, field);
}

bool argsHaveRequiredFields(cJSON* args_or_null,
                            const ToolSpec& tool,
                            const char** missing_field) {
    if (missing_field != nullptr) {
        *missing_field = nullptr;
    }
    if (tool.required_fields == nullptr || tool.required_count == 0) {
        return true;
    }
    if (!cJSON_IsObject(args_or_null)) {
        if (missing_field != nullptr) {
            *missing_field = tool.required_fields[0];
        }
        return false;
    }
    for (int i = 0; i < tool.required_count; ++i) {
        const char* field = tool.required_fields[i];
        if (!fieldPresent(args_or_null, field)) {
            if (missing_field != nullptr) {
                *missing_field = field;
            }
            return false;
        }
    }
    return true;
}

bool confirmMutationIsTrue(cJSON* args_or_null) {
    cJSON* value =
        cJSON_GetObjectItemCaseSensitive(args_or_null, "confirm_mutation");
    if (cJSON_IsTrue(value)) {
        return true;
    }
    return cJSON_IsString(value) && value->valuestring != nullptr &&
           std::strcmp(value->valuestring, "true") == 0;
}

cJSON* createProperty(const char* type, const char* description) {
    cJSON* property = cJSON_CreateObject();
    if (property == nullptr) {
        return nullptr;
    }

    if (cJSON_AddStringToObject(property, "type", type) == nullptr ||
        cJSON_AddStringToObject(property, "description", description) ==
            nullptr) {
        cJSON_Delete(property);
        return nullptr;
    }
    return property;
}

const char* fieldDescription(const char* field) {
    if (streq(field, "binary_path")) {
        return "Path to an allowlisted binary.";
    }
    if (streq(field, "function_addr")) {
        return "Function address.";
    }
    if (streq(field, "gui_port")) {
        return "AURA GUI RPC port.";
    }
    if (streq(field, "gui_token")) {
        return "AURA GUI RPC token.";
    }
    if (streq(field, "function_row")) {
        return "Function table row.";
    }
    if (streq(field, "new_name")) {
        return "New function display name.";
    }
    if (streq(field, "confirm_mutation")) {
        return "Must be true for GUI mutation tools.";
    }
    if (streq(field, "row")) {
        return "Project binary row, default 0.";
    }
    if (streq(field, "level")) {
        return "Analysis level: quick, full, or advanced.";
    }
    return "Tool argument.";
}

const char* fieldType(const char* field) {
    if (streq(field, "confirm_mutation")) {
        return "boolean";
    }
    if (streq(field, "function_row") || streq(field, "row")) {
        return "integer";
    }
    return "string";
}

bool addSchemaProperty(cJSON* properties, const char* field) {
    cJSON* property = createProperty(fieldType(field), fieldDescription(field));
    if (property == nullptr) {
        return false;
    }
    if (!cJSON_AddItemToObject(properties, field, property)) {
        cJSON_Delete(property);
        return false;
    }
    return true;
}

cJSON* createInputSchema(const char* const* required_fields,
                         int required_count,
                         const char* const* optional_fields,
                         int optional_count) {
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
            cJSON* required_item = cJSON_CreateString(field);
            if (required_item == nullptr) {
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
            if (!addSchemaProperty(properties, field)) {
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
            if (!cJSON_AddItemToArray(required, required_item)) {
                cJSON_Delete(required_item);
                cJSON_Delete(schema);
                cJSON_Delete(properties);
                cJSON_Delete(required);
                return nullptr;
            }
        }
    }
    if (optional_fields != nullptr) {
        for (int i = 0; i < optional_count; ++i) {
            if (!addSchemaProperty(properties, optional_fields[i])) {
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
        createInputSchema(spec.required_fields,
                          spec.required_count,
                          spec.optional_fields,
                          spec.optional_count);
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

    const char* missing_field = nullptr;
    if (!argsHaveRequiredFields(args_or_null, *tool, &missing_field)) {
        std::string message = "missing required argument: ";
        message += missing_field != nullptr ? missing_field : "unknown";
        return aura_mcp_envelope_error("protected/1.0",
                                       tool->name,
                                       "invalid_arguments",
                                       message.c_str(),
                                       "protected");
    }

    if (isGuiMutationTool(name) && !confirmMutationIsTrue(args_or_null)) {
        return aura_mcp_envelope_error("protected/1.0",
                                       tool->name,
                                       "mutation_not_confirmed",
                                       "GUI mutation tools require confirm_mutation:true",
                                       "protected");
    }

    if (streq(name, "aura_probe_engines") || streq(name, "aura_info") ||
        streq(name, "aura_analyze") ||
        streq(name, "aura_get_disassembly") ||
        streq(name, "aura_get_cfg") ||
        streq(name, "aura_get_llm_context") ||
        streq(name, "aura_get_gateway_snapshot")) {
        return aura_mcp_cli_bridge_call_json(name, args_or_null);
    }

    if (isGuiTool(name)) {
        return aura_mcp_cli_bridge_gui_call_json(name, args_or_null);
    }

    return aura_mcp_envelope_error("protected/1.0",
                                   tool->name,
                                   "tool_not_implemented",
                                   "MCP tool dispatch is not implemented yet",
                                   "protected");
}
