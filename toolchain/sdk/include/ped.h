
/**
@if Chinese
 * @brief       ��ģ���������� <strong>PEDģ��</strong> ��صĽӿ�
 * @note        �û�����PED�ӿ�ʱ����Ҫ�������ļ�
 * @date        2018/10/30
 * @version     1.0.1
 * @remarks
 *              Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2018/10/30    |  Milton.Wu      | Create file
 * 2022/04/20    | Wenming         | ����Ӣ��ע��
@else	 
  * @brief       This module is used to describe <strong>PED</strong> interfaces module
 * @note        This file is required when users invoke the PED interface
 * @date        2018/10/30
 * @version     1.0.1
 * @remarks
 *              Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2018/10/30    |  Milton.Wu      | Create file
 * 2022/04/20    | Wenming         | Add English description
@endif	 
 */


/**
 * @defgroup PED PED
 * @{
 */

#ifndef __PED_H__
#define __PED_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
 * @brief ��Կ��ϵ����
@else 
 * @brief Key System Definition
@endif 
 */
typedef enum {
    MS_DES          = 0x00,                             /**< 0 : Master Session DES         */
    MS_SM4,                                             /**< 1 : Master Session SM4         */
    FIXED_DES,                                          /**< 2 : FIXED DES                  */
    FIXED_SM4,                                          /**< 3 : FIXED SM4                  */
    DUKPT_DES,                                          /**< 4 : DUKPT DES                  */
    ICC_PLAIN,                                          /**< 5 : ic card Offline plain pin  */
    ICC_CIPHER,                                         /**< 6 : ic card offline cipher pin */
    TMS_DES,                                            /**< 7 : TMS DES                    */
    KS_SM2,                                             /**< 8 : SM2 key system             */
    KS_RSA,                                             /**< 9 : RSA                        */
    KS_ANS,                                             /**< 10: ANS SM4                    */
    MS_AES,                                             /**< 11: AES                        */
    FIXED_AES,                                          /**< 12: FIXED AES                  */
    FIXED_TMTK,                                         /**< 13: FIXED TRANSMIT key system  */
    DUKPT_AES,                                          /**< 14: DUKPT AES                  */
    KS_MAX,                                             /**< END                            */
} KeySystem_t;

/**
@if Chinese
 * @brief   DUKPT AES�������Ŀ��ܵ���Կ�÷�
@else 
 * @brief   DUKPT AES is the possible key usage that can be derived
@endif 
 */
typedef enum TagKeyUsage  {
	_Key_Encryption_Key_, 
	_PIN_Encryption_, 
	_Message_Authentication_generation_,   
	_Message_Authentication_verification_,
	_Message_Authentication_both_ways_,   
	_Data_Encryption_encrypt_,   
	_Data_Encryption_decrypt_,  
	_Data_Encryption_both_ways_,  
}KeyUsage;

/**
@if Chinese
 * @brief   DUKPT AES�����ļ�����Կ����
@else 
 * @brief   DUKPT AES Derived encryption key type
@endif
 */
typedef enum TagKeyType {
	_2TDEA_,
	_3TDEA_,
	_AES128_, 
	_AES192_, 
	_AES256_, 
} DUKPTKeyType;

/**
@if Chinese
 * @brief PED ״̬����: ����������������
@else 
 * @brief PED Status definition: locked, normal, expired
@endif
 */
typedef enum {
    PED_STATUS_LOCK         =   0,                      /**<@if Chinese PED ����״̬��������������     @else PED locked. Machine has been attacked 	@endif*/
    PED_STATUS_NORMAL,                                  /**<@if Chinese PED ����״̬                   @else PED normal state 						@endif*/
    PED_STATUS_EXPIRED,                                 /**<@if Chinese PED ����״̬                   @else PED expired status 					@endif*/
} PedStatus_t;

/**
@if Chinese
 * @name ���з����϶����
@else  
 * @name Sensitive service gap definition
@endif
 * @{
 */
#define TYPE_PIN_INTERVAL       0x01                    /**< PIN Input interval             */
#define TYPE_UPDATE_INTERVAL    0x02                    /**< Firmware update interval       */
#define TYPE_ACCOUNT_INTERVAL   0x03                    /**< Account data encrypt interval  */
#define TYPE_INJECT_INTERVAL    0x04                    /**< key inject interval            */
/** @} */

/**
@if Chinese
 * @name �ӽ����㷨���壬��0~7λ��ʾ
@else 
 * @name Encryption and decryption algorithm definition, represented by 0 to 7 bits
@endif
 * @{
 */
#define TDEA_DECRYPT            0x00000000              /**<@if Chinese TDES����                       @else TDES decode 									@endif*/
#define TDEA_ENCRYPT            0x00000001              /**<@if Chinese TDES����                       @else TDES encrypt  									@endif*/
#define TDEA_NONE               0x00000002              /**<@if Chinese �����ӽ��ܲ���(��ped��apiʹ��) @else No encryption or decryption (for ped API use) 	@endif*/
#define SM4_DECRYPT             0x00000010              /**<@if Chinese SM4����                        @else SM4 decode  									@endif*/
#define SM4_ENCRYPT             0x00000011              /**<@if Chinese SM4����                        @else SM4 encrypt 									@endif*/
#define SM4_NONE                0x00000012              /**<@if Chinese �����ӽ��ܲ���(��ped��apiʹ��) @else No encryption or decryption (for ped API use) 	@endif*/
#define AES_DECRYPT             0x00000020              /**<@if Chinese AES����                        @else AES decode  									@endif*/
#define AES_ENCRYPT             0x00000021              /**<@if Chinese AES����                        @else AES encrypt 									@endif*/
#define AES_NONE                0x00000022              /**<@if Chinese �����ӽ��ܲ���(��ped��apiʹ��) @else No encryption or decryption (for ped API use) 	@endif*/
/** @} */

/**
@if Chinese
 * @name �ӽ���ģʽ���壬��8~15λ��ʾ
@else 
 * @name Encryption and decryption mode definition, represented by 8 to 15 bits
@endif 
 * @{
 */
#define TDEA_MODE_ECB           0x00000000              /**< TDEA MODE ECB          */
#define TDEA_MODE_CBC           0x00000100              /**< TDEA MODE CBC          */
#define TDEA_MODE_CFB           0x00000200              /**< TDEA MODE CFB          */
#define TDEA_MODE_OFB           0x00000300              /**< TDEA MODE OFB          */
#define SM4_MODE_ECB            0x00001000              /**< SM4 MODE ECB           */
#define SM4_MODE_CBC            0x00001100              /**< SM4 MODE CBC           */
#define SM4_MODE_CFB            0x00001200              /**< SM4 MODE CFB           */
#define SM4_MODE_OFB            0x00001300              /**< SM4 MODE OFB           */
#define AES_MODE_ECB            0x00002000              /**< AES MODE ECB           */
#define AES_MODE_CBC            0x00002100              /**< AES MODE CBC           */
#define AES_MODE_CFB            0x00002200              /**< AES MODE CFB           */
#define AES_MODE_OFB            0x00002300              /**< AES MODE OFB           */
/** @} */

/**
@if Chinese
 * @name У���㷨����24~31λ��ʾ
@else 
 * @name Check algorithm, represented by 24 to 31 bits
@endif 
 * @{
 */
#define KEY_VERIFY_NONE         0x00000000              /**<@if Chinese ��У��                 @else no parity 		@endif*/
#define KEY_VERIFY_KVC          0x01000000              /**<@if Chinese KVC use DES            @else KVC use DES  	@endif*/
#define KEY_VERIFY_CMAC         0x02000000              /**<@if Chinese CMAC                   @else CMAC 			@endif*/
#define KEY_VERIFY_SM4_KVC      0x11000000              /**<@if Chinese KVC use SM4            @else KVC use SM4  	@endif*/
#define KEY_VERIFY_MASK         0xff000000              /**<@if Chinese ����                   @else mask  			@endif*/
/** @} */

/**
@if Chinese
 * @name PIN BLOCK �㷨����
@else 
 * @name PIN BLOCK Definition of Algorithm
@endif  
 * @{
 */
#define PIN_BLOCK_FORMAT_0      0x00                    /**< PIN BLOCK FORMAT 0     */
#define PIN_BLOCK_FORMAT_1      0x01                    /**< PIN BLOCK FORMAT 1     */
#define PIN_BLOCK_FORMAT_2      0x02                    /**< PIN BLOCK FORMAT 2     */
#define PIN_BLOCK_FORMAT_3      0x03                    /**< PIN BLOCK FORMAT 3     */
#define PIN_BLOCK_FORMAT_4      0x04                    /**< PIN BLOCK FORMAT 4     */
#define PIN_BLOCK_FORMAT_EPS    0x0A                    /**< PIN BLOCK FORMAT EPS   */
/** @} */

/**
@if Chinese
 * @name MAC BLOCK �㷨����
@else  
 * @name MAC BLOCK Definition of Algorithm
@endif  
 * @{
 */
#define MAC_MODE_1              0x00                    /**< MAC method 1, TDES-TDES...TDES                         */
#define MAC_MODE_2              0x01                    /**< MAC method 2, XOR...XOR...TDES                         */
#define MAC_MODE_EMV            0x02                    /**< MAC for EMV EMV, DES-DES...TDES                        */
#define MAC_MODE_CUP            0x03                    /**< MAC for CUP, XOR-XOR...TDES(left)-XOR-TDES...          */
#define MAC_MODE_DUKPT          0x04                    /**< MAC for DUKPT,Expand, XOR-XOR...TDES(left)-XOR-TDES... */
#define MAC_MODE_CUP_8          0x05                    /**< MAC for CUP, XOR-XOR...TDES(left)-XOR-TDES...          */
#define MAC_MODE_1_8            0x06                    /**< MAC for CUP, TDES-TDES...TDES                          */
/** @} */

/**
@if Chinese
 * @name ��Կ����
@else 
 * @name Key Type
@endif 
 * @{
 */
