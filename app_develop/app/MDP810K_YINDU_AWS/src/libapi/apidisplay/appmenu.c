#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"


/**
 * @describe: 显示菜单
 */
int disp_menu(const char menu[][64], int iLines, int iTitle, int iStartKey, int iEndKey, int iTimeOut)
{
	int screens = 0;
	int start_line = 0;
	int start_item = 0;
	int line_per_screen = 0;
	int cur_screen = 0;
	int i = 0, t =0, key = -1;

	app_kb_flush();
	app_lcd_clear_all();
	
	if (iTitle) {
		start_item = 1;
		screens = (iLines - 2) / (DISP_MAX_LINE - 1) + 1;
		start_line = 1;
		line_per_screen = DISP_MAX_LINE - 1;

		app_lcd_display(0, 0, DISP_CFONT | DISP_INVLINE | DISP_MEDIACY, "%s", (char *)menu[0]);
		app_lcd_flip();
	} else {
		start_item = 0;
		screens = (iLines - 1) / DISP_MAX_LINE + 1;
		start_line = 0;
		line_per_screen = DISP_MAX_LINE;
	}

	cur_screen = 0;

	while (1) {

		//设置图标
		if(cur_screen + 1 < screens){
			app_lcd_set_icon(ICON_DOWN, app_on);
		}
		else{
			app_lcd_set_icon(ICON_DOWN, app_off);
		}
		
		if( cur_screen > 0){
			app_lcd_set_icon(ICON_UP, app_on);
		}
		else{
			app_lcd_set_icon(ICON_UP, app_off);
		}

        if (iTitle) {
            app_lcd_clear_client();
        } else {
            app_lcd_clear_all();
        }
		for (i = 0; i < line_per_screen; i++) {
			t = i + line_per_screen * cur_screen + start_item;
			if (t < iLines) {
				//显示左对齐，并且超过一行自动截断210430
				app_lcd_display(0, (i + start_line)*2, DISP_CFONT, "%-*.*s", DISP_MAX_LEN, DISP_MAX_LEN, (char *) menu[t]);
			}
		}
		app_lcd_flip();
		

		key = app_kb_get_key_ms(iTimeOut * 1000);

		if (key == KEY_CANCEL || key == KEY_TIMEOUT) {
			break;
		} else if (key == KEY_ENTER || key == KEY_DOWN ) {
			if (cur_screen < screens - 1)
				cur_screen++;
		} else if (key == KEY_UP) {
			if (cur_screen > 0)
				cur_screen--;
		} else if (key >= iStartKey && key <= iEndKey) {
			break;
		} 
	}

	app_lcd_set_icon(ICON_DOWN, app_off);
	app_lcd_set_icon(ICON_UP, app_off);

	return key;
}


