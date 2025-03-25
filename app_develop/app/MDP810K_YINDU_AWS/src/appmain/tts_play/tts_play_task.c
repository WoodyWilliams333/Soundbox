#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "audio.h"
#include "fixaudio.h"
#include "tts_play.h"

#include "audiomap.h"
#include "codestool.h"
#include "fixaudioen.h"
#include "syspara.h"
#include "logger.h"
#include "appfile.h"

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif 

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif 


//印度读数规则处理
static void setaudioNum_Hindi(int amt_flag,char *str,int iLen,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0},p4[2]={0},p5[2]={0};
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);
	memcpy(p4,str+3,1);
	memcpy(p5,str+4,1);
	//app_debug("str=%s,iLen=%d\n",str,iLen);
	
	if(iLen >= 5){// 02345  12345

		if(strcmp(p1,"0") == 0 && strcmp(p2,"0") != 0 ){//02
			strcpy(dststr[*offste],p2);
			*offste+=1;

		}else if(strcmp(p1,"0") != 0 ){//12
			strcpy(dststr[*offste],p1);			
			strcat(dststr[*offste],p2);
			*offste+=1;
		}

		if(strcmp(p1,"0") != 0 || strcmp(p2,"0") != 0){
			if(amt_flag == TYPE_AMOUNT_EN){
				strcpy(dststr[*offste],AudioNumEnQian);//千
			}else if(amt_flag == TYPE_AMOUNT_HINDI){
				strcpy(dststr[*offste],AudioNumHindiQian);//千
			}
			*offste+=1;
		}

		if(strcmp(p3,"0") != 0 ){
			strcpy(dststr[*offste],p3);
			*offste+=1;
			if(amt_flag == TYPE_AMOUNT_EN){
				strcpy(dststr[*offste],AudioNumEnBai);//百
			}else if(amt_flag == TYPE_AMOUNT_HINDI){
				strcpy(dststr[*offste],AudioNumHindiBai);//百
			}
			*offste+=1;
		}

		if(strcmp(p4,"0") != 0 ){
			strcpy(dststr[*offste],p4);
			strcat(dststr[*offste],p5);
			*offste+=1;
		}else{
			if(strcmp(p5,"0") != 0){
				strcpy(dststr[*offste],p5);
				*offste+=1;
			}
		}

	}else if(iLen >= 4){//1234 0234

			if(strcmp(p1,"0") != 0 ){
				strcpy(dststr[*offste],p1);			
				*offste+=1;
				if(amt_flag == TYPE_AMOUNT_EN){
					strcpy(dststr[*offste],AudioNumEnQian);//千
				}else if(amt_flag == TYPE_AMOUNT_HINDI){
					strcpy(dststr[*offste],AudioNumHindiQian);//千
				}
				*offste+=1;
			}

			if(strcmp(p2,"0") != 0 ){
				strcpy(dststr[*offste],p2);
				*offste+=1;

				if(amt_flag == TYPE_AMOUNT_EN){
					strcpy(dststr[*offste],AudioNumEnBai);//百
				}else if(amt_flag == TYPE_AMOUNT_HINDI){
					strcpy(dststr[*offste],AudioNumHindiBai);//百
				}
				*offste+=1;
			}
			
			if(strcmp(p3,"0") != 0 ){
				strcpy(dststr[*offste],p3);
				strcat(dststr[*offste],p4);
				*offste+=1;
			}else{
				if(strcmp(p4,"0") != 0){
					strcpy(dststr[*offste],p4);
					*offste+=1;
				}
			}
	
	}else if(iLen >= 3){

		if(strcmp(p1,"0") != 0 ){
			strcpy(dststr[*offste],p1);
			*offste+=1;

			if(amt_flag == TYPE_AMOUNT_EN){
				strcpy(dststr[*offste],AudioNumEnBai);//百
			}else if(amt_flag == TYPE_AMOUNT_HINDI){
				strcpy(dststr[*offste],AudioNumHindiBai);//百
			}else{
				strcpy(dststr[*offste],AudioNumEnBai);//百
			}
			*offste+=1;
		}

		if(strcmp(p2,"0") != 0 ){
			strcpy(dststr[*offste],p2);
			strcat(dststr[*offste],p3);
			*offste+=1;
		}else{
			if(strcmp(p3,"0") != 0){
				strcpy(dststr[*offste],p3);
				*offste+=1;
			}
		}

	}else if(iLen >= 2){// 12		
		if(strcmp(p1,"0") != 0 ){
			strcpy(dststr[*offste],p1);
			strcat(dststr[*offste],p2);
			*offste+=1;
		}else{
			if(strcmp(p2,"0") != 0){
				strcpy(dststr[*offste],p2);
				*offste+=1;
			}
		}
	}
	else{
		strcpy(dststr[*offste],p1);
		*offste+=1;
	}
	
}


