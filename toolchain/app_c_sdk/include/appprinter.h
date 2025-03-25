/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app printer模块</strong> 相关的接口
	 * @par 文件    appprinter.h
	 * @author		yangjing
	 * @date        2020-04-11
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-11    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-20    | 1.0.1        | liyanping     | 增加英文注释  
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
	*@addtogroup appprinter 打印
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
	@brief  该枚举类型列出了打印字体格式.
 @else
	@brief  This enumerated type lists the font types for print.
 @endif
  */
typedef enum{
	PRT_FONT_SMALL = 0,		/**< @if Chinese 小字体格式 @else  small font @endif */	 
	PRT_FONT_BIG,			/**< @if Chinese 大字体格式 @else  big font @endif */
}E_PRINTER_FONT;

/*!
 @if Chinese
  * @brief  该枚举类型列出了字体对齐方式.
@else  
  * @brief  This enumerated type lists the font alignment.
@endif
*/
typedef enum{
	PRT_LEFT = 0,			/**< @if Chinese 打印靠左对齐 @else  Align left when printing @endif */	
	PRT_MID,				/**< @if Chinese 打印居中对齐 @else  Align center when printing @endif */	
	PRT_RIGHT				/**< @if Chinese 打印靠右对齐 @else  Align right when printing @endif */	
}E_PRINT_MODE;

/*!
 @if Chinese
  * @brief  用于描述字体宽度/高度的结构体.
@else  
  * @brief  A structure that describes the width/height of a font.
@endif
*/
typedef struct st_font_info{
	int width;				/**< @if Chinese 打印字体宽度  @else the width of print-font @endif */	
	int height;				/**< @if Chinese 打印字体高度  @else the height of print-font @endif */	
}ST_FONT_INFO;


/*!
 @if Chinese
  * @brief  用于描述所打印图片数据源和索引的结构体.
@else  
  * @brief  A structure that describes the data source and index of the printed image.
@endif
*/
typedef struct _BMP_PRINT_CH{
	const char *character;			/**< @if Chinese 图片索引字符  @else index character of picture @endif */	
	const char *bmpSrc;			  	/**< @if Chinese 图片源数据   @else  source data of picture @endif*/
}ST_BMP_PRINT;

/*!
 @if Chinese
  * @brief  用于描述所打印字体格式和图片信息的结构体.
@else  
  * @brief  A structure that describes the font format and picture information to be printed.
@endif
*/
typedef struct{
	ST_FONT_INFO font;			  	/**< @if Chinese 字体格式信息     @else  font-type info  @endif*/
	ST_BMP_PRINT *pBmpUnits;		/**< @if Chinese 图片信息数组指针 @else  array pointer for picture information @endif*/
}ST_SELDEF_PRINT;

#define MAX_PRINTER_BUFFER	1024	/**< @if Chinese 打印最大缓冲大小 @else the max buffer for print @endif*/


/**
 @if Chinese
	* @brief		打印模块初始化
	* @return		0			-	成功
	* @return		其它		-	失败，参考E_APP_RET定义
 @else
	* @brief		printer init,must be initialized before using it
	* @return		0			-	success
	* @return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_init(void);

/*!
 @if Chinese
 	@brief		打印模块初复位
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
 @else
	@brief		printer reset
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_reset(void);

 /*!
 @if Chinese
 	@brief		关闭打印模块
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
 @else
	@brief		printer close
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/
int app_prt_close(void);


/*!
 @if Chinese
 	@brief		设置当前打印字体格式
 	@param[in]	font		-	字体格式，参考E_PRINTER_FONT定义
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
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
 	@brief		获取打印机状态
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
 @else
	@brief		get the status of printer 
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/
int app_prt_get_status(void);


/*!
 @if Chinese
 	@brief		获取一行内可打印的最大字符数
 	@param[in]	font		-	字体格式，参考E_PRINTER_FONT定义			
	@return     返回字符数
 @else
	@brief		get max bytes of the printable characters in a line
	@param[in]	font		-	font type，Refer to the definition of E_PRINTER_FONT		
	@return		bytes of chars
 @endif
*/ 
int app_prt_get_linechars(E_PRINTER_FONT font);


