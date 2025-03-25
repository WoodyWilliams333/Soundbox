
/**
@if Chinese
 * @brief    ��ģ���������� <strong>��������(GPRS)ģ��</strong> ��صĽӿ�
 * @author   Jezz
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * ����          | �汾          | ����            | ����
 * ------------- | ------------- | --------------- | ----
 * 2018/11/01    | 1.0.0         | Jezz            | �����ļ�
 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
@else 
 * @brief    This module is used to describe <strong>Wireless(GPRS)</strong> interfaces module
 * @author   Jezz
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2018/11/01    | 1.0.0         | Jezz            | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
@endif  
 */

/**
@if Chinese
 * @defgroup Wireless ��������
@else
 * @defgroup Wireless Wireless
@endif  
 * @{
 */

#ifndef __WNET_H__
#define __WNET_H__

#include <stdint.h>
#include <syscall.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* getsockopt/setsockopt optval types. */
#define OPT_DEVWNET                     1               /**<@if Chinese �����豸 	@else Wireless devices @endif*/
#define OPT_DEVETH                      2               /**<@if Chinese ��̫���豸 	@else Ethernet equipment @endif*/
#define OPT_DEVWIFI                     3               /**<@if Chinese WIFI�豸 	@else WIFI devices @endif*/
#define OPT_DEVMODEM                    4               /**<@if Chinese MODEM�豸 	@else MODEM devices  @endif*/

#define MN_MAX_IMSI_ARR_LEN             8               /**<@if Chinese SIM CARD IMSI ��󳤶� @else Maximum length of IMSI of SIM CARD @endif*/
#define MNSIM_ICCID_ID_NUM_LEN          10              /**<@if Chinese SIM CARD ID ��󳤶� 	@else Maximum length of SIM CARD ID @endif*/

#define RAT_AUTO 						0				/**<@if Chinese �Զ�����ģʽ @else auto network mode@endif*/
#define RAT_GSM_ONLY 					2				/**<@if Chinese 2G����ģʽ @else 2G network mode@endif*/
#define RAT_LTE_ONLY                    4				/**<@if Chinese 4G����ģʽ @else 4G network mode@endif*/
/**
@if Chinese
 * @brief SIM����Ϣö��
@else 
 * @brief Enumeration of SIM card information
@endif  
 */
typedef enum {
    SIM_STATE_E = 0,          /**<@if Chinese ��ȡSIM��״̬ 	@else Obtain the SIM card status @endif*/
    SIM_IMSI_E,               /**<@if Chinese ��ȡIMSI 			@else Get IMSI @endif*/
    SIM_CCID_E,               /**<@if Chinese ��ȡSIM��ID 		@else Obtain the SIM card ID @endif*/
    SIM_ALL,                  /**<@if Chinese ��ȡSIM��ȫ����Ϣ @else Obtain all SIM card information @endif*/
    SIM_MAX,                  /**<@if Chinese ���� 				@else keep @endif*/
} SIM_INFO_E;

/**
@if Chinese
 * @brief SIM��IMSI��Ϣ
@else  
 * @brief IMSI information of SIM card
@endif  
 */
typedef struct {
    BYTE imsi_len;               /**<@if Chinese IMSI��Ϣ���� 		@else Length of IMSI information @endif*/
    BYTE imsi_val[20];           /**<@if Chinese IMSI��Ϣ���� 		@else IMSI information @endif*/
} SIM_IMSI_T;

/**
@if Chinese
 * @brief SIM��ID��Ϣ
@else 
 * @brief ID of a SIM card
@endif  
 */
typedef struct {
    BYTE id_num[2 * MNSIM_ICCID_ID_NUM_LEN + 1];        /**<@if Chinese SIM CARD ID ��Ϣ @else SIM CARD ID information @endif*/
} SIM_ICCID_T;

/**
@if Chinese
 * @brief GPRS��վ��Ϣ
@else 
 * @brief GPRS base station information
@endif 
 */
typedef struct {
    int arfcn;                   /**<@if Chinese С��Ƶ��� 		@else Cell frequency number @endif*/
    int rxlev;                   /**<@if Chinese С�����չ��ʣ������仯 @else Cell receiving power, often changing @endif*/
    int bsic;                    /**<@if Chinese С����վ��  		@else Base station ID @endif*/
    int cell_id;                 /**<@if Chinese С����  			@else Base ID @endif*/
    int lac;                     /**<@if Chinese С��λ������ 		@else Location area code @endif*/
} tBaseStationGPRS;

