#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "appmalloc.h"

//pthread_mutex_t queue_work_queue;
//Queue gQueue1;
/**
* @brief ��ʼ�����У�������pqָ��ն��У�
* @param[in] pq ָ��һ������
* return ��
*/
void InitQueue(Queue *pq)
{
	if (NULL == pq)
		return;
	//�����ʼ��֮ǰ���ǿյ���Ҫ��ն��У�
	if(0 != GetQueueCount(pq)){
		EmptyQueue(pq);
	}
	pq->front = pq->rear = NULL;
	pq->items = 0;
}
/**
* @brief ��ӣ������β��������
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return queue_true �ɹ���queue_falseʧ��
*/
QCode PushQueue(Queue *pq, void *item)
{
	//���֮ǰӦ�����ж϶����Ƿ��Ѿ�����
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
* @brief ���ӣ������β��������
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return queue_true �ɹ���queue_falseʧ��
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
* @brief �������Ƿ�����
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return queue_true �洢����queue_errδ��
*/
QCode QueueIsFull(const Queue *pq)
{
	if (NULL != pq && pq->items == MAX_QUEUE) {
		return queue_true;
	}
	return queue_false;
}
/**
* @brief �������Ƿ�Ϊ��
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return queue_true �ն��У�queue_falseʧ��
*/
QCode QueueIsEmpty(const Queue *pq)
{
	if (NULL != pq && pq->items == 0) {
		return queue_true;
	}
	return queue_false;
}
/**
* @brief ��ȡ������Ŀ����
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return true �ɹ���falseʧ��
*/
int GetQueueCount(const Queue *pq)
{
	if (NULL != pq) {
		return pq->items;
	}
	return 0;
}
/**
* @brief ��ն���
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return true �ɹ���falseʧ��
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
* @brief ��ӡ����
* @param[in] pq ָ��һ������
* @param[in] item ��������
* return ��
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