/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app ped模块</strong> 相关的接口
	 * @par 文件    appped.h
	 * @author		yangjing
	 * @date        2020-05-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-05-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-20    | 1.0.1        | liyanping     | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app ped</strong>  module
	 * @par file    appped.h
	 * @author		yangjing
	 * @date        2020-05-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-05-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-20    | 1.0.1        | liyanping     | Add English description
 @endif
*/

/*!
 @if Chinese
	* @addtogroup appped ped
 @else 
	* @addtogroup appped ped
 @endif 
 * @{
*/

#ifndef _APP_PED_H_
#define _APP_PED_H_

#include <ped.h>
/**
 @if Chinese
	@brief  写入MS体系主密钥
 	@param[in]	destekyid	-	主密钥索引号
 	@param[in]	keylen 		-	主密钥长度
	@param[in]	mastkey		-	主密钥明文
	@return   参考SDK PED相关定义	
@else
	@brief  Write master key into MS system   
	@param[in]	destekyid	-	the key index of masterkey
 	@param[in]	keylen		-	the key length of masterkey 
	@param[in]	mastkey		-	the plaintext of masterkey
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */
extern int app_ped_write_masterkey(int destekyid, int keylen, uint8_t *mastkey);


/**
 @if Chinese
	@brief  写入MS体系pin密钥
 	@param[in]	mode		-	参考sdk相关模式定义
 	@param[in]	masterkeyid	-	主密钥索引号
 	@param[in]	pinkeyid	-	pin密钥索引号
 	@param[in]	pinkeylen	-	pin密钥长度
	@param[in]	pinkey		-	pin密钥数据
	@return   参考SDK PED相关定义	
@else
	@brief  Write pinkey into MS system
	@param[in]	mode		-	Refer to SDK related definitions of mode
 	@param[in]	masterkeyid -	the key index of masterkey 
	@param[in]	pinkeyid	-	the key index of pinkey
 	@param[in]	pinkeylen	-	the key length of pinkey 
	@param[in]	pinkey		-	the key data of pinkey
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_write_pinkey(uint32_t mode, int masterkeyid, int pinkeyid, int pinkeylen, uint8_t *pinkey);
 
/**
 @if Chinese
	@brief  写入MS体系mac密钥
 	@param[in]	mode		-	参考sdk相关模式定义
 	@param[in]	masterkeyid	-	主密钥索引号
 	@param[in]	mackeyid	-	mac密钥索引号
 	@param[in]	mackeylen	-	mac密钥长度
	@param[in]	mackey		-	mac密钥数据
	@return   参考SDK PED相关定义	
@else
	@brief  Write mackey into MS system
	@param[in]	mode		-	Refer to SDK related definitions of mode
 	@param[in]	masterkeyid	-	the key index of masterkey 
	@param[in]	mackeyid	-	the key index of mackey
 	@param[in]	mackeylen	-	the key length of mackey 
	@param[in]	mackey		-	the key data of mackey
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */  
extern int app_ped_write_mackey(uint32_t mode, int masterkeyid, int mackeyid, int mackeylen, uint8_t *mackey);

/**
 @if Chinese
	@brief  写入MS体系eak密钥
 	@param[in]	mode		-	参考sdk相关模式定义
 	@param[in]	masterkeyid	-	主密钥索引号
 	@param[in]	eakid		-	eak密钥索引号
 	@param[in]	eaklen		-	eak密钥长度
	@param[in]	eak			-	eak密钥数据
	@return   参考SDK PED相关定义	
@else
	@brief  Write eakkey into MS system
	@param[in]	mode		-	Refer to SDK related definitions of mode
 	@param[in]	masterkeyid	-	the key index of masterkey 
	@param[in]	eakid		-	the key index of eakkey
 	@param[in]	eaklen		-	the key length of eakkey 
	@param[in]	eak			-	the key data of eakkey
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */   
extern int app_ped_write_eak(uint32_t mode, int masterkeyid, int eakid, int eaklen, uint8_t *eak);

/**
 @if Chinese
	@brief  计算mac
 	@param[in]	mode		-	参考sdk相关模式定义
 	@param[in]	mackeyid	-	mac密钥索引号
	@param[in]	datain		-	待计算数据
	@param[in]	inlen		-	待数据长度
	@param[out]	macout		-	mac计算结果
	@return   参考SDK PED相关定义	
@else
	@brief  calculate  mac
	@param[in]	mode		-	Refer to SDK related definitions of mode 		
	@param[in]	mackeyid	-	the key index of mackey
 	@param[in]	datain		-	Data to be calculated
	@param[in]	inlen		-	the length of data to be calculated
	@param[out]	macout		-	the calculated result of mac
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */   
extern int app_ped_calc_mac(int mackeyid, uint8_t *datain, int inlen, uint32_t mode, uint8_t *macout);


