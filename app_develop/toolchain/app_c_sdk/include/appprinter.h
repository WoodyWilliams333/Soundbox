/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app printerģ��</strong> ��صĽӿ�
	 * @par �ļ�    appprinter.h
	 * @author		yangjing
	 * @date        2020-04-11
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-11    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-20    | 1.0.1        | liyanping     | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app printer</strong>  module
	 * @par file    appprinter.h
	 * @author		yangjing
	 * @date        2020-04-11
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-11    | 1.0.0        | yanjing       | create file
	 * 2022-04-20    | 1.0.1        | liyanping     | Add English description
 @endif
*/

/*!
 @if Chinese
	*@addtogroup appprinter ��ӡ
 @else
	*@addtogroup appprinter printer 
 @endif
 * @{
*/

#ifndef _APP_PRINTER_H_
#define _APP_PRINTER_H_

#include <printer.h>

/*!
 @if Chinese
	@brief  ��ö�������г��˴�ӡ�����ʽ.
 @else
	@brief  This enumerated type lists the font types for print.
 @endif
  */
typedef enum{
	PRT_FONT_SMALL = 0,		/**< @if Chinese С�����ʽ @else  small font @endif */	 
	PRT_FONT_BIG,			/**< @if Chinese �������ʽ @else  big font @endif */
}E_PRINTER_FONT;

/*!
 @if Chinese
  * @brief  ��ö�������г���������뷽ʽ.
@else  
  * @brief  This enumerated type lists the font alignment.
@endif
*/
typedef enum{
	PRT_LEFT = 0,			/**< @if Chinese ��ӡ������� @else  Align left when printing @endif */	
	PRT_MID,				/**< @if Chinese ��ӡ���ж��� @else  Align center when printing @endif */	
	PRT_RIGHT				/**< @if Chinese ��ӡ���Ҷ��� @else  Align right when printing @endif */	
}E_PRINT_MODE;

/*!
 @if Chinese
  * @brief  ��������������/�߶ȵĽṹ��.
@else  
  * @brief  A structure that describes the width/height of a font.
@endif
*/
typedef struct st_font_info{
	int width;				/**< @if Chinese ��ӡ������  @else the width of print-font @endif */	
	int height;				/**< @if Chinese ��ӡ����߶�  @else the height of print-font @endif */	
}ST_FONT_INFO;


/*!
 @if Chinese
  * @brief  ������������ӡͼƬ����Դ�������Ľṹ��.
@else  
  * @brief  A structure that describes the data source and index of the printed image.
@endif
*/
typedef struct _BMP_PRINT_CH{
	const char *character;			/**< @if Chinese ͼƬ�����ַ�  @else index character of picture @endif */	
	const char *bmpSrc;			  	/**< @if Chinese ͼƬԴ����   @else  source data of picture @endif*/
}ST_BMP_PRINT;

/*!
 @if Chinese
  * @brief  ������������ӡ�����ʽ��ͼƬ��Ϣ�Ľṹ��.
@else  
  * @brief  A structure that describes the font format and picture information to be printed.
@endif
*/
typedef struct{
	ST_FONT_INFO font;			  	/**< @if Chinese �����ʽ��Ϣ     @else  font-type info  @endif*/
	ST_BMP_PRINT *pBmpUnits;		/**< @if Chinese ͼƬ��Ϣ����ָ�� @else  array pointer for picture information @endif*/
}ST_SELDEF_PRINT;

#define MAX_PRINTER_BUFFER	1024	/**< @if Chinese ��ӡ��󻺳��С @else the max buffer for print @endif*/


