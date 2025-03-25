

#ifndef _EVENT_H_
#define _EVENT_H_

#include <appdatatypedef.h>

// 每一位代表一个EVENT， -1与0特殊
typedef enum{
	EVENT_NOINIT 		= 	-1,			// 未初始化
	EVENT_NONE 			= 	0,			// 无事件触发
	EVENT_KEY			=	0x01,		// 按键事件
	EVENT_TRANS_OCCUR 	= 	0x02,		// 交易触发

	EVENT_ALL		= 	EVENT_KEY|EVENT_TRANS_OCCUR	// 所有事件
}E_EVENT_TYPE;

	
typedef struct event_para_st{
	E_EVENT_TYPE event;		// 触发的事件类型
	int PARAM1;				// 事件参数1
	//void* PARAM2;
}ST_EVENT_PARAM;



/** 
 * @brief  等待事件触发
 * @note   
 * @param in  
 		EventTypes: 监听指定的事件类型
 		timeout: 监听时间
 * @param out
 		lpEventParam: 监听结果
 * @retval 	
 		TRUE-有事件触发
 		FALSE-未触发事件
**/
appbool WaitAppEvent(ST_EVENT_PARAM *lpEventParam, int EventTypes, unsigned long timeout);

/** 
 * @brief  清除事件缓冲
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		none
**/
void ClearAppEvent(void);

/** 
 * @brief  检查是否有事件触发
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		TRUE-有事件触发
 		FALSE-未有事件触发
**/
appbool CheckAppEvent(void);


/** 
 * @brief  检查事件缓冲是否为空
 * @note   
 * @param in  
 		none
 * @param out
 		none
 * @retval 	
 		TRUE-事件缓冲为空
 		FALSE-事件缓冲非空，存有之前触发的事件信息
**/
appbool CheckAppEventEmpty(void);

/** 
 * @brief  推入一个事件，若原有事件为处理，将覆盖未处理的事件
 * @note   
 * @param in  
 		lpEventParam 事件参数
 * @param out
 		none
 * @retval 
 		0-成功 非0-失败
**/
int PullAppEvent(ST_EVENT_PARAM *lpEventParam);


#endif
