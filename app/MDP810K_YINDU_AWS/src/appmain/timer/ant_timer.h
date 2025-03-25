/**
 * ant_timer.h
 *
 * 定时器接口
 */
#ifndef __ANT_TIMER_H__
#define __ANT_TIMER_H__

typedef int                ant_s32;
typedef unsigned int       ant_u32;


#include <timer.h>   

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    ant_s32 year;  // [0~127]
    ant_s32 month; // [1~12]
    ant_s32 wday;
    ant_s32 day;
    ant_s32 hour;
    ant_s32 minute;
    ant_s32 second;
    ant_s32 isdst; // one digit expresses a quarter of an hour, for example: 22 indicates "+5:30"
} ant_time;

    
#define TIME_SYNC_TIMER  0
#define LED_BLINK_TIMER  1
#define TIMER_ID_MAX     5

typedef void (*callback_on_timer)(void *param);
typedef void * ant_timer;


typedef void(*timer_callbackex)(void *param);


typedef struct timer_node{
	struct timer_list timer;
	char timer_name[32+1];
	ant_u32 interval;
	ant_u32 cyc_exe_flag;
	timer_callbackex callback_func;
	void *callback_param;
	uint8_t alredy_setup;//标记是否已创建
}ant_timer_Node;


/**
 * 创建定时器
 *
 * @param  name  定时器名称
 *
 * @return 成功: 返回定时器对象
 *         失败: 返回NULL
 */
ant_timer ant_timer_create(const char *name);

/**
 * 启动定时器
 *
 * @param timer 定时器对象
 * @param callback 时间到达时的回调函数
 * @param param 回调函数参数
 * @param interval 定时时间
 * @param resched_interval 定时时间发生时，自动重新开启定时的时间，如果传入0，则定时器自动停止
 *
 * @return 0   成功
 *         <0  失败
 */
ant_s32 ant_timer_start(ant_timer timer, callback_on_timer callback, void *param, ant_u32 interval, ant_u32 resched_interval);

/**
 * 停止定时器对象
 *
 * @param timer 定时器对象
 *
 * @return 0   成功
 *         <0  失败
 */
ant_s32 ant_timer_stop(ant_timer timer);

/**
 * 销毁定时器
 *
 * @param timer 定时器对象
 *
 * @return 0   成功
 *         <0  失败
 */
ant_s32 ant_timer_destroy(ant_timer timer);


/**
 * 获取定时器挂起状态
 *
 * @param timer 定时器对象
 *
 * @return 1   挂起
 *         0   未挂起/已执行完
 */
ant_s32 get_timer_pedding_status(ant_timer timer);




#ifdef __cplusplus
}
#endif

#endif

