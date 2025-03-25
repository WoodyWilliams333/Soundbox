/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app async msg模块</strong> 相关的接口
	 * @par 文件    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-10-22
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-10-22    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-14    | 1.0.1        | lydia         | 增加英文注释  
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
	@defgroup appasyncmsg 异步消息
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

#define EVENT_MAX_NUM           5    /**< @if Chinese 创建event的最大数目 @else maximum number of events created @endif */   
#define EVENT_NAME_NAX_LEN      21   /**< @if Chinese event名最大长度 @else the maximum length of event name @endif */

/*!
 @if Chinese
	@brief          创建事件,创建最大事件数目为EVENT_MAX_NUM,通讯与scheduwork已各占用一个
	@param[in]      event_name	-	事件名称
	@param[out]     eventgp_ptr	-	事件句柄保存地址
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          发送事件
	@param[in]      msg			-	消息数据指针
	@param[in]      msg_len		-	消息数据长度
	@param[in]      event_ptr	-	 事件句柄
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          接收事件
	@param[in]      event_ptr	-	事件句柄
	@param[out]     msg			-	消息数据指针
	@param[out]     msg_len		-	消息数据长度
	@param[out]     timeout		-	接收事件超时时间，-1为无超时
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          receive message
	@param[in]      event_ptr	-	event handle
	@param[out]     msg			-	message data point
	@param[out]     msg_len		-	message length
	@param[out]     timeout		-	timeout，-1 is no timeout
	@return         0		-	success
	@return         other	-	fail
 @endif
*/    
int app_event_recv_msg(void **msg, int *msg_len, void *event_ptr, int timeout);

/*!
 @if Chinese
	@brief          删除事件
	@param[in]      event_ptr	-	事件句柄
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          初始化响应参数
	@param[in]      event_ptr	-	事件句柄
 @else
	@brief          init event response
	@param[in]      event_ptr	-	event handle
 @endif
*/ 
void app_init_event_respon(void *event_ptr);

/*!
 @if Chinese
	@brief          设置响应已启动，通过app_get_event_respon()获取置位响应并清除
	@param[in]      event_ptr	-	事件句柄
 @else
	@brief          set response started,get and clear by app_get_event_response
	@param[in]      event_ptr	-	event handle
 @endif
*/ 
void app_set_event_resopn(void *event_ptr);

/*!
 @if Chinese
	@brief          阻塞等待直到app_set_event_resopn()置位了响应，并清除置位的响应
	@param[in]      event_ptr	-	事件句柄
	@return         0		-	成功
	@return         其它	-	失败
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