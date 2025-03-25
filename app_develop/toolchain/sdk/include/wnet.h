
/**
@if Chinese
 * @brief    此模块用于描述 <strong>无线网络(GPRS)模块</strong> 相关的接口
 * @author   Jezz
 * @date     2018-11-01
 * @version  V1.0
 * @remarks Change History:
 * 日期          | 版本          | 作者            | 描述
 * ------------- | ------------- | --------------- | ----
 * 2018/11/01    | 1.0.0         | Jezz            | 创建文件
 * 2022/04/20    | 1.0.1         | Wenming         | 增加英文注释
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
 * @defgroup Wireless 无线网络
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
#define OPT_DEVWNET                     1               /**<@if Chinese 无线设备 	@else Wireless devices @endif*/
#define OPT_DEVETH                      2               /**<@if Chinese 以太网设备 	@else Ethernet equipment @endif*/
#define OPT_DEVWIFI                     3               /**<@if Chinese WIFI设备 	@else WIFI devices @endif*/
#define OPT_DEVMODEM                    4               /**<@if Chinese MODEM设备 	@else MODEM devices  @endif*/

#define MN_MAX_IMSI_ARR_LEN             8               /**<@if Chinese SIM CARD IMSI 最大长度 @else Maximum length of IMSI of SIM CARD @endif*/
#define MNSIM_ICCID_ID_NUM_LEN          10              /**<@if Chinese SIM CARD ID 最大长度 	@else Maximum length of SIM CARD ID @endif*/

#define RAT_AUTO 						0				/**<@if Chinese 自动网络模式 @else auto network mode@endif*/
#define RAT_GSM_ONLY 					2				/**<@if Chinese 2G网络模式 @else 2G network mode@endif*/
#define RAT_LTE_ONLY                    4				/**<@if Chinese 4G网络模式 @else 4G network mode@endif*/
/**
@if Chinese
 * @brief SIM卡信息枚举
@else 
 * @brief Enumeration of SIM card information
@endif  
 */
typedef enum {
    SIM_STATE_E = 0,          /**<@if Chinese 获取SIM卡状态 	@else Obtain the SIM card status @endif*/
    SIM_IMSI_E,               /**<@if Chinese 获取IMSI 			@else Get IMSI @endif*/
    SIM_CCID_E,               /**<@if Chinese 获取SIM卡ID 		@else Obtain the SIM card ID @endif*/
    SIM_ALL,                  /**<@if Chinese 获取SIM卡全部信息 @else Obtain all SIM card information @endif*/
    SIM_MAX,                  /**<@if Chinese 保留 				@else keep @endif*/
} SIM_INFO_E;

/**
@if Chinese
 * @brief SIM卡IMSI信息
@else  
 * @brief IMSI information of SIM card
@endif  
 */
typedef struct {
    BYTE imsi_len;               /**<@if Chinese IMSI信息长度 		@else Length of IMSI information @endif*/
    BYTE imsi_val[20];           /**<@if Chinese IMSI信息内容 		@else IMSI information @endif*/
} SIM_IMSI_T;

/**
@if Chinese
 * @brief SIM卡ID信息
@else 
 * @brief ID of a SIM card
@endif  
 */
typedef struct {
    BYTE id_num[2 * MNSIM_ICCID_ID_NUM_LEN + 1];        /**<@if Chinese SIM CARD ID 信息 @else SIM CARD ID information @endif*/
} SIM_ICCID_T;

/**
@if Chinese
 * @brief GPRS基站信息
@else 
 * @brief GPRS base station information
@endif 
 */
typedef struct {
    int arfcn;                   /**<@if Chinese 小区频点号 		@else Cell frequency number @endif*/
    int rxlev;                   /**<@if Chinese 小区接收功率，经常变化 @else Cell receiving power, often changing @endif*/
    int bsic;                    /**<@if Chinese 小区基站号  		@else Base station ID @endif*/
    int cell_id;                 /**<@if Chinese 小区号  			@else Base ID @endif*/
    int lac;                     /**<@if Chinese 小区位置区号 		@else Location area code @endif*/
} tBaseStationGPRS;

