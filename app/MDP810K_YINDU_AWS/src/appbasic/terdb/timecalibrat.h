#ifndef _TIME_CALIBRAT_H_
#define _TIME_CALIBRAT_H_
int TimeStr2tm(char *pYYYYMMDDHHMMSS, struct tm *ptm);
int tm2TimeStr(char pYYYYMMDDHHMMSS[14+1], struct tm *ptm);
int TimeCalibate(char *pExpectTimeStr, char pReferTimeStr[3][14+1], int *refernum);
int TimeCheckRange(char *pBeforeTimeStr,char *pCurTimeStr, int iCompTime);
char pub_check_time_out(struct timeval* timer, int timeout);
#endif


