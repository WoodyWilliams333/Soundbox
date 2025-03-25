/**
 @if Chinese
	 * @brief       此模块用于描述 <strong>rtl 8710 WIFI模块</strong> 相关的接口
	 * @author      jeffery
	 * @date        2019-01-22
	 * @version     V1.0
	 *
	 * @par 修订记录
	 * 日期          | 作者            | 描述
	 * ------------- | --------------- | ----
	 * 2018/12/1     | jeffery         | 创建文件
	 * 2022/04/20    | Wenming         | 增加英文注释
 @else	 
	 * @brief       This module is used to describe <strong>rtl 8710 WIFI module</strong> interfaces module
	 * @author      jeffery
	 * @date        2019-01-22
	 * @version     V1.0
	 *
	 * @par Change History
	 * Date          | Author          | Desc
	 * ------------- | --------------- | ----
	 * 2018/12/1     | jeffery         | Create file
	 * 2022/04/20    | Wenming         | Add English description
 @endif	 
*/


/**
 * @defgroup WIFI WIFI
 * @{
*/

#ifndef __WIFI_API_H__
#define __WIFI_API_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
	* @brief  该枚举类型列出了扫描到的热点安全类型以及连接热点时wifi支持的安全方式.
  @else 
	* @brief  This enumeration type lists the security types of scanned hotspots and the security modes supported by wifi when connecting to hotspots.
  @endif 
*/
typedef enum {
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_WPA2_ENTERPRISE,  /**< authenticate mode : WPA2_ENTERPRISE */
    WIFI_AUTH_WPA3_PSK,         /**< authenticate mode : WPA3_PSK */
    WIFI_AUTH_WPA2_WPA3_PSK,    /**< authenticate mode : WPA2_WPA3_PSK */
    WIFI_AUTH_WAPI_PSK,         /**< authenticate mode : WAPI_PSK */
    WIFI_AUTH_OWE,              /**< authenticate mode : OWE */
    WIFI_AUTH_MAX,
    SECURITY_UNKNOWN        = -1  
} ap_security_t;

/**
 @if Chinese
	* @brief  该枚举列出了wifi的连接状态.
 @else 
	* @brief  This enumeration lists the connection status of wifi.
 @endif	  
  */
typedef enum {
    WIFI_JOIN_DISCONNECT = 0,                   /**< WIFI module disconnected                */
    WIFI_JOIN_CONNECTING,                       /**< WIFI module is connecting               */
    WIFI_JOIN_CONNECTED,                        /**< WIFI module connected                   */
} wifi_join_status;

#define WIFI_COMPILE_VERSION        0x61
#define WIFI_COMPILE_DATA           0x62
#define WIFI_COMPILE_AUTHOR         0x63
#define WIFI_SVN                    0x64



#define WIFI_OPT_APWEBDISABLE   0


/**
 @if Chinese
	* @brief  用于描述SSID.
 @else	
	* @brief  Used to describe an SSID.
 @endif		
  */
typedef struct {
    unsigned char len;                          /**<@if Chinese SSID 长度 @else	SSID length						@endif*/
    unsigned char val[33];                      /**<@if Chinese SSID 名称 (AP 名称) @else	SSID name (AP name)	@endif*/
} ssid_t;


/**
 @if Chinese
	* @brief  用于描述6字节长度的mac地址
 @else	
	* @brief  This parameter is used to describe a 6-byte MAC address
 @endif		
*/
typedef struct {
    unsigned char octet[6];                     /**<@if Chinese 唯一的 6-bytes MAC地址 @else Only 6-byte MAC address	@endif*/
} mac_t;

/**
 @if Chinese
  * @brief 描述一个热点信息的信息
  * @note  根据802.11协议, ssid 长度小于等于32字节
 @else 
  * @brief Information that describes a hotspot
  * @note  According to 802.11, the SSID length must be shorter than or equal to 32 bytes
 @endif	  
  */
typedef struct {
    int security_type;                /**<@if Chinese 安全类型   @else	Safety type		@endif*/
    ssid_t        SSID;                         /**<@if Chinese SSID       @else	SSID  			@endif*/
    mac_t         BSSID;                        /**<@if Chinese MAC地址    @else	MAC address		@endif*/
    signed short  signal_strength;              /**<@if Chinese 信号强度   @else	Signal strength	@endif*/
} ap_info_t;

