
/**
@if Chinese
 * @brief       此模块用于描述 <strong>操作系统信号量模块</strong> 相关接口
 * @note
 * @par 文件    semaphore.h
 * @author
 * @date        2019/01/28
 * @version     1.0.0
 * @remarks     Change History:
 * 日期          | 作者          | 描述
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | 创建文件
 * 2022/04/21    | Wenming         | 增加英文注释
@else 
 * @brief       This module is used to describe <strong>Operating system semaphores</strong> interfaces module
 * @note
 * @par File    semaphore.h
 * @author
 * @date        2019/01/28
 * @version     1.0.0
 * @remarks     Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | Create file
 * 2022/04/21    | Wenming         | Add English description
@endif
*/


/**
@if Chinese
 * @defgroup os_semaphore 信号量
@else 
 * @defgroup os_semaphore Semaphore
@endif 
 * @ingroup os_service
 * @{
*/

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void *sem_handle_t;                     /**<@if Chinese 信号量操作句柄 @else Semaphore operation handle @endif*/

/**
@if Chinese
 * @name 信号等待状态
@else 
 * @name semaphore Wait option
@endif	 
 * @{
 */
#define SEM_OPT_NO_WAIT         0x0             /**<@if Chinese 没有等待信号量 @else no wait for semaphore 		@endif*/
#define SEM_OPT_WAIT_FOREVER    0xFFFFFFFF      /**<@if Chinese 一直等待信号量 @else wait for semaphore forever @endif*/
/** @} */

/**
@if Chinese
 * @brief 创建信号量
 * @param[in] name_ptr          -	信号量的名称
 * @param[in] initial_count     -	信号量初始计数器
 * @retval 非空 -创建成功	
 * @retval  空 	-创建失败.
@else  
 * @brief os api, create semaphore
 * @param[in] name_ptr          -	the name of semaphore
 * @param[in] initial_count     -	initial counter of semaphore
 * @retval non-NULL	-	semaphore create ok
 * @retval	NULL	-	Faild.
@endif 
 */
sem_handle_t os_create_sem(const char *name_ptr, uint32_t initial_count);

/**
@if Chinese
 * @brief 删除信号量
 * @param[in] sem    -	信号量句柄
 * @retval 	0	-	信号删除成功 	 
 * @retval  <0	-	信号删除失败.
@else  
 * @brief os api, delete semaphore
 * @param[in] sem    the handle of semaphore
 * @retval 	0	-	semaphore delete ok
 * @retval  <0	-	Faild.
@endif 
 */
int os_delete_sem(sem_handle_t sem);

/**
@if Chinese
 * @brief 获取信号量
 * @param[in] sem			-	信号量句柄
 * @param[in] wait_option	-	等待选项，请参见 SEM_OPT_NO_WAIT或SEM_OPT_WAIT_FOREVER宏定义。
 * @retval	0	-	获取成功
 * @retval	<0	-	获取失败.
@else 
 * @brief os api, get a semaphore
 * @param[in] sem           -	the handle of semaphore
 * @param[in] wait_option	-	Wait options, see SEM_OPT_NO_WAIT or SEM_OPT_WAIT_FOREVER macro definitions
 * @retval	0	-	semaphore get ok
 * @retval  <0	-	Faild.
@endif	 
 */
int os_get_sem(sem_handle_t sem, uint32_t wait_option);

/**
@if Chinese
 * @brief 抛出一个信号量
 * @param[in] sem    -	信号量句柄
 * @retval	0	-	获取成功
 * @retval  <0	-	获取失败.
@else  
 * @brief os api, put a semaphore
 * @param[in] sem    -	the handle of semaphore
 * @retval	0	-	semaphore put ok
 * @retval  <0	-	Faild.
@endif	 
 */
int os_put_sem(sem_handle_t sem);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SEMAPHORE_H__ */

/** @} */

