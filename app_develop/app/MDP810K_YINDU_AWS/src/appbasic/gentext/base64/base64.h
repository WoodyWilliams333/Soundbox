#ifndef _AFX_BASE64N_H
#define _AFX_BASE64N_H


#include <stdio.h>

int EncodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen); //Base64���� 

int DecodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen); //Base64����   

#endif

