
/**
 @if Chinese
	 * @brief       此模块用于描述 <strong>蜂鸣器模块</strong> 相关的接口
	 * @par 文件    beeper.h
	 * @author
	 * @date        2019/01/22
	 * @version     1.0.1
	 * @remarks        Change History:
	 * 日期          | 作者            | 描述
	 * ------------- | --------------- | ----
	 * 2019/01/22    | liluchang       | 创建文件
	 * 2022/04/20    | Wenming         | 增加英文注释
 @else	 
	 * @brief       This module is used to describe <strong> Beeper </strong> interfaces module
	 * @par File    beeper.h
	 * @author
	 * @date        2019/01/22
	 * @version     1.0.1
	 * @remarks        Change History:
	 * Date          | Author          | Desc
	 * ------------- | --------------- | ----
	 * 2019/01/22    | liluchang       | Create file
	 * 2022/04/20    | Wenming         | Add English description
 @endif	 
*/


/**
@if Chinese
	* @defgroup beeper 蜂鸣器
@else	
	* @defgroup beeper Beeper
@endif
 * @{
*/
// caution, doxygen defgroup header and footer and been both auto generated!!!


#ifndef __BEEPER_H__
#define __BEEPER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief 系统蜂鸣器参数
 @else
	@brief beeper param
 @endif
*/
struct kbdset {
    int         beep_enable;	/**< enable the beep */
    uint16_t    beep_freq;		/**< beep_freq */
    uint16_t    beep_time;		/**< beep_time */
    int         backlight;      /**< Key backlight time */
    int         feed_enable;    /**< Key to enter the paper */
    int         kbd_light;      /**< Keyboard light status */
};

/**
@if Chinese
	 * @brief          系统蜂鸣器声音
	 * @param [in]     frequency - 按键频率
	 * @param [in]     keepms    - 蜂鸣器时间 单位: ms
 @else
	 * @brief          beeps at specified frequency and lasts for specified time
	 * @param [in]     frequency - the frequency to beep
	 * @param [in]     keepms    - the beeper keep time, unit: ms
 @endif	 
*/
void sys_beep(unsigned int frequency, unsigned int keepms);

/**
@if Chinese
	 * @brief          beep启用和禁用
	 * @param [in]     enable - 非0:启用 0:禁用
 @else	 
	 * @brief          beep enable
	 * @param [in]     enable - !0:enable; 0:disable
 @endif		 
*/
void sys_beep_enable(int enable);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  __BEEPER_H__ */

/** @} */


