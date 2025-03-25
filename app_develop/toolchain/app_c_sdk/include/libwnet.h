/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app wnet模块</strong> 相关的接口
	 * @par 文件    libwnet.h
	 * @author		yangjing
	 * @date        2020-03-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-03-30    | 1.0.0        | yangjing      | 创建文件
	 * 2022-04-30    | 1.0.1        | lydia         | 增加英文注释 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app wnet </strong>  module
	 * @par file    libwnet.h
	 * @author		yangjing
	 * @date        2020-03-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-03-30    | 1.0.0        | yangjing      | create file
	 * 2022-04-30    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup libwnet 通讯
 @else
	@defgroup libwnet communication 
 @endif
 * @{
*/
#ifndef __LIBWNET_H__
#define __LIBWNET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/socket.h>

#ifndef MAYBE_UNUSE
#define MAYBE_UNUSE(x)              (void)(x)
#endif

#ifndef UNUSE
#define UNUSE(x)                    (void)(x)
#endif

#ifndef __attribute_used__
#define __attribute_used__          __attribute__((__used__))
#endif

struct wnet_event_cb_t { 
	int event; 
	int (*cb)(int event, int result);
};

#define wnet_register(event, callback) \
        static const struct wnet_event_cb_t wnet_cb_##callback \
        __attribute_used__ __attribute__((section(".wnet.event.handler"))) = {    \
        event, callback                                                            \
};

typedef enum {
    CHECK_SIM_EVENT                         = 0x00,                         
    CHECK_PPP_EVENT                         = 0x01,                         
} WnetStatus_e;

/**
 @if Chinese
	@brief  该枚举类型列出了通讯类型.
 @else
	@brief  This enumerated type lists the communication types.
 @endif
  */
typedef enum {
    CT_WIFI                         = 0x01,                         
    CT_GPRS                         = 0x02,                         
    CT_CDMA                         = 0x04,                         
    CT_TCPIP                        = 0x08,                         
    CT_RS232                        = 0x10,                         
    CT_BT                           = 0x20,                         
    CT_MODEM                        = 0x40,                         
    CT_MODEMPPP                     = 0x80,                         
    CT_ALLCOMM                      = 0xFF,                        
} CommType_e;

/**
 @if Chinese
	@brief  系统通讯模块的通道选择枚举.
 @else
	@brief  communication type.
 @endif
  */
typedef enum {
    CS_GPRS                         = 0x00,                         
    CS_WIFI                         = 0x01,                         
} CommSolt_e;

/**
 @if Chinese
	@brief  该枚举类型列出了SSL版本.
 @else
	@brief  This enumerated type lists the SSL version.
 @endif
  */
typedef enum { 
    SV_TLS_V1_2                     = 0x04, /**< @if Chinese TLS V1.2 @else  TLS V1.2 @endif */
    SV_TLS_V1_3                     = 0x05, /**< @if Chinese TLS V1.3 @else  TLS V1.3 @endif */
} SSLVersion_e;

/**
 @if Chinese
	@brief  该枚举类型列出了SSL认证模式.
 @else
	@brief  This enumerated type lists the SSL authentication mode.
 @endif
  */
typedef enum {
    SVM_VERIFY_NONE                 = 0x00,  /**< @if Chinese SSL握手忽略证书校验 @else  ignore SSL certificate verification @endif */      
    SVM_VERIFY_SINGLE               = 0x01,  /**< @if Chinese SSL单向认证 @else  SSL single certificate verification @endif */  
    SVM_VERIFY_PEER                 = 0x02,  /**< @if Chinese SSL双向认证 @else  SSL double certificate verification @endif */
} SSLVerifyMode_e;

/**
 @if Chinese
	@brief  SSL调试模式.
 @else
	@brief  SSL debug mode.
 @endif
  */
typedef enum {
    SDM_DEBUG_OFF                   = 0x00,                         
    SDM_DEBUG_ON                    = 0x01,                        
} SSLDebugMode_e;
/**
 @if Chinese
	@brief  该枚举类型列出了网络通讯协议类型.
 @else
	@brief  This enumerated type lists the communication protocol type.
 @endif
  */
typedef enum {
    SOCK_TCP                        = 0x01,                         
    SOCK_UDP                        = 0x02,                         
    SOCK_SSL                        = 0x04 | 0x01,                  
} SockType_e;

/**
 @if Chinese
	@brief  该枚举类型列出了访问服务器的方式.
 @else
	@brief  This enumerated type lists the method to access the server.
 @endif
  */
typedef enum {
    HOST_IN_IP                      = 0x00,                         
    HOST_IN_DNS                     = 0x01,                               
} HostInType_e;

/**
 @if Chinese
	@brief  该枚举类型列出了异步连接的状态.
 @else
	@brief  This enumerated type lists the status of asynchronous connection.
 @endif
  */
typedef enum {
    // 连接空闲状态，稳定状态，收到连接动作会执行状态切换
    ASYNC_APP_ST_CONNECT_IDLE       = 0x00,  /**< @if Chinese 连接空闲 @else connect idle @endif */

    // 连接状态，不稳定状态，会随时切换
    ASYNC_APP_ST_PPP_CONNECT        = 0x01,  /**< @if Chinese PPP连接 @else PPP connect @endif */
    ASYNC_APP_ST_DNS                = 0x02,  /**< @if Chinese DNS域名解析 @else DNS domain name resolution @endif */ 
    ASYNC_APP_ST_TCP_CONNECT        = 0x03,  /**< @if Chinese TCP连接 @else TCP connect @endif */
    ASYNC_APP_ST_SSL_CONNECT        = 0x04,  /**< @if Chinese SSL连接 @else SSL connect @endif */

    // 连接结束状态，稳定状态，收到关闭动作会执行状态切换
    ASYNC_APP_ST_CONNECT_FAIL       = 0x05,  /**< @if Chinese 连接失败 @else connect fail @endif */
    ASYNC_APP_ST_CONNECT_OK         = 0x06,  /**< @if Chinese 连接成功 @else connect success @endif */
    ASYNC_APP_CONNECT_CLOSE_DONE	= 0x08,	 /**< @if Chinese 连接完成 @else connect complete @endif */
} AsyncConnectStateAPP_e;

/* DNS 解析状态 */
typedef enum {
	ASYNC_DNS_PASER_FAIL				= -1,
	ASYNC_DNS_PASER_OK					= 0,
} AsyncDnsPaserState_e;

//SSL异步连接默认支持的加密套件列表
#define SSL_APP_DEFAULT_CIPHER_LIST     "AES256-SHA:AES128-SHA:DES-CBC3-SHA:AES256-SHA256:AES128-SHA256"
/**< @if Chinese SSL异步连接默认支持的加密套件列表 @else default encryption suite for asynchronous connection @endif */

// 目前可支持的加密套件列表，推荐应用层不做设置，使用默认加密套件即可
#if 0
"Cur version support 53 cipher:"
"RC4-SHA"
"RC4-MD5"
"DES-CBC3-SHA"
"AES128-SHA"
"AES256-SHA"
"NULL-SHA"
"NULL-SHA256"
"DHE-RSA-AES128-SHA"
"DHE-RSA-AES256-SHA"
"DHE-PSK-AES256-GCM-SHA384"
"DHE-PSK-AES128-GCM-SHA256"
"DHE-PSK-AES256-CBC-SHA384"
"DHE-PSK-AES128-CBC-SHA256"
"DHE-PSK-NULL-SHA384"
"DHE-PSK-NULL-SHA256"
"ECDHE-RSA-AES128-SHA"
"ECDHE-RSA-AES256-SHA"
"ECDHE-ECDSA-AES128-SHA"
"ECDHE-ECDSA-AES256-SHA"
"ECDHE-RSA-RC4-SHA"
"ECDHE-RSA-DES-CBC3-SHA"
"ECDHE-ECDSA-RC4-SHA"
"ECDHE-ECDSA-DES-CBC3-SHA"
"AES128-SHA256"
"AES256-SHA256"
"DHE-RSA-AES128-SHA256"
"DHE-RSA-AES256-SHA256"
"AES128-GCM-SHA256"
"AES256-GCM-SHA384"
"DHE-RSA-AES128-GCM-SHA256"
"DHE-RSA-AES256-GCM-SHA384"
"ECDHE-RSA-AES128-GCM-SHA256"
"ECDHE-RSA-AES256-GCM-SHA384"
"ECDHE-ECDSA-AES128-GCM-SHA256"
"ECDHE-ECDSA-AES256-GCM-SHA384"
"ECDHE-RSA-AES128-SHA256"
"ECDHE-ECDSA-AES128-SHA256"
"ECDHE-RSA-AES256-SHA384"
"ECDHE-ECDSA-AES256-SHA384"
"ECDHE-RSA-CHACHA20-POLY1305"
"ECDHE-ECDSA-CHACHA20-POLY1305"
"DHE-RSA-CHACHA20-POLY1305"
"ECDHE-RSA-CHACHA20-POLY1305-OLD"
"ECDHE-ECDSA-CHACHA20-POLY1305-OLD"
"DHE-RSA-CHACHA20-POLY1305-OLD"
"IDEA-CBC-SHA"
"ECDHE-ECDSA-NULL-SHA"
"ECDHE-PSK-NULL-SHA256"
"ECDHE-PSK-AES128-CBC-SHA256"
"PSK-CHACHA20-POLY1305"
"ECDHE-PSK-CHACHA20-POLY1305"
"DHE-PSK-CHACHA20-POLY1305"
"EDH-RSA-DES-CBC3-SHA"
#endif

// 仅支持IPV4协议
#define MAX_HOST_CNT                2                               // 最多支持2个服务器主机参数
#define MAX_IP_CNT                  2                               // 1个域名最多支持解析出2个ip
#define MAX_IP_LEN                  16                              // 255.255.255.255，最多16字节  
#define MAX_PORT_LEN                6                               // 服务器端口最大长度
#define MAX_HOST_NAME               256                             // 服务器域名地址最大长度
#define MAX_SIM_PIN_LEN             16                              // SIM卡的PIN最大长度
#define MAX_PWD_LEN                 16                              // SIM卡的PWD最大长度
#define MAX_UID_LEN                 64                              // SIM卡的UID最大长度
#define MAX_APN_LEN                 64                              // SIM卡的APN最大长度
#define MAX_SSL_CERT_DEPTH          5                               // 最多支持5级证书链的校验
#define MAX_CIPHER_LIST_LEN         64                              // 字符串形式的加密套件的最大长度
#define MAX_CA_CERT_CNT             3                               // 最多支持3组CA证书输入
#define MAX_FILE_NAME_LEN           48                              // 文件全路径字符串最大长度
#define MAX_PWD_LEN                 16                              // PEM文件密码的最大长度
#define MIN_VERSION_LEN             64                              // 获取版本信息的buffer最少长度

/**
 @if Chinese
	@brief  GPRS等无线模块拨号参数配置.
 @else
	@brief  the param of wireless dialing.
 @endif
  */
typedef struct {
    char                            apn[MAX_APN_LEN+1];         /**< @if Chinese 拨号号码 @else dial number @endif */
    char                            uid[MAX_UID_LEN+1];         /**< @if Chinese 拨号用户id @else dialing user ID @endif */     
    char                            pwd[MAX_PWD_LEN+1];         /**< @if Chinese 拨号用户密码 @else dialing user password @endif */      
    char                            sim_pin[MAX_SIM_PIN_LEN+1]; /**< @if Chinese SIM卡密码 @else SIM card PIN @endif */   
} ST_WIRELESS_PARAM;

/**
 @if Chinese
	@brief  服务器主机的IP和端口信息.
 @else
	@brief  IP and port information of server host.
 @endif
  */
typedef struct {
    char                            ip[MAX_IP_LEN];                 
    char                            port[MAX_PORT_LEN];             
} ST_HOST_IP_PARAM;

/**
 @if Chinese
	@brief  服务器主机的参数信息.
 @else
	@brief  the param information of server host.
 @endif
  */
typedef struct {
    char                            name[MAX_HOST_NAME];  /**< @if Chinese 主机域名地址 @else domain name address @endif */    
    ST_HOST_IP_PARAM                ip_port;              /**< @if Chinese 主机IP和端口信息 @else IP and port @endif */            
} ST_HOST_PARAM;

/**
 @if Chinese
	@brief  SSL通讯的配置参数.
 @else
	@brief  the SSL configuration parameter.
 @endif
  */
typedef struct {
    uint8_t         version;                                    /**< @if Chinese SSL通讯的版本 @else SSL version @endif */  
    uint8_t         depth;                                      /**< @if Chinese 证书链校验支持的最大深度 @else maximum depth supported by certificate chain verification @endif */
    uint8_t         mode;                                       /**< @if Chinese SSL握手的方式，单向认证或双向认证 @else SSL handshake method,single or double @endif */    
    uint8_t         debug;                                      /**< @if Chinese 是否开启SSL调试，为1表示打开，默认关闭 @else SSL debug,1 is open, default is close @endif */                                                                                
    const char      cipher_list[MAX_CIPHER_LIST_LEN];           /**< @if Chinese SSL握手指定加密套件，可配置为""，表示使用默认加密套件 @else SSL cipher suite,configurable as "",indicates that the default suite is used @endif */                                                                                     
    const char      ca_cert[MAX_CA_CERT_CNT][MAX_FILE_NAME_LEN]; /**< @if Chinese SSL握手需要的CA证书列表(PEM格式的标准X509证书,文件系统全路径) @else CA certificate list(X509,full path) @endif */                                                                     
    const char      user_cert[MAX_FILE_NAME_LEN];                 /**< @if Chinese 客户端公钥证书(PEM格式的标准X509证书,文件系统全路径) @else client public key(X509,full path) @endif */ 
    const char      user_key[MAX_FILE_NAME_LEN];                  /**< @if Chinese 客户端私钥文件(文件系统全路径) @else client private key(full path) @endif */  
    const char      user_key_pwd[MAX_PWD_LEN];                    /**< @if Chinese 客户端私钥文件的密码(可以无密码,文件系统全路径) @else client private key password(full path,no password is allowed) @endif */   
} ST_SSL_PARAM;

/**
 @if Chinese
	@brief  异步连接的输入参数.
 @else
	@brief  the input parameter for asynchronous connection.
 @endif
  */
typedef struct {
    uint32_t                        timeout_ms;          /**< @if Chinese 连接超时时间(毫秒) @else connect timeout(ms) @endif */ 
    uint8_t                         protocol_type;       /**< @if Chinese 通讯协议类型(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...) @endif */   
    uint8_t                         dns_ip;              /**< @if Chinese 是否使用域名访问，为1表示域名方式，为0表示IP方式 @else use domain name access,1-DNS,0-IP @endif */     
    ST_WIRELESS_PARAM               wireless;            /**< @if Chinese 无线拨号参数 @else the param of wireless dialing @endif */
    ST_HOST_PARAM                   host;                /**< @if Chinese 主机参数 @else the param of server host @endif */       
    ST_SSL_PARAM                    ssl;                 /**< @if Chinese SSL参数 @else the SSL param @endif */           
} ST_ASYNC_CONNECT_PARAM;

/**
 @if Chinese
	@brief  系统通讯参数配置.
 @else
	@brief  the system communication param.
 @endif
  */
typedef struct {
    uint8_t                         comm_type;           /**< @if Chinese 通讯类型(wifi/gprs...) @else communication types(wifi/gprs...) @endif */         
    uint8_t                         protocol_type;       /**< @if Chinese 通讯协议类型(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...)  @endif */              
    uint8_t                         dns_ip;              /**< @if Chinese 是否使用域名访问，为1表示域名方式，为0表示IP方式 @else use domain name access,1-DNS,0-IP @endif */
    uint32_t                        timeout_ms;          /**< @if Chinese 连接超时时间(毫秒) @else connect timeout(ms) @endif */
    ST_WIRELESS_PARAM               wireless;            /**< @if Chinese 无线拨号参数 @else the param of wireless dialing @endif */
    ST_HOST_PARAM                   host[MAX_HOST_CNT];  /**< @if Chinese 主机参数(最多2组) @else the param of server host(up to 2 groups) @endif */
    ST_SSL_PARAM                    ssl;                 /**< @if Chinese SSL参数 @else the SSL param @endif */
} ST_COMM_CONFIG;

/** 使用结构体不完全定义的方式提前定义，有效解决了 CommOps_t 结构体不能引用它的问题 */
struct _SysCommOps_t;
typedef struct _SysCommOps_t SysCommOps_t;

/**
 @if Chinese
	@brief  系统通讯操作结构体内部.
 @else
	@brief  the system communication operate structure.
 @endif
  */
typedef struct _CommOps_t {
    const char *                    name;   /**< @if Chinese 通讯类型名称 @else the name of communication type @endif */               
    const uint8_t                   id;     /**< @if Chinese 通讯类型id @else the id of communication type @endif */                   
    const void *                    udp;    /**< @if Chinese 通讯使用的udp协议通道 @else UDP protocol channel */                        
    const void *                    tcp;    /**< @if Chinese 通讯使用的tcp协议通道 @else tcp protocol channel */                    
    const void *                    ssl;    /**< @if Chinese 通讯使用的ssl协议通道 @else ssl protocol channel */                      

	/*!
	 @if Chinese
		@brief		预连接，像GPRS中的预拨号操作
		@param[in]	param的完整类型为	-	ST_WIRELESS_PARAM
		@return		0			-	成功
		@return		其它		-	失败
	 @else
		@brief		pre connection
		@param[in]	param		-	the param from ST_WIRELESS_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*predial)(const void *param); 

	/*!
	 @if Chinese
		@brief		域名解析操作
		@param[in]	ops			-	SysCommOps_t
		@param[in]	name		-	服务器的域名地址
		@param[out]	ip			-	应传入一个二维数组，用于存储域名name被解析后的ip列表
		@param[out]	ip_cnt		-	域名name解析出的ip个数
		@return		0			-	成功
		@return		其它		-	失败
		
	 @else
		@brief		domain name resolution
		@param[in]	ops			-	SysCommOps_t
		@param[in]	name		-	domain name
		@param[out]	ip			-	stores the IP list after the domain name is resolved
		@param[out]	ip_cnt		-	 the IP num after the domain name is resolved
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*dns)(const SysCommOps_t *ops, const char *name, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt);

	/*!
	 @if Chinese
		@brief		网络通讯异步连接操作，包括PPP连接
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param的完整类型为	-	ST_ASYNC_CONNECT_PARAM
		@return		0			-	成功
		@return		其它		-	失败
	 @else
		@brief		asynchronous connection,include PPP connect
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param		-	the param from ST_ASYNC_CONNECT_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/ 
    int (*async_predial)(const SysCommOps_t *ops, const void *param);
	
	/*!
	 @if Chinese
		@brief 		网络通讯异步连接操作，包括PPP连接、tcp连接、SSL连接(如果配置了SSL)
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param的完整类型为	-	ST_ASYNC_CONNECT_PARAM
		@return		0			-	成功
		@return		其它		-	失败
	 @else
		@brief		asynchronous connection,include PPP、TCP、SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param		-	the param from ST_ASYNC_CONNECT_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*async_connect)(const SysCommOps_t *ops, const void *param);

	/*!
	 @if Chinese
		@brief		网络通讯异步连接关闭操作
		@param[in]	ops			-	SysCommOps_t
		@return		0			-	成功
		@return		其它		-	失败
	 @else
		@brief		asynchronous connection,close connect
		@param[in]	ops			-	SysCommOps_t
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/    
    int (*async_disconnect)(const SysCommOps_t *ops);
    
	/*!
	 @if Chinese
		@brief		网络通讯异步连接状态查询,包括PPP连接、tcp连接、SSL连接(如果配置了SSL)
		@param[in]	ops			-	SysCommOps_t
		@param[out]	fd			-	返回的有效通讯句柄通过fd传递出去，此句柄可以用于通讯收发操作
		@param[out]	ip			-	步连接域名解析成功后返回的IP列表，最多有1个IP
		@param[out]	ip_cnt		-	域名name解析出的ip个数
		@param[in]	wait		-	当wait为非0时，表示阻塞式查询
		@return:    连接状态，参照AsyncConnectStateAPP_e
	 @else
		@brief		asynchronous connection，check status,include PPP、TCP、SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[out]	fd			-	communication handle
		@param[out]	ip			-	stores the IP list after the domain name is resolved，only have one IP
		@param[out]	ip_cnt		-	the IP num after the domain name is resolved
		@param[in]	wait		-	if wait is not 0，blocking check
		@return	    connect status，reference AsyncConnectStateAPP_e
	 @endif
	*/    
    int (*async_state_chk)(const SysCommOps_t *ops, int *fd, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt, int wait);

	/*!
	 @if Chinese
		@brief		网络通讯异步连接状态查询,包括PPP连接
		@return     连接状态，参照AsyncConnectStateAPP_e
	 @else
		@brief		asynchronous connection，check status,include PPP
		@return     connect status，reference AsyncConnectStateAPP_e
	 @endif
	*/      
	int (*async_ppp_state_chk)(void);

	/*!
	 @if Chinese
		@brief		DNS解析结果查询
		@return     app_true/app_false
	 @else
		@brief		check dns paser result
		@return     app_true/app_false
	 @endif
	*/
	int (*async_dns_paser_chk)(void);

	/*!
	 @if Chinese
		@brief		网络通讯同步连接操作，包括tcp连接或SSL连接(如果配置了SSL) 
		@param[in]	ops			-	SysCommOps_t
		@param[out]	rfd			-	返回的有效通讯句柄，此句柄可以用于通讯收发操作
		@param[in]	host		-	IP和端口，ST_HOST_IP_PARAM结构体
		@param[in]	ssl			-	ssl参数，ST_SSL_PARAM结构体
		@param[in]	timeout_ms	-	超时时间
		@return		>=0		-	成功，句柄
		@return		<0		-	失败
	 @else
		@brief		synchronous connection，include TCP、SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[out]	rfd			-	communication handle
		@param[in]	host		-	IP and port,struct ST_HOST_IP_PARAM
		@param[in]	ssl			-	ssl param，struct  ST_SSL_PARAM
		@param[in]	timeout_ms	-	timeout
		@return		>=0	-	success,communication handle
		@return		<0	-	fail
	 @endif
	*/      
    int (*connect)(const SysCommOps_t *ops, int *rfd, const void *host, const void *ssl, int timeout_ms);

	/*!
	 @if Chinese
		@brief		网络通讯数据发送操作
		@param[in]	ops			-	SysCommOps_t
		@param[in]	host		-	IP和端口，ST_HOST_IP_PARAM结构体
		@param[in]	fd			-	connect或async_state_chk获取的有效fd
		@param[in]	buf			-	应用发送数据的缓存区
		@param[in]	count		-	发送数据的长度
		@param[in]	timeout_ms	-	应用发送数据超时时间，单位为毫秒
		@return		>=0		-	成功，已发送数据的长度
		@return		<0		-	失败
	 @else
		@brief		Send data in TCP
		@param[in]	ops			-	SysCommOps_t
		@param[in]	host		-	IP and port,struct ST_HOST_IP_PARAM
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	buf			-	Buffer storing data to send
		@param[in]	count		-	Data length
		@param[in]	timeout_ms	-	timeout(ms)
		@return		>=0		-	success,length of sent data
		@return		<0		-	fail
	 @endif
	*/      
    int (*write)(const SysCommOps_t *ops, const void *host, int fd, const void *buf, int count, int timeout_ms);

	/*!
	 @if Chinese
		@brief		网络通讯数据接收操作
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect或async_state_chk获取的有效fd
		@param[out]	buf			-	应用接收数据的缓存区
		@param[in]	count		-	期望接收数据的长度
		@param[in]	timeout_ms	-	应用接收数据超时时间，单位为毫秒
		@return		>=0		-	成功，已接收数据的长度
		@return		<0		-	失败
	 @else
		@brief		receive data in TCP
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[out]	buf			-	Buffer storing data to receive
		@param[in]	count		-	The expected length of string will be received
		@param[in]	timeout_ms	-	timeout(ms)
		@return		>=0		-	success,length of received data
		@return		<0		-	fail
	 @endif
	*/        
    int (*read)(const SysCommOps_t *ops, int fd, void *buf, int count, int timeout_ms);

	/*!
	 @if Chinese
		@brief		获取socket通讯的参数操作
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect或async_state_chk获取的有效fd
		@param[in]	level		-	选项定义的层次；支持SOL_SOCKET
		@param[in]	optname		-	需获取的选项
		@param[out]	optval		-	指针，指向存放选项获取到的新值的缓冲区
		@param[out]	optlen		-	optval缓冲区长度
		@return		0		-	成功
		@return		其它	-	失败
	 @else
		@brief		get the parameter operation of socket communication
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	level		-	hierarchy of option definitions；support SOL_SOCKET
		@param[in]	optname		-	options to be get
		@param[out]	optval		-	obtained value
		@param[out]	optlen		-	optval length
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/          
    int (*getsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, void *optval, int *optlen);

	/*!
	 @if Chinese
		@brief		设置socket通讯的参数操作
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect或async_state_chk获取的有效fd
		@param[in]	level		-	选项定义的层次；支持SOL_SOCKET
		@param[in]	optname		-	需设置的选项
		@param[in]	optval		-	指针，需设置的值
		@param[in]	optlen		-	optval缓冲区长度
		@return		0		-	成功
		@return		其它	-	失败
	 @else
		@brief		set the parameter operation of socket communication
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	level		-	hierarchy of option definitions；support SOL_SOCKET
		@param[in]	optname		-	options to be set
		@param[in]	optval		-	value to be set
		@param[in]	optlen		-	optval length
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/     
    int (*setsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, const void *optval, int optlen);

	/*!
	 @if Chinese
		@brief		通讯关闭操作，仅仅是关闭系统句柄
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect或async_state_chk获取的有效fd
		@return		0		-	成功
		@return		其它	-	失败
	 @else
		@brief		the communication closing operation is only to close the system handle
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/       
    int (*close)(const SysCommOps_t *ops, int fd);   

	/*!
	 @if Chinese
		@brief		通讯退出操作，像GPRS中的ppp logout操作
		@param[in]	arg			-	NULL
		@return		0			-	成功
		@return		其它		-	失败
	 @else
		@brief		communication exit,as GPRS ppp logout
		@param[in]	arg			-	NULL
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*exit)(const void *arg);   
} CommOps_t;

/**
 @if Chinese
	@brief  系统通讯操作结构体(对外).
 @else
	@brief  the system communication operate structure(external).
 @endif
  */
typedef struct _SysCommOps_t {
    const void *                    protocol;     /**< @if Chinese 通讯协议类型(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...)  @endif */
    const CommOps_t *               comm;         /**< @if Chinese 通讯操作接口 @else communication operation interface  @endif */
} SysCommOps_t;

/** extern APIS */

/*!
 @if Chinese
	@brief		应用通讯操作初始化(仅获取应用通讯的操作方法)
	@param[in]	comm_type		-	通讯类型编号，如CT_WIFI/CT_GPRS ...
	@param[in]	protocol_type	-	网络通讯协议类型，如SOCK_TCP/SOCK_SSL/SOCK_UDP
	@param[out]	ops				-	应用通讯操作的对象指针 
	@return		!NULL	-	成功,应用通讯操作的对象指针 
	@return		NULL	-	失败
 @else
	@brief		communication operation initialization
	@param[in]	comm_type		-	communication types,CT_WIFI/CT_GPRS ...
	@param[in]	protocol_type	-	communication protocol types(tcp/ssl/udp...)
	@param[out]	ops				-	object point to communication operation
	@return		!NULL	-	success,object point to communication operation
	@return		NULL	-	fail
 @endif
*/   
extern SysCommOps_t *wnet_comm_ops_init(uint8_t comm_type, uint8_t protocol_type, SysCommOps_t *ops);

/*!
 @if Chinese
	@brief		设置wnet库的日志开关，默认情况是日志关闭的
	@param[in]	on			-	欲设置的日志开关状态，非0表示打开，为0表示关闭，见 LOGGER_MODULE_ON 枚举定义
	@return		0				-	成功
	@return		其它			-	失败
 @else
	@brief		set the log switch of the wnet library. the log is off by default
	@param[in]	on			-	 0:close;!0:open
	@return		0				-	success
	@return		other			-	fail
		
 @endif
*/   
extern int wnet_logger_on(int on);
/*!
 @if Chinese
	@brief		获取libwnet库的版本信息
	@param[out]	version			-	libwnet库的版本信息输出
	@param[in]	size			-	version执行的buffer长度，建议至少64字节
	@return		0				-	成功
	@return		其它			-	失败
 @else
	@brief		get libwent version information
	@param[out]	version			-	version information
	@param[in]	size			-	 the version length,At least 64 bytes are recommended
	@return		0				-	success
	@return		other			-	fail
		
 @endif
*/   
extern int wnet_get_version(char *version, int size);

/*!
 @if Chinese
	@brief		停止终端异步线程 
	@return		0				-	成功
	@return		其它			-	失败
 @else
	@brief		stop asynchronous thread
	@return		0				-	success
	@return		other			-	fail
	
 @endif
*/ 
extern int async_thread_stop(void);

//PPP超时时间，pppTimeout的区间范围【10-60】，如不调用这个函数，则PPP超时时间默认30秒
/*!
 @if Chinese
	@brief		设置PPP超时时间，pppTimeout的区间范围【10-60】，如不调用这个函数，则PPP超时时间默认30秒
	@param[in]	pppTimeout		-	PPP超时时间
 @else
	@brief		set PPP timeout[10s-60s],default 30s
	@param[in]	pppTimeout		-	 PPP timeout(s)
 @endif
*/   
extern void gprs_set_ppp_timeout(uint8_t pppTimeout);

#ifdef __cplusplus
}
#endif

#endif


