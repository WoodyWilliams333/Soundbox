#include <stdio.h>
#include <system.h>
#include <libwnet.h>
#include <wnet.h>
#include <apperrdef.h>
#include <pahomqtt.h>
#include <appdatatypedef.h>
#include <appwifi.h>
#include <appsys.h>
#include <wnet.h>
#include <time.h>
#include <os_pthread.h>
#include "basicext.h"
#include "appdef.h"
#include "cJSON.h"
#include "tts_play.h"
#include "task_thread.h"
#include "record_store.h"
#include "fixaudio.h"
#include "tts_play.h"
#include "appgprs.h"
#include <sys/vfs.h>
#include <net_work.h>
#include <wnet.h>
#include <semaphore.h>
#include "mqtt_timer.h"
#include "syspara.h"
#include "tersharedata.h"
#include "pahomqtt.h"
#include "mqtt_payload_func.h"
#include "ota_http_upgrade.h"
#include "aiot_mqtt.h"
#include "codestool.h"

#include "logger.h"
#include "np_led.h"

extern int CheckCommStatus(CommType_e commType, appbool bWait);

uint8_t ltopicbase[1000];
uint8_t lkltopic[1000];
char localIp[15+1] = {0};
int giNoPppdTime=-1;

#define KERNEL_COMPILE              "kernelcompile"
#define FW_VER_TAG                  "image ver::"

MqttObj* mqtt = NULL;

//aws
//#define AWS_ADDR         "a2kmdwakmwgldt-ats.iot.ap-south-1.amazonaws.com"//系统部AWS账号
#define AWS_ADDR         "a35px956ax88xt-ats.iot.ap-south-1.amazonaws.com"//印度客户AWS账号
#define AWS_PORT         8883
#define SERVER_UER_CERT  APP_FILE_PATH"/User.crt"
#define SERVER_UER_KEY   APP_FILE_PATH"/Private"
#define SERVER_CA_CERT   APP_FILE_PATH"/CA.pem"


const char aws_root_cert[] = 
{

"-----BEGIN CERTIFICATE-----\r\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\r\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\r\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\r\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\r\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\r\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\r\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\r\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\r\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\r\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\r\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\r\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\r\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\r\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\r\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\r\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\r\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\r\n" \
"-----END CERTIFICATE-----"
};



#if 0
typedef struct{
	char request_id[50];
	char biz_type[50];
	char broadcast_type[50];
	char timestamp[15+1]; 
	char rcv_time[35+1];
	char rst_time[35+1];
	char money[15+1]; //以分为单位的金额
	char tts_playdata[600];
	char mqtt_topic[150];
	int condingFlag;
}Tts_Data_UNION;
Tts_Data_UNION g_tts_data;
#endif

//#define HEARTBEAT_SEC           (5*60)  //检查网络的时间间隔,单位s
#define HEARTBEAT_SEC           (60)  //MQTT心跳时间 单位s

#define EVT_GET_INFO   'A'//获取设备状态
#define EVT_SET_MCHR   'D'//设置商户名称

#define NET_ERR_MAX_TIME (60)
static mqtt_timer mqttTimer = {
        .alivable = app_false,
        .fun = NULL,
        .jiffies = NET_ERR_MAX_TIME
    };
//4g mqtt 重连使用参数
#define STEP_TIME (60*1000)
#define MAX_TIME (5*60*1000)
static sem_handle_t g_mqtt_recon_sem = NULL;
static long g_mqtt_recon_sem_time = 0;
static appbool set_sem_flag = app_true;

//MqttObj* mqtt = NULL;
mqtt_param_t glmqttpara = {0};
static appbool palyFlag = app_true;
char subTopic[250] = {0};
char clientId[150] = {0};
char username[65]  = {0};
char password[65]  = {0};
char reportTopic[250] = {0};
char uploadTopic[250] = {0};
char subTopicUpgrade[250] = {0};
char subTopicUpgrade2[250] = {0};
char pubTopicDownLoad[250] = {0};
char pubTopicInform[250] = {0};
char pubTopicDevInfo[250] = {0};

uint32_t pubid = 1;
void send_report_res(const char* message);
int check_ack_fail(char *data);
extern int aiotMqttSign(const char *productKey, const char *deviceName, const char *deviceSecret, 
                     char *clientId, char *username, char *password);
extern int aiotMqttSignSecureMode2(const char *productKey, const char *deviceName, const char *deviceSecret, 
					  char clientId[150], char username[64], char password[65]);

extern int CheckWirelessStatus(appbool bWait);