/**
 @if Chinese
	@brief   删除密钥
 	@param[in]	keytype	-	密钥类型，参考sdk 密钥类型定义
 	@param[in]	keyid	-	密钥索引号
	@return  参考SDK PED相关定义		
@else
	@brief  delete the key
	@param[in]	keytype	-	For key type, refer to SDK key type definition
 	@param[in]	keyid	-	the key index 
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_del_key(int keytype,    int keyid);

 /**
 @if Chinese
	@brief   获取密钥校验值
 	@param[in]	keytype		-	密钥类型，参考sdk 密钥类型定义
 	@param[in]	KeyIndex	-	密钥索引号
	@param[out]	KVC			-	kcv保存数组
	@return  参考SDK PED相关定义		
@else
	@brief  get keycheck value 
	@param[in]	keytype		-	For key type, refer to SDK key type definition
 	@param[in]	KeyIndex	-	the key index 
	@param[out] KVC			-	the array to save keycheck value
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_get_kcv(uint32_t keytype, uint32_t KeyIndex, uint8_t KVC[4]);


/**
 @if Chinese
	@brief  设置输密框
 	@param[in]	x		-	输密框左上x轴坐标
	@param[in]	y		-	输密框左上y轴坐标
	@param[in]	width	-	输密框宽度
	@param[in]	height	-	输密框高度
	@return  参考SDK PED相关定义		
@else
	@brief  Set input password box
	@param[in]	x		-	upper left position of password box on X axis
	@param[in]	y		-	upper left position of password box on Y axis
	@param[in]	width	-	the width of password box
	@param[in]	height	-	the height of password box
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_set_input_region(int x, int y, int width, int height);

 /**
 @if Chinese
	@brief   pin输入，获取pinblock
 	@param[in]	keyid		-	密钥索引号
 	@param[in]	format		-	pinblock格式，参考sdk定义
	@param[in]	exppinlen	-	期望pin输入长度，可多个长度，格式为"0,1,2,4,8...“，最长12
	@param[in]	pan			-	账号数据，部分format中使用	
	@param[out]	pinblock	-	pin密文
	@return  参考SDK PED相关定义		
@else
	@brief  input pin and get the pinblock 
	@param[in]	keyid		-	the key index 
 	@param[in]	format		-	the format of pinblock,refer to the definition of sdk
	@param[in]	exppinlen	-	It is expected that the pin input length can be multiple, with the format of "0,1,2,4,8...", and the maximum length is 12
	@param[in]	pan			-	Account data, used in some formats
	@param[out] pinblock	-	the ciphertext of pin
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */  
extern int app_ped_get_pin(int keyid, int format, const char *exppinlen, const char *pan, uint8_t *pinblock);

 /**
 @if Chinese
	@brief  检测是否存在银联密钥
	@return  参考SDK PED相关定义		
@else
	@brief  Check whether UnionPay key exists
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */

extern int app_ped_check_ans_key(void);


