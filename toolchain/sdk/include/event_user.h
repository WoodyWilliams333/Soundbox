/**
@if Chinese
 * @brief       ��ģ���������� <strong>�¼��ϱ�ģ��</strong> ��صĽӿ�
 * @par �ļ�    event_user.h
 * @author
 * @date        2023/12/16
 * @version     1.0.0
 *
 * @remarks        Change History:
 * ����          | ����          | ����
 * ------------- | --------------- | ----
 * 2023/12/16    | WeiFeng         | �����ļ�
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
 * 2023/12/16    | WeiFeng         | �����ļ�
@endif 
*/


/**
@if Chinese
 * @defgroup �¼�
@else 
 * @defgroup EVENT
@endif 
 * @{
*/

#ifndef __EVENT_USER_H__
#define __EVENT_USER_H__

/**
@if Chinese
 * @brief ���¼���ID
@else 
 * @brief Enumeration of event ID
@endif  
 */
typedef enum {
	EVENT_ID_KEY	= 0x0,		                  /**< @if Chinese �����¼�                 @else key event     @endif */ 
    EVENT_ID_POWER_OFF,                           /**< @if Chinese �ػ��¼�                 @else power off event     @endif */ 
    EVENT_ID_USB_PLUG_IN,                         /**< @if Chinese USB�����¼�              @else usb plug in event     @endif */ 
    EVENT_ID_USB_PLUG_OUT,                        /**< @if Chinese USB�γ��¼�              @else usb plug out event     @endif */
    EVENT_ID_LOW_BATTERY,                         /**< @if Chinese �͵����¼�                @else low battery event     @endif */
	EVENT_ID_CHARGE_FINISH,				  		  /**< @if Chinese ������                 @else charge finish     @endif       */
	EVENT_ID_LOW_BATTERY_POWER_OFF,				  /**< @if Chinese �͵����ػ�                @else  The battery is low and will shut down      @endif       */
	EVENT_ID_FW_UPGRADE,                          /**< @if Chinese �й̼���Ҫ�����¼�            @else firware update event     @endif */
    EVENT_ID_MAX_NUM,
} event_id_t;

#define IS_EVENT_SET(event, e_id)   (!!(event & (1<<e_id)))  /**< @if Chinese �ж������¼�ID��Ӧ���¼�    @else is event seted     @endif */ 



#endif

