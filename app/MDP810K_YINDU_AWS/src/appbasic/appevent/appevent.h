

#ifndef _EVENT_H_
#define _EVENT_H_

#include <appdatatypedef.h>

// ÿһλ����һ��EVENT�� -1��0����
typedef enum{
	EVENT_NOINIT 		= 	-1,			// δ��ʼ��
	EVENT_NONE 			= 	0,			// ���¼�����
	EVENT_KEY			=	0x01,		// �����¼�
	EVENT_TRANS_OCCUR 	= 	0x02,		// ���״���

	EVENT_ALL		= 	EVENT_KEY|EVENT_TRANS_OCCUR	// �����¼�
}E_EVENT_TYPE;

	
typedef struct event_para_st{
	E_EVENT_TYPE event;		// �������¼�����
	int PARAM1;				// �¼�����1
	//void* PARAM2;
}ST_EVENT_PARAM;



/** 
 * @brief  �ȴ��¼�����
 * @note   
 * @param in  
 		EventTypes: ����ָ�����¼�����
 		timeout: ����ʱ��
 * @param out
 		lpEventParam: �������
 * @retval 	
 		TRUE-���¼�����
 		FALSE-δ�����¼�
**/
appbool WaitAppEvent(ST_EVENT_PARAM *lpEventParam, int EventTypes, unsigned long timeout);

/** 
 * @brief  ����¼�����
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		none
**/
void ClearAppEvent(void);

/** 
 * @brief  ����Ƿ����¼�����
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		TRUE-���¼�����
 		FALSE-δ���¼�����
**/
appbool CheckAppEvent(void);


/** 
 * @brief  ����¼������Ƿ�Ϊ��
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		TRUE-�¼�����Ϊ��
 		FALSE-�¼�����ǿգ�����֮ǰ�������¼���Ϣ
**/
appbool CheckAppEventEmpty(void);

/** 
 * @brief  ����һ���¼�����ԭ���¼�Ϊ����������δ������¼�
 * @note   
 * @param in  
 		lpEventParam �¼�����
 * @param out
 		none
 * @retval 
 		0-�ɹ� ��0-ʧ��
**/
int PullAppEvent(ST_EVENT_PARAM *lpEventParam);


#endif
