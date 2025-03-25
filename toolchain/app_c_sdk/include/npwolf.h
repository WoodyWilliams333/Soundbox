
#ifndef __NP_WOLFSSL_H__
#define __NP_WOLFSSL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <wolfssl/wolfcrypt/visibility.h>

#define RSA_KEY_MAX_BIT     2048

///////////////////////////////////////////////////////////////////////////////////////

//param:
//version: 存放版本信息的缓存buffer
//len: version的空间大小，应至少保证64字节
int NPWOLF_version(char *version, int len);

///////////////////////////////////////////////////////////////////////////////////////
//for BASE64
WOLFSSL_API int NPWOLF_EVP_EncodeBlock(unsigned char *to, const unsigned char *from, int lenin);
WOLFSSL_API int NPWOLF_EVP_DecodeBlock(unsigned char *to, const unsigned char *from, int lenin);

//API like openssl library
#define EVP_EncodeBlock     NPWOLF_EVP_EncodeBlock
#define EVP_DecodeBlock     NPWOLF_EVP_DecodeBlock

///////////////////////////////////////////////////////////////////////////////////////
//for RSA encrypt/decrypt

#include <stdint.h>

typedef struct     // 公钥结构
{
    uint32_t bits;                   /* length in bits of modulus */    
    uint8_t  exponent[4];            /* public exponent */
    uint8_t  modulus[256];           /* modulus */
    uint16_t usCRC;                  /* CRC 校验码 */
} R_RSA_PUBLIC_KEY;

typedef struct    // 私钥结构
{
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  modulus[256];           /* modulus */
    uint8_t  publicExponent[4];      /* public exponent */
    uint8_t  exponent[256];          /* private exponent */
    uint8_t  prime[2][128];          /* prime factors */
    uint8_t  primeExponent[2][128];  /* exponents for CRT */
    uint8_t  coefficient[128];       /* CRT coefficient */
    uint16_t usCRC;                  /* CRC 校验码 */
} R_RSA_PRIVATE_KEY;

/*
以下接口为RSA 公钥/私钥 加解密接口
输入的inputLen必须等于模长，接口内部实现没有做填充(使用的是无填充模式，数据块长度必须等于模长)；
如果参与运算的输入数据不足模长个字节，可以考虑应用层自行填充到模长个字节
1024 bits RSA  ==> 模长为128字节
2048 bits RSA  ==> 模长为256字节
值得注意的是: 对于无填充模式下，使用同一个类似的密钥(公钥或私钥)做运算，加密与解密的结果是一样的；
即当inputLen=模长时；
公钥解密 = 公钥加密 != 私钥加密
私钥加密 = 私钥解密 != 公钥解密
也就是说，
NPWOLF_RSAPublicDecrypt 既是公钥解密接口，也是公钥加密接口；本质就是一个公钥运算接口
NPWOLF_RSAPrivateEncrypt既是私钥加密接口，也是私钥解密接口；本质就是一个私钥运算接口
*/
WOLFSSL_API int32_t NPWOLF_RSAPublicDecrypt(  void *output,    /* output block */
                                            uint32_t *outputLen,         /* length of output block */
                                            const void *input,           /* input block */
                                            uint32_t inputLen,           /* length of input block */
                                            R_RSA_PUBLIC_KEY *publicKey);/* RSA public key */

WOLFSSL_API int32_t NPWOLF_RSAPrivateEncrypt ( void *output,    /* output block */
                                            uint32_t *outputLen,         /* length of output block */
                                            const void *input,           /* input block */
                                            uint32_t inputLen,           /* length of input block */
                                            R_RSA_PRIVATE_KEY *privateKey); /* RSA private key */

#ifndef NPWOLF_RSAPublicEncrypt
#define NPWOLF_RSAPublicEncrypt(output, outputLen, input, inputLen, publicKey)\
            NPWOLF_RSAPublicDecrypt(output, outputLen, input, inputLen, publicKey)
#endif

#ifndef NPWOLF_RSAPublicDecrypt
#define NPWOLF_RSAPrivateDecrypt(output, outputLen, input, inputLen, publicKey)\
            NPWOLF_RSAPrivateEncrypt(output, outputLen, input, inputLen, publicKey)
