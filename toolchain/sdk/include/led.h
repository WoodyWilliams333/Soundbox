/**
 @if Chinese
	* @brief       此模块用于描述 <strong>非接灯模块</strong> 相关的接口
	* @par 文件    led.h
	* @author		Wenming
	* @date        2019/01/22
	* @version     1.0.1
	* @remarks        Change History:
	* 日期          | 作者            | 描述
	* ------------- | --------------- | ----
	* 2019/01/22    | liluchang       | 创建文件
	* 2022/04/21    | Wenming         | 增加英文注释
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
	* @defgroup LED 非接灯
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

/* 有4个LED灯 */
#define MIF_LED_1               0x01            /**<@if Chinese 1 : 第一个LED灯，蓝灯 @else	1: First LED light, blue light	@endif*/
#define MIF_LED_2               0x02            /**<@if Chinese 2 : 第二个LED灯，黄灯 @else	2: Second LED light, yellow light	@endif*/
#define MIF_LED_3               0x04            /**<@if Chinese 4 : 第三个LED灯，绿灯 @else	4: The third LED light, green light	@endif*/
#define MIF_LED_4               0x08            /**<@if Chinese 8 : 第四个LED灯，红灯 @else	8: The fourth LED light, red light	@endif*/

/**
@if Chinese
	* @brief  LED名称, 有蓝，黄，绿，红四种
@else
	* @brief  LED name, blue，yellow，green，red
@endif
 */
enum {
    LED_BLUE         = (1 << 0),                /**<@if Chinese 1 : 蓝灯   @else	1: blue light	@endif*/
    LED_YELLOW       = (1 << 1),                /**<@if Chinese 2 : 黄灯   @else	2: yellow light	@endif*/
    LED_GREEN        = (1 << 2),                /**<@if Chinese 4 : 绿灯   @else	4: green light	@endif*/
    LED_RED          = (1 << 3),                /**<@if Chinese 8 : 红灯   @else	8: red light	@endif*/
};

#define MIF_LED_OFF             (0x00 << 28)    /**<@if Chinese 关闭LED灯  @else	Close the LED lights	@endif*/
#define MIF_LED_ON              (0x01 << 28)    /**<@if Chinese 打开LED灯  @else	Open the LED lights	@endif*/
#define MIF_LED_FLASH           (0x02 << 28)    /**<@if Chinese LED闪灯    @else	The LED flash	@endif*/



typedef enum{
    SYS_LED_RED  =    0,     /**<@if Chinese 8 : 红灯   @else	8: red light	@endif*/
    SYS_LED_GREEN,           /**<@if Chinese 4 : 绿灯   @else	4: green light	@endif*/
    SYS_LED_BLUE,			 /**<@if Chinese 1 : 蓝灯   @else	1: blue light	@endif*/	
    SYS_LED_CHARGE,          /**<@if Chinese 1 : 电源指示灯   @else	1: power light	@endif*/
}LED_ENUM_T;

#define SYS_LED_ON  1    /**<@if Chinese 打开LED灯  @else	Open the LED lights	@endif*/ 
#define SYS_LED_OFF 0    /**<@if Chinese 关闭LED灯  @else	Close the LED lights	@endif*/
/**
@if Chinese
	* @brief 系统LED灯控制接口，由非接芯片驱动.
	* @param[in]	lednum	-	LED名称号
	* @param[in]	mode	-	高4位代表控制模式，如打开，关闭，闪灯；低28位代表闪灯模式下的间隔时间，单位为1ms
	* @return
	*   <em> 0 </em>    ----成功    <br>
	*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
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
	* @brief 电源指示灯和三色指示灯控制
	* @param[in]	idx	-	LED索引
	* @param[in]	enable	-	SYS_LED_ON：打开，SYS_LED_OFF：关闭
	*   <em> 0 </em>    ----成功    <br>
	*   <em> -1 </em>   ----失败.
 @else	
	* @brief Power indicator and three-color indicator control
	* @param[in]	lednum	-	The LED index
	* @param[in]	mode	-	SYS_LED_ON：turn on，SYS_LED_OFF：turn off
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

