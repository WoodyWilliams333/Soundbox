
#ifndef _TRANS_AUDIO_H_
#define _TRANS_AUDIO_H_ 

typedef enum{
	WAV_TYPE_SUCCESS, //交易成功
	WAV_TYPE_WECHAT,  //微信到账
	WAV_TYPE_BANKCARD,//银行卡收款
	WAV_TYPE_UNIONPAY,//银联到账
	WAV_TYPE_ALIPAY,  //支付宝到账
}E_WAV_TYPE;

void TransResultBroadcastProc(char *msg);
void TransAmountResultBroadcastProc(uint8_t uciWavplay, int iWavType,uint8_t *bcdAmount);
void TransBroadCastWav(audio_t audioFormat, int wavType);
void TransBroadCastTts(int wavType);
void TransWavAmountBroadcastProc(audio_t audioFormat,int wavType,uint8_t *bcdAmount);
#endif

