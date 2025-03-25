#ifndef _TMS_SILENCE_H_
#define _TMS_SILENCE_H_

typedef void (*pTmsAutoTaskCb)(void);

//tms_app_download_ex 需要的参数结构体
typedef struct 
{
	struct timeval tBegin;  //计时开始时间
	unsigned long timeCount; //间隔时间
	uint8_t IsHold;  //是否暂停
	uint8_t IsReset;  //是否在更新TMS 提示用户更新时用到 不用于下载过程
	uint8_t Runing; //用于判断tms下载或者其他线程是否正在执行 防止线程未执行结束又开新线程
	uint8_t showProc;//是否显示下载过程 由应用控制
	uint8_t showTmsProc;//是否已经显示下载过程 由tms库控制
	
	uint8_t TmsUpdata;//是否可以更新 下载后的判断
	char *pAppDir;
	uint8_t UpdataNow;         //用于设置tms强制更新 不判断时间
}TimeArg;

void SetThreadArg(TimeArg pArg_temp);
void GetThreadArg(TimeArg *lpTimerArg);
void InitTmsTimeArg(int supsilence, const char *pAppDir);
int StartTmsService(pTmsAutoTaskCb pCbFunc);
void UpdateTmsTime(void);

#endif

