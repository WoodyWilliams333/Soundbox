
/**
@if Chinese
	 * @brief    此模块用于描述 <strong>绘图打印(Paint)模块</strong> 相关的接口
	 * @author   liluchang
	 * @date     2019-01-24
	 * @version  V1.0
	 * @remarks Change History:
	 * 日期          | 版本          | 作者            | 描述
	 * ------------- | ------------- | --------------- | ----
	 * 2019/01/24    | 1.0.0         | liluchang       | 创建文件
	 * 2022/04/19    | 1.0.1         | Wenming         | 增加英文注释
@else	 
	 * @brief    This module is used to describe <strong>Paint</strong> interfaces module
	 * @author   liluchang
	 * @date     2019-01-24
	 * @version  V1.0
	 * @remarks Change History:
	 * Date          | Version       | Author          | Desc
	 * ------------- | ------------- | --------------- | ----
	 * 2019/01/24    | 1.0.0         | liluchang       | Create file
	 * 2022/04/19    | 1.0.1         | Wenming         | Add English description
@endif	 
 */

/**
@if Chinese
	 * @defgroup PAINT 绘图打印
@else	 
	 * @defgroup PAINT Paint
 @endif
 * @{
 */


#ifndef __PAINT_H__
#define __PAINT_H__

#include "font.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void *Paint_t;

/**
 @if Chinese
	 * @brief  该枚举列出了绘图换行模式.
 @else	 
	 * @brief  This enumeration lists drawing newline modes.
 @endif	 
 */
typedef enum {
    MODE_NO_WRAP    =   0,              /**< @if Chinese 非自动换行 @else	Non-wrap	@endif*/
    MODE_LINE_WRAP  =   1,              /**< @if Chinese 自动换行   @else	Word wrap	@endif*/
} paint_newline_mode;

/**
 @if Chinese
	 * @brief  该结构体指定了一个矩形框参数
 @else		 
	 * @brief  This structure specifies a rectangle box parameter
  @endif	
 */
typedef struct _textRect {
    int  m_x;			/**<@if Chinese 矩形起点X坐标 	@else	The starting x-coordinate of the rectangle		@endif*/
    int  m_y;			/**<@if Chinese 矩形起点Y坐标 	@else	The starting y-coordinate of the rectangle		@endif*/
    uint32_t  width;  	/**<@if Chinese 高度  			@else	Width											@endif*/	
    uint32_t  height;  	/**<@if Chinese 宽度 			@else	Height											@endif*/
} textRect;

/**
@if Chinese
 * @brief  创建用户层的画笔paint
 * @param[in]	width			-	创建画布的像素宽度
 * @param[in]	height			-	创建画布的像素高度
 * @param[in]	bits_per_pixel	-	表示1像素使用的位数，即位/像素
 * @param[out]	paint			-	paint为指向指针的指针，用于输出打开paint的有效指针
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
@else 
 * @brief  Create a brush paint for the user layer
 * @param[in]	width			-	Creates the pixel width of the canvas
 * @param[in]	height			-	Creates the pixel height of the canvas
 * @param[in]	bits_per_pixel	-	Represents the number of bits used by 1 pixel, i.e. bits per pixel
 * @param[out]	paint			-	Paint is a pointer to a pointer that prints a valid pointer to open paint
 * @return int
 *          - =0  Success
 *          - <0  Fail，Returns the corresponding return value
@endif 
 */
int paint_create_user(int width, int height, int bits_per_pixel, Paint_t *paint);

/**
@if Chinese
 * @brief  销毁用户层创建的画笔paint
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
@else 
 * @brief  Destroys the brush paint created by the user layer
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail，Returns the corresponding return value
@endif 
 */
int paint_destory_user(const Paint_t paint);