appbool get_matt_connect_state(void)
{
	if(AppGetMQTTStatus(mqtt) == E_MQTT_CONNECTED || AppGetMQTTStatus(mqtt) == E_MQTT_YIELD){
		logger_debug("app_true\n");
		return app_true;
	}else{
		logger_debug("app_false\n");
		return app_false;
	}
}
appbool get_mqtt_disconnect_state(void)
{
	if(AppGetMQTTStatus(mqtt) == E_MQTT_IDEL){
		return app_true;
	}else{
		return app_false;
	}
}

int checknetok(void)
{
	int ret = 0;
	static struct timeval start_tick = {0,0};

	ret = chk_net_play_status(app_false, app_false);
	logger_debug("[%s] checknetok =%d;\n", __FUNCTION__ , ret);
    if(RET_OK == ret){
        ret = 1;
		start_tick.tv_sec = 0;
    }else{
        ret = 0;
		if(0 == start_tick.tv_sec){
			gettimeofday(&start_tick, NULL);
		}else if(pub_check_timems_out(&start_tick, CHK_NETWORK_ERROR_TIME * 1000)){
			put_net_sem();
			logger_debug("put_net_sem\n");
			start_tick.tv_sec = 0;
		}
		
    }
	// 如果是需要关闭MQTT则直接返回网络检测成功，否则mqtt库会死循环导致stop mqtt接口卡死
	if (stSysTemp.bMqttStopFlg) {
		ret = 1;
		start_tick.tv_sec = 0;
	}
	return ret;
}


void *get_mqtt_ins(void)
{
	return mqtt;

}


int pub_term_step(void)
{
	cJSON *root = NULL;
	cJSON *params = NULL;
	char * pout;
	int rc = 0;

	logger_debug("[%s] pub_term_step pubid=%d;\n", __FUNCTION__,pubid);
	if(stSysTemp.bMqttStarted == app_false)
		return -1;
	//update version for OTA start
	root = cJSON_CreateObject();
	if (root==NULL) 
		return -1;
	cJSON_AddItemToObject(root, "id", cJSON_CreateNumber(pubid++));
	params = cJSON_CreateObject();
	if (params==NULL)
	{
		cJSON_Delete(root);
		return -1;	
	}

	cJSON_AddItemToObject(params, "step", cJSON_CreateString("100"));
	cJSON_AddItemToObject(params, "desc", cJSON_CreateString("download successful"));
	cJSON_AddItemToObject(root, "params", params);
	pout = cJSON_PrintUnformatted(root);
	cJSON_Delete(root);
	logger_debug("PubTermDownStep:%s;\n",pout);

	rc = AppMQTTPublish(mqtt,Mqtt_QOS0,pubTopicDownLoad, pout);
	free(pout);
	return rc;
}

int pub_ver_info(void)
{
	cJSON *root = NULL;
	cJSON *params = NULL;
	char * pout;
	uint8_t icCid[20+1] = {0};
	int rc = 0;
	
	if(stSysTemp.bMqttStarted == app_false)
		return -1;
	//update version for OTA start
	root = cJSON_CreateObject();
	if (root==NULL) 
		return -1;
	cJSON_AddItemToObject(root, "id", cJSON_CreateNumber(pubid++));
	params = cJSON_CreateObject();
	if (params==NULL)
	{
		cJSON_Delete(root);
		return -1;	
	}

	cJSON_AddItemToObject(params, "version", cJSON_CreateString(APP_MAIN_VER));
	cJSON_AddItemToObject(params, "productKey", cJSON_CreateString(stSysTemp.product_key));
	cJSON_AddItemToObject(params, "deviceName", cJSON_CreateString(stSysTemp.device_name));
	app_wireless_read_simcard_id((char*)icCid, sizeof(icCid));
	cJSON_AddItemToObject(params, "iccid", cJSON_CreateString((char *)icCid));
	cJSON_AddItemToObject(root, "params", params);
	pout = cJSON_PrintUnformatted(root);
	cJSON_Delete(root);
	logger_debug("pubTopicInform:[%s]\n", pubTopicInform);
	logger_debug("pout:[%s]\n", pout);
	rc = AppMQTTPublish(mqtt,Mqtt_QOS0, pubTopicInform, pout);
	free(pout);
	
	return rc;
}
#ifdef UPLOAD_DEV_INFO
/**
 * @brief 获取设备信息上送
 * @param[in] root 待解析json
 * @return void 
 */

