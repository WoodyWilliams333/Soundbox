/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app gprs模块</strong> 相关的接口
	 * @par 文件    appgprs.h
	 * @author		yangjing
	 * @date        2020-04-21
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-21    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-15    | 1.0.1        | lydia         | 增加英文注释  
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
	@defgroup appgprs 无线网络
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
	@brief          检测sim卡状态
	@return         0		-	sim卡存在，状态正常
	@return         其它	-	sim卡不存在
 @else
	@brief          check sim card status
	@return         0		-	sim card exist and normal
	@return         other	-	sim card no exist
 @endif
*/    
extern int app_wireless_check_simcard(void);

/*!
 @if Chinese
	@brief          读取sim卡 iccid号
	@param[out]     psimcardid	-	iccid数据保存指针
	@param[in]      ilen		-	数据保存最大长度
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          读取模块imei号
	@param[out]     pimei	-	module imei数据保存指针
	@param[in]      ilen	-	数据保存最大长度
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          读取sim卡imsi号
	@param[out]     pimsi	-	sim imsi数据保存指针
	@param[in]      ilen	-	数据保存最大长度
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取相邻基站信息
	@param[out]     psBaseStationInfo	-	存放附近基站信息数据数组，最少6
	@param[in]      iNum				-	期望获取相邻基站的个数
	@param[out]     piOutNum			-	实际返回的相邻基站个数
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          get the information of nearby base stations
	@param[out]     psBaseStationInfo	-	data array for storing information，Minimum 6 groups
	@param[in]      iNum				-	expected to obtain the number of nearby base stations
	@param[out]     piOutNum			-	number of nearby base stations actually
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_gprs_get_nearby_basestation_info(tBaseStationExt *psBaseStationInfo, int iNum, int *piOutNum);

/*!
 @if Chinese
	@brief          获取基站信息
	@param[out]     psBaseStationInfo	-	基站信息
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取主基站信息
	@param[out]     psBaseStationInfo	-	基站信息
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取当前网络状态
	@param[out]     pstatus	-	网络状态
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取网络信号值
	@param[out]     puiSignal	-	信号值保存地址
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          附网
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          attached network
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_wireless_wnet_attach(void);


#endif
