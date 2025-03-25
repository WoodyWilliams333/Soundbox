#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"
#include "terfilecomm.h"




static void GetSslSetting(ST_SSL_PARAM *lpSSlParam)
{
	lpSSlParam->version	= SV_TLS_V1_2;
	lpSSlParam->mode = SVM_VERIFY_SINGLE;
	lpSSlParam->depth = 3;
	lpSSlParam->debug = app_false;
	snprintf((char *)lpSSlParam->ca_cert[0], MAX_FILE_NAME_LEN, 
		"%s/%s", APP_FILE_PATH, "ca.crt");
	strcpy((char *)lpSSlParam->cipher_list, 
		"AES256-SHA:AES128-SHA:DES-CBC3-SHA:AES256-SHA256:AES128-SHA256");
}

static void GetWirelessSetting(ST_WIRELESS_PARAM *lpstWireless,COMM_PARA_STRC stPara)
{
	snprintf((char *)lpstWireless->apn, 
		sizeof(lpstWireless->apn), "%s", (char *)stPara.stWirlessPara.szAPN);
	snprintf((char *)lpstWireless->uid, 
		sizeof(lpstWireless->uid), "%s", (char *)stPara.stWirlessPara.szUID);
	snprintf((char *)lpstWireless->pwd, 
		sizeof(lpstWireless->pwd), "%s", (char *)stPara.stWirlessPara.szPwd);
	snprintf((char *)lpstWireless->sim_pin, 
		sizeof(lpstWireless->sim_pin), "%s", (char *)stPara.stWirlessPara.szSimPin);			
}


static int SetCommParam(void)
{
	ST_WIRELESS_PARAM stWirelessP;
	ST_SSL_PARAM stSslP, *lpSslP = &stSslP;
	appbool bDnsIp = app_false;
	int ret = RET_OK;
	
	// 使用SSL，设置SSL参数
	if(stCommPara.swUsedSsl == para_on ){
		GetSslSetting(lpSslP);				
	}
	else{
		lpSslP = NULL;
	}

	if(stCommPara.swUsedDNS == para_on && stSysTemp.bNeedDns == app_true){
		bDnsIp = app_true;
	}
	
	GetWirelessSetting(&stWirelessP,stCommPara);
	ret = CommParamSet(TRANS_COMM_HANDLE, bDnsIp, &stWirelessP, lpSslP);

	return ret;
}


static int SetCommParamNew(void)
{
	ST_WIRELESS_PARAM stWirelessP;
	ST_SSL_PARAM stSslP, *lpSslP = &stSslP;
	appbool bDnsIp = app_false;
	int ret = RET_OK;
	COMM_PARA_STRC stCommParatmp;	

	
	lpSslP = NULL;
	memset(&stCommParatmp,0,sizeof(COMM_PARA_STRC));

	strcpy((char *)stCommParatmp.stWirlessPara.szAPN, "CMNET");
	strcpy((char *)stCommParatmp.stWirlessPara.szUID, "CARD");
	strcpy((char *)stCommParatmp.stWirlessPara.szPwd, "CARD");


	if(stCommPara.swUsedDNS == para_on && stSysTemp.bNeedDns == app_true){
		bDnsIp = app_true;
	}
	
	GetWirelessSetting(&stWirelessP,stCommParatmp);
	ret = CommParamSet(TRANS_COMM_HANDLE, bDnsIp, &stWirelessP, lpSslP);

	return ret;
}

int PreDial(unsigned char ucConnectFlg)
{
	//#ifdef OFFLINE_DEMO
	//	return RET_OK;
	//#else

	int ret =RET_OK;
	ST_HOST_PARAM stHostPara;
	//appbool bWifiChkSuccess = app_true;

	logger_debug("PreDial 2222...\n");
	//异步预拨号需要连第一个ip
	if (ucConnectFlg) {
		snprintf((char *)stHostPara.name,
			sizeof(stHostPara.name), "%s", (char *)stCommPara.szDNS);
		snprintf((char *)stHostPara.ip_port.ip , sizeof(stHostPara.ip_port.ip), 
						"%s", (char *)stCommPara.stHost[0].szHostIP);
		snprintf((char *)stHostPara.ip_port.port , sizeof(stHostPara.ip_port.port), 
						"%s", (char *)stCommPara.stHost[0].szHostPort);
	}
	do{
		ret = SetCommParam();
		if(ret == RET_OK){
			if (ucConnectFlg) {
				ret = CommPreDial(TRANS_COMM_HANDLE, &stHostPara);
			}
			else {
				ret = CommPreDial(TRANS_COMM_HANDLE, NULL);
			}
		}
	}while(0);		
	return ret;
//#endif	
}


int PreDialNew(unsigned char ucConnectFlg)
{
//#ifdef OFFLINE_DEMO
//	return RET_OK;
//#else

	int ret =RET_OK;
	ST_HOST_PARAM stHostPara;
	//appbool bWifiChkSuccess = app_true;

	//异步预拨号需要连第一个ip
	if (ucConnectFlg) {
		snprintf((char *)stHostPara.name,
			sizeof(stHostPara.name), "%s", (char *)"otatest.newposp.com");
		snprintf((char *)stHostPara.ip_port.ip , sizeof(stHostPara.ip_port.ip), 
						"%s", (char *)"121.15.2.197");
		snprintf((char *)stHostPara.ip_port.port , sizeof(stHostPara.ip_port.port), 
						"%s", (char *)"2012");
	}
	do{
		ret = SetCommParamNew();
		if(ret == RET_OK){
			if (ucConnectFlg) {
				ret = CommPreDial(TRANS_COMM_HANDLE, &stHostPara);
			}
			else {
				ret = CommPreDial(TRANS_COMM_HANDLE, NULL);
			}
		}
	}while(0);		
	return ret;
//#endif	
}








 
