
#ifndef _COMM_PARA_H_
#define _COMM_PARA_H_

#include <appdatatypedef.h>
#include "comparam.h"

typedef struct _comm_para_strcut{
	CommType_e commType;					// 通讯参数
	uint8_t ucTpdu[6];						// TPDU
	ST_HOST_INFO stHost[2];					// 服务器信息
	uint8_t swPreDial;       				// 是否预拨号
	appsw swUsedSsl;						// 是否启用SSL,除http/https协议，其它报文的ssl控制
	appsw swUsedHttps;						// 是否启用https，只有http/https报文协议时使用
	appsw swUsedDNS;						// 是否启用域名
	
	appsw swLongConnection;					// 长连接开关
	uint8_t szDialNum[32+1];				// 接入点号码
	uint8_t	szDNS[32+1];
	
	uint8_t ucCommWaitTime;					// 通讯超时时间	
	uint8_t ucDialRetryTimes;				// 交易重播次数
	
	ST_TCPIP_INFO	  stTcpIpPara;	        // TCP 配置参数
	ST_WIRELESS_INFO  stWirlessPara;        // GRPS/CDMA无线通讯配置参数
	ST_WIFI_AP_INFO	  stWIFIApPara;	        // WIFI 通讯模式配置参数
}COMM_PARA_STRC;
#define COMM_PARA_SIZE	sizeof(COMM_PARA_STRC)
#endif
