#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "downloadfile.h"
#include "mqtt_report.h"
#include "codestool.h"
#include "np_led.h"
#include "appdef.h"

#include "logger.h"
#include "ota_http_upgrade.h"
#include "appfile.h"
#include <wolfssl/openssl/md5.h>
#include <wolfssl/openssl/sha.h>
#include "syspara.h"
#include "tts_play.h"
#include "appsys.h"
#include "np_zip.h"
#include "fixaudio.h"
#include "mqtt_payload_func.h"
#include "task_thread.h"
#include "aiot_mqtt.h"


#define app_debug logger_debug
#define hexdump logger_hexdump
/***********语音文件下载 begin****************/

static audio_downl_param audio_file_ins;

extern int http_load_file(char *file_path,int file_size,char *host, int port, char *url,signed_struct *signed_va);

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif 



int copy_onedir_to_newdir(char* olddir,char *newdir,int delete_flag)
{
	int iret = -1;	
	DIR *old_d = NULL;
	char src_full_path[150] = {0},dst_full_path[150] = {0};
	struct dirent *old_stdir = NULL;
	if(olddir == NULL || newdir == NULL){
		logger_debug("param NULL\n");
		goto exit;	
	}
	old_d = app_file_opendir(olddir);
	if(old_d == NULL ){
		logger_debug("opendir failed\n");
		goto exit;
	}

	logger_debug("dd_fd=%d,\n",old_d->dd_fd,old_d->dd_buf.d_ino);
	logger_debug("copy_onedir_to_newdir\n");
	logger_debug("------------------------------\n");
	logger_debug("\t dd_fd: %d\n", old_d->dd_fd);
	logger_debug("\t d_ino: %d\n", old_d->dd_buf.d_ino);
	logger_debug("\t d_off: %d\n", old_d->dd_buf.d_off);
	logger_debug("\t d_reclen: %d\n", old_d->dd_buf.d_reclen);
	logger_debug("\t d_type: %d\n", old_d->dd_buf.d_type);
	logger_debug("\t d_name: %s\n", old_d->dd_buf.d_name);
	logger_debug("------------------------------\n");

	old_stdir = app_file_readdir(old_d);
	while(old_stdir){
	
		snprintf(src_full_path,sizeof(src_full_path),"%s/%s",olddir,old_stdir->d_name);
		snprintf(dst_full_path,sizeof(dst_full_path),"%s/%s",newdir,old_stdir->d_name);
		logger_debug("olddir=%s,newdir=%s\n", src_full_path,dst_full_path);
		iret = file_copy_to_newpath(src_full_path,dst_full_path);
		if(iret != 0){
			logger_debug("copy failed\n");
			break;
		}	
		old_stdir = app_file_readdir(old_d);
		logger_debug("old_stdir=%p\n",old_stdir);
	}
	
	
exit:
	if(old_d){
		app_file_closedir(old_d);
	}
	logger_debug("iret=%d\n",iret);


	return iret;

}


