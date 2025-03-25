/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app system模块</strong> 相关的接口
	 * @par 文件    appsys.h
	 * @author		yangjing
	 * @date        2020-08-25
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-08-25    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-27    | 1.0.1        | wenming       | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app system </strong>  module
	 * @par file    appsys.h
	 * @author		yangjing
	 * @date        2020-08-25
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-08-25    | 1.0.0        | yanjing       | create file
	 * 2022-04-27    | 1.0.1        | wenming       | Add English description
 @endif 
*/
/*!
 @if Chinese
	* @addtogroup app_system 系统类
 @else 
	* @addtogroup app_system system
 @endif 
 * @{
*/

#ifndef _APP_SYS_H_
#define _APP_SYS_H_

#include <appdatatypedef.h>

#define BATTERY_ONLY_LOW_VOLTAGE 		3550 /**<@if Chinese 非充电低电压(刘显桂给出的数据) @else	Non-charging low voltage	@endif*/
#define BATTERY_CHARGING_LOW_VOLTAGE	3580 /**<@if Chinese 充电低电压(刘显桂给出的数据) 	@else	Charging low voltage	@endif*/
#define BATTERY_LOW_PERCENTAGE			10	 /**<@if Chinese 低电量 						@else	low battery	@endif*/

/*!
 @if Chinese
  * @brief  该枚举类型列出了电池状态.
@else  
  * @brief  This enumerated type lists the battery status.
@endif
*/
typedef enum{
	BATTERY_ONLY = 0,	/**<@if Chinese 仅电池供电 @else	Battery only	@endif*/
	BATTERY_CHARGEING,	/**<@if Chinese 电池充电中 @else	Battery charging	@endif*/
	BATTERY_FULL,		/**<@if Chinese 电量满 		@else	Battery Full	@endif*/	
	BATTERY_NONE,		/**<@if Chinese 无电池供电 @else	Battery free	@endif*/
}BatteryStatus;

/*!
@if Chinese
  * @brief  该枚举类型列出了机器型号.
@else  
  * @brief  This enumerated type lists the machine model.
@endif
*/
typedef enum{
	SERISE_NEW7X = '1',	/**<@if Chinese NEW7XXX系列 @else	NEW7XXX type	@endif*/
	SERISE_NEW6X = '2',	/**<@if Chinese NEW6XXX系列 @else	NEW6XXX type	@endif*/

	SERISE_UNKNOW = 0	/**<@if Chinese 待定/预留 	@else	To be determined/reserved	@endif*/
}E_PRODUCT_SERISE;

/*!
@if Chinese
  * @brief  该枚举类型列出了FLASH 类型.
@else  
  * @brief  This enumerated type lists the FLASH type.
@endif
*/
typedef enum{
	TERM_FLASH_4M,			/**< 4M FLASH*/
	TERM_FLASH_8M,			/**< 8M FLASH*/
}E_FLASH_TYPE;

/*!
@if Chinese
  * @brief  该枚举类型列出了屏幕类型.
@else  
  * @brief  This enumerated type lists the screen type.
@endif
*/
typedef enum{
	TERM_SCREEN_COLOR,		/**< COLOR SCREEN */
	TERM_SCREEN_COLOR_160,  /**< COLOR SCREEN */
	TERM_SCREEN_BW			/**< Black & White SCREEN */
}E_SCREEN_TYPE;

/*!
@if Chinese
	 *@brief 用于描述机器硬件支持功能的结构体
@else 	 
	 *@brief A structure used to describe the functionality supported by machine hardware
@endif 
*/
typedef struct{
	appbool bSupWifi;					/**<@if Chinese 设备是否支持wifi模块 	@else	Whether the device supports wifi module	@endif*/
	appbool bSupGprs;					/**<@if Chinese 设备是否支持gprs模块 	@else	Whether the device supports GPRS module	@endif*/
	appbool bSupTouchScreen;			/**<@if Chinese 设备是否支持触摸屏 		@else	Whether the device supports touch screen	@endif*/
	appbool bSupCamera;					/**<@if Chinese 设备是否支持摄像头(扫码) @else	Whether the device supports camera (scan code)	@endif*/
	appbool bSupPrinter;				/**<@if Chinese 设备是否支持打印 		@else	Whether the device supports printing	@endif*/
	appbool bSupAudio;					/**<@if Chinese 设备是否语音(喇叭) 		@else	Whether the device is audio (speaker)	@endif*/
	appbool bSupBT;						/**<@if Chinese 设备是否支持蓝牙 		@else	Whether the device supports Bluetooth	@endif*/
	E_PRODUCT_SERISE eProductSerise;	/**<@if Chinese 设备产品系列归属 		@else	Equipment product series ownership	@endif*/
	E_FLASH_TYPE eFlashType;			/**<@if Chinese 设备产品FLASH类型 		@else	Device supports	FLASH type@endif*/
	E_SCREEN_TYPE eScreenType;			/**<@if Chinese 设备产品屏幕类型 		@else	Device Screen type	@endif*/
}TERMINALCAP;

