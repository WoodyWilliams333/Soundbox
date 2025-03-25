/**
@if Chinese
 * @brief       ��ģ���������� <strong>��������</strong> ��ؽӿ�
 * @par �ļ�    system.h
 * @author		Wenming
 * @date          2018/11/10
 * @version       1.0.0
 * @remarks        Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2018/11/10    | Jezz Lin        | �����ļ�
 * 2022/04/20    | Wenming         | ����Ӣ��ע��
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
 * @defgroup sys_service ��������ģ��
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
 * @name Ӳ�����������
@else  
 * @name Hardware configuration subitem definition
@endif 
 * @{
 */
#define TUSN_PREFIX                 "TUSN_PREFIX"           /**<@if Chinese TUSNǰ׺		@else TUSN               	@endif*/
#define HARDWARE_SN                 "SN"                    /**<@if Chinese ����SN��		@else SN                     @endif*/
#define HARDWARE_PN                 "PN"                    /**<@if Chinese ����PN��		@else PN                     @endif*/
#define HARDWARE_CID                "CID"                   /**<@if Chinese Ӳ��CIDֵ		@else CID                    @endif*/
#define HARDWARE_BTMAC              "BTMAC"                 /**<@if Chinese Ӳ��BTMACֵ		@else BTMAC                  @endif*/
#define HARDWARE_VERSION            "hwversion"             /**<@if Chinese Ӳ���汾��		@else hwversion              @endif*/
#define SOFTWARE_VERSION            "swversion"             /**<@if Chinese ����汾��		@else swversion              @endif*/
#define HARDWARE_MACHINE            "machine"               /**<@if Chinese �����ͺ�		@else  machine                @endif*/
#define HARDWARE_BEEP               "beep"                  /**<@if Chinese ����������		@else  beep                   @endif*/
#define HARDWARE_MSRSN              "msrsn"                 /**<@if Chinese Ӳ����msrsn		@else  msrsn                  @endif*/
#define HARDWARE_TERMINAL           "Terminal"              /**<@if Chinese ��������		@else  Terminal               @endif*/
#define HARDWARE_CONFIG             "hwconfig"              /**<@if Chinese ��������		@else  hwconfig               @endif*/
#define SW_FIRMWARE_VERSION         "firmwarever"           /**<@if Chinese firmware�汾	@else  firmwarever            @endif*/
#define SW_KERNEL_VERSION           "kernelver"             /**<@if Chinese kernel�汾		@else  kernelver              @endif*/
#define SW_SP_VERSION               "spver"                 /**<@if Chinese sp�汾			@else  spver                  @endif*/
#define SW_BOOT_VERSION             "bootver"               /**<@if Chinese boot�汾		@else  bootver                @endif*/
#define SW_WIFI_VERSION             "wifiver"               /**<@if Chinese wifiӲ���汾	@else  wifiver                @endif*/
#define KERNEL_COMPILE              "kernelcompile"         /**<@if Chinese kernel����汾	@else  kernelcompile          @endif*/
#define FIRMWARE_ID                 "firmwareid"            /**<@if Chinese firmware ��IDֵ	@else  firmwareid             @endif*/
#define VENDER_ID                   "venderid"              /**<@if Chinese vender��IDֵ	@else  venderid               @endif*/
#define DEBUG_VER                   "debug_ver"             /**<@if Chinese ���԰汾��		@else  debug_ver              @endif*/
#define SW_IMAGE_VERSION            "imagever"              /**<@if Chinese image�汾��		@else  imagever               @endif*/
#define HARDWARE_CONFIG             "hwconfig"              /**<@if Chinese Ӳ������		@else  hwconfig               @endif*/
#define HARDWARE_CPUID              "CPUID"                 /**<@if Chinese CPU ��IDֵ		@else  CPU ID                 @endif*/
#define HARDWARE_WIFI_MAC           "wifi_mac"              /**<@if Chinese ����wifiģ���macֵ@else  wifi_mac            @endif*/
#define HARDWARE_IMEI               "IMEI"                  /**<@if Chinese Ӳ����IMEI		@else  IMEI                   @endif*/
#define FIRMWARE_CUSTOMER           "customer"              /**<@if Chinese customerֵ		@else  customer               @endif*/

