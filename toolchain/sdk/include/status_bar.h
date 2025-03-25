/**
 @if Chinese
	 * @brief       ��ģ���������� <strong>״̬������</strong> ��ؽӿ�
	 * @par �ļ�    status_bar.h
	 * @author		Wenming
	 * @date        2020/09/21
	 * @version     1.0.1
	 * @remarks     Change History:
	 * ����          | ����          | ����
	 * ------------- | --------------- | ----
	 * 2020/09/21    | weifeng         | �����ļ�
	 * 2022/04/20    | Wenming         | ����Ӣ��ע��
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
	* @defgroup status_bar ״̬��
 @else 
	* @defgroup status_bar StatusBar
 @endif 
 * @{
*/
struct icon_callbak{
    int (*set_up_icon)(int onoff); 	/**<@if Chinese ����ע����Ϸ�ͼ��Ļص����� @else	Up icon callback function	@endif*/ 
    int (*set_down_icon)(int onoff);/**<@if Chinese ����ע����·�ͼ��Ļص����� @else	Down icon callback function	@endif*/ 
};

/**
@if Chinese
	 *@brief ��������״̬����Ϣ��������
@else 
	 *@brief Describes the basic type of status bar messages
@endif 
 */
typedef struct {
    int msg_type;	/**<@if Chinese ��Ϣ����,Ӧ����Ҫ�õ�������:STATUS_BAR_MSG @else	Message type:STATUS_BAR_MSG	@endif*/
} ipc_msg_t;

/**
@if Chinese
	 *@brief ��������״̬����Ϣ
@else 	 
	 *@brief Used to describe status bar messages
 @endif 
 */
typedef struct {
    ipc_msg_t base;	/**<@if Chinese ��Ϣ����,Ӧ����Ҫ�õ�������:STATUS_BAR_MSG @else	Message type:STATUS_BAR_MSG	@endif*/
    int type;		/**<@if Chinese ״̬���¼�����  @else	Status type	@endif*/
    int event_id;	/**<@if Chinese �¼�id,��ͬ����Ϣ�¼�id��ͬ @else	Event ID	@endif*/
} status_bar_msg_t;

/**
 @if Chinese
  * @brief  ��ö�������г�����Ϣ����.
@else  
  * @brief  This enumerated type lists the message types.
@endif
*/
typedef enum {
    STATUS_BAR_MSG,/**<@if Chinese ״̬����Ϣ@else	Status bar message	@endif*/
} IPC_MSG_TYPE;

/**
 @if Chinese
  * @brief  ��ö�������г���״̬���¼�����.
 @else  
  * @brief  This enumerated type lists the status bar event types.
@endif  
*/
enum {
	E_PHONE_SERVER_EVENT,		/**<@if Chinese �ƶ�����(4G/2G)�¼� @else	Mobile network (4G/2G) events	@endif*/
	E_PED_EVENT,		 		/**<@if Chinese ped�¼� 			@else	Ped event						@endif*/
	E_TAMPER_ALARM_EVENT,		/**<@if Chinese ped�����¼� 		@else	Ped attacks event				@endif*/
	E_WIFI_EVENT,				/**<@if Chinese wifi�¼� 			@else	WIFI event						@endif*/
	E_BT_EVENT,				    /**<@if Chinese �����¼� 			@else	bluetooth�¼� event				@endif*/
	E_CHARGE_EVENT,				/**<@if Chinese �������¼� 		@else	Charging related event			@endif*/
	E_ICCARD_EVENT,				/**<@if Chinese ICCARD�¼� 			@else	ICCARD event					@endif*/
	E_UP_EVENT,					/**<@if Chinese �Ϸ�ͼ��			@else	UP ICONS						@endif*/
	E_DOWN_EVENT,				/**<@if Chinese �·�ͼ����ʾ�¼�	@else	DOWN ICONS						@endif*/
	E_LINK_EVENT,				/**<@if Chinese ����ͼ����ʾ�¼�	@else	LINK ICONS						@endif*/
	E_LED_1_EVENT,				/**<@if Chinese LED1�¼� 			@else	LED1 event						@endif*/
	E_LED_2_EVENT,				/**<@if Chinese LED2�¼� 			@else	LED2 event						@endif*/
	E_LED_3_EVENT,			    /**<@if Chinese LED3�¼� 			@else	LED3 event						@endif*/
	E_LED_4_EVENT,				/**<@if Chinese LED4�¼� 			@else	LED4 event						@endif*/
	E_PROMPT_EVENT,				/**<@if Chinese ״̬����ʾ�¼� 	    @else	status bar prompt event			@endif*/
	E_DATE_EVENT,				/**<@if Chinese ������ʾ�¼�  	    @else	Date prompt event			    @endif*/
	E_POWER_LPREES_EVENT,		/**<@if Chinese ��Դ�������¼� 	    @else	Power button long press event	@endif*/
	E_END_EVENT,				/**<@if Chinese ö�ٽ�����־ 		@else	Enum end flag					@endif*/
};

/** 
 @if Chinese
	 * @brief  ����ΪӦ���Զ���״̬�� 
	 * @retval  0   ���óɹ�
	 * @retval  -1  ����ʧ��
 @else	 
	 * @brief  Set to apply a custom status bar
	 * @retval  0   Success
	 * @retval  -1  Fail
  @endif
 */
int set_status_bar_customize(void);

/** 
 @if Chinese
	 * @brief  �ָ���ϵͳ״̬��
	 * @retval  0   ���óɹ�
	 * @retval  -1  ����ʧ��
 @else	 
	 * @brief  restore to system stattus bar
	 * @retval  0   Success
	 * @retval  -1  Fail
  @endif
 */
int restore_status_bar_systemize(void);

/** 
 @if Chinese
	 * @brief  ��ȡstatus_bar��Ϣ���е�handle
	 * @return 
		   - NULL    ����ʧ��
		   - ��NULL  �ɹ�������status_bar��Ϣ���е�handle
 @else
	 * @brief  Gets the Handle of the status_bar message queue
	 * @return 
		   - NULL    Fail
		   - !NULL  Success��Returns the Handle of the status_bar message queue
 @endif 
 */
QueueHandle_t get_status_bas_msg_queue_handle(void);


/** 
 @if Chinese
	 * @brief  ����ע����ʾ���·�ͼ��Ļص�����
	 * @param[in] pfun	-	Ӧ����ʾ����ͼ��Ļص����� struct icon_callbak
	 * @return 
		   - -1    ����ʧ��
		   - 1	   ��ȡ�ɹ�
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