/*!
 @if Chinese
	@brief CDMA基站信息
 @else
	@brief CDMA Base Station information
 @endif
*/
typedef struct {                                                                                                                                                  
	int			BandClass;       /**< @if Chinese 频带种类             @else  Absolute Radio Frequency Channel Number           @endif */ 
	int			Channel;		 /**< @if Chinese 通道编号             @else  Received Signal Level                             @endif */ 
	int			SID;			 /**< @if Chinese system ID, 系统编号  @else  Base station ID                                   @endif */ 
	int			NID;			 /**< @if Chinese network ID, 网络编号 @else  Base ID                                           @endif */ 
	int			BaseStationPRev; /**< @if Chinese 基础设施             @else  location area code                                @endif */ 
	int			PilotPNoffset;	 /**< @if Chinese 当前主小区的导频偏移 @else  the pilot offset of the ME's current primary cell @endif */ 
	int			BaseStationID;	 /**< @if Chinese 小区基站号           @else  Base station ID                                   @endif */ 
	int			SlotCycleIndex;	 /**< @if Chinese  时隙周期指数        @else  the solt cycle index                              @endif */ 
	int			RawEcIo;		 /**< @if Chinese  导频强度(单位:DBm)  @else  the ME,s pilot strength in DBm                    @endif */ 
	int			RxPower;		 /**< @if Chinese 接收功率             @else  Reserved field, for extension                     @endif */ 
	int			TxPower;		 /**< @if Chinese 发送功率             @else  Reserved field, for extension                     @endif */ 
	int			TxAdj;			 /**< @if Chinese 发射功率调整         @else  the ME's transmitted power adjustment             @endif */ 
} tBaseStationCDMA; 

/**
@if Chinese
 * @brief 无线网络基站信息
@else 
 * @brief Wireless network base station information
@endif
 */
typedef struct {
    int iFlag;                  /**<@if Chinese 类型 1:GPRS, 2:CDMA @else Type 1: GPRS, 2: CDMA @endif*/
    tBaseStationGPRS oGprs;     /**<@if Chinese GPRS基站信息 		@else GPRS base station information @endif*/
    tBaseStationCDMA oCdma;     /**<@if Chinese CDMA基站信息 		@else CDMA base station information @endif*/
} tBaseStation;

/*!
 @if Chinese
	@brief GPRS基站信息
 @else
	@brief GPRS Base Station information
 @endif
*/
typedef struct {                                                                                                             
	int	arfcn;	  /**< @if Chinese  小区频点号             @else  Absolute Radio Frequency Channel Number @endif */  
	int	rxlev;	  /**< @if Chinese  小区接收功率，经常变化 @else  Received Signal Level                   @endif */  
	int	bsic;	  /**< @if Chinese  小区基站号             @else  Base station ID                         @endif */  
	int	cell_id;  /**< @if Chinese  小区号                 @else  Base ID                                 @endif */  
	int	lac;	  /**< @if Chinese  小区位置区号           @else  location area code                      @endif */  
	int	mnc;      /**< @if Chinese  移动网络代码           @else  Mobile Network Code                     @endif */  
	int	mcc;      /**< @if Chinese  移动台国家码           @else  Mobile Country Code                     @endif */  
	int	aiRev[5]; /**< @if Chinese  保留字段，扩展用       @else  Reserved field, for extension           @endif */  
} tBaseStationGPRSExt;

/*!
 @if Chinese
	@brief WCDMA基站信息
 @else
	@brief WCDMA Base Station information
 @endif
*/
typedef struct {                                                                                                                                               
	int	cell_id; /**< @if Chinese  小区号                           @else  Base ID                                 @endif */                           
	int	lac;	 /**< @if Chinese  小区位置区号                     @else  location area code                      @endif */                           
	int	mnc;     /**< @if Chinese  移动网络代码                     @else  Mobile Network Code                     @endif */                           
	int	mcc;     /**< @if Chinese  移动台国家码                     @else  Mobile Country Code                     @endif */                           
	int	uarfcn;	 /**< @if Chinese  UTRA绝对无线频率信道号           @else  UTRA absolute radio frequency channel number   @endif */                    
	int	psc;	 /**< @if Chinese  主扰码                           @else  Primary Scrambling Code                       @endif */                     
	int	rscp;	 /**< @if Chinese  接收信号码功率                   @else  Received Signal Code Power                    @endif */                     
	int	ecno;	 /**< @if Chinese  每个调制比特的能量与噪声功率之比 @else  Ratio of energy per modulating bit to the noise spectral density @endif */  
} tBaseStationWCDMA; 

