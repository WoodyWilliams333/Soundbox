#ifndef HTTP__H
#define HTTP__H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {		
    POST,
    GET,  
    PUT,    
} METHOD;

int FormHttpPacket(char *pOut,char *extraHeadInfo,char *pIn,const char *pUrl,const char *pHost, METHOD method);
int GetHttpBody(char *psTxdData,char **psTxdDataOut, int *pMsgLen);

int pub_hex2dec(char *source);  


#ifdef __cplusplus
}
#endif

#endif

