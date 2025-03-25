#include <stdio.h>
#include <system.h>
#include <libwnet.h>
#include <wnet.h>
#include <apperrdef.h>
#include <pahomqtt.h>
#include <appdatatypedef.h>
#include <appwifi.h>
#include <appsys.h>
#include <wnet.h>
#include <time.h>
#include "basicext.h"
#include "appdef.h"
#include "cJSON.h"
#include "tts_play.h"
#include "task_thread.h"
#include "record_store.h"
#include "fixaudio.h"
#include "tts_play.h"
#include "appgprs.h"
#include "logger.h"
#include <sys/vfs.h>
#include <net_work.h>
#include <wnet.h>
#include <semaphore.h>
#include "mqtt_timer.h"
#include "syspara.h"
#include "tersharedata.h"
#include "pahomqtt.h"
#include "mqtt_payload_func.h"
#include "aiot_mqtt.h"
#include "ota_http_upgrade.h"
#include "codestool.h"



Tts_Data_UNION g_tts_data;


extern  int pase_biztype_F(cJSON*root);

static int pase_biztype_D(cJSON*root)
{
	cJSON*psub = NULL;
	cJSON*para_inf = NULL;
	cJSON*mcht_name = NULL;
	logger_debug("start pase_biztype_D\r\n");
	if(NULL == root){
		return -1;
	}
	add_play_text(AudioZhenzsjrj,NULL,NULL,PLAY_MP3);
	psub = cJSON_GetObjectItem(root, "para_inf");
	//if ((NULL==para_inf)||(para_inf->type!=cJSON_String))
	if ((NULL==psub)||(psub->type!=cJSON_Array)){
		return -1;
	}else{
		if(cJSON_GetArraySize(psub) > 0){
			para_inf = cJSON_GetArrayItem(psub,0);
			if (NULL==para_inf){
				return -1;
			}else{
				mcht_name = cJSON_GetObjectItem(para_inf,"mcht_name");
				if ((NULL==mcht_name)||(mcht_name->type!=cJSON_String)){
					return -1;
				}else{
					memset(Get_SysPara()->mer_name, 0, sizeof(Get_SysPara()->mer_name));
					snprintf(Get_SysPara()->mer_name, sizeof(Get_SysPara()->mer_name), "%s", mcht_name->valuestring);
					logger_debug("mer_name = %s\r\n", Get_SysPara()->mer_name);

					add_play_text(AudioShenjcg,NULL,NULL,PLAY_MP3);
					add_play_text(Get_SysPara()->mer_name,NULL,NULL,PLAY_MP3);
					SaveSysPara();
					return 0;
				}
			}
		}else{
			return -1;
		}
	}
	return -1;
}



int PrcTranVoice(cJSON* pRoot)
{
	cJSON*psub = NULL;
	char audiotmpbuf[150] = {0};//,play_buf[500] = {0};
	int ret = -1,bcType=0;
	char aMomt[50] = {0},aMomt_tmp[50] = {0};
	int tiki_time = 0,sub_time = 0;
	char timestamp[36] = {0};
	
	//数字人民币收款 uft-8编码
	const char shuzirenminbi[] = {0xE6,0x95,0xB0,0xE5,0xAD,0x97,0xE4,0xBA,0xBA,0xE6,0xB0,0x91,0xE5,0xB8,0x81,0xE6,0x94,0xB6,0xE6,0xAC,0xBE,0x00};

	if(NULL==pRoot)
		return -1;

	psub = cJSON_GetObjectItem(pRoot,"request_id");
	if ((NULL==psub)||(psub->type!=cJSON_String))
		goto EXIT;
	memcpy(g_tts_data.request_id, psub->valuestring, strlen(psub->valuestring)+1);

	psub=cJSON_GetObjectItem(pRoot,"broadcast_type");
	if ((NULL==psub)||(psub->type!=cJSON_String))
		goto EXIT;
	sscanf(psub->valuestring, "%d\r\n", &bcType);

	psub=cJSON_GetObjectItem(pRoot,"money");
	if ((NULL==psub)||(psub->type!=cJSON_String))
		goto EXIT;
	strcpy(aMomt,psub->valuestring);

	psub=cJSON_GetObjectItem(pRoot,"time_stamp");//超过十分钟的消息不再播报
	if(psub != NULL && psub->type == cJSON_String){
		get_timestamp(TIME_STAMP_TYPE_SEC, timestamp, sizeof(timestamp));
		sub_time = atol(timestamp);
		logger_debug("sub_time=%ld\n",sub_time);
		tiki_time = atol(psub->valuestring);
		logger_debug("tiki_time=%ld\n",tiki_time);
		logger_debug("sub_time - tiki_time = %d \n",sub_time - tiki_time);
		if(sub_time > tiki_time && (sub_time - tiki_time) > AUDIO_PLAY_TIMEOUT_MS){//后台返回时间戳是秒
			logger_debug("play audio timeout \n");
			//goto EXIT;
		}		
	}

	psub=cJSON_GetObjectItem(pRoot,"tts");//兼容威富通推送协议

	if(strlen(aMomt) == 0 && (psub != NULL && psub->type == cJSON_String)){
		g_tts_data.condingFlag = PLAY_TTS;
		logger_debug("tts = %s\n", psub->valuestring);

		snprintf(g_tts_data.tts_playdata, sizeof(g_tts_data.tts_playdata), "%s", psub->valuestring);
		//strcpy(g_tts_data.tts_playdata, psub->valuestring);
		GetTtsStrAudioAmt(g_tts_data.tts_playdata,aMomt,audiotmpbuf);

		if(strlen(aMomt) >= 3 && strcmp(&aMomt[strlen(aMomt)-3],".00") == 0){//去掉.00的读音
			strncpy(aMomt_tmp,aMomt,strlen(aMomt)-3);
			strRepl(g_tts_data.tts_playdata,aMomt,aMomt_tmp);
		}				
		if(strcmp(shuzirenminbi,audiotmpbuf) == 0){//数字人民币通过tts推送 特殊处理
			strcpy(g_tts_data.tts_playdata,"数字人民币收款");
			g_tts_data.condingFlag = PLAY_MP3_AMOUNT;
			snprintf(g_tts_data.money,sizeof(g_tts_data.money)-1,"%s",aMomt);
		}else{
			snprintf(g_tts_data.money,sizeof(g_tts_data.money)-1,"%s",aMomt);
		}
		logger_debug("aMomt=%s, audiotmpbuf=%s\n",aMomt,audiotmpbuf);
	}else{

		switch(bcType){
			case 1:
				strcpy(g_tts_data.tts_playdata,Audio_chenggong_shoukuan);
				break;

			case 2:
				strcpy(g_tts_data.tts_playdata,Audio_zhifubao_shoukuan);
				break;

			case 3:
				strcpy(g_tts_data.tts_playdata,Audio_weixin_shoukuan);
				break;

			case 4:
				strcpy(g_tts_data.tts_playdata,Audio_quxiaozhifu);
				break;

			case 5:
				strcpy(g_tts_data.tts_playdata,Audio_yunshanfu_shoukuan);
				break;

			case 6:
				strcpy(g_tts_data.tts_playdata,Audio_shuzirenminbi_shoukuan);
				break;

			default:
				strcpy(g_tts_data.tts_playdata,Audio_chenggong_shoukuan);
				break;
		}
		g_tts_data.condingFlag = PLAY_MP3_AMOUNT;
		snprintf(g_tts_data.money,sizeof(g_tts_data.money)-1,"%s",aMomt);		
	}
	ret=0;
	EXIT:
		return ret;
}