/*!
 @if Chinese
	@brief LTE基站信息
 @else
	@brief LTE Base Station information
 @endif
*/
typedef struct {
	int			mcc;      /**< @if Chinese  移动台国家码                     @else  Mobile Country Code                     @endif */ 
	int			mnc;	  /**< @if Chinese  移动网络代码                     @else  Mobile Network Code                     @endif */
	int			cell_id;  /**< @if Chinese  小区号                           @else  Base ID                                 @endif */ 
	int			pci;      /**< @if Chinese  物理小区标识                     @else  Physical Cell Identifier                @endif */ 
	int			earfcn;	  /**< @if Chinese  频点号                           @else  the E-UTRA-ARFCN of the cell            @endif */
	int			tac;	  /**< @if Chinese  跟踪区编码                       @else  Tracking Area Code                      @endif */
	int			rsrp;	  /**< @if Chinese  参考信号接收功率                 @else  Reference Signal Receiving Power        @endif */
	int			rsrq;	  /**< @if Chinese  参考信号接收质量                 @else  Reference Signal Receiving Quality      @endif */
	int			rxlev;	  /**< @if Chinese  小区接收功率，经常变化           @else  Received Signal Level                   @endif */
} tBaseStationLTE;

/*!
 @if Chinese
	@brief 无线网络基站信息
 @else
	@brief Wireless network Base Station information
 @endif
*/
typedef struct {
	int			iFlag;	            /**< 0:NONE, 1:GPRS, 2:CDMA, 3:WCDMA,  4:LTE */
	union {
		tBaseStationGPRSExt	oGprs; /**< @if Chinese GPRS基站信息  @else GPRS Base Station information @endif */ 
		tBaseStationCDMA	oCdma; /**< @if Chinese CDMA基站信息  @else CDMA Base Station information @endif */
        tBaseStationWCDMA   oWcdma;/**< @if Chinese WCDMA基站信息 @else WCDMA Base Station information @endif */
		tBaseStationLTE     oLte;  /**< @if Chinese LTE基站信息   @else LTE Base Station information @endif */
	} Wnet;
} tBaseStationExt;

/*!
 @if Chinese
	@brief MT主动报告信号强度的服务模式
 @else
	@brief Service mode in which the MT will unsolicitedly report the signal strength
 @endif
*/
typedef enum {
    Mode_NON = 0,   /**< @if Chinese 无服务模式            @else NO SERVICE mode        @endif */
    Mode_GSM,       /**< @if Chinese GSM/GPRS/EDGE模式     @else GSM/GPRS/EDGE mode     @endif */
    Mode_WCDMA,     /**< @if Chinese WCDMA/HSDPA/HSPA模式  @else WCDMA/HSDPA/HSPA mode  @endif */
    Mode_TDSCDMA,   /**< @if Chinese TDSCDMA模式           @else TDSCDMA mode           @endif */
    Mode_LTE,       /**< @if Chinese LTE模式               @else LTE mode               @endif */
    Mode_CDMA,      /**< @if Chinese CDMA模式              @else CDMA mode              @endif */
    Mode_EVDO,      /**< @if Chinese EV-DO/eHRPD模式       @else EV-DO/eHRPD mode       @endif */
    Mode_CDMAEVDO,  /**< @if Chinese CDMA/EV-DO(eHRPD)模式 @else CDMA/EV-DO(eHRPD) mode @endif */
}wnetMode_t;

/*!
 @if Chinese
	@brief GSM/GPRS/EDGE模式下的信号强度
 @else
	@brief Signal strength in GSM/GPRS/EDGE mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator @endif */
    int         reserve[7];
} GsmSigStr_t;

/*!
 @if Chinese
	@brief WCDMA/HSDPA/HSPA模式下的信号强度
 @else
	@brief Signal strength in WCDMA/HSDPA/HSPA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator  @endif */
    int         rscp;      /**< @if Chinese 接收信号码功率     @else Receive Signal Channel Power        @endif */
    int         ecio;      /**< @if Chinese 码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io @endif */
    int         reserve[5];
} WcdmaSigStr_t;

