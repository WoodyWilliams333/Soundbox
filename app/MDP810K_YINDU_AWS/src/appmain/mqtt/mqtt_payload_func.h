
#ifndef _MQTT_PAYLOAD_FUNC_H_
#define _MQTT_PAYLOAD_FUNC_H_


#define BIZ_TYPE_TRANS_VOICE         "1"
#define BIZ_TYPE_GET_INFO            "A"
#define BIZ_TYPE_DO_ENCRYPTION       "B"
#define BIZ_TYPE_DO_DECRYPTION       "C"
#define BIZ_TYPE_SET_PARAM           "D"
#define BIZ_TYPE_OTA_DOWN            "E"
#define BIZ_TYPE_DOWN_VOICE          "F"

#define AUDIO_PLAY_TIMEOUT_MS   (10*60) //十分钟后的数据不播报



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


int MqttPayloadRroc(uint8_t *type,cJSON* pRoot);
#endif

