#pragma once

#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

cJSON* aura_mcp_cli_bridge_call_json(const char* tool_name,
                                     cJSON*      args_or_null);

cJSON* aura_mcp_cli_bridge_gui_call_json(const char* tool_name,
                                         cJSON*      args_or_null);

#ifdef __cplusplus
}
#endif