/**
@if Chinese
 * @brief  在用户创建的画布上清除矩形区域
 * @param[in]	x		-	起始位置的x坐标
 * @param[in]	y		-	起始位置的y坐标
 * @param[in]	width	-	矩形的宽度
 * @param[in]	height	-	矩形的高度
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
@else 
 * @brief  Clears rectangular areas on the user-created canvas
 * @param[in]	x		-	The x-coordinate of our starting position
 * @param[in]	y		-	The y-coordinate of our starting position
 * @param[in]	width	-	Width of rectangle
 * @param[in]	height	-	Height of rectangle
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail，Returns the corresponding return value
@endif 
 */
int paint_clean_rect_user(int x, int y, uint32_t width, uint32_t height, const Paint_t paint);

/**
 @if Chinese
	 * @brief  在用户创建的画布上画图片
	 * @param[in]	x		-	起始位置的x坐标
	 * @param[in]	y		-	起始位置的y坐标
	 * @param[in]	m_pic	-	BMP图片的完整数据内容，包含头部信息
	 * @param[in]	paint	-	paint create user返回的paint
	 * @return int
	 *          - =0  成功
	 *          - <0  失败，返回相应的返回值
	 * @note
	 *          - 此接口暂时仅支持BMP图片，m_pic内容包括BMP图片的头部信息
 @else	 
	 * @brief  Draw a picture on the canvas created by the user
	 * @param[in]	x		-	The x-coordinate of our starting position
	 * @param[in]	y		-	The y-coordinate of our starting position
	 * @param[in]	m_pic	-	Complete data content of BMP images, including header information
	 * @param[in]	paint	-	paint create user return paint value
	 * @return int
	 *          - =0  Success
	 *          - <0  Fail
	 * @note
	 *          - This interface supports only BMP images. The m_pic content contains the header information of BMP images
 @endif	 
 */
int paint_draw_picturefile_user(int x, int y, const void *m_pic, const Paint_t paint);

/**
 @if Chinese
 * @brief  设置用户层创建的画笔paint的换行模式
 * @param[in]	mode	-	换行的模式，@ref paint_newline_mode
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 @else 
 * @brief  Sets the newline mode for the paint created by the user layer
 * @param[in]	mode	-	Newline mode，@ref paint_newline_mode
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
  @endif
 */
int paint_set_auto_newline_user(int mode, Paint_t paint);

/**
 @if Chinese
	 * @brief  获取用户层创建的画笔paint的换行模式
	 * @param[in]	paint	-	paint create user返回的paint
	 * @return int
	 *          - >=0  成功，返回当前的换行模式
	 *          - <0   失败，返回相应的返回值
  @else
	 * @brief  Gets the newline mode for the brush paint created by the user layer
	 * @param[in]	paint	-	paint create user return paint value
	 * @return int
	 *          - >=0  Success
	 *          - <0   Fail
  @endif
 */
int paint_get_newline_mode_user(const Paint_t paint);

/**
 @if Chinese
 * @brief  在用户创建的画布上画字符串
 * @param[in]	pfont	-	打开字库取的的有效字库操作句柄
 * @param[in]	x		-	起始位置的x坐标，可传负值
 * @param[in]	y		-	起始位置的y坐标
 * @param[in]	lpText	-	字符串内容
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 * @note
 *          - 当坐标是负值时，字体显示相当于超出显示屏区域，不会显示，可达到只显示一个字的部分效果。
 @else
 * @brief  Draw strings on a user-created canvas
 * @param[in]	pfont	-	Open a valid font operation handle from the font
 * @param[in]	x		-	The x coordinate of the starting position, which can pass negative values
 * @param[in]	y		-	The y coordinate of our starting position
 * @param[in]	lpText	-	Src buf value
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
 * @note
 *          - When the coordinates are negative, the font display is equivalent to beyond the display area, will not be displayed, can achieve only a partial effect of the display of a word.
  @endif
 */
int paint_draw_text_user(font_t pfont, int x, int y, const char *lpText, const Paint_t paint);