int pase_biztype_F(cJSON*root)
{

	cJSON*psub = NULL;
	cJSON*tmep_pub = NULL;
	cJSON*para_inf = NULL;
	int i = 0,index = 0;//,j = 0,insert_index = 0;
	file_downl_param file_param = {0};
	audio_downl_param *fileparam = NULL;
	//uint8_t insert_flag = 0;
	int ret = -1;
	logger_debug("pase_biztype_F root=%p\n",root);
	if(NULL == root){
		ret = -2;
		goto paseF_EXIT;
	}

	fileparam = malloc(sizeof(audio_downl_param));
	if(fileparam == NULL){
		goto paseF_EXIT;		
	}

	memset(fileparam,0,sizeof(audio_downl_param));
	logger_debug("file_param_record_read\n");
	file_param_record_read(fileparam);
	logger_debug("file_param_record_read\n");
	psub = cJSON_GetObjectItem(root,"request_id");
	if ((NULL==psub)||(psub->type!=cJSON_String))
		goto paseF_EXIT;

	snprintf(fileparam->request_id,sizeof(fileparam->request_id)-1,"%s",psub->valuestring);
	snprintf(audio_file_ins.request_id,sizeof(audio_file_ins.request_id)-1,"%s",psub->valuestring);
	
	app_debug("request_id=%s\n",fileparam->request_id);
	
	psub = cJSON_GetObjectItem(root,"language");
	if ((NULL==psub)||(psub->type!=cJSON_String))
		goto paseF_EXIT;

	fileparam->language = np_hex2long((uint8_t *)psub->valuestring,strlen(psub->valuestring));
	app_debug("language=%d\n",fileparam->language);
	psub = cJSON_GetObjectItem(root, "audio_inf");
	if (NULL== psub){
		ret = -3;
		goto paseF_EXIT;
	}else{
		
		i = cJSON_GetArraySize(psub);
		app_debug("i=%d\n",i);
		for(index = 0;index < i; index++){
		{
			para_inf = cJSON_GetArrayItem(psub,index);
			if (NULL==para_inf){
					ret = -4;
					goto paseF_EXIT;;
			}else{
				memset(&file_param,0,sizeof(file_downl_param));	
				//size
				tmep_pub = cJSON_GetObjectItem(para_inf, "size");
				if (!tmep_pub )
				{
					app_debug("OTA not found size item\n");
					goto paseF_EXIT;
				}
				if(tmep_pub->type == cJSON_String){ 	
					file_param.size = atoi(tmep_pub->valuestring);
				}else {
					file_param.size = tmep_pub->valueint;
				}
				
				//url
				tmep_pub = cJSON_GetObjectItem(para_inf, "url");
				if (!tmep_pub)
				{
					app_debug("OTA not found url item\n");
					goto paseF_EXIT;
				}
				snprintf(file_param.url,sizeof(file_param.url)-1,"%s",tmep_pub->valuestring);
			
				//signMethod
				tmep_pub = cJSON_GetObjectItem(para_inf, "signMethod");
				if (!tmep_pub)
				{
					app_debug("OTA not found signMethod item\n");
					goto paseF_EXIT;
				}
				snprintf(file_param.signMethod,sizeof(file_param.signMethod)-1,"%s",tmep_pub->valuestring);

				//sign
				tmep_pub = cJSON_GetObjectItem(para_inf, "sign");
				if (!tmep_pub)
				{
					app_debug("OTA not found sign item\n");
					goto paseF_EXIT;
				}
				snprintf(file_param.sign,sizeof(file_param.sign)-1,"%s",tmep_pub->valuestring);

				app_debug("size=%d\n",file_param.size);
				app_debug("url=%s\n",file_param.url);
				file_param.donw_flag = AUDIO_FILE_NEW_TASK;
				memcpy(&fileparam->file_task_data[index],&file_param,sizeof(file_downl_param));

			   }
			}
		}
	
	}
	
	//有需要下载的语音 则启动任务
	memcpy(&audio_file_ins,fileparam,sizeof(audio_downl_param));		
	audio_file_ins.all_status = AUDIO_FILE_NEW_TASK;	
	file_param_record_save(&audio_file_ins);//保存状态
	os_put_sem(get_ota_Sem());
	ret = 0;
paseF_EXIT:
	if(fileparam){
		free(fileparam);
	}

	app_debug("ret =%d\n",ret);
	return ret;

}

int file_param_record_save(audio_downl_param *fileparam)
{
	int ret = -1;
	int fp = 0;
	fp = app_file_open((char *)AUDIO_FILE_RECORD,O_RDWR | O_CREAT);
	if(fp <= 0){
		goto exit;
	}

	app_file_ftruncate(fp, 0); // clear all data	
			
	if (app_file_write(fp,(void *)fileparam, sizeof(audio_downl_param)) !=  sizeof(audio_downl_param)) {
		goto exit;
	}		
	ret = 0;

exit:
	if(fp > 0){
		app_file_close(fp);
	}
	return ret;

}

void init_audiofileparam(void)
{
	file_param_record_read(&audio_file_ins);
}


int file_param_record_read(audio_downl_param *fileparam)
{
	int ret = -1;
	int fp;

	fp = app_file_open(AUDIO_FILE_RECORD,O_RDONLY | O_CREAT);
	if(fp <= 0){
		goto exit;
	}
	
	if (app_file_read(fp,(void *)fileparam, sizeof(audio_downl_param)) !=  sizeof(audio_downl_param)) {
		goto exit;
	}

	ret = 0;

exit:
	if(fp > 0){
		app_file_close(fp);
	}
	return ret;

}



audio_downl_param *get_audiofile_ins(void)
{
	return &audio_file_ins;
}

