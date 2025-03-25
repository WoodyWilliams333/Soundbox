/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app inputģ��</strong> ��صĽӿ�
	 * @par �ļ�    appinput.h
	 * @author		yangjing
	 * @date        2020-08-07
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-08-07    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-20    | 1.0.1        | liyanping     | ����Ӣ��ע��  
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
	@defgroup appinput ����
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
#define NUM_IN			0x01		/**< @if Chinese �������� @else  input number  @endif */
#define ALPHA_IN		0x02		/**< @if Chinese ��ĸ���ֻ������ @else  input alphanumeric  @endif */
#define PASS_IN			0x04		/**< @if Chinese �������� @else  input password  @endif */
#define CARRY_IN		0x08		/**< @if Chinese �д������� @else  input with incoming data  @endif */
#define ECHO_IN			0x10		/**< @if Chinese ���Դ�������,���������ԭ���� @else  Press the key to clear the incoming data and echo the original data  @endif */
#define HEX_IN      0x20    /**< @if Chinese ʮ���������� @else  input hexadecimal data  @endif */      
#define AUTO_FONT		0x80	// RFU

#define LEN_GETSTRING		512	// for app_kb_get_string_spec()

/**
 @if Chinese
	@brief  ��ö�������г�����ʾ��������.
 @else
	@brief  This enumerated type lists the alignment types for display.
 @endif
*/
typedef enum{
    LEFT_ALIGN   = 0,                /**< @if Chinese �����  @else  Align left @endif */
    RIGHT_ALIGN  = DISP_RIGHT,       /**< @if Chinese �Ҷ���  @else  Align right @endif */
    CENTER_ALIGN = DISP_MEDIACY,     /**< @if Chinese ����    @else  Align center @endif */
}E_DISPLAY_TYPE;



typedef struct st_display_param {
    int start_x;                    /**< @if Chinese x����ʼλ��  @else  start position on X axis to display @endif */
    int show_line;                  /**< @if Chinese ������ʼ���� @else  the line number of display start line @endif */
    int clean_line;                 /**< @if Chinese ����������, ���������ʼ���������� @else  Clear the maximum number of lines, and clear the area from the input line to this max line @endif */
}ST_DISPLAY_PARAM;

typedef struct st_display_ex_param {
    int start_x;                    /**< @if Chinese x����ʼλ��  @else   start position on X axis to display  @endif */
    textRect rect;                  /**< @if Chinese ��ʾ���� @else   display area  @endif */
}ST_DISPLAY_EX_PARAM;

typedef struct st_app_input_param {
    uint8_t              use_mode;      /**< @if Chinese ʹ�����ò���ģʽ: !=0��ʾʹ���������ò��� @else   Use set parameter mode: !=0 means the following setting parameters are used  @endif */
    E_USE_MODE        choose_disp;      /**< @if Chinese ѡ��ʹ����ʾ���� @else   select and use display function  @endif */
    E_DISPLAY_TYPE     type_align;      /**< @if Chinese ��ʾģʽ: ����/����/���� @else   Display mode: right / left / Center  @endif */
    union {
        ST_DISPLAY_PARAM       param;   /**< @if Chinese ʹ��app_lcd_display�������� @else  Using app_lcd_display parameter configuration  @endif */
        ST_DISPLAY_EX_PARAM ex_param;   /**< @if Chinese ʹ��app_lcd_display_ex�������� @else   Using app_lcd_display_ex parameter configuration @endif */
    } disp_param;
}ST_APP_INPUT_PARAM;



 /**
 @if Chinese
	@brief	�����ַ�ƫ��λ������(���ò������ú���:app_input_string / app_input_string_with_last)
 	@param[in]	pInputParam	-	���ò����ṹ��
	@return     0			-	�ɹ�
	@return     ����		-	ʧ��	
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
	@brief	�ַ�����  ����������(������)����������
 	@param[in]	ucMode		-	����ģʽ���ο�����ģʽ�궨��
 	@param[in]	ucMinlen	-	��С�����ַ���
 	@param[in]	ucMaxlen	-	��������ַ���
 	@param[in]	ucTimeOut	-	���볬ʱʱ��(��)
 	@param[in]	ucEnter		-	�Ƿ�֧�ֿ�����ʱ��ȷ�Ͻ�������
	@param[out]	pszOut		-	���봮����
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��		 
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
	@brief	�����ַ���,�ɴ���������������ֵ
 		Ĭ�Ͻ������ڶ��� ����(������), ������ʾλ�õ����Կ���ͨ������app_input_string_set_location����
 	@param[in]	ucMode		-	����ģʽ��KB_EN_CHAR|...)
 	@param[in]	ucMinlen	-	��С�����ַ���
 	@param[in]	ucMaxlen	-	��������ַ���
 	@param[in]	ucTimeOut	-	����ʱ������
	@param[in]	ucEnter		-	�Ƿ�֧�ֿ�����ʱ��ȷ�Ͻ�������
 	@param[in]	terfunckeys	-	��"ȷ��"ȡ��"���������������ض������飬Ŀǰ��֧��"���ܼ�����������KEY_INVALID��Ϊ������KEY_INVALID�����٣�
	@param[out]	pszOut		-	�����ַ���
	@param[out]	lastkey		-	���������ļ�ֵ
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��		 
@else
	@brief	input string, and return the last pressed key value
 	@param[in]	ucMode		-	For input mode��KB_EN_CHAR|...)
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
	@brief	��������ƺͷ���ֵ.
 @else
	@brief	String input control and return value.
 @endif
*/