/*!
 @if Chinese
	@brief CDMA��վ��Ϣ
 @else
	@brief CDMA Base Station information
 @endif
*/
typedef struct {                                                                                                                                                  
	int			BandClass;       /**< @if Chinese Ƶ������             @else  Absolute Radio Frequency Channel Number           @endif */ 
	int			Channel;		 /**< @if Chinese ͨ�����             @else  Received Signal Level                             @endif */ 
	int			SID;			 /**< @if Chinese system ID, ϵͳ���  @else  Base station ID                                   @endif */ 
	int			NID;			 /**< @if Chinese network ID, ������ @else  Base ID                                           @endif */ 
	int			BaseStationPRev; /**< @if Chinese ������ʩ             @else  location area code                                @endif */ 
	int			PilotPNoffset;	 /**< @if Chinese ��ǰ��С���ĵ�Ƶƫ�� @else  the pilot offset of the ME's current primary cell @endif */ 
	int			BaseStationID;	 /**< @if Chinese С����վ��           @else  Base station ID                                   @endif */ 
	int			SlotCycleIndex;	 /**< @if Chinese  ʱ϶����ָ��        @else  the solt cycle index                              @endif */ 
	int			RawEcIo;		 /**< @if Chinese  ��Ƶǿ��(��λ:DBm)  @else  the ME,s pilot strength in DBm                    @endif */ 
	int			RxPower;		 /**< @if Chinese ���չ���             @else  Reserved field, for extension                     @endif */ 
	int			TxPower;		 /**< @if Chinese ���͹���             @else  Reserved field, for extension                     @endif */ 
	int			TxAdj;			 /**< @if Chinese ���书�ʵ���         @else  the ME's transmitted power adjustment             @endif */ 
} tBaseStationCDMA; 

/**
@if Chinese
 * @brief ���������վ��Ϣ
@else 
 * @brief Wireless network base station information
@endif
 */
typedef struct {
    int iFlag;                  /**<@if Chinese ���� 1:GPRS, 2:CDMA @else Type 1: GPRS, 2: CDMA @endif*/
    tBaseStationGPRS oGprs;     /**<@if Chinese GPRS��վ��Ϣ 		@else GPRS base station information @endif*/
    tBaseStationCDMA oCdma;     /**<@if Chinese CDMA��վ��Ϣ 		@else CDMA base station information @endif*/
} tBaseStation;

/*!
 @if Chinese
	@brief GPRS��վ��Ϣ
 @else
	@brief GPRS Base Station information
 @endif
*/
typedef struct {                                                                                                             
	int	arfcn;	  /**< @if Chinese  С��Ƶ���             @else  Absolute Radio Frequency Channel Number @endif */  
	int	rxlev;	  /**< @if Chinese  С�����չ��ʣ������仯 @else  Received Signal Level                   @endif */  
	int	bsic;	  /**< @if Chinese  С����վ��             @else  Base station ID                         @endif */  
	int	cell_id;  /**< @if Chinese  С����                 @else  Base ID                                 @endif */  
	int	lac;	  /**< @if Chinese  С��λ������           @else  location area code                      @endif */  
	int	mnc;      /**< @if Chinese  �ƶ��������           @else  Mobile Network Code                     @endif */  
	int	mcc;      /**< @if Chinese  �ƶ�̨������           @else  Mobile Country Code                     @endif */  
	int	aiRev[5]; /**< @if Chinese  �����ֶΣ���չ��       @else  Reserved field, for extension           @endif */  
} tBaseStationGPRSExt;

/*!
 @if Chinese
	@brief WCDMA��վ��Ϣ
 @else
	@brief WCDMA Base Station information
 @endif
*/
typedef struct {                                                                                                                                               
	int	cell_id; /**< @if Chinese  С����                           @else  Base ID                                 @endif */                           
	int	lac;	 /**< @if Chinese  С��λ������                     @else  location area code                      @endif */                           
	int	mnc;     /**< @if Chinese  �ƶ��������                     @else  Mobile Network Code                     @endif */                           
	int	mcc;     /**< @if Chinese  �ƶ�̨������                     @else  Mobile Country Code                     @endif */                           
	int	uarfcn;	 /**< @if Chinese  UTRA��������Ƶ���ŵ���           @else  UTRA absolute radio frequency channel number   @endif */                    
	int	psc;	 /**< @if Chinese  ������                           @else  Primary Scrambling Code                       @endif */                     
	int	rscp;	 /**< @if Chinese  �����ź��빦��                   @else  Received Signal Code Power                    @endif */                     
	int	ecno;	 /**< @if Chinese  ÿ�����Ʊ��ص���������������֮�� @else  Ratio of energy per modulating bit to the noise spectral density @endif */  
} tBaseStationWCDMA; 

/*!
 @if Chinese
	@brief LTE��վ��Ϣ
 @else
	@brief LTE Base Station information
 @endif
*/
typedef struct {
	int			mcc;      /**< @if Chinese  �ƶ�̨������                     @else  Mobile Country Code                     @endif */ 
	int			mnc;	  /**< @if Chinese  �ƶ��������                     @else  Mobile Network Code                     @endif */
	int			cell_id;  /**< @if Chinese  С����                           @else  Base ID                                 @endif */ 
	int			pci;      /**< @if Chinese  ����С����ʶ                     @else  Physical Cell Identifier                @endif */ 
	int			earfcn;	  /**< @if Chinese  Ƶ���                           @else  the E-UTRA-ARFCN of the cell            @endif */
	int			tac;	  /**< @if Chinese  ����������                       @else  Tracking Area Code                      @endif */
	int			rsrp;	  /**< @if Chinese  �ο��źŽ��չ���                 @else  Reference Signal Receiving Power        @endif */
	int			rsrq;	  /**< @if Chinese  �ο��źŽ�������                 @else  Reference Signal Receiving Quality      @endif */
	int			rxlev;	  /**< @if Chinese  С�����չ��ʣ������仯           @else  Received Signal Level                   @endif */
} tBaseStationLTE;

