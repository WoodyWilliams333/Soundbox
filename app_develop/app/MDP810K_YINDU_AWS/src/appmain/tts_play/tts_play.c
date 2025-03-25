#include "appdef.h"
#include <appaudio.h>
#include "tts_play.h"
#include "fixaudio.h"
#include "syspara.h"
#include "screen.h"
#include "audiomap.h"
#include "tersharedata.h"
#include "appsys.h"
#include "logger.h"
#include "codestool.h"

typedef struct hzfilemap{
	const char *pszHz;	
	const char *pszFileName; //mp3文件名称
    const char *bufName;     //内存对应文件名
	int *audioLen;           //内存对应文件大小
}ST_HZ_FILE_MAP;
#define MP3_ADD_0	 APP_FILE_PATH"/mp3/0.mp3"
#define MP3_ADD_1	 APP_FILE_PATH"/mp3/1.mp3"
#define MP3_ADD_2	 APP_FILE_PATH"/mp3/2.mp3"
#define MP3_ADD_3	 APP_FILE_PATH"/mp3/3.mp3"
#define MP3_ADD_4	 APP_FILE_PATH"/mp3/4.mp3"
#define MP3_ADD_5	 APP_FILE_PATH"/mp3/5.mp3"
#define MP3_ADD_6	 APP_FILE_PATH"/mp3/6.mp3"
#define MP3_ADD_7	 APP_FILE_PATH"/mp3/7.mp3"
#define MP3_ADD_8	 APP_FILE_PATH"/mp3/8.mp3"
#define MP3_ADD_9	 APP_FILE_PATH"/mp3/9.mp3"
#define MP3_ADD_ten  APP_FILE_PATH"/mp3/10.mp3"
#define MP3_ADD_hun	 APP_FILE_PATH"/mp3/hundred.mp3"
#define MP3_ADD_thou APP_FILE_PATH"/mp3/thous.mp3"
#define MP3_ADD_wan	 APP_FILE_PATH"/mp3/wan.mp3"
#define MP3_ADD_yi	 APP_FILE_PATH"/mp3/yi.mp3"
#define MP3_ADD_dian APP_FILE_PATH"/mp3/dian.mp3"
#define MP3_ADD_yuan APP_FILE_PATH"/mp3/yuan.mp3"

const ST_HZ_FILE_MAP gstChineseMap[] = {
	{"一",	MP3_ADD_1,      NULL,    NULL},
	{"零",	MP3_ADD_0,     NULL,    NULL},
	{"二",	MP3_ADD_2,      NULL,    NULL},
	{"三",	MP3_ADD_3,    NULL,    NULL},
	{"四",	MP3_ADD_4,     NULL,    NULL},
	{"五",	MP3_ADD_5,     NULL,    NULL},
	{"六",	MP3_ADD_6,      NULL,    NULL},
	{"七",	MP3_ADD_7,    NULL,    NULL},
	{"八",	MP3_ADD_8,    NULL,    NULL},
	{"九",	MP3_ADD_9,     NULL,    NULL},
	{"十",	MP3_ADD_ten,      NULL,  NULL},
	{"百",	MP3_ADD_hun,  NULL,  NULL},
	{"千",	MP3_ADD_thou, NULL, NULL},
	{"万",	MP3_ADD_wan,      NULL,  NULL},
	{"亿",	MP3_ADD_yi,       NULL,   NULL},
	{"点",	MP3_ADD_dian,    NULL, NULL},
	{"元",	MP3_ADD_yuan,     NULL, NULL},
	{NULL,	NULL, NULL,	NULL},
};
#if 0
int audio_play_stream(int type, char *p[],int flg)
{
	logger_error("-----------++++++-------------\n");
	logger_error("Hardware play voice=%s\n",p[0]);
	logger_error("-----------++++++-------------\n");
	return 0;
}
#endif
static void GetCnNum(int iNum,char *bcStr)
{
	switch(iNum%10){
	case 0:
		strcat(bcStr,"零");
		break;
	case 1:
		strcat(bcStr,"一");
		break;
	case 2:
		strcat(bcStr,"二");
		break;
	case 3:
		strcat(bcStr,"三");
		break;
	case 4:
		strcat(bcStr,"四");
		break;
	case 5:
		strcat(bcStr,"五");
		break;
	case 6:
		strcat(bcStr,"六");
		break;
	case 7:
		strcat(bcStr,"七");
		break;
	case 8:
		strcat(bcStr,"八");
		break;
	case 9:
		strcat(bcStr,"九");
		break;
	default:
		strcat(bcStr,"零");
		break;
	}
}

