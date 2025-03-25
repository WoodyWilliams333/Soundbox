/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */


#ifndef __SM3_H__H__
#define __SM3_H__H__
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#define SM3_len 256
#define SM2_WORDSIZE 8
#define SM2_NUMBITS 256
#define SM2_NUMWORD	(SM2_NUMBITS / SM2_WORDSIZE) //32
typedef struct {
	unsigned long state[8];
	unsigned long length;
	unsigned long curlen;
	unsigned char buf[64];
} SM3_STATE;


void SM3_init(SM3_STATE *md);
void SM3_compress(SM3_STATE *md);
void SM3_process(SM3_STATE *md, unsigned char *buf, int len);
void SM3_done(SM3_STATE *md, unsigned char hash[]);
void SM3_256(unsigned char buf[], int len, unsigned char hash[]);

#if 0
static void print_hex(const char *prefix, void *src, int src_len)
{
    int i = 0x00;
   
    if (NULL != prefix) {
        printf("%s", prefix);
    } 
    for (i = 0x00; i < src_len;) {
        printf("%02x", (unsigned char)*((unsigned char *)src + i));
        i++;
        if (0x00 == ( i % 16)) {
            printf("\n");
        }
    }
    printf("\n");
}
#endif

#ifdef __cplusplus
}
# endif
#endif
