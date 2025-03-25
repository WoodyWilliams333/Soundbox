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
 * @brief  获取mqtt上送开始计时器
 * @retval 开始计数器
 */
#if 0 
void get_report_start_tick(struct timeval *tick)
{
    tick->tv_sec  = reportstart.tv_sec;
	tick->tv_usec = reportstart.tv_usec;
}
#endif
/**
 * @brief  设置mqtt上送开始计时器
 * @param[in] tick设置参数
 * @retval void
 */
void set_report_start_tick(void)
{
    gettimeofday(&reportstart, NULL); 
}

/**
 * @brief  保存记录数据，有数据加入，保存文件，防止丢失
 * @param[in]   data        记录数据
 * @param[in]   fileName    文件名称
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
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

		ret = app_file_write(fd, data, strlen((char*)data));//把新增的写入到文件中
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
 * @brief  保存播报记录数据，有数据加入，保存文件，防止丢失
 * @param[in]   data        记录数据
 * @param[in]   fileName    文件名称
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
 */
int save_record(char *data)
{
    //logger_debug("%s\n", __FUNCTION__);
    return save_record_file(data, APP_RECORD_FILE);
}

/**
 * @brief  从文件中读取记录数据
 * @param[out]   data        记录数据
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
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

		ret = app_file_read(fd, data, size);//把新增的写入到文件中
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
 * @brief  从文件中读取播报记录数据
 * @param[out]   data        记录数据
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
 */
int read_record(char *data, int size)
{
    logger_debug("%s\n", __FUNCTION__);
    return read_record_file(data, size, APP_RECORD_FILE);
}

/**
 * @brief  初始化记录json结构，使用json数组，历史播报取flash数据，保存10条记录
 * 
 * @retval 1    记录成功
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
 * @brief  返回json数组大小
 * @retval 记录数组大小
 */
int record_get_count(void)
{
    if(NULL == gRootArray){
        return 0;
    }
    return cJSON_GetArraySize(gRootArray); 
}

//清除交易记录
void clean_record(void)
{
    if(NULL != gRootArray){
        pthread_mutex_lock(&mutexRecord);
        cJSON_Delete(gRootArray);
        gRootArray = NULL;
        gRootArray = cJSON_CreateArray();
        
        app_file_remove(APP_RECORD_FILE);//直接删除文件
        pthread_mutex_unlock(&mutexRecord);
    }
}

/**
 * @brief  返回json数组可播报大小
 * @retval 记录数组大小
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
 * @brief  对比msgid是否有重复
 * @param[in]   msgid        播报记录ID
 * @retval 1 有重复交易
 * @retval 0 没有重复交易
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
 * @brief  存储播报记录
 * @param[in]   msgid        播报记录ID
 * @param[in]   voiceMsg     内容
 * @param[in]   money        金额
 * @param[in]   codeflag     方式
 * @param[in]   timestamp    时间
 * @retval 1 存储成功
 * @retval -1 存储失败
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
        //创建保存json 数据
        //cJSON_AddItemToObject(item, JSON_ITEM_TIM, cJSON_CreateString(timestamp));
	    cJSON_AddItemToObject(item, JSON_ITEM_MSGID, cJSON_CreateString(msgid));
	    cJSON_AddItemToObject(item, JSON_ITEM_VMSG, cJSON_CreateString(voiceMsg));
        cJSON_AddItemToObject(item, JSON_ITEM_MONEY, cJSON_CreateString(money));
	    cJSON_AddItemToObject(item, JSON_ITEM_CODE, cJSON_CreateNumber(codeflag));
        //接收到mqtt 默认未播报，未上送
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
 * @brief  保存播报记录数据，有数据加入，保存文件，防止丢失
 * @param[in]   data        记录数据
 * @param[in]   fileName    文件名称
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
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
 * @brief  关键保存数据，系统自动调用
 * @retval 无
 */
void shutdown_save_record_file(void)
{
    auto_save_record_file();
    auto_save_record_ack_file();
    SaveSysPara();
    logger_debug("%s\n", __FUNCTION__);
}

/**
 * @brief  读取数据
 * @param[in]   read_cnt        播报记录
 * @param[out]  max_count       当前记录总数
 * @retval 非NULL 有重复交易
 * @retval NULL 没有记录
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
 * @brief  从文件中读取播报记录数据
 * @param[out]   data        记录数据
 * @retval 1    记录成功
 * @retval 非1  没有记录成功
 */
