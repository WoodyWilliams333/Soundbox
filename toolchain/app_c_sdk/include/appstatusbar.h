/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app status bar模块</strong> 相关的接口
	 * @par 文件    appstatusbar.h
	 * @author		yangjing
	 * @date        2020-11-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-11-05    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-26    | 1.0.1        | wenming       | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app status bar</strong>  module
	 * @par file    appstatusbar.h
	 * @author		yangjing
	 * @date        2020-11-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-11-05    | 1.0.0        | yanjing       | create file
	 * 2022-04-26    | 1.0.1        | wenming       | Add English description
 @endif
*/

/**
 @if Chinese
	* @addtogroup status_bar 状态栏
 @else 
	* @addtogroup status_bar status bar
 @endif 
 * @{
*/

#ifndef _APP_ICON_H_
#define _APP_ICON_H_

#include "applcd.h"
#include "appled.h"

/*!
 @if Chinese
  * @brief  该枚举类型列出了GPRS状态类型.
@else  
  * @brief  This enumerated type lists the GPRS status types.
@endif
*/
typedef enum {
    GRPS_NO_CARD = 0,
    GPRS_SINGAL1,
    GPRS_SINGAL2,
    GPRS_SINGAL3,
    GPRS_SINGAL4,
    GPRS_SINGAL5,

    GPRS_OFF = -1
}GPRS_ICON_STATUS; 

/*!
 @if Chinese
  * @brief  该枚举类型列出了WIFI状态类型.
@else  
  * @brief  This enumerated type lists the WIFI state types.
@endif
*/
typedef enum {
    WIFI_UNLINK = 0,
    WIFI_SINGAL1,
    WIFI_SINGAL2,
    WIFI_SINGAL3,
    WIFI_SINGAL4,

    WIFI_OFF = -1
}WIFI_ICON_STATUS;  

/*!
 @if Chinese
  * @brief  该枚举类型列出了电池状态类型.
@else  
  * @brief  This enumerated type lists the battery state types.
@endif
*/
typedef enum {
    BATTRY_POWER0 = 0,
    BATTRY_POWER1,
    BATTRY_POWER2,
    BATTRY_POWER3,
    BATTRY_POWER4,
    BATTRY_POWER5,
    BATTRY_POWER6,

    BATTRY_CHARGE = -1,
    BATTRY_ERROR  = -3    
}BATTRY_ICON_STATUS;   

/*!
 @if Chinese
  * @brief  该枚举类型列出了时间数字/符号状态类型.
@else  
  * @brief  This enumerated type lists the time number/symbol status types.
@endif
*/
typedef enum {
    TIME_COLON = 0,
    TIME_NUM_0,
    TIME_NUM_1,
    TIME_NUM_2,
    TIME_NUM_3,
    TIME_NUM_4,
    TIME_NUM_5,
    TIME_NUM_6,
    TIME_NUM_7,
    TIME_NUM_8,
    TIME_NUM_9,  
}BATTRY_ICON_TIME_NUM;  

/*!
 @if Chinese
  * @brief  该枚举类型列出了nfc led灯状态类型.
@else  
  * @brief  This enumerated type lists the NFC LED status types.
@endif
*/
typedef enum {
    LED_OFF = 0,    
    LED_ON = 1
}LED_ICON_STATUS; 


/*!
@if Chinese
	 *@brief 用于描述自定义图标结构
@else 	 
	 *@brief Describes a custom icon structure
 @endif 
 */
typedef struct{
    int iconid;                 /**<@if Chinese icon 图标ID,可参见lcd.h宏定义	@else	Icon ICON ID. For details, see LCD. H macro definition	@endif*/
    int status;                 /**<@if Chinese icon对应模块状态				@else	Icon Module status	@endif*/
    int xy;                     /**<@if Chinese icon显示x y周坐标，高16位为x， 低16位为y @else	Icon displays the coordinates of x and y. The high 16 bits are X and the low 16 bits are Y	@endif*/
    unsigned char *pImage;      /**<@if Chinese icon 图片文件数据				@else	Icon Image file data	@endif*/
    void *pnext;                /**<@if Chinese 链表下一元素指针				@else	Pointer to the next element in the list	@endif*/
}ST_ICON_IMAGE;

#define ICON_IMAGE_LENGTHGTH sizeof(ST_ICON_IMAGE)	/**<@if Chinese ICON图片的大小 @else	The size of icon image	@endif*/

#define NOT_CHANGE        0     /**<@if Chinese 模式不修改默认值 @else	Mode does not change the default value	@endif*/

