#include <stdio.h>
#include <string.h>
#include "basicext.h"
#include <os_pthread.h>
#include "tts_play.h"
#include "net_work.h"
#include "task_thread.h"
#include "fixaudio.h"
#include "communication.h"
#include "appdef.h"
#include "led.h"
#include "appled.h"
#include <semaphore.h>
#include "WifiConfig.h"
#include "aiot_mqtt.h"
#include "appgprs.h"
#include "pahomqtt.h"
#include "apperrdef.h"
#include "tersharedata.h"
#include "np_led.h"

extern char pub_check_time_out(struct timeval* timer, int timeout);

void* thread_net_run(void* args) __attribute__((noreturn));
static struct timeval start_net_sem_tick = {0,0};
static sem_handle_t g_net_Sem;
static appbool gcheckstate = app_false;
static int wnet_checksim_result = -1;
int CheckWirelessStatus(appbool bWait)
{
	int ret = RET_OK;
	struct timeval starttick = {0,0};
	static appbool bChkSimCardFlg = app_true;

	gettimeofday(&starttick, NULL);
	while (app_wireless_check_simcard() != 0) {
		if (!bWait || bChkSimCardFlg == app_false || pub_check_time_out(&starttick, stSysTemp.iChkSimTimeout*1000)) {
			bChkSimCardFlg = app_false;
			ret = E_COMM_NO_SIM;
			break;
		}
		if(app_true == get_if_exit_check()){
			ret = E_TRANS_CANCEL;
			break;
		}
		app_pos_msleep(100);
	}
	return ret;
}

int online_proc_wnet_callback(int event, int result)
{
	wnet_checksim_result = result;
	return 0;
}

wnet_register(CHECK_SIM_EVENT, online_proc_wnet_callback);


static int CheckWifiStatus(int timeout, appbool bWait)
{
	int ret = RET_OK;
	char Ip[15+1] = {0};
	struct timeval starttick = {0,0};
	
	if(WifiChanl_AP == stSysTemp.ap_or_airkiss || WifiChanl_AIR == stSysTemp.ap_or_airkiss ){
		return E_COMM_GET_IP;//��������ģʽ����Ҫȥ�������
	}
	if(!bWait){
		if(app_wifi_is_connected() != app_true || app_wifi_get_localip(Ip) != RET_OK
			|| strcmp(Ip,"0.0.0.0")==0){
			ret = E_COMM_GET_IP;
		}
		return ret;
	}
	
	gettimeofday(&starttick, NULL);
	while(1){
		if(pub_check_time_out(&starttick, timeout*1000)){
			ret = E_COMM_GET_IP;
			break;
		}
		if(app_wifi_is_connected() == app_true){
			if(app_wifi_get_localip(Ip) == RET_OK){
				if(strcmp(Ip,"0.0.0.0")){
					ret = RET_OK;
					logger_debug("local ip: %s\n", Ip);
					break;
				}
			}
		}
		if(app_true == get_if_exit_check()){
			ret = E_TRANS_CANCEL;
			break;
		}
		app_pos_msleep(200);//100ms�ĳ�200ms,������ʱ̫��
	}

	return ret;
}

int CheckCommStatus(CommType_e commType, appbool bWait)
{
	int ret = RET_OK;
	
	//ͨѶ��ʽ���
	if(commType == CT_GPRS){
		ret = CheckWirelessStatus(bWait);
	}
	else if(commType == CT_WIFI){
		ret = CheckWifiStatus(stSysPara.ucOprtLimitTime, bWait);
	}

	return ret;
}

/**
 * @brief  ��鲢��������״̬
 * @retval ��
 */
