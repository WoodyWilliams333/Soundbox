#include <stdio.h>
#include <system.h>
#include <string.h>
#include "record_store.h"
#include "task_thread.h"
#include "appdef.h"
#include "tts_play.h"
#include <os_pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include "syspara.h"
#include "aiot_mqtt.h"
#include "appmalloc.h"
#include <fcntl.h>
#include <time.h>
#include "appfile.h"
#include "terfilecomm.h"
#include "logger.h"


#define APP_RECORD_FILE	    "record.dat" 
#define APP_MQTT_ACK_FILE	"mqttack.dat" 

static cJSON *gRootArray = NULL;
static cJSON *gRootACKArray = NULL;
struct timeval reportstart = {0,0};
pthread_mutex_t mutexRecord;

/**
 * @brief  ��ȡmqtt���Ϳ�ʼ��ʱ��
 * @retval ��ʼ������
 */
#if 0 
void get_report_start_tick(struct timeval *tick)
{
    tick->tv_sec  = reportstart.tv_sec;
	tick->tv_usec = reportstart.tv_usec;
}
#endif
/**
 * @brief  ����mqtt���Ϳ�ʼ��ʱ��
 * @param[in] tick���ò���
 * @retval void
 */
void set_report_start_tick(void)
{
    gettimeofday(&reportstart, NULL); 
}

/**
 * @brief  �����¼���ݣ������ݼ��룬�����ļ�����ֹ��ʧ
 * @param[in]   data        ��¼����
 * @param[in]   fileName    �ļ�����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int save_record_file(char *data, const char *fileName)
{
    int fd = -1, ret = 1;
    
    //logger_debug("%s\n", __FUNCTION__);
    if(NULL == data || NULL == fileName){
        return -1;
    }
	do{
		fd = app_file_open(fileName, O_RDWR|O_CREAT|O_TRUNC);
	    if ( fd < 0 ) {
            logger_debug("%s\n", "app_file_open");
	        ret = -1;
			break;
	    }

		ret = app_file_write(fd, data, strlen((char*)data));//��������д�뵽�ļ���
		if( ret!=strlen((char*)data) ){
            logger_debug("%s\n", "app_file_open");
	        ret = -1;
			break;
		}
		logger_debug("app_file_write=%d\n", ret);
	}while(0);

	if( fd > 0)
	    app_file_close(fd);

	return ret;
}

/**
 * @brief  ���沥����¼���ݣ������ݼ��룬�����ļ�����ֹ��ʧ
 * @param[in]   data        ��¼����
 * @param[in]   fileName    �ļ�����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int save_record(char *data)
{
    //logger_debug("%s\n", __FUNCTION__);
    return save_record_file(data, APP_RECORD_FILE);
}

/**
 * @brief  ���ļ��ж�ȡ��¼����
 * @param[out]   data        ��¼����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int read_record_file(char *data, int size, const char *fileName)
{
	int fd = -1, ret = 1;

    //logger_debug("%s\n", __FUNCTION__);
    if(NULL == data || NULL == fileName){
        return -1;
    }
	do{
        if(NULL == data){
            break;
        }
        
		fd = app_file_open(fileName, O_RDWR);
	    if ( fd < 0 ) {
	        ret = -1;
			break;
	    }

		ret = app_file_read(fd, data, size);//��������д�뵽�ļ���
		if(ret < 0){
			//logger_debug("<%s> read fail, ret = %d, errno = %d\n", APP_RECORD_FILE, ret, errno);
			ret = -1;
			break;
		}
        //logger_debug("data = %s\n", data);
	}while(0);

	if( fd > 0)
	    app_file_close(fd);

	return ret;
}

/**
 * @brief  ���ļ��ж�ȡ������¼����
 * @param[out]   data        ��¼����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int read_record(char *data, int size)
{
    logger_debug("%s\n", __FUNCTION__);
    return read_record_file(data, size, APP_RECORD_FILE);
}

/**
 * @brief  ��ʼ����¼json�ṹ��ʹ��json���飬��ʷ����ȡflash���ݣ�����10����¼
 * 
 * @retval 1    ��¼�ɹ�
 */