/**
 @if Chinese
  * @brief      描述wifi当前网络信息
 @else 
  * @brief      Description Current wifi network information
 @endif	  
  */
typedef struct {
    unsigned char ip[4];                        /**<@if Chinese IP地址     @else	IP address		@endif*/
    unsigned char gate[4];                      /**<@if Chinese 网关地址   @else	Gate address	@endif*/
    unsigned char mask[4];                      /**<@if Chinese 掩码地址   @else	Mask address	@endif*/
    int security_type;                /**<@if Chinese 安全类型   @else	Safety type		@endif*/
    int rssi;                                   /**<@if Chinese 信号强度   @else	Signal strength	@endif*/
    unsigned char ssid[33];                     /**<@if Chinese 网络名称   @else	Network name	@endif*/
    mac_t mac;                                  /**<@if Chinese MAC地址    @else	MAC address		@endif*/
} __attribute__((aligned(4))) network_info_t;

/**
 @if Chinese
	* @brief      AP  配网wifi信息
 @else
	* @brief     AP information
 @endif	
  */
typedef struct {
	ssid_t 			ssid;                        /**ssid        */ 
	int		security_type;           /**< 安全类型  */
	unsigned char 		password[65];            /**< 密码      */
	int 				password_len;            /**< 密码长度  */
	int					channel;                 /**< 信道      */
	int					language;                /**< 中英文    */
} __attribute__((aligned(4))) ap_mode_info_t;

/**
 @if Chinese
	* @brief      扫描wifi热点显示时的显示语言
 @else
	* @brief     Display language when scanning wifi hotspot display
 @endif	
  */
typedef enum {
	LANG_ENGLISH = 0,
    LANG_CHINESE = 1,
} wifi_language_e;

/**
 @if Chinese
	  * @brief 打开wifi
	  * @return
	  *         0       ----- 成功.\n
	  *         -1      ----- 失败.\n
 @else
	  * @brief Open wifi
	  * @return
	  *         0       ----- Success.\n
	  *         -1      ----- Fail.\n
 @endif		  
  */
int wifi_open(void);

/**
@if Chinese
  * @brief 关闭wifi
 @else  
  * @brief Close wifi
 @endif	  
  */
void wifi_close(void);

/**
@if Chinese
  * @brief 判断wifi是否打开
  * @return
  *          1  wifi已经打开.\n
  *          0  wifi没有打开.\n
 @else   
  * @brief Check whether wifi is on
  * @return	1  wifi open.\n
  * @return	0  wifi not open.\n
@endif	  
  */
int wifi_is_open(void);

/**
@if Chinese
  * @brief  启动热点扫描
  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
  * @note   调用该接口后只是启动网络扫描, 接口不会阻塞，会立马返回
@else   
  * @brief  Start Hotspot Scanning
  * @return 0-Success. 
	@return	-1:Fail.(Use the errno value to get more error information)
  * @note   When this interface is called, it simply starts network scanning. The interface does not block and returns immediately
@endif	 
  */
int wifi_start_scan_networks(void);

/**
 @if Chinese
  * @brief  获取扫描状态
  * @return
  *         0   ----- 正在扫描中.\n
  *         1   ----- 扫描完成.\n
  *        -1  ------ 扫描失败.\n
  * @note   调用wifi_start_scan_networks() 启动扫描后, 可以调用该接口查询扫描状态。
  *         其他情况下调用该接口返回值无意义
 @else  
  * @brief  Get scan Status
  * @return	0   ----- Scaning.\n
  *         1   ----- Scan success.\n
  *        -1  ------ Scan fail.\n
  * @note   After a scan is started by calling wifi_start_scan_networks(), you can call this interface to query the scan status。
  *         In other cases, it is meaningless to call the return value of this interface
 @endif	  
  */
int wifi_is_scan_complete(void);

