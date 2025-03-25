#include <lcd.h>
#include<string.h>
#include "screen.h"
#include "task_thread.h"
#include "basicext.h"
#include "logger.h"
#include "tersharedata.h"
#include "screen.h"
/**
 * @brief  设置屏幕显示内容
 * @param[in]   display_content 待显示内容
 * @param[in]   type 显示类型，判断是否显示元
 * @retval 无
 */

void ntd_shutdown(void)
{
	return;
}

void set_screen_display(char* display_content, int type)
{
#ifndef __DISP_TRANS_NUM
    if(NULL != display_content){
        if(PLAY_MP3_AMOUNT == type){
            ntd_display(1, display_content);
        }else{
            //mode:0:不显示元 1:显示元
            ntd_display(0, display_content);
        }	
    }
#else
	char buff[21]={0};
	snprintf(buff,sizeof(buff),"%d",stSysPara.record_num);
	ntd_display(0,buff);
#endif
}
/**
 * @brief  清除屏幕显示
 * @retval 无
 */
void clear_screen_display(void)
{
    ntd_shutdown();
}

/**
 * @brief  设置声音图标
 * @retval 无
 */
void set_vol_icon(int vol)
{
    int iconvol = 0;
    
    //底层文档也没写那个是声音图标，第一个参数是图标0=4g, 1=电量，2=wifi，3=声音,第二个参数是具体值0~5
    switch(vol/10){
        case 0:
            iconvol = 0;
            break;
        case 1:
        case 2:
            iconvol = 1;
            break;
        case 3:
        case 4:
            iconvol = 2;
            break;
        case 5:
        case 6:
            iconvol = 3;
            break;
        case 7:
        case 8:
        case 9:
            iconvol = 4;
            break;
        default:
            iconvol = 5;
            break;
    }
    logger_debug("iconvol: %d\n", iconvol);
    lcd_set_icon(3,iconvol);
}