/**
@if Chinese
 * @brief       此模块用于描述 <strong>基础服务</strong> 相关接口
 * @par 文件    system.h
 * @author		Wenming
 * @date          2018/11/10
 * @version       1.0.0
 * @remarks        Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2018/11/10    | Jezz Lin        | 创建文件
 * 2022/04/20    | Wenming         | 增加英文注释
@else 
 * @brief       This module is used to describe <strong>System setting</strong> interfaces module
 * @par File    system.h
 * @author		Wenming
 * @date          2018/11/10
 * @version       1.0.0
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2018/11/10    | Jezz Lin        | Create file
 * 2022/04/20    | Wenming         | Add English description
@endif 
*/


/**
@if Chinese
 * @defgroup sys_service 基础服务模块
@else 
 * @defgroup sys_service SystemService
@endif	 
 * @{
*/
// caution, doxygen defgroup header and footer and been both auto generated!!!


#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
 * @name 硬件配置子项定义
@else  
 * @name Hardware configuration subitem definition
@endif 
 * @{
 */
#define TUSN_PREFIX                 "TUSN_PREFIX"           /**<@if Chinese TUSN前缀		@else TUSN               	@endif*/
#define HARDWARE_SN                 "SN"                    /**<@if Chinese 机器SN号		@else SN                     @endif*/
#define HARDWARE_PN                 "PN"                    /**<@if Chinese 机器PN号		@else PN                     @endif*/
#define HARDWARE_CID                "CID"                   /**<@if Chinese 硬件CID值		@else CID                    @endif*/
#define HARDWARE_BTMAC              "BTMAC"                 /**<@if Chinese 硬件BTMAC值		@else BTMAC                  @endif*/
#define HARDWARE_VERSION            "hwversion"             /**<@if Chinese 硬件版本号		@else hwversion              @endif*/
#define SOFTWARE_VERSION            "swversion"             /**<@if Chinese 软件版本号		@else swversion              @endif*/
#define HARDWARE_MACHINE            "machine"               /**<@if Chinese 机器型号		@else  machine                @endif*/
#define HARDWARE_BEEP               "beep"                  /**<@if Chinese 机器蜂鸣声		@else  beep                   @endif*/
#define HARDWARE_MSRSN              "msrsn"                 /**<@if Chinese 硬件的msrsn		@else  msrsn                  @endif*/
#define HARDWARE_TERMINAL           "Terminal"              /**<@if Chinese 机器类型		@else  Terminal               @endif*/
#define HARDWARE_CONFIG             "hwconfig"              /**<@if Chinese 机器配置		@else  hwconfig               @endif*/
#define SW_FIRMWARE_VERSION         "firmwarever"           /**<@if Chinese firmware版本	@else  firmwarever            @endif*/
#define SW_KERNEL_VERSION           "kernelver"             /**<@if Chinese kernel版本		@else  kernelver              @endif*/
#define SW_SP_VERSION               "spver"                 /**<@if Chinese sp版本			@else  spver                  @endif*/
#define SW_BOOT_VERSION             "bootver"               /**<@if Chinese boot版本		@else  bootver                @endif*/
#define SW_WIFI_VERSION             "wifiver"               /**<@if Chinese wifi硬件版本	@else  wifiver                @endif*/
#define KERNEL_COMPILE              "kernelcompile"         /**<@if Chinese kernel编译版本	@else  kernelcompile          @endif*/
#define FIRMWARE_ID                 "firmwareid"            /**<@if Chinese firmware 的ID值	@else  firmwareid             @endif*/
#define VENDER_ID                   "venderid"              /**<@if Chinese vender的ID值	@else  venderid               @endif*/
#define DEBUG_VER                   "debug_ver"             /**<@if Chinese 调试版本号		@else  debug_ver              @endif*/
#define SW_IMAGE_VERSION            "imagever"              /**<@if Chinese image版本号		@else  imagever               @endif*/
#define HARDWARE_CONFIG             "hwconfig"              /**<@if Chinese 硬件配置		@else  hwconfig               @endif*/
#define HARDWARE_CPUID              "CPUID"                 /**<@if Chinese CPU 的ID值		@else  CPU ID                 @endif*/
#define HARDWARE_WIFI_MAC           "wifi_mac"              /**<@if Chinese 机器wifi模块的mac值@else  wifi_mac            @endif*/
#define HARDWARE_IMEI               "IMEI"                  /**<@if Chinese 硬件的IMEI		@else  IMEI                   @endif*/
#define FIRMWARE_CUSTOMER           "customer"              /**<@if Chinese customer值		@else  customer               @endif*/

#define HARDWARE_BATTERY            "battery"               /**<@if Chinese 电池			@else  Battery                @endif*/
#define HARDWARE_LCD                "lcd"                   /**<@if Chinese 屏幕			@else  LCD                    @endif*/
#define HARDWARE_TOUCHSCREEN        "touchscreen"           /**<@if Chinese 触摸屏			@else  Touch Screen           @endif*/
#define HARDWARE_KEYBOARD           "keyboard"              /**<@if Chinese 键盘			@else  Keyboard               @endif*/
#define HARDWARE_MSR                "msr"                   /**<@if Chinese 磁条读卡器		@else  Magnetic Stripe Reader @endif*/
#define HARDWARE_PRINTER            "printer"               /**<@if Chinese 打印机			@else  printer                @endif*/
#define HARDWARE_NFC                "nfc"                   /**<@if Chinese 非接NFC			@else  contactless            @endif*/
#define HARDWARE_TF                 "tf"                    /**<@if Chinese TF扩展卡		@else  TransFlash             @endif*/
#define HARDWARE_IC                 "ic"                    /**<@if Chinese IC卡模块		@else  IC                     @endif*/
#define HARDWARE_SAM                "sam"                   /**<@if Chinese SAM卡模块		@else  SAM                    @endif*/
#define HARDWARE_2SIM               "2sim"                  /**<@if Chinese 双卡双待模块	@else  Dual SIM               @endif*/
#define HARDWARE_UART               "uart"                  /**<@if Chinese 串口			@else  UART                   @endif*/
#define HARDWARE_BARSCANNER         "barscanner"            /**<@if Chinese 扫码			@else  Bar Scanner            @endif*/
#define HARDWARE_WIRELESS           "wireless"              /**<@if Chinese 无线模块		@else  GPRS or CDMA           @endif*/
#define HARDWARE_MODEM              "modem"                 /**<@if Chinese MODEM模块		@else  Modem                  @endif*/
#define HARDWARE_LAN                "lan"                   /**<@if Chinese LAN模块			@else  LAN                    @endif*/
#define HARDWARE_WIFI               "wifi"                  /**<@if Chinese WIFI模块		@else  WIFI                   @endif*/
#define HARDWARE_BLUETOOTH          "bluetooth"             /**<@if Chinese 蓝牙模块		@else  Bluetooth              @endif*/
#define HARDWARE_USBH               "usbh"                  /**<@if Chinese USB主设备		@else  USB Host               @endif*/
#define HARDWARE_USBD               "usbd"                  /**<@if Chinese USB驱动模块		@else  USB Device             @endif*/
#define HARDWARE_USBO               "usbo"                  /**<@if Chinese USB OTG模块		@else  USB OTG                @endif*/
#define HARDWARE_GPS                "gps"                   /**<@if Chinese GPS模块			@else  GPS                    @endif*/
#define HARDWARE_FINGERPRINT        "fingerprint"           /**<@if Chinese 热敏打印机		@else  Fingerpinter           @endif*/
#define HARDWARE_NFC_LED            "nfc_led"               /**<@if Chinese 非接灯			@else  contactless led        @endif*/
#define HARDWARE_AUDIO              "audio"                 /**<@if Chinese 音频			@else  audio                  @endif*/
#define HARDWARE_ESIM               "esim"                  /**<@if Chinese ESIM卡模块		@else  esim                   @endif*/
#define HARDWARE_NTD      			"ntd"                   /**<@if Chinese 断码屏		    @else  digital display            @endif*/
#define HARDWARE_KEYBOARD_LIGHT  	"keyboard_light"   	    /**<@if Chinese 按键背光灯		@else  keyboard backlight     @endif*/
#define HARDWARE_VOLUME             "volume"                /**<@if Chinese 音量		    @else  volume                 @endif*/

#define HARDWARE_QRCODE             "QRCode"                /**<@if Chinese 二维码			@else  qrcode                 @endif*/
#define HARDWARE_CONFIG_SET         "config"                /**<@if Chinese 配置			@else  config                 @endif*/
#define HARDWARE_BAT_PROPERTY       "Battery Property"      /**<@if Chinese 电池属性		@else  battery property       @endif*/
#define PRODUCTION_PROCESS_NUM      "Production number"     /**<@if Chinese 生产号			@else  Production number      @endif*/
                                                                
#define HARDWARE_TP                 HARDWARE_TOUCHSCREEN    /**<@if Chinese 触摸屏1			@else  tp                     @endif*/
#define HARDWARE_LED                HARDWARE_NFC_LED        /**<@if Chinese 非接灯1			@else  led                    @endif*/

#define HARDWARE_CAMERA             HARDWARE_BARSCANNER     /**<@if Chinese 相机			@else  camera                 @endif*/
#define HARDWARE_GPRS               HARDWARE_WIRELESS       /**<@if Chinese GPRS通讯模块	@else  GPRS                   @endif*/
#define HARDWARE_FIRMWAREID         FIRMWARE_ID             /**<@if Chinese 机器名1			@else  Name of Machine        @endif*/
#define SOFTVARE_RELEASE_VER        DEBUG_VER               /**<@if Chinese 调试版本号1		@else  debug version          @endif*/
#define FIRMWARE_VERSION            SW_IMAGE_VERSION        /**<@if Chinese firmware版本号1	@else  firmware version       @endif*/
/** @} */                                                       
                                                                
/**
@if Chinese
* @brief  获取本机唯一标识序列号(TUSN)
* @param[out]  tusn		-	获取的序列号
* @param[in]   nbytes	-	tusn的最长字节数
* @return
*      |返回值   |注释|
*      | --------| --------|
*      0         | 成功
*      -1        | 失败
* @note
*      - 正常返回时，tusn返回的值是一个带'\0'的字符串: 如果机器的tusn为"0123456789"，
*        即10个字节长的字符串，则nbytes的字节数必须大于等于11，务必至少留有1个字节存储'\0'；
*        否则返回的tusn可能会被截断。
@else
* @brief  Gets the local unique identifier serial number(TUSN)
* @param[out]  tusn		-	Obtained serial number
* @param[in]   nbytes	-	Maximum number of bytes in tusn
* @return
*      |returns  |describe|
*      | --------| --------|
*      0         | Successed
*      -1        | Fail
* @note
*      - When returned normally, tusn returns a string with a '\0' : if the machine's TUSn is "0123456789"，
*        That is, a string of 10 bytes, the number of nbytes must be greater than or equal to 11, and at least one byte must be reserved for storing '\0'.；
*        Otherwise, the returned TUSN may be truncated。
@endif
*/
int sys_get_tusn(char *tusn, int nbytes);

/**
@if Chinese
 * @brief  获取 firmware 版本
 * @note
 * @param[out]  ver_info	-	版本字符串，至少有32字节空闲空间
 * @param[in]   nbytes		-	ver_info的最长字节数
 * @retval	0	-	成功
 * @retval	-1	-	失败
@else 
 * @brief  get firmware version
 * @note
 * @param[out]  ver_info  	-	version string, at least 32 bytes free space
 * @param[in]   nbytes 		-	The ver_info maximum number of bytes
 * @retval	0	-	Successed
 * @retval	-1	-	Fail
@endif 
 */
int sys_read_ver(char *ver_info, int nbytes);

/**
@if Chinese
 * @brief     读取芯片唯一ID号(chip unique id)
 * @retval    -	总是返回chip unique id字符串首地址
 * @note      读取失败，则是空字符串
@else 
 * @brief     Read the unique CHIP ID(chip unique id)
 * @retval    -	Always return the first address of the chip Unique ID string
 * @note      Failed to read, an empty string
@endif 
*/
uint8_t *sys_read_chip_uid(void);

#if 0 //删除此接口
/**
@if Chinese
 * @brief       蜂鸣器按固定频率时长发声
 * @return      none
 * @note
 *  - 与 beep(1000,100); 的调用效果一致
@else 
 * @brief       The buzzer sounds at a fixed frequency
 * @return      none
 * @note
 *  - With the beep (1000100); The call effect is consistent
@endif 
 */
void sys_beep(void);
#endif

/**
@if Chinese
* @brief	设置自动灭屏，设置休眠模式
* @param  mode
*         - 传入mode为0表示，取消屏幕定时灭屏，屏幕常亮(系统不允许休眠)
*         - 传入mode为1表示：恢复屏幕定时灭屏 (系统允许休眠)
* @retval int 返回设置前的mode值
* @note
*         - 注意配对使用，不能循环调用
*         - 应用层可以接收函数的返回值以备恢复设置前的mode值
*         - 接口使用的参考代码，可以避免应用层设置mode后影响了原本系统定义的休眠模式
* @par 示例:
  @code
  int power_save_mode_bak;
  power_save_mode_bak = sys_set_power_save(0); //先备份当前系统休眠模式
  ; //执行一段耗时，LCD不能灭屏的操作
  sys_set_power_save(power_save_mode_bak);     //恢复之前的系统休眠模式
  @endcode
@else
* @brief	Set the auto off screen and sleep mode
* @param  mode
*         - If mode is set to 0, the screen is off and the screen is steady on (the system does not allow sleep).
*         - If mode is 1, the screen is periodically off (the system allows sleep).
* @retval int Returns the mode value before setting
* @note
*         - Note that pairs are used and cannot be called in a loop
*         - The application layer can receive the return value of the function in case of restoring the mode value before setting
*         - The reference code used by the interface prevents the application layer from affecting the sleep mode defined by the system after setting mode
* @par Example:
  @code
  int power_save_mode_bak;
  power_save_mode_bak = sys_set_power_save(0); //Back up the current hibernation mode
  ; //The LCD cannot be off during a time-consuming operation
  sys_set_power_save(power_save_mode_bak);     //Restore the previous system hibernation mode
  @endcode
@endif  
*/
int sys_set_power_save(int mode);

/**
@if Chinese
 * @brief       系统重启
 * @return      none
 * @note
@else 
 * @brief       System reset
 * @return      none
 * @note
@endif 
 */
void sys_reset(void);

/**
@if Chinese
 * @brief       系统关机
 * @return      none
 * @note
@else 
 * @brief       System shutdown
 * @return      none
 * @note
@endif 
 */
void sys_power_off(void);

/**
@if Chinese
* @brief   设置电源键是否关机功能
* @param  enable
*         - 传入enable为0表示，长按电源键系统不关机
*         - 传入enable为非0表示：长按电源键系统关机
* @note
*         - 设置电源键系统不关机,应用需要调用关机接口来实现关机
@else
* @brief   Set whether to shut down the power button
* @param  enable
*         - If the value of enable is 0, the system does not shut down after you hold down the power button
*         - If the value of enable is not 0, you can hold down the power button to shut down the system
* @note
*         - Set the power button not to shut down the system, the application needs to call the shutdown interface to shut down
@endif
*/
void sys_set_power_button(int enable);

/**
@if Chinese
 * @brief       获取系统启动到当前经过的时间
 * @return      获取到的时间
 * @note        单位为ms
@else 
 * @brief       Gets the time elapsed between system startup and the current time
 * @return      the times
 * @note        In milliseconds
@endif 
 */
uint32_t sys_get_timer_count(void);

/**
@if Chinese
* @brief 延时ms个毫秒
* @param[in] ms	-	延时时间（单位：毫秒）
* @return  * @note 精确度为1ms等级
* @par 示例:
* @code
    // 延时100ms:
    ...... // 前期操作
    sys_delay_ms(100);
    ...... // 后期操作
  @endcode
@else  
* @brief The delay is ms ms
* @param[in] ms	-	Delay time (unit: ms)
* @return  * @note Accuracy is 1ms
* @par 示例:
* @code
    // Delay 100 ms:
    ...... // Early done
    sys_delay_ms(100);
    ...... // Late done
  @endcode
@endif  
*/
//void sys_delay_ms(uint32_t count_ms);
void sys_msleep(unsigned long ms);

/**
@if Chinese
 * @brief  设置系统日期和时间，星期值将自动算出并设置
 * @param[in]  time_str	-	日期时间参数的指针,格式为YYMMDDhhmmss,参数为BCD码,共6个字节长.(有效时间范围：2000,1,1 - 2079,12,31)
 * @param[in]  len		-	time_str的输入长度
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0x00 | 设置时间成功
 *      !=0x00 | 设置时间失败
 * @par 示例:
 * @code
    // 设置当前时间为2008年5月6日20点20分52秒：
    int Ret = 0;
    uint8_t time_str[6];

    time_str[0] = 0x08;      // 年，2008-2000=0x08
    time_str[1] = 0x05;      // 月
    time_str[2] = 0x06;      // 日
    time_str[3] = 0x20;     // 时
    time_str[4] = 0x20;     // 分
    time_str[5] = 0x52;     // 秒
    Ret = sys_set_time((const uint8_t *)time_str, sizeof(time_str));
   @endcode
@else   
 * @brief  Set the system date and time, the week value will be calculated and set automatically
 * @param[in]  time_str	-	A pointer to the date-time parameter in the format of YYMMDDhhmmss, in the format of BCD code, with a total of 6 bytes.(Valid time range: 2000,1, 1-2079,12,31)
 * @param[in]  len		-	Input the time_str length
 * @return
 *      |returns  |Describle     |
 *      | --------| --------|
 *      0x00      | Setting the time succeeded
 *      !=0x00    | Failed to set the time
 * @par 示例:
 * @code
    // Set the current time to 20:20:52 May 6, 2008：
    int Ret = 0;
    uint8_t time_str[6];

    time_str[0] = 0x08;      // year，2008-2000=0x08
    time_str[1] = 0x05;      // month
    time_str[2] = 0x06;      // day
    time_str[3] = 0x20;     // hour
    time_str[4] = 0x20;     // minute
    time_str[5] = 0x52;     // seconds
    Ret = sys_set_time((const uint8_t *)time_str, sizeof(time_str));
   @endcode
@endif   
 */
int sys_set_time(const uint8_t *time_str, int len);

/**
@if Chinese
 * @brief	读取当前系统日期和时间
 * @param[out] time_str	-	存放日期时间值的指针, 以BCD码形式存放：
                - time_str[0]  年份， +2000为实际的年份
                - time_str[1]  月份, 为实际的月份值，1-12为有效值
                - time_str[2]  日
                - time_str[3]  小时
                - time_str[4]  分钟
                - time_str[5]  秒钟
                - time_str[6]  星期
 * @param[in]  len	-	time_str的最长字节数
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0x00 | 获取时间成功
 *      !=0x00 | 获取时间失败
 * @note
    星期值的定义:
    1  星期一, 2  星期二, …… 7  星期日.
 *  @par 示例:
 *  @code
    uint8_t time_str[7];
    // 获取时间并显示出来
    memset(time_str, 0x00, sizeof(time_str));
    sys_get_time((char *)time_str, sizeof(time_str));
    lcdDisplay(0,0,0,”%02x-%02x-%02x %02x:%02x:%02x”,
    time_str[0],time_str[1],time_str[2],time_str[3],time_str[4],time_str[5]);
    //显示的结果范例为 "19-02-22 15:57:03" 表示时间为 2019年2月22日15点57分03秒
    @endcode
@else
 * @brief	Read the current system date and time
 * @param[out] time_str	-	Pointer to date and time values in BCD code format：
                - time_str[0]  Year, +2000 is the actual year
                - time_str[1]  Month is the actual month value, and 1-12 is valid
                - time_str[2]  day
                - time_str[3]  hour
                - time_str[4]  Minutes
                - time_str[5]  Seconds
                - time_str[6]  Week
 * @param[in]  len	-	The time_str max length
 * @return
 *      |returns  |describe|
 *      | --------| --------|
 *      0x00      | Obtaining time successfully
 *      !=0x00    | Failed to obtain time
 * @note
    Definition of weekly values:
    1 Monday, 2 Tuesday... 7 Sunday.
 *  @par Example:
 *  @code
    uint8_t time_str[7];
    // Get the time and display it
    memset(time_str, 0x00, sizeof(time_str));
    sys_get_time((char *)time_str, sizeof(time_str));
    lcdDisplay(0,0,0,”%02x-%02x-%02x %02x:%02x:%02x”,
    time_str[0],time_str[1],time_str[2],time_str[3],time_str[4],time_str[5]);
    //An example of the results shown is "19-02-22 15:57:03" The time is 15:57:03 on February 22, 2019
    @endcode
@endif	
 */
int sys_get_time(uint8_t *time_str, int len);

/**
@if Chinese
 * @brief  获取本机硬件模块配置信息
 * @param[in]  module    -	存储需要获取的硬件模块名称,详细模块请参考注释栏
 * @param[out] type      -	获取硬件模块对应的类型，字符串形式。
 * @param[out] numbers   -	获取硬件模块的最大个数。
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0 | 成功
 *      -1 | 失败，见<errno.h>
 * @note   有获取CPUID才返回>0的值，即表示CPUID的字节数。\n
 *         当用来获取CID时，必须判断返回值，\n
 *         返回-1说明机器没有CID，返回0说明获取成功，\n
 *         type得到16进制的CID字符串，调用者需要自行转换为整数。 
@else 
 * @brief  Obtain local hardware module configuration information
 * @param[in]  module    -	Store the name of the hardware module to be obtained. For details about the module, see the comment bar
 * @param[out] type      -	The value is a string of characters。
 * @param[out] numbers   -	Obtain the maximum number of hardware modules。
 * @return
 *      |returns  |describe |
 *      | --------| --------|
 *      0         | Successed
 *      -1        | Fail，see<errno.h>
 * @note   The value >0 is returned only when the CPUID is obtained, that is, the number of bytes of the CPUID。\n
 *         When used to get CID, the return value must be determined，\n
 *         If -1 is returned, the machine does not have CID. If 0 is returned, the CID is successfully obtained，\n
 *         Type gets a hexadecimal CID string that the caller needs to convert to an integer。 
@endif 
 */
int sys_get_hardware_config(const char *module, char *type, int *numbers);

/**
@if Chinese
 * @brief   获取系统配置信息
 * @note    usrapp只允许使用"USER_"开头的section
 * @param[in]   section -	用户配置信息段名
 * @param[in]   key     -	用户配置信息关键字
 * @param[out]  buf     -	获取配置信息的缓冲区
 * @param[in]   buf_len -	传入buf的长度
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      >=0   | 获取到的数据长度
 *      < 0 | 失败，见<errno.h>
@else 
 * @brief   Obtain system configuration information
 * @note    usrapp Only those starting with "USER_" are allowedsection
 * @param[in]   section -	User configuration information segment name
 * @param[in]   key     -	User configuration information keyword
 * @param[out]  buf     -	Gets the buffer of configuration information
 * @param[in]   buf_len -	The length of buF passed in
 * @return
 *      |returns  |describle|
 *      | --------| --------|
 *      >=0       | The length of the data obtained
 *      < 0       | Fail，see<errno.h>
@endif 
 */
int sys_get_settting_config(const char *section, const char *key, char *buf, int buf_len);

/**
@if Chinese
 * @brief   设置系统配置信息
 * @note    usrapp只允许使用"USER_"开头的section。\n
 *          调用该函数之后必须调用sys_save_settting_config()进行保存。
 * @param[in]   section -	用户配置信息段名，必须是以"USER_"开头的字符串
 * @param[in]   key     -	用户配置信息关键字
 * @param[out]  value   -	传入配置信息
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0   | 成功
 *      < 0 | 失败，见<errno.h>
 *      -1  | 没有权限
@else 
 * @brief   Set the system configuration information
 * @note    usrapp Only those starting with "USER_" are allowedsection。\n
 *          This function must be called after it is called sys_save_settting_config() saved。
 * @param[in]   section -	The user configuration information segment name must start with "USER_"
 * @param[in]   key     -	User configuration information keyword
 * @param[out]  value   -	Passing in configuration information
 * @return
 *      |returns  |describe|
 *      | --------| --------|
 *      0         | Successed
 *      < 0       | Fail，see <errno.h>
 *      -1        | No permission
@endif 
 */
int sys_set_settting_config(const char *section, const char *key, const char *value);

/**
@if Chinese
 * @brief   保存系统配置信息
 * @note    在sys_set_settting_config()之后调用
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0   | 成功
 *      < 0 | 失败，见<errno.h>
@else 
 * @brief   Save the system configuration information
 * @note    after sys_set_settting_config() is called
 * @return
 *      |returns  |describle|
 *      | --------| --------|
 *      0         | Successed
 *      < 0       | Fail，see <errno.h>
@endif
 */
int sys_save_settting_config(void);


#if 0
#define LastError()                 \
({                                  \
    int error = 0;                  \
    sysGetLastError(NULL, &error);  \
    error;                          \
})
#endif

// 增加获取电池的电压值、电量百分比的接口

/**
@if Chinese
 * @brief  系统电压信息结构体
@else  
 * @brief  System voltage information structure
@endif
 */
typedef struct {
    uint32_t status;            /**<@if Chinese  0- Battery powered only; 1- Positive charging; 2- Fully charged; 3- Voltage is too low; 4- Stop charging @else 0-仅电池供电;1-正充电; 2-充满电; 3-电压过低; 4-停止充电 @endif*/
    uint32_t cur_values;        /**<@if Chinese  当前电压值 @else  Current voltage                                @endif*/
    uint32_t max_values;        /**<@if Chinese  最高电压值 @else  Maximum voltage                                @endif*/
    uint32_t min_values;        /**<@if Chinese  最低电压值 @else  Minimum voltage                                @endif*/
    uint32_t percent;           /**<@if Chinese  当前电量百分比  @else Current electricity percentage             @endif*/
} sys_battery_info_t;

/**
@if Chinese
 * @brief  获取系统电池信息
 * @param[in]	battery_info	-	系统电压信息结构体
 * @param[out]  battery_info	-	系统电池信息
 * @retval
 *          0 - 成功 , other - 失败
@else 
 * @brief  get system battery info
 * @param[in]	battery_info	-	System voltage information structure
 * @param[out]	battery_info	-	System Battery Information
 * @retval
 *          0 - successful , other - failed
@endif 
 */
int sys_get_battery_info(sys_battery_info_t *battery_info);

/**
@if Chinese
 * @brief           校验应用bin文件的签名
 * @param[in]       file_name  - 应用bin文件的绝对路径
 * @return          int
 *
 *                  0:   校验通过
 *                  非0: 校验失败
 * @note            该接口支持V1/V2版本的签名格式
@else 
 * @brief           Verify the signature of the application bin file
 * @param[in]       file_name  - Absolute path of the application bin file
 * @return          int
 *
 *                  0:   Check success
 *                  !0: Check failure
 * @note            This interface supports the signature format of V1 and V2
@endif 
*/
int sys_verify_file(const char *file_name);

/**
@if Chinese
 * @brief  获取sp内部RTC晶振频率状态
 * @note   缓冲区长度必须大于等于5
 * @param[out] type  -	接收缓冲区，有以下三种可能结果:\n
                     "FD-H"   晶振频率大于1MHz \n
                     "FD-L"   晶振频率小于25KHz \n
                     "FD-N"   晶振频率处于正常范围 \n
 * @param[out] len   传入缓冲区长度，传出实际获取到的字节数
 * @return
 *      |返回值|注释|
 *      | --------| --------|
 *      0 | 成功
 *      -1 | 失败，见<errno.h>
@else 
 * @brief  Obtain the RTC crystal frequency state inside SP
 * @note   The buffer length must be greater than or equal to 5
 * @param[out] type  -	The receive buffer has three possible outcomes:\n
                     "FD-H"   Crystal frequency is greater than 1MHz \n
                     "FD-L"   Crystal frequency is less than 25KHz \n
                     "FD-N"   The crystal frequency is in the normal range \n
 * @param[out] len   The length of the incoming buffer, and the number of bytes actually retrieved
 * @return
 *      |returns  |describe|
 *      | --------| --------|
 *      0         | Successed
 *      -1        | Failed ,see<errno.h>
@endif 
 */
int get_rtc_crystal(char *type, int *len);

/**
@if Chinese
 * @brief           使能/禁止 系统的standby模式
 * @param[in]       mode  -	1  使能  0  禁止
 * @note            standby模式下, 系统后台任务仍能正常运行
@else 
 * @brief           Enable/disable the standby mode of the system
 * @param[in]       mode  -	1 Enable 0 Disable
 * @note            In standby mode, background tasks can still run properly
@endif 
*/
void sys_enable_system_standby(int mode);

/**
@if Chinese
 * @brief           获取内存信息
 * @param[out]      total_heap_mem              -	内存池总大小
 * @param[out]      available_heap_mem          -	可用内存大小
 * @param[out]      max_available_heap_mem_blk  -	最大可分配块大小
 * @retval          =0 成功
 * @retval          -1 失败
@else 
 * @brief           Get Memory Information
 * @param[out]      total_heap_mem              -	Total size of the memory pool
 * @param[out]      available_heap_mem          -	unsigned long totalram
 * @param[out]      max_available_heap_mem_blk  -	Maximum allocatable block size
 * @retval          =0 Successed
 * @retval          -1 Failed
@endif 
*/
int sys_get_free_mem(uint32_t *total_heap_mem, uint32_t *available_heap_mem, uint32_t *max_available_heap_mem_blk);

/**
@if Chinese
 * @brief			发送消息给其它线程
 * @param[in]		signal_ptr  -	消息体的指针
 * @param[in]		dest_id		-	目的线程的id
 * @retval          0 发送成功
 * @retval          -1 发送失败
 * @note            发送的只是消息体的首地址
@else 
 * @brief			Send messages to other threads
 * @param[in]		signal_ptr  -	Pointer to the message body
 * @param[in]		dest_id		-	Id of the destination thread
 * @retval          0 Successed
 * @retval          -1 Failed
 * @note            It sends only the header address of the message body
@endif 
*/
int sys_send_signal(void *signal_ptr, uint32_t dest_id);

/**
@if Chinese
 * @brief			线程中读取其它线程发过来的消息，若无消息，则该函数阻塞
 * @param[in]		thread_id   -	源线程的id
 * @retval          非空 成功，返回消息体的指针
 * @retval          NULL 读取失败
 * @note            注意该函数是阻塞调用的，接收的只是消息体的首地址
@else 
 * @brief			A thread reads a message from another thread. If there is no message, the function blocks
 * @param[in]		thread_id   -	Id of the source thread
 * @retval          !NULL Success, returns a pointer to the message body
 * @retval          NULL Failed
 * @note            Note that this function blocks the call and receives only the first address of the message body
@endif 
*/
void *sys_get_signal(uint32_t thread_id);

/**
@if Chinese
 * @brief			动态分配连续的指定大小的内存块
 * @param[in]		size        -	内存块的大小，单位字节
 * @retval          非空 分配成功，返回指向被分配内存的指针
 * @retval          NULL 分配失败
@else  
 * @brief			Dynamically allocates contiguous chunks of specified size
 * @param[in]		size        -	The size of a memory block, in bytes
 * @retval          !NUll Returns a pointer to allocated memory on success
 * @retval          NULL assignment failure
@endif 
*/
void *sys_malloc(uint32_t size);

/**
@if Chinese
 * @brief			释放动态分配的内存
 * @param[in]		sig        -	需要释放内存的指针
 * @retval          =0 释放成功
 * @retval          -1 释放失败
@else  
 * @brief			Release dynamically allocated memory
 * @param[in]		sig        -	A pointer to memory that needs to be freed
 * @retval          =0 Successed
 * @retval          -1 Failed
@endif
*/
int sys_free(void *sig);

/**
@if Chinese
 * @brief			断言
 * @param[in]		expinfo     -	异常信息
 * @param[in]		file        -	文件名字符串
 * @param[in]		line        -	行号
 * @note            非标准函数，调用总是触发断言，则终止程序执行显示蓝屏
@else 
 * @brief			Assert
 * @param[in]		expinfo     -	exception message
 * @param[in]		file        -	File name string
 * @param[in]		line        -	line number
 * @note            A nonstandard function whose call always triggers an assertion terminates program execution showing a blue screen
@endif 
*/
void sys_assert(const char *expinfo, const char *file, int line);

/**
@if Chinese
* @brief  读取设备唯一编号
* @param[out]  usn -	输出设备唯一编号（带'\0'的字符串形式），要求空间不少于32字节
* @param[in]   len -	传入usn数组的有效长度
* @return
*		   - 0 成功
*		   - <0 失败，返回相应的返回值
@else
* @brief  Read the unique device id
* @param[out]  usn -	Output device unique number (string with '\0'), required space not less than 32 bytes
* @param[in]   len -	The effective length of the usN array passed in
* @return
*		   - 0  Successed
*		   - <0 Failure, return the corresponding return value
@endif
*/
int sys_get_usn(char *usn, int len);

/**
@if Chinese
* @brief  读取授权码
* @param[out]  license	-	输出授权码
* @param[in]   len		-	需要读取的license大小
* @return
*		   - 实际读取的长度	成功
*		   - <0 失败，返回相应的返回值
@else
* @brief  Reading authorization Code
* @param[out]  license	-	Output Authorization Code
* @param[in]   len		-	Get the license size
* @return
*		   - The actual length read succeeded
*		   - <0 Failure, return the corresponding return value
@endif
*/
int get_barcode_license(uint8_t *license, uint32_t len);

/*!
 @if Chinese
        @brief          设置键盘背光灯状态
        @param[in]      status    状态，0-关闭，非0-打开
        @retval                0             设置成功
        @retval                其它          设置失败
 @else
        @brief          Set the keyboard backlight state
        @param[in]      status    Keyboard backlight status，0:close，non-0:open
        @retval                0             successful
        @retval                other         Failure
 @endif
*/
int sys_kbd_backlight_set_status(uint8_t status);

/*!
 @if Chinese
        @brief          获取键盘背光灯状态
        @param[out]     status                 状态
        @retval                0                 获取成功
        @retval                -EINVAL           输入参数有错误，status为空指针
        @retval                其它              获取失败
 @else
        @brief          Get the state of the keyboard backlight
        @param[out]     status              Keyboard backlight status
        @retval                0             successful
        @retval                -EINVAL              input parameter error
        @retval                other         Failure
 @endif
*/
int sys_kbd_backlight_get_status(uint8_t *status);

/**
* @brief  更新系统logo
* @param[in]   filename 要更新的logo文件路径,例如"/home/user0/np.logo"
* @return
*	 - 0    成功 
*	 - -1   固件未支持该接口
*	 - 其他 失败
*/
int sys_update_logo(const char *filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SYSTEM_H__ */

/** @} */

