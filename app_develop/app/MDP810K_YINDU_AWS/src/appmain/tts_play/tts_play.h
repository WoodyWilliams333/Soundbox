#ifndef _TTS_PLAY_H_
#define _TTS_PLAY_H_

#define MP3_FILE_PATH  "mp3"     //�ڲ�flsh�洢

typedef enum{
	TYPE_NUMBER = -1,
	TYPE_AMOUNT_EN = 0,//Ӣ�ﲥ��
	TYPE_AMOUNT_HINDI = '1',//ӡ���ﲥ��
	TYPE_AMOUNT_MARATHI = '3',
	TYPE_AMOUNT_GUJARATI = '4',
	TYPE_AMOUNT_TELUGU = '6',
	TYPE_AMOUNT_TMAIL = '7',
	TYPE_AMOUNT_KANNADA = '8',	
	TYPE_AMOUNT_MALAYALAM = '9',

}AMOUNT_PLAY_TYPE;



typedef struct tts_buff_msg {
	union {//������������
		struct {
			char * buf;  //�����ڴ棬�ǵ��ͷ�
			int len;
		}Audio;
	} ;
	int type;  //���õĲ�������
    char amount[35+1];  //�������ʾ���
    char timestamp[35]; //����ʱ��
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


//AWS�����ű�����
int PlayPackAudio_number(TTS_MSG *msgin,int amt_falg);


int play_pack_audiofile(char*filepath,const char* buf);


int jug_audiofile_exit(const char* filename);


/*ʹ���ڴ沥�� audiomap.c audio_ram_mp3Map���֧�ֵ�����
	amt_flag = 1 amountStr���ڽ��� �Զ������ǧ��Ԫ�Ƚ���ض�����

	amt_flag = 0 amountStr���ڳ������ֲ��� 

*/
int setAmountAudio_ex(char *amountStr,int amt_flag);


/*
TimeStr   :  ����ʱ�䴮
splt_flag :  ʱ�䴮�����ڷָ�������ַ� ��'|'���ָ�

*/
int playAudioTime(char *TimeStr,char splt_flag);


#endif //_TTS_PLAY_H_
