/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app iccard模块</strong> 相关的接口
	 * @par 文件    appiccard.h
	 * @author		yangjing
	 * @date        2020-08-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-08-05    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-15    | 1.0.1        | lydia         | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app iccard </strong>  module
	 * @par file    appiccard.h
	 * @author		yangjing
	 * @date        2020-08-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-08-05    | 1.0.0        | yanjing       | create file
	 * 2022-04-15    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup appiccard ic卡
 @else
	@defgroup appiccard iccard
 @endif
 * @{
*/

#ifndef _APP_IC_CARD_H_
#define _APP_IC_CARD_H_


#ifdef __cplusplus	
extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief  该枚举类型列出了卡槽类型.
 @else
	@brief  This enumerated type lists the  card slot types.
 @endif
  */
typedef enum
{
	SLOT_PSAM1, 	/**< @if Chinese 接触式PSAM卡槽1 @else contact PSAM1 card slot @endif */
	SLOT_PSAM2, 	/**< @if Chinese 接触式PSAM卡槽2 @else contact PSAM2 card slot @endif */
	SLOT_PSAM3, 	/**< @if Chinese 接触式PSAM卡槽3 @else contact PSAM3 card slot @endif */
	SLOT_PSAM4, 	/**< @if Chinese 接触式PSAM卡槽4 @else contact PSAM4 card slot @endif */
	SLOT_EXCARD, 	/**< @if Chinese 接触式用户卡槽 @else contact user card slot @endif */
	SLOT_INRF, 	    /**< @if Chinese 内置非接卡槽 @else inner contactless card slot @endif */
	SLOT_EXRF_COM1, /**< @if Chinese 外置非接卡槽COM1口 @else external contactless COM1 card slot @endif */
	SLOT_EXRF_COM2, /**< @if Chinese 外置非接卡槽COM2口 @else external contactless COM2 card slot @endif */
	SLOT_EXRF_COM3, /**< @if Chinese 外置非接卡槽COM3口 @else external contactless COM3 card slot @endif */
	SLOT_EXRF_USB, 	/**< @if Chinese 外置非接卡槽USB口 @else external contactless USB slot @endif */
	SLOT_CHECK		/**< @if Chinese 检测接触式卡槽插卡状态 @else check the status for contact card slot @endif */
} SlotType;

/**
 @if Chinese
	@brief  该枚举类型列出了IC卡类型.
 @else
	@brief  This enumerated type lists the IC card types.
 @endif
  */
typedef enum
{
    ICC_SLE4442,		
    ICC_SLE4428,		
    ICC_SLE4436,		
    ICC_AT24C64,		
    ICC_CPUCARD,
    ICC_MIFARE,    		
    ICC_RFCPU_1356,            //<非接CPU卡13.56M
    ICC_RFCPU_24,              //<非接CPU卡2.4G 
    ICC_AT88SC102,
    ICC_AT88SC153,
    ICC_AT88SC1604
} IccType;

/**
 @if Chinese
	@brief  该枚举类型列出了IC卡操作类型.
 @else
	@brief  This enumerated type lists the IC card operation types.
 @endif
  */
typedef enum
{
	SLE4442_GET_ATR_BYTES, //上电复位获取复位应答数据
	SLE4442_READ_MAIN_MEMORY, //读主存储器
	SLE4442_UPDATE_MAIN_MEMORY, //修改主存储器
	SLE4442_READ_PROTECTION_MEMORY, //读保护存储器
	SLE4442_WRITE_PROTECTION_MEMORY, //写保护存储器
	SLE4442_READ_SECURITY_MEMORY, //读加密存储器
	SLE4442_UPDATE_SECURITY_MEMORY, //修改加密存储器
	SLE4442_COMPARE_VERIFICATION_DATA, //比较校验数据
	SLE4442_PSC_VERIFICATION, //可编程加密代码验证
	SLE4428_GET_ATR_BYTES, //上电复位获取复位应答数据
	SLE4428_READ_PROTECTED, //带保护位读
	SLE4428_READ_UNPROTECTED, //不带保护位读
	SLE4428_WRITE_ERASE_PROTECTED, //擦除和带保护位写
	SLE4428_WRITE_ERASE_UNPROTECTED, //擦除和不带保护位写
	SLE4428_PROTECT_COMPARE, //带比较的保护位写
	SLE4428_PSC_VERIFICATION, //可编程加密代码验证
	SLE4428_SET_PSC, //设置可编程加密代码
	SLE4436_READ_BYTES, //读取指定位数的字节
	SLE4436_WRITE_BYTES, //写入指定位数的字节
	SLE4436_WRITE_ERASE_CARRY, //在计数区按位地址执行写/擦除/进位
	SLE4436_WRITE_ERASE_CARRY_BACKUP,//在计数区按位地址执行写/擦除/进位，启用备份
	SLE4436_AUTHENTICATE_CARD, //执行认证
	SLE4436_PRESENT_CODE, //向卡片提供三个字节的传输码
	AT24C64A_READ_CARD_MEMORY, //从指定位置读卡内存
	AT24C64A_READ_CARD_MEM_SEQUL, //从当前卡片位置读卡内存
	AT24C64A_WRITE_CARD_MEMORY, //从指定位置写入信息
	AT24C64A_MEM_RESET,//存储器复位
	MIFARE_AUTH_BLOCK, //验证包含指定数据块的扇区
	MIFARE_READ_BLOCKS, //读数据块
	MIFARE_WRITE_BLOCKS, //写数据块
	MIFARE_INCREASE_DATA, //增加数据块内容并将结果保存到寄存器中
	MIFARE_DECREASE_DATA, //减少数据块内容并将结果保存到寄存器中
	CPUCARD_TRANSMIT_APDU //传送APDU命令
} OperationType;

/**
 @if Chinese
	@brief  该枚举类型列出了IC卡APDU.
 @else
	@brief  This enumerated type lists the IC card apdu.
 @endif
  */
typedef struct
{
	unsigned char OperType; /* reference enum - OperationType */
	unsigned char CLA; /* Class unsigned char of the command message*/
	unsigned char INS; /* Instrution*/
	unsigned char P1; /* Parameter1*/
	unsigned char P2; /* Parameter2*/
	unsigned char Lc; /* length of being sent data*/
	unsigned char Le; /* length of expected data*/
	unsigned char SW1; /* status word1*/
	unsigned char SW2; /* status word2*/
	unsigned char C_Data[256]; /* command data*/
	unsigned char R_Data[256]; /* response data*/
} ICCAPDU;

/**
 @if Chinese
	@brief  该枚举类型列出了IC卡状态.
 @else
	@brief  This enumerated type lists the IC card status.
 @endif
  */
typedef enum
{
	ICC_NORF = -4,        /**< @if Chinese 无非接卡片 @else no contactless card @endif */ 
	ICC_EMPTY = -3,       /**< @if Chinese 卡槽无卡片 @else no card in card slot @endif */ 
	ICC_COMMAND_FAIL = -2,/**< @if Chinese 与卡片通讯错误 @else communication error with card @endif */ 
	ICC_FAIL = -1,        /**< @if Chinese 操作失败 @else operation failed @endif */ 
	ICC_OK = 0            /**< @if Chinese 操作成功 @else operation success @endif */
}ICCStatus;

/*!
 @if Chinese
	@brief          检测接触式卡片是否在卡槽中
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         IC卡状态
 @else
	@brief          check whether the contact card is in the card slot
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_getcardstatus(int iSlotType);

/*!
 @if Chinese
	@brief          接触式IC卡上电
	@param[in]      iCardType	-	IC卡类型，参看enum IccType
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         IC卡状态
 @else
	@brief          contact IC card power on
	@param[in]      iCardType	-	IC card type，reference enum IccType
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_powerup(int iCardType, int iSlotType);

/*!
 @if Chinese
	@brief          接触式卡片下电
	@param[in]      iCardType	-	IC卡类型，参看enum IccType
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         IC卡状态
 @else
	@brief          contact IC card power off
	@param[in]      iCardType	-	IC card type，reference enum IccType
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_powerdown(int iCardType,  int iSlotType);

/*!
 @if Chinese
	@brief          接触式IC卡通讯函数
	@param[in]      iCardType	-	IC卡类型，参看enum IccType
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@param[in]      Apdu		-	各种类别的卡片操作根据ICCAPDU结构中的OperType操作类型而定
	@param[out]     Apdu		-	返回的数据根据ICCAPDU结构中的OperType操作类型而定，放在R_Data中
	@return         IC卡状态
 @else
	@brief          Send APDU to ICCard, and receive APDU from ICCard
	@param[in]      iCardType	-	IC card type，reference enum IccType
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@param[in]      Apdu		-	send APDU,reference OperType from struct ICCAPDU 
	@param[out]     Apdu		-	receive APDU,reference OperType from struct ICCAPDU 
	@return         IC card status
 @endif
*/
extern int app_icc_comm (int iCardType,int iSlotType , ICCAPDU *Apdu);

/*!
 @if Chinese
	@brief          接触式IC卡通讯函数(透传)
	@param[in]      iCardType	-	IC卡类型，参看enum IccType
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@param[in]      sendlen		-	发送的数据长度
	@param[in]      senddata	-	发送的数据内容
	@param[out]     recvlen		-	收到的数据长度
	@param[out]     recvdata	-	收到的数据内容
	@return         IC卡状态
 @else
	@brief          contact IC card communication function
	@param[in]      iCardType	-	IC card type，reference enum IccType
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@param[in]      sendlen		-	the length of send data
	@param[in]      senddata	-	send data buffer
	@param[out]     recvlen		-	the length of receive data
	@param[out]     recvdata	-	receive data buffer
	@return         IC card status
 @endif
*/
extern int app_icc_comm_raw(int iCardType,int iSlotType,  uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);

/*!
 @if Chinese
	@brief          非接读卡器寻卡
	@param[in]      iCardType	-	IC卡类型，参看enum IccType
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@param[out]     psUID		-	卡序列号,第一个字节为序列号长度
	@return         IC卡状态
 @else
	@brief          contactless card reader search card 
	@param[in]      iCardType	-	IC card type，reference enum IccType
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@param[out]     psUID		-	card serial number. The first byte is the length of the serial number
	@return         IC card status
 @endif
*/
extern int app_icc_ctls_powerup_seek (int iCardType, int iSlotType, char *psUID);

/*!
 @if Chinese
	@brief          打开IC卡设备
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         IC卡状态
 @else
	@brief          open IC card device 
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_open(int iSlotType);

/*!
 @if Chinese
	@brief          关闭IC卡设备
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         IC卡状态
 @else
	@brief          close IC card device 
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_close(int iSlotType);

/*!
 @if Chinese
	@brief          根据IC卡卡槽获取对应的描述符
	@param[in]      iSlotType	-	卡槽号，参看enum SlotType
	@return         >=0			-	成功,卡槽对应的描述符   other-fail
 @else
	@brief          get card slot descriptor
	@param[in]      iSlotType	-	card slot type，reference enum SlotType
	@return         >=0			-	success,card slot descriptor
	@return         other	-	fail
 @endif
*/
int app_icc_get_slotfd(int iSlotType);

/*!
 @if Chinese
	@brief          IC卡通讯函数
	@param[in]      slottype	-	卡槽号，参看enum SlotType
	@param[in]      sendlen		-	发送的数据长度
	@param[in]      senddata	-	发送的数据内容
	@param[out]     recvlen		-	收到的数据长度
	@param[out]     recvdata	-	收到的数据内容
	@return         IC卡状态
 @else
	@brief          IC card communication function 
	@param[in]      slottype	-	card slot type，reference enum SlotType
	@param[in]      sendlen		-	the length of send data
	@param[in]      senddata	-	send data buffer
	@param[out]     recvlen		-	the length of receive data
	@param[out]     recvdata	-	receive data buffer
	@return         IC card status
 @endif
*/
extern int app_icc_exchange_apdu(int slottype, uint32_t sendlen, unsigned char *senddata, uint32_t *recvlen, unsigned char *recvdata);

#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif


