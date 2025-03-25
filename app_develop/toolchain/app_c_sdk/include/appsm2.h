/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app sm2ģ��</strong> ��صĽӿ�
	 * @par �ļ�    appsm2.h
	 * @author		lydia
	 * @date        2021-11-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2021-11-09    | 1.0.0        | lydia         | �����ļ�
	 * 2022-04-29    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app sm2</strong>  module
	 * @par file    appsm2.h
	 * @author		lydia
	 * @date        2021-11-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2021-11-09    | 1.0.0        | lydia         | create file
	 * 2022-04-29    | 1.0.1        | lydia         | Add English description
 @endif
*/

/*!
 @if Chinese
	* @addtogroup app_sm2 sm2�ӽ���
 @else 
	* @addtogroup app_sm2 ped_sm2
 @endif 
 * @{
*/

#ifndef _APPSM2_H_
#define _APPSM2_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef unsigned long long __u64;
typedef __u64             u_int64_t;
#define __be64            u_int64_t
#define __force

#define ___constant_swab64(x) ((__u64)(                                \
        (((__u64)(x) & (__u64)0x00000000000000ffULL) << 56) |        \
        (((__u64)(x) & (__u64)0x000000000000ff00ULL) << 40) |        \
        (((__u64)(x) & (__u64)0x0000000000ff0000ULL) << 24) |        \
        (((__u64)(x) & (__u64)0x00000000ff000000ULL) <<  8) |        \
        (((__u64)(x) & (__u64)0x000000ff00000000ULL) >>  8) |        \
        (((__u64)(x) & (__u64)0x0000ff0000000000ULL) >> 24) |        \
        (((__u64)(x) & (__u64)0x00ff000000000000ULL) >> 40) |        \
        (((__u64)(x) & (__u64)0xff00000000000000ULL) >> 56)))
    
#define cpu_to_be64(x) ((__force __be64)___constant_swab64((x)))
#define be64_to_cpu(x) ___constant_swab64((__force __u64)(__be64)(x))

/*!
 @if Chinese
 * @brief		��sm2��Կ��������
 * @param[in]   pubKey	-	��Կֵ(x����+y����������������)
 * @param[in]   DataIn	-	�����ܵ�����
 * @param[in]   InLen	-	���������ݳ���
 * @param[out]  DataOut	-	���ܺ������(C1C2C3,û�м�0x04)
 * @param[out]  OutLen	-	���ܺ�����ĳ���, ͨ��Ϊ96
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
	
 @else
 * @brief		encrypt data using sm2 public key 
 * @param[in]   pubKey	-	public key(x plus y, not including the length)
 * @param[in]   DataIn	-	data to be encrypted
 * @param[in]   InLen	-	length of DataIn
 * @param[out]  DataOut	-	ciphertext(C1C2C3,without adding 0x04)
 * @param[out]  OutLen	-	length of ciphertext, normally it equal InLen - 96
 * @return		0		-	success
 * @return		other	-	fail	
 @endif
*/ 
int app_sm2_encrypt(const void *pubKey, const u8 *DataIn, u32 InLen, void *DataOut, u32 *OutLen);

/*!
 @if Chinese
 * @brief		��sm2˽Կ��������
 * @param[in]   priKey	-	˽Կֵ(����������)
 * @param[in]   DataIn	-	�����ܵ�����(C1C2C3,û�м�0x04)
 * @param[in]   InLen	-	���������ݳ���
 * @param[out]  DataOut	-	���ܺ������
 * @param[out]  OutLen	-	���ܺ�������ĳ���, ͨ��Ϊ96
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
	
 @else
 * @brief		decrypt data using sm2 private key
 * @param[in]   priKey	-	private key(not including length)
 * @param[in]   DataIn	-	data to be decrypted(C1C2C3,without adding 0x04)
 * @param[in]   InLen	-	length of DataIn
 * @param[out]  DataOut	-	plaintext
 * @param[out]  OutLen	-	length of plaintext, normally it equal InLen - 96
 * @return		0		-	success
 * @return		other	-	fail	
 @endif
*/  
int app_sm2_decrypt(const void *priKey, const void *DataIn, u32 InLen, u8 *DataOut, u32 *OutLen);

/*!
 @if Chinese
 * @brief		��sm2��Կ��֤ǩ��
 * @param[in]   pubKey	-	��Կֵ(x����+y����������������)
 * @param[in]   Hash	-	��ped_sm2_get_hash_value�����ֵ��32�ֽ�
 * @param[in]   HashLen	-	��ϣֵ�ĳ���
 * @param[in]   Sign	-	ǩ�����ݣ���ped_sm2_sign������64�ֽ�
 * @param[in]   SignLen	-	ǩ�����ݵĳ���
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
	
 @else
 * @brief		verify signature using sm2 public key
 * @param[in]   pubKey	-	public key(x plus y, not including the length)
 * @param[in]   Hash	-	calcuate by call ped_sm2_get_hash_value, 32 bytes
 * @param[in]   HashLen	-	length of Hash
 * @param[in]   Sign	-	signature data, it was generate by ped_sm2_sign, 64 bytes
 * @param[in]   SignLen	-	length of Sign
 * @return		0		-	success
 * @return		other	-	fail	
 @endif
*/   
int app_sm2_verify(const void *pubKey, const u8 *Hash, int HashLen, const u8 *Sign, int SignLen);

/*!
 @if Chinese
 * @brief		��sm2��Կ��֤ǩ��
 * @param[in]   prikey		-	˽Կֵ(����������)
 * @param[in]   Hash		-	��ped_sm2_get_hash_value�����ֵ��32�ֽ�
 * @param[in]   HashLen		-	��ϣֵ�ĳ���
 * @param[in]   pResult		-	ǩ�����ݣ�64�ֽ�
 * @param[in]   pResultLen	-	ǩ�����ݵĳ���
 * @return		0		-	�ɹ�
 * @return		����	-	ʧ��
	
 @else
 * @brief		sign data using private key
 * @param[in]   prikey		-	private key(not including length)
 * @param[in]   Hash		-	calcuate by call ped_sm2_get_hash_value, 32 bytes
 * @param[in]   HashLen		-	length of Hash
 * @param[out]  pResult		-	signature data, 64 bytes
 * @param[out]  pResultLen	-	length of Sign data
 * @return		0		-	success
 * @return		other	-	fail	
 @endif
*/    
int app_sm2_sign(const u8 *prikey, const u8 *Hash, uint32_t HashLen, u8 *pResult, uint32_t *pResultLen);


#endif /* _SM2_H_ */
