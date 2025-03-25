
/**
@if Chinese
 * @brief       ��ģ���������� <strong>��������ģ��</strong> ��صĽӿ�
 * @par �ļ�    key.h
 * @author
 * @date        2018/11/07
 * @version     1.0.1
 *
 * @remarks        Change History:
 * ����          | ����          | ����
 * ------------- | --------------- | ----
 * 2018/11/07    | Milton Wu       | �����ļ�
 * 2022/04/21    | Wenming         | ����Ӣ��ע��
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
 * @defgroup KEY ����
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

/* �����������ֵ */
/**
@if Chinese
 * @name ����ֵ
@else 
 * @name The key value
@endif 
 * @{
 */
#if 0
/**
 * @def KEY0
 * @brief        ���� '0'
 */
/**
 * @def KEY1
 * @brief        ���� '1'
 */
/**
 * @def KEY2
 * @brief        ���� '2'
 */
/**
 * @def KEY3
 * @brief        ���� '3'
 */
/**
 * @def KEY4
 * @brief        ���� '4'
 */
#endif
#define KEY0                    0x30            /**<@if Chinese ���ּ� '0'     @else	Number keys	'0' @endif*/
#define KEY1                    0x31            /**<@if Chinese ���ּ� '1'     @else	Number keys	'1' @endif*/
#define KEY2                    0x32            /**<@if Chinese ���ּ� '2'     @else	Number keys	'2' @endif*/
#define KEY3                    0x33            /**<@if Chinese ���ּ� '3'     @else	Number keys	'3' @endif*/
#define KEY4                    0x34            /**<@if Chinese ���ּ� '4'     @else	Number keys	'4' @endif*/
#define KEY5                    0x35            /**<@if Chinese ���ּ� '5'     @else	Number keys	'5' @endif*/
#define KEY6                    0x36            /**<@if Chinese ���ּ� '6'     @else	Number keys	'6' @endif*/
#define KEY7                    0x37            /**<@if Chinese ���ּ� '7'     @else	Number keys	'7' @endif*/
#define KEY8                    0x38            /**<@if Chinese ���ּ� '8'     @else	Number keys	'8' @endif*/
#define KEY9                    0x39            /**<@if Chinese ���ּ� '9'     @else	Number keys	'9' @endif*/
#define KEY_BACKSPACE           0x09            /**<@if Chinese �˸��         @else	Backspace key	@endif*/
#define KEY_CLEAR               0x2E            /**<@if Chinese ȫ�������     @else	Clear key		@endif*/
#define KEY_ALPHA               0x07            /**<@if Chinese ��ĸ��         @else	The letters		@endif*/
#define KEY_UP                  0x04            /**<@if Chinese �Ϸ���         @else	Up key			@endif*/
#define KEY_DOWN                0x05            /**<@if Chinese �·���         @else	Down key		@endif*/
#define KEY_FN                  0x15            /**<@if Chinese ���ܼ�         @else	The function keys	@endif*/
#define KEY_MENU                0x14            /**<@if Chinese �˵���         @else	Menu key		@endif*/
#define KEY_ENTER               0x08            /**<@if Chinese ȷ�ϼ�         @else	Enter key		@endif*/
#define KEY_CANCEL              0x03            /**<@if Chinese ȡ����         @else	Cancel key		@endif*/
#define KEY_PRNUP               0x19            /**<@if Chinese ��ӡ������ֽ   @else	Print up the paper	@endif*/
#define KEY_POWER               0x02            /**<@if Chinese ��Դ��         @else	Power key		@endif*/
#define KEY_CAMERA              0x0E            /**<@if Chinese camera��       @else	Camera key		@endif*/
#define KEY_INVALID             0xFF            /**<@if Chinese ��Ч����       @else	Invalid key		@endif*/
#define KEY_TIMEOUT             0x00            /**<@if Chinese ��ʱ�ް���     @else	Timeout no key	@endif*/
#define KEY_F1                  0xF1            /**<@if Chinese F1��           @else	F1 key			@endif*/
#define KEY_F2                  0xF2            /**<@if Chinese F2��           @else	F2 key			@endif*/
#define KEY_INC				    0x10            /**<@if Chinese + ��           @else	+ key       	@endif*/
#define KEY_VOLUME_INC          0x12            /**<@if Chinese ����+��        @else	Volume up key       	@endif*/
#define KEY_VOLUME_DEC          0x13            /**<@if Chinese ����-��        @else	Volume down key       	@endif*/

/** @} */

/**
@if Chinese
 * @brief ������״̬ö��
@else 
 * @brief Enumeration of key states
@endif  
 */
typedef enum {
    KEY_STATUS_UP                   = 0x0,      /**<@if Chinese ��������       @else	Button pop-up	@endif*/
    KEY_STATUS_DOWN                 = 0x1,      /**<@if Chinese ��������       @else	Button press	@endif*/
} key_status_t;

/**
@if Chinese
 * @brief ��������ϸ��Ϣ�ṹ��
@else  
 * @brief Key details structure
@endif  
 */
typedef struct {
    key_status_t    status;                     /**<@if Chinese ������״̬, �ο� @ref key_status_t @else For key status, see @ref key_status_t 	@endif*/
    uint32_t        key;                        /**<@if Chinese �����ļ�ֵ                         @else Key value of a key 					@endif*/
    uint64_t        tick_time;                  /**<@if Chinese ������ȡʱ��tickʱ��               @else Tick clock when a button is pressed 	@endif*/
} key_info_t;

/**
@if Chinese
 * @brief       �����Ƿ�����
 * @return      1   -	��ʾ������<br>
                0   -	��ʾû������<br>
                < 0 -	��ʾ�����豸�쳣
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
 * @brief      ��ȡ��ֵ
 * @param[in]	timeout_ms	-	�ȴ�������ʱʱ��,��λ:ms; ����-1��ʾ����ʽ�ȴ�
 * @param[out]	info			-	��������ϸ��Ϣ����������״̬�Ͱ����ϱ�ʱ��tickʱ�ӣ��μ� @ref key_info_t
 * @return     0	-	��ʾ��ʱ,û�л�ȡ��������Ϣ<br>
               >0	-	��ʾ����ֵ
 * @note       ���û�а���,�ú�����ȴ���ʱ���ٷ���; δ��ȡ��ֵʱ,�ú�������0; ���������key_info���ɴ���NULL
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
 * @brief   ��հ�������
 * @note    ͨ���˺�����δ��������Ϣȫ�����
@else 
 * @brief   Cleanup keyboard input buffer
 * @note    clear all unprocessed key information
@endif  
*/
void kb_flush(void);

/**
@if Chinese
 * @brief  ѡ�񰴼�����
 * @note   ĳЩ����֧�ֶ�����ܣ�ͨ���˺����л�
 * @param[in]	kv		-	��Ҫ�л��İ����ļ�ֵ����һ��ڶ����ܼ�ֵ����
 * @param[in]	fidx	-	0:��һ���� 1:�ڶ�����
 * @return 
			0	-	�ɹ� <br>
			-1	-	��֧�ֶ๦��
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

