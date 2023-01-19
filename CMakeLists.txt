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
    -Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
)

add_definitions(
    -DPLATFORM_RP2040 # RP2040 as compile platform
)

add_executable(firmware)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cy8c95xx)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/rp2040/main.c
    ${CMAKE_CURRENT_LIST_DIR}/rp2040/cy8c95xx_rp2040.c
)

target_sources(firmware PUBLIC ${SOURCES})

target_include_directories(firmware PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/rp2040
)

target_link_libraries(firmware cy8c95xx_driver pico_stdlib hardware_i2c hardware_pio)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 1)

pico_add_extra_outputs(firmware)

pico_set_program_url(firmware ${CMAKE_CURRENT_LIST_DIR})