void init_record_cjson(void)
{
    char *pbuff = NULL;
    int filesize = 0;

    logger_debug("%s\n", __FUNCTION__);
    pthread_mutex_init(&mutexRecord, NULL);
    
    if(NULL != gRootArray){
        cJSON_Delete(gRootArray);
        gRootArray = NULL;
    }
    if(0 == app_file_exists(APP_RECORD_FILE)){
        logger_debug("%s\n", "app_file_exists");
        filesize = app_file_size(APP_RECORD_FILE);
        logger_debug("file size = %d\n", filesize);
        pbuff = (char*)app_malloc(filesize+10);
        if(NULL != pbuff){
            memset(pbuff, 0, sizeof(filesize+10));
            read_record(pbuff, filesize+10);
            //logger_debug("pbuff = %s\n", pbuff);
            gRootArray = cJSON_Parse(pbuff);
            app_free(pbuff);
        }
    }
    if(NULL == gRootArray){
        gRootArray = cJSON_CreateArray();
    }
   
}

/**
 * @brief  ����json�����С
 * @retval ��¼�����С
 */
int record_get_count(void)
{
    if(NULL == gRootArray){
        return 0;
    }
    return cJSON_GetArraySize(gRootArray); 
}

//������׼�¼
void clean_record(void)
{
    if(NULL != gRootArray){
        pthread_mutex_lock(&mutexRecord);
        cJSON_Delete(gRootArray);
        gRootArray = NULL;
        gRootArray = cJSON_CreateArray();
        
        app_file_remove(APP_RECORD_FILE);//ֱ��ɾ���ļ�
        pthread_mutex_unlock(&mutexRecord);
    }
}

/**
 * @brief  ����json����ɲ�����С
 * @retval ��¼�����С
 */
int record_get_read_count(void)
{
    do{
        if(NULL == gRootArray){
            break;
        }
        if(RECORD_MAX_COUNT_2 == RECORD_MAX_COUNT){
            return 0;
        }
        if(cJSON_GetArraySize(gRootArray) == RECORD_MAX_COUNT_2){
            return RECORD_MAX_COUNT;
        }else if(cJSON_GetArraySize(gRootArray) > RECORD_MAX_COUNT){
            return (cJSON_GetArraySize(gRootArray) - RECORD_MAX_COUNT);
        }else{
            return 0;
        }
        
    }while(0);

    return -1;
}

/**
 * @brief  �Ա�msgid�Ƿ����ظ�
 * @param[in]   msgid        ������¼ID
 * @retval 1 ���ظ�����
 * @retval 0 û���ظ�����
 */
int record_compare_msgid( char * msgid)
{
    int ret = 0;
    int size = 0;
    int i = 0;
    cJSON *sub = NULL;
    cJSON *item = NULL;

    //logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootArray || NULL == msgid){
            break;
        }
        size = cJSON_GetArraySize(gRootArray);
        for(i = 0; size > 0 && i < size; i++){
            sub = cJSON_GetArrayItem(gRootArray, i);
            if(NULL != sub){
                item = cJSON_GetObjectItem(sub, JSON_ITEM_MSGID);
                //logger_debug("msgid = %s\n", msgid);

                if(NULL != item && cJSON_String == item->type){
                    //logger_debug("item->valuestring = %s\n", item->valuestring);
                    if(0 == strcmp(msgid, item->valuestring)){
                        ret = 1;
                        break;
                    }
                }
            }
        }
    }while(0);

    return ret;
}

/**
 * @brief  �洢������¼
 * @param[in]   msgid        ������¼ID
 * @param[in]   voiceMsg     ����
 * @param[in]   money        ���
 * @param[in]   codeflag     ��ʽ
 * @param[in]   timestamp    ʱ��
 * @retval 1 �洢�ɹ�
 * @retval -1 �洢ʧ��
 */
