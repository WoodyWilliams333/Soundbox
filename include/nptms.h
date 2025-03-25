
#ifndef __NP_TMS_H__
#define __NP_TMS_H__

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>
#include "tms_silence.h"


#define MAX_IP_LEN              16
#define MAX_DNS_LEN             32
#define MAX_IN_LEN              16
#define MAX_REMARK_INFO_LEN     256

enum TMS_LANGUAGE {
    DISP_IN_CHINESE = 0,
    DISP_IN_ENGLISE = 1,
};

enum TMS_COMM_SELECT {    
    SOLTNO_GPRS = 0,
    SOLTNO_WIFI = 1,
    SOLTNO_CDMA = 2, //reserved !!!
};

enum TMS_IP_DNS {
    TMS_IN_IP  = 0,
    TMS_IN_DNS = 1,
};

enum TMS_PARAM_IN {
    TMS_PARAM_INVALID_IN = 0,
    TMS_PARAM_VALID_IN   = 1,    
};

enum TMS_PARAM_OUT {
    TMS_PARAM_NO_RETURN  = 0,
    TMS_PARAM_RETURN     = 1,    
};

//TMS error list
enum TMS_ERROR_CODE {
    TMS_E_OK                = 0,    //交易成功
    TMS_E_PACKET            = -1,   //组包失败
    TMS_E_CONNECT           = -2,   //连接失败
    TMS_E_SEND              = -3,   //发送失败
    TMS_E_RECV              = -4,   //接收失败
    TMS_E_RECV_TIMEOUT      = -5,   //接收超时
    TMS_E_UNPACKET          = -6,   //解包失败
    TMS_E_RSPCODE           = -7,   //返回码错误 //暂时保留使用
    TMS_E_DNS               = -8,   //域名解析失败
    TMS_E_DELETE            = -9,   //删除失败
    TMS_E_GPRS_DEV          = -10,  //通讯设备不存在
    TMS_E_PPP_LOGIN         = -11,  //PPP登录失败
    TMS_E_PPP_TIMEOUT       = -12,  //PPP超时
    TMS_E_NO_SIM            = -13,  //SIM卡未插入
    TMS_E_DOWNLOAD          = -14,  //TMS下载失败，通常为库内部处理下载失败
    TMS_E_DOWNLOAD_CANCEL   = -15,  //TMS下载取消
    TMS_E_WIFI_DISC         = -16,  //WIFI未连接或连接失败
    TMS_E_NO_REGISTER       = -17,  //终端未初始化，未执行补登交易
    TMS_E_DESKTOP_FILE      = -18,  //Desktop file不存在或不合法
    TMS_E_WIFI_CLOSE        = -19,  //WIFI设备未打开
    TMS_E_COMM_DEV          = -20,  //通讯设备异常
    TMS_E_RSPCODE_BASE      = -50,  //TMS后台返回码错误，例如 -51表示返回码为"01"，-66表示返回码为"16"
    TMS_E_RSPCODE_END       = -100, //同上
    TMS_E_NO_DISP           = -127, //不显示信息，库内使用
    TMS_E_UNKNOW            = -128, //未知错误
};

typedef struct _np_tms_param_t {
    char        ip[MAX_IP_LEN];
    char        dns[MAX_DNS_LEN];
    uint16_t    port; 
    uint16_t    timeout;
    uint8_t     language; //see enum TMS_LANGUAGE
    uint8_t     comm_type; //see enum TMS_COMM_SELECT
    uint8_t     ipdns; //see enum TMS_IP_DNS
    char        apn[MAX_IN_LEN];
    char        user[MAX_IN_LEN];
    char        passwd[MAX_IN_LEN];
} np_tms_param_t;

/*
设置保存tms参数的回调函数，由外层调用者实现，参数可能存在文件系统中，也可能存在其他地方
*/
typedef int (*save_tms_param)(void *arg);

extern int tms_main(np_tms_param_t *param, int paramvalidin, int paramreturn, save_tms_param cb);

/////////////////////////////////////////////////////////////////////////////////////////////

