/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app systemģ��</strong> ��صĽӿ�
	 * @par �ļ�    appsys.h
	 * @author		yangjing
	 * @date        2020-08-25
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-08-25    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-27    | 1.0.1        | wenming       | ����Ӣ��ע�� 
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
	* @addtogroup app_system ϵͳ��
 @else 
	* @addtogroup app_system system
 @endif 
 * @{
*/

#ifndef _APP_SYS_H_
#define _APP_SYS_H_

#include <appdatatypedef.h>

#define BATTERY_ONLY_LOW_VOLTAGE 		3550 /**<@if Chinese �ǳ��͵�ѹ(���Թ����������) @else	Non-charging low voltage	@endif*/
#define BATTERY_CHARGING_LOW_VOLTAGE	3580 /**<@if Chinese ���͵�ѹ(���Թ����������) 	@else	Charging low voltage	@endif*/
#define BATTERY_LOW_PERCENTAGE			10	 /**<@if Chinese �͵��� 						@else	low battery	@endif*/

/*!
 @if Chinese
  * @brief  ��ö�������г��˵��״̬.
@else  
  * @brief  This enumerated type lists the battery status.
@endif
*/
typedef enum{
	BATTERY_ONLY = 0,	/**<@if Chinese ����ع��� @else	Battery only	@endif*/
	BATTERY_CHARGEING,	/**<@if Chinese ��س���� @else	Battery charging	@endif*/
	BATTERY_FULL,		/**<@if Chinese ������ 		@else	Battery Full	@endif*/	
	BATTERY_NONE,		/**<@if Chinese �޵�ع��� @else	Battery free	@endif*/
}BatteryStatus;

/*!
@if Chinese
  * @brief  ��ö�������г��˻����ͺ�.
@else  
  * @brief  This enumerated type lists the machine model.
@endif
*/
typedef enum{
	SERISE_NEW7X = '1',	/**<@if Chinese NEW7XXXϵ�� @else	NEW7XXX type	@endif*/
	SERISE_NEW6X = '2',	/**<@if Chinese NEW6XXXϵ�� @else	NEW6XXX type	@endif*/

	SERISE_UNKNOW = 0	/**<@if Chinese ����/Ԥ�� 	@else	To be determined/reserved	@endif*/
}E_PRODUCT_SERISE;

/*!
@if Chinese
  * @brief  ��ö�������г���FLASH ����.
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
  * @brief  ��ö�������г�����Ļ����.
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
	 *@brief ������������Ӳ��֧�ֹ��ܵĽṹ��
@else 	 
	 *@brief A structure used to describe the functionality supported by machine hardware
@endif 
*/
typedef struct{
	appbool bSupWifi;					/**<@if Chinese �豸�Ƿ�֧��wifiģ�� 	@else	Whether the device supports wifi module	@endif*/
	appbool bSupGprs;					/**<@if Chinese �豸�Ƿ�֧��gprsģ�� 	@else	Whether the device supports GPRS module	@endif*/
	appbool bSupTouchScreen;			/**<@if Chinese �豸�Ƿ�֧�ִ����� 		@else	Whether the device supports touch screen	@endif*/
	appbool bSupCamera;					/**<@if Chinese �豸�Ƿ�֧������ͷ(ɨ��) @else	Whether the device supports camera (scan code)	@endif*/
	appbool bSupPrinter;				/**<@if Chinese �豸�Ƿ�֧�ִ�ӡ 		@else	Whether the device supports printing	@endif*/
	appbool bSupAudio;					/**<@if Chinese �豸�Ƿ�����(����) 		@else	Whether the device is audio (speaker)	@endif*/
	appbool bSupBT;						/**<@if Chinese �豸�Ƿ�֧������ 		@else	Whether the device supports Bluetooth	@endif*/
	E_PRODUCT_SERISE eProductSerise;	/**<@if Chinese �豸��Ʒϵ�й��� 		@else	Equipment product series ownership	@endif*/
	E_FLASH_TYPE eFlashType;			/**<@if Chinese �豸��ƷFLASH���� 		@else	Device supports	FLASH type@endif*/
	E_SCREEN_TYPE eScreenType;			/**<@if Chinese �豸��Ʒ��Ļ���� 		@else	Device Screen type	@endif*/
}TERMINALCAP;

/*!
@if Chinese
	 *@brief ���������ն���Ϣ�ṹ��
@else 	 
	 *@brief Describes a terminal information structure
@endif
*/
typedef struct
{
    char Terminal[20];					/**<@if Chinese ��Ʒ�ͺ�	@else	product model			@endif*/
	char Tusn[50]; 						/**<@if Chinese �豸tusn	@else	Device tusn				@endif*/
	TERMINALCAP stCap;					/**<@if Chinese �豸����	@else	Capacity of equipment	@endif*/
} TERMINALINFO;

/*!
@if Chinese
	 *@brief ���������ն˵����ʾ�ṹ��
@else 	 
	 *@brief Term applied to a terminal battery display structure
@endif
*/
typedef struct
{
	uint32_t status;            /**<@if Chinese ���BatteryStatusö��  					@else	See BatteryStatus	@endif*/	
	uint32_t cur_values;        /**<@if Chinese ��ǰ��ѹֵ                              @else	Current voltage	@endif*/	
	uint32_t max_values;        /**<@if Chinese ��ߵ�ѹֵ                              @else	Maximum voltage	@endif*/	
	uint32_t min_values;        /**<@if Chinese ��͵�ѹֵ                              @else	Minimum voltage	@endif*/	
	uint32_t percent;           /**<@if Chinese ��ǰ�����ٷֱ�                          @else	Current electricity percentage	@endif*/
} BATTERYINFO;


/**
@if Chinese
 * @brief	ϵͳ���ܳ�ʼ��
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��	
@else 
 * @brief	System functions are initialized
 * @return		0			-	Successful
 * @return		other		-	Fail
 @endif
 */
extern int app_sys_init(void);

/**
@if Chinese
 * @brief	��������ʾ�ɹ�
@else  
 * @brief	The buzzer indicates success
 @endif 
 */
extern void app_beep_ok(void);

/**
@if Chinese
 * @brief	��������ʾʧ��
@else  
 * @brief	The buzzer failed
@endif
*/ 
extern void app_beep_err(void);

/**
@if Chinese
 * @brief	��������ʾ
 * @param[in]	freq		-	����Ƶ��	 
 * @param[in]	time		-	��������ʱ��(ms)
@else 
 * @brief	Beeper On
 * @param[in]	freq		-	buzzer frequency meter 
 * @param[in]	time		-	Buzzer duration (MS)
@endif 
 */
extern void app_beep_info(int freq, int time);

/**
@if Chinese
 * @brief	ʹ��/ʧ�ܷ�����
 * @param[in]	enable		-	ʹ��/ʧ�ܱ�ʶλ��app_trueΪʹ�ܣ���֮ʧ��
@else 
 * @brief	Enable/disable the buzzer
 * @param[in]	enable		-	Enable/disable flag bit. App_true indicates enable, and vice versa
@endif 
 */
extern void app_beep_enable(appbool enable);

/**
@if Chinese
 * @brief	ʹ��/ʧ�ܰ�����
 * @param[in]	enable		-	ʹ��/ʧ�ܱ�ʶλ��app_trueΪʹ�ܣ���֮ʧ��
@else 
 * @brief	Enable/disable the key tone
 * @param[in]	enable		-	Enable/disable flag bit. App_true indicates enable, and vice versa
@endif 
 */
extern void app_key_voice_enable(appbool enable);

/**
@if Chinese
 * @brief	��ǰ�߳̿��еȴ�����ʱ��
 * @param[in]	keepms		-	�ȴ�ʱ��(ms)
@else  
 * @brief	The current thread is idle and waits a number of times
 * @param[in]	keepms		-	Waiting time (ms)
 @endif 
 */
extern void app_pos_msleep(unsigned int keepms);

/**
@if Chinese
 * @brief	�豸����
@else  
 * @brief	device reboot
@endif  
 */
extern void app_pos_reset(void);

/**
@if Chinese
 * @brief	��ȡϵͳ������δ�ʱ��
 * @return	int �δ�ʱ�Ӻ�����
@else 
 * @brief	Gets the ticking clock after the system is turned on
 * @return	int Tick clock number of milliseconds
@endif 
 */
extern unsigned int app_get_tick_count(void);

/**
@if Chinese
 * @brief	��ʱ�������ģʽ(�Զ�����)����
 * @param[in]	bsw			- 	on:�������ģʽ;off:��ֹ�������ģʽ
 * @return		����ǰ��ģʽ
@else  
 * @brief	Switch to enter energy saving mode (automatic off)
 * @param[in]	bsw			- 	On: allows energy saving mode. Off: Disables the power saving mode
 * @return		the mode before setting
@endif 
 */
extern appbool app_set_auto_powersave_mode(appbool bsw);

/**
@if Chinese
 * @brief	��ȡϵͳʱ��
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	��Ҫ�����buf
 * @param[out]	pTimeYYYYMMDDHHMMSS		-	ϵͳʱ���ַ�������ʽ"YYYYMMDDHHMMSS"
 * @return		0						-	�ɹ�  
 * @return		����					-	ʧ��	
@else  
 * @brief	Get system times
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	Buf that needs to be cached
 * @param[out]	pTimeYYYYMMDDHHMMSS		-	System time string��format "YYYYMMDDHHMMSS"
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
*/
extern int app_get_time(char *pTimeYYYYMMDDHHMMSS);

/**
@if Chinese
 * @brief	����ϵͳʱ��
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	ϵͳʱ���ַ�������ʽ"YYYYMMDDHHMMSS"
 * @return		0		-	�ɹ�  
 * @return		����	-	ʧ��
@else 
 * @brief	Set system time
 * @param[in]	pTimeYYYYMMDDHHMMSS		-	System time string��format "YYYYMMDDHHMMSS"
 * @return		0						-	Successful
 * @return		other					-	Fail
@endif 
 */
extern int app_set_time(char *pTimeYYYYMMDDHHMMSS);

/**
@if Chinese
 * @brief	��ȡ�豸tusn(sn)
 * @param[out]	psn		-	tusn(sn)�����ַ
 * @param[in]	size	-	tusn(sn)����󳤶�
 * @return		0		-	�ɹ�  
 * @return		����	-	ʧ��
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
 * @brief	��ȡ�豸��Ϣ
 * @param[out]	terminal				-	�豸��Ϣ�ṹ
 * @return		TERMINALINFO 			-	�豸��Ϣ�ṹָ��
@else 
 * @brief	Obtaining Device Information
 * @param[out]	terminal				-	Device information structure
 * @return		TERMINALINFO 			-	Device information structure pointer
@endif 
 */
extern TERMINALINFO* app_get_terminal_info(TERMINALINFO *terminal);

/**
@if Chinese
 * @brief	��ȡ��ص�����Ϣ
 * @param[out]	batteryinfo				-	��ص�����Ϣ�ṹ
 * @return		0						-	�ɹ�  
 * @return		����					-	ʧ��	
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
 * @brief	�Ƿ��ֹϵͳ����(��Ϣ������ϵͳ������)
 * @param[in]	mode	-	app_true:��ֹ���ߣ�app_false:��������

@else 
 * @brief	Whether to disable system sleep (screen-off, but system does not sleep)
 * @param[in]	mode	-	app_true:sleep not allowed��app_false:Allowed to sleep

@endif 
 */
extern void app_sys_enable_standby(appbool mode);

/**
@if Chinese
 * @brief	��ȡflashʣ��洢�ռ�
 * @return		ʣ��洢�ռ�Ĵ�С(Kb)
@else 
 * @brief	Obtain the remaining flash storage space
 * @return		Remaining storage space (Kb)
@endif 
 */
extern unsigned int app_get_free_space(void);

/**
@if Chinese
* @brief ʹ��һ���汾�뵱ǰ�̼��汾�Ƚ�
* @param[in] 	comparever 				-	��Ҫ�Ƚϵİ汾 
						��ʽΪ x.x.x������"1.3.7"
* @return 		1 						-	��ǰ�̼��汾 > �Ƚϰ汾<br>
* @return 		0 						-	��ǰ�̼��汾 = �Ƚϰ汾<br>
* @return 		-1 						-	��ǰ�̼��汾 < �Ƚϰ汾
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
 * @brief	�豸�ػ�
@else  
 * @brief	Devices are turned off
@endif 
 */
extern void app_power_off(void);

/**
@if Chinese
* @brief ��ȡVSIM ��APN
* @param[out]	vsimapn  				-	��ȡ����VSIM APN
* @return 		0 						-	��ȡ�ɹ�<br>
* @return 		-1						-	��ȡʧ��
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
 * @brief	�ڴ���Ϣ���Դ�ӡ���Ǿ�ȷ��ֻ���ڴ�仯����4kʱ���ݲŻ�仯
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

