
#include <stdio.h>

#include "tersharedata.h"


char globaltimerstr[14+1] = {0};

char Cmd1[1000] = {0};
char Cmd2[1000] = {0};
char Cmd3[1000] = {0};

char Cmd1hash[100]= {0};



unsigned int global_ts = 0;

unsigned int global_ts1 = 0;
unsigned int global_ts2 = 0;
unsigned int global_ts3 = 0;


int globa_thread_logon = 0;

LOGONMQTTPARAM  RetryParam;

TELLER_STRC operStrc[MAX_OPER_NUM];

SYS_PARA_STRC stSysPara;
CTRL_PARA_STRC stCtrlPara;
SYS_TEMP_STRC stSysTemp;


TRANS_DATA_PARA_STRC stTransPara;
TRANS_CTRL_PARA_STRC stTransCtrl;

COMM_PARA_STRC stCommPara;
COMM_PARA_STRC stTmsCommPara;

ST_POS_VERSION stPosVersion;
CommBaseStation_t stBaseStation = {
	.stBaseStation = {0},
    .timeoutms = 4*1000,
};