/*!
@if Chinese
	 *@brief 用于描述终端信息结构体
@else 	 
	 *@brief Describes a terminal information structure
@endif
*/
typedef struct
{
    char Terminal[20];					/**<@if Chinese 产品型号	@else	product model			@endif*/
	char Tusn[50]; 						/**<@if Chinese 设备tusn	@else	Device tusn				@endif*/
	TERMINALCAP stCap;					/**<@if Chinese 设备能力	@else	Capacity of equipment	@endif*/
} TERMINALINFO;

/*!
@if Chinese
	 *@brief 用于描述终端电池显示结构体
@else 	 
	 *@brief Term applied to a terminal battery display structure
@endif
*/
typedef struct
{
	uint32_t status;            /**<@if Chinese 详见BatteryStatus枚举  					@else	See BatteryStatus	@endif*/	
	uint32_t cur_values;        /**<@if Chinese 当前电压值                              @else	Current voltage	@endif*/	
	uint32_t max_values;        /**<@if Chinese 最高电压值                              @else	Maximum voltage	@endif*/	
	uint32_t min_values;        /**<@if Chinese 最低电压值                              @else	Minimum voltage	@endif*/	
	uint32_t percent;           /**<@if Chinese 当前电量百分比                          @else	Current electricity percentage	@endif*/
} BATTERYINFO;


/**
@if Chinese
 * @brief	系统功能初始化
 * @return		0			-	成功  
 * @return		其它		-	失败	
@else 
 * @brief	System functions are initialized
 * @return		0			-	Successful
 * @return		other		-	Fail
 @endif
 */
extern int app_sys_init(void);

/**
@if Chinese
 * @brief	蜂鸣器提示成功
@else  
 * @brief	The buzzer indicates success
 @endif 
 */
extern void app_beep_ok(void);

/**
@if Chinese
 * @brief	蜂鸣器提示失败
@else  
 * @brief	The buzzer failed
@endif
*/ 
extern void app_beep_err(void);

/**
@if Chinese
 * @brief	蜂鸣器提示
 * @param[in]	freq		-	蜂鸣频率	 
 * @param[in]	time		-	蜂鸣持续时间(ms)
@else 
 * @brief	Beeper On
 * @param[in]	freq		-	buzzer frequency meter 
 * @param[in]	time		-	Buzzer duration (MS)
@endif 
 */
extern void app_beep_info(int freq, int time);

/**
@if Chinese
 * @brief	使能/失能蜂鸣器
 * @param[in]	enable		-	使能/失能标识位，app_true为使能，反之失能
@else 
 * @brief	Enable/disable the buzzer
 * @param[in]	enable		-	Enable/disable flag bit. App_true indicates enable, and vice versa
@endif 
 */
extern void app_beep_enable(appbool enable);

/**
@if Chinese
 * @brief	使能/失能按键音
 * @param[in]	enable		-	使能/失能标识位，app_true为使能，反之失能
@else 
 * @brief	Enable/disable the key tone
 * @param[in]	enable		-	Enable/disable flag bit. App_true indicates enable, and vice versa
@endif 
 */
extern void app_key_voice_enable(appbool enable);

/**
@if Chinese
 * @brief	当前线程空闲等待若干时间
 * @param[in]	keepms		-	等待时间(ms)
@else  
 * @brief	The current thread is idle and waits a number of times
 * @param[in]	keepms		-	Waiting time (ms)
 @endif 
 */
extern void app_pos_msleep(unsigned int keepms);

/**
@if Chinese
 * @brief	设备重启
@else  
 * @brief	device reboot
@endif  
 */
extern void app_pos_reset(void);

/**
@if Chinese
 * @brief	获取系统开机后滴答时钟
 * @return	int 滴答时钟毫秒数
@else 
 * @brief	Gets the ticking clock after the system is turned on
 * @return	int Tick clock number of milliseconds
@endif 
 */
extern unsigned int app_get_tick_count(void);

/**
@if Chinese
 * @brief	定时进入节能模式(自动灭屏)开关
 * @param[in]	bsw			- 	on:允许节能模式;off:禁止进入节能模式
 * @return		设置前的模式
@else  
 * @brief	Switch to enter energy saving mode (automatic off)
 * @param[in]	bsw			- 	On: allows energy saving mode. Off: Disables the power saving mode
 * @return		the mode before setting
@endif 
 */
extern appbool app_set_auto_powersave_mode(appbool bsw);

/**
@if Chinese
 * @brief	获取系统时间
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	需要缓存的buf
 * @param[out]	pTimeYYYYMMDDHHMMSS		-	系统时间字符串，格式"YYYYMMDDHHMMSS"
 * @return		0						-	成功  
 * @return		其它					-	失败	
@else  
 * @brief	Get system times
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	Buf that needs to be cached
 * @param[out]	pTimeYYYYMMDDHHMMSS		-	System time string，format "YYYYMMDDHHMMSS"
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
*/
extern int app_get_time(char *pTimeYYYYMMDDHHMMSS);

