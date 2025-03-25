 /*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app wifiģ��</strong> ��صĽӿ�
	 * @par �ļ�    appwifi.h
	 * @author		yangjing
	 * @date        2020-04-15
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-15    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-27    | 1.0.1        | wenming       | ����Ӣ��ע�� 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app wifi </strong>  module
	 * @par file    appwifi.h
	 * @author		yangjing
	 * @date        2020-04-15
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-15    | 1.0.0        | yanjing       | create file
	 * 2022-04-27    | 1.0.1        | wenming       | Add English description
 @endif 
*/

/*!
 @if Chinese
	* @addtogroup app_wifi WIFIͨѶ
 @else 
	* @addtogroup app_wifi WIFI
 @endif 
 * @{
*/

#ifndef _APP_WIFI_H_
#define _APP_WIFI_H_


#include <wifi.h>
#include <appdatatypedef.h>

/**
@if Chinese
 * @brief	���ȵ�����������ʾ"���ӳɹ�,ȡ��������ע��"����֧��2G�ն�
 * @param[in]	wifi_disp		-	��ʾ�Ͳ���ʾ
@else 
 * @brief	In the hotspot search interface,display "Key id Select"��2G terminal only
 * @param[in]	wifi_disp		-	display or not display
@endif 
 */
extern void app_wifi_disp_success(appbool wifi_disp);


/**
@if Chinese
 * @brief	��wifiģ��
 * @param[in]	opttime			-	����ʱ��
 * @param[in]	searchap		-	��ʱ�Ƿ������ȵ�
 * @return  �ο�E_APP_RET����
@else 
 * @brief	Open the wifi module
 * @param[in]	opttime			-	Operating time
 * @param[in]	searchap		-	Search for hotspots when on
 * @return  See E_APP_RET for definitions
@endif 
 */
extern int app_wifi_open(int opttime, appbool searchap);

/**
@if Chinese
 * @brief �ر�wifiģ��
 * @return  �ο�E_APP_RET����
@else  
 * @brief Close the wifi module
 * @return  See E_APP_RET for definitions
@endif  
 */
extern int app_wifi_close(void);

/**
@if Chinese
 * @brief �����ȵ�
 * @param[in]	ssid			-	ssid����
 * @param[in]	key				-	wifi��Կ
 * @return  �ο�E_APP_RET����
@else  
 * @brief connect hotspot
 * @param[in]	ssid			-	ssid name
 * @param[in]	key				-	wifi password
 * @return  See E_APP_RET for definitions
@endif  
 */
extern int app_wifi_connect_ap(char *ssid, char *key);

/**
 @if Chinese
 * @brief ��ȡwifi����ip��ַ
 * @param[out]	ip				-	ip��ַ�ַ���
 * @return  �ο�E_APP_RET����
@else 
 * @brief Get the wifi local IP address
 * @param[out]	ip				-	IP address string
 * @return  See E_APP_RET for definitions
@endif 
 */
extern int app_wifi_get_localip(char *ip);

/**
@if Chinese
 * @brief ���wifi�Ƿ��������ȵ�
 * @return		app_true 		-	������;
 * @return		app_false		-	δ�����ȵ�
@else		
 * @brief Check whether wifi is connected to a hotspot
 * @return		app_true 		-	connected;
 * @return		app_false		-	Disconnected hotspot
@endif		
 */
extern appbool app_wifi_is_connected(void);

/**
@if Chinese
 * @brief ���õײ���棬�����������ȵ�
 * @param[in]	opttime			-	����ʱ��
 * @return  �ο�E_APP_RET����
@else  
 * @brief Call the underlying interface to search for and link to hot spots
 * @param[in]	opttime			-	Operation time
 * @return  See E_APP_RET for definitions
@endif 
 */
extern int app_wifi_search_ap(int opttime);

/**
@if Chinese
 * @brief ��ȡwifi����״̬
 * @return  wifi����״̬���ο�sdk��ض���
@else 
 * @brief Get wifi connection status
 * @return  Wifi connection status, refer to SDK definitions
@endif 
 */
extern int app_wifi_get_connect_status(void);

/**
@if Chinese
 * @brief ���wifi״̬
 * @return		app_true		-	wifi״̬����
 * @return		app_false		-	wifi״̬������
@else  
 * @brief Check wifi Status
 * @return		app_true		-	Wifi status available
 * @return		app_false		-	Wifi is unavailable
@endif 
 */
appbool app_wifi_check(void);

/**
@if Chinese
 * @brief ����WIFI����
 * @param[in]	fix_ip			-	��̬IP
 * @param[in]	gateway			-	����
 * @param[in]	mask			-	��������
 * @param[in]	primary_dns		-	��ѡDNS
 * @param[in]	sencond_dns		-	��ѡDNS
@else  
 * @brief config wifi param
 * @param[in]	fix_ip			-	fix ip
 * @param[in]	gateway			-	gateway
 * @param[in]	mask			-	mask
 * @param[in]	primary_dns		-	primary dns
 * @param[in]	sencond_dns		-	sencond dns
@endif 
 */
#if 0
extern int app_wifi_param_config(const char *ssid,
								 unsigned char fix_ip[4],
								 unsigned char gateway[4],
								 unsigned char mask[4],
								 unsigned char primary_dns[4],
								 unsigned char sencond_dns[4]);
#endif
#endif

