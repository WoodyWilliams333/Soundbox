/**
 @if Chinese
	* @brief       ��ģ���������� <strong>�ǽӵ�ģ��</strong> ��صĽӿ�
	* @par �ļ�    led.h
	* @author		Wenming
	* @date        2019/01/22
	* @version     1.0.1
	* @remarks        Change History:
	* ����          | ����            | ����
	* ------------- | --------------- | ----
	* 2019/01/22    | liluchang       | �����ļ�
	* 2022/04/21    | Wenming         | ����Ӣ��ע��
 @else
	* @brief       This module is used to describe <strong> Led</strong> interfaces module
	* @par file    led.h
	* @author		Wenming
	* @date        2019/01/22
	* @version     1.0.1
	* @remarks        Change History:
	* Date          | Author          | Desc
	* ------------- | --------------- | ----
	* 2019/01/22    | liluchang       | Create file
	* 2022/04/21    | Wenming         | Add English description
 @endif	
*/


/**
 @if Chinese
	* @defgroup LED �ǽӵ�
 @else
	* @defgroup LED Led
 @endif	
 * @{
*/


#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ��4��LED�� */
#define MIF_LED_1               0x01            /**<@if Chinese 1 : ��һ��LED�ƣ����� @else	1: First LED light, blue light	@endif*/
#define MIF_LED_2               0x02            /**<@if Chinese 2 : �ڶ���LED�ƣ��Ƶ� @else	2: Second LED light, yellow light	@endif*/
#define MIF_LED_3               0x04            /**<@if Chinese 4 : ������LED�ƣ��̵� @else	4: The third LED light, green light	@endif*/
#define MIF_LED_4               0x08            /**<@if Chinese 8 : ���ĸ�LED�ƣ���� @else	8: The fourth LED light, red light	@endif*/

/**
@if Chinese
	* @brief  LED����, �������ƣ��̣�������
@else
	* @brief  LED name, blue��yellow��green��red
@endif
 */
enum {
    LED_BLUE         = (1 << 0),                /**<@if Chinese 1 : ����   @else	1: blue light	@endif*/
    LED_YELLOW       = (1 << 1),                /**<@if Chinese 2 : �Ƶ�   @else	2: yellow light	@endif*/
    LED_GREEN        = (1 << 2),                /**<@if Chinese 4 : �̵�   @else	4: green light	@endif*/
    LED_RED          = (1 << 3),                /**<@if Chinese 8 : ���   @else	8: red light	@endif*/
};

#define MIF_LED_OFF             (0x00 << 28)    /**<@if Chinese �ر�LED��  @else	Close the LED lights	@endif*/
#define MIF_LED_ON              (0x01 << 28)    /**<@if Chinese ��LED��  @else	Open the LED lights	@endif*/
#define MIF_LED_FLASH           (0x02 << 28)    /**<@if Chinese LED����    @else	The LED flash	@endif*/



typedef enum{
    SYS_LED_RED  =    0,     /**<@if Chinese 8 : ���   @else	8: red light	@endif*/
    SYS_LED_GREEN,           /**<@if Chinese 4 : �̵�   @else	4: green light	@endif*/
    SYS_LED_BLUE,			 /**<@if Chinese 1 : ����   @else	1: blue light	@endif*/	
    SYS_LED_CHARGE,          /**<@if Chinese 1 : ��Դָʾ��   @else	1: power light	@endif*/
}LED_ENUM_T;

#define SYS_LED_ON  1    /**<@if Chinese ��LED��  @else	Open the LED lights	@endif*/ 
#define SYS_LED_OFF 0    /**<@if Chinese �ر�LED��  @else	Close the LED lights	@endif*/
/**
@if Chinese
	* @brief ϵͳLED�ƿ��ƽӿڣ��ɷǽ�оƬ����.
	* @param[in]	lednum	-	LED���ƺ�
	* @param[in]	mode	-	��4λ�������ģʽ����򿪣��رգ����ƣ���28λ��������ģʽ�µļ��ʱ�䣬��λΪ1ms
	* @return
	*   <em> 0 </em>    ----�ɹ�    <br>
	*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
 @else	
	* @brief System LED lamp control interface, driven by contactless chip.
	* @param[in]	lednum	-	The LED name
	* @param[in]	mode	-	High 4 represents the control mode, such as open, off, sparking;The lower 28 bits represent the interval in flashing mode, in the unit of 1ms
	* @return
	*   <em> 0 </em>    ----success    <br>
	*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
 @endif	 
*/
int nfc_led_control(int lednum, int mode);


/**
@if Chinese
	* @brief ��Դָʾ�ƺ���ɫָʾ�ƿ���
	* @param[in]	idx	-	LED����
	* @param[in]	enable	-	SYS_LED_ON���򿪣�SYS_LED_OFF���ر�
	*   <em> 0 </em>    ----�ɹ�    <br>
	*   <em> -1 </em>   ----ʧ��.
 @else	
	* @brief Power indicator and three-color indicator control
	* @param[in]	lednum	-	The LED index
	* @param[in]	mode	-	SYS_LED_ON��turn on��SYS_LED_OFF��turn off
	* @return
	*   <em> 0 </em>    ----success    <br>
	*   <em> -1 </em>   ----failed.
 @endif	 
*/
int sys_led_control(LED_ENUM_T idx, uint8_t enable);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for __LED_H__ */

/** @} */