#define HARDWARE_BATTERY            "battery"               /**<@if Chinese ���			@else  Battery                @endif*/
#define HARDWARE_LCD                "lcd"                   /**<@if Chinese ��Ļ			@else  LCD                    @endif*/
#define HARDWARE_TOUCHSCREEN        "touchscreen"           /**<@if Chinese ������			@else  Touch Screen           @endif*/
#define HARDWARE_KEYBOARD           "keyboard"              /**<@if Chinese ����			@else  Keyboard               @endif*/
#define HARDWARE_MSR                "msr"                   /**<@if Chinese ����������		@else  Magnetic Stripe Reader @endif*/
#define HARDWARE_PRINTER            "printer"               /**<@if Chinese ��ӡ��			@else  printer                @endif*/
#define HARDWARE_NFC                "nfc"                   /**<@if Chinese �ǽ�NFC			@else  contactless            @endif*/
#define HARDWARE_TF                 "tf"                    /**<@if Chinese TF��չ��		@else  TransFlash             @endif*/
#define HARDWARE_IC                 "ic"                    /**<@if Chinese IC��ģ��		@else  IC                     @endif*/
#define HARDWARE_SAM                "sam"                   /**<@if Chinese SAM��ģ��		@else  SAM                    @endif*/
#define HARDWARE_2SIM               "2sim"                  /**<@if Chinese ˫��˫��ģ��	@else  Dual SIM               @endif*/
#define HARDWARE_UART               "uart"                  /**<@if Chinese ����			@else  UART                   @endif*/
#define HARDWARE_BARSCANNER         "barscanner"            /**<@if Chinese ɨ��			@else  Bar Scanner            @endif*/
#define HARDWARE_WIRELESS           "wireless"              /**<@if Chinese ����ģ��		@else  GPRS or CDMA           @endif*/
#define HARDWARE_MODEM              "modem"                 /**<@if Chinese MODEMģ��		@else  Modem                  @endif*/
#define HARDWARE_LAN                "lan"                   /**<@if Chinese LANģ��			@else  LAN                    @endif*/
#define HARDWARE_WIFI               "wifi"                  /**<@if Chinese WIFIģ��		@else  WIFI                   @endif*/
#define HARDWARE_BLUETOOTH          "bluetooth"             /**<@if Chinese ����ģ��		@else  Bluetooth              @endif*/
#define HARDWARE_USBH               "usbh"                  /**<@if Chinese USB���豸		@else  USB Host               @endif*/
#define HARDWARE_USBD               "usbd"                  /**<@if Chinese USB����ģ��		@else  USB Device             @endif*/
#define HARDWARE_USBO               "usbo"                  /**<@if Chinese USB OTGģ��		@else  USB OTG                @endif*/
#define HARDWARE_GPS                "gps"                   /**<@if Chinese GPSģ��			@else  GPS                    @endif*/
#define HARDWARE_FINGERPRINT        "fingerprint"           /**<@if Chinese ������ӡ��		@else  Fingerpinter           @endif*/
#define HARDWARE_NFC_LED            "nfc_led"               /**<@if Chinese �ǽӵ�			@else  contactless led        @endif*/
#define HARDWARE_AUDIO              "audio"                 /**<@if Chinese ��Ƶ			@else  audio                  @endif*/
#define HARDWARE_ESIM               "esim"                  /**<@if Chinese ESIM��ģ��		@else  esim                   @endif*/
#define HARDWARE_NTD      			"ntd"                   /**<@if Chinese ������		    @else  digital display            @endif*/
#define HARDWARE_KEYBOARD_LIGHT  	"keyboard_light"   	    /**<@if Chinese ���������		@else  keyboard backlight     @endif*/
#define HARDWARE_VOLUME             "volume"                /**<@if Chinese ����		    @else  volume                 @endif*/

