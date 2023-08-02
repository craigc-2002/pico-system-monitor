add_executable(system_monitor
	main.cpp
)

target_link_libraries(system_monitor pico-sys-monitor-lib pico_stdlib hardware_adc hardware_gpio)

pico_enable_stdio_uart(system_monitor 0)
pico_enable_stdio_usb(system_monitor 1)

pico_add_extra_outputs(system_monitor)