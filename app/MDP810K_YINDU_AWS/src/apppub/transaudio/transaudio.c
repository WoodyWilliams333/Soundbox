#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <appdatatypedef.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"
#include "transaudio.h"

#if SW_SUP_AUDIO
typedef struct hzfilemap{
	const char *pszHz;	
	const char *pszFileName; 
}ST_HZ_FILE_MAP;

const ST_HZ_FILE_MAP gstHzMap[] = {
	{"��",	"zero"},
	{"һ",	"one"},
	{"��",	"two"},
	{"��",	"three"},
	{"��",	"four"},
	{"��",	"five"},
	{"��",	"six"},
	{"��",	"seven"},
	{"��",	"eight"},
	{"��",	"nine"},
	{"ʮ",	"ten"},
	{"��",	"hundred"},
	{"ǧ",	"thousand"},
	{"��",	"wan"},
	{"��",	"yi"},
	{"��",	"point"},
	{"Ԫ",	"yuan"},
	{NULL,	NULL},
};

extern int ConvBcdAmount(uint8_t *bcdAmt, uint8_t *amount_ptr);

void TransResultBroadcastProc(char *msg)
{

	char broadcast1[100] = {0}, broadcast2[100] = {0};
	int icnt = 0, ilen = 0, ioff = 0;
	if(app_get_terminal_info(NULL)->stCap.bSupAudio == app_false
		/*|| stSysPara.swVoice == para_off*/){
		return;
	}
	snprintf(broadcast2, sizeof(broadcast2), "%s", msg);
	icnt = strlen(broadcast2);
	while(ioff < icnt){
		memset(broadcast1, 0, sizeof(broadcast1));
		ilen = MIN(16, icnt-ioff);
		memcpy(broadcast1, broadcast2+ioff, ilen);
		ioff += ilen;
		
		app_play_voice_tts(stSysPara.iVolnume, broadcast1);
		//if(ioff + ilen < icnt){
		app_wait_voice_finish();
		//}
	}		
}

static void GetCnNum(int iNum,char *bcStr)
{
	switch(iNum%10){
	case 0:
		strcat(bcStr,"��");
		break;
	case 1:
		strcat(bcStr,"һ");
		break;
	case 2:
		strcat(bcStr,"��");
		break;
	case 3:
		strcat(bcStr,"��");
		break;
	case 4:
		strcat(bcStr,"��");
		break;
	case 5:
		strcat(bcStr,"��");
		break;
	case 6:
		strcat(bcStr,"��");
		break;
	case 7:
		strcat(bcStr,"��");
		break;
	case 8:
		strcat(bcStr,"��");
		break;
	case 9:
		strcat(bcStr,"��");
		break;
	default:
		strcat(bcStr,"��");
		break;
	}
}


static void GetThousandBcMsg(int iAmountYuan,char *bcStr)
{
	int iFlag = 0;
	int iTemp = 0;

	//ǧλ
	iTemp = iAmountYuan;
	iTemp = iTemp/1000;
	if(iTemp > 0){
		GetCnNum(iTemp,bcStr);
		strcat(bcStr,"ǧ");
		iFlag = 1;
	}

	//��λ
	iTemp = iAmountYuan%1000;
	if(iTemp == 0){
		return;
	}
	iTemp = iTemp/100;
	if(iTemp > 0 || iFlag == 1){
		GetCnNum(iTemp,bcStr);
		if(iTemp != 0){
			strcat(bcStr,"��");
			iFlag = 1;
		}
		else{
			iFlag = 0;
		}
	}

	//ʮλ
	iTemp = iAmountYuan%100;
	if(iTemp == 0){
		return;
	}
	iTemp = iTemp/10;
	if(iTemp > 0 || iFlag == 1){
		GetCnNum(iTemp,bcStr);
		if(iTemp != 0){
			strcat(bcStr,"ʮ");
		}
	}

	//��λ
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
		return;
	}

	if(iAmountYuan == 0){
		strcat(bcStr,"��");
	}
	else{
		if(n1 > 0){
			GetThousandBcMsg(n1, bcStr);
			strcat(bcStr,"��");
		}

		if(n2 > 0){
			if (n1 > 0 && n2 < 1000){ //ǧλΪ�㲥���� 211018
				strcat(bcStr, "��");
			}
			GetThousandBcMsg(n2, bcStr);
		}
	}

	if(iAmountCent != 0){
		strcat(bcStr,"��");
		GetCnNum(iAmountCent/10, bcStr);
		GetCnNum(iAmountCent%10, bcStr);
	}

	strcat(bcStr,"Ԫ");
}

