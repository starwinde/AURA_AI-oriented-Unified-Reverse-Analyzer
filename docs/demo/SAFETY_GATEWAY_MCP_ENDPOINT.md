# AURA Safety Gateway MCP Endpoint

`aura-safety-gateway.exe` is the endpoint that an MCP client should connect to
when reverse-engineering context must be protected before it reaches an LLM.

## Start the Gateway

```powershell
build-trim-gui\src\safety_gateway\Release\aura-safety-gateway.exe `
  --serve `
  --listen-host 127.0.0.1 `
  --listen-port 8765 `
  --cache D:\aura-cache\software-a.sqlite
```

The gateway keeps running until the process is stopped. It filters inbound MCP
payloads before any protected data is returned or forwarded.

## MCP Client Configuration

Point the MCP client URL at the safety gateway, not directly at another AURA
tool:

```json
{
  "mcpServers": {
    "aura-safety-gateway": {
      "url": "http://127.0.0.1:8765/mcp"
    }
  }
}
```

## Port Model

- Input endpoint: `--listen-host` + `--listen-port`.
- Output/upstream endpoint: `--upstream-url`, reserved for approved forwarding.
- Cache DB: `--cache`, selected per target software or shared intentionally.

Example with a separate upstream MCP endpoint:

```powershell
build-trim-gui\src\safety_gateway\Release\aura-safety-gateway.exe `
  --serve `
  --listen-host 127.0.0.1 `
  --listen-port 8765 `
  --upstream-url http://127.0.0.1:8780/mcp `
  --cache D:\aura-cache\software-a.sqlite
```

Non-loopback listen hosts such as `0.0.0.0` are blocked unless the user also
passes `--allow-remote-bind`.
