/**
 * ant_timer.h
 *
 * 定时器接口
 */

#include <time.h>
#include <sys/time.h>
#include "ant_timer.h"
#include "logger.h"
#include <syscall.h>

pthread_mutex_t  timer_xMutex;

//extern const void *kernel_relocate(const char *symbol);


extern const void *kernel_relocate(const char *symbol);


static void run_timer_callback(unsigned long param)
{

	ant_timer_Node *cr_timer = (ant_timer_Node *)param;
	
	if((void*)param == NULL){
		return;
	}

	if(cr_timer->callback_func){
		cr_timer->callback_func(cr_timer->callback_param);
	}
	if(cr_timer->cyc_exe_flag > 0){
		mod_timer(&cr_timer->timer,  syscall_get_tick_count() + cr_timer->cyc_exe_flag);
	}
}




/**
 * 创建定时器
 *
 * @param  name  定时器名称
 *
 * @return 成功: 返回定时器对象
 *         失败: 返回NULL
 */
ant_timer ant_timer_create(const char *name)
{

	ant_timer_Node *timer = NULL;

	timer = malloc(sizeof(ant_timer_Node));
	if(timer != NULL){
		memset(timer,0,sizeof(ant_timer_Node));
		snprintf(timer->timer_name,sizeof(timer->timer_name),"%s",name);
	}

	return timer; 
}

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
ant_s32 ant_timer_start(ant_timer timer, callback_on_timer callback, void *param, ant_u32 interval, ant_u32 resched_interval)
{

    int ret = -1;
    ant_timer_Node *cr_timer = (ant_timer_Node *)timer;
	if(cr_timer != NULL){
		cr_timer->callback_func = callback;
		cr_timer->callback_param = param;
		cr_timer->interval = interval;
		cr_timer->cyc_exe_flag = resched_interval;
		if(cr_timer->alredy_setup)//定时器挂起时不能重复setup，设置前先删除已设置的定时器
		{	
			del_timer(&cr_timer->timer);
		}
		setup_timer(&cr_timer->timer,run_timer_callback,(unsigned long)cr_timer);	
		cr_timer->alredy_setup = 1;
		ret = mod_timer(&cr_timer->timer,  syscall_get_tick_count() + interval);			
		
	}

	return ret;
}
/**
 * 停止定时器对象
 *
 * @param timer 定时器对象
 *
 * @return 0   成功
 *         <0  失败
 */
ant_s32 ant_timer_stop(ant_timer timer)
{

	int ret = -1;
    unsigned long expires = 0x0000FFFF;
    ant_timer_Node *cr_timer = (ant_timer_Node *)timer;
	
    if(cr_timer)
    {
    	//ant_tprintf("ant_timer_stop=%s,cr_timer->timer=%p,pending=%d\n",cr_timer->timer_name,&cr_timer->timer,timer_pending(&cr_timer->timer));
    	ret = mod_timer(&cr_timer->timer,  syscall_get_tick_count() + expires);
	}

	return ret;

}

/**
 * 销毁定时器
 *
 * @param timer 定时器对象
 *
 * @return 0   成功
 *         <0  失败
 */
ant_s32 ant_timer_destroy(ant_timer timer)
{

    ant_timer_Node *cr_timer = (ant_timer_Node *)timer;
	//ant_tprintf("cr_timer=%p\n",cr_timer);
		
    if(cr_timer)
    {
 		del_timer(&cr_timer->timer);
		free(cr_timer);
		cr_timer = NULL;
	}
	return 0;
}

ant_s32 get_timer_pedding_status(ant_timer timer)
{	
	int ret = 0;
	ant_timer_Node *cr_timer = (ant_timer_Node *)timer;
	if(cr_timer)
	{
		ret = timer_pending(&cr_timer->timer);
	}
	return ret;

}