int aduio_download_task(void)
{
	int ret = -1,i = 0;
	int file_free_size = 0,download_fail = 0; 
	char tmp_buff[150] = {0};
	signed_struct verify_signed = {0};
	app_debug("aduio_download_task \n");
	verify_signed.signed_type = OTA_VERIFY_SHA256;
	
	//下载前清理 
	for(i = 0;i < DOWN_AUDIO_FILE_MAX;i++){
		snprintf(audio_file_ins.file_task_data[i].pack_file,sizeof(audio_file_ins.file_task_data[i].pack_file)-1,"%s%d.%s",TEMP_AUDIOFILE_NAME,i,TEMP_FILE_TYPE);
		if(audio_file_ins.file_task_data[i].donw_flag < AUDIO_FILE_DOWN_FINSH)
		{			
			app_file_remove(audio_file_ins.file_task_data[i].pack_file);						
		}										
	}
	
	for(i = 0;i < DOWN_AUDIO_FILE_MAX;i++){
		app_debug("i=%d,url=%s\n",i,audio_file_ins.file_task_data[i].url);
		app_debug("size=%d\n",audio_file_ins.file_task_data[i].size);
	    app_debug("donw_flag=%d\n",audio_file_ins.file_task_data[i].donw_flag);
		if(strlen(audio_file_ins.file_task_data[i].url) != 0 
			&& audio_file_ins.file_task_data[i].size > 0
			&& audio_file_ins.file_task_data[i].donw_flag < AUDIO_FILE_DOWN_FINSH
			){//新建下载和解压任务
			get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_DOWNLOADING;
			setLedStatus(TERM_OTA_START);
			file_free_size = app_get_free_space()*1000;	
			app_debug("file_free_size=%d,size=%d \n",file_free_size,audio_file_ins.file_task_data[i].size);
			if(file_free_size <  audio_file_ins.file_task_data[i].size){//每次下载判断空间
				ret = -5;
				break;	
			}		
			memset(verify_signed.sign,0,sizeof(verify_signed.sign));	
			//下载只重试一次
			if((ret = onefile_download_func(audio_file_ins.file_task_data[i].url,audio_file_ins.file_task_data[i].size,audio_file_ins.file_task_data[i].pack_file
				,&verify_signed)) != 0){
				
				if(ERR_BUSY_FIALED == ret){
					get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_INTERRUP;
					break;
				}
				memset(verify_signed.sign,0,sizeof(verify_signed.sign));	
				//重试使用http
				memset(tmp_buff,0,sizeof(tmp_buff));
				strcpy(tmp_buff,audio_file_ins.file_task_data[i].url);
				strRepl(tmp_buff,"https","http");	
				ret = onefile_download_func(tmp_buff,audio_file_ins.file_task_data[i].size,audio_file_ins.file_task_data[i].pack_file
					,&verify_signed);
			}
			
			app_debug("download ret=%d\n",ret);
			if(ret == 0){
				if(strlen(verify_signed.sign) > 0){//校验文件
					app_debug("data[i].sign=%s,verify_signed.sign=%s\n",audio_file_ins.file_task_data[i].sign,verify_signed.sign);
					np_lower((char*)audio_file_ins.file_task_data[i].sign);
					np_lower((char*)verify_signed.sign);
					ret = strcmp(verify_signed.sign,(char*)audio_file_ins.file_task_data[i].sign);
				}
				app_debug("verify_signed ret=%d\n",ret);
				if(ret == 0){
					audio_file_ins.file_task_data[i].donw_flag = AUDIO_FILE_DOWN_FINSH;
				}else{
					download_fail = 1;
					app_file_remove(audio_file_ins.file_task_data[i].pack_file);	
					audio_file_ins.file_task_data[i].donw_flag = AUDIO_FILE_NEW_TASK;
				}
			
			}else if(ERR_BUSY_FIALED == ret){
				get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_INTERRUP;
				break;
			}else{  //下载失败清理临时文件留出空间
				download_fail = 1;
				app_file_remove(audio_file_ins.file_task_data[i].pack_file);	
							
			}
			
		}

	}
	app_debug("ret = %d,download_fail=%d\n",ret,download_fail);
	/*****************全部先解压 -> 删除下载文件 -> 写入文件替换******************/
	if(audio_file_ins.all_status == AUDIO_FILE_DOWN_FINSH || (ret == 0 && !download_fail )){	
		//全部下载完成后再解压
		audio_file_ins.all_status = AUDIO_FILE_DOWN_FINSH;	
		file_param_record_save(&audio_file_ins);//先保存状态再解压
	
		for(i = 0;i < DOWN_AUDIO_FILE_MAX;i++){
			if(strlen(audio_file_ins.file_task_data[i].url) > 0 && audio_file_ins.file_task_data[i].size > 0
				&& audio_file_ins.file_task_data[i].donw_flag == AUDIO_FILE_DOWN_FINSH
				&& strlen(audio_file_ins.file_task_data[i].pack_file) > 0 ){
				snprintf(tmp_buff,sizeof(tmp_buff),"%s/%s",APP_FILE_PATH,audio_file_ins.file_task_data[i].pack_file);
				ret = npk_install(tmp_buff,(char*)AUDIO_FILE_TMP_PATH,NULL,NULL);
				app_debug("file=%s,unpack ret=%d\n",audio_file_ins.file_task_data[i].pack_file,ret);
				if(ret != 0){
					//解压出错重新下载任务
					audio_file_ins.all_status = AUDIO_FILE_NEW_TASK;	
					audio_file_ins.file_task_data[i].donw_flag = AUDIO_FILE_NEW_TASK;
					audio_file_ins.failed_cont ++;
					file_param_record_save(&audio_file_ins);
					download_fail = 1;
					if(audio_file_ins.failed_cont >= DOWNLOAD_FAILED_COUNT){
						get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_ALL_FAILED;
					}else{
						get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_UNZIP_FIALED;
					}
					break;
				}
				app_file_remove(audio_file_ins.file_task_data[i].pack_file);//解压成功就删除压缩包	
			}		
		}
				
	}
	app_debug("all_status=%d \n",audio_file_ins.all_status);
	//从临时文件拷贝到正式文件夹中
	if(audio_file_ins.all_status == AUDIO_FILE_UNPACK || ( ret == 0 && !download_fail)){
		audio_file_ins.all_status = AUDIO_FILE_UNPACK;	
		file_param_record_save(&audio_file_ins);
		ret = copy_onedir_to_newdir((char*)MP3_TMP_DIR,(char*)MP3_DIR,1);//完整下载和解压之后再拷贝语音
		if(ret == 0){
			audio_file_ins.all_status = AUDIO_FILE_REPLACE; 
			file_param_record_save(&audio_file_ins);
		}else{
			get_audiofile_ins()->Last_err = AUDIO_FILE_ERR_COPY_FAILED;
		}
	}

	app_debug("ret=%d,download_fail=%d,language=%d\n",ret,download_fail,audio_file_ins.language);

	if(ret == 0 && !download_fail){
		for(i = 0;i < DOWN_AUDIO_FILE_MAX;i++){//语音拷贝结束后删除所有解压的语音
			app_file_remove(audio_file_ins.file_task_data[i].pack_file);						
		}	
		app_file_cleardir(MP3_TMP_DIR);
		app_file_rmappdir(MP3_TMP_DIR);
		if(audio_file_ins.language == 0 || audio_file_ins.language == '0'){
			Get_SysPara()->play_lang = TYPE_AMOUNT_EN;
		}else if(audio_file_ins.language == TYPE_AMOUNT_TMAIL || audio_file_ins.language == TYPE_AMOUNT_KANNADA){
			Get_SysPara()->play_lang = TYPE_AMOUNT_TMAIL;
		}else{
			Get_SysPara()->play_lang = TYPE_AMOUNT_HINDI;
		}
		SaveSysPara();
	}else{
		ret = -1;
	}

	app_debug("ret=%d\n",ret);
	setLedStatus(TERM_SERVER_OK);//恢复服务待机LED

	return ret;
}


int onefile_download_func(char *http_url,int file_size,char *file_path,signed_struct *signed_va)
{
	int iRet = -1,szPort = 0;
	char szDNS[65] = {0};

	deal_url(http_url,NULL,szDNS,&szPort,0);
	
	if(szPort == 0){
		if(strncmp(http_url,"https",5) == 0){
			szPort = 443;	
		}else if(strncmp(http_url,"http",4) == 0){
			szPort = 80;
		}
	}
	
	iRet = http_load_file(file_path,file_size,(char *)szDNS, szPort, http_url,signed_va);	  
	
	app_debug("iRet=%d\n",iRet);
	return iRet;

}



/***********语音文件下载 end****************/


