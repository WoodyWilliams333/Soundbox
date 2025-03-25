#include "button.h"
#include <system.h>
#include <string.h> 
#include <key.h>
#include <appkey.h>
#include <wnet.h>
#include "basicext.h"
#include "logger.h"
#include "record_store.h"
#include "tts_play.h"
#include "task_thread.h"
#include "fixaudio.h"
#include "WifiConfig.h"
#include "net_work.h"
#include "aiot_mqtt.h"
#include "appdef.h"
#include "appgprs.h"
#include "pahomqtt.h"
#include <wifi.h>
#include "tersharedata.h"
#include "terfilecomm.h"

#define CHK_BUTTON_TIMEOUT   (5*1000) //查询按键的超时时间ms
#define CHK_LONGPRESS_TIMEOUT   (3*1000) //长按按键时间ms
uint8_t vol_play_limited = 0;      //已播最大或最小音量

#define BUTTON_ADD      KEY_UP          //04
#define BUTTON_SUB      KEY_DOWN        //05
#define BUTTON_FN       8               //08
#define BUTTON_POWER    KEY_POWER       //02
#define LAST_PLAY_TIME_OUT (3*60*1000)

#define KEY_STATUS_LONGPRESS 2

key_info_t down_staus;


#define vol_level   10
static int already_play;
static char vol_str[11];
/**
 * @brief  调高音量，底层是0~100，整10位单位调整
 * @retval 无
 */

void play_vol_level(int vol)
{
	if(vol<=vol_level){
		if(already_play == 0){
			add_play_text(Audio_Yinliang, vol_str, NULL, PLAY_MP3);
			already_play = 1;
			vol_play_limited = 0;
		}else{
			if(!vol_play_limited){
				add_play_text(Audio_yinliangzuixiao, NULL, NULL, PLAY_MP3);
				vol_play_limited = 1;
			}
		}
	}else if(vol>(100 - vol_level)){
		if(already_play == 0){
			add_play_text(Audio_Yinliang, vol_str, NULL, PLAY_MP3);
			already_play = 1;
			vol_play_limited = 0;
		}else{
			if(!vol_play_limited){
				add_play_text(Audio_yinliangzuida, NULL, NULL, PLAY_MP3);
				vol_play_limited = 1;
			}
		}
	}else{
		add_play_text(Audio_Yinliang, vol_str, NULL, PLAY_MP3);
		already_play = 0;
		vol_play_limited = 0;
	}
}

void key_button_add_vol(void)
{
	logger_debug("stSysPara.volume = %d\n", stSysPara.volume);
    stSysPara.volume += vol_level;
    if(stSysPara.volume >= 100){
        stSysPara.volume = 100;
    }
	snprintf(vol_str,sizeof(vol_str),"%d",(stSysPara.volume/vol_level));
	set_play_vol(stSysPara.volume);
	logger_debug("finished set_play_vol\n");
	play_vol_level(stSysPara.volume);
   
    logger_debug("stSysPara.volume = %d,vol_str=%s\n", stSysPara.volume,vol_str);
    SaveSysPara(); 
    
}

/**
 * @brief  调低音量，底层是0~100，整10位单位调整
 * @retval 无
 */
void key_button_sub_vol(void)
{
    logger_debug("stSysPara.volume = %d\n", stSysPara.volume);
    stSysPara.volume -= vol_level;
	logger_debug("+++++++++\n");
    if(stSysPara.volume <= vol_level){
        stSysPara.volume = vol_level;
    }
	snprintf(vol_str,sizeof(vol_str),"%d",(stSysPara.volume/vol_level));
	logger_debug("start set_play_vol\n");
	set_play_vol(stSysPara.volume);
	logger_debug("finished set_play_vol\n");
	play_vol_level(stSysPara.volume);
    logger_debug("stSysPara.volume = %d,vol_str=%s\n", stSysPara.volume,vol_str);
    SaveSysPara(); 
    
}

static int get_record_number(cJSON *root, const char *jsontag, int *msg)
{
    cJSON *item = NULL;

    if(NULL == root || NULL == jsontag || NULL == msg){
        return -1;
    }else{
        //播报内容
        item = cJSON_GetObjectItem(root, jsontag);
        if(NULL != item && cJSON_Number == item->type){
            logger_debug("msg = %d\n",item->valuestring);
            *msg = item->valueint;
            return 1;
        }
    }
    return -1;
}


static int get_record_str(cJSON *root,const char *jsontag, char *msg, int outsize)
{
    cJSON *item = NULL;

    if(NULL == root || NULL == jsontag || NULL == msg){
        return -1;
    }else{
        //播报内容
        item = cJSON_GetObjectItem(root, jsontag);
        if(NULL != item && cJSON_String == item->type){
            logger_debug("msg = %s\n",item->valuestring);
            snprintf(msg, (outsize), "%s", item->valuestring);
            return 1;
        }
    }
    return -1;
}


