
#ifndef _TER_FILE_COMM_H_
#define _TER_FILE_COMM_H_

#include "libapiext.h"
#include "terfiledef.h"
#include "esfile.h"


int SaveOpers(void);
int ReadSysOpers(void);
int LoadOpers(void);
int LoadDefaultOpers(void);

int ReadSysPara(void);
int SaveSysPara(void);
int LoadSysPara(void);
int LoadDefaultSysPara(void);

int SaveCtrlPara(void);
int ReadCtrlPara(void);
int LoadCtrlPara(void);
int LoadDefaultCtrlPara(void);

int SaveTransPara(void);
int ReadTransPara(void);
int LoadTransPara(void);
int LoadDefaultTransPara(void);

int SaveTransCtrlPara(void);
int ReadTransCtrlPara(void);
int LoadTransCtrlPara(void);
int LoadDefaultTransCtrlPara(void);

int SaveCommunicationPara(void);
int ReadCommunicationPara(void);
int LoadCommunicationPara(void);
int LoadDefaultCommunicationPara(void);

int SaveTmsCommunicationPara(void);
int ReadTmsCommunicationPara(void);
int LoadTmsCommunicationPara(void);
int LoadDefaultTmsCommunicationPara(void);

void ClearAllTxnUploadNum(void);
void UpdataTxnCtrlStatus(uint32_t uiTxnIndex, uint32_t uiStatus);
void ClearEsDirTmpFile(void);
void ClearTransLog(void);


int SaveReverseTranData(void);
int ReadReverseTransData(void);
void RemoveReverseTranData(void);

int ReadOriReverseTransData(void);


int SaveScriptTranData(void);
int ReadScriptTransData(void);
void RemoveScriptTranData(void);


int SaveTransTotalData(void);
int ReadTransTotalData(void);



/*
int SaveAddFileBINB(uint8_t *AddBinBuf);
void SaveFileBINC(uint8_t *AddBinBuf);
void LoadFileBIN(void);
void RemoveFileBIN(uint8_t ucCardBinFlg);
int CheckBinExistBinBList(uint8_t *card_no);
int CheckInBinList(uint8_t ucCardBinFlg, uint8_t *card_no);
*/

//uint8_t loadPosExtAppFile(void);

#endif

