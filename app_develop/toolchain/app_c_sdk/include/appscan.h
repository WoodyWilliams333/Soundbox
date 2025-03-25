/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app scan模块</strong> 相关的接口
	 * @par 文件    appscan.h
	 * @author		yangjing
	 * @date        2020-04-10
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-10    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-19    | 1.0.1        | lydia         | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app scan</strong>  module
	 * @par file    appscan.h
	 * @author		yangjing
	 * @date        2020-04-10
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-10    | 1.0.0        | yanjing       | create file
	 * 2022-04-19    | 1.0.1        | lydia         | Add English description
 @endif
*/

/*!
 @if Chinese
	@defgroup appscan 扫码
 @else
	@defgroup appscan scan
 @endif
 * @{
*/ 
#ifndef _APP_SCAN_H_
#define _APP_SCAN_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 @if Chinese
  * @brief  该枚举类型列出了<strong>磁条卡操作类函数返回值</strong>.
@else  
  * @brief  This enumerated type lists the <strong>return value of the magnetic stripe card operation class function</strong>.
@endif
*/
typedef enum 
{ 
	SCAN_EINVAL       	= -4,	/**<@if Chinese 参数错误 				@else	Parameter error							@endif*/
	SCAN_NOT_INIT       = -3,	/**<@if Chinese 设备未初始化 			@else	Device has not been initialized			@endif*/
	SCAN_DEV_ERR		= -2,	/**<@if Chinese 扫码设备异常 			@else	The code scanning device is abnormal	@endif*/
	SCAN_FAIL			= -1,	/**<@if Chinese 扫码失败 				@else	Sweep code failure						@endif*/
	SCAN_OK				=  0,	/**<@if Chinese 扫码成功 				@else	Sweep code success						@endif*/
	SCAN_NO_DATA		=  1,	/**<@if Chinese 无数据 					@else	No Data									@endif*/
	SCAN_DATA_TOO_LONG  =  2,   /**<@if Chinese 数据过长(超过缓冲大小) 	@else	Data too long (exceeding buffer size)	@endif*/
}ScanCodeRet; 



/**
@if Chinese
 * @brief  打开扫码模块
 * @param[in]	preview	-	是否开启预览开关
 * @param[in]	ledctrl	-	是否开启led背光开关
 * @param[in]	sound	-	是否打开扫码提示音
 * @return  参考ScanCodeRet定义
@else 
 * @brief  Open the scan module
 * @param[in]	preview	-	Whether to enable the preview switch
 * @param[in]	ledctrl	-	Whether to enable the LED backlight switch
 * @param[in]	sound	-	Whether to enable the scan prompt tone
 * @return  Refer to ScanCodeRet for definitions
@endif 
 */
int app_scan_open(appsw preview, appbool ledctrl, appbool sound);

/**
@if Chinese
 * @brief  关闭扫码模块 
 * @return  参考ScanCodeRet定义
@else 
 * @brief  Close the scan module 
 * @return  Refer to ScanCodeRet for definitions
@endif 
 */
extern int app_scan_close(void);

/**
@if Chinese
 * @brief  获取扫码数据
 * @param[out]	pScanMsg	-	扫码数据保存地址
 * @param[in]	uiMaxLen	-	扫码数据最大长度
 * @param[in]	uiWaitTime	-	等待超时时间
 * @return  参考ScanCodeRet定义
@else 
 * @brief  Get scan data
 * @param[out]	pScanMsg	-	Address for saving scan data
 * @param[in]	uiMaxLen	-	Maximum length of scanned data
 * @param[in]	uiWaitTime	-	wait timeout
 * @return  Refer to ScanCodeRet for definitions
@endif 
 */
extern int app_scan_get_data(byte *pScanMsg, uint uiMaxLen, uint uiWaitTime);

/**
@if Chinese
 * @brief  设置背光led灯
 * @param[in]	onoff	-	开/关
@else 
 * @brief  Set backlit LED lights
 * @param[in]	onoff	-	on/off
@endif 
 */
extern void app_scan_set_led(appbool onoff);

/**
@if Chinese
 * @brief  设置预览
 * @param[in]	onoff	-	开/关
 * @return  参考ScanCodeRet定义
@else 
 * @brief  Set preview
 * @param[in]	onoff	-	on/off
 * @return  Refer to ScanCodeRet for definitions
@endif 
 */
extern int app_scan_set_preview(appbool onoff);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __APP_SCAN_H__*/


