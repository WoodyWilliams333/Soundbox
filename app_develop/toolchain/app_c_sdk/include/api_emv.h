#ifndef __API_EMV_H__
#define __API_EMV_H__

#ifdef __cplusplus	
extern "C" {
#endif /* __cplusplus */

#include <emvapi.h>
#include <qpbocapi.h>

#define STR_PBOC_AID		"A000000333"

#define MIN_VERSION_LEN     64		// 获取版本信息的buffer最少长度

#define CLSS_VISA_QVSDC   2   // qPBOC方式
#define CLSS_VISA_VSDC    3   // 完整非接PBOC方式

#define AC_AAC       0x00
#define AC_TC        0x01
#define AC_ARQC      0x02

#define RD_CVM_NO            0x00	//no CVM
#define RD_CVM_SIG           0x10	//signature
#define RD_CVM_ONLINE_PIN    0x11	//online PIN

#define     YES                     0x01
#define     NO                      0x00

//内核类型
#define KERNTYPE_DEF             0
#define KERNTYPE_JCB             1
#define KERNTYPE_MC              2
#define KERNTYPE_VIS             3
#define KERNTYPE_PBOC            4
#define KERNTYPE_AE              5
#define KERNTYPE_RFU             6

//EMV参数操作返回枚举
typedef enum
{
	EMV_PRM_ERR =-4, //EMV参数错
	EMV_PRM_NOT_FOUND=-3, //EMV参数未找到
	EMV_PRM_CAPK_CHK_HASH_FAIL=-2, //公钥HASH校验错误
	EMV_PRM_FAIL=-1, //EMV参数操作失败
	EMV_PRM_OK=0 //EMV参数操作成功
} ParamStatus;

//EMV交易状态枚举
typedef enum
{ 
	EMV_TIMEOUT = -21,	   //EMV操作超时
    EMV_QPBOC_DODGE = -20,       //闪卡处理失败发生闪卡
	EMV_EC_DECLINED = -19, //电子现金脱机拒绝
	EMV_APP_NOACCEPT = -18, //应用不接受, 可重新选择
	EMV_SCRIPT_FAIL = -17, //发卡行脚本执行失败
	EMV_ARPC_FAIL = -16, //发卡行认证失败
	EMV_DECLINED = -15, //交易拒绝
	EMV_CANCEL = -14, //交易取消
	EMV_ONLINE = -13, //交易应联机
	EMV_CVM_FAIL = -12, //持卡人验证失败
	EMV_APP_EXPIRED = -11, //应用已失效
	EMV_APP_EFFECT = -10, //应用尚未生效
	EMV_AUTH_FAIL = -9, //数据认证失败
	EMV_FALLBACK = -8, //交易fallback
	EMV_APP_BLOCK = -7, //应用已锁
	EMV_CANDIDATELIST_EMPTY = -6, //无共同应用
	EMV_PARA_ERR = -5, //参数错
	EMV_CARD_BLOCK = -4, //卡片已锁
	EMV_COMMAND_FAIL = -3, //读卡失败
	EMV_CARD_REMOVED = -2, //交易中卡片被移开
	EMV_FAIL = -1, //执行失败
	EMV_OK = 0, //执行成功
	EMV_OTHER_INTERFACE = 1, //请尝试其他通信界面
	EMV_QPBOC_OFFLINE = 2, //非接触QPBOC交易脱机接受
	EMV_QPBOC_ONLINE = 3, //非接触QPBOC交易联机
	EMV_PBOC_ONLINE = 4, //非接触PBOC交易联机
	//EMV_MSD_ONLINE = 5 //非接触MSD交易联机
	EMV_EC_ACCEPT = 6, //电子现金脱机接受
	EMV_OFFLINE_ACCEPT = 7 //标准流程脱机接受
} EmvStatus;

//终端参数结构体
typedef struct { 
	char TermCap[3] ; /*终端性能 '9F33'*/
	char AdditionalTermCap[5] ; /*终端附加性能*/
	char IFDSerialNum[9] ; /*IFD序列号 '9F1E'*/
	char TermCountryCode[2] ; /*终端国家代码 '9F1A'*/
	char TermID[9] ; /*终端标识 '9F1C'*/
	char TermType ; /*终端类型 '9F35'*/
	char TransCurrCode[2] ; /*交易货币 '5F2A'*/
	char TransCurrExp; /*交易货币指数 '5F36'*/
	//PSE Selection 
	char bPSE; /*是否支持选择PSE 1*/
	char bCardHolderConfirm; /*是否支持持卡人确认 1*/
	char bPreferedOrder; /*是否支持优选显示 1*/
	char bPartialAID; /*是否支持部分AID匹配 1*/
	char bMultiLanguage; /*是否支持多语言 0*/
	char bCommonCharset; /*是否支持公共字符集 0*/
	//Data Authentication 
	char bIPKCValidtionCheck; /*是否检查发卡行公钥认证有效性 1*/
	char bContainDefaultDDOL; /*是否包含默认DDOL 1*/
	char bCAPKFailOperAction; /*CAPK读取出错时是否需要操作员干预 1*/
	char bCAPKChecksum; /*是否进行CAPK校验 1*/
	//Cardholder Verification Method 
	char bBypassPIN; /*是否支持跳过PIN输入 (须改流程,待定)*/
	char bGetDataForPINCounter; /*PIN尝试计数器是否支持GetData 1*/
	char bFailCVM; /*是否支持错误的CVM(1必须为Yes)*/
	char bAmountBeforeCVM; /*CVM前是否已知金额 1*/
	//Term Risk Management 
	char bLimitFloorCheck; /*是否进行最低限额检查 1*/
	char bRandomTransSelect; /*是否进行随机交易选择 1*/
	char bValocityCheck; /*是否进行频度检查 1*/
	char bTransLog; /*是否记录交易日志 1*/
	char bExceptionFile; /*是否支持卡片黑名单 1*/
	char bTRMBaseOnAIP; /*终端风险管理是否基于应用交互特征 1*/
	//Terminal Action Analysis 
	char bTerminalActionCodes; /*是否支持终端行为代码 1*/
	char bDefActCodesBefore1stGenAC; /*缺省行为代码是否先于FirstGenerateAC ?*/
	char bDefActCodesAfter1stGenAC; /*缺省行为代码是否后于FirstGenerateAC ?*/
	//Completion Processing char bForceOnline; /*是否允许强制联机 1*/
	char bForceAccept; /*是否允许强制接受交易 1*/
	char bAdvices; /*是否支持通知 0*/
	char bIISVoiceReferal; /*是否支持发卡方发起的语音参考 ?*/
	char bCardVoiceReferal; /*是否支持发卡方发起的语音参考 ?*/
	char bBatchDataCapture; /*是否支持批数据采集*/
	char bDefaultTDOL; /*是否有缺省TDOL*/
	//Exception Handling 
	char cEntryModeUsingMagStripe; /*IC卡故障而只能刷卡时POSEntryMode值*/
	char bAccountSelect; /*是否支持账号选择*/
}TERMCONFIG;

typedef enum{
	EMV_PARAM_AID,
	EMV_PARAM_CAPK,
}EmvParamType;

//EMV_AID参数结构体
typedef struct
{
	unsigned char AID[16]; //AID
	unsigned char AID_Length; //AID长度
	unsigned char bAppSelIndicator; //应用选择指示符
	unsigned char bTerminalPriority; //终端优先级
	/* Domestic */
	unsigned char bMaxTargetDomestic; /*偏置随机选择的最大目标百分数*/
	unsigned char bTargetPercentageDomestic; /*随机选择的目标百分数*/
	unsigned char abTFL_Domestic[4]; /* 终端最低限额 */
	unsigned char abThresholdValueDomestic[4]; /*偏置随机选择的阈值*/
	/* International */
	unsigned char bMaxTargetPercentageInt; /*偏置随机选择的最大目标百分数*/
	unsigned char bTargetPercentageInt; /*随机选择的目标百分数*/
	unsigned char abTFL_International[4]; /* 终端最低限额 */
	unsigned char abThresholdValueInt[4]; /*偏置随机选择的阈值*/
	unsigned char abTerminalApplVersion[4]; /* 终端应用版本 */
	unsigned char abMerchantCategoryCode[2]; /* 商户类别代码tag: 9F15 */
	unsigned char bTransactionCategoryCode; /* 交易类别代码Europay only, tag: 9F53 */
	unsigned char abTrnCurrencyCode[2]; /* 货币代码tag: 5F2A */
	unsigned char abTerminalCountryCode[2]; /* 国家代码终端tag: 9F1A */
	unsigned char TAC_Default[5]; /* TAC缺省data format (n 5) */
	unsigned char TAC_Denial[5]; /* TAC拒绝data format (n 5) */
	unsigned char TAC_Online[5]; /* TAC联机data format (n 5) */
	unsigned char abDDOL[20]; /* DDOL */
	unsigned char DDOL_Length; /* DDOL长度 */
	unsigned char abTDOL[20]; /* TDOL */
	unsigned char TDOL_Length; /* TDOL长度 */
	unsigned char abTrnCurrencyExp; /* tag: 5F36 */
	unsigned char abEC_TFL[6]; /* 终端电子现金交易限额tag: 9F7B n12*/
	unsigned char TerminalType; /* 终端类型data format (n 3) */
	unsigned char TerminalCap[3]; /* 终端能力data format (n 3) */
	unsigned char AddTerminalCap[5]; /* 终端附加性能data format (n 3) */
	unsigned char abRFOfflineLimit[6]; /*非接触脱机最低限额DF19*/
	unsigned char abRFTransLimit[6]; /*非接触交易限额DF20*/
	unsigned char abRFCVMLimit[6]; /*终端执行CVM限额DF21*/
	unsigned char abTransProp[4]; /*终端交易属性9F66*/
	unsigned char bStatusCheck; /*非接触状态检查,  0x00-不检查, 0x01-检查*/
	unsigned char abAcquirerID[6]; /*收单行标识9F01*/
}APPLICATIONPARAMS;

//EMV_AID参数总结构体
typedef struct
{
	unsigned char bTermAppCount;//实际AID参数个数
	APPLICATIONPARAMS *pTermAppList; //AID列表
}TERMINALAPPLIST;

//CA公钥结构体
typedef struct
{
	unsigned char RID[5]; /* Registered Application Provider Identifier */
	unsigned char CA_PKIndex; /* 认证中心公钥索引 */
	unsigned char CA_HashAlgoIndicator; /* 认证中心公钥哈什算法标识 */
	unsigned char CA_PKAlgoIndicator; /* 认证中心公钥算法标识 */
	unsigned char LengthOfCAPKModulus; /* 认证中心公钥模长度 */
	unsigned char CAPKModulus[248]; /* 认证中心公钥模 */
	unsigned char LengthOfCAPKExponent; /* 认证中心公钥指数长度 */
	unsigned char CAPKExponent[3]; /* 认证中心公钥指数 */
	unsigned char ChecksumHash[20]; /* 认证中心公钥校验值 */
	unsigned char CAPKExpDate[3]; /* 认证中心公钥有效期 */
}CAPUBLICKEY;

//EMV_AID参数总结构体
typedef struct
{
	unsigned char bTermCapkCount;//实际Capk参数个数
	CAPUBLICKEY *pTermCapkList;		 
}TERMINALCAPKLIST;

//EMV回调函数
typedef struct
{
	int (*EMV_InputPasswd)(char cType,unsigned short chance,char *pszPin);
	int (*EMV_InputAmount)(unsigned char *Amount);
}STEMVCALLBACKFUN;


//非接模式枚举
typedef enum
{
	EMV_RF_PBOC = 0, //非接PBOC
	EMV_RF_QPBOC = 1, //非接qPBOC
	//EMV_RF_MSD = 2 //非接MSD
	EMV_RF_PBOC_SINGLE  = 3      /**<非接PBOC简化流程*/
}EmvRFType;

//非接交易相关参数结构
typedef struct{
        unsigned long ulAmntAuth;      // 授权金额(ulong)
        unsigned long ulAmntOther;     // 其他金额(ulong)
        unsigned long ulTransNo;       // 交易序列计数器(4 BYTE)
        unsigned char ucTransType;      // 交易类型'9C'
        unsigned char aucTransDate[4];   // 交易日期 YYMMDD
        unsigned char aucTransTime[4];   // 交易时间 HHMMSS
        unsigned char aucReaderTTQ[4]; 	 // 非接交易属性
}Clss_TransParam;

//应用信息结构体
typedef struct
{
	char  szAID[32+1];		//AID
	char  szAppName[32+1];	//应用名
}STAPPINFO;


//回调函数结构体
typedef struct
{
    int (*EMV_InputPasswd)(char cType, unsigned short chance, char *pszPin);
    int (*EMV_InputAmount)(unsigned char *Amount);
    int (*EMV_cVerifyIDCard)(void);
    int (*EMV_cSelectAapp)(STAPPINFO *pstAPPList, int nAPPNum);
    int (*EMV_cqPBOCDodgeRefresh)(void *psCmdBuf);
    int (*EMV_cqPBOCDogeRemoveTrace)(void);
}STEMVCALLBACKFUN2;

typedef struct
{
	unsigned char KernType;
	unsigned char RidTab[6];
} EMVRIDTAB;

/**
 * @description: EMV终端参数始化
 * @param[in]: 	ptermconfig - 终端配置
 *				st_callbackfun - 回调函数结构体
 * @param[out]: none
 * @return: EMV_PRM_ERR  - EMV参数错
 *  		EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK   - EMV设置成功 
 */
int EMV_TermConfigInit(const TERMCONFIG *ptermconfig, STEMVCALLBACKFUN *st_callbackfun);

/**
 * @description: 获取内核版本
 * @param[in]: 	size - KernelVersion执行的buffer长度，建议至少64字节  
 * @param[out]: KernelVersion - libnpemv库的版本信息输出   
 * @return:	0-成功
 *      	其它-失败
 */
int EMV_GetKernelVersion(char *KernelVersion,int size);

/**
 * @description: 清除内核流水
 * @param[in]: none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - 失败
 *      	EMV_PRM_OK - 成功
 */
int EMV_ClrWater(void);

/**
 * @description: 根据TAG获取卡片数据, 从卡片中获取TAG值
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 *				tag - 数据tag
 * @param[out]: DataBuf - 输出数据指针
 *				Len - 输出数据长度
 * @return:	EMV_PRM_NOT_FOUND= - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_GetCardData(int iSlotType, int iCardType, char* Tag, unsigned char* DataBuf, int* Len);


/**
 * @description: 保存指定tag的数据, 保存到EMV内核
 * @param[in]:	Tag-tag值
 *				Len-数据长度
 *				Value-数据内容
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV参数错
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_StoreKernelData(const char *Tag, int Len, unsigned char *Value);

/**
 * @description: 搜索指定tag的数据, 从EMV内核中获取指定TAG值
 * @param[in]:	Tag - tag值
 * @param[out]: Len - Value数据长度
 *				Value - 取出的数据内容
 * @return:	EMV_PRM_ERR - EMV参数错
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_GetKernelData (const char *Tag, int *Len, unsigned char *Value);

/**
 * @description: 初始化参数结构体
 * @param[in]:	pstEmvParam - 参数结构体
 *				iNum - 需要初始化的结构体大小
 *				eParamType - 结构体类型
 * @param[out]: pstEmvParam - 参数结构体
 * @return:	EMV_PRM_ERR - EMV参数错
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_ParamInit(void *pstEmvParam,int iNum, EmvParamType eParamType);

/**
 * @description: 销毁参数结构体
 * @param[in]:	pstEmvParam - 参数结构体
 *				eParamType - 结构体类型
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV参数错
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_ParamDestroy(void *pstEmvParam,EmvParamType eParamType);

/**
 * @description: 保存AID参数
 * @param[in]:	pTerminalApps - AID参数数据指针
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV参数错
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmSetAIDPrm(TERMINALAPPLIST *pTerminalApps);

/**
 * @description: 获取AID参数
 * @param[in]:	pTerminalApps - AID参数数据指针
 *				iMaxAidNum - 接收AID缓冲大小
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND= - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmGetAIDPrm(TERMINALAPPLIST *pTerminalApps,int iMaxAidNum);

/**
 * @description: 删除AID参数
 * @param[in]:	AID - AID数据指针
 *				AID_Len- AID长度
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND= - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmDelAIDPrm(unsigned char *AID, unsigned char AID_Len);

/**
 * @description: 清空AID参数
 * @param[in]:	none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmClearAIDPrmFile(void);

/**
 * @description: 保存公钥
 * @param[in]:	ppkKey - 公钥结构指针
 * @param[out]: none
 * @return:	EMV_PRM_ERR	- 参数错
 *			EMV_PRM_CAPK_CHK_HASH_FAIL - 公钥HASH校验错误
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmSetCAPK(CAPUBLICKEY *ppkKey);

/**
 * @description: 根据RID和索引获取公钥
 * @param[in]:	RID - RID数据
 *				PKIndex - 公钥索引
 * @param[out]: ppkKey - 获取到的公钥
 * @return:	EMV_PRM_NOT_FOUND - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmGetCAPK(CAPUBLICKEY *ppkKey, unsigned char *RID, unsigned char PKIndex);

/**
 * @description: 获取本地公钥列表
 * @param[in]:	pstCapkKeys - 公钥列表结构体
 *				iMaxCapkNum - 接收CAPK缓冲大小
 * @param[out]: pstCapkKeys - 获取到的公钥列表
 * @return:	EMV_PRM_NOT_FOUND - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmGetCAPKList(TERMINALCAPKLIST *pstCapkKeys,int iMaxCapkNum);

/**
 * @description: 根据RID和索引删除公钥
 * @param[in]:	RID - RID数据
 *				PKIndex - 公钥索引
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND - EMV参数未找到
 *			EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmDelCAPK(unsigned char *RID, unsigned char PKIndex);

/**
 * @description: 清空公钥数据
 * @param[in]:	none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmClearCAPKFile(void);

/**
 * @description: 解析并设置公钥数据
 * @param[in]:	pCAPK - TLV数据 
 *				nLen - TLV数据长度
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmSetCAPKTLV(unsigned char *pCAPK, int nLen);

/**
 * @description: 根据RID获取公钥数据
 * @param[in]:	RID - RID数据
 *				PKIndex - 公钥索引
 * @param[out]: pCAPK - TLV数据 
 *				nLen - TLV数据长度
 * @return:	EMV_PRM_FAIL - EMV参数操作失败
 *			EMV_PRM_OK - EMV参数操作成功
 */
int EMV_PrmGetCAPKTLV(unsigned char *pCAPK, int *pnLen, unsigned char *RID, unsigned char PKIndex);

/**
 * @description: EMV/PBOC强制流程(联机后)
 *				 包含的处理流程：
 *				 联机处理、发卡行脚本处理、完成
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 *				bCommResult - 联机处理结果, 2联机批准,1联机拒
 *				usAuthResCode - 返回码域数据
 *				Field55Data - 接收到的IC卡域数据
 *				DataLen - 传入的Field55Data数据长度
 * @param[out]: Field55Data - 处理完的IC卡域数据
 *				DataLen - 传出的Field55Data数据长度
 *				pbMessage - 错误说明
 * @return:		EMV_SCRIPT_FAIL - 发卡行脚本执行失败
 *				EMV_ARPC_FAIL - 发卡行认证失败
 *				EMV_DECLINED - 卡片拒绝
 *				EMV_PARA_ERR - 入参数据错
 *				EMV_COMMAND_FAIL - 与卡片数据交互失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 其它失败
 *				EMV_OK - 执行成功
 * @adition:	处理联机数据(授权响应码、脚本等)
 *				入参Field55Data为解析出来的IC卡域数据, 不带长度
 *				入参Field55Data为处理完的IC卡域数据, 不带长度
 */
int EMV_ProcessFroceFlow(int iSlotType, int iCardType, unsigned char bCommResult, char *usAuthResCode, char *Field55Data, unsigned int * DataLen, unsigned char *pbMessage);

/**
 * @description: 获取卡片及终端共同支持的应用
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_APP_BLOCK - 应用已锁
 *				EMV_CANDIDATELIST_EMPTY - 无共同应用
 *				EMV_PARA_ERR - 参数错
 *				EMV_CARD_BLOCK - 卡片已锁
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 * @adition:	获取的应用列表由API自行维护
 */
int EMV_GetAppCandidate(int iSlotType, int iCardType);

/**
 * @description: 应用选择
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_APP_BLOCK - 应用已锁
 *				EMV_CANDIDATELIST_EMPTY - 无共同应用
 *				EMV_CARD_BLOCK - 卡片已锁
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_FAIL - 执行失败
 *				EMV_CANCEL - 取消
 *				EMV_OK - 执行成功
 */
int  EMV_SelectApp(int iSlotType, int iCardType);

/**
 * @description: 应用初始化, 调用GPO命令通知IC卡开始交易
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_APP_NOACCEPT - 应用不接受, 可重新选择
 *				EMV_FALLBACK - 交易fallback
 *				EMV_APP_BLOCK - 应用已锁
 *				EMV_PARA_ERR - 参数错
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_InitiateApp(int iSlotType, int iCardType,int iTraceNo);

/**
 * @description: 终端获取IC卡中包含的数据, 以完成交易中的各种功能。
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_ReadAppData(int iSlotType, int iCardType);

/**
 * @description: 脱机数据认证, 根据终端及卡片支持情况, 执行相应数据认证
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_AUTH_FAIL - 数据认证失败
 *				EMV_COMMAND_FAIL - 与卡片数据交互失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_DataAuth(int iSlotType, int iCardType);

/**
 * @description: 交易处理限制, 检查IC卡中的应用与终端中应用的兼容程度, 并做必须的调整。
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_OK - 执行成功
 */
int EMV_ProcRestrict(int iSlotType, int iCardType);

/**
 * @description: 终端风险管理
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_OK - 执行成功
 */
int  EMV_TermRiskManage(int iSlotType, int iCardType); 

/**
 * @description: 持卡人验证,将验证当前卡片的使用者是否是卡片中应用授权的人。
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_DECLINED - 交易拒绝
 *				EMV_CANCEL - 交易取消
 *				EMV_CVM_FAIL - 持卡人验证失败
 *				EMV_PARA_ERR - 参数错
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_VerfCardholder(int iSlotType, int iCardType);

/**
 * @description: 终端行为分析是终端将判断交易是否应该批准为脱机交易、拒绝脱机交易或转为联机交易。
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: none
 * @return:		EMV_DECLINED - 交易拒绝
 *				EMV_ONLINE - 交易应联机
 *				EMV_PARA_ERR - 参数错
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_TermAnalys(int iSlotType, int iCardType);

/**
 * @description: 获取电子现金余额。
 * @param[in]:	iSlotType - 参见enum SlotType
 *				iCardType - 参见enum IccType
 * @param[out]: Amount - 金额
 * @return:		EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 * @adition:	获取电子现金余额, 支持接触式、非接触式
 */
int EMV_GetECBalance(int iSlotType, int iCardType, unsigned long *Amount);

/**
 * @description: 非接触应用选择
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				pucKernType - 见内核类型
 * @param[out]: pucDtOut - 最终选择AID对应的RID
 *				pnDtLen - 返回RID长度
 * @return:		EMV_CANDIDATELIST_EMPTY - 应用列表为空
 *				EMV_CANCEL - 取消
 *				EMV_TIMEOUT - 超时
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_FAIL - 其它失败
 *				EMV_OK - 执行成功
 */
int EMV_RF_AppSlt(int iSlotType, int iCardType, unsigned char  *pucKernType, unsigned char *pucDtOut, int *pnDtLen);

/**
 * @description: 非接预处理
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				Clss_TransParam - 交易相关信息
 * @param[out]: none
 * @return:		EMV_OTHER_INTERFACE - 其他界面
 *				EMV_FAIL - 其它失败
 *				EMV_OK - 执行成功
 */
int EMV_RF_PreTransProc(int iSlotType, int iCardType, Clss_TransParam *ptTransParam);

/**
 * @description: 实现GPO及读应用数据（实现QPBOC的 GP0和Read Reord ，如果返回的是非接PBOC路径，也要实现GPO和Read Record）
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				Clss_TransParam - 交易相关信息
 * @param[out]: pucTransPath - 交易路径
 *				pucACType - 应用密文类型
 *				pucType - 持卡人认证方式
 * @return:		EMV_APP_NOACCEPT - 重新选择应用，应删除当前应用
 *				EMV_DECLINED - 交易拒绝
 *				EMV_CANCEL - 交易取消
 *				EMV_ONLINE - 交易应联机
 *				EMV_APP_EXPIRED - 应用已失效
 *				EMV_PARA_ERR - 参数错
 *				EMV_COMMAND_FAIL - 读卡失败
 *				EMV_CARD_REMOVED - 交易中卡片被移开
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 *				EMV_OTHER_INTERFACE - 终止非接触交易, 使用非接触界面方式执行交易。
 */
int EMV_RF_1stProctrans (int iSlotType, int iCardType, unsigned char *pucTransPath, unsigned char *pucACType, unsigned char *pucType);

/**
 * @description: 非接第二次授权，实现脱机数据认证
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 * @param[out]:	pucACType - 应用密文类型
 *				pucType - 持卡人认证方式
 * @return:		EMV_DECLINED - 交易拒绝
 *				EMV_CANCEL - 交易取消
 *				EMV_ONLINE - 交易应联机
 *				EMV_AUTH_FAIL - 数据认证失败
 *				EMV_PARA_ERR - 参数错
 *				EMV_FAIL - 执行失败
 *				EMV_OK - 执行成功
 */
int EMV_RF_2sdProctrans(int iSlotType, int iCardType, unsigned char *pucACType, unsigned char *pucType);

/**
 * @description: Emv内核回调函数设置
 * @param[in]:	pstEMVCALLBACKFUN  - EMV回调函数结构体
 * @param[out]:	none
 * @return:		EMV_PRM_ERR - EMV参数错
 *				EMV_PRM_FAIL - EMV参数操作失败
 *				EMV_PRM_OK - 成功
 */
int	EMV_SetCallbackFun(STEMVCALLBACKFUN2 *pstEMVCALLBACKFUN);

/**
 * @description: Emv参数设置 
 * @param[in]:	psParameter - 参数列表，TLV格式
 * @param[out]:	none
 * @return:		EMV_PRM_ERR - EMV参数错
 *				EMV_PRM_FAIL - EMV参数操作失败
 *				EMV_PRM_OK - 成功
 * @adition:	TLV，4字节TAG，2字节HEX长度LENGTH，长度字节的VALUE
 *              0001：是否强制联机，0x00-否，0x01-是
 *				0002：是否支持电子现金，0x00-否，0x01-是
 *				0003：是否允许选择被锁应用，0x00-否，0x01-是
 */
int	EMV_SetParameter(char *psParameter);

/**
 * @description: 获取非接错误码
 * @param[in]:	none
 * @param[out]:	pnErrorCode - 错误码
 * @return:		EMV_FAIL - EMV参数操作失败
 *				EMV_OK - 成功
 */
int EMV_RF_GetErrorCode(int *pnErrorCode);

/**
 * @description: 检查是否输PIN取消
 * @param[in]:	none
 * @param[out]:	none
 * @return:		1 - 是
 *				其他 - 否
 */
unsigned char EMV_ChkIsPwdCancel(void);

/**
 * @description: 检查是否存在AID
 * @param[in]:	none
 * @param[out]:	none
 * @return:		1 - 是
 *				其他 - 否
 */
int EMV_ChkAidNormal(void);

/**
 * @description: 检查是否存在CAPK
 * @param[in]:	none
 * @param[out]:	none
 * @return:		EMV_OK - 存在
 *				EMV_FAIL - 不存在
 */
int EMV_ChkCapkNormal(void);

/**
 * @description: 删除AID文件
 * @param[in]:	none
 * @param[out]:	none
 * @return:		0 - 成功
 *				其他 - 失败
 */
int EMV_RemoveEmvParamFile(void);

/**
 * @description: 删除CAPK文件
 * @param[in]:	none
 * @param[out]:	none
 * @return:		0 - 成功
 *				其他 - 失败
 */
int EMV_RemoveCapkFile(void);


/**
*@description:设置内核回调时的卡槽号
*@param[in]:iSlotType - enum SlotType
*
*/
void EMV_SetKernelExchangeApduSlot(int iSlotType);

/**
 * @description: 打开libnpemv日志
 * @param[in]:	on - 1:打开 0-关闭
 * @param[out]:	none
 * @return:		0 - 成功
 *				其他 - 失败
 */
int EMV_Logger_On(int on);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
