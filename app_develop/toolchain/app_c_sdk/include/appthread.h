/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app threadģ��</strong> ��صĽӿ�
	 * @par �ļ�    appthread.h
	 * @author		yangjing
	 * @date        2020-11-12
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-11-12    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-27    | 1.0.1        | lydia         | ����Ӣ��ע�� 
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
	* @addtogroup app_thread �߳�
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


typedef void *(*thread_func)(void *arg);  /**<@if Chinese �߳�ִ�к����ص�	@else	The thread performs the function callback	@endif*/

/*!
@if Chinese
	 *@brief ���������߳����ò����Ľṹ��
@else 	 
	 *@brief A structure for describing thread setting parameters
@endif 
*/
typedef struct {
    thread_func         func;                                   /**<@if Chinese �߳�ִ�к����ص�           @else	The thread performs the function callback	@endif*/
    void*               arg;                                    /**<@if Chinese �ص�����                   @else	Callback Arguments	@endif*/
    unsigned int        stacksize;                              /**<@if Chinese �߳�ջ�Ĵ�С               @else	Size of thread stack	@endif*/
    int                 sched_priority;                         /**<@if Chinese �̵߳ĵ������ȼ�,���ȼ�ֵԽ�����ȼ�Խ�ߣ�Ĭ��DEFAULT_APP_PRIORITY_MAX(24),��Χ��2-24   @else	Scheduling priority of a thread,The higher the priority value, the higher the priority,default is 24,the range is 2-24	@endif*/ 
} pthread_para;

/**
@if Chinese
 * @brief  �����߳�
 * @param[in]	func		-	�߳�ִ�к����ص�
 * @param[in]	arg			-	�ص�����
 * @param[in]	stack_size	-	������̵߳�ջ��С
 * @param[out]	task_tid	-	�߳�id
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��	
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
 * @brief  �����߳�
 * @param[in]	para		-	�ο�pthread_para�ṹ˵��
 * @param[out]	task_tid	-	�߳�id
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
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
 * @brief  ��ȡ��ǰ�̵߳�tid
 * @return  
 *				int 		-	��ǰ�̵߳�tid
@else 
 * @brief  Gets the TID of the current thread
 * @return  
 *				int 		-	Tid of the current thread
@endif 
 */
unsigned int app_thread_get_current_id(void);

/**
@if Chinese
 * @brief  ����������
 * @param[out]	mutexobj		-	�����������
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
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
 * @brief  ����������
 * @param[in]	mutex		-	�����������
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
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
 * @brief  ����������
 * @param[in]	mutex		-	�����������
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
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



