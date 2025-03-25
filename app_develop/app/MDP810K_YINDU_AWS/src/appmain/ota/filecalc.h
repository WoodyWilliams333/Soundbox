/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-03-30 16:13:10
 * @LastEditors: YangJing
 * @LastEditTime: 2021-03-30 16:23:34
 */

#ifndef _FILE_CALC_H_
#define _FILE_CALC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "https.h"

#define MAX_SIZE_BUFF   10*1024*1024
extern int ota_file_read(const char *name,char *outData,int readLen);
extern int ota_file_remove(void);
extern int ota_file_check(ota_params *ota_param,char *file_path);
extern int ota_file_save(const char *name,char *content,int len,int type);
extern int hash_final(ota_params *ota_param);
extern int hash_init(ota_params *ota_param);
extern int hash_update(ota_params *ota_param,char *data,int len);
#ifdef __cplusplus
}
#endif

#endif