/**
 @if Chinese
  * @brief  获取扫描结果
  * @param[out]  ap_info	-	用于存放扫描结果的数组
  * @param[out]  size		-	存放扫描结果的数组的大小
  * @return 当扫描成功后，返回扫描到的热点数量, 扫描失败返回-1, 使用errno值获取更多错误信息
  * @note   该接口会阻塞到有扫描完毕后才返回                                         <br />
  *         int wifi_start_scan_networks(void),                                     <br />
  *         int wifi_is_scan_complete(void),                                         <br />
  *         int wifi_get_scan_data(ap_info_t *ap_info, int size)                     <br />
  *         三个接口组合起来有两种使用方法。                                         <br />                                                                             <br />
  * @par 示例:
    @code
            第一种:
                {
                    int return, is_scan_finish = 0, ap_num;
                    ap_info_t aplist[MAX_WIFI_INFO_LIST];
                    // 开始热点扫描
                    return = wifi_start_scan_networks();
                    // 等待热点扫描完成
                    do {
                        ... ;
                        ... ;
                        ... ;

                        is_scan_finish = wifi_is_scan_complete();
                    } while (is_scan_finish == 0);
                        ... ;
                        ... ;

                    // 获取已扫描到的热点信息
                    ap_num = wifi_get_scan_data(aplist, MAX_WIFI_INFO_LIST);
            }

            第二种:
                {
                    int return, ap_num;
                    ap_info_t aplist[MAX_WIFI_INFO_LIST];
                    // 开始热点扫描
                    return = wifi_start_scan_networks();
                //在未扫描结束前, 该接口会一直阻塞
                    ap_num = wifi_get_scan_data(aplist, MAX_WIFI_INFO_LIST);
            }
    @endcode
@else	

  * @brief  Obtaining scan results
  * @param[out]  ap_info	-	An array to store the scan results
  * @param[out]  size		-	The size of the array that holds the scan results
  * @return If the scan succeeds, the number of detected hotspots is returned. If the scan fails, -1 is returned. Use the errno value to obtain more error information
  * @note   The interface will block until a scan is complete                                         <br />
  *         int wifi_start_scan_networks(void),                                     <br />
  *         int wifi_is_scan_complete(void),                                         <br />
  *         int wifi_get_scan_data(ap_info_t *ap_info, int size)                     <br />
  *         The three interfaces can be used in two ways together。                                         <br />                                                                             <br />
  * @par The sample:
    @code
            One:
                {
                    int return, is_scan_finish = 0, ap_num;
                    ap_info_t aplist[MAX_WIFI_INFO_LIST];
                    // Start Hotspot Scan
                    return = wifi_start_scan_networks();
                    //Wait for the hotspot scan to complete
                    do {
                        ... ;
                        ... ;
                        ... ;

                        is_scan_finish = wifi_is_scan_complete();
                    } while (is_scan_finish == 0);
                        ... ;
                        ... ;

                    // Obtain the detected hotspot information
                    ap_num = wifi_get_scan_data(aplist, MAX_WIFI_INFO_LIST);
            }

            Two:
                {
                    int return, ap_num;
                    ap_info_t aplist[MAX_WIFI_INFO_LIST];
                    // Start Hotspot Scan
                    return = wifi_start_scan_networks();
                //The interface is blocked until the scanning is complete
                    ap_num = wifi_get_scan_data(aplist, MAX_WIFI_INFO_LIST);
            }
    @endcode
@endif	
  *
  */
int wifi_get_scan_data(ap_info_t *ap_info, int size);

/**
 @if Chinese
  * @brief  连接热点
  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
  * @param[in]  ssid	-	执行连接的网络的ssid
  * @param[in]  key		-	执行连接的网络的key
  *
  * @note   该接口调用后会立马返回, 返回值只代表接口执行是否成功, 不代表是否连接成功 <br />
  *         返回连接是否成功见下
 @else  
  * @brief  Connect wifi
  * @return	-	0-success, -1:Fail, (Use the errno value to get more error information)
  * @param[in]  ssid	-	wifi ssid
  * @param[in]  key		-	wifi key
  *
  * @note   This interface is returned immediately after the call, and the return value only indicates whether the interface was successfully executed, not whether the connection was successful <br />
 @endif	 
  */
int wifi_connect(const char *ssid, const char *key);

