
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
 * @addtogroup PED PED
 * @{
 */

#ifndef __PED_GM_H__
#define __PED_GM_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CFG_GM_ENABLE
#define CFG_GM_ENABLE           1
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
@if Chinese
 * @name SM2/SM3密钥相关的长度定义
@else 
 * @name SM2/SM3 Key - related length definition
@endif
 * @{
 */
#define SM2_PRI_KEY_SIZE        32                                          /**<@if Chinese SM2私钥长度        @else SM2 private key length 								@endif*/
#define SM2_PUB_KEY_X_SIZE      32                                          /**<@if Chinese SM2公钥X分量长度   @else SM2 Indicates the X component length of the public key @endif*/
#define SM2_PUB_KEY_Y_SIZE      32                                          /**<@if Chinese SM2公钥Y分量长度   @else SM2 Indicates the y-component length of the public key @endif*/
#define SM2_PUB_KEY_SIZE        (SM2_PUB_KEY_X_SIZE + SM2_PUB_KEY_Y_SIZE)   /**<@if Chinese SM2公钥长度        @else SM2 Indicates the length of the public key 			@endif*/
#define SM2_SIGN_RESULT_SIZE    64                                          /**<@if Chinese SM2签名结果长度    @else SM2 Indicates the signature length 					@endif*/
#define SM3_HASH_SIZE           32                                          /**<@if Chinese SM3哈希结果长度    @else SM3 Hash result length 								@endif*/
/* @} */

/**
@if Chinese
 * @brief SM2私钥结构定义
@else 
 * @brief SM2 Private key structure definition
@endif
 */
typedef struct {
    int     len;                        /**<@if Chinese 密钥总长度         @else	Total key length	@endif*/
    uint8_t key[SM2_PRI_KEY_SIZE];      /**<@if Chinese SM2密钥内容        @else	SM2 Key content		@endif*/
} SM2_PriKey_t ;

/**
@if Chinese
 * @brief SM2公钥结构定义
@else 
 * @brief SM2 Public key structure definition
@endif 
 */
typedef struct {
    int     len;                        /**<@if Chinese 密钥总长度         @else	Total key length	@endif*/
    uint8_t x[SM2_PUB_KEY_X_SIZE];      /**<@if Chinese SM2密钥x分量       @else	SM2 Key X component	@endif*/
    uint8_t y[SM2_PUB_KEY_Y_SIZE];      /**<@if Chinese SM2密钥y分量       @else	SM2 Key y component	@endif*/
} SM2_PubKey_t ;

/**
@if Chinese
 * @brief SM2密钥结构定义
@else  
 * @brief SM2 Key structure definition
@endif  
 */
typedef struct {
    SM2_PriKey_t prikey;                /**<@if Chinese SM2私钥部分        @else	SM2 Private key	@endif*/
    SM2_PubKey_t pubkey;                /**<@if Chinese SM2公钥部分        @else	SM2 Public key	@endif*/
} SM2_Key_t ;

/**
@if Chinese
 * @brief SM3计算上下文结构定义
@else  
 * @brief SM3 computes the context structure definition
@endif  
 */
typedef struct {
    uint8_t context[256];               /**<@if Chinese SM3哈希上下文内容  @else	SM3 Hash context content	@endif*/
} SM3_CONTEXT_t;

////////////////////////////////// GM RNG //////////////////////////////////////////////////////////

/**
@if Chinese
 * @brief       通过PED从RNG中获取一系列随机数据
 * @param[in]	bytes	-	预期数据
 * @param[out]	data	-	指向保存数据的缓冲区
 * @return      0    - 成功
 * @return      其它 - 失败，使用errno获取详细信息
@else 
 * @brief       get a serials of random data from RNG by PED
 * @param[in]   bytes	-	how many data you want to get
 * @param[out]  data	-	point the buffer that data save to
 * @return      0    - success
 * @return      other - failure, use errno to get detail
@endif
 */
int ped_gm_get_random_nr(uint32_t bytes, void *data);

////////////////////////////////// SM3 /////////////////////////////////////////////////////////////

/**
@if Chinese
 * @brief       初始化SM3
 * @param[in]   ctx  - SM3数据结构，临时保存数据
 * @param[out]  ctx  - SM3数据结构，临时保存数据（保存传出值）
 * @return      0    - 成功
 * @return      其它 - 失败，使用errno获取详细信息
@else 
 * @brief       initialize SM3
 * @param[in]   ctx  - SM3 data structure, temping saving data
 * @param[out]  ctx  - SM3 data structure, temping saving data
 * @return      0    - success
 * @return      other - failure, use errno to get detail
@endif
 */
int ped_sm3_init(SM3_CONTEXT_t *ctx);

/**
@if Chinese
 * @brief       输入数据到SM3计算器
 * @param[in]   ctx  - SM3数据结构，临时保存数据
 * @param[in]   data - 传入计算的数据
 * @param[in]   len  - 传入计算的数据的长度
 * @param[out]  ctx  - SM3数据结构，临时保存数据（保存传出值）
 * @return      0    - 成功
 * @return      其它 - 失败，使用errno获取详细信息
@else 
 * @brief       input data to SM3 calculator
 * @param[in]   ctx  - SM3 data structure, temping saving data
 * @param[in]   data - data for calculation
 * @param[in]   len  - the data length
 * @param[out]  ctx  - SM3 data structure, temping saving data
 * @return      0    - success
 * @return      other - failure, use errno to get detail
@endif
 */
int ped_sm3_update(SM3_CONTEXT_t *ctx, const void *data, int len);

/**
@if Chinese
 * @brief       得到SM3结果
 * @param[in]   ctx    - SM3数据结构，临时保存数据
 * @param[out]  ctx    - SM3数据结构，临时保存数据（输出）
 * @param[out]  output - 计算结果，32个字节
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       get SM3 result
 * @param[in]   ctx    - SM3 data structure, temping saving data
 * @param[out]  ctx    - SM3 data structure, temping saving data
 * @param[out]  output - result, 32 bytes
 * @return      0      - success
 * @return      other  - failure, use errno to get detail
@endif
 */
int ped_sm3_final(SM3_CONTEXT_t *ctx, uint8_t output[SM3_HASH_SIZE]);

////////////////////////////////// SM2 /////////////////////////////////////////////////////////////

/**
@if Chinese
 * @brief       生成SM2密钥对.
 * @param[in]   PriKeyExist
 * 							- 0-随机生成私钥
 *                          - 1-指定Private，用于生成公钥
 *                          - New9220只支持0
 * @param[in]   PriKey     -	如果PriKeyExist=1，则指向私钥
 * @param[out]  PriKey     -	如果PriKeyExist=0，则输出私钥
 * @param[out]  PubKey     -	传出公钥
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       generate SM2 key pair.
 * @param[in]   PriKeyExist	
 * 							- 0-generate private key by random
 *                          - 1-private was specifed, and used to generate public key
 *                          - new9220 only support 0
 * @param[in]   PriKey     -	if PriKeyExist=1, it pointer to private key
 * @param[out]  PriKey     -	if PriKeyExist=0, output private key
 * @param[out]  PubKey     -	output public key
 * @return      0 - successfull
 * @return      other - failure
@endif
 */
int ped_sm2_genkey(SM2_PriKey_t *PriKey, SM2_PubKey_t *PubKey, int PriKeyExist);

/**
@if Chinese
 * @brief       使用sm2公钥加密数据
 * @param[in]   PubKey     -	公钥
 * @param[in]   InLen      -	DataIn长度
 * @param[in]   DataIn     -	需要加密的数据
 * @param[out]  OutLen     -	密文的长度，一般为InLen + 96
 * @param[out]  DataOut    -	密文
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       encrypt data using sm2 public key
 * @param[in]   PubKey     -	public key
 * @param[in]   InLen      -	length of DataIn
 * @param[in]   DataIn     -	data to be encrypted
 * @param[out]  OutLen     -	length of ciphertext, normally it equal InLen + 96
 * @param[out]  DataOut    -	ciphertext
 * @return      0 - successfull
 * @return      other - failure
@endif
 */
int ped_sm2_pubkey_encrypt(const SM2_PubKey_t *PubKey,
                           uint32_t InLen,   const void *DataIn,
                           uint32_t *OutLen, void *DataOut);

/**
@if Chinese
 * @brief       使用sm2私钥解密数据
 * @param[in]   PriKey     -	私钥
 * @param[in]   InLen      -	DataIn长度
 * @param[in]   DataIn     -	需要解密的数据
 * @param[out]  OutLen     -	明文的长度，通常等于InLen - 96
 * @param[out]  DataOut    -	明文
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       decrypt data using sm2 private key
 * @param[in]   PriKey     -	private key
 * @param[in]   InLen      -	length of DataIn
 * @param[in]   DataIn     -	data to be decrypted
 * @param[out]  OutLen     -	length of plaintext, normally it equal InLen - 96
 * @param[out]  DataOut    -	plaintext
 * @return      0 - successfull
 * @return      other - failure
@endif
 */
int ped_sm2_prikey_decrypt(const SM2_PriKey_t *PriKey,
                           uint32_t InLen,   const void *DataIn,
                           uint32_t *OutLen, void *DataOut);

/**
@if Chinese
 * @brief       计算SM3的值
 * @param[in]   PubKey     -	公钥
 * @param[in]   Msg        -	用户消息
 * @param[in]   MsgLen     -	Msg的长度
 * @param[in]   ID         -	用户ID
 * @param[in]   IDLen      -	ID的长度
 * @param[out]  sm3value   -	Sm3的值为32字节
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       calculate SM3 value
 * @param[in]   PubKey     -	public key
 * @param[in]   Msg        -	user message
 * @param[in]   MsgLen     -	length of Msg
 * @param[in]   ID         -	user ID
 * @param[in]   IDLen      -	length of ID
 * @param[out]  sm3value   -	sm3 value, 32 bytes
 * @return      0 - successfull
 * @return      other - failure
@endif
 */
int ped_sm2_get_hash_value(const SM2_PubKey_t *PubKey,
                           const void *Msg, uint32_t MsgLen,
                           const void *ID,  uint32_t IDLen,
                           void *sm3value);

/**
@if Chinese
 * @brief       使用私钥签名内容
 * @param[in]   Sm2Key     - Sm2密钥(包含私钥和公钥)
 * @param[in]   Hash       - 通过调用ped_sm2_get_hash_value计算，32字节
 * @param[in]   HashLen    - 哈希值的长度
 * @param[out]  pResult    - 签名数据，64字节
 * @param[in]   pResultLen  - [in]  缓冲区大小保存pResult，至少64字节
 * @param[out]  pResultLen  - [out] 实际输出的长度
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       sign message using private key
 * @param[in]   Sm2Key     - sm2 key (contain private key and public key)
 * @param[in]   Hash       - calcuate by call ped_sm2_get_hash_value, 32 bytes
 * @param[in]   HashLen    - length of Hash
 * @param[out]  pResult    - signature data, 64 bytes
 * @param[in]   pResultLen  - [in]  buffer size to save pResult, at least 64 bytes
 * @param[out]  pResultLen  - [out] length of real output pResult
 * @return      0 - successfull
 * @return      other - failure
 @endif
 */
int ped_sm2_sign(const SM2_Key_t *Sm2Key,
                 const void *Hash,  uint32_t HashLen,
                 void *pResult,     uint32_t *pResultLen);

/**
@if Chinese
 * @brief       使用私钥签署消息
 * @param[in]   KeyIndex	-	私钥索引
 * @param[in]   Hash		-	通过调用ped_sm2_get_hash_value计算，32字节
 * @param[in]   HashLen		-	哈希值长度
 * @param[out]  pResult		-	签名数据，64字节
 * @param[in]   pResultLen	-	[in]  缓冲区大小保存pResult，至少64字节
 * @param[out]  pResultLen	-	[out] 实际输出的长度
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       sign message using private key
 * @param[in]   KeyIndex	-	indicate index of private key
 * @param[in]   Hash		-	calcuate by call ped_sm2_get_hash_value, 32 bytes
 * @param[in]   HashLen		-	length of Hash
 * @param[out]  pResult		-	signature data, 64 bytes
 * @param[in]   pResultLen	-	[in]  buffer size to save pResult, at least 64 bytes
 * @param[out]  pResultLen	-	[out] length of real output pResult
 * @return      0 - successfull
 * @return      other - failure
@endif
 */

int ped_sm2_sign_by_key(uint32_t KeyIndex,
                        const void *Hash,
                        uint32_t HashLen,
                        void *pResult,
                        uint32_t *pResultLen);
#if 0 // unsupported
/**

 * @brief       使用私钥签署消息
 * @param[in]   KeyIndex		-	私钥索引
 * @param[in]   message			-	要签名的消息
 * @param[in]   message_len		-	消息总长度
   @param[in]   id				-	指向id的缓冲区指针
   @param[in]   id_len			-	id的长度
 * @param[out]  pResult			-	签名数据，64字节
 * @param[in]   pResultLen		-	缓冲区大小保存pResult，至少64字节
 * @param[out]  pResultLen		-	实际输出的长度
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       sign message using private key
 * @param[in]   KeyIndex		-	indicate index of private key
 * @param[in]   message			-	the message be signed
 * @param[in]   message_len		-	length of message
   @param[in]   id				-	buffer pointer to id
   @param[in]   id_len			-	the len of id
 * @param[out]  pResult			-	signature data, 64 bytes
 * @param[in]   pResultLen		-	buffer size to save pResult, at least 64 bytes
 * @param[out]  pResultLen		-	length of real output pResult
 * @return      0 - successfull
 * @return      other - failure
@endif
 */


int ped_sm2_sign_by_key_ex(uint32_t KeyIndex,
                           const void *message,
                           uint32_t message_len,
                           const void *id,
                           uint32_t id_len,
                           void *pResult,
                           uint32_t *pResultLen);
#endif

/**
@if Chinese
 * @brief       使用sm2公钥验证签名
 * @param[in]   PubKey		-	公钥
 * @param[in]   Hash		-	通过调用ped_sm2_get_hash_value计算，32字节
 * @param[in]   HashLen		-	哈希值长度
 * @param[in]   Sign		-	签名数据，由ped_sm2_sign生成，64字节
 * @param[in]   SignLen		-	信号的长度
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       verify signature using sm2 public key
 * @param[in]   PubKey		-	public key
 * @param[in]   Hash		-	calcuate by call ped_sm2_get_hash_value, 32 bytes
 * @param[in]   HashLen		-	length of Hash
 * @param[in]   Sign		-	signature data, it was generate by ped_sm2_sign, 64 bytes
 * @param[in]   SignLen		-	length of Sign
 * @return      0 - verify ok
 * @return      other - verify failed or other error
@endif
 */
int ped_sm2_verify(const SM2_PubKey_t *PubKey,
                   const void *Hash,   int HashLen,
                   const void *Sign,   int SignLen);

#if 0 // unsupported
/**
@if Chinese
 * @brief       sm2 私钥操作
 * @param[in]   KeyIndex  - 密钥索引
 * @param[in]   input     - 传入数据
 * @param[in]   inputLen  - 传入数据长度
 * @param[out]  output    - 点缓冲区，以保存操作数据
 * @param[in]   outputLen - [in]  输出缓冲区大小
 * @param[out]  outputLen - [out] 实际输出数据的长度
 * @return      0      - 成功
 *              其它   - 失败，使用errno获取详细信息
@else 
 * @brief       sm2 private operation
 * @param[in]   KeyIndex  - index of key
 * @param[in]   input     - point buffer to be operated
 * @param[in]   inputLen  - length of input
 * @param[out]  output    - point buffer to save operated data
 * @param[in]   outputLen - [in]  size of output buffer
 * @param[out]  outputLen - [out] length of real output data
 * @return      0    - success
 *              other - failure, use errno to get detail
@endif
 */
int ped_sm2_private_operation(uint32_t  KeyIndex,
                              void       *output,
                              uint32_t   *outputLen,
                              const void *input,
                              uint32_t    inputLen);
#endif

/**
@if Chinese
 * @brief       导出sm2公钥
 * @param[in]   KeyIndex  - 密钥索引
 * @param[out]  PubKey    - 点缓冲区保存公钥数据，sizeof(SM2_PubKey_t) = 64+4字节
 * @param[in]   PubKeyLen - 保存pubkey的缓冲区大小
 * @param[out]  PubKeyLen - 实际输出数据的长度
 * @return      0      - 成功
 * @return      其它   - 失败，使用errno获取详细信息
@else 
 * @brief       export sm2 public key
 * @param[in]   KeyIndex  - index of key
 * @param[out]  PubKey    - point buffer to save public key data, sizeof(SM2_PubKey_t) = 64+4 bytes
 * @param[in]   PubKeyLen - buffer size to save pubkey
 * @param[out]  PubKeyLen - length of real output data
 * @return      0    - success
 * @return      other - failure, use errno to get detail
@endif
 */
int ped_sm2_export_pub_key(uint32_t KeyIndex,
                           void *PubKey,
                           uint32_t *PubKeyLen);

///////////////////////////////////////// SM4 ////////////////////////////////////////////////////

#if 0 //SM4堆成加解密接口可使用ped_symmetric_crypto接口
/**
@if Chinese
 * @brief       通过SM4加密/解密数据
 * @param[in]   Mode      - (SM4_DECRYPT or SM4_ENCRYPT) | (SM4_MODE_ECB or SM4_MODE_CBC)
 * @param[in]   IV        - 初始IV，必须是16字节
 * @param[in]   KeyLen    - SM4Key长度，必须为16
 * @param[in]   Key       - SM4密钥
 * @param[in]   InLen     - 输入长度，必须为16字节的倍数，每次小于16KB
 * @param[in]   input     - 要加密/解密的点缓冲区
 * @param[out]  IV        - 在调用此函数后更新iv
 * @param[out]  output    - 点缓冲区，以保存解密/加密数据
 * @return      0      - 成功
 *              其它   - 失败，使用errno获取详细信息
@else 
 * @brief       encrypt/decrypt data by SM4
 * @param[in]   Mode      - (SM4_DECRYPT or SM4_ENCRYPT) | (SM4_MODE_ECB or SM4_MODE_CBC)
 * @param[in]   IV        - initial IV, must be 16 bytes
 * @param[in]   KeyLen    - length SM4Key, must be 16
 * @param[in]   Key       - plain SM4 key
 * @param[in]   InLen     - Input length, must be multiple of 16 bytes, less than 16KB per time
 * @param[in]   input     - point buffer to be encrypt/decrypt
 * @param[out]  IV        - update iv after call this function
 * @param[out]  output    - point buffer to save decrypt/encrypt data
 * @return      0    - success
 *              other - failure, use errno to get detail
@endif
 */
int ped_sm4_calc(uint32_t       Mode,
                 uint8_t        IV[16],
                 uint32_t       KeyLen,
                 const void    *Key,
                 uint32_t       InLen,
                 const void    *input,
                 void          *output); //去掉此接口
#endif

/**
 * @brief          Get mqtt data.
 * @param  in      none
 * @param  out     mqtt data
 * @return         none - failure
                   else - success <br>
 * @note
*/
unsigned char *get_mqtt_data(void);
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PED_GM_H__ */

/** @} */

