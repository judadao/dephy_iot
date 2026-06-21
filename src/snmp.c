#include "dephy_iot/snmp.h"

#include "dephy_iot/iot.h"

static struct dephy_iot_snmp_config snmp_config = {
    .community = "public",
};

int dephy_iot_snmp_init(const struct dephy_iot_snmp_config *config)
{
    if (config != 0) {
        snmp_config = *config;
    }

    return DEPHY_IOT_OK;
}

int dephy_iot_snmp_start(void)
{
#if defined(CONFIG_DEPHY_IOT_SNMP)
    (void)snmp_config;
    return DEPHY_IOT_OK;
#else
    return DEPHY_IOT_ERR_NOT_ENABLED;
#endif
}

