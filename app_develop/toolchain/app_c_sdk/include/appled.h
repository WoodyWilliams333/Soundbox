/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app led模块</strong> 相关的接口
	 * @par 文件    appled.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-19    | 1.0.1        | lydia         | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app led</strong>  module
	 * @par file    appled.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-19    | 1.0.1        | lydia         | Add English description
 @endif
*/

/*!
 @if Chinese
	@defgroup appled 非接灯
 @else
	@defgroup appled led
 @endif
 * @{
*/
#ifndef _APP_LED_H_
#define _APP_LED_H_

/**
 @if Chinese
	@brief  该枚举类型列出了非接灯状态.
 @else
	@brief  This enumerated type lists the led status.
 @endif
  */
typedef enum{
	LED_NOT_READY 			= 0x01,		/**< @if Chinese 非接灯未准备好 @else led no ready @endif */
	LED_IDLE				= 0x02,		/**< @if Chinese 非接灯空闲 @else led idle @endif */
	LED_ACTIV_CARD			= 0x04,		/**< @if Chinese 读卡提示中 @else Reading card @endif */
	LED_TRANS_HANDLING 		= 0x08,		/**< @if Chinese 交易处理中 @else transaction processing @endif */
	LED_REMOVE_CARD 		= 0x10,		/**< @if Chinese 等待移卡中 @else wait for moving card @endif */
	LED_ONLINE_HANDLING 	= 0x20,		/**< @if Chinese 联机处理中 @else online processing @endif */
	LED_TRANS_OK 			= 0x40,		/**< @if Chinese 交易成功提示 @else prompt of successful transaction @endif */
	LED_TRANS_FAIL			= 0x80		/**< @if Chinese 交易失败提示 @else prompt of fail transaction @endif */
}NFC_LED_STATUS;

/*!
 @if Chinese
	@brief		设置非接灯状态
	@param[in]	status		-	非接灯状态
 @else
	@brief		set led status
	@param[in]	status		-	led status
 @endif
*/ 
extern void app_nfc_led_set_status(NFC_LED_STATUS status);

#endif

