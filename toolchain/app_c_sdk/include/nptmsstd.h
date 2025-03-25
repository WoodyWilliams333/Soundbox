/*
 * @Description: 
 *      TMS库的若干说明:
 *          1.tms采用任务流和多步骤的模式来实现各tms交易功能:
 *            每个tms交易由一个或多个任务组成任务流，任务流依次逐个执行。
 *            每个任务又分成一个或若干个步骤来执行，每个步骤耗时极短。
 *            通过这样的模式达到tms交易过程(异步方式时)中可及时响应外部请求的效果
 *            备注: 由于底层connect接口的阻塞问题，在tcp连接异常超时时无法达到及时响应的效果，这种情况特殊.
 *          2.tms库分为同步和异步两种方式，
 *              1)同步方式时，调用接口阻塞执行完成
 *              2)异步方式时，tms交易在一子线程内完成，此方式可及时响应其它tms接口
 *              3)同步与异步方式在tms初始化设置，且不可更改
 *          3.异步方式时，tms交易增加了优先级处理，优先级高的接口调用后，会打断正在执行的低优先级交易。
 *            优先级设置如下: quit = delete > register = checkupdte = download
 * @Author: YangJing
 * @Date: 2021-03-17 11:51:54
 * @LastEditors: YangJing
 * @LastEditTime: 2021-04-19 15:54:36
 */

#ifndef __NP_TMS_STD_H__
#define __NP_TMS_STD_H__

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>

enum TMS_COMM_SELECT {    
    SOLTNO_GPRS = 0,
    SOLTNO_WIFI = 1,
    SOLTNO_CDMA = 2, //reserved !!!
};  // TMS通讯方式

enum TMS_IP_DNS {
    TMS_IN_IP  = 0,
    TMS_IN_DNS = 1,
}; // 使用ip还是dns域名解析方式

enum TMS_WORK_MODE {
    TMS_IN_SYNC  = 0,
    TMS_IN_ASYNC = 1,
}; // 同步/异步模式

enum TMS_ASYNC_MODE {
    TMS_IN_SHOW  = 0,
    TMS_IN_SILENCE = 1,
    TMS_IN_SILENCE_FORBID = 2,  // 禁止静默，强制显示
}; // 异步模式时，是否显示TMS界面

enum TMS_FLAG {
    TMS_FLAG_FALSE = 0,
    TMS_FLAG_TRUE = 1,
    TMS_FLAG_NOW = 2,
}; // nptsm真假宏定义

typedef enum {
    TMS_REGISTER = 2050,            // 补登
    TMS_CHECK_UPDATE = 2020,        // 巡检
    TMS_REMOTE_DOWNLOAD = 2000,     // 下载
    TMS_DOWNLOADED_NOTICE = 2010,   // 下载通知

    TMS_QUIT = 3001,                // 退出/中断当前交易
    TMS_DELETE,                     // 删除下载
    TMS_UPDATE,                     // 更新应用
}tms_trans_code_e; // 交易类型

typedef enum {
    TASK_REGISTER = 1,
    TASK_CHECKUPDATE,
    TASK_DOWNLOAD,
    TASK_DOWNLOADED_NOTICE,
    TASK_QUIT,
    TASK_DELETE,
    TASK_UPDATE,

    // 下载过程中的子任务
    TASK_DL_SHARKHANDS = 0x100,
    TASK_DL_VERIFY_REQ,
    TASK_DL_VERIFY_RESP,
    TAKS_DL_GET_LIST,
    TAKS_DL_ANASLYSE_LIST,
    TASK_DL_LOADING,
    TASK_DL_FINISH,
}task_id_e; //任务类型

#define TMS_MAX_IP_LEN              32
#define TMS_MAX_DNS_LEN             256
#define TMS_MAX_IN_LEN              100

#define TMS_MAX_REMARKS_LEN         256
// #define LEN_RSP_CODE            2

