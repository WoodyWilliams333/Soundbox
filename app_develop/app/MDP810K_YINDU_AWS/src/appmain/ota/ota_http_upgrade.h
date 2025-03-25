/* Copyright (C) 2019 RDA Technologies Limited and/or its affiliates("RDA").
 * All rights reserved.
 *
 * This software is supplied "AS IS" without any warranties.
 * RDA assumes no responsibility or liability for the use of the software,
 * conveys no license or title under any patent, copyright, or mask work
 * right to the product. RDA reserves the right to make changes in the
 * software without notification.  RDA also make no representation or
 * warranty that such application will be suitable for the specified use
 * without further testing or modification.
 */
 
#include <appdatatypedef.h>
#include "cJSON.h"
#include <semaphore.h>


#ifndef _FOTA_HTTP_UPGRADE_H
#define _FOTA_HTTP_UPGRADE_H

#ifdef __cplusplus
	extern "C" {
#endif


//#ifndef bool
//#define bool 
//#endif

//#ifdef QL_APP_FEATURE_HTTP_FOTA
	
	
	/*========================================================================
	 *	function Definition
	 *========================================================================*/
typedef enum 
{
	FOTA_DATA_DOWN_INIT,		//��ʼ�׶�
	FOTA_DATA_DOWN_IMG,		//img
}e_fota_data_stage;

typedef enum 
{
	FOTA_HTTP_DOWN_INIT,		//��ʼ�׶�
	FOTA_HTTP_DOWN_DOWNING,		//������
	FOTA_HTTP_DOWN_INTR,		//���ر��ж�
	FOTA_HTTP_DOWN_SUCCESS,		//���سɹ�
	FOTA_HTTP_DOWN_NOSPACE,		//û�пռ�
	FOTA_HTTP_DOWN_FAIL,    //���������쳣
}e_fota_down_stage;

typedef struct 
{
    appbool is_show;			//�Ƿ���ʾ����
    unsigned int total_size;		//�ļ��ܹ���С
    unsigned int dload_size;		//�Ѿ����ش�С
    unsigned int file_size;			//�ϴ������жϱ�����ļ���С
}fota_http_progress_t;



typedef enum ota_verify {
	OTA_VERIFY_NONE		= 0,
	OTA_VERIFY_CRC32	= 1,
	OTA_VERIFY_MD5		= 2,
	OTA_VERIFY_SHA1		= 3,
	OTA_VERIFY_SHA256	= 4,

} ota_verify_t;


typedef enum ota_protocol {
	OTA_PROTOCOL_FILE	= 0,  //�ļ�·�� ������ֱ������
	OTA_PROTOCOL_HTTP	= 1,
	OTA_PROTOCOL_HTTPS	= 2,
	OTA_PROTOCOL_FTP	= 3,
	
} ota_protocol_t;


typedef struct {
	unsigned int	size;
	char 			version[50];
	char 			url[1024];
	ota_verify_t	verify;
	char			verify_value[300];
	char            net_mode;
	unsigned char	down_flag;//�ϵ������ж�
	unsigned int	star_size;
	char	data_type;//img:1 pkg:0
	int	succesCn;//�ɹ�����
	int	totalCn; //�ܴ���
	int	endtime; //ƽ����ʱ
}ota_params;

//�������������ļ�
#define SYSTEM_UPGRADE_FILE     OTA_DIR"/yyx.ini"
#define SYSTEM_UPGRADE_TMP     OTA_DIR"/yyx.ini_"
#define SYSTEM_IHDR_FILE     OTA_DIR"/ihdr.ini"
#define SYSTEM_HASH_FILE     OTA_DIR"/hash.ini"

#define SYSTEM_AUDIODOWN_FILE     OTA_DIR"/audiodown.ini"
#define SYSTEM_AUDIODOWN_TMP     OTA_DIR"/audiodown.ini_"


#define TYPE_UNKNOWN      0
#define TYPE_PKG_DOWN     1
#define TYPE_FW_DOWN      2

int ota_param_save(ota_params *otaparam,const char *name);
int ota_param_read(void);
void ota_param_upgrade(void);
int ota_http_app_thread(void* parm);
void ota_update_arrived(char * data,int len);
int lock_ota_para_file(void);
int unlock_ota_para_file(void);
int check_ota_para_file(void);
void init_https_ota(void);
void ota_success(void);


int OtaDownload(void);
int SaveSysPara(void);
//int audiodown_param_save(ota_params *otaparam,const char *name);
void testOTA(void);

sem_handle_t get_ota_Sem(void);

//#endif
#ifdef __cplusplus
	}/*"C" */
#endif
	
#endif   /*DATACALL_DEMO_H*/