/*!
 @if Chinese
	@brief ���������վ��Ϣ
 @else
	@brief Wireless network Base Station information
 @endif
*/
typedef struct {
	int			iFlag;	            /**< 0:NONE, 1:GPRS, 2:CDMA, 3:WCDMA,  4:LTE */
	union {
		tBaseStationGPRSExt	oGprs; /**< @if Chinese GPRS��վ��Ϣ  @else GPRS Base Station information @endif */ 
		tBaseStationCDMA	oCdma; /**< @if Chinese CDMA��վ��Ϣ  @else CDMA Base Station information @endif */
        tBaseStationWCDMA   oWcdma;/**< @if Chinese WCDMA��վ��Ϣ @else WCDMA Base Station information @endif */
		tBaseStationLTE     oLte;  /**< @if Chinese LTE��վ��Ϣ   @else LTE Base Station information @endif */
	} Wnet;
} tBaseStationExt;

/*!
 @if Chinese
	@brief MT���������ź�ǿ�ȵķ���ģʽ
 @else
	@brief Service mode in which the MT will unsolicitedly report the signal strength
 @endif
*/
typedef enum {
    Mode_NON = 0,   /**< @if Chinese �޷���ģʽ            @else NO SERVICE mode        @endif */
    Mode_GSM,       /**< @if Chinese GSM/GPRS/EDGEģʽ     @else GSM/GPRS/EDGE mode     @endif */
    Mode_WCDMA,     /**< @if Chinese WCDMA/HSDPA/HSPAģʽ  @else WCDMA/HSDPA/HSPA mode  @endif */
    Mode_TDSCDMA,   /**< @if Chinese TDSCDMAģʽ           @else TDSCDMA mode           @endif */
    Mode_LTE,       /**< @if Chinese LTEģʽ               @else LTE mode               @endif */
    Mode_CDMA,      /**< @if Chinese CDMAģʽ              @else CDMA mode              @endif */
    Mode_EVDO,      /**< @if Chinese EV-DO/eHRPDģʽ       @else EV-DO/eHRPD mode       @endif */
    Mode_CDMAEVDO,  /**< @if Chinese CDMA/EV-DO(eHRPD)ģʽ @else CDMA/EV-DO(eHRPD) mode @endif */
}wnetMode_t;

/*!
 @if Chinese
	@brief GSM/GPRS/EDGEģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in GSM/GPRS/EDGE mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator @endif */
    int         reserve[7];
} GsmSigStr_t;

/*!
 @if Chinese
	@brief WCDMA/HSDPA/HSPAģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in WCDMA/HSDPA/HSPA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator  @endif */
    int         rscp;      /**< @if Chinese �����ź��빦��     @else Receive Signal Channel Power        @endif */
    int         ecio;      /**< @if Chinese ��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io @endif */
    int         reserve[5];
} WcdmaSigStr_t;

/*!
 @if Chinese
	@brief TDSCDMAģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in TDSCDMA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator  @endif */
    int         rscp;      /**< @if Chinese �����ź��빦��     @else Receive Signal Channel Power        @endif */
    int         ecio;      /**< @if Chinese ��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io @endif */
    int         reserve[5];
} TdscdmaSigStr_t;

/*!
 @if Chinese
	@brief LTEģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in LTE mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator @endif */
    int         rsrp;      /**< @if Chinese �ο��źŽ��չ���   @else Reference Signal Receiving Power   @endif */
    int         sinr;      /**< @if Chinese �Ÿ����           @else Signal to Interference Noise Ratio @endif */
    int         rsrq;      /**< @if Chinese �ο��źŽ�������   @else Reference Signal Received Quality  @endif */
    int         reserve[4];
} LteSigStr_t;

/*!
 @if Chinese
	@brief CDMAģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in CDMA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator  @endif */
    int         ecio;      /**< @if Chinese ��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io @endif */
    int         reserve[6];
} CdmaSigStr_t;

/*!
 @if Chinese
	@brief EV-DO/eHRPDģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in EV-DO/eHRPD mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator  @endif */
    int         ecio;      /**< @if Chinese ��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io @endif */
    int         sinr;      /**< @if Chinese �Ÿ����           @else Signal to Interference Noise Ratio  @endif */
    int         reserve[5];
} EvdoSigStr_t;

/*!
 @if Chinese
	@brief CDMA/EV-DO(eHRPD)ģʽ�µ��ź�ǿ��
 @else
	@brief Signal strength in CDMA/EV-DO(eHRPD) mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese �����ź�ǿ��ָʾ   @else Received Signal Strength Indicator              @endif */
    int         cdma_ecio; /**< @if Chinese cdma��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io of cdma @endif */
    int         evdo_ecio; /**< @if Chinese evdo��Ƭ�������������Ƶ���ܶȣ��źż��������ı�ֵ   @else Ec/Io of evdo @endif */
    int         evdo_sinr; /**< @if Chinese �Ÿ����           @else Signal to Interference Noise Ratio              @endif */
    int         reserve[4];
} CdmaEvdoSigStr_t;