static void set_Tmail_2len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0};

	memcpy(p1,str,1);
	memcpy(p2,str+1,1);

	if(strcmp(p1,"0") != 0 ){
		strcpy(dststr[*offste],p1);
		strcat(dststr[*offste],p2);
		*offste+=1;
	}else{
		if(strcmp(p2,"0") != 0){
			strcpy(dststr[*offste],p2);
			*offste+=1;
		}
	}	
}

static void set_Tmail_3len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0};
	char *amt_ptr = NULL;
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);

	if(strcmp(p1,"0") != 0 && (strcmp(p2,"0") == 0  && strcmp(p3,"0") == 0 ) ){
		strcpy(dststr[*offste],p1);
		*offste+=1;
		
		strcpy(dststr[*offste],(char*)AudioNumEnBai);//百
		*offste+=1;
	}else{
		
		amt_ptr = get_Tmail_amount_playfile(p1,(char*)AudioNumEnBai);
		if(amt_ptr != NULL){
			strcpy(dststr[*offste],amt_ptr);
			*offste+=1;
		}
		
		amt_ptr = str +1;
		set_Tmail_2len_amount(amt_ptr,dststr,offste);
	}
	
}


static void set_Tmail_4len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0},p4[2]={0};
	char *amt_ptr = NULL;
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);
	memcpy(p4,str+3,1);
	if(strcmp(p1,"0") != 0 && (strcmp(p2,"0") == 0  && strcmp(p3,"0") == 0 && strcmp(p4,"0") == 0 ) ){
		strcpy(dststr[*offste],p1);
		*offste+=1;
	
		strcpy(dststr[*offste],(char*)AudioNumEnQian);//千
		*offste+=1;
	}else{
		
		if(strcmp(p1,"1") != 0){
			strcpy(dststr[*offste],p1);
			*offste+=1;	
		}
		
		strcpy(dststr[*offste],(char*)Audiohindilangt1);//千
		*offste+=1;

		amt_ptr = str +1;
		set_Tmail_3len_amount(amt_ptr,dststr,offste);
	}
}

static void set_Tmail_5len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0},p4[2]={0},p5[2]={0};
	char *amt_ptr = NULL;
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);
	memcpy(p4,str+3,1);
	memcpy(p5,str+4,1);
	if(strcmp(p1,"0") != 0 && (strcmp(p2,"0") == 0  && strcmp(p3,"0") == 0 
		&& strcmp(p4,"0") == 0 && strcmp(p5,"0") == 0)){

		strcpy(dststr[*offste],p1);
		strcat(dststr[*offste],"0");	
		*offste+=1;
		
		strcpy(dststr[*offste],(char*)AudioNumEnQian);
		*offste+=1;
	}else{

		if(strcmp(p1,"0") == 0 && strcmp(p2,"0") != 0 ){
			strcpy(dststr[*offste],p2);
			*offste+=1;
			
			strcpy(dststr[*offste],(char*)Audiohindilangt1);
			*offste+=1;
			
		}else if(strcmp(p1,"0") != 0){
			strcpy(dststr[*offste],p1);
			strcat(dststr[*offste],p2);
			*offste+=1;
			
			strcpy(dststr[*offste],(char*)Audiohindilangt1);
			*offste+=1;	
		}
				
		amt_ptr = str +2;
		set_Tmail_3len_amount(amt_ptr,dststr,offste);
	}
}


