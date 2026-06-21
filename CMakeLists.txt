cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(dephy_iot)

target_sources(app PRIVATE
  src/iot.c
  src/mqtt.c
  src/modbus.c
  src/snmp.c
  src/main.c
)

target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

