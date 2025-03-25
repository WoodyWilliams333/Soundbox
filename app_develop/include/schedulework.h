
#ifndef _SCHEDULE_WORK_H_
#define _SCHEDULE_WORK_H_

#include "workqueue.h"

/****************************************************
��ʼ����������
workfunc [in] ����ִ�е�������ָ��
workarg  [in] ����������ָ��
ST_WORK_NODE [out]  ���س�ʼ������ʵ��

�ɹ���������0��ʧ�ܷ�������
*****************************************************/
int init_work(ST_WORK_NODE *work, pWorkFunc workfunc, void *workarg);

/****************************************************
�������������������߳���ִ��(��������������ȳ���˳��ִ��)
ST_WORK_NODE [in]  ��ʼ��������ʵ��

�ɹ���������0��ʧ�ܷ�������
*****************************************************/
int schedule_work(ST_WORK_NODE *work);

#endif