#define KEY_TYPE_SIEK           0x01                    /**< The key to encrypt the internal sensitive infomation(internal use) */
#define KEY_TYPE_MASTK          0x02                    /**< MASTER KEY                             */
#define KEY_TYPE_PINK           0x03                    /**< PIN KEY                                */
#define KEY_TYPE_MACK           0x04                    /**< MAC KEY                                */
#define KEY_TYPE_FIXPINK        0x05                    /**< Fixed PIN KEY                          */
#define KEY_TYPE_FIXMACK        0x06                    /**< Fixed MAC KEY                          */
#define KEY_TYPE_DUKPTK         0x07                    /**< DUKPT KEY                              */
#define KEY_TYPE_EMRKEY         0x08                    /**< The key for securty magstripe reader   */
#define KEY_TYPE_KMMK           0x09                    /**< The key for KMM                        */
#define KEY_TYPE_EAK            0x0A                    /**< Account Data KEY                       */
#define KEY_TYPE_FIXEAK         0x0B                    /**< Fixed Account Data KEY                 */
#define KEY_TYPE_TMSK           0x0C                    /**< TMS KEY                                */
#define KEY_TYPE_SM2PRI         0x0D                    /**< SM2 Private KEY                        */
#define KEY_TYPE_RSAPRIK        0x0E                    /**< RSA PRIVATE KEY                        */
#define KEY_TYPE_ANSK           0x0F                    /**< ANS SM4 KEY                            */
#define KEY_TYPE_RSA_CA_CERT    0x10                    /**< RSA CA CERT                            */
#define KEY_TYPE_RSA_CLIENT_CERT      0x11              /**< RSA CLIENT CERT                        */
#define KEY_TYPE_RSA_PIN        0x12                    /**< RSA PIN                                */
#define KEY_TYPE_RSA_PIN_CERT   0x13                    /**< RSA PIN CERT                           */
#define KEY_TYPE_FIXTRANSMIT    0x14                    /**< FIX DES TRANSMIT KEY                   */
#define KEY_TYPE_EXPIRED_KEY    0xFE                    /**< The expired key                        */
#define KEY_TYPE_INVALID        0xFF                    /**< Invalid key                            */
/** @} */

/**
@if Chinese
 * @name ����ֵ����
@else 
 * @name returned value define
@endif 
 * @{
 */
#define PED_RET_OK              0x00                    /**< PED OK                                                 */
#define PED_RET_BASE_NO         2000                    /**< PED return code base number                            */
#define PED_RET_LOCKED          (PED_RET_BASE_NO +  1)  /**< PED Locked                                             */
#define PED_RET_ERROR           (PED_RET_BASE_NO +  2)  /**< The others error                                       */
#define PED_RET_COMMERR         (PED_RET_BASE_NO +  3)  /**< Communicate with PED failed                            */
#define PED_RET_NEEDAUTH        (PED_RET_BASE_NO +  4)  /**< Need auth before use sensitive service or expired      */
#define PED_RET_AUTHERR         (PED_RET_BASE_NO +  5)  /**< PED auth failed                                        */
#define PED_RET_WEAK_KEY        (PED_RET_BASE_NO +  6)  /**< weak length key                                        */
#define PED_RET_COLLISION_KEY   (PED_RET_BASE_NO +  7)  /**< collision key                                          */
#define PED_RET_KEYINDEXERR     (PED_RET_BASE_NO +  8)  /**< The index of key incorrect                             */
#define PED_RET_NOKEY           (PED_RET_BASE_NO +  9)  /**< No designated key in PED                               */
#define PED_RET_KEYFULL         (PED_RET_BASE_NO + 10)  /**< Key space is full                                      */
#define PED_RET_OTHERAPPKEY     (PED_RET_BASE_NO + 11)  /**< The designated key is not belong to this APP           */
#define PED_RET_KEYLENERR       (PED_RET_BASE_NO + 12)  /**< The key length error                                   */
#define PED_RET_NOPIN           (PED_RET_BASE_NO + 13)  /**< Card holder press ENTER directly when enter PIN(no PIN)*/
#define PED_RET_CANCEL          (PED_RET_BASE_NO + 14)  /**< Card holder press CANCEL to quit enter PIN             */
#define PED_RET_TIMEOUT         (PED_RET_BASE_NO + 15)  /**< Timeout                                                */
#define PED_RET_NEEDWAIT        (PED_RET_BASE_NO + 16)  /**< Two frequent between 2 sensitive API                   */
#define PED_RET_KEYOVERFLOW     (PED_RET_BASE_NO + 17)  /**< DUKPT KEY overflow                                     */
#define PED_RET_NOCARD          (PED_RET_BASE_NO + 18)  /**< No ICC                                                 */
#define PED_RET_ICCNOTPWRUP     (PED_RET_BASE_NO + 19)  /**< ICC no power up                                        */
#define PED_RET_PARITYERR       (PED_RET_BASE_NO + 20)  /**< The parity incorrect                                   */
#define PED_RET_UNSUPPORTED     (PED_RET_BASE_NO + 255) /**< can not support                                        */
/** @} */

/**
@if Chinese
 * @name RSA ģλ��
@else 
 * @name RSA modular digit
@endif 
 * @{
 */
#define MIN_RSA_BITS            2048                    /**<@if Chinese RSA��Կλ������С����  @else	Minimum length of RSA key bits		@endif*/
#define MAX_RSA_BITS            4096                    /**<@if Chinese RSA��Կλ������󳤶�  @else	Maximum length of the RSA key digit	@endif*/
/** @} */

/**
@if Chinese
 * @name ECC��غ궨��
@else  
 * @name ECC Related macro definitions
@endif 
 * @{
 */
#define ECC_BIGINT32_MAXLEN     18

#define ECC_P256_BITS           256
#define ECC_P521_BITS           544

#define ECC_P256_BYTES          (((ECC_P256_BITS + 31) >> 5) << 2)                      //���ֽڶ���������ֽ�
#define ECC_P521_BYTES          (((ECC_P521_BITS + 31) >> 5) << 2)

#define ECC_P256_TYPE           0
#define ECC_P521_TYPE           1

#define ECC_MAX_PRI_KEY_SIZE        ECC_P521_BYTES
#define ECC_MAX_PUB_KEY_X_SIZE      ECC_P521_BYTES
#define ECC_MAX_PUB_KEY_Y_SIZE      ECC_P521_BYTES
#define ECC_MAX_PUB_KEY_SIZE        (ECC_MAX_PUB_KEY_X_SIZE + ECC_MAX_PUB_KEY_Y_SIZE)
/** @} */

/**
@if Chinese
 * @brief PED ������Ϣ����
@else 
 * @brief PED Configuration Information Definition
@endif 
 */
typedef struct {
    char        Model[16];      /**< Machine Type               */
    char        HwVer[16];      /**< Hardware Version           */
    char        SwVer[16];      /**< Software Version           */
    uint32_t    Status;         /**< PED status                 */
    uint32_t    MaxBps;         /**< PED MAX Baud Rate          */
    uint32_t    MaxAppNum;      /**< Max Application Number     */
    uint32_t    MasterKeyNum;   /**< Max Master Key Number      */
    uint32_t    PINKeyNum;      /**< Max PIN Key Number         */
    uint32_t    MACKeyNum;      /**< Max MAC Key Number         */
    uint32_t    FixPINKeyNum;   /**< Max Fixed PIN Key Number   */
    uint32_t    FixMACKeyNum;   /**< Max Fixed MAC Key Number   */
    uint32_t    DukptKeyNum;    /**< Max DUKPT Key Number       */
    uint32_t    Ctime;          /**< Create Time                */
    uint32_t    MagKeyTime;     /**< MagKey Create Time         */
    uint32_t    MagKeyStatus;   /**< MagKey valid or not        */
    int16_t     MaxTemp;        /**< High Temperature Limit     */
    int16_t     MinTemp;        /**< Low  Temperature Limit     */
    int16_t     CurTemp;        /**< Current CPU Temperature    */
    uint32_t    EAKKeyNum;      /**< Max EAK Key Number         */
    uint32_t    FixEAKKeyNum;   /**< Max Fixed EAK Key Number   */
    uint8_t     Res[146];       /**< Reserved                   */
} PedConfig_t; /* Total 256 bytes */

/**
@if Chinese
 * @brief RSA PIN key ����
@else 
 * @brief RSA PIN key definition
@endif
 */
typedef struct {
    uint32_t   modlen;          /**< The module length of PIN encryption public key    */
    uint8_t    mod[256];        /**< The module data of PIN encryption public key      */
    uint32_t   explen;          /**< The exponet length of PIN encryption public key   */
    uint8_t    exp[4];          /**< The exponet data of PIN encryption public key     */
    uint8_t    iccrandom[8];    /**< The random data from ICC                          */
} RsaPinKey_t;

/**
@if Chinese
 * @brief IC���ѻ�PIN��ADPU����
@else 
 * @brief IC card offline pin define
@endif 
 */
typedef struct {
    uint8_t     cla;            /**< APDU param cla     */
    uint8_t     ins;            /**< APDU param ins     */
    uint8_t     p1;             /**< APDU param p1      */
    uint8_t     p2;             /**< APDU param p2      */
    uint8_t     leflg;          /**< APDU param leflg   */
    uint8_t     le;             /**< APDU param le      */
    RsaPinKey_t rsakey;         /**< RSA key            */
} IccOfflinePinApdu_t;

/**
@if Chinese
 * @brief ǩ����ϣ����
@else 
 * @brief signature hash type
@endif
 */
typedef enum {
    RSA_HASH_NONE      = 0,
    RSA_HASH_MD2       = 1,     /*   unsupported                            */
    RSA_HASH_MD4       = 2,     /*   unsupported                            */
    RSA_HASH_MD5       = 3,     /*   unsupported                            */
    RSA_HASH_SHA1      = 4,     /**< supported !!! SHA1 digest algorithm    */
    RSA_HASH_SHA224    = 5,     /*   unsupported                            */
    RSA_HASH_SHA256    = 6,     /**< supported !!! SHA256 digest algorithm  */
    RSA_HASH_SHA384    = 7,     /*   unsupported                            */
    RSA_HASH_SHA512    = 8,     /*   unsupported                            */
    RSA_HASH_MAX,
} R_Hash_Type;

/**
@if Chinese
 * @brief RSA ��Կ�ṹ
@else 
 * @brief RSA public key
@endif 
 */
