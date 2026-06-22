#include "dephy_iot/iot.h"
#include "dephy_iot/modbus.h"
#include "dephy_iot/mqtt.h"

#include <stdio.h>

#define ASSERT(cond, msg)                                                     \
    do {                                                                      \
        if (!(cond)) {                                                        \
            printf("FAIL: %s\n", msg);                                       \
            return 1;                                                         \
        }                                                                     \
        printf("PASS: %s\n", msg);                                           \
    } while (0)

int main(void)
{
    char topic[64];
    struct dephy_iot_config config = {
        .enabled_protocols = DEPHY_IOT_PROTOCOL_MQTT,
    };

    ASSERT(dephy_iot_init(&config) == DEPHY_IOT_OK, "init accepts config");
    ASSERT(dephy_iot_protocol_enabled(DEPHY_IOT_PROTOCOL_MQTT),
           "mqtt is enabled");
    ASSERT(!dephy_iot_protocol_enabled(DEPHY_IOT_PROTOCOL_MODBUS),
           "modbus is disabled");
    ASSERT(dephy_iot_start(DEPHY_IOT_PROTOCOL_MODBUS) ==
               DEPHY_IOT_ERR_NOT_ENABLED,
           "disabled protocol does not start");
    ASSERT(dephy_iot_mqtt_init(0) == DEPHY_IOT_OK,
           "mqtt accepts default config");
    ASSERT(dephy_iot_start(DEPHY_IOT_PROTOCOL_MQTT) == DEPHY_IOT_OK,
           "enabled mqtt starts");
    ASSERT(dephy_iot_mqtt_format_topic(topic, sizeof(topic), "site/a", "node-1", "state") == 19,
           "mqtt topic formatter returns length");
    ASSERT(dephy_iot_mqtt_format_topic(topic, 8, "site/a", "node-1", "state") ==
               DEPHY_IOT_ERR_INVALID_ARG,
           "mqtt topic formatter rejects truncation");
    {
        const unsigned char req[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02 };
        ASSERT(dephy_iot_modbus_crc16(req, sizeof(req)) == 0x0bc4,
               "modbus crc16 matches known frame");
    }
    {
        const unsigned char frame[] = { 0x01, 0x03, 0x02, 0x00, 0x2a, 0x39, 0x9b };
        struct dephy_iot_modbus_response response;
        ASSERT(dephy_iot_modbus_parse_rtu_response(frame, sizeof(frame), &response) ==
                   DEPHY_IOT_OK,
               "modbus parser accepts valid response");
        ASSERT(response.unit_id == 1 && response.function == 3 &&
                   response.payload_len == 3,
               "modbus parser exposes response header and payload");
    }
    {
        const unsigned char bad_crc[] = { 0x01, 0x03, 0x02, 0x00, 0x2a, 0x00, 0x00 };
        struct dephy_iot_modbus_response response;
        ASSERT(dephy_iot_modbus_parse_rtu_response(bad_crc, sizeof(bad_crc), &response) ==
                   DEPHY_IOT_ERR_INVALID_ARG,
               "modbus parser rejects bad crc");
    }

    return 0;
}
