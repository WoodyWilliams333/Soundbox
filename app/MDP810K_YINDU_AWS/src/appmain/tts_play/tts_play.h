#ifndef _TTS_PLAY_H_
#define _TTS_PLAY_H_

#define MP3_FILE_PATH  "mp3"     //内部flsh存储

typedef enum{
	TYPE_NUMBER = -1,
	TYPE_AMOUNT_EN = 0,//英语播报
	TYPE_AMOUNT_HINDI = '1',//印度语播报
	TYPE_AMOUNT_MARATHI = '3',
	TYPE_AMOUNT_GUJARATI = '4',
	TYPE_AMOUNT_TELUGU = '6',
	TYPE_AMOUNT_TMAIL = '7',
	TYPE_AMOUNT_KANNADA = '8',	
	TYPE_AMOUNT_MALAYALAM = '9',

}AMOUNT_PLAY_TYPE;



typedef struct tts_buff_msg {
	union {//播报语音内容
		struct {
			char * buf;  //申请内存，记得释放
			int len;
		}Audio;
	} ;
	int type;  //采用的播报类型
    char amount[35+1];  //晶体管显示金额
    char timestamp[35]; //播报时间
}TTS_MSG;


void play_tts_msg(char* tts_msg);
int play_mp3_file(char* mp3_file);
int play_num_MP3(char *num);
int play_ver_MP3(char *num);
int play_amt_MP3(char *amount);
void set_play_vol(int vol);
int play_str_MP3(char *str);
int play_mp3_array(char *str);
int TestNumConvert(void);
int PlayMp3EngNum(int num);


char* get_Tmail_amount_playfile(char *srcSmtNum,char* type);


//AWS播报脚本处理
int PlayPackAudio_number(TTS_MSG *msgin,int amt_falg);


int play_pack_audiofile(char*filepath,const char* buf);


int jug_audiofile_exit(const char* filename);


/*使用内存播报 audiomap.c audio_ram_mp3Map表格支持的数字
	amt_flag = 1 amountStr用于金额部分 自动补充百千万元等金额特定播报

	amt_flag = 0 amountStr用于常规数字播报 

*/
int setAmountAudio_ex(char *amountStr,int amt_flag);


/*
TimeStr   :  播报时间串
splt_flag :  时间串中用于分割读音的字符 用'|'来分割

*/
int playAudioTime(char *TimeStr,char splt_flag);


#endif //_TTS_PLAY_H_
