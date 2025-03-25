/*
 * @Description: api bluetooth function
 * @Author: YangJing
 * @Date: 2020-06-29 14:26:33
 * @LastEditors: YangJing
 * @LastEditTime: 2020-08-20 14:14:33
 */ 
#ifndef _APP_BLUE_TOOTH_H_
#define _APP_BLUE_TOOTH_H_

#define NO_BT_API 1

#ifndef NO_BT_API
#include "bluetooth_bnep.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    BT_NO_CONNCET = 0,
    BT_VISIBLE,
    BT_CONNECTING,
    BT_CONNECTED,

    BT_STATUS_UNKNOW
}E_BT_STATUS;

typedef enum{
    BT_OK               = 0,
    BT_NOT_OPEN         = -1,
    BT_OPEN_FAILED      = -2,
    BT_NOT_CONNECTED    = -3,
    BT_CONNECT_FAILED   = -4,
    BT_PARA_ERR         = -5,
    BT_CMD_FAILED       = -6,
    BT_NOT_SUPPORT      = -7,
    BT_NEED_RECONNECT   = -8,
}E_BT_ERROR;

typedef enum{
    BNEP_RES_CONNECTED          = 0,
    BNEP_RES_CONNECTING         = 0x02,
    BNEP_RES_CONNECTTIMETOUT    = 0xFF,
    BNEP_RES_NONSUPPORT         = 0xFE,
}E_BT_RESPON;

int app_bt_init(void);
E_BT_STATUS app_bt_get_status(void);

int app_bt_connect_ready(void);
int app_bt_connect_wait(int timeout);
int app_bt_connect(char *pwd);
int app_bt_close(void);

int app_bt_set_name(char *btname);
int app_bt_get_name(char *btname, int size);

/*
breconnect  控制bnep已连接时，是否需要断开连接重连
            若需要重连，则接口返回BT_NEED_RECONNECT,此时，需要等待
            蓝牙状态为BT_VISIBLE，才能继续重连
*/
int app_bnep_conenct(int timeoutms, appbool breconnect);
int app_bnep_disconnect(void);
int app_bnep_get_status(void);

#ifdef __cplusplus
}
#endif

#endif