#ifndef DEPHY_IOT_MQTT_H
#define DEPHY_IOT_MQTT_H

#ifdef __cplusplus
extern "C" {
#endif

struct dephy_iot_mqtt_config {
    const char *bind_host;
    unsigned short port;
};

int dephy_iot_mqtt_init(const struct dephy_iot_mqtt_config *config);
int dephy_iot_mqtt_start(void);
int dephy_iot_mqtt_format_topic(char *out,
                                unsigned int out_size,
                                const char *prefix,
                                const char *device,
                                const char *stream);

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_MQTT_H */
