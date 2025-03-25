/**
 @if Chinese
	 * @brief       此模块用于描述 <strong>LCD模块</strong> 相关的接口
	 * @par 文件    lcd.h
	 * @author
	 * @date        2018/11/09
	 * @version     1.0.1
	 * @remarks        Change History:
	 * 日期          | 作者            | 描述
	 * ------------- | --------------- | ---------------------
	 * 2018/11/09    | Jezz Lin        | 创建文件
	 * 2022/04/21    | Wenming         | 增加英文注释
 @else	 
	 * @brief       This module is used to describe <strong>Lcd</strong> interfaces module
	 * @par file   lcd.h
	 * @author
	 * @date        2018/11/09
	 * @version     1.0.1
	 * @remarks        Change History:
	 * Date          | Author          | Desc
	 * ------------- | --------------- | ----
	 * 2018/11/09    | Jezz Lin        | Create file
	 * 2022/04/21    | Wenming         | Add English description	 
 @endif	 
*/


/**
 @if Chinese
	* @defgroup LCD  LCD显示
@else
	* @defgroup LCD  LCD
@endif
 * @{
*/
// caution, doxygen defgroup header and footer and been both auto generated!!!


#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "linuxtypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*是否有必要导出到应用层? */
#define     SCREEN_DIR_0            0           /**< @if Chinese LCD的显示方向,正向输出		@else	LCD display direction, positive output	@endif*/
#define     SCREEN_DIR_180          1           /**< @if Chinese LCD的显示方向,翻转180度输出@else  LCD display direction, flip the output 180 degrees @endif*/

#define     SCR_WIDTH               ({uint32_t w;     \
                                        uint32_t h;   \
                                        uint32_t b;   \
                                        lcd_get_size(&h, &w, &b);   \
                                        w;})    /**< @if Chinese LCD的宽度像素 @else 	LCD width pixels	@endif*/
#define     SCR_HEIGHT              ({uint32_t w;     \
                                        uint32_t h;   \
                                        uint32_t b;   \
                                        lcd_get_size(&h, &w, &b);   \
                                        h;})    /**< @if Chinese LCD的高度像素 @else 	LCD height pixels	@endif*/
										
//  lcdDisplay显示模式
#define     DISP_ASCII              (0   )      /**<@if Chinese 小字体显示(5*7) @else	Small font display (5*7)	@endif*/
#define     DISP_CFONT              (1<<0)      /**<@if Chinese 大字体显示(8*16) @else	Large font display (8*16)	@endif*/
#define     DISP_CLRLINE            (1<<5)      /**<@if Chinese 清除显示占用的行 @else	Clear lines occupied by the display	@endif*/
#define     DISP_MEDIACY            (1<<6)      /**<@if Chinese 居中显示 @else	display centered	@endif*/
#define     DISP_REVERSE            (1<<7)      /**<@if Chinese 反白显示 @else	The white shows	@endif*/
#define     DISP_INVLINE            (1<<4)      /**<@if Chinese 整行反白显示 @else	The entire line is displayed in reverse white	@endif*/
#define     DISP_FLIP               (1<<8)      /**<@if Chinese 当行显示也执行flip @else 	The entire line display and execute	@endif*/

//  图标控制
#define     ICON_PHONE              1           /**<@if Chinese 电话 @else	phone	@endif*/
#define     ICON_SIGNAL             2           /**<@if Chinese 信号 @else	wireless signal	@endif*/
#define     ICON_PRINTER            3           /**<@if Chinese 打印机 @else printer @endif*/
#define     ICON_ICCARD             4           /**<@if Chinese IC卡 @else	smart card 	@endif*/
#define     ICON_LOCK               5           /**<@if Chinese lock 锁 @else	lock 	@endif*/
#define     ICON_BATTERY            6           /**<@if Chinese 电池图标 @else	The battery icon	@endif*/
#define     ICON_UP                 7           /**<@if Chinese 向上 @else	up 	@endif*/
#define     ICON_DOWN               8           /**<@if Chinese 向下 @else	down	@endif*/
#define     ICON_LINK               9           /**<@if Chinese 连接图标 @else	Connection icon	@endif*/
#define     ICON_WIFI               10      	/**<@if Chinese wifi图标 @else	Wifi icon	@endif*/
#define     CLOSEICON               0           /**<@if Chinese 关闭图标[针对所有图标] @else	Close ICONS [for all ICONS]	@endif*/
#define     OPENICON                1           /**<@if Chinese 显示图标[针对打印机、IC卡、锁、电池、向上、向下] @else	Display ICONS [for printers, IC cards, locks, batteries, up, down]	@endif*/

