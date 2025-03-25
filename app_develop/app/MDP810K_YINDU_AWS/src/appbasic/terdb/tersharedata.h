
#ifndef _TER_SHARED_DATA_H_
#define _TER_SHARED_DATA_H_

#include <wnet.h>
#include "syspara.h"
#include "tercommpara.h"
#include "transpara.h"
#include "communication.h"



extern char globaltimerstr[14+1];

extern unsigned int global_ts;

extern unsigned int global_ts1;
extern unsigned int global_ts2;
extern unsigned int global_ts3;


extern int retryCount;
extern int retryInterval;	

extern int globa_thread_logon;
extern LOGONMQTTPARAM  RetryParam;


extern char Cmd1[1000];
extern char Cmd2[1000];
extern char Cmd3[1000];


extern char Cmd1hash[100];
extern TELLER_STRC operStrc[MAX_OPER_NUM];

extern SYS_PARA_STRC stSysPara;
extern CTRL_PARA_STRC stCtrlPara;
extern SYS_TEMP_STRC stSysTemp;


extern TRANS_DATA_PARA_STRC stTransPara;
extern TRANS_CTRL_PARA_STRC stTransCtrl;

extern COMM_PARA_STRC stCommPara;

extern ST_POS_VERSION stPosVersion;
extern CommBaseStation_t stBaseStation;

#endif