int record_manage_write(char* msgid, char* voiceMsg, char* money,int codeflag, char* playtime, int playstatus)
{
    cJSON *item = NULL;
    int ret = 0;

    //logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootArray){
            ret = -1;
            break;
        }

        item = cJSON_CreateObject();
        if(NULL == item){
            ret = -1;
            break;
        }
        //logger_debug("gRootArray addr = %p\n", gRootArray);
        //��������json ����
        //cJSON_AddItemToObject(item, JSON_ITEM_TIM, cJSON_CreateString(timestamp));
	    cJSON_AddItemToObject(item, JSON_ITEM_MSGID, cJSON_CreateString(msgid));
	    cJSON_AddItemToObject(item, JSON_ITEM_VMSG, cJSON_CreateString(voiceMsg));
        cJSON_AddItemToObject(item, JSON_ITEM_MONEY, cJSON_CreateString(money));
	    cJSON_AddItemToObject(item, JSON_ITEM_CODE, cJSON_CreateNumber(codeflag));
        //���յ�mqtt Ĭ��δ������δ����
        //cJSON_AddItemToObject(item, JSON_RCV_TIME, cJSON_CreateString(recvtime));
        cJSON_AddItemToObject(item, JSON_RST_TIME, cJSON_CreateString(playtime));
        cJSON_AddItemToObject(item, JSON_ITEM_PLAY_OK, cJSON_CreateNumber(playstatus));
        cJSON_AddItemToObject(item, JSON_ITEM_UPLOAD_FLAG, cJSON_CreateNumber(RECORD_SEND_NO));
        //logger_debug("json array size = [%d]\n", cJSON_GetArraySize(gRootArray));
        pthread_mutex_lock(&mutexRecord);
        if(NULL != gRootArray ){
            //if(cJSON_GetArraySize(gRootArray) >= RECORD_MAX_COUNT){
            if(cJSON_GetArraySize(gRootArray) >= RECORD_MAX_COUNT_2){
                cJSON_DeleteItemFromArray(gRootArray, 0);
            }
            cJSON_AddItemToArray(gRootArray, item);
        }
        pthread_mutex_unlock(&mutexRecord);
        //logger_debug("json array size = [%d]\n", cJSON_GetArraySize(gRootArray));
        
    }while(0);
 
    
    return ret;
}

/**
 * @brief  ���沥����¼���ݣ������ݼ��룬�����ļ�����ֹ��ʧ
 * @param[in]   data        ��¼����
 * @param[in]   fileName    �ļ�����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int save_mqtt_ack_record(char *data)
{
    logger_debug("%s\n", __FUNCTION__);
    return save_record_file(data, APP_MQTT_ACK_FILE);
}

void auto_save_record_file(void)
{
    char *jsonStr = NULL;

    logger_debug("%s\n", __FUNCTION__);
    //logger_debug("gRootArray addr = %p\n", gRootArray);
    if(NULL != gRootArray){
        jsonStr = cJSON_PrintUnformatted(gRootArray);
        //logger_debug("cjson data:%s \r\n", jsonStr);
        save_record(jsonStr);
        free(jsonStr);
        jsonStr = NULL;
    }
    logger_debug("end %s\n", __FUNCTION__);
}

void auto_save_record_ack_file(void)
{
    char *jsonStr = NULL;

    logger_debug("%s\n", __FUNCTION__);
    //logger_debug("gRootACKArray addr = %p\n", gRootACKArray);
    if(NULL != gRootACKArray){
        jsonStr = cJSON_PrintUnformatted(gRootACKArray);
        //logger_debug("cjson data:%s \r\n", jsonStr);
        save_mqtt_ack_record(jsonStr);
        free(jsonStr);
    }
    logger_debug("end %s\n", __FUNCTION__);
}

/**
 * @brief  �ؼ��������ݣ�ϵͳ�Զ�����
 * @retval ��
 */
void shutdown_save_record_file(void)
{
    auto_save_record_file();
    auto_save_record_ack_file();
    SaveSysPara();
    logger_debug("%s\n", __FUNCTION__);
}

/**
 * @brief  ��ȡ����
 * @param[in]   read_cnt        ������¼
 * @param[out]  max_count       ��ǰ��¼����
 * @retval ��NULL ���ظ�����
 * @retval NULL û�м�¼
 */
