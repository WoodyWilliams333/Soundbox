
#ifndef _TRANS_AUDIO_H_
#define _TRANS_AUDIO_H_ 

typedef enum{
	WAV_TYPE_SUCCESS, //���׳ɹ�
	WAV_TYPE_WECHAT,  //΢�ŵ���
	WAV_TYPE_BANKCARD,//���п��տ�
	WAV_TYPE_UNIONPAY,//��������
	WAV_TYPE_ALIPAY,  //֧��������
}E_WAV_TYPE;

void TransResultBroadcastProc(char *msg);
void TransAmountResultBroadcastProc(uint8_t uciWavplay, int iWavType,uint8_t *bcdAmount);
void TransBroadCastWav(audio_t audioFormat, int wavType);
void TransBroadCastTts(int wavType);
void TransWavAmountBroadcastProc(audio_t audioFormat,int wavType,uint8_t *bcdAmount);
#endif

