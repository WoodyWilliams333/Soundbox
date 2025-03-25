/**
 @if Chinese
	 * @brief       ��ģ���������� <strong>LCDģ��</strong> ��صĽӿ�
	 * @par �ļ�    lcd.h
	 * @author
	 * @date        2018/11/09
	 * @version     1.0.1
	 * @remarks        Change History:
	 * ����          | ����            | ����
	 * ------------- | --------------- | ---------------------
	 * 2018/11/09    | Jezz Lin        | �����ļ�
	 * 2022/04/21    | Wenming         | ����Ӣ��ע��
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
	* @defgroup LCD  LCD��ʾ
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

/*�Ƿ��б�Ҫ������Ӧ�ò�? */
#define     SCREEN_DIR_0            0           /**< @if Chinese LCD����ʾ����,�������		@else	LCD display direction, positive output	@endif*/
#define     SCREEN_DIR_180          1           /**< @if Chinese LCD����ʾ����,��ת180�����@else  LCD display direction, flip the output 180 degrees @endif*/

#define     SCR_WIDTH               ({uint32_t w;     \
                                        uint32_t h;   \
                                        uint32_t b;   \
                                        lcd_get_size(&h, &w, &b);   \
                                        w;})    /**< @if Chinese LCD�Ŀ������ @else 	LCD width pixels	@endif*/
#define     SCR_HEIGHT              ({uint32_t w;     \
                                        uint32_t h;   \
                                        uint32_t b;   \
                                        lcd_get_size(&h, &w, &b);   \
                                        h;})    /**< @if Chinese LCD�ĸ߶����� @else 	LCD height pixels	@endif*/
										
//  lcdDisplay��ʾģʽ
#define     DISP_ASCII              (0   )      /**<@if Chinese С������ʾ(5*7) @else	Small font display (5*7)	@endif*/
#define     DISP_CFONT              (1<<0)      /**<@if Chinese ��������ʾ(8*16) @else	Large font display (8*16)	@endif*/
#define     DISP_CLRLINE            (1<<5)      /**<@if Chinese �����ʾռ�õ��� @else	Clear lines occupied by the display	@endif*/
#define     DISP_MEDIACY            (1<<6)      /**<@if Chinese ������ʾ @else	display centered	@endif*/
#define     DISP_REVERSE            (1<<7)      /**<@if Chinese ������ʾ @else	The white shows	@endif*/
#define     DISP_INVLINE            (1<<4)      /**<@if Chinese ���з�����ʾ @else	The entire line is displayed in reverse white	@endif*/
#define     DISP_FLIP               (1<<8)      /**<@if Chinese ������ʾҲִ��flip @else 	The entire line display and execute	@endif*/

//  ͼ�����
#define     ICON_PHONE              1           /**<@if Chinese �绰 @else	phone	@endif*/
#define     ICON_SIGNAL             2           /**<@if Chinese �ź� @else	wireless signal	@endif*/
#define     ICON_PRINTER            3           /**<@if Chinese ��ӡ�� @else printer @endif*/
#define     ICON_ICCARD             4           /**<@if Chinese IC�� @else	smart card 	@endif*/
#define     ICON_LOCK               5           /**<@if Chinese lock �� @else	lock 	@endif*/
#define     ICON_BATTERY            6           /**<@if Chinese ���ͼ�� @else	The battery icon	@endif*/
#define     ICON_UP                 7           /**<@if Chinese ���� @else	up 	@endif*/
#define     ICON_DOWN               8           /**<@if Chinese ���� @else	down	@endif*/
#define     ICON_LINK               9           /**<@if Chinese ����ͼ�� @else	Connection icon	@endif*/
#define     ICON_WIFI               10      	/**<@if Chinese wifiͼ�� @else	Wifi icon	@endif*/
#define     CLOSEICON               0           /**<@if Chinese �ر�ͼ��[�������ͼ��] @else	Close ICONS [for all ICONS]	@endif*/
#define     OPENICON                1           /**<@if Chinese ��ʾͼ��[��Դ�ӡ����IC����������ء����ϡ�����] @else	Display ICONS [for printers, IC cards, locks, batteries, up, down]	@endif*/

