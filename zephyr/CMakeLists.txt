if(CONFIG_DEPHY_IOT)
  zephyr_library_named(dephy_iot)

  zephyr_library_sources(
    ../src/iot.c
    ../src/mqtt.c
    ../src/modbus.c
    ../src/snmp.c
  )

  zephyr_library_include_directories(../include)
  zephyr_include_directories(../include)
endif()