int PrcGetInfo(cJSON* pRoot)
{
	
	return 0;
}

int PrcDoEncrypt(cJSON* pRoot)
{
	
	return 0;
}	

int PrcDoDecrypt(cJSON* pRoot)
{
	
	return 0;
}




int PrcDownVoice(cJSON* pRoot)
{
	return pase_biztype_F(pRoot);
}

int MqttPayloadRroc(uint8_t *type,cJSON* pRoot)
{
	int ret=-1;
	char request_id[50]={0};
	cJSON*psub = NULL;

	logger_debug("+++MqttPayloadRroc type=%s\n",type);

	psub = cJSON_GetObjectItem(pRoot,"request_id");
	if ( NULL != psub && psub->type == cJSON_String )
	{
		snprintf(request_id,sizeof(request_id),"%s",psub->valuestring);
	}
		
	if(0==strcmp(BIZ_TYPE_TRANS_VOICE,(char*)type)){
		memset(&g_tts_data, 0, sizeof(Tts_Data_UNION));
		ret=PrcTranVoice(pRoot);
		if(0==ret && 0 == record_compare_msgid(g_tts_data.request_id) && 0 == record_compare_mqttack_msgid(g_tts_data.request_id)){
			get_timestamp(TIME_STAMP_TYPE_MSEC, g_tts_data.rst_time, sizeof(g_tts_data.rst_time));
			add_play_text(g_tts_data.tts_playdata, g_tts_data.money, NULL, g_tts_data.condingFlag);
			record_manage_write(g_tts_data.request_id, g_tts_data.tts_playdata, g_tts_data.money, g_tts_data.condingFlag, g_tts_data.rst_time, RECORD_PLAY_YES);
			stSysTemp.bSaveRecord = app_true;
			stSysPara.record_num++;//关机前保存文件，这里不用保存
			SaveSysPara();
			
		}else{
			logger_debug("same request id = %s\n", g_tts_data.request_id);
		}
	}
	else if(0==strcmp(BIZ_TYPE_GET_INFO,(char*)type))
		ret=PrcGetInfo(pRoot);
	else if(0==strcmp(BIZ_TYPE_DO_ENCRYPTION,(char*)type))
		ret=PrcDoEncrypt(pRoot);
	else if(0==strcmp(BIZ_TYPE_DO_DECRYPTION,(char*)type))
		ret=PrcDoDecrypt(pRoot);
	else if(0==strcmp(BIZ_TYPE_SET_PARAM,(char*)type))
		ret = pase_biztype_D(pRoot);
	else if(0==strcmp(BIZ_TYPE_DOWN_VOICE,(char*)type))
		ret=PrcDownVoice(pRoot);

	
	if(0 != strcmp(BIZ_TYPE_DOWN_VOICE,(char*)type)){
		if(ret == 0){
			send_param_update_stat(request_id,(char*)type,"1"); //succ:1, failed:0
		}else{
			send_param_update_stat(request_id,(char*)type,"0"); //succ:1, failed:0
		}
	}
	
	return ret;
}

Tts_Data_UNION *get_mqtt_union(void)
{
	return &g_tts_data;
}



