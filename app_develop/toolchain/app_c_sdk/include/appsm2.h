/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app sm2模块</strong> 相关的接口
	 * @par 文件    appsm2.h
	 * @author		lydia
	 * @date        2021-11-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2021-11-09    | 1.0.0        | lydia         | 创建文件
	 * 2022-04-29    | 1.0.1        | lydia         | 增加英文注释  
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
	* @addtogroup app_sm2 sm2加解密
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
 * @brief		用sm2公钥加密数据
 * @param[in]   pubKey	-	公钥值(x分量+y分量，不包括长度)
 * @param[in]   DataIn	-	被加密的数据
 * @param[in]   InLen	-	被加密数据长度
 * @param[out]  DataOut	-	加密后的密文(C1C2C3,没有加0x04)
 * @param[out]  OutLen	-	加密后的密文长度, 通常为96
 * @return		0		-	成功
 * @return		其它	-	失败
	
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
 * @brief		用sm2私钥解密数据
 * @param[in]   priKey	-	私钥值(不包括长度)
 * @param[in]   DataIn	-	被解密的数据(C1C2C3,没有加0x04)
 * @param[in]   InLen	-	被解密数据长度
 * @param[out]  DataOut	-	解密后的明文
 * @param[out]  OutLen	-	解密后的明文文长度, 通常为96
 * @return		0		-	成功
 * @return		其它	-	失败
	
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
 * @brief		用sm2公钥验证签名
 * @param[in]   pubKey	-	公钥值(x分量+y分量，不包括长度)
 * @param[in]   Hash	-	被ped_sm2_get_hash_value计算的值，32字节
 * @param[in]   HashLen	-	哈希值的长度
 * @param[in]   Sign	-	签名数据，被ped_sm2_sign产生，64字节
 * @param[in]   SignLen	-	签名数据的长度
 * @return		0		-	成功
 * @return		其它	-	失败
	
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
 * @brief		用sm2公钥验证签名
 * @param[in]   prikey		-	私钥值(不包括长度)
 * @param[in]   Hash		-	被ped_sm2_get_hash_value计算的值，32字节
 * @param[in]   HashLen		-	哈希值的长度
 * @param[in]   pResult		-	签名数据，64字节
 * @param[in]   pResultLen	-	签名数据的长度
 * @return		0		-	成功
 * @return		其它	-	失败
	
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
