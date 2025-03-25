#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <appdatatypedef.h>
#include <appfile.h>
#include "cJSON.h"
#include "ota_http_upgrade.h"
#include "appdef.h"
#include "filecalc.h"
#include "genutils.h"
#include "https.h"
#include <os_pthread.h>
#include "pahomqtt.h"
#include "appmalloc.h"
#include "task_thread.h"
#include "fixaudio.h"
#include "aiot_mqtt.h"
#include "syspara.h"
#include <syscall.h>
#include "basicext.h"
#include "system.h"
#include "tersharedata.h"
#include "sysupdate.h"
#include "libapiext.h"
#include "timecalibrat.h"
#include "downloadfile.h"
#include "mqtt_payload_func.h"
#include "np_zip.h"


#define TRY_DOWN_TIMES		10
#define WRITE_TO_FILESIZE	(1024*2)		
#define QL_VERSION_MAX 256
#define HTTP_HEAD_RANGE_LENGTH_MAX  50
#define TIMEOUT_OTA  (10*60*1000) 
#define DOWN_SUCCESS_PLAY_TIMEOUT  (60*60*1000)//���سɹ���һСʱ����һ��
#define QL_FOTA_PACK_NAME_MAX_LEN 100


#define OTA_FILE_TMP_PATH   APP_FILE_PATH"/"OTA_FILE_PATA


#define LOCK   1
#define UNLOCK 0
int lock_flag = UNLOCK;
int lock_audiodown_flag = UNLOCK;

struct timeval appExitTime = {0,0};


static int https_ota_thread = 0; 
//static int audio_down_thread = 0; 

pthread_attr_t https_ota_thread_attr;
pthread_attr_t audio_down_thread_attr;

void* thread_ota_run(void* args) __attribute__((noreturn));
ota_params ota_param_tmp = {0};
//ota_params audio_down_param_tmp = {0};

static sem_handle_t g_ota_Sem;
//static sem_handle_t g_audiodown_Sem;
int AudioDownload(void);

int lock_ota_para_file(void){
	lock_flag = LOCK;
	return 0;
}

int unlock_ota_para_file(void){
	lock_flag = UNLOCK;
	return 0;
}
int check_ota_para_file(void){
	return lock_flag;
}

int lock_audiodown_para_file(void){
	lock_audiodown_flag = LOCK;
	return 0;
}

int unlock_audiodown_para_file(void){
	lock_audiodown_flag = UNLOCK;
	return 0;
}
int check_audiodown_para_file(void){
	return lock_audiodown_flag;
}

sem_handle_t get_ota_Sem(void)
{
	return g_ota_Sem;
}



appbool check_if_force_update(void)
{
	logger_debug("ota_param_tmp.down_flag = %d stSysPara.update_type = %d ota end\n", ota_param_tmp.down_flag, stSysPara.update_type);
	//��Ҫͬʱ����������ɣ���ǿ�Ƹ��»����������±��,ota_param_tmp.down_flag��ֹ����һ�������豸 
	if((UPDATE_FORCE == stSysPara.update_type) && (ota_param_tmp.down_flag == FOTA_HTTP_DOWN_SUCCESS)){
		return app_true;
	}else{
		return app_false;
	}
}


void ota_success(void)
{
	ota_params *ota_param = &ota_param_tmp;
	logger_debug("%s\n", __FUNCTION__);
	if(check_playing() != PLAY_BUSY)
		return ;

	logger_debug("version\n",ota_param->version);
	if(strcmp(ota_param->version,APP_MAIN_VER) <= 0 ||
		ota_param->down_flag != FOTA_HTTP_DOWN_SUCCESS)
		return ;

	if(app_true == check_if_force_update()){
		//ǿ�Ƹ��¾Ͳ��ò����������ʾ��Ϣ
		return;		
	}
	
	if(0 == appExitTime.tv_sec || pub_check_time_out(&appExitTime, DOWN_SUCCESS_PLAY_TIMEOUT)){
		logger_debug("Audio_XiaZaiChengGong\n");
		add_play_text(Audio_shengjichenggong,NULL,NULL, PLAY_MP3);
		gettimeofday(&appExitTime, NULL); 
	}

}