static void GetThousandBcMsg(int iAmountYuan,char *bcStr)
{
	int iFlag = 0;
	int iTemp = 0;

	//千位
	iTemp = iAmountYuan;
	iTemp = iTemp/1000;
	if(iTemp > 0){
		GetCnNum(iTemp,bcStr);
		strcat(bcStr,"千");
		iFlag = 1;
	}

	//百位
	iTemp = iAmountYuan%1000;
	if(iTemp == 0){
		return;
	}
	iTemp = iTemp/100;
	if(iTemp > 0 || iFlag == 1){
		GetCnNum(iTemp,bcStr);
		if(iTemp != 0){
			strcat(bcStr,"百");
			iFlag = 1;
		}
		else{
			iFlag = 0;
		}
	}

	//十位
	iTemp = iAmountYuan%100;
	if(iTemp == 0){
		return;
	}
	iTemp = iTemp/10;
	if(iTemp > 0 || iFlag == 1){
		//jiangwei add
		if(0 == strlen(bcStr) && 1 == iTemp){
			//10 读作十
		}else{
			GetCnNum(iTemp,bcStr);
		}
		if(iTemp != 0){
			strcat(bcStr,"十");
		}
	}

	//个位
	iTemp = iAmountYuan%10;
	if(iTemp > 0){
		GetCnNum(iTemp,bcStr);
	}
	
}
static void GetBroadCastAmountStr(char *amountYuan, char *amountCent,char *bcStr)
{
	int iAmountYuan = 0,iAmountCent = 0;
	int n1=0, n2=0;
	
	iAmountYuan = atoi(amountYuan);
	iAmountCent = atoi(amountCent);
	n1 = iAmountYuan / 10000;
	n2 = iAmountYuan % 10000;

	if(iAmountYuan == 0 && iAmountCent == 0){
		strcat(bcStr,"零");//如果俩个都是0，就返回零
		return;
	}

	if(iAmountYuan == 0){
		strcat(bcStr,"零");
	}
	else{
		if(n1 > 0){
			GetThousandBcMsg(n1, bcStr);
			strcat(bcStr,"万");
		}

		if(n2 > 0){
			if (n1 > 0 && n2 < 1000){ //千位为零播报零 211018
				strcat(bcStr, "零");
			}
			GetThousandBcMsg(n2, bcStr);
		}
	}

	if(iAmountCent != 0){
		strcat(bcStr,"点");
		GetCnNum(iAmountCent/10, bcStr);
		GetCnNum(iAmountCent%10, bcStr);
	}

	//strcat(bcStr,"元");
}

int play_mp3(const char *filename)
{
    int iRet = -1;
	char szWavPath[150] = {0};
	char *p[2] = {NULL};

    logger_debug("%s\n", __FUNCTION__);  
    if(NULL == filename){
        return iRet;
    }
	snprintf(szWavPath, sizeof(szWavPath), "%s/%s", APP_FILE_PATH,filename);
    logger_debug("szWavPath = %s\n", szWavPath);
	p[0] = szWavPath;
	iRet = audio_play_stream(AUDIO_FORMAT_MP3, p, 1);
	logger_debug("iRet = %d\n", iRet);
	return iRet;
}

static void GetFileNameByHz(char *pszHz, ST_HZ_FILE_MAP *data)
{
	int iCnt = 0;

	for(iCnt = 0;gstChineseMap[iCnt].pszHz != NULL;iCnt++){
		if(!strcmp(gstChineseMap[iCnt].pszHz,pszHz) && data){
            memcpy(data, &gstChineseMap[iCnt], sizeof(ST_HZ_FILE_MAP));
			//strcpy(data->pszFileName, gstHzMap[iCnt].pszFileName);
		}
	}
}

/**
 * @brief  		tts播报
 * @param[in]   mp3_file        mp3路径
 * @retval 无
 */
void play_tts_msg(char* tts_msg)
{

	appbool bAutoPowerSave;
	bAutoPowerSave = app_set_auto_powersave_mode(app_off);
	
	logger_debug("play_tts_msg = %s\n", tts_msg); 
	if(NULL != tts_msg){
		audio_tts_play(tts_msg, strlen(tts_msg), 1);
		logger_debug("finished audio_tts_play\n"); 
	}

	app_set_auto_powersave_mode(bAutoPowerSave);
}

