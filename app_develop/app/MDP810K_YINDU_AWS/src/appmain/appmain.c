/*
 * main.c
 *
 *  Created on: Aug 12, 2013
 *      Author: Administrator
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <system.h>
#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"
#include "apppubext.h"
#include "ntptime.h"
#include "audio.h"
#include "fixaudio.h"
#include "event_user.h"
#include "ota_http_upgrade.h"
#include "button.h"
#include "task_thread.h"
#include "record_store.h"
#include "aiot_mqtt.h"
#include "net_work.h"
#include "os_pthread.h"
#include "np_led.h"
#include "sysfile.h"
#include "downloadfile.h"
#include "beeper.h"

#define GET_BASETATION_TIME     10*60  
extern int TimeCheckRange(char *pBeforeTimeStr,char *pCurTimeStr, int iCompTime);


static void TempParaInit(void)
{
	memset(&stSysTemp,0,sizeof(SYS_TEMP_STRC));
	
	strcpy(stSysTemp.EntryTeller.szTellerNo, TELLER_NOBODY);
	stSysTemp.bNeedDns = app_true;
	stSysTemp.iChkUpdateAppPeriod = CHECK_UPDATE_APP_TIME_QUICK; 	// 开机快速检查一次
	stSysTemp.ChkUpdateAppTick = app_get_tick_count();
	stSysTemp.iChkSimTimeout = 10; //5改成10，FF模块第一版固件识别SIM卡比较慢 211009
	stSysTemp.bSettleCancelEnable = app_true;

	strcpy(stPosVersion.szVersion,"V311606");
	strcpy(stPosVersion.szCertificate,"123226");

	stSysTemp.iChkSimTimeout  = 10;
	stSysTemp.bMqttStopFlg    = app_false;
	stSysTemp.bMqttStarted    = app_false;
	stSysTemp.bPlayConnecting = app_true;
	stSysTemp.bPlayConnected  = app_true;
	stSysTemp.sFnModel		  = FN_CHANGE_VOL;
	stSysTemp.ap_or_airkiss   = WifiChanl_NON;
	stSysTemp.changeingState  = app_false;
	stSysTemp.bSaveRecord     = app_false;
	stSysTemp.bSaveRecordACK  = app_false;
}


static int SysInit(int argc, char *argv[])
{
	int x = 0, y = 0;
	int width = 0, height = 0;
    ST_LCD_INFO lcdInfo;
    ST_APP_FONT appFont;

    memset(&lcdInfo, 0x00, sizeof(ST_LCD_INFO));
    memset(&appFont, 0x00, sizeof(ST_APP_FONT));
	
	app_sys_init();
	app_lcd_init();

    app_lcd_get_info(&lcdInfo);
    app_lcd_get_app_font(&appFont);

    x = 0;
    width = lcdInfo.width;
    if (LCD_128x64_WIDTH == lcdInfo.width) {
        y = appFont.attr.line_height * 2;
        height = appFont.attr.line_height;
    } else if (LCD_160x128_WIDTH == lcdInfo.width) {
        y = appFont.attr.line_height * 3;
        height = appFont.attr.line_height;
    } else {
        y = appFont.attr.line_height * 3;
        height = 24 * 2;
    }

    logger_debug("lcd_width = [%d], height = [%d]\n", lcdInfo.width, lcdInfo.height);
    logger_debug("x = [%d], y = [%d], width = [%d], height = [%d]\n", x, y, width, height);

	app_lcd_set_flip_sync(app_true);

	app_ped_set_input_region(x, y, width, height);

	app_file_set_workdir(APP_FILE_PATH);

	return RET_OK;
}

static int ParamInit(int argc, char *argv[])
{
	int fd = -1, iRet = 0;
	const char verifytmp[] = "vetmp";

	(void)argc;
	(void)argv;
	
#ifdef RESET_DEFAULT_SETTING
	RemoveAllAppFile();
#endif

	if( app_file_checkappdir("/") == app_false){
		logger_warn("app dir not exsit\n");
		if( app_file_creatappdir("/") != RET_OK){
			disp_win_msg("Creat App Folder Fail!", NULL, MSG_FAILED, MAX_DISP_TIME);
		}
	}

	
	if( app_file_checkappdir(ES_IMAGE_DIR) == app_false){
		logger_warn("app dir not exsit\n");
		if( app_file_creatappdir(ES_IMAGE_DIR) != RET_OK){
			disp_win_msg("Create Sign Folder Fail!", NULL, MSG_FAILED, MAX_DISP_TIME);
		}
	}
	/*********************************************************
	文件检查判断:
	1.判断检查文件是否存在,check if file exist
	2.若检查文件存在，说明参数文件均正常 ,if file exist, param file will be normal
	3.若检查文件不存在，需要判断应用版本是增加检查前/后的版本，通过
	是否存在最后一个参数文件来判断。if file not exist ,need to check app version ,if it is new version or not
	4.若是修改前的版本，增加检查文件即可 if old version , check if need to add file 
	5.若是修改后的版本，说明文件加载时异常，需要恢复所有参数文件默认值 if new version ,it may be file error, need to recover default param
	*********************************************************/
	if(app_file_exists(verifytmp) >= 0){ //文件存在
		LoadOpers();
		LoadSysPara();
		LoadCtrlPara();
		LoadTransPara();
		LoadTransCtrlPara();
		LoadCommunicationPara();
	}
	else{
		//注意是最后一个参数文件，不同应用可能需要修改!!
		if(app_file_exists(COMM_TMS_FILE) >= 0){ //旧版，无需做任何处理
			logger_debug("old version\n");
			LoadOpers();
			LoadSysPara();
			LoadCtrlPara();
			LoadTransPara();
			LoadTransCtrlPara();
			LoadCommunicationPara();
		}
		else{//新版，恢复所有参数文件
			logger_debug("new version\n");

			iRet = LoadDefaultOpers();
			if( iRet == RET_OK){
				iRet = SaveOpers();
			}
				
			iRet = LoadDefaultSysPara();
			if( iRet == RET_OK){
				iRet = SaveSysPara();
			}

			iRet = LoadDefaultCtrlPara();
			if( iRet == RET_OK){
				iRet = SaveCtrlPara();
			}
				
			iRet = LoadDefaultTransPara();
			if( iRet == RET_OK){
				iRet = SaveTransPara();
			}
			
			iRet = LoadDefaultTransCtrlPara();
			if( iRet == RET_OK){
				iRet = SaveTransCtrlPara();
			}
						
			iRet = LoadDefaultCommunicationPara();
			if( iRet == RET_OK){
				iRet = SaveCommunicationPara();
			}
		}

		//创建校验文件
		fd = app_file_open(verifytmp, O_RDWR|O_CREAT);
		if(fd >= 0){
			app_file_write(fd, (char *)APP_PARAM_VERSION, strlen(APP_PARAM_VERSION));
		}
		app_file_close(fd);
	}
	TempParaInit();
	get_ali_mqtt_para();
	init_audiofileparam();

	//loadPosExtAppFile();
	//LoadFileBIN();
	ota_param_read();
	
	return RET_OK;
}

