# openai-privacy-filter runtime asset

This directory contains only the manifest template for the default Token
Classification Model candidate. Model weights and tokenizer artifacts are
runtime assets and must be installed under:

```text
~/.aura/token-classification-models/openai-privacy-filter/
```

AURA core invokes the Python venv runner as an external subprocess and consumes
JSON findings. The model runtime is not linked into `aura_core`.
