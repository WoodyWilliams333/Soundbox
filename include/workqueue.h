
#ifndef _WORK_QUEUE_H_
#define _WORK_QUEUE_H_

#include <pthread.h>
#include "list.h"

typedef void (*pWorkFunc)(void *);

//�������нڵ�
typedef struct WorkNode{
	pWorkFunc wrokdfunc;		//��������ִ�к���
	void* arg;					//��������ִ�к�������
}ST_WORK_NODE;

//��������
typedef struct wrok_queue{
	struct list_head entry;
	ST_WORK_NODE node;
	pthread_mutex_t *mutex;		//�߳���
}WorkQueue;


WorkQueue* InitWorkQueue(void);
int WorkQueueEmpty(WorkQueue *lpWorkQueue);
int WorkQueuePush(WorkQueue *lpWorkQueue,  ST_WORK_NODE node);
int WorkQueuePull(WorkQueue *lpWorkQueue, ST_WORK_NODE *node);
int WorkQueueDestroy(WorkQueue *lpWorkQueue);

void thread_safe_lock(pthread_mutex_t *mutex);
void thread_safe_unlock(pthread_mutex_t *mutex);

#endif