/**
 * @brief  播报mp3文件
 * @param[in]   mp3_file        mp3路径
 * @retval 无
 */
int play_mp3_file(char* mp3_file)
{
	int iret = -1;

	if(NULL != mp3_file){
		iret = play_mp3(mp3_file);
	}
	return iret;
}

/**
 * @brief  金额播报使用mp3文字，补元
 * @param[in]   amount    金额123  or 123.34
 * @retval 无
 */
int play_amt_MP3(char *amount)
{
    char amountYuan[9+1],amountCent[2+1];
	char *pStart = NULL,*pPoint = NULL;
    char bcAmountStr[64] = {0};
	int iOffset = 0,iLen = 0;
	char szHz[2+1] = {0};
    ST_HZ_FILE_MAP data = {0};
	char *szWavPath[30] = {0};
	int iret = 0;
	int index = 0;

    logger_debug("%s\n", __FUNCTION__);  
    if(NULL == amount){
        return -1;
    }
    logger_debug("amount %s\n", amount);  
    if(strlen(amount) > 0){
        pStart = (char *)amount;
		pPoint = strstr((char *)amount, ".");
		if(pPoint != NULL){
			memset(amountYuan, 0, sizeof(amountYuan));
			memset(amountCent, 0, sizeof(amountCent));
			memcpy(amountYuan, amount, pPoint-pStart);
			if(NULL != pPoint+1){//可能只有. 没有小数
				if(1 == strlen(pPoint+1)){//1位小数
					memcpy(amountCent, pPoint+1, 1);
					strcat(amountCent, "0");
				}else{
					memcpy(amountCent, pPoint+1, 2);
				}
			}else{
				memcpy(amountCent, "00", 2);
			}
			logger_debug("amountCent = %s\n",amountCent);
			//memcpy(amountCent, pPoint+1, 2);
			GetBroadCastAmountStr(amountYuan, amountCent, bcAmountStr);
		}else{
            GetBroadCastAmountStr(amount, (char*)"00", bcAmountStr);
        }
    }else{
		return -1;
	}
	logger_debug("bcAmountStr = %s\n",bcAmountStr);
	strcat(bcAmountStr, "元");
    logger_debug("bcAmountStr = %s\n",bcAmountStr);
	iLen = strlen(bcAmountStr);
	
	for(iOffset = 0; iOffset < iLen; iOffset += 2){
		memset(&data, 0, sizeof(ST_HZ_FILE_MAP));
		memcpy(szHz,bcAmountStr+iOffset,2);
		GetFileNameByHz(szHz, &data);
        if(data.pszFileName != NULL && strlen(data.pszFileName) > 0){
			szWavPath[index] = (char *)data.pszFileName;
			logger_debug("szWavPath = %s\n", szWavPath[index]);  
			index++;
        }else{
            return -1;
        }
	}

	iret = audio_play_stream(AUDIO_FORMAT_MP3, szWavPath, 1);
	logger_debug("iret = %d\n",iret);  
	return  iret;
}



/**
 * @brief  数字播报使用mp3文字
 * @param[in]   num        播报内容，数字
 * @retval 无
 */
int play_num_MP3(char *num)
{
    char bcStr[64] = {0};
	int iOffset = 0,iLen = 0;
	char szHz[2+1] = {0};
    ST_HZ_FILE_MAP data = {0};
	char *szWavPath[30] = {0};
	int iret = 0;
	int index = 0;

    logger_debug("%s\n", __FUNCTION__);  
    if(NULL == num){
        return -1;
    }
    logger_debug("num %s\n", num);  
    if(strlen(num) > 0){
        GetBroadCastAmountStr(num, (char*)"00", bcStr);
    }else{
		return -1;
	}
	logger_debug("bcStr = %s\n",bcStr);

	iLen = strlen(bcStr);
	if(iLen <= 0){//如果str是空的就退出，否则audio_play_stream 会卡死
		return  iret;
	}
	for(iOffset = 0; iOffset < iLen; iOffset += 2){
		memset(&data, 0, sizeof(ST_HZ_FILE_MAP));
		memcpy(szHz,bcStr+iOffset,2);
		GetFileNameByHz(szHz, &data);
        if(data.pszFileName != NULL && strlen(data.pszFileName) > 0){
			szWavPath[index] = (char *)data.pszFileName;
			logger_debug("szWavPath = %s\n", szWavPath[index]);  
			index++;
        }else{
            return -1;
        }
	}
	iret = audio_play_stream(AUDIO_FORMAT_MP3, szWavPath, 1);
	logger_debug("iret = %d\n",iret);  
	return  iret;
}