static void AdjustCommPara(void)
{
	TERMINALINFO terminal;

	app_get_terminal_info(&terminal);

	if(stCommPara.commType == CT_GPRS && terminal.stCap.bSupGprs == app_false &&
		terminal.stCap.bSupWifi == app_true){
		stCommPara.commType =  CT_WIFI;
	}else if(stCommPara.commType == CT_WIFI && terminal.stCap.bSupWifi == app_false &&
		terminal.stCap.bSupGprs == app_true){
		stCommPara.commType  =  CT_GPRS;
	}

	SaveCommunicationPara();
}

static int HardwareInit(int argc, char *argv[])
{
	int ret = RET_OK;
	(void)argc;
	(void)argv;
	
	AdjustCommPara();
	CommModuleInit();

    //CommInit函数会显示信号图标，联通卡开机第一笔显示信号图标比较慢，所以在CommInit之前需要加个显示
	if(stCommPara.commType == CT_WIFI){	
		disp_win_language_info_nowait("WIFI初始化中", "请稍候...","WIFI Init","Please Wait...");
	}
	else if(stCommPara.commType == CT_GPRS || stCommPara.commType == CT_CDMA){
		disp_win_language_info_nowait("无线模块初始化中", "请稍候...","Wireless Init","Please Wait...");
		app_wifi_close();
	}

	if(stCommPara.swUsedSsl == para_off){
		CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_TCP);
	}
	else{
		CommInit(TRANS_COMM_HANDLE, stCommPara.commType, SOCK_SSL);
	}

	if(stCommPara.commType == CT_WIFI){
		app_wifi_open(stSysPara.ucOprtLimitTime, app_false);
	}
	else if(stCommPara.commType == CT_GPRS || stCommPara.commType == CT_CDMA){
		//app_lcd_set_icon(ICON_SIGNAL, app_on);//通讯库显示信号图标
		logger_debug("+++PreDial\n");
		PreDial(FALSE);
	}

	return ret;
}

