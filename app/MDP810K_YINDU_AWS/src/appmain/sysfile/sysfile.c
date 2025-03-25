#include <stdio.h>
#include <string.h>
#include <ped_gm.h>
#include "basicext.h"

#include "tts_play.h"
#include "task_thread.h"
#include "fixaudio.h"
#include "tersharedata.h"
#include "system.h"
#include "codestool.h"

//#define TEST_SN_PRODUCT_UAT

#ifdef TEST_SN_PRODUCT_UAT


#if 1//H81023022200003 //测试环境
 const char aws_client_cert_H81023022200003[] = \
 {
	 \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWjCCAkKgAwIBAgIVAJHW7hcW2TYD/AXKjA1s8OuQq7pWMA0GCSqGSIb3DQEB\n" \
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n" \
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA1MjIwNzMy\n" \
"NTBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n" \
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCtGSONxJBfcfBhrGp4\n" \
"1A5m1u+bPZtuUUTFfP896vebyoa1Fq407lGpUWXsMUIxT1hCn+em5jn3LDPo5zke\n" \
"nOqdnHaf+DBFtupBOh4gSdpEC00tu/A0QIKf+U/cX9gZgn2hjFpQFTBVJjFunGzs\n" \
"y54we8RrwDnwfBVt6wuYGM09acmKqtBqrK/lslbWDin9q1HbGr9qmZqi9TemN6a4\n" \
"59xTpPvcAAiv7wI1y7btNhGemg5mI8Xo0rgxTGCVu7mJJboNnlXudyINdmd/NECk\n" \
"Zisx9nGYBGwV2fPil9iqgQtDCuwuqlZ7PKL0oHY1nFT4J9xSblIoVh38y8iRu4v7\n" \
"T3hxAgMBAAGjYDBeMB8GA1UdIwQYMBaAFG5MWQ4WFRvFSzp+xJiifdOUNeC1MB0G\n" \
"A1UdDgQWBBRkGsGfWmA2LMn+okITmIq8oLQwiDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n" \
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAuY0AtVU8X5Bsvcol4hycclVn\n" \
"YzALXVaNidxXcdrZtTMotx090ixxW2V6eLd901WUa/rPZi7WazTwGGmrc1fNs7uv\n" \
"29yN8E+Vqo1QSEZdlsxTT2zAfGmcoyCk4+jhT4pkT9y79pbC0sGvOUHAG64u52X4\n" \
"lPFD+PcbcIxyuA3PKaA1aAbwaWXP8ugkdLojriqfaIQWbfgyBb77gjdZrlEFhiUr\n" \
"dQUwVDi/stv/Rxc8FmgmM5nd0fdRPnl2Q4QBKXnwnTcekEci7ksCAgw+zTpFy6yq\n" \
"JlKfTSbabVigHQML7g8KWPGkPY29q5jj9WTI/TV6F7kDTCFDBpw9Xokz43Ltpw==\n" \
"-----END CERTIFICATE-----"
};


