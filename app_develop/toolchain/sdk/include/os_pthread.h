/**
@if Chinese
 * @brief       ��ģ���������� <strong>����ϵͳ�߳�ģ��</strong> ��ؽӿ�
 * @par �ļ�    os_pthread.h
 * @author		Waylon
 * @date        2020/12/28
 * @version     1.0.0
 * @remarks     Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2020/12/28    | Waylon          | �����ļ�
 * 2022/04/21    | Wenming         | ����Ӣ��ע��
@else 
 * @brief       This module is used to describe <strong> Operating system thread</strong> interfaces module
 * @par File   os_pthread.h
 * @author		Waylon
 * @date        2020/12/28
 * @version     1.0.0
 * @remarks     Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2020/12/28    | Waylon          | Create file
 * 2022/04/21    | Wenming         | Add English description
 @endif
*/


/**
@if Chinese
 * @defgroup os_thread �߳�
@else  
 * @defgroup os_thread Thread
@endif 
 * @ingroup os_service
 * @{
*/

#ifndef __RTOS_PTHREAD_H__
#define __RTOS_PTHREAD_H__

#include <stdint.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define __SIZEOF_PTHREAD_MUTEXATTR_T    4                       /**<@if Chinese �̻߳�����attr_t�Ĵ�С     @else Size of thread mutex attr_t 						@endif*/ 
#define USER_THREAD_PRIORITY_BASE       100                     /**<@if Chinese �û��߳����ȼ��Ļ�׼ֵ     @else A reference value for the user's thread priority 	@endif*/ 
#define PTHREAD_MUTEX_RECURSIVE         0                       /**<@if Chinese �̵߳ݹ黥����             @else Thread recursive mutex 							@endif*/
#define PTHREAD_MUTEX_INITIALIZER       ((void *)0xdead4000)    /**<@if Chinese �̻߳�������ʼֵ           @else Thread mutex initial value 						@endif*/

//typedef unsigned long int pthread_t;                           /**< �߳�ID����                 */ 

typedef void *(*routine_t) (void *);                            /**<@if Chinese �߳�ִ�к�������          @else The thread executes the function definition 		@endif*/
 
//typedef void * pthread_mutex_t;                               /**< �̻߳���������              */ 

#if 0
/**
 * @brief �̵߳��ȶ���
 *
 */
struct sched_param { 
    int                 sched_priority;                         /**< �̵߳ĵ������ȼ�           */ 
};
#endif

#if 0
/**
 * @brief �߳����Զ���
 *
 */
typedef struct {
    struct sched_param  schedparam;                             /**< �̵߳ĵ��Ȳ���             */
    unsigned int        stacksize;                              /**< �߳�ջ�Ĵ�С               */
} pthread_attr_t;
#endif

#if 0
/**
 * @brief �̻߳��������Զ���
 *
 */
typedef union
{
    char                size[__SIZEOF_PTHREAD_MUTEXATTR_T];     /**< mutex��size                */
    int                 align;                                  /**< �ֽڶ������               */
} pthread_mutexattr_t;
#endif

/**
 @if Chinese
 * @brief	��ȡ��ǰ�̵߳�ID
 * @return	���ص�ǰ�̵߳�ID
 @else
 * @brief	Gets the ID of the current thread
 * @return	Returns the ID of the current thread
 @endif
 *
 */
pthread_t pthread_self(void);

/**
@if Chinese
 * @brief			�����̣߳���֧���߳�����
 * @param[out]	newthread		-	ָ���̱߳�ʶ����ָ��
 * @param[in]	attr			-	�߳���������
 * @param[in]	start_routine	-	�߳�ִ�к���
 * @param[in]	arg				-	���ݸ��߳�ִ�к����Ĳ���
 * @return         int
 * @retval         0 ��ʾ�����̳߳ɹ�
 * @retval         <0 �����߳�ʧ��
@else 
 * @brief	Create thread, thread destruction is not supported
 * @param[out]	newthread		-	A pointer to a thread identifier
 * @param[in]	attr			-	Thread property Settings
 * @param[in]	start_routine	-	Thread execution function
 * @param[in]	arg				-	Arguments passed to the thread-executing function
 * @return          int
 * @retval          0 	Succeeded 
 * @retval          <0 	Failed 
@endif 
 */
int pthread_create (pthread_t *newthread, const pthread_attr_t *attr, \
                        routine_t start_routine, void *arg);

/**
@if Chinese
 * @brief	�߳����Գ�ʼ��
 * @param[out]	attr	-	ָ���߳����Ա�����ָ��
 * @return		int
 * @retval      0       �߳����Գ�ʼ���ɹ�
 * @retval      <0      �߳����Գ�ʼ��ʧ��
@else 
 * @brief       Thread initialization
 * @param[out]	attr	-	Pointer to a thread property variable
 * @return      int
 * @retval      0       Succeeded
 * @retval      <0      Failed
@endif 
 */
int pthread_attr_init(pthread_attr_t *attr);

