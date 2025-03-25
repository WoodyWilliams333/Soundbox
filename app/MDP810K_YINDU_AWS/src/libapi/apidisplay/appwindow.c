
#include <stdio.h>
#include <string.h>
#include <key.h>

#include "basicext.h"
#include "libapiext.h"


/**
 * @describe: 显示错误信息，清除所有行再显示
 * @param: disp_info1 必须存在
 * @param: disp_info2 可为空，如果不存在，则显示disp_info1一行即可
 * @param: 如果timeout<0 表示无限期等待， =0 表示按键后马上退出  >0 表示时间 ms
 */
void disp_win_msg(const char *disp_info1, const char *disp_info2, E_INFO_TYPE type, int timeout)
{
	app_lcd_clear_client();
	//app_lcd_clear_line(2, 6);
    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
        if(disp_info1 != NULL)
            app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
        if(disp_info2 != NULL)
            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
    } else {
        if(disp_info1 != NULL)
            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
        if(disp_info2 != NULL)
            app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
    }
	app_lcd_flip();

	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;			
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}
	app_kb_flush();
	if(timeout == -1){
		app_kb_get_key();
	}
	else{
		app_kb_get_key_ms(timeout*1000);
	}
	
}



/**
 * @describe: 显示错误信息，清除所有行再显示
 * @param: disp_info1 必须存在
 * @param: disp_info2 可为空，如果不存在，则显示disp_info1一行即可
 * @param: 如果timeout<0 表示无限期等待， =0 表示按键后马上退出  >0 表示时间 ms
 */
void disp_win_msg_mul_lan(const char *disp_info1, const char *disp_info2, const char *disp_en_info1, const char *disp_en_info2, 
		E_INFO_TYPE type, int timeout)
{
	app_lcd_clear_client();
	//app_lcd_clear_line(2, 6);
	if( App_Lcd_Lan == APP_ZH ){
	    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
	        if(disp_info1 != NULL)
	            app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
	        if(disp_info2 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	    } else {
	        if(disp_info1 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
	        if(disp_info2 != NULL)
	            app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	    }
	}
	else{		
		if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
			if(disp_en_info1 != NULL)
				app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info1);
			if(disp_en_info2 != NULL)
				app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info2);
		} else {
			if(disp_en_info1 != NULL)
				app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info1);
			if(disp_en_info2 != NULL)
				app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info2);
		}
	}
	app_lcd_flip();

	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;			
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}
	app_kb_flush();
	if(timeout == -1){
		app_kb_get_key();
	}
	else{
		app_kb_get_key_ms(timeout*1000);
	}
	
}


void disp_win_msg_ms(const char *disp_info1, const char *disp_info2, E_INFO_TYPE type, int timeout_ms)
{
	app_lcd_clear_client();
	//app_lcd_clear_line(2, 6);
	if(disp_info1 != NULL)
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
	if(disp_info2 != NULL)
		app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	app_lcd_flip();

	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;			
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}
	app_kb_flush();
	app_kb_get_key_ms(timeout_ms);
	
}
void disp_win_msg_ms_mul_lan(const char *disp_info1, const char *disp_info2, const char *disp_eng_info1, const char *disp_eng_info2,
		E_INFO_TYPE type, int timeout_ms)
{

	app_lcd_clear_client();
	//app_lcd_clear_line(2, 6);
	if( App_Lcd_Lan == APP_ZH ){
		if(disp_info1 != NULL)
			app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
		if(disp_info2 != NULL)
			app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	}
	else{
		if(disp_eng_info1 != NULL)
			app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_eng_info1);
		if(disp_eng_info2 != NULL)
			app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_eng_info2);
	}
	app_lcd_flip();

	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;			
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}
	app_kb_flush();
	app_kb_get_key_ms(timeout_ms);
	
}



void disp_win_info_nowait(const char *disp_info1, const char *disp_info2)
{
    app_lcd_clear_client(); //对于免密交易，还会清非接图标
    //app_lcd_clear_line(2, 6);
    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
        if (disp_info1 != NULL)
            app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
        if (disp_info2 != NULL)
            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
    } else {
        if (disp_info1 != NULL)
            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
        if (disp_info2 != NULL)
            app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
    }
    app_lcd_flip();
}

void disp_win_language_info_nowait(const char *disp_info1, const char *disp_info2,
	const char *disp_en_info1, const char *disp_en_info2)
{

    app_lcd_clear_client(); //对于免密交易，还会清非接图标
    //app_lcd_clear_line(2, 6);
    if( App_Lcd_Lan == APP_ZH ){
	    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
	        if (disp_info1 != NULL)
	            app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
	        if (disp_info2 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	    } else {
	        if (disp_info1 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
	        if (disp_info2 != NULL)
	            app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	    }
    }
	else{
		if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
	        if (disp_en_info1 != NULL)
	            app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info1);
	        if (disp_en_info2 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info2);
	    } else {
	        if (disp_en_info1 != NULL)
	            app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info1);
	        if (disp_en_info2 != NULL)
	            app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_en_info2);
	    }
	}
    app_lcd_flip();
}


