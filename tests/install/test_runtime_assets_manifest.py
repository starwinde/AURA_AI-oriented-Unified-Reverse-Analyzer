import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "assets" / "safety" / "runtime-assets.json"


def test_runtime_assets_manifest_shape():
    data = json.loads(MANIFEST.read_text(encoding="utf-8"))
    assert data["schema_version"] == 1
    assert data["python_packages"]["huggingface_hub"] == "1.14.0"

    models = data["token_classification_models"]
    assert len(models) == 1
    model = models[0]
    assert model["asset_id"] == "openai-privacy-filter"
    assert model["repo_id"] == "openai/privacy-filter"
    assert model["repo_type"] == "model"
    assert model["revision"] == "7ffa9a043d54d1be65afb281eddf0ffbe629385b"
    assert model["target_subdir"] == "token-classification-models/openai-privacy-filter"
    assert model["expected_files"] == [
        "config.json",
        "model.safetensors",
        "tokenizer.json",
        "manifest.json",
    ]
    assert {"config.json", "model.safetensors", "tokenizer.json"}.issubset(
        set(model["allow_patterns"])
    )

    assert len(data["eval_datasets"]) == 2
    datasets = {d["asset_id"]: d for d in data["eval_datasets"]}
    assert set(datasets) == {"korean-address-en-ko", "korean-proper-noun-koen"}
    expected_datasets = {
        "korean-address-en-ko": (
            "ziozzang/korean_address_en-ko",
            "69c27815a159f609bee0f7c1b39901232485e313",
        ),
        "korean-proper-noun-koen": (
            "ziozzang/korean_proper_noun_koen",
            "65f0d80aa373ddc0a68a19aebc505054cda48860",
        ),
    }
    for asset_id, (repo_id, revision) in expected_datasets.items():
        dataset = datasets[asset_id]
        assert dataset["repo_id"] == repo_id
        assert dataset["repo_type"] == "dataset"
        assert dataset["revision"] == revision
        assert dataset["target_subdir"] == f"eval-datasets/{asset_id}"
        assert dataset["expected_files"] == ["manifest.aura.json"]


def test_runtime_assets_manifest_has_no_repo_local_targets():
    data = json.loads(MANIFEST.read_text(encoding="utf-8"))
    all_assets = data["token_classification_models"] + data["eval_datasets"]
    for asset in all_assets:
        target = asset["target_subdir"]
        assert not target.startswith("third_party/")
        assert not target.startswith("assets/")
        assert ".." not in Path(target).parts


def test_downloader_script_exists_and_mentions_snapshot_download():
    script = ROOT / "scripts" / "download_safety_assets.py"
    text = script.read_text(encoding="utf-8")
    assert "snapshot_download" in text
    assert "--repo-assets-only" in text
    assert "manifest.aura.json" in text
