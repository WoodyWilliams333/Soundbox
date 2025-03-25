/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app genutilsģ��</strong> ��صĽӿ�
	 * @par �ļ�    genutils.h
	 * @author		yangjing
	 * @date        2020-04-14
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-14    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-27    | 1.0.1        | wenming       | ����Ӣ��ע�� 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app genutils </strong>  module
	 * @par file    genutils.h
	 * @author		yangjing
	 * @date        2020-04-14
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-14    | 1.0.0        | yanjing       | create file
	 * 2022-04-27    | 1.0.1        | wenming       | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup genutils ת������
 @else
	@defgroup genutils genutils
 @endif
 * @{
*/
#ifndef _GEN_UTILS_H_
#define _GEN_UTILS_H_

#define STR_SIZE_BYTES_LEN		4
#define STRUC_MEMBER_OFFSET(TYPE, MEMBER) ((unsigned long)(&(((TYPE *)0)->MEMBER)))

#define ForceIntegerData(var, value, saveflg)	\
			do {\
				if (value != var) { \
					var = value;\
					saveflg = app_true; \
				} \
			} while (0)

/**
 @if Chinese
	* @brief 	ascѹ��bcd
	* @param[in]	psIAsc		-	asc������
	* @param[in]	iAscLen		-	asc����
	* @param[out]	psOBcd		-	ѹ����bcd��ѹ���󳤶���asc��һ��
 @else
	* @brief 	asc compressed bcd
	* @param[in]	psIAsc		-	asc code data
	* @param[in]	iAscLen		-	asc length
	* @param[out]	psOBcd		-	after compression, bcd is half as long as asc
 @endif
*/  
extern void pub_asc2bcd(const char *psIAsc, int iAscLen, unsigned char *psOBcd);

/**
 @if Chinese
	* @brief 	bcdתasc
	* @param[in]	psIHex		-	bcd����
	* @param[in]	iHexLen		-	bcd����
	* @param[out]	psOAsc		-	ת����asc��������bcd���ȵ�����
 @else
	* @brief 	bcd to asc
	* @param[in]	psIHex		-	bcd code data
	* @param[in]	iHexLen		-	bcd length
	* @param[out]	psOAsc		-	after transformation, the length of asc is twice that of bcd
 @endif
*/   
extern void pub_bcd2asc(unsigned char *psIHex, int iHexLen, char *psOAsc);

/**
 @if Chinese
	* @brief 	bcdתasc����β�ӽ�����'\x00'
	* @param[in]	psIHex		-	bcd����
	* @param[in]	iHexLen		-	bcd����
	* @param[out]	pszOAsc		-	ת����asc��������bcd���ȵ�����+1
 @else
	* @brief 	bcd to asc,end with '\x00'
	* @param[in]	psIHex		-	bcd code data
	* @param[in]	iHexLen		-	bcd length
	* @param[out]	pszOAsc		-	after transformation, length is twice the length of bcd + 1
 @endif
*/    
extern void pub_bcd2asc0(unsigned char *psIHex, int iHexLen, char *pszOAsc);

/**
 @if Chinese
	* @brief 	longתbcd����, ʮ���ƣ�����1000 ת�� 4λ���� {0x10, 0x00}
	* @param[in]	ulSource	-	long����
	* @param[in]	iBcdLen		-	ת����bcd���ݳ���
	* @param[out]	psOBcd		-	ת����bcd����
 @else
	* @brief 	long to bcd,decimal,for example, 1000 is converted to 4-bit length {0x10, 0x00}
	* @param[in]	ulSource	-	long code data
	* @param[in]	iBcdLen		-	bcd length
	* @param[out]	psOBcd		-	bcd array
 @endif
*/     
extern void pub_long2bcd(unsigned long ulSource, int iBcdLen, unsigned char *psOBcd);


/**
 @if Chinese
 * @brief	�ַ���ת��д
 * @param[in]	pszString	-	��ת���ַ���
 * @param[out]	pszString	-	ת���󱣴��ַ���
@else 
 * @brief	String conversion to uppercase
 * @param[in]	pszString	-	string to be converted
 * @param[out]	pszString	-	converted String
@endif 
 */
extern void pub_strupper(char *pszString);

/**
 @if Chinese
 * @brief	bcd����תlong��ʮ���ƣ�����{0x10, 0x00}ת��1000 
 * @param[in]	psBcd	-	��ת��bcd����
 * @param[in]	iBcdLen	-	bcd���鳤��
 * @param[out]	pulOut	-	ת����long�����ַ
 * @return	pulOut	-	ת������
@else 
 * @brief	bcd array to long, decimal, for example {0x10, 0x00} to 1000
 * @param[in]	psBcd	-	BCD array to be converted
 * @param[in]	iBcdLen	-	BCD Array length
 * @param[out]	pulOut	-	after converting, Long saves the address
 * @return	pulOut	-	results after conversion
@endif 
 */
extern uint32_t pub_bcd2long(uint8_t *psBcd, int iBcdLen, uint32_t *pulOut);

/**
 @if Chinese
 * @brief	bcd����(���)���
 * @param[in]	augend	-	����1
 * @param[in]	addend	-	����2
 * @param[in]	len		-	���鳤��
 * @param[out]	augend	-	��Ӻ󱣴浽����1
 * @return	0	-	����Ҫ��λ
 * @return	1	-	��Ҫ��λ
@else 
 * @brief	Add BCD data (amount)
 * @param[in]	augend	-	An array of 1
 * @param[in]	addend	-	An array of 2
 * @param[in]	len		-	The length of array
 * @param[out]	augend	-	Add them and save them in array 1
 * @return	0	-	no need to carry
 * @return	1	-	need to carry
@endif 
 */
extern uint8_t pub_bcdadd(uint8_t * augend, uint8_t * addend, uint16_t len);

/**
@if Chinese
 * @brief	bcd����(���)���
 * @param[in]	augend	-	����1
 * @param[in]	subend	-	����2
 * @param[in]	len		-	���鳤��
 * @param[out]	des		-	��������������
 * @return	0	-	����Ҫ��λ
 * @return	1	-	��Ҫ��λ
@else  
 * @brief	minus BCD data (amount)
 * @param[in]	augend	-	An array of 1
 * @param[in]	subend	-	An array of 2
 * @param[in]	len		-	The length of array
 * @param[out]	des		-	The subtraction results are stored in arrays
 * @return	0	-	no need to borrow
 * @return	1	-	need to borrow
@endif 
 */
extern uint8_t pub_bcdsub(uint8_t *des, uint8_t *augend, uint8_t *subend, uint16_t len);

/**
 @if Chinese
 * @brief	bcdתlong��ʮ�����ƣ���0x1000ת����Ϊ{0x10, 0x00}
 * @param[in]	psHex	-	��ת��bcd����
 * @param[in]	iHexLen	-	bcd���鳤��
 * @param[out]	pulOut	-	ת����long�����ַ
 * @return	pulOut	-	ת������
 @else 
 * @brief	BCD to long, hexadecimal, such as 0x1000 to {0x10, 0x00}
 * @param[in]	psHex	-	BCD array to be converted
 * @param[in]	iHexLen	-	BCD Array length
 * @param[out]	pulOut	-	After converting, Long saves the address
 * @return	pulOut	-	results after conversion
 @endif	 
 */
extern uint32_t pub_hex2long(uint8_t *psHex, int iHexLen, uint32_t *pulOut);

/**
@if Chinese
 * @brief	ascתlong��ʮ���ƣ��硰1000��ת��Ϊ1000
 * @param[in]	psString	-	asc�ַ������15
 * @param[in]	iStrLen		-	asc���ȣ���������������
 * @param[out]	pulOut		-	ת����long�����ַ
 * @return	pulOut	-	ת������
@else	 
 * @brief	Asc is converted to long, for example, "1000" is converted to 1000
 * @param[in]	psString	-	asc string, up to 15
 * @param[in]	iStrLen		-	asc length, no used
 * @param[out]	pulOut		-	after converting, long saves the address
 * @return	pulOut	-	results after conversion
@endif	 
 */
extern unsigned long pub_asc2long(char *psString, int iStrLen, unsigned long *pulOut);

/**
@if Chinese
 * @brief	������ת���ɸ�λ��ǰ���ַ�����ʾ(���������ֽڸ�ʽ���)
 * @param[in]	ulSource	-	��ת��int����
 * @param[in]	iAsclen		-	asc�볤��
 * @param[out]	psOAsc		-	ת�����ַ���
@else	 
 * @brief	Conversion of integer numbers to uppermost string representation (stored in network byte format)
 * @param[in]	ulSource	-	Int data to be converted
 * @param[in]	iAsclen		-	The length of asc
 * @param[out]	psOAsc		-	Converted string
@endif 
 */
extern void pub_long2char(unsigned int ulSource, int iAsclen, char *psOAsc);

/**
@if Chinese
 * @brief	��λ��ǰ���ַ�����ʾת��Ϊ������
 * @param[in]	psString	-	��ת��asc����
 * @param[in]	iStrLen		-	asc����
 * @param[out]	pulOut		-	ת����long�����ַ
 * @return	pulOut	-	ת������
@else 
 * @brief	A string with the highest value is converted to an integer
 * @param[in]	psString	-	Asc data to be converted
 * @param[in]	iStrLen		-	The length of asc
 * @param[out]	pulOut		-	After converting, Long saves the address
 * @return	pulOut	-	results after conversion
@endif 
 */
extern unsigned int pub_char2long(uint8_t *psString, int iStrLen, unsigned int *pulOut);

/**
@if Chinese
 * @brief	short����ת��Ϊ2�ֽ�����
 * @param[in]	shortvar	-	short������
 * @param[out]	buf			-	�ֽ�����
@else  
 * @brief	Short is converted to a 2-byte array
 * @param[in]	shortvar	-	Short data type
 * @param[out]	buf			-	Array of Byte
@endif  
 */
extern void pub_short2byte(uint8_t *buf, uint16_t shortvar);

/**
@if Chinese
 * @brief	2�ֽ�����ת��Ϊshort����
 * @param[in]	buf	-	�ֽ�����
 * @return	short	-	ת�����
@else   
 * @brief	The 2-byte array is converted to short
 * @param[in]	buf	-	Byte array
 * @return	short	-	Conversion results
@endif 
 */
extern uint16_t pub_byte2short(uint8_t *buf);

/**
@if Chinese
 * @brief	�ַ���ͷ������ַ�
 * @param[in]	pszString	-	���������
 * @param[in]	iTargetLen	-	�������ݴ�С
 * @param[in]	ChAddChar	-	����ַ�
 * @param[out]	pszString	-	���󱣴��ַ
@else 
 * @brief	String header padding characters
 * @param[in]	pszString	-	Data to be filled
 * @param[in]	iTargetLen	-	Data size after padding
 * @param[in]	ChAddChar	-	Padding character
 * @param[out]	pszString	-	Save the address after filling
@endif 
 */
extern void pub_add_headchars( char *pszString, int iTargetLen, char ChAddChar );

/**
@if Chinese
 * @brief	���Է�Ϊ��λ��asc��תΪ��ԪΪ��λ��asc����ʾ��asc����'\0'����
 * @param[in]	szAmount	-	ԭ����ַ���
 * @param[out]	szAmount	-	ת�������ַ���
 * @return	ת�����ַ�����
@else 
 * @brief	Convert the asc string in units into the asc string in units to represent the amount, ending with '\0'
 * @param[in]	szAmount	-	original amount string
 * @param[out]	szAmount	-	converted amount string
 * @return	Length of converted characters
@enidf 
 */
extern int amt_long2dec(uint8_t * szAmount);

/**
@if Chinese
 * @brief	����ת��Ϊ�������
 * @param[in]	lAmount		-	���ͽ������
 * @param[out]	szAmount	-	�������
 * @return	ת�����ַ�����
@else 
 * @brief	The integer type is converted to an array of amounts
 * @param[in]	lAmount		-	Integer amount data
 * @param[out]	szAmount	-	The amount of the array
 * @return	Length of converted characters
@endif 
 */
extern int pub_long2amout(uint8_t *szAmount, int lAmount);

/**
@if Chinese
 * @brief	�������ܽضϺ���, ���һ��������ʾ������ֵ�����
 * @param[in]	src	-	Դ���ݴ�
 * @param[in]	len	-	Դ���ݳ���
 * @param[out]	dst	-	Ŀ�����ݴ�
 * @return	�ѿ������ַ�������
 * @note	��Ե�GB2313�������ĺ����ַ���.
 *	����     |��һ�ֽ�              |�ڶ��ֽ�
 *---------- | -------------------- | ----------------
 *	GB2312   |0xB0-0xF7(176-247)    |0xA0-0xFE(160-254)
 *	GBK  	 |0x81-0xFE(129-254)    |0x40-0xFE(64-254)
 *	Big5     |0x81-0xFE(129-255)    |0x40-0x7E(64-126) ���� 0xA1��0xFE(161-254) 
@else 
 * @brief	Chinese intelligent truncation function, to solve the problem of a line of Chinese display half a Chinese character
 * @param[in]	src	-	The source data string
 * @param[in]	len	-	Source data length
 * @param[out]	dst	-	Target data string
 * @return	the length of the copied string
 * @note	Character string for GB2313 encoding rules.
 *	name     |First Byte            |Second byte 
 *---------- | -------------------- | ----------------
 *	GB2312   |0xB0-0xF7(176-247)    |0xA0-0xFE(160-254)
 *	GBK  	 |0x81-0xFE(129-254)    |0x40-0xFE(64-254)
 *	Big5     |0x81-0xFE(129-255)    |0x40-0x7E(64-126) or 0xA1��0xFE(161-254) 
@endif 
 */
extern int pub_strcopy(char *dst, const char *src, int len); 

/**
@if Chinese
 * @brief	ɾ���ַ������˵Ŀո񡢻��з�
 * @param[in]	pszString	-	ԭ�ַ���
 * @param[out]	pszString	-	Ŀ���ַ���
@else 
 * @brief	delete spaces and line breaks at both ends of the string
 * @param[in]	pszString	-	original string
 * @param[out]	pszString	-	target string
@endif 
 */
extern void pub_trimstr(char *pszString);

/**
@if Chinese
 * @brief	ɾ���ַ������˵��ض��ַ�
 * @param[in]	pszString	-	ԭ�ַ���
 * @param[in]	ChSpcChar	-	��Ҫɾ�����ض��ַ�
 * @param[out]	pszString	-	Ŀ���ַ���
@else 
 * @brief	deletes specific characters at both ends of a string
 * @param[in]	pszString	-	original string
 * @param[in]	ChSpcChar	-	specific character to be deleted
 * @param[out]	pszString	-	target string
@endif 
 */
extern void pub_trimspcstr(char * pszString, char ChSpcChar);

/**
@if Chinese
 * @brief	�ַ�����ʽ�İ汾�űȽϣ����汾��ʽΪ��xx.xx.xx��
 * @param[in]	version1	-	�Ƚϰ汾1
 * @param[in]	version2	-	�Ƚϰ汾2
 * @param[in]	count		-	�Ƚ϶�����������5
 * @return	0	-	version1=version2
 * @return	1	-	version1>version2
 * @return	-1	-	version1<version2
@else  
 * @brief	Comparison of version numbers in a string format, that is, the version format is xx.xx.xx.
 * @param[in]	version1	-	Comparison Version 1
 * @param[in]	version2	-	Comparison Version 2
 * @param[in]	count		-	Number of comparison segments, not more than 5
 * @return	0	-	version1=version2
 * @return	1	-	version1>version2
 * @return	-1	-	version1<version2
@endif  
 */
extern int pub_compare_version(char *version1, char *version2, int count);

#endif /* APPUTILS_H_ */