#if 0
//  ��������ƺͷ���ֵ
#define     KB_MAXLEN               256         /**<@if Chinese  �ַ��������������������ĳ��� @else Character string Input Maximum length allowed	@endif*/
#define     KB_EN_REVDISP           0x01        /**<@if Chinese  1��0�� ����������ʾ @else	1 (0) positive (negative) display	@endif*/
#define     KB_EN_FLOAT             0x02        /**<@if Chinese  1��0�� �У���С���� @else	1 (0) has (no) decimal point	@endif*/
#define     KB_EN_SHIFTLEFT         0x04        /**<@if Chinese  1��0�� ���ң��������� @else	1 (0) align the input left (right)	@endif*/
#define     KB_EN_CRYPTDISP         0x08        /**<@if Chinese  1��0�� �ǣ������뷽ʽ @else	1 (0) Yes (no) Password	@endif*/
#define     KB_EN_CHAR              0x10        /**<@if Chinese  1��0�� �ܣ������ַ� @else	1 (0) can (no) type characters	@endif*/
#define     KB_EN_NUM               0x20        /**<@if Chinese  1��0�� �ܣ��������� @else	1 (0) can (no) enter numbers	@endif*/
#define     KB_EN_BIGFONT           0x40        /**<@if Chinese  1��0�� ��С������ @else	1 (0) large (small) font	@endif*/
#define     KB_EN_PRESETSTR         0x80        /**<@if Chinese  1��0�� �ǣ�������Ԥ����ַ��� @else	1 (0) Yes (no) Default string allowed	@endif*/
#define     KB_EN_NEWLINE           0x100       /**<@if Chinese  1��0�� �ǣ���������������뻻����ʾ @else	1 (0) Yes (no) Allows left-aligned input newline display	@endif*/
#define     KB_EN_HEX               0x200       /**<@if Chinese  1��0�� �ǣ���ֻ������16�������� @else	1 (0) Yes (no) Only hexadecimal data can be entered	@endif*/

//  Ԥ�輸�鳣�õ��������ģʽ
#define     KB_BIG_ALPHA            0x1F5       /**<@if Chinese  �������ַ������� @else	Large font string input	@endif*/
#define     KB_BIG_NUM              0x1E5       /**<@if Chinese  ���������ִ����� @else	Large font number string input	@endif*/
#define     KB_BIG_PWD              0x6D        /**<@if Chinese  �������������� @else	Large font password input	@endif*/
#define     KB_SMALL_ALPHA          0x1B5       /**<@if Chinese  С�����ַ������� @else	Small font string input	@endif*/
#define     KB_SMALL_NUM            0x1A5       /**<@if Chinese  С�������ִ����� @else	Small font number string input	@endif*/
#define     KB_SMALL_PWD            0x2D        /**<@if Chinese  С������������ @else	Small font password input	@endif*/
#define     KB_CANCEL               -1          /**<@if Chinese  �ַ��������뱻�û���ȡ�����˳� @else	String input is cancelled by the user	@endif*/
#define     KB_TIMEOUT              -2          /**<@if Chinese  �ַ������볬ʱ�˳� @else	String input timed out	@endif*/
#define     KB_ERROR                -3          /**<@if Chinese  �ַ�����������Ƿ� @else	The string input parameter is invalid	@endif*/
#endif

//  ����ģʽ
#define     LIGHT_OFF_TEMP          0           /**<@if Chinese  ������ʱ�ر�(���ڶ�ʱģʽ��) @else	Backlight temporarily off (for timing mode)	@endif*/
#define     LIGHT_TIMER_MODE        1           /**<@if Chinese  ���ⶨʱģʽ @else	Backlit timing mode	@endif*/
#define     LIGHT_ON_MODE           2           /**<@if Chinese  ���ⳣ��ģʽ @else	Backlight normally open mode	@endif*/
#define     LIGHT_OFF_MODE          3           /**<@if Chinese  ���ⳣ��ģʽ @else	Backlight normally off mode	@endif*/

#ifndef ICON_OFF
#define ICON_OFF                    0
#define ICON_ON                     !ICON_OFF
#endif

#define UP_ICON                     122
#define DOWN_ICON                   126

#define LINE_WRAP                   1 /**<@if Chinese �Զ����� @else	Word wrap	@endif*/
#define NO_WRAP                     0 /**<@if Chinese ���Զ�����@else	Non word wrap	@endif*/

#define NTD_ICON_VOLUME             3         /**<@if Chinese ���� @volume	@endif*/

/**
@if Chinese
* @brief  ����ͼ����ʾ�ر�
* @param[in]	icon_no	-	��Ҫ���Ƶ�ͼ��
* @param[in]	mode	
				- 1 ��ʾ<br>
				- 0 �ر�
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
	* @brief  ˢ����ʾ����
@else
	* @brief  Refresh the display
@endif
 */
void lcd_flip(void);

/**
@if Chinese
	* @brief  ͬ��ˢ����ʾ����
	* @retval  -1  ʧ��
	* @retval  0   �ɹ�
@else
	* @brief  Synchronously refresh the display content
	* @retval  -1  fail
	* @retval  0   success
@endif	
 */
int lcd_flip_sync(void);

/** 
@if Chinese
	 * @brief  ˢ������Ļ����(״̬������)����ʾ����
	 * @retval  -1  ʧ��
	 * @retval  0   �ɹ�
@else
	 * @brief  Refreshes the display content of the main screen area (except the status bar)
	 * @retval  -1  fail
	 * @retval  0   success
@endif	 
 */
int lcd_flip_region(void);