/*!
 @if Chinese
	@brief		获取画布尺寸(高度)
	@return		画布最大尺寸(高度)
 @else
	@brief		Get canvas size (height)
	@return 	the max size (height) of canvas
 @endif
*/ 
int app_prt_get_paint_size(void);

 /*!
 @if Chinese
	@brief		获取画布当前绘制高度
	@return  	画布当前绘制高度
 @else
	@brief		Gets the current painting height of the canvas
	@return  	the painting height of the canvas
 @endif
*/
int app_prt_get_cur_height(void);


 /*!
 @if Chinese
	@brief		格式化绘制打印画布,默认使用靠左对齐
	@param[in]	fmt			-	打印内容格式化字符串			
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
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
	@brief		按指定模式格式化绘制打印画布
	@param[in]	mode		-	打印模式，参考E_PRINT_MODE定义
	@param[in]	fmt			-	打印内容格式化字符串			
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
 @else
	@brief		Format and draw the print canvas. Align left by default
	@param[in]	mode		- 	print mode，Refer to the definition of E_PRINT_MODE
	@param[in]	fmt			- 	format string for Print content	
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/  
int app_prt_printf_fmt(E_PRINT_MODE mode, const char *fmt, ...);

 
  /*!
 @if Chinese
	@brief		字体放大绘制打印画布
	@param[in]	w_scale		-	横向比例，大于1
	@param[in]	h_scale		-	纵向比例，大于1
	@param[in]	fmt			-	打印内容格式化字符串			
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
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
	@brief		格式化绘制自定义字体至打印画布
	@param[in]	lpSelfdefprt-	自定义字体结构，参考ST_SELDEF_PRINT定义
	@param[in]	fmt			-	打印内容格式化字符串			
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
 @else
	@brief		draw print canvas in self-defined font 
	@param[in]	lpSelfdefprt- 	structure of self-defined font，reference ST_SELDEF_PRINT
	@param[in]	fmt			- 	format string for Print content	
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
	
 @endif
*/ 
int app_prt_printf_sefdef_font(ST_SELDEF_PRINT *lpSelfdefprt, const char *fmt, ...);


/*!
 @if Chinese
	@brief		绘制BMP图片文件至打印画布，图片应为黑白色bmp格式(文件方式)
	@param[in]	pfilepath	-	文件在应用工作目录下的相对路径
	@param[in]	x			-	打印位置起始x轴
	@param[in]	y			-	打印位置起始y轴
	@param[in]	bmp_width	-	图片宽度，保留，不起作用
	@param[in]	bmp_height	-	图片高度，保留，不起作用		
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
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
	@brief		绘制BMP图片文件至打印画布，图片应为黑白色bmp格式(内存方式)
	@param[in]	x			-	打印位置起始x轴
	@param[in]	y			-	打印位置起始y轴
	@param[in]	pbmpsrc		-	bmp文件数据源
	@param[in]	bmplen		-	bmp文件数据长度
	@param[in]	bmp_width	-	图片宽度
	@param[in]	bmp_height	-	图片高度	
	@param[in]	align		-	图片对齐方式
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
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
	@brief		绘制BMP图片文件至打印画布，图片应为黑白色bmp格式，并按照入参进行放大(文件方式)
	@param[in]	pfile		-	文件在应用工作目录下的相对路径
	@param[in]	alignType	-	对齐方式:1-居中 2-右对齐 其他-左对齐
	@param[in]	margin		-	偏移量		
	@param[in]	bmp_width	-	图片宽度
	@param[in]	bmp_height	-	图片高度	
	@param[in]	zoom_in		-	放大倍数
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
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
	@brief		启动打印画布内容
	@return		0			-	成功
	@return		其它		-	失败，参考E_APP_RET定义
	
 @else
	@brief		Start printing canvas content
	@return		0			-	success
	@return		other		-	fail,refer to the definition of E_APP_RET
 @endif
*/ 
int app_prt_start(void);


/*!
 @if Chinese
	@brief		设置打印走纸偏移量
	@param[in]	offst	- 增加走纸偏移高度
	@return  	返回实际增加走纸高度
 @else
	@brief		Set the print run offset
	@param[in]	offst	- offset height of the paper feed 
	@return		Return to the actual increased paper feeding height
 @endif
*/ 
int app_prt_step(int offst);

#endif

