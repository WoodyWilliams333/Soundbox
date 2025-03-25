#include <stdlib.h>
#include <string.h>
#include "task_thread.h"
#include <os_pthread.h>
#include <semaphore.h>
#include <appsys.h>
#include "logger.h"
#include "queue.h"
#include "tts_play.h"
#include "screen.h"
#include "audiomap.h"
#include "fixaudio.h"
#include "ota_http_upgrade.h"
#include "appdef.h"
#include "record_store.h"
#include "syspara.h"
#include "aiot_mqtt.h"
#include "appmalloc.h"
#include "basicext.h"
#include "tersharedata.h"
#include "libapiext.h"
#include "timecalibrat.h"
#include "codestool.h"



#define MQTT_REPORT_TIME_OUT 	(10*60*1000)
#define DELAY_SCREEN_TIMEOUT    (2*1000)
#define DELAY_TASK_TIMEOUT      (5*60*1000)
#define DEFAULT_SCREEN_DATA "0000.00"

static int task_thread = 0; 
pthread_attr_t task_thread_attr;
Queue taskQueue;
pthread_mutex_t mutex;
//pthread_cond_t cond;
static int  play_state = PLAY_FREE;
static sem_handle_t gSem;
static PLAY_LED_STATE screen_light = LED_STATE_OFF;// 0������ 1����


int check_playing(void)
{
	return play_state;
}

int set_play_state(int state)
{
	play_state = state;
	return 0;
}


/**
 * @brief  ������������
 * @retval ��
 */
void set_screen_light(void)
{
    logger_debug("%s\n", __FUNCTION__);
    add_play_text(NULL, (char*)DEFAULT_SCREEN_DATA, NULL, PLAY_TTS);
}

/**
 * @brief  ��鵱ǰ���Ŷ����Ƿ������񣬵�ǰ�Ƿ��в��������в�����������������
 * @retval 1 ������򲥱�  0��û�в���
 */
int get_have_task_play(void)
{
    logger_debug("play_state = %d\n", play_state); 
    logger_debug("QueueIsEmpty(&taskQueue) = %d\n", QueueIsEmpty(&taskQueue)); 
    if(queue_true == QueueIsEmpty(&taskQueue) && PLAY_FREE == check_playing()){//�ն������޲���
        return 0;
    }
    return 1;
}

/**
 * @brief  ������mqtt����
 * @param[in]   TTS_MSG        ����������
 * @retval ��
 */
void deal_play(TTS_MSG *item)
{
 	int ret = -1;
	char *pack_play = NULL;
	char filePath[150] = {0},fileName[100] = {0};
    if(NULL == item){
        return;
    }
    logger_debug("type = %d\n", item->type); 
    logger_debug("amount = %s\n", item->amount); 
    //logger_debug("timestamp = %s\n", item->timestamp); 
    logger_debug("Audio.buf = %s\n", item->Audio.buf); 
    if(strlen(item->amount) > 0){
        set_screen_display(item->amount, 0);// set_screen_display(item->amount, item->type);
    }else{
        set_screen_display((char*)DEFAULT_SCREEN_DATA, 0);
    }
    do{
        if(NULL != item->Audio.buf){
			
            if(PLAY_MP3_AMOUNT == item->type){
				if(strcmp(item->Audio.buf,AudioDangqiandl) == 0){
					ret = PlayPackAudio_number(item,TYPE_NUMBER);	
				}else{				
					ret = PlayPackAudio_number(item,Get_SysPara()->play_lang);	
				}
            }else if(NULL != strstr(item->Audio.buf, Audio_REGEX)){
                if((ret = play_mp3_array(item->Audio.buf)) == 0){
                    break;
                }
            }else{
				if((ret = getaudioplayfilename(item->Audio.buf, fileName)) == 0){//�����Ƿ���mp3�ļ�����ѡ��mp3����
                	if(strlen(fileName) > 0){
                    	snprintf(filePath, sizeof(filePath), "%s/%s", MP3_FILE_PATH, fileName);
                    	logger_debug("filePath = %s\n", filePath);
						ret = play_mp3_file(filePath);
						logger_debug("play_mp3_file = %d\n", ret);                    	
					}
				}				
			}
			if(ret != 0 && strlen(item->Audio.buf) > 0){
				//mp3����ʧ�ܵ�ת��tts
				pack_play = malloc(item->Audio.len +1);
				if(pack_play){
					memset(pack_play,0,item->Audio.len +1);
					strcpy(pack_play,item->Audio.buf);			
					logger_debug("tts replay\n");
					strRepl(pack_play,"_"," ");//���»����滻�ɿո񲻲����»���
				  
					play_tts_msg(pack_play);  
				  	free(pack_play);
				  	pack_play = NULL;
				}	  
			}
        }
    }while(0);

	if(strlen(item->amount) > 0){
		/*
		if(PLAY_MP3_AMOUNT == item->type){
            if(play_amt_MP3(item->amount) != 0){
                play_tts_msg(item->amount);  
            }
        }else */ 
        if(PLAY_MP3 == item->type){
            if(play_num_MP3(item->amount) != 0 ){
                play_tts_msg(item->amount);  
            }
        }else if(PLAY_MP3_VER == item->type){
            if(play_ver_MP3(item->amount) != 0){
                play_tts_msg(item->amount);  
            }
        }
    }

    logger_debug("Audio.buf(%p) = %s\n", item->Audio.buf, item->Audio.buf);
    if(NULL != item->Audio.buf){
        app_free(item->Audio.buf);
        item->Audio.buf = NULL;
    }
}

