#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfiledef.h"
#include "terfileinter.h"


#define SUP_DEFAULT_PWD		"123456"
#define OPER_DEFAULT_PWD	"0000"

#define  DEFAULT_TELLER_NO	"\x01\x01\x01\x00"

int LoadDefaultOpers(void)
{	
	int i = 0;

	memset(&operStrc[0],0,sizeof(TELLER_STRC)*MAX_OPER_NUM);
	
	for(i = 0; i < 6; i++){
		snprintf(operStrc[i].szTellerNo, sizeof(operStrc[i].szTellerNo), "%03d", i);
	}

	for(i = 6; i < MAX_OPER_NUM; i++){
		snprintf(operStrc[i].szTellerNo, sizeof(operStrc[i].szTellerNo), "%s", DEFAULT_TELLER_NO);
	}
	
	snprintf(operStrc[0].szPassword, sizeof(operStrc[0].szPassword), "%s", SUP_DEFAULT_PWD);
	for(i = 1; i < MAX_OPER_NUM; i++){
		snprintf(operStrc[i].szPassword, sizeof(operStrc[i].szPassword), "%s", OPER_DEFAULT_PWD);
	}
		
	return 0;	
}

int SaveOpers(void)
{
	int ret = RET_OK;

	logger_debug("operstrc one size = %d, total size = %d\n", sizeof(TELLER_STRC), sizeof(operStrc));
	ret = SaveFileComm(OPER_FILE, operStrc, sizeof(operStrc));
	
	return ret;
}


int ReadSysOpers(void)
{
	int ret =RET_OK;
	logger_debug("operstrc one size = %d, total size = %d\n", sizeof(TELLER_STRC), sizeof(operStrc));
	ret = ReadFileComm(OPER_FILE, operStrc, sizeof(operStrc));

	//PrintrfAllOper();
	return ret;	
}

int LoadOpers(void)
{
	int iRet = 0;
	
	if( app_file_exists(OPER_FILE) < 0 ){
		iRet = LoadDefaultOpers();
		if( iRet == RET_OK){
			iRet = SaveOpers();
		}
	}
	else{
		iRet = ReadSysOpers();
	}

	//PrintrfAllOper();
	
	return iRet;	
}