#define HARDWARE_QRCODE             "QRCode"                /**<@if Chinese ��ά��			@else  qrcode                 @endif*/
#define HARDWARE_CONFIG_SET         "config"                /**<@if Chinese ����			@else  config                 @endif*/
#define HARDWARE_BAT_PROPERTY       "Battery Property"      /**<@if Chinese �������		@else  battery property       @endif*/
#define PRODUCTION_PROCESS_NUM      "Production number"     /**<@if Chinese ������			@else  Production number      @endif*/
                                                                
#define HARDWARE_TP                 HARDWARE_TOUCHSCREEN    /**<@if Chinese ������1			@else  tp                     @endif*/
#define HARDWARE_LED                HARDWARE_NFC_LED        /**<@if Chinese �ǽӵ�1			@else  led                    @endif*/

#define HARDWARE_CAMERA             HARDWARE_BARSCANNER     /**<@if Chinese ���			@else  camera                 @endif*/
#define HARDWARE_GPRS               HARDWARE_WIRELESS       /**<@if Chinese GPRSͨѶģ��	@else  GPRS                   @endif*/
#define HARDWARE_FIRMWAREID         FIRMWARE_ID             /**<@if Chinese ������1			@else  Name of Machine        @endif*/
#define SOFTVARE_RELEASE_VER        DEBUG_VER               /**<@if Chinese ���԰汾��1		@else  debug version          @endif*/
#define FIRMWARE_VERSION            SW_IMAGE_VERSION        /**<@if Chinese firmware�汾��1	@else  firmware version       @endif*/
/** @} */                                                       
                                                                
/**
@if Chinese
* @brief  ��ȡ����Ψһ��ʶ���к�(TUSN)
* @param[out]  tusn		-	��ȡ�����к�
* @param[in]   nbytes	-	tusn����ֽ���
* @return
*      |����ֵ   |ע��|
*      | --------| --------|
*      0         | �ɹ�
*      -1        | ʧ��
* @note
*      - ��������ʱ��tusn���ص�ֵ��һ����'\0'���ַ���: ���������tusnΪ"0123456789"��
*        ��10���ֽڳ����ַ�������nbytes���ֽ���������ڵ���11�������������1���ֽڴ洢'\0'��
*        ���򷵻ص�tusn���ܻᱻ�ضϡ�
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
*      - When returned normally, tusn returns a string with a '\0' : if the machine's TUSn is "0123456789"��
*        That is, a string of 10 bytes, the number of nbytes must be greater than or equal to 11, and at least one byte must be reserved for storing '\0'.��
*        Otherwise, the returned TUSN may be truncated��
@endif
*/
int sys_get_tusn(char *tusn, int nbytes);

/**
@if Chinese
 * @brief  ��ȡ firmware �汾
 * @note
 * @param[out]  ver_info	-	�汾�ַ�����������32�ֽڿ��пռ�
 * @param[in]   nbytes		-	ver_info����ֽ���
 * @retval	0	-	�ɹ�
 * @retval	-1	-	ʧ��
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
 * @brief     ��ȡоƬΨһID��(chip unique id)
 * @retval    -	���Ƿ���chip unique id�ַ����׵�ַ
 * @note      ��ȡʧ�ܣ����ǿ��ַ���
@else 
 * @brief     Read the unique CHIP ID(chip unique id)
 * @retval    -	Always return the first address of the chip Unique ID string
 * @note      Failed to read, an empty string
@endif 
*/
uint8_t *sys_read_chip_uid(void);