/**
 * @brief  播报历史记录
 * @param[in]   type            查找播报类型
 * @retval 无
 */
static void play_record_store(int index)
{
    int count = 0;
    char amount[25] = {0};
    char msg[256] = {0};
    //char temp[128] = {0};
    int con = 0;

    cJSON *root = NULL;
	static struct timeval last_play_record_tick = {0,0};
	
    logger_debug("record_get_count() = %d\n",record_get_count());

    logger_debug("g_index = %d\n",index);

    //第一个参数是json数组索引
    root = record_manage_read(index, &count);
    if(NULL != root){
        get_record_str(root, JSON_ITEM_VMSG, msg, sizeof(msg));
        get_record_str(root, JSON_ITEM_MONEY, amount, sizeof(amount));
        get_record_number(root, JSON_ITEM_CODE, &con);
		//snprintf(temp, sizeof(temp), "第%s%d%s笔", Audio_REGEX, (record_get_count()-index), Audio_REGEX);
        add_play_text(Audiodiyibi, NULL, NULL, PLAY_MP3);
        add_play_text(msg, amount, NULL, con);
  
        gettimeofday(&last_play_record_tick, NULL); 
    }else{
        add_play_text(Audio_anjianyin, NULL, NULL, PLAY_MP3);
    }
    logger_debug("g_index = %d\n",index);
}


#define SIGNAL_HIGH 4
#define SIGNAL_LOW  2
/**
 * @brief  功能键播报，播报音量&网络情况
 * @retval 无
 */
void key_button_fn(void)
{
    int battery = 0;
    //int signal = 0, temp = 0;
    char strtemp[10] = {0};
	//int ret = RET_OK;
    
    battery = get_battery_percent();
    if(battery >=0 && battery <= 100){
        logger_debug("battery = %d\n", battery);
		snprintf(strtemp, sizeof(strtemp), "%d", battery);
        add_play_text(AudioDangqiandl, strtemp, NULL, PLAY_MP3_AMOUNT);
		
    }
    //signal 信号强度 varchar(32) C
    #if 0//印度AWS不需要播报网络
    if(CT_WIFI==stCommPara.commType){//rssi	连接的网络的ssid的信号值0-100
        app_get_wifi_signal(&signal, &temp);
    }else{
	    app_lte_get_network_signal(&signal, &temp); 
    }

	snprintf(strtemp, sizeof(strtemp), "%d", signal);

	ret = chk_net_play_status(app_false, app_false);
	logger_debug("chk_net_play_status=%d\n",ret);
	if(E_COMM_NO_SIM == ret){
        add_play_text(Audio_weijiancedaoSIMka, NULL, NULL, PLAY_MP3);
		//add_play_text(Audio_QingChaRuSIMKa, NULL, NULL, PLAY_MP3);
		//add_play_text(Audio_ChongQiSheBei, NULL, NULL, PLAY_MP3);
    }else{
        add_play_text(Audio_XinHaoDengji, strtemp, NULL, PLAY_MP3);
        if(signal <= SIGNAL_LOW){
            add_play_text(Audio_XinHaoRuo, NULL, NULL, PLAY_MP3);
        }else if(signal >= SIGNAL_HIGH){
            add_play_text(Audio_XinHaoQiang, NULL, NULL, PLAY_MP3);
        }else{
            add_play_text(Audio_XinHaoZhengchang, NULL, NULL, PLAY_MP3);
        }
		if(RET_OK == ret){
			logger_debug("get_matt_connect_state\n");
			if(app_true == get_matt_connect_state()){
				 //add_play_text(Audio_fuwulianjiechenggong, NULL, NULL, PLAY_MP3);
			}else{
				//add_play_text(Audio_fuwulianjieshibai, NULL, NULL, PLAY_MP3);
                //wifi路由器正常，外联网络断开，会提示网络连接成功
                //如果检测到mqtt状态为非连接就重启wifi或4g
            	if(app_true == get_mqtt_disconnect_state()){
               		net_reboot();
            	}
            }
		}else{
			add_play_text(Audio_wangluoyichang, NULL, NULL, PLAY_MP3);
		}
    }
	#endif 
	
}

/**
 * @brief  检查是否有双击，检查超时时间500ms
 * @param[in]   onekey          第一次按键值
 * @retval 无
 */