static void set_Tmail_6len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0},p4[2]={0},p5[2]={0},p6[2]={0};
	char *amt_ptr = NULL;
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);
	memcpy(p4,str+3,1);
	memcpy(p5,str+4,1);
	memcpy(p6,str+5,1);
	if(strcmp(p1,"0") != 0 && (strcmp(p2,"0") == 0  && strcmp(p3,"0") == 0 
		&& strcmp(p4,"0") == 0 && strcmp(p5,"0") == 0 && strcmp(p6,"0") == 0)){

		strcpy(dststr[*offste],p1);
		*offste+=1;
		
		strcpy(dststr[*offste],(char*)AudioNumEnShiwan);
		*offste+=1;
	}else{
		strcpy(dststr[*offste],p1);
		*offste+=1;
		
		strcpy(dststr[*offste],(char*)Audiohindilangl1);
		*offste+=1;
		
		amt_ptr = str +1;
		set_Tmail_5len_amount(amt_ptr,dststr,offste);
	}
}


static void set_Tmail_7len_amount(char *str,char dststr[][50],int *offste)
{
	char p1[2] ={0},p2[2]={0},p3[2]={0},p4[2]={0},p5[2]={0},p6[2]={0},p7[2]={0};
	char *amt_ptr = NULL;
	//char set0_flag = 0;
	// 12345 = 12 thousand 4 hundred 45
	memcpy(p1,str,1);
	memcpy(p2,str+1,1);
	memcpy(p3,str+2,1);
	memcpy(p4,str+3,1);
	memcpy(p5,str+4,1);
	memcpy(p6,str+5,1);
	memcpy(p7,str+6,1);
	
	if(strcmp(p1,"0") != 0 && (strcmp(p3,"0") == 0 
		&& strcmp(p4,"0") == 0 && strcmp(p5,"0") == 0 && strcmp(p6,"0") == 0 && strcmp(p7,"0") == 0)){
		
		strcpy(dststr[*offste],p1);
		strcat(dststr[*offste],p2);
		*offste+=1;
		
		strcpy(dststr[*offste],(char*)AudioNumEnShiwan);
		*offste+=1;
	}else{
		if(strcmp(p1,"0") != 0){
			strcpy(dststr[*offste],p1);
			strcat(dststr[*offste],p2);
			*offste+=1;
			strcpy(dststr[*offste],(char*)Audiohindilangl1);
			*offste+=1;
		}else if(strcmp(p1,"0") == 0 && strcmp(p2,"0") != 0){

			strcpy(dststr[*offste],p2);
			*offste+=1;
			strcpy(dststr[*offste],(char*)Audiohindilangl1);
			*offste+=1;
		}

	}
	amt_ptr = str +2;
	set_Tmail_5len_amount(amt_ptr,dststr,offste);
	
}



//印度tmail语种读数规则处理
static void setaudioNum_Tmail(char *str,int iLen,char dststr[][50],int *offste)
{
	char p1[2] ={0};
	memcpy(p1,str,1);

	if(iLen >= 7){
		set_Tmail_7len_amount(str,dststr,offste);	
	}else if(iLen >= 6){
		set_Tmail_6len_amount(str,dststr,offste);
	}else if(iLen >= 5){// 02345  12345
		set_Tmail_5len_amount(str,dststr,offste);
	}else if(iLen >= 4){//1234 0234
		set_Tmail_4len_amount(str,dststr,offste);	
	}else if(iLen >= 3){
		set_Tmail_3len_amount(str,dststr,offste);
	}else if(iLen >= 2){// 12		
		set_Tmail_2len_amount(str,dststr,offste);
	}
	else{
		strcpy(dststr[*offste],p1);
		*offste+=1;
	}
}


