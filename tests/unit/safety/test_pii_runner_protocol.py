import json
import subprocess
import sys
import tempfile
from pathlib import Path


def write_manifest(model_dir: Path, **overrides):
    manifest = {
        "schema_version": 1,
        "model_id": "dummy-privacy-filter",
        "runner": "python_venv",
        "backend": "dummy",
        "labels": ["email"],
    }
    manifest.update(overrides)
    (model_dir / "manifest.json").write_text(
        json.dumps(manifest),
        encoding="utf-8",
    )


def write_request(path: Path, **overrides):
    request = {
        "schema_version": 1,
        "offset_unit": "utf8_byte",
        "request_id": "scan-001",
        "locale": "ko-KR",
        "texts": [
            {
                "text_id": "str-1",
                "text": "문의: hong@example.com",
            }
        ],
    }
    request.update(overrides)
    path.write_text(
        json.dumps(request, ensure_ascii=False),
        encoding="utf-8",
    )


def run_runner(runner: Path, model_dir: Path, request: Path):
    return subprocess.run(
        [
            sys.executable,
            str(runner),
            "--model-dir",
            str(model_dir),
            "--input-json",
            str(request),
        ],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        timeout=5,
    )


def parse_stdout_json(proc):
    assert proc.stdout.strip()
    assert proc.stdout == proc.stdout.strip() + "\n"
    assert proc.stderr == ""
    return json.loads(proc.stdout)


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: test_pii_runner_protocol.py <runner>", file=sys.stderr)
        return 2

    runner = Path(sys.argv[1])
    with tempfile.TemporaryDirectory() as td:
        root = Path(td)
        model_dir = root / "model"
        model_dir.mkdir()
        write_manifest(model_dir)
        request = root / "request.json"
        write_request(request)

        proc = run_runner(runner, model_dir, request)
        if proc.returncode != 0:
            print(proc.stderr, file=sys.stderr)
            return proc.returncode

        payload = parse_stdout_json(proc)
        assert payload["schema_version"] == 1
        assert payload["status"] == "ok"
        assert payload["offset_unit"] == "utf8_byte"
        assert payload["request_id"] == "scan-001"
        assert payload["findings"] == [
            {
                "text_id": "str-1",
                "kind": "email",
                "start": 8,
                "end": 24,
                "confidence": 0.98,
                "detector_id": "model/dummy-privacy-filter",
            }
        ]

        missing_offset_request = root / "missing-offset-request.json"
        write_request(missing_offset_request, offset_unit=None)
        missing_offset_payload = json.loads(missing_offset_request.read_text(encoding="utf-8"))
        del missing_offset_payload["offset_unit"]
        missing_offset_request.write_text(
            json.dumps(missing_offset_payload, ensure_ascii=False),
            encoding="utf-8",
        )
        proc = run_runner(runner, model_dir, missing_offset_request)
        payload = parse_stdout_json(proc)
        assert proc.returncode != 0
        assert payload["status"] == "error"
        assert payload["error_code"] == "invalid_request"
        assert payload["request_id"] == "scan-001"

        wrong_offset_request = root / "wrong-offset-request.json"
        write_request(wrong_offset_request, offset_unit="codepoint")
        proc = run_runner(runner, model_dir, wrong_offset_request)
        payload = parse_stdout_json(proc)
        assert proc.returncode != 0
        assert payload["status"] == "error"
        assert payload["error_code"] == "invalid_request"
        assert payload["request_id"] == "scan-001"

        bom_request = root / "bom-request.json"
        write_request(bom_request, schema_version=2, request_id="scan-bom")
        bom_request.write_bytes(b"\xef\xbb\xbf" + bom_request.read_bytes())
        proc = run_runner(runner, model_dir, bom_request)
        payload = parse_stdout_json(proc)
        assert proc.returncode != 0
        assert payload["status"] == "error"
        assert payload["error_code"] == "invalid_request"
        assert payload["request_id"] == "scan-bom"

        unsupported_model_dir = root / "unsupported-model"
        unsupported_model_dir.mkdir()
        write_manifest(unsupported_model_dir, backend="real_model")
        proc = run_runner(runner, unsupported_model_dir, request)
        payload = parse_stdout_json(proc)
        assert proc.returncode != 0
        assert payload["status"] == "error"
        assert payload["error_code"] == "unsupported_backend"
        assert payload["request_id"] == "scan-001"

        missing_backend_model_dir = root / "missing-backend-model"
        missing_backend_model_dir.mkdir()
        write_manifest(missing_backend_model_dir, backend=None)
        missing_backend_payload = json.loads(
            (missing_backend_model_dir / "manifest.json").read_text(encoding="utf-8")
        )
        del missing_backend_payload["backend"]
        (missing_backend_model_dir / "manifest.json").write_text(
            json.dumps(missing_backend_payload),
            encoding="utf-8",
        )
        proc = run_runner(runner, missing_backend_model_dir, request)
        payload = parse_stdout_json(proc)
        assert proc.returncode != 0
        assert payload["status"] == "error"
        assert payload["error_code"] == "unsupported_backend"
        assert payload["request_id"] == "scan-001"

        malformed_texts_request = root / "malformed-texts-request.json"
        write_request(malformed_texts_request, texts=["bad"])
        proc = run_runner(runner, model_dir, malformed_texts_request)
        payload = parse_stdout_json(proc)
        assert proc.returncode == 0
        assert payload["status"] == "ok"
        assert payload["offset_unit"] == "utf8_byte"
        assert payload["request_id"] == "scan-001"
        assert payload["findings"] == []

        non_list_texts_request = root / "non-list-texts-request.json"
        write_request(non_list_texts_request, texts=None)
        proc = run_runner(runner, model_dir, non_list_texts_request)
        payload = parse_stdout_json(proc)
        assert proc.returncode == 0
        assert payload["status"] == "ok"
        assert payload["offset_unit"] == "utf8_byte"
        assert payload["request_id"] == "scan-001"
        assert payload["findings"] == []
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