int chk_net_play_status(appbool bNeedPlay, appbool bWait)
{
	int ret = RET_OK;
	logger_debug("stCommPara.commType = %X\n",stCommPara.commType);
	do{
		if(CT_WIFI==stCommPara.commType && stSysTemp.bPlayConnecting){
			if(bNeedPlay){
				add_play_text(Audio_zhengzailianjiewangluo, NULL, NULL, PLAY_MP3);
				//add_play_text(Audio_qingshaohou, NULL, NULL, PLAY_MP3);
			}
			stSysTemp.bPlayConnecting = app_false;
			app_set_led(LED_GREEN, LED_FAST_MODE);
					}
		logger_debug("before CheckCommStatus\n");
		ret = CheckCommStatus(stCommPara.commType, bWait);
		logger_debug("CheckCommStatus ret = %X\n",ret);
		if(ret == E_TRANS_CANCEL){
			break;
		}else if(E_COMM_NO_SIM == ret && CT_WIFI!=stCommPara.commType){
			if(bNeedPlay){
		    	add_play_text(Audio_weijiancedaoSIMka, NULL, NULL, PLAY_MP3);
				//add_play_text(Audio_QingChaRuSIMKa, NULL, NULL, PLAY_TTS);
				//add_play_text(Audio_ChongQiSheBei, NULL, NULL, PLAY_TTS);
			}
			app_set_led(LED_RED, LED_FAST_MODE);
			break;
	    }else if(RET_OK != ret){
			if(bNeedPlay){
				add_play_text(Audio_wangluolianjieshibai_qjcwl, NULL, NULL, PLAY_MP3);
				stSysTemp.bPlayConnected  = app_true;//����playmqttstatus����
				set_server_play_status(app_true);//���ڲ������������ӳɹ�
			}
			app_set_led(LED_GREEN, LED_FAST_MODE);
			break;
		}
		if(CT_GPRS==stCommPara.commType && stSysTemp.bPlayConnecting){
			if(bNeedPlay){
				add_play_text(Audio_zhengzailianjiewangluo, NULL, NULL, PLAY_MP3);
				//add_play_text(Audio_qingshaohou, NULL, NULL, PLAY_MP3);
			}
			stSysTemp.bPlayConnecting = app_false;
			app_set_led(LED_GREEN, LED_FAST_MODE);
		}
		//ret = CommChkPredial(TRANS_COMM_HANDLE, bWait);//adjust
		ret = CommChkPredial(TRANS_COMM_HANDLE);//adjust
		logger_debug("CommChkPredial=%d\n",ret);
		if( ret != RET_OK && ret != E_TRANS_CANCEL && bWait){
			PreDial(FALSE);
			//ret = CommChkPredial(TRANS_COMM_HANDLE, bWait);
			ret = CommChkPredial(TRANS_COMM_HANDLE);
			logger_debug("CommChkPredial=%d\n",ret);
		}
		if(ret == E_TRANS_CANCEL){
			break;
		}else if(RET_OK == ret){
			if(bNeedPlay && stSysTemp.bPlayConnected){
				add_play_text(Audio_wangluolianjiechenggong, NULL, NULL, PLAY_MP3);
				stSysTemp.bPlayConnected = app_false;
				set_server_play_status(app_true);//���ڲ������������ӳɹ�
			}

			if(app_true == get_matt_connect_state()){
				setLedStatus(TERM_SERVER_OK);
			}else{
				app_set_led(LED_GREEN, LED_SLOW_MODE);
			}
	
		}else if(RET_OK != ret){
			if(bNeedPlay){
		    	add_play_text(Audio_wangluolianjieshibai_qjcwl, NULL, NULL, PLAY_MP3);
				stSysTemp.bPlayConnected  = app_true;
				set_server_play_status(app_true);//���ڲ������������ӳɹ�
			}
			app_set_led(LED_GREEN, LED_FAST_MODE);
		}
	}while(0);
	return ret;
}

static struct timeval start_net_tick = {0,0};
appbool enable_play_net_err(void)
{
    logger_debug("%s\n", __FUNCTION__);
    if(0 == start_net_tick.tv_sec){
       gettimeofday(&start_net_tick, NULL);
       return app_true;
    }else{
        if(pub_check_time_out(&start_net_tick, CHK_NETWORK_ERROR_TIME * 1000)){
            gettimeofday(&start_net_tick, NULL);
            return app_true;  
        }
        return app_false;
    }
}

static void set_check_net_start_tick(void)
{        
	gettimeofday(&start_net_tick, NULL);
}

/**
 * @brief  ��ʱ�������״̬����������ע��ص�
 * @retval ��
 */
