#ifndef _AIOT_TIMER_H_
#define _AIOT_TIMER_H_

#include <timer.h>
#include "appdatatypedef.h"

typedef struct {
    struct timer_list timer;
    unsigned long jiffies;
    appbool alivable;
    void (*fun)(void* para); 
}mqtt_timer;

void start_time_task(mqtt_timer *mqtimer, int times, void (*fun)(void* para));
void stop_time_task(mqtt_timer *mqtimer);
#endif