int GetfwVer(char *in,char *out,int outsize)
{
	char *p=NULL;
	char *q=NULL;
	int len=0;
	if(in==NULL||out==NULL)
		return FALSE;
	
	p=strstr(in,FW_VER_TAG);
	if(p==NULL)
		return FALSE;
	p=p+strlen(FW_VER_TAG);
	
	q=strchr(p,' ');
	if(q==NULL)
		return FALSE;
	
	len=q-p+1;
	if(len>outsize-1)
		return FALSE;
	
	snprintf(out,len,"%s",p);
	return TRUE;
}

int get_battery_percent(void)
{
	int ret=-1;
	sys_battery_info_t battery_info;

	memset(&battery_info,0,sizeof(sys_battery_info_t));
	ret=sys_get_battery_info(&battery_info);
	if(ret!=0)
		return -1;
	if(battery_info.percent>100)
		return -1;
	logger_debug("get_battery_percent,percent=%d\n",battery_info.percent); 
	return battery_info.percent;
}


void send_hardware_info(char *reqid, char *type)
{
	cJSON*root = NULL;
	cJSON*baseStation = NULL;
	int ret = 0;
	char buff[256] = {0};
	char buff1[50] = {0};
	int temp = 0;
	char *sendbuff = NULL;
	tBaseStationExt stBaseStationExt;
	TERMINALINFO terminal;
	unsigned int freesize = 0;
	struct statfs sys_statfs;
	int signal = 0;
	int count=0;	
	
	logger_debug("%s\n", __FUNCTION__); 
	
	root = cJSON_CreateObject();
	if(NULL == root){
		return ;
	}
	if(NULL == reqid){
		get_timestamp(TIME_STAMP_TYPE_MSEC, buff, sizeof(buff));
		cJSON_AddStringToObject(root, "request_id", buff);
	}else{
		cJSON_AddStringToObject(root, "request_id", reqid);
	}
	if(NULL == type){
		cJSON_AddStringToObject(root, "biz_type", "A");
	}else{
		cJSON_AddStringToObject(root, "biz_type", type);
	}
	app_get_terminal_info(&terminal);
	//verify_version 银联认证版本信息 varchar(32) C
	//cJSON_AddStringToObject(root, "verify_version", MDP810D_CERTIFICAT_VERSION);
	
	//core_version 内核版本信息 varchar(32) C
	//memset(buff, 0, sizeof(buff));
	//sys_read_ver(buff, sizeof(buff)); //共用一个固件版本信息
	//logger_debug("sys_read_ver = %s\n", buff); 
	//logger_hexdump("sys_read_ver=", buff, 50);
	memset(buff1, 0, sizeof(buff1));
	ret = sys_get_hardware_config(KERNEL_COMPILE, buff1, &count);
	logger_debug("ret=%d,count=%d\n",ret,count); 
	logger_hexdump("sys_read_ver=", buff1, 50);
	if(ret==0 && strlen(buff1)>6){
		memset(buff,0,sizeof(buff));
		if(FALSE==GetfwVer(buff1,buff,sizeof(buff)))
			snprintf(buff,sizeof(buff),"%s","unknown");
	}else{
		snprintf(buff,sizeof(buff),"%s","unknown");
	}
	logger_hexdump("sys_read_ver=", buff, 50);
	
	cJSON_AddStringToObject(root, "core_version", buff);
	//sdk_version SDK 版本信息 varchar(32) C
	cJSON_AddStringToObject(root, "sdk_version", buff);
	//hardware_version 硬件版本 varchar(32) C
	cJSON_AddStringToObject(root, "hardware_version", buff);
	//audio_version 音频版本 varchar(32) C
	cJSON_AddStringToObject(root, "audio_version", buff);
	if(terminal.stCap.bSupGprs == app_true){
		//gprs_fw_version GPRS 固件版本
		cJSON_AddStringToObject(root, "gprs_fw_version", buff);
		//gprs_sys_version GPRS 系统版本 varchar(32) C
		cJSON_AddStringToObject(root, "gprs_sys_version", buff);
	}
	//app_version 应用版本信息 varchar(32) M
	cJSON_AddStringToObject(root, "app_version", APP_MAIN_VER);

	//wifi_fw_version WiFi 固件版本 varchar(32) C
	if(terminal.stCap.bSupWifi == app_true){
		memset(buff, 0, sizeof(buff));
		wifi_get_firmware_info(WIFI_COMPILE_VERSION, buff, sizeof(buff));
		cJSON_AddStringToObject(root, "wifi_fw_version", buff);
	}
	
	//product_key 产品 Key varchar(32) M
	cJSON_AddStringToObject(root, "product_key", stSysTemp.product_key);

	//device_sn 设备 SN varchar(32) M
	#ifdef __TEST  //only for test
	if(strlen(stSysPara.device_name)>0){ 
		cJSON_AddStringToObject(root, "device_sn", stSysPara.device_name);
	}else{
		memset(buff, 0, sizeof(buff));
		app_read_sn(buff, sizeof(buff));
		cJSON_AddStringToObject(root, "device_sn", buff);
	}
	#else
	memset(buff, 0, sizeof(buff));
	app_read_sn(buff, sizeof(buff));
	cJSON_AddStringToObject(root, "device_sn", buff);
	#endif
	

	//iccid 设备 SIM 卡的iccid varchar(64) C
	memset(buff, 0, sizeof(buff));
	ret = app_wireless_read_simcard_id((char*)buff, sizeof(buff));
	if(0 == ret && strlen((char*)buff )> 0){
		cJSON_AddStringToObject(root, "iccid", buff);
	}

	//in_flash 内部 flash 文件剩余空间 varchar(16) C
	//temp = app_get_free_space(); 这个取整了 不准确
	statfs("/", &sys_statfs);
	freesize = sys_statfs.f_bsize * sys_statfs.f_bfree;
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%d byte", (freesize));
	cJSON_AddStringToObject(root, "in_flash", buff);

	//out_flash 外部 flash 文件剩余空间 varchar(16) C
	cJSON_AddStringToObject(root, "out_flash", "0");
	//ram 运行 ram 空间 varchar(16) C
	//cJSON_AddStringToObject(root, "ram", buff);

	//battery_inf 剩余电量 varchar(16) C
	temp = get_battery_percent();
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%d%%", temp);
	cJSON_AddStringToObject(root, "battery_inf", buff);

	//network_type 当前网络类型 varchar(16) C
	memset(buff, 0, sizeof(buff));
	if(CT_WIFI!=stCommPara.commType){
		snprintf(buff, sizeof(buff), "%s", "4G");
		cJSON_AddStringToObject(root, "network_type", buff);

		//imei 国际移动设备识别码 char(15) C
		memset(buff, 0, sizeof(buff));
		ret = app_wireless_read_imei((char*)buff, 40);
		if(0 == ret && strlen((char*)buff )> 0){
			cJSON_AddStringToObject(root, "imei", buff);
		}

		//imsi 国际移动用户识别号 char(15) C
		memset(buff, 0, sizeof(buff));
		ret = app_wireless_read_imsi((char*)buff, 40);
		if(0 == ret && strlen((char*)buff )> 0){	
			cJSON_AddStringToObject(root, "imsi", buff);
		}
	}else{
		snprintf(buff, sizeof(buff), "%s", "WiFi");
		cJSON_AddStringToObject(root, "network_type", buff);
	
		//wireless_inf 无线通信信息 varchar(128) C wifi 时上送名称
		//cJSON_AddStringToObject(root, "wireless_inf", buff);
	}
	temp = 0;
	do{
		ret = wnet_get_base_station_info_ex(&stBaseStationExt);
		logger_debug("ret = %d\n", ret); 
		logger_debug("mcc=%d\n", stBaseStationExt.Wnet.oLte.mcc);
		logger_debug("mnc=%d\n", stBaseStationExt.Wnet.oLte.mnc);
		logger_debug("tac=%d\n", stBaseStationExt.Wnet.oLte.tac);
		logger_debug("cell_id=%d\n", stBaseStationExt.Wnet.oLte.cell_id);
		if(0 == ret){
			if(stBaseStationExt.Wnet.oLte.mcc <= 0 || stBaseStationExt.Wnet.oLte.mnc < 0
                || stBaseStationExt.Wnet.oLte.mcc >= 0xFFFF || stBaseStationExt.Wnet.oLte.mnc >= 0xFFFF){ //获取基站信息失败
				;//获取失败重新获取
        	}else{
				break;//获取成功跳出
			}
		}
		app_pos_msleep(300);
	}while(temp++ < 10);

	//base_station 基站信息 JSON 对象 C
	baseStation = cJSON_CreateObject();
	//cellid 基站码 varchar(32) C 移动联通类手机使用，识别基站塔的编码，定位过程中相当重要的数据信息
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%08d", (uint32_t)stBaseStationExt.Wnet.oLte.cell_id);
	cJSON_AddStringToObject(baseStation, "cellid", buff);
	//bid 基站码 varchar(32) C 电信类手机使用，识别基站塔的编码，定位过程中相当重要的数据信息
	//cJSON_AddStringToObject(root, "bid", buff);
	//lac 小区码 varchar(32) C 识别不同的区域，不同的 LAC 管辖范围内会有相同的 CELLID，但实际代表的定位位置是不同的，该码仅在移动、联通类手机定位中使用
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%d", (uint32_t)stBaseStationExt.Wnet.oLte.tac);
	cJSON_AddStringToObject(baseStation, "lac", buff);
	//sid 系统识别编码 varchar(32) C 该码仅在电信手机定位中使用
	//cJSON_AddStringToObject(baseStation, "sid", buff);
	//nid 网络识别编码 varchar(32) C 该码仅在电信手机定位中使用
	//cJSON_AddStringToObject(baseStation, "nid", buff);
	//mnc 网络代码 varchar(32) C
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%d", (uint32_t)stBaseStationExt.Wnet.oLte.mnc);
	cJSON_AddStringToObject(baseStation, "mnc", buff);
	//mcc 国家代码 varchar(32) C
	memset(buff, 0, sizeof(buff));
	snprintf(buff, sizeof(buff), "%d", (uint32_t)stBaseStationExt.Wnet.oLte.mcc);
	cJSON_AddStringToObject(baseStation, "mcc", buff);
	//signal 信号强度 varchar(32) C
	if(CT_GPRS == stCommPara.commType){
		ret = app_lte_get_network_signal(&temp, &signal);
		logger_debug("app_lte_get_network_signal temp=%d signal=%d\n",temp,signal);
	}else{
		ret = app_get_wifi_signal(&temp, &signal);
		logger_debug("app_get_wifi_signal temp=%d signal=%d\n",temp,signal);
	}
	snprintf(buff, sizeof(buff), "%d", signal);
	cJSON_AddStringToObject(baseStation, "signal", buff);
	
	cJSON_AddItemToObject(root, "base_station", baseStation);

	sendbuff = cJSON_PrintUnformatted(root);
	logger_debug("reportTopic = %s\n", pubTopicDevInfo);
	logger_debug("sendbuff = %s\n", sendbuff); 
	if(NULL != sendbuff && strlen(pubTopicDevInfo) > 0){
		AppMQTTPublish(mqtt,Mqtt_QOS0, pubTopicDevInfo, sendbuff);//0成功
	}
	if(NULL != sendbuff){
		free(sendbuff);
	}
	cJSON_Delete(root);
}
#endif 