cJSON *record_manage_read(int read_cnt, int *max_count)
{
    cJSON *item = NULL;
    int maxCount = 0;

    logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootArray){
            break;
        }
        maxCount = record_get_count();
        logger_debug("maxCount = %d\n", maxCount);
        if(read_cnt < 0 || read_cnt >= maxCount){
            break;
        }
        item = cJSON_GetArrayItem(gRootArray, read_cnt);
        *max_count = maxCount;
    }while(0);

    return item;
}

/**
 * @brief  ���ļ��ж�ȡ������¼����
 * @param[out]   data        ��¼����
 * @retval 1    ��¼�ɹ�
 * @retval ��1  û�м�¼�ɹ�
 */
int read_mqtt_ack_record(char *data, int size)
{
    logger_debug("%s\n", __FUNCTION__);
    return read_record_file(data, size, APP_MQTT_ACK_FILE);
}

/**
 * @brief  ��ʼ����¼mqtt ack �쳣�ṹ��ʹ��json���飬��ʷ����ȡflash���ݣ�����10����¼
 * 
 * @retval 1    ��¼�ɹ�
 */
void init_mqtt_ack_cjson(void)
{
    char *pbuff = NULL;
    int filesize = 0;

    logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL != gRootACKArray){
            cJSON_Delete(gRootACKArray);
        }
        if(0 == app_file_exists(APP_MQTT_ACK_FILE)){
            logger_debug("%s\n", "app_file_exists");
            filesize = app_file_size(APP_MQTT_ACK_FILE);
            logger_debug("file size = %d\n", filesize);
            pbuff = (char*)app_malloc(filesize+10);
            if(NULL != pbuff){
                memset(pbuff, 0, sizeof(filesize+10));
                read_mqtt_ack_record(pbuff, filesize+10);
                logger_debug("pbuff = %s\n", pbuff);
                gRootACKArray = cJSON_Parse(pbuff);
                app_free(pbuff);
            }
        }
        if(NULL == gRootACKArray){
            gRootACKArray = cJSON_CreateArray();
        }
    }while(0);
}

/**
 * @brief  �Ա�msgid�Ƿ����ظ�
 * @param[in]   msgid        ������¼ID
 * @retval 1 ���ظ�����
 * @retval 0 û���ظ�����
 */
int record_compare_mqttack_msgid( char * msgid)
{
    int ret = 0;
    int size = 0;
    int i = 0;
    cJSON *sub = NULL;
    cJSON *item = NULL;

    //logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootACKArray || NULL == msgid){
            break;
        }
        size = cJSON_GetArraySize(gRootACKArray);
        //logger_debug("size = %d\n", size);
        for(i = 0; size > 0 && i < size; i++){
            sub = cJSON_GetArrayItem(gRootACKArray, i);
            if(NULL != sub){
                item = cJSON_GetObjectItem(sub, JSON_ITEM_MSGID);
                //logger_debug("msgid = %s\n", msgid);

                if(NULL != item && cJSON_String == item->type){
                    //logger_debug("item->valuestring = %s\n", item->valuestring);
                    if(0 == strcmp(msgid, item->valuestring)){
                        ret = 1;
                    }
                }
            }
        }
    }while(0);

    return ret;
}

/**
 * @brief  �洢������¼
 * @param[in]   msgid        ������¼ID
 * @param[in]   voiceMsg     ����
 * @param[in]   money        ���
 * @param[in]   codeflag     ��ʽ
 * @param[in]   timestamp    ʱ��
 * @retval 1 �洢�ɹ�
 * @retval -1 �洢ʧ��
 */
int record_mqtt_ack_write(char * msgid)
{
    cJSON *item = NULL;
    int ret = 0;

    logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootACKArray){
            ret = -1;
            break;
        }

        item = cJSON_CreateObject();
        if(NULL == item){
            ret = -1;
            break;
        }

        //��������json ����
	    cJSON_AddItemToObject(item, JSON_ITEM_MSGID, cJSON_CreateString(msgid));
        //logger_debug("json array size = [%d]\n", cJSON_GetArraySize(gRootArray));
        if(NULL != gRootACKArray ){
            if(cJSON_GetArraySize(gRootACKArray) >= RECORD_MAX_COUNT){
                cJSON_DeleteItemFromArray(gRootACKArray, 0);
            }
            cJSON_AddItemToArray(gRootACKArray, item);
        }
        //logger_debug("json array size = [%d]\n", cJSON_GetArraySize(gRootArray));
        
    }while(0);
 
    
    return ret;
}

