/**
@if Chinese
* @brief    此模块用于描述 <strong>非接卡模块</strong> 相关的接口
* @details  支持ISO14443协议的非接卡[TYPE A, TYPE B]
* @author   Neal
* @date     2010-10-14
* @version  V1.0
* @remarks Change History:
* 日期          | 版本          | 作者            | 描述
* ------------- | ------------- | --------------- | ----
* 2010/10/14    | 1.0.0         | Neal            | 创建文件
* 2018/10/26    | 1.0.1         | Victor          | 添加doxygen注释信息
* 2022/04/20    | 1.0.2         | Wenming         | 增加英文注释
@else
* @brief    This module is used to describe <strong>NFC Card</strong> interfaces module
* @details  Support the ISO14443 protocol non - access card[TYPE A, TYPE B]
* @author   Neal
* @date     2010-10-14
* @version  V1.0
* @remarks Change History:
* Date          | Version       | Author          | Desc
* ------------- | ------------- | --------------- | ----
* 2010/10/14    | 1.0.0         | Neal            | Create file
* 2018/10/26    | 1.0.1         | Victor          | Add doxyGen comment information
* 2022/04/20    | 1.0.2         | Wenming         | Add English description
@endif
*/

/**
@if Chinese
* @defgroup nfc 非接卡
@else
* @defgroup nfc NFC Card
@endif
* @{
*/

#ifndef ISO14443_H_
#define ISO14443_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__KERNEL__)
enum {
    MIF_TYPE_A      = 0x00,                 /**<@if Chinese 类型A 		@else TypeA              @endif*/
    MIF_TYPE_B,                             /**<@if Chinese 类型B 		@else  TypeB              @endif*/
    MIF_TYPE_C1,                            /**<@if Chinese 类型C1 		@else  FeliCa, 212kbits/s @endif*/
    MIF_TYPE_C2,                            /**<@if Chinese 类型C2 		@else  FeliCa, 424kbits/s @endif*/
    MIF_TYPE_UNKNOWN,                       /**<@if Chinese 未知类型 	@else  unknown type       @endif*/
};
#else

#define MIF_TYPE_A              0x00    /**<@if Chinese 类型A 	@else TypeA              @endif*/
#define MIF_TYPE_B              0x01    /**<@if Chinese 类型B 	@else TypeB              @endif*/
#define MIF_TYPE_C1             0x02    /**<@if Chinese 类型C1 	@else FeliCa, 212kbits/s @endif*/
#define MIF_TYPE_C2             0x03    /**<@if Chinese 类型C2 	@else FeliCa, 424kbits/s @endif*/
#define MIF_TYPE_UNKNOWN        0x04    /**<@if Chinese 未知类型 @else unknown type       @endif*/
#endif

#ifdef CFG_EMV_L1_TEST
/* @brief 仅用于对非接EMV-L1认证
 */
typedef struct {
    uint32_t    nfc_wait_tp_time;
    uint32_t	FWT_ATQB;
    uint32_t	FDT_a_picc_min;
    uint32_t	FDT_pcd_min;
}nfc_time_param_t;
#endif

/**
@if Chinese
* @brief 打开非接读卡器设备，并返回设备文件描述符
* @param[in]	filename	-	设备文件名 "/dev/nfc"
* @return		fd  		-	设备的文件描述符 <br>
*   <em> >= 0 </em>     ----成功 <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
@else
* @brief Opens MIF card reader device and returns the device file descriptor
* @param[in] filename	-	Device name "/dev/nfc"
* @return  	fd 			-	The file descriptor for the device <br>
*   <em> >= 0 </em>     ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_open(const char *filename);

//#define nfc_open mif_open 定义别名，两者都可以使用

//int mif_get_sp_fd(void); //可以删除

/**
@if Chinese
* @brief 关闭非接读卡器设备
* @param[in]	fd		-	非接读卡器设备文件描述符
* @return 返回值 <br>
*   <em> 0 </em>    ----成功 <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
@else
* @brief close MIF device
* @param[in]	fd		-	The file descriptor for the device
* @return int <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_close(int fd);

/**
@if Chinese
* @brief 打开非接读卡器设备，并返回设备文件描述符
* @param[in]	filename	-	设备文件名 "/dev/nfc"
* @return   设备的文件描述符 <br>
*   <em> >= 0 </em>     ----成功 <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
* @note 它是 @ref mif_open 的别名函数，使用效果与 @ref mif_open 完全一样
@else
* @brief Open NFC device,return the file descriptor
* @param[in]	filename	-	Device name "/dev/nfc"
* @return   fd <br>
*   <em> >= 0 </em>     ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
* @note The effect is the same as @ref mif_open 
@endif 
*/
int nfc_open(const char *filename);

/**
@if Chinese
* @brief 关闭非接读卡器设备
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值 <br>
*   <em> 0 </em>    ----成功 <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
* @note 它是 @ref mif_close 的别名函数，使用效果与 @ref mif_close 完全一样
@else
* @brief Close NFC device
* @param[in]	fd	-	NFC card reader device file descriptor
* @return return value <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
* @note The effect is the same as @ref mif_close 
@endif
*/
int nfc_close(int fd);

