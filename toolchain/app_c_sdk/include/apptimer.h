/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app timerģ��</strong> ��صĽӿ�
	 * @par �ļ�    apptimer.h
	 * @author		yangjing
	 * @date        2020-10-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-10-28    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-26    | 1.0.1        | wenming       | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app timer </strong>  module
	 * @par file    apptimer.h
	 * @author		yangjing
	 * @date        2020-10-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-10-28    | 1.0.0        | yanjing       | create file
	 * 2022-04-26    | 1.0.1        | wenming       | Add English description
 @endif 
*/

/*!
 @if Chinese
	* @addtogroup app_timer ��ʱ��
 @else 
	* @addtogroup app_timer timer
 @endif 
 * @{
*/ 
 
#ifndef _APP_TIMER_H_
#define _APP_TIMER_H_

#define TIMER1_BASE_EXPIRES  500        /**<@if Chinese ��ʱ��1����ms @else	Timer 1 precision MS	@endif*/
#define TIMER2_BASE_EXPIRES  1000       /**<@if Chinese ��ʱ��2����ms @else	Timer 2 precision MS	@endif*/

typedef void (*timer_callback_fc)(void *);	/**<@if Chinese ��ʱ��ִ�к����ص�	@else	The timer performs function callbacks	@endif*/

/**
@if Chinese
 * @brief  ��������ʱ��1
 * @param[in]	func		-	��ʱ���ص�����ָ��
 * @param[in]	para		-	��ʱ���ص���������ָ��
 * @return		<= 0   		-	ʧ��
 * @return		>0    		-	���ط���Ķ�ʱ��ID
 * @note 		���ڶ�ʱ�������߳�ʵ�֣���ע�����ָ�����Ч�� 
@else   
 * @brief  Adding a Software Timer 1
 * @param[in]	func		-	Timer callback function pointer
 * @param[in]	para		-	Timer callback function parameter pointer
 * @return		<= 0   		-	Faild
 * @return		>0     		-	Returns the assigned timer ID
 * @note 	Since timers are implemented in threads, be aware of the validity of the parameter pointer
@endif  
 */
int app_timer1_append(timer_callback_fc func, void *para);

/**
@if Chinese
 * @brief  ������ʱ��1
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @param[in]   expires		-	��ʱ����ʱ����(ms)
 * @return 		0    		-	�ɹ�
 * @return 		����    	-	ʧ��
@else 
 * @brief  Start timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @param[in]   expires		-	Timer Timing period (ms)
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
 @endif  
 */
int app_timer1_start(int timerid, unsigned long expires);

/**
@if Chinese
 * @brief  ֹͣ��ʱ��1
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return 		0    		-	�ɹ�
 * @return 		����    	-	ʧ��
@else  
 * @brief  Stop timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
@endif 
 */
int app_timer1_stop(int timerid);

/**
@if Chinese
 * @brief  ɾ����ʱ��1
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return 		0    		-	�ɹ�
 * @return 		����    	-	ʧ��
@else 
 * @brief  Deleting timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
@endif 
 */
int app_timer1_delete(int timerid);

/**
@if Chinese
 * @brief  ��ⶨʱ��1�Ƿ񼤻�
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return 		app_true   		-	�Ѽ���
 * @return 		app_false   	-	δ����򲻴���
@else  
 * @brief  Check whether timer 1 is activated
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		app_true   		-	activated
 * @return		app_false  		-	Inactive or not present
@endif 
 */
appbool app_timer1_check_active(int timerid);

/**
@if Chinese
 * @brief  ��������ʱ��2
 * @param[in]	func		-	��ʱ���ص�����ָ��
 * @param[in]   para		-	��ʱ���ص���������ָ��,���ڶ�ʱ����һ�߳�ʵ�֣���ע�����ָ�����Ч��
 * @return		<= 0    	-	ʧ��
 * @return		>0     		-	���ط���Ķ�ʱ��ID
@else   
 * @brief  Adding a Software Timer 2
 * @param[in]	func		-	Timer callback function pointer
 * @param[in]   para		-	Timer callback function parameter pointer, since timer is a thread implementation, please note the validity of parameter pointer
 * @return		<= 0  		-	fail
* @return		>0     		-	Returns the assigned timer ID
@endif  
 */
int app_timer2_append(timer_callback_fc func, void *para);

/**
@if Chinese
 * @brief  ������ʱ��2
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @param[in]   expires		-	��ʱ����ʱ����(ms)
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
@else   
 * @brief  Start timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @param[in]   expires		-	Timer Timing period (ms)
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif  
 */
int app_timer2_start(int timerid, unsigned long expires);

/**
@if Chinese
 * @brief  ֹͣ��ʱ��2
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
@else 
 * @brief  Stop timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif 
 */
int app_timer2_stop(int timerid);

/**
@if Chinese
 * @brief  ɾ����ʱ��2
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return		0			-	�ɹ�  
 * @return		����		-	ʧ��
@else 
 * @brief  Deleting Timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif 
 */
int app_timer2_delete(int timerid);

/**
@if Chinese
 * @brief  ��鶨ʱ��2�Ƿ񱻼���
 * @param[in]	timerid		-	����Ķ�ʱ��ID
 * @return 		app_true   		-	�Ѽ���
 * @return 		app_false   	-	δ����򲻴���
@else 
 * @brief  Check whether timer 2 is activated
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		app_true  	  	-	activated
 * @return		app_false   	-	Inactive or not present
@endif 
 */
appbool app_timer2_check_active(int timerid);

#endif