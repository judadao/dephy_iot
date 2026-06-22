#include "dephy_iot/mqtt.h"

#include "dephy_iot/iot.h"

#include <stdio.h>

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

int dephy_iot_mqtt_format_topic(char *out,
                                unsigned int out_size,
                                const char *prefix,
                                const char *device,
                                const char *stream)
{
    int written;

    if (out == 0 || out_size == 0 || prefix == 0 || device == 0 || stream == 0) {
        return DEPHY_IOT_ERR_INVALID_ARG;
    }

    written = snprintf(out, out_size, "%s/%s/%s", prefix, device, stream);
    if (written < 0 || (unsigned int)written >= out_size) {
        out[0] = '\0';
        return DEPHY_IOT_ERR_INVALID_ARG;
    }

    return written;
}