typedef struct {   
    uint32_t bits;                   /**< length in bits of modulus */
    uint8_t  exponent[4];            /**< public exponent           */
    uint8_t  modulus[256];           /**< modulus                   */
} RsaPublicKey_t;

/**
@if Chinese
 * @brief RSA private key
@else 
 * @brief RSA  ˽Կ�ṹ
@endif 
 */
typedef struct {  // ˽Կ�ṹ
    uint32_t bits;                   /**< length in bits of modulus */
    uint8_t  modulus[256];           /**< modulus                   */
    uint8_t  publicExponent[4];      /**< public exponent           */
    uint8_t  exponent[256];          /**< private exponent          */
    uint8_t  prime[2][128];          /**< prime factors             */
    uint8_t  primeExponent[2][128];  /**< exponents for CRT         */
    uint8_t  coefficient[128];       /**< CRT coefficient           */
} RsaPrivateKey_t;

typedef struct {
    uint16_t   uLen;                         //32λ�����ʵ�ʳ���
    uint32_t   auValue[ECC_BIGINT32_MAXLEN]; //32λ�����ֵ������ĵ�32λ��ַ��Ŵ����ĵ�32λ��Ч������32λ��ַ��Ŵ����ĸ�32λ��Ч��
} ECC_STU_BIGINT32;

typedef struct {
    ECC_STU_BIGINT32  stuQx;                    // ��Կ����Qx
    ECC_STU_BIGINT32  stuQy;                    // ��Կ����Qy
} ECC_STU_PUBKEY;

typedef struct {
    uint16_t uBits;                             // ģ��P��λ��
    ECC_STU_BIGINT32  stuPrimeP;                // ģ��P
    ECC_STU_BIGINT32  stuCoefficientA;          // ��Բϵ��A
    ECC_STU_BIGINT32  stuCoefficientB;          // ��Բϵ��B
    ECC_STU_BIGINT32  stuGx;                    // ��Բ��������Gx
    ECC_STU_BIGINT32  stuGy;                    // ��Բ��������Gy
    ECC_STU_BIGINT32  stuPrimeN;                // ��Բ��������G�Ľ�
} ECC_STU_PRAMS;

typedef struct {
    int        len;
    uint8_t    x[ECC_MAX_PUB_KEY_X_SIZE];
    uint8_t    y[ECC_MAX_PUB_KEY_Y_SIZE];
} ECC_PubKey_t;

typedef struct {
    int        len;
    uint8_t    key[ECC_MAX_PRI_KEY_SIZE];
} ECC_PriKey_t;

typedef struct {
    ECC_PubKey_t PubKey;
    ECC_PriKey_t PriKey;
} ecc_genkey_t;

/**
@if Chinese
 * @brief	ͨ��PED��RNG�л�ȡһϵ���������
 * @param[in]	bytes	-	Ԥ�����ݳ���
 * @param[out]	data	-	Ԥ������ָ��
 * @retval		0    	-	�ɹ�
 * @retval      ����	-	ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief       get a serials of random data from RNG by PED
 * @param[in]   bytes	-	how many data you want to get
 * @param[out]  data	-	point the buffer that data save to
 * @retval      0		-	success
 * @retval      other	-	failure, use errno to get detail
@endif
 */
int ped_get_random_nr(uint32_t bytes, void *data);


/**
@if Chinese
 * @brief       ��ȡPED������
 * @param[out]  config	-	ָ�򱣴���Ϣ�Ļ�����
 * @retval      0		-	�ɹ�
 * @retval      ����	-	ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief       get configuation of PED
 * @param[out]  config	-	point the buffer that inforamtion save to
 * @retval      0		-	success
 * @retval      other	-	failure, use errno to get detail
@endif 
 */
int ped_get_config(PedConfig_t *config);

/**
 @if Chinese
	@brief       ��ȡPED״̬����֪�������Ƿ񴥷����Լ�����Դ
	@param[out]  status	-	����Դ (0 - ������ ���� - ����Դ)
	@retval      0        �ɹ�
	@retval		 ����    ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief       get the ped status, it can tell you the tamper source
	@param[out]  status	-	tamper source (0-normal, other-tamper source)
	@retval      0        successful
	@retval		 other    failure, use errno to get detail 
 @endif
*/
int ped_get_full_status(uint64_t *status);

/*!
 @if Chinese
	@brief       ����PED��Ļ����λ��
	@param[in]   x,y			-	�����꣬������
	@param[in]   width,height	-	���ڵĿ�ȣ��߶�
	@retval      0        		-	�ɹ�
	@retval		 ����    		-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        set position and size of PIN input window
	@param[in]    x,y			-	start pointer of window
	@param[in]    width,height	-	window size, it will be ignore in A-SMART platform
	@retval       0             -	successful
	@retval		  other         -	failure, use errno to get detail 
 @endif
*/ 
int ped_set_pin_input_region(int x, int y, int width, int height);

#if 0
/**
 @if Chinese
	@brief       �ؽ�PED�����߳�PED��ʽ����������PED��Կ���������PED���������״̬
	@retval      0			-	�ɹ�
	@retval		 ����    	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note        ��PED���ڹ���״̬ʱ��ֻ��RootȨ�޵ĳ����ܹ���PED��ʽ����
 @else
	@brief       clear all the Keys and tamper, make PED enter normal status
	@retval      0			-	successful
	@retval		 other		-	failure, use errno to get detail 
	@note        if PED is tampered, normal application call this function will be refused; \n
                 privilege application can call it at any time.
 @endif
 */
int ped_format(void);
#endif //�ڲ��ӿڣ�������

/*!
 @if Chinese
	@brief       �����ǰ�û�����ǰӦ�ã���PED��Կ
	@retval      0        	-	�ɹ�
	@retval		 ����    	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief       clear all the Keys belongs to this application, other Keys not belong to this application will not be clear.
	@retval      0         	-	successful
	@retval		 other     	-	failure, use errno to get detail 
 @endif
*/
int ped_clear_user_keys(void);

/*!
 @if Chinese
	@brief       ɾ��ָ�������ڸ�APP����Կ
	@param[in]   KeySystem	-	MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
	@param[in]   KeyType	-	KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
	@param[in]   KeyIndex	-	��Կ������
	@retval      0        	-	�ɹ�
	@retval		 ����    	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note        KeySystem��KeyType���Ծ���Ҫɾ��������Կ�����磬KeySystemΪFIXED_DES��KeyTypeΪKEY_TYPE_PINK����ԿӦΪ��Fixed PIN Key��
 @else
	@brief        delete a Key that belong to this APP
	@param[in]    KeySystem	-	MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
	@param[in]    KeyType	-	KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
	@param[in]    KeyIndex	-	index of Key
	@retval       0        	-	successful
	@retval		  other    	-	failure, use errno to get detail 
	@note         KeySystem and KeyType can decide which type of key will be deleted. \n
				  for example, KeySystem is FIXED_DES, KeyType is KEY_TYPE_PINK, the key should be "Fixed PIN Key"
 @endif
*/ 
int ped_delete_key_unified(KeySystem_t KeySystem, uint32_t KeyType, uint32_t KeyIndex);


/*!
 @if Chinese
	@brief       ��ȡPED���з���ʱ��
	@param[in]   SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL, TYPE_INJECT_INTERVAL
	@retval      >=0     -	ʣ���ʱ��(��λ:��)
	@retval		 ����    -	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        get timer left of call sensitive service, for example PIN enter.
	@param[in]    SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL
	@retval       >=0         -	time left in seconds
	@retval		  other       -	failure, use errno to get detail 
 @endif
*/  
int ped_get_sensitive_timer(uint32_t SensitiveType);

/*!
 @if Chinese
	@brief       ��ѯ���з��������Ҫ�ȴ�ʱ�䲢�������з���ʹ�����ƴ���
	@param[in]   SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL, TYPE_INJECT_INTERVAL
	@retval      >0				-	��Ҫ�ȴ���ʱ�� 
	@retval      =0				-	����Ҫ�ȴ�
	@retval		 ����			-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        increase counts and get if need wait for call sensitive service, for example PIN enter.
	@param[in]    SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL
	@retval       >0			-	need wait time 
	@retval       =0			-	no need to wait
	@retval		  other			-	failure, use errno to get detail 
 @endif
*/
int ped_try_and_get_sensitive_timer(uint32_t SensitiveType);

/*!
 @if Chinese
	@brief       ����PIN���볬ʱʱ��
	@param[in]   timeout  
				    time  | description
				 :------: | :--------: 
				   >120	  | �Ƿ�ֵ
				   30~120 | ��Ч����
				   0	  | ����ΪĬ��ֵ60s
				   <30	  | �Ƿ�����
	@retval      0		-	�ɹ�
	@retval		 ����	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        set timeout of PIN input
	@param[in]   timeout  
				    time  | description
				 :------: | :--------: 
				   >120	  | invalid value
				   30~120 | valid value
				   0	  | default is 60s
				   <30	  | invalid value
	@retval       0			-	successful
	@retval		  other		-	failure, use errno to get detail 
 @endif
*/
int ped_set_pin_input_timeout(uint32_t timeout);

/*!
 @if Chinese
	@brief       ��ȡPIN���볬ʱʱ��
	@retval      0			-	�ɹ�
	@retval		 ����    	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        get timeout of PIN input
	@retval       0			-      successful
	@retval		  other		-      failure, use errno to get detail 
 @endif
*/
int ped_get_pin_input_timeout(void);

/*!
 @if Chinese
	@brief        ע��dukpt��Կ����������ped��
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[in]    InitKey	-	��ʼ��Կ, 16�ֽ�
	@param[in]    KeyLen	-	��Կ����, �̶�Ϊ16
	@param[in]    Ksn		-	KSN, 10�ֽ�
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        create a DUKPT key and save to PED
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[in]    InitKey	-	initialized key, 16 bytes.
	@param[in]    KeyLen	-	key len, default is 16
	@param[in]    Ksn		-	KSN, 10 bytes.
	@retval       0         -	successful
	@retval		  other     -	failure, use errno to get detail 
 @endif
*/ 
int ped_create_dukpt_key(uint32_t    KeyIndex,
                         const void *InitKey,
                         uint32_t    KeyLen,
                         const void *Ksn);