void* thread_ota_run(void* args)
{
	int sendver=0;
	
	//����1���Ӻ�����߳�
	app_pos_msleep(1*60*1000);
	logger_debug("thread_ota_run\n");
	while( 1 )
	{
		ota_param_upgrade();
		//logger_debug("AppGetMQTTStatus()=%d\n", AppGetMQTTStatus());
		//logger_debug("\tfree_space(): %d;\n", app_get_free_space());
		if(check_playing() == PLAY_BUSY){
			app_pos_msleep(10*1000);
			continue;
		}
		
		//�汾�ſ�����������һ��,
		if(app_true == get_matt_connect_state()&& sendver == 0){
			pub_ver_info();
			set_upload_matt_info_type(app_true);//����һ���豸��Ϣ����
			sendver = 1;
		}
		AudioDownload();
		if(app_true == get_matt_connect_state()){
			OtaDownload();
			//logger_debug("ota end\n");
			while(app_true == check_if_force_update()){
				logger_debug("need sys_reset\n");
				if(check_playing() == PLAY_BUSY){
					app_pos_msleep(1*1000);
					continue;
				}
				clear_and_stop_play();
				add_play_text(Audio_shengjichenggong,NULL,NULL, PLAY_MP3);
				add_play_text(Audio_zhengzaiguanji,NULL,NULL, PLAY_MP3);
				app_pos_msleep(6*1000);
				stSysPara.update_type = UPDATE_SELECT;//����֮ǰ�ָ�UPDATE_SELECT ״̬����ֹ�����������ٽ���
				SaveSysPara();
				app_file_remove(SYSTEM_UPGRADE_FILE);// ���³ɹ���ota_param_tmp.down_flagһֱ��FOTA_HTTP_DOWN_SUCCESS������´��·���ǿ�Ƹ��£��������ع���ʧ�������������
				disconnect_mqtt(1);
				logger_debug("%s\n", "sys_reset");
				sys_reset();
			}
		}
			os_get_sem(g_ota_Sem, TIMEOUT_OTA);//��ȡ�ź�������ʱʱ��TIMEOUT_NET
	}
}

/**
 * @brief  ��ʼ��ota�߳�
 * @retval void
 */
void init_https_ota(void)
{
    logger_debug("%s\n", __FUNCTION__);
	g_ota_Sem = os_create_sem("check_ota_sem", 0);

    pthread_attr_init(&https_ota_thread_attr);
    https_ota_thread_attr.detachstate = PTHREAD_CREATE_DETACHED;
	https_ota_thread_attr.stacksize = 32*1024;
    pthread_create((pthread_t*)&https_ota_thread, &https_ota_thread_attr, thread_ota_run, NULL);
}

