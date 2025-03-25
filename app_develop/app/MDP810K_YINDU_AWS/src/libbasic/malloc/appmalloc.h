/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-03-15 11:33:05
 * @LastEditors: YangJing
 * @LastEditTime: 2021-05-14 10:35:13
 */
#ifndef _APP_MALLOC_H_
#define _APP_MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <malloc.h>

#if defined(CFG_LOGGER_ON)
//#define _USE_MEM_MONITOR_    // ���������Լ��TMS���ڴ�ʹ�����, ��ʽ�治��, �ή��Ч��!
#endif

#ifdef _USE_MEM_MONITOR_

void *app_malloc(size_t size);
void app_free(void *ptr);

#else

#define app_malloc  malloc
#define app_free    free

#endif

void app_printftmsmem(void);



#ifdef __cplusplus
}
#endif

#endif