static int AppInit(int argc, char *argv[])
{
	int ret = RET_OK;
	uint8_t szDate[8+1] = {0};
	uint8_t szTime[6+1] = {0};
	
#if SW_SUP_NTP	
	ST_SYNC_TIME_IN stIn = {0};
#endif
	(void)argc;
	(void)argv;
	logger_debug("AppInit iVolnume = %d\n",stSysPara.iVolnume);

	audio_tts_set_para(TTS_CONFIG_RESOURCE, TTS_RESOURCE_16K_EN); //set tts language
	audio_set_volume(stSysPara.volume); //init volume

	
#if SW_SUP_NTP	
	stIn.ComType = (int *)&stCommPara.commType;
	stIn.pFileSaveDir = (char *)APP_FILE_PATH;
	stIn.timezone = 5.5;//设置时区参数 印度为IST时区(UTS+5.5h)
	InitSyncPosTime(stIn);
#endif


	StopSavepowerTimer();
	StopPoweroffTimer();

	DeleteSavepowerTimer();
	DeletePoweroffTimer();	
	SaveSysPara();

	stBaseStation.commtype = stCommPara.commType;
	//CommGetBaseStation(&stBaseStation); //开机获取基站信息
	GetPosTime((char *)szDate, (char *)szTime);
	snprintf(stSysTemp.szBaseStationDate, sizeof(stSysTemp.szBaseStationDate), "%s%s", 
		(char *)szDate, (char *)szTime);

	if(app_false==app_file_checkappdir("ota")){ //check ota dir
		app_file_creatappdir("ota");
	}

	return ret;
}

static void* firstmqtt_thread_proc(void* lpThreadParameter)
{
	while (globa_thread_logon) {
		sys_msleep(10);
	}

	sys_msleep(1000);

	AwsMqttProc();
	
	return NULL;
}