void ota_update_arrived(char * data,int len)
{
	cJSON *root = NULL, *item_data,*item_tmp,*item_strategy;
	int totaldownkb = 0;
	char name[33]={0};
	ota_params *ota_data = NULL;
	ota_update_type_t update_type = UPDATE_SELECT;

	logger_debug("%s\n", __FUNCTION__);

	ota_data = (ota_params *)app_malloc(sizeof(ota_params));
	if(ota_data == NULL)
		goto OTA_EXIT;
	memset(ota_data,0,sizeof(ota_params));
	
	root = cJSON_Parse(data);
	if (!root)
	{
		//logger_debug("OTA parse message failed\n");
		goto OTA_EXIT;
	}
	//û��strategy����������ֵ Ĭ����ѡ�����
	item_strategy = cJSON_GetObjectItem(root, "strategy");
	if (item_strategy && strlen(item_strategy->valuestring) > 0)
	{
		if('1' == item_strategy->valuestring[0]){//ǿ�Ƹ���
			update_type = UPDATE_FORCE;
		}
	}
	item_data = cJSON_GetObjectItem(root, "data");
	if (!item_data)
	{
		//logger_debug("OTA not found data item\n");
		goto OTA_EXIT;
	}
	//size
	item_tmp = cJSON_GetObjectItem(item_data, "size");
	if (!item_tmp )
	{
		//logger_debug("OTA not found size item\n");
		goto OTA_EXIT;
	}
	if (item_tmp->type == cJSON_String) {//����size�·���ͬ��ʽ
        ota_data->size = atoi(item_tmp->valuestring);
    } else {
        ota_data->size = item_tmp->valueint;
    }
    logger_debug("ota_data->size=%d\n", ota_data->size);


	//version
	item_tmp = cJSON_GetObjectItem(item_data, "version");
	if (!item_tmp)
	{
		//logger_debug("OTA not found version item\n");
		goto OTA_EXIT;
	}

	snprintf(ota_data->version,sizeof(ota_data->version)-1,"%s",item_tmp->valuestring);
	//strcpy(version_buff, item_version->valuestring);
	//url
	item_tmp = cJSON_GetObjectItem(item_data, "url");
	if (!item_tmp)
	{
		//logger_debug("OTA not found url item\n");
		goto OTA_EXIT;
	}
	snprintf(ota_data->url,sizeof(ota_data->url)-1,"%s",item_tmp->valuestring);

	//signMethod
	item_tmp = cJSON_GetObjectItem(item_data, "signMethod");
	if (!item_tmp)
	{
		//logger_debug("OTA not found signMethod item\n");
		goto OTA_EXIT;
	}
	if (strcmp("Md5", item_tmp->valuestring) == 0)
		{
			ota_data->verify = OTA_VERIFY_MD5;
		}
		else if (strcmp("SHA256", item_tmp->valuestring) == 0)
		{
			ota_data->verify = OTA_VERIFY_SHA256;
		}
		else if (strcmp("SHA1", item_tmp->valuestring) == 0)
		{
			ota_data->verify = OTA_VERIFY_SHA1;
		}
		else
		{
			ota_data->verify = OTA_VERIFY_NONE;
		}

	//sign
	item_tmp = cJSON_GetObjectItem(item_data, "sign");
	if (!item_tmp)
	{
		//logger_debug("OTA not found sign item\n");
		goto OTA_EXIT;
	}

	snprintf(ota_data->verify_value,sizeof(ota_data->verify_value)-1,"%s",item_tmp->valuestring);
		
	if(strstr(ota_data->url,"https") != NULL){
		ota_data->net_mode = OTA_PROTOCOL_HTTPS;
	}else if(strstr(ota_data->url,"http") != NULL ){
		ota_data->net_mode = OTA_PROTOCOL_HTTP;
	}else{
		ota_data->net_mode = OTA_PROTOCOL_FILE;
	}

	logger_debug("OTA new firmware\n");
	logger_debug("------------------------------\n");
	logger_debug("\tupdate_type: %d\n", update_type);
	logger_debug("\tsize: %d\n", ota_data->size);
	logger_debug("\tversion: %s\n", ota_data->version);
	logger_debug("\turl: %s\n", ota_data->url);
	logger_debug("\tsignMethod: %d\n", ota_data->verify);
	logger_debug("\tsign: %s\n", ota_data->verify_value);
	logger_debug("------------------------------\n");
	totaldownkb = ota_data->size/1024 + 1;
	logger_debug("\tfree_space(): %d,totaldownkb=%d;\n", app_get_free_space(),totaldownkb);
	ota_data->down_flag = 0;
	if(app_get_free_space() < totaldownkb)
		ota_data->down_flag = FOTA_HTTP_DOWN_NOSPACE;
		
	logger_debug("\tsign: %s,verify_value:%s\r\n", ota_data->verify_value, ota_param_tmp.verify_value);
	logger_debug("\tversion: %s,version:%s\r\n", ota_data->version, ota_param_tmp.version);
	//ota���ص������ļ����ظ����档
	//pub_strupper(ota_data->verify_value);
	if((strcmp(ota_data->verify_value, ota_param_tmp.verify_value) == 0 &&
		strcmp(ota_data->version, ota_param_tmp.version) == 0 &&
		ota_param_tmp.down_flag == FOTA_HTTP_DOWN_SUCCESS) ||
		(strcmp(ota_data->version, APP_MAIN_VER) == 0)){
		goto OTA_EXIT;
	}

	if ((strcmp(ota_data->verify_value, ota_param_tmp.verify_value) == 0 &&
        strcmp(ota_data->version, ota_param_tmp.version) == 0 &&
        ota_param_tmp.down_flag == FOTA_HTTP_DOWN_DOWNING)) {
        logger_debug("\tstar_size:%d\r\n", ota_param_tmp.star_size);
        goto OTA_EXIT;
    }
//	app_file_cleardir(OTA_DIR);
	if(check_ota_para_file() == LOCK)
		snprintf(name,32,"%s",SYSTEM_UPGRADE_TMP);
	else{
		snprintf(name,32,"%s",SYSTEM_UPGRADE_FILE);
	}

	lock_ota_para_file();
	ota_param_save(ota_data,name);
	#ifdef __TEST
	stSysPara.update_type = 1;
	#else
	stSysPara.update_type = update_type;
	#endif
	
	SaveSysPara();//���ﱣ��ǿ�Ƹ���״̬������������stSysPara.update_type�ͱ��档��ֹ�м�OTA_EXIT�˳�����
	os_put_sem(g_ota_Sem);//�����ź���������thread_net_run�����������û��л�
OTA_EXIT:
	unlock_ota_para_file();
	if (root)
	{
		cJSON_Delete(root);
	}
	if(ota_data != NULL)
		app_free(ota_data);
	return ;
}