void chk_net_status(void)
{	
	if(app_true == enable_play_net_err()){
		//����ģʽ���ӵ�ǰģʽ����ֹ��ʱ��δ���ã���֪����ʲô
		//��������ģʽ���ü������
		if(WifiChanl_AP == stSysTemp.ap_or_airkiss){//������ȵ�����     
			add_play_text(Audio_wangluolianjieshibai_qjcwl, NULL, NULL, PLAY_MP3);
			add_play_text(Audio_xianzaishiWiFiAPpeiwangms, NULL,NULL, PLAY_MP3);
		}else{
			chk_net_play_status(app_true, app_false);			
		}
	}
}
/**
 * @brief  4G��wifi��wifi��4g������ģʽ�������״̬֮ǰ����fasle�����а��������л���������л�����ģʽ����true���˳������������״̬
 * @retval ��
 */
void set_net_check_state(appbool state)
{
	logger_debug("state = %d\n", state); 
	gcheckstate = state;
}
/**
 * @brief  ��������Ѳ���߳�����ģʽ�������л�ģʽ�����̰߳������ƣ�
 * @param[in]   type  �����̲߳���ģʽ
 * @retval ��
 */
void set_wifi_ap_airkiss_type(int type)
{
	logger_debug("type = %d\n", type); 
	
	if(WifiChanl_AP == type || WifiChanl_AIR == type || NET_WIFI_2_4G == type || NET_4G_2_WIFI == type || NET_CHECK_STATE == type){
		stSysTemp.ap_or_airkiss = type;
		os_put_sem(g_net_Sem);//�����ź���������thread_net_run�����������û��л�
		if(NET_CHECK_STATE != type){
			set_net_check_state(app_true);
		}
		
	}else if(WifiChanl_NON == type){
		logger_debug("NET_AP_MODE == NET_NO\n"); 
		stSysTemp.ap_or_airkiss = type;
	}
	
}


/**
 * @brief  ����Ƿ��˳���ǰ����״̬���
 * @retval ��
 */
appbool get_if_exit_check(void)
{ 
	return gcheckstate;
}
/**
 * @brief  ����Ƿ��˳���ǰ����ģʽ
 * @param[in]   ap_or_air    ��ǰ����ģʽ app_true �ȵ������� app_false΢������
 * @retval ��
 */
appbool get_if_exit_ap(appbool ap_or_air)
{
	logger_debug("ap_or_air = %d\n", ap_or_air);  
	logger_debug("stSysTemp.ap_or_airkiss = %d\n", stSysTemp.ap_or_airkiss); 
	if(app_true == ap_or_air){//��ǰ���ȵ�����
		if(WifiChanl_AP != stSysTemp.ap_or_airkiss){
			return app_true;
		}
	}else{//��ǰ��΢������
		if(WifiChanl_AIR != stSysTemp.ap_or_airkiss){
			return app_true;
		}
	}

	return app_false;
}

void put_net_sem(void){
	logger_debug("+++put_net_sem\n"); 
	os_put_sem(g_net_Sem);
}

static int task_net_thread = 0; 
pthread_attr_t task_net_thread_attr;
/**
 * @brief  ѭ������mqtt�������ݣ�mqtt���������ڶ�����
 *         ���������е�buf��Ҫ�ͷ�free�����нڵ�Ҳ��Ҫ�ͷ�free
 * @retval void
 */
