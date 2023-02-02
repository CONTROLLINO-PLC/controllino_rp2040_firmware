add_library(platform_rp2040_lib INTERFACE)

target_sources(platform_rp2040_lib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/hw_platform.c
)

target_include_directories(platform_rp2040_lib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
