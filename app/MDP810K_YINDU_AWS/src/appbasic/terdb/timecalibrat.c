/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2020-01-09 14:24:03
 * @LastEditors  : YangJing
 * @LastEditTime : 2020-01-14 09:37:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <system.h>
#include <math.h>
#include <sys/time.h>
#include "basicext.h"
#include "apperrdef.h"
#include "appsys.h"
#include "logger.h"
#include "timecalibrat.h"
#define ERROR_RANGE_SECOND      20*24*60*60

void printtm(const char *ptimename, struct tm *ptm)
{
    logger_debug("%s: %d-%d-%d %d:%d:%d\n", ptimename, 
        ptm->tm_year, ptm->tm_mon, ptm->tm_mday,
        ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
}

int TimeStr2tm(char *pYYYYMMDDHHMMSS, struct tm *ptm)
{
    #ifndef bcd2bin
    #define bcd2bin(x) (((((x)>>4) & 0x0f) * 10) + ((x) & 0x0f)) //bcd转换为十进制
    #endif
    
    uint8_t strBcd[14+1] = {0};
    uint8_t *ptimebcd = strBcd;
    struct tm ltm;

    //logger_debug("time len = %d\n", strlen(pYYYYMMDDHHMMSS));
	if(strlen(pYYYYMMDDHHMMSS) != 14) {
		return -1;
	}

    pub_asc2bcd((char *)pYYYYMMDDHHMMSS, 14, strBcd);
    
	memset(&ltm, 0, sizeof(ltm));
	ltm.tm_year = (bcd2bin(ptimebcd[0])) * 100 + bcd2bin(ptimebcd[1]) - 1900;
	ltm.tm_mon  = bcd2bin(ptimebcd[2]) - 1;
	ltm.tm_mday = bcd2bin(ptimebcd[3]);
	ltm.tm_hour = bcd2bin(ptimebcd[4]);
	ltm.tm_min  = bcd2bin(ptimebcd[5]);
	ltm.tm_sec  = bcd2bin(ptimebcd[6]);

    *ptm = ltm;

    return 0;
}

int tm2TimeStr(char pYYYYMMDDHHMMSS[14+1], struct tm *ptm)
{
    snprintf((char *)pYYYYMMDDHHMMSS, 4+1, "%.4d", ptm->tm_year + 1900);
    snprintf((char *)pYYYYMMDDHHMMSS+4, 2+1, "%.2d", ptm->tm_mon + 1);
    snprintf((char *)pYYYYMMDDHHMMSS+4+2, 2+1, "%.2d", ptm->tm_mday);
    snprintf((char *)pYYYYMMDDHHMMSS+4+2+2, 2+1, "%.2d", ptm->tm_hour);
    snprintf((char *)pYYYYMMDDHHMMSS+4+2+2+2, 2+1, "%.2d", ptm->tm_min);
    snprintf((char *)pYYYYMMDDHHMMSS+4+2+2+2+2, 2+1, "%.2d", ptm->tm_sec);


    return 0;
}

int TimeCalibate(char *pExpectTimeStr, char pReferTimeStr[3][14+1], int *refernum)
{
    int ret = RET_OK;
    struct tm expecttm, curtm;
    char curtimerstr[14+1] = {0};
    time_t expecttime, curtime;
    time_t offsettime = 0;
    
    do{
        // if(*refernum <= 0){
        //     logger_error("refernum in is invalid, refernum = %d\n", *refernum);
        //     ret = E_APP_FAILED;   
        // }   
       
        app_get_time(curtimerstr);

        logger_debug("pExpectTimeStr = %s, curtimerstr = %s\n", pExpectTimeStr, curtimerstr); 
        
        ret = TimeStr2tm(pExpectTimeStr, &expecttm);
        ret += TimeStr2tm(curtimerstr, &curtm);
        if(ret != 0){
            logger_error("TimeStr2tm failed, ret = %d\n", ret);
            ret = E_APP_FAILED;   
            break;     
        }
        
        ret = RET_OK;
        printtm("expect tm", &expecttm);
        printtm("cur tm", &curtm);
        
        expecttime = mktime(&expecttm);
        curtime = mktime(&curtm);

        offsettime = abs(curtime - expecttime);
        if(offsettime <= ERROR_RANGE_SECOND){ //误差允许范围内，期望值可用
            //pReferTimeStr[0] = expecttime;
            tm2TimeStr(pReferTimeStr[0], &expecttm);
            *refernum = 1;
            break;
        }

        //期望值值前进一年，计算时间
        expecttm.tm_year = curtm.tm_year + 1;
        printtm("next year expect tm", &expecttm); 
        expecttime = mktime(&expecttm);
        curtime = mktime(&curtm);
        offsettime = abs(curtime - expecttime);
        if(offsettime <= ERROR_RANGE_SECOND){ //误差允许范围内，期望值可用
            //pReferTimeStr[0] = expecttime;
            tm2TimeStr(pReferTimeStr[0], &expecttm);
            *refernum = 1;
            break;
        }

        //期望值值后退一年，计算时间
        expecttm.tm_year = curtm.tm_year - 1; 
        printtm("prev year expect tm", &expecttm); 
        expecttime = mktime(&expecttm);
        curtime = mktime(&curtm);
        offsettime = abs(curtime - expecttime);
        if(offsettime <= ERROR_RANGE_SECOND){ //误差允许范围内，期望值可用
            //pReferTimeStr[0] = expecttime;
            tm2TimeStr(pReferTimeStr[0], &expecttm);
            *refernum = 1;
            break;
        }

        //向前一年和回退一年都超过了最大误差值，则提供参考出去
         expecttm.tm_year = curtm.tm_year - 1;
         tm2TimeStr(pReferTimeStr[0], &expecttm);
         expecttm.tm_year = curtm.tm_year;
         tm2TimeStr(pReferTimeStr[1], &expecttm);
         expecttm.tm_year = curtm.tm_year + 1;
         tm2TimeStr(pReferTimeStr[2], &expecttm);
        *refernum = 3;

    }while(0);

    return ret;
}

int TimeCheckRange(char *pBeforeTimeStr,char *pCurTimeStr, int iCompTime)
{
	int ret = RET_OK;
    struct tm expecttm, curtm;
    time_t expecttime, curtime;
    time_t offsettime = 0;

	ret = TimeStr2tm(pBeforeTimeStr, &expecttm);
    ret += TimeStr2tm(pCurTimeStr, &curtm);
    if(ret != 0){
    	logger_error("TimeStr2tm failed, ret = %d\n", ret);
        ret = E_APP_FAILED;   
		return ret;     
    }
        
    ret = RET_OK;
    //printtm("expect tm", &expecttm);
    //printtm("cur tm", &curtm);
        
    expecttime = mktime(&expecttm);
    curtime = mktime(&curtm);

    offsettime = abs(curtime - expecttime);
    if(offsettime <= iCompTime){ //差值在时间范围内
        return -1;
    }
	return RET_OK;
}

char pub_check_time_out(struct timeval* timer, int timeout)
{
    struct timeval now, diff, add;

    gettimeofday(&now, NULL);
	//logger_debug("pub_check_time_out now.tv_sec=%d\n",now.tv_sec);
    
    diff.tv_sec = timeout/1000;
    diff.tv_usec = (timeout%1000) * 1000;

    timeradd(timer, &diff, &add);

    return timercmp(&now, &add, >=);
}

