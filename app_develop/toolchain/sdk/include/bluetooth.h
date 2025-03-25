/**
 * @file    bt.h
 *          
 * @author  Brian.Yang <brian.yang@newpostech.com>.
 *          
 * @date    2018-06-21
 *          
 * @brief  Bluetooth api   
 *          
 * @note    
 *          
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * 2019-08-06   1.0.1   Milton.Wu     Add doxygen comment
 * ----------------------------------------------------------------------------
 *
 */
/** 
* @defgroup bluetooth 蓝牙
* @{
*/ 
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name BT_PARIING_MODE 蓝牙配对模式
 * @{
 */ 
#define PAIRING_MODE_PINCODE        (0x00)
#define PAIRING_MODE_JUSTWORK       (0x01)
#define PAIRING_MODE_PASSKEY        (0x02)
#define PAIRING_MODE_CONFIRM        (0x03)
/**
 * @}
 */

/**
 * @name BT_VISIBLE_MODE 蓝牙可识别模式 
 * @{
 */ 
#define VISIBLE_BT                  (0x03)      /**< bit0:BT3.0 可发现;bit1::BT3.0 可连接 */
#define VISIBLE_BLE                 (0x04)      /**< bit2:BLE 可发现（ADV 广播）*/
#define VISIBLE_ALL                 (VISIBLE_BT | VISIBLE_BLE) 
/**
 * @}
 */

#define BT_ON                       (0x01)    /**< 打开电压检测*/  
#define BT_OFF                      (0x00)    /**< 关闭电压检测*/

#define BT_MATCH_OK                 (0x00)    /**< CONFIRM_GKEY密钥匹配 */
#define BT_MATCH_ERR                (0x01)    /**< CONFIRM_GKEY密钥不匹配 */

/**
 *@if CN
	* @name BT_PAIRING_STATUS 蓝牙配对状态
 *@else
	* @name BT_PAIRING_STATUS bluetooth Bluetooth pairing status
 * @{
 */
#define PAIRING_IDLE                (0x0) /**< @if CN  无配对 @else pairing idle @endif*/
#define PAIRING_FAIL                (0x1) /**< @if CN  配对失败 @else pairing fail @endif*/
#define PAIRING_SUCCESS             (0x2) /**< @if CN  配对成功 @else pairing succcess @endif*/
#define PAIRING_SET_PASSKEY         (0x3) /**< @if CN  手机端显示PASSKEY @else The PASSKEY is displayed on mobile phone @endif*/
#define PAIRING_GET_PASSKEY         (0x4) /**< @if CN  获取到PASSKEY值，在手机输入对应的PASSKEY值进行配对 @else Gets the PASSKEY value, input the corresponding PASSKEY value into the phone for pairing @endif*/
#define PAIRING_BT_COMFIRM          (0x5) /**< @if CN  BT请求COMFIRM @else BT request COMFIRM @endif*/
#define PAIRING_BLE_COMFIRM         (0x6) /**< @if CN  BLE请求COMFIRM @else BLE request COMFIRM @endif*/

/**
 * @brief     打开蓝牙设备，并返回设备文件描述符
 * @param[in] filename 设备文件名 "/dev/bt"
 * @param[in] oflags   打开选项
 * @return   设备的文件描述符 <br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_open(const char *filename, int oflags);

/**
 * @brief     关闭蓝牙设备
 * @param[in] fd 设备的文件描述符
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_close(int fd);

/**
 * @brief     蓝牙数据发送
 * @param[in] fd 设备的文件描述符
 * @param[in] data 发送数据
 * @param[in] data_len 发送数据长度
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----发送数据长度 <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_send(int fd, const void *data, uint32_t data_len);

/**
 * @brief     接收蓝牙数据
 * @param[in] fd 设备的文件描述符
 * @param[in/out] data 接收数据
 * @param[in] data_len 最大接收数据长度
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----接收数据长度 <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_recv(int fd, void *data, uint32_t data_len);

/**
 * @brief     重启蓝牙
 * @param[in] fd 设备的文件描述符
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_reset(int fd);

/**
 * @brief     请求蓝牙状态 
 * @param[in] fd 设备的文件描述符
 * @return    模块状态<br>
 *   <em> bit5: </em>     BLE 已连接
 */
int bt_get_status(int fd);

/**
 * @brief     断开蓝牙连接
 * @param[in] fd 设备的文件描述符
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
int bt_disconnect(int fd);

/*不支持bt_standby_enable和bt_standby_disable*/
int bt_standby_enable(int fd);
int bt_standby_disable(int fd);

/**
 * @brief    获取蓝牙名称  
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] name_str   用于存储name的buffer
 * @param[in] str_len    buffer大小，建议最小33字节, 因为要存储结尾符'\0'
 * @return    蓝牙名称长度<br>
 *   <em> >= 0 </em>     ----strlen(name_str) <br>
 *   <em> <0 </em>     ----failed, 可根据errno获取错误码
 */
int bt_get_name(int fd, char *name_str, int str_len);

/**
 * @brief     设置蓝牙名称  
 * @param[in] fd         设备的文件描述符 
 * @param[in] name_str   用于存储name的buffer
 * @param[in] str_len    strlen(name_str)
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */ 
int bt_set_name(int fd, const char *name_str, int str_len);

/*不支持获取pincode*/
int bt_get_pincode(int fd, void *data, int len);

/**
 * @brief     设置蓝牙PIN码
 * @param[in] fd         设备的文件描述符 
 * @param[in] data       用于存储PIN码的buffer
 * @param[in] len        PIN长度
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */ 
/*不支持bt_set_pincode*/
int bt_set_pincode(int fd, const void *data, int len);

/**
 * @brief     查询蓝牙固件版本号
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] data   用于存储固件的buffer
 * @param[in] len        data大小,最低2字节
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----版本信息实际长度 <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */
/*不支持bt_get_version*/
int bt_get_version(int fd, void *data, int len);

/**
 * @brief     查询蓝牙固件版本号和@ref bt_get_version() 查询结果相同
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] data   用于存储固件的buffer
 * @param[in] len        data大小,最低2字节
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----版本信息实际长度 <br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */ 
/*不支持bt_eeprom_version*/
int bt_eeprom_version(int fd, void *data, int len);

/**
 * @brief     获取蓝牙MAC地址 
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] data   MAC地址的buffer
 * @param[in] len        data大小,最低6字节
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----MAC实际长度<br>
 *   <em> else </em>     ----failed, 可根据errno获取错误码
 */ 
int bt_local_addr(int fd, void *data, int len);

/**
 * @brief     设置蓝牙MAC地址 
 * @param[in] fd         设备的文件描述符 
 * @param[in] data       MAC数据
 * @param[in] len        MAC数据大小，6字节
 * @return    返回值<br>
 *   <em> = 0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */ 
/*不支持bt_set_local_addr*/
int bt_set_local_addr(int fd, const void *data, int len);

/**
 * @brief     获取配对信息
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] data   存储配对信息的buffer
 * @param[in] len        buffer大小，安全起见，要求最低170字节
 * @return    返回值<br>
 *   <em> > 0 </em>     ----获取的数据大小<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */  
int bt_paired_info_get(int fd, void *data, int len);

/**
 * @brief     擦除配对信息,擦除后获取的配对信息长度为120字节或170字节，但是数据应该为全0
 * @param[in] fd         设备的文件描述符 
 * @return    返回值<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */   
int bt_paired_info_erase(int fd);

/**
 * @brief     设置配对模式
 * @param[in] fd         设备的文件描述符 
 * @param[in] mode       配对模式,取值参考@ref BT_PARIING_MODE
 * @return    返回值<br>
 *   <em> >=0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */  
int bt_pairing_mode_set(int fd, uint8_t mode);

/**
 * @brief     获取配对模式
 * @param[in] fd         设备的文件描述符 
 * @param[in] mode       配对模式,取值参考@ref BT_PARIING_MODE
 * @return    返回值<br>
 *   <em> >=0 </em>     ----配对模式 取值参考@ref BT_PARIING_MODE<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */
int bt_pairing_mode_get(int fd);

/**
 * @brief     输入passkey，固定4字节
 * @param[in] fd         设备的文件描述符 
 * @param[in] data       存储passkey的buffer
 * @param[in] len        passkey长度，4字节
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 * @note    passkey为配对时手机需要输入的6位数字 <br>
 *      如uint32_t passkey = 123456，手机需要输入123456
 */
int bt_entry_passkey(int fd, const void *data, int len);

/**
 * @brief     阻塞等待(timeout_sec)秒,直到进入PASSKEY模式或等待超时
 * @param[in] fd         设备的文件描述符 
 * @param[in] timeout_sec  等待超时时间，单位:秒
 * @return    返回值<br>
 *   <em> =0 </em>      ----成功进入PASSKEY配对状态，下一步允许输入PASSKEY<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 * @note    对于PASSKEY配对模式<br>
 *      1.先调用@ref bt_pairing_mode_set() 设置配对模式为@ref PAIRING_MODE_PASSKEY
 *      2.再调用接口@ref bt_entry_passkey_paired()，然后手机发起配对，此接口返回
 *      3.调用@ref bt_entry_passkey() 输入手机端显示的PASSKEY，完成配对
 */ 
int bt_entry_passkey_paired(int fd, unsigned long timeout_sec);

/**
 * @brief     设置蓝牙的可发现和广播状态
 * @param[in] fd         设备的文件描述符 
 * @param[in] visible_mode  可见模式,取值参考@ref BT_VISIBLE_MODE
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */ 
/*不支持bt_set_visible*/
int bt_set_visible(int fd, uint8_t visible_mode);
/*不支持bt_set_uart_baud*/
int bt_set_uart_baud(int fd, const char *baud_str);

/**
 * @brief     设置蓝牙BT3.0 class of device
 * @param[in] fd         设备的文件描述符 
 * @param[in] data       用于存储cod的buffer
 * @param[in] len        cod长度, 3字节
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */ 
 /*不支持bt_set_cod*/
int bt_set_cod(int fd, const void *data, int len);

/**
 * @brief     让蓝牙进入睡眠模式
 * @param[in] fd         设备的文件描述符 
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */ 
/*不支持bt_enter_sleep*/
int bt_enter_sleep(int fd);

/**
 * @brief     设置BLE ADV DATA(低功耗蓝牙广播数据)
 * @param[in] fd         设备的文件描述符 
 * @param[in] data       用于存储ADV的buffer
 * @param[in] len        ADV长度,范围:1-62
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 */
/*不支持bt_set_adv_data*/
int bt_set_adv_data(int fd, const void *data, int len);

/**
 * @brief     查询模块电源电压
 * @param[in] fd         设备的文件描述符 
 * @param[in/out] data    用于存储电压的buffer
 * @param[in] len         buffer大小,最小为2
 * @return    返回值<br>
 *   <em> >=0 </em>      ----存储电压buffer长度<br>
 *   <em> < 0 </em>     ----failed, 可根据errno获取错误码
 * @note    读取电压是2 个的 byte 的电压值
 *          2 个 byte 为定点数，第一个 byte 为电压值的整数部分，
 *          第二个 byte 为电压值的小数部分，2 个 byte 都为十六进制。
 *          例 03 22 为 3.34V 
 */
/*不支持bt_get_volatge*/
int bt_get_volatge(int fd, void *data, int len);

/**
 * @brief     设置模块读取电源电压功能开关
 * @param[in] fd         设备的文件描述符 
 * @param[in] on_off     电压检测是否打开
 *  <em> BT_ON </em>      ----打开电压检测<br>
 *  <em> BT_OFF </em>     ----关闭电压检测<br>
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, 可根据errno获取错误码
 */
/*不支持bt_set_voltage_detect*/
int bt_set_voltage_detect(int fd, uint8_t on_off);

 /**
 * @brief     确认GKEY是否正确
 * @param[in] fd         设备的文件描述符 
 * @param[in] confirm     
 *  <em> BT_MATCH_OK </em>      ----密钥匹配<br>
 *  <em> BT_MATCH_ERR </em>     ----密钥不匹配<br>
 * @return    返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, 可根据errno获取错误码
 */
int bt_user_confirm(int fd, int confirm);

/** 
 * @brief       非阻塞获取GKEY
 * @param[in] fd         设备的文件描述符  
 * @param[in/out] data : 存储GKEY的buffer
 * @param[in] len  :     buffer大小，不能小于GKEY长度4字节
 * @return 返回值<br>
 *   <em> >=0 </em>      获取GKEY的实际长度<br>
 *   <em>else </em>     ----failed, 可根据errno获取错误码 
 * @note        : 如果返回值为-EAGAIN(-11),表示需要进一步尝试获取<br>
 *               CONFIRM GKEY配对方式为 <br>
 *               1.先调用@ref bt_pairing_mode_set() 设置配对模式为@ref PAIRING_MODE_CONFIRM <br>
 *               2.再反复调用@ref bt_user_confirm_passkey() 获取GKEY <br>
 *               3.手机端发起配对请求后，bt_user_confirm_passkey() 获取GKEY成功 <br>
 *               4.对比手机端显示的GKEY与获取的GKEY, 调用@ref bt_user_confirm() 确认获取的GKEY是否正确<br>
 *               5.确认GKEY无误则配对成功，否则失败
 */
int bt_user_confirm_passkey(int fd, void *data, int len);

/** 
 * @brief       改变蓝牙名称, 每次打开蓝牙后设置生效，不保存，蓝牙关闭或reset后失效 
 * @param[in] fd         设备的文件描述符  
 * @param[in] name_str : 输入的name
 * @param[in] str_len  :  strlen(name_str)
 * @return 返回值<br>
 *   <em> =0 </em>      ----success <br>
 *   <em>else </em>     ----failed, 可根据errno获取错误码
 * @note    :    用于应用程序修改蓝牙名称，不保存
 *               系统修改蓝牙名称，使用@ref bt_set_name(), 永久保存 
 */
int bt_change_name(int fd, const char *name_str, int str_len);

/** 
 * @brief       查看蓝牙接收缓存有多少数据
 * @param[in] fd         设备的文件描述符  
 * @return 返回值<br>
 *   <em> >=0 </em>      ----蓝牙接收缓存数据长度 <br>
 *   <em>else </em>      ----failed, 可根据errno获取错误码
 */ 
int bt_peek_rx_len(int fd);

/** 
 * @brief       用于ble justwork/comfirm配对模式开始配对
 * @param[in] fd         设备的文件描述符  
 * @return 返回值<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, 可根据errno获取错误码
 */ 
int bt_ble_start_pairing(int fd);

/**
 *@if CN
	 * @brief     请求蓝牙配对状态 
	 * @param[in] fd 设备的文件描述符
	 * @param[out] status 配对状态@ref BT_PAIRING_STATUS
	 * @param[out] nvcnt nv计数，配对成功nv计数增加
	 * @return 返回值<br>
	 *	 <em> =0 </em>		----success<br>
	 *	 <em>else </em> 	----failed, 可根据errno获取错误码
 *@else
	* @brief     get bluetooth status
	* @param[in] fd file description of device
	* @param[out] status pairing status@ref BT_PAIRING_STATUS
	* @param[out] nvcnt nv count,NV count increases with successful pairing
	* @return 返回值<br>
	 *	 <em> =0 </em>		----success<br>
	 *	 <em>else </em>     ----failed, errno is set appropriately
 *@endif	 
 */
int bt_get_pairing_status(int fd, uint32_t *status, uint32_t *nvcnt);



#ifdef __cplusplus
}
#endif

#endif /* __BT_H__ */
/** @} */

