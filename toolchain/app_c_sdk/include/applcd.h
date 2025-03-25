/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app lcdģ��</strong> ��صĽӿ�
	 * @par �ļ�    applcd.h
	 * @author		yangjing
	 * @date        2020-10-13
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-10-13    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-19    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app lcd</strong>  module
	 * @par file    applcd.h
	 * @author		yangjing
	 * @date        2020-10-13
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-10-13    | 1.0.0        | yanjing       | create file
	 * 2022-04-19    | 1.0.1        | lydia         | Add English description
 @endif
*/

/*!
 @if Chinese
	@defgroup applcd ��ʾ
 @else
	@defgroup applcd display 
 @endif
 * @{
*/

#ifndef _APP_LCD_H_
#define _APP_LCD_H_

#include <font.h>
#include <paint.h>
#include <lcd.h>
#include "appdatatypedef.h"

#define AMT_FONT_18_36 	0 	// ����������ʾ��18*36 Ĭ�ϣ�����������ҪӦ�����

/**
 @if Chinese
	@brief  ��ö�������г�����ʾ��������.
 @else
	@brief  This enumerated type lists the language types for display.
 @endif
  */
typedef enum{
	APP_ZH = 0,     /**< @if Chinese ���� @else  chinese @endif */
	APP_EN,         /**< @if Chinese Ӣ�� @else  english @endif */
}E_APP_LANGUAGE; 
/**
 @if Chinese
	@brief  ������ɫ.
 @else
	@brief  reverse color.
 @endif
  */
typedef struct st_reverse_color{
	int bgcolor;	/**< @if Chinese ����ɫ @else  Background color @endif */
	int fgcolor;	/**< @if Chinese ǰ��ɫ @else  Foreground color @endif */
}ST_REVERSE_COLOR; 

/**
 @if Chinese
	@brief  lcd��Ϣ.
 @else
	@brief  lcd information.
 @endif
  */
typedef struct st_lcd_info{
	int width;				/**< @if Chinese lcd��� @else  lcd width @endif */
	int height;				/**< @if Chinese lcd�߶ȣ���ȥ��״̬���߶� @else  lcd height,Minus the status bar height @endif */
	uint32_t bits;			/**< @if Chinese ������/����(1��4��8��16��24) @else  pixel(1��4��8��16��24) @endif */
	int Language;			/**< @if Chinese ���� @else  language @endif */
	int bgcolor;			/**< @if Chinese ����ɫ @else  Background color @endif */
	int fgcolor;			/**< @if Chinese ǰ��ɫ @else  Foreground color @endif */
}ST_LCD_INFO;

/**
 @if Chinese
	@brief  ��ö�������г�����ʾ��������.
 @else
	@brief  This enumerated type lists the font types for display.
 @endif
  */
typedef enum{
    FONT_12 = 0,            /**< 6*12 */
    FONT_16,                /**< 8*16 */
    FONT_24,                /**< 12*24 */
}E_FONT_TYPE;               

/**
 @if Chinese
	@brief  ��ʾ������Ϣ.\n
	@brief  �и�=����߶�+�������߶�.\n
	@brief  ʹ��Ĭ������ʱ��\n
	@brief  ������:(����/����6200/�ڰ����ֱ�Ϊ:12/8/6)\n
	@brief  ����߶�:(����/����6200/�ڰ����ֱ�Ϊ:24/16/12)\n
	@brief  �����߶�: (����/����6200/�ڰ����ֱ�Ϊ:3/2/2)\n
	@brief  �и�: (����/����6200/�ڰ����ֱ�Ϊ:30/20/16)
 @else
	@brief  font information.\n
	@brief  Row height=font height + Top fill height + bottom fill height).
 @endif
  */
