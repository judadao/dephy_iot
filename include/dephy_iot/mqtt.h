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

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_MQTT_H */

