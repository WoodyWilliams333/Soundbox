/**
@if Chinese
 * @brief       此模块用于描述 <strong>事件上报模块</strong> 相关的接口
 * @par 文件    event_user.h
 * @author
 * @date        2023/12/16
 * @version     1.0.0
 *
 * @remarks        Change History:
 * 日期          | 作者          | 描述
 * ------------- | --------------- | ----
 * 2023/12/16    | WeiFeng         | 创建文件
@else 
 * @brief       This module is used to describe <strong>event</strong> interfaces module
 * @par file    event_user.h
 * @author
 * @date        2023/12/16
 * @version     1.0.0
 *
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2023/12/16    | WeiFeng         | 创建文件
@endif 
*/


/**
@if Chinese
 * @defgroup 事件
@else 
 * @defgroup EVENT
@endif 
 * @{
*/

#ifndef __EVENT_USER_H__
#define __EVENT_USER_H__

/**
@if Chinese
 * @brief 各事件的ID
@else 
 * @brief Enumeration of event ID
@endif  
 */
typedef enum {
	EVENT_ID_KEY	= 0x0,		                  /**< @if Chinese 按键事件                 @else key event     @endif */ 
    EVENT_ID_POWER_OFF,                           /**< @if Chinese 关机事件                 @else power off event     @endif */ 
    EVENT_ID_USB_PLUG_IN,                         /**< @if Chinese USB插入事件              @else usb plug in event     @endif */ 
    EVENT_ID_USB_PLUG_OUT,                        /**< @if Chinese USB拔出事件              @else usb plug out event     @endif */
    EVENT_ID_LOW_BATTERY,                         /**< @if Chinese 低电量事件                @else low battery event     @endif */
	EVENT_ID_CHARGE_FINISH,				  		  /**< @if Chinese 充电结束                 @else charge finish     @endif       */
	EVENT_ID_LOW_BATTERY_POWER_OFF,				  /**< @if Chinese 低电量关机                @else  The battery is low and will shut down      @endif       */
	EVENT_ID_FW_UPGRADE,                          /**< @if Chinese 有固件需要更新事件            @else firware update event     @endif */
    EVENT_ID_MAX_NUM,
} event_id_t;

#define IS_EVENT_SET(event, e_id)   (!!(event & (1<<e_id)))  /**< @if Chinese 判断有无事件ID对应的事件    @else is event seted     @endif */ 



#endif