int ota_param_save(ota_params *otaparam,const char *name)
{
	int ret = -1;
	int fp;
	logger_debug("%s\n", __FUNCTION__);
	
	fp = app_file_open(SYSTEM_UPGRADE_FILE, O_RDWR|O_CREAT);//"a+"�Ը��ӷ�ʽ�򿪿ɶ�/д���ļ������ļ������ڣ���ᴴ�����ļ�������ļ����ڣ���д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ������EOF������������
	if(fp <= 0){
		logger_error("open file:%s-failed \n", SYSTEM_UPGRADE_FILE);
		goto exit;
	}

//	ql_ftruncate(fp, 0); // clear all data	
	app_file_ftruncate(fp, 0);
	if (app_file_write(fp, (void *)otaparam, sizeof(ota_params)) !=  sizeof(ota_params)) {
		logger_error("%s\n", __FUNCTION__);
		goto exit;
	}		
	ota_param_tmp = *otaparam;
	ret = 0;

exit:
	if(fp > 0){
		app_file_close(fp);
		logger_debug("%s\n", __FUNCTION__,fp);
	}
	logger_debug("star_size:%d down_flag=%d;ret=%d;\r\n",otaparam->star_size,otaparam->down_flag,ret);
	return ret;
}

int ota_param_read(void)
{
	int ret = -1;
	int fp;
	logger_debug("%s\n", __FUNCTION__);
	fp = app_file_open(SYSTEM_UPGRADE_FILE, O_RDONLY);//r+�Զ���ʽ���ļ������ļ�������ڡ�
	if(fp <= 0){
		goto exit;
	}
	if (app_file_read(fp, (void *)&ota_param_tmp, sizeof(ota_params)) !=  sizeof(ota_params)) {
		goto exit;
	}
	ret = 0;
exit:
	if(fp > 0){
		app_file_close(fp);

	}
	logger_debug("total:%d star_size:%d down_flag=%d;\r\n",ota_param_tmp.size,ota_param_tmp.star_size,ota_param_tmp.down_flag);
	return ret;
}

void ota_param_upgrade(void)
{
	int iRet = -1;
	
	if(app_file_exists(SYSTEM_UPGRADE_TMP) >= 0){
		iRet = app_file_remove(SYSTEM_UPGRADE_FILE);
		if(iRet != 0){
			logger_error("remove UPGRADE file error= %d\n", errno);
			return;
		}
		iRet = app_file_rename(SYSTEM_UPGRADE_TMP,SYSTEM_UPGRADE_FILE);
		if(iRet != 0){
			logger_error("rename tmp UPGRADE file error= %d\n", errno);
			return;
		}
	}

}