int play_pack_audiofile(char*filepath,const char* buf)
{
	
	char file_full_path[200] = "";
	char fileName[100] = {0};
	int iret;
	
	logger_debug("buf =%s \n",buf);
	getaudioplayfilename((char*)buf,fileName);
	if(strlen(fileName) <= 0){
		snprintf(fileName,sizeof(fileName),"%s",buf);
	}
	snprintf(file_full_path,sizeof(file_full_path),"%s/%s",filepath,fileName);
	if(strstr(file_full_path,".mp3") == NULL){
		strcat(file_full_path,".mp3"); 
	}	
	logger_debug("file_full_path =%s \n",file_full_path);
	iret = play_mp3_file(file_full_path);
	
	logger_debug("iret =%x\n",iret);


	return iret;
}

int jug_audiofile_exit(const char* filename)
{
	char file_full_path[200] = {0};
	int ret = 0;
	snprintf(file_full_path,sizeof(file_full_path),MP3_FILE_PATH"%s%s",filename,".mp3");
	if(0 == app_file_exists(file_full_path)){
		ret = 1;
	}
	return ret;
}

#define HINDI_TMAIL_AMOUNT_SUB  7

static int setAmountAudio_tmail(char *amountStr)
{
	int iLen,ioffset = 0,i;
	char *tts_ptr = NULL,tts_buf[100] = {0},detStr[150] = {0},tmpStr[100] = {0};
	char audip_play_vector[30][50];
	tts_ptr=amountStr;

	logger_debug("amountStr=%s\n",amountStr);
	while(*tts_ptr)
	{
		char tmp;
		tmp=*tts_ptr++;
		if (((tmp<'0')||(tmp>'9'))&&(tmp!='.')) return 0;
	}

	tts_ptr = strstr(amountStr,".");

	//获取数字部分
	if(tts_ptr !=NULL){
		strncpy(detStr,amountStr,tts_ptr -amountStr);
	}else{
		strcpy(detStr,amountStr);
	}
	
	//获取小数部分
	if(tts_ptr != NULL){
		memmove(tts_buf,tts_ptr,strlen(amountStr) - (tts_ptr - amountStr));
	}
	
	logger_debug("tts_buf =%s,detStr=%s\n",tts_buf,detStr);

	iLen = strlen(detStr);
	memset(audip_play_vector,0,sizeof(audip_play_vector));

	/*
		detStr 数字部分
		tts_buf 小数部分
	*/

	do{

		//1 00 0000
		if(iLen > HINDI_TMAIL_AMOUNT_SUB){
			memset(tmpStr,0,sizeof(tmpStr));
			strncpy(tmpStr,&detStr[MAX(iLen- HINDI_TMAIL_AMOUNT_SUB,0)],MAX(HINDI_TMAIL_AMOUNT_SUB,iLen - HINDI_TMAIL_AMOUNT_SUB));
			logger_debug("tmpStr=%s\n",tmpStr);
			if(atoi(tmpStr) > 0){
				setaudioNum_Tmail(tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);

				strcpy(audip_play_vector[ioffset],(char*)AudioNumEnQianwan);//千万
				ioffset += 1;
			}
		}	
	
		//<= 6 10 000	
		memset(tmpStr,0,sizeof(tmpStr));
		strncpy(tmpStr,&detStr[MAX(iLen- HINDI_TMAIL_AMOUNT_SUB,0)],MIN(HINDI_TMAIL_AMOUNT_SUB,iLen));
		logger_debug("tmpStr=%s\n",tmpStr);
		if(atoi(detStr) == 0 && ioffset == 0){//判断多个0的非正常数据，比如00000.01
			strcpy(audip_play_vector[ioffset],"0");
			ioffset+=1;
		}else{
			setaudioNum_Tmail(tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
		}

		strcpy(audip_play_vector[ioffset],(char*)AudioNumEnLubi);
		ioffset += 1;
		
		//添加小数点读数
		if(atoi(&tts_buf[1]) > 0){
			if(tts_buf[1] != '0'){//判断多个0的非正常数据，比如.00
				setaudioNum_Tmail(&tts_buf[1],strlen(&tts_buf[1]),audip_play_vector,&ioffset);
			}else{
				setaudioNum_Tmail(&tts_buf[2],strlen(&tts_buf[2]),audip_play_vector,&ioffset);
			}
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnFen);//paise
			ioffset += 1;
		}

		//your
		strcpy(audip_play_vector[ioffset],(char*)AudioNumEnyour);
		ioffset += 1;
		
		if(strlen(Get_SysPara()->mer_name) > 0 && jug_audiofile_exit(Get_SysPara()->mer_name)){				
			//bank
			strcpy(audip_play_vector[ioffset],Get_SysPara()->mer_name);
			ioffset += 1;
		}

		//account
		strcpy(audip_play_vector[ioffset],(char*)AudioNumEnaccount);
		ioffset += 1;

		//Received
		strcpy(audip_play_vector[ioffset],(char*)AudioNumEnreceived);
		ioffset += 1;
		
	}while(0);


	for(i=0;i<ioffset;i++){
		logger_debug("audip_play_vector[%d] = %s,ioffset=%d\n",i,audip_play_vector[i],ioffset);
		play_pack_audiofile((char*)MP3_FILE_PATH,audip_play_vector[i]);
	}	

	return 0;


}