#if 0 //ɾ���˽ӿ�
/**
@if Chinese
 * @brief       ���������̶�Ƶ��ʱ������
 * @return      none
 * @note
 *  - �� beep(1000,100); �ĵ���Ч��һ��
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
* @brief	�����Զ���������������ģʽ
* @param  mode
*         - ����modeΪ0��ʾ��ȡ����Ļ��ʱ��������Ļ����(ϵͳ����������)
*         - ����modeΪ1��ʾ���ָ���Ļ��ʱ���� (ϵͳ��������)
* @retval int ��������ǰ��modeֵ
* @note
*         - ע�����ʹ�ã�����ѭ������
*         - Ӧ�ò���Խ��պ����ķ���ֵ�Ա��ָ�����ǰ��modeֵ
*         - �ӿ�ʹ�õĲο����룬���Ա���Ӧ�ò�����mode��Ӱ����ԭ��ϵͳ���������ģʽ
* @par ʾ��:
  @code
  int power_save_mode_bak;
  power_save_mode_bak = sys_set_power_save(0); //�ȱ��ݵ�ǰϵͳ����ģʽ
  ; //ִ��һ�κ�ʱ��LCD���������Ĳ���
  sys_set_power_save(power_save_mode_bak);     //�ָ�֮ǰ��ϵͳ����ģʽ
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
 * @brief       ϵͳ����
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
 * @brief       ϵͳ�ػ�
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
* @brief   ���õ�Դ���Ƿ�ػ�����
* @param  enable
*         - ����enableΪ0��ʾ��������Դ��ϵͳ���ػ�
*         - ����enableΪ��0��ʾ��������Դ��ϵͳ�ػ�
* @note
*         - ���õ�Դ��ϵͳ���ػ�,Ӧ����Ҫ���ùػ��ӿ���ʵ�ֹػ�
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
 * @brief       ��ȡϵͳ��������ǰ������ʱ��
 * @return      ��ȡ����ʱ��
 * @note        ��λΪms
@else 
 * @brief       Gets the time elapsed between system startup and the current time
 * @return      the times
 * @note        In milliseconds
@endif 
 */
uint32_t sys_get_timer_count(void);

/**
@if Chinese
* @brief ��ʱms������
* @param[in] ms	-	��ʱʱ�䣨��λ�����룩
* @return  * @note ��ȷ��Ϊ1ms�ȼ�
* @par ʾ��:
* @code
    // ��ʱ100ms:
    ...... // ǰ�ڲ���
    sys_delay_ms(100);
    ...... // ���ڲ���
  @endcode
@else  
* @brief The delay is ms ms
* @param[in] ms	-	Delay time (unit: ms)
* @return  * @note Accuracy is 1ms
* @par ʾ��:
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
 * @brief  ����ϵͳ���ں�ʱ�䣬����ֵ���Զ����������
 * @param[in]  time_str	-	����ʱ�������ָ��,��ʽΪYYMMDDhhmmss,����ΪBCD��,��6���ֽڳ�.(��Чʱ�䷶Χ��2000,1,1 - 2079,12,31)
 * @param[in]  len		-	time_str�����볤��
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0x00 | ����ʱ��ɹ�
 *      !=0x00 | ����ʱ��ʧ��
 * @par ʾ��:
 * @code
    // ���õ�ǰʱ��Ϊ2008��5��6��20��20��52�룺
    int Ret = 0;
    uint8_t time_str[6];

    time_str[0] = 0x08;      // �꣬2008-2000=0x08
    time_str[1] = 0x05;      // ��
    time_str[2] = 0x06;      // ��
    time_str[3] = 0x20;     // ʱ
    time_str[4] = 0x20;     // ��
    time_str[5] = 0x52;     // ��
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
 * @par ʾ��:
 * @code
    // Set the current time to 20:20:52 May 6, 2008��
    int Ret = 0;
    uint8_t time_str[6];

    time_str[0] = 0x08;      // year��2008-2000=0x08
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
 * @brief	��ȡ��ǰϵͳ���ں�ʱ��
 * @param[out] time_str	-	�������ʱ��ֵ��ָ��, ��BCD����ʽ��ţ�
                - time_str[0]  ��ݣ� +2000Ϊʵ�ʵ����
                - time_str[1]  �·�, Ϊʵ�ʵ��·�ֵ��1-12Ϊ��Чֵ
                - time_str[2]  ��
                - time_str[3]  Сʱ
                - time_str[4]  ����
                - time_str[5]  ����
                - time_str[6]  ����
 * @param[in]  len	-	time_str����ֽ���
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0x00 | ��ȡʱ��ɹ�
 *      !=0x00 | ��ȡʱ��ʧ��
 * @note
    ����ֵ�Ķ���:
    1  ����һ, 2  ���ڶ�, ���� 7  ������.
 *  @par ʾ��:
 *  @code
    uint8_t time_str[7];
    // ��ȡʱ�䲢��ʾ����
    memset(time_str, 0x00, sizeof(time_str));
    sys_get_time((char *)time_str, sizeof(time_str));
    lcdDisplay(0,0,0,��%02x-%02x-%02x %02x:%02x:%02x��,
    time_str[0],time_str[1],time_str[2],time_str[3],time_str[4],time_str[5]);
    //��ʾ�Ľ������Ϊ "19-02-22 15:57:03" ��ʾʱ��Ϊ 2019��2��22��15��57��03��
    @endcode
@else
 * @brief	Read the current system date and time
 * @param[out] time_str	-	Pointer to date and time values in BCD code format��
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
    lcdDisplay(0,0,0,��%02x-%02x-%02x %02x:%02x:%02x��,
    time_str[0],time_str[1],time_str[2],time_str[3],time_str[4],time_str[5]);
    //An example of the results shown is "19-02-22 15:57:03" The time is 15:57:03 on February 22, 2019
    @endcode
@endif	
 */