/**
 * @brief  ���¼�¼״̬����
 * @param[in]   msgid  message id
 * @param[in]  tag  ����json����tag
 * @param[in]   value ����ֵ
 * @retval void
 */
void record_manage_update(const char *msgid, const char* tag, void *value)
{
    int size = 0;
    int i = 0;
    cJSON *sub = NULL;
    cJSON *item = NULL;

    logger_debug("%s\n", __FUNCTION__);
    do{
        if(NULL == gRootArray || NULL == msgid || NULL == tag || NULL == value){
            break;
        }
        size = cJSON_GetArraySize(gRootArray);
        for(i = 0; size > 0 && i < size; i++){
            sub = cJSON_GetArrayItem(gRootArray, i);
            if(NULL != sub){
                item = cJSON_GetObjectItem(sub, JSON_ITEM_MSGID);
                //logger_debug("msgid = %s\n", msgid);

                if(NULL != item && cJSON_String == item->type){
                    //logger_debug("item->valuestring = %s\n", item->valuestring);
                    //pthread_mutex_lock(&mutexRecord);
                    if(0 == strcmp(msgid, item->valuestring)){
                        if(0 == strcmp(tag, JSON_ITEM_PLAY_OK) || 0 == strcmp(tag, JSON_ITEM_UPLOAD_FLAG)){
                            //logger_debug("item->valuestring = %d\n", *(int*)value);
                            cJSON_ReplaceItemInObject(sub, tag, cJSON_CreateNumber(*(int*)value) );
                        }else if(0 == strcmp(tag, JSON_RST_TIME)){
                            cJSON_ReplaceItemInObject(sub, tag, cJSON_CreateString((char*)value));
                        }
                    }
                    //pthread_mutex_unlock(&mutexRecord);
                }
            }
        }
    }while(0);
}

/**
 * @brief  ��ʽ��ʱ��YYYY-MM-DD HH:MM:MM
 * @param[in]   inValue  ����ʽ��ʱ���ַ���
 * @param[out]  outvalue  ��ʽ�������������
 * @param[in]   size  outvalue����ռ�
 * @retval void
 */
void get_report_time(char *inValue, char *outvalue, int size)
{
    char *dateTime = inValue;

    if(NULL != dateTime && NULL != outvalue){
        snprintf(outvalue, size, "%.4s-%.2s-%.2s %.2s:%.2s:%.2s",dateTime+0, dateTime+4,dateTime+6,dateTime+8,dateTime+10,dateTime+12);
    }
}
#ifdef UPLOAD_AUDIOPLAY_RESULT
/**
 * @brief  �洢������¼
 * @param[in]   count       δ���ͱ�����10-4G �ﵽʮ�����ͣ�6-wifi�� 0 ��ʱѭ��������10��������
 * @retval void
 */