typedef struct st_font_attr {
    int font_width;         /**< @if Chinese ������ @else  font width(12) @endif */
    int font_height;        /**< @if Chinese ����߶� @else  font height(24) @endif */
    int line_edge;          /**< @if Chinese �����߶� @else  Row fill height(3) @endif */
    int line_height;        /**< @if Chinese �и� @else  Row height(30) @endif */
    int maxline;            /**< @if Chinese ������� @else  max rows @endif */
}ST_FONT_ATTR;

/**
 @if Chinese
	@brief  ��ʾ����.
 @else
	@brief  display font.
 @endif
  */
typedef struct st_app_font {
    E_FONT_TYPE font_type;  /**< @if Chinese �������� @else  font type @endif */
    font_t hfont;           /**< @if Chinese ������ @else  font handle @endif */
    struct st_font_attr attr;/**< @if Chinese ������Ϣ @else  font information @endif */
}ST_APP_FONT;

/**
 @if Chinese
	@brief  �Զ����������.
 @else
	@brief  Custom large font amount.
 @endif
  */
typedef struct _BIG_DITITAL_{
	uint8_t digit;
	const uint8_t *bigDigit;
}ST_BIG_DIGIT;

/**
 @if Chinese
	@brief  �Զ���������.
 @else
	@brief  Custom amount content.
 @endif
  */
typedef struct {
	int type;						/**< @if Chinese �������� @else  amount type @endif */
	int font_width;					/**< @if Chinese �������Ŀ� @else  amount font width @endif */
	int font_height;				/**< @if Chinese �������ĸ� @else  amount font height @endif */
	ST_BIG_DIGIT *pdigitarray;		/**< @if Chinese ��������λ���� @else  amount data digit group @endif */
}ST_AMT_CONTENT;

/**
 @if Chinese
	@brief  ��ö�������г�����ʾ״̬.
 @else
	@brief  This enumerated type lists the display status.
 @endif
  */
typedef enum{
	NOT_DISP 	= -1,	/**< @if Chinese ����ʾ���� @else  No display updates @endif */
	NO_UPDATE 	= 0,	/**< @if Chinese ������� @else  No update required @endif */
	NEED_UPDATE,		/**< @if Chinese ��Ҫ���� @else  Need update @endif */
}E_DISP_STATUS;

/**
 @if Chinese
	@brief  ʹ��app_lcd_display������ʾ����.
 @else
	@brief  Use app_lcd_display Configure display parameters.
 @endif
  */
typedef struct st_page_display_param {
    int start_x;              /**< @if Chinese x����ʼλ�� @else  Start position of X  @endif */
    int show_width;           /**< @if Chinese ��ʾһ�п�� @else  Row width  @endif */
    int begin_line;           /**< @if Chinese ��ʾ��ʼ��, =-1��ʾ���һ�� @else Start line,-1 is last line @endif */
    int end_line;             /**< @if Chinese ��ʾ������, =-1��ʾ���һ�� @else End line,-1 is last line @endif */ 
}ST_PAGE_DISPLAY_PARAM;

/**
 @if Chinese
	@brief  ʹ��app_lcd_display_ex������ʾ����.
 @else
	@brief  Use app_lcd_display_ex Configure display parameters.
 @endif
  */
typedef struct st_page_display_ex_param {
    int start_x;                            /**< @if Chinese x����ʼλ�� @else  Start position of X  @endif */
    int start_y;                            /**< @if Chinese y����ʼλ�� @else  Start position of Y  @endif */
    int show_width;                         /**< @if Chinese ��ʾһ�п�� @else  Row width  @endif */
    int show_height;                        /**< @if Chinese ��ʾһ�и߶� @else  Row height  @endif */
}ST_PAGE_DISPLAY_EX_PARAM;

/**
 @if Chinese
	@brief  ��ö�������г�����ʾģʽ.
 @else
	@brief  This enumerated type lists the display mode.
 @endif
  */
typedef enum{
    USE_DISPLAY = 0,                       /**< app_lcd_display */
    USE_DISPLAY_EX,                        /**< app_lcd_display_ex */
}E_USE_MODE;

