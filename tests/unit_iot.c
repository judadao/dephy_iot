#include "dephy_iot/iot.h"
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

    return 0;
}