static int setAmountAudio_ex_en(char *amountStr,int amt_flag)
{
	int iLen,ioffset = 0,i;
	char *tts_ptr = NULL,tts_buf[200] = {0},detStr[150] = {0},tmpStr[100] = {0};
	char audip_play_vector[30][50];
	//char mogo_buf[65] = {0};

	tts_ptr=amountStr;

	logger_debug("amountStr=%s\n",amountStr);
	while(*tts_ptr)
	{
		char tmp;
		tmp=*tts_ptr++;
		if (((tmp<'0')||(tmp>'9'))&&(tmp!='.')) return 0;
	}

	tts_ptr = strstr(amountStr,".");

	//获取数字部分
	if(tts_ptr !=NULL){
		strncpy(detStr,amountStr,tts_ptr -amountStr);
	}else{
		strcpy(detStr,amountStr);
	}
	
	//获取小数部分
	if(tts_ptr != NULL){
		memmove(tts_buf,tts_ptr,strlen(amountStr) - (tts_ptr - amountStr));
	}
	
	logger_debug("tts_buf =%s,detStr=%s\n",tts_buf,detStr);

	iLen = strlen(detStr);
	memset(audip_play_vector,0,sizeof(audip_play_vector));

	/*
		detStr 数字部分
		tts_buf 小数部分
	*/

	do{
		//mogo 播报前奏音
		if(amt_flag != TYPE_NUMBER){
			//strcat(mogo_buf,(char*)AudioHindimogo);
			if(jug_audiofile_exit((char*)AudioHindimogo)){				
				//mogo_buf
				strcpy(audip_play_vector[ioffset],(char*)AudioHindimogo);
				ioffset += 1;
			}
		}

		//1 00 00 0000
		if(iLen > 7){
			memset(tmpStr,0,sizeof(tmpStr));
			strncpy(tmpStr,&detStr[MAX(iLen- 9,0)],MAX(0,iLen - 7));
			logger_debug("tmpStr=%s\n",tmpStr);
			if(atoi(tmpStr) > 0){//判断多个0的非正常数据，比如00000.01
				setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);

				strcpy(audip_play_vector[ioffset],(char*)AudioNumEnQianwan);//千万
				ioffset += 1;
			}
		}	
	

		//10 00 000
		if(iLen > 5){
			memset(tmpStr,0,sizeof(tmpStr));
			strncpy(tmpStr,&detStr[MAX(iLen- 7,0)],MIN(2,iLen - 5));
			logger_debug("tmpStr=%s\n",tmpStr);
			if(atoi(tmpStr) > 0){//判断多个0的非正常数据，比如00000.01
				setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
				strcpy(audip_play_vector[ioffset],(char*)AudioNumEnShiwan);//十万
				ioffset += 1;
			}
		}

		//<= 5 10 000	
		memset(tmpStr,0,sizeof(tmpStr));
		strncpy(tmpStr,&detStr[MAX(iLen- 5,0)],MIN(5,iLen));
		logger_debug("tmpStr=%s\n",tmpStr);
		if(atoi(detStr) == 0){//判断多个0的非正常数据，比如00000.01
			strcpy(audip_play_vector[ioffset],"0");
			ioffset+=1;
		}else{
			setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
		}
		
		//Rupees
		if(amt_flag != TYPE_NUMBER){
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnLubi);
			ioffset += 1;
		}

		//添加小数点读数
		if(atoi(&tts_buf[1]) > 0){
			if(tts_buf[1] != '0'){//判断多个0的非正常数据，比如.00
				setaudioNum_Hindi(amt_flag,&tts_buf[1],strlen(&tts_buf[1]),audip_play_vector,&ioffset);
			}else{
				setaudioNum_Hindi(amt_flag,&tts_buf[2],strlen(&tts_buf[2]),audip_play_vector,&ioffset);
			}
			if(amt_flag != TYPE_NUMBER){
				strcpy(audip_play_vector[ioffset],(char*)AudioNumEnFen);//paise
				ioffset += 1;
			}
		}

		if(amt_flag == TYPE_AMOUNT_EN){//has been credited to your <kotak bank> account 
			//hbcty
			strcpy(audip_play_vector[ioffset],(char*)AudioNumhbcty);
			ioffset += 1;
	
			if(strlen(Get_SysPara()->mer_name) > 0 && jug_audiofile_exit(Get_SysPara()->mer_name)){				
				//bank
				strcpy(audip_play_vector[ioffset],Get_SysPara()->mer_name);
				ioffset += 1;
			}

			//account
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnaccount);
			ioffset += 1;

		}else if(amt_flag == TYPE_AMOUNT_HINDI){//aapke <kotak bank> khate mein prapt hue 
			//your
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnyour);
			ioffset += 1;
			
			if(strlen(Get_SysPara()->mer_name) > 0 && jug_audiofile_exit(Get_SysPara()->mer_name)){				
				//bank
				strcpy(audip_play_vector[ioffset],Get_SysPara()->mer_name);
				ioffset += 1;
			}

			//account
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnaccount);
			ioffset += 1;

			//Received
			strcpy(audip_play_vector[ioffset],(char*)AudioNumEnreceived);
			ioffset += 1;
		}
			
	}while(0);

	for(i=0;i<ioffset;i++){
		logger_debug("audip_play_vector[%d] = %s,ioffset=%d\n",i,audip_play_vector[i],ioffset);
		play_pack_audiofile((char*)MP3_FILE_PATH,audip_play_vector[i]);
	}	

	return 0;


}