int sys_get_time(uint8_t *time_str, int len);

/**
@if Chinese
 * @brief  ��ȡ����Ӳ��ģ��������Ϣ
 * @param[in]  module    -	�洢��Ҫ��ȡ��Ӳ��ģ������,��ϸģ����ο�ע����
 * @param[out] type      -	��ȡӲ��ģ���Ӧ�����ͣ��ַ�����ʽ��
 * @param[out] numbers   -	��ȡӲ��ģ�����������
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0 | �ɹ�
 *      -1 | ʧ�ܣ���<errno.h>
 * @note   �л�ȡCPUID�ŷ���>0��ֵ������ʾCPUID���ֽ�����\n
 *         ��������ȡCIDʱ�������жϷ���ֵ��\n
 *         ����-1˵������û��CID������0˵����ȡ�ɹ���\n
 *         type�õ�16���Ƶ�CID�ַ�������������Ҫ����ת��Ϊ������ 
@else 
 * @brief  Obtain local hardware module configuration information
 * @param[in]  module    -	Store the name of the hardware module to be obtained. For details about the module, see the comment bar
 * @param[out] type      -	The value is a string of characters��
 * @param[out] numbers   -	Obtain the maximum number of hardware modules��
 * @return
 *      |returns  |describe |
 *      | --------| --------|
 *      0         | Successed
 *      -1        | Fail��see<errno.h>
 * @note   The value >0 is returned only when the CPUID is obtained, that is, the number of bytes of the CPUID��\n
 *         When used to get CID, the return value must be determined��\n
 *         If -1 is returned, the machine does not have CID. If 0 is returned, the CID is successfully obtained��\n
 *         Type gets a hexadecimal CID string that the caller needs to convert to an integer�� 
@endif 
 */
int sys_get_hardware_config(const char *module, char *type, int *numbers);

/**
@if Chinese
 * @brief   ��ȡϵͳ������Ϣ
 * @note    usrappֻ����ʹ��"USER_"��ͷ��section
 * @param[in]   section -	�û�������Ϣ����
 * @param[in]   key     -	�û�������Ϣ�ؼ���
 * @param[out]  buf     -	��ȡ������Ϣ�Ļ�����
 * @param[in]   buf_len -	����buf�ĳ���
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      >=0   | ��ȡ�������ݳ���
 *      < 0 | ʧ�ܣ���<errno.h>
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
 *      < 0       | Fail��see<errno.h>
@endif 
 */
int sys_get_settting_config(const char *section, const char *key, char *buf, int buf_len);

