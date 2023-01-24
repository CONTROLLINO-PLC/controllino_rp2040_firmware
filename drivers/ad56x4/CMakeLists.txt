add_library(ad56x4_driver INTERFACE)
target_sources(ad56x4_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/ad56x4.c)
target_include_directories(ad56x4_driver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
