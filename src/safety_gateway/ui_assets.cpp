#include "ui_assets.h"

namespace aura::safety_gateway {

std::string safetyGatewayUiHtml() {
    return R"HTML(<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Safety Gateway</title>
  <style>
    :root {
      color-scheme: dark;
      --bg: #1f2023;
      --panel: #2b2c30;
      --panel2: #161719;
      --line: #3b3d42;
      --text: #eeeeee;
      --muted: #a8adb8;
      --accent: #4b8dd8;
      --danger: #d75f5f;
      --warn: #d0a34d;
      --ok: #65b36e;
    }
    * { box-sizing: border-box; }
    body {
      margin: 0;
      min-height: 100vh;
      background: var(--bg);
      color: var(--text);
      font: 13px/1.45 "Segoe UI", system-ui, sans-serif;
    }
    header {
      display: flex;
      align-items: center;
      gap: 18px;
      padding: 12px 16px;
      background: #27282c;
      border-bottom: 1px solid var(--line);
    }
    h1 { font-size: 18px; margin: 0; font-weight: 600; }
    .status { color: var(--muted); display: flex; gap: 14px; flex-wrap: wrap; }
    main {
      display: grid;
      grid-template-columns: minmax(360px, 1.05fr) minmax(420px, 1.55fr) minmax(300px, .9fr);
      gap: 10px;
      padding: 10px;
      height: calc(100vh - 50px);
    }
    section {
      min-height: 0;
      background: var(--panel);
      border: 1px solid var(--line);
      display: flex;
      flex-direction: column;
    }
    section h2 {
      margin: 0;
      padding: 8px 10px;
      font-size: 13px;
      font-weight: 600;
      border-bottom: 1px solid var(--line);
      background: #303137;
    }
    .body { padding: 10px; overflow: auto; }
    .stats { display: grid; grid-template-columns: repeat(2, minmax(0, 1fr)); gap: 8px; }
    .stat { background: var(--panel2); border: 1px solid var(--line); padding: 9px; }
    .stat b { display: block; font-size: 20px; margin-bottom: 2px; }
    .stat span { color: var(--muted); }
    button, input, select {
      background: #35373d;
      color: var(--text);
      border: 1px solid #555861;
      min-height: 28px;
      padding: 4px 8px;
      font: inherit;
    }
    button { cursor: pointer; }
    button:hover { border-color: var(--accent); }
    button.danger { border-color: #7d4545; color: #ffd5d5; }
    table { width: 100%; border-collapse: collapse; font-size: 12px; }
    th, td { border-bottom: 1px solid var(--line); padding: 5px 6px; text-align: left; vertical-align: top; }
    th { background: #303137; color: #d9dde5; position: sticky; top: 0; }
    tr.selected { background: #244b76; }
    .pill { display: inline-block; padding: 1px 6px; border-radius: 2px; background: #3a3d44; }
    .allowed { color: var(--ok); }
    .masked { color: var(--warn); }
    .blocked { color: var(--danger); }
    .flow { display: grid; gap: 7px; }
    .step { border: 1px solid var(--line); background: var(--panel2); padding: 8px; }
    .step strong { display: block; margin-bottom: 3px; }
    pre {
      margin: 0;
      white-space: pre-wrap;
      word-break: break-word;
      background: #111214;
      border: 1px solid var(--line);
      padding: 8px;
      min-height: 140px;
    }
    .stack { display: grid; gap: 8px; }
    .row { display: grid; grid-template-columns: 110px 1fr; gap: 8px; align-items: center; }
    .actions { display: flex; gap: 8px; flex-wrap: wrap; }
    .muted { color: var(--muted); }
  </style>
</head>
<body>
  <header>
    <h1>Safety Gateway</h1>
    <div class="status">
      <span id="mode">mode: loading</span>
      <span id="listen">listen: loading</span>
      <span id="upstream">upstream: loading</span>
      <span id="cache">cache: loading</span>
    </div>
  </header>
  <main>
    <section>
      <h2>Live Gateway Monitor</h2>
      <div class="body stack">
        <div class="stats">
          <div class="stat"><b id="requestsToday">0</b><span>Requests today</span></div>
          <div class="stat"><b id="masked">0</b><span>Masked</span></div>
          <div class="stat"><b id="blocked">0</b><span>Blocked</span></div>
          <div class="stat"><b id="allowed">0</b><span>Allowed</span></div>
          <div class="stat"><b id="protectedItems">0</b><span>Protected items</span></div>
        </div>
        <div class="actions">
          <button data-demo="safe">Safe Fixture</button>
          <button data-demo="pii">PII Masking Fixture</button>
          <button data-demo="secret">Hard Secret Fixture</button>
          <button data-demo="remote_fail">Remote Token Failure Fixture</button>
          <button data-demo="upstream_timeout">Upstream Timeout Fixture</button>
        </div>
        <table>
          <thead>
            <tr><th>Time</th><th>Client</th><th>Method/Tool</th><th>Decision</th><th>Categories</th><th>Route</th><th>Auth</th></tr>
          </thead>
          <tbody id="requestRows"></tbody>
        </table>
      </div>
    </section>
    <section>
      <h2>Request Inspector</h2>
      <div class="body stack">
        <div class="actions" aria-label="Request Inspector tabs">
          <button>Flow</button>
          <button>Protected Payload</button>
          <button>Items</button>
          <button>Audit</button>
          <button>Upstream</button>
        </div>
        <div class="flow">
          <div class="step"><strong>1. Incoming request</strong><span id="flowIncoming" class="muted">No request selected.</span></div>
          <div class="step"><strong>2. Safety scan</strong><span id="flowScan" class="muted">Waiting for traffic.</span></div>
          <div class="step"><strong>3. Policy decision</strong><span id="flowDecision" class="muted">Waiting for decision.</span></div>
          <div class="step"><strong>4. Protected payload</strong><span id="flowProtected" class="muted">Protected output will appear below.</span></div>
          <div class="step"><strong>5. Forward or block</strong><span id="flowRoute" class="muted">Route not selected.</span></div>
          <div class="step"><strong>6. Audit result</strong><span id="flowAudit" class="muted">Audit events will appear below.</span></div>
        </div>
        <pre id="payload">{}</pre>
        <table>
          <thead><tr><th>Action</th><th>Category</th><th>Protected</th><th>Reason</th><th>Reveal</th></tr></thead>
          <tbody id="itemRows"></tbody>
        </table>
        <table>
          <thead><tr><th>Event</th><th>Detail</th></tr></thead>
          <tbody id="auditRows"></tbody>
        </table>
        <pre id="upstreamView">Upstream status will appear here.</pre>
      </div>
    </section>
    <section>
      <h2>Gateway Settings</h2>
      <div class="body stack">
        <div class="row"><label>Mode</label><select id="cfgMode"><option value="local_protect_only">Local Protect Only</option><option value="forward">Forward to Upstream</option></select></div>
        <div class="row"><label>Listen host</label><input id="cfgHost" value="127.0.0.1"></div>
        <div class="row"><label>Port</label><input id="cfgPort" value="8765"></div>
        <div class="row"><label>Remote</label><select id="cfgRemote"><option value="false">Off</option><option value="true">On</option></select></div>
        <div class="row"><label>IP allowlist</label><input id="cfgAllowlist" value="127.0.0.1,::1"></div>
        <div class="row"><label>Upstream</label><input id="cfgUpstream" placeholder="http://127.0.0.1:8780/mcp"></div>
        <div class="row"><label>Cache DB</label><input id="cfgCache" placeholder=".aura/safety-gateway-cache.sqlite"></div>
        <div class="actions">
          <button id="saveConfig">Apply Settings</button>
          <button id="generateToken">Generate Token</button>
          <button id="testUpstream">Test Upstream</button>
        </div>
        <p class="muted">Bearer or X-Safety-Gateway-Token is recommended. URL query token is supported for demos and audited as weak.</p>
        <pre id="configResult">{}</pre>
      </div>
    </section>
  </main>
<script>
let selectedId = null;

async function api(path, options = {}) {
  const response = await fetch(path, Object.assign({headers: {'Content-Type': 'application/json'}}, options));
  return response.json();
}

function setText(id, text) { document.getElementById(id).textContent = text; }
function h(value) {
  return String(value ?? '').replace(/[&<>"']/g, ch => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[ch]));
}

function decisionClass(value) {
  if (value === 'blocked') return 'blocked';
  if (value === 'masked') return 'masked';
  return 'allowed';
}

async function refreshStatus() {
  const status = await api('/api/status');
  setText('mode', 'mode: ' + status.mode);
  setText('listen', 'listen: ' + status.listen);
  setText('upstream', 'upstream: ' + status.upstream);
  setText('cache', 'cache: ' + status.cache_db);
  const stats = await api('/api/stats');
  setText('requestsToday', stats.requests_today || 0);
  setText('masked', stats.masked || 0);
  setText('blocked', stats.blocked || 0);
  setText('allowed', stats.allowed || 0);
  setText('protectedItems', stats.protected_items || 0);
}

async function refreshRequests() {
  const list = await api('/api/requests');
  const rows = document.getElementById('requestRows');
  rows.innerHTML = '';
  (list.requests || []).forEach(req => {
    const tr = document.createElement('tr');
    if (req.request_id === selectedId) tr.className = 'selected';
    tr.innerHTML = '<td>' + h(req.timestamp_iso8601) + '</td><td>' + h(req.client_name) + '<br><span class="muted">' + h(req.client_ip) + '</span></td><td>' + h(req.method) + '<br><span class="muted">' + h(req.tool_name) + '</span></td><td class="' + decisionClass(req.decision) + '">' + h(req.decision) + '</td><td>' + h((req.categories || []).join(', ')) + '</td><td>' + h(req.route) + '</td><td>' + h(req.remote_auth_result) + '</td>';
    tr.onclick = () => selectRequest(req.request_id);
    rows.appendChild(tr);
  });
  if (!selectedId && list.requests && list.requests.length) {
    await selectRequest(list.requests[0].request_id);
  }
}

async function selectRequest(id) {
  selectedId = id;
  const req = await api('/api/requests/' + encodeURIComponent(id));
  setText('flowIncoming', req.method + ' / ' + req.tool_name + ' from ' + req.client_name + ' ' + req.client_ip);
  setText('flowScan', (req.items || []).length + ' item(s), categories: ' + (req.categories || []).join(', '));
  setText('flowDecision', req.decision);
  setText('flowProtected', 'Protected payload generated');
  setText('flowRoute', req.route + ' / ' + req.upstream_status);
  setText('upstreamView', req.upstream_status || 'not_forwarded');
  setText('flowAudit', (req.audit_events || []).length + ' audit event(s)');
  setText('payload', req.protected_payload_json || '{}');
  const itemRows = document.getElementById('itemRows');
  itemRows.innerHTML = '';
  (req.items || []).forEach(item => {
    const tr = document.createElement('tr');
    const revealButton = item.action === 'mask' ? '<button data-reveal="' + item.item_id + '">Reveal</button>' : '';
    tr.innerHTML = '<td>' + h(item.action) + '</td><td>' + h(item.category) + '</td><td>' + h(item.protected_value) + '</td><td>' + h(item.reason) + '</td><td>' + revealButton + '</td>';
    itemRows.appendChild(tr);
  });
  itemRows.querySelectorAll('button[data-reveal]').forEach(btn => {
    btn.onclick = async () => {
      const revealed = await api('/api/requests/' + encodeURIComponent(selectedId) + '/reveal', {method: 'POST', body: JSON.stringify({item_id: btn.dataset.reveal})});
      btn.textContent = revealed.original || revealed.error?.code || 'unavailable';
    };
  });
  const auditRows = document.getElementById('auditRows');
  auditRows.innerHTML = '';
  (req.audit_events || []).forEach(event => {
    const tr = document.createElement('tr');
    tr.innerHTML = '<td>' + h(event.event_type) + '</td><td>' + h(event.detail) + '</td>';
    auditRows.appendChild(tr);
  });
  await refreshRequests();
}

async function loadConfig() {
  const cfg = await api('/api/config');
  document.getElementById('cfgMode').value = cfg.mode || 'local_protect_only';
  document.getElementById('cfgHost').value = cfg.listen_host || '127.0.0.1';
  document.getElementById('cfgPort').value = cfg.listen_port || 8765;
  document.getElementById('cfgRemote').value = String(!!cfg.remote_enabled);
  document.getElementById('cfgAllowlist').value = (cfg.ip_allowlist || []).join(',');
  document.getElementById('cfgUpstream').value = cfg.upstream_url || '';
  document.getElementById('cfgCache').value = cfg.cache_db || '';
}

document.querySelectorAll('button[data-demo]').forEach(btn => {
  btn.onclick = async () => {
    const result = await api('/api/demo/inject', {method: 'POST', body: JSON.stringify({fixture: btn.dataset.demo})});
    selectedId = result.request_id;
    await refreshStatus();
    await refreshRequests();
  };
});

document.getElementById('saveConfig').onclick = async () => {
  const body = {
    mode: document.getElementById('cfgMode').value,
    listen_host: document.getElementById('cfgHost').value,
    listen_port: Number(document.getElementById('cfgPort').value),
    remote_enabled: document.getElementById('cfgRemote').value === 'true',
    ip_allowlist: document.getElementById('cfgAllowlist').value.split(',').map(s => s.trim()).filter(Boolean),
    upstream_url: document.getElementById('cfgUpstream').value,
    cache_db: document.getElementById('cfgCache').value
  };
  const result = await api('/api/config', {method: 'PUT', body: JSON.stringify(body)});
  setText('configResult', JSON.stringify(result, null, 2));
  await refreshStatus();
};

document.getElementById('generateToken').onclick = async () => {
  const result = await api('/api/remote/token/generate', {method: 'POST', body: '{}'});
  setText('configResult', JSON.stringify(result, null, 2));
};

document.getElementById('testUpstream').onclick = async () => {
  const result = await api('/api/demo/inject', {method: 'POST', body: JSON.stringify({fixture: 'upstream_timeout'})});
  setText('configResult', JSON.stringify(result, null, 2));
  await refreshRequests();
};

async function boot() {
  await loadConfig();
  await refreshStatus();
  await refreshRequests();
  setInterval(async () => {
    await refreshStatus();
    await refreshRequests();
  }, 2000);
}
boot();
</script>
</body>
</html>)HTML";
}

}  // namespace aura::safety_gateway