/*!
 @if Chinese
	@brief TDSCDMA模式下的信号强度
 @else
	@brief Signal strength in TDSCDMA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator  @endif */
    int         rscp;      /**< @if Chinese 接收信号码功率     @else Receive Signal Channel Power        @endif */
    int         ecio;      /**< @if Chinese 码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io @endif */
    int         reserve[5];
} TdscdmaSigStr_t;

/*!
 @if Chinese
	@brief LTE模式下的信号强度
 @else
	@brief Signal strength in LTE mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator @endif */
    int         rsrp;      /**< @if Chinese 参考信号接收功率   @else Reference Signal Receiving Power   @endif */
    int         sinr;      /**< @if Chinese 信干噪比           @else Signal to Interference Noise Ratio @endif */
    int         rsrq;      /**< @if Chinese 参考信号接收质量   @else Reference Signal Received Quality  @endif */
    int         reserve[4];
} LteSigStr_t;

/*!
 @if Chinese
	@brief CDMA模式下的信号强度
 @else
	@brief Signal strength in CDMA mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator  @endif */
    int         ecio;      /**< @if Chinese 码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io @endif */
    int         reserve[6];
} CdmaSigStr_t;

/*!
 @if Chinese
	@brief EV-DO/eHRPD模式下的信号强度
 @else
	@brief Signal strength in EV-DO/eHRPD mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator  @endif */
    int         ecio;      /**< @if Chinese 码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io @endif */
    int         sinr;      /**< @if Chinese 信干噪比           @else Signal to Interference Noise Ratio  @endif */
    int         reserve[5];
} EvdoSigStr_t;

/*!
 @if Chinese
	@brief CDMA/EV-DO(eHRPD)模式下的信号强度
 @else
	@brief Signal strength in CDMA/EV-DO(eHRPD) mode
 @endif
*/
typedef struct {
    int         rssi;      /**< @if Chinese 接收信号强度指示   @else Received Signal Strength Indicator              @endif */
    int         cdma_ecio; /**< @if Chinese cdma码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io of cdma @endif */
    int         evdo_ecio; /**< @if Chinese evdo码片的能量与接收总频谱密度（信号加噪声）的比值   @else Ec/Io of evdo @endif */
    int         evdo_sinr; /**< @if Chinese 信干噪比           @else Signal to Interference Noise Ratio              @endif */
    int         reserve[4];
} CdmaEvdoSigStr_t;

/* the signal strength of current service network */
/*!
 @if Chinese
	@brief 当前服务网络的信号强度
 @else
	@brief the signal strength of current service network
 @endif
*/
typedef struct signal_strength {
    wnetMode_t  mode;                 /**< @if Chinese 服务模式 @see wnetMode_t  @else Service mode @see wnetMode_t @endif */ 
    union {
        GsmSigStr_t      sGsm;        /**< @if Chinese GSM/GPRS/EDGE模式下的信号强度     @else Signal strength in GSM/GPRS/EDGE mode     @endif */
        WcdmaSigStr_t    sWcdma;      /**< @if Chinese WCDMA/HSDPA/HSPA模式下的信号强度  @else Signal strength in WCDMA/HSDPA/HSPA mode  @endif */
        TdscdmaSigStr_t  sTdscdma;    /**< @if Chinese TDSCDMA模式下的信号强度           @else Signal strength in TDSCDMA mode           @endif */
        LteSigStr_t      sLte;        /**< @if Chinese LTE模式下的信号强度               @else Signal strength in LTE mode               @endif */
        CdmaSigStr_t     sCdma;       /**< @if Chinese CDMA模式下的信号强度              @else Signal strength in CDMA mode              @endif */
        EvdoSigStr_t     sEvdo;       /**< @if Chinese EV-DO/eHRPD模式下的信号强度       @else Signal strength in EV-DO/eHRPD mode       @endif */
        CdmaEvdoSigStr_t sCdmaEvdo;   /**< @if Chinese CDMA/EV-DO(eHRPD)模式下的信号强度 @else Signal strength in CDMA/EV-DO(eHRPD) mode @endif */
    }wss; 
} WnetSigStr_t;

/**
@if Chinese
 * @brief 无线网络PLMN状态信息
@else 
 * @brief PLMN status of the wireless network
@endif  
 */
