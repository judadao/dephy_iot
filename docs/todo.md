# TODO

Source of truth: `docs/todo.yaml`. Update YAML before starting or completing work.

## repo

- [x] Add docs/todo.yaml so dephy_iot is tracked globally.
- [ ] Decide whether dephy_iot is a reusable module or product and update repo.json and docs consistently.
- [ ] Align layout, docs, tests, and Zephyr metadata with the applicable golden sample.
- [ ] Refactor repository identity and layout until the applicable golden structure audit passes.

## architecture

- [ ] Document ownership boundaries between dephy_iot, dephy_industrial_io, and modbus_zephyr_esp32.

## validation

- [ ] Add dependency sync validation that rejects product-to-product dependencies.
- [ ] Add focused unit coverage for Modbus frame parsing, bad CRC, timeout, and exception responses.

## performance

- [ ] Review MQTT buffer sizes and add coverage for payload truncation or bounded formatting behavior.
