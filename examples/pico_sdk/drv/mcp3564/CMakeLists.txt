# example_mcp3564
add_executable(example_mcp3564)
target_sources(example_mcp3564 PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_mcp3564 neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_mcp3564 1)
pico_enable_stdio_uart(example_mcp3564 1)
pico_add_extra_outputs(example_mcp3564)
pico_set_program_url(example_mcp3564 ${CMAKE_CURRENT_LIST_DIR})
