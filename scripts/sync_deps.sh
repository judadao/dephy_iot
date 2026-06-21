#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
DEPS_JSON="$ROOT_DIR/deps.json"

json_value() {
    jq -r "$1 // empty" "$DEPS_JSON"
}

if ! command -v jq >/dev/null 2>&1; then
    printf 'error: jq is required for dependency sync\n' >&2
    exit 1
fi

mkdir -p "$ROOT_DIR/deps"

jq -r '.deps | keys[]' "$DEPS_JSON" | while IFS= read -r name; do
    path=$(json_value ".deps.$name.path")
    local_path=$(json_value ".deps.$name.local")
    repo=$(json_value ".deps.$name.repo")
    tag=$(json_value ".deps.$name.tag")
    dest="$ROOT_DIR/$path"

    if [ -n "$local_path" ] && [ -d "$ROOT_DIR/$local_path/.git" ]; then
        rm -rf "$dest"
        git clone --quiet "$ROOT_DIR/$local_path" "$dest"
    elif [ ! -d "$dest/.git" ]; then
        git clone --quiet "$repo" "$dest"
    fi

    if [ -n "$tag" ]; then
        (cd "$dest" && git fetch --quiet --tags && git checkout --quiet "$tag")
    fi
done

