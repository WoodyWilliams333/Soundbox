
#ifndef _APP_WINDOW_H_
#define _APP_WINDOW_H_

#include "applcd.h"

typedef enum{
	MSG_SUCC = 0,
	MSG_FAILED,
	MSG_INFO
}E_INFO_TYPE;

void disp_win_msg(const char *disp_info1, const char *disp_info2, E_INFO_TYPE type, int timeout);
void disp_win_msg_ms(const char *disp_info1, const char *disp_info2, E_INFO_TYPE type, int timeout_ms);
void disp_win_info_nowait(const char *disp_info1, const char *disp_info2);
void disp_win_msg_mul_language(const char *ch_info, const char *en_info, E_INFO_TYPE type, int timeout);
void disp_win_info_mul_language(const char *ch_info, const char *en_info, int timeout);
void disp_win_msg_mul_language_nowait(const char *ch_info, const char *en_info, E_INFO_TYPE type);
int disp_win_yesno(int timeout);
int disp_win_exit(int timeout);
void disp_win_info_spec_line(char *info, int startline, int endline, int max_character, int dispMode);
void disp_win_language_info_nowait(const char *disp_info1, const char *disp_info2,
	const char *disp_en_info1, const char *disp_en_info2);
void disp_win_msg_mul_lan(const char *disp_info1, const char *disp_info2, const char *disp_en_info1, const char *disp_en_info2, 
		E_INFO_TYPE type, int timeout);
void disp_win_msg_ms_mul_lan(const char *disp_info1, const char *disp_info2, const char *disp_eng_info1, const char *disp_eng_info2,
		E_INFO_TYPE type, int timeout_ms);
void app_lcd_display_mul_lan(const char *disp_info1, const char *disp_info2, 
	const char *disp_eng_info1, const char *disp_eng_info2);



#endif
