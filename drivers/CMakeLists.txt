# cy8c95xx_driver
add_library(cy8c95xx_driver INTERFACE)
target_sources(cy8c95xx_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/cy8c95xx.c)
target_include_directories(cy8c95xx_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
 
# ad56x4_driver
add_library(ad56x4_driver INTERFACE)
target_sources(ad56x4_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/ad56x4.c)
target_include_directories(ad56x4_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# mcp356x_driver
add_library(mcp356x_driver INTERFACE)
target_sources(mcp356x_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/mcp356x.c)
target_include_directories(mcp356x_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# wsen_temp_driver
add_library(wsen_temp_driver INTERFACE)
target_sources(wsen_temp_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/wsen_temp.c)
target_include_directories(wsen_temp_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)