/**
@if Chinese
* @brief 关于MIF超时的结构体成员解析
@else
* @brief Structure member resolution on MIF timeouts
@endif
**/
struct mif_timeout {
    uint32_t WaitTime_PollTypeA;    /**<@if Chinese 在TypeA轮询过程中PCD到PICC的帧延迟时间(单位:us，默认:100us)  	@else The Frame Delay Time PCD to PICC during TypeA poll procedure (Unit:us, default: 100us) 		@endif*/
    uint32_t WaitTime_PollTypeB;    /**<@if Chinese 在TypeB轮询过程中PCD到PICC的帧延迟时间(单位:etu，默认:500etu)  	@else The Frame Delay Time PCD to PICC during TypeB poll procedure (Unit:etu, default: 500etu) 		@endif*/
    uint32_t WaitTime_Mifare;       /**<@if Chinese mifare经典和超轻卡操作期间的帧等待时间(单位:etu，默认:10240etu)	@else The Frame Wait Time during mifare classic and ultralight card opertaion (Unit:etu, default: 10240etu) @endif*/
    uint32_t WaitTime_RATS;         /**<@if Chinese T=CL卡激活时帧等待时间(单位:etu，默认:500etu)  					@else The Frame Wait Time during T=CL card activate (Unit:etu, default: 500etu) 					@endif*/
    uint32_t WaitTime_CardResponse; /**<@if Chinese PICC等待响应的最大帧等待时间(单位:etu，默认:573440etu)  		@else The maxium Frame Wait Time during waiting response from PICC (Unit:etu, default: 573440etu) 	@endif*/
    uint32_t WaitTime_CompleteCmd;  /**<@if Chinese PCD与PICC完成一次数据交换的最大等待时间(单位:ms，默认:6000ms)  	@else The maxium Wait Time for completing one data exchange between PCD and PICC (Unit:ms, default: 6000ms) @endif*/
    uint32_t WaitTime_DelayBefore;  /**<@if Chinese PICC到PCD的帧延迟时间(单位:us，默认:500us)  					@else The Frame Delay Time PICC to PCD (Unit:us, default: 500us) 									@endif*/
    uint32_t WaitTime_IdleRF;       /**<@if Chinese 载波关闭时的延迟时间(单位:ms，默认:6ms)  						@else The delay time while carrier off (Unit:ms, default: 6ms) 										@endif*/
};
int mif_set_timeout(const struct mif_timeout *ptime);
int mif_get_timeout(struct mif_timeout *ptime);

int iso14443_delay_etu(int fd, uint32_t numofetu);

/**
@if Chinese
* @brief 复位非接卡片
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
@else
* @brief Reset the iso14443 card
* @param[in] 	fd	-	Iso14443 card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif
**/
int iso14443_reset_picc(int fd);

/**
@if Chinese
* @brief 配置非接读卡器硬件接口类型
* @param[in] 	fd 		-	非接读卡器设备文件描述符
* @param[in] 	type 	-	非接读卡器硬件接口类型,以下为类型种类:<br>
*                 0x00  ----- ISO14443 TypeA    <br>
*                 0x01  ----- ISO14443 TypeB    <br>
*                 0x02  ----- Sony FeliCa, 212kbits/s   <br>
*                 0x03  ----- Sony FeliCa, 424kbits/s   
* @return 返回值<br>
*   <em> 0 </em>    ----成功 <br>
*   <em> 其它 </em>     ----失败, 可根据errno获取错误码
@else
* @brief Set the MIF card device interface type
* @param[in]	fd		-	Mif card device file descriptor
* @param[in]	type 	-	MIF card reader Hardware interface type:<br>
*                 0x00  ----- ISO14443 TypeA    <br>
*                 0x01  ----- ISO14443 TypeB    <br>
*                 0x02  ----- Sony FeliCa, 212kbits/s   <br>
*                 0x03  ----- Sony FeliCa, 424kbits/s   
* @return <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_select_carrier_type(int fd, int32_t type);

/**
@if Chinese
* @brief 给卡片发送REQA指令
* @param[in]	fd 		-	非接读卡器设备文件描述符
* @param[out]	atqa 	-	卡片对该指令的应答[2 Byte]
* @return 返回值    <br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数         <br>
*               EIO     ---- 硬件错误           <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误           <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容  <br>
*               EBADE   ---- 卡片返回错误响应信息           <br>
*               ETIME   ---- 超时           <br>
*               EMULTIHOP   ---- 射频场中有多张卡            <br>
@else
* @brief Send REQA to card
* @param[in] 	fd 		-	iso14443 card device file descriptor
* @param[out] 	atqa 	-	The card's response to this command[2 Byte]
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif 
*/
int iso14443_ReqA(int fd, void *atqa);

