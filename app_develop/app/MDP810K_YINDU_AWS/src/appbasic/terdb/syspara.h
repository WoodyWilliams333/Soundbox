
#ifndef _SYS_PARA_H_
#define _SYS_PARA_H_

#include <appdatatypedef.h>

#define TERLLER_NO_LEN 	2
#define MAX_OPER_NUM	21


//Ĭ�ϰ����Ʒ���dns
#define MQTT_SERVER_AUTO_DNS        ".iot-as-mqtt.cn-shanghai.aliyuncs.com"   
//Ĭ�ϰ����Ʒ���˿�
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
	UPDATE_SELECT	= 0,  	//ѡ�����
	UPDATE_FORCE	= 1,	//ǿ�Ƹ���
} ota_update_type_t;

typedef enum{
	FN_PLAY_MODEL = 0, //������ʷģʽ
	FN_CHANGE_VOL = 1, //��������ģʽ
}FN_MODEL_ENUM;
typedef enum{
	WifiChanl_AP = 0,	//�ȵ�����
	WifiChanl_AIR,		//΢������
	NET_WIFI_2_4G,		//wifi�л���4G
	NET_4G_2_WIFI,		//4G�л���WIFI
	NET_CHECK_STATE,	//�������״̬
	WifiChanl_NON,
}WIFI_CHANL_AP_OR_AIR_ENUM;
#define  FN_MODEL_CHANGE_VOL_TIMEOUT (15*1000)  //����ģʽ������ʱʱ��
//Ĭ��������С 
#define VOL_DEFAULT		(20*3)
//��������ʱ����,��λs
#define CHK_NETWORK_TIME              (5*60)  
//��������쳣��ʱ����,��λs
#define CHK_NETWORK_ERROR_TIME        (60) 


typedef struct _teller_struct{
	char szTellerNo[4];
	char szPassword[13+1];	
}TELLER_STRC;
#define TELLER_STRC_SIZE sizeof(struct _teller_struct)

/*****************************************************
�������̻�ҵ������Ҫ�������ĵı���
******************************************************/
typedef struct _ctrl_para_struct{
	 
}CTRL_PARA_STRC;
#define CTRL_PARA_SIZE sizeof(CTRL_PARA_STRC)

/*****************************************************
ϵͳ�߼��п����ã����������ĵı���
******************************************************/
typedef struct _sys_para_struct{
	int iVolnume;					// ������С
	appbool bUpdateApp;				// �Ƿ�ɸ���Ӧ��(TMS������ɺ�����)
	appbool bUpdateAppAbs;			// �Ƿ�ǿ�Ƹ���Ӧ��(TMS������ɺ�����)
	int      ucOprtLimitTime;         
	//new add
	int volume;           // ����	1-10,��Ӧ�ײ�1-100
	unsigned short port;  //�˿�
	int NetChanlLTE;      //����ģʽ 4G/wifi
	appsw swTransSsl;     // �����Ƿ�����SSL
	unsigned char ucPlayNetStatus; //����ʱ�Ƿ񲥱���������
	char subTopic[128];
	int record_num;//�����ܱ��������ڲ���
	ota_update_type_t update_type;
	char product_key[64]; 	          
	char device_secret[64];          
	char device_name[64]; 
	int play_lang;           //���Ӣ���ӡ����ı�־ 0-Ӣ�� 
	char mer_name[65];      //�ͻ�������������
	/*Ԥ������*/
	uint8_t szRFU[200];			// �����ֶ�
}SYS_PARA_STRC;
#define SYS_PARA_SIZE sizeof(SYS_PARA_STRC)

/*****************************************************
ϵͳ�в���Ҫ�����ļ������ڴ�ʹ�õı���
******************************************************/
typedef struct _sys_temp_struct{
	TELLER_STRC EntryTeller; 			// ���ڵ�¼����Ա
	appbool bOperLoginFlag;				// ����Ա��¼��ʶ
	appbool bNeedDns;					// ���������Ƿ���ҪDNS
	int iChkUpdateAppPeriod;			// ����������TMS��������(��)
	unsigned int ChkUpdateAppTick;		// ����������TMS���µļ�ʱtick
	unsigned int HomeWinEnterTick;		// ������������ʱtick
	int iChkSimTimeout;					// ���SIM����ʱʱ�䣬��λ����
	appbool bSettleCancelEnable;		// ����ȡ��ʹ�ܱ�ʶ
	char szBaseStationDate[14+1];		// ��ȡ��վ��Ϣ��ʱ��

	appbool bMqttStopFlg;
       appbool bMqttStarted;
	appbool bMqttcloseFlg;

	uint8_t  mqttClientId[200];
	uint8_t  mqttUsername[200];
	uint8_t  mqttPassword[200];

	appbool bPlayConnecting;            //����"������������"
	appbool bPlayConnected;             //����"�������ӳɹ�"
	FN_MODEL_ENUM sFnModel;				//���ܼ�ģʽ
	//mqtt����
	char product_key[64]; 	            // ��Ʒkey
	char device_secret[64];             // �豸��Կ
	char device_name[64]; 	            // �豸��
	char server_url[256];               // ��������ַ

	char *ca;                         
	char *key;


	int ap_or_airkiss;					//wifi����ģʽ
	appbool changeingState; 		    //app_false�� app_true�������100%
	appbool bSaveRecord;                //���沥����¼���
	appbool bSaveRecordACK;             //����ack��¼���
}SYS_TEMP_STRC;

// �汾�ź�֤����
typedef struct _tag_POS_VERSION
{
	char       szVersion[10];            // �汾��
	char       szCertificate[10];        // ֤����
}ST_POS_VERSION;


//MQTT
typedef struct _logonmqttparam
{
	int retryCount;
	int retryInterval;
}LOGONMQTTPARAM;


SYS_PARA_STRC *Get_SysPara(void);


#endif