void* thread_net_run(void* args)    
{   
	int ret;
	
    logger_debug("%s\n", __FUNCTION__);  
    while(1)    
    {    
		logger_debug("stSysTemp.ap_or_airkiss = %d\n", stSysTemp.ap_or_airkiss); 
		if(WifiChanl_AP == stSysTemp.ap_or_airkiss){//���������
			clear_task_queue();//�л��������������²������У�����ж����������᲻֪����ǰ��ʲô           
			add_play_text(Audio_xianzaishiWiFiAPpeiwangms, NULL,NULL, PLAY_MP3);
			//add_play_text(Audio_shuangjignjqhzWiFi_APpwms,NULL,NULL, PLAY_MP3);
			//app_set_led(LED_CHARGE, LED_FAST_MODE);
			set_check_net_start_tick();
			logger_debug("it is wifi ap mode\n");
			ret = wifi_ap_airkiss_mode(app_true, chk_net_status);
			logger_debug("ret = %d\n", ret);
			//���ÿ�ʼ�����飬��Ϊ����������ͨ�������˳�set_net_check_state
			//�˳�������֮ǰ��Ӧ�İ������
			set_net_check_state(app_false);
			if(ret == RET_OK){
				//"������������"�����ȵ��ʱ�򲥱�
				stSysTemp.bPlayConnecting = app_false;
				stSysTemp.bPlayConnected  = app_true;
				stSysTemp.ap_or_airkiss = WifiChanl_NON;	
				chk_net_play_status(app_true, app_true); //�������״̬
			}else if(WifiChanl_NON == stSysTemp.ap_or_airkiss){ //�ȵ�����ģʽ�¿��ܰ���Դ���˳��������˳���Ҫ����wifi
				//add_play_text(Audio_shuangjignjqhzWiFi_APpwms, NULL,NULL, PLAY_MP3);
				app_wifi_close();
				app_pos_msleep(100);
				app_wifi_open(stSysPara.ucOprtLimitTime, app_false);
				logger_debug("app_wifi_open\n");
				stSysTemp.bPlayConnecting = app_true;
				stSysTemp.bPlayConnected  = app_true;	
				chk_net_play_status(app_true, app_true); //�������״̬
			}
			reconnect_mqtt();
			if(WifiChanl_AP == stSysTemp.ap_or_airkiss){//���߳�ͨ�������������޸ĵ�ǰģʽ�������һ��
				stSysTemp.ap_or_airkiss = WifiChanl_NON;
			}
		}else if(WifiChanl_AIR == stSysTemp.ap_or_airkiss){//���������
			//disconnect_mqtt(0);
			clear_task_queue();//�л��������������²������У�����ж����������᲻֪����ǰ��ʲô
            add_play_text(Audio_Xianzswifiwxpwms,NULL,NULL, PLAY_TTS);
			//app_set_led(LED_CHARGE, LED_FAST_MODE);
			set_check_net_start_tick();
			logger_debug("it is wifi air mode\n");
			ret = wifi_ap_airkiss_mode(app_false, chk_net_status);
			//���ÿ�ʼ�����飬��Ϊ����������ͨ�������˳�set_net_check_state
			//�˳�������֮ǰ��Ӧ�İ������
			set_net_check_state(app_false);	
			logger_debug("wifi_ap_airkiss_mode ret = %d\n", ret);	
			if(ret == RET_OK){
				stSysTemp.bPlayConnecting = app_false;
				stSysTemp.bPlayConnected  = app_true;
				stSysTemp.ap_or_airkiss = WifiChanl_NON;
	
				chk_net_play_status(app_true, app_true); //�������״̬
			}else{ //΢����������ʲô���������˳�֮����Ҫ wifi close��open
				if(NET_WIFI_2_4G != stSysTemp.ap_or_airkiss){
					app_wifi_close();
					app_pos_msleep(100);
					app_wifi_open(stSysPara.ucOprtLimitTime, app_false);
					logger_debug("app_wifi_open\n");
					stSysTemp.bPlayConnecting = app_true;
					stSysTemp.bPlayConnected  = app_true;	
					chk_net_play_status(app_true, app_true); //�������״̬
				}
			}
			
			reconnect_mqtt();
			if(WifiChanl_AIR == stSysTemp.ap_or_airkiss){
				stSysTemp.ap_or_airkiss = WifiChanl_NON;
			}
		}else if(NET_WIFI_2_4G == stSysTemp.ap_or_airkiss){//wif�л���4G
			//����֮ǰ �ȷ�mqtt�Ͽ�
			//disconnect_mqtt(0);
			clear_task_queue();//�л��������������²������У�����ж����������᲻֪����ǰ��ʲô
			add_play_text(Audio_xianzaishi4Gwangluomoshi,NULL,NULL, PLAY_MP3);
			stCommPara.commType = CT_GPRS;//�����ļ��ĵ��ػ�ǰ
			SaveCommunicationPara();//����
			switch_Wifi4g_model(stCommPara.commType);
			stSysTemp.ap_or_airkiss = WifiChanl_NON;
			stSysTemp.bPlayConnecting = app_true;
			stSysTemp.bPlayConnected  = app_true;
			set_net_check_state(app_false);
			chk_net_play_status(app_true, app_true); //�������״̬
			//�����豸��Ϣ,�������ͱ�ǣ�Ҫ�������л������ɹ�ʱ����
			reconnect_mqtt();
#ifdef UPLOAD_DEV_INFO
			set_upload_matt_info_type(app_true);
#endif			
			if(NET_WIFI_2_4G == stSysTemp.ap_or_airkiss){
				stSysTemp.ap_or_airkiss = WifiChanl_NON;
			}
		}else if(NET_4G_2_WIFI == stSysTemp.ap_or_airkiss){//4G�л���wif 
			//����֮ǰ �ȷ�mqtt�Ͽ�
			//disconnect_mqtt(0);
			clear_task_queue();//�л��������������²������У�����ж����������᲻֪����ǰ��ʲô
			add_play_text(Audio_xianzaishiWiFiwangluomoshi, NULL, NULL, PLAY_MP3);
            //add_play_text(Audio_shuangjignjqhzWiFi_APpwms, NULL, NULL, PLAY_MP3);
			stCommPara.commType = CT_WIFI;//�����ļ��ĵ��ػ�ǰ
			SaveCommunicationPara();//����
			switch_Wifi4g_model(stCommPara.commType);        
            stSysTemp.ap_or_airkiss = WifiChanl_NON;
			stSysTemp.bPlayConnecting = app_true;
			stSysTemp.bPlayConnected  = app_true;
			set_net_check_state(app_false);
			chk_net_play_status(app_true, app_true); //�������״̬ 
			reconnect_mqtt();
			//�����豸��Ϣ,�������ͱ�ǣ�Ҫ�������л��������ɹ�ʱ����
#ifdef UPLOAD_DEV_INFO
			set_upload_matt_info_type(app_true);
#endif
			if(NET_4G_2_WIFI == stSysTemp.ap_or_airkiss){//
				stSysTemp.ap_or_airkiss = WifiChanl_NON;
			}
			logger_debug("stSysTemp.ap_or_airkiss=%d\n",stSysTemp.ap_or_airkiss);
		}else{
        	chk_net_play_status(app_true, app_true);
		}
		logger_debug("%s\n", __FUNCTION__);  
#ifdef UPLOAD_DEV_INFO
		//�������ӳɹ���,�������ӳɹ������豸��Ϣ
		if(app_true == get_upload_matt_info_type() && app_true == get_matt_connect_state()){
			wait_play_timeout(10*1000);
			send_hardware_info(NULL, NULL);
			set_upload_matt_info_type(app_false);
		}
#endif
		gettimeofday(&start_net_sem_tick, NULL);
		os_get_sem(g_net_Sem, CHK_NETWORK_TIME * 1000);//��ȡ�ź�������ʱʱ��TIMEOUT_NET
		logger_debug("%s os_get_sem\n", __FUNCTION__);                                                   
    }    
} 
int check_get_sem_timeout(void)
{
	struct timeval tick = {0,0};

	gettimeofday(&tick, NULL);
	logger_debug("tick.tv_sec = %d\n", tick.tv_sec);
	logger_debug("start_net_sem_tick.tv_sec = %d\n", start_net_sem_tick.tv_sec);
	return (tick.tv_sec - start_net_sem_tick.tv_sec);
}
/**
 * @brief  ��ʼ����Ϣ���У��̣߳��ź���
 * @retval void
 */
