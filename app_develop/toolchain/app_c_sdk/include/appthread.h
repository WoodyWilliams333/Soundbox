/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app thread模块</strong> 相关的接口
	 * @par 文件    appthread.h
	 * @author		yangjing
	 * @date        2020-11-12
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-11-12    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-27    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app thread </strong>  module
	 * @par file    appthread.h
	 * @author		yangjing
	 * @date        2020-11-12
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-11-12    | 1.0.0        | yanjing       | create file
	 * 2022-04-27    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/**
 @if Chinese
	* @addtogroup app_thread 线程
 @else 
	* @addtogroup app_thread thread
 @endif 
 * @{
*/
 
#ifndef _APP_THREAD_H_
#define _APP_THREAD_H_

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef void *(*thread_func)(void *arg);  /**<@if Chinese 线程执行函数回调	@else	The thread performs the function callback	@endif*/

/*!
@if Chinese
	 *@brief 用于描述线程设置参数的结构体
@else 	 
	 *@brief A structure for describing thread setting parameters
@endif 
*/
typedef struct {
    thread_func         func;                                   /**<@if Chinese 线程执行函数回调           @else	The thread performs the function callback	@endif*/
    void*               arg;                                    /**<@if Chinese 回调参数                   @else	Callback Arguments	@endif*/
    unsigned int        stacksize;                              /**<@if Chinese 线程栈的大小               @else	Size of thread stack	@endif*/
    int                 sched_priority;                         /**<@if Chinese 线程的调度优先级,优先级值越大，优先级越高，默认DEFAULT_APP_PRIORITY_MAX(24),范围：2-24   @else	Scheduling priority of a thread,The higher the priority value, the higher the priority,default is 24,the range is 2-24	@endif*/ 
} pthread_para;

/**
@if Chinese
 * @brief  创建线程
 * @param[in]	func		-	线程执行函数回调
 * @param[in]	arg			-	回调参数
 * @param[in]	stack_size	-	分配给线程的栈大小
 * @param[out]	task_tid	-	线程id
 * @return		0			-	成功  
 * @return		其它		-	失败	
@else  
 * @brief  Create thread
 * @param[in]	func		-	The thread performs the function callback
 * @param[in]	arg			-	Callback Arguments
 * @param[in]	stack_size	-	The stack size assigned to the thread
 * @param[out]	task_tid	-	Thread ID
 * @return		0			-	Successful
 * @return		other		-	Fail
@endif 
 */
int app_thread_create(uint32_t *task_tid, thread_func func, void *arg, int stack_size);

/**
@if Chinese
 * @brief  创建线程
 * @param[in]	para		-	参考pthread_para结构说明
 * @param[out]	task_tid	-	线程id
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  Create thread
 * @param[in]	para		-	Refer to the pthread_para structure description
 * @param[out]	task_tid	-	Thread id
 * @return		0			-	Successful
 * @return		other		-	Fail
@endif 
 */
int app_thread_create_assemble(uint32_t *task_tid, pthread_para *para);

/**
@if Chinese
 * @brief  获取当前线程的tid
 * @return  
 *				int 		-	当前线程的tid
@else 
 * @brief  Gets the TID of the current thread
 * @return  
 *				int 		-	Tid of the current thread
@endif 
 */
unsigned int app_thread_get_current_id(void);

/**
@if Chinese
 * @brief  创建互斥锁
 * @param[out]	mutexobj		-	互斥对象属性
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  Create mutex
 * @param[out]	mutexobj		-	a mutex attributes object 

 * @return		0			-	Successful
 * @return		other		-	Fail
@endif 
 */
int app_mutex_creat(pthread_mutex_t* mutexobj);

/**
@if Chinese
 * @brief  锁定互斥锁
 * @param[in]	mutex		-	互斥对象属性
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  lock mutex
 * @param[in]	mutex		-	a mutex attributes object 

 * @return		0			-	Successful
 * @return		other		-	Fail
@endif 
 */
void app_mutex_safe_lock(pthread_mutex_t *mutex);

/**
@if Chinese
 * @brief  解锁互斥锁
 * @param[in]	mutex		-	互斥对象属性
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  unlock mutex
 * @param[in]	mutex		-	a mutex attributes object 
 * @return		0			-	Successful
 * @return		other		-	Fail
@endif 
 */
void app_mutex_safe_unlock(pthread_mutex_t *mutex);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif



