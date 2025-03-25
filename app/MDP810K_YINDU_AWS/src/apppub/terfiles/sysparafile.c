#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfileinter.h"
#include "terfiledef.h"

#define PARAM_DEFAULT_PWD	"00000000"
#define SAFE_DEFAULT_PWD	"888888"

int LoadDefaultSysPara(void)
{
	memset(&stSysPara,0,sizeof(SYS_PARA_STRC));
	
	//stSysPara.bPosLogonFlag = app_false;
	stSysPara.ucOprtLimitTime = 60;
	//snprintf(stSysPara.szParamsPwd, sizeof(stSysPara.szParamsPwd),"%s", PARAM_DEFAULT_PWD);
	//snprintf(stSysPara.szSafepwd, sizeof(stSysPara.szSafepwd),"%s", SAFE_DEFAULT_PWD);

	//stSysPara.iPrnCopyNum = 2;
	//stSysPara.iReverseTime = 3;
	//stSysPara.iResendTime = 3;
	//stSysPara.bRegstFlag = app_false;
	//stSysPara.iElecSignReSendTimes = 1;
	//stSysPara.swPrnEng = para_off;
	//stSysPara.swBeepEnable = para_on;
	
#if SW_SUP_AUDIO
	if(app_get_terminal_info(NULL)->stCap.bSupAudio == app_false){
	//	stSysPara.swVoice = para_off;		
	}
	else{
		//stSysPara.swVoice = para_on;
	}
#else
	stSysPara.swVoice = para_off;	
#endif
	stSysPara.iVolnume = 6;
	stSysPara.volume = 60;

	//stSysPara.bDepositFlag = app_false;
	//stSysPara.swSupScanPreauth = para_off;
	//stSysPara.swSupIcSmAlg = para_off;

	//if(app_support_power_off()==app_false)
	//	stSysPara.swAutoPowerOff = para_off;
	//else
	//	stSysPara.swAutoPowerOff = para_on;
	//stSysPara.iAutoPoweroffTime = 10;

	stSysPara.bUpdateApp = app_false;
	stSysPara.bUpdateAppAbs = app_false;

	return RET_OK;	
}



int SaveSysPara(void)
{
	return SaveFileComm(SYS_PARAM_FILE, &stSysPara, SYS_PARA_SIZE);
}

int ReadSysPara(void)
{
	return ReadFileComm(SYS_PARAM_FILE, &stSysPara, SYS_PARA_SIZE);
}

int LoadSysPara(void)
{
	int iRet = 0;

	if( app_file_exists(SYS_PARAM_FILE) < 0 ){
		iRet = LoadDefaultSysPara();
		if( iRet == RET_OK){
			iRet = SaveSysPara();
		}
	}
	else{
		iRet = ReadSysPara();
	}


	return iRet;	
}

int LoadDefaultCtrlPara(void)
{		
	return 0;	
}



int SaveCtrlPara(void)
{
	return SaveFileComm(CTRL_PARAM_FILE, &stCtrlPara, CTRL_PARA_SIZE);
}

int ReadCtrlPara(void)
{
	return ReadFileComm(CTRL_PARAM_FILE, &stCtrlPara, CTRL_PARA_SIZE);
}

int LoadCtrlPara(void)
{
	int iRet = 0;
	
	if( app_file_exists(CTRL_PARAM_FILE) < 0 ){
		iRet = LoadDefaultCtrlPara();
		if( iRet == RET_OK){
			iRet = SaveCtrlPara();
		}
	}
	else{
		iRet = ReadCtrlPara();
	}

	return iRet;	
}

SYS_PARA_STRC *Get_SysPara(void)
{
	return &stSysPara;
}