int setAmountAudio_ex_hindi(char *amountStr,int amt_flag)
{
	int iLen,ioffset = 0,i;
	char *tts_ptr = NULL,tts_buf[200] = {0},detStr[150] = {0},tmpStr[100] = {0};
	char audip_play_vector[30][50];

	tts_ptr=amountStr;

	logger_debug("amountStr=%s\n",amountStr);
	while(*tts_ptr)
	{
		char tmp;
		tmp=*tts_ptr++;
		if (((tmp<'0')||(tmp>'9'))&&(tmp!='.')) return 0;
	}

	tts_ptr = strstr(amountStr,".");

	//获取数字部分
	if(tts_ptr !=NULL){
		strncpy(detStr,amountStr,tts_ptr -amountStr);
	}else{
		strcpy(detStr,amountStr);
	}
	
	//获取小数部分
	if(tts_ptr != NULL){
		memmove(tts_buf,tts_ptr,strlen(amountStr) - (tts_ptr - amountStr));
	}
	
	logger_debug("tts_buf =%s,detStr=%s\n",tts_buf,detStr);

	iLen = strlen(detStr);
	memset(audip_play_vector,0,sizeof(audip_play_vector));

	/*
		detStr 数字部分
		tts_buf 小数部分
	*/

	do{
		
		//1 00 00 0000
		if(iLen > 7){
			memset(tmpStr,0,sizeof(tmpStr));
			strncpy(tmpStr,&detStr[MAX(iLen- 7,0)],MAX(0,iLen - 7));
			logger_debug("tmpStr=%s\n",tmpStr);
			if(atoi(tmpStr) > 0){//判断多个0的非正常数据，比如00000.01
				setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
				if(amt_flag == TYPE_AMOUNT_EN ){
					strcpy(audip_play_vector[ioffset],(char*)AudioNumEnQianwan);//千万
					ioffset += 1;
				}else if(amt_flag == TYPE_AMOUNT_HINDI){
					strcpy(audip_play_vector[ioffset],(char*)AudioNumHindiQianwan);//千thousand
					ioffset += 1;
				}
			}
		}	
	

		//10 00 000
		if(iLen > 5){
			memset(tmpStr,0,sizeof(tmpStr));
			strncpy(tmpStr,&detStr[MAX(iLen- 7,0)],MIN(2,iLen - 5));
			logger_debug("tmpStr=%s\n",tmpStr);
			if(atoi(tmpStr) > 0){//判断多个0的非正常数据，比如00000.01
				setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
				if(amt_flag == TYPE_AMOUNT_EN ){
					strcpy(audip_play_vector[ioffset],(char*)AudioNumEnShiwan);//十万
					ioffset += 1;
				}else if(amt_flag == TYPE_AMOUNT_HINDI){
					strcpy(audip_play_vector[ioffset],(char*)AudioNumHindiShiwan);
					ioffset += 1;
				}
			}
		}

		//<= 5 10 000	
		memset(tmpStr,0,sizeof(tmpStr));
		strncpy(tmpStr,&detStr[MAX(iLen- 5,0)],MIN(5,iLen));
		logger_debug("tmpStr=%s\n",tmpStr);
		if(atoi(detStr) == 0){//判断多个0的非正常数据，比如00000.01
			strcpy(audip_play_vector[ioffset],"0");
			ioffset+=1;
		}else{
			setaudioNum_Hindi(amt_flag,tmpStr,strlen(tmpStr),audip_play_vector,&ioffset);
		}
		
		//添加小数点读数
		if(atoi(&tts_buf[1]) > 0){
			if(tts_buf[1] != '0'){//判断多个0的非正常数据，比如.00
				setaudioNum_Hindi(amt_flag,&tts_buf[1],strlen(&tts_buf[1]),audip_play_vector,&ioffset);
			}else{
				setaudioNum_Hindi(amt_flag,&tts_buf[2],strlen(&tts_buf[2]),audip_play_vector,&ioffset);
			}
		}

		
	}while(0);

		for(i=0;i<ioffset;i++){
			logger_debug("audip_play_vector[%d] = %s,ioffset=%d\n",i,audip_play_vector[i],ioffset);
			play_pack_audiofile((char*)MP3_FILE_PATH,audip_play_vector[i]);
		}	

	return 0;


}