/**
@if Chinese
  * @brief  热点连接状态
  * @return  int	-	@ref wifi_join_status
  *
  * @note   该接口有三个返回值, 参见wifi_join_status. 执行接口          <br />
  *         int wifi_connect(const char *ssid, const char *key)         <br />
  *         后可以调用该接口判断是否连接成功                            <br />
  * @par 示例:
    @code
        {
            int connect_stat = WIFI_JOIN_DISCONNECT;
            ret = wifi_connect(ssidbuf, keybuf);
            // 等待WIFI状态
            if (!ret) {
                do {
                    connect_stat = wifi_get_join_status();
                    if (connect_stat == WIFI_JOIN_CONNECTING) {
                        ... ;
                        ... ;
                        msleep(50);
                    }
                } while (connect_stat == WIFI_JOIN_CONNECTING);
            }

            if(ret || connect_stat == WIFI_JOIN_DISCONNECT) {
                printf("连接失败 \n");
            }
        }
    @endcode
	
@else	
  * @brief  wifi connect status
  * @return  int	-	@ref wifi_join_status
  *
  * @note   This interface has three return values, see wifi_join_status. Implement interface          <br />
  *         int wifi_connect(const char *ssid, const char *key)         <br />
  *         Call this interface to determine whether the connection is successful                            <br />
  * @par The sample:
    @code
        {
            int connect_stat = WIFI_JOIN_DISCONNECT;
            ret = wifi_connect(ssidbuf, keybuf);
            // wait wifi status
            if (!ret) {
                do {
                    connect_stat = wifi_get_join_status();
                    if (connect_stat == WIFI_JOIN_CONNECTING) {
                        ... ;
                        ... ;
                        msleep(50);
                    }
                } while (connect_stat == WIFI_JOIN_CONNECTING);
            }

            if(ret || connect_stat == WIFI_JOIN_DISCONNECT) {
                printf("Connect fail \n");
            }
        }
    @endcode
@endif	
  */
int wifi_get_join_status(void);

/**
@if Chinese
  * @brief  wifi是否连接上热点
  * @return 1 表示已经连接上 0 表示未连接
@else 
  * @brief  check wifi is connected
  * @return	0	-	Success
  * @return	-1	-	Fail
 @endif 
*/
int wifi_is_connected(void);

/**
 @if Chinese
  * @brief  断开连接
  * @return  - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
 @else  
  * @brief  disconnect wifi
  * @return	0	-	Success
  * @return	-1	-	Fail
@endif		
  */
int wifi_disconnect(void);

/**
 @if Chinese
  * @brief  获取当前网络信息
  * @param[out] info	-	请参考结构体network_info_t
  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
  @else	 
  * @brief  Get the current network information
  * @param[out] info	-	See the structure network_info_t
  * @return	0	-	Success
  * @return	-1	-	Fail
 @endif	  
  */
int wifi_get_network_info(network_info_t *info);

/**
 @if Chinese
	* @brief  获取wifi固件版本信息
 @else	
	* @brief  Obtain wifi firmware version information
 @endif		
  */
int wifi_get_firmware_info(int module, char *buf, int size);

/**
 @if Chinese
  * @brief  搜索、连接AP热点
  * @param[in] timeout	-	超时时间，单位为秒
  * @param[in] language	-	参考 @ref  wifi_language_e
  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
 @else 
  * @brief  Search for and connect to AP hotspots
  * @param[in] timeout	-	Timeout period, in seconds
  * @param[in] language	-	reference @ref  wifi_language_e
  * @return 
  	  	  0-Success<br>
		  -1-Fail
  @endif	 
  */
int wifi_search_select_ap(int timeout, int language);

/**
 @if Chinese
  * @brief  检测wifi是否活着
  * @return	-	wifi活着返回1，否则返回0
 @else  
  * @brief  Check wifi if alive
  * @return	1	-	alive  
  * @return	0	-	not alive
 @endif	  
  */
int wifi_check(void);

/**
 @if Chinese
	  * @brief  启动airkiss配网，WiFi进入配网模式
	  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
  @else   
	  * @brief  Start airKiss network and WiFi enters network mode
	  * @return 
	  	  0-Success
		  -1-Fail
  @endif	  
  */