/**
 @if Chinese
	@brief  ������ʾ����.
 @else
	@brief  Configure display parameters.
 @endif
  */
typedef struct {
    E_USE_MODE mode;                       
    union {
        ST_PAGE_DISPLAY_PARAM       param;  
        ST_PAGE_DISPLAY_EX_PARAM ex_param;  
    }page;
}ST_PAGE_DISP_PARAM;

typedef struct {
    ST_PAGE_DISP_PARAM dpara;
    textRect rect;              /**< @if Chinese ��ʾ���� @else display rect @endif */
    const char *pStr;           /**< @if Chinese ��ʾ���� @else display content @endif */
    int str_len;                /**< @if Chinese ��ʾ�����ܳ��� @else displays the total length of the content @endif */
    int one_line_str_len;       /**< @if Chinese ��ʾһ�����ݳ��� @else displays the length of a line @endif */
    int disp_line_total;        /**< @if Chinese ��ʾ������ @else displays the total number of rows @endif */
    int one_page_disp_lines;    /**< @if Chinese ��ҳ��ʾ���� @else the number of rows displayed on a single page @endif */
    int line_height_offset;     /**< @if Chinese ��ƫ�Ƹ߶� @else row offset height @endif */
} app_lcd_disp_pagepara_st;

typedef int (*pAppLcdDispPageCb)(app_lcd_disp_pagepara_st *param); /**< callback display function */

#ifndef DISP_ASCII
#define DISP_ASCII              (0   )      /**< @if Chinese С������ʾ(8*16)  @else small font(8*16) @endif */
#endif
#ifndef DISP_CFONT
#define DISP_CFONT              (1<<0)      /**< @if Chinese ��������ʾ(12*24)  @else big font(12*24) @endif */
#endif
#ifndef DISP_CLRLINE
#define DISP_CLRLINE            (1<<5)      /**< @if Chinese �����ʾռ�õ��� @else clear current display line @endif */
#endif
#ifndef DISP_MEDIACY
#define DISP_MEDIACY            (1<<6)      /**< @if Chinese ������ʾ @else display with text-align center @endif */
#endif
#ifndef DISP_RIGHT
#define DISP_RIGHT            	(1<<9)      /**< @if Chinese ������ʾ @else display with right @endif */
#endif
#ifndef DISP_REVERSE
#define DISP_REVERSE            (1<<7)      /**< @if Chinese ������ʾ @else reverse character @endif */
#endif
#ifndef DISP_INVLINE
#define DISP_INVLINE            (1<<4)      /**< @if Chinese ���з�����ʾ @else reverse display line @endif */
#endif
#ifndef DISP_FLIP
#define DISP_FLIP               (1<<8)      /**< @if Chinese ˢ����ʾ @else refresh display @endif */
#endif

#define ROW_MAX_LEN             (app_lcd_get_max_len())     /**< @if Chinese һ����󳤶�(Ĭ������ʱ: ����-26, �ڰ���-21, ����6200-20) @else Max length of one line(26) @endif */  
#define MAX_ROWS                (app_lcd_get_max_line())    /**< @if Chinese �����ʾ����(����/����6200/�ڰ����ֱ�Ϊ:7/5/4) @else max line(7) @endif */
#define FONT_HEIGHT             (app_lcd_get_font_height()) /**< @if Chinese ��ǰʹ������߶�(Ĭ������ʱ: ����/����6200/�ڰ����ֱ�Ϊ:24/16/12) @else font height(24) @endif */ 
#define FONT_WIDTH              (app_lcd_get_font_width())  /**< @if Chinese ��ǰʹ��������(Ĭ������ʱ: ����/����6200/�ڰ����ֱ�Ϊ:12/8/6) @else font weight(210) @endif */ 
#define LCD_HEIGHT              (app_lcd_get_lcd_height())  /**< @if Chinese ��Ļ�߶�(����/����6200/�ڰ����ֱ�Ϊ:210/108/64) @else lcd height(210) @endif */  
#define LCD_WIDTH               (app_lcd_get_lcd_width())   /**< @if Chinese ��Ļ���(����/����6200/�ڰ����ֱ�Ϊ:320/160/128) @else lcd width(320) @endif */ 