int check_db_click(int onekey)
{
    key_info_t key_staus;
    int key;

    do{
        key = kb_get_key_info(500, &key_staus); //检测是否有按键按下 超时时间msec
        logger_debug("key = %d\n", key);
        logger_debug("key_staus.key = %d\n", key_staus.key);
        logger_debug("key_staus.status = %d\n", key_staus.status);//KEY_STATUS_UP 0, KEY_STATUS_DOWN 1
        logger_debug("key_staus.tick_time = %d\n", key_staus.tick_time);
        //非法按键 超时 与第一次按键不一致都不是双击
        if(KEY_INVALID!= key && KEY_TIMEOUT != key && key == onekey){
            if(KEY_STATUS_DOWN == key_staus.status){//按下
                logger_debug("KEY_STATUS_DOWN !!!\n");
                key = kb_get_key_info(500, &key_staus); //检测是否有按键按下 超时时间msec
                logger_debug("key = %d\n", key);
                logger_debug("key_staus.key = %d\n", key_staus.key);
                logger_debug("key_staus.status = %d\n", key_staus.status);//KEY_STATUS_UP 0, KEY_STATUS_DOWN 1
                logger_debug("key_staus.tick_time = %d\n", key_staus.tick_time);
                if(KEY_INVALID != key && KEY_TIMEOUT != key && key == onekey){
                    if(KEY_STATUS_UP == key_staus.status){//弹起
                        logger_debug("KEY_STATUS_UP !!!\n");
                        return  1;
                    }
                }
            }
        }
    }while(0);

    return -1;
}

/**
 * @brief  检查按键状态
 * @param[out]   btInfo 返回当前按键信息
 * @retval 无
 */
void get_button_click(stButtonInfo *btInfo)
{
    key_info_t key_staus;
    int key;
	int cr_time = sys_get_timer_count();
    if(NULL == btInfo){
        return;
    }
    memset(&key_staus, 0, sizeof(key_info_t));
    btInfo->bt_key = KEY_INVALID;
    do{
        key = kb_get_key_info(500, &key_staus); //检测是否有按键按下 超时时间msec
        logger_debug("key = %d\n", key);
        logger_debug("key_staus.key = %d\n", key_staus.key);
        logger_debug("key_staus.status = %d\n", key_staus.status);//KEY_STATUS_UP 0, KEY_STATUS_DOWN 1
        logger_debug("key_staus.tick_time = %d\n", key_staus.tick_time);
        logger_debug("down_staus.key = %d\n", down_staus.key);
        if(KEY_INVALID!= key && KEY_TIMEOUT !=key){
            if(KEY_STATUS_DOWN == key_staus.status){//按下
                logger_debug("KEY_STATUS_DOWN !!!\n");
                memset(&down_staus, 0, sizeof(key_info_t));
                memcpy(&down_staus, &key_staus, sizeof(key_info_t));		
            }
			do{
				kb_get_key_info(CHK_LONGPRESS_TIMEOUT - 500, &key_staus); //检测是否有按键按下 超时时间msec
				logger_debug("key=%d tick_time - tick_time = %d,status=%d !!!\n",key_staus.key, key_staus.tick_time - down_staus.tick_time,key_staus.status);
			}while(key_staus.status == KEY_STATUS_DOWN && (sys_get_timer_count() - cr_time) < (CHK_LONGPRESS_TIMEOUT - 500));
		
			if(KEY_STATUS_UP == key_staus.status && 0 != down_staus.key /*&& down_staus.key == key_staus.key*/){//弹起
                 if(key_staus.tick_time - down_staus.tick_time < 500){
                    if(1 == check_db_click(key_staus.key)){//双击
                        logger_debug("db click !!!\n");
                        btInfo->bt_key = key_staus.key;
                        btInfo->bt_cmd = BUTTON_DOUBLE_CLICK;
                        memset(&down_staus, 0, sizeof(key_info_t));
                        break;
                    }
                }
                logger_debug(" click !!!\n");
                btInfo->bt_key = key_staus.key;
                btInfo->bt_cmd = BUTTON_SHORT_PRESS;
                memset(&down_staus, 0, sizeof(key_info_t));
                break;
            }else if(key_staus.status == KEY_STATUS_DOWN  &&  ((sys_get_timer_count() - cr_time > CHK_LONGPRESS_TIMEOUT - 500) || key_staus.tick_time - down_staus.tick_time > CHK_LONGPRESS_TIMEOUT- 500)){//长按
                logger_debug("long click !!!\n");
                btInfo->bt_key = key_staus.key;
                btInfo->bt_cmd = BUTTON_LONG_PRESS;
                memset(&down_staus, 0, sizeof(key_info_t));
                if(BUTTON_POWER != btInfo->bt_key){
                    add_play_text(Audio_anjianyin, NULL, NULL, PLAY_MP3);
                    //app_beep_info(2700, 100);
                }
                break;
            }else{
                logger_debug("KEY_INVALID click !!!\n");
                memset(&down_staus, 0, sizeof(key_info_t));
                btInfo->bt_key = KEY_INVALID;
                break;
            }
        }
        
    }while(0);
}

