
/**
@if Chinese
 * @brief       此模块用于描述 <strong>按键输入模块</strong> 相关的接口
 * @par 文件    key.h
 * @author
 * @date        2018/11/07
 * @version     1.0.1
 *
 * @remarks        Change History:
 * 日期          | 作者          | 描述
 * ------------- | --------------- | ----
 * 2018/11/07    | Milton Wu       | 创建文件
 * 2022/04/21    | Wenming         | 增加英文注释
@else 
 * @brief       This module is used to describe <strong>KeyBoard</strong> interfaces module
 * @par file    key.h
 * @author
 * @date        2018/11/07
 * @version     1.0.1
 *
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2018/11/07    | Milton Wu       | Create file
 * 2022/04/21    | Wenming         | Add English description
@endif 
*/


/**
@if Chinese
 * @defgroup KEY 按键
@else 
 * @defgroup KEY  KeyBoard
@endif 
 * @{
*/


#ifndef __KEY_H__
#define __KEY_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 定义各个按键值 */
/**
@if Chinese
 * @name 按键值
@else 
 * @name The key value
@endif 
 * @{
 */
#if 0
/**
 * @def KEY0
 * @brief        按键 '0'
 */
/**
 * @def KEY1
 * @brief        按键 '1'
 */
/**
 * @def KEY2
 * @brief        按键 '2'
 */
/**
 * @def KEY3
 * @brief        按键 '3'
 */
/**
 * @def KEY4
 * @brief        按键 '4'
 */
#endif
#define KEY0                    0x30            /**<@if Chinese 数字键 '0'     @else	Number keys	'0' @endif*/
#define KEY1                    0x31            /**<@if Chinese 数字键 '1'     @else	Number keys	'1' @endif*/
#define KEY2                    0x32            /**<@if Chinese 数字键 '2'     @else	Number keys	'2' @endif*/
#define KEY3                    0x33            /**<@if Chinese 数字键 '3'     @else	Number keys	'3' @endif*/
#define KEY4                    0x34            /**<@if Chinese 数字键 '4'     @else	Number keys	'4' @endif*/
#define KEY5                    0x35            /**<@if Chinese 数字键 '5'     @else	Number keys	'5' @endif*/
#define KEY6                    0x36            /**<@if Chinese 数字键 '6'     @else	Number keys	'6' @endif*/
#define KEY7                    0x37            /**<@if Chinese 数字键 '7'     @else	Number keys	'7' @endif*/
#define KEY8                    0x38            /**<@if Chinese 数字键 '8'     @else	Number keys	'8' @endif*/
#define KEY9                    0x39            /**<@if Chinese 数字键 '9'     @else	Number keys	'9' @endif*/
#define KEY_BACKSPACE           0x09            /**<@if Chinese 退格键         @else	Backspace key	@endif*/
#define KEY_CLEAR               0x2E            /**<@if Chinese 全部清除键     @else	Clear key		@endif*/
#define KEY_ALPHA               0x07            /**<@if Chinese 字母键         @else	The letters		@endif*/
#define KEY_UP                  0x04            /**<@if Chinese 上翻键         @else	Up key			@endif*/
#define KEY_DOWN                0x05            /**<@if Chinese 下翻键         @else	Down key		@endif*/
#define KEY_FN                  0x15            /**<@if Chinese 功能键         @else	The function keys	@endif*/
#define KEY_MENU                0x14            /**<@if Chinese 菜单键         @else	Menu key		@endif*/
#define KEY_ENTER               0x08            /**<@if Chinese 确认键         @else	Enter key		@endif*/
#define KEY_CANCEL              0x03            /**<@if Chinese 取消键         @else	Cancel key		@endif*/
#define KEY_PRNUP               0x19            /**<@if Chinese 打印向上走纸   @else	Print up the paper	@endif*/
#define KEY_POWER               0x02            /**<@if Chinese 电源键         @else	Power key		@endif*/
#define KEY_CAMERA              0x0E            /**<@if Chinese camera键       @else	Camera key		@endif*/
#define KEY_INVALID             0xFF            /**<@if Chinese 无效按键       @else	Invalid key		@endif*/
#define KEY_TIMEOUT             0x00            /**<@if Chinese 超时无按键     @else	Timeout no key	@endif*/
#define KEY_F1                  0xF1            /**<@if Chinese F1键           @else	F1 key			@endif*/
#define KEY_F2                  0xF2            /**<@if Chinese F2键           @else	F2 key			@endif*/
#define KEY_INC				    0x10            /**<@if Chinese + 键           @else	+ key       	@endif*/
#define KEY_VOLUME_INC          0x12            /**<@if Chinese 音量+键        @else	Volume up key       	@endif*/
#define KEY_VOLUME_DEC          0x13            /**<@if Chinese 音量-键        @else	Volume down key       	@endif*/

