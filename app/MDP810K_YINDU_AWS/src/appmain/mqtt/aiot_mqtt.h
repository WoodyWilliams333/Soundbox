#ifndef _AIOT_MQTT_H_
#define _AIOT_MQTT_H_

char* strRepl(char *srcStr,const char *str1,const char *str2);
int start_mqtt(void);
int stop_mqtt(void);
int pub_ver_info(void);
int get_battery_percent(void);
int pub_term_step(void);
int send_mqtt_report(char* message);
void set_server_play_status(appbool server_status);
void send_hardware_info(char *reqid, char *type);
void send_param_update_stat(char *reqid, char *type, const char *result);
void set_upload_matt_info_type(appbool type);
appbool get_upload_matt_info_type(void);
appbool get_matt_connect_state(void);
appbool get_mqtt_disconnect_state(void);
void disconnect_mqtt(int closeMqtt);
void reconnect_mqtt(void);
void set_reconnect_mqtt_sem(void);
//int init_MQTT_stat_task(void);

void *get_mqtt_ins(void);

void AwsMqttProc(void);

#endif

