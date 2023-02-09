add_library(hw_platform_driver INTERFACE)

target_sources(hw_platform_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/rp2040/hw_rp2040.c
)

target_include_directories(hw_platform_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
