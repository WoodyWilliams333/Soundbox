
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
* @brief ��ѯ��������������Ƿ������Ч����
* @return ��ѯ�Ľ�??
*	-<em> == 1 </em>  ������Ч����
*	-<em> == 0 </em>  ��������Ч����
*/
extern int app_key_check(void);

/**
* @brief ��������Ļ������
* @return ִ�еĽ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int app_key_flush(void);

/**
* @brief ����ʽ��ȡ����ֵ
* @return ��ȡ�İ���ֵ
*	-<em> == 0 </em>  ��ȡ����ʧ��
*	-<em> >  0 </em>  ��ȡ�İ���ֵ������ֵ��Ӧ�İ������ο�sdk��key.h
*/
extern int app_key_get(void);

/**
* @brief ��һ����ʱʱ���ڻ�ȡ����ֵ
* @param[in] timeout_ms����ȡ����ֵ�ĳ�ʱʱ�䣬��λ���� 
* @return ��ȡ�İ���ֵ
*	-<em> == 0 </em>  ��ȡ����ʧ��
*	-<em> >  0 </em>  ��ȡ�İ���ֵ������ֵ��Ӧ�İ������ο�sdk��key.h
*/
extern int app_key_get_ms(uint32_t timeout_ms);

/************************* LCD module *************************************************/
/*
LCD��һЩ˵����
	1. Ŀǰ7220֧���������壺12*24 �� 8*16����ˣ�������ʹ��ǰ�ߣ��и�30��С����ʹ�ú��ߣ��и�20
	2. ʹ��ʱ����ע��С�����и߲����Ǵ������һ�룡
	3. �����ӿ��ǰ�������������
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

//  lcdDisplay��ʾģʽ
#ifndef DISP_ASCII
#define DISP_ASCII              (0   )      /**< С������ʾ(8*16) */
#endif
#ifndef DISP_CFONT
#define DISP_CFONT              (1<<0)      /**< ��������ʾ(12*24) */
#endif
#ifndef DISP_CLRLINE
#define DISP_CLRLINE            (1<<5)      /**< �����ʾռ�õ��� */
#endif
#ifndef DISP_MEDIACY
#define DISP_MEDIACY            (1<<6)      /**< ������ʾ */
#endif
#ifndef DISP_RIGHT
#define DISP_RIGHT            	(1<<9)      /**< ������ʾ */
#endif
#ifndef DISP_REVERSE
#define DISP_REVERSE            (1<<7)      /**< ������ʾ */
#endif
#ifndef DISP_INVLINE
#define DISP_INVLINE            (1<<4)      /**< ���з�����ʾ */
#endif
#ifndef DISP_FLIP
#define DISP_FLIP               (1<<8)      /**< ������ʾҲִ��flip */
#endif

// macros for screen functions
#define NUM_MAXZHCHARS      26          		// ÿ������ַ���Ŀ(������)
#define NUM_MAXCOLS         320         		// ÿ���������
#define NUM_MAXCOLNO        (NUM_MAXCOLS-1)     // ����к�
#define NUM_MAXLINES        12          		// �������
#define NUM_MAXLINENO       (NUM_MAXLINES-1)    // ����к�
#define NUM_MAXZHLINES      12           		// �����������
#define NUM_MAXCHARS        26


#define DISP_MAX_LEN        26		            //�����ʾ���ٸ��ֽ�
#define DISP_MAX_LINE       7		            //�����ʾ����
#define CLR_MAX_LINE        (DISP_MAX_LINE-1)*2 //����������

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


//���÷�����ɫ back_colorΪ����ɫ    fore_colorΪǰ��ɫ
void app_lcd_set_reverse_display(uint32_t back_color, uint32_t fore_color);


extern int app_lcd_get_language(void);
extern int app_lcd_set_language(int language);
extern int app_lcd_init(void);
extern int app_lcd_set_icon(int icon, appbool onoff);
extern int app_lcd_get_color(uint32_t *back_color, uint32_t *fore_color);
extern int app_lcd_set_color(uint32_t back_color, uint32_t fore_color);
extern void app_lcd_get_info(ST_LCD_INFO *lpLcdInfo);