#if 0
//  串输入控制和返回值
#define     KB_MAXLEN               256         /**<@if Chinese  字符串串输入最大允许输入的长度 @else Character string Input Maximum length allowed	@endif*/
#define     KB_EN_REVDISP           0x01        /**<@if Chinese  1（0） 正（反）显示 @else	1 (0) positive (negative) display	@endif*/
#define     KB_EN_FLOAT             0x02        /**<@if Chinese  1（0） 有（否）小数点 @else	1 (0) has (no) decimal point	@endif*/
#define     KB_EN_SHIFTLEFT         0x04        /**<@if Chinese  1（0） 左（右）对齐输入 @else	1 (0) align the input left (right)	@endif*/
#define     KB_EN_CRYPTDISP         0x08        /**<@if Chinese  1（0） 是（否）密码方式 @else	1 (0) Yes (no) Password	@endif*/
#define     KB_EN_CHAR              0x10        /**<@if Chinese  1（0） 能（否）输字符 @else	1 (0) can (no) type characters	@endif*/
#define     KB_EN_NUM               0x20        /**<@if Chinese  1（0） 能（否）输数字 @else	1 (0) can (no) enter numbers	@endif*/
#define     KB_EN_BIGFONT           0x40        /**<@if Chinese  1（0） 大（小）字体 @else	1 (0) large (small) font	@endif*/
#define     KB_EN_PRESETSTR         0x80        /**<@if Chinese  1（0） 是（否）允许预设的字符串 @else	1 (0) Yes (no) Default string allowed	@endif*/
#define     KB_EN_NEWLINE           0x100       /**<@if Chinese  1（0） 是（否）允许左对齐输入换行显示 @else	1 (0) Yes (no) Allows left-aligned input newline display	@endif*/
#define     KB_EN_HEX               0x200       /**<@if Chinese  1（0） 是（否）只能输入16进制数据 @else	1 (0) Yes (no) Only hexadecimal data can be entered	@endif*/

//  预设几组常用的输入控制模式
#define     KB_BIG_ALPHA            0x1F5       /**<@if Chinese  大字体字符串输入 @else	Large font string input	@endif*/
#define     KB_BIG_NUM              0x1E5       /**<@if Chinese  大字体数字串输入 @else	Large font number string input	@endif*/
#define     KB_BIG_PWD              0x6D        /**<@if Chinese  大字体密码输入 @else	Large font password input	@endif*/
#define     KB_SMALL_ALPHA          0x1B5       /**<@if Chinese  小字体字符串输入 @else	Small font string input	@endif*/
#define     KB_SMALL_NUM            0x1A5       /**<@if Chinese  小字体数字串输入 @else	Small font number string input	@endif*/
#define     KB_SMALL_PWD            0x2D        /**<@if Chinese  小字体密码输入 @else	Small font password input	@endif*/
#define     KB_CANCEL               -1          /**<@if Chinese  字符串串输入被用户按取消键退出 @else	String input is cancelled by the user	@endif*/
#define     KB_TIMEOUT              -2          /**<@if Chinese  字符串输入超时退出 @else	String input timed out	@endif*/
#define     KB_ERROR                -3          /**<@if Chinese  字符串输入参数非法 @else	The string input parameter is invalid	@endif*/
#endif

//  背光模式
#define     LIGHT_OFF_TEMP          0           /**<@if Chinese  背光临时关闭(对于定时模式用) @else	Backlight temporarily off (for timing mode)	@endif*/
#define     LIGHT_TIMER_MODE        1           /**<@if Chinese  背光定时模式 @else	Backlit timing mode	@endif*/
#define     LIGHT_ON_MODE           2           /**<@if Chinese  背光常开模式 @else	Backlight normally open mode	@endif*/
#define     LIGHT_OFF_MODE          3           /**<@if Chinese  背光常关模式 @else	Backlight normally off mode	@endif*/

#ifndef ICON_OFF
#define ICON_OFF                    0
#define ICON_ON                     !ICON_OFF
#endif

#define UP_ICON                     122
#define DOWN_ICON                   126

#define LINE_WRAP                   1 /**<@if Chinese 自动换行 @else	Word wrap	@endif*/
#define NO_WRAP                     0 /**<@if Chinese 非自动换行@else	Non word wrap	@endif*/

