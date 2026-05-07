// src/engine/probe/probe_registry.c — Phase 2.5 slice 6
//
// Sequential collector. Each per-engine probe is best-effort: a probe
// failure (negative rc) leaves that engine's slot populated with the
// UNKNOWN_ERROR status rather than aborting the whole envelope.

#include "probe_registry.h"

#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "engine_probe.h"
#include "probe_result.h"

typedef int (*probe_fn)(AuraCommandRunner *, AuraProbeResult *);

static cJSON *result_to_json(const AuraProbeResult *r) {
    cJSON *o = cJSON_CreateObject();
    if (!o) return NULL;
    cJSON_AddStringToObject(o, "status", aura_probe_status_str(r->status));
    cJSON_AddStringToObject(o, "engine_id",        r->engine_id);
    cJSON_AddStringToObject(o, "detected_version", r->detected_version);
    cJSON_AddStringToObject(o, "required_runtime", r->required_runtime);
    cJSON_AddStringToObject(o, "install_hint",         r->install_hint);
    cJSON_AddStringToObject(o, "install_hint_linux",   r->install_hint_linux);
    cJSON_AddStringToObject(o, "install_hint_macos",   r->install_hint_macos);
    cJSON_AddStringToObject(o, "install_hint_windows", r->install_hint_windows);
    cJSON_AddStringToObject(o, "raw_diagnostic",       r->raw_diagnostic);
    cJSON_AddNumberToObject(o, "probed_at_ms",
                            (double)r->probed_at_ms);
    return o;
}

int aura_probe_collect_all(AuraCommandRunner *runner, char **out_json) {
    if (!runner || !out_json) return -1;

    static const struct {
        const char *engine_id;
        probe_fn    fn;
    } table[] = {
        { "rizin",         aura_probe_rizin         },
        { "ghidra-decomp", aura_probe_ghidra_decomp },
        { "ghidra-full",   aura_probe_ghidra_full   },
        { "angr",          aura_probe_angr          },
        { "retdec",        aura_probe_retdec        },
    };
    const size_t n = sizeof(table) / sizeof(table[0]);

    cJSON *root = cJSON_CreateObject();
    if (!root) return -2;

    for (size_t i = 0; i < n; ++i) {
        AuraProbeResult r;
        memset(&r, 0, sizeof(r));
        int rc = table[i].fn(runner, &r);
        if (rc != 0) {
            r.status = AURA_PROBE_UNKNOWN_ERROR;
            strncpy(r.engine_id, table[i].engine_id,
                    sizeof(r.engine_id) - 1);
        }
        cJSON *child = result_to_json(&r);
        if (!child) {
            cJSON_Delete(root);
            return -3;
        }
        cJSON_AddItemToObject(root, table[i].engine_id, child);
    }

    char *s = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (!s) return -4;
    *out_json = s;
    return 0;
}
