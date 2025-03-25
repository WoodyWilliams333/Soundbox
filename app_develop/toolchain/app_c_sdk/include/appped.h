/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app pedģ��</strong> ��صĽӿ�
	 * @par �ļ�    appped.h
	 * @author		yangjing
	 * @date        2020-05-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-05-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-20    | 1.0.1        | liyanping     | ����Ӣ��ע��  
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
	@brief  д��MS��ϵ����Կ
 	@param[in]	destekyid	-	����Կ������
 	@param[in]	keylen 		-	����Կ����
	@param[in]	mastkey		-	����Կ����
	@return   �ο�SDK PED��ض���	
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
	@brief  д��MS��ϵpin��Կ
 	@param[in]	mode		-	�ο�sdk���ģʽ����
 	@param[in]	masterkeyid	-	����Կ������
 	@param[in]	pinkeyid	-	pin��Կ������
 	@param[in]	pinkeylen	-	pin��Կ����
	@param[in]	pinkey		-	pin��Կ����
	@return   �ο�SDK PED��ض���	
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
	@brief  д��MS��ϵmac��Կ
 	@param[in]	mode		-	�ο�sdk���ģʽ����
 	@param[in]	masterkeyid	-	����Կ������
 	@param[in]	mackeyid	-	mac��Կ������
 	@param[in]	mackeylen	-	mac��Կ����
	@param[in]	mackey		-	mac��Կ����
	@return   �ο�SDK PED��ض���	
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
	@brief  д��MS��ϵeak��Կ
 	@param[in]	mode		-	�ο�sdk���ģʽ����
 	@param[in]	masterkeyid	-	����Կ������
 	@param[in]	eakid		-	eak��Կ������
 	@param[in]	eaklen		-	eak��Կ����
	@param[in]	eak			-	eak��Կ����
	@return   �ο�SDK PED��ض���	
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
	@brief  ����mac
 	@param[in]	mode		-	�ο�sdk���ģʽ����
 	@param[in]	mackeyid	-	mac��Կ������
	@param[in]	datain		-	����������
	@param[in]	inlen		-	�����ݳ���
	@param[out]	macout		-	mac������
	@return   �ο�SDK PED��ض���	
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
	@brief   ɾ����Կ
 	@param[in]	keytype	-	��Կ���ͣ��ο�sdk ��Կ���Ͷ���
 	@param[in]	keyid	-	��Կ������
	@return  �ο�SDK PED��ض���		
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
	@brief   ��ȡ��ԿУ��ֵ
 	@param[in]	keytype		-	��Կ���ͣ��ο�sdk ��Կ���Ͷ���
 	@param[in]	KeyIndex	-	��Կ������
	@param[out]	KVC			-	kcv��������
	@return  �ο�SDK PED��ض���		
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
	@brief  �������ܿ�
 	@param[in]	x		-	���ܿ�����x������
	@param[in]	y		-	���ܿ�����y������
	@param[in]	width	-	���ܿ���
	@param[in]	height	-	���ܿ�߶�
	@return  �ο�SDK PED��ض���		
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
	@brief   pin���룬��ȡpinblock
 	@param[in]	keyid		-	��Կ������
 	@param[in]	format		-	pinblock��ʽ���ο�sdk����
	@param[in]	exppinlen	-	����pin���볤�ȣ��ɶ�����ȣ���ʽΪ"0,1,2,4,8...�����12
	@param[in]	pan			-	�˺����ݣ�����format��ʹ��	
	@param[out]	pinblock	-	pin����
	@return  �ο�SDK PED��ض���		
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
	@brief  ����Ƿ����������Կ
	@return  �ο�SDK PED��ض���		
@else
	@brief  Check whether UnionPay key exists
	@return  
			refer to the related definitions of SDK PED  
 @endif
 */

extern int app_ped_check_ans_key(void);


/**
 @if Chinese
	@brief  ��ȡָ���ֽ����������
 	@param[in]  bytes	-	����ȡ��������ֽ���
	@param[out] data	-	����������ַ
	@return  �ο�SDK PED��ض���		
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
	@brief   pes���ܼ���
 	@param[in]	keytype		-	��Կ���ͣ��ο�sdk��Կ���Ͷ���
	@param[in]	keyindex	-	��Կ������
	@param[in]	mode		-	����ģʽ���ο�sdkģʽ����
	@param[in]	datalen		-	�������ݳ���
	@param[in]	datain		-	����������
	@param[out]	outlen		-	���ܽ������
	@param[out]	dataout		-	���ܽ������
	@return  �ο�SDK PED��ض���		
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
	@brief  ������Կ���ܼ���
 	@param[in]	mode	-	����ģʽ���ο�sdkģʽ����
	@param[in]	iv		-	��ʼ����
	@param[in]	keylen	-	��Կ����
	@param[in]	key		-	��Կ����
	@param[in]	datalen	-	�������ݳ���
	@param[in]	indata	-	����������
	@param[out]	outdata	-	���ܽ������
	@return  �ο�SDK PED��ض���		
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
	@brief  rsa��Կ����
 	@param[in]	indata		-	����������
	@param[in]	inputlen	-	���������ݳ���
	@param[in]	pubkey		-	rsa ��Կ�ṹ���ο�sdk
	@param[out]	outdata		-	���ܽ������
	@param[out]	outlen		-	���ܽ������
	@return  �ο�SDK PED��ض���		
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
	@brief  AES����
 	@param[in]	Data		-	����������
	@param[in]	length		-	���������ݳ���
	@param[in]	mode		-	����ģʽ���ο�sdkģʽ����
	@param[in]	aeskey		-	aeskey����
	@param[out]	outdata		-	���ܽ������
	@param[out]	outlength	-	���ܽ������
	@return  �ο�SDK PED��ض���		
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
	@brief  �����Կ�Ƿ����
 	@param[in]	KeySystem	-	��Կ��ϵ���ο�sdk��ض���
	@param[in]	KeyType		-	��Կ���ͣ��ο�sdk��ض���
	@param[in]	KeyIndex	-	��Կ������
	@param[in]	Mode		-	ģʽ���ο�sdk���ģʽ����
	@return  �ο�SDK PED��ض���			
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

