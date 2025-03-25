
#ifndef _COMPARAM_H_
#define _COMPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <libwnet.h>

// ʹ�õ�ͨѶ�������Ŀ�����ʹ�ö�����ʱ����ע��ͨѶģ���ͳһ
#define MAX_COMM_HANDLER_NUM 2

typedef enum{
	TRANS_COMM_HANDLE = 0x00,	
	TMS_COMM_HANDLE,
}E_COMM_HANDLE_TYPE;


typedef enum{
	TCP_ONLY = 0x00,
		
	HANGUP_ALL,
}E_HANGUP_TYPE;


// HOST���ò���
typedef struct st_host_info{
	uint8_t	szHostIP[15+1];
	uint8_t	szHostPort[5+1];
}ST_HOST_INFO;

// tcp ��·����
typedef struct st_link_info{
	int iSocket;
}ST_LINK_INFO;


// TCP/IP���ò���
typedef struct st_tcpip_info{
	uint8_t	szNetMask[15+1];
	uint8_t	szGatewayIP[15+1];
	uint8_t	szLocalIP[15+1];
}ST_TCPIP_INFO;


// GPRS/CDMA configurations
typedef struct st_wireless_info{
	uint8_t	szAPN[64+1];  ///���ź��� CDMA: #777; GPRS: cmnet
	uint8_t	szUID[64+1];
	uint8_t	szPwd[16+1];
	uint8_t	szSimPin[16+1];     // SIM card PIN
}ST_WIRELESS_INFO;

// WIFI  AP ���ò���
typedef struct st_wifi_ap_info
{
	int iChannel;                  //  Wireless LAN communication channel(0 - 13)����ͨѶ�ŵ�
	int iSecurityType;             //  Sets the Wireless LAN security type. ���� ����ģʽ
	int iWEPKeyIdx;                //  WEP key index (1 - 4) -- WEP��Կ��
    char szListWEPKey[4][32];       //  4 sets of WEP Key  --- ��Կ����Կ
	char szWPAPSK[64];              //  Personal Shared Key Pass-Phrase,
	char szSSID[64];                //  SSID
}ST_WIFI_AP_INFO;


// ͨѶģ��������Ϣ
typedef struct st_comm_infog
{
	uint8_t	ucCommType;		    // ͨѶ����(RS232/gprs/wifi)
	uint8_t bUsedSss;			// �Ƿ�����SSL
	ST_HOST_INFO stHostPara;	// ������Ϣ
}ST_COMM_INFO, *LPCOMM_INFO;



#ifdef __cplusplus
}
#endif

#endif