/*!
 @if Chinese
	@brief        ���¸�DUKPT Key��KSN��KSN������
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[out]   Ksn		-	KSN, 10�ֽ�
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         һ�ε�����������������PIN�벢������ȡһ��mac
 @else
	@brief        update KSN of this DUKPT Key, KSN will increased
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[out]   Ksn		-	KSN, 10 bytes.
	@retval       0         -	successful
	@retval		  other     -	failure, use errno to get detail 
    @note         call it once can allow you enter PIN and get mac one time individually.
 @endif
*/ 
int ped_dukpt_renew(uint32_t KeyIndex, void *Ksn);

/*!
 @if Chinese
	@brief        ��ȡKSN, ��ȡ��KSN�ڼ���һ��PIN��MACʱ���ֲ���
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[out]   Ksn		-	KSN, 10�ֽ�
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         �����������2��PIN���������2�ε���MAC���㣬��2�ε��õ�ʱ��KSN���Զ����ӣ���˻�ȡ��KSNֻ�ܱ�֤����һ��PIN��һ��MAC����ı䡣
 @else
	@brief        update KSN of this DUKPT Key, KSN will increased
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[out]   Ksn		-	KSN, 10 bytes.
	@retval       0        	-	successful
	@retval		  other     -	failure, use errno to get detail 
    @note         If the PIN block is calculated twice or the MAC block is calculated twice, the KSN will be automatically increased when the second call is made. \n 
				  so the obtained KSN can only guarantee that the PIN and MAC are calculated once and will not change.
 @endif
*/
int ped_get_dukpt_ksn(uint32_t KeyIndex, void *Ksn);

/*!
 @if Chinese
	@brief        ��dukpt��Կ�����������ݣ����ñ�������������KSN.
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[in]    DataLen	-	Ҫ�������ݳ��ȣ�����Ϊ8�ı���
	@param[in]    DataIn	-	Ҫ���ܵ�����
	@param[out]   DataOut	-	������ܺ�Ľ�����䳤�����������ݳ���һ��
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ�����ڼ������ݷ�����������
 @else
	@brief        Use dukpt key to encrypt request data. Calling this function will not increase KSN.
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[in]    DataLen	-	length of DataIn in bytes
	@param[in]    DataIn	-	plaintext data
	@param[out]   DataOut	-	ciphertext data
	@retval       0         -	successful
	@retval		  other     -	failure, use errno to get detail 
    @note         This function is usually used to send encrypted data to the server.
 @endif
*/
int ped_dukpt_encrypt_request(uint32_t    KeyIndex,
                              uint32_t    DataLen,
                              const void *DataIn,
                              void       *DataOut);

/*!
 @if Chinese
	@brief        ��dukpt��Կ������Ӧ���ݣ����ñ�������������KSN.
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[in]    DataLen	-	Ҫ�������ݳ��ȣ�����Ϊ8�ı���
	@param[in]    DataIn	-	Ҫ���ܵ�����
	@param[out]   DataOut	-	������ܺ�Ľ�����䳤�����������ݳ���һ��
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ�����ڽ��ܷ��������������������ݡ�
 @else
	@brief        The dukpt key is used to decrypt the response data. Calling this function will not increase the KSN.
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[in]    DataLen	-	length of DataIn in bytes
	@param[in]    DataIn	-	ciphertext data
	@param[out]   DataOut	-	plaintext data
	@retval       0         -   successful
	@retval		  other     -   failure, use errno to get detail 
    @note         This function is usually used to decrypt the ciphertext data sent by the server.
 @endif
*/
int ped_dukpt_decrypt_response(uint32_t    KeyIndex,
                               uint32_t    DataLen,
                               const void *DataIn,
                               void       *DataOut);

/*!
 @if Chinese
	@brief        ��dukpt��Կ������Ӧ���ݣ����ñ�������������KSN.
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[in]    DataLen	-	Ҫ�������ݳ��ȣ�����Ϊ8�ı���
	@param[in]    DataIn	-	Ҫ���ܵ�����
	@param[out]   DataOut	-	������ܺ�Ľ�����䳤�����������ݳ���һ��
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ�����ڽ��ܷ��������������������ݡ�
 @else
	@brief        The dukpt key is used to decrypt the response data. Calling this function will not increase the KSN.
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[in]    DataLen	-	length of DataIn in bytes
	@param[in]    DataIn	-	ciphertext data
	@param[out]   DataOut	-	plaintext data
	@retval       0         -	successful
	@retval		  other     -	failure, use errno to get detail 
    @note         This function is usually used to decrypt the ciphertext data sent by the server.
 @endif
*/
int ped_dukpt_decrypt_request(uint32_t KeyIndex,
                              uint32_t DataLen,
                              const void *DataIn,
                              void *DataOut);

/*!
 @if Chinese
	@brief        ��dukpt��Կ����������������ݵ�MAC�����ñ�������������KSN.
	@param[in]    KeyIndex	-	DUKPT��Կ����, 0��15
	@param[in]    Mode		-	MAC_MODE_1, MAC_MODE_EMV, MAC_MODE_CUP
	@param[in]    DataLen	-	���ڼ���mac�����ݳ���
	@param[in]    DataIn	-	���ڼ���mac������
	@param[out]   MacBlock	-	�����MACֵ���̶�Ϊ8�ֽ�
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ�����ڼ�����������������ݵ�MACֵ��
 @else
	@brief        Cacluate MAC of response data that receive from server. Calling this function will not increase the KSN.
	@param[in]    KeyIndex	-	index of key, 0 ~ 15
	@param[in]    Mode		-	MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP, MAC_MODE_DUKPT
	@param[in]    DataLen	-	length of DataIn in bytes
	@param[in]    DataIn	-	Data used to calculate mac
	@param[out]   MacBlock	-	Calculated MAC block, fixed to 8 bytes
	@retval       0         -   successful
	@retval		  other     -   failure, use errno to get detail 
    @note         This function is usually used to calculate the MAC value of the data sent from the server.
 @endif
*/
int ped_dukpt_calc_mac_response(uint32_t    KeyIndex,
                                uint32_t    Mode,
                                uint32_t    DataLen,
                                const void *DataIn,
                                void       *MacBlock);

/*!
 @if Chinese
	@brief        ��dukpt��Կ��֤�������������ݵ�MAC�����ñ�������������KSN.
	@param[in]    KeyIndex		-	DUKPT��Կ����, 0��15
	@param[in]    Mode			-	MAC_MODE_1, MAC_MODE_EMV, MAC_MODE_CUP
	@param[in]    DataLen		-	���ڼ���mac�����ݳ���
	@param[in]    DataIn		-	���ڼ���mac������
	@param[in]    MacBlock		-	��Ҫ��֤��MACֵ���̶�Ϊ8�ֽ�
	@retval       0        		-	�ɹ�
	@retval		  ����     		-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ��������֤���������������ݵ�MACֵ��  \n
				  �����ʹ�÷�������Ҫ�Ƚϵ��ֽڣ���������ΪFF������Ҫ�Ƚϵ��ֽ���������Ϊ00�� \n
				  �������ʹ�õ���Կ��ped_get_mac_unified(DUKPT_DES)��һ���ġ�
 @else
	@brief        Use the dukpt key to verify the MAC of the data sent by the server. Calling this function will not increase the KSN.
	@param[in]    KeyIndex		-	index of key, 0 ~ 15
	@param[in]    Mode			-	MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP, MAC_MODE_DUKPT
	@param[in]    DataLen		-	length of DataIn in bytes
	@param[in]    DataIn		-	Data used to calculate mac
	@param[in]    MacBlock		-	Calculated MAC block, fixed to 8 bytes
	@retval       0             -	successful
	@retval		  other        	-	failure, use errno to get detail 
    @note         This function is usually used to verify the MAC value of the data sent from the server. \n
				  How to use the mask: Bytes to be compared, the mask is set to FF; Bytes not to be compared, the mask is set to 00. \n
				  this function use the same key as ped_get_mac_unified(DUKPT_DES)
 @endif
*/
int ped_dukpt_verify_mac_response(uint32_t    KeyIndex,
                                  uint32_t    Mode,
                                  uint32_t    DataLen,
                                  const void *DataIn,
                                  const void *MacBlock);

/*!
 @if Chinese
	@brief        ����Կд�뵽������Կ���ܵ�PED��
	@param[in]    KeySystem			-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyType			-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[in]    Mode				-	У���㷨,�ο�: <a href="#ped_verify">verify algorithm</a> 
	@param[in]    MasterKeyIndex	-	����Կ����
	@param[in]    DestKeyIndex		-	Ŀ����Կ����
	@param[in]    KeyLen			-	��Կ����
	@param[in]    KeyData		0-ECC_P256_TYPE��Կ����
	@retval       0        		   	-	�ɹ�
	@retval		  ����    		   	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ���磬KeySystem��FIXED_DES��KeyType��KEY_TYPE_PINK����ԿӦ���ǡ�Fixed PIN Key��        \n 
				  KeySystem��MS_DES��FIXED_DES��MS_AES��FIXED_AES,��Ӧ��Mode��                         \n 
				  KEY_VERIFY_NONE��                                                                    \n 
				  KEY_VERIFY_KVC��                                                                     \n 
				  KEY_VERIFY_CMAC                                                                      \n 
				  KeySystem��MS_SM4��FIXED_SM4,��Ӧ��Mode��                                            \n 
				  KEY_VERIFY_NONE��                                                                    \n 
				  KEY_VERIFY_SM4_KVC                                                                   \n 
				  ע��aes��Կʱ��ֻ�в���KEY_VERIFY_CMACУ���֧��16��24��32�ֽ���Կ��KEY_VERIFY_NONE��KEY_VERIFY_KVCֻ֧��16��32�ֽ���Կ��
 @else
	@brief        Unified interface for injecting keys, and save in ped
	@param[in]    KeySystem			-	key system, reference: @ref KeySystem_t
	@param[in]    KeyType			-	key type, reference: <a href="#ped_key_type">key type</a> 
	@param[in]    Mode				-	verify mode: <a href="#ped_verify">verify algorithm</a> 
	@param[in]    MasterKeyIndex	-	index of master key
	@param[in]    DestKeyIndex		-	index of target key
	@param[in]    KeyLen			-	key length
	@param[in]    KeyData			-	key content
	@retval       0                	-	successful
	@retval		  other            	-	failure, use errno to get detail 
	@note         For example, KeySystem is FIXED_DES, KeyType is KEY_TYPE_PINK, and the key should be "Fixed PIN Key"        \n 
				  When KeySystem is MS_DES or FIXED_DES or MS_AES or FIXED_AES, the corresponding Mode is as follows:         \n 
				  KEY_VERIFY_NONE��                                                                                           \n 
				  KEY_VERIFY_KVC��                                                                                            \n 
				  KEY_VERIFY_CMAC                                                                                             \n 
				  When KeySystem is MS_SM4 or FIXED_SM4, the corresponding Mode is as follows:                                \n 
				  KEY_VERIFY_NONE��                                                                                           \n 
				  KEY_VERIFY_SM4_KVC                                                                                          \n 
				  When injecting an aes key, only when using the KEY_VERIFY_CMAC mode to verify the key, injection of 16, 24, and 32 byte keys is supported.  \n
				  KEY_VERIFY_NONE and KEY_VERIFY_KVC only support 16 and 32 byte keys.
 @endif
*/
int ped_write_key_unified(KeySystem_t KeySystem,
                          uint32_t    KeyType,
                          uint32_t    MasterKeyIndex,
                          uint32_t    DestKeyIndex,
                          uint32_t    Mode,
                          uint32_t    KeyLen,
                          const void *KeyData);