/**
 * @brief 检测按键信息
 *
 * @return void 
 */
void chk_button_status(void)
{
    stButtonInfo btInfo;
    int key;

	stSysTemp.sFnModel = FN_CHANGE_VOL;
    
    memset(&btInfo, 0, sizeof(stButtonInfo));
    get_button_click(&btInfo);
    key = btInfo.bt_key;
    logger_debug("----key = %d\n", btInfo.bt_key);
    logger_debug("----bt_cmd = %d\n", btInfo.bt_cmd);
    if(KEY_INVALID == key){
        return;
    }
    kb_flush();
    
    switch (key)
    {
    case BUTTON_POWER://mdp 电源键
        logger_debug("KEY_POWER\n");
		logger_debug("stSysTemp.ap_or_airkiss = %d\n", stSysTemp.ap_or_airkiss);
        //当前是配网模式 短按电源键 支持wifi  提示退网
        if((WifiChanl_AP == stSysTemp.ap_or_airkiss || WifiChanl_AIR == stSysTemp.ap_or_airkiss ) 
            && BUTTON_SHORT_PRESS == btInfo.bt_cmd && app_true == app_get_terminal_info(NULL)->stCap.bSupWifi ){//支持wifi
            add_play_text(Audio_yituichupeiwang,NULL,NULL, PLAY_MP3);
            set_wifi_ap_airkiss_type(WifiChanl_NON); 
        }else{
			key_button_fn();//单击电源键键，播报电量
		}
        break;
    case BUTTON_FN://mdp 功能键
        logger_debug("KEY_FUN\n");
        if(BUTTON_DOUBLE_CLICK == btInfo.bt_cmd && CT_WIFI == stCommPara.commType){//wifi 配网模式下双击功能键切换到wifi热点配网模式或者wifi微信配网模式
            if(app_true == app_get_terminal_info(NULL)->stCap.bSupWifi ){//支持wifi
				if(WifiChanl_NON == stSysTemp.ap_or_airkiss){
                    set_wifi_ap_airkiss_type(WifiChanl_AP);
	                logger_debug("NET_AP_MODE\n");
                    return;		
                }
				
				  //add_play_text(Audio_shuangjignjqhzWiFi_APpwms,NULL,NULL, PLAY_MP3);
                set_wifi_ap_airkiss_type(WifiChanl_NON); 
            }
        }else {
            //播报最后一笔
            play_record_store(record_get_count()-1);
        }
        
        break;
    case BUTTON_ADD://mdp 音量加
        logger_debug("KEY_+\n");
        set_reconnect_mqtt_sem();
        logger_debug("app_get_terminal_info(NULL)->stCap.bSupWifi = %d\n", app_get_terminal_info(NULL)->stCap.bSupWifi);
        logger_debug("stCommPara.commType = %d\n", stCommPara.commType);
        //4G网络模式下，长按音量+键可以切换到WIFI模式,需要有wifi模块
        if(BUTTON_LONG_PRESS == btInfo.bt_cmd){
            if(app_true == app_get_terminal_info(NULL)->stCap.bSupWifi){
                if(CT_WIFI == stCommPara.commType){//当前是wifi切换到4G
                    set_wifi_ap_airkiss_type(NET_WIFI_2_4G);
	                logger_debug("NET_WIFI_2_4G\n");
                }else{//4G模式进入配网模式
                    set_wifi_ap_airkiss_type(NET_4G_2_WIFI);
	                logger_debug("NET_4G_2_WIFI\n");
                }
                logger_debug("stSysPara.NetChanlLTE = %d\n", stCommPara.commType);
            }
        }else if(FN_CHANGE_VOL == stSysTemp.sFnModel){//音量模式下，可设置音量递增
            key_button_add_vol();
        }
        
        break;
    case BUTTON_SUB://mdp 音量减
        logger_debug("KEY_-\n");
        set_reconnect_mqtt_sem();
        logger_debug("KEY_- %d,sFnModel=%d\n",btInfo.bt_cmd,stSysTemp.sFnModel);
        //音量模式下，单击音量-键，可设置音量递减
        if(BUTTON_LONG_PRESS == btInfo.bt_cmd){
            //播报应用版本号
            //add_play_text("current version", APP_SUB_VER, NULL, PLAY_TTS);
        }else if(FN_CHANGE_VOL == stSysTemp.sFnModel){
            key_button_sub_vol();
        }
        break;
    default:
        break;
    }
}