typedef enum {
    PLMN_NO_SERVICE = 0,                                /**<@if Chinese 没有服务 @else no service @endif*/
    PLMN_NORMAL_GSM_ONLY = 0x01,                        /**<@if Chinese 语音服务 @else voice service available @endif*/
    PLMN_NORMAL_GPRS_ONLY = 0x02,                       /**<@if Chinese 数据服务可用 @else data service available @endif*/
    PLMN_NORMAL_GSM_GPRS_BOTH = 0x03,                   /**<@if Chinese 提供语音和数据服务 @else voice and data service available @endif*/

    PLMN_NORMAL_CS_ONLY = 0x01,                         /**<@if Chinese 语音服务 @else voice service available @endif*/
    PLMN_NORMAL_PS_ONLY = 0x02,                         /**<@if Chinese 数据服务可用 @else data service availabe @endif*/
    PLMN_NORMAL_CS_PS_BOTH = 0x03,                      /**<@if Chinese 提供语音和数据服务 @else voice and data service available @endif*/
    PLMN_EMERGENCY_ONLY = 0x04,                         /**<@if Chinese 紧急服务 @else emergency service available @endif*/
    PLMN_EMERGENCY_SIM_INVALID = 0x05,                  /**<@if Chinese 紧急情况;MM处于有限服务状态和不允许进行进一步的PLMN访问,直到力量或新的SIM卡插入 @else emergency; MM in limited service state and
                                                             no further PLMN access allowed until power
                                                             off or new SIM inserted @endif*/
    PLMN_EMERGENCY_GPRS_ONLY = 0x06,                    /**<@if Chinese 在紧急情况下提供数据服务; MM在有限的服务状态 @else data service availabe but emergency;
                                                             MM in limited service state @endif*/
    PLMN_EMERGENCY_SIM_INVALID_GPRS_ONLY = 0x07,        /**<@if Chinese 在紧急情况下提供数据服务;允许PLMN访问，直到下电或新SIM卡插入 @else data service availabe but emergency;
                                                             MM in limited service state and no further
                                                             PLMN access allowed until power off or new SIM inserted @endif*/

    PLMN_REGISTER_SERVICE = 0x08,                       /**<@if Chinese Register 服务 @else attaching after camping on @endif*/
    PLMN_REGISTER_GPRS_ONLY = 0x09,                     /**<@if Chinese 数据服务可用，但正在连接 @else data service availabe but attaching @endif*/
    PLMN_FULL_PS_SERVICE = 0x0A                         /**<@if Chinese 全PS服务，无cs服务 @else full PS service, no cs service @endif*/

} GPRS_PLMN_STATUS_E;

/**
@if Chinese
 * @brief 无线网络附着状态信息
@else 
 * @brief Wireless network attachment status information
@endif  
 */
typedef enum {
    MN_INVALID_STATE,                                   /**<@if Chinese 此字段无效 @else this field is invalid @endif*/
    MN_ATTACHED_STATE,                                  /**<@if Chinese Cs或ps已附上 @else cs or ps has been attached @endif*/
    MN_DETACHED_SATE,                                   /**<@if Chinese Cs或ps已分离 @else cs or ps has been detached @endif*/
    MN_NO_SERVICE                                       /**<@if Chinese Cs和ps没有服务 @else no service for cs or ps @endif*/
} GPRS_ATTACH_STATE_E;

/**
@if Chinese
 * @brief 无线网络状态信息
 @else 
 * @brief Wireless network status information
@endif  
 */
typedef struct {
    GPRS_PLMN_STATUS_E      plmn_status;                /**<@if Chinese plmn状态 @else plmn statue @endif*/
    BOOL                    plmn_is_roaming;            /**<@if Chinese PLMN是漫游状态 PLMN @else if plmn is roaming plmn @endif*/
    WORD                    mcc;                        /**<@if Chinese 移动台国家码 @else MCC: mobile country code @endif*/
    WORD                    mnc;                        /**<@if Chinese 移动网络代码 @else MNC: mobile network code @endif*/
    WORD                    mnc_digit_num;              /**<@if Chinese MNC位数 @else MNC digit number @endif*/
    WORD                    lac;                        /**<@if Chinese 小区位置区号 @else Location area code @endif*/
    WORD                    cell_id;                    /**<@if Chinese 小区号 @else  Base ID @endif*/
} GPRS_NETWORK_STATUS_T;

