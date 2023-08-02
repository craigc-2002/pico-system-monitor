#ifndef SYS_MONITOR_HPP
#define SYS_MONITOR_HPP

struct sys_info
{
    float temp;
    float supply_voltage;
};

float adc_read_V(void);
sys_info get_system_info(void);

#endif
