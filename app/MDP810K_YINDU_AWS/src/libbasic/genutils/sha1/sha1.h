/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-03-30 11:39:31
 * @LastEditors: YangJing
 * @LastEditTime: 2021-03-30 11:42:24
 */
#ifndef _SHA1_H_
#define _SHA1_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{ 
    unsigned long Total[2]; 
    unsigned long State[5]; 
    unsigned char Buffer[64]; 
}SHA1_CONTEXT; 
typedef SHA1_CONTEXT* LP_SHA1_CONTEXT;


void SysSha1Init(LP_SHA1_CONTEXT ctx); 
int SysSha1Update(LP_SHA1_CONTEXT ctx , const unsigned char * pData, unsigned long ulLength); 
int SysSha1Fina(LP_SHA1_CONTEXT ctx  , unsigned char digest[20]);

int SysSha1Calc(const void * pvData, unsigned long ulLength, void * pvHash20);

#ifdef __cplusplus
}
#endif

#endif