static void GetFileNameByHz(char *pszHz,char *filename)
{
	int iCnt = 0;

	for(iCnt = 0;gstHzMap[iCnt].pszHz != NULL;iCnt++){
		if(!strcmp(gstHzMap[iCnt].pszHz,pszHz) && filename){
			strcpy(filename,gstHzMap[iCnt].pszFileName);
		}
	}
}

void TransAmountResultBroadcastProc(uint8_t uciWavplay, int iWavType,uint8_t *bcdAmount)
{
	char bcAmountStr[64] = {0};
	uint8_t	amount[20];
	char amountYuan[9+1],amountCent[2+1];
	char *pStart = NULL,*pPoint = NULL;

	if(app_get_terminal_info(NULL)->stCap.bSupAudio == app_false
		/*|| stSysPara.swVoice == para_off*/){
		return;
	}

	if(memcmp(bcdAmount,"\x00\x00\x00\x00\x00\x00",6)){
		ConvBcdAmount(bcdAmount, amount);

		pStart = (char *)amount;
		pPoint = strstr((char *)amount,".");
		if(pPoint != NULL){
			memset(amountYuan,0,sizeof(amountYuan));
			memset(amountCent,0,sizeof(amountCent));
			memcpy(amountYuan,amount,pPoint-pStart);
			memcpy(amountCent,pPoint+1,2);
			GetBroadCastAmountStr(amountYuan, amountCent, bcAmountStr);
		}
	}

	if(uciWavplay == 0){
		TransBroadCastTts(iWavType); //tts.bin����
	}else{
		TransBroadCastWav(AUDIO_WAVPCM,iWavType); //wav����
	}
	TransResultBroadcastProc(bcAmountStr);
}

void TransBroadCastTts(int wavType)
{
	char szWavName[13] = {0};

	//���ݲ�������ȷ���ļ���
	switch(wavType){
		case WAV_TYPE_SUCCESS:
			snprintf(szWavName,sizeof(szWavName),"���׳ɹ�");
			break;
		case WAV_TYPE_WECHAT:
			snprintf(szWavName,sizeof(szWavName),"΢�ŵ���");
			break;
		case WAV_TYPE_BANKCARD:
			snprintf(szWavName,sizeof(szWavName),"���п��տ�");
			break;
		case WAV_TYPE_UNIONPAY:
			snprintf(szWavName,sizeof(szWavName),"��������");
			break;
		case WAV_TYPE_ALIPAY:
			snprintf(szWavName,sizeof(szWavName),"֧��������");
			break;
		default:
			return;
	}

	TransResultBroadcastProc(szWavName);
}

static void GetAudioName(audio_t audioFormat, char *pAudioPath, const char *pName){
	char szAudioName[50] = {0};
	
	if(audioFormat==AUDIO_WAVPCM){
		snprintf(szAudioName,sizeof(szAudioName),"%s.wav",pName);	
		sprintf(pAudioPath, "%s/%s", "/wav", szAudioName);	
	}else if(audioFormat==AUDIO_MP3){
		snprintf(szAudioName,sizeof(szAudioName),"%s.mp3",pName);	
		sprintf(pAudioPath, "%s/%s", "/mp3", szAudioName);
	}
}

void TransBroadCastWav(audio_t audioFormat, int wavType)
{
	char szWavPath[50] = {0};
	char *pWavData = NULL;
	int iWavLen = 0,fd = 0,iret = 0;

	//���ݲ�������ȷ���ļ���
	switch(wavType){
		case WAV_TYPE_SUCCESS:
			GetAudioName(audioFormat,szWavPath,"transucc");
			break;
		case WAV_TYPE_WECHAT:
			GetAudioName(audioFormat,szWavPath,"wechat");
			break;
		case WAV_TYPE_BANKCARD:
			GetAudioName(audioFormat,szWavPath,"bankcard");
			break;
		case WAV_TYPE_UNIONPAY:
			GetAudioName(audioFormat,szWavPath,"unionpay");
			break;
		case WAV_TYPE_ALIPAY:
			GetAudioName(audioFormat,szWavPath,"alipay");
			break;
		default:
			return;
	}
	logger_debug("szWavPath = %s\n", szWavPath);
	
	//�ж��ļ��Ƿ����
	if(app_file_exists(szWavPath) < 0){
		logger_debug("wav file not exist\n");
		return ;
	}

	//��ȡ�ļ�����
	iWavLen = app_file_size(szWavPath);
	if(iWavLen <= 0){
		logger_debug("wav file not exist\n");
		return ;
	}

	pWavData = (char *)malloc(iWavLen);
	if(pWavData == NULL){
		return ;
	}

	do{
		fd = app_file_open(szWavPath, 0);
		if(fd < 0){
			break;
		}

		iret = app_file_read(fd, pWavData, iWavLen);
		if(iret != iWavLen){
			break;
		}

		app_play_voice_wav(audioFormat, stSysPara.iVolnume, pWavData, iWavLen);
		app_wait_voice_finish();
	}while(0);

	app_file_close(fd);
	
	free(pWavData);
	pWavData = NULL;
	
}

