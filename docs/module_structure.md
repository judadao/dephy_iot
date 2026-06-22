# dephy_iot Module Structure

`dephy_iot` is a reusable IoT protocol adapter module. It coordinates protocol
selection and adapter boundaries for MQTT, Modbus, and SNMP without owning
product provisioning or deployment flows.

## Public Headers

- `include/dephy_iot/iot.h`: protocol selection, lifecycle, and shared status
  codes.
- `include/dephy_iot/mqtt.h`: MQTT adapter configuration and bounded topic
  formatting.
- `include/dephy_iot/modbus.h`: Modbus adapter configuration, CRC, and RTU
  response parsing helpers.
- `include/dephy_iot/snmp.h`: SNMP adapter configuration.

## Source Layout

- `src/iot.c`: shared protocol enable/start dispatch.
- `src/mqtt.c`: MQTT adapter boundary and broker integration hook.
- `src/modbus.c`: Modbus adapter boundary and backend integration hook.
- `src/snmp.c`: SNMP adapter boundary.
- `src/main.c`: standalone Zephyr sample entry point.

## Dependency Boundary

This module may depend on reusable modules such as `mqtt_min_broker`,
`modbus_zephyr_esp32`, and `dephy`. It must not depend on product repositories.
Product applications consume this module through `deps.json` and call public
headers.

## Validation

- `Makefile.linux test`: Linux unit tests, dependency policy check, and Zephyr
  metadata smoke.
- `scripts/test_deps_policy.sh`: rejects product dependencies in `deps.json`.
- `scripts/test_zephyr_module.sh`: checks required Zephyr metadata.
