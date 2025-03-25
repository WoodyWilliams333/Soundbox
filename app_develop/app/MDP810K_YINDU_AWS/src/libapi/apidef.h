/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2020-03-11 16:11:15
 * @LastEditors: YangJing
 * @LastEditTime: 2020-03-11 16:26:06
 */

#ifndef _API_DEF_H_
#define _API_DEF_H_


/*----------pos api confing--------*/


#ifdef CFG_4G_FLAG
#define APP_NAME 			"HindiAws"
#else
//#define APP_NAME 			"HindiAws"
#define APP_NAME 			"HindiAws"
#endif
#define APP_FILE_PATH 		"/home/user0/"APP_NAME

//#define CL_LED_SUPPORT
#define ASYNC_CONNECT

#ifdef ASYNC_CONNECT
#define ASYNC_CONNECT_PPP
//#define ASYNC_CONNECT_TCP

#ifdef ASYNC_CONNECT_PPP
#undef ASYNC_CONNECT_TCP
#endif


#ifdef ASYNC_CONNECT_TCP
#undef ASYNC_CONNECT_PPP
#endif

#endif


/*-------pos api confing end--------*/




#endif