// macros for screen functions

#define NUM_MAXZHCHARS          26               /**< @if Chinese ÿ������ַ���Ŀ(������) @else Maximum characters per line @endif */            
#define NUM_MAXCOLS             LCD_WIDTH        /**< @if Chinese ÿ���������(����Ļ���) @else lcd width @endif */               
#define NUM_MAXCOLNO            (NUM_MAXCOLS-1)  /**< @if Chinese ����к� @else Maximum column number @endif */              
#define NUM_MAXLINES            (MAX_ROWS - 1)*2 /**< @if Chinese �������(��������/����6200/�ڰ����ֱ�Ϊ:12/8/6) @else Maximum number of rows @endif */          
#define NUM_MAXLINENO           (NUM_MAXLINES-1) /**< @if Chinese ����к� @else Maximum line number @endif */           
#define NUM_MAXZHLINES          NUM_MAXLINES     /**< @if Chinese ����������� @else Maximum number of rows with chinese characters @endif */             
#define NUM_MAXCHARS            ROW_MAX_LEN      /**< @if Chinese ÿ������ֽ��� @else Maximum bytes per line @endif */            

#define DISP_MAX_LEN            ROW_MAX_LEN                 
#define DISP_MAX_LINE           MAX_ROWS                   
#define CLR_MAX_LINE            12                         

#define DISP_128x64_MAX_LEN     DISP_MAX_LEN                
#define DISP_128x64_MAX_LINE    DISP_MAX_LINE               
#define CLR_128x64_MAX_LINE     (DISP_128x64_MAX_LINE-1)*2 /**< @if Chinese ���������� @else Clear maximum rows @endif */ 


#define LCD_320x240_WIDTH       320
#define LCD_128x64_WIDTH        128
#define LCD_160x128_WIDTH       160

#define FONT_12x24_WIDTH        12      /**< @if Chinese ������ @else font width @endif */
#define FONT_12x24_HEIGHT       24      /**< @if Chinese ����߶� @else font height @endif */

#define FONT_8x16_WIDTH         8       /**< @if Chinese ������ @else font width @endif */
#define FONT_8x16_HEIGHT        16      /**< @if Chinese ����߶� @else font height @endif */

#define FONT_6x12_WIDTH         6       /**< @if Chinese ������ @else font width @endif */
#define FONT_6x12_HEIGHT        12      /**< @if Chinese ����߶� @else font height @endif */


/*!
 @if Chinese
	@brief          �����û��ֿ�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set the user font
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
extern int app_lcd_set_user_font(const char *font);

/*!
 @if Chinese
	@brief          lcd��ʼ����lcd����ǰ�����ȳ�ʼ��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          lcd init,must be initialized before using lcd
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
extern int app_lcd_init(void);


/*!
 @if Chinese
	@brief          ��ȡlcd��Ϣ
	@param[in]    	 lpLcdInfo	-	lcd��Ϣ�ṹ
 @else
	@brief          get lcd information
	@param[in]     	lpLcdInfo	-	ST_LCD_INFO
 @endif
*/
extern void app_lcd_get_info(ST_LCD_INFO *lpLcdInfo);


/*!
 @if Chinese
	@brief          ˢ��lcd��ʾ
 @else
	@brief          Refresh LCD display
 @endif
*/ 
extern void app_lcd_flip(void);


/*!
 @if Chinese
	@brief          ��������ʾ��
 @else
	@brief          Cleanup current lcd content
 @endif
*/  
extern void app_lcd_clear_all(void);


