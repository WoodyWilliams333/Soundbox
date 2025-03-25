/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app mathutilsģ��</strong> ��صĽӿ�
	 * @par �ļ�    mathutils.h
	 * @author		yangjing
	 * @date        2020-07-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-07-30    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-05-05    | 1.0.1        | lydia         | ����Ӣ��ע�� 
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
	@defgroup mathutils �����ຯ��
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
	* @brief ���ݴ���λ�쳣
	* @param[in]	psSource1	-	���ݴ�1  
	* @param[in]  	psSource2	-	���ݴ�2
	* @param[in]  	iLength		-	�������ݳ���
	* @param[out]  	psSource1	-	���������������ݴ�1��
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
	* @brief ���ݴ�crc����
	* @param[in]	psData		-	���ݴ�
	* @param[in]  	ulLength	-	�������ݳ���
	* @return		crc������
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
	* @brief ���ݴ�lrc���� 
	* @param[in]	psData		-	���ݴ�
	* @param[in]  	ulLength	-	�������ݳ���
	* @param[in]  	ChInit		-	��ʼ����
	* @return		lrc������
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
	* @brief �ж������ַ��Ƿ�Ϊ�����ַ�
	* @param[in]	ch		-	�ַ�1
	* @param[in]  	ch2		-	�ַ�2
	* @return		app_true	-	�����ַ�
	* @return		app_false	-	�������ַ�
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
	* @brief �������ֽڻ�ȡUTF8�ַ�����
	* @param[in]	ch		-	�ַ�1
	* @return		�ַ���ռ�ֽڵĳ���
 @else
	* @brief get UTF8 char length
	* @param[in]	ch		-	character 1
	* @return		the lenght of utf8 char
 @endif
*/ 
extern int pub_utf8_len(unsigned char ch);


#endif
