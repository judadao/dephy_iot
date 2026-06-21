# Repository Guidelines

## Project Structure

`dephy_iot` is a reusable IoT protocol module collection. Public APIs live in
`include/dephy_iot/`, portable implementation lives in `src/`, Zephyr module
metadata lives in `zephyr/`, Linux tests live in `tests/`, and build helpers
live in `scripts/`.

## Development Model

Keep protocol integrations reusable. MQTT, Modbus, and SNMP should each expose
a small public adapter API and be individually controlled by Kconfig symbols and
Linux build flags. Product-specific workflows should live in product
repositories, not in this module.

This repository supports two Zephyr paths:

- Standard Zephyr module use through `ZEPHYR_EXTRA_MODULES`.
- Dephy-led builds that use the Dephy-managed Zephyr workspace and board
  support modules.

## Build And Test

Linux:

```bash
make -f Makefile.linux
make -f Makefile.linux test
```

Zephyr through Dephy:

```bash
./scripts/sync_deps.sh
./scripts/build_zephyr.sh
```

## Style

Use C11, four-space indentation, snake_case symbols, and uppercase config
macros such as `CONFIG_DEPHY_IOT_MQTT`. Keep module APIs stable and small.

