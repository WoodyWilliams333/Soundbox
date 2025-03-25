
#ifndef __SEOS_H__
#define __SEOS_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#include <stdint.h>

#ifndef MAYBE_UNUSE
#define MAYBE_UNUSE(x)              (void)(x)
#endif

#ifndef UNUSE
#define UNUSE(x)                    (void)(x)
#endif

#ifndef __attribute_used__
#define __attribute_used__          __attribute__((__used__))
#endif

#ifndef __attribute_maybe_unused__
#define __attribute_maybe_unused__  __attribute__((__unused__)) 
#endif

/************************* KEY module ************************************************/

#include "key.h"

/**
* @brief 查询按键缓存队列中是否存在有效按键
* @return 查询的结??
*	-<em> == 1 </em>  存在有效按键
*	-<em> == 0 </em>  不存在有效按键
*/
extern int app_key_check(void);

/**
* @brief 清除按键的缓存队列
* @return 执行的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int app_key_flush(void);

/**
* @brief 阻塞式获取按键值
* @return 获取的按键值
*	-<em> == 0 </em>  获取按键失败
*	-<em> >  0 </em>  获取的按键值，具体值对应的按键，参考sdk的key.h
*/
extern int app_key_get(void);

/**
* @brief 在一定超时时间内获取按键值
* @param[in] timeout_ms，获取按键值的超时时间，单位毫秒 
* @return 获取的按键值
*	-<em> == 0 </em>  获取按键失败
*	-<em> >  0 </em>  获取的按键值，具体值对应的按键，参考sdk的key.h
*/
extern int app_key_get_ms(uint32_t timeout_ms);

/************************* LCD module *************************************************/
/*
LCD的一些说明：
	1. 目前7220支持两种字体：12*24 和 8*16，因此，大字体使用前者，行高30；小字体使用后者，行高20
	2. 使用时，请注意小字体行高不再是大字体的一半！
	3. 清屏接口是按大字体来计算
*/

#include <font.h>
#include "appdatatypedef.h"
#include "lcd.h"


typedef struct st_reverse_color{
	int bgcolor;
	int fgcolor;

}ST_REVERSE_COLOR;



typedef struct st_lcd_info{
	int width;
	int height;
	uint32_t bits;
	int line_height;
	int line_edge;
	int maxline;
	int Language;
	int bgcolor;
	int fgcolor;
	font_t hfont;
	
}ST_LCD_INFO;

typedef enum{
	FONT_16 = 0,
	FONT_24
}E_FONT_TYPE;

//  lcdDisplay显示模式
#ifndef DISP_ASCII
#define DISP_ASCII              (0   )      /**< 小字体显示(8*16) */
#endif
#ifndef DISP_CFONT
#define DISP_CFONT              (1<<0)      /**< 大字体显示(12*24) */
#endif
#ifndef DISP_CLRLINE
#define DISP_CLRLINE            (1<<5)      /**< 清除显示占用的行 */
#endif
#ifndef DISP_MEDIACY
#define DISP_MEDIACY            (1<<6)      /**< 居中显示 */
#endif
#ifndef DISP_RIGHT
#define DISP_RIGHT            	(1<<9)      /**< 靠右显示 */
#endif
#ifndef DISP_REVERSE
#define DISP_REVERSE            (1<<7)      /**< 反白显示 */
#endif
#ifndef DISP_INVLINE
#define DISP_INVLINE            (1<<4)      /**< 整行反白显示 */
#endif
#ifndef DISP_FLIP
#define DISP_FLIP               (1<<8)      /**< 当行显示也执行flip */
#endif

// macros for screen functions
#define NUM_MAXZHCHARS      26          		// 每行最多字符数目(大字体)
#define NUM_MAXCOLS         320         		// 每行最多列数
#define NUM_MAXCOLNO        (NUM_MAXCOLS-1)     // 最大列号
#define NUM_MAXLINES        12          		// 最多行数
#define NUM_MAXLINENO       (NUM_MAXLINES-1)    // 最大行号
#define NUM_MAXZHLINES      12           		// 最大中文行数
#define NUM_MAXCHARS        26


#define DISP_MAX_LEN        26		            //最大显示多少个字节
#define DISP_MAX_LINE       7		            //最大显示行数
#define CLR_MAX_LINE        (DISP_MAX_LINE-1)*2 //清除最大行数

//void app_lcd_get_size_t(int * width, int * height);
extern void app_lcd_flip(void);
extern void app_lcd_clear_all(void);
extern void app_lcd_clear_client(void);
extern void app_lcd_clear_line(int beginline, int endline);
extern void app_lcd_draw_line (int x, int y, int height, int width, int color);
extern void app_lcd_set_direction(int direction);
extern void app_lcd_draw_bmp(int x, int y, const uint8_t *pucBitMap);
extern void app_lcd_draw_pixel(int x, int y, int height, int width, 
							const uint8_t *pucPixel, uint32_t length);
extern void app_lcd_draw_frame(int xstart, int ystart, int xend, int yend, int color);
extern void app_lcd_draw_rect(int x, int y, int width, int height, int color);

//void app_lcd_goto(int col, int line);
void app_lcd_display(int col, int line, uint32_t mode, const char *format, ...);
void app_lcd_display_ex(int x, int y, uint32_t mode, const char *format, ...);


//设置反显颜色 back_color为背景色    fore_color为前景色
void app_lcd_set_reverse_display(uint32_t back_color, uint32_t fore_color);


extern int app_lcd_get_language(void);
extern int app_lcd_set_language(int language);
extern int app_lcd_init(void);
extern int app_lcd_set_icon(int icon, appbool onoff);
extern int app_lcd_get_color(uint32_t *back_color, uint32_t *fore_color);
extern int app_lcd_set_color(uint32_t back_color, uint32_t fore_color);
extern void app_lcd_get_info(ST_LCD_INFO *lpLcdInfo);

