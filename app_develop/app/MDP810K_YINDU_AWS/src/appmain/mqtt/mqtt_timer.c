#include "mqtt_timer.h"
#include "logger.h"
#include "appsys.h"
#include <syscall.h>

static unsigned long calc_expires(int timerJiffies)
{
    return syscall_get_tick_count() + timerJiffies;
}


static void time_callback(unsigned long para)
{	
	mqtt_timer *mqtimer = (mqtt_timer *)para;

    logger_debug("%s \r\n", __func__);

	if(NULL != mqtimer && NULL != mqtimer->fun){
		mqtimer->fun(mqtimer);

		logger_debug("mqtimer->jiffies = %d \r\n", mqtimer->jiffies);
		if (mqtimer->alivable) {
        	mod_timer(&mqtimer->timer, calc_expires(mqtimer->jiffies));
   		}
	}
}

/**
 * @brief 关闭定时器
 * 
 * @param mqtimer 
 */
void stop_time_task(mqtt_timer *mqtimer)
{
	logger_debug("%s\r\n", __func__);

	if(NULL == mqtimer){
		return;
	}

	while(!timer_pending(&mqtimer->timer)) {
        app_pos_msleep(10);
    }
    del_timer(&mqtimer->timer);
	logger_debug("%s\r\n", __func__);
	mqtimer->alivable = app_false;
}


/**
 * @brief 启动定时器
 * 
 * @param mqtimer 定时器句柄
 */
void start_time_task(mqtt_timer *mqtimer, int times, void (*fun)(void* para))
{
	logger_debug("%s \r\n", __func__);

	if(NULL == mqtimer){
		return;
	}
	mqtimer->fun = fun;
	mqtimer->jiffies = times*1000;
	mqtimer->alivable = app_false;
	setup_timer(&mqtimer->timer, time_callback, (unsigned long)mqtimer);
	mqtimer->alivable = app_true;
	mod_timer(&mqtimer->timer, calc_expires(mqtimer->jiffies));
}
