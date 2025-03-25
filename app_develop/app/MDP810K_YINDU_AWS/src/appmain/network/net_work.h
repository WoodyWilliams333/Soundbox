#ifndef _NET_WORK_H_
#define _NET_WORK_H_

#define NETWORK_HOSTPOINT_NAME   "Cloud Horn" //热点配网的热点名称前缀

int chk_net_play_status(appbool bNeedPlay, appbool bWait);
/**
 * @brief 单独使用线程检查网络状态
 * 
 */
void init_net_task(void);
//int PreDial(void);
void switch_Wifi4g_model(int model);
//4g模式检查SIM卡
void check_4g_exit_sim(void);
void set_wifi_ap_airkiss_type(int type);
appbool get_if_exit_ap(appbool ap_or_air);
appbool get_if_exit_check(void);
void net_reboot(void);
int app_get_wifi_signal(int *puiSignal, int *signalValue);
int app_lte_get_network_signal(int *puiSignal, int *rsrp_sinr);
void put_net_sem(void);
int check_get_sem_timeout(void);
//char pub_check_time_out(struct timeval* timer, int timeout);
int SaveCommunicationPara(void);
int PreDial(unsigned char ucConnectFlg);
int CheckCommStatus(CommType_e commType, appbool bWait);
#endif //_NET_WORK_H_