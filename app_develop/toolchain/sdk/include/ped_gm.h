
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
 * @name SM2/SM3��Կ��صĳ��ȶ���
@else 
 * @name SM2/SM3 Key - related length definition
@endif
 * @{
 */
#define SM2_PRI_KEY_SIZE        32                                          /**<@if Chinese SM2˽Կ����        @else SM2 private key length 								@endif*/
#define SM2_PUB_KEY_X_SIZE      32                                          /**<@if Chinese SM2��ԿX��������   @else SM2 Indicates the X component length of the public key @endif*/
#define SM2_PUB_KEY_Y_SIZE      32                                          /**<@if Chinese SM2��ԿY��������   @else SM2 Indicates the y-component length of the public key @endif*/
#define SM2_PUB_KEY_SIZE        (SM2_PUB_KEY_X_SIZE + SM2_PUB_KEY_Y_SIZE)   /**<@if Chinese SM2��Կ����        @else SM2 Indicates the length of the public key 			@endif*/
#define SM2_SIGN_RESULT_SIZE    64                                          /**<@if Chinese SM2ǩ���������    @else SM2 Indicates the signature length 					@endif*/
#define SM3_HASH_SIZE           32                                          /**<@if Chinese SM3��ϣ�������    @else SM3 Hash result length 								@endif*/
/* @} */

/**
@if Chinese
 * @brief SM2˽Կ�ṹ����
@else 
 * @brief SM2 Private key structure definition
@endif
 */
typedef struct {
    int     len;                        /**<@if Chinese ��Կ�ܳ���         @else	Total key length	@endif*/
    uint8_t key[SM2_PRI_KEY_SIZE];      /**<@if Chinese SM2��Կ����        @else	SM2 Key content		@endif*/
} SM2_PriKey_t ;

/**
@if Chinese
 * @brief SM2��Կ�ṹ����
@else 
 * @brief SM2 Public key structure definition
@endif 
 */
typedef struct {
    int     len;                        /**<@if Chinese ��Կ�ܳ���         @else	Total key length	@endif*/
    uint8_t x[SM2_PUB_KEY_X_SIZE];      /**<@if Chinese SM2��Կx����       @else	SM2 Key X component	@endif*/
    uint8_t y[SM2_PUB_KEY_Y_SIZE];      /**<@if Chinese SM2��Կy����       @else	SM2 Key y component	@endif*/
} SM2_PubKey_t ;

/**
@if Chinese
 * @brief SM2��Կ�ṹ����
@else  
 * @brief SM2 Key structure definition
@endif  
 */
typedef struct {
    SM2_PriKey_t prikey;                /**<@if Chinese SM2˽Կ����        @else	SM2 Private key	@endif*/
    SM2_PubKey_t pubkey;                /**<@if Chinese SM2��Կ����        @else	SM2 Public key	@endif*/
} SM2_Key_t ;

/**
@if Chinese
 * @brief SM3���������Ľṹ����
@else  
 * @brief SM3 computes the context structure definition
@endif  
 */
typedef struct {
    uint8_t context[256];               /**<@if Chinese SM3��ϣ����������  @else	SM3 Hash context content	@endif*/
} SM3_CONTEXT_t;

////////////////////////////////// GM RNG //////////////////////////////////////////////////////////

/**
@if Chinese
 * @brief       ͨ��PED��RNG�л�ȡһϵ���������
 * @param[in]	bytes	-	Ԥ������
 * @param[out]	data	-	ָ�򱣴����ݵĻ�����
 * @return      0    - �ɹ�
 * @return      ���� - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ��ʼ��SM3
 * @param[in]   ctx  - SM3���ݽṹ����ʱ��������
 * @param[out]  ctx  - SM3���ݽṹ����ʱ�������ݣ����洫��ֵ��
 * @return      0    - �ɹ�
 * @return      ���� - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       �������ݵ�SM3������
 * @param[in]   ctx  - SM3���ݽṹ����ʱ��������
 * @param[in]   data - ������������
 * @param[in]   len  - �����������ݵĳ���
 * @param[out]  ctx  - SM3���ݽṹ����ʱ�������ݣ����洫��ֵ��
 * @return      0    - �ɹ�
 * @return      ���� - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       �õ�SM3���
 * @param[in]   ctx    - SM3���ݽṹ����ʱ��������
 * @param[out]  ctx    - SM3���ݽṹ����ʱ�������ݣ������
 * @param[out]  output - ��������32���ֽ�
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ����SM2��Կ��.
 * @param[in]   PriKeyExist
 * 							- 0-�������˽Կ
 *                          - 1-ָ��Private���������ɹ�Կ
 *                          - New9220ֻ֧��0
 * @param[in]   PriKey     -	���PriKeyExist=1����ָ��˽Կ
 * @param[out]  PriKey     -	���PriKeyExist=0�������˽Կ
 * @param[out]  PubKey     -	������Կ
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ʹ��sm2��Կ��������
 * @param[in]   PubKey     -	��Կ
 * @param[in]   InLen      -	DataIn����
 * @param[in]   DataIn     -	��Ҫ���ܵ�����
 * @param[out]  OutLen     -	���ĵĳ��ȣ�һ��ΪInLen + 96
 * @param[out]  DataOut    -	����
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ʹ��sm2˽Կ��������
 * @param[in]   PriKey     -	˽Կ
 * @param[in]   InLen      -	DataIn����
 * @param[in]   DataIn     -	��Ҫ���ܵ�����
 * @param[out]  OutLen     -	���ĵĳ��ȣ�ͨ������InLen - 96
 * @param[out]  DataOut    -	����
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ����SM3��ֵ
 * @param[in]   PubKey     -	��Կ
 * @param[in]   Msg        -	�û���Ϣ
 * @param[in]   MsgLen     -	Msg�ĳ���
 * @param[in]   ID         -	�û�ID
 * @param[in]   IDLen      -	ID�ĳ���
 * @param[out]  sm3value   -	Sm3��ֵΪ32�ֽ�
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ʹ��˽Կǩ������
 * @param[in]   Sm2Key     - Sm2��Կ(����˽Կ�͹�Կ)
 * @param[in]   Hash       - ͨ������ped_sm2_get_hash_value���㣬32�ֽ�
 * @param[in]   HashLen    - ��ϣֵ�ĳ���
 * @param[out]  pResult    - ǩ�����ݣ�64�ֽ�
 * @param[in]   pResultLen  - [in]  ��������С����pResult������64�ֽ�
 * @param[out]  pResultLen  - [out] ʵ������ĳ���
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ʹ��˽Կǩ����Ϣ
 * @param[in]   KeyIndex	-	˽Կ����
 * @param[in]   Hash		-	ͨ������ped_sm2_get_hash_value���㣬32�ֽ�
 * @param[in]   HashLen		-	��ϣֵ����
 * @param[out]  pResult		-	ǩ�����ݣ�64�ֽ�
 * @param[in]   pResultLen	-	[in]  ��������С����pResult������64�ֽ�
 * @param[out]  pResultLen	-	[out] ʵ������ĳ���
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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

 * @brief       ʹ��˽Կǩ����Ϣ
 * @param[in]   KeyIndex		-	˽Կ����
 * @param[in]   message			-	Ҫǩ������Ϣ
 * @param[in]   message_len		-	��Ϣ�ܳ���
   @param[in]   id				-	ָ��id�Ļ�����ָ��
   @param[in]   id_len			-	id�ĳ���
 * @param[out]  pResult			-	ǩ�����ݣ�64�ֽ�
 * @param[in]   pResultLen		-	��������С����pResult������64�ֽ�
 * @param[out]  pResultLen		-	ʵ������ĳ���
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ʹ��sm2��Կ��֤ǩ��
 * @param[in]   PubKey		-	��Կ
 * @param[in]   Hash		-	ͨ������ped_sm2_get_hash_value���㣬32�ֽ�
 * @param[in]   HashLen		-	��ϣֵ����
 * @param[in]   Sign		-	ǩ�����ݣ���ped_sm2_sign���ɣ�64�ֽ�
 * @param[in]   SignLen		-	�źŵĳ���
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       sm2 ˽Կ����
 * @param[in]   KeyIndex  - ��Կ����
 * @param[in]   input     - ��������
 * @param[in]   inputLen  - �������ݳ���
 * @param[out]  output    - �㻺�������Ա����������
 * @param[in]   outputLen - [in]  �����������С
 * @param[out]  outputLen - [out] ʵ��������ݵĳ���
 * @return      0      - �ɹ�
 *              ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
 * @brief       ����sm2��Կ
 * @param[in]   KeyIndex  - ��Կ����
 * @param[out]  PubKey    - �㻺�������湫Կ���ݣ�sizeof(SM2_PubKey_t) = 64+4�ֽ�
 * @param[in]   PubKeyLen - ����pubkey�Ļ�������С
 * @param[out]  PubKeyLen - ʵ��������ݵĳ���
 * @return      0      - �ɹ�
 * @return      ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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

#if 0 //SM4�ѳɼӽ��ܽӿڿ�ʹ��ped_symmetric_crypto�ӿ�
/**
@if Chinese
 * @brief       ͨ��SM4����/��������
 * @param[in]   Mode      - (SM4_DECRYPT or SM4_ENCRYPT) | (SM4_MODE_ECB or SM4_MODE_CBC)
 * @param[in]   IV        - ��ʼIV��������16�ֽ�
 * @param[in]   KeyLen    - SM4Key���ȣ�����Ϊ16
 * @param[in]   Key       - SM4��Կ
 * @param[in]   InLen     - ���볤�ȣ�����Ϊ16�ֽڵı�����ÿ��С��16KB
 * @param[in]   input     - Ҫ����/���ܵĵ㻺����
 * @param[out]  IV        - �ڵ��ô˺��������iv
 * @param[out]  output    - �㻺�������Ա������/��������
 * @return      0      - �ɹ�
 *              ����   - ʧ�ܣ�ʹ��errno��ȡ��ϸ��Ϣ
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
                 void          *output); //ȥ���˽ӿ�
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

