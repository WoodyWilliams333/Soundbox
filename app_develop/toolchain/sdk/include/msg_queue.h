/**
@if Chinese
 * @brief       ��ģ���������� <strong>��Ϣ����</strong> ��ؽӿ�
 * @note
 * @par �ļ�    msg_queue.h
 * @author		Wenming
 * @date        2020/09/18
 * @version     1.0.0
 * @remarks     Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2020/09/18    | weifeng         | �����ļ�
 * 2022/04/20    | Wenming         | ����Ӣ��ע��
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
 * @defgroup msg_queue ��Ϣ����
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
 * @brief  ����һ����Ϣ����
 * @param[in]	uxQueueLength	-	���г��� 
 * @param[in]	uxItemSize		-	������Ϣ�ռ��С
 * @return 
		- ��    ����ʧ��
		- �ǿ�  �ɹ������ش����Ķ��е�handle
@else  
 * @brief  Create a message queue
 * @param[in]	uxQueueLength	-	The queue length
 * @param[in]	uxItemSize		-	Size of a single message space
 * @return 
		- NULL    	Fail
		- !NULL  	Success��Returns the Handle of the created queue
@endif  
 */
QueueHandle_t os_msg_queue_create(const unsigned long uxQueueLength, const unsigned long uxItemSize);

/** 
@if Chinese
 * @brief  ��Ϣ���н���
 * @param[in]	xQueue		-	����handle
 * @param[in]	ms			-	(��λms)��ȡʱ�����������ʱʱ�� 0�������� 0xFFFFFFFF���������� 
 * @param[out]	pvBuffer	-	��ȡ������Ϣ������
 * @return 
		- -1    ����ʧ��
        - 0     ����ʧ��
		- 1     ���ճɹ�
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
 * @brief  ��Ϣ���з���
 * @param[in]	xQueue			-	����handle
 * @param[in]	ms				-	(��λms)�ȴ����п��е����ʱʱ�� 0�����ȴ� 0xFFFFFFFF�����õȴ�
 * @param[in]	pvItemToQueue	-	Ҫ���͵Ķ�����
 * @return 
	    - -1    ����ʧ��
        - 0     ����ʧ��
		- 1     ���ͳɹ�
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