/**
@if Chinese
 * @brief PDP激活后GPRS信息
@else  
 * @brief GPRS information after PDP activation
@endif 
 */
typedef struct {
    uint32_t ipaddr;            /**<@if Chinese IP地址 				@else IP address @endif*/
    uint32_t pri_dns;           /**<@if Chinese DNS服务器 			@else Primary  @endif*/
    uint32_t sec_dns;           /**<@if Chinese DNS服务器 			@else Secondary  @endif*/
    uint8_t  nsapi[4];          /**<@if Chinese 网络服务接入点标识符 @else Network service Access Point identifier @endif*/
} PDP_GPRS_INFO;

/**
@if Chinese
* @brief  初始化模块
* @param[in]  TimeoutMs	
*          - >0		-	初始化寻找模块的时间（单位：毫秒）
*          - <=0	-	一直等待寻找模块完成
* @return
*          - 0	-	成功
*          - <0	-	失败，返回相应的返回值
@else
* @brief  init wnet module
* @param[in]  TimeoutMs	
*          - >0		-	Time to initialize the search module in milliseconds
*          - <=0	-	Wait for the search module to complete
* @return
*          - 0	-	Success
*          - <0	-	Fail，Returns the corresponding return value
@endif 
*/
int wnet_init(int TimeoutMs);

/**
@if Chinese
* @brief  对模块进行复位
* @return
*          - 0	-	成功
*          - <0	-	失败，返回相应的返回值
@else
* @brief  Reset wnet
* @return
*          - 0	-	Success
*          - <0	-	Fail，Returns the corresponding return value
@endif
*/
int wnet_reset(void);

/**
@if Chinese
* @brief  选择无线模块操作的通道，slot0或者slot1
* @param[in]  slotNo	-	选择通道	
*          - 0	-	选择slot0通道（默认）
*          - 1	-	选择slot1通道（在配置了第二个模块的情况下使用）
* @return int
*          - 0	-	上一次使用通道0
*          - 1	-	上一次使用通道1
*          - <0	-	失败，返回相应的返回值
@else
* @brief  Select the channel that the wireless module operates on，slot0 or slot1
* @param[in]  slotNo	-	selector channel		
*          - 0	-	Select SLOt0 channel (default)
*          - 1	-	Select the SLOT1 channel (used when a second module is configured)
* @return int
*          - 0	-	Channel 0 was used last time
*          - 1	-	Channel 1 was used last time
*          - <0	-	Fail，Returns the corresponding return value
@endif 
*/
int wnet_select_module(int slotNo);

/**
@if Chinese
* @brief  启用PPP链路
* @param[in]  devtype   -	忽略(可默认:OPT_DEVWNET)
* @param[in]  apn       -	无线连接的接入点名称,长度不能超过99个字符
* @param[in]  name      -	认证时所需的用户名，长度不能超过64个字符
* @param[in]  passwd    -	认证时所需的密码，长度不能超过64个字符
* @param[in]  auth      -	忽略
* @param[in]  timeout	-	ppp登陆的超时时间，单位为毫秒
* @return  int
*          - 0	-	表示成功
*          - <0	-	表示失败
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
* @brief  关闭PPP链路
* @param[in]  devtype	-	忽略(可默认:OPT_DEVWNET)
* @return
*          - 0	-	成功<br>
*          - <0	-	失败，返回相应的返回值
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
* @brief  检查PPP链路情况
* @param[in]  devtype	-	忽略(可默认:0)
* @return
*          - 0	-	表示链路已成功建立；<br>
*          - <0	-	表示链路建立失败或链路没有启用；或者表示处理当中；
@else
* @brief  Check PPP links
* @param[in]  devtype	-	Ignore (default :0)
* @return
*          - 0	-	Indicates that the link is successfully established；<br>
*          - <0	-	Indicates that the link fails to be established or the link is disabled.Or in process;
@endif
*/
int wnet_PPP_check(int devtype);