void send_param_update_stat(char *reqid,char *type,  const char *result)
{
	cJSON*root = NULL;
	char buff[256] = {0};
	char *sendbuff = NULL;
	
	logger_debug("send_param_update_stat reqid:%s\n",reqid);
	logger_debug("stSysPara.product_key=%s\n",stSysPara.product_key);
	logger_debug("stSysPara.device_name=%s\n",stSysPara.device_name);
	
	root = cJSON_CreateObject();
	if(NULL == root){
		return ;
	}
	
	cJSON_AddStringToObject(root, "request_id", reqid);
	cJSON_AddStringToObject(root, "biz_type", type);
	cJSON_AddStringToObject(root, "product_key", stSysTemp.product_key);

	#ifdef __TEST  //only for test
	if(strlen(stSysPara.device_name)>0){ 
		cJSON_AddStringToObject(root, "device_sn", stSysPara.device_name);
	}else{
		memset(buff, 0, sizeof(buff));
		app_read_sn(buff, sizeof(buff));
		cJSON_AddStringToObject(root, "device_sn", buff);
	}
	#else
	memset(buff, 0, sizeof(buff));
	app_read_sn(buff, sizeof(buff));
	cJSON_AddStringToObject(root, "device_sn", buff);
	#endif
	
	cJSON_AddStringToObject(root, "result", result);
	sendbuff = cJSON_PrintUnformatted(root);
	logger_debug("send_param_update_stat sendbuff=%s\n",sendbuff);
	if(NULL != sendbuff && strlen(uploadTopic) > 0){
		AppMQTTPublish(mqtt,Mqtt_QOS0, uploadTopic, sendbuff);//0成功
	}
	if(NULL != sendbuff){
		free(sendbuff);
	}
	cJSON_Delete(root);
}


