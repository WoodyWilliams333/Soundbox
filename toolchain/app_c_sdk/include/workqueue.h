/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app workqueque模块</strong> 相关的接口
	 * @par 文件    workqueque.h
	 * @author		yangjing
	 * @date        2020-04-23
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-23    | 1.0.0        | yangjing      | 创建文件
	 * 2022-04-30    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app workqueque </strong>  module
	 * @par file    workqueque.h
	 * @author		yangjing
	 * @date        2020-04-23
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-23    | 1.0.0        | yangjing      | create file
	 * 2022-04-30    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup workqueque 工作队列
 @else
	@defgroup workqueque workqueque
 @endif
 * @{
*/

#ifndef _WORK_QUEUE_H_
#define _WORK_QUEUE_H_

#include <pthread.h>
#include <linuxlist.h>

#include "appthread.h"

typedef void (*pWorkFunc)(void *);

/**
 @if Chinese
	@brief  工作队列节点.
 @else
	@brief  work queue node.
 @endif
  */ 
typedef struct WorkNode{
	pWorkFunc wrokdfunc;	/**< @if Chinese 工作队列执行函数 @else  work queue execution function @endif */	
	void* arg;				/**< @if Chinese 工作队列执行函数参数 @else  work queue execution function parameters @endif */
}ST_WORK_NODE;

/**
 @if Chinese
	@brief  工作队列.
 @else
	@brief  work queue.
 @endif
  */ 
typedef struct wrok_queue{
	struct list_head entry;
	ST_WORK_NODE node;
	pthread_mutex_t *mutex;		//线程锁
}WorkQueue;

/*!
 @if Chinese
	@brief          初始化工作队列
	@return         !NULL	-	工作队列
	@return         NULL	-	失败
 @else
	@brief          Initialize work queue
	@return         !NULL	-	work queue
	@return         NULL	-	fail
 @endif
*/
WorkQueue* InitWorkQueue(void);

/*!
 @if Chinese
	@brief          检查队列是否为空
	@param[in]    	lpWorkQueue	-	需要检查的队列
	@return         1		-	成功
	@return         其它	-	失败
 @else
	@brief          Check whether the queue is empty
	@param[in]    	lpWorkQueue	-	queue to check
	@return         1		-	success
	@return         other	-	fail
 @endif
*/
int WorkQueueEmpty(WorkQueue *lpWorkQueue);

/*!
 @if Chinese
	@brief          把队列插入到共享队列中
	@param[in]    	lpWorkQueue	-	系统共享工作队列
	@param[in]    	node		-	工作队列节点
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          Insert queue into shared queue
	@param[in]    	lpWorkQueue	-	System shared work queue
	@param[in]    	node		-	work queue node
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
int WorkQueuePush(WorkQueue *lpWorkQueue,  ST_WORK_NODE node);

/*!
 @if Chinese
	@brief          删除队列中某个节点
	@param[in]    	lpWorkQueue	-	系统共享工作队列
	@param[in]    	node		-	工作队列节点
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          Delete a node in the queue
	@param[in]    	lpWorkQueue	-	System shared work queue
	@param[in]    	node		-	work queue node
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
int WorkQueuePull(WorkQueue *lpWorkQueue, ST_WORK_NODE *node);

/*!
 @if Chinese
	@brief          删除整个队列（未使用）
	@param[in]    	lpWorkQueue	-	系统共享工作队列
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          Delete entire queue(not used)
	@param[in]    	lpWorkQueue	-	System shared work queue
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
int WorkQueueDestroy(WorkQueue *lpWorkQueue);

#endif
