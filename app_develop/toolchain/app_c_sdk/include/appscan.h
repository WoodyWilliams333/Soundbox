/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app scanģ��</strong> ��صĽӿ�
	 * @par �ļ�    appscan.h
	 * @author		yangjing
	 * @date        2020-04-10
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-10    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-19    | 1.0.1        | lydia         | ����Ӣ��ע��  
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
	@defgroup appscan ɨ��
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
  * @brief  ��ö�������г���<strong>�����������ຯ������ֵ</strong>.
@else  
  * @brief  This enumerated type lists the <strong>return value of the magnetic stripe card operation class function</strong>.
@endif
*/
typedef enum 
{ 
	SCAN_EINVAL       	= -4,	/**<@if Chinese �������� 				@else	Parameter error							@endif*/
	SCAN_NOT_INIT       = -3,	/**<@if Chinese �豸δ��ʼ�� 			@else	Device has not been initialized			@endif*/
	SCAN_DEV_ERR		= -2,	/**<@if Chinese ɨ���豸�쳣 			@else	The code scanning device is abnormal	@endif*/
	SCAN_FAIL			= -1,	/**<@if Chinese ɨ��ʧ�� 				@else	Sweep code failure						@endif*/
	SCAN_OK				=  0,	/**<@if Chinese ɨ��ɹ� 				@else	Sweep code success						@endif*/
	SCAN_NO_DATA		=  1,	/**<@if Chinese ������ 					@else	No Data									@endif*/
	SCAN_DATA_TOO_LONG  =  2,   /**<@if Chinese ���ݹ���(���������С) 	@else	Data too long (exceeding buffer size)	@endif*/
}ScanCodeRet; 



/**
@if Chinese
 * @brief  ��ɨ��ģ��
 * @param[in]	preview	-	�Ƿ���Ԥ������
 * @param[in]	ledctrl	-	�Ƿ���led���⿪��
 * @param[in]	sound	-	�Ƿ��ɨ����ʾ��
 * @return  �ο�ScanCodeRet����
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
 * @brief  �ر�ɨ��ģ�� 
 * @return  �ο�ScanCodeRet����
@else 
 * @brief  Close the scan module 
 * @return  Refer to ScanCodeRet for definitions
@endif 
 */
extern int app_scan_close(void);

/**
@if Chinese
 * @brief  ��ȡɨ������
 * @param[out]	pScanMsg	-	ɨ�����ݱ����ַ
 * @param[in]	uiMaxLen	-	ɨ��������󳤶�
 * @param[in]	uiWaitTime	-	�ȴ���ʱʱ��
 * @return  �ο�ScanCodeRet����
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
 * @brief  ���ñ���led��
 * @param[in]	onoff	-	��/��
@else 
 * @brief  Set backlit LED lights
 * @param[in]	onoff	-	on/off
@endif 
 */
extern void app_scan_set_led(appbool onoff);

/**
@if Chinese
 * @brief  ����Ԥ��
 * @param[in]	onoff	-	��/��
 * @return  �ο�ScanCodeRet����
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


