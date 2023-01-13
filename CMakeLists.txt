cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId}  C CXX) 

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(
    -Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-maybe-uninitialized
)

add_definitions(
    -DCO_DRIVER_CUSTOM   # include CO_driver_custom.h in CO_driver_target to add custom configurations
)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(firmware)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/cy8C95xx.c
)

target_sources(firmware PUBLIC ${SOURCES})

target_include_directories(firmware PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(firmware PUBLIC pico_stdlib hardware_i2c hardware_pio)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 1)

pico_add_extra_outputs(firmware)

pico_set_program_url(firmware ${CMAKE_CURRENT_LIST_DIR})