/**
@if Chinese
 * @brief   ����ϵͳ������Ϣ
 * @note    usrappֻ����ʹ��"USER_"��ͷ��section��\n
 *          ���øú���֮��������sys_save_settting_config()���б��档
 * @param[in]   section -	�û�������Ϣ��������������"USER_"��ͷ���ַ���
 * @param[in]   key     -	�û�������Ϣ�ؼ���
 * @param[out]  value   -	����������Ϣ
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0   | �ɹ�
 *      < 0 | ʧ�ܣ���<errno.h>
 *      -1  | û��Ȩ��
@else 
 * @brief   Set the system configuration information
 * @note    usrapp Only those starting with "USER_" are allowedsection��\n
 *          This function must be called after it is called sys_save_settting_config() saved��
 * @param[in]   section -	The user configuration information segment name must start with "USER_"
 * @param[in]   key     -	User configuration information keyword
 * @param[out]  value   -	Passing in configuration information
 * @return
 *      |returns  |describe|
 *      | --------| --------|
 *      0         | Successed
 *      < 0       | Fail��see <errno.h>
 *      -1        | No permission
@endif 
 */
int sys_set_settting_config(const char *section, const char *key, const char *value);

/**
@if Chinese
 * @brief   ����ϵͳ������Ϣ
 * @note    ��sys_set_settting_config()֮�����
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0   | �ɹ�
 *      < 0 | ʧ�ܣ���<errno.h>
@else 
 * @brief   Save the system configuration information
 * @note    after sys_set_settting_config() is called
 * @return
 *      |returns  |describle|
 *      | --------| --------|
 *      0         | Successed
 *      < 0       | Fail��see <errno.h>
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

// ���ӻ�ȡ��صĵ�ѹֵ�������ٷֱȵĽӿ�

/**
@if Chinese
 * @brief  ϵͳ��ѹ��Ϣ�ṹ��
@else  
 * @brief  System voltage information structure
@endif
 */
typedef struct {
    uint32_t status;            /**<@if Chinese  0- Battery powered only; 1- Positive charging; 2- Fully charged; 3- Voltage is too low; 4- Stop charging @else 0-����ع���;1-�����; 2-������; 3-��ѹ����; 4-ֹͣ��� @endif*/
    uint32_t cur_values;        /**<@if Chinese  ��ǰ��ѹֵ @else  Current voltage                                @endif*/
    uint32_t max_values;        /**<@if Chinese  ��ߵ�ѹֵ @else  Maximum voltage                                @endif*/
    uint32_t min_values;        /**<@if Chinese  ��͵�ѹֵ @else  Minimum voltage                                @endif*/
    uint32_t percent;           /**<@if Chinese  ��ǰ�����ٷֱ�  @else Current electricity percentage             @endif*/
} sys_battery_info_t;

/**
@if Chinese
 * @brief  ��ȡϵͳ�����Ϣ
 * @param[in]	battery_info	-	ϵͳ��ѹ��Ϣ�ṹ��
 * @param[out]  battery_info	-	ϵͳ�����Ϣ
 * @retval
 *          0 - �ɹ� , other - ʧ��
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
 * @brief           У��Ӧ��bin�ļ���ǩ��
 * @param[in]       file_name  - Ӧ��bin�ļ��ľ���·��
 * @return          int
 *
 *                  0:   У��ͨ��
 *                  ��0: У��ʧ��
 * @note            �ýӿ�֧��V1/V2�汾��ǩ����ʽ
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
 * @brief  ��ȡsp�ڲ�RTC����Ƶ��״̬
 * @note   ���������ȱ�����ڵ���5
 * @param[out] type  -	���ջ����������������ֿ��ܽ��:\n
                     "FD-H"   ����Ƶ�ʴ���1MHz \n
                     "FD-L"   ����Ƶ��С��25KHz \n
                     "FD-N"   ����Ƶ�ʴ���������Χ \n
 * @param[out] len   ���뻺�������ȣ�����ʵ�ʻ�ȡ�����ֽ���
 * @return
 *      |����ֵ|ע��|
 *      | --------| --------|
 *      0 | �ɹ�
 *      -1 | ʧ�ܣ���<errno.h>
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
 * @brief           ʹ��/��ֹ ϵͳ��standbyģʽ
 * @param[in]       mode  -	1  ʹ��  0  ��ֹ
 * @note            standbyģʽ��, ϵͳ��̨����������������
@else 
 * @brief           Enable/disable the standby mode of the system
 * @param[in]       mode  -	1 Enable 0 Disable
 * @note            In standby mode, background tasks can still run properly
@endif 
*/
void sys_enable_system_standby(int mode);

