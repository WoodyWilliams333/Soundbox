
/**
 @if Chinese
 * @brief       ��ģ���������� <strong>����ϵͳ��ʱ��ģ��</strong> ��ؽӿ�
 * @note
 * @par �ļ�    timer.h
 * @author
 * @date        2019/01/28
 * @version     1.0.1
 * @remarks     Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | �����ļ�
 * 2022/04/21    | Wenming         | ����Ӣ��ע�� 
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
 * @defgroup os_timer ��ʱ��
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
	 *@brief ��ʱ������ڵ㶨��
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
 * @brief ����һ���µļ�ʱ��
 * @param[in] timer         -	������ļ�ʱ��
 * @param[in] function      -	��ʱ������ʱ��excute����
 * @param[in] data          -	����ִ�е���������
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
 * @brief 	��ʱ���Ƿ����
 * @param[in] timer -	���ļ�ʱ��
 *
 * @note 	�����߸����ļ�ʱ����ǰ�Ƿ����,
 * 			���÷�����ȷ�����л�wrt�������������
 *
 * @retval 	1	-	��ʱ������
 * @retval 	0	-	��ʱ��δ����
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
 * @brief ɾ����ʱ��
 * @param[in] timer     -	Ŀ�궨ʱ��
 * @retval 0	-	ɾ���ɹ�
 * @retval ��0	-	ɾ��ʧ��
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
 * @brief ���µĹ���ʱ���޸ļ�ʱ��
 * @param[in] timer     -	Ŀ�궨ʱ��
 * @param[in] expires   -	�µ���ʱ��
 * @retval 0	-	�޸ĳɹ�
 * @retval ��0	-	�޸�ʧ��
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
 * @brief	����һ����ʱ��
 * @param[in]	timer	-	��Ҫ��ӵĶ�ʱ��
 * @retval	none 
 * @note �ں˽���->����(->����)�ص�
 *		��ʱ���ж���->��δ�����ڵ㡣��
 *		��ǰʱ����'jiffies'��
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

