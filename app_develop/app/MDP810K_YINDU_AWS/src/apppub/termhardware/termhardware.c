#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"
#include "apppubext.h"

void GetPosTime(char *pszDate, char *pszTime)
{
	char tmptime[20] = {0};
	
	app_get_time(tmptime);

	memcpy(pszDate, tmptime, 8);
	
	memcpy(pszTime, tmptime+8, 6);

	//logger_debug("POS Date: %s, Time: %s     \n", pszDate, pszTime);
}


appbool CheckBatteryCharge(void)
{
	BATTERYINFO batteryInfo;
	int iRet =  RET_OK;
	
	iRet = app_get_battery_info(&batteryInfo);
	if(iRet == RET_OK){
		if(batteryInfo.status == BATTERY_CHARGEING){
			return app_true;
		}
	}

	return app_false;
}

appbool CheckBatteryLow(void)
{
	int iRet = RET_OK;
	BATTERYINFO batteryInfo;

	iRet = app_get_battery_info(&batteryInfo);
	if(iRet == RET_OK){
		if(batteryInfo.status == BATTERY_ONLY){
			if(app_get_terminal_info(NULL)->stCap.bSupPrinter == app_true){
				if(batteryInfo.cur_values <= BATTERY_ONLY_LOW_VOLTAGE){
					return app_true;
				}
			}else{//不带打印机的机器，电量低于10%是低电量 20210316
				if(batteryInfo.percent < BATTERY_LOW_PERCENTAGE){ 
					return app_true;
				}
			}
		}
		else if(batteryInfo.status == BATTERY_CHARGEING){
			if(app_get_terminal_info(NULL)->stCap.bSupPrinter == app_true){
				if(batteryInfo.cur_values <= BATTERY_CHARGING_LOW_VOLTAGE){
					return app_true;
				}
			}else{
				return app_false;
			}
		}
		else if(batteryInfo.status == BATTERY_NONE){
			return app_true;
		}
	}
	
	
	return app_false;
}

appbool CheckBatteryStatus(void)
{
	int iRet = RET_OK;
	BATTERYINFO batteryInfo;

	iRet = app_get_battery_info(&batteryInfo);
	if(iRet == RET_OK){
		if(batteryInfo.status == BATTERY_ONLY && batteryInfo.cur_values <= BATTERY_ONLY_LOW_VOLTAGE){
			app_lcd_clear_all();
			disp_win_msg_mul_lan("电量低，无法打印", "请及时充电","Battery Low Power", "Please Recharge", MSG_FAILED, RESULT_DISP_TIME);
		}
		else if(batteryInfo.status == BATTERY_CHARGEING && batteryInfo.cur_values <= BATTERY_CHARGING_LOW_VOLTAGE){
			app_lcd_clear_all();
			disp_win_msg_mul_lan("电量低，无法打印", "请继续充电","Battery Low Power", "Please Recharge", MSG_FAILED, RESULT_DISP_TIME);		
		}
		else if(batteryInfo.status == BATTERY_NONE){
			app_lcd_clear_all();
			disp_win_msg_mul_lan("电量低，无法打印", "请继续充电","Battery Low Power", "Please Recharge", MSG_FAILED, RESULT_DISP_TIME);		
		}
		else{
			return app_true;
		}

		return app_false;
	}

	return app_true;
}

appbool CheckIfNew6230(void)
{
	if(!memcmp(app_get_terminal_info(NULL)->Terminal,"NEW6230",strlen("NEW6230"))){
		return app_true;
	}

	return app_false;
}

static int g_powerofftimer = -1;
static int g_checksavetimer = -1;

static void checksavepower(void *arg)
{
	if(!lcd_get_backlight_status()){//进入休眠后
		//logger_debug("lcd_get_backlight_status is off\n");	
		if (app_timer1_check_active(g_powerofftimer) == app_false 
			/*&& stSysPara.swAutoPowerOff == para_on*/){
			logger_debug("start timer\n");

			//激活关机定时器
			//app_timer1_start(g_powerofftimer, stSysPara.iAutoPoweroffTime*60*1000);
		}
	}
	else{ // 休眠唤醒
		//logger_debug("lcd_get_backlight_status is on\n");
		if(app_timer1_check_active(g_powerofftimer) == app_true){
			logger_debug("stop timer\n");
			app_timer1_stop(g_powerofftimer);
		}
	}
}

void pos_poweroff(void *arg)
{
	BATTERYINFO batteryInfo;
	int iRet;
	
	logger_debug("%s run...\n", __FUNCTION__);
	/*
	if(stSysPara.swAutoPowerOff == para_off)
		return;
	*/ 
	//充电状态不检查关机
	iRet = app_get_battery_info(&batteryInfo);
	if(iRet != 0)
		return;
	
	logger_debug("batteryInfo.status = %d\n", batteryInfo.status);
	if(0 == iRet && BATTERY_ONLY != batteryInfo.status) //接外电不关机，否则会重启
		return;

	logger_debug("power off\n");
	app_power_off();	
}

void InitSavepowerTimer(void)
{
	if (g_checksavetimer <= 0){
		g_checksavetimer = app_timer1_append(checksavepower, NULL);
	}
	logger_debug("g_checksavetimer = %d\n", g_checksavetimer);
}

void StartSavepowerTimer(int timeperiod)
{
	app_timer1_start(g_checksavetimer, timeperiod);
}

void StopSavepowerTimer(void)
{
	app_timer1_stop(g_checksavetimer);
}

void DeleteSavepowerTimer(void)
{
	app_timer1_delete(g_checksavetimer);
	g_checksavetimer = -1;
}

void InitPoweroffTimer(void)
{
	if (g_powerofftimer <= 0){
		g_powerofftimer = app_timer1_append(pos_poweroff, NULL);
	}
	logger_debug("g_powerofftimer = %d\n", g_powerofftimer);
}

void StartPoweroffTimer(int timeperiod)
{
	app_timer1_start(g_powerofftimer, timeperiod);
}

void StopPoweroffTimer(void)
{
	app_timer1_stop(g_powerofftimer);
}

void DeletePoweroffTimer(void)
{
	app_timer1_delete(g_powerofftimer);
	g_powerofftimer = -1;
}


