# dephy_iot

Reusable IoT protocol adapters for Dephy and Zephyr projects.

This repository is intended to collect protocol modules behind one small public
API while keeping each protocol independently enabled:

- MQTT through `mqtt_min_broker`
- Modbus through `modbus_zephyr_esp32`, planned
- SNMP, planned

It supports two build modes:

1. **Linux development build** with `Makefile.linux` for fast compile and unit
   testing.
2. **Zephyr module build** with standard `ZEPHYR_EXTRA_MODULES`, plus helper
   scripts that build through the Dephy-managed Zephyr workspace.

## Layout

```text
dephy_iot/
├── include/dephy_iot/     # public module APIs
├── src/                   # portable protocol adapter implementation
├── zephyr/                # Zephyr module metadata, CMake, Kconfig
├── tests/                 # Linux unit tests
├── scripts/               # dependency sync and Dephy-led build helpers
├── deps.json              # local and remote dependency pins
└── Makefile.linux         # Linux development build
```

## Linux

```bash
make -f Makefile.linux
make -f Makefile.linux test
```

Build flags:

```bash
make -f Makefile.linux MQTT=1
make -f Makefile.linux MODBUS=1
make -f Makefile.linux SNMP=1
```

## Zephyr

As a normal Zephyr module, add this repository to `ZEPHYR_EXTRA_MODULES` and
enable the protocol options you need:

```text
CONFIG_DEPHY_IOT=y
CONFIG_DEPHY_IOT_MQTT=y
CONFIG_DEPHY_IOT_MODBUS=n
CONFIG_DEPHY_IOT_SNMP=n
```

For Dephy-led builds, sync the pinned dependencies and build the sample app.
Dependencies are materialized into `deps/`; build scripts consume dependency
source, headers, Zephyr CMake metadata, and the Dephy-managed Zephyr workspace
from that directory:

```bash
./scripts/sync_deps.sh
./scripts/build_zephyr.sh
```

The default board is read from `deps.json` and is currently
`esp32_devkitc/esp32/procpu`.

`deps.json` separates the Dephy profile from the Zephyr target:

- `deps.dephy.profile`: Dephy profile directory, currently `esp32`
- `deps.dephy.module_path`: Zephyr module path, currently
  `deps/dephy/boards/esp32`
- `build.board`: Zephyr target passed to `west build`, currently
  `esp32_devkitc/esp32/procpu`
- `build.dephy_workspace`: local Zephyr workspace, currently
  `deps/dephy/zephyrproject`

`modbus_zephyr_esp32` is already declared as an optional dependency. Its remote
repository is currently empty, so `scripts/build_zephyr.sh` skips it until it
contains Zephyr module metadata such as `zephyr/module.yml`.
