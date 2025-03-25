
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libwnet.h>
#include "apidef.h"
#include "comparam.h"
#include <wnet.h>

// 是否使用异步通信开关
//#define ASYNC_CONNECT	0


/** 
 * @brief  通讯模组初始化，
 		   程序初始化调用，初始化通讯变量
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		无
**/
void CommModuleInit(void);
/** 
 * @brief  关闭通讯模组，所有socket及ppp等都将挂断
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		无
**/
void CommModuleExit(void);


//|------------------------------------------------------------------
//| 通讯调用流程
//|------------------------------------------------------------------
//| Init-->Paramset(-->Predial)-->connect-->send-->recv-->hangup
//|------------------------------------------------------------------

/** 
 * @brief  通信参数设置，在init之后可调用
 		   在预拨号和connect之前必须先设置参数!!
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		初始化成功返回0，其它-错误
**/
	int CommParamSet(int comHandler, appbool DNSIP, ST_WIRELESS_PARAM *lpWirelessParam, ST_SSL_PARAM *lpSslParam);
/** 
 * @brief  预拨号
 * @note   
 * @param in  
		comHandler 通信句柄，为多个通信通道预留
		ST_HOST_PARAM 服务器信息,异步时有效
 * @param out
 		none
 * @retval 	
		初始化成功返回0，其它-错误
**/
int CommPreDial(int comHandler, ST_HOST_PARAM *lpHostParam);

/** 
 * @brief  通讯初始化
 * @note   
 * @param in  
		comHandler 通讯句柄，为多个通信通道预留
		CommType_e 通讯类型
		SockType_e 通讯协议	
 * @param out
 		none
 * @retval 	
		初始化成功返回0，其它-错误
	注意：若使用WIFI，comm初始化必须在wifi设备打开(wifi_open)之后！！！
**/
int CommInit(int comHandler, CommType_e comtype, SockType_e protocoltype);

/** 
 * @brief DNS解析后回调 
 * @note   
 * @param in  
			(param1)char* DNS解析出来的ip
			(param2)int* DNS解析出来的ip个数
 * @param out
 		none
 * @retval 	
		none
**/
typedef void (*pAfterDNSCallback)(char [MAX_IP_CNT][MAX_IP_LEN], int );

int CommChkPredial(int comHandler);

#ifdef ASYNC_CONNECT_TCP
appbool CommChkIfPreDial(void);
int CommChkPreConnect(int comHandler, ST_HOST_PARAM *lpHostParam, uint32_t timeout, pAfterDNSCallback pSaveIpFunc);
int CommChkSocketState(int comHandler);
#endif

/** 
 * @brief  连接
 * @note   
 * @param in  
		comHandler 通讯句柄，为多个通信通道预留
		ST_HOST_PARAM 服务器信息
		timeout 连接超时时间	
		pSaveIpFunc DSN解析后回调，可用来保存IP
		注意，只有在使用的DNS且连接成功后，才会调用该回调
 * @param out
 		none
 * @retval 	
		初始化成功返回0，其它-错误
**/
int CommConnect(int comHandler, ST_HOST_PARAM *lpHostParam, uint32_t timeout, pAfterDNSCallback pSaveIpFunc);

/** 
 * @brief  挂断
 * @note   
 * @param in  
		comHandler 通讯句柄，为多个通讯通道预留
 * @param out
 		none
 * @retval 	
		初始化成功返回0，其它-错误
**/
int CommHangUp(int comHandler);
/** 
 * @brief  发送
 * @retval 	
		初始化成功返回0，其它-错误
**/
int CommSend(int comHandler, void *psendbuf, int bytes, uint32_t timeout);

typedef void (*pRecvDispFc)(void *param);
/** 
 * @brief  接收
 * @retval 	
		初始化成功返回0，其它-错误
**/
int CommRecv(int comHandler, void *precvbuf, int bytes, uint32_t timeout, pRecvDispFc DispCb);

int CommRecvhttp(int comHandler, void *precvbuf, int bytes, uint32_t timeout, pRecvDispFc DispCb);

#if 1
typedef struct{
	tBaseStationExt stBaseStation;
	uint32_t timeoutms;
	int commtype;	
}CommBaseStation_t;

void CommGetBaseStation(CommBaseStation_t *oBaseStationExt);

appbool CheckGetBaseStation(void);

appbool CheckBaseStationValid(tBaseStationExt oBaseStation);

void GetBaseStation(void *oBaseStationExt);
#endif
#ifdef __cplusplus
}
#endif

#endif

