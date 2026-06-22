# dephy_iot

Reusable IoT protocol adapter module for Dephy and Zephyr projects.

This repo provides a small protocol coordination layer for MQTT, Modbus, and
SNMP adapter boundaries. Product-specific provisioning and workflows belong in
product repos; reusable protocol glue belongs here.

## Current Capabilities

- Protocol enable/start dispatch through `include/dephy_iot/iot.h`.
- MQTT adapter config and bounded topic formatting.
- Modbus adapter config, CRC16 helper, and RTU response parser.
- SNMP adapter placeholder boundary.
- Dependency policy check that rejects product-to-product dependencies.
- Zephyr module metadata smoke test.

## Layout

```text
include/dephy_iot/   public headers
src/                 portable protocol adapter implementation
scripts/             deps policy, Zephyr smoke, sync/build helpers
tests/               Linux unit tests
zephyr/              Zephyr module metadata
deps.json            pinned reusable dependencies
repo.json            repo_type: module
```

## Commands

```sh
make -f Makefile.linux
make -f Makefile.linux test
./scripts/sync_deps.sh
./scripts/build_zephyr.sh
```

Optional Linux feature flags:

```sh
make -f Makefile.linux MQTT=1
make -f Makefile.linux MODBUS=1
make -f Makefile.linux SNMP=1
```

## Zephyr

Add this repo to `ZEPHYR_EXTRA_MODULES`, then enable the protocol options:

```conf
CONFIG_DEPHY_IOT=y
CONFIG_DEPHY_IOT_MQTT=y
CONFIG_DEPHY_IOT_MODBUS=y
CONFIG_DEPHY_IOT_SNMP=n
```

## Dependency Boundary

Allowed dependencies are reusable modules such as `dephy`, `mqtt_min_broker`,
and `modbus_zephyr_esp32`. Product repositories must not be dependencies.

## TODO

TODO state is tracked in `docs/todo.yaml` and summarized in `docs/todo.md`.