void sys_event_proc(void)
{
	int fd = -1;
    int event = 0;
	int ret=-1;
	
	fd = open("/dev/event", O_RDONLY);
    if(fd<0){
        logger_debug("open event dev fail\r\n");
		set_play_state(PLAY_BUSY);
		add_play_text(Audio_shebeiguzhang, NULL, NULL, PLAY_MP3);
		shutdown_save_record_file();
		syscall_msleep(1000);
		syscall_reboot();
		return;
    }

	globa_thread_logon=0;

	while (1){
		ret = read(fd, &event, 4);
        logger_debug("read event value:%08x,ret:%d\r\n", event, ret);
        if(ret == 4){
            if(IS_EVENT_SET(event, EVENT_ID_KEY)){
				chk_button_status();
                logger_debug("key hit\r\n");
			} 
            if(IS_EVENT_SET(event, EVENT_ID_POWER_OFF)){
				disconnect_mqtt(1);
				app_set_led(LED_GREEN|LED_BLUE|LED_RED, LED_OFF_MODE);
				shutdown_save_record_file();
				clear_and_stop_play();
                add_play_text(Audio_zhengzaiguanji, NULL, NULL, PLAY_MP3);
                syscall_msleep( 3000);
                syscall_power_off();
            }
            if(IS_EVENT_SET(event, EVENT_ID_USB_PLUG_IN)){
				app_set_led(LED_CHARGE, LED_ON_MODE); //sys_led_control(SYS_LED_CHARGE,SYS_LED_ON);
                add_play_text(Audio_chongdianzhong, NULL, NULL, PLAY_MP3);
			}
            if(IS_EVENT_SET(event, EVENT_ID_USB_PLUG_OUT)){
				app_set_led(LED_CHARGE, LED_OFF_MODE); //sys_led_control(SYS_LED_CHARGE,SYS_LED_OFF);
				add_play_text(Audio_chongdianyiyichu, NULL, NULL, PLAY_MP3);
			}
            if(IS_EVENT_SET(event, EVENT_ID_LOW_BATTERY)){
                add_play_text(Audio_qingchongdian, NULL, NULL, PLAY_MP3);
            }
            if(IS_EVENT_SET(event, EVENT_ID_FW_UPGRADE)){
                add_play_text(Audio_shengjichenggong, NULL, NULL, PLAY_MP3);//fw upgarde success
            }
			if(IS_EVENT_SET(event, EVENT_ID_CHARGE_FINISH)){
				app_set_led(LED_CHARGE, LED_OFF_MODE); //sys_led_control(SYS_LED_CHARGE,SYS_LED_OFF);
				add_play_text(Audio_chongdianyiwancheng, NULL, NULL, PLAY_MP3);
			}
			if(IS_EVENT_SET(event, EVENT_ID_LOW_BATTERY_POWER_OFF)){
				add_play_text(Audio_dianliangdi, NULL, NULL, PLAY_MP3);
				shutdown_save_record_file();
				syscall_msleep( 3000);
				syscall_power_off();
			}
			
		}

		syscall_msleep( 10 );
    }
	return;
}


int npmain(int argc, char *argv[])
{
	pthread_attr_t attr2;
	pthread_t pid;

	(void)argc;
	(void)argv;
	
	logger_debug("enter appmain now\r\n");
	logger_debug("app_lcd_get_language=%d,APP_ZH=%d\n",app_lcd_get_language(),APP_ZH);
	init_led();
	app_set_led(LED_GREEN|LED_BLUE|LED_RED, LED_ON_MODE);
	if(SysInit(argc, argv ) != RET_OK ){
	}

	if( ParamInit(argc, argv ) != RET_OK ){
	}
	
	if( HardwareInit(argc, argv) != RET_OK){
	}
	logger_debug("AppInit\n");
	
	if (AppInit(argc, argv) != RET_OK){
		
	}


#if SW_SUP_NTP
	StartSyncPosTime(1);
	logger_debug("StartSyncPosTime\n");
#endif	
	sys_beep_enable(app_false);//AWS不用蜂鸣器
	SaveTransPara();
	app_set_led(LED_GREEN, LED_ON_MODE);
	//初始化记录数据
	init_record_cjson();
	init_mqtt_ack_cjson();
	//初始化队列
	init_task();
	logger_debug("init_task\n");
	//ota下载线程启动 
	init_https_ota();	
	init_net_task();
	wait_play_timeout(6*1000);
	logger_debug("wait_play_timeout\n");
	globa_thread_logon=1;
	pthread_attr_init(&attr2);
	logger_debug("pthread_attr_init\n");
	attr2.stacksize = 32*1024;
	
	logger_debug("create thread firstmqtt_thread_proc\n");
	if (pthread_create(&pid, &attr2, firstmqtt_thread_proc, NULL) != 0) {
	    logger_debug("create thread failed");
	    return -1;
	}
	sys_event_proc(); //loop
	return 0;
}

