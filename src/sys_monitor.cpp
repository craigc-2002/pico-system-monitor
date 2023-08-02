#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#include "sys_monitor.hpp"

void sys_monitor_init(void)
{
    // initialise the GPIO and ADC
    gpio_init(23);                              // GPIO23 connected to PS (Power Save) pin - controls switching supply mode
    gpio_set_dir(23, GPIO_OUT);
    stdio_init_all();
    adc_init();
    adc_gpio_init(29);                          // pin V_sys is connected Pin 29 to pin via /3 voltage divider
    adc_set_temp_sensor_enabled(true);
}

// read adc and convert to voltage
float adc_read_V(void)
{
    uint16_t adc_value = adc_read();
    float adc_voltage = adc_value * (3.3f / (1 << 12));         // convert adc reading to voltage - assuming 3.3V ADC reference
    return adc_voltage;
}

// read the ADC to measure temperature input voltage, then pack them into a struct and return
sys_info get_system_info(void)
{
    gpio_put(23, 1);                                    // set power supply to PWM mode to reduce ripple in ADC readings
                                                                
    adc_select_input(4);                                // set the ADC input to the built in temperature sensor
    float temp_volt = adc_read_V();
    float temp = 27 - ((temp_volt - 0.706) / 0.001721); // convert ADC voltage to temperature
                                                                
    adc_select_input(3);                                // set ADC input to monitor pico V_sys
    float input_voltage = adc_read_V();
    input_voltage *= 3;                                 // V_sys divided by 3 before pin - multiply to get acutal V_sys
                                                                
    // pack values into struct
    sys_info system_info;
    system_info.temp = temp;
    system_info.supply_voltage = input_voltage;

    gpio_put(23, 0);                                    // reset power supply to improve efficiency
    return system_info;
}