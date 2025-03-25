
/**
@if Chinese
	 * @brief    ��ģ���������� <strong>��ͼ��ӡ(Paint)ģ��</strong> ��صĽӿ�
	 * @author   liluchang
	 * @date     2019-01-24
	 * @version  V1.0
	 * @remarks Change History:
	 * ����          | �汾          | ����            | ����
	 * ------------- | ------------- | --------------- | ----
	 * 2019/01/24    | 1.0.0         | liluchang       | �����ļ�
	 * 2022/04/19    | 1.0.1         | Wenming         | ����Ӣ��ע��
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
	 * @defgroup PAINT ��ͼ��ӡ
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
	 * @brief  ��ö���г��˻�ͼ����ģʽ.
 @else	 
	 * @brief  This enumeration lists drawing newline modes.
 @endif	 
 */
typedef enum {
    MODE_NO_WRAP    =   0,              /**< @if Chinese ���Զ����� @else	Non-wrap	@endif*/
    MODE_LINE_WRAP  =   1,              /**< @if Chinese �Զ�����   @else	Word wrap	@endif*/
} paint_newline_mode;

/**
 @if Chinese
	 * @brief  �ýṹ��ָ����һ�����ο����
 @else		 
	 * @brief  This structure specifies a rectangle box parameter
  @endif	
 */
typedef struct _textRect {
    int  m_x;			/**<@if Chinese �������X���� 	@else	The starting x-coordinate of the rectangle		@endif*/
    int  m_y;			/**<@if Chinese �������Y���� 	@else	The starting y-coordinate of the rectangle		@endif*/
    uint32_t  width;  	/**<@if Chinese �߶�  			@else	Width											@endif*/	
    uint32_t  height;  	/**<@if Chinese ��� 			@else	Height											@endif*/
} textRect;

/**
@if Chinese
 * @brief  �����û���Ļ���paint
 * @param[in]	width			-	�������������ؿ��
 * @param[in]	height			-	�������������ظ߶�
 * @param[in]	bits_per_pixel	-	��ʾ1����ʹ�õ�λ������λ/����
 * @param[out]	paint			-	paintΪָ��ָ���ָ�룬���������paint����Чָ��
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Create a brush paint for the user layer
 * @param[in]	width			-	Creates the pixel width of the canvas
 * @param[in]	height			-	Creates the pixel height of the canvas
 * @param[in]	bits_per_pixel	-	Represents the number of bits used by 1 pixel, i.e. bits per pixel
 * @param[out]	paint			-	Paint is a pointer to a pointer that prints a valid pointer to open paint
 * @return int
 *          - =0  Success
 *          - <0  Fail��Returns the corresponding return value
@endif 
 */
int paint_create_user(int width, int height, int bits_per_pixel, Paint_t *paint);

/**
@if Chinese
 * @brief  �����û��㴴���Ļ���paint
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Destroys the brush paint created by the user layer
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail��Returns the corresponding return value
@endif 
 */
int paint_destory_user(const Paint_t paint);

/**
@if Chinese
 * @brief  ���û������Ļ����������������
 * @param[in]	x		-	��ʼλ�õ�x����
 * @param[in]	y		-	��ʼλ�õ�y����
 * @param[in]	width	-	���εĿ��
 * @param[in]	height	-	���εĸ߶�
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Clears rectangular areas on the user-created canvas
 * @param[in]	x		-	The x-coordinate of our starting position
 * @param[in]	y		-	The y-coordinate of our starting position
 * @param[in]	width	-	Width of rectangle
 * @param[in]	height	-	Height of rectangle
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail��Returns the corresponding return value
@endif 
 */
int paint_clean_rect_user(int x, int y, uint32_t width, uint32_t height, const Paint_t paint);

/**
 @if Chinese
	 * @brief  ���û������Ļ����ϻ�ͼƬ
	 * @param[in]	x		-	��ʼλ�õ�x����
	 * @param[in]	y		-	��ʼλ�õ�y����
	 * @param[in]	m_pic	-	BMPͼƬ�������������ݣ�����ͷ����Ϣ
	 * @param[in]	paint	-	paint create user���ص�paint
	 * @return int
	 *          - =0  �ɹ�
	 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
	 * @note
	 *          - �˽ӿ���ʱ��֧��BMPͼƬ��m_pic���ݰ���BMPͼƬ��ͷ����Ϣ
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
 * @brief  �����û��㴴���Ļ���paint�Ļ���ģʽ
 * @param[in]	mode	-	���е�ģʽ��@ref paint_newline_mode
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
 @else 
 * @brief  Sets the newline mode for the paint created by the user layer
 * @param[in]	mode	-	Newline mode��@ref paint_newline_mode
 * @param[in]	paint	-	paint create user return paint value
 * @return int
 *          - =0  Success
 *          - <0  Fail
  @endif
 */
int paint_set_auto_newline_user(int mode, Paint_t paint);