/*!
 @if Chinese
  * @brief  该枚举类型列出了充电显示图标模式.
@else  
  * @brief  This enumerated type lists the charging display icon mode.
@endif
*/
typedef enum{
    CHARGE_SHOW_ICON = 1,       /**<@if Chinese 充电显示为静态图标模式		@else	Charging is displayed in static icon mode	@endif*/
    CHARGE_SHOW_CYCLE,          /**<@if Chinese 充电显示为动态循环电量模式	@else	Charging is displayed in dynamic cycle mode	@endif*/
}CHARGE_SHOW_MODE;

/*!
 @if Chinese
  * @brief  该枚举类型列出了充电动态循环显示参数结构体.
@else  
  * @brief  This enumerated type lists the charging dynamic cycle display parameter structure.
@endif
*/
typedef struct{
    CHARGE_SHOW_MODE mode;      /**<@if Chinese 充电模式				@else	charging mode	@endif*/
    // uint32_t peroid;         /**<@if Chinese 动态显示模式循环间隔 	@else	Dynamic display mode cycle interval	@endif*/        
}ST_SB_CHAGER_PARA;             

/*!
 @if Chinese
  * @brief  该枚举类型列出了状态栏参数结构体.
@else  
  * @brief  This enumerated type lists the Status Bar parameter structure.
@endif
*/
typedef struct{
    ST_SB_CHAGER_PARA chargepara;
}ST_STATUS_BAR_PARA;


#define ICON_APP_DEF    100					/**<@if Chinese 自定义图标ID(可优先考虑使用底层提供ID，若无，再添加自定义ID) @else	Custom icon ID(it is preferred to use the ID provided by the bottom layer; if no, add a custom ID)	@endif*/

#ifndef ICON_DEV_PROM
#define ICON_DEV_PROM   ICON_APP_DEF+1 		/**<@if Chinese 开发机提示图标ID	@else	The developer prompts the icon ID	@endif*/
#endif

#ifndef ICON_TIME
#define ICON_TIME   ICON_APP_DEF+2			/**<@if Chinese 时间图标ID			@else	Time icon ID	@endif*/
#endif

#ifndef ICON_LED_BLUE
#define ICON_LED_BLUE   ICON_APP_DEF+3		/**<@if Chinese 蓝灯				@else	Blue light	@endif*/
#endif

#ifndef ICON_LED_YELLOW
#define ICON_LED_YELLOW   ICON_APP_DEF+4	/**<@if Chinese 黄灯				@else	Yellow light	@endif*/
#endif


#ifndef ICON_LED_GREEN
#define ICON_LED_GREEN   ICON_APP_DEF+5		/**<@if Chinese 绿灯				@else	Green light	@endif*/
#endif


#ifndef ICON_LED_RED
#define ICON_LED_RED   ICON_APP_DEF+6		/**<@if Chinese 红灯				@else	Red light	@endif*/
#endif

/**
@if Chinese
 * @brief	设置状态栏图标
 * @param[in]	icon	-	图标类型
 * @param[in]	onoff	-	是否显示图标
 * @return		0		-	成功
 * @return		其它	-	失败
@else 
 * @brief	Set the status bar icon
 * @param[in]	icon	-	icon Type
 * @param[in]	onoff	-	Whether to display ICONS
 * @return		0		-	success
 * @return		other	-	fail
@endif 
 */
extern int app_statusbar_set_icon(int icon, appbool onoff);

/*!
@if Chinese
 * @brief	自定义状态栏初始化
@else 
 * @brief	Custom status bar initialization
 @endif
 */
extern void app_statusbar_init(void);

/*!
@if Chinese
 * @brief		启动应用自定义状态服务
 * @return		0		-	成功
 * @return		其它	-	失败
 * @note        未启动时，使用底层提供的默认状态；<br>
 *              启动后，应用开启自定义状态栏服务线程。默认使用一套与底层图标相同的状态栏；<br>
 *              通过app_statusbar_set_subject实现个性化设置状态栏             
  
@else 
 * @brief		Start the application custom status service 
 * @return		0		-	success
 * @return		other	-	fail
 * @note        When not started, use the default state provided at the bottom；<br>
 *              After startup, the application starts the custom status bar service thread. The default is to use the same set of status bars as the underlying icons；<br>
 *              Use the app_statusbar_set_subject achieve personalized setting status bar             
  
@endif 
 */
extern int app_statusbar_service_start(void);

