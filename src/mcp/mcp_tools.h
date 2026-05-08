#pragma once

extern "C" {
struct cJSON;

cJSON* aura_mcp_tools_list_json();
cJSON* aura_mcp_call_tool_json(const char* name, cJSON* args_or_null);
}
