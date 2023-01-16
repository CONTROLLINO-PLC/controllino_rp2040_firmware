add_library(cy8C95xx_driver INTERFACE)

target_sources(cy8C95xx_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/cy8C95xx.c
)

target_include_directories(cy8C95xx_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
