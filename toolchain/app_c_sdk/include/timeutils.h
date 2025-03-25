/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app timeutils模块</strong> 相关的接口
	 * @par 文件    timeutils.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yangjing      | 创建文件
	 * 2022-05-05    | 1.0.1        | lydia         | 增加英文注释 
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
	@defgroup timeutils 时间函数
 @else
	@defgroup timeutils timeutils
 @endif
 * @{
*/
#ifndef _TIME_UTILS_H_
#define _TIME_UTILS_H_

/**
 @if Chinese
	* @brief 	检测日期是否合法
	* @param[in]	sdate		-	日期，格式为"YYYYMMDD"
	* @return		0			-	成功
	* @return		其它		-	失败
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
	* @brief 	检测时间是否合法
	* @param[in]	sTime		-	时间，格式为"hhmmss"
	* @return		0			-	成功
	* @return		其它		-	失败
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
	* @brief 	检测年月是否合法
	* @param[in]	sYYMM		-	年月，格式为"YYMM"
	* @return		0			-	成功
	* @return		其它		-	失败
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
	* @brief 	检测是否达到超时时间(sys_get_timer_count函数计算)
	* @param[in]	time_out		-	超时时间，单位秒
	* @param[in]	start_time	-	用sys_get_timer_count获取的当前时间
	* @return		0			-	未超时
	* @return		E_TRANS_TIMEOUT	-	超时
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
	* @brief 	检测是否达到超时时间(gettimeofday函数计算,更准确)
	* @param[in]	timer		-	初始时间，通过gettimeofday获取
	* @param[in]	timeout		-	超时时间，单位毫秒
	* @return		ture		-	超时
	* @return		false 	-	未超时
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

