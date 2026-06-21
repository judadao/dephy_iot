#ifndef DEPHY_IOT_MODBUS_H
#define DEPHY_IOT_MODBUS_H

#ifdef __cplusplus
extern "C" {
#endif

struct dephy_iot_modbus_config {
    unsigned int unit_id;
    unsigned int baudrate;
    unsigned short tcp_port;
};

int dephy_iot_modbus_init(const struct dephy_iot_modbus_config *config);
int dephy_iot_modbus_start(void);

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_MODBUS_H */
