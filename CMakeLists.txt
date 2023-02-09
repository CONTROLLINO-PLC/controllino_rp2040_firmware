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

# add_definitions(
#     -DPLATFORM_RP2040
# )

add_subdirectory(platform) # hardware platform abstraction
add_subdirectory(drivers) # Diferent chip drivers
add_subdirectory(test) # Test examples for each driver

