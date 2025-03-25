/****************************************************************************
NAME
	https.h - httpsͨѶ�ӿ�
****************************************************************************/
#ifndef _HTTPS_H
#define _HTTPS_H
#include "appdef.h"
#include "cJSON.h"
#include "../../../appmain/ota/ota_http_upgrade.h"

typedef struct {
    uint32_t type;
    uint32_t offset;
    uint32_t len;
    char path[64];
}firm_info_t;

#define MAX_FIRMWARE_NUM 32



typedef struct {
    char magic[4];  // npup
    uint32_t size;  // length of the whole image file
    uint32_t firmware_num; // firmware num
    firm_info_t firms_info[MAX_FIRMWARE_NUM];
} image_hdr_t;
	
typedef enum pkg_file {
	TASK_FIRMWARE_FILE		= 9,    //�̼�
	TASK_APP_FILE					= 10,    //Ӧ�ó���
	TASK_FONT_FILE				= 11,    //�ֿ��ļ�
	TASK_DYNAMIC_LIB_FILE	= 12,    //��̬��
	TASK_DATA_FILE				= 13,    //�����ļ�
	TASK_DESKTOP_FILE			= 15,    //�����ļ�

} pkg_file_t;

int https_down(ota_params *ota_param, char *fileName);
int parse_path(char *input,char *file_path);


int sent_http_method(char *method,char *http_url,char* opk_key,char* body,int bodyLen,unsigned char *outData,int *outLen,int get_header_flag);


#endif //_MISHTTPS_H


