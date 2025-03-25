
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libwnet.h>
#include "apidef.h"
#include "comparam.h"
#include <wnet.h>

// �Ƿ�ʹ���첽ͨ�ſ���
//#define ASYNC_CONNECT	0


/** 
 * @brief  ͨѶģ���ʼ����
 		   �����ʼ�����ã���ʼ��ͨѶ����
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		��
**/
void CommModuleInit(void);
/** 
 * @brief  �ر�ͨѶģ�飬����socket��ppp�ȶ����Ҷ�
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		��
**/
void CommModuleExit(void);


//|------------------------------------------------------------------
//| ͨѶ��������
//|------------------------------------------------------------------
//| Init-->Paramset(-->Predial)-->connect-->send-->recv-->hangup
//|------------------------------------------------------------------

/** 
 * @brief  ͨ�Ų������ã���init֮��ɵ���
 		   ��Ԥ���ź�connect֮ǰ���������ò���!!
 * @note   
 * @param in  
		none
 * @param out
 		none
 * @retval 	
		��ʼ���ɹ�����0������-����
**/
	int CommParamSet(int comHandler, appbool DNSIP, ST_WIRELESS_PARAM *lpWirelessParam, ST_SSL_PARAM *lpSslParam);
/** 
 * @brief  Ԥ����
 * @note   
 * @param in  
		comHandler ͨ�ž����Ϊ���ͨ��ͨ��Ԥ��
		ST_HOST_PARAM ��������Ϣ,�첽ʱ��Ч
 * @param out
 		none
 * @retval 	
		��ʼ���ɹ�����0������-����
**/
int CommPreDial(int comHandler, ST_HOST_PARAM *lpHostParam);

/** 
 * @brief  ͨѶ��ʼ��
 * @note   
 * @param in  
		comHandler ͨѶ�����Ϊ���ͨ��ͨ��Ԥ��
		CommType_e ͨѶ����
		SockType_e ͨѶЭ��	
 * @param out
 		none
 * @retval 	
		��ʼ���ɹ�����0������-����
	ע�⣺��ʹ��WIFI��comm��ʼ��������wifi�豸��(wifi_open)֮�󣡣���
**/
int CommInit(int comHandler, CommType_e comtype, SockType_e protocoltype);

/** 
 * @brief DNS������ص� 
 * @note   
 * @param in  
			(param1)char* DNS����������ip
			(param2)int* DNS����������ip����
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
 * @brief  ����
 * @note   
 * @param in  
		comHandler ͨѶ�����Ϊ���ͨ��ͨ��Ԥ��
		ST_HOST_PARAM ��������Ϣ
		timeout ���ӳ�ʱʱ��	
		pSaveIpFunc DSN������ص�������������IP
		ע�⣬ֻ����ʹ�õ�DNS�����ӳɹ��󣬲Ż���øûص�
 * @param out
 		none
 * @retval 	
		��ʼ���ɹ�����0������-����
**/
int CommConnect(int comHandler, ST_HOST_PARAM *lpHostParam, uint32_t timeout, pAfterDNSCallback pSaveIpFunc);

/** 
 * @brief  �Ҷ�
 * @note   
 * @param in  
		comHandler ͨѶ�����Ϊ���ͨѶͨ��Ԥ��
 * @param out
 		none
 * @retval 	
		��ʼ���ɹ�����0������-����
**/
int CommHangUp(int comHandler);
/** 
 * @brief  ����
 * @retval 	
		��ʼ���ɹ�����0������-����
**/
int CommSend(int comHandler, void *psendbuf, int bytes, uint32_t timeout);

typedef void (*pRecvDispFc)(void *param);
/** 
 * @brief  ����
 * @retval 	
		��ʼ���ɹ�����0������-����
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

