/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app key模块</strong> 相关的接口
	 * @par 文件    appkey.h
	 * @author		yangjing
	 * @date        2020-04-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-28    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-20    | 1.0.1        | liyanping     | 增加英文注释  
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
	@defgroup app_key	键盘
 @else
	@defgroup app_key	keyboard
 @endif
 * @{
*/

#ifndef _APP_KEY_H_
#define _APP_KEY_H_

#include "key.h"
// #include "logger.h"

//功能键方式定义
/**
 @if Chinese
	@brief  功能键方式定义.
 @else
	@brief  This enumerated type lists the Function key mode .
 @endif
*/
typedef enum{
	FIRST_FUNC = 0,		/**< @if Chinese 第一功能键  @else  First function key  @endif */ 
	SECOND_FUNC,		  /**< @if Chinese 第二功能键  @else  Second function key  @endif */
}E_FV_FIDX;

/**
 @if Chinese
	@brief  	检测是否有按键
	@return		0		-	无按键
	@return		其它	-	有按键
@else
	@brief  Check if any key be pressed
	@return		0		-	No key is pressed 
	@return		Other	- 	there is a key pressed
 @endif
 */
extern int app_kb_check_key(void);


 /**
 @if Chinese
	@brief  清空按键			
@else
	@brief  Cleanup keyboard input buffer
 @endif
 */
extern void app_kb_flush(void);

/**
 @if Chinese
	@brief  阻塞直到获取到按键
	@return 按键键值		
@else
	@brief  Block until the key value is obtained
	@return	the pressed key value
 @endif
 */
extern int app_kb_get_key(void);

 
 /**
 @if Chinese
	@brief  阻塞msec毫秒，直到获取到按键或超时
 	@param[in]	msec	-	超时时间(ms)
	@return 	按键键值	
@else
	@brief  Block msec  for milliseconds until the key value is obtained or a timeout occurs
	@param[in]	msec	-	timeout (ms)
	@return		the pressed key value
 @endif
 */
extern int app_kb_get_key_ms(int msec);


 /**
 @if Chinese
	@brief  设置功能键方式
 	@param[in]	kv		-	需设置的功能键键值(KEY_DOWN或KEY_UP)
  	@param[in]	fidx	-	功能键方式
	@return		0		-	成功
	@return		其它	-	失败
	@note		KEY_DOWN 和 KEY_UP 为第二功能键<br>
 				KEY_FN 和 KEY_ALPAH 为第一功能键<br>
 				系统默认使用第二功能键<br>
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