//extern API for APP-TMS call

/*
用于应用程序向TMS库传入通讯参数，若使用库的默认参数，可传入NULL
与tms app deinit接口配套使用
返回0表示成功，其他表示失败
*/
int tms_app_init(void *param, int paramvalidin);

/*
用于TMS库向应用程序导出通讯参数，并清空库参数缓存，若不适用，可传入NULL
与tms app init接口配套使用
返回0表示成功，其他表示失败
*/
int tms_app_deinit(void *param, int paramreturn);

/*
仅当函数返回值为0，补登成功
其他情况，均为补登失败
*/
int tms_app_terminal_register(void);

/*
仅当函数返回值为0，表示查询成功，查询成功有以下2种可能:
1.查询成功，有应用需要下载更新: 此时updateflg将被赋值为1返回，且remarkinfo将返回待下载应用的备注信息(升级信息)
2.查询成功，当前版本是最新版本: 此时updateflg将被赋值为0返回，remarkinfo的内容可忽略
其他情况，均为查询失败
注意: remarkinfo的有效空间至少256字节
*/
int tms_app_check_update(int *updateflg, char *remarkinfo);

int tms_app_check_update_ex(int *updateflg, char *remarkinfo);//去掉显示


typedef struct _tms_update_result_t {
    int done;           //异步任务是否完成，应用层可以在发起异步任务前清空此标志，任务结束后，结果回调会置位此标志
    int ret;            //用于保存tms交易的返回值，见枚举 TMS_ERROR_CODE
    int updateflg;      //用于保存当前应用是否需要下载更新, 1表示需要下载更新，其他值表示不需要
    char remarkinfo[MAX_REMARK_INFO_LEN]; //用于保存服务器下发的应用的版本更新信息，至少256字节
} tms_update_result_t;



typedef int (*tms_result_cb)(tms_update_result_t *result);

/*
仅当函数返回值为0，表示发起异步任务成功
void *arg目前保留，可传入NULL
tms_result_cb cb用于保存tms更新信息结果的回调
注意事项:
应用发起异步任务，在代价空闲时间，可查询结果是否有返回，若返回有应用需要下载更新，则
再次调用远程下载接口进入下载
*/
int tms_app_check_update_async(void *arg, tms_result_cb cb);

/*
仅当函数返回值为0时，表示下载成功；此函数封装了下载、更新的连贯过程；
若顺利的话，从进入下载，就一直到提示重启更新，且为强制更新。
其他情况，均为下载失败
*/
int tms_app_download(void);

int tms_app_update_single(void);


/*
仅当函数返回值为0时，表示下载完全结束 ；此函数执行完后只完成下载；

下载结束由tms_update_tasks_ex提醒更新重启等流程。

返回其他值，均为下载失败
*/
int tms_app_download_ex(void);

//int tms_update_tasks_ex(void);//TMS更新流程 使用前先判断是否存在流水未处理


void checkstop(void);

int checkShow(void);

/*
返回0表示成功，其他表示失败
*/
int tms_app_delete_tmp_files(void);

/*
对应的参数传入NULL, 表示不获取该项版本信息；每一项传入有效buf，需至少16字节
返回0表示成功，其他表示失败
*/
int tms_app_get_versions(char *appname, char *appver, char *libtmsver);

/*
是否使能tms下载过程中，运行按取消键退出下载
传入0表示不允许取消，其他值表示运行取消；默认为不允许取消
*/
void tms_app_download_cancel_enable(int enable);

/*
获取tms库的版本号，version的空间至少32字节
*/
int tms_app_get_tms_version(char *version, int nbytes);

/*
获取返回值ret代表的含义，分别是中文显示和英文显示，传入buf至少32字节
返回值说明:
返回0时，可从msgcn和msgen中取出显示的msg;
若返回1，可从msgcn和msgen中取出显示的msg，此时终端补登交易也是成功的，应用需要做成功提示
若返回-1，表示此返回码表示无需显示;
*/
int tms_app_get_result_disp(int ret, char *msgcn, char *msgen);

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