static int ParseCMisMqttRecvData(char *pRecvData,int len)
{
	cJSON*root = NULL;
	cJSON*psub = NULL;
	char type[10] = {0};
	int ret = -1;
	char *tmprevbuf = NULL;
	logger_debug("+++ParseCMisMqttRecvData\n");

	tmprevbuf = malloc(len +1);
	if(!tmprevbuf){
		logger_debug("no space \n");
		goto cJson_EXIT;
	}
	memset(tmprevbuf,0,len +1);
	memcpy(tmprevbuf,pRecvData,len);

	root=cJSON_Parse((void *)tmprevbuf);
	if (NULL!=root)
	{
		psub = cJSON_GetObjectItem(root,"biz_type");
		if ((NULL==psub)||(psub->type!=cJSON_String))
			goto cJson_EXIT;

		snprintf(type,sizeof(type),"%s",psub->valuestring);
		logger_debug("+++type=%s\n",type);
		ret=MqttPayloadRroc((uint8_t *)type,root);	
	}

cJson_EXIT:

	if (root)
		cJSON_Delete(root);

	if(tmprevbuf){
		free(tmprevbuf);	
	}
	
	return ret;
}

//不要有耗时操作，影响ack上送
void recvmsgproc(void *msg, int len, const char*topic)
{
	int ret = -1;

    if (len > 0 && NULL != msg) {
		((char*)msg)[len] = 0;
		logger_debug("msg (%d): %s\n", len, (char*)msg);
		if(NULL != topic){
			logger_debug("topic : %s\n", topic);
		}else{
			logger_debug("topic : %p\n", topic);
		}
		if((strlen(subTopicUpgrade) > 0 && strstr(topic,subTopicUpgrade) != NULL) || 
			(strlen(subTopicUpgrade2) > 0 && strstr(topic, subTopicUpgrade2) != NULL)){//升级任务
    		ota_update_arrived((char*)msg,(int)len);
    		return;
    	}

		logger_debug("ParseCMisMqttRecvData\n");
		if(strstr(topic,subTopic) != NULL){
			logger_debug("ParseCMisMqttRecvData\n");	
			ret = ParseCMisMqttRecvData((char *)msg,len);
			if(ret != RET_OK){
				return;
			}
		}
    }
}