//��ѹMDP810��MDP810K������ѹ���� ������ȡMDP810K��������������

static int upack_otafile_toupgrate(char *ota_pata)
{
	int iret = -1;
	char tmp_file[150] = {0};
	snprintf((char *)tmp_file, sizeof(tmp_file), "%s/%s",OTA_FILE_TMP_PATH,OTA_TEMP_FILE); 

	iret = npk_install(ota_pata,(char *)OTA_FILE_TMP_PATH,(char *)OTA_FILE_PATA,tmp_file);
	logger_error("npk_install iret=%X\n",iret);
	if(iret == 0){		
		iret = sys_update_pkg(tmp_file);
		logger_error("sys_update_pkg iret=%X\n",iret);
	}	  	

	logger_error("iret=%X\n",iret);
	return iret;
}


int UpdatePkg(const char *path)
{
	int ret=-1;
	
	logger_debug("enter %s\n", __func__);
	if(NULL==path){
		logger_error("UpdatePkg file path is null!\n");
		return -1;
	}	

	ret = upack_otafile_toupgrate((char *)path);
	if(ret != SYS_UPDATE_OK){
		ret = sys_update_pkg(path);
	}
	// show the error infomation if installation failed
	if(ret != SYS_UPDATE_OK){
		logger_error("process error ret : %d\n", ret);
		sys_delete_fw_node();
		switch(ret) {
		case SYS_UPDATE_ERR_SIGN:
			logger_error("signature error\n");
			break;
		case SYS_UPDATE_NO_SPACE:
			logger_error("space not enough\n");
			break;
		case SYS_UPDATE_ERR_FID:
			logger_error("FID error\n");
			break;
		default:
			logger_error("other error\n");
			break;
		}

		return -1;
	} else {
		logger_debug("pkg update sucess!!!\n");
		return 0;
	}

	return -1;
}

/***********************************************************
* funcname		:OtaDownload
* description	:
*	�������������庯��
* return:
*  0 		-- sucess  ���سɹ�����У��ɹ�
*
*  other 	-- failed 
************************************************************/

