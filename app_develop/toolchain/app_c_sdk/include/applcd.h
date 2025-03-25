/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app lcd模块</strong> 相关的接口
	 * @par 文件    applcd.h
	 * @author		yangjing
	 * @date        2020-10-13
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-10-13    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-19    | 1.0.1        | lydia         | 增加英文注释  
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
	@defgroup applcd 显示
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

#define AMT_FONT_18_36 	0 	// 大字体金额显示，18*36 默认，其它字体需要应用添加

/**
 @if Chinese
	@brief  该枚举类型列出了显示语言类型.
 @else
	@brief  This enumerated type lists the language types for display.
 @endif
  */
typedef enum{
	APP_ZH = 0,     /**< @if Chinese 中文 @else  chinese @endif */
	APP_EN,         /**< @if Chinese 英文 @else  english @endif */
}E_APP_LANGUAGE; 
/**
 @if Chinese
	@brief  反显颜色.
 @else
	@brief  reverse color.
 @endif
  */
typedef struct st_reverse_color{
	int bgcolor;	/**< @if Chinese 背景色 @else  Background color @endif */
	int fgcolor;	/**< @if Chinese 前景色 @else  Foreground color @endif */
}ST_REVERSE_COLOR; 

/**
 @if Chinese
	@brief  lcd信息.
 @else
	@brief  lcd information.
 @endif
  */
typedef struct st_lcd_info{
	int width;				/**< @if Chinese lcd宽度 @else  lcd width @endif */
	int height;				/**< @if Chinese lcd高度，减去了状态栏高度 @else  lcd height,Minus the status bar height @endif */
	uint32_t bits;			/**< @if Chinese 比特数/像素(1、4、8、16、24) @else  pixel(1、4、8、16、24) @endif */
	int Language;			/**< @if Chinese 语言 @else  language @endif */
	int bgcolor;			/**< @if Chinese 背景色 @else  Background color @endif */
	int fgcolor;			/**< @if Chinese 前景色 @else  Foreground color @endif */
}ST_LCD_INFO;

/**
 @if Chinese
	@brief  该枚举类型列出了显示字体类型.
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
	@brief  显示字体信息.\n
	@brief  行高=字体高度+上下填充高度.\n
	@brief  使用默认字体时：\n
	@brief  字体宽度:(彩屏/彩屏6200/黑白屏分别为:12/8/6)\n
	@brief  字体高度:(彩屏/彩屏6200/黑白屏分别为:24/16/12)\n
	@brief  行填充高度: (彩屏/彩屏6200/黑白屏分别为:3/2/2)\n
	@brief  行高: (彩屏/彩屏6200/黑白屏分别为:30/20/16)
 @else
	@brief  font information.\n
	@brief  Row height=font height + Top fill height + bottom fill height).
 @endif
  */
typedef struct st_font_attr {
    int font_width;         /**< @if Chinese 字体宽度 @else  font width(12) @endif */
    int font_height;        /**< @if Chinese 字体高度 @else  font height(24) @endif */
    int line_edge;          /**< @if Chinese 行填充高度 @else  Row fill height(3) @endif */
    int line_height;        /**< @if Chinese 行高 @else  Row height(30) @endif */
    int maxline;            /**< @if Chinese 最大行数 @else  max rows @endif */
}ST_FONT_ATTR;

/**
 @if Chinese
	@brief  显示字体.
 @else
	@brief  display font.
 @endif
  */
typedef struct st_app_font {
    E_FONT_TYPE font_type;  /**< @if Chinese 字体类型 @else  font type @endif */
    font_t hfont;           /**< @if Chinese 字体句柄 @else  font handle @endif */
    struct st_font_attr attr;/**< @if Chinese 字体信息 @else  font information @endif */
}ST_APP_FONT;

/**
 @if Chinese
	@brief  自定义大字体金额.
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
	@brief  自定义金额内容.
 @else
	@brief  Custom amount content.
 @endif
  */
typedef struct {
	int type;						/**< @if Chinese 金额的类型 @else  amount type @endif */
	int font_width;					/**< @if Chinese 金额字体的宽 @else  amount font width @endif */
	int font_height;				/**< @if Chinese 金额字体的高 @else  amount font height @endif */
	ST_BIG_DIGIT *pdigitarray;		/**< @if Chinese 金额的数据位数组 @else  amount data digit group @endif */
}ST_AMT_CONTENT;

