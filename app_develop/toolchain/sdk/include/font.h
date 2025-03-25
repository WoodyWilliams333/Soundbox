/**
@if Chinese
 * @brief    此模块用于描述 <strong>字库(Font)模块</strong> 相关的接口
 * @author   liluchang
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * 日期          | 版本          | 作者            | 描述
 * ------------- | ------------- | --------------- | ----
 * 2019/01/24    | 1.0.0         | liluchang       | 创建文件
 * 2022/04/20    | 1.0.1         | Wenming         | 增加英文注释
@else
 * @brief    This module is used to describe <strong>Font</strong> interfaces module
 * @author   liluchang
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/24    | 1.0.0         | liluchang       | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
@endif 
 */

/**
@if Chinese
 * @defgroup FONT 字库
@else
 * @defgroup FONT Font
@endif 
 * @{
 */


#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>
#include <string.h>
#include "stdlib.h"
//#include "common.h"
//#include "complier.h"
//#include "linuxlist.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef uint16_t WCHAR_t;                                   /**<@if Chinese WCHAR_t类型定义   @else	WCHAR_t type definition	@endif*/
typedef void *font_t;                                       /**<@if Chinese font指针类型定义  @else	Font pointer type definition	@endif*/

/* 应用内容，应用层不关心，不必导出到SDK */
#if 0
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)                   (sizeof(x) / sizeof((x)[0]))
#endif

#define FONT_LIB_FLAG                   ".FONT."
#define PIXTABLE_FLAG                   "FONT HEAD INFO"

#define FONT_MAX_SUPPORT                64
#define FONT_LIB_MAX_SUPPORT            128
#endif

/**
@if Chinese
 * @name 字体定义
@else 
 * @name The font definition
@endif 
 * @{
 */
#define FONT_COURIER_NEW                "CourierNew"        /**<@if Chinese	CourierNew 字体    @else	CourierNew font	@endif*/
#define FONT_SONG                       "宋体"              /**<@if Chinese 宋体               @else	Song typeface	@endif*/
#define FONT_IMITATE_SONG               "仿宋"              /**<@if Chinese 仿宋 字体          @else	Imitation song dynasty style typeface fonts	@endif*/
#define FONT_SYSTEM                     "System"            /**<@if Chinese System 字体        @else	System font	@endif*/
#define FONT_ARIAL                      "Arial"             /**<@if Chinese Arial 字体         @else	Arial font	@endif*/
#define FONT_TAHOMA                     "Tahoma"            /**<@if Chinese Tahoma 字体        @else	Tahoma font	@endif*/
#define FONT_VERDANA                    "Verdana"           /**<@if Chinese Verdana 字体       @else	Verdana font @endif*/
#define FONT_DOTUM                      "Dotum"             /**<@if Chinese Dotum 字体         @else	Dotum font	@endif*/
/** @} */

/**
@if Chinese
 * @name 字符集定义
@else 
 * @name Character set definition
@endif  
 * @{
 */
