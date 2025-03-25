#ifndef __API_EMV_H__
#define __API_EMV_H__

#ifdef __cplusplus	
extern "C" {
#endif /* __cplusplus */

#include <emvapi.h>
#include <qpbocapi.h>

#define STR_PBOC_AID		"A000000333"

#define MIN_VERSION_LEN     64		// ��ȡ�汾��Ϣ��buffer���ٳ���

#define CLSS_VISA_QVSDC   2   // qPBOC��ʽ
#define CLSS_VISA_VSDC    3   // �����ǽ�PBOC��ʽ

#define AC_AAC       0x00
#define AC_TC        0x01
#define AC_ARQC      0x02

#define RD_CVM_NO            0x00	//no CVM
#define RD_CVM_SIG           0x10	//signature
#define RD_CVM_ONLINE_PIN    0x11	//online PIN

#define     YES                     0x01
#define     NO                      0x00

//�ں�����
#define KERNTYPE_DEF             0
#define KERNTYPE_JCB             1
#define KERNTYPE_MC              2
#define KERNTYPE_VIS             3
#define KERNTYPE_PBOC            4
#define KERNTYPE_AE              5
#define KERNTYPE_RFU             6

//EMV������������ö��
typedef enum
{
	EMV_PRM_ERR =-4, //EMV������
	EMV_PRM_NOT_FOUND=-3, //EMV����δ�ҵ�
	EMV_PRM_CAPK_CHK_HASH_FAIL=-2, //��ԿHASHУ�����
	EMV_PRM_FAIL=-1, //EMV��������ʧ��
	EMV_PRM_OK=0 //EMV���������ɹ�
} ParamStatus;

//EMV����״̬ö��
typedef enum
{ 
	EMV_TIMEOUT = -21,	   //EMV������ʱ
    EMV_QPBOC_DODGE = -20,       //��������ʧ�ܷ�������
	EMV_EC_DECLINED = -19, //�����ֽ��ѻ��ܾ�
	EMV_APP_NOACCEPT = -18, //Ӧ�ò�����, ������ѡ��
	EMV_SCRIPT_FAIL = -17, //�����нű�ִ��ʧ��
	EMV_ARPC_FAIL = -16, //��������֤ʧ��
	EMV_DECLINED = -15, //���׾ܾ�
	EMV_CANCEL = -14, //����ȡ��
	EMV_ONLINE = -13, //����Ӧ����
	EMV_CVM_FAIL = -12, //�ֿ�����֤ʧ��
	EMV_APP_EXPIRED = -11, //Ӧ����ʧЧ
	EMV_APP_EFFECT = -10, //Ӧ����δ��Ч
	EMV_AUTH_FAIL = -9, //������֤ʧ��
	EMV_FALLBACK = -8, //����fallback
	EMV_APP_BLOCK = -7, //Ӧ������
	EMV_CANDIDATELIST_EMPTY = -6, //�޹�ͬӦ��
	EMV_PARA_ERR = -5, //������
	EMV_CARD_BLOCK = -4, //��Ƭ����
	EMV_COMMAND_FAIL = -3, //����ʧ��
	EMV_CARD_REMOVED = -2, //�����п�Ƭ���ƿ�
	EMV_FAIL = -1, //ִ��ʧ��
	EMV_OK = 0, //ִ�гɹ�
	EMV_OTHER_INTERFACE = 1, //�볢������ͨ�Ž���
	EMV_QPBOC_OFFLINE = 2, //�ǽӴ�QPBOC�����ѻ�����
	EMV_QPBOC_ONLINE = 3, //�ǽӴ�QPBOC��������
	EMV_PBOC_ONLINE = 4, //�ǽӴ�PBOC��������
	//EMV_MSD_ONLINE = 5 //�ǽӴ�MSD��������
	EMV_EC_ACCEPT = 6, //�����ֽ��ѻ�����
	EMV_OFFLINE_ACCEPT = 7 //��׼�����ѻ�����
} EmvStatus;

//�ն˲����ṹ��
typedef struct { 
	char TermCap[3] ; /*�ն����� '9F33'*/
	char AdditionalTermCap[5] ; /*�ն˸�������*/
	char IFDSerialNum[9] ; /*IFD���к� '9F1E'*/
	char TermCountryCode[2] ; /*�ն˹��Ҵ��� '9F1A'*/
	char TermID[9] ; /*�ն˱�ʶ '9F1C'*/
	char TermType ; /*�ն����� '9F35'*/
	char TransCurrCode[2] ; /*���׻��� '5F2A'*/
	char TransCurrExp; /*���׻���ָ�� '5F36'*/
	//PSE Selection 
	char bPSE; /*�Ƿ�֧��ѡ��PSE 1*/
	char bCardHolderConfirm; /*�Ƿ�֧�ֳֿ���ȷ�� 1*/
	char bPreferedOrder; /*�Ƿ�֧����ѡ��ʾ 1*/
	char bPartialAID; /*�Ƿ�֧�ֲ���AIDƥ�� 1*/
	char bMultiLanguage; /*�Ƿ�֧�ֶ����� 0*/
	char bCommonCharset; /*�Ƿ�֧�ֹ����ַ��� 0*/
	//Data Authentication 
	char bIPKCValidtionCheck; /*�Ƿ��鷢���й�Կ��֤��Ч�� 1*/
	char bContainDefaultDDOL; /*�Ƿ����Ĭ��DDOL 1*/
	char bCAPKFailOperAction; /*CAPK��ȡ����ʱ�Ƿ���Ҫ����Ա��Ԥ 1*/
	char bCAPKChecksum; /*�Ƿ����CAPKУ�� 1*/
	//Cardholder Verification Method 
	char bBypassPIN; /*�Ƿ�֧������PIN���� (�������,����)*/
	char bGetDataForPINCounter; /*PIN���Լ������Ƿ�֧��GetData 1*/
	char bFailCVM; /*�Ƿ�֧�ִ����CVM(1����ΪYes)*/
	char bAmountBeforeCVM; /*CVMǰ�Ƿ���֪��� 1*/
	//Term Risk Management 
	char bLimitFloorCheck; /*�Ƿ��������޶��� 1*/
	char bRandomTransSelect; /*�Ƿ�����������ѡ�� 1*/
	char bValocityCheck; /*�Ƿ����Ƶ�ȼ�� 1*/
	char bTransLog; /*�Ƿ��¼������־ 1*/
	char bExceptionFile; /*�Ƿ�֧�ֿ�Ƭ������ 1*/
	char bTRMBaseOnAIP; /*�ն˷��չ����Ƿ����Ӧ�ý������� 1*/
	//Terminal Action Analysis 
	char bTerminalActionCodes; /*�Ƿ�֧���ն���Ϊ���� 1*/
	char bDefActCodesBefore1stGenAC; /*ȱʡ��Ϊ�����Ƿ�����FirstGenerateAC ?*/
	char bDefActCodesAfter1stGenAC; /*ȱʡ��Ϊ�����Ƿ����FirstGenerateAC ?*/
	//Completion Processing char bForceOnline; /*�Ƿ�����ǿ������ 1*/
	char bForceAccept; /*�Ƿ�����ǿ�ƽ��ܽ��� 1*/
	char bAdvices; /*�Ƿ�֧��֪ͨ 0*/
	char bIISVoiceReferal; /*�Ƿ�֧�ַ���������������ο� ?*/
	char bCardVoiceReferal; /*�Ƿ�֧�ַ���������������ο� ?*/
	char bBatchDataCapture; /*�Ƿ�֧�������ݲɼ�*/
	char bDefaultTDOL; /*�Ƿ���ȱʡTDOL*/
	//Exception Handling 
	char cEntryModeUsingMagStripe; /*IC�����϶�ֻ��ˢ��ʱPOSEntryModeֵ*/
	char bAccountSelect; /*�Ƿ�֧���˺�ѡ��*/
}TERMCONFIG;

typedef enum{
	EMV_PARAM_AID,
	EMV_PARAM_CAPK,
}EmvParamType;

//EMV_AID�����ṹ��
typedef struct
{
	unsigned char AID[16]; //AID
	unsigned char AID_Length; //AID����
	unsigned char bAppSelIndicator; //Ӧ��ѡ��ָʾ��
	unsigned char bTerminalPriority; //�ն����ȼ�
	/* Domestic */
	unsigned char bMaxTargetDomestic; /*ƫ�����ѡ������Ŀ��ٷ���*/
	unsigned char bTargetPercentageDomestic; /*���ѡ���Ŀ��ٷ���*/
	unsigned char abTFL_Domestic[4]; /* �ն�����޶� */
	unsigned char abThresholdValueDomestic[4]; /*ƫ�����ѡ�����ֵ*/
	/* International */
	unsigned char bMaxTargetPercentageInt; /*ƫ�����ѡ������Ŀ��ٷ���*/
	unsigned char bTargetPercentageInt; /*���ѡ���Ŀ��ٷ���*/
	unsigned char abTFL_International[4]; /* �ն�����޶� */
	unsigned char abThresholdValueInt[4]; /*ƫ�����ѡ�����ֵ*/
	unsigned char abTerminalApplVersion[4]; /* �ն�Ӧ�ð汾 */
	unsigned char abMerchantCategoryCode[2]; /* �̻�������tag: 9F15 */
	unsigned char bTransactionCategoryCode; /* ����������Europay only, tag: 9F53 */
	unsigned char abTrnCurrencyCode[2]; /* ���Ҵ���tag: 5F2A */
	unsigned char abTerminalCountryCode[2]; /* ���Ҵ����ն�tag: 9F1A */
	unsigned char TAC_Default[5]; /* TACȱʡdata format (n 5) */
	unsigned char TAC_Denial[5]; /* TAC�ܾ�data format (n 5) */
	unsigned char TAC_Online[5]; /* TAC����data format (n 5) */
	unsigned char abDDOL[20]; /* DDOL */
	unsigned char DDOL_Length; /* DDOL���� */
	unsigned char abTDOL[20]; /* TDOL */
	unsigned char TDOL_Length; /* TDOL���� */
	unsigned char abTrnCurrencyExp; /* tag: 5F36 */
	unsigned char abEC_TFL[6]; /* �ն˵����ֽ����޶�tag: 9F7B n12*/
	unsigned char TerminalType; /* �ն�����data format (n 3) */
	unsigned char TerminalCap[3]; /* �ն�����data format (n 3) */
	unsigned char AddTerminalCap[5]; /* �ն˸�������data format (n 3) */
	unsigned char abRFOfflineLimit[6]; /*�ǽӴ��ѻ�����޶�DF19*/
	unsigned char abRFTransLimit[6]; /*�ǽӴ������޶�DF20*/
	unsigned char abRFCVMLimit[6]; /*�ն�ִ��CVM�޶�DF21*/
	unsigned char abTransProp[4]; /*�ն˽�������9F66*/
	unsigned char bStatusCheck; /*�ǽӴ�״̬���,  0x00-�����, 0x01-���*/
	unsigned char abAcquirerID[6]; /*�յ��б�ʶ9F01*/
}APPLICATIONPARAMS;

//EMV_AID�����ܽṹ��
typedef struct
{
	unsigned char bTermAppCount;//ʵ��AID��������
	APPLICATIONPARAMS *pTermAppList; //AID�б�
}TERMINALAPPLIST;

//CA��Կ�ṹ��
typedef struct
{
	unsigned char RID[5]; /* Registered Application Provider Identifier */
	unsigned char CA_PKIndex; /* ��֤���Ĺ�Կ���� */
	unsigned char CA_HashAlgoIndicator; /* ��֤���Ĺ�Կ��ʲ�㷨��ʶ */
	unsigned char CA_PKAlgoIndicator; /* ��֤���Ĺ�Կ�㷨��ʶ */
	unsigned char LengthOfCAPKModulus; /* ��֤���Ĺ�Կģ���� */
	unsigned char CAPKModulus[248]; /* ��֤���Ĺ�Կģ */
	unsigned char LengthOfCAPKExponent; /* ��֤���Ĺ�Կָ������ */
	unsigned char CAPKExponent[3]; /* ��֤���Ĺ�Կָ�� */
	unsigned char ChecksumHash[20]; /* ��֤���Ĺ�ԿУ��ֵ */
	unsigned char CAPKExpDate[3]; /* ��֤���Ĺ�Կ��Ч�� */
}CAPUBLICKEY;

//EMV_AID�����ܽṹ��
typedef struct
{
	unsigned char bTermCapkCount;//ʵ��Capk��������
	CAPUBLICKEY *pTermCapkList;		 
}TERMINALCAPKLIST;

//EMV�ص�����
typedef struct
{
	int (*EMV_InputPasswd)(char cType,unsigned short chance,char *pszPin);
	int (*EMV_InputAmount)(unsigned char *Amount);
}STEMVCALLBACKFUN;


//�ǽ�ģʽö��
typedef enum
{
	EMV_RF_PBOC = 0, //�ǽ�PBOC
	EMV_RF_QPBOC = 1, //�ǽ�qPBOC
	//EMV_RF_MSD = 2 //�ǽ�MSD
	EMV_RF_PBOC_SINGLE  = 3      /**<�ǽ�PBOC������*/
}EmvRFType;

//�ǽӽ�����ز����ṹ
typedef struct{
        unsigned long ulAmntAuth;      // ��Ȩ���(ulong)
        unsigned long ulAmntOther;     // �������(ulong)
        unsigned long ulTransNo;       // �������м�����(4 BYTE)
        unsigned char ucTransType;      // ��������'9C'
        unsigned char aucTransDate[4];   // �������� YYMMDD
        unsigned char aucTransTime[4];   // ����ʱ�� HHMMSS
        unsigned char aucReaderTTQ[4]; 	 // �ǽӽ�������
}Clss_TransParam;

//Ӧ����Ϣ�ṹ��
typedef struct
{
	char  szAID[32+1];		//AID
	char  szAppName[32+1];	//Ӧ����
}STAPPINFO;


//�ص������ṹ��
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
 * @description: EMV�ն˲���ʼ��
 * @param[in]: 	ptermconfig - �ն�����
 *				st_callbackfun - �ص������ṹ��
 * @param[out]: none
 * @return: EMV_PRM_ERR  - EMV������
 *  		EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK   - EMV���óɹ� 
 */
int EMV_TermConfigInit(const TERMCONFIG *ptermconfig, STEMVCALLBACKFUN *st_callbackfun);

/**
 * @description: ��ȡ�ں˰汾
 * @param[in]: 	size - KernelVersionִ�е�buffer���ȣ���������64�ֽ�  
 * @param[out]: KernelVersion - libnpemv��İ汾��Ϣ���   
 * @return:	0-�ɹ�
 *      	����-ʧ��
 */
int EMV_GetKernelVersion(char *KernelVersion,int size);

/**
 * @description: ����ں���ˮ
 * @param[in]: none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - ʧ��
 *      	EMV_PRM_OK - �ɹ�
 */
int EMV_ClrWater(void);

/**
 * @description: ����TAG��ȡ��Ƭ����, �ӿ�Ƭ�л�ȡTAGֵ
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 *				tag - ����tag
 * @param[out]: DataBuf - �������ָ��
 *				Len - ������ݳ���
 * @return:	EMV_PRM_NOT_FOUND= - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_GetCardData(int iSlotType, int iCardType, char* Tag, unsigned char* DataBuf, int* Len);


/**
 * @description: ����ָ��tag������, ���浽EMV�ں�
 * @param[in]:	Tag-tagֵ
 *				Len-���ݳ���
 *				Value-��������
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV������
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_StoreKernelData(const char *Tag, int Len, unsigned char *Value);

/**
 * @description: ����ָ��tag������, ��EMV�ں��л�ȡָ��TAGֵ
 * @param[in]:	Tag - tagֵ
 * @param[out]: Len - Value���ݳ���
 *				Value - ȡ������������
 * @return:	EMV_PRM_ERR - EMV������
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_GetKernelData (const char *Tag, int *Len, unsigned char *Value);

/**
 * @description: ��ʼ�������ṹ��
 * @param[in]:	pstEmvParam - �����ṹ��
 *				iNum - ��Ҫ��ʼ���Ľṹ���С
 *				eParamType - �ṹ������
 * @param[out]: pstEmvParam - �����ṹ��
 * @return:	EMV_PRM_ERR - EMV������
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_ParamInit(void *pstEmvParam,int iNum, EmvParamType eParamType);

/**
 * @description: ���ٲ����ṹ��
 * @param[in]:	pstEmvParam - �����ṹ��
 *				eParamType - �ṹ������
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV������
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_ParamDestroy(void *pstEmvParam,EmvParamType eParamType);

/**
 * @description: ����AID����
 * @param[in]:	pTerminalApps - AID��������ָ��
 * @param[out]: none
 * @return:	EMV_PRM_ERR - EMV������
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmSetAIDPrm(TERMINALAPPLIST *pTerminalApps);

/**
 * @description: ��ȡAID����
 * @param[in]:	pTerminalApps - AID��������ָ��
 *				iMaxAidNum - ����AID�����С
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND= - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmGetAIDPrm(TERMINALAPPLIST *pTerminalApps,int iMaxAidNum);

/**
 * @description: ɾ��AID����
 * @param[in]:	AID - AID����ָ��
 *				AID_Len- AID����
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND= - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmDelAIDPrm(unsigned char *AID, unsigned char AID_Len);

/**
 * @description: ���AID����
 * @param[in]:	none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmClearAIDPrmFile(void);

/**
 * @description: ���湫Կ
 * @param[in]:	ppkKey - ��Կ�ṹָ��
 * @param[out]: none
 * @return:	EMV_PRM_ERR	- ������
 *			EMV_PRM_CAPK_CHK_HASH_FAIL - ��ԿHASHУ�����
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmSetCAPK(CAPUBLICKEY *ppkKey);

/**
 * @description: ����RID��������ȡ��Կ
 * @param[in]:	RID - RID����
 *				PKIndex - ��Կ����
 * @param[out]: ppkKey - ��ȡ���Ĺ�Կ
 * @return:	EMV_PRM_NOT_FOUND - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmGetCAPK(CAPUBLICKEY *ppkKey, unsigned char *RID, unsigned char PKIndex);

/**
 * @description: ��ȡ���ع�Կ�б�
 * @param[in]:	pstCapkKeys - ��Կ�б�ṹ��
 *				iMaxCapkNum - ����CAPK�����С
 * @param[out]: pstCapkKeys - ��ȡ���Ĺ�Կ�б�
 * @return:	EMV_PRM_NOT_FOUND - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmGetCAPKList(TERMINALCAPKLIST *pstCapkKeys,int iMaxCapkNum);

/**
 * @description: ����RID������ɾ����Կ
 * @param[in]:	RID - RID����
 *				PKIndex - ��Կ����
 * @param[out]: none
 * @return:	EMV_PRM_NOT_FOUND - EMV����δ�ҵ�
 *			EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmDelCAPK(unsigned char *RID, unsigned char PKIndex);

/**
 * @description: ��չ�Կ����
 * @param[in]:	none
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmClearCAPKFile(void);

/**
 * @description: ���������ù�Կ����
 * @param[in]:	pCAPK - TLV���� 
 *				nLen - TLV���ݳ���
 * @param[out]: none
 * @return:	EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmSetCAPKTLV(unsigned char *pCAPK, int nLen);

/**
 * @description: ����RID��ȡ��Կ����
 * @param[in]:	RID - RID����
 *				PKIndex - ��Կ����
 * @param[out]: pCAPK - TLV���� 
 *				nLen - TLV���ݳ���
 * @return:	EMV_PRM_FAIL - EMV��������ʧ��
 *			EMV_PRM_OK - EMV���������ɹ�
 */
int EMV_PrmGetCAPKTLV(unsigned char *pCAPK, int *pnLen, unsigned char *RID, unsigned char PKIndex);

/**
 * @description: EMV/PBOCǿ������(������)
 *				 �����Ĵ������̣�
 *				 �������������нű��������
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 *				bCommResult - ����������, 2������׼,1������
 *				usAuthResCode - ������������
 *				Field55Data - ���յ���IC��������
 *				DataLen - �����Field55Data���ݳ���
 * @param[out]: Field55Data - �������IC��������
 *				DataLen - ������Field55Data���ݳ���
 *				pbMessage - ����˵��
 * @return:		EMV_SCRIPT_FAIL - �����нű�ִ��ʧ��
 *				EMV_ARPC_FAIL - ��������֤ʧ��
 *				EMV_DECLINED - ��Ƭ�ܾ�
 *				EMV_PARA_ERR - ������ݴ�
 *				EMV_COMMAND_FAIL - �뿨Ƭ���ݽ���ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ����ʧ��
 *				EMV_OK - ִ�гɹ�
 * @adition:	������������(��Ȩ��Ӧ�롢�ű���)
 *				���Field55DataΪ����������IC��������, ��������
 *				���Field55DataΪ�������IC��������, ��������
 */
int EMV_ProcessFroceFlow(int iSlotType, int iCardType, unsigned char bCommResult, char *usAuthResCode, char *Field55Data, unsigned int * DataLen, unsigned char *pbMessage);

/**
 * @description: ��ȡ��Ƭ���ն˹�֧ͬ�ֵ�Ӧ��
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_APP_BLOCK - Ӧ������
 *				EMV_CANDIDATELIST_EMPTY - �޹�ͬӦ��
 *				EMV_PARA_ERR - ������
 *				EMV_CARD_BLOCK - ��Ƭ����
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 * @adition:	��ȡ��Ӧ���б���API����ά��
 */
int EMV_GetAppCandidate(int iSlotType, int iCardType);

/**
 * @description: Ӧ��ѡ��
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_APP_BLOCK - Ӧ������
 *				EMV_CANDIDATELIST_EMPTY - �޹�ͬӦ��
 *				EMV_CARD_BLOCK - ��Ƭ����
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_CANCEL - ȡ��
 *				EMV_OK - ִ�гɹ�
 */
int  EMV_SelectApp(int iSlotType, int iCardType);

/**
 * @description: Ӧ�ó�ʼ��, ����GPO����֪ͨIC����ʼ����
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_APP_NOACCEPT - Ӧ�ò�����, ������ѡ��
 *				EMV_FALLBACK - ����fallback
 *				EMV_APP_BLOCK - Ӧ������
 *				EMV_PARA_ERR - ������
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_InitiateApp(int iSlotType, int iCardType,int iTraceNo);

/**
 * @description: �ն˻�ȡIC���а���������, ����ɽ����еĸ��ֹ��ܡ�
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_ReadAppData(int iSlotType, int iCardType);

/**
 * @description: �ѻ�������֤, �����ն˼���Ƭ֧�����, ִ����Ӧ������֤
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_AUTH_FAIL - ������֤ʧ��
 *				EMV_COMMAND_FAIL - �뿨Ƭ���ݽ���ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_DataAuth(int iSlotType, int iCardType);

/**
 * @description: ���״�������, ���IC���е�Ӧ�����ն���Ӧ�õļ��ݳ̶�, ��������ĵ�����
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_OK - ִ�гɹ�
 */
int EMV_ProcRestrict(int iSlotType, int iCardType);

/**
 * @description: �ն˷��չ���
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_OK - ִ�гɹ�
 */
int  EMV_TermRiskManage(int iSlotType, int iCardType); 

/**
 * @description: �ֿ�����֤,����֤��ǰ��Ƭ��ʹ�����Ƿ��ǿ�Ƭ��Ӧ����Ȩ���ˡ�
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_DECLINED - ���׾ܾ�
 *				EMV_CANCEL - ����ȡ��
 *				EMV_CVM_FAIL - �ֿ�����֤ʧ��
 *				EMV_PARA_ERR - ������
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_VerfCardholder(int iSlotType, int iCardType);

/**
 * @description: �ն���Ϊ�������ն˽��жϽ����Ƿ�Ӧ����׼Ϊ�ѻ����ס��ܾ��ѻ����׻�תΪ�������ס�
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: none
 * @return:		EMV_DECLINED - ���׾ܾ�
 *				EMV_ONLINE - ����Ӧ����
 *				EMV_PARA_ERR - ������
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_TermAnalys(int iSlotType, int iCardType);

/**
 * @description: ��ȡ�����ֽ���
 * @param[in]:	iSlotType - �μ�enum SlotType
 *				iCardType - �μ�enum IccType
 * @param[out]: Amount - ���
 * @return:		EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 * @adition:	��ȡ�����ֽ����, ֧�ֽӴ�ʽ���ǽӴ�ʽ
 */
int EMV_GetECBalance(int iSlotType, int iCardType, unsigned long *Amount);

/**
 * @description: �ǽӴ�Ӧ��ѡ��
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				pucKernType - ���ں�����
 * @param[out]: pucDtOut - ����ѡ��AID��Ӧ��RID
 *				pnDtLen - ����RID����
 * @return:		EMV_CANDIDATELIST_EMPTY - Ӧ���б�Ϊ��
 *				EMV_CANCEL - ȡ��
 *				EMV_TIMEOUT - ��ʱ
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_FAIL - ����ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_RF_AppSlt(int iSlotType, int iCardType, unsigned char  *pucKernType, unsigned char *pucDtOut, int *pnDtLen);

/**
 * @description: �ǽ�Ԥ����
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				Clss_TransParam - ���������Ϣ
 * @param[out]: none
 * @return:		EMV_OTHER_INTERFACE - ��������
 *				EMV_FAIL - ����ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_RF_PreTransProc(int iSlotType, int iCardType, Clss_TransParam *ptTransParam);

/**
 * @description: ʵ��GPO����Ӧ�����ݣ�ʵ��QPBOC�� GP0��Read Reord ��������ص��Ƿǽ�PBOC·����ҲҪʵ��GPO��Read Record��
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 *				Clss_TransParam - ���������Ϣ
 * @param[out]: pucTransPath - ����·��
 *				pucACType - Ӧ����������
 *				pucType - �ֿ�����֤��ʽ
 * @return:		EMV_APP_NOACCEPT - ����ѡ��Ӧ�ã�Ӧɾ����ǰӦ��
 *				EMV_DECLINED - ���׾ܾ�
 *				EMV_CANCEL - ����ȡ��
 *				EMV_ONLINE - ����Ӧ����
 *				EMV_APP_EXPIRED - Ӧ����ʧЧ
 *				EMV_PARA_ERR - ������
 *				EMV_COMMAND_FAIL - ����ʧ��
 *				EMV_CARD_REMOVED - �����п�Ƭ���ƿ�
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 *				EMV_OTHER_INTERFACE - ��ֹ�ǽӴ�����, ʹ�÷ǽӴ����淽ʽִ�н��ס�
 */
int EMV_RF_1stProctrans (int iSlotType, int iCardType, unsigned char *pucTransPath, unsigned char *pucACType, unsigned char *pucType);

/**
 * @description: �ǽӵڶ�����Ȩ��ʵ���ѻ�������֤
 * @param[in]:	SlotType - enum SlotType
 * 				CardType - enum IccType
 * @param[out]:	pucACType - Ӧ����������
 *				pucType - �ֿ�����֤��ʽ
 * @return:		EMV_DECLINED - ���׾ܾ�
 *				EMV_CANCEL - ����ȡ��
 *				EMV_ONLINE - ����Ӧ����
 *				EMV_AUTH_FAIL - ������֤ʧ��
 *				EMV_PARA_ERR - ������
 *				EMV_FAIL - ִ��ʧ��
 *				EMV_OK - ִ�гɹ�
 */
int EMV_RF_2sdProctrans(int iSlotType, int iCardType, unsigned char *pucACType, unsigned char *pucType);

/**
 * @description: Emv�ں˻ص���������
 * @param[in]:	pstEMVCALLBACKFUN  - EMV�ص������ṹ��
 * @param[out]:	none
 * @return:		EMV_PRM_ERR - EMV������
 *				EMV_PRM_FAIL - EMV��������ʧ��
 *				EMV_PRM_OK - �ɹ�
 */
int	EMV_SetCallbackFun(STEMVCALLBACKFUN2 *pstEMVCALLBACKFUN);

/**
 * @description: Emv�������� 
 * @param[in]:	psParameter - �����б�TLV��ʽ
 * @param[out]:	none
 * @return:		EMV_PRM_ERR - EMV������
 *				EMV_PRM_FAIL - EMV��������ʧ��
 *				EMV_PRM_OK - �ɹ�
 * @adition:	TLV��4�ֽ�TAG��2�ֽ�HEX����LENGTH�������ֽڵ�VALUE
 *              0001���Ƿ�ǿ��������0x00-��0x01-��
 *				0002���Ƿ�֧�ֵ����ֽ�0x00-��0x01-��
 *				0003���Ƿ�����ѡ����Ӧ�ã�0x00-��0x01-��
 */
int	EMV_SetParameter(char *psParameter);

/**
 * @description: ��ȡ�ǽӴ�����
 * @param[in]:	none
 * @param[out]:	pnErrorCode - ������
 * @return:		EMV_FAIL - EMV��������ʧ��
 *				EMV_OK - �ɹ�
 */
int EMV_RF_GetErrorCode(int *pnErrorCode);

/**
 * @description: ����Ƿ���PINȡ��
 * @param[in]:	none
 * @param[out]:	none
 * @return:		1 - ��
 *				���� - ��
 */
unsigned char EMV_ChkIsPwdCancel(void);

/**
 * @description: ����Ƿ����AID
 * @param[in]:	none
 * @param[out]:	none
 * @return:		1 - ��
 *				���� - ��
 */
int EMV_ChkAidNormal(void);

/**
 * @description: ����Ƿ����CAPK
 * @param[in]:	none
 * @param[out]:	none
 * @return:		EMV_OK - ����
 *				EMV_FAIL - ������
 */
int EMV_ChkCapkNormal(void);

/**
 * @description: ɾ��AID�ļ�
 * @param[in]:	none
 * @param[out]:	none
 * @return:		0 - �ɹ�
 *				���� - ʧ��
 */
int EMV_RemoveEmvParamFile(void);

/**
 * @description: ɾ��CAPK�ļ�
 * @param[in]:	none
 * @param[out]:	none
 * @return:		0 - �ɹ�
 *				���� - ʧ��
 */
int EMV_RemoveCapkFile(void);


/**
*@description:�����ں˻ص�ʱ�Ŀ��ۺ�
*@param[in]:iSlotType - enum SlotType
*
*/
void EMV_SetKernelExchangeApduSlot(int iSlotType);

/**
 * @description: ��libnpemv��־
 * @param[in]:	on - 1:�� 0-�ر�
 * @param[out]:	none
 * @return:		0 - �ɹ�
 *				���� - ʧ��
 */
int EMV_Logger_On(int on);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