/**
 @if Chinese
	@brief  该枚举类型列出了显示状态.
 @else
	@brief  This enumerated type lists the display status.
 @endif
  */
typedef enum{
	NOT_DISP 	= -1,	/**< @if Chinese 无显示更新 @else  No display updates @endif */
	NO_UPDATE 	= 0,	/**< @if Chinese 无需更新 @else  No update required @endif */
	NEED_UPDATE,		/**< @if Chinese 需要更新 @else  Need update @endif */
}E_DISP_STATUS;

/**
 @if Chinese
	@brief  使用app_lcd_display配置显示参数.
 @else
	@brief  Use app_lcd_display Configure display parameters.
 @endif
  */
typedef struct st_page_display_param {
    int start_x;              /**< @if Chinese x轴起始位置 @else  Start position of X  @endif */
    int show_width;           /**< @if Chinese 显示一行宽度 @else  Row width  @endif */
    int begin_line;           /**< @if Chinese 显示起始行, =-1表示最后一行 @else Start line,-1 is last line @endif */
    int end_line;             /**< @if Chinese 显示结束行, =-1表示最后一行 @else End line,-1 is last line @endif */ 
}ST_PAGE_DISPLAY_PARAM;

/**
 @if Chinese
	@brief  使用app_lcd_display_ex配置显示参数.
 @else
	@brief  Use app_lcd_display_ex Configure display parameters.
 @endif
  */
typedef struct st_page_display_ex_param {
    int start_x;                            /**< @if Chinese x轴起始位置 @else  Start position of X  @endif */
    int start_y;                            /**< @if Chinese y轴起始位置 @else  Start position of Y  @endif */
    int show_width;                         /**< @if Chinese 显示一行宽度 @else  Row width  @endif */
    int show_height;                        /**< @if Chinese 显示一行高度 @else  Row height  @endif */
}ST_PAGE_DISPLAY_EX_PARAM;

/**
 @if Chinese
	@brief  该枚举类型列出了显示模式.
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
	@brief  配置显示参数.
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
    textRect rect;              /**< @if Chinese 显示区域 @else display rect @endif */
    const char *pStr;           /**< @if Chinese 显示内容 @else display content @endif */
    int str_len;                /**< @if Chinese 显示内容总长度 @else displays the total length of the content @endif */
    int one_line_str_len;       /**< @if Chinese 显示一行内容长度 @else displays the length of a line @endif */
    int disp_line_total;        /**< @if Chinese 显示总行数 @else displays the total number of rows @endif */
    int one_page_disp_lines;    /**< @if Chinese 单页显示行数 @else the number of rows displayed on a single page @endif */
    int line_height_offset;     /**< @if Chinese 行偏移高度 @else row offset height @endif */
} app_lcd_disp_pagepara_st;

typedef int (*pAppLcdDispPageCb)(app_lcd_disp_pagepara_st *param); /**< callback display function */

#ifndef DISP_ASCII
#define DISP_ASCII              (0   )      /**< @if Chinese 小字体显示(8*16)  @else small font(8*16) @endif */
#endif
#ifndef DISP_CFONT
#define DISP_CFONT              (1<<0)      /**< @if Chinese 大字体显示(12*24)  @else big font(12*24) @endif */
#endif
#ifndef DISP_CLRLINE
#define DISP_CLRLINE            (1<<5)      /**< @if Chinese 清除显示占用的行 @else clear current display line @endif */
#endif
#ifndef DISP_MEDIACY
#define DISP_MEDIACY            (1<<6)      /**< @if Chinese 居中显示 @else display with text-align center @endif */
#endif
#ifndef DISP_RIGHT
#define DISP_RIGHT            	(1<<9)      /**< @if Chinese 靠右显示 @else display with right @endif */
#endif
#ifndef DISP_REVERSE
#define DISP_REVERSE            (1<<7)      /**< @if Chinese 反白显示 @else reverse character @endif */
#endif
#ifndef DISP_INVLINE
#define DISP_INVLINE            (1<<4)      /**< @if Chinese 整行反白显示 @else reverse display line @endif */
#endif
#ifndef DISP_FLIP
#define DISP_FLIP               (1<<8)      /**< @if Chinese 刷新显示 @else refresh display @endif */
#endif

