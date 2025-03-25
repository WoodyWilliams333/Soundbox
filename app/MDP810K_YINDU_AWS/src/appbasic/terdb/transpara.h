

#ifndef _TRANS_PARA_H_
#define _TRANS_PARA_H_

#include "appdef.h"

/*****************************************************
½»Ò×ÖĞÁ÷³Ì¿ØÖÆ»ò¾­³£±ä»¯µÄ±äÁ¿
******************************************************/
typedef struct _trans_ctrl_para_strcut{	
	int lNowTraceNo;
	int lNowBatchNum;
	appbool bClearLog;									// ½áËãºóÊ±ºòÇå³ıÈÕÖ¾
	appbool bScriptFlag;								// ½Å±¾±êÖ¾
	appbool bReveralFlag;								// ³åÕı±êÖ¾
	int iTransNum;	
	uint32_t  sTxnRecIndexList[MAX_TRANS_LOG_NUM];		// ½»Ò×¼ÇÂ¼±í
	uint8_t szLastLogonDate[8+1];						// Ä©±ÊÇ©µ½Ê±¼ä
	uint8_t szRFU[100];									// ±¸ÓÃÊı¾İ
}TRANS_CTRL_PARA_STRC;
#define TRANS_CTRL_SIZE sizeof(TRANS_CTRL_PARA_STRC)

/*****************************************************
½»Ò×ÖĞÖÕ¶Ë±£´æµÄ½»Ò×²ÎÊı±äÁ¿
******************************************************/
typedef struct _trans_data_para_strcut{
	char szLogonTellerNo[4];	// ÖÕ¶ËÇ©µ½Ê±ÒÑµÇÂ¼²Ù×÷Ô±ºÅ	
	uint8_t szUnitNum[16];		// ÉÌ»§ºÅ
	uint8_t szPosId[9];			// ÖÕ¶ËºÅ
	uint8_t szUnitChnName[41];	// ÉÌ»§Ãû³Æ(ch)
	uint8_t szEngName[41];		// ÉÌ»§Ãû³Æ(en)

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
	
	appbool bFreePinLoaded; 			//ÃâÃÜ¿¨BIN
	appbool bFreePinBlkListLoaded;		//ÃâÃÜBINºÚÃûµ¥
	
	appsw swQuickFlag;         //·Ç½Ó¿ìËÙÒµÎñ±êÊ¶
	appsw swBINAFlag;          //BIN±íA±êÊ¶
	appsw swBINBFlag;          //BIN±íB±êÊ¶
	appsw swBINCFlag;			//BIN±íC±ê¼Ç
	appsw swCDCVMFlag;         //CDCVM±êÊ¶
	appsw swFreeSignFlag;      //ÃâÇ©±êÊ¶
	uint8_t ucMaxFreePinAmt[13];  //·Ç½Ó¿ìËÙÒµÎñ£¨QPS£©ÃâÃÜÏŞ¶î
	uint8_t ucMaxFreeSignAmt[13]; //ÃâÇ©ÏŞ¶î
	uint8_t ucDepositAmt[13];	  //Ñº½ğ½ğ¶î
	
	appsw swPreferPassive;    //ÓÅÑ¡»Ó¿¨
	appsw swTrackEncrypt;	  // ´ÅµÀ¼ÓÃÜ
	appsw swByPass;	 	 	  // ÊÇ·ñÔÊĞíbypass

	appsw swSupElecSign;		 // ÊÇ·ñÖ§³Öµç×ÓÇ©Ãû

	/*½»Ò×ÊÇ·ñÊäÃÜÀàstart*/
	appsw swVoidPin;						//³·ÏúÊÇ·ñÊäÃÜ
	appsw swPreVoidPin;						//Ô¤ÊÚÈ¨³·ÏúÊÇ·ñÊäÃÜ
	appsw swPreComVoidPin;					//Ô¤ÊÚÈ¨Íê³É³·ÏúÊÇ·ñÊäÃÜ
	appsw swPreComPin;  					//Ô¤ÊÚÈ¨Íê³ÉÊÇ·ñÊäÃÜ

	/*½»Ò×ÊÇ·ñÊäË¢¿¨ start*/
	appsw swVoidSwipe;						//³·ÏúÊÇ·ñË¢¿¨
	appsw swPreComVoidSwipe;				//Ô¤ÊÚÈ¨Íê³É³·ÏúÊÇ·ñË¢¿¨

	/*½áËã½»Ò×¿ØÖÆstart*/
	appsw swAutoLogoff;						//½áËã×Ô¶¯Ç©ÍË
	appsw swDetailPrt;						//½áËãÊÇ·ñ´òÓ¡Ã÷Ï¸

	/*ÆäËû½»Ò×¿ØÖÆstart*/
	appsw swManualInput;					//ÊÇ·ñÖ§³ÖÊÖÊä¿¨ºÅ


	uint8_t sTransOpen[8];
	uint8_t randomKey[64];       //ç”¨æˆ·éšæœºå¯†é’¥
	
}TRANS_DATA_PARA_STRC;
#define TRANS_PARA_SIZE	sizeof(TRANS_DATA_PARA_STRC)


/*****************************************************
mqttå‚æ•°
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
mqtt ç™»å½•å‚æ•°
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
	char value[400];		//å€¼
	
}JSON_RECVDATA_REC;





#endif