/*!
 @if Chinese
	@brief          ��ͻ���ʾ����,ָ�ӵڶ��п�ʼ�����������һ��)������Ļ���λ��
 @else
	@brief          Clear second to last line
 @endif
*/ 
extern void app_lcd_clear_client(void);


/*!
 @if Chinese
	@brief          ����������ʾ����,�и߰��մ������и�/2���㣬��30/2 = 15
	@param[in]	    beginline	-	��ʼ�У���Сֵ0����״̬���¿�ʼ����,endline-��ֹ�У����ֵ12
	@param[in]	    endline		-	��ֹ�У����ֵ12
 @else
	@brief          Clear one or more specified lines
	@param[in]  	beginline	-	starting line number��Exclude status bar
	@param[in]  	endline		-	Ending line number��max is 12
 @endif
*/  
extern void app_lcd_clear_line(int beginline, int endline);


/*!
 @if Chinese
	@brief          ��ֱ�ߣ���lcd��Ļ���Ͻ�Ϊԭ��
	@param[in]      x1		-	�˵�1 x������
	@param[in]      y1		-	�˵�1 y������
	@param[in]      x2		-	�˵�2 x������(ֱ�ߵĿ��)
	@param[in]      y2		-	�˵�2 y������(ֱ�ߵĸ߶�)
	@param[in]      color	-	������ɫ
 @else
	@brief          Draw a straight line
	@param[in]      x1		-	the x-coordinate of start point
	@param[in]      y1		-	the y-coordinate of start point
	@param[in]      x2		-	the x-coordinate of end point
	@param[in]      y2		-	the y-coordinate of end point
	@param[in]      color	-	line color
 @endif
*/  
extern void app_lcd_draw_line(int x1, int y1, int x2, int y2, int color);

/*!
 @if Chinese
	@brief          ����bmpͼƬ����lcd��Ļ���Ͻ�Ϊԭ��
	@param[in]      x			-	ͼƬ��ʼ�� x������
	@param[in]      y			-	ͼƬ��ʼ�� x������
	@param[in]      pucBitMap	-	bmpͼƬ����
 @else
	@brief          Draw a BMP picture on LCD
	@param[in]      x			-	the x-coordinate of start point
	@param[in]      y			-	the y-coordinate of start point
	@param[in]      pucBitMap	-	Display buffer pointer
 @endif
*/  
extern void app_lcd_draw_bmp(int x, int y, const uint8_t *pucBitMap);

/*!
 @if Chinese
	@brief          ����һ�����η���
	@param[in]     	xstart	-	�������ϵ� x������
	@param[in]    	ystart	-	�������ϵ� y������
	@param[in]      xend	-	�������µ� x������
	@param[in]      yend	-	�������µ� y������
	@param[in]      color	-	������ɫ 
 @else
	@brief          Draw a rectangle on LCD
	@param[in]      xstart	-	the x-coordinate of start point
	@param[in]      ystart	-	the y-coordinate of start point
	@param[in]      xend	-	the x-coordinate of end point
	@param[in]      yend	-	the y-coordinate of end point
	@param[in]      color	-	rectangle line color
 @endif
*/   
extern void app_lcd_draw_frame(int xstart, int ystart, int xend, int yend, int color);

/*!
 @if Chinese
	@brief          ����һ������
	@param[in]      x		-	�������ϵ� x������
	@param[in]      y		-	�������ϵ� y������
	@param[in]      width	-	���ο�
	@param[in]      height	-	���θ�
	@param[in]      color	-	�������ɫ
 @else
	@brief          Draw a rectangle on LCD
	@param[in]      x		-	the x-coordinate of start point
	@param[in]      y		-	the y-coordinate of start point
	@param[in]      width	-	rectangle width
	@param[in]      height	-	rectangle height
	@param[in]      color	-	rectangle fill color
 @endif
*/  
extern void app_lcd_draw_rect(int x, int y, int width, int height, int color);

