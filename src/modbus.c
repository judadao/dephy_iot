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

unsigned short dephy_iot_modbus_crc16(const unsigned char *data,
                                      unsigned int len)
{
    unsigned short crc = 0xffffu;
    unsigned int i;
    unsigned int bit;

    if (data == 0 && len != 0u) {
        return 0u;
    }

    for (i = 0; i < len; ++i) {
        crc ^= data[i];
        for (bit = 0; bit < 8u; ++bit) {
            if ((crc & 0x0001u) != 0u) {
                crc = (unsigned short)((crc >> 1) ^ 0xa001u);
            } else {
                crc = (unsigned short)(crc >> 1);
            }
        }
    }

    return crc;
}

int dephy_iot_modbus_parse_rtu_response(const unsigned char *frame,
                                        unsigned int len,
                                        struct dephy_iot_modbus_response *out)
{
    unsigned short expected_crc;
    unsigned short actual_crc;

    if (frame == 0 || out == 0 || len < 5u) {
        return DEPHY_IOT_ERR_INVALID_ARG;
    }

    expected_crc = dephy_iot_modbus_crc16(frame, len - 2u);
    actual_crc = (unsigned short)(frame[len - 2u] | ((unsigned short)frame[len - 1u] << 8));
    if (expected_crc != actual_crc) {
        return DEPHY_IOT_ERR_INVALID_ARG;
    }

    out->unit_id = frame[0];
    out->function = frame[1];
    out->payload = &frame[2];
    out->payload_len = len - 4u;

    if ((out->function & 0x80u) != 0u) {
        return DEPHY_IOT_ERR_UNSUPPORTED;
    }

    return DEPHY_IOT_OK;
}