#endif

///////////////////////////////////////////////////////////////////////////////////////
#include <wolfssl/openssl/evp.h>
#include <wolfssl/openssl/ssl.h>
#include <wolfssl/openssl/hmac.h>

//for p12 file parse
WOLFSSL_API int NPWOLF_PKCS12_parse(  const char * pk12_filename, 
                                    const char* password,
                                    EVP_PKEY **prikey,
                                    EVP_PKEY **pubkey,
                                    WOLFSSL_X509 **cert,
                                    WOLF_STACK_OF(WOLFSSL_X509) **ca);

///////////////////////////////////////////////////////////////////////////////////////

#define RSA_KEY_DATA_SIGN       0
#define RSA_KEY_DATA_VERIFY     1

/*
// Hash types enum list
enum wc_HashType {
    WC_HASH_TYPE_NONE = 0,
    WC_HASH_TYPE_MD2 = 1,
    WC_HASH_TYPE_MD4 = 2,
    WC_HASH_TYPE_MD5 = 3,
    WC_HASH_TYPE_SHA = 4, // SHA-1 (not old SHA-0)
    WC_HASH_TYPE_SHA224 = 9,
    WC_HASH_TYPE_SHA256 = 5,
    WC_HASH_TYPE_SHA384 = 6,
    WC_HASH_TYPE_SHA512 = 7,
    WC_HASH_TYPE_MD5_SHA = 8,
};
*/
/*
param: dorsa, it should be filled with RSA_KEY_DATA_SIGN or RSA_KEY_DATA_VERIFY
usually: RSA private key for data sign-operation, and RSA public key for data verify-operation
for data sign: return 0 means data sign ok, negative means data sign fail
for data verify: return 0 means sign-data verify ok, negative means verify fail
*/
WOLFSSL_API int NPWOLF_RSA_sign_verify(const void *src, int srclen, void *sigdata, int *siglen, 
                        enum wc_HashType hash_type, const EVP_PKEY *rsakey, int dorsa);

///////////////////////////////////////////////////////////////////////////////////////

/*
In these API:
1.Len-in shouldn't longer than the length of RSA modulus;
2.The return value < 0, means RSA operation error, look the ret-value to found out error reason
3.The return value >=0, means RSA operation ok, the ret is the encrypt/decrypt length.
*/

WOLFSSL_API int NPWOLF_RSA_public_encrypt(int len, const unsigned char* from, 
                            unsigned char* to, const EVP_PKEY *rsakey);
WOLFSSL_API int NPWOLF_RSA_public_decrypt(int len, const unsigned char* from, 
                            unsigned char* to, const EVP_PKEY *rsakey);
WOLFSSL_API int NPWOLF_RSA_private_encrypt(int len, const unsigned char* from, 
                            unsigned char* to, const EVP_PKEY *rsakey);
WOLFSSL_API int NPWOLF_RSA_private_decrypt(int len, const unsigned char* from, 
                            unsigned char* to, const EVP_PKEY *rsakey);

///////////////////////////////////////////////////////////////////////////////////////

typedef enum PaddingType {
    PKCS1_PADDING_BLOCK_TYPE_0      = 0, //PKCS1 padding BT=00, paddind with ox00 bytes
    PKCS1_PADDING_BLOCK_TYPE_1      = 1, //PKCS1 padding BT=01, paddind with oxFF bytes
    PKCS1_PADDING_BLOCK_TYPE_2      = 2, //PKCS1 padding BT=02, paddind with random bytes
    PKCS1_PADDING_BLOCK_TYPE_2_FF   = 3, //PKCS1 padding BT=02, paddind with oxFF bytes
} PKCS1_PADDIING_TYPE;

/*
函数功能: RSA公钥/私钥、加密/解密 操作
private: 为0表示公钥操作；非0表示私钥操作
encrypt: 为0表示解密操作，非0表示加密操作
padding: 见枚举值PKCS1_PADDIING_TYPE
*/
WOLFSSL_API int NPWOLF_RSA_pub_pri_enc_dec(int len, const unsigned char* from, 
                            unsigned char* to, const EVP_PKEY *rsakey, int private, int encrypt, int padding);

