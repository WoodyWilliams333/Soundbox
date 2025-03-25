
/**
@if Chinese
 * @brief       此模块用于描述 <strong>PED模块</strong> 相关的接口
 * @note        用户调用PED接口时，需要包含本文件
 * @date        2018/10/30
 * @version     1.0.1
 * @remarks
 *              Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2018/10/30    |  Milton.Wu      | Create file
 * 2022/04/20    | Wenming         | 增加英文注释
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
 * @brief 密钥体系定义
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
 * @brief   DUKPT AES可派生的可能的密钥用法
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
 * @brief   DUKPT AES派生的加密密钥类型
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
 * @brief PED 状态定义: 锁定，正常，过期
@else 
 * @brief PED Status definition: locked, normal, expired
@endif
 */
typedef enum {
    PED_STATUS_LOCK         =   0,                      /**<@if Chinese PED 锁定状态，机器被攻击了     @else PED locked. Machine has been attacked 	@endif*/
    PED_STATUS_NORMAL,                                  /**<@if Chinese PED 正常状态                   @else PED normal state 						@endif*/
    PED_STATUS_EXPIRED,                                 /**<@if Chinese PED 过期状态                   @else PED expired status 					@endif*/
} PedStatus_t;

/**
@if Chinese
 * @name 敏感服务间隙定义
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
 * @name 加解密算法定义，用0~7位表示
@else 
 * @name Encryption and decryption algorithm definition, represented by 0 to 7 bits
@endif
 * @{
 */
#define TDEA_DECRYPT            0x00000000              /**<@if Chinese TDES解密                       @else TDES decode 									@endif*/
#define TDEA_ENCRYPT            0x00000001              /**<@if Chinese TDES加密                       @else TDES encrypt  									@endif*/
#define TDEA_NONE               0x00000002              /**<@if Chinese 不做加解密操作(给ped的api使用) @else No encryption or decryption (for ped API use) 	@endif*/
#define SM4_DECRYPT             0x00000010              /**<@if Chinese SM4解密                        @else SM4 decode  									@endif*/
#define SM4_ENCRYPT             0x00000011              /**<@if Chinese SM4加密                        @else SM4 encrypt 									@endif*/
#define SM4_NONE                0x00000012              /**<@if Chinese 不做加解密操作(给ped的api使用) @else No encryption or decryption (for ped API use) 	@endif*/
#define AES_DECRYPT             0x00000020              /**<@if Chinese AES解密                        @else AES decode  									@endif*/
#define AES_ENCRYPT             0x00000021              /**<@if Chinese AES加密                        @else AES encrypt 									@endif*/
#define AES_NONE                0x00000022              /**<@if Chinese 不做加解密操作(给ped的api使用) @else No encryption or decryption (for ped API use) 	@endif*/
/** @} */

/**
@if Chinese
 * @name 加解密模式定义，用8~15位表示
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
 * @name 校验算法，用24~31位表示
@else 
 * @name Check algorithm, represented by 24 to 31 bits
@endif 
 * @{
 */
#define KEY_VERIFY_NONE         0x00000000              /**<@if Chinese 无校验                 @else no parity 		@endif*/
#define KEY_VERIFY_KVC          0x01000000              /**<@if Chinese KVC use DES            @else KVC use DES  	@endif*/
#define KEY_VERIFY_CMAC         0x02000000              /**<@if Chinese CMAC                   @else CMAC 			@endif*/
#define KEY_VERIFY_SM4_KVC      0x11000000              /**<@if Chinese KVC use SM4            @else KVC use SM4  	@endif*/
#define KEY_VERIFY_MASK         0xff000000              /**<@if Chinese 掩码                   @else mask  			@endif*/
/** @} */

/**
@if Chinese
 * @name PIN BLOCK 算法定义
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
 * @name MAC BLOCK 算法定义
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
 * @name 密钥类型
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
 * @name 返回值定义
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
 * @name RSA 模位数
@else 
 * @name RSA modular digit
@endif 
 * @{
 */
