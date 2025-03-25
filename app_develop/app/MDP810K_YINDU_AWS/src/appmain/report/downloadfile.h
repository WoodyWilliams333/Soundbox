#ifndef _AUDIO_FILE_DOWNLOAD_H
#define _AUDIO_FILE_DOWNLOAD_H

#ifdef __cplusplus
	extern "C" {
#endif

#define AUDIO_FILE_TMP_PATH   APP_FILE_PATH"/"MP3_TMP_DIR
#define AUDIO_FILE_MP3_PATH   APP_FILE_PATH"/"MP3_DIR


/////语音文件下载记录
#define DOWNLOAD_FAILED_COUNT     3 //下载重试失败后不再重试
#define AUDIO_FILE_RECORD     "donw_record.dat"
#define TEMP_AUDIOFILE_NAME   "temppack"
#define TEMP_FILE_TYPE        "zip"
#define TEMP_AUDIOFILE_DIR   "down_audio"

#define ERR_BUSY_FIALED (-8)


#define DOWN_AUDIO_FILE_MAX   20//最大支持下载任务

#define DOWN_AUDIO_UZIP_MAXSIZE   (2*1024*1024) //解压内容使用1M

#define DOWN_AUDIO_UZIP_BACKUP_SIZE   (300*1024) //判断移动压缩包的差距大小

#define DOWN_AUDIO_PATH_LEN   (128) //下载文件路径名长度


enum{
	AUDIO_FILE_NOTASK = 0,  //无文件下载任务
	AUDIO_FILE_NEW_TASK,	//存在任务未下载
	AUDIO_FILE_DOWN_FINSH,  //完成下载
	AUDIO_FILE_UNPACK,      //完成解压
	AUDIO_FILE_REPLACE,		//完成部署

};


enum{
	AUDIO_FILE_ERR_INIT = 0, 
	AUDIO_FILE_ERR_DOWNLOADING,	
	AUDIO_FILE_ERR_INTERRUP,  
	AUDIO_FILE_ERR_UNZIP_FIALED,
	AUDIO_FILE_ERR_COPY_FAILED, 
	AUDIO_FILE_ERR_ALL_FAILED,      

};


typedef struct downl_param_{
	int size;
	char url[256+1];
	char signMethod[32+1];
	char sign[1024+1];
	int donw_flag; //当前处理状态
	char pack_file[64+1];//临时存储的文件路径 解压完了之后需要删除腾出空间
}file_downl_param;

typedef struct audio_downl_param_{
	char request_id[50];
	int language;  //语言标识
	file_downl_param file_task_data[DOWN_AUDIO_FILE_MAX]; //是否已下载该签名的文件
	int all_status;
	int Last_err;
	int failed_cont;//记录重试次数
}audio_downl_param;

typedef struct _signed{
	int signed_type;	
	char sign[256+1];
	uint32_t sign_len;
}signed_struct;





int file_param_record_save(audio_downl_param *fileparam);

int file_param_record_read(audio_downl_param *fileparam);



void init_audiofileparam(void);

//轮训每个下载任务 并组包处理结果返回
int aduio_download_task(void);

//获取语音任务实例
audio_downl_param *get_audiofile_ins(void);


//单独下载一个文件 
int onefile_download_func(char *file_url,int file_size,char *file_path,signed_struct *signed_va);


//解压并覆盖原有文件
int unpack_zipfile_topath(char *file_name);

//判断是否是金额文件
int jug_is_amtfile(char * filename);

//从程序目录覆盖拷贝文件到新目录中  delete_flag 是否拷贝完删除olddir原文件 1删除 0 不删除
int copy_onedir_to_newdir(char* olddir,char *newdir,int delete_flag);

//计算文件校验值判断与传入校验值是否一致
//int verify_file_signature(const char*srcpath,int sign_type,char *insign,int sign_len);


#ifdef __cplusplus
	}/*"C" */
#endif
	
#endif  