/* the signal strength of current service network */
/*!
 @if Chinese
	@brief ��ǰ����������ź�ǿ��
 @else
	@brief the signal strength of current service network
 @endif
*/
typedef struct signal_strength {
    wnetMode_t  mode;                 /**< @if Chinese ����ģʽ @see wnetMode_t  @else Service mode @see wnetMode_t @endif */ 
    union {
        GsmSigStr_t      sGsm;        /**< @if Chinese GSM/GPRS/EDGEģʽ�µ��ź�ǿ��     @else Signal strength in GSM/GPRS/EDGE mode     @endif */
        WcdmaSigStr_t    sWcdma;      /**< @if Chinese WCDMA/HSDPA/HSPAģʽ�µ��ź�ǿ��  @else Signal strength in WCDMA/HSDPA/HSPA mode  @endif */
        TdscdmaSigStr_t  sTdscdma;    /**< @if Chinese TDSCDMAģʽ�µ��ź�ǿ��           @else Signal strength in TDSCDMA mode           @endif */
        LteSigStr_t      sLte;        /**< @if Chinese LTEģʽ�µ��ź�ǿ��               @else Signal strength in LTE mode               @endif */
        CdmaSigStr_t     sCdma;       /**< @if Chinese CDMAģʽ�µ��ź�ǿ��              @else Signal strength in CDMA mode              @endif */
        EvdoSigStr_t     sEvdo;       /**< @if Chinese EV-DO/eHRPDģʽ�µ��ź�ǿ��       @else Signal strength in EV-DO/eHRPD mode       @endif */
        CdmaEvdoSigStr_t sCdmaEvdo;   /**< @if Chinese CDMA/EV-DO(eHRPD)ģʽ�µ��ź�ǿ�� @else Signal strength in CDMA/EV-DO(eHRPD) mode @endif */
    }wss; 
} WnetSigStr_t;

/**
@if Chinese
 * @brief ��������PLMN״̬��Ϣ
@else 
 * @brief PLMN status of the wireless network
@endif  
 */
typedef enum {
    PLMN_NO_SERVICE = 0,                                /**<@if Chinese û�з��� @else no service @endif*/
    PLMN_NORMAL_GSM_ONLY = 0x01,                        /**<@if Chinese �������� @else voice service available @endif*/
    PLMN_NORMAL_GPRS_ONLY = 0x02,                       /**<@if Chinese ���ݷ������ @else data service available @endif*/
    PLMN_NORMAL_GSM_GPRS_BOTH = 0x03,                   /**<@if Chinese �ṩ���������ݷ��� @else voice and data service available @endif*/

    PLMN_NORMAL_CS_ONLY = 0x01,                         /**<@if Chinese �������� @else voice service available @endif*/
    PLMN_NORMAL_PS_ONLY = 0x02,                         /**<@if Chinese ���ݷ������ @else data service availabe @endif*/
    PLMN_NORMAL_CS_PS_BOTH = 0x03,                      /**<@if Chinese �ṩ���������ݷ��� @else voice and data service available @endif*/
    PLMN_EMERGENCY_ONLY = 0x04,                         /**<@if Chinese �������� @else emergency service available @endif*/
    PLMN_EMERGENCY_SIM_INVALID = 0x05,                  /**<@if Chinese �������;MM�������޷���״̬�Ͳ�������н�һ����PLMN����,ֱ���������µ�SIM������ @else emergency; MM in limited service state and
                                                             no further PLMN access allowed until power
                                                             off or new SIM inserted @endif*/
    PLMN_EMERGENCY_GPRS_ONLY = 0x06,                    /**<@if Chinese �ڽ���������ṩ���ݷ���; MM�����޵ķ���״̬ @else data service availabe but emergency;
                                                             MM in limited service state @endif*/
    PLMN_EMERGENCY_SIM_INVALID_GPRS_ONLY = 0x07,        /**<@if Chinese �ڽ���������ṩ���ݷ���;����PLMN���ʣ�ֱ���µ����SIM������ @else data service availabe but emergency;
                                                             MM in limited service state and no further
                                                             PLMN access allowed until power off or new SIM inserted @endif*/

    PLMN_REGISTER_SERVICE = 0x08,                       /**<@if Chinese Register ���� @else attaching after camping on @endif*/
    PLMN_REGISTER_GPRS_ONLY = 0x09,                     /**<@if Chinese ���ݷ�����ã����������� @else data service availabe but attaching @endif*/
    PLMN_FULL_PS_SERVICE = 0x0A                         /**<@if Chinese ȫPS������cs���� @else full PS service, no cs service @endif*/

} GPRS_PLMN_STATUS_E;

/**
@if Chinese
 * @brief �������總��״̬��Ϣ
@else 
 * @brief Wireless network attachment status information
@endif  
 */
typedef enum {
    MN_INVALID_STATE,                                   /**<@if Chinese ���ֶ���Ч @else this field is invalid @endif*/
    MN_ATTACHED_STATE,                                  /**<@if Chinese Cs��ps�Ѹ��� @else cs or ps has been attached @endif*/
    MN_DETACHED_SATE,                                   /**<@if Chinese Cs��ps�ѷ��� @else cs or ps has been detached @endif*/
    MN_NO_SERVICE                                       /**<@if Chinese Cs��psû�з��� @else no service for cs or ps @endif*/
} GPRS_ATTACH_STATE_E;

/**
@if Chinese
 * @brief ��������״̬��Ϣ
 @else 
 * @brief Wireless network status information
@endif  
 */
