# dephy_iot

Reusable IoT protocol adapter module for Dephy and Zephyr projects.

## Overview

`dephy_iot` coordinates protocol adapter boundaries for MQTT, Modbus, and SNMP.
Products enable the protocols they need while keeping reusable protocol glue out
of product-only code.

## Key Value

- Shared protocol startup and config shape.
- MQTT topic helpers and bounded config handling.
- Modbus CRC and RTU response parsing.
- Dependency policy that rejects product-to-product dependencies.

## How To Use

```sh
make -f Makefile.linux test
make -f Makefile.linux MQTT=1
make -f Makefile.linux MODBUS=1
./scripts/build_zephyr.sh
```

```conf
CONFIG_DEPHY_IOT=y
CONFIG_DEPHY_IOT_MQTT=y
CONFIG_DEPHY_IOT_MODBUS=y
```

## Simple Principle

Products own provisioning and workflows. This module owns reusable protocol
adapter boundaries.

## Docs

- `docs/todo.md`: current TODO summary.
