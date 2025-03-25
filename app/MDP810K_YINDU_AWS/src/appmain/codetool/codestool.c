#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codestool.h"
#include "appfile.h"
#include "logger.h"
#include "system.h"
#include "fixaudio.h"
#include "appsys.h"
#include "system.h"


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif 

#define ONE_RDWR_LEN   4*4096  //单次操作文件的大小

int GetTtsStrAudioAmt(char* srcStr,char* AmtStr,char *audioStr)
{
	char*q=NULL;
	int strLen,FindFlag = -1,offSet = 0;
	if(srcStr == NULL || AmtStr ==NULL){
		return -1;
	}	
	strLen = strlen(srcStr);
	q = srcStr + strLen;
	//app_debug("AmtStr =%s\n",srcStr);
	while(q != NULL && q > (srcStr-1))
	{
		//app_debug("*q=%d\n",*q);
		if((*q>='0' && *q <= '9') || *q== '.' ){
			if(offSet > 0){			
				memmove(&AmtStr[1],&AmtStr[0],offSet);	
			}
			AmtStr[0] = *q;
			FindFlag =1;
			offSet++;
		}else if(FindFlag == 1 ){
			break;
		}
		q--;
	}
	//app_debug("context=%s,q=%d\n",context,*q);
	q+=1;
	if(audioStr != NULL){
		memcpy(audioStr,srcStr,q-srcStr);
	}
	
	//app_debug("AmtStr=%s,audioStr=%s\n",AmtStr,audioStr);
	
	return 0;

}



int strSplit(const char *psrc,int psrc_len,char sign,proto_Items **proto_Item,int pdest_Num)
{

	int i = 0;
	int result = 0;
	int start = 0,end = 0;
	int len = 0;
	if(NULL == psrc || NULL == proto_Item)
	{
		return 0;
	}
	for(i = 0;i < psrc_len;i++)
	{

		if(result > pdest_Num ){
			break;	
		}

		if(psrc[i] == sign)
		{
			end = i;
			len = end - start;
			
			proto_Item[result] = (proto_Items*)malloc(sizeof(proto_Items));
			if(proto_Item[result] != NULL)
			{
				proto_Item[result]->items_value = (char *)malloc(len+1);
				
				if(proto_Item[result]->items_value != NULL)
				{
					
					memcpy(proto_Item[result]->items_value,psrc+start,len);
					proto_Item[result]->itemLen = len;
					proto_Item[result]->items_value[len] = '\0';
					result++;
					start = end+1;
				}else
				{
					free(proto_Item[result]);
					proto_Item[result] =NULL;
					return result;
				}
			}else
			{
				return result;
			}
			
		}
		
	}

	if(start != psrc_len && result < pdest_Num)
	{
		len = psrc_len-start;
		proto_Item[result] = (proto_Items*)malloc(sizeof(proto_Items));
		if(proto_Item[result] != NULL)
		{
			proto_Item[result]->items_value = (char *)malloc(len+1);
			if(proto_Item[result]->items_value != NULL)
			{
				memcpy(proto_Item[result]->items_value,psrc+start,len);
				proto_Item[result]->itemLen = len;
				proto_Item[result]->items_value[len] = '\0';
				result++;
				start = end+1;
			}else
			{
				free(proto_Item[result]);
					proto_Item[result] =NULL;
				return result;
			}		
		}else
		{
			return result;
		}
	}
	return result;
}

void free_SplitSpace(proto_Items **proto_Item,int pdest_Num)
{
	int i = 0;
	if(proto_Item == NULL || pdest_Num <= 0)
		return;
	
	for(i = 0;i < pdest_Num;i++)
	{
	
		if(proto_Item[i] !=NULL){
	
			if(proto_Item[i]->items_value != NULL)
			{
				free(proto_Item[i]->items_value);
				proto_Item[i]->items_value = NULL;
				proto_Item[i]->itemLen = 0;
			}
			
			free(proto_Item[i]);
			proto_Item[i] = NULL;
		}

	}
	return;
}

/*字符串替换
src 源字符串的首地址(buf的地址)
str1 被替换字符
str2 替换成的字符串
return 替换后字符串
*/

char* strRepl(char *srcStr,const char *str1,const char *str2)
{
	char* ptr = NULL,*src_ptr = srcStr;
	if(srcStr == NULL || str1 ==NULL || str2 ==NULL
		|| !strlen(srcStr))
		return srcStr;

	if(strcmp(str1,str2) == 0){
		return srcStr;
	}
		
	while((ptr = strstr(src_ptr,str1)) != NULL )
	{
		memmove(ptr + strlen(str2),ptr + strlen(str1),strlen(ptr) -strlen(str1)+1);
		memcpy(ptr,str2,strlen(str2));
		src_ptr = ptr + strlen(str2);
	}

	return srcStr;
}


