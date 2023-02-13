# example_ad56x4
add_executable(example_ad56x4)
target_sources(example_ad56x4 PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../src/hw_rp2040.c
)
target_link_libraries(example_ad56x4 neo_drivers pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(example_ad56x4 1)
pico_enable_stdio_uart(example_ad56x4 1)
pico_add_extra_outputs(example_ad56x4)
pico_set_program_url(example_ad56x4 ${CMAKE_CURRENT_LIST_DIR})