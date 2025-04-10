

#ifndef _TRANS_PARA_H_
#define _TRANS_PARA_H_

#include "appdef.h"

/*****************************************************
交易中流程控制或经常变化的变量
******************************************************/
typedef struct _trans_ctrl_para_strcut{	
	int lNowTraceNo;
	int lNowBatchNum;
	appbool bClearLog;									// 结算后时候清除日志
	appbool bScriptFlag;								// 脚本标志
	appbool bReveralFlag;								// 冲正标志
	int iTransNum;	
	uint32_t  sTxnRecIndexList[MAX_TRANS_LOG_NUM];		// 交易记录表
	uint8_t szLastLogonDate[8+1];						// 末笔签到时间
	uint8_t szRFU[100];									// 备用数据
}TRANS_CTRL_PARA_STRC;
#define TRANS_CTRL_SIZE sizeof(TRANS_CTRL_PARA_STRC)

/*****************************************************
交易中终端保存的交易参数变量
******************************************************/
typedef struct _trans_data_para_strcut{
	char szLogonTellerNo[4];	// 终端签到时已登录操作员号	
	uint8_t szUnitNum[16];		// 商户号
	uint8_t szPosId[9];			// 终端号
	uint8_t szUnitChnName[41];	// 商户名称(ch)
	uint8_t szEngName[41];		// 商户名称(en)

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
	
	appbool bFreePinLoaded; 			//免密卡BIN
	appbool bFreePinBlkListLoaded;		//免密BIN黑名单
	
	appsw swQuickFlag;         //非接快速业务标识
	appsw swBINAFlag;          //BIN表A标识
	appsw swBINBFlag;          //BIN表B标识
	appsw swBINCFlag;			//BIN表C标记
	appsw swCDCVMFlag;         //CDCVM标识
	appsw swFreeSignFlag;      //免签标识
	uint8_t ucMaxFreePinAmt[13];  //非接快速业务（QPS）免密限额
	uint8_t ucMaxFreeSignAmt[13]; //免签限额
	uint8_t ucDepositAmt[13];	  //押金金额
	
	appsw swPreferPassive;    //优选挥卡
	appsw swTrackEncrypt;	  // 磁道加密
	appsw swByPass;	 	 	  // 是否允许bypass

	appsw swSupElecSign;		 // 是否支持电子签名

	/*交易是否输密类start*/
	appsw swVoidPin;						//撤销是否输密
	appsw swPreVoidPin;						//预授权撤销是否输密
	appsw swPreComVoidPin;					//预授权完成撤销是否输密
	appsw swPreComPin;  					//预授权完成是否输密

	/*交易是否输刷卡 start*/
	appsw swVoidSwipe;						//撤销是否刷卡
	appsw swPreComVoidSwipe;				//预授权完成撤销是否刷卡

	/*结算交易控制start*/
	appsw swAutoLogoff;						//结算自动签退
	appsw swDetailPrt;						//结算是否打印明细

	/*其他交易控制start*/
	appsw swManualInput;					//是否支持手输卡号


	uint8_t sTransOpen[8];
	uint8_t randomKey[64];       //鐢ㄦ埛闅忔満瀵嗛挜
	
}TRANS_DATA_PARA_STRC;
#define TRANS_PARA_SIZE	sizeof(TRANS_DATA_PARA_STRC)


/*****************************************************
mqtt鍙傛暟
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
mqtt 鐧诲綍鍙傛暟
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
	char value[400];		//鍊�
	
}JSON_RECVDATA_REC;





#endif