#define ROW_MAX_LEN             (app_lcd_get_max_len())     /**< @if Chinese 一行最大长度(默认字体时: 彩屏-26, 黑白屏-21, 彩屏6200-20) @else Max length of one line(26) @endif */  
#define MAX_ROWS                (app_lcd_get_max_line())    /**< @if Chinese 最大显示行数(彩屏/彩屏6200/黑白屏分别为:7/5/4) @else max line(7) @endif */
#define FONT_HEIGHT             (app_lcd_get_font_height()) /**< @if Chinese 当前使用字体高度(默认字体时: 彩屏/彩屏6200/黑白屏分别为:24/16/12) @else font height(24) @endif */ 
#define FONT_WIDTH              (app_lcd_get_font_width())  /**< @if Chinese 当前使用字体宽度(默认字体时: 彩屏/彩屏6200/黑白屏分别为:12/8/6) @else font weight(210) @endif */ 
#define LCD_HEIGHT              (app_lcd_get_lcd_height())  /**< @if Chinese 屏幕高度(彩屏/彩屏6200/黑白屏分别为:210/108/64) @else lcd height(210) @endif */  
#define LCD_WIDTH               (app_lcd_get_lcd_width())   /**< @if Chinese 屏幕宽度(彩屏/彩屏6200/黑白屏分别为:320/160/128) @else lcd width(320) @endif */ 

// macros for screen functions

#define NUM_MAXZHCHARS          26               /**< @if Chinese 每行最多字符数目(大字体) @else Maximum characters per line @endif */            
#define NUM_MAXCOLS             LCD_WIDTH        /**< @if Chinese 每行最多列数(即屏幕宽度) @else lcd width @endif */               
#define NUM_MAXCOLNO            (NUM_MAXCOLS-1)  /**< @if Chinese 最大列号 @else Maximum column number @endif */              
#define NUM_MAXLINES            (MAX_ROWS - 1)*2 /**< @if Chinese 最多行数(彩屏彩屏/彩屏6200/黑白屏分别为:12/8/6) @else Maximum number of rows @endif */          
#define NUM_MAXLINENO           (NUM_MAXLINES-1) /**< @if Chinese 最大行号 @else Maximum line number @endif */           
#define NUM_MAXZHLINES          NUM_MAXLINES     /**< @if Chinese 最大中文行数 @else Maximum number of rows with chinese characters @endif */             
#define NUM_MAXCHARS            ROW_MAX_LEN      /**< @if Chinese 每行最大字节数 @else Maximum bytes per line @endif */            

#define DISP_MAX_LEN            ROW_MAX_LEN                 
#define DISP_MAX_LINE           MAX_ROWS                   
#define CLR_MAX_LINE            12                         

#define DISP_128x64_MAX_LEN     DISP_MAX_LEN                
#define DISP_128x64_MAX_LINE    DISP_MAX_LINE               
#define CLR_128x64_MAX_LINE     (DISP_128x64_MAX_LINE-1)*2 /**< @if Chinese 清除最大行数 @else Clear maximum rows @endif */ 


#define LCD_320x240_WIDTH       320
#define LCD_128x64_WIDTH        128
#define LCD_160x128_WIDTH       160

#define FONT_12x24_WIDTH        12      /**< @if Chinese 字体宽度 @else font width @endif */
#define FONT_12x24_HEIGHT       24      /**< @if Chinese 字体高度 @else font height @endif */

#define FONT_8x16_WIDTH         8       /**< @if Chinese 字体宽度 @else font width @endif */
#define FONT_8x16_HEIGHT        16      /**< @if Chinese 字体高度 @else font height @endif */

#define FONT_6x12_WIDTH         6       /**< @if Chinese 字体宽度 @else font width @endif */
#define FONT_6x12_HEIGHT        12      /**< @if Chinese 字体高度 @else font height @endif */


/*!
 @if Chinese
	@brief          设置用户字库
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          set the user font
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
extern int app_lcd_set_user_font(const char *font);

/*!
 @if Chinese
	@brief          lcd初始化，lcd操作前必须先初始化
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          lcd init,must be initialized before using lcd
	@return         0		-	success
	@return         other	-	fail
 @endif
*/
extern int app_lcd_init(void);


/*!
 @if Chinese
	@brief          获取lcd信息
	@param[in]    	 lpLcdInfo	-	lcd信息结构
 @else
	@brief          get lcd information
	@param[in]     	lpLcdInfo	-	ST_LCD_INFO
 @endif
*/
extern void app_lcd_get_info(ST_LCD_INFO *lpLcdInfo);