int setAmountAudio_ex(char *amountStr,int amt_flag)
{

	if(amt_flag == TYPE_AMOUNT_TMAIL){//单独处理tmail语言
		return setAmountAudio_tmail(amountStr);
	}else{
		//数字-英文-印度语
		return setAmountAudio_ex_en(amountStr,amt_flag);
	}
	

}

int playCountEn(int inum)
{
	char fileName[50] = {0};
	logger_debug("playCountEn \n");
	
	//英文播放第几笔和中文不同处理
	switch(inum){
		case 1:
			strcpy(fileName,(char*)Audiodiyibi);
			//tts_led_play_text(Audiodiyibi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 2:
			strcpy(fileName,(char*)Audiodi2bi);
			//tts_led_play_text(Audiodierbi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 3:
			strcpy(fileName,(char*)Audiodi3bi);
			//tts_led_play_text(Audiodisanbi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 4:
			strcpy(fileName,(char*)Audiodi4bi);
			//tts_led_play_text(Audiodisibi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 5:
			strcpy(fileName,(char*)Audiodi5bi);
			//tts_led_play_text(Audiodiwubi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 6:
			strcpy(fileName,(char*)Audiodi6bi);
			//tts_led_play_text(Audiodiliubi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 7:
			strcpy(fileName,(char*)Audiodi7bi);
			//tts_led_play_text(Audiodiqibi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 8:
			strcpy(fileName,(char*)Audiodi8bi);
			//tts_led_play_text(Audiodibabi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 9:
			strcpy(fileName,(char*)Audiodi9bi);
			//tts_led_play_text(Audiodijiubi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		case 10:
			strcpy(fileName,(char*)Audiodi10bi);
			//tts_led_play_text(Audiodishibi,MP3_WAV_FILE_TEXT,NULL,NULL);
			break;
		default:
			return 1;
	}
	
	play_pack_audiofile((char*)MP3_FILE_PATH,fileName);
	return 0;
}

