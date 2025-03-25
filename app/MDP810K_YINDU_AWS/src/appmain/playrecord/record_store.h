#ifndef __RECORD_STORE_H__
#define __RECORD_STORE_H__

#include "cJSON.h"
#include "appdef.h"

#define JSON_ITEM_MSGID         "ID"         //message id，唯一
#define JSON_ITEM_VMSG          "VM"         //播报信息，如微信收款
#define JSON_ITEM_CODE          "PC"         //播报方式
#define JSON_ITEM_TIM           "RT"         //后台时间
#define JSON_ITEM_MONEY         "AM"         //金额
#define JSON_RCV_TIME           "RT"         //接收时间
#define JSON_RST_TIME           "PT"         //播报时间
#define JSON_ITEM_PLAY_OK       "PF"         //是否播报成功
#define JSON_ITEM_UPLOAD_FLAG   "UF"         //是否已上送

#define RECORD_MAX_COUNT      (10)           //历史查询最大数据大小  
#define RECORD_MAX_COUNT_2    (10)           //默认最大存储数据大小
//交易记录播报状态
typedef enum{
    RECORD_PLAY_NO = 0,
    RECORD_PLAY_YES = 1,
}RECORD_PLAY_STATUS;

//交易记录上送状态
typedef enum{
    RECORD_SEND_YES = 1,
    RECORD_SEND_NO = 0,
}RECORD_SEND_STATUS;

//交易记录上送状态
typedef enum{
    RECORD_SEND_TIME_TYPE   = 1, //定时上送
    RECORD_SEND_COUNT_TYPE  = 2, //固定笔数上送
}RECORD_SEND_type;

typedef enum{
	TIME_STAMP_TYPE_SEC  =0, 		//时间戳 秒
	TIME_STAMP_TYPE_MSEC =1,		//时间戳 毫秒
}TIME_STAMP_TYPE;

//初始化记录数据
void init_record_cjson(void);
//比较是否有重复ID
int record_compare_msgid( char * msgid);
//记录交易记录
int record_manage_write(char * msgid, char* voiceMsg, char *money,int codeflag, char*playtime, int playstatus);
//int record_manage_write(char * msgid, char* voiceMsg, char *money,int codeflag,char *rcvtime);
//读取数据
cJSON *record_manage_read(int read_cnt, int *max_count);
//读取存储数据记录数
int record_get_count(void);
//清除交易记录
void clean_record(void);

void init_mqtt_ack_cjson(void);
int record_compare_mqttack_msgid( char * msgid);
int record_mqtt_ack_write(char * msgid);
void record_manage_update(const char *msgid, const char* tag, void *value);
void send_need_report_info(RECORD_SEND_type type);
//void get_report_start_tick(struct timeval *tick);
void set_report_start_tick(void);
void shutdown_save_record_file(void);
void get_timestamp(TIME_STAMP_TYPE type, char *timestamp, int size);
int record_get_read_count(void);
void auto_save_record_file(void);
void auto_save_record_ack_file(void);
#endif //__RECORD_STORE_H__