/**
@if Chinese
 * @brief	设置系统时间
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	系统时间字符串，格式"YYYYMMDDHHMMSS"
 * @return		0		-	成功  
 * @return		其它	-	失败
@else 
 * @brief	Set system time
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	System time string，format "YYYYMMDDHHMMSS"
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
 */
extern int app_set_time(char *pTimeYYYYMMDDHHMMSS);

/**
@if Chinese
 * @brief	读取设备tusn(sn)
 * @param[out]	psn		-	tusn(sn)保存地址
 * @param[in]	size	-	tusn(sn)的最大长度
 * @return		0		-	成功  
 * @return		其它	-	失败
@else 
 * @brief	Get device tusn(sn)
 * @param[out]	psn	-tusn(sn)save address
 * @param[in]	size	-	maximum length of tusn(sn) 
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
 */
extern int app_read_sn(char *psn, int size);

/**
@if Chinese
 * @brief	获取设备信息
 * @param[out]	terminal				-	设备信息结构
 * @return		TERMINALINFO 			-	设备信息结构指针
@else 
 * @brief	Obtaining Device Information
 * @param[out]	terminal				-	Device information structure
 * @return		TERMINALINFO 			-	Device information structure pointer
@endif 
 */
extern TERMINALINFO* app_get_terminal_info(TERMINALINFO *terminal);

/**
@if Chinese
 * @brief	获取电池电量信息
 * @param[out]	batteryinfo				-	电池电量信息结构
 * @return		0						-	成功  
 * @return		其它					-	失败	
@else 
 * @brief	Obtain battery information
 * @param[out]	batteryinfo				-	Battery capacity information structure
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
 */
extern int app_get_battery_info(BATTERYINFO *batteryinfo);


/**
@if Chinese
 * @brief	是否禁止系统休眠(可息屏，但系统不休眠)
 * @param[in]	mode	-	app_true:禁止休眠；app_false:允许休眠

@else 
 * @brief	Whether to disable system sleep (screen-off, but system does not sleep)
 * @param[in]	mode	-	app_true:sleep not allowed；app_false:Allowed to sleep

@endif 
 */
extern void app_sys_enable_standby(appbool mode);

/**
@if Chinese
 * @brief	获取flash剩余存储空间
 * @return		剩余存储空间的大小(Kb)
@else 
 * @brief	Obtain the remaining flash storage space
 * @return		Remaining storage space (Kb)
@endif 
 */
extern unsigned int app_get_free_space(void);

/**
@if Chinese
* @brief 使用一个版本与当前固件版本比较
* @param[in] 	comparever 				-	需要比较的版本 
						格式为 x.x.x，例如"1.3.7"
* @return 		1 						-	当前固件版本 > 比较版本<br>
* @return 		0 						-	当前固件版本 = 比较版本<br>
* @return 		-1 						-	当前固件版本 < 比较版本
@else 			
* @brief Use a version to compare to the current firmware version
* @param[in] 	comparever				-	The version you want to compare<br>
						The format is X.X.X, for example, "1.3.7"
* @return 		1 						-	Current firmware version > Comparison version<br>
* @return 		0 						-	Current firmware version = Comparison version<br>
* @return 		-1 						-	Current firmware version < comparison version
@endif 		
*/
extern int app_compare_fwversion(char *comparever);

/**
@if Chinese
 * @brief	设备关机
@else  
 * @brief	Devices are turned off
@endif 
 */
extern void app_power_off(void);

/**
@if Chinese
* @brief 获取VSIM 的APN
* @param[out]	vsimapn  				-	获取到的VSIM APN
* @return 		0 						-	获取成功<br>
* @return 		-1						-	获取失败
@else 			
* @brief Get VSIM's APN
* @param[out]	vsimapn 				-	Obtained VSIM APN
* @return 		0 						-	Successful<br>
* @return 		-1 						-	Fail
@endif 			
*/
extern int app_get_vsim_apn(char *vsimapn);

/**
@if Chinese
 * @brief	内存信息调试打印，非精确，只有内存变化超过4k时数据才会变化
@else  
 * @brief	Memory information debugging printing, inexact, only when the memory change exceeds 4K data will change
@endif  
 */
#define app_get_mem_info() \
{\
    uint32_t total_heap_mem;\
    uint32_t available_heap_mem;\
    uint32_t max_available_heap_mem_blk;\
\
    syscall_get_free_mem(&total_heap_mem, &available_heap_mem, &max_available_heap_mem_blk);\
    logger_debug("total=%d available=%d  max_available=%d\r\n", total_heap_mem, available_heap_mem, max_available_heap_mem_blk);\
}

#endif

