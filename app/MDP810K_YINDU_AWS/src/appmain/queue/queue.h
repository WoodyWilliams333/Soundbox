#ifndef _QUEUE_H
#define _QUEUE_H

#define MAX_QUEUE 100


/*typedef struct STR_ITEM{
	void *pStr;   //自己申请空间，自己释放
	int size;
}QItem;*/
typedef struct STR_NODE {
	//QItem itme;
    void *item;
	struct STR_NODE * next;
}Node;

typedef struct STR_QUEUE {
	Node *front;	//队首
	Node *rear;		//队尾
	int items;		//项目个数
}Queue;

typedef enum ENUM_ERR_CODE_QUEUE{
    queue_false= -1,
    queue_unknow= 0,
    queue_true=1
} QCode;

//extern Queue gQueue1;

void InitQueue(Queue *pq);               //初始化队列
QCode PushQueue(Queue *pq, void * item);	//入队，向队列尾插入数据
QCode PopQueue(Queue *pq, void **item);	//出队，向队列尾插入数据
QCode QueueIsFull(const Queue *pq);		//检测队列是否已满
QCode QueueIsEmpty(const Queue *pq);		//检测队列是否为空
int  GetQueueCount(const Queue *pq);	//获取队列项目个数
void EmptyQueue(Queue *pq);				//清空队列
void PrintQueue(const Queue *pq);    //打印队列
#endif //_QUEUE_H