#define FONT_CHARSET_ASCII              "ASCII"             /**<@if Chinese ASCII 字符集        @else	ASCII 	@endif*/
#define FONT_CHARSET_GB2312             "GB2312"            /**<@if Chinese GB2312 字符集       @else	GB2312	@endif*/
#define FONT_CHARSET_GB18030            "GB18030"           /**<@if Chinese GB18030 字符集      @else	GB18030	@endif*/
#define FONT_CHARSET_VIETNAM            "VIETNAM"           /**<@if Chinese VIETNAM 字符集      @else	VIETNAM	@endif*/
#define FONT_CHARSET_ARABIC             "ARABIC"            /**<@if Chinese ARABIC 字符集       @else	ARABIC	@endif*/
#define FONT_CHARSET_UNICODE            "UNICODE"           /**<@if Chinese UNICODE 字符集      @else	UNICODE	@endif*/
#define FONT_CHARSET_CP437              "CP437"             /**<@if Chinese CP437 字符集        @else	CP437	@endif*/
#define FONT_CHARSET_CP737              "CP737"             /**<@if Chinese CP737 字符集        @else	CP737	@endif*/
#define FONT_CHARSET_CP775              "CP775"             /**<@if Chinese CP775 字符集        @else	CP775	@endif*/
#define FONT_CHARSET_CP850              "CP850"             /**<@if Chinese CP850 字符集        @else	CP850 	@endif*/
#define FONT_CHARSET_CP852              "CP852"             /**<@if Chinese CP852 字符集        @else	CP852 	@endif*/
#define FONT_CHARSET_CP855              "CP855"             /**<@if Chinese CP855 字符集        @else	CP855 	@endif*/
#define FONT_CHARSET_CP857              "CP857"             /**<@if Chinese CP857 字符集        @else	CP857 	@endif*/
#define FONT_CHARSET_CP860              "CP860"             /**<@if Chinese CP860 字符集        @else	CP860 	@endif*/
#define FONT_CHARSET_CP861              "CP861"             /**<@if Chinese CP861 字符集        @else	CP861 	@endif*/
#define FONT_CHARSET_CP862              "CP862"             /**<@if Chinese CP862 字符集        @else	CP862 	@endif*/
#define FONT_CHARSET_CP863              "CP863"             /**<@if Chinese CP863 字符集        @else	CP863 	@endif*/
#define FONT_CHARSET_CP864              "CP864"             /**<@if Chinese CP864 字符集        @else	CP864 	@endif*/
#define FONT_CHARSET_CP865              "CP865"             /**<@if Chinese CP865 字符集        @else	CP865 	@endif*/
#define FONT_CHARSET_CP866              "CP866"             /**<@if Chinese CP866 字符集        @else	CP866 	@endif*/
#define FONT_CHARSET_CP869              "CP869"             /**<@if Chinese CP869 字符集        @else	CP869 	@endif*/
#define FONT_CHARSET_CP874              "CP874"             /**<@if Chinese CP874 字符集        @else	CP874 	@endif*/
#define FONT_CHARSET_CP932              "CP932"             /**<@if Chinese CP932 字符集        @else	CP932 	@endif*/
#define FONT_CHARSET_CP936              "CP936"             /**<@if Chinese CP936 字符集        @else	CP936 	@endif*/
#define FONT_CHARSET_CP949              "CP949"             /**<@if Chinese CP949 字符集        @else	CP949 	@endif*/
#define FONT_CHARSET_CP950              "CP950"             /**<@if Chinese CP950 字符集        @else	CP950 	@endif*/
#define FONT_CHARSET_CP1250             "CP1250"            /**<@if Chinese CP1250 字符集       @else	CP1250	@endif*/
#define FONT_CHARSET_CP1251             "CP1251"            /**<@if Chinese CP1251 字符集       @else	CP1251	@endif*/
#define FONT_CHARSET_CP1252             "CP1252"            /**<@if Chinese CP1252 字符集       @else	CP1252	@endif*/
#define FONT_CHARSET_CP1255             "CP1255"            /**<@if Chinese CP1255 字符集       @else	CP1255	@endif*/
#define FONT_CHARSET_ISO8859_1          "ISO8859-1"         /**<@if Chinese ISO8859-1 字符集    @else	ISO8859-1 	@endif*/
#define FONT_CHARSET_ISO8859_2          "ISO8859-2"         /**<@if Chinese ISO8859-2 字符集    @else	ISO8859-2 	@endif*/
#define FONT_CHARSET_ISO8859_3          "ISO8859-3"         /**<@if Chinese ISO8859-3 字符集    @else	ISO8859-3 	@endif*/
#define FONT_CHARSET_ISO8859_4          "ISO8859-4"         /**<@if Chinese ISO8859-4 字符集    @else	ISO8859-4 	@endif*/
#define FONT_CHARSET_ISO8859_5          "ISO8859-5"         /**<@if Chinese ISO8859-5 字符集    @else	ISO8859-5 	@endif*/
#define FONT_CHARSET_ISO8859_6          "ISO8859-6"         /**<@if Chinese ISO8859-6 字符集    @else	ISO8859-6 	@endif*/
#define FONT_CHARSET_ISO8859_7          "ISO8859-7"         /**<@if Chinese ISO8859-7 字符集    @else	ISO8859-7 	@endif*/
#define FONT_CHARSET_ISO8859_8          "ISO8859-8"         /**<@if Chinese ISO8859-8 字符集    @else	ISO8859-8 	@endif*/
#define FONT_CHARSET_ISO8859_9          "ISO8859-9"         /**<@if Chinese ISO8859-9 字符集    @else	ISO8859-9 	@endif*/
#define FONT_CHARSET_ISO8859_10         "ISO8859-10"        /**<@if Chinese ISO8859-10 字符集   @else	ISO8859-10	@endif*/
#define FONT_CHARSET_ISO8859_11         "ISO8859-11"        /**<@if Chinese ISO8859-11 字符集   @else	ISO8859-11	@endif*/
#define FONT_CHARSET_ISO8859_12         "ISO8859-12"        /**<@if Chinese ISO8859-12 字符集   @else	ISO8859-12	@endif*/
#define FONT_CHARSET_ISO8859_13         "ISO8859-13"        /**<@if Chinese ISO8859-13 字符集   @else	ISO8859-13	@endif*/
#define FONT_CHARSET_ISO8859_14         "ISO8859-14"        /**<@if Chinese ISO8859-14 字符集   @else	ISO8859-14	@endif*/
#define FONT_CHARSET_ISO8859_15         "ISO8859-15"        /**<@if Chinese ISO8859-15 字符集   @else	ISO8859-15	@endif*/
#define FONT_CHARSET_ISO8859_16         "ISO8859-16"        /**<@if Chinese ISO8859-16 字符集   @else	ISO8859-16	@endif*/
/** @} */