void set_server_play_status(appbool server_status)
{
	palyFlag = server_status;
}
#ifdef UPLOAD_DEV_INFO
static appbool gSendMqttInfo = app_false;
void set_upload_matt_info_type(appbool type)
{
	gSendMqttInfo = type;
}
appbool get_upload_matt_info_type(void)
{
	logger_debug("gSendMqttInfo=%d\n",gSendMqttInfo);
	return gSendMqttInfo;
}
#endif 
int playmqttstatus(int status)
{
	logger_debug("status=%d\n",status);
    if (status == E_MQTT_CONNECTED ) {
		if(palyFlag){			
			add_play_text(Audio_fuwulianjiechenggong, NULL, NULL, PLAY_MP3);
			palyFlag = app_false;
		}
		logger_debug("SYS_LED_BLUE\n");
		//服务连接成功
		setLedStatus(TERM_SERVER_OK);
    }else if(E_MQTT_DISCONNECTED == status && palyFlag == app_false){
		setLedStatus(TERM_SERVER_DIS);
	}
	return 0;
}
int check_ack_fail(char *data)
{
	cJSON*root = NULL;
	cJSON*psub = NULL;
	char tmprevbuf[512] = {0};
	char request_id[50];

	logger_debug("%s\n", __FUNCTION__); 
	if(NULL == data){
		return -1;
	}
	memcpy(tmprevbuf,data,MIN(strlen(data),512));
	logger_debug("len = %d,inbuf=%s\n",strlen(data),tmprevbuf);
	root=cJSON_Parse((void *)tmprevbuf);
	
	if (NULL!=root)
	{
		psub = cJSON_GetObjectItem(root,"request_id");
		if ((NULL==psub)||(psub->type!=cJSON_String)){
			return -1;
		}
		logger_debug("request_id = %s\n", psub->valuestring);	
		memcpy(request_id, psub->valuestring, strlen(psub->valuestring)+1);
		record_mqtt_ack_write(request_id);
		stSysTemp.bSaveRecordACK = app_true;
	}
	return 1;
}
static int mqtt_status = E_MQTT_UNSTART;
int get_mqtt_status(void)
{
	return mqtt_status;
}

void set_reconnect_mqtt_sem(void)
{
	logger_debug("%s set_sem_flag: %d g_mqtt_recon_sem_time: %d\r\n", __FUNCTION__, set_sem_flag, g_mqtt_recon_sem_time);
	if(0 != g_mqtt_recon_sem_time && app_true == set_sem_flag && CT_GPRS==stCommPara.commType){//只有4G支持
		set_sem_flag = app_false;
		os_put_sem(g_mqtt_recon_sem);
	}
}

