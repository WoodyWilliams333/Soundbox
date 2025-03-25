/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app timer模块</strong> 相关的接口
	 * @par 文件    apptimer.h
	 * @author		yangjing
	 * @date        2020-10-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-10-28    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-26    | 1.0.1        | wenming       | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app timer </strong>  module
	 * @par file    apptimer.h
	 * @author		yangjing
	 * @date        2020-10-28
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-10-28    | 1.0.0        | yanjing       | create file
	 * 2022-04-26    | 1.0.1        | wenming       | Add English description
 @endif 
*/

/*!
 @if Chinese
	* @addtogroup app_timer 定时器
 @else 
	* @addtogroup app_timer timer
 @endif 
 * @{
*/ 
 
#ifndef _APP_TIMER_H_
#define _APP_TIMER_H_

#define TIMER1_BASE_EXPIRES  500        /**<@if Chinese 定时器1精度ms @else	Timer 1 precision MS	@endif*/
#define TIMER2_BASE_EXPIRES  1000       /**<@if Chinese 定时器2精度ms @else	Timer 2 precision MS	@endif*/

typedef void (*timer_callback_fc)(void *);	/**<@if Chinese 定时器执行函数回调	@else	The timer performs function callbacks	@endif*/

/**
@if Chinese
 * @brief  添加软件定时器1
 * @param[in]	func		-	定时器回调函数指针
 * @param[in]	para		-	定时器回调函数参数指针
 * @return		<= 0   		-	失败
 * @return		>0    		-	返回分配的定时器ID
 * @note 		由于定时器是以线程实现，请注意参数指针的有效性 
@else   
 * @brief  Adding a Software Timer 1
 * @param[in]	func		-	Timer callback function pointer
 * @param[in]	para		-	Timer callback function parameter pointer
 * @return		<= 0   		-	Faild
 * @return		>0     		-	Returns the assigned timer ID
 * @note 	Since timers are implemented in threads, be aware of the validity of the parameter pointer
@endif  
 */
int app_timer1_append(timer_callback_fc func, void *para);

/**
@if Chinese
 * @brief  启动定时器1
 * @param[in]	timerid		-	分配的定时器ID
 * @param[in]   expires		-	定时器定时周期(ms)
 * @return 		0    		-	成功
 * @return 		其它    	-	失败
@else 
 * @brief  Start timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @param[in]   expires		-	Timer Timing period (ms)
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
 @endif  
 */
int app_timer1_start(int timerid, unsigned long expires);

/**
@if Chinese
 * @brief  停止定时器1
 * @param[in]	timerid		-	分配的定时器ID
 * @return 		0    		-	成功
 * @return 		其它    	-	失败
@else  
 * @brief  Stop timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
@endif 
 */
int app_timer1_stop(int timerid);

/**
@if Chinese
 * @brief  删除定时器1
 * @param[in]	timerid		-	分配的定时器ID
 * @return 		0    		-	成功
 * @return 		其它    	-	失败
@else 
 * @brief  Deleting timer 1
 * @param[in]	timerid		-	ID of the assigned timer
 * @return 		0    		-	Successfull
 * @return 		other    	-	Faild
@endif 
 */
int app_timer1_delete(int timerid);

/**
@if Chinese
 * @brief  检测定时器1是否激活
 * @param[in]	timerid		-	分配的定时器ID
 * @return 		app_true   		-	已激活
 * @return 		app_false   	-	未激活或不存在
@else  
 * @brief  Check whether timer 1 is activated
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		app_true   		-	activated
 * @return		app_false  		-	Inactive or not present
@endif 
 */
appbool app_timer1_check_active(int timerid);

/**
@if Chinese
 * @brief  添加软件定时器2
 * @param[in]	func		-	定时器回调函数指针
 * @param[in]   para		-	定时器回调函数参数指针,由于定时器是一线程实现，请注意参数指针的有效性
 * @return		<= 0    	-	失败
 * @return		>0     		-	返回分配的定时器ID
@else   
 * @brief  Adding a Software Timer 2
 * @param[in]	func		-	Timer callback function pointer
 * @param[in]   para		-	Timer callback function parameter pointer, since timer is a thread implementation, please note the validity of parameter pointer
 * @return		<= 0  		-	fail
* @return		>0     		-	Returns the assigned timer ID
@endif  
 */
int app_timer2_append(timer_callback_fc func, void *para);

/**
@if Chinese
 * @brief  启动定时器2
 * @param[in]	timerid		-	分配的定时器ID
 * @param[in]   expires		-	定时器定时周期(ms)
 * @return		0			-	成功  
 * @return		其它		-	失败
@else   
 * @brief  Start timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @param[in]   expires		-	Timer Timing period (ms)
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif  
 */
int app_timer2_start(int timerid, unsigned long expires);

/**
@if Chinese
 * @brief  停止定时器2
 * @param[in]	timerid		-	分配的定时器ID
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  Stop timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif 
 */
int app_timer2_stop(int timerid);

/**
@if Chinese
 * @brief  删除定时器2
 * @param[in]	timerid		-	分配的定时器ID
 * @return		0			-	成功  
 * @return		其它		-	失败
@else 
 * @brief  Deleting Timer 2
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		0     		-	Successfull
 * @return		other   	-	Faild
@endif 
 */
int app_timer2_delete(int timerid);

/**
@if Chinese
 * @brief  检查定时器2是否被激活
 * @param[in]	timerid		-	分配的定时器ID
 * @return 		app_true   		-	已激活
 * @return 		app_false   	-	未激活或不存在
@else 
 * @brief  Check whether timer 2 is activated
 * @param[in]	timerid		-	ID of the assigned timer
 * @return		app_true  	  	-	activated
 * @return		app_false   	-	Inactive or not present
@endif 
 */
appbool app_timer2_check_active(int timerid);

#endif