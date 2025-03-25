
#ifndef _COMM_PARA_H_
#define _COMM_PARA_H_

#include <appdatatypedef.h>
#include "comparam.h"

typedef struct _comm_para_strcut{
	CommType_e commType;					// ͨѶ����
	uint8_t ucTpdu[6];						// TPDU
	ST_HOST_INFO stHost[2];					// ��������Ϣ
	uint8_t swPreDial;       				// �Ƿ�Ԥ����
	appsw swUsedSsl;						// �Ƿ�����SSL,��http/httpsЭ�飬�������ĵ�ssl����
	appsw swUsedHttps;						// �Ƿ�����https��ֻ��http/https����Э��ʱʹ��
	appsw swUsedDNS;						// �Ƿ���������
	
	appsw swLongConnection;					// �����ӿ���
	uint8_t szDialNum[32+1];				// ��������
	uint8_t	szDNS[32+1];
	
	uint8_t ucCommWaitTime;					// ͨѶ��ʱʱ��	
	uint8_t ucDialRetryTimes;				// �����ز�����
	
	ST_TCPIP_INFO	  stTcpIpPara;	        // TCP ���ò���
	ST_WIRELESS_INFO  stWirlessPara;        // GRPS/CDMA����ͨѶ���ò���
	ST_WIFI_AP_INFO	  stWIFIApPara;	        // WIFI ͨѶģʽ���ò���
}COMM_PARA_STRC;
#define COMM_PARA_SIZE	sizeof(COMM_PARA_STRC)
#endif
