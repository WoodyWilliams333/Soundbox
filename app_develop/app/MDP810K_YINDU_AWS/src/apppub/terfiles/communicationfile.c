#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfileinter.h"
#include "terfiledef.h"

int LoadDefaultCommunicationPara(void)
{
#ifdef CFG_4G_FLAG
	int iRet = -1;
	char tmp[128] = {0};
	char *chr = NULL;
#endif

	memset(&stCommPara,0,sizeof(COMM_PARA_STRC));
	
	stCommPara.commType = CT_GPRS;
	memcpy(stCommPara.ucTpdu, "\x60\x02\x01\x00\x00", 5);
	
	strcpy((char *)stCommPara.stHost[0].szHostIP,  "114.80.86.73");
	strcpy((char *)stCommPara.stHost[0].szHostPort, "1125");
	strcpy((char *)stCommPara.stHost[1].szHostIP,  "114.80.86.73");
	strcpy((char *)stCommPara.stHost[1].szHostPort, "1125");
	
	stCommPara.swPreDial = para_on;
	stCommPara.swUsedHttps = para_off;
	stCommPara.swUsedSsl = para_off;
	stCommPara.swUsedDNS = para_off;

	stCommPara.swLongConnection = para_off;
	stCommPara.ucCommWaitTime = 60;
	stCommPara.ucDialRetryTimes = 3;

#ifdef CFG_4G_FLAG	
	iRet = app_get_vsim_apn(tmp); //VSIM卡APN的获取 210702
	if(iRet == 0){
		chr = strchr(tmp,':');//配置文件的格式是ICCID:apn
		if(chr){
			snprintf((char *)stCommPara.stWirlessPara.szAPN,
				sizeof(stCommPara.stWirlessPara.szAPN),"%s",chr+1);
			logger_debug("szAPN=%s\n",stCommPara.stWirlessPara.szAPN);
		}else{
			strcpy((char *)stCommPara.stWirlessPara.szAPN, "CMIOT");
		}
	}else{
		strcpy((char *)stCommPara.stWirlessPara.szAPN, "CMIOT");
	}
	strcpy((char *)stCommPara.stWirlessPara.szUID, "");
	strcpy((char *)stCommPara.stWirlessPara.szPwd, "");
#else	
	strcpy((char *)stCommPara.stWirlessPara.szAPN, "CMNET");
	strcpy((char *)stCommPara.stWirlessPara.szUID, "CARD");
	strcpy((char *)stCommPara.stWirlessPara.szPwd, "CARD");
#endif	
	strcpy((char *)stCommPara.szDialNum, "*99***1#");

	strcpy((char *)stCommPara.szDNS, "vpn.newpostech.cn");

	return 0;	
}



int SaveCommunicationPara(void)
{
	return SaveFileComm(COMM_PARAM_FILE, &stCommPara, COMM_PARA_SIZE);
}

int ReadCommunicationPara(void)
{
	return ReadFileComm(COMM_PARAM_FILE, &stCommPara, COMM_PARA_SIZE);
}

int LoadCommunicationPara(void)
{
	int iRet = 0;

	if( app_file_exists(COMM_PARAM_FILE) < 0 ){
		iRet = LoadDefaultCommunicationPara();
		if( iRet == RET_OK){
			iRet = SaveCommunicationPara();
		}
	}
	else{
		iRet = ReadCommunicationPara();
	}

	//printfCommPara();
	
	return iRet;	
}