//删除源字符串中的指定子串，使用strstr函数进行查找
char * deleteSubString(char * srcString, const char * subString)
{
	char *p = NULL;
	long len = 0;
    if (NULL==srcString||NULL==subString) {
        printf("Pointer is NULL\n");
        return NULL;
    }
    //指向第一个subString
    p = strstr(srcString, subString);
    if (NULL==p) {
        printf("subString is not exist\n");
        return NULL;
    }

    len = strlen(subString);
    while (p) {
        while (1) {
            //删除subString
            *p=*(p+len);
            if (*p=='\0') {
                break;
            }
            p++;
        }
        p=strstr(srcString, subString);
    }

    return srcString;
}

char * deleteSubString_1(char * srcString, const char * subString)
{
	char *p =NULL;
	long len;
	if (NULL==srcString||NULL==subString) {
        return NULL;
    }
    //指向第一个subString
    p = strstr(srcString, subString);
    if (NULL==p) {
        return NULL;
    }

    len = strlen(subString);

    while (1) {
        //删除subString
        *p=*(p+len);
        if (*p=='\0') {
            break;
        }
        p++;
    }

    return srcString;

}


void np_hex_to_string(uint8_t const *data, uint16_t length, char *hexString)
{
	uint16_t i = 0;

	if(hexString == NULL || data == NULL){
		return ;
	}

	for(i=0; i<length; i++)
	{
		sprintf(&hexString[i*2], "%02X", data[i]); 
	}

}

char char_upper(char s)
{
	if(s >='a' && s<='z')
	{
		s -= ('a'-'A');
	}
	return s;         
}

char char_lower(char s)
{
	if(s >='A' && s<='Z')
	{
		s -= ('A'-'a');
	}
	return s;
}

void np_lower(char *s)
{
    long i;
    long length = strlen(s);

        for (i=0; i<length; i++)
    {
        if(s[i]>='A' && s[i]<='Z')
        {
            s[i] -= ('A'-'a');
        }
    }
}

void np_upper(char *s)
{
    long i;
    long length = strlen(s);

        for (i=0; i<length; i++)
    {
        if(s[i]>='a' && s[i]<='z')
        {
            s[i] -= ('a'-'A');
        }
    }
}


/*
 将可读的16进制串合并成其一半长度的二进制串,"12AB"-->0x12AB
 */
 /*
static void np_asc2bcd(const char *psIAsc, int iAscLen, unsigned char *psOBcd)
{
	char Chtmp, ChBcd;
	int iCnt = 0;

	for(iCnt = 0; iCnt < iAscLen; iCnt += 2) {
		Chtmp = psIAsc[iCnt];
		if(Chtmp >= 'A') {
			Chtmp = Chtmp - 'A' + 0x0A;
		} else {
			Chtmp &= 0x0F;
		}

		ChBcd = (Chtmp << 4); // 获取BCD的高位
		Chtmp = psIAsc[iCnt+1];

		if(Chtmp >= 'A') {
			Chtmp = Chtmp - 'A' + 0x0A;
		} else {
			Chtmp &= 0x0F;
		}

		ChBcd |= Chtmp; // 获取BCD低位
		psOBcd[iCnt/2] = ChBcd;
	}
}

*/
void np_Str_To_Hex(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
    char h1,h2;
    unsigned char s1,s2;
    int i,j = 0;
	
	if(!pbDest || !pbSrc){
		return ;
	}

	//np_lower((char *)pbSrc);
	np_upper((char *)pbSrc);
	//app_debug("pbSrc=%s\n",pbSrc);
	//np_asc2bcd((char*)pbSrc,nLen,pbDest);

	/*
	if(nLen%2){
		nLen += 1;
		tmp = pbSrc[0] - 0x30;
        if (tmp > 9)
            tmp -= 7;
		pbDest[j] = tmp;
		j++;
	}*/

    for (i=j; i<nLen; i++)
    {
        h1 = pbSrc[2*i];
        h2 = pbSrc[2*i+1];

        s1 = h1 - 0x30;
        if (s1 > 9)
            s1 -= 7;

        s2 = h2 - 0x30;
        if (s2 > 9)
            s2 -= 7;

        //pbDest[i] = s1*16 + s2;
        pbDest[i] = (s1<<4) + s2;
    }
	
}