/**
@if Chinese
* @brief 给卡片发送WUPA指令
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[out]	atqa	-	卡片对该指令的应答[2 Byte]
* @return 返回值    <br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数           <br>
*               EIO     ---- 硬件错误           <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误           <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容  <br>
*               EBADE   ---- 卡片返回错误响应信息           <br>
*               ETIME   ---- 超时           <br>
*               EMULTIHOP   ---- 射频场中有多张卡           <br>
@else 
* @brief Send WUPA instructions to iso14443 card
* @param[in]	fd		-	iso14443 card device file descriptor
* @param[out]	atqa	-	The card's response to this command[2 Byte]
* @return   <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif
*/
int iso14443_WupA(int fd, void *atqa);

/**
@if Chinese
* @brief 给卡片发送防冲突指令
* @param[in]	fd	-	非接读卡器设备文件描述符
* @param[in]	sel	-	防冲突级别 <br>
*                0x93    ---- 第一级 <br>
*                0x95    ---- 第二级 <br>
*                0x97    ---- 第三级 <br>
* @param[out]	uid	-	uid information of current level. [5 Bytes,4字节UID+BCC]
* @return 返回值<br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@else 
* @brief Send anti-collision instructions to the card
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	sel	-	anti-conflict layer <br>
*                0x93    ---- first  level <br>
*                0x95    ---- second  level <br>
*                0x97    ---- third  level <br>
* @param[out]	uid	-	uid information of current level. [5 Bytes,4 bytes UID+BCC]
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif 
*/
int iso14443_Anticollision(int fd, uint8_t sel, void *uid);

/**
@if Chinese
* @brief 给卡片发送select指令 [Type A]
* @param[in]	fd	-	非接读卡器设备文件描述符
* @param[in]	sel	-	防冲突级别 <br>
*       0x93    ---- 第一级 <br>
*       0x95    ---- 第二级 <br>
*       0x97    ---- 第三级
* @param[in]	uid	-	唯一标识符
* @param[out]	sak	-	卡片返回的确认信息，1字节
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数           <br>
*               EIO     ---- 硬件错误           <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误           <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容  <br>
*               EBADE   ---- 卡片返回错误响应信息           <br>
*               ETIME   ---- 超时           <br>
@else 
* @brief Send the select command to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	sel	-	choose layer <br>
*       0x93    ---- first level <br>
*       0x95    ---- second level <br>
*       0x97    ---- third level
* @param[in]	uid	-	Unique Identifier
* @param[out]	sak	-	card returned confirmation, 1 byte
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
@endif 
*/
int iso14443_Select(int fd, uint8_t sel, const void *uid, uint8_t *sak);

/**
@if Chinese
* @brief 获取当前A类卡片的uid
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[out]	uidlen	-	uid长度[unit:Byte]
* @param[out]	uid		-	卡片的uid数据
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else
* @brief Gets the UID of the current class A card
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	uidlen	-	uid length[unit:Byte]
* @param[out]	uid		-	Uid data of the card
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int iso14443_get_typeA_uid(int fd, uint8_t *uidlen, void *uid);

/**
@if Chinese
* @brief 	获取卡片的类型
* @return 	返回卡片的类型值.<br>
*   MIF_TYPE_A          --- TypeA <br>
*   MIF_TYPE_B,         --- TypeB <br>
*   MIF_TYPE_C1,        --- FeliCa, 212kbits/s <br>
*   MIF_TYPE_C2,        --- FeliCa, 424kbits/s <br>
*   MIF_TYPE_UNKNOWN    --- 未知卡类型
@else 
* @brief 	Gets the type of the card
* @return 	Returns the type value of the card.<br>
*   MIF_TYPE_A          --- TypeA <br>
*   MIF_TYPE_B,         --- TypeB <br>
*   MIF_TYPE_C1,        --- FeliCa, 212kbits/s <br>
*   MIF_TYPE_C2,        --- FeliCa, 424kbits/s <br>
*   MIF_TYPE_UNKNOWN    --- Unknown Card Type
@endif 
*/
uint8_t iso14443_get_cardtype(void);

/**
@if Chinese
* @brief 	给卡片发送HALT指令 [Type A]
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief 	Send the HALT instruction to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int iso14443_HaltA(int fd);

/**
@if Chinese
* @brief	发送RATS指令给卡片 [Type A]
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[in]	cid		-	卡片的逻辑卡号, default is 0
* @param[in]	fsdi	-	终端可接收的最大帧长度系数 <br>
*               0  ---- 16 bytes    <br>
*               1  ---- 24 bytes    <br>
*               2  ---- 32 bytes    <br>
*               3  ---- 40 bytes    <br>
*               4  ---- 48 bytes    <br>
*               5  ---- 64 bytes    <br>
*               6  ---- 96 bytes    <br>
*               7  ---- 128 bytes   <br>
*               >=8 ---- 256 bytes  
* @param[out]	atslen	-	应答报文长度
* @param[out]	ats		-	应答报文有效值
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数   <br>
*               EIO     ---- 硬件错误   <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误   <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息   <br>
*               EACCES   --- 射频场中的卡不是T=CL卡   <br>
*               ETIME   ---- 超时   <br>
@else

* @brief	Send the RATS instruction to the card [Type A]
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[in]	cid		-	card number of card, default is 0
* @param[in]	fsdi	-	The maximum frame length coefficient that terminal can receive, values are as follows <br>
*               0  ---- 16 bytes    <br>
*               1  ---- 24 bytes    <br>
*               2  ---- 32 bytes    <br>
*               3  ---- 40 bytes    <br>
*               4  ---- 48 bytes    <br>
*               5  ---- 64 bytes    <br>
*               6  ---- 96 bytes    <br>
*               7  ---- 128 bytes   <br>
*               >=8 ---- 256 bytes  
* @param[out]	atslen	-	length of ATS information that info_len returned
* @param[out]	ats		-	ATS information that info_len returned
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   <br>
@endif 
*/
int iso14443_RATS(int fd, uint8_t cid, uint8_t fsdi, uint8_t *atslen, void *ats);

