
/**
 @if Chinese
	 * @brief       ��ģ���������� <strong>������ģ��</strong> ��صĽӿ�
	 * @par �ļ�    beeper.h
	 * @author
	 * @date        2019/01/22
	 * @version     1.0.1
	 * @remarks        Change History:
	 * ����          | ����            | ����
	 * ------------- | --------------- | ----
	 * 2019/01/22    | liluchang       | �����ļ�
	 * 2022/04/20    | Wenming         | ����Ӣ��ע��
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
	* @defgroup beeper ������
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
	@brief ϵͳ����������
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
	 * @brief          ϵͳ����������
	 * @param [in]     frequency - ����Ƶ��
	 * @param [in]     keepms    - ������ʱ�� ��λ: ms
 @else
	 * @brief          beeps at specified frequency and lasts for specified time
	 * @param [in]     frequency - the frequency to beep
	 * @param [in]     keepms    - the beeper keep time, unit: ms
 @endif	 
*/
void sys_beep(unsigned int frequency, unsigned int keepms);

/**
@if Chinese
	 * @brief          beep���úͽ���
	 * @param [in]     enable - ��0:���� 0:����
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


