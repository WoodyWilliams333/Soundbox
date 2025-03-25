/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app timeutilsģ��</strong> ��صĽӿ�
	 * @par �ļ�    timeutils.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-05-05    | 1.0.1        | lydia         | ����Ӣ��ע�� 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app timeutils </strong>  module
	 * @par file    timeutils.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yangjing      | create file
	 * 2022-05-05    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup timeutils ʱ�亯��
 @else
	@defgroup timeutils timeutils
 @endif
 * @{
*/
#ifndef _TIME_UTILS_H_
#define _TIME_UTILS_H_

/**
 @if Chinese
	* @brief 	��������Ƿ�Ϸ�
	* @param[in]	sdate		-	���ڣ���ʽΪ"YYYYMMDD"
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
 @else
	* @brief 	check if the date is legal
	* @param[in]	sdate		-	date,format is "YYYYMMDD"
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int pub_check_date(char *sdate);

/**
 @if Chinese
	* @brief 	���ʱ���Ƿ�Ϸ�
	* @param[in]	sTime		-	ʱ�䣬��ʽΪ"hhmmss"
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
 @else
	* @brief 	check if the time is legal
	* @param[in]	sTime		-	time,format is "hhmmss"
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/  
extern int pub_check_time(char *sTime);

/**
 @if Chinese
	* @brief 	��������Ƿ�Ϸ�
	* @param[in]	sYYMM		-	���£���ʽΪ"YYMM"
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
 @else
	* @brief 	check if the time is legal
	* @param[in]	sYYMM		-	years,format is "YYMM"
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/  
extern int pub_check_yymm(char *sYYMM);

/**
 @if Chinese
	* @brief 	����Ƿ�ﵽ��ʱʱ��(sys_get_timer_count��������)
	* @param[in]	time_out		-	��ʱʱ�䣬��λ��
	* @param[in]	start_time	-	��sys_get_timer_count��ȡ�ĵ�ǰʱ��
	* @return		0			-	δ��ʱ
	* @return		E_TRANS_TIMEOUT	-	��ʱ
 @else
	* @brief 	check if the time is timeout(sys_get_timer_count)
	* @param[in]	time_out		-	timeout(s)
	* @param[in]	start_time	-	get the current time by sys_get_timer_count
	* @return		0			-	not timeout
	* @return		E_TRANS_TIMEOUT	-	timeout
 @endif
*/ 
extern int pub_CheckTimeOut(int time_out, unsigned long start_time);

/**
 @if Chinese
	* @brief 	����Ƿ�ﵽ��ʱʱ��(gettimeofday��������,��׼ȷ)
	* @param[in]	timer		-	��ʼʱ�䣬ͨ��gettimeofday��ȡ
	* @param[in]	timeout		-	��ʱʱ�䣬��λ����
	* @return		ture		-	��ʱ
	* @return		false 	-	δ��ʱ
 @else
	* @brief 	check if the time is timeout(gettimeofday)
	* @param[in]	timer		-	get the current time by gettimeofday
	* @param[in]	timeout		-	timeout(ms)
	* @return		ture		-	timeout
	* @return		false		-	not timeout
 @endif
*/ 
extern char pub_check_timems_out(struct timeval* timer, int timeout);



#endif