/**
@if Chinese
* @brief 发送PPSE指令给卡片 [Type A]
* @param[in]	fd	-	非接读卡器设备文件描述符
* @param[in]	cid	-	卡片标识符，同iso14443_rats(…)
* @param[in]	br	-	比特率能力，从PCD到PICC的bit8~bit5码的比特率，,
*  				以及从PICC到PCD的bit4~位码的码率. <br>
*                  0  --- 106kbits/s    <br>
*                  1  --- 212kbits/s    <br>
*                  2  --- 424kbits/s    <br>
*                  3  --- 848kbits/s    <br>
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数   <br>
*               EIO     ---- 硬件错误   <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误   <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息   <br>
*               EACCES  ---  射频场中的卡不是T=CL卡   <br>
*               ETIME   ---- 超时   <br>
@else
* @brief Send the PPSE instruction to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	cid	-	Card Identifier, the same as used in iso14443_rats(...)
* @param[in]	br	-	the bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*   and bit4~bit code bit rate from PICC to PCD. <br>
*                  0  --- 106kbits/s    <br>
*                  1  --- 212kbits/s    <br>
*                  2  --- 424kbits/s    <br>
*                  3  --- 848kbits/s    
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   
@endif 
*/
int iso14443_PPS(int fd, uint8_t cid, uint8_t br);