/*!
 @if Chinese
	@brief          ���޶���������ʾ�ı�
	@param[in]      x			-	�ı���ʼx������
	@param[in]      y			-	�ı���ʼy������
	@param[in]      mode		-	��ʾģʽ
	@param[in]      rect		-	������Ϣ
	@param[in]      format		-	��ʽ���ַ���
 @else
	@brief          Displays text within a limit rectangle
	@param[in]      x			-	the text x-coordinate of start point
	@param[in]      y			-	the text y-coordinate of start point
	@param[in]      mode		-	display mode
	@param[in]      rect		-	rectangle information
	@param[in]      format		-	String and format to be displayed
 @endif
*/ 
extern void app_lcd_display_in_rect(int x, int y, uint32_t mode, textRect *rect, const char *format, ...);

/*!
 @if Chinese
	@brief          ���з�ʽ��ʾ�ı�(֧���Զ����С����з�����)
	@param[in]      col		-	�ı���ʼ��
	@param[in]      line	-	�ı���ʼ��
	@param[in]      mode	-	��ʾģʽ
	@param[in]      format	-	��ʽ���ַ���
 @else
	@brief          Displays format string from line position
	@param[in]      col		-	Horizontal coordinate of the starting point
	@param[in]      line	-	Vertical coordinate (line number) of the starting point
	@param[in]      mode	-	display mode
	@param[in]      format	-	String and format to be displayed
 @endif
*/ 
extern void app_lcd_display(int col, int line, uint32_t mode, const char *format, ...);

/*!
 @if Chinese
	@brief          �����귽ʽ��ʾ�ı�(֧���Զ����С����з�����)
	@param[in]      x		-	�ı���ʼx������
	@param[in]      y		-	�ı���ʼy������
	@param[in]      mode	-	��ʾģʽ
	@param[in]      format	-	��ʽ���ַ���
 @else
	@brief          Displays format string from cursor position
	@param[in]      x		-	the x-coordinate of start point
	@param[in]      y		-	the y-coordinate of start point
	@param[in]      mode	-	display mode
	@param[in]      format	-	String and format to be displayed
 @endif
*/ 
extern void app_lcd_display_ex(int x, int y, uint32_t mode, const char *format, ...);

/*!
 @if Chinese
	@brief          ���÷�����ɫ
	@param[in]      back_color	-	����ɫ
	@param[in]      fore_color	-	ǰ��ɫ
 @else
	@brief          set reverse display color
	@param[in]      back_color	-	Background color
	@param[in]      fore_color	-	Foreground color
 @endif
*/ 
extern void app_lcd_set_reverse_display(uint32_t back_color, uint32_t fore_color);

/*!
 @if Chinese
	@brief          ��ȡ��ʾ��������
	@return         ��ʾ��������(APP_ZH���ģ�APP_ENӢ��)
 @else
	@brief          get display language type
	@return         language type(APP_ZH-chinese��APP_EN-english)
 @endif
*/ 
extern int app_lcd_get_language(void);

/*!
 @if Chinese
	@brief          ������������
	@param[in]      language	-	��ʾ��������(APP_ZH���ģ�APP_ENӢ��)
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set language type
	@param[in]      language	-	language type(APP_ZH-chinese��APP_EN-english)
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_lcd_set_language(int language);

/*!
 @if Chinese
	@brief          ��ȡlcd��ɫ
	@param[out]     back_color	-	����ɫ
	@param[out]     fore_color	-	ǰ��ɫ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get lcd color
	@param[out]     back_color	-	Background color
	@param[out]     fore_color	-	Foreground color
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_lcd_get_color(uint32_t *back_color, uint32_t *fore_color);

/*!
 @if Chinese
	@brief          ����״̬��ͼ��
	@param[in]      icon	-	ͼ������
	@param[in]      onoff	-	�Ƿ���ʾͼ�� 1-��ʾ 0-�ر�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set status bar icon
	@param[out]     icon	-	icon type
	@param[out]     onoff	-	display icon 1-on 0-off
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_lcd_set_icon(int icon, appbool onoff);

/*!
 @if Chinese
	@brief          ����lcd��ɫ
	@param[in]      back_color	-	����ɫ
	@param[in]      fore_color	-	ǰ��ɫ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set lcd color
	@param[in]      back_color	-	Background color
	@param[in]      fore_color	-	Foreground color
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_lcd_set_color(uint32_t back_color, uint32_t fore_color);

/*!
 @if Chinese
	@brief          ����lcd�Ƿ��ͬ��ˢ����ʽ
	@param[in]      onoff	-	�Ƿ�� 1-�� 0-�ر�
 @else
	@brief          set refreshing screen mode by synchronization
	@param[in]      onoff	-	1-on 0-off
 @endif
*/  
extern void app_lcd_set_flip_sync(int onoff);