/**
 @if Chinese
	@brief  获取指定字节数的随机数
 	@param[in]  bytes	-	欲获取随机数的字节数
	@param[out] data	-	随机数保存地址
	@return  参考SDK PED相关定义		
@else
	@brief  Gets the random number of the specified number of bytes
	@param[in]	bytes	-	Number of bytes to get random number
	@param[out]	data	-	storage address to save Random number 
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_get_random_spec(int bytes, void *data);

/**
 @if Chinese
	@brief   pes加密计算
 	@param[in]	keytype		-	密钥类型，参考sdk密钥类型定义
	@param[in]	keyindex	-	密钥索引号
	@param[in]	mode		-	加密模式，参考sdk模式定义
	@param[in]	datalen		-	加密数据长度
	@param[in]	datain		-	待加密数据
	@param[out]	outlen		-	加密结果长度
	@param[out]	dataout		-	加密结果数据
	@return  参考SDK PED相关定义		
@else
	@brief   PES encryption calculation
 	@param[in]	keytype		-	For key type, refer to the key type definition in SDK 
	@param[in]	keyindex	-	the key index 
	@param[in]	mode		-	Encryption mode, refer to mode definition in SDK
	@param[in]	datalen		-	Length of data to be encrypted
	@param[in]	datain		-	data to be encrypted
	@param[out] outlen		-	the length of Encryption result 
	@param[out] dataout		-	Encryption result
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */  
extern int app_ped_crypto(uint32_t keytype, uint32_t keyindex, uint32_t mode,
		uint32_t datalen, const void *datain, uint32_t *outlen, void *dataout);

 /**
 @if Chinese
	@brief  明文密钥加密计算
 	@param[in]	mode	-	加密模式，参考sdk模式定义
	@param[in]	iv		-	初始向量
	@param[in]	keylen	-	密钥长度
	@param[in]	key		-	密钥明文
	@param[in]	datalen	-	加密数据长度
	@param[in]	indata	-	待加密数据
	@param[out]	outdata	-	加密结果数据
	@return  参考SDK PED相关定义		
@else
	@brief   Encryption calculation by plaintext key
 	@param[in]	mode	-	Encryption mode, refer to mode definition in SDK 
	@param[in]	iv		-	Initial vector
	@param[in]	keylen	-	the length of key
	@param[in]	key		-	the plaintext of Key 
	@param[in]	datalen	-	the length of data to be encrypted
	@param[in]	indata	-	data to be encrypted
	@param[out]	outdata	-	Encryption result
	@return  refer to the related definitions of SDK PED  
 @endif
 */
extern int app_ped_cryto_key(uint32_t mode, uint8_t *iv, uint8_t keylen, uint8_t *key,
	uint32_t datalen, uint8_t* indata, uint8_t* outdata);
 
/**
@if Chinese
	@brief  rsa公钥计算
 	@param[in]	indata		-	待加密数据
	@param[in]	inputlen	-	待加密数据长度
	@param[in]	pubkey		-	rsa 公钥结构，参考sdk
	@param[out]	outdata		-	加密结果数据
	@param[out]	outlen		-	加密结果长度
	@return  参考SDK PED相关定义		
@else
	@brief  Calculate with RSA public key
 	@param[in]	indata		-	data to be encrypted
	@param[in]	inputlen	-	the length of data to be encrypted
	@param[in]	pubkey		-	RSA public key structure, refer to SDK
	@param[out]	outdata		-	Encryption result
	@param[out]	outlen		-	the length of Encryption result 
	@return  refer to the related definitions of SDK PED  
 @endif
 */
extern int app_ped_rsa_publickey_calc(void *outdata, uint32_t *outlen, const void *indata, uint32_t inputlen, const RsaPublicKey_t *pubkey);

/**
@if Chinese
	@brief  AES计算
 	@param[in]	Data		-	待加密数据
	@param[in]	length		-	待加密数据长度
	@param[in]	mode		-	加密模式，参考sdk模式定义
	@param[in]	aeskey		-	aeskey明文
	@param[out]	outdata		-	加密结果数据
	@param[out]	outlength	-	加密结果长度
	@return  参考SDK PED相关定义		
@else
	@brief  Calculate with AES algorithm
 	@param[in]	Data		-	data to be encrypted
	@param[in]	length		-	the length of data to be encrypted
	@param[in]	mode		-	Encryption mode, refer to mode definition in SDK
	@param[in]	aeskey		-	the key plaintext of aeskey
	@param[out]	outdata		-	Encryption result
	@param[out]	outlength	-	the length of Encryption result 
	@return  refer to the related definitions of SDK PED  
 @endif
 */ 
extern int app_ped_aes_key(char* Data,int length,int mode,char * aeskey,char* outdata,int* outlength);

 /**
 @if Chinese
	@brief  检测密钥是否存在
 	@param[in]	KeySystem	-	密钥体系，参考sdk相关定义
	@param[in]	KeyType		-	密钥类型，参考sdk相关定义
	@param[in]	KeyIndex	-	密钥索引号
	@param[in]	Mode		-	模式，参考sdk相关模式定义
	@return  参考SDK PED相关定义			
@else
	@brief   Check whether the key is existed
 	@param[in]	KeySystem	-	For the key system, refer to the relevant definitions of SDK
	@param[in]	KeyType		-	For key type, refer to the related definitions of SDK
	@param[in]	KeyIndex	-	the key index
	@param[in]	Mode		-	Mode, refer to the related mode definitions of SDK
	@return  
			refer to the related definitions of SDK PED
 @endif
 */
extern int app_ped_check_key_exist(KeySystem_t KeySystem, uint32_t KeyType, uint32_t KeyIndex, uint32_t Mode);

#endif

