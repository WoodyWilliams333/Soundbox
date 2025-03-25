/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app async msgģ��</strong> ��صĽӿ�
	 * @par �ļ�    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-10-22
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-10-22    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-14    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app async msg </strong>  module
	 * @par file    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-10-22
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-10-22    | 1.0.0        | yanjing       | create file
	 * 2022-04-14    | 1.0.1        | lydia         | Add English description
 @endif 
*/
/*!
 @if Chinese
	@defgroup appasyncmsg �첽��Ϣ
 @else
	@defgroup appasyncmsg async message
 @endif
 * @{
*/

#ifndef _APP_ASYNC_MSG_H_
#define _APP_ASYNC_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <system.h>
#include <syscall.h>

#define EVENT_MAX_NUM           5    /**< @if Chinese ����event�������Ŀ @else maximum number of events created @endif */   
#define EVENT_NAME_NAX_LEN      21   /**< @if Chinese event����󳤶� @else the maximum length of event name @endif */

/*!
 @if Chinese
	@brief          �����¼�,��������¼���ĿΪEVENT_MAX_NUM,ͨѶ��scheduwork�Ѹ�ռ��һ��
	@param[in]      event_name	-	�¼�����
	@param[out]     eventgp_ptr	-	�¼���������ַ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          create event
	@param[in]      event_name	-	event name
	@param[out]     eventgp_ptr	-	event handle save address
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
int app_event_creat(const char *event_name, void **eventgp_ptr);

/*!
 @if Chinese
	@brief          �����¼�
	@param[in]      msg			-	��Ϣ����ָ��
	@param[in]      msg_len		-	��Ϣ���ݳ���
	@param[in]      event_ptr	-	 �¼����
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          send message
	@param[in]      msg			- message data point
	@param[in]      msg_len		-	message length
	@param[in]      event_ptr	-	event handle
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
int app_event_send_msg(void *msg, int msg_len, void *event_ptr);

/*!
 @if Chinese
	@brief          �����¼�
	@param[in]      event_ptr	-	�¼����
	@param[out]     msg			-	��Ϣ����ָ��
	@param[out]     msg_len		-	��Ϣ���ݳ���
	@param[out]     timeout		-	�����¼���ʱʱ�䣬-1Ϊ�޳�ʱ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          receive message
	@param[in]      event_ptr	-	event handle
	@param[out]     msg			-	message data point
	@param[out]     msg_len		-	message length
	@param[out]     timeout		-	timeout��-1 is no timeout
	@return         0		-	success
	@return         other	-	fail
 @endif
*/    
int app_event_recv_msg(void **msg, int *msg_len, void *event_ptr, int timeout);

/*!
 @if Chinese
	@brief          ɾ���¼�
	@param[in]      event_ptr	-	�¼����
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          delete event
	@param[in]      event_ptr	-	event handle
	@return         0		-	success
	@return         other	-	fail
 @endif
*/     
int app_event_delete(void *event_ptr);

/*!
 @if Chinese
	@brief          ��ʼ����Ӧ����
	@param[in]      event_ptr	-	�¼����
 @else
	@brief          init event response
	@param[in]      event_ptr	-	event handle
 @endif
*/ 
void app_init_event_respon(void *event_ptr);

/*!
 @if Chinese
	@brief          ������Ӧ��������ͨ��app_get_event_respon()��ȡ��λ��Ӧ�����
	@param[in]      event_ptr	-	�¼����
 @else
	@brief          set response started,get and clear by app_get_event_response
	@param[in]      event_ptr	-	event handle
 @endif
*/ 
void app_set_event_resopn(void *event_ptr);

/*!
 @if Chinese
	@brief          �����ȴ�ֱ��app_set_event_resopn()��λ����Ӧ���������λ����Ӧ
	@param[in]      event_ptr	-	�¼����
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          block wait until app_set_event_respn() set and clear the response
	@param[in]      event_ptr	-	event handle
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
uint8_t app_get_event_respon(void *event_ptr);

#ifdef __cplusplus
}
#endif

#endif