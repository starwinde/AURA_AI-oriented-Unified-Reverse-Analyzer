# AURA Plugin System Design

> Task 1.5 -- Plugin system C API design
> Date: 2026-04-04

---

## 1. Overview

AURA plugins are shared libraries (`.so` on Linux) that extend the host
application at runtime. The plugin system uses a pure C API to ensure ABI
stability and maximum compatibility across compiler versions.

### Design Goals

| Goal | Approach |
|------|----------|
| ABI stability | Pure C API, no C++ name mangling, no STL in interface |
| Backward compatibility | Versioned API (major.minor), host rejects incompatible major |
| Minimal coupling | Plugins access AURA services only through `AuraHostApi` vtable |
| Safe lifecycle | Explicit init/destroy, host owns dlopen/dlclose |
| Zero mandatory dependencies | Plugin .so links only against libc; host symbols resolved at runtime |

### Non-Goals (MVP)

- Hot-reload (unload + re-load while running)
- Plugin dependency resolution (plugin A depends on plugin B)
- Sandboxing / permission model
- Network-based plugin distribution

---

## 2. Architecture

```
+--------------------------------------------------+
|                  AURA Host                        |
|                                                   |
|  +-------------+   +-------------------------+   |
|  | PluginMgr   |-->| AuraPluginHandle[0..N]  |   |
|  +-------------+   +----------+--------------+   |
|        |                       |                  |
|  +-----v---------+    +-------v---------+        |
|  | AuraHostApi   |    | dlopen/dlsym    |        |
|  | (vtable)      |    | (system loader) |        |
|  +-----+---------+    +-------+---------+        |
|        |                       |                  |
+--------|-----------------------|------------------+
         |                       |
   +-----v---------+    +-------v---------+
   | Plugin uses   |    | Plugin .so      |
   | host services |<---| aura_plugin_info|
   +---------------+    +-----------------+
```

### Components

1. **`AuraPluginInfo`** -- Static descriptor exported by each plugin.
   Contains metadata (name, version, author), capability flags, and
   function pointers (init, destroy, callbacks).

2. **`AuraHostApi`** -- Vtable of services the host provides to plugins.
   Includes logging, disassembly, file info queries, symbol access, and
   console output.

3. **`AuraPluginHandle`** -- Opaque per-plugin instance managed by the host.
   Wraps the dlopen handle, plugin info, and plugin context pointer.

4. **`AuraPluginManager`** -- Orchestrator that loads/unloads multiple plugins
   and dispatches events (e.g., file loaded) to all relevant plugins.

---

## 3. Plugin Lifecycle

```
                Host                              Plugin .so
                ----                              ----------
    1. dlopen(path)
    2. dlsym("aura_plugin_info")
    3. version_check(info->api_version_major)
         |
         | major mismatch? --> log error, dlclose, skip
         |
    4. ctx = info->init(&host_api)  --------->  allocate state,
         |                                      store host_api ptr,
         |                                      return ctx
         |
    5. Register callbacks based on             Plugin is now active
       info->capabilities
         |
    [runtime: host dispatches events]
         |
    6. info->on_file_loaded(ctx, ...)  ------> analyze file,
         |                                     call host_api->log(),
         |                                     call host_api->console_print()
         |
    [user requests unload or host exits]
         |
    7. info->destroy(ctx)  ------------------> free all plugin state,
         |                                     stop using host_api
    8. dlclose(handle)
```

### State Transitions

```
  [not loaded] --dlopen--> [loaded] --init()--> [active]
                                                   |
                                            destroy()
                                                   |
                           [loaded] <--------------+
                              |
                          dlclose()
                              |
                       [not loaded]
```

### Error Handling

| Stage | Error | Host Action |
|-------|-------|-------------|
| dlopen | File not found / invalid ELF | Log error, skip |
| dlsym | `aura_plugin_info` not found | Log error, dlclose, skip |
| Version check | Major version mismatch | Log error, dlclose, skip |
| init() | Returns NULL | Log error, dlclose, skip |
| Callback | Returns error code | Log warning, continue |

---

## 4. API Version Contract

```c
#define AURA_PLUGIN_API_VERSION_MAJOR  1
#define AURA_PLUGIN_API_VERSION_MINOR  0
```

### Compatibility Rules

| Plugin Major | Host Major | Compatible? |
|-------------|------------|-------------|
| 1 | 1 | Yes |
| 1 | 2 | No (host broke ABI) |
| 2 | 1 | No (plugin uses new ABI) |

Minor version increases are backward-compatible: a plugin built against
1.0 works with host 1.5 (new host_api fields are appended at the end).

---

## 5. Capability System

Plugins declare their capabilities via bitflags in `AuraPluginInfo.capabilities`:

| Flag | Value | Meaning | Required Callback |
|------|-------|---------|-------------------|
| `AURA_PLUGIN_CAP_ANALYSIS` | `1<<0` | Runs analysis on loaded files | `on_file_loaded` |
| `AURA_PLUGIN_CAP_UI_MENU` | `1<<1` | Adds a menu entry in GUI | `menu_action` |
| `AURA_PLUGIN_CAP_LOADER` | `1<<2` | Provides a file format loader | (future) |
| `AURA_PLUGIN_CAP_EXPORTER` | `1<<3` | Provides an output exporter | (future) |