int get_datastream_from_file(const char *audio_fullpath,char **dstaudio_data,uint8_t encry_flag)
{
	int fp = 0;

	int ret = 0,read_data = 0,tatol_size = 0;

	
	if(audio_fullpath ==NULL || app_file_exists(audio_fullpath) != 0 ){
		logger_debug("fullpath =%s file not exit\n",audio_fullpath);
		goto exit;
	}

	tatol_size = app_file_size(audio_fullpath);
	if(tatol_size <= 0){
		goto exit;
	}

	fp = app_file_open(audio_fullpath, O_RDONLY | O_CREAT);
	if (fp <=0) {
		goto exit;
	}

	//app_debug("tatol_size = %d\n",tatol_size);
	*dstaudio_data = malloc(tatol_size);
	if(*dstaudio_data == NULL){
		goto exit;	
	}
	memset(*dstaudio_data,0,tatol_size);

	do{
		//sys_msleep(1);	
		read_data = app_file_read(fp,(void *)(*dstaudio_data + ret), MIN(ONE_RDWR_LEN,tatol_size-ret));
		if(read_data > 0){
			ret += read_data;
		}
	}while(ret < tatol_size && read_data > 0);

	
exit:
	if(fp > 0){
		app_file_close(fp);
	}
	//app_debug("ret = %d\n",ret);

	return ret;	

}

//保存内存数据到文件中 encry_flag->是否追加保存
int write_datastream_to_file(const char *audio_fullpath,uint8_t *dstaudio_data,uint32_t datalen,uint8_t append_flag)
{
	int fp = 0;

	int ret = 0,read_data = 0,tatol_size = datalen;

	if(!dstaudio_data || !audio_fullpath ){
		logger_debug("fullpath =%s file not exit\n",audio_fullpath);
		goto exit;
	}
	logger_debug("append_flag = %d,datalen=%d\n",append_flag,datalen);
	fp = app_file_open(audio_fullpath, O_WRONLY | O_CREAT);
	
	if (fp <=0) {
		logger_debug("fp = %X\n",fp);
		goto exit;
	}
	if(append_flag){		
	    app_file_seek(fp, 0, SEEK_END);
	}else{
		app_file_seek(fp, 0, SEEK_SET);
	}
	do{
		//sys_msleep(1);	
		read_data = app_file_write(fp,(void *)(dstaudio_data + ret), MIN(ONE_RDWR_LEN,tatol_size-ret));
		if(read_data > 0){
			ret += read_data;
		}
		logger_debug("read_data=%d\n",read_data);

	}while(ret < tatol_size && read_data > 0);
	
exit:
	if(fp > 0){
		app_file_close(fp);
	}
	logger_debug("ret = %d\n",ret);

	return ret;	


}



uint32_t np_hex2long(uint8_t *psHex, int iHexLen)
{
	int i = 0;
	unsigned long ulTmp = 0;

	for(i = 0; i < iHexLen; i++){
		ulTmp = ulTmp<<8;
		ulTmp += psHex[i];
	}


	return ulTmp;
}



/**
* @brief        时间戳转化为日期
* @param        [in] timep 秒 date 日期值 CN_flag 是否转成北京时间
* @retval       =0 成功
* @retval       非0 失败，以及失败原因
*/
uint32_t fml_stamp_to_time( uint32_t timep, date_time_t *date,uint8_t CN_flag)
{
	
    uint32_t days = 0;
    uint32_t rem = 0;
    uint16_t year;
	uint16_t month;
	uint16_t leap;
	uint16_t ydays;
	uint16_t mdays;
	static const uint16_t days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
    /* 转换时区 */
	if(CN_flag > 0){
		timep = timep + 8*60*60;
	}
    
    // 计算天数
    days = (uint32_t)(timep / 86400);
    rem = (uint32_t)(timep % 86400);
 
 
    // 计算年份
  
    for (year = 1970; ; ++year)
    {
        leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
        ydays = leap ? 366 : 365;
        if (days < ydays)
        {
            break;
        }
        days -= ydays;
    }
    date->year  =  year;
 
 
    // 计算月份
     
    for (month = 0; month < 12; month++)
    {
        mdays = days_in_month[month];
        if(month == 1 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)))
        {
            mdays = 29;
        }
        if (days < mdays)
        {
            break;
        }
        days -= mdays;
    }
    date->month = month;
    date->month += 1;
 
    // 计算日期
    date->day = days + 1;
 
    // 计算时间
    date->hour = rem / 3600;
    rem %= 3600;
    date->min = rem / 60;
    date->sec = rem % 60;
 
    return 0;
}



