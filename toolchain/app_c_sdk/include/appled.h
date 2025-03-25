/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app ledģ��</strong> ��صĽӿ�
	 * @par �ļ�    appled.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-19    | 1.0.1        | lydia         | ����Ӣ��ע��  
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
	@defgroup appled �ǽӵ�
 @else
	@defgroup appled led
 @endif
 * @{
*/
#ifndef _APP_LED_H_
#define _APP_LED_H_

/**
 @if Chinese
	@brief  ��ö�������г��˷ǽӵ�״̬.
 @else
	@brief  This enumerated type lists the led status.
 @endif
  */
typedef enum{
	LED_NOT_READY 			= 0x01,		/**< @if Chinese �ǽӵ�δ׼���� @else led no ready @endif */
	LED_IDLE				= 0x02,		/**< @if Chinese �ǽӵƿ��� @else led idle @endif */
	LED_ACTIV_CARD			= 0x04,		/**< @if Chinese ������ʾ�� @else Reading card @endif */
	LED_TRANS_HANDLING 		= 0x08,		/**< @if Chinese ���״����� @else transaction processing @endif */
	LED_REMOVE_CARD 		= 0x10,		/**< @if Chinese �ȴ��ƿ��� @else wait for moving card @endif */
	LED_ONLINE_HANDLING 	= 0x20,		/**< @if Chinese ���������� @else online processing @endif */
	LED_TRANS_OK 			= 0x40,		/**< @if Chinese ���׳ɹ���ʾ @else prompt of successful transaction @endif */
	LED_TRANS_FAIL			= 0x80		/**< @if Chinese ����ʧ����ʾ @else prompt of fail transaction @endif */
}NFC_LED_STATUS;

/*!
 @if Chinese
	@brief		���÷ǽӵ�״̬
	@param[in]	status		-	�ǽӵ�״̬
 @else
	@brief		set led status
	@param[in]	status		-	led status
 @endif
*/ 
extern void app_nfc_led_set_status(NFC_LED_STATUS status);

#endif

