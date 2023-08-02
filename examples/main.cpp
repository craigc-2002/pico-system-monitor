#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#include "sys_monitor.hpp"

int main()
{
    sys_monitor_init();

    while (true)
    {
        sys_info system_info = get_system_info();

        printf("Temp: %.2f *C\tVoltage: %.2f V\n", system_info.temp, system_info.supply_voltage);
        sleep_ms(1000);
    }
}

