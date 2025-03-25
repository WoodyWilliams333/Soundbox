 /*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app wifi模块</strong> 相关的接口
	 * @par 文件    appwifi.h
	 * @author		yangjing
	 * @date        2020-04-15
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-15    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-27    | 1.0.1        | wenming       | 增加英文注释 
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
	* @addtogroup app_wifi WIFI通讯
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
 * @brief	在热点搜索界面显示"连接成功,取消键返回注册"，仅支持2G终端
 * @param[in]	wifi_disp		-	显示和不显示
@else 
 * @brief	In the hotspot search interface,display "Key id Select"，2G terminal only
 * @param[in]	wifi_disp		-	display or not display
@endif 
 */
extern void app_wifi_disp_success(appbool wifi_disp);


/**
@if Chinese
 * @brief	打开wifi模块
 * @param[in]	opttime			-	操作时间
 * @param[in]	searchap		-	打开时是否搜索热点
 * @return  参考E_APP_RET定义
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
 * @brief 关闭wifi模块
 * @return  参考E_APP_RET定义
@else  
 * @brief Close the wifi module
 * @return  See E_APP_RET for definitions
@endif  
 */
extern int app_wifi_close(void);

/**
@if Chinese
 * @brief 连接热点
 * @param[in]	ssid			-	ssid名称
 * @param[in]	key				-	wifi密钥
 * @return  参考E_APP_RET定义
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
 * @brief 获取wifi本地ip地址
 * @param[out]	ip				-	ip地址字符串
 * @return  参考E_APP_RET定义
@else 
 * @brief Get the wifi local IP address
 * @param[out]	ip				-	IP address string
 * @return  See E_APP_RET for definitions
@endif 
 */
extern int app_wifi_get_localip(char *ip);

/**
@if Chinese
 * @brief 检测wifi是否已连接热点
 * @return		app_true 		-	已连接;
 * @return		app_false		-	未连接热点
@else		
 * @brief Check whether wifi is connected to a hotspot
 * @return		app_true 		-	connected;
 * @return		app_false		-	Disconnected hotspot
@endif		
 */
extern appbool app_wifi_is_connected(void);

/**
@if Chinese
 * @brief 调用底层界面，搜索并链接热点
 * @param[in]	opttime			-	操作时间
 * @return  参考E_APP_RET定义
@else  
 * @brief Call the underlying interface to search for and link to hot spots
 * @param[in]	opttime			-	Operation time
 * @return  See E_APP_RET for definitions
@endif 
 */
extern int app_wifi_search_ap(int opttime);

/**
@if Chinese
 * @brief 获取wifi连接状态
 * @return  wifi连接状态，参考sdk相关定义
@else 
 * @brief Get wifi connection status
 * @return  Wifi connection status, refer to SDK definitions
@endif 
 */
extern int app_wifi_get_connect_status(void);

/**
@if Chinese
 * @brief 检测wifi状态
 * @return		app_true		-	wifi状态可用
 * @return		app_false		-	wifi状态不可用
@else  
 * @brief Check wifi Status
 * @return		app_true		-	Wifi status available
 * @return		app_false		-	Wifi is unavailable
@endif 
 */
appbool app_wifi_check(void);

/**
@if Chinese
 * @brief 配置WIFI功能
 * @param[in]	fix_ip			-	静态IP
 * @param[in]	gateway			-	网关
 * @param[in]	mask			-	子网掩码
 * @param[in]	primary_dns		-	首选DNS
 * @param[in]	sencond_dns		-	次选DNS
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

