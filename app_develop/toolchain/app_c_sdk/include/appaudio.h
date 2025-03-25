/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app audio模块</strong> 相关的接口
	 * @par 文件    appasyncmsg.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-14    | 1.0.1        | lydia         | 增加英文注释  
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
	@defgroup appaudio 喇叭
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
	@brief  该枚举类型列出了语音文件类型.
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
	@brief          tts方式播放语音
	@param[in]      volume	-	播放音量
	@param[in]      pText	-	播放的语音字符串
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          wav文件方式播放语音
	@param[in]      audioFormat	-	4G支持AUDIO_WAVPCM和AUDIO_MP3，2G仅仅支持AUDIO_WAVPCM
	@param[in]      volume		-	播放音量
	@param[in]      pwavdata	-	wav文件数据
	@param[in]      datalen		-	wav文件数据长度
	@return         0		-	成功
	@return         其它	-	失败
 @else
	@brief          wav play voice
	@param[in]      audioFormat	-	4G support AUDIO_WAVPCM和AUDIO_MP3，2G support AUDIO_WAVPCM
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
	@brief          终止播放
 @else
	@brief          end play
 @endif
*/ 
extern void app_stop_voice(void);

/*!
 @if Chinese
	@brief          阻塞等待当前语音播放完成
 @else
	@brief          block and wait for the current voice play to complete
 @endif
*/  
extern void app_wait_voice_finish(void);


#endif

