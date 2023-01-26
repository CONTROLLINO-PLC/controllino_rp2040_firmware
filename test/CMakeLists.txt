# test_cy8c95xx
add_executable(test_cy8c95xx)
target_sources(test_cy8c95xx PUBLIC ${CMAKE_CURRENT_LIST_DIR}/test_cy8c95xx.c)
target_link_libraries(test_cy8c95xx platform_rp2040_lib cy8c95xx_driver pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(test_cy8c95xx 1)
pico_enable_stdio_uart(test_cy8c95xx 1)
pico_add_extra_outputs(test_cy8c95xx)
pico_set_program_url(test_cy8c95xx ${CMAKE_CURRENT_LIST_DIR})
 
# test_ad56x4
add_executable(test_ad56x4)
target_sources(test_ad56x4 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/test_ad56x4.c)
target_link_libraries(test_ad56x4 platform_rp2040_lib cy8c95xx_driver ad56x4_driver pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(test_ad56x4 1)
pico_enable_stdio_uart(test_ad56x4 1)
pico_add_extra_outputs(test_ad56x4)
pico_set_program_url(test_ad56x4 ${CMAKE_CURRENT_LIST_DIR})

# test_mcp356x
add_executable(test_mcp356x)
target_sources(test_mcp356x PUBLIC ${CMAKE_CURRENT_LIST_DIR}/test_mcp356x.c)
target_link_libraries(test_mcp356x platform_rp2040_lib cy8c95xx_driver mcp356x_driver pico_stdlib hardware_i2c hardware_spi hardware_pio)
pico_enable_stdio_usb(test_mcp356x 1)
pico_enable_stdio_uart(test_mcp356x 1)
pico_add_extra_outputs(test_mcp356x)
pico_set_program_url(test_mcp356x ${CMAKE_CURRENT_LIST_DIR})