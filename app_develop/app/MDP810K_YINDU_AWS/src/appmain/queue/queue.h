#ifndef _QUEUE_H
#define _QUEUE_H

#define MAX_QUEUE 100


/*typedef struct STR_ITEM{
	void *pStr;   //�Լ�����ռ䣬�Լ��ͷ�
	int size;
}QItem;*/
typedef struct STR_NODE {
	//QItem itme;
    void *item;
	struct STR_NODE * next;
}Node;

typedef struct STR_QUEUE {
	Node *front;	//����
	Node *rear;		//��β
	int items;		//��Ŀ����
}Queue;

typedef enum ENUM_ERR_CODE_QUEUE{
    queue_false= -1,
    queue_unknow= 0,
    queue_true=1
} QCode;

//extern Queue gQueue1;

void InitQueue(Queue *pq);               //��ʼ������
QCode PushQueue(Queue *pq, void * item);	//��ӣ������β��������
QCode PopQueue(Queue *pq, void **item);	//���ӣ������β��������
QCode QueueIsFull(const Queue *pq);		//�������Ƿ�����
QCode QueueIsEmpty(const Queue *pq);		//�������Ƿ�Ϊ��
int  GetQueueCount(const Queue *pq);	//��ȡ������Ŀ����
void EmptyQueue(Queue *pq);				//��ն���
void PrintQueue(const Queue *pq);    //��ӡ����
#endif //_QUEUE_H