void net_check_err_callback(void* para)
{
	int ret = 0;
	mqtt_timer *time = (mqtt_timer *)para;
	
	if(E_MQTT_CONNECTED != mqtt_status && E_MQTT_YIELD != mqtt_status){
		ret = check_get_sem_timeout();
		logger_debug("ret = %d\n", ret);
		if(ret >= NET_ERR_MAX_TIME /*&& 快接近**/){
			add_play_text(Audio_fuwulianjieshibai, NULL, NULL, PLAY_MP3);
			palyFlag = app_true;
			time->jiffies = NET_ERR_MAX_TIME*1000; //播报完重置1分钟时间
		}else if(ret < NET_ERR_MAX_TIME && 0 != ret){
			if(NULL != time){
				time->jiffies = (NET_ERR_MAX_TIME - ret) * 1000; //如果距离上此网络检查时间不足NET_ERR_MAX_TIME，重新设置定时器为剩余时间
			}
		}

	}
}

/**
 * @brief mqtt回调函数
 * 
 * @param status mqtt当前状态
 * @param code 	mqtt函数返回码
 * @param para 	回调传入参数
 */
void notify_mqtt_action(int status, int code, void *para)
{
	mqtt_status = status;

	logger_debug("%s status: %d code: %d , para = %p\r\n", __FUNCTION__, status, code, para);
	logger_debug("g_mqtt_recon_sem_time: %d set_sem_flag: %d\r\n", g_mqtt_recon_sem_time, set_sem_flag);

	if(WifiChanl_AP == stSysTemp.ap_or_airkiss || WifiChanl_AIR == stSysTemp.ap_or_airkiss ||
		NET_4G_2_WIFI == stSysTemp.ap_or_airkiss || NET_WIFI_2_4G == stSysTemp.ap_or_airkiss){  
		if(app_true == mqttTimer.alivable){
			//切换网络关闭当前mqtt时，如果当前服务器连接失败，可能打开定时器播报服务器连接失败，
			//这里要关闭定时器，防止切换到另外一种模式，网络异常情况下同时播报网络异常+服务器连接异常
			//（如4G，但没有卡会播报未检测到SIM卡，还同时播报服务器连接异常）
			stop_time_task(&mqttTimer);
		}
	}

	playmqttstatus(status);
	sys_msleep(5);//加延时防止连接不上时频繁调用
	if(E_MQTT_YIELD == status){
		g_mqtt_recon_sem_time = 0;
		set_sem_flag = app_true;
		if(NULL != para){
			check_ack_fail((char*)para);
		}
		//服务连接成功后，关闭定时器
		if(app_true == mqttTimer.alivable){
			stop_time_task(&mqttTimer);
		}
	}else if(E_MQTT_CONNECTING == status && -1 == code && NULL != para){//5次连接异常重启
		logger_debug("*p = %d\r\n", *((int*)para));

		if(app_false == mqttTimer.alivable){
			start_time_task(&mqttTimer, NET_ERR_MAX_TIME, net_check_err_callback);
		}
		
		if(CT_WIFI==stCommPara.commType){
			//wifi 5次连接失败，重启wifi模块
			if(*((int*)para) != 0 && *((int*)para) % 5 == 0){ 
				net_reboot();
			}
		}else{
			//4G次连接失败一个循环1~5：123 重启，45 休眠1min；678 重启 9,10 休眠2min。。。最大休眠5分钟
			//测试网络正常，服务器异常，可以修改mqtt连接url：glmqttpara.sever.addr = "121.15.2.198";
			logger_debug("4g reconnect & sleep control\r\n");

			if(0 != *((int*)para)){
				if(*((int*)para) % 5 == 3){//连续3次连接mqtt失败，重启
					net_reboot();
				}else if(*((int*)para) % 5 == 0){
					if(g_mqtt_recon_sem_time < MAX_TIME){ //最大休眠5分钟
						g_mqtt_recon_sem_time += STEP_TIME; //休眠时间增加1分钟
					}
					os_get_sem(g_mqtt_recon_sem, g_mqtt_recon_sem_time);//获取信号量，超时时间TIMEOUT_NET
					set_sem_flag = app_true;
				}
			}
		}
	}
}

int get_keepAliveInterval(void)
{
    return HEARTBEAT_SEC;
}


