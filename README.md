# dephy_iot

Reusable IoT protocol adapter module for Dephy and Zephyr projects.

`dephy_iot` is the protocol coordination layer. It keeps MQTT, Modbus, and SNMP
adapter boundaries reusable so product repos can choose which protocols to
enable without copying protocol glue into product code.

## Why This Exists

- Products need consistent protocol startup and configuration rules.
- MQTT topic formatting, Modbus parsing, and SNMP boundaries should be shared.
- Protocol adapters should be testable on Linux and buildable as Zephyr modules.
- Product-specific provisioning stays in product repos; reusable protocol logic
  stays here.

## Normal Flow

1. Pin this module in a product `deps.json`.
2. Sync it into the product `deps/` directory.
3. Enable only the protocol features the product needs.
4. Fill the adapter configs from product configuration or provisioning.
5. Start the selected protocol adapters through the public API.

Linux feature flags:

```sh
make -f Makefile.linux MQTT=1
make -f Makefile.linux MODBUS=1
make -f Makefile.linux SNMP=1
```

Zephyr configuration:

```conf
CONFIG_DEPHY_IOT=y
CONFIG_DEPHY_IOT_MQTT=y
CONFIG_DEPHY_IOT_MODBUS=y
CONFIG_DEPHY_IOT_SNMP=n
```

## How It Works

The module exposes small, bounded adapter APIs. MQTT helpers format topics and
hold broker connection settings. Modbus helpers validate config, compute CRC16,
and parse RTU responses. SNMP currently provides a placeholder boundary so the
dependency and build shape are ready before a full implementation lands.

A dependency policy check rejects product-to-product dependencies. Reusable
modules may depend on other reusable modules, but a product app should not
become a dependency of another product.

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

## TODO

TODO state is tracked in `docs/todo.yaml` and summarized in `docs/todo.md`.
