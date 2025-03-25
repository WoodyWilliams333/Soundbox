/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2020-11-04 08:49:36
 * @LastEditors: YangJing
 * @LastEditTime: 2020-11-20 10:25:10
 */

#ifndef _TRANS_COMM_H_
#define _TRANS_COMM_H_

typedef struct {
	int start_line;
	int end_line;
}online_disp_ctrl;

void InitTransComm(void);
int PreDial(unsigned char ucConnectFlg);
void SetOnlineDispArea(int startline, int endline);
void GetOnlineDispArea(int *startline, int *endline);
int OnlineProc(int packettype, void *lpSendPacket, void *lpRecvPacket);

#endif

