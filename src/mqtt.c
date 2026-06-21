#include "dephy_iot/mqtt.h"

#include "dephy_iot/iot.h"

#if defined(CONFIG_DEPHY_IOT_MQTT_MIN_BROKER)
#include "broker.h"
#endif

static struct dephy_iot_mqtt_config mqtt_config = {
    .bind_host = "0.0.0.0",
    .port = 1883,
};

int dephy_iot_mqtt_init(const struct dephy_iot_mqtt_config *config)
{
    if (config != 0) {
        mqtt_config = *config;
    }

    return DEPHY_IOT_OK;
}

int dephy_iot_mqtt_start(void)
{
#if defined(CONFIG_DEPHY_IOT_MQTT)
    (void)mqtt_config;
#if defined(CONFIG_DEPHY_IOT_MQTT_MIN_BROKER)
    return broker_init();
#else
    return DEPHY_IOT_OK;
#endif
#else
    return DEPHY_IOT_ERR_NOT_ENABLED;
#endif
}
