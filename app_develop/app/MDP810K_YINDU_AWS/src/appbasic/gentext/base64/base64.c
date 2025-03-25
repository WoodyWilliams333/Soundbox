#include "base64.h"
#include <ctype.h>



//++++++++++++++++++++++++++++增加RFSIM福分交易 wzl_rfsimmg 20101112 ↓++++++++++++++++++

/*====================================================================  
 Base64编码函数  
 btSrc指向被编码的数据缓冲区  
 iSrcLen被编码的数据的大小（字节）  
 btRet指向存放Base64编码的数据缓冲区  
 piRetLen指向存放Base64编码的数据缓冲区的长度  
 若btRet为NULL函数返回0，piRetLen传回btSrc的Base64编码所需缓冲区的大小  
 若btRet指向的缓冲区太小，函数返回-1  
 否则函数返回实际btSrc的Base64编码所需缓冲区的大小  
=====================================================================*/  
int EncodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen) //Base64编码   
{   
    int i = 0, j = 0, k = 0 ;   
    uint8_t EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";   
       
    i = (iSrcLen+2) / 3 * 4 ; //获取btSrc的Base64编码所需缓冲区的大小   
    if(btRet != NULL)   
    {   
        //if(*piRetLen < i) //Base64编码所需缓冲区偏小   
        //    return 0 ;   
        *piRetLen = i ; //*piRetLen返回btSrc的Base64编码的缓冲区大小   
    }   
    else  
    {   
        *piRetLen = i ;   
        return 0 ;   
    }   
  
    k = iSrcLen - iSrcLen % 3 ;   
    for(i=j=0; i<k; i+=3) //编码   
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
 Base64解码函数   
 btSrc指向被解码的数据缓冲区   
 iSrcLen被解码的数据的大小（字节）   
 btRet指向存放Base64解码的数据缓冲区   
 piRetLen指向存放Base64解码的数据缓冲区的长度   
 若btRet为NULL函数返回0，piRetLen传回btSrc的Base64解码所需缓冲区的大小   
 若btRet指向的缓冲区太小，函数返回-1   
 否则函数返回btSrc的Base64解码所需缓冲区的大小   
=====================================================================*/   
int DecodeBase64(uint8_t *btSrc, int iSrcLen, uint8_t *btRet, int *piRetLen) //Base64解码   
{   
    int i = 0, j = 0 ;   
    uint8_t EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";   
    uint8_t DecodeBase64Map[256] = {0} ;   
       
    for(j = iSrcLen; j>0 && '='==btSrc[j-1]; --j) ; //忽略=号   
    i = (j/4)*3+(j%4+1)/2; //计算解码后 字符串的长度   
       
    if(btRet != NULL)   
    {   
       // if(*piRetLen < i) //Base64解码所需缓冲区偏小   
          //  return 0 ;   
        *piRetLen = i ; //*piRetLen返回btSrc的Base64解码的缓冲区大小   
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