/**
 * @brief  数字播报使用mp3文字
 * @param[in]   num        播报内容，数字
 * @retval 无
 */
int play_ver_MP3(char *num)
{
    char bcStr[64] = {0};
	int iOffset = 0,iLen = 0;
	char szHz[2+1] = {0};
    ST_HZ_FILE_MAP data = {0};
	char *szWavPath[30] = {0};
	int iret = 0;
	int index = 0;
	int inum = 0;

    logger_debug("%s\n", __FUNCTION__);  
    if(NULL == num){
        return -1;
    }
    logger_debug("num %s\n", num);  
    
    for(iOffset=0;iOffset< strlen(num);iOffset++){
    	memset(szHz,0,sizeof(szHz));
    	szHz[0] = num[iOffset];
    	inum = atoi(szHz);
    	GetCnNum(inum, bcStr);
  	}

	logger_debug("bcStr = %s\n",bcStr);

	iLen = strlen(bcStr);
	if(iLen <= 0){//如果str是空的就退出，否则audio_play_stream 会卡死
		return  iret;
	}
	for(iOffset = 0; iOffset < iLen; iOffset += 2){
		memset(&data, 0, sizeof(ST_HZ_FILE_MAP));
		memcpy(szHz,bcStr+iOffset,2);
		GetFileNameByHz(szHz, &data);
        if(data.pszFileName != NULL && strlen(data.pszFileName) > 0){
			szWavPath[index] = (char *)data.pszFileName;
			logger_debug("szWavPath = %s\n", szWavPath[index]);  
			index++;
        }else{
            return -1;
        }
	}
	iret = audio_play_stream(AUDIO_FORMAT_MP3, szWavPath, 1);
	logger_debug("iret = %d\n",iret);  
	return  iret;
}

/**
 * @brief  设置声音大小
 * @param[in]   vol  声音
 * @retval 无
 */
void set_play_vol(int vol)
{
	int volume = vol;

	if(volume < 10){
		volume = 10;
	}else if(volume > 100 ){
		volume = 100;
	}
	logger_debug("set_play_vol:%d\n",volume);  
	//set_vol_icon(stSysPara.volume);
	audio_set_volume(volume);
}

int is_zh_ch(char p)
{
	if(~(p >> 8) == 0) //将p字节进行移位运算，右移8位，这样，如果移位后是0，则说明原来的字节最高位为0，不是1那么也就不是汉字的一个字节。
	{
		return 0; //代表不是汉字
	}
	return -1;
}

int is_num(char *str, int size)
{
	int i = 0;

	if(NULL == str){
		return -1;
	}
	while(i < size){
		if(str[i] <= '9' && str[i] >= '0'){
			i++;
		}else{
			break;
		}
	}
	if(i == size){
		return size;
	}
	return -1;
}

/**
 * @brief  流媒体播报拼接mp3,一个汉字对应一个mp3  第一笔
 * @param[in]   str    播报内容
 * @retval 无
 */
