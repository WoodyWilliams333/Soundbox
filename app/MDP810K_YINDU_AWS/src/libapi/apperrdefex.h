
#ifndef _APP_ERR_DEF_EX_H_
#define _APP_ERR_DEF_EX_H_

#include <apperrdef.h>

typedef enum{
	E_ELE_SIGN_TIMEOUT = -(R_BASE + 1),
	E_CTL_RETRY 	   = -(R_BASE + 2),	//非接读卡需要重试
}E_APP_RET_EX;

#endif