//////////////////////////////////////////////////////////////////////////

//类型分类定义
#define SET_PRIMARY_FONT                0   /**<@if Chinese 设置首选字库 				@else	Set the preferred font library	@endif*/
#define SET_SECONDARY_FONT              1   /**<@if Chinese 设置备选字库(针对首选字库为汉字，通过这个备选字库选择ascii部分的字体) @else	Set alternative font (select ASCII font from this alternative font if the preferred font is Chinese)	@endif*/

//Farsi定义
#define TYPE_CONNECTOR                  0   /**<@if Chinese 具备4种字型状态且从右到左 	@else	Four font states from right to left	@endif*/
#define TYPE_NONCONNECTOR               1   /**<@if Chinese 具备2种字型且从右到左 		@else	Have 2 font types from right to left	@endif*/
#define TYPE_RHYME                      2   /**<@if Chinese 具备与前一个字符结合的特性 	@else	Has the property of combining with the previous character	@endif*/
#define TYPE_INTERPUNCTION              3   /**<@if Chinese 标点或者符号，独立成形 		@else	Punctuation marks, or symbols, stand on their own	@endif*/
#define TYPE_INTER_NUM                  4   /**<@if Chinese 若没有连续出现且前后为数字则与数字结合 @else	If it does not appear consecutively and is preceded by digits, it is combined with digits	@endif*/
#define TYPE_CHAR                       5   /**<@if Chinese 字符类型，整体从左到右 		@else	Character type, overall from left to right	@endif*/
#define TYPE_NUMBERIC                   6   /**<@if Chinese 数字类型，整体从左到右 		@else	Numeric type, whole from left to right	@endif*/
#define TYPE_EXP                        7   /**<@if Chinese 指数 						@else	index	@endif*/
#define TYPE_NONE                       8   /**<@if Chinese 没有类型 					@else	There is no type	@endif*/

//Vietnam定义
#define TYPE_NORMOL                     10  /**<@if Chinese 普通字符 					@else	Normal character	@endif*/
#define TYPE_SUB                        11  /**<@if Chinese 下加符 						@else	To the operator	@endif*/
#define TYPE_SUPER                      12  /**<@if Chinese 上加符 						@else	Add operator	@endif*/

