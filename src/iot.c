#include "dephy_iot/iot.h"

#include "dephy_iot/modbus.h"
#include "dephy_iot/mqtt.h"
#include "dephy_iot/snmp.h"

static uint32_t active_protocols;

int dephy_iot_init(const struct dephy_iot_config *config)
{
    if (config == 0) {
        return DEPHY_IOT_ERR_INVALID_ARG;
    }

    active_protocols = config->enabled_protocols;
    return DEPHY_IOT_OK;
}

int dephy_iot_start(uint32_t protocol)
{
    if (!dephy_iot_protocol_enabled(protocol)) {
        return DEPHY_IOT_ERR_NOT_ENABLED;
    }

    switch (protocol) {
    case DEPHY_IOT_PROTOCOL_MQTT:
        return dephy_iot_mqtt_start();
    case DEPHY_IOT_PROTOCOL_MODBUS:
        return dephy_iot_modbus_start();
    case DEPHY_IOT_PROTOCOL_SNMP:
        return dephy_iot_snmp_start();
    default:
        return DEPHY_IOT_ERR_INVALID_ARG;
    }
}

bool dephy_iot_protocol_enabled(uint32_t protocol)
{
    return protocol != 0u && (active_protocols & protocol) == protocol;
}

const char *dephy_iot_protocol_name(uint32_t protocol)
{
    switch (protocol) {
    case DEPHY_IOT_PROTOCOL_MQTT:
        return "mqtt";
    case DEPHY_IOT_PROTOCOL_MODBUS:
        return "modbus";
    case DEPHY_IOT_PROTOCOL_SNMP:
        return "snmp";
    default:
        return "unknown";
    }
}