#define MIN_RSA_BITS            2048                    /**<@if Chinese RSA密钥位数的最小长度  @else	Minimum length of RSA key bits		@endif*/
#define MAX_RSA_BITS            4096                    /**<@if Chinese RSA密钥位数的最大长度  @else	Maximum length of the RSA key digit	@endif*/
/** @} */

/**
@if Chinese
 * @name ECC相关宏定义
@else  
 * @name ECC Related macro definitions
@endif 
 * @{
 */
#define ECC_BIGINT32_MAXLEN     18

#define ECC_P256_BITS           256
#define ECC_P521_BITS           544

#define ECC_P256_BYTES          (((ECC_P256_BITS + 31) >> 5) << 2)                      //四字节对齐后所用字节
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
 * @brief PED 配置信息定义
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
 * @brief RSA PIN key 定义
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
 * @brief IC卡脱机PIN的ADPU定义
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
 * @brief 签名哈希类型
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
 * @brief RSA 公钥结构
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
 * @brief RSA  私钥结构
@endif 
 */
typedef struct {  // 私钥结构
    uint32_t bits;                   /**< length in bits of modulus */
    uint8_t  modulus[256];           /**< modulus                   */
    uint8_t  publicExponent[4];      /**< public exponent           */
    uint8_t  exponent[256];          /**< private exponent          */
    uint8_t  prime[2][128];          /**< prime factors             */
    uint8_t  primeExponent[2][128];  /**< exponents for CRT         */
    uint8_t  coefficient[128];       /**< CRT coefficient           */
} RsaPrivateKey_t;

typedef struct {
    uint16_t   uLen;                         //32位数组的实际长度
    uint32_t   auValue[ECC_BIGINT32_MAXLEN]; //32位数组的值，数组的低32位地址存放大数的低32位有效数，高32位地址存放大数的高32位有效数
} ECC_STU_BIGINT32;

typedef struct {
    ECC_STU_BIGINT32  stuQx;                    // 公钥坐标Qx
    ECC_STU_BIGINT32  stuQy;                    // 公钥坐标Qy
} ECC_STU_PUBKEY;