/*!
 @if Chinese
	@brief        �����û���PIN������������PIN�鷵�ظ�Ӧ�ó���
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyIndex		-	��Կ����
	@param[in]    Mode			-	����pin block�㷨,�ο�: <a href="#ped_pin_format">PIN BLOCK algorithm</a> 
	@param[in]    ExpectPinLen	-	��������PIN���ȵ�ö��ֵ�ַ���,��ʽ��[����<,����>],���ܴ���12.����, "0,6,7,8,12"
	@param[in]    CardNo		-	�ɴ�����16���ֽڣ�ǰ4���ֽ���Ч����ʹ�ú�12���ֽ�
	@param[in]    PinBlock		-	PIN BLOCK�����DES�̶�Ϊ8�ֽڣ�SM4��AES�̶�Ϊ16�ֽ�
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         PIN�����Ĭ�ϳ�ʱʱ����120�룬����ͨ�����ýӿ�ped_set_pin_input_timeout() ���ó�ʱʱ�䡣 \n 
				  PIN�����������з���2��PIN������̫�̵Ļ����ܻᱻ�ܾ��������õ���ped_get_sensitive_timer��ȡ��ǰ�Ƿ��������룬 \n 
				  �������ֵ����0��˵����Ҫ�ȴ�n������ֵ����������PIN���롣      
 @else
	@brief        input user's PIN and encrypted it, return pin block to app
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	Calculate the pin block algorithm, reference: <a href="#ped_pin_format">PIN BLOCK algorithm</a> 
	@param[in]    ExpectPinLen	-	list of expected length, format is [digit<,digit>], no more than 12. for example, "0,6,7,8,12"
	@param[in]    CardNo		-	processed card No, 16 bytes, first 4 bytes are invalid, just use last 12 bytes
	@param[in]    PinBlock		-	The PIN BLOCK result. Des is fixed to 8 bytes, sm4 and aes are fixed to 16 bytes.
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
	@note         The default timeout is 120 seconds. If you want to set the timeout value, please call the API ped_set_pin_input_timeout() to set.  \n
				  PIN input is sensitive service, if the time between two PIN input is too fast, the operation will be refused.       \n 
				  So you can call ped_get_sensitive_timer() to get current state, if the return value large than 0(etc n), it means only after n seconds, you can inpuit PIN again. 
 @endif
*/
int ped_get_pin_unified(KeySystem_t KeySystem,
                        uint32_t    KeyIndex,
                        uint32_t    Mode,
                        const char *ExpectPinLen,
                        const char *CardNo,
                        void       *PinBlock);


/*!
 @if Chinese
	@brief       �˳�����pin�ӿ�
	@retval      0			-	�ɹ�
	@retval		 ����    	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note        ���ڵ���pin����ӿ�ʹ��ʱ��Ч��
 @else
	@brief       Exit the pin input interface
	@retval      0			-	successful
	@retval		 other		-	failure, use errno to get detail 
	@note        Only effective when used in the pin input interface.\n
 @endif
 */
int ped_input_pin_exit(void);

/*!
 @if Chinese
	@brief        ��ȡic���Ĳ�ۺ�
	@param[in]    fd		-	IC���豸������, iccard_open_cardslot() �ķ���ֵ
	@param[out]   slotno	-	IC����ۺ�
	@retval       0        	-	�ɹ�
	@retval		  ����     	-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         �ù������ڻ�ȡic���Ĳ�ۺţ�ped_get_offline_pin() ������Ҫ��ۺ�     
 @else
	@brief        input user's PIN and encrypted it, return pin block to app
	@param[in]    fd		-	device description that return by call iccard_open_cardslot()
	@param[out]   slotno	-	current slot number
	@retval       0			-	successful
	@retval		  other		-	failure, use errno to get detail 
	@note         this function use to get slot number of ic card, slot number is need by function ped_get_offline_pin()
 @endif
*/
int ped_icc_get_slotno(int fd, uint32_t *slotno);

/*!
 @if Chinese
	@brief        ����PIN��������PIN BLOCK�͵�IC����Ȼ������Ӧ
	@param[in]    KeySystem		-	��Կ��ϵ, ����ȡֵICC_PLAIN��ICC_CIPHER, �ο�: @ref KeySystem_t 
	@param[in]    slotno		-	IC����ۺ�, ����ʹ�ú��� ped_icc_get_slotno() ���
	@param[in]    ExpectPinLen	-	��������PIN���ȵ�ö��ֵ�ַ���,��ʽ��[����<,����>],���ܴ���12.����, "0,6,7,8,12"
	@param[in]    icc			-	APDU��Ϣ, CLA��INS��P1��P2��LC
	@param[out]   rsplen		-	rspdata�ĳ��ȣ����ֽ�Ϊ��λ��
	@param[out]   rspdata		-	��IC���յ���Ӧ�����ݣ���ʽΪSWA + SWB
	@retval       0        		-	�ɹ�
	@retval		  ����     		-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ICC_PLAIN ��ʾ�ѻ�����PIN���������û���PIN
				  ICC_CIPHER ��ʾ�ѻ�����PIN��ʹ��RSA�����û���PIN
	
 @else
	@brief       input PIN and send offline pin block to IC card then get response
	@param[in]    KeySystem		-	key system, Can be ICC_PLAIN and ICC_CIPHER, reference: @ref KeySystem_t
	@param[in]    slotno		-	No. of IC card slot, user can use ped_icc_get_slotno() to got it
	@param[in]    ExpectPinLen	-	list of expected length, format is [digit<,digit>], no more than 12, for example, "0,6,7,8,12"
	@param[in]    icc			-	APDU information, CLA��INS��P1��P2��LC
	@param[out]   rsplen		-	length of rspdata in bytes
	@param[out]   rspdata		-	response data that received from IC card, format is SWA��SWB
	@retval       0             -	successful
	@retval		  other         -	failure, use errno to get detail 
	@note         ICC_PLAIN    - offline plaintext PIN, don't encrypt user's PIN         \n
	              ICC_CIPHER   - offline ciphertext PIN, use RSA to encrypt user's PIN
 @endif
*/
int ped_get_offline_pin(KeySystem_t                KeySystem,
                        uint32_t                   slotno,
                        const char                *ExpectPinLen,
                        const IccOfflinePinApdu_t *icc,
                        uint32_t                  *rsplen,
                        void                      *rspdata);

/*!
 @if Chinese
	@brief        �����������ݵ�MACֵ
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyIndex		-	MAC��Կ������
	@param[in]    Mode			-	�����㷨: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	DataIn�ĳ��ȣ�8/16/24/32/40/48...
	@param[in]    DataIn		-	MAC�����������ݣ����ڼ���MACֵ
	@param[out]   MacBlock		-	MAC������, Des�̶�Ϊ8�ֽ�, sm4��aes�̶�Ϊ16�ֽ�
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         MAC_MODE_CUP_8��MAC_MODE_1_8ֻ��MS_DES��FIXED_DES��DUKPT_DES֧�֡�
 @else
	@brief        calculate MAC block of data
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	Calculation algorithm: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	length of DataIn��8/16/24/32/40/48...
	@param[in]    DataIn		-	input data will be computed the MAC block
	@param[out]   MacBlock		-	The MAC block result, Des is fixed to 8 bytes, sm4 and aes are fixed to 16 bytes.
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
	@note         MAC_MODE_CUP_8 and MAC_MODE_1_8 are supported only by MS_DES, FIXED_DES, and DUKPT_DES.
 @endif
*/
int ped_get_mac_unified(KeySystem_t KeySystem,
                        uint32_t    KeyIndex,
                        uint32_t    Mode,
                        uint32_t    DataLen,
                        const void *DataIn,
                        void       *MacBlock);

/*!
 @if Chinese
	@brief        �ʻ����ݼ���
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyIndex		-	�˺���Կ������
	@param[in]    Mode			-	�����㷨: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	DataIn�ĳ��ȣ�������8�ı���
	@param[in]    DataIn		-	�������ڼ��ܵ�����
	@param[out]   DataOut		-	�������ڼ��ܺ����������
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         �������ֻ֧��KEY_TYPE_EAK���͵���Կʹ��des�㷨��������
 @else
	@brief        Account data encryption
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	only support @ref TDEA_ENCRYPT
	@param[in]    DataLen		-	The length of DataIn , must be a multiple of 8.
	@param[in]    DataIn		-	point buffer to be encrypted
	@param[out]   DataOut		-	point buffer to save ciphertext data
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
	@note         this function use KEY_TYPE_EAK encrypt data by DES
 @endif
*/
int ped_get_account(KeySystem_t KeySystem,
                    uint32_t    KeyIndex,
                    uint32_t    Mode,
                    uint32_t    DataLen,
                    const void *DataIn,
                    void       *DataOut);

