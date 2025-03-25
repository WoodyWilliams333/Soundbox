/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app input模块</strong> 相关的接口
	 * @par 文件    appinput.h
	 * @author		yangjing
	 * @date        2020-08-07
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-08-07    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-20    | 1.0.1        | liyanping     | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app input</strong>  module
	 * @par file    appinput.h
	 * @author		yangjing
	 * @date        2020-08-07
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-08-05    | 1.0.0        | yanjing       | create file
	 * 2022-04-20    | 1.0.1        | liyanping     | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup appinput 输入
 @else
	@defgroup appinput input
 @endif
 * @{
*/
#ifndef _APP_INPUT_H_
#define _APP_INPUT_H_

#include <appdatatypedef.h>
#include "applcd.h"


// macros for app_kb_get_string_spec()
#define NUM_IN			0x01		/**< @if Chinese 数字输入 @else  input number  @endif */
#define ALPHA_IN		0x02		/**< @if Chinese 字母数字混合输入 @else  input alphanumeric  @endif */
#define PASS_IN			0x04		/**< @if Chinese 密码输入 @else  input password  @endif */
#define CARRY_IN		0x08		/**< @if Chinese 有传入数据 @else  input with incoming data  @endif */
#define ECHO_IN			0x10		/**< @if Chinese 回显传入数据,按键则清除原数据 @else  Press the key to clear the incoming data and echo the original data  @endif */
#define HEX_IN      0x20    /**< @if Chinese 十六进制输入 @else  input hexadecimal data  @endif */      
#define AUTO_FONT		0x80	// RFU

#define LEN_GETSTRING		512	// for app_kb_get_string_spec()

/**
 @if Chinese
	@brief  该枚举类型列出了显示对齐类型.
 @else
	@brief  This enumerated type lists the alignment types for display.
 @endif
*/
typedef enum{
    LEFT_ALIGN   = 0,                /**< @if Chinese 左对齐  @else  Align left @endif */
    RIGHT_ALIGN  = DISP_RIGHT,       /**< @if Chinese 右对齐  @else  Align right @endif */
    CENTER_ALIGN = DISP_MEDIACY,     /**< @if Chinese 居中    @else  Align center @endif */
}E_DISPLAY_TYPE;



typedef struct st_display_param {
    int start_x;                    /**< @if Chinese x轴起始位置  @else  start position on X axis to display @endif */
    int show_line;                  /**< @if Chinese 输入起始行数 @else  the line number of display start line @endif */
    int clean_line;                 /**< @if Chinese 清除最大行数, 清除输入起始至此行区域 @else  Clear the maximum number of lines, and clear the area from the input line to this max line @endif */
}ST_DISPLAY_PARAM;

typedef struct st_display_ex_param {
    int start_x;                    /**< @if Chinese x轴起始位置  @else   start position on X axis to display  @endif */
    textRect rect;                  /**< @if Chinese 显示区域 @else   display area  @endif */
}ST_DISPLAY_EX_PARAM;

typedef struct st_app_input_param {
    uint8_t              use_mode;      /**< @if Chinese 使用设置参数模式: !=0表示使用以下设置参数 @else   Use set parameter mode: !=0 means the following setting parameters are used  @endif */
    E_USE_MODE        choose_disp;      /**< @if Chinese 选择使用显示函数 @else   select and use display function  @endif */
    E_DISPLAY_TYPE     type_align;      /**< @if Chinese 显示模式: 靠右/靠左/居中 @else   Display mode: right / left / Center  @endif */
    union {
        ST_DISPLAY_PARAM       param;   /**< @if Chinese 使用app_lcd_display参数配置 @else  Using app_lcd_display parameter configuration  @endif */
        ST_DISPLAY_EX_PARAM ex_param;   /**< @if Chinese 使用app_lcd_display_ex参数配置 @else   Using app_lcd_display_ex parameter configuration @endif */
    } disp_param;
}ST_APP_INPUT_PARAM;



 /**
 @if Chinese
	@brief	输入字符偏移位置设置(设置参数适用函数:app_input_string / app_input_string_with_last)
 	@param[in]	pInputParam	-	配置参数结构体
	@return     0			-	成功
	@return     其它		-	失败	
@else
	@brief  set the offset position of input character   (apply to the following function: app_input_string / app_input_string_with_last)
	@param[in]	pInputParam	-	structure
	@return     0			-	success
	@return     other		-	fail
 @endif
 */
extern int app_input_string_set_location(ST_APP_INPUT_PARAM *pInputParam);

 /**
 @if Chinese
	@brief	字符输入  清屏第三行(大字体)以下所有屏
 	@param[in]	ucMode		-	输入模式，参考上述模式宏定义
 	@param[in]	ucMinlen	-	最小输入字符数
 	@param[in]	ucMaxlen	-	最大输入字符数
 	@param[in]	ucTimeOut	-	输入超时时间(秒)
 	@param[in]	ucEnter		-	是否支持空输入时按确认结束输入
	@param[out]	pszOut		-	输入串保存
	@return		0			-	成功  
	@return		其它		-	失败		 
@else
	@brief	input string, and clear Clear all screen area from the third line (large font) to the last line
 	@param[in]	ucMode		-	For input mode, refer to the mode macro definition above
 	@param[in]	ucMinlen	-	Minimum length of input characters
 	@param[in]	ucMaxlen	-	Maxmum length of input characters
 	@param[in]	ucTimeOut	-	timeout for input (second) 
 	@param[in]	ucEnter		-	Whether null input is supported, press ENTER key to end the input
	@param[out]	pszOut		- 	address to save inputed string
	@return		0			-	success  
	@return		Other		-	fail	
 @endif
 */ 
extern int app_input_string(uint8_t ucMode, uint8_t ucMinlen, uint8_t ucMaxlen, uint8_t *pszOut, 
								uint8_t ucTimeOut, appbool ucEnter);

 /**
 @if Chinese
	@brief	输入字符串,可传回最后结束按键键值
 		默认仅清屏第二、 三行(大字体), 输入显示位置等属性可以通过函数app_input_string_set_location设置
 	@param[in]	ucMode		-	输入模式（KB_EN_CHAR|...)
 	@param[in]	ucMinlen	-	最小输入字符数
 	@param[in]	ucMaxlen	-	最大输入字符数
 	@param[in]	ucTimeOut	-	输入时间限制
	@param[in]	ucEnter		-	是否支持空输入时按确认结束输入
 	@param[in]	terfunckeys	-	除"确认"取消"外允许结束输入的特定键数组，目前仅支持"功能键“，数组以KEY_INVALID作为结束，KEY_INVALID不能少！
	@param[out]	pszOut		-	返回字符串
	@param[out]	lastkey		-	结束按键的键值
	@return		0			-	成功  
	@return		其它		-	失败		 
@else
	@brief	input string, and return the last pressed key value
 	@param[in]	ucMode		-	For input mode（KB_EN_CHAR|...)
 	@param[in]	ucMinlen	-	Minimum length of input characters
 	@param[in]	ucMaxlen	-	Maxmum length of input characters
 	@param[in]	ucTimeOut	-	timeout for input (second) 
	@param[in]	ucEnter		-	Whether null input is supported, press ENTER key to end the input
 	@param[in]	terfunckeys	-	In addition to "confirm key" and "Cancel key" , it is allowed to end the specific key array entered. At present, only "function key" is supported. The array ends with KEY_INVALID, and KEY_INVALID cannot be less!
	@param[out]	pszOut		-	address to save inputed string
	@param[out]	lastkey		- 	the key value of end key
	@return		0			-	success  
	@return		Other		-	fail
 @endif
 */ 
extern int app_input_string_with_last(uint8_t ucMode, uint8_t ucMinlen, uint8_t ucMaxlen, uint8_t *pszOut, 
								uint8_t ucTimeOut, appbool ucEnter, uint8_t *terfunckeys, uint8_t *lastkey);

/**
 @if Chinese
	@brief	串输入控制和返回值.
 @else
	@brief	String input control and return value.
 @endif
*/

#ifndef 	KB_MAXLEN
#define     KB_MAXLEN               256         /**< @if Chinese  串输入最大允许输入的长度  @else  Maximum allowable length of string input @endif */
#endif
#ifndef		KB_EN_REVDISP
#define     KB_EN_REVDISP           0x01        /**< @if Chinese  1（0） 正（反）显示  @else  1（0） Normal(Reverse) display @endif */
#endif
#ifndef		KB_EN_FLOAT
#define     KB_EN_FLOAT             0x02        /**< @if Chinese  1（0） 有（否）小数点 @else  1（0） with (without) Decimal point  @endif */
#endif
#ifndef		KB_EN_SHIFTLEFT
#define     KB_EN_SHIFTLEFT         0x04        /**< @if Chinese  1（0） 左（右）对齐输入 @else  1（0） Left (right) aligned input @endif */
#endif
#ifndef		KB_EN_CRYPTDISP
#define     KB_EN_CRYPTDISP         0x08        /**< @if Chinese  1（0） 是（否）密码方式   @else  1（0）is( isn't) Password mode @endif */
#endif
#ifndef		KB_EN_CHAR
#define     KB_EN_CHAR              0x10        /**< @if Chinese  1（0） 能（否）输字符   @else  1（0）  Can (cannot) enter characters @endif */
#endif
#ifndef		KB_EN_NUM
#define     KB_EN_NUM               0x20       /**< @if Chinese  1（0） 能（否）输数字    @else   1 (0) can (cannot) enter a number @endif */
#endif
#ifndef		KB_EN_BIGFONT
#define     KB_EN_BIGFONT           0x40        /**< @if Chinese  1（0） 大（小）字体    @else   1 (0) large (small) font @endif */
#endif
#ifndef		KB_EN_PRESETSTR
#define     KB_EN_PRESETSTR         0x80        /**< @if Chinese  1（0） 是（否）允许预设的字符串   @else   1 (0)  preseted strings  is(isn't) allowed @endif */
#endif
#ifndef		KB_EN_NEWLINE
#define     KB_EN_NEWLINE           0x100       /**< @if Chinese  1（0） 是（否）允许左对齐输入换行显示   @else   1 (0)  whether or not display a new line with left aligned   @endif */
#endif
#ifndef		KB_EN_HEX
#define     KB_EN_HEX               0x200       /**< @if Chinese  1（0） 是（否）只能输入16进制数据   @else  1（0） whether or not Only hexadecimal data can be entered @endif */
#endif
#ifndef		KB_EN_PREFIX
#define     KB_EN_PREFIX            0x400       /**< @if Chinese  1（0） 是（否）显示输入前缀  @else   1 (0)  displays the input prefix :Yes (no) @endif */
#endif
#ifndef		KB_EN_CIRCULAR_ENTER
#define     KB_EN_CIRCULAR_ENTER    0x800       /**< @if Chinese  1（0） 是（否）允许圆形扫码建当enter键使用  @else  1（0） allow circular scanncode key to replace Enter key  : Yes (no)  @endif */
#endif
#ifndef		KB_EN_BIG_AMT
#define     KB_EN_BIG_AMT    		0x1000       /**< @if Chinese  1（0） 是（否）大字体金额 (字体宽度放大2倍, 字体高度放大3倍) @else  1 (0) large font (font width is enlarged by 2 times and font height is enlarged by 3 times) display amount : Yes (no)  @endif */
#endif
#ifndef 	KB_EN_MEDIACY
#define 	KB_EN_MEDIACY			0x2000		/**< @if Chinese  1（0） 是（否）居中显示 @else    1（0）  centered display :Yes (no) @endif */
#endif
#ifndef     KB_EN_ECHO_IN
#define     KB_EN_ECHO_IN           0x4000      /**< @if Chinese  1（0） 是（否）有回显传入数据,按键则清除原数据  @else  1（0） whether (or not) the incoming data is echoed. Press the key to clear the original data @endif */
#endif



/**
 @if Chinese
	@brief	预设几组常用的输入控制模式
 @else
	@brief	Preset several groups of common input control modes 
 @endif
*/
#ifndef		KB_BIG_ALPHA
#define     KB_BIG_ALPHA            0x1F5        /**< @if Chinese 大字体字符串输入       @else  input string with large font  @endif */
#endif
#ifndef		KB_BIG_NUM
#define     KB_BIG_NUM              0x1E5       /**< @if Chinese  大字体数字串输入        @else   input numeric string with large font   @endif */
#endif
#ifndef		KB_BIG_PWD
#define     KB_BIG_PWD              0x6D        /**< @if Chinese  大字体密码输入          @else   input password with large font  @endif */
#endif
#ifndef		KB_SMALL_ALPHA
#define     KB_SMALL_ALPHA          0x1B5       /**< @if Chinese  小字体字符串输入         @else  input string with small font   @endif */       
#endif
#ifndef		KB_SMALL_NUM
#define     KB_SMALL_NUM            0x1A5       /**< @if Chinese  小字体数字串输入         @else   input numeric string with small font    @endif */
#endif
#ifndef		KB_SMALL_PWD
#define     KB_SMALL_PWD            0x2D        /**< @if Chinese  小字体密码输入            @else   input password with small font    @endif */
#endif
#ifndef		KB_CANCEL
#define     KB_CANCEL               -1          /**< @if Chinese  字符串输入被用户按取消键退出    @else  string input is ended when the user press 'cancel key'  @endif */
#endif
#ifndef		KB_TIMEOUT
#define     KB_TIMEOUT              -2          /**< @if Chinese  字符串输入超时退出              @else  string input is ended when timeout happens @endif */
#endif
#ifndef		KB_ERROR
#define     KB_ERROR                -3          /**< @if Chinese  字符串输入参数非法              @else  string parameter input is Illegal @endif */
#endif


 
/**
@if Chinese
	@brief	输入字符偏移设置偏移(此函数设置参数只在函数app_input_get_string中使用)
 	@param[in]	x			-	x轴偏移
	@param[in]	line		-	输入起始行数
	@return		0			-	成功  
	@return		其它		-	失败		
@else
	@brief	set offset for character Input (this parameter is only used in the function app_input_get_string)
 	@param[in]	x			- 	offset on X-axis 
	@param[in]	line		- 	the line number of starting lines
	@return		0			-	success  
	@return		Other		-	fail
 @endif
 */
extern int app_input_set_entry_location(int x, int line);

 /**
 @if Chinese
	@brief	输入字符串
 	@param[in]	mode		-	输入模式（KB_EN_CHAR|...)
 	@param[in]	minlen		-	最小输入字符数
 	@param[in]	maxLen		-	最大输入字符数 			
 	@param[in]	timeOutms	-	输入时间限制
 	@param[in]	strbuf		-	预设字符串
	@param[out]	strbuf		-	返回字符串
	@return		0			-	成功  
	@return		其它		-	失败		
@else
	@brief	Input string
 	@param[in]	mode		-	input mode（KB_EN_CHAR|...)
 	@param[in]	minlen		- 	Minimum bytes of input characters
 	@param[in]	maxLen		- 	Maximum bytes of input characters		
 	@param[in]	timeOutms	- 	timeout for input
 	@param[in]	strbuf		- 	string preseted 			
	@param[out]	strbuf		- 	string returned
	@return		0			-	success  
	@return		Other		-	fail	
 @endif
 */ 
extern int app_input_get_string(uint32_t mode, int minlen, int maxLen, int timeOutms, char* strbuf);

/**
 @if Chinese
	@brief	输入字符串
 	@param[in]	pInputParam	-	输入字符显示位置参数 
 	@param[in]	mode		-	输入模式（KB_EN_CHAR|...)
 	@param[in]	minlen		-	最小输入字符数
 	@param[in]	maxLen		-	最大输入字符数 			
 	@param[in]	timeout_ms	-	输入时间限制
 	@param[in]	str_buf		-	预设字符串
 	@param[in]	ucEnter		-	未输入字符按确认键是否退出
 	@param[in]	ucSpace		-	输入字符串是否增加空格显示, 每输入4个字符后面增加一个空格显示
 	@param[in]	terfunckeys	-	除"确认"取消"外允许结束输入的特定键数组，数组以KEY_INVALID作为结束，KEY_INVALID不能少！
	@param[out]	str_buf		-	返回字符串
	@param[out]	lastkey		-	结束按键的键值
	@return 	>=0			-	成功，返回输入字符长度
  	@return 	其它		-	失败
@else
	@brief	Input string
 	@param[in] 	pInputParam	- 	display position parameters for Input character 
 	@param[in] 	mode		- 	input mode（KB_EN_CHAR|...)
 	@param[in] 	minlen		- 	Minimum bytes of input characters
 	@param[in] 	maxLen		- 	Maximum bytes of input characters		
 	@param[in] 	timeout_ms	- 	timeout for input
 	@param[in] 	str_buf		- 	string preseted
 	@param[in] 	ucEnter		- 	when no characters are entered, wheather or not press the ENTER key to exit
 	@param[in] 	ucSpace		- 	Whether to add a space to the input string. Add a space after every 4 characters
 	@param[in] 	terfunckeys	- 	In addition to "confirm key" and "Cancel key" , it is allowed to end the specific key array entered.  The array ends with KEY_INVALID, and KEY_INVALID cannot be less! 			
	@param[out] str_buf		-	string returned
	@param[out]	lastkey		-	key value of end key
	@return 	>=0			-	success,the length of input string
  	@return 	other		-	fail
 @endif
 */  
extern int app_input_get_string_ex(ST_APP_INPUT_PARAM *pInputParam, uint32_t mode, int minlen, int maxLen, 
              int timeout_ms, char* str_buf, appbool ucEnter, appbool ucSpace, uint8_t *terfunckeys, uint8_t *lastkey);				
 /**
 @if Chinese
	@brief	数字和字母使用按键切换分开输入
 	@param[in] 	col			-	密码缩进列坐标
 	@param[in] 	line 		-	密码显示行位置, 自动清除起始位置到最后一行数据
 	@param[in] 	tipDispline -	字母选择提示行
 	@param[in] 	ucMinlen	-	字串最小长度,最小值为0
 	@param[in] 	ucMaxlen	-	字串最大长度,最大值为128字节
 	@param[in] 	ucTimeOut	-	接口超时退出时间
 	@param[in] 	pszIn		-	传入的提示字符串
 	@param[in] 	orgPassWord	-	传入的预设值字符串
	@param[out]	pszOut		-	输出字串
	@return		0			-	成功  
	@return		其它		-	失败		
@else
	@brief	Numbers and letters are input separately using key switching
 	@param[in] 	col 		-  	Password indent column coordinates
 	@param[in] 	line 		- 	The password displays the line position and automatically clears the data from the starting position to the last line
 	@param[in] 	tipDispline - 	Letter selection prompt line
 	@param[in] 	ucMinlen 	- 	The minimum length of the string,  the minimum is 0
 	@param[in] 	ucMaxlen 	- 	The maximum length of the string,  the maximum is 128 bytes
 	@param[in] 	ucTimeOut 	- 	timeout for input
 	@param[in] 	pszIn 		- 	Incoming Prompt string
 	@param[in] 	orgPassWord - 	Incoming preset string
	@param[out] pszOut		- 	output string
	@return		0			-	success  
	@return		Other		-	fail
 @endif
 */ 
extern int app_switchable_input_string(int col, int line, int tipDispline, uint8_t ucMinlen, uint8_t ucMaxlen, 
										const char *pszIn, char *orgPassWord, char *pszOut, uint32_t ucTimeOut);

/**
 @if Chinese
	@brief	数字和字母使用按键切换分开输入
 	@param[in] 	col 			-	密码缩进列坐标
 	@param[in] 	line 			-	密码显示行位置(当dispdispUseMode==USE_DISPLAY_EX时，这里传入密码显示起始y轴坐标), 自动清除起始位置到最后一行数据
 	@param[in] 	tipDispline		-	字母选择提示行(当dispdispUseMode==USE_DISPLAY_EX时，这里传入字母选择提示起始y轴坐标)
 	@param[in] 	ucMinlen		-	字串最小长度,最小值为0
 	@param[in] 	ucMaxlen		-	字串最大长度,最大值为128字节
 	@param[in] 	ucTimeOut		-	接口超时退出时间
 	@param[in] 	pszIn			-	传入的提示字符串
 	@param[in] 	orgPassWord		-	传入的预设值字符串
 	@param[in] 	dispUseMode		-	传入显示函数使用:USE_DISPLAY / USE_DISPLAY_EX
	@param[out] pszOut			-	输出字串
	@return		0				-	成功  
	@return		其它			-	失败		
@else
	@brief	Numbers and letters are input separately using key switching
 	@param[in] 	col 		-	Password indent column coordinates
 	@param[in] 	line 		-	The password displays the line position(When dispdispUseMode==USE_DISPLAY_EX, the incomming param is the starting Y-axis coordinates of Password display) 
 							and automatically clears the data from the starting position to the last line
 	@param[in] 	tipDispline -	Letter selection prompt line(When dispdispUseMode==USE_DISPLAY_EX,  the incomming param is the starting Y-axis coordinates of Letter selection prompt)
 	@param[in] 	ucMinlen 	- 	The minimum length of the string,  the minimum is 0
 	@param[in] 	ucMaxlen 	- 	The maximum length of the string,  the maximum is 128 bytes
 	@param[in] 	ucTimeOut 	- 	Interface timeout exit time
 	@param[in] 	pszIn 		-	Incoming Prompt string
 	@param[in] 	orgPassWord -	Incoming preset string
	@param[in] 	dispUseMode	-	incoming display function usage:USE_DISPLAY / USE_DISPLAY_EX
	@param[out] pszOut		- 	output string
	@return		0			-	success  
	@return		Other		-	fail
@endif
 */
extern int app_switchable_input_string_ex(int col, int line, int tipDispline, uint8_t ucMinlen, uint8_t ucMaxlen, 
										const char *pszIn, char *orgPassWord, char *pszOut, uint32_t ucTimeOut, uint8_t dispUseMode);

/**
 @if Chinese
	@brief  数字和字母使用按键切换分开输入
 	@param[in]  col             -   密码缩进列坐标
 	@param[in]  line            -   密码显示行位置(当dispdispUseMode==USE_DISPLAY_EX时，这里传入密码显示起始y轴坐标)
 	@param[in]  clearEndLine    -   清除起始位置到传入行数据
 	@param[in]  tipDispline     -   字母选择提示行(当dispdispUseMode==USE_DISPLAY_EX时，这里传入字母选择提示起始y轴坐标)
 	@param[in]  ucMinlen        -   字串最小长度,最小值为0
 	@param[in]  ucMaxlen        -   字串最大长度,最大值为128字节
 	@param[in]  ucTimeOut       -   接口超时退出时间
 	@param[in]  pszIn           -   传入的提示字符串
 	@param[in]  orgPassWord     -   传入的预设值字符串
 	@param[in]  dispUseMode     -   传入显示函数使用:USE_DISPLAY / USE_DISPLAY_EX
 	@param[out] pszOut          -   输出字串
 	@return     0               -   成功  
 	@return     其它          -   失败      
@else
	@brief  Numbers and letters are input separately using key switching
 	@param[in]  col         -   Password indent column coordinates
 	@param[in]  line        -   The password displays the line position(When dispdispUseMode==USE_DISPLAY_EX, the incomming param is the starting Y-axis coordinates of Password display) 
 	@param[in]  clearEndLine -  Clear end line
 	@param[in]  tipDispline -   Letter selection prompt line(When dispdispUseMode==USE_DISPLAY_EX,  the incomming param is the starting Y-axis coordinates of Letter selection prompt)
 	@param[in]  ucMinlen    -   The minimum length of the string,  the minimum is 0
 	@param[in]  ucMaxlen    -   The maximum length of the string,  the maximum is 128 bytes
 	@param[in]  ucTimeOut   -   Interface timeout exit time
 	@param[in]  pszIn       -   Incoming Prompt string
 	@param[in]  orgPassWord -   Incoming preset string
 	@param[in]  dispUseMode -   incoming display function usage:USE_DISPLAY / USE_DISPLAY_EX
 	@param[out] pszOut      -   output string
 	@return     0           -   success  
 	@return     Other       -   fail
@endif
 */
extern int app_switchable_input_string_add_clear(int col, int line, int clearEndLine, int tipDispline, uint8_t ucMinlen, uint8_t ucMaxlen, 
										const char *pszIn, char *orgPassWord, char *pszOut, uint32_t ucTimeOut);

 /**
@if Chinese
	@brief	汉字输入
 	@param[in] 	MinLen		-	输入最小长度
 	@param[in] 	MaxLen		-	输入最大长度
 	@param[in] 	TimeOutMs	-	输入超时时间，<0表示无超时
 	@param[in] 	StrBuf		-	输入-初始串
 	@param[in] 	InputLine	-	输入起始行
 	@param[in] 	EndLine		-	输入终止行(暂时无效)
 	@param[in] 	iDispMode	-	输入模式(暂时无效)
	@param[out] StrBuf		-	手输串结果
	@return		0			-	成功  
	@return		其它		-	失败
	
@else
	@brief	input Chinese character 
 	@param[in] 	MinLen		-	The minimum length of the string input,
 	@param[in] 	MaxLen		-	The Maximum length of the string input
 	@param[in] 	TimeOutMs	-	timout to input，<0 means no timeout
 	@param[in] 	StrBuf		-	Input - initial string
 	@param[in] 	InputLine	-	the starting line number to input
 	@param[in] 	EndLine		-	the end line number to input(Temporarily invalid)
 	@param[in] 	iDispMode	-	imput mode(Temporarily invalid)
	@param[out] StrBuf		- 	output string
	@return		0			-	success  
	@return		Other		-	fail
	
@endif
 */ 
extern int app_input_get_hz(int MinLen, int MaxLen, int TimeOutMs, char *StrBuf, int InputLine, int EndLine,  int  iDispMode);

#endif

