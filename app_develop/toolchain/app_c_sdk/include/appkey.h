/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app keyģ��</strong> ��صĽӿ�
	 * @par �ļ�    appkey.h
	 * @author		yangjing
	 * @date        2020-04-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-28    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-20    | 1.0.1        | liyanping     | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app key</strong>  module
	 * @par file    appkey.h
	 * @author		yangjing
	 * @date        2020-04-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-28    | 1.0.0        | yanjing       | create file
	 * 2022-04-20    | 1.0.1        | liyanping     | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup app_key	����
 @else
	@defgroup app_key	keyboard
 @endif
 * @{
*/

#ifndef _APP_KEY_H_
#define _APP_KEY_H_

#include "key.h"
// #include "logger.h"

//���ܼ���ʽ����
/**
 @if Chinese
	@brief  ���ܼ���ʽ����.
 @else
	@brief  This enumerated type lists the Function key mode .
 @endif
*/
typedef enum{
	FIRST_FUNC = 0,		/**< @if Chinese ��һ���ܼ�  @else  First function key  @endif */ 
	SECOND_FUNC,		  /**< @if Chinese �ڶ����ܼ�  @else  Second function key  @endif */
}E_FV_FIDX;

/**
 @if Chinese
	@brief  	����Ƿ��а���
	@return		0		-	�ް���
	@return		����	-	�а���
@else
	@brief  Check if any key be pressed
	@return		0		-	No key is pressed 
	@return		Other	- 	there is a key pressed
 @endif
 */
extern int app_kb_check_key(void);


 /**
 @if Chinese
	@brief  ��հ���			
@else
	@brief  Cleanup keyboard input buffer
 @endif
 */
extern void app_kb_flush(void);

/**
 @if Chinese
	@brief  ����ֱ����ȡ������
	@return ������ֵ		
@else
	@brief  Block until the key value is obtained
	@return	the pressed key value
 @endif
 */
extern int app_kb_get_key(void);

 
 /**
 @if Chinese
	@brief  ����msec���룬ֱ����ȡ��������ʱ
 	@param[in]	msec	-	��ʱʱ��(ms)
	@return 	������ֵ	
@else
	@brief  Block msec  for milliseconds until the key value is obtained or a timeout occurs
	@param[in]	msec	-	timeout (ms)
	@return		the pressed key value
 @endif
 */
extern int app_kb_get_key_ms(int msec);


 /**
 @if Chinese
	@brief  ���ù��ܼ���ʽ
 	@param[in]	kv		-	�����õĹ��ܼ���ֵ(KEY_DOWN��KEY_UP)
  	@param[in]	fidx	-	���ܼ���ʽ
	@return		0		-	�ɹ�
	@return		����	-	ʧ��
	@note		KEY_DOWN �� KEY_UP Ϊ�ڶ����ܼ�<br>
 				KEY_FN �� KEY_ALPAH Ϊ��һ���ܼ�<br>
 				ϵͳĬ��ʹ�õڶ����ܼ�<br>
@else
	@brief  Set function key mode
	@param[in]	kv		-	Function key value to be set(KEY_DOWN or KEY_UP)
	@param[in]	fidx	-	Function key mode
	@return  	0		-	success
	@return  	other	-	fail
	@note		KEY_DOWN and KEY_UP is the second function key<br>
				KEY_FN and KEY_ALPAH is the first function key<br>
				The system uses the second function key by default			
 @endif
 */
extern int app_kb_select_key(int kv, E_FV_FIDX fidx);

#endif