void disp_win_msg_mul_language(const char *ch_info, const char *en_info, E_INFO_TYPE type, int timeout)
{

	//app_lcd_clear_client();
	app_lcd_clear_line(2, 6);
	if( App_Lcd_Lan == APP_ZH ){
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", ch_info);		
	}
	else{
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", en_info);		
	}
	app_lcd_flip();
	
	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;		
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}

	
	app_kb_flush();
	app_kb_get_key_ms(timeout*1000);
}

void disp_win_msg_mul_language_nowait(const char *ch_info, const char *en_info, E_INFO_TYPE type)
{

	//app_lcd_clear_client();
	app_lcd_clear_line(2, 6);
	if( App_Lcd_Lan == APP_ZH ){
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", ch_info);		
	}
	else{
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", en_info);		
	}
	app_lcd_flip();
	
	switch(type){
		case MSG_SUCC:
			app_beep_ok();
			break;		
		case MSG_FAILED:
			app_beep_err();
			break;
		default:
			break;
	}
}


void disp_win_info_mul_language(const char *ch_info, const char *en_info, int timeout)
{

	//app_lcd_clear_client();
	app_lcd_clear_line(2, 6);
	if( App_Lcd_Lan == APP_ZH ){
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", ch_info);		
	}
	else{
		app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", en_info);		
	}
	app_lcd_flip();
	
	app_beep_err();
	
	app_kb_flush();
	app_kb_get_key_ms(timeout*1000);
}


/**
 * @return: 按确定键返回1，按取消键返回0
 * @param: timeout 单位，秒
 */
int disp_win_yesno(int timeout)
{
	int ret = E_TRANS_TIMEOUT, t0 = 0, key = 0;
    int line;

    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
        line = 6;
    } else {
        line = 8;
    }

	if (timeout <= 0)
		return E_TRANS_TIMEOUT;
	
	t0 = app_get_tick_count();
	app_kb_flush();

	//app_lcd_clear_client();
	app_lcd_clear_line(2, line);
	app_lcd_display(4, line, DISP_CFONT, "%4s", "是");//|DISP_RIGHT
	app_lcd_display(4, line, DISP_CFONT, "%*s", ROW_MAX_LEN-4+2, "否");//|DISP_RIGHT
	app_lcd_flip();	
	
	app_kb_flush();
	while (app_get_tick_count() - t0 < ((unsigned int)timeout * 1000)) {

		key = app_kb_get_key_ms(10);
		if (key == KEY_CANCEL || key == KEY_ENTER){
			ret = (key == KEY_CANCEL ? app_no: app_yes);
			break;
		}
	}

	return ret;
}

int disp_win_exit(int timeout)
{
	int ret = E_TRANS_TIMEOUT, key = 0;
	unsigned int t0 = 0, t1 = 0;

	if (timeout <= 0)
		return E_TRANS_TIMEOUT;
	
	app_lcd_clear_all();
    if (app_get_terminal_info(NULL)->stCap.eScreenType == TERM_SCREEN_BW) {
        app_lcd_display(0, 2, DISP_CFONT|DISP_MEDIACY, "Exit APP?");
        app_lcd_display(0, 6, DISP_CFONT, "%s", "Cancel");
        app_lcd_display(0, 6, DISP_CFONT|DISP_RIGHT, "%s", "Enter");
    } else {
        app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "Exit APP?");
        app_lcd_display(0, 8, DISP_CFONT, "%s", "Cancel");
        app_lcd_display(0, 8, DISP_CFONT|DISP_RIGHT, "%s", "Enter");
    }
	app_lcd_flip();	
	
	t0 = app_get_tick_count();
	app_kb_flush();
	while (1) {
		t1 = app_get_tick_count();
		if(t1 - t0 > ((unsigned int)timeout * 1000)){
			break;
		}
		
		key = app_kb_get_key_ms(10);
		if (key == KEY_CANCEL || key == KEY_ENTER){
			logger_debug("key = 0x%X\n", key);
			ret = (key == KEY_CANCEL ? app_no: app_yes);
			break;
		}
	}

	logger_debug("t1 = %d, t0 = %d\n", t1, t0);
	logger_debug("ret = %d\n", ret);
	return ret;
	
}

void disp_win_info_spec_line(char *info, int startline, int endline, int max_character, int dispMode)
{
    int i;
    int line;
    unsigned char disp[128] = {0};

    for(i = 0, line = startline; i < strlen((char *)info) && line <= endline; line+=2)
    {
        memset(disp, 0, sizeof(disp));
        i += pub_strcopy((char *)disp, (char *)info + i, max_character);
		app_lcd_display(0, line, dispMode, "%s", disp);
    }
}
void app_lcd_display_mul_lan(const char *disp_info1, const char *disp_info2, 
	const char *disp_eng_info1, const char *disp_eng_info2)
{
	if( App_Lcd_Lan == APP_ZH ){
		if(disp_info1 != NULL)
			app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_info1);
		if(disp_info2 != NULL)
			app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_info2);
	}
	else{
		if(disp_eng_info1 != NULL)
			app_lcd_display(0, 4, DISP_CFONT|DISP_MEDIACY, "%s", disp_eng_info1);
		if(disp_eng_info2 != NULL)
			app_lcd_display(0, 6, DISP_CFONT|DISP_MEDIACY, "%s", disp_eng_info2);
	}
	
}