int OtaDownload(void)
{
	int ret = -1;
	char *tmp_file = NULL;
	ota_params *ota_param = &ota_param_tmp;

	ret = app_file_exists(SYSTEM_UPGRADE_FILE);
	if (ret != 0){	
		logger_error("file not exist\n");	
		return 0;
	}

	if(strlen(ota_param->url) == 0){
		logger_error("NULL url\n"); 
		return 0;
	}
		
	if(strcmp(ota_param->version,APP_MAIN_VER) == 0 ){//��ͬ�汾�Ų�����
		logger_error("no need update pkg\n"); 
		return 0;
	}

	if(ota_param->down_flag == FOTA_HTTP_DOWN_SUCCESS ||
		ota_param->down_flag == FOTA_HTTP_DOWN_NOSPACE ||
		ota_param->down_flag == FOTA_HTTP_DOWN_FAIL){//�ļ�У��ʧ�ܣ����������أ��ȴ��´�ota��������������
		logger_error("no need update:down_flag %d;\n",ota_param->down_flag); 
		return 0;
	}
	
	if(check_ota_para_file()== LOCK)
		return 0;
	lock_ota_para_file();

	logger_debug("\tfree_space(): %d,totaldownkb=%d;\n", app_get_free_space(),ota_param->size/1024 + 1);

	tmp_file = (char *)app_malloc(256);
	if( tmp_file == NULL){
		goto EXIT;
	}

	//snprintf((char *)tmp_file, 256, "/home/user0/Basic4G/%s/%s",OTA_DIR,OTA_TEMP_FILE);
	snprintf((char *)tmp_file, 256, "%s/%s",OTA_DIR,OTA_TEMP_FILE);
	
	ret = https_down(ota_param,tmp_file);
	if(ret < 0){
		if(ota_param->down_flag == FOTA_HTTP_DOWN_FAIL)
			goto REMOVE;//���ش������ݣ���������������ļ�
		else
			goto EXIT;//ͨѶ����ֱ���˳����´�ֱ�ӴӶϵ㿪ʼ����
	}
	add_play_text(Audio_zhengzaishengjiruanjian,NULL,NULL, PLAY_MP3);
	if(0!=app_file_exists(tmp_file))
		logger_error("%s not exist!!!!\n",tmp_file);
	else{
		//int fz;
		app_file_size(tmp_file);
		logger_error("%s is exist,size is:%d!!!!\n",tmp_file,app_file_size(tmp_file));
	}

	ret = ota_file_check(ota_param,tmp_file);
	if(ret < 0){
		ota_param->down_flag = FOTA_HTTP_DOWN_FAIL;
		add_play_text(Audio_shengjishibai,NULL,NULL, PLAY_MP3);
		goto REMOVE;
	}

	//update file
	memset(tmp_file,0,256);
	snprintf((char *)tmp_file, 256, "%s/%s/%s",APP_FILE_PATH,OTA_DIR,OTA_TEMP_FILE); //updatepkg api need absolut path
	ret=UpdatePkg(tmp_file);
	if(-1==ret){
		add_play_text(Audio_shengjishibai,NULL,NULL, PLAY_MP3);
		ota_param->down_flag = FOTA_HTTP_DOWN_FAIL;
		goto REMOVE;
	}
	add_play_text(Audio_shengjichenggong,NULL,NULL, PLAY_MP3);
	ret=0;
	pub_term_step();
	//�����ɹ����̲���һ������
	appExitTime.tv_sec = 0;
	ota_param->down_flag = FOTA_HTTP_DOWN_SUCCESS;
	
REMOVE:
	//������³ɹ�����ʧ�ܶ�ɾ�������ļ�
	if(ota_param->down_flag == FOTA_HTTP_DOWN_FAIL||
		ota_param->down_flag == FOTA_HTTP_DOWN_SUCCESS){
		remove(tmp_file);
		ota_param->star_size = 0;
	}
	logger_debug("\tfree_space(): %d,totaldownkb=%d;\n", app_get_free_space(),ota_param->size/1024 + 1);
	ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);

EXIT:
	unlock_ota_para_file();
	//Ӧ�����سɹ�����У��ɹ���Ӧ��ȥ���£�����0��Ӧ�����سɹ�У��ʧ�ܣ�Ӧ�û�ɾ�����ص���ʱ�ļ���ͬʱ��״̬��Ϊ0.

	if(tmp_file != NULL)
		app_free(tmp_file);
	return ret;
}


int AudioDownload(void)
{
	int ret = -1;
	
	logger_debug("start AudioDownload\n");
	ret = app_file_exists(AUDIO_FILE_RECORD);
	if (ret != 0){	
		logger_error("file not exist\n");	
		return 0;
	}
	logger_error("all_status=%d\n",get_audiofile_ins()->all_status);	
	if(get_audiofile_ins()->all_status == AUDIO_FILE_NOTASK ||
		AUDIO_FILE_REPLACE == get_audiofile_ins()->all_status
		|| get_audiofile_ins()->Last_err == AUDIO_FILE_ERR_ALL_FAILED){
		logger_error("No task\n"); 
		return 0;
	}

	if(get_audiofile_ins()->Last_err == AUDIO_FILE_ERR_INIT){
		add_play_text(Audio_zhengzaishengjiruanjian,NULL,NULL, PLAY_MP3);
	}
	
	ret = aduio_download_task();
	if(ret == 0){
		send_param_update_stat(get_audiofile_ins()->request_id,(char*)BIZ_TYPE_DOWN_VOICE,"1");//��ִ����̨���������		
		add_play_text(Audio_shengjichenggong,NULL,NULL, PLAY_MP3);
	}else{		
		if(get_audiofile_ins()->Last_err == AUDIO_FILE_ERR_ALL_FAILED){
			add_play_text(Audio_shengjishibai,NULL,NULL, PLAY_MP3);
			send_param_update_stat(get_audiofile_ins()->request_id,(char*)BIZ_TYPE_DOWN_VOICE,"0");
		}
	}
	
	return ret;
}


