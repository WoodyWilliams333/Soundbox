#ifndef _TMS_SILENCE_H_
#define _TMS_SILENCE_H_

typedef void (*pTmsAutoTaskCb)(void);

//tms_app_download_ex ��Ҫ�Ĳ����ṹ��
typedef struct 
{
	struct timeval tBegin;  //��ʱ��ʼʱ��
	unsigned long timeCount; //���ʱ��
	uint8_t IsHold;  //�Ƿ���ͣ
	uint8_t IsReset;  //�Ƿ��ڸ���TMS ��ʾ�û�����ʱ�õ� ���������ع���
	uint8_t Runing; //�����ж�tms���ػ��������߳��Ƿ�����ִ�� ��ֹ�߳�δִ�н����ֿ����߳�
	uint8_t showProc;//�Ƿ���ʾ���ع��� ��Ӧ�ÿ���
	uint8_t showTmsProc;//�Ƿ��Ѿ���ʾ���ع��� ��tms�����
	
	uint8_t TmsUpdata;//�Ƿ���Ը��� ���غ���ж�
	char *pAppDir;
	uint8_t UpdataNow;         //��������tmsǿ�Ƹ��� ���ж�ʱ��
}TimeArg;

void SetThreadArg(TimeArg pArg_temp);
void GetThreadArg(TimeArg *lpTimerArg);
void InitTmsTimeArg(int supsilence, const char *pAppDir);
int StartTmsService(pTmsAutoTaskCb pCbFunc);
void UpdateTmsTime(void);

#endif