/**
 @if Chinese
	 * @brief  ��ȡ�û��㴴���Ļ���paint�Ļ���ģʽ
	 * @param[in]	paint	-	paint create user���ص�paint
	 * @return int
	 *          - >=0  �ɹ������ص�ǰ�Ļ���ģʽ
	 *          - <0   ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ���û������Ļ����ϻ��ַ���
 * @param[in]	pfont	-	���ֿ�ȡ�ĵ���Ч�ֿ�������
 * @param[in]	x		-	��ʼλ�õ�x���꣬�ɴ���ֵ
 * @param[in]	y		-	��ʼλ�õ�y����
 * @param[in]	lpText	-	�ַ�������
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
 * @note
 *          - �������Ǹ�ֵʱ��������ʾ�൱�ڳ�����ʾ�����򣬲�����ʾ���ɴﵽֻ��ʾһ���ֵĲ���Ч����
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
	 * @brief  ���û������Ļ����ϻ����ص�
	 * @param[in]	x		-	�����x����
	 * @param[in]	y		-	�����y����
	 * @param[in]	paint	-	paint create user���ص�paint
	 * @return int
	 *          - =0  �ɹ�
	 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ��ȡ���û������Ļ����ϻ����ص����ɫֵ
 * @param[in]	x		-	�����x����
 * @param[in]	y		-	�����y����
 * @param[out]	color	-	�������ɫֵ������RGB888��24λɫ�ı�ʾ��ʽ
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ���û������Ļ����ϻ���
 * @param[in]	x1	-	������ʼ���x����
 * @param[in]	y1	-	������ʼ���y����
 * @param[in]	x2	-	�����յ��x����
 * @param[in]	y2	-	�����յ��y����
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  �����û��㴴���Ļ���paint���пհ�
 * @param[in]	line_space	-	�пհ�
 * @param[in]	paint		-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  �����û��㴴���Ļ���paint�ĵ�ǰ��������
 * @param[in]	width	-	�����õĿ��ֵ
 * @param[in]	height	-	�����õĸ߶�ֵ
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - 0  �ɹ�
 *          - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ��ȡ�û��㴴���Ļ���paint�ĵ�ǰ��������
 * @param[out]	width	-	���ص�ǰ��������Ŀ��ֵ
 * @param[out]	height	-	���ص�ǰ��������ĸ߶�ֵ
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - 0  �ɹ�
 *          - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
 * @note
 *          - �ýӿڲ����ô�ӡͼƬ
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
 * @brief  �����û��㴴���Ļ���paint��ǰ��ɫ�ͱ���ɫ
 * @param[in]	back_color	-	�����õı�����ɫֵ������RGB888��24λɫ�ı�ʾ��ʽ
 * @param[in]	fore_color	-	�����õ�ǰ����ɫֵ������RGB888��24λɫ�ı�ʾ��ʽ
 * @param[in]	paint		-	paint create user���ص�paint
 * @return int
 *          - 0  �ɹ�
 *          - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ��ȡ�û��㴴���Ļ���paint��ǰ��ɫ�ͱ���ɫ
 * @param[out]	back_color	-	�洢��ǰpaint�ı�����ɫֵ������RGB888��24λɫ�ı�ʾ��ʽ
 * @param[out]	fore_color	-	�洢��ǰpaint��ǰ����ɫֵ������RGB888��24λɫ�ı�ʾ��ʽ
 * @param[in]	paint		-	paint create user���ص�paint
 * @return int
 *          - 0  �ɹ�
 *          - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
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
 * @brief  ��ȡ�û��㴴���Ļ���paint��buffer����
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - ��NULL  �ɹ������ص�ǰ��paint��buffer����
 *          - NULL    ʧ��
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
 * @brief  ���û������Ļ����ϻ��ַ������û��ַ�������������һ��������rectָ�����ο���
 * @param[in]	fd		-	���ֿ�ȡ�ĵ���Ч�ֿ�������
 * @param[in]	nX		-	��ʼλ�õ�x���꣬�ɴ���ֵ
 * @param[in]	nY		-	��ʼλ�õ�y���꣬�ɴ���ֵ
 * @param[in]	rect	-	���ο���� �ο�@link textRect textRect @endlink
 * @param[in]	lpText	-	�ַ�������
 * @param[in]	paint	-	paint create user���ص�paint
 * @return int
 *          - =0  �ɹ�
 *          - <0  ʧ�ܣ�������Ӧ�ķ���ֵ
 * @note
 *          - ע��ýӿ���������һ�����ο�����ʾ������Ծ��ο���������㣬���ο�����ֻ������Ļ���귶Χ�ڣ������괫Ϊ��0��x����
 *           ����nXΪ����ʱ��������ʾ������ߣ�y�������ơ�
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
 *			If the parameter nX is negative, it can be displayed on the far left, and the y coordinates are similar��
 @endif 
 */
int paint_draw_text_rect_user(void *fd, int nX, int nY, void *rect, const char *lpText, Paint_t paint);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PAINT_H__ */

/** @} */