/************************* key get string ************************************************/
//  串输入控制和返回值
#ifndef 	KB_MAXLEN
#define     KB_MAXLEN               256         /**< 串输入最大允许输入的长度                   */
#endif
#ifndef		KB_EN_REVDISP
#define     KB_EN_REVDISP           0x01        /**< 1（0） 正（反）显示                        */
#endif
#ifndef		KB_EN_FLOAT
#define     KB_EN_FLOAT             0x02        /**< 1（0） 有（否）小数点                      */
#endif
#ifndef		KB_EN_SHIFTLEFT
#define     KB_EN_SHIFTLEFT         0x04        /**< 1（0） 左（右）对齐输入                    */
#endif
#ifndef		KB_EN_CRYPTDISP
#define     KB_EN_CRYPTDISP         0x08        /**< 1（0） 是（否）密码方式                    */
#endif
#ifndef		KB_EN_CHAR
#define     KB_EN_CHAR              0x10        /**< 1（0） 能（否）输字符                      */
#endif
#ifndef		KB_EN_NUM
#define     KB_EN_NUM               0x20        /**< 1（0） 能（否）输数字                      */
#endif
#ifndef		KB_EN_BIGFONT
#define     KB_EN_BIGFONT           0x40        /**< 1（0） 大（小）字体                        */
#endif
#ifndef		KB_EN_PRESETSTR
#define     KB_EN_PRESETSTR         0x80        /**< 1（0） 是（否）允许预设的字符串            */
#endif
#ifndef		KB_EN_NEWLINE
#define     KB_EN_NEWLINE           0x100       /**< 1（0） 是（否）允许左对齐输入换行显示      */
#endif
#ifndef		KB_EN_HEX
#define     KB_EN_HEX               0x200       /**< 1（0） 是（否）只能输入16进制数据          */
#endif
#ifndef		KB_EN_PREFIX
#define     KB_EN_PREFIX            0x400       /**< 1（0） 是（否）显示输入前缀                */
#endif
#ifndef		KB_EN_CIRCULAR_ENTER
#define     KB_EN_CIRCULAR_ENTER    0x800       /**< 1（0） 是（否）允许圆形扫码建当enter键使用 */
#endif
#ifndef		KB_EN_BIG_AMT
#define     KB_EN_BIG_AMT    		0x1000       /**< 1（0） 是（否）大字体金额*/
#endif


//  预设几组常用的输入控制模式
#ifndef		KB_BIG_ALPHA
#define     KB_BIG_ALPHA            0x1F5       /**< 大字体字符串输入               */
#endif
#ifndef		KB_BIG_NUM
#define     KB_BIG_NUM              0x1E5       /**< 大字体数字串输入               */  
#endif
#ifndef		KB_BIG_PWD
#define     KB_BIG_PWD              0x6D        /**< 大字体密码输入                 */
#endif
#ifndef		KB_SMALL_ALPHA
#define     KB_SMALL_ALPHA          0x1B5       /**< 小字体字符串输入               */      
#endif
#ifndef		KB_SMALL_NUM
#define     KB_SMALL_NUM            0x1A5       /**< 小字体数字串输入               */
#endif
#ifndef		KB_SMALL_PWD
#define     KB_SMALL_PWD            0x2D        /**< 小字体密码输入                 */
#endif
#ifndef		KB_CANCEL
#define     KB_CANCEL               -1          /**< 字符串输入被用户按取消键退出   */
#endif
#ifndef		KB_TIMEOUT
#define     KB_TIMEOUT              -2          /**< 字符串输入超时退出             */
#endif
#ifndef		KB_ERROR
#define     KB_ERROR                -3          /**< 字符串输入参数非法             */
#endif

/**
* @brief 输入字符偏移设置偏移
* @param[in] x，x轴偏移
			line， 输入起始行数
* @return 返回值
*	-<em> == 0 </em>  成功
*	-<em> > !=0 </em>  失败
*/
extern int app_key_set_entry_location(int x, int line);
/**
* @brief 输入字符偏移设置偏移
* @param[in] mode，输入模式（KB_EN_CHAR|...)
			min_len 最小输入字符数
			max_len 最大输入字符数
			timeout_ms 输入时间限制
* @param[in/out]	str_buf  预设字符(采用预设模式)，输入返回字符串
* @return 返回值
*	-<em> >= 0 </em>  输入字符长度
*	-<em> <0 </em>  失败
*/
extern int app_key_get_string(uint32_t mode, int min_len, int max_len, int timeout_ms, char *str_buf);

/*
	MinLen: 输入最小长度
	MaxLen: 输入最大长度
	TimeOutMs： 输入超时时间，<0表示无超时
	StrBuf: 输入-初始串
			输出-手输串结果
	InputLine: 输入起始行
	EndLine: 输入终止行(暂时无效)
	iDispMode: 输入模式(暂时无效)

	返回值: 0 成功， 其它错误(KB_CANCEL KB_TIMEOU...)
*/	
extern int app_kb_get_hz(int MinLen, int MaxLen, int TimeOutMs, char *StrBuf, int InputLine, int EndLine,  int  iDispMode);


/**************************************************************************************/


/**
* @brief 设置wnet库的日志开关，默认情况是日志关闭的
* @param[in] on     欲设置的日志开关状态，非0表示打开，为0表示关闭，见 LOGGER_MODULE_ON 枚举定义
* @return 设置后的日志开关状态
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int seos_logger_on(int on);


/**
* @brief 获取libseos库的版本信息
* @param[out] version，libwnet库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int seos_get_version(char *version, int size);


#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of __SEOS_H__ */