/*!
 @if Chinese
	@brief        ע��������Կ
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    KeyLen		-	������Կ�ĳ��� 
	@param[in]    Key			-	������Կ������
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         �������֧�ֵ���Կ���ͣ�KEY_TYPE_MASTK,KEY_TYPE_FIXPINK,KEY_TYPE_FIXMACK,KEY_TYPE_FIXEAK
 @else
	@brief        Account data encryption
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	index of key
	@param[in]    KeyLen		-	length of key 
	@param[in]    Key			-	Content of the plaintext key
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
	@note         Key types supported by this function:KEY_TYPE_MASTK,KEY_TYPE_FIXPINK,KEY_TYPE_FIXMACK,KEY_TYPE_FIXEAK
 @endif
*/
int ped_inject_key(KeySystem_t KeySystem,
                   uint32_t    KeyType,
                   uint32_t    KeyIndex,
                   uint32_t    KeyLen,
                   const void *Key);

#if 0
/**
 * @brief       inject key by privilege application, normal APP will be refused
 * @param[in]   KeySystem	-	MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param[in]   KeyType		-	KEY_TYPE_MASTK, KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param[in]   KeyIndex	-	index of key
 * @param[in]   CUID		-	CID and UID
 * @param[in]   KeyLen		-	length of PlaintextKey in bytes
 * @param[in]   PlaintextKey	-	plaintext key
 * @return      0    		- success <br>
 *              other 		- failure, use errno to get detail
 * @note        KEY_TYPE_EAK only MS_DES can supported
 */
int ped_root_inject_key(KeySystem_t KeySystem,
                        uint32_t    KeyType,
                        uint32_t    KeyIndex,
                        uint32_t    CUID,
                        uint32_t    KeyLen,
                        const void *PlaintextKey);
#endif //�ڲ��ӿڣ�������

/*!
 @if Chinese
	@brief        ���ָ����Կ�Ƿ����
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    Mode			-	��ʱ��ʹ�ã���Ϊ0
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        check specified key exist or not
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	not used for the moment, set to 0
	@retval       0             -  	successful
	@retval		  other         -   failure, use errno to get detail 
 @endif
*/
int ped_check_key_unified(KeySystem_t KeySystem,
                          uint32_t    KeyType,
                          uint32_t    KeyIndex,
                          uint32_t    Mode);

#if 1 //����ӿ�Ҫ����
/*!
 @if Chinese
	@brief        ͨ���Գ���Կ����/��������
	@param[in]    Mode		-	�ӽ����㷨,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							�ο�:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV		-	IV
	@param[in]    KeyLen	-	��Կ����
	@param[in]    Key		-	���ڼӽ��ܵ���Կ
	@param[in]    DataLen	-	���ݳ��ȣ�DES������8�ı�����SM4��AES������16�ı���
	@param[in]    DataIn	-	���ڼӽ��ܵ�����
	@param[out]   DataOut	-	�ӽ��ܺ�Ľ��
	@retval       0        	-	   �ɹ�
	@retval		  ����     	-	   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        Encrypt/decrypt data with a symmetric key
	@param[in]    Mode		-	Encryption and decryption algorithm,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							reference:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV		-	IV
	@param[in]    KeyLen	-	Length of key
	@param[in]    Key		-	Key used for encryption or decryption
	@param[in]    DataLen	-	Length of data, DES must be a multiple of 8, SM4 and AES must be a multiple of 16
	@param[in]    DataIn	-	Data to be encrypted or decrypted
	@param[out]   DataOut	-	Encrypted or decrypted result
	@retval       0         -	successful
	@retval		  other     -	failure, use errno to get detail 
 @endif
*/
int ped_symmetric_crypto(uint32_t Mode,    uint8_t IV[],
                         uint32_t KeyLen,  const void *Key,
                         uint32_t DataLen, const void *DataIn, void *DataOut);
#endif

/*!
 @if Chinese
	@brief        ʹ�ñ�����ped�������Կ���м���
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	��Կ����	
	@param[in]    Mode			-	�����㷨,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							       �ο�:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV			-	IV
	@param[in]    DataLen		-	DataIn�����ݳ��ȣ�DES������8�ı�����SM4��AES������16�ı���
	@param[in]    DataIn		-	���ڼ��ܵ�����
	@param[out]   OutLen		-	DataOut���ݳ���
	@param[out]   DataOut		-	���ܺ�Ľ��
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        Encrypt data using the key saved on ped.
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a>
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	Encryption algorithm,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							       reference:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV			-	IV
	@param[in]    DataLen		-	Length of DataIn, DES must be a multiple of 8, SM4 and AES must be a multiple of 16
	@param[in]    DataIn		-	Data to be encrypted 
	@param[out]   OutLen		-	The address of the length of the output data
	@param[out]   DataOut		-	Encrypted result
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
 @endif
*/
int ped_crypto_unified(KeySystem_t KeySystem,
                       uint32_t    KeyType,
                       uint32_t    KeyIndex,
                       uint32_t    Mode,
                       uint8_t     IV[],
                       uint32_t    DataLen,
                       const void *DataIn,
                       uint32_t   *OutLen,
                       void       *DataOut);

/*!
 @if Chinese
	@brief        ��ȡ������Կkvc
	@param[in]    KeySystem		-	��Կ��ϵ,�ο�: @ref KeySystem_t
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    KVC			-	KVC����
	@retval       0        		-   �ɹ�
	@retval		  ����     		-   ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        get work key kvc
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	index of key
	@param[out]   KVC			-	kvc content
	@retval       0             -   successful
	@retval		  other         -   failure, use errno to get detail 
 @endif
*/
int ped_get_key_kvc(KeySystem_t KeySystem, uint32_t KeyType, uint32_t KeyIndex, uint8_t KVC[4]);

/*!
 @if Chinese
	@brief        ʹ����ped�����RSA˽Կ����RSA block
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    input			-	���ڼ���RSA block��ԭʼ���� 
	@param[in]    inputLen		-	input���ݳ���
	@param[out]   output		-	���ڱ�����������RSA block
	@param[in]    outputLen		-	output����������
	@param[out]   outputLen		-	ʵ����������ݳ��� 
	@retval       0				-	�ɹ�
	@retval		  ���� 			-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        rsa private operation
	@param[in]    KeyIndex		-	index of key
	@param[in]    input			-	point buffer to be operated 
	@param[in]    inputLen		-	length of input
	@param[out]   output		-	point buffer to save operated data
	@param[in]    outputLen		-	size of output buffer
	@param[out]   outputLen		-	length of real output data 
	@retval       0				-	successful
	@retval		  other			-	failure, use errno to get detail 
 @endif
*/
int ped_rsa_private_operation(uint32_t    KeyIndex,
                              void       *output,
                              uint32_t   *outputLen,
                              const void *input,
                              uint32_t    inputLen);

/*!
 @if Chinese
	@brief        ����rsa��Կ
	@param[in]    KeyIndex		-	��Կ������
	@param[out]   PubKey		-	���ڱ��湫Կ����
	@param[in]    KeyLen		-	PubKey����������
	@param[out]   KeyLen		-	ʵ����������ݳ��� 
	@retval       0				-	�ɹ�
	@retval		  ���� 			-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        export rsa public key
	@param[in]    KeyIndex		-	index of key
	@param[out]   PubKey		-	point buffer to save public key data
	@param[in]    KeyLen		-	buffer size to save pubkey
	@param[out]   KeyLen		-	length of real output data 
	@retval       0				-	successful
	@retval		  other			-	failure, use errno to get detail 
 @endif
*/
int ped_rsa_export_pub_key(uint32_t    KeyIndex,
                           void       *PubKey,
                           uint32_t   *KeyLen);
 /*!
 @if Chinese
	@brief        ����rsa֤��
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a> 
	@param[out]   pubCert		-	���ڱ����ȡ����֤������
	@param[in]    CertLen		-	output����������
	@param[out]   CertLen		-	��ȡ����֤�����ݳ���
	@retval       0				-	�ɹ�
	@retval		  ���� 			-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        export rsa public cert
	@param[in]    KeyIndex		-	index of key
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a> 
	@param[out]   pubCert		-	point buffer to cert exported
	@param[in]    CertLen		-	buffer size to save pubkey
	@param[out]   CertLen		-	length of real output data
	@retval       0				-	successful
	@retval		  other			-	failure, use errno to get detail 
 @endif
*/
int ped_get_rsa_pub_cert(uint32_t KeyIndex, uint32_t KeyType,
                         void *pubCert, uint32_t *CertLen);

 /*!
 @if Chinese
	@brief        ע��rsa����֤��
	@param[in]    KeyIndex		-	��Կ������
	@param[in]    CUID			-	�Զ���id���û�id 
	@param[in]    KeyType		-	��Կ����,�ο�: <a href="#ped_key_type">key type</a>
	@param[in]    input			-	֤������
	@param[in]    inputLen		-	Input���ݳ���
	@retval       0				-	�ɹ�
	@retval		  ���� 			-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        save rsa public cert
	@param[in]    KeyIndex		-	index of key
	@param[in]    CUID			-	custom id and user id
	@param[in]    KeyType		-	key type, reference: <a href="#ped_key_type">key type</a>
	@param[in]    input			-	point buffer to cert saved
	@param[in]    inputLen		-	buffer size to save pubkey
	@retval       0				-	successful
	@retval		  other			-	failure, use errno to get detail 
 @endif
*/
int ped_inject_rsa_pub_cert(uint32_t KeyIndex,
                            uint32_t CUID,
                            uint32_t KeyType,
                            const void *input,
                            uint32_t inputLen);

/**
 @if Chinese
  * @brief      Ӳ������rsa��Կ.
  * @param[in]  bits		-	RSA���֧��2048
  * @param[in]  exponent	-	rsaָ�� 65537
  * @param[out] PriKey		-	���rsa˽Կ
  * @retval      0 			-	�ɹ�
  * @retval      ���� 		-	ʧ��
@else
  * @brief      generate rsa key by hardware.
  * @param[in]  bits		-	rsa can support 2048 bits
  * @param[in]  exponent	-	rsa exponent is 65537
  * @param[out] PriKey		-	output rsa private key
  * @retval     0			-	successfull
  * @retval     other		-	failure
@endif
  */
