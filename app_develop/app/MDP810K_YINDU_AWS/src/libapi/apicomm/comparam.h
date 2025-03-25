
#ifndef _COMPARAM_H_
#define _COMPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <libwnet.h>

// 使用的通讯类最大数目，如果使用多个句柄时，请注意通讯模块的统一
#define MAX_COMM_HANDLER_NUM 2

typedef enum{
	TRANS_COMM_HANDLE = 0x00,	
	TMS_COMM_HANDLE,
}E_COMM_HANDLE_TYPE;


typedef enum{
	TCP_ONLY = 0x00,
		
	HANGUP_ALL,
}E_HANGUP_TYPE;


// HOST配置参数
typedef struct st_host_info{
	uint8_t	szHostIP[15+1];
	uint8_t	szHostPort[5+1];
}ST_HOST_INFO;

// tcp 链路参数
typedef struct st_link_info{
	int iSocket;
}ST_LINK_INFO;


// TCP/IP配置参数
typedef struct st_tcpip_info{
	uint8_t	szNetMask[15+1];
	uint8_t	szGatewayIP[15+1];
	uint8_t	szLocalIP[15+1];
}ST_TCPIP_INFO;


// GPRS/CDMA configurations
typedef struct st_wireless_info{
	uint8_t	szAPN[64+1];  ///拨号号码 CDMA: #777; GPRS: cmnet
	uint8_t	szUID[64+1];
	uint8_t	szPwd[16+1];
	uint8_t	szSimPin[16+1];     // SIM card PIN
}ST_WIRELESS_INFO;

// WIFI  AP 配置参数
typedef struct st_wifi_ap_info
{
	int iChannel;                  //  Wireless LAN communication channel(0 - 13)－－通讯信道
	int iSecurityType;             //  Sets the Wireless LAN security type. －－ 加密模式
	int iWEPKeyIdx;                //  WEP key index (1 - 4) -- WEP密钥组
    char szListWEPKey[4][32];       //  4 sets of WEP Key  --- 密钥组密钥
	char szWPAPSK[64];              //  Personal Shared Key Pass-Phrase,
	char szSSID[64];                //  SSID
}ST_WIFI_AP_INFO;


// 通讯模块配置信息
typedef struct st_comm_infog
{
	uint8_t	ucCommType;		    // 通讯类型(RS232/gprs/wifi)
	uint8_t bUsedSss;			// 是否启用SSL
	ST_HOST_INFO stHostPara;	// 主机信息
}ST_COMM_INFO, *LPCOMM_INFO;



#ifdef __cplusplus
}
#endif

#endif

