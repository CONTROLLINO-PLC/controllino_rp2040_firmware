# neo_drivers
add_library(neo_drivers INTERFACE)
target_sources(neo_drivers INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/ad56x4.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/bts71220.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/mcp356x.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/cy8c95xx.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/src/wsen_temp.c
    ${CMAKE_CURRENT_LIST_DIR}/hw_rp2040/src/hw_rp2040.c
)
target_include_directories(neo_drivers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/drivers/include)