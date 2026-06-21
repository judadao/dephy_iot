#include "dephy_iot/modbus.h"

#include "dephy_iot/iot.h"

static struct dephy_iot_modbus_config modbus_config = {
    .unit_id = 1,
};

int dephy_iot_modbus_init(const struct dephy_iot_modbus_config *config)
{
    if (config != 0) {
        modbus_config = *config;
    }

    return DEPHY_IOT_OK;
}

int dephy_iot_modbus_start(void)
{
#if defined(CONFIG_DEPHY_IOT_MODBUS)
    (void)modbus_config;
    return DEPHY_IOT_OK;
#else
    return DEPHY_IOT_ERR_NOT_ENABLED;
#endif
}

