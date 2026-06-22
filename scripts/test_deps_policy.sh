#!/bin/sh
set -eu

root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"

python3 - "$root/deps.json" <<'PY'
import json
import sys
from pathlib import Path

deps = json.loads(Path(sys.argv[1]).read_text(encoding="utf-8")).get("deps", {})
bad = []
for name, dep in deps.items():
    local = dep.get("local")
    repo_json = Path(sys.argv[1]).parent / local / "repo.json" if local else None
    if repo_json and repo_json.exists():
        repo_type = json.loads(repo_json.read_text(encoding="utf-8")).get("repo_type")
        if repo_type in {"product", "product_template"}:
            bad.append(f"{name}:{repo_type}")

if bad:
    print("product dependencies are not allowed: " + ", ".join(bad), file=sys.stderr)
    sys.exit(1)

print("dependency policy OK")
PY
