# example_ad5664
add_executable(example_ad5664)
target_sources(example_ad5664 PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_link_libraries(example_ad5664 neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_ad5664 1)
pico_enable_stdio_uart(example_ad5664 1)
pico_add_extra_outputs(example_ad5664)
pico_set_program_url(example_ad5664 ${CMAKE_CURRENT_LIST_DIR})