void send_need_report_info(RECORD_SEND_type type)
{
    int size = 0;
    int i = 0, j = 0;
    cJSON *sub = NULL;
    cJSON *root = NULL;
    cJSON *array = NULL;
    cJSON *item2 = NULL;
    char dateTime[32] = {0};
    char reqid[64] = {0};
    char status;
    char buff[128] = {0};
    char *str = NULL;
    int sendMax = 0;
    RECORD_SEND_STATUS sendStatus;

    logger_debug("%s\n", __FUNCTION__);

    pthread_mutex_lock(&mutexRecord);
    do{
        if(NULL == gRootArray){
            break;
        }
        size = cJSON_GetArraySize(gRootArray);
        logger_debug("size = %d type = %d\n", size, type);
        if(RECORD_SEND_TIME_TYPE == type){//��ʱ����
            sendMax = size;
        }else{//�̶���������
            sendMax = 1;
        }
        
        //��������json root
        root = cJSON_CreateObject();
        if(NULL == root){
            break;
        }
        //����result_list array
        array = cJSON_CreateArray();
        if(NULL == array){
            break;
        }
        
        cJSON_AddItemToObject(root, "result_list",array);
        for(i = 0, j = 0; i < size && j < sendMax; i++){
            sub = cJSON_GetArrayItem(gRootArray, i);
            if(NULL == sub){
                break;
            }
            item2 = cJSON_GetObjectItem(sub, JSON_ITEM_UPLOAD_FLAG);
            if(NULL == item2 || RECORD_SEND_YES == item2->valueint){//û���ֶλ����ѷ�������
                continue;
            }
            //msgid
            item2 = cJSON_GetObjectItem(sub, JSON_ITEM_MSGID);
            if(item2 != NULL){
                memset(reqid, 0, sizeof(reqid));
                snprintf(reqid, sizeof(reqid), "%s", item2->valuestring);
            }
            //����״̬
            if(RECORD_PLAY_NO == cJSON_GetObjectItem(sub, JSON_ITEM_PLAY_OK)->valueint){
                status = '0';
            }else{
                status = '1';
            }
           
            //����ʱ��
            item2 = cJSON_GetObjectItem(sub, JSON_RST_TIME);
            if(item2 != NULL){
                memset(dateTime, 0, sizeof(dateTime));
                snprintf(dateTime, sizeof(dateTime), "%s", item2->valuestring);
            }
            memset(buff, 0, sizeof(buff));
            snprintf(buff, sizeof(buff), "%s|%s|%c|", reqid, dateTime, status);
            cJSON_AddItemToArray(array, cJSON_CreateString(buff));
            j++;
        }
        logger_debug("sendMax = %d j = %d\n", sendMax, j);
        if(0 == j || (RECORD_SEND_COUNT_TYPE == type && j < sendMax)){//���һ��Ҳû�оͲ�����
            break;
        }
        //�ֶ�report_time ����ʱ��
        get_timestamp(TIME_STAMP_TYPE_MSEC, dateTime, sizeof(dateTime));
        cJSON_AddStringToObject(root, "report_time", dateTime);
        
        str = cJSON_PrintUnformatted(root);
        logger_debug("get_need_report_info = %s\n", str);
        i = send_mqtt_report(str);
        logger_debug("i = %d\n", i);
        set_report_start_tick();
        
        //�������ͱ��λRECORD_SEND_YES
        for(i = 0, j = 0; i < size && j < sendMax; i++){
            sub = cJSON_GetArrayItem(gRootArray, i);
            if(NULL == sub){
                break;
            }
            item2 = cJSON_GetObjectItem(sub, JSON_ITEM_UPLOAD_FLAG);
            if(NULL == item2 || RECORD_SEND_YES == item2->valueint){//û���ֶλ����ѷ�������
                continue;
            }
            sendStatus = RECORD_SEND_YES;
            record_manage_update(cJSON_GetObjectItem(sub, JSON_ITEM_MSGID)->valuestring, JSON_ITEM_UPLOAD_FLAG, (void*)(&sendStatus));
            j++;
        }
    }while(0);

    pthread_mutex_unlock(&mutexRecord);
    //�ͷ���Դ
    if(NULL != str){
        free(str);
    }
    if(NULL != root){
        cJSON_Delete(root);
    }
    //logger_debug("exit %s\n", __FUNCTION__);
}
#endif 
/**
 * @brief  ��ȡʱ���
 * @param[in]   type       δ���ͱ�����10-4G �ﵽʮ�����ͣ�6-wifi�� 0 ��ʱѭ��������10��������
 * @param[out]   timestamp  ����ʱ�������
 * @param[in]   size      ����ռ��С
 * @retval void
 */
void get_timestamp(TIME_STAMP_TYPE type, char *timestamp, int size)
{
	struct timeval tv;

	if(NULL != timestamp){
		gettimeofday(&tv, NULL);
		//tv.tv_sec = tv.tv_sec-8*60*60;
		if(TIME_STAMP_TYPE_MSEC == type){
			snprintf(timestamp, size, "%lld%03ld", tv.tv_sec, (tv.tv_usec / 1000));
		}else{
			snprintf(timestamp, size, "%lld", tv.tv_sec);
		}
		//logger_debug("timestamp : %s\n", timestamp);
	}
}