int read_mqtt_ack_record(char *data, int size)
{
    logger_debug("%s\n", __FUNCTION__);
    return read_record_file(data, size, APP_MQTT_ACK_FILE);
}

/**
 * @brief  初始化记录mqtt ack 异常结构，使用json数组，历史播报取flash数据，保存10条记录
 * 
 * @retval 1    记录成功
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
 * @brief  对比msgid是否有重复
 * @param[in]   msgid        播报记录ID
 * @retval 1 有重复交易
 * @retval 0 没有重复交易
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
 * @brief  存储播报记录
 * @param[in]   msgid        播报记录ID
 * @param[in]   voiceMsg     内容
 * @param[in]   money        金额
 * @param[in]   codeflag     方式
 * @param[in]   timestamp    时间
 * @retval 1 存储成功
 * @retval -1 存储失败
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

        //创建保存json 数据
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
 * @brief  更新记录状态参数
 * @param[in]   msgid  message id
 * @param[in]  tag  更新json数据tag
 * @param[in]   value 更新值
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
 * @brief  格式化时间YYYY-MM-DD HH:MM:MM
 * @param[in]   inValue  待格式化时间字符串
 * @param[out]  outvalue  格式化后输出缓冲区
 * @param[in]   size  outvalue缓冲空间
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
 * @brief  存储播报记录
 * @param[in]   count       未上送笔数，10-4G 达到十笔上送，6-wifi， 0 定时循环，满足10分钟上送
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
        if(RECORD_SEND_TIME_TYPE == type){//定时上送
            sendMax = size;
        }else{//固定笔数上送
            sendMax = 1;
        }
        
        //创建上送json root
        root = cJSON_CreateObject();
        if(NULL == root){
            break;
        }
        //创建result_list array
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
            if(NULL == item2 || RECORD_SEND_YES == item2->valueint){//没有字段或者已发送跳过
                continue;
            }
            //msgid
            item2 = cJSON_GetObjectItem(sub, JSON_ITEM_MSGID);
            if(item2 != NULL){
                memset(reqid, 0, sizeof(reqid));
                snprintf(reqid, sizeof(reqid), "%s", item2->valuestring);
            }
            //播报状态
            if(RECORD_PLAY_NO == cJSON_GetObjectItem(sub, JSON_ITEM_PLAY_OK)->valueint){
                status = '0';
            }else{
                status = '1';
            }
           
            //播报时间
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
        if(0 == j || (RECORD_SEND_COUNT_TYPE == type && j < sendMax)){//如果一笔也没有就不送了
            break;
        }
        //字段report_time 上送时间
        get_timestamp(TIME_STAMP_TYPE_MSEC, dateTime, sizeof(dateTime));
        cJSON_AddStringToObject(root, "report_time", dateTime);
        
        str = cJSON_PrintUnformatted(root);
        logger_debug("get_need_report_info = %s\n", str);
        i = send_mqtt_report(str);
        logger_debug("i = %d\n", i);
        set_report_start_tick();
        
        //设置上送标记位RECORD_SEND_YES
        for(i = 0, j = 0; i < size && j < sendMax; i++){
            sub = cJSON_GetArrayItem(gRootArray, i);
            if(NULL == sub){
                break;
            }
            item2 = cJSON_GetObjectItem(sub, JSON_ITEM_UPLOAD_FLAG);
            if(NULL == item2 || RECORD_SEND_YES == item2->valueint){//没有字段或者已发送跳过
                continue;
            }
            sendStatus = RECORD_SEND_YES;
            record_manage_update(cJSON_GetObjectItem(sub, JSON_ITEM_MSGID)->valuestring, JSON_ITEM_UPLOAD_FLAG, (void*)(&sendStatus));
            j++;
        }
    }while(0);

    pthread_mutex_unlock(&mutexRecord);
    //释放资源
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
 * @brief  获取时间戳
 * @param[in]   type       未上送笔数，10-4G 达到十笔上送，6-wifi， 0 定时循环，满足10分钟上送
 * @param[out]   timestamp  返回时间戳缓存
 * @param[in]   size      缓存空间大小
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