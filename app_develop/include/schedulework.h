
#ifndef _SCHEDULE_WORK_H_
#define _SCHEDULE_WORK_H_

#include "workqueue.h"

/****************************************************
初始化工作任务
workfunc [in] 工作执行的任务函数指针
workarg  [in] 任务函数参数指针
ST_WORK_NODE [out]  返回初始化任务实例

成功启动返回0，失败返回其它
*****************************************************/
int init_work(ST_WORK_NODE *work, pWorkFunc workfunc, void *workarg);

/****************************************************
分配任务，任务将在任务线程内执行(分配的任务按先入先出的顺序执行)
ST_WORK_NODE [in]  初始化后任务实例

成功启动返回0，失败返回其它
*****************************************************/
int schedule_work(ST_WORK_NODE *work);

#endif

