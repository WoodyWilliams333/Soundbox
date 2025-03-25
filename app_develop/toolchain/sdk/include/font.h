/**
@if Chinese
 * @brief    ��ģ���������� <strong>�ֿ�(Font)ģ��</strong> ��صĽӿ�
 * @author   liluchang
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * ����          | �汾          | ����            | ����
 * ------------- | ------------- | --------------- | ----
 * 2019/01/24    | 1.0.0         | liluchang       | �����ļ�
 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
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
 * @defgroup FONT �ֿ�
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

typedef uint16_t WCHAR_t;                                   /**<@if Chinese WCHAR_t���Ͷ���   @else	WCHAR_t type definition	@endif*/
typedef void *font_t;                                       /**<@if Chinese fontָ�����Ͷ���  @else	Font pointer type definition	@endif*/

/* Ӧ�����ݣ�Ӧ�ò㲻���ģ����ص�����SDK */
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
 * @name ���嶨��
@else 
 * @name The font definition
@endif 
 * @{
 */
#define FONT_COURIER_NEW                "CourierNew"        /**<@if Chinese	CourierNew ����    @else	CourierNew font	@endif*/
#define FONT_SONG                       "����"              /**<@if Chinese ����               @else	Song typeface	@endif*/
#define FONT_IMITATE_SONG               "����"              /**<@if Chinese ���� ����          @else	Imitation song dynasty style typeface fonts	@endif*/
#define FONT_SYSTEM                     "System"            /**<@if Chinese System ����        @else	System font	@endif*/
#define FONT_ARIAL                      "Arial"             /**<@if Chinese Arial ����         @else	Arial font	@endif*/
#define FONT_TAHOMA                     "Tahoma"            /**<@if Chinese Tahoma ����        @else	Tahoma font	@endif*/
#define FONT_VERDANA                    "Verdana"           /**<@if Chinese Verdana ����       @else	Verdana font @endif*/
#define FONT_DOTUM                      "Dotum"             /**<@if Chinese Dotum ����         @else	Dotum font	@endif*/
/** @} */

/**
@if Chinese
 * @name �ַ�������
@else 
 * @name Character set definition
@endif  
 * @{
 */
#define FONT_CHARSET_ASCII              "ASCII"             /**<@if Chinese ASCII �ַ���        @else	ASCII 	@endif*/
#define FONT_CHARSET_GB2312             "GB2312"            /**<@if Chinese GB2312 �ַ���       @else	GB2312	@endif*/
#define FONT_CHARSET_GB18030            "GB18030"           /**<@if Chinese GB18030 �ַ���      @else	GB18030	@endif*/
#define FONT_CHARSET_VIETNAM            "VIETNAM"           /**<@if Chinese VIETNAM �ַ���      @else	VIETNAM	@endif*/
#define FONT_CHARSET_ARABIC             "ARABIC"            /**<@if Chinese ARABIC �ַ���       @else	ARABIC	@endif*/
#define FONT_CHARSET_UNICODE            "UNICODE"           /**<@if Chinese UNICODE �ַ���      @else	UNICODE	@endif*/
#define FONT_CHARSET_CP437              "CP437"             /**<@if Chinese CP437 �ַ���        @else	CP437	@endif*/
#define FONT_CHARSET_CP737              "CP737"             /**<@if Chinese CP737 �ַ���        @else	CP737	@endif*/
#define FONT_CHARSET_CP775              "CP775"             /**<@if Chinese CP775 �ַ���        @else	CP775	@endif*/
#define FONT_CHARSET_CP850              "CP850"             /**<@if Chinese CP850 �ַ���        @else	CP850 	@endif*/
#define FONT_CHARSET_CP852              "CP852"             /**<@if Chinese CP852 �ַ���        @else	CP852 	@endif*/
#define FONT_CHARSET_CP855              "CP855"             /**<@if Chinese CP855 �ַ���        @else	CP855 	@endif*/
#define FONT_CHARSET_CP857              "CP857"             /**<@if Chinese CP857 �ַ���        @else	CP857 	@endif*/
#define FONT_CHARSET_CP860              "CP860"             /**<@if Chinese CP860 �ַ���        @else	CP860 	@endif*/
#define FONT_CHARSET_CP861              "CP861"             /**<@if Chinese CP861 �ַ���        @else	CP861 	@endif*/
#define FONT_CHARSET_CP862              "CP862"             /**<@if Chinese CP862 �ַ���        @else	CP862 	@endif*/
#define FONT_CHARSET_CP863              "CP863"             /**<@if Chinese CP863 �ַ���        @else	CP863 	@endif*/
#define FONT_CHARSET_CP864              "CP864"             /**<@if Chinese CP864 �ַ���        @else	CP864 	@endif*/
#define FONT_CHARSET_CP865              "CP865"             /**<@if Chinese CP865 �ַ���        @else	CP865 	@endif*/
#define FONT_CHARSET_CP866              "CP866"             /**<@if Chinese CP866 �ַ���        @else	CP866 	@endif*/
#define FONT_CHARSET_CP869              "CP869"             /**<@if Chinese CP869 �ַ���        @else	CP869 	@endif*/
#define FONT_CHARSET_CP874              "CP874"             /**<@if Chinese CP874 �ַ���        @else	CP874 	@endif*/
#define FONT_CHARSET_CP932              "CP932"             /**<@if Chinese CP932 �ַ���        @else	CP932 	@endif*/
#define FONT_CHARSET_CP936              "CP936"             /**<@if Chinese CP936 �ַ���        @else	CP936 	@endif*/
#define FONT_CHARSET_CP949              "CP949"             /**<@if Chinese CP949 �ַ���        @else	CP949 	@endif*/
#define FONT_CHARSET_CP950              "CP950"             /**<@if Chinese CP950 �ַ���        @else	CP950 	@endif*/
#define FONT_CHARSET_CP1250             "CP1250"            /**<@if Chinese CP1250 �ַ���       @else	CP1250	@endif*/
#define FONT_CHARSET_CP1251             "CP1251"            /**<@if Chinese CP1251 �ַ���       @else	CP1251	@endif*/
#define FONT_CHARSET_CP1252             "CP1252"            /**<@if Chinese CP1252 �ַ���       @else	CP1252	@endif*/
#define FONT_CHARSET_CP1255             "CP1255"            /**<@if Chinese CP1255 �ַ���       @else	CP1255	@endif*/
#define FONT_CHARSET_ISO8859_1          "ISO8859-1"         /**<@if Chinese ISO8859-1 �ַ���    @else	ISO8859-1 	@endif*/
#define FONT_CHARSET_ISO8859_2          "ISO8859-2"         /**<@if Chinese ISO8859-2 �ַ���    @else	ISO8859-2 	@endif*/
#define FONT_CHARSET_ISO8859_3          "ISO8859-3"         /**<@if Chinese ISO8859-3 �ַ���    @else	ISO8859-3 	@endif*/
#define FONT_CHARSET_ISO8859_4          "ISO8859-4"         /**<@if Chinese ISO8859-4 �ַ���    @else	ISO8859-4 	@endif*/
#define FONT_CHARSET_ISO8859_5          "ISO8859-5"         /**<@if Chinese ISO8859-5 �ַ���    @else	ISO8859-5 	@endif*/
#define FONT_CHARSET_ISO8859_6          "ISO8859-6"         /**<@if Chinese ISO8859-6 �ַ���    @else	ISO8859-6 	@endif*/
#define FONT_CHARSET_ISO8859_7          "ISO8859-7"         /**<@if Chinese ISO8859-7 �ַ���    @else	ISO8859-7 	@endif*/
#define FONT_CHARSET_ISO8859_8          "ISO8859-8"         /**<@if Chinese ISO8859-8 �ַ���    @else	ISO8859-8 	@endif*/
#define FONT_CHARSET_ISO8859_9          "ISO8859-9"         /**<@if Chinese ISO8859-9 �ַ���    @else	ISO8859-9 	@endif*/
#define FONT_CHARSET_ISO8859_10         "ISO8859-10"        /**<@if Chinese ISO8859-10 �ַ���   @else	ISO8859-10	@endif*/
#define FONT_CHARSET_ISO8859_11         "ISO8859-11"        /**<@if Chinese ISO8859-11 �ַ���   @else	ISO8859-11	@endif*/
#define FONT_CHARSET_ISO8859_12         "ISO8859-12"        /**<@if Chinese ISO8859-12 �ַ���   @else	ISO8859-12	@endif*/
#define FONT_CHARSET_ISO8859_13         "ISO8859-13"        /**<@if Chinese ISO8859-13 �ַ���   @else	ISO8859-13	@endif*/
#define FONT_CHARSET_ISO8859_14         "ISO8859-14"        /**<@if Chinese ISO8859-14 �ַ���   @else	ISO8859-14	@endif*/
#define FONT_CHARSET_ISO8859_15         "ISO8859-15"        /**<@if Chinese ISO8859-15 �ַ���   @else	ISO8859-15	@endif*/
#define FONT_CHARSET_ISO8859_16         "ISO8859-16"        /**<@if Chinese ISO8859-16 �ַ���   @else	ISO8859-16	@endif*/
/** @} */

//////////////////////////////////////////////////////////////////////////

//���ͷ��ඨ��
#define SET_PRIMARY_FONT                0   /**<@if Chinese ������ѡ�ֿ� 				@else	Set the preferred font library	@endif*/
#define SET_SECONDARY_FONT              1   /**<@if Chinese ���ñ�ѡ�ֿ�(�����ѡ�ֿ�Ϊ���֣�ͨ�������ѡ�ֿ�ѡ��ascii���ֵ�����) @else	Set alternative font (select ASCII font from this alternative font if the preferred font is Chinese)	@endif*/

//Farsi����
#define TYPE_CONNECTOR                  0   /**<@if Chinese �߱�4������״̬�Ҵ��ҵ��� 	@else	Four font states from right to left	@endif*/
#define TYPE_NONCONNECTOR               1   /**<@if Chinese �߱�2�������Ҵ��ҵ��� 		@else	Have 2 font types from right to left	@endif*/
#define TYPE_RHYME                      2   /**<@if Chinese �߱���ǰһ���ַ���ϵ����� 	@else	Has the property of combining with the previous character	@endif*/
#define TYPE_INTERPUNCTION              3   /**<@if Chinese �����߷��ţ��������� 		@else	Punctuation marks, or symbols, stand on their own	@endif*/
#define TYPE_INTER_NUM                  4   /**<@if Chinese ��û������������ǰ��Ϊ�����������ֽ�� @else	If it does not appear consecutively and is preceded by digits, it is combined with digits	@endif*/
#define TYPE_CHAR                       5   /**<@if Chinese �ַ����ͣ���������� 		@else	Character type, overall from left to right	@endif*/
#define TYPE_NUMBERIC                   6   /**<@if Chinese �������ͣ���������� 		@else	Numeric type, whole from left to right	@endif*/
#define TYPE_EXP                        7   /**<@if Chinese ָ�� 						@else	index	@endif*/
#define TYPE_NONE                       8   /**<@if Chinese û������ 					@else	There is no type	@endif*/

//Vietnam����
#define TYPE_NORMOL                     10  /**<@if Chinese ��ͨ�ַ� 					@else	Normal character	@endif*/
#define TYPE_SUB                        11  /**<@if Chinese �¼ӷ� 						@else	To the operator	@endif*/
#define TYPE_SUPER                      12  /**<@if Chinese �ϼӷ� 						@else	Add operator	@endif*/

#define BigGlyphMetrics_size            8   /**<@if Chinese  BigGlyphMetrics size 		@else	BigGlyphMetrics size	@endif*/
#define SmallGlyphMetrics_size          5   /**<@if Chinese  SmallGlyphMetrics size 	@else	SmallGlyphMetrics size	@endif*/
#define BigGlyphMetrics                 1   /**<@if Chinese  BigGlyphMetrics 			@else	BigGlyphMetrics	@endif*/
#define SmallGlyphMetrics               0   /**<@if Chinese  SmallGlyphMetrics 			@else	SmallGlyphMetrics	@endif*/
#define CHR(ch1,ch2,ch3,ch4)            (((ch1)<<24)|((ch2)<<16)|((ch3)<<8)|(ch4)) /**<@if Chinese  ���ֱ���ϳ� @else	Chinese character encoding and synthesis	@endif*/

/**
@if Chinese
 * @brief  ���û�����ֿ�
 * @param[in]  fontname	-	�ֿ������ļ�ϵͳ�еľ���·��
 * @param[in]  charset	-	�ֿ�ʹ�õ��ַ��������ַ����ĺ궨��
 * @param[in]  style	-	�ֿ������
 * @param[in]  size	-	����Ĵ�С
 * @param[out] ppfont	-	fontָ���ָ�룬��������ֿ�򿪺�Ĳ���ָ����
 * @return	0	-	�ɹ�
 * @return	<0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Open the user layer font library
 * @param[in]  fontname	- The absolute path where the font is stored in the file system
 * @param[in]  charset	- The character set used by the character library, see the macro definition of the character set
 * @param[in]  style	- The type of the font
 * @param[in]  size	- Font size
 * @param[out] ppfont	- The pointer to the font pointer, used to output the operation pointer handle after the font library has been opened
 * @return	0	-	Success
 * @return	<0	-	Fail��Returns the corresponding return value
@endif 
 */
int font_open_user(const char *fontname, const char *charset, int style, int size, font_t *ppfont);

/**
@if Chinese
 * @brief  �ر��û�����ֿ�
 * @param[in]	pfont	-	���ֿ�Ĳ������
 * @return	0	-	�ɹ�
 * @return	<0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Close the user level font library
 * @param[in]	pfont	-	Opens the operation handle of the font library
 * @return	0	-	Success
 * @return	<0	-	Fail��Returns the corresponding return value
@endif 
 */
int font_close_user(const font_t pfont);

/**
@if Chinese
 * @brief  ��ȡ�ַ�(ASCII�ַ�����)��ָ���ֿ��µĿ�Ⱥ͸߶�
 * @param[in]	pfont	-	���ֿ�Ĳ������
 * @param[in]	lpText	-	������ַ�����ʼ��ַ�������ǵ���ASCII�ַ���һ������
 * @param[out]	width	-	�����ַ��Ŀ��ֵ
 * @param[out]	height	-	�����ַ��ĸ߶�ֵ
 * @return	0	-	�ɹ�
 * @return	<0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else 
 * @brief  Gets the width and height of a character (ASCII or chinese characters) in the specified font
 * @param[in]	pfont	-	Opens the operation handle of the font library
 * @param[in]	lpText	-	The starting address of the character passed in, either a single ASCII character or a Chinese character
 * @param[out]	width	-	Returns the width value of a character
 * @param[out]  height	-	Returns the height value of a character
 * @return	0	-	Success
 * @return	<0	-	Fail��Returns the corresponding return value
@endif 
 */
int font_get_word_info_user(const font_t pfont, const char *lpText, int *width, int *height);

/**
@if Chinese
 * @brief  ��ȡ�ַ�����ָ���ֿ��µĿ��
 * @param[in]	pfont	-	���ֿ�Ĳ������
 * @param[in]	lpText	-	������ַ���ָ��
 * @param[in]	len		-	�����ַ����ĳ���
 * @return	>=0	-	�ɹ������ض�Ӧ�Ŀ��ֵ
 * @return	<0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
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

