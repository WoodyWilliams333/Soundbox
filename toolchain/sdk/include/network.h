/**
 @if Chinese
* @brief    此模块用于描述 <strong>网络通讯模块</strong> 相关的接口
* @author   Jezz
* @date     2018-11-01
* @version  V1.0
* @remarks Change History:
* 日期          | 版本          | 作者            | 描述
* ------------- | ------------- | --------------- | ----
* 2018/11/01    | 1.0.0         | Jezz            | 创建文件
* 2022/04/19    | 1.0.1         | Wenming         | 增加英文注释
 @else
* @brief    This module is used to describe <strong>Network</strong> interfaces module
* @author   Jezz
* @date     2018-11-01
* @version  V1.0
* @remarks Change History:
* Date          | Version       | Author          | Desc
* ------------- | ------------- | --------------- | ----
* 2018/11/01    | 1.0.0         | Jezz            | Create file
* 2022/04/19    | 1.0.1         | Wenming         | Add English description
 @endif
*/


/**
 @if Chinese
 * @defgroup network 网络通讯
 @else 
 * @defgroup network Network
@endif 
 * @{
*/


#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
	* @brief  本函数将一个32位数从主机字节顺序转换成网络字节顺序。
	* @param[in]	h	-	主机字节顺序表达的32位数
	* @return long int <br>
			- 一个网络字节顺序的值
@else
	* @brief  This function converts a 32 - digit number from host byte order to network byte order.。
	* @param[in]	h	-	The host byte order representation of 32 bits
	* @return long int <br>
			- A network byte order value
@endif
*/
unsigned long int htonl(unsigned long int h);

/**
@if Chinese
* @brief  本函数将一个32位数由网络字节顺序转换为主机字节顺序
* @param[in]	n	-	一个以网络字节顺序表达的32位数。
* @return long int <br>
		- 一个以主机字节顺序表达的数
@else
* @brief  This function converts a 32 - digit number from network byte order to host byte order
* @param[in]	n	-	A 32-bit number expressed in network byte order。
* @return long int <br>
		- A number expressed in host byte order
@endif
*/
unsigned long int ntohl(unsigned long int n);

/**
@if Chinese
* @brief  将一个16位数由网络字节顺序转换为主机字节顺序
* @param[in]	h	-	主机字节顺序表达的16位数
* @return short int <br>
		- 一个网络字节顺序的值
@else
* @brief  Converts a 16-bit number from network byte order to host byte order
* @param[in]	h	-	The 16-digit host byte order representation
* @return short int <br>
		- A network byte order value
@endif
*/
unsigned short int htons(unsigned short int h);

/**
@if Chinese
* @brief  将整型变量从主机字节顺序转变成网络字节顺序
* @param[in]	n	-	一个以网络字节顺序表达的16位数
* @return 
	- 一个以主机字节顺序表达的数
@else
* @brief  Converts integer variables from host byte order to network byte order
* @param[in]	n	-	A 16-digit number expressed in network byte order
* @return int 
	- A number expressed in host byte order
@endif
*/
unsigned short int ntohs(unsigned short int n);

/**
@if Chinese
* @brief  将一个点分十进制的IP转换成一个长整数型数（u_long类型）
* @param[in]	cp	-	字符串，一个点分十进制的IP地址
* @return 如果正确执行将返回一个无符号长整数型数。如果传入的字符串不是一个合法的IP地址，将返回INADDR_NONE
@else
* @brief  Convert a dotted decimal IP to a long integer (type u_long)
* @param[in]	cp	-	The value is an IP address in dotted decimal notation
* @return 
*	- Success -Unsigned long integer type
*	- Fail	-INADDR_NONE
@endif
*/
in_addr_t inet_addr(const char *cp);

/**
@if Chinese
* @brief  将一个32位网络字节序的二进制IP地址转换成相应的点分十进制的IP地址
* @param[in]	in	-	一个表示Internet主机地址的结构
* @return 若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL
@else
* @brief  Converts a 32-bit network byte order binary IP address to the corresponding dotted decimal IP address
* @param[in]	in	-	A structure that represents the address of an Internet host
* @return 
*	- Success -inet_ntoa()Returns a character pointer。
*	- Fail	-return NULL
@endif
*/
char *inet_ntoa(struct in_addr in);

/**
@if Chinese
* @brief  将“二进制整数” －> “点分十进制”
* @param[in]	af	-	地址簇
* @param[in]	src	-	源地址
* @param[out]	dst	-	转换后的数据
* @param[in]	cnt	-	参数dst的大小
* @return 
	- 1	-成功
	- -1	-失败
@else
* @brief  Will "binary integer" - >"Dotted decimal notation"
* @param[in]	af	-	Address cluster
* @param[in]	src	-	Source address
* @param[out]	dst	-	Converted data
* @param[in]	cnt	-	The size of the DST parameter
* @return 	
	- 1	-Success
	- -1	-Fail
@endif
*/
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);

/**
@if Chinese
* @brief  将“点分十进制” －> “二进制整数”
* @param[in]	af	-	地址簇
* @param[in]	src	-	源地址
* @param[out]	dst	-	转换后的数据
* @return 如果函数出错将返回一个负值，并将errno设置为EAFNOSUPPORT，如果参数af指定的地址族和src格式不对，函数将返回0。
@else
* @brief  Put "dotted decimal" - >"Binary integer"
* @param[in]    af	-	Address cluster
* @param[in]    src -	Source address
* @param[out]   dst -	Converted data
* @return If the function fails, it returns a negative value and sets errno to EAFNOSUPPORT. If the af parameter specifies the wrong address family and SRC format, the function returns 0.
@endif
*/
int inet_pton(int af, const char *src, void *dst);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__NETWORK_H__

/** @} */