/**
 @if Chinese
	 * @brief  在用户创建的画布上画像素点
	 * @param[in]	x		-	画点的x坐标
	 * @param[in]	y		-	画点的y坐标
	 * @param[in]	paint	-	paint create user返回的paint
	 * @return int
	 *          - =0  成功
	 *          - <0  失败，返回相应的返回值
 @else
	 * @brief  Draw pixels on a user-created canvas
	 * @param[in]	x		-	Let me draw my point x
	 * @param[in]	y		-	Let me draw my point y
	 * @param[in]	paint	-	paint create user return paint value
	 * @return int
	 *          - =0  Success
	 *          - <0  Fail
@endif
 */
int paint_draw_pixel_user(int x, int y, const Paint_t paint);

/**
 @if Chinese
 * @brief  获取在用户创建的画布上画像素点的颜色值
 * @param[in]	x		-	画点的x坐标
 * @param[in]	y		-	画点的y坐标
 * @param[out]	color	-	画点的颜色值，采用RGB888，24位色的表示形式
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 @else 
 * @brief  Gets the color value for drawing pixels on a user-created canvas
 * @param[in]	x		-	Let me draw my point x
 * @param[in]	y		-	Let me draw my point y
 * @param[out]	color	-	Point color value, using RGB888, 24 - bit color representation
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
  @endif
 */
int paint_get_pixel_user(int x, int y, uint32_t *color, const Paint_t paint) ;

/**
 @if Chinese
 * @brief  在用户创建的画布上画线
 * @param[in]	x1	-	画线起始点的x坐标
 * @param[in]	y1	-	画线起始点的y坐标
 * @param[in]	x2	-	画线终点的x坐标
 * @param[in]	y2	-	画线终点的y坐标
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 @else 
 * @brief  Draw lines on the canvas created by the user
 * @param[in]	x1	-	Draw the x coordinate of the starting point of the line
 * @param[in]	y1	-	Draw the y coordinate of the starting point of the line
 * @param[in]	x2	-	Draw the x-coordinate at the end of the line
 * @param[in]	y2	-	Draw the y-coordinate at the end of the line
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
 @endif 
 */
int paint_draw_line_user(int x1, int y1, int x2, int y2, const Paint_t paint);

/**
 @if Chinese
 * @brief  设置用户层创建的画笔paint的行空白
 * @param[in]	line_space	-	行空白
 * @param[in]	paint		-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 @else 
 * @brief  Sets the line whitespace for the paint created by the user layer
 * @param[in]	line_space	-	Blank line
 * @param[in]	paint		-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
 @endif 
 */
int paint_set_line_space_user(int line_space, Paint_t paint);

/**
 @if Chinese
 * @brief  设置用户层创建的画笔paint的当前操作坐标
 * @param[in]	width	-	欲设置的宽度值
 * @param[in]	height	-	欲设置的高度值
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - 0  成功
 *          - <0 失败，返回相应的返回值
@else
 * @brief  Sets the current operation coordinates of the brush paint created by the user layer
 * @param[in]	width	-	The width value to set
 * @param[in]	height	-	The height value to set
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - 0  Success
 *          - <0 Fail
 @endif 
 */
int paint_set_current_location_user(int width, int height, Paint_t paint);

/**
 @if Chinese
 * @brief  获取用户层创建的画笔paint的当前操作坐标
 * @param[out]	width	-	返回当前操作坐标的宽度值
 * @param[out]	height	-	返回当前操作坐标的高度值
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - 0  成功
 *          - <0 失败，返回相应的返回值
 * @note
 *          - 该接口不适用打印图片
 @else 
 * @brief  Gets the current operation coordinates of the brush paint created by the user layer
 * @param[out]	width	-	Returns the width value of the current operation coordinate
 * @param[out]	height	-	Returns the height value of the current operation coordinate
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - 0  Success
 *          - <0 Fail
 * @note
 *          - This interface is not suitable for printing pictures
 @endif 
 */
int paint_get_current_location_user(int *width, int *height,
                                    const Paint_t paint);

