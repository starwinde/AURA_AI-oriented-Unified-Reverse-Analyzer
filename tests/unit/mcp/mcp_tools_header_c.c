#include "mcp_tools.h"

cJSON* aura_mcp_tools_header_c_smoke(cJSON* args) {
    return aura_mcp_call_tool_json("aura_analyze", args);
}