void init_net_task(void)
{
    logger_debug("%s\n", __FUNCTION__);

	g_net_Sem = os_create_sem("check_net_sem", 0);
    pthread_attr_init(&task_net_thread_attr);
    task_net_thread_attr.detachstate = PTHREAD_CREATE_DETACHED;
	task_net_thread_attr.stacksize = 32*1024;
    pthread_create((pthread_t*)&task_net_thread, &task_net_thread_attr, thread_net_run, NULL);
}

/**
 * @brief  wifi/4g�л�
 * @param [in] model �л�Ŀ��CT_WIFI��ʾ��4g�л���wifi��CT_GPRS��wifi�л���4g
 * @retval void
 */
void switch_Wifi4g_model(int model)
{
	CommModuleExit();
    if(stSysPara.swTransSsl == para_off){
		CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_TCP);
	}
	else{
		CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_SSL);
	}

	if(CT_GPRS == model){
        app_wifi_close();
	}
	PreDial(FALSE);
}

/**
 * @brief ��������
 * @param[in] root ������json
 * @return void 
 */
void net_reboot(void)
{
	logger_debug("%s\n", __FUNCTION__);

	if(CT_WIFI==stCommPara.commType){
		app_set_auto_powersave_mode(app_off);
		app_wifi_close();
		app_pos_msleep(100);
		app_wifi_open(stSysPara.ucOprtLimitTime, app_false);
		app_set_auto_powersave_mode(app_on);
		logger_debug("app_wifi_open reboot\n");
	}else{
		CommModuleExit();
		if(stSysPara.swTransSsl == para_off){
			CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_TCP);
		}else{
			CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_SSL);
		}
		PreDial(FALSE);
		logger_debug("gprs reboot\n");
	}
}

