#ifndef DEPHY_IOT_IOT_H
#define DEPHY_IOT_IOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

enum dephy_iot_protocol {
    DEPHY_IOT_PROTOCOL_MQTT = 1u << 0,
    DEPHY_IOT_PROTOCOL_MODBUS = 1u << 1,
    DEPHY_IOT_PROTOCOL_SNMP = 1u << 2,
};

enum dephy_iot_status {
    DEPHY_IOT_OK = 0,
    DEPHY_IOT_ERR_INVALID_ARG = -1,
    DEPHY_IOT_ERR_NOT_ENABLED = -2,
    DEPHY_IOT_ERR_UNSUPPORTED = -3,
};

struct dephy_iot_config {
    uint32_t enabled_protocols;
};

int dephy_iot_init(const struct dephy_iot_config *config);
int dephy_iot_start(uint32_t protocol);
bool dephy_iot_protocol_enabled(uint32_t protocol);
const char *dephy_iot_protocol_name(uint32_t protocol);

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_IOT_H */

