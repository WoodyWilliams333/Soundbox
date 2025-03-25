
#ifndef _NTP_TIME_H_
#define _NTP_TIME_H_


//功能：
//通过NTP获取网络时间并同步到本地时间

/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app ntptime模块</strong> 相关的接口
	 * @par 文件    ntptime.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | 创建文件
	 * 2022-05-05    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app ntptime </strong>  module
	 * @par file    ntptime.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | create file
	 * 2022-05-05    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup ntptime ntptime
 @else
	@defgroup ntptime ntptime
 @endif
 * @{
*/

#include <sys/time.h>


typedef struct{
	int *ComType;		/**< @if Chinese 通讯类型 指针 01-WIFI 02-GPRS @else communication type(pointer) 01-WIFI 02-GPRS @endif */
	char *pFileSaveDir;	/**< @if Chinese 同步时间文件保存目录(一般填应用目录) @else synchronization time file storage directory (generally fill in the application directory) @endif */	
	int timezone;		/**< @if Chines  时区 @else timezone @endif */			
}ST_SYNC_TIME_IN;

typedef struct{
	char apn[20];		/**< sim apn */
	char simuid[20];	/**< sim user id */
	char simpwd[20];	/**< sim user password */
}ST_NET_PARAM;

/*!
 @if Chinese
  * @brief  该枚举类型列出了同步时间结果.
@else  
  * @brief  This enumerated type lists the synchronization time results.
@endif
*/
typedef enum{
	sync_ok = 0,		/**< @if Chinese 同步成功 @else synchronization succeeded @endif */	
	sync_failed,		/**< @if Chinese 同步失败 @else synchronization failed @endif */		
	sync_not_support,	/**< @if Chinese 不支持同步(固件版本太低) @else synchronization is not supported (firmware version is too low) @endif */
	sync_working,		/**< @if Chinese 同步中 @else synchronizing @endif */	

	sync_unknow = 0xFF	/**< @if Chinese 同步结果未知 @else the synchronization result is unknown @endif */	
}E_SYNC_TIME_RESULT;


/**
 @if Chinese
	* @brief 	更改NTP的网络参数,若未更改，默认参数为：apn-"CMNET",uid-"CARD",pwd-"CARD"
	* @param[in]	stNetParam		-	参考ST_NET_PARAM结构体
	* @return		0			-	成功
	* @return		其它		-	失败
 @else
	* @brief 	change network parameters of NTP,if not changed, the default parameter is apn-"CMNET",uid-"CARD",pwd-"CARD"
	* @param[in]	stNetParam		-	reference ST_NET_PARAM structure
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int UpdateNTPNetParam(ST_NET_PARAM stNetParam);

/**
 @if Chinese
	* @brief 	初始化NTP服务参数
	* @param[in]	stSyncTimeIn	-	参考ST_SYNC_TIME_IN结构体
	* @return		0			-	成功
	* @return		其它		-	失败
 @else
	* @brief	 initialize NTP service parameters
	* @param[in]	stSyncTimeIn	-	reference ST_SYNC_TIME_IN structure
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int InitSyncPosTime(ST_SYNC_TIME_IN stSyncTimeIn);

/**
 @if Chinese
	* @brief 	启动NTP任务
	* @note  	若更新成功周期为6小时;若更新失败周期为1小时
	* @param[in]	runnow	-	0:不立即执行，等到更新周期到了再执行NTP更新;<br>
								1:立即执行NTP更新，不检查更新周期是否达到;
	* @return		0			-	成功
	* @return		其它		-	失败
 @else
	* @brief 	start NTP task
	* @note 	 if the update is successful, the cycle is 6 hours; if the update fails, the period is 1 hour
	* @param[in]	runnow	-	0:do not execute immediately, wait until the update cycle is up; <br>
								1:execute NTP update immediately without checking whether the update cycle is reached;
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int StartSyncPosTime(int runnow);

/**
 @if Chinese
	* @brief 	获取最后一次同步结果
	* @return		E_SYNC_TIME_RESULT	-	参考E_SYNC_TIME_RESULT枚举
 @else
	* @brief 	get the last synchronization result
	* @return		E_SYNC_TIME_RESULT	-	reference E_SYNC_TIME_RESULT
 @endif
*/ 
extern E_SYNC_TIME_RESULT GetLastSyncTimeResult(void);


#endif