const char aws_client_key_H81023022200003[] = \
{
    \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEowIBAAKCAQEArRkjjcSQX3HwYaxqeNQOZtbvmz2bblFExXz/Per3m8qGtRau\n" \
"NO5RqVFl7DFCMU9YQp/npuY59ywz6Oc5HpzqnZx2n/gwRbbqQToeIEnaRAtNLbvw\n" \
"NECCn/lP3F/YGYJ9oYxaUBUwVSYxbpxs7MueMHvEa8A58HwVbesLmBjNPWnJiqrQ\n" \
"aqyv5bJW1g4p/atR2xq/apmaovU3pjemuOfcU6T73AAIr+8CNcu27TYRnpoOZiPF\n" \
"6NK4MUxglbu5iSW6DZ5V7nciDXZnfzRApGYrMfZxmARsFdnz4pfYqoELQwrsLqpW\n" \
"ezyi9KB2NZxU+CfcUm5SKFYd/MvIkbuL+094cQIDAQABAoIBAQCb8NbP4/JwmfQF\n" \
"+k8dNWUYDrBjeZfqRXqgM+C6RlD1X/oFcD5W3xBgaj1ZEHNieum3c9k8yZIU9BR7\n" \
"0Lrrsk/G1+siaHQMiiH1y0bSrdXdkRThi7t1R1ymg/MHRK0pJh7KB+hg1wXo3/SO\n" \
"gou6tCF56jZlIBLSbObdVG/ogQd9N7IJ7FrHQOSZJgEJrdsio3Uh+e8BtUlaZqj9\n" \
"mgORjiKT0y+TJupCcMdgSUvJQ3FCNab+ICAHTa/zISxxd3E0kOycdZFGsguchoWU\n" \
"kAB8ZJUFrcX32za+DaEQXp/HrNdmGMC/WSy/qbCXfkPuAkzb3xwo2gJf01RJ2cv1\n" \
"8SiBvpZxAoGBANY2T3Whc4uhFpP01yK03ONgvcv5+wqVuiVtMbdyB6ofJe+G89K/\n" \
"cZ2mAj1RwA0Uc4L65fsbfJeCWQrRoU8Md+tG+PXSwQk8LDruwf4mxcc8Uh91ZEFy\n" \
"XryBM9WhFvjmKH4hu5k8bEu3Rc32A8WWrthlUtrxaTzsDLgtRtkSj98tAoGBAM7d\n" \
"nDsPuj3R12Sd/He34fdRvlHOIK0c2mqXz9IvMsUOTT9xc1TPWqq1bdIr3pcj6t4m\n" \
"ckUPw8Uupg1zyL/YSwd66KmCv/ovjrd1P6QzOa67cgQ197Ymz9hkcLGlHcevR7/J\n" \
"li032S5DkpFWAfAPIxov7rnl7SSmPvITkVytAujVAoGAEYoE24bKpSYdaSPk8YyJ\n" \
"gXyMTcU8DtPPl/zm0zRc+ErwmjocgKb4MIZFLKwi429HPfQ5HGRVwToE/GPJp2VH\n" \
"9FWtUMNe1ti8bl7aN2sJSpTfzH+aI9mvdBPIILe938dIjXtJlvRhkZmB96krCeSa\n" \
"kFFLhW26xig1qmbapC9m5EkCgYBkPKXTSI+qHOAN9S+8ovFvccCSyxqyR2TeealN\n" \
"42jqaz+rGkIUOlVomnkYegFloxXPhzmflT/7b9sucYg4zYmtmjTazmxPwnOZGcs4\n" \
"uUmeDV32BGB/dtcHt8OTkLqZY6mUmQ2X45PtAvkmS1KtC+iqa8d1dKAwPg4KJsks\n" \
"6viZ8QKBgCBqNRxzCeRz9JLcz6LjkrzuSO6cXJQFXYKQr4D82L2vKDk/U5mWOxof\n" \
"SsvZIRnP6Piog53avBCWpk5QA9LPxz473HE5//Zae6W1hN+/AgZejgEtp0ez1z/s\n" \
"5mcY3RzNjYUZiIk20piHd2HXkdiZ6EZS9y9FTns4mVEWMbXKAECB\n" \
"-----END RSA PRIVATE KEY-----"
};
#endif




#endif 

/**
* @brief mqtt参数字符串中提取对应参数
* @param[in] inStr  mqtt参数字符串
* @param[in] strTag tag
* @param[out] strTag outValue根据tag查找到的返回数据
* @param[in] outSize outValue缓存空间
* @retval 大于0成功，strTag内容大小；小于0失败
*/
int get_para_for_string(const char *inStr, const char *strTag, char *outValue, int outSize)
{
    char *start = NULL, *end = NULL;
    char temp[128] = {0};
    int len = 0;
    if(NULL == inStr || NULL == strTag || NULL == outValue){
        return -1;
    }
    //logger_debug("inStr = %s\n", inStr); 
    //logger_debug("strTag = %s\n", strTag); 
    memset(temp, 0, sizeof(temp));
    snprintf(temp, sizeof(temp), "<%s>", strTag);
    len = strlen(temp);
    start = strstr(inStr, temp);
    if(NULL != start){
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "</%s>", strTag);
        end = strstr(start, temp);

        if(NULL != end && (end - (start+len) < outSize) ){
            memcpy(outValue, (start+len), (end - (start+len)));
            //logger_debug("outValue = %s\n", outValue); 
            return (end - (start+len));
        }
    }
    //logger_debug("return -1\n"); 
    return -1 ;
}

