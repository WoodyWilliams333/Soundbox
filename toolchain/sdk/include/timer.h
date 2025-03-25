
/**
 @if Chinese
 * @brief       此模块用于描述 <strong>操作系统定时器模块</strong> 相关接口
 * @note
 * @par 文件    timer.h
 * @author
 * @date        2019/01/28
 * @version     1.0.1
 * @remarks     Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | 创建文件
 * 2022/04/21    | Wenming         | 增加英文注释 
@else 
 * @brief       This module is used to describe <strong>Operating system timer</strong> interfaces module
 * @remarks     Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | Create file
 * 2022/04/21    | Wenming         | Add English description 
@endif 
*/


/**
@if Chinese
 * @defgroup os_timer 定时器
@else 
 * @defgroup os_timer Timer
@endif 
 * @ingroup os_service
 * @{
*/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <linuxlist.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define TIMER_INIT(func,arg,expires) {{NULL, NULL}, expires, func, arg}

/**
 @if Chinese
	 *@brief 定时器链表节点定义
 @else	 
	 *@brief Timer list node definition
 @endif
 */
struct timer_list {
    struct list_head entry;                 
    unsigned long expires;
    void (*function)(unsigned long);
    unsigned long data;
};

/**
@if Chinese
 * @brief 设置一个新的计时器
 * @param[in] timer         -	有问题的计时器
 * @param[in] function      -	定时器过期时的excute函数
 * @param[in] data          -	函数执行的输入数据
@else	 
 * @brief setup a new timer
 * @param[in] timer         -	the timer in question
 * @param[in] function      -	the excute function when timer expired
 * @param[in] data          -	the input data for fucntion excute
@endif 
 */
static inline void setup_timer(struct timer_list *timer,
                               void (*function)(unsigned long),
                               unsigned long data)
{
    INIT_LIST_HEAD(&timer->entry);
    timer->expires = 0x0FFFFFFF;
    timer->function = function;
    timer->data = data;
}

/**
@if Chinese
 * @brief 	定时器是否挂起
 * @param[in] timer -	检测的计时器
 *
 * @note 	将告诉给定的计时器当前是否挂起,
 * 			调用方必须确保序列化wrt。其他操作完成
 *
 * @retval 	1	-	定时器挂起
 * @retval 	0	-	定时器未挂起
@else
 * @brief 	Is the timer suspended?
 * @param[in] timer Target timer
 *
 * @note timer_pending will tell whether the timer suspended. Callers must ensure serialization wrt. other operations done
 * to this timer, eg. interrupt contexts, or other CPUs on SMP.
 *
 * @retval 	1	-	the timer is pending
 * @retval 	0	-	the timer is not pending
@endif 
 */
static inline int timer_pending(const struct timer_list *timer)
{
    return (timer->entry.next != NULL && timer->entry.next != &timer->entry
            && timer->entry.prev != NULL && timer->entry.prev != &timer->entry
            && timer->entry.next->prev == &timer->entry);
}

/**
@if Chinese
 * @brief 删除定时器
 * @param[in] timer     -	目标定时器
 * @retval 0	-	删除成功
 * @retval 非0	-	删除失败
@else 
 * @brief delete timer
 * @param[in] timer     -	Target timer
 * @retval 0	-	timer delete ok
 * @retval !0	-	timer delete fail
@endif 
 */
int del_timer(struct timer_list *timer);

/**
@if Chinese
 * @brief 用新的过期时间修改计时器
 * @param[in] timer     -	目标定时器
 * @param[in] expires   -	新到期时间
 * @retval 0	-	修改成功
 * @retval 非0	-	修改失败
@else 
 * @brief modify timer with new expires time
 * @param[in] timer     -	Target timer
 * @param[in] expires   -	new expires time
 * @retval 0	-	modify ok
 * @retval !0	-	modify fail
@endif 
 */
int mod_timer(struct timer_list *timer, unsigned long expires);

/**
@if Chinese
 * @brief	启动一个计时器
 * @param[in]	timer	-	需要添加的定时器
 * @retval	none 
 * @note 内核将从->函数(->数据)回调
 *		定时器中断在->在未来到期点。的
 *		当前时间是'jiffies'。
@else 
 * @brief	start a timer
 * @param[in]	timer	-	the timer to be added
 * @retval	none 
 * @note 
 * The kernel will do a ->function(->data) callback from the
 * timer interrupt at the ->expires point in the future. The
 * current time is 'jiffies'.
 *
 * The timer's ->expires, ->function (and if the handler uses it, ->data)
 * fields must be set prior calling this function.
 *
 * Timers with an ->expires field in the past will be executed in the next
 * timer tick.
@endif 
 */
static inline void add_timer(struct timer_list *timer)
{
    mod_timer(timer, timer->expires);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIMER_H__ */

/** @} */

