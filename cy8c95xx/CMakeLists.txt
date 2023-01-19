add_library(cy8c95xx_driver INTERFACE)

target_sources(cy8c95xx_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/cy8c95xx.c
)

target_include_directories(cy8c95xx_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
