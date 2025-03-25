#ifndef _APP_PED_EX_H_
#define _APP_PED_EX_H_

#include <ped.h>
#include <npwolf.h>

typedef enum{
	APP_DEA_ENCRYPT,	//单DES加密
	APP_DEA_DECRYPT,	//单DES解密
	APP_TDEA_ENCRYPT,	//双倍长密钥DES加密
	APP_TDEA_DECRYPT,	//双倍长密钥DES解密
	APP_TDEA_ENCRYPT_24,//三倍长密钥DES加密
	APP_TDEA_DECRYPT_24	//三倍长密钥DES解密
}DES_TYPE;

int app_ped_des(const void *DataIn, void *DataOut, const void *DesKey, DES_TYPE DesType);

#endif
