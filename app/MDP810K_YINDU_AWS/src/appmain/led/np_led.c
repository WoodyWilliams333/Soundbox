#include <os_pthread.h>
#include <string.h>
#include "np_led.h"
#include "ant_timer.h"
#include "led.h"
#include "system.h"
#include "logger.h"


static ant_timer app_led_timer = NULL;
LITHT_SWITHC_ST gp_led_st = {0};
static int led_on_off_time;
static pthread_mutex_t app_led_mutex;

void app_led_proc(void *param);


void init_led(void)
{
	//printf("init_led\n");
	memset(&gp_led_st,0,sizeof(LITHT_SWITHC_ST));
	gp_led_st.idx = SYS_LED_GREEN|SYS_LED_BLUE|SYS_LED_RED;
	gp_led_st.init_status = SYS_LED_ON;
	gp_led_st.period.holdon_time1 = 1000;
	gp_led_st.period.holdon_time2 = 1000;
	
	//printf("idx=%d\n",gp_led_st.idx);
	pthread_mutex_init(&app_led_mutex, NULL);
	//printf("init_led\n");
	if(app_led_timer == NULL){			
		app_led_timer = ant_timer_create("app_led");
		//printf("app_led\n");
	}
	
	ant_timer_start(app_led_timer,app_led_proc,NULL,1000,200);
	led_on_off_time = sys_get_timer_count();

	return;
}

void app_led_proc(void *param)
{
	//printf("app_led_proc b\n");
	pthread_mutex_lock(&app_led_mutex);
	if( gp_led_st.init_status == SYS_LED_ON){
		if(LED_BLUE & gp_led_st.idx ){
			sys_led_control(SYS_LED_BLUE, SYS_LED_ON );
			//printf("%d\n",__LINE__);
		}
		if(LED_GREEN & gp_led_st.idx){
			sys_led_control(SYS_LED_GREEN, SYS_LED_ON );
			//printf("%d\n",__LINE__);
		}
		if(LED_RED & gp_led_st.idx ){
			sys_led_control(SYS_LED_RED, SYS_LED_ON );
			//printf("%d\n",__LINE__);
		}
		//if(LED_CHARGE & gp_led_st.idx ){
		//	sys_led_control(SYS_LED_CHARGE, SYS_LED_ON );
			//printf("%d\n",__LINE__);
		//}
		if(gp_led_st.period.holdon_time1 > 0 && sys_get_timer_count() - led_on_off_time > gp_led_st.period.holdon_time1){
			gp_led_st.init_status = SYS_LED_OFF;
			led_on_off_time = sys_get_timer_count();
			//printf("SYS_LED_ON init_status=%d,idx=%d\n",gp_led_st.init_status,gp_led_st.idx);
		}
	}else if( gp_led_st.init_status == SYS_LED_OFF){
		if(LED_BLUE & gp_led_st.idx ){
			sys_led_control(SYS_LED_BLUE, SYS_LED_OFF );
			//printf("%d\n",__LINE__);
		}
		if(LED_GREEN & gp_led_st.idx){
			sys_led_control(SYS_LED_GREEN, SYS_LED_OFF );
			//printf("%d\n",__LINE__);
		}
		if(LED_RED & gp_led_st.idx ){
			sys_led_control(SYS_LED_RED, SYS_LED_OFF );
			//printf("%d\n",__LINE__);
		}
		//if(LED_CHARGE & gp_led_st.idx ){
		//	sys_led_control(SYS_LED_CHARGE, SYS_LED_OFF );
			//printf("%d\n",__LINE__);
		//}
		if(gp_led_st.period.holdon_time2 > 0 && sys_get_timer_count() - led_on_off_time > gp_led_st.period.holdon_time2){
			
			gp_led_st.init_status = SYS_LED_ON;
			led_on_off_time = sys_get_timer_count();
			//printf("SYS_LED_OFF init_status=%d,idx=%d\n",gp_led_st.init_status,gp_led_st.idx);
		}
	}	
	//printf("app_led_proc n\n");
	gp_led_st.idx &= ~LED_CHARGE;
	
	pthread_mutex_unlock(&app_led_mutex);
}



