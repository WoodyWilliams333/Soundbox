#include <lcd.h>
#include<string.h>
#include "screen.h"
#include "task_thread.h"
#include "basicext.h"
#include "logger.h"
#include "tersharedata.h"
#include "screen.h"
/**
 * @brief  ������Ļ��ʾ����
 * @param[in]   display_content ����ʾ����
 * @param[in]   type ��ʾ���ͣ��ж��Ƿ���ʾԪ
 * @retval ��
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
            //mode:0:����ʾԪ 1:��ʾԪ
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
 * @brief  �����Ļ��ʾ
 * @retval ��
 */
void clear_screen_display(void)
{
    ntd_shutdown();
}

/**
 * @brief  ��������ͼ��
 * @retval ��
 */
void set_vol_icon(int vol)
{
    int iconvol = 0;
    
    //�ײ��ĵ�Ҳûд�Ǹ�������ͼ�꣬��һ��������ͼ��0=4g, 1=������2=wifi��3=����,�ڶ��������Ǿ���ֵ0~5
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