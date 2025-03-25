/**
@if Chinese
 * @brief       此模块用于描述 <strong>消息队列</strong> 相关接口
 * @note
 * @par 文件    msg_queue.h
 * @author		Wenming
 * @date        2020/09/18
 * @version     1.0.0
 * @remarks     Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2020/09/18    | weifeng         | 创建文件
 * 2022/04/20    | Wenming         | 增加英语注释
@else 
 * @brief      This module is used to describe <strong>Message Queue</strong> interfaces module
 * @note
 * @par file    msg_queue.h
 * @author		Wenming
 * @date        2020/09/18
 * @version     1.0.0
 * @remarks     Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2020/09/18    | weifeng         | Create file
 * 2022/04/20    | Wenming         | Add English description
@endif  
*/


/**
@if Chinese
 * @defgroup msg_queue 消息队列
@else 
 * @defgroup msg_queue MessageQueue
@endif 
 * @{
*/

#ifndef _MSG_QUEUE_H__
#define _MSG_QUEUE_H__

#define SCI_NO_WAIT                 0x0
#define SCI_WAIT_FOREVER            0xFFFFFFFF

typedef void * QueueHandle_t;

/** 
@if Chinese
 * @brief  创建一个消息队列
 * @param[in]	uxQueueLength	-	队列长度 
 * @param[in]	uxItemSize		-	单个消息空间大小
 * @return 
		- 空    调用失败
		- 非空  成功，返回创建的队列的handle
@else  
 * @brief  Create a message queue
 * @param[in]	uxQueueLength	-	The queue length
 * @param[in]	uxItemSize		-	Size of a single message space
 * @return 
		- NULL    	Fail
		- !NULL  	Success，Returns the Handle of the created queue
@endif  
 */
QueueHandle_t os_msg_queue_create(const unsigned long uxQueueLength, const unsigned long uxItemSize);

/** 
@if Chinese
 * @brief  消息队列接收
 * @param[in]	xQueue		-	队列handle
 * @param[in]	ms			-	(单位ms)读取时发生阻塞最大超时时间 0：不阻塞 0xFFFFFFFF：永久阻塞 
 * @param[out]	pvBuffer	-	获取到的消息队列项
 * @return 
		- -1    调用失败
        - 0     接收失败
		- 1     接收成功
@else 
 * @brief  Message queue reception
 * @param[in]	xQueue		-	queue handle...
 * @param[in]	ms			-	(Unit: ms)Maximum timeout for blocking when reading 0: not blocked 0xFFFFFFFF: permanently blocked 
 * @param[out]	pvBuffer	-	The message queue entry that was obtained
 * @return 
		- -1    Call fails
        - 0     Receive failure
		- 1     Receive success 
@endif 
 */
long os_msg_queue_receive(QueueHandle_t xQueue, void * const pvBuffer, unsigned int ms);

/** 
@if Chinese
 * @brief  消息队列发送
 * @param[in]	xQueue			-	队列handle
 * @param[in]	ms				-	(单位ms)等待队列空闲的最大超时时间 0：不等待 0xFFFFFFFF：永久等待
 * @param[in]	pvItemToQueue	-	要发送的队列项
 * @return 
	    - -1    调用失败
        - 0     发送失败
		- 1     发送成功
@else 
 * @brief  Message queue sending
 * @param[in]	xQueue			-	queue handle...
 * @param[in]	ms				-	(Unit: ms)Maximum timeout for blocking when reading 0: not blocked 0xFFFFFFFF: permanently blocked 
 * @param[in]	pvItemToQueue	-	The queue item to send
 * @return 
		- -1    Call fails
        - 0     Receive failure
		- 1     Receive success
@endif 
 */
long os_msg_queue_send(QueueHandle_t xQueue, const void * const pvItemToQueue, unsigned int ms);
#endif

/** @} */