#define BigGlyphMetrics_size            8   /**<@if Chinese  BigGlyphMetrics size 		@else	BigGlyphMetrics size	@endif*/
#define SmallGlyphMetrics_size          5   /**<@if Chinese  SmallGlyphMetrics size 	@else	SmallGlyphMetrics size	@endif*/
#define BigGlyphMetrics                 1   /**<@if Chinese  BigGlyphMetrics 			@else	BigGlyphMetrics	@endif*/
#define SmallGlyphMetrics               0   /**<@if Chinese  SmallGlyphMetrics 			@else	SmallGlyphMetrics	@endif*/
#define CHR(ch1,ch2,ch3,ch4)            (((ch1)<<24)|((ch2)<<16)|((ch3)<<8)|(ch4)) /**<@if Chinese  汉字编码合成 @else	Chinese character encoding and synthesis	@endif*/

/**
@if Chinese
 * @brief  打开用户层的字库
 * @param[in]  fontname	-	字库存放在文件系统中的绝对路径
 * @param[in]  charset	-	字库使用的字符集，见字符集的宏定义
 * @param[in]  style	-	字库的类型
 * @param[in]  size	-	字体的大小
 * @param[out] ppfont	-	font指针的指针，用于输出字库打开后的操作指针句柄
 * @return	0	-	成功
 * @return	<0	-	失败，返回相应的返回值
@else 
 * @brief  Open the user layer font library
 * @param[in]  fontname	- The absolute path where the font is stored in the file system
 * @param[in]  charset	- The character set used by the character library, see the macro definition of the character set
 * @param[in]  style	- The type of the font
 * @param[in]  size	- Font size
 * @param[out] ppfont	- The pointer to the font pointer, used to output the operation pointer handle after the font library has been opened
 * @return	0	-	Success
 * @return	<0	-	Fail，Returns the corresponding return value
@endif 
 */
int font_open_user(const char *fontname, const char *charset, int style, int size, font_t *ppfont);

/**
@if Chinese
 * @brief  关闭用户层的字库
 * @param[in]	pfont	-	打开字库的操作句柄
 * @return	0	-	成功
 * @return	<0	-	失败，返回相应的返回值
@else 
 * @brief  Close the user level font library
 * @param[in]	pfont	-	Opens the operation handle of the font library
 * @return	0	-	Success
 * @return	<0	-	Fail，Returns the corresponding return value
@endif 
 */
int font_close_user(const font_t pfont);

/**
@if Chinese
 * @brief  获取字符(ASCII字符或汉字)在指定字库下的宽度和高度
 * @param[in]	pfont	-	打开字库的操作句柄
 * @param[in]	lpText	-	传入的字符的起始地址，可以是单个ASCII字符或一个汉字
 * @param[out]	width	-	返回字符的宽度值
 * @param[out]	height	-	返回字符的高度值
 * @return	0	-	成功
 * @return	<0	-	失败，返回相应的返回值
@else 
 * @brief  Gets the width and height of a character (ASCII or chinese characters) in the specified font
 * @param[in]	pfont	-	Opens the operation handle of the font library
 * @param[in]	lpText	-	The starting address of the character passed in, either a single ASCII character or a Chinese character
 * @param[out]	width	-	Returns the width value of a character
 * @param[out]  height	-	Returns the height value of a character
 * @return	0	-	Success
 * @return	<0	-	Fail，Returns the corresponding return value
@endif 
 */
int font_get_word_info_user(const font_t pfont, const char *lpText, int *width, int *height);

/**
@if Chinese
 * @brief  获取字符串在指定字库下的宽度
 * @param[in]	pfont	-	打开字库的操作句柄
 * @param[in]	lpText	-	传入的字符串指针
 * @param[in]	len		-	传入字符串的长度
 * @return	>=0	-	成功，返回对应的宽度值
 * @return	<0	-	失败，返回相应的返回值
@else 
 * @brief  Gets the width of the string in the specified font
 * @param[in]	pfont	-	Opens the operation handle of the font library
 * @param[in]	lpText	-	Pointer to the string passed in
 * @param[in]	len		-	The length of the string passed in
 * @return	>=0	-	Success, returns the corresponding width value
 * @return	< 0	-	Fail, return the corresponding return value
@endif 
 */
int font_get_width_user(const font_t pfont, const char *lpText, int len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FONT_H__ */

/** @} */

