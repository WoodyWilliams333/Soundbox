#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"

#include "http.h"
#include "tersharedata.h"






/* 返回ch字符在sign数组中的序号 */  
static int getIndexOfSigns(char ch)  
{  
    if(ch >= '0' && ch <= '9')  
    {  
        return ch - '0';  
    }  
    if(ch >= 'A' && ch <='F')   
    {  
        return ch - 'A' + 10;  
    }  
    if(ch >= 'a' && ch <= 'f')  
    {  
        return ch - 'a' + 10;  
    }  
    return -1;  
} 

/* 十六进制数转换为十进制数 */  
int pub_hex2dec(char *source)  
{  
    int sum = 0;  
    int t = 1;  
    int i = 0, len = 0;  
   
    len = strlen(source);
    if(len==0){
	return 0;  
   }
    for(i=len-1; i>=0; i--)  
    {  
        sum += t * getIndexOfSigns(*(source + i));  
        t *= 16;  
    }    
   
    return sum;  
}  




int FormHttpPacket(char *pOut,char *pPosInfo,char *pIn,const char *pUrl,const char *pHost, METHOD method)
{	

    if (method == PUT) {
        sprintf(&pOut[strlen(pOut)], "%s %s HTTP/1.1\x0D\x0A", "PUT", pUrl);
    }
    else if (method == POST) {
        sprintf(&pOut[strlen(pOut)], "%s %s HTTP/1.1\x0D\x0A", "POST", pUrl);
    } else {
        sprintf(&pOut[strlen(pOut)], "%s %s?%s HTTP/1.1\x0D\x0A", "GET", pUrl, pIn);
    }
    sprintf(&pOut[strlen(pOut)], "HOST: %s\x0D\x0A", pHost);

    if (method == POST||method == PUT) {

		sprintf(&pOut[strlen(pOut)], "Connection:Keep-Alive\r\n");
		sprintf(&pOut[strlen(pOut)], "Accept:*/*\r\n");

		//	sprintf(&pOut[strlen(pOut)], "Content-Type: %s\x0D\x0A", "text/plain");
		sprintf(&pOut[strlen(pOut)], "Content-Length: %d\x0D\x0A", strlen(pIn));
		sprintf(&pOut[strlen(pOut)], "Cache-Control:no-cache\r\n");

		sprintf(&pOut[strlen(pOut)],"Content-Type: %s\r\n", "application/json");
	
	} else {
        sprintf(&pOut[strlen(pOut)], "Cache-Control: max-age=0\x0D\x0A");
    }

	if(pPosInfo != NULL && strlen(pPosInfo) > 0){
		sprintf(&pOut[strlen(pOut)], "X-POS-INFO: %s\x0D\x0A",pPosInfo);
	}
	
    sprintf(&pOut[strlen(pOut)], "\x0D\x0A");

	if(method == POST||method == PUT)
	{
		strcpy(&pOut[strlen(pOut)], pIn);
	}
	
    return strlen(pOut);
}

int GetHttpBody(char *psTxdData,char **psTxdDataOut, int *pMsgLen)
{
	char *pLengEnd = NULL, *pLengStart = NULL,*pLengEnd1 = NULL, *pLengStart1 = NULL;
    char tmpData[2*1024] = {0};
    char templen[12] = {0};
	uint8_t ucFlg = 0;
	int  iMsgLen1=0, iMsgLen2=0;
    pLengStart = (char *)psTxdData;
    pLengEnd= strstr((char *)psTxdData, "\r\n\r\n");
    if(pLengEnd == NULL){
        return -1;
    }
    pLengEnd += 4;
	memset(tmpData,0,sizeof(tmpData));
    memcpy(tmpData, pLengStart, pLengEnd-pLengStart);
    pub_strupper(tmpData); 
    logger_debug("GetHttpBody tmpData len =%d\n",pLengEnd-pLengStart);
    pLengStart = strstr(tmpData, "CONTENT-LENGTH:");
    if(pLengStart != NULL)
    {
    	pLengStart += 15;
    	pLengEnd = strstr(pLengStart, "\r\n");
        memset(templen, 0, sizeof(templen));
    	memcpy(templen, pLengStart, pLengEnd-pLengStart);
        pub_trimspcstr(templen, ' ');
    	*pMsgLen = atoi(templen);

        pLengStart = NULL;
        pLengStart = strstr((char *)psTxdData, "\r\n\r\n");
        if(pLengStart == NULL){
            return -1;
        }
        pLengStart += 4;
    }
    else
    {
        
        pLengStart = strstr((char *)psTxdData, "\r\n\r\n");
        pLengStart += 4;
        pLengEnd = strstr((char *)pLengStart, "{");
        memcpy(templen, pLengStart, pLengEnd-pLengStart-2);
	 iMsgLen1= pub_hex2dec(templen);
//	 logger_debug("iMsgLen1=%d\n",iMsgLen1);
	 if(memcmp(pLengEnd+iMsgLen1,"\r\n0\r\n\r\n",7)!=0){
	 	
		if(memcmp(pLengEnd+iMsgLen1, "\r\n",2)==0){
              //pLengStart1=strstr(pLengEnd+iMsgLen1-1, "\r\n");
              pLengStart1=pLengEnd+iMsgLen1+2;
		
		 //	logger_hexdump("pLengStart1", pLengStart1, 16);
		//	pLengStart1 += 2;
		//	logger_hexdump("pLengStart11", pLengStart1, 16);
			pLengEnd1=strstr((char *)pLengStart1, "\r\n");
			if(pLengEnd1 !=NULL){
			//	logger_hexdump("pLengEnd1", pLengEnd1, 16);
				memset(templen,0,sizeof(templen));
				if(pLengEnd1-pLengStart1 <=4){
	 			memcpy(templen, pLengStart1, pLengEnd1-pLengStart1);
			//	   logger_debug("pLengEnd1-pLengStart=%d\n",pLengEnd1-pLengStart1);
				//    logger_debug("templen=%s\n",templen);
				iMsgLen2= pub_hex2dec(templen);
					}
				pLengEnd1+=2;
			}





		}
		
	 }
      //  logger_debug("iMsgLen2=%d\n",iMsgLen2);
//	 app_kb_get_key_ms(-1);
        *pMsgLen = iMsgLen1+iMsgLen2;//  pub_hex2dec(templen);
        ucFlg = 1;
    }

	*psTxdDataOut = (char *)malloc(*pMsgLen + 1);
	if (NULL != *psTxdDataOut) {
		memset(*psTxdDataOut, 0, *pMsgLen + 1);
		if (1 == ucFlg){
			
			memcpy(*psTxdDataOut, pLengEnd, iMsgLen1);
			if( (iMsgLen2 > 0) &&(pLengEnd1 != NULL)){
				memcpy(*psTxdDataOut+iMsgLen1, pLengEnd1, iMsgLen2);
			}


		}
		else{
			memcpy(*psTxdDataOut, pLengStart, *pMsgLen);
		}
	}
    
    return 0;
}