int deal_url(char *url,char*path,char*host,int *port,int dns_with_port_flag)
{
	int ret = -1;
	char *p = NULL,*q = NULL;
	
	if(url == NULL ){
		goto exit;
	}
	
	logger_debug("deal_host\n");
	p = strstr(url,"//");
	if(p == NULL) {
		goto exit;
	}
	p +=2;
	q=strstr(p,"/");
	if(q == NULL) {
		goto exit;
	}
	logger_debug("p=%s,q=%s\n",p,q);
	if(host != NULL ){
		logger_debug("host=%p\n",&host);
		memcpy(host,p,q - p);
		logger_debug("memcpy size:%d\n",q - p);
		p = strstr(host,":");
		q = p;
		if(port && p){
			p+=1;
			*port = atoi(p);	
			logger_debug("*port =%d\n",*port);
			
		}
		//host不带端口
		if(dns_with_port_flag == 0 && q){
			*q = 0;	
		}
		
	}
	if(path != NULL){
		memcpy(path,q,strlen(q));
	}
	
	ret = 0;
exit:

	return ret;

}


int get_voice_version(char *srcVersion,char *databuf)
{
	char strtmpbuf[50] = {0};
	proto_Items *dataItems[10];
	int itemsNum,i = 0;

	GetTtsStrAudioAmt(srcVersion,strtmpbuf,NULL);	 	
	logger_debug("strtmpbuf=%s\n",strtmpbuf);
	itemsNum = strSplit(strtmpbuf, strlen(strtmpbuf),'.',dataItems,10);
	strcat(databuf,"version");	
	for(i = 0;i < itemsNum;i++){
		strcat(databuf,Audio_REGEX);
		if(dataItems[i]->itemLen > 1 && dataItems[i]->items_value[0] == '0'){
			strcat(databuf,&dataItems[i]->items_value[1]);						
		}else{
			strcat(databuf,dataItems[i]->items_value);			
		}
	}
	free_SplitSpace(dataItems,itemsNum);
	logger_debug("databuf=%s\n",databuf);	
	return 0;
}


int file_copy_to_newpath(char* srcpath,char* dstpath)
{
	int ret = -1,tatol_size = 0,read_data = 0,write_data = 0;
	int fps = 0,fpd = 0;
	char *dstaudio_data=NULL;	

	if(srcpath == NULL || dstpath == NULL){
		goto exit;
	}
	tatol_size = app_file_size(srcpath);
	fps = app_file_open(srcpath,O_RDONLY);		
	logger_debug("srcpath %s ret=%x,dstpath=%s\n",srcpath,fps,dstpath);
	if (fps <=0) {
		goto exit;
	}
	
	fpd = app_file_open(dstpath,  O_RDWR | O_CREAT);	
	logger_debug("ret=%x,dstpath=%s,tatol_size=%d\n",fpd,dstpath,tatol_size);
	if (fpd <=0) {
		goto exit;
	}
	app_file_ftruncate(fpd,0);

	if(tatol_size <= 0){
		goto exit;
	}
	
	dstaudio_data = malloc(ONE_RDWR_LEN);
	if(dstaudio_data == NULL){
		goto exit;	
	}	
	memset(dstaudio_data,0,ONE_RDWR_LEN);
		
	do{
		read_data = app_file_read(fps,(void *)dstaudio_data, MIN(ONE_RDWR_LEN,tatol_size));
		write_data = app_file_write(fpd,(void *)dstaudio_data,read_data);
		if(write_data > 0 ){		
			tatol_size -= write_data;	
		}
		logger_debug("read_data=%d,write_data=%d,tatol_size=%d\n",read_data,write_data,tatol_size);
		
	}while(tatol_size > 0 && read_data > 0);
	
	ret = 0;
exit:

	if(fps > 0){
		app_file_close(fps);
	}
	
	if(fpd > 0){
		app_file_close(fpd);
	}

	if(dstaudio_data){
		free(dstaudio_data);	
	}

	logger_debug("ret = %d\n",ret);

	return ret;		
}


void get_yyyy_MM_dd_HH_mm_ss_ms_time_ex(char *indata,int size,char*date_str,int data_size)
{
	char time_str[8] = {0};
  
    sys_get_time((uint8_t *)time_str,sizeof(time_str));

    if(indata){
  	    snprintf(indata, size, "%04d-%02d-%02d %02d:%02d:%02d",time_str[0]+2000,time_str[1],time_str[2],time_str[3],time_str[4],time_str[5]);
		
		logger_debug("indata=%s\n",indata);
	}
  
    if(date_str){
	    //snprintf(date_str, data_size, "%02d:%02d:%02d",date.hour,date.min,date.sec);
	    snprintf(date_str, data_size, "%02d:%02d:%02d",time_str[3],time_str[4],time_str[5]);
    }
  
  
}


