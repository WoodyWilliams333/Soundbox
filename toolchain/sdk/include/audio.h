
/**
 * @brief       ��ģ���������� <strong>��������ģ��</strong> ��صĽӿ�
 * @author      liluchang
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | liluchang       | �����ļ�
*/


/**
 * @defgroup audio ����
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
  * @brief  ��ö�������г��˲�����Ƶ֧�ֵ���Ƶ�ļ���ʽ.\n
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
    AUDIO_TIP_POWER_OFF  = 0x0,       /**< �ػ�����       */
    AUDIO_TIP_USB_PLUG_IN,            /**< usb����      */
    AUDIO_TIP_USB_PLUG_OUT,           /**< usb�γ�      */
    AUDIO_TIP_LOW_BATTERY,            /**< �͵���        */
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
 * @note   �����ַ�������GB2312��GBK����GB18030����
 * @param  text Pointer to the text that the string will be played
 * @param  len text����
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_tts_play(const char *text, int len, int is_wait);

/** 
 * @brief  ����wav��Ƶ
 * @param  src wav��ʽ����Ƶ����
 * @param  len ��Ƶ���ݳ���
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_wav_play(const char *src, int len, int is_wait);

/** 
 * @brief  ����ָ����ʽ����Ƶ
 * @param  format pcm/wav/mp3��ʽ
 * @param  src ��Ƶ����
 * @param  len ��Ƶ���ݳ���
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_play(int format, const char *src, int len, int is_wait);

/** 
 * @brief  �����ļ�
 * @param  format pcm/wav/mp3��ʽ
 * @param  path �ļ���
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */
int audio_play_file(const char *path, int is_wait);

/** 
 * @brief  ���������Ŷ���ļ�
 * @param  format ��֧��mp3��ʽ
 * @param  file ����ļ�·�������飬��NULL��β
 * @param  is_wait 0:no waitting !0:waitting for playing tts done
 * @retval 0: success other: failure
 */

int audio_play_stream(int format, char **file, int is_wait);

/**
 * @brief ����������Ƶ
 * @param[in] type
 *      Ŀǰ��֧�� AUDIO_TYPE_TTS
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_abort(int type);

/**
 * @brief �Ƿ����ڲ�������
 * @return
 *      - 1: ���ڲ�������
 *      - 0: û�в�������
 **/
int is_playing_tts(void);

/**
 * @brief �ͷ�tts��Դ
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_suspend(void);
/**
 * @brief ��ȡtts��Դ
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_resume(void);
/**
 * @brief ����tts����
 * @return
 *      - 0: success
 *      - other: failure
 **/
int audio_tts_set_para(int type, int value);

int audio_tts_play_register(void *operator);         //ttslibʹ��

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AUDIO_H__ */

/** @}*/

