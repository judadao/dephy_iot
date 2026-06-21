#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
DEPS_JSON="$ROOT_DIR/deps.json"

if command -v jq >/dev/null 2>&1; then
    BOARD=$(jq -r '.build.board // "esp32"' "$DEPS_JSON")
    DEPHY_PATH=$(jq -r '.deps.dephy.path // empty' "$DEPS_JSON")
    DEPHY_WORKSPACE=$(jq -r '.build.dephy_workspace // empty' "$DEPS_JSON")
    EXTRA_MODULES=$(jq -r '.deps | to_entries | map(.value.module_path // .value.path) | join(";")' "$DEPS_JSON")
else
    BOARD=esp32
    DEPHY_PATH=deps/dephy
    DEPHY_WORKSPACE=../dephy/zephyrproject
    EXTRA_MODULES="deps/dephy/boards/esp32;deps/mqtt_min_broker"
fi

EXTRA_MODULES_ABS="$ROOT_DIR"
OLD_IFS=$IFS
IFS=';'
for module_path in $EXTRA_MODULES; do
    EXTRA_MODULES_ABS="$EXTRA_MODULES_ABS;$ROOT_DIR/$module_path"
done
IFS=$OLD_IFS

if [ -n "$DEPHY_WORKSPACE" ] && [ -x "$ROOT_DIR/$DEPHY_WORKSPACE/.venv/bin/west" ]; then
    WEST="$ROOT_DIR/$DEPHY_WORKSPACE/.venv/bin/west"
    WEST_WORKDIR="$ROOT_DIR/$DEPHY_WORKSPACE"
elif command -v west >/dev/null 2>&1; then
    WEST=$(command -v west)
    WEST_WORKDIR=$ROOT_DIR
elif [ -n "$DEPHY_PATH" ] && [ -x "$ROOT_DIR/$DEPHY_PATH/zephyrproject/.venv/bin/west" ]; then
    WEST="$ROOT_DIR/$DEPHY_PATH/zephyrproject/.venv/bin/west"
    WEST_WORKDIR="$ROOT_DIR/$DEPHY_PATH/zephyrproject"
else
    printf 'error: west not found; run ./scripts/sync_deps.sh first\n' >&2
    exit 1
fi

(cd "$WEST_WORKDIR" && "$WEST" build -b "$BOARD" "$ROOT_DIR" \
    -- -DZEPHYR_EXTRA_MODULES="$EXTRA_MODULES_ABS")
