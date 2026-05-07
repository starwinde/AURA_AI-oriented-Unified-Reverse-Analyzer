# AURA Collaboration Server Design

> Task 8.53 -- Server-client architecture design for real-time collaboration.
> Date: 2026-04-04

---

## 1. Overview

AURA Collaboration Server enables multiple analysts to work on the same binary
analysis project simultaneously, similar to Ghidra Server / IDA Team Server.
The system provides real-time synchronization of annotations, comments, function
renames, type changes, and cursor positions across connected clients.

### Design Goals

| Goal | Description |
|------|-------------|
| **Low latency** | Sub-100ms propagation for annotation changes |
| **Conflict-free** | Last-writer-wins (LWW) with server-authoritative ordering |
| **Lightweight** | Single-binary server, no external DB dependency (embedded SQLite) |
| **Secure** | Token-based authentication, per-project permissions |
| **Offline-capable** | Clients queue changes when disconnected, sync on reconnect |

---

## 2. Architecture

```
 ┌──────────────┐       WebSocket (TCP)       ┌──────────────────┐
 │  AURA Client │ ◄──────────────────────────► │  AURA Server     │
 │  (aura-gui)  │                              │  (aura-server)   │
 └──────────────┘                              │                  │
                                               │  ┌────────────┐ │
 ┌──────────────┐       WebSocket (TCP)       │  │ SessionMgr  │ │
 │  AURA Client │ ◄──────────────────────────► │  ├────────────┤ │
 │  (aura-gui)  │                              │  │ AuthModule  │ │
 └──────────────┘                              │  ├────────────┤ │
                                               │  │ SyncEngine  │ │
 ┌──────────────┐       WebSocket (TCP)       │  ├────────────┤ │
 │  AURA Client │ ◄──────────────────────────► │  │ ProjectDB   │ │
 │  (aura-gui)  │                              │  │ (SQLite)    │ │
 └──────────────┘                              │  └────────────┘ │
                                               └──────────────────┘
```

### Components

| Component | Role |
|-----------|------|
| **aura-server** | Standalone TCP server binary. Manages projects, authenticates users, broadcasts changes. |
| **CollabClient** | Client-side module embedded in aura-gui. Connects to server via WebSocket, sends/receives change events. |
| **SyncEngine** | Server-side event ordering, conflict resolution, and broadcast. |
| **AuthModule** | Token-based authentication and per-project role enforcement. |
| **ProjectDB** | SQLite database storing project state, change history, and user info. |

---

## 3. Protocol

### 3.1 Transport

- **WebSocket over TCP** (RFC 6455)
- Default port: **17721** (`0x4541` = "EA" for Engineering Analysis)
- Message format: **JSON** (cJSON, already in project dependencies)
- Maximum message size: 1 MB
- Heartbeat: server sends `ping` every 30s; client must `pong` within 10s

### 3.2 Message Envelope

Every message follows this envelope:

```json
{
  "type": "<message_type>",
  "seq": 12345,
  "ts": 1712188800,
  "payload": { ... }
}
```

| Field | Type | Description |
|-------|------|-------------|
| `type` | string | Message type identifier |
| `seq` | uint64 | Monotonically increasing sequence number (per-client for requests, global for server broadcasts) |
| `ts` | uint64 | Unix timestamp (seconds) |
| `payload` | object | Type-specific data |

### 3.3 Message Types

#### Authentication

| Type | Direction | Description |
|------|-----------|-------------|
| `auth_request` | C -> S | Client sends token to authenticate |
| `auth_response` | S -> C | Server confirms/denies with session ID |

```json
// auth_request
{
  "type": "auth_request",
  "seq": 1,
  "ts": 1712188800,
  "payload": {
    "username": "analyst1",
    "token": "sha256:abcdef...",
    "client_version": "0.1.0"
  }
}

// auth_response
{
  "type": "auth_response",
  "seq": 1,
  "ts": 1712188800,
  "payload": {
    "success": true,
    "session_id": "sess_abc123",
    "user_id": 1,
    "role": "editor"
  }
}
```

#### Project Operations

