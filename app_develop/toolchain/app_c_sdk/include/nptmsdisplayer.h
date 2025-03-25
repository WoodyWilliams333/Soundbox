/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-04-22 08:39:44
 * @LastEditors: YangJing
 * @LastEditTime: 2021-05-13 08:32:57
 */

#ifndef _NP_TMS_DISPLYAER_H_
#define _NP_TMS_DISPLYAER_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

typedef struct {
    int missiontotallen;                // 当前任务总长度
    int missiondownloadlen;             // 当前任务已下载长度
    int totallen;                       // 下载总长度
    int downloadlen;                    // 已下载总长度
}notifydl_st;

typedef struct {
    int errcode;                       // 更新结果
}notifyupdate_st;

typedef struct {
    int transid;                        // TMS交易id
    int taskid;                         // 任务id
    int step;                           // 步骤id
    int state;                          // 步骤状态
    int leftms;                         // 步骤执行剩余时间
    const char *modname;                // 模块名称
    int missionid;                      // 模块id

    union {
        notifydl_st dlinfo;             // 下载信息             
        notifyupdate_st updateinfo;     // 更新信息
    } curinfo;
}notifypara_st;

typedef void (*recv_state_change)(notifypara_st *); // 观察者接收通知回调

typedef struct {
    recv_state_change recver;    
}displayerobv_st;   // 显示观察者结构

/**
 * @brief: 获取TMS交易名称
 * @return {none}
 * @param 
 *      {int} transid   tms交易id
 * @param 
 *      {char} *name    交易名称缓存地址
 * @param 
 *      {int} size      缓存大小
 */
extern void nptms_get_trans_name(int transid, char *name, int size);

/**
 * @brief: 获取TMS任务名称
 * @return {none}
 * @param 
 *      {int} taskid    tms任务id
 * @param 
 *      {char} *name    任务名称缓存地址
 * @param 
 *      {int} size      缓存大小
 */
extern void nptms_get_task_name(int taskid, char *name, int size);

/**
 * @brief: 获取TMS任务步骤名称
 * @return {none}
 * @param 
 *      {int} step   tms任务步骤id
 * @param 
 *      {char} *name    任务步骤名称缓存地址
 * @param 
 *      {int} size      缓存大小
 */
extern void nptms_get_step_name(int step, char *name, int size);

/**
 * @brief: 注册显示观察者，目前仅支持一个观察者
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 * {displayerobv_st} *obv 要注册观察者结构指针
 */
extern int nptms_registedisplayer(displayerobv_st *obv);    

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
