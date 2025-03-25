#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfileinter.h"
#include "terfiledef.h"

#define PARAM_DEFAULT_PWD	"00000000"

int LoadDefaultTransPara(void)
{		
	memset(&stTransPara,0,sizeof(TRANS_DATA_PARA_STRC));
	
	memset(stTransPara.szLogonTellerNo, 0, sizeof(stTransPara.szLogonTellerNo));
	snprintf((char *)stTransPara.szUnitNum, sizeof(stTransPara.szUnitNum), "000000000000000");
	snprintf((char *)stTransPara.szPosId, sizeof(stTransPara.szPosId), "00000000");
	snprintf((char *)stTransPara.szUnitChnName, sizeof(stTransPara.szUnitChnName), "中国银联测试商户");
	snprintf((char *)stTransPara.szEngName, sizeof(stTransPara.szEngName), "HZR");

	stTransPara.ucKeyMode = KEY_MODE_3DES;
	stTransPara.iMaxTransNum = MAX_TRANS_LOG_NUM;
	stTransPara.ucPosStatus = WORK_STATUS;
	stTransPara.ucBatchUpStatus = NOLOG;
	stTransPara.ucRmbSettStatus = '1';
	stTransPara.ucFrnSettStatus = '1';
	stTransPara.ucKeyIndex = 0;
	stTransPara.bEmvCapkLoaded = app_false;
	stTransPara.bEmvAppLoaded = app_false;
	stTransPara.bQuickPayParaLoaded = app_false;
	stTransPara.bFreePinLoaded = app_false;
	stTransPara.bFreePinBlkListLoaded = app_false;

	stTransPara.swQuickFlag = para_on;
	stTransPara.swBINAFlag = para_off;
	stTransPara.swBINBFlag = para_off;
	stTransPara.swBINCFlag = para_on;		//默认BIN表C是开启的
	stTransPara.swCDCVMFlag = para_on;
	stTransPara.swFreeSignFlag = para_on;
	strcpy((char*)stTransPara.ucMaxFreePinAmt,"000000100000");
	strcpy((char*)stTransPara.ucMaxFreeSignAmt,"000000100000");
	//客户要求6220系列的押金金额为150元，而7220系列为299元
	if(app_get_terminal_info(NULL)->stCap.bSupPrinter == app_false){
		strcpy((char*)stTransPara.ucDepositAmt,"000000015000");
	}
	else{
		strcpy((char*)stTransPara.ucDepositAmt,"000000029900");
	}
	stTransPara.swPreferPassive = para_off;
	stTransPara.swTrackEncrypt = para_off;
	stTransPara.swByPass = para_on;
	stTransPara.swSupElecSign = para_on;

	stTransPara.swVoidPin = para_on;
	stTransPara.swPreVoidPin = para_on;
	stTransPara.swPreComVoidPin = para_on;
	stTransPara.swPreComPin = para_on;

	stTransPara.swVoidSwipe = para_on;
	stTransPara.swPreComVoidSwipe = para_on;
	
	stTransPara.swAutoLogoff = para_on;
	stTransPara.swDetailPrt = para_on;
	
	stTransPara.swManualInput = para_off;
		
	return RET_OK;	
}

int SaveTransPara(void)
{
	return SaveFileComm(TRANS_PARA_FILE, &stTransPara, TRANS_PARA_SIZE);
}

int ReadTransPara(void)
{
	return ReadFileComm(TRANS_PARA_FILE, &stTransPara, TRANS_PARA_SIZE);
}

int LoadTransPara(void)
{
	int iRet = RET_OK;

	if( app_file_exists(TRANS_PARA_FILE) < 0 ){
		iRet = LoadDefaultTransPara();
		if( iRet == RET_OK){
			iRet = SaveTransPara();
		}
	}
	else{
		iRet = ReadTransPara();
	}

	return iRet;	
}

int LoadDefaultTransCtrlPara(void)
{		

	memset(&stTransCtrl,0,sizeof(TRANS_CTRL_PARA_STRC));
	stTransCtrl.lNowTraceNo = 1;
	stTransCtrl.lNowBatchNum = 1;

	stTransCtrl.bClearLog = app_false;
	stTransCtrl.bScriptFlag = app_false;
	stTransCtrl.bReveralFlag = app_false;

	stTransCtrl.iTransNum = 0;
	
	memset(stTransCtrl.sTxnRecIndexList,0,sizeof(stTransCtrl.sTxnRecIndexList));
	memset(stTransCtrl.szLastLogonDate,0,sizeof(stTransCtrl.szLastLogonDate));
	return RET_OK;	
}

int SaveTransCtrlPara(void)
{
	return SaveFileComm(TRANS_CTRL_FILE, &stTransCtrl, TRANS_CTRL_SIZE);
}

int ReadTransCtrlPara(void)
{
	return ReadFileComm(TRANS_CTRL_FILE, &stTransCtrl, TRANS_CTRL_SIZE);
}

int LoadTransCtrlPara(void)
{
	int iRet = 0;
	
	if( app_file_exists(TRANS_CTRL_FILE) < 0 ){
		iRet = LoadDefaultTransCtrlPara();
		if( iRet == RET_OK){
			iRet = SaveTransCtrlPara();
		}
	}
	else{
		iRet = ReadTransCtrlPara();
	}

	return iRet;	
}

void ClearAllTxnUploadNum(void)
{
	int iCnt;
	
	for (iCnt=0; iCnt<MAX_TRANS_LOG_NUM; iCnt++)
	{
		stTransCtrl.sTxnRecIndexList[iCnt] &= 0xFFFFFFF0;
	}
}


void UpdataTxnCtrlStatus(uint32_t uiTxnIndex,uint32_t uiStatus)
{
	if (uiTxnIndex >= MAX_TRANS_LOG_NUM)
	{
		return;
	}

	stTransCtrl.sTxnRecIndexList[uiTxnIndex] = uiStatus;
	SaveTransCtrlPara();
}