void* thread_run(void* args) __attribute__((noreturn));

/**
 * @brief  ѭ������mqtt�������ݣ�mqtt���������ڶ�����
 *         ���������е�buf��Ҫ�ͷ�free�����нڵ�Ҳ��Ҫ�ͷ�free
 * @retval void
 */
void* thread_run(void* args)    
{   
    TTS_MSG *item = NULL;
	struct timeval cl_screen_start_tick = {0,0};

    logger_debug("%s\n", __FUNCTION__);  
    
    while(1)    
    {    
        logger_debug("%s\n", __FUNCTION__); 
        if(LED_STATE_ON == screen_light){
            os_get_sem(gSem, DELAY_SCREEN_TIMEOUT);
        }else{
#ifdef UPLOAD_AUDIOPLAY_RESULT
            os_get_sem(gSem, DELAY_TASK_TIMEOUT);
#else
			logger_debug("wait sem....\n");  
            //os_get_sem(gSem, SEM_OPT_WAIT_FOREVER);
            os_get_sem(gSem, DELAY_TASK_TIMEOUT);
#endif
        }

        logger_debug("%s sem triggered!!!!\n", __FUNCTION__);  
        //if =>while   sem_handle_t ��ϵͳ��������ź��������16�������ĵĻ����������ź���ֵ��
        // ���Բ����� ����������9�β�����ʷ��¼ ʹ��if������������п�������
        // ��������ź���û�����ý�ȥ�����涼�ǵȴ���ʱȥ����,
        if(GetQueueCount(&taskQueue) > 0){
            while(GetQueueCount(&taskQueue) > 0)//��������������Ϣȡ��
            {
            	logger_error("++++SET PLAY_BUSY\n");  
                set_play_state(PLAY_BUSY);
                pthread_mutex_lock(&mutex);
                PopQueue(&taskQueue, (void*)&item);
                screen_light = LED_STATE_ON;
                pthread_mutex_unlock(&mutex);
                //logger_debug("item addr = %p\n", item); 

                deal_play(item);

                app_free(item);
                item = NULL;
				gettimeofday(&cl_screen_start_tick, NULL);
                
                logger_debug("%s\n", __FUNCTION__);  
    #ifdef UPLOAD_AUDIOPLAY_RESULT
                if(app_true == get_matt_connect_state()){
                    send_need_report_info(RECORD_SEND_COUNT_TYPE);
                }
                logger_debug("%s\n", __FUNCTION__);
    #endif
                if(app_true == stSysTemp.bSaveRecord && 0 == GetQueueCount(&taskQueue)){
                    auto_save_record_file();
                    stSysTemp.bSaveRecord = app_false;
                }else if(app_true == stSysTemp.bSaveRecordACK && 0 == GetQueueCount(&taskQueue)){
                    auto_save_record_ack_file();
                    stSysTemp.bSaveRecordACK = app_false;
                }
                //ota_success();���������ⲥ��
				logger_error("-----SET PLAY_FREE\n");  
                set_play_state(PLAY_FREE);
            }
        }else {//�������еĲ����꣬�������
            if(pub_check_time_out(&cl_screen_start_tick, DELAY_SCREEN_TIMEOUT)){
                screen_light = LED_STATE_OFF;
                clear_screen_display();
                cl_screen_start_tick.tv_sec = 0;
				cl_screen_start_tick.tv_usec = 0;
            }
        } 
#ifdef UPLOAD_DEV_INFO
        //�������ӳɹ���,�������ӳɹ������豸��Ϣ,�������紦���߳��� ����û�����ϣ���Ҫ����һ���Զ��������״̬����
		if(app_true == get_upload_matt_info_type() && app_true == get_matt_connect_state()){
			logger_debug("send_hardware_info\n");  
			send_hardware_info(NULL, NULL);
			set_upload_matt_info_type(app_false);
		}
#endif             
    }    
} 

/**
 * @brief  ��ʼ����Ϣ���У��̣߳��ź���
 * @retval void
 */
