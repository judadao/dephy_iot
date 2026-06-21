#include "dephy_iot/modbus.h"

#include "dephy_iot/iot.h"

#if defined(CONFIG_DEPHY_IOT_MODBUS_ZEPHYR_ESP32)
#include "modbus_zephyr_esp32/modbus.h"
#endif

static struct dephy_iot_modbus_config modbus_config = {
    .unit_id = 1,
    .baudrate = 115200,
    .tcp_port = 502,
};

int dephy_iot_modbus_init(const struct dephy_iot_modbus_config *config)
{
    if (config != 0) {
        modbus_config = *config;
    }

    return DEPHY_IOT_OK;
}

int dephy_iot_modbus_start(void)
{
#if defined(CONFIG_DEPHY_IOT_MODBUS)
#if defined(CONFIG_DEPHY_IOT_MODBUS_ZEPHYR_ESP32)
    struct modbus_zephyr_esp32_config backend_config = {
        .mode = MODBUS_ZEPHYR_ESP32_MODE_RTU,
        .unit_id = modbus_config.unit_id,
        .baudrate = modbus_config.baudrate,
        .tcp_port = modbus_config.tcp_port,
    };
    int rc = modbus_zephyr_esp32_init(&backend_config);
    if (rc != MODBUS_ZEPHYR_ESP32_OK) {
        return DEPHY_IOT_ERR_INVALID_ARG;
    }
    return modbus_zephyr_esp32_start() == MODBUS_ZEPHYR_ESP32_OK
        ? DEPHY_IOT_OK
        : DEPHY_IOT_ERR_UNSUPPORTED;
#else
    return DEPHY_IOT_OK;
#endif
#else
    return DEPHY_IOT_ERR_NOT_ENABLED;
#endif
}