| Type | Direction | Description |
|------|-----------|-------------|
| `project_join` | C -> S | Join a shared project |
| `project_joined` | S -> C | Confirmation with current state snapshot |
| `project_leave` | C -> S | Leave a project |
| `project_list` | C -> S | List available projects |
| `project_list_response` | S -> C | Available projects |

#### Change Events

| Type | Direction | Description |
|------|-----------|-------------|
| `change` | C -> S | Client submits a change |
| `change_broadcast` | S -> C* | Server broadcasts accepted change to all clients |
| `change_ack` | S -> C | Server acknowledges change acceptance with global seq |
| `change_reject` | S -> C | Server rejects change (permission denied, conflict) |

Change payload categories:

```json
// Function rename
{
  "category": "func_rename",
  "addr": "0x401000",
  "old_name": "sub_401000",
  "new_name": "parse_header"
}

// Comment add/edit
{
  "category": "comment",
  "addr": "0x401020",
  "text": "Initializes the parser state"
}

// Type annotation
{
  "category": "type_change",
  "addr": "0x401000",
  "param_idx": 0,
  "old_type": "int",
  "new_type": "uint32_t"
}

// Bookmark
{
  "category": "bookmark",
  "action": "add",
  "addr": "0x401000",
  "label": "Entry point"
}
```

#### Cursor & Presence

| Type | Direction | Description |
|------|-----------|-------------|
| `cursor_update` | C -> S | Client cursor position changed |
| `cursor_broadcast` | S -> C* | Broadcast cursor positions of all users |
| `user_joined` | S -> C* | A user joined the project |
| `user_left` | S -> C* | A user left the project |

```json
// cursor_update
{
  "type": "cursor_update",
  "seq": 50,
  "ts": 1712188900,
  "payload": {
    "addr": "0x401234",
    "view": "disasm"
  }
}
```

#### History

| Type | Direction | Description |
|------|-----------|-------------|
| `history_request` | C -> S | Request change history (paginated) |
| `history_response` | S -> C | Page of change records |
| `undo_request` | C -> S | Request undo of a specific change |
| `undo_response` | S -> C | Undo result |

---

## 4. Authentication & Permissions

### 4.1 Authentication Flow

1. Server generates a per-user token on first registration (CLI: `aura-server --add-user <name>`)
2. Token is SHA-256 hash of `username + password + server_salt`
3. Client stores token in local config (`~/.config/aura/servers.json`)
4. On connect, client sends `auth_request` with username + token
5. Server validates against its user database
6. On success, server returns a session ID valid for the connection lifetime

### 4.2 Roles & Permissions

| Role | Read | Comment | Rename | Type Edit | Admin |
|------|------|---------|--------|-----------|-------|
| `viewer` | Y | N | N | N | N |
| `commenter` | Y | Y | N | N | N |
| `editor` | Y | Y | Y | Y | N |
| `admin` | Y | Y | Y | Y | Y |

- Roles are per-project (a user can be `editor` on project A, `viewer` on project B)
- `admin` can add/remove users, change roles, delete projects
- The server creator is automatically `admin` for all projects

### 4.3 Token Storage (Server-side)

```sql
CREATE TABLE users (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    username    TEXT UNIQUE NOT NULL,
    token_hash  TEXT NOT NULL,          -- SHA-256(token)
    created_at  INTEGER NOT NULL,
    last_login  INTEGER
);

CREATE TABLE project_roles (
    user_id     INTEGER NOT NULL,
    project_id  INTEGER NOT NULL,
    role        TEXT NOT NULL DEFAULT 'viewer',
    PRIMARY KEY (user_id, project_id),
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (project_id) REFERENCES projects(id)
);
```

---

## 5. Synchronization Strategy

### 5.1 Server-Authoritative Ordering

The server assigns a **global sequence number** to every accepted change.
Clients apply changes in global sequence order. This avoids the complexity
of full CRDT/OT while providing deterministic state across all clients.

```
Client A: rename func @ 0x401000 -> "foo"    (client_seq=1)
Client B: rename func @ 0x401000 -> "bar"    (client_seq=1)

Server receives A first:
  global_seq=100: rename 0x401000 -> "foo"   (broadcast to all)
Server receives B second:
  global_seq=101: rename 0x401000 -> "bar"   (broadcast to all)

Final state on all clients: func @ 0x401000 = "bar"
```

