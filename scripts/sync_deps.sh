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
    version=$(json_value ".deps.$name.version")
    dest="$ROOT_DIR/$path"

    if [ -n "$local_path" ] && [ -d "$ROOT_DIR/$local_path/.git" ]; then
        rm -rf "$dest"
        git clone --quiet "$ROOT_DIR/$local_path" "$dest"
    elif [ ! -d "$dest/.git" ]; then
        git clone --quiet "$repo" "$dest"
    fi

    if [ -n "$version" ]; then
        (cd "$dest" && git fetch --quiet --tags && git checkout --quiet "$version")
    fi
done

dephy_path=$(json_value '.deps.dephy.path')
dephy_profile=$(json_value '.deps.dephy.profile')
if [ -n "$dephy_path" ]; then
    if [ -z "$dephy_profile" ]; then
        dephy_profile=esp32
    fi
    dephy_sync="$ROOT_DIR/$dephy_path/boards/$dephy_profile/scripts/sync_zephyr_modules.sh"
    if [ -x "$dephy_sync" ]; then
        "$dephy_sync"
    else
        printf 'warning: Dephy sync script not found: %s\n' "$dephy_sync" >&2
    fi
fi