/** 
@if Chinese
	 * @brief  ��ȡlcd��ʾ������Ϣ
	 * @param[out]	height	-	��ʾ�����
	 * @param[out]	width	-	��ʾ�����
	 * @param[out]	bits	-	˵��������/���أ���ֵΪ1��4��8��16��24
	 * @retval  -1  ʧ��
	 * @retval  0   �ɹ�
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
	 * @brief  ��ȡ��Ļ��״̬�������ʾ����Ļ��棨��ʼ����ַ
	 * @return
			- NULL    ��ȡʧ��
			- ��NULL  �ɹ������ض�Ӧ�Ļ����׵�ַ
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
	* @brief  ��ȡ��Ļ��ʾ״̬���ĸ߶�
	* @return
		- -1   ʧ�ܣ�
		- > 0  �ɹ�������״̬�ĸ߶�ֵ
	* @note   ��λ: ����
@else	
	* @brief  Gets the height of the screen display status bar
	* @return
		- -1   fail��
		- > 0  success��Returns the height value of the status
	* @note   Unit: pixels
@endif	
*/
int lcd_get_status_bar_height(void);

/**
@if Chinese
	 * @brief  ��ȡϵͳĬ����ʾ��fontָ��
	 * @return
			- NULL    ��ȡʧ��
			- ��NULL  �ɹ������ض�Ӧ��fontָ��
@else	 
	 * @brief  Gets the font pointer displayed by default
	 * @return
			- NULL    fail
			- !NULL   success��Returns the corresponding font pointer
@endif	 
 */
void *lcd_get_sys_font(void);

/**
@if Chinese
	 * @brief  ��ȡϵͳ������paintָ��
@else		 
	 * @brief  Gets the paint pointer that is displayed by full screen
@endif	 	 
 */
void *lcd_get_sys_paint_full(void);

/**
@if Chinese
	 * @brief  ��ȡϵͳĬ����ʾ��paintָ��
@else		 
	 * @brief  Gets the paint pointer that is displayed by default
@endif	 	 
 */
void *lcd_get_sys_paint(void);
/** 
@if Chinese
	 * @brief  ��ȡ״̬��icon��ʾ��paintָ�� 
@else		 
	 * @brief  Gets the paint pointer displayed on the status bar icon
 @endif
 */
void * lcd_get_sys_paint_icon(void);

/**
@if Chinese
	 * @brief   ��ȡLCD����״̬
	 * @retval  1   LCD��
	 * @retval  0   LCD��
	 * @retval  -1  ����ʧ��
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
	 * @brief       ������Ļ����ʱ��
	 * @param[in]	second	-	����(����5 ~ 2000֮��)
	 * @retval      0       �ɹ�
	 * @retval      -1      ����ʧ��
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
	 * @brief       �����ʾ
	 * @param[in]	mode:0 Ԥ��(���������е�λ����Ϊ�Ƿ���ʾ��λ)
	 * @param[in]  str:���ַ�����ʽ�� ��:��11.23��
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
	 * @brief       ���ƶ�������ͼ��
	 * @param[in]	icon_idx:Ҫ���Ƶ�ͼ������
	 * @param[in]   val:ͼ��ȼ�
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
	 * @brief       ��ȡ���������ֵ�����
	 * @retval      none
@else		 
	 * @brief       Get number of digital
	 * @retval      none
@endif 	 
 */
int ntd_get_number_count(void);


/**
@if Chinese
	 * @brief  �����ַ�����ʾ���򣬶�Ӧ�����뿴sdk ͷ�ļ���Ӧλ�õ�ע��
	 ����value�Ķ�Ӧ��������:
  		   bit0
  		   -----
  	 bit6 | 	| bit1	 
  		  |bit2 |  
  		  |-----|
  		  | 	|
  	 bit3 | 	| bit5
  		   ----- 
  		   bit4
   	����: ����ַ�'A',  �����������'	  A' ===>>> 0b1101111 �����ntd_set_disp_map('A', 0b1101111)�������
    ��Ӻ���Ȼʹ��ntd_display������ʾ����ʱ�Ϳ���ntd_display(0, "11A2")��ʾ��'11A2'����;
	 * @param[in]	key:�ַ�
	 * @param[in]   value:���ַ���Ӧ����ʾ
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
     then can use ntd_display to displey��like this :ntd_display(0, "11A2") can display '11A2'pattern.
	* @param[in]	key:char
	* @param[in]    value: rule
	 * @retval      none
@endif  
 */

void ntd_set_disp_map(char key, uint8_t value);

/**
@if Chinese
	 * @brief       ������Ļ��������
	 * @param[in]	brightness	-	����(����5 ~ 100֮��)
	 * @retval      0       �ɹ�
	 * @retval      -1      ����ʧ��
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
	 * @brief ������Ļ����
	 * @param[in]	direction	
					- SCREEN_DIR_0:������ʾ <br>
					- SCREEN_DIR_180:��ת180��
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