/**
 @if Chinese
 * @brief  设置用户层创建的画笔paint的前景色和背景色
 * @param[in]	back_color	-	欲设置的背景颜色值，采用RGB888，24位色的表示形式
 * @param[in]	fore_color	-	欲设置的前景颜色值，采用RGB888，24位色的表示形式
 * @param[in]	paint		-	paint create user返回的paint
 * @return int
 *          - 0  成功
 *          - <0 失败，返回相应的返回值
 @else
 * @brief  Sets the foreground and background colors for the paint created by the user layer
 * @param[in]	back_color	-	The background color value to be set is RGB888, 24-bit color representation
 * @param[in]	fore_color	-	To set the foreground color value, use RGB888, 24 - bit color representation
 * @param[in]	paint		-	paint create user return paint value
 * @return int
 *          - 0  Success
 *          - <0 Fail
@endif
 */
int paint_set_color_user(uint32_t back_color, uint32_t fore_color, Paint_t paint);

/**
 @if Chinese
 * @brief  获取用户层创建的画笔paint的前景色和背景色
 * @param[out]	back_color	-	存储当前paint的背景颜色值，采用RGB888，24位色的表示形式
 * @param[out]	fore_color	-	存储当前paint的前景颜色值，采用RGB888，24位色的表示形式
 * @param[in]	paint		-	paint create user返回的paint
 * @return int
 *          - 0  成功
 *          - <0 失败，返回相应的返回值
 @else 
 * @brief  Gets the foreground and background colors of the brush paint created by the user layer
 * @param[out]	back_color	-	Stores the current paint background color value in RGB888, 24-bit color representation
 * @param[out]	fore_color	-	Stores the current paint foreground color value in RGB888, 24-bit color representation
 * @param[in]	paint		-	paint create user return paint value
 * @return int
 *          - 0  Success
 *          - <0 Fail
 @endif 
 */
int paint_get_color_user(uint32_t *back_color, uint32_t *fore_color, const Paint_t paint);

/**
 @if Chinese
 * @brief  获取用户层创建的画笔paint的buffer内容
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - 非NULL  成功，返回当前的paint绑定buffer内容
 *          - NULL    失败
 @else
 * @brief  Gets the buffer contents of the brush paint created by the user layer
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - !NULL  Success
 *          - NULL    Fail
 @endif 
 */
void *paint_get_buf_user(const Paint_t paint);

/**
 @if Chinese
 * @brief  在用户创建的画布上画字符串，该画字符串区域被限制在一个参数有rect指定矩形框内
 * @param[in]	fd		-	打开字库取的的有效字库操作句柄
 * @param[in]	nX		-	起始位置的x坐标，可传负值
 * @param[in]	nY		-	起始位置的y坐标，可传负值
 * @param[in]	rect	-	矩形框参数 参考@link textRect textRect @endlink
 * @param[in]	lpText	-	字符串内容
 * @param[in]	paint	-	paint create user返回的paint
 * @return int
 *          - =0  成功
 *          - <0  失败，返回相应的返回值
 * @note
 *          - 注意该接口是限制在一个矩形框内显示，不会对矩形框外的区域打点，矩形框坐标只能在屏幕坐标范围内，当坐标传为（0，x），
 *           参数nX为负数时，可以显示在最左边，y坐标类似。
 @else 
 * @brief  Draws a string on a user-created canvas. The string area is confined to a rectangle with rect specified as the parameter
 * @param[in]	fd		-	Open a valid font operation handle from the font
 * @param[in]	nX		-	The x coordinate of the starting position, which can pass negative values
 * @param[in]	nY		-	The y coordinate of the starting position, which can pass negative values
 * @param[in]	rect	-	Rectangle box parameter, reference@link textRect textRect @endlink
 * @param[in]	lpText	-	String content
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
 * @note
 *          - Note that this interface is limited to a rectangular box display, does not dot the area outside the rectangular box, rectangular box coordinates can only be within the screen coordinates, when the coordinate is passed to (0, x),
 *			If the parameter nX is negative, it can be displayed on the far left, and the y coordinates are similar。
 @endif 
 */
int paint_draw_text_rect_user(void *fd, int nX, int nY, void *rect, const char *lpText, Paint_t paint);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PAINT_H__ */

/** @} */

