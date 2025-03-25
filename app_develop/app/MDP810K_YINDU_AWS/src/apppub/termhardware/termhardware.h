/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2020-10-27 09:01:51
 * @LastEditors: YangJing
 * @LastEditTime: 2020-10-28 13:48:54
 */
#ifndef _TERM_HARDWARE_H_
#define _TERM_HARDWARE_H_
void GetPosTime(char *pszDate, char *pszTime);

appbool CheckBatteryCharge(void);
appbool CheckBatteryLow(void);
appbool CheckBatteryStatus(void);
appbool CheckIfNew6230(void);

void InitSavepowerTimer(void);
void StartSavepowerTimer(int timeperiod);
void StopSavepowerTimer(void);
void DeleteSavepowerTimer(void);

void InitPoweroffTimer(void);
void StartPoweroffTimer(int timeperiod);
void StopPoweroffTimer(void);
void DeletePoweroffTimer(void);

#endif
