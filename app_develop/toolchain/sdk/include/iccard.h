/**
@if Chinese
 * @brief  此模块用于描述 <strong>接触式IC卡模块</strong> 相关的接口
 * @author      jeffery
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * 日期          | 版本          | 作者            | 描述
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | jeffery         | 创建文件
 * 2022/04/20    | 1.0.1         | Wenming         | 增加英文注释
@else 
 * @brief  This module is used to describe <strong>IC Card</strong> interfaces module
 * @author      jeffery
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | jeffery         | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
@endif
 */


/**
@if Chinese
 * @defgroup iccard IC卡
@else
 * @defgroup iccard IC Card
@endif 
 * @{
*/


#ifndef __ICCARD_H__
#define __ICCARD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CVCC_1_8_VOLT       1   /**<@if Chinese IC卡VCC类型: 1.8v 		@else IC card VCC mode: 1.8v 			@endif*/
#define CVCC_3_VOLT         2   /**<@if Chinese IC卡VCC类型: 3v 		@else IC card VCC mode: 3v 				@endif*/
#define CVCC_5_VOLT         3   /**<@if Chinese IC卡VCC类型: 5v 		@else IC card VCC mode: 5v 				@endif*/

#define EMV_MODE            0   /**<@if Chinese 操作模式: EMV 			@else operation mode: EMV 				@endif*/
#define ISO_MODE            1   /**<@if Chinese 操作模式: ISO standard 	@else operation mode: ISO standard 		@endif*/
#define ISO_19200           2   /**<@if Chinese 操作模式: ISO 19200 	@else operation mode: ISO 19200 		@endif*/
#define ISO_38400           3   /**<@if Chinese 操作模式: ISO 38400 	@else operation mode: ISO 38400 		@endif*/

#define ISO_SPEED_NORMAL   0
#define ISO_SPEED_HIGH   (3<<30)

/**
@if Chinese
 * @brief          打开IC卡读卡器
 * @param[in]	filename	-	卡槽的名字
 * @return	>=0		-	设备id，用于读取IC卡信息的API函数使用
 * @return	-1		-	失败，请检查“errno”的实际错误码
@else 
 * @brief          open ic card reader device
 * @param[in]	filename	-	card slot name
 * @return	>=0	-	device id, used by following reader api function
 * @return	-1	-	failed, please check "errno" for actual error code
@endif 
*/
int iccard_open_cardslot(const char *filename);


/**
@if Chinese
 * @brief         关闭IC卡读卡器
 * @param[in]     fd	-	打开读卡器的句柄, 函数 @link iccard_open_cardslot iccard_open_cardslot @endlink的返回值
 * @return	0	-	成功
 * @return	-1	-	失败，请检查“errno”的实际错误码
@else 
 * @brief         close ic card reader device
 * @param[in]     fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return	0	-	success
 * @return	-1	-	failed, please check "errno" for actual error code
@endif 
*/
int iccard_close_cardslot(int fd);


/**
@if Chinese
 * @brief          检查卡是否存在于卡槽中
 * @param[in]      fd	-	打开读卡器的句柄, 函数 @link iccard_open_cardslot iccard_open_cardslot @endlink的返回值
 * @return	0		-	卡在卡槽中
 * @return	-1		-	失败，请检查“errno”的实际错误码
 * @return	ENXIO	-	卡未在卡槽中
@else 
 * @brief          check if card existed in slot
 * @param[in]      fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return	0		-	card in slot
 * @return	-1		-	failed, please check "errno" for actual error code
 * @return	ENXIO	-	card not in slot
@endif 
*/
int iccard_check_card_in_slot(int fd);