void TransBroadCastWavFile(audio_t audioFormat, char *filename)
{
	char szWavName[13] = {0};
	char szWavPath[50] = {0};
	char *pWavData = NULL;
	int iWavLen = 0,fd = 0,iret = 0;

	if(audioFormat==AUDIO_WAVPCM){
		snprintf(szWavName,sizeof(szWavName),"%s.wav",filename);
		snprintf(szWavPath, sizeof(szWavPath), "%s/%s", "/wav", szWavName);
	}else if(audioFormat==AUDIO_MP3){
		snprintf(szWavName,sizeof(szWavName),"%s.mp3",filename);
		snprintf(szWavPath, sizeof(szWavPath), "%s/%s", "/mp3", szWavName);
	}
	logger_debug("szWavPath = %s\n", szWavPath);

	//�ж��ļ��Ƿ����
	if(app_file_exists(szWavPath) < 0){
		logger_debug("wav file not exist\n");
		return ;
	}

	//��ȡ�ļ�����
	iWavLen = app_file_size(szWavPath);
	if(iWavLen <= 0){
		logger_debug("wav file not exist\n");
		return ;
	}

	pWavData = (char *)malloc(iWavLen);
	if(pWavData == NULL){
		return ;
	}

	do{
		fd = app_file_open(szWavPath, 0);
		if(fd < 0){
			break;
		}

		iret = app_file_read(fd, pWavData, iWavLen);
		if(iret != iWavLen){
			break;
		}

		app_play_voice_wav(audioFormat, stSysPara.iVolnume, pWavData, iWavLen);
		app_wait_voice_finish();
	}while(0);

	app_file_close(fd);
	
	free(pWavData);
	pWavData = NULL;
	
}

static void TransBroadAmtWav(audio_t audioFormat, char *pszAmtStr)
{
	int iOffset = 0,iLen = 0;
	char szHz[2+1] = {0},szFileName[32] = {0};

	iLen = strlen(pszAmtStr);
	
	for(iOffset = 0;iOffset < iLen;iOffset += 2){
		memcpy(szHz,pszAmtStr+iOffset,2);
		GetFileNameByHz(szHz, szFileName);
		TransBroadCastWavFile(audioFormat,szFileName);
	}
}


void TransWavAmountBroadcastProc(audio_t audioFormat, int wavType,uint8_t *bcdAmount)
{
	char bcAmountStr[64] = {0};
	uint8_t	amount[20];
	char amountYuan[9+1],amountCent[2+1];
	char *pStart = NULL,*pPoint = NULL;

	if(app_get_terminal_info(NULL)->stCap.bSupAudio == app_false
		/*|| stSysPara.swVoice == para_off*/){
		return;
	}

	if(memcmp(bcdAmount,"\x00\x00\x00\x00\x00\x00",6)){
		ConvBcdAmount(bcdAmount, amount);

		pStart = (char *)amount;
		pPoint = strstr((char *)amount,".");
		if(pPoint != NULL){
			memset(amountYuan,0,sizeof(amountYuan));
			memset(amountCent,0,sizeof(amountCent));
			memcpy(amountYuan,amount,pPoint-pStart);
			memcpy(amountCent,pPoint+1,2);
			GetBroadCastAmountStr(amountYuan, amountCent, bcAmountStr);
		}
	}

	TransBroadCastWav(audioFormat,wavType);
	logger_debug("bcAmountStr = %s\n",bcAmountStr);
	if(strlen(bcAmountStr) > 0){
		TransBroadAmtWav(audioFormat,bcAmountStr);
	}
}

#endif