typedef struct {
    uint16_t uBits;                             // 模数P的位数
    ECC_STU_BIGINT32  stuPrimeP;                // 模数P
    ECC_STU_BIGINT32  stuCoefficientA;          // 椭圆系数A
    ECC_STU_BIGINT32  stuCoefficientB;          // 椭圆系数B
    ECC_STU_BIGINT32  stuGx;                    // 椭圆基点坐标Gx
    ECC_STU_BIGINT32  stuGy;                    // 椭圆基点坐标Gy
    ECC_STU_BIGINT32  stuPrimeN;                // 椭圆基点坐标G的阶
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
 * @brief	通过PED从RNG中获取一系列随机数据
 * @param[in]	bytes	-	预期数据长度
 * @param[out]	data	-	预期数据指针
 * @retval		0    	-	成功
 * @retval      其它	-	失败，使用errno获取详细信息
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
 * @brief       获取PED的配置
 * @param[out]  config	-	指向保存信息的缓冲区
 * @retval      0		-	成功
 * @retval      其它	-	失败，使用errno获取详细信息
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
	@brief       获取PED状态，可知道机器是否触发，以及触发源
	@param[out]  status	-	触发源 (0 - 正常， 其它 - 触发源)
	@retval      0        成功
	@retval		 其它    失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief       设置PED屏幕输入位置
	@param[in]   x,y			-	横坐标，纵坐标
	@param[in]   width,height	-	窗口的宽度，高度
	@retval      0        		-	成功
	@retval		 其它    		-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief       重建PED（或者称PED格式化），所有PED密钥将被清除，PED将解除锁定状态
	@retval      0			-	成功
	@retval		 其它    	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note        当PED处于攻击状态时，只有Root权限的程序能够对PED格式化。
 @else
	@brief       clear all the Keys and tamper, make PED enter normal status
	@retval      0			-	successful
	@retval		 other		-	failure, use errno to get detail 
	@note        if PED is tampered, normal application call this function will be refused; \n
                 privilege application can call it at any time.
 @endif
 */
int ped_format(void);
#endif //内部接口，不公开

/*!
 @if Chinese
	@brief       清除当前用户（或当前应用）的PED密钥
	@retval      0        	-	成功
	@retval		 其它    	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
 @else
	@brief       clear all the Keys belongs to this application, other Keys not belong to this application will not be clear.
	@retval      0         	-	successful
	@retval		 other     	-	failure, use errno to get detail 
 @endif
*/
int ped_clear_user_keys(void);

/*!
 @if Chinese
	@brief       删除指定的属于该APP的密钥
	@param[in]   KeySystem	-	MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
	@param[in]   KeyType	-	KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
	@param[in]   KeyIndex	-	密钥的索引
	@retval      0        	-	成功
	@retval		 其它    	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note        KeySystem和KeyType可以决定要删除哪种密钥。例如，KeySystem为FIXED_DES，KeyType为KEY_TYPE_PINK，密钥应为“Fixed PIN Key”
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
	@brief       获取PED敏感服务时间
	@param[in]   SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL, TYPE_INJECT_INTERVAL
	@retval      >=0     -	剩余的时间(单位:秒)
	@retval		 其它    -	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief       查询敏感服务访问需要等待时间并增加敏感服务使用限制次数
	@param[in]   SensitiveType	-	TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL, TYPE_INJECT_INTERVAL
	@retval      >0				-	需要等待的时间 
	@retval      =0				-	不需要等待
	@retval		 其它			-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief       设置PIN输入超时时间
	@param[in]   timeout  
				    time  | description
				 :------: | :--------: 
				   >120	  | 非法值
				   30~120 | 有效输入
				   0	  | 设置为默认值60s
				   <30	  | 非法输入
	@retval      0		-	成功
	@retval		 其它	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief       获取PIN输入超时时间
	@retval      0			-	成功
	@retval		 其它    	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
 @else
	@brief        get timeout of PIN input
	@retval       0			-      successful
	@retval		  other		-      failure, use errno to get detail 
 @endif
*/
int ped_get_pin_input_timeout(void);

/*!
 @if Chinese
	@brief        注入dukpt密钥，并保存在ped中
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[in]    InitKey	-	初始密钥, 16字节
	@param[in]    KeyLen	-	密钥长度, 固定为16
	@param[in]    Ksn		-	KSN, 10字节
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        更新该DUKPT Key的KSN，KSN将增加
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[out]   Ksn		-	KSN, 10字节
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         一次调用它可以让你输入PIN码并单独获取一次mac
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
	@brief        获取KSN, 获取的KSN在计算一次PIN和MAC时保持不变
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[out]   Ksn		-	KSN, 10字节
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         如果连续调用2次PIN计算或连续2次调用MAC计算，第2次调用的时候KSN会自动增加，因此获取的KSN只能保证计算一次PIN和一次MAC不会改变。
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
	@brief        用dukpt密钥加密请求数据，调用本函数不会增加KSN.
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[in]    DataLen	-	要加密数据长度，必须为8的倍数
	@param[in]    DataIn	-	要加密的数据
	@param[out]   DataOut	-	保存加密后的结果，其长度与明文数据长度一样
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于加密数据发给服务器。
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
	@brief        用dukpt密钥解密响应数据，调用本函数不会增加KSN.
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[in]    DataLen	-	要解密数据长度，必须为8的倍数
	@param[in]    DataIn	-	要解密的数据
	@param[out]   DataOut	-	保存解密后的结果，其长度与密文数据长度一样
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于解密服务器发过来的密文数据。
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
	@brief        用dukpt密钥解密响应数据，调用本函数不会增加KSN.
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[in]    DataLen	-	要解密数据长度，必须为8的倍数
	@param[in]    DataIn	-	要解密的数据
	@param[out]   DataOut	-	保存解密后的结果，其长度与密文数据长度一样
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于解密服务器发过来的密文数据。
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
	@brief        用dukpt密钥计算服务器发送数据的MAC，调用本函数不会增加KSN.
	@param[in]    KeyIndex	-	DUKPT密钥索引, 0～15
	@param[in]    Mode		-	MAC_MODE_1, MAC_MODE_EMV, MAC_MODE_CUP
	@param[in]    DataLen	-	用于计算mac的数据长度
	@param[in]    DataIn	-	用于计算mac的数据
	@param[out]   MacBlock	-	计算的MAC值，固定为8字节
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于计算服务器发过来数据的MAC值。
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
	@brief        用dukpt密钥验证服务器发送数据的MAC，调用本函数不会增加KSN.
	@param[in]    KeyIndex		-	DUKPT密钥索引, 0～15
	@param[in]    Mode			-	MAC_MODE_1, MAC_MODE_EMV, MAC_MODE_CUP
	@param[in]    DataLen		-	用于计算mac的数据长度
	@param[in]    DataIn		-	用于计算mac的数据
	@param[in]    MacBlock		-	需要验证的MAC值，固定为8字节
	@retval       0        		-	成功
	@retval		  其它     		-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于验证服务器发过来数据的MAC值。  \n
				  掩码的使用方法：需要比较的字节，掩码设置为FF；不需要比较的字节掩码设置为00。 \n
				  这个函数使用的密钥跟ped_get_mac_unified(DUKPT_DES)是一样的。
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
	@brief        将密钥写入到由主密钥加密的PED中
	@param[in]    KeySystem			-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyType			-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[in]    Mode				-	校验算法,参考: <a href="#ped_verify">verify algorithm</a> 
	@param[in]    MasterKeyIndex	-	主密钥索引
	@param[in]    DestKeyIndex		-	目标密钥索引
	@param[in]    KeyLen			-	密钥长度
	@param[in]    KeyData		0-ECC_P256_TYPE密钥内容
	@retval       0        		   	-	成功
	@retval		  其它    		   	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         例如，KeySystem是FIXED_DES，KeyType是KEY_TYPE_PINK，密钥应该是“Fixed PIN Key”        \n 
				  KeySystem是MS_DES或FIXED_DES或MS_AES或FIXED_AES,对应的Mode：                         \n 
				  KEY_VERIFY_NONE，                                                                    \n 
				  KEY_VERIFY_KVC，                                                                     \n 
				  KEY_VERIFY_CMAC                                                                      \n 
				  KeySystem是MS_SM4或FIXED_SM4,对应的Mode：                                            \n 
				  KEY_VERIFY_NONE，                                                                    \n 
				  KEY_VERIFY_SM4_KVC                                                                   \n 
				  注入aes密钥时，只有采用KEY_VERIFY_CMAC校验才支持16、24、32字节密钥。KEY_VERIFY_NONE和KEY_VERIFY_KVC只支持16和32字节密钥。
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
				  KEY_VERIFY_NONE，                                                                                           \n 
				  KEY_VERIFY_KVC，                                                                                            \n 
				  KEY_VERIFY_CMAC                                                                                             \n 
				  When KeySystem is MS_SM4 or FIXED_SM4, the corresponding Mode is as follows:                                \n 
				  KEY_VERIFY_NONE，                                                                                           \n 
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
	@brief        输入用户的PIN并加密它，将PIN块返回给应用程序
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyIndex		-	密钥索引
	@param[in]    Mode			-	计算pin block算法,参考: <a href="#ped_pin_format">PIN BLOCK algorithm</a> 
	@param[in]    ExpectPinLen	-	允许输入PIN长度的枚举值字符串,格式是[数字<,数字>],不能大于12.例如, "0,6,7,8,12"
	@param[in]    CardNo		-	可处理卡号16个字节，前4个字节无效，仅使用后12个字节
	@param[in]    PinBlock		-	PIN BLOCK结果，DES固定为8字节，SM4和AES固定为16字节
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         PIN输入的默认超时时间是120秒，可以通过调用接口ped_set_pin_input_timeout() 设置超时时间。 \n 
				  PIN输入属于敏感服务，2次PIN输入间隔太短的话可能会被拒绝，因此最好调用ped_get_sensitive_timer获取当前是否允许输入， \n 
				  如果返回值大于0则说明需要等待n（返回值）秒后才允许PIN输入。      
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
	@brief       退出输入pin接口
	@retval      0			-	成功
	@retval		 其它    	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note        仅在调用pin输入接口使用时有效。
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
	@brief        获取ic卡的插槽号
	@param[in]    fd		-	IC卡设备描述符, iccard_open_cardslot() 的返回值
	@param[out]   slotno	-	IC卡插槽号
	@retval       0        	-	成功
	@retval		  其它     	-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         该功能用于获取ic卡的插槽号，ped_get_offline_pin() 函数需要插槽号     
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
	@brief        输入PIN并将离线PIN BLOCK送到IC卡，然后获得响应
	@param[in]    KeySystem		-	密钥体系, 可以取值ICC_PLAIN和ICC_CIPHER, 参考: @ref KeySystem_t 
	@param[in]    slotno		-	IC卡插槽号, 可以使用函数 ped_icc_get_slotno() 获得
	@param[in]    ExpectPinLen	-	允许输入PIN长度的枚举值字符串,格式是[数字<,数字>],不能大于12.例如, "0,6,7,8,12"
	@param[in]    icc			-	APDU信息, CLA＋INS＋P1＋P2＋LC
	@param[out]   rsplen		-	rspdata的长度（以字节为单位）
	@param[out]   rspdata		-	从IC卡收到的应答数据，格式为SWA + SWB
	@retval       0        		-	成功
	@retval		  其它     		-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         ICC_PLAIN 表示脱机明文PIN，不加密用户的PIN
				  ICC_CIPHER 表示脱机密文PIN，使用RSA加密用户的PIN
	
 @else
	@brief       input PIN and send offline pin block to IC card then get response
	@param[in]    KeySystem		-	key system, Can be ICC_PLAIN and ICC_CIPHER, reference: @ref KeySystem_t
	@param[in]    slotno		-	No. of IC card slot, user can use ped_icc_get_slotno() to got it
	@param[in]    ExpectPinLen	-	list of expected length, format is [digit<,digit>], no more than 12, for example, "0,6,7,8,12"
	@param[in]    icc			-	APDU information, CLA＋INS＋P1＋P2＋LC
	@param[out]   rsplen		-	length of rspdata in bytes
	@param[out]   rspdata		-	response data that received from IC card, format is SWA＋SWB
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
	@brief        计算输入数据的MAC值
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyIndex		-	MAC密钥索引号
	@param[in]    Mode			-	计算算法: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	DataIn的长度，8/16/24/32/40/48...
	@param[in]    DataIn		-	MAC运算输入数据，用于计算MAC值
	@param[out]   MacBlock		-	MAC运算结果, Des固定为8字节, sm4和aes固定为16字节
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         MAC_MODE_CUP_8和MAC_MODE_1_8只有MS_DES、FIXED_DES和DUKPT_DES支持。
 @else
	@brief        calculate MAC block of data
	@param[in]    KeySystem		-	key system, reference: @ref KeySystem_t
	@param[in]    KeyIndex		-	index of key
	@param[in]    Mode			-	Calculation algorithm: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	length of DataIn，8/16/24/32/40/48...
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
	@brief        帐户数据加密
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyIndex		-	账号密钥索引号
	@param[in]    Mode			-	计算算法: <a href="#ped_mac_format">MAC BLOCK</a> 
	@param[in]    DataLen		-	DataIn的长度，必须是8的倍数
	@param[in]    DataIn		-	保存用于加密的数据
	@param[out]   DataOut		-	保存用于加密后的密文数据
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         这个函数只支持KEY_TYPE_EAK类型的密钥使用des算法加密数据
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
	@brief        注入明文密钥
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    KeyLen		-	明文密钥的长度 
	@param[in]    Key			-	明文密钥的内容
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         这个函数支持的密钥类型：KEY_TYPE_MASTK,KEY_TYPE_FIXPINK,KEY_TYPE_FIXMACK,KEY_TYPE_FIXEAK
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
#endif //内部接口，不公开

/*!
 @if Chinese
	@brief        检查指定密钥是否存在
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    Mode			-	暂时不使用，设为0
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
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

#if 1 //这个接口要开放
/*!
 @if Chinese
	@brief        通过对称密钥加密/解密数据
	@param[in]    Mode		-	加解密算法,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							参考:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV		-	IV
	@param[in]    KeyLen	-	密钥长度
	@param[in]    Key		-	用于加解密的密钥
	@param[in]    DataLen	-	数据长度，DES必须是8的倍数，SM4和AES必须是16的倍数
	@param[in]    DataIn	-	用于加解密的数据
	@param[out]   DataOut	-	加解密后的结果
	@retval       0        	-	   成功
	@retval		  其它     	-	   失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        使用保存在ped里面的密钥进行加密
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	密钥索引	
	@param[in]    Mode			-	加密算法,eg: (TDEA_ENCRYPT | TDEA_MODE_ECB)     \n
							       参考:<a href="#ped_crypto">crypto algorithm</a>, <a href="#ped_crypto_mode">crypto mode</a>
	@param[in]    IV			-	IV
	@param[in]    DataLen		-	DataIn的数据长度，DES必须是8的倍数，SM4和AES必须是16的倍数
	@param[in]    DataIn		-	用于加密的数据
	@param[out]   OutLen		-	DataOut数据长度
	@param[out]   DataOut		-	加密后的结果
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        获取工作密钥kvc
	@param[in]    KeySystem		-	密钥体系,参考: @ref KeySystem_t
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    KVC			-	KVC内容
	@retval       0        		-   成功
	@retval		  其它     		-   失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        使用在ped里面的RSA私钥计算RSA block
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    input			-	用于计算RSA block的原始数据 
	@param[in]    inputLen		-	input数据长度
	@param[out]   output		-	用于保存计算出来的RSA block
	@param[in]    outputLen		-	output缓存区长度
	@param[out]   outputLen		-	实际输出的数据长度 
	@retval       0				-	成功
	@retval		  其它 			-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        导出rsa公钥
	@param[in]    KeyIndex		-	密钥索引号
	@param[out]   PubKey		-	用于保存公钥数据
	@param[in]    KeyLen		-	PubKey缓存区长度
	@param[out]   KeyLen		-	实际输出的数据长度 
	@retval       0				-	成功
	@retval		  其它 			-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        导出rsa证书
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a> 
	@param[out]   pubCert		-	用于保存获取到的证书数据
	@param[in]    CertLen		-	output缓存区长度
	@param[out]   CertLen		-	获取到的证书数据长度
	@retval       0				-	成功
	@retval		  其它 			-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
	@brief        注入rsa公共证书
	@param[in]    KeyIndex		-	密钥索引号
	@param[in]    CUID			-	自定义id和用户id 
	@param[in]    KeyType		-	密钥类型,参考: <a href="#ped_key_type">key type</a>
	@param[in]    input			-	证书数据
	@param[in]    inputLen		-	Input数据长度
	@retval       0				-	成功
	@retval		  其它 			-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
  * @brief      硬件生成rsa密钥.
  * @param[in]  bits		-	RSA最大支持2048
  * @param[in]  exponent	-	rsa指数 65537
  * @param[out] PriKey		-	输出rsa私钥
  * @retval      0 			-	成功
  * @retval      其它 		-	失败
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
 * @brief          RSA公钥计算.
 * @param[out]     output		-	输出字符的指针
 * @param[in]      outputlen    -	[in]  传出字符预留长度
 * @param[out]     outputlen    -	[out] 传出字符长度
 * @param[in]      input        -	传入字符的指针
 * @param[in]      inputlen     -	传入字符长度
 * @param[in]      public_key   -	RSA公钥
 * @retval     	   0   			-	成功
 * @retval     	   其它 		-	失败，使用errno获取详细信息
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
 * @brief          RSA私钥计算.
 * @param[out]     output       -	输出字符的指针
 * @param[in]      outputlen    -	[in]  输出字符的指针
 * @param[out]     outputlen    -	[out] 传出字符的长度
 * @param[in]      input        -	传入字符的指针
 * @param[in]      inputlen     -	传入字符的指针
 * @param[in]      private_key  -	RSA私钥
 * @retval      0    - 成功
 * @retval      其它 - 失败，使用errno获取详细信息
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
 * @brief           硬件使用rsa私钥对消息进行签名
 * @param[in]       type	- 签名的哈希类型。看到@ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	传入数据的指针
 * @param[in]       m_len	-	传入数据的长度
 * @param[out]      sigret	-	签名数据
 * @param[in]       siglen	-	签名数据的长度,
 *                            [in] 保存pResult的缓冲区大小，至少是关键模块的长度
 * @param[out]      siglen	-	签名数据的长度，[out]实际输出sigret的长度
 * @param[in]       private_key	-	rsa私钥缓冲区
 * @retval     0 - 成功
 * @retval     其它 - 失败，使用errno获取详细信息
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
 * @brief           硬件使用rsa公钥验证签名
 * @param[in]       type	-	签名的哈希类型。参考@ref R_Hash_Type
                        - RSA_HASH_SHA1 : sha1
                        - RSA_HASH_SHA256: sha256
 * @param[in]       m		-	消息数据指针
 * @param[in]       m_len	-	消息数据长度
 * @param[in]       sigbuf	-	签名数据
 * @param[in]       siglen	-	签名数据的长度
 * @param[in]       public_key	-	rsa公钥缓冲区
 * @retval      0 		- 成功
 * @retval      其它 	- 失败，使用errno获取详细信息
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
	@brief        计算（硬件序列号+加密随机因子）的MAC值
	@param[in]    factor		-	加密随机因子，MAC运算输入数据，用于计算MAC值
	@param[in]    factorLen		-	输入的加密随机因子数据长度，一般6字节
	@param[out]   macOut		-	MAC运算结果，长度8字节
	@retval       0        		-	成功
	@retval		  其它     		-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
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
 * @brief        创建一个AES DUKPT密钥并保存到PED
 * @param[in]    KeyIndex		-	密钥的索引，0 ~ 15
 * @param[in]    Dukpttype		-	2:_AES128_,3:_AES192_,4:_AES256_.
 * @param[in]    InitKey        -	初始化的密钥，16字节，24字节，32字节.
 * @param[in]    KeyLen         -	key len，默认为_AES128_:16， _AES192_:24， _AES256_:32
 * @param[in]    Ksn            -	KSN 12字节.
 * @retval      0 - 成功   
 * @retval      其它 -失败
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
 * @brief        更新这个DUKPT密钥的KSN, KSN将增加
 * @param[in]    KeyIndex		-	密钥索引，0 ~ 15
 * @param[out]   Ksn			-	KSN 12字节.
 * @retval	   	0 		- 成功	 
 * @retval   	其它 	-失败，使用errno获取详细信息
 * @note        调用它一次可以允许你输入PIN和获得mac一次单独.
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
 * @brief        获取这个DUKPT密钥的KSN, KSN将增加
 * @param[in]    KeyIndex		-	密钥索引，0 ~ 15
 * @param[out]   Ksn			-	KSN 12字节.
 * @retval      0 		- 成功   
 * @retval      其它 	- 失败
 * @note        如果PIN块被计算两次或MAC块被计算两次，KSN将在第二次呼叫时自动增加。\ n
 *				所以得到的KSN只能保证PIN和MAC计算一次，不会改变。
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
	@brief        用dukpt aes密钥加密请求数据，调用本函数不会增加KSN.
	@param[in]    KeyIndex		-	DUKPT密钥索引, 0～15
	@param[in]    Mode		-	DUKPTKeyType的枚举类型或KeyUsage的枚举类型(_2TDEA_ << 24 | _Key_Encryption_Key_) 
                                 不支持 _PIN_Encryption_, _Data_Encryption_decrypt_
	@param[in]    DataLen		-	要加密数据长度，必须为16的倍数
	@param[in]    DataIn		-	要加密的数据
	@param[out]   DataOut		-	保存加密后的结果，其长度与明文数据长度一样
	@retval       0        		-	成功
	@retval		  其它     		-	失败, 错误码参考:<a href="#ped_errno">Errno</a>
	@note         本函数通常用于加密数据发给服务器。
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
 * @brief        dukpt aes密钥用于解密响应数据。调用这个函数不会增加KSN。.
 * @param[in]    KeyIndex		-	密钥索引, 0 ~ 15
 * @param[in]    Mode			-	类型为DUKPTKeyType，模式为KeyUsage(_2TDEA_ << 24 | _Key_Encryption_Key_) 
 *                              不支持 _PIN_Encryption_, _Data_Encryption_encrypt_
 * @param[in]    DataLen		-	DataIn的长度，16字节
 * @param[in]    DataIn			-	密文数据
 * @param[out]   DataOut		-	明文数据
 * @retval       0 - 成功
 * @retval       其它 - 失败
 * @note         该功能通常用于对服务器发送的密文数据进行解密.
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
 * @brief        生成ecc密钥对.
 * @param[in]    EccType	
 *					- 0-ECC_P256_TYPE
 *                  - 1-ECC_P521_TYPE
 * @param[in]    Para		-	ECC参数
 * @param[out]   PriKey		-	传出的私钥
 * @param[out]   PubKey		-	传出的公钥
 * @retval       0 			- 成功
 * @retval       其它 		- 失败
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
 * @brief         使用ecc公钥加密数据
 * @param[in]     PubKey	-	公钥
 * @param[in]     Para		-	ECC参数
 * @param[in]     InLen		-	传输数据的长度
 * @param[in]     DataIn	-	传入数据
 * @param[out]    OutLen	-	输出数据的长度
 * @param[out]    DataOut	-	输出数据
 * @retval        0 		- 成功
 * @retval        其它 		- 失败
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
 * @brief         使用ecc私钥解密数据
 * @param[in]     PriKey	-	私钥
 * @param[in]     Para		-	ecc参数
 * @param[in]     InLen		-	DataIn长度
 * @param[in]     DataIn	-	需要解密的数据
 * @param[out]    OutLen	-	明文的长度，通常等于InLen - 96
 * @param[out]    DataOut	-	传输数据
 * @retval        0 		- 成功
 * @retval        其它 		- 失败
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
* @brief        使用ECC私钥对消息进行签名
* @param[in]     mes		-	 用于签名的消息
* @param[in]     mLen		-	签名消息的长度 
* @param[in]     hashMode	-	哈希计算方法
* @param[in]     priKey		-	私钥
* @param[in]     para		-	ecdsa参数
* @param[out]    pSignR		-	签名结果R 
* @param[out]    pSignS		-	签名结果S
* @retval        0 			- 成功
* @retval        其它 		- 失败
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
	* @brief         使用ECC公钥验证签名
	* @param[in]     mes		-	用于签名的消息 
	* @param[in]     mLen		-	签名消息的长度
	* @param[in]     hashMode	-	哈希计算方法 
	* @param[in]     pubKey		-	公钥
	* @param[in]     para		-	ecdsa参数
	* @param[out]    pSignR		-	签名结果R 
	* @param[out]    pSignS		-	签名结果S
	* @retval        0 			- 成功
	* @retval        其它 		- 失败
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
#endif //内部接口，不公开

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PED_H__ */

/** @} */

