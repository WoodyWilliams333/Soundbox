
/**
 @if Chinese
 * @brief       此模块用于描述 <strong>操作系统模块</strong> 相关接口
 * @note
 * @par 文件    os.h
 * @author		Wenming
 * @date          2019/01/28
 * @version       1.0.1
 * @remarks        Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | 创建文件
 * 2022/04/21    | Wenming         | 增加英文注释
@else 
 * @brief       This module is used to describe <strong>Operating System</strong> interfaces module
 * @note
 * @par File    os.h
 * @author		Wenming
 * @date          2019/01/28
 * @version       1.0.1
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | Create file
 * 2022/04/21    | Wenming         | Add English description
@endif 
*/


/**
@if Chinese
 * @defgroup os_service 操作系统
@else 
 * @defgroup os_service Operating System
@endif
 * @{
*/

#ifndef __OS_H__
#define __OS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
	*@brief  多线程和互斥锁的相关接口 
@else	
	*@brief  Multithreading and mutex related interfaces 
@endif
*/
#include "os_pthread.h"

/**
@if Chinese
	*@brief  定时器相关接口 
@else	
	*@brief  Timer related interfaces 
@endif	
*/
#include "timer.h"

/**
@if Chinese
	*@brief 信号量相关接口 
@else	
	*@brief Semaphore correlation interface
@endif	
*/
#include "semaphore.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OS_H__ */

/** @} */
