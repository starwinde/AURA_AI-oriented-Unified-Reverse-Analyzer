#ifndef AURA_MCP_MCP_ENVELOPE_H
#define AURA_MCP_MCP_ENVELOPE_H

#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

cJSON* aura_mcp_envelope_success(const char* tool_schema_version,
                                 const char* kind,
                                 cJSON*      data_or_null,
                                 const char* disclosure);

cJSON* aura_mcp_envelope_error(const char* tool_schema_version,
                               const char* kind,
                               const char* code,
                               const char* message,
                               const char* disclosure);

cJSON* aura_mcp_envelope_add_warning(cJSON* envelope, const char* warning);

int aura_mcp_envelope_is_valid(const cJSON* envelope);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* AURA_MCP_MCP_ENVELOPE_H */