/**
@if Chinese
 * @brief         IC卡上电
 * @param[in]     fd	-	打开读卡器的句柄, 函数 @link iccard_open_cardslot iccard_open_cardslot @endlink的返回值
 * @param[in]     vcc	-	VCC卡的值:
 *          		-	CVCC_1_8_VOLT  
 *          		-	CVCC_3_VOLT   
 *         			-	CVCC_5_VOLT  
 * @param[in]     mode	-	操作卡类型:
 *          		-	ISO_MODE        ----- iso7816 类型 
 *          		-	EMV_MODE        ----- EMV specification 类型  
 *          		-	ISO_19200       ----- 快速卡 iso7816 类型, 19200bps
 *          		-	ISO_38400       ----- 快速卡 iso7816 类型, 38400bps
 * @param[out]    len	-	atr信息长度
 * @param[out]    atr	-	atr信息
 * @return         
 *          0		-成功<br>
 *          -1      -失败，请检查“errno”的实际错误码<br>
 *          ENXIO   -卡未在卡槽<br>
 *          EINVAL  -无效的参数<br>
 *          ETIME   -读卡超时<br>
 *          ECOMM   -奇偶校验错误或edc错误<br>
 *          EPROTO  -来自iccard的无效信息
 
@else
 * @brief         reset cpucard and get the atr information
 * @param[in]     fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @param[in]     vcc	-	card operation vcc value:
 *          		-	CVCC_1_8_VOLT    ----- 1.8v voltage
 *          		-	CVCC_3_VOLT      ----- 3v voltage
 *          		-	CVCC_5_VOLT      ----- 5v voltage
 * @param[in]     mode	-	card operation mode:
 *          		-	ISO_MODE        ----- iso7816 mode
 *          		-	EMV_MODE        ----- EMV specification mode
 *          		-	ISO_19200       ----- higher rate iso7816 mode, 19200bps
 *          		-	ISO_38400       ----- higher rate iso7816 mode, 38400bps
 * @param[out]    len	-	length of atr information
 * @param[out]    atr	-	atr information
 * @return         
 *          0       -success<br>
 *          -1      -failed, please check "errno" for actual error code<br>
 *          ENXIO   -card  not in slot<br>
 *          EINVAL  -invalid argument<br>
 *          ETIME   -timeout<br>
 *          ECOMM   -parity error or edc error<br>
 *          EPROTO  -invalid information from iccard<br>
@endif 
*/
int iccard_power_up(int fd, int vcc, int mode, int *len, void *atr);


/**
@if Chinese
 * @brief        在读卡器和iccard之间交换apdu包（读卡器和IC卡进行交互信息）
 * @param[in]    fd        
				- 打开读卡器的句柄, 函数 @link iccard_open_cardslot iccard_open_cardslot @endlink的返回值
 * @param[in]    sendlen   
				- APDU发送数据的长度
 * @param[in]    senddata  
				- APDU发送数据的值
 * @param[out]   recvlen   
				- APDU接收数据的长度
 * @param[out]   recvdata  
				- APDU接收数据的值
 * @return        
 *          - 0       成功
 *          - -1      失败，请检查“errno”的实际错误码
 *          - ENXIO   卡未在卡槽
 *          - EINVAL  无效的参数
 *          - ETIME   超时
 *          - ECOMM   奇偶校验错误或edc错误
 *          - EPROTO  无效信息
 *          - EACCES  卡片需要先重置
@else 
 * @brief         Send C-APDU to ICCard, and receive R-APDU from ICCard
 * @param[in]     fd        
				- device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @param[in]     sendlen   
				- length of c-apdu information
 * @param[in]     senddata  
				- c-apdu information
 * @param[out]    recvlen   
				- length of r-apdu information from iccard
 * @param[out]    recvdata  
				- r-apdu information from iccard
 * @return     
 *          - 0       success
 *          - -1      failed, please check "errno" for actual error code
 *          - ENXIO   card  not in slot
 *          - EINVAL  invalid argument
 *          - ETIME   timeout
 *          - ECOMM   parity error or edc error
 *          - EPROTO  invalid information from iccard
 *          - EACCES  card need be reset first
@endif 
*/
int iccard_exchange_apdu(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);


/**
@if Chinese
 * @brief          IC卡下电
 * @param[in]      fd  
				- 打开读卡器的句柄, 函数 @link iccard_open_cardslot iccard_open_cardslot @endlink的返回值
 * @return        
 *          	- 0       成功
 *          	- -1      失败，请检查“errno”的实际错误码
@else 
 * @brief          power down iccard
 * @param[in]      fd  
				- device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return         
 *          - 0       success
 *          - -1      failed, please check "errno" for actual error code
@endif 
*/
int iccard_power_down(int fd);

#if 0 //这个接口功能与ped获取卡座号的接口有重合，可以删除
/**
 * @brief          obtain the number of slot, this function used by ped
 * @param          fd  - device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return        
 *          >=0     ----- slot number
 *          -1      ----- failed, please check "errno" for actual error code
*/
int iccard_get_slotnum(int fd);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ICCARD_H__ */

/** @} */