/*!
 @if Chinese
	@brief          ������������������ʾ
	@param[in]      x		-	��ʾ��ʼx������
	@param[in]      y		-	��ʾ��ʼy������
	@param[in]      str		-	����ַ���
	@param[in]      mode	-	��ʾģʽ���ο�lcdDisplay��ʾģʽ
	@param[in]      wscale	-	�������,������
	@param[in]      hscale	-	�������,������
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          Displays text within a limit rectangle
	@param[in]      x		-	the x-coordinate of start point
	@param[in]      y		-	the y-coordinate of start point
	@param[in]      str		-	amount string
	@param[in]      mode	-	display mode
	@param[in]      wscale	-	Horizontal scale, integer multiple
	@param[in]      hscale	-	Vertical scale, integer multiple
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_lcd_disp_big_amt(int x, int y, char *str, int mode, int wscale, int hscale);

/*!
 @if Chinese
	@brief          �Զ�������ʾ
	@param[in]      x			-	��ʾ��ʼx������
	@param[in]      y			-	��ʾ��ʼy������
	@param[in]      str			-	����ַ���
	@param[in]      FontType	-	�������ͣ���AmtContent�ṹ��Ҫ��Ӧ
	@param[in]      AmtContent	-	���������������
	@param[in]      AmtNum		-	�������
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          Custom amount display
	@param[in]      x			-	the x-coordinate of start point
	@param[in]      y			-	the y-coordinate of start point
	@param[in]      str			-	amount string
	@param[in]      FontType	-	font type,Corresponding to the type from struct ST_AMT_CONTENT
	@param[in]      AmtContent	-	struct ST_AMT_CONTENT
	@param[in]      AmtNum		-	Number of ST_AMT_CONTENT
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_lcd_disp_sefdef_amt(int x, int y, char *str, int FontType, ST_AMT_CONTENT AmtContent[], int AmtNum);

/*!
 @if Chinese
	@brief          ������ʾ��������
	@param[in]      fontype	-	lcd��ʾ��������
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set font type
	@param[in]     fontype	-	display font type
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_lcd_set_font(E_FONT_TYPE fontype);

/*!
 @if Chinese
	@brief          ��ȡ��ʾ����������Ϣ
	@param[out]     pappfont	-	����������Ϣ�ṹ
 @else
	@brief          get font information
	@param[out]     pappfont	-	struct ST_APP_FONT
 @endif
*/ 
extern void app_lcd_get_app_font(ST_APP_FONT *pappfont);

/*!
 @if Chinese
	@brief          ��ָ����ʾ����
	@param[in]      rect	-	���������Ϣ
 @else
	@brief          clear designated region
	@param[in]      rect	-	region information
 @endif
*/  
extern void app_lcd_clear_rect(textRect *rect);

/*!
 @if Chinese
	@brief          ��ȡ��ʾһ����󳤶�
	@return         �����ʾ�ֽ���
 @else
	@brief          get the maximum length of a line
	@return         Maximum display bytes
 @endif
*/ 
extern int app_lcd_get_max_len(void);

