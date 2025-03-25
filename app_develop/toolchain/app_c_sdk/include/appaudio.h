/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app audioģ��</strong> ��صĽӿ�
	 * @par �ļ�    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-14    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app audio </strong>  module
	 * @par file    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-14    | 1.0.1        | lydia         | Add English description
 @endif 
*/
/*!
 @if Chinese
	@defgroup appaudio ����
 @else
	@defgroup appaudio audio
 @endif
 * @{
*/ 
#ifndef _APP_AUDIO_H_
#define _APP_AUDIO_H_

#include <audio.h>

/**
 @if Chinese
	@brief  ��ö�������г��������ļ�����.
 @else
	@brief  This enumerated type lists the audio file types.
 @endif
  */
typedef enum{    
	AUDIO_PCM,     /**< audio PCM format */    
	AUDIO_WAVPCM,  /**< audio WAV format */   
	AUDIO_MP3,     /**< audio MP3 format */
} audio_t;

/*!
 @if Chinese
	@brief          tts��ʽ��������
	@param[in]      volume	-	��������
	@param[in]      pText	-	���ŵ������ַ���
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          tts play voice
	@param[in]      volume	-	volume
	@param[in]      pText	-	voice string
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_play_voice_tts(int volume, const char *pText);

/*!
 @if Chinese
	@brief          wav�ļ���ʽ��������
	@param[in]      audioFormat	-	4G֧��AUDIO_WAVPCM��AUDIO_MP3��2G����֧��AUDIO_WAVPCM
	@param[in]      volume		-	��������
	@param[in]      pwavdata	-	wav�ļ�����
	@param[in]      datalen		-	wav�ļ����ݳ���
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          wav play voice
	@param[in]      audioFormat	-	4G support AUDIO_WAVPCM��AUDIO_MP3��2G support AUDIO_WAVPCM
	@param[in]      volume		-	volume
	@param[in]      pwavdata	-	data of wav file
	@param[in]      datalen		-	data length of wav file
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_play_voice_wav(audio_t audioFormat, int volume, char *pwavdata, int datalen);

/*!
 @if Chinese
	@brief          ��ֹ����
 @else
	@brief          end play
 @endif
*/ 
extern void app_stop_voice(void);

/*!
 @if Chinese
	@brief          �����ȴ���ǰ�����������
 @else
	@brief          block and wait for the current voice play to complete
 @endif
*/  
extern void app_wait_voice_finish(void);


#endif

