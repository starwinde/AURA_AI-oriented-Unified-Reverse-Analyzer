#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import shutil
import sys
from pathlib import Path
from typing import Any


REPO_ASSET_SUBDIRS = (
    "rule-packs",
    "eval-datasets",
    "safety-profiles",
    "token-classification-models",
)


def load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8"))


def copy_tree_contents(src: Path, dst: Path) -> None:
    if not src.exists():
        return

    dst.mkdir(parents=True, exist_ok=True)
    for child in src.iterdir():
        target = dst / child.name
        if child.is_dir():
            copy_tree_contents(child, target)
        else:
            shutil.copy2(child, target)


def ensure_expected_files(base: Path, expected: list[str], asset_id: str) -> None:
    missing = [name for name in expected if not (base / name).exists()]
    if missing:
        raise RuntimeError(
            f"asset '{asset_id}' is incomplete under {base}; missing: {', '.join(missing)}"
        )


def install_repo_assets(repo_root: Path, aura_home: Path) -> None:
    safety_root = repo_root / "assets" / "safety"
    copy_tree_contents(safety_root, aura_home / "assets" / "safety")
    for subdir in REPO_ASSET_SUBDIRS:
        copy_tree_contents(safety_root / subdir, aura_home / subdir)


def download_model(asset: dict[str, Any], aura_home: Path) -> Path:
    from huggingface_hub import snapshot_download

    target = aura_home / asset["target_subdir"]
    target.mkdir(parents=True, exist_ok=True)
    snapshot_download(
        repo_id=asset["repo_id"],
        repo_type=asset.get("repo_type", "model"),
        revision=asset.get("revision", "main"),
        local_dir=str(target),
        allow_patterns=asset.get("allow_patterns"),
    )

    manifest_template = target / "manifest.template.json"
    manifest_path = target / "manifest.json"
    if manifest_template.exists() and not manifest_path.exists():
        manifest_path.write_text(
            manifest_template.read_text(encoding="utf-8"),
            encoding="utf-8",
        )

    ensure_expected_files(target, asset["expected_files"], asset["asset_id"])
    return target


def download_dataset(asset: dict[str, Any], aura_home: Path) -> Path:
    from huggingface_hub import snapshot_download

    target = aura_home / asset["target_subdir"]
    target.mkdir(parents=True, exist_ok=True)
    snapshot_download(
        repo_id=asset["repo_id"],
        repo_type=asset.get("repo_type", "dataset"),
        revision=asset.get("revision", "main"),
        local_dir=str(target),
    )
    manifest = {
        "schema_version": 1,
        "dataset_id": asset["asset_id"],
        "source": "huggingface",
        "repo_id": asset["repo_id"],
        "revision": asset.get("revision", "main"),
        "purpose": asset.get("purpose", "external_reference_eval_material"),
    }
    (target / "manifest.aura.json").write_text(
        json.dumps(manifest, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    ensure_expected_files(target, asset["expected_files"], asset["asset_id"])
    return target


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", required=True)
    parser.add_argument("--aura-home", required=True)
    parser.add_argument("--manifest", required=True)
    parser.add_argument("--repo-assets-only", action="store_true")
    return parser.parse_args(argv)


def main(argv: list[str]) -> int:
    args = parse_args(argv)

    repo_root = Path(args.repo_root).resolve()
    aura_home = Path(args.aura_home).expanduser().resolve()
    manifest = load_json(Path(args.manifest).resolve())
    aura_home.mkdir(parents=True, exist_ok=True)

    install_repo_assets(repo_root, aura_home)
    if args.repo_assets_only:
        print(
            json.dumps(
                {"aura_home": str(aura_home), "mode": "repo-assets-only"},
                ensure_ascii=False,
            )
        )
        return 0

    for model in manifest["token_classification_models"]:
        download_model(model, aura_home)
    for dataset in manifest["eval_datasets"]:
        download_dataset(dataset, aura_home)

    print(
        json.dumps(
            {
                "aura_home": str(aura_home),
                "model_count": len(manifest["token_classification_models"]),
                "dataset_count": len(manifest["eval_datasets"]),
            },
            ensure_ascii=False,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
