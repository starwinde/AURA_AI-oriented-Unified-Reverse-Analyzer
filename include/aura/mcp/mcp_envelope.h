#ifndef AURA_MCP_MCP_ENVELOPE_H
#define AURA_MCP_MCP_ENVELOPE_H

#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

cJSON* aura_mcp_envelope_success(const char* kind,
                                 const char* tool_schema_version,
                                 const char* disclosure,
                                 cJSON*      data_or_null);

cJSON* aura_mcp_envelope_error(const char* kind,
                               const char* tool_schema_version,
                               const char* code,
                               const char* message);

cJSON* aura_mcp_envelope_add_warning(cJSON* envelope, const char* warning);

int aura_mcp_envelope_is_valid(const cJSON* envelope);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* AURA_MCP_MCP_ENVELOPE_H */
