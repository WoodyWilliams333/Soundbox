#ifndef _AUDIO_FILE_DOWNLOAD_H
#define _AUDIO_FILE_DOWNLOAD_H

#ifdef __cplusplus
	extern "C" {
#endif

#define AUDIO_FILE_TMP_PATH   APP_FILE_PATH"/"MP3_TMP_DIR
#define AUDIO_FILE_MP3_PATH   APP_FILE_PATH"/"MP3_DIR


/////�����ļ����ؼ�¼
#define DOWNLOAD_FAILED_COUNT     3 //��������ʧ�ܺ�������
#define AUDIO_FILE_RECORD     "donw_record.dat"
#define TEMP_AUDIOFILE_NAME   "temppack"
#define TEMP_FILE_TYPE        "zip"
#define TEMP_AUDIOFILE_DIR   "down_audio"

#define ERR_BUSY_FIALED (-8)


#define DOWN_AUDIO_FILE_MAX   20//���֧����������

#define DOWN_AUDIO_UZIP_MAXSIZE   (2*1024*1024) //��ѹ����ʹ��1M

#define DOWN_AUDIO_UZIP_BACKUP_SIZE   (300*1024) //�ж��ƶ�ѹ�����Ĳ���С

#define DOWN_AUDIO_PATH_LEN   (128) //�����ļ�·��������


enum{
	AUDIO_FILE_NOTASK = 0,  //���ļ���������
	AUDIO_FILE_NEW_TASK,	//��������δ����
	AUDIO_FILE_DOWN_FINSH,  //�������
	AUDIO_FILE_UNPACK,      //��ɽ�ѹ
	AUDIO_FILE_REPLACE,		//��ɲ���

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
	int donw_flag; //��ǰ����״̬
	char pack_file[64+1];//��ʱ�洢���ļ�·�� ��ѹ����֮����Ҫɾ���ڳ��ռ�
}file_downl_param;

typedef struct audio_downl_param_{
	char request_id[50];
	int language;  //���Ա�ʶ
	file_downl_param file_task_data[DOWN_AUDIO_FILE_MAX]; //�Ƿ������ظ�ǩ�����ļ�
	int all_status;
	int Last_err;
	int failed_cont;//��¼���Դ���
}audio_downl_param;

typedef struct _signed{
	int signed_type;	
	char sign[256+1];
	uint32_t sign_len;
}signed_struct;





int file_param_record_save(audio_downl_param *fileparam);

int file_param_record_read(audio_downl_param *fileparam);



void init_audiofileparam(void);

//��ѵÿ���������� ���������������
int aduio_download_task(void);

//��ȡ��������ʵ��
audio_downl_param *get_audiofile_ins(void);


//��������һ���ļ� 
int onefile_download_func(char *file_url,int file_size,char *file_path,signed_struct *signed_va);


//��ѹ������ԭ���ļ�
int unpack_zipfile_topath(char *file_name);

//�ж��Ƿ��ǽ���ļ�
int jug_is_amtfile(char * filename);

//�ӳ���Ŀ¼���ǿ����ļ�����Ŀ¼��  delete_flag �Ƿ񿽱���ɾ��olddirԭ�ļ� 1ɾ�� 0 ��ɾ��
int copy_onedir_to_newdir(char* olddir,char *newdir,int delete_flag);

//�����ļ�У��ֵ�ж��봫��У��ֵ�Ƿ�һ��
//int verify_file_signature(const char*srcpath,int sign_type,char *insign,int sign_len);


#ifdef __cplusplus
	}/*"C" */
#endif
	
#endif  


