#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"
#include "apppubext.h"

#include "WifiConfig.h"
#include "timecalibrat.h"
#include "appdef.h"

#include "net_work.h"
#include "task_thread.h"
#include "fixaudio.h"


//------------------------------------
int check_dbclick_fn_key(void)
{
	int key1, key2; 
	key1 = app_kb_get_key_ms(200);
	logger_debug("key1=%d\n",key1);
	if(KEY_UP != key1){
		return E_TRANS_CANCEL;
	}else{
		key2 = app_kb_get_key_ms(800);
		logger_debug("key2=%d\n",key2);
		if(KEY_UP == key2){
			return RET_OK;
		}else{
			return E_TRANS_CANCEL;
		}
	}
	
}

/**
 * @brief  ����ģʽ��ͨ��get_if_exit_ap����Ƿ��˳���ǰ����������޸�������״̬���˳�
 * @param[in]   ap ����ģʽ
 * @param[in]   fp �ص����������������д��������߳��еĲ��������쳣
 * @retval ��
 */
int wifi_ap_airkiss_mode(appbool ap, void(* fp)(void))
{
	char SN[50+1];
	char AP_SSID[33] = {0};
	char AP_PWD[65]  = {0};
	int ret = RET_OK;
	ap_mode_info_t ap_info = {0};
	struct timeval start_time = {0,0};
	int connect_stat = E_COMM_CONNECT_CANCEL;
	
	logger_debug("start wifi_ap_airkiss_mode func\n");
	
	gettimeofday(&start_time, NULL); 
	if( wifi_is_open() == app_false){
		ret = wifi_open();
		logger_debug("wifi_open ret=%d\n",ret);
		if(ret == RET_OK){
			while(1){
				logger_debug("check wifi_is_open\n");
				if(wifi_is_open() == app_true){
					break;
				}

				if(pub_check_time_out(&start_time, 20 * 1000)){
					ret = E_COMM_CONNECT_CANCEL;
					break;
				}
				//�ص�����
				if(NULL != fp){
					fp();					
				}
				if(app_true == get_if_exit_ap(ap)){
					ret = E_COMM_CONNECT_CANCEL;
					break;
				}
				sleep(1);
			}
		}	
	}

	if(ret != RET_OK){
		logger_debug("wifi_open failed\n");
		return ret;
	}

	logger_debug("app_read_sn\n");
	if(ap){
		app_read_sn(SN, sizeof(SN));
		snprintf((char*)ap_info.ssid.val, sizeof(ap_info.ssid.val), "%s-%s",NETWORK_HOSTPOINT_NAME,SN);
		ap_info.ssid.len = strlen((char *)ap_info.ssid.val);
		ap_info.channel = 11; //������1-13���̶���11
		ap_info.security_type = WIFI_AUTH_OPEN; //������
		ap_info.password_len = 0;
		ap_info.language = LANG_ENGLISH;
		logger_debug("ap_info.ssid.val=%s\n",ap_info.ssid.val);
	}

	logger_debug("start wifi_ap_mode\n");
	do{
		if(ap){
			logger_debug("before wifi_ap_mode_start\n");
			ret = wifi_ap_mode_start(&ap_info);
			logger_debug("wifi_ap_mode_start=%d\n",ret);
			if(ret != RET_OK){
				break;
			}

			while(1){
				ret = wifi_ap_mode_is_done(AP_SSID,AP_PWD); 
				logger_debug("wifi_ap_mode_is_done=%d AP_SSID=%s AP_PWD=%s\n",ret,AP_SSID,AP_PWD);
				if(ret == 1){	//�������	
					logger_debug("+++ap wifi is ok!!!!!\n");
					ret = RET_OK;
					break;
				}
				//�ص�����
				if(NULL != fp){
					fp();
				}
				if(app_true == get_if_exit_ap(ap)){
					logger_debug("++++get_if_exit_ap\n");
					ret = E_COMM_CONNECT_CANCEL;
					return ret;//���ȵ���������΢������������Ҫ����wifi_ap_mode_stop
					//break;
				}
				app_pos_msleep(400);
			}
			if(ret != RET_OK){
				wifi_ap_mode_stop();//�������������1.6��
				logger_debug("wifi_ap_mode_stop\n");
				break;
			}
			ret = wifi_ap_mode_stop();
			if(ret != RET_OK){
				break;
			}
		}else{
			ret = wifi_airkiss_start();
			logger_debug("wifi_airkiss_start=%d\n",ret);
			if(ret != RET_OK){
				break;
			}

			while(1){
				ret = wifi_airkiss_is_done(AP_SSID, AP_PWD);
				logger_debug("ret=%d AP_SSID=%s AP_PWD=%s\n",ret,AP_SSID,AP_PWD);
				if(ret == 1){	//�������	
					ret = RET_OK;
					break;
				}else if(ret == -1){//����ʧ��
					break;
				}
				//�ص�����
				if(NULL != fp){
					fp();
				}
				if(app_true == get_if_exit_ap(ap)){
					logger_debug("E_COMM_CONNECT_CANCEL\n");
					ret = E_COMM_CONNECT_CANCEL;
					break;
				}
				sleep(1);
			}
			if(ret != RET_OK){
				wifi_airkiss_stop();
				break;
			}

			ret = wifi_airkiss_stop();
			if(ret != RET_OK){
				break;
			}
		}

		if(ap){//�ȵ���������Ҫִ������Ĳ���
			ret = wifi_connect(AP_SSID,AP_PWD);
			logger_debug("wifi_connect=%d\n",ret);
			if(ret != RET_OK){
				break;
			}

			add_play_text(Audio_zhengzailianjiewangluo, NULL, NULL, PLAY_MP3);
			gettimeofday(&start_time, NULL); 
			while(1) {	
				connect_stat = wifi_get_join_status();
				logger_debug("wifi_get_join_status=%d\n",connect_stat);
				if(connect_stat == WIFI_JOIN_CONNECTED){
					ret = RET_OK;
					break;
				}
				if(pub_check_time_out(&start_time, 20 * 1000)){
					add_play_text(Audio_wangluolianjieshibai_qjcwl, NULL, NULL, PLAY_MP3);
					ret = E_COMM_CONNECT_FAILED;
					break;
				}
				//�ص�����
				if(NULL != fp){
					fp();
				}
				if(app_true == get_if_exit_ap(ap)){
					ret = E_COMM_CONNECT_CANCEL;
					break;
				}
				//��ʱ��������̫����Ҫ��Ȼ�����MQTT�Ѳ������ӳɹ������ﻹ��ѭ�������
				app_pos_msleep(200);
			}
		}
	}while(0);
	return ret;
}