#define NTD_ICON_VOLUME             3         /**<@if Chinese 音量 @volume	@endif*/

/**
@if Chinese
* @brief  设置图标显示关闭
* @param[in]	icon_no	-	需要控制的图标
* @param[in]	mode	
				- 1 显示<br>
				- 0 关闭
@else
* @brief  Set the icon display to be off
* @param[in]	icon_no	-	ICONS to control
* @param[in]	mode:
				- 1 display<br>
				- 0 no display
@endif
 */
void lcd_set_icon(int icon_no, int mode);

/**
@if Chinese
	* @brief  刷新显示内容
@else
	* @brief  Refresh the display
@endif
 */
void lcd_flip(void);

/**
@if Chinese
	* @brief  同步刷新显示内容
	* @retval  -1  失败
	* @retval  0   成功
@else
	* @brief  Synchronously refresh the display content
	* @retval  -1  fail
	* @retval  0   success
@endif	
 */
int lcd_flip_sync(void);

/** 
@if Chinese
	 * @brief  刷新主屏幕区域(状态栏除外)的显示内容
	 * @retval  -1  失败
	 * @retval  0   成功
@else
	 * @brief  Refreshes the display content of the main screen area (except the status bar)
	 * @retval  -1  fail
	 * @retval  0   success
@endif	 
 */
int lcd_flip_region(void);

/** 
@if Chinese
	 * @brief  获取lcd显示区域信息
	 * @param[out]	height	-	显示区域高
	 * @param[out]	width	-	显示区域宽
	 * @param[out]	bits	-	说明比特数/像素，其值为1、4、8、16、24
	 * @retval  -1  失败
	 * @retval  0   成功
@else	 
	 * @brief  Obtain information about the LCD display area
	 * @param[out]	height	-	Display area height
	 * @param[out]	width	-	Display area width
	 * @param[out]	bits	-	Bits per pixel, the value is 1, 4, 8, 16, and 24
	 * @retval  -1  fail
	 * @retval  0   success
@endif		 
 */
int lcd_get_size(uint32_t *height, uint32_t *width, uint32_t *bits);

/**
@if Chinese
	 * @brief  获取屏幕除状态栏外的显示区域的缓存（起始）地址
	 * @return
			- NULL    获取失败
			- 非NULL  成功，返回对应的缓存首地址
@else	 
	 * @brief  Gets the cache (start) address of the display area of the screen except the status bar
	 * @return
			- NULL	-	fial
			- !NULL	-	Success, returns the corresponding cache header address
@endif		 
 */
const uint8_t *lcd_get_buffer_addr(void);

/**
@if Chinese
	* @brief  获取屏幕显示状态栏的高度
	* @return
		- -1   失败，
		- > 0  成功，返回状态的高度值
	* @note   单位: 像素
@else	
	* @brief  Gets the height of the screen display status bar
	* @return
		- -1   fail，
		- > 0  success，Returns the height value of the status
	* @note   Unit: pixels
@endif	
*/
int lcd_get_status_bar_height(void);

/**
@if Chinese
	 * @brief  获取系统默认显示的font指针
	 * @return
			- NULL    获取失败
			- 非NULL  成功，返回对应的font指针
@else	 
	 * @brief  Gets the font pointer displayed by default
	 * @return
			- NULL    fail
			- !NULL   success，Returns the corresponding font pointer
@endif	 
 */
void *lcd_get_sys_font(void);

/**
@if Chinese
	 * @brief  获取系统整屏的paint指针
@else		 
	 * @brief  Gets the paint pointer that is displayed by full screen
@endif	 	 
 */
void *lcd_get_sys_paint_full(void);

/**
@if Chinese
	 * @brief  获取系统默认显示的paint指针
@else		 
	 * @brief  Gets the paint pointer that is displayed by default
@endif	 	 
 */
void *lcd_get_sys_paint(void);
/** 
@if Chinese
	 * @brief  获取状态栏icon显示的paint指针 
@else		 
	 * @brief  Gets the paint pointer displayed on the status bar icon
 @endif
 */
void * lcd_get_sys_paint_icon(void);

/**
@if Chinese
	 * @brief   获取LCD背光状态
	 * @retval  1   LCD亮
	 * @retval  0   LCD灭
	 * @retval  -1  调用失败
@else 
	 * @brief   Obtain LCD backlight status
	 * @retval  1   turn on
	 * @retval  0   turn off
	 * @retval  -1  fail
 @endif 
 */