int ped_rsa_genkey(uint32_t bits, uint32_t exponent, RsaPrivateKey_t *PriKey);

/**
 @if Chinese
 * @brief          RSA��Կ����.
 * @param[out]     output		-	����ַ���ָ��
 * @param[in]      outputlen    -	[in]  �����ַ�Ԥ������
 * @param[out]     outputlen    -	[out] �����ַ�����
 * @param[in]      input        -	�����ַ���ָ��
 * @param[in]      inputlen     -	�����ַ�����
 * @param[in]      public_key   -	RSA��Կ
 * @retval     	   0   			-	�ɹ�
 * @retval     	   ���� 		-	ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief          rsa public block calculation by hardware.
 * @param[out]     output       -	point buffer to save operated data
 * @param[in]      outputlen    -	[in]  size of output buffer
 * @param[out]     outputlen    -	[out] length of real output data
 * @param[in]      input        -	point buffer to be operated
 * @param[in]      inputlen     -	length of input
 * @param[in]      public_key   -	the rsa public key
 * @retval     0				-	success
 * @retval     other			-	failure, use errno to get detail
@endif
 */
int ped_rsa_public_block(void *output,
                         uint32_t *outputlen,
                         const void *input,
                         uint32_t inputlen,
                         const RsaPublicKey_t *public_key);

/*!
 @if Chinese
 * @brief          RSA˽Կ����.
 * @param[out]     output       -	����ַ���ָ��
 * @param[in]      outputlen    -	[in]  ����ַ���ָ��
 * @param[out]     outputlen    -	[out] �����ַ��ĳ���
 * @param[in]      input        -	�����ַ���ָ��
 * @param[in]      inputlen     -	�����ַ���ָ��
 * @param[in]      private_key  -	RSA˽Կ
 * @retval      0    - �ɹ�
 * @retval      ���� - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief          rsa private block calculation by hardware.
 * @param[out]     output       -	point buffer to save operated data
 * @param[in]      outputlen    -	[in]  size of output buffer
 * @param[out]     outputlen    -	[out] length of real output data
 * @param[in]      input        -	point buffer to be operated
 * @param[in]      inputlen     -	length of input
 * @param[in]      private_key  -	the rsa private key
 * @retval      0    - success
 * @retval      other - failure, use errno to get detail 
@endif
 */
int ped_rsa_private_block(void *output,
                          uint32_t *outputlen,
                          const void *input,
                          uint32_t inputlen,
                          const RsaPrivateKey_t *private_key);

/*!
@if Chinese
 * @brief           Ӳ��ʹ��rsa˽Կ����Ϣ����ǩ��
 * @param[in]       type	- ǩ���Ĺ�ϣ���͡�����@ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	�������ݵ�ָ��
 * @param[in]       m_len	-	�������ݵĳ���
 * @param[out]      sigret	-	ǩ������
 * @param[in]       siglen	-	ǩ�����ݵĳ���,
 *                            [in] ����pResult�Ļ�������С�������ǹؼ�ģ��ĳ���
 * @param[out]      siglen	-	ǩ�����ݵĳ��ȣ�[out]ʵ�����sigret�ĳ���
 * @param[in]       private_key	-	rsa˽Կ������
 * @retval     0 - �ɹ�
 * @retval     ���� - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief           sign message using rsa private key by hardware
 * @param[in]       type	-	the hash type of signature. see @ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	the point of message
 * @param[in]       m_len	-	the message length
 * @param[out]      sigret	-	the signature data
 * @param[in]       siglen	-	the length of signature data,
 *                            [in] buffer size to save pResult, at least the length of modules of key
 * @param[out]      siglen	-	the length of signature data, [out] length of real output sigret
 * @param[in]       private_key	-	the buffer of rsa private key
 * @retval     0 - successfull
 * @retval      other - failure
 @endif
 */
int ped_rsa_sign(int type, const unsigned char *m, unsigned int m_len,
                 unsigned char *sigret, unsigned int *siglen, RsaPrivateKey_t *private_key);

/*!
 @if Chinese
 * @brief           Ӳ��ʹ��rsa��Կ��֤ǩ��
 * @param[in]       type	-	ǩ���Ĺ�ϣ���͡��ο�@ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	��Ϣ����ָ��
 * @param[in]       m_len	-	��Ϣ���ݳ���
 * @param[in]       sigbuf	-	ǩ������
 * @param[in]       siglen	-	ǩ�����ݵĳ���
 * @param[in]       public_key	-	rsa��Կ������
 * @retval      0 		- �ɹ�
 * @retval      ���� 	- ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
@else 
 * @brief           verify signature using rsa public key by hardware
 * @param[in]       type	-	the hash type of signature. see @ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	the point of message
 * @param[in]       m_len	-	the message length
 * @param[in]       sigbuf	-	the signature data
 * @param[in]       siglen	-	the length of signature data
 * @param[in]       public_key	-	the buffer of rsa public key
 * @return      0 		- verify ok
 * @return      other 	- failure
@endif
 */
int ped_rsa_verify(int type, const unsigned char *m, unsigned int m_len,
                   unsigned char *sigbuf, unsigned int siglen, RsaPublicKey_t *public_key);

/*!
 @if Chinese
	@brief        ���㣨Ӳ�����к�+����������ӣ���MACֵ
	@param[in]    factor		-	����������ӣ�MAC�����������ݣ����ڼ���MACֵ
	@param[in]    factorLen		-	����ļ�������������ݳ��ȣ�һ��6�ֽ�
	@param[out]   macOut		-	MAC������������8�ֽ�
	@retval       0        		-	�ɹ�
	@retval		  ����     		-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
 @else
	@brief        Calculate the MAC value of the (serial number + encrypted random factor).
	@param[in]    factor		-	The encryption random factor, is used to calculate the MAC value.
	@param[in]    factorLen		-	Encrypted random factor data length, generally 6 bytes.
	@param[out]   macOut		-	The MAC result, 8 bytes.
	@retval       0            	-	successful
	@retval		  other        	-	failure, use errno to get detail 
 @endif
*/
int ped_get_mac_sm4_ans(const void *factor, uint32_t factorLen, void *macOut);

/*!
 @if Chinese
 * @brief        ����һ��AES DUKPT��Կ�����浽PED
 * @param[in]    KeyIndex		-	��Կ��������0 ~ 15
 * @param[in]    Dukpttype		-	2:_AES128_,3:_AES192_,4:_AES256_.
 * @param[in]    InitKey        -	��ʼ������Կ��16�ֽڣ�24�ֽڣ�32�ֽ�.
 * @param[in]    KeyLen         -	key len��Ĭ��Ϊ_AES128_:16�� _AES192_:24�� _AES256_:32
 * @param[in]    Ksn            -	KSN 12�ֽ�.
 * @retval      0 - �ɹ�   
 * @retval      ���� -ʧ��
@else 
 * @brief        create a AES DUKPT key and save to PED
 * @param[in]    KeyIndex       -	index of key, 0 ~ 15
 * @param[in]    Dukpttype      -	2:_AES128_,3:_AES192_,4:_AES256_.
 * @param[in]    InitKey        -	initialized key, 16 bytes, 24bytes, 32 bytes.
 * @param[in]    KeyLen         -	key len, default is _AES128_:16, _AES192_:24, _AES256_:32
 * @param[in]    Ksn            -	KSN, 12 bytes.
 * @retval      0 - successfull   
 * @retval      other - failure
@endif
 */ 
int ped_create_dukpt_aes_key(uint32_t    KeyIndex,
                             uint32_t    Dukpttype,
                             const void *InitKey,
                             uint32_t    KeyLen,
                             const void *Ksn);

/*!
 @if Chinese
 * @brief        �������DUKPT��Կ��KSN, KSN������
 * @param[in]    KeyIndex		-	��Կ������0 ~ 15
 * @param[out]   Ksn			-	KSN 12�ֽ�.
 * @retval	   	0 		- �ɹ�	 
 * @retval   	���� 	-ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
 * @note        ������һ�ο�������������PIN�ͻ��macһ�ε���.
@else 
 * @brief        update KSN of this DUKPT Key, KSN will increased
 * @param[in]    KeyIndex		-	index of key, 0 ~ 15
 * @param[out]   Ksn			-	KSN, 12 bytes.
 * @retval	   0 		- successful	 
 * @retval	   other 	- failed
 * @note      call it once can allow you enter PIN and get mac one time individually.
@endif 
 */ 
int ped_dukpt_aes_renew(uint32_t KeyIndex, void *Ksn);

/**
@if Chinese
 * @brief        ��ȡ���DUKPT��Կ��KSN, KSN������
 * @param[in]    KeyIndex		-	��Կ������0 ~ 15
 * @param[out]   Ksn			-	KSN 12�ֽ�.
 * @retval      0 		- �ɹ�   
 * @retval      ���� 	- ʧ��
 * @note        ���PIN�鱻�������λ�MAC�鱻�������Σ�KSN���ڵڶ��κ���ʱ�Զ����ӡ�\ n
 *				���Եõ���KSNֻ�ܱ�֤PIN��MAC����һ�Σ�����ı䡣
@else
 
 * @brief        get KSN of this DUKPT Key, KSN will increased
 * @param[in]    KeyIndex		-	index of key, 0 ~ 15
 * @param[out]   Ksn			-	KSN, 12 bytes.
 * @retval      0 - successfull   
 * @retval      other - failure
 * @note         If the PIN block is calculated twice or the MAC block is calculated twice, the KSN will be automatically increased when the second call is made. \n 
 * 				  so the obtained KSN can only guarantee that the PIN and MAC are calculated once and will not change.
@endif 
 */
int ped_get_dukpt_aes_ksn(uint32_t KeyIndex, void *Ksn);


