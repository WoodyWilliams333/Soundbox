/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app gprsģ��</strong> ��صĽӿ�
	 * @par �ļ�    appgprs.h
	 * @author		yangjing
	 * @date        2020-04-21
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-21    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-15    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app gprs </strong>  module
	 * @par file    appgprs.h
	 * @author		yangjing
	 * @date        2020-04-21
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-21    | 1.0.0        | yanjing       | create file
	 * 2022-04-15    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup appgprs ��������
 @else
	@defgroup appgprs gprs
 @endif
 * @{
*/ 
#ifndef _APP_GPRS_H_
#define _APP_GPRS_H_

#include <network.h>
#include <wnet.h>

#include "appdatatypedef.h"

/*!
 @if Chinese
	@brief          ���sim��״̬
	@return         0		-	sim�����ڣ�״̬����
	@return         ����	-	sim��������
 @else
	@brief          check sim card status
	@return         0		-	sim card exist and normal
	@return         other	-	sim card no exist
 @endif
*/    
extern int app_wireless_check_simcard(void);

/*!
 @if Chinese
	@brief          ��ȡsim�� iccid��
	@param[out]     psimcardid	-	iccid���ݱ���ָ��
	@param[in]      ilen		-	���ݱ�����󳤶�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          read iccid of sim card
	@param[out]     psimcardid	-	cid data buffer 
	@param[in]      ilen		-	data length
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_wireless_read_simcard_id(char *psimcardid, int ilen);

/*!
 @if Chinese
	@brief          ��ȡģ��imei��
	@param[out]     pimei	-	module imei���ݱ���ָ��
	@param[in]      ilen	-	���ݱ�����󳤶�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          read module imei
	@param[out]     pimei	-	imei data buffer 
	@param[in]      ilen	-	data length
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_wireless_read_imei(char *pimei, int ilen);

/*!
 @if Chinese
	@brief          ��ȡsim��imsi��
	@param[out]     pimsi	-	sim imsi���ݱ���ָ��
	@param[in]      ilen	-	���ݱ�����󳤶�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          read sim card imsi
	@param[out]     pimsi	-	imsi data buffer 
	@param[in]      ilen	-	data length
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_wireless_read_imsi(char *pimsi, int ilen);

/*!
 @if Chinese
	@brief          ��ȡ���ڻ�վ��Ϣ
	@param[out]     psBaseStationInfo	-	��Ÿ�����վ��Ϣ�������飬����6
	@param[in]      iNum				-	������ȡ���ڻ�վ�ĸ���
	@param[out]     piOutNum			-	ʵ�ʷ��ص����ڻ�վ����
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get the information of nearby base stations
	@param[out]     psBaseStationInfo	-	data array for storing information��Minimum 6 groups
	@param[in]      iNum				-	expected to obtain the number of nearby base stations
	@param[out]     piOutNum			-	number of nearby base stations actually
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_gprs_get_nearby_basestation_info(tBaseStationExt *psBaseStationInfo, int iNum, int *piOutNum);

/*!
 @if Chinese
	@brief          ��ȡ��վ��Ϣ
	@param[out]     psBaseStationInfo	-	��վ��Ϣ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get the information of base station
	@param[out]     psBaseStationInfo	-	data buffer for storing information
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_wireless_get_basestation_info(tBaseStationExt *psBaseStationInfo);

/*!
 @if Chinese
	@brief          ��ȡ����վ��Ϣ
	@param[out]     psBaseStationInfo	-	��վ��Ϣ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get the information of main base station
	@param[out]     psBaseStationInfo	-	data buffer for storing information
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_wireless_get_mainstation_info(tBaseStation *psBaseStationInfo);

/*!
 @if Chinese
	@brief          ��ȡ��ǰ����״̬
	@param[out]     pstatus	-	����״̬
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get current network status
	@param[out]     pstatus	-	network status
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_wireless_wnet_get_network_info(GPRS_NETWORK_STATUS_T *pstatus);

/*!
 @if Chinese
	@brief          ��ȡ�����ź�ֵ
	@param[out]     puiSignal	-	�ź�ֵ�����ַ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get current network signal
	@param[out]     puiSignal	-	network sig
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_gprs_get_network_signal(int *puiSignal);

/*!
 @if Chinese
	@brief          ����
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          attached network
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_wireless_wnet_attach(void);


#endif
