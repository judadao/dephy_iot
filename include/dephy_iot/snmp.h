#ifndef DEPHY_IOT_SNMP_H
#define DEPHY_IOT_SNMP_H

#ifdef __cplusplus
extern "C" {
#endif

struct dephy_iot_snmp_config {
    const char *community;
};

int dephy_iot_snmp_init(const struct dephy_iot_snmp_config *config);
int dephy_iot_snmp_start(void);

#ifdef __cplusplus
}
#endif

#endif /* DEPHY_IOT_SNMP_H */