### 5.2 Conflict Resolution: Last-Writer-Wins (LWW)

- For same-address, same-category changes: the later global_seq wins
- No merge needed -- annotations are atomic values, not text documents
- Server broadcasts all changes; clients apply in order
- The `change_ack` message tells the originator their change's global_seq

### 5.3 Offline Queueing

When a client disconnects:
1. Client queues changes locally (in-memory + SQLite journal)
2. On reconnect, client sends `sync_request` with its last known `global_seq`
3. Server sends all changes since that seq as a batch
4. Client then replays its queued local changes to the server
5. Server assigns new global_seq to each, potentially overwriting interim changes

### 5.4 Change Persistence (Server-side)

```sql
CREATE TABLE projects (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    name        TEXT UNIQUE NOT NULL,
    binary_hash TEXT NOT NULL,           -- SHA-256 of the analyzed binary
    created_at  INTEGER NOT NULL
);

CREATE TABLE changes (
    global_seq  INTEGER PRIMARY KEY AUTOINCREMENT,
    project_id  INTEGER NOT NULL,
    user_id     INTEGER NOT NULL,
    category    TEXT NOT NULL,
    addr        INTEGER,
    payload     TEXT NOT NULL,           -- JSON blob
    ts          INTEGER NOT NULL,
    undone      INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY (project_id) REFERENCES projects(id),
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE INDEX idx_changes_project ON changes(project_id, global_seq);
```

---

## 6. Server Implementation Plan

### 6.1 Binary: `aura-server`

- Standalone executable, no Qt dependency
- Uses POSIX sockets + `poll()`/`epoll()` for connection management
- WebSocket handshake implemented via HTTP/1.1 upgrade (custom, lightweight)
- JSON parsing via cJSON (already in project)
- SQLite for persistence (already in project)
- Single-threaded event loop (sufficient for <100 concurrent users)

### 6.2 Source Layout

```
src/
  collab/
    collab_server.h/.cpp    -- Server main loop, connection management
    collab_client.h/.cpp    -- Client-side connection (used by GUI)
    collab_protocol.h/.cpp  -- Message serialization/deserialization
    collab_auth.h/.cpp      -- Authentication and role management
    collab_sync.h/.cpp      -- Server-side sync engine, change ordering
    collab_types.h          -- Shared types and constants
```

### 6.3 Client Integration

The `CollabClient` class integrates with the existing GUI:
- Runs WebSocket I/O on a separate `QThread` (via `QTcpSocket`)
- Emits Qt signals for incoming changes, cursor updates, user events
- `MainWindow` connects to these signals to update views
- Changes made in the GUI are forwarded to `CollabClient::sendChange()`

---

## 7. Wire Format Examples

### Full session example

```
1. Client connects via TCP to server:17721
2. WebSocket handshake (HTTP Upgrade)
3. C->S: auth_request { username, token }
4. S->C: auth_response { success, session_id, role }
5. C->S: project_join { project_name: "firmware_v2" }
6. S->C: project_joined { project_id, users: [...], last_seq: 500 }
7. S->C: cursor_broadcast { users: [{id:2, addr:0x401000, view:"disasm"}] }
8. C->S: change { category:"comment", addr:0x401020, text:"loop counter" }
9. S->C: change_ack { client_seq:1, global_seq:501 }
10. S->C*: change_broadcast { global_seq:501, user:"analyst1", ... }
11. (periodic) S->C: ping / C->S: pong
12. C->S: project_leave {}
13. WebSocket close
```

---

## 8. Security Considerations

| Concern | Mitigation |
|---------|------------|
| Token interception | TLS recommended for production (optional `--tls` flag with cert/key) |
| Replay attacks | Session ID + monotonic seq prevent replay |
| DoS | Max connections per IP (default: 10), rate limiting on change events |
| Data integrity | Server validates all changes before broadcasting |
| Privilege escalation | Role checks on every change; admin operations require admin role |

---

## 9. Future Extensions (Post-MVP)

- TLS encryption (OpenSSL integration)
- Project versioning (branch/merge model)
- Binary diff synchronization (share analyzed binaries)
- Web-based viewer (read-only WebSocket client)
- LDAP/SSO authentication integration