int Start_AWS_Mqtt_pthread(mqtt_param_t *pstMqttPara)
{
	int ret = RET_OK;
	char non_str[] = "";
	memset(pstMqttPara,0,sizeof(mqtt_param_t));
	//initAwsParm(pstAwsParam);

	snprintf(pubTopicDownLoad,sizeof(pubTopicDownLoad),"/ota/device/progress/%s/%s",stSysTemp.product_key,stSysTemp.device_name);
	snprintf(pubTopicInform,sizeof(pubTopicInform),"/ota/device/inform/%s/%s",stSysTemp.product_key,stSysTemp.device_name);
	snprintf(reportTopic,sizeof(reportTopic), "/%s/%s/user/result",stSysTemp.product_key,stSysTemp.device_name); 
	snprintf(uploadTopic,sizeof(uploadTopic), "/%s/%s/user/upload",stSysTemp.product_key,stSysTemp.device_name); 
	snprintf(clientId,sizeof(clientId)-1,"%s&%s",stSysTemp.product_key,stSysTemp.device_name);

	snprintf(pubTopicDevInfo,sizeof(pubTopicDevInfo), "devices/%s/messages/events/",stSysTemp.device_name); 
	


	//subcribe 3 topics
	snprintf(subTopic,sizeof(subTopic),"/%s/%s/user/update",stSysTemp.product_key,stSysTemp.device_name);
   	pstMqttPara->protocol.topic[0] = subTopic;
	snprintf(subTopicUpgrade,sizeof(subTopicUpgrade),"/ota/device/upgrade/%s/%s",stSysTemp.product_key,stSysTemp.device_name);
	pstMqttPara->protocol.topic[1] = subTopicUpgrade;
	snprintf(subTopicUpgrade2,sizeof(subTopicUpgrade2),"/%s/%s/user/upgrade",stSysTemp.product_key,stSysTemp.device_name);
	pstMqttPara->protocol.topic[2] = subTopicUpgrade2;

	
	pstMqttPara->check_net_ok = checknetok;
	pstMqttPara->recv_message_proc = recvmsgproc;
	pstMqttPara->protocol.qos = Mqtt_QOS0;

    pstMqttPara->protocol.clientid  = clientId;
    pstMqttPara->protocol.username = non_str;
    pstMqttPara->protocol.password = non_str;

	pstMqttPara->notify_mqtt_action = notify_mqtt_action;
	pstMqttPara->get_keepAliveInterval = get_keepAliveInterval;
	
	pstMqttPara->protocol.heartbeat_sec =HEARTBEAT_SEC;  //adjust
	pstMqttPara->protocol.clean_session =0;

	
 	pstMqttPara->sever.addr= AWS_ADDR ;
	pstMqttPara->sever.port = AWS_PORT ;
	pstMqttPara->sever.sslmode = MQTT_SSL_VERIFY_PEER;	

	//liyo 
#if 1//使用文件秘钥
	pstMqttPara->sever.cacert[0] = (char*)APP_FILE_PATH"/"MQTT_CA_CERT;
	pstMqttPara->sever.usercert = (char*)APP_FILE_PATH"/"MQTT_CLIENT_CERT;
	pstMqttPara->sever.userkey = (char*)APP_FILE_PATH"/"MQTT_CLIENT_KEY;

#else //使用buff秘钥
	pstMqttPara->sever.cacert[0]=aws_root_cert;
	pstMqttPara->sever.usercert=(char*)stSysTemp.ca;
	pstMqttPara->sever.userkey=stSysTemp.key;
#endif 


	mqtt = StartMqttService(pstMqttPara);
	logger_debug("\n StartMqttService  ret=[%d]\n", ret);
	if (NULL != mqtt) {
		stSysTemp.bMqttStarted = app_true;
    }
	return ret;
}

void AwsMqttProc(void)
{
	Start_AWS_Mqtt_pthread(&glmqttpara);
}

int stop_mqtt(void)
{
	int ret = RET_OK;
	
	if(stSysTemp.bMqttStarted == app_true){
		// 主线程关闭MQTT服务时如果子线程网络没连上会卡死，所以设置一个标志终端网络检测
		stSysTemp.bMqttStopFlg = app_true;
		//ret = StopMqttService();
		stSysTemp.bMqttStopFlg = app_false;
		logger_debug("StopMqttService = %d\n", ret);
		if(ret == 0){
			stSysTemp.bMqttStarted = app_false;
		}
	}
	return ret;
}

void disconnect_mqtt(int closeMqtt)
{
	AppMQTTDisconnect(mqtt,closeMqtt);
}
void reconnect_mqtt(void)
{
	return;
}

int send_mqtt_report(char* message)
{
	logger_debug("reportTopic = %s\n", reportTopic);
	return AppMQTTPublish(mqtt,Mqtt_QOS0, reportTopic, message);//0成功
}



