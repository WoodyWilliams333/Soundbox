#ifndef _TASK_THREAD_H_
#define _TASK_THREAD_H_

typedef enum{
    PLAY_TTS = 1,       //使用TTS播报，如果有金额可能包含其中
    PLAY_MP3 = 2,       //mp3播报amount内容，为纯数字
    PLAY_MP3_AMOUNT = 3,//mp3播报amount内容，为金额，需要特殊处理
    PLAY_MP3_VER = 4,   //mp3播报纯数字,比如版本号
}PLAY_MODEL;

typedef enum{
    PLAY_BUSY = 1,
    PLAY_FREE = 2,
}PLAY_STATE;

typedef enum{
    LED_STATE_OFF =0,
    LED_STATE_ON = 1,
}PLAY_LED_STATE;

void init_task(void);
void add_play_text(const char *text, const char *amount, const char *time, PLAY_MODEL model);
int check_playing(void);
int set_play_state(int state);
int get_have_task_play(void);
int wait_play_timeout(int timeout);
void set_screen_light(void);
void clear_task_queue(void);
void clear_and_stop_play(void);
#endif