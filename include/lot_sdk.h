#ifndef _SDK_INCLUDE_H_
#define _SDK_INCLUDE_H_

#ifndef MIN_VERSION_LEN
#define MIN_VERSION_LEN             64                  // ��ȡ�汾��Ϣ��buffer���ٳ���
#endif


/*
mqtt�������������ṹ
check_net_ok 
	������
		������ص���������PPP���ӣ�wifi�ȵ����ӡ�����ʵ��ppp���ӣ��Ա��쳣ʱ����ppp
		ֻ�����������ŻὨ��MQTT���ӡ�
	���أ�
		 0 - ����δ���Ӻ� 
		 1 - ���������Ӻ�
recv_message_proc
	������
		���յ�MQTT������Ϣ����ص�����
	������
	 	msg [in] ���յ���Ϣ����
	 	msg_len ���յ���Ϣ����

char topic[256] 
	������
		���ĵ�����
*/
typedef struct{
	int (*check_net_ok)(void);		//
	void (*recv_message_proc)(void *msg, int msg_len); //
	//int (*check_cancel_wait_msg)(void);
	char topic[256];
	char *productkey;
	char *devname;
	char *devsercetkey;
}mqtt_serv_param_t;


/**
* @brief ����־����
* @param[in] on	0-�� ��0-��
* @return 
*	-<em> 0 </em>  success
*	-<em> ��0 </em>	 failed
*/
extern int lotsdk_logger_on(int on);

/**
* @brief ��ȡliblotsdk��İ汾��Ϣ
* @param[out] version��liblotsdk��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int lotsdk_get_version(char *version, int size);

/**
* @brief ����MQTT�����߳�  
* @param[in]  servpara ���mqtt_serv_param_t�ṹ����
* @return ִ�н��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int StartMqttService(mqtt_serv_param_t *servpara);


#endif
