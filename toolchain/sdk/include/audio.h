
/**
 * @brief       此模块用于描述 <strong>语音播报模块</strong> 相关的接口
 * @author      liluchang
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | liluchang       | 创建文件
*/


/**
 * @defgroup audio 语音
 * @{
*/


#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TONE_One            0       /**< audio with tone 1 */
#define TONE_Two            1       /**< audio with tone 2 */
#define TONE_Three          2       /**< audio with tone 3 */
#define TONE_letterA        3       /**< audio with tone A */
#define TONE_Four           4       /**< audio with tone 4 */
#define TONE_Five           5       /**< audio with tone 5 */
#define TONE_Six            6       /**< audio with tone 6 */
#define TONE_letterB        7       /**< audio with tone B */
#define TONE_Seven          8       /**< audio with tone 7 */
#define TONE_Eight          9       /**< audio with tone 8 */
#define TONE_Nine           10      /**< audio with tone 9 */
#define TONE_letterC        11      /**< audio with tone C */
#define TONE_Star           12      /**< audio with tone * */
#define TONE_Zero           13      /**< audio with tone 0 */
#define TONE_Pond           14      /**< audio with tone # */
#define TONE_letterD        15      /**< audio with tone D */

#define TTS_MAX_TEXT_LEN    958     /**< max tts text length */

#define AUDIO_TYPE_DTMF     0       /**< audio with DTMF */
#define AUDIO_TYPE_TTS      1       /**< audio with TTS */

/**
  * @brief  该枚举类型列出了播放音频支持的音频文件格式.\n
  */
typedef enum
{
    AUDIO_FORMAT_PCM,     /**< audio PCM format */
    AUDIO_FORMAT_WAVPCM,  /**< audio WAV format */
    AUDIO_FORMAT_MP3,     /**< audio MP3 format */
    AUDIO_FORMAT_AMR,     /**< audio MP3 format */
} audioFormat_t;

typedef enum
{
	TTS_RESOURCE_16K_CN = 1,
	TTS_RESOURCE_16K_EN,
	TTS_RESOURCE_8K_CN
}tts_resource_t;

typedef enum
{
	TTS_CONFIG_RESOURCE,
	TTS_CONFIG_SPEED,
	TTS_CONFIG_VOLUME,
    TTS_CONFIG_ENCODING,
    TTS_CONFIG_DIGITS,
    TTS_CONFIG_DGAIN,
	TTS_CONFIG_MAX,
}tts_config_t;

enum {
	TTS_GBK,
	TTS_UTF8,
	TTS_UCS2,
};

typedef enum {
    AUDIO_TIP_POWER_OFF  = 0x0,       /**< 关机语音       */
    AUDIO_TIP_USB_PLUG_IN,            /**< usb插入      */
    AUDIO_TIP_USB_PLUG_OUT,           /**< usb拔出      */
    AUDIO_TIP_LOW_BATTERY,            /**< 低电量        */
    AUDIO_TIP_MAX_NUM,
} audio_tip_event_t;


/**
 * @brief  set volume of tts
 * @note
 * @param[in] volume
 *      - 0~100
 * @return
 *      - 0: success
 *      - other: failure
 */
int audio_set_volume(int volume);

/**
 * @brief  get volume of tts
 * @note
 * @return
 *      - 0~100
 */
int audio_get_volume(void);

/**
 * @brief  play tts
 * @note   传入字符必须是GB2312、GBK或者GB18030编码
 * @param  text Pointer to the text that the string will be played
 * @param  len text长度
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_tts_play(const char *text, int len, int is_wait);

/** 
 * @brief  播放wav音频
 * @param  src wav格式的音频数据
 * @param  len 音频数据长度
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_wav_play(const char *src, int len, int is_wait);

/** 
 * @brief  播放指定格式的音频
 * @param  format pcm/wav/mp3格式
 * @param  src 音频数据
 * @param  len 音频数据长度
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_play(int format, const char *src, int len, int is_wait);

/** 
 * @brief  播放文件
 * @param  format pcm/wav/mp3格式
 * @param  path 文件名
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_play_file(const char *path, int is_wait);

/** 
 * @brief  数据流播放多个文件
 * @param  format 仅支持mp3格式
 * @param  file 多个文件路径的数组，以NULL结尾
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */

int audio_play_stream(int format, char **file, int is_wait);

/**
 * @brief 结束播放音频
 * @param[in] type
 *      目前仅支持 AUDIO_TYPE_TTS
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_abort(int type);

/**
 * @brief 是否正在播放语音
 * @return
 *      - 1: 正在播放语音
 *      - 0: 没有播放语音
 **/
int is_playing_tts(void);

/**
 * @brief 释放tts资源
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_suspend(void);
/**
 * @brief 获取tts资源
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_resume(void);
/**
 * @brief 设置tts参数
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_set_para(int type, int value);

int audio_tts_play_register(void *operator);         //ttslib使用

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AUDIO_H__ */

/** @}*/