The host checks that required callbacks are non-NULL for declared capabilities.
If a capability is declared but the callback is NULL, the host logs a warning
and clears that capability bit.

---

## 6. Host API Surface

The `AuraHostApi` struct provides these service categories:

### 6.1 Logging

```c
void (*log)(int level, const char *fmt, ...);
// level: 0=DEBUG, 1=INFO, 2=WARN, 3=ERROR
```

### 6.2 Disassembly

```c
int (*disassemble)(const uint8_t *data, size_t size,
                   AuraAddr base_addr, AuraArch arch,
                   char *out_text, size_t text_size);
```

### 6.3 File Information

```c
uint32_t (*get_section_count)(void);
const char *(*get_section_name)(uint32_t idx);
AuraError (*get_section_info)(uint32_t idx, uint64_t *vaddr, uint64_t *size);
AuraError (*get_section_data)(uint32_t idx, const uint8_t **data, size_t *size);
uint32_t (*get_symbol_count)(void);
AuraError (*get_symbol_info)(uint32_t idx, const char **name,
                             uint64_t *addr, uint64_t *size);
```

### 6.4 Console Output

```c
void (*console_print)(const char *fmt, ...);
```

### Future Extensions

New function pointers will be appended to `AuraHostApi` in minor version
updates. Plugins built against older minor versions will not access the
new fields (they don't know about them), ensuring backward compatibility.

---

## 7. Plugin Directory Layout

```
plugins/
  example/
    CMakeLists.txt          # Builds example_plugin.so
    example_plugin.c        # Plugin source
  yara_scanner/
    CMakeLists.txt
    yara_plugin.c
  ...
```

Default plugin search paths (checked in order):
1. `$AURA_PLUGIN_DIR` environment variable
2. `~/.local/share/aura/plugins/`
3. `<install_prefix>/lib/aura/plugins/`

---

## 8. Example Plugin Skeleton

```c
#include "aura_plugin.h"
#include <stdlib.h>

typedef struct {
    const AuraHostApi *host;
    int file_count;
} MyPluginCtx;

static void *my_init(const AuraHostApi *host) {
    MyPluginCtx *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) return NULL;
    ctx->host = host;
    host->log(1, "[MyPlugin] initialized");
    return ctx;
}

static void my_destroy(void *plugin_ctx) {
    MyPluginCtx *ctx = plugin_ctx;
    if (ctx) {
        ctx->host->log(1, "[MyPlugin] destroyed (analyzed %d files)",
                       ctx->file_count);
        free(ctx);
    }
}

static AuraError my_on_file_loaded(void *plugin_ctx,
                                    const char *path,
                                    const uint8_t *data,
                                    size_t data_size,
                                    AuraArch arch,
                                    AuraFileFormat format) {
    MyPluginCtx *ctx = plugin_ctx;
    ctx->file_count++;
    ctx->host->console_print("[MyPlugin] File loaded: %s (%zu bytes)", path, data_size);
    return AURA_OK;
}

static const AuraPluginInfo g_info = {
    .api_version_major = AURA_PLUGIN_API_VERSION_MAJOR,
    .api_version_minor = AURA_PLUGIN_API_VERSION_MINOR,
    .name        = "Example Plugin",
    .version     = "1.0.0",
    .description = "Demonstrates the AURA plugin API",
    .author      = "AURA Contributors",
    .capabilities = AURA_PLUGIN_CAP_ANALYSIS,
    .init        = my_init,
    .destroy     = my_destroy,
    .on_file_loaded = my_on_file_loaded,
    .menu_action    = NULL,
};

const AuraPluginInfo *aura_plugin_info(void) {
    return &g_info;
}
```

---

## 9. Build & Link Model

### Plugin Build

Plugins are built as shared libraries with position-independent code:

```cmake
add_library(example_plugin SHARED example_plugin.c)
target_include_directories(example_plugin PRIVATE
    ${AURA_INCLUDE_DIR}    # include/aura_plugin.h, include/aura.h
    ${AURA_CORE_DIR}       # src/core/aura.h
)
set_target_properties(example_plugin PROPERTIES
    PREFIX ""              # Output: example_plugin.so (no "lib" prefix)
)
```

Plugins do NOT link against `libaura_core.a`. All host interaction goes
through the `AuraHostApi` vtable. This means:
- No symbol resolution issues
- Plugin can be built independently of the host
- Plugin .so has no dependency on host binary layout

### Host Side

The host links with `-ldl` for `dlopen`/`dlsym`/`dlclose`.

---

## 10. Thread Safety

- `init()` and `destroy()` are called from the main thread only.
- `on_file_loaded()` may be called from an analysis worker thread.
  Plugins that need thread safety must implement their own synchronization.
- `AuraHostApi` function pointers are thread-safe (host guarantees this).

---

## 11. Security Considerations

- Plugins are native code with full process privileges. Users should only
  load plugins from trusted sources.
- The host validates the `aura_plugin_info` symbol signature (returns
  non-NULL, valid version) but cannot verify plugin behavior.
- Future: optional signature verification for plugin .so files.

---

## 12. Files

| File | Purpose |
|------|---------|
| `include/aura_plugin.h` | Public plugin API header |
| `src/core/plugin_loader.c` | Host-side dlopen/dlsym loader (Task 1.6) |
| `plugins/example/example_plugin.c` | Example plugin (Task 1.6) |
| `docs/plugin_api.md` | This design document |