int wifi_airkiss_start(void);

/**
 @if Chinese
  * @brief  停止airkiss配网，WiFi恢复普通模式
  * @return - 成功返回0, 失败返回-1, 使用errno值获取更多错误信息
 @else  
  * @brief  Stop the Airkiss network and restore the normal WiFi mode
  * @return 
	  0-Success
	  -1-Fail
 @endif	  
  */
int wifi_airkiss_stop(void);

/**
 @if Chinese
	 * @brief  判断WiFi是否还处于airkiss配网模式
	 * @return 出于配网模式返回1，普通模式返回0
 @else	 
	 * @brief  Check whether WiFi is still in AirKiss network configuration mode
	 * @return 
	 *1-Distribution network model<br>
	 *0-Normal mode
 @endif	 
 */
int wifi_is_airkiss_stop(void);

/**
@if Chinese
 * @brief		 判断airkiss 是否完成
 * @param[in]  ssid	                -	执行连接的网络的ssid
 * @param[in]  password		        -	执行连接的网络的key
 * @retval			=1              -	配网完成 
 * @retval			=0              -	配网未完成
 * @retval          -1              -	配网连接失败
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			 is airkiss is done?
 * @param[in]     ssid	            -	wifi ssid
 * @param[in]     password		    -	wifi key
 * @retval			=0              -	airKiss is no finish
 * @retval          -1         	    -	airKiss err 
 * @retval          =1              -	Success
 * @note           
@endif 
*/    
int wifi_airkiss_is_done(char ssid[33], char password[65]);

  
/**
@if Chinese
 * @brief		 开始AP 配网.	
 * @param[in]		ap_info 	    -   输入的配网信息
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            
@else 
 * @brief			 start AP mode.
 * @param[in]		ap_info 	    -   ap mode infomation
 * @retval			=0              -	Success
 * @retval          -1         	    -	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/      
int wifi_ap_mode_start(ap_mode_info_t *ap_info);

/**
@if Chinese
 * @brief		 判断ap 配网 是否完成
 * @param[in]  ssid	                -	执行连接的网络的ssid
 * @param[in]  password		        -	执行连接的网络的key
 * @retval			=1              -	配网完成 
 * @retval			=0              -	配网未完成
 * @note        
@else 
 * @brief			 is ap mode is done?
 * @param[in]     ssid	            -	wifi ssid
 * @param[in]     password		    -	wifi key
 * @retval			=0              -	ap mode  is no finish
 * @retval          =1              -	Success
 * @note           
@endif 
*/       
int wifi_ap_mode_is_done(char ssid[33], char password[65]);

  /**
@if Chinese
 * @brief		 停止AP模式.	
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            
@else 
 * @brief			 stop ap mode.
 * @retval			=0              -	Success
 * @retval          -1         	    -	fail
 * @note            
@endif 
*/  
int wifi_ap_mode_stop(void);

  
 /**
@if Chinese
 * @brief		 用于清除保存的SSID	
 * @param[in]  ssid	        -	执行清除的网络的ssid 
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            
@else 
 * @brief			 Used to clean SSID information.
 * @param[in]  ssid	        -	 input clean ssid 
 * @retval			=0              -	Success
 * @retval          -1         	    -	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/ 
  
int wifi_clean_connet_info(const char *ssid);

/**
@if Chinese
 * @brief		 用于取信号值	
 * @param[out]		rssi		        -	信号值
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			 Used to get SSID signal strength.
 * @param[out]		rssi		    -	signal strength
 * @retval			=0              -	Success
 * @retval          -1         	    -	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/ 
 
int wifi_get_rssi(int *rssi);

/**
@if Chinese
 * @brief		 设置WIFI属性	
 * @param[in]		cmd		        -	命令号
 * @param[in]		opt 	        -   输入的设置属性
 * @param[in]		optlen 	        -   属性大小
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			get host address info
 * @param[in]		cmd		    -	command no
 * @param[in]		opt 	    -   input option
 * @param[in]		optlen 	    -   option len
 * @retval			=0              -	Success
 * @retval          -1         	    -	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/
int wifi_set_opt(int cmd,void *opt,int optlen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WIFI_API_H__ */

/** @} */

