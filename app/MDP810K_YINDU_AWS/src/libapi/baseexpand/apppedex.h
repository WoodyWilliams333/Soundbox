#ifndef _APP_PED_EX_H_
#define _APP_PED_EX_H_

#include <ped.h>
#include <npwolf.h>

typedef enum{
	APP_DEA_ENCRYPT,	//��DES����
	APP_DEA_DECRYPT,	//��DES����
	APP_TDEA_ENCRYPT,	//˫������ԿDES����
	APP_TDEA_DECRYPT,	//˫������ԿDES����
	APP_TDEA_ENCRYPT_24,//��������ԿDES����
	APP_TDEA_DECRYPT_24	//��������ԿDES����
}DES_TYPE;

int app_ped_des(const void *DataIn, void *DataOut, const void *DesKey, DES_TYPE DesType);

#endif