typedef struct _np_tms_respone_t {
    int errcode;                                // 执行结果
    int rspcode;                                // 后台响应结果
    uint8_t newverflag;                         // 新版本标识，值为TMS_FLAG_TRUE表示有新版本应用待下载
    uint8_t updateflag;                         // 可更新标识，值为TMS_FLAG_TRUE表示下载完成,可执行更新
    uint8_t updateabsolutely;                   // 强制更新标识, 值为TMS_FLAG_TRUE表示强制更新
    char newverremark[TMS_MAX_REMARKS_LEN];     // 新版本备注信息
} np_tms_respone_t;                             // tms交易应答回调参数


typedef int (*pnptmsrespcb)(np_tms_respone_t *, void *arg); 

typedef struct _np_tms_param_t {
    // 可配置参数，初始化或nptms_config接口均可配置参数
    char            ip[TMS_MAX_IP_LEN];         // tms通讯域名, ipdns为TMS_IN_DNS时有效
    char            dns[TMS_MAX_DNS_LEN];       // tms通讯ip, ipdns为TMS_IN_IP时有效
    unsigned short        port;                 // tms通讯端口 
    unsigned short        timeout;              // 通讯包接收超时时间(ms)，最小100ms
    unsigned short        spacelimit;           // 限制下载存储空间(kb),最小100kb
    unsigned char         comm_type; 			// see enum TMS_COMM_SELECT
    unsigned char         ipdns; 				// see enum TMS_IP_DNS
    unsigned char         asyncmode;            // see enum TMS_WORK_MODE
    unsigned char         silence;              // see enum TMS_ASYNC_MODE
    
    // 初始化时可配置参数
    const char*     appdir;                     // 应用工作目录
    int             (*autoruncb)(void *);       // 静默自动运行函数(定时时间或立即巡检等)
    unsigned int    silenceperoid;              // 静默下载执行周期,单位（s),最小6小时
    // pnptmsrespcb    silenrespcb;             // 静默时自动巡检后的处理

    // 以下参数为库控制, 应用不可配置以下参数
    // int             async_dl_run;            // 异步下载是否正在运行
} np_tms_param_t;

/**
 * @brief: tms参数初始化
 * @return 
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *  {np_tms_param_t} *para  参数结构，详细见np_tms_param_t定义
 */
extern int nptms_init(np_tms_param_t *para);

/**
 * @brief:  启动tms静默服务，只有在使用异步模式时有效 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param {none}
 */
extern int nptms_start_server(void);

/**
 * @brief:  TMS补登，补登结果传递给cb回调中 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_register(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS补登，补登结果传递给cb回调中 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_checkupdate(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS下载，下载结果传递给cb回调中 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_download(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS更新，更新结果传递给cb回调中 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_update(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS删除下载，结果传递给cb回调中 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_delete_dl(pnptmsrespcb cb, void *arg);

/**
 * @brief:  退出当前TMS操作 
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {pnptmsrespcb} cb   执行结果通知回调函数
 * @param 
 *      {void} *arg     回调函数传参
 */
extern int nptms_quit(pnptmsrespcb cb, void *arg);

/**
 * @brief:  tms参数配置, np_tms_param_t内可配置的参数才有效
 *          可一次配置多个参数，由arraynum控制配置参数数目
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {const char**} namearary 配置参数名称串数组，配置参数的名称即np_tms_param_t内的成员变量名字符串
 * @param 
 *      {const void **} valuearray 一组指针配置参数值的指针数组, 各指针的类型 严格与 配置参数的类型 相匹配! 
 * @param 
 *      {int} arraynum 配置参数的个数，即namearary和valuearray数组的大小
 */
extern int nptms_config(const char **namearary, const void **valuearray, int arraynum);

/**
 * @brief:  获取错误码string串
 * @return 
 *      {char *}  返回的string串指针，string为const char[], 不需要释放，也不能修改!
 * @param 
 *      {int} code 错误码
 */
extern const char* nptms_get_errcode_string(int code);

/**
 * @brief:  获取后台应答码string串
 * @return
 *      {char *}  返回的string串指针，string为const char[], 不需要释放，也不能修改!
 * @param 
 *      {int} code  应答码
 */
extern const char* nptms_get_respcode_string(int code);

/**
 * @brief:  获取库版本信息
 * @return
 *      0   -   成功
 *      其它 -  失败
 * @param 
 *      {char} *version     版本信息保存地址
 * @param 
 *      {int} size          version大小
 */
extern int nptms_get_version(char* version, int size);

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