/**
@if Chinese
* @brief	给卡片发送REQB指令 [Type B]
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	afi			-	所有应用程序的应用程序族标识，类型B. 0
* @param[in]	slotnum		-	槽数,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	回答请求的长度
* @param[out]	atqb		-	回答请求数据
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数   <br>
*               EIO     ---- 硬件错误   <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误   <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息   <br>
*               EACCES  ---  射频场中的卡不是T=CL卡   <br>
*               ETIME   ---- 超时   <br>
@else 
* @brief Send the REQB command to the card [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	afi			-	Application Family Identifier, Type B. 0 for all applications
* @param[in]	slotnum		-	Number of slots,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	information length of ATQB
* @param[out]	atqb		-	ATQB information
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   <br>
@endif 
*/
int iso14443_ReqB(int fd, uint8_t afi, uint8_t slotnum, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief 给卡片发送WUPB指令 [Type B]
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[in]	afi		-	所有应用程序的应用程序族标识，类型B. 0
* @param[in]	slotnum	-	槽数,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out] lenofatqb	-	回答请求的长度
* @param[out] atqb		-	回答请求的数值
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Send the WUPB command to the card [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	afi			-	Application Family Identifier, Type B. 0 for all applications
* @param[in]	slotnum		-	Number of slots,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	the length of Answer To Request
* @param[out]	atqb		-	Answer to Request
* @return <br>
*   <em> 0 </em>    ----success	<br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int iso14443_WupB(int fd, uint8_t afi, uint8_t slotnum, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief 位置标记命令 [Type B]
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	slot		-	时间槽位，根据ReqB或WupB的slotnum参数，取值应小于16
* @param[out]	lenofatqb	-	回答请求的长度
* @param[out]	atqb		-	回答请求的数值
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Slot Marker command [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	slot		-	time slot parameter, 0~15
* @param[out]	lenofatqb	-	information length of ATQB
* @param[out]	atqb		-	ATQB information
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_SlotMarker(int fd, uint8_t slot, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief 给卡片发送ATTRIB指令
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[in]	cid		-	卡标识符
* @param[in]	fsdi	-	PCD整数的帧大小  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  <br>
* @param[in]	uid		-	唯一标识符
* @param[in]	br		-	比特率能力，从PCD到PICC的bit8~bit5码位率，和从PICC到PCD的bit4~码位率<br>
*                  0  --- 106kbits/s  <br>
*                  1  --- 212kbits/s  <br>
*                  2  --- 424kbits/s  <br>
*                  3  --- 848kbits/s  <br>
* @param[out]	len		-	回答Attrib命令的长度
* @param[out]	info	-	对ATTRIB命令的回答
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Send an ATTRIB instruction to the card
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[in]	cid		-	Card Identifier
* @param[in]	fsdi	-	Frame Size for PCD integer  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  <br>
* @param[in]	uid		-	Unique Identifier
* @param[in]	br		-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC, and bit4~bit code bit rate from PICC to PCD<br>
*                  0  --- 106kbits/s  <br>
*                  1  --- 212kbits/s  <br>
*                  2  --- 424kbits/s  <br>
*                  3  --- 848kbits/s  <br>
* @param[out]	len		-	The length of Answer to an Attrib command
* @param[out]	info	-	Answer of to an ATTRIB Command
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_AttriB(int fd, uint8_t cid, uint8_t fsdi, const void *uid, uint8_t br, uint8_t *len, void *info);

/**
@if Chinese
* @brief PICC选择命令，设置T=CL [Type B]
* @param[in]	fd		-	设备id，返回mif_open(…)
* @param[in]	cid		-	卡标识符
* @param[in]	fsdi	-	PCD整数的帧大小  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  
* @param[in]	uid	-	唯一标识符
* @param[in]	br	-	比特率能力，从PCD到PICC的bit8~bit5码的比特率，
*       				以及从PICC到PCD的bit4~位码的码率 <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s 
* @param[out]	len		-	回答Attrib命令的长度
* @param[out]	info	-	对ATTRIB命令的回答
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief PICC selection command, set T=CL [Type B]
* @param[in]	fd		-	Device id, return from mif_open(...)
* @param[in]	cid		-	Card Identifier
* @param[in]	fsdi	-	Frame Size for PCD integer  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  
* @param[in]	uid		-	Unique Identifier
* @param[in]	br		-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*       and bit4~bit code bit rate from PICC to PCD <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s 
* @param[out]	len		-	The length of Answer to an Attrib command
* @param[out]	info	-	Answer of to an ATTRIB Command
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_AttriB(int fd, uint8_t cid, uint8_t fsdi, const void *uid, uint8_t br, uint8_t *len, void *info);

/**
@if Chinese
* @brief 给卡片发送HALTB指令 [Type B]
* @param[in]	fd	-	非接读卡器设备文件描述符
* @param[in]	uid	-	唯一标识符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Send the HALTB command to the card [Type B]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	uid	-	Unique Identifier
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_HaltB(int fd, const void *uid);

// contactless card type definition

#define MIF_M1_S50          0x00	/**<@if Chinese 	非接触式读卡器S50	@else mifare classic S50 @endif*/
#define MIF_M1_S70          0x01	/**<@if Chinese 	非接触式读卡器S70	@else mifare classic S70 @endif*/
#define MIF_ULTRALIGHT      0x02	/**<@if Chinese 	简约型非接触式读卡器	@else mifare Ultralight @endif*/
#define MIF_DESFIRE         0x03	/**<@if Chinese 	非接触式读卡器D40或EV1	@else mifare DESFire D40 or EV1 @endif*/
#define MIF_PRO             0x04	/**<@if Chinese 	非接触式读卡器ProX	@else mifare ProX @endif*/
#define MIF_PRO_S50         0x05	/**<@if Chinese 	mifare ProX和嵌入mifare经典S50，兼容T=CL协议	@else mifare ProX and embed mifare classic S50,compatible with T=CL protocol @endif*/
#define MIF_PRO_S70         0x06	/**<@if Chinese 	mifare ProX和嵌入mifare经典S70，兼容T=CL协议	@else mifare ProX and embed mifare classic S70,compatible with T=CL protocol @endif*/
#define MIF_TYPEB           0x07	/**<@if Chinese 	ISO14443类型b，与T=CL协议不兼容	@else ISO14443 TypeB, and not compatible with T=CL protocol @endif*/
#define MIF_TYPEB_TCL       0x08	/**<@if Chinese 	ISO14443类型b，与T=CL协议兼容	@else ISO14443 TypeB, and compatible with T=CL protocol @endif*/
#define MIF_FELICA          0x09	/**<@if Chinese 	索尼菲利卡	@else Sony FeliCa @endif*/
#define MIF_UNKNOWEN_TYPEA  0x0A	/**<@if Chinese 	ISO14443类型a，与T=CL协议不兼容	@else ISO14443 TypeA, and not compatible with T=CL protocol @endif*/

/**
@if Chinese
* @brief 在RF字段中轮询T=CL卡，并返回卡信息
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	mode		-	轮询方式，取值为:<br>
*                  0  --- 只轮询现在处于IDLE状态的T=CL卡  <br>
*                  1  --- 轮询现在处于IDLE状态和HALT状态的T=CL卡   
* @param[out]	cardinfo_len	-	T=CL卡信息的长度
* @param[out]	cardinfo	-	T=CL卡信息. T=CL卡信息如下: <br>
*                           cardinfo[0] --- return the T=CL card type, refer to contactless card type definition. <br>
*                           for TypeA, the following information is ATQA[2bytes] + UidLen(1byte) + Uid(UidLen bytes) + SAK(1byte) <br>
*                           for TypeB, the follwoing information is ATQB[12bytes] 
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Poll the RF field for T=CL card, and return the card information
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	mode		-	Poll mode, value can be:<br>
*                  0  --- only poll the T=CL cards which in IDLE state now  <br>
*                  1  --- poll the T=CL cards which in IDLE state and HALT state now  
* @param[out]	cardinfo_len	-	The length of T=CL card information
* @param[out]	cardinfo	-	the T=CL card information. the cardinfo organized as following: <br>
*                           cardinfo[0] --- return the T=CL card type, refer to contactless card type definition. <br>
*                           for TypeA, the following information is ATQA[2bytes] + UidLen(1byte) + Uid(UidLen bytes) + SAK(1byte) <br>
*                           for TypeB, the follwoing information is ATQB[12bytes] 
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_poll(int fd, int mode, uint8_t *cardinfo_len, void *cardinfo);

/**
@if Chinese
* @brief 激活感应区内的T=CL卡
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[in]	cid		-	卡片的逻辑卡号
* @param[in]	br		-	终端与卡片之间的通信波特率参数，具体取值如下: <br>
					高4位为终端到卡片的通信速率， <br>
*       			低4位为卡片到终端的通信速率， <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s <br>
* @param[in]	fsdi	-	终端可接收的最大帧长度系数   <br>
*               0 ---- 16bytes   <br>
*               1 ---- 24bytes   <br>
*               2 ---- 32bytes   <br>
*               3 ---- 40bytes   <br>
*               4 ---- 48bytes   <br>
*               5 ---- 64bytes   <br>
*               6 ---- 96bytes   <br>
*               7 ---- 128bytes   <br>
*               8 ---- 256bytes   <br>
*               其它值 ---- 256bytes   <br>
* @param[out]	info_len	-	TypeA 卡：<br>
							info_len返回ATS信息的长度 <br>
						  TypeB 卡：<br>
							做为输入时，info_len指ArttriB命令中Higher-layer INF信息的长度；<br>
							做为输出时，info_len返回卡片的响应数据长度
* @param[out]	info	-	TypeA 卡：<br>
							info_len返回ATS信息 <br>
						  TypeB 卡：<br>
							做为 输入时，info 指AttriB命令中Higher-Layer INF信息；<br>
							做为输出时，info返回卡片的响应数据
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Active T=CL card in inductive zone
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	cid	-	The logical card no, usually is set as 0
* @param[in]	br	-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*       and bit4~bit code bit rate from PICC to PCD <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s <br>
* @param[in]	fsdi	-	The maximum frame length coefficient that terminal can receive, values are as follows   <br>
*               0 ---- 16bytes   <br>
*               1 ---- 24bytes   <br>
*               2 ---- 32bytes   <br>
*               3 ---- 40bytes   <br>
*               4 ---- 48bytes   <br>
*               5 ---- 64bytes   <br>
*               6 ---- 96bytes   <br>
*               7 ---- 128bytes   <br>
*               8 ---- 256bytes   <br>
*               other ---- 256bytes   <br>
* @param[out]	info_len	-	The length of card information
* @param[out]	info		-	Card Information. <br>
*                   For Type A, the info field is organized  as following: <br>
*                       Card Type(1byte) || ATQA(2bytes) || uid len(1byte) || uid (uidlen bytes) <br>
*                   For TypeB, the info field is organized as following: <br>
*                       Card Type(1byte) || ATQB(12/13bytes) 
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_active(int fd, uint8_t cid, uint8_t br, uint8_t fsdi, uint8_t *info_len, void *info);

/**
@if Chinese
* @brief 在PCD和PICC之间交换T=CL数据包
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	sendlen		-	发送到PICC的数据包长度
* @param[in]	senddata	-	发送到PICC的数据包
* @param[out]	recvlen		-	从PICC返回的数据包长度
* @param[out]	recvdata	-	从PICC返回的数据包
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Exchange T=CL data packet between PCD and PICC
* @param[in]	fd			-	Non-access card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief	复位射频场所有卡，使其进入IDLE状态
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief	Reset all card in RF field, and put them into IDLE state
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_deactive(int fd);

/**
@if Chinese
* @brief PCD和PICC之间的数据交换，不组织在ISO14443 T=CL数据包中
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	sendlen		-	发送到PICC的数据包长度
* @param[in]	senddata	-	发送到PICC的数据包
* @param[in]	timeout		-	等待时间(单位:etu)
* @param[out]	recvlen		-	从PICC返回的数据包长度
* @param[out]	recvdata	-	从PICC返回的数据包
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Exchange data between PCD and PICC, not organized in ISO14443 T=CL data packet
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[in]	timeout		-	Wait time (unit:etu)
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_no_tcl_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata, uint32_t timeout);

/**
@if Chinese
* @brief	检查射频场是否有多个卡
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数   <br>
*               EIO     ---- 硬件错误   <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误   <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息   <br>
*               EACCES  ---  射频场中的卡不是T=CL卡  <br>
*               ETIME   ---- 超时   <br>
@else 
* @brief Check if more than one card in RF field
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout during poll card   <br>
@endif 
*/
int iso14443_check_multi_card(int fd);

/**
@if Chinese
* @brief 在PCD和索尼FeliCa之间交换数据
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	sendlen		-	发送到PICC的数据包长度
* @param[in]	senddata	-	发送到PICC的数据包
* @param[in]	timeout		-	等待时间(单位:etu)
* @param[out]	recvlen		-	从PICC返回的数据包长度
* @param[out]	recvdata	-	从PICC返回的数据包
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容    <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
@else 
* @brief Exchange data between PCD and Sony FeliCa
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[in]	timeout		-	Wait time (unit:etu)
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int felica_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata, uint32_t timeout);

/*! 
@if Chinese
	@brief	EMV模式下的卡片状态定义 
@else
	@brief	Card state definition in EMV mode
@endif 
*/
enum {
    NFC_OP_NULL         = 0x00, /**<@if Chinese 0 : 未初始化状态 	@else	0: uninitialized		@endif*/
    NFC_OP_POLL,            	/**<@if Chinese 1 : 轮询卡片 		@else	1: polling cards		@endif*/
    NFC_OP_ANTICOLL,        	/**<@if Chinese 2 : 防冲突处理 		@else	2: anti-conflict processing	@endif*/
    NFC_OP_REMOVE,          	/**<@if Chinese 3 : 移除卡片, 应用程序获取不到此状态, emv_contactless_deactive_picc返回即表示移卡完成 @else	3: The card is removed. The application program cannot obtain the status. If emv_ContactLess_deactive_PICc returns, the card is removed	@endif*/
    NFC_OP_EXCHANGE_APDU,   	/**<@if Chinese 4:  数据交换 		@else	4: Data exchange		@endif*/
};

/**
@if Chinese
* @brief	打开电磁场，检测感应区内IC卡
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效的参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 奇偶校验错误或CRC错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容    <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡   <br>
*               ETIME   ---- 超时    <br>
* @note 如果射频场超过2张卡，我们就不能激活这两张卡
*       这个函数不是BLOCK函数，它会立即退出.
@else 
* @brief	Open the electromagnetic filed and check card
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
* @note If more than 2 cards in RF field, we can't active neither of it
*       this function is not a BLOCK function, it will quit immediately.
@endif 
*/
int emv_contactless_active_picc(int fd);

/**
@if Chinese
* @brief 移开卡片，检测到卡片移开后关闭电场
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 校验错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
@else 
* @brief Wait until the card remove out of the RF field, then close the electromagnetic field.
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_deactive_picc(int fd);

/**
@if Chinese
* @brief 移开卡片，检测到卡片移开后关闭电场
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 校验错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
* @note 和emv_contactless_deactive_picc()的区别在于该接口非阻塞
@else 
* @brief Wait until the card remove out of the RF field, then close the electromagnetic field.
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed,You can obtain the error code according to errno:<br>
*				EINVAL	---- invalid argument    <br>
*				EIO		---- hardware error    <br>
*				ECOMM	---- Parity Error or CRC error    <br>
*				EPROTO	---- the response from card not compatile with ISO14443    <br>
*				EBADE	---- card return error response information    <br>
*				EACCES   ---  The card in RF field is not a T=CL card    <br>
*				ETIME	---- timeout during poll card    <br>
* @note The difference from emv_contactLess_deactive_picc () is that this interface is non-blocking
@endif 
*/
int emv_contactless_deactive_picc_nonblock(int fd);

/**
@if Chinese
* @brief 获取当前操作状态.
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[out]	status	-	当前操作状态等。NFC_OP_POLL NFC_OP_ANTICOLL
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 校验错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
@else 
* @brief Get current operation status.
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	status	-	Current operation status, et. NFC_OP_POLL NFC_OP_ANTICOLL
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_obtain_status(int fd, int *status);

/**
@if Chinese
* @brief 获取轮询期间的最后错误代码，防冲突，激活，交换，取消激活。
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[out]	error	-	最后一个错误代码
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 校验错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
@else 
* @brief Get last error code during the poll, prevent(collision, active, exchange, deactive).
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	error	-	Last error code
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_get_lasterror(int fd, int *error);

/**
@if Chinese
* @brief PCD与PICC交换APDU数据
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	sendlen		-	要发送的数据长度(以字节为单位)
* @param[in]	senddata	-	要发送的数据值
* @param[out]	recvlen		-	接收数据的长度(以字节为单位)
* @param[out]	recvdata	-	接收的数据值
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.以下为错误码映射信息:<br>
*               EINVAL  ---- 无效参数    <br>
*               EIO     ---- 硬件错误    <br>
*               ECOMM   ---- 校验错误    <br>
*               EPROTO  ---- 卡片的响应与ISO14443不兼容   <br>
*               EBADE   ---- 卡片返回错误响应信息    <br>
*               EACCES  ---  射频场中的卡不是T=CL卡    <br>
*               ETIME   ---- 超时    <br>
@else 
* @brief Exchange APDU data between PCD and PICC
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The length of data (in bytes) to send
* @param[in]	senddata	-	The data to be send to PICC
* @param[out]	recvlen		-	The length of data (in bytes) that received
* @param[out]	recvdata	-	The data that received from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_exchange_apdu(int fd, uint32_t sendlen, const void *senddata,
                                  uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief 从PCD发送数据到PICC非阻塞，发送后立即返回
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[in]	sendlen		-	要发送的数据长度(以字节为单位)
* @param[in]	senddata	-	要发送的数据
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Send data from PCD to PICC nonblock, after sending return immediately
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The length of data (in bytes) to send
* @param[in]	senddata	-	The data to be send to PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed,You can obtain the error code according to errno.
@endif 
*/
int emv_contactless_exchange_apdu_nonblock_send(int fd, uint32_t sendlen, const void *senddata);

/**
@if Chinese
* @brief 从PICC获取数据
* @param[in]	fd			-	非接读卡器设备文件描述符
* @param[out]	error		-	返回交换过程中的错误，如ETIME, EPROTO等。<br>
*                   			如果错误不等于0，这意味着错误发生了，并且交换已停止，尝试再次发送APDU或去激活。
* @param[out]	status		-	显示当前运行状态:NFC_OP_POLL、NFC_OP_ANTICOLL、NFC_OP_ANTICOLL、NFC_OP_REMOVE。
* @param[out]	finish		-	1:交换完成，然后从参数recvlen和recvdata获取响应数据。<br>
*                     			0:未完成，等待完成。如果发生错误(第一个参数error != 0)，则无需进一步等待。
* @param[out]	recvlen		-	当finish == 1时，接收到的数据长度(以字节为单位)。
* @param[out]	recvdata	-	当finish == 1时，从PICC接收到的数据
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief Get response data from PICC
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[out]	error		-	Return the error during exchange, such as ETIME, EPROTO etc.<br>
*                     			if error not equal 0, that means error occur, and exchange stopped, try send APDU again or deactive.
* @param[out]	status		-	Show current operation state:NFC_OP_POLL, NFC_OP_ANTICOLL, NFC_OP_ANTICOLL, NFC_OP_REMOVE.
* @param[out]	finish		-	1:exchange finish, then get response data from parameter recvlen and recvdata.<br>
*                     			0:not finish, wait until finish. If error occur(the first parameter error != 0), no need to wait further.
* @param[out]	recvlen		-	When finish == 1, the length of data (in bytes) that received.
* @param[out]	recvdata	-	When finish == 1, the data that received from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int emv_contactless_exchange_apdu_nonblock_response(int fd, int *error, int *status, int *finish, uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief	只有在使用API“emv_contactless_exchange_apdu_nonblock_send”发送数据时，终止当前交换
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief	Abort current exchange, only if using API "emv_contactless_exchange_apdu_nonblock_send" to send data
* @param[in]	fd	-	Emv card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int emv_contactless_exchange_apdu_nonblock_abort(int fd);

int nfc_get_reg_param(int fd, void *buf, int *nr_reg);
int nfc_set_reg_param(int fd, const void *buf, int nr_reg);
#if 0
int nfc_start_status_notify(int fd, int *status);
int nfc_wait_status_changed(int fd, int *status, int timeout);
int nfc_stop_status_notify(void);
#endif
/**
@if Chinese
* @brief	将非接读卡器复位为ISO14443模式
* @param[in]	fd	-	非接读卡器设备文件描述符
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief	Reset the non-access card reader to ISO14443 mode
* @param[in]	fd	-	nfc card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int nfc_reset_iso144443(int fd);

/**
@if Chinese
* @brief 打开/关闭场强
* @param[in]	fd		-	非接读卡器设备文件描述符
* @param[in]	onoff	-	打开或关闭，参数为CARRIER_OFF 或 CARRIER_ON
* @return 返回值<br>
*   <em> 0 </em>    ----成功    <br>
*   <em> -1 </em>   ----失败, 可根据errno获取错误码.
@else 
* @brief open/close field
* @param[in]	fd		-	nfc card device file descriptor
* @param[in]	onoff	-	Turn it on or off with the parameter CARRIER_OFF or CARRIER_ON
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif  
*/
int nfc_carrier_control(int fd, uint8_t onoff);

#define CARRIER_OFF              0x00       /**<@if Chinese 关闭场强 @else	Close the field strength	@endif*/
#define CARRIER_ON               0x01       /**<@if Chinese 开启场强 @else	Open field	@endif*/

#ifdef CFG_EMV_L1_TEST

/**
@if Chinese
	* @brief 仅用于对非接EMV-L1认证
@else 	
	* @brief It is used only for emV-L1 authentication
@endif 	
 */
int emv_L1_transac_a_test(void);
int emv_L1_transac_b_test(void);
int emv_set_exit_flag(int flag);
int emv_L1_digital_test(void);
int emv_set_cmd_flag(int flag);

int nfc_set_time_param(int fd, nfc_time_param_t *time_param);
int nfc_get_time_param(int fd, nfc_time_param_t *time_param);
int nfc_time_optimize_ctl(int fd, int on_off);
int nfc_time_optimize_status(int fd, int *on_off);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONTACTLESS_H_ */

/** @} */