///////////////////////////////////////////////////////////////////////////////////////

//for RSA key format change !!!

typedef enum FileDataFormat {
    FILE_DATA_FORMAT_DER = 0,
    FILE_DATA_FORMAT_PEM = 1,
} FILE_DATA_FORMAT;

typedef enum FileDataType {
    FILE_DATA_TYPE_RSA_PRI_KEY  = 0,
    FILE_DATA_TYPE_RSA_PUB_KEY  = 1,
    FILE_DATA_TYPE_RSA_PUB_CERT = 2,
} FILE_DATA_TYPE;

/*
In this API:
1.passwd can be private key which encrypted, it can be NULL when private key haa not passwd.
*/

WOLFSSL_API int NPWOLF_Byte_Data_2_EVP_PKEY(const unsigned char *byte, int bytelen, 
                            int format, int type, const char *passwd, EVP_PKEY **pkey);

///////////////////////////////////////////////////////////////////////////////////////

//API for software DES algorithm

#include <stdint.h>

#ifndef  ERROR
#define  ERROR	0x01
#endif

#ifndef TDEA_DECRYPT_CALL
/*
 * 加解密算法定义，用0~7位表示
 */
#define TDEA_DECRYPT_CALL       0x00000000  // TDES解密
#define TDEA_ENCRYPT_CALL       0x00000001  // TDES加密
#define TDEA_NONE_CALL          0x00000002  // 不做加解密操作
#endif

/**************************************************************************
* 函数名称:
*		    void DES(const void *source, uint8_t *dest, const void *key, uint8_t flag);
* 功能描述:
*		    实现 DES 运算
* 输入参数:
*	        DataIn      待进行DES运算的数据(8字节)
*           DesKey      DES密钥,密钥长度(8字节)
*           Mode        加密或者解密运算
* 输出参数:
*		    DataOut     DES运算后得到的数据(8字节)
* 返回值:
*		    0           运算成功
*           0x01        输入参数错误(密钥长度错误或者操作模式错误)
****************************************************************************/
WOLFSSL_API int NPWOLF_DES(const void *DataIn, void *DataOut, const void *DesKey, uint32_t Mode);


/**************************************************************************
* 函数名称:
*		    int  TDEA(uchar *DataIn, uchar *DataOut, uchar *DesKey, uint KeyLen, uint Mode)
* 功能描述:
*		    实现Tripe DES 运算
* 输入参数:
*	        DataIn      待进行TDES运算的数据(8字节)
*           DesKey      DES密钥
*           KeyLen      密钥长度(8，16，24三种可能值)
*           Mode        加密或者解密运算
* 输出参数:
*		    DataOut     TDES运算后得到的数据(8字节)
* 返回值:
*		    0           运算成功
*           0x01        输入参数错误(密钥长度错误或者操作模式错误)
****************************************************************************/
WOLFSSL_API int NPWOLF_TDEA(const void *DataIn, void *DataOut, const void *DesKey, uint32_t KeyLen, uint32_t Mode);

///////////////////////////////////////////////////////////////////////////////////////

//API for software AES algorithm

#ifndef GETU32
#define GETU32(pt) (((uint32_t)(pt)[0] << 24) ^ ((uint32_t)(pt)[1] << 16) ^ ((uint32_t)(pt)[2] <<  8) ^ ((uint32_t)(pt)[3]))
#define PUTU32(ct, st) { (ct)[0] = (uint8_t)((st) >> 24); (ct)[1] = (uint8_t)((st) >> 16); (ct)[2] = (uint8_t)((st) >>  8); (ct)[3] = (uint8_t)(st); }
#endif

#ifndef AES_ENCRYPT_CALL
#define AES_ENCRYPT_CALL    1
#define AES_DECRYPT_CALL    0
#endif

#ifndef AES_MAXNR
#define AES_MAXNR           14
#endif