/*!
 @if Chinese
	@brief          ��ȡ�����ʾ����
	@return         �����ʾ����
 @else
	@brief          get the maximum number of lines
	@return         maximum number of lines
 @endif
*/ 
extern int app_lcd_get_max_line(void);

/*!
 @if Chinese
	@brief          ��ȡ��Ļ���
	@return         ��Ļ���
 @else
	@brief          get the lcd width
	@return         lcd width
 @endif
*/
extern int app_lcd_get_lcd_width(void);

/*!
 @if Chinese
	@brief          ��ȡ��Ļ�߶�
	@return         ��ȡ��Ļ�߶�
 @else
	@brief          get the lcd height
	@return         lcd height
 @endif
*/
extern int app_lcd_get_lcd_height(void);

/*!
 @if Chinese
	@brief          ��ȡ��ǰʹ��������
	@return         ������
 @else
	@brief          get the current font width
	@return         font width
 @endif
*/
extern int app_lcd_get_font_width(void);

/*!
 @if Chinese
	@brief          ��ȡ��ǰʹ������߶�
	@return         ����߶�
 @else
	@brief          get the current font height
	@return         font height
 @endif
*/
extern int app_lcd_get_font_height(void);

/*!
 @if Chinese
	@brief          ��ʾ�ı�(�ɷ�ҳ��ʾ��Ϣ, ֧���Զ����С����з�����)
	@brief          (��ʾ��ҳʱ��ʱ(��ȷ�ϼ�)���Զ�������һҳ, �����һҳ��ʱ(��ȷ�ϼ�)ֱ���˳�)
	@param[in]     DispStr		-	��Ҫ��ʾ������
	@param[in]     StDispParam	-	��ʾ����
	@param[in]     terfunckeys	-	�����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������
	@param[in]     loop			-	ѭ����ҳ��ʾ��־
	@param[in]     timeout_ms	-	��ʾʱ��(ms)
	@return        �ɹ�		-	0���ֵ(loop=0����0�����򷵻ؼ�ֵ)
	@return        ����		-	ʧ��
 @else
	@brief          Split page display
	@param[in]      DispStr			-	display content
	@param[in]      StDispParam		-	display param
	@param[in]      terfunckeys		-	key value
	@param[in]      loop			-	turn page to display 1-yes 0-no
	@param[in]      timeout_ms		-	timeout times
	@return         0 or key value	-	success(loop=0 is 0,or is key vlaue)
	@return         other			-	fail
 @endif
*/  
extern int app_lcd_display_pageable(const char *DispStr, ST_PAGE_DISP_PARAM StDispParam, uint8_t *terfunckeys, appbool loop, int timeout_ms);

/*!
 @if Chinese
	@brief          ��ʾ�ı�(�ɷ�ҳ��ʾ��Ϣ, ֧���Զ����С����з�����)
	@brief          ���ûص���ʾ����, ���ݴ���������Ӧ���ⲿʵ�ַ�ҳ��ʾ, ��������������ʾ����, �˳���ʾҲ�Զ���
	@param[in]      DispStr		-	��Ҫ��ʾ������
	@param[in]      StDispParam	-	��ʾ����
	@param[in]      pcb			-	�ص���ʾ����
	@return         �ɹ�			-	�ص������Զ��巵��>=0��ֵ
	@return         ����			-	ʧ��
 @else
	@brief          Split page display
	@brief          (Use callbacks to display content, paging outside the application based on outgoing parameters)
	@param[in]      DispStr			-	display content
	@param[in]      StDispParam		-	display param
	@param[in]      pcb				-	callback display function
	@return         >=0				-	success(customize values greater than or equal to 0)
	@return         other			-	fail
 @endif
*/
extern int app_lcd_display_pageable_ex(const char *DispStr, ST_PAGE_DISP_PARAM StDispParam, pAppLcdDispPageCb pcb);

#endif

