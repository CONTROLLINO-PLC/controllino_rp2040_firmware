# example_mcp356x
add_executable(example_mcp356x)
target_sources(example_mcp356x PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_mcp356x neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_mcp356x 1)
pico_enable_stdio_uart(example_mcp356x 1)
pico_add_extra_outputs(example_mcp356x)
pico_set_program_url(example_mcp356x ${CMAKE_CURRENT_LIST_DIR})