int lcd_get_backlight_status(void);
    
/**
@if Chinese
	 * @brief       设置屏幕背光时间
	 * @param[in]	second	-	秒数(限制5 ~ 2000之间)
	 * @retval      0       成功
	 * @retval      -1      调用失败
@else	 
	 * @brief       Set the screen backlight time
	 * @param[in]	second	-	Seconds (limited between 5 and 2000)
	 * @retval      0       success
	 * @retval      -1      fail
@endif 
 */
int lcd_set_backlight_time(int second);


/**
@if Chinese
	 * @brief       余额显示
	 * @param[in]	mode:0 预留(断码屏上有单位的作为是否显示单位)
	 * @param[in]  str:余额（字符串格式） 如:”11.23”
	 * @retval      none
@else		 
	 * @brief       Balance display
	 * @param[in]	mode:0 reserved (whether to display units if there are units on the code screen)
	* @param[in]    str:Balance (string format) such as "11.23"
	 * @retval      none
@endif 	 
 */
void ntd_display(uint32_t mode, char *str);

/**
@if Chinese
	 * @brief       控制段码屏的图标
	 * @param[in]	icon_idx:要控制的图标索引
	 * @param[in]   val:图标等级
	 * @retval      none
@else		 
	 * @brief       control digital icons
	 * @param[in]	icon idx: Index of icons to control
	* @param[in]:   val: Icon level
	 * @retval      none
@endif  
 */
void ntd_icon_control(uint32_t icon_idx, uint32_t val);


/**
@if Chinese
	 * @brief       获取断码屏数字的数量
	 * @retval      none
@else		 
	 * @brief       Get number of digital
	 * @retval      none
@endif 	 
 */
int ntd_get_number_count(void);


/**
@if Chinese
	 * @brief  设置字符的显示规则，对应规则请看sdk 头文件对应位置的注释
	 参数value的对应规则如下:
  		   bit0
  		   -----
  	 bit6 | 	| bit1	 
  		  |bit2 |  
  		  |-----|
  		  | 	|
  	 bit3 | 	| bit5
  		   ----- 
  		   bit4
   	例如: 添加字符'A',  根据上面规则'	  A' ===>>> 0b1101111 则调用ntd_set_disp_map('A', 0b1101111)即可添加
    添加后依然使用ntd_display进行显示，此时就可以ntd_display(0, "11A2")显示出'11A2'字样;
	 * @param[in]	key:字符
	 * @param[in]   value:该字符对应的显示
	 * @retval      none
@else		 
	 * @brief       set display rule of char, For the corresponding rules, 
	 see the comments in the corresponding location of the sdk header file.
	 rule of param value as sample:
		  bit0
		  -----
	bit6 |	   | bit1	
		 |bit2 |  
		 |-----|
		 |	   |
	bit3 |	   | bit5
		  ----- 
		  bit4
     sample: add char 'A',  According to the above rules:'A' ===>>> 0b1101111 so calling function ntd_set_disp_map('A', 0b1101111) 
     can adding a map rule,
     then can use ntd_display to displey，like this :ntd_display(0, "11A2") can display '11A2'pattern.
	* @param[in]	key:char
	* @param[in]    value: rule
	 * @retval      none
@endif  
 */

void ntd_set_disp_map(char key, uint8_t value);

/**
@if Chinese
	 * @brief       设置屏幕背光亮度
	 * @param[in]	brightness	-	亮度(限制5 ~ 100之间)
	 * @retval      0       成功
	 * @retval      -1      调用失败
@else		 
	 * @brief       Set the screen backlight brightness
	 * @param[in]	brightness	-	Brightness (limit 5 ~ 100)
	 * @retval      0       success
	 * @retval      -1      fail
@endif 	 
 */
int lcd_set_brightness(int brightness);

/**
@if Chinese
	 * @brief 设置屏幕方向
	 * @param[in]	direction	
					- SCREEN_DIR_0:正常显示 <br>
					- SCREEN_DIR_180:旋转180度
@else		 
	 * @brief Set screen Orientation
	 * @param[in]	direction	
					- SCREEN_DIR_0:The normal display<br>
					- CREEN_DIR_180:Rotate 180 degrees
@endif 	 
 **/
void lcd_set_screen_rotation(int direction);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  __LCD_H__ */

/** @} */

