# example_wsen_temp
add_executable(example_wsen_temp)
target_sources(example_wsen_temp PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_wsen_temp neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_wsen_temp 1)
pico_enable_stdio_uart(example_wsen_temp 1)
pico_add_extra_outputs(example_wsen_temp)
pico_set_program_url(example_wsen_temp ${CMAKE_CURRENT_LIST_DIR})
