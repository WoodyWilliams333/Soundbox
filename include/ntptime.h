
#ifndef _NTP_TIME_H_
#define _NTP_TIME_H_

/*
功能：
通过NTP获取网络时间并同步到本地时间
*/

#include <sys/time.h>


typedef struct{
	int *ComType;					//通讯类型 指针 01-WIFI 02-GPRS
	char *pFileSaveDir;				//同步时间文件保存目录(一般填应用目录)
}ST_SYNC_TIME_IN;

typedef struct{
	char apn[20];		// sim apn
	char simuid[20];	// sim user id
	char simpwd[20];	// sim user password
}ST_NET_PARAM;


/****************************************************
更改NTP的网络参数
若未更改，默认参数为：
	apn-"CMNET"
	uid-"CARD"
	pwd-"CARD"
*****************************************************/
extern int UpdateNTPNetParam(ST_NET_PARAM stNetParam);

/****************************************************
初始化NTP服务参数
stSyncTimeIn [in] ST_SYNC_TIME_IN结构
成功启动返回0，失败返回其它
*****************************************************/
extern int InitSyncPosTime(ST_SYNC_TIME_IN stSyncTimeIn);

/****************************************************
启动NTP任务

runnow [in] 是否立刻执行NTP
	0-不立即执行，等到更新周期到了再执行
	1-立即执行，不检查更新周期是否达到

成功启动返回0，失败返回其它

备注: 
	若更新成功周期为6小时;若更新失败周期为1小时
*****************************************************/
extern int StartSyncPosTime(int runnow);


#endif
