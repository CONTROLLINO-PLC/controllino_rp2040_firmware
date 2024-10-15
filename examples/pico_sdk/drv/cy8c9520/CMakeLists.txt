# example_cy8c9520
add_executable(example_cy8c9520)
target_sources(example_cy8c9520 PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_cy8c9520 drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_cy8c9520 1)
pico_enable_stdio_uart(example_cy8c9520 1)
pico_add_extra_outputs(example_cy8c9520)
pico_set_program_url(example_cy8c9520 ${CMAKE_CURRENT_LIST_DIR})