/*!
 @if Chinese
	@brief        ��dukpt aes��Կ�����������ݣ����ñ�������������KSN.
	@param[in]    KeyIndex		-	DUKPT��Կ����, 0��15
	@param[in]    Mode		-	DUKPTKeyType��ö�����ͻ�KeyUsage��ö������(_2TDEA_ << 24 | _Key_Encryption_Key_) 
                                 ��֧�� _PIN_Encryption_, _Data_Encryption_decrypt_
	@param[in]    DataLen		-	Ҫ�������ݳ��ȣ�����Ϊ16�ı���
	@param[in]    DataIn		-	Ҫ���ܵ�����
	@param[out]   DataOut		-	������ܺ�Ľ�����䳤�����������ݳ���һ��
	@retval       0        		-	�ɹ�
	@retval		  ����     		-	ʧ��, ������ο�:<a href="#ped_errno">Errno</a>
	@note         ������ͨ�����ڼ������ݷ�����������
 @else
	@brief        Use dukpt key to encrypt request data. Calling this function will not increase KSN.
	@param[in]    KeyIndex		-	index of key, 0 ~ 15
	@param[in]    Mode			-	type of enum DUKPTKeyType and mode of enum KeyUsage(_2TDEA_ << 24 | _Key_Encryption_Key_) 
                                 unsupport _PIN_Encryption_, _Data_Encryption_decrypt_
	@param[in]    DataLen		-	length of DataIn in 16 bytes
	@param[in]    DataIn		-	plaintext data
	@param[out]   DataOut		-	ciphertext data
	@retval       0             -	successful
	@retval		  other         -	failure, use errno to get detail 
    @note         This function is usually used to send encrypted data to the server.
 @endif
*/
int ped_dukpt_aes_encrypt_request(uint32_t    KeyIndex,
                                  uint32_t    Mode,
                                  uint32_t    DataLen,
                                  const void *DataIn,
                                  void       *DataOut);

/**
@if Chinese
 * @brief        dukpt aes��Կ���ڽ�����Ӧ���ݡ��������������������KSN��.
 * @param[in]    KeyIndex		-	��Կ����, 0 ~ 15
 * @param[in]    Mode			-	����ΪDUKPTKeyType��ģʽΪKeyUsage(_2TDEA_ << 24 | _Key_Encryption_Key_) 
 *                              ��֧�� _PIN_Encryption_, _Data_Encryption_encrypt_
 * @param[in]    DataLen		-	DataIn�ĳ��ȣ�16�ֽ�
 * @param[in]    DataIn			-	��������
 * @param[out]   DataOut		-	��������
 * @retval       0 - �ɹ�
 * @retval       ���� - ʧ��
 * @note         �ù���ͨ�����ڶԷ��������͵��������ݽ��н���.
@else 
 * @brief        The dukpt aes key is used to decrypt the response data. Calling this function will not increase the KSN.
 * @param[in]    KeyIndex		-	index of key, 0 ~ 15
 * @param[in]    Mode			-	type of enum DUKPTKeyType and mode of enum KeyUsage(_2TDEA_ << 24 | _Key_Encryption_Key_) 
 *                              unsupport _PIN_Encryption_, _Data_Encryption_encrypt_
 * @param[in]    DataLen		-	length of DataIn in 16 bytes
 * @param[in]    DataIn			-	ciphertext data
 * @param[out]   DataOut		-	plaintext data
 * @retval       0 				- successfull
 * @retval       other 			- failure
 * @note         This function is usually used to decrypt the ciphertext data sent by the server.
@endif 
 */
int ped_dukpt_aes_decrypt_request(uint32_t    KeyIndex,
                                   uint32_t    Mode,
                                   uint32_t    DataLen,
                                   const void *DataIn,
                                   void       *DataOut);


/**
@if Chinese
 * @brief        ����ecc��Կ��.
 * @param[in]    EccType	
 *					- 0-ECC_P256_TYPE
 *                  - 1-ECC_P521_TYPE
 * @param[in]    Para		-	ECC����
 * @param[out]   PriKey		-	������˽Կ
 * @param[out]   PubKey		-	�����Ĺ�Կ
 * @retval       0 			- �ɹ�
 * @retval       ���� 		- ʧ��
@else 
 * @brief        generate ecc key pair.
 * @param[in]    EccType
 * 					- 0-ECC_P256_TYPE
 *                  - 1-ECC_P521_TYPE
 * @param[in]    Para		-	Elliptic Curve parameters
 * @param[out]   PriKey		-	output private key
 * @param[out]   PubKey		-	output public key
 * @retval       0 			- successfull
 * @retval       other 		- failure
@endif      
 */
int ped_ecc_genkey(ECC_PriKey_t *PriKey, ECC_PubKey_t *PubKey, ECC_STU_PRAMS *Para, int EccType);

/**
@if Chinese
 * @brief         ʹ��ecc��Կ��������
 * @param[in]     PubKey	-	��Կ
 * @param[in]     Para		-	ECC����
 * @param[in]     InLen		-	�������ݵĳ���
 * @param[in]     DataIn	-	��������
 * @param[out]    OutLen	-	������ݵĳ���
 * @param[out]    DataOut	-	�������
 * @retval        0 		- �ɹ�
 * @retval        ���� 		- ʧ��
@else 
 * @brief         encrypt data using ecc public key
 * @param[in]      PubKey	-	 public key
 * @param[in]      Para		-	Elliptic Curve parameters
 * @param[in]      InLen	-	length of DataIn
 * @param[in]      DataIn	-	data to be encrypted
 * @param[out]     OutLen	-	length of ciphertext
 * @param[out]    DataOut	-	ciphertext
 * @retval        0 		- successfull
 * @retval        other 	- failure
@endif     
 */
int ped_ecc_pubkey_encrypt(const ECC_PubKey_t *PubKey, ECC_STU_PRAMS *Para, 
                                     uint32_t InLen,   const void *DataIn,
                                     uint32_t *OutLen, void *DataOut);

/**
@if Chinese
 * @brief         ʹ��ecc˽Կ��������
 * @param[in]     PriKey	-	˽Կ
 * @param[in]     Para		-	ecc����
 * @param[in]     InLen		-	DataIn����
 * @param[in]     DataIn	-	��Ҫ���ܵ�����
 * @param[out]    OutLen	-	���ĵĳ��ȣ�ͨ������InLen - 96
 * @param[out]    DataOut	-	��������
 * @retval        0 		- �ɹ�
 * @retval        ���� 		- ʧ��
@else 
 * @brief         decrypt data using ecc private key
 * @param[in]     PriKey	-	private key
 * @param[in]     Para		-	 Elliptic Curve parameters
 * @param[in]     InLen		-	length of DataIn
 * @param[in]     DataIn	-	data to be decrypted
 * @param[out]    OutLen	-	length of plaintext, normally it equal InLen - 96
 * @param[out]    DataOut	-	plaintext
 * @retval        0 		- successfull
 * @retval        other 	- failure
@endif       
 */
int ped_ecc_prikey_decrypt(const ECC_PriKey_t *PriKey, ECC_STU_PRAMS *Para,
                                     uint32_t InLen,    const void *DataIn,
                                     uint32_t *OutLen, void *DataOut);

/**
 @if Chinese
* @brief        ʹ��ECC˽Կ����Ϣ����ǩ��
* @param[in]     mes		-	 ����ǩ������Ϣ
* @param[in]     mLen		-	ǩ����Ϣ�ĳ��� 
* @param[in]     hashMode	-	��ϣ���㷽��
* @param[in]     priKey		-	˽Կ
* @param[in]     para		-	ecdsa����
* @param[out]    pSignR		-	ǩ�����R 
* @param[out]    pSignS		-	ǩ�����S
* @retval        0 			- �ɹ�
* @retval        ���� 		- ʧ��
@else
* @brief         Use ECC private key to sign message 
* @param[in]      mes		-	message used for signature 
* @param[in]      mLen		-	The length of the signed message 
* @param[in]      hashMode	-	Hash calculation method 
* @param[in]      priKey	-	Private key
* @param[in]      para		-	Elliptic Curve parameters
* @param[out]     pSignR	-	Signature result R 
* @param[out]     pSignS	-	Signature result S
* @retval        0 			- successfull
* @retval        other 		- failure
@endif     
*/
int ped_ecdsa_sign(unsigned char *mes, unsigned short mLen, unsigned char hashMode,
                         const ECC_PriKey_t *priKey, ECC_STU_BIGINT32 *pSignR, 
                         ECC_STU_BIGINT32 *pSignS, ECC_STU_PRAMS *para);

/*!
@if Chinese
	* @brief         ʹ��ECC��Կ��֤ǩ��
	* @param[in]     mes		-	����ǩ������Ϣ 
	* @param[in]     mLen		-	ǩ����Ϣ�ĳ���
	* @param[in]     hashMode	-	��ϣ���㷽�� 
	* @param[in]     pubKey		-	��Կ
	* @param[in]     para		-	ecdsa����
	* @param[out]    pSignR		-	ǩ�����R 
	* @param[out]    pSignS		-	ǩ�����S
	* @retval        0 			- �ɹ�
	* @retval        ���� 		- ʧ��
@else
	* @brief         Use ECC public key to verify signature 
	* @param[in]     mes		-	message used for signature 
	* @param[in]     mLen		-	The length of the signed message 
	* @param[in]     hashMode	-	Hash calculation method 
	* @param[in]     pubKey		-	Public key
	* @param[in]     para		-	Elliptic Curve parameters
	* @param[out]    pSignR		-	Signature result R 
	* @param[out]    pSignS		-	Signature result S
	* @retval        0 			- successfull
	* @retval        other 		- failure
@endif       
*/
int ped_ecdsa_verify(unsigned char *mes, unsigned short mLen, unsigned char hashMode,
                            const ECC_PubKey_t *pubKey, ECC_STU_BIGINT32 *pSignR,
                            ECC_STU_BIGINT32 *pSignS, ECC_STU_PRAMS *para);


#if 0
/**
 * @brief       inject plaintext ans-key by privilege application
 * @param[in]   AnsKeyLen	-	length of ANS-Key in bytes
 * @param[in]   AnsKey		-	ANS-Key content
 * @return      0    		- success
 *              other 		- failure, use errno to get detail
 * @note        The caller must be a privilege application, or it will return fail
 */
int ped_inject_ans_key(uint32_t AnsKeyLen, const void *AnsKey);
#endif //�ڲ��ӿڣ�������

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PED_H__ */

/** @} */

