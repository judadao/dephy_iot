#!/bin/sh
set -eu

root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"

for path in CMakeLists.txt Kconfig zephyr/CMakeLists.txt zephyr/Kconfig zephyr/module.yml; do
    if [ ! -f "$root/$path" ]; then
        echo "missing $path" >&2
        exit 1
    fi
done

grep -q "name: dephy_iot" "$root/zephyr/module.yml"
grep -q "DEPHY_IOT" "$root/zephyr/Kconfig"

echo "dephy_iot Zephyr metadata OK"