int play_str_MP3(char *str)
{
    char bcStr[64] = {0};
	char tempStr[64] = {0};
	int iOffset = 0,iLen = 0;
	char szHz[2+1] = {0};
    ST_HZ_FILE_MAP data = {0};
	char *szWavPath[30] = {0};
	int iret = 0;
	int index = 0;
	char *p = NULL;
	int iOffset2 = 0;

    logger_debug("%s\n", __FUNCTION__);  
    if(NULL == str){
        return -1;
    }
    logger_debug("str %s\n", str);  
    
	iLen = strlen(str);
	while(iOffset < iLen){
		p = strstr(str+iOffset, "|");
		if(NULL != p){
			if(p-(str+iOffset) > sizeof(bcStr)){
				return -1;
			}
			memset(tempStr, 0, sizeof(tempStr));
			memcpy(tempStr, str+iOffset, p-(str+iOffset));
			logger_debug("tempStr = %s\n", tempStr);  
			iOffset = p - str + 1;
			logger_debug("iOffset = %d\n", iOffset);  
		}else{
			strcpy(tempStr, str+iOffset);
			logger_debug("tempStr = %s\n", tempStr);  
			iOffset = iLen;
		}
			if(is_num(tempStr, strlen(tempStr)) > 0){
				GetBroadCastAmountStr(tempStr, (char*)"00", bcStr);
				logger_debug("bcStr = %s\n", bcStr);  
				for(iOffset2 = 0; iOffset2 < strlen(bcStr); iOffset2 += 2){
					memset(&data, 0, sizeof(ST_HZ_FILE_MAP));
					memcpy(szHz,bcStr+iOffset2,2);
					GetFileNameByHz(szHz, &data); 
					if(data.pszFileName != NULL && strlen(data.pszFileName) > 0){
						szWavPath[index] = (char *)data.pszFileName;
						logger_debug("szWavPath = %s\n", szWavPath[index]);  
						index++;
					}else{
						return -1;
					}
				}
			}else{//按汉字处理
				memset(&data, 0, sizeof(ST_HZ_FILE_MAP));
				GetFileNameByHz(tempStr, &data);
				logger_debug("data.pszFileName = %s\n", data.pszFileName);  
				if(data.pszFileName != NULL && strlen(data.pszFileName) > 0){
					szWavPath[index] = (char *)data.pszFileName;
					logger_debug("szWavPath = %s\n", szWavPath[index]);  
					index++;
				}else{
					return -1;
				}
			}
			
	}
	
	iret = audio_play_stream(AUDIO_FORMAT_MP3, szWavPath, 1);
	logger_debug("iret = %d\n",iret);  
	return  iret;
}

/**
 * @brief  流媒体播报拼接mp3,一个汉字对应一个mp3  第一笔
 * @param[in]   str    播报内容
 * @retval 无
 */
int play_mp3_array(char *str)
{
#define WavPathNum 20	
#define WavPathLen 50 //路径长度

	int iRet = -1;
	char bcStr[64] = {0};
	char *szWavPath[WavPathNum+1] = {0}; //暂时支持20个mp3文件，最后一个是NULL
	proto_Items *proto_Item[WavPathNum]; 
	int item_Num = 0,i;
	char *sign = (char*)Audio_REGEX;

    logger_debug("%s\n", __FUNCTION__); 
	if(NULL == str){
        return -1;
    }
	
	item_Num = strSplit(str,strlen(str),sign[0],proto_Item,WavPathNum);
	logger_debug("item_Num = %d\n", item_Num);	

	for(i = 0;i < item_Num;i++){		
		//logger_debug("itemLen = %d\n",proto_Item[i]->itemLen);		
		szWavPath[i] = (char*)malloc(WavPathLen);
		//logger_debug("items_value = %s\n",proto_Item[i]->items_value); 		
		getaudioplayfilename(proto_Item[i]->items_value,bcStr);
		//logger_debug("szWavPath[%d] = %p, bcStr = %s\n", i, szWavPath[i], bcStr); 
		snprintf(szWavPath[i], WavPathLen, "%s/mp3/%s", APP_FILE_PATH, bcStr);	
		if(strstr(szWavPath[i],".mp3") == NULL){
			strcat(szWavPath[i],".mp3");
		}
		logger_debug("szWavPath[%d] = %s\n", i, szWavPath[i]);  
	}

	free_SplitSpace(proto_Item,item_Num);
	
	iRet = audio_play_stream(AUDIO_FORMAT_MP3, szWavPath, i);
	logger_debug("iRet = %d\n", iRet);

	for(; i >= 0; i--){
		logger_debug("szWavPath[%d] = %p\n", i, szWavPath[i]); 
		if(NULL != szWavPath[i]){
			free(szWavPath[i]);
			szWavPath[i] = NULL;
		}
	}
	return iRet;
}

 
// English words list
const char* numbers[] = {
    "0", "1", "2", "3", "4",
    "5", "6", "7", "8", "9",
    "10", "11", "12", "13", "14",
    "15", "16", "17", "18", "19"
};
 
const char* tens[] = {
    NULL, "10", "20", "30", "40",
    "50", "60", "70", "80", "90"
};
 
const char* thousand[] = {
    "1000", "10_6", "10_9"
};
 