int get_para_for_string_ptr(const char *inStr, const char *strTag, char **outValue)
{
	char *start = NULL, *end = NULL;
    char temp[128] = {0};
    int len = 0;
    if(NULL == inStr || NULL == strTag || NULL == outValue){
        return -1;
    }
    //logger_debug("inStr = %s\n", inStr); 
    //logger_debug("strTag = %s\n", strTag); 
    memset(temp, 0, sizeof(temp));
    snprintf(temp, sizeof(temp), "<%s>", strTag);
    len = strlen(temp);
    start = strstr(inStr, temp);
    if(NULL != start){
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "</%s>", strTag);
        end = strstr(start, temp);
        if(NULL != end ){
			*outValue = malloc((end - (start+len))+1);
			if(*outValue){
				memset(*outValue,0,(end - (start+len))+1);	
				memcpy(*outValue, (start+len), (end - (start+len)));
			}
            //logger_debug("outValue = %s\n", *outValue); 
            return (end - (start+len));
        }
    }
    //logger_debug("return -1\n"); 
    return -1 ;

}

extern char aws_root_cert[];

/**
* @brief 获取mqtt参数
* @retval 无
*/
void get_ali_mqtt_para(void)
{
    unsigned char *p = NULL;
    logger_debug("%s\n", __FUNCTION__);  
    p = get_mqtt_data();
    logger_debug("mqtt = %p\n", p);  

    if(NULL != p){
        //logger_debug("mqtt_str = %s\n", p); 
        get_para_for_string((char *)p, "PRODUCTKEY", stSysTemp.product_key, sizeof(stSysTemp.product_key));
        get_para_for_string((char *)p, "DEVICENAME", stSysTemp.device_name, sizeof(stSysTemp.device_name));
        get_para_for_string((char *)p, "DEVICESECRET", stSysTemp.device_secret, sizeof(stSysTemp.device_secret));
		
        //snprintf(stSysTemp.server_url,sizeof(stSysTemp.server_url),"%s%s",stSysTemp.product_key,MQTT_SERVER_AUTO_DNS);	
		write_datastream_to_file((char*)MQTT_CA_CERT,(uint8_t*)aws_root_cert,strlen(aws_root_cert),0);

#ifdef TEST_SN_PRODUCT_UAT
		write_datastream_to_file((char*)MQTT_CLIENT_CERT,(uint8_t*)aws_client_cert_H81023022200003,strlen(aws_client_cert_H81023022200003),0);
		write_datastream_to_file((char*)MQTT_CLIENT_KEY,(uint8_t*)aws_client_key_H81023022200003,strlen(aws_client_key_H81023022200003),0);

		snprintf(stSysTemp.device_name,sizeof(stSysTemp.device_name),"%s","H81023022200003");
		snprintf(stSysTemp.product_key,sizeof(stSysTemp.product_key),"%s","ilYS8iBwYuq");
		
		stSysTemp.ca = (char*)aws_client_cert_H81023022200003;
		stSysTemp.key = (char*)aws_client_key_H81023022200003;
#else 
	   get_para_for_string_ptr((char *)p, "POS_CERT", &stSysTemp.ca);
	   get_para_for_string_ptr((char *)p, "POS_PRI_KEY", &stSysTemp.key);
	   write_datastream_to_file((char*)MQTT_CLIENT_CERT,(uint8_t*)stSysTemp.ca,strlen(stSysTemp.ca),0);
	   write_datastream_to_file((char*)MQTT_CLIENT_KEY,(uint8_t*)stSysTemp.key,strlen(stSysTemp.key),0);

#endif 
		logger_debug("stSysTemp.device_name = %s\n", stSysTemp.device_name);  
		logger_debug("stSysTemp.product_key = %s\n", stSysTemp.product_key);  
		logger_debug("stSysTemp.ca = %s\n", stSysTemp.ca);	
		logger_debug("stSysTemp.key = %s\n", stSysTemp.key);  

		sys_free(p);
	}

	logger_debug("mqtt_str = %s\n", p); 

	
}