typedef struct {
    GPRS_PLMN_STATUS_E      plmn_status;                /**<@if Chinese plmn״̬ @else plmn statue @endif*/
    BOOL                    plmn_is_roaming;            /**<@if Chinese PLMN������״̬ PLMN @else if plmn is roaming plmn @endif*/
    WORD                    mcc;                        /**<@if Chinese �ƶ�̨������ @else MCC: mobile country code @endif*/
    WORD                    mnc;                        /**<@if Chinese �ƶ�������� @else MNC: mobile network code @endif*/
    WORD                    mnc_digit_num;              /**<@if Chinese MNCλ�� @else MNC digit number @endif*/
    WORD                    lac;                        /**<@if Chinese С��λ������ @else Location area code @endif*/
    WORD                    cell_id;                    /**<@if Chinese С���� @else  Base ID @endif*/
} GPRS_NETWORK_STATUS_T;

/**
@if Chinese
 * @brief PDP�����GPRS��Ϣ
@else  
 * @brief GPRS information after PDP activation
@endif 
 */
typedef struct {
    uint32_t ipaddr;            /**<@if Chinese IP��ַ 				@else IP address @endif*/
    uint32_t pri_dns;           /**<@if Chinese DNS������ 			@else Primary  @endif*/
    uint32_t sec_dns;           /**<@if Chinese DNS������ 			@else Secondary  @endif*/
    uint8_t  nsapi[4];          /**<@if Chinese ������������ʶ�� @else Network service Access Point identifier @endif*/
} PDP_GPRS_INFO;

/**
@if Chinese
* @brief  ��ʼ��ģ��
* @param[in]  TimeoutMs	
*          - >0		-	��ʼ��Ѱ��ģ���ʱ�䣨��λ�����룩
*          - <=0	-	һֱ�ȴ�Ѱ��ģ�����
* @return
*          - 0	-	�ɹ�
*          - <0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else
* @brief  init wnet module
* @param[in]  TimeoutMs	
*          - >0		-	Time to initialize the search module in milliseconds
*          - <=0	-	Wait for the search module to complete
* @return
*          - 0	-	Success
*          - <0	-	Fail��Returns the corresponding return value
@endif 
*/
int wnet_init(int TimeoutMs);

/**
@if Chinese
* @brief  ��ģ����и�λ
* @return
*          - 0	-	�ɹ�
*          - <0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else
* @brief  Reset wnet
* @return
*          - 0	-	Success
*          - <0	-	Fail��Returns the corresponding return value
@endif
*/
int wnet_reset(void);

/**
@if Chinese
* @brief  ѡ������ģ�������ͨ����slot0����slot1
* @param[in]  slotNo	-	ѡ��ͨ��	
*          - 0	-	ѡ��slot0ͨ����Ĭ�ϣ�
*          - 1	-	ѡ��slot1ͨ�����������˵ڶ���ģ��������ʹ�ã�
* @return int
*          - 0	-	��һ��ʹ��ͨ��0
*          - 1	-	��һ��ʹ��ͨ��1
*          - <0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else
* @brief  Select the channel that the wireless module operates on��slot0 or slot1
* @param[in]  slotNo	-	selector channel		
*          - 0	-	Select SLOt0 channel (default)
*          - 1	-	Select the SLOT1 channel (used when a second module is configured)
* @return int
*          - 0	-	Channel 0 was used last time
*          - 1	-	Channel 1 was used last time
*          - <0	-	Fail��Returns the corresponding return value
@endif 
*/
int wnet_select_module(int slotNo);

/**
@if Chinese
* @brief  ����PPP��·
* @param[in]  devtype   -	����(��Ĭ��:OPT_DEVWNET)
* @param[in]  apn       -	�������ӵĽ��������,���Ȳ��ܳ���99���ַ�
* @param[in]  name      -	��֤ʱ������û��������Ȳ��ܳ���64���ַ�
* @param[in]  passwd    -	��֤ʱ��������룬���Ȳ��ܳ���64���ַ�
* @param[in]  auth      -	����
* @param[in]  timeout	-	ppp��½�ĳ�ʱʱ�䣬��λΪ����
* @return  int
*          - 0	-	��ʾ�ɹ�
*          - <0	-	��ʾʧ��
@else
* @brief  Login PPP Links
* @param[in]  devtype   -	Ignore (default :OPT_DEVWNET)
* @param[in]  apn       -	Name of the wireless connection access point
* @param[in]  name      -	The user name required for authentication cannot exceed 99 characters
* @param[in]  passwd    -	The password must contain a maximum of 99 characters
* @param[in]  auth      -	Passed
* @param[in]  timeout	-	PPP login timeout, in milliseconds
* @return  int
*          - 0	-	Success
*          - <0	-	Fail
@endif 
*/
int wnet_PPP_login(int devtype, const char *apn, const char *name,
                   const char *passwd, const uint32_t auth, int timeout);

/**
@if Chinese
* @brief  �ر�PPP��·
* @param[in]  devtype	-	����(��Ĭ��:OPT_DEVWNET)
* @return
*          - 0	-	�ɹ�<br>
*          - <0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else
* @brief  Close PPP Links
* @param[in]  devtype	-	Ignore (default :OPT_DEVWNET)
* @return
*          - 0	-	Success<br>
*          - <0	-	Fail
@endif 
*/
int wnet_PPP_logout(int devtype);

