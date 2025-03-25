/**
@if Chinese
 * @brief       此模块用于描述 <strong>操作系统线程模块</strong> 相关接口
 * @par 文件    os_pthread.h
 * @author		Waylon
 * @date        2020/12/28
 * @version     1.0.0
 * @remarks     Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2020/12/28    | Waylon          | 创建文件
 * 2022/04/21    | Wenming         | 增加英文注释
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
 * @defgroup os_thread 线程
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

#define __SIZEOF_PTHREAD_MUTEXATTR_T    4                       /**<@if Chinese 线程互斥锁attr_t的大小     @else Size of thread mutex attr_t 						@endif*/ 
#define USER_THREAD_PRIORITY_BASE       100                     /**<@if Chinese 用户线程优先级的基准值     @else A reference value for the user's thread priority 	@endif*/ 
#define PTHREAD_MUTEX_RECURSIVE         0                       /**<@if Chinese 线程递归互斥锁             @else Thread recursive mutex 							@endif*/
#define PTHREAD_MUTEX_INITIALIZER       ((void *)0xdead4000)    /**<@if Chinese 线程互斥锁初始值           @else Thread mutex initial value 						@endif*/

//typedef unsigned long int pthread_t;                           /**< 线程ID定义                 */ 

typedef void *(*routine_t) (void *);                            /**<@if Chinese 线程执行函数定义          @else The thread executes the function definition 		@endif*/
 
//typedef void * pthread_mutex_t;                               /**< 线程互斥锁定义              */ 

#if 0
/**
 * @brief 线程调度定义
 *
 */
struct sched_param { 
    int                 sched_priority;                         /**< 线程的调度优先级           */ 
};
#endif

#if 0
/**
 * @brief 线程属性定义
 *
 */
typedef struct {
    struct sched_param  schedparam;                             /**< 线程的调度参数             */
    unsigned int        stacksize;                              /**< 线程栈的大小               */
} pthread_attr_t;
#endif

#if 0
/**
 * @brief 线程互斥锁属性定义
 *
 */
typedef union
{
    char                size[__SIZEOF_PTHREAD_MUTEXATTR_T];     /**< mutex的size                */
    int                 align;                                  /**< 字节对齐参数               */
} pthread_mutexattr_t;
#endif

/**
 @if Chinese
 * @brief	获取当前线程的ID
 * @return	返回当前线程的ID
 @else
 * @brief	Gets the ID of the current thread
 * @return	Returns the ID of the current thread
 @endif
 *
 */
pthread_t pthread_self(void);

/**
@if Chinese
 * @brief			创建线程，不支持线程销毁
 * @param[out]	newthread		-	指向线程标识符的指针
 * @param[in]	attr			-	线程属性设置
 * @param[in]	start_routine	-	线程执行函数
 * @param[in]	arg				-	传递给线程执行函数的参数
 * @return         int
 * @retval         0 表示创建线程成功
 * @retval         <0 创建线程失败
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
 * @brief	线程属性初始化
 * @param[out]	attr	-	指向线程属性变量的指针
 * @return		int
 * @retval      0       线程属性初始化成功
 * @retval      <0      线程属性初始化失败
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
 * @brief       线程属性销毁
 * @param[in]	attr	-	指向线程属性变量的指针
 * @return	int
 * @retval      0 线程属性销毁成功
 * @retval      <0 线程属性销毁失败
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
 * @brief       线程锁加锁操作
 * @param[in]	mutex	-	指向线程锁变量的指针
 * @return      int
 * @retval      0 线程锁加锁成功
 * @retval      <0 线程锁加锁失败
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
 * @brief       线程锁解锁操作
 * @param[out]	mutex	-	指向线程锁变量的指针
 * @return      int
 * @retval      0 线程锁解锁成功
 * @retval      <0 线程锁解锁失败
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
 * @brief       线程锁属性初始化
 * @param[out]	attr	-	指向线程锁属性变量的指针
 * @return      int
 * @retval      0 线程锁属性初始化成功
 * @retval      <0 线程锁属性初始化失败
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
 * @brief       设置线程锁属性类型
 * @param[in]	attr	-	指向线程锁属性变量的指针
 * @param[in]	kind	-	线程锁属性类型
 * @return      int
 * @retval      0 线程锁属性类型设置成功
 * @retval      <0 线程锁属性类型设置失败
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
 * @brief       线程锁初始化
 * @param[out]	mutex		-	指向线程锁变量的指针
 * @param[in]	mutexattr	-	指向线程锁属性变量的指针
 * @return      int
 * @retval      0 线程锁初始化成功
 * @retval      <0 线程锁初始化失败
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
 * @brief 线程锁销毁
 * @param[out]	mutex	-	指向线程锁变量的指针
 * @return      int
 * @retval      0 线程锁销毁成功
 * @retval     <0 线程锁销毁失败
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
 * @brief			创建线程，不支持线程销毁
 * @param[out]	pxCreatedTask	-	指向线程标识符的指针
 * @param[in]	attr			-	线程属性设置
 * @param[in]	start_routine	-	线程执行函数
 * @param[in]	arg				-	传递给线程执行函数的参数
 * @param[in]	queue_num		-	线程消息队列长度
 * @return          int
 * @retval          0  表示创建线程成功
 * @retval          <0 创建线程失败
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