/*!
 @if Chinese
	@brief          刷新lcd显示
 @else
	@brief          Refresh LCD display
 @endif
*/ 
extern void app_lcd_flip(void);


/*!
 @if Chinese
	@brief          清整个显示区
 @else
	@brief          Cleanup current lcd content
 @endif
*/  
extern void app_lcd_clear_all(void);


/*!
 @if Chinese
	@brief          清客户显示区域,指从第二行开始（标题栏算第一行)起至屏幕最后位置
 @else
	@brief          Clear second to last line
 @endif
*/ 
extern void app_lcd_clear_client(void);


/*!
 @if Chinese
	@brief          清若干行显示区域,行高按照大字体行高/2计算，即30/2 = 15
	@param[in]	    beginline	-	起始行，最小值0，从状态栏下开始算起,endline-终止行，最大值12
	@param[in]	    endline		-	终止行，最大值12
 @else
	@brief          Clear one or more specified lines
	@param[in]  	beginline	-	starting line number，Exclude status bar
	@param[in]  	endline		-	Ending line number，max is 12
 @endif
*/  
extern void app_lcd_clear_line(int beginline, int endline);


/*!
 @if Chinese
	@brief          画直线，以lcd屏幕左上角为原点
	@param[in]      x1		-	端点1 x轴坐标
	@param[in]      y1		-	端点1 y轴坐标
	@param[in]      x2		-	端点2 x轴坐标(直线的宽度)
	@param[in]      y2		-	端点2 y轴坐标(直线的高度)
	@param[in]      color	-	线条颜色
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
	@brief          绘制bmp图片，以lcd屏幕左上角为原点
	@param[in]      x			-	图片起始点 x轴坐标
	@param[in]      y			-	图片起始点 x轴坐标
	@param[in]      pucBitMap	-	bmp图片数据
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
	@brief          绘制一个矩形方框
	@param[in]     	xstart	-	矩形左上点 x轴坐标
	@param[in]    	ystart	-	矩形左上点 y轴坐标
	@param[in]      xend	-	矩形右下点 x轴坐标
	@param[in]      yend	-	矩形右下点 y轴坐标
	@param[in]      color	-	方框颜色 
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
	@brief          绘制一个矩形
	@param[in]      x		-	矩形左上点 x轴坐标
	@param[in]      y		-	矩形左上点 y轴坐标
	@param[in]      width	-	矩形宽
	@param[in]      height	-	矩形高
	@param[in]      color	-	矩形填充色
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
	@brief          在限定矩形内显示文本
	@param[in]      x			-	文本起始x轴坐标
	@param[in]      y			-	文本起始y轴坐标
	@param[in]      mode		-	显示模式
	@param[in]      rect		-	矩形信息
	@param[in]      format		-	格式化字符串
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
	@brief          以行方式显示文本(支持自动换行、换行符换行)
	@param[in]      col		-	文本起始列
	@param[in]      line	-	文本起始行
	@param[in]      mode	-	显示模式
	@param[in]      format	-	格式化字符串
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
	@brief          以坐标方式显示文本(支持自动换行、换行符换行)
	@param[in]      x		-	文本起始x轴坐标
	@param[in]      y		-	文本起始y轴坐标
	@param[in]      mode	-	显示模式
	@param[in]      format	-	格式化字符串
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
	@brief          设置反显颜色
	@param[in]      back_color	-	背景色
	@param[in]      fore_color	-	前景色
 @else
	@brief          set reverse display color
	@param[in]      back_color	-	Background color
	@param[in]      fore_color	-	Foreground color
 @endif
*/ 
extern void app_lcd_set_reverse_display(uint32_t back_color, uint32_t fore_color);

/*!
 @if Chinese
	@brief          获取显示语言类型
	@return         显示语言类型(APP_ZH中文，APP_EN英文)
 @else
	@brief          get display language type
	@return         language type(APP_ZH-chinese，APP_EN-english)
 @endif
*/ 
extern int app_lcd_get_language(void);

/*!
 @if Chinese
	@brief          设置语言类型
	@param[in]      language	-	显示语言类型(APP_ZH中文，APP_EN英文)
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          set language type
	@param[in]      language	-	language type(APP_ZH-chinese，APP_EN-english)
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_lcd_set_language(int language);

/*!
 @if Chinese
	@brief          获取lcd颜色
	@param[out]     back_color	-	背景色
	@param[out]     fore_color	-	前景色
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          设置状态栏图标
	@param[in]      icon	-	图标类型
	@param[in]      onoff	-	是否显示图标 1-显示 0-关闭
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          设置lcd颜色
	@param[in]      back_color	-	背景色
	@param[in]      fore_color	-	前景色
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          设置lcd是否打开同步刷屏方式
	@param[in]      onoff	-	是否打开 1-打开 0-关闭
 @else
	@brief          set refreshing screen mode by synchronization
	@param[in]      onoff	-	1-on 0-off
 @endif
*/  
extern void app_lcd_set_flip_sync(int onoff);