void init_task(void)
{
	
	char version_play[50] = {0};
    logger_debug("%s\n", __FUNCTION__);
    pthread_mutex_init(&mutex, NULL);
    InitQueue(&taskQueue);
    gSem = os_create_sem("test_sem", 0);

    pthread_attr_init(&task_thread_attr);
	task_thread_attr.stacksize = 32*1024;
    task_thread_attr.detachstate = PTHREAD_CREATE_DETACHED;
    pthread_create((pthread_t*)&task_thread, &task_thread_attr, thread_run, NULL);

    //���Ż�ӭ����
	add_play_text(AudioWelcome_vbox, NULL,NULL, PLAY_MP3);
	add_play_text(AudioWUAGBNS, NULL,NULL, PLAY_MP3);

	get_voice_version((char*)APP_MAIN_VER,version_play);
	add_play_text(version_play, NULL,NULL, PLAY_MP3);

	
}

/**
 * @brief  ��ʼ����Ϣ���У��̣߳��ź���
 * @retval void
 */
int AscCheck(uint8_t *in)
{
	int len=0,i=0;
	
	len=strlen((char*)in);
	if(len==0)
		return -1;
	for(i=0;i<len;i++){	
		if(in[i]>127)
			return -1;
	}
	return 0;
}
/**
 * @brief  ������mqtt����
 * @param[in]   text        ��������
 * @param[in]   amount      ���
 * @param[in]   time        ʱ��
 * @retval ��
 */
void add_play_text(const char *text, const char *amount, const char *time, PLAY_MODEL model)
{
    TTS_MSG *msg = NULL;
    int iret= 0;
    logger_debug("%s\n", __FUNCTION__);

    if(NULL == text && NULL == amount && NULL == time){
		logger_debug("return\n");	
        return;
    }

	if(0!=AscCheck((uint8_t*)text))//if not ascii,skip
	{
		logger_debug("return\n");	
		//return;
	}
	
    msg = (TTS_MSG *)app_malloc(sizeof(TTS_MSG));
    //logger_debug("item addr = %p \n", msg);
    if(NULL == msg){
        logger_debug("malloc err \n");
    }else{
        if(queue_false == QueueIsFull(&taskQueue)){
            memset(msg, 0, sizeof(TTS_MSG));
            msg->type = model;

            if(NULL != amount){
                logger_debug("amount = %s \n", amount);
                snprintf(msg->amount, sizeof(msg->amount), "%s", amount);
            }
            if(NULL != time){
                logger_debug("time = %s \n", time);
                snprintf(msg->timestamp, sizeof(msg->timestamp), "%s", time);
            }
            if(NULL != text){
                msg->Audio.len = strlen(text);
                msg->Audio.buf = (char*)app_malloc((msg->Audio.len+1));
                //logger_debug("msg->Audio.buf addr = %p \n", msg->Audio.buf );
                if(NULL != msg->Audio.buf){
                    logger_debug("text = %s \n", text);
                    memset(msg->Audio.buf, 0, (msg->Audio.len+1));
                    snprintf(msg->Audio.buf, (msg->Audio.len+1), "%s", text);
                }
            }
            pthread_mutex_lock(&mutex);/*��ס������*/
            iret = PushQueue(&taskQueue, msg);
            logger_debug("iret = %d \n", iret);
            if(queue_true == iret){
                iret = os_put_sem(gSem);
                logger_debug("os_put_sem iret = %d \n", iret);
            }else{//���ʧ�ܺ� �ͷſռ�
                if(NULL != msg->Audio.buf){
                    app_free(msg->Audio.buf);
                }
                if(NULL != msg){
                    app_free(msg);
                } 
            }
            pthread_mutex_unlock(&mutex);/*����������*/  
        }else{//�������ͷ�����ռ�
            if(NULL != msg){
                free(msg);
            } 
        }
    }
}

int wait_play_timeout(int timeout)
{
	struct timeval tick = {0,0};
    
    logger_debug("%s\n", __FUNCTION__);
	gettimeofday(&tick, NULL); 
    do{
        if(0 == get_have_task_play()){
            return 1;
        }
        sleep(1);
    }while(!pub_check_time_out(&tick, timeout));
    return 0;
}

void clear_task_queue(void)
{
    TTS_MSG *item = NULL;

    logger_debug("start %s\n", __FUNCTION__);
    logger_debug("GetQueueCount(&taskQueue) = %d\n", GetQueueCount(&taskQueue));
    pthread_mutex_lock(&mutex);
    while(GetQueueCount(&taskQueue) > 0)
    {
        PopQueue(&taskQueue, (void*)&item);  
        if(NULL != item && NULL != item->Audio.buf){
            logger_debug("Audio.buf = %s\n", item->Audio.buf);
            app_free(item->Audio.buf);
            item->Audio.buf = NULL;
        }
        app_free(item);
        item = NULL;
        logger_debug("GetQueueCount(&taskQueue) = %d\n", GetQueueCount(&taskQueue));
    }
    pthread_mutex_unlock(&mutex);
    logger_debug("end %s\n", __FUNCTION__);
}

void clear_and_stop_play(void)
{
	clear_task_queue();
	audio_abort(AUDIO_TYPE_TTS);
}