int led_status_control(uint32_t idx_bits, uint32_t init_status, LITHT_ON_OFF_TIME period)
{
	pthread_mutex_lock(&app_led_mutex);

	if(LED_CHARGE & gp_led_st.idx ){
		sys_led_control(SYS_LED_CHARGE, init_status);//电源灯单独处理
	}else{
		gp_led_st.idx = idx_bits;
		gp_led_st.init_status = init_status;
		gp_led_st.period.holdon_time1 = period.holdon_time1;
		gp_led_st.period.holdon_time2 = period.holdon_time2;
	}
	pthread_mutex_unlock(&app_led_mutex);
	return 0;
}


void app_set_light_status(int led_idx,LITHT_SWITHC sw)
{

	//由于网络异常每400ms会检测一次，每检测一次，需要执行下这个函数，
	//所以快闪不能设置超过400ms，否则会出现一直亮的情况
	LITHT_ON_OFF_TIME period_fast = {200, 200}; //亮200ms,灭200ms
	LITHT_ON_OFF_TIME period_slow = {500, 3000};//亮500ms,灭3秒
	LITHT_ON_OFF_TIME period_off  = {0};
	if(LED_BLUE & led_idx ||
		LED_GREEN & led_idx ||
		LED_RED & led_idx ){
		//led_status_control(LED_BLUE|LED_RED|LED_GREEN, SYS_LED_OFF, period_off);
		sys_led_control(SYS_LED_BLUE, SYS_LED_OFF );
		sys_led_control(SYS_LED_GREEN, SYS_LED_OFF );
		sys_led_control(SYS_LED_RED, SYS_LED_OFF );		
	}
	//printf("led_idx=%d,sw=%d\n",led_idx,sw);
	if(LED_SLOW_MODE == sw){
		led_status_control(led_idx, SYS_LED_ON, period_slow);
	}else if(LED_FAST_MODE == sw){
		led_status_control(led_idx, SYS_LED_ON, period_fast);
	}else if(LED_ON_MODE == sw){		
		led_status_control(led_idx, SYS_LED_ON, period_off);
	}else if(LED_OFF_MODE == sw && (SYS_LED_CHARGE & led_idx)){		
		led_status_control(led_idx, SYS_LED_OFF, period_off);
	}
}


void app_set_led(int idx,int mode)
{
	app_set_light_status(idx,mode);

}

void setLedStatus(int mode)
{
	switch(mode)
	{

		case TERM_POWEROFF:
			app_set_led(LED_CHARGE|LED_BLUE|LED_GREEN|LED_RED,LED_OFF_MODE);
			break;
		case TERM_OTA_START:
			app_set_led(LED_GREEN|LED_BLUE|LED_RED,LED_SLOW_MODE);
			break;
		
		case TERM_NET_CONNING:
			app_set_led(LED_GREEN,LED_SLOW_MODE);
			break;
		case TERM_NET_DISCON:
		case TERM_LTE_NET_ABNORMAL:
		case TERM_NET_APMODE:
		case TERM_OTA_FAIL:	
			app_set_led(LED_GREEN,LED_FAST_MODE);
			break;
		
		case TERM_CHARGE_FULL:
		case TERM_CHARGE_OFF:	
			app_set_led(LED_CHARGE,LED_OFF_MODE);
			break;
			
		case TERM_LOWBAT:
		case TERM_NO_SIM:
		case TERM_PARAM_ERR:	
			app_set_led(LED_RED,LED_FAST_MODE);
			break;
			
		case TERM_SERVER_OK:
		case TERM_OTA_OK:	
			app_set_led(LED_BLUE,LED_SLOW_MODE);
			break;

		case TERM_SERVER_DIS:
			app_set_led(LED_GREEN,LED_FAST_MODE);
			break;


		case TERM_NET_OK: 
			app_set_led(LED_BLUE,LED_ON_MODE);
			break;

		default:
			break;
	}

}


