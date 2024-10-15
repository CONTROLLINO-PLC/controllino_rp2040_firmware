# drivers
add_library(drivers INTERFACE)
target_sources(drivers INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/ad5664.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/bts71220.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/mcp3564.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/cy8c9520.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/wsen_temp.c
    ${CMAKE_CURRENT_LIST_DIR}/hw_rp2/src/hw_rp2_gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/hw_rp2/src/hw_rp2_i2c.c
    ${CMAKE_CURRENT_LIST_DIR}/hw_rp2/src/hw_rp2_spi.c
    ${CMAKE_CURRENT_LIST_DIR}/hw_rp2/src/hw_rp2_timing.c

)
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/drivers/include)