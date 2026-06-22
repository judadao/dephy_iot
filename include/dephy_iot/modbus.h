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

struct dephy_iot_modbus_response {
    unsigned char unit_id;
    unsigned char function;
    const unsigned char *payload;
    unsigned int payload_len;
};

int dephy_iot_modbus_init(const struct dephy_iot_modbus_config *config);
int dephy_iot_modbus_start(void);
unsigned short dephy_iot_modbus_crc16(const unsigned char *data,
                                      unsigned int len);
int dephy_iot_modbus_parse_rtu_response(const unsigned char *frame,
                                        unsigned int len,
                                        struct dephy_iot_modbus_response *out);

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_MODBUS_H */