int playAudioTimeEn(char *TimeStr,char splt_flag)
{

	int itemsNum = 0,i;
	proto_Items *dataItems[50];
	logger_debug("playAudioTimeEn \n");

	itemsNum = strSplit(TimeStr, strlen(TimeStr),splt_flag,dataItems,50);
	
	//英文播放第几笔和中文不同处理
	if(strcmp(dataItems[0]->items_value,"第")==0 && strcmp(dataItems[2]->items_value,"笔")==0){
		if(playCountEn(atoi(dataItems[1]->items_value))== 0)
			return 0;
	}

	for(i=0;i<itemsNum;i++){
		logger_debug("audip_play_vetor[%d] = %s\n",i,dataItems[i]->items_value);
		play_pack_audiofile((char*)MP3_FILE_PATH,dataItems[i]->items_value);
	}		

	free_SplitSpace(dataItems,itemsNum);

	return 0;

}

int playAudioTime(char *TimeStr,char splt_flag)
{

	int itemsNum = 0,i;
	proto_Items *dataItems[50];
	char tempbuf[50] = {0};

	itemsNum = strSplit(TimeStr, strlen(TimeStr),splt_flag,dataItems,50);

	for(i=0;i<itemsNum;i++){
		//app_debug("audip_play_vetor[%d] = %s\n",i,dataItems[i]->items_value);
		getaudioplayfilename(dataItems[i]->items_value,tempbuf);
		play_pack_audiofile((char*)MP3_FILE_PATH,tempbuf);
	}

	free_SplitSpace(dataItems,itemsNum);

	return 0;

}


//播报纯数字 不带百千万元等
int PlayPackAudio_number(TTS_MSG *msgin,int amt_falg)
{

	//int mLen = msgin->Audio.len&(~1);
	char *mp3Name=msgin->Audio.buf;
	char *aMount = msgin->amount; 

	logger_debug("PlayPackAudio_number\n");
	play_pack_audiofile((char*)MP3_FILE_PATH,mp3Name);

	//set Amount
	if(setAmountAudio_ex(aMount,amt_falg)){
		return -1;
	}

	if(strcmp(mp3Name,(char*)AudioDangqiandl)== 0){
		logger_debug(" pack play AudioBaifenzhi=%s\n",AudioBaifenzhi);
	    play_pack_audiofile((char*)MP3_FILE_PATH,(char*)AudioBaifenzhi);
	}
	
	logger_debug(" pack play successful");
	return 0;
}


//时间数字等播报
int PlayPackAudio_number_ex(struct tts_buff_msg * msgin)
{
	//int mLen = msgin->Audio.len&(~1);
	char *mp3Name=msgin->Audio.buf;
	//char *aMount = msgin->amount; 

	//app_debug("PlayPackAudio_number_ex\n");

	//set Amount
	if(playAudioTime(mp3Name,'|')){

		return -1;
	}

	return 0;
}



