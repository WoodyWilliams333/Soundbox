
#ifndef _MDP810_MQTT_REPORT_H
#define _MDP810_MQTT_REPORT_H


#ifdef __cplusplus
	extern "C" {
#endif


typedef struct RetInfo{
	char core_version[32];
	char verify_version[32];
	char sdk_version[32];
	char app_version[32];
	char in_flash_free_size[16];
	char out_flash_free_size[16];
	char ram_free_size[16];
	char battery_inf[16];
	char wireless_inf[100];
	
	//基站信息
	char lac[32];
	char cellid[32];
	char signal[32];
	char mnc[32];
	char mcc[32];
}net_lbsInfo;//MQTT_RET_INFO;


typedef struct 
{
	char request_id[50];
	char biz_type[5];
	char rst_time[35+1];
	char codes[5];
}task_cmd_struct;


#define EVT_REPORT_RES   '1'//播报结果回执
#define EVT_GET_INFO   'A'//获取设备状态
#define EVT_REPORT_POST   'P'//回执AZURE平台直接方法
#define DOWN_BANK_NAME   'D'//银行名称下载
#define DOWN_AUDIO_FILE   'F'//语音文件下载

#define UPLOAD_AUDIOPLAY_RESULT //是否上送播报结果




int DealRetInfo(task_cmd_struct * evt_node);

net_lbsInfo *get_mqtt_report_struct(void);


char * PubTerm_ReportInfo(char *requestId,char *rst,char *res);



//#endif
#ifdef __cplusplus
	}/*"C" */
#endif
	
#endif   /*DATACALL_DEMO_H*/