/*!
 @if Chinese
	@brief          按比例扩大字体金额显示
	@param[in]      x		-	显示起始x轴坐标
	@param[in]      y		-	显示起始y轴坐标
	@param[in]      str		-	金额字符串
	@param[in]      mode	-	显示模式，参考lcdDisplay显示模式
	@param[in]      wscale	-	横向比例,整数倍
	@param[in]      hscale	-	纵向比例,整数倍
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          自定义金额显示
	@param[in]      x			-	显示起始x轴坐标
	@param[in]      y			-	显示起始y轴坐标
	@param[in]      str			-	金额字符串
	@param[in]      FontType	-	字体类型，与AmtContent结构需要对应
	@param[in]      AmtContent	-	金额字体数据数组
	@param[in]      AmtNum		-	数组个数
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          设置显示字体类型
	@param[in]      fontype	-	lcd显示字体类型
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取显示字体类型信息
	@param[out]     pappfont	-	字体类型信息结构
 @else
	@brief          get font information
	@param[out]     pappfont	-	struct ST_APP_FONT
 @endif
*/ 
extern void app_lcd_get_app_font(ST_APP_FONT *pappfont);

/*!
 @if Chinese
	@brief          清指定显示区域
	@param[in]      rect	-	清除区域信息
 @else
	@brief          clear designated region
	@param[in]      rect	-	region information
 @endif
*/  
extern void app_lcd_clear_rect(textRect *rect);

/*!
 @if Chinese
	@brief          获取显示一行最大长度
	@return         最大显示字节数
 @else
	@brief          get the maximum length of a line
	@return         Maximum display bytes
 @endif
*/ 
extern int app_lcd_get_max_len(void);

/*!
 @if Chinese
	@brief          获取最大显示行数
	@return         最大显示行数
 @else
	@brief          get the maximum number of lines
	@return         maximum number of lines
 @endif
*/ 
extern int app_lcd_get_max_line(void);

/*!
 @if Chinese
	@brief          获取屏幕宽度
	@return         屏幕宽度
 @else
	@brief          get the lcd width
	@return         lcd width
 @endif
*/
extern int app_lcd_get_lcd_width(void);

/*!
 @if Chinese
	@brief          获取屏幕高度
	@return         获取屏幕高度
 @else
	@brief          get the lcd height
	@return         lcd height
 @endif
*/
extern int app_lcd_get_lcd_height(void);

/*!
 @if Chinese
	@brief          获取当前使用字体宽度
	@return         字体宽度
 @else
	@brief          get the current font width
	@return         font width
 @endif
*/
extern int app_lcd_get_font_width(void);

/*!
 @if Chinese
	@brief          获取当前使用字体高度
	@return         字体高度
 @else
	@brief          get the current font height
	@return         font height
 @endif
*/
extern int app_lcd_get_font_height(void);

/*!
 @if Chinese
	@brief          显示文本(可分页显示信息, 支持自动换行、换行符换行)
	@brief          (显示多页时超时(或按确认键)会自动调到下一页, 在最后一页超时(或按确认键)直接退出)
	@param[in]     DispStr		-	需要显示的数据
	@param[in]     StDispParam	-	显示参数
	@param[in]     terfunckeys	-	传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少
	@param[in]     loop			-	循环翻页显示标志
	@param[in]     timeout_ms	-	显示时间(ms)
	@return        成功		-	0或键值(loop=0返回0，否则返回键值)
	@return        其它		-	失败
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
	@brief          显示文本(可分页显示信息, 支持自动换行、换行符换行)
	@brief          采用回调显示内容, 根据传出参数在应用外部实现分页显示, 可以自行增加显示内容, 退出显示也自定义
	@param[in]      DispStr		-	需要显示的数据
	@param[in]      StDispParam	-	显示参数
	@param[in]      pcb			-	回调显示函数
	@return         成功			-	回调函数自定义返回>=0的值
	@return         其它			-	失败
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

