
#ifndef __NP_LED_H__
#define __NP_LED_H__

#include <stdint.h>
#include <errno.h>
#include "led.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum {
	LED_CHARGE		 = (1 << 4),				/**< 8 : 充电灯	 */
};


typedef enum{
    LED_SLOW_MODE = 0,
    LED_FAST_MODE = 1,
    LED_ON_MODE = 2,
    LED_OFF_MODE = 3,
}LITHT_SWITHC;

//亮灭的持续时间
typedef struct{
	int holdon_time1; 
	int holdon_time2;
}LITHT_ON_OFF_TIME;


typedef struct{
	int idx;
	int init_status;
	LITHT_ON_OFF_TIME period;
}LITHT_SWITHC_ST;


typedef enum
{

	TERM_POWEROFF,       //关机
	TERM_OTA_START,      //开始升级
	TERM_OTA_FAIL,       //升级失败
	TERM_OTA_OK,         //升级成功
	TERM_NET_CONNING,    //正在查找网络并连接
	TERM_NET_OK,         //联网成功
	TERM_NET_DISCON,     //5 网络断开
	TERM_LTE_NET_ABNORMAL,//mqtt服务持续时网络异常
 	TERM_NET_APMODE,      //处于配网状态
	TERM_PARAM_ERR,       //参数错误 阿里三元组信息等未下载
	TERM_CHARGEING,     //充电中
 	TERM_CHARGE_FULL,     //电量已充满
 	TERM_CHARGE_OFF,     //未在充电
	TERM_LOWBAT,          //10 低电提醒充电
	TERM_NO_SIM,          //无sim卡
	TERM_SERVER_OK,       //服务连接成功
	TERM_SERVER_DIS,      //服务断开

}LcdModeDef;



void init_led(void);

void app_set_light_status(int led_idx,LITHT_SWITHC sw);


int led_status_control(uint32_t idx_bits, uint32_t init_status, LITHT_ON_OFF_TIME period);


void app_set_led(int idx,int mode);


void setLedStatus(int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for __LED_H__ */

/** @} */