/************************* key get string ************************************************/
//  ��������ƺͷ���ֵ
#ifndef 	KB_MAXLEN
#define     KB_MAXLEN               256         /**< �����������������ĳ���                   */
#endif
#ifndef		KB_EN_REVDISP
#define     KB_EN_REVDISP           0x01        /**< 1��0�� ����������ʾ                        */
#endif
#ifndef		KB_EN_FLOAT
#define     KB_EN_FLOAT             0x02        /**< 1��0�� �У���С����                      */
#endif
#ifndef		KB_EN_SHIFTLEFT
#define     KB_EN_SHIFTLEFT         0x04        /**< 1��0�� ���ң���������                    */
#endif
#ifndef		KB_EN_CRYPTDISP
#define     KB_EN_CRYPTDISP         0x08        /**< 1��0�� �ǣ������뷽ʽ                    */
#endif
#ifndef		KB_EN_CHAR
#define     KB_EN_CHAR              0x10        /**< 1��0�� �ܣ������ַ�                      */
#endif
#ifndef		KB_EN_NUM
#define     KB_EN_NUM               0x20        /**< 1��0�� �ܣ���������                      */
#endif
#ifndef		KB_EN_BIGFONT
#define     KB_EN_BIGFONT           0x40        /**< 1��0�� ��С������                        */
#endif
#ifndef		KB_EN_PRESETSTR
#define     KB_EN_PRESETSTR         0x80        /**< 1��0�� �ǣ�������Ԥ����ַ���            */
#endif
#ifndef		KB_EN_NEWLINE
#define     KB_EN_NEWLINE           0x100       /**< 1��0�� �ǣ���������������뻻����ʾ      */
#endif
#ifndef		KB_EN_HEX
#define     KB_EN_HEX               0x200       /**< 1��0�� �ǣ���ֻ������16��������          */
#endif
#ifndef		KB_EN_PREFIX
#define     KB_EN_PREFIX            0x400       /**< 1��0�� �ǣ�����ʾ����ǰ׺                */
#endif
#ifndef		KB_EN_CIRCULAR_ENTER
#define     KB_EN_CIRCULAR_ENTER    0x800       /**< 1��0�� �ǣ�������Բ��ɨ�뽨��enter��ʹ�� */
#endif
#ifndef		KB_EN_BIG_AMT
#define     KB_EN_BIG_AMT    		0x1000       /**< 1��0�� �ǣ��񣩴�������*/
#endif


//  Ԥ�輸�鳣�õ��������ģʽ
#ifndef		KB_BIG_ALPHA
#define     KB_BIG_ALPHA            0x1F5       /**< �������ַ�������               */
#endif
#ifndef		KB_BIG_NUM
#define     KB_BIG_NUM              0x1E5       /**< ���������ִ�����               */  
#endif
#ifndef		KB_BIG_PWD
#define     KB_BIG_PWD              0x6D        /**< ��������������                 */
#endif
#ifndef		KB_SMALL_ALPHA
#define     KB_SMALL_ALPHA          0x1B5       /**< С�����ַ�������               */      
#endif
#ifndef		KB_SMALL_NUM
#define     KB_SMALL_NUM            0x1A5       /**< С�������ִ�����               */
#endif
#ifndef		KB_SMALL_PWD
#define     KB_SMALL_PWD            0x2D        /**< С������������                 */
#endif
#ifndef		KB_CANCEL
#define     KB_CANCEL               -1          /**< �ַ������뱻�û���ȡ�����˳�   */
#endif
#ifndef		KB_TIMEOUT
#define     KB_TIMEOUT              -2          /**< �ַ������볬ʱ�˳�             */
#endif
#ifndef		KB_ERROR
#define     KB_ERROR                -3          /**< �ַ�����������Ƿ�             */
#endif

/**
* @brief �����ַ�ƫ������ƫ��
* @param[in] x��x��ƫ��
			line�� ������ʼ����
* @return ����ֵ
*	-<em> == 0 </em>  �ɹ�
*	-<em> > !=0 </em>  ʧ��
*/
extern int app_key_set_entry_location(int x, int line);
/**
* @brief �����ַ�ƫ������ƫ��
* @param[in] mode������ģʽ��KB_EN_CHAR|...)
			min_len ��С�����ַ���
			max_len ��������ַ���
			timeout_ms ����ʱ������
* @param[in/out]	str_buf  Ԥ���ַ�(����Ԥ��ģʽ)�����뷵���ַ���
* @return ����ֵ
*	-<em> >= 0 </em>  �����ַ�����
*	-<em> <0 </em>  ʧ��
*/
extern int app_key_get_string(uint32_t mode, int min_len, int max_len, int timeout_ms, char *str_buf);

/*
	MinLen: ������С����
	MaxLen: ������󳤶�
	TimeOutMs�� ���볬ʱʱ�䣬<0��ʾ�޳�ʱ
	StrBuf: ����-��ʼ��
			���-���䴮���
	InputLine: ������ʼ��
	EndLine: ������ֹ��(��ʱ��Ч)
	iDispMode: ����ģʽ(��ʱ��Ч)

	����ֵ: 0 �ɹ��� ��������(KB_CANCEL KB_TIMEOU...)
*/	
extern int app_kb_get_hz(int MinLen, int MaxLen, int TimeOutMs, char *StrBuf, int InputLine, int EndLine,  int  iDispMode);


/**************************************************************************************/


/**
* @brief ����wnet�����־���أ�Ĭ���������־�رյ�
* @param[in] on     �����õ���־����״̬����0��ʾ�򿪣�Ϊ0��ʾ�رգ��� LOGGER_MODULE_ON ö�ٶ���
* @return ���ú����־����״̬
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int seos_logger_on(int on);


/**
* @brief ��ȡlibseos��İ汾��Ϣ
* @param[out] version��libwnet��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int seos_get_version(char *version, int size);


#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of __SEOS_H__ */