// 0-99 convert to words
char* NumberToWords(int num) {
	static char buf[64]={0};

	memset((buf),0,sizeof(buf));
    if (num < 20) {
		snprintf(buf,sizeof(buf),"%s",numbers[num]);
        return buf;
    } else if (num < 100) {  //ten
        sprintf(buf, "%s %s", tens[num / 10], numbers[num % 10]);
        return buf;
    }
	return buf;
}

//  convert to words
char* GetWords(int num) {
	static char buf[64]={0};
	int part=0;
	
	if(num>=1000){
		snprintf(buf,sizeof(buf), " ");
		return buf;
	}

	memset((buf),0,sizeof(buf));
	if(num/100>0)
		snprintf(buf,sizeof(buf), "%s 100 ", numbers[num/100]);

	part=num%100;
	strcat(buf, NumberToWords(part));
	return buf;
}


// convert num to words
void convertNumberToWords(int num,char *out) {
	int count = 0;
	int part=0;
	char buff[128]={0};
	char buff1[128]={0};
	char buff2[128]={0};
	
	char unit1[64]={0};
	char unit2[32]={0};
	
	if(NULL==out)
		return;
	
	if (num == 0) {
        strcpy(out,"0");
        return;
    }
 
     while (num > 0) {
        part = num % 1000;
        if (part != 0) {
            if (count > 0) {
				memset(unit2,0,sizeof(unit2));
                strcpy(unit2,thousand[count - 1]); //thousand million ...
            }
			
            memset(unit1,0,sizeof(unit1));
			memset(buff,0,sizeof(buff));
			logger_debug("+++++part=%d\n",part);
            snprintf(unit1,sizeof(unit1),"%s",GetWords(part));
			logger_debug("+++++unit1=%s\n",unit1);
			logger_debug("+++++unit2=%s\n",unit2);
			snprintf(buff,sizeof(buff),"%s %s ",unit1,unit2);

			memset(buff2,0,sizeof(buff2));
			snprintf(buff2,sizeof(buff2),"%s",buff1);
			memset(buff1,0,sizeof(buff1));
			logger_debug("+++++buff=%s\n",buff);
			snprintf(buff1,sizeof(buff1),"%s",buff);
			strcat(buff1,buff2);
			logger_debug("+++++buff1=%s\n",buff1);
        }
        num /= 1000;
        count++;
    }
	strcpy(out,buff1);
}
 
int PlayMp3EngNum(int num)
{
    char amtstr[200]={0};
	char audioPath[40][30] = {0};
	char buff[40] = {0};
	int i=0,j=0;
	char *p1=NULL;
	char *p2=NULL;
	int len=0;
	
    convertNumberToWords(num,amtstr);
	logger_error("\n\n\n+++++++++++++++++\n%s\n",buff);

	p2=amtstr;
	while(1){
		p1=strchr(p2,' ');
		if(p1==NULL)
			break;
		len=p1-p2;
		if(len==0)
			break;
		memset(buff,0,sizeof(buff));
		memcpy(buff,p2,len);
		
		snprintf(audioPath[i],sizeof(audioPath[i]),"mp3/%s.mp3",buff);
		logger_error("audioPath:%s\n",audioPath[i]);
		i++;
		if(i>40)
			break;
		p2=p1+1;
	}

	for(j=0;j<i;j++)
		play_mp3_file(audioPath[i]);
	return 0;
}

int TestNumConvert(void){
    int number = 193456; // 示例数字
    char amtstr[200]={0};

	char audioPath[40][30] = {0};
	char buff[40] = {0};
	int i=0;
	char *p1=NULL;
	char *p2=NULL;
	int len=0;
	
    convertNumberToWords(number,amtstr);
	logger_error("\n\n\n++++++++@@@@@@@@@@@@@@+++++++++\n%s\n",buff);

	p2=amtstr;
	while(1){
		p1=strchr(p2,' ');
		if(p1==NULL)
			break;
		len=p1-p2;
		memset(buff,0,sizeof(buff));
		memcpy(buff,p2,len);
		
		snprintf(audioPath[i],sizeof(audioPath[i]),"mp3/%s.mp3",buff);
		logger_error("audioPath:%s\n",audioPath[i]);
		i++;
		if(i>40)
			break;
		p2=p1+1;
	}

	for(i=0;i<10;i++)
		play_mp3_file(audioPath[i]);
	return 0;
}


