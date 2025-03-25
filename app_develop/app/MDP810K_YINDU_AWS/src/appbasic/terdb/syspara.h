
#ifndef _SYS_PARA_H_
#define _SYS_PARA_H_

#include <appdatatypedef.h>

#define TERLLER_NO_LEN 	2
#define MAX_OPER_NUM	21


//默认阿里云服务dns
#define MQTT_SERVER_AUTO_DNS        ".iot-as-mqtt.cn-shanghai.aliyuncs.com"   
//默认阿里云服务端口
#define MQTT_SERVER_AUTO_PORT       (443) 

#define get_mem_info() \
{\
    uint32_t total_heap_mem;\
    uint32_t available_heap_mem;\
    uint32_t max_available_heap_mem_blk;\
\
    syscall_get_free_mem(&total_heap_mem, &available_heap_mem, &max_available_heap_mem_blk);\
    logger_debug("total=%d available=%d  max_available=%d\r\n", total_heap_mem, available_heap_mem, max_available_heap_mem_blk);\
}
typedef enum ota_update_type {
	UPDATE_SELECT	= 0,  	//选择更新
	UPDATE_FORCE	= 1,	//强制更新
} ota_update_type_t;

typedef enum{
	FN_PLAY_MODEL = 0, //播放历史模式
	FN_CHANGE_VOL = 1, //调整音量模式
}FN_MODEL_ENUM;
typedef enum{
	WifiChanl_AP = 0,	//热点配网
	WifiChanl_AIR,		//微信配网
	NET_WIFI_2_4G,		//wifi切换到4G
	NET_4G_2_WIFI,		//4G切换到WIFI
	NET_CHECK_STATE,	//检查网络状态
	WifiChanl_NON,
}WIFI_CHANL_AP_OR_AIR_ENUM;
#define  FN_MODEL_CHANGE_VOL_TIMEOUT (15*1000)  //音量模式操作超时时间
//默认声音大小 
#define VOL_DEFAULT		(20*3)
//检查网络的时间间隔,单位s
#define CHK_NETWORK_TIME              (5*60)  
//检查网络异常的时间间隔,单位s
#define CHK_NETWORK_ERROR_TIME        (60) 


typedef struct _teller_struct{
	char szTellerNo[4];
	char szPassword[13+1];	
}TELLER_STRC;
#define TELLER_STRC_SIZE sizeof(struct _teller_struct)

/*****************************************************
控制流程或业务中需要经常更改的变量
******************************************************/
typedef struct _ctrl_para_struct{
	 
}CTRL_PARA_STRC;
#define CTRL_PARA_SIZE sizeof(CTRL_PARA_STRC)

/*****************************************************
系统逻辑中可设置，不经常更改的变量
******************************************************/
typedef struct _sys_para_struct{
	int iVolnume;					// 音量大小
	appbool bUpdateApp;				// 是否可更新应用(TMS下载完成后设置)
	appbool bUpdateAppAbs;			// 是否强制更新应用(TMS下载完成后设置)
	int      ucOprtLimitTime;         
	//new add
	int volume;           // 音量	1-10,对应底层1-100
	unsigned short port;  //端口
	int NetChanlLTE;      //网络模式 4G/wifi
	appsw swTransSsl;     // 播报是否启用SSL
	unsigned char ucPlayNetStatus; //待机时是否播报断网重连
	char subTopic[128];
	int record_num;//播报总笔数，用于测试
	ota_update_type_t update_type;
	char product_key[64]; 	          
	char device_secret[64];          
	char device_name[64]; 
	int play_lang;           //添加英语和印度语的标志 0-英语 
	char mer_name[65];      //客户用作银行名称
	/*预留数据*/
	uint8_t szRFU[200];			// 备用字段
}SYS_PARA_STRC;
#define SYS_PARA_SIZE sizeof(SYS_PARA_STRC)

/*****************************************************
系统中不需要保存文件，仅内存使用的变量
******************************************************/
typedef struct _sys_temp_struct{
	TELLER_STRC EntryTeller; 			// 正在登录操作员
	appbool bOperLoginFlag;				// 操作员登录标识
	appbool bNeedDns;					// 本次连接是否需要DNS
	int iChkUpdateAppPeriod;			// 待机界面检查TMS更新周期(秒)
	unsigned int ChkUpdateAppTick;		// 待机界面检查TMS更新的计时tick
	unsigned int HomeWinEnterTick;		// 进入待机界面计时tick
	int iChkSimTimeout;					// 检测SIM卡超时时间，单位是秒
	appbool bSettleCancelEnable;		// 结算取消使能标识
	char szBaseStationDate[14+1];		// 获取基站信息的时间

	appbool bMqttStopFlg;
       appbool bMqttStarted;
	appbool bMqttcloseFlg;

	uint8_t  mqttClientId[200];
	uint8_t  mqttUsername[200];
	uint8_t  mqttPassword[200];

	appbool bPlayConnecting;            //播报"正在连接网络"
	appbool bPlayConnected;             //播报"网络连接成功"
	FN_MODEL_ENUM sFnModel;				//功能键模式
	//mqtt参数
	char product_key[64]; 	            // 产品key
	char device_secret[64];             // 设备秘钥
	char device_name[64]; 	            // 设备名
	char server_url[256];               // 服务器地址

	char *ca;                         
	char *key;


	int ap_or_airkiss;					//wifi配网模式
	appbool changeingState; 		    //app_false， app_true插入充满100%
	appbool bSaveRecord;                //保存播报记录标记
	appbool bSaveRecordACK;             //保存ack记录标记
}SYS_TEMP_STRC;

// 版本号和证书编号
typedef struct _tag_POS_VERSION
{
	char       szVersion[10];            // 版本号
	char       szCertificate[10];        // 证书编号
}ST_POS_VERSION;


//MQTT
typedef struct _logonmqttparam
{
	int retryCount;
	int retryInterval;
}LOGONMQTTPARAM;


SYS_PARA_STRC *Get_SysPara(void);


#endif

