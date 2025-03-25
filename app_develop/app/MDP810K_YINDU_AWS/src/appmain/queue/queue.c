#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "appmalloc.h"

//pthread_mutex_t queue_work_queue;
//Queue gQueue1;
/**
* @brief 初始化队列，操作后pq指向空队列，
* @param[in] pq 指向一个队列
* return 无
*/
void InitQueue(Queue *pq)
{
	if (NULL == pq)
		return;
	//如果初始化之前不是空的需要清空队列，
	if(0 != GetQueueCount(pq)){
		EmptyQueue(pq);
	}
	pq->front = pq->rear = NULL;
	pq->items = 0;
}
/**
* @brief 入队，向队列尾插入数据
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return queue_true 成功，queue_false失败
*/
QCode PushQueue(Queue *pq, void *item)
{
	//入队之前应该先判断队列是否已经满了
	if ( (NULL != pq) && (queue_false == QueueIsFull(pq))){
		Node *pNode = (Node *)app_malloc(sizeof(Node));
		if (NULL != pNode) {
			pNode->item = item;
			pNode->next = NULL;

			if (queue_true == QueueIsEmpty(pq)) {
				pq->front = pNode;
			}
			else {
				pq->rear->next = pNode;
			}
			pq->rear = pNode;
			pq->items++;

			return queue_true;
		}
	}
	return queue_false;
}
/**
* @brief 出队，向队列尾插入数据
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return queue_true 成功，queue_false失败
*/
QCode PopQueue(Queue *pq, void **item)
{
	if ((NULL != pq) && (queue_false == QueueIsEmpty(pq))) {
		Node *pt;
		*item = pq->front->item;
		pt = pq->front;
		pq->front = pq->front->next;
		app_free(pt);
		pq->items--;
		if (0 == pq->items) {
			pq->rear = NULL;
		}
		return queue_true;
	}
	return queue_false;
}

/**
* @brief 检测队列是否已满
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return queue_true 存储满，queue_err未满
*/
QCode QueueIsFull(const Queue *pq)
{
	if (NULL != pq && pq->items == MAX_QUEUE) {
		return queue_true;
	}
	return queue_false;
}
/**
* @brief 检测队列是否为空
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return queue_true 空队列，queue_false失败
*/
QCode QueueIsEmpty(const Queue *pq)
{
	if (NULL != pq && pq->items == 0) {
		return queue_true;
	}
	return queue_false;
}
/**
* @brief 获取队列项目个数
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return true 成功，false失败
*/
int GetQueueCount(const Queue *pq)
{
	if (NULL != pq) {
		return pq->items;
	}
	return 0;
}
/**
* @brief 清空队列
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return true 成功，false失败
*/
void EmptyQueue(Queue *pq)
{
	void *item = NULL;
	while (queue_false == QueueIsEmpty(pq)) {
		PopQueue(pq, &item);
        if(NULL != item){
            app_free(item);
        }
	};
}
/**
* @brief 打印队列
* @param[in] pq 指向一个队列
* @param[in] item 插入数据
* return 无
*/
/*void PrintQueue(const Queue *pq)
{
	Node *node = pq->front;
	Node *rear = pq->rear;

	while (node != rear)
	{
		printf("%s", node->itme);
		node = node->next;
	}
	printf("\n");

}*/