#ifndef 	KB_MAXLEN
#define     KB_MAXLEN               256         /**< @if Chinese  �����������������ĳ���  @else  Maximum allowable length of string input @endif */
#endif
#ifndef		KB_EN_REVDISP
#define     KB_EN_REVDISP           0x01        /**< @if Chinese  1��0�� ����������ʾ  @else  1��0�� Normal(Reverse) display @endif */
#endif
#ifndef		KB_EN_FLOAT
#define     KB_EN_FLOAT             0x02        /**< @if Chinese  1��0�� �У���С���� @else  1��0�� with (without) Decimal point  @endif */
#endif
#ifndef		KB_EN_SHIFTLEFT
#define     KB_EN_SHIFTLEFT         0x04        /**< @if Chinese  1��0�� ���ң��������� @else  1��0�� Left (right) aligned input @endif */
#endif
#ifndef		KB_EN_CRYPTDISP
#define     KB_EN_CRYPTDISP         0x08        /**< @if Chinese  1��0�� �ǣ������뷽ʽ   @else  1��0��is( isn't) Password mode @endif */
#endif
#ifndef		KB_EN_CHAR
#define     KB_EN_CHAR              0x10        /**< @if Chinese  1��0�� �ܣ������ַ�   @else  1��0��  Can (cannot) enter characters @endif */
#endif
#ifndef		KB_EN_NUM
#define     KB_EN_NUM               0x20       /**< @if Chinese  1��0�� �ܣ���������    @else   1 (0) can (cannot) enter a number @endif */
#endif
#ifndef		KB_EN_BIGFONT
#define     KB_EN_BIGFONT           0x40        /**< @if Chinese  1��0�� ��С������    @else   1 (0) large (small) font @endif */
#endif
#ifndef		KB_EN_PRESETSTR
#define     KB_EN_PRESETSTR         0x80        /**< @if Chinese  1��0�� �ǣ�������Ԥ����ַ���   @else   1 (0)  preseted strings  is(isn't) allowed @endif */
#endif
#ifndef		KB_EN_NEWLINE
#define     KB_EN_NEWLINE           0x100       /**< @if Chinese  1��0�� �ǣ���������������뻻����ʾ   @else   1 (0)  whether or not display a new line with left aligned   @endif */
#endif
#ifndef		KB_EN_HEX
#define     KB_EN_HEX               0x200       /**< @if Chinese  1��0�� �ǣ���ֻ������16��������   @else  1��0�� whether or not Only hexadecimal data can be entered @endif */
#endif
#ifndef		KB_EN_PREFIX
#define     KB_EN_PREFIX            0x400       /**< @if Chinese  1��0�� �ǣ�����ʾ����ǰ׺  @else   1 (0)  displays the input prefix :Yes (no) @endif */
#endif
#ifndef		KB_EN_CIRCULAR_ENTER
#define     KB_EN_CIRCULAR_ENTER    0x800       /**< @if Chinese  1��0�� �ǣ�������Բ��ɨ�뽨��enter��ʹ��  @else  1��0�� allow circular scanncode key to replace Enter key  : Yes (no)  @endif */
#endif
#ifndef		KB_EN_BIG_AMT
#define     KB_EN_BIG_AMT    		0x1000       /**< @if Chinese  1��0�� �ǣ��񣩴������� (�����ȷŴ�2��, ����߶ȷŴ�3��) @else  1 (0) large font (font width is enlarged by 2 times and font height is enlarged by 3 times) display amount : Yes (no)  @endif */
#endif
#ifndef 	KB_EN_MEDIACY
#define 	KB_EN_MEDIACY			0x2000		/**< @if Chinese  1��0�� �ǣ��񣩾�����ʾ @else    1��0��  centered display :Yes (no) @endif */
#endif
#ifndef     KB_EN_ECHO_IN
#define     KB_EN_ECHO_IN           0x4000      /**< @if Chinese  1��0�� �ǣ����л��Դ�������,���������ԭ����  @else  1��0�� whether (or not) the incoming data is echoed. Press the key to clear the original data @endif */
#endif