/*!
@if Chinese
 * @brief	自定义个性化状态栏
 *               注意: "开发机禁止商用"图标不允许修改,该图标不能自定义设置
 * @param[in]	lpStIconImages	-	一组自定义图标集，用于更新/添加服务内原图标集<br>
 *                       当iconid与status与原图标集中匹配有相同时，更新原图标集<br>
 *                       当iconid与status与原图标集中未有匹配时，添加到原图标集<br>
 *                       注意 pImage 图片数据不能为空，否则图标无法正常显示或清除<br>
 * @param[in]    num			-	自定义图标集元素个数
 * @param[in]    lpPara			-	自定义状态栏设置参数
 * @return		0		-	成功
 * @return		其它	-	失败
 * @note	服务默认图标集数据如下：<br>
 *    {ICON_SIGNAL, GRPS_NO_CARD, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL1, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL2, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL3, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL4, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL5, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 * 
 *    {ICON_LINK,     0,      (LINK_ICON_X<<16)+LINK_ICON_Y,          ...},<br>
 *    {ICON_ICCARD,   0,      (IC_CARD_ICON_X<<16)+IC_CARD_ICON_Y,    ...},<br>
 *    {ICON_LOCK,     0,      (LOCK_ICON_X<<16)+LOCK_ICON_Y,          ...},<br>
 *    {ICON_UP,       0,      (UP_ICON_X<<16)+UP_ICON_Y,              ...},<br>
 *    {ICON_DOWN,     0,      (DOWN_ICON_X<<16)+DOWN_ICON_Y,          ...},<br>
 *   
 *    {ICON_WIFI, WIFI_UNLINK,    (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL1,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL2,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL3,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL4,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 * 
 *    {ICON_BATTERY, BATTRY_POWER0, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER1, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER2, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER3, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER4, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER5, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER6, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_CHARGE, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_ERROR,  (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>

 *    {ICON_TIME, TIME_COLON, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_0, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_1, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_2, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_3, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_4, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_5, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_6, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_7, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_8, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_9, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...}
 
@else 
 * @brief	Customize the personalized status bar
 *          Notice: The "Developer do not use" icon cannot be modified and cannot be customized
 * @param[in]	lpStIconImages	-	A set of custom icon sets that can be used to update/add the original icon set within a service<br>
 *                       When the iconID and status match the original icon set, the original icon set is updated<br>
 *                       If the iconID and status do not match the original icon set, they are added to the original icon set<br>
 *                       Note pImage data cannot be empty; otherwise, ICONS cannot be displayed or cleared<br>
 * @param[in]    num			-	Number of elements in a custom icon set
 * @param[in]    lpPara			-	Customize status bar Settings parameters
 * @return		0		-	success
 * @return		other	-	fail
 * @note	The default icon set data for the service is as follows:<br>
 *    {ICON_SIGNAL, GRPS_NO_CARD, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL1, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL2, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL3, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL4, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 *    {ICON_SIGNAL, GPRS_SINGAL5, (GPRS_ICON_X<<16)+GPRS_ICON_Y, ...},<br>
 * 
 *    {ICON_LINK,     0,      (LINK_ICON_X<<16)+LINK_ICON_Y,          ...},<br>
 *    {ICON_ICCARD,   0,      (IC_CARD_ICON_X<<16)+IC_CARD_ICON_Y,    ...},<br>
 *    {ICON_LOCK,     0,      (LOCK_ICON_X<<16)+LOCK_ICON_Y,          ...},<br>
 *    {ICON_UP,       0,      (UP_ICON_X<<16)+UP_ICON_Y,              ...},<br>
 *    {ICON_DOWN,     0,      (DOWN_ICON_X<<16)+DOWN_ICON_Y,          ...},<br>
 *   
 *    {ICON_WIFI, WIFI_UNLINK,    (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL1,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL2,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL3,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 *    {ICON_WIFI, WIFI_SINGAL4,   (WIFI_ICON_X<<16)+WIFI_ICON_Y,  ...},<br>
 * 
 *    {ICON_BATTERY, BATTRY_POWER0, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER1, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER2, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER3, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER4, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER5, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_POWER6, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_CHARGE, (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>
 *    {ICON_BATTERY, BATTRY_ERROR,  (BATTERY_ICON_X<<16)+BATTERY_ICON_Y, ...},<br>

 *    {ICON_TIME, TIME_COLON, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_0, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_1, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_2, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_3, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_4, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_5, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_6, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_7, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_8, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...},<br>
 *    {ICON_TIME, TIME_NUM_9, (TIME_ICON_HOUR_H_X<<16)+TIME_ICON_Y, ...}
 @endif
 */
extern int app_statusbar_set_subject(ST_ICON_IMAGE *lpStIconImages, int num, ST_STATUS_BAR_PARA* lpPara);

#endif
