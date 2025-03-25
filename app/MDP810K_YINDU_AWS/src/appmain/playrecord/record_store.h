#ifndef __RECORD_STORE_H__
#define __RECORD_STORE_H__

#include "cJSON.h"
#include "appdef.h"

#define JSON_ITEM_MSGID         "ID"         //message id��Ψһ
#define JSON_ITEM_VMSG          "VM"         //������Ϣ����΢���տ�
#define JSON_ITEM_CODE          "PC"         //������ʽ
#define JSON_ITEM_TIM           "RT"         //��̨ʱ��
#define JSON_ITEM_MONEY         "AM"         //���
#define JSON_RCV_TIME           "RT"         //����ʱ��
#define JSON_RST_TIME           "PT"         //����ʱ��
#define JSON_ITEM_PLAY_OK       "PF"         //�Ƿ񲥱��ɹ�
#define JSON_ITEM_UPLOAD_FLAG   "UF"         //�Ƿ�������

#define RECORD_MAX_COUNT      (10)           //��ʷ��ѯ������ݴ�С  
#define RECORD_MAX_COUNT_2    (10)           //Ĭ�����洢���ݴ�С
//���׼�¼����״̬
typedef enum{
    RECORD_PLAY_NO = 0,
    RECORD_PLAY_YES = 1,
}RECORD_PLAY_STATUS;

//���׼�¼����״̬
typedef enum{
    RECORD_SEND_YES = 1,
    RECORD_SEND_NO = 0,
}RECORD_SEND_STATUS;

//���׼�¼����״̬
typedef enum{
    RECORD_SEND_TIME_TYPE   = 1, //��ʱ����
    RECORD_SEND_COUNT_TYPE  = 2, //�̶���������
}RECORD_SEND_type;

typedef enum{
	TIME_STAMP_TYPE_SEC  =0, 		//ʱ��� ��
	TIME_STAMP_TYPE_MSEC =1,		//ʱ��� ����
}TIME_STAMP_TYPE;

//��ʼ����¼����
void init_record_cjson(void);
//�Ƚ��Ƿ����ظ�ID
int record_compare_msgid( char * msgid);
//��¼���׼�¼
int record_manage_write(char * msgid, char* voiceMsg, char *money,int codeflag, char*playtime, int playstatus);
//int record_manage_write(char * msgid, char* voiceMsg, char *money,int codeflag,char *rcvtime);
//��ȡ����
cJSON *record_manage_read(int read_cnt, int *max_count);
//��ȡ�洢���ݼ�¼��
int record_get_count(void);
//������׼�¼
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