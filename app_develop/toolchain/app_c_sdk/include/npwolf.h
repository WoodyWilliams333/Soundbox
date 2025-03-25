
#ifndef __NP_WOLFSSL_H__
#define __NP_WOLFSSL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <wolfssl/wolfcrypt/visibility.h>

#define RSA_KEY_MAX_BIT     2048

///////////////////////////////////////////////////////////////////////////////////////

//param:
//version: ��Ű汾��Ϣ�Ļ���buffer
//len: version�Ŀռ��С��Ӧ���ٱ�֤64�ֽ�
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

typedef struct     // ��Կ�ṹ
{
    uint32_t bits;                   /* length in bits of modulus */    
    uint8_t  exponent[4];            /* public exponent */
    uint8_t  modulus[256];           /* modulus */
    uint16_t usCRC;                  /* CRC У���� */
} R_RSA_PUBLIC_KEY;

typedef struct    // ˽Կ�ṹ
{
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  modulus[256];           /* modulus */
    uint8_t  publicExponent[4];      /* public exponent */
    uint8_t  exponent[256];          /* private exponent */
    uint8_t  prime[2][128];          /* prime factors */
    uint8_t  primeExponent[2][128];  /* exponents for CRT */
    uint8_t  coefficient[128];       /* CRT coefficient */
    uint16_t usCRC;                  /* CRC У���� */
} R_RSA_PRIVATE_KEY;

/*
���½ӿ�ΪRSA ��Կ/˽Կ �ӽ��ܽӿ�
�����inputLen�������ģ�����ӿ��ڲ�ʵ��û�������(ʹ�õ��������ģʽ�����ݿ鳤�ȱ������ģ��)��
�������������������ݲ���ģ�����ֽڣ����Կ���Ӧ�ò�������䵽ģ�����ֽ�
1024 bits RSA  ==> ģ��Ϊ128�ֽ�
2048 bits RSA  ==> ģ��Ϊ256�ֽ�
ֵ��ע�����: ���������ģʽ�£�ʹ��ͬһ�����Ƶ���Կ(��Կ��˽Կ)�����㣬��������ܵĽ����һ���ģ�
����inputLen=ģ��ʱ��
��Կ���� = ��Կ���� != ˽Կ����
˽Կ���� = ˽Կ���� != ��Կ����
Ҳ����˵��
NPWOLF_RSAPublicDecrypt ���ǹ�Կ���ܽӿڣ�Ҳ�ǹ�Կ���ܽӿڣ����ʾ���һ����Կ����ӿ�
NPWOLF_RSAPrivateEncrypt����˽Կ���ܽӿڣ�Ҳ��˽Կ���ܽӿڣ����ʾ���һ��˽Կ����ӿ�
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
��������: RSA��Կ/˽Կ������/���� ����
private: Ϊ0��ʾ��Կ��������0��ʾ˽Կ����
encrypt: Ϊ0��ʾ���ܲ�������0��ʾ���ܲ���
padding: ��ö��ֵPKCS1_PADDIING_TYPE
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
 * �ӽ����㷨���壬��0~7λ��ʾ
 */
#define TDEA_DECRYPT_CALL       0x00000000  // TDES����
#define TDEA_ENCRYPT_CALL       0x00000001  // TDES����
#define TDEA_NONE_CALL          0x00000002  // �����ӽ��ܲ���
#endif

/**************************************************************************
* ��������:
*		    void DES(const void *source, uint8_t *dest, const void *key, uint8_t flag);
* ��������:
*		    ʵ�� DES ����
* �������:
*	        DataIn      ������DES���������(8�ֽ�)
*           DesKey      DES��Կ,��Կ����(8�ֽ�)
*           Mode        ���ܻ��߽�������
* �������:
*		    DataOut     DES�����õ�������(8�ֽ�)
* ����ֵ:
*		    0           ����ɹ�
*           0x01        �����������(��Կ���ȴ�����߲���ģʽ����)
****************************************************************************/
WOLFSSL_API int NPWOLF_DES(const void *DataIn, void *DataOut, const void *DesKey, uint32_t Mode);


/**************************************************************************
* ��������:
*		    int  TDEA(uchar *DataIn, uchar *DataOut, uchar *DesKey, uint KeyLen, uint Mode)
* ��������:
*		    ʵ��Tripe DES ����
* �������:
*	        DataIn      ������TDES���������(8�ֽ�)
*           DesKey      DES��Կ
*           KeyLen      ��Կ����(8��16��24���ֿ���ֵ)
*           Mode        ���ܻ��߽�������
* �������:
*		    DataOut     TDES�����õ�������(8�ֽ�)
* ����ֵ:
*		    0           ����ɹ�
*           0x01        �����������(��Կ���ȴ�����߲���ģʽ����)
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
* ��������: (����AES������صĽӿڣ������������˵������)
* ��������:
*		    ʵ��AES����ģʽ�µļӽ�������
* �������:
*	        userKey     �û����AES��Կ����ԭʼ����Կ����
*           key         �����ڲ������AES��Կ�����ڴ���ӽ��ܽӿڵ�key
*           in          �ӽ��ܵ��������� (����ӦΪ16��������)           
*           length      �������ݵĳ���
*           enc         �ӽ��ܵı�־λ�� AES_ENCRYPT_CALL(1)��ʾ���ܣ�AES_DECRYPT_CALL(0)��ʾ����
*           ivec        ��������
* �������:
*		    out         �ӽ��ܵ��������
* ����ֵ:
*		    0           ����ɹ�
*           ����        ����ʧ��
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
