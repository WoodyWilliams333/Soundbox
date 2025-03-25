#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "basicext.h"
#include "libapiext.h"

#include "appevent.h"

typedef struct event_listener_st{
	E_EVENT_TYPE listenEvents;
	int checktime;
	ST_EVENT_PARAM eventPara;
}ST_EVENT_LISTENER;

typedef struct event_check{
	E_EVENT_TYPE event;
	appbool (*pCheckFunc)(void);
}ST_EVENT_CHECK;

static appbool CheckKeyEvent(void);

static const ST_EVENT_CHECK EventChkList[] ={
	{EVENT_KEY, CheckKeyEvent},
	{EVENT_NONE, NULL}
	
};

static ST_EVENT_LISTENER gl_EventListener = {0};

static appbool CheckKeyEvent(void)
{
	int ikey = 0;
	
	if( app_kb_check_key()){ // check key event
		ikey = app_kb_get_key();
		gl_EventListener.eventPara.event = EVENT_KEY;
		gl_EventListener.eventPara.PARAM1 = ikey;
		logger_debug("key press = 0x%X\n", gl_EventListener.eventPara.PARAM1);
		return app_true;
	}

	return app_false;
}


void SetEventListener(E_EVENT_TYPE listenEvents, int checktime) // , EventListenerCallBack callback
{
	E_EVENT_TYPE events = listenEvents & (EVENT_ALL);

	gl_EventListener.listenEvents = events;
	gl_EventListener.checktime = checktime;
	
	gl_EventListener.eventPara.event = EVENT_NONE;
	//if(gl_EventListener.eventPara.PARAM2 != NULL){
	//	free(gl_EventListener.eventPara.PARAM2);
	//	gl_EventListener.eventPara.PARAM2 = NULL;
	//}
	
}

void ClearAppEvent(void)
{
	gl_EventListener.eventPara.event = EVENT_NONE;
}

int GetEventListener(ST_EVENT_LISTENER* lpEventListener, appbool ClearFlag)
{
	memcpy(lpEventListener, &gl_EventListener, sizeof(ST_EVENT_LISTENER));
	if( ClearFlag == app_true){
		ClearAppEvent();
	}
	
	return 0;
}

appbool CheckAppEvent(void)
{
	unsigned int ts = 0;
	appbool ret = app_false,  loop = app_true;
	int i = 0;

	ts = app_get_tick_count();
	while(loop){
		if( app_get_tick_count() - ts >= 
			(unsigned int)gl_EventListener.checktime) { // check time out
			break;
		}

		for(i = 0; EventChkList[i].event != EVENT_NONE; i++){
			if( (gl_EventListener.listenEvents & EventChkList[i].event) && 
				EventChkList[i].pCheckFunc != NULL && 
				EventChkList[i].pCheckFunc() == app_true){
				ret = app_true;
				loop = app_false; 
				break;
			}
		}
		app_pos_msleep(10);
	}

	return ret;
}

appbool CheckAppEventEmpty(void)
{
	if(gl_EventListener.eventPara.event >= EVENT_KEY && 
			gl_EventListener.eventPara.event < EVENT_ALL){
		return app_false;
	}

	return app_true;
}

int PullAppEvent(ST_EVENT_PARAM *lpEventParam)
{
	memcpy(&gl_EventListener.eventPara, lpEventParam, sizeof(ST_EVENT_PARAM));

	return RET_OK;
}

appbool WaitAppEvent(ST_EVENT_PARAM *lpEventParam, int EventTypes, unsigned long timeout)
{

	ST_EVENT_LISTENER stEventListener;
	appbool ret = app_false;
	if( CheckAppEventEmpty() == app_true){
		SetEventListener(EventTypes, timeout);
		ret = CheckAppEvent();
	}
	else{
		ret = app_true; // 若监听到事件非空，认为是有事件，置位TURE去处理事件
	}
	if( lpEventParam != NULL){
		if ( ret  == app_true){
			GetEventListener(&stEventListener, app_false);
			if( lpEventParam != NULL){
			if( (stEventListener.eventPara.event & EventTypes) == 0) { // 过滤事件类型
				ret = app_false;
				lpEventParam->event = EVENT_NONE;
			}
			else {
				lpEventParam->event = stEventListener.eventPara.event;
				lpEventParam->PARAM1 =  stEventListener.eventPara.PARAM1;
			}
			}
		}
		else{
			lpEventParam->event = EVENT_NONE;
		}
	}
	
	return ret;		
}



