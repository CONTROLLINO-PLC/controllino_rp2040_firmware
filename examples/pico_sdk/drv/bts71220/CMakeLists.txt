# example_bts71220
add_executable(example_bts71220)
target_sources(example_bts71220 PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_bts71220 drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_bts71220 1)
pico_enable_stdio_uart(example_bts71220 1)
pico_add_extra_outputs(example_bts71220)
pico_set_program_url(example_bts71220 ${CMAKE_CURRENT_LIST_DIR})