/**
 @if Chinese
	@brief	Ԥ�輸�鳣�õ��������ģʽ
 @else
	@brief	Preset several groups of common input control modes 
 @endif
*/
#ifndef		KB_BIG_ALPHA
#define     KB_BIG_ALPHA            0x1F5        /**< @if Chinese �������ַ�������       @else  input string with large font  @endif */
#endif
#ifndef		KB_BIG_NUM
#define     KB_BIG_NUM              0x1E5       /**< @if Chinese  ���������ִ�����        @else   input numeric string with large font   @endif */
#endif
#ifndef		KB_BIG_PWD
#define     KB_BIG_PWD              0x6D        /**< @if Chinese  ��������������          @else   input password with large font  @endif */
#endif
#ifndef		KB_SMALL_ALPHA
#define     KB_SMALL_ALPHA          0x1B5       /**< @if Chinese  С�����ַ�������         @else  input string with small font   @endif */       
#endif
#ifndef		KB_SMALL_NUM
#define     KB_SMALL_NUM            0x1A5       /**< @if Chinese  С�������ִ�����         @else   input numeric string with small font    @endif */
#endif
#ifndef		KB_SMALL_PWD
#define     KB_SMALL_PWD            0x2D        /**< @if Chinese  С������������            @else   input password with small font    @endif */
#endif
#ifndef		KB_CANCEL
#define     KB_CANCEL               -1          /**< @if Chinese  �ַ������뱻�û���ȡ�����˳�    @else  string input is ended when the user press 'cancel key'  @endif */
#endif
#ifndef		KB_TIMEOUT
#define     KB_TIMEOUT              -2          /**< @if Chinese  �ַ������볬ʱ�˳�              @else  string input is ended when timeout happens @endif */
#endif
#ifndef		KB_ERROR
#define     KB_ERROR                -3          /**< @if Chinese  �ַ�����������Ƿ�              @else  string parameter input is Illegal @endif */
#endif


 
/**
@if Chinese
	@brief	�����ַ�ƫ������ƫ��(�˺������ò���ֻ�ں���app_input_get_string��ʹ��)
 	@param[in]	x			-	x��ƫ��
	@param[in]	line		-	������ʼ����
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��		
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
	@brief	�����ַ���
 	@param[in]	mode		-	����ģʽ��KB_EN_CHAR|...)
 	@param[in]	minlen		-	��С�����ַ���
 	@param[in]	maxLen		-	��������ַ��� 			
 	@param[in]	timeOutms	-	����ʱ������
 	@param[in]	strbuf		-	Ԥ���ַ���
	@param[out]	strbuf		-	�����ַ���
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��		
@else
	@brief	Input string
 	@param[in]	mode		-	input mode��KB_EN_CHAR|...)
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
	@brief	�����ַ���
 	@param[in]	pInputParam	-	�����ַ���ʾλ�ò��� 
 	@param[in]	mode		-	����ģʽ��KB_EN_CHAR|...)
 	@param[in]	minlen		-	��С�����ַ���
 	@param[in]	maxLen		-	��������ַ��� 			
 	@param[in]	timeout_ms	-	����ʱ������
 	@param[in]	str_buf		-	Ԥ���ַ���
 	@param[in]	ucEnter		-	δ�����ַ���ȷ�ϼ��Ƿ��˳�
 	@param[in]	ucSpace		-	�����ַ����Ƿ����ӿո���ʾ, ÿ����4���ַ���������һ���ո���ʾ
 	@param[in]	terfunckeys	-	��"ȷ��"ȡ��"���������������ض������飬������KEY_INVALID��Ϊ������KEY_INVALID�����٣�
	@param[out]	str_buf		-	�����ַ���
	@param[out]	lastkey		-	���������ļ�ֵ
	@return 	>=0			-	�ɹ������������ַ�����
  	@return 	����		-	ʧ��
@else
	@brief	Input string
 	@param[in] 	pInputParam	- 	display position parameters for Input character 
 	@param[in] 	mode		- 	input mode��KB_EN_CHAR|...)
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
	@brief	���ֺ���ĸʹ�ð����л��ֿ�����
 	@param[in] 	col			-	��������������
 	@param[in] 	line 		-	������ʾ��λ��, �Զ������ʼλ�õ����һ������
 	@param[in] 	tipDispline -	��ĸѡ����ʾ��
 	@param[in] 	ucMinlen	-	�ִ���С����,��СֵΪ0
 	@param[in] 	ucMaxlen	-	�ִ���󳤶�,���ֵΪ128�ֽ�
 	@param[in] 	ucTimeOut	-	�ӿڳ�ʱ�˳�ʱ��
 	@param[in] 	pszIn		-	�������ʾ�ַ���
 	@param[in] 	orgPassWord	-	�����Ԥ��ֵ�ַ���
	@param[out]	pszOut		-	����ִ�
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��		
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
	@brief	���ֺ���ĸʹ�ð����л��ֿ�����
 	@param[in] 	col 			-	��������������
 	@param[in] 	line 			-	������ʾ��λ��(��dispdispUseMode==USE_DISPLAY_EXʱ�����ﴫ��������ʾ��ʼy������), �Զ������ʼλ�õ����һ������
 	@param[in] 	tipDispline		-	��ĸѡ����ʾ��(��dispdispUseMode==USE_DISPLAY_EXʱ�����ﴫ����ĸѡ����ʾ��ʼy������)
 	@param[in] 	ucMinlen		-	�ִ���С����,��СֵΪ0
 	@param[in] 	ucMaxlen		-	�ִ���󳤶�,���ֵΪ128�ֽ�
 	@param[in] 	ucTimeOut		-	�ӿڳ�ʱ�˳�ʱ��
 	@param[in] 	pszIn			-	�������ʾ�ַ���
 	@param[in] 	orgPassWord		-	�����Ԥ��ֵ�ַ���
 	@param[in] 	dispUseMode		-	������ʾ����ʹ��:USE_DISPLAY / USE_DISPLAY_EX
	@param[out] pszOut			-	����ִ�
	@return		0				-	�ɹ�  
	@return		����			-	ʧ��		
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
	@brief  ���ֺ���ĸʹ�ð����л��ֿ�����
 	@param[in]  col             -   ��������������
 	@param[in]  line            -   ������ʾ��λ��(��dispdispUseMode==USE_DISPLAY_EXʱ�����ﴫ��������ʾ��ʼy������)
 	@param[in]  clearEndLine    -   �����ʼλ�õ�����������
 	@param[in]  tipDispline     -   ��ĸѡ����ʾ��(��dispdispUseMode==USE_DISPLAY_EXʱ�����ﴫ����ĸѡ����ʾ��ʼy������)
 	@param[in]  ucMinlen        -   �ִ���С����,��СֵΪ0
 	@param[in]  ucMaxlen        -   �ִ���󳤶�,���ֵΪ128�ֽ�
 	@param[in]  ucTimeOut       -   �ӿڳ�ʱ�˳�ʱ��
 	@param[in]  pszIn           -   �������ʾ�ַ���
 	@param[in]  orgPassWord     -   �����Ԥ��ֵ�ַ���
 	@param[in]  dispUseMode     -   ������ʾ����ʹ��:USE_DISPLAY / USE_DISPLAY_EX
 	@param[out] pszOut          -   ����ִ�
 	@return     0               -   �ɹ�  
 	@return     ����          -   ʧ��      
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
	@brief	��������
 	@param[in] 	MinLen		-	������С����
 	@param[in] 	MaxLen		-	������󳤶�
 	@param[in] 	TimeOutMs	-	���볬ʱʱ�䣬<0��ʾ�޳�ʱ
 	@param[in] 	StrBuf		-	����-��ʼ��
 	@param[in] 	InputLine	-	������ʼ��
 	@param[in] 	EndLine		-	������ֹ��(��ʱ��Ч)
 	@param[in] 	iDispMode	-	����ģʽ(��ʱ��Ч)
	@param[out] StrBuf		-	���䴮���
	@return		0			-	�ɹ�  
	@return		����		-	ʧ��
	
@else
	@brief	input Chinese character 
 	@param[in] 	MinLen		-	The minimum length of the string input,
 	@param[in] 	MaxLen		-	The Maximum length of the string input
 	@param[in] 	TimeOutMs	-	timout to input��<0 means no timeout
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

