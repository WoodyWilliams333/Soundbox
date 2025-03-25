/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app schedulework模块</strong> 相关的接口
	 * @par 文件    schedulework.h
	 * @author		yangjing
	 * @date        2020-09-29
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-09-29    | 1.0.0        | yangjing      | 创建文件
	 * 2022-05-05    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app schedulework </strong>  module
	 * @par file    schedulework.h
	 * @author		yangjing
	 * @date        2020-09-29
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-09-29    | 1.0.0        | yangjing      | create file
	 * 2022-05-05    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup schedulework schedulework
 @else
	@defgroup schedulework schedulework
 @endif
 * @{
*/
#ifndef _SCHEDULE_WORK_H_
#define _SCHEDULE_WORK_H_

#include "workqueue.h"

/**
 @if Chinese
	* @brief 	初始化工作任务
	* @param[out]	work		-	初始化任务实例
	* @param[in]	workfunc	-	工作执行的任务函数指针
	* @param[in]	workarg		-	任务函数参数指针
	* @return		0			-	成功
	* @return		其它		-	失败
 @else
	* @brief 	initialize work tasks
	* @param[out]	work		-	initialize task instance
	* @param[in]	workfunc	-	pointer to the task function where the work is executed
	* @param[in]	workarg		-	task function parameter pointer
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int init_work(ST_WORK_NODE *work, pWorkFunc workfunc, void *workarg);

/**
 @if Chinese
	* @brief 	分配任务，任务将在任务线程内执行(分配的任务按先入先出的顺序执行)
	* @param[in]	work		-	初始化后任务实例
	* @return		0			-	成功
	* @return		其它		-	失败
 @else
	* @brief 	assign tasks, which will be executed within the task thread (the assigned tasks will be executed in the order of first in first out)
	* @param[in]	work		-	initialize task instance
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int schedule_work(ST_WORK_NODE *work);

#endif

