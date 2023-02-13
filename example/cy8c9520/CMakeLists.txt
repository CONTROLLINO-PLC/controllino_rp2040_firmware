# example_cy8c95xx
add_executable(example_cy8c95xx)
target_sources(example_cy8c95xx PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../src/hw_rp2040.c
)
target_link_libraries(example_cy8c95xx neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_cy8c95xx 1)
pico_enable_stdio_uart(example_cy8c95xx 1)
pico_add_extra_outputs(example_cy8c95xx)
pico_set_program_url(example_cy8c95xx ${CMAKE_CURRENT_LIST_DIR})