/**
@if Chinese
* @brief  ���PPP��·���
* @param[in]  devtype	-	����(��Ĭ��:0)
* @return
*          - 0	-	��ʾ��·�ѳɹ�������<br>
*          - <0	-	��ʾ��·����ʧ�ܻ���·û�����ã����߱�ʾ�����У�
@else
* @brief  Check PPP links
* @param[in]  devtype	-	Ignore (default :0)
* @return
*          - 0	-	Indicates that the link is successfully established��<br>
*          - <0	-	Indicates that the link fails to be established or the link is disabled.Or in process;
@endif
*/
int wnet_PPP_check(int devtype);

/**
@if Chinese
* @brief  ��ȡ��վ��Ϣ
* @param[out]  psBaseStationInfo	-	��վ��Ϣ
* @return ����0��ʾ�ɹ���������ʾʧ��
@else
* @brief  Get base station information
* @param[out]  psBaseStationInfo -	station information
* @return
*          - 0	-	Success<br>
*          - <0	-	Fail
@endif 
*/
int wnet_get_base_station_info(tBaseStation *psBaseStationInfo);

/**
@if Chinese
* @brief  ��ȡ��վ��Ϣ
* @param[out]  psBaseStationInfo-	��վ��Ϣ
* @return ����RET_OK��ʾ�ɹ���������ʾʧ��
@else
* @brief  Get base station information
* @param[out]  psBaseStationInfo-	station information
* @return
*          - 0	-	Success
*          - <0	-	Fail
@endif
*/
int wnet_get_base_station_info_ex(tBaseStationExt *psBaseStationInfo);

/**
@if Chinese
* @brief  ��ȡ���ڻ�վ��Ϣ
* @param[out]   psBaseStationInfo   -	������ڻ�վ��Ϣ�Ľṹ���飬����6����
* @param[in]    iNum                -	��վ��Ϣ�ṹ��������С6
* @param[out]   piOutNum            -	��ѯ�������ڻ�վ��Ϣ�ĸ���
* @return ����0��ʾ�ɹ���������ʾʧ��
@else
* @brief  Get adjacent base station information
* @param[out]   psBaseStationInfo   -	An array of structures containing information about adjacent base stations, at least 6
* @param[in]    iNum                -	Number of base station information structures, minimum 6
* @param[out]   piOutNum            -	Indicates the number of adjacent base stations to be queried
* @return
*          - 0	-	Success
*          - <0	-	Fail
@endif 
*/
int wnet_get_neighbour_base_station_info(tBaseStationExt *psBaseStationInfo, int iNum, int *piOutNum);

/**
@if Chinese
* @brief  ��ȡGPRSģ���IMEI��
* @param[out]  IMEI	-	���IMEI�ţ���'\0'���ַ�����ʽ����Ҫ��ռ䲻����16�ֽ�
* @param[in]   len	-	����IMEI�������Ч����
* @return
*          - 0	-	�ɹ�
*          - <0	-	ʧ�ܣ�������Ӧ�ķ���ֵ
@else
* @brief  Read the IMEI of the GPRS module
* @param[out]  IMEI	-	Output the IMEI (as a string with '\0'), requiring at least 16 bytes of space
* @param[in]   len	-	Pass in the effective length of the IMEI array
* @return
*          - 0	-	Success
*          - <0	-	Fail��Returns the corresponding return value
@endif 
*/
int wnet_get_IMEI(char *IMEI, int len);

/**
@if Chinese
* @brief  ��ȡSIM��ID
* @param[out]   psSimCardID     -	�洢Sim Card ID ��Ϣ(��'\0'���ַ�����ʽ)
* @param[in]    iLen            -	psSimCardID���峤��
* @return ����0��ʾ�ɹ���������ʾʧ��
* @note   ע��: psSimCardID���ص�ʵ���ַ���������iLen�Ĵ�ֵ�йأ�һ��sim card id����Ϊ20�ֽڣ�iLen�Ľ���ֵΪ>=21�ֽ�
* ����: ��ʵsim card idΪ "01234567890123456789"
* �������iLenС��0�����1���ֽڣ������ᱨ����������һ���ֽڴ洢'\0'
* �������2���ֽڣ���ʵ�ʷ���psSimCardID="0\0"
* �������4���ֽڣ���ʵ�ʷ���psSimCardID="012\0"
* �������5���ֽڣ���ʵ�ʷ���psSimCardID="0123\0"
* �������10���ֽڣ���ʵ�ʷ���psSimCardID="012345678\0"
* �������20���ֽڣ���ʵ�ʷ���psSimCardID="0123456789012345678\0"
* �������21���ֽڣ���ʵ�ʷ���psSimCardID="01234567890123456789\0"
* �������25���ֽڣ���ʵ�ʷ���psSimCardID="01234567890123456789\0"
@else
* @brief  Get the SIM card ID
* @param[out]   psSimCardID     -	Store Sim Card ID information (string with '\0')
* @param[in]    iLen            -	The length of the buffer
* @return
*          - 0	-	Success
*          - <0	-	Fail��Returns the corresponding return value
* @note   Note that the actual string content returned by psSimCardID is related to the iLen pass;Generally, the LENGTH of sim card ID is 20 bytes. The recommended value for iLen is >.= 21 bytes
@endif
*/
int wnet_read_sim_card_id(char *psSimCardID, int iLen);