/**
@if Chinese
* @brief  获取基站信息
* @param[out]  psBaseStationInfo	-	基站信息
* @return 返回0表示成功；其他表示失败
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
* @brief  获取基站信息
* @param[out]  psBaseStationInfo-	基站信息
* @return 返回RET_OK表示成功；其他表示失败
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
* @brief  获取相邻基站信息
* @param[out]   psBaseStationInfo   -	存放相邻基站信息的结构数组，最少6个。
* @param[in]    iNum                -	基站信息结构个数，最小6
* @param[out]   piOutNum            -	查询到的相邻基站信息的个数
* @return 返回0表示成功；其他表示失败
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
* @brief  读取GPRS模块的IMEI号
* @param[out]  IMEI	-	输出IMEI号（带'\0'的字符串形式），要求空间不少于16字节
* @param[in]   len	-	传入IMEI数组的有效长度
* @return
*          - 0	-	成功
*          - <0	-	失败，返回相应的返回值
@else
* @brief  Read the IMEI of the GPRS module
* @param[out]  IMEI	-	Output the IMEI (as a string with '\0'), requiring at least 16 bytes of space
* @param[in]   len	-	Pass in the effective length of the IMEI array
* @return
*          - 0	-	Success
*          - <0	-	Fail，Returns the corresponding return value
@endif 
*/
int wnet_get_IMEI(char *IMEI, int len);

/**
@if Chinese
* @brief  获取SIM卡ID
* @param[out]   psSimCardID     -	存储Sim Card ID 信息(带'\0'的字符串形式)
* @param[in]    iLen            -	psSimCardID缓冲长度
* @return 返回0表示成功；其他表示失败
* @note   注意: psSimCardID返回的实际字符串内容与iLen的传值有关；一般sim card id长度为20字节，iLen的建议值为>=21字节
* 比如: 真实sim card id为 "01234567890123456789"
* 如果传入iLen小于0或等于1个字节，都将会报错，至少留有一个字节存储'\0'
* 如果传入2个字节，则实际返回psSimCardID="0\0"
* 如果传入4个字节，则实际返回psSimCardID="012\0"
* 如果传入5个字节，则实际返回psSimCardID="0123\0"
* 如果传入10个字节，则实际返回psSimCardID="012345678\0"
* 如果传入20个字节，则实际返回psSimCardID="0123456789012345678\0"
* 如果传入21个字节，则实际返回psSimCardID="01234567890123456789\0"
* 如果传入25个字节，则实际返回psSimCardID="01234567890123456789\0"
@else
* @brief  Get the SIM card ID
* @param[out]   psSimCardID     -	Store Sim Card ID information (string with '\0')
* @param[in]    iLen            -	The length of the buffer
* @return
*          - 0	-	Success
*          - <0	-	Fail，Returns the corresponding return value
* @note   Note that the actual string content returned by psSimCardID is related to the iLen pass;Generally, the LENGTH of sim card ID is 20 bytes. The recommended value for iLen is >.= 21 bytes
@endif
*/
int wnet_read_sim_card_id(char *psSimCardID, int iLen);

/**
@if Chinese
* @brief  获取SIM卡IMSI
* @param[out]   IMSI           -	存储Sim Card IMSI 信息（带'\0'的字符串形式），要求空间不少于16字节
* @param[in]    len            -	传入IMSI数组的有效长度
* @return 返回0表示成功；其他表示失败
@else
* @brief  Get the IMSI of the SIM card
* @param[out]   IMSI	-	Store Sim Card IMSI information (in the form of a string with '\0'). The space required is not less than 16 bytes
* @param[in]    len		-	The effective length of the IMSI array passed in
* @return 	0:Succes；other:Fail
@endif 
*/
int wnet_get_sim_card_IMSI(char *IMSI, int len);

/**
@if Chinese
 * @brief 检查SIM卡状态
 * @return 0: 存在 其他: 不存在
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
* @brief  函数执行gprs附网请求
* @return
*          - 0	-	成功
*          - -1	-	失败
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
* @brief  该函数执行gprs分离请求
* @return
*          - 0	-	成功
*          - -1	-	失败
@else
* @brief  This function performs the GPRS separation request
* @return
*          - 0	-	Success
*          - -1	-	Fail
@endif 
*/
int wnet_gprs_detach(void);

