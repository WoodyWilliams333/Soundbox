
#ifndef _NTP_TIME_H_
#define _NTP_TIME_H_


//���ܣ�
//ͨ��NTP��ȡ����ʱ�䲢ͬ��������ʱ��

/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app ntptimeģ��</strong> ��صĽӿ�
	 * @par �ļ�    ntptime.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-05-05    | 1.0.1        | lydia         | ����Ӣ��ע�� 
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
	int *ComType;		/**< @if Chinese ͨѶ���� ָ�� 01-WIFI 02-GPRS @else communication type(pointer) 01-WIFI 02-GPRS @endif */
	char *pFileSaveDir;	/**< @if Chinese ͬ��ʱ���ļ�����Ŀ¼(һ����Ӧ��Ŀ¼) @else synchronization time file storage directory (generally fill in the application directory) @endif */	
	int timezone;		/**< @if Chines  ʱ�� @else timezone @endif */			
}ST_SYNC_TIME_IN;

typedef struct{
	char apn[20];		/**< sim apn */
	char simuid[20];	/**< sim user id */
	char simpwd[20];	/**< sim user password */
}ST_NET_PARAM;

/*!
 @if Chinese
  * @brief  ��ö�������г���ͬ��ʱ����.
@else  
  * @brief  This enumerated type lists the synchronization time results.
@endif
*/
typedef enum{
	sync_ok = 0,		/**< @if Chinese ͬ���ɹ� @else synchronization succeeded @endif */	
	sync_failed,		/**< @if Chinese ͬ��ʧ�� @else synchronization failed @endif */		
	sync_not_support,	/**< @if Chinese ��֧��ͬ��(�̼��汾̫��) @else synchronization is not supported (firmware version is too low) @endif */
	sync_working,		/**< @if Chinese ͬ���� @else synchronizing @endif */	

	sync_unknow = 0xFF	/**< @if Chinese ͬ�����δ֪ @else the synchronization result is unknown @endif */	
}E_SYNC_TIME_RESULT;


/**
 @if Chinese
	* @brief 	����NTP���������,��δ���ģ�Ĭ�ϲ���Ϊ��apn-"CMNET",uid-"CARD",pwd-"CARD"
	* @param[in]	stNetParam		-	�ο�ST_NET_PARAM�ṹ��
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
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
	* @brief 	��ʼ��NTP�������
	* @param[in]	stSyncTimeIn	-	�ο�ST_SYNC_TIME_IN�ṹ��
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
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
	* @brief 	����NTP����
	* @note  	�����³ɹ�����Ϊ6Сʱ;������ʧ������Ϊ1Сʱ
	* @param[in]	runnow	-	0:������ִ�У��ȵ��������ڵ�����ִ��NTP����;<br>
								1:����ִ��NTP���£��������������Ƿ�ﵽ;
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
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
	* @brief 	��ȡ���һ��ͬ�����
	* @return		E_SYNC_TIME_RESULT	-	�ο�E_SYNC_TIME_RESULTö��
 @else
	* @brief 	get the last synchronization result
	* @return		E_SYNC_TIME_RESULT	-	reference E_SYNC_TIME_RESULT
 @endif
*/ 
extern E_SYNC_TIME_RESULT GetLastSyncTimeResult(void);


#endif