int app_lte_get_network_signal(int *puiSignal, int *rsrp_sinr)
{
	const int rsrpRangeCustz[]  = {-140, -128, -118, -108, -98, -88, -44};  /* rsrp Range Customize �Զ���4G�źŷ�Χ */
	const int sinrRangeCustz[]  = {30, 110, 130, 160, 260, 300};            /* sinr Range Customize �Զ���4G�źŷ�Χ */
	WnetSigStr_t strength;
	int iRet,rsrpLevel = -1,sinrLevel=-1;
	
	*puiSignal = *rsrp_sinr = 0;
	iRet = wnet_get_lte_signal(&strength);
	logger_debug("wnet_get_lte_signal=%d errno=%d\n",iRet,errno);
	if(iRet){
		return -1;
	}

	logger_debug("wnet mode=%d\n",strength.mode);
	if(strength.mode == Mode_LTE){
		if (strength.wss.sLte.rsrp < rsrpRangeCustz[0] || strength.wss.sLte.rsrp > rsrpRangeCustz[6]) {
            rsrpLevel = -1;
        } else if (strength.wss.sLte.rsrp >= rsrpRangeCustz[5]) {
            rsrpLevel = 5;
        } else if (strength.wss.sLte.rsrp >= rsrpRangeCustz[4]) {
            rsrpLevel = 4;
        } else if (strength.wss.sLte.rsrp >= rsrpRangeCustz[3]) {
            rsrpLevel = 3;
        } else if (strength.wss.sLte.rsrp >= rsrpRangeCustz[2]) {
            rsrpLevel = 2;
        } else if (strength.wss.sLte.rsrp >= rsrpRangeCustz[1]) {
            rsrpLevel = 1;
        } else {
            rsrpLevel = 0;
        }
		*puiSignal = rsrpLevel;
		*rsrp_sinr = strength.wss.sLte.rsrp;

		if (-1 == rsrpLevel) {
            if (strength.wss.sLte.sinr > sinrRangeCustz[5]) { /* SINR = sinr/10 */
                sinrLevel = 0;
            } else if (strength.wss.sLte.sinr >= sinrRangeCustz[4]) {
                sinrLevel = 5;
            } else if (strength.wss.sLte.sinr >= sinrRangeCustz[3]) {
                sinrLevel = 4;
            } else if (strength.wss.sLte.sinr >= sinrRangeCustz[2]) {
                sinrLevel = 3;
            } else if (strength.wss.sLte.sinr >= sinrRangeCustz[1]) {
                sinrLevel = 2;
            } else if (strength.wss.sLte.sinr >= sinrRangeCustz[0]) {
                sinrLevel = 1;
            } else {
                sinrLevel = 0;
            }
            *puiSignal = sinrLevel;
			*rsrp_sinr = strength.wss.sLte.sinr;
        }
	}
	return 0;	
}
int app_get_wifi_signal(int *puiSignal, int *signalValue)
{
    if(NULL == puiSignal || NULL == signalValue){
        return -1;
    }
    if(1 == wifi_is_connected()){//���ж��Ƿ�����wifi
        wifi_get_rssi(signalValue);
    }else{
        *signalValue = *puiSignal = 0;
    }
        
    logger_debug("wifi signal = %d\n", *signalValue);
    if(*signalValue < 20){
        *puiSignal = 1;
    }else if(*signalValue < 40){
        *puiSignal = 2;
    }else if(*signalValue < 60){
        *puiSignal = 3;
    }else if(*signalValue < 80){
        *puiSignal = 4;
    }else{
        *puiSignal = 5;
    }
    return 0;
}