/**
@if Chinese
 * @brief           ��ȡ�ڴ���Ϣ
 * @param[out]      total_heap_mem              -	�ڴ���ܴ�С
 * @param[out]      available_heap_mem          -	�����ڴ��С
 * @param[out]      max_available_heap_mem_blk  -	���ɷ�����С
 * @retval          =0 �ɹ�
 * @retval          -1 ʧ��
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
 * @brief			������Ϣ�������߳�
 * @param[in]		signal_ptr  -	��Ϣ���ָ��
 * @param[in]		dest_id		-	Ŀ���̵߳�id
 * @retval          0 ���ͳɹ�
 * @retval          -1 ����ʧ��
 * @note            ���͵�ֻ����Ϣ����׵�ַ
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
 * @brief			�߳��ж�ȡ�����̷߳���������Ϣ��������Ϣ����ú�������
 * @param[in]		thread_id   -	Դ�̵߳�id
 * @retval          �ǿ� �ɹ���������Ϣ���ָ��
 * @retval          NULL ��ȡʧ��
 * @note            ע��ú������������õģ����յ�ֻ����Ϣ����׵�ַ
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
 * @brief			��̬����������ָ����С���ڴ��
 * @param[in]		size        -	�ڴ��Ĵ�С����λ�ֽ�
 * @retval          �ǿ� ����ɹ�������ָ�򱻷����ڴ��ָ��
 * @retval          NULL ����ʧ��
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
 * @brief			�ͷŶ�̬������ڴ�
 * @param[in]		sig        -	��Ҫ�ͷ��ڴ��ָ��
 * @retval          =0 �ͷųɹ�
 * @retval          -1 �ͷ�ʧ��
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
 * @brief			����
 * @param[in]		expinfo     -	�쳣��Ϣ
 * @param[in]		file        -	�ļ����ַ���
 * @param[in]		line        -	�к�
 * @note            �Ǳ�׼�������������Ǵ������ԣ�����ֹ����ִ����ʾ����
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
* @brief  ��ȡ�豸Ψһ���
* @param[out]  usn -	����豸Ψһ��ţ���'\0'���ַ�����ʽ����Ҫ��ռ䲻����32�ֽ�
* @param[in]   len -	����usn�������Ч����
* @return
*		   - 0 �ɹ�
*		   - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
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
* @brief  ��ȡ��Ȩ��
* @param[out]  license	-	�����Ȩ��
* @param[in]   len		-	��Ҫ��ȡ��license��С
* @return
*		   - ʵ�ʶ�ȡ�ĳ���	�ɹ�
*		   - <0 ʧ�ܣ�������Ӧ�ķ���ֵ
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
        @brief          ���ü��̱����״̬
        @param[in]      status    ״̬��0-�رգ���0-��
        @retval                0             ���óɹ�
        @retval                ����          ����ʧ��
 @else
        @brief          Set the keyboard backlight state
        @param[in]      status    Keyboard backlight status��0:close��non-0:open
        @retval                0             successful
        @retval                other         Failure
 @endif
*/
int sys_kbd_backlight_set_status(uint8_t status);

/*!
 @if Chinese
        @brief          ��ȡ���̱����״̬
        @param[out]     status                 ״̬
        @retval                0                 ��ȡ�ɹ�
        @retval                -EINVAL           ��������д���statusΪ��ָ��
        @retval                ����              ��ȡʧ��
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
* @brief  ����ϵͳlogo
* @param[in]   filename Ҫ���µ�logo�ļ�·��,����"/home/user0/np.logo"
* @return
*	 - 0    �ɹ� 
*	 - -1   �̼�δ֧�ָýӿ�
*	 - ���� ʧ��
*/
int sys_update_logo(const char *filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SYSTEM_H__ */

/** @} */