/**
 @if Chinese
	* @brief		��ӡģ���ʼ��
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ�ܣ��ο�E_APP_RET����
 @else
	* @brief		printer init,must be initialized before using it
	* @return		0			-	success
	* @return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_init(void);

/*!
 @if Chinese
 	@brief		��ӡģ�����λ
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
 @else
	@brief		printer reset
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_reset(void);

 /*!
 @if Chinese
 	@brief		�رմ�ӡģ��
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
 @else
	@brief		printer close
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_close(void);


/*!
 @if Chinese
 	@brief		���õ�ǰ��ӡ�����ʽ
 	@param[in]	font		-	�����ʽ���ο�E_PRINTER_FONT����
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		set print-font 
 	@param[in]	font		-	Font format, refer to E_PRINTER_FONT definition
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/
int app_prt_setfont(E_PRINTER_FONT font);

 /*!
 @if Chinese
 	@brief		��ȡ��ӡ��״̬
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		get the status of printer 
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/
int app_prt_get_status(void);


/*!
 @if Chinese
 	@brief		��ȡһ���ڿɴ�ӡ������ַ���
 	@param[in]	font		-	�����ʽ���ο�E_PRINTER_FONT����			
	@return     �����ַ���
 @else
	@brief		get max bytes of the printable characters in a line
	@param[in]	font		-	font type��Refer to the definition of E_PRINTER_FONT		
	@return		bytes of chars
 @endif
*/ 
int app_prt_get_linechars(E_PRINTER_FONT font);


/*!
 @if Chinese
	@brief		��ȡ�����ߴ�(�߶�)
	@return		�������ߴ�(�߶�)
 @else
	@brief		Get canvas size (height)
	@return 	the max size (height) of canvas
 @endif
*/ 
int app_prt_get_paint_size(void);

 /*!
 @if Chinese
	@brief		��ȡ������ǰ���Ƹ߶�
	@return  	������ǰ���Ƹ߶�
 @else
	@brief		Gets the current painting height of the canvas
	@return  	the painting height of the canvas
 @endif
*/
int app_prt_get_cur_height(void);


 /*!
 @if Chinese
	@brief		��ʽ�����ƴ�ӡ����,Ĭ��ʹ�ÿ������
	@param[in]	fmt			-	��ӡ���ݸ�ʽ���ַ���			
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
 @else
	@brief		Format and draw the print canvas. Align left by default
	@param[in] 	fmt			-	format string for Print content	
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/ 
int app_prt_printf(const char *fmt, ...);

 /*!
 @if Chinese
	@brief		��ָ��ģʽ��ʽ�����ƴ�ӡ����
	@param[in]	mode		-	��ӡģʽ���ο�E_PRINT_MODE����
	@param[in]	fmt			-	��ӡ���ݸ�ʽ���ַ���			
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		Format and draw the print canvas. Align left by default
	@param[in]	mode		- 	print mode��Refer to the definition of E_PRINT_MODE
	@param[in]	fmt			- 	format string for Print content	
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/  
int app_prt_printf_fmt(E_PRINT_MODE mode, const char *fmt, ...);

 
  /*!
 @if Chinese
	@brief		����Ŵ���ƴ�ӡ����
	@param[in]	w_scale		-	�������������1
	@param[in]	h_scale		-	�������������1
	@param[in]	fmt			-	��ӡ���ݸ�ʽ���ַ���			
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		draw print canvas in enlarged Font 
	@param[in]	w_scale		-	 Horizontal scale, greater than 1
	@param[in]	h_scale		- 	 Longitudinal scale, greater than 1
	@param[in]	fmt			-	 format string for Print content	
	@return		0			-	 success
	@return		other		-	 fail,refer to the definition of E_APP_RET
	
 @endif
*/  
int app_prt_printf_big(int w_scale, int h_scale, const char *fmt, ...);


