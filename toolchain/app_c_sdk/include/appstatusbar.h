/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app status barģ��</strong> ��صĽӿ�
	 * @par �ļ�    appstatusbar.h
	 * @author		yangjing
	 * @date        2020-11-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-11-05    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-26    | 1.0.1        | wenming       | ����Ӣ��ע��  
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
	* @addtogroup status_bar ״̬��
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
  * @brief  ��ö�������г���GPRS״̬����.
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
  * @brief  ��ö�������г���WIFI״̬����.
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
  * @brief  ��ö�������г��˵��״̬����.
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
  * @brief  ��ö�������г���ʱ������/����״̬����.
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
  * @brief  ��ö�������г���nfc led��״̬����.
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
	 *@brief ���������Զ���ͼ��ṹ
@else 	 
	 *@brief Describes a custom icon structure
 @endif 
 */
typedef struct{
    int iconid;                 /**<@if Chinese icon ͼ��ID,�ɲμ�lcd.h�궨��	@else	Icon ICON ID. For details, see LCD. H macro definition	@endif*/
    int status;                 /**<@if Chinese icon��Ӧģ��״̬				@else	Icon Module status	@endif*/
    int xy;                     /**<@if Chinese icon��ʾx y�����꣬��16λΪx�� ��16λΪy @else	Icon displays the coordinates of x and y. The high 16 bits are X and the low 16 bits are Y	@endif*/
    unsigned char *pImage;      /**<@if Chinese icon ͼƬ�ļ�����				@else	Icon Image file data	@endif*/
    void *pnext;                /**<@if Chinese ������һԪ��ָ��				@else	Pointer to the next element in the list	@endif*/
}ST_ICON_IMAGE;

#define ICON_IMAGE_LENGTHGTH sizeof(ST_ICON_IMAGE)	/**<@if Chinese ICONͼƬ�Ĵ�С @else	The size of icon image	@endif*/

#define NOT_CHANGE        0     /**<@if Chinese ģʽ���޸�Ĭ��ֵ @else	Mode does not change the default value	@endif*/

/*!
 @if Chinese
  * @brief  ��ö�������г��˳����ʾͼ��ģʽ.
@else  
  * @brief  This enumerated type lists the charging display icon mode.
@endif
*/
typedef enum{
    CHARGE_SHOW_ICON = 1,       /**<@if Chinese �����ʾΪ��̬ͼ��ģʽ		@else	Charging is displayed in static icon mode	@endif*/
    CHARGE_SHOW_CYCLE,          /**<@if Chinese �����ʾΪ��̬ѭ������ģʽ	@else	Charging is displayed in dynamic cycle mode	@endif*/
}CHARGE_SHOW_MODE;

/*!
 @if Chinese
  * @brief  ��ö�������г��˳�綯̬ѭ����ʾ�����ṹ��.
@else  
  * @brief  This enumerated type lists the charging dynamic cycle display parameter structure.
@endif
*/
typedef struct{
    CHARGE_SHOW_MODE mode;      /**<@if Chinese ���ģʽ				@else	charging mode	@endif*/
    // uint32_t peroid;         /**<@if Chinese ��̬��ʾģʽѭ����� 	@else	Dynamic display mode cycle interval	@endif*/        
}ST_SB_CHAGER_PARA;             

/*!
 @if Chinese
  * @brief  ��ö�������г���״̬�������ṹ��.
@else  
  * @brief  This enumerated type lists the Status Bar parameter structure.
@endif
*/
typedef struct{
    ST_SB_CHAGER_PARA chargepara;
}ST_STATUS_BAR_PARA;


#define ICON_APP_DEF    100					/**<@if Chinese �Զ���ͼ��ID(�����ȿ���ʹ�õײ��ṩID�����ޣ�������Զ���ID) @else	Custom icon ID(it is preferred to use the ID provided by the bottom layer; if no, add a custom ID)	@endif*/

#ifndef ICON_DEV_PROM
#define ICON_DEV_PROM   ICON_APP_DEF+1 		/**<@if Chinese ��������ʾͼ��ID	@else	The developer prompts the icon ID	@endif*/
#endif

#ifndef ICON_TIME
#define ICON_TIME   ICON_APP_DEF+2			/**<@if Chinese ʱ��ͼ��ID			@else	Time icon ID	@endif*/
#endif

#ifndef ICON_LED_BLUE
#define ICON_LED_BLUE   ICON_APP_DEF+3		/**<@if Chinese ����				@else	Blue light	@endif*/
#endif

#ifndef ICON_LED_YELLOW
#define ICON_LED_YELLOW   ICON_APP_DEF+4	/**<@if Chinese �Ƶ�				@else	Yellow light	@endif*/
#endif


#ifndef ICON_LED_GREEN
#define ICON_LED_GREEN   ICON_APP_DEF+5		/**<@if Chinese �̵�				@else	Green light	@endif*/
#endif


#ifndef ICON_LED_RED
#define ICON_LED_RED   ICON_APP_DEF+6		/**<@if Chinese ���				@else	Red light	@endif*/
#endif

/**
@if Chinese
 * @brief	����״̬��ͼ��
 * @param[in]	icon	-	ͼ������
 * @param[in]	onoff	-	�Ƿ���ʾͼ��
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
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
 * @brief	�Զ���״̬����ʼ��
@else 
 * @brief	Custom status bar initialization
 @endif
 */
extern void app_statusbar_init(void);

/*!
@if Chinese
 * @brief		����Ӧ���Զ���״̬����
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
 * @note        δ����ʱ��ʹ�õײ��ṩ��Ĭ��״̬��<br>
 *              ������Ӧ�ÿ����Զ���״̬�������̡߳�Ĭ��ʹ��һ����ײ�ͼ����ͬ��״̬����<br>
 *              ͨ��app_statusbar_set_subjectʵ�ָ��Ի�����״̬��             
  
@else 
 * @brief		Start the application custom status service 
 * @return		0		-	success
 * @return		other	-	fail
 * @note        When not started, use the default state provided at the bottom��<br>
 *              After startup, the application starts the custom status bar service thread. The default is to use the same set of status bars as the underlying icons��<br>
 *              Use the app_statusbar_set_subject achieve personalized setting status bar             
  
@endif 
 */
extern int app_statusbar_service_start(void);

/*!
@if Chinese
 * @brief	�Զ�����Ի�״̬��
 *               ע��: "��������ֹ����"ͼ�겻�����޸�,��ͼ�겻���Զ�������
 * @param[in]	lpStIconImages	-	һ���Զ���ͼ�꼯�����ڸ���/��ӷ�����ԭͼ�꼯<br>
 *                       ��iconid��status��ԭͼ�꼯��ƥ������ͬʱ������ԭͼ�꼯<br>
 *                       ��iconid��status��ԭͼ�꼯��δ��ƥ��ʱ����ӵ�ԭͼ�꼯<br>
 *                       ע�� pImage ͼƬ���ݲ���Ϊ�գ�����ͼ���޷�������ʾ�����<br>
 * @param[in]    num			-	�Զ���ͼ�꼯Ԫ�ظ���
 * @param[in]    lpPara			-	�Զ���״̬�����ò���
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
 * @note	����Ĭ��ͼ�꼯�������£�<br>
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