/**
@if Chinese
* @brief  ��ȡSIM��IMSI
* @param[out]   IMSI           -	�洢Sim Card IMSI ��Ϣ����'\0'���ַ�����ʽ����Ҫ��ռ䲻����16�ֽ�
* @param[in]    len            -	����IMSI�������Ч����
* @return ����0��ʾ�ɹ���������ʾʧ��
@else
* @brief  Get the IMSI of the SIM card
* @param[out]   IMSI	-	Store Sim Card IMSI information (in the form of a string with '\0'). The space required is not less than 16 bytes
* @param[in]    len		-	The effective length of the IMSI array passed in
* @return 	0:Succes��other:Fail
@endif 
*/
int wnet_get_sim_card_IMSI(char *IMSI, int len);

/**
@if Chinese
 * @brief ���SIM��״̬
 * @return 0: ���� ����: ������
 @else
 * @brief check the state of SIM card
 * @return 
 * 			- 0		-	exist
 *			- other	-	not exist
 @endif
 **/
int wnet_check_sim(void);

/**
@if Chinese
* @brief  ����ִ��gprs��������
* @return
*          - 0	-	�ɹ�
*          - -1	-	ʧ��
@else
* @brief  Function to perform a GPRS network attachment request
* @return
*          - 0	-	Success
*          - -1	-	Fail
@endif
*/
int wnet_gprs_attach(void);

/**
@if Chinese
* @brief  �ú���ִ��gprs��������
* @return
*          - 0	-	�ɹ�
*          - -1	-	ʧ��
@else
* @brief  This function performs the GPRS separation request
* @return
*          - 0	-	Success
*          - -1	-	Fail
@endif 
*/
int wnet_gprs_detach(void);

#if 0 //ɾ���˽ӿ�
/**
* @brief  �ù��ܻ�ȡSIM����Ϣ������IMSI,CCID
* @param[in]    flag ����(��Ĭ��:SIM_ALL)
* @param[out]   imsi_str ��ȡIMSI��Ϣ
* @param[out]   ccid ��ȡCCID��Ϣ
* @return
*          - 1 �ɹ�
*          - 0 ʧ��
*/
int wnet_get_sim_info(SIM_INFO_E flag, SIM_IMSI_T *imsi_str, SIM_ICCID_T *ccid);
#endif

/**
@if Chinese
* @brief  G��ȡ��ǰ����״̬
* @param[out]  pstatus -	�ṹ�� GPRS_NETWORK_STATUS_T ��������״̬��Ϣ
* @return
*          - 0	-	�ɹ�
*          - -1	-	ʧ��
@else
* @brief  Gets the current network status
* @param[out]  pstatus -	The GPRS_NETWORK_STATUS_T structure contains network status information
* @return
*          - 0 	-	Success
*          - -1	-	Fail
@endif 
*/
int wnet_get_network_state(GPRS_NETWORK_STATUS_T *pstatus);

/**
@if Chinese
* @brief  ��ȡ��ǰ�����ź�����
* @param[out]  prssi	-	�����ź�ǿ��
* @param[out]  prxfull	-	�����ź�����
* @return
*          - 0	-	�ɹ�
*          - -1	-	ʧ��
@else
* @brief  Get the current network signal quality
* @param[out]  prssi 	-	Received signal strength
* @param[out]  prxfull 	-	Received signal quality
* @return
*          - 0	-	Success
*          - -1	-	Fail
@endif 
*/
int wnet_get_network_signal_quality(BYTE *prssi, WORD *prxfull);

/*!
 @if Chinese
	@brief          ��ѯLTEģ��������ź�ǿ��
	@param[out]     strength         -	����LTEģ�鵱ǰ�������ź�ǿ��
	@return    	    
           - 0	-	�ɹ�
           - -1	-	ʧ��	
 @else
	@brief          Query the network signal strength of the LTE module
	@param[out]     strength         -	Save the current network signal strength of the LTE module
	@return    	    
           - 0	-	success
           - -1	-	failed
 @endif
*/
int wnet_get_lte_signal(WnetSigStr_t *strength);

/*!
 @if Chinese
	@brief          ��ѯLTEģ��ĸ���״̬
    @param[in]  devtype -	����(��Ĭ��:0)
	@return    	    
           - 0	-	δ��������
           - 1	-	�Ѹ�������
 @else
	@brief          Query the network attatch status of the LTE module
    @param[in]  devtype -	ignore (default: 0)
	@return    	    
           - 0	-	detached
           - 1	-	attached
 @endif
*/
int wnet_gprs_is_attatched(int devtype);

/**
@if Chinese
 * @brief  ��ȡpdp�����IP��ַ��DNS
 * @param[out] pdp_info -	�ṹ��PDP_GPRS_INFO ����IP��ַ��DNS
 * @return
 *          - 0		-	�ɹ�
 *          - -1	-	ʧ��
@else
 * @brief  Get the IP address and DNS after PDP activation
 * @param[out] pdp_info -	The structure PDP_GPRS_INFO contains the IP address and DNS
 * @return
 *          - 0		-	Success
 *          - -1	-	Fail
@endif  
 */
int wnet_get_pdp_link_info(PDP_GPRS_INFO *pdp_info);

/**
@if Chinese
* @brief  ʵ�忨/���⿨ģʽת��������������Ч
* @param[in]  mode	-	0:ʵ�忨,1:���⿨
* @return  
		   - 1    -	�ɹ�
		   - ���� - ʧ��	
@else		   
* @brief  The conversion between physical card and virtual card mode takes effect only after a restart
* @param[in]  mode	-	0:Physical card,1:Virtual card
* @return  
		   - 1 		- Success
		   - other 	- Fail	
@endif		   
*/
int sys_change_sim_mode(uint8_t mode);

