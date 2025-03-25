
#ifndef _NTP_TIME_H_
#define _NTP_TIME_H_

/*
���ܣ�
ͨ��NTP��ȡ����ʱ�䲢ͬ��������ʱ��
*/

#include <sys/time.h>


typedef struct{
	int *ComType;					//ͨѶ���� ָ�� 01-WIFI 02-GPRS
	char *pFileSaveDir;				//ͬ��ʱ���ļ�����Ŀ¼(һ����Ӧ��Ŀ¼)
}ST_SYNC_TIME_IN;

typedef struct{
	char apn[20];		// sim apn
	char simuid[20];	// sim user id
	char simpwd[20];	// sim user password
}ST_NET_PARAM;


/****************************************************
����NTP���������
��δ���ģ�Ĭ�ϲ���Ϊ��
	apn-"CMNET"
	uid-"CARD"
	pwd-"CARD"
*****************************************************/
extern int UpdateNTPNetParam(ST_NET_PARAM stNetParam);

/****************************************************
��ʼ��NTP�������
stSyncTimeIn [in] ST_SYNC_TIME_IN�ṹ
�ɹ���������0��ʧ�ܷ�������
*****************************************************/
extern int InitSyncPosTime(ST_SYNC_TIME_IN stSyncTimeIn);

/****************************************************
����NTP����

runnow [in] �Ƿ�����ִ��NTP
	0-������ִ�У��ȵ��������ڵ�����ִ��
	1-����ִ�У��������������Ƿ�ﵽ

�ɹ���������0��ʧ�ܷ�������

��ע: 
	�����³ɹ�����Ϊ6Сʱ;������ʧ������Ϊ1Сʱ
*****************************************************/
extern int StartSyncPosTime(int runnow);


#endif
