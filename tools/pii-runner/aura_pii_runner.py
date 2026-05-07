#!/usr/bin/env python3
# Copyright 2026 AURA Project Contributors
# SPDX-License-Identifier: Apache-2.0

"""AURA PII model runner protocol v1.

This runner is intentionally a separate process from AURA core. The initial
implementation supports a deterministic dummy mode so the JSON protocol,
venv/subprocess boundary, and error envelope can be tested before a real token
classification backend is wired in.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Any


EMAIL_RE = re.compile(r"[A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,}")
SCHEMA_VERSION = 1
OFFSET_UNIT = "utf8_byte"


def error(code: str, message: str, request_id: str | None = None) -> int:
    payload: dict[str, Any] = {
        "schema_version": 1,
        "status": "error",
        "error_code": code,
        "message": message,
    }
    if request_id:
        payload["request_id"] = request_id
    print(json.dumps(payload, ensure_ascii=False))
    return 1


def load_json(path: Path) -> Any:
    with path.open("r", encoding="utf-8-sig") as f:
        return json.load(f)


def utf8_byte_offset(text: str, codepoint_offset: int) -> int:
    return len(text[:codepoint_offset].encode("utf-8"))


def scan_dummy(model_id: str, request: dict[str, Any]) -> list[dict[str, Any]]:
    findings: list[dict[str, Any]] = []
    texts = request.get("texts", [])
    if not isinstance(texts, list):
        texts = []
    for item in texts:
        if not isinstance(item, dict):
            continue
        text_id = item.get("text_id")
        text = item.get("text", "")
        if not isinstance(text_id, str) or not isinstance(text, str):
            continue
        for match in EMAIL_RE.finditer(text):
            findings.append(
                {
                    "text_id": text_id,
                    "kind": "email",
                    "start": utf8_byte_offset(text, match.start()),
                    "end": utf8_byte_offset(text, match.end()),
                    "confidence": 0.98,
                    "detector_id": f"model/{model_id}",
                }
            )
    return findings


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--model-dir", required=True)
    parser.add_argument("--input-json", required=True)
    args = parser.parse_args(argv)

    request_id = None
    try:
        request = load_json(Path(args.input_json))
        if isinstance(request, dict):
            request_id = request.get("request_id")
        manifest = load_json(Path(args.model_dir) / "manifest.json")
    except OSError as exc:
        return error("io_error", str(exc), request_id)
    except json.JSONDecodeError:
        return error("invalid_json", "invalid JSON", request_id)

    if not isinstance(request, dict):
        return error("invalid_request", "request must be a JSON object", request_id)
    if request.get("schema_version") != SCHEMA_VERSION:
        return error("invalid_request", "request schema_version must be 1", request_id)
    if request.get("offset_unit") != OFFSET_UNIT:
        return error("invalid_request", "request offset_unit must be utf8_byte", request_id)
    if not isinstance(manifest, dict) or manifest.get("schema_version") != 1:
        return error("invalid_model_manifest", "model manifest schema_version must be 1", request_id)

    model_id = manifest.get("model_id")
    if not isinstance(model_id, str) or not model_id:
        return error("invalid_model_manifest", "model_id is required", request_id)

    backend = manifest.get("backend")
    if backend != "dummy":
        return error("unsupported_backend", "unsupported runner backend", request_id)

    payload = {
        "schema_version": SCHEMA_VERSION,
        "status": "ok",
        "offset_unit": OFFSET_UNIT,
        "request_id": request.get("request_id", ""),
        "findings": scan_dummy(model_id, request),
    }
    print(json.dumps(payload, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
