#include <stdio.h>
#include <errno.h>

#include "apppedex.h"

#include "logger.h"

int app_ped_des(const void *DataIn, void *DataOut, const void *DesKey, DES_TYPE DesType)
{
	int ret = 1;
	uint32_t mode = TDEA_NONE_CALL,keyLen = 16; 

	if(DesType == APP_DEA_DECRYPT || DesType == APP_TDEA_DECRYPT ||
		DesType == APP_TDEA_DECRYPT_24 ){
		mode = TDEA_DECRYPT_CALL;
	}else if(DesType == APP_DEA_ENCRYPT|| DesType == APP_TDEA_ENCRYPT||
		DesType == APP_TDEA_ENCRYPT_24 ){
		mode = TDEA_ENCRYPT_CALL;
	}else{
		mode = TDEA_NONE_CALL;
	}

	if(DesType == APP_DEA_DECRYPT || DesType == APP_DEA_ENCRYPT){
		keyLen = 8;
	}else if(DesType == APP_TDEA_DECRYPT || DesType == APP_TDEA_ENCRYPT){
		keyLen = 16;
	}else if(DesType == APP_TDEA_DECRYPT_24 || DesType == APP_TDEA_ENCRYPT_24){
		keyLen = 24;
	}
	
	
	if(keyLen == 8){
		ret = NPWOLF_DES(DataIn,DataOut,DesKey,mode);
	}else{
		ret = NPWOLF_TDEA(DataIn,DataOut,DesKey,keyLen,mode);
	}

	return ret;
}