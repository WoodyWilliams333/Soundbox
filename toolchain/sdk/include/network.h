/**
 @if Chinese
* @brief    ��ģ���������� <strong>����ͨѶģ��</strong> ��صĽӿ�
* @author   Jezz
* @date     2018-11-01
* @version  V1.0
* @remarks Change History:
* ����          | �汾          | ����            | ����
* ------------- | ------------- | --------------- | ----
* 2018/11/01    | 1.0.0         | Jezz            | �����ļ�
* 2022/04/19    | 1.0.1         | Wenming         | ����Ӣ��ע��
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
 * @defgroup network ����ͨѶ
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
	* @brief  ��������һ��32λ���������ֽ�˳��ת���������ֽ�˳��
	* @param[in]	h	-	�����ֽ�˳�����32λ��
	* @return long int <br>
			- һ�������ֽ�˳���ֵ
@else
	* @brief  This function converts a 32 - digit number from host byte order to network byte order.��
	* @param[in]	h	-	The host byte order representation of 32 bits
	* @return long int <br>
			- A network byte order value
@endif
*/
unsigned long int htonl(unsigned long int h);

/**
@if Chinese
* @brief  ��������һ��32λ���������ֽ�˳��ת��Ϊ�����ֽ�˳��
* @param[in]	n	-	һ���������ֽ�˳�����32λ����
* @return long int <br>
		- һ���������ֽ�˳�������
@else
* @brief  This function converts a 32 - digit number from network byte order to host byte order
* @param[in]	n	-	A 32-bit number expressed in network byte order��
* @return long int <br>
		- A number expressed in host byte order
@endif
*/
unsigned long int ntohl(unsigned long int n);

/**
@if Chinese
* @brief  ��һ��16λ���������ֽ�˳��ת��Ϊ�����ֽ�˳��
* @param[in]	h	-	�����ֽ�˳�����16λ��
* @return short int <br>
		- һ�������ֽ�˳���ֵ
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
* @brief  �����ͱ����������ֽ�˳��ת��������ֽ�˳��
* @param[in]	n	-	һ���������ֽ�˳�����16λ��
* @return 
	- һ���������ֽ�˳�������
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
* @brief  ��һ�����ʮ���Ƶ�IPת����һ��������������u_long���ͣ�
* @param[in]	cp	-	�ַ�����һ�����ʮ���Ƶ�IP��ַ
* @return �����ȷִ�н�����һ���޷��ų��������������������ַ�������һ���Ϸ���IP��ַ��������INADDR_NONE
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
* @brief  ��һ��32λ�����ֽ���Ķ�����IP��ַת������Ӧ�ĵ��ʮ���Ƶ�IP��ַ
* @param[in]	in	-	һ����ʾInternet������ַ�Ľṹ
* @return ���޴�������inet_ntoa()����һ���ַ�ָ�롣����Ļ�������NULL
@else
* @brief  Converts a 32-bit network byte order binary IP address to the corresponding dotted decimal IP address
* @param[in]	in	-	A structure that represents the address of an Internet host
* @return 
*	- Success -inet_ntoa()Returns a character pointer��
*	- Fail	-return NULL
@endif
*/
char *inet_ntoa(struct in_addr in);

/**
@if Chinese
* @brief  ���������������� ��> �����ʮ���ơ�
* @param[in]	af	-	��ַ��
* @param[in]	src	-	Դ��ַ
* @param[out]	dst	-	ת���������
* @param[in]	cnt	-	����dst�Ĵ�С
* @return 
	- 1	-�ɹ�
	- -1	-ʧ��
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
* @brief  �������ʮ���ơ� ��> ��������������
* @param[in]	af	-	��ַ��
* @param[in]	src	-	Դ��ַ
* @param[out]	dst	-	ת���������
* @return ���������������һ����ֵ������errno����ΪEAFNOSUPPORT���������afָ���ĵ�ַ���src��ʽ���ԣ�����������0��
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

