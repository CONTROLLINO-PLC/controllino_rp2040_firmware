# neo_drivers
add_library(neo_drivers INTERFACE)
target_sources(neo_drivers INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/src/ad56x4.c
    ${CMAKE_CURRENT_LIST_DIR}/src/bts71220.c
    ${CMAKE_CURRENT_LIST_DIR}/src/mcp356x.c
    ${CMAKE_CURRENT_LIST_DIR}/src/cy8c95xx.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wsen_temp.c
)
target_include_directories(neo_drivers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)