/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app workquequeģ��</strong> ��صĽӿ�
	 * @par �ļ�    workqueque.h
	 * @author		yangjing
	 * @date        2020-04-23
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-23    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-04-30    | 1.0.1        | lydia         | ����Ӣ��ע�� 
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
	@defgroup workqueque ��������
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
	@brief  �������нڵ�.
 @else
	@brief  work queue node.
 @endif
  */ 
typedef struct WorkNode{
	pWorkFunc wrokdfunc;	/**< @if Chinese ��������ִ�к��� @else  work queue execution function @endif */	
	void* arg;				/**< @if Chinese ��������ִ�к������� @else  work queue execution function parameters @endif */
}ST_WORK_NODE;

/**
 @if Chinese
	@brief  ��������.
 @else
	@brief  work queue.
 @endif
  */ 
typedef struct wrok_queue{
	struct list_head entry;
	ST_WORK_NODE node;
	pthread_mutex_t *mutex;		//�߳���
}WorkQueue;

/*!
 @if Chinese
	@brief          ��ʼ����������
	@return         !NULL	-	��������
	@return         NULL	-	ʧ��
 @else
	@brief          Initialize work queue
	@return         !NULL	-	work queue
	@return         NULL	-	fail
 @endif
*/
WorkQueue* InitWorkQueue(void);

/*!
 @if Chinese
	@brief          �������Ƿ�Ϊ��
	@param[in]    	lpWorkQueue	-	��Ҫ���Ķ���
	@return         1		-	�ɹ�
	@return         ����	-	ʧ��
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
	@brief          �Ѷ��в��뵽���������
	@param[in]    	lpWorkQueue	-	ϵͳ����������
	@param[in]    	node		-	�������нڵ�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
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
	@brief          ɾ��������ĳ���ڵ�
	@param[in]    	lpWorkQueue	-	ϵͳ����������
	@param[in]    	node		-	�������нڵ�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
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
	@brief          ɾ���������У�δʹ�ã�
	@param[in]    	lpWorkQueue	-	ϵͳ����������
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          Delete entire queue(not used)
	@param[in]    	lpWorkQueue	-	System shared work queue
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
int WorkQueueDestroy(WorkQueue *lpWorkQueue);

#endif
