#include "dephy_iot/iot.h"

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    struct dephy_iot_config config = {
        .enabled_protocols = 0u
#if defined(CONFIG_DEPHY_IOT_MQTT)
            | DEPHY_IOT_PROTOCOL_MQTT
#endif
#if defined(CONFIG_DEPHY_IOT_MODBUS)
            | DEPHY_IOT_PROTOCOL_MODBUS
#endif
#if defined(CONFIG_DEPHY_IOT_SNMP)
            | DEPHY_IOT_PROTOCOL_SNMP
#endif
    };

    printk("dephy_iot starting\n");
    (void)dephy_iot_init(&config);

    if (dephy_iot_protocol_enabled(DEPHY_IOT_PROTOCOL_MQTT)) {
        printk("dephy_iot mqtt enabled\n");
    }
    if (dephy_iot_protocol_enabled(DEPHY_IOT_PROTOCOL_MODBUS)) {
        printk("dephy_iot modbus enabled\n");
    }
    if (dephy_iot_protocol_enabled(DEPHY_IOT_PROTOCOL_SNMP)) {
        printk("dephy_iot snmp enabled\n");
    }

    return 0;
}

