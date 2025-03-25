
#ifndef _APP_DISP_COMM_H_
#define _APP_DISP_COMM_H_
	

#include "applcd.h"

#define DISP_MENU_MACRO(menu,titleflag,keystart,keyend,timeout) disp_menu(menu,ARRAY_SIZE(menu),titleflag,keystart,keyend,timeout);

int disp_menu(const char menu[][64], int iLines, int iTitle, int iStartKey, int iEndKey, int iTimeOut);
void disp_mul_lan_string(int Col, int Line, uint32_t Mode, const char *pstChBuf, const char *pstEnBuf);
void disp_title(const char *pstChBuf, const char *pstEnBuf);
void disp_nfc_led(appbool blue, appbool yellow, appbool green, appbool red);


#endif

