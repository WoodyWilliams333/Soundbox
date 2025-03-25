

#ifndef _TRANS_PARA_H_
#define _TRANS_PARA_H_

#include "appdef.h"

/*****************************************************
���������̿��ƻ򾭳��仯�ı���
******************************************************/
typedef struct _trans_ctrl_para_strcut{	
	int lNowTraceNo;
	int lNowBatchNum;
	appbool bClearLog;									// �����ʱ�������־
	appbool bScriptFlag;								// �ű���־
	appbool bReveralFlag;								// ������־
	int iTransNum;	
	uint32_t  sTxnRecIndexList[MAX_TRANS_LOG_NUM];		// ���׼�¼��
	uint8_t szLastLogonDate[8+1];						// ĩ��ǩ��ʱ��
	uint8_t szRFU[100];									// ��������
}TRANS_CTRL_PARA_STRC;
#define TRANS_CTRL_SIZE sizeof(TRANS_CTRL_PARA_STRC)

/*****************************************************
�������ն˱���Ľ��ײ�������
******************************************************/
typedef struct _trans_data_para_strcut{
	char szLogonTellerNo[4];	// �ն�ǩ��ʱ�ѵ�¼����Ա��	
	uint8_t szUnitNum[16];		// �̻���
	uint8_t szPosId[9];			// �ն˺�
	uint8_t szUnitChnName[41];	// �̻�����(ch)
	uint8_t szEngName[41];		// �̻�����(en)

	uint8_t ucKeyMode;
	uint8_t ucKeyIndex;
	
	int iMaxTransNum;

	uint8_t ucPosStatus; 
	uint8_t ucBatchUpStatus; 	 
	uint8_t ucRmbSettStatus;
	uint8_t ucFrnSettStatus;
	
	appbool bEmvCapkLoaded;
	appbool bEmvAppLoaded;
	appbool bQuickPayParaLoaded;
	
	appbool bFreePinLoaded; 			//���ܿ�BIN
	appbool bFreePinBlkListLoaded;		//����BIN������
	
	appsw swQuickFlag;         //�ǽӿ���ҵ���ʶ
	appsw swBINAFlag;          //BIN��A��ʶ
	appsw swBINBFlag;          //BIN��B��ʶ
	appsw swBINCFlag;			//BIN��C���
	appsw swCDCVMFlag;         //CDCVM��ʶ
	appsw swFreeSignFlag;      //��ǩ��ʶ
	uint8_t ucMaxFreePinAmt[13];  //�ǽӿ���ҵ��QPS�������޶�
	uint8_t ucMaxFreeSignAmt[13]; //��ǩ�޶�
	uint8_t ucDepositAmt[13];	  //Ѻ����
	
	appsw swPreferPassive;    //��ѡ�ӿ�
	appsw swTrackEncrypt;	  // �ŵ�����
	appsw swByPass;	 	 	  // �Ƿ�����bypass

	appsw swSupElecSign;		 // �Ƿ�֧�ֵ���ǩ��

	/*�����Ƿ�������start*/
	appsw swVoidPin;						//�����Ƿ�����
	appsw swPreVoidPin;						//Ԥ��Ȩ�����Ƿ�����
	appsw swPreComVoidPin;					//Ԥ��Ȩ��ɳ����Ƿ�����
	appsw swPreComPin;  					//Ԥ��Ȩ����Ƿ�����

	/*�����Ƿ���ˢ�� start*/
	appsw swVoidSwipe;						//�����Ƿ�ˢ��
	appsw swPreComVoidSwipe;				//Ԥ��Ȩ��ɳ����Ƿ�ˢ��

	/*���㽻�׿���start*/
	appsw swAutoLogoff;						//�����Զ�ǩ��
	appsw swDetailPrt;						//�����Ƿ��ӡ��ϸ

	/*�������׿���start*/
	appsw swManualInput;					//�Ƿ�֧�����俨��


	uint8_t sTransOpen[8];
	uint8_t randomKey[64];       //用户随机密钥
	
}TRANS_DATA_PARA_STRC;
#define TRANS_PARA_SIZE	sizeof(TRANS_DATA_PARA_STRC)


/*****************************************************
mqtt参数
******************************************************/
typedef struct _mqttdata_strcut{

	uint8_t  clientId[100];  
	uint8_t deviceName[100];
 	uint8_t productKey[100];
	uint8_t broker[100];
	uint8_t subscribe_topics[100];
	uint8_t token[100];
	uint8_t username[100];	
	uint8_t groupId[80];
	uint8_t mqttaddr[60];
	
	int mqttport;

}MQTTDATA_STRC;

#define MQTTDATA_SIZE	sizeof(MQTTDATA_STRC)



/*****************************************************
mqtt 登录参数
******************************************************/
typedef struct _mqttlogondata_strcut{

	MQTTDATA_STRC mqttpara;
	
	int Mqttinterval;
	int retryCount;
	int retryInterval;	
	
}MQTTLOGONDATA_STRC;

#define MQTTLOGONDATA_SIZE	sizeof(MQTTLOGONDATA_STRC)




typedef struct _staticdata_strcut{

	uint8_t  Key[50];  
	uint8_t  Value[100];
	
}STATICDATA_STRC;

#define STATICDATA_SIZE	sizeof(STATICDATA_STRC)


typedef struct JSON_RECVDATA22
{
	char key[30];   		//KEY
	char value[400];		//值
	
}JSON_RECVDATA_REC;





#endif