/**
@if Chinese
 * @brief       �߳���������
 * @param[in]	attr	-	ָ���߳����Ա�����ָ��
 * @return	int
 * @retval      0 �߳��������ٳɹ�
 * @retval      <0 �߳���������ʧ��
@else 
 * @brief       Thread destruction
 * @param[in]   attr	-	Pointer to a thread property variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif
 */
int pthread_attr_destroy(pthread_attr_t *attr);

/**
@if Chinese
 * @brief       �߳�����������
 * @param[in]	mutex	-	ָ���߳���������ָ��
 * @return      int
 * @retval      0 �߳��������ɹ�
 * @retval      <0 �߳�������ʧ��
@else  
 * @brief       Thread lock locks
 * @param[in]	mutex	-	Pointer to a thread lock variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif 
 */
int pthread_mutex_lock(pthread_mutex_t *mutex);

/**
@if Chinese
 * @brief       �߳�����������
 * @param[out]	mutex	-	ָ���߳���������ָ��
 * @return      int
 * @retval      0 �߳��������ɹ�
 * @retval      <0 �߳�������ʧ��
@else  
 * @brief       Thread lock unlock
 * @param[out]	mutex	-	Pointer to a thread lock variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif  
 */
int pthread_mutex_unlock(pthread_mutex_t *mutex);

/**
@if Chinese
 * @brief       �߳������Գ�ʼ��
 * @param[out]	attr	-	ָ���߳������Ա�����ָ��
 * @return      int
 * @retval      0 �߳������Գ�ʼ���ɹ�
 * @retval      <0 �߳������Գ�ʼ��ʧ��
@else 
 * @brief       The thread lock property is initialized
 * @param[out]	attr	-	Pointer to a thread lock property variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif 
 */
int pthread_mutexattr_init (pthread_mutexattr_t *attr);

/**
@if Chinese
 * @brief       �����߳�����������
 * @param[in]	attr	-	ָ���߳������Ա�����ָ��
 * @param[in]	kind	-	�߳�����������
 * @return      int
 * @retval      0 �߳��������������óɹ�
 * @retval      <0 �߳���������������ʧ��
@else 
 * @brief       Sets the thread lock property type
 * @param[in]	attr	-	Pointer to a thread lock property variable
 * @param[in]	kind	-	Thread lock property type
 * @return     int
 * @retval     0 	Succeeded
 * @retval     <0 	Failed
@endif  
 */
int pthread_mutexattr_settype (pthread_mutexattr_t *attr, int kind);

/**
@if Chinese
 * @brief       �߳�����ʼ��
 * @param[out]	mutex		-	ָ���߳���������ָ��
 * @param[in]	mutexattr	-	ָ���߳������Ա�����ָ��
 * @return      int
 * @retval      0 �߳�����ʼ���ɹ�
 * @retval      <0 �߳�����ʼ��ʧ��
@else  
 * @brief       Thread lock initialization
 * @param[out]  mutex		-	Pointer to a thread lock variable
 * @param[in]   mutexattr	-	Pointer to a thread lock property variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif 
 */
int pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

/**
@if Chinese
 * @brief �߳�������
 * @param[out]	mutex	-	ָ���߳���������ָ��
 * @return      int
 * @retval      0 �߳������ٳɹ�
 * @retval     <0 �߳�������ʧ��
@else
 * @brief Thread lock destruction
 * @param[out]	mutex	-	Pointer to a thread lock variable
 * @return      int
 * @retval      0 	Succeeded
 * @retval      <0 	Failed
@endif 
 */
int pthread_mutex_destroy(pthread_mutex_t *mutex);

/**
@if Chinese
 * @brief			�����̣߳���֧���߳�����
 * @param[out]	pxCreatedTask	-	ָ���̱߳�ʶ����ָ��
 * @param[in]	attr			-	�߳���������
 * @param[in]	start_routine	-	�߳�ִ�к���
 * @param[in]	arg				-	���ݸ��߳�ִ�к����Ĳ���
 * @param[in]	queue_num		-	�߳���Ϣ���г���
 * @return          int
 * @retval          0  ��ʾ�����̳߳ɹ�
 * @retval          <0 �����߳�ʧ��
@else 
 * @brief			Create thread, thread destruction is not supported
 * @param[out]	pxCreatedTask	-	A pointer to a thread identifier
 * @param[in]	attr 	        -	Thread property Settings
 * @param[in]	start_routine   -	Thread execution function
 * @param[in]	arg				-	Arguments passed to the thread-executing function
 * @param[in]	queue_num		-	Thread message queue length
 * @return          int
 * @retval      	0 	Succeeded
 * @retval      	<0 	Failed
@endif 
*/
int pthread_create_ex(pthread_t *pxCreatedTask, const pthread_attr_t *attr, \
                        routine_t start_routine, void *arg, uint32_t queue_num);

#ifdef __cplusplus
}
#endif /* __cplusplus */
	
#endif /* __PTHREAD_H__ */

/** @} */