/**
@if Chinese
* @brief  ��ȡ��ǰ�� ʵ�忨/���⿨ģʽ
* @return  0:ʵ�忨,1:���⿨
@else
* @brief  Gets the current physical card/virtual card mode
* @return  0:Physical card,1:Virtual card
@endif 
*/
uint8_t sys_get_sim_mode(void);

/**
@if Chinese
* @brief  China Mobile��China Unicom��China Telecom�����п�
* @param[in]  opid	-	1 - �й��ƶ�, 2 - �й���ͨ, 3 - �й�����
* @return  
		- 1    - �ɹ�
		- ���� - ʧ��	
@else		   
* @brief  China Mobile��China Unicom��China Telecom -Three network card
* @param[in]  opid	-	1 - to China Mobile, 2 - to China Unicom, 3 - to China Telecom
* @return  
		- 1 	- Success
		- other - Fail
@endif  		   
*/
int sys_vsim_switch_byopid(uint8_t opid);

/**
@if Chinese
* @brief  �ж��Ƿ��Ѿ�����vsim profile
* @return  
		- 1:vsim profile������ 
		- 0:vsim profileδ����
@else
* @brief  Check whether the VSIM profile has been downloaded
* @return  
		- 1	-	vsim profile downloaded 
		- 0	-	vsim profile not download
@endif 
*/
uint8_t sys_vsim_is_download(void);

/*!
 @if Chinese
	@brief      ��ȡ��ǰʹ�õ�����SIM��
	@return    	    
           - 0		-	SIM��1
           - 1		-	SIM��2
           - ����	-	��ȡʧ��
 @else
	@brief      Get the physical SIM card currently in use 
	@return    	    
           - 0		-	SIM card 1
           - 1		-	SIM card 2
           - Other	-	failed
 @endif
*/
int wnet_get_current_sim(void);

/*!
 @if Chinese
	@brief         �л�ʹ��ָ��������SIM��
    @param[in]     simno   -	ѡ���SIM����
                            - 0 ѡ��SIM��1
                            - 1 ѡ��SIM��2
	@return    	    
           - 0		-	 �ɹ�
           - ����	-	ʧ��
    @note   �л�SIM���ɹ�֮����Ҫ������������Ч
 @else
	@brief         Switch to the specified SIM card
	@param[in]     simno    -	Selected SIM card number
                            - 0 Select SIM card 1 
                            - 1 Select SIM card 2
	@return    	    
           - 0		-	successful
           - Other	-	failed
    @note   After switching the SIM card successfully, you need to restart the machine to take effect 
 @endif
*/
int wnet_select_sim(int simno);


/*!
 @if Chinese
	@brief         ��ȡ��ǰ����ģʽ
	@param none
	@return  
             - AT_AUTO	-	�Զ�ģʽ
             - RAT_GSM_ONLY	-	2Gģʽ
             - RAT_LTE_ONLY	-	4Gģʽ
             - ����	-	ʧ��
 @else
	@brief         get current network mode
	@param none
	@return  
             - AT_AUTO	auto network mode 
             - RAT_GSM_ONLY	2G network mode 
             - RAT_LTE_ONLY	4G network mode 
             - other	failed
 @endif
*/
uint8_t  wnet_get_lte_rat(void);

/*!
 @if Chinese
	@brief        ��������ģ(auto��2G��4G)
	@param[in] rat   -	�����õ�����ģʽ
                     - AT_AUTO	�Զ�ģʽ
                     - RAT_GSM_ONLY	2Gģʽ
                     - RAT_LTE_ONLY	4Gģʽ
	@return    	    
           - 0  -	�ɹ�
           - -1	-	ʧ��	    
 @else
	@brief       get current network mode
	@param[in] rat  -	Network mode to be set
                    - AT_AUTO	auto network mode 
                    - RAT_GSM_ONLY	2G network mode 
                    - RAT_LTE_ONLY	4G network mode 
	@return    	    
           - 0	-	successful
           - -1	-	failed	
 @endif
*/
int  wnet_set_lte_rat(uint8_t rat);


/*!
 @if Chinese
	@brief		  ��ȡĬ�ϳ���ʹ�õ�apn
	@param[in] apn_str	 -	���apn�ַ����Ļ�������apn���֧��99�ֽ�,����apn_str���������Ϊ100�ֽ�
	@param[in] len		 -	apn_str�������Ĵ�С
	@return 		
		   -  0  -	�ɹ�
		   - -1 -	�̼�δ֧�ָýӿ�
		   - -2 -	δ����sim��
		   - -3 -	���紦�ڷ���״̬
		   - -4 -  δ֪����   
 @else
	@brief		 Gets the apn used by the default pdn
	@param[in] apn_str	 -	The apn buffer supports a maximum of 99 bytes. It is recommended that the apn_str buffer be a maximum of 100 bytes
	@param[in] len		 -	apn str Size of the buffer
	@return 		
		   -  0  -	successful
		   - -1 -	The firmware does not support this api
		   - -2 -	No sim card is inserted
		   - -3 -	The network is not attached.
		   - -4 -	Unknown error
 @endif
*/
int  wnet_get_default_pdn_apn(char *apn_str, int len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WNET_H__ */

/** @} */

