#include "base64.h"
#include <ctype.h>



//++++++++++++++++++++++++++++����RFSIM���ֽ��� wzl_rfsimmg 20101112 ��++++++++++++++++++

/*====================================================================  
 Base64���뺯��  
 btSrcָ�򱻱�������ݻ�����  
 iSrcLen����������ݵĴ�С���ֽڣ�  
 btRetָ����Base64��������ݻ�����  
 piRetLenָ����Base64��������ݻ������ĳ���  
 ��btRetΪNULL��������0��piRetLen����btSrc��Base64�������軺�����Ĵ�С  
 ��btRetָ��Ļ�����̫С����������-1  
 ����������ʵ��btSrc��Base64�������軺�����Ĵ�С  
=====================================================================*/  
int EncodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen) //Base64����   
{   
    int i = 0, j = 0, k = 0 ;   
    uint8_t EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";   
       
    i = (iSrcLen+2) / 3 * 4 ; //��ȡbtSrc��Base64�������軺�����Ĵ�С   
    if(btRet != NULL)   
    {   
        //if(*piRetLen < i) //Base64�������軺����ƫС   
        //    return 0 ;   
        *piRetLen = i ; //*piRetLen����btSrc��Base64����Ļ�������С   
    }   
    else  
    {   
        *piRetLen = i ;   
        return 0 ;   
    }   
  
    k = iSrcLen - iSrcLen % 3 ;   
    for(i=j=0; i<k; i+=3) //����   
    {   
        btRet[j++] = EncodeBase64Map[(btSrc[i]>>2)&0x3F] ;   
        btRet[j++] = EncodeBase64Map[((btSrc[i]<<4) + (btSrc[i+1]>>4))&0x3F] ;   
        btRet[j++] = EncodeBase64Map[((btSrc[i+1]<<2) + (btSrc[i+2]>>6))&0x3F] ;   
        btRet[j++] = EncodeBase64Map[btSrc[i+2]&0x3F] ;   
    }   
    k = iSrcLen - k ;   
    if(1 == k)   
    {   
        btRet[j++] = EncodeBase64Map[(btSrc[i]>>2)&0x3F] ;   
        btRet[j++] = EncodeBase64Map[(btSrc[i]<<4)&0x3F] ;   
        btRet[j++] = '=' ;    
		btRet[j++] = '=' ; 
    }   
    else if(2 == k)   
    {   
        btRet[j++] = EncodeBase64Map[(btSrc[i]>>2)&0x3F] ;   
        btRet[j++] = EncodeBase64Map[((btSrc[i]<<4) + (btSrc[i+1]>>4))&0x3F] ;   
        btRet[j++] = EncodeBase64Map[(btSrc[i+1]<<2)&0x3F] ;   
        btRet[j++] = '=' ;   
    }   

    return j ;   
}   
  
/*====================================================================   
 Base64���뺯��   
 btSrcָ�򱻽�������ݻ�����   
 iSrcLen����������ݵĴ�С���ֽڣ�   
 btRetָ����Base64��������ݻ�����   
 piRetLenָ����Base64��������ݻ������ĳ���   
 ��btRetΪNULL��������0��piRetLen����btSrc��Base64�������軺�����Ĵ�С   
 ��btRetָ��Ļ�����̫С����������-1   
 ����������btSrc��Base64�������軺�����Ĵ�С   
=====================================================================*/   
int DecodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen) //Base64����   
{   
    int i = 0, j = 0 ;   
    uint8_t EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";   
    uint8_t DecodeBase64Map[256] = {0} ;   
       
    for(j = iSrcLen; j>0 && '='==btSrc[j-1]; --j) ; //����=��   
    i = (j/4)*3+(j%4+1)/2; //�������� �ַ����ĳ���   
       
    if(btRet != NULL)   
    {   
       // if(*piRetLen < i) //Base64�������軺����ƫС   
          //  return 0 ;   
        *piRetLen = i ; //*piRetLen����btSrc��Base64����Ļ�������С   
    }   
    else  
    {   
        *piRetLen = i ;   
        return 0 ;   
    }   
  
    j = sizeof(EncodeBase64Map) ;   
    for(i=0; i<j; ++i)   
        DecodeBase64Map[ EncodeBase64Map[i] ] = i ;   
    for(i=j=0; i<iSrcLen; i+=4)   
    {   
        btRet[j++] = DecodeBase64Map[btSrc[i  ]] << 2 | DecodeBase64Map[btSrc[i+1]] >> 4 ;   
        btRet[j++] = DecodeBase64Map[btSrc[i+1]] << 4 | DecodeBase64Map[btSrc[i+2]] >> 2 ;   
        btRet[j++] = DecodeBase64Map[btSrc[i+2]] << 6 | DecodeBase64Map[btSrc[i+3]] ;   
    }   
  
    return *piRetLen ;   
}