/** @} */

/**
@if Chinese
 * @brief 按键的状态枚举
@else 
 * @brief Enumeration of key states
@endif  
 */
typedef enum {
    KEY_STATUS_UP                   = 0x0,      /**<@if Chinese 按键弹起       @else	Button pop-up	@endif*/
    KEY_STATUS_DOWN                 = 0x1,      /**<@if Chinese 按键按下       @else	Button press	@endif*/
} key_status_t;

/**
@if Chinese
 * @brief 按键的详细信息结构体
@else  
 * @brief Key details structure
@endif  
 */
typedef struct {
    key_status_t    status;                     /**<@if Chinese 按键的状态, 参考 @ref key_status_t @else For key status, see @ref key_status_t 	@endif*/
    uint32_t        key;                        /**<@if Chinese 按键的键值                         @else Key value of a key 					@endif*/
    uint64_t        tick_time;                  /**<@if Chinese 按键获取时的tick时钟               @else Tick clock when a button is pressed 	@endif*/
} key_info_t;

/**
@if Chinese
 * @brief       键盘是否输入
 * @return      1   -	表示有输入<br>
                0   -	表示没有输入<br>
                < 0 -	表示输入设备异常
@else   
 * @brief       Check if any key be pressed
 * @return      1   -	There is input<br>
                0   -	No input<br>
                < 0 -	Indicates that the input device is abnormal
@endif  
*/
int kb_hit(void);

/**
@if Chinese
 * @brief      获取键值
 * @param[in]	timeout_ms	-	等待按键超时时间,单位:ms; 传入-1表示阻塞式等待
 * @param[out]	info			-	按键的详细信息，包含按键状态和按键上报时的tick时钟，参见 @ref key_info_t
 * @return     0	-	表示超时,没有获取到按键信息<br>
               >0	-	表示按键值
 * @note       如果没有按键,该函数会等待超时后再返回; 未获取键值时,该函数返回0; 如果不关心key_info，可传入NULL
@else   
 * @brief      get the key value
 * @param[in]	timeout_ms	-	Timeout time for waiting buttons, unit :ms;Passing -1 indicates a blocking wait
 * @param[out]	info		-	For details about buttons, including button status and tick clock when buttons are reported, see @ref key_info_t
 * @return     0  -	Timeout<br>
               >0 -	Key value
 * @note       If there is no key, the function waits for a timeout before returning;This function returns 0 if no key is retrieved;If you don't care about key_info, you can pass NULL
@endif   
*/
int kb_get_key_info(uint32_t timeout_ms, key_info_t *info);

/**
@if Chinese
 * @brief   清空按键缓存
 * @note    通过此函数将未处理按键信息全部清空
@else 
 * @brief   Cleanup keyboard input buffer
 * @note    clear all unprocessed key information
@endif  
*/
void kb_flush(void);

/**
@if Chinese
 * @brief  选择按键功能
 * @note   某些按键支持多个功能，通过此函数切换
 * @param[in]	kv		-	需要切换的按键的键值，第一或第二功能键值均可
 * @param[in]	fidx	-	0:第一功能 1:第二功能
 * @return 
			0	-	成功 <br>
			-1	-	不支持多功能
@else 
 * @brief  Select button function
 * @note   Some keys support multiple functions, which can be switched through this function
 * @param[in]	kv		-	The key value of the key to be switched can be the first or second function key value
 * @param[in]	fidx	-	0: first function 1: second function
 * @return 
			0	-	Success. <br>
			-1	-	Fail
 @endif 
 */
int kb_select_key_func(int kv, int fidx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __KEY_H__ */

/** @} */