#ifndef AES_BLOCK_SIZE
#define AES_BLOCK_SIZE      16
#endif

typedef struct {
		unsigned int rd_key[4 *(AES_MAXNR + 1)];
		int rounds;
} aes_key_t;

#ifndef AES_KEY
#define AES_KEY aes_key_t
#endif

/**************************************************************************
* 函数名称: (以下AES操作相关的接口，输入输出参数说明类似)
* 功能描述:
*		    实现AES各个模式下的加解密运算
* 输入参数:
*	        userKey     用户层的AES密钥，即原始的密钥数组
*           key         经库内部填充后的AES密钥，用于传入加解密接口的key
*           in          加解密的数据输入 (长度应为16的整数倍)           
*           length      输入数据的长度
*           enc         加解密的标志位， AES_ENCRYPT_CALL(1)表示加密；AES_DECRYPT_CALL(0)表示解密
*           ivec        输入向量
* 输出参数:
*		    out         加解密的数据输出
* 返回值:
*		    0           运算成功
*           其他        运算失败
****************************************************************************/

WOLFSSL_API int NPWOLF_aes_set_encrypt_key(const unsigned char *userKey, 
						const int bits, AES_KEY *key);
WOLFSSL_API int NPWOLF_aes_set_decrypt_key(const unsigned char *userKey, 
						const int bits, AES_KEY *key);
WOLFSSL_API void NPWOLF_aes_encrypt(const unsigned char *in, unsigned char *out,
				const AES_KEY *key);
WOLFSSL_API void NPWOLF_aes_decrypt(const unsigned char *in, unsigned char *out,
				const AES_KEY *key);

WOLFSSL_API void NPWOLF_aes_ecb_encrypt(const unsigned char *in, unsigned char *out, 
					const AES_KEY *key, const int enc);

WOLFSSL_API void NPWOLF_aes_cbc_encrypt(const unsigned char *in, unsigned char *out, 
					const unsigned long length, const AES_KEY *key,	
					unsigned char *ivec, const int enc);

WOLFSSL_API void NPWOLF_aes_cfb128_encrypt(const unsigned char *in, unsigned char *out, 
					const unsigned long length, const AES_KEY *key,	
					unsigned char *ivec, int *num, const int enc);

WOLFSSL_API void NPWOLF_aes_cfb1_encrypt(const unsigned char *in, unsigned char *out,	
					const unsigned long length, const AES_KEY *key,	
					unsigned char *ivec, int *num, const int enc);

WOLFSSL_API void NPWOLF_aes_cfb8_encrypt(const unsigned char *in, unsigned char *out,	
					const unsigned long length, const AES_KEY *key,	
					unsigned char *ivec, int *num, const int enc);

WOLFSSL_API void NPWOLF_aes_cfbr_encrypt_block(const unsigned char *in, unsigned char *out, 
							const int nbits, const AES_KEY *key, 
							unsigned char *ivec, const int enc);

WOLFSSL_API void NPWOLF_aes_ofb128_encrypt(const unsigned char *in, unsigned char *out, 
						const unsigned long length, const AES_KEY *key,	
						unsigned char *ivec, int *num);

WOLFSSL_API void NPWOLF_aes_ctr128_encrypt(const unsigned char *in, unsigned char *out,
						const unsigned long length, const AES_KEY *key,
						unsigned char ivec[AES_BLOCK_SIZE],
						unsigned char ecount_buf[AES_BLOCK_SIZE],
						unsigned int *num);

/* For IGE, see also http://www.links.org/files/openssl-ige.pdf */
/* NB: the IV is _two_ blocks long */
WOLFSSL_API void NPWOLF_aes_ige_encrypt(const unsigned char *in, unsigned char *out,
					const unsigned long length, const AES_KEY *key,
					unsigned char *ivec, const int enc);

/* NB: the IV is _four_ blocks long */
WOLFSSL_API void NPWOLF_aes_bi_ige_encrypt(const unsigned char *in, unsigned char *out,
						const unsigned long length, 
						const AES_KEY *key, const AES_KEY *key2, 
						const unsigned char *ivec, const int enc);

///////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif
