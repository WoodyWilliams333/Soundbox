
#ifndef _WORK_QUEUE_H_
#define _WORK_QUEUE_H_

#include <pthread.h>
#include "list.h"

typedef void (*pWorkFunc)(void *);

//工作队列节点
typedef struct WorkNode{
	pWorkFunc wrokdfunc;		//工作队列执行函数
	void* arg;					//工作队列执行函数参数
}ST_WORK_NODE;

//工作队列
typedef struct wrok_queue{
	struct list_head entry;
	ST_WORK_NODE node;
	pthread_mutex_t *mutex;		//线程锁
}WorkQueue;


WorkQueue* InitWorkQueue(void);
int WorkQueueEmpty(WorkQueue *lpWorkQueue);
int WorkQueuePush(WorkQueue *lpWorkQueue,  ST_WORK_NODE node);
int WorkQueuePull(WorkQueue *lpWorkQueue, ST_WORK_NODE *node);
int WorkQueueDestroy(WorkQueue *lpWorkQueue);

void thread_safe_lock(pthread_mutex_t *mutex);
void thread_safe_unlock(pthread_mutex_t *mutex);

#endif
