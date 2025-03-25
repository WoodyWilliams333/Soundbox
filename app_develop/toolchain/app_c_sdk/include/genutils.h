/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app genutils模块</strong> 相关的接口
	 * @par 文件    genutils.h
	 * @author		yangjing
	 * @date        2020-04-14
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-14    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-27    | 1.0.1        | wenming       | 增加英文注释 
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
	@defgroup genutils 转换函数
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
	* @brief 	asc压缩bcd
	* @param[in]	psIAsc		-	asc码数据
	* @param[in]	iAscLen		-	asc长度
	* @param[out]	psOBcd		-	压缩后bcd，压缩后长度是asc的一半
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
	* @brief 	bcd转asc
	* @param[in]	psIHex		-	bcd数组
	* @param[in]	iHexLen		-	bcd长度
	* @param[out]	psOAsc		-	转化后asc，长度是bcd长度的两倍
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
	* @brief 	bcd转asc，结尾加结束符'\x00'
	* @param[in]	psIHex		-	bcd数组
	* @param[in]	iHexLen		-	bcd长度
	* @param[out]	pszOAsc		-	转化后asc，长度是bcd长度的两倍+1
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
	* @brief 	long转bcd数组, 十进制，例如1000 转成 4位长度 {0x10, 0x00}
	* @param[in]	ulSource	-	long数据
	* @param[in]	iBcdLen		-	转化后bcd数据长度
	* @param[out]	psOBcd		-	转化后bcd数组
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
 * @brief	字符串转大写
 * @param[in]	pszString	-	待转换字符串
 * @param[out]	pszString	-	转化后保存字符串
@else 
 * @brief	String conversion to uppercase
 * @param[in]	pszString	-	string to be converted
 * @param[out]	pszString	-	converted String
@endif 
 */
extern void pub_strupper(char *pszString);

/**
 @if Chinese
 * @brief	bcd数组转long，十进制，例如{0x10, 0x00}转成1000 
 * @param[in]	psBcd	-	待转化bcd数组
 * @param[in]	iBcdLen	-	bcd数组长度
 * @param[out]	pulOut	-	转化后long保存地址
 * @return	pulOut	-	转化后结果
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
 * @brief	bcd数据(金额)相加
 * @param[in]	augend	-	数组1
 * @param[in]	addend	-	数组2
 * @param[in]	len		-	数组长度
 * @param[out]	augend	-	相加后保存到数组1
 * @return	0	-	不需要进位
 * @return	1	-	需要进位
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
 * @brief	bcd数据(金额)相减
 * @param[in]	augend	-	数组1
 * @param[in]	subend	-	数组2
 * @param[in]	len		-	数组长度
 * @param[out]	des		-	相减结果保存数组
 * @return	0	-	不需要借位
 * @return	1	-	需要借位
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
 * @brief	bcd转long，十六进制，如0x1000转化后为{0x10, 0x00}
 * @param[in]	psHex	-	待转化bcd数组
 * @param[in]	iHexLen	-	bcd数组长度
 * @param[out]	pulOut	-	转化后long保存地址
 * @return	pulOut	-	转化后结果
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
 * @brief	asc转long，十进制，如“1000”转后为1000
 * @param[in]	psString	-	asc字符串，最长15
 * @param[in]	iStrLen		-	asc长度，保留，不起作用
 * @param[out]	pulOut		-	转化后long保存地址
 * @return	pulOut	-	转化后结果
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
 * @brief	整型数转换成高位在前的字符串表示(按照网络字节格式存放)
 * @param[in]	ulSource	-	待转化int数据
 * @param[in]	iAsclen		-	asc码长度
 * @param[out]	psOAsc		-	转化后字符串
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
 * @brief	高位在前的字符串表示转换为整型数
 * @param[in]	psString	-	待转化asc数据
 * @param[in]	iStrLen		-	asc长度
 * @param[out]	pulOut		-	转化后long保存地址
 * @return	pulOut	-	转化后结果
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
 * @brief	short类型转化为2字节数组
 * @param[in]	shortvar	-	short型数据
 * @param[out]	buf			-	字节数组
@else  
 * @brief	Short is converted to a 2-byte array
 * @param[in]	shortvar	-	Short data type
 * @param[out]	buf			-	Array of Byte
@endif  
 */
extern void pub_short2byte(uint8_t *buf, uint16_t shortvar);

/**
@if Chinese
 * @brief	2字节数组转化为short类型
 * @param[in]	buf	-	字节数组
 * @return	short	-	转化结果
@else   
 * @brief	The 2-byte array is converted to short
 * @param[in]	buf	-	Byte array
 * @return	short	-	Conversion results
@endif 
 */
extern uint16_t pub_byte2short(uint8_t *buf);

/**
@if Chinese
 * @brief	字符串头部填充字符
 * @param[in]	pszString	-	待填充数据
 * @param[in]	iTargetLen	-	填充后数据大小
 * @param[in]	ChAddChar	-	填充字符
 * @param[out]	pszString	-	填充后保存地址
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
 * @brief	将以分为单位的asc串转为以元为单位的asc串表示金额，asc串以'\0'结束
 * @param[in]	szAmount	-	原金额字符串
 * @param[out]	szAmount	-	转化后金额字符串
 * @return	转化后字符长度
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
 * @brief	整型转化为金额数组
 * @param[in]	lAmount		-	整型金额数据
 * @param[out]	szAmount	-	金额数组
 * @return	转化后字符长度
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
 * @brief	中文智能截断函数, 解决一行中文显示半个汉字的问题
 * @param[in]	src	-	源数据串
 * @param[in]	len	-	源数据长度
 * @param[out]	dst	-	目标数据串
 * @return	已拷贝的字符串长度
 * @note	针对的GB2313编码规则的汉字字符串.
 *	名称     |第一字节              |第二字节
 *---------- | -------------------- | ----------------
 *	GB2312   |0xB0-0xF7(176-247)    |0xA0-0xFE(160-254)
 *	GBK  	 |0x81-0xFE(129-254)    |0x40-0xFE(64-254)
 *	Big5     |0x81-0xFE(129-255)    |0x40-0x7E(64-126) 或者 0xA1－0xFE(161-254) 
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
 *	Big5     |0x81-0xFE(129-255)    |0x40-0x7E(64-126) or 0xA1－0xFE(161-254) 
@endif 
 */
extern int pub_strcopy(char *dst, const char *src, int len); 

/**
@if Chinese
 * @brief	删除字符串两端的空格、换行符
 * @param[in]	pszString	-	原字符串
 * @param[out]	pszString	-	目标字符串
@else 
 * @brief	delete spaces and line breaks at both ends of the string
 * @param[in]	pszString	-	original string
 * @param[out]	pszString	-	target string
@endif 
 */
extern void pub_trimstr(char *pszString);

/**
@if Chinese
 * @brief	删除字符串两端的特定字符
 * @param[in]	pszString	-	原字符串
 * @param[in]	ChSpcChar	-	需要删除的特定字符
 * @param[out]	pszString	-	目标字符串
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
 * @brief	字符串形式的版本号比较，即版本格式为“xx.xx.xx”
 * @param[in]	version1	-	比较版本1
 * @param[in]	version2	-	比较版本2
 * @param[in]	count		-	比较段数，不超过5
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