#if 0 //删除此接口
/**
* @brief  该功能获取SIM卡信息，包含IMSI,CCID
* @param[in]    flag 忽略(可默认:SIM_ALL)
* @param[out]   imsi_str 获取IMSI信息
* @param[out]   ccid 获取CCID信息
* @return
*          - 1 成功
*          - 0 失败
*/
int wnet_get_sim_info(SIM_INFO_E flag, SIM_IMSI_T *imsi_str, SIM_ICCID_T *ccid);
#endif

/**
@if Chinese
* @brief  G获取当前网络状态
* @param[out]  pstatus -	结构体 GPRS_NETWORK_STATUS_T 包含网络状态信息
* @return
*          - 0	-	成功
*          - -1	-	失败
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
* @brief  获取当前网络信号质量
* @param[out]  prssi	-	接收信号强度
* @param[out]  prxfull	-	接收信号质量
* @return
*          - 0	-	成功
*          - -1	-	失败
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
	@brief          查询LTE模块的网络信号强度
	@param[out]     strength         -	保存LTE模块当前的网络信号强度
	@return    	    
           - 0	-	成功
           - -1	-	失败	
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
	@brief          查询LTE模块的附网状态
    @param[in]  devtype -	忽略(可默认:0)
	@return    	    
           - 0	-	未附着网络
           - 1	-	已附着网络
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
 * @brief  获取pdp激活后IP地址和DNS
 * @param[out] pdp_info -	结构体PDP_GPRS_INFO 包含IP地址和DNS
 * @return
 *          - 0		-	成功
 *          - -1	-	失败
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
* @brief  实体卡/虚拟卡模式转换，需重启才生效
* @param[in]  mode	-	0:实体卡,1:虚拟卡
* @return  
		   - 1    -	成功
		   - 其他 - 失败	
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
* @brief  获取当前是 实体卡/虚拟卡模式
* @return  0:实体卡,1:虚拟卡
@else
* @brief  Gets the current physical card/virtual card mode
* @return  0:Physical card,1:Virtual card
@endif 
*/
uint8_t sys_get_sim_mode(void);

/**
@if Chinese
* @brief  China Mobile、China Unicom、China Telecom三网切卡
* @param[in]  opid	-	1 - 中国移动, 2 - 中国联通, 3 - 中国电信
* @return  
		- 1    - 成功
		- 其他 - 失败	
@else		   
* @brief  China Mobile、China Unicom、China Telecom -Three network card
* @param[in]  opid	-	1 - to China Mobile, 2 - to China Unicom, 3 - to China Telecom
* @return  
		- 1 	- Success
		- other - Fail
@endif  		   
*/
int sys_vsim_switch_byopid(uint8_t opid);

/**
@if Chinese
* @brief  判断是否已经下载vsim profile
* @return  
		- 1:vsim profile已下载 
		- 0:vsim profile未下载
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
	@brief      获取当前使用的物理SIM卡
	@return    	    
           - 0		-	SIM卡1
           - 1		-	SIM卡2
           - 其它	-	获取失败
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
	@brief         切换使用指定的物理SIM卡
    @param[in]     simno   -	选择的SIM卡号
                            - 0 选择SIM卡1
                            - 1 选择SIM卡2
	@return    	    
           - 0		-	 成功
           - 其它	-	失败
    @note   切换SIM卡成功之后，需要重启机器才生效
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
	@brief         获取当前网络模式
	@param none
	@return  
             - AT_AUTO	-	自动模式
             - RAT_GSM_ONLY	-	2G模式
             - RAT_LTE_ONLY	-	4G模式
             - 其他	-	失败
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
	@brief        设置网络模(auto、2G、4G)
	@param[in] rat   -	需设置的网络模式
                     - AT_AUTO	自动模式
                     - RAT_GSM_ONLY	2G模式
                     - RAT_LTE_ONLY	4G模式
	@return    	    
           - 0  -	成功
           - -1	-	失败	    
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
	@brief		  获取默认承载使用的apn
	@param[in] apn_str	 -	存放apn字符串的缓冲区，apn最大支持99字节,建议apn_str缓冲区最大为100字节
	@param[in] len		 -	apn_str缓冲区的大小
	@return 		
		   -  0  -	成功
		   - -1 -	固件未支持该接口
		   - -2 -	未插入sim卡
		   - -3 -	网络处于分离状态
		   - -4 -  未知错误   
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

