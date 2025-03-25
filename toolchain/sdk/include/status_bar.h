/**
 @if Chinese
	 * @brief       此模块用于描述 <strong>状态栏操作</strong> 相关接口
	 * @par 文件    status_bar.h
	 * @author		Wenming
	 * @date        2020/09/21
	 * @version     1.0.1
	 * @remarks     Change History:
	 * 日期          | 作者          | 描述
	 * ------------- | --------------- | ----
	 * 2020/09/21    | weifeng         | 创建文件
	 * 2022/04/20    | Wenming         | 增加英文注释
 @else	 
	 * @brief       This module is used to describe <strong>StatusBar</strong> interfaces module
	 * @par file    status_bar.h
	 * @author		Wenming
	 * @date        2020/09/21
	 * @version     1.0.1
	 * @remarks     Change History:
	 * Date          | Author          | Desc
	 * ------------- | --------------- | ----
	 * 2020/09/21    | weifeng         | Create file
	 * 2022/04/20    | Wenming         | Add English description
 @endif 
*/

#include "msg_queue.h"

/**
 @if Chinese
	* @defgroup status_bar 状态栏
 @else 
	* @defgroup status_bar StatusBar
 @endif 
 * @{
*/
struct icon_callbak{
    int (*set_up_icon)(int onoff); 	/**<@if Chinese 向下注册的上翻图标的回调函数 @else	Up icon callback function	@endif*/ 
    int (*set_down_icon)(int onoff);/**<@if Chinese 向下注册的下翻图标的回调函数 @else	Down icon callback function	@endif*/ 
};

/**
@if Chinese
	 *@brief 用于描述状态栏消息基本类型
@else 
	 *@brief Describes the basic type of status bar messages
@endif 
 */
typedef struct {
    int msg_type;	/**<@if Chinese 消息类型,应用主要用到该类型:STATUS_BAR_MSG @else	Message type:STATUS_BAR_MSG	@endif*/
} ipc_msg_t;

/**
@if Chinese
	 *@brief 用于描述状态栏消息
@else 	 
	 *@brief Used to describe status bar messages
 @endif 
 */
typedef struct {
    ipc_msg_t base;	/**<@if Chinese 消息类型,应用主要用到该类型:STATUS_BAR_MSG @else	Message type:STATUS_BAR_MSG	@endif*/
    int type;		/**<@if Chinese 状态栏事件类型  @else	Status type	@endif*/
    int event_id;	/**<@if Chinese 事件id,不同的消息事件id不同 @else	Event ID	@endif*/
} status_bar_msg_t;

/**
 @if Chinese
  * @brief  该枚举类型列出了消息类型.
@else  
  * @brief  This enumerated type lists the message types.
@endif
*/
typedef enum {
    STATUS_BAR_MSG,/**<@if Chinese 状态栏消息@else	Status bar message	@endif*/
} IPC_MSG_TYPE;

/**
 @if Chinese
  * @brief  该枚举类型列出了状态栏事件类型.
 @else  
  * @brief  This enumerated type lists the status bar event types.
@endif  
*/
enum {
	E_PHONE_SERVER_EVENT,		/**<@if Chinese 移动网络(4G/2G)事件 @else	Mobile network (4G/2G) events	@endif*/
	E_PED_EVENT,		 		/**<@if Chinese ped事件 			@else	Ped event						@endif*/
	E_TAMPER_ALARM_EVENT,		/**<@if Chinese ped攻击事件 		@else	Ped attacks event				@endif*/
	E_WIFI_EVENT,				/**<@if Chinese wifi事件 			@else	WIFI event						@endif*/
	E_BT_EVENT,				    /**<@if Chinese 蓝牙事件 			@else	bluetooth事件 event				@endif*/
	E_CHARGE_EVENT,				/**<@if Chinese 充电相关事件 		@else	Charging related event			@endif*/
	E_ICCARD_EVENT,				/**<@if Chinese ICCARD事件 			@else	ICCARD event					@endif*/
	E_UP_EVENT,					/**<@if Chinese 上翻图标			@else	UP ICONS						@endif*/
	E_DOWN_EVENT,				/**<@if Chinese 下翻图标显示事件	@else	DOWN ICONS						@endif*/
	E_LINK_EVENT,				/**<@if Chinese 连接图标显示事件	@else	LINK ICONS						@endif*/
	E_LED_1_EVENT,				/**<@if Chinese LED1事件 			@else	LED1 event						@endif*/
	E_LED_2_EVENT,				/**<@if Chinese LED2事件 			@else	LED2 event						@endif*/
	E_LED_3_EVENT,			    /**<@if Chinese LED3事件 			@else	LED3 event						@endif*/
	E_LED_4_EVENT,				/**<@if Chinese LED4事件 			@else	LED4 event						@endif*/
	E_PROMPT_EVENT,				/**<@if Chinese 状态栏提示事件 	    @else	status bar prompt event			@endif*/
	E_DATE_EVENT,				/**<@if Chinese 日期提示事件  	    @else	Date prompt event			    @endif*/
	E_POWER_LPREES_EVENT,		/**<@if Chinese 电源键长按事件 	    @else	Power button long press event	@endif*/
	E_END_EVENT,				/**<@if Chinese 枚举结束标志 		@else	Enum end flag					@endif*/
};

/** 
 @if Chinese
	 * @brief  设置为应用自定义状态栏 
	 * @retval  0   设置成功
	 * @retval  -1  调用失败
 @else	 
	 * @brief  Set to apply a custom status bar
	 * @retval  0   Success
	 * @retval  -1  Fail
  @endif
 */
int set_status_bar_customize(void);

/** 
 @if Chinese
	 * @brief  恢复成系统状态栏
	 * @retval  0   设置成功
	 * @retval  -1  调用失败
 @else	 
	 * @brief  restore to system stattus bar
	 * @retval  0   Success
	 * @retval  -1  Fail
  @endif
 */
int restore_status_bar_systemize(void);

/** 
 @if Chinese
	 * @brief  获取status_bar消息队列的handle
	 * @return 
		   - NULL    调用失败
		   - 非NULL  成功，返回status_bar消息队列的handle
 @else
	 * @brief  Gets the Handle of the status_bar message queue
	 * @return 
		   - NULL    Fail
		   - !NULL  Success，Returns the Handle of the status_bar message queue
 @endif 
 */
QueueHandle_t get_status_bas_msg_queue_handle(void);


/** 
 @if Chinese
	 * @brief  向下注册显示上下翻图标的回调函数
	 * @param[in] pfun	-	应用显示上下图标的回调函数 struct icon_callbak
	 * @return 
		   - -1    调用失败
		   - 1	   获取成功
 @else	 
	 * @brief  Register down the callback function that displays the scroll down icon
	 * @param[in] pfun	-	function struct icon_callbak
	 * @return 
		   - -1    Fail
		   - 1	   Success 
 @endif
 */
int regiter_up_down_icon_display_callback(struct icon_callbak *pfun);

/** @} */