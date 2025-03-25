/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app mathutils模块</strong> 相关的接口
	 * @par 文件    mathutils.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | 创建文件
	 * 2022-05-05    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app mathutils </strong>  module
	 * @par file    mathutils.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | create file
	 * 2022-05-05    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup mathutils 工具类函数
 @else
	@defgroup mathutils mathutils
 @endif
 * @{
*/
#ifndef	_MATH_UTILS_H_
#define _MATH_UTILS_H_

#include <appdatatypedef.h>

#define INI_VECTORLo 0x00
#define INI_VECTORHi 0x00
#define POLYNOMIALHi 0x80
#define POLYNOMIALLo 0x05

#ifndef  MAX
#define MAX(a, b)       ( (a)>=(b) ? (a) : (b) )
#endif

#ifndef  MIN
#define MIN(a, b)       ( (a)<=(b) ? (a) : (b) )
#endif

#ifndef  ABS
#define  ABS(a)      ( (a)>=0 ? (a) : (-1)*(a) )
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)	(sizeof(x)/sizeof((x)[0]))
#endif



/**
 @if Chinese
	* @brief 数据串按位异常
	* @param[in]	psSource1	-	数据串1  
	* @param[in]  	psSource2	-	数据串2
	* @param[in]  	iLength		-	运算数据长度
	* @param[out]  	psSource1	-	运算结果保存在数据串1中
 @else
	* @brief data string bitwise exception
	* @param[in]	psSource1	-	data string 1  
	* @param[in]  	psSource2	-	data string 2
	* @param[in]  	iLength		-	data string length
	* @param[out]  	psSource1	-	operation result
 @endif
*/ 
extern void pub_xor(char *psSource1, char *psSource2, int iLength);

/**
 @if Chinese
	* @brief 数据串crc运算
	* @param[in]	psData		-	数据串
	* @param[in]  	ulLength	-	运算数据长度
	* @return		crc运算结果
 @else
	* @brief data string CRC operation
	* @param[in]	psData		-	data string 
	* @param[in]  	ulLength	-	data string length
	* @return		crc operation result
 @endif
*/ 
extern unsigned short pub_calc_crc(char *psData, unsigned long ulLength);

/**
 @if Chinese
	* @brief 数据串lrc运算 
	* @param[in]	psData		-	数据串
	* @param[in]  	ulLength	-	运算数据长度
	* @param[in]  	ChInit		-	初始向量
	* @return		lrc运算结果
 @else
	* @brief data string LRC operation
	* @param[in]	psData		-	data string 
	* @param[in]  	ulLength	-	data string length
	* @param[in]  	ChInit		-	initial vector
	* @return		lrc operation result
 @endif
*/  
extern char pub_calc_lrc(const char *psData, unsigned long ulLength, char ChInit);

/**
 @if Chinese
	* @brief 判断两个字符是否为中文字符
	* @param[in]	ch		-	字符1
	* @param[in]  	ch2		-	字符2
	* @return		app_true	-	中文字符
	* @return		app_false	-	非中文字符
 @else
	* @brief judge whether the two characters are Chinese characters
	* @param[in]	ch		-	character 1
	* @param[in]  	ch2		-	character 2
	* @return		app_true	-	chinese characters
	* @return		app_false	-	no Chinese characters
 @endif
*/   
extern appbool pub_isCnChar(unsigned char ch,unsigned char ch2);

/**
 @if Chinese
	* @brief 根据首字节获取UTF8字符长度
	* @param[in]	ch		-	字符1
	* @return		字符所占字节的长度
 @else
	* @brief get UTF8 char length
	* @param[in]	ch		-	character 1
	* @return		the lenght of utf8 char
 @endif
*/ 
extern int pub_utf8_len(unsigned char ch);


#endif