/*!
 @if Chinese
	@brief		��ʽ�������Զ�����������ӡ����
	@param[in]	lpSelfdefprt-	�Զ�������ṹ���ο�ST_SELDEF_PRINT����
	@param[in]	fmt			-	��ӡ���ݸ�ʽ���ַ���			
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		draw print canvas in self-defined font 
	@param[in]	lpSelfdefprt- 	structure of self-defined font��reference ST_SELDEF_PRINT
	@param[in]	fmt			- 	format string for Print content	
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/ 
int app_prt_printf_sefdef_font(ST_SELDEF_PRINT *lpSelfdefprt, const char *fmt, ...);


/*!
 @if Chinese
	@brief		����BMPͼƬ�ļ�����ӡ������ͼƬӦΪ�ڰ�ɫbmp��ʽ(�ļ���ʽ)
	@param[in]	pfilepath	-	�ļ���Ӧ�ù���Ŀ¼�µ����·��
	@param[in]	x			-	��ӡλ����ʼx��
	@param[in]	y			-	��ӡλ����ʼy��
	@param[in]	bmp_width	-	ͼƬ��ȣ���������������
	@param[in]	bmp_height	-	ͼƬ�߶ȣ���������������		
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		Draw BMP picture file to the print canvas, and the picture should be in black-and-white BMP format (file mode)
	@param[in]	pfilepath	- 	The relative path of the file in the application working directory
	@param[in]	x			- 	Print start position on X axis
	@param[in]	y			- 	Print start position on Y axis
	@param[in]	bmp_width	- 	Picture width, reserved, does not work
	@param[in]	bmp_height	- 	Picture height, reserved, does not work
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/ 
int app_prt_printf_bmp_file(const char *pfilepath, int x, int y, int bmp_width, int bmp_height);


/*!
 @if Chinese
	@brief		����BMPͼƬ�ļ�����ӡ������ͼƬӦΪ�ڰ�ɫbmp��ʽ(�ڴ淽ʽ)
	@param[in]	x			-	��ӡλ����ʼx��
	@param[in]	y			-	��ӡλ����ʼy��
	@param[in]	pbmpsrc		-	bmp�ļ�����Դ
	@param[in]	bmplen		-	bmp�ļ����ݳ���
	@param[in]	bmp_width	-	ͼƬ���
	@param[in]	bmp_height	-	ͼƬ�߶�	
	@param[in]	align		-	ͼƬ���뷽ʽ
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		Draw BMP picture file to the print canvas, and the picture should be in black-and-white BMP format (memory mode)
	@param[in]	x			-	Print start position on X axis
	@param[in]	y			-	Print start position on Y axis
	@param[in]	pbmpsrc		-	data source of BMP file 
	@param[in]	bmplen		-	data length of BMP file
	@param[in]	bmp_width	-	Picture width 
	@param[in]	bmp_height	-	Picture height 
	@param[in]	align		-	alignType of Picture 
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/  
int app_prt_printf_bmp_buffer(int x, int y, const uint8_t *pbmpsrc, int bmplen, int bmp_width, int bmp_height, E_PRINT_MODE align);

 /*!
 @if Chinese
	@brief		����BMPͼƬ�ļ�����ӡ������ͼƬӦΪ�ڰ�ɫbmp��ʽ����������ν��зŴ�(�ļ���ʽ)
	@param[in]	pfile		-	�ļ���Ӧ�ù���Ŀ¼�µ����·��
	@param[in]	alignType	-	���뷽ʽ:1-���� 2-�Ҷ��� ����-�����
	@param[in]	margin		-	ƫ����		
	@param[in]	bmp_width	-	ͼƬ���
	@param[in]	bmp_height	-	ͼƬ�߶�	
	@param[in]	zoom_in		-	�Ŵ���
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		Draw BMP picture file to the printing canvas. The picture should be in black-and-white BMP format and enlarged according to the input parameters (file mode)	
	@param[in]	pfile		-	The relative path of the file in the application working directory		
	@param[in]	alignType	-	Alignment:1 - Center; 2 - align right; other - align left
	@param[in]	margin		-	Offset	
	@param[in]	bmp_width	-	Picture width 
	@param[in]	bmp_height	-	Picture height 
	@param[in]	zoom_in		-	zoom_in times , Magnification
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/  
int app_prt_printf_bmp_file_zoomin(const char *pfile, int alignType, int margin, int bmp_width, int bmp_height, int zoom_in);


/*!
 @if Chinese
	@brief		������ӡ��������
	@return		0			-	�ɹ�
	@return		����		-	ʧ�ܣ��ο�E_APP_RET����
	
 @else
	@brief		Start printing canvas content
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/ 
int app_prt_start(void);


/*!
 @if Chinese
	@brief		���ô�ӡ��ֽƫ����
	@param[in]	offst	- ������ֽƫ�Ƹ߶�
	@return  	����ʵ��������ֽ�߶�
 @else
	@brief		Set the print run offset
	@param[in]	offst	- offset height of the paper feed 
	@return		Return to the actual increased paper feeding height
 @endif
*/ 
int app_prt_step(int offst);

#endif

