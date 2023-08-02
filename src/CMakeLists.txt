cmake_minimum_required(VERSION 3.13)

file(GLOB FILES *.cpp *.hpp)
add_library(pico-sys-monitor-lib ${FILES})
target_link_libraries(pico-sys-monitor-lib pico_stdlib hardware_adc hardware_gpio)
target_include_directories(pico-sys-monitor-lib PUBLIC ../include/pico-sys-monitor-lib)
